#include "CampWar.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include "MonsterActivity.h"
#include "PlantActivity.h"
#include "CfgData.h"
#include "Player.h"
#include "Bag.h"
#include <algorithm>
#include <functional>

using namespace Answer;

CCampWar::CCampWar( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_nLastTime( 0 )
, m_Camp_1_battle( 0 )
, m_Camp_2_battle( 0 )
{
}

CCampWar::~CCampWar()
{
	m_BuffIdMap.clear();
	m_sScoreRank.clear();
	m_mPlayerScore.clear();
}

void CCampWar::Init()
{
	CActivity::Init();
}

void CCampWar::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
	if ( NULL == pMap || !IsRuning() )
	{
		return;
	}

	int64_t curTick = pMap->getNow();
	if ( curTick - m_nLastTime <= 299 )
	{
		return;
	}
	m_nLastTime = curTick;

	// Broadcast activity status (ID 421)
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( packet != NULL )
	{
		packet->writeInt32( 421 );
		packet->setSize( packet->getWOffset() );
		worldBroadcast( 0, packet );
		setNeedBroadcastActivityScore();
	}

	// Check for early end if one camp's score is 2x the other
	checkCampWinner();

	// Assign camps based on rank parity
	for ( ScoreRankSet::iterator iter = m_sScoreRank.begin(); iter != m_sScoreRank.end(); ++iter )
	{
		PlayerScore* score = *iter;
		if ( score == NULL || score->nRankIndex == 0 || !score->bInActivity )
		{
			continue;
		}

		if ( (score->nRankIndex & 1) != 0 )
		{
			// Odd rank → camp 2
			score->nCamp = 2;
			Player* pPlayer = GAME_SERVICE.getPlayer( score->nCharId, 0, 0 );
			if ( pPlayer != NULL )
			{
				pPlayer->setPkMode( PK_MODE_LEGION, false );
			}
		}
		else
		{
			// Even rank → camp 1
			score->nCamp = 1;
			Player* pPlayer = GAME_SERVICE.getPlayer( score->nCharId, 0, 0 );
			if ( pPlayer != NULL )
			{
				pPlayer->setPkMode( PK_MODE_ALL, false );
			}
		}
	}
}

void CCampWar::reset()
{
	CActivity::reset();
	m_nLastTime = 0;
	m_BuffIdMap.clear();
	m_mPlayerScore.clear();
	m_sScoreRank.clear();
	m_Camp_1_battle = 0;
	m_Camp_2_battle = 0;
}

bool CCampWar::checkData()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	// Active during first week after server start
	if ( startDays >= 0 && startDays <= 6 )
	{
		return true;
	}
	return CActivity::checkData();
}

bool CCampWar::checkWeek()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( startDays >= 0 && startDays <= 6 )
	{
		return true;
	}
	return CActivity::checkWeek();
}

void CCampWar::SendPlayerActivityInfo( Player* player )
{
	if ( NULL == player ) return;
	NetPacket* packet = popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
	if ( NULL == packet ) return;
	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( getNextStartTime() );
	packet->setSize( packet->getWOffset() );
	sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CCampWar::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
	if ( NULL == player ) return;

	int32_t nPersonalScore = 0;
	int32_t nCampId = 0;
	PlayerScoreMap::iterator scoreIter = m_mPlayerScore.find( player->getCid() );
	if ( scoreIter != m_mPlayerScore.end() )
	{
		nPersonalScore = scoreIter->second.nPoints;
		nCampId = scoreIter->second.nCamp;
	}

	NetPacket* packet = popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt8( (int8_t)nCampId );
	packet->writeInt32( m_Camp_1_battle );
	packet->writeInt32( m_Camp_2_battle );
	packet->writeInt32( nPersonalScore );
	packet->writeInt32( nLeftTime );

	packet->setSize( packet->getWOffset() );
	sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

Position CCampWar::GetRandBornPos( Player* player )
{
	return getBornRandPosA();
}

int32_t CCampWar::GetRevive( Player* player )
{
	return CActivity::GetRevive( player );
}

int32_t CCampWar::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	if ( m_nState != AS_RUNNING )
	{
		return 10002;
	}
	return CActivity::canEnter( player, pTargetMap );
}

void CCampWar::addPlayer( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		// Restore existing player state
		player->setPkMode( PK_MODE_ALL, false );
		iter->second.bInActivity = true;
		iter->second.nAddTime = player->getNow();

		// Re-apply any existing buffs for this player's camp
		for ( std::map<int,int>::iterator it = m_BuffIdMap.begin(); it != m_BuffIdMap.end(); ++it )
		{
			if ( it->second == iter->second.nCamp )
			{
				addActivityBuff( player, it->first, true );
			}
		}
	}
	else
	{
		// New player - initialize score
		PlayerScore score;
		score.nCharId = player->getCid();
		score.strName = player->getName();
		score.nAddTime = player->getNow();
		selectCamp( player, score.nCamp );
		score.bInActivity = true;
		player->setPkMode( PK_MODE_ALL, false );

		m_mPlayerScore[score.nCharId] = score;

		// Update camp battle power
		int32_t nBattle = player->getBattle();
		if ( score.nCamp == 1 )
		{
			m_Camp_1_battle += nBattle;
		}
		else
		{
			m_Camp_2_battle += nBattle;
		}

		// Apply camp buffs
		for ( std::map<int,int>::iterator it = m_BuffIdMap.begin(); it != m_BuffIdMap.end(); ++it )
		{
			if ( it->second == score.nCamp )
			{
				addActivityBuff( player, it->first, true );
			}
		}
	}

	CActivity::addPlayer( player );
}

void CCampWar::removePlayer( Player* player, bool islogout )
{
	CActivity::removePlayer( player, islogout );
	if ( NULL == player )
	{
		return;
	}

	// Reset player's PK mode when leaving the camp war
	player->setPkMode( PK_MODE_FREE, true );

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() )
	{
		return;
	}

	PlayerScore& score = iter->second;
	score.bInActivity = false;

	// Remove from rank set
	PlayerScore* pScore = &score;
	m_sScoreRank.erase( pScore );

	// Deduct 20% of points as penalty
	score.nPoints = (int32_t)(score.nPoints * 0.8);

	// Re-insert into rank set
	m_sScoreRank.insert( pScore );

	refreshRankIndex( score.nCharId );
	setNeedBroadcastActivityScore();
}

void CCampWar::onPlayerKilled( Player* pDier, Player* pAttacker )
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

	// Remove victim from rank set
	PlayerScore* pDieScore = &dieScore;
	m_sScoreRank.erase( pDieScore );

	// Handle contKill broadcast
	if ( dieScore.nContLevel > 0 )
	{
		broadcastBreakContKill( dieScore.strName, dieScore.nCharId,
			pAttacker->getName(), pAttacker->getCid(),
			dieScore.nContKill );
	}

	// Calculate point transfer (20% of victim's points + 5 base)
	int32_t nTransferPoints = (int32_t)(dieScore.nPoints * 0.2) + 5;
	dieScore.nPoints -= (nTransferPoints - 5);

	// Re-insert victim into rank set
	m_sScoreRank.insert( pDieScore );

	// Give points and kill to attacker
	addPlayerScore( pAttacker, nTransferPoints, 1 );
	notifyAddScore( pAttacker, nTransferPoints, 1 );

	// Reset victim's kill streak
	dieScore.nContKill = 0;
	dieScore.nContLevel = 0;

	// Check attacker kill rewards
	PlayerScoreMap::iterator attIter = m_mPlayerScore.find( pAttacker->getCid() );
	if ( attIter != m_mPlayerScore.end() )
	{
		addKillReward( attIter->first, attIter->second.nKillCount );
	}
}

void CCampWar::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
	if ( NULL == pMonster || NULL == pKiller )
	{
		return;
	}

	addPlayerScore( pKiller, 5, 0 );
	notifyAddScore( pKiller, 5, 2 );
}

void CCampWar::onPlayerRevive( Player* player, bool bSafe )
{
	if ( NULL == player )
	{
		return;
	}

	// Re-apply camp buffs on revive
	int32_t nCampId = 0;
	PlayerScoreMap::iterator campIter = m_mPlayerScore.find( player->getCid() );
	if ( campIter != m_mPlayerScore.end() )
	{
		nCampId = campIter->second.nCamp;
	}

	for ( std::map<int,int>::iterator it = m_BuffIdMap.begin(); it != m_BuffIdMap.end(); ++it )
	{
		if ( it->second == nCampId )
		{
			addActivityBuff( player, it->first, true );
		}
	}
}

void CCampWar::onBeginGather( PlantActivity* pPlant, Player* player )
{
	// If plant has a camp owner and player is the same camp, cannot gather
	if ( NULL == pPlant || NULL == player )
	{
		return;
	}

	// Check player's camp
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() )
	{
		return;
	}
	int32_t nPlayerCamp = iter->second.nCamp;

	// Check plant's camp (stored in m_BuffIdMap by onPlantGather)
	if ( nPlayerCamp > 0 && m_BuffIdMap.find( pPlant->getPlantId() ) != m_BuffIdMap.end() )
	{
		return; // Cannot gather own camp's plant
	}
}

void CCampWar::onPlantGather( PlantActivity* pPlant, Player* player )
{
	if ( NULL == pPlant || NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() || iter->second.nCamp <= 0 )
	{
		return;
	}

	int32_t nCamp = iter->second.nCamp;
	int32_t nPoints = 5; // base gather points
	addPlayerScore( player, nPoints, 0 );
	notifyAddScore( player, nPoints, 0 );

	// Broadcast gather event (ID 422)
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 422 );
	packet->writeInt64( player->getCid() );
	packet->writeUTF8( player->getName() );
	packet->writeInt8( (int8_t)nCamp );
	packet->writeInt32( pPlant->getPlantId() );
	packet->setSize( packet->getWOffset() );
	worldBroadcast( 0, packet );
}

void CCampWar::addPlayerScore( Player* player, int32_t nPoint, int32_t nKillCount )
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

	// Remove from rank set
	PlayerScore* pScore = &score;
	m_sScoreRank.erase( pScore );

	score.nPoints += nPoint;

	if ( nKillCount > 0 )
	{
		score.nKillCount += nKillCount;
		score.nContKill += nKillCount;

		// Check contKill title threshold
		if ( score.nContKill >= 3 && score.nContKill > (int32_t)(score.nContLevel > 0 ? 1 : 0) )
		{
			score.nContLevel = score.nContKill;
			int32_t nTitleId = getContTitle( score.nContLevel );
			if ( nTitleId > 0 )
			{
				broadcastContKill( score.nCharId, score.strName, score.nContKill );
			}
		}
	}

	// Re-insert into rank set
	m_sScoreRank.insert( pScore );

	// Update camp scores
	if ( score.nCamp == 1 )
	{
		m_Camp_1_battle += nPoint;
	}
	else
	{
		m_Camp_2_battle += nPoint;
	}

	SendPlayerActivityScore( player, getLeftTime() );

	// Check if any player reached the winning threshold (2000 points)
	if ( score.nPoints > 1999 )
	{
		onWarEnd();
	}
}

void CCampWar::addRewards()
{
	int32_t nWinnerCamp = ( m_Camp_1_battle >= m_Camp_2_battle ) ? 1 : 2;

	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		Player* player = GAME_SERVICE.getPlayer( iter->first, 0, false );
		if ( NULL == player )
		{
			continue;
		}

		// Base reward on points
		int32_t nRewardExp = m_cfgActivity.exp_add_interval > 0 ? ( iter->second.nPoints * m_cfgActivity.exp_add_interval ) : 0;
		int32_t nRewardMoney = iter->second.nPoints * 100;
		if ( nRewardExp > 0 )
		{
			player->addExp( nRewardExp );
		}
		if ( nRewardMoney > 0 )
		{
			player->AddCurrency( CURRENCY_MONEY, nRewardMoney, MCR_MONEY_GAIN_ITEM );
		}

		// Winner camp extra reward
		if ( iter->second.nCamp == nWinnerCamp && !m_cfgActivity.gift_id.empty() )
		{
			MemChrBag bagItem;
			bagItem.itemId		= m_cfgActivity.gift_id[0];
			bagItem.itemClass	= IC_NORMAL;
			bagItem.itemCount	= 1;
			bagItem.bind		= IBS_BIND;
			if ( !player->GetBag().AddItem( bagItem, IACR_ACTIVITY ) )
			{
				DB_SERVICE.OnSendSysMail( player->getCid(), MI_FAMILYWAR_REWARD, bagItem, "" );
			}
		}
	}
}

void CCampWar::addKillReward( CharId_t nCharId, int32_t nKillCount )
{
	if ( nCharId <= 0 )
	{
		return;
	}

	int32_t nMailId = 0;
	MemChrBag reward;
	memset( &reward, 0, sizeof(reward) );
	reward.itemId = 1;
	reward.itemClass = IC_NORMAL;
	reward.itemCount = 1;
	reward.bind = IBS_BIND;

	switch ( nKillCount )
	{
	case 1:
		if ( !m_cfgActivity.gift_id.empty() )
			reward.itemId = m_cfgActivity.gift_id[0];
		nMailId = 6256;
		break;
	case 5:
		if ( m_cfgActivity.gift_id.size() > 1 )
			reward.itemId = m_cfgActivity.gift_id[1];
		nMailId = 6256;
		break;
	case 10:
		if ( m_cfgActivity.gift_id.size() > 2 )
			reward.itemId = m_cfgActivity.gift_id[2];
		nMailId = 6256;
		break;
	case 20:
		if ( m_cfgActivity.gift_id.size() > 3 )
			reward.itemId = m_cfgActivity.gift_id[3];
		nMailId = 6256;
		break;
	case 50:
		if ( m_cfgActivity.gift_id.size() > 4 )
			reward.itemId = m_cfgActivity.gift_id[4];
		nMailId = 6256;
		break;
	default:
		return;
	}

	DB_SERVICE.OnSendSysMail( nCharId, nMailId, reward, "" );
}

void CCampWar::checkCampWinner()
{
	// When one camp's score exceeds 2x the other, end the war
	if ( m_Camp_1_battle > m_Camp_2_battle * 2 || m_Camp_2_battle > m_Camp_1_battle * 2 )
	{
		broadcastCampResult();
	}
}

void CCampWar::broadcastCampResult()
{
	int32_t nWinnerCamp = ( m_Camp_1_battle >= m_Camp_2_battle ) ? 1 : 2;
	std::string strWinnerCampName = ( nWinnerCamp == 1 ) ? "\xe9\x98\xb5\xe8\x90\xa5\xe4\xb8\x80" : "\xe9\x98\xb5\xe8\x90\xa5\xe4\xba\x8c";

	// Build sorted score list
	typedef std::pair<int32_t, PlayerScore*> ScorePair;
	std::vector<ScorePair> vSorted;
	vSorted.reserve( m_sScoreRank.size() );
	for ( ScoreRankSet::iterator it = m_sScoreRank.begin(); it != m_sScoreRank.end(); ++it )
	{
		PlayerScore* pScore = *it;
		if ( pScore != NULL )
		{
			vSorted.push_back( std::make_pair( pScore->nPoints, pScore ) );
		}
	}
	std::sort( vSorted.begin(), vSorted.end(), std::greater<ScorePair>() );

	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( BCI_CAMP_WAR_RESULT );
	packet->writeInt8( (int8_t)nWinnerCamp );
	packet->writeUTF8( strWinnerCampName );
	packet->writeInt32( m_Camp_1_battle );
	packet->writeInt32( m_Camp_2_battle );

	// Top 10 players
	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );
	for ( std::vector<ScorePair>::iterator iter = vSorted.begin(); iter != vSorted.end() && nCount < 10; ++iter )
	{
		PlayerScore* pScore = iter->second;
		if ( pScore == NULL ) continue;
		packet->writeUTF8( pScore->strName );
		packet->writeInt8( (int8_t)pScore->nCamp );
		packet->writeInt32( pScore->nPoints );
		++nCount;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	worldBroadcast( 0, packet );
}

void CCampWar::broadcastReady()
{
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 99 );
	packet->setSize( packet->getWOffset() );
	worldBroadcast( 0, packet );
}

void CCampWar::broadcastStart()
{
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 100 );
	packet->setSize( packet->getWOffset() );
	worldBroadcast( 0, packet );
}

void CCampWar::broadcastContKill( CharId_t nCharId, const std::string& name, int32_t nContKill )
{
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 97 );
	packet->writeUTF8( name );
	packet->writeInt32( nContKill );
	packet->setSize( packet->getWOffset() );
	worldBroadcast( 0, packet );
}

void CCampWar::broadcastBreakContKill( const std::string& victimName, CharId_t nVictimId,
	const std::string& killerName, CharId_t nKillerId, int32_t nContKill )
{
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 98 );
	packet->writeUTF8( victimName );
	packet->writeInt64( nVictimId );
	packet->writeUTF8( killerName );
	packet->writeInt64( nKillerId );
	packet->writeInt32( nContKill );
	packet->setSize( packet->getWOffset() );
	worldBroadcast( 0, packet );
}

void CCampWar::RefreshBuff( int32_t nBuffId, int8_t nCampId )
{
	for ( PlayerList::iterator iter = m_players.begin(); iter != m_players.end(); ++iter )
	{
		Player* player = *iter;
		if ( player == NULL ) continue;

		PlayerScoreMap::iterator campIter = m_mPlayerScore.find( player->getCid() );
		if ( campIter == m_mPlayerScore.end() ) continue;

		if ( campIter->second.nCamp == nCampId )
		{
			addActivityBuff( player, nBuffId, true );
		}
		else
		{
			player->removeBuff( nBuffId );
		}
	}
}

void CCampWar::selectCamp( Player* player, int32_t& nCamp )
{
	// Alternate camps based on player count
	int32_t nCamp1Count = 0;
	int32_t nCamp2Count = 0;
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( iter->second.nCamp == 1 ) nCamp1Count++;
		else nCamp2Count++;
	}
	nCamp = ( nCamp1Count <= nCamp2Count ) ? 1 : 2;
}

int32_t CCampWar::getContTitle( int32_t nContLevel )
{
	// Return title ID based on consecutive kill count
	if ( nContLevel >= 10 ) return 5;
	if ( nContLevel >= 7 ) return 4;
	if ( nContLevel >= 5 ) return 3;
	if ( nContLevel >= 3 ) return 2;
	return 1;
}

void CCampWar::notifyAddScore( Player* player, int32_t nPoint, int32_t nType )
{
	if ( NULL == player ) return;

	NetPacket* packet = popNetpacket( player->getConnId(), PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 423 );
	packet->writeInt64( player->getCid() );
	packet->writeInt8( (int8_t)nType );
	packet->writeInt32( nPoint );
	packet->setSize( packet->getWOffset() );
	sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CCampWar::refreshRankIndex( CharId_t nCharId )
{
	int32_t nIndex = 0;
	for ( ScoreRankSet::iterator iter = m_sScoreRank.begin(); iter != m_sScoreRank.end(); ++iter )
	{
		PlayerScore* pScore = *iter;
		if ( pScore == NULL ) continue;
		pScore->nRankIndex = ++nIndex;
	}
}

void CCampWar::sendPlayerScore( Player* player )
{
	if ( NULL == player ) return;

	int32_t nScore = 0;
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		nScore = iter->second.nPoints;
	}

	NetPacket* packet = popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet ) return;
	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( nScore );
	packet->writeInt32( getLeftTime() );
	packet->setSize( packet->getWOffset() );
	sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

void CCampWar::SendPlayerRankInfo( Player* player )
{
	if ( NULL == player ) return;

	int32_t nRank = 0;
	int32_t nScore = 0;
	for ( ScoreRankSet::iterator iter = m_sScoreRank.begin(); iter != m_sScoreRank.end(); ++iter )
	{
		PlayerScore* pScore = *iter;
		if ( pScore == NULL ) continue;
		++nRank;
		if ( pScore->nCharId == player->getCid() )
		{
			nScore = pScore->nPoints;
			break;
		}
	}

	NetPacket* packet = popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
	if ( NULL == packet ) return;
	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( nRank );
	packet->writeInt32( nScore );
	packet->setSize( packet->getWOffset() );
	sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

Answer::NetPacket* CCampWar::packetActivityScore()
{
	NetPacket* packet = popNetpacket( 0, PACK_DISPATCH, SM_SEND_ONE_ICON );
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

	packet->writeInt32( m_Camp_1_battle );
	packet->writeInt32( m_Camp_2_battle );

	packet->setSize( packet->getWOffset() );
	return packet;
}

void CCampWar::onTimeEnd()
{
	broadcastCampResult();
	addRewards();
	broadcastActivityResult();

	CActivity::onTimeEnd();
}

void CCampWar::onWarEnd()
{
	// Called when a player reaches the winning score threshold
	addRewards();
	m_nState = AS_END;
	delayKickAll( 0 );
	broadcastActivityResult();
}

void CCampWar::broadcastActivityResult()
{
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		PlayerScore& score = iter->second;
		if ( !score.bInActivity )
		{
			continue;
		}

		Player* player = GAME_SERVICE.getPlayer( score.nCharId, 0, 0 );
		if ( NULL == player )
		{
			continue;
		}

		NetPacket* packet = popNetpacket( player->getConnId(), PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
		if ( NULL == packet ) return;

		packet->writeInt32( m_cfgActivity.id );
		packet->writeInt32( score.nRankIndex );
		packet->writeInt32( score.nKillCount );
		packet->setSize( packet->getWOffset() );
		sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
	}
}
