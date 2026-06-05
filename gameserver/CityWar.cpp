#include <inttypes.h>
#include <functional>
#include "CityWar.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include "FamilyManager.h"
#include "ActivityManager.h"
#include "Monster.h"
#include <algorithm>
#include <sstream>

using namespace Answer;

struct FamilyScoreRankGreater
{
	bool operator()( const CityWarFamilyScore* left, const CityWarFamilyScore* right ) const
	{
		if ( left == NULL || right == NULL ) return false;
		if ( left->nScore != right->nScore )
			return left->nScore > right->nScore;
		return left->nScoreTime < right->nScoreTime;
	}
};

CCityWar::CCityWar( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_pMonster( NULL )
, m_nIndex( 0 )
, m_nFamilyId( 0 )
, m_nLastFamilyId( 0 )
, m_nWinTime( 0 )
, m_Leader( 0 )
, m_bUpdateFamilyScroe( false )
, m_nLastUpdateRankTick( 0 )
, m_First( 0 )
, m_Second( 0 )
, m_Third( 0 )
, m_FirstTime( 0 )
, m_SecondTime( 0 )
, m_ThirdTime( 0 )
{
}

CCityWar::~CCityWar()
{
	m_mFamilyScore.clear();
	m_mPlayerScore.clear();
	m_lFamilyScore.clear();
	m_Apply.clear();
}

void CCityWar::Init()
{
	CActivity::Init();

	MySqlDBGuard db( DBPOOL );
	MySqlQuery result = db.query( "SELECT * FROM `mem_city_war` ORDER BY `index` DESC LIMIT 1" );
	while ( !result.eof() )
	{
		m_nIndex = result.getIntValue( "index" );
		m_nFamilyId = result.getInt64Value( "familyid" );
		m_Leader = result.getInt64Value( "leader" );
		m_nWinTime = result.getIntValue( "time" );
		m_FirstFamilyName = result.getStringValue( "firstname" );
		m_SecondFamilyName = result.getStringValue( "secondname" );
		m_ThirdFamilyName = result.getStringValue( "thirdname" );
		m_First = result.getIntValue( "firstscore" );
		m_Second = result.getIntValue( "secondscore" );
		m_Third = result.getIntValue( "thirdscore" );
		ACTIVITY_MANAGER.SetCityWarWinner( m_nFamilyId );
		break;
	}

	// Load apply info
	char applySql[256];
	snprintf( applySql, sizeof(applySql), "SELECT * FROM `mem_city_war_apply` WHERE `index`=%d", m_nIndex + 1 );
	MySqlQuery applyResult = db.query( applySql );
	while ( !applyResult.eof() )
	{
		std::string strApplyInfo = applyResult.getStringValue( "applyinfo" );

		// Parse applyinfo: format "familyid1:applytype1|familyid2:applytype2|..."
		std::istringstream iss( strApplyInfo );
		std::string token;
		while ( std::getline( iss, token, '|' ) )
		{
			size_t pos = token.find( ':' );
			if ( pos != std::string::npos )
			{
				FamilyId_t nFamilyId = atoll( token.substr( 0, pos ).c_str() );
				int32_t nApplyType = atoi( token.substr( pos + 1 ).c_str() );
				m_Apply[nFamilyId].nFamilyId = nFamilyId;
				m_Apply[nFamilyId].nMemberCount = nApplyType;
			}
		}
		applyResult.nextRow();
	}
}

void CCityWar::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
	if ( NULL == pMap || !IsRuning() )
	{
		return;
	}

	int64_t curTick = pMap->getTick();
	if ( curTick - m_nLastUpdateRankTick < 1000 )
	{
		return;
	}
	m_nLastUpdateRankTick = curTick;

	// Check family change
	checkChangeFamily( true );

	// Sort family scores and update rank
	if ( !m_lFamilyScore.empty() )
	{
		m_lFamilyScore.sort( FamilyScoreRankGreater() );
		setNeedBroadcastActivityScore();
	}
}

void CCityWar::reset()
{
	CActivity::reset();
	m_mFamilyScore.clear();
	m_mPlayerScore.clear();
	m_lFamilyScore.clear();
	m_Apply.clear();
	m_pMonster = NULL;
	m_nIndex = 0;
	m_nFamilyId = 0;
	m_nLastFamilyId = 0;
	m_nWinTime = 0;
	m_Leader = 0;
	m_bUpdateFamilyScroe = false;
	m_nLastUpdateRankTick = 0;
	m_First = 0;
	m_Second = 0;
	m_Third = 0;
	m_FirstTime = 0;
	m_SecondTime = 0;
	m_ThirdTime = 0;
	m_FirstFamilyName.clear();
	m_SecondFamilyName.clear();
	m_ThirdFamilyName.clear();
}

bool CCityWar::isSpecialDay( int32_t nStartDays )
{
	return nStartDays == 2;
}

bool CCityWar::isInSpecialDay( int32_t nStartDays )
{
	return nStartDays <= 2;
}

bool CCityWar::checkData()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( isSpecialDay( startDays ) )
	{
		return true;
	}
	if ( isInSpecialDay( startDays ) )
	{
		return false;
	}
	return CActivity::checkData();
}

bool CCityWar::checkWeek()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( isSpecialDay( startDays ) )
	{
		return true;
	}
	if ( isInSpecialDay( startDays ) )
	{
		return false;
	}
	return CActivity::checkWeek();
}

bool CCityWar::HaveOwner()
{
	for ( PlayerList::iterator iter = m_players.begin(); iter != m_players.end(); ++iter )
	{
		Player* player = *iter;
		if ( player != NULL && !player->IsDead() && player->getMapId() == 50130 )
		{
			CityWarPlayerScoreMap::iterator scoreIter = m_mPlayerScore.find( player->getCid() );
			if ( scoreIter != m_mPlayerScore.end() && scoreIter->second.nFamilyId == m_nFamilyId )
			{
				return true;
			}
		}
	}
	return false;
}

void CCityWar::SetOwner()
{
	for ( PlayerList::iterator iter = m_players.begin(); iter != m_players.end(); ++iter )
	{
		Player* player = *iter;
		if ( player != NULL )
		{
			CityWarPlayerScoreMap::iterator scoreIter = m_mPlayerScore.find( player->getCid() );
			if ( scoreIter != m_mPlayerScore.end() )
			{
				if ( scoreIter->second.nFamilyId == m_nFamilyId )
				{
					player->setPkMode( PK_MODE_LEGION, false );
				}
				else
				{
					player->setPkMode( PK_MODE_ALL, false );
				}
			}
		}
	}
}

void CCityWar::checkChangeFamily( bool bUpdateScore )
{
	if ( m_nFamilyId <= 0 )
	{
		// No current owner - find one
		if ( !m_lFamilyScore.empty() )
		{
			m_lFamilyScore.sort( FamilyScoreRankGreater() );
			CityWarFamilyScore* pTop = m_lFamilyScore.front();
			if ( pTop != NULL && pTop->nCamp == 2 && pTop->nFamilyId != m_nFamilyId )
			{
				m_nLastFamilyId = m_nFamilyId;
				m_nFamilyId = pTop->nFamilyId;
				SetOwner();
				setNeedBroadcastActivityScore();
			}
		}
		return;
	}

	if ( !HaveOwner() )
	{
		if ( m_nFamilyId > 0 && !m_Apply.empty() )
		{
			NotOccupyGongGao();
		}
		m_nLastFamilyId = m_nFamilyId;
		m_nFamilyId = 0;
		SetOwner();
		setNeedBroadcastActivityScore();
	}
}

void CCityWar::NotOccupyGongGao()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 342 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

FamilyId_t CCityWar::GetGuilDerFirstFamily()
{
	if ( m_lFamilyScore.empty() )
	{
		return 0;
	}	m_lFamilyScore.sort( FamilyScoreRankGreater() );

	for ( CityWarFamilyScorePtrList::iterator iter = m_lFamilyScore.begin(); iter != m_lFamilyScore.end(); ++iter )
	{
		CityWarFamilyScore* pScore = *iter;
		if ( pScore != NULL && pScore->nCamp == 2 )
		{
			return pScore->nFamilyId;
		}
	}
	return 0;
}

int8_t CCityWar::GetFamilyCamp( FamilyId_t nFamilyId )
{
	if ( nFamilyId == m_nFamilyId )
	{
		return 1;
	}

	if ( m_Apply.find( nFamilyId ) != m_Apply.end() )
	{
		return 2;
	}

	if ( m_nFamilyId == 0 )
	{
		if ( nFamilyId == m_nLastFamilyId )
		{
			return 1;
		}
		return 2;
	}

	return 4;
}

void CCityWar::SendPlayerActivityInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nFamilyId );
	packet->writeInt64( m_Leader );
	packet->writeInt32( m_nIndex );
	packet->writeInt32( m_nWinTime );
	packet->writeInt32( m_First );
	packet->writeUTF8( m_FirstFamilyName );
	packet->writeInt32( m_Second );
	packet->writeUTF8( m_SecondFamilyName );
	packet->writeInt32( m_Third );
	packet->writeUTF8( m_ThirdFamilyName );
	packet->writeInt32( getNextStartTime() );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CCityWar::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nFamilyId );
	packet->writeInt32( nLeftTime );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );

	NetPacket* familyPacket = packetActivityFamilyScore();
	if ( familyPacket != NULL )
	{
		GAME_SERVICE.sendPacketTo( player->getGateIndex(), familyPacket );
	}

	NetPacket* playerPacket = packetActivityPlayerScore( player );
	if ( playerPacket != NULL )
	{
		GAME_SERVICE.sendPacketTo( player->getGateIndex(), playerPacket );
	}
}

Position CCityWar::GetRandBornPos( Player* player )
{
	return getBornRandPosA();
}

bool CCityWar::OnSitRevive( Player* player )
{
	return false;
}

int32_t CCityWar::GetRevive( Player* player )
{
	return CActivity::GetRevive( player );
}

int32_t CCityWar::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	if ( m_nState != AS_RUNNING )
	{
		return 10002;
	}

	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	// Check if player's family has applied
	FamilyId_t nFamilyId = player->getFamilyId();
	if ( nFamilyId <= 0 )
	{
		return 10002;
	}

	if ( m_Apply.find( nFamilyId ) == m_Apply.end() && nFamilyId != m_nFamilyId )
	{
		return 10002;
	}

	return CActivity::canEnter( player, pTargetMap );
}

void CCityWar::GetFamilyMembers( FamilyId_t nFamilyId, CharIdList& cids )
{
	for ( CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		if ( iter->second.nFamilyId == nFamilyId && iter->second.bInActivity )
		{
			cids.push_back( iter->first );
		}
	}
}

void CCityWar::OnCityWarResult( FamilyId_t nWinnerId, const std::string& winnerName )
{
	m_nFamilyId = nWinnerId;
	m_nWinTime = TIMER.GetNow();
	saveResult();
	broadcastRankInfo();
}

bool CCityWar::ApplyCityWar( Player* player )
{
	if ( NULL == player )
	{
		return false;
	}

	FamilyId_t nFamilyId = player->getFamilyId();
	if ( nFamilyId <= 0 )
	{
		return false;
	}

	if ( m_Apply.find( nFamilyId ) != m_Apply.end() )
	{
		return false; // Already applied
	}

	CityWarApply apply;
	apply.nFamilyId = nFamilyId;
	apply.strLeaderName = player->getName();
	apply.nMemberCount = 0;

	m_Apply[nFamilyId] = apply;
	SaveApplyInfo();
	GongGao( 341 );

	return true;
}

void CCityWar::SendAppyCityWarInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt8( (int8_t)m_Apply.size() );

	for ( CityWarApplyMap::iterator iter = m_Apply.begin(); iter != m_Apply.end(); ++iter )
	{
		packet->writeInt64( iter->first );
		packet->writeUTF8( iter->second.strLeaderName );
		packet->writeInt32( iter->second.nMemberCount );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CCityWar::AutoApplyCityWar()
{
	// Auto-apply is handled on activity start - applies are loaded from DB
	// and managed through ApplyCityWar/Unapply

}

void CCityWar::GongGao( int32_t nGongGaoId )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( nGongGaoId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CCityWar::SaveApplyInfo()
{
	// Build applyinfo string: "familyid1:type1|familyid2:type2|..."
	std::string strApplyInfo;
	for ( CityWarApplyMap::iterator iter = m_Apply.begin(); iter != m_Apply.end(); ++iter )
	{
		char buf[64];
		snprintf( buf, sizeof(buf), "%" PRId64 ":%d", iter->first, iter->second.nMemberCount );
		if ( !strApplyInfo.empty() )
		{
			strApplyInfo += "|";
		}
		strApplyInfo += buf;
	}

	MySqlDBGuard db( DBPOOL );
	char sql[2048];
	// Escape string for SQL - use simple hex encoding to avoid escape issues
	std::string escapedInfo;
	for ( size_t i = 0; i < strApplyInfo.size(); ++i )
	{
		char c = strApplyInfo[i];
		if ( c == '\'' || c == '\\' || c == '"' || c == '\0' )
		{
			escapedInfo += '\\';
			escapedInfo += c;
		}
		else
		{
			escapedInfo += c;
		}
	}
	snprintf( sql, sizeof(sql),
		"INSERT INTO `mem_city_war_apply` (`index`, `applyinfo`) VALUES (%d, '%s') "
		"ON DUPLICATE KEY UPDATE `applyinfo`='%s'",
		m_nIndex + 1, escapedInfo.c_str(), escapedInfo.c_str() );
	db.excute( sql );
}

bool CCityWar::canGetOnlineReward( Player* player )
{
	if ( NULL == player )
	{
		return false;
	}

	CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() )
	{
		return false;
	}

	// Total session time (current + accumulated)
	int32_t nTotalTime = iter->second.nSessionTime;
	if ( iter->second.bInActivity )
	{
		nTotalTime += player->getNow() - iter->second.nScoreTime;
	}

	return nTotalTime > 299;
}

void CCityWar::addPlayer( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.bInActivity = true;
		iter->second.nScoreTime = player->getNow();
	}
	else
	{
		CityWarPlayerScore score;
		score.nCharId = player->getCid();
		score.strName = player->getName();
		score.nFamilyId = player->getFamilyId();
		score.nCamp = GetFamilyCamp( player->getFamilyId() );
		score.nScore = 0;
		player->setPkMode( PK_MODE_ALL, false );
		m_mPlayerScore.insert( CityWarPlayerScoreMap::value_type( score.nCharId, score ) );

		// Initialize family score if not exist
		FamilyId_t nFamilyId = player->getFamilyId();
		if ( nFamilyId > 0 && m_mFamilyScore.find( nFamilyId ) == m_mFamilyScore.end() )
		{
			CityWarFamilyScore familyScore;
			familyScore.nFamilyId = nFamilyId;
			familyScore.strName = player->getFamilyName();
			familyScore.nCamp = score.nCamp;
			m_mFamilyScore[nFamilyId] = familyScore;
			m_lFamilyScore.push_back( &m_mFamilyScore[nFamilyId] );
		}
	}

	CActivity::addPlayer( player );
}

void CCityWar::removePlayer( Player* player, bool islogout )
{
	CActivity::removePlayer( player, islogout );
	if ( NULL == player )
	{
		return;
	}

	CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		// Accumulate session time
		if ( iter->second.bInActivity )
		{
			iter->second.nSessionTime += player->getNow() - iter->second.nScoreTime;
		}
		iter->second.bInActivity = false;
	}
}

void CCityWar::onPlayerKilled( Player* pDier, Player* pAttacker )
{
	if ( NULL == pDier || NULL == pAttacker )
	{
		return;
	}

	addPlayerScore( pAttacker, 1 );

	// Check if this triggers a family change on city war map
	if ( pDier->getMapId() == 50130 )
	{
		checkChangeFamily( true );
	}

	// Broadcast notification
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 326 );
	packet->writeInt64( pAttacker->getCid() );
	packet->writeUTF8( pAttacker->getName() );
	packet->writeInt64( pDier->getCid() );
	packet->writeUTF8( pDier->getName() );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CCityWar::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
	if ( NULL == pMonster || NULL == pKiller )
	{
		return;
	}

	addPlayerScore( pKiller, 5 );
}

void CCityWar::onMonsterAdd( MonsterActivity* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}

	// Set the monster's family allegiance based on current city owner
	// This makes monsters side with the current owner
	pMonster->SetFamilyId( m_nFamilyId );
}

void CCityWar::addPlayerScore( Player* player, int32_t nScore )
{
	if ( NULL == player )
	{
		return;
	}

	CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.nScore += nScore;
		iter->second.nScoreTime = player->getNow();

		// Also add to family score
		if ( player->getFamilyId() > 0 )
		{
			addFamilyScore( player->getFamilyId(), player->getFamilyName(), nScore, iter->second.nScoreTime );
		}
	}
	else
	{
		CityWarPlayerScore score;
		score.nCharId = player->getCid();
		score.strName = player->getName();
		score.nFamilyId = player->getFamilyId();
		score.nScore = nScore;
		score.nScoreTime = player->getNow();
		score.nCamp = GetFamilyCamp( player->getFamilyId() );
		score.bInActivity = true;
		m_mPlayerScore.insert( CityWarPlayerScoreMap::value_type( score.nCharId, score ) );
	}
}

void CCityWar::setUpdateScoreRank( FamilyId_t nFamilyId )
{
	CityWarFamilyScoreMap::iterator iter = m_mFamilyScore.find( nFamilyId );
	if ( iter != m_mFamilyScore.end() )
	{
		iter->second.bUpdateScroeRank = true;
	}
}

void CCityWar::addFamilyScore( FamilyId_t nFamilyId, const std::string& strFamilyName, int32_t nScore, int32_t nScoreTime )
{
	CityWarFamilyScoreMap::iterator iter = m_mFamilyScore.find( nFamilyId );
	if ( iter != m_mFamilyScore.end() )
	{
		iter->second.nScore += nScore;
		iter->second.nScoreTime = nScoreTime;
	}
	else
	{
		CityWarFamilyScore familyScore;
		familyScore.nFamilyId = nFamilyId;
		familyScore.strName = strFamilyName;
		familyScore.nScore = nScore;
		familyScore.nScoreTime = nScoreTime;
		familyScore.nCamp = GetFamilyCamp( nFamilyId );
		m_mFamilyScore[nFamilyId] = familyScore;
		m_lFamilyScore.push_back( &m_mFamilyScore[nFamilyId] );
	}

	m_bUpdateFamilyScroe = true;
	setNeedBroadcastActivityScore();
}

void CCityWar::win()
{
	if ( m_lFamilyScore.empty() )
	{
		return;
	}

	m_lFamilyScore.sort( FamilyScoreRankGreater() );

	// Get top 3 families
	CityWarFamilyScorePtrList::iterator iter = m_lFamilyScore.begin();
	if ( iter != m_lFamilyScore.end() && *iter != NULL )
	{
		m_nFamilyId = (*iter)->nFamilyId;
		m_First = (*iter)->nScore;
		m_FirstFamilyName = (*iter)->strName;
		m_FirstTime = (*iter)->nScoreTime;
		++iter;
	}
	if ( iter != m_lFamilyScore.end() && *iter != NULL )
	{
		m_Second = (*iter)->nScore;
		m_SecondFamilyName = (*iter)->strName;
		m_SecondTime = (*iter)->nScoreTime;
		++iter;
	}
	if ( iter != m_lFamilyScore.end() && *iter != NULL )
	{
		m_Third = (*iter)->nScore;
		m_ThirdFamilyName = (*iter)->strName;
		m_ThirdTime = (*iter)->nScoreTime;
	}

	m_nWinTime = TIMER.GetNow();

	// Send system mail to winner family leader
	Player* pLeader = GAME_SERVICE.getPlayer( m_Leader, 0, false );
	if ( pLeader != NULL && !m_cfgActivity.gift_id.empty() )
	{
		MemChrBag reward;
		memset( &reward, 0, sizeof(reward) );
		reward.itemId = m_cfgActivity.gift_id[0];
		reward.itemClass = IC_NORMAL;
		reward.itemCount = 1;
		reward.bind = IBS_BIND;
		DB_SERVICE.OnSendSysMail( m_Leader, MI_FAMILYWAR_REWARD, reward, "" );
	}

	addRewards();
	broadcastResult();
	OnCityWarResult( m_nFamilyId, m_FirstFamilyName );
}

void CCityWar::addRewards()
{
	for ( CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		const CityWarPlayerScore& score = iter->second;
		if ( !score.bInActivity )
		{
			continue;
		}

		Player* player = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
		if ( NULL == player )
		{
			continue;
		}

		// Base reward based on score
		int32_t nRewardExp = m_cfgActivity.exp_add_interval > 0 ? ( score.nScore * m_cfgActivity.exp_add_interval ) : 0;
		int32_t nRewardMoney = score.nScore * 100;
		if ( nRewardExp > 0 )
		{
			player->addExp( nRewardExp );
		}
		if ( nRewardMoney > 0 )
		{
			player->AddCurrency( CURRENCY_MONEY, nRewardMoney, MCR_MONEY_GAIN_ITEM );
		}

		// Winner family extra reward
		if ( score.nFamilyId == m_nFamilyId && !m_cfgActivity.gift_id.empty() )
		{
			MemChrBag bagItem;
			bagItem.itemId = m_cfgActivity.gift_id[0];
			bagItem.itemClass = IC_NORMAL;
			bagItem.itemCount = 1;
			bagItem.bind = IBS_BIND;
			if ( !player->GetBag().AddItem( bagItem, IACR_ACTIVITY ) )
			{
				DB_SERVICE.OnSendSysMail( player->getCid(), MI_FAMILYWAR_REWARD, bagItem, "" );
			}
		}
	}
}

void CCityWar::saveResult()
{
	int32_t nNow = TIMER.GetNow();
	MySqlDBGuard db( DBPOOL );
	char sql[2048];
	// Simple SQL escaping - replace single quotes
	std::string firstName = m_FirstFamilyName;
	std::string secondName = m_SecondFamilyName;
	std::string thirdName = m_ThirdFamilyName;
	size_t pos;
	while ( (pos = firstName.find("\'")) != std::string::npos ) firstName.replace(pos, 1, "\\\'");
	while ( (pos = secondName.find("\'")) != std::string::npos ) secondName.replace(pos, 1, "\\\'");
	while ( (pos = thirdName.find("\'")) != std::string::npos ) thirdName.replace(pos, 1, "\\\'");

	snprintf( sql, sizeof(sql),
		"INSERT INTO `mem_city_war` (`index`, `familyid`, `leader`, `time`, "
		"`firstname`, `secondname`, `thirdname`, "
		"`firstscore`, `secondscore`, `thirdscore`) "
		"VALUES (%d, %" PRId64 ", %" PRId64 ", %d, "
		"'%s', '%s', '%s', %d, %d, %d)",
		m_nIndex + 1, m_nFamilyId, m_Leader, nNow,
		firstName.c_str(), secondName.c_str(), thirdName.c_str(),
		m_First, m_Second, m_Third );
	db.excute( sql );
}

void CCityWar::onActivityStart()
{
	m_nIndex++;
	m_nFamilyId = 0;
	m_nLastFamilyId = 0;
	m_Leader = 0;
	m_nWinTime = 0;
	m_First = 0;
	m_Second = 0;
	m_Third = 0;
	m_FirstFamilyName.clear();
	m_SecondFamilyName.clear();
	m_ThirdFamilyName.clear();
	m_Apply.clear();
	m_bUpdateFamilyScroe = false;

	AutoApplyCityWar();
}

void CCityWar::onTimeEnd()
{
	win();

	// Clear apply data
	m_Apply.clear();

	CActivity::onTimeEnd();
}

int32_t CCityWar::getNextStartTime()
{
	if ( m_cfgActivity.start_hour.empty() )
	{
		return 0;
	}

	const tm& localnow = TIMER.GetLocalNow();
	int32_t nowMinute = localnow.tm_hour * 60 + localnow.tm_min;
	(void)nowMinute;
	int32_t startMinute = m_cfgActivity.start_hour[0];
	(void)startMinute;

	// Check if we're in a special day period
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( isInSpecialDay( startDays ) && startDays <= 6 )
	{
		return 0; // No scheduling constraints
	}

	return CActivity::getNextStartTime();
}

bool CCityWar::OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t Param )
{
	if ( NULL == player || NULL == pMap )
	{
		return false;
	}

	if ( !pMap->isWalkablePosition( nX, nY ) )
	{
		return false;
	}

	// Check if map belongs to this activity
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

	if ( pMap->GetId() == 50133 )
	{
		// Check owner on city hall map
		if ( m_nFamilyId > 0 && player->getFamilyId() != m_nFamilyId )
		{
			// Not the owning family - check if they can enter
			if ( m_Apply.find( player->getFamilyId() ) == m_Apply.end() )
			{
				return false;
			}
		}
	}

	return player->switchMap( pMap, nX, nY, true ) == 0;
}

Answer::NetPacket* CCityWar::packetActivityScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nFamilyId );
	packet->writeInt32( getLeftTime() );

	// Append family rankings (top 5)
	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );

	if ( !m_lFamilyScore.empty() )
	{
		m_lFamilyScore.sort( FamilyScoreRankGreater() );
		for ( CityWarFamilyScorePtrList::iterator iter = m_lFamilyScore.begin();
			iter != m_lFamilyScore.end() && nCount < 5; ++iter )
		{
			CityWarFamilyScore* pScore = *iter;
			if ( pScore != NULL )
			{
				packet->writeInt64( pScore->nFamilyId );
				packet->writeUTF8( pScore->strName );
				packet->writeInt32( pScore->nScore );
				++nCount;
			}
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	return packet;
}

void CCityWar::appendPlayerRankInfo( NetPacket* packet, FamilyId_t nFamilyId, int32_t nRank )
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt64( nFamilyId );
	packet->writeInt32( nRank );

	// Append top 3 players from this family
	int32_t nPlayerCount = 0;
	for ( CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.begin();
		iter != m_mPlayerScore.end() && nPlayerCount < 3; ++iter )
	{
		if ( iter->second.nFamilyId == nFamilyId && iter->second.bInActivity )
		{
			packet->writeInt64( iter->first );
			packet->writeUTF8( iter->second.strName );
			packet->writeInt32( iter->second.nScore );
			nPlayerCount++;
		}
	}

	packet->writeInt8( (int8_t)nPlayerCount );
}

void CCityWar::broadcastReady()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 332 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CCityWar::broadcastStart()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet ) return;
	packet->writeInt32( 335 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CCityWar::broadcastRankInfo()
{
	NetPacket* packet = packetActivityScore();
	if ( packet != NULL )
	{
		GAME_SERVICE.worldBroadcast( packet );
	}
}

void CCityWar::broadcastResult()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nFamilyId );

	// Append top 4 family rankings
	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );

	if ( !m_lFamilyScore.empty() )
	{
		m_lFamilyScore.sort( FamilyScoreRankGreater() );
		for ( CityWarFamilyScorePtrList::iterator iter = m_lFamilyScore.begin();
			iter != m_lFamilyScore.end() && nCount < 4; ++iter )
		{
			CityWarFamilyScore* pScore = *iter;
			if ( pScore != NULL )
			{
				packet->writeInt64( pScore->nFamilyId );
				packet->writeUTF8( pScore->strName );
				packet->writeInt32( pScore->nScore );
				++nCount;
			}
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

Answer::NetPacket* CCityWar::packetActivityFamilyScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_FAMILY_SCORE );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nFamilyId );

	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );

	if ( !m_lFamilyScore.empty() )
	{
		m_lFamilyScore.sort( FamilyScoreRankGreater() );
		for ( CityWarFamilyScorePtrList::iterator iter = m_lFamilyScore.begin();
			iter != m_lFamilyScore.end() && nCount < 4; ++iter )
		{
			CityWarFamilyScore* pScore = *iter;
			if ( pScore != NULL )
			{
				packet->writeInt64( pScore->nFamilyId );
				packet->writeUTF8( pScore->strName );
				packet->writeInt32( pScore->nScore );
				++nCount;
			}
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	return packet;
}

Answer::NetPacket* CCityWar::packetActivityPlayerScore( Player* player )
{
	if ( NULL == player )
	{
		return NULL;
	}

	CityWarPlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() )
	{
		return NULL;
	}

	const CityWarPlayerScore& score = iter->second;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_PLAYER_SCORE );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( score.nScore );
	packet->writeInt32( 0 ); // Kill count placeholder

	packet->setSize( packet->getWOffset() );
	return packet;
}
