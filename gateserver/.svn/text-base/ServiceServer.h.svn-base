#pragma once

#include <vector>

class User;

enum ServiceName
{
	SN_CHARACTER,
	SN_GAME,
	SN_LOGIN,
	SN_SOCIAL
};

struct GameServiceConnection 
{
	int32_t line;
	int32_t count;
	bool isOpen;
	Answer::TcpConnection *conn;
};
typedef std::vector<GameServiceConnection> GameServiceConnectionVector;

struct NetProc 
{
	int32_t count;
	int64_t bytes;
};

typedef std::vector<int32_t> Int32Vector;

class ServiceServer
	: public Answer::TcpServer
{
public:
	ServiceServer();
	virtual ~ServiceServer();

public:
	virtual void onConnect(Answer::TcpConnection *conn);
	virtual void onDisconnect(Answer::TcpConnection *conn);
	virtual void onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

public:
	void setAcceptIps(const StringVector &acceptIps);
	bool forPHPToService(ServiceName service, Answer::TcpConnection *fromconn,Answer::NetPacket *inPacket);
	void forwardToService(ServiceName service, Answer::TcpConnection *fromconn, Answer::NetPacket *inPacket);
	void onAddUser(int16_t cgindex, int32_t uid, int32_t sid, const std::string &fromip);
	void onRemoveUser(int16_t cgindex, int32_t uid, LogoutReason reason, int32_t param);
	void onUpdateBanChat(int32_t action, int32_t uid, int32_t expire_time);
	void onGMReloadItem();

	GameServiceConnectionVector getGameServices();
	GameServiceConnection findGameService(int32_t line);
	void closeLines(const Int32Vector &lines);
	void onSwitchGameService(Answer::TcpConnection *pOld, Answer::TcpConnection *pNew);

	void logServerProcs();

private:
	void sendAddUser(Answer::TcpConnection *conn, int16_t cgindex, int32_t uid, int32_t sid, const std::string &fromip);
	void sendRemoveUser(Answer::TcpConnection *conn, int16_t cgindex, int32_t uid, LogoutReason reason, int32_t param);
	void sendUpdateBanChat(Answer::TcpConnection *conn, int32_t action, int32_t uid, int32_t expire_time);
	void sendGMReloadItem(Answer::TcpConnection *conn);

	void onInternalProc(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onServerProc(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onPHPProc(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onCharacterServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onGameServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onLoginServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onSocialServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	
	void onUserSaved(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	void directForward(Answer::TcpConnection *service, Answer::NetPacket *inPacket);
	void forwardToGame(Answer::NetPacket *inPacket);
	void broadcastToGame(Answer::NetPacket *inPacket);
	void forwardToGameLine(Answer::NetPacket *inPacket);

	void addServerProcRecord(int32_t proc, int32_t count, int32_t bytes);

	void sendQQToPlayer(Answer::TcpConnection *conn,int16_t cgindex ,std::string openId ,std::string openKey ,std::string pf ,std::string pfKey,int32_t isYellowVip,int32_t isYellowYearVip,int32_t yellowVipLevel,int32_t isYellowHighVip);

	//void onFlexToKingDom()
	void onGameKickUser(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

private:
	Answer::TcpConnection *m_character;
	GameServiceConnectionVector m_games;
	Answer::RwLock m_gamesLock;
	Answer::TcpConnection *m_gameSocial;
	Answer::TcpConnection *m_login;
	Answer::TcpConnection *m_social;
	NetProc m_netprocs[SM_MAX-SM_MIN+1];

	StringVector m_accetpIps;
};
#define SERVICE_SERVER Answer::Singleton<ServiceServer>::instance()
