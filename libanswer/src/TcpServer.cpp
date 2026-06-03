#include "stdafx.h"

#include "NetPacket.h"
#include "TcpAcceptor.h"
#include "TcpConnection.h"
#include "TcpServer.h"

using namespace Answer;

TcpServer::TcpServer(unsigned int netpackSize, unsigned int initNetpacketCount, unsigned int maxNetpacketCount, bool bCompress, bool log /* = false */)
	: m_netpackSize(netpackSize), m_netpackPool(netpackSize, initNetpacketCount, maxNetpacketCount, log), m_acceptor(NULL), m_bCompress(bCompress)
{

}

TcpServer::~TcpServer()
{

}

int TcpServer::start(int port, int backlog, int iothreadnum, int processthreadnum, unsigned int initConnPoolCount, unsigned int maxConnPoolCount, unsigned int packSize, unsigned int initPackCount, unsigned int maxPackCount)
{
	LOG_DEBUG("TcpServer::start with port %d, m_netpackPool %p\n", port, &m_netpackPool);

	m_acceptor = new TcpAcceptor(this, initConnPoolCount, maxConnPoolCount, m_bCompress);
	return m_acceptor->startListen(port, backlog, iothreadnum, processthreadnum, packSize, initPackCount, maxPackCount);
}

void TcpServer::stop()
{
	if (m_acceptor != NULL)
	{
		m_acceptor->stopListen();
	}
}

NetPacket* TcpServer::popNetpacket()
{
	return popNetpacket(m_netpackSize);
}

NetPacket* TcpServer::popNetpacket(unsigned int packsize)
{
	return m_netpackPool.pop(packsize);
}

void TcpServer::replySuccess(Answer::TcpConnection *conn, uint16_t proc, int64_t addon /* = 0 */)
{
	if (conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		packet->writeUInt8(1);
		packet->writeInt64(addon);
		packet->setType(PACK_PROCREPLY);
		packet->setProc(proc);
		packet->setSize(packet->getWOffset());
		conn->sendPacket(packet, true);
	}
}

void TcpServer::replyFailure(Answer::TcpConnection *conn, uint16_t proc, int32_t errcode, int64_t addon /* = 0 */)
{
	if (conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		packet->writeUInt8(0);
		packet->writeInt32(errcode);
		packet->writeInt64(addon);
		packet->setType(PACK_PROCREPLY);
		packet->setProc(proc);
		packet->setSize(packet->getWOffset());
		conn->sendPacket(packet, true);
	}
}

