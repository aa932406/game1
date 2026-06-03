#ifndef __ZSZZ_DUNGEON_H__
#define __ZSZZ_DUNGEON_H__
#include "stdafx.h"
#include "SocialPlayer.h"
class DungeonRankInfo
{
public:
	DungeonRankInfo()
	{
		nCharId			= 0;
		nCharName		= "";
		nDungeonId		= 0;
	}

	bool operator < ( const DungeonRankInfo& stu ) const
	{
		return nDungeonId < stu.nDungeonId;
	}
	bool operator > ( const DungeonRankInfo& stu ) const
	{
		return nDungeonId > stu.nDungeonId;
	}
	CharId_t		nCharId;
	std::string		nCharName;
	int32_t			nDungeonId;
};

typedef std::vector<DungeonRankInfo> DungeonRankVct;

class ZSZZDungeonRank
{
public:
	ZSZZDungeonRank();
	~ZSZZDungeonRank();

public:
	void Init();
	void OnUpdateRankInfo( Answer::NetPacket* InPacket );
	void SortRank( DungeonRankVct& m_RankVt );
	void SendCharInfo( SocialPlayer* pPlayer );
private:
	DungeonRankVct  m_RankVt;
};
#define  ZSZZ_DUNGEON_RANK Answer::Singleton<ZSZZDungeonRank>::instance()
#endif