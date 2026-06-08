#include "stdafx.h"

#include "Bag.h"
#include "CfgData.h"
#include "DBService.h"
#include "GameService.h"
#include "ItemEffect.h"
#include "EquipManager.h"
#include "ItemHelper.h"
#include "EquipRansom.h"
#include "DropItem.h"
#include "MapManager.h"
#include "PDUDefine.h"
#include <algorithm>
#include <set>

#define ADD_SLOT_NEED_GOLD 1

using namespace Answer;

int32_t m_itemCD[ITEM_CD_GROUP_COUNT] = {10000, 5000, 1, 750, 12000,3000,3000};

bool GreaterItem(const MemChrBag &left, const MemChrBag &right)
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

CExtCharBag::CExtCharBag()
{
	reset();
}

CExtCharBag::~CExtCharBag()
{

}

void CExtCharBag::OnCleanUp()
{
	reset();
}

void CExtCharBag::OnLoadFromDB( const PlayerDBData& dbData )
{
	if ( m_pPlayer != NULL )
	{
		if ( GetBagSize() >= MAX_BAG_SLOT_NUM )
		{
			m_bagInfo.m_nLastOpenTime	= 0;
		}
		else
		{
			m_bagInfo.m_nLastOpenTime = m_pPlayer->getNow();
		}
	}
	m_bagInfo.m_nOpenedSlots	= dbData.chr.data.bag_open_slot;
	m_bagInfo.m_nCanOpenSlots	= dbData.chr.data.bag_can_open;
	m_bagInfo.m_nLeftSeconds	= dbData.chr.data.bag_open_time;
	if ( 0 == m_bagInfo.m_nLeftSeconds )
	{
		m_bagInfo.m_nLeftSeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( m_bagInfo.m_nCanOpenSlots + 1, CBT_BAG );
	}

	memcpy( m_bagData, dbData.bagData.bagData, sizeof( m_bagData ) );
	m_ItemLimit	= dbData.bagData.m_ItemLimit;
}

void CExtCharBag::OnSaveToDB( PlayerDBData& dbData )
{
	if ( m_pPlayer != NULL )
	{
		int32_t nNow = m_pPlayer->getNow();
		m_bagInfo.m_nLeftSeconds -= ( nNow - m_bagInfo.m_nLastOpenTime );
		if ( m_bagInfo.m_nLeftSeconds < 0 )
		{
			m_bagInfo.m_nLeftSeconds = 0;
		}
		m_bagInfo.m_nLastOpenTime = nNow;
	}

	dbData.chr.data.bag_open_time		= m_bagInfo.m_nLeftSeconds;
	dbData.chr.data.bag_open_slot		= m_bagInfo.m_nOpenedSlots;
	dbData.chr.data.bag_can_open		= m_bagInfo.m_nCanOpenSlots;

	memcpy( dbData.bagData.bagData, m_bagData, sizeof( m_bagData ) );
	dbData.bagData.m_ItemLimit = 	m_ItemLimit;
}

void CExtCharBag::OnUpdate( int64_t curTick )
{
	// ��ⱳ������
	checkBagOpen();
	// �����Ҫ�����ĵ���
	checkCreate();
	// �����ݴ������������
	checkDirty();
}

void CExtCharBag::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_MOVE_ITEM );
	procList.push_back( CM_SPLIT_ITEM );
	procList.push_back( CM_SORT_BAG );
	procList.push_back( CM_SELL_ITEM );
	procList.push_back( CM_ADD_BAGSLOT );
	procList.push_back( CM_USE_ITEM );
	procList.push_back( CM_PATCH_USE_ITEM );
	procList.push_back( CM_SELECT_ITEM );
	procList.push_back( CM_DISCARD_ITEM );
	procList.push_back( CM_USE_MMULTI_ITEM );
	procList.push_back( CM_ADD_BAG_ITEM );
	procList.push_back( CM_ASK_RANSOM_INFO );
	procList.push_back( CM_ASK_SPOILS_INFO );
	procList.push_back( CM_ASK_RANSOM_ITEM );
}

int32_t CExtCharBag::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	switch( nProcId )
	{
	case CM_ADD_BAGSLOT:	return onAddBagSlots( inPacket );
	case CM_MOVE_ITEM:		return onMoveItem( inPacket );
	case CM_SPLIT_ITEM:		return onSplitItem( inPacket );
	case CM_SORT_BAG:		return onSort( inPacket );
	case CM_SELL_ITEM:		return onSellItem( inPacket );
	case CM_USE_ITEM:		return onUseItem( inPacket );
	case CM_PATCH_USE_ITEM:	return onPatchUseItem( inPacket );
	case CM_SELECT_ITEM:	return onSelectItem( inPacket );
	case CM_DISCARD_ITEM:	return onDiscardItem( inPacket );
	case CM_USE_MMULTI_ITEM:	return onUseMutiItem( inPacket );
	case CM_ADD_BAG_ITEM:		return onAddItem( inPacket );

	case CM_ASK_RANSOM_INFO:return OnAskRansomInfo( inPacket ); 
	case CM_ASK_SPOILS_INFO:return OnAskSpoilsInfo( inPacket );
	case CM_ASK_RANSOM_ITEM:return OnAskRansomItem( inPacket );

	default:break;
	}
	return ERR_OK;
}

void CExtCharBag::reset()
{
	bzero(&m_bagInfo,sizeof(m_bagInfo));
	bzero(m_bagData, sizeof(m_bagData));
	bzero(&m_sellItemInfo,sizeof(m_sellItemInfo));
	bzero(&m_nullobj, sizeof(m_nullobj));
	bzero(m_lastItemTick, sizeof(m_lastItemTick));
	bzero(m_bagBackUp, sizeof(m_bagBackUp));
	m_lstItemChangeLog.clear();
	m_lstDirty.clear();
	m_lstWaitCreate.clear();
	m_ItemLimit.clear();
	m_lastCheckSlotOpen	= 0;
}

void CExtCharBag::OnLogout()
{
	cleanSellItem();
}

void CExtCharBag::cleanSellItem()
{
	for ( int32_t i = 0; i < MAX_SELL_ITEM_COUNT; ++i )
	{
		MemChrBag& curSlot = m_sellItemInfo[i];
		if ( curSlot.itemClass == IC_EQUIP && curSlot.srcId > 0 )
		{
			EQUIP_MANAGER.DeleteMemEquip( curSlot.srcId );
		}
	}
	bzero(&m_sellItemInfo,sizeof(m_sellItemInfo));
}

int32_t CExtCharBag::addBagSlots(int32_t slot,int32_t &buySlots,int32_t& openSlots)
{
	if ( slot < 0 || slot >= MAX_BAG_SLOT_NUM )
	{
		return ERR_INVALID_DATA;
	}

	if ( IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}

	openSlots = slot+1 - GetBagSize();
	if ( openSlots <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	else
	{
		buySlots = (m_bagInfo.m_nCanOpenSlots*2+1+openSlots)*openSlots/2;
	}

	SendBagInfo();
	return ERR_OK;
}


int32_t CExtCharBag::patchUseItem( int32_t slot, int32_t count )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( slot );
	if (slotData.itemCount <= 0 || slotData.itemClass != IC_NORMAL)
	{
		return ERR_INVALID_DATA;
	}
	if ( count > slotData.itemCount )
	{
		count = slotData.itemCount;
	}

	CfgItem *cfgItem = CFG_DATA.getItem(slotData.itemId);
	if (cfgItem == NULL || cfgItem->level > m_pPlayer->getLevel())
	{
		return ERR_INVALID_DATA;
	}

	if (cfgItem->job != 0 && cfgItem->job != m_pPlayer->getJob())
	{
		return ERR_INVALID_DATA;
	}

	if (cfgItem->cd_group < 0 || cfgItem->cd_group >= ITEM_CD_GROUP_COUNT)
	{
		return ERR_INVALID_DATA;
	}

	if (m_pPlayer->getTick() - m_lastItemTick[cfgItem->cd_group] < m_itemCD[cfgItem->cd_group])
	{
		return GAME_SERVICE.replyfailure(m_pPlayer->getGateIndex(), CM_PATCH_USE_ITEM, ERR_ITEM_CD);
	}

	 int32_t err = ITEM_EFFECT.effect( slotData.itemId, *m_pPlayer, *m_pPlayer, count );
	 if (err == ERR_OK)
	 {
		 m_pPlayer->GetTask().updateTaskUseItem( slotData.itemId, count );
		 slotData.itemCount -= count;
		 SetSlotData( slot, slotData, IDCR_BAG_USE, count );

		 m_lastItemTick[cfgItem->cd_group] = m_pPlayer->getTick();

		 GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), CM_PATCH_USE_ITEM, cfgItem->id);
	 }

	 return err;

}

int32_t CExtCharBag::useItem( int32_t slot, int32_t type )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( slot );
	if (slotData.itemCount <= 0 || slotData.itemClass != IC_NORMAL)
	{
		return ERR_INVALID_DATA;
	}

	CfgItem *cfgItem = CFG_DATA.getItem(slotData.itemId);
	if (cfgItem == NULL || cfgItem->level > m_pPlayer->getLevel())
	{
		return ERR_INVALID_DATA;
	}

	if (cfgItem->job != 0 && cfgItem->job != m_pPlayer->getJob())
	{
		return ERR_INVALID_DATA;
	}

	if (cfgItem->cd_group < 0 || cfgItem->cd_group >= ITEM_CD_GROUP_COUNT)
	{
		return ERR_INVALID_DATA;
	}

	if (m_pPlayer->getTick() - m_lastItemTick[cfgItem->cd_group] < m_itemCD[cfgItem->cd_group])
	{
		return GAME_SERVICE.replyfailure(m_pPlayer->getGateIndex(), CM_USE_ITEM, ERR_ITEM_CD);
	}
	if ( slotData.itemId == ISI_XIAO_JV_HUA )
	{
		if ( m_pPlayer->getRecord( PR_XIAO_JV_HUA_SHI_YONG ) >= 10 )
		{
			return ERR_INVALID_DATA;
		}
	}

	int32_t err = ERR_INVALID_DATA;
	if (type ==ET_PLAYER)
	{
		 err = ITEM_EFFECT.effect(slotData.itemId, *m_pPlayer, *m_pPlayer,1 );
	}

	if ( err == ERR_OK )
	{
		if ( slotData.itemId == ISI_XIAO_JV_HUA )
		{
			m_pPlayer->updateRecord( PR_XIAO_JV_HUA_SHI_YONG, m_pPlayer->getRecord( PR_XIAO_JV_HUA_SHI_YONG ) + 1 );
		}

		m_pPlayer->GetTask().updateTaskUseItem( slotData.itemId, 1 );
		slotData.itemCount--;
		SetSlotData( slot, slotData,IDCR_BAG_USE,1 );

		m_lastItemTick[cfgItem->cd_group] = m_pPlayer->getTick();

		GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), CM_USE_ITEM, cfgItem->id);
	}

	return err;
}

int32_t CExtCharBag::onAddBagSlots( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t slot = inPacket->readInt32();

	if ( slot < 0 || slot >= MAX_BAG_SLOT_NUM )
	{
		return ERR_INVALID_DATA;
	}

	if ( IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}
	slot += 1; //�ͻ��˷������ĵ��Ǵ�0��ʼ��
	if ( slot <= m_bagInfo.m_nCanOpenSlots + FREE_BAG_SLOT_NUM )
	{
		int32_t nSize = slot - GetBagSize();
		for( int32_t i = 0; i < nSize; i++ )	//�Ӿ���
		{
			const CfgBagSlotOpenTime* pCfgSlotOpen = CFG_DATA.GetBagSlotOpenTimeTable().Get( m_bagInfo.m_nOpenedSlots + i + 1 );
			if ( NULL != pCfgSlotOpen )
			{
				m_pPlayer->addExp( pCfgSlotOpen->m_nBagAddExp );
			}
		}
		m_bagInfo.m_nOpenedSlots = slot - FREE_BAG_SLOT_NUM;

		int32_t nNow = m_pPlayer->getNow();
		m_bagInfo.m_nLeftSeconds -= ( nNow - m_bagInfo.m_nLastOpenTime );
		if ( m_bagInfo.m_nLeftSeconds < 0 )
		{
			m_bagInfo.m_nLeftSeconds = 0;
		}
		m_bagInfo.m_nLastOpenTime = nNow;
		SendBagInfo();
		m_pPlayer->recalcAttr();
		return ERR_OK;
	}

	int32_t nStartSlot	= m_bagInfo.m_nCanOpenSlots + 1;
	int32_t	nEndSlot	= slot - FREE_BAG_SLOT_NUM;
	int32_t DiffTime    = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( nStartSlot, CBT_BAG ) -  m_bagInfo.m_nLeftSeconds;
	if ( DiffTime <= 0 )
	{
		DiffTime = 0;
	}
	int32_t nBuySeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( nStartSlot, nEndSlot, CBT_BAG ) - DiffTime;
	if ( nBuySeconds <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBuyTimes = ( nBuySeconds % (60*10) == 0 ) ? ( nBuySeconds / (60*10) ) : ( nBuySeconds / ( 60 *10 )+ 1 );
	int32_t nCostGold = nBuyTimes * ADD_SLOT_NEED_GOLD;
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCostGold, GCR_BAG_SLOT_OPEN, nStartSlot ) )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nSize = slot - GetBagSize();

	//�Ӿ���
	int32_t NeedAddExp = 0;
	for( int32_t i = 0; i < nSize; i++ )	
	{
		const CfgBagSlotOpenTime* pCfgSlotOpen = CFG_DATA.GetBagSlotOpenTimeTable().Get( m_bagInfo.m_nOpenedSlots + i + 1 );
		if ( NULL != pCfgSlotOpen )
		{
			NeedAddExp += pCfgSlotOpen->m_nBagAddExp;
		}
	}
	if ( NeedAddExp > 0 )
	{
		m_pPlayer->addExp( NeedAddExp );
	}


	m_bagInfo.m_nLastOpenTime = m_pPlayer->getNow();
	m_bagInfo.m_nOpenedSlots  = nEndSlot;
	m_bagInfo.m_nCanOpenSlots = nEndSlot;

	if ( slot + 1  < MAX_BAG_SLOT_NUM )
	{
		m_bagInfo.m_nLeftSeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( nEndSlot + 1, CBT_BAG );
	}

	SendBagInfo();
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int32_t CExtCharBag::onMoveItem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t oldslot	= inPacket->readInt32();
	int32_t newslot	= inPacket->readInt32();

	if ( !IsSlotValid( oldslot ) || !IsSlotValid( newslot ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( oldslot == newslot )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag oldSlotData = GetSlotData( oldslot );
	if (oldSlotData.itemCount <= 0)
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag newSlotData = GetSlotData( newslot );
	if (newSlotData.itemCount > 0)
	{
		if ( compairSlot( oldSlotData, newSlotData ) )
		{
			int32_t overlay = CFG_DATA.getOverlay( oldSlotData.itemId, oldSlotData.itemClass );
			if (overlay <= 0)
			{
				return ERR_INVALID_DATA;
			}

			if ( newSlotData.itemCount >= overlay )
			{
				return ERR_INVALID_DATA;
			}

			int32_t addon = (std::min)(oldSlotData.itemCount, overlay-newSlotData.itemCount);
			if (addon < 0)
			{
				return ERR_INVALID_DATA;
			}

			newSlotData.itemCount += addon;
			
			setSlotData( newslot, newSlotData );

			oldSlotData.itemCount -= addon;
			setSlotData( oldslot, oldSlotData );
		}
		else
		{
	
			MemChrBag tmp = newSlotData;
			setSlotData( newslot, oldSlotData );
			setSlotData( oldslot, tmp );
		}
	}
	else
	{
		setSlotData( newslot, oldSlotData );
		setSlotData( oldslot, m_nullobj );
	}

	return ERR_OK;
}

int32_t CExtCharBag::onSplitItem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t slot	= inPacket->readInt32();
	int32_t count	= inPacket->readInt32();

	if ( !IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( slot );
	if ( count <= 0 || count > slotData.itemCount || slotData.itemCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t freeSlot = GetFirstFreeSlot();
	if ( !IsSlotValid( freeSlot ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag newSlotData = slotData;
	newSlotData.itemCount = count;
	setSlotData( freeSlot, newSlotData );

	slotData.itemCount -= count;
	setSlotData( slot, slotData );

	return ERR_OK;
}

void CExtCharBag::updateBagSlots(int32_t slots)
{
	m_bagInfo.m_nCanOpenSlots += slots;
	SendBagInfo();
}

int32_t CExtCharBag::onSort( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	// ��ȡ�������ִ����
	MemChrBagVector items;
	int32_t nBagSize = GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
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
	std::sort(items.begin(), items.end(), GreaterItem);

	// ��˳��Żذ�����
	int32_t slot = 0;
	MemChrBagVector::iterator iter = items.begin();
	for ( ; iter != items.end() && slot < nBagSize; ++iter )
	{
		MemChrBag& bagSlot = *iter;
		int32_t overlay = CFG_DATA.getOverlay( bagSlot.itemId, bagSlot.itemClass );
		if ( overlay <= 0 )
		{
			continue;
		}

		while( bagSlot.itemCount > overlay && slot < nBagSize )
		{
			MemChrBag tSlot = bagSlot;
			tSlot.itemCount = overlay;
			bagSlot.itemCount -= overlay;
			setSlotData( slot, tSlot );
			++slot;
		}
		
		if ( bagSlot.itemCount > 0 && slot < nBagSize )
		{
			setSlotData( slot, bagSlot );
			++slot;
		}
	}

	// ��ʣ������ÿ�
	for ( ; slot < nBagSize; ++slot )
	{
		setSlotData( slot, m_nullobj );
	}

	return ERR_OK;
}

int32_t CExtCharBag::onSellItem( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t slot	= inPacket->readInt32();
	const MemChrBag &slotData = GetSlotData( slot );
	if (slotData.itemCount <= 0)
	{
		return ERR_INVALID_DATA;
	}

	if (!CFG_DATA.canSell(slotData.itemId, slotData.itemClass))
	{
		return ERR_INVALID_DATA;
	}

	int32_t itemId = slotData.itemId;
	int32_t itemClass = slotData.itemClass;

	int32_t outValue = CFG_DATA.getOutValue(itemId, itemClass);
	if ( outValue < 0 )
	{
		return ERR_INVALID_DATA;
	}

	outValue *= slotData.itemCount;

	m_pPlayer->sendSellItemInfo( itemId, itemClass, slotData.itemCount, outValue );

	setSellItem( slotData );
	setSlotData( slot, m_nullobj );
	//addMoney( outValue, MCR_NPC_SELL, slotData.itemId );
	m_pPlayer->AddCurrency( CURRENCY_MONEY, outValue, MCR_NPC_SELL, slotData.itemId );

	SendBagSellItem();
	return ERR_OK;
}

int32_t	CExtCharBag::OnAskRansomInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendRansomInfo();
	return ERR_OK;
}

int32_t CExtCharBag::OnAskSpoilsInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendSpoilsInfo();
	return ERR_OK;
}

int32_t	CExtCharBag::OnAskRansomItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	EquipId_t EquipId = inPacket->readInt64();
	MemEquip equip = EQUIP_MANAGER.GetMemEquip( EquipId );
	const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( equip.base );
	if ( NULL == pCfgEquip )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetBagSize() <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	DropEquipInfo EquipInfo;
	EQUIP_RANSOM.GetRansomEquip( EquipId, EquipInfo );
	if ( EquipInfo.CanGetLastTime < m_pPlayer->getNow() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t GemWorth = 0;
	for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++)
	{
		if ( equip.GemHole[i] > 0 )
		{
			const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( equip.GemHole[i] );
			if ( NULL != pGem )
			{
				GemWorth += pGem->m_nRansomWorth;
			}
		}
	}

	int32_t EquipBaseWorth	  = pCfgEquip->m_nRansomWorth;
	int32_t QiangHuaWorth = CFG_DATA.GetQiangHuaWorth( pCfgEquip->m_nQuality, equip.star );
	int32_t EquipWorth = EquipBaseWorth + GemWorth + QiangHuaWorth;
	if ( EquipWorth <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t NeedGold = 0;
	if ( EquipWorth <= 100 )
	{
		NeedGold = 10;
	}
	else if ( EquipWorth < 1000 )
	{
		NeedGold = 50;
	}
	else if ( EquipWorth < 2000 )
	{
		NeedGold = 100;
	}
	else if ( EquipWorth < 3000 )
	{
		NeedGold = 200;
	}
	else if ( EquipWorth < 4000 )
	{
		NeedGold = 300;
	}
	else if ( EquipWorth < 5000  )
	{
		NeedGold = 400;
	}
	else
	{
		NeedGold = 500;
	}

	if ( m_pPlayer->GetCurrency( CURRENCY_GOLD) < NeedGold )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, NeedGold, GCR_RANSOM_ITEM, EquipId ) )
	{
		return ERR_SYETEM_ERR;
	}
	//���Է����ʼ�
	int32_t GetGold	= NeedGold;
	if ( GetGold > 0 && EquipInfo.KillerId > 0 )
	{
		MemChrBag CurrencyItem = {};
		CurrencyItem.itemId		= CURRENCY_GOLD_ID;	
		CurrencyItem.itemClass  = IC_CURRENCY;
		CurrencyItem.itemCount  = GetGold;
		DB_SERVICE.OnSendSysMail( EquipInfo.KillerId, RansomItemId, CurrencyItem,m_pPlayer->getName() );
	}
	MemChrBag Item = {};
	Item.itemClass		= EquipInfo.itemClass;
	Item.itemId			= EquipInfo.itemId;
	Item.itemCount		= EquipInfo.itemCount;
	Item.bind			= EquipInfo.bind;
	Item.endTime		= EquipInfo.endTime;
	Item.srcId			= EquipInfo.srcId;
	if ( !AddItem( Item, IACR_RANSOM_ITEM ) )
	{
		return ERR_SYETEM_ERR;
	}
	EQUIP_RANSOM.DeleteRansom( EquipId );
	SendRansomInfo();
	RansomGongGao( EquipInfo, NeedGold );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc());
	return ERR_OK;
}

void CExtCharBag::RansomGongGao( DropEquipInfo EquipInfo, int32_t Gold )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	if ( EquipInfo.KillerId > 0  )
	{
		packet->writeInt32( BCI_RANSOM_EQUIP );
		packet->writeUTF8(  EquipInfo.CharName );
		packet->writeInt64( EquipInfo.CharId );
		packet->writeInt32( Gold );
		packet->writeUTF8( EquipInfo.KillerName );
		packet->writeInt64( EquipInfo.KillerId );
		packet->writeInt32( EquipInfo.itemId );
		packet->writeInt64( EquipInfo.srcId );
	}
	else
	{
		packet->writeInt32( BCI_RANSOM_EQUIP_2 );
		packet->writeUTF8(  EquipInfo.CharName );
		packet->writeInt64( EquipInfo.CharId );
		packet->writeInt32( Gold );
		packet->writeInt32( EquipInfo.Mid );
		packet->writeInt32( EquipInfo.itemId );
		packet->writeInt64( EquipInfo.srcId );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

int32_t CExtCharBag::buyBackChrShopItem(int32_t index,int32_t itemID,int32_t itemClass)
{
	if ( NULL == m_pPlayer || index < 0 || index > MAX_SELL_ITEM_COUNT )
	{
		return ERR_INVALID_DATA;
	}

	int32_t  freeSlot = GetFirstFreeSlot();
	if ( freeSlot < 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_sellItemInfo[index].itemId != itemID || m_sellItemInfo[index].itemClass != itemClass )
	{
		return ERR_INVALID_DATA;
	}

	int32_t costValue =  0;
	if (itemClass == IC_EQUIP)
	{
		const CfgEquip*pEquip = CFG_DATA.getEquip( itemID );
		if (pEquip == NULL)
		{
			return ERR_INVALID_DATA;
		}

		costValue = pEquip->m_nPrice*m_sellItemInfo[index].itemCount;
	}
	else if ( itemClass == IC_NORMAL )
	{
		CfgItem*pItem = CFG_DATA.getItem( itemID );
		if ( pItem == NULL )
		{
			return ERR_INVALID_DATA;
		}

		costValue = pItem->in_value*m_sellItemInfo[index].itemCount;
	}
	else if ( itemClass == IC_GEM )
	{
		const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( itemID );
		if ( NULL == pGem )
		{
			return ERR_SYETEM_ERR;
		}
		costValue = pGem->m_InValue*m_sellItemInfo[index].itemCount;	
	}
	if ( costValue <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if( m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < costValue )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag add = {};
	add.itemId = itemID;
	add.itemClass = itemClass;
	add.itemCount = m_sellItemInfo[index].itemCount;

	setSlotData( freeSlot, m_sellItemInfo[index] );
	m_pPlayer->sendBuyItemInfo( m_sellItemInfo[index].itemId, m_sellItemInfo[index].itemClass, m_sellItemInfo[index].itemCount, costValue );
	deleteSellItem(index);
	//addMoney(-costValue,MCR_BUY_BACK_ITEM,itemID);
	m_pPlayer->GetCurrency().DecMoneyAndNoBind( costValue, MCR_BUY_BACK_ITEM, itemID );
	SendBagSellItem();
	return ERR_OK;
}

int32_t CExtCharBag::buyChrShopItem( CfgChrShop* pCharShop,int32_t id,int32_t count )
{
	if ( NULL == m_pPlayer || NULL == pCharShop )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCharShop->Price <= 0 || count <= 0)
	{
		return ERR_INVALID_DATA;
	}
	if ( pCharShop->LimitCount > 0 )
	{
		if ( GetLimitCount( pCharShop->Index ) + count  > pCharShop->LimitCount )
		{
			return ERR_SYETEM_ERR;
		}
	}
	if ( pCharShop->ItemClass == IC_PET_EGG )
	{
		if ( m_pPlayer->GetCharPet().GetEggBagAddHatchBagFreeCount() <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		if ( m_pPlayer->GetBag().GetbagFreeSize() <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
	}
	MemChrBag add = {};
	add.itemId		= pCharShop->ItemId;
	add.itemClass	= pCharShop->ItemClass;
	add.itemCount	= count;
	add.bind		= pCharShop->IsBind;

	int32_t costValue = pCharShop->Price * count;
	if ( costValue > m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( costValue, MCR_CHR_SHOP_COST, pCharShop->ItemId ) )
	{
		return ERR_INVALID_DATA;
	}
	if ( pCharShop->ItemClass == IC_PET_EGG )
	{
		std::list<int32_t> EggIdList;
		EggIdList.push_back( pCharShop->ItemId );
		m_pPlayer->GetCharPet().AddEggs( EggIdList );
	}
	else if ( !AddItem( add,IACR_CHR_SHOP ) )
	{
		LOG_ERROR("��������̵���Ʒʧ��,itemClass=%d,ItemId=%d,ItemCount=%d,time=%d,cid=%lld",pCharShop->ItemClass,pCharShop->ItemId,count,m_pPlayer->getNow(),m_pPlayer->getCid() );
	}
	if ( pCharShop->LimitCount > 0 )
	{
		AddLimitCount( pCharShop->Index, count );
	}
	m_pPlayer->sendBuyItemInfo( add.itemId, add.itemClass, count, costValue,pCharShop->Index );
	return ERR_OK;
}

int32_t CExtCharBag::GetLimitCount( int32_t index )
{
	ItemLimitMap::iterator it = m_ItemLimit.find(index);
	if ( it != m_ItemLimit.end() )
	{
		return it->second;
	}
	return 0;
}

void CExtCharBag::AddLimitCount( int32_t index, int32_t count )
{
	ItemLimitMap::iterator it = m_ItemLimit.find(index);
	if ( it != m_ItemLimit.end() )
	{
		it->second += count;
	}
	else
	{
		m_ItemLimit[index] = count;
	}
}

void CExtCharBag::SendLimitCount()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_CHAR_SHOP_LINIT );
	if (NULL == packet)
	{
		return;
	}
	int32_t Count = m_ItemLimit.size();
	packet->writeInt32( Count );
	ItemLimitMap::iterator it = m_ItemLimit.begin();
	for ( ; it != m_ItemLimit.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

const MemChrBag& CExtCharBag::GetSlotData( int32_t slot ) const
{
	if ( !IsSlotValid( slot ) )
	{
		return m_nullobj;
	}

	return m_bagData[slot];
}

void CExtCharBag::SetSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason, int32_t count )
{
	setSlotData( slot, slotData, reason, count );
	saveItemChangeLog();
}

void CExtCharBag::CleanSlot( int32_t slot, int32_t reason )
{
	if ( !IsSlotValid( slot ) )
	{
		return;
	}

	if ( m_bagData[slot].itemId > 0 )
	{
		addItemChangeLog( reason, m_bagData[slot].itemId, m_bagData[slot].itemClass, m_bagData[slot].srcId, m_bagData[slot].itemCount, ITEM_CHANGE_LOG_REMOVE );
		if ( m_bagData[slot].itemClass == IC_EQUIP && m_bagData[slot].srcId > 0 )
		{
			EQUIP_MANAGER.DeleteMemEquip( m_bagData[slot].srcId );
		}

		m_bagData[slot] = m_nullobj;
		addDirty( slot, reason );
		saveItemChangeLog();
	}
}

void CExtCharBag::setSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason, int32_t count )
{
	if ( !IsSlotValid( slot ) )
	{
		return;
	}

	if ( slotData.itemCount > 0 )
	{
		if ( m_bagData[slot].itemCount >= slotData.itemCount )
		{
			addItemChangeLog( reason, slotData.itemId, slotData.itemClass, slotData.srcId, m_bagData[slot].itemCount - slotData.itemCount, ITEM_CHANGE_LOG_REMOVE );
		}
		else if ( m_bagData[slot].itemCount < slotData.itemCount )
		{
			addItemChangeLog( reason, slotData.itemId, slotData.itemClass, slotData.srcId, slotData.itemCount - m_bagData[slot].itemCount, ITEM_CHANGE_LOG_ADD );
		}

		m_bagData[slot] = slotData;
		bool bNeedCreate = false;
		if ( slotData.itemClass == IC_EQUIP && slotData.srcId == 0 )
		{
			bNeedCreate = true;
		}
		addDirty( slot, reason, bNeedCreate );
	}
	else
	{
		if ( m_bagData[slot].itemId > 0 )
		{
			addItemChangeLog( reason, m_bagData[slot].itemId, m_bagData[slot].itemClass, m_bagData[slot].srcId, m_bagData[slot].itemCount, ITEM_CHANGE_LOG_REMOVE );
		}

		m_bagData[slot] = m_nullobj;
		addDirty( slot, reason );
	}
}

int32_t CExtCharBag::GetItemCount( int32_t nId, int8_t nClass ) const
{
	int32_t nCount = 0;
	int32_t nBagSize = GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		const MemChrBag &slotData = GetSlotData( i );
		if ( IsEmptySlot( slotData ) )
		{
			continue;
		}

		if ( nClass == slotData.itemClass && slotData.itemId == nId )
		{
			nCount += slotData.itemCount;
		}
	}

	return nCount;
}

bool CExtCharBag::HasItem( const ItemData& data ) const
{
	return HasItem( data.m_nId, data.m_nClass, data.m_nCount );
}

bool CExtCharBag::HasItem( int32_t nId, int8_t nClass, int32_t nCount ) const
{
	int32_t countHas = 0;
	int32_t nBagSize = GetBagSize();
	for ( int32_t slot = 0; slot < nBagSize; ++slot )
	{
		const MemChrBag &slotData = GetSlotData( slot );
		if ( slotData.itemCount > 0 )
		{
			if ( nClass != slotData.itemClass )
			{
				continue;
			}

			if ( slotData.itemId == nId )
			{
				countHas += slotData.itemCount;
			}

			if ( countHas >= nCount )
			{
				return true;
			}
		}
	}

	return false;
}

const ChrBagInfo& CExtCharBag::GetChrBagInfo() const
{
	return m_bagInfo;
}

int32_t CExtCharBag::GetFirstFreeSlot() const
{
	int32_t nBagSize = GetBagSize();
	for ( int32_t slot = 0; slot < nBagSize; ++slot )
	{
		const MemChrBag &slotData = GetSlotData( slot );
		if ( IsEmptySlot( slotData ) )
		{
			return slot;
		}
	}

	return -1;
}

int32_t CExtCharBag::GetFreeSlotCount() const
{
	int32_t count = 0;
	int32_t nBagSize = GetBagSize();
	for ( int32_t slot = 0; slot < nBagSize; ++slot )
	{
		const MemChrBag &slotData = GetSlotData( slot );
		if ( IsEmptySlot( slotData ) )
		{
			++count;
		}
	}
	return count;
}

bool CExtCharBag::IsSlotValid( int32_t slot ) const
{
	if( slot < GetBagSize() )
	{
		return true;
	}

	return false;
}

int32_t CExtCharBag::GetBagSize() const
{
	return FREE_BAG_SLOT_NUM + m_bagInfo.m_nOpenedSlots;
}

void CExtCharBag::SendBagItem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_BAG_ITEMS);
	if (NULL == packet)
	{
		return;
	}
	
	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	int32_t nBagSize = GetBagSize();
	for ( int32_t slot = 0; slot < nBagSize; ++slot )
	{
		const MemChrBag& tSlot = m_bagData[slot];
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

void CExtCharBag::SendBagInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_BAG_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( GetBagSize() );
	packet->writeInt32( m_bagInfo.m_nCanOpenSlots - m_bagInfo.m_nOpenedSlots );
	packet->writeInt32( m_bagInfo.m_nLeftSeconds );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CExtCharBag::SendBagSellItem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_BAG_SELL_ITEMS );
	if (NULL == packet)
	{
		return;
	}

	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	for (int32_t i = 0; i < MAX_SELL_ITEM_COUNT;++i)
	{
		const MemChrBag& tSlot = m_sellItemInfo[i];
		if ( tSlot.itemCount > 0 )
		{
			packet->writeInt32( i );
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

void CExtCharBag::SaveDBData( PlayerDBData& dbData )
{
	memcpy( dbData.bagData.bagData, m_bagData, sizeof( m_bagData ) );
}

void CExtCharBag::setSellItem( const MemChrBag& sellItem )
{
	MemChrBag& endSlot = m_sellItemInfo[MAX_SELL_ITEM_COUNT-1];
	if ( endSlot.itemClass == IC_EQUIP && endSlot.srcId > 0 )
	{
		EQUIP_MANAGER.DeleteMemEquip( endSlot.srcId );
	}

	for (int32_t i = MAX_SELL_ITEM_COUNT-1; i > 0;--i)
	{
		m_sellItemInfo[i] = m_sellItemInfo[i-1];
	}

	m_sellItemInfo[0] = sellItem;
}

void CExtCharBag::deleteSellItem(int32_t index)
{
	if (index < 0|| index > MAX_SELL_ITEM_COUNT)
	{
		return;
	}

	for (int32_t i = index ; i < MAX_SELL_ITEM_COUNT-1;++i)
	{
		m_sellItemInfo[i] = m_sellItemInfo[i+1];
	}

	bzero(&m_sellItemInfo[MAX_SELL_ITEM_COUNT-1],sizeof(MemChrBag));
}


void CExtCharBag::sendGoldCashChange(int32_t type, int32_t addon, BenefitType benefitType)
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_GOLD_CASH_CHANGE);
	packet->writeInt32(type);
	packet->writeInt32(addon);
	packet->writeInt32(benefitType);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CExtCharBag::GetItemCount( const Int32Vector& vSlot, int8_t nClass, int32_t nId ) const
{
	int32_t nCount = 0;
	int32_t isize = vSlot.size();
	for ( int32_t i = 0; i < isize; ++i )
	{
		if ( !IsSlotValid( vSlot[i] ) )
		{
			continue;
		}
		const MemChrBag& bagSlot = GetSlotData( vSlot[i] );
		if ( bagSlot.itemId != nId || bagSlot.itemClass != nClass )
		{
			continue;
		}

		nCount += bagSlot.itemCount;
	}
	return nCount;
}

int32_t	CExtCharBag::GetItemType( const MemChrBag& item ) const
{
	return CItemHelper::GetItemType( item.itemId, item.itemClass );
}

bool CExtCharBag::IsEmptySlot( const MemChrBag& slot ) const
{
	return 0 == slot.itemId || 0 == slot.itemCount;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( vSlot, lst, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( vItem, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( vSlot, data, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( vItem, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( lst, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( vItem, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const ItemData& data, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( data, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( vItem, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( vSlot, lst, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( item, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( vSlot, data, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( item, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( lst, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( item, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const ItemData& data, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( data, delReason ) )
	{
		recoverBagData();
		return false;
	}

	if ( !addItem( item, addReason ) )
	{
		recoverBagData();
		return false;
	}

	saveItemChangeLog();
	return true;
}

bool CExtCharBag::AddItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason )
{
	backUpBagData();
	if ( !addItem( vItem, addReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::addItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason )
{
	int32_t isize = vItem.size();
	for ( int32_t i = 0; i < isize; ++i )
	{
		if ( UseCurrencyItem( vItem[i], addReason ) )
		{
			continue;
		}
		if ( !addItem( vItem[i], addReason ) )
		{
			return false;
		}
	}
	return true;
}

bool CExtCharBag::AddItem( const MemChrBag& item, ITEM_ADD_REASON addReason )
{
	if ( UseCurrencyItem( item, addReason ) )
	{
		return true;
	}
	backUpBagData();
	if ( !addItem( item, addReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

int32_t	CExtCharBag::HaveItemCount( const ItemData& data, bool IsBind, bool IsTimeLiness )
{
	int32_t BagSize = GetBagSize();
	int32_t Count = 0;
	for ( int32_t i = 0; i < BagSize; ++i )
	{
		if ( m_bagData[i].itemId == data.m_nId && m_bagData[i].itemClass == data.m_nClass )
		{
			if ( IsBind && m_bagData[i].bind == IBS_BIND )
			{
				if ( IsTimeLiness )
				{
					Count += m_bagData[i].itemCount;
				}
				else if ( m_bagData[i].endTime == 0 )
				{
					Count += m_bagData[i].itemCount;
				}
			}
			else if ( !IsBind && m_bagData[i].bind == IBS_UNBIND )
			{
				if ( IsTimeLiness )
				{
					Count += m_bagData[i].itemCount;
				}
				else if ( m_bagData[i].endTime == 0 )
				{
					Count += m_bagData[i].itemCount;
				}
			}
		}
	}
	return Count;
}

bool CExtCharBag::addItem( const MemChrBag& item, ITEM_ADD_REASON addReason )
{
	int32_t nLayNum = CFG_DATA.getOverlay( item.itemId, item.itemClass );
	if ( nLayNum <= 0 )
	{
		return false;
	}

	int32_t nCount = item.itemCount;
	if ( nCount < 0 )
	{
		return false;
	}

	if ( nCount == 0 )
	{
		return true;
	}

	int32_t nBagSize = GetBagSize();
	if ( nLayNum > 1 )
	{
		for ( int32_t slot = 0; slot < nBagSize; ++slot )
		{
			MemChrBag slotData = GetSlotData( slot );
			if ( !compairSlot( item, slotData ) )
			{
				continue;
			}
		
			int32_t nAddon = (std::min)( nLayNum - slotData.itemCount, nCount );
			if ( nAddon <= 0 )
			{
				continue;
			}

			slotData.itemCount += nAddon;
			setSlotData( slot, slotData, addReason );
			nCount -= nAddon;

			if ( nCount <= 0 )
			{
				return true;
			}
		}
	}

	MemChrBag bagSlot = {};
	int32_t needSlots = ( nCount % nLayNum == 0 ) ? ( nCount / nLayNum ) : ( nCount / nLayNum + 1 );
	for ( int32_t i = 0 ; i <  nBagSize ; ++i )
	{
		bagSlot = GetSlotData( i );
		if ( !IsEmptySlot( bagSlot ) )
		{
			continue;
		}

		bagSlot = item;
		if ( nCount <= nLayNum )
		{
			bagSlot.itemCount = nCount;
			setSlotData( i, bagSlot, addReason, nCount );
			return true;
		}
		else
		{
			bagSlot.itemCount = nLayNum;
			nCount -= nLayNum;
			setSlotData( i, bagSlot, addReason, nLayNum );
		}
	}

	GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), CM_QUERY_BAG_ITEMS, ERR_BAG_IS_FULL );
	return false;
}

bool CExtCharBag::RemoveItem( const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( vSlot, lst, delReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::removeItem( const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	ItemDataList::const_iterator iter = lst.begin();
	ItemDataList::const_iterator eiter = lst.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( !removeItem( vSlot, *iter, delReason ) )
		{
			return false;
		}
	}
	return true;
}

bool CExtCharBag::RemoveItem( const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( vSlot, data, delReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::removeItem( const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason )
{
	int32_t nCount = data.m_nCount;
	if ( nCount <= 0 )
	{
		return true;
	}
	int32_t isize = vSlot.size();
	for ( int32_t i = 0; i < isize; ++i )
	{
		if ( !IsSlotValid( vSlot[i] ) )
		{
			break;
		}

		MemChrBag bagSlot = GetSlotData( vSlot[i] );
		if ( !compairItem( bagSlot, data ) )
		{
			continue;
		}

		int32_t nRemove = bagSlot.itemCount < nCount ? bagSlot.itemCount : nCount;
		bagSlot.itemCount -= nRemove;
		setSlotData( vSlot[i], bagSlot, delReason, nRemove );
		if ( bagSlot.itemClass == IC_EQUIP && bagSlot.srcId > 0 )
		{
			EQUIP_MANAGER.DeleteMemEquip( bagSlot.srcId );
		}

		nCount -= nRemove;
		if ( nCount <= 0 )
		{
			return true;
		}
	}
	return false;
}

bool CExtCharBag::RemoveItem( const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( lst, delReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::RemoveCombiItem( const ItemDataList& lst, ITEM_DEL_REASON delReason)
{
	backUpBagData();
	if ( !removeCombiItem( lst, delReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::removeCombiItem(  const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	ItemDataList::const_iterator it = lst.begin();
	for ( ; it != lst.end(); ++it )
	{
		//����һ��󶨵�
		int32_t nCount = (*it).m_nCount;
		int32_t nBagSize = GetBagSize();
		for ( int32_t i = 0; i < nBagSize; ++i )
		{
			MemChrBag bagSlot = GetSlotData( i );
			if ( !compairItem( bagSlot,*it ) )
			{
				continue;
			}
			if ( bagSlot.bind == IBS_UNBIND )
			{
				continue;
			}
			int32_t nRemove = bagSlot.itemCount < nCount ? bagSlot.itemCount : nCount;
			bagSlot.itemCount -= nRemove;
			setSlotData( i, bagSlot, delReason, nRemove );
			nCount -= nRemove;
			if ( nCount <= 0 )
			{
				break;
			}
		}

		if ( nCount <= 0 )
		{
			continue;
		}

		//����һ��ǰ󶨵�
		for ( int32_t i = 0; i < nBagSize; ++i )
		{
			MemChrBag bagSlot = GetSlotData( i );
			if ( !compairItem( bagSlot, *it ) )
			{
				continue;
			}
			if ( bagSlot.bind == IBS_BIND )
			{
				continue;
			}
			int32_t nRemove = bagSlot.itemCount < nCount ? bagSlot.itemCount : nCount;
			bagSlot.itemCount -= nRemove;
			setSlotData( i, bagSlot, delReason, nRemove );
			nCount -= nRemove;
			if ( nCount <= 0 )
			{
				break;
			}
		}
		if ( nCount > 0 )
		{
			return false;
		}
	}
	return true;
}

bool CExtCharBag::removeItem( const ItemDataList& lst, ITEM_DEL_REASON delReason )
{
	ItemDataList::const_iterator iter = lst.begin();
	ItemDataList::const_iterator eiter = lst.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( !removeItem( *iter, delReason ) )
		{
			return false;
		}
	}
	return true;
}

bool CExtCharBag::RemoveItem( const ItemData& data, ITEM_DEL_REASON delReason )
{
	backUpBagData();
	if ( !removeItem( data, delReason ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::removeItem( const ItemData& data, ITEM_DEL_REASON delReason )
{
	int32_t nCount = data.m_nCount;
	int32_t nBagSize = GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		MemChrBag bagSlot = GetSlotData( i );
		if ( !compairItem( bagSlot, data ) )
		{
			continue;
		}

		int32_t nRemove = bagSlot.itemCount < nCount ? bagSlot.itemCount : nCount;
		bagSlot.itemCount -= nRemove;
		setSlotData( i, bagSlot, delReason, nRemove );

		nCount -= nRemove;
		if ( nCount <= 0 )
		{
			return true;
		}
	}
	return false;
}

void CExtCharBag::backUpBagData()
{
	memcpy( m_bagBackUp, m_bagData, sizeof( m_bagData ) );
	saveItemChangeLog();
}

void CExtCharBag::recoverBagData()
{
	memcpy( m_bagData, m_bagBackUp, sizeof( m_bagData ) );
	clearItemChangeLog();
}

void CExtCharBag::addItemChangeLog( int32_t nReason, int32_t nId, int8_t nClass, int64_t nSrcId, int32_t nCount, int8_t nFlag )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( nReason <= 0 || nClass == IC_EQUIP )
	{
		return;
	}

	LogItemChange itemLog = {};
	itemLog.cid			= m_pPlayer->getCid();
	itemLog.flag		= nFlag;
	itemLog.reason		= nReason;
	itemLog.id			= nId;
	itemLog.itemClass	= nClass;
	itemLog.count		= nCount;
	itemLog.time		= m_pPlayer->getNow();
	itemLog.srcId		= nSrcId;
	snprintf( itemLog.name, MAX_NAME_CCH_LENGTH, m_pPlayer->getName().c_str() );
	m_lstItemChangeLog.push_back( itemLog );
}

void CExtCharBag::saveItemChangeLog()
{
	LogItemChangeList::iterator iter = m_lstItemChangeLog.begin();
	LogItemChangeList::iterator eiter = m_lstItemChangeLog.end();
	for ( ; iter != eiter; ++iter )
	{
		DB_SERVICE.insertItemChange( *iter );
	}
	m_lstItemChangeLog.clear();
}

void CExtCharBag::clearItemChangeLog()
{
	m_lstItemChangeLog.clear();
}

bool CExtCharBag::compairItem( const MemChrBag& bagSlot, const ItemData& data )
{
	if ( bagSlot.itemClass != data.m_nClass )
	{
		return false;
	}

	return data.m_nId == bagSlot.itemId;
}

bool CExtCharBag::compairSlot( const MemChrBag& left, const MemChrBag& right )
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

void CExtCharBag::addDirty( int32_t nSlot, int32_t reason, bool bNeedCreate )
{
	BagDirtyList::iterator iter = m_lstDirty.begin();
	BagDirtyList::iterator eiter = m_lstDirty.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( iter->nSlot == nSlot )
		{
			return;
		}
	}

	BagDirty dirty = {};
	dirty.nSlot = nSlot;
	dirty.bChange = reason > 0;
	m_lstDirty.push_back( dirty );

	if ( bNeedCreate )
	{
		m_lstWaitCreate.push_back( nSlot );
	}
}

void CExtCharBag::ForceSendDirty()
{
	if ( sendDirty() )
	{
		clearDirty();
	}
}


void CExtCharBag::checkDirty()
{
	if ( sendDirty() )
	{
		clearDirty();
	}
}

void CExtCharBag::checkCreate()
{
	if ( NULL == m_pPlayer || m_lstWaitCreate.empty() )
	{
		return;
	}

	int32_t	nMaxSize = m_lstWaitCreate.size();

	MemEquipVector vEquip;
	vEquip.reserve( nMaxSize );

	Int32List::iterator iter = m_lstWaitCreate.begin();
	Int32List::iterator eiter = m_lstWaitCreate.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nSlot = *iter;
		const MemChrBag& bagSlot = GetSlotData( nSlot );
		if ( bagSlot.srcId > 0 )
		{
			LOG_ERROR( "CExtCharBag::checkCreate() create twice! id=%d,class=%d,srcid=%d,owner=%d,time=%d", bagSlot.itemId, bagSlot.itemClass, bagSlot.srcId, m_pPlayer->getCid(), m_pPlayer->getNow() );
			continue;
		}

		if ( bagSlot.itemClass == IC_EQUIP )
		{
			MemEquip equip = EQUIP_MANAGER.CreateMemEquip( bagSlot.itemId, m_pPlayer->getSid(), m_pPlayer->getCid() );
			MemChrBag tSlot = {};
			if ( equip.id > 0 )
			{
				tSlot		= bagSlot;
				tSlot.srcId	= equip.id;

				vEquip.push_back( equip );
			}
			setSlotData( nSlot, tSlot );
		}
	}

	if ( !vEquip.empty() )
	{
		m_pPlayer->sendEquipInfo( vEquip );
	}

	m_lstWaitCreate.clear();
}

bool CExtCharBag::sendDirty()
{
	if ( NULL == m_pPlayer || m_lstDirty.empty() )
	{
		return false;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_BAG_DIRTY );
	if (NULL == packet)
	{
		return false;
	}

	packet->writeInt8( CBT_BAG );

	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	BagDirtyList::iterator iter = m_lstDirty.begin();
	BagDirtyList::iterator eiter = m_lstDirty.end();
	for ( ; iter != eiter; ++iter )
	{
		packet->writeInt8( iter->bChange ? 1 : 0 );
		int32_t nSlot = iter->nSlot;
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
int32_t CExtCharBag::GetbagFreeSize()
{
	int32_t BagSize = GetBagSize();
	int32_t FreeCount = 0;
	for ( int32_t i = 0; i < BagSize; ++i )
	{
		if ( m_bagData[i].itemId <= 0 || m_bagData[i].itemCount <= 0 )
		{
			FreeCount++;
		}
	}
	return FreeCount;
}
void CExtCharBag::clearDirty()
{
	m_lstDirty.clear();
}

void CExtCharBag::checkBagOpen()
{
	if ( GetBagSize() >= MAX_BAG_SLOT_NUM )
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
	m_bagInfo.m_nLeftSeconds -= Rate;
	if ( nNow - m_bagInfo.m_nLastOpenTime < m_bagInfo.m_nLeftSeconds )
	{
		return;
	}
	m_bagInfo.m_nLastOpenTime = nNow;
	++m_bagInfo.m_nCanOpenSlots;

	m_bagInfo.m_nLeftSeconds = CFG_DATA.GetBagSlotOpenTimeTable().GetNeedSeconds( m_bagInfo.m_nCanOpenSlots + 1, CBT_BAG );
	SendBagInfo();
}

void CExtCharBag::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int32_t i = 0; i < m_bagInfo.m_nOpenedSlots; i++ )
	{
		const CfgBagSlotOpenTime* pCfgSlotOpen = CFG_DATA.GetBagSlotOpenTimeTable().Get( i + 1 );
		if ( NULL != pCfgSlotOpen )
		{
			m_pPlayer->AddAttrValue(CObjAttrs::ATTR_HP,pCfgSlotOpen->m_nBagAddHp);
		}
	}
}

bool CExtCharBag::UseCurrencyItem( const MemChrBag& Item, ITEM_ADD_REASON addReason )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	if ( Item.itemClass != IC_CURRENCY )
	{
		return false;
	}

	if ( Item.itemCount <= 0 )
	{
		return false;
	}
	if( addReason == IACR_PICK )
	{			switch( Item.itemId )
		{
		case CURRENCY_MONEY_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_MONEY, Item.itemCount,MCR_PICK_CURRENCY_ITEM );
			}
		case CURRENCY_GOLD_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_GOLD, Item.itemCount, GCR_PICK_CURRENCY_ITEM );
			}
		case CURRENCY_CASH_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_CASH, Item.itemCount, GCC_PICK_CURRENCY_ITEM );
			}
		case CURRENCY_VIGOUR_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_VIGOUR, Item.itemCount, GCC_PICK_CURRENCY_ITEM );
			}
		case CURRENCY_HORNOR_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_HONOR, Item.itemCount, GCC_PICK_CURRENCY_ITEM );
			}
		default:
			return false;
		}
	}
	else if ( addReason == IACR_MAIL )
	{
		switch( Item.itemId )
		{
		case CURRENCY_MONEY_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_MONEY, Item.itemCount,MCR_MAIL_CURRENCY_ITEM );
			}
		case CURRENCY_GOLD_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_GOLD, Item.itemCount, GCR_MAIL_CURRENCY_ITEM );
			}
		case CURRENCY_CASH_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_CASH, Item.itemCount, GCC_MAIL_CURRENCY_ITEM );
			}
		case CURRENCY_HORNOR_ID:
			{
				return m_pPlayer->AddCurrency( CURRENCY_HONOR, Item.itemCount, GCC_MAIL_CURRENCY_ITEM );
			}
		default:
			return false;
		}
	}

	return false;
}

void CExtCharBag::GetDropItem( Player *pKiller, PkDropRate* DropRate,MemChrBagVector& ItemVector, int32_t Mid )
{
	if ( NULL == DropRate || NULL == m_pPlayer )
	{
		return;
	}
	std::vector<int32_t> UsualItemSlotVt;
	std::vector<int32_t> SpecialItemSlotVt;

	for ( int32_t i = 0; i < GetBagSize(); ++i )
	{
		if ( m_bagData[i].itemId <= 0 || m_bagData[i].itemCount <= 0 )
		{
			continue;
		}
		if ( m_bagData[i].itemClass == IC_EQUIP )
		{
			const CfgEquip* pItem = CFG_DATA.getEquip( m_bagData[i].itemId );
			if ( NULL == pItem )
			{
				continue;
			}
			if ( pItem->m_nGrade == 1 )
			{
				if ( m_bagData[i].bind == IBS_UNBIND )
				{
					SpecialItemSlotVt.push_back(i);
				}
			}
			else
			{
				if ( m_bagData[i].bind == IBS_UNBIND )
				{
					UsualItemSlotVt.push_back(i);
				}
			}
		}

		if ( m_bagData[i].itemClass == IC_NORMAL )
		{
			CfgItem* pItem = CFG_DATA.getItem( m_bagData[i].itemId );
			if ( NULL == pItem )
			{
				continue;
			}
			if ( pItem->item_Grade == 1 )
			{
				if ( m_bagData[i].bind == IBS_UNBIND )
				{
					SpecialItemSlotVt.push_back(i);
				}
			}
			else
			{
				if ( m_bagData[i].bind == IBS_UNBIND )
				{
					UsualItemSlotVt.push_back(i);
				}
			}
		}

		if ( m_bagData[i].itemClass == IC_GEM )
		{
			const CfgItemGem* pItem = CFG_DATA.GetItemGemTable().GetItemGem( m_bagData[i].itemId );
			if ( NULL == pItem )
			{
				continue;
			}
			if ( pItem->m_nGrade == 1 )
			{
				if ( m_bagData[i].bind == IBS_UNBIND )
				{
					SpecialItemSlotVt.push_back(i);
				}
			}
			else
			{
				if ( m_bagData[i].bind == IBS_UNBIND )
				{
					UsualItemSlotVt.push_back(i);
				}
			}
		}
	}

	int32_t DropUsualItemCount = 0;
	int32_t DropSpecialItemCount = 0;
	if ( SpecialItemSlotVt.size() > 0 )
	{
		DropSpecialItemCount = SpecialItemSlotVt.size() * DropRate->SpecialCountRate / 100;
		if ( DropSpecialItemCount <= 0 )
		{
			DropSpecialItemCount = 1;
		}
	}
	if ( UsualItemSlotVt.size() > 0 )
	{
		DropUsualItemCount = UsualItemSlotVt.size() * DropRate->UsualCountRate / 100;
		if ( DropSpecialItemCount <= 0 )
		{
			DropUsualItemCount = 1;
		}
	}
	
	if ( DropSpecialItemCount > 0 )
	{
		for ( int32_t i = 0; i < DropSpecialItemCount; i++ )
		{
			int32_t nRand = RANDOM.generate(0,100);
			if ( nRand < DropRate->SpecialDropRate )
			{
				std::random_shuffle(SpecialItemSlotVt.begin(),SpecialItemSlotVt.end());
				std::vector<int32_t>::iterator it = SpecialItemSlotVt.begin();
				if ( m_bagData[*it].itemClass == IC_EQUIP )
				{
					if ( m_bagData[*it].bind == IBS_BIND )
					{
						DropEquipInfo EquipInfo;
						EquipInfo.CharId			= m_pPlayer->getCid();	
						EquipInfo.CharName			= m_pPlayer->getName();	
						if ( pKiller == NULL )
						{
							EquipInfo.KillerId			= 0;	
							EquipInfo.KillerName		= "";
							EquipInfo.Mid				= Mid;
						}
						else
						{
							EquipInfo.KillerId			= pKiller->getCid();	
							EquipInfo.KillerName		= pKiller->getName();
						}
						EquipInfo.CanGetLastTime	= m_pPlayer->getNow() + EQUIP_RANSOM_TIME;
						EquipInfo.itemId			= m_bagData[*it].itemId;	
						EquipInfo.itemClass			= m_bagData[*it].itemClass;
						EquipInfo.itemCount			= m_bagData[*it].itemCount;
						EquipInfo.bind				= m_bagData[*it].bind;
						EquipInfo.endTime			= m_bagData[*it].endTime;
						EquipInfo.srcId				= m_bagData[*it].srcId;
						EQUIP_RANSOM.AddRansom(EquipInfo);
					}
					else
					{
						ItemVector.push_back( m_bagData[*it] );
					}
					setSlotData( *it, m_nullobj, IDCR_DIE_DROP );
					SpecialItemSlotVt.erase( it );
				}
				else
				{
					int32_t DropCount = 0;
					DropCount = m_bagData[*it].itemCount * DropRate->OverlayRate / 100;
					if ( DropCount == 0 )
					{
						DropCount = 1;
					}
					MemChrBag BagDataTmp = m_bagData[*it];
					if ( m_bagData[*it].itemCount - DropCount <= 0 )
					{
						setSlotData( *it, m_nullobj, IDCR_DIE_DROP );
					}
					else
					{
						BagDataTmp.itemCount -= DropCount;
						setSlotData( *it, BagDataTmp, IDCR_DIE_DROP );
					}
					BagDataTmp.itemCount = DropCount;
					ItemVector.push_back( BagDataTmp );
					SpecialItemSlotVt.erase( it );
				}
			}
		}
	}

	if ( DropUsualItemCount > 0 )
	{
		for ( int32_t i = 0; i < DropUsualItemCount; i++ )
		{
			int32_t nRand = RANDOM.generate(0,100);
			if ( nRand < DropRate->UsualDropRate )
			{
				std::random_shuffle(UsualItemSlotVt.begin(),UsualItemSlotVt.end());
				std::vector<int32_t>::iterator it = UsualItemSlotVt.begin();
				if ( m_bagData[*it].itemClass == IC_EQUIP )
				{
					if ( m_bagData[*it].bind == IBS_BIND )
					{
						DropEquipInfo EquipInfo;
						EquipInfo.CharId			= m_pPlayer->getCid();	
						EquipInfo.CharName			= m_pPlayer->getName();	
						if ( pKiller == NULL )
						{
							EquipInfo.KillerId			= 0;	
							EquipInfo.KillerName		= "";
							EquipInfo.Mid				= Mid;
						}
						else
						{
							EquipInfo.KillerId			= pKiller->getCid();	
							EquipInfo.KillerName		= pKiller->getName();
						}	
						EquipInfo.CanGetLastTime	= m_pPlayer->getNow() + EQUIP_RANSOM_TIME;
						EquipInfo.itemId			= m_bagData[*it].itemId;	
						EquipInfo.itemClass			= m_bagData[*it].itemClass;
						EquipInfo.itemCount			= m_bagData[*it].itemCount;
						EquipInfo.bind				= m_bagData[*it].bind;
						EquipInfo.endTime			= m_bagData[*it].endTime;
						EquipInfo.srcId				= m_bagData[*it].srcId;
						EQUIP_RANSOM.AddRansom(EquipInfo);
					}
					else
					{
						ItemVector.push_back( m_bagData[*it] );
					}
					setSlotData( *it, m_nullobj, IDCR_DIE_DROP );
					UsualItemSlotVt.erase( it );
				}
				else
				{
					int32_t DropCount = 0;
					DropCount = m_bagData[*it].itemCount * DropRate->OverlayRate / 100;
					if ( DropCount == 0 )
					{
						DropCount = 1;
					}
					MemChrBag BagDataTmp = m_bagData[*it];
					if ( m_bagData[*it].itemCount - DropCount <= 0 )
					{
						setSlotData( *it, m_nullobj, IDCR_DIE_DROP );
					}
					else
					{
						BagDataTmp.itemCount -= DropCount;
						setSlotData( *it, BagDataTmp, IDCR_DIE_DROP );
					}
					BagDataTmp.itemCount = DropCount;
					ItemVector.push_back( BagDataTmp );
					UsualItemSlotVt.erase( it );
				}
			}
		}
	}
}

void CExtCharBag::SendRansomInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_RANSOM_INFO );
	if (NULL == packet)
	{
		return;
	}
	RANSOM_ITEM_LIST EquipList;
	EQUIP_RANSOM.GetRansomInfo( m_pPlayer->getCid(), EquipList );
	EQUIP_RANSOM.PackRansomInfo( packet, EquipList );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CExtCharBag::SendSpoilsInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_SPOILS_INFO );
	if (NULL == packet)
	{
		return;
	}
	RANSOM_ITEM_LIST EquipList;
	EQUIP_RANSOM.GetSpoilsInfo( m_pPlayer->getCid(), EquipList );
	EQUIP_RANSOM.PackRansomInfo( packet, EquipList );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}


bool CExtCharBag::AddItemsAndEggs( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( vItem.empty() )
	{
		return true;
	}
	MemChrBagVector items;
	std::list<int32_t> Eggs;
	for (MemChrBagVector::const_iterator it = vItem.begin(); it != vItem.end(); ++it)
	{

		if ( it->itemClass == IC_PET_EGG )
		{
			const CfgPetEgg* pPetEgg = CFG_DATA.GetPetEggTable().GetEgg(it->itemId);
			if ( pPetEgg == NULL )
			{
				continue;
			}
			int32_t ItemCount = it->itemCount;
			while( ItemCount > 0 )
			{
				Eggs.push_back(it->itemId);
				ItemCount--;
			}
		}	
		else
		{
			items.push_back(*it);
		}
	}
	if ( m_pPlayer->GetCharPet().GetEggBagAddHatchBagFreeCount() < static_cast<int32_t>( Eggs.size() ) )
	{
		m_pPlayer->TiShiInfo( PET_EGG_BAG_NOT_ENOUGH );
		return false;
	}
	if ( m_pPlayer->GetBag().GetFreeSlotCount() < static_cast<int32_t>( items.size() ) )
	{
		m_pPlayer->TiShiInfo( BAG_SLOT_NOT_ENOUGH );
		return false;
	}
	if ( Eggs.size() > 0 )
	{
		m_pPlayer->GetCharPet().AddEggs( Eggs );
	}

	if ( items.size() > 0 )
	{
		m_pPlayer->GetBag().AddItem( items, addReason );
	}
	return true;
}

void CExtCharBag::OnDaySwitch( int32_t nDiffDays )
{
	m_ItemLimit.clear();
	SendLimitCount();
}

bool CExtCharBag::RemoveItem( const ItemData& data, ITEM_DEL_REASON delReason, int32_t& BindCount, int32_t& UnBindCount )
{
	backUpBagData();
	if ( !removeItem( data, delReason, BindCount, UnBindCount ) )
	{
		recoverBagData();
		return false;
	}
	saveItemChangeLog();
	return true;
}

bool CExtCharBag::removeItem( const ItemData& data, ITEM_DEL_REASON delReason, int32_t& BindCount, int32_t& UnBindCount )
{
	int32_t nCount = data.m_nCount;
	int32_t nBagSize = GetBagSize();
	//��ɾ��
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		MemChrBag bagSlot = GetSlotData( i );
		if ( !compairItem( bagSlot, data ) )
		{
			continue;
		}
		if (  bagSlot.bind != IBS_BIND )
		{
			continue;
		}
		int32_t nRemove = bagSlot.itemCount < nCount ? bagSlot.itemCount : nCount;
		bagSlot.itemCount -= nRemove;
		BindCount += nRemove;
		setSlotData( i, bagSlot, delReason, nRemove );
		nCount -= nRemove;
		if ( nCount <= 0 )
		{
			return true;
		}
	}

	for ( int32_t j = 0; j < nBagSize; ++j )
	{
		MemChrBag bagSlot = GetSlotData( j );
		if ( !compairItem( bagSlot, data ) )
		{
			continue;
		}
		if (  bagSlot.bind != IBS_UNBIND )
		{
			continue;
		}
		int32_t nRemove = bagSlot.itemCount < nCount ? bagSlot.itemCount : nCount;
		bagSlot.itemCount -= nRemove;
		UnBindCount += nRemove;
		setSlotData( j, bagSlot, delReason, nRemove );
		nCount -= nRemove;
		if ( nCount <= 0 )
		{
			return true;
		}
	}
	return false;
}

// ========== ���°汾�·��� ==========

int32_t CExtCharBag::onUseItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t slot = inPacket->readInt32();
	int32_t type = inPacket->readInt32();
	int32_t nItemId = inPacket->readInt32();

	if ( !IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( slot );
	if ( slotData.itemCount <= 0 || slotData.itemId != nItemId )
	{
		return ERR_INVALID_DATA;
	}

	if ( slotData.endTime > 0 && slotData.endTime < m_pPlayer->getNow() )
	{
		return ERR_INVALID_DATA;
	}

	CfgItem* cfgItem = CFG_DATA.getItem( slotData.itemId );
	if ( NULL == cfgItem || !canUseItem( slot, cfgItem ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( cfgItem->type == 106 )
	{
		if ( m_pPlayer->IsInFight() )
		{
			return ERR_INVALID_DATA;
		}
	}

	if ( slotData.itemId == ISI_XIAO_JV_HUA )
	{
		if ( m_pPlayer->getRecord( PR_XIAO_JV_HUA_SHI_YONG ) >= 10 )
		{
			return ERR_INVALID_DATA;
		}
	}

	int32_t err = ERR_INVALID_DATA;
	if ( type == ET_PLAYER )
	{
		err = ITEM_EFFECT.effect( slotData.itemId, *m_pPlayer, *m_pPlayer, 1 );
	}

	if ( err == ERR_OK )
	{
		if ( slotData.itemId == ISI_XIAO_JV_HUA )
		{
			m_pPlayer->updateRecord( PR_XIAO_JV_HUA_SHI_YONG, m_pPlayer->getRecord( PR_XIAO_JV_HUA_SHI_YONG ) + 1 );
		}

		m_pPlayer->GetTask().updateTaskUseItem( slotData.itemId, 1 );
		slotData.itemCount--;
		SetSlotData( slot, slotData, IDCR_BAG_USE, 1 );

		m_lastItemTick[cfgItem->cd_group] = m_pPlayer->getTick();

		if ( cfgItem->broadcast > 0 )
		{
			sendUseBroadcast( cfgItem->broadcast, m_pPlayer->getName(), m_pPlayer->getCid(), slotData.itemId );
		}

		GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_USE_ITEM, cfgItem->id );
	}

	return err;
}

int32_t CExtCharBag::onPatchUseItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t slot = inPacket->readInt32();
	int32_t count = inPacket->readInt32();
	int32_t nItemId = inPacket->readInt32();

	if ( !IsSlotValid( slot ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( slot );
	if ( slotData.itemCount <= 0 || slotData.itemId != nItemId )
	{
		return ERR_INVALID_DATA;
	}

	if ( slotData.endTime > 0 && slotData.endTime < m_pPlayer->getNow() )
	{
		return ERR_INVALID_DATA;
	}

	CfgItem* cfgItem = CFG_DATA.getItem( slotData.itemId );
	if ( NULL == cfgItem || !canUseItem( slot, cfgItem ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( count > slotData.itemCount )
	{
		count = slotData.itemCount;
	}

	int32_t err = ERR_OK;
	if ( cfgItem->type == 106 || cfgItem->type == 108 )
	{
		if ( cfgItem->type == 106 && m_pPlayer->IsInFight() )
		{
			return ERR_INVALID_DATA;
		}

		int32_t used = 0;
		for ( int32_t i = 0; i < count; ++i )
		{
			err = ITEM_EFFECT.effect( slotData.itemId, *m_pPlayer, *m_pPlayer, 1 );
			if ( err == ERR_OK )
			{
				m_pPlayer->GetTask().updateTaskUseItem( slotData.itemId, 1 );
				slotData.itemCount--;
				SetSlotData( slot, slotData, IDCR_BAG_USE, 1 );
				used++;
			}
		}

		if ( cfgItem->type == 108 )
		{
			m_pPlayer->RecalcAttr();
		}

		m_lastItemTick[cfgItem->cd_group] = m_pPlayer->getTick();
		GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_PATCH_USE_ITEM, nItemId );
		err = ERR_OK;
	}
	else
	{
		err = ITEM_EFFECT.effect( slotData.itemId, *m_pPlayer, *m_pPlayer, count );
		if ( err == ERR_OK )
		{
			m_pPlayer->GetTask().updateTaskUseItem( slotData.itemId, count );
			slotData.itemCount -= count;
			SetSlotData( slot, slotData, IDCR_BAG_USE, count );

			m_lastItemTick[cfgItem->cd_group] = m_pPlayer->getTick();
			GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_PATCH_USE_ITEM, cfgItem->id );
		}
	}

	return err;
}

int32_t CExtCharBag::onSelectItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nSlot = inPacket->readInt32();
	int32_t nId = inPacket->readInt32();

	if ( !IsSlotValid( nSlot ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( nSlot );
	if ( slotData.itemCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	CfgItem* cfgItem = CFG_DATA.getItem( slotData.itemId );
	if ( NULL == cfgItem )
	{
		return ERR_INVALID_DATA;
	}

	if ( cfgItem->type != 213 )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBagVector selectItems = CItemHelper::parseItemString( slotData.itemId, cfgItem->effect );
	if ( selectItems.empty() )
	{
		return ERR_INVALID_DATA;
	}

	if ( nId < 0 || nId >= (int32_t)selectItems.size() )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetFreeSlotCount() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !RemoveItem( ItemData( slotData.itemId, slotData.itemClass, 1 ), IDCR_SELECT_ITEM ) )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !AddItemsAndMingGe( selectItems, IACR_SELECT_ITEM ) )
	{
		return ERR_SYETEM_ERR;
	}

	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_SELECT_ITEM, nId );
	return ERR_OK;
}

int32_t CExtCharBag::onDiscardItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	/* line check removed for compatibility */

	int32_t nSlot = inPacket->readInt32();
	if ( !IsSlotValid( nSlot ) )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slotData = GetSlotData( nSlot );
	if ( slotData.itemCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( slotData.bind == IBS_BIND || slotData.bind == IBS_BIND_2 )
	{
		CleanSlot( nSlot, IDCR_DISCARD );
	}
	else
	{
		CfgItem* cfgItem = CFG_DATA.getItem( slotData.itemId );
		if ( NULL == cfgItem )
		{
			return ERR_INVALID_DATA;
		}

		Map* pMap = MAP_MANAGER.GetMap( m_pPlayer->getMapId() );
		if ( NULL == pMap )
		{
			return ERR_SYETEM_ERR;
		}

		Position pos = m_pPlayer->getCurrentTile();
		DropItem dropItem = {};
		dropItem.itemId = slotData.itemId;
		dropItem.itemClass = slotData.itemClass;
		dropItem.itemCount = slotData.itemCount;
		dropItem.bindType = slotData.bind;
		dropItem.endTime = slotData.endTime;
		dropItem.srcId = slotData.srcId;
		CDropItemGroup* pDrop = new CDropItemGroup();
		if ( NULL != pDrop )
		{
			DropItem dropItems[MAX_DROPITEM_SIZE] = {};
			dropItems[0] = dropItem;
			pDrop->init( pMap, pos, m_pPlayer, -1, 0, dropItems, m_pPlayer->getName(), 0, 0 );
			pMap->addDropItemGroup( pDrop );
		}

		CleanSlot( nSlot, IDCR_DISCARD );
	}

	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_DISCARD_ITEM, nSlot );
	return ERR_OK;
}

int32_t CExtCharBag::onUseMutiItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nId = inPacket->readInt32();
	int32_t nCount = inPacket->readInt32();
	if ( nCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	CfgItem* cfgItem = CFG_DATA.getItem( nId );
	if ( NULL == cfgItem )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nSlot = GetItemSlot( nId, IC_NORMAL );
	if ( nSlot < 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !canUseItem( nSlot, cfgItem ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nHasCount = GetItemCount( nId, IC_NORMAL );
	if ( nCount > nHasCount )
	{
		nCount = nHasCount;
	}

	int32_t err = ITEM_EFFECT.effect( nId, *m_pPlayer, *m_pPlayer, nCount );
	if ( err == ERR_OK )
	{
		m_pPlayer->GetTask().updateTaskUseItem( nId, nCount );
		RemoveItem( ItemData( nId, IC_NORMAL, nCount ), IDCR_BAG_USE );
		m_lastItemTick[cfgItem->cd_group] = m_pPlayer->getTick();
		GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_USE_MMULTI_ITEM, nId );
	}

	return err;
}

int32_t CExtCharBag::onAddItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	int32_t nReason = inPacket->readInt32();
	std::string MailParam = inPacket->readUTF8( true );

	MemChrBagVector vItem;
	int32_t nSize = inPacket->readInt32();
	vItem.resize( nSize );

	for ( int32_t i = 0; i < nSize; ++i )
	{
		MemChrBag& item = vItem[i];
		item.itemId = inPacket->readInt32();
		item.itemClass = inPacket->readInt8();
		item.itemCount = inPacket->readInt32();
		item.bind = inPacket->readInt8();
		item.endTime = inPacket->readInt32();
		item.srcId = inPacket->readInt64();
	}

	if ( !AddItem( vItem, (ITEM_ADD_REASON)nReason ) )
	{
		int32_t MailId = 6208;
		if ( nReason == IACR_AUCTION_BUY )
		{
			MailId = 6208;
		}
		else if ( nReason == IACR_AUCTION_CANCEL )
		{
			MailId = 6209;
		}
		DB_SERVICE.OnSendSysMail( m_pPlayer->getCid(), MailId, vItem, MailParam );
	}

	return 0;
}

bool CExtCharBag::canUseItem( int32_t nSlot, const CfgItem* cfgItem )
{
	if ( NULL == m_pPlayer || NULL == cfgItem )
	{
		return false;
	}

	if ( cfgItem->level > m_pPlayer->getLevel() )
	{
		return false;
	}

	if ( cfgItem->job != 0 && cfgItem->job != m_pPlayer->getJob() )
	{
		return false;
	}	/* carrier check removed for compatibility */

	if ( cfgItem->cd_group < 0 || cfgItem->cd_group >= ITEM_CD_GROUP_COUNT )
	{
		return false;
	}

	if ( m_pPlayer->getTick() - m_lastItemTick[cfgItem->cd_group] < m_itemCD[cfgItem->cd_group] )
	{
		GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), CM_USE_ITEM, ERR_ITEM_CD );
		return false;
	}

	return true;
}

bool CExtCharBag::isAutoUseItem( const CfgItem* cfgItem )
{
	if ( NULL == cfgItem )
	{
		return false;
	}
	return cfgItem->type == 1 || cfgItem->type == 4 || cfgItem->type == 86;
}

bool CExtCharBag::autoUseItem( const MemChrBag& item )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	if ( item.itemCount <= 0 )
	{
		return false;
	}

	if ( item.itemClass == IC_CURRENCY )
	{
		if ( item.itemId == CURRENCY_GOLD_ID )
		{
			m_pPlayer->AddCurrency( CURRENCY_GOLD, item.itemCount, GCR_AUTO_USE );
			return true;
		}
		else if ( item.itemId == CURRENCY_CASH_ID )
		{
			m_pPlayer->AddCurrency( CURRENCY_CASH, item.itemCount, GCC_AUTO_USE );
			return true;
		}
		else if ( item.itemId == CURRENCY_HORNOR_ID )
		{
			m_pPlayer->AddCurrency( CURRENCY_HONOR, item.itemCount, GCC_AUTO_USE );
			return true;
		}
		else if ( item.itemId == CURRENCY_VIGOUR_ID )
		{
			m_pPlayer->AddCurrency( CURRENCY_VIGOUR, item.itemCount, GCC_AUTO_USE );
			return true;
		}
		else
		{
			return m_pPlayer->AddCurrency( CURRENCY_MONEY, item.itemCount, MCR_AUTO_USE );
		}
	}
	else if ( item.itemClass == IC_NORMAL )
	{
		CfgItem* cfgItem = CFG_DATA.getItem( item.itemId );
		if ( NULL == cfgItem )
		{
			return false;
		}

		if ( cfgItem->type == 1 || cfgItem->type == 86 )
		{
			int32_t err = ITEM_EFFECT.effect( item.itemId, *m_pPlayer, *m_pPlayer, item.itemCount );
			return err == ERR_OK;
		}
	}

	return false;
}

void CExtCharBag::sendUseBroadcast( int32_t nBroadcast, const std::string& p_name, CharId_t cid, int32_t nItemId )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nBroadcast );
	packet->writeUTF8( p_name );
	packet->writeInt64( cid );
	packet->writeInt32( nItemId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CExtCharBag::CleanItemId( int32_t nId, int32_t nReason, int8_t nClass )
{
	int32_t nBagSize = GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		const MemChrBag& slotData = GetSlotData( i );
		if ( slotData.itemId == nId && slotData.itemClass == nClass )
		{
			setSlotData( i, m_nullobj, nReason, 0 );
		}
	}
}

int32_t CExtCharBag::GetItemSlot( int32_t nId, int8_t nClass ) const
{
	int32_t nBagSize = GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		const MemChrBag& slotData = GetSlotData( i );
		if ( slotData.itemId == nId && slotData.itemClass == nClass )
		{
			return i;
		}
	}
	return -1;
}

int32_t CExtCharBag::GetTypeItem( int32_t nType ) const
{
	int32_t nBagSize = GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		if ( CItemHelper::GetItemType( m_bagData[i].itemId, m_bagData[i].itemClass ) == nType )
		{
			return i;
		}
	}
	return -1;
}

bool CExtCharBag::AddItemsAndMingGe( const MemChrBagVector& vItem, int32_t addReason )
{
	if ( NULL == m_pPlayer || vItem.empty() )
	{
		return false;
	}

	MemChrBagVector items;
	for ( MemChrBagVector::const_iterator it = vItem.begin(); it != vItem.end(); ++it )
	{
		if ( it->itemClass == IC_NORMAL || it->itemClass == IC_EQUIP || it->itemClass == IC_GEM )
		{
			items.push_back( *it );
		}
	}

	if ( items.empty() )
	{
		return true;
	}

	return AddItem( items, (ITEM_ADD_REASON)addReason );
}
