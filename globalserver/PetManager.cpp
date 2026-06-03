#include "stdafx.h"

#include "PetRank.h"
#include "PetManager.h"
#include "PlayerManager.h"
#include "SocialService.h"

#define PET_RANK_REFRESH_TIME	1000		// 排行榜刷新延迟
#define PET_RANK_SIZE			100			// 排行榜最大显示人数
#define O_PET_BASE_ID			9			// o兽id
#define XO_PET_BASE_ID			10			// XO兽
using namespace Answer;

CPetManager::CPetManager()
	:m_socialPetPool( 500, 1000 )
{
}

CPetManager::~CPetManager()
{
}

void CPetManager::Init()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf( szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_pet` WHERE delflag=0 AND bornflag=1" );
	MySqlQuery result = db.query( szSQL );

	SocialPetData pet = {};
	while(!result.eof())
	{
		pet.nBaseId		= result.getIntValue("baseid");
		int32_t	level	= result.getIntValue("level");
		if ( !IsInsidePet( pet.nBaseId ) && level < PET_RANK_OPEN_LEVEL || pet.nBaseId == O_PET_BASE_ID || pet.nBaseId == XO_PET_BASE_ID )
		{
			result.nextRow();
			continue;	// 灵兽没有这个等级限制
		}
		pet.nPetId		= result.getInt64Value("pid");
		pet.nPoints		= result.getIntValue("points");
		pet.nOwner		= result.getInt64Value("owner");
		snprintf( pet.strName, MAX_NAME_CCH_LENGTH, result.getStringValue( "name" ) );

// 		pet.vAttr[PET_ATTR_START_HP]			= result.getIntValue("start_hp");
// 		pet.vAttr[PET_ATTR_START_PHY_ATK_MIN]	= result.getIntValue("start_phy_atk_min");
// 		pet.vAttr[PET_ATTR_START_PHY_ATK_MAX]	= result.getIntValue("start_phy_atk_max");
// 		pet.vAttr[PET_ATTR_START_PHY_DEF]		= result.getIntValue("start_phy_def");
// 		pet.vAttr[PET_ATTR_START_MAG_ATK_MIN]	= result.getIntValue("start_mag_atk_min");
// 		pet.vAttr[PET_ATTR_START_MAG_ATK_MAX]	= result.getIntValue("start_mag_atk_max");
// 		pet.vAttr[PET_ATTR_START_MAG_DEF]		= result.getIntValue("start_mag_def");
// 		pet.vAttr[PET_ATTR_START_DODGE]			= result.getIntValue("start_dodge");
// 		pet.vAttr[PET_ATTR_START_HITRATE]		= result.getIntValue("start_hitrate");
// 		pet.vAttr[PET_ATTR_START_CRITRATE]		= result.getIntValue("start_critrate");
// 		pet.vAttr[PET_ATTR_START_TENACITY]		= result.getIntValue("start_tenacity");
		pet.vAttr[PET_ATTR_GROW_HP]				= result.getIntValue("grow_hp");
		pet.vAttr[PET_ATTR_GROW_PHY_ATK_MIN]	= result.getIntValue("grow_phy_atk_min");
		pet.vAttr[PET_ATTR_GROW_PHY_ATK_MAX]	= result.getIntValue("grow_phy_atk_max");
		pet.vAttr[PET_ATTR_GROW_PHY_DEF]		= result.getIntValue("grow_phy_def");
		pet.vAttr[PET_ATTR_GROW_MAG_ATK_MIN]	= result.getIntValue("grow_mag_atk_min");
		pet.vAttr[PET_ATTR_GROW_MAG_ATK_MAX]	= result.getIntValue("grow_mag_atk_max");
		pet.vAttr[PET_ATTR_GROW_MAG_DEF]		= result.getIntValue("grow_mag_def");
		pet.vAttr[PET_ATTR_GROW_DODGE]			= result.getIntValue("grow_dodge");
		pet.vAttr[PET_ATTR_GROW_HITRATE]		= result.getIntValue("grow_hitrate");
		pet.vAttr[PET_ATTR_GROW_CRITRATE]		= result.getIntValue("grow_critrate");
		pet.vAttr[PET_ATTR_GROW_TENACITY]		= result.getIntValue("grow_tenacity");

		AddPet( pet, false );

		result.nextRow();
	}

	// 刷新所有宠物排名
	PET_RANK.RefreshRank();
}

CSocialPet* CPetManager::GetPet( PetId_t nPetId )
{
	SocialPetMap::iterator iter = m_mSocialPet.find( nPetId );
	if ( iter == m_mSocialPet.end() )
	{
		return NULL;
	}
	return iter->second;
}

CSocialPet* CPetManager::AddPet( const SocialPetData& pet, bool bNeedRefresh )
{
	PetId_t nPetId = pet.nPetId;
	CSocialPet* pPet = m_socialPetPool.pop();
	if ( NULL == pPet )
	{
		return NULL;
	}

	pPet->Set( pet );
	m_mSocialPet[nPetId] = pPet;
	PET_RANK.AddPet( pPet, bNeedRefresh );
	return pPet;
}

CSocialPet* CPetManager::UpdatePet( const SocialPetData& pet )
{
	CSocialPet* pPet = GetPet( pet.nPetId );
	if ( NULL == pPet )
	{
		return AddPet( pet );
	}

	//更新放在set中，需要在删除原节点后更新，否则无法找到原节点
	PET_RANK.UpdatePet( pPet, pet );
	return pPet;
}

void CPetManager::DelPet( PetId_t nPetId )
{
	CSocialPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return;
	}

	PET_RANK.DelPet( pPet );
	m_mSocialPet.erase( nPetId );
	m_socialPetPool.push( pPet );
}

void CPetManager::SendPetRankInfo( const PetIdList& petIdList, int16_t nGateIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	int8_t nCount = 0;
	packet->writeInt8( nCount );
	PetIdList::const_iterator iter = petIdList.begin();
	PetIdList::const_iterator eiter = petIdList.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = GetPet( *iter );
		if ( NULL == pPet )
		{
			return;
		}

		pPet->AppendRankInfo( packet );
		++nCount;
	}

	uint32_t nOffset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt8( nCount );
	packet->setWOffset( nOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_PET_RANK_INFO );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nGateIndex, packet);
}

void CPetManager::SendGameAllRankInfo( int32_t nLine )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( nLine );
	uint16_t nOffset = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	SocialPetMap::iterator iter = m_mSocialPet.begin();
	SocialPetMap::iterator eiter = m_mSocialPet.end();
	for ( ; iter != m_mSocialPet.end(); ++iter )
	{
		CSocialPet* pPet = iter->second;
		if ( NULL == pPet )
		{
			continue;
		}
		if ( !pPet->IsInRank() )
		{
			continue;
		}

		pPet->AppendRankInfo( packet );
		++nCount;
	}

	uint16_t nOldOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt32( nCount );
	packet->setWOffset( nOldOffset );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_SINGLE_GAME_INIT_PET_RANK );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void CPetManager::GetAllPetRankData( PetRankDataVector& vPet )
{
	vPet.reserve( m_mSocialPet.size() );
	SocialPetMap::iterator iter = m_mSocialPet.begin();
	SocialPetMap::iterator eiter = m_mSocialPet.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = iter->second;
		if ( pPet != NULL && !IsInsidePet( pPet->GetBaseId() ) )	// 内置宠不算做普通宠物
		{
			PlayerInfo* pPlayer = PLAYER_MANAGER.GetPlayerInfo( pPet->GetOwnerId() );
			if ( pPlayer != NULL )
			{
				vPet.push_back( PetRankData( pPet->GetBaseId(), pPet->GetPoints(), pPet->GetPetName(), pPlayer->nCharId, pPlayer->strName, pPet->GetPetId() ) );
			}
		}
	}
}

void CPetManager::GetInsidePetRankData( PetRankDataVector& vPet )
{
	vPet.reserve( m_mSocialPet.size() );
	SocialPetMap::iterator iter = m_mSocialPet.begin();
	SocialPetMap::iterator eiter = m_mSocialPet.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = iter->second;
		if ( pPet != NULL && IsInsidePet( pPet->GetBaseId() ) )	// 内置宠
		{
			PlayerInfo* pPlayer = PLAYER_MANAGER.GetPlayerInfo( pPet->GetOwnerId() );
			if ( pPlayer != NULL )
			{
				vPet.push_back( PetRankData( pPet->GetBaseId(), pPet->GetPoints(), pPet->GetPetName(), pPlayer->nCharId, pPlayer->strName, pPet->GetPetId() ) );
			}
		}
	}
}

bool CPetManager::ChangePetOwner( PetId_t nPetId, CharId_t nOwnerId )
{
	SocialPetMap::iterator iter = m_mSocialPet.find( nPetId );
	if ( iter == m_mSocialPet.end() )
	{
		return false;
	}

	if ( iter->second->ChangeOwner( nOwnerId ) )
	{
		// 直接修改数据库
		MySqlDBGuard db(DBPOOL);
		char szSQL[MAX_SQL_LENGTH] = "";
		snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_pet` SET `owner` = %lld WHERE pid = %lld", nOwnerId, nPetId );
		db.excute(szSQL);

		// 发送游戏服更新所有者
		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if ( packet != NULL )
		{
			packet->writeInt8( IC_PET );
			packet->writeInt64( nPetId );
			packet->writeInt64( nOwnerId );

			packet->setType( PACK_PROC );
			packet->setProc( IM_SOCIAL_ALL_GAME_CHANGE_OWNER );
			packet->setSize( packet->getWOffset() );
			SOCIAL_SERVICE.sendPacket( packet );
		}
	}
	return true;
}
