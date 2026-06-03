#pragma once

#include "Unit.h"

#include <vector>


#define SKILL_ID_FLY_HIT			14		// 飞天连斩技能ID
#define SKILL_ID_LIU_LIAN_ZHAN		13		//  六连斩
#define SKILL_ID_LONG_HUN_QIANG		204		// 龙枪葬魂 
#define SKILL_ID_DIVIDE				103		// 伤害评分技能
#define SKILL_PUBLIC_CD		500		// 技能共CD

class Skill
{
public:
	Skill(int32_t skillId,int32_t skillLevel);
	~Skill();

public:
	int32_t unitAction(Unit &launcher, UnitHandle targetHandle, int32_t &attackValue, Position srcPos=Position(), Position tarPos=Position() );	// 单体伤害
	int32_t unitResult(Unit &launcher, UnitHandle targetHandle, int32_t &attackValue);

	void posAction(Unit &launcher, Position pos, UnitVector &targets, EntityIdInt32Map &attackValues);	// 区域伤害
	void posResult(Unit &launcher, Position pos, UnitVector &targets, EntityIdInt32Map &attackValues);

	void calcDamage(Unit &launcher, Unit &target, int32_t &damge, SkillAttackState &attackState, int32_t &attackValue);

	void instantResult(Unit &launcher, Unit	&target, SkillResult &launcherResult, SkillResult &targetResult, int32_t &attackValue);

	void broadcastAction(Unit &launcher, const Position &targetPos, const UnitHandle &targetHandle, Position srcPos=Position(), Position tarPos=Position());
	void broadcastResult(Unit &launcherUnit, const SkillResult &launcherResult, const Position &targetPos, const SkillResult &targetResult);
	void broadcastResult(Unit &launcherUnit, const SkillResult &launcherResult, const Position &targetPos, const SkillResultVector &targetsResult);

private:
	CfgSkill *m_cfg;
	int32_t m_level;
};


