#include "stdafx.h"

#include "GateServer.h"
#include "ServiceServer.h"

#include <string>

using namespace Answer;
using namespace std;

GateServer::GateServer()
	: TcpServer(2048-NET_PACKET_HEAD_LEN, 2000, 5000, true), m_conns(MAX_CONNECTION), m_userPool(1000, 2000)
{
	m_conns.add(new TcpConnection);
	m_currentTime = 0;
	m_currentProc=0;
	OnLoadShieldProtocol();
}

GateServer::~GateServer()
{

}

//保存客户端连接的玩家套接口
void GateServer::onConnect(Answer::TcpConnection *conn)
{
	int16_t index = m_conns.add(conn);
	if (index > 0)
	{
		User *user = m_userPool.pop();
		if (user != NULL && conn != NULL)
		{
			user->setIndex(index);
			conn->setPtr(static_cast<void*>(user)); //添加一个玩家数据
#ifdef _DEBUG
			printf( "GateServer::onConnect() index=%d,\tip=%s\n", index, conn->getIP().c_str() );
#endif
		}
	}
}

void GateServer::onDisconnect(Answer::TcpConnection *conn)
{
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && conn != NULL)
	{
		int16_t cgindex = user->getIndex();
		if (cgindex > 0)
		{
			int32_t uid = user->getUid();
			if (uid > 0)
			{
				int32_t sid = user->getSid();

				removeUser(uid, sid);

				user->setUid(0);
				user->setSid(0);				
				user->setGameConn(NULL);

				SERVICE_SERVER.onRemoveUser(cgindex, uid, LR_DISCONNECT, 0);
			}

			if (user->isGM())
			{
				MutexGuard lock(m_gmLock);
				m_gmUsers.remove(user);
			}
#ifdef _DEBUG
			printf( "GateServer::onDisconnect() index=%d,\tip=%s\n", cgindex, conn->getIP().c_str() );
#endif
			conn->setPtr(NULL);
			m_conns.remove(user->getIndex(), conn);				
			m_userPool.push(user);
		}
	}
}

//接收客户端flash数据
void GateServer::onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	PackType type = inPacket->getType();
	uint16_t proc = inPacket->getProc();
	int64_t nowTime= DayTime::tick();
	if (nowTime-m_currentTime <=30 && m_currentProc==proc) //小于30ms的包丢弃
	{
		m_currentTime =nowTime;
		LOG_ERROR("不正常的协议%d",proc);
		return;
	}
	if ( CheckProtocolShielded( proc ) )
	{
		return;
	}
	m_currentProc =proc;
	//接收数据转发给gameServer游戏服务器
	if (type == PACK_PROC)
	{
		if (proc > CM_CHARACTER_MIN && proc < CM_CHARACTER_MAX)//globalserver
		{
			User *user = static_cast<User*>(conn->getPtr());
			if (user != NULL && user->getUid() > 0 && inPacket->decryptAndCheck() && user->checkAutoIncreaseAndUpdate(inPacket->getAutoIncrease()))
			{
				SERVICE_SERVER.forwardToService(SN_CHARACTER, conn, inPacket);
			}
		}
		else if (proc > CM_GAME_MIN && proc < CM_GAME_MAX)//gameserver
		{
			User *user = static_cast<User*>(conn->getPtr());
			if (user != NULL && user->getUid() > 0 && inPacket->decryptAndCheck() && user->checkAutoIncreaseAndUpdate(inPacket->getAutoIncrease()))
			{
				if (proc == CM_MOVE )
				{
					user->updateActiveTick();
				}
				SERVICE_SERVER.forwardToService(SN_GAME, conn, inPacket);
			}
		}
		else if (proc > CM_GATE_MIN && proc < CM_GATE_MAX)//Gateserver
		{
			if (inPacket->decryptAndCheck())
			{
				if (proc == CM_GATE_LOGIN || proc == CM_GATE_LOGIN_ROBOT)
				{
					switch (proc)
					{
					case CM_GATE_LOGIN: onGateLogin(conn, inPacket); break;
					case CM_GATE_LOGIN_ROBOT: onGateLoginRobot(conn, inPacket); break;
					default: break;
					}
				}
				else
				{
					User *user = static_cast<User*>(conn->getPtr());
					if (user != NULL && user->getUid() > 0 && user->checkAutoIncreaseAndUpdate(inPacket->getAutoIncrease()))
					{
						switch (proc)
						{
						case CM_GATE_SWITCH_LINE: onGateSwitchLine(conn, inPacket); break;
						case CM_GATE_QUERY_LINE: onGateQueryLine(conn, inPacket); break;
						case CM_GATE_LOAD_UI:	OnRecordLoadUi( conn, inPacket ); break;
						default: break;
						}
					}
				}
			}
		}
		
		else if (proc > CM_LOGIN_MIN && proc < CM_LOGIN_MAX)//globlserver
		{
			if (inPacket->decryptAndCheck())
			{
				SERVICE_SERVER.forwardToService(SN_LOGIN, conn, inPacket);
			}
		}
		else if (proc > CM_SOCIAL_MIN && proc < CM_SOCIAL_MAX)//globlserver
		{
			User *user = static_cast<User*>(conn->getPtr());
			if (user != NULL && user->getUid() > 0 && inPacket->decryptAndCheck() && user->checkAutoIncreaseAndUpdate(inPacket->getAutoIncrease()))
			{
				inPacket->readInt32();
				if (proc == CM_SOCIAL_PUBLIC_CHAT || proc == CM_SOCIAL_PRIVATE_CHAT)
				{
					user->updateActiveTick();
				}
				SERVICE_SERVER.forwardToService(SN_SOCIAL, conn, inPacket);
			}
		}
		else if (proc > CM_GM_MIN && proc < CM_GM_MAX)//gateserver
		{
			switch (proc)
			{
			case CM_GM_LOGIN: onGMLogin(conn, inPacket); break;
			case CM_GM_BAN_LOGIN: onGMBanLogin(conn, inPacket); break;
			case CM_GM_BAN_CHAT: onGMBanChat(conn, inPacket); break;
			case CM_GM_BAN_IP: onGMBanIp(conn, inPacket); break;
			case CM_GM_KICK_USER: onGMKickUser(conn, inPacket); break;
			case CM_GM_CLOSE_LINE: onGMCloseLine(conn, inPacket); break;
			case CM_GM_RELOAD_ITEM: onGMReloadItem(conn, inPacket); break;
			default: break;
			}
		}
		else
		{
			onDisconnect(conn); //非法的协议断开
		}
	}
	else
	{
		LOG_INFO("wrong packet from ip %s, type %d, proc %d\n", conn->getIP().c_str(), (int)(type), (int)(proc));
	}
}

void GateServer::OnRecordLoadUi( Answer::TcpConnection *conn, Answer::NetPacket *inPacket )
{
	if ( NULL == conn || NULL == inPacket )
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if ( NULL == user )
	{
		return;
	}
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `sys_user` SET `load_create_chr_ui`=2 WHERE `uid`=%d AND `sid`=%d", user->getUid(), user->getSid() );
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);
}

void GateServer::OnLoadShieldProtocol()
{
	string inifile = "./ServerConfig/Config/ShieldPDU.ini";

	Inifile ini;
	ini.parse(inifile);
	string PDUString = ini.getStrValue("ShieldPDU", "ProtocolList");
	StringVector PDUvt = StringUtility::split(PDUString, "|");
	MutexGuard lock(m_ShieldProtocolLock);
	m_ShieldProtocol.clear();
	for (StringVector::const_iterator itor = PDUvt.begin(); itor!=PDUvt.end(); ++itor)
	{
		int32_t procId=atoi(itor->c_str());
		if (procId > 0)
		{
			m_ShieldProtocol.push_back(procId);
			LOG_INFO("添加屏蔽协议ID：%d 成功\n", procId);
		}
	}
}

bool GateServer::CheckProtocolShielded( int32_t ProcId )
{
	MutexGuard lock(m_ShieldProtocolLock);
	for ( std::list<int32_t>::iterator pId = m_ShieldProtocol.begin(); pId != m_ShieldProtocol.end(); ++pId )
	{
		if(*pId==ProcId)
		{
			return true;
		}
	}

	return false;
}

void GateServer::sendPacketTo(int16_t pos, Answer::NetPacket *inPacket, bool needEncodeHead)
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

	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{
		if (inPacket->getProc() == SM_CHR_INFO)
		{
			user->setIsInGame(true);
		}
	}
	conn->sendPacket(inPacket, needEncodeHead);
}

void GateServer::sendPacketToPHP(int16_t pos, Answer::NetPacket *inPacket, bool needEncodeHead)
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
	TcpConnection* pConn=NULL;
	User *user = static_cast<User*>(conn->getPtr());
	if(user!=NULL)
	{
		pConn =user->getPHPConn();
		pConn->sendPacket(inPacket, needEncodeHead);
		user->setPHPConn(NULL);
		user->setIsPHP(false);
	}
}
void GateServer::checkSendToGM(Answer::NetPacket *packet)
{
	if (packet == NULL)
	{
		return;
	}

	uint16_t proc = packet->getProc();
	if (proc == SM_PUBLIC_CHAT || proc == SM_PRIVATE_CHAT)
	{
		MutexGuard lock(m_gmLock);
		if (!m_gmUsers.empty())
		{
			int32_t gmCount = static_cast<int32_t>(m_gmUsers.size());

			NetPacket *gmPacket = popNetpacket(packet->getSize());
			if (NULL == gmPacket)
			{
				return;
			}
			gmPacket->write(packet->getBuffer(), packet->getSize()-NET_PACKET_HEAD_LEN);
			gmPacket->setType(packet->getType());
			gmPacket->setProc(SM_GM_CHAT);
			gmPacket->setSize(gmPacket->getWOffset());
			gmPacket->setRefCount(gmPacket->getRefCount()+gmCount);
			gmPacket->encodeHeadInfo();

			for (UserList::iterator it = m_gmUsers.begin(); it != m_gmUsers.end(); ++it)
			{
				sendPacketTo((*it)->getIndex(), gmPacket, false);
			}

			gmPacket->destroy();
		}
	}
}
void GateServer::onUserSaved(int32_t uid, int32_t sid, int32_t reason, int64_t wparam, int32_t lparam)
{
	switch (reason)
	{
	case LR_KICK_SELF:
		{
			User *user = findUser(uid, sid);
			if (user != NULL)
			{
				TcpConnection *conn = m_conns.find(user->getIndex());
				if (conn != NULL)
				{
					SERVICE_SERVER.onAddUser(user->getIndex(), user->getUid(), user->getSid(), conn->getIP());
					sendLineList(conn);
					replySuccess(conn, CM_GATE_LOGIN);
				}
			}
		}
		break;

	case LR_SWITCH_LINE:
		{
			GameServiceConnection game = SERVICE_SERVER.findGameService(lparam);
			if (game.conn != NULL)
			{
				User *user = findUser(uid, sid);
				if (user != NULL)
				{
					TcpConnection *conn = m_conns.find(user->getIndex());
					if (conn != NULL)
					{
						user->setGameConn(NULL);

						NetPacket *packet = popNetpacket();
						if (NULL == packet)
						{
							return;
						}
						packet->writeInt32(uid);
						packet->writeInt32(sid);
						packet->writeInt32(lparam);
						packet->setType(PACK_PROC);
						packet->setProc(CM_ENTER_GAME);
						packet->setSize(packet->getWOffset());
						SERVICE_SERVER.forwardToService(SN_GAME, conn, packet);
					}
				}
			}
		}

	default:
		break;
	}
}
void GateServer::onGameKickUser(int32_t uid, int32_t sid)
{
	User *user = findUser(uid, sid);
	if ( user != NULL )
	{

		MutexGuard lock( m_nmUserLock );
		removeUserNoLock( user->getUid(), user->getSid() );

		SERVICE_SERVER.onRemoveUser( user->getIndex(), uid, LR_KICK_BY_GM, 0 );
		sendKickOut( user->getIndex(), LR_KICK_BY_GM );

		user->setUid(0);
		user->setSid(0);
		user->setGameConn(NULL);
	}
}

Answer::TcpConnection* GateServer::getUserGameConn(int32_t uid, int32_t sid)
{
	User *user = findUser(uid, sid);
	if (user != NULL)
	{
		return user->getGameConn();
	}
	else
	{
		return NULL;
	}
}

Int16Vector GateServer::getUserIndexesInGame()
{
	Int16Vector index;

	MutexGuard lock(m_nmUserLock);
	for (Int32UserMap::iterator it = m_nmUsers.begin(); it != m_nmUsers.end(); ++it)
	{
		for (UserList::iterator itUser = it->second.begin(); itUser != it->second.end(); ++itUser)
		{
			if ((*itUser)->getGameConn() != NULL)
			{
				index.push_back((*itUser)->getIndex());
			}
		}
	}
			
	return index;
}

OnlineStatus GateServer::getOnlineStatus()
{
	int64_t nowTick = DayTime::tick();

	OnlineStatus status = {};

	MutexGuard lock(m_nmUserLock);

	for (Int32UserMap::iterator it = m_nmUsers.begin(); it != m_nmUsers.end(); ++it)
	{
		for (UserList::iterator itUser = it->second.begin(); itUser != it->second.end(); ++itUser)
		{
			++status.login;
			if ((*itUser)->isInGame())
			{
				if ((*itUser)->isActive(nowTick))
				{
					++status.active;
				}
				else
				{
					++status.inactive;
				}
			}
		}
	}

	return status;
}

int32_t GateServer::getGMSealLeftTime( int32_t uid, int32_t sid )
{
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.`expire_time` FROM `gmt_seal` a LEFT JOIN `mem_character` b ON a.`cid`=b.`cid` WHERE b.`uid`=%d and b.`sid`=%d", uid,sid);

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result =	db.query(szSQL);
	if ( result.getRowCount() > 0 )
	{
		int32_t nExpireTime = result.getIntValue("expire_time");
		int32_t nowtime = DayTime::now();
		if ( nExpireTime > nowtime )
		{
			return nExpireTime - nowtime;
		}
	}

	return 0;
}

void GateServer::onGateLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	//LOG_INFO("1");
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{	//LOG_INFO("2");
		inPacket->readInt32();
		int32_t uid = inPacket->readInt32();
		int32_t sid = inPacket->readInt32();
		std::string token = inPacket->readUTF8(true);
		//QQ
		std::string openId  = "";	// inPacket->readUTF8(true);
		std::string openKey = "";	// inPacket->readUTF8(true);
		std::string pf		= "";	// inPacket->readUTF8(true);
		std::string pfKey	= "";	// inPacket->readUTF8(true);

		int32_t nSealTime = getGMSealLeftTime( uid,sid );
		if ( nSealTime > 0 )
		{
			// 封号
			replyFailure( conn, inPacket->getProc(), 1, nSealTime );
			return;
		}

		char szSQL[MAX_SQL_LENGTH] = {};
		snprintf(szSQL, sizeof(szSQL)-1, "SELECT `token`, `create_time`,`is_yellow_vip`,`is_yellow_year_vip`,`yellow_vip_level`,`is_yellow_high_vip` FROM `sys_user_token` WHERE `uid`=%d and `sid`=%d", uid,sid);

		MySqlDBGuard db(DBPOOL);
		MySqlQuery result =	db.query(szSQL);
		if (result.getRowCount() == 1)
		{
			//LOG_INFO("3");
			int32_t nowtime = DayTime::now();
			string dbtoken = result.getStringValue("token");
			int32_t create_time = result.getIntValue("create_time");
			int32_t is_yellow_vip = result.getIntValue("is_yellow_vip");
			int32_t is_yellow_year_vip = result.getIntValue("is_yellow_year_vip");
			int32_t yellow_vip_level = result.getIntValue("yellow_vip_level");
			int32_t is_yellow_high_vip = result.getIntValue("is_yellow_high_vip");
			if (token == dbtoken && abs(nowtime - create_time) < 60*10)
			{
				//LOG_INFO("4");
				User *olduser = findUser(uid, sid);
				if (olduser != NULL)
				{
					//LOG_INFO("5");
					removeUser(uid, sid);
					olduser->setUid(0);
					olduser->setSid(0);

					user->setUid(uid);
					user->setSid(sid);
					addUser(uid, user);

					SERVICE_SERVER.onRemoveUser(olduser->getIndex(), uid, LR_KICK_SELF, 0);
					sendKickOut(olduser->getIndex(), LR_KICK_SELF);

					if (olduser->getGameConn() != NULL)
					{
						//LOG_INFO("6");
						olduser->setGameConn(NULL);
					}
					else
					{
						//LOG_INFO("7");
						if (!openId.empty() && !openKey.empty() && !pf.empty() && !pfKey.empty())
						{
							user->setOpenId(openId);
							user->setOpenKey(openKey);
							user->setPf(pf);
							user->setPfKey(pfKey);

						}
						user->setIsYellowVip(is_yellow_vip);
						user->setIsYellowYearVip(is_yellow_year_vip);
						user->setYellowVipLevel(yellow_vip_level);
						user->setIsYellowHighVip(is_yellow_high_vip);

						SERVICE_SERVER.onAddUser(user->getIndex(), user->getUid(), user->getSid(), conn->getIP());
						sendLineList(conn);
						replySuccess(conn, inPacket->getProc());
					}
				}
				else
				{
					//LOG_INFO("8");
					user->setUid(uid);
					user->setSid(sid);
					if (!openId.empty() && !openKey.empty() && !pf.empty() && !pfKey.empty())
					{
						user->setOpenId(openId);
						user->setOpenKey(openKey);
						user->setPf(pf);
						user->setPfKey(pfKey);

					}

					user->setIsYellowVip(is_yellow_vip);
					user->setIsYellowYearVip(is_yellow_year_vip);
					user->setYellowVipLevel(yellow_vip_level);
					user->setIsYellowHighVip(is_yellow_high_vip);

					addUser(uid, user);
					SERVICE_SERVER.onAddUser(user->getIndex(), user->getUid(), user->getSid(), conn->getIP());
					sendLineList(conn);
					replySuccess(conn, inPacket->getProc());
				}
			}
		}
	}
}


void GateServer::onGateLoginRobot(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{
		inPacket->readInt32();
		int32_t uid = inPacket->readInt32();

		if (uid > 0x1234567)
		{
			user->setUid(uid);
			addUser(uid, user);
			SERVICE_SERVER.onAddUser(user->getIndex(), user->getUid(), 1, conn->getIP());
			replySuccess(conn, inPacket->getProc());
		}
	}
}

void GateServer::onGateSwitchLine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && user->getIndex() > 0 && user->getUid() > 0 && user->getGameConn() != NULL)
	{
		inPacket->readInt32();
		int32_t line = inPacket->readInt32();

		GameServiceConnection game = SERVICE_SERVER.findGameService(line);
		if (game.conn != NULL && game.conn != user->getGameConn() && game.isOpen)
		{
			SERVICE_SERVER.onRemoveUser(user->getIndex(), user->getUid(), LR_SWITCH_LINE, line);
		}
	}
}

void GateServer::onGateQueryLine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && user->getIndex() > 0 && user->getUid() > 0 && user->getGameConn() != NULL)
	{
		sendLineList(conn);
	}
}

void GateServer::onGMLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && !user->isGM())
	{
		std::string name = inPacket->readUTF8(true);
		std::string password = inPacket->readUTF8(true);

		char szSQL[MAX_SQL_LENGTH] = {};
		snprintf(szSQL, sizeof(szSQL)-1, "SELECT `value` FROM `sys_server_config` WHERE `name`='gm_key'");

		MySqlDBGuard db(DBPOOL);
		MySqlQuery result = db.query(szSQL);
		if (!result.eof())
		{
			string key = result.getStringValue("value");
			if (password == MD5().md5sum(name + key))
			{
				user->setIsGM(true);
				replySuccess(conn, inPacket->getProc());
				Answer::MutexGuard lock(m_gmLock);
				m_gmUsers.push_back(user);
				return;
			}
		}
		
		replyFailure(conn, inPacket->getProc(), ERR_WRONG_PASSWORD);
	}
	else
	{
		replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
	}
}

void GateServer::onGMBanLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && user->isGM())
	{
		int32_t action = inPacket->readInt32();
		if (action)//ban
		{
			int32_t uid = inPacket->readInt32();
			std::string name = inPacket->readUTF8(true);
			int32_t expire_time = inPacket->readInt32();
			if (expire_time != 0)
			{
				expire_time += DayTime::now();
			}
			std::string reason = inPacket->readUTF8(true);
			std::string gm_user = inPacket->readUTF8(true);

			char szSQL[MAX_SQL_LENGTH*2] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `gmt_ban_login` (`uid`, `name`, `expire_time`, `reason`, `gm_user`, `operate_time`) VALUES (%d, '%s', %d, '%s', '%s', %d) ON DUPLICATE KEY UPDATE `expire_time`=%d, `reason`='%s', `gm_user`='%s', `operate_time`=%d",
					 uid, name.c_str(), expire_time, reason.c_str(), gm_user.c_str(), DayTime::now(), expire_time, reason.c_str(), gm_user.c_str(), DayTime::now());

			MySqlDBGuard db(DBPOOL);
			db.excute(szSQL);

			replySuccess(conn, inPacket->getProc(), uid);
		}
		else
		{
			int32_t uid = inPacket->readInt32();

			char szSQL[MAX_SQL_LENGTH] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `gmt_ban_login` WHERE `uid`=%d", uid);

			MySqlDBGuard db(DBPOOL);
			db.excute(szSQL);

			replySuccess(conn, inPacket->getProc(), uid);
		}
	}
	else
	{
		replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
	}
}

void GateServer::onGMBanChat(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && user->isGM())
	{
		int32_t action = inPacket->readInt32();
		if (action)//ban
		{
			int32_t uid = inPacket->readInt32();
			std::string name = inPacket->readUTF8(true);
			int32_t expire_time = inPacket->readInt32();
			if (expire_time != 0)
			{
				expire_time += DayTime::now();
			}
			std::string reason = inPacket->readUTF8(true);
			std::string gm_user = inPacket->readUTF8(true);

			char szSQL[MAX_SQL_LENGTH*2] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `gmt_ban_chat` (`uid`, `name`, `expire_time`, `reason`, `gm_user`, `operate_time`) VALUES (%d, '%s', %d, '%s', '%s', %d) ON DUPLICATE KEY UPDATE `expire_time`=%d, `reason`='%s', `gm_user`='%s', `operate_time`=%d", 
					 uid, name.c_str(), expire_time, reason.c_str(), gm_user.c_str(), DayTime::now(), expire_time, reason.c_str(), gm_user.c_str(), DayTime::now());

			MySqlDBGuard db(DBPOOL);
			db.excute(szSQL);

			SERVICE_SERVER.onUpdateBanChat(action, uid, expire_time);

			replySuccess(conn, inPacket->getProc(), uid);
		}
		else
		{
			int32_t uid = inPacket->readInt32();

			char szSQL[MAX_SQL_LENGTH] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `gmt_ban_chat` WHERE `uid`=%d", uid);

			MySqlDBGuard db(DBPOOL);
			db.excute(szSQL);

			SERVICE_SERVER.onUpdateBanChat(action, uid, 0);

			replySuccess(conn, inPacket->getProc(), uid);
		}
	}
	else
	{
		replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
	}
}

void GateServer::onGMBanIp(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && user->isGM())
	{
		int32_t action = inPacket->readInt32();
		if (action)//ban
		{
			int32_t uid = inPacket->readInt32();
			std::string name = inPacket->readUTF8(true);
			int32_t expire_time = inPacket->readInt32();
			if (expire_time != 0)
			{
				expire_time += DayTime::now();
			}
			std::string reason = inPacket->readUTF8(true);
			std::string gm_user = inPacket->readUTF8(true);

			MySqlDBGuard db(DBPOOL);
			
			char szSQL[MAX_SQL_LENGTH*2] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "SELECT `last_login_ip` FROM `sys_user` WHERE `uid`=%d", uid);

			MySqlQuery result = db.query(szSQL);
			if (result.eof())
			{
				return;
			}
			std::string ip = result.getStringValue("last_login_ip");

			bzero(szSQL, sizeof(szSQL));
			snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `gmt_ban_ip` (`uid`, `name`, `expire_time`, `reason`, `ip`,  `gm_user`, `operate_time`) VALUES (%d, '%s', %d, '%s', '%s', '%s', %d) ON DUPLICATE KEY UPDATE `expire_time`=%d, `reason`='%s', `ip`='%s', `gm_user`='%s', `operate_time`=%d", 
					 uid, name.c_str(), expire_time, reason.c_str(), ip.c_str(), gm_user.c_str(), DayTime::now(), expire_time, reason.c_str(), ip.c_str(), gm_user.c_str(), DayTime::now());
			db.excute(szSQL);

			bzero(szSQL, sizeof(szSQL));
			snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `gmt_ban_login` (`uid`, `name`, `expire_time`, `reason`,  `gm_user`, `operate_time`) VALUES (%d, '%s', %d, '%s', '%s', %d) ON DUPLICATE KEY UPDATE `expire_time`=%d, `reason`='%s', `gm_user`='%s', `operate_time`=%d", 
					 uid, name.c_str(), expire_time, reason.c_str(), gm_user.c_str(), DayTime::now(), expire_time, reason.c_str(), gm_user.c_str(), DayTime::now());
			db.excute(szSQL);

			SERVICE_SERVER.onUpdateBanChat(action, uid, expire_time);

			replySuccess(conn, inPacket->getProc(), uid);
		}
		else
		{
			int32_t uid = inPacket->readInt32();

			char szSQL[MAX_SQL_LENGTH] = {};
			snprintf(szSQL, sizeof(szSQL)-1, "DELETE FROM `gmt_ban_ip` WHERE `uid`=%d", uid);

			MySqlDBGuard db(DBPOOL);
			db.excute(szSQL);

			SERVICE_SERVER.onUpdateBanChat(action, uid, 0);

			replySuccess(conn, inPacket->getProc(), uid);
		}
	}
	else
	{
		replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
	}
}
void GateServer::onKickUser(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{
		int32_t uid =  user->getUid();

		MutexGuard lock(m_nmUserLock);

		UserList users = findAllUserNoLock(uid);
		if (!users.empty())
		{
			for (UserList::iterator it = users.begin(); it != users.end(); ++it)
			{
				User *olduser = *it;

				removeUserNoLock(olduser->getUid(), olduser->getSid());

				SERVICE_SERVER.onRemoveUser(olduser->getIndex(), uid, LR_KICK_BY_GM, 0);
				sendKickOut(olduser->getIndex(), LR_KICK_BY_GM);

				olduser->setUid(0);
				olduser->setSid(0);
				olduser->setGameConn(NULL);
				replySuccess(conn, inPacket->getProc());
			}
		}
		else
		{
			replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
		}
	}
}
void GateServer::onGMKickUser(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL && user->isGM())
	{
		int32_t uid = inPacket->readInt32();

		MutexGuard lock(m_nmUserLock);

		UserList users = findAllUserNoLock(uid);
		if (!users.empty())
		{
			for (UserList::iterator it = users.begin(); it != users.end(); ++it)
			{
				User *olduser = *it;

				removeUserNoLock(olduser->getUid(), olduser->getSid());
				
				SERVICE_SERVER.onRemoveUser(olduser->getIndex(), uid, LR_KICK_BY_GM, 0);
				sendKickOut(olduser->getIndex(), LR_KICK_BY_GM);
				
				olduser->setUid(0);
				olduser->setSid(0);
				olduser->setGameConn(NULL);
				
				replySuccess(conn, inPacket->getProc());
			}
		}
		else
		{
			replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
		}
	}
	else
	{
		replyFailure(conn, inPacket->getProc(), ERR_PLAYER_NOT_EXIST);
	}
}

void GateServer::onGMCloseLine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{
		int32_t count = inPacket->readInt32();
		if (count > 0 && count < 8)
		{
			Int32Vector lines;
			for (int32_t i = 0; i < count; ++i)
			{
				int32_t line = inPacket->readInt32();
				if (line > 0)
				{
					lines.push_back(line);
				}
			}
			string token = inPacket->readUTF8(true);

			char szToken[MAX_SQL_LENGTH] = {};
			int32_t offset = 0;
			for (Int32Vector::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				offset += snprintf(szToken+offset, sizeof(szToken)-1-offset, "%d", *it);
			}
			snprintf(szToken+offset, sizeof(szToken)-1-offset, "%s", PRIVATE_KEY);

			if (token == MD5().md5sum(szToken))
			{
				LOG_INFO("receive close line command %d%s\n", count, szToken);
				SERVICE_SERVER.closeLines(lines);
			}
		}
	}
}

void GateServer::onGMReloadItem(Answer::TcpConnection *conn, Answer::NetPacket *inPacket)
{
	if (NULL == conn || NULL == inPacket)
	{
		return;
	}
	User *user = static_cast<User*>(conn->getPtr());
	if (user != NULL)
	{
		string token = inPacket->readUTF8(true);
		if (token == PRIVATE_KEY)
		{
			LOG_INFO("receive reload command\n");
			SERVICE_SERVER.onGMReloadItem();
		}
	}
}

void GateServer::sendLineList(Answer::TcpConnection *conn)
{
	if (conn != NULL)
	{
		GameServiceConnectionVector lines = SERVICE_SERVER.getGameServices();

		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		int32_t count = 0;
		packet->writeInt32(static_cast<int32_t>(count));
		for (GameServiceConnectionVector::iterator it = lines.begin(); it != lines.end(); ++it)
		{
			if (it->isOpen)
			{
				packet->writeInt32(it->line);
				packet->writeInt32(getLineStatus(it->count));
				++count;
			}
		}
		int32_t oldoffset = packet->getWOffset();
		packet->setWOffset(0);
		packet->writeInt32(count);
		packet->setWOffset(oldoffset);
		packet->setType(PACK_DISPATCH);
		packet->setProc(SM_LINE_LIST);
		packet->setSize(packet->getWOffset());
		conn->sendPacket(packet, true);
	}
}

void GateServer::sendKickOut(int16_t index, int32_t reason)
{
	if (index > 0 && index < MAX_CONNECTION)
	{
		NetPacket *packet = popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(reason);
		packet->setType(PACK_DISPATCH);
		packet->setProc(SM_KICK_OUT);
		packet->setSize(packet->getWOffset());
		sendPacketTo(index, packet, true);
	}
}



Answer::TcpConnection* GateServer::findClinetConnByPHP(int32_t uid,int32_t sid,Answer::TcpConnection* pconn)
{
	TcpConnection* pitem=NULL;
	User* pUser=findUser(uid,sid);
	if(pUser!=NULL)
	{
		pUser->setPHPConn(pconn);
		int16_t index=pUser->getIndex();
		pitem=m_conns.find(index);
	}

	return pitem;
}

User* GateServer::findUser(int32_t uid, int32_t sid)
{
	MutexGuard lock(m_nmUserLock);

	Int32UserMap::iterator it = m_nmUsers.find(uid);
	if (it != m_nmUsers.end())
	{
		for (UserList::iterator itUser = it->second.begin(); itUser != it->second.end(); ++itUser)
		{
			if ((*itUser)->getSid() == sid)
			{
				return *itUser;
			}
		}
	}

	return NULL;
}

UserList GateServer::findAllUserNoLock(int32_t uid)
{
	UserList users;

	Int32UserMap::iterator it = m_nmUsers.find(uid);
	if (it != m_nmUsers.end())
	{
		users = it->second;
	}

	return users;
}

void GateServer::addUser(int32_t uid, User *user)
{
	if (uid > 0 && user != NULL)
	{
		MutexGuard lock(m_nmUserLock);
		m_nmUsers[uid].push_back(user);
	}
}

void GateServer::removeUser(int32_t uid, int32_t sid)
{
	MutexGuard lock(m_nmUserLock);

	removeUserNoLock(uid, sid);
}

void GateServer::removeUserNoLock(int32_t uid, int32_t sid)
{
	Int32UserMap::iterator it = m_nmUsers.find(uid);
	if (it != m_nmUsers.end())
	{
		for (UserList::iterator itUser = it->second.begin(); itUser != it->second.end();)
		{
			if ((*itUser)->getSid() == sid)
			{
				it->second.erase(itUser++);
			}
			else
			{
				++itUser;
			}
		}
	}
}

int32_t GateServer::getLineStatus(int32_t count)
{
	if (count <= 20)
	{
		return LS_LIUCHANG;
	}
	else if (count <= 50)
	{
		return lS_LIANGHAO;
	}
	else if (count <= 70)
	{
		return LS_YONGJI;
	}
	else
	{
		return LS_HUOBAO;
	}
}
