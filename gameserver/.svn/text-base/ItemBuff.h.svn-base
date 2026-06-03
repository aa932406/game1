#pragma once

#include "Buff.h"

class ItemBuff
	: public Buff
{
public:
	ItemBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~ItemBuff();

public:
	virtual int32_t getType() const;
	virtual int32_t getGroupId() const;
	virtual int32_t getLevel() const;

public:
	bool init(int32_t itemid);

protected:
	CfgItem *m_cfgItem;
};

class ChiXuHuiXueBuff
	: public ItemBuff
{
public:
	ChiXuHuiXueBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~ChiXuHuiXueBuff();

public:
	virtual void effect();
	virtual void interval();
	virtual void restore();

	virtual bool deathClear();
};

class ChiXuHuiMoBuff
	: public ItemBuff
{
public:
	ChiXuHuiMoBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~ChiXuHuiMoBuff();

public:
	virtual void effect();
	virtual void interval();
	virtual void restore();

	virtual bool deathClear();
};
