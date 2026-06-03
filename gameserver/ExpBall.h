#ifndef __EXP_BALL_H_
#define __EXP_BALL_H_
#include "ExtSystemBase.h"

class CExpBall
	:public CExtSystemBase
{
public:
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnCleanUp();
	
	void					SendExpBallInfo();
	void					AddBallExp( int32_t AddExp );
private:
	int32_t					OnPutInExpBall( Answer::NetPacket *inPacket );

private:
	int32_t		m_ItemId;
	int32_t		m_CurExp;
	int32_t		m_MaxExp;
};

#endif