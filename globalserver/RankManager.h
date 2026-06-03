/*
* 排行榜数据管理
*/

#ifndef __TPOC_RANK_MANAGER_H__
#define __TPOC_RANK_MANAGER_H__

#include "DataStructs.h"

#define RANK_SIZE	100
enum RANK_TYPE
{
	RT_PLAYER_BATTLE	= 1,
	RT_PLAYER_LEVEL		= 2,
	RT_PET_POINTS		= 3,
	RT_PLAYER_GUAN_WEI  = 4,
	RT_INSID_PET_POINTS	= 5,
};

struct AllPetPointsRankGreater	 {	bool operator()( const PetRankData& _Left, const PetRankData& _Right ) const;	};
struct PlayerBattleRankGreater	 {	bool operator()( const PlayerInfo& _Left, const PlayerInfo& _Right ) const;		};
struct PlayerLevelRankGreater	 {	bool operator()( const PlayerInfo& _Left, const PlayerInfo& _Right ) const;		};
struct InsidePetPointsRankGreater{  bool operator()( const PetRankData& _Left, const PetRankData& _Right ) const;	};
struct PlayerGuanWeiRankGreater  {  bool operator()( const PlayerInfo& _Left, const PlayerInfo& _Right ) const;     };
class CRankManager
{
public:
	CRankManager();
	virtual ~CRankManager();

public:
	void			Init();
	void			NewMinuteCome( int32_t nMinute, int32_t nNowTime );
	void			SendGameRank( int8_t rt, uint16_t nIndex );

private:
	void			refreshPlayerRank();
	void			refreshPetRank();

	void			sendPlayerBattleRank( uint16_t nIndex );
	void			sendPlayerLevelRank( uint16_t nIndex );
	void			sendPetPointsRank( uint16_t nIndex );
	void			sendPetInsidePetPointsRank( uint16_t nIndex );
	void			sendPlayerGuanWeiRank( uint16_t nIndex );
	void			SynRank( int8_t Type, int32_t nMinute );

private:
	PlayerInfoVt		m_vPlayerBattleRank;			// 等级排行榜
	PlayerInfoVt		m_vPlayerLevelRank;				// 战斗力排行榜
	PetRankDataVector	m_vPetPointsRank;				// 宠物星级排行榜
	PetRankDataVector	m_vInsidePetPointsRank;			// 内置宠物星级排行榜
	PlayerInfoVt		m_vPlayerGuanWeiRank;			// 官位排行榜
	int32_t				m_nRefreshTime;
};

#define RANK_MANAGER Answer::Singleton<CRankManager>::instance()

#endif	// __TPOC_RANK_MANAGER_H__
