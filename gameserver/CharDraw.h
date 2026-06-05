#pragma once

#include "ExtSystemBase.h"

class CExtCharDraw : public CExtSystemBase
{
public:
	CExtCharDraw();
	virtual ~CExtCharDraw();

public:
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t	OnDraw( Answer::NetPacket *inPacket );
	int32_t	GetItemRecord( int8_t nType );
	bool	canDraw( int8_t nType );
	void	addDrawTimes( int8_t nType, int32_t nGetItemRecord );
};
