#include "stdafx.h"
#include "Timer.h"
#include "Activity.h"
#include "GameService.h"
#include "PetManager.h"
#include "ActivityManager.h"
#include "GMBackstage.h"
#include "WorldBoss.h"

using namespace Answer;

CTimer::CTimer()
: m_nTick( DayTime::tick() ), m_nNow( DayTime::now() ), m_tmLocalNow( DayTime::localnow() ), m_tmLastLocalNow( m_tmLocalNow ), m_nextAnnoucement( 0 ),/* m_nDaysFromStart( 0 ),m_nDaysFromUnite( 0 ),*/ m_nWeekDay( 0 )
{
//	m_nDaysFromStart	= DayTime::daydiff( CFG_DATA.getServerStartTime() );
//	m_nDaysFromUnite	= DayTime::daydiff( CFG_DATA.getServerStartTime() );
	m_nWeekDay			= static_cast<int8_t>( ( m_tmLocalNow.tm_wday + 6 ) % 7 + 1 );
}

CTimer::~CTimer()
{

}

void CTimer::run()
{
	m_bRunning = true;
	while ( m_bRunning )
	{
		m_nTick			= DayTime::tick();
		m_nNow			= DayTime::now();
		m_tmLocalNow	= DayTime::localnow();
		checkNewMinute( m_tmLocalNow );
		checkAnnoucement( m_tmLocalNow );
		
		ACTIVITY_MANAGER.OnUpdate();
		GM_BACKSTAGE.OnUpdate();
		WORLDBOSS.Update( m_nTick );

		DayTime::sleep(10);
	}
}

void CTimer::Init()
{

}

void CTimer::Start()
{
	m_bRunning			= true;
	m_tmLastLocalNow	= GetLocalNow();
	m_nextAnnoucement	= 0;

	start(); //启动线程
}

void CTimer::Stop()
{
	m_bRunning = false;
	join();
}

int64_t CTimer::GetTick()
{
	return m_nTick;
}

int32_t CTimer::GetNow()
{
	return m_nNow;
}

const tm& CTimer::GetLocalNow()
{
	return m_tmLocalNow;
}

int32_t CTimer::GetDaysFromStart()
{
	return DayTime::daydiff( CFG_DATA.getServerStartTime() );
}

int32_t CTimer::GetDaysFromUnite()
{
	return DayTime::daydiff( CFG_DATA.getServerStartTime() );
}

int8_t CTimer::GetWeekDay()
{
	return m_nWeekDay;
}

bool CTimer::BetweenDate( int32_t begin_date, int32_t end_date )
{
	int32_t date = ( m_tmLocalNow.tm_year+1900 )*10000 + ( m_tmLocalNow.tm_mon+1 )*100 + m_tmLocalNow.tm_mday;
	return date >= begin_date && date <= end_date;
}

void CTimer::checkNewMinute(const tm &localnow)
{
	if (localnow.tm_min != m_tmLastLocalNow.tm_min)
	{
		GAME_SERVICE.onNewMinuteCome(localnow.tm_hour * 60 + localnow.tm_min);
	}
	if ( localnow.tm_yday != m_tmLastLocalNow.tm_yday )
	{
		onDaySwitch();
		GAME_SERVICE.SendServerDiffToGlobal();
	}

	m_tmLastLocalNow = localnow;
}

void CTimer::onDaySwitch()
{
//	m_nDaysFromStart	= DayTime::daydiff( CFG_DATA.getServerStartTime() );
//	m_nDaysFromUnite	= DayTime::daydiff( CFG_DATA.getServerStartTime() );
	m_nWeekDay			= static_cast<int8_t>( ( m_tmLocalNow.tm_wday + 6 ) % 7 + 1 );

	PET_MANAGER.ResetRecords();
}

void CTimer::checkAnnoucement(const tm &localnow)
{
	const CfgAnnoucementTimeTable& allAnnoucements = CFG_DATA.getAllAnnoucementTime();					//公告的列表
	if (localnow.tm_hour == 0 && localnow.tm_min == 0)
	{
		m_nextAnnoucement = 0;
	}

	for (; m_nextAnnoucement < allAnnoucements.size(); ++m_nextAnnoucement)
	{
		const CfgAnnoucementTime &annoucement = allAnnoucements[m_nextAnnoucement];

		if (annoucement.hour*60+annoucement.minute > localnow.tm_hour*60+localnow.tm_min)
		{
			break;
		}

		if (std::find(annoucement.weekday.begin(), annoucement.weekday.end(), (localnow.tm_wday + 6)%7 + 1) == annoucement.weekday.end() || !DayTime::betweendate(annoucement.begin_date, annoucement.end_date))
		{
			continue;
		}

		NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_ANNOUCEMENT);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(annoucement.annoucement_id);
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.broadcast(packet);
	}
}
