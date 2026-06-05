#ifndef __KAI_FU_HUO_DONG_H__
#define __KAI_FU_HUO_DONG_H__
#include "CfgData.h"

struct BossFirstKilled
{
	int32_t		BossId;
	int64_t		Killer;
	std::string	KillerName;
	int32_t		KillTime;
};

struct TimeArea
{
	int32_t nStartTime;
	int32_t nEndTime;
};

struct ShopGoods
{
	int32_t nPrice;
	MemChrBagVector vItem;
};

struct FestivalRank
{
	int64_t nCharId;
	std::string strName;
	int32_t nScore;
	int32_t nTime;
	int8_t bChange;

	FestivalRank() : nCharId(0), nScore(0), nTime(0), bChange(0) {}
};

typedef std::vector<FestivalRank> FestivalRankVector;

class CKaiFuHuoDong
{
public:
	CKaiFuHuoDong();
	~CKaiFuHuoDong();

	// ========== Existing methods ==========
	void				Init();
	int32_t				KaiFuHuoDongOperator( Player* pPlayer, Answer::NetPacket *inPacket );
	int32_t				OnGetReward( Player* pPlayer, Answer::NetPacket *inPacket );
	int32_t				AskInfo( Player* pPlayer, Answer::NetPacket *inPacket );
	void				RecvRank( Answer::NetPacket *inPacket );
	void				SendHuoDongState( Player* pPlayer );
	void				AddRewardRecord( Player* pPlayer, int32_t Index );
	int32_t				CanGetReward( Player* pPlayer, int32_t Index );
	bool				IsAlreadyGet( Player* pPlayer,int32_t Index );
	int32_t				GetRewardState( Player* pPlayer, int32_t Conditions, int32_t Param1, int32_t Param2, int32_t LimitCount );
	void				UpdateHDData( Player* pPlayer,KaiFuHuoDongCondition Type, int32_t Values );
	void				GetKaiFuHuoDongIcon( Player* pPlayer, IconStateList& IconList );
	void				SendKaiFuHuoDongIcon( Player* pPlayer );
	ShowIcon			GetKaiFuHuoDongIconStu( Player *pPlayer );
	void				SendHuoDongInfo( Player* pPlayer,int8_t Type );
	std::string			GetLevelLimitString( int32_t Level );
	int32_t				GetDiffDay();
	void				LoadData();
	void				SaveData();
	bool				InTime();
	void				GongGao( Player* pPlayer, int32_t GongGaoId, int32_t Index );
	int32_t				HaveRewardCount( Player* pPlayer );
	void				OnKilledMonster( Player* pPlayer, int32_t Mid );
	void				OnUpdateKilledMonster( int32_t Mid, CharId_t cid, const std::string& Name, int32_t KillTime );
	void				SendBossFirstKillInfo( Player* pPlayer );
	bool				HaveTeHuiGift( Player* pPlayer );
	bool				HaveBuyPetItem( Player* pPlayer );
	void				GetKaiFuPetIcon( Player* pPlayer, IconStateList& IconList );
	void				SendKaiFuPetIcon( Player* pPlayer );
	int32_t				GetKaiFuPetStartDay();
	int32_t				GetKaiFuPetEndDay();
	int32_t				GetFlopType( int32_t nFlopId );
	bool				CanFlopDraw( Player* pPlayer, int32_t FlopId );
	int32_t				GetMaxFlopTimes( Player* pPlayer );
	int32_t				GetDaysFromServerStart();

	// ========== New methods from COpenBeta ==========
	void				Init( int32_t line );

	// Time checks
	bool				IsInTime( int8_t Type );
	bool				IsOpenBetaTime();
	bool				IsInBossTime();
	int32_t				getLeftTime();

	// Daily callbacks
	void				OnDaySwitch();
	void				OnNewMinute( int32_t nMinute );
	void				updateStartTime();

	// Icon state
	void				GetIconState( Player* player, IconStateList& IconList );
	void				SendIconState( Player* player );
	void				SendActivityInfo( Player* player );

	// Boss methods
	void				GetBossIconState( IconStateList& IconList );
	void				SendBossIconState();
	void				CheckBoss();
	void				BossDie( int32_t MonsterId, std::string* p_name, CharId_t Cid );
	void				BroadcastBossKilled( const std::string* name, CharId_t cid );
	void				broadcastBossStart();
	void				broadcastBossEnd();

	// Recharge
	int32_t				GetRechargeGift( Player* player, int32_t nIndex );

	// Shops
	int32_t			BuyGiftShopItem( Player* player, int8_t nIndex );
	int32_t			BuyTitleShopItem( Player* player, int8_t nIndex );
	int32_t			BuyShiZhuangShopItem( Player* player, int8_t nIndex );
	int32_t			BuyLiQuan( Player* player, int8_t nIndex );

	// Online gift
	void				AddOnlineRecord( Player* player );
	bool				canGetOnlineGift( Player* player );
	int32_t				GetOnlineTimeRewardTime( Player* player );
	int32_t				GetOnlineGift( Player* player );

	// Collect drop
	int32_t				GetEndCollectDropTime();

	// Draw
	int32_t				GetChouJiangType();

	// YanHua
	void				AddYanHuaPoint( int32_t Values );
	void				LoadYanHuaValue();
	void				UpdateYanHuaValue();
	int32_t				GetYanHuaPointReward( Player* player, int8_t nIndex );

	// QianDao
	int32_t				GetQianDaoReward( Player* player, int8_t nIndex, int8_t nType );

	// XiaoFei Sum Rank
	void				loadXiaoFeiSumRank();
	void				updateXiaoFeiSumRank( Player* player, int32_t AddValues );
	void				checkXiaoFeiSumRankInvalid( int8_t connid );
	void				checkXiaoFeiSumRank();
	void				sendXiaoFeiSumRankMail();

	// Result notification
	void				SendResult( Player* pPlayer, int8_t Type, int32_t Index, int32_t param );

private:
	// Helper methods
	void				getIconState( ShowIcon& stu, Player* player );
	void				getBossIconState( ShowIcon& stu );
	void				sendBroadcast( int32_t nBroadId, CharId_t cid, const std::string* name );

	// Limit methods (int32_t and std::string overloads)
	int32_t				GetLimitCount( int32_t index );
	void				AddLimitCount( int32_t index, int32_t Values );
	int32_t				GetLimitCount( std::string LimitString );
	void				AddLimitCount( std::string LimitString, int32_t Values );

private:
	KaiFuHuoDongRank		m_PetRank;
	KaiFuHuoDongRank		m_BattleRank;
	int32_t					m_PetRankEndDay;		
	int32_t					m_BattleRankEndDay;
	int32_t					m_HDLastDay;
	KaiFuHuoDongCfg			m_KaiFuHuoDongCfg;

	Answer::Mutex			m_Lock;
	std::map<int32_t,BossFirstKilled>	m_BossFirstKilledMap;
	std::vector<int32_t>		m_FlopType;
	std::vector<ItemData>		m_FlopCost;
	int32_t					m_FlopFreeTimes;
	int32_t					m_FlopBuyTimes;
	int32_t					m_FlopSize;
	int32_t					m_FlopStartTime;
	int32_t					m_FlopEndTime;

	// ========== New member variables from COpenBeta ==========
	// General config
	int32_t					m_nStartDay;
	int32_t					m_nEndDay;
	int32_t					m_nIcon;
	int32_t					m_nDay;
	int32_t					m_nMinute;
	int32_t					m_vStartDay[18];
	int32_t					m_vEndDay[18];

	// Boss
	int32_t					m_nBossIcon;
	int32_t					m_nBossStartBroadcast;
	int32_t					m_nBossEndBroadcast;
	int32_t					m_nBossKillBroadcast;
	int32_t					m_MapId;
	int32_t					m_X;
	int32_t					m_Y;
	int32_t					m_Mid;
	int32_t					m_MonsterId;
	bool					m_bDie;
	std::vector<TimeArea>	m_vBossMinute;

	// Recharge days
	int32_t					m_nRechargeDaysSize;
	std::vector<int32_t>	m_vRechargeValue;
	std::vector<MemChrBagVector>	m_vRechargeGift;

	// Daily limit shop
	int32_t					m_nDailyLimitShopSize;
	std::vector<ShopGoods>	m_vDailyLimitShopGoods;
	std::vector<int32_t>	m_vDailyLimitShopBroadcast;

	// Title shop
	int32_t					m_nTitleShopSize;
	std::vector<ShopGoods>	m_vTitleShopGoods;
	std::vector<int32_t>	m_vTitleShopBroadcast;

	// ShiZhuang shop
	int32_t					m_nShiZhuangShopSize;
	std::vector<ShopGoods>	m_vShizhuangShopGoods;
	std::vector<int32_t>	m_vShiZhuangShopBroadcast;

	// Online gift
	int32_t					m_nOnlineStartMinute;
	int32_t					m_nOnlineEndMinute;
	int32_t					m_nOnlineTimeArea;
	int32_t					m_nMaxCount;
	MemChrBagVector			m_vOnlineReward;

	// XiaoFei Sum Rank
	int32_t					m_nShowSize;
	int32_t					m_nXiaoFeiSumRankSize;
	int32_t					m_nXiaoFeiSumRankLimit;
	std::vector<int32_t>	m_vXiaoFeiSumRankMail;
	std::vector<MemChrBagVector>	m_vXiaoFeiSumRankReward;
	std::map<int8_t, FestivalRankVector>	m_mXiaoFeiSumRank;

	// OBT_FLOP
	// (m_FlopType/m_FlopCost/m_FlopSize already exist)

	// OBT_LI_QUAN
	int32_t					m_LiQuanSize;
	std::vector<MemChrBag>	m_LiQuanItem;
	std::vector<int32_t>	m_LiQuanPriceVt;
	std::vector<int32_t>	m_LiQuanLimitCount;
	std::vector<ItemData>	m_ItemDataVector;

	// OBT_QIAN_DAO
	int32_t					m_QianDaoSize;
	std::vector<MemChrBag>	m_QianDaoReward;
	std::vector<int32_t>	m_BuQianPrice;

	// OBT_YAN_HUA
	int32_t					m_YanHuaSize;
	std::vector<MemChrBag>	m_YanHuaReward;
	std::vector<int32_t>	m_YanHuaPointVt;
	int32_t					m_CurrYanHuaPoint;

	// CHOU_JIANG
	int32_t					m_ChouJiangType;
};
#define KAI_FU_HUO_DONG Answer::Singleton<CKaiFuHuoDong>::instance()
#endif