#include "stdafx.h"
#include "GuardPrivilege.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "CfgData.h"
#include "Bag.h"
#include <cstring>

CGuardPrivilege::CGuardPrivilege()
    : m_nState(0), m_nLastTick(0)
{
}

CGuardPrivilege::~CGuardPrivilege()
{
}

void CGuardPrivilege::OnLoadFromDB( const PlayerDBData& dbData )
{
}

void CGuardPrivilege::OnSaveToDB( PlayerDBData& dbData )
{
}

void CGuardPrivilege::GetInterestsProtocol( ProcIdList& procList )
{
    procList.push_back( 980 );   // onRequestInfo
    procList.push_back( 981 );   // onGetReward
    procList.push_back( 20259 ); // onDBGetReward
}

int32_t CGuardPrivilege::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
    if ( NULL == inPacket )
        return 2;
    if ( !isOpen() )
        return 2;
    switch ( nProcId )
    {
    case 980:
        return onRequestInfo( inPacket );
    case 20259:
        return onDBGetReward( inPacket );
    case 981:
        return onGetReward( inPacket );
    }
    return 0;
}

void CGuardPrivilege::OnCleanUp()
{
    m_nState = 0;
    m_nLastTick = 0;
}

void CGuardPrivilege::OnUpdate( int64_t curTick )
{
    if ( isOpen() && curTick - m_nLastTick > 999 )
    {
        m_nLastTick = curTick;
        int8_t nState = getTimeState();
        if ( m_nState != nState )
        {
            m_nState = nState;
            sendIconState();
        }
    }
}

bool CGuardPrivilege::isOpen()
{
    if ( NULL == m_pPlayer )
        return false;
    return m_pPlayer->GetPlatform() == "w360";
}

int8_t CGuardPrivilege::getTimeState()
{
    if ( NULL == m_pPlayer )
        return 0;

    int32_t nNowTime = m_pPlayer->getNow();
    int32_t nStartTime = CFG_DATA.GetGuardPrivilegeStartTime();
    int32_t nEndTime = CFG_DATA.GetGuardPrivilegeEndTime();

    if ( nStartTime > nNowTime )
        return 0;
    if ( nEndTime >= nNowTime )
        return 2;
    return 4;
}

void CGuardPrivilege::GetIconState( IconStateList& iconList )
{
    if ( isOpen() && getTimeState() == 2 )
    {
        ShowIcon icon;
        memset( &icon, 0, sizeof(icon) );
        icon.nId = 62;
        icon.nState = 2;
        iconList.push_back( icon );
    }
}

void CGuardPrivilege::sendIconState()
{
    if ( NULL == m_pPlayer )
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ONE_ICON );
    if ( packet )
    {
        ShowIcon stu;
        memset( &stu, 0, sizeof(stu) );
        stu.nId = 62;
        stu.nState = m_nState;
        stu.nLeftTime = -1;

        packet->writeInt32( stu.nId );
        packet->writeInt8( stu.nState );
        packet->writeInt32( stu.nLeftTime );
        packet->writeInt8( stu.IconLeft );
        packet->writeInt32( stu.IconRight );
        packet->writeInt8( stu.Effects );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
    }
}

int32_t CGuardPrivilege::onRequestInfo( Answer::NetPacket *inPacket )
{
    if ( NULL == inPacket || NULL == m_pPlayer )
        return 2;
    sendInfo();
    return 0;
}

int32_t CGuardPrivilege::onGetReward( Answer::NetPacket *inPacket )
{
    if ( NULL == inPacket || NULL == m_pPlayer )
        return 2;

    int8_t nIndex = inPacket->readInt8();
    const CfgGuardPrivilege* pReward = CFG_DATA.GetGuardPrivilege( nIndex );
    if ( NULL == pReward )
        return 10002;

    int32_t nRecord = ( pReward->nDaily == 1 ) ? 2053 : 1109;
    int32_t nOldRecord = m_pPlayer->GetOperateLimit().GetLimitCount( nRecord );
    if ( nOldRecord == ( nOldRecord | (1 << nIndex) ) )
        return 10002;

    // Cross-server verification not needed in single-server mode
    // Falls back to direct local processing with duplicate-prevention via OperateLimit records
    return onDBGetReward( inPacket );
}

int32_t CGuardPrivilege::onDBGetReward( Answer::NetPacket *inPacket )
{
    if ( NULL == inPacket || NULL == m_pPlayer )
        return 2;

    int8_t nIndex = inPacket->readInt8();
    if ( !inPacket->readInt8() )
        return 2;

    const CfgGuardPrivilege* pReward = CFG_DATA.GetGuardPrivilege( nIndex );
    if ( NULL == pReward )
        return 10002;

    int32_t nRecord = ( pReward->nDaily == 1 ) ? 2053 : 1109;
    int32_t nOldRecord = m_pPlayer->GetOperateLimit().GetLimitCount( nRecord );
    int32_t nNewRecord = nOldRecord | (1 << nIndex);
    if ( nOldRecord == nNewRecord )
        return 10002;

    if ( !m_pPlayer->GetBag().AddItem( pReward->vReward, (ITEM_ADD_REASON)IACR_GUARD_PRIVILEGE_REWARD ) )
        return 10002;

    m_pPlayer->GetOperateLimit().UpdateLimitCount( nRecord, nNewRecord );
    GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
    return 0;
}

void CGuardPrivilege::sendInfo()
{
    if ( NULL == m_pPlayer )
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2F2B );
    if ( NULL == packet )
        return;

    int32_t nRewardRecord = m_pPlayer->GetOperateLimit().GetLimitCount( 1109 );
    int32_t nDailyRecord = m_pPlayer->GetOperateLimit().GetLimitCount( 2053 );
    const CfgGuardPrivilegeMap& map = CFG_DATA.GetGuardPrivilegeMap();

    packet->writeInt8( (int8_t)map.size() );

    for ( CfgGuardPrivilegeMap::const_iterator iter = map.begin(); iter != map.end(); ++iter )
    {
        const CfgGuardPrivilege& guard = iter->second;
        packet->writeInt8( guard.nIndex );
        if ( guard.nDaily == 1 )
            packet->writeInt8( (int8_t)((nDailyRecord >> guard.nIndex) & 1) );
        else
            packet->writeInt8( (int8_t)((nRewardRecord >> guard.nIndex) & 1) );
    }

    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}
