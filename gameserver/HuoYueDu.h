#ifndef __HUO_YUE_DU_H__
#define __HUO_YUE_DU_H__
#include "ExtSystemBase.h"
enum HuoYueDuType
{
	HYDT_ACTIVITY		= 1,	//活动
	HYDT_DUNGEON		= 2,	//副本
	HYDT_QI_FU_EXP		= 3,	//祈福经验
	HYDT_QI_FU_MONEY    = 4,	//祈福铜钱
	HYDT_KILL_BOSS		= 5,	//击杀boss 
	HYDT_DA_WEI_WANG	= 6,	//大胃王  
	HYDT_SIGN			= 7,	//签到
	HYDT_ILLUSION		= 8,	//幻化      
	HYDT_KILL_MONSTER	= 9,	//击杀指定怪 
	HYDT_COST_CASH		= 10,	//消费绑定魔石
	HYDT_COST_GOLD		= 11,	//消费魔石
	HYDT_EQUIP_STAT_UP	= 12,	//装备强化 
	HYDT_CYCLE_TASK		= 13,	//循环任务
	HYDT_FAMILY_DONATE	= 14,	//军团捐献
};

class CHuoYueDu
	:public CExtSystemBase
{
public:
	CHuoYueDu();
	~CHuoYueDu();

	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			OnCleanUp();
	virtual void			OnDaySwitch( int32_t nDiffDays );

	void					AddHuoYueDuRecord( int8_t Type, int32_t Effect = 0 );
	void					SendHuoYueDuInfo();
	int32_t					RewardCount();
private:
	int32_t					OnAskHuoYueDuInfo( Answer::NetPacket *inPacket );
	int32_t					OnGetHuoYueDuReward( Answer::NetPacket *inPacket );
	int32_t					OnSec( Answer::NetPacket *inPacket );
	
	int32_t					CalculateHuoYueDu();
private:
	HuoYueDuRecordMap		m_HuoYueDuRecord;
};

#endif