#ifndef __SOCIAL_DA_TI_HD_H__
#define __SOCIAL_DA_TI_HD_H__
#include "stdafx.h"
#include "SocialPlayer.h"
enum DaTiState
{
	NOT_ANSWER		= 1,	//没有回答
	ANSWER_IS_WRONG = 2,	//答对了
	ANSWER_IS_RIGHT = 3,	//答错了
};
class DaTiHDInfo
{
public:
	DaTiHDInfo()
	{
		m_CharID			= 0;			
		m_Points			= 0;			
		m_Name				= "";				
		m_CostTime			= 0;			
		m_LastAnswerIndex	= 0;
		m_LastPoints		= 0;
		m_DaTiState			= NOT_ANSWER;
		m_LastAnswerId	    = 0;
	}

	bool operator > ( const DaTiHDInfo& stu ) const
	{
		return m_Points > stu.m_Points;
	}

	bool operator < ( const DaTiHDInfo& stu ) const
	{
		return m_Points < stu.m_Points;
	}

	CharId_t		m_CharID;			//主角id
	int32_t			m_Points;			//答题积分
	std::string		m_Name;				//玩家姓名
	int32_t			m_CostTime;			//消耗时间
	int8_t			m_LastAnswerIndex;	//最后回答的是第几题
	int32_t			m_LastPoints;		//这一题获得的积分
	int8_t			m_DaTiState;		//本题答题状态
	int8_t			m_LastAnswerId;		//选择的答案id
};

typedef std::vector<DaTiHDInfo> DaTiInofVct;

class CSocialDaTiHD
{
public:
	CSocialDaTiHD();
	~CSocialDaTiHD();
	void		Reset();
	int32_t		OnRecvHDReadyStart( Answer::NetPacket* InPacket );
	int32_t		OnRecvHDStart( Answer::NetPacket* InPacket );
	int32_t		OnRecvHDEnd( Answer::NetPacket* InPacket );
	int32_t		OnRecvQuestionsInfo( Answer::NetPacket* InPacket );
	int32_t		OnRecvRandAnswer();

	int32_t		OnReqAnswerQuestion( SocialPlayer* pPlayer, Answer::NetPacket* InPacket );			//回答问题
	
	int32_t	    SendLogInDaTiInfo( SocialPlayer* pPlayer );
	void		SendDaTiId( SocialPlayer* pPlayer );
private:
	void		SendAnswerResult( SocialPlayer* pPlayer, int32_t AddPoints, int8_t RightAnswer );
	void		SendRankInfo( SocialPlayer* pPlayer = NULL);												//发送前三名排行榜	
	void		SendCharReadyStart( SocialPlayer* pPlayer );
	void		SendQuestionsToClient( SocialPlayer* pPlayer = NULL );
	void		SendCharRankInfo( SocialPlayer* pPlayer );
	void		SendDaTiHDEndToGs();
	void		SendAnswered(SocialPlayer* pPlayer);			//发送参加过这次答题活动
	void		PickRankInfo( Answer::NetPacket *packet );
	int32_t		GetPoints( int32_t & DiffSeconds );
	int32_t		GetNowSeconds();
	void		SortRank( DaTiInofVct & DaTiInfo );
	void		SetHDState( int8_t State );
	int8_t		GetHDState();
private:
	int8_t		m_DaTiState;					//答题活动的状态
	int32_t		m_DaTiHDStartSeconds;			//答题活动开始的时间
	int32_t		m_QuestionsStartSeconds;		//这个问题开始的时间
	int8_t		m_QuestionsIndex;				//答题活动进行到第几题了
	int32_t		m_QuestionsId;					//问题id
	int8_t		m_AnswerId;						//问题答案id
	DaTiInofVct m_DaTiInfo;						//答题信息
	int32_t		m_HdId;
};

#define SOCIAL_DA_TI_HD Answer::Singleton<CSocialDaTiHD>::instance()

#endif