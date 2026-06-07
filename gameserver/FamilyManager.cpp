#include "stdafx.h"

#include "CfgData.h"
#include "FamilyManager.h"
#include "GameService.h"
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
		info.nId		= result.getInt64Value("id");;
		info.strName	= result.getStringValue("name");
		info.nLevel		= result.getIntValue("level");

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
}

void FamilyManager::OnUpdateFamilyInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	int8_t	nReason = inPacket->readInt8();
	FamilyInfo info;
	info.nId		= inPacket->readInt64();
	info.strName	= inPacket->readUTF8(true);
	info.nLevel		= inPacket->readInt32();
	info.nAddBattle	= inPacket->readInt32();
	info.FamilyTaskCount = inPacket->readInt32();
	int32_t Count   = inPacket->readInt32();
	for ( int32_t i = 0; i < Count; i++ )
	{
		info.OpenedTotom.insert( inPacket->readInt32() );
	}
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
