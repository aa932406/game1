
#include "FamilyWar.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
#include "ActivityMap.h"
#include "FamilyManager.h"
#include "ActivityManager.h"
#include "KaiFuHuoDong.h"
using namespace Answer;

CFamilyWar::CFamilyWar( const CfgActivity& cfgActivity )
:CActivity( cfgActivity ), m_pSton( NULL ), m_pPillar( NULL ), m_nGuidFamily( 0 ), m_nWinTimes( 0 )
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
	string leadyername= "";	
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
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		PlayerScore& score = iter->second;
		if ( score.bInActivity && score.nJoinExp == 0 )
		{
			if ( ( curTick - score.nStartTick ) / 1000 + score.nSeconds >= 900 )
			{
				Player* pPlayer = GAME_SERVICE.getPlayer( score.nCharId, pMap->GetRunnerId() );
				if ( pPlayer != NULL )
				{
					int32_t nExp = CFG_DATA.GetFamilyWarJoinRewardTable().GetReward( pPlayer->getLevel() );
					pPlayer->addExp( nExp );
					score.nJoinExp = nExp;
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

	m_lstFamilyScore.clear();
	m_mPlayerScore.clear();
}

bool CFamilyWar::checkData()
{
	int32_t startDays = TIMER.GetDaysFromStart();	// 开服、合服后第三天开启
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
	int32_t startDays = TIMER.GetDaysFromStart();	// 开服、合服后第三天开启
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
		int32_t nAddExp = nDamage;		// 原来要除10;
		pAttacker->addExp( nAddExp );
		addPlayerScore( pAttacker, nAddExp, 0, 0 );
	}
	else if ( pMonster == m_pPillar )
	{
		int32_t nAddMoney = nDamage / 10;
		pAttacker->AddCurrency( CURRENCY_MONEY, nDamage / 10, MCR_ATTACK_FAMIWAR_PILLAR );
		addPlayerScore( pAttacker, 0, nAddMoney, 0 );
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

	if ( m_pPillar == pMonster )
	{
		FamilyId_t nFamilyId = 0;
		if ( !m_lstFamilyScore.empty() )
		{
			nFamilyId = m_lstFamilyScore.front().nFamilyId;
			m_lstFamilyScore.clear();
			setNeedBroadcastActivityScore();
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

	addPlayerScore( pAttacker, 0, 0, 1 );
}

void CFamilyWar::onMonsterAdd( MonsterActivity* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}

	if ( pMonster->getActivityMonsterId() == ACTICITY_MONSTER_ID_FAMILY_WAR_STON )
	{
		m_pSton = pMonster;
	}
	else if ( pMonster->getActivityMonsterId() == ACTICITY_MONSTER_ID_FAMILY_WAR_PILLAR )
	{
		m_pPillar = pMonster;
	}

	pMonster->SetFamilyId( m_nGuidFamily );
}

void CFamilyWar::addPlayer( Player* player )
{
	CActivity::addPlayer( player );
	if ( NULL == player )
	{
		return;
	}

	// 设置PK模式
	if ( player->getFamilyId() > 0 )
	{
		player->setPkMode( PK_MODE_LEGION, false );
	}
	else
	{
		player->setPkMode( PK_MODE_ALL, false );
	}

	// 添加BUFF
	addBuff( player );

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.bInActivity = true;
		iter->second.nStartTick = player->getTick();
	}
	else
	{
		PlayerScore score = {};
		score.nCharId	= player->getCid();
		score.nFamilyId	= player->getFamilyId();
		score.bInActivity = true;
		score.nStartTick = player->getTick();
		m_mPlayerScore.insert( PlayerScoreMap::value_type( score.nCharId, score ) );
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
	removeBuff(player);
	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.bInActivity = false;
		iter->second.nSeconds += static_cast<int32_t>( ( player->getTick() - iter->second.nStartTick ) / 1000 );
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
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_NOTIFY_FAMILYWAR_INFO );
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
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_INFO );
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
		GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
	}
}


void CFamilyWar::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
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

void CFamilyWar::addPlayerScore( Player* player, int32_t nExp, int32_t nMoney, int32_t nKillCount )
{
	if ( NULL == player )
	{
		return;
	}

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter != m_mPlayerScore.end() )
	{
		iter->second.nExp		+= nExp;
		iter->second.nMoney		+= nMoney;
		iter->second.nKillCount	+= nKillCount;

		NetPacket* packet = packetActivityPlayerScore( player );
		if ( NULL == packet )
		{
			return;
		}
		GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
	}
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
		m_lstFamilyScore.push_back( score );
	}
	m_lstFamilyScore.sort(std::greater<FamilyScore>());
	setNeedBroadcastActivityScore();
}

void CFamilyWar::win( FamilyId_t nFamilyId )
{
	// 结束
	if ( m_nGuidFamily != nFamilyId )
	{
		FirstFamilyWar( nFamilyId );
		m_nWinTimes = 0;
		m_nGuidFamily = nFamilyId;
	}
	++m_nWinTimes;
	m_nState = AS_END;
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
	PlayerScoreMap::iterator iter = m_mPlayerScore.begin();
	PlayerScoreMap::iterator eiter = m_mPlayerScore.end();
	for ( ; iter != eiter; ++iter )
	{
		const PlayerScore& score = iter->second;
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
	PlayerScoreMap::iterator iter = m_mPlayerScore.begin();
	PlayerScoreMap::iterator eiter = m_mPlayerScore.end();
	for ( ; iter != eiter; ++iter )
	{
		const PlayerScore& score = iter->second;
		if ( score.bInActivity )
		{
			Player* player = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
			if ( player != NULL )
			{
				int32_t nGiftId = 0;
				if ( m_nGuidFamily > 0 && m_nGuidFamily == player->getFamilyId() )
				{
					nGiftId = m_cfgActivity.gift_id[ player->getFamilyPosition() ];
				}
				else if ( score.nKillCount > 0 )
				{
					nGiftId = m_cfgActivity.gift_id[10];
				}
				else
				{
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
				if ( isDoubleReward() )	// 双倍奖励发两个
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
	for ( PlayerScoreMap::iterator iter = m_mPlayerScore.begin(); iter != m_mPlayerScore.end(); ++iter )
	{
		PlayerScore& score = iter->second;
		if ( score.bInActivity )
		{
			Player* pPlayer = GAME_SERVICE.getPlayer( score.nCharId, 0, false );
			if ( pPlayer != NULL )
			{
				NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_RESULT );
				if ( NULL == packet )
				{
					return;
				}

				packet->writeInt32( m_cfgActivity.id );
				packet->writeInt64( m_nGuidFamily );
				FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( m_nGuidFamily );
				packet->writeUTF8( familyInfo.strName );
				packet->writeInt32( score.nJoinExp );
				packet->writeInt8( isDoubleReward() ? 1 : 0 );

				packet->setSize( packet->getWOffset() );
				GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
			}
		}
	}
}

void CFamilyWar::onTimeEnd()
{
	if ( m_pPillar != NULL )
	{
		win( m_pPillar->GetFamilyId() );
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
	int32_t startDays = TIMER.GetDaysFromStart();	// 开服、合服后第三天开启
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
	return packetActivityFamilyScore();
}

Answer::NetPacket* CFamilyWar::packetActivityFamilyScore()
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_FAMILY_SCORE );
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

	PlayerScoreMap::iterator iter = m_mPlayerScore.find( player->getCid() );
	if ( iter == m_mPlayerScore.end() )
	{
		return NULL;
	}

	const PlayerScore& score = iter->second;
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_PLAYER_SCORE );
	if ( NULL == packet )
	{
		return NULL;
	}

	packet->writeInt32( m_cfgActivity.id );
	packet->writeInt32( score.nExp );
	packet->writeInt32( score.nMoney );
	packet->writeInt32( score.nKillCount );

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

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_FAMILY_WAR_PILLAR_INFP );
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
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
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
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_WORLD_FAMILYWAR_READY );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CFamilyWar::broadcastStart()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_WORLD_FAMILYWAR_START );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CFamilyWar::broadcastPillerKilled( FamilyId_t nFamilyId )
{
	if ( nFamilyId > 0 )
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( BCI_WORLD_FAMILYWAR_PILLAR_KILLED_BY_FAMILY );
		FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( nFamilyId );
		packet->writeUTF8( familyInfo.strName );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast(packet);
	}
	else
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( BCI_WORLD_FAMILYWAR_PILLAR_KILLED_BY_FREE );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.worldBroadcast(packet);
	}
}

void CFamilyWar::broadcastStoneKilled()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_WORLD_FAMILYWAR_STONE_KILLED );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CFamilyWar::broadcastWin()
{
	if ( m_nGuidFamily > 0 )
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( BCI_WORLD_FAMILYWAR_WIN );
		FamilyInfo familyInfo = FAMILY_MANAGER.GetFamilyInfo( m_nGuidFamily );
		packet->writeUTF8( familyInfo.strName );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(packet);
	}
	else
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( BCI_WORLD_FAMILYWAR_FAIL );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(packet);
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
	CfgBuff *cfgBuff = CFG_DATA.getBuff( ACTIVITY_FAMILY_WAR_BUFF_ID );
	if ( cfgBuff != NULL )
	{
		SkillBuff *buff = new SkillBuff( *player, *cfgBuff );
		if (NULL == buff)
		{
			return;
		}
		buff->init( cfgBuff->id, nBuffLevel, player->getHandle(), player->getHandle() );
		player->addBuff( buff );
	}
}

void CFamilyWar::removeBuff( Player* player )
{
	if ( player != NULL )
	{
		player->removeBuff( ACTIVITY_FAMILY_WAR_BUFF_ID );
	}
}

bool CFamilyWar::isDoubleReward() const
{
	int32_t startDays = TIMER.GetDaysFromStart();	// 开服、合服后第三天双倍奖励
	return startDays <= 2;
}

bool CFamilyWar::isShowDoubleReward()
{
	int32_t startDays = TIMER.GetDaysFromStart();	// 开服、合服后第三天双倍奖励
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

std::string	CFamilyWar::GetFamilyLeaderName()
{
	return m_FamilyLeaderName;
}

void CFamilyWar::NotifyActivityInfo( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_FAMILY_WAR_WIN_FAMILY );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64( m_nGuidFamily );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.worldBroadcast(packet);
	}
	else
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_FAMILY_WAR_WIN_FAMILY );
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt64( m_nGuidFamily );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);
	}
}
