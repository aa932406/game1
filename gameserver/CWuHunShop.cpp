#include "stdafx.h"
#include "CWuHunShop.h"
#include "GameService.h"
#include "Player.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "CfgData.h"
#include "Timer.h"

using namespace Answer;

CWuHunShop::CWuHunShop()
    : CExtSystemBase()
    , m_RefreshTimes( 0 )
    , m_LastRefreshTime( 0 )
{
}

CWuHunShop::~CWuHunShop()
{
}

void CWuHunShop::OnDaySwitch( int32_t nDiffDays )
{
    for ( std::map<int32_t, WuHunShop>::iterator it = m_WuHunShopMap.begin();
            it != m_WuHunShopMap.end(); ++it )
    {
        RefreshShop( it->first );
    }
}

void CWuHunShop::OnUpdate( int64_t curTick )
{
    if ( m_pPlayer != NULL && m_LastRefreshTime > 0
        && m_pPlayer->getNow() >= m_LastRefreshTime + 7200 )
    {
        AddRefreshTimes( 1, 1 );
        m_LastRefreshTime = m_pPlayer->getNow();
    }
}

void CWuHunShop::OnCleanUp()
{
    m_WuHunShopMap.clear();
    m_RefreshTimes = 0;
    m_LastRefreshTime = 0;
}

void CWuHunShop::OnLoadFromDB( const PlayerDBData* dbData )
{
    if ( NULL == dbData )
    {
        return;
    }
    m_LastRefreshTime = dbData->m_WuHunShopDBData.m_LastRefreshTime;
    m_RefreshTimes = dbData->m_WuHunShopDBData.m_RefreshTimes;
    // m_WuHunShopMap is transient - regenerated on demand via RefreshShop()

    if ( m_pPlayer != NULL && m_LastRefreshTime > 0 )
    {
        int32_t AddCount = ( m_pPlayer->getNow() - m_LastRefreshTime ) / 7200;
        if ( AddCount > 0 )
        {
            m_LastRefreshTime += 7200 * AddCount;
            AddRefreshTimes( AddCount, 0 );
        }
    }
}

void CWuHunShop::OnSaveToDB( PlayerDBData* dbData )
{
    if ( NULL == dbData )
    {
        return;
    }
    dbData->m_WuHunShopDBData.m_LastRefreshTime = m_LastRefreshTime;
    dbData->m_WuHunShopDBData.m_RefreshTimes = m_RefreshTimes;
    // m_WuHunShopMap is transient - no need to save
}

void CWuHunShop::GetInterestsProtocol( ProcIdList& procList )
{
    procList.push_back( 650 );
    procList.push_back( 651 );
    procList.push_back( 652 );
}

int32_t CWuHunShop::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
    if ( NULL == inPacket )
    {
        return ERR_INVALID_DATA;
    }

    switch ( nProcId )
    {
    case 650:   return onAskShopInfo( inPacket );
    case 651:   return onRefreshShopItems( inPacket );
    case 652:   return onBuyShopItem( inPacket );
    }
    return ERR_INVALID_DATA;
}

int32_t CWuHunShop::onAskShopInfo( Answer::NetPacket* inPacket )
{
    if ( NULL == m_pPlayer || NULL == inPacket )
    {
        return ERR_INVALID_DATA;
    }

    int32_t ShopId = inPacket->readInt32();
    std::map<int32_t, WuHunShop>::iterator it = m_WuHunShopMap.find( ShopId );

    if ( it == m_WuHunShopMap.end() )
    {
        if ( !RefreshShop( ShopId ) )
        {
            return ERR_INVALID_DATA;
        }
    }

    sendShopRefreshTimes();
    sendShopInfo( ShopId );
    return ERR_INVALID_DATA;
}

int32_t CWuHunShop::onBuyShopItem( Answer::NetPacket* inPacket )
{
    if ( NULL == m_pPlayer || NULL == inPacket )
    {
        return ERR_INVALID_DATA;
    }

    int32_t ShopId = inPacket->readInt32();
    int8_t  nIndex = inPacket->readInt8();

    std::map<int32_t, WuHunShop>::iterator it = m_WuHunShopMap.find( ShopId );
    if ( it == m_WuHunShopMap.end() )
    {
        return ERR_INVALID_DATA;
    }

    if ( nIndex >= 4 )
    {
        return ERR_INVALID_DATA;
    }

    if ( it->second.nState[nIndex] > 0 )
    {
        return ERR_INVALID_DATA;
    }

    int32_t nCfgIndex = it->second.nIndex[nIndex];
    const CfgWuHunShop* pCfg = CFG_DATA.GetWuHunShopItem( nCfgIndex );
    if ( NULL == pCfg )
    {
        return ERR_INVALID_DATA;
    }

    if ( pCfg->Const > 0
        && !m_pPlayer->DecCurrency( CURRENCY_BLOOD, pCfg->Const, GCR_WU_HUN_SHOP_BUY, 0 ) )
    {
        return ERR_INVALID_DATA;
    }

    if ( !m_pPlayer->GetBag().AddItem( &pCfg->Item, ICR_WU_HUN_SHOP_BUY ) )
    {
        return ERR_INVALID_DATA;
    }

    it->second.nState[nIndex] = 1;
    sendShopInfo( ShopId );
    return 0;
}

int32_t CWuHunShop::onRefreshShopItems( Answer::NetPacket* inPacket )
{
    if ( NULL == m_pPlayer || NULL == inPacket )
    {
        return ERR_INVALID_DATA;
    }

    int32_t ShopId = inPacket->readInt32();

    std::map<int32_t, WuHunShop>::iterator it = m_WuHunShopMap.find( ShopId );
    if ( it == m_WuHunShopMap.end() )
    {
        return ERR_INVALID_DATA;
    }

    if ( m_RefreshTimes > 0 )
    {
        SubRefreshTimes();
    }
    else if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, 100, GCR_WU_HUN_SHOP_REFRESH, 0 ) )
    {
        return ERR_INVALID_DATA;
    }

    if ( !RefreshShop( ShopId ) )
    {
        return ERR_INVALID_DATA;
    }

    sendShopInfo( ShopId );

    // 回复成功
    GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
    return 0;
}

void CWuHunShop::sendShopInfo( int32_t ShopId )
{
    if ( NULL == m_pPlayer )
    {
        return;
    }

    std::map<int32_t, WuHunShop>::iterator it = m_WuHunShopMap.find( ShopId );
    if ( it == m_WuHunShopMap.end() )
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2E9F );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( ShopId );
    packet->writeInt8( 4 );  // 4个商品位
    for ( int32_t i = 0; i < 4; ++i )
    {
        packet->writeInt32( it->second.nIndex[i] );
        packet->writeInt8( it->second.nState[i] );
    }
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CWuHunShop::sendShopRefreshTimes()
{
    if ( NULL == m_pPlayer )
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2EA0 );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( m_RefreshTimes );
    packet->writeInt32( m_LastRefreshTime );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CWuHunShop::AddRefreshTimes( int32_t Times, bool IsNow )
{
    if ( NULL == m_pPlayer )
    {
        return;
    }

    if ( m_RefreshTimes <= 4 )
    {
        m_RefreshTimes += Times;
        if ( IsNow )
        {
            m_LastRefreshTime = m_pPlayer->getNow();
        }
        if ( m_RefreshTimes > 4 )
        {
            m_RefreshTimes = 5;
            m_LastRefreshTime = 0;
        }
        sendShopRefreshTimes();
    }
    else
    {
        m_RefreshTimes = 5;
        m_LastRefreshTime = 0;
    }
}

void CWuHunShop::SubRefreshTimes()
{
    --m_RefreshTimes;
    if ( !m_LastRefreshTime )
    {
        m_LastRefreshTime = m_pPlayer->getNow();
    }
    sendShopRefreshTimes();
}

bool CWuHunShop::RefreshShop( int32_t ShopId )
{
    // 创建局部副本，选中后从副本中移除（防止同个商品被多次选中）
    CfgWuHunShopList Items = CFG_DATA.GetWuHunShopItemList();
    if ( Items.size() <= 3 )
    {
        return false;
    }

    int32_t MaxRand = 0;
    for ( CfgWuHunShopList::const_iterator iter = Items.begin(); iter != Items.end(); ++iter )
    {
        MaxRand += iter->Rate;
    }

    WuHunShop& shop = m_WuHunShopMap[ShopId];

    // 按概率抽取4个商品
    for ( int32_t i = 0; i < 4; ++i )
    {
        if ( MaxRand <= 0 )
        {
            return false;
        }

        int32_t nRand = RANDOM.generate( 1, MaxRand );
        for ( CfgWuHunShopList::iterator it = Items.begin(); it != Items.end(); ++it )
        {
            if ( it->Rate >= nRand )
            {
                shop.nIndex[i] = it->Index;
                shop.nState[i] = 0;
                MaxRand -= it->Rate;
                Items.erase( it );  // 移除已选中的商品
                break;
            }
            nRand -= it->Rate;
        }
    }

    return true;
}
