#ifndef __TPOC_CMING_GE_TABLE_H__
#define __TPOC_CMING_GE_TABLE_H__

#include <map>
#include <list>

struct MingGeAddAttr
{
    MingGeAddAttr() : m_nAddAttrType(0), m_nAddAttrValue(0) {}
    uint8_t m_nAddAttrType;
    int32_t m_nAddAttrValue;
};

struct CMingGeCfg
{
    CMingGeCfg() : nId(0), nNextId(0), nUpExp(0), nDecExp(0), nDecMoney(0),
        nCostChip(0), nCanPickup(0), nQuality(0), nType(0) {}

    int32_t nId;
    int32_t nNextId;
    int32_t nUpExp;
    int32_t nDecExp;
    int32_t nDecMoney;
    int32_t nCostChip;
    int32_t nCanPickup;
    int32_t nQuality;
    int32_t nType;
    std::list<MingGeAddAttr> lAttrList;
};

struct MingGeDrawCost
{
    MingGeDrawCost() : nType(0), nConstMoney(0), nConstGold(0), nRate(0) {}
    int32_t nType;
    int32_t nConstMoney;
    int32_t nConstGold;
    int32_t nRate;
};

struct MingGeParam2
{
    int32_t nParam1;
    int32_t nParam2;
};

struct MingGeDrawRate
{
    MingGeDrawRate() : nMaxRate(0) {}
    int32_t nMaxRate;
    std::list<MingGeParam2> nItemRate;
};

typedef std::map<int32_t, CMingGeCfg> CMingGeCfgMap;
typedef std::map<int32_t, MingGeDrawCost> MingGeDrawCostMap;
typedef std::map<int32_t, MingGeDrawRate> MingGeDrawRateMap;

class CMingGeTable
{
public:
    CMingGeTable() {}
    ~CMingGeTable() {}

    void AddMingGeCfg(CMingGeCfg* p_stu);
    void AddMingGeDrawCost(MingGeDrawCost stu);
    void AddMingGeDrawRate(int32_t nType, MingGeParam2 ItemRate);
    int32_t RandMingGe(int32_t nType) const;

    const CMingGeCfg* GetCMingGeCfg(int32_t nId) const;
    const MingGeDrawCost* GetMingGeDrawCost(int32_t nType) const;

    const CMingGeCfgMap& GetMingGeCfgMap() const { return m_CMingGeCfgMap; }

private:
    CMingGeCfgMap m_CMingGeCfgMap;
    MingGeDrawCostMap m_MingGeDrawCostMap;
    MingGeDrawRateMap m_MingGeDrawRateMap;
};

#endif
