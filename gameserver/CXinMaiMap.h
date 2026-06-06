#ifndef __C_XIN_MAI_MAP_H__
#define __C_XIN_MAI_MAP_H__

#include "stdafx.h"
#include "Activity.h"
#include <map>

class MonsterActivity;

class CXinMaiMap : public CActivity
{
public:
	CXinMaiMap( const CfgActivity& cfgActivity );
	~CXinMaiMap();

	virtual void	OnUpdate( CActivityMap* pMap );

	virtual void	reset();
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual int32_t	canEnter( Player* player, CActivityMap* pTargetMap ) const;
	virtual bool	OnSitRevive( Player* player );
	virtual void	onPlayerKilled( Player* pDier, Player* pKiller );
	virtual void	onMonsterAdd( MonsterActivity* pMonster );
	virtual void	onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
	virtual int32_t	onBeginGather( Plant* plant, Player* player );
	virtual void	onPlantGather( Plant* pPlant, Player* player );

	virtual void	sendPlayerScore( Player* player );
	virtual void	onTimeEnd();
	virtual void	broadcastReady();
	virtual void	broadcastStart();
	virtual bool	alwaysShowIcon();

private:
	std::map<int64_t, MonsterActivity*>	m_MonsterActivityMap;
	MonsterActivity*					m_pLastBoss;
	int32_t								m_LeftTime;
	std::map<int64_t, int32_t>			m_ReviveTimes;
};

#endif	//__C_XIN_MAI_MAP_H__
