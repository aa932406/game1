#include "stdafx.h"

#include "PersistBuff.h"
#include "Player.h"

#define EXP_RATE_ATTR		102 //经验比例的属性类型

PersistBuff::PersistBuff(Unit &unit, CfgBuff &cfgBuff)
	: Buff(unit, cfgBuff)
{

}

PersistBuff::~PersistBuff()
{

}

void PersistBuff::effect()
{
	for ( int32_t i = 0; i < 2; i++ )
	{
		if ( m_cfgBuff.buffAttr[i].attr == EXP_RATE_ATTR )
		{
			Player* pPlayer = dynamic_cast<Player*>(&m_unit);
			if ( NULL != pPlayer )
			{
				pPlayer->AddExpRate( m_cfgBuff.buffAttr[i].getAddon(getLevel()));
			}
		}
		else
		{
			m_unit.AddBuffAttrRatio( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), m_cfgBuff.buffAttr[i].getRatio(getLevel()) );
			m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), m_cfgBuff.buffAttr[i].getAddon(getLevel()) );
		}
	}
}

void PersistBuff::interval()
{

}

void PersistBuff::restore()
{
	for ( int32_t i = 0; i < 2; i++ )
	{
		if ( m_cfgBuff.buffAttr[i].attr == EXP_RATE_ATTR )
		{
			Player* pPlayer = dynamic_cast<Player*>(&m_unit);
			if ( NULL != pPlayer )
			{
				pPlayer->AddExpRate( -1*m_cfgBuff.buffAttr[i].getAddon(getLevel()));
			}
		}
		else
		{
			m_unit.AddBuffAttrRatio( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), -1*m_cfgBuff.buffAttr[i].getRatio(getLevel()) );
			m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), -1*m_cfgBuff.buffAttr[i].getAddon(getLevel()) );
		}
	}
}

bool PersistBuff::deathClear()
{
	return false;
}

int32_t PersistBuff::getType() const
{
	return BT_PERSIST;
}

int32_t PersistBuff::getGroupId() const
{
	if (m_cfgItem != NULL)
	{
		return m_cfgItem->group_id;
	}

	return 0;
}

int32_t PersistBuff::getLevel() const
{
	if (m_cfgItem != NULL)
	{
		return m_cfgItem->level;
	}

	return 0;
}

bool PersistBuff::init(int32_t itemid, int32_t time)
{
	m_cfgItem = CFG_DATA.getItem(itemid);

	if (time != 0)
	{
		m_endTick = m_unit.getTick() + (time)*1000;
	}
	else
	{
		m_endTick = m_unit.getTick() + m_cfgBuff.duration;
	}

	return m_cfgItem != NULL;
}

void PersistBuff::extend(Buff *pBuff)
{
	if (pBuff != NULL)
	{
		m_endTick += pBuff->getCfgBuff().duration;
	}
}

int32_t PersistBuff::getEndTime()
{
	return roundInt((m_endTick-m_unit.getTick())*0.001);
}

int32_t PersistBuff::getItemId()
{
	if (m_cfgItem != NULL)
	{
		return m_cfgItem->id;
	}

	return 0;
}


