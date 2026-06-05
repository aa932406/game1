// Decompiled methods for class: MapManager
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl MapManager::StartAll(MapManager *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 4; ++i )
    CMapRunner::Start(&this->m_Runner[i]);
}


#####################################
void __cdecl MapManager::StopAll(MapManager *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 4; ++i )
    CMapRunner::Stop(&this->m_Runner[i]);
}


#####################################
void __cdecl MapManager::initRunner(MapManager *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 4; ++i )
    CMapRunner::SetId(&this->m_Runner[i], i + 1);
}


#####################################
void __cdecl MapManager::initMap(MapManager *const this)
{
  CfgData *v1; // rax
  const std::pair<const int,CfgMap> *v2; // rax
  GameService *v3; // rax
  CActivityMap *v4; // rbx
  GameService *v5; // rax
  Map *v7; // rbx
  Map *pMap; // [rsp+28h] [rbp-C8h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgMap> > it; // [rsp+30h] [rbp-C0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgMap> > v10; // [rsp+40h] [rbp-B0h] BYREF
  MapType mt; // [rsp+4Ch] [rbp-A4h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,Map*> >,bool> v12; // [rsp+50h] [rbp-A0h]
  std::pair<const int,Map*> __x; // [rsp+60h] [rbp-90h] BYREF
  Map *__b; // [rsp+70h] [rbp-80h] BYREF
  int __a; // [rsp+78h] [rbp-78h] BYREF
  MapType v16; // [rsp+7Ch] [rbp-74h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,Map*> >,bool> v17; // [rsp+80h] [rbp-70h]
  std::pair<const int,Map*> v18; // [rsp+90h] [rbp-60h] BYREF
  int MapId; // [rsp+A4h] [rbp-4Ch] BYREF
  const CfgMapTable *cfgAllMap; // [rsp+A8h] [rbp-48h]
  const CfgMap *mapInfo; // [rsp+B0h] [rbp-40h]
  int32_t nRunnerId; // [rsp+BCh] [rbp-34h]
  CMapRunner *runner; // [rsp+C0h] [rbp-30h]
  CActivityMap *pActivityMap; // [rsp+C8h] [rbp-28h]

  v1 = Answer::Singleton<CfgData>::instance();
  cfgAllMap = CfgData::getMapAll(v1);
  for ( it._M_node = std::map<int,CfgMap>::begin(cfgAllMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator++(&it) )
  {
    v10._M_node = std::map<int,CfgMap>::end(cfgAllMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator!=(&it, &v10) )
      break;
    v2 = std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator->(&it);
    mapInfo = &v2->second;
    nRunnerId = v2->second.runnerId;
    if ( nRunnerId <= 0 || nRunnerId > 5 )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "MapManager::initMap() runner id out of range, mapid=%d, runnerid=%d \n",
        mapInfo->id,
        nRunnerId);
      continue;
    }
    v3 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v3) == 9 )
    {
      if ( !CfgMap::isCross(mapInfo, CROSS_MAP_TYPE::CMT_CROSS) )
        continue;
    }
    else if ( !CfgMap::isCross(mapInfo, CROSS_MAP_TYPE::CMT_NORMAL) )
    {
      continue;
    }
    runner = (CMapRunner *)(&this->m_maps._M_t._M_impl._M_header._M_parent + 23 * nRunnerId);
    mt = MapType::MT_ACTIVITY;
    if ( CfgMap::isType(mapInfo, &mt) )
    {
      v4 = (CActivityMap *)operator new(0x280u);
      CActivityMap::CActivityMap(v4);
      pActivityMap = v4;
      if ( v4 )
      {
        (*((void (__fastcall **)(CActivityMap *, CMapRunner *, const CfgMap *))pActivityMap->_vptr_Map + 2))(
          pActivityMap,
          runner,
          mapInfo);
        __b = pActivityMap;
        __a = Map::GetMapId(pActivityMap);
        std::pair<int const,Map *>::pair(&__x, &__a, &__b);
        v12 = std::map<int,Map *>::insert(&this->m_maps, &__x);
        CMapRunner::AddMap(runner, pActivityMap);
      }
    }
    else
    {
      v16 = MapType::MT_NORMAL;
      if ( CfgMap::isType(mapInfo, &v16) )
      {
        if ( mapInfo->param <= 0 || (v5 = Answer::Singleton<GameService>::instance(), GameService::getLine(v5) == 1) )
        {
          v7 = (Map *)operator new(0x1C8u);
          Map::Map(v7);
          pMap = v7;
          if ( v7 )
          {
            (*((void (__fastcall **)(Map *, CMapRunner *, const CfgMap *))pMap->_vptr_Map + 2))(pMap, runner, mapInfo);
            MapId = Map::GetMapId(pMap);
            std::pair<int const,Map *>::pair(&v18, &MapId, &pMap);
            v17 = std::map<int,Map *>::insert(&this->m_maps, &v18);
            CMapRunner::AddMap(runner, pMap);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl MapManager::AddDungeon(MapManager *const this, Dungeon *pDungeon)
{
  Dungeon *pDungeona; // [rsp+10h] [rbp-60h] BYREF
  MapManager *thisa; // [rsp+18h] [rbp-58h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,Dungeon*> >,bool> v5; // [rsp+30h] [rbp-40h]
  std::pair<const int,Dungeon*> __x; // [rsp+40h] [rbp-30h] BYREF
  int __a[5]; // [rsp+5Ch] [rbp-14h] BYREF

  thisa = this;
  pDungeona = pDungeon;
  if ( pDungeon )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_mapLock);
    __a[0] = Dungeon::GetId(pDungeona);
    std::pair<int const,Dungeon *>::pair(&__x, __a, &pDungeona);
    v5 = std::map<int,Dungeon *>::insert(&thisa->m_dungeons, &__x);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl MapManager::DelDungeon(MapManager *const this, int32_t nId)
{
  CPoolManager *v2; // rax
  int32_t nIda; // [rsp+4h] [rbp-4Ch] BYREF
  MapManager *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,Dungeon*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Dungeon*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Dungeon *pDungeon; // [rsp+38h] [rbp-18h]

  thisa = this;
  nIda = nId;
  pDungeon = 0;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_mapLock);
  iter._M_node = std::map<int,Dungeon *>::find(&this->m_dungeons, &nIda)._M_node;
  __x._M_node = std::map<int,Dungeon *>::end(&thisa->m_dungeons)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,Dungeon *>>::operator!=(&iter, &__x) )
  {
    pDungeon = std::_Rb_tree_iterator<std::pair<int const,Dungeon *>>::operator->(&iter)->second;
    std::map<int,Dungeon *>::erase(&thisa->m_dungeons, iter);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  if ( pDungeon )
  {
    v2 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<Dungeon>(v2, pDungeon);
  }
}


#####################################
void __cdecl MapManager::PostMsg(
        MapManager *const this,
        int32_t nRunnerId,
        GameMsgCode msgcode,
        void *ptr1,
        void *ptr2,
        int32_t iparam1,
        int32_t iparam2,
        void *ptr3)
{
  if ( nRunnerId > 0 && nRunnerId <= 5 )
    CMapRunner::PostMsg(
      (CMapRunner *const)&this->m_maps._M_t._M_impl._M_header._M_parent + nRunnerId,
      msgcode,
      ptr1,
      ptr2,
      iparam1,
      iparam2,
      ptr3);
  else
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "MapManager::PostMessage() runner id out of range, msgcode=%d, runnerid=%d \n",
      msgcode,
      nRunnerId);
}


#####################################
int32_t __cdecl MapManager::newDungenId(MapManager *const this)
{
  int32_t m_DungenId; // ebx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_mapLock);
  m_DungenId = this->m_DungenId;
  this->m_DungenId = m_DungenId + 1;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_DungenId;
}


#####################################
void __cdecl MapManager::AddTerritory(MapManager *const this, CTerritory *pTerritory)
{
  CTerritory *pTerritorya; // [rsp+10h] [rbp-60h] BYREF
  MapManager *thisa; // [rsp+18h] [rbp-58h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CTerritory*> >,bool> v5; // [rsp+30h] [rbp-40h]
  std::pair<const long int,CTerritory*> __x; // [rsp+40h] [rbp-30h] BYREF
  __int64 __a[3]; // [rsp+58h] [rbp-18h] BYREF

  thisa = this;
  pTerritorya = pTerritory;
  if ( pTerritory )
  {
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_mapLock);
    __a[0] = CTerritory::GetTerritoryId(pTerritorya);
    std::pair<long const,CTerritory *>::pair(&__x, __a, &pTerritorya);
    v5 = std::map<long,CTerritory *>::insert(&thisa->m_Territorys, &__x);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl MapManager::DelTerritory(MapManager *const this, FamilyId_t FamilyID)
{
  CPoolManager *v2; // rax
  FamilyId_t FamilyIDa; // [rsp+0h] [rbp-50h] BYREF
  MapManager *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,CTerritory*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CTerritory*> > __x; // [rsp+30h] [rbp-20h] BYREF
  CTerritory *pTerritory; // [rsp+38h] [rbp-18h]

  thisa = this;
  FamilyIDa = FamilyID;
  pTerritory = 0;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_mapLock);
  iter._M_node = std::map<long,CTerritory *>::find(&this->m_Territorys, &FamilyIDa)._M_node;
  __x._M_node = std::map<long,CTerritory *>::end(&thisa->m_Territorys)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CTerritory *>>::operator!=(&iter, &__x) )
  {
    pTerritory = std::_Rb_tree_iterator<std::pair<long const,CTerritory *>>::operator->(&iter)->second;
    std::map<long,CTerritory *>::erase(&thisa->m_Territorys, iter);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  if ( pTerritory )
  {
    v2 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<CTerritory>(v2, pTerritory);
  }
}


#####################################
void __cdecl MapManager::ResetMapMonster(MapManager *const this)
{
  std::_Rb_tree_iterator<std::pair<const int,Map*> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Map*> > __x; // [rsp+30h] [rbp-20h] BYREF
  Map *pMap; // [rsp+38h] [rbp-18h]

  Answer::MutexGuard::MutexGuard(&lock, &this->m_mapLock);
  for ( iter._M_node = std::map<int,Map *>::begin(&this->m_maps)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,Map *>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<int,Map *>::end(&this->m_maps)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,Map *>>::operator!=(&iter, &__x) )
      break;
    pMap = std::_Rb_tree_iterator<std::pair<int const,Map *>>::operator->(&iter)->second;
    if ( pMap )
      Map::ResetRefreshMonster(pMap);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


