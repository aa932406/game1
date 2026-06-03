#include "stdafx.h"

#include "DayTime.h"
#include <sstream>
#ifdef LIBANSWER_LINUX
#include <sys/time.h>
#endif

using namespace Answer;

int64_t DayTime::tick()
{
#ifdef LIBANSWER_WINDOWS
	return GetTickCount();
#endif

#ifdef LIBANSWER_LINUX
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000+tv.tv_usec/1000;
#endif
}

int32_t DayTime::now()
{
	return static_cast<int32_t>(time(NULL));
}

tm DayTime::localnow()
{
	time_t nowtimet = time(NULL);
	tm *ptm = localtime(&nowtimet);
	if (ptm != NULL)
	{
		return *ptm;
	}
	else
	{
		return tm();
	}
}

tm DayTime::localnow(int time)
{
	time_t ttime = (time_t)time;
	tm tmtime = *(localtime(&ttime));
	return tmtime;
}

tm DayTime::utcnow()
{
	time_t nowtimet = time(NULL);
	tm *ptm = gmtime(&nowtimet);
	if (ptm != NULL)
	{
		return *ptm;
	}
	else
	{
		return tm();
	}
}

void DayTime::sleep(int milliseconds)
{
#ifdef LIBANSWER_WINDOWS
	Sleep(milliseconds);
#endif

#ifdef LIBANSWER_LINUX
	timespec req;
	req.tv_nsec = milliseconds%1000;
	req.tv_sec = (milliseconds-req.tv_nsec)/1000;
	req.tv_nsec = req.tv_nsec*1000000;
	timespec rem;
	nanosleep(&req, &rem);
#endif
}

int DayTime::daydiff(int old)
{
	int oldzero = dayzero(old);
	int nowzero = dayzero(now());

	return (nowzero - oldzero)/86400;
}

int DayTime::daydiffBw(int old,int32_t newTime)
{
	int oldzero = dayzero(old);
	int nowzero = dayzero(newTime);

	return (nowzero - oldzero)/86400;
}

int DayTime::day18diff(int old)
{
	time_t ttime_old = (time_t)old;
	tm tmtime_old = *(localtime(&ttime_old));

	int result_old  = 0;
	if (tmtime_old.tm_hour >= 18)
	{
		result_old =  (int)(ttime_old - tmtime_old.tm_sec - tmtime_old.tm_min*60 - (tmtime_old.tm_hour-18)*3600);
	}
	else
	{
		result_old = (int)(ttime_old - 86400+(60-tmtime_old.tm_sec)+(59-tmtime_old.tm_min)*60+(17-tmtime_old.tm_hour)*3600);
	}

	time_t ttime_now = (time_t)now();
	tm tmtime_now = *(localtime(&ttime_now));

	int result_now  = 0;
	if (tmtime_now.tm_hour >= 18)
	{
		result_now =  (int)(ttime_now - tmtime_now.tm_sec - tmtime_now.tm_min*60 - (tmtime_now.tm_hour-18)*3600);
	}
	else
	{
		result_now = (int)(ttime_now - 86400+(60-tmtime_now.tm_sec)+(59-tmtime_now.tm_min)*60+(17-tmtime_now.tm_hour)*3600);
	}

	return (result_now -result_old)/86400;
}

int DayTime::hourzero(int time)
{
	time_t ttime = (time_t)time;
	tm tmtime = *(localtime(&ttime));

	return (int)(ttime - tmtime.tm_sec - tmtime.tm_min*60);
}

int DayTime::dayzero(int time)
{
	time_t ttime = (time_t)time;
	tm tmtime = *(localtime(&ttime));

	return (int)(ttime - tmtime.tm_sec - tmtime.tm_min*60 - tmtime.tm_hour*3600);
}

int DayTime::monthzero(int time)
{
	time_t ttime = (time_t)time;
	tm tmtime = *(localtime(&ttime));

	return (int)(ttime - tmtime.tm_sec - tmtime.tm_min*60 - tmtime.tm_hour*3600-tmtime.tm_mday*24*60*60);
}

int DayTime::weekdiff(int old)
{
	time_t told = (time_t)old;
	tm tmold = *(localtime(&told));
	tmold.tm_wday = (tmold.tm_wday + 6)%7;

	time_t tnow = (time_t)now();
	tm tmnow = *(localtime(&tnow));
	tmnow.tm_wday = (tmnow.tm_wday + 6)%7;

	int oldzero = (int)(told - tmold.tm_sec - tmold.tm_min*60 - tmold.tm_hour*3600 - tmold.tm_wday*86400);
	int nowzero = (int)(tnow - tmnow.tm_sec - tmnow.tm_min*60 - tmnow.tm_hour*3600 - tmnow.tm_wday*86400);

	return (nowzero - oldzero)/604800;
}

int DayTime::monthdiff(int old)
{
	time_t told = (time_t)old;
	tm tmold = *(localtime(&told));

	time_t tnow = (time_t)now();
	tm tmnow = *(localtime(&tnow));

	return tmnow.tm_mon - tmold.tm_mon;
}

bool DayTime::betweendate(int32_t begin_date, int32_t end_date)
{
	tm nowlocal = localnow();

	int32_t date = (nowlocal.tm_year+1900)*10000 + (nowlocal.tm_mon+1)*100 + nowlocal.tm_mday;

	return date >= begin_date && date <= end_date;
}

int32_t DayTime::StringToIntTime( std::string StringTime )
{
	if ( StringTime.size() != 19 )
	{
		return 0;
	}
	if(StringTime.compare("0000-00-00 00:00:00") == 0)
	{
		return 0;
	}

	tm localtm = StringToTM(StringTime);

	time_t result = mktime(&localtm);

	return (int32_t)result;
}

tm DayTime::StringToTM (const std::string& StringTime)
{
	tm* timetm = NULL;
	std::string timestr;
	std::stringstream timess( StringTime );
	char buf[] = "-- :: ";     
	uint32_t index = 0;

	int32_t tm_time[6] = {0};
	while(getline(timess, timestr, buf[index]))
	{
		tm_time[index] = atoi(timestr.c_str());
		++index;
	}

	time_t now;
	time(&now);

	timetm = localtime(&now);

	timetm->tm_year = tm_time[0] - 1900;
	timetm->tm_mon = tm_time[1] -1;
	timetm->tm_mday = tm_time[2];
	timetm->tm_hour = tm_time[3];
	timetm->tm_min = tm_time[4];
	timetm->tm_sec = tm_time[5];

	time_t newTime = mktime(timetm);

	timetm = localtime(&newTime);

	return *timetm;
}
