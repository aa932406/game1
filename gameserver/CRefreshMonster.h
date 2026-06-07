#ifndef __C_REFRESH_MONSTER_H__
#define __C_REFRESH_MONSTER_H__

#include "stdafx.h"
#include "Activity.h"

class CRefreshMonster : public CActivity
{
public:
	CRefreshMonster( const CfgActivity& cfgActivity );
	~CRefreshMonster();

	virtual void	reset();
	virtual void	CheckActivity();
	virtual void	stopActivity();
	virtual void	broadcastStart();
	virtual void	broadcastEnd();

	void	FlushMonsters( int32_t NowTime );
	void	FreshObjGongGao( int32_t GongGaoId );

private:
	int32_t		m_StateTime;
};

#endif	//__C_REFRESH_MONSTER_H__
