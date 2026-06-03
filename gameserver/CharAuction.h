#ifndef __CHAR_AUCTION_H__
#define __CHAR_AUCTION_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharAuction : public CExtSystemBase
{
public:
	CExtCharAuction();
	virtual ~CExtCharAuction();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onAuctionSell( Answer::NetPacket* inPacket );
	int32_t				onAuctionBuy( Answer::NetPacket* inPacket );
	int32_t				onOpenStall( Answer::NetPacket* inPacket );
	int32_t				onCloseStall( Answer::NetPacket* inPacket );

public:
	bool				IsInStall() const;
	void				OnLogOut();

private:
	void				sendSocialSell( const MemChrBag& item, int32_t nPrice );
	void				sendSocialBuy( int32_t nId );
	void				sendSocialStall( bool bStall );
	bool				closeStall();

private:
	EntityId_t			m_nStall;
};

#endif	//__CHAR_AUCTION_H__
