#include "stdafx.h"

#include "DBSaver.h"
#include "DBServer.h"
#include "DataStruct.h"

using namespace Answer;

DBSaver::DBSaver()
{
}

DBSaver::~DBSaver()
{
}

void DBSaver::run()
{
	m_bRun = true;
	while ( m_bRun )
	{
		int64_t startTick = DayTime::tick();

		checkSqlStringList();
		checkPlayerDBList();

		int64_t endTick = DayTime::tick();
		int32_t usedTick = static_cast<int32_t>( endTick - startTick );
		if ( usedTick < 50 )
		{
			DayTime::sleep( 50-usedTick );
		}
	}
}

void DBSaver::stop()
{
	m_bRun = false;			//先结束条线程
	join();
	checkSqlStringList();
	checkPlayerDBList();
}

void DBSaver::AddSqlString( const std::string& sqlStr )
{
	m_sqls.push( sqlStr );
}

void DBSaver::AddPlayerDB( const PlayerDBSql& playerdb )
{
	m_playerdbs.push( playerdb );
}

void DBSaver::checkSqlStringList()
{
	MySqlDBGuard db(DBPOOL);

	while ( m_sqls.size() > 0 )
	{
		//printf( "%s\n", m_sqls.front().c_str() );
		//LOG_INFO( "%s;\n", m_sqls.front().c_str() );
		db.excute( m_sqls.front().c_str() );
		m_sqls.pop();
	}
}

void DBSaver::checkPlayerDBList()
{
	MySqlDBGuard db(DBPOOL);

	while ( m_playerdbs.size() > 0 )
	{
		PlayerDBSql playerdb = m_playerdbs.pop();
		SqlStringList::iterator iter = playerdb.sqls.begin();
		SqlStringList::iterator eiter = playerdb.sqls.end();
		for ( ; iter != eiter; ++iter )
		{
			db.excute( iter->c_str() );
		}
		DB_SERVER.onSaveOver( playerdb.backId );
		//m_playerdbs.pop();
	}
}
