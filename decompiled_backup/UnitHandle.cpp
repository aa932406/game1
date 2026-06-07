// Decompiled methods for class: UnitHandle
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl UnitHandle::isEmpty(const UnitHandle *const this)
{
  return !this->id || !this->type;
}


