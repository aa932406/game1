#include "stdafx.h"

#include "GateServer.h"
#include "ServiceServer.h"
#include "User.h"

#include <algorithm>

using namespace Answer;

ServiceServer::ServiceServer()
	: TcpServer(8192-NET_PACKET_HEAD_LEN, 20000, 100000, false), m_character(NULL), m_login(NULL), m_social(NULL)
{
	bzero(m_netprocs, sizeof(m_netprocs));
}

ServiceServer::~ServiceServer()
{

}

void ServiceServer::onConnect(Answer::TcpConnection *conn)
{
	if (NULL == conn)
	{
		return;
	}
	if (std::find(m_accetpIps.begin(), m_accetpIps.end(), conn->getIP()) == m_accetpIps.end())
	{
		LOG_WARN("ServiceServer::onConnect with invalid ip %s, halt it\n", conn->getIP().c_str());
		conn->halt();
		return;
	}
	conn->setCheckPackSize(false);
	conn->setCheckHalt(false);
}

void ServiceServer::onDisconnect(Answer::TcpConnection *conn)
{
	if (conn == m_character)
	{
		m_character = NULL;
	}

	Answer::RwLockWrGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		if (it->conn == conn)
		{
			m_games.erase(it);
			break;
		}
	}

	if (conn == m_gameSocial)
	{
		m_gameSocial = NULL;
	}

	if (conn == m_login)
	{
		m_login = NULL;
	}

	if (conn == m_social)
	{
		m_social = NULL;
	}
	LOG_INFO("ServiceServer::onDisconnect with ip %s\n", conn->getIP().c_str());
}
//接收
void ServiceServer::onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	uint16_t proc = inPacket->getProc();

	if (proc > IM_MIN && proc < IM_MAX)
	{
		//内部消息处理
		onInternalProc(conn, inPacket);
	}
	else if(proc>SM_PHP_MIN && proc <SM_PHP_MAX)
	{
		onPHPProc(conn, inPacket);
	}
	else
	{
		//发送给gate处理并发送给flash_client
		onServerProc(conn, inPacket);
	}
}

void ServiceServer::setAcceptIps(const StringVector &acceptIps)
{
	m_accetpIps.assign(acceptIps.begin(), acceptIps.end());
}

void ServiceServer::sendQQToPlayer(Answer::TcpConnection *conn,int16_t cgindex,std::string openId ,std::string openKey ,std::string pf ,std::string pfKey,int32_t isYellowVip,int32_t isYellowYearVip,int32_t yellowVipLevel,int32_t isYellowHighVip)
{
	if(conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(cgindex);
		packet->writeUTF8(openId.c_str());
		packet->writeUTF8(openKey.c_str());
		packet->writeUTF8(pf.c_str());
		packet->writeUTF8(pfKey.c_str());
		packet->writeInt32(isYellowVip);
		packet->writeInt32(isYellowYearVip);
		packet->writeInt32(yellowVipLevel);
		packet->writeInt32(isYellowHighVip);
		packet->setType(PACK_PROC);
		packet->setProc(IM_GATE_QQ_TO_PLAYER);
		packet->setSize(packet->getWOffset());
		conn->sendPacket(packet, true);

	}
	
}


bool ServiceServer::forPHPToService(ServiceName service, Answer::TcpConnection *fromconn,Answer::NetPacket *inPacket)
{
	if (fromconn == NULL || inPacket == NULL)
	{
		return false;
	}
	User *fromuser = static_cast<User*>(fromconn->getPtr());
	if (fromuser == NULL)
	{
		return false;
	}
	//选择连接
	TcpConnection *toconn = NULL;
	switch (service)
	{
	case SN_CHARACTER: toconn = m_character; break; //角色
	case SN_GAME: toconn = fromuser->getGameConn(); break;
	case SN_LOGIN: toconn = m_login; break;
	case SN_SOCIAL: toconn = m_social; break;
	default: toconn = NULL; break;
	}
	if(toconn ==NULL)
	{
		return false;
	}
	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return false;
	}
	int32_t ntype =inPacket->readInt32();
	int32_t item=inPacket->readInt32();
	int32_t ncount=inPacket->readInt32();
	packet->writeInt16(fromuser->getIndex());
	packet->writeInt32(ntype);
	packet->writeInt32(item);
	packet->writeInt32(ncount);
	packet->setType(inPacket->getType());
	packet->setProc(inPacket->getProc());
	packet->setSize(inPacket->getSize());
	//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
	toconn->sendPacket(packet, true);
	packet->destroy();
	return true;
}
//角色处理
void ServiceServer::forwardToService(ServiceName service, Answer::TcpConnection *fromconn, Answer::NetPacket *inPacket)
{
	if (fromconn == NULL || inPacket == NULL)
	{
		return;
	}

	User *fromuser = static_cast<User*>(fromconn->getPtr());
	if (fromuser == NULL)
	{
		return;
	}
	//选择连接
	TcpConnection *toconn = NULL;
	switch (service)
	{
	case SN_CHARACTER: toconn = m_character; break; //角色
	case SN_GAME: toconn = fromuser->getGameConn(); break;
	case SN_LOGIN: toconn = m_login; break;
	case SN_SOCIAL: toconn = m_social; break;
	default: toconn = NULL; break;
	}

	if (inPacket->getProc() == CM_ENTER_GAME || inPacket->getProc() == CM_ENTER_GAME_ROBOT)
	{
		if (toconn != NULL)
		{
			return;
		}

		inPacket->readInt32();
		CharId_t CharId = inPacket->readInt64();
		int32_t line = inPacket->readInt32();

		Answer::RwLockRdGuard lock(m_gamesLock);
		for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
		{
			if (it->line == line && it->isOpen)
			{
				fromuser->setGameConn(it->conn);
				toconn = it->conn;
				break;
			}
		}

		if (toconn != NULL)
		{
			sendAddUser(toconn, fromuser->getIndex(), fromuser->getUid(), fromuser->getSid(), fromconn->getIP());
			if(inPacket->getProc() == CM_ENTER_GAME)
			{
				sendQQToPlayer(toconn,fromuser->getIndex(),fromuser->getOpenId(),fromuser->getOpenKey(),fromuser->getPf(),fromuser->getPfKey(),fromuser->getIsYellowVip(),fromuser->getIsYellowYearVip(),fromuser->getYellowVipLevel(),fromuser->getIsYellowHighVip());
				
			}
		}
	}

	if (toconn == NULL)
	{
		return;
	}

	inPacket->setWOffset(0);
	inPacket->writeInt32(fromuser->getIndex());
	NetPacket *packet = popNetpacket(inPacket->getSize());
	if (NULL == packet)
	{
		return;
	}
	packet->write(inPacket->getBuffer(), inPacket->getSize());
	packet->setType(inPacket->getType());
	packet->setProc(inPacket->getProc());
	packet->setSize(inPacket->getSize());
	//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
	toconn->sendPacket(packet, true);
}

void ServiceServer::onAddUser(int16_t cgindex, int32_t uid, int32_t sid, const std::string &fromip)
{
	sendAddUser(m_character, cgindex, uid, sid, fromip);
}

void ServiceServer::onRemoveUser(int16_t cgindex, int32_t uid, LogoutReason reason, int32_t param)
{
	sendRemoveUser(m_character, cgindex, uid, reason, param);

	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		sendRemoveUser(it->conn, cgindex, uid, reason, param);
	}
}

void ServiceServer::onUpdateBanChat(int32_t action, int32_t uid, int32_t expire_time)
{
	sendUpdateBanChat(m_social, action, uid, expire_time);

	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		sendUpdateBanChat(it->conn, action, uid, expire_time);
	}
}

void ServiceServer::onGMReloadItem()
{
	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		sendGMReloadItem(it->conn);
	}
}

GameServiceConnectionVector ServiceServer::getGameServices()
{
	Answer::RwLockRdGuard lock(m_gamesLock);
	return GameServiceConnectionVector(m_games);
}

GameServiceConnection ServiceServer::findGameService(int32_t line)
{
	GameServiceConnection game = {};

	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		if (it->line == line)
		{
			game = *it;
			break;
		}
	}

	return game;
}

void ServiceServer::closeLines(const Int32Vector &lines)
{
	Answer::RwLockWrGuard lock(m_gamesLock);
	for (Int32Vector::const_iterator it = lines.begin(); it != lines.end(); ++it)
	{
		for (GameServiceConnectionVector::iterator itGame = m_games.begin(); itGame != m_games.end(); ++itGame)
		{
			if (itGame->line == *it && itGame->isOpen)
			{
				itGame->isOpen = false;
			}
		}
	}

	Int16Vector indexes(GATE_SERVER.getUserIndexesInGame());

	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(static_cast<int32_t>(lines.size()));
	for (Int32Vector::const_iterator it = lines.begin(); it != lines.end(); ++it)
	{
		packet->writeInt32(*it);
	}
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_LINE_CLOSED);
	packet->setSize(packet->getWOffset());
	packet->setRefCount(packet->getRefCount()+indexes.size());
	packet->encodeHeadInfo();
	for (Int16Vector::iterator it = indexes.begin(); it != indexes.end(); ++it)
	{
		int16_t pos = *it;
		GATE_SERVER.sendPacketTo(pos, packet, false);
	}
	packet->destroy();
}

void ServiceServer::onSwitchGameService(Answer::TcpConnection *pOld, Answer::TcpConnection *pNew)
{
	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		if (it->conn != NULL)
		{
			if (it->conn == pOld)
			{
				--it->count;
			}

			if (it->conn == pNew)
			{
				++it->count;
			}
		}
	}
}

void ServiceServer::logServerProcs()
{
	for (int32_t i = 0; i < SM_MAX-SM_MIN+1; ++i)
	{
		if (m_netprocs[i].count > 0 || m_netprocs[i].bytes > 0)
		{
			LOG_INFO("server proc %d, count %d, byte %d kbytes\n", i+SM_MIN, m_netprocs[i].count, static_cast<int32_t>(m_netprocs[i].bytes/1000));
		}
	}
}

void ServiceServer::sendAddUser(Answer::TcpConnection *conn, int16_t cgindex, int32_t uid, int32_t sid, const std::string &fromip)
{
	if (conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(cgindex);
		packet->writeInt32(uid);
		packet->writeInt32(sid);
		packet->writeUTF8(fromip.c_str());
		packet->setType(PACK_PROC);
		packet->setProc(IM_GATE_ADD_USER);
		packet->setSize(packet->getWOffset());
		conn->sendPacket(packet, true);
	}
}

void ServiceServer::sendRemoveUser(Answer::TcpConnection *conn, int16_t cgindex, int32_t uid, LogoutReason reason, int32_t param)
{
	if (conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(cgindex);
		packet->writeInt32(uid);
		packet->writeInt32(reason);
		packet->writeInt32(param);
		packet->setType(PACK_PROC);
		packet->setProc(IM_GATE_REMOVE_USER);
		packet->setSize(packet->getWOffset());
		//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
		conn->sendPacket(packet, true);
	}
}

void ServiceServer::sendUpdateBanChat(Answer::TcpConnection *conn, int32_t action, int32_t uid, int32_t expire_time)
{
	if (conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(action);
		packet->writeInt32(uid);
		packet->writeInt32(expire_time);
		packet->setType(PACK_PROC);
		packet->setProc(IM_GATE_UPDATE_BAN_CHAT);
		packet->setSize(packet->getWOffset());
		//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
		conn->sendPacket(packet, true);
	}
}

void ServiceServer::sendGMReloadItem(Answer::TcpConnection *conn)
{
	if (conn != NULL)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(0);
		packet->setType(PACK_PROC);
		packet->setProc(IM_GATE_RELOAD_ITEM);
		packet->setSize(packet->getWOffset());
		conn->sendPacket(packet, true);
	}
}

void ServiceServer::onInternalProc(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	uint16_t proc = inPacket->getProc();

	if ( proc == IM_SOCIAL_NEW_MINUTE_COME )	//屏蔽协议号
	{
		GATE_SERVER.OnLoadShieldProtocol();
	}
	if (proc > IM_SOCIAL_GAME_MIN && proc < IM_SOCIAL_GAME_MAX) //gameserver
	{
		forwardToGame(inPacket);
	}
	else if (proc > IM_SOCIAL_SPECIFIC_GAME_MIN && proc < IM_SOCIAL_SPECIFIC_GAME_MAX)//gameserver
	{
		directForward(m_gameSocial, inPacket);
	}
	else if (proc > IM_SOCIAL_ALL_GAME_MIN && proc < IM_SOCIAL_ALL_GAME_MAX)
	{
		broadcastToGame(inPacket);
	}
	else if (proc > IM_SOCIAL_SINGLE_GAME_MIN && proc < IM_SOCIAL_SINGLE_GAME_MAX)
	{
		forwardToGameLine(inPacket);
	}
	else if ((proc > IM_SOCIAL_GLOBAL_MIN && proc < IM_SOCIAL_GLOBAL_MAX) || (proc > IM_GAME_SOCIAL_MIN && proc < IM_GAME_SOCIAL_MAX))//globalserver
	{
		directForward(m_social, inPacket);
	}
	else
	{
		switch (proc)
		{
		case IM_CHARACTER_SERVICE_CONNECT: onCharacterServiceConnect(conn, inPacket); break;//内部CharacterService的连接
		case IM_GAME_SERVICE_CONNECT: onGameServiceConnect(conn, inPacket); break;	//内部GameService的连接
		case IM_LOGIN_SERVICE_CONNECT: onLoginServiceConnect(conn, inPacket); break;	//内部LoginService的连接
		case IM_SOCIAL_SERVICE_CONNECT: onSocialServiceConnect(conn, inPacket); break; //内部SocialService的连接
		case IM_GAME_GATE_USER_SAVED: onUserSaved(conn, inPacket); break;
		case IM_GAME_GATE_KICK_USER:	onGameKickUser( conn, inPacket );	break;
		default: break;
		}
	}
}
void ServiceServer::onPHPProc(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	//size_t offset = sizeof(int32_t) + sizeof(int32_t);

	//if (inPacket->getSize() > offset)
	{
		int16_t index = inPacket->readInt16();
		int8_t flag =inPacket->readInt8();
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt8(flag);
		packet->setType(inPacket->getType());
		packet->setProc(inPacket->getProc());
		packet->setSize(packet->getWOffset());
		//int8_t size=0;
		//packet->setRefCount(inPacket->getRefCount() + size);
		//packet->encodeHeadInfo();

		GATE_SERVER.sendPacketToPHP(index,packet,true);
		packet->destroy();
	}

}
void ServiceServer::onServerProc(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	int16_t size = inPacket->readInt16();
	if (size > 0)
	{
		uint32_t outpacksize = inPacket->getSize() - (size+1)*sizeof(int16_t);
		NetPacket *packet = popNetpacket(outpacksize);
		if (NULL == packet)
		{
			return;
		}
		packet->write(inPacket->getBuffer()+(size+1)*sizeof(int16_t), outpacksize);
		packet->setType(inPacket->getType());
		packet->setProc(inPacket->getProc());
		packet->setSize(outpacksize);
		//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
		packet->setRefCount(inPacket->getRefCount() + size);
		packet->encodeHeadInfo();

		GATE_SERVER.checkSendToGM(packet);
		addServerProcRecord(inPacket->getProc(), size, inPacket->getSize());

		for (int16_t i = 0; i < size; ++i)
		{
			int16_t pos = inPacket->readInt16();
			GATE_SERVER.sendPacketTo(pos, packet, false);
		}

		packet->destroy();
	}
	else if (size == -1) //world broadcast
	{
		Int16Vector index(GATE_SERVER.getUserIndexesInGame());

		uint32_t outpacksize = inPacket->getSize() - sizeof(int16_t);
		NetPacket *packet = popNetpacket(outpacksize);
		if (NULL == packet)
		{
			return;
		}
		packet->write(inPacket->getBuffer()+sizeof(int16_t), outpacksize);
		packet->setType(inPacket->getType());
		packet->setProc(inPacket->getProc());
		packet->setSize(outpacksize);
		//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
		packet->setRefCount(inPacket->getRefCount() + index.size());
		packet->encodeHeadInfo();

		GATE_SERVER.checkSendToGM(packet);
		addServerProcRecord(inPacket->getProc(), index.size(), inPacket->getSize());

		for (Int16Vector::iterator it = index.begin(); it != index.end(); ++it)
		{
			int16_t pos = *it;
			GATE_SERVER.sendPacketTo(pos, packet, false);
		}

		packet->destroy();
	}
}

void ServiceServer::onCharacterServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (m_character == NULL && conn != NULL)
	{
		m_character = conn;
	}
}

//来自游戏中心的连接
void ServiceServer::onGameServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (conn != NULL || inPacket != NULL)
	{
		int32_t line = inPacket->readInt32();

		GameServiceConnection gameConn = {};
		gameConn.line = line;
		gameConn.isOpen = true;
		gameConn.conn = conn;

		Answer::RwLockWrGuard lock(m_gamesLock);
		m_games.push_back(gameConn);

		if (gameConn.line == GAME_SERVICE_LINE_SOCIAL)
		{
			m_gameSocial = conn;
		}
	}
}

void ServiceServer::onLoginServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (m_login == NULL && conn != NULL)
	{
		m_login = conn;
	}
}

void ServiceServer::onSocialServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (m_social == NULL && conn != NULL)
	{
		m_social = conn;
	}
}

void ServiceServer::onUserSaved(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	int32_t uid = inPacket->readInt32();
	int32_t sid = inPacket->readInt32();
	int32_t reason = inPacket->readInt32();
	int64_t wparam = inPacket->readInt64();
	int32_t lparam = inPacket->readInt32();

	GATE_SERVER.onUserSaved(uid, sid, reason, wparam, lparam);
}

void ServiceServer::onGameKickUser(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	int32_t uid = inPacket->readInt32();
	int32_t sid = inPacket->readInt32();

	GATE_SERVER.onGameKickUser(uid, sid);
}

void ServiceServer::directForward(Answer::TcpConnection *service, Answer::NetPacket *inPacket)
{
	if (service != NULL && inPacket != NULL)
	{
		NetPacket *packet = popNetpacket(inPacket->getSize());
		if (NULL == packet)
		{
			return;
		}
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setType(inPacket->getType());
		packet->setProc(inPacket->getProc());
		packet->setSize(inPacket->getSize());
		//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
		service->sendPacket(packet, true);
	}
}

void ServiceServer::forwardToGame(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	size_t offset = sizeof(int32_t) + sizeof(int32_t);
	
	if (inPacket->getSize() > offset)
	{
		int32_t uid = inPacket->readInt32();
		int32_t sid = inPacket->readInt32();

		TcpConnection *gameConn = GATE_SERVER.getUserGameConn(uid, sid);
		if (gameConn != NULL)
		{
			NetPacket *packet = popNetpacket(inPacket->getSize());
			if (NULL == packet)
			{
				return;
			}
			packet->write(inPacket->getBuffer()+offset, inPacket->getSize()-offset);
			packet->setType(inPacket->getType());
			packet->setProc(inPacket->getProc());
			packet->setSize(inPacket->getSize()-offset);
			//LOG_DEBUG("ServiceServer popNetpacket %p proc %d in line %d\n", packet, packet->getProc(), __LINE__);
			gameConn->sendPacket(packet, true);
		}
	}
}

void ServiceServer::broadcastToGame(Answer::NetPacket *inPacket)
{
	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		directForward(it->conn, inPacket);
	}
}

void ServiceServer::forwardToGameLine(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return;
	}
	int32_t nLine = inPacket->readInt32();
	uint16_t offset = sizeof( int32_t );
	Answer::RwLockRdGuard lock(m_gamesLock);
	for (GameServiceConnectionVector::iterator it = m_games.begin(); it != m_games.end(); ++it)
	{
		if ( it->line == nLine )
		{
			NetPacket *packet = popNetpacket( inPacket->getSize() );
			if ( NULL == packet )
			{
				return;
			}
			packet->write( inPacket->getBuffer()+offset, inPacket->getSize()-offset );
			packet->setType( inPacket->getType() );
			packet->setProc( inPacket->getProc() );
			packet->setSize( packet->getWOffset() );
			it->conn->sendPacket(packet, true);
			break;
		}
	}
}

void ServiceServer::addServerProcRecord(int32_t proc, int32_t count, int32_t bytes)
{
	if (proc >= SM_MIN && proc <= SM_MAX && count >= 0 && bytes >= 0)
	{
		m_netprocs[proc-SM_MIN].count += count;
		m_netprocs[proc-SM_MIN].bytes += count*bytes;
	}
}

