#ifndef __TPOC_FAMILY_WAR_H__
#define __TPOC_FAMILY_WAR_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"

struct FamilyScore 
{
	FamilyId_t	nFamilyId;
	std::string	strFamilyName;
	int32_t		nScore;
	int32_t		nUsedScore;
	int32_t		nActivePillar;

	bool operator<( const FamilyScore& _right ) const
	{
		return nScore < _right.nScore;
	}

	bool operator>( const FamilyScore& _right ) const
	{
		return nScore > _right.nScore;
	}
};
typedef std::list<FamilyScore> FamilyScoreList;

struct PlayerScore 
{
	CharId_t	nCharId;
	FamilyId_t	nFamilyId;
	std::string	strName;
	int32_t		nScore;
	int32_t		nKillCount;
	int32_t		nTaskId;
	int32_t		nTaskCount;
	int64_t		nStartTick;
	bool		bInActivity;

	bool operator>( const PlayerScore& _right ) const
	{
		return nScore > _right.nScore;
	}

	PlayerScore() : nCharId(0), nFamilyId(0), nScore(0), nKillCount(0),
		nTaskId(0), nTaskCount(0), nStartTick(0), bInActivity(false) {}
};
typedef std::list<PlayerScore> PlayerScoreList;

class CFamilyWar
	: public CActivity
{
public:
	CFamilyWar( const CfgActivity& cfgActivity );
	virtual ~CFamilyWar();

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
	virtual int32_t		HaveRewardCount( Player* Player );
	virtual void		NotifyActivityInfo( Player* pPlayer = NULL );
	virtual int32_t		canEnter( Player* player, CActivityMap* pTargetMap ) const;

	bool	CanAddPillarMoney( Player* player ) const;
	int32_t	AddPillarMoney( int32_t nMoney );
	void	SendPlayerPillarInfo( Player* player );
	void	OnFamilyWarResult( FamilyId_t nFamilyId, int16_t nTimes, string FamilyName, string LeadyerName );

	FamilyId_t		GetWinFamily();
	std::string     GetFamilyName();
	std::string		GetFamilyLeaderName();

	// ========== 新版本方法 ==========
	void	AdjustMonsterAttr( CfgMonster* cfgMonster );
	bool	OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t param );
	bool	OnActivePillar( Player* player, int32_t nIndex );
	void	OnTaskSubmited( Player* player, int32_t nScore );
	int32_t	GetActivePillar( FamilyId_t nFamilyId );
	PlayerScore* getPlayerScore( CharId_t nCharId );
	FamilyScore* getFamilyScore( FamilyId_t nFamilyId );

protected:
	virtual void	reset();
	virtual bool	checkData();
	virtual bool	checkWeek();
	virtual void	onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, Player* pAttacker );
	virtual void	onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
	virtual void	onPlayerKilled( Player* pDier, Player* pAttacker );
	virtual void	onMonsterAdd( MonsterActivity* pMonster );
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual int32_t	getNextStartTime();
	virtual void	broadcastActivityResult();
	virtual void	onTimeEnd();
	virtual void	broadcastReady();
	virtual void	broadcastStart();
	virtual Answer::NetPacket*	packetActivityScore();
private:
	void	addPlayerScore( Player* player, int32_t nScore, int32_t nKillCount );
	void	addFamilyScore( FamilyId_t nFamilyId, const std::string& strFamilyName, int32_t nScore );
	void	win( FamilyId_t nFamilyId );
	void	saveFamilyWarResult();
	void	addRewards();
	bool	isDoubleReward() const;
	bool	isShowDoubleReward();

	Answer::NetPacket*	packetActivityFamilyScore();
	Answer::NetPacket*	packetActivityPlayerScore( Player* player );

	void	broadcastPillerKilled( FamilyId_t nFamilyId );
	void	broadcastStoneKilled();
	void	broadcastWin();
	void	addBuff( Player* player );
	void	removeBuff( Player* player );
	int32_t	getBuffLevel() const;
	void	FirstFamilyWar( FamilyId_t FamilyId );

	// ========== 新版本方法 ==========
	void	sendPlayerScoreRankReward();
	void	sendFamilyScoreRankReward();
	void	sendActivePillarReward( FamilyId_t nFamilyId );
	void	sendWinnerReward( FamilyId_t nFamilyId );
	void	appendPlayerScoreRank( Answer::NetPacket* packet );
	void	appendFamilyScoreRank( Answer::NetPacket* packet );
	void	sendPlayerScore( Player* player );

private:
	MonsterActivity*	m_pSton;			// 防守基石
	MonsterActivity*	m_pPillar;			// 防守之柱
	MonsterActivity*	m_pTitle;			// 称号怪物
	MonsterActivity*	m_pBoss;			// Boss怪物

	Player*				m_pBuffPlayer;		// 持有Buff的玩家
	int64_t				m_nBuffStartTick;	// Buff开始时间

	FamilyId_t			m_nGuidFamily;		// 获胜家族
	int32_t				m_nWinTimes;		// 获胜次数
	FamilyScoreList		m_lstFamilyScore;	// 家族积分列表
	PlayerScoreList		m_lstPlayerScore;	// 玩家积分列表
	int32_t				m_nActiveState;		// 活跃状态
	int32_t				m_nActivePillarState; // 柱子激活状态(bitmask)

	std::string			m_FamilyName;		// 首届家族战获胜家族
	std::string			m_FamilyLeaderName;	// 首届家族战获胜族长
};

#endif	//__TPOC_FAMILY_WAR_H__
