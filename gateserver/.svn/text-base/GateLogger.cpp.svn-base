#include "stdafx.h"

#include "GateLogger.h"
#include "GateServer.h"

using namespace Answer;

GateLogger::GateLogger()
	: m_bRunning(false), m_mutex(), m_cond(m_mutex), m_lastOnlineCountRecordTime(0)
{

}

GateLogger::~GateLogger()
{

}

void GateLogger::run()
{
	while (m_bRunning)
	{
		recordOnline();

		m_cond.timedwait(60);
	}
}

void GateLogger::startLogger()
{
	m_bRunning = true;

	start();
}

void GateLogger::stopLogger()
{
	m_bRunning = false;
	m_cond.notify();
	join();
}

void GateLogger::recordOnline()
{
	int32_t nowTime = DayTime::now();

	if (nowTime - m_lastOnlineCountRecordTime >= 5*60)
	{
		OnlineStatus status = GATE_SERVER.getOnlineStatus();

		char szSQL[MAX_SQL_LENGTH] = {};
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `log_online` (`login`, `active`, `inactive`, `online`, `time`) VALUES (%d, %d, %d, %d, %d)", status.login, status.active, status.inactive, status.active + status.inactive, nowTime);

		MySqlDBGuard db(DBPOOL);
		db.excute(szSQL);

		m_lastOnlineCountRecordTime = nowTime;
	}
}
