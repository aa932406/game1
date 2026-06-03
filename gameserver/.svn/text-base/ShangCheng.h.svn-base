#ifndef __SHANG_CHENG_H__
#define __SHANG_CHENG_H__
#include "stdafx.h"
#include "ExtSystemBase.h"
#include "CfgData.h"

class CShangCheng:
	public CExtSystemBase
{
public:
	CShangCheng();
	~CShangCheng();
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			OnCleanUp();
	virtual void			OnDaySwitch( int32_t nDiffDays );

	int32_t					BuyShopItem( int32_t ShopId, int32_t ItemCount, bool AddBag = true );
	void					SendLimitInfo();
private:
	int32_t					OnBuyShopItem( Answer::NetPacket *inPacket );
	int32_t					OnAskLimitInfo( Answer::NetPacket *inPacket );
	void					SendItemLimitChange( int32_t ShopId );

	int32_t					OnBuyGameLimitItem( Answer::NetPacket *inPacket );		// 收到globalserver 发来的购买全服限购物品
	void					SendBuyItemSucceed( int32_t ShopId, int32_t AddCount );	// 通知中心服购买成功

	int32_t					GetLimitCount( int32_t ShopId );
	void					AddLimitCount( int32_t ShopId, int32_t AddCount );
	bool					IsLimited( CfgGameShop* pShangCheng, int32_t ItemCount );


	void					SendSocialBuyLimitItem( int32_t ShopId, int32_t Count );// 发到中心服购买全服限制物品
	void					SendSocialAskLimitInfo();								// 请求全服限制物品的信息

//商城中的开服活动

private:
	ItemLimitMap m_LiMitMap;
};

#endif