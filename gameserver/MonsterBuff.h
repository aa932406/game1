#pragma once

#include "Buff.h"

class MonsterBuff
	: public Buff
{
public:
	MonsterBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~MonsterBuff();

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
	BuffAttrAddon m_restore[2];
};

