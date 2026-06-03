/*
* 循环任务
*/

#ifndef __TPOC_TASK_CYCLE_H__
#define __TPOC_TASK_CYCLE_H__

#include "DataStruct.h"
#define TASK_CYCLE_DAILY_LIMIT 20


class CExtChrTaskCycle : public CExtSystemBase
{
public:
	CExtChrTaskCycle();
	virtual ~CExtChrTaskCycle();

public:
	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t			onReceiveTask( Answer::NetPacket* inPacket );
	int32_t			onSubmitTask( Answer::NetPacket* inPacket );
	int32_t			onRefreshStar( Answer::NetPacket* inPacket );
	int32_t			OnBuyCycleTaskTime( Answer::NetPacket* inPacket );

public:
	void			UpdateTaskMonster(int32_t mid, int32_t level);
	void			SendTaskCycle();
	bool			IsFunctionOpen();
	void			OpenCycleTask();
	int32_t			GetSurplusTimes();

private:
	void			sendTaskInfo();
	void			refreshTask();
	void			refreshStar();
	void			addReward( int8_t nRadio );
	int32_t			GetTaskCycleTimes();

private:
	int32_t			m_nFinishTimes;			// 当前完成几次了
	int32_t			m_nTaskId;				// 当前任务ID
	int8_t			m_nStar;				// 当前星级
	int8_t			m_nState;				// 当前任务状态 2 可接 3 已接 4 可提交
	int32_t			m_nKills;				// 已经杀了几个了
	int32_t			m_nMonsterId;			// 需要杀死哪个怪物
	int32_t			m_nNeedKills;			// 总共需要杀几个
	int32_t			m_nRefreshStarTimes;	// 刷星次数
};

#endif	//__TPOC_TASK_CYCLE_H__