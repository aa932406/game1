
#include <algorithm>

#include "stdafx.h"
#include "CharSkill.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "PDUDefine.h"

using namespace Answer;


CExtCharSkill::CExtCharSkill()
{
	OnCleanUp();
}

CExtCharSkill::~CExtCharSkill()
{
}

void CExtCharSkill::OnCleanUp()
{
	m_bXP = false;
	m_nXP = 0;
	m_nSelectXP = 0;
	m_nXPAddExp = 0;
	m_nLastTick = 0;
	m_nStartTick = 0;
}

void CExtCharSkill::OnLoadFromDB( const PlayerDBData& dbData )
{
}

void CExtCharSkill::OnSaveToDB( PlayerDBData& dbData )
{

}

void CExtCharSkill::OnUpdate( int64_t curTick )
{
	checkXP( curTick );
}

void CExtCharSkill::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back ( CM_START_XP );
	procList.push_back ( IM_SOCIAL_GAME_UPDATE_XP );
	procList.push_back ( IM_SOCIAL_GAME_ADD_XP );
}

int32_t CExtCharSkill::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch ( nProcId )
	{
	case CM_START_XP:							return onStartXP( inPacket );
	case IM_SOCIAL_GAME_UPDATE_XP:				return onSocialUpdateXP( inPacket );
	case IM_SOCIAL_GAME_ADD_XP:					return onSocialAddExp( inPacket );
	default:	break;
	}
	return ERR_OK;
}

int32_t CExtCharSkill::onStartXP( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nSkillId = inPacket->readInt32();
	if ( IsInXP() )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_nXP < MAX_XP_POINTS )
	{
		return ERR_INVALID_DATA;
	}

	Map* pMap = m_pPlayer->getMap();
	if ( pMap != NULL )
	{
		if ( !pMap->CanUseXP() )
		{
			return ERR_INVALID_DATA;
		}
	}

	bool bFind = false;
	for (MemChrSkillVector::iterator it = m_pPlayer->m_skills.begin(); it != m_pPlayer->m_skills.end(); ++it)
	{
		if ( it->id == nSkillId )
		{
			bFind = true;
			break;
		}
	}

	if ( !bFind )
	{
		return ERR_INVALID_DATA;
	}

	startXP( nSkillId );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_nSelectXP );
	return ERR_OK;
}

int32_t CExtCharSkill::onSocialUpdateXP( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	m_nXP = inPacket->readInt32();
	m_nStartTick = m_pPlayer->getTick();
	sendXP();
	return ERR_OK;
}

int32_t CExtCharSkill::onSocialAddExp( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int64_t nAddExp = inPacket->readInt64();
	AddPlayerExp( static_cast<int32_t>(nAddExp) );
	return ERR_OK;
}

void CExtCharSkill::AddPlayerExp( int32_t Exp )
{
	m_pPlayer->addExp( Exp );
	m_pPlayer->GetCharPet().OnAddExp( Exp );
	m_pPlayer->GetExpBall().AddBallExp( Exp );
}

bool CExtCharSkill::IsInXP() const
{
	return m_bXP;
}

SkillId_t CExtCharSkill::GetSelectedXP() const
{
	return m_nSelectXP;
}

void CExtCharSkill::AddMonsterExp( int64_t nAddExp )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( IsInXP() )
	{
		if ( m_pPlayer->IsInTeam() && m_pPlayer->GetCharTeam().GetMemberCount() > 1 )
		{
			m_nXPAddExp += nAddExp;
		}
		else
		{
			int64_t nFinalExp = static_cast<int64_t>( nAddExp * 1.5f );
			m_nXPAddExp += nFinalExp;
// 			m_pPlayer->addExp( nFinalExp );
// 			m_pPlayer->GetExpBall().AddBallExp( static_cast<int32_t>(nFinalExp) );
// 			m_pPlayer->GetCharPet().OnAddExp( nFinalExp );
		}
	}
}

void CExtCharSkill::SendXpRecord()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_XP_EXP_BOARD );
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt8( 1 );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeInt64( m_nXPAddExp );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CExtCharSkill::FillXP()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Map* pMap = m_pPlayer->getMap();
	if ( pMap != NULL )
	{
		if ( !pMap->CanUseXP() )
		{
			return;
		}
	}

	SetInXP( false );
	m_nXP = MAX_XP_POINTS;
	m_nSelectXP = 0;
	m_nStartTick = 0;
	sendXP();
}

void CExtCharSkill::LearnXPSkill()
{
	if ( IsLearnedXPSkill() )
	{
		return;
	}
	if ( m_pPlayer != NULL )
	{
		m_pPlayer->GetOperateLimit().AddLimitCount( PR_LEARNED_XP_SKILL, 1 );
		m_pPlayer->sendUpdateSocialPlayerInfo( PII_LEARN_XP_SKILL, 1 );
	}
}

void CExtCharSkill::checkXP( int64_t curTick )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( curTick - m_nLastTick < 1000 )
	{
		return;
	}

	if ( !IsLearnedXPSkill() )
	{
		return;
	}

	Map* pMap = m_pPlayer->getMap();
	if ( pMap == NULL )
	{
		return;
	}
	if ( !pMap->CanUseXP() || pMap->IsFullXP() )
	{
		return;
	}
	if ( 0 == m_nStartTick )
	{
		m_nStartTick = curTick;
	}
	if ( IsInXP() )
	{
		if ( curTick - m_nStartTick > XP_TIME )
		{
			endXP();
			m_nStartTick = curTick;		
		}
	}
	else
	{
		if ( m_nXP >= MAX_XP_POINTS )
		{
			if ( curTick - m_nStartTick > XP_WAIT_SELECT_TIME )
			{
				m_nStartTick  = curTick;
				sendSocialBreakXP();
			}
		}
		else
		{
			if ( curTick - m_nStartTick > ADD_XP_TIME )
			{
				m_nStartTick = curTick;
				sendSocialAddXP();
			}
		}
	}
}

void CExtCharSkill::endXP()
{
	SetInXP( false );
	m_nSelectXP = 0;
	sendSocialEndXP();
}

void CExtCharSkill::DieResetXp()
{
	if ( IsInXP() )
	{
		SetInXP( false );
		m_nSelectXP		= 0;
		m_nStartTick	= 0;
	}
}

void CExtCharSkill::ClearXP()
{
	if ( IsInXP() )
	{
		SetInXP( false );
		m_nSelectXP		= 0;
		m_nStartTick	= 0;
	}
	sendSocialEndXP();
}

bool CExtCharSkill::IsLearnedXPSkill() const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	return m_pPlayer->GetOperateLimit().CheckIsLimitedForever( PR_LEARNED_XP_SKILL );
}

void CExtCharSkill::sendXP()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	// 发送客户端XP技能
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_XP_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( IsInXP() ? 1 : 0 );
	packet->writeInt32( m_nXP );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CExtCharSkill::sendSocialAddXP( int32_t AddXp )				// XP增加
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	// 将消息发送到到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_ADD_XP );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( AddXp );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharSkill::sendSocialStartXP()				// 开始
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	// 将消息发送到到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_START_XP );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharSkill::sendSocialEndXP()				// 结束
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( m_pPlayer->getMap() == NULL )
	{
		return;
	}

	if ( ( !m_pPlayer->IsInTeam() || m_pPlayer->GetCharTeam().GetMemberCount() <= 1 )  && m_pPlayer->getMap()->CanUseXP() )
	{
		AddPlayerExp( static_cast<int32_t>(m_nXPAddExp) );
		SendXpRecord();
	}

	// 将消息发送到到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_END_XP );
	if ( packet != NULL )
	{
		packet->writeInt32( m_pPlayer->getGateIndex() );
		packet->writeInt64( m_nXPAddExp );
		packet->setSize( packet->getWOffset() ); 
		GAME_SERVICE.sendPacket( packet );
	}

	// 结束后清空XP
	m_nXPAddExp = 0;
}

void CExtCharSkill::sendSocialBreakXP()				// 跳过
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	// 将消息发送到到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_BREAK_XP );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharSkill::SetInXP( bool bFlg )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( bFlg != m_bXP )
	{
		m_bXP = bFlg;
		m_pPlayer->setSyncStatusFlag();
	}
}

void CExtCharSkill::startXP( SkillId_t nSkillId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	SetInXP( true );
	m_nSelectXP = nSkillId;
	m_nXPAddExp = 0;
	m_nStartTick = m_pPlayer->getTick();
	sendSocialStartXP();
}
