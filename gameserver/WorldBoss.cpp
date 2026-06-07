#include "WorldBoss.h"
#include "GameService.h"
#include "MapManager.h"
#include "Monster.h"
#include "ActivityManager.h"
#include "DBService.h"
#include "Timer.h"
using namespace Answer;


CWorldBoss::CWorldBoss()
{
	m_WarVictoryBoss = NULL;
	m_lastUpdateTick = 0;
}

CWorldBoss::~CWorldBoss()
{
}

void CWorldBoss::Init(int32_t line)
{
	// 跨服模式下跳过初始化
	if (line == 9)
		return;

	int32_t nNowTime = TIMER.GetNow();

	const BossInfoMap& BossMap = CFG_DATA.GetBossInfoMap();
	for ( BossInfoMap::const_iterator it = BossMap.begin(); it != BossMap.end(); ++it )
	{
		CfgMapMonster* pCfgMapMonster = CFG_DATA.GetMapMonsterInfo( it->first );
		if ( NULL == pCfgMapMonster )
		{
			continue;
		}

		CfgMonster* pMonster = CFG_DATA.getMonster( pCfgMapMonster->monsterid );
		if ( NULL == pMonster )
		{
			continue;
		}
		WorldBossInfo stu;
		stu.nBossId		 = it->first;
		stu.nMid		 = pMonster->mid;
		stu.nBossType	 = pMonster->boss_sign;
		stu.nMapId		 = pCfgMapMonster->mapid;
		stu.nLevel		 = 1;
		if ( stu.nBossType == BOSS_TYPE_SPIDER_QUEEN )
		{
			stu.nState		= 3;
			stu.nReviveTime = 0;
		}
		else
		{
			stu.nState		= 0;
			int32_t ReviveTime = GetBossRevieTime( stu.nBossId );
			if ( ReviveTime <= 0 )
			{
				ReviveTime = CFG_DATA.GetMonsterReviveTime( pMonster->revive_time, pMonster->boss_sign ) / 1000;
			}
			stu.nReviveTime = nNowTime + ReviveTime;
		}
		m_mBossMap[it->first] = stu;
	}

	InitDBInfo();
	InitDropRecord();
}

void CWorldBoss::InitDBInfo()
{
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( "SELECT * FROM `mem_world_boss_info`" );
	while ( !result.eof() )
	{
		int32_t nBossId = result.getIntValue( "id", 0 );
		BoosMap::iterator iter = m_mBossMap.find( nBossId );
		if ( iter != m_mBossMap.end() )
		{
			iter->second.nLevel = result.getIntValue( "level", 0 );
			iter->second.nExp = result.getIntValue( "exp", 0 );
			iter->second.vKiller[0].nCharId = result.getInt64Value( "killer1", 0 );
			iter->second.vKiller[0].strName = result.getStringValue( "killer_name1", "" );
			iter->second.vKiller[0].nTime = result.getIntValue( "kill_time1", 0 );
			iter->second.vKiller[1].nCharId = result.getInt64Value( "killer2", 0 );
			iter->second.vKiller[1].strName = result.getStringValue( "killer_name2", "" );
			iter->second.vKiller[1].nTime = result.getIntValue( "kill_time2", 0 );
			iter->second.vKiller[2].nCharId = result.getInt64Value( "killer3", 0 );
			iter->second.vKiller[2].strName = result.getStringValue( "killer_name3", "" );
			iter->second.vKiller[2].nTime = result.getIntValue( "kill_time3", 0 );
			iter->second.vKiller[3].nCharId = result.getInt64Value( "killer4", 0 );
			iter->second.vKiller[3].strName = result.getStringValue( "killer_name4", "" );
			iter->second.vKiller[3].nTime = result.getIntValue( "kill_time4", 0 );
			iter->second.vKiller[4].nCharId = result.getInt64Value( "killer5", 0 );
			iter->second.vKiller[4].strName = result.getStringValue( "killer_name5", "" );
			iter->second.vKiller[4].nTime = result.getIntValue( "kill_time5", 0 );
		}
		result.nextRow();
	}
}

void CWorldBoss::InitDropRecord()
{
	MySqlDBGuard db(DBPOOL);

	// 加载特殊掉落记录（最多5条）
	int32_t nSize = 0;
	MySqlQuery result = db.query(
		"SELECT * FROM `mem_drop_record` WHERE `special`=1 ORDER BY `time` DESC LIMIT 5" );
	while ( !result.eof() && nSize < 5 )
	{
		DropRecord record;
		record.strName	= result.getStringValue( "name", "" );
		record.nCharId	= result.getInt64Value( "cid", 0 );
		record.nMapId	= result.getIntValue( "mapid", 0 );
		record.nMid		= result.getIntValue( "mid", 0 );
		record.nRecord	= result.getIntValue( "record", 0 );
		record.nTime	= result.getIntValue( "time", 0 );
		record.nSpecial = result.getIntValue( "special", 0 );
		m_dropRecordsSpecial.push_back( record );
		++nSize;
		result.nextRow();
	}

	// 加载普通掉落记录（最多30条）
	nSize = 0;
	result = db.query(
		"SELECT * FROM `mem_drop_record` WHERE `special`=0 ORDER BY `time` DESC LIMIT 30" );
	while ( !result.eof() && nSize < 30 )
	{
		DropRecord record;
		record.strName	= result.getStringValue( "name", "" );
		record.nCharId	= result.getInt64Value( "cid", 0 );
		record.nMapId	= result.getIntValue( "mapid", 0 );
		record.nMid		= result.getIntValue( "mid", 0 );
		record.nRecord	= result.getIntValue( "record", 0 );
		record.nTime	= result.getIntValue( "time", 0 );
		record.nSpecial = result.getIntValue( "special", 0 );
		m_dropRecords.push_back( record );
		++nSize;
		result.nextRow();
	}
}

int32_t CWorldBoss::GetBossRevieTime( int32_t BossId )
{
	BossInfo* pBossInfo = CFG_DATA.GetBossInfo( BossId );
	if ( NULL == pBossInfo )
	{
		return 0;
	}
	if ( pBossInfo->m_NeedResetReviveTime <= 0 )
	{
		return 0;
	}
	int32_t DiffDay = CFG_DATA.getServerDiffTime();
	switch ( DiffDay )
	{
	case 0:		return 5 * 60;
	case 1:		return 10 * 60;
	case 2:		return 20 * 60;
	case 3:		return 30 * 60;
	case 4:		return 40 * 60;
	case 5:		return 50 * 60;
	default:	return 0;
	}
}

Position CWorldBoss::GetRevivePos( int32_t BossId )
{
	Position Pos;
	BossInfo* pBossInfo = CFG_DATA.GetBossInfo( BossId );
	if ( NULL == pBossInfo )
	{
		return Pos;
	}
	std::vector<Position> PosVector = pBossInfo->m_RevivePosVector;
	std::random_shuffle( PosVector.begin(), PosVector.end());
	if ( PosVector.begin() == PosVector.end() )
	{
		return Pos;
	}
	return *(PosVector.begin());
}

void CWorldBoss::PacketBossInfo( Answer::NetPacket *packet, int8_t BossType )
{
	if ( NULL == packet )
	{
		return;
	}
	int32_t nSize = 0;
	int32_t NowTime = TIMER.GetNow();
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt32( nSize );
	packet->writeInt8( BossType );
	for ( BoosMap::iterator it = m_mBossMap.begin(); it != m_mBossMap.end(); ++it )
	{
		if ( it->second.nBossType == BossType )
		{
			BossInfo* pBossInfo = CFG_DATA.GetBossInfo( it->first );
			if ( NULL == pBossInfo )
			{
				continue;
			}
			it->second.PackageBossInfo( packet, NowTime );
			nSize++;
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt32( nSize );
	packet->setWOffset( NewOffset );
}

void CWorldBoss::PacketBossHomeInfo( Answer::NetPacket *packet, int32_t MapId )
{
	if ( NULL == packet )
	{
		return;
	}
	int32_t nSize = 0;
	int32_t NowTime = Answer::DayTime::now();
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt32( nSize );
	packet->writeInt8( BOSS_TYPE_BOSS_HOME );
	for ( BoosMap::iterator it = m_mBossMap.begin(); it != m_mBossMap.end(); ++it )
	{
		if ( it->second.nBossType == BOSS_TYPE_BOSS_HOME && it->second.nMapId == MapId )
		{
			packet->writeInt32( it->second.nBossId );
			packet->writeInt32( it->second.nMid );
			packet->writeInt32( it->second.nMapId );
			if ( it->second.nState )
			{
				packet->writeInt32( it->second.nReviveTime - NowTime );
			}
			else
			{
				packet->writeInt32( 0 );
			}
			if ( it->second.vKiller[0].nCharId > 0 )
			{
				packet->writeInt64( it->second.vKiller[0].nCharId );
				packet->writeUTF8( it->second.vKiller[0].strName );
			}
			else
			{
				packet->writeInt64( 0 );
				packet->writeUTF8( "" );
			}
			nSize++;
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt32( nSize );
	packet->setWOffset( NewOffset );
}

void CWorldBoss::UpdateBossInfo( int32_t BossId, int32_t DieTime, CharId_t KillerId, std::string KillerName, int32_t ReviveTime )
{
	BoosMap::iterator it = m_mBossMap.find( BossId );
	if ( it == m_mBossMap.end() )
	{
		return;
	}

	it->second.nReviveTime = DieTime + ReviveTime;
	if ( KillerId > 0 )
	{
		it->second.vKiller[0].nCharId = KillerId;
		it->second.vKiller[0].strName = KillerName;
		it->second.vKiller[0].nTime = DieTime;
		it->second.nState = 1;
	}
	else
	{
		it->second.nState = 2;
	}

	if ( DieTime > 0 )
	{
		if ( it->second.nBossType == BOSS_TYPE_SPIDER_QUEEN )
		{
			if ( ReviveTime > 0 )
			{
				it->second.nReviveTime = ReviveTime;
			}
			if ( IsAllSpiderQueenDie() )
			{
				ACTIVITY_MANAGER.StopSqiderQueen();
			}
		}
		else
		{
			int32_t nNewRevive = GetBossRevieTime( it->first );
			if ( nNewRevive > 0 )
			{
				it->second.nReviveTime = DieTime + nNewRevive;
			}
		}

		if ( it->second.nBossType == BOSS_TYPE_SPIDER_QUEEN || it->second.nBossType == BOSS_TYPE_WORLD_BOSS )
		{
			if ( KillerId > 0 )
			{
				GongGao( DieTime, it->second.nMid, BossId, it->second.vKiller[0].strName, it->second.nMapId, KillerId );
			}
		}
		if ( it->second.nBossType == BOSS_TYPE_BOSS_HOME )
		{
			Map* pMap = MAP_MANAGER.GetMap( it->second.nMapId );
			if ( NULL != pMap )
			{
				NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_BOSS_CHANGE );
				if ( NULL != packet )
				{
					packet->writeInt32( it->second.nBossId );
					packet->writeInt32( it->second.nMid );
					packet->writeInt32( it->second.nMapId );
					packet->writeInt32( it->second.nState ? (it->second.nReviveTime - Answer::DayTime::now()) : 0 );
					packet->writeInt64( KillerId );
					packet->writeUTF8( KillerName );
					packet->setSize( packet->getWOffset() );
					pMap->broadcast( packet );
				}
			}
		}
	}
}

void CWorldBoss::GongGao( int32_t DieTime, int32_t Mid, int32_t BossId, std::string KillerName, int32_t MapId, CharId_t KillerId )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_BOSS_GONG_GAO );
	if ( NULL == packet )
	{
		return;
	}
	if ( DieTime > 0 )
	{
		packet->writeInt8( 0 );		// 0 = 已击杀
		packet->writeInt32( Mid );
		packet->writeUTF8( KillerName );
		packet->writeInt64( KillerId );
	}
	else
	{
		packet->writeInt8( 1 );		// 1 = 已复活
		packet->writeInt32( Mid );
		packet->writeInt32( BossId );
		packet->writeInt32( MapId );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.broadcast( packet );
}

void CWorldBoss::GetWorldBossIcon( IconStateList& IconList )
{
	ShowIcon stu = {};
	stu.nId			= JI_ZHAN_BOSS;
	stu.nState		= AS_RUNNING;
	stu.nLeftTime	= -1;
	IconList.push_back( stu );
}

void CWorldBoss::SendWorldBossIcon( Player *pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	ShowIcon stu = {};
	stu.nId			= JI_ZHAN_BOSS;
	stu.nState		= AS_RUNNING;
	stu.nLeftTime	= -1;
	pPlayer->SendIconState( &stu );
}

void CWorldBoss::AddMonst( Monster* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}
	m_MonsterList.push_back( pMonster );
}

bool CWorldBoss::IsInHuoDongTiem()
{
	tm LocalNow = DayTime::localnow();
	int32_t Minute = LocalNow.tm_hour * 60 + LocalNow.tm_min;
	for ( int32_t i = 0; i < ReviveTimeCount; i++ )
	{
		if ( Minute >= ReviveTime[i] && Minute <= ReviveTime[i] + REVIVE_TIME )
		{
			return true;
		}
	}
	return false;
}

int32_t CWorldBoss::GetSpiderQueenReviveTime()
{
	tm LocalNow = DayTime::localnow();
	int32_t Minute = LocalNow.tm_hour * 60 + LocalNow.tm_min;
	for ( int32_t i = 0; i < ReviveTimeCount; i++ )
	{
		if ( ReviveTime[i] > Minute )
		{
			return ReviveTime[i];
		}
	}
	return ReviveTime[0];
}

bool CWorldBoss::IsAllSpiderQueenDie()
{
	for ( MonsterList::iterator it = m_MonsterList.begin(); it != m_MonsterList.end(); ++it )
	{
		if ( (*it)->GetHP() > 0 )
		{
			return false;
		}
	}
	return true;
}

void CWorldBoss::KillAllSpiderQueen()
{
	for ( MonsterList::iterator it = m_MonsterList.begin(); it != m_MonsterList.end(); ++it )
	{
		if ( (*it)->GetHP() > 0 )
		{
			Map* pMap = (*it)->getMap();
			if ( NULL != pMap )
			{
				MAP_MANAGER.PostMsg( pMap->GetRunnerId(), GMC_KILL_MONST, pMap, *it );
			}
		}
	}
}

bool CWorldBoss::IsWarVictoryBossTime()
{
	WarVictoryHd* pWarVictory = CFG_DATA.GetWarVictoryHdCfg( 1 );
	if ( NULL == pWarVictory )
	{
		return false;
	}
	int32_t NowTime = Answer::DayTime::now();
	if ( NowTime < pWarVictory->StartTime || NowTime > pWarVictory->EndTime )
	{
		return false;
	}
	tm LocalNow = DayTime::localnow();
	int32_t Minute = LocalNow.tm_hour * 60 + LocalNow.tm_min;
	for ( int32_t i = 0; i < WarVictoryBossReviveTimeCount; i++ )
	{
		if ( Minute >= WarVictoryBossReviveTime[i] && Minute <= WarVictoryBossReviveTime[i] + WAR_VICTORY_BOSS_REVIVE_TIME )
		{
			return true;
		}
	}
	return false;
}

void CWorldBoss::AddWarVictoryBoss( Monster* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}
	m_WarVictoryBoss = pMonster;
}

void CWorldBoss::KillWarVictoryBoss()
{
	if ( NULL == m_WarVictoryBoss )
	{
		return;
	}

	if ( m_WarVictoryBoss->GetHP() > 0 )
	{
		Map* pMap = m_WarVictoryBoss->getMap();
		if ( NULL != pMap )
		{
			MAP_MANAGER.PostMsg( pMap->GetRunnerId(), GMC_KILL_MONST, pMap, m_WarVictoryBoss );
			GongGao( BCI_WAR_VICTORY_BOSS_LEAVE );
		}
	}
}

void CWorldBoss::Update( int64_t CurTick )
{
	if ( CurTick - m_lastUpdateTick > 1000 )
	{
		m_lastUpdateTick = CurTick;
	}
	if ( NULL == m_WarVictoryBoss )
	{
		return;
	}
	if ( !IsWarVictoryBossTime() )
	{
		KillWarVictoryBoss();
	}
}

void CWorldBoss::GongGao( int32_t GongGaoId, Player* pPlayer )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( GongGaoId );
	if ( GongGaoId == BCI_WAR_VICTORY_BOSS_KILLED )
	{
		if ( pPlayer != NULL )
		{
			packet->writeUTF8( pPlayer->getName() );
			packet->writeInt64( pPlayer->getCid() );
		}
		else
		{
			packet->writeUTF8( "" );
			packet->writeInt64( 0 );
		}
	}
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_NOTICE_PARAM );
	GAME_SERVICE.worldBroadcast( packet );
}

// ============================================================
// 2019新增方法
// ============================================================

int32_t CWorldBoss::GetBossLevel( int32_t nBossId )
{
	Answer::MutexGuard lock( m_Lock );
	BoosMap::iterator iter = m_mBossMap.find( nBossId );
	if ( iter != m_mBossMap.end() )
	{
		return iter->second.nLevel;
	}
	return 0;
}

void CWorldBoss::adjustBossAttr( CfgMonster* cfgMonster, int32_t nLevel )
{
	if ( NULL == cfgMonster )
	{
		return;
	}
	CfgMonsterAdjust* pCfgAdjust = CFG_DATA.GetMonsterAdjust( cfgMonster->mid, nLevel, 0 );
	if ( pCfgAdjust )
	{
		cfgMonster->level = pCfgAdjust->level;
		// vAttr 映射到 CfgMonster 字段（按标准顺序：hp, phy_atk_min, phy_atk_max, mag_atk_min, mag_atk_max, phy_def, mag_def, ...）
		if ( pCfgAdjust->vAttr[0] ) cfgMonster->hp				= pCfgAdjust->vAttr[0];
		if ( pCfgAdjust->vAttr[1] ) cfgMonster->phy_atk_min	= pCfgAdjust->vAttr[1];
		if ( pCfgAdjust->vAttr[2] ) cfgMonster->phy_atk_max	= pCfgAdjust->vAttr[2];
		if ( pCfgAdjust->vAttr[3] ) cfgMonster->mag_atk_min	= pCfgAdjust->vAttr[3];
		if ( pCfgAdjust->vAttr[4] ) cfgMonster->mag_atk_max	= pCfgAdjust->vAttr[4];
		if ( pCfgAdjust->vAttr[5] ) cfgMonster->phy_def		= pCfgAdjust->vAttr[5];
		if ( pCfgAdjust->vAttr[6] ) cfgMonster->mag_def		= pCfgAdjust->vAttr[6];
	}
}

void CWorldBoss::OnAddBoss( Map* pMap, const CfgMonster* cfgMonster, const CfgMapMonster* cfgMapMonster )
{
	if ( NULL == pMap )
	{
		return;
	}

	int32_t nBossId = cfgMapMonster->id;
	int32_t nLevel = GetBossLevel( nBossId );
	if ( nLevel <= 0 || GAME_SERVICE.getLine() == 1 )
	{
		CfgMonster tCfgMonster = *cfgMonster;
		int8_t nState = 0;
		Monster* pMonster = POOL_MANAGER.pop<Monster>();
		if ( pMonster )
		{
			if ( nLevel > 0 )
			{
				adjustBossAttr( &tCfgMonster, nLevel );
			}
			if ( tCfgMonster.boss_sign != BOSS_TYPE_SPIDER_QUEEN )
			{
				pMonster->init( tCfgMonster, *cfgMapMonster );
			}
			pMap->addMonster( pMonster, cfgMapMonster->x, cfgMapMonster->y );
			Answer::MutexGuard lock( m_Lock );
			BoosMap::iterator iter = m_mBossMap.find( nBossId );
			if ( iter != m_mBossMap.end() )
			{
				iter->second.nState = nState;
			}
		}
	}
}

void CWorldBoss::OnBossSummon( int32_t nBossId, Map* pMap, Monster* pMonster )
{
	if ( NULL == pMonster )
	{
		return;
	}

	WorldBossInfo info;
	bool bFind = false;

	{
		Answer::MutexGuard lock( m_Lock );
		BoosMap::iterator iter = m_mBossMap.find( nBossId );
		if ( iter != m_mBossMap.end() )
		{
			iter->second.nState = 0;
			info = iter->second;
			bFind = true;
		}
	}

	if ( bFind )
	{
		broadcastBossRevive( info.nMid, info.nBossId, info.nMapId );
		saveBossInfo( info );
	}
}

void CWorldBoss::OnBossKilled( int32_t nBossId, int32_t nNowTime, Map* pMap, Monster* pMonster, Player* pKiller )
{
	if ( NULL == pMap || NULL == pMonster )
	{
		return;
	}

	WorldBossInfo info;
	KillerInfo killer;
	bool bFind = false;
	bool bLevelUp = false;

	{
		Answer::MutexGuard lock( m_Lock );
		BoosMap::iterator iter = m_mBossMap.find( nBossId );
		if ( iter != m_mBossMap.end() )
		{
			if ( pKiller )
			{
				iter->second.nState = 1;
				killer.nCharId = pKiller->getCid();
				killer.strName = pKiller->getName();
				killer.nTime = nNowTime;
				iter->second.AddKiller( killer );

				// 检查是否升级
				int32_t nLevel = iter->second.nLevel;
				int32_t nMid = iter->second.nMid;
				CfgMonsterAdjust* pCfgAdjust = CFG_DATA.GetMonsterAdjust( nMid, nLevel, 0 );
				CfgMonsterAdjust* pNext = CFG_DATA.GetMonsterAdjust( nMid, nLevel + 1, 0 );
				if ( pCfgAdjust && pNext )
				{
					++iter->second.nExp;
					if ( iter->second.nExp >= pCfgAdjust->exp )
					{
						bLevelUp = true;
						++iter->second.nLevel;
						iter->second.nExp -= pCfgAdjust->exp;
					}
				}
			}
			else
			{
				iter->second.nState = 2;
			}

			// 计算复活时间
			int32_t nReviveTime = GetBossRevieTime( iter->second.nBossId );
			if ( nReviveTime <= 0 )
			{
				CfgMonster* pMonsterCfg = CFG_DATA.getMonster( iter->second.nMid );
				if ( pMonsterCfg )
				{
					nReviveTime = CFG_DATA.GetMonsterReviveTime( pMonsterCfg->revive_time, pMonsterCfg->boss_sign ) / 1000;
				}
			}
			iter->second.nReviveTime = nNowTime + nReviveTime;
			info = iter->second;
			bFind = true;
		}
	}

	if ( bFind )
	{
		if ( bLevelUp )
		{
			CfgMonster* pCfgMonster = CFG_DATA.getMonster( info.nMid );
			if ( pCfgMonster )
			{
				CfgMonster tCfgMonster = *pCfgMonster;
				adjustBossAttr( &tCfgMonster, info.nLevel );
				pMonster->OnLevelUp( tCfgMonster );
			}
		}

		pMonster->SetReviveTime( info.nReviveTime );

		if ( info.nBossType == BOSS_TYPE_SPIDER_QUEEN && pKiller )
		{
			broadcastBossKilled( info.nMid, pKiller->getName(), pKiller->getCid() );
		}
		if ( info.nBossType == BOSS_TYPE_WORLD_BOSS )
		{
			if ( pKiller )
			{
				broadcastBossKilled( info.nMid, pKiller->getName(), pKiller->getCid() );
			}
		}
		else if ( info.nBossType == 12 ) // BOSS_TYPE_RUINS
		{
			int32_t nNow = TIMER.GetNow();
			UpdateRuinsBossInfo( pMap, info, nNow );
		}

		saveBossInfo( info );
	}
}

void CWorldBoss::broadcastBossKilled( int32_t nMid, const std::string& strKillerName, CharId_t nKillerId )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_BOSS_GONG_GAO );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt8( 0 );		// 0 = 已击杀
	packet->writeInt32( nMid );
	packet->writeUTF8( strKillerName );
	packet->writeInt64( nKillerId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.broadcast( packet );
}

void CWorldBoss::broadcastBossRevive( int32_t nMid, int32_t nBossId, int32_t nMapId )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_BOSS_GONG_GAO );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt8( 1 );		// 1 = 已复活
	packet->writeInt32( nMid );
	packet->writeInt32( nBossId );
	packet->writeInt32( nMapId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.broadcast( packet );
}

int32_t CWorldBoss::GetBossRevie( int32_t nBossId )
{
	int32_t NowTime = TIMER.GetNow();

	Answer::MutexGuard lock( m_Lock );
	BoosMap::iterator it = m_mBossMap.find( nBossId );
	if ( it != m_mBossMap.end() )
	{
		if ( it->second.nState == 0 )
		{
			return 0;	// BOSS 存活中
		}
		int32_t nReviveTime = it->second.nReviveTime - NowTime;
		if ( nReviveTime < 0 )
		{
			nReviveTime = 0;
		}
		return nReviveTime;
	}
	return 0;
}

void CWorldBoss::UpdateWorldBossInfo( const WorldBossInfo& info )
{
	Answer::MutexGuard lock( m_Lock );
	BoosMap::iterator iter = m_mBossMap.find( info.nBossId );
	if ( iter != m_mBossMap.end() )
	{
		iter->second = info;
	}
}

void CWorldBoss::saveBossInfo( const WorldBossInfo& info )
{
	DB_SERVICE.SaveWorldBossInfo( info );
}

void CWorldBoss::AddDropRecord( const std::string& name, CharId_t cid, MapId_t mapid, int32_t mid, int32_t record, int32_t time )
{
	const CfgDropRecord* pCfgRecord = CFG_DATA.GetDropRecord( record );
	if ( NULL == pCfgRecord )
	{
		return;
	}

	DropRecord dropRecord( name, cid, mapid, mid, record, time, pCfgRecord->nSpecial );
	if ( pCfgRecord->nSpecial )
	{
		Answer::MutexGuard lock( m_RecordLock );
		m_dropRecordsSpecial.push_front( dropRecord );
		if ( m_dropRecordsSpecial.size() > 5 )
		{
			m_dropRecordsSpecial.pop_back();
		}
	}
	else
	{
		Answer::MutexGuard lock( m_RecordLock );
		m_dropRecords.push_front( dropRecord );
		if ( m_dropRecords.size() + m_dropRecordsSpecial.size() > 30 )
		{
			m_dropRecords.pop_back();
		}
	}

	DB_SERVICE.SaveDropRecord( dropRecord );
}

void CWorldBoss::SendDropRecord( int8_t connid, int16_t nGateIndex )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, SM_SEND_DROP_RECORD );
	if ( NULL == packet )
	{
		return;
	}

	Answer::MutexGuard lock( m_RecordLock );
	int16_t nTotal = static_cast<int16_t>( m_dropRecords.size() + m_dropRecordsSpecial.size() );
	packet->writeInt16( nTotal );

	// 先写特殊记录
	for ( std::list<DropRecord>::const_iterator iter = m_dropRecordsSpecial.begin();
		  iter != m_dropRecordsSpecial.end(); ++iter )
	{
		packet->writeInt32( iter->nRecord );
		packet->writeUTF8( iter->strName );
		packet->writeInt64( iter->nCharId );
		packet->writeInt32( iter->nMapId );
		packet->writeInt32( iter->nMid );
		packet->writeInt32( iter->nTime );
	}

	// 再写普通记录
	for ( std::list<DropRecord>::const_iterator iter = m_dropRecords.begin();
		  iter != m_dropRecords.end(); ++iter )
	{
		packet->writeInt32( iter->nRecord );
		packet->writeUTF8( iter->strName );
		packet->writeInt64( iter->nCharId );
		packet->writeInt32( iter->nMapId );
		packet->writeInt32( iter->nMid );
		packet->writeInt32( iter->nTime );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( connid, nGateIndex, packet );
}

void CWorldBoss::SendRuinsBossInfo( Player* player, int32_t nBossType, int32_t nMapId )
{
	if ( NULL == player )
	{
		return;
	}

	int8_t connid = (int8_t)player->getConnId();
	NetPacket *packet = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, SM_SEND_RUINS_BOSS_INFO );
	if ( NULL == packet )
	{
		return;
	}

	int8_t nSize = 0;
	int32_t NowTime = TIMER.GetNow();
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt8( 0 );	// 占位，后面回填nSize
	for ( BoosMap::iterator it = m_mBossMap.begin(); it != m_mBossMap.end(); ++it )
	{
		if ( it->second.nBossType == nBossType && it->second.nMapId == nMapId )
		{
			packet->writeInt32( it->second.nBossId );
			packet->writeInt32( it->second.nMid );
			packet->writeInt32( it->second.nMapId );
			if ( it->second.nState )
			{
				packet->writeInt32( it->second.nReviveTime - NowTime );
			}
			else
			{
				packet->writeInt32( 0 );
			}
			++nSize;
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt8( nSize );
	packet->setWOffset( NewOffset );
	packet->setSize( NewOffset );
	GAME_SERVICE.sendPacketTo( connid, player->getGateIndex(), packet );
}

void CWorldBoss::UpdateRuinsBossInfo( Map* pMap, const WorldBossInfo& info, int32_t nNowTime )
{
	if ( NULL == pMap )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_RUINS_BOSS_CHANGE );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( info.nBossId );
	packet->writeInt32( info.nMid );
	packet->writeInt32( info.nMapId );
	if ( info.nState )
	{
		packet->writeInt32( info.nReviveTime - nNowTime );
	}
	else
	{
		packet->writeInt32( 0 );
	}
	packet->setSize( packet->getWOffset() );
	pMap->broadcast( packet );
}

// ============================================================
// WorldBossInfo 方法实现
// ============================================================

void WorldBossInfo::PackageBossInfo( Answer::NetPacket* packet, int32_t nNowTime ) const
{
	packet->writeInt32( nBossId );
	packet->writeInt32( nMid );
	packet->writeInt32( nMapId );
	packet->writeInt8( nState );
	packet->writeInt32( nState ? (nReviveTime - nNowTime) : 0 );

	// 击杀者列表（Top5）
	int32_t nCount = 0;
	int32_t nOldOffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( int32_t i = 0; i < 5; ++i )
	{
		if ( vKiller[i].nCharId > 0 )
		{
			packet->writeInt64( vKiller[i].nCharId );
			packet->writeUTF8( vKiller[i].strName );
			packet->writeInt32( vKiller[i].nTime );
			nCount++;
		}
	}
	packet->writeInt32( nLevel );
	packet->writeInt32( nExp );

	int32_t nNewOffset = packet->getWOffset();
	packet->setWOffset( nOldOffset );
	packet->writeInt32( nCount );
	packet->setWOffset( nNewOffset );
}

void WorldBossInfo::AddKiller( const KillerInfo& info )
{
	bool bFind = false;
	for ( int32_t i = 0; i < 5; ++i )
	{
		if ( vKiller[i].nCharId == 0 )
		{
			vKiller[i] = info;
			bFind = true;
			break;
		}
	}
	if ( !bFind )
	{
		// 全部满了，移除第一个，后移并追加
		for ( int32_t i = 0; i < 4; ++i )
		{
			vKiller[i] = vKiller[i + 1];
		}
		vKiller[4] = info;
	}
}
