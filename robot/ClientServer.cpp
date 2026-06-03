#include "stdafx.h"

#include "Logger.h"
#include "SockOpts.h"
#include "ClientServer.h"

using namespace Answer;
using namespace std;

ClientServer::ClientServer()
	:m_bufferSize(8192), m_bufferPool(8192, 5000, 10000), m_nSize(4),m_curindex( 0 )
{
	m_conns = NULL;
}

//ClientServer::ClientServer(int recvBufferSize, int sendBufferSize, unsigned int bufferSize, unsigned int initCount, unsigned int maxCount )
//	: m_bufferSize(bufferSize), m_bufferPool(bufferSize, initCount, maxCount)
//{
//}

ClientServer::~ClientServer()
{
	if ( m_conns != NULL )
	{
		delete[] m_conns;
		m_conns = NULL;
	}
}

//void ClientServer::run()
//{
//}

NetPacket* ClientServer::popNetpacket()
{
	return popNetpacket(m_bufferSize);
}

NetPacket* ClientServer::popNetpacket(unsigned int buffersize)
{
	return m_bufferPool.pop(buffersize);
}

void ClientServer::init( int32_t nThreads )
{
	m_nSize = nThreads;
	m_conns = new MultiConnection[m_nSize];
	for ( int32_t i = 0; i < m_nSize; ++i )
	{
		m_conns[i].start();
	}
}

void ClientServer::addConn( ClientConnection* pConn )
{
	if ( pConn != NULL )
	{
		m_conns[m_curindex].add( pConn, MASK_READ );
		pConn->setindex( m_curindex );
		++m_curindex;
		if ( m_curindex >= m_nSize )
		{
			m_curindex -= m_nSize;
		}
	}
}

void ClientServer::removeConn( ClientConnection* pConn )
{
	if ( pConn != NULL )
	{
		m_conns[pConn->getindex()].remove( pConn );
	}
}
