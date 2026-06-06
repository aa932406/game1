#ifndef __C_WU_HUN_SHOP_H__
#define __C_WU_HUN_SHOP_H__

#include "stdafx.h"
#include "ExtSystemBase.h"

// 武魂商店单个槽位结构
struct WuHunShop
{
    WuHunShop()
    {
        memset( nIndex, 0, sizeof(nIndex) );
        memset( nState, 0, sizeof(nState) );
    }
    int32_t nIndex[4];  // 4个商品配置索引
    int8_t  nState[4];  // 4个商品购买状态 (0=可购买, 1=已购买)
};

class CWuHunShop : public CExtSystemBase
{
public:
    CWuHunShop();
    virtual ~CWuHunShop();

    virtual void    OnDaySwitch( int32_t nDiffDays );
    virtual void    OnUpdate( int64_t curTick );
    virtual void    OnCleanUp();

    virtual void    OnLoadFromDB( const PlayerDBData* dbData );
    virtual void    OnSaveToDB( PlayerDBData* dbData );

    virtual void    GetInterestsProtocol( ProcIdList& procList );
    virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

    int32_t onAskShopInfo( Answer::NetPacket* inPacket );
    int32_t onBuyShopItem( Answer::NetPacket* inPacket );
    int32_t onRefreshShopItems( Answer::NetPacket* inPacket );

    void    sendShopInfo( int32_t ShopId );
    void    sendShopRefreshTimes();

    void    AddRefreshTimes( int32_t Times, bool IsNow );
    void    SubRefreshTimes();
    bool    RefreshShop( int32_t ShopId );

private:
    std::map<int32_t, WuHunShop>    m_WuHunShopMap;
    int32_t                         m_RefreshTimes;
    int32_t                         m_LastRefreshTime;
};

#endif //__C_WU_HUN_SHOP_H__
