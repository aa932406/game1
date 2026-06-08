#include "stdafx.h"

#include "Buff.h"

#include "Unit.h"

Buff::Buff(Unit &unit, CfgBuff &cfgBuff, const UnitHandle &launcher, int8_t nType, bool bClear)
	: m_unit(unit), m_cfgBuff(cfgBuff), m_launcher(launcher)
	, m_endTick(0), m_lastEffectTick(0), m_lastIntervalTick(0)
	, m_nShield(0), m_nEffectTimes(0), m_nType(nType), m_bDeathClear(bClear)
{
	if (m_cfgBuff.shieldValue > 0)
		m_nShield = m_cfgBuff.shieldValue;
	if (m_cfgBuff.shieldRatio > 0)
		m_nShield += m_cfgBuff.shieldRatio * m_unit.GetMaxHP() / 100;
	m_lastIntervalTick = m_unit.getTick();
	m_endTick = m_unit.getTick() + m_cfgBuff.duration;
}

Buff::~Buff()
{

}

int32_t Buff::remainTick()
{
	return static_cast<int32_t>(m_endTick - m_unit.getTick());
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
	if (m_unit.getTick() > m_endTick)
		return true;
	if (m_nType == 2)
		return !m_unit.InDungeon();
	if (m_nType == 3)
		return !m_unit.InActivity();
	return false;
}

void Buff::effect()
{
	int32_t nAttrSize = 2;
	m_restore.clear();
	m_restore.resize(nAttrSize);
	for (int32_t i = 0; i < nAttrSize; ++i)
	{
		m_restore[i].index = m_cfgBuff.buffAttr[i].attr;
		if (m_cfgBuff.buffAttr[i].attr == 12)
		{
			m_restore[i].ratio = m_unit.AddSpeedBuffRatio(
				m_cfgBuff.buffAttr[i].getRatio(getLevel()));
		}
		else
		{
			m_restore[i].ratio = m_unit.AddBuffAttrRatio(
				static_cast<CObjAttrs::Index_T>(m_cfgBuff.buffAttr[i].attr),
				m_cfgBuff.buffAttr[i].getRatio(getLevel()));
		}
		m_restore[i].addon = m_unit.AddBuffAttrValue(
			static_cast<CObjAttrs::Index_T>(m_cfgBuff.buffAttr[i].attr),
			m_cfgBuff.buffAttr[i].getAddon(getLevel()));
	}

	switch (m_cfgBuff.special)
	{
	case 1:
		m_unit.AddBuffState(CObjState::OBS_YUNXUAN);
		break;
	case 2:
	case 11:
		m_unit.AddBuffState(CObjState::OBS_WUDI);
		break;
	case 3:
		m_unit.AddBuffState(CObjState::OBS_BINGDONG);
		break;
	case 4:
		m_unit.AddBuffState(CObjState::OBS_FREEDOM);
		break;
	case 5:
		m_unit.AddBuffState(CObjState::OBS_CHENMO);
		break;
	case 6:
		m_unit.AddBuffState(CObjState::OBS_SLEEP);
		break;
	case 7:
		m_unit.AddBuffState(CObjState::OBS_SHIELD);
		break;
	case 8:
		m_unit.AddBuffState(CObjState::OBS_PLYSIS);
		break;
	case 9:
		m_unit.AddBuffState(CObjState::OBS_FROZEN);
		break;
	}

	m_lastEffectTick = m_unit.getTick();
}

void Buff::interval()
{
	int32_t hpchange = 0;
	if (m_cfgBuff.beneficial)
	{
		if (m_cfgBuff.hpValue > 0)
			hpchange += m_cfgBuff.hpValue;
		if (m_cfgBuff.hpPecent > 0)
			hpchange += m_cfgBuff.hpPecent * m_unit.GetMaxHP() / 100;
		m_unit.AddHP(hpchange);
	}
	else
	{
		int32_t nDamage = 0;
		if (m_cfgBuff.hpValue > 0)
			nDamage += m_cfgBuff.hpValue;
		if (m_cfgBuff.hpPecent > 0)
			nDamage += m_cfgBuff.hpPecent * m_unit.GetMaxHP() / 100;
		hpchange -= nDamage;
		int32_t attackState = 0;
		m_unit.struckDamage(nDamage, m_cfgBuff.attack_type, m_launcher);
	}
}

void Buff::restore()
{
	int32_t nAttrSize = static_cast<int32_t>(m_restore.size());
	if (nAttrSize > 0)
	{
		for (int32_t i = 0; i < nAttrSize; ++i)
		{
		if (m_cfgBuff.buffAttr[i].attr == 12)
		{
			m_restore[i].ratio = m_unit.RemoveSpeedBuffRatio(m_restore[i].ratio);
		}
		else
		{
			m_unit.AddBuffAttrRatio(
				static_cast<CObjAttrs::Index_T>(m_restore[i].index),
				-m_restore[i].ratio);
		}
			m_unit.AddBuffAttrValue(
				static_cast<CObjAttrs::Index_T>(m_restore[i].index),
				-m_restore[i].addon);
		}
	}

	switch (m_cfgBuff.special)
	{
	case 1:
		m_unit.RemoveBuffState(CObjState::OBS_YUNXUAN);
		break;
	case 2:
	case 11:
		m_unit.RemoveBuffState(CObjState::OBS_WUDI);
		break;
	case 3:
		m_unit.RemoveBuffState(CObjState::OBS_BINGDONG);
		break;
	case 4:
		m_unit.RemoveBuffState(CObjState::OBS_FREEDOM);
		break;
	case 5:
		m_unit.RemoveBuffState(CObjState::OBS_CHENMO);
		break;
	case 6:
		m_unit.RemoveBuffState(CObjState::OBS_SLEEP);
		break;
	case 7:
		m_unit.RemoveBuffState(CObjState::OBS_SHIELD);
		break;
	case 8:
		m_unit.RemoveBuffState(CObjState::OBS_PLYSIS);
		break;
	case 9:
		m_unit.RemoveBuffState(CObjState::OBS_FROZEN);
		break;
	}
}

bool Buff::shieldDamage(int32_t &nDamage)
{
	if (nDamage < m_nShield)
	{
		m_nShield -= nDamage;
		nDamage = 0;
		return false;
	}
	else
	{
		nDamage -= m_nShield;
		m_nShield = 0;
		return true;
	}
}

void Buff::trigTime()
{
	if (m_cfgBuff.interval > 0
		&& m_unit.getTick() - m_lastIntervalTick >= m_cfgBuff.interval)
	{
		interval();
		m_lastIntervalTick += m_cfgBuff.interval;
	}
}

bool Buff::effectTimes()
{
	return ++m_nEffectTimes >= m_cfgBuff.effectTimes;
}
