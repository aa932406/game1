#ifndef __C_KIA_FU_RECHARGE_H__
#define __C_KIA_FU_RECHARGE_H__

#include "Shared.h"
#include "../share/DataStruct.h"
#include "CfgData.h"
#include <vector>

// 开服充值活动类型
enum KAI_FU_RECHARGE_TYPE
{
    KFRT_NONE           = 0,
    KFRT_RECHARGE_SUM   = 1,   // 累计充值
    KFRT_LIAN_RECHARGE  = 2,   // 连充
    KFRT_CHOU_JIANG     = 3,   // 抽奖
    KFRT_XIAO_FEI_SUM  = 4,   // 累计消费
};

// 连充配置
struct LianRechargeCfg
{
    int32_t                         nValues;
    std::vector<MemChrBagVector>    vGiftVector;
};

class Player;

class CKiaFuRecharge
{
public:
    CKiaFuRecharge();
    ~CKiaFuRecharge();

    void    Init();

    // 驱动事件
    void    OnDaySwitch();
    void    OnRecharge(Player* player, int32_t OldValue, int32_t AddValue);
    void    OnXiaoFeiSum(Player* player, int32_t AddTimes);
    void    OnAddChouJiangTimes(Player* player, int32_t AddTimes);

    // 奖励领取
    void    OnGetRechargeSumReward(Player* player, int32_t nIndex);
    void    OnGetXiaoFeiReward(Player* player, int32_t nIndex);
    void    OnGetChouJiangReward(Player* player, int32_t nIndex);
    void    GetLianRechargeReward(Player* player, int32_t nType, int32_t nIndex);

    // 查询
    int32_t HaveRechargeRewardCount(Player* player);
    int32_t HaveChouJiangCount(Player* player);
    int32_t GetChouJiangLeftTime();

    // 图标状态
    void    GetIconState(Player* player, IconStateList& IconList);
    void    SendIconState(Player* player);
    void    GetChouJiangIconState(Player* player, IconStateList& IconList);
    void    SendChouJiangIconState(Player* player);
    void    hideIcon(int32_t nIconId);

    // 公告
    void    GongGao(int32_t GongGaoId, Player* player);

private:
    void    initCfgData();
    bool    IsInTime() const;
    bool    IsInTime(KAI_FU_RECHARGE_TYPE nType) const;
    bool    needShowIcon() const;
    bool    needShowShouJinagIcon() const;
    int32_t getLeftTime();
    void    getIconState(ShowIcon& icon, Player* player);
    void    getChouJiangIconState(ShowIcon& icon, Player* player);

    // 配置数据
    int32_t m_nDay;
    int32_t m_nMinute;
    int32_t m_nEndDay;
    int32_t m_nIcon;
    int32_t m_nSize;
    int32_t m_nXiaoFeiSize;

    // 各活动时间段
    int32_t m_vStartDay[5];
    int32_t m_vEndDay[5];

    // 累计充值
    std::vector<int32_t>            m_vSumGolds;
    std::vector<MemChrBagVector>    m_vSumGift;

    // 连充
    std::vector<LianRechargeCfg>    m_LianRechargeCfgVt;

    // 抽奖
    int32_t m_ChouJiangIcon;

    // 累计消费
    std::vector<int32_t>            m_nValues;
    std::vector<MemChrBagVector>    m_vXiaoFeiSumGift;
    std::vector<int32_t>            m_vXiaoFeiGongGaoId;
};

#define KIA_FU_RECHARGE Answer::Singleton<CKiaFuRecharge>::instance()

#endif // __C_KIA_FU_RECHARGE_H__
