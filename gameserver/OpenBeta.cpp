#include "stdafx.h"
#include "OpenBeta.h"
#include "GameService.h"
#include "DBPool.h"
#include "Timer.h"
#include "Player.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "MapManager.h"
#include "Map.h"
#include "Monster.h"
#include "PoolManager.h"
#include "OperateLimit.h"
#include "DBService.h"

COpenBeta::COpenBeta()
	: m_nStartDay(0)
	, m_nEndDay(0)
	, m_nIcon(0)
	, m_nDay(0)
	, m_nMinute(0)
	, m_nBossIcon(0)
	, m_nBossStartBroadcast(0)
	, m_nBossEndBroadcast(0)
	, m_nBossKillBroadcast(0)
	, m_MapId(0)
	, m_X(0)
	, m_Y(0)
	, m_Mid(0)
	, m_MonsterId(0)
	, m_bDie(false)
	, m_nDailyLimitShopSize(0)
	, m_nTitleShopSize(0)
	, m_nShiZhuangShopSize(0)
	, m_nOnlineStartMinute(0)
	, m_nOnlineEndMinute(0)
	, m_nOnlineTimeArea(0)
	, m_nMaxCount(0)
	, m_nRechargeDaysSize(0)
	, m_ChouJiangType(0)
	, m_nShowSize(0)
	, m_nXiaoFeiSumRankSize(0)
	, m_nXiaoFeiSumRankLimit(0)
	, m_FlopSize(0)
	, m_LiQuanSize(0)
	, m_QianDaoSize(0)
	, m_CurrYanHuaPoint(0)
	, m_YanHuaSize(0)
{
	memset(m_vStartDay, 0, sizeof(m_vStartDay));
	memset(m_vEndDay, 0, sizeof(m_vEndDay));
}

COpenBeta::~COpenBeta()
{
}

void COpenBeta::Init(int32_t line)
{
	if (line == 9)
		return;

	// 获取当前分钟
	CTimer* pTimer = Answer::Singleton<CTimer>::instance();
	tm nowTime;
	CTimer::GetLocalNow(&nowTime, pTimer);
	m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;

	// 读取配置文件
	Answer::Inifile ini;
	ini.parse("./ServerConfig/Tables/OpenBetaAct.cfg");

	// CONFIG 段
	m_nStartDay = Answer::DayTime::StringToIntTime(ini.getStrValue("CONFIG", "start_time"));
	m_nEndDay = ini.getIntValue("CONFIG", "end_day");
	m_nIcon = ini.getIntValue("CONFIG", "icon");

	int32_t now = Answer::DayTime::now();
	m_nDay = (Answer::DayTime::dayzero(now) - Answer::DayTime::dayzero(m_nStartDay)) / 86400;

	// RECHARGE 段
	m_vStartDay[OBTT_RECHARGE] = ini.getIntValue("RECHARGE", "start_day");
	m_vEndDay[OBTT_RECHARGE] = ini.getIntValue("RECHARGE", "end_day");
	m_nRechargeDaysSize = ini.getIntValue("RECHARGE", "size");
	m_vRechargeValue.reserve(m_nRechargeDaysSize);
	m_vRechargeGift.reserve(m_nRechargeDaysSize);

	char szCol[64];
	for (int32_t i = 0; i < m_nRechargeDaysSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "gold%d", i + 1);
		m_vRechargeValue.push_back(ini.getIntValue("RECHARGE", szCol));

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "gift%d", i + 1);
		MemChrBagVector items = CItemHelper::parseItemVectorString(ini.getStrValue("RECHARGE", szCol));
		m_vRechargeGift.push_back(items);
	}

	// CHOU_JIANG 段
	m_vStartDay[OBTT_CHOU_JIANG] = ini.getIntValue("CHOU_JIANG", "start_day");
	m_vEndDay[OBTT_CHOU_JIANG] = ini.getIntValue("CHOU_JIANG", "end_day");
	m_ChouJiangType = ini.getIntValue("CHOU_JIANG", "Type");

	// COLLECT_DROP 段
	m_vStartDay[OBTT_COLLECT_DROP] = ini.getIntValue("COLLECT_DROP", "start_day");
	m_vEndDay[OBTT_COLLECT_DROP] = ini.getIntValue("COLLECT_DROP", "end_day");

	// BOSS 段
	m_vStartDay[OBTT_BOSS] = ini.getIntValue("BOSS", "start_day");
	m_vEndDay[OBTT_BOSS] = ini.getIntValue("BOSS", "end_day");
	m_nBossIcon = ini.getIntValue("BOSS", "icon");
	m_nBossStartBroadcast = ini.getIntValue("BOSS", "start_broadcast");
	m_nBossEndBroadcast = ini.getIntValue("BOSS", "end_broadcast");
	m_nBossKillBroadcast = ini.getIntValue("BOSS", "kill_broadcast");

	int32_t nBossCount = ini.getIntValue("BOSS", "count");
	m_vBossMinute.reserve(nBossCount);
	TimeArea tarea;
	for (int32_t i = 0; i < nBossCount; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "start_minute%d", i + 1);
		tarea.nStartTime = ini.getIntValue("BOSS", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "end_minute%d", i + 1);
		tarea.nEndTime = ini.getIntValue("BOSS", szCol);

		m_vBossMinute.push_back(tarea);
	}

	m_MapId = ini.getIntValue("BOSS", "mapid");
	m_X = ini.getIntValue("BOSS", "x");
	m_Y = ini.getIntValue("BOSS", "y");
	m_Mid = ini.getIntValue("BOSS", "mid");

	// DAILY_LIMIT_SHOP 段
	m_vStartDay[OBTT_DAILY_LIMIT_SHOP] = ini.getIntValue("DAILY_LIMIT_SHOP", "start_day");
	m_vEndDay[OBTT_DAILY_LIMIT_SHOP] = ini.getIntValue("DAILY_LIMIT_SHOP", "end_day");
	m_nDailyLimitShopSize = ini.getIntValue("DAILY_LIMIT_SHOP", "size");
	m_vDailyLimitShopGoods.resize(m_nDailyLimitShopSize);
	m_vDailyLimitShopBroadcast.resize(m_nDailyLimitShopSize, 0);

	for (int32_t i = 0; i < m_nDailyLimitShopSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "price%d", i + 1);
		m_vDailyLimitShopGoods[i].nPrice = ini.getIntValue("DAILY_LIMIT_SHOP", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
		m_vDailyLimitShopGoods[i].vItem = CItemHelper::parseItemVectorString(
			ini.getStrValue("DAILY_LIMIT_SHOP", szCol));

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
		m_vDailyLimitShopBroadcast[i] = ini.getIntValue("DAILY_LIMIT_SHOP", szCol);
	}

	// TITLE 段
	m_vStartDay[OBTT_TITLE_SHOP] = ini.getIntValue("TITLE", "start_day");
	m_vEndDay[OBTT_TITLE_SHOP] = ini.getIntValue("TITLE", "end_day");
	m_nTitleShopSize = ini.getIntValue("TITLE", "size");
	m_vTitleShopGoods.resize(m_nTitleShopSize);
	m_vTitleShopBroadcast.resize(m_nTitleShopSize, 0);

	for (int32_t i = 0; i < m_nTitleShopSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "price%d", i + 1);
		m_vTitleShopGoods[i].nPrice = ini.getIntValue("TITLE", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
		m_vTitleShopGoods[i].vItem = CItemHelper::parseItemVectorString(
			ini.getStrValue("TITLE", szCol));

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
		m_vTitleShopBroadcast[i] = ini.getIntValue("TITLE", szCol);
	}

	// SHI_ZHUANG 段
	m_vStartDay[OBTT_SHI_ZHUANG_SHOP] = ini.getIntValue("SHI_ZHUANG", "start_day");
	m_vEndDay[OBTT_SHI_ZHUANG_SHOP] = ini.getIntValue("SHI_ZHUANG", "end_day");
	m_nShiZhuangShopSize = ini.getIntValue("SHI_ZHUANG", "size");
	m_vShizhuangShopGoods.resize(m_nShiZhuangShopSize);
	m_vShiZhuangShopBroadcast.resize(m_nShiZhuangShopSize, 0);

	for (int32_t i = 0; i < m_nShiZhuangShopSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "price%d", i + 1);
		m_vShizhuangShopGoods[i].nPrice = ini.getIntValue("SHI_ZHUANG", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
		m_vShizhuangShopGoods[i].vItem = CItemHelper::parseItemVectorString(
			ini.getStrValue("SHI_ZHUANG", szCol));

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
		m_vShiZhuangShopBroadcast[i] = ini.getIntValue("SHI_ZHUANG", szCol);
	}

	// RED_PACK (在线奖励) 段
	m_vStartDay[OBTT_ONLINE_REWARD] = ini.getIntValue("RED_PACK", "start_day");
	m_vEndDay[OBTT_ONLINE_REWARD] = ini.getIntValue("RED_PACK", "end_day");
	m_nOnlineStartMinute = ini.getIntValue("RED_PACK", "start_time");
	m_nOnlineEndMinute = ini.getIntValue("RED_PACK", "end_time");
	m_nOnlineTimeArea = 60 * ini.getIntValue("RED_PACK", "dis_time");
	m_vOnlineReward = CItemHelper::parseItemVectorString(ini.getStrValue("RED_PACK", "reward"));
	m_nMaxCount = ini.getIntValue("RED_PACK", "max_count");

	// XIAO_FEI_SUM_RANK 段
	m_vStartDay[OBTT_XIAO_FEI_SUM_RANK] = ini.getIntValue("XIAO_FEI_SUM_RANK", "start_day");
	m_vEndDay[OBTT_XIAO_FEI_SUM_RANK] = ini.getIntValue("XIAO_FEI_SUM_RANK", "end_day");
	m_nShowSize = ini.getIntValue("XIAO_FEI_SUM_RANK", "show_size");
	m_nXiaoFeiSumRankSize = ini.getIntValue("XIAO_FEI_SUM_RANK", "size");
	m_nXiaoFeiSumRankLimit = ini.getIntValue("XIAO_FEI_SUM_RANK", "limit");
	m_vXiaoFeiSumRankMail.resize(m_nXiaoFeiSumRankSize, 0);
	m_vXiaoFeiSumRankReward.resize(m_nXiaoFeiSumRankSize);

	for (int32_t i = 0; i < m_nXiaoFeiSumRankSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "mail%d", i + 1);
		m_vXiaoFeiSumRankMail[i] = ini.getIntValue("XIAO_FEI_SUM_RANK", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
		m_vXiaoFeiSumRankReward[i] = CItemHelper::parseItemVectorString(
			ini.getStrValue("XIAO_FEI_SUM_RANK", szCol));
	}

	// OBT_FLOP 段
	m_vStartDay[OBTT_FLOP] = ini.getIntValue("OBT_FLOP", "start_day");
	m_vEndDay[OBTT_FLOP] = ini.getIntValue("OBT_FLOP", "end_day");
	m_FlopSize = ini.getIntValue("OBT_FLOP", "size");
	m_FlopType.resize(m_FlopSize, 0);
	m_FlopCost.resize(m_FlopSize);

	for (int32_t i = 0; i < m_FlopSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "type%d", i + 1);
		m_FlopType[i] = ini.getIntValue("OBT_FLOP", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "cost%d", i + 1);
		m_FlopCost[i] = CItemHelper::parseItemDataString(ini.getStrValue("OBT_FLOP", szCol));
	}

	// OBT_LI_QUAN 段
	m_vStartDay[OBTT_LI_QUAN] = ini.getIntValue("OBT_LI_QUAN", "start_day");
	m_vEndDay[OBTT_LI_QUAN] = ini.getIntValue("OBT_LI_QUAN", "end_day");
	m_LiQuanSize = ini.getIntValue("OBT_LI_QUAN", "size");
	m_LiQuanItem.resize(m_LiQuanSize);
	m_ItemDataVector.resize(m_LiQuanSize);
	m_LiQuanPriceVt.resize(m_LiQuanSize, 0);
	m_LiQuanLimitCount.resize(m_LiQuanSize, 0);

	for (int32_t i = 0; i < m_LiQuanSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "item%d", i + 1);
		MemChrBagVector tmpItems = CItemHelper::parseItemString(0, ini.getStrValue("OBT_LI_QUAN", szCol));
		if (!tmpItems.empty()) m_LiQuanItem[i] = tmpItems[0];

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "price%d", i + 1);
		m_LiQuanPriceVt[i] = ini.getIntValue("OBT_LI_QUAN", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
		m_LiQuanLimitCount[i] = ini.getIntValue("OBT_LI_QUAN", szCol);

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "costitem%d", i + 1);
		m_ItemDataVector[i] = CItemHelper::parseItemDataString(ini.getStrValue("OBT_LI_QUAN", szCol));
	}

	// OBT_QIAN_DAO 段
	m_vStartDay[OBTT_QIAN_DAO] = ini.getIntValue("OBT_QIAN_DAO", "start_day");
	m_vEndDay[OBTT_QIAN_DAO] = ini.getIntValue("OBT_QIAN_DAO", "end_day");
	m_QianDaoSize = ini.getIntValue("OBT_QIAN_DAO", "size");
	m_QianDaoReward.resize(m_QianDaoSize);
	m_BuQianPrice.resize(m_QianDaoSize, 0);

	for (int32_t i = 0; i < m_QianDaoSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "item%d", i + 1);
		MemChrBagVector tmpQD = CItemHelper::parseItemString(0, ini.getStrValue("OBT_QIAN_DAO", szCol));
		if (!tmpQD.empty()) m_QianDaoReward[i] = tmpQD[0];

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "price%d", i + 1);
		m_BuQianPrice[i] = ini.getIntValue("OBT_QIAN_DAO", szCol);
	}

	// OBT_YAN_HUA 段
	m_vStartDay[OBTT_YAN_HUA] = ini.getIntValue("OBT_YAN_HUA", "start_day");
	m_vEndDay[OBTT_YAN_HUA] = ini.getIntValue("OBT_YAN_HUA", "end_day");
	m_YanHuaSize = ini.getIntValue("OBT_YAN_HUA", "size");
	m_YanHuaReward.resize(m_YanHuaSize);
	m_YanHuaPointVt.resize(m_YanHuaSize, 0);

	for (int32_t i = 0; i < m_YanHuaSize; ++i)
	{
		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "item%d", i + 1);
		MemChrBagVector tmpYH = CItemHelper::parseItemString(0, ini.getStrValue("OBT_YAN_HUA", szCol));
		if (!tmpYH.empty()) m_YanHuaReward[i] = tmpYH[0];

		bzero(szCol, sizeof(szCol));
		snprintf(szCol, sizeof(szCol), "point%d", i + 1);
		m_YanHuaPointVt[i] = ini.getIntValue("OBT_YAN_HUA", szCol);
	}

	// OBT_GUO_QING_TASK / OBT_GUO_QING_REWARD
	m_vStartDay[OBTT_GUO_QING_TASK] = ini.getIntValue("OBT_GUO_QING_TASK", "start_day");
	m_vEndDay[OBTT_GUO_QING_TASK] = ini.getIntValue("OBT_GUO_QING_TASK", "end_day");
	m_vStartDay[OBTT_GUO_QING_REWARD] = ini.getIntValue("OBT_GUO_QING_REWARD", "start_day");
	m_vEndDay[OBTT_GUO_QING_REWARD] = ini.getIntValue("OBT_GUO_QING_REWARD", "end_day");

	// 加载数据
	loadXiaoFeiSumRank();
	LoadYanHuaValue();

	LOG_INFO("COpenBeta::Init line=%d\n", line);
}

void COpenBeta::OnDaySwitch()
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	m_nDay = Answer::DayTime::daydiff(m_nStartDay);

	// 活动结束广播
	if (m_nDay == m_nEndDay)
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2CC3);
		if (packet)
		{
			packet->writeInt32(m_nIcon);
			packet->writeInt8(4);
			packet->writeInt32(0);
			packet->writeInt8(0);
			packet->writeInt32(0);
			packet->writeInt8(0);
			packet->setSize(packet->getWOffset());
			GAME_SERVICE.worldBroadcast(0, packet);
		}
	}

	// 消费排行邮件
	if (m_nDay == m_vEndDay[OBTT_XIAO_FEI_SUM_RANK])
		sendXiaoFeiSumRankMail();

	if (IsOpenBetaTime())
		GAME_SERVICE.SendOpenBetaIcon();
}

void COpenBeta::OnNewMinute(int32_t nMinute)
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	m_nMinute = nMinute;
	CheckBoss();
	checkXiaoFeiSumRank();
}

void COpenBeta::updateStartTime()
{
	// placeholder — line check already done in Init
}

bool COpenBeta::IsInTime(int8_t Type)
{
	if (GAME_SERVICE.getLine() == 9)
		return false;
	if (Type <= 0 || Type > OBTT_MAX)
		return false;
	return m_nDay >= m_vStartDay[Type] && m_nDay < m_vEndDay[Type];
}

bool COpenBeta::IsOpenBetaTime()
{
	if (GAME_SERVICE.getLine() == 9)
		return false;
	return m_nDay >= 0 && m_nDay < m_nEndDay;
}

int32_t COpenBeta::getLeftTime()
{
	if (GAME_SERVICE.getLine() == 9)
		return 0;
	return 86400 * (m_nEndDay - m_nDay) - 60 * m_nMinute;
}

int32_t COpenBeta::GetEndCollectDropTime()
{
	if (GAME_SERVICE.getLine() == 9)
		return 0;
	if (!IsInTime(OBTT_COLLECT_DROP))
		return 0;
	return 86400 * m_vEndDay[OBTT_COLLECT_DROP] + Answer::DayTime::dayzero(m_nStartDay) - 1;
}

void COpenBeta::getIconState(ShowIcon* pIcon, Player* player)
{
	pIcon->nId = m_nIcon;
	pIcon->nState = 0;
	pIcon->nLeftTime = 0;
	pIcon->IconLeft = 0;
	pIcon->IconRight = 0;
	pIcon->Effects = 0;

	if (!player)
		return;

	// 在线奖励可领取
	if (IsInTime(OBTT_ONLINE_REWARD) && canGetOnlineGift(player))
		pIcon->nState = 1;

	// 充值奖励可领取
	if (IsInTime(OBTT_RECHARGE))
	{
		CExtOperateLimit& limit = player->GetOperateLimit();
		int32_t nRecord = limit.GetLimitCount(2091);
		int32_t nPayGold = player->GetTodayPayGold();
		for (int32_t i = 0; i < m_nRechargeDaysSize; ++i)
		{
			if (nPayGold >= m_vRechargeValue[i] && !(nRecord & (1 << i)))
			{
				pIcon->nState = 1;
				break;
			}
		}
	}

	// 烟花奖励可领取
	if (IsInTime(OBTT_YAN_HUA))
	{
		CExtOperateLimit& limit = player->GetOperateLimit();
		int32_t nRecord = limit.GetLimitCount(1930);
		for (int32_t i = 0; i < m_YanHuaSize; ++i)
		{
			if (m_CurrYanHuaPoint >= m_YanHuaPointVt[i] && !(nRecord & (1 << i)))
			{
				pIcon->nState = 1;
				break;
			}
		}
	}

	pIcon->nLeftTime = getLeftTime();
}

void COpenBeta::GetIconState(Player* player, IconStateList* IconList)
{
	if (!player)
		return;
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (m_nDay < 0 || m_nDay >= m_nEndDay)
		return;

	ShowIcon icon;
	getIconState(&icon, player);
	IconList->push_back(icon);
}

void COpenBeta::SendIconState(Player* player)
{
	if (!player)
		return;
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (!IsOpenBetaTime())
		return;

	ShowIcon icon;
	getIconState(&icon, player);
	player->SendIconState(&icon);
}

void COpenBeta::getBossIconState(ShowIcon* pIcon)
{
	pIcon->nId = m_nBossIcon;
	pIcon->nState = IsInBossTime() ? (m_bDie ? 3 : 1) : 0;
	pIcon->nLeftTime = 0;
	pIcon->IconLeft = 0;
	pIcon->IconRight = 0;
	pIcon->Effects = 0;
}

void COpenBeta::GetBossIconState(IconStateList* IconList)
{
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (!IsInBossTime())
		return;

	ShowIcon icon;
	getBossIconState(&icon);
	IconList->push_back(icon);
}

void COpenBeta::SendBossIconState()
{
	if (GAME_SERVICE.getLine() != 1)
		return;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2CC3);
	if (packet)
	{
		ShowIcon icon;
		getBossIconState(&icon);
		packet->writeInt32(icon.nId);
		packet->writeInt8(icon.nState);
		packet->writeInt32(icon.nLeftTime);
		packet->writeInt8(icon.IconLeft);
		packet->writeInt32(icon.IconRight);
		packet->writeInt8(icon.Effects);
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(0, packet);
	}
}

void COpenBeta::SendActivityInfo(Player* player)
{
	if (!player)
		return;
	if (GAME_SERVICE.getLine() == 9)
		return;

	int8_t connid = (int8_t)player->getConnId();
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2EBD);
	if (!packet)
		return;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nRecord = limit.GetLimitCount(1917);

	packet->writeInt8(m_nTitleShopSize);
	for (int32_t i = 0; i < m_nTitleShopSize; ++i)
		packet->writeInt8((nRecord >> i) & 1);

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo((int8_t)player->getConnId(), player->getGateIndex(), packet);
}

bool COpenBeta::IsInBossTime()
{
	if (GAME_SERVICE.getLine() == 9)
		return false;
	return IsInTime(OBTT_BOSS);
}

void COpenBeta::BossDie(int32_t MonsterId, std::string* p_name, CharId_t Cid)
{
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (m_MonsterId > 0 && m_MonsterId == MonsterId)
	{
		m_bDie = true;
		BroadcastBossKilled(p_name, Cid);
		SendBossIconState();
	}
}

void COpenBeta::BroadcastBossKilled(const std::string* name, CharId_t cid)
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2CD6);
	if (packet)
	{
		packet->writeInt32(m_nBossKillBroadcast);
		packet->writeUTF8(name);
		packet->writeInt64(cid);
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(0, packet);
	}
}

void COpenBeta::CheckBoss()
{
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (!IsInTime(OBTT_BOSS))
		return;
	if (m_vBossMinute.empty())
		return;
	if (GAME_SERVICE.getLine() != 1)
		return;

	for (size_t i = 0; i < m_vBossMinute.size(); ++i)
	{
		if (m_nMinute == m_vBossMinute[i].nStartTime)
		{
			// 刷BOSS
			CfgMonster* pMonster = CFG_DATA.getMonster(m_Mid);
			if (!pMonster || pMonster->boss_sign != 11)
				return;

			int32_t MonsterId = CFG_DATA.GetMapMonsterId();
			CfgMapMonster MapMonster;
			memset(&MapMonster, 0, sizeof(MapMonster));
			MapMonster.id = MonsterId;
			MapMonster.mapid = m_MapId;
			MapMonster.x = m_X;
			MapMonster.y = m_Y;
			m_MonsterId = MonsterId;

			CPoolManager* pPool = Answer::Singleton<CPoolManager>::instance();
			Monster* monster = pPool->pop<Monster>();
			if (monster && pMonster)
			{
				monster->init(*pMonster, MapMonster, nullptr);
				int32_t nEndTime = m_vBossMinute[i].nEndTime;
				monster->SetLifeTime(Answer::DayTime::now() + 60 * (nEndTime - m_vBossMinute[i].nStartTime));

				Map* pMap = Answer::Singleton<MapManager>::instance()->GetMap(m_MapId);
				if (pMap)
				{
					pMap->addMonster(monster, MapMonster.x, MapMonster.y);
					m_bDie = false;
				}
			}
			broadcastBossStart();
			SendBossIconState();
		}
		else if (m_nMinute == m_vBossMinute[i].nEndTime && !m_bDie)
		{
			m_bDie = true;
			broadcastBossEnd();
			SendBossIconState();
		}
	}
}

void COpenBeta::broadcastBossStart()
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2CD6);
	if (packet)
	{
		packet->writeInt32(m_nBossStartBroadcast);
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(0, packet);
	}
}

void COpenBeta::broadcastBossEnd()
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2CD6);
	if (packet)
	{
		packet->writeInt32(m_nBossEndBroadcast);
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(0, packet);
	}
}

int32_t COpenBeta::GetRechargeGift(Player* player, int32_t nIndex)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!IsInTime(OBTT_RECHARGE)) return 10002;
	if (nIndex < 0 || nIndex >= m_nRechargeDaysSize) return 10002;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nRewardRecord = limit.GetLimitCount(2091);
	int32_t nPayGold = player->GetTodayPayGold();
	if (nPayGold < m_vRechargeValue[nIndex])
		return 10002;

	int32_t nNewRecord = nRewardRecord | (1 << nIndex);
	if (nRewardRecord == nNewRecord)
		return 10002;

	if (!player->GetBag().AddItem(m_vRechargeGift[nIndex], ICR_OPEN_BETA))
		return 10002;

	limit.UpdateLimitCount(2091, nNewRecord);
	SendIconState(player);
	SendResult(player, OBTT_RECHARGE, nIndex, 0);
	return 0;
}

int32_t COpenBeta::BuyGiftShopItem(Player* player, int8_t nIndex)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!IsInTime(OBTT_DAILY_LIMIT_SHOP)) return 10002;
	if (nIndex < 0 || nIndex >= m_nDailyLimitShopSize) return 10002;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOldRecord = limit.GetLimitCount(2092);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
		return 10002;

	const ShopGoods& goods = m_vDailyLimitShopGoods[nIndex];
	if (player->GetCurrency(CURRENCY_GOLD) < goods.nPrice)
		return 10002;

	if (!player->GetBag().AddItem(goods.vItem, ICR_OPEN_BETA))
		return 10002;

	if (!player->DecCurrency(CURRENCY_GOLD, goods.nPrice, GCR_OPEN_BETA, 0))
		return 10002;

	limit.UpdateLimitCount(2092, nNewRecord);

	if (m_vDailyLimitShopBroadcast[nIndex] > 0)
	{
		std::string name = player->getName();
		sendBroadcast(m_vDailyLimitShopBroadcast[nIndex], player->getCid(), &name);
	}

	SendResult(player, OBTT_DAILY_LIMIT_SHOP, nIndex, 0);
	return 0;
}

int32_t COpenBeta::BuyTitleShopItem(Player* player, int8_t nIndex)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!IsInTime(OBTT_TITLE_SHOP)) return 10002;
	if (nIndex < 0 || nIndex >= m_nTitleShopSize) return 10002;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOldRecord = limit.GetLimitCount(1917);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
		return 10002;

	const ShopGoods& goods = m_vTitleShopGoods[nIndex];
	if (player->GetCurrency(CURRENCY_GOLD) < goods.nPrice)
		return 10002;

	if (!player->GetBag().AddItem(goods.vItem, ICR_OPEN_BETA))
		return 10002;

	if (!player->DecCurrency(CURRENCY_GOLD, goods.nPrice, GCR_OPEN_BETA, 0))
		return 10002;

	limit.UpdateLimitCount(1917, nNewRecord);

	if (m_vTitleShopBroadcast[nIndex] > 0)
	{
		std::string name = player->getName();
		sendBroadcast(m_vTitleShopBroadcast[nIndex], player->getCid(), &name);
	}

	SendResult(player, OBTT_TITLE_SHOP, nIndex, 0);
	return 0;
}

int32_t COpenBeta::BuyShiZhuangShopItem(Player* player, int8_t nIndex)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!IsInTime(OBTT_SHI_ZHUANG_SHOP)) return 10002;
	if (nIndex < 0 || nIndex >= m_nShiZhuangShopSize) return 10002;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOldRecord = limit.GetLimitCount(1918);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
		return 10002;

	const ShopGoods& goods = m_vShizhuangShopGoods[nIndex];
	if (player->GetCurrency(CURRENCY_GOLD) < goods.nPrice)
		return 10002;

	if (!player->GetBag().AddItem(goods.vItem, ICR_OPEN_BETA))
		return 10002;

	if (!player->DecCurrency(CURRENCY_GOLD, goods.nPrice, GCR_OPEN_BETA, 0))
		return 10002;

	limit.UpdateLimitCount(1918, nNewRecord);

	if (m_vShiZhuangShopBroadcast[nIndex] > 0)
	{
		std::string name = player->getName();
		sendBroadcast(m_vShiZhuangShopBroadcast[nIndex], player->getCid(), &name);
	}

	SendResult(player, OBTT_SHI_ZHUANG_SHOP, nIndex, 0);
	return 0;
}

int32_t COpenBeta::BuyLiQuan(Player* player, int8_t nIndex)
{
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!player) return 10002;
	if (!IsInTime(OBTT_LI_QUAN)) return 10002;
	if (nIndex < 0 || nIndex >= m_LiQuanSize) return 10002;

	int32_t nLimit = m_LiQuanLimitCount[nIndex];
	if (nLimit <= player->getRecord(nIndex + 10000))
		return 10002;

	if (m_LiQuanPriceVt[nIndex] > 0)
	{
		if (player->GetCurrency(CURRENCY_GOLD) < m_LiQuanPriceVt[nIndex])
			return 10002;
	}

	if (player->GetBag().GetFreeSlotCount() <= 0)
		return 10002;

	if (!player->GetBag().RemoveItem(m_ItemDataVector[nIndex], IDCR_OPEN_BETA_LI_QUAN))
		return 10002;

	if (m_LiQuanPriceVt[nIndex] > 0)
	{
		if (!player->DecCurrency(CURRENCY_GOLD, m_LiQuanPriceVt[nIndex], GCR_OPEN_BETA, 0))
			return 10002;
	}

	player->GetOperateLimit().AddLimitCount(nIndex + 10000, 1);
	player->GetBag().AddItem(m_LiQuanItem[nIndex], IDCR_OPEN_BETA_LI_QUAN);
	return 0;
}

int32_t COpenBeta::GetFlopType(int32_t nFlopId)
{
	if (GAME_SERVICE.getLine() == 9)
		return 0;
	if (nFlopId < 0 || nFlopId >= m_FlopSize)
		return 0;
	return m_FlopType[nFlopId];
}

bool COpenBeta::CanFlopDraw(Player* pPlayer, int32_t FlopId)
{
	if (GAME_SERVICE.getLine() == 9)
		return false;
	if (!IsInTime(OBTT_FLOP))
		return false;
	if (!pPlayer || FlopId < 0 || FlopId >= m_FlopSize)
		return false;

	// 扣除道具
	if (m_FlopCost[FlopId].m_nId > 0)
	{
		if (!pPlayer->GetBag().RemoveItem(m_FlopCost[FlopId], IDCR_FLOP))
			return false;
	}

	// type==2 为免费翻牌
	if (m_FlopType[FlopId] == 2)
		return true;

	// 检查翻牌次数
	int32_t FlopTimes = pPlayer->getRecord(2114);
	if (FlopTimes >= GetMaxFlopTimes(pPlayer))
	{
		int32_t BuyTimes = pPlayer->getRecord(2113);
		// 只有最后一天或BuyTimes<=1才能购买
		if (m_nDay == m_vEndDay[OBTT_FLOP] - 1 || BuyTimes <= 1)
		{
			int32_t NeedCost = 500 * (BuyTimes + 1);
			if (NeedCost > 0)
			{
				if (!pPlayer->DecCurrency(CURRENCY_GOLD, NeedCost, GCR_FLOP, 0))
					return false;
				pPlayer->GetOperateLimit().AddLimitCount(2113, 1);
				pPlayer->GetOperateLimit().AddLimitCount(2114, 1);
				return true;
			}
			return false;
		}
		return false;
	}

	pPlayer->GetOperateLimit().AddLimitCount(2114, 1);
	return true;
}

int32_t COpenBeta::GetMaxFlopTimes(Player* pPlayer)
{
	if (!pPlayer) return 0;
	if (GAME_SERVICE.getLine() == 9) return 0;

	int32_t Times = 1;
	if (pPlayer->GetTodayPayGold() > 0)
		Times = 2;
	return pPlayer->getRecord(2113) + Times;
}

int32_t COpenBeta::GetChouJiangType()
{
	if (GAME_SERVICE.getLine() == 9)
		return 0;
	if (IsInTime(OBTT_CHOU_JIANG))
		return m_ChouJiangType;
	return 0;
}

void COpenBeta::AddOnlineRecord(Player* player)
{
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (!IsInTime(OBTT_ONLINE_REWARD))
		return;
	if (!player)
		return;
	if (m_nMinute < m_nOnlineStartMinute || m_nMinute >= m_nOnlineEndMinute)
		return;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOnlineTime = limit.GetLimitCount(2093);
	int32_t nRewardTimes = limit.GetLimitCount(2094);

	if (m_nMaxCount > nRewardTimes)
	{
		limit.AddLimitCount(2093, 1);
		if (nOnlineTime / m_nOnlineTimeArea - nRewardTimes != (nOnlineTime + 1) / m_nOnlineTimeArea - nRewardTimes)
			SendIconState(player);
	}
}

bool COpenBeta::canGetOnlineGift(Player* player)
{
	if (GAME_SERVICE.getLine() == 9) return false;
	if (!player) return false;
	if (!IsInTime(OBTT_ONLINE_REWARD)) return false;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOnlineTime = limit.GetLimitCount(2093);
	int32_t nRewardTimes = limit.GetLimitCount(2094);

	return m_nMaxCount > nRewardTimes && nOnlineTime / m_nOnlineTimeArea > nRewardTimes;
}

int32_t COpenBeta::GetOnlineTimeRewardTime(Player* player)
{
	if (GAME_SERVICE.getLine() == 9) return 0;
	if (!player) return 0;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOnlineTime = limit.GetLimitCount(2093);
	int32_t nRewardTimes = limit.GetLimitCount(2094);

	if (nOnlineTime / m_nOnlineTimeArea > nRewardTimes)
		return 0;
	return (nRewardTimes + 1) * m_nOnlineTimeArea - nOnlineTime;
}

int32_t COpenBeta::GetOnlineGift(Player* player)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!canGetOnlineGift(player)) return 10002;

	if (!player->GetBag().AddItem(m_vOnlineReward, ICR_OPEN_BETA))
		return 10002;

	player->GetOperateLimit().AddLimitCount(2094, 1);
	SendIconState(player);
	int32_t OnlineTimeRewardTime = GetOnlineTimeRewardTime(player);
	SendResult(player, OBTT_ONLINE_REWARD, OnlineTimeRewardTime, 0);
	return 0;
}

int32_t COpenBeta::GetQianDaoReward(Player* player, int8_t nIndex, int8_t nType)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!IsInTime(OBTT_QIAN_DAO)) return 10002;
	if (nIndex < 0 || nIndex >= m_QianDaoSize) return 10002;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOldRecord = limit.GetLimitCount(1931);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
		return 10002;

	int32_t nQianDaoStartDay = m_nDay - m_vStartDay[OBTT_QIAN_DAO];
	if (nQianDaoStartDay < 0)
		return 10002;
	if (m_QianDaoSize <= nQianDaoStartDay)
		return 10002;
	if (nIndex > nQianDaoStartDay)
		return 10002;

	// 补签需要扣费
	if (nIndex != nQianDaoStartDay)
	{
		if (nType != 1)
			return 10002;
		if (player->GetCurrency(CURRENCY_GOLD) < m_BuQianPrice[nIndex])
			return 10002;
	}

	if (!player->GetBag().AddItem(m_QianDaoReward[nIndex], ICR_OPEN_BETA))
		return 10002;

	if (nIndex != nQianDaoStartDay)
	{
		if (!player->DecCurrency(CURRENCY_GOLD, m_BuQianPrice[nIndex], GCR_OPEN_BETA, 0))
			return 10002;
	}

	limit.UpdateLimitCount(1931, nNewRecord);
	SendResult(player, OBTT_QIAN_DAO, nIndex, 0);
	SendIconState(player);
	return 0;
}

void COpenBeta::LoadYanHuaValue()
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::MySqlDBGuard db(Answer::Singleton<Answer::DBPool>::instance());
	char mySql[1024];
	bzero(mySql, sizeof(mySql));
	snprintf(mySql, sizeof(mySql), "SELECT `value` FROM `sys_server_config` WHERE `name`='YAN_HUA'");
	Answer::MySqlQuery result(db.query(mySql));
	if (!result.eof())
	{
		m_CurrYanHuaPoint = atoi(result.getStringValue(0));
	}
}

void COpenBeta::UpdateYanHuaValue()
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::MySqlDBGuard db(Answer::Singleton<Answer::DBPool>::instance());
	char mySql[1024];
	bzero(mySql, sizeof(mySql));
	snprintf(mySql, sizeof(mySql), "SELECT `value` FROM `sys_server_config` WHERE `name`='YAN_HUA'");
	Answer::MySqlQuery result(db.query(mySql));

	char mySql_0[1024];
	bzero(mySql_0, sizeof(mySql_0));
	if (result.eof())
		snprintf(mySql_0, sizeof(mySql_0), "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('YAN_HUA','%d')", m_CurrYanHuaPoint);
	else
		snprintf(mySql_0, sizeof(mySql_0), "UPDATE `sys_server_config` SET `value`= %d WHERE `name`='YAN_HUA'", m_CurrYanHuaPoint);

	db.excute(mySql_0);
}

void COpenBeta::AddYanHuaPoint(int32_t Values)
{
	if (GAME_SERVICE.getLine() == 9)
		return;
	if (!IsInTime(OBTT_YAN_HUA))
		return;

	bool NeedSendIcon = false;
	int32_t OldPoint = m_CurrYanHuaPoint;
	m_CurrYanHuaPoint += Values;
	UpdateYanHuaValue();

	for (int32_t i = 0; i < m_YanHuaSize; ++i)
	{
		if (m_YanHuaPointVt[i] > OldPoint && m_CurrYanHuaPoint >= m_YanHuaPointVt[i])
		{
			NeedSendIcon = true;
			break;
		}
	}

	if (NeedSendIcon)
		GAME_SERVICE.SendOpenBetaIcon();
}

int32_t COpenBeta::GetYanHuaPointReward(Player* player, int8_t nIndex)
{
	if (!player) return 10002;
	if (GAME_SERVICE.getLine() == 9) return 10002;
	if (!IsInTime(OBTT_YAN_HUA)) return 10002;
	if (nIndex < 0 || nIndex >= m_YanHuaSize) return 10002;

	CExtOperateLimit& limit = player->GetOperateLimit();
	int32_t nOldRecord = limit.GetLimitCount(1930);
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if (nOldRecord == nNewRecord)
		return 10002;

	if (m_CurrYanHuaPoint < m_YanHuaPointVt[nIndex])
		return 10002;

	if (!player->GetBag().AddItem(m_YanHuaReward[nIndex], ICR_OPEN_BETA))
		return 10002;

	limit.UpdateLimitCount(1930, nNewRecord);
	SendResult(player, OBTT_YAN_HUA, nIndex, 0);
	SendIconState(player);
	return 0;
}

void COpenBeta::loadXiaoFeiSumRank()
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::MySqlDBGuard db(Answer::Singleton<Answer::DBPool>::instance());
	Answer::MySqlQuery result(db.query(
		"SELECT * FROM `mem_open_beta_rank` WHERE `type`=5 ORDER BY `count` DESC,`time`"));

	int32_t nIndex = 0;
	FestivalRankVector vRank;
	FestivalRank p_x;
	vRank.resize(m_nShowSize, p_x);

	while (!result.eof() && m_nShowSize > nIndex)
	{
		vRank[nIndex].nCharId = result.getInt64Value("cid", 0);
		vRank[nIndex].strName = result.getStringValue("name");
		vRank[nIndex].nScore = result.getIntValue("count", 0);
		vRank[nIndex].nTime = result.getIntValue("time", 0);
		++nIndex;
		result.nextRow();
	}

	int8_t key = 0;
	m_mXiaoFeiSumRank[key] = vRank;
}

void COpenBeta::updateXiaoFeiSumRank(Player* player, int32_t AddValues)
{
	if (!player) return;
	if (GAME_SERVICE.getLine() == 9) return;
	if (!IsInTime(OBTT_XIAO_FEI_SUM_RANK)) return;

	player->GetOperateLimit().AddLimitCount(1919, AddValues);
	int32_t nScore = player->GetOperateLimit().GetLimitCount(1919);

	if (m_nXiaoFeiSumRankLimit <= nScore)
	{
		int8_t connid = player->getConnId();
		CharId_t nCharId = player->getCid();
		std::string strName = player->getName();

		checkXiaoFeiSumRankInvalid(connid);

		// 查找排名位置
		int32_t nRankIndex = -1;
		for (int32_t i = 0; i < m_nShowSize; ++i)
		{
			std::lock_guard<std::mutex> guard(m_lock);
			FestivalRank& rank = m_mXiaoFeiSumRank[connid][i];
			if (rank.nScore < nScore)
			{
				nRankIndex = i;
				break;
			}
		}

		if (nRankIndex >= 0)
		{
			// 查找旧位置
			int32_t nOldIndex = m_nShowSize - 1;
			for (int32_t i = 0; i < m_nShowSize; ++i)
			{
				std::lock_guard<std::mutex> guard(m_lock);
				if (m_mXiaoFeiSumRank[connid][i].nCharId == nCharId)
				{
					nOldIndex = i;
					break;
				}
			}

			if (nOldIndex < nRankIndex)
				nRankIndex = nOldIndex;

			// 移位
			if (nOldIndex != nRankIndex)
			{
				for (int32_t i = nOldIndex; i > nRankIndex; --i)
				{
					std::lock_guard<std::mutex> guard(m_lock);
					m_mXiaoFeiSumRank[connid][i] = m_mXiaoFeiSumRank[connid][i - 1];
					m_mXiaoFeiSumRank[connid][i].bChange = true;
				}
			}

			{
				std::lock_guard<std::mutex> guard(m_lock);
				FestivalRank& rank = m_mXiaoFeiSumRank[connid][nRankIndex];
				rank.nCharId = nCharId;
				rank.strName = strName;
				rank.nScore = nScore;
				rank.nTime = Answer::DayTime::now();
				rank.bChange = true;
			}
		}
	}
}

void COpenBeta::checkXiaoFeiSumRankInvalid(int8_t connid)
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	std::lock_guard<std::mutex> guard(m_lock);
	auto iter = m_mXiaoFeiSumRank.find(connid);
	if (iter == m_mXiaoFeiSumRank.end())
	{
		FestivalRankVector vRank;
		FestivalRank p_x;
		vRank.resize(m_nShowSize, p_x);
		m_mXiaoFeiSumRank[connid] = vRank;
	}
}

void COpenBeta::checkXiaoFeiSumRank()
{
	if (GAME_SERVICE.getLine() == 9) return;
	if (!IsInTime(OBTT_XIAO_FEI_SUM_RANK)) return;

	std::lock_guard<std::mutex> guard(m_lock);
	for (auto& pair : m_mXiaoFeiSumRank)
	{
		int8_t connid = pair.first;
		FestivalRankVector& vRank = pair.second;

		for (int32_t i = 0; i < m_nShowSize && vRank[i].nCharId > 0; ++i)
		{
			if (vRank[i].bChange)
			{
				vRank[i].bChange = false;
				char szSQL[4096];
				bzero(szSQL, sizeof(szSQL));
				snprintf(szSQL, sizeof(szSQL),
					"INSERT INTO `mem_open_beta_rank` (`type`, `day`, `cid`, `name`, `count`,`time`) "
					"VALUES (%d,%d,%lld,'%s',%d,%d) ON DUPLICATE KEY UPDATE `count`=%d,`time`=%d",
					5, 0, (long long)vRank[i].nCharId, vRank[i].strName.c_str(),
					vRank[i].nScore, vRank[i].nTime,
					vRank[i].nScore, vRank[i].nTime);

				Answer::MySqlDBGuard db(Answer::Singleton<Answer::DBPool>::instance());
				db.excute(szSQL);
			}
		}
	}
}

void COpenBeta::sendXiaoFeiSumRankMail()
{
	if (GAME_SERVICE.getLine() != 1)
		return;

	std::lock_guard<std::mutex> guard(m_lock);
	for (auto& pair : m_mXiaoFeiSumRank)
	{
		int8_t connid = pair.first;
		FestivalRankVector& vRank = pair.second;

		for (int32_t i = 0; i < m_nXiaoFeiSumRankSize; ++i)
		{
			if (vRank[i].nCharId > 0)
			{
				std::string Param;
				DB_SERVICE.OnSendSysMail(connid, vRank[i].nCharId,
					m_vXiaoFeiSumRankMail[i], m_vXiaoFeiSumRankReward[i],
					ICR_OPEN_BETA, &Param, 0);
			}
		}
	}
}

void COpenBeta::SendResult(Player* pPlayer, int8_t Type, int32_t Index, int32_t param)
{
	if (!pPlayer) return;
	if (GAME_SERVICE.getLine() == 9) return;

	int8_t connid = pPlayer->getConnId();
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(connid, Answer::PackType::PACK_DISPATCH, 0x2EBE);
	if (!packet)
		return;

	packet->writeInt8(Type);
	packet->writeInt32(Index);
	packet->writeInt32(param);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo((int8_t)pPlayer->getConnId(), pPlayer->getGateIndex(), packet);
}

void COpenBeta::sendBroadcast(int32_t nBroadId, CharId_t cid, const std::string* name)
{
	if (GAME_SERVICE.getLine() == 9)
		return;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(0, Answer::PackType::PACK_DISPATCH, 0x2CD6);
	if (packet)
	{
		packet->writeInt32(nBroadId);
		packet->writeUTF8(name);
		packet->writeInt64(cid);
		packet->setSize(packet->getWOffset());
		packet->setProc(0x2CD6);
		GAME_SERVICE.worldBroadcast(0, packet);
	}
}
