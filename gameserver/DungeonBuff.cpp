#include "stdafx.h"

#include "DungeonBuff.h"
#include "Unit.h"

DungeonBuff::DungeonBuff(Unit &unit, CfgBuff &cfgBuff)
	: Buff(unit, cfgBuff)
{
	bzero(&m_restore, sizeof(m_restore));
}

DungeonBuff::~DungeonBuff()
{

}

bool DungeonBuff::expire()
{
	return !m_unit.InDungeon();
}

void DungeonBuff::effect()
{
	for (int32_t i = 0; i < 2; ++i)
	{
		if ( m_cfgBuff.buffAttr[i].attr == CObjAttrs::ATTR_HP )
		{
			if (m_cfgBuff.buffAttr[i].getAddon(0) != 0)
			{
				m_unit.AddHp(m_cfgBuff.buffAttr[i].getAddon(0));
			}
		}
		else if (m_cfgBuff.buffAttr[i].attr == CObjAttrs::ATTR_MP)
		{
			if (m_cfgBuff.buffAttr[i].getAddon(0) != 0)
			{
				m_unit.AddMp(m_cfgBuff.buffAttr[i].getAddon(0));
			}
		}
		else
		{
			int32_t realaddon = m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ),
															m_cfgBuff.buffAttr[i].getRatio(getLevel()), m_cfgBuff.buffAttr[i].getAddon(getLevel()));
			if (realaddon != 0)
			{
				m_restore[i].index = m_cfgBuff.buffAttr[i].attr;
				m_restore[i].addon = -1*realaddon;
			}
		}
	}
}

void DungeonBuff::interval()
{
	if (m_cfgBuff.interval > 0 && m_unit.getTick() - m_lastEffectTick >= m_cfgBuff.interval)
	{
		for (int32_t i = 0; i < 2; ++i)
		{
			if ( m_cfgBuff.buffAttr[i].attr == CObjAttrs::ATTR_HP )
			{
				if (m_cfgBuff.buffAttr[i].getAddon(1) > 0)
				{
					m_unit.AddHp( m_cfgBuff.buffAttr[i].getAddon(1) );
				}
				else
				{
					m_unit.struckDamage(-1*m_cfgBuff.buffAttr[i].getAddon(m_skilllevel), 0, m_launcher);
				}
			}
			else if (m_cfgBuff.buffAttr[i].attr == CObjAttrs::ATTR_MP)
			{
				m_unit.AddMp(m_cfgBuff.buffAttr[i].getAddon(1));
			}
		}

		m_lastEffectTick = m_unit.getTick();
	}
}

void DungeonBuff::restore()
{
	for (int32_t i = 0; i < 2; ++i)
	{
		if (m_restore[i].index > 0)
		{
			m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_restore[i].index ), m_restore[i].addon);
		}
	}

	if (m_cfgBuff.special == SS_XUANYUN)
	{
		m_unit.RemoveBuffState( CObjState::OBS_YUNXUAN );
	}
	else if (m_cfgBuff.special == SS_WUDI)
	{
		m_unit.RemoveBuffState( CObjState::OBS_WUDI );
	}
	else if (m_cfgBuff.special == SS_BINGDONG)
	{
		m_unit.RemoveBuffState( CObjState::OBS_BINGDONG );
	}
}

bool DungeonBuff::deathClear()
{
	return false;
}

int32_t DungeonBuff::getType() const
{
	return BT_DUNGEON;
}

int32_t DungeonBuff::getGroupId() const
{
	return m_cfgBuff.id;
}

int32_t DungeonBuff::getLevel() const
{
	return 1;
}

void DungeonBuff::init()
{
	m_endTick = m_unit.getTick() + m_cfgBuff.duration;
}
