#include "stdafx.h"

#include "StringUtility.h"
#include <sstream>
#include <string.h>

using namespace Answer;

int StringUtility::utf8Strlen(const char *str)
{
	if (str == NULL)
	{
		return 0;
	}

	int byteLength = static_cast<int>(strlen(str));

	int length = 0;

	int index = 0;
	while (index < byteLength)
	{
		char ch = str[index];

		length++;

		index++;

		if (index >= byteLength)
		{
			break;
		}

		if (ch & 0x80)
		{
			ch <<= 1;
			while(ch & 0x80)
			{
				index++;
				ch <<=1;
			}
		}
	}

	return length;
}

StringVector StringUtility::split(const std::string& str, const std::string& delims /* =  */, uint32_t maxSplits /* = 0 */)
{
	StringVector ret;  

	uint32_t numSplits = 0;  

	size_t start = 0;
	size_t pos = 0;  
	do   
	{  
		pos = str.find_first_of(delims, start);  
		if (pos == start)  
		{  
			start = pos + 1;  
		}  
		else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))  
		{  
			ret.push_back( str.substr(start) );  
			break;  
		}  
		else  
		{  
			ret.push_back( str.substr(start, pos - start) );  
			start = pos + 1;  
		}  

		start = str.find_first_not_of(delims, start);  
		++numSplits;  

	} while (pos != std::string::npos);  

	return ret;  
}

std::string StringUtility::combi(const Int32Vector & ve,const std::string& delims )
{
	std::string str = "";
	Int32Vector::const_iterator it = ve.begin();
	if (it != ve.end())
	{
		char buff[20] = {};
		std::string tempStr = "";
		sprintf(buff,"%d",*it);
		tempStr = buff;
		str+= tempStr;
		it++;
	}

	for (;it != ve.end();++it)
	{
		char buff[20] = {};
		std::string tempStr = "";
		sprintf(buff,"%d",*it);
		tempStr = buff;
		str += ":";
		str+= tempStr;
	}

	return str;
}

std::string StringUtility::toString( int32_t val, uint16_t width, char fill, std::ios::fmtflags flags )  
{  
	std::ostringstream stream;  
	stream.width(width);  
	stream.fill(fill);  
	if (flags)  
		stream.setf(flags);  
	stream << val;  
	return stream.str();  
}

std::string StringUtility::toString( int64_t val, uint16_t width, char fill, std::ios::fmtflags flags )
{  
	std::ostringstream stream;  
	stream.width(width);  
	stream.fill(fill);  
	if (flags)  
		stream.setf(flags);  
	stream << val;  
	return stream.str();  
}

std::string StringUtility::toString( double val, uint16_t precision, uint16_t width, char fill, std::ios::fmtflags flags )
{  
	std::ostringstream stream;  
	stream.precision(precision);  
	stream.width(width);  
	stream.fill(fill);  
	if (flags)  
		stream.setf(flags);  
	stream << val;  
	return stream.str();  
}

std::string StringUtility::replace( const std::string& templatestr, const std::string& findstr, const std::string& replacestr )  
{  
	std::string ret = templatestr;  
	std::string::size_type pos = 0;  
	pos = ret.find(findstr,pos);  
	while (pos != std::string::npos)  
	{  
		ret.replace(pos,findstr.size(),replacestr);  
		pos = ret.find(findstr,pos+replacestr.size());  
	}  
	return ret;  
}  

