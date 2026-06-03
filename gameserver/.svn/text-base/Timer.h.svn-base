/********************************************************
* 计时器线程											*
* 主要用来承载时间触发的事件，主要是各种游戏活动		*
* 2014.12.3												*
* robin													*
********************************************************/

#ifndef __TPOC_TIMER_H__
#define __TPOC_TIMER_H__

class CTimer
	: public Answer::Thread
{
public:
	CTimer();
	virtual ~CTimer();

protected:
	virtual void run();

public:
	void	Init();
	void	Start();
	void	Stop();

public:
	int64_t		GetTick();
	int32_t		GetNow();
	const tm&	GetLocalNow();

	int32_t		GetDaysFromStart();		// 开服到现在的日子
	int32_t		GetDaysFromUnite();		// 合服到现在的日子
	int8_t		GetWeekDay();
	bool		BetweenDate(int32_t begin_date, int32_t end_date);

private:
	void	checkNewMinute( const tm &localnow );
	void	checkAnnoucement(const tm &localnow);	//监视公告
	void	onDaySwitch();

private:
	bool	m_bRunning;
	int64_t	m_nTick;
	int32_t	m_nNow;
	tm		m_tmLocalNow;
	tm		m_tmLastLocalNow;		// 时间检测

	size_t	m_nextAnnoucement;		// 公告检测

//	int32_t	m_nDaysFromStart;		// 开服到现在的日子
//	int32_t	m_nDaysFromUnite;		// 合服到现在的日子
	int8_t	m_nWeekDay;				// 周几 1~7
};

#define TIMER Answer::Singleton<CTimer>::instance()

#endif	//__TPOC_TIMER_H__
