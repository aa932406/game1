#pragma once

#include "Buff.h"

class DungeonBuff
	: public Buff
{
public:
	DungeonBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~DungeonBuff();

public:
	virtual bool expire();

	virtual void effect();
	virtual void interval();
	virtual void restore();

	virtual bool deathClear();

	virtual int32_t getType() const;
	virtual int32_t getGroupId() const;
	virtual int32_t getLevel() const;

public:
	void init();

private:
	AttrAddon m_restore[2];
};

