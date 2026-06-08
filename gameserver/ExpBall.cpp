#include "stdafx.h"
#include "Player.h"
#include "ExpBall.h"
#include "GameService.h"
#include "DBService.h"
#define  MAX_EXP			10000000		//�����

void CExpBall::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_ItemId = dbData.m_ExpBallData.m_ItemId;
	m_CurExp = dbData.m_ExpBallData.m_CurExp;
	if ( m_ItemId > 0 )
	{
		m_MaxExp	= MAX_EXP;
	}
}

void CExpBall::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_ExpBallData.m_ItemId	= m_ItemId;
	dbData.m_ExpBallData.m_CurExp	= m_CurExp;
}

void CExpBall::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_PUT_IN_EXP_BALL );
	procList.push_back( CM_ASK_EXP_BALL_INFO );
}

int32_t	CExpBall::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case CM_PUT_IN_EXP_BALL:
		{
			return OnPutInExpBall( inPacket );
		}
	case CM_ASK_EXP_BALL_INFO:
		{
			SendExpBallInfo();
			break;
		}
	default:
		break;
	}
	return ERR_OK;
}

void CExpBall::OnCleanUp()
{
	m_ItemId		= 0;
	m_MaxExp		= 0;
	m_CurExp		= 0;
}

void CExpBall::AddBallExp( int32_t AddExp )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( AddExp <= 0 )
	{
		return;
	}
	if ( m_ItemId <= 0 )
	{
		return;
	}
	m_CurExp += AddExp;
	if ( m_CurExp >= m_MaxExp )
	{
		MemChrBag bagItem = {};
		bagItem.itemClass = IC_NORMAL;
		bagItem.itemId	  = ISI_EXP_BALL;
		bagItem.itemCount = 1;
		if( m_pPlayer->GetBag().GetbagFreeSize() <= 0 )
		{
			DB_SERVICE.OnSendSysMail( m_pPlayer->getCid(), ExpBallId, bagItem );
		}
		else
		{					
			m_pPlayer->GetBag().AddItem( bagItem, IACR_EXP_BALL );
		}
		OnCleanUp();
		ItemData data;
		data.m_nClass	= IC_NORMAL;
		data.m_nId		= ISI_EMPTY_EXP_BALL;
		data.m_nCount	= 1;
		if ( m_pPlayer->GetBag().RemoveItem( data ,IDCR_PUT_IN_EXP_BALL ))
		{
			m_ItemId	 = ISI_EMPTY_EXP_BALL;
			m_MaxExp	 = MAX_EXP;
			m_CurExp	 = 0;
			SendExpBallInfo();
		}
	}
}


int32_t CExpBall::OnPutInExpBall( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t Slot = inPacket->readInt32();
	MemChrBag bagItem = {};
	bagItem = m_pPlayer->getBagSlotData( Slot );
	if ( bagItem.itemId != ISI_EMPTY_EXP_BALL || bagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	bagItem.itemCount--;
	m_pPlayer->GetBag().SetSlotData( Slot, bagItem, IDCR_PUT_IN_EXP_BALL );

	m_ItemId	 = bagItem.itemId;
	m_MaxExp	 = MAX_EXP;
	m_CurExp	 = 0;
	SendExpBallInfo();
	return ERR_OK;
}

void CExpBall::SendExpBallInfo()
{
	if ( NULL == m_pPlayer )
	{
		return ;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_EXP_BALL_INFO );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_ItemId );
	packet->writeInt32( m_CurExp );
	packet->writeInt32( m_MaxExp );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}