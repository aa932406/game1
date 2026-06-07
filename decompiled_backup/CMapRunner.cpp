// Decompiled methods for class: CMapRunner
// Source: gameserver.cc
// Total methods: 22

#####################################
void __cdecl CMapRunner::run(CMapRunner *const this)
{
  CTimer *v1; // rax
  int64_t Tick; // rax
  CTimer *v3; // rax
  int32_t Now; // eax
  CTimer *v5; // rax
  CMapRunner *v6; // rbx
  tm v7; // [rsp+0h] [rbp-80h] BYREF
  CMapRunner *thisa; // [rsp+48h] [rbp-38h]
  int64_t nStartTick; // [rsp+58h] [rbp-28h]
  int64_t nEndTick; // [rsp+60h] [rbp-20h]
  int32_t nUsedTick; // [rsp+6Ch] [rbp-14h]

  thisa = this;
  this->m_bRunning = 1;
  while ( thisa->m_bRunning )
  {
    nStartTick = Answer::DayTime::tick();
    v1 = Answer::Singleton<CTimer>::instance();
    Tick = CTimer::GetTick(v1);
    thisa->m_nTick = Tick;
    v3 = Answer::Singleton<CTimer>::instance();
    Now = CTimer::GetNow(v3);
    thisa->m_nNow = Now;
    v5 = Answer::Singleton<CTimer>::instance();
    v6 = thisa;
    CTimer::GetLocalNow(&v7, v5);
    v6->m_tmLocalNow = v7;
    CMapRunner::update(thisa);
    CMapRunner::checkMessage(thisa);
    nEndTick = Answer::DayTime::tick();
    nUsedTick = nEndTick - nStartTick;
    if ( (int)nEndTick - (int)nStartTick <= 200 )
      Answer::DayTime::sleep(10);
    else
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "MapRunner update used time = %d !!!\n", nUsedTick);
  }
}


#####################################
void __cdecl CMapRunner::Stop(CMapRunner *const this)
{
  this->m_bRunning = 0;
  Answer::Thread::join(this);
}


#####################################
void __cdecl CMapRunner::AddMap(CMapRunner *const this, Map *pMap)
{
  Map *pMapa; // [rsp+0h] [rbp-10h] BYREF
  CMapRunner *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  pMapa = pMap;
  std::list<Map *>::push_back(&this->m_maps, &pMapa);
}


#####################################
void __cdecl CMapRunner::DelMap(CMapRunner *const this, MapId_t nMapId)
{
  std::_List_iterator<Map*> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Map*> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<Map *>::begin(&this->m_maps)._M_node; ; std::_List_iterator<Map *>::operator++(&iter) )
  {
    __x._M_node = std::list<Map *>::end(&this->m_maps)._M_node;
    if ( !std::_List_iterator<Map *>::operator!=(&iter, &__x) )
      break;
    std::list<Map *>::erase(&this->m_maps, iter);
  }
}


#####################################
void __cdecl CMapRunner::PostMsg(
        CMapRunner *const this,
        GameMsgCode msgcode,
        void *ptr1,
        void *ptr2,
        int32_t iparam1,
        int32_t iparam2,
        void *ptr3)
{
  CPoolManager *v7; // rax
  GameMsg *msg; // [rsp+38h] [rbp-8h]

  v7 = Answer::Singleton<CPoolManager>::instance();
  msg = CPoolManager::pop<GameMsg>(v7);
  if ( msg )
  {
    msg->msgcode = msgcode;
    msg->ptr1 = ptr1;
    msg->ptr2 = ptr2;
    msg->ptr3 = ptr3;
    msg->iparam1 = iparam1;
    msg->iparam2 = iparam2;
    msg->effecttick = 0;
    Answer::SafeQueue<GameMsg *>::push(&this->m_msgQueue, msg);
  }
}


#####################################
void __cdecl CMapRunner::update(CMapRunner *const this)
{
  Map **v1; // rax
  std::_List_iterator<Map*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Map*> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<Map *>::begin(&this->m_maps)._M_node; ; std::_List_iterator<Map *>::operator++(&it) )
  {
    __x._M_node = std::list<Map *>::end(&this->m_maps)._M_node;
    if ( !std::_List_iterator<Map *>::operator!=(&it, &__x) )
      break;
    if ( *std::_List_iterator<Map *>::operator*(&it) )
    {
      v1 = std::_List_iterator<Map *>::operator*(&it);
      (*((void (__fastcall **)(Map *))(*v1)->_vptr_Map + 3))(*v1);
    }
  }
}


#####################################
void __cdecl CMapRunner::checkMessage(CMapRunner *const this)
{
  CPoolManager *v1; // rax
  GameMsg *msg; // [rsp+18h] [rbp-8h]

  while ( 1 )
  {
    msg = Answer::SafeQueue<GameMsg *>::pop(&this->m_msgQueue);
    if ( !msg )
      break;
    CMapRunner::dealMessage(this, msg);
    v1 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<GameMsg>(v1, msg);
  }
}


#####################################
void __cdecl CMapRunner::dealMessage(CMapRunner *const this, GameMsg *msg)
{
  if ( msg )
  {
    switch ( msg->msgcode )
    {
      case GameMsgCode::GMC_PLAYER_ENTER_MAP:
        CMapRunner::onPlayerEnterMap(this, (Player *)msg->ptr1, (Map *)msg->ptr2, msg->iparam1, msg->iparam2);
        break;
      case GameMsgCode::GMC_PLAYER_LEAVE_MAP:
        CMapRunner::onPlayerLeaveMap(this, (Player *)msg->ptr1, (Map *)msg->ptr2, msg->iparam1, msg->iparam2);
        break;
      case GameMsgCode::GMC_ADD_DUNGEON:
        CMapRunner::onAddDungeon(this, (Dungeon *)msg->ptr1);
        break;
      case GameMsgCode::GMC_DEL_DUNGEON:
        CMapRunner::onDelDungeon(this, (Dungeon *)msg->ptr1);
        break;
      case GameMsgCode::GMC_PLAYER_LOGOUT:
        CMapRunner::onPlayerLogout(this, (Player *)msg->ptr1);
        break;
      case GameMsgCode::GMC_ACTIVITY_START:
        CMapRunner::onActivityStart(this, (CActivityMap *)msg->ptr1, (CActivity *)msg->ptr2);
        break;
      case GameMsgCode::GMC_CITY_STAR:
        CMapRunner::onStarCityWar(this, (Map *)msg->ptr1);
        goto LABEL_12;
      case GameMsgCode::GMC_GOBLIN_ACTIVITY:
        CMapRunner::onStartGoblinRuqin(this, (Map *)msg->ptr1, (CActivity *)msg->ptr2, msg->iparam1);
        break;
      case GameMsgCode::GMC_ACTIVITY_STOP:
        CMapRunner::onActivityStop(this, (CActivityMap *)msg->ptr1, (CActivity *)msg->ptr2);
        break;
      case GameMsgCode::GMC_ADD_TERRITORY:
LABEL_12:
        CMapRunner::onAddTerritory(this, (CTerritory *)msg->ptr1);
        break;
      case GameMsgCode::GMC_DEL_TERRITORY:
        CMapRunner::onDelTerritory(this, (CTerritory *)msg->ptr1);
        break;
      case GameMsgCode::GMC_ADD_WORLD_BOSS_NPC:
        CMapRunner::onStartActivityWorldBoss(this, (Map *)msg->ptr1, (CActivity *)msg->ptr2, msg->iparam1);
        break;
      case GameMsgCode::GMC_ADD_OBJ:
        CMapRunner::onStartRefreshMonster(this, (Map *)msg->ptr1, (CActivity *)msg->ptr2, msg->iparam1, msg->iparam2);
        break;
      default:
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "Kingdom::checkMessage with unknown msg code %d\n",
          msg->msgcode);
        break;
    }
  }
}


#####################################
void __cdecl CMapRunner::onPlayerEnterMap(CMapRunner *const this, Player *pPlayer, Map *pMap, int32_t x, int32_t y)
{
  int32_t RunnerId; // ebx
  int GateIndex; // ebx
  CharId_t Cid; // rax

  if ( pPlayer )
  {
    if ( pMap )
    {
      RunnerId = Map::GetRunnerId(pMap);
      if ( RunnerId == CMapRunner::GetId(this) )
      {
        GateIndex = Player::getGateIndex(pPlayer);
        Cid = Player::getCid(pPlayer);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_DEBUG,
          "CMapRunner::onPlayerEnterMap with player = %p, cid = %lld, cgindex = %d\n",
          pPlayer,
          Cid,
          GateIndex);
        (*((void (__fastcall **)(Map *, Player *, _QWORD, _QWORD))pMap->_vptr_Map + 15))(
          pMap,
          pPlayer,
          (unsigned int)x,
          (unsigned int)y);
      }
    }
  }
}


#####################################
void __cdecl CMapRunner::onPlayerLeaveMap(CMapRunner *const this, Player *pPlayer, Map *pMap, int32_t x, int32_t y)
{
  int GateIndex; // ebx
  CharId_t Cid; // rax
  int32_t RunnerId; // ebx
  MapManager *v8; // rax

  if ( pPlayer )
  {
    if ( pMap )
    {
      GateIndex = Player::getGateIndex(pPlayer);
      Cid = Player::getCid(pPlayer);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_DEBUG,
        "CMapRunner::onPlayerLeaveMap with player = %p, cid = %lld, cgindex = %d\n",
        pPlayer,
        Cid,
        GateIndex);
      RunnerId = Map::GetRunnerId(pMap);
      v8 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v8, RunnerId, GameMsgCode::GMC_PLAYER_ENTER_MAP, pPlayer, pMap, x, y, 0);
    }
  }
}


#####################################
void __cdecl CMapRunner::onAddDungeon(CMapRunner *const this, Dungeon *pDungeon)
{
  MapManager *v2; // rax
  Map *__x; // [rsp+18h] [rbp-8h] BYREF

  if ( pDungeon )
  {
    __x = pDungeon;
    std::list<Map *>::push_back(&this->m_maps, &__x);
    v2 = Answer::Singleton<MapManager>::instance();
    MapManager::AddDungeon(v2, pDungeon);
  }
}


#####################################
void __cdecl CMapRunner::onDelDungeon(CMapRunner *const this, Dungeon *pDungeon)
{
  int32_t Id; // ebx
  MapManager *v3; // rax
  std::_List_iterator<Map*> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Map*> __x; // [rsp+20h] [rbp-20h] BYREF

  if ( pDungeon )
  {
    for ( iter._M_node = std::list<Map *>::begin(&this->m_maps)._M_node; ; std::_List_iterator<Map *>::operator++(&iter) )
    {
      __x._M_node = std::list<Map *>::end(&this->m_maps)._M_node;
      if ( !std::_List_iterator<Map *>::operator!=(&iter, &__x) )
        break;
      if ( *std::_List_iterator<Map *>::operator*(&iter) == pDungeon )
      {
        std::list<Map *>::erase(&this->m_maps, iter);
        break;
      }
    }
    Id = Dungeon::GetId(pDungeon);
    v3 = Answer::Singleton<MapManager>::instance();
    MapManager::DelDungeon(v3, Id);
  }
}


#####################################
void __cdecl CMapRunner::onPlayerLogout(CMapRunner *const this, Player *pPlayer)
{
  int GateIndex; // r12d
  int ConnId; // ebx
  CharId_t Cid; // rax
  GameService *v5; // rax

  if ( pPlayer )
  {
    GateIndex = Player::getGateIndex(pPlayer);
    ConnId = Player::getConnId(pPlayer);
    Cid = Player::getCid(pPlayer);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_DEBUG,
      "CMapRunner::onPlayerLogout with player = %p cid = %lld, connid=%d, cgindex = %d\n",
      pPlayer,
      Cid,
      ConnId,
      GateIndex);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::onPlayerLogout(v5, pPlayer);
  }
}


#####################################
void __cdecl CMapRunner::onAddTerritory(CMapRunner *const this, CTerritory *pTerritory)
{
  MapManager *v2; // rax
  Map *__x; // [rsp+18h] [rbp-8h] BYREF

  if ( pTerritory )
  {
    __x = pTerritory;
    std::list<Map *>::push_back(&this->m_maps, &__x);
    v2 = Answer::Singleton<MapManager>::instance();
    MapManager::AddTerritory(v2, pTerritory);
  }
}


#####################################
void __cdecl CMapRunner::onDelTerritory(CMapRunner *const this, CTerritory *pTerritory)
{
  FamilyId_t TerritoryId; // rbx
  MapManager *v3; // rax
  std::_List_iterator<Map*> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Map*> __x; // [rsp+20h] [rbp-20h] BYREF

  if ( pTerritory )
  {
    for ( iter._M_node = std::list<Map *>::begin(&this->m_maps)._M_node; ; std::_List_iterator<Map *>::operator++(&iter) )
    {
      __x._M_node = std::list<Map *>::end(&this->m_maps)._M_node;
      if ( !std::_List_iterator<Map *>::operator!=(&iter, &__x) )
        break;
      if ( *std::_List_iterator<Map *>::operator*(&iter) == pTerritory )
      {
        std::list<Map *>::erase(&this->m_maps, iter);
        break;
      }
    }
    TerritoryId = CTerritory::GetTerritoryId(pTerritory);
    v3 = Answer::Singleton<MapManager>::instance();
    MapManager::DelTerritory(v3, TerritoryId);
  }
}


#####################################
void __cdecl CMapRunner::onActivityStart(CMapRunner *const this, CActivityMap *pMap, CActivity *pActivity)
{
  if ( pMap )
  {
    if ( pActivity )
      CActivityMap::onActivityStart(pMap, pActivity);
  }
}


#####################################
void __cdecl CMapRunner::onActivityStop(CMapRunner *const this, CActivityMap *pMap, CActivity *pActivity)
{
  if ( pMap )
  {
    if ( pActivity )
      CActivityMap::onActivityStop(pMap, pActivity);
  }
}


#####################################
void __cdecl CMapRunner::onStartGoblinRuqin(
        CMapRunner *const this,
        Map *pMap,
        CActivity *pActivity,
        int32_t RefreshCount)
{
  int32_t v4; // edx
  int32_t Id; // ecx

  if ( pMap )
  {
    if ( RefreshCount )
    {
      Id = CActivity::GetId(pActivity);
      Map::OnStartGoblinRuQin(pMap, Id, RefreshCount);
    }
    else
    {
      v4 = CActivity::GetId(pActivity);
      Map::cleanActivityMonster(pMap, v4);
    }
  }
}


#####################################
void __cdecl CMapRunner::onStartRefreshMonster(
        CMapRunner *const this,
        Map *pMap,
        CActivity *pActivity,
        int32_t nTime,
        int32_t nIndex)
{
  int32_t Id; // ebx

  if ( pMap )
  {
    Id = CActivity::GetId(pActivity);
    Map::ActivityRefreshMonster(pMap, Id, nTime, nIndex);
  }
}


#####################################
void __cdecl CMapRunner::onStartActivityWorldBoss(
        CMapRunner *const this,
        Map *pMap,
        CActivity *pActivity,
        int32_t Time)
{
  Npc *v4; // rbx
  CfgData *v5; // rax
  int32_t v6; // edx
  CfgNpc *pCfgNpc; // [rsp+28h] [rbp-28h]

  if ( pMap )
  {
    v4 = (Npc *)operator new(0x4E8u);
    Npc::Npc(v4);
    if ( v4 )
    {
      v5 = Answer::Singleton<CfgData>::instance();
      pCfgNpc = CfgData::getNpc(v5, 3018);
      if ( pCfgNpc )
      {
        v6 = Time + CMapRunner::getNow(this);
        Npc::init(v4, pCfgNpc, v6);
        Map::addNpc(pMap, v4, pCfgNpc->x, pCfgNpc->y);
      }
    }
  }
}


#####################################
void __cdecl CMapRunner::onStarCityWar(CMapRunner *const this, Map *pMap)
{
  if ( pMap )
    Map::AllPlayerBackCity(pMap);
}


#####################################
void __cdecl CMapRunner::~CMapRunner(CMapRunner *const this)
{
  CMapRunner::~CMapRunner(this);
  operator delete(this);
}


