#ifndef __C_TEST_SERVER_REWARD_H__
#define __C_TEST_SERVER_REWARD_H__

#include "stdafx.h"
#include "ExtSystemBase.h"

class CTestServerReward : public CExtSystemBase
{
public:
	CTestServerReward();
	virtual ~CTestServerReward();

	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	int32_t	OnGetTestServerReward( Answer::NetPacket* inPacket );

	void	GetTestServerIcon( IconStateList& IconList );
	void	SendTestServerIcon();
	int32_t	CanActivationCount();
	bool	IsAllGetReward();
};

#endif	//__C_TEST_SERVER_REWARD_H__
