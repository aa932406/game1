#ifndef __SPIDER_QUEEN_H__
#define __SPIDER_QUEEN_H__
#include "stdafx.h"
#include "Activity.h"
class CSqiderQueen
	:public CActivity
{
public:
	CSqiderQueen( const CfgActivity& cfgActivity );
	~CSqiderQueen();
	
	void StopActivityBySqiderQueenDie();

protected:
	virtual void stopActivity();
	virtual void broadcastStart();
	virtual void broadcastTimeEnd();
	virtual void broadcastKillAllSqiderQueen();
};

#endif //__SPIDER_QUEEN_H__