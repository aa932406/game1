#pragma once

class LogParser
	: public Answer::Thread
{
public:
	LogParser();
	virtual ~LogParser();

protected:
	virtual void run();

public:
	void startParse();
	void stopParse();

private:
	void dailyReport();
	void hourlyReport();

private:
	bool m_bRunning;
	Answer::Mutex m_mutex;
	Answer::Condition m_cond;
};
#define LOG_PARSER Answer::Singleton<LogParser>::instance()
