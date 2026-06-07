// Decompiled methods for class: Entity
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl Entity::~Entity(Entity *const this)
{
  Entity::~Entity(this);
  operator delete(this);
}


#####################################
void __cdecl Entity::generateEntityId(Entity *const this)
{
  this->m_entityId = _InterlockedExchangeAdd64(&Entity::m_nextEntityId, 1u) + 0x100000001LL;
}


