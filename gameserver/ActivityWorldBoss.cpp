#include "ActivityWorldBoss.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include <algorithm>
#include <functional>

using namespace Answer;

CActivityWorldBoss::CActivityWorldBoss( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_IsBossDie( false )
{
}

CActivityWorldBoss::~CActivityWorldBoss()
{
	m_sScoreRank.clear();
	m_mPlayerScore.clear();
	m_ReviveTimes.clear();
}

void CActivityWorldBoss::Init()
{
	CActivity::Init();
}

void CActivityWorldBoss::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
}

void CActivityWorldBoss::reset()
{
	CActivity::reset();
	m_mPlayerScore.clear();
	m_sScoreRank.clear();
	m_ReviveTimes.clear();
	m_IsBossDie = false;
}

int32_t CActivityWorldBoss::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	return CActivity::canEnter( player, pTargetMap );
}

void CActivityWorldBoss::SendPlayerActivityInfo( Player* player )
{
	if ( NULL == player ) return;
	NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
	if ( NULL == packet ) return;
	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( getLeftTime() );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CActivityWorldBoss::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
	if ( NULL == player ) return;

	int32_t nDamage = 0;
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		nDamage = iter->second.nDamage;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( nDamage );
	packet->writeInt32( nLeftTime );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

int32_t CActivityWorldBoss::GetRevive( Player* player )
{
	return CActivity::GetRevive( player );
}

Position CActivityWorldBoss::GetRandBornPos( Player* player )
{
	return getBornRandPosA();
}

bool CActivityWorldBoss::OnSitRevive( Player* player )
{
	return player != NULL;
}

void CActivityWorldBoss::onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, Player* pAttacker )
{
	if ( NULL == pMonster || NULL == pAttacker )
	{
		return;
	}
	// Binary checks boss sign == 4; use isBoss check
	if ( pMonster->isBoss() )
	{
		addPlayerScore( pAttacker, nDamage );
		sendPlayerScore( pAttacker );
	}
}

void CActivityWorldBoss::onPlayerKilled( Player* pDier, Player* pKiller )
{
	if ( NULL == pDier || m_nState == AS_END )
	{
		return;
	}

	// Increment revive count
	++m_ReviveTimes[pDier->getCid()];

	if ( NULL != pKiller )
	{
		// Transfer 20% of victim's damage to killer
		int32_t Score = 0;
		PlayerScoreMap::iterator dieIter = m_mPlayerScore.find( pDier->getCid() );
		if ( dieIter != m_mPlayerScore.end() )
		{
			Score = 20 * dieIter->second.nDamage / 100;
			if ( Score > 0 )
			{
				dieIter->second.nDamage -= Score;
			}
		}

		if ( Score > 0 )
		{
			PlayerScoreMap::iterator attIter = m_mPlayerScore.find( pKiller->getCid() );
			if ( attIter != m_mPlayerScore.end() )
			{
				attIter->second.nDamage += Score;
			}
		}

		refreshRank();
		setNeedBroadcastActivityScore();
		sendPlayerScore( pDier );
		sendPlayerScore( pKiller );
	}
	else
	{
		sendPlayerScore( pDier );
	}
}

void CActivityWorldBoss::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
	if ( NULL == pMonster || NULL == pKiller || !IsRuning() )
	{
		return;
	}
	// Binary checks boss sign == 4; use isBoss check
	if ( !pMonster->isBoss() )
	{
		return;
	}

	m_IsBossDie = true;

	const PlayerScore* FirstPlayer = getRankFirst();
	if ( FirstPlayer != NULL )
	{
		broadcastBossKilled( FirstPlayer->strName, FirstPlayer->nCharId );

		// Send kill mail reward to rank 1 player
		if ( m_cfgActivity.gift_id.size() > 5 )
		{
			MemChrBag bagItem;
			memset( &bagItem, 0, sizeof(bagItem) );
			bagItem.itemId		= m_cfgActivity.gift_id[5];
			bagItem.itemClass	= IC_NORMAL;
			bagItem.itemCount	= 1;
			bagItem.bind		= IBS_BIND;

			DB_SERVICE.OnSendSysMail( FirstPlayer->nCharId, 6505, bagItem, "" );
		}
	}
}

void CActivityWorldBoss::onMonsterAdd( MonsterActivity* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}
	// Binary checks boss sign == 1 (first boss add); check isBoss
	if ( pMonster->isBoss() )
	{
		setNeedBroadcastActivityScore();
	}
}

void CActivityWorldBoss::addPlayer( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		// Restore existing player
		iter->second.bInActivity = true;
		iter->second.nStartTick = player->getTick();
	}
	else
	{
		// New player
		PlayerScore score;
		score.nCharId = player->getCid();
		score.strName = player->getName();
		score.bInActivity = true;
		score.nStartTick = player->getTick();

		m_mPlayerScore[score.nCharId] = score;
		m_ReviveTimes[player->getCid()] = 0;
	}

	CActivity::addPlayer( player );
}

void CActivityWorldBoss::removePlayer( Player* player, bool islogout )
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
	}
}

void CActivityWorldBoss::addPlayerScore( Player* player, int32_t nDamage )
{
	if ( m_nState == AS_END || NULL == player )
	{
		return;
	}

	// Convert damage to score: 1 for <=100000, else damage/100000
	int32_t Score = 0;
	if ( nDamage <= 100000 )
	{
		Score = 1;
	}
	else
	{
		Score = nDamage / 100000;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.nDamage += Score;
		iter->second.nStartTick = player->getTick();
		setNeedBroadcastActivityScore();
		refreshRank();
	}
}

void CActivityWorldBoss::sendPlayerScore( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	int32_t DieTimes = 0;
	std::map<CharId_t, int32_t>::iterator reviveIter = m_ReviveTimes.find( player->getCid() );
	if ( reviveIter != m_ReviveTimes.end() )
	{
		DieTimes = reviveIter->second;
	}

	PlayerScoreMap::iterator scoreIter = m_mPlayerScore.find( player->getCid() );
	if ( scoreIter == m_mPlayerScore.end() )
	{
		return;
	}

	const PlayerScore& score = scoreIter->second;

	NetPacket* packet = GAME_SERVICE.popNetpacket( player->getConnId(), PACK_DISPATCH, 0x2E24 );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( score.nIndex );
	packet->writeInt32( score.nDamage );
	packet->writeInt32( DieTimes );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CActivityWorldBoss::addRewards()
{
	refreshRank();

	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		const PlayerScore& score = iter->second;
		int32_t nGiftId = 0;
		int32_t nMailId = 0;

		// Binary: rank <= 10 || bInActivity players get rewards
		if ( score.nIndex > 10 && !score.bInActivity )
		{
			continue;
		}

		if ( score.nDamage > 0 )
		{
			if ( score.nIndex <= 0 )
			{
				continue;
			}
			if ( score.nIndex == 1 )
			{
				// Rank 1
				if ( m_cfgActivity.gift_id.size() > 1 )
					nGiftId = m_cfgActivity.gift_id[1];
				nMailId = 6502;
			}
			else if ( score.nIndex <= 3 )
			{
				// Rank 2-3
				if ( m_cfgActivity.gift_id.size() > 2 )
					nGiftId = m_cfgActivity.gift_id[2];
				nMailId = 6503;
			}
			else if ( score.nIndex <= 10 )
			{
				// Rank 4-10
				if ( m_cfgActivity.gift_id.size() > 3 )
					nGiftId = m_cfgActivity.gift_id[3];
				nMailId = 6504;
			}
			else
			{
				// Rank > 10 but bInActivity
				if ( m_cfgActivity.gift_id.size() > 4 )
					nGiftId = m_cfgActivity.gift_id[4];
				nMailId = 6501;
			}
		}
		else
		{
			// No damage
			if ( !m_cfgActivity.gift_id.empty() )
				nGiftId = m_cfgActivity.gift_id[0];
			nMailId = 6501;
		}

		if ( nGiftId > 0 )
		{
			MemChrBag bagItem;
			memset( &bagItem, 0, sizeof(bagItem) );
			bagItem.itemId		= nGiftId;
			bagItem.itemClass	= IC_NORMAL;
			bagItem.itemCount	= 1;
			bagItem.bind		= IBS_BIND;

			DB_SERVICE.OnSendSysMail( score.nCharId, nMailId, bagItem, "" );
		}
	}
}

void CActivityWorldBoss::onTimeEnd()
{
	addRewards();
	broadcastActivityResult();
	broadcastEnd();
	m_nState = AS_END;
	delayKickAll( 30 );
}

Answer::NetPacket* CActivityWorldBoss::packetActivityScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2E26 );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( getLeftTime() );

	// Top 20 players (int16 count-prefix format)
	int16_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt16( nCount );

	for ( ScoreRankSet::iterator iter = m_sScoreRank.begin(); iter != m_sScoreRank.end(); ++iter )
	{
		PlayerScore* pScore = *iter;
		if ( pScore == NULL ) continue;

		packet->writeInt16( (int16_t)pScore->nIndex );
		packet->writeUTF8( pScore->strName );
		packet->writeInt32( pScore->nDamage );

		if ( ++nCount > 19 ) break;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->writeInt8( m_IsBossDie ? 1 : 0 );
	packet->setSize( packet->getWOffset() );
	return packet;
}

void CActivityWorldBoss::broadcastStart()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet ) return;

	packet->writeInt32( 323 );
	packet->writeInt32( m_cfgActivity.id );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CActivityWorldBoss::broadcastEnd()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet ) return;

	packet->writeInt32( 325 );
	packet->writeInt32( m_cfgActivity.id );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CActivityWorldBoss::broadcastActivityResult()
{
	for ( std::list<CActivityMap*>::iterator iter = m_activityMaps.begin(); iter != m_activityMaps.end(); ++iter )
	{
		CActivityMap* pMap = *iter;
		if ( NULL == pMap ) continue;

		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2E27 );
		if ( NULL == packet ) return;

		packet->writeInt32( m_cfgActivity.id );
		packet->writeInt8( m_IsBossDie ? 1 : 0 );
		packet->setSize( packet->getWOffset() );
		pMap->broadcast( packet );
	}
}

void CActivityWorldBoss::broadcastBossKilled( const std::string& name, CharId_t cid )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet ) return;

	packet->writeInt32( 324 );
	packet->writeUTF8( name );
	packet->writeInt64( cid );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CActivityWorldBoss::refreshRank()
{
	m_sScoreRank.clear();

	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( iter->second.nDamage > 0 )
		{
			m_sScoreRank.insert( &iter->second );
		}
	}

	int32_t nIndex = 1;
	for ( ScoreRankSet::iterator iter = m_sScoreRank.begin(); iter != m_sScoreRank.end(); ++iter )
	{
		PlayerScore* pScore = *iter;
		if ( pScore == NULL ) continue;

		if ( pScore->nIndex != nIndex )
		{
			pScore->nIndex = nIndex;
			if ( pScore->bInActivity )
			{
				Player* pPlayer = GAME_SERVICE.getPlayer( pScore->nCharId, 0, 0 );
				if ( pPlayer != NULL )
				{
					sendPlayerScore( pPlayer );
				}
			}
		}
		++nIndex;
	}
}

int32_t CActivityWorldBoss::getAutoReviveTime( Player* player )
{
	if ( NULL == player )
	{
		return 10000;
	}

	int32_t Time = 0;
	std::map<CharId_t, int32_t>::iterator iter = m_ReviveTimes.find( player->getCid() );
	if ( iter != m_ReviveTimes.end() )
	{
		Time = iter->second;
	}

	if ( 5 * Time <= 30 )
	{
		return 5000 * Time;
	}
	return 30000;
}

const CActivityWorldBoss::PlayerScore* CActivityWorldBoss::getRankFirst() const
{
	if ( m_sScoreRank.empty() )
	{
		return NULL;
	}
	return *m_sScoreRank.begin();
}
