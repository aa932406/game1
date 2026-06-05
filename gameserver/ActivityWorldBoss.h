#ifndef __TPOC_ACTIVITY_WORLD_BOSS_H__
#define __TPOC_ACTIVITY_WORLD_BOSS_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"
#include <set>

class CActivityWorldBoss : public CActivity
{
public:
	struct PlayerScore
	{
		CharId_t	nCharId;
		std::string	strName;
		int32_t		nDamage;
		int32_t		nIndex;
		int64_t		nStartTick;
		bool		bInActivity;

		PlayerScore()
			: nCharId( 0 )
			, nDamage( 0 )
			, nIndex( 0 )
			, nStartTick( 0 )
			, bInActivity( false )
		{
		}
	};

	struct PlayerScoreRankGreater
	{
		bool operator()( const PlayerScore* _Left, const PlayerScore* _Right ) const
		{
			if ( _Left == NULL || _Right == NULL ) return false;
			if ( _Left->nDamage != _Right->nDamage )
				return _Left->nDamage > _Right->nDamage;
			return _Left->nStartTick < _Right->nStartTick;
		}
	};

	typedef std::map<CharId_t, PlayerScore>		PlayerScoreMap;
	typedef std::multiset<PlayerScore*, PlayerScoreRankGreater>	ScoreRankSet;

public:
	CActivityWorldBoss( const CfgActivity& cfgActivity );
	virtual ~CActivityWorldBoss();

	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );

	virtual void		SendPlayerActivityInfo( Player* player );
	virtual void		SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual int32_t		GetRevive( Player* player );
	virtual Position	GetRandBornPos( Player* player );
	virtual bool		OnSitRevive( Player* player );
	virtual int32_t		canEnter( Player* player, CActivityMap* pTargetMap ) const;

protected:
	virtual void	reset();
	virtual void	onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
	virtual void	onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, Player* pAttacker );
	virtual void	onMonsterAdd( MonsterActivity* pMonster );
	virtual void	onPlayerKilled( Player* pDier, Player* pKiller );
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual void	onTimeEnd();
	virtual Answer::NetPacket*	packetActivityScore();
	virtual void	broadcastStart();
	virtual void	broadcastEnd();
	virtual void	broadcastActivityResult();

private:
	void	addPlayerScore( Player* player, int32_t nDamage );
	void	sendPlayerScore( Player* player );
	void	addRewards();
	void	refreshRank();
	void	broadcastBossKilled( const std::string& name, CharId_t cid );
	int32_t	getAutoReviveTime( Player* player );
	const PlayerScore* getRankFirst() const;

	PlayerScoreMap	m_mPlayerScore;
	ScoreRankSet	m_sScoreRank;
	std::map<CharId_t, int32_t>	m_ReviveTimes;
	bool			m_IsBossDie;
};

#endif
