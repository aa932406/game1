#include "stdafx.h"
#include "ChrDepot.h"
#include "CfgData.h"
#include "GameService.h"
#include "Vip.h"
#include "EquipManager.h"

bool sortItem(const MemChrBag &left, const MemChrBag &right)
{
	if (left.itemClass < right.itemClass)
	{
		return true;
	}
	else if (left.itemClass == right.itemClass)
	{
		return left.itemId < right.itemId;
	}
	else
	{
		return false;
	}
}

CChrDepot::CChrDepot()
{
	CleanUp();
}
CChrDepot::~CChrDepot()
{

}

void CChrDepot::OnCleanUp()
{
	CleanUp();
}

void CChrDepot::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_OpenCount = dbData.gambleDepot.OpneCount;
	m_Password = dbData.gambleDepot.Password;
	m_SendPassword = dbData.gambleDepot.SecondPassword;
	memcpy( m_DepotData, dbData.gambleDepot.gambleDepot, sizeof( m_DepotData ) );
	memcpy( m_aCurrency, dbData.gambleDepot.Currency, sizeof( m_aCurrency ) );
}
	
void CChrDepot::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.gambleDepot.OpneCount = m_OpenCount;
	dbData.gambleDepot.Password = m_Password;
	dbData.gambleDepot.SecondPassword = m_SendPassword;
	memcpy( dbData.gambleDepot.gambleDepot, m_DepotData, sizeof( m_DepotData ) );
	memcpy( dbData.gambleDepot.Currency, m_aCurrency, sizeof( m_aCurrency ) );
}

void CChrDepot::OnUpdate( int64_t curTick )
{
	CheckDirty();
	CheckCurrency();
}

void CChrDepot::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_GET_DEPOT_ITEM );	
	procList.push_back( CM_SAVE_DEPOT_ITEM );		
	procList.push_back( CM_GET_DEPOT_CURRENCY );
	procList.push_back( CM_SAVE_DEPOT_CURRENCY );
	procList.push_back( CM_SORT_DEPOT );		
	procList.push_back( CM_OPEN_DEPOT_SLOT );
	procList.push_back( CM_SET_DEPOT_PASSWORD );
	procList.push_back( CM_ENTER_DEPOT_PASSWORD );
	procList.push_back( CM_MODIFY_DEPOT_PASSWORD );
	procList.push_back( CM_CANCEL_DEPOT_PASSWORD );
	procList.push_back( CM_SET_DEPOT_SECOND_PASSWORD );
	procList.push_back( CM_ENTER_DEPOT_SECOND_PASSWORD );
	procList.push_back( CM_MODIFY_DEPOT_SECOND_PASSWORD );
	procList.push_back( CM_CANCEL_DEPOT_SECOND_PASSWORD );
}

int32_t CChrDepot::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	switch( nProcId )
	{
	case CM_GET_DEPOT_ITEM:			return OnGetDepotItem( inPacket );
	case CM_SAVE_DEPOT_ITEM:		return OnSaveItemToDepot( inPacket );
	case CM_GET_DEPOT_CURRENCY: 	return OnGetDepotCurrency( inPacket );
	case CM_SAVE_DEPOT_CURRENCY:	return OnSaveDepotCurrency( inPacket );
	case CM_SORT_DEPOT:				return OnSortDepot( inPacket );
	case CM_OPEN_DEPOT_SLOT:		return OnOpenDepotSlot( inPacket );
	case CM_SET_DEPOT_PASSWORD:		return OnSetPassword( inPacket );
	case CM_ENTER_DEPOT_PASSWORD:	return OnEnterPassword( inPacket );
	case CM_MODIFY_DEPOT_PASSWORD:	return OnModifyPassword( inPacket );
	case CM_CANCEL_DEPOT_PASSWORD:	return OnCancelPassword( inPacket );
	case CM_SET_DEPOT_SECOND_PASSWORD:	return OnSetSecondPassword( inPacket );
	case CM_ENTER_DEPOT_SECOND_PASSWORD:	return OnEnterSecondPassword( inPacket );
	case CM_MODIFY_DEPOT_SECOND_PASSWORD:	return OnModifySecondPassword( inPacket );
	case CM_CANCEL_DEPOT_SECOND_PASSWORD:	return OnCancelSecondPassword( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

void CChrDepot::CleanUp()
{
	bzero( m_DepotData, sizeof( m_DepotData ) );
	bzero( &m_nullobj, sizeof( m_nullobj ) );
	bzero( &m_aCurrency, sizeof( m_aCurrency ) );
	m_lstDirty.clear();
	m_NeedSendCurrency = false;
	m_NeedSendDirty	   = false;
	m_OpenCount = 0;
	m_Password.clear();
	m_SendPassword.clear();
}

int32_t	CChrDepot::OnGetDepotItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t DepotSlot = inPacket->readInt32();
	int32_t BagSlot	  = inPacket->readInt32();
	if ( !IsSlotValid( DepotSlot ) )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag SlotData = GetSlotData( DepotSlot );
	if ( SlotData.itemId <= 0 || SlotData.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( BagSlot < 0 )
	{
		if ( !m_pPlayer->GetBag().AddItem( SlotData, IACR_DEPOT_GET ) )
		{
			return GAME_SERVICE.replyfailure( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_BAG_IS_FULL, 0 );
		}
	}
	else
	{
		if ( !m_pPlayer->GetBag().IsSlotValid( BagSlot ) )
		{
			return ERR_SYETEM_ERR;
		}
		MemChrBag BagItem = m_pPlayer->getBagSlotData( BagSlot );
		if ( BagItem.itemId != 0 && BagItem.itemCount != 0 )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->GetBag().SetSlotData( BagSlot, SlotData, IACR_DEPOT_GET );
	}

	RemoveItem( DepotSlot );
	return ERR_OK;
}
	int32_t DepotSlot = inPacket->readInt32();
	int32_t BagSlot	  = inPacket->readInt32();
	if ( !IsSlotValid( DepotSlot ) )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag SlotData = GetSlotData( DepotSlot );
	if ( SlotData.itemId <= 0 || SlotData.itemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	// �������м�
	if ( BagSlot >= 0 )
	{
		if ( !m_pPlayer->GetBag().IsSlotValid( BagSlot ) )
		{
			return ERR_SYETEM_ERR;
		}
		MemChrBag BagItem = m_pPlayer->getBagSlotData( BagSlot );
		if ( BagItem.itemId == 0 || BagItem.itemCount == 0 )
		{
			m_pPlayer->GetBag().SetSlotData( BagSlot, SlotData, IACR_DEPOT_GET );
		}
		else
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		if ( !m_pPlayer->GetBag().AddItem( SlotData, IACR_DEPOT_GET ) )
		{
			return  GAME_SERVICE.replyfailure(m_pPlayer->getGateIndex(),inPacket->getProc(),ERR_BAG_IS_FULL);
		}
	}

	//ɾ���ֿ���
	RemoveItem( DepotSlot );
	return ERR_OK;
}

int32_t CChrDepot::OnSaveItemToDepot( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t BagSlot		= inPacket->readInt32();
	int32_t DepotSlot	= inPacket->readInt32();
	int32_t Page = m_pPlayer->GetPlayerVip().GetStorePage();
	if ( GetPageBySlot( DepotSlot ) > Page )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag BagItem = m_pPlayer->getBagSlotData( BagSlot );
	if ( BagItem.itemId == 0 || BagItem.itemCount == 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( DepotSlot < 0 )
	{
		if ( !AddItem( BagItem ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		MemChrBag DepotItem = GetSlotData( DepotSlot );
		if ( DepotItem.itemId != 0 && DepotItem.itemCount != 0 )
		{
			return ERR_SYETEM_ERR;
		}
		setSlotData( DepotSlot, BagItem );
	}
	m_pPlayer->GetBag().SetSlotData( BagSlot, m_nullobj, IACR_DEPOT_SAVE );
	return ERR_OK;
}
	int32_t BagSlot		= inPacket->readInt32();
	int32_t DepotSlot	= inPacket->readInt32();
	
	MemChrBag BagItem = m_pPlayer->getBagSlotData( BagSlot );
	if ( BagItem.itemId == 0 || BagItem.itemCount == 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// ���˲ֿ�
	if ( DepotSlot >= 0 )
	{
		MemChrBag DepotItem = GetSlotData( DepotSlot );
		if ( DepotItem.itemId != 0 && DepotItem.itemCount != 0 )
		{
			return ERR_SYETEM_ERR;
		}
		else
		{
			setSlotData( DepotSlot, BagItem );
		}
	}
	else
	{
		if ( !AddItem( BagItem ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	//ɾ�������еĵ���
	m_pPlayer->GetBag().SetSlotData( BagSlot, m_nullobj, IACR_DEPOT_SAVE );
	return ERR_OK;
}

bool CChrDepot::AddItem( const MemChrBag& item )
{
	int32_t DepotSize = GetDepotSize();
	for ( int32_t i = 0; i < DepotSize; ++i )
	{
		MemChrBag DepotItem = GetSlotData( i );
		if ( DepotItem.itemId == 0 || DepotItem.itemCount == 0 )
		{
			setSlotData( i, item );
			return true;
		}
	}
	return false;
}

bool CChrDepot::RemoveItem( int32_t Slot )
{
	if ( !IsSlotValid( Slot ) )
	{
		return false;
	}
	setSlotData( Slot, m_nullobj );
	return true;
}

const MemChrBag& CChrDepot::GetSlotData( int32_t Slot )
{
	if ( !IsSlotValid( Slot ) )
	{
		return m_nullobj;
	}
	return m_DepotData[Slot];
}

bool CChrDepot::IsSlotValid( int32_t Slot )
{
	return Slot >= 0 && GetDepotSize() > Slot;
}

int32_t CChrDepot::GetDepotSize()
{
	int32_t size = FREE_DEPOT_SLOT + m_OpenCount;
	if ( size > MAX_DEPOT_SLOT )
	{
		return MAX_DEPOT_SLOT;
	}
	return size;
}

bool CChrDepot::setSlotData( int32_t Slot, const MemChrBag &slotData )
{
	if ( !IsSlotValid( Slot ) )
	{
		return false;
	}
	if ( slotData.itemCount > 0 ) //������Ʒ
	{
		m_DepotData[Slot] = slotData;
	}
	else //ɾ����Ʒ
	{
		m_DepotData[Slot] = m_nullobj;
	}
	AddDirty( Slot );
	return true;
}

int32_t CChrDepot::GetCurrency( CURRENCY_TYPE const nType )
{
	if ( nType < 0 || nType >= CURRENCY_TYPE_COUNT )
	{
		return 0;
	}
	return m_aCurrency[nType];
}

int32_t	CChrDepot::OnGetDepotCurrency( Answer::NetPacket *inPacket  )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t  nType	 = inPacket->readInt8(); 
	int32_t Value	 = inPacket->readInt32();
	if ( nType < 0 || nType >= CURRENCY_TYPE_COUNT )
	{
		return ERR_SYETEM_ERR;
	}
	
	if ( Value <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( GetCurrency( static_cast<CURRENCY_TYPE>(nType) ) < Value )
	{
		return ERR_SYETEM_ERR;
	}
	
	m_aCurrency[nType] -= Value;
	m_pPlayer->AddCurrency( static_cast<CURRENCY_TYPE>(nType), Value, GCR_DEPOT_GET );
	m_NeedSendCurrency = true;
	return ERR_OK;
}
	
int32_t CChrDepot::OnSaveDepotCurrency( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t  nType	 = inPacket->readInt8(); 
	int32_t Value	 = inPacket->readInt32();
	if ( nType < 0 || nType >= CURRENCY_TYPE_COUNT )
	{
		return ERR_SYETEM_ERR;
	}

	if ( Value <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( m_pPlayer->GetCurrency( static_cast<CURRENCY_TYPE>(nType) ) < Value )
	{
		return ERR_SYETEM_ERR;
	}

	m_aCurrency[nType] += Value;
	m_pPlayer->DecCurrency( static_cast<CURRENCY_TYPE>(nType), Value, GCR_DEPOT_GET );
	m_NeedSendCurrency = true;
	return ERR_OK;
}

void CChrDepot::CheckCurrency()
{
	if ( m_NeedSendCurrency )
	{
		SendDepotCurrency();
		m_NeedSendCurrency = false;
	}
}

void CChrDepot::SendDepotCurrency()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_DEPOT_CURRENCY_INFO );
	if ( NULL == packet )
	{
		return;
	}

	uint32_t oldOffset = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( nCount );
	for ( int8_t i = 0; i < CURRENCY_TYPE_COUNT; ++i )
	{
		if ( m_aCurrency[i] > 0 )
		{
			packet->writeInt8( i );
			packet->writeInt64( m_aCurrency[i] );	
			++nCount;
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( newOffset );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t	CChrDepot::OnSortDepot( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}

	MemChrBagVector items;
	int32_t nDepotSize = GetDepotSize();
	for ( int32_t i = 0; i < nDepotSize; ++i )
	{
		const MemChrBag& slotdata = GetSlotData( i );
		if ( slotdata.itemCount > 0 )
		{
			bool bFind = false;
			for (MemChrBagVector::iterator it = items.begin();it != items.end();++it)
			{
				if ( compairSlot( *it, slotdata ) )
				{
					it->itemCount += slotdata.itemCount;
					bFind = true;
					break;
				}
			}
			if ( !bFind )
			{
				items.push_back(slotdata);
			}
		}
	}

	std::sort(items.begin(), items.end(), sortItem );

	int32_t slot = 0;
	MemChrBagVector::iterator iter = items.begin();
	for ( ; iter != items.end() && slot < nDepotSize; ++iter )
	{
		MemChrBag& bagSlot = *iter;
		int32_t overlay = CFG_DATA.getOverlay( bagSlot.itemId, bagSlot.itemClass );
		if ( overlay <= 0 )
		{
			continue;
		}

		while( bagSlot.itemCount > overlay && slot < nDepotSize )
		{
			MemChrBag tSlot = bagSlot;
			tSlot.itemCount = overlay;
			bagSlot.itemCount -= overlay;
			setSlotData( slot, tSlot );
			++slot;
		}

		if ( bagSlot.itemCount > 0 && slot < nDepotSize )
		{
			setSlotData( slot, bagSlot );
			++slot;
		}
	}

	for ( ; slot < nDepotSize; ++slot )
	{
		setSlotData( slot, m_nullobj );
	}

	return ERR_OK;
}

	// ��ȡ�ֿ����ִ����
	MemChrBagVector items;
	int32_t nDepotSize = GetDepotSize();
	for ( int32_t i = 0; i < nDepotSize; ++i )
	{
		const MemChrBag& slotdata = GetSlotData( i );
		if ( slotdata.itemCount > 0 )
		{
			bool bFind = false;
			for (MemChrBagVector::iterator it = items.begin();it != items.end();++it)
			{
				if ( compairSlot( *it, slotdata ) )
				{
					it->itemCount += slotdata.itemCount;
					bFind = true;
					break;
				}
			}
			if ( !bFind )
			{
				items.push_back(slotdata);
			}
		}
	}

	// ��������
	std::sort(items.begin(), items.end(), sortItem );

	// ��˳��Żذ�����
	int32_t slot = 0;
	MemChrBagVector::iterator iter = items.begin();
	for ( ; iter != items.end() && slot < nDepotSize; ++iter )
	{
		MemChrBag& bagSlot = *iter;
		int32_t overlay = CFG_DATA.getOverlay( bagSlot.itemId, bagSlot.itemClass );
		if ( overlay <= 0 )
		{
			continue;
		}

		while( bagSlot.itemCount > overlay && slot < nDepotSize )
		{
			MemChrBag tSlot = bagSlot;
			tSlot.itemCount = overlay;
			bagSlot.itemCount -= overlay;
			setSlotData( slot, tSlot );
			++slot;
		}

		if ( bagSlot.itemCount > 0 && slot < nDepotSize )
		{
			setSlotData( slot, bagSlot );
			++slot;
		}
	}

	// ��ʣ������ÿ�
	for ( ; slot < nDepotSize; ++slot )
	{
		setSlotData( slot, m_nullobj );
	}

	return ERR_OK;
}

bool CChrDepot::compairSlot( const MemChrBag& left, const MemChrBag& right )
{
	if ( left.itemId != right.itemId )
	{
		return false;
	}
	if ( left.srcId != right.srcId )
	{
		return false;
	}
	if ( left.itemClass != right.itemClass )
	{
		return false;
	}
	if ( left.bind != right.bind )
	{
		return false;
	}
	if ( left.endTime != right.endTime )
	{
		return false;
	}

	return true;	
}

void CChrDepot::AddDirty( int32_t nSlot )
{
	Int32List::iterator iter = std::find( m_lstDirty.begin(), m_lstDirty.end(), nSlot );
	if ( iter != m_lstDirty.end() )
	{
		return;
	}
	m_lstDirty.push_back( nSlot );
	m_NeedSendDirty = true;
}
	
void CChrDepot::CheckDirty()
{
	if ( m_NeedSendDirty )
	{
		if ( SendDirty() )
		{
			ClearDirty();
			m_NeedSendDirty = false;
		}
	}
}

bool CChrDepot::SendDirty()
{
	if ( NULL == m_pPlayer || m_lstDirty.empty() )
	{
		return false;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_BAG_DIRTY );
	if (NULL == packet)
	{
		return false;
	}

	packet->writeInt8( CBT_DEPORT );

	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	Int32List::iterator iter = m_lstDirty.begin();
	Int32List::iterator eiter = m_lstDirty.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nSlot = *iter;
		const MemChrBag& tSlot = GetSlotData( nSlot );
		packet->writeInt32( nSlot );
		packet->writeInt32( tSlot.itemId );
		packet->writeInt8( tSlot.itemClass );
		packet->writeInt32( tSlot.itemCount );
		packet->writeInt8( tSlot.bind );
		packet->writeInt32( tSlot.endTime );
		packet->writeInt64( tSlot.srcId );
		++nCount;
	}

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt32( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );

	return true;
}
	
void CChrDepot::ClearDirty()
{
	m_lstDirty.clear();
}

int32_t	CChrDepot::OnOpenDepotSlot( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t slot = inPacket->readInt32();

	if ( slot < 0 || slot >= MAX_DEPOT_SLOT )
	{
		return ERR_INVALID_DATA;
	}

	if ( IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t CostValues = 0;
	int32_t OpenCount = slot - GetDepotSize() + 1;
	for ( int32_t i = GetDepotSize(); i <= slot; ++i )
	{
		CostValues += OpenSlotCostGold( i );
	}
	if ( CostValues <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, CostValues, GCR_DEPOT_SLOT_OPEN ) )
	{
		return ERR_INVALID_DATA;
	}
	m_OpenCount += OpenCount;
	SendDepotInfo();
	return ERR_OK;
}


void CChrDepot::SendDepotItem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_NOTIFY_DEPOT_ITEM );
	if (NULL == packet)
	{
		return;
	}

	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	int32_t nDepotSize = GetDepotSize();
	for ( int32_t slot = 0; slot < nDepotSize; ++slot )
	{
		const MemChrBag& tSlot = m_DepotData[slot];
		if ( tSlot.itemCount > 0 )
		{
			packet->writeInt32( slot );
			packet->writeInt32( tSlot.itemId);
			packet->writeInt8( tSlot.itemClass );
			packet->writeInt32( tSlot.itemCount );
			packet->writeInt8( tSlot.bind );
			packet->writeInt32( tSlot.endTime );
			packet->writeInt64( tSlot.srcId );
			++nCount;
		}
	}

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt32( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CChrDepot::AddCharAttr()
{
}

bool CChrDepot::CanOperateDepot()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( !m_pPlayer->GetPlayerVip().GetVipFlg( 2 ) && m_pPlayer->getMapId() != 50001 )
	{
		return false;
	}
	if ( m_Password.empty() )
	{
		return true;
	}
	return m_pPlayer->getRecord( 2 ) == 1;
}

bool CChrDepot::IsEnterSecondPasswordOperate()
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( m_SendPassword.empty() )
	{
		return true;
	}
	return m_pPlayer->getRecord( 9 ) == 1;
}

int32_t CChrDepot::GetPageBySlot( int32_t Slot )
{
	return Slot / 56 + 1;
}

int32_t CChrDepot::OpenSlotCostGold( int32_t Slot )
{
	if ( IsSlotValid( Slot ) )
	{
		return 0;
	}
	return 10 * ( ( Slot - 56 ) / 5 + 1 );
}

void CChrDepot::CleanBag()
{
	int32_t nSize = GetDepotSize();
	for ( int32_t i = 0; i < nSize && IsSlotValid( i ); ++i )
	{
		if ( m_DepotData[i].itemId > 0 )
		{
			if ( m_DepotData[i].itemClass == 2 && m_DepotData[i].srcId > 0 )
			{
				EQUIP_MANAGER->DeleteMemEquip( m_pPlayer->getConnId(), m_DepotData[i].srcId );
			}
			m_DepotData[i] = m_nullobj;
			AddDirty( i );
		}
	}
}

int32_t CChrDepot::OnNewSortDepot( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CanOperateDepot() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t Page = inPacket->readInt32();
	int32_t MinSlot = 56 * Page;
	int32_t MaxSlot = 56 * ( Page + 1 ) - 1;
	if ( MinSlot < 0 || MaxSlot > 559 )
	{
		return ERR_INVALID_DATA;
	}
	if ( MinSlot >= MaxSlot )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBagVector items;
	for ( int32_t i = MinSlot; i <= MaxSlot; ++i )
	{
		const MemChrBag& slotdata = GetSlotData( i );
		if ( slotdata.itemCount > 0 )
		{
			bool bFind = false;
			for ( MemChrBagVector::iterator it = items.begin(); it != items.end(); ++it )
			{
				if ( compairSlot( *it, slotdata ) )
				{
					it->itemCount += slotdata.itemCount;
					bFind = true;
					break;
				}
			}
			if ( !bFind )
			{
				items.push_back( slotdata );
			}
		}
	}

	if ( (int32_t)items.size() > 56 )
	{
		return ERR_INVALID_DATA;
	}

	std::sort( items.begin(), items.end(), sortItem );
	int32_t slot = MinSlot;
	for ( MemChrBagVector::iterator iter = items.begin(); iter != items.end() && slot <= MaxSlot; ++iter )
	{
		MemChrBag& bagSlot = *iter;
		int32_t overlay = CFG_DATA.getOverlay( bagSlot.itemId, bagSlot.itemClass );
		if ( overlay > 0 )
		{
			while ( bagSlot.itemCount > overlay && slot <= MaxSlot )
			{
				MemChrBag tSlot = bagSlot;
				tSlot.itemCount = overlay;
				bagSlot.itemCount -= overlay;
				setSlotData( slot++, tSlot );
			}
			if ( bagSlot.itemCount > 0 && slot <= MaxSlot )
			{
				setSlotData( slot++, bagSlot );
			}
		}
	}
	while ( slot <= MaxSlot )
	{
		setSlotData( slot++, m_nullobj );
	}
	return ERR_OK;
}

int32_t CChrDepot::OnSetPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_Password.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string OnePassword = inPacket->readUTF8( true );
	std::string TwoPassword = inPacket->readUTF8( true );
	if ( OnePassword != TwoPassword )
	{
		m_pPlayer->TiShiInfo( 16 );
		return ERR_INVALID_DATA;
	}
	m_Password = OnePassword;
	m_pPlayer->TiShiInfo( 14 );
	m_pPlayer->updateRecord( 2, 1 );
	SendDepotInfo();
	return ERR_OK;
}

int32_t CChrDepot::OnEnterPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_Password.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string Password = inPacket->readUTF8( true );
	if ( Password != m_Password )
	{
		m_pPlayer->TiShiInfo( 15 );
		return ERR_INVALID_DATA;
	}
	m_pPlayer->updateRecord( 2, 1 );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CChrDepot::OnModifyPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_Password.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string OldPassword = inPacket->readUTF8( true );
	std::string OnePassword = inPacket->readUTF8( true );
	std::string TwoPassword = inPacket->readUTF8( true );
	if ( OldPassword != m_Password )
	{
		m_pPlayer->TiShiInfo( 15 );
		return ERR_INVALID_DATA;
	}
	if ( OnePassword != TwoPassword )
	{
		m_pPlayer->TiShiInfo( 16 );
		return ERR_INVALID_DATA;
	}
	m_Password = OnePassword;
	m_pPlayer->TiShiInfo( 17 );
	return ERR_OK;
}

int32_t CChrDepot::OnCancelPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_Password.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string OldPassword = inPacket->readUTF8( true );
	if ( OldPassword != m_Password )
	{
		m_pPlayer->TiShiInfo( 15 );
		return ERR_INVALID_DATA;
	}
	m_Password.clear();
	SendDepotInfo();
	return ERR_OK;
}

int32_t CChrDepot::OnSetSecondPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_SendPassword.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string OnePassword = inPacket->readUTF8( true );
	std::string TwoPassword = inPacket->readUTF8( true );
	if ( OnePassword != TwoPassword )
	{
		m_pPlayer->TiShiInfo( 16 );
		return ERR_INVALID_DATA;
	}
	m_SendPassword = OnePassword;
	m_pPlayer->TiShiInfo( 14 );
	m_pPlayer->updateRecord( 9, 1 );
	SendDepotInfo();
	return ERR_OK;
}

int32_t CChrDepot::OnEnterSecondPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_SendPassword.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string Password = inPacket->readUTF8( true );
	if ( Password != m_SendPassword )
	{
		m_pPlayer->TiShiInfo( 15 );
		return ERR_INVALID_DATA;
	}
	m_pPlayer->updateRecord( 9, 1 );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CChrDepot::OnModifySecondPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_SendPassword.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string OldPassword = inPacket->readUTF8( true );
	std::string OnePassword = inPacket->readUTF8( true );
	std::string TwoPassword = inPacket->readUTF8( true );
	if ( OldPassword != m_SendPassword )
	{
		m_pPlayer->TiShiInfo( 15 );
		return ERR_INVALID_DATA;
	}
	if ( OnePassword != TwoPassword )
	{
		m_pPlayer->TiShiInfo( 16 );
		return ERR_INVALID_DATA;
	}
	m_SendPassword = OnePassword;
	m_pPlayer->TiShiInfo( 17 );
	return ERR_OK;
}

int32_t CChrDepot::OnCancelSecondPassword( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_SendPassword.empty() )
	{
		return ERR_INVALID_DATA;
	}
	std::string OldPassword = inPacket->readUTF8( true );
	if ( OldPassword != m_SendPassword )
	{
		m_pPlayer->TiShiInfo( 15 );
		return ERR_INVALID_DATA;
	}
	m_SendPassword.clear();
	SendDepotInfo();
	return ERR_OK;
}