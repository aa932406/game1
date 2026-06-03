#pragma once

#include <cmath>
#include <list>
#include <map>
#include <string>
#include <vector>
//class Player;
//class MonsterActivity;
//enum ACTIVITY_MSG
//{
//	MSG_MATCHONE,
//	MSG_MATCHTWO,
//	MSG_MATCHTHREE,
//	MSG_MATCHSC,
//};

enum DungeonState
{
	DS_FREE,			// 空闲
	DS_WAIT,			// 准备阶段
	DS_RUNNING,			// 进行中
	DS_WIN,				// 完成
	DS_FAIL,			// 失败
	DS_RESET,			// 需要重置
};

struct DungeonFinshInfo
{
	int32_t	kill_count;
	int32_t boss_count;
	int32_t escape_count;
	int32_t	get_exp;
	int32_t	lost_exp;
	int32_t	get_money;
	int32_t	normal_wave;
	int32_t	reward_wave;
};

//enum FamilyActivityState
//{
//	FAS_FREE,
//	FAS_RUNNING,
//	FAS_CAN_LEAVE,
//	FAS_MUST_LEAVE,
//	FAS_SUCESS,
//};

enum DungeonEventTriggerType
{
	DETT_TIME_LINE				= 1,	// 时间到达
	DETT_MONSTER_WAVE			= 2,	// 杀死特定波怪
	DETT_MONSTER_ID				= 3,	// 杀死某个怪
	DETT_MONSTER_WAVE_TIMELINE	= 4,	// 限时杀死怪
	DETT_PLANT_GATHER			= 5,	// 植物采集
	DETT_ARRIVE_AREA			= 6,	// 到达区域
	DETT_HP_PERCENT				= 7,	// 生命值
	DETT_MULTI_MONSTER_WAVE		= 8,	// 杀死多波怪
	DETT_PLAYER_DIE				= 9,	// 玩家死亡
};

enum DungeonEventEventType
{
	DEET_WIN			= 1,		// 副本通关
	DEET_FAIL			= 2,		// 副本失败
	DEET_ADD_MONSTER	= 3,		// 放置怪物
	DEET_ADD_TRAP		= 4,		// 放置陷阱
	DEET_ADD_PLANT		= 5,		// 放置采集物
	DEET_SHOW_MOVIE		= 6,		// 播放过场动画
	DEET_ACTIVE_EVENT	= 7,		// 打开事件
	DEET_REMOVE_MONSTER	= 8,		// 移除怪物
	DEET_ADD_TOWER		= 9,		// 预设置塔
	DEET_SET_WAIT_TIME	= 10,		// 插入准备阶段，结束后激活事件列表
	DEET_REWARD_RATIO	= 11,		// 调整奖励系数(*100)
	DEET_ADD_STACK		= 12,		// 添加障碍点
	DEET_REMOVE_STACK	= 13,		// 减少障碍点
};

enum HPEventType
{
	HPET_PLAYER = 1,
	HPET_MONSTER = 2, 
};

enum ActivityEventTriggerType
{
	AETT_TIME_LINE				= 1,	// 时间到达
	AETT_MONSTER_WAVE			= 2,	// 杀死特定波怪
	AETT_MULTI_MONSTER_WAVE		= 3,	// 杀死多波怪
	AETT_MONSTER_WAVE_TIMELINE	= 4,	// 限时杀死怪
	AETT_MONSTER_ID				= 5,	// 杀死某个怪
	AETT_PLANT_GATHER			= 6,	// 植物采集
	AETT_ARRIVE_AREA			= 7,	// 到达区域
	AETT_HP_PERCENT				= 8,	// 生命值
};

enum ActivityEventEffectType
{
	AEET_ADD_MONSTER	= 1,		// 放置怪物
	AEET_ADD_TRAP		= 2,		// 放置陷阱
	AEET_ADD_PLANT		= 3,		// 放置采集物
	AEET_ACTIVE_EVENT	= 4,		// 打开事件
	AEET_REMOVE_MONSTER	= 5,		// 移除怪物
	AEET_ADD_STACK		= 6,		// 添加碰撞
	AEET_REMOVE_STACK	= 7,		// 移除碰撞
	AEET_BROADCAST		= 8,		// 击杀公告
};


#define ACTICITY_MONSTER_ID_FAMILY_WAR_PILLAR	10003		// 军团战战神之柱
#define ACTICITY_MONSTER_ID_FAMILY_WAR_STON		10004		// 军团战圣战神石
#define ACTIVITY_FAMILY_WAR_BUFF_ID				126			// 失败BUFF
#define ACTIVITY_HORSE_RACING_BUFF_ID			136			// 飞天神驹buff

struct CfgMapEvent 
{
	int32_t		id;
	int32_t		mapid;
	int32_t		trigger_id;
	int32_t		trigger_type;
	Int32Vector	trigger_param;
	int32_t		event_type;
	std::string	effect;

	bool		bOpen;
	bool		bDone;
};
typedef std::list<CfgMapEvent> CfgMapEventList;
typedef std::map<int32_t, CfgMapEventList> CfgMapEventMap;
typedef std::map<int32_t, CfgMapEventMap> CfgMapEventTable;

