#include "stdafx.h"
#include "CfgData.h"
#include "Tile.h"
#include "MapManager.h"
#include "RobotServer.h"
#include "ClientServer.h"

using namespace Answer;
using namespace std;

void test_findPath()
{
	int32_t mapid = 0;
	int32_t times = 0;
	std::cout << "input mapid:";
	std::cin >> mapid;
	std::cout << "input times:";
	std::cin >> times;
	Map* pMap = MAP_MANAGER.GetMap( mapid );
	if ( NULL == pMap )
	{
		return;
	}

	int64_t t1 = DayTime::tick();
	for ( int32_t i = 0; i < times; ++i )
	{
		Position curTile = pMap->getRandomWalkablePosition();
		Position tarTile = pMap->getRandomWalkablePosition();
		int64_t t2 = DayTime::tick();
		Position findTile = pMap->firstLinePosition( curTile, tarTile );
		int64_t t3 = DayTime::tick();
		int64_t usedtime = t3-t2;
		if ( usedtime > 50 )
		{
			std::cout << i << "\tcurpos " << curTile.x << "," << curTile.y 
				<< "\ttarpos " << tarTile.x << "," << tarTile.y 
				<< "\tfindpos" << findTile.x << "," << findTile.y 
				<< "\tuse time " << usedtime << std::endl;
		}
	}
	int64_t t4 = DayTime::tick();
	std::cout << "times:"<< times << ", used time:" << t4-t1 << ", average time:" << (double)(t4-t1)/times<< std::endl;
}

int main(int argc, char *argv[])
{
	Application::setWorkingDirectory();

	Application::initLogger("robot", LOG_LEVEL_INFO);


	RANDOM.init(true);
	CFG_DATA.init();
	TILE_MANAGER.Init();
	MAP_MANAGER.Init();

	//test_findPath();

	string inifile = "robot.ini";

	Inifile ini;
	ini.parse(inifile);

	string host = ini.getStrValue("GateServer", "host");
	int port = ini.getIntValue("GateServer", "port");

	int32_t nStart = 0;
	int32_t nCount = 0;
	int32_t nDelay = 0;
	//int32_t nMoveDelay = 0;
	std::cout << "输入机器人开始位置：";
	std::cin >> nStart;
	std::cout << "输入机器人数量：";
	std::cin >> nCount;
	std::cout << "输入登陆间隔(ms)(>=100)：";
	std::cin >> nDelay;
	//std::cout << "输入人物移动间隔(ms)(>=1000)：";
	//std::cin >> nMoveDelay;

	if ( nDelay < 100 )
	{
		nDelay = 100;
	}
	int32_t nThreads = nCount / FD_SETSIZE;
	if ( nCount % FD_SETSIZE )
	{
		++nThreads;
	}

	std::cout << "创建线程数：" << nThreads << std::endl;
	CLIENT_SERVER.init( nThreads );

	if ( ROBOT_SERVER.init( InetAddress( host, port ), nStart, nCount, nDelay ) )
	{
		ROBOT_SERVER.startAll();
	}
	
	Application::hookSignal();
	Application::waitSignal();
	Application::unhookSignal();
	return 0;
}
