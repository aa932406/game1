#pragma once

#include "Buff.h"

class PersistBuff
	: public Buff
{
public:
	PersistBuff(Unit &unit, CfgBuff &cfgBuff);
	virtual ~PersistBuff();

public:
	virtual void effect();
	virtual void interval();
	virtual void restore();

	virtual bool deathClear();

	virtual int32_t getType() const;
	virtual int32_t getGroupId() const;
	virtual int32_t getLevel() const;

public:
	bool init(int32_t itemid, int32_t time);
	void extend(Buff *pBuff);
	int32_t getEndTime();
	int32_t getItemId();

protected:
	CfgItem *m_cfgItem;
};


