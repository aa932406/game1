#include "stdafx.h"

#include "CfgData.h"
#include "GameService.h"
#include "Map.h"
#include "Skill.h"
#include "SkillBuff.h"
#include "Unit.h"

using namespace Answer;

SkillBuff::SkillBuff(Unit &unit, CfgBuff &cfgBuff)
	: Buff(unit, cfgBuff), m_skillid(0), m_skilllevel(0)
{

}

SkillBuff::~SkillBuff()
{

}

void SkillBuff::effect()
{
	m_restore.resize(2);
	for (int32_t i = 0; i < 2; ++i)
	{
		if (m_cfgBuff.buffAttr[i].attr > 0)
		{
			int32_t hpchange = 0;
			if ( m_cfgBuff.buffAttr[i].attr == ATTR_CUR_HP )
			{
				if ( m_cfgBuff.buffAttr[i].getAddon(m_skilllevel) > 0)
				{
					m_unit.AddHP(m_cfgBuff.buffAttr[i].getAddon(m_skilllevel));
				}
				else
				{
					m_unit.struckDamage(-1*m_cfgBuff.buffAttr[i].getAddon(m_skilllevel), 0, m_launcher);
					hpchange += m_cfgBuff.buffAttr[i].getAddon(m_skilllevel);
				}
				if ( m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) > 0  )
				{
					int32_t AddHp = m_unit.GetMaxHP() / m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) / 100;
					m_unit.AddHP(m_cfgBuff.buffAttr[i].getAddon(m_skilllevel));
				}
				else
				{
					int32_t AddHp = m_unit.GetMaxHP() * m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) / 100;
					m_unit.struckDamage( -1*AddHp, 0, m_launcher);
					hpchange +=AddHp;
				}
				if (hpchange != 0)
				{
					broadcastIntervalEffect( hpchange);
				}
			}
// 			else if (m_cfgBuff.buffAttr[i].attr == ATTR_MP)
// 			{
// 				m_unit.addMP(m_cfgBuff.buffAttr[i].getAddon(m_skilllevel));
// 			}
			else
			{
				m_restore[i].index = m_cfgBuff.buffAttr[i].attr;
				m_restore[i].ratio = m_unit.AddBuffAttrRatio( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) );
				m_restore[i].addon = m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_cfgBuff.buffAttr[i].attr ), m_cfgBuff.buffAttr[i].getAddon(m_skilllevel) );
			}
		}
	}

	if (m_cfgBuff.special == SS_XUANYUN)
	{
		m_unit.AddBuffState( CObjState::OBS_YUNXUAN );
	}
	else if (m_cfgBuff.special == SS_WUDI)
	{
		m_unit.AddBuffState( CObjState::OBS_WUDI );
	}
	else if (m_cfgBuff.special == SS_BINGDONG)
	{
		m_unit.AddBuffState( CObjState::OBS_BINGDONG );
	}
	else if ( m_cfgBuff.special == SS_DIVIDE)
	{
		m_unit.AddBuffState( CObjState::OBS_DIVIDE );
	}
	m_lastEffectTick = m_unit.getTick();
}

void SkillBuff::interval()
{
	if (m_cfgBuff.interval > 0 && m_unit.getTick() - m_lastEffectTick >= m_cfgBuff.interval)
	{
		for (int32_t i = 0; i < 2; ++i)
		{
			if (m_cfgBuff.buffAttr[i].attr == ATTR_CUR_HP)
			{
				int32_t hpchange = 0;
				if (m_cfgBuff.buffAttr[i].getAddon(m_skilllevel) > 0)
				{
					m_unit.AddHP(m_cfgBuff.buffAttr[i].getAddon(m_skilllevel));
				}
				else
				{
					m_unit.struckDamage(-1*m_cfgBuff.buffAttr[i].getAddon(m_skilllevel), 0, m_launcher);
					hpchange = m_cfgBuff.buffAttr[i].getAddon(m_skilllevel);
				}
				if ( m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) > 0  )
				{
					int32_t AddHp = m_unit.GetMaxHP() / m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) / 100;
					m_unit.AddHP(m_cfgBuff.buffAttr[i].getAddon(m_skilllevel));
				}
				else
				{
					int32_t AddHp = m_unit.GetMaxHP() * m_cfgBuff.buffAttr[i].getRatio(m_skilllevel) / 100;
					m_unit.struckDamage( -1*AddHp, 0, m_launcher);
					hpchange +=AddHp;
				}
				if (hpchange != 0)
				{
					broadcastIntervalEffect(hpchange);
				}
			}
			//else if (m_cfgBuff.buffAttr[i].attr == ATTR_MP)
			//{
			//	m_unit.addMP(m_cfgBuff.buffAttr[i].getAddon(m_skilllevel));
			//}
		}

		m_lastEffectTick = m_unit.getTick();
	}
}

void SkillBuff::restore()
{
	for (int32_t i = 0; i < 2; ++i)
	{
		if (m_restore[i].index > 0)
		{
			m_unit.AddBuffAttrRatio( static_cast<CObjAttrs::Index_T>( m_restore[i].index ),-1 * m_restore[i].ratio );
			m_unit.AddBuffAttrValue( static_cast<CObjAttrs::Index_T>( m_restore[i].index ),-1 * m_restore[i].addon );
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
	//else if (m_cfgBuff.special == SS_PERSIST_HP)
	//{
	//	m_unit.RemoveBuffState( CObjState::OBS_PERSIST_HP );
	//}
	else if (m_cfgBuff.special == SS_BINGDONG)
	{
		m_unit.RemoveBuffState( CObjState::OBS_BINGDONG );
	}
	else if (m_cfgBuff.special == SS_SLOW)
	{
		m_unit.RemoveBuffState( CObjState::OBS_SLOW );
	}
	else if (  m_cfgBuff.special == SS_DIVIDE )
	{
		m_unit.RemoveBuffState( CObjState::OBS_DIVIDE );
	}
	//else if (m_cfgBuff.special == SS_CONFUSION)
	//{
	//	m_unit.RemoveBuffState( CObjState::OBS_CONFUSION );
	//}
	//else if (m_cfgBuff.special == SS_ANTI_JUMP)
	//{
	//	m_unit.RemoveBuffState( CObjState::OBS_ANTI_JUMP );
	//}
}

bool SkillBuff::deathClear()
{
	return true;
}

int32_t SkillBuff::getType() const
{
	return BT_SKILL;
}

int32_t SkillBuff::getGroupId() const
{
	return m_skillid;
}

int32_t SkillBuff::getLevel() const
{
	return m_skilllevel;
}

bool SkillBuff::init(int32_t skillid, int32_t skilllevel, UnitHandle launcher, UnitHandle target)
{
	m_skillid = skillid;
	m_skilllevel = skilllevel;
	m_launcher = launcher;

	int32_t  deleTime = 0;
	if (m_cfgBuff.duration > 0)
	{
		//switch(m_cfgBuff.special)
		//{
		//case  SS_BINGDONG:
		//	{
		//		Unit* pUnit = GAME_SERVICE.getUnit(target.id,target.type);
		//		if (pUnit != NULL)
		//		{
		//			deleTime = pUnit->getAttr(ATTR_PREFROST)*100;
		//		}
		//		break;
		//	}
		//case  SS_XUANYUN:
		//	{
		//		Unit* pUnit = GAME_SERVICE.getUnit(target.id,target.type);
		//		if (pUnit != NULL)
		//		{
		//			deleTime = pUnit->getAttr(ATTR_PREBK)*100;
		//		}
		//		break;
		//	}	
		//default:
		//	break;
		//}
		m_endTick = m_unit.getTick() + m_cfgBuff.duration - deleTime;
	}

	return true;
}

void SkillBuff::broadcastIntervalEffect(int32_t hpchange)
{
	Map *pMap = m_unit.getMap();
	if (pMap == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SKILL_RESULT);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_unit.GetSkillFlag() );
	packet->writeInt16(static_cast<int16_t>(m_skillid));
	packet->writeInt64(m_launcher.id);
	packet->writeInt8(static_cast<int8_t>(m_launcher.type));
	packet->writeInt32(0);
	packet->writeInt16(m_unit.getCurrentTile().x);
	packet->writeInt16(m_unit.getCurrentTile().y);

	packet->writeInt32(1);
	packet->writeInt64(m_unit.getUnitId());
	packet->writeInt8(static_cast<int8_t>(m_unit.getType()));
	packet->writeInt32(hpchange);
	packet->writeInt16(static_cast<int16_t>(SAS_NORMAL));
	packet->writeInt32(0);
	packet->writeInt32(0);
	packet->setSize(packet->getWOffset());
	pMap->broadcastAreaAround(packet, &m_unit);
}

