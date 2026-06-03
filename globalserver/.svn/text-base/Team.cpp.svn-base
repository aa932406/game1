#include "stdafx.h"

#include "SocialService.h"
#include "SocialPlayer.h"
#include "Team.h"
#include "TeamManager.h"

float XPExpKey[MAX_TEAM_MEMBER_COUNT+1] = { 0, 1.5f, 2.0f, 2.5f, 3.0f };

using namespace Answer;

Team::Team( int32_t nTeamId, SocialPlayer* player )
	: m_nTeamId( nTeamId ), m_pLeader( player )
{
	bzero( m_arrMembers, sizeof( m_arrMembers ) );
	m_arrMembers[0] = player;
	m_nMemberCount = 1;
	m_lstApply.clear();
}

Team::~Team()
{

}

void Team::cleanUp()
{
	m_nTeamId = 0;
	m_nMemberCount = 0;
	m_pLeader = NULL;
	bzero( m_arrMembers, sizeof( m_arrMembers ) );
}

bool Team::IsFull() const
{
	return m_nMemberCount >= MAX_TEAM_MEMBER_COUNT;
}

bool Team::IsInTeam( CharId_t nCharId ) const
{
	if ( nCharId <= 0 )
	{
		return false;
	}

	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( m_arrMembers[i] != NULL && m_arrMembers[i]->getCid() == nCharId )
		{
			return true;
		}
	}
	return false;
}

int32_t Team::GetId() const
{
	return m_nTeamId;
}

int8_t Team::GetMemberCount() const
{
	return m_nMemberCount;
}

void Team::GetMembers( TeamMemberList& members ) const
{
	if ( m_pLeader != NULL )
	{
		members.push_back( TeamMember( m_pLeader->getCid(), m_pLeader->getName(), m_pLeader->getGateIndex() ) );
	}

	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		if ( m_pLeader == m_arrMembers[i] )
		{
			continue;
		}

		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			return;
		}

		members.push_back( TeamMember( pMember->getCid(), pMember->getName(), pMember->getGateIndex() ) );
	}
}

bool Team::AllMembersXpStateStop()
{
	bool bFlg = true;
	for ( int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i )
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			continue;;
		} 
		if ( pMember->GetXPState() != XS_STOP )
		{
			bFlg = false;
			break;
		} 
	}
	return bFlg;
}

SocialPlayer* Team::GetLeader() const
{
	return m_pLeader;
}

bool Team::SetLeader( CharId_t nCid )
{
	if ( NULL == m_pLeader || m_pLeader->getCid() == nCid )
	{
		return false;
	}

	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			continue;;
		}
		if ( pMember->getCid() == nCid )
		{
			SocialPlayer* pOldLeader = m_pLeader;
			m_pLeader = pMember;
			//m_pLeader->SendGameUpdateTeamInfo();		// 更新人物组队状态到游戏服
			//pOldLeader->SendGameUpdateTeamInfo();
			BroadcastMembers();
			return true;
		}
	}

	return false;
}

int32_t Team::MemberJoin( SocialPlayer* player )
{
	if ( NULL == player || NULL == m_pLeader )
	{
		return ERR_INVALID_DATA;
	}
	if ( IsInTeam( player->getCid() ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t slot = 0;
	while ( slot < MAX_TEAM_MEMBER_COUNT )
	{
		if ( NULL == m_arrMembers[slot] )
		{
			break;
		}
		slot++;
	}
	if ( slot == MAX_TEAM_MEMBER_COUNT )
	{
		return ERR_INVALID_DATA;
	}

	m_arrMembers[slot] = player;
	++m_nMemberCount;

	player->SetTeam( this );
	//player->SendGameUpdateTeamInfo();
	//m_pLeader->SendGameUpdateTeamInfo();

	BroadcastMembers();

	if ( player->GetXPState() == XS_DO_SKILL )
	{
		player->SetJoinWithXP();
	}
	else
	{
		avrageXP();	// 平分XP
	}
	return ERR_OK;
}

bool Team::MemberLeave( CharId_t nCid, LEAVE_TEAM_REASON nReason )
{
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			return false;
		}
		if ( pMember->getCid() == nCid )
		{
			sendLeaveTeam( nCid, nReason );
			for ( int32_t j = i; j < MAX_TEAM_MEMBER_COUNT-1; ++j )
			{
				m_arrMembers[j] = m_arrMembers[j+1];
			}

			m_arrMembers[MAX_TEAM_MEMBER_COUNT-1] = 0;
			--m_nMemberCount;

			pMember->ResetXP();
			pMember->SetTeam( NULL );
			if ( m_arrMembers[0] != NULL )
			{
				if ( m_pLeader == pMember )
				{
					m_pLeader = m_arrMembers[0];
				}

				//m_pLeader->SendGameUpdateTeamInfo();
				pMember->SendGameUpdateTeamInfo();
				BroadcastMembers();
			}
			else
			{
				pMember->SendGameUpdateTeamInfo();
				TEAM_MANAGER.DeleteTeam( m_nTeamId );
			}
			return true;
		}
	}
	return false;
}

void Team::Destroy()
{
	sendLeaveTeam( 0, LTR_DESTROY );
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			continue;
		}

		pMember->ResetXP();
		pMember->SetTeam( NULL );
		pMember->SendGameUpdateTeamInfo();
	}
	TEAM_MANAGER.DeleteTeam( m_nTeamId );
}

void Team::Broadcast(Answer::NetPacket *inPacket)
{
	if (inPacket == NULL)
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

	SOCIAL_SERVICE.broadcast( indexes, inPacket );
}

void Team::BroadcastMembers()
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

	int32_t nMemberCount = 0;
	packet->writeInt32( m_nTeamId );
	packet->writeInt64( m_pLeader->getCid() );

	int32_t nOffSet = packet->getWOffset();
	packet->writeInt8( nMemberCount );
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			continue;
		}

		packet->writeInt64( pMember->getCid() );
		packet->writeUTF8( pMember->getName() );
		packet->writeInt8( pMember->getSex() );
		packet->writeInt8( pMember->getJob() );
		packet->writeInt32( 0 );				// 0
		packet->writeInt32( 0 );				// HP
		packet->writeInt32( 0 );				// MaxHP
		packet->writeInt32( 0 );				// MapId
		packet->writeInt32( 0 );				// MapX
		packet->writeInt32( 0 );				// MapY
		packet->writeInt32( 0 );				// WeaponId
		packet->writeInt32( 0 );				// ClothesId
		++nMemberCount;
	}

	uint32_t nOldOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt8( nMemberCount );
	packet->setWOffset( nOldOffSet );

	packet->setProc( SM_TEAM_MEMBERS );
	packet->setSize( packet->getWOffset() );
	Broadcast( packet );

	// 让每个队员发送自身的信息给其他队员
	updateGameAllMemberInfo();
}

void Team::updateGameAllMemberInfo()
{
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			continue;
		}

		pMember->SendGameUpdateTeamInfo();
	}
}

void Team::sendLeaveTeam( CharId_t nCid, LEAVE_TEAM_REASON nReason )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt64( nCid );
	packet->writeInt8( nReason );

	packet->setProc( SM_TEAM_LEAVED );
	packet->setSize( packet->getWOffset() );
	Broadcast( packet );
}

SocialPlayer* Team::CheckInApplyList( CharId_t nCid ) const
{
	ApplyList::const_iterator iter = m_lstApply.begin();
	ApplyList::const_iterator eiter = m_lstApply.end();
	for ( ; iter != eiter; ++iter )
	{
		SocialPlayer* pApplyer = *iter;
		if ( pApplyer != NULL && pApplyer->getCid() == nCid )
		{
			return pApplyer;
		}
	}
	return NULL;
}

void Team::AddApplyer( SocialPlayer* pApplyer )
{
	if ( NULL == pApplyer )
	{
		return;
	}

	if ( CheckInApplyList( pApplyer->getCid() ) )
	{
		return;
	}

	m_lstApply.push_back( pApplyer );
}

void Team::RemoveApplyer( CharId_t nCid )
{
	ApplyList::iterator iter = m_lstApply.begin();
	ApplyList::iterator eiter = m_lstApply.end();
	for ( ; iter != eiter; ++iter )
	{
		SocialPlayer* pApplyer = *iter;
		if ( pApplyer != NULL && pApplyer->getCid() == nCid )
		{
			break;
		}
	}
	if ( iter != eiter )
	{
		m_lstApply.erase( iter );
	}
}

//void Team::AddXP()
//{
//	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
//	{
//		if ( m_arrMembers[i] != NULL )
//		{
//			m_arrMembers[i]->AddXP();
//		}
//	}
//}

bool Team::IsInXP()
{
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		if ( m_arrMembers[i] != NULL && m_arrMembers[i]->GetXPState() == XS_DO_SKILL )
		{
			return true;
		}
	}
	return false;
}

void Team::resetXP( int32_t nValue )
{
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		if ( m_arrMembers[i] != NULL )
		{
			m_arrMembers[i]->ResetXP( nValue );
		}
	}
}

void Team::CheckEndXP()
{
	bool bNeedBroad = false;
	int32_t nMenberCount = 0;
	int32_t nTotalXP = 0;
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( pMember != NULL )
		{
			if ( !pMember->IsLearnedXP() )
			{
				continue;
			}
			if ( pMember->GetXPState() == XS_DO_SKILL )
			{
				return;
			}
			else if ( pMember->GetXPState() == XS_OTHER_END )
			{
				bNeedBroad = false;
			}
			else if ( pMember->GetXPState() == XS_END )
			{
				bNeedBroad = true;
			}
			nTotalXP += pMember->GetXP();
			++nMenberCount;
		}
	}

	int32_t nFinalXP = nTotalXP;
	if ( nMenberCount > 0 )
	{
		nFinalXP = nTotalXP / nMenberCount;
	}

	if ( bNeedBroad )
	{
		broadcastXPRecord();
	}

	resetXP( nFinalXP );
}

void Team::avrageXP()
{
	int32_t nMenberCount = 0;
	int32_t nTotalXP = 0;
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( pMember != NULL )
		{
			if ( pMember->GetXPState() == XS_DO_SKILL )
			{
				return;
			}
			if ( !pMember->IsLearnedXP() )
			{
				continue;
			}

			nTotalXP += pMember->GetXP();
			++nMenberCount;
		}
	}

	int32_t nFinalXP = nTotalXP;
	if ( nMenberCount > 0 )
	{
		nFinalXP = nTotalXP / nMenberCount;
		resetXP( nFinalXP );
	}
}

void Team::broadcastXPRecord()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	float nKey = getXPExpKey();

	int8_t	nMemberCount = 0;
	int32_t nOffSet = packet->getWOffset();
	packet->writeInt8( nMemberCount );
	for (int32_t i = 0; i < MAX_TEAM_MEMBER_COUNT; ++i)
	{
		SocialPlayer* pMember = m_arrMembers[i];
		if ( NULL == pMember )
		{
			continue;
		}

		int64_t nExp = pMember->GetXPAddExp();
		int64_t nFinalExp = static_cast<int64_t>( nExp * nKey );
		pMember->SendGameAddExp( nFinalExp );

		packet->writeInt64( pMember->getCid() );
		packet->writeInt64( nFinalExp );
		++nMemberCount;
	}

	uint32_t nOldOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt8( nMemberCount );
	packet->setWOffset( nOldOffSet );
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_XP_EXP_BOARD );

	Broadcast( packet );
}

float Team::getXPExpKey()
{
	int32_t nMemberCount = GetMemberCount();
	return XPExpKey[nMemberCount];
}
