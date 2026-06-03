#include "stdafx.h"

#include "Logger.h"
#include "SockOpts.h"
#include "ClientConnection.h"
#include "RobotServer.h"
#include "ClientServer.h"

using namespace Answer;
using namespace std;

ClientConnection::ClientConnection( int recvBufferSize, int sendBufferSize, const std::string& name )
	: m_fd(INVALID_SOCKET), m_connected(false), m_recvBufferSize(recvBufferSize), m_packet(NULL), m_sendBufferSize(sendBufferSize),m_recvParissBufferSize(recvBufferSize*2), m_name( name ), m_index( 0 )
{
	m_recvBuffer			= new char[m_recvBufferSize];
	m_sendBuffer			= new char[m_sendBufferSize];
	m_recvParissBuffer		= new char[m_recvParissBufferSize];
	m_recvCompressBuffer	= new char[m_recvBufferSize];

	reset();
}

ClientConnection::~ClientConnection()
{
	delete[] m_recvBuffer;
	delete[] m_sendBuffer;
	delete[] m_recvParissBuffer;
}

socket_t ClientConnection::getfd() const
{
	return m_fd;
}

int	ClientConnection::getindex() const
{
	return m_index;
}

void ClientConnection::setindex( int index )
{
	m_index = index;
}

//void ClientConnection::onDisconnect()
//{
//	close();
//}

void ClientConnection::network()
{
	if (!m_connected)
	{
		LOG_ERROR("ClientConnection::network() enter with m_connected = false, return\n");
		return;
	}

	//int64_t tick1 = DayTime::tick();

	fd_set rfds;
	fd_set wfds;

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);

	FD_SET(m_fd, &rfds);
	if (needSend())
	{
		FD_SET(m_fd, &wfds);
	}

	timeval timeout = {};
	timeout.tv_sec = 0;
	//timeout.tv_usec = 50*1000;	// 延迟时间，即使没有拿到东西也会有延迟
	timeout.tv_usec = 0;

	int err = select((int)(m_fd+1), &rfds, &wfds, NULL, &timeout);

	//int64_t tick2 = DayTime::tick();
	//printf( "ClientConnection::network() name=%s, select time=%d\n", m_name.c_str(), tick2-tick1 );

	if (err > 0)
	{
		if (FD_ISSET(m_fd, &rfds))
		{
			if (onRecv() == SOCKET_ERROR)
			{
				LOG_ERROR("ClientConnection %s network onRecv return SOCKET_ERROR\n", m_name.c_str() );
				close();
			}
		}

		//int64_t tick3 = DayTime::tick();
		//printf( "ClientConnection::network() name=%s, recv time=%d\n", m_name.c_str(), tick3-tick2 );

		if (FD_ISSET(m_fd, &wfds))
		{
			if (onSend() == SOCKET_ERROR)
			{
				LOG_ERROR("ClientConnection %s network onSend return SOCKET_ERROR\n", m_name.c_str() );
				close();
			}
		}

		//int64_t tick4 = DayTime::tick();
		//printf( "ClientConnection::network() name=%s, send time=%d\n", m_name.c_str(), tick4-tick3 );
	}
	else if (err == 0)
	{
		return;
	}
	else
	{
		int error = WSAGetLastError();
		LOG_ERROR("ClientConnection %s network select return %d, errno = %d\n", m_name.c_str(), err, error);
		close();
	}
}

void ClientConnection::close()
{
	::closesocket(m_fd);
	m_fd = INVALID_SOCKET;
	m_connected = false;
	onDisconnect();
}

void ClientConnection::reset()
{
	if (m_fd != INVALID_SOCKET)
	{
		close();
	}

	m_connected = false;

	bzero(m_recvParissBuffer, sizeof(char)*m_recvParissBufferSize);
	m_recvParissOffset = 0;

	bzero(m_recvBuffer, sizeof(char)*m_recvBufferSize);
	m_recvOffset = 0;

	if (m_packet != NULL)
	{
		m_packet->destroy();
	}
	m_decodeState = DECODE_HEAD;

	NetPacket *packet = NULL;
	while ((packet = m_sendList.pop()) != NULL)
	{
		packet->destroy();
	}
	m_parseLen = 0;

	bzero(m_sendBuffer, sizeof(char)*m_sendBufferSize);
	m_sendLen = 0;
	m_sendCursor = 0;
}

bool ClientConnection::isconnected() const
{
	return m_connected;
}

bool ClientConnection::connect(const InetAddress &serverAddr)
{
	if (m_fd != INVALID_SOCKET || m_connected)
	{
		LOG_ERROR("ClientConnection::connect with m_fd %d, m_connected %d return false\n", m_fd, (int)m_connected);
		return false;
	}

	m_serverAddr = serverAddr;

	m_fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (m_fd == INVALID_SOCKET)
	{
		LOG_ERROR("ClientConnection::connect socket return INVALID_SOCKET, return false\n");
		return false;
	}

	int err = ::connect(m_fd, (const sockaddr*)(&(m_serverAddr.getSockAddr())), m_serverAddr.getAddrLen());
	if (err	== SOCKET_ERROR)
	{
		LOG_ERROR("ClientConnection::connect connect return SOCKET_ERROR, errno %d\n", WSAGetLastError());
		close();
		return false;
	}

	char szPolicy[23] = {};
	err = ::send(m_fd, szPolicy, sizeof(szPolicy), 0);
	if (err != sizeof(szPolicy))
	{
		LOG_ERROR("ClientConnection::connect send return %d\n", err);
		close();
		return false;
	}
	
	setnonblock(m_fd);
	setnodelay(m_fd);
	setkeepalive(m_fd, 300);

	m_connected = true;
	return true;
}

void ClientConnection::sendPacket(NetPacket *packet)
{
	if (packet != NULL)
	{
		if (m_connected)
		{
			packet->encodeHeadInfo();
			m_sendList.push(packet);
			//printf( "ClientConnection::sendPacket() name='%s', buffsize=%d, \tproc=%d\t\n", m_name.c_str(), m_sendList.size(), packet->getProc() );
		}
		else
		{
			packet->destroy();
		}
	}
}

bool ClientConnection::needSend()
{
	return m_sendList.size() > 0 || m_sendCursor < m_sendLen;
}

int ClientConnection::onRecv()
{
	int error = ::recv(m_fd, m_recvBuffer+m_recvOffset, m_recvBufferSize-m_recvOffset, 0);
	if (error > 0)
	{
		m_recvOffset += error;
		parissRecvBuffer();

		//if (m_recvParissOffset > m_recvParissBufferSize)
		//{
		//	LOG_INFO("ClientConnection to ip %s m_recvParissOffset %d > m_recvParissBufferSize %d\n", m_serverAddr.getIP().c_str(), m_recvParissOffset, m_recvParissBufferSize);
		//	error = SOCKET_ERROR;
		//}
		//else
		//{
		//	decodeRecvBuffer();
		//}
	}
	else if (error == 0)
	{
		LOG_INFO("ClientConnection %s onRecv recv return 0\n", m_name.c_str() );
		error = SOCKET_ERROR;
	}
	else
	{
		int err = WSAGetLastError();
		LOG_INFO("ClientConnection %s onRecv recv return %d, errno = %d\n", m_name.c_str(), error, err);
		if (err == WSAEWOULDBLOCK)
		{
			error = 0;
		}
	}

	return error;
}

int ClientConnection::onSend()
{
	if (m_sendLen == 0)
	{
		encodeSendBuffer();
		if (m_sendLen == 0)
		{
			LOG_ERROR("ClientConnection::onSend m_sendLen == 0 after encodeSendBuffer\n");
		}
	}

	int error = ::send(m_fd, m_sendBuffer+m_sendCursor, m_sendLen-m_sendCursor, 0);
	if (error > 0)
	{
		m_sendCursor += error;
		if (m_sendCursor == m_sendLen)
		{
			m_sendLen = 0;
			m_sendCursor = 0;
		}
		else if (m_sendCursor > m_sendLen)
		{
			LOG_INFO("ClientConnection to ip %s m_sendCursor %d > m_sendLen %d\n", m_serverAddr.getIP().c_str(), m_sendCursor, m_sendLen);
			error = SOCKET_ERROR;
		}
	}
	else if (error == 0)
	{
		LOG_INFO("ClientConnection %s onSend send return 0\n", m_name.c_str());
		error = SOCKET_ERROR;
	}
	else
	{
		int err = WSAGetLastError();
		LOG_INFO("ClientConnection %s onSend send return %d, errno = %d\n", m_name.c_str(), error, err);
		if (err == WSAEWOULDBLOCK)
		{
			error = 0;
		}
	}

	return error;
}

void ClientConnection::parissRecvBuffer()
{
	int32_t offset = 0;
	uint16_t buffsize = 0;
	uint16_t realsize = 0;

	while ( m_recvOffset >= offset + 4+NET_PACKET_HEAD_LEN )
	{
		buffsize = *((uint16_t*)(m_recvBuffer+offset));
		realsize = *((uint16_t*)(m_recvBuffer+offset+2));
		if ( buffsize < 4+NET_PACKET_HEAD_LEN || offset + buffsize > m_recvOffset )
		{
			//LOG_INFO( "ClientConnection::parissRecvBuffer() out of range name=%s, buffsize=%d, offset=%d, recvOffset=%d\n", m_name.c_str(), buffsize, offset, m_recvOffset );
			//printf( "ClientConnection::parissRecvBuffer() out of range name=%s, buffsize=%d, offset=%d, recvOffset=%d\n", m_name.c_str(), buffsize, offset, m_recvOffset );
			break;
		}

		offset += 4;
		buffsize-=4;

		if ( realsize > 0 )	// 大包，服务器压缩过了
		{
			int compressLen = Zip::uncompressbuf(m_recvCompressBuffer, realsize, m_recvBuffer+offset, buffsize);
			if ( compressLen == realsize )
			{
				if ( compressLen + m_recvParissOffset > m_recvParissBufferSize )
				{
					doubleRecvParissBuff( compressLen + m_recvParissOffset );
				}
				memcpy( m_recvParissBuffer+m_recvParissOffset, m_recvCompressBuffer, compressLen );
				m_recvParissOffset += compressLen;
				decodeRecvBuffer();
			}
		}
		else
		{
			if ( buffsize + m_recvParissOffset > m_recvParissBufferSize )
			{
				doubleRecvParissBuff( buffsize + m_recvParissOffset );
			}
			memcpy( m_recvParissBuffer+m_recvParissOffset, m_recvBuffer+offset, buffsize );
			m_recvParissOffset += buffsize;
			decodeRecvBuffer();
		}

		offset += buffsize;
	}

	if ( offset < m_recvOffset )
	{
		memmove( m_recvBuffer, m_recvBuffer+offset, m_recvOffset-offset );
		//LOG_INFO( "ClientConnection::parissRecvBuffer() not buff end offset=%d, m_recvOffset=%d\n", offset, m_recvOffset );
		//printf( "ClientConnection::parissRecvBuffer() not buff end offset=%d, m_recvOffset=%d\n", offset, m_recvOffset );
	}

	m_recvOffset -= offset;
}

void ClientConnection::doubleRecvParissBuff( int32_t needsize )
{
	int32_t newsize = m_recvParissBufferSize * 2;
	while ( needsize > newsize )
	{
		newsize += m_recvParissBufferSize;
	}

	char* tBuff = m_recvParissBuffer;
	m_recvParissBuffer = new char[newsize];
	memcpy( m_recvParissBuffer, tBuff, m_recvParissBufferSize );
	delete[] tBuff;

	printf( "Double RecvParissBuff name=%s, needsize=%d, oldsize=%d, newsize=%d\n", m_name.c_str(), needsize, m_recvParissBufferSize, newsize );
	LOG_ERROR( "ClientConnection::doubleRecvParissBuff() name=%s, needsize=%d, oldsize=%d, newsize=%d\n", m_name.c_str(), needsize, m_recvParissBufferSize, newsize  );
	m_recvParissBufferSize = newsize;
}

void ClientConnection::decodeRecvBuffer()
{
	int decodeOffset = 0;
	while ((m_decodeState == DECODE_HEAD && m_recvParissOffset-decodeOffset >= NET_PACKET_HEAD_LEN) || (m_decodeState == DECODE_DATA && m_recvParissOffset-decodeOffset >0))
	{
		if (m_decodeState == DECODE_HEAD)
		{
			uint8_t packType = *((uint8_t*)(m_recvParissBuffer+decodeOffset));
			uint16_t proc = *((uint16_t*)(m_recvParissBuffer+decodeOffset+1));
			uint32_t datalen = *((uint32_t*)(m_recvParissBuffer+decodeOffset+3));

			if ( packType != PACK_DISPATCH && packType != PACK_PROCREPLY )
			{
				LOG_ERROR("ClientConnection::decodeRecvBuffer wrong packet type packType = %d, proc = %d, datalen = %d\n", static_cast<int>(packType), static_cast<int>(proc), datalen );
				printf( "ClientConnection::decodeRecvBuffer wrong packet type packType = %d, proc = %d, datalen = %d\n", static_cast<int>(packType), static_cast<int>(proc), datalen );
				close();
				return;
			}

			if (static_cast<int>(datalen) > m_recvParissBufferSize)
			{
				LOG_INFO("ClientConnection::decodeRecvBuffer very large packet packType = %d, proc = %d, datalen = %d, m_recvParissBufferSize = %d\n", static_cast<int>(packType), static_cast<int>(proc), datalen, m_recvParissBufferSize);
			}

			decodeOffset += NET_PACKET_HEAD_LEN;

			m_packet = CLIENT_SERVER.popNetpacket(datalen);
			m_packet->setType(static_cast<PackType>(packType));
			m_packet->setProc(proc);
			m_packet->setSize(datalen);
			
			m_decodeState = DECODE_DATA;
		}

		if (m_decodeState == DECODE_DATA && m_packet != NULL)
		{
			uint32_t needlen = m_packet->getSize() - m_packet->getWOffset();
			uint32_t haslen = m_recvParissOffset - decodeOffset;
			uint32_t writelen = (std::min)(needlen, haslen);
			m_packet->write(m_recvParissBuffer+decodeOffset, writelen);
			decodeOffset += writelen;
			if (m_packet->getSize() == m_packet->getWOffset())
			{
				onNetPacket(m_packet);
				m_packet = NULL;
				m_decodeState = DECODE_HEAD;
			}
			//else
			//{
			//	LOG_INFO("ClientConnection::decodeRecvBuffer unfinish packet proc = %d, datalen = %d, m_recvParissOffset = %d\n", static_cast<int>(m_packet->getProc()), m_packet->getSize(), m_recvParissOffset );
			//}
		}
	}

	if ( decodeOffset < m_recvParissOffset )
	{
		memmove(m_recvParissBuffer, m_recvParissBuffer+decodeOffset, m_recvParissOffset-decodeOffset);
		//LOG_INFO( "ClientConnection::decodeRecvBuffer() not buff end decodeOffset=%d, m_recvParissBufferSize=%d\n", decodeOffset, m_recvParissBufferSize );
		//printf( "ClientConnection::decodeRecvBuffer() not buff end decodeOffset=%d, m_recvParissBufferSize=%d\n", decodeOffset, m_recvParissBufferSize );
	}

	m_recvParissOffset = m_recvParissOffset - decodeOffset;
}

void ClientConnection::encodeSendBuffer()
{
	NetPacket *nextPacket = m_sendList.front();
	while (nextPacket != NULL)
	{
		int len = (std::min)(static_cast<int>(nextPacket->getSize())-m_parseLen, m_sendBufferSize-m_sendLen);
		if (len <= 0)
		{
			LOG_ERROR("ClientConnection::encodeSendBuffer len = %d, nextPacket->getSize() = %d, m_parseLen = %d, m_sendBufferSize = %d, m_sendLen = %d\n", len, nextPacket->getSize(), m_parseLen, m_sendBufferSize, m_sendLen);
			return;
		}

		memcpy(m_sendBuffer+m_sendLen, nextPacket->getBuffer()-NET_PACKET_HEAD_LEN+m_parseLen, len);

		m_parseLen += len;
		if (m_parseLen == static_cast<int>(nextPacket->getSize()))
		{
			m_sendList.pop()->destroy();
			nextPacket = m_sendList.front();
			m_parseLen = 0;
		}

		m_sendLen += len;
		if (m_sendLen == m_sendBufferSize)
		{
			break;
		}
	}
}

int ClientConnection::setkeepalive(socket_t fd, int idleseconds)
{
	const char chOpt = 1;  
	int err = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&chOpt, sizeof(chOpt));
	if (err == 0)
	{
		tcp_keepalive klive;  
		klive.onoff = 1;
		klive.keepalivetime = idleseconds*1000;
		klive.keepaliveinterval = 10 * 1000;
		tcp_keepalive kliveout;
		DWORD dwBytes = 0;
		err = WSAIoctl(fd, SIO_KEEPALIVE_VALS, &klive, sizeof(klive), &kliveout, sizeof(kliveout), &dwBytes, NULL, NULL);
	}

	return err;
}

int ClientConnection::setnonblock(socket_t fd)
{
	u_long flag=1;
	return ioctlsocket(fd, FIONBIO, &flag);
}

int ClientConnection::setnodelay(socket_t fd)
{
	socklen_t optval = 1;
	int err = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&optval, sizeof(optval));
	if (err == SOCKET_ERROR)
	{
		LOG_DEBUG("setsockopt return SOCKET_ERROR in Answer::setnodelay\n");
	}
	return err;
}




