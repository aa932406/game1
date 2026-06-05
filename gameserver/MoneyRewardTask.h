//////////////////////////////////////////////////////////////////////////
// 金币奖励任务系统
// 包含：金币奖励任务、PDBF副本任务、装备回购任务、押镖系统、祥曜任务、神威任务
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_MONEY_REWARD_TASK_H__
#define __TPOC_MONEY_REWARD_TASK_H__

#include "ExtSystemBase.h"
#include "DataStruct.h"

class Player;
namespace Answer { class NetPacket; }

class CMoneyRewardTask : public CExtSystemBase
{
friend class Player;
public:
	CMoneyRewardTask();
	virtual ~CMoneyRewardTask();

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	// 金币奖励任务
	bool		IsFunctionOpen();
	void		InitMoneyRewardTask();
	int32_t		OnReceiveMoneyRewardTask( Answer::NetPacket* inPacket );
	int32_t		OnSubmitMoneyRewardTask( Answer::NetPacket* inPacket );
	int32_t		OnGetReward( Answer::NetPacket* inPacket );
	int32_t		OneKeyCompletion( Answer::NetPacket* inPacket );
	void		sendTaskInfo();
	void		parseMoneyRewardTaskInfo( const std::string& infoString );
	std::string	GetMoneyRewardTaskInfo();

	// PDBF副本任务
	bool		IsPdbfFunctionOpen();
	void		InitPdbfTask();
	int32_t		OnReceivePdbfTask( Answer::NetPacket* inPacket );
	int32_t		OnSubmitPdbfTask( Answer::NetPacket* inPacket );
	int32_t		OnPdbfRandStar( Answer::NetPacket* inPacket );
	void		SendPdbfTaskInfo();
	int32_t		RandTaskId();
	int32_t		RandStar();
	float		GetPdbfRewardRate();

	// 装备回购任务
	bool		IsBackEquipFunctionOpen();
	void		InitEquipBackTask();
	int32_t		OnReceiveEquipBackTask( Answer::NetPacket* inPacket );
	int32_t		OnSubmitEquipBackTask( Answer::NetPacket* inPacket );
	int32_t		OnEquipBackTaskRandStar( Answer::NetPacket* inPacket );
	int32_t		GetEquipBackTaskLimit();
	int32_t		RandTaskIndex( int32_t nRandTimes );
	void		SendBackEquipTaskInfo();

	// 押镖系统
	int32_t		OnAskTrailerPos( Answer::NetPacket* inPacket );
	int32_t		OnRandTrailer( Answer::NetPacket* inPacket );
	int32_t		OnStartTrailer( Answer::NetPacket* inPacket );
	int32_t		OnSubTrailer( Answer::NetPacket* inPacket );
	int32_t		OnRequestSupport( Answer::NetPacket* inPacket );
	void		AddJieBiaoTimes();
	int32_t		GetYaBiaoLimit();
	void		RandTrailer();
	void		ResetTrailer();
	void		SendTrailerInfo();
	void		SendTRailerEnd();

	// 祥曜任务
	bool		IsXiangYaoFunctionOpen();
	void		InitXiangYaoTask();
	void		OnXiangYaoFunctionOpen();
	int32_t		OnAskXiangYaoTask( Answer::NetPacket* inPacket );
	int32_t		OnOperatorTask( Answer::NetPacket* inPacket );
	int32_t		OnRefreshTask( Answer::NetPacket* inPacket );
	bool		NeedRefreshTask();
	void		RandXiangYaoTask( bool bBest, bool bNeedGongGao );
	void		LoginInitXiangYaoTask();
	void		SendXiangYaoTaskInfo();
	void		parseXiangYaoTask( const std::string& infoString );
	std::string	saveXiangYaoTaskString();

	// 神威任务
	bool		IsShenWeiFunctionOPen();
	void		InitShenWeiTask();
	int32_t		OnOperatorShenWeiTask( Answer::NetPacket* inPacket );
	void		LoginInitShenWeiTask();
	void		SendShenWeiTaskInfo();
	void		parseShenWeiTask( const std::string& infoString );
	std::string	saveShenWeiTaskString();

	// 虚无/心魔任务
	void		InitXuWuTask();
	void		InitXinMoTask();

private:
	Player*			m_pPlayer;

	// 金币奖励任务
	TaskStateInfo	m_MoneyRewardTask[9];
	int32_t			m_FinishTimes;
	int8_t			m_IsGetReward;

	// PDBF副本任务
	int32_t			m_TaskId;
	int32_t			m_Star;
	int32_t			m_RandStarTimes;
	int32_t			m_PdbfFinishTimes;

	// 装备回购任务
	int32_t			m_EquipBackTaskId;
	int32_t			m_EquipBackTaskFinishTimes;
	int32_t			m_RandEquipBackTaskStarTimes;

	// 押镖系统
	int32_t			m_JieBiaoTimes;
	int32_t			m_YaBiaoTimes;
	int8_t			m_TrailerQuality;
	int32_t			m_EndTime;

	// 祥曜任务
	TaskStateInfo	m_XiangYaoTask[4];
	int32_t			m_XiangYaoFinishTimes;
	int32_t			m_RefreshTimes;

	// 神威任务
	int8_t			m_ShenWeiTaskState[5];
};

#endif	//__TPOC_MONEY_REWARD_TASK_H__
