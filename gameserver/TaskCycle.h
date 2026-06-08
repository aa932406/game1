/*
* ѭ������
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
	int32_t			GetDrawTimes();

private:
	void			sendTaskInfo();
	void			refreshTask();
	void			refreshStar();
	void			addReward( int8_t nRadio );
	int32_t			GetTaskCycleTimes();

private:
	int32_t			m_nFinishTimes;			// ��ǰ��ɼ�����
	int32_t			m_nTaskId;				// ��ǰ����ID
	int8_t			m_nStar;				// ��ǰ�Ǽ�
	int8_t			m_nState;				// ��ǰ����״̬ 2 �ɽ� 3 �ѽ� 4 ���ύ
	int32_t			m_nKills;				// �Ѿ�ɱ�˼�����
	int32_t			m_nMonsterId;			// ��Ҫɱ���ĸ�����
	int32_t			m_nNeedKills;			// �ܹ���Ҫɱ����
	int32_t			m_nRefreshStarTimes;	// ˢ�Ǵ���
};

#endif	//__TPOC_TASK_CYCLE_H__