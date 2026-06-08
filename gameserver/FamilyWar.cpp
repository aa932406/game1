#include "FamilyWar.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include "FamilyManager.h"
#include "ActivityManager.h"
#include "KaiFuHuoDong.h"
#include <algorithm>

using namespace Answer;

CFamilyWar::CFamilyWar( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_pSton( NULL )
, m_pPillar( NULL )
, m_pTitle( NULL )
, m_pBoss( NULL )
, m_pBuffPlayer( NULL )
, m_nBuffStartTick( 0 )
, m_nGuidFamily( 0 )
, m_nWinTimes( 0 )
, m_nActiveState( 0 )
, m_nActivePillarState( 0 )
{
	m_FamilyName			= "";
	m_FamilyLeaderName		= "";
}

CFamilyWar::~CFamilyWar()
{
}

void CFamilyWar::Init()
{
	CActivity::Init();
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( "SELECT * FROM `mem_family_war` ORDER BY `time` DESC LIMIT 1" );

	FamilyId_t nFamilyId = 0;
	int16_t	nWinTimes = 0;
	string familyname = "";
	string leadyername = "";
	while(!result.eof())
	{
		nFamilyId	= result.getInt64Value("familyid");
		nWinTimes	= result.getIntValue("wintimes");
		familyname	= result.getStringValue("familyname");
		leadyername = result.getStringValue("leadyername");
		break;
	}
	m_FamilyLeaderName	= leadyername;
	m_FamilyName		= familyname;
	m_nGuidFamily		= nFamilyId;
	m_nWinTimes			= nWinTimes;
}

void CFamilyWar::OnUpdate( CActivityMap* pMap )
{
	CActivity::OnUpdate( pMap );
	if ( NULL == pMap )
	{
		return;
	}

	int64_t curTick = pMap->getTick();
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		PlayerScore& score = *iter;
		if ( score.bInActivity && score.nScore == 0 )
		{
			if ( ( curTick - score.nStartTick ) / 1000 >= 900 )
			{
				Player* pPlayer = GAME_SERVICE.getPlayer( score.nCharId, pMap->GetRunnerId() );
				if ( pPlayer != NULL )
				{
					int32_t nExp = CFG_DATA.GetFamilyWarJoinRewardTable().GetReward( pPlayer->getLevel() );
					pPlayer->addExp( nExp );
					score.nScore = nExp;
				}
			}
		}
	}
}

void CFamilyWar::reset()
{
	CActivity::reset();
	m_pSton			= NULL;
	m_pPillar		= NULL;
	m_pTitle		= NULL;
	m_pBoss			= NULL;
	m_pBuffPlayer	= NULL;
	m_nBuffStartTick = 0;
	m_nActiveState	= 0;
	m_nActivePillarState = 0;

	m_lstFamilyScore.clear();
	m_lstPlayerScore.clear();
}

bool CFamilyWar::checkData()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( startDays == 2 )
	{
		return true;
	}
	else if ( startDays < 2 )
	{
		return false;
	}
	else
	{
		return CActivity::checkData();
	}
}

bool CFamilyWar::checkWeek()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( startDays == 2 )
	{
		return true;
	}
	else if ( startDays < 2 )
	{
		return false;
	}
	else
	{
		return CActivity::checkWeek();
	}
}

void CFamilyWar::onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, Player* pAttacker )
{
	if ( NULL == pMonster || NULL == pAttacker )
	{
		return;
	}

	if ( pMonster == m_pSton )
	{
		int32_t nAddExp = nDamage;
		pAttacker->addExp( nAddExp );
		addPlayerScore( pAttacker, nAddExp, 0 );
	}
	else if ( pMonster == m_pPillar )
	{
		pAttacker->AddCurrency( CURRENCY_MONEY, nDamage / 10, MCR_ATTACK_FAMIWAR_PILLAR );
		addPlayerScore( pAttacker, 0, 0 );
		if ( pAttacker->getFamilyId() > 0 )
		{
			addFamilyScore( pAttacker->getFamilyId(), pAttacker->getFamilyName(), nDamage );
		}
	}
}

void CFamilyWar::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
	if ( NULL == pMonster || NULL == pKiller )
	{
		return;
	}

	if ( !IsRuning() )
	{
		return;
	}

	if ( m_pTitle == pMonster )
	{
		m_pBuffPlayer = pKiller;
		m_nBuffStartTick = pKiller->getTick();
		addBuff( pKiller );
		setNeedBroadcastActivityScore();
	}
	else if ( m_pPillar == pMonster )
	{
		FamilyId_t nFamilyId = 0;
		if ( !m_lstFamilyScore.empty() )
		{
			nFamilyId = m_lstFamilyScore.front().nFamilyId;
		}
		m_pPillar->SetFamilyId( nFamilyId );
		broadcastPillerKilled( nFamilyId );
		if ( NULL == m_pSton || !m_pSton->isAlive() )
		{
				win( nFamilyId );
		}
	}
	else if ( m_pSton == pMonster )
	{
		broadcastStoneKilled();
		if ( m_pPillar != NULL )
		{
			if ( m_pPillar->GetFamilyId() != m_nGuidFamily )
			{
				win( m_pPillar->GetFamilyId() );
			}
		}
	}
}

void CFamilyWar::onPlayerKilled( Player* pDier, Player* pAttacker )
{
	if ( NULL == pDier || NULL == pAttacker )
	{
		return;
	}

	addPlayerScore( pAttacker, 20, 1 );

	if ( m_pBuffPlayer == pDier )
	{
		m_pBuffPlayer = pAttacker;
		m_nBuffStartTick = pAttacker->getTick();
		addBuff( m_pBuffPlayer );
		setNeedBroadcastActivityScore();
	}
}

void CFamilyWar::onMonsterAdd( MonsterActivity* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}

	int32_t nActMonsterId = pMonster->getActivityMonsterId();
	if ( nActMonsterId == 20333 )
	{
		m_pTitle = pMonster;
	}
	else if ( nActMonsterId == 20334 )
	{
		m_pBoss = pMonster;
	}
	else if ( nActMonsterId == ACTICITY_MONSTER_ID_FAMILY_WAR_STON )
	{
		m_pSton = pMonster;
	}
	else if ( nActMonsterId == ACTICITY_MONSTER_ID_FAMILY_WAR_PILLAR )
	{
		m_pPillar = pMonster;
	}

	if ( m_pSton != NULL && m_pPillar != NULL && m_pTitle != NULL && m_pBoss != NULL )
	{
		pMonster->SetFamilyId( m_nGuidFamily );
	}
}

void CFamilyWar::addPlayer( Player* player )
{
	CActivity::addPlayer( player );
	if ( NULL == player )
	{
		return;
	}

	// Set PK mode
	if ( player->getFamilyId() > 0 )
	{
		player->setPkMode( PK_MODE_LEGION, false );
	}
	else
	{
		player->setPkMode( PK_MODE_ALL, false );
	}

	addBuff( player );

	CharId_t nCharId = player->getCid();
	PlayerScore* pFound = NULL;
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		if ( iter->nCharId == nCharId )
		{
			iter->bInActivity = true;
			iter->nStartTick = player->getTick();
			pFound = &(*iter);
			break;
		}
	}

	if ( pFound == NULL )
	{
		PlayerScore score;
		score.nCharId		= nCharId;
		score.strName		= player->getName();
		score.nFamilyId		= player->getFamilyId();
		score.nStartTick	= player->getTick();
		score.bInActivity	= true;
		m_lstPlayerScore.push_back( score );
	}

	player->updateRecord( RP_FIRST_JUN_TUAN_ZHAN_STATE ,3 );
	KAI_FU_HUO_DONG.SendKaiFuHuoDongIcon( player );
	SendPlayerActivityScore( player, getLeftTime() );
}

void CFamilyWar::removePlayer( Player* player, bool islogout )
{
	CActivity::removePlayer( player, islogout );
	if ( NULL == player )
	{
		return;
	}

	if ( player->HasBuffById( 100001 ) )
	{
		removeBuff( player );
		if ( m_pTitle != NULL )
		{
			m_pTitle->OnRevive();
		}
	}

	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		if ( iter->nCharId == player->getCid() )
		{
			iter->bInActivity = false;
			iter->nStartTick = player->getTick();
			return;
		}
	}
}

void CFamilyWar::SendPlayerActivityInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	if ( m_nGuidFamily > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, IM_GAME_SOCIAL_NOTIFY_FAMILYWAR_INFO );
		if ( NULL == packet )
		{
			return;
		}

		packet->writeInt32( player->getGateIndex() );
		packet->writeInt32( m_cfgActivity.id );
		packet->writeInt64( m_nGuidFamily );
		packet->writeInt32( getNextStartTime() );
		packet->writeInt8( isShowDoubleReward() ? 1 : 0 );

		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacket( packet );
	}
	else
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
		if ( NULL == packet )
		{
			return;
		}
		packet->writeInt32( m_cfgActivity.id );
		packet->writeInt64( m_nGuidFamily );
		packet->writeInt32( getNextStartTime() );
		packet->writeUTF8( "" );
		packet->writeInt8( 0 );
		packet->writeInt8( isShowDoubleReward() ? 1 : 0 );

		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
	}
}

void CFamilyWar::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt64( m_nGuidFamily );
	if ( m_nGuidFamily > 0 )
	{
		FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( m_nGuidFamily );
		packet->writeUTF8( familyInfo.strName );
	}
	else
	{
		packet->writeUTF8( "" );
	}
	packet->writeInt32( nLeftTime );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );

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

Position CFamilyWar::GetRandBornPos( Player* player )
{
	if ( NULL == player )
	{
		return Position( -1, -1 );
	}

	if ( m_nGuidFamily > 0 && player->getFamilyId() == m_nGuidFamily )
	{
		return getBornRandPosB();
	}
	return getBornRandPosA();
}

bool CFamilyWar::OnSitRevive( Player* player )
{
	if ( player != NULL )
	{
		ItemData data;
		data.m_nClass	= IC_NORMAL;
		data.m_nId		= ISI_FAMILY_WAR_SIT_REVIVE;
		data.m_nCount	= 1;
		if ( player->GetBag().RemoveItem( data, IDCR_FAMILY_WAR_SIT_REVIVE ) )
		{
			addBuff( player );
			return true;
		}
	}
	return false;
}

int32_t CFamilyWar::GetRevive( Player* player )
{
	if ( NULL == player )
	{
		return CActivity::GetRevive( player );
	}

	addBuff( player );
	if ( m_nGuidFamily > 0 && player->getFamilyId() == m_nGuidFamily )
	{
		int32_t lenth = m_cfgActivity.target_regionb.size();
		if( lenth == 1 )
		{
			return m_cfgActivity.target_regionb[0];
		}
		else
		{
			return m_cfgActivity.target_regionb[RANDOM.generate( 0, lenth-1 )]; 
		}
	}
	else
	{
		int32_t lenth = m_cfgActivity.target_regiona.size();
		if( lenth == 1 )
		{
			return m_cfgActivity.target_regiona[0];
		}
		else
		{
			return m_cfgActivity.target_regiona[RANDOM.generate( 0, lenth-1 )]; 
		}
	}
}

void CFamilyWar::addPlayerScore( Player* player, int32_t nScore, int32_t nKillCount )
{
	if ( NULL == player )
	{
		return;
	}

	CharId_t Cid = player->getCid();
	PlayerScore* pPlayerScore = getPlayerScore( Cid );
	if ( NULL == pPlayerScore )
	{
		return;
	}

	if ( nKillCount > 0 )
	{
		if ( pPlayerScore->nKillCount >= 19 )
			return;
		pPlayerScore->nKillCount += nKillCount;
	}
	pPlayerScore->nScore += nScore;

	addFamilyScore( player->getFamilyId(), player->getFamilyName(), nScore );
	m_lstPlayerScore.sort( std::greater<PlayerScore>() );
	sendPlayerScore( player );
	setNeedBroadcastActivityScore();
}

void CFamilyWar::addFamilyScore( FamilyId_t nFamilyId, const std::string& strFamilyName, int32_t nScore )
{
	FamilyScoreList::iterator iter = m_lstFamilyScore.begin();
	for ( ; iter != m_lstFamilyScore.end(); ++iter )
	{
		if ( iter->nFamilyId == nFamilyId )
		{
			iter->nScore += nScore;
			break;
		}
	}
	if ( iter == m_lstFamilyScore.end() )
	{
		FamilyScore score;
		score.nFamilyId		= nFamilyId;
		score.strFamilyName	= strFamilyName;
		score.nScore		= nScore;
		score.nUsedScore	= 0;
		score.nActivePillar	= 0;
		m_lstFamilyScore.push_back( score );
	}
	m_lstFamilyScore.sort( std::greater<FamilyScore>() );
	setNeedBroadcastActivityScore();
}

void CFamilyWar::win( FamilyId_t nFamilyId )
{
	m_nActiveState = 2;
	if ( nFamilyId != m_nGuidFamily && nFamilyId > 0 )
	{
		FirstFamilyWar( nFamilyId );
		m_nWinTimes = 0;
		m_nGuidFamily = nFamilyId;
	}
	++m_nWinTimes;
	m_nState = AS_END;

	sendWinnerReward( nFamilyId );
	sendPlayerScoreRankReward();
	sendFamilyScoreRankReward();

	saveFamilyWarResult();
	addRewards();
	broadcastActivityResult();
	BroadcastActivityState();
	delayKickAll( 30 );
	broadcastWin();
	stopActivity();
	NotifyActivityInfo();
	GAME_SERVICE.broadcastHuoDongDaTingIcon();
}

void CFamilyWar::FirstFamilyWar( FamilyId_t FamilyId )
{
	if ( !isDoubleReward() )
	{
		return;
	}
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		const PlayerScore& score = *iter;
		Player* player = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
		if ( NULL != player )
		{
			if ( score.nFamilyId == FamilyId )
			{
				FamilyInfo stu = FAMILY_MANAGER.GetFamilyInfo( FamilyId );
				m_FamilyName		= stu.strName;
				if ( player->getFamilyPosition() == FP_LEADER )
				{
					player->updateRecord( RP_FIRST_JUN_TUAN_ZHAN_STATE ,1 );
					m_FamilyLeaderName	= player->getName();
					KAI_FU_HUO_DONG.SendKaiFuHuoDongIcon( player );
				}
				else
				{
					player->updateRecord( RP_FIRST_JUN_TUAN_ZHAN_STATE ,2 );
					KAI_FU_HUO_DONG.SendKaiFuHuoDongIcon( player );
				}
			}	
		}
	}
}

void CFamilyWar::addRewards()
{
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		const PlayerScore& score = *iter;
		if ( score.bInActivity )
		{
			Player* player = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
			if ( player != NULL )
			{
				int32_t nGiftId = 0;
				if ( m_nGuidFamily > 0 && m_nGuidFamily == player->getFamilyId() )
				{
				if ( m_cfgActivity.gift_id.size() > (size_t)player->getFamilyPosition() )
					nGiftId = m_cfgActivity.gift_id[ player->getFamilyPosition() ];
			}
			else if ( score.nKillCount > 0 )
			{
				if ( m_cfgActivity.gift_id.size() > 10 )
					nGiftId = m_cfgActivity.gift_id[10];
			}
			else
			{
				if ( m_cfgActivity.gift_id.size() > 11 )
					nGiftId = m_cfgActivity.gift_id[11];
				}

				MemChrBag bagItem;
				bagItem.itemId		= nGiftId;
				bagItem.itemClass	= IC_NORMAL;
				bagItem.itemCount	= 1;
				bagItem.bind		= IBS_BIND;
				if ( !player->GetBag().AddItem( bagItem, IACR_ACTIVITY ) )
				{
					DB_SERVICE.OnSendSysMail( player->getCid(), MI_FAMILYWAR_REWARD, bagItem );
				}
				if ( isDoubleReward() )
				{
					if ( !player->GetBag().AddItem( bagItem, IACR_ACTIVITY ) )
					{
						DB_SERVICE.OnSendSysMail( player->getCid(), MI_FAMILYWAR_REWARD, bagItem );
					}
				}
			}
		}
	}
}

void CFamilyWar::saveFamilyWarResult()
{
	int32_t nTime = DayTime::dayzero( TIMER.GetNow() ) + m_cfgActivity.start_hour[0] * 60;
	DB_SERVICE.SaveFamilyWarResult( GetId(), m_nGuidFamily, m_nWinTimes, nTime, m_FamilyName, m_FamilyLeaderName);
}

void CFamilyWar::broadcastActivityResult()
{
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		PlayerScore& score = *iter;
		if ( score.bInActivity )
		{
			Player* pPlayer = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
			if ( pPlayer != NULL )
			{
				NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
				if ( NULL == packet )
				{
					return;
				}

				packet->writeInt32( m_cfgActivity.id );
				packet->writeInt64( m_nGuidFamily );
				FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( m_nGuidFamily );
				packet->writeUTF8( familyInfo.strName );
				packet->writeInt32( score.nScore );
				packet->writeInt8( isDoubleReward() ? 1 : 0 );

				packet->setSize( packet->getWOffset() );
				GAME_SERVICE.sendPacketTo( pPlayer->getConnId(), pPlayer->getGateIndex(), packet );
			}
		}
	}
}

void CFamilyWar::onTimeEnd()
{
	if ( m_pBuffPlayer != NULL )
	{
		win( m_pBuffPlayer->getFamilyId() );
	}
	else
	{
		win( 0 );
	}
	CActivity::onTimeEnd();
}

int32_t	CFamilyWar::getNextStartTime()
{
	if ( IsRuning() || m_cfgActivity.start_hour.empty() )
	{
		return 0;
	}

	int32_t nNowTime = TIMER.GetNow();
	const tm& localnow	= TIMER.GetLocalNow();
	int32_t nowMinute	= localnow.tm_hour * 60 + localnow.tm_min;
	int32_t startMinute = m_cfgActivity.start_hour[0];
	for ( uint32_t i = 0; i < m_cfgActivity.start_hour.size(); ++i )
	{
		int32_t startTime = DayTime::dayzero( nNowTime ) + m_cfgActivity.start_hour[i] * 60;
		if ( startMinute > nNowTime )
		{
			startMinute = m_cfgActivity.start_hour[i];
			break;
		}
	}

	int32_t days = -1;
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( checkData() && checkWeek() )
	{
		if( nowMinute < startMinute )
		{
			days = 0;
		}
	}
	else if ( startDays < 2 )
	{
		days = 2 - startDays;
	}

	if ( days < 0 )
	{
		if ( m_cfgActivity.weekday.empty() )
		{
			return 0;
		}
		int32_t weekday = TIMER.GetWeekDay();
		int32_t nextweekday = 0;

		Int32Vector::const_reverse_iterator iter = m_cfgActivity.weekday.rbegin();
		for ( ; iter != m_cfgActivity.weekday.rend(); ++iter )
		{
			if ( weekday == *iter )
			{
				++iter;
				break;
			}
		}

		if ( iter == m_cfgActivity.weekday.rend() )
		{
			nextweekday = m_cfgActivity.weekday.back();
		}
		else
		{
			nextweekday = *iter;
		}

		if ( nextweekday < weekday )
		{
			days = nextweekday + 7 - weekday;
		}
		else
		{
			days = nextweekday - weekday;
		}
	}

	int32_t time = DayTime::dayzero( nNowTime );
	time += days * 24 * 60 * 60 + startMinute*60;
	return time;
}

Answer::NetPacket* CFamilyWar::packetActivityScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2E26 );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt8( (int8_t)m_nActiveState );
	packet->writeInt32( m_nActivePillarState );
	packet->writeInt32( getLeftTime() );

	// Write current buff player's family name and remaining win time
	if ( m_pBuffPlayer != NULL )
	{
		packet->writeUTF8( m_pBuffPlayer->getName() + "(" + m_pBuffPlayer->getFamilyName() + ")" );
		int32_t nLeftWinTime = (int32_t)(m_nBuffStartTick - m_pBuffPlayer->getTick() + 300000) / 1000;
		if ( nLeftWinTime < 0 ) nLeftWinTime = 0;
		packet->writeInt32( nLeftWinTime );
	}
	else
	{
		packet->writeUTF8( "" );
		packet->writeInt32( 0 );
	}

	appendPlayerScoreRank( packet );
	appendFamilyScoreRank( packet );

	packet->setSize( packet->getWOffset() );
	return packet;
}

Answer::NetPacket* CFamilyWar::packetActivityFamilyScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_ACTIVITY_FAMILY_SCORE );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	if ( m_pPillar != NULL )
	{
		FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( m_pPillar->GetFamilyId() );
		packet->writeInt64( familyInfo.nId );
		packet->writeUTF8( familyInfo.strName );
	}
	else
	{
		packet->writeInt64( 0 );
		packet->writeUTF8( "" );
	}

	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );
	for ( FamilyScoreList::iterator iter = m_lstFamilyScore.begin(); iter != m_lstFamilyScore.end(); ++iter )
	{
		packet->writeInt64( iter->nFamilyId );
		packet->writeUTF8( iter->strFamilyName );
		packet->writeInt32( iter->nScore );
		++nCount;
		if ( nCount >= 4 )
		{
			break;
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	return packet;
}

Answer::NetPacket* CFamilyWar::packetActivityPlayerScore( Player* player )
{
	if ( NULL == player )
	{
		return NULL;
	}

	PlayerScore* pScore = getPlayerScore( player->getCid() );
	if ( NULL == pScore )
	{
		return NULL;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_ACTIVITY_PLAYER_SCORE );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( pScore->nScore );
	packet->writeInt32( 0 ); // money (not tracked separately in new version)
	packet->writeInt32( pScore->nKillCount );

	packet->setSize( packet->getWOffset() );
	return packet;
}

bool CFamilyWar::CanAddPillarMoney( Player* player ) const
{
	if ( NULL == player )
	{
		return false;
	}

	if ( GetPositionLevel( player->getFamilyPosition() ) < FPL_VICE )
	{
		return false;
	}

	if ( !IsRuning() )
	{
		return false;
	}

	if ( NULL == m_pPillar )
	{
		return false;
	}

	if ( !m_pPillar->isAlive() )
	{
		return false;
	}

	if ( m_pPillar->GetFamilyId() != player->getFamilyId() )
	{
		return false;
	}

	return true;
}

int32_t CFamilyWar::AddPillarMoney( int32_t nMoney )
{
	if ( !IsRuning() )
	{
		return 0;
	}

	if ( NULL == m_pPillar )
	{
		return 0;
	}

	if ( !m_pPillar->isAlive() )
	{
		return 0;
	}

	return m_pPillar->AddFamilyMoney( nMoney );
}

void CFamilyWar::OnFamilyWarResult( FamilyId_t nFamilyId, int16_t nTimes, string FamilyName, string LeadyerName )
{
	m_nGuidFamily			= nFamilyId;
	m_nWinTimes				= nTimes;
	m_FamilyName			= FamilyName;
	m_FamilyLeaderName		= LeadyerName;
	GAME_SERVICE.broadcastHuoDongDaTingIcon();
}

FamilyId_t CFamilyWar::GetWinFamily()
{
	return m_nGuidFamily;
}

int32_t  CFamilyWar::HaveRewardCount( Player* Player )
{
	if ( NULL == Player )
	{
		return 0;
	}
	if ( m_nGuidFamily <= 0 )
	{
		return 0;
	}

	if ( m_nGuidFamily != Player->getFamilyId() )
	{
		return 0;
	}

	int32_t limitId = PR_ACTIVITY_DAILY_REAWRD_START + GetId();
	if ( Player->GetOperateLimit().CheckCountIsLimited( limitId, 1 ) )
	{
		return 0;
	}
	return 1;
}

void CFamilyWar::SendPlayerPillarInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	if ( NULL == m_pPillar )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_FAMILY_WAR_PILLAR_INFP );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cfgActivity.id );
	if ( m_pPillar != NULL )
	{
		packet->writeInt32( m_pPillar->GetFamilyMoney() );
	}
	else
	{
		packet->writeInt32( 0 );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

int32_t CFamilyWar::GiveDailyReward( Player* player )
{
	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_nGuidFamily <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_nGuidFamily != player->getFamilyId() )
	{
		return ERR_INVALID_DATA;
	}

	int32_t limitId = PR_ACTIVITY_DAILY_REAWRD_START + GetId();
	if ( player->GetOperateLimit().CheckCountIsLimited( limitId, 1 ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag addItem;
	addItem.itemClass	= IC_NORMAL;
	addItem.itemId		= m_cfgActivity.daily_reward[player->getFamilyPosition()];
	addItem.itemCount	= 1;
	addItem.bind		= IBS_BIND;
	if ( !player->GetBag().AddItem( addItem, IACR_ACTIVITY ) )
	{
		return ERR_INVALID_DATA;
	}

	player->GetOperateLimit().AddLimitCount( limitId, 1 );
	player->GetPlayerDailyActivity().SendHuoDongDaTingIcon();
	return ERR_OK;
}

bool CFamilyWar::CanUseXP() const
{
	return false;
}

void CFamilyWar::broadcastReady()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet ) return;
	packet->writeInt32( 2 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CFamilyWar::broadcastStart()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet ) return;
	packet->writeInt32( 3 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CFamilyWar::broadcastPillerKilled( FamilyId_t nFamilyId )
{
	if ( nFamilyId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
		if ( NULL == packet ) return;
		packet->writeInt32( 6 );
		FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( nFamilyId );
		packet->writeUTF8( familyInfo.strName );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( 0, packet );
	}
	else
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
		if ( NULL == packet ) return;
		packet->writeInt32( 7 );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( 0, packet );
	}
}

void CFamilyWar::broadcastStoneKilled()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet ) return;
	packet->writeInt32( 8 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( 0, packet );
}

void CFamilyWar::broadcastWin()
{
	if ( m_nGuidFamily > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
		if ( NULL == packet ) return;
		packet->writeInt32( 9 ); // BCI_WORLD_FAMILYWAR_WIN
		FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( m_nGuidFamily );
		packet->writeUTF8( familyInfo.strName );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( 0, packet );
	}
	else
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2CD6 );
		if ( NULL == packet ) return;
		packet->writeInt32( 10 ); // BCI_WORLD_FAMILYWAR_FAIL
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( 0, packet );
	}
}

int32_t CFamilyWar::getBuffLevel() const
{
	if ( m_nWinTimes == 1 )
	{
		return 1;
	}
	else if ( m_nWinTimes >= 2 )
	{
		return 2;
	}
	else if ( m_nWinTimes >= 3 )
	{
		return 3;
	}
	return 0;
}

void CFamilyWar::addBuff( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	if ( m_nGuidFamily <= 0 || player->getFamilyId() == m_nGuidFamily )
	{
		return;
	}

	int32_t nBuffLevel = getBuffLevel();
	if ( nBuffLevel == 0 )
	{
		return;
	}
	addActivityBuff( player, 100001, true );
}

void CFamilyWar::removeBuff( Player* player )
{
	if ( player != NULL )
	{
		player->removeBuff( 100001 );
	}
}

bool CFamilyWar::isDoubleReward() const
{
	int32_t startDays = TIMER.GetDaysFromStart();
	return startDays <= 2;
}

bool CFamilyWar::isShowDoubleReward()
{
	int32_t startDays = TIMER.GetDaysFromStart();
	if ( startDays < 2 )
	{
		return true;
	}
	if ( startDays == 2 )
	{
		int32_t NextTime = getNextStartTime();
		if ( DayTime::daydiff( NextTime ) != 0 )
		{
			return false;
		}
		return true;
	}
	return false;
}

std::string CFamilyWar::GetFamilyName()
{
	return m_FamilyName;
}

std::string CFamilyWar::GetFamilyLeaderName()
{
	return m_FamilyLeaderName;
}

void CFamilyWar::NotifyActivityInfo( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_FAMILY_WAR_WIN_FAMILY );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64( m_nGuidFamily );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast( 0, packet );
	}
	else
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, SM_NOTIFY_FAMILY_WAR_WIN_FAMILY );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64( m_nGuidFamily );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( pPlayer->getConnId(), pPlayer->getGateIndex(), packet );
	}
}

// ========== 新版本方法 ==========

void CFamilyWar::AdjustMonsterAttr( CfgMonster* cfgMonster )
{
	if ( NULL == cfgMonster ) return;
	// Binary: adjust by world level -> use GetDaysFromStart as a proxy
	int32_t nLevel = 1 + TIMER.GetDaysFromStart() / 7;
	adjustMonsterAttr( cfgMonster, nLevel, true );
}

bool CFamilyWar::OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t param )
{
	if ( NULL == player || NULL == pMap )
	{
		return false;
	}

	if ( !pMap->isWalkablePosition( nX, nY ) )
	{
		return false;
	}

	// Find map index in activity maps
	int32_t nIndex = 0;
	bool bFind = false;
	for ( std::list<CActivityMap*>::iterator iter = m_activityMaps.begin(); iter != m_activityMaps.end(); ++iter )
	{
		++nIndex;
		if ( *iter == pMap )
		{
			bFind = true;
			break;
		}
	}

	if ( !bFind )
	{
		return false;
	}

	// Map index 2: requires m_nActivePillarState == 15 (all pillars activated)
	if ( nIndex == 2 )
	{
		return m_nActivePillarState == 15;
	}

	// Map index 3: requires winning family member
	if ( nIndex == 3 )
	{
		return m_nGuidFamily > 0 && player->getFamilyId() == m_nGuidFamily;
	}

	return false;
}

bool CFamilyWar::OnActivePillar( Player* player, int32_t nIndex )
{
	if ( NULL == player )
	{
		return false;
	}

	FamilyId_t FamilyId = player->getFamilyId();
	FamilyScore* pFamilyScore = getFamilyScore( FamilyId );
	if ( NULL == pFamilyScore )
	{
		return false;
	}

	// Need at least 1000 unused score to activate a pillar
	if ( pFamilyScore->nScore - pFamilyScore->nUsedScore < 1000 )
	{
		return false;
	}

	int32_t nResult = m_nActivePillarState | (1 << nIndex);
	if ( m_nActivePillarState == nResult )
	{
		return false;
	}

	pFamilyScore->nUsedScore += 1000;
	++pFamilyScore->nActivePillar;
	sendActivePillarReward( FamilyId );

	m_nActivePillarState = nResult;
	setNeedBroadcastActivityScore();

	if ( m_nActivePillarState == 15 )
	{
		m_nActiveState = 1;
	}

	return true;
}

void CFamilyWar::OnTaskSubmited( Player* player, int32_t nScore )
{
	if ( NULL == player ) return;

	CharId_t Cid = player->getCid();
	PlayerScore* pPlayerScore = getPlayerScore( Cid );
	if ( NULL == pPlayerScore ) return;

	++pPlayerScore->nTaskCount;
	pPlayerScore->nScore += nScore;

	m_lstPlayerScore.sort( std::greater<PlayerScore>() );

	addFamilyScore( player->getFamilyId(), player->getFamilyName(), nScore );
	sendPlayerScore( player );
}

int32_t CFamilyWar::GetActivePillar( FamilyId_t nFamilyId )
{
	FamilyScore* pFamilyScore = getFamilyScore( nFamilyId );
	if ( pFamilyScore )
		return pFamilyScore->nActivePillar;
	return 0;
}

int32_t CFamilyWar::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
	if ( NULL == player || NULL == pTargetMap )
	{
		return 10002;
	}
	if ( player->getFamilyId() > 0 )
	{
		return CActivity::canEnter( player, pTargetMap );
	}
	return 10102;
}

PlayerScore* CFamilyWar::getPlayerScore( CharId_t nCharId )
{
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		if ( iter->nCharId == nCharId )
			return &(*iter);
	}
	return NULL;
}

FamilyScore* CFamilyWar::getFamilyScore( FamilyId_t nFamilyId )
{
	for ( FamilyScoreList::iterator iter = m_lstFamilyScore.begin(); iter != m_lstFamilyScore.end(); ++iter )
	{
		if ( iter->nFamilyId == nFamilyId )
			return &(*iter);
	}
	return NULL;
}

void CFamilyWar::sendPlayerScoreRankReward()
{
	int32_t nIndex = 1;
	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end() && nIndex <= 3; ++iter, ++nIndex )
	{
		int32_t nGiftId = 0;
		int32_t nMailId = 0;

		if ( nIndex == 1 )
		{
			if ( m_cfgActivity.gift_id.size() > 0 ) nGiftId = m_cfgActivity.gift_id[0];
			nMailId = 6336;
		}
		else if ( nIndex == 2 )
		{
			if ( m_cfgActivity.gift_id.size() > 1 ) nGiftId = m_cfgActivity.gift_id[1];
			nMailId = 6337;
		}
		else
		{
			if ( m_cfgActivity.gift_id.size() > 2 ) nGiftId = m_cfgActivity.gift_id[2];
			nMailId = 6338;
		}

		if ( nGiftId <= 0 ) continue;

		MemChrBag reward;
		memset( &reward, 0, sizeof(reward) );
		reward.itemId		= nGiftId;
		reward.itemClass	= IC_NORMAL;
		reward.itemCount	= 1;
		reward.bind		= IBS_BIND;

		DB_SERVICE.OnSendSysMail( iter->nCharId, nMailId, reward, "" );
	}
}

void CFamilyWar::sendFamilyScoreRankReward()
{
	int32_t nIndex = 1;
	for ( FamilyScoreList::iterator iter = m_lstFamilyScore.begin(); iter != m_lstFamilyScore.end() && nIndex <= 3; ++iter, ++nIndex )
	{
		int32_t nGiftId = 0;
		int32_t nMailId = 0;

		if ( nIndex == 1 )
		{
			if ( m_cfgActivity.gift_id.size() > 3 ) nGiftId = m_cfgActivity.gift_id[3];
			nMailId = 6339;
		}
		else if ( nIndex == 2 )
		{
			if ( m_cfgActivity.gift_id.size() > 4 ) nGiftId = m_cfgActivity.gift_id[4];
			nMailId = 6340;
		}
		else
		{
			if ( m_cfgActivity.gift_id.size() > 5 ) nGiftId = m_cfgActivity.gift_id[5];
			nMailId = 6341;
		}

		if ( nGiftId <= 0 ) continue;

		MemChrBag reward;
		memset( &reward, 0, sizeof(reward) );
		reward.itemId		= nGiftId;
		reward.itemClass	= IC_NORMAL;
		reward.itemCount	= 1;
		reward.bind		= IBS_BIND;

		DB_SERVICE.OnSendSysMail( 0, nMailId, reward, "" );
	}
}

void CFamilyWar::sendActivePillarReward( FamilyId_t nFamilyId )
{
	if ( m_cfgActivity.gift_id.size() <= 6 ) return;
	MemChrBag reward;
	memset( &reward, 0, sizeof(reward) );
	reward.itemId		= m_cfgActivity.gift_id[6];
	reward.itemClass	= IC_NORMAL;
	reward.itemCount	= 1;
	reward.bind		= IBS_BIND;

	DB_SERVICE.OnSendSysMail( 0, 6342, reward, "" );
}

void CFamilyWar::sendWinnerReward( FamilyId_t nFamilyId )
{
	if ( m_cfgActivity.gift_id.size() <= 7 ) return;
	MemChrBag reward;
	memset( &reward, 0, sizeof(reward) );
	reward.itemId		= m_cfgActivity.gift_id[7];
	reward.itemClass	= IC_NORMAL;
	reward.itemCount	= 1;
	reward.bind		= IBS_BIND;

	DB_SERVICE.OnSendSysMail( 0, 6343, reward, "" );
}

void CFamilyWar::appendPlayerScoreRank( Answer::NetPacket* packet )
{
	if ( NULL == packet ) return;

	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );

	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		if ( iter->nScore <= 0 ) break;

		packet->writeUTF8( iter->strName );
		packet->writeInt32( iter->nScore );

		if ( ++nCount > 9 ) break;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );
}

void CFamilyWar::appendFamilyScoreRank( Answer::NetPacket* packet )
{
	if ( NULL == packet ) return;

	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );

	for ( FamilyScoreList::iterator iter = m_lstFamilyScore.begin(); iter != m_lstFamilyScore.end(); ++iter )
	{
		packet->writeUTF8( iter->strFamilyName );
		packet->writeInt32( iter->nScore );

		if ( ++nCount > 2 ) break;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );
}

void CFamilyWar::sendPlayerScore( Player* player )
{
	if ( NULL == player ) return;

	int8_t nIndex = 0;
	int32_t nScore = 0;
	int8_t nTaskCount = 0;

	for ( PlayerScoreList::iterator iter = m_lstPlayerScore.begin(); iter != m_lstPlayerScore.end(); ++iter )
	{
		++nIndex;
		if ( iter->nCharId == player->getCid() )
		{
			nScore = iter->nScore;
			nTaskCount = (int8_t)iter->nTaskCount;
			break;
		}
	}

	int8_t nFamilyIndex = 0;
	int32_t nFamilyScore = 0;
	for ( FamilyScoreList::iterator iter = m_lstFamilyScore.begin(); iter != m_lstFamilyScore.end(); ++iter )
	{
		++nFamilyIndex;
		if ( iter->nFamilyId == player->getFamilyId() )
		{
			nFamilyScore = iter->nScore - iter->nUsedScore;
			break;
		}
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( 0, PACK_DISPATCH, 0x2E24 );
	if ( NULL == packet ) return;

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt8( nIndex );
	packet->writeInt32( nScore );
	packet->writeInt8( nFamilyIndex );
	packet->writeInt32( nFamilyScore );
	packet->writeInt8( nTaskCount );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}
