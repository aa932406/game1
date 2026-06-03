#ifndef __WORLD_BOSS_H__
#define __WORLD_BOSS_H__

#include "stdafx.h"
#include "CfgData.h"

#define ReviveTimeCount 4		// 蜘蛛女王复活时间的个数
const int32_t  ReviveTime[ReviveTimeCount] = { 630, 870,1110,1350 };
#define WarVictoryBossReviveTimeCount 2		//抗战胜利boss复活时间个数
const int32_t  WarVictoryBossReviveTime[WarVictoryBossReviveTimeCount] = { 1020,1290 };
#define REVIVE_TIME		30		// 蜘蛛女王存活时间
#define WAR_VICTORY_BOSS_REVIVE_TIME 120 //抗战胜利boss存活时间

class WorldBossInfo
{
public:
	WorldBossInfo()
	{
		BossId			= 0;		
		BossType		= 0;	
		MapId			= 0;		
		DieTime			= 0;	
		ReviveTimes		= 0;
		KillerId		= 0;	
		KillerName		= "";
		Mid				= 0;
	}

	int32_t		BossId;			// bossId
	int32_t     Mid;			// Mid
	int32_t		BossType;		// boss类型
	int32_t		MapId;			// boss所在地图
	int32_t		DieTime;		// 死亡时间
	int32_t		ReviveTimes;	// 复活间隔
	CharId_t	KillerId;		// 杀死者id
	std::string KillerName;		// 杀死者name
};

typedef std::map<int32_t, WorldBossInfo> BoosMap;

class CWorldBoss
{
public:
	CWorldBoss();
	~CWorldBoss();
	
public:
	void			Init();
	Position		GetRevivePos( int32_t BossId );
	void			PacketBossInfo( Answer::NetPacket *packet, int8_t BossType );
	void			PacketBossHomeInfo( Answer::NetPacket *packet, int32_t MapId );
	void			UpdateBossInfo(  int32_t BossId, int32_t DieTime, CharId_t KillerId, std::string KillerName, int32_t ReviveTime = 0 );
	void			GongGao( int32_t DieTime, int32_t Mid, int32_t BossId, std::string KillerName, int32_t MapId, CharId_t KillerId );
	void			GetWorldBossIcon( IconStateList& IconList );
	void			SendWorldBossIcon( Player *pPlayer );
	bool			IsInHuoDongTiem();
	int32_t			GetSpiderQueenReviveTime();
	void			KillAllSpiderQueen();
	bool			IsAllSpiderQueenDie();
	void			AddMonst( Monster* pMonster );
	int32_t			GetBossRevieTime( int32_t BossId );
	void			AddWarVictoryBoss( Monster* pMonster );
	bool			IsWarVictoryBossTime();
	void			KillWarVictoryBoss();
	void			Update( int64_t CurTick );
	void			GongGao( int32_t GongGaoId, Player* pPlayer = NULL );

private:
	MonsterList		m_MonsterList;				//蜘蛛女王
	BoosMap			m_BossMap; 
	Monster*		m_WarVictoryBoss;			//抗战胜利boss
	int64_t			m_lastUpdateTick;	
};

#define WORLDBOSS Answer::Singleton<CWorldBoss>::instance()
#endif