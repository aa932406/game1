#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharTeam.h"

using namespace Answer;

CExtCharTeam::CExtCharTeam()
{
	OnCleanUp();
}

CExtCharTeam::~CExtCharTeam()
{
}

void CExtCharTeam::OnCleanUp()
{
	m_nTeamId				= 0;
	m_nLastQueryTeamTick	= 0;
	m_nLeaderId				= 0;
	m_strLeaderName			= "";
	m_lstMember.clear();
}

void CExtCharTeam::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_QUERY_TEAMS_AROUND );					// 搜寻附近队伍
	procList.push_back( CM_TEAM_SET_AUTO_OPERATE );					// 组队默认设置
	procList.push_back( IM_SOCIAL_GAME_UPDATE_TEAM_INFO );			// 更新组队信息
}

int32_t CExtCharTeam::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !IsFunctionOpen() )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case CM_QUERY_TEAMS_AROUND:				return onQueryTeamsAround( inPacket );
	case CM_TEAM_SET_AUTO_OPERATE:			return onSetTeamAutoOperate( inPacket );
	case IM_SOCIAL_GAME_UPDATE_TEAM_INFO:	return onUpdateTeamInfo( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtCharTeam::onQueryTeamsAround( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap )
	{
		return ERR_INVALID_DATA;
	}

	// 做个时间限制吧 先弄个5秒
	int64_t nCurTick = m_pPlayer->getTick();
	if (  nCurTick - m_nLastQueryTeamTick < 5000 )
	{
		return ERR_INVALID_DATA;
	}

	m_nLastQueryTeamTick = nCurTick;
	pMap->sendTeamsInMap( m_pPlayer );
	return ERR_OK;
}

int32_t CExtCharTeam::onSetTeamAutoOperate( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t	bAutoAcceptInvite	= inPacket->readInt8();
	int8_t	bAutoAcceptApply	= inPacket->readInt8();

	m_pPlayer->GetOperateLimit().UpdateLimitCount( PR_TEAM_AUTO_ACCEPT_INVITE, bAutoAcceptInvite );
	m_pPlayer->GetOperateLimit().UpdateLimitCount( PR_TEAM_AUTO_ACCEPT_APPLY, bAutoAcceptApply );
	UpdateTeamSetting();
	return ERR_OK;
}

int32_t CExtCharTeam::onUpdateTeamInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t nOldNum = m_lstMember.size();
	m_lstMember.clear();
	int32_t TeamId	= inPacket->readInt32();
	if ( TeamId != m_nTeamId )
	{
		m_nTeamId = TeamId;
		m_pPlayer->GetAchievemnet().AddAchievement( AT_TEAM );
	}
	m_nLeaderId		= inPacket->readInt64();
	m_strLeaderName = inPacket->readUTF8(true);

	int8_t	nMemberCount = inPacket->readInt8();
	for ( int8_t i = 0; i < nMemberCount; ++i )
	{
		CharId_t nCharId	= inPacket->readInt64();
		std::string strName	= inPacket->readUTF8(true);
		int16_t	nIndex		= inPacket->readInt16();
		m_lstMember.push_back( TeamMember( nCharId, strName, nIndex ) );
	}

	if ( nOldNum != nMemberCount )
	{
		int32_t nOldHPRatio = CFG_DATA.GetTeamTable().GetTeamHPRatio( nOldNum );
		int32_t nNewHPRatio = CFG_DATA.GetTeamTable().GetTeamHPRatio( nMemberCount );
		if ( nOldHPRatio > 0 )
		{
			m_pPlayer->AddBuffAttrRatio( CObjAttrs::ATTR_HP, -1*nOldHPRatio );
		}
		if ( nNewHPRatio > 0 )
		{
			m_pPlayer->AddBuffAttrRatio( CObjAttrs::ATTR_HP, nNewHPRatio );
		}
		m_pPlayer->recalcAttr();
	}

	m_pPlayer->setSyncStatusFlag();
	m_pPlayer->setSyncToTeamFlag();
	return ERR_OK;
}

bool CExtCharTeam::IsInTeam() const
{
	return m_nTeamId > 0;
}

bool CExtCharTeam::IsLeader() const
{
	return m_pPlayer != NULL && m_pPlayer->getCid() == m_nLeaderId;
}

int32_t CExtCharTeam::GetTeamId() const
{
	return m_nTeamId;
}

CharId_t CExtCharTeam::GetLeaderId() const
{
	return m_nLeaderId;
}

std::string CExtCharTeam::GetLeaderName() const
{
	return m_strLeaderName;
}

int32_t CExtCharTeam::GetMemberCount() const
{
	return m_lstMember.size();
}

bool CExtCharTeam::IsFunctionOpen() const
{
	if ( !m_pPlayer )
		return false;
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_DUAN_ZHAO );
}

void CExtCharTeam::Broadcast( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return;
	}

	uint32_t oldSize = inPacket->getSize();
	uint32_t nsize = m_lstMember.size();
	uint32_t addonSize = (nsize+1)*(sizeof(int16_t));
	if (inPacket->rightShift(addonSize))
	{
		inPacket->writeInt16(static_cast<int16_t>(nsize));
		for ( TeamMemberList::iterator it = m_lstMember.begin(); it != m_lstMember.end(); ++it)
		{
			inPacket->writeInt16( it->nIndex );
		}
		inPacket->setSize(oldSize+addonSize);
		GAME_SERVICE.sendPacket(inPacket);
	}
	else
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(inPacket->getType(), inPacket->getProc(), (nsize+1)*sizeof(int16_t) + inPacket->getSize());
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt16(static_cast<int16_t>(nsize));
		for ( TeamMemberList::iterator it = m_lstMember.begin(); it != m_lstMember.end(); ++it)
		{
			inPacket->writeInt16( it->nIndex );
		}
		packet->write(inPacket->getBuffer(), inPacket->getSize());
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacket(packet);
		inPacket->destroy();
	}
}

void CExtCharTeam::LeaveTeam()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !IsInTeam() )
	{
		return;
	}

	// 将消息发送到到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_LEAVE_TEAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

const TeamMemberList& CExtCharTeam::GetTeamMembers() const
{
	return m_lstMember;
}

void CExtCharTeam::GetTeamMembers( CharIdList& members ) const
{
	TeamMemberList::const_iterator iter = m_lstMember.begin();
	TeamMemberList::const_iterator eiter = m_lstMember.end();
	for ( ; iter != eiter; ++iter )
	{
		members.push_back( iter->nCharId );
	}
}

void CExtCharTeam::BroadcastBasicData()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !IsInTeam() )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TEAM_MEMBER_BASIC_DATA );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeInt32( m_pPlayer->getLevel() );
	packet->writeInt32( m_pPlayer->GetHP() );
	packet->writeInt32( m_pPlayer->GetMaxHP() );
	packet->writeInt32( m_pPlayer->getMapId() );
	packet->writeInt32( m_pPlayer->getCurrentTile().x );
	packet->writeInt32( m_pPlayer->getCurrentTile().y );
	packet->writeInt32( m_pPlayer->getWeaponId() );
	packet->writeInt32( m_pPlayer->getClothesId() );

	packet->setSize( packet->getWOffset() );
	Broadcast( packet );
}

void CExtCharTeam::UpdateTeamSetting()
{
	int8_t bAutoAcceptInvite = (int8_t)m_pPlayer->getRecord( PR_TEAM_AUTO_ACCEPT_INVITE ); 
	int8_t bAutoAcceptApply  = (int8_t)m_pPlayer->getRecord( PR_TEAM_AUTO_ACCEPT_APPLY );
	int8_t bCanInvite		 = (int8_t)m_pPlayer->GetSysSettingInfo( SS_TEAM );
	int8_t bCanAddFriend	 = (int8_t)m_pPlayer->GetSysSettingInfo( SS_FRIEND );	//好友的设置放这里一起同步
	// 组队设置同步到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_SET_TEAM_AUTO_OPERATE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt8( bAutoAcceptInvite );
	packet->writeInt8( bAutoAcceptApply );
	packet->writeInt8( bCanInvite );
	packet->writeInt8( bCanAddFriend );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

