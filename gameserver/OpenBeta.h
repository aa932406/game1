#ifndef __TPOC_OPEN_BETA_H__
#define __TPOC_OPEN_BETA_H__

#include "CfgData.h"
#include <vector>
#include <map>
#include <string>

// 公测活动类型
enum OpenBetaActivityType
{
	OB_HUO_YUE_DU		= 1,	// 活跃度
	OB_DAILY_RECHARGE	= 2,	// 每日充值
	OB_DAILY_LIMIT_SHOP	= 3,	// 每日限购
	OB_CHOU_JIANG		= 4,	// 抽奖
	OB_XIAO_FEI_SUM_DRAW= 5,	// 消费抽奖
	OB_BOSS				= 6,	// 世界BOSS
	OB_COLLECT_DROP		= 7,	// 收集掉落
	OB_XIAO_FEI_DRAW	= 8,	// 消费抽
	OB_MYSTERY_SHOP		= 9,	// 神秘商店
	OB_LIAN_RECHARGE	= 10,	// 连充
	OB_CHOU_JIANG_TIMES	= 11,	// 抽奖次数
	OB_WING_LEVEL_UP	= 12,	// 翅膀升级
};

// 商店物品
struct ShopGoods
{
	ShopGoods() : nId(0), nGold(0), nReGold(0), nCount(0), nLeftCount(0) {}
	int32_t		nId;
	int32_t		nGold;
	int32_t		nReGold;
	int32_t		nCount;
	int32_t		nLeftCount;
};

// 烟花排行榜
struct FestivalRank
{
	FestivalRank() : nCid(0), nValue(0) {}
	CharId_t	nCid;
	std::string	strName;
	int32_t		nValue;

	void PackageData(Answer::NetPacket* packet) const
	{
		packet->writeInt64(nCid);
		packet->writeUTF8(strName);
		packet->writeInt32(nValue);
	}
};

inline bool GreaterFestivalRank(const FestivalRank& a, const FestivalRank& b)
{
	if (a.nValue != b.nValue) return a.nValue > b.nValue;
	return a.nCid < b.nCid;
}

class COpenBeta
{
public:
	COpenBeta();
	~COpenBeta();

	// Init
	void			Init(int32_t line);

	// Time checks
	bool			IsInTime(int8_t Type);
	bool			IsOpenBetaTime();
	int32_t			getLeftTime();
	int32_t			GetEndCollectDropTime();

	// Daily callbacks
	void			OnDaySwitch();
	void			OnNewMinute(int32_t nMinute);

	// Icon state
	void			GetIconState(Player* player, IconStateList* IconList);
	void			SendIconState(Player* player);
	void			GetBossIconState(IconStateList* IconList);
	void			SendBossIconState();

	// Activity info
	void			SendActivityInfo(Player* player);

	// Boss
	bool			IsInBossTime();
	void			BossDie(int32_t MonsterId, std::string* p_name, CharId_t Cid);
	void			BroadcastBossKilled(const std::string* name, CharId_t cid);
	void			CheckBoss();

	// Recharge
	int32_t			GetRechargeGift(Player* player, int32_t nIndex);

	// Shop
	int32_t			BuyGiftShopItem(Player* player, int8_t nIndex);
	int32_t			BuyTitleShopItem(Player* player, int8_t nIndex);
	int32_t			BuyShiZhuangShopItem(Player* player, int8_t nIndex);
	int32_t			BuyLiQuan(Player* player, int8_t nIndex);

	// FlopDraw
	int32_t			GetFlopType(int32_t nFlopId);
	bool			CanFlopDraw(Player* pPlayer, int32_t FlopId);
	int32_t			GetMaxFlopTimes(Player* pPlayer);

	// ChouJiang
	int32_t			GetChouJiangType();

	// Online reward
	void			AddOnlineRecord(Player* player);
	bool			canGetOnlineGift(Player* player);
	int32_t			GetOnlineTimeRewardTime(Player* player);
	int32_t			GetOnlineGift(Player* player);

	// YanHua (fireworks)
	void			LoadYanHuaValue();
	void			UpdateYanHuaValue();
	void			AddYanHuaPoint(int32_t Values);
	int32_t			GetYanHuaPointReward(Player* player, int8_t nIndex);

	// XiaoFei sum rank
	void			loadXiaoFeiSumRank();
	void			updateXiaoFeiSumRank(Player* player, int32_t AddValues);
	void			checkXiaoFeiSumRankInvalid(int8_t connid);
	void			checkXiaoFeiSumRank();
	void			sendXiaoFeiSumRankMail();

	// Result
	void			SendResult(Player* pPlayer, int8_t Type, int32_t Index, int32_t param);

private:
	void			updateStartTime();
	void			sendBroadcast(int32_t nBroadId, CharId_t cid, const std::string* name);

private:
	// General config
	int32_t			m_nStartDay;
	int32_t			m_nEndDay;
	int32_t			m_nIcon;
	int32_t			m_nDay;
	int32_t			m_nMinute;

	// Activity time areas
	TimeArea		m_vTimeArea[12];

	// Boss
	int32_t			m_nBossStartBroadcast;
	int32_t			m_nBossEndBroadcast;
	int32_t			m_nBossKillBroadcast;
	int32_t			m_BossMapId;
	int32_t			m_BossX;
	int32_t			m_BossY;
	int32_t			m_BossMid;
	int32_t			m_BossMonsterId;
	bool			m_bBossDie;
	std::vector<TimeArea>	m_vBossMinute;

	// Shop
	std::vector<ShopGoods>	m_GiftShop;
	std::vector<ShopGoods>	m_TitleShop;
	std::vector<ShopGoods>	m_ShiZhuangShop;
	std::vector<ShopGoods>	m_LiQuanShop;

	// Online
	int32_t			m_nOnlineSize;
	std::vector<int32_t>	m_vOnlineValue;
	std::vector<MemChrBagVector>	m_vOnlineGift;

	// Recharge
	int32_t			m_nRechargeDaysSize;
	std::vector<int32_t>	m_vRechargeValue;
	std::vector<MemChrBagVector>	m_vRechargeGift;

	// YanHua
	int32_t			m_CurrYanHuaPoint;
	std::vector<FestivalRank>	m_YanHuaRank;
	std::vector<MemChrBagVector>	m_YanHuaReward;

	// XiaoFei sum
	std::vector<FestivalRank>	m_XiaoFeiSumRank;
	std::vector<MemChrBagVector>	m_XiaoFeiSumReward;

	// ChouJiang
	int32_t			m_ChouJiangType;
	int32_t			m_ChouJiangCount;
};

#define OPEN_BETA Answer::Singleton<COpenBeta>::instance()

#endif // __TPOC_OPEN_BETA_H__
