#pragma once

#include "CfgData.h"

#include <list>

class Unit;

enum BuffType
{
	BT_ITEM,
	BT_SKILL,
	BT_PERSIST,
	BT_DUNGEON,
	BT_MONSTER,
	BT_WARFIELDARTIFACT,
	BT_MAGICWEAPON,
};

//enum BuffState
//{
//	BS_XUANYUN = 1,//眩晕
//	BS_WUDI,//无敌
//	BS_PERSIST_HP,//持续回血
//	BS_BINGDONG,//冰冻
//	BS_SLOW,//迟缓
//	BS_CONFUSION,//混乱
//	BS_WEAK,//虚弱
//	BS_BURN,//灼伤
//	BS_REBOUND,//反弹
//	BS_EXCITE,//兴奋
//	BS_ANTI_JUMP,
//	BS_BATEPDEF, // 物理防御减弱
//	BS_BATEMDEF, // 法术防御减弱
//	BS_BATEHITP, // 减命中
//	BS_BATEDP, // 减闪避
//	BS_HERO_DUNGEON_MONSTER, //英雄副本怪物加状态
//	BS_BUFF_STATE_MAX,
//};

enum SkillSpecial
{
	SS_NONE			= 0,
	SS_SHUNYI		= 1,	// 移位
	SS_XUANYUN		= 2,	// 眩晕
	SS_WUDI			= 3,	// 无敌
	SS_PERSIST_HP	= 4,	// 持续回血
	SS_BINGDONG		= 5,	// 冰冻
	SS_SLOW			= 6,	// 迟缓
	SS_CONFUSION	= 7,	// 混乱
	SS_WEAK			= 8,	// 虚弱
	SS_BURN			= 9,	// 灼伤
	SS_EXCITE		= 10,	// 兴奋
	SS_FUHUO		= 11,	// 复活
	SS_ANTI_JUMP	= 12,
	SS_JUMP			= 21,
	SS_SHAKE		= 22,
	SS_PULL			= 23,
	SS_HIT			= 24,
	SS_KICKOUT		= 25,
	SS_SPEED_UP		= 26,	//加速
	SS_DIVIDE		= 28,	//伤害评分
	SS_CLEAR = 100,			//清除异常状态	
};

struct BuffAttrAddon 
{
	int32_t index;
	int32_t ratio;
	int32_t addon;
};

class Buff
{
public:
	Buff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~Buff();

public:
	int32_t remainTick();
	int32_t getId();
	bool beneficial();
	int32_t getSpecial();
	CfgBuff& getCfgBuff();
	bool	NeedShow();

public:
	virtual bool expire();

	virtual void effect() = 0;
	virtual void interval() = 0;
	virtual void restore() = 0;

	virtual bool deathClear() = 0;

	virtual int32_t getType() const = 0;
	virtual int32_t getGroupId() const = 0;
	virtual int32_t getLevel() const = 0;

protected:
	Unit &m_unit;
	CfgBuff &m_cfgBuff;

	int64_t m_endTick;
	int64_t m_lastEffectTick;
};
typedef std::list<Buff*> BuffList;
