#ifndef __ZONG_HE_YUN_YING_HD_H__
#define __ZONG_HE_YUN_YING_HD_H__

#include "DataStructs.h"
#include <vector>
#include <map>
#include <string>

class Player;
class ShowIcon;

// ====== FestivalRank (from decompiled CZongHeYunYingHD) ======
struct FestivalRank
{
    int64_t nCharId;
    std::string strName;
    int32_t nScore;
    int32_t nTime;
    int16_t nIndex;

    FestivalRank()
        : nCharId(0), nScore(0), nTime(0), nIndex(-1) {}
};

typedef std::vector<FestivalRank> FestivalRankVector;

// ====== ZongHeYunYingHD Type ======
enum ZONG_HE_YUN_YING_HD_TYPE
{
    ZHYYHDT_RECHARGE_DAILY           = 1,
    ZHYYHDT_RECHARGE_RANK_DAILY      = 2,
    ZHYYHDT_RECHARGE_TEAM_SHOP_DAILY = 3,
    ZHYYHDT_ONCE_SHOP                = 4,
    ZHYYHDT_MAX                      = 5,
};

class CZongHeYunYingHD
{
public:
    CZongHeYunYingHD();
    ~CZongHeYunYingHD();

    void Init(int32_t line);
    void OnDaySwitch();
    void OnNewMinute(int32_t nMinute);
    void OnRecharge(Player* player, int32_t nValue);

    // Icon
    void GetIconState(Player* player, IconStateList& IconList);
    void SendIconState(Player* player);
    void SendActivityInfo(Player* player);
    void hideIcon(int32_t nIconId);

    // Activity info for client protocol
    int32_t GetRechargeDailyReward(Player* player);
    int32_t GetRechargeTeamShopDailyReward(Player* player, int32_t nIndex);
    int32_t BuyOnceShopItem(Player* player, int32_t nIndex);

    // Rank sync
    void UpdatePlayerInfo(int8_t connid, Answer::NetPacket* inPacket);
    void UpdateRankInfo(int8_t connid, int8_t nType, int32_t nDay, const FestivalRankVector& vUpdateRank);

    // Time checks
    bool IsInTime();
    bool IsInTime(ZONG_HE_YUN_YING_HD_TYPE nType);
    bool IsOpen(ZONG_HE_YUN_YING_HD_TYPE nType);
    int32_t getLeftTime();
    bool needShowIcon();

    // Config
    void initCfgData();
    void initOpenList(const std::string& str);
    void loadRankData();

private:
    void sendRechargeDailyRankReward();
    void sendLineSocialPlayerInfo(int8_t connid, int8_t nType, const FestivalRank& info);
    void updateRankInfo(int8_t connid, int8_t nType, const FestivalRank& info);
    void checkRankInvalid(int8_t connid, int8_t nType);
    int32_t getRechargePlayer(int8_t connid);

    // Helper to get icon state
    void getIconState(ShowIcon& icon, Player* player);
    bool isOpen(ZONG_HE_YUN_YING_HD_TYPE nType) const;

public:
    // Member variables
    int32_t         m_nDay;
    int32_t         m_nStartDay;
    int32_t         m_nEndDay;
    int32_t         m_nIcon;
    int32_t         m_nMinute;

    // Sub-activity config: indexed by ZONG_HE_YUN_YING_HD_TYPE
    int8_t          m_vOpen[ZHYYHDT_MAX];
    int32_t         m_vStartDay[ZHYYHDT_MAX];
    int32_t         m_vEndDay[ZHYYHDT_MAX];

    // === DAILY_RECHARGE (type 1) ===
    int32_t         m_nRechargeDailyValue;
    int32_t         m_nRechargeDailyRewardLimit;
    MemChrBagVector m_vRechargeDailyReward;

    // === RECHARGE_RANK_DAILY (type 2) ===
    int32_t         m_nRechargeRankDailyArea;
    int32_t         m_nRechargeRankDailySize;
    std::vector< std::pair<int32_t, int32_t> > m_vRechargeRankDailyIndex;
    std::vector<MemChrBagVector> m_vRechargeRankDailyReward;
    std::vector<int32_t>         m_vRechargeRankDailyMail;
    std::map<int8_t, FestivalRankVector> m_mRechargeDailyRank;

    // === RECHARGE_TEAM_SHOP_DAILY (type 3) ===
    int32_t         m_nRechargeTeamShopDailySize;
    std::vector<int32_t>         m_vRechargeTeamShopDailyPlayer;
    std::vector<int32_t>         m_vRechargeTeamShopDailyValue;
    std::vector<MemChrBagVector> m_vRechargeTeamShopDailyReward;
    std::map<int8_t, std::map<int64_t, int32_t> > m_mRechargeDailyPlayer;

    // === ONCE_SHOP (type 4) ===
    int32_t         m_nOnceShopSize;
    std::vector<int32_t>         m_vOnceShopPrice;
    std::vector<MemChrBagVector> m_vOnceShopItem;

    Answer::Mutex   m_lock;
};

#endif // __ZONG_HE_YUN_YING_HD_H__
