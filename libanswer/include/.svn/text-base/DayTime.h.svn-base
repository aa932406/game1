#pragma once

#include <time.h>
#include <iostream>

namespace Answer
{
	namespace DayTime
	{
		ANSWER_EXPORT_SYMBOL int64_t tick();
		ANSWER_EXPORT_SYMBOL int32_t now();
		ANSWER_EXPORT_SYMBOL tm localnow();
		ANSWER_EXPORT_SYMBOL tm localnow(int time);
		ANSWER_EXPORT_SYMBOL tm utcnow();
		ANSWER_EXPORT_SYMBOL void sleep(int milliseconds);
		ANSWER_EXPORT_SYMBOL int daydiff(int old);
		ANSWER_EXPORT_SYMBOL int daydiffBw(int old,int32_t newTime);
		ANSWER_EXPORT_SYMBOL int day18diff(int old);
		ANSWER_EXPORT_SYMBOL int hourzero(int time);
		ANSWER_EXPORT_SYMBOL int dayzero(int time);
		ANSWER_EXPORT_SYMBOL int monthzero(int time);
		ANSWER_EXPORT_SYMBOL int weekdiff(int old);
		ANSWER_EXPORT_SYMBOL int monthdiff(int old);
		ANSWER_EXPORT_SYMBOL bool betweendate(int32_t begin_date, int32_t end_date);
		ANSWER_EXPORT_SYMBOL int32_t StringToIntTime( std::string StringTime );
		ANSWER_EXPORT_SYMBOL tm StringToTM (const std::string& StringTime);
	}
}

