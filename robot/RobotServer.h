#ifndef __TPOC_ROBOT_SERVER_H__
#define __TPOC_ROBOT_SERVER_H__

#include "InetAddress.h"
#include "NetPacket.h"
#include "NetPacketPool.h"
#include "SafeQueue.h"
#include "Thread.h"
#include "Robot.h"
#include "ClientServer.h"

#include <string>
using namespace Answer;

class RobotServer
	: public Thread
{
public:
	RobotServer();
	virtual ~RobotServer();

protected:
	virtual void run();

public:
	bool init( const InetAddress& address, int32_t nStart, int32_t nCount, int32_t nDelay );
	void startAll();

private:
	void checkWaitList( int64_t curTick );
	//void doNetWork();
	void updateAll( int64_t curTick );

private:
	typedef list<CRobot*> RobotList;
	typedef Answer::SafeQueue<CRobot*> RobotQueue;
	bool		m_brun;
	RobotList	m_robots;
	RobotQueue	m_waitList;

	InetAddress	m_address;
	int64_t		m_delay;
	int64_t		m_lastConnectTick;
};

#define ROBOT_SERVER Answer::Singleton<RobotServer>::instance()

#endif	//__TPOC_ROBOT_SERVER_H__
