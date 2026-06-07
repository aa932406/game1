#ifndef __KUN_LING_TABLE_H__
#define __KUN_LING_TABLE_H__

#include "Shared.h"
#include "../share/DataStruct.h"

// ========== Config Data Structures ==========

// 鲲升级配置
struct KunLevelUpCfg
{
    KunLevelUpCfg() : nLevel(0), nExp(0), nCostMoney(0), nCostShengYaoBi(0),
                      nGongGaoId(0), nTalentId(0), nTalentLevel(0) {}

    int32_t nLevel;
    int32_t nExp;
    int32_t nCostMoney;
    int32_t nCostShengYaoBi;
    int32_t nGongGaoId;
    int32_t nTalentId;
    int32_t nTalentLevel;
    AddAttrList lAttrList;
};

// 灵珠配置
struct LingZhuCfg
{
    LingZhuCfg() : nId(0), nType(0), nDecExp(0), nGetGongGao(0), nLevelUpGongGao(0),
                   nKunLingLevel(0), nCostMoney(0), nCostId(0), nCostCount(0),
                   nNextId(0), nLevel(0), nSuitId(0) {}

    int32_t nId;
    int32_t nType;
    int32_t nDecExp;
    int32_t nGetGongGao;
    int32_t nLevelUpGongGao;
    int32_t nKunLingLevel;
    int32_t nCostMoney;
    int32_t nCostId;
    int32_t nCostCount;
    int32_t nNextId;
    int32_t nLevel;
    int32_t nSuitId;
    AddAttrList lAttrList;
};

// 丹田配置
struct DanTianCfg
{
    DanTianCfg() : nMid(0), nRate(0), nTime(0), nId(0) {}

    int32_t nMid;
    int32_t nRate;
    int32_t nTime;
    int32_t nId;

    static int32_t RandDanTianId(const DanTianCfg* pCfg);
    static int32_t RandHighDanTianId(const DanTianCfg* pCfg);
};

// 灵珠套装属性
struct LingZhuSuit
{
    LingZhuSuit() : nSuitId(0) {}

    int32_t nSuitId;
    AddAttrList lAttrList;
};

// 灵珠位置初始配置
struct LingZhuPosCfg
{
    LingZhuPosCfg() : nPos(0), nFirstId(0), nCostId(0), nCostCount(0), nMoney(0) {}

    int32_t nPos;
    int32_t nFirstId;
    int32_t nCostId;
    int32_t nCostCount;
    int32_t nMoney;
};

// 灵珠全满技能配置
struct LingZhuSkill
{
    LingZhuSkill() : nLevel(0), TalentId(0), TalentLevel(0) {}

    int32_t nLevel;
    int32_t TalentId;
    int32_t TalentLevel;
};

// ========== KunLingTable ==========

class KunLingTable
{
public:
    KunLingTable() {}
    ~KunLingTable() {}

    void AddKunLevelUpCfg(const KunLevelUpCfg* pCfg)
    {
        KunLevelUpCfg cfg = *pCfg;
        m_mKunLevelUpCfg[pCfg->nLevel] = cfg;
    }

    const KunLevelUpCfg* GetKunLevelUpCfg(int32_t nLevel) const
    {
        std::map<int32_t, KunLevelUpCfg>::const_iterator it = m_mKunLevelUpCfg.find(nLevel);
        if (it != m_mKunLevelUpCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuCfg(const LingZhuCfg* pCfg)
    {
        LingZhuCfg cfg = *pCfg;
        m_mLingZhuCfg[pCfg->nId] = cfg;
    }

    const LingZhuCfg* GetLingZhuCfg(int32_t nId) const
    {
        std::map<int32_t, LingZhuCfg>::const_iterator it = m_mLingZhuCfg.find(nId);
        if (it != m_mLingZhuCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddDanTianCfg(const DanTianCfg* pCfg)
    {
        DanTianCfg cfg = *pCfg;
        m_mDanTianCfg[pCfg->nMid] = cfg;
    }

    const DanTianCfg* GetDanTianCfg(int32_t nMid) const
    {
        std::map<int32_t, DanTianCfg>::const_iterator it = m_mDanTianCfg.find(nMid);
        if (it != m_mDanTianCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuSuit(const LingZhuSuit* pCfg)
    {
        LingZhuSuit cfg = *pCfg;
        m_mLingZhuSuit[pCfg->nSuitId] = cfg;
    }

    const LingZhuSuit* GetLingZhuSuit(int32_t nSuitId) const
    {
        std::map<int32_t, LingZhuSuit>::const_iterator it = m_mLingZhuSuit.find(nSuitId);
        if (it != m_mLingZhuSuit.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuPosId(const LingZhuPosCfg* pCfg)
    {
        LingZhuPosCfg cfg = *pCfg;
        m_mLingZhuPosCfg[pCfg->nPos] = cfg;
    }

    const LingZhuPosCfg* GetLingZhuPosId(int32_t nPos) const
    {
        std::map<int32_t, LingZhuPosCfg>::const_iterator it = m_mLingZhuPosCfg.find(nPos);
        if (it != m_mLingZhuPosCfg.end())
        {
            return &it->second;
        }
        return NULL;
    }

    void AddLingZhuSkill(const LingZhuSkill* pCfg)
    {
        LingZhuSkill cfg = *pCfg;
        m_mLingZhuSkill[pCfg->nLevel] = cfg;
    }

    const LingZhuSkill* GetLingZhuSkill(int32_t nLevel) const
    {
        std::map<int32_t, LingZhuSkill>::const_iterator it = m_mLingZhuSkill.find(nLevel);
        if (it != m_mLingZhuSkill.end())
        {
            return &it->second;
        }
        return NULL;
    }

private:
    std::map<int32_t, KunLevelUpCfg> m_mKunLevelUpCfg;
    std::map<int32_t, LingZhuCfg>    m_mLingZhuCfg;
    std::map<int32_t, DanTianCfg>    m_mDanTianCfg;
    std::map<int32_t, LingZhuSuit>   m_mLingZhuSuit;
    std::map<int32_t, LingZhuPosCfg> m_mLingZhuPosCfg;
    std::map<int32_t, LingZhuSkill>  m_mLingZhuSkill;
};

#endif // __KUN_LING_TABLE_H__
