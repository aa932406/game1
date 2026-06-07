#include "stdafx.h"
#include "CDBCFile.h"
#include "Logger.h"

CDBCFile::CDBCFile()
	: m_nRecordsNum(0), m_nFieldsNum(0), m_nIndexColum(-1)
	, m_nStringBufSize(0), m_pStringBuf(nullptr)
{

}

CDBCFile::~CDBCFile()
{
	if (m_pStringBuf)
	{
		delete[] m_pStringBuf;
		m_pStringBuf = nullptr;
	}
}

bool CDBCFile::OpenFromMemory(const char* pMemory, const char* pDeadEnd, const char* szFileName)
{
	if (!pMemory || !pDeadEnd)
	{
		assert(pMemory && pDeadEnd);
		return false;
	}

	if ((pDeadEnd - pMemory) > 16 && *(uint32_t*)pMemory == 0x43424457)
		return OpenFromMemoryImpl_Binary(pMemory, pDeadEnd, szFileName);
	else
		return OpenFromMemoryImpl_Text(pMemory, pDeadEnd, szFileName);
}

bool CDBCFile::OpenFromMemoryImpl_Binary(const char* pMemory, const char* pDeadEnd, const char* szFileName)
{
	FILE_HEAD theHead;
	memcpy(&theHead, pMemory, sizeof(theHead));

	if (theHead.m_Identify != 0x43424457)
		return false;

	if (4 * (2 * theHead.m_nRecordsNum * (int64_t)theHead.m_nFieldsNum + theHead.m_nFieldsNum + 4)
		+ theHead.m_nStringBlockSize > (uint64_t)(pDeadEnd - pMemory))
		return false;

	const char* p = pMemory + 16;
	m_nRecordsNum = theHead.m_nRecordsNum;
	m_nFieldsNum = theHead.m_nFieldsNum;
	m_nStringBufSize = theHead.m_nStringBlockSize;

	m_pStringBuf = new char[theHead.m_nStringBlockSize];
	if (!m_pStringBuf)
		return false;

	m_vFieldType.resize(theHead.m_nFieldsNum);
	memcpy(&m_vFieldType[0], p, 4 * theHead.m_nFieldsNum);
	p += 4 * theHead.m_nFieldsNum;

	memcpy(m_pStringBuf, p + 4 * theHead.m_nRecordsNum * theHead.m_nFieldsNum, theHead.m_nStringBlockSize);

	m_vDataBuf.resize(theHead.m_nRecordsNum * theHead.m_nFieldsNum);
	for (int32_t i = 0; i < theHead.m_nRecordsNum; ++i)
	{
		for (int32_t j = 0; j < theHead.m_nFieldsNum; ++j)
		{
			FIELD& field = m_vDataBuf[i * theHead.m_nFieldsNum + j];
			switch (m_vFieldType[j])
			{
			case FT_INT:
			case FT_FLOAT:
				memcpy(&field, p, 4);
				break;
			case FT_STRING:
				field.pString = m_pStringBuf + field.iValue;
				break;
			}
			p += 4;
		}
	}

	return true;
}

bool CDBCFile::OpenFromMemoryImpl_Text(const char* pMemory, const char* pDeadEnd, const char* szFileName)
{
	// Text format: first line is field names, subsequent lines are records
	// Fields separated by tab
	std::vector<std::string> fieldNames;
	std::vector<std::vector<std::string>> records;

	const char* p = pMemory;
	const char* lineStart = p;

	// Parse first line for field names
	while (p < pDeadEnd)
	{
		if (*p == '\n' || *p == '\r')
		{
			std::string line(lineStart, p - lineStart);
			if (!line.empty())
			{
				if (fieldNames.empty())
				{
					// First line: field names
					size_t pos = 0, end;
					while ((end = line.find('\t', pos)) != std::string::npos)
					{
						fieldNames.push_back(line.substr(pos, end - pos));
						pos = end + 1;
					}
					fieldNames.push_back(line.substr(pos));
				}
				else
				{
					// Data line
					std::vector<std::string> record;
					size_t pos = 0, end;
					while ((end = line.find('\t', pos)) != std::string::npos)
					{
						record.push_back(line.substr(pos, end - pos));
						pos = end + 1;
					}
					record.push_back(line.substr(pos));
					if (record.size() == fieldNames.size())
						records.push_back(record);
				}
			}
			lineStart = p + 1;
			if (*p == '\r' && p + 1 < pDeadEnd && *(p + 1) == '\n')
			{
				p++;
				lineStart = p + 1;
			}
		}
		p++;
	}

	// Handle last line
	if (lineStart < pDeadEnd)
	{
		std::string line(lineStart, pDeadEnd - lineStart);
		if (!line.empty() && !fieldNames.empty())
		{
			std::vector<std::string> record;
			size_t pos = 0, end;
			while ((end = line.find('\t', pos)) != std::string::npos)
			{
				record.push_back(line.substr(pos, end - pos));
				pos = end + 1;
			}
			record.push_back(line.substr(pos));
			if (record.size() == fieldNames.size())
				records.push_back(record);
		}
	}

	m_nFieldsNum = (int32_t)fieldNames.size();
	m_nRecordsNum = (int32_t)records.size();
	m_nStringBufSize = 0;

	// Calculate string buffer size
	for (int32_t i = 0; i < m_nRecordsNum; ++i)
	{
		for (int32_t j = 0; j < m_nFieldsNum; ++j)
		{
			m_nStringBufSize += (int32_t)records[i][j].size() + 1;
		}
	}

	m_pStringBuf = new char[m_nStringBufSize];
	if (!m_pStringBuf)
		return false;

	m_vFieldType.resize(m_nFieldsNum, FT_INT);
	m_vDataBuf.resize(m_nRecordsNum * m_nFieldsNum);

	int32_t stringOffset = 0;
	for (int32_t i = 0; i < m_nRecordsNum; ++i)
	{
		for (int32_t j = 0; j < m_nFieldsNum; ++j)
		{
			FIELD& field = m_vDataBuf[i * m_nFieldsNum + j];
			const std::string& val = records[i][j];

			// Try to parse as int
			char* endPtr = nullptr;
			long intVal = strtol(val.c_str(), &endPtr, 10);
			if (*endPtr == '\0' && endPtr != val.c_str())
			{
				field.iValue = (int32_t)intVal;
				m_vFieldType[j] = FT_INT;
			}
			else
			{
				// Try to parse as float
				char* floatEnd = nullptr;
				float floatVal = strtof(val.c_str(), &floatEnd);
				if (*floatEnd == '\0' && floatEnd != val.c_str())
				{
					field.fValue = floatVal;
					m_vFieldType[j] = FT_FLOAT;
				}
				else
				{
					// String
					strcpy(m_pStringBuf + stringOffset, val.c_str());
					field.iValue = stringOffset;
					stringOffset += (int32_t)val.size() + 1;
					m_vFieldType[j] = FT_STRING;
				}
			}
		}
	}

	// Fix string field pointers
	for (int32_t i = 0; i < m_nRecordsNum; ++i)
	{
		for (int32_t j = 0; j < m_nFieldsNum; ++j)
		{
			if (m_vFieldType[j] == FT_STRING)
			{
				FIELD& field = m_vDataBuf[i * m_nFieldsNum + j];
				field.pString = m_pStringBuf + field.iValue;
			}
		}
	}

	return true;
}

int32_t CDBCFile::SearchPosition(int32_t nIndex) const
{
	for (int32_t i = 0; i < m_nRecordsNum; ++i)
	{
		const FIELD* pField = &m_vDataBuf[i * m_nFieldsNum];
		if (pField->iValue == nIndex)
			return i;
	}
	return -1;
}

void CDBCFile::CreateIndex(int32_t nColum, const char* szFileName)
{
	if (nColum < 0 || nColum >= m_nFieldsNum || m_nIndexColum == nColum)
		return;

	m_hashIndex.clear();
	for (int32_t i = 0; i < m_nRecordsNum; ++i)
	{
		FIELD* p = &m_vDataBuf[i * m_nFieldsNum + nColum];
		auto itFind = m_hashIndex.find(p->iValue);
		if (itFind != m_hashIndex.end())
		{
			// Duplicate index
			return;
		}
		m_hashIndex.insert(std::make_pair(p->iValue, p));
	}
	m_nIndexColum = nColum;
}
