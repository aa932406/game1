#ifndef __CHAR_MYSTERY_GIFT_H__
#define __CHAR_MYSTERY_GIFT_H__

#include "ExtSystemBase.h"

class CfgMysteryGift;

class CExtCharMysteryGift : public CExtSystemBase
{
public:
	CExtCharMysteryGift(){ OnCleanUp(); }
	virtual ~CExtCharMysteryGift(){}

	virtual void GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	
	virtual void OnCleanUp(){ m_pPlayer = NULL; }

private:
	bool isFunctionOpen() const;

	int32_t onGetGift( Answer::NetPacket *inPacket );
	int32_t onRequestInfo( Answer::NetPacket *inPacket );

	void SendMysteryGiftInfo( bool bCheckIndex );

	int32_t getLeftTime();
	int64_t getCondition();
	int8_t	getState();
	void	setState( int8_t nState );
	int32_t getIndex();
	void	addIndex();
	void	broadcastGetGift( int32_t nBroadId );
};

#endif //__CHAR_MYSTERY_GIFT_H__
