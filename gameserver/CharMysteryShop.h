#pragma once
//////////////////////////////////////////////////////////////////////////
// 神秘商店系统
// Protocol: 880 (请求信息), 881 (购买), 882 (刷新)
//////////////////////////////////////////////////////////////////////////

#include "ExtSystemBase.h"
#include "CfgData.h"

// 协议常量
#define SM_MYSTERY_SHOP_INFO			0x2EA4		// 11940
#define SM_BROADCAST_MYSTERY_SHOP_BUY	0x2CD6		// 11478

class CExtCharMysteryShop : public CExtSystemBase
{
	friend class CExtSystemMgr;
public:
	CExtCharMysteryShop();
	virtual ~CExtCharMysteryShop();

	virtual void	OnLoadFromDB( const PlayerDBData* dbData );
	virtual void	OnSaveToDB( PlayerDBData* dbData );
	virtual void	OnDaySwitch( int32_t nNow );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual	int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

protected:
	bool			isFunctionOpen() const;

	// 协议处理
	int32_t			onAskShopInfo( Answer::NetPacket* inPacket );		// 880
	int32_t			onBuyShopItem( Answer::NetPacket* inPacket );		// 881
	int32_t			onRefreshShopItems( Answer::NetPacket* inPacket );	// 882

	// 内部方法
	void			sendShopInfo( const MysteryShop* shop );
	void			checkRefresh( MysteryShop* shop );
	void			refreshShop( MysteryShop* shop, bool bAuto );
	int32_t			refreshShopItem( int8_t nType, int32_t nLevel, const Int32List* excepts );
	int32_t			getNextRefreshTime( int32_t nLastTime ) const;
	void			broadcastBuyItem( int32_t broad, const std::string* name, CharId_t cid, int32_t id );

protected:
	MysteryShopList	m_lstShops;			// 玩家商店列表
};
