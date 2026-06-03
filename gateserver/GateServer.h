#pragma once

#include "User.h"

#include <map>
#include <vector>

enum LineStatus
{
	LS_LIUCHANG = 1,
	lS_LIANGHAO = 2,
	LS_YONGJI = 3,
	LS_HUOBAO = 4,
};

#define PRIVATE_KEY "ef8b71bdedb2fd39a543b2ff7be534ed"

struct OnlineStatus 
{
	int32_t login;
	int32_t active;
	int32_t inactive;
};

typedef std::vector<int16_t> Int16Vector;
typedef std::vector<int32_t> Int32Vector;

typedef std::list<User*> UserList;
typedef std::map<int32_t, UserList> Int32UserMap;

class GateServer
	: public Answer::TcpServer
{
public:
	GateServer();
	virtual ~GateServer();

public:
	void onConnect(Answer::TcpConnection *conn);
	void onDisconnect(Answer::TcpConnection *conn);
	void onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	void sendPacketTo(int16_t pos, Answer::NetPacket *inPacket, bool needEncodeHead);
	void checkSendToGM(Answer::NetPacket *packet);

	void sendPacketToPHP(int16_t pos, Answer::NetPacket *inPacket, bool needEncodeHead);
	void onUserSaved(int32_t uid, int32_t sid, int32_t reason, int64_t wparam, int32_t lparam);
	void onGameKickUser(int32_t uid, int32_t sid);

	Answer::TcpConnection* getUserGameConn(int32_t uid, int32_t sid);
	Int16Vector getUserIndexesInGame();	
	
	OnlineStatus getOnlineStatus();
	
	void OnLoadShieldProtocol();						// 加载屏蔽的协议号
	void OnRecordLoadUi( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );
private:
	bool CheckProtocolShielded( int32_t ProcId );		// 检查协议是否被屏蔽
	void onGateLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGateLoginRobot(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGateSwitchLine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGateQueryLine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	void onGMLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGMBanLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGMBanChat(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGMBanIp(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGMKickUser(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGMCloseLine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGMReloadItem(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	
	void sendLineList(Answer::TcpConnection *conn);
	void sendKickOut(int16_t index, int32_t reason);
	
	
	User* findUser(int32_t uid, int32_t sid);
	UserList findAllUserNoLock(int32_t uid);
	void addUser(int32_t uid, User *user);
	void removeUser(int32_t uid, int32_t sid);
	void removeUserNoLock(int32_t uid, int32_t sid);

	int32_t getLineStatus(int32_t count);
	int32_t getGMSealLeftTime( int32_t uid, int32_t sid );

	void onKickUser(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

public:
	Answer::TcpConnection* findClinetConnByPHP(int32_t uid,int32_t sid,Answer::TcpConnection* pconn);
private:
	Answer::ArrayList<Answer::TcpConnection*> m_conns;
	Answer::ObjectPool<User> m_userPool;

	Int32UserMap m_nmUsers;
	Answer::Mutex m_nmUserLock;


	UserList m_gmUsers;
	Answer::Mutex m_gmLock;

	//zxj 2012 -7-13 修改
	//控制恶意发送协议
	int64_t				m_currentTime;	//当前时间
	uint16_t			m_currentProc;
	Answer::Mutex		m_ShieldProtocolLock;
	std::list<int32_t>	m_ShieldProtocol;	//被屏蔽的协议号
};
#define GATE_SERVER Answer::Singleton<GateServer>::instance()

