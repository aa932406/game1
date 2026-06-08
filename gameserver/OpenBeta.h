#ifndef __TPOC_OPEN_BETA_H__
#define __TPOC_OPEN_BETA_H__

#include "CfgData.h"
#include <vector>
#include <map>
#include <string>
#include <mutex>

// 公测活动时间索引（用于 m_vStartDay/m_vEndDay 数组下标）
enum OpenBetaTimeType
{
	OBTT_ONLINE_REWARD	= 1,	// 在线奖励 (RED_PACK)
	OBTT_RECHARGE		= 2,	// 每日充值
	OBTT_DAILY_LIMIT_SHOP	= 3,	// 每日限购
	OBTT_CHOU_JIANG		= 4,	// 抽奖
	OBTT_XIAO_FEI_SUM_RANK	= 5,	// 消费排行
	OBTT_TITLE_SHOP		= 6,	// 称号商店
	OBTT_SHI_ZHUANG_SHOP	= 7,	// 时装商店
	OBTT_COLLECT_DROP	= 8,	// 收集掉落
	OBTT_BOSS			= 9,	// 世界BOSS
	OBTT_LI_QUAN		= 10,	// 礼券
	OBTT_FLOP			= 11,	// 翻牌
	OBTT_QIAN_DAO		= 12,	// 签到
	OBTT_YAN_HUA		= 13,	// 烟花
	OBTT_GUO_QING_TASK	= 16,	// 国庆任务
	OBTT_GUO_QING_REWARD	= 17,	// 国庆奖励
	OBTT_MAX			= 18,
};

// 商店物品（2019版）
struct ShopGoods
{
	ShopGoods() : nPrice(0) {}
	int32_t			nPrice;
	MemChrBagVector		vItem;
};

// 排行榜条目（2019版，支持多连接）
struct FestivalRank
{
	FestivalRank() : nCharId(0), nScore(0), nTime(0), bChange(false) {}
	CharId_t		nCharId;
	std::string		strName;
	int32_t			nScore;
	int32_t			nTime;
	bool			bChange;

	void PackageData(Answer::NetPacket* packet) const
	{
		packet->writeInt64(nCharId);
		packet->writeUTF8(strName);
		packet->writeInt32(nScore);
	}
};

typedef std::vector<FestivalRank> FestivalRankVector;

inline bool GreaterFestivalRank(const FestivalRank& a, const FestivalRank& b)
{
	if (a.nScore != b.nScore) return a.nScore > b.nScore;
	return a.nCharId < b.nCharId;
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

	// QianDao (check-in)
	int32_t			GetQianDaoReward(Player* player, int8_t nIndex, int8_t nType);

	// XiaoFei sum rank (multi-conn aware)
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
	void			broadcastBossStart();
	void			broadcastBossEnd();
	void			getIconState(ShowIcon* pIcon, Player* player);
	void			getBossIconState(ShowIcon* pIcon);

private:
	// General config
	int32_t			m_nStartDay;
	int32_t			m_nEndDay;
	int32_t			m_nIcon;
	int32_t			m_nDay;
	int32_t			m_nMinute;
	int32_t			m_vStartDay[OBTT_MAX];
	int32_t			m_vEndDay[OBTT_MAX];

	// Boss
	int32_t			m_nBossIcon;
	int32_t			m_nBossStartBroadcast;
	int32_t			m_nBossEndBroadcast;
	int32_t			m_nBossKillBroadcast;
	int32_t			m_MapId;
	int32_t			m_X;
	int32_t			m_Y;
	int32_t			m_Mid;
	int32_t			m_MonsterId;
	bool			m_bDie;
	std::vector<TimeArea>	m_vBossMinute;

	// Daily limit shop
	int32_t			m_nDailyLimitShopSize;
	std::vector<ShopGoods>	m_vDailyLimitShopGoods;
	std::vector<int32_t>	m_vDailyLimitShopBroadcast;

	// Title shop
	int32_t			m_nTitleShopSize;
	std::vector<ShopGoods>	m_vTitleShopGoods;
	std::vector<int32_t>	m_vTitleShopBroadcast;

	// ShiZhuang shop
	int32_t			m_nShiZhuangShopSize;
	std::vector<ShopGoods>	m_vShizhuangShopGoods;
	std::vector<int32_t>	m_vShiZhuangShopBroadcast;

	// Online reward
	int32_t			m_nOnlineStartMinute;
	int32_t			m_nOnlineEndMinute;
	int32_t			m_nOnlineTimeArea;
	MemChrBagVector		m_vOnlineReward;
	int32_t			m_nMaxCount;

	// Recharge
	int32_t			m_nRechargeDaysSize;
	std::vector<int32_t>	m_vRechargeValue;
	std::vector<MemChrBagVector>	m_vRechargeGift;

	// ChouJiang
	int32_t			m_ChouJiangType;

	// XiaoFei sum rank (multi-conn)
	int32_t			m_nShowSize;
	int32_t			m_nXiaoFeiSumRankSize;
	int32_t			m_nXiaoFeiSumRankLimit;
	std::vector<int32_t>	m_vXiaoFeiSumRankMail;
	std::vector<MemChrBagVector>	m_vXiaoFeiSumRankReward;
	std::map<int8_t, FestivalRankVector>	m_mXiaoFeiSumRank;
	std::mutex		m_lock;

	// Flop
	int32_t			m_FlopSize;
	std::vector<int32_t>	m_FlopType;
	std::vector<ItemData>	m_FlopCost;

	// LiQuan
	int32_t			m_LiQuanSize;
	std::vector<MemChrBag>	m_LiQuanItem;
	std::vector<ItemData>	m_ItemDataVector;
	std::vector<int32_t>	m_LiQuanPriceVt;
	std::vector<int32_t>	m_LiQuanLimitCount;

	// QianDao
	int32_t			m_QianDaoSize;
	std::vector<MemChrBag>	m_QianDaoReward;
	std::vector<int32_t>	m_BuQianPrice;

	// YanHua
	int32_t			m_CurrYanHuaPoint;
	int32_t			m_YanHuaSize;
	std::vector<MemChrBag>	m_YanHuaReward;
	std::vector<int32_t>	m_YanHuaPointVt;
	std::vector<FestivalRank>	m_YanHuaRank;
};

#define OPEN_BETA Answer::Singleton<COpenBeta>::instance()

#endif // __TPOC_OPEN_BETA_H__
