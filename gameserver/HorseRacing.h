#ifndef __TPOC_HORSE_RACING_H__
#define __TPOC_HORSE_RACING_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"

struct PlayerRank
{
	CharId_t	nCharId;
	std::string	strName;
};
typedef std::list<PlayerRank> PlayerRankList;

class CHorseRacing
	: public CActivity
{
public:
	CHorseRacing( const CfgActivity& cfgActivity );
	virtual ~CHorseRacing();

public:
	virtual void	SendPlayerActivityInfo( Player* player );
	virtual void	SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual bool	CanUseXP() const;
	virtual bool	CanUsePet( MapId_t mid ) const;
	virtual void	OnUpdate( CActivityMap* pMap );

protected:
	virtual void	reset();
	virtual void	sendActivityResult( Player* player );
	virtual void	onTimeEnd();
	virtual void	broadcastReady();
	virtual void	broadcastStart();
	virtual	void	removePlayer( Player* player, bool islogout );
	virtual void	addPlayer( Player* player );
	virtual int32_t	canEnter( Player* player, CActivityMap* pTargetMap ) const;

	virtual Answer::NetPacket*	packetActivityScore();

private:
	void	win( Player* Player );
	void	broadcastWin( Player* player );
	void	addReward( Player* player );
	bool	bArrived( CharId_t cid ) const;

private:
	int32_t			m_nIndex;			// 名次
	PlayerRankList	m_rankList;			// 胜利列表
	PlayerList		m_racing;			// 参赛选手
	PlayerList		m_winner;			// 胜利选手
};


#endif	//__TPOC_HORSE_RACING_H__