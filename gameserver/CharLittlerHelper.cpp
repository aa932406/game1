#include "stdafx.h"
#include "CharLittlerHelper.h"
#include "Map.h"
#include "MapManager.h"
#include "CfgData.h"
#include "DropItem.h"
#include "GameService.h"
#include "Bag.h"
#include "PoolManager.h"
#include "Currency.h"
#include "Timer.h"

using namespace Answer;

CharLittlerHelper::CharLittlerHelper()
    : CExtSystemBase()
    , m_LittleHelperId( 0 )
    , m_CLittleHelper( NULL )
    , m_NeedPick( 0 )
{
    bzero( m_PickSetUp, sizeof( m_PickSetUp ) );
}

CharLittlerHelper::~CharLittlerHelper()
{
}

void CharLittlerHelper::GetInterestsProtocol( ProcIdList& procList )
{
    // CM_LITTLE_HELPER_WORK = 530, CM_LITTLE_HELPER_REST = 531, CM_LITTLE_HELPER_BUY = 532
    procList.push_back( CM_LITTLE_HELPER_WORK );
    procList.push_back( CM_LITTLE_HELPER_REST );
    procList.push_back( CM_LITTLE_HELPER_BUY );
}

int32_t CharLittlerHelper::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
    if ( !inPacket )
        return 2;
    switch ( nProcId )
    {
    case CM_LITTLE_HELPER_WORK:
        return OnWork( inPacket );
    case CM_LITTLE_HELPER_REST:
        return OnRest( inPacket );
    case CM_LITTLE_HELPER_BUY:
        return OnBuyLittlerHelper( inPacket );
    }
    return 2;
}

void CharLittlerHelper::OnLoadFromDB( const PlayerDBData *const dbData )
{
    // TODO: PlayerDBData integration - stub
}

void CharLittlerHelper::OnSaveToDB( PlayerDBData *const dbData )
{
    // TODO: PlayerDBData integration - stub
}

void CharLittlerHelper::OnCleanUp()
{
    if ( m_CLittleHelper )
    {
        m_CLittleHelper->LeaveMap();
        POOL_MANAGER.push<CLittleHelper>( m_CLittleHelper );
        m_CLittleHelper = NULL;
    }
    m_ActMap.clear();
    m_LittleHelperId = 0;
}

void CharLittlerHelper::OnUpdate( int64_t curTick )
{
    if ( m_CLittleHelper )
    {
        m_CLittleHelper->refresh();
        if ( m_CLittleHelper->IsWork() )
        {
            int32_t nId = m_CLittleHelper->OnGetLittleHelperId();
            ActLittleHelperInfo* pInfo = GetActLittleHelperInfo( nId );
            if ( pInfo && pInfo->nTimes < TIMER.GetNow() )
            {
                m_CLittleHelper->LeaveMap();
                m_CLittleHelper->OnRest();
                SendCharLittlerhelper();
            }
        }
    }
}

ActLittleHelperInfo* CharLittlerHelper::GetActLittleHelperInfo( int32_t nId )
{
    std::map<int32_t, ActLittleHelperInfo>::iterator it = m_ActMap.find( nId );
    if ( it != m_ActMap.end() )
        return &it->second;
    return NULL;
}

int32_t CharLittlerHelper::OnAutoWork()
{
    return OnWork( m_LittleHelperId );
}

int32_t CharLittlerHelper::OnWork( int32_t nId )
{
    ActLittleHelperInfo* pInfo = GetActLittleHelperInfo( nId );
    if ( !pInfo )
        return 2;
    if ( pInfo->nTimes < TIMER.GetNow() )
        return 2;
    
    if ( m_CLittleHelper )
    {
        if ( m_CLittleHelper->OnGetLittleHelperId() == nId && m_CLittleHelper->IsWork() )
            return 2;
        if ( m_CLittleHelper->OnGetLittleHelperId() != nId )
            m_CLittleHelper->ChangeLittleHelperId( nId, pInfo->nSkin );
    }
    else
    {
        m_CLittleHelper = POOL_MANAGER.pop<CLittleHelper>();
        if ( !m_CLittleHelper )
            return 2;
        m_CLittleHelper->init( m_pPlayer, nId, pInfo->nSkin );
    }
    m_CLittleHelper->EnterMap();
    m_CLittleHelper->OnWork();
    m_LittleHelperId = nId;
    SendCharLittlerhelper();
    return 0;
}

int32_t CharLittlerHelper::OnWork( Answer::NetPacket *inPacket )
{
    if ( !inPacket || !m_pPlayer )
        return 2;
    if ( GAME_SERVICE.getLine() == 9 )
        return 2;
    int32_t nId = inPacket->readInt32();
    Map* pMap = (Map*)m_pPlayer->getMap();
    if ( !pMap )
        return 2;
    if ( !pMap->IsActivityMap() )
        return 2;
    
    if ( !OnWork( nId ) )
    {
        uint16_t Proc = inPacket->getProc();
        int16_t GateIndex = m_pPlayer->getGateIndex();
        GAME_SERVICE.replySuccess( GateIndex, Proc, nId );
    }
    return 0;
}

int32_t CharLittlerHelper::OnRest( Answer::NetPacket *inPacket )
{
    if ( !inPacket || !m_pPlayer || !m_CLittleHelper )
        return 2;
    if ( !m_CLittleHelper->IsWork() )
        return 10002;
    m_CLittleHelper->LeaveMap();
    m_CLittleHelper->OnRest();
    m_LittleHelperId = 0;
    uint16_t Proc = inPacket->getProc();
    int16_t GateIndex = m_pPlayer->getGateIndex();
    GAME_SERVICE.replySuccess( GateIndex, Proc, 0 );
    return 0;
}

int32_t CharLittlerHelper::OnRest()
{
    if ( !m_pPlayer || !m_CLittleHelper )
        return 2;
    if ( m_CLittleHelper->IsWork() )
    {
        m_CLittleHelper->LeaveMap();
        m_CLittleHelper->OnRest();
        SendCharLittlerhelper();
    }
    return 0;
}

int32_t CharLittlerHelper::AddLittlerHelper( int32_t nId, int32_t nAddTime )
{
    if ( !m_pPlayer )
        return 2;
    if ( GAME_SERVICE.getLine() == 9 )
        return 2;
    Map* pMap = (Map*)m_pPlayer->getMap();
    if ( !pMap )
        return 2;
    
    ActLittleHelperInfo* pInfo = GetActLittleHelperInfo( nId );
    int32_t nTime = TIMER.GetNow();
    if ( pInfo )
    {
        if ( pInfo->nTimes < nTime )
            pInfo->nTimes = nTime + nAddTime;
        else
            pInfo->nTimes = nAddTime + pInfo->nTimes;
    }
    else
    {
        ActLittleHelperInfo stu;
        stu.nId = nId;
        stu.nTimes = nTime + nAddTime;
        stu.nSkin = 0;
        m_ActMap[nId] = stu;
    }
    
    if ( pMap->IsActivityMap() )
        OnWork( nId );
    SendCharLittlerhelper();
    return 0;
}

int32_t CharLittlerHelper::OnBuyLittlerHelper( Answer::NetPacket *inPacket )
{
    if ( !inPacket || !m_pPlayer )
        return 2;
    if ( GAME_SERVICE.getLine() == 9 )
        return 2;
    Map* pMap = (Map*)m_pPlayer->getMap();
    if ( !pMap )
        return 2;
    if ( !pMap->IsActivityMap() )
        return 2;
    
    int32_t nId = inPacket->readInt32();
    ActLittleHelperInfo* pInfo = GetActLittleHelperInfo( nId );
    LittleHelperCfg* pCfg = CFG_DATA.GetLittleHelperCfg( nId );
    if ( !pCfg )
        return 2;
    if ( pCfg->nGold <= 0 || pCfg->nReGold <= 0 || pCfg->nTime <= 0 )
        return 2;
    
    int32_t nTime = TIMER.GetNow();
    int32_t NeedGold = 0;
    int32_t DaoQiTime = 0;
    
    if ( pInfo )
    {
        if ( pInfo->nTimes < nTime )
        {
            NeedGold = pCfg->nGold;
            DaoQiTime = nTime + pCfg->nTime;
        }
        else
        {
            NeedGold = pCfg->nReGold;
            DaoQiTime = pInfo->nTimes + pCfg->nTime;
        }
        if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, NeedGold, GCR_BUY_LITTLE_HELPER, 0 ) )
            return 2;
        pInfo->nTimes = DaoQiTime;
    }
    else
    {
        if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nGold, GCR_BUY_LITTLE_HELPER, 0 ) )
            return 2;
        ActLittleHelperInfo stu;
        stu.nId = nId;
        stu.nTimes = nTime + pCfg->nTime;
        stu.nSkin = 0;
        m_ActMap[nId] = stu;
    }
    
    OnWork( nId );
    SendCharLittlerhelper();
    
    uint16_t Proc = inPacket->getProc();
    int16_t GateIndex = m_pPlayer->getGateIndex();
    GAME_SERVICE.replySuccess( GateIndex, Proc, nId );
    
    if ( pCfg->nGongGaoId > 0 )
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
        if ( packet )
        {
            packet->writeInt32( pCfg->nGongGaoId );
            packet->writeUTF8( m_pPlayer->getName() );
            packet->writeInt64( m_pPlayer->getCid() );
            packet->setSize( packet->getWOffset() );
            GAME_SERVICE.worldBroadcast( packet );
        }
    }
    return 0;
}

void CharLittlerHelper::SendCharLittlerhelper()
{
    if ( !m_pPlayer )
        return;
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_LITTLE_HELPER_INFO );
    if ( !packet )
        return;
    
    if ( m_CLittleHelper && m_CLittleHelper->IsWork() )
        packet->writeInt32( m_CLittleHelper->OnGetLittleHelperId() );
    else
        packet->writeInt32( 0 );
    
    packet->writeInt32( (int32_t)m_ActMap.size() );
    for ( std::map<int32_t, ActLittleHelperInfo>::iterator it = m_ActMap.begin(); it != m_ActMap.end(); ++it )
    {
        packet->writeInt32( it->second.nId );
        packet->writeInt32( it->second.nTimes );
    }
    packet->setSize( packet->getWOffset() );
    int16_t GateIndex = m_pPlayer->getGateIndex();
    GAME_SERVICE.sendPacketTo( GateIndex, packet );
}

void CharLittlerHelper::SetTargetTile( int32_t tx, int32_t ty, Direction dir )
{
    if ( m_CLittleHelper && m_CLittleHelper->IsWork() )
        m_CLittleHelper->ResetTargetTile( tx, ty, dir );
}

void CharLittlerHelper::AddCharAttr()
{
    if ( !m_pPlayer )
        return;
    int32_t nNow = TIMER.GetNow();
    for ( std::map<int32_t, ActLittleHelperInfo>::iterator it = m_ActMap.begin(); it != m_ActMap.end(); ++it )
    {
        if ( it->second.nTimes > nNow )
        {
            LittleHelperCfg* pCfg = CFG_DATA.GetLittleHelperCfg( it->first );
            if ( pCfg )
            {
                for ( AddAttrList::iterator ait = pCfg->lAttr.begin(); ait != pCfg->lAttr.end(); ++ait )
                {
                    m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)ait->m_nAddAttrType, ait->m_nAddAttrValue );
                }
            }
        }
    }
}

bool CharLittlerHelper::CanPick( int8_t nClass, int32_t nId )
{
    if ( !m_pPlayer )
        return false;
    if ( IsFilterItem( nClass, nId ) )
        return false;
    return true;
}

bool CharLittlerHelper::IsFilterItem( int8_t nclass, int32_t nId )
{
    std::map<std::pair<int8_t, int32_t>, int32_t>::iterator it = m_ItemFilterMap.find( std::make_pair( nclass, nId ) );
    return it != m_ItemFilterMap.end();
}

bool CharLittlerHelper::IsFilterEquipGrade( int32_t Grade )
{
    return m_EquipFilter.find( Grade ) != m_EquipFilter.end();
}

void CharLittlerHelper::parsePickString( std::string *pStr )
{
    m_ItemFilterMap.clear();
    m_EquipFilter.clear();
    m_NeedPick = 1;
}
