#include "CrossTower.h"
#include "GameService.h"
#include "DBService.h"
#include "ActivityManager.h"
#include "ActivityMap.h"
#include "Timer.h"
#include "MapManager.h"
#include "Map.h"
#include "Monster.h"
#include <algorithm>
#include <cmath>

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

    // 从数据库加载跨服塔胜者信息
    MySqlDBGuard db( DBPOOL );
    MySqlQuery result = db.query( "SELECT * FROM `mem_cross_tower` WHERE id=1" );
    if ( !result.eof() )
    {
        m_nWinerId    = result.getIntValue( "winner" );
        m_sWinerName  = result.getStringValue( "name" );
        m_nBattle     = result.getIntValue( "battle" );
        m_nConnId     = (int8_t)result.getIntValue( "connid" );
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

    NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
    if ( NULL == packet ) return;

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt64( m_nWinerId );
    packet->writeInt32( getNextStartTime() );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
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

    NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
    if ( NULL == packet ) return;

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt64( m_nWinerId );
    packet->writeInt32( nPersonalScore );
    packet->writeInt32( nLeftTime );
    packet->writeInt32( m_nBattle );

    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

Position CCrossTower::GetRandBornPos( Player* player )
{
    return getBornRandPosA();
}

int32_t CCrossTower::GetRevive( Player* player )
{
    return CActivity::GetRevive( player );
}

void CCrossTower::SetWinnerInfo( CharId_t nWinnerId, const std::string& sName )
{
    m_nWinerId = nWinnerId;
    m_sWinerName = sName;

    if ( m_pMonster != NULL )
    {
        if ( m_pMonster != NULL )
        {
            m_pMonster->SetFamilyId( 0 );
        }
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

    NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
    if ( packet != NULL )
    {
        packet->writeInt32( m_cfgActivity.id );
        packet->writeInt32( GetId() );
        packet->setSize( packet->getWOffset() );
        GAME_SERVICE.worldBroadcast( packet );
    }

    CActivity::onTimeEnd();
}

void CCrossTower::addRewards()
{
    // 通知 ActivityManager
    ACTIVITY_MANAGER.SetCrossTowerResult( m_nNewWinerId, m_nBattle, m_sNewWinerName );

    // 发放邮件奖励
    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
    {
        const PlayerScore& score = iter->second;
        int32_t nCurMapId = score.nCurMapId;
        const CrossTowerCfg* pCfg = CFG_DATA.GetCrossTowerCfg( nCurMapId );
        if ( pCfg != NULL && score.bInActivity )
        {
            DB_SERVICE.OnSendSysMail( score.nCharId, pCfg->nMailId, pCfg->RewardVt, "" );
        }
    }

    // 清理排行数据
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
    bool bHasActivePlayer = false;
    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
    {
        if ( iter->second.bInActivity )
        {
            bHasActivePlayer = true;
            break;
        }
    }

    if ( !bHasActivePlayer && !bForce )
    {
        return;
    }

    CharId_t nWinnerId = 0;
    std::string sWinnerName;
    int32_t nMaxScore = 0;
    int32_t nBattle = 0;

    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
    {
        if ( iter->second.nScore > nMaxScore )
        {
            nMaxScore = iter->second.nScore;
            nWinnerId = iter->first;
        }
    }

    if ( nWinnerId > 0 )
    {
        Player* pWinner = GAME_SERVICE.getPlayer( nWinnerId, 0, false );
        if ( pWinner != NULL )
        {
            sWinnerName = pWinner->getName();
            nBattle = pWinner->getBattle();
        }
    }

    m_nNewWinerId   = nWinnerId;
    m_sNewWinerName = sWinnerName;
    m_nBattle       = nBattle;
}

Answer::NetPacket* CCrossTower::packetActivityMapInfo( CActivityMap* pMap )
{
    if ( NULL == pMap ) return NULL;

    NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
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

Answer::NetPacket* CCrossTower::packetActivityScore()
{
    NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
    if ( NULL == packet ) return NULL;

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt64( m_nWinerId );
    packet->writeInt32( m_nBattle );

    int32_t nCount = 0;
    uint32_t nCountPos = packet->getWOffset();
    packet->writeInt16( 0 );

    for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
    {
        Player* player = GAME_SERVICE.getPlayer( iter->first, 0, false );
        if ( NULL == player ) continue;

        packet->writeInt64( iter->first );
        packet->writeInt32( iter->second.nScore );
        ++nCount;
    }

    uint32_t nEndPos = packet->getWOffset();
    packet->setWOffset( nCountPos );
    packet->writeInt16( (int16_t)nCount );
    packet->setWOffset( nEndPos );

    packet->setSize( nEndPos );
    return packet;
}
