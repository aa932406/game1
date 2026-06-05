#ifndef __TPOC_PEERLESS_WAR_H__
#define __TPOC_PEERLESS_WAR_H__

#include "stdafx.h"
#include "Activity.h"
#include <string>

class CPeerlessWar : public CActivity
{
public:
	struct PlayerScore
	{
		CharId_t	nCharId;
		std::string	strName;
		int32_t		nKillCount;
		int32_t		nReviveTimes;
		int32_t		nContKill;
		int32_t		nBroadCont;
		bool		bInActivity;

		PlayerScore()
			: nCharId( 0 )
			, nKillCount( 0 )
			, nReviveTimes( 0 )
			, nContKill( 0 )
			, nBroadCont( 0 )
			, bInActivity( false )
		{
		}
	};

	typedef std::map<CharId_t, PlayerScore> PlayerScoreMap;

public:
	CPeerlessWar( const CfgActivity& cfgActivity );
	virtual ~CPeerlessWar();

	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );

	virtual void		SendPlayerActivityInfo( Player* player );
	virtual void		SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual Position	GetRandBornPos( Player* player );
	virtual int32_t		GetRevive( Player* player );
	virtual int32_t		canEnter( Player* player, CActivityMap* pTargetMap ) const;

	void	SetPeerlessWarWinner( FamilyId_t nFamilyId );
	FamilyId_t	GetPeerlessWarWinner() const;
	void	OnPeerlessWarResult( CharId_t nWinnerId, const std::string& winnerName );
	int32_t	getLeftReviveTimes( Player* player );

protected:
	virtual void	reset();
	virtual void	onPlayerKilled( Player* pDier, Player* pAttacker );
	virtual void	onPlayerRevive( Player* player, bool bSafe );
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	virtual void	onTimeEnd();

private:
	void	addPlayerScore( Player* player, int32_t nScore );
	void	addRewards();
	void	addKillReward( CharId_t nCharId, int32_t nKillCount );
	void	addJoinReward( CharId_t nCharId );
	void	addWinnerReward();
	void	broadcastResult();
	void	broadcastReady();
	void	broadcastStart();
	void	broadcastKnockout( CharId_t nCharId, const std::string& name );
	void	broadcastConstKill( CharId_t nCharId, const std::string& name, int32_t nContKill );
	void	broadcastBreakConst( CharId_t nCharId, const std::string& name, CharId_t nKillerId, const std::string& killerName, int32_t nContKill );
	void	broadcastDraw();
	void	checkWin();
	void	win( CharId_t nWinnerId, const std::string& winnerName );
	void	draw();
	void	saveWarResult( int32_t nWinnerType );
	void	sendPlayerScore( Player* player );
	void	sendActivityResult( Player* player );
	Answer::NetPacket*	packetActivityScore();
	void	addPlayerKillCount( Player* player, int32_t nKillCount );
	void	clearOldTitle();

private:
	PlayerScoreMap	m_mPlayerScore;
	int64_t			m_nLastTick;
	int32_t			m_nWarState;
	CharId_t		m_nWinner;
	std::string		m_strWinnerName;
};

#endif
