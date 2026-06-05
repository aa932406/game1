#include "stdafx.h"
#include "UltimateChallenge.h"
#include "ActivityMap.h"
#include "Monster.h"
#include "MonsterActivity.h"
#include "DropItem.h"
#include "Player.h"
#include "DBService.h"
#include "CfgData.h"
#include "Bag.h"
#include "Currency.h"
#include "Timer.h"
#include "GameService.h"

using namespace Answer;

typedef std::list<CActivityMap*> ActivityMapList;

CUltimateChallenge::CUltimateChallenge( const CfgActivity& cfgActivity )
    : CActivity( cfgActivity )
    , m_ActState( 0 )
    , m_lastUpdateTime( 0 )
    , m_nRand( 0 )
    , m_MonsterScore( 0 )
{
}

CUltimateChallenge::~CUltimateChallenge()
{
}

void CUltimateChallenge::Init()
{
    CActivity::Init();
}

void CUltimateChallenge::OnUpdate( CActivityMap* pMap )
{
    CActivity::OnUpdate( pMap );
    if ( NULL == pMap )
    {
        return;
    }

    if ( pMap->getTick() - m_lastUpdateTime > 1000 && !m_ActState )
    {
        m_lastUpdateTime = pMap->getTick();
        if ( IsRuning() && getActivityTime() > 599 )
        {
            m_ActState = 1;
            BroadcastActivityState();
        }
    }
}

int8_t CUltimateChallenge::GetState()
{
    if ( m_nState == AS_RUNNING && getActivityTime() > 599 )
    {
        return 3;
    }
    return m_nState;
}

int32_t CUltimateChallenge::GetIconLeftTime()
{
    return 600 - getActivityTime();
}

void CUltimateChallenge::GetIconState( IconStateList& iconList )
{
    CActivity::GetIconState( iconList );
}

Answer::NetPacket* CUltimateChallenge::packetActivityScore()
{
    return NULL;
}

void CUltimateChallenge::reset()
{
    CActivity::reset();
    m_ActState = 0;
    m_lastUpdateTime = 0;
    m_nRand = 0;
    m_MonsterScore = 0;
}

int32_t CUltimateChallenge::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
    if ( m_nState != AS_RUNNING )
    {
        return 10002;
    }

    // MapId 50041 is the boss room - block entry when ActState is active (time > 599s)
    if ( pTargetMap != NULL && pTargetMap->GetId() == 50041 && m_ActState )
    {
        return 10002;
    }

    return CActivity::canEnter( player, pTargetMap );
}

void CUltimateChallenge::addPlayer( Player* player )
{
    if ( NULL == player )
    {
        return;
    }

    // Set PK mode based on whether player has a family
    if ( player->getFamilyId() <= 0 )
    {
        player->setPkMode( PK_MODE_ALL, false );
    }
    else
    {
        player->setPkMode( PK_MODE_LEGION, false );
    }

    CActivity::addPlayer( player );
}

void CUltimateChallenge::removePlayer( Player* player, bool islogout )
{
    if ( NULL == player )
    {
        return;
    }

    int32_t nMapId = player->getMapId();
    const CfgUltimateChallenge* pCfg = CFG_DATA.GetUltimateChallengeCfg( nMapId );

    if ( pCfg != NULL )
    {
        // Clean cost items from player's bag when leaving
        ItemData costItem( pCfg->CostItems.m_nId, pCfg->CostItems.m_nClass, pCfg->GetItems.size() );
        player->GetBag().RemoveItem( costItem, IDCR_DUNGEON );
    }

    CActivity::removePlayer( player, islogout );
}

bool CUltimateChallenge::OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t Param )
{
    if ( NULL == player || NULL == pMap )
    {
        return false;
    }

    if ( !pMap->isWalkablePosition( nX, nY ) )
    {
        return false;
    }

    int32_t nMapId = player->getMapId();
    const CfgUltimateChallenge* pCfg = CFG_DATA.GetUltimateChallengeCfg( nMapId );

    if ( NULL == pCfg )
    {
        return false;
    }

    // Check if this map belongs to this activity
    bool bFind = false;
    for ( std::list<CActivityMap*>::iterator iter = m_activityMaps.begin(); iter != m_activityMaps.end(); ++iter )
    {
        CActivityMap* tp = *iter;
        if ( tp != NULL && tp == pMap )
        {
            bFind = true;
            break;
        }
    }

    if ( !bFind )
    {
        return false;
    }

    // Target map must match configured NextMapId
    if ( pMap->GetId() != pCfg->NextMapId )
    {
        return false;
    }

    int32_t nMaxFloor = player->getRecord( 2082 );

    // If param > 0 and this floor hasn't been cleared yet, check gold for double reward
    if ( Param > 0 && pCfg->Floor > nMaxFloor )
    {
        int64_t nGold = player->GetCurrency( CURRENCY_GOLD );
        if ( nGold < pCfg->DoubleConst )
        {
            return false;
        }
    }

    // Remove cost item
    ItemData costItem( pCfg->CostItems.m_nId, pCfg->CostItems.m_nClass, 1 );
    if ( !player->GetBag().RemoveItem( costItem, IDCR_DUNGEON ) )
    {
        return false;
    }

    if ( pCfg->Floor <= nMaxFloor )
    {
        // Already cleared this floor, just switch map
        return player->switchMap( pMap, nX, nY, true ) == 0;
    }

    // First time clearing this floor - give rewards via mail
    MemChrBagVector getItems = pCfg->GetItems;

    if ( Param > 0 )
    {
        // Double reward - deduct gold and triple items
        if ( !player->DecCurrency( CURRENCY_GOLD, pCfg->DoubleConst, GCR_ENTER_DUNGEON, 0 ) )
        {
            return false;
        }

        for ( MemChrBagVector::iterator it = getItems.begin(); it != getItems.end(); ++it )
        {
            it->itemCount *= 3;
        }
    }

    // Send rewards via mail
    DB_SERVICE.OnSendSysMail( player->getCid(), pCfg->MailId, getItems, "" );

    // Update player record for this floor
    player->updateRecord( 2082, pCfg->Floor );

    return player->switchMap( pMap, nX, nY, true ) == 0;
}

void CUltimateChallenge::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
    if ( NULL == pMonster || NULL == pKiller )
    {
        return;
    }

    // Only process activity monster with score mechanic
    if ( !pMonster->isActivityMonster() || m_nRand <= 0 )
    {
        return;
    }

    int32_t nStartDays = TIMER.GetDaysFromStart();
    if ( nStartDays > 2 )
    {
        return;
    }

    int32_t nMapId = pKiller->getMapId();
    const CfgUltimateChallenge* pCfg = CFG_DATA.GetUltimateChallengeCfg( nMapId );

    if ( NULL == pCfg || pCfg->Score <= 0 )
    {
        return;
    }

    m_MonsterScore += pCfg->Score;

    if ( m_MonsterScore >= m_nRand )
    {
        // Accumulated enough score - drop equipment
        int32_t nEquipId = 0;
        int32_t nRand = RANDOM.generate( 1, 10000 );

        for ( std::list<Param2>::const_iterator it = pCfg->DropRateList.begin(); it != pCfg->DropRateList.end(); ++it )
        {
            if ( it->nParam2 <= nRand )
            {
                nEquipId = it->nParam1;
                break;
            }
            nRand -= it->nParam2;
        }

        if ( nEquipId >= 0 )
        {
            // Create drop item group
            DropItem dropItems[MAX_DROPITEM_SIZE];
            memset( dropItems, 0, sizeof( dropItems ) );
            dropItems[0].itemId = nEquipId;
            dropItems[0].itemClass = IC_EQUIP;
            dropItems[0].itemCount = 1;

            Map* pMap = pMonster->getMap();
            if ( pMap != NULL )
            {
                Position pos = pMonster->getCurrentTile();
                CDropItemGroup* pGroup = new CDropItemGroup();
                if ( pGroup != NULL )
                {
                    pGroup->init( pMap, pos, pKiller, 2, nEquipId, dropItems, "", 0, 0 );
                    pMap->addDropItemGroup( pGroup );
                    m_nRand = 0;
                }
            }
        }
    }
}

void CUltimateChallenge::onPlayerKilled( Player* pDier, Player* pKiller )
{
    // Intentionally empty
}

void CUltimateChallenge::onPlayerRevive( Player* player, bool bSafe )
{
    if ( NULL == player )
    {
        return;
    }

    if ( bSafe )
    {
        player->leaveActivity();
    }
}

void CUltimateChallenge::BroadcastActivityState()
{
    int8_t nIconState = GetState();

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ONE_ICON );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( m_cfgActivity.iconid );
    packet->writeInt8( nIconState );

    if ( nIconState == 2 )
    {
        packet->writeInt32( 600 - getActivityTime() );
    }
    else
    {
        packet->writeInt32( getLeftTime() );
    }

    packet->writeInt8( 0 );
    packet->writeInt32( 0 );

    if ( nIconState == 2 )
    {
        packet->writeInt8( 1 );
    }
    else
    {
        packet->writeInt8( 0 );
    }

    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CUltimateChallenge::broadcastReady()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( 420 );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CUltimateChallenge::broadcastStart()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( 419 );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );

    m_nRand = RANDOM.generate( 1, 10000 );
}
