#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharAuction.h"
#include "Npc.h"
#include "EquipManager.h"
using namespace Answer;

CExtCharAuction::CExtCharAuction()
{
	OnCleanUp();
}

CExtCharAuction::~CExtCharAuction()
{
}

void CExtCharAuction::OnCleanUp()
{
	m_nStall = 0;
}

void CExtCharAuction::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_OPEN_STALL );					// 出摊
	procList.push_back( CM_CLOSE_STALL );					// 收摊
	procList.push_back( IM_SOCIAL_GAME_AUCTION_SELL );		// 拍卖
	procList.push_back( IM_SOCIAL_GAME_AUCTION_BUY );		// 购买
}

int32_t CExtCharAuction::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case CM_OPEN_STALL:							return onOpenStall( inPacket );
	case CM_CLOSE_STALL:						return onCloseStall( inPacket );
	case IM_SOCIAL_GAME_AUCTION_SELL:			return onAuctionSell( inPacket );
	case IM_SOCIAL_GAME_AUCTION_BUY:			return onAuctionBuy( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtCharAuction::onAuctionSell( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType	= inPacket->readInt8();
	int32_t nSlot	= inPacket->readInt32();
	int32_t nCount	= inPacket->readInt32();
	int32_t nPrice	= inPacket->readInt32();

	MemChrBag item = {};
	switch ( nType ) 
	{
	case AIC_ITEM:
		{
			item = m_pPlayer->getBagSlotData( nSlot );
			if ( item.itemId <= 0 || item.itemCount <= 0 )
			{
				return ERR_INVALID_DATA;
			}

			if ( item.bind > 0 || item.endTime > 0 )
			{
				return ERR_INVALID_DATA;
			}
			if ( item.itemCount < nCount )
			{
				return ERR_INVALID_DATA;
			}
			MemChrBag emptySlot = item;
			item.itemCount = nCount;
			emptySlot.itemCount -= nCount;
			m_pPlayer->GetBag().SetSlotData( nSlot, emptySlot, IDCR_AUCTION_SELL );
		}
		break;
	case AIC_MONEY:
		{
			if ( !m_pPlayer->GetCurrency().DecCurrency(CURRENCY_MONEY, nCount, MCR_AUCTION_SELL ) )
			{
				return ERR_INVALID_DATA;
			}
			item.itemClass	= IC_CURRENCY;
			item.itemId		= CURRENCY_MONEY_ID;
			item.itemCount	= nCount;
		}
		break;
	case AIC_GOLD:
		{
			if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCount, GCR_AUCTION_SELL ) )
			{
				return ERR_INVALID_DATA;
			}
			item.itemClass	= IC_CURRENCY;
			item.itemId		= CURRENCY_GOLD_ID;
			item.itemCount	= nCount;
		}
		break;
	default:
		return ERR_INVALID_DATA;
	}

	sendSocialSell( item, nPrice );
	return ERR_OK;
}

int32_t CExtCharAuction::onAuctionBuy( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nId		= inPacket->readInt32();
	int8_t	nPayType= inPacket->readInt8();
	int32_t nPrice	= inPacket->readInt32();

	if ( nPayType == CURRENCY_GOLD_ID && !m_pPlayer->DecCurrency( CURRENCY_GOLD, nPrice, GCR_AUCTION_BUY, nId ) )
	{
		return ERR_SYETEM_ERR;
	}
	else if ( nPayType == CURRENCY_MONEY_ID && !m_pPlayer->GetCurrency().DecCurrency( CURRENCY_MONEY,nPrice, MCR_AUCTION_BUY, nId ) )
	{
		return ERR_SYETEM_ERR;
	}

	sendSocialBuy( nId );
	return ERR_OK;
}

int32_t CExtCharAuction::onOpenStall( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( GAME_SERVICE.getLine() != 1 )
	{
		return ERR_SYETEM_ERR;
	}

	EntityId_t	nNpcId	= inPacket->readInt64();
	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap )
	{
		return ERR_SYETEM_ERR;
	}

	Npc* pNpc = pMap->getNpc( nNpcId );
	if ( NULL == pNpc )
	{
		return ERR_SYETEM_ERR;
	}

	// 判定是否是摊位
	if ( pNpc->GetFuncExtra() != NFE_STALL )
	{
		return ERR_SYETEM_ERR;
	}

	// 判定是否已经被人抢占
	if ( pNpc->getOwner() > 0 )
	{
		return ERR_SYETEM_ERR;
	}

	m_nStall = pNpc->getEntityId();
	m_pPlayer->setNeedSyncSelf();

	//transferToNear( pNpc );			// 强制传送到附近
	Position stallPos = pNpc->GetStallPos();
	if ( stallPos.x > 0 && stallPos.y > 0 )
	{
		m_pPlayer->instantMove( stallPos.x, stallPos.y, IMR_OPEN_STALL );
	}

	pNpc->SetOwner( m_pPlayer->getCid() );
	pNpc->leaveMap();
	pMap->broadcastNpcIntoMap( pNpc );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nNpcId );

	sendSocialStall( true );
	return ERR_OK;
}

int32_t CExtCharAuction::onCloseStall( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !closeStall() )
	{
		return ERR_SYETEM_ERR;
	}

	m_pPlayer->setNeedSyncSelf();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

void CExtCharAuction::sendSocialSell( const MemChrBag& item, int32_t nPrice )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_AUCTION_SELL );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getGateIndex() );

	packet->writeInt32( item.itemId );
	packet->writeInt8( item.itemClass );
	packet->writeInt32( item.itemCount );
	packet->writeInt64( item.srcId );
	packet->writeInt32( nPrice );
	if ( IC_EQUIP == item.itemClass )
	{
		MemEquip Equip = EQUIP_MANAGER.GetMemEquip( item.srcId );
		packet->writeInt32( Equip.star );
	}
	else
	{
		packet->writeInt32( 0 );
	}
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharAuction::sendSocialBuy( int32_t nId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_AUCTION_BUY );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getGateIndex() );

	packet->writeInt32( nId );

	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharAuction::sendSocialStall( bool bStall )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_STALL );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getGateIndex() );

	packet->writeInt8( bStall ? 1 : 0 );

	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

bool CExtCharAuction::IsInStall() const
{
	return m_nStall > 0;
}

void CExtCharAuction::OnLogOut()
{
	closeStall();
}

bool CExtCharAuction::closeStall()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	if ( !IsInStall() )
	{
		return false;
	}

	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap )
	{
		return false;
	}

	Npc* pNpc = pMap->getNpc( m_nStall );
	if ( NULL == pNpc )
	{
		return false;
	}

	m_nStall = 0;
	pNpc->SetOwner( 0 );
	pNpc->leaveMap();
	pMap->broadcastNpcIntoMap( pNpc );
	sendSocialStall( false );
	return true;
}
