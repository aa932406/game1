#include "stdafx.h"
#include "ChrDepot.h"
#include "CfgData.h"
#include "GameService.h"

#define OPEN_SLOT_NEED_GOLD 1

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
	if ( m_pPlayer != NULL )
	{
		m_DepotInfo.m_nLastOpenTime = m_pPlayer->getNow();
	}
	m_DepotInfo.m_nOpenedSlots	= dbData.gambleDepot.DeoptInfo.m_nOpenedSlots;
	m_DepotInfo.m_nCanOpenSlots	= dbData.gambleDepot.DeoptInfo.m_nCanOpenSlots;
	m_DepotInfo.m_nLeftSeconds	= dbData.gambleDepot.DeoptInfo.m_nLeftSeconds;
	if ( 0 == m_DepotInfo.m_nLeftSeconds )
	{
		m_DepotInfo.m_nLeftSeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( m_DepotInfo.m_nCanOpenSlots + 1, CBT_DEPORT );
	}

	memcpy( m_DepotData, dbData.gambleDepot.gambleDepot, sizeof( m_DepotData ) );
	memcpy( m_aCurrency, dbData.gambleDepot.Currency, sizeof( m_aCurrency ) );
}
	
void CChrDepot::OnSaveToDB( PlayerDBData& dbData )
{
	if ( m_pPlayer != NULL )
	{
		int32_t nNow = m_pPlayer->getNow();
		m_DepotInfo.m_nLeftSeconds -= ( nNow - m_DepotInfo.m_nLastOpenTime );
		if ( m_DepotInfo.m_nLeftSeconds < 0 )
		{
			m_DepotInfo.m_nLeftSeconds = 0;
		}
		m_DepotInfo.m_nLastOpenTime = nNow;
	}

	dbData.gambleDepot.DeoptInfo.m_nOpenedSlots		= m_DepotInfo.m_nOpenedSlots;
	dbData.gambleDepot.DeoptInfo.m_nCanOpenSlots	= m_DepotInfo.m_nCanOpenSlots;
	dbData.gambleDepot.DeoptInfo.m_nLeftSeconds		= m_DepotInfo.m_nLeftSeconds;

	memcpy( dbData.gambleDepot.gambleDepot, m_DepotData, sizeof( m_DepotData ) );
	memcpy( dbData.gambleDepot.Currency, m_aCurrency, sizeof( m_aCurrency ) );
}

void CChrDepot::OnUpdate( int64_t curTick )
{
	//更新脏数据
	CheckDirty();
	//自动开启
	CheckOpenSlot();
	//仓库资源更新
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
	default:
		break;
	}
	return ERR_OK;
}

void CChrDepot::CleanUp()
{
	bzero( &m_DepotInfo, sizeof( m_DepotInfo ) );
	bzero( m_DepotData, sizeof( m_DepotData ) );
	bzero( &m_nullobj, sizeof( m_nullobj ) );
	bzero( &m_aCurrency, sizeof( m_aCurrency ) );
	m_lstDirty.clear();
	m_NeedSendCurrency = false;
	m_NeedSendDirty	   = false;
	m_lastCheckSlotOpen = 0;
}

int32_t	CChrDepot::OnGetDepotItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
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

	// 往背包中加
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

	//删除仓库中
	RemoveItem( DepotSlot );
	return ERR_OK;
}

int32_t CChrDepot::OnSaveItemToDepot( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t BagSlot		= inPacket->readInt32();
	int32_t DepotSlot	= inPacket->readInt32();
	
	MemChrBag BagItem = m_pPlayer->getBagSlotData( BagSlot );
	if ( BagItem.itemId == 0 || BagItem.itemCount == 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// 放了仓库
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
	//删除背包中的道具
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
	if( Slot < GetDepotSize() )
	{
		return true;
	}

	return false;
}

int32_t CChrDepot::GetDepotSize()
{
	if ( ( FREE_DEPOT_SLOT + m_DepotInfo.m_nOpenedSlots )  > MAX_DEPOT_SLOT )
	{
		return MAX_DEPOT_SLOT;
	}
	
	return FREE_DEPOT_SLOT + m_DepotInfo.m_nOpenedSlots;
}

bool CChrDepot::setSlotData( int32_t Slot, const MemChrBag &slotData )
{
	if ( !IsSlotValid( Slot ) )
	{
		return false;
	}
	if ( slotData.itemCount > 0 ) //添加物品
	{
		m_DepotData[Slot] = slotData;
	}
	else //删除物品
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

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_DEPOT_CURRENCY_INFO );
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
			packet->writeInt32( m_aCurrency[i] );	
			++nCount;
		}
	}

	uint32_t newOffset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( newOffset );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t	CChrDepot::OnSortDepot( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	// 提取仓库中现存道具
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

	// 道具排序
	std::sort(items.begin(), items.end(), sortItem );

	// 按顺序放回包裹中
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

	// 将剩余格子置空
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

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_BAG_DIRTY );
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
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);

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

	int32_t slot = inPacket->readInt32();

	if ( slot < 0 || slot >= MAX_DEPOT_SLOT )
	{
		return ERR_INVALID_DATA;
	}

	if ( IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}
	slot += 1; //客户端发过来的的是从0开始的
	if ( slot <= m_DepotInfo.m_nCanOpenSlots + FREE_DEPOT_SLOT )
	{
		int32_t nSize = slot - GetDepotSize();
		for( int32_t i = 0; i < nSize; i++ )	//加经验
		{
			const CfgBagSlotOpenTime* pCfgSlotOpen = CFG_DATA.GetBagSlotOpenTimeTable().Get( m_DepotInfo.m_nOpenedSlots + i + 1 );
			if ( NULL != pCfgSlotOpen )
			{
				m_pPlayer->addExp( pCfgSlotOpen->m_nDepotAddExp );
			}
		}
		m_DepotInfo.m_nOpenedSlots = slot - FREE_DEPOT_SLOT;

		int32_t nNow = m_pPlayer->getNow();
		m_DepotInfo.m_nLeftSeconds -= ( nNow - m_DepotInfo.m_nLastOpenTime );
		if ( m_DepotInfo.m_nLeftSeconds < 0 )
		{
			m_DepotInfo.m_nLeftSeconds = 0;
		}
		m_DepotInfo.m_nLastOpenTime = nNow;
		SendDepotInfo();
		m_pPlayer->recalcAttr();
		return ERR_OK;
	}

	int32_t nStartSlot	= m_DepotInfo.m_nCanOpenSlots + 1;
	int32_t	nEndSlot	= slot - FREE_DEPOT_SLOT;
	int32_t DiffTime    = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( nStartSlot, CBT_DEPORT ) -  m_DepotInfo.m_nLeftSeconds;
	if ( DiffTime <= 0 )
	{
		DiffTime = 0;
	}
	int32_t nBuySeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( nStartSlot, nEndSlot, CBT_DEPORT ) - DiffTime;
	if ( nBuySeconds <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBuyTimes = ( nBuySeconds % ( 60 * 10 ) == 0 ) ? ( nBuySeconds / ( 60 * 10 ) ) : ( nBuySeconds / ( 60 * 10 )+ 1 );
	int32_t nCostGold = nBuyTimes * OPEN_SLOT_NEED_GOLD;
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_DEPOT_SLOT_OPEN ) )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nSize = slot - GetDepotSize();

	//加经验
	int32_t NeedAddExp = 0;
	for( int32_t i = 0; i < nSize; i++ )	
	{
		const CfgBagSlotOpenTime* pCfgSlotOpen = CFG_DATA.GetBagSlotOpenTimeTable().Get( m_DepotInfo.m_nOpenedSlots + i + 1 );
		if ( NULL != pCfgSlotOpen )
		{
			NeedAddExp += pCfgSlotOpen->m_nDepotAddExp;
		}
	}
	if ( NeedAddExp > 0 )
	{
		m_pPlayer->addExp( NeedAddExp );
	}


	m_DepotInfo.m_nLastOpenTime = m_pPlayer->getNow();
	m_DepotInfo.m_nOpenedSlots  = nEndSlot;
	m_DepotInfo.m_nCanOpenSlots = nEndSlot;

	if ( slot + 1  < MAX_DEPOT_SLOT )
	{
		m_DepotInfo.m_nLeftSeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( nEndSlot + 1, CBT_DEPORT );
	}

	SendDepotInfo();
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

void CChrDepot::SendDepotItem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_DEPOT_ITEM);
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
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CChrDepot::CheckOpenSlot()
{
	if ( GetDepotSize() >= MAX_DEPOT_SLOT )
	{
		return;
	}

	int32_t nNow = m_pPlayer->getNow();
	if ( nNow == m_lastCheckSlotOpen )
	{
		return;
	}
	m_lastCheckSlotOpen = nNow;
	int32_t Rate = m_pPlayer->GetPlayerVip().GetOpenBagRate();
	m_DepotInfo.m_nLeftSeconds -= Rate;
	if ( nNow - m_DepotInfo.m_nLastOpenTime < m_DepotInfo.m_nLeftSeconds )
	{
		return;
	}

	m_DepotInfo.m_nLastOpenTime = nNow;
	++m_DepotInfo.m_nCanOpenSlots;

	m_DepotInfo.m_nLeftSeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( m_DepotInfo.m_nCanOpenSlots + 1, CBT_DEPORT );
	SendDepotInfo();
}

void CChrDepot::SendDepotInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_DEPOT_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( GetDepotSize() );
	packet->writeInt32( m_DepotInfo.m_nCanOpenSlots - m_DepotInfo.m_nOpenedSlots );
	packet->writeInt32( m_DepotInfo.m_nLeftSeconds );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CChrDepot::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int32_t i = 0; i < m_DepotInfo.m_nOpenedSlots; i++ )
	{
		const CfgBagSlotOpenTime* pCfgSlotOpen = CFG_DATA.GetBagSlotOpenTimeTable().Get( i + 1 );
		if ( NULL != pCfgSlotOpen )
		{
			m_pPlayer->AddAttrValue(CObjAttrs::ATTR_HP,pCfgSlotOpen->m_nDepotAddHp);
		}
	}
}