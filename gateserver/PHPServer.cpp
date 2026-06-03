#include "stdafx.h"
#include "PHPServer.h"

#include "ServiceServer.h"
#include "GateServer.h"

#include <string>

using namespace Answer;
using namespace std;

PHPServer::PHPServer()
	: TcpServer(2048-NET_PACKET_HEAD_LEN, 2000, 5000, true), m_conns(MAX_CONNECTION),m_userPool(1000,2000)
{
	m_conns.add(new TcpConnection);
}


PHPServer::~PHPServer()
{
}

void PHPServer::onConnect(Answer::TcpConnection *conn)
{
	int16_t index = m_conns.add(conn);
	if (index > 0)
	{
		User *user = m_userPool.pop();
		if (user != NULL)
		{
			user->setIndex(index);
			conn->setPtr(static_cast<void*>(user)); //添加一个玩家数据
		}
	}
}
void PHPServer::onDisconnect(Answer::TcpConnection *conn)
{
	if (NULL == conn)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{
		int16_t cgindex = user->getIndex();
		if (cgindex > 0)
		{
			conn->setPtr(NULL);
			m_conns.remove(user->getIndex(), conn);				
			m_userPool.push(user);
		}
	}
}
void PHPServer::onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	PackType type = inPacket->getType();
	uint16_t proc = inPacket->getProc();
	if(proc == CM_GATE_PHP_PROP && type ==PACK_PROC)
	{
		int32_t uid=inPacket->readInt32();
		int32_t sid =inPacket->readInt32();
		
		User *user = static_cast<User*>(conn->getPtr());

		{
			MySqlDBGuard db(DBPOOL);
			char szSQL[MAX_SQL_LENGTH*2] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "SELECT `key` FROM `pay_key` WHERE `ip`='%s'",conn->getIP().c_str());
			MySqlQuery result = db.query(szSQL);
			if (result.eof())
			{
				sendToPHP(user->getIndex(),1);
				return;
			}
		}
		TcpConnection* userConn=NULL;
		User *gameUser=NULL;
		if (user != NULL)
		{
			bool bret=false;
			if(uid>0) 
			{
				bret =true;
				userConn =GATE_SERVER.findClinetConnByPHP(uid,sid,conn);
				if(userConn==NULL)bret=false;
				if(userConn!=NULL)
				{
					gameUser =static_cast<User*>(userConn->getPtr());
					if(gameUser==NULL)bret =false;
				}
			}
			if(bret)
			{
				bret=SERVICE_SERVER.forPHPToService(SN_GAME, userConn, inPacket);
				if(!bret)
				{
					gameUser->setIsPHP(false);
					gameUser->setPHPConn(NULL);
				}
			}
			if(!bret)
			{
				sendToPHP(user->getIndex(),1);
			}
		}
	}
}

void PHPServer::sendPacketTo(int16_t pos, Answer::NetPacket *inPacket, bool needEncodeHead)
{
	if (NULL == inPacket)
	{
		return;
	}
	TcpConnection *conn = m_conns.find(pos);
	if (conn == NULL)
	{
		inPacket->destroy();
		return;
	}

	conn->sendPacket(inPacket, needEncodeHead);
}
void PHPServer::sendToPHP(int16_t index,int8_t reason)
{
	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8(reason);
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_PHP_BUY);
	packet->setSize(packet->getWOffset());
	sendPacketTo(index, packet, true);
	packet->destroy();
}

