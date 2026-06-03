#include "stdafx.h"

#include "GateLogger.h"
#include "GateServer.h"
#include "ServiceServer.h"
#include "PHPServer.h"

#include <string>

using namespace Answer;
using namespace std;

void initDBPool();
void stopPHPServer();
void startPHPServer();
void startGateServer();
void stopGateServer();
void startGateLogger();
void startServiceServer();
void stopServiceServer();

int main(int argc, char *argv[])
{
	Application::setWorkingDirectory();

	Application::initLogger("gateserver", LOG_LEVEL_INFO);

	string inifile = "gateserver.ini";
	Inifile ini;
	ini.parse(inifile);
	int flag = ini.getIntValue("PHPServer", "flag");

	initDBPool();

	startServiceServer();

	startGateServer();

	startGateLogger();

	if(flag ==1)startPHPServer();

#ifdef _DEBUG
	printf( " gateserver init over!!!\n " );
#endif

	Application::hookSignal();

	Application::waitSignal();

	Application::unhookSignal();

	if(flag ==1)stopPHPServer();

	stopGateServer();

	stopServiceServer();

	return 0;
}

void initDBPool()
{
	string inifile = "database.ini";

	Inifile ini;
	ini.parse(inifile);

	int conn = ini.getIntValue("GateServer", "conn");

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
//服务端的gateserver和网页客户端相连
void startGateServer()
{
	string inifile = "gateserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int port = ini.getIntValue("GateServer", "port");
	int threadnum = ini.getIntValue("GateServer", "threadnum");

	LOG_INFO("parse %s, port %d, threadnum %d\n", inifile.c_str(), port, threadnum);
	//内部服务端 
	if (GATE_SERVER.start(port, SOMAXCONN, threadnum, threadnum, 1024, 2048, 2048-NET_PACKET_HEAD_LEN, 5000, 10000) != ERR_ANSWER_OK)
	{
		LOG_ERROR("Failed to start gate server, exit\n");
		exit(EXIT_FAILURE);
	}
}

void startPHPServer()
{
	string inifile = "gateserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int port = ini.getIntValue("PHPServer", "port");
	int threadnum = ini.getIntValue("PHPServer", "threadnum");

	LOG_INFO("parse %s, port %d, threadnum %d\n", inifile.c_str(), port, threadnum);
	//内部服务端 
	if (PHP_SERVER.start(port, SOMAXCONN, threadnum, threadnum, 1024, 2048, 2048-NET_PACKET_HEAD_LEN, 5000, 10000) != ERR_ANSWER_OK)
	{
		LOG_ERROR("Failed to start gate server, exit\n");
		exit(EXIT_FAILURE);
	}
}
void stopPHPServer()
{
	PHP_SERVER.stop();
}
void stopGateServer()
{
	GATE_SERVER.stop();
}

void startGateLogger()
{
	string inifile = "gateserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int log = ini.getIntValue("GateLogger", "log");

	LOG_INFO("parse %s, log %d\n", inifile.c_str(), log);

	if (log != 0)
	{
		GATE_LOGGER.startLogger();
	}
}
//内部服务端 
void startServiceServer()
{
	string inifile = "gateserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int port = ini.getIntValue("ServiceServer", "port");
	int threadnum = ini.getIntValue("ServiceServer", "threadnum");
	string strAcceptIps = ini.getStrValue("ServiceServer", "accept");
	StringVector acceptIps = StringUtility::split(strAcceptIps, "|");

	LOG_INFO("parse %s, port %d, threadnum %d, accept %s\n", inifile.c_str(), port, threadnum, strAcceptIps.c_str());

	if (SERVICE_SERVER.start(port, SOMAXCONN, threadnum, threadnum, 4, 8, 8192-NET_PACKET_HEAD_LEN, 5000, 10000) != ERR_ANSWER_OK)
	{
		LOG_ERROR("Failed to start service server, exit\n");
		exit(EXIT_FAILURE);
	}

	SERVICE_SERVER.setAcceptIps(acceptIps);
}

void stopServiceServer()
{
	SERVICE_SERVER.logServerProcs();
	SERVICE_SERVER.stop();
}

