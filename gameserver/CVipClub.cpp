#include "CVipClub.h"
#include "GameService.h"
#include "CfgData.h"
#include "DBService.h"
#include "share/Shared.h"
#include <algorithm>

using namespace Answer;

bool GreaterClubData(const ClubData& left, const ClubData& right)
{
    return left.nVip7Time < right.nVip7Time;
}

CVipClub::CVipClub()
{
    m_ClubLevel = 0;
}

CVipClub::~CVipClub()
{
}

void CVipClub::Init( int32_t line )
{
    if ( line == 9 )
    {
        return;
    }

    m_ClubDataMap.clear();
    m_LevelCountMap.clear();

    // Load club members from DB
    DBPool* pDBPool = Answer::Singleton<Answer::DBPool>::instance();
    MySqlDBGuard db( pDBPool );
    MySqlQuery* pResult = db.query(
        "select a.cid,a.level,a.club_7_time,a.club_10_time,b.name "
        "from mem_chr_vip as a, mem_character as b "
        "where club > 0 and a.cid = b.cid" );

    if ( pResult != NULL )
    {
        MySqlQuery result( pResult );
        while ( !result.eof() )
        {
            ClubData stu;
            stu.nCid = result.getInt64Value( "cid", 0 );
            stu.nVipLevel = result.getIntValue( "level", 0 );
            stu.nVip7Time = result.getIntValue( "club_7_time", 0 );
            stu.nVip10Time = result.getIntValue( "club_10_time", 0 );
            stu.strName = result.getStringValue( "name", "" );
            m_ClubDataMap[stu.nCid] = stu;
            result.nextRow();
        }
    }

    m_ClubLevel = CalculationClubLevel();
    CalculationClubWallInfo();
}

void CVipClub::UpdateClubData( CharId_t nCid, const std::string& strName, int32_t nVipLevel, int32_t nTime )
{
    std::map<CharId_t, ClubData>::iterator it = m_ClubDataMap.find( nCid );
    if ( it != m_ClubDataMap.end() )
    {
        // Update existing member
        it->second.strName = strName;
        if ( it->second.nVipLevel <= 6 && nVipLevel > 6 )
        {
            it->second.nVip7Time = nTime;
        }
        if ( it->second.nVipLevel <= 9 && nVipLevel > 9 )
        {
            it->second.nVip10Time = nTime;
        }
        it->second.nVipLevel = nVipLevel;
    }
    else
    {
        // Add new member
        ClubData stu;
        stu.nCid = nCid;
        stu.strName = strName;
        if ( nVipLevel > 6 )
        {
            stu.nVip7Time = nTime;
        }
        if ( nVipLevel > 9 )
        {
            stu.nVip10Time = nTime;
        }
        stu.nVipLevel = nVipLevel;
        m_ClubDataMap[nCid] = stu;
    }

    int32_t nOldLevel = m_ClubLevel;
    m_ClubLevel = CalculationClubLevel();
    if ( m_ClubLevel != nOldLevel )
    {
        GAME_SERVICE.AddPlayerVipClubDropTime();
    }

    CalculationClubWallInfo();
}

int32_t CVipClub::CalculationClubLevel()
{
    int32_t nLevel = 0;
    m_LevelCountMap.clear();

    const ClbAimCfgList& cfgList = CFG_DATA.GetClbAimCfgList();
    for ( ClbAimCfgList::const_iterator it = cfgList.begin(); it != cfgList.end(); ++it )
    {
        int32_t nCount = 0;
        int32_t nAddLevel = 0;

        for ( std::map<CharId_t, ClubData>::iterator iter = m_ClubDataMap.begin();
              iter != m_ClubDataMap.end(); ++iter )
        {
            if ( iter->second.nVipLevel >= it->nNeedVipLevel )
            {
                ++nCount;
            }
            if ( nCount >= it->nNeedCount && nAddLevel <= 0 )
            {
                nAddLevel = it->nAddDropTimes;
            }
        }

        m_LevelCountMap[it->nNeedVipLevel] = nCount;
        nLevel += nAddLevel;
    }

    return nLevel + 1;
}

void CVipClub::CalculationClubWallInfo()
{
    int32_t Vip10Time = 0;
    m_Vip7ClubDataVt.clear();	m_Vip10ClubData = ClubData();

    for ( std::map<CharId_t, ClubData>::iterator it = m_ClubDataMap.begin();
          it != m_ClubDataMap.end(); ++it )
    {
        if ( it->second.nVipLevel > 9 )
        {
            if ( Vip10Time == 0 || it->second.nVip10Time < Vip10Time )
            {
                m_Vip10ClubData = it->second;
                Vip10Time = it->second.nVip10Time;
            }
        }
        if ( it->second.nVipLevel > 6 )
        {
            m_Vip7ClubDataVt.push_back( it->second );
        }
    }

    // Remove VIP10 member from VIP7 list if present
    if ( m_Vip10ClubData.nCid > 0 )
    {
        for ( std::vector<ClubData>::iterator iter = m_Vip7ClubDataVt.begin();
              iter != m_Vip7ClubDataVt.end(); ++iter )
        {
            if ( iter->nCid == m_Vip10ClubData.nCid )
            {
                m_Vip7ClubDataVt.erase( iter );
                break;
            }
        }
    }

    // Sort VIP7 list by VIP7 time ascending
    if ( !m_Vip7ClubDataVt.empty() )
    {
        std::sort( m_Vip7ClubDataVt.begin(), m_Vip7ClubDataVt.end(), GreaterClubData );
    }
}

void CVipClub::AppendClubWallInfo( Answer::NetPacket* packet )
{
    if ( NULL == packet )
    {
        return;
    }

    // VIP10 info
    if ( m_Vip10ClubData.nCid > 0 )
    {
        packet->writeInt32( 1 );
        packet->writeInt64( m_Vip10ClubData.nCid );
        packet->writeUTF8( m_Vip10ClubData.strName );
    }
    else
    {
        packet->writeInt32( 0 );
    }

    // VIP7 info (up to 3)
    int32_t nSize = m_Vip7ClubDataVt.size();
    if ( nSize > 3 )
    {
        nSize = 3;
    }
    packet->writeInt32( nSize );

    int32_t nCount = 0;
    for ( std::vector<ClubData>::iterator it = m_Vip7ClubDataVt.begin();
          it != m_Vip7ClubDataVt.end(); ++it )
    {
        if ( nCount > 2 )
        {
            break;
        }
        packet->writeInt64( it->nCid );
        packet->writeUTF8( it->strName );
        ++nCount;
    }

    // Club level and level counts
    packet->writeInt32( m_ClubLevel );

    nSize = m_LevelCountMap.size();
    packet->writeInt32( nSize );
    for ( std::map<int32_t, int32_t>::iterator it = m_LevelCountMap.begin();
          it != m_LevelCountMap.end(); ++it )
    {
        packet->writeInt32( it->first );
        packet->writeInt32( it->second );
    }
}
