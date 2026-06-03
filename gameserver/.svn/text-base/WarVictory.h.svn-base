#ifndef __WAR_VICTORY_H__
#define __WAR_VICTORY_H__
#include "ExtSystemBase.h"


class CWarVictory:
	public CExtSystemBase
{
public:
	CWarVictory();
	~CWarVictory();
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnUpdate( int64_t curTick );
	virtual void			OnDaySwitch( int32_t nDiffDays );
	virtual void			OnCleanUp();

private:
	int32_t					OnGetWarVictoryReward( Answer::NetPacket *inPacket );

public:
	void					GetWarVictoryIconState( IconStateList& IconList );
	void					SendWarVictoryIcon();
	ShowIcon				GetWarVictoryIconStu();

	void					SendWarVictoryInfo();
	void					GongGao( int32_t GongGaoId  );

	void					AddGold( int32_t Gold );
};

#endif
