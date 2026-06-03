#include "stdafx.h"

#include "MonsterBuff.h"
#include "Unit.h"

MonsterBuff::MonsterBuff(Unit &unit, CfgBuff &cfgBuff)
	: Buff(unit, cfgBuff)
{
	bzero(&m_restore, sizeof(m_restore));
}

MonsterBuff::~MonsterBuff()
{
}

bool MonsterBuff::expire()
{
	return false;
}

void MonsterBuff::effect()
{
	for (int32_t i = 0; i < 2; ++i)
	{
		m_restore[i].index = m_cfgBuff.buffAttr[i].attr;
		m_restore[i].ratio = m_unit.AddBuffAttrRatio( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), m_cfgBuff.buffAttr[i].getRatio(getLevel()) );
		m_restore[i].addon = m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), m_cfgBuff.buffAttr[i].getAddon(getLevel()) );
	}
	if (m_cfgBuff.special == SS_WUDI)
	{
		m_unit.AddBuffState( CObjState:: OBS_WUDI );
	}
}

void MonsterBuff::interval()
{
}

void MonsterBuff::restore()
{
	for (int32_t i = 0; i < 2; ++i)
	{
		if (m_restore[i].index > 0)
		{
			m_unit.AddBuffAttrRatio( static_cast<CObjAttrs::Index_T>( m_restore[i].index ), -1 * m_restore[i].ratio );
			m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_restore[i].index ), -1 * m_restore[i].addon );
		}
	}
	if ( m_cfgBuff.special == SS_WUDI )
	{
		m_unit.RemoveBuffState( CObjState::OBS_WUDI );
	}
}

bool MonsterBuff::deathClear()
{
	return true;
}

int32_t MonsterBuff::getType() const
{
	return BT_MONSTER;
}

int32_t MonsterBuff::getGroupId() const
{
	return 0;
}

int32_t MonsterBuff::getLevel() const
{
	return 1;
}

void MonsterBuff::init()
{
	if (m_cfgBuff.duration > 0)
	{
		m_endTick = m_unit.getTick() + m_cfgBuff.duration;
	}
}

