#include "stdafx.h"
#include "CharMysteryGift.h"
#include "Player.h"
#include "GameService.h"
#include "CfgData.h"
#include "YunYingHD.h"
#include "OperateLimit.h"
#include "Bag.h"
#include "Currency.h"

using namespace Answer;

// 协议号
#define CM_MYSTERY_GIFT_ON_GET_GIFT		885
#define CM_MYSTERY_GIFT_ON_REQUEST_INFO		886

// 广播协议号
#define SM_BROADCAST_MYSTERY_GIFT		0x2CD6

// OperateLimit IDs
#define MYSTERY_GIFT_STATE_LIMIT_ID		1061
#define MYSTERY_GIFT_INDEX_LIMIT_ID		1062

bool CExtCharMysteryGift::isFunctionOpen() const
{
	// 神秘礼物功能默认开放
	return true;
}

void CExtCharMysteryGift::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_MYSTERY_GIFT_ON_GET_GIFT );
	procList.push_back( CM_MYSTERY_GIFT_ON_REQUEST_INFO );
}

int32_t CExtCharMysteryGift::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( !isFunctionOpen() )
	{
		return 10002;
	}

	if ( nProcId == CM_MYSTERY_GIFT_ON_GET_GIFT )
	{
		return onGetGift( inPacket );
	}

	if ( nProcId == CM_MYSTERY_GIFT_ON_REQUEST_INFO )
	{
		return onRequestInfo( inPacket );
	}

	return 0;
}

void CExtCharMysteryGift::OnDaySwitch( int32_t nDiffDays )
{
	if ( getIndex() != 1 || getState() )
	{
		addIndex();
		setState( 0 );
		SendMysteryGiftInfo( false );
	}
}

int32_t CExtCharMysteryGift::onGetGift( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 10002;
	}

	if ( getState() )
	{
		return 10002;
	}

	int32_t nIndex = getIndex();
	int64_t nCondition = getCondition();

	const CfgMysteryGiftTable* pMysteryGiftTable = CFG_DATA.GetMysteryGiftTable();
	if ( NULL == pMysteryGiftTable )
	{
		return 10002;
	}

	const CfgMysteryGift* pCfg = pMysteryGiftTable->GetGiftInfo( nIndex );
	if ( NULL == pCfg )
	{
		return 10002;
	}

	if ( pCfg->nCondition > nCondition )
	{
		return 10002;
	}

	if ( !m_pPlayer->GetBag().AddItem( pCfg->vItem, IACR_ACTIVITY ) )
	{
		return 10002;
	}

	if ( pCfg->nType == 3 && pCfg->nCondition > 0 )
	{
		m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nCondition, GCR_MYSTERY_GIFT_BUY, nIndex );
	}

	setState( 1 );
	broadcastGetGift( pCfg->nBroadId );

	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nIndex );

	return 0;
}

int32_t CExtCharMysteryGift::onRequestInfo( Answer::NetPacket *inPacket )
{
	SendMysteryGiftInfo( true );
	return 0;
}

void CExtCharMysteryGift::SendMysteryGiftInfo( bool bCheckIndex )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( bCheckIndex )
	{
		int32_t nIndex = getIndex();
		const CfgMysteryGiftTable* pMysteryGiftTable = CFG_DATA.GetMysteryGiftTable();
		if ( pMysteryGiftTable )
		{
			pMysteryGiftTable->GetGiftInfo( nIndex );
		}
	}
}

int32_t CExtCharMysteryGift::getLeftTime()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	if ( getIndex() == 1 )
	{
		return 0;
	}

	int32_t nNowTime = m_pPlayer->getNow();
	return DayTime::dayzero( nNowTime ) + 86400 - nNowTime;
}

int64_t CExtCharMysteryGift::getCondition()
{
	int32_t nIndex = getIndex();
	const CfgMysteryGiftTable* pMysteryGiftTable = CFG_DATA.GetMysteryGiftTable();
	if ( NULL == pMysteryGiftTable )
	{
		return 0;
	}

	const CfgMysteryGift* pCfg = pMysteryGiftTable->GetGiftInfo( nIndex );
	if ( NULL == pCfg )
	{
		return 0;
	}

	switch ( pCfg->nType )
	{
	case 1:
		return m_pPlayer->GetTodayPayGold();
	case 2:
		return 0; // GetTodayUsedGold 尚未移植
	case 3:
		return m_pPlayer->GetCurrency( CURRENCY_GOLD );
	}

	return 0;
}

int8_t CExtCharMysteryGift::getState()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	return m_pPlayer->GetOperateLimit().GetLimitCount( MYSTERY_GIFT_STATE_LIMIT_ID );
}

void CExtCharMysteryGift::setState( int8_t nState )
{
	if ( m_pPlayer )
	{
		m_pPlayer->GetOperateLimit().UpdateLimitCount( MYSTERY_GIFT_STATE_LIMIT_ID, nState );
	}
}

int32_t CExtCharMysteryGift::getIndex()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	int32_t nIndex = m_pPlayer->GetOperateLimit().GetLimitCount( MYSTERY_GIFT_INDEX_LIMIT_ID );
	if ( nIndex == 0 )
	{
		nIndex = 1;
		m_pPlayer->GetOperateLimit().UpdateLimitCount( MYSTERY_GIFT_INDEX_LIMIT_ID, 1 );
	}

	return nIndex;
}

void CExtCharMysteryGift::addIndex()
{
	if ( m_pPlayer )
	{
		m_pPlayer->GetOperateLimit().AddLimitCount( MYSTERY_GIFT_INDEX_LIMIT_ID, 1 );
	}
}

void CExtCharMysteryGift::broadcastGetGift( int32_t nBroadId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_BROADCAST_MYSTERY_GIFT );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nBroadId );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}
