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

void FamilyManager::Init()
{
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
