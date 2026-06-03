#pragma once

#include "User.h"

#include <map>
#include <vector>
typedef std::vector<int16_t> Int16Vector;
typedef std::vector<int32_t> Int32Vector;

class PHPServer : 
	public Answer::TcpServer
{
public:
	PHPServer();
	virtual ~PHPServer();

public:
	void onConnect(Answer::TcpConnection *conn);
	void onDisconnect(Answer::TcpConnection *conn);
	void onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
private:
	
	void sendToPHP(int16_t index,int8_t reason);
	void sendPacketTo(int16_t pos, Answer::NetPacket *inPacket, bool needEncodeHead);
private:
	Answer::ArrayList<Answer::TcpConnection*> m_conns;
	Answer::ObjectPool<User> m_userPool;
};
#define PHP_SERVER Answer::Singleton<PHPServer>::instance()

