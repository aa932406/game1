#include "stdafx.h"
#include "CMingGeTable.h"
#include "stdafx.h"
#include "CMingGeTable.h"
#include "GameService.h"

using namespace Answer;

void CMingGeTable::AddMingGeCfg(CMingGeCfg* p_stu)
{
    if (p_stu)
        m_CMingGeCfgMap[p_stu->nId] = *p_stu;
}

void CMingGeTable::AddMingGeDrawCost(MingGeDrawCost stu)
{
    m_MingGeDrawCostMap[stu.nType] = stu;
}

void CMingGeTable::AddMingGeDrawRate(int32_t nType, MingGeParam2 ItemRate)
{
    m_MingGeDrawRateMap[nType].nItemRate.push_back(ItemRate);
    m_MingGeDrawRateMap[nType].nMaxRate += ItemRate.nParam2;
}

int32_t CMingGeTable::RandMingGe(int32_t nType) const
{
    MingGeDrawRateMap::const_iterator it = m_MingGeDrawRateMap.find(nType);
    if (it == m_MingGeDrawRateMap.end())
        return 0;

    int32_t nMaxRate = it->second.nMaxRate;
    if (nMaxRate <= 0)
        return 0;

    int32_t nRand = RANDOM.generate(1, nMaxRate);

    for (std::list<MingGeParam2>::const_iterator itRate = it->second.nItemRate.begin();
         itRate != it->second.nItemRate.end(); ++itRate)
    {
        if (nRand <= itRate->nParam2)
            return itRate->nParam1;
        nRand -= itRate->nParam2;
    }
    return 0;
}

const CMingGeCfg* CMingGeTable::GetCMingGeCfg(int32_t nId) const
{
    CMingGeCfgMap::const_iterator it = m_CMingGeCfgMap.find(nId);
    if (it != m_CMingGeCfgMap.end())
        return &it->second;
    return NULL;
}

const MingGeDrawCost* CMingGeTable::GetMingGeDrawCost(int32_t nType) const
{
    MingGeDrawCostMap::const_iterator it = m_MingGeDrawCostMap.find(nType);
    if (it != m_MingGeDrawCostMap.end())
        return &it->second;
    return NULL;
}
