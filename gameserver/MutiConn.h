#ifndef _MUTICONN_H_
#define _MUTICONN_H_

//////////////////////////////////////////////////////////////////////////
// MutiConn - multi-connection template for service-to-service communication
// Each MutiConn is a TcpClient that forwards packets to the owner service
//////////////////////////////////////////////////////////////////////////

#include "Answer/TcpClient.h"
#include <string>
#include <cstdint>

template <typename T>
class MutiConn : public Answer::TcpClient
{
public:
	typedef MutiConn<T> ConnType;

	MutiConn(uint32_t recvBuf, uint32_t sendBuf, uint32_t packBuf,
			 uint32_t sendQueue, uint32_t interval,
			 const std::string& name, int8_t id, T* pService)
		: TcpClient(recvBuf, sendBuf, packBuf, sendQueue, interval, name)
		, m_id(id)
		, m_pService(pService)
	{}

	~MutiConn() {}

	int8_t GetId() const { return m_id; }

protected:
	virtual void onNetPacket(Answer::NetPacket* inPacket)
	{
		if (m_pService)
			m_pService->onNetPacket(this, inPacket);
	}

private:
	int8_t	m_id;
	T*		m_pService;
};

#endif // _MUTICONN_H_
