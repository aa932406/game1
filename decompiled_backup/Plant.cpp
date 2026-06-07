// Decompiled methods for class: Plant
// Source: gameserver.cc
// Total methods: 21

#####################################
void __cdecl Plant::~Plant(Plant *const this)
{
  Plant::~Plant(this);
  operator delete(this);
}


#####################################
void __cdecl Plant::init(
        Plant *const this,
        Map *pMap,
        const CfgPlant *const cfgPlant,
        const CfgMapPlant *const cfgMapPlant,
        Monster *pBoss)
{
  Position v7; // [rsp+30h] [rbp-20h] BYREF

  CfgPlant::operator=(&this->m_cfgPlant, cfgPlant);
  this->m_cfgMapPlant = *cfgMapPlant;
  this->m_pSummonBoss = pBoss;
  this->m_pMap = pMap;
  Position::Position(&v7, this->m_cfgMapPlant.x, this->m_cfgMapPlant.y);
  this->m_currentTile = v7;
  this->m_currentPos = Map::tileToPixel(this->m_cfgMapPlant.x, this->m_cfgMapPlant.y);
  this->m_gather = 0;
  this->m_gatherTick = 0;
  this->m_isCorpse = 0;
  this->m_isHide = 0;
  this->m_corpseTick = 0;
  this->m_whoCanPlant = 0;
  this->m_nLifeTime = 0;
  this->m_Camp = 0;
}


#####################################
void __cdecl Plant::reset(Plant *const this)
{
  StaticObj::reset(this);
  this->m_gather = 0;
  this->m_gatherTick = 0;
  this->m_isCorpse = 0;
  this->m_isHide = 0;
  this->m_corpseTick = 0;
  this->m_whoCanPlant = 0;
  this->m_pSummonBoss = 0;
  this->m_Camp = 0;
}


#####################################
void __cdecl Plant::refresh(Plant *const this)
{
  tm localNow; // [rsp+10h] [rbp-40h] BYREF
  int64_t curTick; // [rsp+48h] [rbp-8h]

  if ( this->m_pMap )
  {
    Map::getLocalNow(&localNow, this->m_pMap);
    if ( localNow.tm_hour < this->m_cfgPlant.start_hour || localNow.tm_hour > this->m_cfgPlant.end_hour )
    {
      this->m_isHide = 1;
      Plant::broadcastRemove(this);
    }
    else if ( this->m_isCorpse && this->m_cfgPlant.revive_time > 0 )
    {
      curTick = Map::getTick(this->m_pMap);
      if ( !this->m_isHide && curTick - this->m_corpseTick >= this->m_cfgPlant.hide_time )
      {
        this->m_isHide = 1;
        Plant::broadcastRemove(this);
        if ( this->m_cfgPlant.revive_skin > 0 )
          Map::broadcastIntoMap(this->m_pMap, this);
      }
      if ( !this->m_pSummonBoss && curTick - this->m_corpseTick >= this->m_cfgPlant.revive_time )
        (*((void (__fastcall **)(Plant *const))this->_vptr_Entity + 10))(this);
    }
    else if ( !this->m_pSummonBoss && this->m_isHide )
    {
      (*((void (__fastcall **)(Plant *const))this->_vptr_Entity + 10))(this);
    }
  }
}


#####################################
int32_t __cdecl Plant::GetReviveTime(Plant *const this)
{
  __int64 v1; // rax
  __int64 revive_time; // rbx
  int64_t m_corpseTick; // r12

  if ( this->m_cfgPlant.revive_skin > 0 )
  {
    if ( this->m_isCorpse )
    {
      revive_time = this->m_cfgPlant.revive_time;
      m_corpseTick = this->m_corpseTick;
      return (revive_time + m_corpseTick - Map::getTick(this->m_pMap)) / 1000;
    }
    else
    {
      LODWORD(v1) = 0;
    }
  }
  else
  {
    LODWORD(v1) = 0;
  }
  return v1;
}


#####################################
int32_t __cdecl Plant::onBeginGather(Plant *const this, Player *player)
{
  int32_t TaskId; // ebx
  ChrTask *Task; // rax
  bool v6; // al
  CExtCharFamily *CharFamily; // rax
  char v8; // al
  int32_t Record; // ebx
  CFestivalActivity *v10; // rax
  int32_t v11; // ebx
  CFestivalActivity *v12; // rax
  CharId_t m_gather; // rbx
  int64_t Tick; // rdx

  if ( !this->m_pMap || !player || Plant::isCorpse(this) )
    return 10002;
  if ( this->m_cfgPlant.TaskId > 0 )
  {
    TaskId = this->m_cfgPlant.TaskId;
    Task = Player::GetTask(player);
    if ( ChrTask::GetTaskState(Task, TaskId) != 3 )
      goto LABEL_28;
  }
  v6 = Plant::GetPlantType(this) == 4 && Player::getRecord(player, 1923) > 0;
  if ( v6
    || (Plant::GetPlantType(this) != 6
     || (CharFamily = Player::GetCharFamily(player), CExtCharFamily::GetHoeId(CharFamily) > 0)
      ? (v8 = 0)
      : (v8 = 1),
        v8
     || Plant::GetPlantType(this) == 3 && Player::getRecord(player, 2086) > 19
     || Plant::GetPlantType(this) == 9
     && (Record = Player::getRecord(player, 2119),
         v10 = Answer::Singleton<CFestivalActivity>::instance(),
         Record >= CFestivalActivity::GetPlantTimes(v10))
     || Plant::GetPlantType(this) == 10
     && (v11 = Player::getRecord(player, 2124),
         v12 = Answer::Singleton<CFestivalActivity>::instance(),
         v11 >= CFestivalActivity::GetPlantTimes2(v12))) )
  {
LABEL_28:
    Player::sendEndGather(player, 10019);
    return 10002;
  }
  if ( this->m_gather )
  {
    m_gather = this->m_gather;
    if ( m_gather != Player::getCid(player) )
    {
      if ( Map::getTick(this->m_pMap) - this->m_gatherTick <= this->m_cfgPlant.gather_time + 2000 )
      {
        Player::sendEndGather(player, 10019);
        return 10019;
      }
      this->m_gather = Player::getCid(player);
      this->m_gatherTick = Map::getTick(this->m_pMap);
      Plant::BroadcastChange(this);
    }
  }
  if ( this->m_cfgPlant.item_cost && !Player::hasItem(player, this->m_cfgPlant.item_cost, 1, 1) )
    return 10002;
  if ( this->m_cfgPlant.revive_time > 0 || Plant::GetPlantType(this) == 6 )
  {
    this->m_gather = Player::getCid(player);
    this->m_gatherTick = Map::getTick(this->m_pMap);
    Plant::BroadcastChange(this);
    if ( Plant::GetPlantType(this) == 6 )
      goto LABEL_51;
  }
  else if ( !this->m_cfgPlant.revive_time )
  {
LABEL_51:
    Tick = Map::getTick(this->m_pMap);
    Player::SetStartGather(player, Tick);
  }
  return 0;
}


#####################################
int32_t __cdecl Plant::onEndGather(Plant *const this, Player *player)
{
  int64_t Tick; // rbx
  int32_t EventMaxRate; // ebx
  Answer::Random *v6; // rax
  CfgPlantEvent *v7; // rax
  int32_t EventId; // edx
  CfgPlantEvent *v9; // rax
  Monster *m_pSummonBoss; // r13
  Map *m_pMap; // r12
  int32_t BossId; // ebx
  CWorldBoss *v13; // rax
  int32_t id; // ebx
  ChrTask *Task; // rax
  int32_t v16; // edx
  int32_t v17; // edx
  int32_t v18; // edx
  __gnu_cxx::__normal_iterator<CfgPlantEvent*,std::vector<CfgPlantEvent> > it; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<CfgPlantEvent*,std::vector<CfgPlantEvent> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  int32_t roll; // [rsp+2Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( this->m_cfgPlant.revive_time <= 0 )
  {
    if ( !this->m_cfgPlant.revive_time )
    {
      Tick = Map::getTick(this->m_pMap);
      if ( Tick - Player::GetStartGather(player) < this->m_cfgPlant.gather_time )
        goto LABEL_5;
    }
  }
  else if ( Map::getTick(this->m_pMap) - this->m_gatherTick < this->m_cfgPlant.gather_time )
  {
LABEL_5:
    Plant::BreakGather(this);
    Player::SetPlantState(player, 0);
    return 10002;
  }
  if ( this->m_cfgPlant.item_cost && !Player::hasItem(player, this->m_cfgPlant.item_cost, 1, 1) )
  {
    Player::SetPlantState(player, 0);
    Plant::BreakGather(this);
    return 10002;
  }
  else
  {
    EventMaxRate = this->m_cfgPlant.EventMaxRate;
    v6 = Answer::Singleton<Answer::Random>::instance();
    roll = Answer::Random::generate(v6, 1, EventMaxRate);
    for ( it._M_current = std::vector<CfgPlantEvent>::begin(&this->m_cfgPlant.Events)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgPlantEvent *,std::vector<CfgPlantEvent>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgPlantEvent>::end(&this->m_cfgPlant.Events)._M_current;
      if ( !__gnu_cxx::operator!=<CfgPlantEvent *,std::vector<CfgPlantEvent>>(&it, &__rhs) )
        break;
      v7 = __gnu_cxx::__normal_iterator<CfgPlantEvent *,std::vector<CfgPlantEvent>>::operator->(&it);
      if ( v7->Probability >= roll )
      {
        EventId = __gnu_cxx::__normal_iterator<CfgPlantEvent *,std::vector<CfgPlantEvent>>::operator->(&it)->EventId;
        if ( Plant::PlantEvent(this, player, EventId) )
        {
          Plant::BreakGather(this);
          Player::SetPlantState(player, 0);
          return 10002;
        }
        break;
      }
      v9 = __gnu_cxx::__normal_iterator<CfgPlantEvent *,std::vector<CfgPlantEvent>>::operator->(&it);
      roll -= v9->Probability;
    }
    if ( this->m_cfgPlant.revive_time > 0 )
    {
      this->m_gather = 0;
      this->m_gatherTick = 0;
      this->m_isCorpse = 1;
      this->m_corpseTick = Map::getTick(this->m_pMap);
      if ( this->m_cfgPlant.hide_time <= 0 )
        Plant::broadcastRemove(this);
      else
        Plant::BroadcastGathered(this);
      Player::sendEndGather(player, 0);
    }
    if ( Plant::GetPlantType(this) == 6 )
    {
      this->m_gather = 0;
      this->m_gatherTick = 0;
      Plant::BroadcastChange(this);
    }
    if ( this->m_pSummonBoss )
    {
      m_pSummonBoss = this->m_pSummonBoss;
      m_pMap = this->m_pMap;
      BossId = Monster::getBossId(m_pSummonBoss);
      v13 = Answer::Singleton<CWorldBoss>::instance();
      CWorldBoss::OnBossSummon(v13, BossId, m_pMap, m_pSummonBoss);
      Monster::OnRevive(this->m_pSummonBoss);
    }
    id = this->m_cfgPlant.id;
    Task = Player::GetTask(player);
    ChrTask::updateTaskPlant(Task, id);
    if ( Plant::GetPlantType(this) == 3 )
    {
      v16 = Player::getRecord(player, 2086) + 1;
      Player::updateRecord(player, 2086, v16);
    }
    if ( Plant::GetPlantType(this) == 4 )
      Player::UpdateCycleTowerState(player, CYCLE_TOWER_ENVET_TYPE::CTET_OPEN_BOX);
    if ( Plant::GetPlantType(this) == 9 )
    {
      v17 = Player::getRecord(player, 2119) + 1;
      Player::updateRecord(player, 2119, v17);
    }
    if ( Plant::GetPlantType(this) == 10 )
    {
      v18 = Player::getRecord(player, 2124) + 1;
      Player::updateRecord(player, 2124, v18);
    }
    return 0;
  }
}


#####################################
int32_t __cdecl Plant::PlantEvent(Plant *const this, Player *pPlayer, int32_t EventId)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  CExtCharFamily *CharFamily; // rax
  int v6; // r12d
  MemChrBag *v7; // rax
  CExtCharBag *Bag; // rax
  CharId_t Cid; // r13
  int8_t ConnId; // r12
  DBService *v11; // rax
  CActivityMap *v12; // rax
  CActivityMap *v13; // rax
  Dungeon *v14; // rax
  int v15; // r12d
  size_t v16; // rax
  const char *v17; // rax
  CExtCharCarrier *CharCarrier; // rax
  int8_t v19; // bl
  GameService *v20; // rax
  CharId_t v21; // rax
  uint32_t WOffset; // eax
  int8_t v23; // bl
  GameService *v24; // rax
  DropItem item; // [rsp+50h] [rbp-170h] BYREF
  Position pos; // [rsp+80h] [rbp-140h] BYREF
  CDropItemGroup dropItemGroup; // [rsp+90h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it_0; // [rsp+A0h] [rbp-120h] BYREF
  DropItemVector dropItems; // [rsp+B0h] [rbp-110h] BYREF
  MemChrBagVector ItemVector_0; // [rsp+D0h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+F0h] [rbp-D0h] BYREF
  MemChrBagVector ItemVector; // [rsp+100h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+120h] [rbp-A0h] BYREF
  std::string Param; // [rsp+130h] [rbp-90h] BYREF
  char v37; // [rsp+13Fh] [rbp-81h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v38; // [rsp+140h] [rbp-80h] BYREF
  std::string dropper; // [rsp+150h] [rbp-70h] BYREF
  std::string val; // [rsp+160h] [rbp-60h] BYREF
  CfgPlantEventEffect *pPlantEvent; // [rsp+168h] [rbp-58h]
  int32_t Rate; // [rsp+174h] [rbp-4Ch]
  CActivityMap *pAactivityMap; // [rsp+178h] [rbp-48h]
  CActivityMap *pAactivityMap_0; // [rsp+180h] [rbp-40h]
  Dungeon *pDungeon; // [rsp+188h] [rbp-38h]
  int32_t nId; // [rsp+194h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+198h] [rbp-28h]

  if ( !this->m_pMap || !pPlayer )
    return 2;
  v4 = Answer::Singleton<CfgData>::instance();
  pPlantEvent = CfgData::GetPlantEvent(v4, EventId);
  if ( !pPlantEvent )
    return 2;
  switch ( pPlantEvent->EventType )
  {
    case 1:
      CItemHelper::parseItemVectorString(&ItemVector, &pPlantEvent->EventEffect);
      if ( Plant::GetPlantType(this) != 6 )
        goto LABEL_13;
      CharFamily = Player::GetCharFamily(pPlayer);
      Rate = CExtCharFamily::EndMining(CharFamily);
      if ( Rate > 0 )
      {
        for ( it._M_current = std::vector<MemChrBag>::begin(&ItemVector)._M_current;
              ;
              __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0) )
        {
          __rhs._M_current = std::vector<MemChrBag>::end(&ItemVector)._M_current;
          if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
            break;
          v7 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
          v7->itemCount *= Rate;
        }
LABEL_13:
        if ( std::vector<MemChrBag>::size(&ItemVector) )
        {
          Bag = Player::GetBag(pPlayer);
          if ( CExtCharBag::AddItem(Bag, &ItemVector, ITEM_CHANGE_REASON::ICR_PLANT_GET) )
          {
            if ( Plant::GetPlantType(this) != 6 )
              Plant::SendGainItem(this, pPlayer, &ItemVector);
          }
          else
          {
            std::allocator<char>::allocator(&v37);
            std::string::string(&Param, &unk_8E91CF);
            Cid = Player::getCid(pPlayer);
            ConnId = Player::getConnId(pPlayer);
            v11 = Answer::Singleton<DBService>::instance();
            DBService::OnSendSysMail(v11, ConnId, Cid, 6216, &ItemVector, ITEM_CHANGE_REASON::ICR_PLANT_GET, &Param, 0);
            std::string::~string(&Param);
            std::allocator<char>::~allocator(&v37);
          }
        }
        v6 = 1;
      }
      else
      {
        v3 = 2;
        v6 = 0;
      }
      std::vector<MemChrBag>::~vector(&ItemVector);
      if ( v6 )
        goto LABEL_49;
      break;
    case 2:
      if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap) )
      {
        v12 = this->m_pMap
            ? (CActivityMap *)__dynamic_cast(
                                this->m_pMap,
                                (const struct __class_type_info *)&`typeinfo for'Map,
                                (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                0)
            : 0LL;
        pAactivityMap = v12;
        if ( v12 )
          (*((void (__fastcall **)(CActivityMap *, std::string *))pAactivityMap->_vptr_Map + 29))(
            pAactivityMap,
            &pPlantEvent->EventEffect);
      }
      goto LABEL_49;
    case 3:
      if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap) )
      {
        if ( this->m_pMap )
          v13 = (CActivityMap *)__dynamic_cast(
                                  this->m_pMap,
                                  (const struct __class_type_info *)&`typeinfo for'Map,
                                  (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                  0);
        else
          v13 = 0;
        pAactivityMap_0 = v13;
        if ( v13 )
          CActivityMap::generateMonster(pAactivityMap_0, &pPlantEvent->EventEffect);
      }
      else if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
      {
        v14 = this->m_pMap
            ? (Dungeon *)__dynamic_cast(
                           this->m_pMap,
                           (const struct __class_type_info *)&`typeinfo for'Map,
                           (const struct __class_type_info *)&`typeinfo for'Dungeon,
                           0)
            : 0LL;
        pDungeon = v14;
        if ( v14 )
          Dungeon::generateMonster(pDungeon, &pPlantEvent->EventEffect, 0);
      }
      goto LABEL_49;
    case 4:
      CItemHelper::parseItemVectorString(&ItemVector_0, &pPlantEvent->EventEffect);
      if ( std::vector<MemChrBag>::empty(&ItemVector_0) )
      {
        v3 = 2;
        v15 = 0;
      }
      else
      {
        std::vector<DropItem>::vector(&dropItems);
        v16 = std::vector<MemChrBag>::size(&ItemVector_0);
        std::vector<DropItem>::reserve(&dropItems, v16);
        for ( it_0._M_current = std::vector<MemChrBag>::begin(&ItemVector_0)._M_current;
              ;
              __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it_0, 0) )
        {
          v38._M_current = std::vector<MemChrBag>::end(&ItemVector_0)._M_current;
          if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it_0, &v38) )
            break;
          memset(&item, 0, sizeof(item));
          item.itemId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it_0)->itemId;
          item.itemClass = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it_0)->itemClass;
          item.bindType = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it_0)->bind;
          item.itemCount = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it_0)->itemCount;
          std::vector<DropItem>::push_back(&dropItems, &item);
        }
        CDropItemGroup::CDropItemGroup(&dropItemGroup);
        Position::Position(&pos, this->m_cfgMapPlant.x, this->m_cfgMapPlant.y);
        Player::getName((const Player *const)&dropper);
        CDropItemGroup::init(
          &dropItemGroup,
          0,
          this->m_pMap,
          &pos,
          pPlayer,
          6,
          this->m_cfgPlant.id,
          &dropItems,
          &dropper,
          0,
          0,
          0);
        std::string::~string(&dropper);
        Map::addDropItemGroup(this->m_pMap, &dropItemGroup);
        CDropItemGroup::~CDropItemGroup(&dropItemGroup);
        std::vector<DropItem>::~vector(&dropItems);
        v15 = 1;
      }
      std::vector<MemChrBag>::~vector(&ItemVector_0);
      if ( v15 )
        goto LABEL_49;
      return v3;
    case 5:
      v17 = (const char *)std::string::c_str(&pPlantEvent->EventEffect);
      nId = atoi(v17);
      if ( nId > 0 )
      {
        CharCarrier = Player::GetCharCarrier(pPlayer);
        CExtCharCarrier::EnterCarrier(CharCarrier, nId);
      }
      goto LABEL_49;
    default:
LABEL_49:
      if ( pPlantEvent->GongGaoId > 0 )
      {
        v19 = Player::getConnId(pPlayer);
        v20 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v20, v19, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( packet )
        {
          Answer::NetPacket::writeInt32(packet, pPlantEvent->GongGaoId);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          v21 = Player::getCid(pPlayer);
          Answer::NetPacket::writeInt64(packet, v21);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v23 = Player::getConnId(pPlayer);
          v24 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v24, v23, packet);
        }
      }
      v3 = 0;
      break;
  }
  return v3;
}


#####################################
void __cdecl Plant::SendGainItem(Plant *const this, Player *pPlayer, const MemChrBagVector *const vItem)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int64_t v5; // rax
  const MemChrBag *v6; // rax
  const MemChrBag *v7; // rax
  const MemChrBag *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > it; // [rsp+20h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+30h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+40h] [rbp-20h]
  int32_t nSize; // [rsp+4Ch] [rbp-14h]

  ConnId = Player::getConnId(pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE1u);
  if ( packet )
  {
    v5 = (*((__int64 (__fastcall **)(Plant *const))this->_vptr_Entity + 2))(this);
    Answer::NetPacket::writeInt64(packet, v5);
    nSize = std::vector<MemChrBag>::size(vItem);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_current = std::vector<MemChrBag>::begin(vItem)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<MemChrBag>::end(vItem)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&it, &__rhs) )
        break;
      v6 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
      Answer::NetPacket::writeInt8(packet, v6->itemClass);
      v7 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v7->itemId);
      v8 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v8->itemCount);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(pPlayer);
    v11 = Player::getConnId(pPlayer);
    v12 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v12, v11, GateIndex, packet);
  }
}


#####################################
int32_t __cdecl Plant::onBreakGather(Plant *const this, Player *player)
{
  if ( !this->m_pMap || !player )
    return 10002;
  Plant::BreakGather(this);
  return 0;
}


#####################################
void __cdecl Plant::BreakGather(Plant *const this)
{
  this->m_gather = 0;
  this->m_gatherTick = 0;
  Plant::BroadcastChange(this);
}


#####################################
bool __cdecl Plant::IsShow(const Plant *const this)
{
  if ( this->m_cfgPlant.revive_skin > 0 )
    return 1;
  if ( this->m_cfgPlant.hide_time <= 0 )
  {
    if ( this->m_isCorpse )
      return 0;
    if ( this->m_isHide )
      return 0;
  }
  else if ( this->m_isHide )
  {
    return 0;
  }
  return 1;
}


#####################################
bool __cdecl Plant::appendInfo(Plant *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  int64_t v4; // rdx
  int32_t ReviveTime; // edx

  if ( !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  v4 = (*((__int64 (__fastcall **)(Plant *const))this->_vptr_Entity + 2))(this);
  Answer::NetPacket::writeInt64(packet, v4);
  Answer::NetPacket::writeInt32(packet, this->m_cfgPlant.id);
  Answer::NetPacket::writeInt64(packet, this->m_gather);
  Answer::NetPacket::writeInt16(packet, this->m_cfgMapPlant.x);
  Answer::NetPacket::writeInt16(packet, this->m_cfgMapPlant.y);
  Answer::NetPacket::writeInt8(packet, this->m_Camp);
  ReviveTime = Plant::GetReviveTime(this);
  Answer::NetPacket::writeInt32(packet, ReviveTime);
  return 1;
}


#####################################
void __cdecl Plant::BroadcastChange(Plant *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2789u);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Plant *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Answer::NetPacket::writeInt64(packet, this->m_gather);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Plant::BroadcastGathered(Plant *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x278Au);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Plant *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Plant::broadcastRemove(Plant *const this)
{
  if ( this->m_pMap )
    Map::broadcastLeaveMap(this->m_pMap, this);
}


#####################################
int32_t __cdecl Plant::getNow(Plant *const this)
{
  CTimer *v2; // rax

  if ( this->m_pMap )
    return Map::getNow(this->m_pMap);
  v2 = Answer::Singleton<CTimer>::instance();
  return CTimer::GetNow(v2);
}


#####################################
bool __cdecl Plant::isLifeEnd(Plant *const this)
{
  return this->m_nLifeTime > 0 && Plant::getNow(this) >= this->m_nLifeTime;
}


#####################################
void __cdecl Plant::setLifeTime(Plant *const this, int32_t nLifeTime)
{
  if ( nLifeTime <= 0 )
    this->m_nLifeTime = 0;
  else
    this->m_nLifeTime = nLifeTime + Plant::getNow(this);
}


#####################################
void __cdecl Plant::revive(Plant *const this)
{
  this->m_gather = 0;
  this->m_gatherTick = 0;
  this->m_isCorpse = 0;
  this->m_isHide = 0;
  this->m_corpseTick = 0;
  if ( this->m_cfgPlant.revive_skin > 0 )
    Plant::broadcastRemove(this);
  Map::broadcastIntoMap(this->m_pMap, this);
}


#####################################
int32_t __cdecl Plant::GetSpecialItem(Plant *const this, int32_t nIndex)
{
  if ( nIndex < 0 || (int)std::vector<int>::size(&this->m_cfgPlant.ItemVt) <= nIndex )
    return 0;
  else
    return *std::vector<int>::operator[](&this->m_cfgPlant.ItemVt, nIndex);
}


