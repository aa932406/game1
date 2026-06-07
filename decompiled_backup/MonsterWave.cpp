// Decompiled methods for class: MonsterWave
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl MonsterWave::alive(MonsterWave *const this)
{
  return this->count > this->killed + this->escaped;
}


