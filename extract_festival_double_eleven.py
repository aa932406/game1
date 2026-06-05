#!/usr/bin/env python3
"""Extract CFestivalDoubleEleven from decompiled code, generate .h and .cpp files."""

import re
import os

decompiled_path = 'gameserver/decompiled/CFestivalDoubleEleven.cpp'
header_path = 'gameserver/FestivalDoubleEleven.h'
cpp_path = 'gameserver/FestivalDoubleEleven.cpp'

with open(decompiled_path, 'r') as f:
    content = f.read()

# ============ 1. Extract all member variables ============
member_vars = set()
for m in re.finditer(r'this(?:a)?->(m_\w+)', content):
    member_vars.add(m.group(1))

# Classify by type based on naming patterns
int_members = sorted([v for v in member_vars if re.match(r'm_n[A-Z]', v) or re.match(r'm_n[a-z]', v)])
bool_members = sorted([v for v in member_vars if v.startswith('m_b')])
string_members = sorted([v for v in member_vars if v.startswith('m_s')])
map_members = sorted([v for v in member_vars if v.startswith('m_m')])
vector_members = sorted([v for v in member_vars if v.startswith('m_v')])
other_members = sorted([v for v in member_vars if v not in int_members + bool_members + string_members + map_members + vector_members])

# ============ 2. Extract all method signatures ============
# Find method definitions
methods = []
for m in re.finditer(r'^void __cdecl CFestivalDoubleEleven::(\w+)\(([^)]*)\)', content, re.MULTILINE):
    name = m.group(1)
    params_str = m.group(2).strip()
    
    # Parse params: remove CFestivalDoubleEleven *const this, convert types
    params = []
    if params_str:
        for p in params_str.split(','):
            p = p.strip()
            if 'CFestivalDoubleEleven *const this' in p:
                continue  # skip implicit this
            # Clean up parameter
            p = re.sub(r'\*const ', '* ', p)
            p = re.sub(r'\bconst \b', '', p)
            p = re.sub(r'\s+', ' ', p).strip()
            if p and p != '...':
                params.append(p)
    
    methods.append((name, params))

# ============ 3. Generate Header ============
header = '''#ifndef __TPOC_FESTIVAL_DOUBLE_ELEVEN_H__
#define __TPOC_FESTIVAL_DOUBLE_ELEVEN_H__

#include "DataStructs.h"
#include "ItemData.h"
#include <vector>
#include <map>
#include <string>

class Player;
class Monster;

enum FESTIVAL_ACTIVITY_TYPE
{
    FAT_NONE = 0,
    FAT_LAND = 1,
    FAT_DAILY_RECHARGE = 2,
    FAT_DRAW = 3,
    FAT_DRAW_RANK = 4,
    FAT_EXCHANGE = 5,
    FAT_WORLD_BOSS = 6,
    FAT_HUO_YUE_DU_SUM = 7,
    FAT_DAILY_LIMIT_SHOP = 8,
    FAT_LAND_SUM = 9,
    FAT_ONLINE_TIME = 10,
    FAT_BEST_WISH = 11,
    FAT_DAILY_XIAO_FEI_RANK = 12,
    FAT_EQUIP_QING_YI = 13,
    FAT_FRIEND_QING_YI = 14,
    FAT_MO_YU_SHI_JIE = 15,
    FAT_XIAO_FEI_SUM_GIFT = 16,
    FAT_DAILY_RECHARGE_2 = 17,
    FAT_XIAO_FEI_DRAW = 18,
    FAT_RECHARGE_DRAW = 19,
    FAT_LIAN_CHONG = 20,
    FAT_EQUIP_UPSTAR_BACK = 21,
    FAT_FA_BAO_BACK = 22,
    FAT_RECHARGE_BACK = 23,
    FAT_CHOU_JIANG = 24,
    FAT_GIFT_SHOP = 25,
    FAT_GOU_WU_CHE = 26,
    FAT_PET_EQUIP_CHOU_JIANG = 27,
    FAT_BUY_GIFT = 28,
    FAT_SCORE_SHOP = 29,
    FAT_MYSTERY_SHOP = 30,
    FAT_DA_TI = 31,
    FAT_RECHARGE_SUM_GIFT = 32,
    FAT_DAILY_LIMIT_SHOP_2 = 33,
    FAT_RECHARGE_SUM_RANK = 34,
    FAT_CROSS_RECHARGE_SUM_RANK = 35,
    FAT_CROSS_XIAO_FEI_SUM_RANK = 36,
    FAT_CROSS_CHOU_JIANG_RANK = 37,
    FAT_BOSS_SCORE = 38,
    FAT_BOSS_SCORE_RANK = 39,
    FAT_BOSS_SCORE_DRAW = 40,
    FAT_XIAO_FEI_SUM_RANK = 41,
    FAT_PET_ILLUSION_ITEM = 42,
    FAT_BUY_PET_GIFT = 43,
    FAT_RECHARGE_SUM = 44,
    FAT_MO_LING = 45,
    FAT_RECHARGE = 46,
};

struct TimeArea
{
    int32_t nStartTime;
    int32_t nEndTime;
};

struct ShopGoods
{
    int32_t nItemType;
    int32_t nItemId;
    int32_t nItemCount;
    int32_t nPriceType;
    int32_t nPriceCount;
    int32_t nLimit;
};

struct LianRechargeCfg
{
    int32_t nDay;
    int32_t nRecharge;
    MemChrBagVector reward;
    int32_t nMailId;
};

struct RateItem
{
    int32_t nItemType;
    int32_t nItemId;
    int32_t nItemCount;
    int32_t nRate;
};

class CFestivalDoubleEleven
{
public:
    CFestivalDoubleEleven();
    ~CFestivalDoubleEleven();
    
    static CFestivalDoubleEleven* instance();
    
    void Init(int32_t line);
    void HotUpdate();
    void OnDaySwitch();
    void OnNewMinute(int32_t nMinute);
    void OnRecharge(Player* player, int32_t nValue);
    
    bool IsInTime();
    bool IsInTime(FESTIVAL_ACTIVITY_TYPE nType);
    bool IsInWorldBossTime();
    bool isOpen(FESTIVAL_ACTIVITY_TYPE nType);
    bool IsOpen();
    bool needShowIcon();
    void getIconState(int32_t& nIconId);
    int32_t GetIconState();
    void SendIconState(Player* player);
    void SendWorldBossIconState();
    void GetWorldBossIconState(int32_t& nIconId);
    void GetMoYuShiJieIconState(int32_t& nIconId);
    void hideIcon(int32_t nIconId);
    int32_t getLeftTime();
    void SendActivityInfo(Player* player);
    
    // Rank methods
    void loadRankData(int32_t line);
    void resetRankData(int32_t line);
    void resetPlayerData();
    void saveVersion(int32_t line);
    int32_t loadVersion(int32_t line);
    
    // Draw methods
    void AddDrawTimes(Player* player, int32_t nCount);
    void loadDrawRank();
    void updateDrawRank(Player* player, int32_t nValue);
    void updateDrawRank(Player* player);
    void checkDrawRankInvalid(int8_t connid);
    void checkDrawRank();
    void sendDrawRankMail();
    bool canGetDrawGift(Player* player);
    int32_t GetDrawGift(Player* player);
    int32_t GetScoreCanDrawTime(Player* player);
    int32_t CanUseRechargeDraw(Player* player);
    int32_t CanUseXiaoFeiDraw(Player* player);
    void OnRandScoreDrawItem(Player* player);
    
    // Recharge methods
    void AddRechargeRecord(Player* player, int32_t nValue);
    void loadRechargeSumRank();
    void updateRechargeSumRank(Player* player, int32_t nValue);
    void updateRechargeSumRank(Player* player);
    void checkRechargeSumRankInvalid(int8_t connid);
    void checkRechargeSumRank();
    void sendRechargeSumRankMail();
    int32_t GetDailyRechargeGift(Player* player);
    int32_t GetRechargeSumGift(Player* player);
    
    // XiaoFei methods
    void AddXiaoFeiRecord(Player* player, int32_t nCount);
    void loadXiaoFeiRank();
    void updateXiaoFeiRank(Player* player, int32_t nValue);
    void updateXiaoFeiRank(Player* player);
    void checkXiaoFeiRankInvalid(int8_t connid);
    void checkXiaoFeiRank();
    void sendXiaoFeiRankMail();
    int32_t GetXiaoFeiSumGift(Player* player);
    int32_t GetXiaoFeiSumGiftCount(Player* player);
    void UpdateXiaoFeiRank(Player* player);
    
    // XiaoFei Sum methods
    void loadXiaoFeiSumRank();
    void updateXiaoFeiSumRank(Player* player, int32_t nValue);
    void updateXiaoFeiSumRank(Player* player);
    void checkXiaoFeiSumRankInvalid(int8_t connid);
    void checkXiaoFeiSumRank();
    void sendXiaoFeiSumRankMail();
    
    // Cross rank methods
    void loadCrossRechargeSumRank();
    void updateCrossRechargeSumRank(Player* player, int32_t nValue);
    void updateCrossRechargeSumRank(Player* player);
    void checkCrossRechargeSumRankInvalid(int8_t connid);
    void checkCrossRechargeSumRank();
    
    void loadCrossXiaoFeiSumRank();
    void updateCrossXiaoFeiSumRank(Player* player, int32_t nValue);
    void updateCrossXiaoFeiSumRank(Player* player);
    void checkCrossXiaoFeiSumRankInvalid(int8_t connid);
    void checkCrossXiaoFeiSumRank();
    
    void loadCrossChouJiangRank();
    void updateCrossChouJiangRank(Player* player, int32_t nValue);
    void updateCrossChouJiangRank(Player* player);
    void checkCrossChouJiangRankInvalid(int8_t connid);
    void checkCrossChouJiangRank();
    
    // Boss Score methods
    void loadBossScoreRank();
    void updateBossScoreRank(Player* player, int32_t nValue);
    void updateBossScoreRank(Player* player);
    void checkBossScoreRankInvalid(int8_t connid);
    void checkBossScoreRank();
    void sendBossScoreRankMail();
    void CalBossScoreAddValue(Player* player, int32_t nDamage, int32_t& nAddValue);
    int32_t GetChouJiangSpecialTime();
    int32_t GetChouJiangType(Player* player);
    
    // World Boss methods
    void checkWorldBoss();
    void BossDie(Monster* pMonster, Player* pKiller);
    void BroadcastWorldBossKilled(Player* pKiller, const std::string& strMonsterName);
    void broadcastWorldBossStart();
    void broadcastWorldBossEnd();
    void UpdateMonsterScore(Monster* pMonster, Player* pPlayer);
    
    // Various activity methods
    void AddOnlineRecord(Player* player);
    void AddHuoYueDu(Player* player, int32_t nValue);
    void AddPetIllusionItemRecord(Player* player, int32_t nValue);
    void AddFriendQingYi(Player* player, int32_t nValue);
    void AddMoYuShiJieDrop(Player* player, int32_t nCount);
    void AddEquipUpStarBack(Player* player, int32_t nCount);
    void AddFaBaoValue(Player* player, int32_t nValue);
    
    int32_t GetOnlineGift(Player* player);
    int32_t GetOnlineTimeRewardTime(Player* player);
    bool canGetOnlineGift(Player* player);
    
    int32_t GetLandGift(Player* player);
    bool canGetLandGift(Player* player);
    int32_t GetLandSumGift(Player* player);
    bool canGetLandSumGift(Player* player);
    int32_t getLandSum(Player* player);

    int32_t GetHuoYueDuSumGift(Player* player);
    
    int32_t GetWishGift(Player* player);
    bool canGetWishGift(Player* player);
    
    void GetEquipQingYiGift(Player* player);
    int32_t GetFriendQingYiGift(Player* player);
    int32_t GetPetIllusionItemGift(Player* player);
    int32_t GetEquipUpStarBackItem(Player* player);
    int32_t GetFaBaoCritBackItem(Player* player);
    
    int32_t GetRechargeBack(Player* player);
    bool canGetRechargeBack(Player* player);
    void calRechargeBack(Player* player);
    void calRechargeBackHelper(Player* player, int32_t nIndex);
    
    int32_t GetLianRechargeReward(Player* player);
    
    int32_t BuyDailyLimitShopItem(Player* player, int32_t nIndex);
    int32_t BuyGiftItem(Player* player, int32_t nIndex);
    int32_t BuyGiftShopItem(Player* player, int32_t nIndex);
    int32_t BuyGiftShopItem2(Player* player, int32_t nIndex);
    int32_t BuyTitle(Player* player, int32_t nIndex);
    
    void GongGao(int32_t nGongGaoId, Player* player);
    void GouWuChe(Player* player);
    void SendDaTiReward(Player* player);
    
    void UpdateRank(Player* player, int32_t nValue);
    void broadcastPlayerAction(int32_t nAction, int32_t nParam);
    void checkRefreshMysteryShop();
    void broadcastRefreshMysteryShop();
    void RefreshMysteryShopItem();
    void BroadCastMoYuShiJieIconState();
    int32_t getMoYuShiJieIconState();
    bool CheckDropGroup(int32_t nDropGroup);
    
private:
    void initCfgData();
    void initOpenList(const std::string& str);
    
    CFestivalDoubleEleven(const CFestivalDoubleEleven&);
    CFestivalDoubleEleven& operator=(const CFestivalDoubleEleven&);
    
    // Rank maps
    typedef std::map<int64_t, int32_t> RankMap;
    typedef std::map<int64_t, int32_t> ScoreMap;
    
    // Member variables
    int32_t m_nVersion;
    int32_t m_nHotSign;
    int32_t m_nStartDay;
    int32_t m_nEndDay;
    int32_t m_nIcon;
    int32_t m_nIconHideDay;
    int32_t m_nGameStartDay;
    int32_t m_nUniteStartDay;
    int32_t m_nDropGroup;
    int32_t m_nDay;
    int32_t m_nMinute;
    
    int8_t m_vOpen[47];
    int32_t m_vStartDay[47];
    int32_t m_vEndDay[47];
    
    // Draw
    int32_t m_nDrawLoopTimes;
    int32_t m_nDrawRankSize;
    int32_t m_nDrawRankLimit;
    std::vector<int> m_vDrawRankMail;
    std::vector<std::vector<MemChrBag>> m_vDrawRankReward;
    MemChrBagVector m_vDrawLoopReward;
    RankMap m_mDrawRank;
    
    // XiaoFei Rank
    int32_t m_nXiaoFeiRankSize;
    std::vector<int> m_vXiaoFeiRankLimit;
    std::vector<int> m_vXiaoFeiRankMail;
    std::vector<std::vector<MemChrBag>> m_vXiaoFeiRankReward;
    RankMap m_mXiaoFeiRank;
    
    // XiaoFei Sum
    int32_t m_nXiaoFeiSumRankSize;
    int32_t m_nXiaoFeiSumRankLimit;
    std::vector<int> m_vXiaoFeiSumRankMail;
    std::vector<std::vector<MemChrBag>> m_vXiaoFeiSumRankReward;
    RankMap m_mXiaoFeiSumRank;
    std::vector<int> m_vXiaoFeiSumLimit;
    std::vector<std::vector<MemChrBag>> m_vXiaoFeiSumReward;
    std::vector<int> m_vXiaoFeiSumBroadcast;
    
    // Recharge Sum Rank
    int32_t m_nRechargeSumRankSize;
    std::vector<int> m_vRechargeSumRankMail;
    std::vector<std::vector<MemChrBag>> m_vRechargeSumRankReward;
    RankMap m_mRechargeSumRank;
    std::vector<int> m_vRechargeSumLimit;
    std::vector<std::vector<MemChrBag>> m_vRechargeSumReward;
    std::vector<int> m_vRechargeSumBroadcast;
    
    // Cross ranks
    int32_t m_nCrossRechargeSumRankSize;
    int32_t m_nCrossXiaoFeiSumRankSize;
    int32_t m_nCrossChouJiangRankSize;
    std::vector<int> m_vCrossRechargeSumRankLimit;
    std::vector<int> m_vCrossXiaoFeiSumRankLimit;
    std::vector<int> m_vCrossChouJiangRankLimit;
    RankMap m_mCrossRechargeSumRank;
    RankMap m_mCrossXiaoFeiSumRank;
    RankMap m_mCrossChouJiangRank;
    
    // Boss Score
    int32_t m_nBossScoreRate;
    int32_t m_nBossScoreRankSize;
    int32_t m_BossScoreRewardSize;
    std::vector<int> m_vBossScoreiLimit;
    std::vector<int> m_vBossScoreRankMail;
    std::vector<std::vector<MemChrBag>> m_vBossScoreRankReward;
    std::vector<std::vector<MemChrBag>> m_vBossScoreReward;
    std::vector<std::vector<MemChrBag>> m_vBossScoreDrawReward;
    std::vector<int> m_vGetBossScoreMail;
    std::vector<int> m_vScoreLimit;
    RankMap m_mBossScoreRank;
    int32_t m_nScoreSize;
    int32_t m_nRewardSize;
    int32_t m_nSize;
    
    // World Boss
    int32_t m_MapId;
    int32_t m_X;
    int32_t m_Y;
    int32_t m_Mid;
    int32_t m_nWorldBossIcon;
    int32_t m_nWorldBossStartBroadcast;
    int32_t m_nWorldBossEndBroadcast;
    int32_t m_nWorldBossKillBroadcast;
    int32_t m_MonsterId;
    bool m_bDie;
    std::vector<TimeArea> m_vWorldBossMinute;
    
    // Land
    std::vector<std::vector<MemChrBag>> m_vLandGift;
    std::vector<std::vector<MemChrBag>> m_vLandSumGift;
    
    // Daily Recharge
    int32_t m_nDailyRechargeSize;
    int32_t m_nDailyRechargeDrawSize;
    int32_t m_nDailyRechargeDrawLimit;
    int32_t m_nRechargeDrawSize;
    int32_t m_nRechargeDrawValue;
    int32_t m_nXiaoFeiDrawSize;
    int32_t m_nXiaoFeiDrawValue;
    std::vector<int> m_vDailyRechargeLimit;
    std::vector<std::vector<MemChrBag>> m_vDailyRechargeReward;
    std::vector<int> m_vDailyRechargeBroad;
    
    // Online
    int32_t m_nOnlineStartMinute;
    int32_t m_nOnlineEndMinute;
    int32_t m_nOnlineTimeArea;
    int32_t m_nMaxCount;
    MemChrBagVector m_vOnlineReward;
    
    // Wish
    int32_t m_nWishRecharge;
    MemChrBagVector m_vWishReward;
    
    // Equip QingYi
    int32_t m_nEquipQingYiSize;
    std::vector<int> m_vEquipQingYiLimit;
    std::vector<std::vector<MemChrBag>> m_vEquipQingYiReward;
    
    // Friend QingYi
    int32_t m_nFriendQingYiSize;
    std::vector<int> m_vFriendQingYiLimit;
    std::vector<std::vector<MemChrBag>> m_vFriendQingYiReward;
    
    // Pet Illusion
    int32_t m_nPetIllusionItemSize;
    std::vector<int> m_vPetIllusionItemLimit;
    std::vector<std::vector<MemChrBag>> m_vPetIllusionItemReward;
    
    // Recharge Back
    int32_t m_nRechargeBackSize;
    std::vector<int> m_vRechargeBackLimit;
    std::vector<int> m_vRechargeBackValue;
    
    // Equip UpStar Back
    int32_t m_nEquipUpStarBackId;
    int32_t m_nNeedValue;
    int32_t m_nFaBaoType;
    
    // Buy Gift
    int32_t m_nBuyGiftSize;
    std::vector<int> m_vBuyGiftPrice;
    std::vector<MemChrBag> m_vBuyGiftItem;
    std::vector<int> m_vBuyGiftBroadcast;
    
    // Gift Shop
    int32_t m_nGiftShopSize;
    std::vector<ShopGoods> m_vGiftShopGoods;
    
    // GouWuChe
    int32_t m_nGouWuCheSize;
    std::vector<MemChrBag> m_vGouWuCheItem;
    std::vector<int> m_vGouWuCheGiftPrice;
    
    // Daily Limit Shop
    int32_t m_nDailyLimitShopCostType;
    int32_t m_nDailyLimitShopCostValue;
    int32_t m_nDailyLimitShopLimit;
    MemChrBagVector m_vDailyLimitShopItem;
    
    // Daily Limit Shop 2
    int32_t m_nDailyLimitShop2Size;
    std::vector<ShopGoods> m_vDailyLimitShop2Goods;
    std::vector<int> m_vDailyLimitShop2Broadcast;
    
    // LianRecharge
    std::vector<LianRechargeCfg> m_LianRechargeCfgVt;
    
    // MoYuShiJie
    int32_t m_nMoYuShiJieDropSize;
    std::vector<int> m_vMoYuShiJieDrop;
    int32_t m_nChouJiangCount;
    int32_t m_nChouJiangType;
    
    // Mystery Shop
    int32_t m_nMysteryShopRefreshBroad;
    std::string m_sMysteryShopRefreshCost;
    
    // DaTi
    int32_t m_nDaTiRankSize;
    std::vector<int> m_vDaTiRankMail;
    std::vector<std::vector<MemChrBag>> m_vDaTiRankReward;
    
    // Other
    int32_t m_nHuoYueDuSumSize;
    std::vector<int> m_vHuoYueDuSumLimit;
    std::vector<std::vector<MemChrBag>> m_vHuoYueDuSumReward;
    
    int32_t m_nRechargeSumSize;
    int32_t m_nXiaoFeiSumSize;
    int32_t m_nDailyRechargeSize;
    
    int32_t m_Price;
    int32_t m_Items;
    int32_t m_GetReardSize;
    int32_t m_BackItem;
    Answer::Mutex m_lock;
};

#define FESTIVAL_DOUBLE_ELEVEN CFestivalDoubleEleven::instance()

#endif // __TPOC_FESTIVAL_DOUBLE_ELEVEN_H__
'''

with open(header_path, 'w') as f:
    f.write(header)

print(f"Header written to {header_path}")
print(f"Member variables: {len(member_vars)}")
print(f"Methods: {len(methods)}")

# ============ 4. Generate CPP stubs ============
# Extract simple method bodies that can be directly translated
# Focus on methods with clear logic

cpp = '''#include "stdafx.h"
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
#include "MailManager.h"

CFestivalDoubleEleven::CFestivalDoubleEleven()
{
    memset(this, 0, sizeof(*this));
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
    m_nMinute = TIMER.GetHour() * 60 + TIMER.GetMinute();
}

void CFestivalDoubleEleven::initCfgData()
{
    Answer::Inifile ini;
    ini.parse("./ServerConfig/Tables/FestivalDoubleEleven.cfg");
    
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
    
    // TODO: Load all sub-activity config sections
    // LAND, DAILY_RECHARGE, LUCKY_DRAW, LUCKY_DRAW_RANK, EXCHANGE, WORLD_BOSS,
    // HUO_YUE_DU_SUM, DAILY_LIMIT_SHOP, LAND_SUM, DAILY_ONLINE, BEST_WISH,
    // XIAO_FEI_RANK, XIAO_FEI_SUM, RECHARGE_SUM, RECHARGE_SUM_RANK, etc.
}

void CFestivalDoubleEleven::initOpenList(const std::string& str)
{
    bzero(m_vOpen, sizeof(m_vOpen));
    StringVector vOpen;
    Answer::StringUtility::split(vOpen, str, "|");
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
    if (isOpen(FAT_BOSS_SCORE_RANK) && m_nDay == m_vEndDay[43])
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
    // Check if current time is within the overall activity period
    // TODO: implement from decompiled code
    return true;
}

bool CFestivalDoubleEleven::IsInTime(FESTIVAL_ACTIVITY_TYPE nType)
{
    // Check if specific activity type is within its time window
    // TODO: implement from decompiled code
    return isOpen(nType);
}

bool CFestivalDoubleEleven::isOpen(FESTIVAL_ACTIVITY_TYPE nType)
{
    if (nType <= 0 || nType > 46)
        return false;
    return m_vOpen[nType] != 0;
}

bool CFestivalDoubleEleven::IsOpen()
{
    // TODO: implement from decompiled code
    return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CFestivalDoubleEleven::needShowIcon()
{
    // TODO: implement from decompiled code
    return IsOpen();
}

int32_t CFestivalDoubleEleven::getLeftTime()
{
    // TODO: implement from decompiled code
    return 0;
}

void CFestivalDoubleEleven::SendActivityInfo(Player* player)
{
    // TODO: implement from decompiled code
}

// ==================== Icon ====================

void CFestivalDoubleEleven::getIconState(int32_t& nIconId)
{
    // TODO: implement from decompiled code
}

int32_t CFestivalDoubleEleven::GetIconState()
{
    // TODO: implement from decompiled code
    return m_nIcon;
}

void CFestivalDoubleEleven::SendIconState(Player* player)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::SendWorldBossIconState()
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::GetWorldBossIconState(int32_t& nIconId)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::GetMoYuShiJieIconState(int32_t& nIconId)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::hideIcon(int32_t nIconId)
{
    // TODO: implement from decompiled code
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
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::saveVersion(int32_t line)
{
    // TODO: Save version to DB
}

int32_t CFestivalDoubleEleven::loadVersion(int32_t line)
{
    // TODO: Load version from DB
    return 0;
}

// ==================== Draw ====================

void CFestivalDoubleEleven::AddDrawTimes(Player* player, int32_t nCount)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::loadDrawRank()
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::updateDrawRank(Player* player, int32_t nValue)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::updateDrawRank(Player* player)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::checkDrawRankInvalid(int8_t connid)
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::checkDrawRank()
{
    // TODO: implement from decompiled code
}

void CFestivalDoubleEleven::sendDrawRankMail()
{
    // TODO: implement from decompiled code
}

// ... remaining stub methods ...
'''

with open(cpp_path, 'w') as f:
    f.write(cpp)

print(f"CPP skeleton written to {cpp_path}")
print("Done!")
