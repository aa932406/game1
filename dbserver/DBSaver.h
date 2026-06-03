#pragma once

#include "DataStruct.h"


class DBSaver
	: public Answer::Thread
{
public:
	DBSaver();
	virtual ~DBSaver();

public:
	virtual void run();
	void stop();

public:
	void AddSqlString( const std::string& sqlStr );
	void AddPlayerDB( const PlayerDBSql& playerdb );

private:
	void checkSqlStringList();
	void checkPlayerDBList();

private:
	typedef Answer::SafeQueue<std::string> SafeSqlStrList;
	typedef Answer::SafeQueue<PlayerDBSql> SafePlayerDBList;
	SafeSqlStrList		m_sqls;
	SafePlayerDBList	m_playerdbs;
	bool				m_bRun;
};

#define DB_SAVER Answer::Singleton<DBSaver>::instance()

