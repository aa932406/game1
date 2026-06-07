#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <hash_map>

class CDBCFile
{
public:
	enum FIELD_TYPE
	{
		FT_INT = 0,
		FT_FLOAT = 1,
		FT_STRING = 2,
	};

	struct FIELD
	{
		union
		{
			int32_t iValue;
			float fValue;
			const char* pString;
		};
	};

	struct FILE_HEAD
	{
		uint32_t m_Identify;
		uint32_t m_nFieldsNum;
		uint32_t m_nRecordsNum;
		uint32_t m_nStringBlockSize;
	};

public:
	CDBCFile();
	~CDBCFile();

	bool OpenFromMemory(const char* pMemory, const char* pDeadEnd, const char* szFileName);
	bool OpenFromMemoryImpl_Binary(const char* pMemory, const char* pDeadEnd, const char* szFileName);
	bool OpenFromMemoryImpl_Text(const char* pMemory, const char* pDeadEnd, const char* szFileName);
	void CreateIndex(int32_t nColum, const char* szFileName);

	int32_t GetRecordsNum() const { return m_nRecordsNum; }
	int32_t GetFieldsNum() const { return m_nFieldsNum; }

	const FIELD* SearchField(int32_t nIndex) const
	{
		auto itFind = m_hashIndex.find(nIndex);
		if (itFind != m_hashIndex.end())
			return itFind->second;
		return nullptr;
	}

	int32_t SearchPosition(int32_t nIndex) const;

private:
	int32_t m_nRecordsNum;
	int32_t m_nFieldsNum;
	int32_t m_nIndexColum;
	int32_t m_nStringBufSize;
	char* m_pStringBuf;
	std::vector<FIELD> m_vDataBuf;
	std::vector<FIELD_TYPE> m_vFieldType;
	__gnu_cxx::hash_map<int, FIELD*> m_hashIndex;
};
