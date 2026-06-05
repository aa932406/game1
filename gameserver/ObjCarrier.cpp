#include "stdafx.h"

#include "ObjCarrier.h"
#include "CharCarrier.h"
#include "Player.h"
#include "CfgData.h"

CObjCarrier::CObjCarrier()
: Unit( ET_CARRIER )
{
	m_nId = 0;
	m_pPlayer = NULL;
}

CObjCarrier::~CObjCarrier()
{
}

void CObjCarrier::reset()
{
	Unit::reset();
	m_nId = 0;
	m_pPlayer = NULL;
	m_lSkills.clear();
}

void CObjCarrier::refresh()
{
	if ( !m_pPlayer )
		return;

	if ( !isAlive() )
	{
		m_pPlayer->GetCharCarrier().LeaveCarrier();
		return;
	}
}

EntityId_t CObjCarrier::getUnitId() const
{
	if ( m_pPlayer )
		return m_pPlayer->getCid();
	return Unit::getUnitId();
}

CharId_t CObjCarrier::getOwner() const
{
	if ( m_pPlayer )
		return m_pPlayer->getCid();
	return 0;
}

int32_t CObjCarrier::getLevel() const
{
	if ( m_pPlayer )
		return m_pPlayer->getLevel();
	return 0;
}

int32_t CObjCarrier::getBattle() const
{
	if ( m_pPlayer )
		return m_pPlayer->getBattle();
	return 0;
}

bool CObjCarrier::isFriendSide(Unit *pUnit)
{
	return m_pPlayer && m_pPlayer->isFriendSide(pUnit);
}

bool CObjCarrier::checkSkillTarget(CfgSkill *pCfg, Unit *pUnit)
{
	return m_pPlayer && m_pPlayer->checkSkillTarget(pCfg, pUnit);
}

void CObjCarrier::Init(Player *pOwner, int32_t nId)
{
	m_nId = nId;
	m_pPlayer = pOwner;

	const CfgCarrierTable* pCarrierTable = CFG_DATA.GetCarrierTable();
	const CfgCarrier* pCfgCarrier = pCarrierTable->GetCarrier(nId);
	if ( pCfgCarrier )
	{
		// 直接从配置复制技能ID
		m_lSkills = pCfgCarrier->lSkills;
		ResetAttrs();
		initBaseAttr();
		adjustUnitAttr();
		FillHP(100);
	}
}

void CObjCarrier::initBaseAttr()
{
	if ( !m_pPlayer )
		return;

	int32_t nLevel = m_pPlayer->getLevel();
	const CfgCarrierTable* pCarrierTable = CFG_DATA.GetCarrierTable();
	const CfgCarrierAttr* pCfgAttr = pCarrierTable->GetCarrierAttr(m_nId, nLevel);
	if ( pCfgAttr )
	{
		for ( std::vector<AttrAddon>::const_iterator iter = pCfgAttr->vAttr.begin();
			iter != pCfgAttr->vAttr.end(); ++iter )
		{
			AddAttrValue((CObjAttrs::Index_T)iter->index, iter->addon);
		}
	}
}

bool CObjCarrier::HaveSkill(int32_t nSkillId) const
{
	return std::find(m_lSkills.begin(), m_lSkills.end(), nSkillId) != m_lSkills.end();
}

bool CObjCarrier::appendInfo(Answer::NetPacket *packet)
{
	return m_pPlayer != NULL && packet != NULL;
}
