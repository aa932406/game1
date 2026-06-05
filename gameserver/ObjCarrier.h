#pragma once

#include "Unit.h"
#include "Entity.h"

class Player;
struct CfgActiveSkill;

class CObjCarrier : public Unit
{
public:
	CObjCarrier();
	virtual ~CObjCarrier();

public:
	virtual void reset();
	virtual void refresh();
	virtual EntityId_t getUnitId() const;
	virtual CharId_t getOwner() const;
	virtual int32_t getLevel() const;
	virtual int32_t getBattle() const;
	virtual bool isFriendSide(Unit *pUnit);
	virtual bool checkSkillTarget(CfgSkill *pCfg, Unit *pUnit);
	virtual void postDamage(int32_t damge, UnitHandle launcher);

public:
	void Init(Player *pOwner, int32_t nId);
	bool HaveSkill(int32_t nSkillId) const;
	bool appendInfo(Answer::NetPacket *packet);
	int32_t GetCarrierId() const { return m_nId; }


private:
	void initBaseAttr();

private:
	int32_t				m_nId;
	Player*				m_pPlayer;
	std::list<int32_t>	m_lSkills;
};
