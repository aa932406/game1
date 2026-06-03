#include "stdafx.h"

#include "ItemBuff.h"
#include "Unit.h"

ItemBuff::ItemBuff(Unit &unit, CfgBuff &cfgBuff)
	: Buff(unit, cfgBuff), m_cfgItem(NULL)
{

}

ItemBuff::~ItemBuff()
{

}

int32_t ItemBuff::getType() const
{
	return BT_ITEM;
}

int32_t ItemBuff::getGroupId() const
{
	if (m_cfgItem != NULL)
	{
		return m_cfgItem->type;
	}

	return 0;
}

int32_t ItemBuff::getLevel() const
{
	if (m_cfgItem != NULL)
	{
		return m_cfgItem->level;
	}

	return 0;
}

bool ItemBuff::init(int32_t itemid)
{
	m_cfgItem = CFG_DATA.getItem(itemid);
	if (m_cfgBuff.duration > 0)
	{
		m_endTick = m_unit.getTick() + m_cfgBuff.duration;
	}

	return m_cfgItem != NULL;
}

ChiXuHuiXueBuff::ChiXuHuiXueBuff(Unit &unit, CfgBuff &cfgBuff)
	: ItemBuff(unit, cfgBuff)
{

}

ChiXuHuiXueBuff::~ChiXuHuiXueBuff()
{

}

void ChiXuHuiXueBuff::effect()
{
	if (m_unit.isAlive())
	{
		m_unit.AddHP(m_cfgBuff.buffAttr[0].getAddon(getLevel()));
	}
	m_lastEffectTick = m_unit.getTick();
}

void ChiXuHuiXueBuff::interval()
{
	if (m_cfgBuff.interval > 0 && m_unit.getTick() - m_lastEffectTick >= m_cfgBuff.interval)
	{
		if (m_unit.isAlive())
		{
			m_unit.AddHP(m_cfgBuff.buffAttr[0].getAddon(getLevel()));
		}
		m_lastEffectTick = m_unit.getTick();
	}
}

void ChiXuHuiXueBuff::restore()
{

}

bool ChiXuHuiXueBuff::deathClear()
{
	return true;
}

ChiXuHuiMoBuff::ChiXuHuiMoBuff(Unit &unit, CfgBuff &cfgBuff)
	: ItemBuff(unit, cfgBuff)
{

}

ChiXuHuiMoBuff::~ChiXuHuiMoBuff()
{

}

void ChiXuHuiMoBuff::effect()
{
	if (m_unit.isAlive())
	{
		m_unit.AddMP(m_cfgBuff.buffAttr[0].getAddon(getLevel()));
	}
	m_lastEffectTick = m_unit.getTick();
}

void ChiXuHuiMoBuff::interval()
{
	if (m_cfgBuff.interval > 0 && m_unit.getTick() - m_lastEffectTick >= m_cfgBuff.interval)
	{
		if (m_unit.isAlive())
		{
			m_unit.AddMP(m_cfgBuff.buffAttr[0].getAddon(getLevel()));
		}
		m_lastEffectTick = m_unit.getTick();
	}
}

void ChiXuHuiMoBuff::restore()
{

}

bool ChiXuHuiMoBuff::deathClear()
{
	return true;
}

