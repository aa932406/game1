#ifndef __TPOC_CITY_WAR_H__
#define __TPOC_CITY_WAR_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"

struct CityWarPlayerScore
{
	CharId_t	nCharId;
	FamilyId_t	nFamilyId;
	std::string	strName;
	int32_t		nScore;
	int32_t		nScoreTime;
	int32_t		nCamp;
	int8_t		nActivityState;
	int32_t		nSessionTime;
	bool		bInActivity;

	CityWarPlayerScore()
		: nCharId( 0 )
		, nFamilyId( 0 )
		, nScore( 0 )
		, nScoreTime( 0 )
		, nCamp( 0 )
		, nActivityState( 0 )
		, nSessionTime( 0 )
		, bInActivity( false )
	{
	}
};
typedef std::map<CharId_t, CityWarPlayerScore> CityWarPlayerScoreMap;

struct CityWarFamilyScore
{
	FamilyId_t	nFamilyId;
	std::string	strName;
	int32_t		nScore;
	int32_t		nScoreTime;
	int32_t		nCamp;
	bool		bUpdateScroeRank;

	CityWarFamilyScore()
		: nFamilyId( 0 )
		, nScore( 0 )
		, nScoreTime( 0 )
		, nCamp( 0 )
		, bUpdateScroeRank( false )
	{
	}
};
typedef std::list<CityWarFamilyScore*> CityWarFamilyScorePtrList;
typedef std::map<FamilyId_t, CityWarFamilyScore> CityWarFamilyScoreMap;

struct CityWarApply
{
	FamilyId_t	nFamilyId;
	std::string	strLeaderName;
	int32_t		nMemberCount;

	CityWarApply()
		: nFamilyId( 0 )
		, nMemberCount( 0 )
	{
	}
};
typedef std::map<FamilyId_t, CityWarApply> CityWarApplyMap;

class CCityWar
	: public CActivity
{
public:
	CCityWar( const CfgActivity& cfgActivity );
	virtual ~CCityWar();

public:
	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );

	virtual void		SendPlayerActivityInfo( Player* player );
	virtual void		SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual Position	GetRandBornPos( Player* player );
	virtual bool		OnSitRevive( Player* player );
	virtual int32_t		GetRevive( Player* player );
	virtual int32_t		canEnter( Player* player, CActivityMap* pTargetMap ) const;

	void	GetFamilyMembers( FamilyId_t nFamilyId, CharIdList& cids );
	void	OnCityWarResult( FamilyId_t nWinnerId, const std::string& winnerName );
	bool	ApplyCityWar( Player* player );

	int8_t	GetFamilyCamp( FamilyId_t nFamilyId );
	FamilyId_t	GetGuilDerFirstFamily();
	bool	isSpecialDay( int32_t nStartDays );
	bool	isInSpecialDay( int32_t nStartDays );
	bool	HaveOwner();

protected:
	virtual void	reset();
	virtual bool	checkData();
	virtual bool	checkWeek();
	virtual void	onPlayerKilled( Player* pDier, Player* pAttacker );
	virtual void	onMonsterDie( MonsterActivity* pMonster, Player* pKiller );
	virtual void	onMonsterAdd( MonsterActivity* pMonster );
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual void	onTimeEnd();
	virtual void	onActivityStart();
	virtual int32_t	getNextStartTime();
	virtual bool	OnChangeMap( Player* player, CActivityMap* pMap, int32_t nX, int32_t nY, int32_t Param );
	virtual Answer::NetPacket*	packetActivityScore();

private:
	void	addPlayerScore( Player* player, int32_t nScore );
	void	addFamilyScore( FamilyId_t nFamilyId, const std::string& strFamilyName, int32_t nScore, int32_t nScoreTime );
	void	win();
	void	addRewards();
	void	saveResult();
	void	checkChangeFamily( bool bUpdateScore );
	void	SetOwner();
	void	NotOccupyGongGao();
	void	GongGao( int32_t nGongGaoId );
	void	setUpdateScoreRank( FamilyId_t nFamilyId );
	void	SaveApplyInfo();
	void	AutoApplyCityWar();
	void	SendAppyCityWarInfo( Player* player );
	bool	canGetOnlineReward( Player* player );
	void	appendPlayerRankInfo( Answer::NetPacket* packet, FamilyId_t nFamilyId, int32_t nRank );
	void	broadcastReady();
	void	broadcastStart();
	void	broadcastRankInfo();
	void	broadcastResult();

	Answer::NetPacket*	packetActivityFamilyScore();
	Answer::NetPacket*	packetActivityPlayerScore( Player* player );

private:
	CityWarFamilyScoreMap	m_mFamilyScore;
	CityWarPlayerScoreMap	m_mPlayerScore;
	CityWarFamilyScorePtrList	m_lFamilyScore;
	CityWarApplyMap			m_Apply;

	MonsterActivity*	m_pMonster;
	int32_t				m_nIndex;
	FamilyId_t			m_nFamilyId;
	FamilyId_t			m_nLastFamilyId;
	int32_t				m_nWinTime;
	CharId_t			m_Leader;
	bool				m_bUpdateFamilyScroe;
	int64_t				m_nLastUpdateRankTick;

	// Top 3 family scores and names
	int32_t		m_First;
	int32_t		m_Second;
	int32_t		m_Third;
	int32_t		m_FirstTime;
	int32_t		m_SecondTime;
	int32_t		m_ThirdTime;
	std::string	m_FirstFamilyName;
	std::string	m_SecondFamilyName;
	std::string	m_ThirdFamilyName;
};

#endif	//__TPOC_CITY_WAR_H__
