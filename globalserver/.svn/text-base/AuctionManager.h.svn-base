#ifndef __SOCIAL_AUCTION_MANAGER_H__
#define __SOCIAL_AUCTION_MANAGER_H__


#include "DataStructs.h"
#include "SocialPlayer.h"

#define PLAYER_AUCTION_ITEM_SIZE	18	// 18个道具栏，1个金币栏，1个魔石栏


class AuctionManager
{
typedef std::map<CharId_t, Int32List> PlayerAuctionMap;
public:
	AuctionManager();
	~AuctionManager();

public:
	bool Init();

public:
	int32_t				SellItem( CharId_t nCharId, const AuctionItem& item );			// 物品上架
	bool				CancelItem( CharId_t nCharId, int32_t nId );					// 物品下架
	bool				BuyItem( CharId_t nCharId, int32_t nId );						// 购买道具

	AuctionItem*		GetAuctionItem( int32_t nId );
	bool				IsPlayerItem( CharId_t nCharId, int32_t nId );

	void				SendItemList( SocialPlayer& player );
	void				SendSelfItems( SocialPlayer& player );
	void				SendRecords( SocialPlayer& player );

	bool				CanSell( CharId_t nCharId, int8_t nType );

private:
	bool				addPlayerItem( CharId_t nCharId, int32_t nId );
	bool				removePlayerItem( CharId_t nCharId, int32_t nId );

	void				sendMailItem( CharId_t nCharId, int32_t nMailId, const AuctionItem& item );
	void				sendMailCurrency( CharId_t nCharId, int32_t nMailId, int8_t nType, int32_t nCount );
	void				sendGameAddCurrency( CharId_t nCharId, int8_t nCurrency, int32_t nCount );

	void				saveItem( int32_t nId, const AuctionItem& item );
	void				saveBuy( int32_t nId, CharId_t nBuyer, int32_t nTime );
	void				delItem( int32_t nId );	// 下架直接删除，不留记录

	void				changePetOwner( int64_t nSrcId, CharId_t nOwnerId );
	void				changeEquipOwner( int64_t nSrcId, CharId_t nOwnerId );

private:
	AuctionItemMap		m_mAuctionItems;
	PlayerAuctionMap	m_mPlayerAuctionItems;
	AuctionItemList		m_lstRecords;
	int32_t				m_nNextId;
};
#define AUCTION_MANAGER Answer::Singleton<AuctionManager>::instance()

#endif	// __SOCIAL_AUCTION_MANAGER_H__
