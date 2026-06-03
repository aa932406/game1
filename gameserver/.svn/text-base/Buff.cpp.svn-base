#include "stdafx.h"

#include "Buff.h"

#include "Unit.h"

Buff::Buff(Unit &unit, CfgBuff &cfgBuff)
	: m_unit(unit), m_cfgBuff(cfgBuff), m_endTick(0), m_lastEffectTick(0)
{

}

Buff::~Buff()
{

}

int32_t Buff::remainTick()
{
	return static_cast<int32_t>(m_endTick-m_unit.getTick());
}

int32_t Buff::getId()
{
	return m_cfgBuff.id;
}

bool Buff::beneficial()
{
	return m_cfgBuff.beneficial != 0;
}

int32_t Buff::getSpecial()
{
	return m_cfgBuff.special;
}

bool Buff::NeedShow()
{
	return m_cfgBuff.isShow > 0;
}

CfgBuff& Buff::getCfgBuff()
{
	return m_cfgBuff;
}

bool Buff::expire()
{
	return m_unit.getTick() > m_endTick;
}
