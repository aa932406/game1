#include "stdafx.h"
#include "RankManager.h"
#include "PlayerManager.h"
#include "PetManager.h"
#include "SocialService.h"
#include "FamilyManager.h"
#include <algorithm>

using namespace Answer;


bool AllPetPointsRankGreater::operator()( const PetRankData& _Left, const PetRankData& _Right ) const
{
	return _Left.nPoints > _Right.nPoints;
}

bool PlayerBattleRankGreater::operator()( const PlayerInfo& _Left, const PlayerInfo& _Right ) const
{
	return _Left.nBattle > _Right.nBattle;
}

bool PlayerLevelRankGreater::operator()( const PlayerInfo& _Left, const PlayerInfo& _Right ) const
{
	return _Left.nLevel > _Right.nLevel;
}

bool InsidePetPointsRankGreater::operator()( const PetRankData& _Left, const PetRankData& _Right ) const
{
	return _Left.nPoints > _Right.nPoints; 
}

bool PlayerGuanWeiRankGreater::operator()( const PlayerInfo& _Left, const PlayerInfo& _Right ) const
{
	return _Left.nGuanWei > _Right.nGuanWei;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CRankManager::CRankManager()
{
}

CRankManager::~CRankManager()
{
}

void CRankManager::NewMinuteCome( int32_t nMinute, int32_t nNowTime )
{
	if ( nMinute % 30 != 0 )			// 每30分钟刷新一次
	{
		return;
	}
	refreshPlayerRank();
	refreshPetRank();
	SynRank( 1, nMinute );
	SynRank( 2, nMinute );
	m_nRefreshTime = nNowTime;
}

void CRankManager::SynRank( int8_t Type, int32_t nMinute )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( Type );
	packet->writeInt32( nMinute );
	if ( Type == 1 )
	{
		int32_t Rank = 0;
		int32_t OldOff = packet->getWOffset();
		packet->writeInt32( Rank );
		PetRankDataVector::iterator it = m_vPetPointsRank.begin(); 
		list<CharId_t> CharList;
		for ( ; it != m_vPetPointsRank.end(); ++it )
		{
			bool IsInCharList = false;
			list<CharId_t>::iterator itList = CharList.begin();
			for ( ; itList != CharList.end(); ++itList )
			{
				if ( *itList == it->nOwnerId )
				{
					IsInCharList = true;
				}
			}
			if ( IsInCharList )
			{
				continue;
			}
			CharList.push_back( it->nOwnerId );

			Rank++;
			packet->writeInt32( Rank );
			packet->writeInt64( it->nOwnerId );
			packet->writeUTF8( it->strOwnerName );
			PlayerInfo*  Player = PLAYER_MANAGER.GetPlayerInfo( it->nOwnerId );
			if ( NULL != Player )
			{
				packet->writeInt8( Player->nJob );
				packet->writeInt8( Player->nSex );
			}
			else
			{
				packet->writeInt8( 0 );
				packet->writeInt8( 0 );
			}
			packet->writeInt32( it->nPoints );
			if ( Rank >= 10 )
			{
				break;
			}
		}
		int32_t NewOff = packet->getWOffset();
		packet->setWOffset( OldOff );
		packet->writeInt32( Rank );
		packet->setWOffset( NewOff );
	}
	else
	{
		int32_t nSize = m_vPlayerBattleRank.size();
		nSize = nSize < 10 ? nSize : 10; 
		packet->writeInt32( nSize );
		PlayerInfoVt::iterator it = m_vPlayerBattleRank.begin(); 
		int32_t Rank = 0;
		for ( ; it != m_vPlayerBattleRank.end(); ++it )
		{
			Rank++;
			packet->writeInt32( Rank );
			packet->writeInt64( (*it).nCharId );
			packet->writeUTF8( (*it).strName );
			packet->writeInt8( (*it).nJob );
			packet->writeInt8( (*it).nSex );
			packet->writeInt32( (*it).nBattle );
			if ( Rank >= 10 )
			{
				break;
			}
		}	
	}
	packet->setType(PACK_DISPATCH);
	packet->setProc(IM_SOCIAL_ALL_GAME_KAI_FU_HUO_DAO_RANK);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacket( packet );
}

void CRankManager::Init()
{
	refreshPlayerRank();
	refreshPetRank();
	m_nRefreshTime = DayTime::now();
}

void CRankManager::refreshPlayerRank()
{
	PlayerInfoVt vPlayer;
	PLAYER_MANAGER.GetAllPlayerInfo( vPlayer );
	int32_t nNewSize = vPlayer.size() < RANK_SIZE ? vPlayer.size() : RANK_SIZE;
	{
		std::sort( vPlayer.begin(), vPlayer.end(), PlayerBattleRankGreater() );
		m_vPlayerBattleRank.resize( nNewSize );
		for ( int32_t i = 0; i < nNewSize; ++i )
		{
			m_vPlayerBattleRank[i] = vPlayer[i];
		}
	}
	{
		std::sort( vPlayer.begin(), vPlayer.end(), PlayerLevelRankGreater() );
		m_vPlayerLevelRank.resize( nNewSize );
		for ( int32_t i = 0; i < nNewSize; ++i )
		{
			m_vPlayerLevelRank[i] = vPlayer[i];
		}
	}
	{
		std::sort( vPlayer.begin(), vPlayer.end(), PlayerGuanWeiRankGreater() );
		m_vPlayerGuanWeiRank.resize( nNewSize );
		for ( int32_t i = 0; i < nNewSize; ++i )
		{
			m_vPlayerGuanWeiRank[i] = vPlayer[i];
		}
	}
}

void CRankManager::refreshPetRank()
{
	PetRankDataVector vPet;
	PET_MANAGER.GetAllPetRankData( vPet );
	std::sort( vPet.begin(), vPet.end(), AllPetPointsRankGreater() );

	int32_t nNewSize = vPet.size() < RANK_SIZE ? vPet.size() : RANK_SIZE;
	m_vPetPointsRank.resize( nNewSize );
	for ( int32_t i = 0; i < nNewSize; ++i )
	{
		m_vPetPointsRank[i] = vPet[i];
	}

	vPet.clear();
	PET_MANAGER.GetInsidePetRankData(vPet);
	std::sort( vPet.begin(), vPet.end(), InsidePetPointsRankGreater() );
	nNewSize = vPet.size() < RANK_SIZE ? vPet.size() : RANK_SIZE;
	m_vInsidePetPointsRank.resize( nNewSize );
	for ( int32_t i = 0; i < nNewSize; ++i )
	{
		m_vInsidePetPointsRank[i] = vPet[i];
	}
}

void CRankManager::SendGameRank( int8_t rt, uint16_t nIndex )
{
	switch( rt )
	{
	case RT_PLAYER_BATTLE:		sendPlayerBattleRank( nIndex );	break;
	case RT_PLAYER_LEVEL:		sendPlayerLevelRank( nIndex );	break;
	case RT_PET_POINTS:			sendPetPointsRank( nIndex );	break;
	case RT_INSID_PET_POINTS:	sendPetInsidePetPointsRank( nIndex );	break;
	case RT_PLAYER_GUAN_WEI:	sendPlayerGuanWeiRank( nIndex );break;
	default:	break;
	}
}

void CRankManager::sendPlayerBattleRank( uint16_t nIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( RT_PLAYER_BATTLE );
	packet->writeInt32( m_nRefreshTime );

	uint32_t nOffset = packet->getWOffset();

	int16_t nCount = 0;
	packet->writeInt16( nCount );
	for ( uint32_t i = 0; i < m_vPlayerBattleRank.size(); ++i )
	{
		PlayerInfo player = m_vPlayerBattleRank[i];
		packet->writeInt8( i+1 );
		packet->writeInt64( player.nCharId );
		packet->writeInt8( player.nJob );
		packet->writeUTF8( player.strName );
		Family* pFamily = FAMILY_MANAGER.GetFamily( player.nFamilyId );
		if ( pFamily != NULL )
		{
			packet->writeUTF8( pFamily->GetName() );
		}
		else
		{
			packet->writeUTF8( "" );
		}
		packet->writeInt32( player.nBattle );
		++nCount;
	}

	uint32_t nFinalOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( nFinalOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_GAME_RANK_DATA );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nIndex, packet);
}

void CRankManager::sendPlayerLevelRank( uint16_t nIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( RT_PLAYER_LEVEL );
	packet->writeInt32( m_nRefreshTime );

	uint32_t nOffset = packet->getWOffset();

	int16_t nCount = 0;
	packet->writeInt16( nCount );
	for ( uint32_t i = 0; i < m_vPlayerLevelRank.size(); ++i )
	{
		PlayerInfo player = m_vPlayerLevelRank[i];
		packet->writeInt8( i+1 );
		packet->writeInt64( player.nCharId );
		packet->writeInt8( player.nJob );
		packet->writeUTF8( player.strName );
		Family* pFamily = FAMILY_MANAGER.GetFamily( player.nFamilyId );
		if ( pFamily != NULL )
		{
			packet->writeUTF8( pFamily->GetName() );
		}
		else
		{
			packet->writeUTF8( "" );
		}
		packet->writeInt32( player.nLevel );
		++nCount;
	}

	uint32_t nFinalOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( nFinalOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_GAME_RANK_DATA );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nIndex, packet);
}

void CRankManager::sendPetPointsRank( uint16_t nIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( RT_PET_POINTS );
	packet->writeInt32( m_nRefreshTime );

	uint32_t nOffset = packet->getWOffset();

	int16_t nCount = 0;
	packet->writeInt16( nCount );
	for ( uint32_t i = 0; i < m_vPetPointsRank.size(); ++i )
	{
		PetRankData& pet = m_vPetPointsRank[i];
		packet->writeInt8( i+1 );
		packet->writeInt32( pet.nBaseId );
		packet->writeInt64( pet.nPetId );
		packet->writeUTF8( pet.strName );
		packet->writeInt64( pet.nOwnerId );
		packet->writeUTF8( pet.strOwnerName );
		packet->writeInt32( pet.nPoints );
		++nCount;
	}

	uint32_t nFinalOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( nFinalOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_GAME_RANK_DATA );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nIndex, packet);
}

void CRankManager::sendPetInsidePetPointsRank( uint16_t nIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( RT_INSID_PET_POINTS );
	packet->writeInt32( m_nRefreshTime );

	uint32_t nOffset = packet->getWOffset();

	int16_t nCount = 0;
	packet->writeInt16( nCount );
	for ( uint32_t i = 0; i < m_vInsidePetPointsRank.size(); ++i )
	{
		PetRankData& pet = m_vInsidePetPointsRank[i];
		packet->writeInt8( i+1 );
		packet->writeInt32( pet.nBaseId );
		packet->writeInt64( pet.nPetId );
		PlayerInfo* player = PLAYER_MANAGER.GetPlayerInfo( pet.nOwnerId );
		if ( player != NULL )
		{
			Family* pFamily = FAMILY_MANAGER.GetFamily( player->nFamilyId );
			if ( pFamily != NULL )
			{
				packet->writeUTF8( pFamily->GetName() );
			}
			else
			{
				packet->writeUTF8( "" );
			}
		}
		else
		{
			packet->writeUTF8( "" );
		}
		packet->writeInt64( pet.nOwnerId );
		packet->writeUTF8( pet.strOwnerName );
		packet->writeInt32( pet.nPoints );
		++nCount;
	}

	uint32_t nFinalOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( nFinalOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_GAME_RANK_DATA );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nIndex, packet);
}

void CRankManager::sendPlayerGuanWeiRank( uint16_t nIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( RT_PLAYER_GUAN_WEI );
	packet->writeInt32( m_nRefreshTime );

	uint32_t nOffset = packet->getWOffset();

	int16_t nCount = 0;
	packet->writeInt16( nCount );
	for ( uint32_t i = 0; i < m_vPlayerGuanWeiRank.size(); ++i )
	{
		PlayerInfo player = m_vPlayerGuanWeiRank[i];
		packet->writeInt8( i+1 );
		packet->writeInt64( player.nCharId );
		packet->writeInt8( player.nJob );
		packet->writeUTF8( player.strName );
		Family* pFamily = FAMILY_MANAGER.GetFamily( player.nFamilyId );
		if ( pFamily != NULL )
		{
			packet->writeUTF8( pFamily->GetName() );
		}
		else
		{
			packet->writeUTF8( "" );
		}
		packet->writeInt32( player.nGuanWei );
		++nCount;
	}

	uint32_t nFinalOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( nFinalOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_GAME_RANK_DATA );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nIndex, packet);
}
