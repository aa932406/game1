#include "CharMysteryShop.h"
#include "GameService.h"
#include "CfgData.h"
#include "Player.h"
#include "Bag.h"
#include "DataStruct.h"

using namespace Answer;

CExtCharMysteryShop::CExtCharMysteryShop()
{
}

CExtCharMysteryShop::~CExtCharMysteryShop()
{
}

void CExtCharMysteryShop::OnLoadFromDB( const PlayerDBData* dbData )
{
	m_lstShops = dbData->m_MysteryShopDBData.lstShop;
}

void CExtCharMysteryShop::OnSaveToDB( PlayerDBData* dbData )
{
	dbData->m_MysteryShopDBData.lstShop = m_lstShops;
}

void CExtCharMysteryShop::OnDaySwitch( int32_t nNow )
{
	// 每日清空
	m_lstShops.clear();
}

bool CExtCharMysteryShop::isFunctionOpen() const
{
	// 功能开放 — 可后续通过 CFunctionOpen 扩展
	return true;
}

void CExtCharMysteryShop::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 880 );	// 请求商店信息
	procList.push_back( 881 );	// 购买商品
	procList.push_back( 882 );	// 刷新商店
}

int32_t CExtCharMysteryShop::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( !isFunctionOpen() )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case 880: return onAskShopInfo( inPacket );
	case 881: return onBuyShopItem( inPacket );
	case 882: return onRefreshShopItems( inPacket );
	default: break;
	}
	return ERR_OK;
}

// ========== 880 请求商店信息 ==========
int32_t CExtCharMysteryShop::onAskShopInfo( NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType = inPacket->readInt8();
	if ( nType <= 0 || nType > 2 )
	{
		return ERR_INVALID_DATA;
	}

	// 时间检查 — 简化版，后续可接入 CUniteServer / CFestivalDoubleEleven

	// 查找已有商店
	for ( MysteryShopList::iterator iter = m_lstShops.begin(); iter != m_lstShops.end(); ++iter )
	{
		if ( iter->nType == nType )
		{
			checkRefresh( &(*iter) );
			sendShopInfo( &(*iter) );
			return ERR_OK;
		}
	}

	// 新建商店
	MysteryShop shop;
	memset( &shop, 0, sizeof( shop ) );
	shop.nType = nType;
	refreshShop( &shop, true );
	sendShopInfo( &shop );
	m_lstShops.push_back( shop );
	return ERR_OK;
}

// ========== 881 购买商品 ==========
int32_t CExtCharMysteryShop::onBuyShopItem( NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType = inPacket->readInt8();
	int8_t nIndex = inPacket->readInt8();

	if ( nType <= 0 || nType > 2 || (uint8_t)nIndex >= 4 )
	{
		return ERR_INVALID_DATA;
	}

	// 查找商店
	MysteryShop* pShop = NULL;
	for ( MysteryShopList::iterator iter = m_lstShops.begin(); iter != m_lstShops.end(); ++iter )
	{
		if ( iter->nType == nType )
		{
			pShop = &(*iter);
			break;
		}
	}

	if ( NULL == pShop )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBuyFlag = pShop->nBuyFlag | (1 << nIndex);
	if ( pShop->nBuyFlag == nBuyFlag )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nGoodsId = pShop->vGoods[nIndex];
	const CfgMysteryShop* pCfg = CFG_DATA.GetMysteryShopTable()->GetShopGood( nGoodsId );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}

	// 检查背包空格
	CExtCharBag& bag = m_pPlayer->GetBag();
	if ( bag.GetFreeSlotCount() <= 0 )
	{
		return ERR_BAG_IS_FULL;
	}

	// 扣费
	if ( pCfg->nCostType == -1 )
	{
		// 物品兑换
		if ( pCfg->exchange.m_nId <= 0 || pCfg->exchange.m_nCount <= 0 )
		{
			return ERR_INVALID_DATA;
		}
		if ( !bag.RemoveItem( pCfg->exchange, IDCR_MYSTERY_SHOP_BUY_COST ) )
		{
			return ERR_NOT_ENOUGH_STUFF;
		}
	}
	else
	{
		if ( pCfg->nPrice <= 0 )
		{
			return ERR_INVALID_DATA;
		}
		if ( pCfg->nCostType == 0 )
		{
			// 元宝（不可用绑定元宝）
			if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nPrice, GCR_MYSTERY_SHOP_BUY, pCfg->nId ) )
			{
				return ERR_NOT_ENOUGH_GOLD;	// CURRENCY_GOLD
			}
		}
		else
		{
			// 其他货币类型
			if ( !m_pPlayer->DecCurrency( (CURRENCY_TYPE)pCfg->nCostType, pCfg->nPrice, GCR_MYSTERY_SHOP_BUY, pCfg->nId ) )
			{
				return ERR_NOT_ENOUGH_MONEY;
			}
		}
	}

	// 发放物品
	bag.AddItem( pCfg->item, IACR_MYSTERY_SHOP_BUY_GET );

	// 广播
	if ( pCfg->nBroad > 0 )
	{
		std::string name = m_pPlayer->getName();
		CharId_t cid = m_pPlayer->getCid();
		broadcastBuyItem( pCfg->nBroad, &name, cid, pCfg->nId );
	}

	// 回复客户端
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nIndex );

	pShop->nBuyFlag = nBuyFlag;

	// 全部买完则刷新
	if ( nBuyFlag == 15 )
	{
		refreshShop( pShop, true );
		sendShopInfo( pShop );
	}

	return ERR_OK;
}

// ========== 882 刷新商店 ==========
int32_t CExtCharMysteryShop::onRefreshShopItems( NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nType = inPacket->readInt8();
	if ( nType <= 0 || nType > 2 )
	{
		return ERR_INVALID_DATA;
	}

	// 时间检查 — 简化版

	// 查找商店
	MysteryShop* pShop = NULL;
	for ( MysteryShopList::iterator iter = m_lstShops.begin(); iter != m_lstShops.end(); ++iter )
	{
		if ( iter->nType == nType )
		{
			pShop = &(*iter);
			break;
		}
	}

	if ( NULL == pShop )
	{
		return ERR_INVALID_DATA;
	}

	// 刷新扣费（20元宝/次）
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, 20, GCR_MYSTERY_SHOP_REFRESH, nType ) )
	{
		return ERR_NOT_ENOUGH_GOLD;	// CURRENCY_GOLD
	}

	refreshShop( pShop, false );
	sendShopInfo( pShop );

	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nType );

	return ERR_OK;
}

// ========== 发送商店信息 ==========
void CExtCharMysteryShop::sendShopInfo( const MysteryShop* shop )
{
	if ( NULL == m_pPlayer || NULL == shop )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_MYSTERY_SHOP_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( shop->nType );
	int32_t nextRefreshTime = getNextRefreshTime( shop->nAutoRefreshTime );
	packet->writeInt32( nextRefreshTime );

	for ( int32_t i = 0; i < 4; ++i )
	{
		packet->writeInt32( shop->vGoods[i] );
		packet->writeInt8( (shop->nBuyFlag >> i) & 1 );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

// ========== 检查自动刷新 ==========
void CExtCharMysteryShop::checkRefresh( MysteryShop* shop )
{
	if ( NULL == m_pPlayer || NULL == shop )
	{
		return;
	}

	if ( shop->nAutoRefreshTime / 7200 != m_pPlayer->getNow() / 7200 )
	{
		refreshShop( shop, true );
	}
}

// ========== 刷新商店 ==========
void CExtCharMysteryShop::refreshShop( MysteryShop* shop, bool bAuto )
{
	if ( NULL == m_pPlayer || NULL == shop )
	{
		return;
	}

	shop->nBuyFlag = 0;

	Int32List excepts;
	for ( int32_t i = 0; i < 4; ++i )
	{
		int32_t nGoodsId = refreshShopItem( shop->nType, m_pPlayer->getLevel(), &excepts );
		shop->vGoods[i] = nGoodsId;
		excepts.push_back( nGoodsId );
	}

	if ( bAuto )
	{
		shop->nAutoRefreshTime = m_pPlayer->getNow();
	}
}

// ========== 刷新单个商品 ==========
int32_t CExtCharMysteryShop::refreshShopItem( int8_t nType, int32_t nLevel, const Int32List* excepts )
{
	const CfgMysteryShopTable* pTable = CFG_DATA.GetMysteryShopTable();
	if ( NULL == pTable )
	{
		return 0;
	}

	CfgMysteryShopList tlist;
	pTable->GetShopList( tlist, nType );

	CfgMysteryShopList newlist;
	for ( CfgMysteryShopList::const_iterator iter = tlist.begin(); iter != tlist.end(); ++iter )
	{
		// 排除已选中的商品
		if ( excepts != NULL )
		{
			Int32List::const_iterator findIter = std::find( excepts->begin(), excepts->end(), iter->nId );
			if ( findIter != excepts->end() )
			{
				continue;
			}
		}

		// 等级过滤
		if ( nLevel < iter->nMinLevel || nLevel > iter->nMaxLevel )
		{
			continue;
		}

		newlist.push_back( *iter );
	}

	int32_t nMaxRate = 0;
	for ( CfgMysteryShopList::const_iterator iter = newlist.begin(); iter != newlist.end(); ++iter )
	{
		nMaxRate += iter->nRate;
	}

	if ( nMaxRate <= 0 )
	{
		return 0;
	}

	int32_t nRand = RANDOM.generate( 1, nMaxRate );
	for ( CfgMysteryShopList::const_iterator iter = newlist.begin(); iter != newlist.end(); ++iter )
	{
		if ( iter->nRate >= nRand )
		{
			return iter->nId;
		}
		nRand -= iter->nRate;
	}

	return 0;
}

// ========== 获取下次刷新时间 ==========
int32_t CExtCharMysteryShop::getNextRefreshTime( int32_t nLastTime ) const
{
	return 7200 * ( nLastTime / 7200 + 1 );
}

// ========== 广播购买 ==========
void CExtCharMysteryShop::broadcastBuyItem( int32_t broad, const std::string* name, CharId_t cid, int32_t id )
{
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_BROADCAST_MYSTERY_SHOP_BUY );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( broad );
	packet->writeUTF8( *name );
	packet->writeInt64( cid );
	packet->writeInt32( id );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}
