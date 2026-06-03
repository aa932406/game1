#include "stdafx.h"

#include "NpcActivity.h"
#include "Player.h"

NpcActivity::NpcActivity()
{

}

NpcActivity::~NpcActivity()
{

}

bool NpcActivity::isLifeEnd()
{
	if ( m_endTime <= 0 )
	{
		return false;
	}
	return getNow() >= m_endTime;
}

void NpcActivity::onTalkByPlayer(Player *player)
{
	//if (m_cfgNpc.func_extra == NFE_REAL_GOLD)
	//{
	//	player->onFindRealGold(m_cfgNpc.id, m_activityId);
	//}
}

void NpcActivity::init(const CfgNpc &cfgNpc, int32_t activity_id, int32_t lifetime)
{
	m_activityId = activity_id;

	m_endTime = getNow() + lifetime - 1;

	Npc::init(cfgNpc,m_endTime);
}

void NpcActivity::reset()
{
	generateEntityId();

	Unit::reset();

	m_activityId = 0;

	m_endTime = 0;
}

