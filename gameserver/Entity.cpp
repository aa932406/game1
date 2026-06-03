#include "stdafx.h"

#include "Entity.h"

long Entity::m_nextEntityId = 10000;

Entity::Entity(EntityType type)
	: m_entityId(0), m_type(type)
{
	generateEntityId();
}

Entity::~Entity()
{

}

EntityId_t Entity::getEntityId() const
{
	return m_entityId;
}

EntityType Entity::getType() const
{
	return m_type;
}

void Entity::generateEntityId()
{
	//m_entityId = static_cast<EntityId_t>(AtomicAdd(&m_nextEntityId));
	m_entityId = static_cast<EntityId_t>(AtomicAdd(&m_nextEntityId)) + (static_cast<EntityId_t>(1) << 32);	// ²âÊÔÓÃ
}

