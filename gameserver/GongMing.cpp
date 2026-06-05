#include "stdafx.h"
#include "GongMing.h"
#include "Player.h"
#include "GameService.h"
#include "CfgData.h"

CGongMing::CGongMing()
{
}

CGongMing::~CGongMing()
{
}

void CGongMing::OnLoadFromDB( const PlayerDBData& dbData )
{
}

void CGongMing::OnSaveToDB( PlayerDBData& dbData )
{
}

void CGongMing::GetInterestsProtocol( ProcIdList& procList )
{
    procList.push_back( 262 );
}

int32_t CGongMing::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
    if ( NULL == m_pPlayer || NULL == inPacket )
        return ERR_INVALID_DATA;
    if ( nProcId == 262 )
        return OnGongMinLevelUp( inPacket );
    return ERR_INVALID_DATA;
}

void CGongMing::OnCleanUp()
{
}

void CGongMing::OnUpdate( int64_t curTick )
{
}

void CGongMing::AddGongMingValues( int32_t Values )
{
    if ( Values > 0 && NULL != m_pPlayer )
    {
        m_pPlayer->GetOperateLimit().AddLimitCount( 1162, Values );
        SendGongMinInfo();
    }
}

void CGongMing::AddCharAttr()
{
    if ( NULL == m_pPlayer )
        return;

    int32_t CurLevel = m_pPlayer->getRecord( 1161 );
    const GongMingCfg* CurCfg = CFG_DATA.GetGongMingCfg( CurLevel );
    if ( NULL == CurCfg )
        return;

    for ( AddAttrList::const_iterator iter = CurCfg->lAttrList.begin();
          iter != CurCfg->lAttrList.end(); ++iter )
    {
        m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)iter->m_nAddAttrType, iter->m_nAddAttrValue );
    }
}

int32_t CGongMing::OnGongMinLevelUp( Answer::NetPacket *inPacket )
{
    if ( NULL == m_pPlayer || NULL == inPacket )
        return ERR_INVALID_DATA;

    int32_t CurLevel = m_pPlayer->getRecord( 1161 );
    const GongMingCfg* CurCfg = CFG_DATA.GetGongMingCfg( CurLevel );
    const GongMingCfg* NextCfg = CFG_DATA.GetGongMingCfg( CurLevel + 1 );
    int32_t HaveCurr = m_pPlayer->getRecord( 1162 );

    if ( NULL == CurCfg || NULL == NextCfg )
        return ERR_INVALID_DATA;

    if ( CurCfg->NeedGongMingZhi > HaveCurr )
        return ERR_INVALID_DATA;

    m_pPlayer->updateRecord( 1162, HaveCurr - CurCfg->NeedGongMingZhi );
    m_pPlayer->updateRecord( 1161, CurLevel + 1 );

    if ( NextCfg->GongGaoId > 0 )
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
        if ( packet )
        {
            packet->writeInt32( NextCfg->GongGaoId );
            packet->writeUTF8( m_pPlayer->getName() );
            packet->writeInt64( m_pPlayer->getCid() );
            packet->writeInt32( NextCfg->nChong );
            packet->writeInt32( NextCfg->nStar );
            packet->setSize( packet->getWOffset() );
            GAME_SERVICE.worldBroadcast( packet );
        }
    }

    m_pPlayer->RecalcAttr();
    SendGongMinInfo();
    GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
    return ERR_OK;
}

void CGongMing::SendGongMinInfo()
{
    if ( NULL == m_pPlayer )
        return;

    int32_t HaveCurr = m_pPlayer->getRecord( 1162 );
    int32_t CurLevel = m_pPlayer->getRecord( 1161 );
    const GongMingCfg* CurCfg = CFG_DATA.GetGongMingCfg( CurLevel );
    if ( NULL == CurCfg )
        return;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2DCC );
    if ( packet )
    {
        packet->writeInt32( CurCfg->nChong );
        packet->writeInt32( CurCfg->nStar );
        packet->writeInt32( HaveCurr );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
    }
}
