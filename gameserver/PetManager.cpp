#include "stdafx.h"

#include "GameService.h"
#include "Map.h"
#include "Player.h"
#include "PetManager.h"
#include "PoolManager.h"
#include "Timer.h"
#include "CfgData.h"
#include "DBService.h"


using namespace Answer;

CPetManager::CPetManager()
	:m_nLastTick( 0 )
{
}

CPetManager::~CPetManager()
{
}

void CPetManager::Init()
{
	m_NeedUpdatePet.clear();
	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( "SELECT * FROM `mem_pet` WHERE delflag=0" );

	MemPetDBData pet;
	while(!result.eof())
	{
		pet.CleanUp();
		pet.nOwner		= result.getInt64Value("owner");
		pet.nPetId		= result.getInt64Value("pid");
		pet.nBaseId		= result.getIntValue("baseid");
		pet.strName		= result.getStringValue( "name" );
		pet.nLevel		= result.getIntValue("level");
		pet.nExp		= result.getInt64Value("exp");
		pet.nPotential	= result.getIntValue("potential");
		pet.nRein		= result.getIntValue("rein");
		pet.nAdjustRein	= result.getIntValue("adj_rein");
		pet.nNumber		= result.getIntValue("number");
		pet.nPhase		= result.getIntValue("phase");
		pet.nLucky		= result.getIntValue("lucky");
		pet.nBornFlag	= result.getIntValue("bornflag");
		pet.nFromWay	= result.getIntValue("fromway");
		pet.nGrowTimes	= result.getIntValue("growtimes");
		pet.nPoints		= result.getIntValue("Points");

// 		pet.vAttr[PET_ATTR_START_HP]				= result.getIntValue("start_hp");
// 		pet.vAttr[PET_ATTR_START_PHY_ATK_MIN]		= result.getIntValue("start_phy_atk_min");
// 		pet.vAttr[PET_ATTR_START_PHY_ATK_MAX]		= result.getIntValue("start_phy_atk_max");
// 		pet.vAttr[PET_ATTR_START_PHY_DEF]			= result.getIntValue("start_phy_def");
// 		pet.vAttr[PET_ATTR_START_MAG_ATK_MIN]		= result.getIntValue("start_mag_atk_min");
// 		pet.vAttr[PET_ATTR_START_MAG_ATK_MAX]		= result.getIntValue("start_mag_atk_max");
// 		pet.vAttr[PET_ATTR_START_MAG_DEF]			= result.getIntValue("start_mag_def");
// 		pet.vAttr[PET_ATTR_START_DODGE]				= result.getIntValue("start_dodge");
// 		pet.vAttr[PET_ATTR_START_HITRATE]			= result.getIntValue("start_hitrate");
// 		pet.vAttr[PET_ATTR_START_CRITRATE]			= result.getIntValue("start_critrate");
// 		pet.vAttr[PET_ATTR_START_TENACITY]			= result.getIntValue("start_tenacity");
		pet.vAttr[PET_ATTR_GROW_HP]					= result.getIntValue("grow_hp");
		pet.vAttr[PET_ATTR_GROW_PHY_ATK_MIN]		= result.getIntValue("grow_phy_atk_min");
		pet.vAttr[PET_ATTR_GROW_PHY_ATK_MAX]		= result.getIntValue("grow_phy_atk_max");
		pet.vAttr[PET_ATTR_GROW_PHY_DEF]			= result.getIntValue("grow_phy_def");
		pet.vAttr[PET_ATTR_GROW_MAG_ATK_MIN]		= result.getIntValue("grow_mag_atk_min");
		pet.vAttr[PET_ATTR_GROW_MAG_ATK_MAX]		= result.getIntValue("grow_mag_atk_max");
		pet.vAttr[PET_ATTR_GROW_MAG_DEF]			= result.getIntValue("grow_mag_def");
		pet.vAttr[PET_ATTR_GROW_DODGE]				= result.getIntValue("grow_dodge");
		pet.vAttr[PET_ATTR_GROW_HITRATE]			= result.getIntValue("grow_hitrate");
		pet.vAttr[PET_ATTR_GROW_CRITRATE]			= result.getIntValue("grow_critrate");
		pet.vAttr[PET_ATTR_GROW_TENACITY]			= result.getIntValue("grow_tenacity");

		pet.records		= result.getStringValue( "records" );
		pet.skills		= result.getStringValue( "skills" );

		CPet* pPet = POOL_MANAGER.pop<CPet>();
		if ( NULL == pPet )
		{
			LOG_ERROR( "CPetManager::Init() fail POOL_MANAGER FULL !!! pet count=%d\n", result.getFieldCount() );
			return;
		}

		pPet->OnLoadFromDB( pet, true );
		m_mPet.insert( PetMap::value_type( pet.nPetId, pPet ) );
		if ( pPet->GetPoints() != pet.nPoints )
		{
			m_NeedUpdatePet.push_back( pPet->GetPetId() );
		}
		result.nextRow();
	}
}

void CPetManager::UpdataChangedPet()
{
	std::list<PetId_t>::iterator it = m_NeedUpdatePet.begin();
	for ( ; it != m_NeedUpdatePet.end(); ++it )
	{
		UpdatePet( GetPet(*it) );
	}
}

void CPetManager::OnUpdated( const MemPetDBData& pet )
{
	CPet* pPet = NULL;
	{
		RwLockWrGuard lock( m_rwLock );
		PetMap::iterator findIter = m_mPet.find( pet.nPetId );
		if ( findIter != m_mPet.end() )
		{
			pPet = findIter->second;
		}
		else
		{
			pPet = POOL_MANAGER.pop<CPet>();
		}

		if ( NULL == pPet )
		{
			return;
		}

		pPet->OnLoadFromDB( pet );
	}
}

void CPetManager::OnDeleted( PetId_t nPetId )
{
	CPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return;
	}

	{
		RwLockWrGuard lock( m_rwLock );
		m_mPet.erase( pPet->GetPetId() );
	}
	POOL_MANAGER.push<CPet>( pPet );
}

CPet* CPetManager::GetPet( PetId_t nPetId )
{
	RwLockWrGuard lock( m_rwLock );
	PetMap::iterator findIter = m_mPet.find( nPetId );
	if ( findIter != m_mPet.end() )
	{
		return findIter->second;
	}
	return NULL;
}

CPet* CPetManager::CreateNewPetFromEgg( int32_t nEggId, Player* pCreater, int32_t nFromWay )
{
	if ( NULL == pCreater )
	{
		return NULL;
	}

	const CfgPetEgg* pEgg = CFG_DATA.GetPetEggTable().GetEgg( nEggId );
	if ( NULL == pEgg )
	{
		return 0;
	}

	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( pEgg->nPetId );
	if ( NULL == pCfgPet )
	{
		return NULL;
	}

	PetId_t nPetId = getPetId( pCreater->getSid() );
	if ( 0 == nPetId )
	{
		return NULL;
	}

	CPet* pPet = POOL_MANAGER.pop<CPet>();
	if ( pPet != NULL )
	{
		pPet->Init( pCreater->getCid(), nPetId, *pEgg, nFromWay );
	}
	return pPet;

}

CPet* CPetManager::CreateNewPet( int32_t nBaseId, Player* pCreater, int8_t nFromWay )
{
	if ( NULL == pCreater )
	{
		return NULL;
	}
	
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( nBaseId );
	if ( NULL == pCfgPet )
	{
		return NULL;
	}

	PetId_t nPetId = getPetId( pCreater->getSid() );
	if ( 0 == nPetId )
	{
		return NULL;
	}

	CPet* pPet = POOL_MANAGER.pop<CPet>();
	if ( pPet != NULL )
	{
		pPet->Init( pCreater->getCid(), nPetId, nBaseId, nFromWay );
	}
	return pPet;
}

void CPetManager::AddPet( CPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}

	PetId_t nPetId = pPet->GetPetId();
	{
		RwLockWrGuard lock( m_rwLock );
		m_mPet.insert( PetMap::value_type( nPetId, pPet ) );
	}
	MemPetDBData pet;
	pPet->OnSaveToDB( pet );
	DB_SERVICE.insertMemPet( pet );

	if ( IsInsidePet( pPet->GetBaseId() ) ||  ( pPet->GetLevel() >= PET_RANK_OPEN_LEVEL  && !pPet->IsXOType() ) )
	{
		sendSocialUpdatePet( pPet );
	}
}

void CPetManager::DelPet( CPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}

	PetId_t nPetId = pPet->GetPetId();
	{
		RwLockWrGuard lock( m_rwLock );
		m_mPet.erase( pPet->GetPetId() );
	}
	if ( IsInsidePet( pPet->GetBaseId() ) || pPet->GetLevel() >= PET_RANK_OPEN_LEVEL )
	{
		sendSocialDeletePet( nPetId );
	}
	POOL_MANAGER.push<CPet>( pPet );
	DB_SERVICE.deleteMemPet( nPetId );
}

void CPetManager::UpdatePet( CPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}

	MemPetDBData pet;
	pPet->OnSaveToDB( pet );
	DB_SERVICE.updateMemPet( pet );
	if ( IsInsidePet( pPet->GetBaseId() ) || ( pPet->GetLevel() >= PET_RANK_OPEN_LEVEL  && !pPet->IsXOType() ) )
	{
		sendSocialUpdatePet( pPet );
	}
}

void CPetManager::GetPlayerPetList( CharId_t nCharId, PetList& pets )
{
	RwLockWrGuard lock( m_rwLock );
	PetMap::iterator iter = m_mPet.begin();
	PetMap::iterator eiter = m_mPet.end();
	for ( ; iter != eiter; ++iter )
	{
		CPet* pPet = iter->second;
		if ( pPet != NULL && pPet->GetOwnerId() == nCharId )
		{
			pets.push_back( pPet );
		}
	}
}

void CPetManager::ChangeOwner( PetId_t nPetId, CharId_t nOwner )
{
	CPet* pPet = NULL;
	Player* pPlayer = GAME_SERVICE.getPlayer( nOwner, 0, false );
	{
		RwLockWrGuard lock( m_rwLock );
		PetMap::iterator findIter = m_mPet.find( nPetId );
		if ( findIter != m_mPet.end() )
		{
			pPet = findIter->second;
			if ( pPet != NULL )
			{
				pPet->ChangeOwner( nOwner );
				if ( pPlayer != NULL )
				{
					pPet->SendPetInfo( pPlayer );
				}
			}
		}
	}
}

PetId_t CPetManager::getPetId( int32_t nServerId ) const
{
	char szSql[MAX_SQL_LENGTH] = {};
	snprintf( szSql, sizeof( szSql ) - 1, "call NewPetId(%d,@OutPetId)", nServerId );

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( szSql );
	if ( !result.eof() )
	{
		int32_t nNewPetId = result.getIntValue( 0 );
		if ( nNewPetId > 0 )
		{
			return ( static_cast<CharId_t>( nServerId ) << 32 ) + nNewPetId;
		}
	}

	LOG_ERROR( "CPetManager::getPetId() FAIL! time=%d\n", TIMER.GetNow() );
	return 0;
}

void CPetManager::ResetRecords()
{
	RwLockWrGuard lock( m_rwLock );
	PetMap::iterator iter = m_mPet.begin();
	PetMap::iterator eiter = m_mPet.end();
	for ( ; iter != eiter; ++iter )
	{
		CPet* pPet = iter->second;
		if ( pPet != NULL )
		{
			pPet->ResetRecord();
		}
	}
}

void CPetManager::OnUpdatePetRank( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	int32_t nCount = inPacket->readInt32();
	RwLockWrGuard lock( m_rwLock );
	for ( int32_t i = 0; i < nCount; ++i )
	{
		PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
		PetMap::iterator findIter = m_mPet.find( nPetId );
		if ( findIter == m_mPet.end() )
		{
			continue;
		}

		CPet* pPet = findIter->second;
		if ( NULL == pPet )
		{
			continue;
		}
		pPet->SetRankIndex( PRT_POINTS,				inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_HP,			inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_PHY_ATK_MIN,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_PHY_ATK_MAX,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_PHY_DEF,		inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_MAG_ATK_MIN,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_MAG_ATK_MAX,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_MAG_DEF,		inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_HP,			inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_PHY_ATK_MIN,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_PHY_ATK_MAX,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_PHY_DEF,		inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_MAG_ATK_MIN,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_MAG_ATK_MAX,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_MAG_DEF,		inPacket->readInt16() );
	}
}

void CPetManager::OnInitPetRank( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	int32_t nCount = inPacket->readInt32();
	RwLockWrGuard lock( m_rwLock );
	for ( int32_t i = 0; i < nCount; ++i )
	{
		PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
		PetMap::iterator findIter = m_mPet.find( nPetId );
		if ( findIter == m_mPet.end() )
		{
			continue;
		}

		CPet* pPet = findIter->second;
		if ( NULL == pPet )
		{
			continue;
		}
		pPet->SetRankIndex( PRT_POINTS,				inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_HP,			inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_PHY_ATK_MIN,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_PHY_ATK_MAX,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_PHY_DEF,		inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_MAG_ATK_MIN,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_MAG_ATK_MAX,	inPacket->readInt16() );
// 		pPet->SetRankIndex( PRT_START_MAG_DEF,		inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_HP,			inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_PHY_ATK_MIN,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_PHY_ATK_MAX,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_PHY_DEF,		inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_MAG_ATK_MIN,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_MAG_ATK_MAX,	inPacket->readInt16() );
		pPet->SetRankIndex( PRT_GROW_MAG_DEF,		inPacket->readInt16() );
	}
}

void CPetManager::sendSocialUpdatePet( CPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}

	if ( !pPet->IsPetBorn() )
	{
		return;
	}

	SocialPetData petData = {};
	pPet->GetPetData( petData );

	// 同步到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_SOCIAL_UPDATE_PET_DATA );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( petData.nPetId );
	packet->writeInt32( petData.nBaseId );
	packet->writeInt64( petData.nOwner );
	packet->writeInt32( petData.nPoints );
	packet->writeUInt32( petData.nRankFlag );
	packet->writeUTF8( petData.strName );
	for ( int32_t i = 0; i < PET_ATTR_COUNT; ++i )
	{
		packet->writeInt32( petData.vAttr[i] );
	}

	packet->setSize( packet->getWOffset() ); 

	GAME_SERVICE.sendPacket( packet );
}

void CPetManager::sendSocialDeletePet( PetId_t nPetId )
{
	// 同步到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_SOCIAL_DELETE_PET_DATA );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( nPetId );
	packet->setSize( packet->getWOffset() ); 

	GAME_SERVICE.sendPacket( packet );
}
