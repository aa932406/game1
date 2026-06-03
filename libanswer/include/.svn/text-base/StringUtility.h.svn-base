#pragma once

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
typedef std::vector<std::string> StringVector;
typedef std::vector<int32_t> Int32Vector;

namespace Answer
{
	#if defined(LIBANSWER_WINDOWS)
	#define		tvsnprintf		_vsnprintf
	#define		tstricmp		_stricmp
	#define		tsnprintf		_snprintf
	#elif defined(LIBANSWER_LINUX)
	#define		tvsnprintf		vsnprintf
	#define		tstricmp		strcasecmp
	#define		tsnprintf		snprintf
	#define     _atoi64(val) strtoll(val,NULL,10)
	#endif
	namespace StringUtility
	{
		ANSWER_EXPORT_SYMBOL int utf8Strlen(const char *str);
		ANSWER_EXPORT_SYMBOL StringVector split(const std::string& str, const std::string& delims = ",", uint32_t maxSplits = 0); 
		ANSWER_EXPORT_SYMBOL std::string combi(const Int32Vector & ve,const std::string& delims ); 
		ANSWER_EXPORT_SYMBOL std::string toString( int32_t val, uint16_t width, char fill, std::ios::fmtflags flags );
		ANSWER_EXPORT_SYMBOL std::string toString( int64_t val, uint16_t width, char fill, std::ios::fmtflags flags );
		ANSWER_EXPORT_SYMBOL std::string toString( double val, uint16_t precision, uint16_t width, char fill, std::ios::fmtflags flags );
		ANSWER_EXPORT_SYMBOL std::string replace( const std::string& templatestr, const std::string& findstr, const std::string& replacestr );
	}
}
