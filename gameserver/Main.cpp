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
#include "EquipBack.h"
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
	 //��ȡ��ǰĿ¼
	Application::setWorkingDirectory();
	//������־�ļ�
	Application::initLogger("gameserver", LOG_LEVEL_INFO);
	
	//���������˳�
	if (argc != 2)
	{
		LOG_ERROR("gameserver with wrong argc = %d, exit\n", argc);
		exit(EXIT_FAILURE);
	}
	int32_t line = atoi(argv[1]);
	LOG_INFO("start gameserver line %d\n", line);

	//�����ڴ��洦����
	RANDOM.init(true);
	
	//��ȡ���ò��������ݿ����ӳ�
	initDBPool();

	// ����س�ʼ��
	POOL_MANAGER.Init();
	
	//��Ϸ�����ݵĳ��Ի��������ݿ��е����ݵĶ�ȡ
	initCfgData();
	ITEM_EFFECT.init();
	EQUIP_MANAGER.Init();
	PET_MANAGER.Init();
	FAMILY_MANAGER.Init();
	WORLDBOSS.Init();
	KAI_FU_HUO_DONG.Init();
	KIA_FU_RECHARGE.Init();
	EQUIP_BACK.Init();

	// ������ʱ���߳�
	TIMER.Start();

	//�����������ݿ������ ����һ���߳� 
	startDBService();
	//��������gate������ ����ʼ����Ϸ��ͼ���� ����һ���߳�
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
	//����logerver�����
	if (!DB_SERVICE.connect(InetAddress(host, port)))
	{
		exit(EXIT_FAILURE);
	}

	DB_SERVICE.start();

	//����DBServer�ɹ�����һ����Ϣ
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

//TcpЭ�� ����GeteServer�ڲ��ͻ���
void startGameService(int32_t line)
{
	string inifile = "gameserver.ini";

	Inifile ini;
	ini.parse(inifile);

	string host = ini.getStrValue("GateServer", "host");
	int port = ini.getIntValue("GateServer", "port");

	LOG_INFO("parse %s, host = %s, port = %d\n", inifile.c_str(), host.c_str(), port);
	//���ӵ�gate��������
	if (!GAME_SERVICE.connect(InetAddress(host, port)))
	{
		exit(EXIT_FAILURE);
	}

	GAME_SERVICE.start();
	//������Ϣ��gate�������ϴ���һ������
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
