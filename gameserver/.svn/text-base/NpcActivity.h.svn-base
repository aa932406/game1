#pragma once

#include "Npc.h"

class NpcActivity
	: public Npc
{
public:
	NpcActivity();
	virtual ~NpcActivity();

public:
	virtual bool isLifeEnd();
	virtual void onTalkByPlayer(Player *player);

public:
	void init(const CfgNpc &cfgNpc, int32_t activity_id, int32_t lifetime);
	void reset();

private:
	int32_t m_activityId;
};

