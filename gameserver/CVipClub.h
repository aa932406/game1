#ifndef __TPOC_VIP_CLUB_H__
#define __TPOC_VIP_CLUB_H__

#include "share/Shared.h"
#include <map>
#include <vector>
#include <list>
#include <string>

// Club member data
struct ClubData
{
    ClubData() : nCid(0), nVipLevel(0), nVip7Time(0), nVip10Time(0) {}
    CharId_t    nCid;
    std::string strName;
    int32_t     nVipLevel;
    int32_t     nVip7Time;
    int32_t     nVip10Time;
};

// VIP club level config (parsed from ClubAim.txt)
struct ClbAimCfg
{
    ClbAimCfg() : nId(0), nNeedVipLevel(0), nNeedCount(0), nAddDropTimes(0) {}
    int32_t nId;
    int32_t nNeedVipLevel;
    int32_t nNeedCount;
    int32_t nAddDropTimes;
};
typedef std::list<ClbAimCfg> ClbAimCfgList;

// Comparator for club wall sorting (by VIP7 time ascending)
bool GreaterClubData(const ClubData& left, const ClubData& right);

class CVipClub
{
public:
    CVipClub();
    ~CVipClub();

    void    Init( int32_t line );
    void    UpdateClubData( CharId_t nCid, const std::string& strName, int32_t nVipLevel, int32_t nTime );
    void    AppendClubWallInfo( Answer::NetPacket* packet );

private:
    int32_t CalculationClubLevel();
    void    CalculationClubWallInfo();

private:
    std::map<CharId_t, ClubData>    m_ClubDataMap;
    int32_t                         m_ClubLevel;
    std::map<int32_t, int32_t>      m_LevelCountMap;
    std::vector<ClubData>           m_Vip7ClubDataVt;
    ClubData                        m_Vip10ClubData;
};

#define VIP_CLUB Answer::Singleton<CVipClub>::instance()

#endif //__TPOC_VIP_CLUB_H__
