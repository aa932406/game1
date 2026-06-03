#ifndef __TRADE_H__
#define __TRADE_H__

#include "ExtSystemBase.h"

#define TRADE_BOX_MAX_COUNT 6		//交易

enum OPERATE_VALUES
{
	OPERATE_AGREE_TRADE		= 1,	//同意邀请
	OPERATE_SET_LOCK		= 2,	//锁定物品
	OPERATE_SET_SURED		= 3,	//确定交易
	OPERATE_CANCEL			= 4,	//取消交易
};

enum TRADE_ERR_VALUES
{
	ERR_TARGET_TRADING			= 1,	//对方正在交易
	ERR_TARGET_BAG_NOT_ENOUGH	= 2,	//对方背包格子不足
	ERR_BAG_NOT_ENOUGH			= 3,	//背包格子不足
	ERR_MONEY_NOT_ENOUGH		= 4,	//金币不足
	ERR_TARGET_MONEY_NOT_ENOUGH	= 5,	//对方金币不足
	ERR_GOLD_NOT_ENOUGH			= 6,	//元宝不足
	ERR_TARGET_GOLD_NOT_ENOUGH	= 7,	//对方元宝不足
	ERR_NOT_THIS_ITEM			= 8,	//没有这个物品
	ERR_TARGET_NOT_THIS_ITEM	= 9,	//对方没有这个物品
	ERR_TARGET_LEVEL_LOW		= 10,	//对方等级不足
};

class TradeData
{
public:
	TradeData()
	{
		OnClanup();
	}
	void OnClanup()
	{
		BagSlot = -1;
		bzero(&CharBagData,sizeof( CharBagData ) );
	}
	int32_t		BagSlot;
	MemChrBag	CharBagData;
};

class CTrade:
	 public CExtSystemBase
{
public:
	CTrade();
	~CTrade();
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnCleanUp();
	virtual void			OnUpdate( int64_t curTick );

private:
	int32_t					OnAskTrade( Answer::NetPacket *inPacket );					//请求交易
	int32_t					OnAgreeTrade( Answer::NetPacket *inPacket );				//同意交易
	int32_t					OnAddItem( Answer::NetPacket *inPacket );					//添加物品
	int32_t					OnRemoveItem( Answer::NetPacket *inPacket );				//移除物品
	int32_t					OnAddMoney( Answer::NetPacket *inPacket );					//增加铜钱或魔石
//	int32_t					OnSubMoney( Answer::NetPacket *inPacket );					//减少铜钱或魔石
	int32_t					OnLock( Answer::NetPacket *inPacket );						//锁定物品
	int32_t					OnSured( Answer::NetPacket *inPacket );						//确定交易
	int32_t					OnCancel( Answer::NetPacket *inPacket );					//取消交易
private:
	void					SendAskTrade( Player *pTarget );							
	void					SendItemChange( int32_t TradeSlot );						
	void					SendTargetItemChange( int32_t TradeSlot );					
	void					SendTradeMoneyChange();										
	void					SendTargetTradeMoneychange();								
	void					SendTradeSucceed( int32_t& Moeny, int32_t& Gold, MemChrBagVector& ItemVector );	
	void					SendOperateToTarget( OPERATE_VALUES OperateType );			
	int32_t					GetDistance( Position Pos );																			
	void					CheckDistance();
	void					RemoveItem( int32_t TradeSlot );

public:
	bool					IsTrading();
	bool					IsLock();
	bool					IsSureTrad();

	void					SetTrading();
	void					SetSureTrad();
	void					SetLock();
	void					SetTargetChar( CharId_t TargetId );
	void					GetTradeItem( int32_t& Moeny, int32_t& Gold, MemChrBagVector& ItemVector);
	bool					CompareItem();
	void					RemoveBagItem();
	void					AddBagItem( MemChrBagVector& ItemVector );
	bool					HaveSameBagSlot(int32_t BagSlot );				//不能有相同的Bagslot在交易栏
private:
	TradeData			m_TradeData[TRADE_BOX_MAX_COUNT];
	CharId_t			m_TargetId;					// 交易对方id					
	bool				m_IsTrading;				// 是否正在交易
	bool				m_IsLock;					// 是否锁定
	bool				m_IsSureTrad;				// 是否确认交易
	int32_t				m_TradMoney;				// 铜钱
	int32_t				m_TradGold;					// 元宝
};

#endif