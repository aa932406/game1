#pragma once

enum EntityType
{
	ET_NONE			= 0,
	ET_PLAYER		= 1,	// 玩家
	ET_MONSTER		= 2,	// 怪物
	ET_NPC			= 3,	// NPC
	ET_PET			= 4,	// 副将
	ET_DROPITEM		= 5,	// 掉落包
	ET_PLANT		= 6,	// 采集物
	ET_TRAP			= 7,	// 触发器
	ET_TRAILER		= 8,	// 镖车
	ET_LACKEY		= 9,	// 随从
};

class Entity
{
public:
	Entity(EntityType type);
	virtual ~Entity() = 0;

public:
	EntityId_t getEntityId() const;
	EntityType getType() const;

protected:
	void generateEntityId();

private:
	EntityId_t m_entityId;
	EntityType m_type;

	static long m_nextEntityId;
};

