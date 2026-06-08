#include "ScoreShop.h"
#include "GameService.h"
#include "DataStruct.h"


enum ScoreShopType
{
	ChouJinagScore	= 1,
	BossScore		= 2,
};

ScoreShop::ScoreShop()
{

}

ScoreShop::	~ScoreShop()
{

}

void ScoreShop::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_ItemLimit = dbData.m_ScoreShopData.m_LiMitMap;
}

void ScoreShop::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_ScoreShopData.m_LiMitMap = m_ItemLimit;
}

void ScoreShop::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_BUY_SCORE_SHOP_ITEM );
	procList.push_back( CM_ASK_SCORE_SHOP_INFO );
}

int32_t	ScoreShop::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case CM_BUY_SCORE_SHOP_ITEM:
		{
			return OnBuyItem( inPacket );
		}
	case CM_ASK_SCORE_SHOP_INFO:
		{
			SendLimitInfo();
			break;
		}
	default:
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t ScoreShop::OnBuyItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t Index	= inPacket->readInt32();
	int32_t Count	= inPacket->readInt32();
	if ( Count <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	ChouJiangShop* pShop = CFG_DATA.GetChouJiangCfg().GetCJShop( Index );
	if ( NULL == pShop )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nLayNum = CFG_DATA.getOverlay( pShop->ItemId, pShop->ItemClass );
	if ( nLayNum < Count )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pShop->ItemClass == IC_PET_EGG )
	{
		if ( m_pPlayer->GetCharPet().GetEggBagAddHatchBagFreeCount() <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else if ( m_pPlayer->GetBag().GetbagFreeSize() <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pShop->Limit > 0 )
	{
		int32_t Limit = GetLimitCount( Index );
		if ( Limit + Count > pShop->Limit )
		{
			return ERR_SYETEM_ERR;
		}
	}
	
	if ( pShop->Type == ChouJinagScore )
	{
		if ( pShop->NeedScore <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
		if (  m_pPlayer->GetCurrency( CURRENCY_CHOUJINAG ) < pShop->NeedScore * Count )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_CHOUJINAG, pShop->NeedScore * Count, SCR_BUY_ITEM, Index ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else if ( pShop->Type == BossScore )
	{
		if ( pShop->NeedScore <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
		if (  m_pPlayer->GetCurrency( CURRENCY_BOSS ) < pShop->NeedScore*Count )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_BOSS, pShop->NeedScore*Count, SCR_BUY_ITEM, Index ))
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		return ERR_SYETEM_ERR;
	}
	MemChrBag item = {};
	item.itemId		= pShop->ItemId;	
	item.itemClass	= pShop->ItemClass;
	item.itemCount	= pShop->ItemCount*Count;	
	item.bind		= pShop->Bind;
	if ( item.itemClass == IC_PET_EGG )
	{
		std::list<int32_t> Eggs;
		Eggs.push_back(pShop->ItemId);
		m_pPlayer->GetCharPet().AddEggs(Eggs);
	}
	else
	{
		m_pPlayer->GetBag().AddItem( item, IACR_BUY_CHOU_JIANG_SHOP );
	}
	if ( pShop->Limit > 0 )
	{
		AddLimitCount( Index, Count );
		SendLimitInfo( Index );
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(),inPacket->getProc() ,Index);
	return ERR_OK;
}

void ScoreShop::SendLimitInfo( int32_t Index )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_SCORE_SHOP_LIMIT_INFO );
	if (NULL == packet)
	{
		return;
	}
	if ( Index > 0 )
	{
		ItemLimitMap::iterator it = m_ItemLimit.find(Index);
		if ( it != m_ItemLimit.end() )
		{
			packet->writeInt32( 1 );
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
		}
		else
		{
			packet->writeInt32( 1 );
			packet->writeInt32( 0 );
			packet->writeInt32( 0 );
		}

	}
	else
	{
		int32_t nCount = m_ItemLimit.size();
		packet->writeInt32( nCount );
		ItemLimitMap::iterator iter = m_ItemLimit.begin();
		ItemLimitMap::iterator eiter = m_ItemLimit.end();
		for ( ; iter != eiter; ++iter )
		{
			packet->writeInt32( iter->first );
			packet->writeInt32( iter->second );
		}
	}

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

int32_t ScoreShop::GetLimitCount( int32_t index )
{
	ItemLimitMap::iterator it = m_ItemLimit.find(index);
	if ( it != m_ItemLimit.end() )
	{
		return it->second;
	}
	return 0;
}

void ScoreShop::AddLimitCount( int32_t index, int32_t count )
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

void ScoreShop::OnDaySwitch( int32_t nDiffDays )
{
	m_ItemLimit.clear();
}

void ScoreShop::GetIconState( IconStateList& iconList )
{
	ShowIcon icon = {};
	icon.nId		= SCORE_SHOP;
	icon.nState		= AS_RUNNING;
	icon.nLeftTime	= -1;
	iconList.push_back( icon );
}