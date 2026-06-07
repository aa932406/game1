#include "stdafx.h"
#include "SevenDayTask.h"
#include "GameService.h"
#include "Timer.h"
#include "Bag.h"
#include "CharWing.h"
#include "JueWei.h"
#include "Equip.h"

// Helper: calculate days between now and a timestamp
static int32_t Diff24Hour( int32_t nOldTime )
{
    if ( nOldTime <= 0 )
    {
        return 0;
    }
    int32_t nNowTime = TIMER.GetNow();
    int32_t nDiff = nNowTime - nOldTime;
    if ( nDiff < 0 )
    {
        nDiff = 0;
    }
    return nDiff / 86400;  // seconds per day
}

void CSevenDayTask::OnLoadFromDB( const PlayerDBData* dbData )
{
    if ( NULL == m_pPlayer || NULL == dbData )
    {
        return;
    }
    m_OpenTime = dbData->m_CSevenDayData.m_OpenTime;
    m_RewardState = dbData->m_CSevenDayData.m_RewardState;
    m_SumRewardState = dbData->m_CSevenDayData.m_SumRewardState;
    m_DiffDay = Diff24Hour( m_OpenTime ) + 1;
    OpenSevenDayTask();
}

void CSevenDayTask::OnSaveToDB( PlayerDBData* dbData )
{
    if ( NULL == dbData )
    {
        return;
    }
    dbData->m_CSevenDayData.m_OpenTime = m_OpenTime;
    dbData->m_CSevenDayData.m_RewardState = m_RewardState;
    dbData->m_CSevenDayData.m_SumRewardState = m_SumRewardState;
}

void CSevenDayTask::GetInterestsProtocol( ProcIdList& procList )
{
    procList.push_back( 567 );
    procList.push_back( 568 );
    procList.push_back( 569 );
}

int32_t CSevenDayTask::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
    if ( NULL == inPacket )
    {
        return 2;
    }
    switch ( nProcId )
    {
    case 567:   // 0x237 - SendTaskState
        SendTaskSTate();
        break;
    case 568:   // 0x238 - OnAskReward
        return OnAskReward( inPacket );
    case 569:   // 0x239 - OnAskSumReward
        return OnAskSumReward( inPacket );
    default:
        return 2;
    }
    return 0;
}

void CSevenDayTask::OnCleanUp()
{
    m_OpenTime = 0;
    m_RewardState.clear();
    m_LastUpdateTick = 0;
    m_SumRewardState = 0;
    m_bShowIcon = false;
    m_DiffDay = 0;
}

void CSevenDayTask::OnUpdate( int64_t curTick )
{
    if ( curTick - m_LastUpdateTick > 1000 && m_bShowIcon && m_OpenTime > 0 )
    {
        if ( Diff24Hour( m_OpenTime ) + 1 > 7 && HaveRewardCount() <= 0 )
        {
            SendIcon();
            m_bShowIcon = false;
        }
        int32_t nDiffDay = Diff24Hour( m_OpenTime ) + 1;
        if ( m_DiffDay != nDiffDay )
        {
            m_DiffDay = nDiffDay;
            SendIcon();
        }
        m_LastUpdateTick = curTick;
    }
}

void CSevenDayTask::OpenSevenDayTask()
{
    if ( NULL == m_pPlayer )
    {
        return;
    }
    if ( m_pPlayer->getLevel() > 99 && m_OpenTime <= 0 )
    {
        // Check server diff day
        if ( CFG_DATA.getServerDiffDay( 0 ) + 1 <= 7 )
        {
            m_OpenTime = m_pPlayer->getNow();
            UpdateTaskState( 1, m_pPlayer->getLevel(), false );
            UpdateTaskState( 2, m_pPlayer->getRecord( 1148 ), false );
            // Cross-module calls
            int32_t wingLevel = m_pPlayer->GetCharWing().GetLevel();
            UpdateTaskState( 3, wingLevel, false );
            int32_t jueWei = m_pPlayer->GetPlayerJueWei().GetJueWei();
            UpdateTaskState( 4, jueWei, false );
            int32_t totalGemLevel = m_pPlayer->GetEquip().GetEquipAllGemLevel();
            UpdateTaskState( 5, totalGemLevel, false );
            int32_t totalUpPosLevel = m_pPlayer->GetEquip().GetEquipAllUpPosLevel();
            UpdateTaskState( 6, totalUpPosLevel, false );
            SendIcon();
            SendTaskSTate();
        }
    }
}

void CSevenDayTask::UpdateTaskState( int32_t nType, int32_t Values, bool NeedSend )
{
    if ( m_OpenTime <= 0 )
    {
        return;
    }

    int32_t nDiffDay = Diff24Hour( m_OpenTime ) + 1;
    if ( nDiffDay > 7 )
    {
        return;
    }

    Int32List NeedSendId;
    const SevenTaskTable* pTable = CFG_DATA.GetSevenTaskTable();
    if ( NULL == pTable )
    {
        return;
    }

    const SevenTaskCfgMap& cfgMap = pTable->GetSevenTaskCfgMap();
    for ( SevenTaskCfgMap::const_iterator it = cfgMap.begin(); it != cfgMap.end(); ++it )
    {
        std::map<int32_t, int32_t>::iterator itState = m_RewardState.find( it->first );
        if ( itState == m_RewardState.end() )
        {
            if ( it->second.nEndDay >= nDiffDay
                && it->second.nType == nType
                && it->second.nCondition <= Values )
            {
                m_RewardState[it->first] = 0;
                NeedSendId.push_back( it->first );
            }
        }
    }

    if ( NeedSend && !NeedSendId.empty() )
    {
        SendIcon();
        SendTaskSTate();
    }
}

int32_t CSevenDayTask::OnAskReward( Answer::NetPacket* inPacket )
{
    if ( NULL == inPacket || NULL == m_pPlayer )
    {
        return 10002;
    }

    int32_t nId = inPacket->readInt32();
    const SevenTaskTable* pTable = CFG_DATA.GetSevenTaskTable();
    if ( NULL == pTable )
    {
        return 10002;
    }

    const SevenTaskCfg* pCfg = pTable->GetSevenTaskCfg( nId );
    if ( NULL == pCfg )
    {
        return 10002;
    }

    std::map<int32_t, int32_t>::iterator it = m_RewardState.find( nId );
    if ( it == m_RewardState.end() )
    {
        return 10002;
    }
    if ( it->second > 0 )
    {
        return 10002;
    }

    if ( !m_pPlayer->GetBag().AddItem( pCfg->Item, (ITEM_ADD_REASON)IDCR_SEVEN_DAY ) )
    {
        return 10002;
    }

    it->second = 1;
    SendIcon();
    SendTaskSTate();
    return 0;
}

int32_t CSevenDayTask::OnAskSumReward( Answer::NetPacket* inPacket )
{
    if ( NULL == inPacket || NULL == m_pPlayer )
    {
        return 10002;
    }

    int32_t nId = inPacket->readInt32();
    const SevenTaskTable* pTable = CFG_DATA.GetSevenTaskTable();
    if ( NULL == pTable )
    {
        return 10002;
    }

    const SevenTaskSumReward* pReward = pTable->GetSevenTaskSumReward( nId );
    if ( NULL == pReward )
    {
        return 10002;
    }

    if ( (int32_t)m_RewardState.size() < pReward->nFinishCount )
    {
        return 10002;
    }

    int32_t nNewState = (1 << (nId - 1)) | m_SumRewardState;
    if ( m_SumRewardState == nNewState )
    {
        return 10002;
    }

    if ( !m_pPlayer->GetBag().AddItem( pReward->Item, (ITEM_ADD_REASON)IDCR_SEVEN_DAY ) )
    {
        return 10002;
    }

    m_SumRewardState = nNewState;
    SendIcon();
    SendTaskSTate();

    // World broadcast if GongGaoId > 0
    if ( pReward->nGongGaoId > 0 )
    {
        Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
        if ( NULL != packet )
        {
            packet->writeInt32( pReward->nGongGaoId );
            packet->writeUTF8( m_pPlayer->getName() );
            packet->writeInt64( m_pPlayer->getCid() );
            packet->setSize( packet->getWOffset() );
            GAME_SERVICE.worldBroadcast( packet );
        }
    }

    return 0;
}

void CSevenDayTask::SendTaskSTate()
{
    if ( NULL == m_pPlayer )
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CC8 );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( m_OpenTime );
    packet->writeInt32( (int32_t)m_RewardState.size() );
    for ( std::map<int32_t, int32_t>::iterator it = m_RewardState.begin();
        it != m_RewardState.end(); ++it )
    {
        packet->writeInt32( it->first );
        packet->writeInt32( it->second );
    }
    packet->writeInt32( m_SumRewardState );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CSevenDayTask::GetIcon( IconStateList& IconList )
{
    if ( NULL == m_pPlayer )
    {
        return;
    }

    int32_t nDiffDay = Diff24Hour( m_OpenTime ) + 1;
    bool bExpired = ( nDiffDay > 7 && HaveRewardCount() <= 0 );
    if ( !bExpired && m_OpenTime > 0 )
    {
        ShowIcon stu;
        memset( &stu, 0, sizeof( stu ) );
        stu.nId = 106; // Seven day task icon
        stu.nState = 2;  // Show
        stu.nLeftTime = 0;
        IconList.push_back( stu );
    }
}

void CSevenDayTask::SendIcon()
{
    if ( NULL == m_pPlayer || m_OpenTime <= 0 )
    {
        return;
    }

    ShowIcon stu;
    memset( &stu, 0, sizeof( stu ) );
    stu.nId = 106; // Seven day task icon
    stu.nState = 2;
    stu.nLeftTime = 0;

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CC3 );
    if ( NULL != packet )
    {
        packet->writeInt32( stu.nId );
        packet->writeInt8( stu.nState );
        packet->writeInt32( stu.nLeftTime );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
    }
}

int32_t CSevenDayTask::HaveRewardCount()
{
    int32_t nDiffDay = Diff24Hour( m_OpenTime ) + 1;
    if ( nDiffDay <= 0 )
    {
        return 0;
    }

    int32_t nCount = 0;
    int32_t nFinishCount = 0;

    const SevenTaskTable* pTable = CFG_DATA.GetSevenTaskTable();
    if ( NULL == pTable )
    {
        return 0;
    }

    // Count task rewards
    for ( std::map<int32_t, int32_t>::iterator it = m_RewardState.begin();
        it != m_RewardState.end(); ++it )
    {
        const SevenTaskCfg* pCfg = pTable->GetSevenTaskCfg( it->first );
        if ( NULL != pCfg && pCfg->nStartDay <= nDiffDay )
        {
            ++nFinishCount;
            if ( it->second <= 0 )
            {
                ++nCount;
            }
        }
    }

    // Count sum rewards
    const SevenTaskSumRewardMap& sumMap = pTable->GetSevenTaskSumRewardMap();
    for ( SevenTaskSumRewardMap::const_iterator it = sumMap.begin(); it != sumMap.end(); ++it )
    {
        if ( it->second.nFinishCount <= nFinishCount )
        {
            int32_t nMask = 1 << (it->first - 1);
            if ( (m_SumRewardState & nMask) <= 0 )
            {
                ++nCount;
            }
        }
    }

    return nCount;
}
