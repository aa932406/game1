// Decompiled methods for class: Map
// Source: gameserver.cc
// Total methods: 97

#####################################
void __cdecl Map::~Map(Map *const this)
{
  Map::~Map(this);
  operator delete(this);
}


#####################################
void __cdecl Map::init(Map *const this, CMapRunner *pRunner, const CfgMap *const cfgmap)
{
  int32_t MapId; // ebx
  CfgData *v4; // rax
  int32_t Day; // ebx
  CfgData *v6; // rax
  int32_t v7; // ebx
  CfgData *v8; // rax
  CfgMapMonster *v9; // r12
  CWorldBoss *v10; // rax
  CPoolManager *v11; // rax
  CfgMapMonster *v12; // rax
  void (__fastcall *v13)(Map *const, Monster *, __int64, _QWORD); // r13
  unsigned int y; // r12d
  __int64 x; // rdx
  int32_t v16; // ebx
  CfgData *v17; // rax
  GroupMonster *v18; // rax
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v20; // rax
  GroupMonster *v21; // rax
  int32_t v22; // eax
  CfgData *v23; // rax
  int32_t v24; // ebx
  CfgData *v25; // rax
  CPoolManager *v26; // rax
  GroupMonster *v27; // rax
  GroupMonster *v28; // rax
  int32_t MonsterCount; // ebx
  GroupMonster *v30; // rax
  CfgData *v32; // rax
  int32_t v33; // r13d
  int32_t RegionCount; // r12d
  int32_t id; // ebx
  TileManager *v36; // rax
  int32_t Mid; // ebx
  CfgData *v38; // rax
  CPoolManager *v39; // rax
  int32_t v40; // ebx
  GroupMonster *v41; // rax
  GroupMonster *v42; // rax
  GroupMonster *v43; // rax
  GroupMonster *v44; // rax
  CfgData *v45; // rax
  int32_t v46; // ebx
  const std::pair<const int,CfgNpc> *v47; // rax
  CfgData *v49; // rax
  Npc *v51; // rbx
  const std::pair<const int,CfgNpc> *v52; // rax
  int32_t v53; // r12d
  int32_t v54; // edx
  int32_t v55; // ebx
  CfgData *v56; // rax
  int32_t plantid; // ebx
  CfgData *v58; // rax
  Plant *v59; // rbx
  CfgMapPlant *v60; // rax
  __gnu_cxx::__normal_iterator<CfgMapPlant*,std::vector<CfgMapPlant> > it_1; // [rsp+30h] [rbp-220h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgNpc> > it_0; // [rsp+40h] [rbp-210h] BYREF
  Position Pos; // [rsp+50h] [rbp-200h]
  CfgMapMonster MapMonster_0; // [rsp+60h] [rbp-1F0h] BYREF
  CfgMapMonster MapMonster; // [rsp+80h] [rbp-1D0h] BYREF
  std::vector<Position> RevivePos; // [rsp+A0h] [rbp-1B0h] BYREF
  __gnu_cxx::__normal_iterator<CfgMapMonster*,std::vector<CfgMapMonster> > it; // [rsp+C0h] [rbp-190h] BYREF
  __gnu_cxx::__normal_iterator<GroupMonster*,std::vector<GroupMonster> > Git; // [rsp+D0h] [rbp-180h] BYREF
  GroupMonsterVector GMonster; // [rsp+E0h] [rbp-170h] BYREF
  __gnu_cxx::__normal_iterator<CfgMapMonster*,std::vector<CfgMapMonster> > __rhs; // [rsp+100h] [rbp-150h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+110h] [rbp-140h] BYREF
  __gnu_cxx::__normal_iterator<GroupMonster*,std::vector<GroupMonster> > v73; // [rsp+130h] [rbp-120h] BYREF
  std::vector<AttrAddon> v74; // [rsp+140h] [rbp-110h] BYREF
  std::vector<Position> p_PosVector; // [rsp+160h] [rbp-F0h] BYREF
  std::vector<AttrAddon> v76; // [rsp+180h] [rbp-D0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgNpc> > __x; // [rsp+1A0h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<CfgMapPlant*,std::vector<CfgMapPlant> > v78; // [rsp+1B0h] [rbp-A0h] BYREF
  CfgMapMonsterVector *pMonsters; // [rsp+1B8h] [rbp-98h]
  const CfgNpcTable *allNpc; // [rsp+1C0h] [rbp-90h]
  CfgMapPlantVector *pPlants; // [rsp+1C8h] [rbp-88h]
  CfgMonster *pCfgMonster; // [rsp+1D0h] [rbp-80h]
  Monster *monster; // [rsp+1D8h] [rbp-78h]
  int32_t i; // [rsp+1E0h] [rbp-70h]
  int32_t MonsterId; // [rsp+1E4h] [rbp-6Ch]
  CfgMonster *pMonster; // [rsp+1E8h] [rbp-68h]
  Monster *monster_0; // [rsp+1F0h] [rbp-60h]
  int32_t AgvCount; // [rsp+1F8h] [rbp-58h]
  int32_t CurCount; // [rsp+1FCh] [rbp-54h]
  int32_t i_0; // [rsp+200h] [rbp-50h]
  int32_t MonsterId_0; // [rsp+204h] [rbp-4Ch]
  CfgMonster *pMonster_0; // [rsp+208h] [rbp-48h]
  Monster *monster_1; // [rsp+210h] [rbp-40h]
  Npc *npc; // [rsp+218h] [rbp-38h]
  CfgPlant *pCfgPlant; // [rsp+220h] [rbp-30h]
  Plant *plant; // [rsp+228h] [rbp-28h]

  CfgMap::operator=(&this->m_cfgmap, cfgmap);
  this->m_pMapRunner = pRunner;
  this->m_widthTileCount = this->m_cfgmap.width / 48;
  this->m_heightTileCount = roundInt((double)this->m_cfgmap.height / 17.0);
  this->m_widthAreaCount = this->m_cfgmap.width / 232 + 1;
  this->m_heightAreaCount = this->m_cfgmap.height / 162 + 1;
  this->m_lastUpdateTime = 0;
  this->m_StartandEndTime = 0;
  this->m_IsStart = 0;
  MapId = Map::GetMapId(this);
  v4 = Answer::Singleton<CfgData>::instance();
  pMonsters = CfgData::getMonstersOnMap(v4, MapId);
  if ( pMonsters )
  {
    for ( it._M_current = std::vector<CfgMapMonster>::begin(pMonsters)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgMapMonster>::end(pMonsters)._M_current;
      if ( !__gnu_cxx::operator!=<CfgMapMonster *,std::vector<CfgMapMonster>>(&it, &__rhs) )
        break;
      if ( !__gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator->(&it)->hide )
      {
        if ( __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator->(&it)->Day <= 0
          || (Day = __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator->(&it)->Day,
              v6 = Answer::Singleton<CfgData>::instance(),
              Day <= CfgData::getServerDiffDay(v6, SERVER_TYPE::SVT_NORMAL) + 1) )
        {
          v7 = __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator->(&it)->monsterid;
          v8 = Answer::Singleton<CfgData>::instance();
          pCfgMonster = CfgData::getMonster(v8, v7);
          if ( pCfgMonster )
          {
            if ( pCfgMonster->boss_sign <= 0 )
            {
              v11 = Answer::Singleton<CPoolManager>::instance();
              monster = CPoolManager::pop<Monster>(v11);
              if ( monster )
              {
                std::vector<AttrAddon>::vector(&vAttrAddon);
                v12 = __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator*(&it);
                Monster::init(monster, pCfgMonster, v12, MonsterState::MS_STAND, &vAttrAddon);
                std::vector<AttrAddon>::~vector(&vAttrAddon);
                v13 = (void (__fastcall *)(Map *const, Monster *, __int64, _QWORD))*((_QWORD *)this->_vptr_Map + 28);
                y = __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator->(&it)->y;
                x = (unsigned int)__gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator->(&it)->x;
                v13(this, monster, x, y);
              }
            }
            else
            {
              v9 = __gnu_cxx::__normal_iterator<CfgMapMonster *,std::vector<CfgMapMonster>>::operator*(&it);
              v10 = Answer::Singleton<CWorldBoss>::instance();
              CWorldBoss::OnAddBoss(v10, this, pCfgMonster, v9);
            }
          }
        }
      }
    }
  }
  v16 = Map::GetMapId(this);
  v17 = Answer::Singleton<CfgData>::instance();
  CfgData::GetGroupMonsterVector(&GMonster, v17, v16);
  for ( Git._M_current = std::vector<GroupMonster>::begin(&GMonster)._M_current;
        ;
        __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator++(&Git) )
  {
    v73._M_current = std::vector<GroupMonster>::end(&GMonster)._M_current;
    if ( !__gnu_cxx::operator!=<GroupMonster *,std::vector<GroupMonster>>(&Git, &v73) )
      break;
    if ( __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->IsSpecial <= 0 )
    {
      MonsterCount = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->MonsterCount;
      AgvCount = MonsterCount
               / __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->RegionCount;
      CurCount = 0;
      if ( AgvCount <= 0 )
      {
        v44 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "GroupMonster error mapid=%d,mid=%d\n",
          cfgmap->id,
          v44->Mid);
      }
      else
      {
        for ( i_0 = 0; ; ++i_0 )
        {
          v42 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
          if ( v42->MonsterCount <= i_0 )
            break;
          v30 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
          if ( v30->RegionCount - 1 != CurCount && i_0 && !(i_0 % AgvCount) )
            ++CurCount;
          v32 = Answer::Singleton<CfgData>::instance();
          MonsterId_0 = CfgData::GetMapMonsterId(v32);
          memset(&MapMonster_0.mapid, 0, 24);
          MapMonster_0.id = MonsterId_0;
          MapMonster_0.mapid = cfgmap->id;
          v33 = CurCount + 1;
          RegionCount = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->RegionCount;
          id = cfgmap->id;
          v36 = Answer::Singleton<TileManager>::instance();
          Pos = TileManager::getRandomWalkablePosition(v36, id, RegionCount, v33);
          if ( Pos.x != -1 && Pos.y != -1 )
          {
            *(Position *)&MapMonster_0.x = Pos;
            Mid = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->Mid;
            v38 = Answer::Singleton<CfgData>::instance();
            pMonster_0 = CfgData::getMonster(v38, Mid);
            v39 = Answer::Singleton<CPoolManager>::instance();
            monster_1 = CPoolManager::pop<Monster>(v39);
            if ( monster_1 )
            {
              if ( pMonster_0 )
              {
                std::vector<AttrAddon>::vector(&v76);
                Monster::init(monster_1, pMonster_0, &MapMonster_0, MonsterState::MS_STAND, &v76);
                std::vector<AttrAddon>::~vector(&v76);
                v40 = CurCount + 1;
                v41 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
                Monster::SetGroupMonster(monster_1, v41->RegionCount, v40);
                (*((void (__fastcall **)(Map *const, Monster *, _QWORD, _QWORD))this->_vptr_Map + 28))(
                  this,
                  monster_1,
                  (unsigned int)MapMonster_0.x,
                  (unsigned int)MapMonster_0.y);
              }
            }
          }
        }
        v43 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
        *std::map<int,int>::operator[](&this->m_MonsterReviveMap, &v43->Mid) = 0;
      }
    }
    else
    {
      v18 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
      std::vector<Position>::vector(&RevivePos, &v18->RevivePos);
      M_current = std::vector<Position>::end(&RevivePos)._M_current;
      v20._M_current = std::vector<Position>::begin(&RevivePos)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
        v20,
        (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
      for ( i = 0; ; ++i )
      {
        v27 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
        if ( v27->MonsterCount <= i )
          break;
        v21 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
        v22 = std::vector<Position>::size(&v21->RevivePos);
        if ( v22 <= i )
          break;
        v23 = Answer::Singleton<CfgData>::instance();
        MonsterId = CfgData::GetMapMonsterId(v23);
        memset(&MapMonster.mapid, 0, 24);
        MapMonster.id = MonsterId;
        MapMonster.mapid = cfgmap->id;
        MapMonster.x = std::vector<Position>::operator[](&RevivePos, i)->x;
        MapMonster.y = std::vector<Position>::operator[](&RevivePos, i)->y;
        v24 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->Mid;
        v25 = Answer::Singleton<CfgData>::instance();
        pMonster = CfgData::getMonster(v25, v24);
        v26 = Answer::Singleton<CPoolManager>::instance();
        monster_0 = CPoolManager::pop<Monster>(v26);
        if ( monster_0 && pMonster )
        {
          std::vector<AttrAddon>::vector(&v74);
          Monster::init(monster_0, pMonster, &MapMonster, MonsterState::MS_STAND, &v74);
          std::vector<AttrAddon>::~vector(&v74);
          Monster::SetGroupMonster(monster_0, 0, 0);
          std::vector<Position>::vector(&p_PosVector, &RevivePos);
          Monster::SetRevivePos(monster_0, &p_PosVector);
          std::vector<Position>::~vector(&p_PosVector);
          (*((void (__fastcall **)(Map *const, Monster *, _QWORD, _QWORD))this->_vptr_Map + 28))(
            this,
            monster_0,
            (unsigned int)MapMonster.x,
            (unsigned int)MapMonster.y);
        }
      }
      v28 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
      *std::map<int,int>::operator[](&this->m_MonsterReviveMap, &v28->Mid) = 0;
      std::vector<Position>::~vector(&RevivePos);
    }
  }
  v45 = Answer::Singleton<CfgData>::instance();
  allNpc = CfgData::getNpcAll(v45);
  for ( it_0._M_node = std::map<int,CfgNpc>::begin(allNpc)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator++(&it_0) )
  {
    __x._M_node = std::map<int,CfgNpc>::end(allNpc)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator!=(&it_0, &__x) )
      break;
    v46 = Map::GetMapId(this);
    v47 = std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0);
    if ( CfgNpc::findMapId(&v47->second, v46)
      && std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0)->second.x > 0
      && std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0)->second.y > 0 )
    {
      if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0)->second.unite_flag != 1
        || (v49 = Answer::Singleton<CfgData>::instance(), CfgData::isUniteServer(v49)) )
      {
        v51 = (Npc *)operator new(0x4E8u);
        Npc::Npc(v51);
        npc = v51;
        if ( v51 )
        {
          v52 = std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0);
          Npc::init(npc, &v52->second, 0);
          v53 = std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0)->second.y;
          v54 = std::_Rb_tree_const_iterator<std::pair<int const,CfgNpc>>::operator->(&it_0)->second.x;
          Map::addNpc(this, npc, v54, v53);
        }
      }
    }
  }
  v55 = Map::GetMapId(this);
  v56 = Answer::Singleton<CfgData>::instance();
  pPlants = CfgData::getPlantOnMap(v56, v55);
  if ( pPlants )
  {
    for ( it_1._M_current = std::vector<CfgMapPlant>::begin(pPlants)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgMapPlant *,std::vector<CfgMapPlant>>::operator++(&it_1) )
    {
      v78._M_current = std::vector<CfgMapPlant>::end(pPlants)._M_current;
      if ( !__gnu_cxx::operator!=<CfgMapPlant *,std::vector<CfgMapPlant>>(&it_1, &v78) )
        break;
      plantid = __gnu_cxx::__normal_iterator<CfgMapPlant *,std::vector<CfgMapPlant>>::operator->(&it_1)->plantid;
      v58 = Answer::Singleton<CfgData>::instance();
      pCfgPlant = CfgData::getPlant(v58, plantid);
      if ( pCfgPlant
        && (!pCfgPlant->type
         || pCfgPlant->type == 3
         || pCfgPlant->type == 4
         || pCfgPlant->type == 6
         || pCfgPlant->type == 7
         || pCfgPlant->type == 8) )
      {
        v59 = (Plant *)operator new(0xE0u);
        Plant::Plant(v59);
        plant = v59;
        if ( v59 )
        {
          v60 = __gnu_cxx::__normal_iterator<CfgMapPlant *,std::vector<CfgMapPlant>>::operator*(&it_1);
          Plant::init(plant, this, pCfgPlant, v60, 0);
          Map::addPlant(this, plant);
        }
      }
    }
  }
  if ( Map::IsMoLingHuanYu(this) )
  {
    this->m_StartandEndTime = Answer::DayTime::now();
    this->m_IsStart = 1;
  }
  std::vector<GroupMonster>::~vector(&GMonster);
}


#####################################
void __cdecl Map::update(Map *const this)
{
  int32_t MapId; // ebx
  CfgData *v3; // rax
  GameService *v4; // rax
  uint32_t WOffset; // eax
  GameService *v6; // rax
  tm LocalNow; // [rsp+10h] [rbp-60h] BYREF
  SpecialBossMapCfg *pCfg; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  Map::getLocalNow(&LocalNow, this);
  if ( !std::list<Player *>::empty(&this->m_players)
    || !std::list<Trailer *>::empty(&this->m_trailers)
    || LocalNow.tm_min != this->m_lastLocalNow.tm_min
    || this->m_NeedUpdate )
  {
    this->m_NeedUpdate = 0;
    this->m_lastUpdateTime = Map::getNow(this);
    this->m_lastLocalNow = LocalNow;
    Map::updateGroupMonsterRevive(this, this->m_lastUpdateTime);
    Map::updatePlayers(this);
    Map::updateMonsters(this);
    Map::updateNpcs(this);
    Map::updatePlants(this);
    Map::updateDropItems(this);
    Map::updateTraps(this);
    Map::updateTrailers(this);
    if ( Map::IsMoLingHuanYu(this) )
    {
      MapId = Map::GetMapId(this);
      v3 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetSpecialBossMapCfg(v3, MapId);
      if ( pCfg )
      {
        if ( pCfg->StartCD > 0 )
        {
          if ( this->m_IsStart )
          {
            if ( this->m_lastUpdateTime - this->m_StartandEndTime > 60 * pCfg->ContinuedTime )
            {
              this->m_StartandEndTime = this->m_lastUpdateTime;
              this->m_IsStart = 0;
            }
          }
          else if ( this->m_lastUpdateTime - this->m_StartandEndTime > 60 * pCfg->StartCD )
          {
            this->m_StartandEndTime = this->m_lastUpdateTime;
            this->m_IsStart = 1;
            v4 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( packet )
            {
              Answer::NetPacket::writeInt32(packet, 476);
              WOffset = Answer::NetPacket::getWOffset(packet);
              Answer::NetPacket::setSize(packet, WOffset);
              v6 = Answer::Singleton<GameService>::instance();
              GameService::worldBroadcast(v6, 0, packet);
            }
          }
        }
      }
    }
  }
}


#####################################
bool __cdecl Map::IsCrossMap(const Map *const this)
{
  return CfgMap::isCross(&this->m_cfgmap, CROSS_MAP_TYPE::CMT_CROSS);
}


#####################################
void __cdecl Map::ResetRefreshMonster(Map *const this)
{
  std::pair<const int,int> *v1; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nNow; // [rsp+2Ch] [rbp-4h]

  nNow = Map::getNow(this);
  for ( it._M_node = std::map<int,int>::begin(&this->m_MonsterReviveMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end(&this->m_MonsterReviveMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second > 0 )
    {
      v1 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      v1->second = nNow;
    }
  }
  this->m_NeedUpdate = 1;
}


#####################################
void __cdecl Map::updateGroupMonsterRevive(Map *const this, int32_t Now)
{
  int32_t Mid; // ebx
  std::pair<const int,int> *v4; // rax
  int first; // ebx
  CfgData *v6; // rax
  int32_t boss_sign; // r12d
  int32_t revive_time; // ebx
  CfgData *v9; // rax
  std::pair<const int,int> *v10; // rax
  std::_List_iterator<Monster*> itMonst; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v13; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+40h] [rbp-30h] BYREF
  int32_t ReviveTime; // [rsp+4Ch] [rbp-24h]
  Monster *monster; // [rsp+50h] [rbp-20h]
  CfgMonster *pMonster; // [rsp+58h] [rbp-18h]

  for ( it._M_node = std::map<int,int>::begin(&this->m_MonsterReviveMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    v13._M_node = std::map<int,int>::end(&this->m_MonsterReviveMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &v13) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second > 0
      && std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second <= Now )
    {
      ReviveTime = 0;
      for ( itMonst._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
            ;
            std::_List_iterator<Monster *>::operator++(&itMonst, 0) )
      {
        __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
        if ( !std::_List_iterator<Monster *>::operator!=(&itMonst, &__x) )
          break;
        monster = *std::_List_iterator<Monster *>::operator*(&itMonst);
        if ( monster )
        {
          Mid = Monster::getMid(monster);
          if ( Mid == std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first
            && Monster::IsGroupMonster(monster) )
          {
            v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
            Monster::SetReviveTime(monster, v4->second);
            first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
            v6 = Answer::Singleton<CfgData>::instance();
            pMonster = CfgData::getMonster(v6, first);
            if ( pMonster )
            {
              boss_sign = pMonster->boss_sign;
              revive_time = pMonster->revive_time;
              v9 = Answer::Singleton<CfgData>::instance();
              ReviveTime = CfgData::GetMonsterReviveTime(v9, revive_time, boss_sign) / 1000;
            }
          }
        }
      }
      if ( ReviveTime > 0 )
      {
        v10 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        v10->second += ReviveTime;
      }
    }
  }
}


#####################################
int32_t __cdecl Map::canEnter(Map *const this, Player *player)
{
  GameService *v4; // rax
  CfgData *v5; // rax
  int32_t SuitId; // ebx
  CExtEquip *Equip; // rax
  int32_t VipLevel; // ebx
  CVip *PlayerVip; // rax
  int32_t JueWeiLevel; // ebx
  CExtCharJueWei *CharJueWei; // rax
  int8_t ConnId; // bl
  CActivityManager *v13; // rax
  CActivityManager *v14; // rax
  FamilyId_t FamilyId; // rbx
  int8_t v16; // r12
  CActivityManager *v17; // rax
  CActivityManager *v18; // rax
  CXinMo *CXinMo; // rax
  CXinMo *v20; // rax
  tm time; // [rsp+10h] [rbp-50h] BYREF

  if ( !player )
    return 10002;
  if ( (*((int (__fastcall **)(Player *))player->_vptr_Entity + 9))(player) < this->m_cfgmap.player_level
    || (*((int (__fastcall **)(Player *))player->_vptr_Entity + 9))(player) > this->m_cfgmap.player_level_max )
  {
    return 10056;
  }
  if ( this->m_cfgmap.XingMaiLevel > 0 && Player::getRecord(player, 1147) < this->m_cfgmap.XingMaiLevel )
    return 10002;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) != 9 && this->m_cfgmap.LimitDay > 0 )
  {
    v5 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v5, SERVER_TYPE::SVT_NORMAL) + 1 < this->m_cfgmap.LimitDay )
      return 10002;
  }
  if ( this->m_cfgmap.SuitId > 0 )
  {
    SuitId = this->m_cfgmap.SuitId;
    Equip = Player::GetEquip(player);
    if ( SuitId > CExtEquip::GetCount12SuitId(Equip) )
      return 10002;
  }
  if ( this->m_cfgmap.VipLevel > 0 )
  {
    VipLevel = this->m_cfgmap.VipLevel;
    PlayerVip = Player::GetPlayerVip(player);
    if ( VipLevel > CVip::GetVipLevel(PlayerVip) )
      return 10002;
  }
  if ( this->m_cfgmap.JueWeiLevel > 0 )
  {
    JueWeiLevel = this->m_cfgmap.JueWeiLevel;
    CharJueWei = Player::GetCharJueWei(player);
    if ( JueWeiLevel > CExtCharJueWei::GetJueWei(CharJueWei) )
      return 10002;
  }
  if ( Map::GetMapId(this) == 50134 )
  {
    ConnId = Player::getConnId(player);
    v13 = Answer::Singleton<CActivityManager>::instance();
    if ( CActivityManager::GetCityWarWinner(v13, ConnId) <= 0 )
    {
LABEL_27:
      Player::TiShiInfo(player, 21, 0);
      return 10002;
    }
    v14 = Answer::Singleton<CActivityManager>::instance();
    if ( CActivityManager::IsActivityRunning(v14, 7) )
    {
      Player::TiShiInfo(player, 20, 0);
      return 10002;
    }
    FamilyId = Player::getFamilyId(player);
    v16 = Player::getConnId(player);
    v17 = Answer::Singleton<CActivityManager>::instance();
    if ( FamilyId != CActivityManager::GetCityWarWinner(v17, v16) )
      goto LABEL_27;
  }
  if ( Map::GetMapId(this) == 50133 )
  {
    v18 = Answer::Singleton<CActivityManager>::instance();
    if ( CActivityManager::IsActivityRunning(v18, 7) )
      return 10002;
  }
  if ( !Map::IsXinMoMap(this) )
    goto LABEL_46;
  Answer::DayTime::localnow(&time);
  if ( time.tm_hour <= 11 )
    return 10002;
  if ( this->m_cfgmap.XinMoAct >= 0 )
  {
    CXinMo = Player::GetCXinMo(player);
    if ( CXinMo::GetActiveXinMoLevel(CXinMo) < this->m_cfgmap.XinMoAct )
      return 10002;
  }
LABEL_46:
  if ( Map::IsXinMoCun(this) )
  {
    v20 = Player::GetCXinMo(player);
    if ( CXinMo::GetXinMoLevel(v20) <= 0 )
      return 10002;
  }
  return 0;
}


#####################################
bool __cdecl Map::SpecialSitRevive(Map *const this)
{
  return Map::IsXinMoMap(this);
}


#####################################
bool __cdecl Map::CanAutoRevive(Map *const this)
{
  int32_t MapId; // eax

  MapId = Map::GetMapId(this);
  if ( MapId == 50167 )
    return 1;
  if ( MapId > 50167 )
  {
    if ( MapId >= 50169 && (MapId <= 50171 || MapId == 51100) )
      return 1;
  }
  else if ( MapId == 50154 || MapId >= 50154 && (unsigned int)(MapId - 50157) <= 1 )
  {
    return 1;
  }
  return 0;
}


#####################################
void __cdecl Map::onMonsterDie(Map *const this, Monster *monster, Player *player, bool IsGroupMonster)
{
  int32_t MapId; // ebx
  CfgData *v6; // rax
  int32_t Mid; // ebx
  CfgData *v8; // rax
  GroupMonster *v9; // rax
  int *v10; // rbx
  int32_t v11; // r12d
  int32_t boss_sign; // r14d
  int32_t revive_time; // r13d
  CfgData *v14; // rax
  std::_List_iterator<Monster*> it; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<GroupMonster*,std::vector<GroupMonster> > Git; // [rsp+30h] [rbp-80h] BYREF
  GroupMonsterVector GMonster; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+60h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<GroupMonster*,std::vector<GroupMonster> > __rhs; // [rsp+70h] [rbp-40h] BYREF
  int32_t DieCount; // [rsp+7Ch] [rbp-34h]
  Monster *pMonster; // [rsp+80h] [rbp-30h]
  CfgMonster *pMonster_0; // [rsp+88h] [rbp-28h]

  if ( IsGroupMonster && monster )
  {
    if ( this->m_cfgmap.Refresh == 1 )
    {
      DieCount = 0;
      for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
            ;
            std::_List_iterator<Monster *>::operator++(&it) )
      {
        __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
        if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
          break;
        pMonster = *std::_List_iterator<Monster *>::operator*(&it);
        if ( pMonster && Monster::IsGroupMonster(pMonster) )
        {
          if ( DieCount > 1 )
            return;
          if ( !Unit::isAlive(pMonster)
            && (Monster::getState(pMonster) == MonsterState::MS_CORPSE
             || Monster::getState(pMonster) == MonsterState::MS_GHOST) )
          {
            ++DieCount;
          }
        }
      }
    }
    MapId = Map::GetMapId(this);
    v6 = Answer::Singleton<CfgData>::instance();
    CfgData::GetGroupMonsterVector(&GMonster, v6, MapId);
    for ( Git._M_current = std::vector<GroupMonster>::begin(&GMonster)._M_current;
          ;
          __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator++(&Git, 0) )
    {
      __rhs._M_current = std::vector<GroupMonster>::end(&GMonster)._M_current;
      if ( !__gnu_cxx::operator!=<GroupMonster *,std::vector<GroupMonster>>(&Git, &__rhs) )
        break;
      Mid = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git)->Mid;
      v8 = Answer::Singleton<CfgData>::instance();
      pMonster_0 = CfgData::getMonster(v8, Mid);
      if ( pMonster_0 )
      {
        v9 = __gnu_cxx::__normal_iterator<GroupMonster *,std::vector<GroupMonster>>::operator->(&Git);
        v10 = std::map<int,int>::operator[](&this->m_MonsterReviveMap, &v9->Mid);
        v11 = Answer::DayTime::now();
        boss_sign = pMonster_0->boss_sign;
        revive_time = pMonster_0->revive_time;
        v14 = Answer::Singleton<CfgData>::instance();
        *v10 = v11 + CfgData::GetMonsterReviveTime(v14, revive_time, boss_sign) / 1000;
      }
    }
    std::vector<GroupMonster>::~vector(&GMonster);
  }
}


#####################################
bool __cdecl Map::OnSitRevive(Map *const this, Player *player)
{
  if ( !player )
    return 0;
  return Map::IsXinMoMap(this)
      && Player::DecCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD, 500, CURRENCY_CHANGE_REASON::GCT_LI_JI_FU_HUO, 0);
}


#####################################
bool __cdecl Map::CanUsePet(const Map *const this)
{
  return this->m_cfgmap.MapCanUsePet > 0;
}


#####################################
bool __cdecl Map::CanStayInMap(Map *const this)
{
  return this->m_cfgmap.SignOut <= 0;
}


#####################################
int32_t __cdecl Map::GetAvgBattle(Map *const this)
{
  __int64 v1; // rax
  Player **v2; // rax
  int v3; // eax
  std::_List_iterator<Player*> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+30h] [rbp-20h] BYREF
  int64_t Battle; // [rsp+40h] [rbp-10h]
  int32_t nSize; // [rsp+4Ch] [rbp-4h]

  Battle = 0;
  nSize = std::list<Player *>::size(&this->m_players);
  if ( nSize > 0 )
  {
    for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&it, 0) )
    {
      __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
        break;
      v2 = std::_List_iterator<Player *>::operator*(&it);
      v3 = (*((__int64 (__fastcall **)(Player *))(*v2)->_vptr_Entity + 10))(*v2);
      Battle += v3;
    }
    return Battle / nSize;
  }
  else
  {
    LODWORD(v1) = 0;
  }
  return v1;
}


#####################################
int64_t __cdecl Map::getTick(Map *const this)
{
  CTimer *v2; // rax

  if ( this->m_pMapRunner )
    return CMapRunner::getTick(this->m_pMapRunner);
  v2 = Answer::Singleton<CTimer>::instance();
  return CTimer::GetTick(v2);
}


#####################################
int32_t __cdecl Map::getNow(Map *const this)
{
  CTimer *v2; // rax

  if ( this->m_pMapRunner )
    return CMapRunner::getNow(this->m_pMapRunner);
  v2 = Answer::Singleton<CTimer>::instance();
  return CTimer::GetNow(v2);
}


#####################################
bool __cdecl Map::isWalkablePosition(Map *const this, int32_t tx, int32_t ty)
{
  int32_t v4; // r12d
  int32_t id; // ebx
  TileManager *v6; // rax

  if ( Map::inStack(this, tx, ty) )
    return 0;
  if ( tx < 0 || this->m_widthTileCount <= tx || ty < 0 || this->m_heightTileCount <= ty )
    return 0;
  v4 = this->m_cfgmap.width / 48;
  id = this->m_cfgmap.id;
  v6 = Answer::Singleton<TileManager>::instance();
  return TileManager::isWalkblePosition(v6, id, tx, ty, v4);
}


#####################################
bool __cdecl Map::inStack(const Map *const this, int32_t tx, int32_t ty)
{
  std::_List_const_iterator<Position> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<Position> __x; // [rsp+20h] [rbp-10h] BYREF

  if ( std::list<Position>::empty(&this->m_lstStack) )
    return 0;
  for ( iter._M_node = std::list<Position>::begin(&this->m_lstStack)._M_node;
        ;
        std::_List_const_iterator<Position>::operator++(&iter) )
  {
    __x._M_node = std::list<Position>::end(&this->m_lstStack)._M_node;
    if ( !std::_List_const_iterator<Position>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_const_iterator<Position>::operator->(&iter)->x == tx
      && std::_List_const_iterator<Position>::operator->(&iter)->y == ty )
    {
      return 1;
    }
  }
  return 0;
}


#####################################
int32_t __cdecl Map::getViewAreaCount(const Map *const this, int32_t nSize)
{
  return (2 * nSize + 1) * (2 * nSize + 1);
}


#####################################
void __cdecl Map::getViewAreas(
        Map *const this,
        const Position *const pos,
        PositionVector *const outAreas,
        int32_t nSize)
{
  size_t ViewAreaCount; // rdx
  Position area; // [rsp+20h] [rbp-20h]
  Position __x; // [rsp+30h] [rbp-10h] BYREF
  int32_t x; // [rsp+38h] [rbp-8h]
  int32_t y; // [rsp+3Ch] [rbp-4h]

  area = Map::getAreaByPos(this, pos);
  ViewAreaCount = Map::getViewAreaCount(this, nSize);
  std::vector<Position>::reserve(outAreas, ViewAreaCount);
  for ( x = area.x - nSize; nSize + area.x >= x; ++x )
  {
    for ( y = area.y - nSize; nSize + area.y >= y; ++y )
    {
      if ( x >= 0 && this->m_widthAreaCount > x && y >= 0 && this->m_heightAreaCount > y )
      {
        Position::Position(&__x, x, y);
        std::vector<Position>::push_back(outAreas, &__x);
      }
    }
  }
}


#####################################
void __cdecl Map::getNewAreas(
        Map *const this,
        const Position *const oldPos,
        const Position *const newPos,
        PositionVector *const outAreas,
        int32_t nSize)
{
  size_t ViewAreaCount; // rdx
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v7; // rax
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > iter; // [rsp+30h] [rbp-B0h] BYREF
  PositionVector newAreas; // [rsp+40h] [rbp-A0h] BYREF
  PositionVector oldAreas; // [rsp+60h] [rbp-80h] BYREF
  Position newArea; // [rsp+80h] [rbp-60h] BYREF
  Position oldArea; // [rsp+90h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v16; // [rsp+A0h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > __rhs; // [rsp+B0h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > __lhs; // [rsp+C0h] [rbp-20h] BYREF
  Position *tmpArea; // [rsp+C8h] [rbp-18h]

  oldArea = Map::getAreaByPos(this, oldPos);
  newArea = Map::getAreaByPos(this, newPos);
  if ( !Position::operator==(&oldArea, &newArea) )
  {
    std::vector<Position>::vector(&oldAreas);
    std::vector<Position>::vector(&newAreas);
    Map::getViewAreas(this, oldPos, &oldAreas, nSize);
    Map::getViewAreas(this, newPos, &newAreas, nSize);
    ViewAreaCount = Map::getViewAreaCount(this, nSize);
    std::vector<Position>::reserve(outAreas, ViewAreaCount);
    for ( iter._M_current = std::vector<Position>::begin(&newAreas)._M_current;
          ;
          __gnu_cxx::__normal_iterator<Position *,std::vector<Position>>::operator++(&iter) )
    {
      v16._M_current = std::vector<Position>::end(&newAreas)._M_current;
      if ( !__gnu_cxx::operator!=<Position *,std::vector<Position>>(&iter, &v16) )
        break;
      tmpArea = __gnu_cxx::__normal_iterator<Position *,std::vector<Position>>::operator*(&iter);
      __rhs._M_current = std::vector<Position>::end(&oldAreas)._M_current;
      M_current = std::vector<Position>::end(&oldAreas)._M_current;
      v7._M_current = std::vector<Position>::begin(&oldAreas)._M_current;
      __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>,Position>(
                           v7,
                           (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current,
                           tmpArea)._M_current;
      if ( __gnu_cxx::operator==<Position *,std::vector<Position>>(&__lhs, &__rhs) )
        std::vector<Position>::push_back(outAreas, tmpArea);
    }
    std::vector<Position>::~vector(&newAreas);
    std::vector<Position>::~vector(&oldAreas);
  }
}


#####################################
void __cdecl Map::broadcastToAreas(Map *const this, Answer::NetPacket *packet, const PositionVector *const areas)
{
  std::list<short int> *v4; // rax
  GameService *v5; // rax
  IndexMap indexMap; // [rsp+20h] [rbp-70h] BYREF
  std::_List_iterator<Player*> it; // [rsp+50h] [rbp-40h] BYREF
  std::_List_iterator<Player*> v9; // [rsp+60h] [rbp-30h] BYREF
  __int16 __x; // [rsp+74h] [rbp-1Ch] BYREF
  char __k; // [rsp+77h] [rbp-19h] BYREF
  Player *player; // [rsp+78h] [rbp-18h]

  if ( !packet || std::list<Player *>::empty(&this->m_players) )
  {
    Answer::NetPacket::destroy(packet);
  }
  else
  {
    std::map<signed char,std::list<short>>::map(&indexMap);
    for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&it) )
    {
      v9._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&it, &v9) )
        break;
      player = *std::_List_iterator<Player *>::operator*(&it);
      if ( player && Map::inAreas(this, player, areas) )
      {
        __x = Player::getGateIndex(player);
        __k = Player::getConnId(player);
        v4 = std::map<signed char,std::list<short>>::operator[](&indexMap, &__k);
        std::list<short>::push_back(v4, &__x);
      }
    }
    if ( std::map<signed char,std::list<short>>::empty(&indexMap) )
    {
      Answer::NetPacket::destroy(packet);
    }
    else
    {
      v5 = Answer::Singleton<GameService>::instance();
      GameService::broadcast(v5, packet, &indexMap);
    }
    std::map<signed char,std::list<short>>::~map(&indexMap);
  }
}


#####################################
void __cdecl Map::sendSelfEnterArea(Map *const this, Player *player, const Position *const oldPos)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Position newArea; // [rsp+20h] [rbp-40h]
  Position oldArea; // [rsp+30h] [rbp-30h]
  Position pos; // [rsp+40h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( player )
  {
    oldArea = Map::getAreaByPos(this, oldPos);
    pos = StaticObj::getCurrentPixel(player);
    newArea = Map::getAreaByPos(this, &pos);
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x271Du);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, oldArea.x);
      Answer::NetPacket::writeInt32(packet, oldArea.y);
      Answer::NetPacket::writeInt32(packet, newArea.x);
      Answer::NetPacket::writeInt32(packet, newArea.y);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Map::getAreaPlayer(
        Map *const this,
        PlayerList *const outPlayers,
        const Position *const pos,
        int32_t nRang)
{
  Player *player; // [rsp+28h] [rbp-38h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+40h] [rbp-20h] BYREF
  Position CurrentTile; // [rsp+50h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&iter) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&iter, &__x) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( player )
    {
      CurrentTile = StaticObj::getCurrentTile(player);
      if ( Position::tileDistance(pos, &CurrentTile) <= nRang )
        std::list<Player *>::push_back(outPlayers, &player);
    }
  }
}


#####################################
void __cdecl Map::getAreaUnits(Map *const this, const PositionVector *const areas, UnitList *const outUnits)
{
  std::_List_iterator<CLittleHelper*> it_4; // [rsp+20h] [rbp-F0h] BYREF
  std::_List_iterator<Trailer*> it_3; // [rsp+30h] [rbp-E0h] BYREF
  std::_List_iterator<Npc*> it_2; // [rsp+40h] [rbp-D0h] BYREF
  std::_List_iterator<Monster*> it_1; // [rsp+50h] [rbp-C0h] BYREF
  std::_List_iterator<CObjPet*> it_0; // [rsp+60h] [rbp-B0h] BYREF
  std::_List_iterator<Player*> it; // [rsp+70h] [rbp-A0h] BYREF
  std::_List_iterator<Player*> v16; // [rsp+80h] [rbp-90h] BYREF
  Unit *__x; // [rsp+88h] [rbp-88h] BYREF
  std::_List_iterator<CObjPet*> v18; // [rsp+90h] [rbp-80h] BYREF
  Unit *v19; // [rsp+98h] [rbp-78h] BYREF
  std::_List_iterator<Monster*> v20; // [rsp+A0h] [rbp-70h] BYREF
  Unit *v21; // [rsp+A8h] [rbp-68h] BYREF
  std::_List_iterator<Npc*> v22; // [rsp+B0h] [rbp-60h] BYREF
  Unit *v23; // [rsp+B8h] [rbp-58h] BYREF
  std::_List_iterator<Trailer*> v24; // [rsp+C0h] [rbp-50h] BYREF
  Unit *v25; // [rsp+C8h] [rbp-48h] BYREF
  std::_List_iterator<CLittleHelper*> v26; // [rsp+D0h] [rbp-40h] BYREF
  Unit *v27; // [rsp+D8h] [rbp-38h] BYREF
  Player *player; // [rsp+E0h] [rbp-30h]
  CObjPet *pPet; // [rsp+E8h] [rbp-28h]
  Monster *monster; // [rsp+F0h] [rbp-20h]
  Npc *pNpc; // [rsp+F8h] [rbp-18h]
  Trailer *trailer; // [rsp+100h] [rbp-10h]
  CLittleHelper *pCLittleHelper; // [rsp+108h] [rbp-8h]

  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    v16._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &v16) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&it);
    if ( player && Map::inAreas(this, player, areas) )
    {
      __x = player;
      std::list<Unit *>::push_back(outUnits, &__x);
    }
  }
  for ( it_0._M_node = std::list<CObjPet *>::begin(&this->m_pets)._M_node;
        ;
        std::_List_iterator<CObjPet *>::operator++(&it_0) )
  {
    v18._M_node = std::list<CObjPet *>::end(&this->m_pets)._M_node;
    if ( !std::_List_iterator<CObjPet *>::operator!=(&it_0, &v18) )
      break;
    pPet = *std::_List_iterator<CObjPet *>::operator*(&it_0);
    if ( pPet && Map::inAreas(this, pPet, areas) )
    {
      v19 = pPet;
      std::list<Unit *>::push_back(outUnits, &v19);
    }
  }
  for ( it_1._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it_1) )
  {
    v20._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it_1, &v20) )
      break;
    monster = *std::_List_iterator<Monster *>::operator*(&it_1);
    if ( monster && Map::inAreas(this, monster, areas) )
    {
      v21 = monster;
      std::list<Unit *>::push_back(outUnits, &v21);
    }
  }
  for ( it_2._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it_2) )
  {
    v22._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it_2, &v22) )
      break;
    pNpc = *std::_List_iterator<Npc *>::operator*(&it_2);
    if ( pNpc && Map::inAreas(this, pNpc, areas) )
    {
      v23 = pNpc;
      std::list<Unit *>::push_back(outUnits, &v23);
    }
  }
  for ( it_3._M_node = std::list<Trailer *>::begin(&this->m_trailers)._M_node;
        ;
        std::_List_iterator<Trailer *>::operator++(&it_3) )
  {
    v24._M_node = std::list<Trailer *>::end(&this->m_trailers)._M_node;
    if ( !std::_List_iterator<Trailer *>::operator!=(&it_3, &v24) )
      break;
    trailer = *std::_List_iterator<Trailer *>::operator*(&it_3);
    if ( trailer && Map::inAreas(this, trailer, areas) )
    {
      v25 = trailer;
      std::list<Unit *>::push_back(outUnits, &v25);
    }
  }
  for ( it_4._M_node = std::list<CLittleHelper *>::begin(&this->m_CLittleHelperList)._M_node;
        ;
        std::_List_iterator<CLittleHelper *>::operator++(&it_4) )
  {
    v26._M_node = std::list<CLittleHelper *>::end(&this->m_CLittleHelperList)._M_node;
    if ( !std::_List_iterator<CLittleHelper *>::operator!=(&it_4, &v26) )
      break;
    pCLittleHelper = *std::_List_iterator<CLittleHelper *>::operator*(&it_4);
    if ( pCLittleHelper && Map::inAreas(this, pCLittleHelper, areas) )
    {
      v27 = pCLittleHelper;
      std::list<Unit *>::push_back(outUnits, &v27);
    }
  }
}


#####################################
void __cdecl Map::getAllObjects(Map *const this, ObjList *const outObjs)
{
  std::_List_iterator<CLittleHelper*> it_5; // [rsp+10h] [rbp-100h] BYREF
  std::_List_iterator<Trap*> it_4; // [rsp+20h] [rbp-F0h] BYREF
  std::_List_iterator<Plant*> it_3; // [rsp+30h] [rbp-E0h] BYREF
  std::_List_iterator<CDropItem*> it_2; // [rsp+40h] [rbp-D0h] BYREF
  std::_List_iterator<Monster*> it_1; // [rsp+50h] [rbp-C0h] BYREF
  std::_List_iterator<CObjPet*> it_0; // [rsp+60h] [rbp-B0h] BYREF
  std::_List_iterator<Player*> it; // [rsp+70h] [rbp-A0h] BYREF
  std::_List_iterator<Player*> v11; // [rsp+80h] [rbp-90h] BYREF
  StaticObj *__x; // [rsp+88h] [rbp-88h] BYREF
  std::_List_iterator<CObjPet*> v13; // [rsp+90h] [rbp-80h] BYREF
  StaticObj *v14; // [rsp+98h] [rbp-78h] BYREF
  std::_List_iterator<Monster*> v15; // [rsp+A0h] [rbp-70h] BYREF
  StaticObj *v16; // [rsp+A8h] [rbp-68h] BYREF
  std::_List_iterator<CDropItem*> v17; // [rsp+B0h] [rbp-60h] BYREF
  StaticObj *v18; // [rsp+B8h] [rbp-58h] BYREF
  std::_List_iterator<Plant*> v19; // [rsp+C0h] [rbp-50h] BYREF
  StaticObj *v20; // [rsp+C8h] [rbp-48h] BYREF
  std::_List_iterator<Trap*> v21; // [rsp+D0h] [rbp-40h] BYREF
  StaticObj *v22; // [rsp+D8h] [rbp-38h] BYREF
  std::_List_iterator<CLittleHelper*> v23; // [rsp+E0h] [rbp-30h] BYREF
  StaticObj *v24; // [rsp+F0h] [rbp-20h] BYREF
  Monster *monster; // [rsp+F8h] [rbp-18h]
  Plant *pPlant; // [rsp+100h] [rbp-10h]
  CLittleHelper *pCLittleHelper; // [rsp+108h] [rbp-8h]

  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    v11._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &v11) )
      break;
    __x = *std::_List_iterator<Player *>::operator*(&it);
    std::list<StaticObj *>::push_back(outObjs, &__x);
  }
  for ( it_0._M_node = std::list<CObjPet *>::begin(&this->m_pets)._M_node;
        ;
        std::_List_iterator<CObjPet *>::operator++(&it_0) )
  {
    v13._M_node = std::list<CObjPet *>::end(&this->m_pets)._M_node;
    if ( !std::_List_iterator<CObjPet *>::operator!=(&it_0, &v13) )
      break;
    v14 = *std::_List_iterator<CObjPet *>::operator*(&it_0);
    std::list<StaticObj *>::push_back(outObjs, &v14);
  }
  for ( it_1._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it_1) )
  {
    v15._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it_1, &v15) )
      break;
    monster = *std::_List_iterator<Monster *>::operator*(&it_1);
    if ( monster && Monster::IsShow(monster) )
    {
      v16 = *std::_List_iterator<Monster *>::operator*(&it_1);
      std::list<StaticObj *>::push_back(outObjs, &v16);
    }
  }
  for ( it_2._M_node = std::list<CDropItem *>::begin(&this->m_dropItems)._M_node;
        ;
        std::_List_iterator<CDropItem *>::operator++(&it_2) )
  {
    v17._M_node = std::list<CDropItem *>::end(&this->m_dropItems)._M_node;
    if ( !std::_List_iterator<CDropItem *>::operator!=(&it_2, &v17) )
      break;
    v18 = *std::_List_iterator<CDropItem *>::operator*(&it_2);
    std::list<StaticObj *>::push_back(outObjs, &v18);
  }
  for ( it_3._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node; ; std::_List_iterator<Plant *>::operator++(&it_3) )
  {
    v19._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
    if ( !std::_List_iterator<Plant *>::operator!=(&it_3, &v19) )
      break;
    pPlant = *std::_List_iterator<Plant *>::operator*(&it_3);
    if ( pPlant && Plant::IsShow(pPlant) )
    {
      v20 = *std::_List_iterator<Plant *>::operator*(&it_3);
      std::list<StaticObj *>::push_back(outObjs, &v20);
    }
  }
  for ( it_4._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node; ; std::_List_iterator<Trap *>::operator++(&it_4) )
  {
    v21._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
    if ( !std::_List_iterator<Trap *>::operator!=(&it_4, &v21) )
      break;
    v22 = *std::_List_iterator<Trap *>::operator*(&it_4);
    std::list<StaticObj *>::push_back(outObjs, &v22);
  }
  for ( it_5._M_node = std::list<CLittleHelper *>::begin(&this->m_CLittleHelperList)._M_node;
        ;
        std::_List_iterator<CLittleHelper *>::operator++(&it_5) )
  {
    v23._M_node = std::list<CLittleHelper *>::end(&this->m_CLittleHelperList)._M_node;
    if ( !std::_List_iterator<CLittleHelper *>::operator!=(&it_5, &v23) )
      break;
    pCLittleHelper = *std::_List_iterator<CLittleHelper *>::operator*(&it_5);
    if ( pCLittleHelper )
    {
      v24 = pCLittleHelper;
      std::list<StaticObj *>::push_back(outObjs, &v24);
    }
  }
}


#####################################
void __cdecl Map::getAreaObjects(
        Map *const this,
        Player *launcher,
        const PositionVector *const areas,
        ObjList *const outObjs,
        bool bAll)
{
  CharId_t Cid; // rbx
  std::_List_iterator<CLittleHelper*> it_5; // [rsp+30h] [rbp-150h] BYREF
  std::_List_iterator<Trap*> it_4; // [rsp+40h] [rbp-140h] BYREF
  std::_List_iterator<Plant*> it_3; // [rsp+50h] [rbp-130h] BYREF
  std::_List_iterator<CDropItem*> it_2; // [rsp+60h] [rbp-120h] BYREF
  std::_List_iterator<Monster*> it_1; // [rsp+70h] [rbp-110h] BYREF
  std::_List_iterator<CObjPet*> it_0; // [rsp+80h] [rbp-100h] BYREF
  std::_List_iterator<Player*> it; // [rsp+90h] [rbp-F0h] BYREF
  std::_List_iterator<Player*> v27; // [rsp+A0h] [rbp-E0h] BYREF
  StaticObj *__x; // [rsp+A8h] [rbp-D8h] BYREF
  std::_List_iterator<CObjPet*> v29; // [rsp+B0h] [rbp-D0h] BYREF
  StaticObj *v30; // [rsp+B8h] [rbp-C8h] BYREF
  std::_List_iterator<Monster*> v31; // [rsp+C0h] [rbp-C0h] BYREF
  StaticObj *v32; // [rsp+D0h] [rbp-B0h] BYREF
  StaticObj *v33; // [rsp+D8h] [rbp-A8h] BYREF
  std::_List_iterator<CDropItem*> v34; // [rsp+E0h] [rbp-A0h] BYREF
  StaticObj *v35; // [rsp+F0h] [rbp-90h] BYREF
  StaticObj *v36; // [rsp+F8h] [rbp-88h] BYREF
  std::_List_iterator<Plant*> v37; // [rsp+100h] [rbp-80h] BYREF
  StaticObj *v38; // [rsp+108h] [rbp-78h] BYREF
  std::_List_iterator<Trap*> v39; // [rsp+110h] [rbp-70h] BYREF
  StaticObj *v40; // [rsp+118h] [rbp-68h] BYREF
  std::_List_iterator<CLittleHelper*> v41; // [rsp+120h] [rbp-60h] BYREF
  StaticObj *v42; // [rsp+130h] [rbp-50h] BYREF
  Player *player; // [rsp+138h] [rbp-48h]
  CObjPet *pPet; // [rsp+140h] [rbp-40h]
  Monster *monster; // [rsp+148h] [rbp-38h]
  CDropItem *pItem; // [rsp+150h] [rbp-30h]
  Plant *pPlant; // [rsp+158h] [rbp-28h]
  Trap *pTrap; // [rsp+160h] [rbp-20h]
  CLittleHelper *pCLittleHelper; // [rsp+168h] [rbp-18h]

  if ( launcher )
  {
    for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&it) )
    {
      v27._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&it, &v27) )
        break;
      player = *std::_List_iterator<Player *>::operator*(&it);
      if ( player && Map::inAreas(this, player, areas) )
      {
        __x = player;
        std::list<StaticObj *>::push_back(outObjs, &__x);
      }
    }
    for ( it_0._M_node = std::list<CObjPet *>::begin(&this->m_pets)._M_node;
          ;
          std::_List_iterator<CObjPet *>::operator++(&it_0) )
    {
      v29._M_node = std::list<CObjPet *>::end(&this->m_pets)._M_node;
      if ( !std::_List_iterator<CObjPet *>::operator!=(&it_0, &v29) )
        break;
      pPet = *std::_List_iterator<CObjPet *>::operator*(&it_0);
      if ( pPet && Map::inAreas(this, pPet, areas) )
      {
        v30 = pPet;
        std::list<StaticObj *>::push_back(outObjs, &v30);
      }
    }
    for ( it_1._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
          ;
          std::_List_iterator<Monster *>::operator++(&it_1) )
    {
      v31._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
      if ( !std::_List_iterator<Monster *>::operator!=(&it_1, &v31) )
        break;
      monster = *std::_List_iterator<Monster *>::operator*(&it_1);
      if ( monster && Monster::IsShow(monster) )
      {
        if ( bAll )
        {
          if ( (*((unsigned __int8 (__fastcall **)(Monster *))monster->_vptr_Entity + 5))(monster)
            || Map::inAreas(this, monster, areas) )
          {
            v32 = monster;
            std::list<StaticObj *>::push_back(outObjs, &v32);
          }
        }
        else if ( (*((unsigned __int8 (__fastcall **)(Monster *))monster->_vptr_Entity + 5))(monster) != 1
               && Map::inAreas(this, monster, areas) )
        {
          v33 = monster;
          std::list<StaticObj *>::push_back(outObjs, &v33);
        }
      }
    }
    for ( it_2._M_node = std::list<CDropItem *>::begin(&this->m_dropItems)._M_node;
          ;
          std::_List_iterator<CDropItem *>::operator++(&it_2) )
    {
      v34._M_node = std::list<CDropItem *>::end(&this->m_dropItems)._M_node;
      if ( !std::_List_iterator<CDropItem *>::operator!=(&it_2, &v34) )
        break;
      pItem = *std::_List_iterator<CDropItem *>::operator*(&it_2);
      if ( pItem
        && (*((__int64 (__fastcall **)(CDropItem *))pItem->_vptr_Entity + 4))(pItem) > 0
        && !Map::DropNeedBroadcast(this) )
      {
        Cid = Player::getCid(launcher);
        if ( Cid == (*((__int64 (__fastcall **)(CDropItem *))pItem->_vptr_Entity + 4))(pItem)
          && pItem
          && !CDropItem::picked(pItem)
          && Map::inAreas(this, pItem, areas) )
        {
          v35 = pItem;
          std::list<StaticObj *>::push_back(outObjs, &v35);
        }
      }
      else if ( pItem && !CDropItem::picked(pItem) && Map::inAreas(this, pItem, areas) )
      {
        v36 = pItem;
        std::list<StaticObj *>::push_back(outObjs, &v36);
      }
    }
    for ( it_3._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node;
          ;
          std::_List_iterator<Plant *>::operator++(&it_3) )
    {
      v37._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
      if ( !std::_List_iterator<Plant *>::operator!=(&it_3, &v37) )
        break;
      pPlant = *std::_List_iterator<Plant *>::operator*(&it_3);
      if ( pPlant && Plant::IsShow(pPlant) && Map::inAreas(this, pPlant, areas) )
      {
        v38 = pPlant;
        std::list<StaticObj *>::push_back(outObjs, &v38);
      }
    }
    for ( it_4._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node; ; std::_List_iterator<Trap *>::operator++(&it_4) )
    {
      v39._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
      if ( !std::_List_iterator<Trap *>::operator!=(&it_4, &v39) )
        break;
      pTrap = *std::_List_iterator<Trap *>::operator*(&it_4);
      if ( pTrap && Map::inAreas(this, pTrap, areas) )
      {
        v40 = pTrap;
        std::list<StaticObj *>::push_back(outObjs, &v40);
      }
    }
    for ( it_5._M_node = std::list<CLittleHelper *>::begin(&this->m_CLittleHelperList)._M_node;
          ;
          std::_List_iterator<CLittleHelper *>::operator++(&it_5) )
    {
      v41._M_node = std::list<CLittleHelper *>::end(&this->m_CLittleHelperList)._M_node;
      if ( !std::_List_iterator<CLittleHelper *>::operator!=(&it_5, &v41) )
        break;
      pCLittleHelper = *std::_List_iterator<CLittleHelper *>::operator*(&it_5);
      if ( pCLittleHelper && Map::inAreas(this, pCLittleHelper, areas) )
      {
        v42 = pCLittleHelper;
        std::list<StaticObj *>::push_back(outObjs, &v42);
      }
    }
  }
}


#####################################
void __cdecl Map::getAreaTargets(
        Map *const this,
        Unit *const launcher,
        const Position *const pos,
        const CfgActiveSkill *pCfg,
        UnitList *const outUnits)
{
  int32_t v5; // eax
  int32_t v7; // eax
  int32_t v9; // eax
  int32_t v11; // eax
  std::_List_iterator<Trailer*> it_2; // [rsp+30h] [rbp-100h] BYREF
  std::_List_iterator<CObjPet*> it_1; // [rsp+40h] [rbp-F0h] BYREF
  std::_List_iterator<Player*> it_0; // [rsp+50h] [rbp-E0h] BYREF
  std::_List_iterator<Monster*> it; // [rsp+60h] [rbp-D0h] BYREF
  std::_List_iterator<Monster*> v20; // [rsp+70h] [rbp-C0h] BYREF
  Position CurrentTile; // [rsp+80h] [rbp-B0h] BYREF
  Unit *__x; // [rsp+88h] [rbp-A8h] BYREF
  std::_List_iterator<Player*> v23; // [rsp+90h] [rbp-A0h] BYREF
  Position v24; // [rsp+A0h] [rbp-90h] BYREF
  Unit *v25; // [rsp+A8h] [rbp-88h] BYREF
  std::_List_iterator<CObjPet*> v26; // [rsp+B0h] [rbp-80h] BYREF
  Position v27; // [rsp+C0h] [rbp-70h] BYREF
  Unit *v28; // [rsp+C8h] [rbp-68h] BYREF
  std::_List_iterator<Trailer*> v29; // [rsp+D0h] [rbp-60h] BYREF
  Position v30; // [rsp+E0h] [rbp-50h] BYREF
  Unit *v31; // [rsp+F0h] [rbp-40h] BYREF
  int32_t nArea; // [rsp+FCh] [rbp-34h]
  Monster *monster; // [rsp+100h] [rbp-30h]
  Player *player; // [rsp+108h] [rbp-28h]
  CObjPet *pPet; // [rsp+110h] [rbp-20h]
  Trailer *trailer; // [rsp+118h] [rbp-18h]

  if ( pCfg )
  {
    nArea = 0;
    if ( pCfg->range == 2 )
      nArea = pCfg->distance;
    else
      nArea = pCfg->area;
    if ( (pCfg->tar_type & 4) != 0 )
    {
      for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
            ;
            std::_List_iterator<Monster *>::operator++(&it) )
      {
        v20._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
        if ( !std::_List_iterator<Monster *>::operator!=(&it, &v20) )
          break;
        monster = *std::_List_iterator<Monster *>::operator*(&it);
        if ( monster )
        {
          if ( !Monster::isTrap(monster) )
          {
            CurrentTile = StaticObj::getCurrentTile(monster);
            v5 = Position::tileDistance(pos, &CurrentTile);
            if ( v5 <= nArea )
            {
              if ( (*((unsigned __int8 (__fastcall **)(Unit *const, const CfgActiveSkill *, Monster *))launcher->_vptr_Entity
                    + 15))(
                     launcher,
                     pCfg,
                     monster) )
              {
                __x = monster;
                std::list<Unit *>::push_back(outUnits, &__x);
              }
            }
          }
        }
      }
    }
    if ( (pCfg->tar_type & 2) != 0 )
    {
      for ( it_0._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
            ;
            std::_List_iterator<Player *>::operator++(&it_0) )
      {
        v23._M_node = std::list<Player *>::end(&this->m_players)._M_node;
        if ( !std::_List_iterator<Player *>::operator!=(&it_0, &v23) )
          break;
        player = *std::_List_iterator<Player *>::operator*(&it_0);
        if ( player )
        {
          v24 = StaticObj::getCurrentTile(player);
          v7 = Position::tileDistance(pos, &v24);
          if ( v7 <= nArea )
          {
            if ( (*((unsigned __int8 (__fastcall **)(Unit *const, const CfgActiveSkill *, Player *))launcher->_vptr_Entity
                  + 15))(
                   launcher,
                   pCfg,
                   player) )
            {
              v25 = player;
              std::list<Unit *>::push_back(outUnits, &v25);
            }
          }
        }
      }
    }
    if ( (pCfg->tar_type & 0x10) != 0 )
    {
      for ( it_1._M_node = std::list<CObjPet *>::begin(&this->m_pets)._M_node;
            ;
            std::_List_iterator<CObjPet *>::operator++(&it_1) )
      {
        v26._M_node = std::list<CObjPet *>::end(&this->m_pets)._M_node;
        if ( !std::_List_iterator<CObjPet *>::operator!=(&it_1, &v26) )
          break;
        pPet = *std::_List_iterator<CObjPet *>::operator*(&it_1);
        if ( pPet )
        {
          v27 = StaticObj::getCurrentTile(pPet);
          v9 = Position::tileDistance(pos, &v27);
          if ( v9 <= nArea )
          {
            if ( (*((unsigned __int8 (__fastcall **)(Unit *const, const CfgActiveSkill *, CObjPet *))launcher->_vptr_Entity
                  + 15))(
                   launcher,
                   pCfg,
                   pPet) )
            {
              v28 = pPet;
              std::list<Unit *>::push_back(outUnits, &v28);
            }
          }
        }
      }
    }
    if ( (pCfg->tar_type & 0x100) != 0 )
    {
      for ( it_2._M_node = std::list<Trailer *>::begin(&this->m_trailers)._M_node;
            ;
            std::_List_iterator<Trailer *>::operator++(&it_2) )
      {
        v29._M_node = std::list<Trailer *>::end(&this->m_trailers)._M_node;
        if ( !std::_List_iterator<Trailer *>::operator!=(&it_2, &v29) )
          break;
        trailer = *std::_List_iterator<Trailer *>::operator*(&it_2);
        if ( trailer )
        {
          v30 = StaticObj::getCurrentTile(trailer);
          v11 = Position::tileDistance(pos, &v30);
          if ( v11 <= nArea )
          {
            if ( (*((unsigned __int8 (__fastcall **)(Unit *const, const CfgActiveSkill *, Trailer *))launcher->_vptr_Entity
                  + 15))(
                   launcher,
                   pCfg,
                   trailer) )
            {
              v31 = trailer;
              std::list<Unit *>::push_back(outUnits, &v31);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Map::checkAreaChange(Map *const this, Unit *pUnit, const Position *const oldPos)
{
  bool v3; // al
  GameService *v4; // rax
  int8_t AutoConnId; // cl
  Player *v6; // rax
  int8_t ConnId; // cl
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  GameService *v11; // rax
  int8_t v12; // cl
  Player *v13; // rax
  int8_t v14; // cl
  int16_t v15; // r12
  int8_t v16; // bl
  GameService *v17; // rax
  ObjList areaObjs_0; // [rsp+20h] [rbp-E0h] BYREF
  ObjList self_0; // [rsp+30h] [rbp-D0h] BYREF
  ObjList areaObjs; // [rsp+40h] [rbp-C0h] BYREF
  ObjList self; // [rsp+50h] [rbp-B0h] BYREF
  PositionVector newAreas; // [rsp+60h] [rbp-A0h] BYREF
  PositionVector oldAreas; // [rsp+80h] [rbp-80h] BYREF
  Position CurrentPixel; // [rsp+A0h] [rbp-60h] BYREF
  StaticObj *__x; // [rsp+A8h] [rbp-58h] BYREF
  Position newPos; // [rsp+B0h] [rbp-50h] BYREF
  StaticObj *v28; // [rsp+B8h] [rbp-48h] BYREF
  Player *player; // [rsp+C0h] [rbp-40h]
  Answer::NetPacket *packet; // [rsp+C8h] [rbp-38h]
  Answer::NetPacket *packet_0; // [rsp+D0h] [rbp-30h]
  Player *player_0; // [rsp+D8h] [rbp-28h]
  Answer::NetPacket *packet_1; // [rsp+E0h] [rbp-20h]
  Answer::NetPacket *packet_2; // [rsp+E8h] [rbp-18h]

  v3 = !pUnit || std::list<Player *>::empty(&this->m_players);
  if ( !v3 && Entity::getType(pUnit) != EntityType::ET_TRAILER )
  {
    std::vector<Position>::vector(&oldAreas);
    CurrentPixel = StaticObj::getCurrentPixel(pUnit);
    Map::getNewAreas(this, &CurrentPixel, oldPos, &oldAreas, 2);
    if ( !std::vector<Position>::empty(&oldAreas) )
    {
      if ( (*((unsigned __int8 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 5))(pUnit) != 1 )
      {
        std::list<StaticObj *>::list(&self);
        __x = pUnit;
        std::list<StaticObj *>::push_back(&self, &__x);
        v4 = Answer::Singleton<GameService>::instance();
        AutoConnId = GameService::GetAutoConnId(v4);
        packet = Map::packageUnitLeaveArea(this, AutoConnId, &self);
        if ( packet )
          Map::broadcastToAreas(this, packet, &oldAreas);
        std::list<StaticObj *>::~list(&self);
      }
      if ( pUnit )
        v6 = (Player *)__dynamic_cast(
                         pUnit,
                         (const struct __class_type_info *)&`typeinfo for'Unit,
                         (const struct __class_type_info *)&`typeinfo for'Player,
                         0);
      else
        v6 = 0;
      player = v6;
      if ( v6 )
      {
        std::list<StaticObj *>::list(&areaObjs);
        Map::getAreaObjects(this, player, &oldAreas, &areaObjs, 0);
        ConnId = Player::getConnId(player);
        packet_0 = Map::packageUnitLeaveArea(this, ConnId, &areaObjs);
        if ( packet_0 )
        {
          GateIndex = Player::getGateIndex(player);
          v9 = Player::getConnId(player);
          v10 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v10, v9, GateIndex, packet_0);
        }
        std::list<StaticObj *>::~list(&areaObjs);
      }
    }
    std::vector<Position>::vector(&newAreas);
    newPos = StaticObj::getCurrentPixel(pUnit);
    Map::getNewAreas(this, oldPos, &newPos, &newAreas, 2);
    if ( !std::vector<Position>::empty(&newAreas) )
    {
      if ( (*((unsigned __int8 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 5))(pUnit) != 1 )
      {
        std::list<StaticObj *>::list(&self_0);
        v28 = pUnit;
        std::list<StaticObj *>::push_back(&self_0, &v28);
        v11 = Answer::Singleton<GameService>::instance();
        v12 = GameService::GetAutoConnId(v11);
        packet_1 = Map::packageUnitEnterArea(this, v12, &self_0);
        if ( packet_1 )
          Map::broadcastToAreas(this, packet_1, &newAreas);
        std::list<StaticObj *>::~list(&self_0);
      }
      if ( pUnit )
        v13 = (Player *)__dynamic_cast(
                          pUnit,
                          (const struct __class_type_info *)&`typeinfo for'Unit,
                          (const struct __class_type_info *)&`typeinfo for'Player,
                          0);
      else
        v13 = 0;
      player_0 = v13;
      if ( v13 )
      {
        Map::sendSelfEnterArea(this, player_0, oldPos);
        std::list<StaticObj *>::list(&areaObjs_0);
        Map::getAreaObjects(this, player_0, &newAreas, &areaObjs_0, 0);
        v14 = Player::getConnId(player_0);
        packet_2 = Map::packageUnitEnterArea(this, v14, &areaObjs_0);
        if ( packet_2 )
        {
          v15 = Player::getGateIndex(player_0);
          v16 = Player::getConnId(player_0);
          v17 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v17, v16, v15, packet_2);
        }
        std::list<StaticObj *>::~list(&areaObjs_0);
      }
    }
    std::vector<Position>::~vector(&newAreas);
    std::vector<Position>::~vector(&oldAreas);
  }
}


#####################################
void __cdecl Map::addPlayer(Map *const this, Player *player, int32_t x, int32_t y)
{
  int GateIndex; // ebx
  CharId_t Cid; // rax
  CExtCharPet *CharPet; // rax
  CExtCharPet *v9; // rax
  CharLittlerHelper *CharLittlerHelper; // rax
  CharLittlerHelper *v11; // rax
  int32_t RunnerId; // r12d
  CharId_t v13; // rbx
  GameService *v14; // rax
  int32_t EndTime; // ebx
  CMoneyRewardTask *CMoneyRewardTask; // rax
  CMoneyRewardTask *v17; // rax
  int32_t MapId; // r12d
  Player *v19; // rbx
  CWorldBoss *v20; // rax
  Player *playera; // [rsp+10h] [rbp-70h] BYREF
  Map *thisa; // [rsp+18h] [rbp-68h]
  std::_List_iterator<Player*> it; // [rsp+20h] [rbp-60h] BYREF
  Position pos; // [rsp+40h] [rbp-40h]
  std::_List_iterator<Player*> __x; // [rsp+50h] [rbp-30h] BYREF
  Trailer *pTrailer; // [rsp+58h] [rbp-28h]
  int32_t specialRegion; // [rsp+64h] [rbp-1Ch]

  thisa = this;
  playera = player;
  if ( player && Player::getGateIndex(playera) > 0 )
  {
    if ( (*((unsigned __int8 (__fastcall **)(Map *))thisa->_vptr_Map + 8))(thisa) )
    {
      pos = Map::getRandomWalkablePosition(thisa);
      if ( pos.x > 0 && pos.y > 0 )
      {
        x = pos.x;
        y = pos.y;
      }
    }
    else
    {
      specialRegion = 0;
    }
    for ( it._M_node = std::list<Player *>::begin(&thisa->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&it) )
    {
      __x._M_node = std::list<Player *>::end(&thisa->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
        break;
      if ( *std::_List_iterator<Player *>::operator*(&it) == playera )
      {
        GateIndex = Player::getGateIndex(playera);
        Cid = Player::getCid(playera);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "Map::addPlayer player = %p, cid = %lld, cgindex = %d\n",
          playera,
          Cid,
          GateIndex);
        return;
      }
    }
    Unit::setAtTile(playera, thisa, x, y);
    std::list<Player *>::push_front(&thisa->m_players, &playera);
    if ( Map::GetMapId(thisa) != 90041 )
    {
      Map::sendEnterMap(thisa, playera, x, y);
      Map::sendNpcsInMap(thisa, playera);
      Map::sendTrailersInMap(thisa, playera);
      Map::SendObjsInMap(thisa, playera);
      Map::SendStacksInMap(thisa, playera);
      Map::broadcastIntoMap(thisa, playera);
      Player::resetPkModeOnEnterMap(playera, thisa);
      if ( (*((unsigned __int8 (__fastcall **)(Map *))thisa->_vptr_Map + 22))(thisa) != 1 )
      {
        CharPet = Player::GetCharPet(playera);
        if ( CExtCharPet::IsFighting(CharPet) )
        {
          v9 = Player::GetCharPet(playera);
          CExtCharPet::onRestPet(v9);
        }
      }
      if ( (*((unsigned __int8 (__fastcall **)(Map *))thisa->_vptr_Map + 22))(thisa) != 1 )
      {
        CharLittlerHelper = Player::GetCharLittlerHelper(playera);
        CharLittlerHelper::OnRest(CharLittlerHelper);
      }
      else
      {
        v11 = Player::GetCharLittlerHelper(playera);
        CharLittlerHelper::OnAutoWork(v11);
      }
      RunnerId = Map::GetRunnerId(thisa);
      v13 = Player::getCid(playera);
      v14 = Answer::Singleton<GameService>::instance();
      pTrailer = GameService::getPlayerTrailer(v14, v13, RunnerId);
      if ( pTrailer )
      {
        Player::setTrailer(playera, pTrailer);
        EndTime = Trailer::getEndTime(pTrailer);
        CMoneyRewardTask = Player::GetCMoneyRewardTask(playera);
        CMoneyRewardTask::SetTrailerTime(CMoneyRewardTask, EndTime);
        Trailer::SendInfo(pTrailer, playera);
      }
      else
      {
        Player::setTrailer(playera, 0);
        v17 = Player::GetCMoneyRewardTask(playera);
        CMoneyRewardTask::SetTrailerTime(v17, 0);
      }
      if ( Map::IsMoLingHuanYu(thisa) )
      {
        MapId = Map::GetMapId(thisa);
        v19 = playera;
        v20 = Answer::Singleton<CWorldBoss>::instance();
        CWorldBoss::SendRuinsBossInfo(v20, v19, BossType::BOSS_TYPE_MO_LING_HUAN_YU, MapId);
      }
      if ( !Map::IsCycleTower(thisa) )
      {
        Player::updateRecord(playera, 1922, 0);
      }
      else
      {
        Player::SendCycleTowerInfo(playera);
        Player::SendCycleTowerTime(playera);
      }
    }
  }
}


#####################################
void __cdecl Map::removePlayer(Map *const this, Player *player, bool islogout)
{
  CharId_t Cid; // rax
  std::_List_iterator<Player*> it; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+30h] [rbp-10h] BYREF

  if ( player )
  {
    Unit::setAtTile(player, 0, 0, 0);
    it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
    while ( 1 )
    {
      __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
        break;
      if ( *std::_List_iterator<Player *>::operator*(&it) == player )
      {
        if ( islogout )
        {
          Cid = Player::getCid(player);
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_DEBUG,
            "Map::removePlayer remove player = %p, cid = %lld from m_players\n",
            player,
            Cid);
        }
        it._M_node = std::list<Player *>::erase(&this->m_players, it)._M_node;
      }
      else
      {
        std::_List_iterator<Player *>::operator++(&it);
      }
    }
  }
}


#####################################
void __cdecl Map::addMonster(Map *const this, Monster *monster, int32_t x, int32_t y)
{
  Monster *v4; // rbx
  GameService *v5; // rax
  Monster *monstera; // [rsp+10h] [rbp-20h] BYREF
  Map *thisa; // [rsp+18h] [rbp-18h]

  thisa = this;
  monstera = monster;
  if ( monster )
  {
    Unit::setAtTile(monstera, thisa, x, y);
    std::list<Monster *>::push_back(&thisa->m_monsters, &monstera);
    if ( Unit::isAlive(monstera) )
      Map::broadcastIntoMap(thisa, monstera);
    v4 = monstera;
    v5 = Answer::Singleton<GameService>::instance();
    GameService::addMonster(v5, v4);
  }
}


#####################################
void __cdecl Map::addNpc(Map *const this, Npc *npc, int32_t x, int32_t y)
{
  Npc *npca; // [rsp+10h] [rbp-20h] BYREF
  Map *thisa; // [rsp+18h] [rbp-18h]

  thisa = this;
  npca = npc;
  if ( npc )
  {
    Unit::setAtTile(npca, thisa, x, y);
    std::list<Npc *>::push_back(&thisa->m_npcs, &npca);
    Map::broadcastIntoMap(thisa, npca);
  }
}


#####################################
void __cdecl Map::addDropItem(Map *const this, CDropItem *dropItem)
{
  CDropItem *dropItema; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  dropItema = dropItem;
  if ( dropItem )
  {
    std::list<CDropItem *>::push_back(&thisa->m_dropItems, &dropItema);
    Map::broadcastIntoMap(thisa, dropItema);
  }
}


#####################################
bool __cdecl Map::HaveDropAndPlayer(Map *const this, Position Pos)
{
  std::_List_iterator<Npc*> it_1; // [rsp+10h] [rbp-70h] BYREF
  std::_List_iterator<CDropItem*> it_0; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<Player*> it; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<CDropItem*> v10; // [rsp+50h] [rbp-30h] BYREF
  std::_List_iterator<Npc*> v11; // [rsp+60h] [rbp-20h] BYREF
  Player *pPlayer; // [rsp+68h] [rbp-18h]
  CDropItem *pDropItem; // [rsp+70h] [rbp-10h]
  Npc *pNpc; // [rsp+78h] [rbp-8h]

  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    pPlayer = *std::_List_iterator<Player *>::operator*(&it);
    if ( pPlayer )
    {
      if ( StaticObj::GetPosX(pPlayer) == Pos.x && StaticObj::GetPosY(pPlayer) == Pos.y )
        return 1;
    }
  }
  for ( it_0._M_node = std::list<CDropItem *>::begin(&this->m_dropItems)._M_node;
        ;
        std::_List_iterator<CDropItem *>::operator++(&it_0) )
  {
    v10._M_node = std::list<CDropItem *>::end(&this->m_dropItems)._M_node;
    if ( !std::_List_iterator<CDropItem *>::operator!=(&it_0, &v10) )
      break;
    pDropItem = *std::_List_iterator<CDropItem *>::operator*(&it_0);
    if ( pDropItem )
    {
      if ( StaticObj::GetPosX(pDropItem) == Pos.x && StaticObj::GetPosY(pDropItem) == Pos.y )
        return 1;
    }
  }
  for ( it_1._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it_1) )
  {
    v11._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it_1, &v11) )
      break;
    pNpc = *std::_List_iterator<Npc *>::operator*(&it_1);
    if ( pNpc )
    {
      if ( StaticObj::GetPosX(pNpc) == Pos.x && StaticObj::GetPosY(pNpc) == Pos.y )
        return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl Map::addDropItemGroup(Map *const this, const CDropItemGroup *const dropItemGroup)
{
  CDropItem *v2; // rdx
  std::_List_const_iterator<CDropItem*> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<CDropItem*> __x; // [rsp+20h] [rbp-10h] BYREF
  const DropItemList *dropItemList; // [rsp+28h] [rbp-8h]

  dropItemList = CDropItemGroup::GetDropItemList(dropItemGroup);
  for ( iter._M_node = std::list<CDropItem *>::begin(dropItemList)._M_node;
        ;
        std::_List_const_iterator<CDropItem *>::operator++(&iter) )
  {
    __x._M_node = std::list<CDropItem *>::end(dropItemList)._M_node;
    if ( !std::_List_const_iterator<CDropItem *>::operator!=(&iter, &__x) )
      break;
    v2 = *std::_List_const_iterator<CDropItem *>::operator*(&iter);
    Map::addDropItem(this, v2);
  }
}


#####################################
void __cdecl Map::addPlant(Map *const this, Plant *plant)
{
  Plant *planta; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  planta = plant;
  if ( plant )
  {
    std::list<Plant *>::push_back(&thisa->m_plants, &planta);
    Map::broadcastIntoMap(thisa, planta);
  }
}


#####################################
void __cdecl Map::removePlant(Map *const this, EntityId_t id)
{
  Plant **v2; // rax
  std::_List_iterator<Plant*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Plant*> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node; ; std::_List_iterator<Plant *>::operator++(&it) )
  {
    __x._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
    if ( !std::_List_iterator<Plant *>::operator!=(&it, &__x) )
      break;
    v2 = std::_List_iterator<Plant *>::operator*(&it);
    if ( (*((__int64 (__fastcall **)(Plant *))(*v2)->_vptr_Entity + 2))(*v2) == id )
    {
      std::list<Plant *>::erase(&this->m_plants, it);
      return;
    }
  }
}


#####################################
void __cdecl Map::AddLittleHelper(Map *const this, CLittleHelper *pLittleHelper)
{
  CLittleHelper *pLittleHelpera; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  pLittleHelpera = pLittleHelper;
  if ( pLittleHelper )
  {
    std::list<CLittleHelper *>::push_back(&thisa->m_CLittleHelperList, &pLittleHelpera);
    Map::broadcastIntoMap(thisa, pLittleHelpera);
  }
}


#####################################
void __cdecl Map::removeLittleHelper(Map *const this, CLittleHelper *pLittleHelper)
{
  CLittleHelper *pLittleHelpera; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  pLittleHelpera = pLittleHelper;
  if ( pLittleHelper )
    std::list<CLittleHelper *>::remove(&thisa->m_CLittleHelperList, &pLittleHelpera);
}


#####################################
void __cdecl Map::addTrailer(Map *const this, Trailer *trailer, int32_t x, int32_t y)
{
  Trailer *trailera; // [rsp+10h] [rbp-20h] BYREF
  Map *thisa; // [rsp+18h] [rbp-18h]

  thisa = this;
  trailera = trailer;
  if ( trailer )
  {
    Unit::setAtTile(trailera, thisa, x, y);
    std::list<Trailer *>::push_back(&thisa->m_trailers, &trailera);
    Map::broadcastIntoMap(thisa, trailera);
  }
}


#####################################
void __cdecl Map::removeTrailer(Map *const this, Trailer *trailer)
{
  Trailer *trailera; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  trailera = trailer;
  if ( trailer )
    std::list<Trailer *>::remove(&thisa->m_trailers, &trailera);
}


#####################################
void __cdecl Map::addPet(Map *const this, CObjPet *pet)
{
  CObjPet *peta; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  peta = pet;
  if ( pet )
  {
    std::list<CObjPet *>::push_back(&thisa->m_pets, &peta);
    Map::broadcastIntoMap(thisa, peta);
  }
}


#####################################
void __cdecl Map::removePet(Map *const this, CObjPet *pet)
{
  CObjPet *peta; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  peta = pet;
  if ( pet )
    std::list<CObjPet *>::remove(&thisa->m_pets, &peta);
}


#####################################
void __cdecl Map::addTrap(Map *const this, Trap *trap)
{
  Trap *trapa; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  trapa = trap;
  if ( trap )
  {
    std::list<Trap *>::push_back(&thisa->m_traps, &trapa);
    Map::broadcastIntoMap(thisa, trapa);
  }
}


#####################################
void __cdecl Map::removeTrap(Map *const this, Trap *trap)
{
  Trap *trapa; // [rsp+0h] [rbp-10h] BYREF
  Map *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  trapa = trap;
  if ( trap )
    std::list<Trap *>::remove(&thisa->m_traps, &trapa);
}


#####################################
bool __cdecl Map::inSafeRegion(Map *const this, const Position *const pos)
{
  int32_t MapId; // ebx
  CfgData *v3; // rax
  int32_t min_y; // ebx
  CfgMapRegion *v7; // rax
  int32_t max_y; // ebx
  CfgMapRegion *v9; // rax
  Position PixelMin; // [rsp+20h] [rbp-70h]
  Position CurPos; // [rsp+30h] [rbp-60h]
  __gnu_cxx::__normal_iterator<CfgMapRegion*,std::vector<CfgMapRegion> > it; // [rsp+40h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<CfgMapRegion*,std::vector<CfgMapRegion> > __rhs; // [rsp+50h] [rbp-40h] BYREF
  CfgMapRegionVector *pMapRegion; // [rsp+60h] [rbp-30h]
  int32_t startX; // [rsp+68h] [rbp-28h]
  int32_t startY; // [rsp+6Ch] [rbp-24h]
  float width; // [rsp+70h] [rbp-20h]
  float height; // [rsp+74h] [rbp-1Ch]
  int32_t absoluteX; // [rsp+78h] [rbp-18h]
  int32_t absoluteY; // [rsp+7Ch] [rbp-14h]
  Position v21; // 0:rax.8

  MapId = Map::GetMapId(this);
  v3 = Answer::Singleton<CfgData>::instance();
  pMapRegion = CfgData::getRegionOnMap(v3, MapId);
  if ( !pMapRegion )
    return 0;
  for ( it._M_current = std::vector<CfgMapRegion>::begin(pMapRegion)._M_current;
        ;
        __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<CfgMapRegion>::end(pMapRegion)._M_current;
    if ( !__gnu_cxx::operator!=<CfgMapRegion *,std::vector<CfgMapRegion>>(&it, &__rhs) )
      break;
    if ( __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator->(&it)->type == 1
      || __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator->(&it)->type == 2 )
    {
      CurPos = Map::tileToPixel(pos->x, pos->y);
      min_y = __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator->(&it)->min_y;
      v7 = __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator->(&it);
      PixelMin = Map::tileToPixel(v7->min_x, min_y);
      max_y = __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator->(&it)->max_y;
      v9 = __gnu_cxx::__normal_iterator<CfgMapRegion *,std::vector<CfgMapRegion>>::operator->(&it);
      v21 = Map::tileToPixel(v9->max_x, max_y);
      startX = PixelMin.x - 24;
      startY = PixelMin.y - 17;
      width = (float)(v21.x + 24 - (PixelMin.x - 24));
      height = (float)(v21.y + 17 - (PixelMin.y - 17));
      absoluteX = CurPos.x - (PixelMin.x - 24);
      absoluteY = CurPos.y - (PixelMin.y - 17);
      if ( (float)absoluteY >= (float)((float)(height / 2.0)
                                     + (float)((float)((float)-height / width) * (float)absoluteX))
        && (float)((float)((float)(3.0 * height) / 2.0) + (float)((float)((float)-height / width) * (float)absoluteX)) > (float)absoluteY
        && (float)((float)(height / 2.0) + (float)((float)(height / width) * (float)absoluteX)) >= (float)absoluteY
        && (float)absoluteY > (float)((float)(height / -2.0) + (float)((float)(height / width) * (float)absoluteX)) )
      {
        return 1;
      }
    }
  }
  return 0;
}


#####################################
bool __cdecl Map::checkSkillTarget(
        Map *const this,
        Unit *const launcher,
        Position pos,
        Unit *const target,
        const CfgActiveSkill *pCfg)
{
  int32_t range; // eax
  Position posa; // [rsp+10h] [rbp-70h] BYREF
  Unit *launchera; // [rsp+20h] [rbp-60h]
  Map *thisa; // [rsp+28h] [rbp-58h]
  Position CurrentTile; // [rsp+30h] [rbp-50h] BYREF
  Position v14; // [rsp+40h] [rbp-40h] BYREF
  Position v15; // [rsp+50h] [rbp-30h] BYREF
  bool bSuccess; // [rsp+67h] [rbp-19h]
  int32_t distance; // [rsp+68h] [rbp-18h]
  int32_t distance_0; // [rsp+6Ch] [rbp-14h]

  thisa = this;
  launchera = launcher;
  posa = pos;
  if ( !pCfg )
    return 0;
  if ( (*((unsigned __int8 (__fastcall **)(Unit *, const CfgActiveSkill *, Unit *const))launchera->_vptr_Entity + 15))(
         launchera,
         pCfg,
         target) != 1 )
    return 0;
  bSuccess = 0;
  if ( Entity::getType(launchera) == EntityType::ET_PLAYER && StaticObj::InDungeon(launchera) )
    return 1;
  range = pCfg->range;
  if ( range > 4 )
  {
    if ( range != 10 )
      return bSuccess;
  }
  else if ( range < 3 )
  {
    if ( range == 2 )
    {
      CurrentTile = StaticObj::getCurrentTile(target);
      v14 = StaticObj::getCurrentTile(launchera);
      distance = Position::tileDistance(&v14, &CurrentTile);
      return pCfg->distance + 1 >= distance;
    }
    return bSuccess;
  }
  v15 = StaticObj::getCurrentTile(target);
  distance_0 = Position::tileDistance(&posa, &v15);
  return pCfg->area >= distance_0;
}


#####################################
bool __cdecl Map::inRegion(Map *const this, const Position *const pos, const CfgMapRegion *const region)
{
  if ( Map::GetMapId(this) != region->mapid )
    return 0;
  return pos->x >= region->min_x && pos->x <= region->max_x && pos->y >= region->min_y && pos->y <= region->max_y;
}


#####################################
void __cdecl Map::sendEnterMap(Map *const this, Player *player, int32_t x, int32_t y)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  CharId_t Cid; // rdx
  int32_t RunnerId; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x271Fu);
    if ( packet )
    {
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      RunnerId = Map::GetRunnerId(this);
      Answer::NetPacket::writeInt32(packet, RunnerId);
      Answer::NetPacket::writeInt32(packet, this->m_cfgmap.id);
      Answer::NetPacket::writeInt32(packet, x);
      Answer::NetPacket::writeInt32(packet, y);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v10 = Player::getConnId(player);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v11, v10, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Map::sendNpcsInMap(Map *const this, Player *player)
{
  bool v2; // al
  Npc **v3; // rax
  bool v4; // bl
  int8_t ConnId; // cl
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_List_iterator<Npc*> it; // [rsp+10h] [rbp-60h] BYREF
  ObjList outObjs; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<Npc*> v11; // [rsp+30h] [rbp-40h] BYREF
  std::string platform; // [rsp+40h] [rbp-30h] BYREF
  StaticObj *__x; // [rsp+50h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  v2 = !player || std::list<Npc *>::empty(&this->m_npcs);
  if ( !v2 && player )
  {
    std::list<StaticObj *>::list(&outObjs);
    for ( it._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it) )
    {
      v11._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
      if ( !std::_List_iterator<Npc *>::operator!=(&it, &v11) )
        break;
      Player::GetPlatform((const Player *const)&platform);
      v3 = std::_List_iterator<Npc *>::operator*(&it);
      v4 = !Npc::CheckcheckPlatform(*v3, &platform);
      std::string::~string(&platform);
      if ( !v4 )
      {
        __x = *std::_List_iterator<Npc *>::operator*(&it);
        std::list<StaticObj *>::push_back(&outObjs, &__x);
      }
    }
    if ( !std::list<StaticObj *>::empty(&outObjs) )
    {
      ConnId = Player::getConnId(player);
      packet = Map::packageUnitEnterArea(this, ConnId, &outObjs);
      if ( packet )
      {
        GateIndex = Player::getGateIndex(player);
        v7 = Player::getConnId(player);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, v7, GateIndex, packet);
      }
    }
    std::list<StaticObj *>::~list(&outObjs);
  }
}


#####################################
void __cdecl Map::sendTrailersInMap(Map *const this, Player *player)
{
  bool v3; // al
  int8_t ConnId; // cl
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_List_iterator<Trailer*> it; // [rsp+10h] [rbp-50h] BYREF
  ObjList outObjs; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<Trailer*> v10; // [rsp+30h] [rbp-30h] BYREF
  StaticObj *__x; // [rsp+40h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( player && !std::list<Trailer *>::empty(&this->m_trailers) )
  {
    v3 = !player || std::list<Npc *>::empty(&this->m_npcs);
    if ( !v3 && player )
    {
      std::list<StaticObj *>::list(&outObjs);
      for ( it._M_node = std::list<Trailer *>::begin(&this->m_trailers)._M_node;
            ;
            std::_List_iterator<Trailer *>::operator++(&it) )
      {
        v10._M_node = std::list<Trailer *>::end(&this->m_trailers)._M_node;
        if ( !std::_List_iterator<Trailer *>::operator!=(&it, &v10) )
          break;
        __x = *std::_List_iterator<Trailer *>::operator*(&it);
        std::list<StaticObj *>::push_back(&outObjs, &__x);
      }
      if ( !std::list<StaticObj *>::empty(&outObjs) )
      {
        ConnId = Player::getConnId(player);
        packet = Map::packageUnitEnterArea(this, ConnId, &outObjs);
        if ( packet )
        {
          GateIndex = Player::getGateIndex(player);
          v6 = Player::getConnId(player);
          v7 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v7, v6, GateIndex, packet);
        }
      }
      std::list<StaticObj *>::~list(&outObjs);
    }
  }
}


#####################################
void __cdecl Map::sendTeamsInMap(Map *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t x; // eax
  int32_t v6; // eax
  int32_t y; // rax^4
  int32_t v8; // rax^4
  int32_t TeamId; // eax
  CharId_t Cid; // rax
  CExtCharTeam *CharTeam; // rax
  int8_t MemberCount; // al
  int16_t GateIndex; // r12
  int8_t v15; // bl
  GameService *v16; // rax
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-50h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-40h]
  int32_t count; // [rsp+38h] [rbp-38h]
  int oldwoffset; // [rsp+3Ch] [rbp-34h]
  int32_t areaX; // [rsp+40h] [rbp-30h]
  int32_t areaY; // [rsp+44h] [rbp-2Ch]
  int32_t minX; // [rsp+48h] [rbp-28h]
  int32_t maxX; // [rsp+4Ch] [rbp-24h]
  int32_t minY; // [rsp+50h] [rbp-20h]
  int32_t maxY; // [rsp+54h] [rbp-1Ch]
  Player *pTeamPlayer; // [rsp+58h] [rbp-18h]

  if ( player && !std::list<Player *>::empty(&this->m_players) )
  {
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2747u);
    if ( packet )
    {
      count = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
      eiter._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
      {
        areaX = StaticObj::getCurrentPixel(player).x / 232;
        areaY = StaticObj::getCurrentPixel(player).y / 162;
        minX = 232 * (areaX - 1);
        maxX = 232 * areaX + 464;
        minY = 162 * (areaY - 1);
        maxY = 162 * areaY + 324;
        pTeamPlayer = *std::_List_iterator<Player *>::operator*(&iter);
        if ( pTeamPlayer )
        {
          if ( Player::IsTeamLeader(pTeamPlayer) )
          {
            x = StaticObj::getCurrentPixel(pTeamPlayer).x;
            if ( x > minX )
            {
              v6 = StaticObj::getCurrentPixel(pTeamPlayer).x;
              if ( v6 < maxX )
              {
                y = StaticObj::getCurrentPixel(pTeamPlayer).y;
                if ( y > minY )
                {
                  v8 = StaticObj::getCurrentPixel(pTeamPlayer).y;
                  if ( v8 < maxY )
                  {
                    TeamId = Player::GetTeamId(pTeamPlayer);
                    Answer::NetPacket::writeInt32(packet, TeamId);
                    Cid = Player::getCid(pTeamPlayer);
                    Answer::NetPacket::writeInt64(packet, Cid);
                    CharTeam = Player::GetCharTeam(pTeamPlayer);
                    MemberCount = CExtCharTeam::GetMemberCount(CharTeam);
                    Answer::NetPacket::writeInt8(packet, MemberCount);
                    ++count;
                  }
                }
              }
            }
          }
        }
        std::_List_iterator<Player *>::operator++(&iter);
      }
      oldwoffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, 0);
      Answer::NetPacket::writeInt32(packet, count);
      Answer::NetPacket::setWOffset(packet, oldwoffset);
      Answer::NetPacket::setSize(packet, oldwoffset);
      GateIndex = Player::getGateIndex(player);
      v15 = Player::getConnId(player);
      v16 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v16, v15, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Map::broadcastIntoMap(Map *const this, StaticObj *pObj)
{
  GameService *v2; // rax
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( pObj )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x271Eu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      (*((void (__fastcall **)(StaticObj *, Answer::NetPacket *))pObj->_vptr_Entity + 3))(pObj, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this, packet, pObj);
    }
  }
}


#####################################
void __cdecl Map::broadcastLeaveMap(Map *const this, StaticObj *pObj)
{
  GameService *v2; // rax
  int64_t v3; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( pObj )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2720u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      v3 = (*((__int64 (__fastcall **)(StaticObj *))pObj->_vptr_Entity + 2))(pObj);
      Answer::NetPacket::writeInt64(packet, v3);
      Type = Entity::getType(pObj);
      Answer::NetPacket::writeInt8(packet, Type);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this, packet, pObj);
    }
  }
}


#####################################
void __cdecl Map::broadcast(Map *const this, Answer::NetPacket *inPacket)
{
  std::list<short int> *v2; // rax
  GameService *v3; // rax
  IndexMap indexMap; // [rsp+10h] [rbp-70h] BYREF
  std::_List_iterator<Player*> it; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<Player*> v6; // [rsp+50h] [rbp-30h] BYREF
  __int16 __x; // [rsp+64h] [rbp-1Ch] BYREF
  char __k; // [rsp+67h] [rbp-19h] BYREF
  Player *player; // [rsp+68h] [rbp-18h]

  if ( inPacket )
  {
    if ( std::list<Player *>::empty(&this->m_players) )
    {
      Answer::NetPacket::destroy(inPacket);
    }
    else
    {
      std::map<signed char,std::list<short>>::map(&indexMap);
      for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
            ;
            std::_List_iterator<Player *>::operator++(&it) )
      {
        v6._M_node = std::list<Player *>::end(&this->m_players)._M_node;
        if ( !std::_List_iterator<Player *>::operator!=(&it, &v6) )
          break;
        player = *std::_List_iterator<Player *>::operator*(&it);
        if ( player )
        {
          __x = Player::getGateIndex(player);
          __k = Player::getConnId(player);
          v2 = std::map<signed char,std::list<short>>::operator[](&indexMap, &__k);
          std::list<short>::push_back(v2, &__x);
        }
      }
      v3 = Answer::Singleton<GameService>::instance();
      GameService::broadcast(v3, inPacket, &indexMap);
      std::map<signed char,std::list<short>>::~map(&indexMap);
    }
  }
}


#####################################
void __cdecl Map::broadcastAreaAround(Map *const this, Answer::NetPacket *inPacket, StaticObj *pObj)
{
  __int64 v5; // rbx
  std::list<short int> *v7; // rax
  std::list<short int> *v8; // rax
  std::list<short int> *v9; // rax
  GameService *v10; // rax
  IndexMap indexMap; // [rsp+20h] [rbp-B0h] BYREF
  Position playerPos; // [rsp+50h] [rbp-80h]
  std::_List_iterator<Player*> it; // [rsp+60h] [rbp-70h] BYREF
  Position currentPos; // [rsp+70h] [rbp-60h]
  std::_List_iterator<Player*> v16; // [rsp+80h] [rbp-50h] BYREF
  __int16 __x; // [rsp+94h] [rbp-3Ch] BYREF
  char __k; // [rsp+97h] [rbp-39h] BYREF
  __int16 v19; // [rsp+98h] [rbp-38h] BYREF
  char v20; // [rsp+9Bh] [rbp-35h] BYREF
  __int16 GateIndex; // [rsp+9Ch] [rbp-34h] BYREF
  char ConnId; // [rsp+9Fh] [rbp-31h] BYREF
  int32_t areaX; // [rsp+A0h] [rbp-30h]
  int32_t areaY; // [rsp+A4h] [rbp-2Ch]
  int32_t minX; // [rsp+A8h] [rbp-28h]
  int32_t maxX; // [rsp+ACh] [rbp-24h]
  int32_t minY; // [rsp+B0h] [rbp-20h]
  int32_t maxY; // [rsp+B4h] [rbp-1Ch]
  Player *player; // [rsp+B8h] [rbp-18h]

  if ( inPacket )
  {
    if ( std::list<Player *>::empty(&this->m_players) || !pObj )
      goto LABEL_7;
    if ( (*((unsigned __int8 (__fastcall **)(StaticObj *))pObj->_vptr_Entity + 5))(pObj) )
    {
      Map::broadcast(this, inPacket);
    }
    else
    {
      currentPos = StaticObj::getCurrentPixel(pObj);
      if ( currentPos.x <= 0
        || currentPos.x > this->m_cfgmap.width
        || currentPos.y <= 0
        || currentPos.y > this->m_cfgmap.height )
      {
LABEL_7:
        Answer::NetPacket::destroy(inPacket);
        return;
      }
      areaX = currentPos.x / 232;
      areaY = currentPos.y / 162;
      minX = 232 * (currentPos.x / 232) - 464;
      maxX = 232 * (currentPos.x / 232) + 696;
      minY = 162 * (currentPos.y / 162) - 324;
      maxY = 162 * (currentPos.y / 162) + 486;
      std::map<signed char,std::list<short>>::map(&indexMap);
      for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
            ;
            std::_List_iterator<Player *>::operator++(&it) )
      {
        v16._M_node = std::list<Player *>::end(&this->m_players)._M_node;
        if ( !std::_List_iterator<Player *>::operator!=(&it, &v16) )
          break;
        player = *std::_List_iterator<Player *>::operator*(&it);
        if ( player )
        {
          playerPos = StaticObj::getCurrentPixel(player);
          if ( Entity::getType(pObj) == EntityType::ET_DROPITEM
            && (*((__int64 (__fastcall **)(StaticObj *))pObj->_vptr_Entity + 4))(pObj) > 0
            && !Map::DropNeedBroadcast(this) )
          {
            if ( playerPos.x >= minX && playerPos.x < maxX && playerPos.y >= minY && playerPos.y < maxY )
            {
              v5 = (*((__int64 (__fastcall **)(StaticObj *))pObj->_vptr_Entity + 4))(pObj);
              if ( v5 == Player::getCid(player) )
              {
                __x = Player::getGateIndex(player);
                __k = Player::getConnId(player);
                v7 = std::map<signed char,std::list<short>>::operator[](&indexMap, &__k);
                std::list<short>::push_back(v7, &__x);
              }
            }
          }
          else if ( playerPos.x < minX || playerPos.x >= maxX || playerPos.y < minY || playerPos.y >= maxY )
          {
            if ( Entity::getType(pObj) == EntityType::ET_TRAILER )
            {
              GateIndex = Player::getGateIndex(player);
              ConnId = Player::getConnId(player);
              v9 = std::map<signed char,std::list<short>>::operator[](&indexMap, &ConnId);
              std::list<short>::push_back(v9, &GateIndex);
            }
          }
          else
          {
            v19 = Player::getGateIndex(player);
            v20 = Player::getConnId(player);
            v8 = std::map<signed char,std::list<short>>::operator[](&indexMap, &v20);
            std::list<short>::push_back(v8, &v19);
          }
        }
      }
      v10 = Answer::Singleton<GameService>::instance();
      GameService::broadcast(v10, inPacket, &indexMap);
      std::map<signed char,std::list<short>>::~map(&indexMap);
    }
  }
}


#####################################
int32_t __cdecl Map::xAddHalfY(Map *const this, int32_t x, int32_t y)
{
  return x + y / 2;
}


#####################################
int32_t __cdecl Map::xSubHalfY(Map *const this, int32_t x, int32_t y)
{
  return x - y / 2;
}


#####################################
bool __cdecl Map::inAreas(Map *const this, StaticObj *pObj, const PositionVector *const areas)
{
  const Position *v5; // rdx
  __gnu_cxx::__normal_iterator<const Position*,std::vector<Position> > it; // [rsp+20h] [rbp-30h] BYREF
  Position pos; // [rsp+30h] [rbp-20h] BYREF
  __gnu_cxx::__normal_iterator<const Position*,std::vector<Position> > __rhs; // [rsp+40h] [rbp-10h] BYREF

  if ( !pObj || StaticObj::getMap(pObj) != this )
    return 0;
  pos = StaticObj::getCurrentPixel(pObj);
  for ( it._M_current = std::vector<Position>::begin(areas)._M_current;
        ;
        __gnu_cxx::__normal_iterator<Position const*,std::vector<Position>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<Position>::end(areas)._M_current;
    if ( !__gnu_cxx::operator!=<Position const*,std::vector<Position>>(&it, &__rhs) )
      break;
    v5 = __gnu_cxx::__normal_iterator<Position const*,std::vector<Position>>::operator*(&it);
    if ( Map::checkPos(this, &pos, v5) )
      return 1;
  }
  return 0;
}


#####################################
bool __cdecl Map::checkPos(const Map *const this, const Position *const pos, const Position *const area)
{
  int nLeft; // [rsp+18h] [rbp-10h]
  int nBottom; // [rsp+20h] [rbp-8h]

  nLeft = 232 * area->x;
  nBottom = 162 * area->y;
  return pos->x >= nLeft && pos->x < nLeft + 232 && pos->y >= nBottom && pos->y < nBottom + 162;
}


#####################################
void __cdecl Map::updatePlayers(Map *const this)
{
  int16_t GateIndex; // ax
  GameService *v2; // rax
  std::_List_iterator<Player*> it; // [rsp+10h] [rbp-40h] BYREF
  PlayerList players; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  std::list<Player *>::list(&players, &this->m_players);
  for ( it._M_node = std::list<Player *>::begin(&players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    __x._M_node = std::list<Player *>::end(&players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&it);
    if ( player )
    {
      if ( Player::getGateIndex(player) <= 0 )
      {
        GateIndex = Player::getGateIndex(player);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "Map::updatePlayers with player->getGateIndex() == %d\n",
          GateIndex);
        (*((void (__fastcall **)(Map *const, Player *, __int64))this->_vptr_Map + 16))(this, player, 1);
        v2 = Answer::Singleton<GameService>::instance();
        GameService::removePlayer(v2, player);
      }
      else
      {
        Unit::update(player);
      }
    }
    else
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Map::updatePlayers with player == NULL\n");
    }
  }
  std::list<Player *>::~list(&players);
}


#####################################
bool __cdecl Map::IsSpecialBossMap(const Map *const this)
{
  return this->m_cfgmap.type == 1
      && (this->m_cfgmap.param == 13
       || this->m_cfgmap.param == 15
       || this->m_cfgmap.param == 16
       || this->m_cfgmap.param == 19
       || this->m_cfgmap.param == 22);
}


#####################################
bool __cdecl Map::IsBeastShrine(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 22;
}


#####################################
bool __cdecl Map::IsMoLingHuanYu(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 15;
}


#####################################
bool __cdecl Map::IsCycleTower(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 16;
}


#####################################
bool __cdecl Map::IsKuangDong(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 18;
}


#####################################
bool __cdecl Map::IsWastelands(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 19;
}


#####################################
bool __cdecl Map::IsXinMoCun(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 24;
}


#####################################
bool __cdecl Map::IsXinMoMap(const Map *const this)
{
  return this->m_cfgmap.type == 1 && this->m_cfgmap.param == 25;
}


#####################################
void __cdecl Map::updateMonsters(Map *const this)
{
  std::_List_iterator<Monster*> v1; // rax
  std::_List_iterator<Monster*> v2; // rax
  std::_List_iterator<Monster*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  Monster *monster; // [rsp+28h] [rbp-8h]

  it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
  while ( 1 )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    monster = *std::_List_iterator<Monster *>::operator*(&it);
    if ( monster )
    {
      Unit::update(monster);
      if ( (*((unsigned __int8 (__fastcall **)(Monster *))monster->_vptr_Entity + 37))(monster) )
      {
        (*((void (__fastcall **)(Monster *))monster->_vptr_Entity + 38))(monster);
        v2._M_node = std::_List_iterator<Monster *>::operator++(&it, 0)._M_node;
        std::list<Monster *>::erase(&this->m_monsters, v2);
      }
      else
      {
        std::_List_iterator<Monster *>::operator++(&it);
      }
    }
    else
    {
      v1._M_node = std::_List_iterator<Monster *>::operator++(&it, 0)._M_node;
      std::list<Monster *>::erase(&this->m_monsters, v1);
    }
  }
}


#####################################
void __cdecl Map::updateNpcs(Map *const this)
{
  std::_List_iterator<Npc*> v2; // rax
  NpcActivity *v3; // rbx
  CPoolManager *v4; // rax
  std::_List_iterator<Npc*> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Npc*> __x; // [rsp+20h] [rbp-20h] BYREF
  Npc *npc; // [rsp+28h] [rbp-18h]

  it._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node;
  while ( 1 )
  {
    __x._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it, &__x) )
      break;
    npc = *std::_List_iterator<Npc *>::operator*(&it);
    if ( npc && (*((unsigned __int8 (__fastcall **)(Npc *))npc->_vptr_Entity + 33))(npc) )
    {
      Npc::leaveMap(npc);
      v2._M_node = std::_List_iterator<Npc *>::operator++(&it, 0)._M_node;
      std::list<Npc *>::erase(&this->m_npcs, v2);
      if ( npc )
        v3 = (NpcActivity *)__dynamic_cast(
                              npc,
                              (const struct __class_type_info *)&`typeinfo for'Npc,
                              (const struct __class_type_info *)&`typeinfo for'NpcActivity,
                              0);
      else
        v3 = 0;
      v4 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<NpcActivity>(v4, v3);
    }
    else
    {
      std::_List_iterator<Npc *>::operator++(&it);
    }
  }
}


#####################################
void __cdecl Map::updatePlants(Map *const this)
{
  std::_List_iterator<Plant*> v1; // rax
  PlantActivity *v3; // rbx
  CPoolManager *v4; // rax
  PlantDungeon *v6; // rbx
  CPoolManager *v7; // rax
  std::_List_iterator<Plant*> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Plant*> __x; // [rsp+20h] [rbp-20h] BYREF
  Plant *plant; // [rsp+28h] [rbp-18h]

  it._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node;
  while ( 1 )
  {
    __x._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
    if ( !std::_List_iterator<Plant *>::operator!=(&it, &__x) )
      break;
    plant = *std::_List_iterator<Plant *>::operator*(&it);
    if ( !plant )
      goto LABEL_3;
    (*((void (__fastcall **)(Plant *))plant->_vptr_Entity + 11))(plant);
    if ( (*((unsigned __int8 (__fastcall **)(Plant *))plant->_vptr_Entity + 9))(plant) )
    {
      Plant::broadcastRemove(plant);
      if ( plant
        && __dynamic_cast(
             plant,
             (const struct __class_type_info *)&`typeinfo for'Plant,
             (const struct __class_type_info *)&`typeinfo for'PlantActivity,
             0) )
      {
        if ( plant )
          v3 = (PlantActivity *)__dynamic_cast(
                                  plant,
                                  (const struct __class_type_info *)&`typeinfo for'Plant,
                                  (const struct __class_type_info *)&`typeinfo for'PlantActivity,
                                  0);
        else
          v3 = 0;
        v4 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<PlantActivity>(v4, v3);
      }
      else if ( plant
             && __dynamic_cast(
                  plant,
                  (const struct __class_type_info *)&`typeinfo for'Plant,
                  (const struct __class_type_info *)&`typeinfo for'PlantDungeon,
                  0) )
      {
        if ( plant )
          v6 = (PlantDungeon *)__dynamic_cast(
                                 plant,
                                 (const struct __class_type_info *)&`typeinfo for'Plant,
                                 (const struct __class_type_info *)&`typeinfo for'PlantDungeon,
                                 0);
        else
          v6 = 0;
        v7 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<PlantDungeon>(v7, v6);
      }
      else if ( plant )
      {
        (*((void (__fastcall **)(Plant *))plant->_vptr_Entity + 1))(plant);
      }
LABEL_3:
      v1._M_node = std::_List_iterator<Plant *>::operator++(&it, 0)._M_node;
      std::list<Plant *>::erase(&this->m_plants, v1);
    }
    else
    {
      std::_List_iterator<Plant *>::operator++(&it);
    }
  }
}


#####################################
void __cdecl Map::updateDropItems(Map *const this)
{
  std::_List_iterator<CDropItem*> v2; // rax
  CPoolManager *v3; // rax
  std::_List_iterator<CDropItem*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CDropItem*> __x; // [rsp+20h] [rbp-10h] BYREF
  CDropItem *pDropItem; // [rsp+28h] [rbp-8h]

  it._M_node = std::list<CDropItem *>::begin(&this->m_dropItems)._M_node;
  while ( 1 )
  {
    __x._M_node = std::list<CDropItem *>::end(&this->m_dropItems)._M_node;
    if ( !std::_List_iterator<CDropItem *>::operator!=(&it, &__x) )
      break;
    pDropItem = *std::_List_iterator<CDropItem *>::operator*(&it);
    if ( pDropItem && CDropItem::checkEnd(pDropItem) )
    {
      Map::broadcastLeaveMap(this, pDropItem);
      v2._M_node = std::_List_iterator<CDropItem *>::operator++(&it, 0)._M_node;
      std::list<CDropItem *>::erase(&this->m_dropItems, v2);
      v3 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<CDropItem>(v3, pDropItem);
    }
    else
    {
      std::_List_iterator<CDropItem *>::operator++(&it);
    }
  }
}


#####################################
void __cdecl Map::updateTraps(Map *const this)
{
  Trap **v1; // rax
  std::_List_iterator<Trap*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Trap*> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node; ; std::_List_iterator<Trap *>::operator++(&it) )
  {
    __x._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
    if ( !std::_List_iterator<Trap *>::operator!=(&it, &__x) )
      break;
    v1 = std::_List_iterator<Trap *>::operator*(&it);
    Trap::checkState(*v1);
  }
}


#####################################
void __cdecl Map::updateTrailers(Map *const this)
{
  std::_List_iterator<Trailer*> v1; // rax
  GameService *v2; // rax
  CPoolManager *v3; // rax
  std::_List_iterator<Trailer*> it; // [rsp+10h] [rbp-40h] BYREF
  TrailerList trailers; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<Trailer*> __x; // [rsp+30h] [rbp-20h] BYREF
  Trailer *pTrailer; // [rsp+38h] [rbp-18h]

  std::list<Trailer *>::list(&trailers, &this->m_trailers);
  it._M_node = std::list<Trailer *>::begin(&trailers)._M_node;
  while ( 1 )
  {
    __x._M_node = std::list<Trailer *>::end(&trailers)._M_node;
    if ( !std::_List_iterator<Trailer *>::operator!=(&it, &__x) )
      break;
    pTrailer = *std::_List_iterator<Trailer *>::operator*(&it);
    if ( pTrailer )
    {
      Unit::update(pTrailer);
      if ( Trailer::isLifeEnd(pTrailer) )
      {
        Trailer::LeaveMap(pTrailer);
        v2 = Answer::Singleton<GameService>::instance();
        GameService::removeTrailer(v2, pTrailer);
        v3 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<Trailer>(v3, pTrailer);
      }
      std::_List_iterator<Trailer *>::operator++(&it);
    }
    else
    {
      v1._M_node = std::_List_iterator<Trailer *>::operator++(&it, 0)._M_node;
      std::list<Trailer *>::erase(&trailers, v1);
    }
  }
  std::list<Trailer *>::~list(&trailers);
}


#####################################
void __cdecl Map::SendStacksInMap(Map *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player && !std::list<Position>::empty(&this->m_lstStack) )
  {
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x272Au);
    if ( packet )
    {
      Map::appendStack(this, packet, &this->m_lstStack);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Map::SendObjsInMap(Map *const this, Player *player)
{
  int8_t ConnId; // cl
  int16_t GateIndex; // r12
  int8_t v4; // bl
  GameService *v5; // rax
  PositionVector outAreas; // [rsp+10h] [rbp-50h] BYREF
  ObjList outObjs; // [rsp+30h] [rbp-30h] BYREF
  Position pos; // [rsp+40h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( player )
  {
    std::list<StaticObj *>::list(&outObjs);
    std::vector<Position>::vector(&outAreas);
    pos = StaticObj::getCurrentPixel(player);
    Map::getViewAreas(this, &pos, &outAreas, 2);
    if ( !std::vector<Position>::empty(&outAreas) )
      Map::getAreaObjects(this, player, &outAreas, &outObjs, 1);
    if ( !std::list<StaticObj *>::empty(&outObjs) )
    {
      ConnId = Player::getConnId(player);
      packet = Map::packageUnitEnterArea(this, ConnId, &outObjs);
      if ( packet )
      {
        GateIndex = Player::getGateIndex(player);
        v4 = Player::getConnId(player);
        v5 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v5, v4, GateIndex, packet);
      }
    }
    std::vector<Position>::~vector(&outAreas);
    std::list<StaticObj *>::~list(&outObjs);
  }
}


#####################################
void __cdecl Map::appendStack(Map *const this, Answer::NetPacket *packet, const PosList *const posList)
{
  int16_t v3; // dx
  int16_t x; // dx
  int16_t y; // dx
  std::_List_const_iterator<Position> eiter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_const_iterator<Position> iter; // [rsp+30h] [rbp-10h] BYREF

  if ( packet )
  {
    v3 = std::list<Position>::size(posList);
    Answer::NetPacket::writeInt16(packet, v3);
    iter._M_node = std::list<Position>::begin(posList)._M_node;
    eiter._M_node = std::list<Position>::end(posList)._M_node;
    while ( std::_List_const_iterator<Position>::operator!=(&iter, &eiter) )
    {
      x = std::_List_const_iterator<Position>::operator->(&iter)->x;
      Answer::NetPacket::writeInt16(packet, x);
      y = std::_List_const_iterator<Position>::operator->(&iter)->y;
      Answer::NetPacket::writeInt16(packet, y);
      std::_List_const_iterator<Position>::operator++(&iter);
    }
  }
}


#####################################
void __cdecl Map::AddStack(Map *const this, const PosList *const posList)
{
  const Position *v2; // rax
  GameService *v3; // rax
  uint32_t WOffset; // eax
  std::_List_const_iterator<Position> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<Position> __x; // [rsp+20h] [rbp-10h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::list<Position>::begin(posList)._M_node; ; std::_List_const_iterator<Position>::operator++(&iter) )
  {
    __x._M_node = std::list<Position>::end(posList)._M_node;
    if ( !std::_List_const_iterator<Position>::operator!=(&iter, &__x) )
      break;
    v2 = std::_List_const_iterator<Position>::operator*(&iter);
    std::list<Position>::push_back(&this->m_lstStack, v2);
  }
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x272Au);
  if ( packet )
  {
    Map::appendStack(this, packet, posList);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Map::RemoveStack(Map *const this, const PosList *const posList)
{
  const Position *v2; // rdx
  GameService *v3; // rax
  uint32_t WOffset; // eax
  std::_List_const_iterator<Position> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<Position> __x; // [rsp+20h] [rbp-10h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::list<Position>::begin(posList)._M_node; ; std::_List_const_iterator<Position>::operator++(&iter) )
  {
    __x._M_node = std::list<Position>::end(posList)._M_node;
    if ( !std::_List_const_iterator<Position>::operator!=(&iter, &__x) )
      break;
    v2 = std::_List_const_iterator<Position>::operator*(&iter);
    Map::removeStack(this, v2);
  }
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x272Bu);
  if ( packet )
  {
    Map::appendStack(this, packet, posList);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Map::removeStack(Map *const this, const Position *const pos)
{
  Position *v2; // rax
  std::_List_iterator<Position> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Position> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<Position>::begin(&this->m_lstStack)._M_node;
        ;
        std::_List_iterator<Position>::operator++(&iter) )
  {
    __x._M_node = std::list<Position>::end(&this->m_lstStack)._M_node;
    if ( !std::_List_iterator<Position>::operator!=(&iter, &__x) )
      break;
    v2 = std::_List_iterator<Position>::operator*(&iter);
    if ( Position::operator==(v2, pos) )
    {
      std::list<Position>::erase(&this->m_lstStack, iter);
      return;
    }
  }
}


#####################################
void __cdecl Map::removeNpc(Map *const this, EntityId_t npcid)
{
  Npc **v2; // rax
  Npc **v3; // rax
  std::_List_iterator<Npc*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Npc*> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it) )
  {
    __x._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it, &__x) )
      break;
    v2 = std::_List_iterator<Npc *>::operator*(&it);
    if ( (*((__int64 (__fastcall **)(Npc *))(*v2)->_vptr_Entity + 2))(*v2) == npcid )
    {
      v3 = std::_List_iterator<Npc *>::operator*(&it);
      Npc::leaveMap(*v3);
      std::list<Npc *>::erase(&this->m_npcs, it);
      return;
    }
  }
}


#####################################
void __cdecl Map::OnKillMonster(Map *const this, EntityId_t MonsterId)
{
  Monster **v2; // rax
  Monster **v3; // rax
  Monster **v4; // rax
  Monster **v5; // rax
  Monster *v6; // rbx
  void (__fastcall *v7)(Monster *, _QWORD); // r12
  Monster **v8; // rax
  int v9; // eax
  std::_List_iterator<Monster*> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-20h] BYREF

  for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    v2 = std::_List_iterator<Monster *>::operator*(&it);
    if ( (*((__int64 (__fastcall **)(Monster *))(*v2)->_vptr_Entity + 2))(*v2) == MonsterId )
    {
      v3 = std::_List_iterator<Monster *>::operator*(&it);
      Monster::leaveMap(*v3);
      v4 = std::_List_iterator<Monster *>::operator*(&it);
      Monster::SetDieType(*v4, 1);
      v5 = std::_List_iterator<Monster *>::operator*(&it);
      v6 = *v5;
      v7 = (void (__fastcall *)(Monster *, _QWORD))*((_QWORD *)(*v5)->_vptr_Entity + 21);
      v8 = std::_List_iterator<Monster *>::operator*(&it);
      v9 = (*((__int64 (__fastcall **)(Monster *))(*v8)->_vptr_Entity + 19))(*v8);
      v7(v6, (unsigned int)-v9);
      return;
    }
  }
}


#####################################
void __cdecl Map::AddContribution(Map *const this, int32_t Values, CURRENCY_CHANGE_REASON nOpWay)
{
  std::_List_iterator<Player*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+20h] [rbp-10h] BYREF
  Player *pPlayer; // [rsp+28h] [rbp-8h]

  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    pPlayer = *std::_List_iterator<Player *>::operator*(&it);
    if ( pPlayer )
      Player::AddCurrency(pPlayer, CURRENCY_TYPE::CURRENCY_CONTRIBUTION, Values, nOpWay, 0);
  }
}


#####################################
void __cdecl Map::delMonster(Map *const this, int32_t mid)
{
  std::_List_iterator<Monster*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  Monster *pMonster; // [rsp+28h] [rbp-8h]

  for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    pMonster = *std::_List_iterator<Monster *>::operator*(&it);
    if ( pMonster && Monster::getMid(pMonster) == mid )
      Monster::setDelFlg(pMonster);
  }
}


#####################################
void __cdecl Map::cleanActivityMonster(Map *const this, int32_t nActivityId)
{
  std::_List_iterator<Monster*> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  Monster *pMonster; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&iter) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&iter, &__x) )
      break;
    pMonster = *std::_List_iterator<Monster *>::operator*(&iter);
    if ( pMonster && Monster::GetActivityId(pMonster) == nActivityId )
      Monster::setDelFlg(pMonster);
  }
}


#####################################
void __cdecl Map::OnStartGoblinRuQin(Map *const this, int32_t nActivityId, int32_t RefreshCount)
{
  CfgData *v3; // rax
  const cfgGoblinTableData *GoblinTable; // rax
  int32_t nId; // edx
  unsigned int v6; // eax
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v8; // rax
  std::vector<CurrentData> *container; // r12
  const CurrentData *v10; // rbx
  __gnu_cxx::__normal_iterator<const CurrentData*,std::vector<CurrentData> > v11; // rax
  CurrentData *v12; // rax
  size_t v13; // rbx
  int32_t y; // r12d
  int32_t x; // esi
  CurrentDatas refresh; // [rsp+10h] [rbp-70h] BYREF
  std::vector<Position> PosVector; // [rsp+30h] [rbp-50h] BYREF
  int32_t MonsterCount; // [rsp+4Ch] [rbp-34h]
  const cfgGoblinData *goblin; // [rsp+50h] [rbp-30h]
  int32_t nSize; // [rsp+58h] [rbp-28h]
  int32_t nFlush; // [rsp+5Ch] [rbp-24h]
  uint32_t i; // [rsp+60h] [rbp-20h]
  int32_t nowCount; // [rsp+64h] [rbp-1Ch]
  int32_t mid; // [rsp+68h] [rbp-18h]
  uint32_t i_0; // [rsp+6Ch] [rbp-14h]

  MonsterCount = 0;
  v3 = Answer::Singleton<CfgData>::instance();
  GoblinTable = CfgData::GetGoblinTable(v3);
  goblin = cfgGoblinTableData::getGoblinData(GoblinTable, RefreshCount);
  if ( goblin )
  {
    for ( i = 0; i < std::vector<CurrentData>::size(&goblin->m_RefreshMonsters); ++i )
    {
      nId = std::vector<CurrentData>::operator[](&goblin->m_RefreshMonsters, i)->nId;
      Map::delMonster(this, nId);
      MonsterCount += std::vector<CurrentData>::operator[](&goblin->m_RefreshMonsters, i)->nValue;
    }
    v6 = time(0);
    srand(v6);
    std::vector<Position>::vector(&PosVector, &goblin->m_RevivePosVector);
    M_current = std::vector<Position>::end(&PosVector)._M_current;
    v8._M_current = std::vector<Position>::begin(&PosVector)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
      v8,
      (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
    nSize = std::vector<Position>::size(&PosVector);
    nFlush = 0;
    std::vector<CurrentData>::vector(&refresh);
    container = std::back_inserter<std::vector<CurrentData>>(&refresh).container;
    v10 = std::vector<CurrentData>::end(&goblin->m_RefreshMonsters)._M_current;
    v11._M_current = std::vector<CurrentData>::begin(&goblin->m_RefreshMonsters)._M_current;
    std::copy<__gnu_cxx::__normal_iterator<CurrentData const*,std::vector<CurrentData>>,std::back_insert_iterator<std::vector<CurrentData>>>(
      v11,
      (__gnu_cxx::__normal_iterator<const CurrentData*,std::vector<CurrentData> >)v10,
      (std::back_insert_iterator<std::vector<CurrentData> >)container);
    for ( nowCount = 0; nowCount < MonsterCount; ++nowCount )
    {
      mid = 0;
      if ( nFlush >= nSize )
        break;
      for ( i_0 = 0; ; ++i_0 )
      {
        v13 = i_0;
        if ( v13 >= std::vector<CurrentData>::size(&refresh) )
          break;
        if ( std::vector<CurrentData>::operator[](&refresh, i_0)->nValue > 0 )
        {
          mid = std::vector<CurrentData>::operator[](&refresh, i_0)->nId;
          v12 = std::vector<CurrentData>::operator[](&refresh, i_0);
          --v12->nValue;
          break;
        }
      }
      y = std::vector<Position>::operator[](&PosVector, nFlush)->y;
      x = std::vector<Position>::operator[](&PosVector, nFlush)->x;
      Map::GoblinAddMonster(this, nActivityId, mid, goblin->m_mapId, x, y);
      ++nFlush;
    }
    std::vector<CurrentData>::~vector(&refresh);
    std::vector<Position>::~vector(&PosVector);
  }
}


#####################################
void __cdecl Map::GoblinAddMonster(Map *const this, int32_t nActivityId, int32_t mid, int32_t mapId, int x, int y)
{
  CfgData *v6; // rax
  CfgData *v7; // rax
  CPoolManager *v8; // rax
  CfgMapMonster cfgmapmonster; // [rsp+20h] [rbp-60h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+40h] [rbp-40h] BYREF
  const CfgMonster *pMonster; // [rsp+60h] [rbp-20h]
  Monster *monster; // [rsp+68h] [rbp-18h]

  v6 = Answer::Singleton<CfgData>::instance();
  pMonster = CfgData::getMonster(v6, mid);
  if ( pMonster )
  {
    cfgmapmonster.id = 0;
    *(_DWORD *)&cfgmapmonster.hide = 0;
    cfgmapmonster.Day = 0;
    cfgmapmonster.mapid = Map::GetMapId(this);
    v7 = Answer::Singleton<CfgData>::instance();
    cfgmapmonster.monsterid = CfgData::GetMapMonsterId(v7);
    cfgmapmonster.x = x;
    cfgmapmonster.y = y;
    v8 = Answer::Singleton<CPoolManager>::instance();
    monster = CPoolManager::pop<Monster>(v8);
    if ( monster )
    {
      std::vector<AttrAddon>::vector(&vAttrAddon);
      Monster::init(monster, pMonster, &cfgmapmonster, MonsterState::MS_STAND, &vAttrAddon);
      std::vector<AttrAddon>::~vector(&vAttrAddon);
      Monster::SetActivityId(monster, nActivityId);
      (*((void (__fastcall **)(Map *const, Monster *, _QWORD, _QWORD))this->_vptr_Map + 28))(
        this,
        monster,
        (unsigned int)x,
        (unsigned int)y);
    }
  }
}


#####################################
void __cdecl Map::ActivityRefreshMonster(Map *const this, int32_t nActivityId, int32_t nTime, int32_t nIndex)
{
  int32_t v4; // eax
  unsigned int v5; // eax
  RefreshMonsterCfg *v6; // rax
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v8; // rax
  RefreshMonsterCfg *v9; // rax
  int32_t nCount; // eax
  int32_t nType; // eax
  int32_t v12; // ebx
  CfgData *v13; // rax
  CfgData *v14; // rax
  CPoolManager *v15; // rax
  int32_t v16; // eax
  int32_t nId; // ebx
  CfgData *v18; // rax
  Npc *v19; // rbx
  int v20; // ebx
  int32_t v21; // eax
  int32_t y; // r12d
  int32_t x; // edx
  int32_t v24; // ebx
  CfgData *v25; // rax
  Plant *v26; // rbx
  CfgMapPlant stu; // [rsp+20h] [rbp-110h] BYREF
  CfgMapMonster MapMonster; // [rsp+30h] [rbp-100h] BYREF
  std::vector<Position> PosVector; // [rsp+50h] [rbp-E0h] BYREF
  std::_List_iterator<RefreshMonsterCfg> it; // [rsp+70h] [rbp-C0h] BYREF
  RefreshMonsterCfgList m_RefreshCfgList; // [rsp+80h] [rbp-B0h] BYREF
  std::_List_iterator<RefreshMonsterCfg> __x; // [rsp+90h] [rbp-A0h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+A0h] [rbp-90h] BYREF
  int32_t nSize; // [rsp+BCh] [rbp-74h]
  int32_t NeedFreshSize; // [rsp+C0h] [rbp-70h]
  int32_t nFlush; // [rsp+C4h] [rbp-6Ch]
  CfgMonster *pMonster; // [rsp+C8h] [rbp-68h]
  int32_t nowCount; // [rsp+D0h] [rbp-60h]
  int32_t MonsterId; // [rsp+D4h] [rbp-5Ch]
  Monster *monster; // [rsp+D8h] [rbp-58h]
  CfgNpc *pCfgNpc; // [rsp+E0h] [rbp-50h]
  int32_t nowCount_0; // [rsp+ECh] [rbp-44h]
  Npc *npc; // [rsp+F0h] [rbp-40h]
  CfgPlant *pCfgPlant; // [rsp+F8h] [rbp-38h]
  int32_t nowCount_1; // [rsp+104h] [rbp-2Ch]
  Plant *plant; // [rsp+108h] [rbp-28h]

  v4 = (unsigned int)Answer::Singleton<CfgData>::instance();
  CfgData::GetRefreshMonsterCfgList((CfgData *const)&m_RefreshCfgList, v4);
  for ( it._M_node = std::list<RefreshMonsterCfg>::begin(&m_RefreshCfgList)._M_node;
        ;
        std::_List_iterator<RefreshMonsterCfg>::operator++(&it, 0) )
  {
    __x._M_node = std::list<RefreshMonsterCfg>::end(&m_RefreshCfgList)._M_node;
    if ( !std::_List_iterator<RefreshMonsterCfg>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nIndex != nIndex )
      continue;
    v5 = time(0);
    srand(v5);
    v6 = std::_List_iterator<RefreshMonsterCfg>::operator->(&it);
    std::vector<Position>::vector(&PosVector, &v6->vRevivePosVector);
    M_current = std::vector<Position>::end(&PosVector)._M_current;
    v8._M_current = std::vector<Position>::begin(&PosVector)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
      v8,
      (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
    nSize = std::vector<Position>::size(&PosVector);
    v9 = std::_List_iterator<RefreshMonsterCfg>::operator->(&it);
    if ( v9->nCount > nSize )
      nCount = nSize;
    else
      nCount = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nCount;
    NeedFreshSize = nCount;
    nFlush = 0;
    nType = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nType;
    if ( nType == 2 )
    {
      nId = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nId;
      v18 = Answer::Singleton<CfgData>::instance();
      pCfgNpc = CfgData::getNpc(v18, nId);
      for ( nowCount_0 = 0; nowCount_0 < NeedFreshSize; ++nowCount_0 )
      {
        if ( pCfgNpc )
        {
          v19 = (Npc *)operator new(0x4E8u);
          Npc::Npc(v19);
          npc = v19;
          if ( !v19 )
          {
            v20 = 0;
            goto LABEL_35;
          }
          v21 = Answer::DayTime::now();
          Npc::init(npc, pCfgNpc, nTime + v21);
          y = std::vector<Position>::operator[](&PosVector, nFlush)->y;
          x = std::vector<Position>::operator[](&PosVector, nFlush)->x;
          Map::addNpc(this, npc, x, y);
        }
        ++nFlush;
      }
      goto LABEL_34;
    }
    if ( nType == 3 )
    {
      v24 = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nId;
      v25 = Answer::Singleton<CfgData>::instance();
      pCfgPlant = CfgData::getPlant(v25, v24);
      for ( nowCount_1 = 0; ; ++nowCount_1 )
      {
        if ( nowCount_1 >= NeedFreshSize )
          goto LABEL_34;
        if ( pCfgPlant )
        {
          v26 = (Plant *)operator new(0xE0u);
          Plant::Plant(v26);
          plant = v26;
          if ( !v26 )
            continue;
          *(_QWORD *)&stu.mapid = 0;
          *(_QWORD *)&stu.x = 0;
          stu.mapid = Map::GetMapId(this);
          stu.plantid = pCfgPlant->id;
          stu.x = std::vector<Position>::operator[](&PosVector, nFlush)->x;
          stu.y = std::vector<Position>::operator[](&PosVector, nFlush)->y;
          Plant::init(plant, this, pCfgPlant, &stu, 0);
          Plant::setLifeTime(plant, nTime);
          Map::addPlant(this, plant);
        }
        ++nFlush;
      }
    }
    if ( nType != 1 )
    {
      v20 = 0;
      goto LABEL_35;
    }
    v12 = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nId;
    v13 = Answer::Singleton<CfgData>::instance();
    pMonster = CfgData::getMonster(v13, v12);
    for ( nowCount = 0; nowCount < NeedFreshSize; ++nowCount )
    {
      if ( pMonster )
      {
        v14 = Answer::Singleton<CfgData>::instance();
        MonsterId = CfgData::GetMapMonsterId(v14);
        memset(&MapMonster.mapid, 0, 24);
        MapMonster.id = MonsterId;
        MapMonster.mapid = Map::GetMapId(this);
        MapMonster.x = std::vector<Position>::operator[](&PosVector, nFlush)->x;
        MapMonster.y = std::vector<Position>::operator[](&PosVector, nFlush)->y;
        v15 = Answer::Singleton<CPoolManager>::instance();
        monster = CPoolManager::pop<Monster>(v15);
        if ( monster )
        {
          if ( pMonster )
          {
            std::vector<AttrAddon>::vector(&vAttrAddon);
            Monster::init(monster, pMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
            std::vector<AttrAddon>::~vector(&vAttrAddon);
            v16 = Answer::DayTime::now();
            Monster::SetLifeTime(monster, nTime + v16);
            (*((void (__fastcall **)(Map *const, Monster *, _QWORD, _QWORD))this->_vptr_Map + 28))(
              this,
              monster,
              (unsigned int)MapMonster.x,
              (unsigned int)MapMonster.y);
          }
        }
      }
      ++nFlush;
    }
LABEL_34:
    v20 = 1;
LABEL_35:
    std::vector<Position>::~vector(&PosVector);
    if ( !v20 )
      break;
  }
  std::list<RefreshMonsterCfg>::~list(&m_RefreshCfgList);
}


#####################################
bool __cdecl Map::HaveUnit(Map *const this, int32_t x, int32_t y)
{
  Player **v3; // rax
  Player **v4; // rax
  Monster **v7; // rax
  Monster **v8; // rax
  Monster **v9; // rax
  Plant **v11; // rax
  Plant **v12; // rax
  std::_List_iterator<Plant*> itplant; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<Monster*> itmonster; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<Player*> it; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+40h] [rbp-30h] BYREF
  std::_List_iterator<Monster*> v19; // [rsp+50h] [rbp-20h] BYREF
  std::_List_iterator<Plant*> v20; // [rsp+60h] [rbp-10h] BYREF

  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    v3 = std::_List_iterator<Player *>::operator*(&it);
    if ( StaticObj::getCurrentTile(*v3).x == x )
    {
      v4 = std::_List_iterator<Player *>::operator*(&it);
      if ( StaticObj::getCurrentTile(*v4).y == y )
        return 1;
    }
  }
  for ( itmonster._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&itmonster) )
  {
    v19._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&itmonster, &v19) )
      break;
    v7 = std::_List_iterator<Monster *>::operator*(&itmonster);
    if ( StaticObj::getCurrentTile(*v7).x == x )
    {
      v8 = std::_List_iterator<Monster *>::operator*(&itmonster);
      if ( StaticObj::getCurrentTile(*v8).y == y )
      {
        v9 = std::_List_iterator<Monster *>::operator*(&itmonster);
        if ( Unit::isAlive(*v9) )
          return 1;
      }
    }
  }
  for ( itplant._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node;
        ;
        std::_List_iterator<Plant *>::operator++(&itplant) )
  {
    v20._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
    if ( !std::_List_iterator<Plant *>::operator!=(&itplant, &v20) )
      break;
    v11 = std::_List_iterator<Plant *>::operator*(&itplant);
    if ( StaticObj::getCurrentTile(*v11).x == x )
    {
      v12 = std::_List_iterator<Plant *>::operator*(&itplant);
      if ( StaticObj::getCurrentTile(*v12).y == y )
        return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl Map::HaveMonster(Map *const this, int32_t x, int32_t y)
{
  Monster **v3; // rax
  Monster **v4; // rax
  std::_List_iterator<Monster*> itmonster; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( itmonster._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&itmonster) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&itmonster, &__x) )
      break;
    v3 = std::_List_iterator<Monster *>::operator*(&itmonster);
    if ( StaticObj::getCurrentTile(*v3).x == x )
    {
      v4 = std::_List_iterator<Monster *>::operator*(&itmonster);
      if ( StaticObj::getCurrentTile(*v4).y == y )
        return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl Map::AllPlayerBackCity(Map *const this)
{
  std::_List_iterator<Player*> it; // [rsp+10h] [rbp-40h] BYREF
  PlayerList playerListTmp; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  std::list<Player *>::list(&playerListTmp, &this->m_players);
  for ( it._M_node = std::list<Player *>::begin(&playerListTmp)._M_node; ; std::_List_iterator<Player *>::operator++(
                                                                             &it,
                                                                             0) )
  {
    __x._M_node = std::list<Player *>::end(&playerListTmp)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&it);
    if ( player )
      Player::OnBackCity(player, 1, 0);
  }
  std::list<Player *>::~list(&playerListTmp);
}


#####################################
int32_t __cdecl Map::GetMapPlayerSize(Map *const this)
{
  return std::list<Player *>::size(&this->m_players);
}


#####################################
int32_t __cdecl Map::GetAliveBossCount(Map *const this, int32_t nLevel)
{
  Monster **v2; // rax
  Monster **v3; // rax
  std::_List_iterator<Monster*> itMonst; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-4h]

  Count = 0;
  for ( itMonst._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&itMonst, 0) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&itMonst, &__x) )
      break;
    v2 = std::_List_iterator<Monster *>::operator*(&itMonst);
    if ( Unit::isAlive(*v2) )
    {
      if ( nLevel <= 0 )
      {
        ++Count;
      }
      else
      {
        v3 = std::_List_iterator<Monster *>::operator*(&itMonst);
        if ( (*((unsigned int (__fastcall **)(Monster *))(*v3)->_vptr_Entity + 9))(*v3) == nLevel )
          ++Count;
      }
    }
  }
  return Count;
}


#####################################
int32_t __cdecl Map::GetMapPlayerAliveSize(Map *const this)
{
  Player **v1; // rax
  std::_List_iterator<Player*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-4h]

  Count = 0;
  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&it, 0) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    v1 = std::_List_iterator<Player *>::operator*(&it);
    if ( Unit::isAlive(*v1) )
      ++Count;
  }
  return Count;
}


#####################################
bool __cdecl Map::NearNpc(Map *const this, int32_t NpcId, int32_t x, int32_t y, int32_t Diff)
{
  Npc **v5; // rax
  Npc **v6; // rax
  Npc **v7; // rax
  std::_List_iterator<Npc*> it; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<Npc*> __x; // [rsp+30h] [rbp-10h] BYREF
  int __b; // [rsp+38h] [rbp-8h] BYREF
  int __a; // [rsp+3Ch] [rbp-4h] BYREF

  for ( it._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it, 0) )
  {
    __x._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it, &__x) )
      break;
    v5 = std::_List_iterator<Npc *>::operator*(&it);
    if ( Npc::getNpcId(*v5) == NpcId )
    {
      v6 = std::_List_iterator<Npc *>::operator*(&it);
      __b = abs32(StaticObj::GetPosY(*v6) - y);
      v7 = std::_List_iterator<Npc *>::operator*(&it);
      __a = abs32(StaticObj::GetPosX(*v7) - x);
      if ( *std::max<int>(&__a, &__b) <= Diff )
        return 1;
    }
  }
  return 0;
}


