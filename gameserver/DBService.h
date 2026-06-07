#pragma once
//////////////////////////////////////////////////////////////////////////
// DBService - multi-connection database service
// Manages multiple MutiConn<DBService> connections to DB server instances
//////////////////////////////////////////////////////////////////////////
#include <map>
#include "MutiConn.h"
#include "actStructs.h"
#include "DataStruct.h"

struct EquipBackRankCfg;
struct WorldBossInfo;
struct FestivalRank;
typedef std::vector<FestivalRank> FestivalRankVector;
struct DropRecord;
struct LogMoYuShiJieReward;
struct LogPlayerLevel;
struct Log360;
struct PacketProcLog;
struct Generallog;
struct UpStartLog;
struct DropLog;
struct ChangeMapLog;
struct NpcFuncLog;
struct TencentInfo;
struct MGLog;

class DBService
{
public:
	DBService();
	virtual ~DBService();

	typedef MutiConn<DBService> ConnType;

	// Multi-connection management
	bool		Connect(int8_t index, const std::string& host, int32_t port);
	ConnType*	GetConn(int8_t index);
	void		Init(int32_t line);

	// Called by MutiConn when a packet arrives
	void		onNetPacket(ConnType* pConn, Answer::NetPacket* inPacket);

public:
	// Player
	void		savePlayer(int8_t connid, int32_t reason, int32_t param, PlayerDBData& dbData);
	void		loadPlayer(int8_t connid, int16_t cgindex, int64_t uid, int32_t sid, int32_t reason = 0);
	void		UpdateLoginTime(int8_t connid, CharId_t cid, int32_t login_time);

	// FengHao (ban/seal)
	void		fengHao(int8_t connid, int8_t Type, int64_t Cid, const std::string& name);

	// Player stay log
	void		LogPlayerStay(int8_t connid, int32_t nTime, int32_t nDay);

	// Equip
	void		insertMemEquip(int8_t connid, const MemEquip& equip, int32_t nReason = 0);
	void		updateMemEquip(int8_t connid, const MemEquip& equip, int32_t nReason = 0);
	void		deleteMemEquip(int8_t connid, const MemEquip& equip, int32_t nReason = 0);

	// Pet
	void		insertMemPet(int8_t connid, const MemPetDBData& pet);
	void		updateMemPet(int8_t connid, const MemPetDBData& pet);
	void		deleteMemPet(int8_t connid, PetId_t nPetId);

	// Task
	void		insertTaskInfo(int8_t connid, const LogTask& task);
	void		updateTaskInfo(int8_t connid, const LogTask& task);

	// Equip logs
	void		insertEquipEnhance(int8_t connid, const LogEquipEnhance& equip);
	void		insertEquipAddgem(int8_t connid, const LogEquipAddGem& equipAddGem);
	void		insertItemCombine(int8_t connid, const LogItemCombine& itemCombine);
	void		insertEquipSmithing(int8_t connid, const LogEquipSmithing& equipSmithing);
	void		insertEquipDismantle(int8_t connid, const LogEquipDismantle& equipDismantle);

	// Dungeon
	void		insertDungeon(int8_t connid, const LogDungeon& dungeon);
	void		updateDungeon(int8_t connid, const LogDungeon& dungeon);

	// Family
	void		insertFamilyCreate(int8_t connid, const LogFamily& family);
	void		insertFamilyJoin(int8_t connid, const LogFamily& family);
	void		updateFamilyOut(int8_t connid, const LogFamily& family);

	// Achievement
	void		insertAchievement(int8_t connid, const LogAchievement& achievement);

	// Yellow stone
	void		insertMemYelloStone(int8_t connid, const MemYellowStone& mys, int16_t type);

	// Boss
	void		InsertBossLog(int8_t connid, const LogBoss& boss);
	void		SaveBossFirstKilled(int32_t BossId, CharId_t Cid, const std::string& Name, int32_t time);

	// Activity
	void		InsertActivityLog(int8_t connid, const LogActivity& activity);

	// Gift
	void		InsertDailyGiftLog(int8_t connid, const LogDailyGift& gift);

	// Item change
	void		insertItemChange(int8_t connid, const LogItemChange& item);

	// MingGe
	void		insertMingGeItem(int8_t connid, const MGLog& logStu);

	// Level up log
	void		logLevelUp(int8_t connid, const LogPlayerLevel& logLevel);

	// Online time
	void		SaveOnlineTime(int8_t connid, CharId_t nCharId, int32_t nDayTime, int32_t nOnlineTime);

	// Artifact
	void		logArtifactAddExp(int8_t connid, const LogArtifactAddExp& artifactAddExp);
	void		logArtifactAddMaxLevel(int8_t connid, const LogArtifactAddMaxLevel& artifactAddMaxLevel);
	void		logArtifactAddQuality(int8_t connid, const LogArtifactAddQuality& artifactAddQuality);

	// Equip detail logs
	void		logEquipAddGemSlotNum(int8_t connid, const LogEquipAddGemSlot& equipAddGemSlot);
	void		logEquipAppendStar(int8_t connid, const LogEquipAppendStar& equipAppendStar);
	void		logEquipCombine(int8_t connid, const LogEquipCombine& equipCombine);
	void		logEquipForge(int8_t connid, const LogEquipForge& equipForge);
	void		logEquipRefreshBind(int8_t connid, const LogEquipRefreshBind& equipRefreshBind);
	void		logEquipRefreshElement(int8_t connid, const LogEquipRefreshElement& equipRefreshElement);
	void		logEquipRefreshFloatAttr(int8_t connid, const LogEquipRefreshFloatAttr& equipRefreshFloatAttr);
	void		logEquipRemoveGem(int8_t connid, const LogEquipRemoveGem& equipRemoveGem);
	void		logEquipRemoveStar(int8_t connid, const LogEquipRemoveStar& equipRemoveStar);
	void		logEquipStrengthen(int8_t connid, const LogEquipStrengthen& equipStrengthen);
	void		logEquipUpgrade(int8_t connid, const LogEquipUpgrade& equipUpgrade);

	// Player login/deal/currency
	void		logPlayerLogin(int8_t connid, CharId_t cid, int32_t action, int32_t time, int32_t MapId = 0);
	void		logPlayerDeal(int8_t connid, CharId_t cid, const std::string& name, int64_t tcid, const std::string& tname, int32_t reason, int32_t money, const std::string& items, int32_t time);
	void		logCurrency(int8_t connid, CharId_t cid, const std::string& name, int32_t nType, int32_t opWay, int32_t nVal, int64_t nParam, int32_t nTime, int64_t LeftVal = 0, int32_t FuLiLevel = 0);

	// MoYuShiJie
	void		logMoYuShiJieReward(int8_t connid, const LogMoYuShiJieReward& logInfo);

	// ShangCheng (shop)
	void		logShangCheng(int8_t connid, CharId_t cid, const std::string& name, int32_t Type, int32_t ShopId, int32_t ItemClass, int32_t ItemId, int32_t ItemCount, int32_t CostGold, int64_t LeftGold, int32_t Time);

	// Platform logs
	void		log360(int8_t connid, const Log360& LogStu);
	void		LogProc(int8_t connid, const PacketProcLog& stu);
	void		logGeneral(int8_t connid, const Generallog& LogStu);
	void		LogUpEquipStar(int8_t connid, const UpStartLog& LogStu);
	void		LogEquipDrop(int8_t connid, const DropLog& LogStu);
	void		LogChangeMap(int8_t connid, const ChangeMapLog& LogStu);
	void		LogNpcFunc(int8_t connid, const NpcFuncLog& LogStu);

	// WorldBoss
	void		SaveWorldBossInfo(const WorldBossInfo& info);

	// Ransom
	void		OnAddRansom(DropEquipInfo& DropEquip);
	void		OnDleRansom(EquipId_t EquipId);
	void		OnUpdateRansom(Answer::NetPacket* inPacket);

	// Mail
	void		OnSendMail(int8_t connid, MailInfo& Mail, const std::string& Param = "", FamilyId_t nFamilyid = 0);
	void		OnSendSysMail(int8_t connid, CharId_t ReceiverId, int32_t SysMailId, const std::string& Param = "", FamilyId_t nFamilyid = 0);
	void		OnSendSysMail(int8_t connid, CharId_t ReceiverId, int32_t SysMailId, const MemChrBagVector& items, int32_t nReason = 2, const std::string& Param = "", FamilyId_t nFamilyid = 0);
	void		OnSendSysMail(int8_t connid, CharId_t ReceiverId, int32_t SysMailId, MemChrBag& item, int32_t nReason = 2, const std::string& Param = "", FamilyId_t nFamilyid = 0);
	void		OnDeleteMail(int8_t connid, int32_t nMailId);
	void		OnUpdateMailInfo(ConnType* pConn, Answer::NetPacket* inPacket);

	// Minute/timer
	void		onNewMinuteCome(int32_t minute);

	// Update pay
	void		OnUpdatePay();

	// CityWar
	void		SaveCityWarResult(int32_t nActId, FamilyId_t nFamilyId, int32_t nWinTime, int32_t nTime,
								CharId_t nLeaderCid, CharId_t First, CharId_t Second, CharId_t Third,
								int32_t nIndex, const std::string& FirstFamilyName,
								const std::string& SecondFamilyName, const std::string& ThirdFamilyName);
	void		onLoadCityWarInfo();

	// CrossTower
	void		SaveCrossTowerResult(int32_t nActId, CharId_t Winner, const std::string& name, int32_t battle, int8_t connid, int32_t time);
	void		onLoadCrossTowerInfo();

	// PeerlessWar
	void		SavePeerlessWarResult(int32_t nActId, CharId_t winner, const std::string& name, int32_t nTime);
	void		onLoadPeerlessWarInfo();

	// FamilyWar (legacy compatibility)
	void		SaveFamilyWarResult(int32_t nActId, FamilyId_t nFamilyId, int16_t nWinTimes, int32_t nTime, const std::string& FamilyName, const std::string& LeaderName);

	// TerritoryWar (legacy compatibility)
	void		SaveTerritoryWarResult(int32_t nActId, const std::string& winners, int32_t nTime);

	// ServerBattle
	void		onLoadServerBattle();

	// DoubleEleven
	void		LoadDoubleElevenRank(int8_t nType, int8_t nDay);
	void		SaveDoubleElevenRank(int8_t connid, int8_t nType, int16_t nDay, int16_t nIndex, const FestivalRank& info);

	// ZHYYHD
	void		LoadZHYYHDRank(int8_t nType, int8_t nDay);
	void		SaveZHYYHDRank(int8_t connid, int8_t nType, int16_t nDay, const FestivalRankVector& vRank);

	// DropTimes
	void		SaveDropTimes(int32_t nGroupId, int32_t nTimes);
	void		ClearDropTimes();

	// DropRecord
	void		SaveDropRecord(const DropRecord& record);

	// Tencent
	void		ReloadTencentInfo(int8_t connid, CharId_t cid);

	// Mobile phone gift
	void		CheckMobilePhoneGiftEffect(int8_t connid, int16_t cgindex, int32_t sid, const std::string& passport, int8_t nType);

	// Guard privilege
	void		CheckGuardPrivilege(int8_t connid, int16_t cgindex, int64_t uid, int32_t sid, int8_t type, int32_t param, int8_t index);

	// DBClick game
	void		OnDBClickGame(int8_t connid, int64_t uid, int32_t sid, int32_t start_time);

	// Equip back
	void		SaveEquipBackCount(int32_t nId, int8_t nType, int32_t nCount, std::string& name);
	void		SaveEquipBackRecord(int32_t nId, int8_t nType, int32_t nTime, std::string& name);

	// GuiGuDaoRen
	void		SaveGuiGuDaoRenData(int32_t NpcId, int32_t Count);
	void		SaveGuiGuBackEquipCount(int32_t Count);
	void		SaveGuiGuBackEquipRank(EquipBackRankCfg* p_stu);

private:
	// DB response handlers
	void		onDBPlayerLoaded(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onDBPlayerSaved(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onDBEquipUpdated(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onDBUserPayed(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onDBPetUpdated(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onDBPetDeleted(ConnType* pConn, Answer::NetPacket* inPacket);

	// 2019 new response handlers
	void		onUpdateMYSJReward(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onCityWarInfoLoaded(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onPeerlessWarInfoLoaded(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onCrossTowerInfoLoaded(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onServerBattleLoaded(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateCityWarResult(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateKaiFuTime(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateGMBroadcast(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateGMBanChat(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateGMSeal(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onBackStageKick(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateCrossTowerResutl(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdatePeerlessWarResult(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateBossFirstKilled(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateWorldBossInfo(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateEquipBackRecord(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateEquipBackInfo(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateDoubleElevenRank(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateZHYYHDRank(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateDropTimes(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateTencentInfo(ConnType* pConn, Answer::NetPacket* inPacket);

	// Legacy handlers (for backward compatibility)
	void		onUpdateFamilyWarResult(ConnType* pConn, Answer::NetPacket* inPacket);
	void		onUpdateTerritoryWarResult(ConnType* pConn, Answer::NetPacket* inPacket);

	// GM backstage
	void		onLoadGMBackstage();

	// Player packet forwarding
	void		onPlayerNetPacket(ConnType* pConn, Answer::NetPacket* inPacket);

private:
	std::map<int8_t, ConnType*> m_mConn;
};

#define DB_SERVICE Answer::Singleton<DBService>::instance()
