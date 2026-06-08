#include "Trade.h"
#include "GameService.h"
#include "EquipManager.h"
#include "PetManager.h"
using namespace Answer;

#define MAX_TRADE_DISTANCE 20	//最大交易距离
#define TRADE_LEVEL		   70   //交易等级70级

CTrade::CTrade()
{
	OnCleanUp();
}

CTrade::~CTrade()
{

}

void CTrade::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_REQUEST_TRADE );	
	procList.push_back( CM_AGREE_TRADE );	
	procList.push_back( CM_ADD_TRADE_ITEM );
	procList.push_back( CM_REMOVE_TRADE_ITEM );
	procList.push_back( CM_ADD_TRADE_MONEY );
	procList.push_back( CM_SUB_TRADE_MONEY );
	procList.push_back( CM_LOCK_TRADE );		
	procList.push_back( CM_SURED_TRADE );		
	procList.push_back( CM_CANCEL_TRADE	);	
}

int32_t CTrade::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->isAlive() )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_REQUEST_TRADE: 			return OnAskTrade( inPacket );
	case CM_AGREE_TRADE:			return OnAgreeTrade( inPacket );
	case CM_ADD_TRADE_ITEM:			return OnAddItem( inPacket );
	case CM_REMOVE_TRADE_ITEM:		return OnRemoveItem( inPacket );
	case CM_ADD_TRADE_MONEY:		return OnAddMoney( inPacket );
//	case CM_SUB_TRADE_MONEY:		return OnSubMoney( inPacket );
	case CM_LOCK_TRADE:				return OnLock( inPacket );
	case CM_SURED_TRADE:
		{
			if( OnSured( inPacket ) != ERR_OK )
			{
				Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
				if ( NULL != pTarget )
				{
					pTarget->GetPlayerTrade().OnCleanUp();
				}
				OnCleanUp();
			}
			break;
		}
	case CM_CANCEL_TRADE:			return OnCancel( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

void CTrade::OnCleanUp()
{
	m_TargetId			= 0;										
	m_IsTrading			= false;					
	m_IsLock			= false;					
	m_IsSureTrad		= false;					
	m_TradMoney			= 0;
	m_TradGold			= 0;
	for ( int32_t i = 0; i < TRADE_BOX_MAX_COUNT; ++i )
	{
		m_TradeData[i].OnClanup();
	}
}

void CTrade::OnUpdate( int64_t curTick )
{
	CheckDistance();
}

int32_t	CTrade::OnAskTrade( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}

	if ( IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}

	CharId_t TargetId = inPacket->readInt64();
	Player *pTarget = GAME_SERVICE.getPlayer( TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == pTarget )
	{	
		return ERR_SYETEM_ERR;
	}
	if ( pTarget->GetSysSettingInfo(SS_TRADE) )
	{
		m_pPlayer->TiShiInfo( NO_TRADE );
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->getLevel() < TRADE_LEVEL )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pTarget->getLevel() < TRADE_LEVEL )
	{
		return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_LEVEL_LOW );
	}
	if ( pTarget->getMapId() != m_pPlayer->getMapId() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pTarget->GetPlayerTrade().IsTrading() )
	{
		return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_TRADING);
	}
	if ( IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}
	Position TarPos = pTarget->getCurrentTile();
	int32_t Distance = m_pPlayer->getCurrentTile().tileDistance(TarPos);
	if ( Distance > MAX_TRADE_DISTANCE )
	{
		return ERR_SYETEM_ERR;
	}
	SendAskTrade( pTarget );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc());
	return ERR_OK;
}

int32_t	CTrade::OnAgreeTrade( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}

	CharId_t TargetId = inPacket->readInt64();
	Player *pTarget = GAME_SERVICE.getPlayer( TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == pTarget )
	{	
		return ERR_SYETEM_ERR;
	}

	if ( pTarget->getMapId() != m_pPlayer->getMapId() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pTarget->GetPlayerTrade().IsTrading() )
	{
		return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_TRADING);
	}
	Position TarPos = pTarget->getCurrentTile();
	int32_t Distance = m_pPlayer->getCurrentTile().tileDistance(TarPos);
	if ( Distance > MAX_TRADE_DISTANCE )
	{
		return ERR_SYETEM_ERR;
	}    

	SetTargetChar( TargetId );
	SetTrading();
	pTarget->GetPlayerTrade().SetTargetChar( m_pPlayer->getCid() );
	pTarget->GetPlayerTrade().SetTrading();

	SendOperateToTarget( OPERATE_AGREE_TRADE );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_pPlayer->getCid() );
	return ERR_OK;
}

int32_t	CTrade::OnAddItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( IsLock() || IsSureTrad() )	
	{
		return ERR_SYETEM_ERR;
	}

	int32_t BagSlot		= inPacket->readInt32();
	int8_t TradeSlot	= inPacket->readInt8();
	if ( BagSlot < 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( TradeSlot < 0 || TradeSlot > TRADE_BOX_MAX_COUNT )
	{
		return ERR_SYETEM_ERR;
	}
	if ( HaveSameBagSlot( BagSlot ) )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag BagItem = m_pPlayer->GetBag().GetSlotData( BagSlot );
	if ( BagItem.itemId <= 0 || BagItem.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( BagItem.bind == IBS_BIND )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_TradeData[TradeSlot].CharBagData.itemId > 0 || m_TradeData[TradeSlot].CharBagData.itemCount > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	TradeData TradItem;
	TradItem.BagSlot		= BagSlot;
	TradItem.CharBagData	= BagItem;
	m_TradeData[TradeSlot]	= TradItem;
	SendItemChange( TradeSlot );
	SendTargetItemChange( TradeSlot );
	return ERR_OK;
}			 

int32_t	CTrade::OnRemoveItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( IsLock() || IsSureTrad() )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t TradeSlot	= inPacket->readInt8();
	if ( TradeSlot < 0 || TradeSlot > TRADE_BOX_MAX_COUNT )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_TradeData[TradeSlot].CharBagData.itemId <= 0 || m_TradeData[TradeSlot].CharBagData.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	RemoveItem( TradeSlot );
	SendItemChange( TradeSlot );
	SendTargetItemChange( TradeSlot );
	return ERR_OK;
}

int32_t	CTrade::OnAddMoney( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( IsLock() || IsSureTrad() )	
	{
		return ERR_SYETEM_ERR;
	}
	int8_t AddMoneyType		= inPacket->readInt8();
	int32_t AddMoneyCount   = inPacket->readInt32();
	if ( AddMoneyType != CURRENCY_MONEY && AddMoneyType != CURRENCY_GOLD )
	{
		return ERR_SYETEM_ERR;
	}
	if ( AddMoneyCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->GetCurrency( static_cast<CURRENCY_TYPE>(AddMoneyType) ) < AddMoneyCount )
	{
		return ERR_SYETEM_ERR;
	}
	if ( AddMoneyType == CURRENCY_MONEY )
	{
		m_TradMoney	= AddMoneyCount;
	}
	else if ( AddMoneyType == CURRENCY_GOLD )
	{
		m_TradGold = AddMoneyCount;
	}
	else
	{
		return ERR_SYETEM_ERR;
	}
	SendTradeMoneyChange();
	SendTargetTradeMoneychange();
	return ERR_OK;
}

// int32_t	CTrade::OnSubMoney( Answer::NetPacket *inPacket )
// {
// 	if ( NULL == inPacket || NULL == m_pPlayer )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 	if ( !IsTrading() )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 	if ( IsLock() || IsSureTrad() )	
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 	int8_t SubMoneyType		= inPacket->readInt8();
// 	int32_t SubMoneyCount   = inPacket->readInt32();
// 	if ( SubMoneyType != CURRENCY_MONEY || SubMoneyType != CURRENCY_GOLD )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 	if ( SubMoneyCount <= 0 )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}
// 	if ( SubMoneyType == CURRENCY_MONEY )
// 	{
// 		if ( SubMoneyCount > m_TradMoney )
// 		{
// 			return ERR_SYETEM_ERR;
// 		}
// 		m_TradMoney -= SubMoneyCount;
// 	}
// 	else
// 	{
// 		if ( SubMoneyCount > m_TradGold )
// 		{
// 			return ERR_SYETEM_ERR;
// 		}
// 		m_TradGold -= SubMoneyCount;
// 	}
// 	SendTradeMoneyChange();
// 	SendTargetTradeMoneychange();
// 	return ERR_OK;	
// }

int32_t	CTrade::OnLock( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SetLock();
	SendOperateToTarget( OPERATE_SET_LOCK );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc());
	return ERR_OK;
}

int32_t	CTrade::OnSured( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !IsLock() )		
	{
		return ERR_SYETEM_ERR;
	}
	Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == pTarget )
	{	
		return ERR_SYETEM_ERR;
	}
	if ( pTarget->GetPlayerTrade().IsSureTrad() )
	{
		int32_t Money			= 0;
		int32_t Gold			= 0;
		MemChrBagVector ItemVector;
		int32_t TargetMoney		= 0;
		int32_t TargetGold		= 0;
		MemChrBagVector TargetItemVector;
		GetTradeItem( Money, Gold, ItemVector );
		pTarget->GetPlayerTrade().GetTradeItem( TargetMoney, TargetGold, TargetItemVector );
		int32_t BagFreeCount		= m_pPlayer->GetBag().GetbagFreeSize();
		int32_t TargetBagFreeCount	= pTarget->GetBag().GetbagFreeSize();
		
		if ( static_cast<int32_t>( TargetItemVector.size() ) > BagFreeCount )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_TARGET_BAG_NOT_ENOUGH);
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_BAG_NOT_ENOUGH);
		}

		if ( static_cast<int32_t>( ItemVector.size() ) > TargetBagFreeCount )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_BAG_NOT_ENOUGH);
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_BAG_NOT_ENOUGH);
		}

		if ( TargetMoney > pTarget->GetCurrency( CURRENCY_MONEY) )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_MONEY_NOT_ENOUGH);
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_MONEY_NOT_ENOUGH);
		}

		if ( TargetGold > pTarget->GetCurrency( CURRENCY_GOLD ) )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_GOLD_NOT_ENOUGH );
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_GOLD_NOT_ENOUGH );
		}

		if ( Money > m_pPlayer->GetCurrency( CURRENCY_MONEY ) )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_TARGET_MONEY_NOT_ENOUGH );
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_MONEY_NOT_ENOUGH );
		}

		if ( Gold > m_pPlayer->GetCurrency( CURRENCY_GOLD ) )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_TARGET_GOLD_NOT_ENOUGH );
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_GOLD_NOT_ENOUGH );
		}
		
		if ( !CompareItem() )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_TARGET_NOT_THIS_ITEM );
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_NOT_THIS_ITEM );
		}

		if ( !pTarget->GetPlayerTrade().CompareItem() )
		{
			GAME_SERVICE.replyfailure( pTarget->getGateIndex(), inPacket->getProc(),ERR_NOT_THIS_ITEM );
			return GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(),ERR_TARGET_NOT_THIS_ITEM );
		}

		//检查是否有装备,和宠物
		MemChrBagVector::iterator TargetIt = TargetItemVector.begin();
		for ( ; TargetIt != TargetItemVector.end(); ++TargetIt )
		{
			if ( TargetIt->itemClass == IC_EQUIP )
			{
				MemEquip equip = EQUIP_MANAGER.GetMemEquip( TargetIt->srcId );
				if ( equip.base	= TargetIt->itemId )
				{
					equip.owner	= m_pPlayer->getCid();
					++equip.nFlag;
					EQUIP_MANAGER.UpdateMemEquip( equip );
				}
			}
			else if ( TargetIt->itemClass == IC_PET )
			{
				CPet* pPet = PET_MANAGER.GetPet( TargetIt->srcId );
				if ( NULL == pPet )
				{
					return ERR_SYETEM_ERR;
				}
				pPet->ChangeOwner( m_pPlayer->getCid() );
			}
		}

		MemChrBagVector::iterator it = ItemVector.begin();
		for ( ; it != ItemVector.end(); ++it )
		{
			if ( it->itemClass == IC_EQUIP )
			{
				MemEquip equip = EQUIP_MANAGER.GetMemEquip( it->srcId );
				if ( equip.base	= it->itemId )
				{
					equip.owner	= pTarget->getCid();
					++equip.nFlag;
					EQUIP_MANAGER.UpdateMemEquip( equip );
				}
			}
			else if ( it->itemClass == IC_PET )
			{
				CPet* pPet = PET_MANAGER.GetPet( it->srcId );
				if ( NULL == pPet )
				{
					return ERR_SYETEM_ERR;
				}
				pPet->ChangeOwner( pTarget->getCid() );
			}

		}
		//物品交换
		RemoveBagItem();		
		pTarget->GetPlayerTrade().RemoveBagItem();
		AddBagItem( TargetItemVector );
		pTarget->GetPlayerTrade().AddBagItem( ItemVector );
		
		//金币交换
		if ( Money > 0 )
		{
			m_pPlayer->DecCurrency( CURRENCY_MONEY, Money, MCR_TRADE_CONST_MONEY, pTarget->getCid() );
			pTarget->AddCurrency( CURRENCY_MONEY, Money, MCR_TRADE_GET_MONEY, m_pPlayer->getCid() );
		}
		if ( Gold > 0 )
		{
			m_pPlayer->DecCurrency( CURRENCY_GOLD, Gold, GCR_TRADE_CONST_GOLD, pTarget->getCid() );
			if ( m_pPlayer->GetPlayerVip().GetVipType() > 1 )
			{
				Gold = static_cast<int32_t>(Gold * 0.98);
			}
			else
			{
				Gold = static_cast<int32_t>(Gold * 0.8);
			}
			
			pTarget->AddCurrency( CURRENCY_GOLD, Gold, GCR_TRADE_GET_GOLD, m_pPlayer->getCid() );
		}
		if ( TargetMoney > 0 )
		{
			pTarget->DecCurrency( CURRENCY_MONEY, TargetMoney, MCR_TRADE_CONST_MONEY, m_pPlayer->getCid() );
			m_pPlayer->AddCurrency( CURRENCY_MONEY, TargetMoney, MCR_TRADE_GET_MONEY, pTarget->getCid()  );
		}
		if ( TargetGold > 0 )
		{
			pTarget->DecCurrency( CURRENCY_GOLD, TargetGold, GCR_TRADE_CONST_GOLD, m_pPlayer->getCid() );
			if ( m_pPlayer->GetPlayerVip().GetVipType() > 1 )
			{
				TargetGold = static_cast<int32_t>(TargetGold * 0.98 );
			}
			else
			{
				TargetGold = static_cast<int32_t>(TargetGold * 0.8 ); 
			}
			m_pPlayer->AddCurrency( CURRENCY_GOLD, TargetGold, GCR_TRADE_GET_GOLD, pTarget->getCid() );
		}
		SendTradeSucceed( TargetMoney, TargetGold, TargetItemVector );
		pTarget->GetPlayerTrade().SendTradeSucceed( Money,Gold, ItemVector );
		OnCleanUp();
		pTarget->GetPlayerTrade().OnCleanUp();
		return ERR_OK;
	}
	else
	{
		SetSureTrad();
		SendOperateToTarget( OPERATE_SET_SURED );
		GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc());
	}
	return ERR_OK;
}

int32_t	CTrade::OnCancel( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !IsTrading() )
	{
		return ERR_SYETEM_ERR;
	}
	Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == pTarget )
	{	
		return ERR_SYETEM_ERR;
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc());
	SendOperateToTarget( OPERATE_CANCEL );
	OnCleanUp();
	pTarget->GetPlayerTrade().OnCleanUp();
	return ERR_OK;
}

void CTrade::SendAskTrade( Player *pTarget )
{
	if ( NULL == pTarget || NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ASK_TRADE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeInt32( m_pPlayer->getLevel() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt32( m_pPlayer->getBattle() );		//战斗力,先预留出来
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pTarget->getGateIndex(), packet);
}

void CTrade::SendOperateToTarget( OPERATE_VALUES OperateType )
{
	Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == pTarget || NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_OPERATE_TO_TARGET );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( OperateType ) );
	if ( OperateType ==  OPERATE_AGREE_TRADE )
	{
		packet->writeInt64( m_pPlayer->getCid() );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pTarget->getGateIndex(), packet);
}

void CTrade::SendItemChange( int32_t TradeSlot )
{
	if ( TradeSlot < 0 || TradeSlot > TRADE_BOX_MAX_COUNT )
	{
		return;
	}
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TRADE_ITEM_CHANGE );
	if (NULL == packet)
	{
		return;
	}
	if ( m_TradeData[TradeSlot].CharBagData.itemId < 0 ||  m_TradeData[TradeSlot].CharBagData.itemCount <= 0 )
	{
		m_TradeData->BagSlot = -1;
	}
	packet->writeInt8( TradeSlot );
	packet->writeInt32( m_TradeData[TradeSlot].BagSlot );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CTrade::SendTargetItemChange( int32_t TradeSlot )
{
	if ( TradeSlot < 0 || TradeSlot > TRADE_BOX_MAX_COUNT )
	{
		return;
	}
	Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == m_pPlayer || NULL == pTarget )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TARGET_TRADE_ITEM_CHANGE );
	if (NULL == packet)
	{
		return;
	}
	if ( m_TradeData[TradeSlot].CharBagData.itemId < 0 ||  m_TradeData[TradeSlot].CharBagData.itemCount <= 0 )
	{
		m_TradeData->BagSlot = -1;
	}

 	if ( IC_EQUIP == m_TradeData[TradeSlot].CharBagData.itemClass )
	{
 		MemEquip Equip = EQUIP_MANAGER.GetMemEquip( m_TradeData[TradeSlot].CharBagData.srcId );
 		pTarget->sendEquipInfo( Equip );
 	}
	packet->writeInt8( TradeSlot );
	packet->writeInt32( m_TradeData[TradeSlot].CharBagData.itemId );
	packet->writeInt8( m_TradeData[TradeSlot].CharBagData.itemClass );
	packet->writeInt32(	m_TradeData[TradeSlot].CharBagData.itemCount );	
	packet->writeInt8( m_TradeData[TradeSlot].CharBagData.bind );	
	packet->writeInt32(	m_TradeData[TradeSlot].CharBagData.endTime );
	packet->writeInt64(	m_TradeData[TradeSlot].CharBagData.srcId );		
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pTarget->getGateIndex(), packet);
}

void CTrade::SendTradeMoneyChange()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TRADE_MONEY_CHANGE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_TradMoney );
	packet->writeInt32( m_TradGold );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CTrade::SendTargetTradeMoneychange()
{
	Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
	if ( NULL == m_pPlayer || NULL == pTarget )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_TARGET_MONEY_CHANGE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_TradMoney );
	packet->writeInt32( m_TradGold );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pTarget->getGateIndex(), packet);
}

void CTrade::SendTradeSucceed( int32_t& Moeny, int32_t& Gold, MemChrBagVector& ItemVector )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_TRADE_SUCCEED );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( Moeny );
	packet->writeInt32( Gold );
	int8_t nSize = ItemVector.size();
	packet->writeInt8( nSize );
	MemChrBagVector::iterator it = ItemVector.begin();
	for ( ; it != ItemVector.end(); ++it )
	{
		packet->writeInt32( it->itemId );
		packet->writeInt8( it->itemClass );
		packet->writeInt32(	it->itemCount );	
		packet->writeInt8( it->bind );	
		packet->writeInt32(	it->endTime );
		packet->writeInt64(	it->srcId );	
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CTrade::RemoveItem( int32_t TradeSlot )
{
	if ( TradeSlot > TRADE_BOX_MAX_COUNT || TradeSlot < 0 )
	{
		return;
	}
	TradeData TradeItem;
	m_TradeData[TradeSlot]	= TradeItem;
}

void CTrade::SetTrading()
{
	m_IsTrading = true;
}

void CTrade::SetSureTrad()
{
	m_IsSureTrad = true;
}

void CTrade::SetLock()
{
	m_IsLock	= true;
}

bool CTrade::IsTrading()
{
	return m_IsTrading;
}

bool CTrade::IsLock()
{
	return m_IsLock;
}

bool CTrade::IsSureTrad()
{
	return m_IsSureTrad;
}

void CTrade::SetTargetChar( CharId_t TargetId )
{
	m_TargetId = TargetId;
}

int32_t	CTrade::GetDistance( Position Pos )
{
	int32_t Distance = 0;
	return Distance = m_pPlayer->getCurrentTile().tileDistance( Pos );
}	

void CTrade::GetTradeItem( int32_t& Moeny, int32_t& Gold, MemChrBagVector& ItemVector )
{
	Moeny = m_TradMoney;
	Gold  = m_TradGold;
	for ( int32_t i = 0; i < TRADE_BOX_MAX_COUNT; ++i )
	{
		if ( m_TradeData[i].BagSlot < 0 )
		{
			continue;
		}
		if ( m_TradeData[i].CharBagData.itemId <= 0 || m_TradeData[i].CharBagData.itemCount <= 0 )
		{
			continue;
		}
		ItemVector.push_back( m_TradeData[i].CharBagData );
	}
}

void CTrade::CheckDistance()
{
	if ( IsTrading() )
	{
		Player *pTarget = GAME_SERVICE.getPlayer( m_TargetId, m_pPlayer->GetRunnerId() );
		if ( NULL == m_pPlayer || NULL == pTarget )
		{
			OnCleanUp();
			return ;
		}
		if ( pTarget->getMapId() != m_pPlayer->getMapId() )
		{
			OnCleanUp();
			pTarget->GetPlayerTrade().OnCleanUp();
			return;
		}
		Position Pos = pTarget->getCurrentTile();
		if ( GetDistance( Pos ) > MAX_TRADE_DISTANCE )
		{
			OnCleanUp();
			pTarget->GetPlayerTrade().OnCleanUp();
			return;
		}
	}
}
bool CTrade::CompareItem()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	for ( int32_t i = 0; i < TRADE_BOX_MAX_COUNT; i++ )
	{
		if ( m_TradeData[i].CharBagData.itemId > 0 && m_TradeData[i].CharBagData.itemCount > 0 )
		{
			MemChrBag BagItem  = m_pPlayer->GetBag().GetSlotData( m_TradeData[i].BagSlot );
			if ( BagItem.bind != m_TradeData[i].CharBagData.bind || 
				 BagItem.endTime != m_TradeData[i].CharBagData.endTime ||
				 BagItem.itemClass != m_TradeData[i].CharBagData.itemClass ||
				 BagItem.itemCount	!= m_TradeData[i].CharBagData.itemCount ||
				 BagItem.itemId	!= m_TradeData[i].CharBagData.itemId ||
				 BagItem.srcId	!= m_TradeData[i].CharBagData.srcId
				)
			{
				return false;
			}
		}

	}
	return true;
}

void CTrade::RemoveBagItem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Int32Vector  vSlot;
	ItemDataList lst;
	for ( int32_t i = 0; i < TRADE_BOX_MAX_COUNT; ++i )
	{
		if ( m_TradeData[i].BagSlot >= 0 && m_TradeData[i].CharBagData.itemId > 0 && m_TradeData[i].CharBagData.itemCount > 0 )
		{
			ItemData item = {};
			item.m_nClass = m_TradeData[i].CharBagData.itemClass;
			item.m_nCount = m_TradeData[i].CharBagData.itemCount;
			item.m_nId	  = m_TradeData[i].CharBagData.itemId;
			MemChrBag slotData = {};
			if ( item.m_nClass == IC_EQUIP )
			{
				m_pPlayer->GetBag().SetSlotData( m_TradeData[i].BagSlot, slotData, IDCR_TRADE );
			}
			else
			{
				lst.push_back( item );
				vSlot.push_back(m_TradeData[i].BagSlot);
			}
		}
	}
	m_pPlayer->GetBag().RemoveItem( vSlot, lst, IDCR_TRADE );
}

void CTrade::AddBagItem( MemChrBagVector& ItemVector )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_pPlayer->GetBag().AddItem( ItemVector, IACR_TRADE );
}

bool CTrade::HaveSameBagSlot(int32_t BagSlot )
{
	for ( int32_t i = 0; i < TRADE_BOX_MAX_COUNT; ++i )
	{
		if ( m_TradeData[i].BagSlot < 0  )
		{
			continue;
		}
		if ( m_TradeData[i].BagSlot == BagSlot )
		{
			return true;
		}
	}
	return false;
}