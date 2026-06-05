#include "stdafx.h"

#include "Activity.h"
#include "ActivityMap.h"
#include "MonsterActivity.h"
#include "GameService.h"
#include "SkillBuff.h"
#include "Timer.h"
#include "DaTiHD.h"
#include "MapManager.h"
#include <algorithm>

using namespace Answer;

CActivity::CActivity( const CfgActivity& cfgActivity )
:m_cfgActivity( cfgActivity ), m_nState( AS_NOT_START ), m_nBraodcastActivityScoreSign( 0 ), m_nBroadcastActivityScoreTick( 0 ), m_nKickTime( 0 ), m_nLastReviveCheckTick( 0 ), m_nStartTime( 0 )
{
}

CActivity::~CActivity()
{

}

//���ʼ������
void CActivity::Init()
{
	Int32Vector::const_iterator iter = m_cfgActivity.maps.begin();
	Int32Vector::const_iterator eiter = m_cfgActivity.maps.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nMapId = *iter;
		if ( nMapId > 0 )
		{
			Map* pMap = MAP_MANAGER.GetMap( nMapId );
			if( pMap!=NULL && pMap->IsActivityMap() )
			{
				CActivityMap *pActivityMap = dynamic_cast<CActivityMap*>( pMap );
				if ( pActivityMap != NULL )
				{
					m_activityMaps.push_back( pActivityMap );
				}
			}
		}
	}
}

void CActivity::OnUpdate( CActivityMap* pMap )
{
	if ( NULL == pMap )
	{
		return;
	}

	int64_t curTick = pMap->getTick();
	//if ( curTick - m_nBroadcastActivityScoreTick >= 1000 )
	{
		m_nBroadcastActivityScoreTick = curTick;
		BroadcastActivityScore( pMap );
	}

	if ( m_nKickTime > 0 )
	{
		if ( pMap->getNow() >= m_nKickTime )
		{
			PlayerList tList = m_players;
			PlayerList::iterator iter = tList.begin();
			PlayerList::iterator eiter = tList.end();
			for ( ; iter != eiter; ++iter )
			{
				Player* player = *iter;
				if ( player != NULL && player->getMap() == pMap )
				{
					player->leaveActivity();
				}
			}

			if ( m_players.empty() )
			{
				reset();
			}
		}
	}
}

void CActivity::reset()
{
	m_nKickTime						= 0;
	m_nBraodcastActivityScoreSign	= 0;
	m_nBroadcastActivityScoreTick	= 0;
	m_nLastReviveCheckTick			= 0;
	m_nStartTime					= 0;
	m_players.clear();
}

void CActivity::SendPlayerActivityInfo( Player* player )
{

}


void CActivity::SendPlayerActivityState( Player* player )
{

}

void CActivity::SendPlayerActivityScore( Player* player, int32_t nLeftTime )
{

}

void CActivity::BroadcastActivityState()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ONE_ICON );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_cfgActivity.iconid );
	packet->writeInt8(  m_nState );
	packet->writeInt32( getLeftTime() );
	packet->writeInt8( 0 );
	packet->writeInt32( 0 );
	if ( m_nState == AS_RUNNING )
	{
		packet->writeInt8( 1 );
	}
	else
	{
		packet->writeInt8( 0 );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast( packet );	
}

int32_t	CActivity::HaveRewardCount( Player* Player )
{
	return 0;
}

void CActivity::BroadcastActivityScore( CActivityMap* pMap )
{
	if ( NULL == pMap )
	{
		return;
	}

	if ( !needBroadcastActivityScore() )
	{
		return;
	}

	NetPacket* packet = packetActivityScore();
	if ( NULL == packet )
	{
		return;
	}
	pMap->broadcast( packet );
	--m_nBraodcastActivityScoreSign;
}

bool CActivity::OnSitRevive( Player* player )
{
	return false;
}

void CActivity::GetIconState( IconStateList& iconList )
{
	if ( m_nState == AS_TIME_OUT && GetType() != ATI_FAMILY_WAR )
	{
		return;
	}
	
	ShowIcon icon = {};
	icon.nId		= m_cfgActivity.iconid;
	icon.nState		= m_nState;
	icon.nLeftTime	= getLeftTime();
	if ( AS_RUNNING == m_nState )
	{
		icon.Effects = 1;
	}
	if ( m_nState == AS_TIME_OUT && GetType() == ATI_FAMILY_WAR )
	{
		icon.nState = AS_NOT_START;
	}
	iconList.push_back( icon );
}

void CActivity::CheckActivity()
{
	if ( !checkData() )		// ����
	{
		m_nState = AS_TIME_OUT;
		return;
	}
	else if ( m_nState == AS_TIME_OUT)
	{
		m_nState = AS_NOT_START;
	}

	if ( !checkWeek() )
	{
		m_nState = AS_NOT_START;
		return;
	}

	bool bRightLine			= checkLine();
	ACTIVITY_STATE nState	= checkTime();
	switch ( nState )
	{
	case AS_NOT_START:
		{
			if ( m_nState == AS_END )
			{
				m_nState = AS_NOT_START;
			}
			else if ( m_nState == AS_RUNNING )
			{
				if ( bRightLine )
				{
					stopActivity();
					onTimeEnd();
				}
				m_nState = AS_NOT_START;
			}
		}
		break;
	case AS_END:
		{
			if ( m_nState == AS_RUNNING )
			{
				if ( bRightLine )
				{
					stopActivity();
					onTimeEnd();
				}
				m_nState = AS_END;
			}
			m_nState = AS_END;
		}
		break;
	case AS_READY:
		{
			if ( m_nState == AS_END || m_nState == AS_NOT_START )
			{
				m_nState = AS_READY;
				if ( bRightLine )
				{
					BroadcastActivityState();
					broadcastReady();
				}
			}
		}
		break;
	case AS_RUNNING:
		{
			if ( m_nState == AS_READY || m_nState == AS_NOT_START )
			{
				if ( bRightLine )
				{
					startActivity();
					BroadcastActivityState();
					broadcastStart();
				}
				m_nState = AS_RUNNING;
			}
		}
		break;
	default:
		return;
	}
}

void CActivity::startActivity()
{
	reset();
	m_nState = AS_RUNNING;
	for ( ActivityMapList::iterator iter = m_activityMaps.begin(); iter != m_activityMaps.end(); ++iter )
	{
		CActivityMap* pMap = *iter;
		if ( pMap != NULL )
		{
			MAP_MANAGER.PostMsg( pMap->GetRunnerId(), GMC_ACTIVITY_START, pMap, this );
		}
	}
	onActivityStart();
}

void CActivity::stopActivity()
{
	m_nState = AS_END;
	for ( ActivityMapList::iterator iter = m_activityMaps.begin(); iter != m_activityMaps.end(); ++iter )
	{
		CActivityMap* pMap = *iter;
		if ( pMap != NULL )
		{
			MAP_MANAGER.PostMsg( pMap->GetRunnerId(), GMC_ACTIVITY_STOP, pMap, this );
		}
	}
	BroadcastActivityState();
}

void CActivity::broadcastActivityResult()
{

}

void CActivity::onActivityStart()
{

}

void CActivity::onTimeEnd()
{
	m_nState = AS_END;
	delayKickAll( 30 );
}

int32_t	CActivity::getNextStartTime()
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
	int32_t startDays = TIMER.GetDaysFromStart();	// �������Ϸ�������쿪��
	if ( checkData() && checkWeek() )
	{
		if( nowMinute < startMinute )
		{
			days = 0;
		}
	}
	else
	{
		if ( m_cfgActivity.weekday.empty() )
		{
			return 0;
		}
		int32_t weekday = TIMER.GetWeekDay();
		int32_t nextweekday = 0;

		Int32Vector::const_iterator iter = m_cfgActivity.weekday.begin();
		for ( ; iter != m_cfgActivity.weekday.end(); ++iter )
		{
			if ( weekday == *iter )
			{
				++iter;
				break;
			}
		}

		if ( iter == m_cfgActivity.weekday.end() )
		{
			nextweekday = m_cfgActivity.weekday.front();
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

int32_t	CActivity::getLeftTime()
{
	if ( m_cfgActivity.start_hour.empty() )
	{
		return 0;
	}

	int32_t start_hour = m_cfgActivity.start_hour[0];
	int32_t nNowTime = TIMER.GetNow();
	if ( m_nState == AS_RUNNING )
	{
		int32_t startMinute = m_cfgActivity.start_hour[0];
		for ( uint32_t i = 0; i < m_cfgActivity.start_hour.size(); ++i )
		{
			int32_t tend = DayTime::dayzero( nNowTime ) + ( m_cfgActivity.start_hour[i] + m_cfgActivity.duration ) * 60;
			if ( tend > nNowTime )
			{
				startMinute = m_cfgActivity.start_hour[i];
				break;
			}
		}
		int32_t endTime = DayTime::dayzero( nNowTime ) + ( startMinute + m_cfgActivity.duration ) * 60;
		return endTime - nNowTime;
	}
	else
	{
		return getNextStartTime() - nNowTime;
	}
}

int32_t CActivity::getActivityTime()
{
	return m_cfgActivity.duration * 60 - getLeftTime();
}

// ========== �·��� - ���Է������°汾 ==========

bool CActivity::IsRightTime()
{
	return checkTime() == AS_RUNNING;
}

void CActivity::removeActivityMonster( int32_t monsterId )
{
	// ͨ�� GameService ɾ��ָ�� monsterId �Ĺ���
	Monster* pMonster = GAME_SERVICE.getMonster( monsterId, 0 );
	if ( pMonster != NULL )
	{
		pMonster->leaveMap();
		pMonster->destroy();
	}
}

void CActivity::adjustMonsterAttr( CfgMonster* cfgMonster, int32_t nLevel, bool bAutoLow )
{
	if ( NULL == cfgMonster || nLevel <= 0 )
	{
		return;
	}
	if ( cfgMonster->level <= 0 )
	{
		return;
	}
	// 根据等级调整怪物属性
	double fRatio = (double)nLevel / (double)cfgMonster->level;
	cfgMonster->hp = (int32_t)(cfgMonster->hp * fRatio);
	cfgMonster->phy_atk_min = (int32_t)(cfgMonster->phy_atk_min * fRatio);
	cfgMonster->phy_atk_max = (int32_t)(cfgMonster->phy_atk_max * fRatio);
	cfgMonster->mag_atk_min = (int32_t)(cfgMonster->mag_atk_min * fRatio);
	cfgMonster->mag_atk_max = (int32_t)(cfgMonster->mag_atk_max * fRatio);
	cfgMonster->phy_def = (int32_t)(cfgMonster->phy_def * fRatio);
	cfgMonster->mag_def = (int32_t)(cfgMonster->mag_def * fRatio);
	cfgMonster->hitrate = (int32_t)(cfgMonster->hitrate * fRatio);
	cfgMonster->dodge = (int32_t)(cfgMonster->dodge * fRatio);
	cfgMonster->critrate = (int32_t)(cfgMonster->critrate * fRatio);
	if ( bAutoLow )
	{
		// 降低 20% 属性
		cfgMonster->hp = (int32_t)(cfgMonster->hp * 0.8);
		cfgMonster->phy_atk_min = (int32_t)(cfgMonster->phy_atk_min * 0.8);
		cfgMonster->phy_atk_max = (int32_t)(cfgMonster->phy_atk_max * 0.8);
		cfgMonster->mag_atk_min = (int32_t)(cfgMonster->mag_atk_min * 0.8);
		cfgMonster->mag_atk_max = (int32_t)(cfgMonster->mag_atk_max * 0.8);
		cfgMonster->phy_def = (int32_t)(cfgMonster->phy_def * 0.8);
		cfgMonster->mag_def = (int32_t)(cfgMonster->mag_def * 0.8);
		cfgMonster->hitrate = (int32_t)(cfgMonster->hitrate * 0.8);
		cfgMonster->dodge = (int32_t)(cfgMonster->dodge * 0.8);		cfgMonster->critrate = (int32_t)(cfgMonster->critrate * 0.8);
	}
}

bool CActivity::OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t Param )
{
	if ( NULL == player || NULL == pMap )
	{
		return false;
	}

	if ( !pMap->isWalkablePosition( nX, nY ) )
	{
		return false;
	}

	bool bFind = false;
	for ( ActivityMapList::iterator iter = m_activityMaps.begin(); iter != m_activityMaps.end(); ++iter )
	{
		CActivityMap* tp = *iter;
		if ( tp != NULL && tp == pMap )
		{
			bFind = true;
			break;
		}
	}

	if ( bFind )
	{
		return player->switchMap( pMap, nX, nY, true ) == 0;
	}

	return false;
}

void CActivity::addActivityBuff( Unit* pUnit, int32_t nBuffId, bool bClear )
{
	if ( NULL == pUnit )
	{
		return;
	}

	CfgBuff* cfgBuff = CFG_DATA.getBuff( nBuffId );
	if ( NULL == cfgBuff )
	{
		return;
	}

	UnitHandle launcher = pUnit->getHandle();
	SkillBuff* buff = new SkillBuff( *pUnit, *cfgBuff );
	if ( buff != NULL )
	{
		buff->init( cfgBuff->id, 1, launcher, pUnit->getHandle() );
		pUnit->addBuff( buff );
	}
}

bool CActivity::checkRevive( CActivityMap* pMap )
{
	if ( NULL == pMap )
	{
		return false;
	}

	int64_t curTick = TIMER.GetTick();
	if ( curTick - m_nLastReviveCheckTick <= 500 )
	{
		return false;
	}
	m_nLastReviveCheckTick = curTick;

	PlayerList tList = m_players;
	for ( PlayerList::iterator iter = tList.begin(); iter != tList.end(); ++iter )
	{
		Player* player = *iter;
		if ( player != NULL && player->IsDead() && player->getMap() == pMap )
		{
			int32_t nReviveTime = GetRevive( player );
			if ( nReviveTime > 0 && player->getDeadTime() >= nReviveTime )
			{
				player->FillHP();
				player->FillMP();
				Position pos = GetRandBornPos( player );
				player->switchMap( pMap, pos.x, pos.y, true );
			}
		}
	}
	return false;
}

void CActivity::sendSocialUpdateActivityState( int8_t nState )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( m_cfgActivity.iconid );
	packet->writeInt8( nState );
	packet->writeInt32( getLeftTime() );
	packet->writeInt8( 0 );
	packet->writeInt32( 0 );
	packet->writeInt8( nState == AS_RUNNING ? 1 : 0 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacket( packet );
}
bool CActivity::checkData()
{
    return TIMER.BetweenDate( m_cfgActivity.begin_date, m_cfgActivity.end_date );
}

bool CActivity::checkWeek()
{
    return std::find( m_cfgActivity.weekday.begin(), m_cfgActivity.weekday.end(), TIMER.GetWeekDay() ) != m_cfgActivity.weekday.end();
}

ACTIVITY_STATE CActivity::checkTime()
{
    if ( m_cfgActivity.start_hour.empty() )
    {
        return AS_NOT_START;
    }
    const tm& localnow	= TIMER.GetLocalNow();
    int32_t nowMinute	= localnow.tm_hour * 60 + localnow.tm_min;
    int32_t startMinute = m_cfgActivity.start_hour[0];
    int32_t endMinute	= startMinute + m_cfgActivity.duration;
    int32_t readyMinute	= startMinute-5;
    for ( uint32_t i = 0; i < m_cfgActivity.start_hour.size(); ++i )
    {
        if ( nowMinute < readyMinute )
        {
            return AS_NOT_START;
        }
        else if ( nowMinute < startMinute )
        {
            return AS_READY;
        }
        else if ( nowMinute < endMinute )
        {
            return AS_RUNNING;
        }
    }
    return AS_END;
}

bool CActivity::checkLine()
{
    return m_cfgActivity.line == 0 || m_cfgActivity.line == GAME_SERVICE.getLine();
}

Answer::NetPacket* CActivity::packetActivityScore()
{
    return NULL;
}
void CActivity::delayKickAll( int32_t nTime )
{
    m_nKickTime = TIMER.GetNow() + nTime;
}

bool CActivity::needBroadcastActivityScore() const
{
    return m_nBraodcastActivityScoreSign > 0;
}

bool CActivity::IsRuning() const
{
    return m_nState == AS_RUNNING;
}


int32_t CActivity::GetId() const
{
    return m_cfgActivity.id;
}

int16_t CActivity::GetType() const
{
    return m_cfgActivity.typeId;
}

int8_t CActivity::GetState() const
{
    return m_nState;
}

int32_t CActivity::canEnter( Player* player, CActivityMap* pTargetMap ) const
{
    if ( NULL == player || NULL == pTargetMap )
    {
        return ERR_INVALID_DATA;
    }
    if ( !( m_cfgActivity.line == 0 || m_cfgActivity.line == GAME_SERVICE.getLine() ) )
    {
        return ERR_MAP_ACTIVITY_OTHER_LINE;
    }
    if ( m_cfgActivity.level > player->getLevel() )
    {
        return ERR_MAP_PLAYER_LEVEL;
    }
    return ERR_OK;
}

int32_t CActivity::getPkMode() const
{
    return PK_MODE_FREE;
}

bool CActivity::canRevive() const
{
    return true;
}

int32_t CActivity::GiveDailyReward( Player* player )
{
    return ERR_INVALID_DATA;
}

bool CActivity::CanUseXP() const
{
    return true;
}

bool CActivity::CanUsePet( MapId_t mid ) const
{
    return true;
}

void CActivity::onPlantGather( Plant* pPlant, Player *player )
{
}

void CActivity::AddPlant( Plant* plant )
{
}

int32_t CActivity::onBeginGather(  Plant* plant, Player *player )
{
    return ERR_OK;
}

int32_t CActivity::GetRevive( Player* player )
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

void CActivity::removePlayer( Player* player, bool islogout )
{
    for ( PlayerList::iterator iter = m_players.begin(); iter != m_players.end(); ++iter )
    {
        if ( *iter == player )
        {
            m_players.erase( iter );
            return;
        }
    }
}

void CActivity::addPlayer( Player* player )
{
    if ( NULL == player )
    {
        return;
    }
    player->GetPlayerDailyActivity().RecordEnterNumber( m_cfgActivity.typeId, m_cfgActivity.id );
    m_players.push_back( player );
    SendPlayerActivityScore( player, getLeftTime() );
}

Position CActivity::GetRandBornPos( Player* player )
{
    return getBornRandPosA();
}

Position CActivity::getBornRandPosA()
{
    return getBornRandPos( m_cfgActivity.target_mapid, m_cfgActivity.target_regiona );
}

Position CActivity::getBornRandPosB()
{
    return getBornRandPos( m_cfgActivity.target_mapid, m_cfgActivity.target_regionb );
}

Position CActivity::getBornRandPos( int32_t nMapId, const Int32Vector& regions )
{
    Position pos( -1, -1 );
    if( regions.empty() ) 
    {
        return pos;
    }
    Map* pMap = MAP_MANAGER.GetMap( nMapId );
    if ( NULL == pMap )
    {
        return pos;
    }
    int32_t nReginId = -1;
    int32_t lenth = regions.size();
    if( lenth == 1 )
    {
        nReginId = regions[0];
    }
    else
    {
        nReginId = regions[RANDOM.generate( 0, lenth-1 )]; 
    }
    CfgMapRegion *pCfgRegion = CFG_DATA.getMapRegion( nReginId );
    if( NULL == pCfgRegion )
    {
        return pos;
    }
    return pMap->getRandomWalkablePositionInRegion( *pCfgRegion );
}

void CActivity::NotifyActivityInfo( Player* player )
{
}

void CActivity::onMonsterAdd( MonsterActivity* pMonster )
{
}

void CActivity::onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, Player* pAttacker )
{
}

void CActivity::onMonsterDie( MonsterActivity* pMonster )
{
}

void CActivity::onMonsterDie( MonsterActivity* pMonster, Player* pKiller )
{
}

void CActivity::onPlayerKilled( Player* pDier, Player* pKiller )
{
}

void CActivity::broadcastReady()
{
}

void CActivity::broadcastStart()
{
}

void CActivity::setNeedBroadcastActivityScore()
{
    m_nBraodcastActivityScoreSign = m_activityMaps.size();
}


