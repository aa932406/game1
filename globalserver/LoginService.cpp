#include "stdafx.h"

#include "LoginService.h"

#include <string>

using namespace Answer;
using namespace std;

LoginService::LoginService()
	: TcpService(CLIENT_RECV_BUFFER, CLIENT_RECV_BUFFER, 2048-NET_PACKET_HEAD_LEN, 0, 2000, "LoginService")
{

}

LoginService::~LoginService()
{

}

void LoginService::onNetPacket(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	uint16_t proc = inPacket->getProc();
	if (proc > IM_MIN && proc < IM_MAX)
	{
		//do nothing now
	}
	else
	{
		int16_t pos = static_cast<int16_t>(inPacket->readInt32());
		if (pos > 0)
		{
			switch (proc)
			{
			case CM_USER_LOGIN: onUserLogin(pos, inPacket); break;
			//case CM_USER_JOIN:onUserJoin(pos,inPacket);break;
			default: break;
			}
		}

	}

	inPacket->destroy();
}

void LoginService::onUserLogin(int16_t pos, Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return;
	}
	string passport = inPacket->readUTF8(true);
	int32_t sid = inPacket->readInt32();
	if (passport.empty() || sid <= 0)
	{
		return;
	}

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT `uid` FROM `sys_user` WHERE `passport`='%s' AND `sid`=%d", passport.c_str(), sid);

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query(szSQL);

	int32_t uid = 0;

	if (!result.eof())
	{
		uid = result.getIntValue("uid");
	}
	else
	{
		uid = registerUser(pos, passport, sid);
	}
	realLogin(pos, uid, sid);
}

void LoginService::realLogin(int16_t pos, int32_t uid, int32_t sid)
{
	if (uid <= 0)
	{
		return;
	}

	char szToken[32] = {};
	snprintf(szToken, sizeof(szToken)-1, "%d%d%d", uid, DayTime::now(), rand()%1000);
	string md5token = MD5().md5sum(szToken);

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `sys_user_token` (`uid`,`sid`, `token`, `create_time`) VALUES (%d, %d,'%s', UNIX_TIMESTAMP()) ON DUPLICATE KEY UPDATE `token`='%s', `create_time`=UNIX_TIMESTAMP()",
			 uid,sid, md5token.c_str(), md5token.c_str());

	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);

	NetPacket *packet = popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(uid);
	packet->writeInt32(sid);
	packet->writeUTF8(md5token);
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_USER_TOKEN);
	packet->setSize(packet->getWOffset());
	sendPacketTo(pos, packet);
}

int LoginService::registerUser(int16_t pos, const std::string &passport, int32_t sid)
{
	MySqlDBGuard db(DBPOOL);

	char szSQL[MAX_SQL_LENGTH] = "";
	//snprintf(szSQL, sizeof(szSQL)-1, "SELECT `uid` FROM `sys_user` WHERE `passport`='%s'", passport.c_str());
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT `uid` FROM `sys_user` WHERE `passport`='%s' AND `sid`=%d", passport.c_str(), sid);
	int32_t uid = 0;

	MySqlQuery result = db.query(szSQL);
	if (!result.eof())
	{
		uid = result.getIntValue(0);
	}
	else
	{
		result = db.query("SELECT max(`uid`) FROM `sys_user`");
		if (!result.eof())
		{
			uid = result.getIntValue(0) + 1;
		}
		if (uid > 0)
		{
			bzero(szSQL, sizeof(szSQL));
			snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO `sys_user` (`uid`, `sid`, `passport`, `gold`, `cash`,`gold_pay_total`,`create_time`) VALUES (%d, %d, '%s', 0, 0, 0,UNIX_TIMESTAMP())",
				uid, sid, passport.c_str());
			db.excute(szSQL);
		}
	}

	

	return uid;
}


