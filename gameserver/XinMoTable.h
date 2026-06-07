#ifndef __XIN_MO_TABLE_H__
#define __XIN_MO_TABLE_H__

#include "Shared.h"
#include "../share/DataStruct.h"

// ===== 心魔配置结构 =====

// 心魔等级配置（XinMoLevel.txt）
struct XinMoCfg
{
    XinMoCfg()
        : nLevel(0), nCostMoney(0), nCostShenYaoBi(0), nCostExp(0)
        , nNeedQiQingLevel(0), nGongGaoId(0)
    {}

    int32_t     nLevel;
    int32_t     nCostMoney;
    int32_t     nCostShenYaoBi;
    int32_t     nCostExp;
    int32_t     nNeedQiQingLevel;
    AddAttrList lAttr;
    int32_t     nGongGaoId;
    AddAttrList lAddAttr;
};

// 七情激活配置（XinMoQiQing.txt）
struct QiQingCfg
{
    QiQingCfg()
        : nId(0), nGongGaoId(0)
    {}

    int32_t         nId;
    ItemDataList    lCostItems;
    AddAttrList     lAttr;
    int32_t         nGongGaoId;
    AddAttrList     lAddAttr;
};

// 心魔七情升级配置
struct XinMoQiQingLevelUpCfg
{
    XinMoQiQingLevelUpCfg()
        : nType(0), nLevel(0), nNeedLastTypeLevel(0), nGongGaoId(0)
    {}

    int32_t         nType;
    int32_t         nLevel;
    int32_t         nNeedLastTypeLevel;
    ItemDataList    lCostList;
    AddAttrList     lAttr;
    int32_t         nGongGaoId;
};

// 心情奖励配置（XinQingReward.txt）
struct XinQingReward
{
    XinQingReward()
        : nFlagCount(0), nGongGaoId(0)
    {}

    int32_t         nFlagCount;
    MemChrBagVector Items;
    int32_t         nGongGaoId;
};

// 心情概率配置（XinQing.txt）
struct XinQingRate
{
    XinQingRate()
        : nFlagCount(0), nSpecialMount(0), nRate(0)
    {}

    int32_t nFlagCount;
    int32_t nSpecialMount;
    int32_t nRate;
};

// 装备进化配置（XinMoJingHua.txt）
struct EquipJinHua
{
    EquipJinHua()
        : nEquipId(0)
    {}

    int32_t         nEquipId;
    ItemDataList    CostItems;
    int32_t         nParamRate;
};

// ===== XinMoTable 配置表 =====
class XinMoTable
{
public:
    XinMoTable() {}
    ~XinMoTable() {}

    void AddXinMoCfg(const XinMoCfg& cfg) { m_mXinMoCfg[cfg.nLevel] = cfg; }
    void AddQiQingCfg(const QiQingCfg& cfg) { m_mQiQingCfg[cfg.nId] = cfg; }
    void AddQiQingLevelUpCfg(const XinMoQiQingLevelUpCfg& cfg)
    {
        m_mQiQingLevelUpCfg[std::make_pair(cfg.nType, cfg.nLevel)] = cfg;
    }
    void AddXinQingReward(const XinQingReward& cfg) { m_mXinQingReward[cfg.nFlagCount] = cfg; }
    void AddXinQingRate(const XinQingRate& cfg) { m_lstXinQingRate.push_back(cfg); }
    void AddEquipJinHua(const EquipJinHua& cfg) { m_mEquipJinHua[cfg.nEquipId] = cfg; }

    const XinMoCfg* GetXingMoCfg(int32_t nLevel) const
    {
        std::map<int32_t, XinMoCfg>::const_iterator it = m_mXinMoCfg.find(nLevel);
        if (it != m_mXinMoCfg.end()) return &it->second;
        return NULL;
    }

    const QiQingCfg* GetQiQingCfg(int32_t nId) const
    {
        std::map<int32_t, QiQingCfg>::const_iterator it = m_mQiQingCfg.find(nId);
        if (it != m_mQiQingCfg.end()) return &it->second;
        return NULL;
    }

    const XinMoQiQingLevelUpCfg* GetXinMoQiQingLevelUpCfg(int32_t nType, int32_t nLevel) const
    {
        std::map<std::pair<int32_t, int32_t>, XinMoQiQingLevelUpCfg>::const_iterator it =
            m_mQiQingLevelUpCfg.find(std::make_pair(nType, nLevel));
        if (it != m_mQiQingLevelUpCfg.end()) return &it->second;
        return NULL;
    }

    const XinQingReward* GetXinQingReward(int32_t nFlagCount) const
    {
        std::map<int32_t, XinQingReward>::const_iterator it = m_mXinQingReward.find(nFlagCount);
        if (it != m_mXinQingReward.end()) return &it->second;
        return NULL;
    }

    int32_t GetAppearCount(int32_t nRemainFlagCount) const;

    const EquipJinHua* GetJinHuaCfg(int32_t nEquipId) const
    {
        std::map<int32_t, EquipJinHua>::const_iterator it = m_mEquipJinHua.find(nEquipId);
        if (it != m_mEquipJinHua.end()) return &it->second;
        return NULL;
    }

private:
    std::map<int32_t, XinMoCfg>                     m_mXinMoCfg;
    std::map<int32_t, QiQingCfg>                    m_mQiQingCfg;
    std::map<std::pair<int32_t, int32_t>, XinMoQiQingLevelUpCfg> m_mQiQingLevelUpCfg;
    std::map<int32_t, XinQingReward>                m_mXinQingReward;
    std::list<XinQingRate>                          m_lstXinQingRate;
    std::map<int32_t, EquipJinHua>                  m_mEquipJinHua;
};

#endif // __XIN_MO_TABLE_H__
