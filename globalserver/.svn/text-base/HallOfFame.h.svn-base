/*
* 名人堂
*/

#ifndef __TPOC_HALL_OF_FAME_H__
#define __TPOC_HALL_OF_FAME_H__

#include "SocialPlayer.h"

enum FAME_BATTLE_FORCE
{
	FBF_RAND	= 0,	// 随机
	FBF_WIN		= 1,	// 必胜
	FBF_FAIL	= 2,	// 必败
};

class FameFighter 
{
public:
	FameFighter( int32_t battle, int32_t tarBattle, bool bAtker );
	~FameFighter();

public:
	bool	Hurt( int32_t nDamage );
	int32_t Attack();
	int32_t	GetHP();

private:
	int32_t		nBattle;
	int32_t		nHP;
	int32_t		nHPMax;
	int32_t		nAtkMax;
	int32_t		nAtkMin;
};

class FameBattle
{
public:
	FameBattle( int32_t battle, int32_t tarBattle );
	~FameBattle();

public:
	bool Fight( Answer::NetPacket* packet, int8_t bForce = FBF_RAND );

private:
	bool isMiss();

private:
	FameFighter	m_atker;
	FameFighter	m_defer;
};

class CFamePlayer
{
public:
	CFamePlayer();
	~CFamePlayer();

public:
	void		ResetFighters();
	bool		IsTimesLimit() const;
	bool		CanFight( int32_t nIndex ) const;
	void		ResetLastIndex();
	void		SignReward( bool bSign=true );

public:
	CharId_t	nCharId;
	int32_t		nIndex;
	Int32List	vFighters;
	int32_t		nLastIndex;
	int8_t		nReward;
};
typedef std::map<CharId_t, CFamePlayer> FamePlayerMap;
/*
* 名人堂
*/
class CHallOfFameManager
{
public:
	CHallOfFameManager();
	virtual ~CHallOfFameManager();

public:
	void	Init();
	void	OnNewMinuteCome( int32_t minute );
	void	SendIconState( SocialPlayer* player );

public:
	int32_t	OnRequestInfo( SocialPlayer* player, Answer::NetPacket* inPacket );
	int32_t	OnFight( SocialPlayer* player, Answer::NetPacket* inPacket );
	int32_t	OnRequestRankInfo( SocialPlayer* player, Answer::NetPacket* inPacket );
	int32_t OnGetReward( SocialPlayer* player, Answer::NetPacket* inPacket );
	int32_t OnRewardResult( SocialPlayer* player, Answer::NetPacket* inPacket );

private:
	void	loadRank();
	void	loadChars();
	void	broadcastFight( CharId_t cid, const std::string& atker, const std::string& defer, int32_t nOldIndex, int32_t nNewIndex );
	void	broadcastTops();
	void	sendRankReward();
	void	saveIndex( int32_t nIndex );
	void	saveLastIndex();
	void	updateReward( int32_t nIndex );
	int32_t	firstFight( SocialPlayer* player, CFamePlayer& famePlayer,int32_t nIndex );

private:
	CFamePlayer*	m_vPlayer[HALL_OF_FAME_RANK_SIZE+1];
	FamePlayerMap	m_mPlayer;
};

#define HALL_OF_FAME Answer::Singleton<CHallOfFameManager>::instance()

#endif	// __TPOC_PET_MANAGER_H__
