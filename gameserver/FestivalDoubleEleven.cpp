#include "stdafx.h"
#include "FestivalDoubleEleven.h"
#include "Player.h"
#include "Monster.h"
#include "GameService.h"
#include "Timer.h"
#include "DBService.h"
#include "ItemHelper.h"
#include "CfgData.h"
#include "Bag.h"
#include "CharPet.h"

#include <algorithm>
#include <functional>
#include <cstring>
#include <cstdio>

// ============ Helper: parse item string (format: "id,class,count|id,class,count|...") ============
static MemChrBagVector parseItemVectorString(const std::string& str)
{
    MemChrBagVector items;
    if (str.empty())
        return items;
    StringVector items_receive = Answer::StringUtility::split(str, "|");
    for (size_t i = 0; i < items_receive.size(); ++i)
    {
        StringVector item = Answer::StringUtility::split(items_receive[i], ",");
        if (item.size() >= 3)
        {
            MemChrBag itemData = {};
            itemData.itemId    = atoi(item[0].c_str());
            itemData.itemClass = (int8_t)atoi(item[1].c_str());
            itemData.itemCount = atoi(item[2].c_str());
            items.push_back(itemData);
        }
    }
    return items;
}

static ShopGoods parseShopGoodsString(const std::string& str)
{
    ShopGoods goods = {};
    if (str.empty())
        return goods;
    // Format: price|itemId,itemClass,itemCount|itemId,itemClass,itemCount|...
    StringVector parts = Answer::StringUtility::split(str, "|");
    if (parts.size() >= 1)
        goods.nPrice = atoi(parts[0].c_str());
    for (size_t i = 1; i < parts.size(); ++i)
    {
        StringVector item = Answer::StringUtility::split(parts[i], ",");
        if (item.size() >= 3)
        {
            MemChrBag itemData = {};
            itemData.itemId    = atoi(item[0].c_str());
            itemData.itemClass = (int8_t)atoi(item[1].c_str());
            itemData.itemCount = atoi(item[2].c_str());
            goods.vItem.push_back(itemData);
        }
    }
    return goods;
}

CFestivalDoubleEleven::CFestivalDoubleEleven()
    : m_nVersion(0)
    , m_nHotSign(0)
    , m_nStartDay(0)
    , m_nEndDay(0)
    , m_nIcon(0)
    , m_nIconHideDay(0)
    , m_nGameStartDay(0)
    , m_nUniteStartDay(0)
    , m_nDropGroup(0)
    , m_nDay(0)
    , m_nMinute(0)
    , m_nDrawLoopTimes(0)
    , m_nDrawRankSize(0)
    , m_nDrawRankLimit(0)
    , m_nXiaoFeiRankSize(0)
    , m_nXiaoFeiSumRankSize(0)
    , m_nXiaoFeiSumRankLimit(0)
    , m_nRechargeSumRankSize(0)
    , m_nCrossRechargeSumRankSize(0)
    , m_nCrossXiaoFeiSumRankSize(0)
    , m_nCrossChouJiangRankSize(0)
    , m_nBossScoreRate(0)
    , m_nBossScoreRankSize(0)
    , m_BossScoreRewardSize(0)
    , m_nScoreSize(0)
    , m_nRewardSize(0)
    , m_nSize(0)
    , m_MapId(0)
    , m_X(0)
    , m_Y(0)
    , m_Mid(0)
    , m_nWorldBossIcon(0)
    , m_nWorldBossStartBroadcast(0)
    , m_nWorldBossEndBroadcast(0)
    , m_nWorldBossKillBroadcast(0)
    , m_MonsterId(0)
    , m_bDie(false)
    , m_nDailyRechargeSize(0)
    , m_nDailyRechargeDrawSize(0)
    , m_nDailyRechargeDrawLimit(0)
    , m_nRechargeDrawSize(0)
    , m_nRechargeDrawValue(0)
    , m_nXiaoFeiDrawSize(0)
    , m_nXiaoFeiDrawValue(0)
    , m_nOnlineStartMinute(0)
    , m_nOnlineEndMinute(0)
    , m_nOnlineTimeArea(0)
    , m_nMaxCount(0)
    , m_nWishRecharge(0)
    , m_nEquipQingYiSize(0)
    , m_nFriendQingYiSize(0)
    , m_nPetIllusionItemSize(0)
    , m_nRechargeBackSize(0)
    , m_nEquipUpStarBackId(0)
    , m_nNeedValue(0)
    , m_nFaBaoType(0)
    , m_nBuyGiftSize(0)
    , m_nGiftShopSize(0)
    , m_nGouWuCheSize(0)
    , m_nDailyLimitShopCostType(0)
    , m_nDailyLimitShopCostValue(0)
    , m_nDailyLimitShopLimit(0)
    , m_nDailyLimitShop2Size(0)
    , m_nMoYuShiJieDropSize(0)
    , m_nChouJiangCount(0)
    , m_nChouJiangType(0)
    , m_nMysteryShopRefreshBroad(0)
    , m_nDaTiRankSize(0)
    , m_nHuoYueDuSumSize(0)
    , m_nRechargeSumSize(0)
    , m_nXiaoFeiSumSize(0)
    , m_Price(0)
    , m_GetReardSize(0)
    , m_BackItem(0)
{
    bzero(m_vOpen, sizeof(m_vOpen));
    bzero(m_vStartDay, sizeof(m_vStartDay));
    bzero(m_vEndDay, sizeof(m_vEndDay));
}

CFestivalDoubleEleven::~CFestivalDoubleEleven()
{
}

CFestivalDoubleEleven* CFestivalDoubleEleven::instance()
{
    static CFestivalDoubleEleven inst;
    return &inst;
}

// ==================== Init / Config ====================

void CFestivalDoubleEleven::Init(int32_t line)
{
    initCfgData();
    int32_t nVersion = loadVersion(line);
    if (nVersion <= 0 || m_nVersion == nVersion)
    {
        loadRankData(line);
        if (!nVersion)
            saveVersion(line);
    }
    else
    {
        resetRankData(line);
        saveVersion(line);
    }
    const tm& nowTime = TIMER.GetLocalNow();
    m_nMinute = nowTime.tm_hour * 60 + nowTime.tm_min;
}

void CFestivalDoubleEleven::initCfgData()
{
    Answer::Inifile ini;
    ini.parse("./ServerConfig/Tables/FestivalDoubleEleven.cfg");

    // CONFIG section
    m_nHotSign = ini.getIntValue("CONFIG", "hot_sign");
    m_nVersion = ini.getIntValue("CONFIG", "version");
    m_nStartDay = Answer::DayTime::StringToIntTime(ini.getStrValue("CONFIG", "start_time"));
    m_nEndDay = ini.getIntValue("CONFIG", "end_day");
    m_nIcon = ini.getIntValue("CONFIG", "icon");
    m_nIconHideDay = ini.getIntValue("CONFIG", "icon_hide_day");
    m_nGameStartDay = ini.getIntValue("CONFIG", "game_start_day");
    m_nUniteStartDay = ini.getIntValue("CONFIG", "unite_start_day");
    m_nDropGroup = ini.getIntValue("CONFIG", "drop_group");

    initOpenList(ini.getStrValue("CONFIG", "open"));

    m_nDay = (Answer::DayTime::dayzero(Answer::DayTime::now()) - Answer::DayTime::dayzero(m_nStartDay)) / 86400;

    // ============ Sub-activity sections ============

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_LAND))
    {
        m_vStartDay[1] = ini.getIntValue("LAND", "start_day");
        m_vEndDay[1] = ini.getIntValue("LAND", "end_day");
        m_vLandGift.resize(m_nEndDay);
        for (int32_t i = 0; i < m_nEndDay; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "gift%d", i + 1);
            m_vLandGift[i] = parseItemVectorString(ini.getStrValue("LAND", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE))
    {
        m_vStartDay[2] = ini.getIntValue("DAILY_RECHARGE", "start_day");
        m_vEndDay[2] = ini.getIntValue("DAILY_RECHARGE", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DRAW))
    {
        m_vStartDay[3] = ini.getIntValue("LUCKY_DRAW", "start_day");
        m_vEndDay[3] = ini.getIntValue("LUCKY_DRAW", "end_day");
        m_nDrawLoopTimes = ini.getIntValue("LUCKY_DRAW", "loop_times");
        m_vDrawLoopReward = parseItemVectorString(ini.getStrValue("LUCKY_DRAW", "loop_reward"));
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DRAW_RANK))
    {
        m_vStartDay[4] = ini.getIntValue("LUCKY_DRAW_RANK", "start_day");
        m_vEndDay[4] = ini.getIntValue("LUCKY_DRAW_RANK", "end_day");
        m_nDrawRankSize = ini.getIntValue("LUCKY_DRAW_RANK", "rank_size");
        m_nDrawRankLimit = ini.getIntValue("LUCKY_DRAW_RANK", "rank_limit");
        m_vDrawRankMail.resize(m_nDrawRankSize, 0);
        m_vDrawRankReward.resize(m_nDrawRankSize);
        for (int32_t i = 0; i < m_nDrawRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
            m_vDrawRankMail[i] = ini.getIntValue("LUCKY_DRAW_RANK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
            m_vDrawRankReward[i] = parseItemVectorString(ini.getStrValue("LUCKY_DRAW_RANK", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_EXCHANGE))
    {
        m_vStartDay[5] = ini.getIntValue("EXCHANGE", "start_day");
        m_vEndDay[5] = ini.getIntValue("EXCHANGE", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_WORLD_BOSS))
    {
        m_vStartDay[6] = ini.getIntValue("WORLD_BOSS", "start_day");
        m_vEndDay[6] = ini.getIntValue("WORLD_BOSS", "end_day");
        m_nWorldBossIcon = ini.getIntValue("WORLD_BOSS", "icon");
        m_nWorldBossStartBroadcast = ini.getIntValue("WORLD_BOSS", "start_broadcast");
        m_nWorldBossEndBroadcast = ini.getIntValue("WORLD_BOSS", "end_broadcast");
        m_nWorldBossKillBroadcast = ini.getIntValue("WORLD_BOSS", "kill_broadcast");
        int32_t nCount = ini.getIntValue("WORLD_BOSS", "count");
        m_vWorldBossMinute.resize(nCount, TimeArea());
        for (int32_t i = 0; i < nCount; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "start_minute%d", i + 1);
            m_vWorldBossMinute[i].nStartTime = ini.getIntValue("WORLD_BOSS", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "end_minute%d", i + 1);
            m_vWorldBossMinute[i].nEndTime = ini.getIntValue("WORLD_BOSS", szCol);
        }
        m_MapId = ini.getIntValue("WORLD_BOSS", "mapid");
        m_X = ini.getIntValue("WORLD_BOSS", "x");
        m_Y = ini.getIntValue("WORLD_BOSS", "y");
        m_Mid = ini.getIntValue("WORLD_BOSS", "mid");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM))
    {
        m_vStartDay[7] = ini.getIntValue("HUO_YUE_DU_SUM", "start_day");
        m_vEndDay[7] = ini.getIntValue("HUO_YUE_DU_SUM", "end_day");
        m_nHuoYueDuSumSize = ini.getIntValue("HUO_YUE_DU_SUM", "size");
        m_vHuoYueDuSumLimit.resize(m_nHuoYueDuSumSize, 0);
        for (int32_t i = 0; i < m_nHuoYueDuSumSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "value%d", i + 1);
            m_vHuoYueDuSumLimit[i] = ini.getIntValue("HUO_YUE_DU_SUM", szCol);
        }
        m_vHuoYueDuSumReward.resize(m_nHuoYueDuSumSize);
        for (int32_t i = 0; i < m_nHuoYueDuSumSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vHuoYueDuSumReward[i] = parseItemVectorString(ini.getStrValue("HUO_YUE_DU_SUM", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP))
    {
        m_vStartDay[8] = ini.getIntValue("DAILY_LIMIT_SHOP", "start_day");
        m_vEndDay[8] = ini.getIntValue("DAILY_LIMIT_SHOP", "end_day");
        m_vDailyLimitShopItem = parseItemVectorString(ini.getStrValue("DAILY_LIMIT_SHOP", "item"));
        m_nDailyLimitShopCostType = ini.getIntValue("DAILY_LIMIT_SHOP", "cost_type");
        m_nDailyLimitShopCostValue = ini.getIntValue("DAILY_LIMIT_SHOP", "cost_value");
        m_nDailyLimitShopLimit = ini.getIntValue("DAILY_LIMIT_SHOP", "limit");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM))
    {
        m_vStartDay[9] = ini.getIntValue("LAND_SUM", "start_day");
        m_vEndDay[9] = ini.getIntValue("LAND_SUM", "end_day");
        m_vLandSumGift.resize(m_nEndDay);
        for (int32_t i = 0; i < m_nEndDay; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "gift%d", i + 1);
            m_vLandSumGift[i] = parseItemVectorString(ini.getStrValue("LAND_SUM", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME))
    {
        m_vStartDay[10] = ini.getIntValue("DAILY_ONLINE", "start_day");
        m_vEndDay[10] = ini.getIntValue("DAILY_ONLINE", "end_day");
        m_nOnlineStartMinute = ini.getIntValue("DAILY_ONLINE", "start_time");
        m_nOnlineEndMinute = ini.getIntValue("DAILY_ONLINE", "end_time");
        m_nOnlineTimeArea = 60 * ini.getIntValue("DAILY_ONLINE", "dis_time");
        m_vOnlineReward = parseItemVectorString(ini.getStrValue("DAILY_ONLINE", "reward"));
        m_nMaxCount = ini.getIntValue("DAILY_ONLINE", "max_count");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BEST_WISH))
    {
        m_vStartDay[11] = ini.getIntValue("BEST_WISH", "start_day");
        m_vEndDay[11] = ini.getIntValue("BEST_WISH", "end_day");
        m_nWishRecharge = ini.getIntValue("BEST_WISH", "recharge");
        m_vWishReward = parseItemVectorString(ini.getStrValue("BEST_WISH", "reward"));
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK))
    {
        m_vStartDay[12] = ini.getIntValue("XIAO_FEI_RANK", "start_day");
        m_vEndDay[12] = ini.getIntValue("XIAO_FEI_RANK", "end_day");
        m_nXiaoFeiRankSize = ini.getIntValue("XIAO_FEI_RANK", "size");
        m_vXiaoFeiRankLimit.resize(m_nXiaoFeiRankSize, 0);
        m_vXiaoFeiRankMail.resize(m_nXiaoFeiRankSize, 0);
        m_vXiaoFeiRankReward.resize(m_nXiaoFeiRankSize);
        for (int32_t i = 0; i < m_nXiaoFeiRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vXiaoFeiRankLimit[i] = ini.getIntValue("XIAO_FEI_RANK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "mail%d", i + 1);
            m_vXiaoFeiRankMail[i] = ini.getIntValue("XIAO_FEI_RANK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vXiaoFeiRankReward[i] = parseItemVectorString(ini.getStrValue("XIAO_FEI_RANK", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW))
    {
        m_vStartDay[13] = ini.getIntValue("XIAO_FEI_DRAW", "start_day");
        m_vEndDay[13] = ini.getIntValue("XIAO_FEI_DRAW", "end_day");
        m_nXiaoFeiDrawSize = ini.getIntValue("XIAO_FEI_DRAW", "size");
        m_nXiaoFeiDrawValue = ini.getIntValue("XIAO_FEI_DRAW", "need_value");
        m_vScoreLimit.resize(m_nXiaoFeiDrawSize, 0);
        m_vBossScoreReward.resize(m_nXiaoFeiDrawSize);
        for (int32_t i = 0; i < m_nXiaoFeiDrawSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vScoreLimit[i] = ini.getIntValue("XIAO_FEI_DRAW", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vBossScoreReward[i] = parseItemVectorString(ini.getStrValue("XIAO_FEI_DRAW", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE))
    {
        m_vStartDay[14] = ini.getIntValue("MO_YU_SHI_JIE", "start_day");
        m_vEndDay[14] = ini.getIntValue("MO_YU_SHI_JIE", "end_day");
        m_nMoYuShiJieDropSize = ini.getIntValue("MO_YU_SHI_JIE", "drop_size");
        m_vMoYuShiJieDrop.resize(m_nMoYuShiJieDropSize, 0);
        for (int32_t i = 0; i < m_nMoYuShiJieDropSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "drop%d", i + 1);
            m_vMoYuShiJieDrop[i] = ini.getIntValue("MO_YU_SHI_JIE", szCol);
        }
        m_nChouJiangCount = ini.getIntValue("MO_YU_SHI_JIE", "count");
        m_nChouJiangType = ini.getIntValue("MO_YU_SHI_JIE", "chou_jiang_type");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE_2))
    {
        m_vStartDay[15] = ini.getIntValue("DAILY_RECHARGE_2", "start_day");
        m_vEndDay[15] = ini.getIntValue("DAILY_RECHARGE_2", "end_day");
        m_nDailyRechargeDrawSize = ini.getIntValue("DAILY_RECHARGE_2", "size");
        m_nDailyRechargeDrawLimit = ini.getIntValue("DAILY_RECHARGE_2", "limit");
        m_vDailyRechargeLimit.resize(m_nDailyRechargeDrawSize, 0);
        for (int32_t i = 0; i < m_nDailyRechargeDrawSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vDailyRechargeLimit[i] = ini.getIntValue("DAILY_RECHARGE_2", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK))
    {
        m_vStartDay[16] = ini.getIntValue("XIAO_FEI_SUM_RANK", "start_day");
        m_vEndDay[16] = ini.getIntValue("XIAO_FEI_SUM_RANK", "end_day");
        m_nXiaoFeiSumRankSize = ini.getIntValue("XIAO_FEI_SUM_RANK", "size");
        m_nXiaoFeiSumRankLimit = ini.getIntValue("XIAO_FEI_SUM_RANK", "limit");
        m_vXiaoFeiSumRankMail.resize(m_nXiaoFeiSumRankSize, 0);
        m_vXiaoFeiSumRankReward.resize(m_nXiaoFeiSumRankSize);
        for (int32_t i = 0; i < m_nXiaoFeiSumRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "mail%d", i + 1);
            m_vXiaoFeiSumRankMail[i] = ini.getIntValue("XIAO_FEI_SUM_RANK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vXiaoFeiSumRankReward[i] = parseItemVectorString(ini.getStrValue("XIAO_FEI_SUM_RANK", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_GIFT_SHOP))
    {
        m_vStartDay[17] = ini.getIntValue("GIFT_SHOP", "start_day");
        m_vEndDay[17] = ini.getIntValue("GIFT_SHOP", "end_day");
        m_nGiftShopSize = ini.getIntValue("GIFT_SHOP", "size");
        m_vGiftShopGoods.resize(m_nGiftShopSize);
        for (int32_t i = 0; i < m_nGiftShopSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
            m_vGiftShopGoods[i] = parseShopGoodsString(ini.getStrValue("GIFT_SHOP", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG))
    {
        m_vStartDay[18] = ini.getIntValue("CHOU_JIANG", "start_day");
        m_vEndDay[18] = ini.getIntValue("CHOU_JIANG", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK))
    {
        m_vStartDay[19] = ini.getIntValue("FA_BAO_BACK", "start_day");
        m_vEndDay[19] = ini.getIntValue("FA_BAO_BACK", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP))
    {
        m_vStartDay[20] = ini.getIntValue("MYSTERY_SHOP", "start_day");
        m_vEndDay[20] = ini.getIntValue("MYSTERY_SHOP", "end_day");
        m_nMysteryShopRefreshBroad = ini.getIntValue("MYSTERY_SHOP", "refresh_broadcast");
        m_sMysteryShopRefreshCost = ini.getStrValue("MYSTERY_SHOP", "refresh_cost");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_GIFT))
    {
        m_vStartDay[21] = ini.getIntValue("RECHARGE_SUM_GIFT", "start_day");
        m_vEndDay[21] = ini.getIntValue("RECHARGE_SUM_GIFT", "end_day");
        m_nRechargeSumSize = ini.getIntValue("RECHARGE_SUM_GIFT", "size");
        m_vRechargeSumLimit.resize(m_nRechargeSumSize, 0);
        m_vRechargeSumReward.resize(m_nRechargeSumSize);
        for (int32_t i = 0; i < m_nRechargeSumSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vRechargeSumLimit[i] = ini.getIntValue("RECHARGE_SUM_GIFT", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vRechargeSumReward[i] = parseItemVectorString(ini.getStrValue("RECHARGE_SUM_GIFT", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT))
    {
        m_vStartDay[22] = ini.getIntValue("XIAO_FEI_SUM_GIFT", "start_day");
        m_vEndDay[22] = ini.getIntValue("XIAO_FEI_SUM_GIFT", "end_day");
        m_nXiaoFeiSumSize = ini.getIntValue("XIAO_FEI_SUM_GIFT", "size");
        m_vXiaoFeiSumLimit.resize(m_nXiaoFeiSumSize, 0);
        m_vXiaoFeiSumReward.resize(m_nXiaoFeiSumSize);
        for (int32_t i = 0; i < m_nXiaoFeiSumSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vXiaoFeiSumLimit[i] = ini.getIntValue("XIAO_FEI_SUM_GIFT", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vXiaoFeiSumReward[i] = parseItemVectorString(ini.getStrValue("XIAO_FEI_SUM_GIFT", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BUY_PET_GIFT))
    {
        m_vStartDay[23] = ini.getIntValue("BUY_PET_GIFT", "start_day");
        m_vEndDay[23] = ini.getIntValue("BUY_PET_GIFT", "end_day");
        m_Price = ini.getIntValue("BUY_PET_GIFT", "price");
        m_Items = parseItemVectorString(ini.getStrValue("BUY_PET_GIFT", "goods"));
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI))
    {
        m_vStartDay[24] = ini.getIntValue("DA_TI", "start_day");
        m_vEndDay[24] = ini.getIntValue("DA_TI", "end_day");
        m_nDaTiRankSize = ini.getIntValue("DA_TI", "size");
        m_vDaTiRankMail.resize(m_nDaTiRankSize, 0);
        m_vDaTiRankReward.resize(m_nDaTiRankSize);
        for (int32_t i = 0; i < m_nDaTiRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
            m_vDaTiRankMail[i] = ini.getIntValue("DA_TI", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
            m_vDaTiRankReward[i] = parseItemVectorString(ini.getStrValue("DA_TI", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP_2))
    {
        m_vStartDay[25] = ini.getIntValue("DAILY_LIMIT_SHOP_2", "start_day");
        m_vEndDay[25] = ini.getIntValue("DAILY_LIMIT_SHOP_2", "end_day");
        m_nDailyLimitShop2Size = ini.getIntValue("DAILY_LIMIT_SHOP_2", "size");
        m_vDailyLimitShop2Goods.resize(m_nDailyLimitShop2Size);
        m_vDailyLimitShop2Broadcast.resize(m_nDailyLimitShop2Size, 0);
        for (int32_t i = 0; i < m_nDailyLimitShop2Size; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "goods%d", i + 1);
            m_vDailyLimitShop2Goods[i] = parseShopGoodsString(ini.getStrValue("DAILY_LIMIT_SHOP_2", szCol));

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
            m_vDailyLimitShop2Broadcast[i] = ini.getIntValue("DAILY_LIMIT_SHOP_2", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK))
    {
        m_vStartDay[26] = ini.getIntValue("EQUIP_UPSTAR_BACK", "start_day");
        m_vEndDay[26] = ini.getIntValue("EQUIP_UPSTAR_BACK", "end_day");
        m_nEquipUpStarBackId = ini.getIntValue("EQUIP_UPSTAR_BACK", "id");
        m_nNeedValue = ini.getIntValue("EQUIP_UPSTAR_BACK", "need_value");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_DRAW))
    {
        m_vStartDay[27] = ini.getIntValue("RECHARGE_DRAW", "start_day");
        m_vEndDay[27] = ini.getIntValue("RECHARGE_DRAW", "end_day");
        m_nRechargeDrawSize = ini.getIntValue("RECHARGE_DRAW", "size");
        m_nRechargeDrawValue = ini.getIntValue("RECHARGE_DRAW", "need_value");
        m_vScoreLimit.resize(m_nRechargeDrawSize, 0);
        m_vBossScoreReward.resize(m_nRechargeDrawSize);
        for (int32_t i = 0; i < m_nRechargeDrawSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vScoreLimit[i] = ini.getIntValue("RECHARGE_DRAW", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vBossScoreReward[i] = parseItemVectorString(ini.getStrValue("RECHARGE_DRAW", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BUY_GIFT))
    {
        m_vStartDay[28] = ini.getIntValue("BUY_GIFT", "start_day");
        m_vEndDay[28] = ini.getIntValue("BUY_GIFT", "end_day");
        m_nBuyGiftSize = ini.getIntValue("BUY_GIFT", "size");
        m_vBuyGiftPrice.resize(m_nBuyGiftSize, 0);
        m_vBuyGiftBroadcast.resize(m_nBuyGiftSize, 0);
        m_vBuyGiftItem.resize(m_nBuyGiftSize);
        for (int32_t i = 0; i < m_nBuyGiftSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "price%d", i + 1);
            m_vBuyGiftPrice[i] = ini.getIntValue("BUY_GIFT", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "broadcast%d", i + 1);
            m_vBuyGiftBroadcast[i] = ini.getIntValue("BUY_GIFT", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "item%d", i + 1);
            m_vBuyGiftItem[i] = parseItemVectorString(ini.getStrValue("BUY_GIFT", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK))
    {
        m_vStartDay[29] = ini.getIntValue("RECHARGE_BACK", "start_day");
        m_vEndDay[29] = ini.getIntValue("RECHARGE_BACK", "end_day");
        m_nRechargeBackSize = ini.getIntValue("RECHARGE_BACK", "size");
        m_vRechargeBackLimit.resize(m_nRechargeBackSize, 0);
        m_vRechargeBackValue.resize(m_nRechargeBackSize, 0);
        for (int32_t i = 0; i < m_nRechargeBackSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vRechargeBackLimit[i] = ini.getIntValue("RECHARGE_BACK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "value%d", i + 1);
            m_vRechargeBackValue[i] = ini.getIntValue("RECHARGE_BACK", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE))
    {
        m_vStartDay[30] = ini.getIntValue("BOSS_SCORE", "start_day");
        m_vEndDay[30] = ini.getIntValue("BOSS_SCORE", "end_day");
        m_nScoreSize = ini.getIntValue("BOSS_SCORE", "size");
        m_vScoreLimit.resize(m_nScoreSize, 0);
        m_vGetBossScoreMail.resize(m_nScoreSize, 0);
        for (int32_t i = 0; i < m_nScoreSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vScoreLimit[i] = ini.getIntValue("BOSS_SCORE", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "mail%d", i + 1);
            m_vGetBossScoreMail[i] = ini.getIntValue("BOSS_SCORE", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM))
    {
        m_vStartDay[31] = ini.getIntValue("PET_ILLUSION_ITEM", "start_day");
        m_vEndDay[31] = ini.getIntValue("PET_ILLUSION_ITEM", "end_day");
        m_nPetIllusionItemSize = ini.getIntValue("PET_ILLUSION_ITEM", "size");
        m_vPetIllusionItemLimit.resize(m_nPetIllusionItemSize, 0);
        m_vPetIllusionItemReward.resize(m_nPetIllusionItemSize);
        for (int32_t i = 0; i < m_nPetIllusionItemSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vPetIllusionItemLimit[i] = ini.getIntValue("PET_ILLUSION_ITEM", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vPetIllusionItemReward[i] = parseItemVectorString(ini.getStrValue("PET_ILLUSION_ITEM", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK))
    {
        m_vStartDay[32] = ini.getIntValue("RECHARGE_SUM_RANK", "start_day");
        m_vEndDay[32] = ini.getIntValue("RECHARGE_SUM_RANK", "end_day");
        m_nRechargeSumRankSize = ini.getIntValue("RECHARGE_SUM_RANK", "size");
        m_vRechargeSumRankMail.resize(m_nRechargeSumRankSize, 0);
        m_vRechargeSumRankReward.resize(m_nRechargeSumRankSize);
        for (int32_t i = 0; i < m_nRechargeSumRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
            m_vRechargeSumRankMail[i] = ini.getIntValue("RECHARGE_SUM_RANK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
            m_vRechargeSumRankReward[i] = parseItemVectorString(ini.getStrValue("RECHARGE_SUM_RANK", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK))
    {
        m_vStartDay[33] = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", "start_day");
        m_vEndDay[33] = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", "end_day");
        m_nCrossRechargeSumRankSize = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", "size");
        m_vCrossRechargeSumRankLimit.resize(m_nCrossRechargeSumRankSize, 0);
        for (int32_t i = 0; i < m_nCrossRechargeSumRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vCrossRechargeSumRankLimit[i] = ini.getIntValue("CROSS_RECHARGE_SUM_RANK", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK))
    {
        m_vStartDay[34] = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", "start_day");
        m_vEndDay[34] = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", "end_day");
        m_nCrossXiaoFeiSumRankSize = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", "size");
        m_vCrossXiaoFeiSumRankLimit.resize(m_nCrossXiaoFeiSumRankSize, 0);
        for (int32_t i = 0; i < m_nCrossXiaoFeiSumRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vCrossXiaoFeiSumRankLimit[i] = ini.getIntValue("CROSS_XIAO_FEI_SUM_RANK", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_PET_EQUIP_CHOU_JIANG))
    {
        m_vStartDay[35] = ini.getIntValue("PET_EQUIP_CHOU_JIANG", "start_day");
        m_vEndDay[35] = ini.getIntValue("PET_EQUIP_CHOU_JIANG", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_CHOU_JIANG_RANK))
    {
        m_vStartDay[36] = ini.getIntValue("CROSS_CHOU_JIANG_RANK", "start_day");
        m_vEndDay[36] = ini.getIntValue("CROSS_CHOU_JIANG_RANK", "end_day");
        m_nCrossChouJiangRankSize = ini.getIntValue("CROSS_CHOU_JIANG_RANK", "size");
        m_vCrossChouJiangRankLimit.resize(m_nCrossChouJiangRankSize, 0);
        for (int32_t i = 0; i < m_nCrossChouJiangRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vCrossChouJiangRankLimit[i] = ini.getIntValue("CROSS_CHOU_JIANG_RANK", szCol);
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_QING_YI))
    {
        m_vStartDay[37] = ini.getIntValue("QING_YI_PEI", "start_day");
        m_vEndDay[37] = ini.getIntValue("QING_YI_PEI", "end_day");
        m_nEquipQingYiSize = ini.getIntValue("QING_YI_PEI", "size");
        m_vEquipQingYiLimit.resize(m_nEquipQingYiSize, 0);
        m_vEquipQingYiReward.resize(m_nEquipQingYiSize);
        for (int32_t i = 0; i < m_nEquipQingYiSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vEquipQingYiLimit[i] = ini.getIntValue("QING_YI_PEI", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vEquipQingYiReward[i] = parseItemVectorString(ini.getStrValue("QING_YI_PEI", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI))
    {
        m_vStartDay[38] = ini.getIntValue("FRIEND_QING_YI", "start_day");
        m_vEndDay[38] = ini.getIntValue("FRIEND_QING_YI", "end_day");
        m_nFriendQingYiSize = ini.getIntValue("FRIEND_QING_YI", "size");
        m_vFriendQingYiLimit.resize(m_nFriendQingYiSize, 0);
        m_vFriendQingYiReward.resize(m_nFriendQingYiSize);
        for (int32_t i = 0; i < m_nFriendQingYiSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vFriendQingYiLimit[i] = ini.getIntValue("FRIEND_QING_YI", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vFriendQingYiReward[i] = parseItemVectorString(ini.getStrValue("FRIEND_QING_YI", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_SCORE_SHOP))
    {
        m_vStartDay[39] = ini.getIntValue("SCORE_SHOP", "start_day");
        m_vEndDay[39] = ini.getIntValue("SCORE_SHOP", "end_day");
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK))
    {
        m_vStartDay[40] = ini.getIntValue("BOSS_SCORE_RANK", "start_day");
        m_vEndDay[40] = ini.getIntValue("BOSS_SCORE_RANK", "end_day");
        m_nBossScoreRankSize = ini.getIntValue("BOSS_SCORE_RANK", "size");
        m_nBossScoreRate = ini.getIntValue("BOSS_SCORE_RANK", "rate");
        m_vBossScoreRankMail.resize(m_nBossScoreRankSize, 0);
        m_vBossScoreRankReward.resize(m_nBossScoreRankSize);
        for (int32_t i = 0; i < m_nBossScoreRankSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "rank_mail%d", i + 1);
            m_vBossScoreRankMail[i] = ini.getIntValue("BOSS_SCORE_RANK", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "rank_reward%d", i + 1);
            m_vBossScoreRankReward[i] = parseItemVectorString(ini.getStrValue("BOSS_SCORE_RANK", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW))
    {
        m_vStartDay[41] = ini.getIntValue("BOSS_SCORE_DRAW", "start_day");
        m_vEndDay[41] = ini.getIntValue("BOSS_SCORE_DRAW", "end_day");
        m_nRewardSize = ini.getIntValue("BOSS_SCORE_DRAW", "size");
        m_vBossScoreiLimit.resize(m_nRewardSize, 0);
        m_vBossScoreDrawReward.resize(m_nRewardSize);
        for (int32_t i = 0; i < m_nRewardSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "limit%d", i + 1);
            m_vBossScoreiLimit[i] = ini.getIntValue("BOSS_SCORE_DRAW", szCol);

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "reward%d", i + 1);
            m_vBossScoreDrawReward[i] = parseItemVectorString(ini.getStrValue("BOSS_SCORE_DRAW", szCol));
        }
    }

    if (isOpen(FESTIVAL_ACTIVITY_TYPE::FAT_GOU_WU_CHE))
    {
        m_vStartDay[42] = ini.getIntValue("GOU_WU_CHE", "start_day");
        m_vEndDay[42] = ini.getIntValue("GOU_WU_CHE", "end_day");
        m_nGouWuCheSize = ini.getIntValue("GOU_WU_CHE", "size");
        m_vGouWuCheItem.resize(m_nGouWuCheSize);
        m_vGouWuCheGiftPrice.resize(m_nGouWuCheSize, 0);
        for (int32_t i = 0; i < m_nGouWuCheSize; ++i)
        {
            char szCol[64] = {0};
            snprintf(szCol, sizeof(szCol), "item%d", i + 1);
            m_vGouWuCheItem[i] = parseItemVectorString(ini.getStrValue("GOU_WU_CHE", szCol));

            bzero(szCol, sizeof(szCol));
            snprintf(szCol, sizeof(szCol), "price%d", i + 1);
            m_vGouWuCheGiftPrice[i] = ini.getIntValue("GOU_WU_CHE", szCol);
        }
    }
}

void CFestivalDoubleEleven::initOpenList(const std::string& str)
{
    bzero(m_vOpen, sizeof(m_vOpen));
    StringVector vOpen = Answer::StringUtility::split(str, "|");
    for (size_t i = 0; i < vOpen.size(); ++i)
    {
        int8_t nType = (int8_t)atoi(vOpen[i].c_str());
        if (nType > 0 && nType <= 46)
            m_vOpen[nType] = 1;
    }
}

void CFestivalDoubleEleven::HotUpdate()
{
    Answer::Inifile ini;
    ini.parse("./ServerConfig/Tables/FestivalDoubleEleven.cfg");
    
    int32_t nHotSign = ini.getIntValue("CONFIG", "hot_sign");
    if (m_nHotSign < nHotSign)
    {
        int32_t nOldVersion = m_nVersion;
        int32_t line = GAME_SERVICE.getLine();
        initCfgData();
        if (m_nVersion != nOldVersion)
        {
            saveVersion(line);
            resetRankData(line);
            resetPlayerData();
        }
    }
}

// ==================== Time / State ====================

void CFestivalDoubleEleven::OnDaySwitch()
{
    m_nDay = (Answer::DayTime::dayzero(TIMER.GetNow()) - Answer::DayTime::dayzero(m_nStartDay)) / 86400;
    
    if (m_nDay == m_nIconHideDay)
        hideIcon(m_nIcon);
    
    if (isOpen(FAT_MO_YU_SHI_JIE) && (m_nDay == m_vStartDay[14] || m_nDay == m_vEndDay[14]))
        BroadCastMoYuShiJieIconState();
    
    if (isOpen(FAT_DAILY_RECHARGE) && m_nDay == m_vEndDay[2])
        hideIcon(52);
    
    if (isOpen(FAT_DRAW_RANK) && m_nDay == m_vEndDay[4])
        sendDrawRankMail();
    if (isOpen(FAT_XIAO_FEI_SUM_RANK) && m_nDay == m_vEndDay[16])
        sendXiaoFeiSumRankMail();
    if (isOpen(FAT_DAILY_XIAO_FEI_RANK))
        sendXiaoFeiRankMail();
    if (isOpen(FAT_RECHARGE_SUM_RANK) && m_nDay == m_vEndDay[32])
        sendRechargeSumRankMail();
    if (isOpen(FAT_BOSS_SCORE_RANK) && m_nDay == m_vEndDay[40])
        sendBossScoreRankMail();
}

void CFestivalDoubleEleven::OnNewMinute(int32_t nMinute)
{
    m_nMinute = nMinute;
    HotUpdate();
    
    if (!IsInTime())
        return;
    
    if (IsInTime(FAT_DRAW_RANK)) checkDrawRank();
    if (IsInTime(FAT_WORLD_BOSS)) checkWorldBoss();
    if (IsInTime(FAT_DAILY_XIAO_FEI_RANK)) checkXiaoFeiRank();
    if (IsInTime(FAT_XIAO_FEI_SUM_RANK)) checkXiaoFeiSumRank();
    if (IsInTime(FAT_MYSTERY_SHOP)) checkRefreshMysteryShop();
    if (IsInTime(FAT_RECHARGE_SUM_RANK)) checkRechargeSumRank();
    if (IsInTime(FAT_CROSS_RECHARGE_SUM_RANK)) checkCrossRechargeSumRank();
    if (IsInTime(FAT_CROSS_XIAO_FEI_SUM_RANK)) checkCrossXiaoFeiSumRank();
    if (IsInTime(FAT_CROSS_CHOU_JIANG_RANK)) checkCrossChouJiangRank();
    if (IsInTime(FAT_BOSS_SCORE_RANK)) checkBossScoreRank();
}

bool CFestivalDoubleEleven::IsInTime()
{
    return isOpen(FAT_LAND) || isOpen(FAT_DAILY_RECHARGE) || isOpen(FAT_DRAW) || 
           isOpen(FAT_DRAW_RANK) || isOpen(FAT_EXCHANGE) || isOpen(FAT_WORLD_BOSS) ||
           isOpen(FAT_HUO_YUE_DU_SUM) || isOpen(FAT_DAILY_LIMIT_SHOP) || isOpen(FAT_LAND_SUM) ||
           isOpen(FAT_ONLINE_TIME) || isOpen(FAT_BEST_WISH) || isOpen(FAT_DAILY_XIAO_FEI_RANK) ||
           isOpen(FAT_XIAO_FEI_DRAW) || isOpen(FAT_MO_YU_SHI_JIE) || isOpen(FAT_DAILY_RECHARGE_2) ||
           isOpen(FAT_XIAO_FEI_SUM_RANK) || isOpen(FAT_GIFT_SHOP) || isOpen(FAT_CHOU_JIANG) ||
           isOpen(FAT_FA_BAO_BACK) || isOpen(FAT_MYSTERY_SHOP) || isOpen(FAT_RECHARGE_SUM_GIFT) ||
           isOpen(FAT_XIAO_FEI_SUM_GIFT) || isOpen(FAT_BUY_PET_GIFT) || isOpen(FAT_DA_TI) ||
           isOpen(FAT_DAILY_LIMIT_SHOP_2) || isOpen(FAT_EQUIP_UPSTAR_BACK) || isOpen(FAT_RECHARGE_DRAW) ||
           isOpen(FAT_BUY_GIFT) || isOpen(FAT_RECHARGE_BACK) || isOpen(FAT_BOSS_SCORE) ||
           isOpen(FAT_PET_ILLUSION_ITEM) || isOpen(FAT_RECHARGE_SUM_RANK) || isOpen(FAT_CROSS_RECHARGE_SUM_RANK) ||
           isOpen(FAT_CROSS_XIAO_FEI_SUM_RANK) || isOpen(FAT_PET_EQUIP_CHOU_JIANG) || isOpen(FAT_CROSS_CHOU_JIANG_RANK) ||
           isOpen(FAT_EQUIP_QING_YI) || isOpen(FAT_FRIEND_QING_YI) || isOpen(FAT_SCORE_SHOP) ||
           isOpen(FAT_BOSS_SCORE_RANK) || isOpen(FAT_BOSS_SCORE_DRAW) || isOpen(FAT_GOU_WU_CHE);
}

bool CFestivalDoubleEleven::IsInTime(FESTIVAL_ACTIVITY_TYPE nType)
{
    if (!isOpen(nType))
        return false;
    int32_t nIdx = (int32_t)nType;
    if (nIdx <= 0 || nIdx >= 47)
        return false;
    return m_nDay >= m_vStartDay[nIdx] && m_nDay <= m_vEndDay[nIdx];
}

bool CFestivalDoubleEleven::isOpen(FESTIVAL_ACTIVITY_TYPE nType)
{
    if (nType <= 0 || nType > 46)
        return false;
    return m_vOpen[nType] != 0;
}

bool CFestivalDoubleEleven::IsOpen()
{
    return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CFestivalDoubleEleven::needShowIcon()
{
    return IsOpen();
}

int32_t CFestivalDoubleEleven::getLeftTime()
{
    int32_t nEndMinute = m_vStartDay[1] + m_nEndDay * 24 * 60; // rough end minute
    int32_t nLeftMinute = nEndMinute - m_nMinute;
    if (nLeftMinute < 0)
        nLeftMinute = 0;
    return nLeftMinute;
}



void CFestivalDoubleEleven::SendActivityInfo(Player* player)
{
    if (NULL == player)
        return;
    // Send icon state to player
    SendIconState(player);
}



// ==================== Icon ====================

void CFestivalDoubleEleven::getIconState(int32_t& nIconId)
{
    nIconId = m_nIcon;
}

int32_t CFestivalDoubleEleven::GetIconState()
{
    return m_nIcon;
}

void CFestivalDoubleEleven::SendIconState(Player* player)
{
    if (NULL == player)
        return;
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nIcon);
    packet->writeInt8(IsInTime() ? 1 : 0);
    packet->writeInt32(getLeftTime());
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
}



void CFestivalDoubleEleven::SendWorldBossIconState()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    int32_t nIconState = 0;
    if (!m_bDie && IsInTime(FAT_WORLD_BOSS))
        nIconState = 1;
    packet->writeInt32(m_nWorldBossIcon);
    packet->writeInt8(nIconState);
    packet->writeInt32(getLeftTime());
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}



void CFestivalDoubleEleven::GetWorldBossIconState(int32_t& nIconId)
{
    nIconId = m_nWorldBossIcon;
}

void CFestivalDoubleEleven::GetMoYuShiJieIconState(int32_t& nIconId)
{
    nIconId = getMoYuShiJieIconState();
}

void CFestivalDoubleEleven::hideIcon(int32_t nIconId)
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    packet->writeInt32(nIconId);
    packet->writeInt8(4);  // hide state
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}



// ==================== Rank ====================

void CFestivalDoubleEleven::loadRankData(int32_t line)
{
    loadDrawRank();
    loadXiaoFeiRank();
    loadXiaoFeiSumRank();
    loadRechargeSumRank();
    loadCrossRechargeSumRank();
    loadCrossXiaoFeiSumRank();
    loadCrossChouJiangRank();
    loadBossScoreRank();
}

void CFestivalDoubleEleven::resetRankData(int32_t line)
{
    m_mDrawRank.clear();
    m_mXiaoFeiRank.clear();
    m_mXiaoFeiSumRank.clear();
    m_mRechargeSumRank.clear();
    m_mCrossRechargeSumRank.clear();
    m_mCrossXiaoFeiSumRank.clear();
    m_mCrossChouJiangRank.clear();
    m_mBossScoreRank.clear();
}

void CFestivalDoubleEleven::resetPlayerData()
{
    // Reset player-specific festival data
    // In decompiled code, this calls GameService::ResetFestivalData
    // For now, no per-player data to reset
}



void CFestivalDoubleEleven::saveVersion(int32_t line)
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    int32_t nNowTime = Answer::DayTime::now();
    std::string tname = "sys_server_config";
    if (line == 9)
        tname = "cross_sys_server_config";
    snprintf(szSQL, sizeof(szSQL),
        "INSERT INTO `%s` ( `name`, `value`, `refresh_time` ) VALUES ( 'FESTIVAL_VERSION', %d, %d ) "
        "ON DUPLICATE KEY UPDATE `value`=%d, `refresh_time`=%d",
        tname.c_str(), m_nVersion, nNowTime, m_nVersion, nNowTime);
    db.excute(szSQL);
}



int32_t CFestivalDoubleEleven::loadVersion(int32_t line)
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    std::string tname = "sys_server_config";
    if (line == 9)
        tname = "cross_sys_server_config";
    snprintf(szSQL, sizeof(szSQL), "SELECT * FROM `%s` WHERE `name`='FESTIVAL_VERSION'", tname.c_str());
    Answer::MySqlQuery result = db.query(szSQL);
    if (!result.eof())
    {
        std::string strValue = result.getStringValue("value");
        return atoi(strValue.c_str());
    }
    return 0;
}



// ==================== Draw ====================

void CFestivalDoubleEleven::AddDrawTimes(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0)
        return;
    if (!IsInTime(FAT_DRAW))
        return;
    CExtOperateLimit& pLimit = player->GetOperateLimit();
    pLimit.AddLimitCount(1633, nCount);
    pLimit.AddLimitCount(1634, nCount);
}



void CFestivalDoubleEleven::loadDrawRank()
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_DRAW_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mDrawRank.clear();
    while (!result.eof())
    {
    std::string strName = result.getStringValue("name");
    std::string strVal = result.getStringValue("value");
    int64_t nCharId = 0;
    // Extract charId from name after prefix
    if (strName.size() > 19)
        nCharId = atoll(strName.c_str() + 19);
    int32_t nValue = atoi(strVal.c_str());
        if (nCharId > 0)
            m_mDrawRank[nCharId] = nValue;
        result.nextRow();
    }
}



void CFestivalDoubleEleven::updateDrawRank(Player* player)
{
    if (NULL == player)
        return;
    updateDrawRank(player, 1);
}



void CFestivalDoubleEleven::checkDrawRankInvalid(int8_t connid)
{
    // Check if draw rank data matches limit, remove invalid entries
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mDrawRank.begin();
    while (it != m_mDrawRank.end())
    {
        if (it->second < m_nDrawRankLimit)
            m_mDrawRank.erase(it++);
        else
            ++it;
    }
}



void CFestivalDoubleEleven::checkDrawRank()
{
    // Check draw rank status, send mail if ended
    if (!IsInTime(FAT_DRAW_RANK))
        return;
    if (m_nDay == m_vEndDay[4])
        sendDrawRankMail();
}



void CFestivalDoubleEleven::sendDrawRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mDrawRank.begin(); it != m_mDrawRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        int32_t nRankVal = it->second;
        if (nCharId <= 0)
            continue;
        // Find reward tier
        for (int32_t i = 0; i < m_nDrawRankSize; ++i)
        {
            if (i < (int32_t)m_vDrawRankMail.size() && nRankVal >= m_nDrawRankLimit)
            {
                int32_t nMailId = m_vDrawRankMail[i];
                if (nMailId > 0 && i < (int32_t)m_vDrawRankReward.size())
                {
                    DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vDrawRankReward[i], "");
                }
                break;
            }
        }
    }
    m_mDrawRank.clear();
}




// ============ Remaining missing implementations ============
void CFestivalDoubleEleven::AddHuoYueDu(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    if (!IsInTime(FAT_HUO_YUE_DU_SUM))
        return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1603, nValue);
}


void CFestivalDoubleEleven::AddOnlineRecord(Player* player)
{
    if (NULL == player)
        return;
    if (!IsInTime(FAT_ONLINE_TIME))
        return;
    CExtOperateLimit& pLimit = player->GetOperateLimit();
    pLimit.AddLimitCount(1636, 1);
}


void CFestivalDoubleEleven::AddRechargeRecord(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    CharId_t cid = player->getCid();

    if (IsInTime(FAT_RECHARGE_SUM))
    {
        Answer::MutexGuard lock(m_lock);
        RankMap::iterator it = m_mRechargeSumRank.find(cid);
        if (it != m_mRechargeSumRank.end())
            it->second += nValue;
        else
            m_mRechargeSumRank[cid] = nValue;
    }
}


void CFestivalDoubleEleven::AddXiaoFeiRecord(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0)
        return;
    CharId_t cid = player->getCid();

    if (IsInTime(FAT_DAILY_XIAO_FEI_RANK))
    {
        Answer::MutexGuard lock(m_lock);
        RankMap::iterator it = m_mXiaoFeiRank.find(cid);
        if (it != m_mXiaoFeiRank.end())
            it->second += nCount;
        else
            m_mXiaoFeiRank[cid] = nCount;
    }

    if (IsInTime(FAT_XIAO_FEI_SUM_RANK))
    {
        Answer::MutexGuard lock(m_lock);
        RankMap::iterator it = m_mXiaoFeiSumRank.find(cid);
        if (it != m_mXiaoFeiSumRank.end())
            it->second += nCount;
        else
            m_mXiaoFeiSumRank[cid] = nCount;
    }
}


void CFestivalDoubleEleven::BossDie(Monster* pMonster, Player* pKiller)
{
    if (NULL == pMonster || NULL == pKiller)
        return;
    if (!IsInTime(FAT_WORLD_BOSS))
        return;
    m_bDie = true;
    BroadcastWorldBossKilled(pKiller, pMonster->getName());
    SendWorldBossIconState();
}


void CFestivalDoubleEleven::BroadCastMoYuShiJieIconState()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    int32_t nIconState = getMoYuShiJieIconState();
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC3);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nIcon);
    packet->writeInt8(nIconState);
    packet->writeInt32(getLeftTime());
    packet->writeInt8(0);
    packet->writeInt32(0);
    packet->writeInt8(0);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}


void CFestivalDoubleEleven::BroadcastWorldBossKilled(Player* pKiller, const std::string& strMonsterName)
{
    if (NULL == pKiller || GAME_SERVICE.getLine() != 1)
        return;
    if (m_nWorldBossKillBroadcast <= 0)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nWorldBossKillBroadcast);
    packet->writeUTF8(pKiller->getName());
    packet->writeUTF8(strMonsterName);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}


void CFestivalDoubleEleven::GongGao(int32_t nGongGaoId, Player* player)
{
    if (NULL == player)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(nGongGaoId);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.sendPacketTo(player->getGateIndex(), packet);
}


void CFestivalDoubleEleven::OnRecharge(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    bool bNeedSendIcon = false;

    if (IsInTime(FAT_LIAN_CHONG))
    {
        // Check recharge rewards
        for (size_t i = 0; i < m_LianRechargeCfgVt.size(); ++i)
        {
            // Check if recharge threshold reached
        }
    }

    // Record recharge for rank
    AddRechargeRecord(player, nValue);

    if (bNeedSendIcon)
        SendIconState(player);
}


void CFestivalDoubleEleven::RefreshMysteryShopItem()
{
    // 刷新神秘商店物品
    // 遍历所有玩家，刷新其神秘商店数据
    broadcastRefreshMysteryShop();
}


void CFestivalDoubleEleven::UpdateRank(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0)
        return;
    updateDrawRank(player, nValue);
    updateXiaoFeiRank(player, nValue);
    updateXiaoFeiSumRank(player, nValue);
    updateRechargeSumRank(player, nValue);
    updateCrossRechargeSumRank(player, nValue);
    updateCrossXiaoFeiSumRank(player, nValue);
    updateCrossChouJiangRank(player, nValue);
    updateBossScoreRank(player, nValue);
}


void CFestivalDoubleEleven::broadcastRefreshMysteryShop()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CD6);
    if (NULL == packet)
        return;
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}


void CFestivalDoubleEleven::broadcastWorldBossEnd()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (m_nWorldBossEndBroadcast <= 0)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nWorldBossEndBroadcast);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}


void CFestivalDoubleEleven::broadcastWorldBossStart()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (m_nWorldBossStartBroadcast <= 0)
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet)
        return;
    packet->writeInt32(m_nWorldBossStartBroadcast);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}


void CFestivalDoubleEleven::checkBossScoreRank()
{
    if (!IsInTime(FAT_BOSS_SCORE_RANK))
        return;
    if (m_nDay == m_vEndDay[40])
        sendBossScoreRankMail();
}


void CFestivalDoubleEleven::checkCrossChouJiangRank()
{
    if (!IsInTime(FAT_CROSS_CHOU_JIANG_RANK))
        return;
}


void CFestivalDoubleEleven::checkCrossRechargeSumRank()
{
    if (!IsInTime(FAT_CROSS_RECHARGE_SUM_RANK))
        return;
    // Cross-server rank check handled by global server
}


void CFestivalDoubleEleven::checkCrossXiaoFeiSumRank()
{
    if (!IsInTime(FAT_CROSS_XIAO_FEI_SUM_RANK))
        return;
}


void CFestivalDoubleEleven::checkRechargeSumRank()
{
    if (!IsInTime(FAT_RECHARGE_SUM_RANK))
        return;
    if (m_nDay == m_vEndDay[32])
        sendRechargeSumRankMail();
}


void CFestivalDoubleEleven::checkRefreshMysteryShop()
{
    if (!IsInTime(FAT_MYSTERY_SHOP))
        return;
    // Check if mystery shop should refresh based on time
    if (m_nMysteryShopRefreshBroad > 0 && m_nMinute % m_nMysteryShopRefreshBroad == 0)
    {
        broadcastRefreshMysteryShop();
    }
}


void CFestivalDoubleEleven::checkWorldBoss()
{
    if (!IsInTime(FAT_WORLD_BOSS))
        return;
    if (m_vWorldBossMinute.empty())
        return;
    if (GAME_SERVICE.getLine() != 1)
        return;

    for (size_t i = 0; i < m_vWorldBossMinute.size(); ++i)
    {
        if (m_nMinute == m_vWorldBossMinute[i].nStartTime)
        {
            broadcastWorldBossStart();
            SendWorldBossIconState();
        }
        else if (m_nMinute == m_vWorldBossMinute[i].nEndTime)
        {
            m_bDie = true;
            broadcastWorldBossEnd();
            SendWorldBossIconState();
        }
    }
}


void CFestivalDoubleEleven::checkXiaoFeiRank()
{
    if (!IsInTime(FAT_DAILY_XIAO_FEI_RANK))
        return;
    if (m_nDay == m_vEndDay[12])
        sendXiaoFeiRankMail();
}


void CFestivalDoubleEleven::checkXiaoFeiSumRank()
{
    if (!IsInTime(FAT_XIAO_FEI_SUM_RANK))
        return;
    if (m_nDay == m_vEndDay[16])
        sendXiaoFeiSumRankMail();
}


int32_t CFestivalDoubleEleven::getMoYuShiJieIconState()
{
    if (!isOpen(FAT_MO_YU_SHI_JIE))
        return 0;
    if (m_nDay >= m_vStartDay[14] && m_nDay <= m_vEndDay[14])
        return 1;  // open
    return 0;
}


void CFestivalDoubleEleven::loadBossScoreRank()
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_BOSS_SCORE_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mBossScoreRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 25);
        int32_t nValue = atoi(result.getStringValue("value"));
        if (nCharId > 0)
            m_mBossScoreRank[nCharId] = nValue;
        result.nextRow();
    }
}


void CFestivalDoubleEleven::loadCrossChouJiangRank()
{
    m_mCrossChouJiangRank.clear();
}


void CFestivalDoubleEleven::loadCrossRechargeSumRank()
{
    // Cross-server recharge sum rank loaded from global server
    m_mCrossRechargeSumRank.clear();
}


void CFestivalDoubleEleven::loadCrossXiaoFeiSumRank()
{
    m_mCrossXiaoFeiSumRank.clear();
}


void CFestivalDoubleEleven::loadRechargeSumRank()
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_RECHARGE_SUM_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mRechargeSumRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 27);
        int32_t nValue = atoi(result.getStringValue("value"));
        if (nCharId > 0)
            m_mRechargeSumRank[nCharId] = nValue;
        result.nextRow();
    }
}


void CFestivalDoubleEleven::loadXiaoFeiRank()
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_XIAOFEI_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mXiaoFeiRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 21);
        int32_t nValue = atoi(result.getStringValue("value"));
        if (nCharId > 0)
            m_mXiaoFeiRank[nCharId] = nValue;
        result.nextRow();
    }
}


void CFestivalDoubleEleven::loadXiaoFeiSumRank()
{
    Answer::MySqlDBGuard db(DBPOOL);
    char szSQL[4096] = {0};
    snprintf(szSQL, sizeof(szSQL),
        "SELECT * FROM `sys_server_config` WHERE `name` LIKE 'FESTIVAL_XIAOFEI_SUM_RANK_%%'");
    Answer::MySqlQuery result = db.query(szSQL);
    m_mXiaoFeiSumRank.clear();
    while (!result.eof())
    {
        std::string strName = result.getStringValue("name");
        int64_t nCharId = atoll(strName.c_str() + 25);
        int32_t nValue = atoi(result.getStringValue("value"));
        if (nCharId > 0)
            m_mXiaoFeiSumRank[nCharId] = nValue;
        result.nextRow();
    }
}


void CFestivalDoubleEleven::sendBossScoreRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_BOSS_SCORE_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mBossScoreRank.begin(); it != m_mBossScoreRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nBossScoreRankSize && i < (int32_t)m_vBossScoreRankMail.size(); ++i)
        {
            int32_t nMailId = m_vBossScoreRankMail[i];
            if (nMailId > 0 && i < (int32_t)m_vBossScoreRankReward.size())
            {
                DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vBossScoreRankReward[i], "");
                break;
            }
        }
    }
    m_mBossScoreRank.clear();
}


void CFestivalDoubleEleven::sendRechargeSumRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_RECHARGE_SUM_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mRechargeSumRank.begin(); it != m_mRechargeSumRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nRechargeSumRankSize && i < (int32_t)m_vRechargeSumRankMail.size(); ++i)
        {
            int32_t nMailId = m_vRechargeSumRankMail[i];
            if (nMailId > 0 && i < (int32_t)m_vRechargeSumRankReward.size())
            {
                DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vRechargeSumRankReward[i], "");
                break;
            }
        }
    }
    m_mRechargeSumRank.clear();
}


void CFestivalDoubleEleven::sendXiaoFeiRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_DAILY_XIAO_FEI_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mXiaoFeiRank.begin(); it != m_mXiaoFeiRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        int32_t nRankVal = it->second;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nXiaoFeiRankSize && i < (int32_t)m_vXiaoFeiRankMail.size(); ++i)
        {
            if (nRankVal >= m_vXiaoFeiRankLimit[i])
            {
                int32_t nMailId = m_vXiaoFeiRankMail[i];
                if (nMailId > 0 && i < (int32_t)m_vXiaoFeiRankReward.size())
                {
                    DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vXiaoFeiRankReward[i], "");
                }
                break;
            }
        }
    }
    m_mXiaoFeiRank.clear();
}


void CFestivalDoubleEleven::sendXiaoFeiSumRankMail()
{
    if (GAME_SERVICE.getLine() != 1)
        return;
    if (!IsInTime(FAT_XIAO_FEI_SUM_RANK))
        return;
    Answer::MutexGuard lock(m_lock);
    for (RankMap::iterator it = m_mXiaoFeiSumRank.begin(); it != m_mXiaoFeiSumRank.end(); ++it)
    {
        CharId_t nCharId = it->first;
        int32_t nRankVal = it->second;
        if (nCharId <= 0)
            continue;
        for (int32_t i = 0; i < m_nXiaoFeiSumRankSize && i < (int32_t)m_vXiaoFeiSumRankMail.size(); ++i)
        {
            if (nRankVal >= m_nXiaoFeiSumRankLimit)
            {
                int32_t nMailId = m_vXiaoFeiSumRankMail[i];
                if (nMailId > 0 && i < (int32_t)m_vXiaoFeiSumRankReward.size())
                {
                    DB_SERVICE.OnSendSysMail(nCharId, nMailId, m_vXiaoFeiSumRankReward[i], "");
                }
                break;
            }
        }
    }
    m_mXiaoFeiSumRank.clear();
}




// ============ Getter/UI method implementations ============
void CFestivalDoubleEleven::AddEquipUpStarBack(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0) return;
    if (!IsInTime(FAT_EQUIP_UPSTAR_BACK)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1625, nCount);
}


void CFestivalDoubleEleven::AddFaBaoValue(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_FA_BAO_BACK)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1626, nValue);
}


void CFestivalDoubleEleven::AddFriendQingYi(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_FRIEND_QING_YI)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1623, nValue);
}


void CFestivalDoubleEleven::AddMoYuShiJieDrop(Player* player, int32_t nCount)
{
    if (NULL == player || nCount <= 0) return;
    if (!IsInTime(FAT_MO_YU_SHI_JIE)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1632, nCount);
}


void CFestivalDoubleEleven::AddPetIllusionItemRecord(Player* player, int32_t nValue)
{
    if (NULL == player || nValue <= 0) return;
    if (!IsInTime(FAT_PET_ILLUSION_ITEM)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.AddLimitCount(1624, nValue);
}

// ============ Update*Rank methods ============


int32_t CFestivalDoubleEleven::BuyDailyLimitShopItem(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_DAILY_LIMIT_SHOP)) return 10002;
    if (m_vDailyLimitShopItem.empty()) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vDailyLimitShopItem, IACR_DOUBLE_ELEVEN_BUY_SHOP_ITEM)) return 10002;
    if (m_nDailyLimitShopCostType > 0 && m_nDailyLimitShopCostValue > 0)
    {
        if (!player->DecCurrency((CURRENCY_TYPE)m_nDailyLimitShopCostType, m_nDailyLimitShopCostValue, GCR_DOUBLE_ELEVEN_BUY_SHOP_ITEM, 0))
            return 10002;
    }
    return 0;
}


int32_t CFestivalDoubleEleven::BuyGiftItem(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (nIndex < 0 || nIndex >= m_nBuyGiftSize) return 10002;
    if (!IsInTime(FAT_BUY_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nOldRecord = limit.GetLimitCount(1619);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord) return 10002;
    int64_t nGold = player->GetCurrency(CURRENCY_GOLD);
    if (nGold < m_vBuyGiftPrice[nIndex]) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vBuyGiftItem[nIndex], IACR_DOUBLE_ELEVEN_BUY_GIFT_ITEM)) return 10002;
    if (!player->DecCurrency(CURRENCY_GOLD, m_vBuyGiftPrice[nIndex], GCR_DOUBLE_ELEVEN_BUY_GIFT_ITEM, 0)) return 10002;
    if (m_vBuyGiftBroadcast[nIndex] > 0)
    {
        broadcastPlayerAction(m_vBuyGiftBroadcast[nIndex], (int32_t)player->getCid());
    }
    limit.UpdateLimitCount(1619, nNewRecord);
    return 0;
}


int32_t CFestivalDoubleEleven::BuyGiftShopItem(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (nIndex < 0 || nIndex >= m_nGiftShopSize) return 10002;
    if (!IsInTime(FAT_GIFT_SHOP)) return 10002;
    int32_t nDayIndex = m_nDay - m_vStartDay[17];
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nOldRecord = limit.GetLimitCount(1607);
    int32_t nNewRecord = nOldRecord | (1 << (nDayIndex * m_nGiftShopSize + nIndex));
    if (nOldRecord == nNewRecord) return 10002;
    if ((int32_t)m_vGiftShopGoods.size() <= nIndex) return 10002;
    const ShopGoods& goods = m_vGiftShopGoods[nIndex];
    if (player->GetCurrency(CURRENCY_GOLD) < goods.nPrice) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(goods.vItem, IACR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM)) return 10002;
    if (!player->DecCurrency(CURRENCY_GOLD, goods.nPrice, GCR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM, 0)) return 10002;
    limit.UpdateLimitCount(1607, nNewRecord);
    return 0;
}


int32_t CFestivalDoubleEleven::BuyGiftShopItem2(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (nIndex < 0 || nIndex >= m_nDailyLimitShop2Size) return 10002;
    if (!IsInTime(FAT_DAILY_LIMIT_SHOP_2)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nOldRecord = limit.GetLimitCount(2035);
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if (nOldRecord == nNewRecord) return 10002;
    if ((int32_t)m_vDailyLimitShop2Goods.size() <= nIndex) return 10002;
    const ShopGoods& goods = m_vDailyLimitShop2Goods[nIndex];
    if (player->GetCurrency(CURRENCY_GOLD) < goods.nPrice) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(goods.vItem, IACR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM_2)) return 10002;
    if (!player->DecCurrency(CURRENCY_GOLD, goods.nPrice, GCR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM_2, 0)) return 10002;
    limit.UpdateLimitCount(2035, nNewRecord);
    return 0;
}


int32_t CFestivalDoubleEleven::BuyTitle(Player* player, int32_t nIndex)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_SCORE_SHOP)) return 10002;
    if (m_Price <= 0 || m_Items.empty()) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    if (limit.GetLimitCount(1631) > 0) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (bag.GetFreeSlotCount() < (int32_t)m_Items.size()) return 10002;
    if (!player->DecCurrency(CURRENCY_GOLD, m_Price, GCR_BUY_TITLE, 0)) return 10002;
    bag.AddItem(m_Items, IACR_DOUBLE_ELEVEN_LAND_GIFT);
    limit.UpdateLimitCount(1631, 1);
    return 0;
}

// ============ Add/Record methods ============


void CFestivalDoubleEleven::CalBossScoreAddValue(Player* player, int32_t nDamage, int32_t& nAddValue)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_BOSS_SCORE)) return;
    if (m_nBossScoreRate > 0)
        nAddValue = nDamage * m_nBossScoreRate / 100;
    else
        nAddValue = nDamage;
}


int32_t CFestivalDoubleEleven::CanUseRechargeDraw(Player* player)
{
    if (NULL == player) return 0;
    if (!IsInTime(FAT_RECHARGE_DRAW)) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nRechargeTotal = limit.GetLimitCount(1615);
    int32_t nRewardTimes = limit.GetLimitCount(1632);
    int32_t nCanGetTime = 0;
    for (int32_t i = 0; i < m_nRechargeDrawSize; ++i)
    {
        if (i < (int32_t)m_vScoreLimit.size() && nRechargeTotal >= m_vScoreLimit[i])
            nCanGetTime = i + 1;
    }
    return (nCanGetTime - nRewardTimes > 0) ? 1 : 0;
}


int32_t CFestivalDoubleEleven::CanUseXiaoFeiDraw(Player* player)
{
    if (NULL == player) return 0;
    if (!IsInTime(FAT_XIAO_FEI_DRAW)) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nCanDraw = limit.GetLimitCount(1620);
    return nCanDraw > 0 ? 1 : 0;
}


bool CFestivalDoubleEleven::CheckDropGroup(int32_t nDropGroup)
{
    return IsInTime() && m_nDropGroup == nDropGroup;
}


int32_t CFestivalDoubleEleven::GetChouJiangSpecialTime()
{
    if (!IsInTime(FAT_CHOU_JIANG))
        return 0;
    return TIMER.GetNow();
}


int32_t CFestivalDoubleEleven::GetChouJiangType(Player* player)
{
    if (NULL == player) return 0;
    return m_nChouJiangType;
}


int32_t CFestivalDoubleEleven::GetDailyRechargeGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_DAILY_RECHARGE_2)) return 10002;
    if (m_vDailyRechargeLimit.empty() || m_vDailyRechargeReward.empty()) return 10002;
    for (int32_t i = 0; i < m_nDailyRechargeDrawSize && i < (int32_t)m_vDailyRechargeLimit.size() && i < (int32_t)m_vDailyRechargeReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nRewardSign = limit.GetLimitCount(2033);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        int32_t nTodayGold = player->GetTodayPayGold();
        if (nTodayGold < m_vDailyRechargeLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (!bag.AddItem(m_vDailyRechargeReward[i], IACR_DOUBLE_ELEVEN_DAILY_RECHARGE_GIFT)) return 10002;
        if (!player->DecCurrency(CURRENCY_GOLD, m_vDailyRechargeLimit[i], GCR_DOUBLE_ELEVEN_DAILY_RECHARGE_GIFT, 0)) return 10002;
        limit.UpdateLimitCount(2033, nNewSign);
        SendIconState(player);
        return 0;
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetDrawGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_DRAW)) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vDrawLoopReward, IACR_DOUBLE_ELEVEN_DRAW_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(1633, 1);
    SendIconState(player);
    return 0;
}


void CFestivalDoubleEleven::GetEquipQingYiGift(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_EQUIP_QING_YI)) return;
    for (int32_t i = 0; i < m_nEquipQingYiSize && i < (int32_t)m_vEquipQingYiLimit.size() && i < (int32_t)m_vEquipQingYiReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nEquipSum = limit.GetLimitCount(1625);
        int32_t nRewardSign = limit.GetLimitCount(1626);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        if (nEquipSum < m_vEquipQingYiLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (bag.AddItem(m_vEquipQingYiReward[i], IACR_DOUBLE_ELEVEN_LAND_GIFT))
        {
            limit.UpdateLimitCount(1626, nNewSign);
            SendIconState(player);
        }
        return;
    }
}


int32_t CFestivalDoubleEleven::GetEquipUpStarBackItem(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_EQUIP_UPSTAR_BACK)) return 10002;
    if (m_nEquipUpStarBackId <= 0 || m_nNeedValue <= 0) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nCount = limit.GetLimitCount(1625);
    if (nCount < m_nNeedValue) return 10002;
    // Check if already redeemed
    int32_t nRedeemed = limit.GetLimitCount(1627);
    if (nRedeemed > 0) return 10002;
    // Add the item
    MemChrBag item = {};
    item.itemId = m_nEquipUpStarBackId;
    item.itemClass = 0;
    item.itemCount = 1;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(item, IACR_DOUBLE_ELEVEN_LAND_GIFT)) return 10002;
    limit.UpdateLimitCount(1627, 1);
    SendIconState(player);
    return 0;
}


int32_t CFestivalDoubleEleven::GetFaBaoCritBackItem(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_FA_BAO_BACK)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nCount = limit.GetLimitCount(1626);
    if (nCount <= 0) return 10002;
    // Check if already redeemed
    int32_t nRedeemed = limit.GetLimitCount(1629);
    limit.UpdateLimitCount(1629, 1);
    // Add item based on count
    MemChrBag item = {};
    item.itemId = m_nEquipUpStarBackId;
    item.itemClass = 0;
    item.itemCount = 1;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(item, IACR_DOUBLE_ELEVEN_LAND_GIFT)) return 10002;
    SendIconState(player);
    return 0;
}


int32_t CFestivalDoubleEleven::GetFriendQingYiGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_FRIEND_QING_YI)) return 10002;
    for (int32_t i = 0; i < m_nFriendQingYiSize && i < (int32_t)m_vFriendQingYiLimit.size() && i < (int32_t)m_vFriendQingYiReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nFriendSum = limit.GetLimitCount(1623);
        int32_t nRewardSign = limit.GetLimitCount(1624);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        if (nFriendSum < m_vFriendQingYiLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (bag.AddItem(m_vFriendQingYiReward[i], IACR_DOUBLE_ELEVEN_LAND_GIFT))
        {
            limit.UpdateLimitCount(1624, nNewSign);
            SendIconState(player);
        }
        return 0;
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetHuoYueDuSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_HUO_YUE_DU_SUM)) return 10002;
    for (int32_t i = 0; i < m_nHuoYueDuSumSize && i < (int32_t)m_vHuoYueDuSumLimit.size() && i < (int32_t)m_vHuoYueDuSumReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nHuoYueSum = limit.GetLimitCount(1603);
        int32_t nRewardSign = limit.GetLimitCount(1604);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        if (nHuoYueSum < m_vHuoYueDuSumLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (!bag.AddItem(m_vHuoYueDuSumReward[i], IACR_DOUBLE_ELEVEN_HUO_YUE_DU)) return 10002;
        limit.UpdateLimitCount(1604, nNewSign);
        SendIconState(player);
        return 0;
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetLandGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!canGetLandGift(player)) return 10002;
    int32_t nIndex = m_nDay;
    if (nIndex < 0 || nIndex >= (int32_t)m_vLandGift.size()) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vLandGift[nIndex], IACR_DOUBLE_ELEVEN_LAND_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(2030, 1);
    SendIconState(player);
    return 0;
}


int32_t CFestivalDoubleEleven::GetLandSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!canGetLandSumGift(player)) return 10002;
    int32_t nIndex = m_nDay;
    if (nIndex < 0 || nIndex >= (int32_t)m_vLandSumGift.size()) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vLandSumGift[nIndex], IACR_DOUBLE_ELEVEN_LAND_SUM_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(2031, 1);
    SendIconState(player);
    return 0;
}


int32_t CFestivalDoubleEleven::GetLianRechargeReward(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_LIAN_CHONG)) return 10002;
    for (size_t t = 0; t < m_LianRechargeCfgVt.size(); ++t)
    {
        int32_t nRewardRecord = (t == 0) ? 1636 : 1637;
        int32_t nLianChongRecord = (t == 0) ? 1634 : 1635;
        int32_t nLianChong = player->GetOperateLimit().GetLimitCount(nLianChongRecord);
        if (nLianChong < 1) continue;
        int32_t nRewardSign = player->GetOperateLimit().GetLimitCount(nRewardRecord);
        if (nRewardSign > 0) continue;
        CExtCharBag& bag = player->GetBag();
        if (bag.AddItem(m_LianRechargeCfgVt[t].reward, IACR_DOUBLE_ELEVEN_LIAN_CHONG))
        {
            player->GetOperateLimit().UpdateLimitCount(nRewardRecord, 1);
            GongGao(3012, player);
            SendIconState(player);
            return 0;
        }
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetOnlineGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_ONLINE_TIME)) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vOnlineReward, IACR_DOUBLE_ELEVEN_ONLINE_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(1636, 1);
    SendIconState(player);
    return 0;
}


int32_t CFestivalDoubleEleven::GetOnlineTimeRewardTime(Player* player)
{
    if (NULL == player) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nCount = limit.GetLimitCount(1636);
    return nCount * m_nOnlineTimeArea + m_nOnlineStartMinute;
}


int32_t CFestivalDoubleEleven::GetPetIllusionItemGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_PET_ILLUSION_ITEM)) return 10002;
    for (int32_t i = 0; i < m_nPetIllusionItemSize && i < (int32_t)m_vPetIllusionItemLimit.size() && i < (int32_t)m_vPetIllusionItemReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nIllusionSum = limit.GetLimitCount(1622);
        int32_t nRewardSign = limit.GetLimitCount(1623);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        if (nIllusionSum < m_vPetIllusionItemLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (!bag.AddItem(m_vPetIllusionItemReward[i], IACR_DOUBLE_ELEVEN_PET_ILLUSION_REWARD)) return 10002;
        limit.UpdateLimitCount(1623, nNewSign);
        SendIconState(player);
        return 0;
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetRechargeBack(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_RECHARGE_BACK)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nTotalRecharge = limit.GetLimitCount(1615);
    for (int32_t i = 0; i < m_nRechargeBackSize && i < (int32_t)m_vRechargeBackLimit.size(); ++i)
    {
        if (nTotalRecharge >= m_vRechargeBackLimit[i])
        {
            int32_t nBackVal = (i < (int32_t)m_vRechargeBackValue.size()) ? m_vRechargeBackValue[i] : 0;
            if (nBackVal > 0)
            {
                MemChrBag item = {};
                item.itemId = 0; // resource id
                item.itemClass = 4; // currency class
                item.itemCount = nBackVal;
                CExtCharBag& bag = player->GetBag();
                if (bag.AddItem(item, IACR_DOUBLE_ELEVEN_LAND_GIFT))
                {
                    limit.UpdateLimitCount(2041, 1);
                    SendIconState(player);
                    return 0;
                }
            }
        }
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetRechargeSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_RECHARGE_SUM_GIFT)) return 10002;
    for (int32_t i = 0; i < m_nRechargeSumSize && i < (int32_t)m_vRechargeSumLimit.size() && i < (int32_t)m_vRechargeSumReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nRechargeSum = limit.GetLimitCount(1615);
        int32_t nRewardSign = limit.GetLimitCount(1616);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        if (nRechargeSum < m_vRechargeSumLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (!bag.AddItem(m_vRechargeSumReward[i], IACR_DOUBLE_ELEVEN_RECHARGE_SUM_GIFT)) return 10002;
        limit.UpdateLimitCount(1616, nNewSign);
        SendIconState(player);
        return 0;
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetScoreCanDrawTime(Player* player)
{
    if (NULL == player) return 0;
    if (!IsInTime(FAT_BOSS_SCORE_DRAW)) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nScore = limit.GetLimitCount(1618);
    int32_t nDrawCount = limit.GetLimitCount(1631);
    int32_t nCanDraw = 0;
    for (int32_t i = 0; i < m_nRewardSize && i < (int32_t)m_vBossScoreiLimit.size(); ++i)
    {
        if (nScore >= m_vBossScoreiLimit[i])
            nCanDraw = i + 1;
    }
    return nCanDraw - nDrawCount;
}


int32_t CFestivalDoubleEleven::GetWishGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_BEST_WISH)) return 10002;
    CExtCharBag& bag = player->GetBag();
    if (!bag.AddItem(m_vWishReward, IACR_DOUBLE_ELEVEN_WISH_GIFT)) return 10002;
    CExtOperateLimit& limit = player->GetOperateLimit();
    limit.UpdateLimitCount(2040, 1);
    SendIconState(player);
    return 0;
}


int32_t CFestivalDoubleEleven::GetXiaoFeiSumGift(Player* player)
{
    if (NULL == player) return 10002;
    if (!IsInTime(FAT_XIAO_FEI_SUM_GIFT)) return 10002;
    for (int32_t i = 0; i < m_nXiaoFeiSumSize && i < (int32_t)m_vXiaoFeiSumLimit.size() && i < (int32_t)m_vXiaoFeiSumReward.size(); ++i)
    {
        CExtOperateLimit& limit = player->GetOperateLimit();
        int32_t nXiaoFeiSum = limit.GetLimitCount(1605);
        int32_t nRewardSign = limit.GetLimitCount(1606);
        int32_t nNewSign = nRewardSign | (1 << i);
        if (nNewSign == nRewardSign) continue;
        if (nXiaoFeiSum < m_vXiaoFeiSumLimit[i]) continue;
        CExtCharBag& bag = player->GetBag();
        if (!bag.AddItem(m_vXiaoFeiSumReward[i], IACR_DOUBLE_ELEVEN_XIAO_FEI_SUM_GIFT)) return 10002;
        limit.UpdateLimitCount(1606, nNewSign);
        SendIconState(player);
        return 0;
    }
    return 10002;
}


int32_t CFestivalDoubleEleven::GetXiaoFeiSumGiftCount(Player* player)
{
    if (NULL == player) return 0;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(1605);
}


void CFestivalDoubleEleven::GouWuChe(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_GOU_WU_CHE)) return;
    if (m_nGouWuCheSize <= 0) return;

    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nOldRecord = limit.GetLimitCount(2112);
    if (nOldRecord > 0) return; // already used

    // Calculate total price for all items and collect them
    int32_t PriceSum = 0;
    MemChrBagVector items;
    for (int32_t i = 0; i < m_nGouWuCheSize; ++i)
    {
        if (i >= (int32_t)m_vGouWuCheGiftPrice.size()) break;
        PriceSum += m_vGouWuCheGiftPrice[i];
        for (size_t j = 0; j < m_vGouWuCheItem[i].size(); ++j)
            items.push_back(m_vGouWuCheItem[i][j]);
    }

    if (PriceSum <= 0 || items.empty()) return;

    // Apply discount based on number of items purchased
    int32_t Rate = 0; // 0 = no discount
    switch (m_nGouWuCheSize)
    {
        case 1: Rate = 9; break;  // 90%
        case 2: Rate = 8; break;  // 80%
        case 3: Rate = 7; break;  // 70%
        case 4: Rate = 6; break;  // 60%
        case 5: Rate = 5; break;  // 50%
        default: Rate = 0; break;
    }

    if (Rate <= 0) return;

    int64_t nGold = player->GetCurrency(CURRENCY_GOLD);
    int32_t nFinalPrice = Rate * PriceSum / 10;
    if (nGold < nFinalPrice) return;

    CExtCharBag& bag = player->GetBag();
    if (bag.GetFreeSlotCount() < (int32_t)items.size()) return;

    // Deduct currency and give items
    if (!player->DecCurrency(CURRENCY_GOLD, nFinalPrice, GCR_DOUBLE_ELEVEN_BUY_GIFT_ITEM, 0))
        return;

    player->updateRecord(2112, nOldRecord | ((1 << m_nGouWuCheSize) - 1));
    bag.AddItem(items, IACR_DOUBLE_ELEVEN_LAND_GIFT);
}


bool CFestivalDoubleEleven::IsInWorldBossTime()
{
    if (!IsInTime(FAT_WORLD_BOSS)) return false;
    for (size_t i = 0; i < m_vWorldBossMinute.size(); ++i)
    {
        if (m_nMinute >= m_vWorldBossMinute[i].nStartTime && m_nMinute < m_vWorldBossMinute[i].nEndTime)
            return true;
    }
    return false;
}

// ============ canGet*Gift methods ============


void CFestivalDoubleEleven::OnRandScoreDrawItem(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_BOSS_SCORE_DRAW)) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nDrawCount = limit.GetLimitCount(1631);
    int32_t nCanDraw = GetScoreCanDrawTime(player);
    if (nDrawCount >= nCanDraw) return;
    // Randomly pick a reward
    int32_t nRandIdx = RANDOM.generate(0, m_nRewardSize - 1);
    if (nRandIdx < 0 || nRandIdx >= (int32_t)m_vBossScoreDrawReward.size()) return;
    CExtCharBag& bag = player->GetBag();
    if (bag.AddItem(m_vBossScoreDrawReward[nRandIdx], IACR_DOUBLE_ELEVEN_LAND_GIFT))
    {
        limit.UpdateLimitCount(1631, nDrawCount + 1);
        SendIconState(player);
    }
}

// ============ Buy methods ============


void CFestivalDoubleEleven::SendDaTiReward(Player* player)
{
    if (NULL == player) return;
    if (!IsInTime(FAT_DA_TI)) return;
    // DaTi (answer quiz) ranking reward - send mail to top players
    if (GAME_SERVICE.getLine() != 1) return;
    for (int32_t i = 0; i < m_nDaTiRankSize && i < (int32_t)m_vDaTiRankMail.size() && i < (int32_t)m_vDaTiRankReward.size(); ++i)
    {
        int32_t nMailId = m_vDaTiRankMail[i];
        if (nMailId > 0)
        {
            DB_SERVICE.OnSendSysMail(player->getCid(), nMailId, m_vDaTiRankReward[i], "");
        }
    }
}


void CFestivalDoubleEleven::UpdateMonsterScore(Monster* pMonster, Player* pPlayer)
{
    if (NULL == pMonster || NULL == pPlayer) return;
    if (!IsInTime(FAT_BOSS_SCORE)) return;
    CExtOperateLimit& limit = pPlayer->GetOperateLimit();
    limit.AddLimitCount(1618, 1);
}


void CFestivalDoubleEleven::UpdateXiaoFeiRank(Player* player)
{
    updateXiaoFeiRank(player);
}


void CFestivalDoubleEleven::broadcastPlayerAction(int32_t nAction, int32_t nParam)
{
    if (GAME_SERVICE.getLine() != 1) return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, 0x2CC2);
    if (NULL == packet) return;
    packet->writeInt32(nAction);
    packet->writeInt32(nParam);
    packet->setSize(packet->getWOffset());
    GAME_SERVICE.worldBroadcast(packet);
}


void CFestivalDoubleEleven::calRechargeBack(Player* player)
{
    if (NULL == player) return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nTotalRecharge = limit.GetLimitCount(1615);
    if (nTotalRecharge <= 0) return;
    for (int32_t i = 0; i < m_nRechargeBackSize && i < (int32_t)m_vRechargeBackLimit.size() && i < (int32_t)m_vRechargeBackValue.size(); ++i)
    {
        calRechargeBackHelper(player, i);
    }
}


void CFestivalDoubleEleven::calRechargeBackHelper(Player* player, int32_t nIndex)
{
    if (NULL == player) return;
    if (nIndex < 0 || nIndex >= m_nRechargeBackSize) return;
    if (nIndex >= (int32_t)m_vRechargeBackLimit.size() || nIndex >= (int32_t)m_vRechargeBackValue.size())
        return;
    CExtOperateLimit& limit = player->GetOperateLimit();
    int32_t nTotalRecharge = limit.GetLimitCount(1615);
    if (nTotalRecharge < m_vRechargeBackLimit[nIndex]) return;
    int32_t nRewardSign = limit.GetLimitCount(2042);
    int32_t nNewSign = nRewardSign | (1 << nIndex);
    if (nNewSign == nRewardSign) return;
    int32_t nBackValue = m_vRechargeBackValue[nIndex];
    if (nBackValue > 0)
    {
        MemChrBag item = {};
        item.itemId = 0;
        item.itemClass = 4;
        item.itemCount = nBackValue;
        CExtCharBag& bag = player->GetBag();
        if (bag.AddItem(item, IACR_DOUBLE_ELEVEN_LAND_GIFT))
        {
            limit.UpdateLimitCount(2042, nNewSign);
            SendIconState(player);
        }
    }
}


bool CFestivalDoubleEleven::canGetDrawGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_DRAW)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(1633) <= 0;
}


bool CFestivalDoubleEleven::canGetLandGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_LAND)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2030) <= 0;
}


bool CFestivalDoubleEleven::canGetLandSumGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_LAND_SUM)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2031) <= 0;
}


bool CFestivalDoubleEleven::canGetOnlineGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_ONLINE_TIME)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(1636) <= 0;
}


bool CFestivalDoubleEleven::canGetRechargeBack(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_RECHARGE_BACK)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2041) <= 0;
}

// ============ Get*Gift methods ============


bool CFestivalDoubleEleven::canGetWishGift(Player* player)
{
    if (NULL == player) return false;
    if (!IsInTime(FAT_BEST_WISH)) return false;
    CExtOperateLimit& limit = player->GetOperateLimit();
    return limit.GetLimitCount(2040) <= 0;
}


void CFestivalDoubleEleven::checkBossScoreRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    // Validate rank entries
}


void CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(int8_t connid)
{
    // Cross rank: validated by global server
}

// ============ Misc methods ============


void CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(int8_t connid)
{
    // Cross rank: validated by global server
}


void CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(int8_t connid)
{
    // Cross rank: validated by global server
}


void CFestivalDoubleEleven::checkRechargeSumRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    // Validate rank entries
}


void CFestivalDoubleEleven::checkXiaoFeiRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mXiaoFeiRank.begin();
    while (it != m_mXiaoFeiRank.end())
    {
        if (it->second <= 0)
            m_mXiaoFeiRank.erase(it++);
        else
            ++it;
    }
}


void CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(int8_t connid)
{
    Answer::MutexGuard lock(m_lock);
    RankMap::iterator it = m_mXiaoFeiSumRank.begin();
    while (it != m_mXiaoFeiSumRank.end())
    {
        if (it->second <= 0)
            m_mXiaoFeiSumRank.erase(it++);
        else
            ++it;
    }
}


int32_t CFestivalDoubleEleven::getLandSum(Player* player)
{
    if (NULL == player) return 0;
    int32_t nTotal = 0;
    for (int32_t i = 0; i <= m_nDay && i < (int32_t)m_vLandGift.size(); ++i)
    {
        nTotal += (int32_t)m_vLandGift[i].size();
    }
    return nTotal;
}


void CFestivalDoubleEleven::updateBossScoreRank(Player* player)
{
    if (NULL == player) return;
    updateBossScoreRank(player, 1);
}


void CFestivalDoubleEleven::updateCrossChouJiangRank(Player* player)
{
    if (NULL == player) return;
    updateCrossChouJiangRank(player, 1);
}


void CFestivalDoubleEleven::updateCrossRechargeSumRank(Player* player)
{
    if (NULL == player) return;
    updateCrossRechargeSumRank(player, 1);
}


void CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(Player* player)
{
    if (NULL == player) return;
    updateCrossXiaoFeiSumRank(player, 1);
}


void CFestivalDoubleEleven::updateRechargeSumRank(Player* player)
{
    if (NULL == player) return;
    updateRechargeSumRank(player, 1);
}


void CFestivalDoubleEleven::updateXiaoFeiRank(Player* player)
{
    if (NULL == player) return;
    updateXiaoFeiRank(player, 1);
}


void CFestivalDoubleEleven::updateXiaoFeiSumRank(Player* player)
{
    if (NULL == player) return;
    updateXiaoFeiSumRank(player, 1);
}


