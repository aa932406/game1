//////////////////////////////////////////////////////////////////////////
// 活动主结构
// Update由Timer线程驱动，不能直接调用地图数据
// 涉及添加删除操作需要由地图驱动
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_ACTIVITY_H__
#define __TPOC_ACTIVITY_H__

#include "CfgData.h"
#include "actStructs.h"
#include "NpcActivity.h"

class MonsterActivity;
class CActivityMap;
class CActivity
{
friend class CActivityMap;
typedef std::list<CActivityMap*>	ActivityMapList;
public:
	CActivity( const CfgActivity& cfgActivity );
	virtual ~CActivity();

public:
	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );

public:
	int32_t	GetId() const;
	int16_t	GetType() const;
	int8_t	GetState() const;
	bool	IsRuning() const;
	void	GetIconState( IconStateList& iconList );

	virtual void	CheckActivity();	// 监视开启活动
	virtual void	SendPlayerActivityInfo( Player* player );
	virtual void	SendPlayerActivityState( Player* player );
	virtual void	SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual void	BroadcastActivityState();
	virtual void	BroadcastActivityScore( CActivityMap* pMap );
	virtual bool	OnSitRevive( Player* player );
	virtual int32_t GetRevive( Player* player );
	virtual int32_t	GiveDailyReward( Player* player );
	virtual bool	CanUseXP() const;
	virtual bool	CanUsePet( MapId_t mid ) const;
	virtual void	onPlantGather( Plant* pPlant, Player *player );
	virtual int32_t onBeginGather(  Plant* plant, Player *player );
	virtual void	AddPlant( Plant* plant );
	virtual Position	GetRandBornPos( Player* player );
	virtual int32_t	HaveRewardCount( Player* Player );
	virtual void	NotifyActivityInfo( Player* player );

protected:
	virtual void	reset();
	virtual	void	removePlayer( Player* player, bool islogout );
	virtual void	addPlayer( Player* player );
	virtual int32_t	canEnter( Player* player, CActivityMap* pTargetMap ) const;

	virtual void	onMonsterAdd( MonsterActivity* pMonster );
	virtual void	onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, Player* pAttacker );
	virtual void	onMonsterDie( MonsterActivity* pMonster );
	virtual void	onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
	virtual	void	onPlayerKilled( Player* pDier, Player* pKiller );
	virtual int32_t	getNextStartTime();
	virtual void	broadcastActivityResult();

	virtual void	onActivityStart();
	virtual void	onTimeEnd();

	virtual void	broadcastReady();
	virtual void	broadcastStart();

	virtual bool			checkData();
	virtual bool			checkWeek();
	virtual ACTIVITY_STATE	checkTime();
	virtual bool			checkLine();

	virtual Answer::NetPacket*	packetActivityScore();

	int32_t		getPkMode() const;
	bool		canRevive() const;
	Position	getBornRandPosA();
	Position	getBornRandPosB();
	Position	getBornRandPos( int32_t nMapId, const Int32Vector& regions );
	void		delayKickAll( int32_t nTime );

protected:
	virtual void	startActivity();	// 开始活动
	virtual void	stopActivity();		// 结束活动
	int32_t	getLeftTime();		// 获得剩余时间 
	int32_t	getActivityTime();	// 持续时间

	bool	needBroadcastActivityScore() const;
	void	setNeedBroadcastActivityScore();

protected:
	const CfgActivity&	m_cfgActivity;
	ACTIVITY_STATE		m_nState;
	ActivityMapList		m_activityMaps;
	PlayerList			m_players;
	int32_t				m_nKickTime;

	int32_t				m_nBraodcastActivityScoreSign;
	int64_t				m_nBroadcastActivityScoreTick;
};

#endif	//__TPOC_ACTIVITY_H__

