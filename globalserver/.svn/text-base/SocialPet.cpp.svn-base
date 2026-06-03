#include "stdafx.h"

#include "SocialPet.h"
#include "SocialService.h"
#include "PlayerManager.h"

#define PET_RANK_REFRESH_TIME	1000		// 排行榜刷新延迟
#define PET_RANK_SIZE			100			// 排行榜最大显示人数
#define PET_RANK_VIEW_MAX_INDEX	110			// 排行显示数值最大值

using namespace Answer;

CSocialPet::CSocialPet()
{
	reset();
}

CSocialPet::~CSocialPet()
{

}

void CSocialPet::reset()
{
	bzero( &m_petData, sizeof( m_petData ) );
	bzero( &m_rankIndex, sizeof( m_rankIndex ) );
}

void CSocialPet::Set( const SocialPetData& petData )
{
	m_petData = petData;
}

int32_t CSocialPet::GetBaseId() const
{
	return m_petData.nBaseId;
}

PetId_t CSocialPet::GetPetId() const
{
	return m_petData.nPetId;
}

std::string	CSocialPet::GetPetName() const
{
	return m_petData.strName;
}

CharId_t CSocialPet::GetOwnerId() const
{
	return m_petData.nOwner;
}

int32_t CSocialPet::GetRankFlag() const
{
	return m_petData.nRankFlag;
}

int32_t CSocialPet::GetPoints() const
{
	return m_petData.nPoints;
}

int32_t CSocialPet::GetBaseAttr( PET_ATTR nAttr ) const
{
	return m_petData.vAttr[nAttr];
}

bool CSocialPet::SetPointsRankIndex( int32_t nIndex )
{
	if ( nIndex <= 0 || nIndex > PET_RANK_VIEW_MAX_INDEX )
	{
		nIndex = 0;
	}
	if ( m_rankIndex.nPointsIndex != nIndex )
	{
		m_rankIndex.nPointsIndex = nIndex;
		return true;
	}
	return false;
}

bool CSocialPet::SetRankIndex( PET_ATTR nAttr, int32_t nIndex )
{
	if ( nIndex <= 0 || nIndex > PET_RANK_VIEW_MAX_INDEX )
	{
		nIndex = 0;
	}
	if ( m_rankIndex.vAttrIndex[nAttr] != nIndex )
	{
		m_rankIndex.vAttrIndex[nAttr] = nIndex;
		return true;
	}
	return false;
}

void CSocialPet::AppendRankInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt64( m_petData.nPetId );
	packet->writeInt16( m_rankIndex.nPointsIndex );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_HP] );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MIN] );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MAX] );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_PHY_DEF] );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MIN] );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MAX] );
// 	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_START_MAG_DEF] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_HP] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MIN] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MAX] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_PHY_DEF] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MIN] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MAX] );
	packet->writeInt16( m_rankIndex.vAttrIndex[PET_ATTR_GROW_MAG_DEF] );
}

void CSocialPet::AppendRankList( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	std::string ownerName = "";
	PlayerInfo* pInfo = PLAYER_MANAGER.GetPlayerInfo( m_petData.nOwner );
	if ( pInfo != NULL )
	{
		ownerName = pInfo->strName;
	}
	packet->writeInt64( m_petData.nPetId );
	packet->writeUTF8( m_petData.strName );
	packet->writeInt64( m_petData.nOwner );
	packet->writeUTF8( ownerName );
	packet->writeInt32( m_petData.nPoints );
}

bool CSocialPet::IsInRank() const
{
	if ( m_rankIndex.nPointsIndex > 0 && m_rankIndex.nPointsIndex <= PET_RANK_VIEW_MAX_INDEX )
	{
		return true;
	}
	for ( int32_t i = 0; i < PET_ATTR_COUNT; ++i )
	{
		if ( m_rankIndex.vAttrIndex[i] > 0 && m_rankIndex.vAttrIndex[i] <= PET_RANK_VIEW_MAX_INDEX )
		{
			return true;
		}
	}
	return false;
}

bool CSocialPet::ChangeOwner( CharId_t nOwnerId )
{
	if ( m_petData.nOwner == nOwnerId )
	{
		return false;
	}

	m_petData.nOwner = nOwnerId;
	return true;
}
