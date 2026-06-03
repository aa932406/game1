#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>
#include "DataStruct.h"

typedef std::vector<int32_t> Int32Vector;

class DBServer
	: public Answer::TcpServer
{
public:
	DBServer();
	virtual ~DBServer();

public:
	virtual void onConnect(Answer::TcpConnection *conn);
	virtual void onDisconnect(Answer::TcpConnection *conn);
	virtual void onNetPacket(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

public:
	void setAcceptIps(const StringVector &acceptIps);
	void onSaveOver( CharId_t cid );

private:
	void onDBGameServiceConnect(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLoadPlayer(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBSavePlayer(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertEquip(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBUpdateEquip(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBDeleteEquip(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onUpdateLoginTime(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	//void onDBUpdateFamilyWar(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/*  pet  */
	void onDBInsertPet(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBUpdatePet(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBDeletePet(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	void broadcastPetUpdated(const MemPetDBData &pet, Answer::TcpConnection *except);
	void broadcastPetDeleted(PetId_t nPetId, Answer::TcpConnection *except);

	/*  task  */
	void onDBInsertTask(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBUpdateTask(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/*  equip  */
	void onDBInsertEquipEnhance(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertEquipAddGem(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertItemCombine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertEquipSmithing(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertEquipDismantle(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/*  dungeon    */
	void onDBInsertDungeon(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBUpdateDungeon(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/*   family   */
	void onDBInsertFamilyCreate(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertFamilyJoin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBUpdateFamilyOut(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/*  achievement   */
	void onDBInsertAchievement(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/* boss */
	void onDBLogKillBoss(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	/* gift */
	void onDBLogDailyGift(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);

	void onDBLogArtifactAddExp(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogArtifactAddMaxLevel(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogArtifactAddQuality(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertItemChange(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipAddGemSlot(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipAppendStar(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipCombine(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipForge(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipLife(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipRefreshBind(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipRefreshElement(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipRefreshFloatAttr(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipRemoveGem(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipRemoveStar(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipStrengthen(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogEquipUpgrade(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogActivityData(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogCurrency( Answer::TcpConnection* conn, Answer::NetPacket* inPacket );
	void onDBLogPlayerLogin(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBLogPlayerDeal(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBUserPay(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void onDBInsertMemYellowStone(Answer::TcpConnection *conn, Answer::NetPacket *inPacket);
	void addConn(Answer::TcpConnection *conn);
	void removeConn(Answer::TcpConnection *conn);

	void broadcastEquipUpdated(const MemEquip &equip, Answer::TcpConnection *except);
	void broadcastEquipUpdated(const MemEquipVector &equips, Answer::TcpConnection *except);

	//void broadcastFamilyWarUpdated(int32_t family_id, std::string family_name, Answer::TcpConnection *except);

	void broadcastUserPayed(int32_t uid, int32_t sid, Answer::TcpConnection *except);

	void OnUpdateRansom( Answer::TcpConnection *conn, DropEquipInfo& DropEquip );
	void OnUpdateRansom( Answer::TcpConnection *conn, EquipId_t EquipId );
	void onDbDleRansom( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );
	void onDBAddRansom( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );

	void onNewMinuteCome( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );
	void onInsertMailToDB( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );
	void SendNewMailToGame( MailInfo& Mail );
	void UpdateNewMail();
	std::string GetItemString( MemChrBag & Item );
	MemChrBag ParesChrBagString( std::string ItemString );

	void onSaveFamilyWarResult( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );
	void broadcastFamilyWarResult( int32_t nActId, FamilyId_t nFamilyId, int16_t nWinTimes,string FamilyName, string LeadyerName, Answer::TcpConnection *except );

	void onSaveTerritoryWarResult( Answer::TcpConnection *conn, Answer::NetPacket *inPacket );
	void broadcastTerritoryWarResult( int32_t nActId, string winners, Answer::TcpConnection *except );

	void updateBroadcast();		// 更新公告
	void updateBanChat();		// 更新禁言
	void updateSeal();			// 更新封号

	void sendGameBroadcasts( const GMBroadcastList& broadcasts );
	void sendGameBanChat( const GMBanChatList& banchat );
	void sendGameSeal( const GMSealList& seals );

private:
	typedef std::list<Answer::TcpConnection*> TcpConnectionList; //连接列表
	TcpConnectionList m_conns;
	Answer::Mutex m_connsLock;
	StringVector m_accetpIps;

	std::map<CharId_t,Answer::TcpConnection*>	m_PlayerConnection;
	Answer::Mutex m_PlayerConnLock;

	std::map<CharId_t,PlayerDBData> m_PlayerDBData;
	Answer::Mutex m_PlayerDBDataLock;

	//zxj 2012 -7-13 修改
	//控制恶意发送协议
	int64_t m_currentTime;	//当前时间
	uint16_t	m_currentProc;
};
#define DB_SERVER Answer::Singleton<DBServer>::instance()

