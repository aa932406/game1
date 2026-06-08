#include "CrossTower.h"
#include "GameService.h"
#include "DBService.h"
#include "ActivityManager.h"
#include "ActivityMap.h"
#include "Timer.h"
#include "MapManager.h"
#include "Map.h"
#include "Monster.h"
#include "OperateLimit.h"
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace Answer;

CCrossTower::CCrossTower( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_nWinerId( 0 )
, m_nNewWinerId( 0 )
, m_nBattle( 0 )
, m_nConnId( 0 )
, m_pMonster( NULL )
, m_nNeedChangeMap( 0 )
, m_nNeedAddScore( 0 )
, m_nLastAddScoreTime( 0 )
, m_nLastUpdateTime( 0 )
, m_nStateTime( 0 )
{
}

CCrossTower::~CCrossTower()
{
}

void CCrossTower::Init()
{
    CActivity::Init();

    m_nWinerId = 0;
    m_sWinerName = "";
    m_pMonster = NULL;

    if ( GAME_SERVICE.getLine() == 9 )
    {
        DB_SERVICE.onLoadCrossTowerInfo();
    }
    else
    {
        MySqlDBGuard db( DBPOOL );
        MySqlQuery result = db.query( "SELECT * FROM `mem_cross_tower` where id=1" );
        if ( !result.eof() )
        {
            m_nWinerId    = result.getInt64Value( "cid", 0 );
            m_sWinerName  = result.getStringValue( "name", "" );
            m_nBattle     = result.getIntValue( "battle", 0 );
            if ( m_nWinerId > 0 )
            {
                ACTIVITY_MANAGER.SetCrossTowerWinner( m_nWinerId, m_nBattle, m_sWinerName );
            }
        }
    }
}

void CCrossTower::OnUpdate( CActivityMap* pMap )
{
    CActivity::OnUpdate( pMap );
    if ( NULL == pMap ) return;

    int32_t nMapId = pMap->GetId();

    // 1. 检查是否需要广播地图信息
    NeedSysMapSet::iterator findIt = m_NeedSysMap.find( nMapId );
    if ( findIt != m_NeedSysMap.end() )
    {
        Answer::NetPacket* packet = packetActivityMapInfo( pMap );
        if ( packet != NULL )
        {
            pMap->broadcast( packet );
            m_NeedSysMap.erase( findIt );
        }
        return;
    }

    // 2. 检查是否需要切换楼层
    if ( m_nNeedChangeMap )
    {
        PlayerList tList = m_players;
        for ( PlayerList::iterator iter = tList.begin(); iter != tList.end(); ++iter )
        {
            Player* player = *iter;
            if ( NULL == player ) continue;

            int32_t nCurMapId = player->getMapId();
            const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nCurMapId );
            if ( pCfg != NULL 
                && !( m_nState == AS_END && pCfg->nFloor == 8 ) 
                && pCfg->nNextMapId > 0 )
            {
                int32_t nRecord = player->getRecord( 3 );
                if ( nRecord >= pCfg->nKillCount )
                {
                    Map* pTargetMap = MAP_MANAGER.GetMap( pCfg->nNextMapId );
                    if ( pTargetMap != NULL )
                    {
                        CfgMapRegion* pRegion = CFG_DATA.getMapRegion( pTargetMap->getReive( player ) );
                        Position pos( 32, 56 );
                        if ( pRegion != NULL )
                        {
                            pos = pTargetMap->getRandomWalkablePositionInRegion( *pRegion );
                            if ( pos.x < 0 || pos.y < 0 )
                            {
                                pos.x = 32;
                                pos.y = 56;
                            }
                        }
                        player->FillHP();
                        player->FillMP();
                        player->switchMap( pTargetMap, pos.x, pos.y, false );
                    }
                }
            }
        }
        m_nNeedChangeMap = 0;
    }

    // 3. 检查是否需要加积分
    if ( m_nNeedAddScore )
    {
        PlayerList tList = m_players;
        for ( PlayerList::iterator iter = tList.begin(); iter != tList.end(); ++iter )
        {
            Player* player = *iter;
            if ( NULL == player ) continue;

            int32_t nCurMapId = player->getMapId();
            const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nCurMapId );
            Map* pMapObj = player->getMap();
            if ( pCfg != NULL && pMapObj != NULL )
            {
                int32_t nFloor       = pCfg->nFloor;
                int32_t nAliveCount  = pMap->GetAlivePlayerCount();
                int32_t nAddScore    = callAddScore( pCfg->nMaxPlayer, pCfg->nMaxScore, pCfg->nMinScore, nAliveCount, nFloor );

                if ( nAddScore > 0 )
                {
                    player->AddCurrency( CURRENCY_MONEY, nAddScore, MCR_MONEY_GAIN_ITEM, 0 );

                    PlayerScoreMap::iterator scoreIt = m_mPlayerScore.find( player->getCid() );
                    if ( scoreIt != m_mPlayerScore.end() )
                    {
                        scoreIt->second.nScore += nAddScore;
                        scoreIt->second.nScoreTime = player->getNow();
                        SendPlayerActivityScore( player, getLeftTime() );
                    }
                }
            }
        }
        m_nNeedAddScore = 0;
    }

    // 4. 检查胜负条件
    if ( nMapId != 60029 )
    {
        checkWin( false );
    }
}

void CCrossTower::SendPlayerActivityInfo( Player* player )
{
    if ( NULL == player ) return;

    NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
    if ( NULL == packet ) return;

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt64( m_nWinerId );
    packet->writeInt32( getNextStartTime() );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CCrossTower::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
    if ( NULL == player ) return;

    int32_t nPersonalScore = 0;
    PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
    if ( iter != m_mPlayerScore.end() )
    {
        nPersonalScore = iter->second.nScore;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
    if ( NULL == packet ) return;

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt64( m_nWinerId );
    packet->writeInt32( nPersonalScore );
    packet->writeInt32( nLeftTime );
    packet->writeInt32( m_nBattle );

    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

Position CCrossTower::GetRandBornPos( Player* player )
{
    return getBornRandPosA();
}

int32_t CCrossTower::GetRevive( Player* player )
{
    if ( NULL == player )
    {
        return CActivity::GetRevive( player );
    }
    int32_t nMapId = player->getMapId();
    const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nMapId );
    if ( NULL == pCfg )
    {
        return CActivity::GetRevive( player );
    }
    int32_t nTargetMapId = pCfg->LastMapId;
    if ( pCfg->Floor <= 5 )
    {
        nTargetMapId = pCfg->MapId;
    }
    Map* pTargetMap = MAP_MANAGER.GetMap( nTargetMapId );
    if ( pTargetMap != NULL )
    {
        return pTargetMap->getReive( player );
    }
    return CActivity::GetRevive( player );
}

void CCrossTower::SetWinnerInfo( CharId_t nWinnerId, const std::string& sName )
{
    m_nWinerId = nWinnerId;
    m_sWinerName = sName;

    if ( m_pMonster != NULL )
    {
        m_pMonster->SetFamilyId( 0, m_sWinerName );
    }
}

void CCrossTower::reset()
{
    m_nState = AS_NOT_START;
    m_nStateTime = 0;
    m_nLastUpdateTime = 0;
    m_mPlayerScore.clear();
    m_nNeedChangeMap = 0;
    m_nNeedAddScore = 0;
    m_nLastAddScoreTime = 0;
    m_NeedSysMap.clear();
    m_nNewWinerId = 0;
    m_sNewWinerName = "";
    m_nConnId = 0;
    m_nBattle = 0;
    m_pMonster = 0;
    CActivity::reset();
}

void CCrossTower::addPlayer( Player* player )
{
    if ( NULL == player )
    {
        CActivity::addPlayer( player );
        return;
    }

    if ( m_nState == AS_RUNNING )
    {
        player->setPkMode( 1, false );
    }
    else
    {
        player->setPkMode( 6, false );
    }

    int32_t nMapId = player->getMapId();
    m_NeedSysMap.insert( nMapId );
    player->updateRecord( 3, 0 );

    CharId_t nCid = player->getCid();
    PlayerScoreMap::iterator iter = m_mPlayerScore.find( nCid );
    if ( iter != m_mPlayerScore.end() )
    {
        iter->second.nConnId     = player->getGateIndex();
        iter->second.nCurMapId   = nMapId;
        iter->second.bInActivity = 1;
        iter->second.nScoreTime  = player->getNow();
    }
    else
    {
        PlayerScore score;
        score.nCharId     = nCid;
        score.nConnId     = player->getGateIndex();
        score.nScore      = 0;
        score.nScoreTime  = player->getNow();
        score.nCurMapId   = nMapId;
        score.bInActivity = 1;
        score.nKillCount  = 0;
        score.nIsMoBai    = 0;
        score.nBattle     = player->getBattle();
        score.nSid        = player->getSid();
        score.strName     = player->getName();
        m_mPlayerScore[nCid] = score;
    }

    CActivity::addPlayer( player );
}

void CCrossTower::removePlayer( Player* player, bool islogout )
{
    CActivity::removePlayer( player, islogout );

    if ( NULL == player ) return;

    int32_t nMapId = player->getMapId();
    m_NeedSysMap.insert( nMapId );
    player->updateRecord( 3, 0 );

    CharId_t nCid = player->getCid();
    PlayerScoreMap::iterator iter = m_mPlayerScore.find( nCid );
    if ( iter != m_mPlayerScore.end() )
    {
        iter->second.bInActivity = 0;
    }
}

int32_t CCrossTower::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
    if ( NULL == player || NULL == pTargetMap )
    {
        return 10002;
    }
    return CActivity::canEnter( player, pTargetMap );
}

void CCrossTower::onTimeEnd()
{
    checkWin( true );
    addRewards();

    m_nState = AS_END;
    delayKickAll( 30 );

    NetPacket* packet = GAME_SERVICE.popNetpacket( 0, Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( packet != NULL )
    {
        packet->writeInt32( 513 );
        packet->writeInt32( GetId() );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.worldBroadcast( 0, packet );
    }

    CActivity::onTimeEnd();
}

void CCrossTower::addRewards()
{
    if ( m_nWinerId > 0 )
    {
        GAME_SERVICE.onRemoveTitle( m_nWinerId, 9 );
    }

    m_nWinerId = m_nNewWinerId;
    m_sWinerName = m_sNewWinerName;

    if ( m_nNewWinerId > 0 )
    {
        GAME_SERVICE.onCheckTitle( m_nNewWinerId, 9, 1 );
    }

    ACTIVITY_MANAGER.SetCrossTowerResult( m_nNewWinerId, m_nBattle, m_sNewWinerName );

    int32_t nNow = TIMER.GetNow();
    DB_SERVICE.SaveCrossTowerResult( GetId(), m_nNewWinerId, m_sNewWinerName, m_nBattle, m_nConnId, nNow );

    CActivity::reset();

    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
    {
        const PlayerScore& score = iter->second;
        int32_t nCurMapId = score.nCurMapId;
        const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nCurMapId );
        if ( pCfg != NULL && score.bInActivity )
        {
            DB_SERVICE.OnSendSysMail( score.nConnId, score.nCharId, pCfg->MailId, pCfg->RewardVt, "" );
        }
    }

    m_mPlayerScore.clear();
    m_nNewWinerId = 0;
    m_sNewWinerName = "";
}

void CCrossTower::addPlayerScore( Player* player, int32_t nScore )
{
    if ( NULL == player ) return;

    PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
    if ( iter != m_mPlayerScore.end() )
    {
        iter->second.nScore += nScore;
        SendPlayerActivityScore( player, getLeftTime() );
    }
}

int32_t CCrossTower::callAddScore( int32_t nMaxPlayer, int32_t nMaxScore, 
                                    int32_t nMinScore, int32_t nCurPlayer, int32_t nFloor )
{
    if ( nCurPlayer <= nMaxPlayer )
    {
        return nMaxScore;
    }

    int32_t nDiffCount = nCurPlayer - nMaxPlayer;
    int32_t nScore;

    if ( nFloor <= 8 )
    {
        float fRatio = 1.0f + (float)(15 * nDiffCount) / -100.0f;
        if ( fRatio < 0.0f ) fRatio = 0.0f;
        nScore = (int32_t)(fRatio * (float)nMaxScore);
    }
    else
    {
        nScore = (int32_t)(std::pow( 0.5f, (float)nDiffCount ) * (float)nMaxScore);
    }

    if ( nScore < nMinScore )
    {
        return nMinScore;
    }
    return nScore;
}

void CCrossTower::checkWin( bool bForce )
{
    if ( m_nNewWinerId > 0 || m_nState != 3 )
    {
        return;
    }

    struct PlayerScoreGreater
    {
        bool operator()( const PlayerScore* a, const PlayerScore* b ) const
        {
            return a->nScore > b->nScore;
        }
    };
    typedef std::set<PlayerScore*, PlayerScoreGreater> PlayerScoreSet;

    PlayerScoreSet scoreRank;
    for ( PlayerScoreMap::iterator it = m_mPlayerScore.begin(); it != m_mPlayerScore.end(); ++it )
    {
        if ( it->second.nCurMapId == 60029 && it->second.bInActivity )
        {
            scoreRank.insert( &it->second );
        }
    }

    if ( bForce )
    {
        if ( !scoreRank.empty() )
        {
            PlayerScore* pTop = *scoreRank.begin();
            std::stringstream ss;
            ss << "s" << pTop->nSid << "." << pTop->strName;
            m_nNewWinerId = pTop->nCharId;
            m_sNewWinerName = ss.str();
            m_nConnId = pTop->nConnId;
            m_nBattle = pTop->nBattle;
        }
    }
    else if ( scoreRank.size() == 1 )
    {
        PlayerScore* pTop = *scoreRank.begin();
        std::stringstream ss;
        ss << "s" << pTop->nSid << "." << pTop->strName;
        m_nNewWinerId = pTop->nCharId;
        m_sNewWinerName = ss.str();
        m_nConnId = pTop->nConnId;
        m_nBattle = pTop->nBattle;
    }
}

Answer::NetPacket* CCrossTower::packetActivityMapInfo( CActivityMap* pMap )
{
    if ( NULL == pMap ) return NULL;

    NetPacket* packet = GAME_SERVICE.popNetpacket( 0, Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
    if ( NULL == packet ) return NULL;

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt64( m_nWinerId );
    packet->writeUTF8( m_sWinerName.c_str() );

    // 写入该地图中的玩家排行（前10名）
    int32_t nCount = 0;
    uint32_t nCountPos = packet->getWOffset();
    packet->writeInt8( 0 );

    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); 
          iter != m_mPlayerScore.end() && nCount < 10; ++iter )
    {
        Player* player = GAME_SERVICE.getPlayer( iter->first, 0, false );
        if ( NULL == player ) continue;

        packet->writeUTF8( player->getName() );
        packet->writeInt32( iter->second.nScore );
        ++nCount;
    }

    uint32_t nEndPos = packet->getWOffset();
    packet->setWOffset( nCountPos );
    packet->writeInt8( (int8_t)nCount );
    packet->setWOffset( nEndPos );

    packet->setSize( nEndPos );
    return packet;
}

void CCrossTower::onPlayerKilled( Player* pDier, Player* pKiller )
{
    if ( NULL == pDier || NULL == pKiller )
    {
        return;
    }

    m_NeedSysMap.insert( pDier->getMapId() );

    int32_t nMapId = pKiller->getMapId();
    const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nMapId );
    if ( pCfg == NULL )
    {
        return;
    }

    if ( pCfg->KillCount > pKiller->getRecord( 3 ) )
    {
        pKiller->GetOperateLimit().AddLimitCount( 3, 1 );
        pKiller->SetNeedSyncAround();
    }

    SendPlayerActivityScore( pKiller, getLeftTime() );

    CharId_t nCid = pKiller->getCid();
    PlayerScoreMap::iterator it = m_mPlayerScore.find( nCid );
    if ( it == m_mPlayerScore.end() )
    {
        return;
    }

    bool bGongGao = false;
    ++it->second.nKillCount;
    int32_t nKillCount = it->second.nKillCount;

    if ( nKillCount == 5 || nKillCount == 15 || nKillCount == 30
        || nKillCount == 50 || nKillCount == 100 || nKillCount == 150 )
    {
        bGongGao = true;
    }
    if ( nKillCount > 150 && nKillCount % 50 == 0 )
    {
        bGongGao = true;
    }

    if ( bGongGao )
    {
        NetPacket* packet = GAME_SERVICE.popNetpacket( pKiller->getConnId(), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
        if ( packet != NULL )
        {
            packet->writeInt32( 514 );
            packet->writeUTF8( pKiller->getName() );
            packet->writeInt64( pKiller->getCid() );
            packet->writeInt32( it->second.nKillCount );
            packet->setSize( packet->getWOffset() );
            GAME_SERVICE.worldBroadcast( pKiller->getConnId(), packet );
        }
    }
}

void CCrossTower::onMonsterAdd( MonsterActivity* pMonster )
{
    if ( pMonster != NULL )
    {
        if ( pMonster->getMid() == 2033 )
        {
            pMonster->SetFamilyId( 0, m_sWinerName );
            m_pMonster = pMonster;
        }
    }
}

void CCrossTower::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
    if ( NULL == pKiller || NULL == pMonster )
    {
        return;
    }

    int32_t nMapId = pKiller->getMapId();
    const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nMapId );
    if ( pCfg == NULL )
    {
        return;
    }

    if ( pCfg->KillCount > pKiller->getRecord( 3 ) )
    {
        pKiller->GetOperateLimit().AddLimitCount( 3, 1 );
        pKiller->SetNeedSyncAround();
        SendPlayerActivityScore( pKiller, getLeftTime() );
    }
}

void CCrossTower::onPlayerRevive( Player* player, bool bSafe )
{
    if ( player != NULL )
    {
        m_NeedSysMap.insert( player->getMapId() );
    }
}

int32_t CCrossTower::onBeginGather( Plant* plant, Player* player )
{
    if ( NULL == plant || NULL == player )
    {
        return 10002;
    }
    if ( player->getRecord( 2110 ) <= 3 )
    {
        return 0;
    }
    return 10002;
}

void CCrossTower::onPlantGather( Plant* pPlant, Player* player )
{
    if ( pPlant != NULL && player != NULL )
    {
        player->GetOperateLimit().AddLimitCount( 2110, 1 );
    }
}

void CCrossTower::broadcastReady()
{
    NetPacket* packet = GAME_SERVICE.popNetpacket( 0, Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( packet != NULL )
    {
        packet->writeInt32( 511 );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.worldBroadcast( 0, packet );
    }
}

void CCrossTower::broadcastStart()
{
    NetPacket* packet = GAME_SERVICE.popNetpacket( 0, Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( packet != NULL )
    {
        packet->writeInt32( 512 );
        packet->writeInt32( GetId() );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.worldBroadcast( 0, packet );
    }
}

void CCrossTower::broadcastActivityResult()
{
    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
    {
        const PlayerScore& score = iter->second;
        if ( !score.bInActivity )
        {
            continue;
        }

        Player* pPlayer = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
        if ( pPlayer == NULL )
        {
            continue;
        }

        NetPacket* packet = GAME_SERVICE.popNetpacket( pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
        if ( packet == NULL )
        {
            return;
        }

        packet->writeInt32( m_cfgActivity.id );
        packet->writeInt32( score.nCurMapId );
        packet->writeUTF8( m_sNewWinerName );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.sendPacketTo( pPlayer->getConnId(), pPlayer->getGateIndex(), packet );
    }
}

void CCrossTower::sendPlayerScore( Player* player )
{
    if ( NULL == player )
    {
        return;
    }

    CharId_t nCid = player->getCid();
    PlayerScoreMap::iterator it = m_mPlayerScore.find( nCid );
    if ( it == m_mPlayerScore.end() )
    {
        return;
    }

    NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
    if ( packet == NULL )
    {
        return;
    }

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt32( it->second.nScore );
    packet->writeInt32( player->getRecord( 3 ) );
    packet->writeInt8( it->second.nIsMoBai );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

int32_t CCrossTower::GiveDailyReward( Player* player )
{
    if ( NULL == player )
    {
        return 10002;
    }

    CharId_t nCid = player->getCid();
    PlayerScoreMap::iterator it = m_mPlayerScore.find( nCid );
    if ( it == m_mPlayerScore.end() )
    {
        return 10002;
    }

    if ( it->second.nIsMoBai > 0 )
    {
        return 10002;
    }

    it->second.nIsMoBai = 1;
    player->AddCurrency( CURRENCY_DUST, 10000, GCR_CROSS_TOWER );
    SendPlayerActivityScore( player, getLeftTime() );
    return 0;
}

void CCrossTower::ActUpdate( int64_t CurTick )
{
    int32_t nNow = TIMER.GetNow();
    m_nLastUpdateTime = CurTick;

    if ( m_nLastAddScoreTime > 0 && nNow - m_nLastAddScoreTime > 19 )
    {
        m_nNeedAddScore = 1;
        m_nLastAddScoreTime = nNow;
        setNeedBroadcastActivityScore();
    }

    if ( m_nState == 1 )
    {
        if ( getLeftTime() > 300 )
        {
            if ( nNow - m_nStateTime > 119 )
            {
                PlayerList tList = m_players;
                for ( PlayerList::iterator iter = tList.begin(); iter != tList.end(); ++iter )
                {
                    if ( *iter != NULL )
                    {
                        (*iter)->setPkMode( 6, false );
                    }
                }
                m_nState = 2;
                m_nStateTime = nNow;
                m_nLastAddScoreTime = nNow;
                setNeedBroadcastActivityScore();
            }
        }
        else
        {
            m_nState = 3;
            m_nLastAddScoreTime = nNow;
            setNeedBroadcastActivityScore();
        }
    }
    else if ( m_nState <= 1 )
    {
        if ( m_nState == 0 )
        {
            m_nState = 1;
            m_nStateTime = nNow;
            setNeedBroadcastActivityScore();
        }
    }
    else if ( m_nState == 2 )
    {
        if ( getLeftTime() <= 300 )
        {
            m_nState = 3;
            setNeedBroadcastActivityScore();
        }
        if ( nNow - m_nStateTime > 59 )
        {
            m_nNeedChangeMap = 1;
            m_nStateTime = nNow;
            setNeedBroadcastActivityScore();
        }
    }
    else if ( m_nState == 3 )
    {
        if ( nNow - m_nStateTime > 59 )
        {
            m_nNeedChangeMap = 1;
            m_nStateTime = nNow;
            setNeedBroadcastActivityScore();
        }
    }
}

int32_t CCrossTower::GetEnterMapId( Player* player )
{
    if ( NULL == player )
    {
        return CActivity::GetEnterMapId( player );
    }

    CharId_t nCid = player->getCid();
    PlayerScoreMap::iterator it = m_mPlayerScore.find( nCid );
    if ( it == m_mPlayerScore.end() )
    {
        return CActivity::GetEnterMapId( player );
    }

    int32_t nCurMapId = it->second.nCurMapId;
    const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nCurMapId );
    if ( pCfg == NULL )
    {
        return CActivity::GetEnterMapId( player );
    }

    if ( pCfg->LastMapId > 0 )
    {
        return pCfg->LastMapId;
    }
    return nCurMapId;
}
