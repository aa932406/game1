#include "stdafx.h"
#include "ChouJiang.h"
#include "GameService.h"
#include "DataStruct.h"
#include "EquipManager.h"
#define MAX_LUCK_POINT	500 //最大幸运值
#define CHOU_JIANG_RECORD_MAX_COUT	50 //抽奖记录最多50条


enum ChouJiangTimes
{
	CJT_ONE_TIME	= 1,
	CJT_TEN_TIME	= 10,
};

ChouJiang::ChouJiang()
{
	CleanUp();
}

ChouJiang::~ChouJiang()
{

}

void ChouJiang::CleanUp()
{
	 m_RecordList.clear();		
	 m_LuckyPoint		= 0;		
	 bzero(&m_ItemList,sizeof(m_ItemList));
}

void ChouJiang::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_LuckyPoint	= dbData.m_ChouJinagData.m_LuckyPoint;
	m_RecordList	= dbData.m_ChouJinagData.m_RecordList;
	memcpy( m_ItemList, dbData.m_ChouJinagData.m_ItemList, sizeof(m_ItemList) );
}

void ChouJiang::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_ChouJinagData.m_LuckyPoint		= m_LuckyPoint;
	dbData.m_ChouJinagData.m_RecordList		= m_RecordList;
	memcpy( dbData.m_ChouJinagData.m_ItemList, m_ItemList, sizeof(m_ItemList) );
}

void ChouJiang::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_CHOU_JIANG );
	procList.push_back( CM_TIDY_CHOU_JIANG_BAG );
	procList.push_back( CM_GET_CHOU_JIANG_ITEM );
	procList.push_back( CM_ASK_CHOU_JIANG_RECORD );
	procList.push_back( IM_SOCIAL_GAME_ASK_CHOU_JIANG );
}

int32_t ChouJiang::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case CM_ASK_CHOU_JIANG:
		{
			return OnAskChouJiang( inPacket );
		}
	case CM_TIDY_CHOU_JIANG_BAG:
		{
			return OnTidy( inPacket );
		}
	case CM_GET_CHOU_JIANG_ITEM:
		{
			return OnGetItem( inPacket );
		}
	case CM_ASK_CHOU_JIANG_RECORD:
		{
			return OnAskChouJiangRecord( inPacket );
		}
	case IM_SOCIAL_GAME_ASK_CHOU_JIANG:
		{
			return OnChouJiang( inPacket );
		}
	default:
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t	ChouJiang::OnAskChouJiang( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t ChouJiangType  = inPacket->readInt8();
	int8_t ChouJiangTimes = inPacket->readInt8();
	if ( ChouJiangTimes != CJT_ONE_TIME && ChouJiangTimes != CJT_TEN_TIME )
	{
		return ERR_SYETEM_ERR;
	}

	if ( GetFreeCount() < ChouJiangTimes )
	{
		return ERR_SYETEM_ERR;
	}

	ChouJiangCost* pCJCost = CFG_DATA.GetChouJiangCfg().GetCJCost( ChouJiangType );
	if ( NULL == pCJCost )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t BindTimes = 0;
	int32_t AllTimes  = 0;
	std::vector<int32_t> BindBagSlotVt;
	std::vector<int32_t> UnBindBagSlotVt;
	BindBagSlotVt.clear();
	UnBindBagSlotVt.clear();
	CheckChouJiangItemList( pCJCost, BindTimes, AllTimes, BindBagSlotVt, UnBindBagSlotVt );
	if ( BindTimes < ChouJiangTimes && ( AllTimes - BindTimes ) < ChouJiangTimes )//绑定物品,非绑定物品,不能混合使用
	{
		int64_t HaveGold = m_pPlayer->GetCurrency( CURRENCY_GOLD );
		int32_t NeedGold = 0;
		if ( ChouJiangTimes == CJT_ONE_TIME )
		{
			NeedGold = pCJCost->CostGold;
		}
		else 
		{
			NeedGold = pCJCost->CostGold2;
		}
		if ( NeedGold <= 0 || NeedGold > HaveGold )
		{
			return ERR_SYETEM_ERR;
		}
	}
	CheckGlobalPoint( ChouJiangType, ChouJiangTimes );
	return ERR_OK;
}

int32_t ChouJiang::OnChouJiang( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{	
		return ERR_SYETEM_ERR;
	}
	int8_t	ChouJiangType  = inPacket->readInt8();
	int8_t	ChouJiangTimes = inPacket->readInt8();
	int8_t	Special		   = inPacket->readInt8();

	if ( ChouJiangTimes != CJT_ONE_TIME && ChouJiangTimes != CJT_TEN_TIME )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFreeCount() < ChouJiangTimes )
	{
		return ERR_SYETEM_ERR;
	}

	ChouJiangCost* pCJCost = CFG_DATA.GetChouJiangCfg().GetCJCost( ChouJiangType );
	if ( NULL == pCJCost )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t BindTimes	 = 0;
	int32_t AllTimes	 = 0;
	std::vector<int32_t> BindBagSlotVt;
	std::vector<int32_t> UnBindBagSlotVt;
	BindBagSlotVt.clear();
	UnBindBagSlotVt.clear();
	CheckChouJiangItemList( pCJCost, BindTimes, AllTimes, BindBagSlotVt, UnBindBagSlotVt );
	int64_t HaveGold = m_pPlayer->GetCurrency( CURRENCY_GOLD );
	int32_t NeedGold = 0;
	if ( BindTimes < ChouJiangTimes && ( AllTimes - BindTimes ) < ChouJiangTimes )//绑定物品,非绑定物品,不能混合使用
	{
		if ( ChouJiangTimes == CJT_ONE_TIME )
		{
			NeedGold = pCJCost->CostGold;
		}
		else 
		{
			NeedGold = pCJCost->CostGold2;
		}
		if ( NeedGold <= 0 || NeedGold > HaveGold )
		{
			return ERR_SYETEM_ERR;
		}
	}
	ItemData Item = {};
	Item.m_nClass = pCJCost->CostItemClass;
	Item.m_nCount = pCJCost->CostItemCount * ChouJiangTimes;
	Item.m_nId	  = pCJCost->CostItemId;
	if ( ( Item.m_nId <=0 || Item.m_nCount <= 0 ) && NeedGold <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( BindTimes >= ChouJiangTimes )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( BindBagSlotVt, Item, IDCR_CHOU_JIANG ) )
		{
			return ERR_SYETEM_ERR;
		}
		NoAddLuckPointChoujiang( ChouJiangType, ChouJiangTimes );
	}
	else if ( AllTimes - BindTimes >= ChouJiangTimes )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( UnBindBagSlotVt, Item, IDCR_CHOU_JIANG ) )
		{
			return ERR_SYETEM_ERR;
		}
		AddLuckPointChouJiang( ChouJiangType, ChouJiangTimes, Special );
	}
	else
	{
		if ( NeedGold <= 0 || NeedGold > HaveGold )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, NeedGold, GCR_CHOU_JIANG ) )
		{
			return ERR_SYETEM_ERR;
		}
		AddLuckPointChouJiang( ChouJiangType, ChouJiangTimes, Special );
	}
	m_pPlayer->GetAchievemnet().AddAchievement( AT_CHOU_JIANG, ChouJiangTimes );
	m_pPlayer->AddCurrency( CURRENCY_CHOUJINAG,pCJCost->AddScore * ChouJiangTimes,SCR_ON_CHOU_JIANG );
	return ERR_OK;
}

int32_t ChouJiang::NoAddLuckPointChoujiang( int8_t ChouJiangType, int8_t ChouJiangTimes  )
{
	CJCfgList CJCfgItem;
	CJCfgItem.clear();
	while( ChouJiangTimes > 0 )
	{
		ChouJiangTimes--;
		ChouJiangCfg pCJCfg = CFG_DATA.GetChouJiangCfg().GetCJCfg( ChouJiangType );
		if ( pCJCfg.IsEmpty() )
		{
			continue;
		}
		CJCfgItem.push_back( pCJCfg );
	}
	AddItem( CJCfgItem ,IBS_BIND );
	return ERR_OK;
}

int32_t ChouJiang::AddLuckPointChouJiang( int8_t ChouJiangType, int8_t ChouJiangTimes, int8_t Special )
{
	CJCfgList CJCfgItem;
	CJCfgItem.clear();
	int32_t AddCount = ChouJiangTimes;
	bool    IsClean	 = false;
	while( ChouJiangTimes > 0 )
	{
		ChouJiangTimes--;
		ChouJiangCfg pCJCfg = {};
		if ( Special || m_LuckyPoint >= MAX_LUCK_POINT )
		{
			pCJCfg = CFG_DATA.GetChouJiangCfg().GetCJCfg( ChouJiangType, true );
			if ( pCJCfg.IsEmpty() )
			{
				continue;
			}
			IsClean	= true;
			Special = false;
			CleanLuckyPoint();
		}
		else
		{
			pCJCfg = CFG_DATA.GetChouJiangCfg().GetCJCfg( ChouJiangType );
		}

		if ( pCJCfg.IsEmpty() )
		{
			continue;
		}
		if ( pCJCfg.Quality == 4 )
		{
			IsClean = true;
			CleanLuckyPoint();
		}
		CJCfgItem.push_back( pCJCfg );
		m_LuckyPoint++;
	}
	AddItem( CJCfgItem );
	ChangeGlobalPoint( AddCount, IsClean );
	return ERR_OK;
}

int32_t	ChouJiang::OnAskChouJiangRecord( Answer::NetPacket *inPacket )
{
	SendChouJiangRecord();
	ToGlobalAskChouJiangRecord();
	return ERR_OK;
}

int32_t ChouJiang::ToGlobalAskChouJiangRecord()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_PROC, IM_GAME_SOCIAL_ASK_CHOU_JIANG_RECORD);
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt8( 0 );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
	return ERR_OK;
}

int32_t	ChouJiang::OnGetItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t Slot = inPacket->readInt32();
	if ( Slot < -1 || Slot >= MAX_ITEM_LIST )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->GetBag().GetFreeSlotCount() < 1 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( Slot == -1 )
	{
		for ( int32_t i = 0; i < MAX_ITEM_LIST; i++ )
		{
			if ( m_ItemList[i].itemCount <= 0 || m_ItemList[i].itemId <= 0 )
			{
				continue;
			}
			GetItem( i );
		}
	}
	else
	{
		GetItem( Slot );
	}
	
	return ERR_OK;
}

int32_t ChouJiang::OnTidy( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	std::map<int32_t,MemChrBag> ItemTmp;
	ItemTmp.clear();
	for (  int32_t i = 0; i < MAX_ITEM_LIST; i++  )
	{
		if ( m_ItemList[i].itemCount <= 0 || m_ItemList[i].itemId <= 0 )
		{
			continue;
		}
		ItemTmp[i] = m_ItemList[i];
		bzero( &m_ItemList[i], sizeof(m_ItemList[i]) );
	}
	std::map<int32_t,MemChrBag>::iterator it = ItemTmp.begin();
	for ( ; it != ItemTmp.end(); ++it )
	{
		for (  int32_t i = 0; i < MAX_ITEM_LIST; i++  )
		{
			if ( m_ItemList[i].itemCount <= 0 || m_ItemList[i].itemId <= 0 )
			{
				m_ItemList[i] = it->second;
				break;
			}
			else
			{
				if ( m_ItemList[i].itemClass == IC_EQUIP || m_ItemList[i].itemClass == IC_PET_EGG ) // 装备不能跌加
				{
					continue;
				}
				else if ( m_ItemList[i].itemClass == it->second.itemClass &&
					m_ItemList[i].itemId  == it->second.itemId &&
					m_ItemList[i].bind    == it->second.bind &&
					m_ItemList[i].srcId	== it->second.srcId 
					)
				{
					m_ItemList[i].itemCount += it->second.itemCount;
					break;
				}
			}
		}
	}
	SendChouJiangItem();
	return ERR_OK;
}

void ChouJiang::SendChouJiangRecord()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_CHOU_JIANG_RECORD );
	if (NULL == packet)
	{
		return;
	}
	int32_t Count = m_RecordList.size();
	packet->writeInt32( Count );
	CJRecordList::iterator it = m_RecordList.begin();
	for ( ; it != m_RecordList.end(); ++it )
	{
		packet->writeInt32(  it->CJItem.itemId );
		packet->writeInt8( it->CJItem.itemClass );
		packet->writeInt32( it->CJItem.itemCount );
		packet->writeInt32( it->Time );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

void ChouJiang::AddChouJiangRecord( MemChrBag& CJItem, int32_t Time, int8_t IsRecord )
{
	ChouJiangRecord Record = {};
	Record.CJItem	= CJItem;
	Record.Time		= Time;
	if ( m_RecordList.size() >= CHOU_JIANG_RECORD_MAX_COUT )
	{
		m_RecordList.pop_front();
		m_RecordList.push_back( Record );
	}
	else
	{
		m_RecordList.push_back( Record );
	}
	SendNewRecord( CJItem, Time );
	if ( IsRecord == 1 )
	{
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_PROC, IM_GAME_SOCIAL_ADD_CHOU_JIANG_RECORD);
		if ( NULL == packet || NULL == m_pPlayer )
		{
			return;
		}
		packet->writeInt32( m_pPlayer->getGateIndex() );
		packet->writeInt64( m_pPlayer->getCid() );
		packet->writeUTF8( m_pPlayer->getName() );
		packet->writeInt8( CJItem.itemClass );
		packet->writeInt32( CJItem.itemId );
		packet->writeInt32( CJItem.itemCount );
		packet->setSize(packet->getWOffset());
		GAME_SERVICE.sendPacket(packet);
	}
}

void ChouJiang::SendNewRecord( MemChrBag& CJItem, int32_t Time )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ADD_CHOU_JIANG_RECORD );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32(  CJItem.itemId );
	packet->writeInt8( CJItem.itemClass );
	packet->writeInt32( CJItem.itemCount );
	packet->writeInt32( Time );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

void ChouJiang::CheckGlobalPoint( int8_t ChouJiangType, int8_t ChouJiangTimes )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_PROC, IM_GAME_SOCIAL_CHECK_GLOBAL_POINT);
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt8( ChouJiangType );
	packet->writeInt8( ChouJiangTimes );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void ChouJiang::CleanLuckyPoint()
{
	m_LuckyPoint = 0;
}

void ChouJiang::ChangeGlobalPoint(  int32_t AddCount, bool IsClean )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_PROC, IM_GAME_SOCIAL_CLEAN_GLOBAL_POINT);
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt8( AddCount );
	packet->writeInt8( IsClean ? 1 : 0 );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

bool ChouJiang::CheckChouJiangItemList( ChouJiangCost* pCJCost,int32_t& BindTimes, int32_t& AllTimes,std::vector<int32_t>& BindBagSlotVt, std::vector<int32_t>& UnBindBagSlotVt  )
{
	if ( NULL == m_pPlayer || NULL == pCJCost )
	{
		return false;
	}
	int32_t BindCount		= 0;
	int32_t UnBindCount		= 0;
	int32_t BagSize = m_pPlayer->GetBag().GetBagSize();
	for ( int32_t i = 0; i < BagSize; i++ )
	{
		 const MemChrBag Item = m_pPlayer->GetBag().GetSlotData(i);
		 if ( Item.itemClass == pCJCost->CostItemClass &&
			  Item.itemId  == pCJCost->CostItemId )
		 {
			 if ( Item.bind == IBS_BIND )
			 {
				BindCount += Item.itemCount;
				BindBagSlotVt.push_back(i);
			 }
			 else
			 {
				UnBindCount += Item.itemCount;
				UnBindBagSlotVt.push_back(i);
			 }
		 }
	}
	if ( pCJCost->CostItemCount <= 0 || pCJCost->CostItemId <= 0 )
	{
		return false;
	}
	BindTimes = BindCount /  pCJCost->CostItemCount;
	AllTimes  = ( UnBindCount / pCJCost->CostItemCount ) + BindTimes;
	return true;
}

void ChouJiang::SendChouJiangItemChang( std::list<int32_t>& ItemList )
{
	int32_t Count = ItemList.size();
	if ( Count <= 0 )
	{
		return;
	}
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_CHOU_JIANG_ITEM_CHANGE );
	if (NULL == packet)
	{
		return;
	}
	
	packet->writeInt32( Count );
	std::list<int32_t>::iterator it = ItemList.begin();
	for ( ; it != ItemList.end(); it++  )
	{
		packet->writeInt32( *it );
		packet->writeInt32( m_ItemList[*it].itemId );
		packet->writeInt8( m_ItemList[*it].itemClass );
		packet->writeInt32(m_ItemList[*it].itemCount );
		packet->writeInt8( m_ItemList[*it].bind );
		packet->writeInt32( m_ItemList[*it].endTime );
		packet->writeInt64( m_ItemList[*it].srcId );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

void ChouJiang::SendGetItem( std::list<int32_t>& ItemList )
{
	int32_t Count = ItemList.size();
	if ( Count <= 0 )
	{
		return;
	}
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_GET_ITEM );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( Count );
	std::list<int32_t>::iterator it = ItemList.begin();
	for ( ; it != ItemList.end(); it++  )
	{
		packet->writeInt32( *it );
		packet->writeInt32( m_ItemList[*it].itemId );
		packet->writeInt8( m_ItemList[*it].itemClass );
		packet->writeInt32(m_ItemList[*it].itemCount );
		packet->writeInt8( m_ItemList[*it].bind );
		packet->writeInt32( m_ItemList[*it].endTime );
		packet->writeInt64( m_ItemList[*it].srcId );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

void ChouJiang::SendChouJiangItem()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ALL_CHOU_JIANG_ITEM );
	if (NULL == packet)
	{
		return;
	}
	int32_t Count = 0;
	int32_t OldOffet = packet->getWOffset();
	packet->writeInt32( Count );
	for ( int32_t i = 0; i < MAX_ITEM_LIST; ++i )
	{
		if ( m_ItemList[i].itemCount <= 0 || m_ItemList[i].itemId <= 0 )
		{
			continue;
		}
		Count++;
		packet->writeInt32( i );
		packet->writeInt32( m_ItemList[i].itemId );
		packet->writeInt8( m_ItemList[i].itemClass );
		packet->writeInt32(m_ItemList[i].itemCount );
		packet->writeInt8( m_ItemList[i].bind );
		packet->writeInt32( m_ItemList[i].endTime );
		packet->writeInt64( m_ItemList[i].srcId );
	}
	int32_t NewOffet = packet->getWOffset();
	packet->setWOffset( OldOffet );
	packet->writeInt32( Count );
	packet->setWOffset( NewOffet );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);	
}

bool ChouJiang::AddItem( CJCfgList& CJCfgItem, int8_t IsBind )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	int32_t time = m_pPlayer->getNow();
	std::list<int32_t> ItemList;
	ItemList.clear();
	CJCfgList::iterator it = CJCfgItem.begin();
	for ( ; it != CJCfgItem.end(); ++it )
	{
		MemChrBag CJItem = {};
		CJItem.itemId		= it->ItemId;	
		CJItem.itemClass	= it->ItemClass;
		CJItem.itemCount	= it->ItemCount;
		CJItem.bind			= IsBind;
		CJItem.endTime		= 0;
		if ( it->ItemClass == IC_EQUIP )
		{
			MemEquip equip = EQUIP_MANAGER.CreateMemEquip( it->ItemId, m_pPlayer->getSid(), m_pPlayer->getCid(), it->Star );
			if ( equip.base <= 0 || equip.id <= 0 )
			{
				return false;
			}
			CJItem.srcId		= equip.id;	
			m_pPlayer->sendEquipInfo( equip );
		}

		for ( int32_t i = 0; i < MAX_ITEM_LIST; i++ )
		{
			if ( m_ItemList[i].itemCount > 0 && m_ItemList[i].itemId > 0 )
			{
				continue;
			}
			if ( it->IsGongGao == 1 )
			{
				GongGao( it->ItemClass, it->ItemId,CJItem.srcId );
			}

			AddChouJiangRecord( CJItem, time, it->IsRecord );
			m_ItemList[i] = CJItem;
			ItemList.push_back(i);
			break;
		}
	}
	SendChouJiangItemChang( ItemList );
	SendGetItem( ItemList );
	return true;
}

void ChouJiang::GongGao(  int8_t ItemClass, int32_t ItemId, int64_t SrcId )
{
	if(m_pPlayer == NULL)
	{
		return ;
	}
	Answer::NetPacket* pNetData = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_CHOU_JIANG_GONG_GAO);
	if (pNetData != NULL)
	{
		pNetData->writeUTF8( m_pPlayer->getName() );
		pNetData->writeInt64( m_pPlayer->getCid() );
		pNetData->writeInt8( ItemClass );
		pNetData->writeInt32( ItemId );
		pNetData->writeInt64( SrcId );
		pNetData->setSize(pNetData->getWOffset());
		GAME_SERVICE.broadcast( pNetData );
	}
}

void ChouJiang::GetItem( int32_t Slot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( Slot < 0 || Slot >= MAX_ITEM_LIST )
	{
		return;
	}
	if ( m_ItemList[Slot].itemCount <= 0 || m_ItemList[Slot].itemId <= 0 )
	{
		return;
	}
	int32_t nLayNum = CFG_DATA.getOverlay( m_ItemList[Slot].itemId, m_ItemList[Slot].itemClass );
	while( m_ItemList[Slot].itemCount > 0 )
	{
		if ( m_pPlayer->GetBag().GetbagFreeSize() <= 0 )
		{
			break;
		}
		
		if ( m_ItemList[Slot].itemCount > nLayNum )
		{
			MemChrBag BagItem = m_ItemList[Slot];
			BagItem.itemCount = nLayNum;
			MemChrBagVector item;
			item.push_back( BagItem );
			if ( !m_pPlayer->GetBag().AddItemsAndEggs( item, IACR_CHOU_JIANG ) )
			{
				return;
			}
			m_ItemList[Slot].itemCount -= nLayNum;
		}
		else
		{
			MemChrBagVector item;
			item.push_back(m_ItemList[Slot]);
			if ( !m_pPlayer->GetBag().AddItemsAndEggs( item, IACR_CHOU_JIANG ) )
			{
				return;
			}
			m_ItemList[Slot].itemCount = 0;
		}
	}
	if ( m_ItemList[Slot].itemCount <= 0 )
	{
		bzero(&m_ItemList[Slot], sizeof(m_ItemList[Slot]));
	}
	std::list<int32_t> TmpList;
	TmpList.push_back( Slot );
	SendChouJiangItemChang( TmpList );
}

int32_t	ChouJiang::GetFreeCount()
{
	int32_t FreeCount = 0;
	for ( int32_t i = 0; i < MAX_ITEM_LIST; i++ )
	{
		if ( m_ItemList[i].itemId <= 0 || m_ItemList[i].itemCount <= 0 )
		{
			FreeCount++;
		}
	}
	return FreeCount;
}

void ChouJiang::GetChouJiangStu( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if (!m_pPlayer->GetPlayerFunctionOpen().IsOpened(FT_CHOU_JIANG) )
	{
		return;
	}
	IconList.push_back(GetShowIconStu());
}

ShowIcon ChouJiang::GetShowIconStu()
{
	ShowIcon stu = {};
	stu.nId			= CHOU_JIANG_ICON;
	stu.nState		= AS_RUNNING;
	stu.nLeftTime	= -1;
	return stu;
}

void ChouJiang::SendHuoDongIcon()
{
	if (!m_pPlayer->GetPlayerFunctionOpen().IsOpened(FT_CHOU_JIANG) )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetShowIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8( stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast( packet );	
}