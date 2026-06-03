#ifndef __ACHIEVEMENT_H__
#define __ACHIEVEMENT_H__
#include "ExtSystemBase.h"

enum AchievementTaskState
{
	ATS_NO_FINISH	= 0,	 //未完成
	ATS_FINISH		= 1,	 //完成
	ATS_GET_REWARD	= 2,	 //奖励以领取
};

class CAchievement
	:public CExtSystemBase
{
public:
	CAchievement();
	~CAchievement();
	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
private:
	int32_t			OnGetAchievemnetReward( Answer::NetPacket * inPacket );
	int32_t			OnBuyXunZhangSocre( Answer::NetPacket * inPacket );
public:
	void	AddAchievement( int8_t GroupId, int32_t Effect = 0, int32_t HuoDongId = 0 );
	void	SendAchievementInfo();
	void	SendFinishAchievement( std::list<int32_t> FinishList );
private:
	AchievementMap	m_AchievementMap;
};

#endif
