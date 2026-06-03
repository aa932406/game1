#ifndef __EXT_TASK_H__
#define __EXT_TASK_H__

#include "CfgData.h"
#include "ExtSystemBase.h"

class CRobot;
class CExtTask : public CExtSystemBase
{
public:
	CExtTask();
	virtual ~CExtTask();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onTaskList( Answer::NetPacket* inPacket );
	int32_t				onTaskKillMonster( Answer::NetPacket* inPacket );
	int32_t				onTaskReceive( Answer::NetPacket* inPacket );

public:
	void				EndTask();
	void				SubmitTask();
	void				ForceSubmit();
	int8_t				GetState() const;
	const TaskDest*		GetDest() const;

private:
	void				updateTask( int32_t nTaskId, int8_t nState );
	bool				checkCanSubmit();

private:
	int32_t				m_nTaskId;
	int8_t				m_nTaskState;
	int32_t				m_nKillCount;
};

#endif	//__EXT_TASK_H__
