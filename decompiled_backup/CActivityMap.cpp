// Decompiled methods for class: CActivityMap
// Source: gameserver.cc
// Total methods: 35

#####################################
void __cdecl CActivityMap::~CActivityMap(CActivityMap *const this)
{
  CActivityMap::~CActivityMap(this);
  operator delete(this);
}


#####################################
void __cdecl CActivityMap::init(CActivityMap *const this, CMapRunner *pRunner, const CfgMap *const cfgmap)
{
  Map::init(this, pRunner, cfgmap);
  CActivityMap::clear(this);
}


#####################################
void __cdecl CActivityMap::clear(CActivityMap *const this)
{
  EntityId_t v1; // rdx
  CPoolManager *v2; // rax
  CPoolManager *v3; // rax
  std::_List_iterator<Trap*> iter_1; // [rsp+10h] [rbp-70h] BYREF
  std::_List_iterator<PlantActivity*> iter_0; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<MonsterActivity*> iter; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<MonsterActivity*> __x; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<PlantActivity*> v8; // [rsp+50h] [rbp-30h] BYREF
  std::_List_iterator<Trap*> v9; // [rsp+60h] [rbp-20h] BYREF
  MonsterActivity *pMonster; // [rsp+68h] [rbp-18h]
  PlantActivity *plant; // [rsp+70h] [rbp-10h]
  Trap *pTrap; // [rsp+78h] [rbp-8h]

  IMapEvent::clear(&this->IMapEvent);
  std::list<Position>::clear(&this->m_lstStack);
  this->m_nStartTick = 0;
  std::map<int,MonsterWave>::clear(&this->m_monsterWave);
  std::list<MonsterWait>::clear(&this->m_waitMonster);
  std::map<long,int>::clear(&this->m_CidBattle);
  if ( !std::list<MonsterActivity *>::empty(&this->m_actMonsters) )
  {
    for ( iter._M_node = std::list<MonsterActivity *>::begin(&this->m_actMonsters)._M_node;
          ;
          std::_List_iterator<MonsterActivity *>::operator++(&iter) )
    {
      __x._M_node = std::list<MonsterActivity *>::end(&this->m_actMonsters)._M_node;
      if ( !std::_List_iterator<MonsterActivity *>::operator!=(&iter, &__x) )
        break;
      pMonster = *std::_List_iterator<MonsterActivity *>::operator*(&iter);
      if ( pMonster )
        MonsterActivity::remove(pMonster);
    }
    std::list<MonsterActivity *>::clear(&this->m_actMonsters);
  }
  if ( !std::list<PlantActivity *>::empty(&this->m_actPlants) )
  {
    for ( iter_0._M_node = std::list<PlantActivity *>::begin(&this->m_actPlants)._M_node;
          ;
          std::_List_iterator<PlantActivity *>::operator++(&iter_0) )
    {
      v8._M_node = std::list<PlantActivity *>::end(&this->m_actPlants)._M_node;
      if ( !std::_List_iterator<PlantActivity *>::operator!=(&iter_0, &v8) )
        break;
      plant = *std::_List_iterator<PlantActivity *>::operator*(&iter_0);
      if ( plant )
      {
        v1 = (*((__int64 (__fastcall **)(PlantActivity *))plant->_vptr_Entity + 2))(plant);
        Map::removePlant(this, v1);
        v2 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<PlantActivity>(v2, plant);
      }
    }
    std::list<PlantActivity *>::clear(&this->m_actPlants);
  }
  if ( !std::list<Trap *>::empty(&this->m_traps) )
  {
    for ( iter_1._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node;
          ;
          std::_List_iterator<Trap *>::operator++(&iter_1) )
    {
      v9._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
      if ( !std::_List_iterator<Trap *>::operator!=(&iter_1, &v9) )
        break;
      pTrap = *std::_List_iterator<Trap *>::operator*(&iter_1);
      if ( pTrap )
      {
        Trap::leaveMap(pTrap);
        v3 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<Trap>(v3, pTrap);
      }
    }
    std::list<Trap *>::clear(&this->m_traps);
  }
}


#####################################
bool __cdecl CActivityMap::IsActivityMap(const CActivityMap *const this)
{
  MapType mt; // [rsp+1Ch] [rbp-4h] BYREF

  mt = MapType::MT_NORMAL;
  return !CfgMap::isType(&this->m_cfgmap, &mt) || this->m_pActivity;
}


#####################################
void __cdecl CActivityMap::update(CActivityMap *const this)
{
  CTimer *v1; // rax
  int64_t curTick; // [rsp+18h] [rbp-8h]

  Map::update(this);
  if ( this->m_pActivity )
  {
    (*((void (__fastcall **)(CActivity *, CActivityMap *const))this->m_pActivity->_vptr_CActivity + 3))(
      this->m_pActivity,
      this);
    if ( CActivity::IsRuning(this->m_pActivity) )
    {
      v1 = Answer::Singleton<CTimer>::instance();
      curTick = CTimer::GetTick(v1);
      (*((void (__fastcall **)(CActivityMap *const))this->_vptr_Map + 30))(this);
      CActivityMap::checkAddMonster(this, curTick);
    }
  }
}


#####################################
void __cdecl CActivityMap::checkEvents(CActivityMap *const this)
{
  void (__fastcall *v1)(CActivityMap *const, CfgMapEvent *); // rbx
  CfgMapEvent *v2; // rdx
  std::_List_iterator<CfgMapEvent> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+20h] [rbp-20h] BYREF

  for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
        ;
        std::_List_iterator<CfgMapEvent>::operator++(&it) )
  {
    __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
    if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
      break;
    v1 = (void (__fastcall *)(CActivityMap *const, CfgMapEvent *))*((_QWORD *)this->_vptr_Map + 31);
    v2 = std::_List_iterator<CfgMapEvent>::operator*(&it);
    v1(this, v2);
  }
}


#####################################
int32_t __cdecl CActivityMap::canEnter(CActivityMap *const this, Player *player)
{
  if ( !player )
    return 10002;
  if ( this->m_pActivity )
    return (*((int32_t (__fastcall **)(CActivity *, Player *, CActivityMap *const))this->m_pActivity->_vptr_CActivity
            + 32))(
             this->m_pActivity,
             player,
             this);
  if ( (Map::GetType(this) & 1) != 0 )
    return Map::canEnter(this, player);
  return 10058;
}


#####################################
int32_t __cdecl CActivityMap::getPkMode(const CActivityMap *const this)
{
  int32_t pkMode; // [rsp+1Ch] [rbp-4h]

  pkMode = 0;
  if ( this->m_pActivity )
    pkMode = (*((__int64 (__fastcall **)(CActivity *))this->m_pActivity->_vptr_CActivity + 56))(this->m_pActivity);
  if ( !pkMode )
    return Map::getPkMode(this);
  return pkMode;
}


#####################################
bool __cdecl CActivityMap::CanSitRevive(CActivityMap *const this)
{
  if ( this->m_pActivity )
    return (*((bool (__fastcall **)(CActivity *))this->m_pActivity->_vptr_CActivity + 57))(this->m_pActivity);
  else
    return Map::CanSitRevive(this);
}


#####################################
bool __cdecl CActivityMap::SpecialSitRevive(CActivityMap *const this)
{
  if ( this->m_pActivity )
    return (*((bool (__fastcall **)(CActivity *))this->m_pActivity->_vptr_CActivity + 58))(this->m_pActivity);
  else
    return Map::SpecialSitRevive(this);
}


#####################################
int32_t __cdecl CActivityMap::getReive(CActivityMap *const this, Player *player)
{
  if ( this->m_pActivity && CActivity::GetType(this->m_pActivity) != 2 && CActivity::GetType(this->m_pActivity) != 14 )
    return (*((int32_t (__fastcall **)(CActivity *, Player *))this->m_pActivity->_vptr_CActivity + 14))(
             this->m_pActivity,
             player);
  else
    return Map::getReive(this, player);
}


#####################################
void __cdecl CActivityMap::removePlayer(CActivityMap *const this, Player *player, bool islogout)
{
  if ( this->m_pActivity )
    (*((void (__fastcall **)(CActivity *, Player *, bool))this->m_pActivity->_vptr_CActivity + 30))(
      this->m_pActivity,
      player,
      islogout);
  Map::removePlayer(this, player, islogout);
}


#####################################
void __cdecl CActivityMap::addPlayer(CActivityMap *const this, Player *player, int32_t x, int32_t y)
{
  int *v4; // rbx
  __int64 __k[3]; // [rsp+28h] [rbp-18h] BYREF

  Map::addPlayer(this, player, x, y);
  if ( this->m_pActivity )
    (*((void (__fastcall **)(CActivity *, Player *))this->m_pActivity->_vptr_CActivity + 31))(this->m_pActivity, player);
  if ( Map::GetMapParam(this) == 5 )
    CActivityMap::SendUltimateChallengeInfo(this, player);
  __k[0] = Player::getCid(player);
  v4 = std::map<long,int>::operator[](&this->m_CidBattle, __k);
  *v4 = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 10))(player);
}


#####################################
int32_t __cdecl CActivityMap::GetTop10Battle(CActivityMap *const this)
{
  std::pair<const long int,int> *v1; // rax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v3; // rax
  int *v4; // rax
  int32_t v5; // ebx
  std::reverse_iterator<__gnu_cxx::__normal_iterator<int*,std::vector<int> > > v7; // [rsp+0h] [rbp-90h] BYREF
  CActivityMap *thisa; // [rsp+18h] [rbp-78h]
  std::reverse_iterator<__gnu_cxx::__normal_iterator<int*,std::vector<int> > > itVt; // [rsp+20h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+30h] [rbp-60h] BYREF
  std::vector<int> BattleVt; // [rsp+40h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > __x; // [rsp+60h] [rbp-30h] BYREF
  std::vector<int> v13; // [rsp+70h] [rbp-20h] BYREF

  thisa = this;
  std::vector<int>::vector(&BattleVt);
  for ( it._M_node = std::map<long,int>::begin(&this->m_CidBattle)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<long,int>::end(&thisa->m_CidBattle)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&it, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it);
    std::vector<int>::push_back(&BattleVt, &v1->second);
  }
  v13._M_impl._M_finish = 0;
  M_current = std::vector<int>::end(&BattleVt)._M_current;
  v3._M_current = std::vector<int>::begin(&BattleVt)._M_current;
  std::sort<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
    v3,
    (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
  std::vector<int>::rbegin((std::vector<int> *const)&itVt);
  while ( 1 )
  {
    std::vector<int>::rend(&v13);
    if ( !std::operator!=<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
            &itVt,
            (const std::reverse_iterator<__gnu_cxx::__normal_iterator<int*,std::vector<int> > > *const)&v13) )
      break;
    ++LODWORD(v13._M_impl._M_finish);
    v4 = std::reverse_iterator<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>::operator*(&itVt);
    HIDWORD(v13._M_impl._M_finish) += *v4;
    if ( SLODWORD(v13._M_impl._M_finish) > 9 )
      break;
    std::reverse_iterator<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>::operator++(&v7, (int)&itVt);
  }
  if ( SLODWORD(v13._M_impl._M_finish) <= 0 )
    v5 = 0;
  else
    v5 = ((__int64)v13._M_impl._M_finish >> 32) / SLODWORD(v13._M_impl._M_finish);
  std::vector<int>::~vector(&BattleVt);
  return v5;
}


#####################################
int32_t __cdecl CActivityMap::HaveAliveMonster(CActivityMap *const this)
{
  Monster **v1; // rax
  Monster **v2; // rax
  std::_List_iterator<Monster*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-4h]

  Count = 0;
  for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it, 0) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    v1 = std::_List_iterator<Monster *>::operator*(&it);
    if ( Unit::isAlive(*v1) )
    {
      v2 = std::_List_iterator<Monster *>::operator*(&it);
      if ( (*((unsigned __int8 (__fastcall **)(Monster *))(*v2)->_vptr_Entity + 17))(*v2) )
        ++Count;
    }
  }
  return Count;
}


#####################################
int32_t __cdecl CActivityMap::HaveAlivePet(CActivityMap *const this)
{
  CObjPet **v1; // rax
  std::_List_iterator<CObjPet*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CObjPet*> __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-4h]

  Count = 0;
  for ( it._M_node = std::list<CObjPet *>::begin(&this->m_pets)._M_node;
        ;
        std::_List_iterator<CObjPet *>::operator++(&it, 0) )
  {
    __x._M_node = std::list<CObjPet *>::end(&this->m_pets)._M_node;
    if ( !std::_List_iterator<CObjPet *>::operator!=(&it, &__x) )
      break;
    v1 = std::_List_iterator<CObjPet *>::operator*(&it);
    if ( Unit::isAlive(*v1) )
      ++Count;
  }
  return Count;
}


#####################################
bool __cdecl CActivityMap::OnSitRevive(CActivityMap *const this, Player *player)
{
  if ( this->m_pActivity && CActivity::IsRuning(this->m_pActivity) )
    return (*((bool (__fastcall **)(CActivity *, Player *))this->m_pActivity->_vptr_CActivity + 12))(
             this->m_pActivity,
             player);
  else
    return Map::OnSitRevive(this, player);
}


#####################################
void __cdecl CActivityMap::onActivityStart(CActivityMap *const this, CActivity *pActivity)
{
  int64_t Tick; // rbx
  MapId_t MapId; // r13d
  int32_t Id; // r12d
  CfgData *v5; // rax
  const CfgMapEventList *ActivityEvents; // rax
  CTimer *v7; // rax

  if ( pActivity )
  {
    this->m_pActivity = pActivity;
    Tick = Map::getTick(this);
    MapId = Map::GetMapId(this);
    Id = CActivity::GetId(pActivity);
    v5 = Answer::Singleton<CfgData>::instance();
    ActivityEvents = CfgData::getActivityEvents(v5, Id, MapId);
    IMapEvent::init(&this->IMapEvent, ActivityEvents, Tick);
    v7 = Answer::Singleton<CTimer>::instance();
    this->m_nStartTick = CTimer::GetTick(v7);
  }
}


#####################################
void __cdecl CActivityMap::onPlayerKilled(CActivityMap *const this, Player *pDier, Player *pKiller)
{
  if ( this->m_pActivity && CActivity::IsRuning(this->m_pActivity) )
    (*((void (__fastcall **)(CActivity *, Player *, Player *))this->m_pActivity->_vptr_CActivity + 40))(
      this->m_pActivity,
      pDier,
      pKiller);
}


#####################################
void __cdecl CActivityMap::onPlayerRevive(CActivityMap *const this, Player *player, bool bSafe)
{
  if ( this->m_pActivity && CActivity::IsRuning(this->m_pActivity) )
    (*((void (__fastcall **)(CActivity *, Player *, bool))this->m_pActivity->_vptr_CActivity + 41))(
      this->m_pActivity,
      player,
      bSafe);
}


#####################################
void __cdecl CActivityMap::onMonsterDie(CActivityMap *const this, MonsterActivity *monster)
{
  std::pair<const int,MonsterWave> *v3; // rax
  CfgMapEvent *v4; // rax
  CfgMapEvent *v5; // rax
  void (__fastcall *v7)(CActivityMap *const, CfgMapEvent *); // rbx
  CfgMapEvent *v8; // rdx
  CfgMapEvent *v9; // rax
  int v10; // ebx
  void (__fastcall *v11)(CActivityMap *const, CfgMapEvent *, MonsterActivity *); // r12
  CfgMapEvent *v12; // rcx
  std::_List_iterator<CfgMapEvent> it_0; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it; // [rsp+20h] [rbp-40h] BYREF
  int __x; // [rsp+2Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v16; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> v17; // [rsp+40h] [rbp-20h] BYREF

  if ( this->m_pActivity && monster && CActivity::IsRuning(this->m_pActivity) )
  {
    (*((void (__fastcall **)(CActivity *, MonsterActivity *))this->m_pActivity->_vptr_CActivity + 38))(
      this->m_pActivity,
      monster);
    __x = MonsterActivity::getWave(monster);
    it._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &__x)._M_node;
    v16._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it, &v16) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it);
      ++v3->second.killed;
    }
    for ( it_0._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it_0) )
    {
      v17._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it_0, &v17) )
        break;
      v4 = std::_List_iterator<CfgMapEvent>::operator->(&it_0);
      if ( CfgMapEvent::isOpen(v4) )
      {
        v5 = std::_List_iterator<CfgMapEvent>::operator->(&it_0);
        if ( !CfgMapEvent::isDone(v5) )
        {
          if ( std::_List_iterator<CfgMapEvent>::operator->(&it_0)->trigger_type == 2 )
          {
            v7 = (void (__fastcall *)(CActivityMap *const, CfgMapEvent *))*((_QWORD *)this->_vptr_Map + 31);
            v8 = std::_List_iterator<CfgMapEvent>::operator*(&it_0);
            v7(this, v8);
          }
          else if ( std::_List_iterator<CfgMapEvent>::operator->(&it_0)->trigger_type == 5 )
          {
            v9 = std::_List_iterator<CfgMapEvent>::operator->(&it_0);
            v10 = *std::vector<int>::operator[](&v9->trigger_param, 0);
            if ( v10 == MonsterActivity::getActivityMonsterId(monster) )
            {
              v11 = (void (__fastcall *)(CActivityMap *const, CfgMapEvent *, MonsterActivity *))*((_QWORD *)this->_vptr_Map
                                                                                                + 32);
              v12 = std::_List_iterator<CfgMapEvent>::operator*(&it_0);
              v11(this, v12, monster);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CActivityMap::onMonsterHPEvent(CActivityMap *const this, MonsterActivity *monster, int32_t id)
{
  CfgMapEvent *v3; // rax
  CfgMapEvent *v4; // rax
  void (__fastcall *v6)(CActivityMap *const, CfgMapEvent *, MonsterActivity *); // r12
  CfgMapEvent *v7; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( monster )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( CfgMapEvent::isOpen(v3) )
      {
        v4 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v4) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_id == id )
        {
          v6 = (void (__fastcall *)(CActivityMap *const, CfgMapEvent *, MonsterActivity *))*((_QWORD *)this->_vptr_Map
                                                                                           + 32);
          v7 = std::_List_iterator<CfgMapEvent>::operator*(&it);
          v6(this, v7, monster);
        }
      }
    }
  }
}


#####################################
void __cdecl CActivityMap::onMonsterDie(
        CActivityMap *const this,
        Monster *monster,
        Player *player,
        bool IsGroupMonster)
{
  MonsterActivity *v4; // rax
  MonsterActivity *pMonster; // [rsp+28h] [rbp-18h]

  Map::onMonsterDie(this, monster, player, IsGroupMonster);
  if ( monster )
    v4 = (MonsterActivity *)__dynamic_cast(
                              monster,
                              (const struct __class_type_info *)&`typeinfo for'Monster,
                              (const struct __class_type_info *)&`typeinfo for'MonsterActivity,
                              0);
  else
    v4 = 0;
  pMonster = v4;
  if ( this->m_pActivity && v4 )
  {
    (*((void (__fastcall **)(CActivity *, MonsterActivity *, Player *))this->m_pActivity->_vptr_CActivity + 39))(
      this->m_pActivity,
      v4,
      player);
    if ( Map::GetMapParam(this) == 5
      && (*((unsigned __int8 (__fastcall **)(MonsterActivity *))pMonster->_vptr_Entity + 17))(pMonster) )
    {
      CActivityMap::SendUltimateChallengeInfo(this, 0);
    }
  }
}


#####################################
int32_t __cdecl CActivityMap::onBeginGather(CActivityMap *const this, PlantActivity *plant, Player *player)
{
  if ( this->m_pActivity )
    return (*((int32_t (__fastcall **)(CActivity *, PlantActivity *, Player *))this->m_pActivity->_vptr_CActivity + 18))(
             this->m_pActivity,
             plant,
             player);
  else
    return 2;
}


#####################################
void __cdecl CActivityMap::onPlantGather(CActivityMap *const this, PlantActivity *plant, Player *player)
{
  CfgMapEvent *v3; // rax
  CfgMapEvent *v4; // rax
  CfgMapEvent *v5; // rax
  int v6; // ebx
  void (__fastcall *v8)(CActivityMap *const, CfgMapEvent *, _QWORD); // rbx
  CfgMapEvent *v9; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( plant && this->m_pActivity )
  {
    (*((void (__fastcall **)(CActivity *, PlantActivity *, Player *))this->m_pActivity->_vptr_CActivity + 17))(
      this->m_pActivity,
      plant,
      player);
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( CfgMapEvent::isOpen(v3) )
      {
        v4 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v4) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 6 )
        {
          v5 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          v6 = *std::vector<int>::operator[](&v5->trigger_param, 0);
          if ( v6 == Plant::getPlantId(plant) )
          {
            v8 = (void (__fastcall *)(CActivityMap *const, CfgMapEvent *, _QWORD))*((_QWORD *)this->_vptr_Map + 32);
            v9 = std::_List_iterator<CfgMapEvent>::operator*(&it);
            v8(this, v9, 0);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CActivityMap::onMonsterDamaged(
        CActivityMap *const this,
        MonsterActivity *pMonster,
        int32_t nDamage,
        const UnitHandle *const launcher)
{
  int32_t RunnerId; // r12d
  EntityId_t id; // rbx
  GameService *v6; // rax
  int32_t v7; // r12d
  EntityId_t v8; // rbx
  GameService *v9; // rax
  Player *pAttacker; // [rsp+20h] [rbp-20h]
  CObjPet *pPet; // [rsp+28h] [rbp-18h]

  if ( this->m_pActivity && CActivity::IsRuning(this->m_pActivity) )
  {
    pAttacker = 0;
    if ( launcher->type == 1 )
    {
      RunnerId = Map::GetRunnerId(this);
      id = launcher->id;
      v6 = Answer::Singleton<GameService>::instance();
      pAttacker = GameService::getPlayer(v6, id, RunnerId, 1);
    }
    else if ( launcher->type == 4 )
    {
      v7 = Map::GetRunnerId(this);
      v8 = launcher->id;
      v9 = Answer::Singleton<GameService>::instance();
      pPet = GameService::getPet(v9, v8, v7);
      if ( pPet )
        pAttacker = CObjPet::GetPlayer(pPet);
    }
    if ( pAttacker )
      (*((void (__fastcall **)(CActivity *, MonsterActivity *, _QWORD, Player *))this->m_pActivity->_vptr_CActivity + 37))(
        this->m_pActivity,
        pMonster,
        (unsigned int)nDamage,
        pAttacker);
  }
}


#####################################
void __cdecl CActivityMap::checkEvent(CActivityMap *const this, CfgMapEvent *const mapEvent)
{
  int64_t v3; // rbx
  int *v5; // rax
  std::pair<const int,MonsterWave> *v6; // rax
  int *v8; // rax
  std::pair<const int,MonsterWave> *v9; // rax
  int64_t Tick; // rbx
  int64_t v11; // rbx
  int32_t v13; // ebx
  int *v14; // rax
  int32_t v15; // ebx
  int *v16; // rax
  std::_List_iterator<Player*> it_2; // [rsp+10h] [rbp-C0h] BYREF
  Position ps2; // [rsp+20h] [rbp-B0h] BYREF
  Position ps1; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it_1; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > __x; // [rsp+70h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v24; // [rsp+90h] [rbp-40h] BYREF
  std::_List_iterator<Player*> v25; // [rsp+A0h] [rbp-30h] BYREF
  int32_t nsize; // [rsp+ACh] [rbp-24h]
  int32_t count; // [rsp+B0h] [rbp-20h]
  int32_t i; // [rsp+B4h] [rbp-1Ch]
  Player *pPlayer; // [rsp+B8h] [rbp-18h]

  if ( CfgMapEvent::isOpen(mapEvent) && !CfgMapEvent::isDone(mapEvent) )
  {
    switch ( mapEvent->trigger_type )
    {
      case 1:
        if ( !std::vector<int>::empty(&mapEvent->trigger_param) )
        {
          v3 = Map::getTick(this) - mapEvent->nOpenTime;
          if ( v3 >= 1000 * *std::vector<int>::operator[](&mapEvent->trigger_param, 0) )
            (*((void (__fastcall **)(CActivityMap *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 32))(
              this,
              mapEvent,
              0);
        }
        break;
      case 2:
        if ( !std::vector<int>::empty(&mapEvent->trigger_param) )
        {
          v5 = std::vector<int>::operator[](&mapEvent->trigger_param, 0);
          it._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, v5)._M_node;
          __x._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it, &__x) )
          {
            v6 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it);
            if ( !MonsterWave::alive(&v6->second) )
              (*((void (__fastcall **)(CActivityMap *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 32))(
                this,
                mapEvent,
                0);
          }
        }
        break;
      case 3:
        if ( std::vector<int>::size(&mapEvent->trigger_param) > 1 )
        {
          nsize = std::vector<int>::size(&mapEvent->trigger_param);
          if ( nsize > 0 )
          {
            count = 0;
            i = 0;
          }
        }
        break;
      case 4:
        if ( std::vector<int>::size(&mapEvent->trigger_param) == 2 )
        {
          v8 = std::vector<int>::operator[](&mapEvent->trigger_param, 0);
          it_1._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, v8)._M_node;
          v24._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it_1, &v24) )
          {
            v9 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_1);
            if ( !MonsterWave::alive(&v9->second) )
            {
              Tick = Map::getTick(this);
              v11 = Tick - std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_1)->second.startTime;
              if ( v11 <= 1000 * *std::vector<int>::operator[](&mapEvent->trigger_param, 1u) )
                (*((void (__fastcall **)(CActivityMap *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 32))(
                  this,
                  mapEvent,
                  0);
            }
          }
        }
        break;
      case 7:
        if ( std::vector<int>::size(&mapEvent->trigger_param) == 4 )
        {
          v13 = *std::vector<int>::operator[](&mapEvent->trigger_param, 1u);
          v14 = std::vector<int>::operator[](&mapEvent->trigger_param, 0);
          Position::Position(&ps1, *v14, v13);
          v15 = *std::vector<int>::operator[](&mapEvent->trigger_param, 3u);
          v16 = std::vector<int>::operator[](&mapEvent->trigger_param, 2u);
          Position::Position(&ps2, *v16, v15);
          for ( it_2._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
                ;
                std::_List_iterator<Player *>::operator++(&it_2) )
          {
            v25._M_node = std::list<Player *>::end(&this->m_players)._M_node;
            if ( !std::_List_iterator<Player *>::operator!=(&it_2, &v25) )
              break;
            pPlayer = *std::_List_iterator<Player *>::operator*(&it_2);
            if ( pPlayer && Player::isInRectangle(pPlayer, ps1, ps2) )
              (*((void (__fastcall **)(CActivityMap *const, CfgMapEvent *const, Player *))this->_vptr_Map + 32))(
                this,
                mapEvent,
                pPlayer);
          }
        }
        break;
      default:
        return;
    }
  }
}


#####################################
void __cdecl CActivityMap::triggerEvent(CActivityMap *const this, CfgMapEvent *const mapEvent, Unit *pUnit)
{
  std::string *v3; // rax
  const char *v4; // rax
  int32_t v5; // ebx
  CfgData *v6; // rax
  int32_t tid; // ebx
  CfgData *v8; // rax
  CPoolManager *v9; // rax
  EntityId_t v10; // rdx
  std::string *v11; // rax
  const char *v12; // rax
  int32_t v13; // ebx
  CfgData *v14; // rax
  int32_t plant_id; // ebx
  CfgData *v16; // rax
  int32_t region_id; // ebx
  CfgData *v18; // rax
  int32_t mapid; // ebx
  CPoolManager *v21; // rax
  int v22; // ebx
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v24; // rax
  CPoolManager *v25; // rax
  std::string *v27; // rax
  const char *v28; // rax
  int64_t v29; // rax
  int32_t ActivityMonsterId; // ebx
  std::string *v31; // rax
  const char *v32; // rax
  std::string *v34; // rax
  std::string *v35; // rax
  const char *v36; // rax
  int32_t v37; // ebx
  std::string *v38; // rax
  const char *v39; // rax
  int32_t v40; // eax
  std::string *v41; // rax
  std::string *v42; // rax
  const char *v43; // rax
  int32_t v44; // ebx
  std::string *v45; // rax
  const char *v46; // rax
  int32_t v47; // eax
  Monster *v48; // rax
  const char *v49; // rax
  GameService *v50; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v53; // rax
  CfgData *v54; // rax
  std::string *v55; // rax
  const char *v56; // rax
  const char *v57; // rax
  GameService *v58; // rax
  uint32_t v59; // eax
  GameService *v60; // rax
  std::string *v61; // rax
  std::string *v62; // rax
  const char *v63; // rax
  std::string *v64; // rax
  const char *v65; // rax
  int *v66; // rax
  std::pair<const int,int> *v67; // rax
  std::string *v68; // rax
  std::string *v69; // rax
  const char *v70; // rax
  std::string *v71; // rax
  const char *v72; // rax
  int *v73; // rax
  GameService *v74; // rax
  std::pair<const int,int> *v75; // rax
  int64_t Tick; // rdx
  Int32Int32Map BattleMonster; // [rsp+20h] [rbp-5D0h] BYREF
  MonsterWait stu; // [rsp+50h] [rbp-5A0h] BYREF
  int32_t Battle_0; // [rsp+7Ch] [rbp-574h] BYREF
  StringVector BattleVt_0; // [rsp+80h] [rbp-570h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it_6; // [rsp+A0h] [rbp-550h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > strit_0; // [rsp+B0h] [rbp-540h] BYREF
  StringVector strIds_5; // [rsp+C0h] [rbp-530h] BYREF
  int32_t Battle; // [rsp+DCh] [rbp-514h] BYREF
  StringVector BattleVt; // [rsp+E0h] [rbp-510h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it_5; // [rsp+100h] [rbp-4F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > strit; // [rsp+110h] [rbp-4E0h] BYREF
  StringVector strIds_4; // [rsp+120h] [rbp-4D0h] BYREF
  StringVector strIds_3; // [rsp+140h] [rbp-4B0h] BYREF
  StringVector vstack_0; // [rsp+160h] [rbp-490h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_4; // [rsp+180h] [rbp-470h] BYREF
  StringVector strstacks_0; // [rsp+190h] [rbp-460h] BYREF
  PosList stacks_0; // [rsp+1B0h] [rbp-440h] BYREF
  StringVector vstack; // [rsp+1C0h] [rbp-430h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_3; // [rsp+1E0h] [rbp-410h] BYREF
  StringVector strstacks; // [rsp+1F0h] [rbp-400h] BYREF
  PosList stacks; // [rsp+210h] [rbp-3E0h] BYREF
  std::_List_iterator<MonsterActivity*> iter_0; // [rsp+220h] [rbp-3D0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_2; // [rsp+230h] [rbp-3C0h] BYREF
  StringVector strIds_2; // [rsp+240h] [rbp-3B0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_1; // [rsp+260h] [rbp-390h] BYREF
  StringVector strIds_1; // [rsp+270h] [rbp-380h] BYREF
  Int32List events; // [rsp+290h] [rbp-360h] BYREF
  PlantActivity *plant; // [rsp+2A8h] [rbp-348h] BYREF
  CfgMapPlant mapPlant; // [rsp+2B0h] [rbp-340h] BYREF
  Position pos; // [rsp+2C0h] [rbp-330h]
  std::vector<Position> PosVector; // [rsp+2D0h] [rbp-320h] BYREF
  PlantActivity *plant_0; // [rsp+2E8h] [rbp-308h] BYREF
  CfgMapPlant mapPlant_0; // [rsp+2F0h] [rbp-300h] BYREF
  Position pos_0; // [rsp+300h] [rbp-2F0h]
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_0; // [rsp+310h] [rbp-2E0h] BYREF
  std::_List_iterator<PlantActivity*> iter; // [rsp+320h] [rbp-2D0h] BYREF
  StringVector strIds_0; // [rsp+330h] [rbp-2C0h] BYREF
  Position trapPos; // [rsp+350h] [rbp-2A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+360h] [rbp-290h] BYREF
  StringVector strIds; // [rsp+370h] [rbp-280h] BYREF
  std::string delims; // [rsp+390h] [rbp-260h] BYREF
  char v119; // [rsp+39Fh] [rbp-251h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+3A0h] [rbp-250h] BYREF
  std::_List_iterator<PlantActivity*> __x; // [rsp+3B0h] [rbp-240h] BYREF
  std::string v122; // [rsp+3C0h] [rbp-230h] BYREF
  char v123; // [rsp+3CFh] [rbp-221h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v124; // [rsp+3D0h] [rbp-220h] BYREF
  std::string v125; // [rsp+3E0h] [rbp-210h] BYREF
  char v126; // [rsp+3EFh] [rbp-201h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v127; // [rsp+3F0h] [rbp-200h] BYREF
  int v128; // [rsp+3FCh] [rbp-1F4h] BYREF
  std::string v129; // [rsp+400h] [rbp-1F0h] BYREF
  char v130; // [rsp+40Fh] [rbp-1E1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v131; // [rsp+410h] [rbp-1E0h] BYREF
  std::_List_iterator<MonsterActivity*> v132; // [rsp+420h] [rbp-1D0h] BYREF
  std::string v133; // [rsp+430h] [rbp-1C0h] BYREF
  char v134; // [rsp+43Fh] [rbp-1B1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v135; // [rsp+440h] [rbp-1B0h] BYREF
  std::string v136; // [rsp+450h] [rbp-1A0h] BYREF
  char v137; // [rsp+45Fh] [rbp-191h] BYREF
  Position v138; // [rsp+460h] [rbp-190h] BYREF
  std::string v139; // [rsp+470h] [rbp-180h] BYREF
  char v140; // [rsp+47Fh] [rbp-171h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v141; // [rsp+480h] [rbp-170h] BYREF
  std::string v142; // [rsp+490h] [rbp-160h] BYREF
  char v143; // [rsp+49Fh] [rbp-151h] BYREF
  Position v144; // [rsp+4A0h] [rbp-150h] BYREF
  std::string val; // [rsp+4B0h] [rbp-140h] BYREF
  std::string v146; // [rsp+4C0h] [rbp-130h] BYREF
  char v147; // [rsp+4CFh] [rbp-121h] BYREF
  std::string v148; // [rsp+4D0h] [rbp-120h] BYREF
  char v149; // [rsp+4DFh] [rbp-111h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v150; // [rsp+4E0h] [rbp-110h] BYREF
  std::string v151; // [rsp+4F0h] [rbp-100h] BYREF
  char v152; // [rsp+4FFh] [rbp-F1h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v153; // [rsp+500h] [rbp-F0h] BYREF
  std::string v154; // [rsp+510h] [rbp-E0h] BYREF
  char v155; // [rsp+51Fh] [rbp-D1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v156; // [rsp+520h] [rbp-D0h] BYREF
  std::string v157; // [rsp+530h] [rbp-C0h] BYREF
  char v158; // [rsp+53Fh] [rbp-B1h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v159; // [rsp+540h] [rbp-B0h] BYREF
  CfgActivityTrap *pCfgActivityTrap; // [rsp+550h] [rbp-A0h]
  CfgTrap *pCfgTrap; // [rsp+558h] [rbp-98h]
  Trap *pTrap; // [rsp+560h] [rbp-90h]
  PlantActivity *pPlant; // [rsp+568h] [rbp-88h]
  CfgActivityPlant *pCfgActivityPlan; // [rsp+570h] [rbp-80h]
  CfgPlant *pCfgPlant; // [rsp+578h] [rbp-78h]
  CfgMapRegion *pCfgRegion; // [rsp+580h] [rbp-70h]
  int32_t i_0; // [rsp+58Ch] [rbp-64h]
  int32_t nSize; // [rsp+590h] [rbp-60h]
  int32_t i; // [rsp+594h] [rbp-5Ch]
  MonsterActivity *pMonster; // [rsp+598h] [rbp-58h]
  Monster *pMonster_0; // [rsp+5A0h] [rbp-50h]
  int32_t bcid; // [rsp+5ACh] [rbp-44h]
  Answer::NetPacket *packet; // [rsp+5B0h] [rbp-40h]
  Player *pKiller; // [rsp+5B8h] [rbp-38h]
  int32_t KiaFuDay; // [rsp+5C0h] [rbp-30h]
  int32_t GongGaoId; // [rsp+5C4h] [rbp-2Ch]
  Answer::NetPacket *packet_0; // [rsp+5C8h] [rbp-28h]
  int32_t AvgBattle; // [rsp+5D0h] [rbp-20h]
  int32_t BossId; // [rsp+5D4h] [rbp-1Ch]
  int32_t AvgBattle_0; // [rsp+5D8h] [rbp-18h]
  int32_t BossId_0; // [rsp+5DCh] [rbp-14h]

  if ( this->m_pActivity )
  {
    switch ( mapEvent->event_type )
    {
      case 1:
        CActivityMap::generateMonster(this, &mapEvent->effect);
        goto LABEL_121;
      case 2:
        std::allocator<char>::allocator(&v119);
        std::string::string(&delims, L":|", &v119);
        Answer::StringUtility::split(&strIds, &mapEvent->effect, &delims, 0);
        std::string::~string(&delims);
        std::allocator<char>::~allocator(&v119);
        for ( it._M_current = std::vector<std::string>::begin(&strIds)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<std::string>::end(&strIds)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
            break;
          v3 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
          v4 = (const char *)std::string::c_str(v3);
          v5 = atoi(v4);
          v6 = Answer::Singleton<CfgData>::instance();
          pCfgActivityTrap = CfgData::getActivityTrap(v6, v5);
          if ( pCfgActivityTrap )
          {
            tid = pCfgActivityTrap->tid;
            v8 = Answer::Singleton<CfgData>::instance();
            pCfgTrap = CfgData::getTrap(v8, tid);
            if ( pCfgTrap )
            {
              Position::Position(&trapPos, pCfgActivityTrap->x, pCfgActivityTrap->y);
              if ( pUnit )
                trapPos = StaticObj::getCurrentTile(pUnit);
              if ( trapPos.x > 0 && trapPos.y > 0 )
              {
                v9 = Answer::Singleton<CPoolManager>::instance();
                pTrap = CPoolManager::pop<Trap>(v9);
                if ( pTrap )
                {
                  Trap::init(pTrap, this, trapPos, pCfgTrap);
                  Map::addTrap(this, pTrap);
                }
              }
            }
          }
        }
        std::vector<std::string>::~vector(&strIds);
        goto LABEL_121;
      case 3:
        iter._M_node = std::list<PlantActivity *>::begin(&this->m_actPlants)._M_node;
        while ( 1 )
        {
          __x._M_node = std::list<PlantActivity *>::end(&this->m_actPlants)._M_node;
          if ( !std::_List_iterator<PlantActivity *>::operator!=(&iter, &__x) )
            break;
          pPlant = *std::_List_iterator<PlantActivity *>::operator*(&iter);
          if ( Plant::GetPlantType(pPlant) == 1 )
          {
            std::_List_iterator<PlantActivity *>::operator++(&iter);
          }
          else
          {
            Plant::broadcastRemove(pPlant);
            v10 = (*((__int64 (__fastcall **)(PlantActivity *))pPlant->_vptr_Entity + 2))(pPlant);
            Map::removePlant(this, v10);
            iter._M_node = std::list<PlantActivity *>::erase(&this->m_actPlants, iter)._M_node;
          }
        }
        std::allocator<char>::allocator(&v123);
        std::string::string(&v122, L":|", &v123);
        Answer::StringUtility::split(&strIds_0, &mapEvent->effect, &v122, 0);
        std::string::~string(&v122);
        std::allocator<char>::~allocator(&v123);
        it_0._M_current = std::vector<std::string>::begin(&strIds_0)._M_current;
        while ( 2 )
        {
          v124._M_current = std::vector<std::string>::end(&strIds_0)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_0, &v124) )
            goto LABEL_55;
          v11 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_0);
          v12 = (const char *)std::string::c_str(v11);
          v13 = atoi(v12);
          v14 = Answer::Singleton<CfgData>::instance();
          pCfgActivityPlan = CfgData::getActivityPlant(v14, v13);
          if ( !pCfgActivityPlan )
            goto LABEL_55;
          plant_id = pCfgActivityPlan->plant_id;
          v16 = Answer::Singleton<CfgData>::instance();
          pCfgPlant = CfgData::getPlant(v16, plant_id);
          if ( !pCfgPlant )
            goto LABEL_53;
          if ( pCfgActivityPlan->region_id > 0 )
          {
            region_id = pCfgActivityPlan->region_id;
            v18 = Answer::Singleton<CfgData>::instance();
            pCfgRegion = CfgData::getMapRegion(v18, region_id);
            if ( pCfgRegion )
            {
              mapid = pCfgRegion->mapid;
              if ( mapid == Map::GetMapId(this) )
              {
                for ( i_0 = 0; pCfgActivityPlan->count > i_0; ++i_0 )
                {
                  pos_0 = Map::getRandomWalkablePositionInRegion(this, pCfgRegion);
                  if ( pos_0.x > 0 && pos_0.y > 0 )
                  {
                    mapPlant_0.mapid = Map::GetMapId(this);
                    mapPlant_0.plantid = pCfgPlant->id;
                    *(Position *)&mapPlant_0.x = pos_0;
                    v21 = Answer::Singleton<CPoolManager>::instance();
                    plant_0 = CPoolManager::pop<PlantActivity>(v21);
                    if ( plant_0 )
                    {
                      PlantActivity::init(plant_0, this, pCfgPlant, &mapPlant_0, pCfgActivityPlan->life_time);
                      Map::addPlant(this, plant_0);
                      std::list<PlantActivity *>::push_back(&this->m_actPlants, &plant_0);
                      (*((void (__fastcall **)(CActivity *, PlantActivity *))this->m_pActivity->_vptr_CActivity + 19))(
                        this->m_pActivity,
                        plant_0);
                    }
                  }
                }
              }
            }
LABEL_53:
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_0);
            continue;
          }
          break;
        }
        std::vector<Position>::vector(&PosVector, &pCfgActivityPlan->EnterPosVector);
        nSize = std::vector<Position>::size(&PosVector);
        if ( nSize > 0 )
        {
          M_current = std::vector<Position>::end(&PosVector)._M_current;
          v24._M_current = std::vector<Position>::begin(&PosVector)._M_current;
          std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
            v24,
            (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
          for ( i = 0; pCfgActivityPlan->count > i && i < nSize; ++i )
          {
            pos = *std::vector<Position>::operator[](&PosVector, i);
            if ( pos.x > 0 && pos.y > 0 )
            {
              mapPlant.mapid = Map::GetMapId(this);
              mapPlant.plantid = pCfgPlant->id;
              *(Position *)&mapPlant.x = pos;
              v25 = Answer::Singleton<CPoolManager>::instance();
              plant = CPoolManager::pop<PlantActivity>(v25);
              if ( plant )
              {
                PlantActivity::init(plant, this, pCfgPlant, &mapPlant, pCfgActivityPlan->life_time);
                Map::addPlant(this, plant);
                std::list<PlantActivity *>::push_back(&this->m_actPlants, &plant);
                (*((void (__fastcall **)(CActivity *, PlantActivity *))this->m_pActivity->_vptr_CActivity + 19))(
                  this->m_pActivity,
                  plant);
              }
            }
          }
          v22 = 1;
        }
        else
        {
          v22 = 0;
        }
        std::vector<Position>::~vector(&PosVector);
        if ( v22 )
          goto LABEL_53;
LABEL_55:
        std::vector<std::string>::~vector(&strIds_0);
LABEL_121:
        Tick = Map::getTick(this);
        CfgMapEvent::trig(mapEvent, Tick);
        break;
      case 4:
        std::list<int>::list(&events);
        std::allocator<char>::allocator(&v126);
        std::string::string(&v125, L":|", &v126);
        Answer::StringUtility::split(&strIds_1, &mapEvent->effect, &v125, 0);
        std::string::~string(&v125);
        std::allocator<char>::~allocator(&v126);
        for ( it_1._M_current = std::vector<std::string>::begin(&strIds_1)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_1) )
        {
          v127._M_current = std::vector<std::string>::end(&strIds_1)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_1, &v127) )
            break;
          v27 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_1);
          v28 = (const char *)std::string::c_str(v27);
          v128 = atoi(v28);
          std::list<int>::push_back(&events, &v128);
        }
        v29 = Map::getTick(this);
        IMapEvent::openEvents(&this->IMapEvent, &events, v29);
        std::vector<std::string>::~vector(&strIds_1);
        std::list<int>::~list(&events);
        goto LABEL_121;
      case 5:
        std::allocator<char>::allocator(&v130);
        std::string::string(&v129, L":|", &v130);
        Answer::StringUtility::split(&strIds_2, &mapEvent->effect, &v129, 0);
        std::string::~string(&v129);
        std::allocator<char>::~allocator(&v130);
        it_2._M_current = std::vector<std::string>::begin(&strIds_2)._M_current;
        while ( 2 )
        {
          v131._M_current = std::vector<std::string>::end(&strIds_2)._M_current;
          if ( __gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_2, &v131) )
          {
            for ( iter_0._M_node = std::list<MonsterActivity *>::begin(&this->m_actMonsters)._M_node;
                  ;
                  std::_List_iterator<MonsterActivity *>::operator++(&iter_0) )
            {
              v132._M_node = std::list<MonsterActivity *>::end(&this->m_actMonsters)._M_node;
              if ( !std::_List_iterator<MonsterActivity *>::operator!=(&iter_0, &v132) )
                goto LABEL_70;
              pMonster = *std::_List_iterator<MonsterActivity *>::operator*(&iter_0);
              if ( pMonster )
              {
                ActivityMonsterId = MonsterActivity::getActivityMonsterId(pMonster);
                v31 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_2);
                v32 = (const char *)std::string::c_str(v31);
                if ( ActivityMonsterId == atoi(v32) )
                  break;
              }
            }
            MonsterActivity::remove(pMonster);
            std::list<MonsterActivity *>::erase(&this->m_actMonsters, iter_0);
LABEL_70:
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_2);
            continue;
          }
          break;
        }
        std::vector<std::string>::~vector(&strIds_2);
        goto LABEL_121;
      case 6:
        std::list<Position>::list(&stacks);
        std::allocator<char>::allocator(&v134);
        std::string::string(&v133, 9181714, &v134);
        Answer::StringUtility::split(&strstacks, &mapEvent->effect, &v133, 0);
        std::string::~string(&v133);
        std::allocator<char>::~allocator(&v134);
        for ( it_3._M_current = std::vector<std::string>::begin(&strstacks)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_3) )
        {
          v135._M_current = std::vector<std::string>::end(&strstacks)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_3, &v135) )
            break;
          std::allocator<char>::allocator(&v137);
          std::string::string(&v136, L":|", &v137);
          v34 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_3);
          Answer::StringUtility::split(&vstack, v34, &v136, 0);
          std::string::~string(&v136);
          std::allocator<char>::~allocator(&v137);
          if ( std::vector<std::string>::size(&vstack) == 2 )
          {
            v35 = std::vector<std::string>::operator[](&vstack, 1u);
            v36 = (const char *)std::string::c_str(v35);
            v37 = atoi(v36);
            v38 = std::vector<std::string>::operator[](&vstack, 0);
            v39 = (const char *)std::string::c_str(v38);
            v40 = atoi(v39);
            Position::Position(&v138, v40, v37);
            std::list<Position>::push_back(&stacks, &v138);
          }
          std::vector<std::string>::~vector(&vstack);
        }
        Map::AddStack(this, &stacks);
        std::vector<std::string>::~vector(&strstacks);
        std::list<Position>::~list(&stacks);
        goto LABEL_121;
      case 7:
        std::list<Position>::list(&stacks_0);
        std::allocator<char>::allocator(&v140);
        std::string::string(&v139, 9181714, &v140);
        Answer::StringUtility::split(&strstacks_0, &mapEvent->effect, &v139, 0);
        std::string::~string(&v139);
        std::allocator<char>::~allocator(&v140);
        for ( it_4._M_current = std::vector<std::string>::begin(&strstacks_0)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_4) )
        {
          v141._M_current = std::vector<std::string>::end(&strstacks_0)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_4, &v141) )
            break;
          std::allocator<char>::allocator(&v143);
          std::string::string(&v142, L":|", &v143);
          v41 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_4);
          Answer::StringUtility::split(&vstack_0, v41, &v142, 0);
          std::string::~string(&v142);
          std::allocator<char>::~allocator(&v143);
          if ( std::vector<std::string>::size(&vstack_0) == 2 )
          {
            v42 = std::vector<std::string>::operator[](&vstack_0, 1u);
            v43 = (const char *)std::string::c_str(v42);
            v44 = atoi(v43);
            v45 = std::vector<std::string>::operator[](&vstack_0, 0);
            v46 = (const char *)std::string::c_str(v45);
            v47 = atoi(v46);
            Position::Position(&v144, v47, v44);
            std::list<Position>::push_back(&stacks_0, &v144);
          }
          std::vector<std::string>::~vector(&vstack_0);
        }
        Map::RemoveStack(this, &stacks_0);
        std::vector<std::string>::~vector(&strstacks_0);
        std::list<Position>::~list(&stacks_0);
        goto LABEL_121;
      case 8:
        if ( pUnit )
          v48 = (Monster *)__dynamic_cast(
                             pUnit,
                             (const struct __class_type_info *)&`typeinfo for'Unit,
                             (const struct __class_type_info *)&`typeinfo for'Monster,
                             0);
        else
          v48 = 0;
        pMonster_0 = v48;
        if ( v48 )
        {
          v49 = (const char *)std::string::c_str(&mapEvent->effect);
          bcid = atoi(v49);
          v50 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v50, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( packet )
          {
            Answer::NetPacket::writeInt32(packet, bcid);
            pKiller = Monster::getKiller(pMonster_0);
            if ( pKiller )
            {
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet, &val);
              std::string::~string(&val);
              Cid = Player::getCid(pKiller);
              Answer::NetPacket::writeInt64(packet, Cid);
            }
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v53 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v53, 0, packet);
          }
        }
        goto LABEL_121;
      case 9:
        std::allocator<char>::allocator(&v147);
        std::string::string(&v146, L":|", &v147);
        Answer::StringUtility::split(&strIds_3, &mapEvent->effect, &v146, 0);
        std::string::~string(&v146);
        std::allocator<char>::~allocator(&v147);
        if ( std::vector<std::string>::size(&strIds_3) == 7 )
        {
          v54 = Answer::Singleton<CfgData>::instance();
          KiaFuDay = CfgData::getServerDiffDay(v54, SERVER_TYPE::SVT_NORMAL);
          if ( (unsigned int)KiaFuDay <= 6 )
          {
            memset(&stu.broad, 0, 36);
            v55 = std::vector<std::string>::operator[](&strIds_3, KiaFuDay);
            v56 = (const char *)std::string::c_str(v55);
            stu.id = atoi(v56);
            std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
          }
        }
        std::vector<std::string>::~vector(&strIds_3);
        goto LABEL_121;
      case 0xA:
        v57 = (const char *)std::string::c_str(&mapEvent->effect);
        GongGaoId = atoi(v57);
        v58 = Answer::Singleton<GameService>::instance();
        packet_0 = GameService::popNetpacket(v58, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet_0 )
          return;
        Answer::NetPacket::writeInt32(packet_0, GongGaoId);
        v59 = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, v59);
        v60 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v60, packet_0);
        goto LABEL_121;
      case 0xB:
        std::map<int,int>::map(&BattleMonster);
        std::allocator<char>::allocator(&v149);
        std::string::string(&v148, 9181714, &v149);
        Answer::StringUtility::split(&strIds_4, &mapEvent->effect, &v148, 0);
        std::string::~string(&v148);
        std::allocator<char>::~allocator(&v149);
        for ( strit._M_current = std::vector<std::string>::begin(&strIds_4)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&strit, 0) )
        {
          v150._M_current = std::vector<std::string>::end(&strIds_4)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&strit, &v150) )
            break;
          std::allocator<char>::allocator(&v152);
          std::string::string(&v151, L":|", &v152);
          v61 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&strit);
          Answer::StringUtility::split(&BattleVt, v61, &v151, 0);
          std::string::~string(&v151);
          std::allocator<char>::~allocator(&v152);
          if ( std::vector<std::string>::size(&BattleVt) == 2 )
          {
            v62 = std::vector<std::string>::operator[](&BattleVt, 0);
            v63 = (const char *)std::string::c_str(v62);
            BossId = atoi(v63);
            v64 = std::vector<std::string>::operator[](&BattleVt, 1u);
            v65 = (const char *)std::string::c_str(v64);
            Battle = atoi(v65);
            v66 = std::map<int,int>::operator[](&BattleMonster, &Battle);
            *v66 = BossId;
          }
          std::vector<std::string>::~vector(&BattleVt);
        }
        AvgBattle = CActivityMap::GetTop10Battle(this);
        it_5._M_node = std::map<int,int>::begin(&BattleMonster)._M_node;
        while ( 2 )
        {
          v153._M_node = std::map<int,int>::end(&BattleMonster)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it_5, &v153) )
          {
            v67 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_5);
            if ( v67->first < AvgBattle )
            {
              std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it_5, 0);
              continue;
            }
            memset(&stu, 0, sizeof(stu));
            stu.id = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_5)->second;
            std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
          }
          break;
        }
        std::vector<std::string>::~vector(&strIds_4);
        std::map<int,int>::~map(&BattleMonster);
        goto LABEL_121;
      case 0xC:
        std::map<int,int>::map(&BattleMonster);
        std::allocator<char>::allocator(&v155);
        std::string::string(&v154, 9181714, &v155);
        Answer::StringUtility::split(&strIds_5, &mapEvent->effect, &v154, 0);
        std::string::~string(&v154);
        std::allocator<char>::~allocator(&v155);
        for ( strit_0._M_current = std::vector<std::string>::begin(&strIds_5)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&strit_0, 0) )
        {
          v156._M_current = std::vector<std::string>::end(&strIds_5)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&strit_0, &v156) )
            break;
          std::allocator<char>::allocator(&v158);
          std::string::string(&v157, L":|", &v158);
          v68 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&strit_0);
          Answer::StringUtility::split(&BattleVt_0, v68, &v157, 0);
          std::string::~string(&v157);
          std::allocator<char>::~allocator(&v158);
          if ( std::vector<std::string>::size(&BattleVt_0) == 2 )
          {
            v69 = std::vector<std::string>::operator[](&BattleVt_0, 0);
            v70 = (const char *)std::string::c_str(v69);
            BossId_0 = atoi(v70);
            v71 = std::vector<std::string>::operator[](&BattleVt_0, 1u);
            v72 = (const char *)std::string::c_str(v71);
            Battle_0 = atoi(v72);
            v73 = std::map<int,int>::operator[](&BattleMonster, &Battle_0);
            *v73 = BossId_0;
          }
          std::vector<std::string>::~vector(&BattleVt_0);
        }
        v74 = Answer::Singleton<GameService>::instance();
        AvgBattle_0 = GameService::GetBattle(v74);
        it_6._M_node = std::map<int,int>::begin(&BattleMonster)._M_node;
        while ( 2 )
        {
          v159._M_node = std::map<int,int>::end(&BattleMonster)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it_6, &v159) )
          {
            v75 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_6);
            if ( v75->first < AvgBattle_0 )
            {
              std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it_6, 0);
              continue;
            }
            memset(&stu, 0, sizeof(stu));
            stu.id = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_6)->second;
            std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
          }
          break;
        }
        std::vector<std::string>::~vector(&strIds_5);
        std::map<int,int>::~map(&BattleMonster);
        goto LABEL_121;
      default:
        goto LABEL_121;
    }
  }
}


#####################################
void __cdecl CActivityMap::generateMonster(CActivityMap *const this, const std::string *const str)
{
  std::string *v2; // rax
  const char *v3; // rax
  MonsterWait stu; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-60h] BYREF
  StringVector strIds; // [rsp+50h] [rbp-50h] BYREF
  std::string delims; // [rsp+70h] [rbp-30h] BYREF
  char v8; // [rsp+7Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-20h] BYREF

  std::allocator<char>::allocator(&v8);
  std::string::string(&delims, L":|", &v8);
  Answer::StringUtility::split(&strIds, str, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v8);
  for ( it._M_current = std::vector<std::string>::begin(&strIds)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<std::string>::end(&strIds)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
      break;
    memset(&stu, 0, sizeof(stu));
    v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
    v3 = (const char *)std::string::c_str(v2);
    stu.id = atoi(v3);
    std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
  }
  std::vector<std::string>::~vector(&strIds);
}


#####################################
void __cdecl CActivityMap::checkAddMonster(CActivityMap *const this, int64_t curTick)
{
  MonsterWait *v2; // rcx
  std::_List_iterator<MonsterWait> v3; // rax
  std::_List_iterator<MonsterWait> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<MonsterWait> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<MonsterWait>::begin(&this->m_waitMonster)._M_node;
  eiter._M_node = std::list<MonsterWait>::end(&this->m_waitMonster)._M_node;
  while ( std::_List_iterator<MonsterWait>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<MonsterWait>::operator*(&iter);
    if ( CActivityMap::flashMonster(this, v2, curTick) )
    {
      std::_List_iterator<MonsterWait>::operator++(&iter);
    }
    else
    {
      v3._M_node = std::_List_iterator<MonsterWait>::operator++(&iter, 0)._M_node;
      std::list<MonsterWait>::erase(&this->m_waitMonster, v3);
    }
  }
}


#####################################
bool __cdecl CActivityMap::flashMonster(CActivityMap *const this, MonsterWait *const waitAddMonster, int64_t curTick)
{
  int32_t id; // ebx
  CfgData *v4; // rax
  int32_t mid; // ebx
  CfgData *v7; // rax
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v9; // rax
  int32_t v10; // r12d
  int32_t v11; // ecx
  int32_t v12; // eax
  Position pos; // [rsp+20h] [rbp-60h] BYREF
  std::vector<Position> positions; // [rsp+30h] [rbp-50h] BYREF
  CfgActivityMonster *pCfgActivityMonster; // [rsp+50h] [rbp-30h]
  CfgMonster *pCfgMonster; // [rsp+58h] [rbp-28h]
  int32_t x; // [rsp+64h] [rbp-1Ch]
  int32_t y; // [rsp+68h] [rbp-18h]
  int32_t i; // [rsp+6Ch] [rbp-14h]

  id = waitAddMonster->id;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgActivityMonster = CfgData::getActivityMonster(v4, id);
  if ( !pCfgActivityMonster )
    return 0;
  if ( pCfgActivityMonster->count < 0 )
    return 0;
  mid = pCfgActivityMonster->mid;
  v7 = Answer::Singleton<CfgData>::instance();
  pCfgMonster = CfgData::getMonster(v7, mid);
  if ( !pCfgMonster )
    return 0;
  if ( curTick - waitAddMonster->lastTick < pCfgActivityMonster->delay )
    return 1;
  ++waitAddMonster->times;
  waitAddMonster->lastTick = curTick;
  if ( pCfgActivityMonster->count == 1 )
  {
    CActivityMap::flashMonster(this, pCfgActivityMonster, pCfgMonster, pCfgActivityMonster->x, pCfgActivityMonster->y);
  }
  else
  {
    std::vector<Position>::vector(&positions);
    for ( x = -2; x <= 1; ++x )
    {
      for ( y = -2; y <= 1; ++y )
      {
        Position::Position(&pos, x + pCfgActivityMonster->x, y + pCfgActivityMonster->y);
        if ( Map::isWalkablePosition(this, pos.x, pos.y) )
          std::vector<Position>::push_back(&positions, &pos);
      }
    }
    M_current = std::vector<Position>::end(&positions)._M_current;
    v9._M_current = std::vector<Position>::begin(&positions)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
      v9,
      (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
    for ( i = 0; pCfgActivityMonster->count > i; ++i )
    {
      v12 = std::vector<Position>::size(&positions);
      if ( v12 <= i )
        break;
      v10 = std::vector<Position>::operator[](&positions, i)->y;
      v11 = std::vector<Position>::operator[](&positions, i)->x;
      CActivityMap::flashMonster(this, pCfgActivityMonster, pCfgMonster, v11, v10);
    }
    std::vector<Position>::~vector(&positions);
  }
  return waitAddMonster->times < pCfgActivityMonster->times;
}


#####################################
void __cdecl CActivityMap::AddActivityNpc(CActivityMap *const this, std::string *const Effect)
{
  std::string *v2; // rax
  const char *v3; // rax
  int32_t v4; // ebx
  CfgData *v5; // rax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v7; // rax
  CfgData *v8; // rax
  int32_t mapid; // ebx
  int32_t npc_id; // ebx
  CfgData *v12; // rax
  NpcActivity *v13; // rbx
  int32_t Id; // eax
  Position pos; // [rsp+10h] [rbp-D0h]
  Int32Vector regionIds; // [rsp+20h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-A0h] BYREF
  StringVector strIds; // [rsp+50h] [rbp-90h] BYREF
  std::string delims; // [rsp+70h] [rbp-70h] BYREF
  char v20; // [rsp+7Fh] [rbp-61h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-60h] BYREF
  int32_t EndTime; // [rsp+94h] [rbp-4Ch]
  CfgActivityNpc *pNpcAct; // [rsp+98h] [rbp-48h]
  CfgMapRegion *pCfgRegion; // [rsp+A0h] [rbp-40h]
  int32_t i; // [rsp+ACh] [rbp-34h]
  const CfgNpc *pNpc; // [rsp+B0h] [rbp-30h]
  NpcActivity *npc; // [rsp+B8h] [rbp-28h]

  if ( this->m_pActivity )
  {
    std::allocator<char>::allocator(&v20);
    std::string::string(&delims, L":|", &v20);
    Answer::StringUtility::split(&strIds, Effect, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v20);
    EndTime = CActivity::getLeftTime(this->m_pActivity);
    for ( it._M_current = std::vector<std::string>::begin(&strIds)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strIds)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      v3 = (const char *)std::string::c_str(v2);
      v4 = atoi(v3);
      v5 = Answer::Singleton<CfgData>::instance();
      pNpcAct = CfgData::getActivityNpc(v5, v4);
      if ( pNpcAct )
      {
        std::vector<int>::vector(&regionIds, &pNpcAct->region_id);
        if ( std::vector<int>::size(&regionIds) )
        {
          M_current = std::vector<int>::end(&regionIds)._M_current;
          v7._M_current = std::vector<int>::begin(&regionIds)._M_current;
          std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
            v7,
            (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
          LODWORD(M_current) = *std::vector<int>::operator[](&regionIds, 0);
          v8 = Answer::Singleton<CfgData>::instance();
          pCfgRegion = CfgData::getMapRegion(v8, (int32_t)M_current);
          if ( pCfgRegion )
          {
            mapid = pCfgRegion->mapid;
            if ( mapid == Map::GetMapId(this) )
            {
              for ( i = 0; pNpcAct->count > i; ++i )
              {
                pos = Map::getRandomWalkablePositionInRegion(this, pCfgRegion);
                if ( pos.x > 0 && pos.y > 0 )
                {
                  npc_id = pNpcAct->npc_id;
                  v12 = Answer::Singleton<CfgData>::instance();
                  pNpc = CfgData::getNpc(v12, npc_id);
                  if ( !pNpc )
                    break;
                  v13 = (NpcActivity *)operator new(0x4E8u);
                  NpcActivity::NpcActivity(v13);
                  npc = v13;
                  if ( v13 )
                  {
                    Id = CActivity::GetId(this->m_pActivity);
                    NpcActivity::init(npc, pNpc, Id, EndTime);
                    Map::addNpc(this, npc, pos.x, pos.y);
                  }
                }
              }
            }
          }
        }
        std::vector<int>::~vector(&regionIds);
      }
    }
    std::vector<std::string>::~vector(&strIds);
  }
}


#####################################
void __cdecl CActivityMap::flashMonster(
        CActivityMap *const this,
        CfgActivityMonster *pCfgActivityMonster,
        CfgMonster *pCfgMonster,
        int32_t x,
        int32_t y)
{
  CPoolManager *v5; // rax
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v7; // rax
  std::pair<const int,MonsterWave> *v8; // rax
  CfgMonster cfgMonster; // [rsp+30h] [rbp-380h] BYREF
  MonsterWave monsterWave; // [rsp+2D0h] [rbp-E0h] BYREF
  PosVt vPos; // [rsp+2F0h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > itMonsterWave; // [rsp+310h] [rbp-A0h] BYREF
  CfgMapMonster cfgmapmonster; // [rsp+320h] [rbp-90h] BYREF
  MonsterActivity *pMonster; // [rsp+348h] [rbp-68h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > __x; // [rsp+350h] [rbp-60h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,MonsterWave> >,bool> v19; // [rsp+360h] [rbp-50h]
  std::pair<const int,MonsterWave> v20; // [rsp+370h] [rbp-40h] BYREF

  if ( this->m_pActivity )
  {
    v5 = Answer::Singleton<CPoolManager>::instance();
    pMonster = CPoolManager::pop<MonsterActivity>(v5);
    if ( pMonster )
    {
      memset(&cfgmapmonster, 0, sizeof(cfgmapmonster));
      cfgmapmonster.id = pCfgActivityMonster->id;
      cfgmapmonster.mapid = Map::GetMapId(this);
      cfgmapmonster.monsterid = pCfgActivityMonster->mid;
      cfgmapmonster.x = x;
      cfgmapmonster.y = y;
      cfgmapmonster.side = pCfgActivityMonster->side;
      if ( std::vector<Position>::size(&pCfgActivityMonster->randpos) )
      {
        std::vector<Position>::vector(&vPos, &pCfgActivityMonster->randpos);
        M_current = std::vector<Position>::end(&vPos)._M_current;
        v7._M_current = std::vector<Position>::begin(&vPos)._M_current;
        std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
          v7,
          (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
        cfgmapmonster.x = std::vector<Position>::operator[](&vPos, 0)->x;
        cfgmapmonster.y = std::vector<Position>::operator[](&vPos, 0)->y;
        std::vector<Position>::~vector(&vPos);
      }
      CfgMonster::CfgMonster(&cfgMonster, pCfgMonster);
      (*((void (__fastcall **)(CActivity *, CfgMonster *))this->m_pActivity->_vptr_CActivity + 23))(
        this->m_pActivity,
        &cfgMonster);
      MonsterActivity::init(pMonster, this, pCfgActivityMonster, &cfgMonster, &cfgmapmonster);
      (*((void (__fastcall **)(CActivity *, MonsterActivity *))this->m_pActivity->_vptr_CActivity + 36))(
        this->m_pActivity,
        pMonster);
      (*((void (__fastcall **)(CActivityMap *const, MonsterActivity *, _QWORD, _QWORD))this->_vptr_Map + 28))(
        this,
        pMonster,
        (unsigned int)cfgmapmonster.x,
        (unsigned int)cfgmapmonster.y);
      CActivityMap::addMonsterHPEventInfo(this, pMonster);
      MonsterActivity::runOnRoad(pMonster);
      itMonsterWave._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &pCfgActivityMonster->wave)._M_node;
      __x._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&itMonsterWave, &__x) )
      {
        v8 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&itMonsterWave);
        ++v8->second.count;
      }
      else
      {
        *(_QWORD *)&monsterWave.count = 1;
        memset(&monsterWave.escaped, 0, 24);
        monsterWave.startTime = Map::getTick(this);
        std::pair<int const,MonsterWave>::pair(&v20, &pCfgActivityMonster->wave, &monsterWave);
        v19 = std::map<int,MonsterWave>::insert(&this->m_monsterWave, &v20);
      }
      std::list<MonsterActivity *>::push_back(&this->m_actMonsters, &pMonster);
      CfgMonster::~CfgMonster(&cfgMonster);
    }
  }
}


#####################################
void __cdecl CActivityMap::addMonsterHPEventInfo(CActivityMap *const this, MonsterActivity *pMonster)
{
  CfgMapEvent *v2; // rax
  CfgMapEvent *v3; // rax
  CfgMapEvent *v5; // rax
  int v6; // ebx
  CfgMapEvent *v7; // rax
  CfgMapEvent *v8; // rax
  CfgMapEvent *v10; // rax
  CfgMapEvent *v11; // rax
  HPEvent hpEvent; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( pMonster )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 8 )
      {
        v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( *std::vector<int>::operator[](&v2->trigger_param, 0) == 2 )
        {
          v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( std::vector<int>::size(&v3->trigger_param) == 4 )
          {
            v5 = std::_List_iterator<CfgMapEvent>::operator->(&it);
            v6 = *std::vector<int>::operator[](&v5->trigger_param, 1u);
            if ( v6 == MonsterActivity::getActivityMonsterId(pMonster) )
            {
              v7 = std::_List_iterator<CfgMapEvent>::operator->(&it);
              if ( *std::vector<int>::operator[](&v7->trigger_param, 2u) >= 0 )
              {
                v8 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                if ( *std::vector<int>::operator[](&v8->trigger_param, 3u) > 0 )
                {
                  *(_QWORD *)&hpEvent.id = 0;
                  hpEvent.maxhp = 0;
                  hpEvent.id = std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_id;
                  v10 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                  hpEvent.minhp = *std::vector<int>::operator[](&v10->trigger_param, 2u);
                  v11 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                  hpEvent.maxhp = *std::vector<int>::operator[](&v11->trigger_param, 3u);
                  MonsterActivity::addEventHp(pMonster, &hpEvent);
                }
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CActivityMap::SendUltimateChallengeInfo(CActivityMap *const this, Player *pPlayer)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t Id; // edx
  int32_t HaveAliveMonster; // edx
  int32_t HaveAlivePet; // edx
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  GameService *v12; // rax
  int32_t v13; // edx
  int32_t v14; // edx
  int32_t v15; // edx
  int32_t v16; // edx
  uint32_t v17; // edx
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+18h] [rbp-18h]

  if ( this->m_pActivity )
  {
    if ( pPlayer )
    {
      ConnId = Player::getConnId(pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E26u);
      if ( packet )
      {
        Id = CActivity::GetId(this->m_pActivity);
        Answer::NetPacket::writeInt32(packet, Id);
        HaveAliveMonster = CActivityMap::HaveAliveMonster(this);
        Answer::NetPacket::writeInt32(packet, HaveAliveMonster);
        HaveAlivePet = CActivityMap::HaveAlivePet(this);
        Answer::NetPacket::writeInt32(packet, HaveAlivePet);
        LeftTime = CActivity::getLeftTime(this->m_pActivity);
        Answer::NetPacket::writeInt32(packet, LeftTime);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pPlayer);
        v10 = Player::getConnId(pPlayer);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v11, v10, GateIndex, packet);
      }
    }
    else
    {
      v12 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v12, 0, Answer::PackType::PACK_DISPATCH, 0x2E26u);
      if ( packet_0 )
      {
        v13 = CActivity::GetId(this->m_pActivity);
        Answer::NetPacket::writeInt32(packet_0, v13);
        v14 = CActivityMap::HaveAliveMonster(this);
        Answer::NetPacket::writeInt32(packet_0, v14);
        v15 = CActivityMap::HaveAlivePet(this);
        Answer::NetPacket::writeInt32(packet_0, v15);
        v16 = CActivity::getLeftTime(this->m_pActivity);
        Answer::NetPacket::writeInt32(packet_0, v16);
        v17 = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, v17);
        Map::broadcast(this, packet_0);
      }
    }
  }
}


