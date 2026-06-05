#include "PeerlessWar.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include "ActivityManager.h"
#include "CfgData.h"
#include "Bag.h"
#include <algorithm>
#include <inttypes.h>

using namespace Answer;

CPeerlessWar::CPeerlessWar( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_nLastTick( 0 )
, m_nWarState( 0 )
, m_nWinner( 0 )
{
}

CPeerlessWar::~CPeerlessWar()
{
	m_mPlayerScore.clear();
}

void CPeerlessWar::Init()
{
	CActivity::Init();

	// Load last winner from database
	MySqlDBGuard db( DBPOOL );
	MySqlQuery result = db.query( "SELECT * FROM `mem_peerless_war` ORDER BY `time` DESC LIMIT 1" );
	while ( !result.eof() )
	{
		m_nWinner = result.getInt64Value( "winner" );
		m_strWinnerName = result.getStringValue( "name" );
		ACTIVITY_MANAGER.SetPeerlessWarWinner( m_nWinner );
		break;
	}
}

void CPeerlessWar::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
	if ( NULL == pMap || !IsRuning() )
	{
		return;
	}

	int64_t curTick = pMap->getTick();
	if ( curTick - m_nLastTick <= 1000 )
	{
		return;
	}
	m_nLastTick = curTick;

	if ( m_nWarState == 1 && getActivityTime() > 299 )
	{
		m_nWarState = 2;
		setNeedBroadcastActivityScore();
		checkWin();
	}

	// Periodic score broadcast
	if ( needBroadcastActivityScore() )
	{
		Answer::NetPacket* packet = packetActivityScore();
		if ( packet != NULL )
		{
			GAME_SERVICE.worldBroadcast( packet );
		}
	}
}

void CPeerlessWar::reset()
{
	CActivity::reset();
	m_nLastTick = 0;
	m_nWarState = 0;
	m_nWinner = 0;
	m_strWinnerName.clear();
	m_mPlayerScore.clear();
}

void CPeerlessWar::SendPlayerActivityInfo( Player* player )
{
	if ( NULL == player ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
	if ( NULL == packet ) return;
	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nWinner );
	packet->writeInt32( getNextStartTime() );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CPeerlessWar::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
	if ( NULL == player ) return;

	int32_t nPersonalScore = 0;
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		nPersonalScore = iter->second.nKillCount;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nWinner );
	packet->writeInt32( nPersonalScore );
	packet->writeInt32( nLeftTime );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

Position CPeerlessWar::GetRandBornPos( Player* player )
{
	if ( NULL != player )
	{
		return getBornRandPosA();
	}
	Position pos( -1, -1 );
	return pos;
}

int32_t CPeerlessWar::GetRevive( Player* player )
{
	return CActivity::GetRevive( player );
}

int32_t CPeerlessWar::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	if ( m_nState != AS_RUNNING )
	{
		return 10002;
	}
	// Check revive limits: if player has used all 3 revives, cannot enter
	if ( NULL != player )
	{
		PlayerScoreMap::const_iterator iter = m_mPlayerScore.find( player->getCid() );
		if ( iter != m_mPlayerScore.end() && iter->second.nReviveTimes >= 3 )
		{
			return 10002;
		}
	}
	return CActivity::canEnter( player, pTargetMap );
}

void CPeerlessWar::SetPeerlessWarWinner( FamilyId_t nFamilyId )
{
	m_nWinner = nFamilyId;
}

FamilyId_t CPeerlessWar::GetPeerlessWarWinner() const
{
	return m_nWinner;
}

void CPeerlessWar::OnPeerlessWarResult( CharId_t nWinnerId, const std::string& winnerName )
{
	m_nState = AS_END;
	m_nWinner = nWinnerId;
	m_strWinnerName = winnerName;
	ACTIVITY_MANAGER.SetPeerlessWarWinner( nWinnerId );
}

int32_t CPeerlessWar::getLeftReviveTimes( Player* player )
{
	if ( NULL == player )
	{
		return 0;
	}
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		return 3 - iter->second.nReviveTimes;
	}
	return 0;
}

void CPeerlessWar::addPlayer( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.bInActivity = true;
	}
	else
	{
		PlayerScore score;
		score.nCharId = player->getCid();
		score.strName = player->getName();
		score.nKillCount = 0;
		score.nReviveTimes = 0;
		score.nContKill = 0;
		score.nBroadCont = 0;
		score.bInActivity = true;
		m_mPlayerScore.insert( PlayerScoreMap::value_type( score.nCharId, score ) );
	}

	CActivity::addPlayer( player );
}

void CPeerlessWar::removePlayer( Player* player, bool islogout )
{
	CActivity::removePlayer( player, islogout );
	if ( NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.bInActivity = false;

		if ( m_nWarState == 2 )
		{
			addJoinReward( player->getCid() );
			sendActivityResult( player );
		}
	}

	checkWin();
}

void CPeerlessWar::onPlayerKilled( Player* pDier, Player* pAttacker )
{
	if ( NULL == pDier || NULL == pAttacker )
	{
		return;
	}

	PlayerScoreMap::iterator dieIter = m_mPlayerScore.find( pDier->getCid() );
	if ( dieIter == m_mPlayerScore.end() )
	{
		return;
	}

	PlayerScore& dieScore = dieIter->second;

	// Broadcast break const kill if needed
	if ( dieScore.nContKill > 0 && dieScore.bInActivity )
	{
		broadcastBreakConst( dieScore.nCharId, dieScore.strName,
			pAttacker->getCid(), pAttacker->getName(),
			dieScore.nContKill );
	}

	// Reset death player kill streak
	dieScore.nContKill = 0;
	dieScore.nBroadCont = 0;
	dieScore.nReviveTimes++;

	// If used all revives, broadcast knockout and force leave
	if ( dieScore.nReviveTimes >= 3 )
	{
		broadcastKnockout( dieScore.nCharId, dieScore.strName );
		pDier->leaveActivity();
	}
	else
	{
		// Revive player
		Position pos = GetRandBornPos( pDier );
		CActivityMap* pMap = dynamic_cast<CActivityMap*>( pDier->getMap() );
		if ( pMap != NULL )
		{
			pDier->switchMap( pMap, pos.x, pos.y, true );
		}
	}	// Add kill to attacker
	addPlayerKillCount( pAttacker, 1 );

	// Check win condition
	checkWin();
}

void CPeerlessWar::onPlayerRevive( Player* player, bool bSafe )
{
	if ( NULL == player )
	{
		return;
	}

	if ( !bSafe )
	{
		// Check if player can still revive
		PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
		if ( iter != m_mPlayerScore.end() && iter->second.nReviveTimes < 3 )
		{
			iter->second.nReviveTimes++;
			Position pos = GetRandBornPos( player );
			CActivityMap* pMap = dynamic_cast<CActivityMap*>( player->getMap() );
			if ( pMap != NULL )
			{
				player->switchMap( pMap, pos.x, pos.y, true );
			}
		}
		else
		{
			player->leaveActivity();
		}
	}
}

void CPeerlessWar::onTimeEnd()
{
	// Determine winner: player with most kills
	CharId_t nWinnerId = 0;
	std::string strWinnerName;
	int32_t nMaxKills = -1;

	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( iter->second.nKillCount > nMaxKills )
		{
			nMaxKills = iter->second.nKillCount;
			nWinnerId = iter->first;
			strWinnerName = iter->second.strName;
		}
	}

	if ( nWinnerId > 0 )
	{
		win( nWinnerId, strWinnerName );
	}
	else
	{
		draw();
	}
}

void CPeerlessWar::addPlayerScore( Player* player, int32_t nScore )
{
	if ( NULL == player ) return;
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.nKillCount += nScore;
		SendPlayerActivityScore( player, getLeftTime() );
	}
}

void CPeerlessWar::addRewards()
{
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		const PlayerScore& score = iter->second;
		if ( !score.bInActivity )
		{
			continue;
		}

		// Skip the winner (already got winner reward)
		if ( iter->first == m_nWinner )
		{
			continue;
		}

		addJoinReward( iter->first );
		sendActivityResult( GAME_SERVICE.getPlayer( iter->first, 0, false ) );
	}
}

void CPeerlessWar::addKillReward( CharId_t nCharId, int32_t nKillCount )
{
	if ( nCharId <= 0 )
	{
		return;
	}

	int32_t nMailId = 0;
	MemChrBag reward;
	memset( &reward, 0, sizeof( reward ) );
	reward.itemId = 1;
	reward.itemClass = IC_NORMAL;
	reward.itemCount = 1;
	reward.bind = IBS_BIND;

	switch ( nKillCount )
	{
	case 3:
		if ( !m_cfgActivity.gift_id.empty() )
		{
			reward.itemId = m_cfgActivity.gift_id[0];
		}
		nMailId = 6256;
		break;
	case 10:
		if ( m_cfgActivity.gift_id.size() > 1 )
		{
			reward.itemId = m_cfgActivity.gift_id[1];
		}
		nMailId = 6256;
		break;
	default:
		return;
	}

	DB_SERVICE.OnSendSysMail( nCharId, nMailId, reward, "" );
}

void CPeerlessWar::addJoinReward( CharId_t nCharId )
{
	if ( nCharId <= 0 )
	{
		return;
	}

	int32_t nMailId = 6211; // MI_FAMILYWAR_REWARD, reuse as participation reward
	MemChrBag reward;
	memset( &reward, 0, sizeof( reward ) );
	reward.itemId = 1;
	reward.itemClass = IC_NORMAL;
	reward.itemCount = 1;
	reward.bind = IBS_BIND;

	if ( !m_cfgActivity.gift_id.empty() )
	{
		reward.itemId = m_cfgActivity.gift_id[0];
	}

	DB_SERVICE.OnSendSysMail( nCharId, nMailId, reward, "" );
}

void CPeerlessWar::addWinnerReward()
{
	if ( m_nWinner <= 0 )
	{
		return;
	}

	int32_t nMailId = 6256; // MI_PEERLESS_WAR_WINNER
	MemChrBag reward;
	memset( &reward, 0, sizeof( reward ) );
	reward.itemId = 1;
	reward.itemClass = IC_NORMAL;
	reward.itemCount = 1;
	reward.bind = IBS_BIND;

	if ( m_cfgActivity.gift_id.size() > 2 )
	{
		reward.itemId = m_cfgActivity.gift_id[2];
	}

	DB_SERVICE.OnSendSysMail( m_nWinner, nMailId, reward, "" );
}

void CPeerlessWar::broadcastResult()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nWinner );

	// Attach top 10 ranking
	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( nCount >= 10 ) break;
		packet->writeInt64( iter->first );
		packet->writeInt32( iter->second.nKillCount );
		++nCount;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::broadcastReady()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 176 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::broadcastStart()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 177 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::broadcastKnockout( CharId_t nCharId, const std::string& name )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 178 );
	packet->writeInt64( nCharId );
	packet->writeUTF8( name );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::broadcastConstKill( CharId_t nCharId, const std::string& name, int32_t nContKill )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 180 );
	packet->writeInt64( nCharId );
	packet->writeUTF8( name );
	packet->writeInt32( nContKill );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::broadcastBreakConst( CharId_t nCharId, const std::string& name, CharId_t nKillerId, const std::string& killerName, int32_t nContKill )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 181 );
	packet->writeInt64( nKillerId );
	packet->writeUTF8( killerName );
	packet->writeInt64( nCharId );
	packet->writeUTF8( name );
	packet->writeInt32( nContKill );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::broadcastDraw()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 179 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CPeerlessWar::checkWin()
{
	if ( m_nState != AS_RUNNING || m_nWarState != 2 )
	{
		return;
	}

	// Count alive players (in activity and with remaining revives)
	int32_t nAliveCount = 0;
	CharId_t nLastAliveId = 0;
	std::string strLastAliveName;

	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( iter->second.bInActivity && iter->second.nReviveTimes < 3 )
		{
			nAliveCount++;
			nLastAliveId = iter->first;
			strLastAliveName = iter->second.strName;
		}
	}

	if ( nAliveCount == 1 )
	{
		win( nLastAliveId, strLastAliveName );
	}
	else if ( nAliveCount <= 0 )
	{
		draw();
	}
}

void CPeerlessWar::win( CharId_t nWinnerId, const std::string& winnerName )
{
	if ( nWinnerId <= 0 )
	{
		return;
	}

	m_nWarState = 2;
	m_nWinner = nWinnerId;
	m_strWinnerName = winnerName;

	clearOldTitle();
	saveWarResult( 1 );
	addWinnerReward();
	addRewards();
	broadcastResult();

	m_nState = AS_END;
	ACTIVITY_MANAGER.SetPeerlessWarWinner( nWinnerId );
	delayKickAll( 10 );
}

void CPeerlessWar::draw()
{
	clearOldTitle();
	m_nWarState = 0;
	m_nWinner = 0;
	m_strWinnerName.clear();

	saveWarResult( 0 );
	addRewards();
	broadcastDraw();

	m_nState = AS_END;
	delayKickAll( 10 );
}

void CPeerlessWar::saveWarResult( int32_t nWinnerType )
{
	int32_t nNow = TIMER.GetNow();
	MySqlDBGuard db( DBPOOL );
	char sql[1024];
	snprintf( sql, sizeof(sql), "INSERT INTO `mem_peerless_war` (id, winner, name, wintype, time) VALUES (%d, %" PRId64 ", '%s', %d, %d)",
		m_cfgActivity.id, m_nWinner, m_strWinnerName.c_str(), nWinnerType, nNow );
	db.excute( sql );
}

void CPeerlessWar::sendPlayerScore( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( getLeftReviveTimes( player ) );

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		packet->writeInt32( iter->second.nKillCount );
	}
	else
	{
		packet->writeInt32( 0 );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

Answer::NetPacket* CPeerlessWar::packetActivityScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.iconid );
	packet->writeInt8( (int8_t)m_nState );

	if ( m_nState == AS_RUNNING )
	{
		packet->writeInt32( getLeftTime() );
	}

	packet->writeInt32( m_nWarState );

	// Count alive players
	int32_t nAliveCount = 0;
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( iter->second.bInActivity && iter->second.nReviveTimes < 3 )
		{
			nAliveCount++;
		}
	}
	packet->writeInt32( nAliveCount );

	packet->setSize( packet->getWOffset() );
	return packet;
}

void CPeerlessWar::sendActivityResult( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nWinner );
	packet->writeInt32( 0 ); // Rank

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		packet->writeInt32( iter->second.nKillCount );
	}
	else
	{
		packet->writeInt32( 0 );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CPeerlessWar::addPlayerKillCount( Player* player, int32_t nKillCount )
{
	if ( NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() )
	{
		return;
	}

	PlayerScore& score = iter->second;
	score.nKillCount += nKillCount;
	score.nContKill += nKillCount;

	if ( score.nContKill >= 3 && score.nContKill > score.nBroadCont )
	{
		score.nBroadCont = score.nContKill;
		broadcastConstKill( score.nCharId, score.strName, score.nContKill );
	}

	// Check kill rewards at milestones
	addKillReward( score.nCharId, score.nKillCount );
}

void CPeerlessWar::clearOldTitle()
{
	// Clear any old winner title - titles are cleared per-player in removePlayer
}
