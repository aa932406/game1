#include "stdafx.h"

#include "SocialService.h"
#include "SocialPlayer.h"
#include "TeamDungeon.h"
#include "TeamManager.h"

using namespace Answer;

TeamDungeon::TeamDungeon( int32_t nId, SocialPlayer* player, int32_t nDungeonId, int32_t battle, int32_t nLine )
	:m_nId( nId ), m_pLeader( player ), m_nDungeonId( nDungeonId ), m_nLimitBattle( battle ), m_nCreaterLine( nLine ), m_bAutoStart( 1 )	// 默认开启满员自动开始副本
{
	bzero( m_arrMembers, sizeof( m_arrMembers ) );
	m_arrMembers[0] = player;
	m_nMemberCount = 1;
}

TeamDungeon::~TeamDungeon()
{

}

int32_t TeamDungeon::GetId() const
{
	return m_nId;
}

int32_t TeamDungeon::GetDungeonId() const
{
	return m_nDungeonId;
}

int32_t TeamDungeon::GetLimitBattle() const
{
	return m_nLimitBattle;
}

SocialPlayer* TeamDungeon::GetLeader()
{
	return m_pLeader;
}

bool TeamDungeon::StartDungeon( SocialPlayer* player )
{
	if ( NULL == player || NULL == m_pLeader )
	{
		return false;
	}

	if ( player != m_pLeader )
	{
		return false;
	}

	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( NULL == m_arrMembers[i] )
		{
			continue;
		}
		if ( m_arrMembers[i] == m_pLeader )
		{
			continue;
		}
		if ( !m_arrMembers[i]->IsTeamDungeonReady() )
		{
			return false;
		}
	}

	sendGameCreateDungeon();
	sendGameStartDungeon();
	broadcastStartDungeon();
	return true;
}

bool TeamDungeon::MemberLeave( SocialPlayer* player )
{
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( m_arrMembers[i] == player )
		{
			player->SetTeamDungeon( NULL );
			m_arrMembers[i] = NULL;
			--m_nMemberCount;
			if ( 0 == m_nMemberCount )
			{
				TEAM_DUNGEON_MANAGER.RemoveDungeon( this );
				return true;
			}
			if ( m_pLeader == player )
			{
				setNewLeader();
				BroadcastMemberInfo();
			}
			broadcastMemberLeave( player->getCid(), LTR_NORMAL );
			return true;
		}
	}
	return false;
}

bool TeamDungeon::MemberJoin( SocialPlayer* player )
{
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( m_arrMembers[i] == NULL )
		{
			player->SetTeamDungeon( this );
			m_arrMembers[i] = player;
			++m_nMemberCount;
			BroadcastMemberInfo();
			return true;
		}
	}
	return false;
}

bool TeamDungeon::SetAutoStart( SocialPlayer* player, int8_t bAuto )
{
	if ( NULL == m_pLeader || NULL == player )
	{
		return false;
	}

	if ( player != m_pLeader )
	{
		return false;
	}

	if ( m_bAutoStart != bAuto )
	{
		m_bAutoStart = bAuto;
		BroadcastMemberInfo();
	}
	return false;
}

bool TeamDungeon::KickMember( SocialPlayer* player, CharId_t memberId )
{
	if ( NULL == m_pLeader || NULL == player )
	{
		return false;
	}

	if ( player != m_pLeader )
	{
		return false;
	}

	if ( m_pLeader->getCid() == memberId )
	{
		return false;
	}

	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( NULL == m_arrMembers[i] )
		{
			continue;
		}
		if ( m_arrMembers[i]->getCid() == memberId )
		{
			broadcastMemberLeave( m_arrMembers[i]->getCid(), LTR_KICKED );
			m_arrMembers[i]->SetTeamDungeon( NULL );
			m_arrMembers[i] = NULL;
			--m_nMemberCount;
			return true;
		}
	}
	return false;
}

void TeamDungeon::AppendInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_nId );
	if ( m_pLeader != NULL )
	{
		packet->writeUTF8( m_pLeader->getName() );
	}
	else
	{
		packet->writeUTF8( "" );
	}
	packet->writeInt8( m_nMemberCount );
	packet->writeInt32( m_nLimitBattle );
}

void TeamDungeon::BroadcastMemberInfo()
{
	if ( NULL == m_pLeader )
	{
		return;
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_nId );
	packet->writeInt32( m_nDungeonId );
	packet->writeInt64( m_pLeader->getCid() );
	packet->writeInt32( m_nLimitBattle );
	packet->writeInt8( m_bAutoStart );
	packet->writeInt8( m_nMemberCount );
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( m_arrMembers[i] != NULL )
		{
			packet->writeInt64( m_arrMembers[i]->getCid() );
			packet->writeUTF8( m_arrMembers[i]->getName() );
			packet->writeInt8( m_arrMembers[i]->getJob() );
			packet->writeInt8( m_arrMembers[i]->getSex() );
			packet->writeInt32( m_arrMembers[i]->getLevel() );
			packet->writeInt32( m_arrMembers[i]->GetBattle() );
			packet->writeInt8( m_arrMembers[i]->IsTeamDungeonReady() ? 1 : 0 );
		}
	}

	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_TEAM_DUNGEON_MEMBER_INFO );

	Broadcast( packet );
}

void TeamDungeon::Broadcast( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	Int16Vector indexes;
	indexes.reserve( MAX_TEAM_MEMBER_COUNT );
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		if ( m_arrMembers[i] != NULL )
		{
			indexes.push_back( m_arrMembers[i]->getGateIndex() );
		}
	}

	SOCIAL_SERVICE.broadcast( indexes, packet );
}

void TeamDungeon::setNewLeader()
{
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( m_arrMembers[i] != NULL )
		{
			m_pLeader = m_arrMembers[i];
			return;
		}
	}
}

void TeamDungeon::broadcastMemberLeave( CharId_t cid, int8_t reason )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( cid );
	packet->writeInt8( reason );

	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_TEAM_DUNGEON_MEMBER_LEAVE );

	Broadcast( packet );
}

void TeamDungeon::sendGameCreateDungeon()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_nCreaterLine );
	packet->writeInt32( m_nDungeonId );
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( NULL == m_arrMembers[i] )
		{
			packet->writeInt64( 0 );
		}
		else
		{
			packet->writeInt64( m_arrMembers[i]->getCid() );
		}
	}

	packet->setSize( packet->getWOffset() );
	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_SINGLE_GAME_TEAM_DUNGEON_CREATE );
	
	SOCIAL_SERVICE.sendPacket( packet );
}

void TeamDungeon::sendGameStartDungeon()
{
	if ( NULL == m_pLeader )
	{
		return;
	}

	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( NULL == m_arrMembers[i] )
		{
			continue;
		}
		m_arrMembers[i]->SendGameTeamDungeonStart( m_nCreaterLine );
	}
}

void TeamDungeon::broadcastStartDungeon()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_nId );

	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_TEAM_DUNGEON_START );

	Broadcast( packet );
}

bool TeamDungeon::CheckAutoStart()
{
	if ( m_bAutoStart == 0 )
	{
		return false;
	}
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( NULL == m_arrMembers[i] )
		{
			return false;
		}

		if ( !m_arrMembers[i]->IsTeamDungeonReady() )
		{
			return false;
		}
	}

	sendGameCreateDungeon();
	sendGameStartDungeon();
	broadcastStartDungeon();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TeamDungeonManager::TeamDungeonManager()
:m_nNextId( 1 )
{

}

TeamDungeonManager::~TeamDungeonManager()
{

}

bool TeamDungeonManager::RemoveDungeon( TeamDungeon* pDungeon )
{
	TeamDungeonList::iterator iter = m_lstTeamDungon.begin();
	TeamDungeonList::iterator eiter = m_lstTeamDungon.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == pDungeon )
		{
			m_lstTeamDungon.erase( iter );
			return true;
		}
	}
	return false;
}

void TeamDungeonManager::SendDungeonList( SocialPlayer* pPlayer, int32_t nDungeonId )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( nDungeonId );
	uint32_t offset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount );
	TeamDungeonList::iterator iter = m_lstTeamDungon.begin();
	TeamDungeonList::iterator eiter = m_lstTeamDungon.end();
	for ( ; iter != eiter; ++iter )
	{
		TeamDungeon* pTeamDungeon = *iter;
		if ( NULL == pTeamDungeon )
		{
			continue;
		}
		if ( pTeamDungeon->GetDungeonId() == nDungeonId )
		{
			pTeamDungeon->AppendInfo( packet );
			++nCount;
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_TEAM_DUNGEON_SEND_LIST );
	SOCIAL_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

TeamDungeon* TeamDungeonManager::CreateTeamDungeon( SocialPlayer* pPlayer, int32_t nDungeonId, int32_t battle, int32_t nLine )
{
	TeamDungeon* pDungeon = new TeamDungeon( m_nNextId, pPlayer, nDungeonId, battle, nLine );
	if ( NULL == pDungeon )
	{
		return pDungeon;
	}

	++m_nNextId;
	m_lstTeamDungon.push_back( pDungeon );
	return pDungeon;
}

TeamDungeon* TeamDungeonManager::GetTeamDungeon( int32_t nId )
{
	TeamDungeonList::iterator iter = m_lstTeamDungon.begin();
	TeamDungeonList::iterator eiter = m_lstTeamDungon.end();
	for ( ; iter != eiter; ++iter )
	{
		TeamDungeon* pTeamDungeon = *iter;
		if ( NULL == pTeamDungeon )
		{
			continue;
		}
		if ( pTeamDungeon->GetId() == nId )
		{
			return pTeamDungeon;
		}
	}

	return NULL;
}
