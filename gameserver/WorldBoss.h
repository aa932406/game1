#ifndef __WORLD_BOSS_H__
#define __WORLD_BOSS_H__

#include "stdafx.h"
#include "CfgData.h"

class Map;
class Monster;
class Player;
class CfgMonster;
class CfgMapMonster;

#define ReviveTimeCount 4			// 蜘蛛女王每日复活时间点数量
const int32_t  ReviveTime[ReviveTimeCount] = { 630, 870,1110,1350 };
#define WarVictoryBossReviveTimeCount 2		//战争胜利boss复活时间点数量
const int32_t  WarVictoryBossReviveTime[WarVictoryBossReviveTimeCount] = { 1020,1290 };
#define REVIVE_TIME		30		// 蜘蛛女王复活窗口（分钟）
#define WAR_VICTORY_BOSS_REVIVE_TIME 120 //战争胜利boss复活窗口

// 击杀者信息（Top5 记录）
struct KillerInfo
{
	KillerInfo()
	{
		nCharId = 0;
		nTime = 0;
	}

	CharId_t	nCharId;
	std::string	strName;
	int32_t		nTime;
};

// 世界BOSS信息
class WorldBossInfo
{
public:
	WorldBossInfo()
	{
		nBossId		= 0;
		nLevel		= 1;
		nExp		= 0;
		nMid		= 0;
		nBossType	= 0;
		nMapId		= 0;
		nReviveTime	= 0;
		nState		= 0;
		for ( int32_t i = 0; i < 5; ++i )
		{
			vKiller[i].nCharId = 0;
			vKiller[i].strName = "";
			vKiller[i].nTime = 0;
		}
	}

	void PackageBossInfo( Answer::NetPacket* packet, int32_t nNowTime ) const;
	void AddKiller( const KillerInfo& info );

	int32_t		nBossId;			// bossId（对应 CfgMapMonster.id）
	int32_t		nLevel;				// 当前等级
	int32_t		nExp;				// 当前经验
	int32_t		nMid;				// 怪物模板ID
	int32_t		nBossType;			// BOSS 类型（boss_sign）
	int32_t		nMapId;				// 所在地图
	int32_t		nReviveTime;		// 下次复活时间（绝对时间戳）
	int8_t		nState;				// 0=存活, 1=已击杀(有击杀者), 2=已击杀(无击杀者)
	KillerInfo	vKiller[5];			// Top5 击杀者记录
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
	void			UpdateBossInfo( int32_t BossId, int32_t DieTime, CharId_t KillerId, std::string KillerName, int32_t ReviveTime = 0 );
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

	// ===== 反编译新增方法 =====
	int32_t			GetBossLevel( int32_t nBossId );
	void			OnBossSummon( int32_t nBossId, Monster* pMonster );
	void			OnBossKilled( int32_t nBossId, int32_t nNowTime, Monster* pMonster, Player* pKiller = NULL );
	void			broadcastBossKilled( int32_t nMid, const std::string& strKillerName, CharId_t nKillerId );
	void			broadcastBossRevive( int32_t nMid, int32_t nBossId, int32_t nMapId );
	int32_t			GetBossRevie( int32_t nBossId );

private:
	MonsterList		m_MonsterList;			// 蜘蛛女王列表
	BoosMap			m_mBossMap;				// BOSS信息映射（key=bossId）
	Monster*		m_WarVictoryBoss;		// 战争胜利BOSS
	int64_t			m_lastUpdateTick;
	Answer::Mutex	m_Lock;					// 线程锁（用于 m_mBossMap 访问）
};

#define WORLDBOSS Answer::Singleton<CWorldBoss>::instance()
#endif
