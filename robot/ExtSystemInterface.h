#ifndef _EXTSYSTEMINTERFACE_H_
#define _EXTSYSTEMINTERFACE_H_

#include "Shared.h"
#include "libanswer.h"
//#include "DataStruct.h"

typedef std::list<ProcId_t> ProcIdList;
class IExtSystem
{
public:
	virtual void	OnCleanUp() = 0;
	//virtual void	OnDaySwitch( int32_t nDiffDays ) = 0;
	virtual void	OnUpdate( int64_t curTick ) = 0;
 //   virtual void	OnLoadFromDB( const PlayerDBData& dbData ) = 0;
	//virtual void	OnSaveToDB( PlayerDBData& dbData ) = 0;
	virtual void	GetInterestsProtocol( ProcIdList& procList) = 0;
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket ) = 0;
};

#endif // _EXTSYSTEMINTERFACE_H_
