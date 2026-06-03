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
	int32_t		nKillCount;
	int32_t		nExp;
	int32_t		nMoney;
	int32_t		nJoinExp;
	int32_t		nSeconds;
	int64_t		nStartTick;
	bool		bInActivity;
};
typedef std::map<CharId_t, PlayerScore> PlayerScoreMap;

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

	bool	CanAddPillarMoney( Player* player ) const;
	int32_t	AddPillarMoney( int32_t nMoney );
	void	SendPlayerPillarInfo( Player* player );
	void	OnFamilyWarResult( FamilyId_t nFamilyId, int16_t nTimes, string FamilyName, string LeadyerName );


	FamilyId_t		GetWinFamily();
	std::string     GetFamilyName();
	std::string		GetFamilyLeaderName();

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
	void	addPlayerScore( Player* player, int32_t nExp, int32_t nMoney, int32_t nKillCount );
	void	addPlayerKillCount( Player* Player );
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

private:
	MonsterActivity*	m_pSton;				// 战神神石
	MonsterActivity*	m_pPillar;				// 战神之柱

	FamilyId_t			m_nGuidFamily;			// 防守军团
	int32_t				m_nWinTimes;			// 连胜次数
	FamilyScoreList		m_lstFamilyScore;		// 军团积分列表
	PlayerScoreMap		m_mPlayerScore;			// 玩家积分

	std::string			m_FamilyName;			// 首届军团战军团名字
	std::string			m_FamilyLeaderName;		// 首届军团长名字
};

//#define FAMILY_WAR Answer::Singleton<CFamilyWar>::instance()

#endif	//__TPOC_FAMILY_WAR_H__