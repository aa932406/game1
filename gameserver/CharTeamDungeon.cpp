#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharTeamDungeon.h"

using namespace Answer;

CExtCharTeamDungeon::CExtCharTeamDungeon()
{
	OnCleanUp();
}

CExtCharTeamDungeon::~CExtCharTeamDungeon()
{
}

void CExtCharTeamDungeon::OnCleanUp()
{
}

void CExtCharTeamDungeon::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_TEAM_DUNGEON_CREATE );						// ´´½¨×é¶Ó¸±±¾ 
	procList.push_back( CM_TEAM_DUNGEON_JOIN );							// ¼ÓÈë×é¶Ó¸±±¾
	procList.push_back( CM_TEAM_DUNGEON_START );						// ×é¶Ó¸±±¾¿ªÆô
	procList.push_back( IM_SOCIAL_GAME_TEAM_DUNGEON_START );			// ×é¶Ó¸±±¾¿ªÆô
	procList.push_back( IM_SOCIAL_GAME_TEAM_DUNGEON_UPDATE_INFO );		// ×é¶Ó¸±±¾¸üÐÂÐÅÏ¢
}

int32_t CExtCharTeamDungeon::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
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
	case CM_TEAM_DUNGEON_CREATE:					return onTeamDungeonCreate( inPacket );
	case CM_TEAM_DUNGEON_JOIN:						return onTeamDungeonJoin( inPacket );
	case CM_TEAM_DUNGEON_START:						return onTeamDungeonStart( inPacket );
	case IM_SOCIAL_GAME_TEAM_DUNGEON_START:			return onSocialTeamDungeonStart( inPacket );
	case IM_SOCIAL_GAME_TEAM_DUNGEON_UPDATE_INFO:	return onSocialTeamDungeonUpdateInfo( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtCharTeamDungeon::onTeamDungeonCreate( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t	nDungeonId	= inPacket->readInt32();
	int32_t nLimitBattle= inPacket->readInt32();
	CfgDungeon* pCfgDungeon = CFG_DATA.getDungeon( nDungeonId );
	if (pCfgDungeon == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if ( !checkTeamDungeon( *pCfgDungeon ) )
	{
		return ERR_INVALID_DATA;
	}

	// Í¬²½µ½Éç»á·þÎñÆ÷
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_TEAM_DUNGEON_CREATE );
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nDungeonId );
	packet->writeInt32( nLimitBattle );
	packet->writeInt32( GAME_SERVICE.getLine() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
	return ERR_OK;
}

int32_t CExtCharTeamDungeon::onTeamDungeonJoin( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t	nId			= inPacket->readInt32();
	int32_t	nDungeonId	= inPacket->readInt32();
	CfgDungeon* pCfgDungeon = CFG_DATA.getDungeon( nDungeonId );
	if (pCfgDungeon == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if ( !checkTeamDungeon( *pCfgDungeon ) )
	{
		return ERR_INVALID_DATA;
	}

	// Í¬²½µ½Éç»á·þÎñÆ÷
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_TEAM_DUNGEON_JOIN );
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nId );
	packet->writeInt32( nDungeonId );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
	return ERR_OK;
}

int32_t CExtCharTeamDungeon::onTeamDungeonStart( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	// Í¬²½µ½Éç»á·þÎñÆ÷
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_TEAM_DUNGEON_START );
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
	return ERR_OK;
}

void CExtCharTeamDungeon::LeaveTeamDungeon()
{
	if ( !IsInTeamDungeon() )
	{
		return;
	}

	// Í¬²½µ½Éç»á·þÎñÆ÷
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_TEAM_DUNGEON_LEAVE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

int32_t CExtCharTeamDungeon::onSocialTeamDungeonStart( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nLine = inPacket->readInt32();
	if ( nLine != GAME_SERVICE.getLine() )
	{
		// TODO:ÇÐ»»µ½¸±±¾ÏßÂ·
	}
	return ERR_OK;
}

int32_t CExtCharTeamDungeon::onSocialTeamDungeonUpdateInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	m_nId			= inPacket->readInt32();
	m_nDungeonId	= inPacket->readInt32();
	m_nLeader		= inPacket->readInt64();
	
	return ERR_OK;
}

bool CExtCharTeamDungeon::IsFunctionOpen() const
{
	return true;
}

bool CExtCharTeamDungeon::IsInTeamDungeon() const
{
	return m_nId > 0;
}

bool CExtCharTeamDungeon::IsTeamDungeonLeader() const
{
	return m_pPlayer != NULL && m_pPlayer->getCid() == m_nLeader;
}

bool CExtCharTeamDungeon::checkTeamDungeon( const CfgDungeon& cfgDungeon ) const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	if ( cfgDungeon.type != DT_TEAM )
	{
		return false;
	}

	tm localNow = m_pPlayer->getLocalNow();
	// ÈÕÆÚÅÐ¶¨
	if ( ( cfgDungeon.weekday & ( 1 << GetWeekDay( localNow.tm_wday ) ) ) == 0 )
	{
		return false;
	}

	// Ê±¼äÅÐ¶¨
	if ( localNow.tm_hour < cfgDungeon.start_hour || localNow.tm_hour > cfgDungeon.end_hour )
	{
		return false;
	}

	// µÈ¼¶ÅÐ¶¨
	if ( m_pPlayer->getLevel() < cfgDungeon.level || m_pPlayer->getLevel() > cfgDungeon.maxLevel )
	{
		return false;
	}

	// Ç°ÖÃ¸±±¾ÅÐ¶¨
	if ( cfgDungeon.last_id > 0 )
	{
		if ( !m_pPlayer->GetOperateLimit().CheckIsLimitedForever( PR_DUNGEON_COMPLETED_BEING + cfgDungeon.last_id ) )
		{
			return false;
		}
	}

	return true;
}

// ========== æ–°ç‰ˆæœ¬æ·»åŠ æ–¹æ³• - TeamDungeon ==========
int32_t CExtCharTeamDungeon::onSocialTeamDungeonCost( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

// ========== æ–°ç‰ˆæœ¬æ·»åŠ æ–¹æ³• - Auction ==========
int32_t CExtCharAuction::onAddEquip( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

// ========== æ–°ç‰ˆæœ¬æ·»åŠ æ–¹æ³• - JueWei ==========
void CJueWei::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
}

int32_t CJueWei::onAskJueWeiLevelUp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

