#include "stdafx.h"

#include "DBServer.h"
#include "DBSaver.h"
#include "LogParser.h"

#include <string>

using namespace Answer;
using namespace std;

void initDBPool();
void startDBServer();
void stopDBServer();
void startLoggerParser();

int main(int argc, char *argv[])
{
	Application::setWorkingDirectory();

	Application::initLogger("dbserver", LOG_LEVEL_INFO);
	
	initDBPool();

	DB_SAVER.start();

	startDBServer();

	startLoggerParser();

#ifdef _DEBUG
	printf( " dbserver init over!!!\n " );
#endif

	Application::hookSignal();

	Application::waitSignal();

	Application::unhookSignal();

	stopDBServer();

	DB_SAVER.stop();

	return 0;
}

void initDBPool()
{
	string inifile = "database.ini";

	Inifile ini;
	ini.parse(inifile);

	int conn = ini.getIntValue("DBServer", "conn");

	string host = ini.getStrValue("MySQL", "host");
	string user = ini.getStrValue("MySQL", "user");
	string password = ini.getStrValue("MySQL", "password");
	string db = ini.getStrValue("MySQL", "db");
	int port = ini.getIntValue("MySQL", "port");

	LOG_INFO("parse %s, conn = %d, host = %s, user = %s, password = %s, db = %s, port = %d\n", inifile.c_str(), conn, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port);

	int realconn = DBPOOL.init(conn, host, user, password, db, port);

	LOG_INFO("get %d real db conn\n", realconn);

	if (realconn <= 0)
	{
		LOG_ERROR("Failed to init DB Pool, exit\n");
		exit(EXIT_FAILURE);
	}
}

void startDBServer()
{
	string inifile = "dbserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int port = ini.getIntValue("DBServer", "port");
	int threadnum = ini.getIntValue("DBServer", "threadnum");
	string strAcceptIps = ini.getStrValue("DBServer", "accept");
	StringVector acceptIps = StringUtility::split(strAcceptIps, "|");

	LOG_INFO("parse %s, port %d, threadnum %d, accept %s\n", inifile.c_str(), port, threadnum, strAcceptIps.c_str());

	if (DB_SERVER.start(port, SOMAXCONN, threadnum, threadnum, 0, 1024, 2048-NET_PACKET_HEAD_LEN, 0, 2000) != ERR_ANSWER_OK)
	{
		LOG_ERROR("Failed to start db server, exit\n");
		exit(EXIT_FAILURE);
	}

	DB_SERVER.setAcceptIps(acceptIps);
}

void stopDBServer()
{
	DB_SERVER.stop();
}

void startLoggerParser()
{
	string inifile = "dbserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int parse = ini.getIntValue("LogParser", "parse");

	LOG_INFO("parse %s, parse %d\n", inifile.c_str(), parse);

	if (parse != 0)
	{
		LOG_PARSER.startParse();
	}
}

