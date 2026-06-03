#ifndef __DA_TI_HD_H__
#define __DA_TI_HD_H__
#include "stdafx.h"
#include "Activity.h"
#include "GameService.h"
class CDaTiHD:
	public CActivity
{
public:
	CDaTiHD( const CfgActivity& cfgActivity );
	~CDaTiHD();

	virtual void	Init();
	virtual void	reset();
	virtual void	CheckActivity();

	void	SendReadyStartDaTiHD();										//准备开始活动
	void	SendStartDaTiHD();											//开始答题
	void	SendEndDaTiHD();
	void	SendQuestionsInfo( int32_t NowSeconds );										//发送答题信息
	void	OnReceiveDaTiRank( Answer::NetPacket* InPacket );

private:
	void	RandomQuestions();
	void	RandAnswer();
private:

	int8_t	m_DaTiIndex;												//第几题
	int32_t	m_LastSendQuestions;										//最后发送答题时间
	QuestionsVector m_QuestionsVct;										//题目信息
	int8_t	m_RandAnswerDaTiIndex;	
	int8_t	m_IsSendReadyStartToCs;
};

#endif