#include "stdafx.h"
#include "CharDraw.h"
#include "Player.h"
#include "GameService.h"
#include "CfgData.h"
#include "FestivalDoubleEleven.h"
#include "UniteServer.h"

using namespace Answer;

// 协议号 920 - WXJ 范围 (900~998)
#define CM_DRAW 920

CExtCharDraw::CExtCharDraw()
{
	OnCleanUp();
}

CExtCharDraw::~CExtCharDraw()
{
}

void CExtCharDraw::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_DRAW );
}

int32_t CExtCharDraw::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( nProcId == CM_DRAW )
	{
		return OnDraw( inPacket );
	}

	return ERR_OK;
}

int32_t CExtCharDraw::OnDraw( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType = inPacket->readInt8();
	if ( !canDraw( nType ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nGetItemList = GetItemRecord( nType );

	const CfgDrawTable* pDrawTable = CFG_DATA.GetDrawTable();
	CfgDrawReward pReward;
	pDrawTable->RandomReward( &pReward, nType, &nGetItemList );

	if ( pReward.vItem.empty() )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->GetBag().AddItem( pReward.vItem, ICR_DRAW_GET_REWARD2 ) )
	{
		return ERR_INVALID_DATA;
	}

	addDrawTimes( nType, nGetItemList );

	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), pReward.nIndex );

	if ( pReward.nBroad > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet != NULL )
		{
			packet->writeInt32( pReward.nBroad );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( pReward.nIndex );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
		}
	}

	return ERR_OK;
}

int32_t CExtCharDraw::GetItemRecord( int8_t nType )
{
	switch ( nType )
	{
	case 1:
		return 0;
	case 2:
		return m_pPlayer->getRecord( 1608 );
	case 3:
		return m_pPlayer->getRecord( 1633 );
	case 4:
		return m_pPlayer->getRecord( 1404 );
	}
	return 0;
}

bool CExtCharDraw::canDraw( int8_t nType )
{
	switch ( nType )
	{
	case 1:
		{
			int32_t nDrawTimes = m_pPlayer->GetCharTaskCycle().GetDrawTimes();
			int32_t nLimitCount = m_pPlayer->GetOperateLimit().GetLimitCount( 2032 );
			if ( nDrawTimes > nLimitCount )
			{
				return true;
			}
			break;
		}
	case 2:
		{
			CFestivalDoubleEleven* pFDE = FESTIVAL_DOUBLE_ELEVEN;
			if ( pFDE && pFDE->CanUseXiaoFeiDraw( m_pPlayer ) )
			{
				return true;
			}
			break;
		}
	case 3:
		{
			CFestivalDoubleEleven* pFDE = FESTIVAL_DOUBLE_ELEVEN;
			if ( pFDE && pFDE->CanUseRechargeDraw( m_pPlayer ) )
			{
				return true;
			}
			break;
		}
	case 4:
		{
			CUniteServer* pUS = UNITE_SERVER;
			if ( pUS && pUS->GetCanXiaoFeiDrawTime( m_pPlayer ) > 0 )
			{
				return true;
			}
			break;
		}
	}
	return false;
}

void CExtCharDraw::addDrawTimes( int8_t nType, int32_t nGetItemRecord )
{
	switch ( nType )
	{
	case 1:
		m_pPlayer->GetOperateLimit().AddLimitCount( 2032, 1 );
		break;
	case 2:
		m_pPlayer->updateRecord( 1608, nGetItemRecord );
		m_pPlayer->GetOperateLimit().AddLimitCount( 1606, 1 );
		{
			CFestivalDoubleEleven* pFDE = FESTIVAL_DOUBLE_ELEVEN;
			if ( pFDE ) pFDE->SendIconState( m_pPlayer );
		}
		break;
	case 3:
		m_pPlayer->updateRecord( 1633, nGetItemRecord );
		m_pPlayer->GetOperateLimit().AddLimitCount( 1632, 1 );
		{
			CFestivalDoubleEleven* pFDE = FESTIVAL_DOUBLE_ELEVEN;
			if ( pFDE ) pFDE->SendIconState( m_pPlayer );
		}
		break;
	case 4:
		m_pPlayer->updateRecord( 1404, nGetItemRecord );
		m_pPlayer->GetOperateLimit().AddLimitCount( 1403, 1 );
		{
			CUniteServer* pUS = UNITE_SERVER;
			if ( pUS ) pUS->SendIconState( m_pPlayer );
		}
		break;
	}
}
