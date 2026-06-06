#include "stdafx.h"
#include "CLittleHelperData.h"
#include "../share/Shared.h"
#include <sstream>

using namespace Answer;

CLittleHelperData::CLittleHelperData()
    : m_LittleHelperId( 0 )
{
}

CLittleHelperData::~CLittleHelperData()
{
}

void CLittleHelperData::CleanUp()
{
    m_LittleHelperId = 0;
    m_ActLittleHelperInfoMap.clear();
}

void CLittleHelperData::SaveToSqlString( SqlStringList *sqls, char (*szSQL)[4096], CharId_t nCid )
{
    bzero( szSQL, 0x1000 );
    std::string strReward = getRewardState();
    snprintf(
        (char *)szSQL,
        0xFFF,
        "INSERT INTO `mem_little_helper` (cid,work_id,act_info) VALUES (%lld,%d,'%s') on duplicate key update work_id =%d,act_info='%s'",
        nCid,
        m_LittleHelperId,
        strReward.c_str(),
        m_LittleHelperId,
        strReward.c_str() );
    sqls->push_back( std::string( (const char *)szSQL ) );
}

bool CLittleHelperData::LoadFromDB( Answer::MySqlDBGuard *db, char (*szSQL)[4096], int64_t nUid, int32_t nSid, CharId_t nCid )
{
    // Stub - DB operations not fully implemented in skeleton
    return false;
}

std::string CLittleHelperData::getRewardState()
{
    std::ostringstream oss;
    for ( std::map<int32_t, ActLittleHelperInfo>::iterator it = m_ActLittleHelperInfoMap.begin();
        it != m_ActLittleHelperInfoMap.end(); ++it )
    {
        oss << it->first << ":" << it->second.nSkin << ":" << it->second.nTimes << "|";
    }
    return oss.str();
}

void CLittleHelperData::SaveRewardState( std::string *pStr )
{
    if ( pStr->empty() )
        return;
    
    StringVector vt = Answer::StringUtility::split( *pStr, "|" );
    for ( size_t i = 0; i < vt.size(); ++i )
    {
        StringVector socreVt = Answer::StringUtility::split( vt[i], ":" );
        if ( socreVt.size() == 3 )
        {
            ActLittleHelperInfo stu;
            stu.nId = atoi( socreVt[0].c_str() );
            stu.nSkin = atoi( socreVt[1].c_str() );
            stu.nTimes = atoi( socreVt[2].c_str() );
            m_ActLittleHelperInfoMap[stu.nId] = stu;
        }
    }
}

void CLittleHelperData::PackageData( Answer::NetPacket *packet )
{
    if ( !packet )
        return;
    packet->writeInt32( m_LittleHelperId );
    packet->writeInt32( (int32_t)m_ActLittleHelperInfoMap.size() );
    for ( std::map<int32_t, ActLittleHelperInfo>::iterator it = m_ActLittleHelperInfoMap.begin();
        it != m_ActLittleHelperInfoMap.end(); ++it )
    {
        packet->writeInt32( it->first );
        packet->writeInt32( it->second.nSkin );
        packet->writeInt32( it->second.nTimes );
    }
}

void CLittleHelperData::UnPackageData( Answer::NetPacket *inPacket, CharId_t nCid )
{
    if ( !inPacket )
        return;
    m_LittleHelperId = inPacket->readInt32();
    int32_t nSize = inPacket->readInt32();
    for ( int32_t i = 0; i < nSize; ++i )
    {
        ActLittleHelperInfo stu;
        stu.nId = inPacket->readInt32();
        stu.nSkin = inPacket->readInt32();
        stu.nTimes = inPacket->readInt32();
        m_ActLittleHelperInfoMap[stu.nId] = stu;
    }
}
