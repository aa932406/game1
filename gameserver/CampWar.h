#ifndef __TPOC_CAMP_WAR_H__
#define __TPOC_CAMP_WAR_H__

#include "stdafx.h"
#include "Activity.h"
#include <set>

class PlantActivity;

class CCampWar : public CActivity
{
public:
	struct PlayerScore
	{
		CharId_t	nCharId;
		int32_t		nRankIndex;
		int32_t		nPoints;
		int32_t		nKillCount;
		int32_t		nCamp;
		int32_t		nContKill;
		int32_t		nContLevel;
		bool		bInActivity;
		int32_t		nAddTime;
		std::string	strName;

		PlayerScore()
			: nCharId( 0 )
			, nRankIndex( 0 )
			, nPoints( 0 )
			, nKillCount( 0 )
			, nCamp( 0 )
			, nContKill( 0 )
			, nContLevel( 0 )
			, bInActivity( false )
			, nAddTime( 0 )
		{
		}
	};

	struct PlayerScoreGreater
	{
		bool operator()( const PlayerScore* left, const PlayerScore* right ) const
		{
			if ( left == NULL || right == NULL ) return false;
			if ( left->nPoints != right->nPoints )
				return left->nPoints > right->nPoints;
			return left->nCharId < right->nCharId;
		}
	};

	typedef std::map<CharId_t, PlayerScore> PlayerScoreMap;
	typedef std::set<PlayerScore*, PlayerScoreGreater> ScoreRankSet;

public:
	CCampWar( const CfgActivity& cfgActivity );
	virtual ~CCampWar();

	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );

	virtual void		SendPlayerActivityInfo( Player* player );
	virtual void		SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual Position	GetRandBornPos( Player* player );
	virtual int32_t		GetRevive( Player* player );
	virtual int32_t		canEnter( Player* player, CActivityMap* pTargetMap ) const;

protected:
	virtual void	reset();
	virtual bool	checkData();
	virtual bool	checkWeek();
	virtual void	onPlayerKilled( Player* pDier, Player* pAttacker );
	virtual void	onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
	virtual void	onPlayerRevive( Player* player, bool bSafe );
	virtual void	onBeginGather( PlantActivity* pPlant, Player* player );
	virtual void	onPlantGather( PlantActivity* pPlant, Player* player );
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual void	onTimeEnd();
	virtual Answer::NetPacket*	packetActivityScore();

private:
	void	addPlayerScore( Player* player, int32_t nPoint, int32_t nKillCount );
	void	addRewards();
	void	addKillReward( CharId_t nCharId, int32_t nKillCount );
	void	checkCampWinner();
	void	broadcastCampResult();
	void	broadcastReady();
	void	broadcastStart();
	void	broadcastContKill( CharId_t nCharId, const std::string& name, int32_t nContKill );
	void	broadcastBreakContKill( const std::string& victimName, CharId_t nVictimId, const std::string& killerName, CharId_t nKillerId, int32_t nContKill );
	void	broadcastActivityResult();
	void	RefreshBuff( int32_t nBuffId, int8_t nCampId );
	void	selectCamp( Player* player, int32_t& nCamp );
	int32_t	getContTitle( int32_t nContLevel );
	void	notifyAddScore( Player* player, int32_t nPoint, int32_t nType );
	void	refreshRankIndex( CharId_t nCharId );
	void	sendPlayerScore( Player* player );
	void	SendPlayerRankInfo( Player* player );

private:
	PlayerScoreMap	m_mPlayerScore;
	ScoreRankSet	m_sScoreRank;
	std::map<int,int>	m_BuffIdMap;	// buffId -> campId
	int64_t			m_nLastTime;
	int32_t			m_Camp_1_battle;
	int32_t			m_Camp_2_battle;
};

#endif
