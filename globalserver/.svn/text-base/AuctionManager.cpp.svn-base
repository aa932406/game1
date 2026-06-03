
#include "stdafx.h"
#include "AuctionManager.h"
#include "PlayerManager.h"
#include "SocialService.h"
#include "PetManager.h"

#define NETPACKET_AUCTION_ITEM_LIMIT	50
#define NETPACKET_AUCTION_RECORD_LIMIT	50

using namespace Answer;

AuctionManager::AuctionManager()
{
}

AuctionManager::~AuctionManager()
{

}

bool AuctionManager::Init()
{
	int32_t nLimitTime = DayTime::now() - 60*60*24*5;	// 保留5天的数据
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.* FROM `mem_chr_auction` As a LEFT JOIN `mem_character` As b ON a.seller = b.cid WHERE ( a.optime=0 OR a.optime>%d ) AND b.last_login_time>%d", nLimitTime, nLimitTime );
	MySqlQuery result = db.query(szSQL);

	m_nNextId = 0;
	int32_t nId = 0;
	AuctionItem item = {};
	while ( !result.eof() )
	{
		nId	= result.getIntValue("aid");
		item.nId	= result.getIntValue("id");
		item.nClass	= result.getIntValue("class");
		item.nCount	= result.getIntValue("count");
		item.nSrcId	= result.getInt64Value("srcid");
		item.nPrice = result.getIntValue("price");
		item.nSeller= result.getInt64Value("seller");
		item.nBuyer = result.getInt64Value("buyer");
		item.nTime	= result.getIntValue("optime");
		item.nEquipStar	= result.getIntValue("equipStar");

		if ( item.nBuyer > 0 )
		{
			m_lstRecords.push_back( item );
		}
		else
		{
			m_mAuctionItems[nId] = item;
			addPlayerItem( item.nSeller, nId );
		}

		if ( nId > m_nNextId )
		{
			m_nNextId = nId;
		}

		result.nextRow();
	}

	return true;
}

int32_t AuctionManager::SellItem( CharId_t nCharId, const AuctionItem& item )		// 物品上架
{
	m_mAuctionItems.insert( AuctionItemMap::value_type( ++m_nNextId, item ) );
	addPlayerItem( nCharId, m_nNextId );
	saveItem( m_nNextId, item );
	return m_nNextId;
}

bool AuctionManager::CancelItem( CharId_t nCharId, int32_t nId )					// 物品下架
{
	AuctionItemMap::iterator iter = m_mAuctionItems.find( nId );
	if ( iter == m_mAuctionItems.end() )
	{
		return false;
	}

	if ( !IsPlayerItem( nCharId, nId ) )
	{
		return false;
	}

	// 寄邮件给卖家
	const AuctionItem& item = iter->second;
	if ( item.nClass == IC_CURRENCY )
	{
		sendGameAddCurrency( nCharId, item.nId, item.nCount );
	}
	else
	{
		sendMailItem( nCharId, MI_AUCTION_DOWNLOAD, item );
	}

	// 下架直接从数据库中删除记录
	delItem( nId );

	// 删除拍卖数据
	m_mAuctionItems.erase( iter );
	removePlayerItem( nCharId, nId );
	return true;
}

bool AuctionManager::BuyItem( CharId_t nCharId, int32_t nId )					// 购买道具
{
	AuctionItemMap::iterator iter = m_mAuctionItems.find( nId );
	if ( iter == m_mAuctionItems.end() )
	{
		return false;
	}

	AuctionItem item = iter->second;
	CharId_t nSeller = item.nSeller;

	// 寄邮件给买家
	sendMailItem( nCharId, MI_AUCTION_BUY, item );
	if ( item.nClass == IC_PET )
	{
		changePetOwner( item.nSrcId, nCharId );
	}
	else if ( item.nClass == IC_EQUIP )
	{
		changeEquipOwner( item.nSrcId, nCharId );
	}

	// 寄邮件给卖家
	int32_t nCostPecent = 20;
	SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( item.nSeller );
	if ( pPlayer != NULL && pPlayer->IsInStall() )
	{
		nCostPecent = 10;
	}
	PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( item.nSeller );
	if ( NULL != pPlayerInfo )
	{
		if ( pPlayerInfo->nVipLevel > 1 )
		{
			nCostPecent /= 10;			//vip减90%的税
		}
	}
	int32_t nGetCount = item.nPrice - item.nPrice * nCostPecent / 100;	// 20%税
	int8_t nPayType = CURRENCY_GOLD_ID;
	if ( item.nClass == IC_CURRENCY && item.nId == CURRENCY_GOLD_ID )
	{
		nPayType = CURRENCY_MONEY_ID;
	}
	sendMailCurrency( item.nSeller, MI_AUCTION_SELL, nPayType, nGetCount );

	// 转入交易记录
	item.nBuyer = nCharId;
	item.nTime	= DayTime::now();
	m_lstRecords.push_front( item );

	// 存储交易信息
	saveBuy( nId, nCharId, item.nTime );

	// 删除拍卖数据
	removePlayerItem( nSeller, nId );
	m_mAuctionItems.erase( iter );
	return true;
}

AuctionItem* AuctionManager::GetAuctionItem( int32_t nId )
{
	AuctionItemMap::iterator iter = m_mAuctionItems.find( nId );
	if ( iter != m_mAuctionItems.end() )
	{
		return &(iter->second);
	}
	return NULL;
}

bool AuctionManager::CanSell( CharId_t nCharId, int8_t nType )
{
	PlayerAuctionMap::iterator findIter = m_mPlayerAuctionItems.find( nCharId );
	if ( findIter == m_mPlayerAuctionItems.end() )
	{
		return true;
	}

	int32_t nItemCount	= 0;
	bool haveSellMoney	= false;
	bool haveSellGold	= false;
	Int32List::iterator iter = findIter->second.begin();
	Int32List::iterator eiter = findIter->second.end();
	for ( ; iter != eiter; ++iter )
	{
		AuctionItem* pItem = GetAuctionItem( *iter );
		if ( NULL == pItem )
		{
			continue;
		}

		if ( pItem->nClass == IC_CURRENCY )
		{
			if ( pItem->nId == CURRENCY_MONEY_ID )
			{
				haveSellMoney = true;
			}
			else if ( pItem->nId == CURRENCY_GOLD_ID )
			{
				haveSellGold = true;
			}
		}
		else
		{
			++nItemCount;
		}
	}

	// 空间不足
	if ( nType == AIC_ITEM && nItemCount >= PLAYER_AUCTION_ITEM_SIZE )
	{
		return false;
	}
	// 已经上架铜钱
	if ( nType == AIC_MONEY && haveSellMoney )
	{
		return false;
	}
	// 已经上架魔石
	if ( nType == AIC_GOLD && haveSellGold )
	{
		return false;
	}
	return true;
}

bool AuctionManager::IsPlayerItem( CharId_t nCharId, int32_t nId )
{
	PlayerAuctionMap::iterator playerIter = m_mPlayerAuctionItems.find( nCharId );
	if ( playerIter == m_mPlayerAuctionItems.end() )
	{
		return false;
	}

	Int32List::iterator iter = playerIter->second.begin();
	Int32List::iterator eiter = playerIter->second.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == nId )
		{
			return true;
		}
	}
	return false;
}

bool AuctionManager::addPlayerItem( CharId_t nCharId, int32_t nId )
{
	PlayerAuctionMap::iterator playerIter = m_mPlayerAuctionItems.find( nCharId );
	if ( playerIter != m_mPlayerAuctionItems.end() )
	{
		playerIter->second.push_back( nId );
	}
	else
	{
		Int32List newList;
		newList.push_back( nId );
		m_mPlayerAuctionItems.insert( PlayerAuctionMap::value_type( nCharId, newList ) );
	}

	return true;
}

bool AuctionManager::removePlayerItem( CharId_t nCharId, int32_t nId )
{
	PlayerAuctionMap::iterator playerIter = m_mPlayerAuctionItems.find( nCharId );
	if ( playerIter == m_mPlayerAuctionItems.end() )
	{
		return false;
	}

	Int32List::iterator iter = playerIter->second.begin();
	Int32List::iterator eiter = playerIter->second.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == nId )
		{
			playerIter->second.erase( iter );
			return true;
		}
	}
	return false;
}

void AuctionManager::sendMailItem( CharId_t nCharId, int32_t nMailId, const AuctionItem& item )
{
	MemChrBag mailItem = {};
	mailItem.itemId		= item.nId;
	mailItem.itemClass	= item.nClass;
	mailItem.itemCount	= item.nCount;
	mailItem.srcId		= item.nSrcId;
	SOCIAL_SERVICE.SendSystemMail( nCharId, nMailId, mailItem );
}

void AuctionManager::sendMailCurrency( CharId_t nCharId, int32_t nMailId, int8_t nType, int32_t nCount )
{
	MemChrBag mailItem = {};
	mailItem.itemId		= nType;
	mailItem.itemClass  = IC_CURRENCY;
	mailItem.itemCount	= nCount;
	SOCIAL_SERVICE.SendSystemMail( nCharId, nMailId, mailItem );
}

void AuctionManager::sendGameAddCurrency( CharId_t nCharId, int8_t nCurrency, int32_t nCount )
{
	SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( nCharId );
	if ( pPlayer != NULL )
	{
		CURRENCY_TYPE currency = TranseCurrency( static_cast<CURRENCY_ITEM_ID>( nCurrency ) );
		if ( currency != CURRENCY_INVALID )
		{
			pPlayer->SendGameAddCurrency( currency, nCount );
		}
	}
}

void AuctionManager::SendItemList( SocialPlayer& player )
{
	AuctionItemMap::iterator iter = m_mAuctionItems.begin();
	AuctionItemMap::iterator eiter = m_mAuctionItems.end();
	do
	{
		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == packet)
		{
			return;
		}

		int8_t	nEnd	= 0;
		int32_t nCount	= 0;
		packet->writeInt8( nEnd );
		packet->writeInt32( nCount );
		for ( ; iter != eiter; ++iter )
		{
			const AuctionItem& item = iter->second;
			PlayerInfo* pSeller = PLAYER_MANAGER.GetPlayerInfo( item.nSeller );
			if ( NULL == pSeller )
			{
				continue;
			}

			packet->writeInt32( iter->first );
			packet->writeInt32( item.nId );
			packet->writeInt8( item.nClass );
			packet->writeInt32( item.nCount );
			packet->writeInt64( item.nSrcId );
			packet->writeInt32( item.nPrice );
			packet->writeInt64( item.nSeller );
			packet->writeUTF8( pSeller->strName );
			packet->writeInt32( item.nEquipStar );
			++nCount;
			if ( nCount >= NETPACKET_AUCTION_ITEM_LIMIT )
			{
				++iter;
				break;
			}
		}

		if ( iter == eiter )
		{
			nEnd = 1;
		}

		uint32_t oldwoffset = packet->getWOffset();
		packet->setWOffset( 0 );
		packet->writeInt8( nEnd );
		packet->writeInt32( nCount );
		packet->setWOffset( oldwoffset );

		packet->setType( PACK_DISPATCH );
		packet->setProc( SM_AUCTION_ITEM_LIST );
		packet->setSize( packet->getWOffset() );
		SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
	}
	while ( iter != eiter );
}

void AuctionManager::SendSelfItems( SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	int32_t nCount = 0;
	packet->writeInt32( nCount );

	PlayerAuctionMap::iterator findIter = m_mPlayerAuctionItems.find( player.getCid() );
	if ( findIter != m_mPlayerAuctionItems.end() )
	{
		Int32List::iterator iter = findIter->second.begin();
		Int32List::iterator eiter = findIter->second.end();
		for ( ; iter != eiter; ++iter )
		{
			int32_t nId = *iter;
			AuctionItem* pItem = GetAuctionItem( nId );
			if ( NULL == pItem )
			{
				continue;
			}

			packet->writeInt32( nId );
			packet->writeInt32( pItem->nId );
			packet->writeInt8( pItem->nClass );
			packet->writeInt32( pItem->nCount );
			packet->writeInt64( pItem->nSrcId );
			packet->writeInt32( pItem->nPrice );
			packet->writeInt32( pItem->nEquipStar );
			++nCount;
		}
	}

	uint32_t oldwoffset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( oldwoffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_AUCTION_SELF_ITEMS );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void AuctionManager::SendRecords( SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	int32_t nCount = 0;
	packet->writeInt32( nCount );
	AuctionItemList::iterator iter = m_lstRecords.begin();
	AuctionItemList::iterator eiter = m_lstRecords.end();
	for ( ; iter != eiter; ++iter )
	{
		AuctionItem& item = *iter;

		PlayerInfo* pInfo = NULL;
		if ( item.nSeller == player.getCid() )
		{
			pInfo =  PLAYER_MANAGER.GetPlayerInfo( item.nBuyer );
		}
		//else if ( item.nBuyer == player.getCid() )
		//{
		//	pInfo =  PLAYER_MANAGER.GetPlayerInfo( item.nSeller );
		//}
		else
		{
			continue;
		}

		if ( NULL == pInfo )
		{
			continue;
		}

		packet->writeInt32( item.nId );
		packet->writeInt8( item.nClass );
		packet->writeInt32( item.nCount );
		packet->writeInt32( item.nPrice );
		packet->writeInt64( item.nSeller );
		packet->writeInt64( item.nBuyer );
		packet->writeUTF8( pInfo->strName );
		packet->writeInt32( item.nTime );
		++nCount;
		if ( nCount >= NETPACKET_AUCTION_RECORD_LIMIT )
		{
			break;
		}
	}

	uint32_t oldwoffset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( oldwoffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_AUCTION_RECORD );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void AuctionManager::saveItem( int32_t nId, const AuctionItem& item )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `mem_chr_auction` (`aid`,`id`,`class`,`count`,`equipStar`,`srcid`,`price`,`seller`) VALUES (%d,%d,%d,%d,%d,%lld,%d,%lld) ON DUPLICATE KEY UPDATE `id`=%d,`class`=%d,`count`=%d,`equipStar`=%d,`srcid`=%lld,`price`=%d,`seller`=%lld",
		nId,
		item.nId,
		item.nClass,
		item.nCount,
		item.nEquipStar,
		item.nSrcId,
		item.nPrice,
		item.nSeller,
		item.nId,
		item.nClass,
		item.nCount,
		item.nEquipStar,
		item.nSrcId,
		item.nPrice,
		item.nSeller );
	db.excute(szSQL);
}

void AuctionManager::saveBuy( int32_t nId, CharId_t nBuyer, int32_t nTime )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_auction` SET `buyer` = %d, `optime`=%d WHERE aid = %d", nBuyer, nTime, nId );
	db.excute(szSQL);
}

void AuctionManager::delItem( int32_t nId )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "DELETE FROM `mem_chr_auction` WHERE aid = %d", nId );
	db.excute(szSQL);
}

void AuctionManager::changePetOwner( int64_t nSrcId, CharId_t nOwnerId )
{
	PET_MANAGER.ChangePetOwner( static_cast<PetId_t>( nSrcId ), nOwnerId );
}

void AuctionManager::changeEquipOwner( int64_t nSrcId, CharId_t nOwnerId )
{
	// 直接修改数据库
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_equip` SET `owner` = %lld WHERE id = %lld", nOwnerId, nSrcId );
	db.excute(szSQL);

	// 发送游戏服更新所有者
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if ( packet != NULL )
	{
		packet->writeInt8( IC_EQUIP );
		packet->writeInt64( nSrcId );
		packet->writeInt64( nOwnerId );

		packet->setType( PACK_PROC );
		packet->setProc( IM_SOCIAL_ALL_GAME_CHANGE_OWNER );
		packet->setSize( packet->getWOffset() );
		SOCIAL_SERVICE.sendPacket( packet );
	}
}
