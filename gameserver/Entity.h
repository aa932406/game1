#pragma once

enum EntityType
{
	ET_NONE			= 0,
	ET_PLAYER		= 1,	// 玩家
	ET_MONSTER		= 2,	// 怪物
	ET_NPC			= 3,	// NPC
	ET_PET			= 4,	// 宠物
	ET_DROPITEM		= 5,	// 掉落物
	ET_PLANT		= 6,	// 采集物
	ET_TRAP			= 7,	// 陷阱
	ET_TRAILER		= 8,	// 拖车
	ET_LACKEY		= 9,	// 跟班
	ET_CARRIER		= 10,	// 护送
	ET_LITTLE_HELPER	= 11,	// 小助手
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
