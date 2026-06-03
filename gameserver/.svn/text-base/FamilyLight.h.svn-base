#ifndef __TPOC_FAMILY_LIGHT_H__
#define __TPOC_FAMILY_LIGHT_H__

#include "stdafx.h"
#include "Activity.h"
#include "MonsterActivity.h"

enum FAMILY_LIGHT_AREA
{
	FLA_NORMAL	= 0,
	FLA_BLUE	= 1,
	FLA_RED		= 2,
};

class CFamilyLight
	: public CActivity
{
	struct PlayerScore 
	{
		CharId_t	nCharId;
		int32_t		nExp;
		int32_t		nArea;
		int32_t		nItemEndTime;
		bool		bInActivity;
		int64_t		nLastTick;
	};
	typedef std::map<CharId_t, PlayerScore> PlayerScoreMap;
public:
	CFamilyLight( const CfgActivity& cfgActivity );
	virtual ~CFamilyLight();

public:
	virtual void Init();
	virtual void OnUpdate( CActivityMap* pMap );
	virtual void SendPlayerActivityScore( Player* player, int32_t nLeftTime );
	virtual bool CanUseXP() const;
	virtual bool OnSitRevive( Player* player );

	bool	DrinkWine( Player* player, int32_t Count );

protected:
	virtual void	reset();
//	virtual bool	checkData();
	virtual void	addPlayer( Player* player );
	virtual void	removePlayer( Player* player, bool islogout );
	//virtual void	broadcastReady();
	//virtual void	broadcastStart();
	virtual void	onTimeEnd();

private:
	int32_t	checkArea( const Position& pos );
	int32_t	getExpRate( Player* player, const PlayerScore& score );

private:
	PlayerScoreMap		m_mPlayerScore;			// Íæ¼Ò»ý·Ö
};

//#define FAMILY_WAR Answer::Singleton<CFamilyWar>::instance()

#endif	//__TPOC_FAMILY_LIGHT_H__