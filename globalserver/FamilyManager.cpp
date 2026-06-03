#include "stdafx.h"

#include "CfgData.h"
#include "FamilyManager.h"
#include "SocialService.h"
#include <string>
#include <algorithm>
using namespace Answer;

FamilyManager::FamilyManager()
:m_FamilyPool(50,100)
{
}

FamilyManager::~FamilyManager()
{

}

bool FamilyManager::Init()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, "SELECT a.* FROM `mem_family` AS a LEFT JOIN `mem_chr_family` AS b ON a.leader_cid=b.cid WHERE a.delflag=0 AND b.position=%d", FP_LEADER );
	MySqlQuery result = db.query(szSQL);

	while ( !result.eof() )
	{
		Family *pFamily = m_FamilyPool.pop();
		if ( NULL == pFamily )
		{
			LOG_ERROR( "FamilyManager::Init() FamilyPool Full!!!" );
			return false;
		}

		FamilyDBData dbData;
		dbData.nFamilyId		= result.getInt64Value("id");;
		dbData.strName			= result.getStringValue("name");
		dbData.nLevel			= result.getIntValue("level");
		dbData.nMoney			= result.getIntValue("money");
		dbData.strNotice		= result.getStringValue("notice");
		dbData.AutoAgree		= result.getIntValue("auto_agree");
		dbData.FamilyTaskCount  = result.getIntValue("task_count");
		dbData.LastFamilyTaskTime = result.getIntValue("task_time");
		pFamily->LoadFromDB( dbData );

		m_mFamily[pFamily->GetId()] = pFamily;
		result.nextRow();
	}

	return true;
}

Family* FamilyManager::GetFamily( FamilyId_t nId )
{
	FamilyMap::iterator iter = m_mFamily.find( nId );
	if ( iter != m_mFamily.end() )
	{
		return iter->second;
	}
	return NULL;
}

void FamilyManager::SendFamilyList( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( player.getLevelFamilyTime() );
	int32_t nCount = 0;
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt16( nCount);

	for ( FamilyMap::iterator iter = m_mFamily.begin(); iter != m_mFamily.end(); ++iter)
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL )
		{
			if ( pFamily->AppendListInfo( packet, player ) )
			{
				++nCount;
			}
		}
	}

	int32_t newOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( newOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_LIST );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

bool FamilyManager::CheckFamilyName( const std::string& name )
{
	for ( FamilyMap::iterator iter = m_mFamily.begin(); iter != m_mFamily.end(); ++iter)
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL && pFamily->GetName() == name )
		{
			return true;
		}
	}
	return false;
}

Family* FamilyManager::CreateFamily( const std::string& name, SocialPlayer& player )
{
	FamilyId_t nFamilyId = getFamilyId( player.getsid() );
	if ( nFamilyId <= 0 )
	{
		return NULL;
	}

	Family* pFamily = m_FamilyPool.pop();
	if ( NULL == pFamily )
	{
		return NULL;
	}
	{
		MySqlDBGuard db(DBPOOL);

		char szSQL[MAX_SQL_LENGTH] = "";
		snprintf(szSQL, sizeof(szSQL)-1, 
			"INSERT INTO `mem_family` (`id`,`name`,`leader_cid`,`creator_cid`,`create_time`,`level`,`count`,`auto_agree`) VALUES ('%lld','%s','%lld','%lld','%d',1,1,1)",
			nFamilyId,
			name.c_str(), 
			player.getCid(), 
			player.getCid(),
			DayTime::now()
			);
		db.excute(szSQL);
	}
	CleanApply( player.GetPlayerInfo() );
	pFamily->Init( nFamilyId, name, player );
	m_mFamily[nFamilyId] = pFamily;
	return pFamily;
}

void FamilyManager::CleanApply( PlayerInfo* pPlayerInfo )
{
	if ( NULL == pPlayerInfo )
	{
		return;
	}
	for ( FamilyMap::iterator iter = m_mFamily.begin(); iter != m_mFamily.end(); ++iter)
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL )
		{
			pFamily->RemoveApply( pPlayerInfo->nCharId );
		}
	}

	pPlayerInfo->nFamilyApplyCount = 0;
}

void FamilyManager::DestroyFamily( FamilyId_t nFamilyId )
{
	FamilyMap::iterator iter = m_mFamily.find( nFamilyId );
	if ( iter != m_mFamily.end() )
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL )
		{
			m_mFamily.erase( iter );
			m_FamilyPool.push( pFamily );
		}
	}
	{
		MySqlDBGuard db(DBPOOL);

		char szSQL[MAX_SQL_LENGTH] = "";
		snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_family` SET delflag=1,del_time=%d WHERE id=%lld", DayTime::now(), nFamilyId );
		db.excute(szSQL);
	}
}

void FamilyManager::CheckFamilyTotom( int32_t nNowTime )
{
	for ( FamilyMap::iterator iter = m_mFamily.begin(); iter != m_mFamily.end(); ++iter)
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL )
		{
			pFamily->CheckTotomTime( nNowTime );
		}
	}
}

FamilyId_t FamilyManager::getFamilyId( int32_t nServerId ) const
{
	char szSql[MAX_SQL_LENGTH] = {};
	snprintf( szSql, sizeof( szSql ) - 1, "call NewFamilyId(%d,@OutFamilyId)", nServerId );

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( szSql );
	if ( !result.eof() )
	{
		int32_t nNewFamilyId = result.getIntValue( 0 );
		if ( nNewFamilyId > 0 )
		{
			return ( static_cast<CharId_t>( nServerId ) << 32 ) + nNewFamilyId;
		}
	}

	LOG_ERROR( "CPetManager::getFamilyId() FAIL! time=%d\n", DayTime::now() );
	return 0;
}

void FamilyManager::UpdateFamilyInfo()
{
	for ( FamilyMap::iterator iter = m_mFamily.begin(); iter != m_mFamily.end(); ++iter)
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL )
		{
			pFamily->sendGameUpdateFamilyInfo( FUR_UPDATE );
		}
	}
}
void FamilyManager::ResetFamilyCount()
{
	for ( FamilyMap::iterator iter = m_mFamily.begin(); iter != m_mFamily.end(); ++iter)
	{
		Family* pFamily = iter->second;
		if ( pFamily != NULL )
		{
			pFamily->ResetFamilyCount();
		}
	}
}
