#include "stdafx.h"
#include "RongHe.h"
#include "Player.h"
#include "CfgData.h"
#include "Currency.h"
#include "GameService.h"
#include "GuiGuDaoRen.h"

CRongHe::CRongHe()
{
}

CRongHe::~CRongHe()
{
}

void CRongHe::OnCleanUp()
{
	m_RongLianInfoMap.clear();
}

void CRongHe::OnLoadFromDB( const PlayerDBData& dbData )
{
	ParesRongHeEquipString( dbData.m_strRongHeEquipData );
}

void CRongHe::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_strRongHeEquipData = GetRongHeEquipString();
}

void CRongHe::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 944 );
	procList.push_back( 945 );
	procList.push_back( 946 );
	procList.push_back( 947 );
	procList.push_back( 948 );
}

int32_t CRongHe::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return 10002;
	}

	switch ( nProcId )
	{
	case 944:	return OnRongLian( inPacket );
	case 945:	return OnEquipRongLian( inPacket );
	case 946:	return OnDismantlingEquip( inPacket );
	case 947:	return OnItemRecovery( inPacket );
	case 948:	return OnOneKeyItemRecovery( inPacket );
	default:
		return 10002;
	}
}

int32_t CRongHe::OnRongLian( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	int32_t nId = inPacket->readInt32();
	const RongHeCfg* pCfg = CFG_DATA.GetRongHeCfg( nId );
	if ( NULL == pCfg )
	{
		return 2;
	}

	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		m_pPlayer->TiShiInfo( 2048, 0 );
		return 10002;
	}

	RongHeItem resultItem;
	resultItem.CleanUp();

	// Weighted random selection (with GuiGuDaoRen rate correction)
	bool bUseRate2 = ( GUI_GU_DAO_REN.GetRongHeRate() != 0 );
	int32_t nMaxRate = bUseRate2 ? pCfg->nMaxRate2 : pCfg->nMaxRate;
	int32_t nRand = RANDOM.generate( 1, nMaxRate );
	for ( RongHeItemList::const_iterator it = pCfg->lRongHeItemList.begin(); it != pCfg->lRongHeItemList.end(); ++it )
	{
		int32_t nRate = bUseRate2 ? it->nRate2 : it->nRate;
		if ( nRand <= nRate )
		{
			resultItem = *it;
			break;
		}
		nRand -= nRate;
	}

	if ( resultItem.item.itemId <= 0 )
	{
		return 10002;
	}

	// Remove cost item
	ItemData costItem = pCfg->nCostItem;
	if ( !m_pPlayer->GetBag().RemoveItem( costItem, IDCR_RONG_HE_COST ) )
	{
		return 10002;
	}

	// Add result item
	if ( !m_pPlayer->GetBag().AddItem( resultItem.item, IACR_AUCTION_BUY ) )
	{
		return 10002;
	}

	m_pPlayer->GetBag().ForceSendDirty();
	SendRongHeResult( nId, resultItem.nSuccess, resultItem.item );

	// Record fusion result if needed
	if ( resultItem.nRecord > 0 )
	{
		RongHeRecord record;
		record.nCid = m_pPlayer->getCid();
		record.strName = m_pPlayer->getName();
		record.nCostId = costItem.m_nId;
		record.nGiveId = resultItem.item.itemId;
		record.nSuccess = resultItem.nSuccess;
		record.nTime = m_pPlayer->getNow();
		GUI_GU_DAO_REN.AddRongHeRecord( &record );
	}

	// Broadcast if needed
	if ( resultItem.nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet )
		{
			packet->writeInt32( resultItem.nGongGaoId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( costItem.m_nId );
			packet->writeInt32( resultItem.item.itemId );
			packet->writeInt8( resultItem.item.itemClass );
			packet->writeInt32( resultItem.item.itemCount );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	// Track fusion statistics
	{
		int32_t nCostValue = 0;
		int32_t nGetValue = 0;
		const CfgItem* pCostCfg = CFG_DATA.getItem( costItem.m_nId );
		const CfgItem* pResultCfg = CFG_DATA.getItem( resultItem.item.itemId );
		if ( pCostCfg != NULL && pCostCfg->RongHeReceovery.nParam2 > 0 )
		{
			nCostValue = pCostCfg->RongHeReceovery.nParam2;
		}
		if ( pResultCfg != NULL && pResultCfg->RongHeReceovery.nParam2 > 0 )
		{
			nGetValue = pResultCfg->RongHeReceovery.nParam2;
		}
		GUI_GU_DAO_REN.AddRongHeCount( nCostValue, nGetValue );
	}

	// Reply success
	Answer::NetPacket* reply = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, inPacket->getProc() );
	if ( reply )
	{
		reply->writeInt64( resultItem.nSuccess );
		reply->setSize( reply->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), reply );
	}
	return 0;
}

int32_t CRongHe::OnEquipRongLian( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	int32_t nSlot = inPacket->readInt32();

	// Check if already in fusion map
	if ( m_RongLianInfoMap.find( nSlot ) != m_RongLianInfoMap.end() )
	{
		return 10002;
	}

	// Get bag slot data
	MemChrBag BagItem = m_pPlayer->GetBag().GetSlotData( nSlot );
	if ( BagItem.itemId <= 0 || BagItem.itemCount <= 0 )
	{
		return 10002;
	}

	// Must be an equip
	if ( BagItem.itemClass != 2 )
	{
		return 10002;
	}

	// Check if equip can be fused
	const CfgEquip* pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( BagItem.itemId );
	if ( NULL == pCfgEquip || pCfgEquip->m_CanRongHe <= 0 )
	{
		return 10002;
	}

	// Get fusion config
	const EquipRongHe* pEquipRongHe = CFG_DATA.GetEquipRongHe( BagItem.itemId );
	if ( NULL == pEquipRongHe )
	{
		return 10002;
	}

	// Check max equip count
	if ( (int32_t)m_RongLianInfoMap.size() >= pEquipRongHe->nMaxEquip )
	{
		return 10002;
	}

	// Add to fusion map
	RongLianInfo info;
	info.nItemId = pEquipRongHe->nItemId;
	info.nCount = 1;
	info.nEquipId = BagItem.itemId;
	m_RongLianInfoMap[nSlot] = info;

	// Remove equip from bag
	m_pPlayer->GetBag().CleanSlot( nSlot, IDCR_EQUIP_RONG_HE );

	// Add result item
	MemChrBag reward;
	reward.itemId = pEquipRongHe->nItemId;
	reward.itemClass = 1;
	reward.itemCount = 1;
	m_pPlayer->GetBag().AddItem( reward, IACR_AUCTION_BUY );

	m_pPlayer->GetBag().ForceSendDirty();
	m_pPlayer->RecalcAttr();
	SendOneRongHeInfo( nSlot );

	Answer::NetPacket* reply = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, inPacket->getProc() );
	if ( reply )
	{
		reply->writeInt32( nSlot );
		reply->setSize( reply->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), reply );
	}
	return 0;
}

int32_t CRongHe::OnDismantlingEquip( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	int32_t nSlot = inPacket->readInt32();

	RongLianInfoMap::iterator it = m_RongLianInfoMap.find( nSlot );
	if ( it == m_RongLianInfoMap.end() )
	{
		return 10002;
	}

	// Check free slots
	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		m_pPlayer->TiShiInfo( 2048, 0 );
		return 10002;
	}

	RongLianInfo& info = it->second;
	if ( info.nEquipId > 0 )
	{
		MemChrBag stu;
		stu.itemId = info.nEquipId;
		stu.itemClass = 2;
		stu.itemCount = 1;
		if ( m_pPlayer->GetBag().AddItem( stu, IACR_AUCTION_BUY ) )
		{
			m_RongLianInfoMap.erase( it );
			m_pPlayer->RecalcAttr();
			GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nSlot );
			return 0;
		}
	}

	m_RongLianInfoMap.erase( it );
	return 10002;
}

int32_t CRongHe::OnItemRecovery( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	int32_t nBagslot = inPacket->readInt32();
	MemChrBag BagItem = m_pPlayer->GetBag().GetSlotData( nBagslot );
	if ( BagItem.itemId <= 0 || BagItem.itemCount <= 0 )
	{
		return 10002;
	}

	CfgItem* pItem = CFG_DATA.getItem( BagItem.itemId );
	if ( NULL == pItem )
	{
		return 10002;
	}

	if ( pItem->RongHeReceovery.nParam1 < 0 || pItem->RongHeReceovery.nParam2 <= 0 )
	{
		return 10002;
	}

	// Validate currency type
	if ( pItem->RongHeReceovery.nParam1 < 0 || pItem->RongHeReceovery.nParam1 >= CURRENCY_TYPE_COUNT )
	{
		return 10002;
	}

	// Give currency to player
	m_pPlayer->AddCurrency( (CURRENCY_TYPE)pItem->RongHeReceovery.nParam1, pItem->RongHeReceovery.nParam2, GCR_RONG_HE_HUI_SHOU );

	// Decrease item count from the specific slot
	BagItem.itemCount -= 1;
	if ( BagItem.itemCount > 0 )
	{
		m_pPlayer->GetBag().SetSlotData( nBagslot, BagItem, IDCR_RONG_HE_GET );
	}
	else
	{
		m_pPlayer->GetBag().CleanSlot( nBagslot, IDCR_RONG_HE_GET );
	}

	m_pPlayer->GetBag().ForceSendDirty();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), pItem->RongHeReceovery.nParam2 );
	return 0;
}

int32_t CRongHe::OnOneKeyItemRecovery( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	std::map<CURRENCY_TYPE, int64_t> CurrMap;
	Int32Vector vRemoveSlot;

	// Query bag info for items
	m_pPlayer->queryBagInfo();

	// Iterate all bag slots
	int32_t nBagSize = m_pPlayer->GetBag().GetBagSize();
	for ( int32_t i = 0; i < nBagSize; ++i )
	{
		MemChrBag BagItem = m_pPlayer->GetBag().GetSlotData( i );
		if ( BagItem.itemId <= 0 || BagItem.itemCount <= 0 )
		{
			continue;
		}

		CfgItem* pItem = CFG_DATA.getItem( BagItem.itemId );
		if ( NULL == pItem )
		{
			continue;
		}

		if ( pItem->RongHeReceovery.nParam1 < 0 || pItem->RongHeReceovery.nParam1 >= CURRENCY_TYPE_COUNT || pItem->RongHeReceovery.nParam2 <= 0 )
		{
			continue;
		}

		CURRENCY_TYPE nType = (CURRENCY_TYPE)pItem->RongHeReceovery.nParam1;
		int64_t nValue = (int64_t)pItem->RongHeReceovery.nParam2 * BagItem.itemCount;
		CurrMap[nType] += nValue;
		vRemoveSlot.push_back( i );
	}

	if ( vRemoveSlot.empty() )
	{
		return 10002;
	}

	// Remove all items first
	for ( size_t i = 0; i < vRemoveSlot.size(); ++i )
	{
		m_pPlayer->GetBag().CleanSlot( vRemoveSlot[i], IDCT_RONG_HE_BACK );
	}

	// Add currency rewards
	for ( std::map<CURRENCY_TYPE, int64_t>::iterator it = CurrMap.begin(); it != CurrMap.end(); ++it )
	{
		m_pPlayer->AddCurrency( it->first, it->second, GCR_RONG_HE_HUI_SHOU );
	}

	m_pPlayer->GetBag().ForceSendDirty();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), (int32_t)vRemoveSlot.size() );
	return 0;
}

void CRongHe::SendAllRongHeInfo()
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 11716 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( (int32_t)m_RongLianInfoMap.size() );
	for ( RongLianInfoMap::const_iterator it = m_RongLianInfoMap.begin(); it != m_RongLianInfoMap.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.nItemId );
		packet->writeInt32( it->second.nCount );
		packet->writeInt32( it->second.nEquipId );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CRongHe::SendOneRongHeInfo( int32_t nSlot )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 11717 );
	if ( NULL == packet )
	{
		return;
	}

	RongLianInfoMap::const_iterator it = m_RongLianInfoMap.find( nSlot );
	if ( it != m_RongLianInfoMap.end() )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.nItemId );
		packet->writeInt32( it->second.nCount );
		packet->writeInt32( it->second.nEquipId );
	}
	else
	{
		packet->writeInt32( nSlot );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CRongHe::SendRongHeResult( int32_t nId, int32_t nSuccess, const MemChrBag& stu )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 11718 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nId );
	packet->writeInt32( nSuccess );
	packet->writeInt32( stu.itemId );
	packet->writeInt8( stu.itemClass );
	packet->writeInt32( stu.itemCount );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

std::string CRongHe::GetRongHeEquipString()
{
	std::stringstream ss;
	for ( RongLianInfoMap::const_iterator it = m_RongLianInfoMap.begin(); it != m_RongLianInfoMap.end(); ++it )
	{
		if ( it != m_RongLianInfoMap.begin() )
		{
			ss << "\r\n";
		}
		ss << it->first << ":|" << it->second.nItemId << ":|" << it->second.nCount << ":|" << it->second.nEquipId;
	}
	return ss.str();
}

void CRongHe::ParesRongHeEquipString( const std::string& strData )
{
	m_RongLianInfoMap.clear();
	if ( strData.empty() )
	{
		return;
	}

	StringVector vStr = Answer::StringUtility::split( strData, "\r\n" );
	for ( size_t i = 0; i < vStr.size(); ++i )
	{
		StringVector tv = Answer::StringUtility::split( vStr[i], ":|" );
		if ( tv.size() == 4 )
		{
			int32_t nType = atoi( tv[0].c_str() );
			if ( (uint32_t)nType <= 9 )
			{
				RongLianInfo& info = m_RongLianInfoMap[nType];
				info.nItemId = atoi( tv[1].c_str() );
				info.nCount = atoi( tv[2].c_str() );
				info.nEquipId = atoi( tv[3].c_str() );
			}
		}
	}
}
