#include "stdafx.h"
#include "LevelRefining.h"
#include "Player.h"
#include "GameService.h"
#include "Timer.h"

using namespace Answer;

CLevelRefining::CLevelRefining()
{
}

CLevelRefining::~CLevelRefining()
{
}

void CLevelRefining::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_REFIN_INFO );
	procList.push_back( CM_REFIN_UPGRADE );
}

int32_t CLevelRefining::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( nProcId == CM_REFIN_INFO )
	{
		SendRefinInfo();
	}
	else if ( nProcId == CM_REFIN_UPGRADE )
	{
		return OnRefining( inPacket );
	}
	return 0;
}

int32_t CLevelRefining::OnRefining( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nTime = m_pPlayer->getRecord( 2081 );
	int32_t nLevel = m_pPlayer->getLevel();
	LevelRefinCfg* pCfg = CFG_DATA.GetRefining( nLevel );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCfg->nLimit <= nTime )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCfg->vNeedGold[nTime] <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->vNeedGold[nTime], GCR_LEVEL_REFIN, 0 ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nTargetLevel = pCfg->nLevelUp[nTime];
	if ( nTargetLevel <= m_pPlayer->GetMaxLevel() )
	{
		m_pPlayer->SetLevel( nTargetLevel );
	}
	else
	{
		m_pPlayer->SetLevel( m_pPlayer->GetMaxLevel() );
	}

	// Broadcast announcement
	if ( pCfg->nGongGaoId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet != NULL )
		{
			packet->writeInt32( pCfg->nGongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	m_pPlayer->updateRecord( 2081, nTime + 1 );
	SendRefinInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	SendIcon();
	return 0;
}

void CLevelRefining::SendRefinInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_REFIN_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getRecord( 2081 ) );
	packet->writeInt32( GetLeftTime() );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CLevelRefining::GetLeftTime()
{
	int32_t nNow = m_pPlayer->getNow();
	// 3 days from server start (259200 = 3 * 24 * 3600)
	return CFG_DATA.getServerStartDayTime() + 259200 - nNow;
}

void CLevelRefining::GetIcon( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( CFG_DATA.getServerType() != 0 )
	{
		return;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 186 ) )
	{
		return;
	}

	int32_t nServerDay = CFG_DATA.getServerDiffDay( 0 );
	if ( nServerDay >= 0 && nServerDay + 1 <= 3 )
	{
		ShowIcon stu;
		GetIconStu( &stu );
		IconList.push_back( stu );
	}
}

void CLevelRefining::SendIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( CFG_DATA.getServerType() != 0 )
	{
		return;
	}

	ShowIcon stu;
	GetIconStu( &stu );

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CLevelRefining::GetIconStu( ShowIcon* stu )
{
	if ( NULL == stu )
	{
		return;
	}

	stu->nId		= LEVEL_REFINING_ICON;
	stu->nState		= AS_RUNNING;
	stu->nLeftTime	= -1;
	stu->IconLeft	= 0;
	stu->IconRight	= 0;
	stu->Effects	= 1;
}
