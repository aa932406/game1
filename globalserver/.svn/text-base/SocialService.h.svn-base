#pragma once

#include "SocialPlayer.h"
#include <vector>
#include "DataStructs.h"
using namespace std;

typedef Answer::ObjectPool<SocialPlayer> SocialPlayerPool;
typedef Answer::ObjectPool<PlayerInfo> PlayerInfoPool;

class SocialService
	: public Answer::TcpService
{
public:
	SocialService();
	virtual ~SocialService();

public:
	virtual void onNetPacket(Answer::NetPacket *inPacket);

public:
	void startSocial();
	void stopSocial();

	//int32_t getCidByName(const std::string &name);

	//int32_t getPlayerFamilyId(int32_t cid);
	//FamilyInfo* getFamilyInfoByCid(int32_t cid);
	//FamilyInfo* getFamilyInfo(int32_t fid);
	//CfgFamilyLevel* getCfgFamilyLevel(int32_t level);
	//void  getFamilyRewardList(int32_t type,int32_t kingdom,FamilyRewardInfoVector rewardInfo);
	void getActivityRank(ActivityRankVector **activityRank);
	//void clearFamilyApply(int32_t cid);

	//int32_t setFamilyInfo(FamilyInfo* family, FamilyInfoIndex key, int32_t value,int16_t kingdom=0);
	//FamilyMemberInfo* getMemberInfo(FamilyInfo* family, int32_t cid);
	//int32_t getPositionCount(FamilyInfo* family, int32_t pos);

	//int32_t setMemberInfo(FamilyInfo* family, int32_t cid, int32_t pos, int32_t contri);
	//int32_t setMemberInfo(FamilyInfo* family, int32_t cid, FamilyMemberIndex key, int32_t value);
	//int32_t addMemberInfo(FamilyInfo* family, int32_t cid, FamilyMemberIndex key, int32_t addon);
	//int32_t removeMemberInfo(FamilyInfo* family, int32_t cid, bool update);

	//int32_t addFamily(int32_t cid, std::string name,std::string notice);

	//int32_t	getFamilyTotal(int32_t nKingDomId); //获取本国的帮派的数目
	//int32_t addFamilyMember(FamilyInfo* family, int32_t cid, const std::string &name,int pos);
	//int32_t addFamilyApplier(const Int32Vector &nums, int32_t cid, int32_t ckingdom ,Int32Int32Map & applyFid);
	//void    removeAllFamilyApplier(int32_t tcid);
	//int32_t removeFamilyApplier(FamilyInfo* family, int32_t cid);
	//int32_t approveFamilyApply(int32_t fid, int32_t cid, int32_t tcid, int32_t result);
	//void  loadFamilyApply(Int32Int32Map &familyApply,int32_t cid);
	//bool hasFamilyApplier(FamilyInfo* family, int32_t cid);
	//int32_t appointFamily(int32_t fid, int32_t cid, int32_t tcid, int32_t pos);
	//int32_t changeNameFamily(int32_t fid, int32_t cid, std::string name);
	//int32_t kickFamily(int32_t fid, int32_t cid, int32_t tcid);
	//int32_t breakFamily(int32_t fid, int32_t cid);
	//int32_t breakFamily(FamilyInfo* family);
	//int32_t leaveFamily(int32_t fid, int32_t cid);
	//int32_t openFamilyMap(int32_t fid, int32_t cid);
	//int32_t shakeFamilyTree(int32_t fid, int32_t cid, int& money);

	//bool isStoreItemEmpty(int32_t fid, int32_t slot_id);
	//int32_t addStoreItem(int32_t fid, int32_t slot_id, const MemChrBag &bagdata);
	//int32_t removeStoreItem(int32_t fid, int32_t slot_id);
	//MemChrBag getStoreItem(int32_t fid, int32_t slot_id);
	//int32_t reorderStoreItem(int32_t fid, int32_t slot_id, int32_t slot_id2);
	//int32_t addFamilyContribution(int32_t fid, int32_t cid, int32_t addon, int32_t rate);
	//int32_t  addSelfFamilyContribute(FamilyInfo*pFamily,int32_t cid,int32_t addon);
	
	//int32_t sendFamilyList(int32_t cgindex, int32_t kingdom,Int32Int32Map &familyApply);
	void sendLimitShop(int32_t cgindex);

	int32_t getCreateTime();

	//void broadcastFamilyApply(int32_t fid, std::string name);
	//void broadcastFamilyApprove(int32_t fid, int32_t cid, std::string name, std::string fname);
	//void broadcastFamilyLeave(int32_t fid, int32_t cid, std::string name);
	//void broadcastFamilyKick(int32_t fid, int32_t cid, std::string name, std::string tname);
	//void broadcastFamilyAppoint(int32_t fid, int32_t cid, int32_t pos, std::string name, std::string tname);
	//void broadcastFamilyOpenMap(int32_t fid, std::string name);
	//void broadcastFamilyDonateCard(int32_t fid, std::string name, int32_t addon);
	//void broadcastFamilyActivity(int32_t fid);
	//void broadcastFamilyLeaderDown(int32_t fid,int32_t cid,const std::string name,int32_t tcid,const std::string tname);
	//void broadcastFamilySetRewardRatio(int32_t fid,int32_t index);

	bool isBanChat(int32_t uid);
	//void getFamilyList(FamilyRankVector* plist,KDMSRVECTOR* pResult);
	int32_t GetServerDiffDay();

	void SendSystemMail( CharId_t nReceiver, int32_t nMailId, const MemChrBag& item );
	void SendSystemMail( CharId_t nReceiver, int32_t nMailId, const ItemDataList& items );
private:
	void initFamily();
	//void initRealTimeRank();
	void fetchActivity();
	//void fetchFamilyLevel();
	void fetchGiftLimit();
	void fetchGMAnnouncement();
	void fetchBanChat();
	void fetchCreateTime();
	void fetchNewServerActivity();
	//void fetchViceGeneral();
	void InitShangChengTable();		//初始化商城表

	MemChrBagVector parseItemString(int32_t id, const std::string &strItems);
	void parseItemString(MemChrBagVector & items,const std::string &strItems);
	void onGMReloadInfo(Answer::NetPacket *inPacket);
	void onUpdateBanChat(Answer::NetPacket *inPacket);
	//void onAddPlayerInfo(Answer::NetPacket *inPacket);
	void onUpdatePlayerInfo(Answer::NetPacket *inPacket);
	//void onRemovePlayerInfo(int32_t cid);
	void onAddPlayer(Answer::NetPacket *inPacket);
	//void onUpdateGambleRecord(Answer::NetPacket *inPacket);
	//void onFamilyActivityPlayer(Answer::NetPacket *inPacket);
	//void onWorldBossActivityResult(Answer::NetPacket *inPacket);
	void onRemovePlayer(Answer::NetPacket *inPacket);
	void onNewMinuteCome(Answer::NetPacket *inPacket);
	//void onFamilyWar(Answer::NetPacket *inPacket);
	void onActivityClear(Answer::NetPacket *inPacket);
	//void sendAddFamilyApplier(int32_t kingdom,int32_t cid,int32_t fid);

	void onUpdatePetData(Answer::NetPacket *inPacket);
	void onDeletePetData(Answer::NetPacket *inPacket);
	void onUpdateServerDiffDay( Answer::NetPacket *inPacket );
	void onRequestPetRankData( Answer::NetPacket* inPacket );
	void onUpdateFamilyInfo( Answer::NetPacket* inPacket );
public:
	void broadcast( const Int16Vector& indexes, Answer::NetPacket *inPacket );
	//void familyBroadcast(int32_t family, int32_t level, Answer::NetPacket *inPacket);
	//void familyExcludeBroadcast(int32_t family, int32_t level, Answer::NetPacket *inPacket);
	//void GetPlayerVector(SocialPlayer* pPlayer, std::list<FriendInfo>& FriendList, int32_t MinLeve, int32_t MaxLevel );
	//void UpdatePetRankBattleToGameServer( PetId_t nPetId, int32_t nAddBattle );
	void worldBroadcast(Answer::NetPacket *inPacket);
private:
	void checkGMAnnouncement();
	void refreshRanks(bool sendTitle);

//全服限制商店
public:
	void				PacketItemLimitInfo( Answer::NetPacket *inPacket );
	int32_t				GetLimitCount( int32_t ShopId );
	void				AddLimitCount( int32_t ShopId, int32_t AddCount );
	void				RefreshLimitInfo();

	CfgGameShop*		GetCfgGameShop( int32_t ShopId );
private:
	Answer::Mutex   m_limitShopLock;
	ItemLimitMap	m_ItemLimitMap;			//全服限购物品
	GameShopMap		m_ShopCfg;

private:
	//CfgKingdomPostVector  m_kingdomPost;
	CfgActivityTable m_activity;
	//CfgFamilyLevelTable m_familyLevel;

	int32_t m_lastRankTime;
	int32_t m_secondRecord;
	int32_t m_serverdiffDay;
	//gamble
	//GambleRecord  m_gambleRecord[MAX_GAMBLE_RECORD];
	//int32_t       m_gambleIndex;
	//int32_t       m_gambleSecondIndex;

	GmtAnnouncementTable m_gmAnnouncements;

	//Int32FamilyInfoMap m_fidFamilyInfo;
	//Answer::Mutex m_familyInfoLock;

	//TeamDungeonList m_teamDungeon;
	//Answer::Mutex m_teamDungeonLock;

	int32_t m_newServerTime;

	GmtBanChatTable m_banChats;

	int32_t m_createTime;
	int32_t m_mysteriousShopGroup;
	Int32Vector m_mysteriousRefreshTime;

	ActivityRankVector m_activityRank;
	//CfgViceGeneralBaseTable m_viceGeneralBases;
	//CfgEquipMap m_equips;


	// Player
	//PlayerInfoPool			m_playerPool;
	//Int32PlayerInfoMap		m_cidPlayerInfo;
	//StringPlayerInfoMap		m_namePlayerInfo;

	//SocialPlayerPool		m_playerPool;
	//Int32SocialPlayerMap	m_playerByCid;
	//Int32SocialPlayerMap	m_playerByGateIndex;
};
#define SOCIAL_SERVICE Answer::Singleton<SocialService>::instance()
