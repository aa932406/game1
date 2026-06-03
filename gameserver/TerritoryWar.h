#ifndef __TPOC_TERRITORY_WAR_H__
#define __TPOC_TERRITORY_WAR_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"

enum TERRIORY_WAR_STATE
{
	TWS_NOT_START	= 0,		// 未开始
	TWS_READY		= 1,		// 准备进场
	TWS_START		= 2,		// 战斗中
	TWS_END			= 3,		// 结束
};

class CTerritoryWar
	: public CActivity
{
public:
	CTerritoryWar( const CfgActivity& cfgActivity, bool& special );
	virtual ~CTerritoryWar();

public:
	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );

	virtual void		SendPlayerActivityInfo( Player* player );
	virtual void		SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual Position	GetRandBornPos( Player* player );
	virtual bool		OnSitRevive( Player* player );
	virtual int32_t		GetRevive( Player* player );
	virtual int32_t		GiveDailyReward( Player* player );
	virtual bool		CanUseXP() const;

	void	OnTerritoryWarResult( std::string winners );
	void	AppendTerritoryWarInfo( Answer::NetPacket* packet, int32_t& nCount );

	virtual int32_t	HaveRewardCount( Player* Player );

protected:
	virtual void	reset();
	virtual bool	checkData();
	virtual bool	checkWeek();
	virtual void	onPlayerKilled( Player* pDier, Player* pAttacker );
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual int32_t	getNextStartTime();
	virtual void	broadcastActivityResult();
	virtual void	onActivityStart();
	virtual void	onTimeEnd();
	//virtual void	broadcastReady();
	virtual void	broadcastStart();
	//virtual Answer::NetPacket*	packetActivityScore();

private:
	void	win( TeamMemberList& winners );
	void	saveTerritoryWarResult();
	void	addRewards();
	bool	isDoubleReward() const;

	//Answer::NetPacket*	packetActivityFamilyScore();
	//Answer::NetPacket*	packetActivityPlayerScore( Player* player );

	void	broadcastWin();
	void	broadcastTerritoryStart();

	bool	checkWin();
	int32_t	getLeftReviveTimes( Player* player );
	void	changePKMode();
	void	setJoiner();
	bool	isWinner( CharId_t cid );

private:
	bool			m_bSpecialSign;		// 处理公告、活动图标标记
	int64_t			m_nLastTick;
	TeamMemberList	m_winners;
	int8_t			m_nTerritoryState;
	CharIdList		m_lstJoiner;
};

//#define FAMILY_WAR Answer::Singleton<CFamilyWar>::instance()

#endif	//__TPOC_TERRITORY_WAR_H__