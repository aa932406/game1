#ifndef _EXTSYSTEMMGR_H_
#define _EXTSYSTEMMGR_H_

#include "stdafx.h"
#include "ExtSystemInterface.h"
#include <map>
#include <list>

class CExtSystemBase;
class CExtSystemMgr : public IExtSystem
{
	typedef std::map<ProcId_t, CExtSystemBase*> ExtSysMap;
	typedef std::list<CExtSystemBase*> ExtSysList;
public:
	CExtSystemMgr();
	virtual ~CExtSystemMgr();

	void			Register(CExtSystemBase* pExtSystem);
	bool			IsProcRegisted( ProcId_t nProc );

public:
	//virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	//virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnUpdate( int64_t curTick );
	//virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	OnCleanUp();
	virtual void	GetInterestsProtocol( ProcIdList& procList ) {}
	virtual int32_t DispatchNetDatas( ProcId_t procId, Answer::NetPacket *inPacket );

private:
	void			registProtocolHandler( ProcId_t procId, CExtSystemBase* pHanlder );

private:
	ExtSysMap		m_mapProcHandler;
	ExtSysList		m_lstExtSystems;
};

#endif // _EXTSYSTEMMGR_H_
