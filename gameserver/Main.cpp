#include "stdafx.h"

#include "CfgData.h"
#include "CfgGameConn.h"
#include "DBService.h"
#include "GameService.h"
#include "ItemEffect.h"
#include "PoolManager.h"
#include "EquipManager.h"
#include "PetManager.h"
#include "FamilyManager.h"
#include "Timer.h"
#include "WorldBoss.h"
#include "KaiFuHuoDong.h"
#include "EquipBack.h"
#include "UniteServer.h"
#include "GuiGuDaoRen.h"
#include "OpenBeta.h"
#include "OutLinkFestival.h"
#include "CVipClub.h"
#include "CHttpRequest.h"
#include <string>
using namespace Answer;
using namespace std;

// === 2019 infrastructure ===

// GetServerVersion - 2019版本号
string GetServerVersion()
{
	return "2019-06-26";
}

// CheckKey - 密钥验证（简化版）
namespace Answer {
namespace CheckKey {
	bool CheckKeyValid()
	{
		// 简化实现：始终返回true
		// 完整实现需要读取 .key.ini 文件并验证MD5
		return true;
	}
} // namespace CheckKey
} // namespace Answer

// === Function declarations ===
void initDBPool(int32_t line);
void initCfgData(int32_t line);
void initCfgGameConn(int32_t line, int32_t id, CfgGameConnList& dbList, CfgGameConnList& gateList);
void startDBService(int32_t line, CfgGameConnList& p_dbList);
void startGameService(int32_t id, int32_t line, CfgGameConnList& p_gateList);
void stopGameService();

// === main ===
int main(int argc, char *argv[])
{
	// 设置当前工作目录
	Application::setWorkingDirectory();
	// 初始化日志文件
	Application::initLogger("gameserver", LOG_LEVEL_INFO);

	// 打印版本号
	string version = GetServerVersion();
	LOG_INFO("game version = %s\n", version.c_str());

	// 检查参数数量（支持2或3参数，3参数用于跨服）
	if (argc != 2 && argc != 3)
	{
		LOG_ERROR("gameserver with wrong argc = %d, exit\n", argc);
		exit(EXIT_FAILURE);
	}

	// 密钥验证
	if (!CheckKey::CheckKeyValid())
	{
		return 0;
	}

	int32_t line = atoi(argv[1]);
	int32_t id = 0;

	if (line == 9)
	{
		// 跨服模式
		id = atoi(argv[2]);
		LOG_INFO("start crossserver id %d\n", id);
	}
	else
	{
		LOG_INFO("start gameserver line %d\n", line);
	}

	// 初始化随机数
	RANDOM.init(true);

	// 读取配置、初始化数据库连接池
	initDBPool(line);

	// 对象池初始化
	POOL_MANAGER.Init();

	// 游戏配置数据的初始化和从数据库中的数据的读取
	initCfgData(line);
	ITEM_EFFECT.init();
	EQUIP_MANAGER.Init(line);
	PET_MANAGER.Init(line);
	FAMILY_MANAGER.Init(line);
	UNITE_SERVER.Init(line);
	WORLDBOSS.Init(line);
	EQUIP_BACK.Init(line);
	KAI_FU_HUO_DONG.Init(line);
	GUI_GU_DAO_REN.Init(line);
	OPEN_BETA.Init(line);
	OUT_LINK_FESTIVAL.Init(line);
	VIP_CLUB.Init(line);

	// 启动定时器线程
	TIMER.Start();

	// 启动HTTP请求线程
	HTTP_REQUEST.Start();

	// 初始化连接配置（支持多连接/跨服）
	CfgGameConnList dbList;
	CfgGameConnList gateList;
	initCfgGameConn(line, id, dbList, gateList);

	// 启动数据库服务
	startDBService(line, dbList);

	// 启动gate服务，初始化游戏地图
	startGameService(id, line, gateList);

#ifdef _DEBUG
	printf( " gameserver init over!!!\n " );
#endif

	// 等待退出信号
	Application::hookSignal();
	Application::waitSignal();
	Application::unhookSignal();

	// 停止服务
	TIMER.Stop();
	HTTP_REQUEST.Stop();
	GUI_GU_DAO_REN.SaveRecordToDB();
	stopGameService();

	return 0;
}

// === initDBPool (2019版，支持line参数) ===
void initDBPool(int32_t line)
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

	LOG_INFO("parse %s, conn = %d, host = %s, user = %s, password = %s, db = %s, port = %d\n",
		inifile.c_str(), conn, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port);

	int realconn = DBPOOL.init(conn, host, user, password, db, port);

	LOG_INFO("get %d real db conn\n", realconn);

	if (realconn <= 0)
	{
		LOG_ERROR("Failed to init DB Pool, exit\n");
		exit(EXIT_FAILURE);
	}
}

// === initCfgData (2019版，支持line参数) ===
void initCfgData(int32_t line)
{
	string inifile = "gameserver.ini";

	Inifile ini;
	ini.parse(inifile);

	int32_t debug = ini.getIntValue("CfgData", "debug");

	LOG_INFO("parse %s, debug = %d\n", inifile.c_str(), debug);

	CFG_DATA.init(line, debug);

	// 2019新增：HTTP服务器配置
	string httpid = ini.getStrValue("HttpServer", "httpip");
	string httppath = ini.getStrValue("HttpServer", "httppath");
	HTTP_REQUEST.Init(httpid, httppath);
}

// === initCfgGameConn (2019新增，多连接/跨服配置) ===
void initCfgGameConn(int32_t line, int32_t id, CfgGameConnList& dbList, CfgGameConnList& gateList)
{
	if (line == 9)
	{
		// 跨服模式：从数据库读取连接配置
		MySqlDBGuard dbGuard(&DBPOOL);
		char szSQL[4096];
		memset(szSQL, 0, sizeof(szSQL));
		snprintf(szSQL, 0xFFF, "SELECT * FROM `cross_server` WHERE `id`=%d", id);
		MySqlQuery result = dbGuard.query(szSQL);
		while (!result.eof())
		{
			CfgGameConn cfgdb;
			cfgdb.host = result.getStringValue("db_host", "");
			cfgdb.port = result.getIntValue("db_port", 0);
			dbList.push_back(cfgdb);
			LOG_INFO("cfgdb.host %s, cfgdb.port = %d\n", cfgdb.host.c_str(), cfgdb.port);

			CfgGameConn cfgGate;
			cfgGate.host = result.getStringValue("gate_host", "");
			cfgGate.port = result.getIntValue("gate_port", 0);
			gateList.push_back(cfgGate);
			LOG_INFO("cfgGate.host %s, cfgGate.port = %d\n", cfgGate.host.c_str(), cfgGate.port);

			result.nextRow();
		}
	}
	else
	{
		// 普通模式：从ini文件读取
		string inifile = "gameserver.ini";
		Inifile ini;
		ini.parse(inifile);

		CfgGameConn cfgdb;
		cfgdb.host = ini.getStrValue("DBServer", "host");
		cfgdb.port = ini.getIntValue("DBServer", "port");
		dbList.push_back(cfgdb);

		CfgGameConn cfgGate;
		cfgGate.host = ini.getStrValue("GateServer", "host");
		cfgGate.port = ini.getIntValue("GateServer", "port");
		gateList.push_back(cfgGate);
	}
}

// === startDBService (2019版，支持多连接) ===
void startDBService(int32_t line, CfgGameConnList& p_dbList)
{
	int8_t index = 0;
	if (line == 9)
		++index;

	for (CfgGameConnList::iterator iter = p_dbList.begin(); iter != p_dbList.end(); ++iter)
	{
		int32_t port = iter->port;
		string host = iter->host;
		if (!DB_SERVICE.Connect(index, host, port))
		{
			LOG_INFO("startDBService line=%d,dbhost=%s, dbport = %d\n", line, host.c_str(), port);
			exit(EXIT_FAILURE);
		}
		++index;
	}

	DB_SERVICE.Init(line);
}

// === startGameService (2019版，支持多连接和跨服) ===
void startGameService(int32_t id, int32_t line, CfgGameConnList& p_gateList)
{
	GAME_SERVICE.setId(id);
	GAME_SERVICE.setLine(line);

	int8_t index = 0;
	if (line == 9)
		++index;

	for (CfgGameConnList::iterator iter = p_gateList.begin(); iter != p_gateList.end(); ++iter)
	{
		int32_t port = iter->port;
		string host = iter->host;
		if (!GAME_SERVICE.Connect(index, host, port))
		{
			LOG_INFO("startGameService line=%d,gatehost=%s, gateport = %d\n", line, host.c_str(), port);
			exit(EXIT_FAILURE);
		}
		++index;
	}

	// 发送初始连接消息到gate
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
