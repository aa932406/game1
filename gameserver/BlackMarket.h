#ifndef __GAMESERVER_BLACK_MARKET_H__
#define __GAMESERVER_BLACK_MARKET_H__

#include "ExtSystemBase.h"
#include "DataStructs.h"

class Player;
struct ShowIcon;

class CBlackMarket : public CExtSystemBase
{
public:
	CBlackMarket( Player* pPlayer )
	{
		m_pPlayer = pPlayer;
	}
	virtual ~CBlackMarket() {}

	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void		OnLoadFromDB(){}
	virtual void		OnSaveToDB( PlayerDBData& dbData ){}
	virtual void		OnCleanUp(){}
	virtual void		OnUpdate( int64_t curTick ){}

	// BlackMarket methods
	int32_t	onRequestMarketInfo( Answer::NetPacket *inPacket );
	int32_t	onEnterMarket( Answer::NetPacket *inPacket );
	int32_t	onBuyMarketGoods( Answer::NetPacket *inPacket );
	void	sendMarketInfo();
	void	SendMarketIcon();
	void	GetMarketIconState( IconStateList& IconList );
	bool	checkBuyRecord();
	void	broadcastBuyItem( int32_t nBroadcast, const MemChrBag& item );
};

#endif	//__GAMESERVER_BLACK_MARKET_H__
