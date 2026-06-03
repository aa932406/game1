#ifndef __DAILY_ACTIVITY_H__
#define __DAILY_ACTIVITY_H__

#include "ExtSystemBase.h"

struct SearchBackInfo
{
	int32_t		Index;
	int32_t		LeftTimes;
};
typedef list<SearchBackInfo> SearchBackInfoList;
enum SEARCH_BACK_TYPE
{
	SBT_ACTIVITY		= 1,		//活动
	SBT_DUNGEON			= 2,		//副本
};

class DailyActivity:
	public CExtSystemBase
{
public:
	DailyActivity();
	~DailyActivity();
	virtual void			OnCleanUp();
	virtual void			OnUpdate( int64_t curTick );
	virtual void			OnDaySwitch( int32_t nDiffDays );
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
private:
	//签到
	int32_t			onSign( Answer::NetPacket *inPacket );
	int32_t			onGetSignReward( Answer::NetPacket *inPacket );
	int32_t			onQuerySignInfo(Answer::NetPacket *inPacket);
	
	//在线奖励
	int32_t			OnGetOnLineReward( Answer::NetPacket *inPacket );
	int32_t			OnQueryOnLineInfo( Answer::NetPacket *inPacket );
	//周在线奖励
	int32_t			OnGetWeekOnLineReward( Answer::NetPacket *inPacket );

	//大胃王
	int32_t			OnQueryDWWInfo( Answer::NetPacket *inPacket );
	int32_t			OnQueryDWWReward( Answer::NetPacket *inPacket );

	//七天登陆		
	int32_t			OnQuerySevenLoginInfo( Answer::NetPacket *inPacket );
	int32_t			OnGetSevenLoginRewrad( Answer::NetPacket *inPacket );

	//等级礼包
	int32_t			OnQueryLevelGiftInfo( Answer::NetPacket *inPacket );
	int32_t			OnGetLevelGift( Answer::NetPacket *inPacket );	

	//离线经验
	int32_t			OnQueryOffLineExpInfo( Answer::NetPacket *inPacket );
	int32_t			OnGetOffLineExp( Answer::NetPacket *inPacket );

	//经验找回
	int32_t			OnGetSearchBackReward( Answer::NetPacket *inPacket );
	int32_t			RecordEnterNumber( Answer::NetPacket *inPacket );

	//活动大厅数据
	int32_t			OnQueryHuoDaoDaTingData( Answer::NetPacket *inPacket );

public:
	void			SendDailyActivityInfo();
	void			GetDaWeiWangIcon( IconStateList& IconList );
	void			GetHuoDongDaTingIcon( IconStateList& IconList );
	void			GetJiangLiDaTingIcon( IconStateList& IconList );
	void			SendJiangLiDaTingIcon();
	void			SendHuoDongDaTingIcon();
	void			OnLevelUp();
	void			RecordEnterNumber( int32_t ActivityType, int32_t ActivityId );
	void			AddYesterdayRecord( int32_t ActivityType, int32_t ActivityId );
	int32_t			GetJoinActivityCount( int32_t Type );
	bool			TodayHaveJoineThisActivity( int32_t ActivityType, int32_t HuoDongId );
private:
	void			refreshSignInfo();
	void			sendSignInfo();
	bool			TodayIsSign();
	bool			HaveSignReward();

	int32_t			GetTodayOnLineTime();
	void			SendOnlineRewardInfo();
	bool			HaveOnLineReward();
	bool			HaveWeekReward();
	
	void			SendDWWInfo();
	void			SendDWWHDIcon();

	void			SendSevenLoginInfo();
	bool			HaveSevenLoginReward();

	void			SendLevelGiftInfo();
	bool			HaveLevelReward();

	int32_t			GetNewSeverWeek();
	int32_t			GetWeekOnlineTime();
	int32_t			GetLastWeekOnlineTime();
	void			refreshWeekTime();

	void			SendOffLineInfo();
	bool			HaveOffLineReard();

	bool			IsAlreadyGetSearchBackReward( int32_t Index );
	bool			HaveSearchBackReward();
	void			SendSearchBackInfo();
	SearchBackInfo  GetSearchBackInfo( int32_t Index );
	int32_t			GetActivityRecord( int32_t SearchBackType );
	void			DaySwitch( int32_t nDiffDays );

	ShowIcon		GetShowIconStu();
	void			SendHuoDaoDaTingData( int8_t Type );
	
	void			UpDateJiangLiDatingIcon( int64_t curTick );
	int32_t			HaveActivityRewardCount();

private:
	MemChrSignInfo	m_signInfo;
	int64_t			m_LastUpdate;
	int64_t			m_LastUpdateIcon;
	bool			m_IsLogin;

	JoinedActivityRecord	m_ActivityRecord;
};
#endif