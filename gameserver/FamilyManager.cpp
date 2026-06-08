#include "stdafx.h"

#include "CfgData.h"
#include "FamilyManager.h"
#include "GameService.h"
#include "MapManager.h"
#include "Dungeon.h"
#include "Timer.h"
#include <string>
#include <algorithm>
using namespace Answer;

FamilyManager::FamilyManager()
{
}

FamilyManager::~FamilyManager()
{
}

void FamilyManager::Init(int32_t line)
{
	// 跨服模式下跳过初始化
	if (line == 9)
		return;

	// 初始化军团
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_family` WHERE `delflag`=0");
	MySqlQuery result = db.query(szSQL);

	int32_t nNowTime = TIMER.GetNow();
	while ( !result.eof() )
	{
		FamilyInfo info;
		info.nId				= result.getInt64Value("id");
		info.strName			= result.getStringValue("name");
		info.nLevel				= result.getIntValue("level");
		info.nMemberCard		= (int8_t)result.getIntValue("member_card", 0);
		info.FamilyLeaderCid	= result.getInt64Value("leader_cid", 0);
		info.MedalLevel			= result.getIntValue("medl_level", 0);
		info.Territory			= (int8_t)result.getIntValue("territory_open", 0);

		// 查找族长名字
		if ( info.FamilyLeaderCid > 0 )
		{
			char szLeaderSQL[MAX_SQL_LENGTH] = {};
			snprintf(szLeaderSQL, sizeof(szLeaderSQL)-1, "SELECT name FROM `mem_character` WHERE `cid`=%lld", info.FamilyLeaderCid);
			MySqlQuery Leaderdb = db.query(szLeaderSQL);
			if ( !Leaderdb.eof() )
			{
				info.FamilyLeaderName = Leaderdb.getStringValue("name", "");
			}
		}

		// 图腾增加战斗力
		bzero( szSQL, sizeof( szSQL ) );
		snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_family_totom` WHERE `family_id`=%lld", info.nId );
		MySqlQuery totoms = db.query(szSQL);
		while ( !totoms.eof() )
		{
			int32_t startTime = totoms.getIntValue("start_time");
			int32_t addBattle = totoms.getIntValue("battle");
			if ( nNowTime - startTime <= FAMILY_TOTOM_ACTIVE_TIME && addBattle > 0 )
			{
				info.nAddBattle	+= addBattle;
			}
			info.OpenedTotom.insert( totoms.getIntValue("totom_id") );
			totoms.nextRow();
		}

		m_mFamilyInfo[info.nId] = info;
		result.nextRow();
	}

	// 加载家族副本数据
	MySqlQuery result2 = db.query("SELECT * FROM `mem_family_dungeon`");
	while ( !result2.eof() )
	{
		FamilyId_t nFamilyId = result2.getInt64Value("id");
		FamilyDungeonStu stu;
		stu.StartCounts	= result2.getIntValue("times", 0);
		stu.StartTime	= result2.getIntValue("start_time", 0);
		stu.nMaxHard	= result2.getIntValue("finish_hard", 0);
		m_FamilyDungeonStuMap[nFamilyId] = stu;
		result2.nextRow();
	}
}

void FamilyManager::OnUpdateFamilyInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	int8_t	nReason = inPacket->readInt8();
	FamilyInfo info;
	info.UnPackageData( inPacket );

	switch ( nReason )
	{
	case FUR_CREATE:
		{
			addFamilyInfo( info );
			break;
		}
	case FUR_UPDATE:
		{
			updateFamilyInfo( info );
			break;
		}
	case FUR_DELETE:
		{
			deleteFamilyInfo( info.nId );
			break;
		}
	}
}

void FamilyManager::OnInitFamilyInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	FamilyInfo info;
	int32_t size = inPacket->readInt32();
	for ( int32_t i = 0; i < size; ++i )
	{
		info.CleanUp();
		info.UnPackageData( inPacket );
		addFamilyInfo( info );
	}
}

FamilyInfo FamilyManager::GetFamilyInfo( FamilyId_t nId )
{
	FamilyInfo info;
	{
		Answer::MutexGuard lock( m_Lock );
		FamilyInfoMap::iterator iter = m_mFamilyInfo.find( nId );
		if ( iter != m_mFamilyInfo.end() )
		{
			return iter->second;
		}
	}
	return info;
}

int8_t FamilyManager::GetTerritoryState( FamilyId_t nFamilyId )
{
	int8_t Territory = 0;
	Answer::MutexGuard lock( m_Lock );
	FamilyInfoMap::iterator it = m_mFamilyInfo.find( nFamilyId );
	if ( it != m_mFamilyInfo.end() )
	{
		Territory = it->second.Territory;
	}
	return Territory;
}

int32_t FamilyManager::GetMedlLevel( FamilyId_t nFamilyId )
{
	int32_t MedalLevel = 0;
	Answer::MutexGuard lock( m_Lock );
	FamilyInfoMap::iterator it = m_mFamilyInfo.find( nFamilyId );
	if ( it != m_mFamilyInfo.end() )
	{
		MedalLevel = it->second.MedalLevel;
	}
	return MedalLevel;
}

bool FamilyManager::StartfamilyDungeon( FamilyId_t nFamilyId, int32_t DungeonId, int32_t Hard )
{
	if ( Hard <= 0 || Hard > 5 )
	{
		return false;
	}

	// 检查是否已有进行中的副本
	FamilyDungeonMap::iterator itDun = m_FamilyDungeonMap.find( nFamilyId );
	if ( itDun != m_FamilyDungeonMap.end() )
	{
		return false;
	}

	// 检查副本数据
	FamilyDungeonStuMap::iterator it = m_FamilyDungeonStuMap.find( nFamilyId );
	if ( it != m_FamilyDungeonStuMap.end() )
	{
		// 同一天内不能重复启动
		if ( !Answer::DayTime::daydiff( it->second.StartTime ) )
		{
			return false;
		}
		// 已启动超过1次
		if ( it->second.StartCounts > 1 )
		{
			return false;
		}
		// 难度不能跳级
		if ( it->second.nMaxHard + 1 < Hard )
		{
			return false;
		}
	}
	else
	{
		// 首次必须从难度1开始
		if ( Hard != 1 )
		{
			return false;
		}
	}

	// 创建副本
	Dungeon* pDungeon = MAP_MANAGER.NewDungeon( DungeonId );
	if ( NULL == pDungeon )
	{
		return false;
	}

	pDungeon->SetHard( Hard );
	pDungeon->SetFamilyId( nFamilyId );
	pDungeon->start( 0 );
	int32_t RunnerId = pDungeon->GetRunnerId();
	MAP_MANAGER.PostMsg( RunnerId, GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0 );

	// 更新副本数据
	if ( it != m_FamilyDungeonStuMap.end() )
	{
		++it->second.StartCounts;
		it->second.StartTime = Answer::DayTime::now();
	}
	else
	{
		FamilyDungeonStu stu;
		stu.StartCounts = 1;
		stu.StartTime = Answer::DayTime::now();
		stu.nMaxHard = 0;
		m_FamilyDungeonStuMap[nFamilyId] = stu;
	}

	m_FamilyDungeonMap[nFamilyId] = pDungeon;
	SaveFamilyDungeonStuMap( nFamilyId );

	return true;
}

void FamilyManager::SaveFamilyDungeonStuMap( FamilyId_t nFamilyId )
{
	FamilyDungeonStuMap::iterator it = m_FamilyDungeonStuMap.find( nFamilyId );
	if ( it == m_FamilyDungeonStuMap.end() )
	{
		return;
	}

	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `mem_family_dungeon` ( `id`, `times`, `start_time`, `finish_hard` ) VALUES ( %lld, %d, %d, %d ) "
		"ON DUPLICATE KEY UPDATE `times`=%d, `start_time`=%d, `finish_hard`=%d",
		nFamilyId,
		it->second.StartCounts,
		it->second.StartTime,
		it->second.nMaxHard,
		it->second.StartCounts,
		it->second.StartTime,
		it->second.nMaxHard );
	db.excute( szSQL );
}

void FamilyManager::DeleteFamilyDungeon( FamilyId_t nFamilyId )
{
	FamilyDungeonMap::iterator iter = m_FamilyDungeonMap.find( nFamilyId );
	if ( iter != m_FamilyDungeonMap.end() )
	{
		m_FamilyDungeonMap.erase( iter );
		SendSocialFinishBoss( nFamilyId, 1, 1 );
	}
}

void FamilyManager::SetFamilyDungeonHard( FamilyId_t nFamilyId, int32_t Hard )
{
	FamilyDungeonStuMap::iterator it = m_FamilyDungeonStuMap.find( nFamilyId );
	if ( it != m_FamilyDungeonStuMap.end() && it->second.nMaxHard < Hard )
	{
		it->second.nMaxHard = Hard;
		SaveFamilyDungeonStuMap( nFamilyId );
	}
}

void FamilyManager::SendSocialFinishBoss( FamilyId_t nFamilyId, int32_t ActId, int8_t result )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( 0, Answer::PACK_DISPATCH, SM_FAMILY_SOCIAL_FINISH_BOSS );
	if ( packet )
	{
		packet->writeInt64( nFamilyId );
		packet->writeInt32( ActId );
		packet->writeInt8( result );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacket( 0, packet );
	}
}

void FamilyManager::addFamilyInfo( const FamilyInfo& info )
{
	if ( info.IsEmpty() )
	{
		return;
	}

	Answer::MutexGuard lock( m_Lock );
	m_mFamilyInfo[info.nId] = info;
}

void FamilyManager::updateFamilyInfo( const FamilyInfo& info )
{
	if ( info.IsEmpty() )
	{
		return;
	}

	Answer::MutexGuard lock( m_Lock );
	FamilyInfoMap::iterator iter = m_mFamilyInfo.find( info.nId );
	if ( iter != m_mFamilyInfo.end() )
	{
		iter->second = info;
	}
}

void FamilyManager::deleteFamilyInfo( FamilyId_t nFamilyId )
{
	Answer::MutexGuard lock( m_Lock );
	m_mFamilyInfo.erase( nFamilyId );
}

//////////////////////////////////////////////////////////////////////////
// FamilyInfo methods
//////////////////////////////////////////////////////////////////////////
void FamilyInfo::CleanUp()
{
	nId = 0;
	nLevel = 0;
	nMemberCard = 0;
	strName.clear();
	FamilyTaskCount = 0;
	nBossPoints = 0;
	FamilyLeaderCid = 0;
	FamilyLeaderName.clear();
	Battle = 0;
	Territory = 0;
	MedalLevel = 0;
	nBossState = 0;
	DeclareFamilies.clear();
}

bool FamilyInfo::IsDeclareWarFamily(FamilyId_t nFamilyId)
{
	return DeclareFamilies.find(nFamilyId) != DeclareFamilies.end();
}

void FamilyInfo::UnPackageData(Answer::NetPacket* packet)
{
	if (!packet) return;
	nId = packet->readInt64();
	{ std::string tmp; packet->readUTF8(tmp); strName = tmp; }
	nLevel = packet->readInt32();
	nMemberCard = packet->readInt8();
	FamilyTaskCount = packet->readInt32();
	nBossPoints = packet->readInt32();
	FamilyLeaderCid = packet->readInt64();
	{ std::string tmp; packet->readUTF8(tmp); FamilyLeaderName = tmp; }
	Battle = packet->readInt32();
	Territory = packet->readInt8();
	MedalLevel = packet->readInt32();
	nBossState = packet->readInt8();
	int32_t count = packet->readInt32();
	for (int32_t i = 0; i < count; ++i)
	{
		int64_t familyId = packet->readInt64();
		DeclareFamilies.insert(familyId);
	}
}
