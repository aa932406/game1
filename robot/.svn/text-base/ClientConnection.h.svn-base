#ifndef __TPOC_CLIENT_CONNECTION_H__
#define __TPOC_CLIENT_CONNECTION_H__

#include "InetAddress.h"
#include "NetPacket.h"
#include "NetPacketPool.h"
#include "SafeQueue.h"
#include "Thread.h"

#include <string>
using namespace Answer;

class ClientConnection
{
public:
	ClientConnection( int recvBufferSize, int sendBufferSize, const std::string& name );
	virtual ~ClientConnection();

protected:
	virtual void onNetPacket(Answer::NetPacket *inPacket) = 0;
	virtual void onDisconnect() = 0;

public:
	void			reset();
	void			network();
	bool			isconnected() const;
	bool			connect(const Answer::InetAddress &serverAddr);
	void			sendPacket(Answer::NetPacket *packet);
	socket_t		getfd() const;
	int				getindex() const;
	void			setindex( int index );

	bool			needSend();
	int				onRecv();
	int				onSend();
	void			close();

private:
	void			parissRecvBuffer();
	void			decodeRecvBuffer();
	void			encodeSendBuffer();

	int				setnonblock(socket_t fd);
	int				setnodelay(socket_t fd);
	int				setkeepalive(socket_t fd, int idleseconds);

	void			doubleRecvParissBuff( int32_t needsize );

protected:
	std::string		m_name;

private:
	socket_t		m_fd;
	InetAddress		m_serverAddr;
	bool			m_connected;

	int				m_index;

	int				m_recvParissBufferSize;
	char*			m_recvParissBuffer;
	int				m_recvParissOffset;
	NetPacket*		m_packet;
	int				m_decodeState;

	char*			m_recvBuffer;
	int				m_recvBufferSize;
	int				m_recvOffset;

	char*			m_recvCompressBuffer;

	NetPacketList	m_sendList;
	int				m_parseLen;
	int				m_sendBufferSize;
	char*			m_sendBuffer;
	int				m_sendLen;
	int				m_sendCursor;
};

#endif	//__TPOC_CLIENT_CONNECTION_H__
