#include "stdafx.h"

#include "Logger.h"
#include "SockOpts.h"
#include "RobotServer.h"
#include "FileDef.h"
#include "ClientServer.h"

#define FILE_ROBOT	"./robot.txt"					// 机器人配置表

using namespace Answer;
using namespace std;

RobotServer::RobotServer()
:m_brun( false ), m_lastConnectTick( 0 )
{

}

RobotServer::~RobotServer()
{
}

void RobotServer::run()
{
	int64_t curTick = 0;
	while( m_brun )
	{
		curTick = DayTime::tick();
		checkWaitList( curTick );
		//doNetWork();
		updateAll( curTick );

		int32_t usedTime = static_cast<int32_t>( DayTime::tick() - curTick );
		if ( usedTime < 50 )
		{
			DayTime::sleep( 50-usedTime );
		}

		//printf( "RobotServer::run() use time ---%d---\n",  );
	}
}

void RobotServer::checkWaitList( int64_t curTick )
{
	if ( curTick - m_lastConnectTick < m_delay )
	{
		return;
	}
	m_lastConnectTick = curTick;

	CRobot* pRobot = m_waitList.pop();
	if ( NULL == pRobot )
	{
		return;
	}

	if ( !pRobot->connect( m_address ) )
	{
		printf( "robot connect fail!!! passport=%s\n", pRobot->getPassPort().c_str() );
		return;
	}

	pRobot->sendStartPacket();
	m_robots.push_back( pRobot );

	CLIENT_SERVER.addConn( pRobot );
}

//void RobotServer::doNetWork()
//{
//	RobotList::iterator iter = m_robots.begin();
//	RobotList::iterator eiter = m_robots.end();
//	for ( ; iter != eiter; ++iter )
//	{
//		CRobot* pRobot = *iter;
//		if ( pRobot != NULL && pRobot->isconnected() )
//		{
//			pRobot->network();
//		}
//	}
//}

void RobotServer::updateAll( int64_t curTick )
{
	RobotList::iterator iter = m_robots.begin();
	RobotList::iterator eiter = m_robots.end();
	for ( ; iter != eiter; ++iter )
	{
		CRobot* pRobot = *iter;
		if ( pRobot != NULL )
		{
			pRobot->update( curTick );
		}
	}
}

bool RobotServer::init( const InetAddress& address, int32_t nStart, int32_t nCount, int32_t nDelay )
{
	m_delay = nDelay;
	m_address = address;

	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_ROBOT );
	if ( ret == false )
	{
		printf("open FILE_ROBOT 失败,请检查文件名大小写!!!\n");
		return false;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return false;
	}

	int32_t nMax = nStart + nCount;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int32_t order	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		if ( order < nStart || order >= nMax )
		{
			continue;
		}
		string	pass	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		int32_t	sid		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		string	name	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		int32_t	sex		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t	job		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t	head	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t mapid	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		CRobot* pRobot = new CRobot( pass, sid, name, sex, job, head );
		if ( NULL == pRobot )
		{
			printf( "create robot fail!!!\n" );
			return false;
		}

		//if ( !pRobot->connect( address ) )
		//{
		//	printf( "robot connect fail!!! passport=%s\n", pRobot->getPassPort().c_str() );
		//	return false;
		//}

		//pRobot->setTargetMap( mapid, nMoveDelay );
		m_waitList.push( pRobot );
	}

	return true;
}

void RobotServer::startAll()
{
	m_brun = true;
	start();
}
