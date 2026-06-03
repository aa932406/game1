#include "stdafx.h"

#include "CfgData.h"
#include "DBService.h"
#include "GameService.h"
#include "ItemEffect.h"
#include "PoolManager.h"
#include "EquipManager.h"
#include "PetManager.h"
#include "PoolManager.h"
#include "FamilyManager.h"
#include "Timer.h"
#include "WorldBoss.h"
#include "KaiFuHuoDong.h"
#include <string>
using namespace Answer;
using namespace std;

void initDBPool();
void initCfgData();

void startDBService();
void startGameService(int32_t line);
void stopGameService();
int main(int argc, char *argv[])
{
	 //获取当前目录
	Application::setWorkingDirectory();
	//创建日志文件
	Application::initLogger("gameserver", LOG_LEVEL_INFO);
	
	//参数错误退出
	if (argc != 2)
	{
		LOG_ERROR("gameserver with wrong argc = %d, exit\n", argc);
		exit(EXIT_FAILURE);
	}
	int32_t line = atoi(argv[1]);
	LOG_INFO("start gameserver line %d\n", line);

	//设置内存益处监视
	RANDOM.init(true);
	
	//读取配置并创建数据库连接池
	initDBPool();

	// 对象池初始化
	POOL_MANAGER.Init();
	
	//游戏中数据的初试化，对数据库中的数据的读取
	initCfgData();
	ITEM_EFFECT.init();
	EQUIP_MANAGER.Init();
	PET_MANAGER.Init();
	FAMILY_MANAGER.Init();
	WORLDBOSS.Init();
	KAI_FU_HUO_DONG.Init();

	// 启动计时器线程
	TIMER.Start();

	//启动连接数据库服务器 启动一条线程 
	startDBService();
	//启动连接gate服务器 并初始化游戏地图数据 启动一条线程
	startGameService(line);


#ifdef _DEBUG
	printf( " gameserver init over!!!\n " );
#endif

	//
	Application::hookSignal();
	Application::waitSignal();
	Application::unhookSignal();
	TIMER.Stop();
	KAI_FU_HUO_DONG.SaveData();
	stopGameService();
	return 0;
}

void initDBPool()
{
	string inifile = "database.ini";

	Inifile ini;
	ini.parse(inifile);

	int conn = ini.getIntValue("GameServer", "conn");

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

void initCfgData()
{
	string inifile = "gameserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int32_t equip = ini.getIntValue("CfgData", "equip");
	int32_t pet = ini.getIntValue("CfgData", "pet");
	int32_t debug = ini.getIntValue("CfgData", "debug");

	LOG_INFO("parse %s, equip = %d, pet = %d, debug = %d\n", inifile.c_str(), equip, pet, debug);

	CFG_DATA.init(equip, pet,equip, debug);
}

void startDBService()
{
	string inifile = "gameserver.ini";

	Inifile ini;
	ini.parse(inifile);

	string host = ini.getStrValue("DBServer", "host");
	int port = ini.getIntValue("DBServer", "port");

	LOG_INFO("parse %s, host = %s, port = %d\n", inifile.c_str(), host.c_str(), port);
	//连接logerver服务端
	if (!DB_SERVICE.connect(InetAddress(host, port)))
	{
		exit(EXIT_FAILURE);
	}

	DB_SERVICE.start();

	//连接DBServer成功发送一条消息
	NetPacket *packet = DB_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeUTF8(DB_SERVICE.getName());
	packet->setType(PACK_PROC);
	packet->setProc(IM_DB_GAME_SERVICE_CONNECT);
	packet->setSize(packet->getWOffset());
	DB_SERVICE.sendPacket(packet);
}

//Tcp协议 连接GeteServer内部客户端
void startGameService(int32_t line)
{
	string inifile = "gameserver.ini";

	Inifile ini;
	ini.parse(inifile);

	string host = ini.getStrValue("GateServer", "host");
	int port = ini.getIntValue("GateServer", "port");

	LOG_INFO("parse %s, host = %s, port = %d\n", inifile.c_str(), host.c_str(), port);
	//连接到gate服务器上
	if (!GAME_SERVICE.connect(InetAddress(host, port)))
	{
		exit(EXIT_FAILURE);
	}

	GAME_SERVICE.start();
	//发送消息到gate服务器上创建一个连接
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_GAME_SERVICE_CONNECT);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(line);
	packet->writeUTF8(GAME_SERVICE.getName());
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);

	GAME_SERVICE.startGame(line);
}

void stopGameService()
{
	GAME_SERVICE.stopGame();
	DayTime::sleep(5*1000);
}
