#ifndef _EXTSYSTEMBASE_H_
#define _EXTSYSTEMBASE_H_

#include "stdafx.h"
#include "ExtSystemInterface.h"

class Player;
class CExtSystemBase : public IExtSystem
{
public:
	CExtSystemBase();
	virtual ~CExtSystemBase();

public:
	virtual void	OnCleanUp();

	//如果子类要重写,必须调用父类的Init函数
	virtual void	Init( Player* pPlayer );
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

protected:
	Player*			m_pPlayer;
};

#endif // _EXTSYSTEMBASE_H_
