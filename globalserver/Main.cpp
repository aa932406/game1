#include "stdafx.h"

#include "CfgData.h"
#include "CharacterService.h"
#include "LoginService.h"
#include "SocialService.h"
#include "PetManager.h"
#include "PlayerManager.h"
#include "FamilyManager.h"
#include "RankManager.h"
#include "AuctionManager.h"
#include "HallOfFame.h"

#include "GlobalJueWei.h"
#include "ZSZZDungeon.h"
#include "GlobalRecord.h"
#include <string>
#include <iostream>

using namespace Answer;
using namespace std;

void initDBPool();
void startSocialService();
void startCharacterService();
void startLoginService();
void startKingDomService();
void SaveData();

int main(int argc, char *argv[])
{
	Application::setWorkingDirectory();

	Application::initLogger("globalserver", LOG_LEVEL_INFO);
	
	RANDOM.init(true);

	initDBPool();

	CFG_DATA.init();

	PLAYER_MANAGER.Init();

	PET_MANAGER.Init();

	FAMILY_MANAGER.Init();
	RANK_MANAGER.Init();

	AUCTION_MANAGER.Init();

	HALL_OF_FAME.Init();

	GLOBAL_JUE_WEI.Init();
	ZSZZ_DUNGEON_RANK.Init();
	GLOBAL_RECORD.Init();
	//工会服务器
	startSocialService();
	//角色服务器
	startCharacterService();
	//登陆服务器
	startLoginService();

	//国家服务器

#ifdef _DEBUG
	printf( " globalserver init over!!!\n " );
#endif
	
	Application::hookSignal();
	Application::waitSignal();
	Application::unhookSignal();
	SaveData();
	return 0;
}

void initDBPool()
{
	string inifile = "database.ini";

	Inifile ini;
	ini.parse(inifile);

	int conn = ini.getIntValue("GlobalServer", "conn");

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

//角色请求内部客户端连接 到gateServer
void startCharacterService()
{
	string inifile = "globalserver.ini";

	Inifile ini;
	ini.parse(inifile);

	string host = ini.getStrValue("GateServer", "host");
	int port = ini.getIntValue("GateServer", "port");

	inifile = "version.ini";
	ini.parse(inifile);
	int version = ini.getIntValue("Version","flag");

	LOG_INFO("parse %s, host = %s, port = %d\n", inifile.c_str(), host.c_str(), port);

	if (!CHARACTER_SERVICE.init(version))
	{
		exit(EXIT_FAILURE);
	}

	if (!CHARACTER_SERVICE.connect(InetAddress(host, port)))
	{
		exit(EXIT_FAILURE);
	}

	CHARACTER_SERVICE.start();

	NetPacket *packet = CHARACTER_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		exit(EXIT_FAILURE);
	}
	packet->writeUTF8(CHARACTER_SERVICE.getName());
	packet->setType(PACK_PROC);
	packet->setProc(IM_CHARACTER_SERVICE_CONNECT);
	packet->setSize(packet->getWOffset());
	CHARACTER_SERVICE.sendPacket(packet);
}

//内部客户端连接 到gateServer
void startSocialService()
{
	string inifile = "globalserver.ini";

	Inifile ini;
	ini.parse(inifile);
	string host = ini.getStrValue("GateServer", "host");
	int port = ini.getIntValue("GateServer", "port");

	LOG_INFO("parse %s, host = %s, port = %d\n", inifile.c_str(), host.c_str(), port);

	if (!SOCIAL_SERVICE.connect(InetAddress(host, port)))
	{
		exit(EXIT_FAILURE);
	}

	SOCIAL_SERVICE.start();

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		exit(EXIT_FAILURE);
	}
	packet->writeUTF8(SOCIAL_SERVICE.getName());
	packet->setType(PACK_PROC);
	packet->setProc(IM_SOCIAL_SERVICE_CONNECT);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacket(packet);

	SOCIAL_SERVICE.startSocial();
}

//登陆服务请求内部客户端连接 到gateServer
void startLoginService()
{
	string inifile = "globalserver.ini";

	Inifile ini;
	ini.parse(inifile);

	string host = ini.getStrValue("GateServer", "host");
	int port = ini.getIntValue("GateServer", "port");
	int login = ini.getIntValue("GateServer", "login");

	LOG_INFO("parse %s, host = %s, port = %d, login = %d\n", inifile.c_str(), host.c_str(), port, login);

	if (login)
	{
		if (!LOGIN_SERVER.connect(InetAddress(host, port)))
		{
			exit(EXIT_FAILURE);
		}

		LOGIN_SERVER.start();

		NetPacket *packet = LOGIN_SERVER.popNetpacket();
		if (NULL == packet)
		{
			exit(EXIT_FAILURE);
		}
		packet->writeUTF8(LOGIN_SERVER.getName());
		packet->setType(PACK_PROC);
		packet->setProc(IM_LOGIN_SERVICE_CONNECT);
		packet->setSize(packet->getWOffset());
		LOGIN_SERVER.sendPacket(packet);
	}
}

void SaveData()
{
	GLOBAL_RECORD.SaveRecordToDB();
}