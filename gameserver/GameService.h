#pragma once
//////////////////////////////////////////////////////////////////////////
// author:zxj     modify Time: 2012-7-7 / 2019-6-26
// description: 游戏线程处理类 — 2019 多连接架构
//////////////////////////////////////////////////////////////////////////
#include <list>
#include <vector>
#include <map>

#include "Player.h"
#include "User.h"
#include "MutiConn.h"

#define MAX_TREASURE_RECORD_SIZE  10
#define MAX_ONLINE_BROADCAST_COUNT 3
#define MAX_GATE_CONNS             100

typedef std::map<int8_t, std::list<int16_t>> IndexMap;

// Forward declarations for types used before GameService is defined
class GameService;
struct TencentInfo;
struct LogMoYuShiJieReward;

typedef MutiConn<GameService> GameConn;

struct ChatValidate
{
	Answer::NetPacket* SendPacket;
	int32_t Time;
	int64_t CharId;
	int32_t Channel;
	int32_t FamilyId;
	int64_t SendCharId;
	std::list<CharId_t> NeedSender;

	ChatValidate()
		: SendPacket(NULL), Time(0), CharId(0), Channel(0), FamilyId(0), SendCharId(0)
	{
	}
};

class MonsterActivity;
class NpcActivity;
class PlantActivity;
class Trailer;
class GameService
	: public Answer::TcpService
{
public:
	GameService();
	virtual ~GameService();

	// onNetPacket called by MutiConn (NOT a virtual override of TcpService::onNetPacket)
	void onNetPacket(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void startGame(int32_t line);
	void stopGame();

	int32_t getLine();
	void	setId(int32_t id);
	void	setLine(int32_t line);

	// 2019 multi-connection support
	bool	Connect(int8_t index, const std::string& host, int32_t port);
	GameConn* GetConn(int8_t connid);
	int8_t   GetAutoConnId();
	int8_t   GetConnId(CharId_t cid);

	void onPlayerLoaded(PlayerDBData& dbData, int32_t reason = 0, bool isRobot = false);
	void onPlayerLogout(Player *player);
	void onPlayerSaved(int8_t connid, int64_t uid, int32_t sid, int32_t reason, int32_t param, CharId_t cid);

	Answer::NetPacket* popNetpacket(int8_t connid, Answer::PackType packType, uint16_t proc);
	Answer::NetPacket* popNetpacket(int8_t connid, Answer::PackType packType, uint16_t proc, unsigned int buffersize);

	void sendPacket(int8_t connid, Answer::NetPacket* packet);
	void sendPacketTo(int8_t connid, int16_t index, Answer::NetPacket* inPacket);
	int32_t replySuccess(int8_t connid, int16_t index, uint16_t proc, int64_t addon = 0);
	int32_t replyfailure(int8_t connid, int16_t index, uint16_t proc, int32_t errcode, int64_t addon = 0);

	void broadcast(Answer::NetPacket* inPacket);
	void worldBroadcast(Answer::NetPacket* inPacket);
	void broadcast(Answer::NetPacket* inPacket, const CharIdList& cids);
	void broadcastToFamily(Answer::NetPacket* inPacket, FamilyId_t nFamilyId, int32_t nLevel = -1);
	void broadcastActivityState(int32_t nId, int8_t nState);
	void broadFamilyWarIcon();
	void broadCastKiaFuHuoDongIcon();
	void SendOpenBetaIcon();
	void FamilyBroadcast(int32_t nFamilyId, Answer::NetPacket* inPacket);

	void worldBroadcast(int8_t connid, Answer::NetPacket* inPacket);

	void AddPlayer(Player* player, int32_t reason = 0);
	void removePlayer(Player* player);
	Player* getPlayer(CharId_t cid, int32_t nRunnerId, bool bCheck = true);

	void addPet(CObjPet* pPet);
	void removePet(CObjPet* pPet);
	CObjPet* getPet(PetId_t pid, int32_t nRunnerId);

	void addMonster(Monster* monster);
	void removeMonster(Monster* monster);
	Monster* getMonster(EntityId_t unitid, int32_t nRunnerId);

	void addTrailer(Trailer* trailer);
	void removeTrailer(Trailer* trailer);
	Trailer* getTrailer(EntityId_t unitid, int32_t nRunnerId);

	Unit* getUnit(EntityId_t unitid, int32_t unittype, int32_t nRunnerId);

	void saveAllPlayerToDB();

	void onUserPayed(Answer::NetPacket* inPacket);
	void onNewMinuteCome(int32_t minute);
	void OnDaySwitch();
	void onUpdatePay();

	void OnUpdateMail(Answer::NetPacket* inPacket);
	void TeamDungeonEnterDungeon(Dungeon* pDungeon, const CharIdList& lst);
	void broadcastHuoDongDaTingIcon();
	void SendServerDiffToGlobal();
	void requestFamilyInfo();
	void requestSocialData();
	void requestWorldLevel();
	void requestPetRankInfo();

	// Title/CityWar
	void onCheckTitle(CharId_t nCharId, int8_t nType, int32_t nParam);
	void onCheckTeShuTitle(CharId_t nCharId, int8_t nType, int32_t nParam);
	void onRemoveTitle(CharId_t nCharId, int8_t nType);
	void UpdateCityWarTitle(FamilyId_t OldFamilyId, FamilyId_t NewFamilyId);
	void UpdateCityActState(FamilyId_t FamilyId, int8_t ActState);
	void SetFamilyMemberNeedSync(FamilyId_t nFamilyId);
	void GetFamilyMemberInMap(FamilyId_t nFamilyId, int32_t nMapId, CharIdList& lst);
	void broadcastCityWarWinnerLogin(CharId_t Cid, const std::string& strName);

	// Kick
	void KickUser(CharId_t cid, int32_t opWay = 0);
	void KickAll(int32_t opWay = 0);

	// ChatValidate
	bool SendChatValidate(Player* Owner, int32_t Channel, Answer::NetPacket* inPacket);
	void OnChatValidateResult(Answer::NetPacket* inPacket);
	ChatValidate GetChatValidate(int32_t nid, CharId_t CharId);
	void CheckChatValidateChatSend(CharId_t CharId);

	// Drop control
	int32_t GetDropTimes(int32_t nGroupId);
	void AddDropTimes(int32_t nGroupId, int32_t nAddTimes);
	void UpdateDropTimes(int32_t nGroupId, int32_t nTimes);
	void ResetDropTimes();
	void InitDropTimes();
	void ClearDropTimes();
	void OnDropTimesLoaded(Answer::NetPacket* inPacket);
	bool CheckDropLimit(int32_t nGroupId, int32_t nItemId);
	void OnDropRecordLoaded(Answer::NetPacket* inPacket);
	void OnDropRecordSaved();

	// Server battle
	void InitServerBattle();
	void SetServerBattle(int32_t Battle);

	// MoYuShiJie
	void InitMoYuShiJieRecord();
	void SendMoYuShiJieRecord(Player* player);
	void AddMoYuShiJieRecord(const LogMoYuShiJieReward& logReward);

	// Festival
	void ResetFestivalData(int32_t nVersion);

	// Tencent
	void UpdateTencentInfo(CharId_t cid, const TencentInfo* info);

	// Recalc
	void RecalAllPlayerAttr();

	// BanChat
	void OnSocialCityMasterBanChat(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	int32_t GetCityMasterBanChatTime(CharId_t nCharId);

	// DB dispatch
	void OnDBNetPacket(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket);

	// GM Backstage
	void SetWorldLevel(int32_t nLevel);

private:
	// Old compat wrappers (keep existing callers working)
	Answer::NetPacket* popNetpacket(Answer::PackType packType, uint16_t proc);
	Answer::NetPacket* popNetpacket(Answer::PackType packType, uint16_t proc, unsigned int buffersize);

	std::string GetVersion();

	void onAddUser(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onRemoveUser(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onUpdateBanChat(Answer::NetPacket* inPacket);
	void onGMReloadItem(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onAvgLevel(Answer::NetPacket* inPacket);
	void onSocialNetpacket(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onGateDisconnect(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onEnterGame(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket);
	void onEnterGameRobot(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket);
	void onGameNetpacket(int8_t connid, int16_t cgindex, Answer::NetPacket* inPacket);

	void sendSocialAddPlayer(Player* player);
	void sendSocialRemovePlayer(Player* player);
	void qqToPlayer(
		GameConn* pConn,
		Answer::NetPacket* inPacket);

	User* getUser(int8_t connid, int16_t cgindex);
	Player* getUserPlayer(int8_t connid, int16_t cgindex);

	void onSocialUpdatePetRank(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialUpdateFamilyInfo(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialInitPetRank(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialInitRankMirror(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialUpdateRankMirror(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialQueryPlayerInfo(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialCreateTeamDungeon(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialSendSystemMail(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialSendSystemMail2(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onSocialChangeOwner(Answer::NetPacket* inPacket);
	void onSocialUpdateRank(Answer::NetPacket* inPacket);

	void onSocialInitFamilyInfo(
		GameConn* pConn,
		Answer::NetPacket* inPacket);

	void onSetWorldLevel(
		GameConn* pConn,
		Answer::NetPacket* inPacket);

	void OnReceiveDaTiRank(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void OnReceiveDaTiResult(
		GameConn* pConn,
		Answer::NetPacket* inPacket);

	void onUpdateActivityState(
		GameConn* pConn,
		Answer::NetPacket* inPacket);
	void onRequestDropRecord(
		GameConn* pConn,
		Answer::NetPacket* inPacket);

	void AddPlayerVipClubDropTime();

	GameService(const GameService&);
	GameService& operator=(const GameService&);

private:
	int32_t m_line;
	int32_t m_id;               // cross-server id

	std::map<int8_t, GameConn*> m_mConn;

	User* m_users[MAX_GATE_CONNS * MAX_CONNECTION];
	Answer::Mutex m_userLock;

	CharIdPlayerMap m_players;
	Answer::Mutex m_playerLock;

	PetIdObjPetMap m_pets;
	Answer::Mutex m_petsLock;

	EntityIdMonsterMap m_monsters;
	Answer::Mutex m_monstersLock;

	EntityIdTrailerMap m_trailers;
	Answer::Mutex m_trailersLock;

	int32_t m_onLineBroadcast[MAX_ONLINE_BROADCAST_COUNT];

	// ChatValidate
	std::map<int32_t, ChatValidate> m_ChatValidateMap;
	Answer::Mutex m_ChatValidateLock;

	// Drop control
	std::map<int32_t, int32_t> m_dropControl;
	Answer::Mutex m_dropControlLock;

	// Server battle
	int32_t m_serverBattle;
};
#define GAME_SERVICE Answer::Singleton<GameService>::instance()
