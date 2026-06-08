#pragma once

#include "Buff.h"

class Unit;

class SkillBuff
	: public Buff
{
public:
	SkillBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~SkillBuff();

public:
	virtual void effect();
	virtual void interval();
	virtual void restore();

	virtual bool deathClear();

	virtual int32_t getType() const;
	virtual int32_t getGroupId() const;
	virtual int32_t getLevel() const;

public:
	bool init(int32_t skillid, int32_t skilllevel, UnitHandle launcher, UnitHandle target);

private:
	void broadcastIntervalEffect(int32_t hpchange);

private:
	int32_t m_skillid;
	int32_t m_skilllevel;

};

