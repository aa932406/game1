#ifndef __TPOC_CLIENT_SERVER_H__
#define __TPOC_CLIENT_SERVER_H__

#include "InetAddress.h"
#include "NetPacket.h"
#include "NetPacketPool.h"
#include "SafeQueue.h"
#include "Thread.h"
#include "MultiConnection.h"

#include <string>
using namespace Answer;

class ClientServer
{
public:
	ClientServer();
	//ClientServer( int recvBufferSize, int sendBufferSize, unsigned int bufferSize, unsigned int initCount, unsigned int maxCount );
	virtual ~ClientServer();

//protected:
//	virtual void run();

public:
	Answer::NetPacket* popNetpacket();
	Answer::NetPacket* popNetpacket(unsigned int buffersize);

public:
	void init( int32_t nThreads );
	void addConn( ClientConnection* pConn );
	void removeConn( ClientConnection* pConn );

private:
	unsigned int		m_bufferSize;
	NetPacketPool		m_bufferPool;
	MultiConnection*	m_conns;
	int32_t				m_nSize;
	int32_t				m_curindex;
};

#define CLIENT_SERVER Answer::Singleton<ClientServer>::instance()

#endif	//__TPOC_CLIENT_SERVER_H__
