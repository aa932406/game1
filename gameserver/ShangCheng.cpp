#include "ShangCheng.h"
#include "Player.h"
#include "GameService.h"

CShangCheng::CShangCheng()
{
	OnCleanUp();
}

CShangCheng::~CShangCheng()
{

}

void CShangCheng::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_LiMitMap = dbData.m_ShangChengData.m_LiMitMap;
}

void CShangCheng::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_ShangChengData.m_LiMitMap = m_LiMitMap;
}

void CShangCheng::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_SHANG_CHENG_LIMIT_INFO);
	procList.push_back( CM_BUY_SHANG_CHENG_ITEM	);
	procList.push_back( IM_SOCIAL_GAME_BUY_LIMIT_ITEM );
}

int32_t CShangCheng::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch ( nProcId )
	{
	case CM_ASK_SHANG_CHENG_LIMIT_INFO:		return 	 OnAskLimitInfo( inPacket );
	case CM_BUY_SHANG_CHENG_ITEM:			return   OnBuyShopItem( inPacket );
	case IM_SOCIAL_GAME_BUY_LIMIT_ITEM:		return	 OnBuyGameLimitItem( inPacket );
	default:
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

void CShangCheng::OnCleanUp()
{
	m_LiMitMap.clear();
}

void CShangCheng::OnDaySwitch( int32_t nDiffDays )
{
	m_LiMitMap.clear();
	SendLimitInfo();
}

int32_t CShangCheng::BuyShopItem( int32_t ShopId, int32_t ItemCount, bool AddBag )
{
	CfgGameShop* pShangCheng = CFG_DATA.GetGameShop( ShopId );
	if ( NULL == pShangCheng )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pShangCheng->VipLevelLimit > m_pPlayer->GetPlayerVip().GetVipLevel() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pShangCheng->LimitType == LIMIT_TYPE_SERVER )
	{
		SendSocialBuyLimitItem( ShopId, ItemCount );
		return ERR_SYETEM_ERR;
	}

	if ( IsLimited( pShangCheng, ItemCount ) )	//判断个数和时间限制
	{
		return ERR_SYETEM_ERR;
	}

	if ( pShangCheng->Price <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nLayNum = CFG_DATA.getOverlay( pShangCheng->ItemId, pShangCheng->ItemClass );

	if ( ItemCount > nLayNum )
	{
		return ERR_SYETEM_ERR;
	}

	if ( AddBag )
	{
		if ( pShangCheng->ItemClass == IC_PET_EGG )
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
	}

	if ( pShangCheng->ShopType == BANG_SHI_SHANG_CHENG_TYPE )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_CASH ) < pShangCheng->Price * ItemCount )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_CASH , pShangCheng->Price * ItemCount, GCC_BUY_SHANG_CHENG_ITEM, pShangCheng->ShopId ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pShangCheng->Price * ItemCount )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD , pShangCheng->Price * ItemCount, GCR_BUY_SHANG_CHENG_ITEM, pShangCheng->ShopId ) )
		{
			return ERR_SYETEM_ERR;
		}
	}

	if ( AddBag )
	{
		MemChrBag Item = {};
		Item.itemClass		= pShangCheng->ItemClass;
		Item.itemCount		= ItemCount;
		Item.bind			= pShangCheng->ItemBind;
		Item.itemId			= pShangCheng->ItemId;


		if ( pShangCheng->ItemClass == IC_PET_EGG )
		{
			std::list<int32_t> EggIdList;
			EggIdList.push_back( pShangCheng->ItemId );
			m_pPlayer->GetCharPet().AddEggs( EggIdList );
		}
		else if ( !m_pPlayer->GetBag().AddItem( Item,IACR_BUY_SHANG_CHENG_ITEM ) )
		{
			LOG_ERROR("购买商城物品失败,itemClass=%d,ItemId=%d,ItemCount=%d,time=%d,cid=%lld",pShangCheng->ItemClass,pShangCheng->ItemId,ItemCount,m_pPlayer->getNow(),m_pPlayer->getCid() );
		}

		GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_BUY_SHANG_CHENG_ITEM, pShangCheng->ShopId );
	}

	if ( pShangCheng->LimitType == LIMIT_TYPE_CHAR )
	{
		AddLimitCount( pShangCheng->ShopId, ItemCount );
		SendItemLimitChange( pShangCheng->ShopId );
	}

	return ERR_OK;
}

int32_t	CShangCheng::OnBuyShopItem( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || inPacket == NULL )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ShopId		= inPacket->readInt32();
	int32_t ItemCount	= inPacket->readInt32();
	return BuyShopItem(  ShopId, ItemCount );
}

int32_t	CShangCheng::OnAskLimitInfo( Answer::NetPacket *inPacket )
{
	SendLimitInfo();
	SendSocialAskLimitInfo();
	return ERR_OK;
}

void CShangCheng::SendItemLimitChange( int32_t ShopId )
{
	ItemLimitMap::iterator it = m_LiMitMap.find( ShopId );
	if ( it == m_LiMitMap.end() )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ITEM_LIMIT_COUNT );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( 1 );
	packet->writeInt32( it->first );
	packet->writeInt32( it->second );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CShangCheng::OnBuyGameLimitItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ShopId		= inPacket->readInt32();
	int32_t ItemCount	= inPacket->readInt32();

	CfgGameShop* pShangCheng = CFG_DATA.GetGameShop( ShopId );
	if ( NULL == pShangCheng )
	{
		return ERR_SYETEM_ERR;
	}
	if ( ItemCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nLayNum = CFG_DATA.getOverlay( pShangCheng->ItemId, pShangCheng->ItemClass );

	if ( ItemCount > nLayNum )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pShangCheng->LimitType != LIMIT_TYPE_SERVER )	
	{
		return ERR_SYETEM_ERR;
	}

	if ( pShangCheng->ItemClass == IC_PET_EGG )
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

	if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pShangCheng->Price * ItemCount )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD , pShangCheng->Price * ItemCount, GCR_BUY_SHANG_CHENG_ITEM, pShangCheng->ShopId ) )
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag Item = {};
	Item.itemClass		= pShangCheng->ItemClass;
	Item.itemCount		= ItemCount;
	Item.bind			= pShangCheng->ItemBind;
	Item.itemId			= pShangCheng->ItemId;

	if ( pShangCheng->ItemClass == IC_PET_EGG )
	{
		std::list<int32_t> EggIdList;
		EggIdList.push_back( pShangCheng->ItemId );
		m_pPlayer->GetCharPet().AddEggs( EggIdList );
	}
	else if ( !m_pPlayer->GetBag().AddItem( Item,IACR_BUY_SHANG_CHENG_ITEM ) )
	{
		LOG_ERROR("购买商城物品失败,itemClass=%d,ItemId=%d,ItemCount=%d,time=%d,cid=%lld",pShangCheng->ItemClass,pShangCheng->ItemId,ItemCount,m_pPlayer->getNow(),m_pPlayer->getCid() );
	}
	SendBuyItemSucceed( ShopId, ItemCount );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_BUY_SHANG_CHENG_ITEM, pShangCheng->ShopId );
	return ERR_OK;
}

void CShangCheng::SendBuyItemSucceed( int32_t ShopId, int32_t AddCount )
{
	 Answer::NetPacket *Packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, IM_GAME_SOCIAL_BUY_LIMIT_SHOP_SUCCEED);
	if (NULL == Packet || NULL == m_pPlayer )
	{
		return;
	}
	Packet->writeInt32( m_pPlayer->getGateIndex() );
	Packet->writeInt32( ShopId );
	Packet->writeInt32( AddCount );
	Packet->setSize(Packet->getWOffset());
	GAME_SERVICE.sendPacket(Packet);
}

int32_t	CShangCheng::GetLimitCount( int32_t ShopId )
{
	ItemLimitMap::iterator it = m_LiMitMap.find(ShopId);
	if ( it != m_LiMitMap.end() )
	{
		return it->second;
	}
	return 0;
}

void CShangCheng::SendLimitInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ITEM_LIMIT_COUNT );
	if (NULL == packet)
	{
		return;
	}
	int32_t nSize = m_LiMitMap.size();
	packet->writeInt32( nSize );
	ItemLimitMap::iterator it = m_LiMitMap.begin();
	for ( ; it != m_LiMitMap.end(); ++it )
	{	
		packet->writeInt32( it->first );
		packet->writeInt32( it->second );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CShangCheng::AddLimitCount( int32_t ShopId, int32_t AddCount )
{
	if ( ShopId <= 0 || AddCount <= 0 )
	{
		return;
	}
	ItemLimitMap::iterator it = m_LiMitMap.find( ShopId );
	if ( it != m_LiMitMap.end() )
	{
		m_LiMitMap[ShopId] +=  AddCount;
	}
	else
	{
		m_LiMitMap[ShopId] = AddCount;
	}
}

bool CShangCheng::IsLimited( CfgGameShop* pShangCheng, int32_t ItemCount )
{
	if ( NULL == pShangCheng || ItemCount <= 0 || NULL == m_pPlayer )
	{
		return true;
	}
	
	switch( pShangCheng->LimitType )
	{
	case LIMIT_TYPE_INVALID:
		{
			return false;
		}
	case LIMIT_TYPE_CHAR:
		{
			if ( GetLimitCount( pShangCheng->ShopId ) + ItemCount > pShangCheng->LimitCount )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	case LIMIT_TYPE_TIME:
		{
			int32_t TimeNow = m_pPlayer->getNow();
			if ( TimeNow > pShangCheng->LimitStartTime &&  TimeNow < pShangCheng->LimitEndTime )
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	default:
		return true;
	}
}

void CShangCheng::SendSocialBuyLimitItem( int32_t ShopId, int32_t Count )
{
	 Answer::NetPacket *Packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, IM_GAME_SOCIAL_BUY_LIMIT_SHOP_ITEM);
	if (NULL == Packet || NULL == m_pPlayer )
	{
		return;
	}
	Packet->writeInt32( m_pPlayer->getGateIndex() );
	Packet->writeInt32( ShopId );
	Packet->writeInt32( Count );
	Packet->setSize(Packet->getWOffset());
	GAME_SERVICE.sendPacket(Packet);
}

void CShangCheng::SendSocialAskLimitInfo()
{
	 Answer::NetPacket *Packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, IM_GAME_SOCIAL_ASK_LIMIT_SHOP_INFO);
	if (NULL == Packet || NULL == m_pPlayer )
	{
		return;
	}
	Packet->writeInt32( m_pPlayer->getGateIndex() );
	Packet->writeInt8( 0 );
	Packet->setSize(Packet->getWOffset());
	GAME_SERVICE.sendPacket(Packet);
}

