#ifndef __GUAN_WEI_H__
#define __GUAN_WEI_H__
#include "ExtSystemBase.h"
class CGuanWei
	:public CExtSystemBase
{
public:
	CGuanWei();
	~CGuanWei();

	virtual void			OnLoadFromDB( const PlayerDBData& dbData );			
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	
	void					AddGuanWeiAttr();
	int32_t					GetAddBattle();
	void					SendGuanWeiInfo();
	void					InitGuanWei();
private:
	int32_t					OnAskGuanWeiInfo( Answer::NetPacket *inPacket );
	int32_t					OnGetDailyReward( Answer::NetPacket *inPacket );
	int32_t					OnUpGuanWei( Answer::NetPacket *inPacket );
	void					GongGao( int32_t GuanWei );
};

#endif