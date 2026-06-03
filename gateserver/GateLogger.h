#pragma once

class GateLogger
	: public Answer::Thread
{
public:
	GateLogger();
	virtual ~GateLogger();

protected:
	virtual void run();

public:
	void startLogger();
	void stopLogger();

private:
	void recordOnline();

private:
	bool m_bRunning;
	Answer::Mutex m_mutex;
	Answer::Condition m_cond;

	int32_t m_lastOnlineCountRecordTime;
};
#define GATE_LOGGER Answer::Singleton<GateLogger>::instance()

