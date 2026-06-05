#include "stdafx.h"
#include "BlackMarket.h"
#include "Player.h"
#include "GameService.h"
#include "CfgData.h"
#include "Bag.h"
#include "OperateLimit.h"
#include "DataStructs.h"
#include "Timer.h"

using namespace Answer;

void CBlackMarket::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 956 );  // onRequestMarketInfo
	procList.push_back( 957 );  // onEnterMarket
	procList.push_back( 958 );  // onBuyMarketGoods
}

int32_t CBlackMarket::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case 956:
		return onRequestMarketInfo( inPacket );
	case 957:
		return onEnterMarket( inPacket );
	case 958:
		return onBuyMarketGoods( inPacket );
	}

	return ERR_OK;
}

int32_t CBlackMarket::onRequestMarketInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	sendMarketInfo();
	return ERR_OK;
}

int32_t CBlackMarket::onEnterMarket( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	// Check enter limit (2041)
	if ( m_pPlayer->GetOperateLimit().GetLimitCount( 2041 ) > 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nSlot = inPacket->readInt32();
	if ( nSlot >= 0 )
	{
		// Try to consume a ticket item
		MemChrBag bagSlot = m_pPlayer->GetBag().GetSlotData( nSlot );
		if ( bagSlot.itemClass != 1 || bagSlot.itemCount <= 0 )
		{
			return ERR_INVALID_DATA;
		}

		const CfgItem* pCfgItem = CFG_DATA.getItem( bagSlot.itemId );
		if ( NULL == pCfgItem )
		{
			return ERR_INVALID_DATA;
		}

		if ( pCfgItem->type != 167 )
		{
			return ERR_INVALID_DATA;
		}

		bagSlot.itemCount--;
		m_pPlayer->GetBag().SetSlotData( nSlot, bagSlot, IACR_BLACK_MARKET_ENTER_TICKET, 0 );
	}
	else
	{
		// Pay 100 gold
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, 100, GCR_BLACK_MARCKET_ENTER_TICKET, 0 ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	m_pPlayer->GetOperateLimit().UpdateLimitCount( 2041, 1 );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), 1 );
	return ERR_OK;
}

int32_t CBlackMarket::onBuyMarketGoods( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nIndex = inPacket->readInt8();

	// Must have entered market (OperateLimit 2041)
	if ( m_pPlayer->GetOperateLimit().GetLimitCount( 2041 ) <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nDay = TIMER.GetDaysFromStart();
	int32_t nJob = m_pPlayer->getJob();
	const CfgBlacketMarketTable* pTable = CFG_DATA.GetBlacketMarketTable();
	if ( NULL == pTable )
	{
		return ERR_INVALID_DATA;
	}

	const CfgBlackMarketGoods* pCfgGoods = pTable->GetGoods( nDay + 1, nIndex + 1, nJob );
	if ( NULL == pCfgGoods )
	{
		return ERR_INVALID_DATA;
	}

	// Check buy record (2042)
	int32_t nOldRecord = m_pPlayer->GetOperateLimit().GetLimitCount( 2042 );
	int32_t nNewRecord = nOldRecord | (1 << nIndex);
	if ( nOldRecord == nNewRecord )
	{
		return ERR_INVALID_DATA;
	}

	// Check gold
	if ( pCfgGoods->nPrice <= 0 || m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfgGoods->nPrice )
	{
		return ERR_INVALID_DATA;
	}

	// Add item and deduct gold
	if ( !m_pPlayer->GetBag().AddItem( pCfgGoods->item, IACR_BLACK_MARKET_BUY_GOODS ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfgGoods->nPrice, GCR_BLACK_MARCKET_BUY_GOODS, 0 );
	m_pPlayer->updateRecord( 2042, nNewRecord );

	if ( pCfgGoods->nBroadcast > 0 )
	{
		broadcastBuyItem( pCfgGoods->nBroadcast, pCfgGoods->item );
	}

	SendMarketIcon();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nIndex );
	return ERR_OK;
}

void CBlackMarket::sendMarketInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int32_t nDay = TIMER.GetDaysFromStart();
	int32_t nJob = m_pPlayer->getJob();
	const CfgBlacketMarketTable* pTable = CFG_DATA.GetBlacketMarketTable();
	if ( NULL == pTable )
	{
		return;
	}

	if ( NULL == pTable->GetGoods( nDay + 1, 1, nJob ) )
	{
		return;
	}

	int32_t nRecord = m_pPlayer->GetOperateLimit().GetLimitCount( 2042 );

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2F18 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( (int8_t)m_pPlayer->GetOperateLimit().GetLimitCount( 2041 ) );
	packet->writeInt8( 4 );  // total slots count
	for ( int8_t i = 0; i <= 3; ++i )
	{
		packet->writeInt8( (nRecord >> i) & 1 );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CBlackMarket::SendMarketIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	ShowIcon stu;
	stu.nId = 115;
	stu.nState = checkBuyRecord() ? 1 : 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( packet != NULL )
	{
		packet->writeInt32( stu.nId );
		packet->writeInt8( stu.nState );
		packet->writeInt32( stu.nLeftTime );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
	}
}

void CBlackMarket::GetMarketIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( checkBuyRecord() )
	{
		ShowIcon stu;
		stu.nId = 115;
		stu.nState = 1;
		stu.nLeftTime = 0;
		stu.IconLeft = 0;
		stu.IconRight = 0;
		stu.Effects = 0;
		IconList.push_back( stu );
	}
}

bool CBlackMarket::checkBuyRecord()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	int32_t nDay = TIMER.GetDaysFromStart();
	int32_t nJob = m_pPlayer->getJob();
	const CfgBlacketMarketTable* pTable = CFG_DATA.GetBlacketMarketTable();
	if ( NULL == pTable )
	{
		return false;
	}

	if ( NULL == pTable->GetGoods( nDay + 1, 1, nJob ) )
	{
		return false;
	}

	// Check if all 4 items bought (bits 0-3 all set)
	int32_t nAllBought = 0;
	for ( int32_t i = 0; i <= 3; ++i )
	{
		nAllBought |= 1 << i;
	}

	return m_pPlayer->GetOperateLimit().GetLimitCount( 2042 ) != nAllBought;
}

void CBlackMarket::broadcastBuyItem( int32_t nBroadcast, const MemChrBag& item )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nBroadcast );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeInt32( item.itemId );
	packet->writeInt8( item.itemClass );
	packet->writeInt32( item.itemCount );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}
