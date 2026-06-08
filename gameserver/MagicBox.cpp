#include "stdafx.h"
#include "MagicBox.h"
#include "GameService.h"
#include "Bag.h"
#include "Player.h"
#include "Currency.h"
#include "Timer.h"
#include "EquipManager.h"
#include "OperateLimit.h"

using namespace Answer;

void CExtMagicBox::OnCleanUp()
{
	m_nCombiPoints = 0;
	m_nLastReviveTime = 0;
	m_lActiveScrolls.clear();
	m_lSuccessIds.clear();
}

void CExtMagicBox::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_nCombiPoints = dbData.m_MagicBoxDBData.nCombiPoints;
	m_nLastReviveTime = dbData.m_MagicBoxDBData.nLastReviveTime;
	loadString( m_lActiveScrolls, dbData.m_MagicBoxDBData.strActiveScrolls );
	loadString( m_lSuccessIds, dbData.m_MagicBoxDBData.strSuccessIds );
}

void CExtMagicBox::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_MagicBoxDBData.nCombiPoints = m_nCombiPoints;
	dbData.m_MagicBoxDBData.nLastReviveTime = m_nLastReviveTime;
	dbData.m_MagicBoxDBData.strActiveScrolls = saveString( m_lActiveScrolls );
	dbData.m_MagicBoxDBData.strSuccessIds = saveString( m_lSuccessIds );
}

void CExtMagicBox::OnUpdate( int64_t curTick )
{
	if ( !m_pPlayer )
	{
		return;
	}

	int32_t nNowTime = m_pPlayer->getNow();
	if ( m_nLastReviveTime )
	{
		int32_t nAddTimes = ( nNowTime - m_nLastReviveTime ) / 300;
		if ( nAddTimes > 0 )
		{
			m_nLastReviveTime += 300 * nAddTimes;
			int32_t nValue = nAddTimes * getPointsReviveValue();
			AddPoints( nValue );
		}
	}
	else
	{
		m_nCombiPoints = getMaxPoints();
		SendItemCombiPoint();
		m_nLastReviveTime = nNowTime;
	}
}

void CExtMagicBox::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_MAGIC_BOX_INFO );
	procList.push_back( CM_MAGIC_BOX_COMBI );
	procList.push_back( CM_MAGIC_BOX_ORNAMENT_COMBI );
	procList.push_back( CM_MAGIC_BOX_EQUIP_COMBI );
	procList.push_back( CM_MAGIC_BOX_DECOMPOSE );
}

int32_t CExtMagicBox::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( !inPacket )
	{
		return 10002;
	}

	switch ( nProcId )
	{
	case CM_MAGIC_BOX_INFO:				return onRequestInfo( inPacket );
	case CM_MAGIC_BOX_COMBI:			return onItemCombi( inPacket );
	case CM_MAGIC_BOX_ORNAMENT_COMBI:	return onOrnamentCombi( inPacket );
	case CM_MAGIC_BOX_EQUIP_COMBI:		return onEquipCombi( inPacket );
	case CM_MAGIC_BOX_DECOMPOSE:		return onItemDecompose( inPacket );
	default:							return 0;
	}
}

int32_t CExtMagicBox::onRequestInfo( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket )
	{
		return 10002;
	}
	SendMagicBoxInfo();
	return 0;
}

int32_t CExtMagicBox::onItemDecompose( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket )
	{
		return 10002;
	}

	int32_t Slot = inPacket->readInt32();
	MemChrBag slotData = m_pPlayer->GetBag().GetSlotData( Slot );
	if ( slotData.itemClass <= 0 || slotData.itemCount <= 0 || slotData.itemId <= 0 )
	{
		return 10002;
	}

	// Check bag space
	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		return 10002;
	}

	// Consume the item
	--slotData.itemCount;
	m_pPlayer->GetBag().SetSlotData( Slot, slotData, IDCR_BAG_USE, 0 );

	// Send reply
	uint16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), Proc, 0 );
	return 0;
}

int32_t CExtMagicBox::onItemCombi( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket )
	{
		return 10002;
	}

	int32_t nId = inPacket->readInt32();
	int32_t nTimes = inPacket->readInt32();

	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	int8_t bAutoBuy = inPacket->readInt8();

	if ( nTimes <= 0 )
	{
		return 10002;
	}

	const CfgMagicBoxCombi* pCfg = CFG_DATA.GetMagicBoxTable()->Get( nId );
	if ( !pCfg || pCfg->m_nCombiType != 0 )
	{
		return 10002;
	}

	if ( pCfg->m_bNeedActive > 0 && !isActive( nId ) )
	{
		return 10002;
	}

	if ( pCfg->m_nMoney < 0 || pCfg->m_vGiveItem.empty() )
	{
		return 10002;
	}

	MemChrBag giveItem = pCfg->m_vGiveItem.front();
	int64_t nCostMoney = (int64_t)pCfg->m_nMoney * nTimes;

	if ( m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < nCostMoney )
	{
		return 10002;
	}

	int32_t nCombiAllTimes = 0;
	int32_t nCombiBindTimes = 0;
	int64_t nNeedGold = 0;
	ItemDataList lCostItem;

	for ( ItemDataList::const_iterator it = pCfg->m_lCostItem.begin(); it != pCfg->m_lCostItem.end(); ++it )
	{
		if ( it->m_nCount <= 0 )
		{
			continue;
		}

		int32_t nHaveBindCount = m_pPlayer->GetBag().HaveItemCount( *it, 1, 0 );
		int32_t nHaveUnBindCount = m_pPlayer->GetBag().HaveItemCount( *it, 0, 0 );
		int32_t nTotalHave = nHaveBindCount + nHaveUnBindCount;

		if ( nTimes * it->m_nCount <= nTotalHave )
		{
			nCombiAllTimes = nTotalHave / it->m_nCount;
			if ( nCombiAllTimes > nTimes )
			{
				nCombiAllTimes = nTimes;
			}
			ItemData costItem( it->m_nId, it->m_nClass, nCombiAllTimes * it->m_nCount );
			lCostItem.push_back( costItem );
		}
		else
		{
			if ( bAutoBuy != 1 )
			{
				return 10002;
			}
			int32_t nDiffCount = nTimes * it->m_nCount - nTotalHave;
			CfgGameShop* pShop = CFG_DATA.GetGameShopItem( it->m_nClass, it->m_nId );
			if ( !pShop )
			{
				return 10002;
			}
			nNeedGold += (int64_t)nDiffCount * pShop->Price;
			ItemData costItem( it->m_nId, it->m_nClass, nTotalHave );
			lCostItem.push_back( costItem );
			nCombiAllTimes = nTimes;
		}

		int32_t nBindTimes = nHaveBindCount / it->m_nCount;
		if ( nBindTimes > nCombiBindTimes )
		{
			nCombiBindTimes = nBindTimes;
		}
		if ( nCombiAllTimes > nBindTimes )
		{
			if ( nHaveBindCount % it->m_nCount )
			{
				++nCombiBindTimes;
			}
		}
	}

	if ( nNeedGold > 0 )
	{
		int64_t HaveGold = m_pPlayer->GetCurrency( CURRENCY_GOLD );
		if ( HaveGold < nNeedGold )
		{
			return 10002;
		}
	}

	if ( nCombiAllTimes <= 0 )
	{
		return 10002;
	}

	if ( nCombiBindTimes > nCombiAllTimes )
	{
		nCombiBindTimes = nCombiAllTimes;
	}

	int32_t nUnBindTimes = 0;
	int32_t nBindTimes = 0;

	if ( pCfg->m_nTotalRate > 0 )
	{
		for ( int32_t i = 0; i < nCombiAllTimes - nCombiBindTimes; ++i )
		{
			if ( RANDOM.generate( 1, pCfg->m_nTotalRate ) <= pCfg->m_nRate )
			{
				++nUnBindTimes;
			}
		}
		for ( int32_t i = 0; i < nCombiBindTimes; ++i )
		{
			if ( RANDOM.generate( 1, pCfg->m_nTotalRate ) <= pCfg->m_nRate )
			{
				++nBindTimes;
			}
		}
	}

	int32_t nSuccessTimes = nBindTimes + nUnBindTimes;
	int32_t nFailTimes = nCombiAllTimes - nSuccessTimes;
	int32_t nGiveBind = nBindTimes * giveItem.itemCount;
	int32_t nGiveUnBind = nUnBindTimes * giveItem.itemCount;

	MemChrBagVector vAddItem;

	if ( nGiveBind > 0 )
	{
		MemChrBag bindItem = giveItem;
		bindItem.itemCount = nGiveBind;
		bindItem.bind = 1;
		vAddItem.push_back( bindItem );
	}
	if ( nGiveUnBind > 0 )
	{
		MemChrBag unBindItem = giveItem;
		unBindItem.itemCount = nGiveUnBind;
		unBindItem.bind = 0;
		vAddItem.push_back( unBindItem );
	}

	if ( nFailTimes > 0 )
	{
		for ( size_t i = 0; i < pCfg->m_vBackItem.size(); ++i )
		{
			MemChrBag backItem = pCfg->m_vBackItem[i];
			backItem.itemCount = nFailTimes * pCfg->m_vBackItem[i].itemCount;
			vAddItem.push_back( backItem );
		}
	}

	int32_t nNeedBagSlot = 0;
	for ( size_t i = 0; i < vAddItem.size(); ++i )
	{
		int32_t nOverlay = CFG_DATA.getOverlay( vAddItem[i].itemId, vAddItem[i].itemClass );
		if ( nOverlay <= 0 )
		{
			return 10002;
		}
		nNeedBagSlot += vAddItem[i].itemCount / nOverlay;
		if ( vAddItem[i].itemCount % nOverlay )
		{
			++nNeedBagSlot;
		}
	}

	if ( m_pPlayer->GetBag().GetFreeSlotCount() < nNeedBagSlot )
	{
		m_pPlayer->TiShiInfo( 2048, 0 );
		return 10002;
	}

	if ( !m_pPlayer->GetBag().RemoveCombiItem( lCostItem, IDCR_BAG_USE ) )
	{
		return 10002;
	}

	if ( nNeedGold > 0 )
	{
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nNeedGold, GCR_ITEM_COMBI_AUTO_BUY, nId ) )
		{
			return 10002;
		}
	}

	if ( nCostMoney > 0 )
	{
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( nCostMoney, MCR_COMBI_ITEM, 0 ) )
		{
			return 10002;
		}
	}

	if ( !m_pPlayer->GetBag().AddItem( vAddItem, IACR_NONE ) )
	{
		return 10002;
	}

	if ( pCfg->m_bBroadcast > 0 && nSuccessTimes > 0 )
	{
		broadcastItemCombi( giveItem.itemId, giveItem.itemClass );
	}

	if ( nSuccessTimes > 0 )
	{
		bool bFound = false;
		for ( Int32List::const_iterator it = m_lSuccessIds.begin(); it != m_lSuccessIds.end(); ++it )
		{
			if ( *it == nId )
			{
				bFound = true;
				break;
			}
		}
		if ( !bFound )
		{
			m_lSuccessIds.push_back( nId );
		}
	}

	sendItemCombiResult( nId, nSuccessTimes, nFailTimes );
	return 0;
}

int32_t CExtMagicBox::onOrnamentCombi( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket )
	{
		return 10002;
	}

	int32_t nId = inPacket->readInt32();
	int32_t nSpecialCost = inPacket->readInt32();
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	const CfgMagicBoxCombi* pCfg = CFG_DATA.GetMagicBoxTable()->Get( nId );
	if ( !pCfg )
	{
		return 10002;
	}

	if ( pCfg->m_nCombiType != 1 && pCfg->m_nCombiType != 2 )
	{
		return 10002;
	}

	if ( nSpecialCost < 0 || (size_t)nSpecialCost >= pCfg->m_vProbability.size() )
	{
		return 10002;
	}

	if ( pCfg->m_nMoney < 0 || pCfg->m_nCostPoint < 0 )
	{
		return 10002;
	}

	if ( m_nCombiPoints < pCfg->m_nCostPoint )
	{
		return 10002;
	}

	if ( m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < pCfg->m_nMoney )
	{
		return 10002;
	}

	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		return 10002;
	}

	ItemDataList lCostItem;
	for ( ItemDataList::const_iterator it = pCfg->m_lCostItem.begin(); it != pCfg->m_lCostItem.end(); ++it )
	{
		lCostItem.push_back( *it );
	}

	if ( nSpecialCost > 0 && (size_t)( nSpecialCost - 1 ) < pCfg->m_vSpecialItems.size() )
	{
		const MemChrBag& specItem = pCfg->m_vSpecialItems[nSpecialCost - 1];
		ItemData specialData( specItem.itemId, specItem.itemClass, specItem.itemCount );
		lCostItem.push_back( specialData );
	}

	const Int32Vector& vProb = pCfg->m_vProbability[nSpecialCost];
	int32_t nIndex = randomIndex( vProb );
	if ( nIndex < 0 || (size_t)nIndex >= pCfg->m_vGiveItem.size() )
	{
		return 10002;
	}

	int32_t nBindCount = 0;
	int32_t nUnBindCount = 0;
	if ( !m_pPlayer->GetBag().RemoveItem( vSlot, lCostItem, IDCR_BAG_USE ) )
	{
		return 10002;
	}

	if ( nBindCount > 0 )
	{
		// Bind flag tracking
	}

	MemChrBag giveItem = pCfg->m_vGiveItem[nIndex];

	if ( pCfg->m_nCostPoint > 0 )
	{
		m_nCombiPoints -= pCfg->m_nCostPoint;
	}

	if ( pCfg->m_nMoney > 0 )
	{
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfg->m_nMoney, MCR_COMBI_ITEM, 0 ) )
		{
			return 10002;
		}
	}

	if ( !m_pPlayer->GetBag().AddItem( giveItem, IACR_NONE ) )
	{
		return 10002;
	}

	SendItemCombiPoint();
	sendItemCombiResult( nId, 1, 0 );
	return 0;
}

int32_t CExtMagicBox::onEquipCombi( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket )
	{
		return 10002;
	}

	int32_t nId = inPacket->readInt32();
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );

	const CfgMagicBoxCombi* pCfg = CFG_DATA.GetMagicBoxTable()->Get( nId );
	if ( !pCfg || pCfg->m_nCombiType != 3 )
	{
		return 10002;
	}

	if ( pCfg->m_nMoney < 0 || pCfg->m_nCostPoint < 0 )
	{
		return 10002;
	}

	if ( pCfg->m_vGiveItem.empty() )
	{
		return 10002;
	}

	MemChrBag giveItem = pCfg->m_vGiveItem.front();
	if ( giveItem.itemClass != 2 )
	{
		return 10002;
	}

	if ( m_nCombiPoints < pCfg->m_nCostPoint )
	{
		return 10002;
	}

	if ( pCfg->m_lCostItem.empty() )
	{
		return 10002;
	}

	if ( m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < pCfg->m_nMoney )
	{
		return 10002;
	}

	ItemDataList lCostItem = pCfg->m_lCostItem;

	for ( size_t i = 0; i < vSlot.size(); ++i )
	{
		int32_t nBagSlot = vSlot[i];
		MemChrBag bagSlot = m_pPlayer->GetBag().GetSlotData( nBagSlot );

		if ( bagSlot.itemId <= 0 || bagSlot.itemClass != 2 )
		{
			return 10002;
		}

		MemEquip equip = EQUIP_MANAGER.GetMemEquip( bagSlot.srcId );
		if ( equip.base != bagSlot.itemId )
		{
			return 10002;
		}

		for ( ItemDataList::iterator it = lCostItem.begin(); it != lCostItem.end(); )
		{
			if ( it->m_nId == bagSlot.itemId )
			{
				--it->m_nCount;
				if ( it->m_nCount <= 0 )
				{
					it = lCostItem.erase( it );
				}
				break;
			}
			else
			{
				++it;
			}
		}
	}

	if ( !lCostItem.empty() )
	{
		return 10002;
	}

	if ( pCfg->m_nMoney > 0 )
	{
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfg->m_nMoney, MCR_COMBI_ITEM, 0 ) )
		{
			return 10002;
		}
	}

	for ( size_t i = 0; i < vSlot.size(); ++i )
	{
		m_pPlayer->GetBag().CleanSlot( vSlot[i], IDCR_BAG_USE );
	}

	if ( !m_pPlayer->GetBag().AddItem( giveItem, IACR_NONE ) )
	{
		return 10002;
	}

	if ( pCfg->m_nCostPoint > 0 )
	{
		m_nCombiPoints -= pCfg->m_nCostPoint;
		SendItemCombiPoint();
	}

	if ( pCfg->m_bBroadcast > 0 )
	{
		broadcastItemCombi( giveItem.itemId, giveItem.itemClass );
	}

	sendItemCombiResult( nId, 1, 0 );
	return 0;
}

int32_t CExtMagicBox::randomIndex( const Int32Vector& vParam )
{
	int32_t nTotal = 0;
	int32_t nSize = (int32_t)vParam.size();
	for ( int32_t i = 0; i < nSize; ++i )
	{
		nTotal += vParam[i];
	}
	if ( nTotal <= 0 )
	{
		return 0;
	}

	int32_t nRand = RANDOM.generate( 1, nTotal );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		if ( vParam[i] >= nRand )
		{
			return i;
		}
		nRand -= vParam[i];
	}
	return 0;
}

bool CExtMagicBox::AddPoints( int32_t nValue )
{
	int32_t nMaxPoints = getMaxPoints();
	if ( m_nCombiPoints >= nMaxPoints )
	{
		return false;
	}

	m_nCombiPoints += nValue;
	if ( m_nCombiPoints > nMaxPoints )
	{
		m_nCombiPoints = nMaxPoints;
	}
	SendItemCombiPoint();
	return true;
}

bool CExtMagicBox::ActiveScroll( int32_t nId )
{
	if ( isActive( nId ) )
	{
		return false;
	}
	m_lActiveScrolls.push_back( nId );
	return true;
}

bool CExtMagicBox::isActive( int32_t nId ) const
{
	for ( Int32List::const_iterator it = m_lActiveScrolls.begin(); it != m_lActiveScrolls.end(); ++it )
	{
		if ( *it == nId )
		{
			return true;
		}
	}
	return false;
}

void CExtMagicBox::SendMagicBoxInfo()
{
	if ( !m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_MAGIC_BOX_INFO );
	if ( !packet )
	{
		return;
	}

	packet->writeInt32( (int32_t)m_lActiveScrolls.size() );
	for ( Int32List::const_iterator it = m_lActiveScrolls.begin(); it != m_lActiveScrolls.end(); ++it )
	{
		packet->writeInt32( *it );
	}

	packet->writeInt32( (int32_t)m_lSuccessIds.size() );
	for ( Int32List::const_iterator it = m_lSuccessIds.begin(); it != m_lSuccessIds.end(); ++it )
	{
		packet->writeInt32( *it );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtMagicBox::SendItemCombiPoint()
{
	if ( !m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_MAGIC_BOX_COMBI_POINT );
	if ( !packet )
	{
		return;
	}

	packet->writeInt32( m_nCombiPoints );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtMagicBox::sendItemCombiResult( int32_t nId, int32_t nSuccessTimes, int32_t nFailTimes )
{
	if ( !m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_MAGIC_BOX_COMBI_RESULT );
	if ( !packet )
	{
		return;
	}

	packet->writeInt32( nId );
	packet->writeInt32( nSuccessTimes );
	packet->writeInt32( nFailTimes );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtMagicBox::broadcastItemCombi( int32_t ItemId, int8_t ItemClass )
{
	if ( !m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), PACK_DISPATCH, SM_ITEM_COMBINE_BROADCAST );
	if ( !packet )
	{
		return;
	}

	packet->writeInt32( 121 );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt32( ItemId );
	packet->writeInt8( ItemClass );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.broadcast( m_pPlayer->getConnId(), packet );
}

std::string CExtMagicBox::saveString( const Int32List& lst )
{
	if ( lst.empty() )
	{
		return "";
	}

	std::stringstream ss;
	bool bFirst = true;
	for ( Int32List::const_iterator it = lst.begin(); it != lst.end(); ++it )
	{
		if ( !bFirst )
		{
			ss << ",";
		}
		ss << *it;
		bFirst = false;
	}
	return ss.str();
}

void CExtMagicBox::loadString( Int32List& lst, const std::string& str )
{
	lst.clear();
	if ( str.empty() )
	{
		return;
	}

	StringVector v = Answer::StringUtility::split( str, "," );
	for ( size_t i = 0; i < v.size(); ++i )
	{
		int32_t nVal = atoi( v[i].c_str() );
		lst.push_back( nVal );
	}
}
