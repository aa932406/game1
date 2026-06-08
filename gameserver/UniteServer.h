#ifndef __UNITE_SERVER_H__
#define __UNITE_SERVER_H__

#include "CfgData.h"

// 合服活动类型
enum UnitServerActivityType
{
	US_HUO_YUE_DU			= 1,	// 活跃度
	US_DAILY_RECHARGE		= 2,	// 每日充值
	US_DAILY_LIMIT_SHOP		= 3,	// 每日限购
	US_CHOU_JIANG			= 4,	// 抽奖
	US_XIAO_FEI_SUM_DRAW	= 5,	// 消费抽奖
	US_BOSS					= 6,	// 世界BOSS
	US_COLLECT_DROP			= 7,	// 收集掉落
	US_XIAO_FEI_DRAW		= 8,	// 消费抽
	US_MYSTERY_SHOP			= 9,	// 神秘商店
	US_LIAN_RECHARGE		= 10,	// 连充
	US_CHOU_JIANG_TIMES		= 11,	// 抽奖次数
	US_WING_LEVEL_UP		= 12,	// 翅膀升级
};

struct TimeArea
{
	int32_t nStartTime;
	int32_t nEndTime;
};

struct LianRechargeCfg
{
	int32_t nDay;
	int32_t nGold;
	MemChrBagVector vReward;
};

class CUniteServer
{
public:
	CUniteServer();
	~CUniteServer();

	// Init
	void			Init( int32_t line );

	// Time checks
	bool			IsInUnitServerTime();
	bool			IsInTime( UnitServerActivityType nType );
	bool			IsInSpiderQueenTime();
	bool			IsInMysteryShopTime();
	int32_t			getLeftTime();

	// Daily callbacks
	void			OnDaySwitch();
	void			OnNewMinute( int32_t nMinute );

	// Icon state
	void			GetIconState( Player* player, IconStateList& IconList );
	void			SendIconState( Player* player );
	void			GetSpiderQueenIconState( IconStateList& IconList );
	void			SendSpiderQueenIconState();
	void			SendUniteServerInfo( Player* player );

	// Boss (SpiderQueen)
	void			checkSpiderQueen();
	void			BossDie( int32_t MonsterId, std::string* p_name, CharId_t Cid );
	void			BroadcastSpiderQueenKilled( const std::string* name, CharId_t cid );
	void			broadcastSpiderQueenStart();
	void			broadcastSpiderQueenEnd();

	// Recharge
	int32_t			GetRechargeGift( Player* player, int32_t nIndex );

	// LianRecharge
	int32_t			GetLianRechargeReward( Player* player, int32_t nIndex );

	// Discount shop
	int32_t			BuyDiscountGift( Player* player, int16_t nIndex );

	// HuoYueDu
	int32_t			GetHuoYueDuGift( Player* player, int32_t nIndex );
	void			AddHuoYueDu( Player* player, int32_t nValue );

	// Mystery shop
	bool			RefreshMysteryShopItem( Player* player );
	void			checkMysteryShopRefreshBroad();

	// Wing level up
	int32_t			GetWingLevelUpGift( Player* player, int32_t nIndex );
	int32_t			GetWingLevelUpRewardCount( Player* player );
	void			AddWingLevelUp( Player* player );

	// XiaoFei draw
	int32_t			GetCanXiaoFeiDrawTime( Player* player );
	void			AddXiaoFeiValue( Player* player, int32_t nValue );

	// ChouJiang
	int32_t			GetChouJiangType();
	int32_t			GetChouJiangSpecialTime();
	int32_t			OnGetChouJiangReward( Player* player );
	void			OnAddChouJiangTimes( Player* player, int32_t nCount );

	// Other
	int32_t			BuyChangeNameCard( Player* player );
	int32_t			GetEndCollectDropTime();
	void			OnRecharge( Player* player, int32_t nGold );
	void			GongGao( Player* pPlayer, int32_t GongGaoId, int32_t Index );

	// Info helpers
	void			appendRechargeInfo( Answer::NetPacket* packet, Player* player );
	void			appendDiscountGiftInfo( Answer::NetPacket* packet, Player* player );
	void			appendHuoYueDuInfo( Answer::NetPacket* packet, Player* player );

private:
	void			getIconState( ShowIcon& stu, Player* player );
	void			getSpiderQueenIconState( ShowIcon& stu );
	void			sendBroadcast( int32_t nBroadId, CharId_t cid, const std::string* name );

private:
	// General config
	int32_t			m_nStartDay;
	int32_t			m_nEndDay;
	int32_t			m_nIcon;
	int32_t			m_nDay;
	int32_t			m_nMinute;
	int32_t			m_vStartDay[18];
	int32_t			m_vEndDay[18];

	// Boss (SpiderQueen)
	int32_t			m_nSpiderQueenStartBroadcast;
	int32_t			m_nSpiderQueenEndBroadcast;
	int32_t			m_nSpiderQueenKillBroadcast;
	int32_t			m_MapId;
	int32_t			m_X;
	int32_t			m_Y;
	int32_t			m_Mid;
	int32_t			m_MonsterId;
	bool			m_bDie;
	std::vector<TimeArea>	m_vSpiderQueenMinute;

	// HuoYueDu
	int32_t			m_nHuoYueSize;
	std::vector<int32_t>	m_vHuoYueValue;
	std::vector<MemChrBagVector>	m_vHuoYueGift;

	// Recharge
	int32_t			m_nRechargeDaysSize;
	std::vector<int32_t>	m_vRechargeValue;
	std::vector<MemChrBagVector>	m_vRechargeGift;

	// XiaoFei draw
	int32_t			m_XiaoFeiDrawSize;
	std::vector<int32_t>	m_nXiaoFeiDrawValue;

	// Mystery shop
	int32_t			m_nMysteryShopRefreshBroad;
	int32_t			m_sMysteryShopRefreshCost;

	// Wing level up
	int32_t			m_nSize;
	std::vector<int32_t>	m_UseItemCount;
	std::vector<MemChrBag>	m_Items;

	// Change name card
	int32_t			m_nPrice;
	MemChrBag		m_Item;

	// LianRecharge
	std::vector<LianRechargeCfg>	m_LianRechargeCfgVt;

	// ChouJiang
	int32_t			m_ChouJiangType;
	int32_t			m_ChouJiangCount;
};

#define UNITE_SERVER Answer::Singleton<CUniteServer>::instance()

#endif
