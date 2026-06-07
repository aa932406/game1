// Decompiled methods for class: StaticObj
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl StaticObj::~StaticObj(StaticObj *const this)
{
  StaticObj::~StaticObj(this);
  operator delete(this);
}


#####################################
void __cdecl StaticObj::reset(StaticObj *const this)
{
  Position v1; // [rsp+10h] [rbp-20h] BYREF
  Position v2; // [rsp+20h] [rbp-10h] BYREF

  Entity::generateEntityId(this);
  this->m_pMap = 0;
  Position::Position(&v1, 0, 0);
  this->m_currentTile = v1;
  Position::Position(&v2, 0, 0);
  this->m_currentPos = v2;
}


#####################################
int32_t __cdecl StaticObj::getMapId(StaticObj *const this)
{
  if ( this->m_pMap )
    return Map::GetMapId(this->m_pMap);
  else
    return 0;
}


#####################################
int32_t __cdecl StaticObj::getMapType(StaticObj *const this)
{
  if ( this->m_pMap )
    return Map::GetType(this->m_pMap);
  else
    return 0;
}


#####################################
bool __cdecl StaticObj::InDungeon(const StaticObj *const this)
{
  return this->m_pMap && (*((bool (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap);
}


#####################################
bool __cdecl StaticObj::InActivity(const StaticObj *const this)
{
  return this->m_pMap && (*((bool (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap);
}


#####################################
bool __cdecl StaticObj::InPrison(const StaticObj *const this)
{
  return this->m_pMap && Map::IsPrison(this->m_pMap);
}


#####################################
int32_t __cdecl StaticObj::GetRunnerId(const StaticObj *const this)
{
  if ( this->m_pMap )
    return Map::GetRunnerId(this->m_pMap);
  else
    return 0;
}


#####################################
bool __cdecl StaticObj::IsSpecialBossMap(const StaticObj *const this)
{
  return this->m_pMap && Map::IsSpecialBossMap(this->m_pMap);
}


#####################################
bool __cdecl StaticObj::IsCycleTower(const StaticObj *const this)
{
  return this->m_pMap && Map::IsCycleTower(this->m_pMap);
}


#####################################
bool __cdecl StaticObj::IsKuangDong(const StaticObj *const this)
{
  return this->m_pMap && Map::IsKuangDong(this->m_pMap);
}


#####################################
bool __cdecl StaticObj::IsTerritory(const StaticObj *const this)
{
  return this->m_pMap && (*((bool (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 19))(this->m_pMap);
}


