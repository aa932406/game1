// Decompiled methods for class: Trap
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl Trap::~Trap(Trap *const this)
{
  Trap::~Trap(this);
  operator delete(this);
}


#####################################
void __cdecl Trap::init(Trap *const this, Map *pMap, Position pos, const CfgTrap *const cfgTrap)
{
  if ( pMap )
  {
    CfgTrap::operator=(&this->m_cfgTrap, cfgTrap);
    this->m_pMap = pMap;
    this->m_currentTile = pos;
    this->m_currentPos = Map::tileToPixel(pos.x, pos.y);
    this->m_user = 0;
    this->m_state = TrapState::TS_STANDBY;
    this->m_stateTick = Map::getTick(this->m_pMap);
    if ( this->m_cfgTrap.life > 0 )
      this->m_liftTime = Map::getNow(this->m_pMap) + this->m_cfgTrap.life;
  }
}


#####################################
void __cdecl Trap::reset(Trap *const this)
{
  StaticObj::reset(this);
  this->m_user = 0;
  this->m_state = TrapState::TS_STANDBY;
  this->m_stateTick = 0;
  this->m_liftTime = 0;
}


#####################################
void __cdecl Trap::checkState(Trap *const this)
{
  TrapState m_state; // eax

  if ( this->m_pMap )
  {
    if ( this->m_liftTime > 0 && this->m_state != TrapState::TS_DIE && Map::getNow(this->m_pMap) > this->m_liftTime )
    {
      Trap::setState(this, TrapState::TS_DIE);
    }
    else
    {
      m_state = this->m_state;
      if ( m_state == TrapState::TS_EFFECT )
      {
        if ( Map::getTick(this->m_pMap) - this->m_stateTick >= this->m_cfgTrap.delay )
          Trap::effect(this);
      }
      else if ( m_state == TrapState::TS_COOLDOWN
             && Map::getTick(this->m_pMap) - this->m_stateTick >= this->m_cfgTrap.cd )
      {
        Trap::setState(this, TrapState::TS_STANDBY);
      }
    }
  }
}


#####################################
int32_t __cdecl Trap::onUse(Trap *const this, Player *player)
{
  if ( !this->m_pMap || !player )
    return 10002;
  if ( this->m_state )
    return 10005;
  if ( this->m_cfgTrap.item_cost && !Player::hasItem(player, this->m_cfgTrap.item_cost, 1, 1) )
    return 10002;
  if ( (this->m_cfgTrap.event_type == 4 || this->m_cfgTrap.event_type == 6) && Player::IsTeamLeader(player) )
    return 10002;
  Trap::setState(this, TrapState::TS_EFFECT);
  this->m_user = Player::getCid(player);
  return 0;
}


#####################################
bool __cdecl Trap::appendInfo(Trap *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  int64_t v4; // rdx

  if ( !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  v4 = (*((__int64 (__fastcall **)(Trap *const))this->_vptr_Entity + 2))(this);
  Answer::NetPacket::writeInt64(packet, v4);
  Answer::NetPacket::writeInt32(packet, this->m_cfgTrap.id);
  Answer::NetPacket::writeInt16(packet, this->m_currentTile.x);
  Answer::NetPacket::writeInt16(packet, this->m_currentTile.y);
  return 1;
}


#####################################
void __cdecl Trap::broadcastState(Trap *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2741u);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Trap *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Answer::NetPacket::writeInt32(packet, this->m_state);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcast(this->m_pMap, packet);
    }
  }
}


#####################################
void __cdecl Trap::broadcastLeaveMap(Trap *const this)
{
  if ( this->m_pMap )
    Map::broadcastLeaveMap(this->m_pMap, this);
}


#####################################
void __cdecl Trap::setState(Trap *const this, TrapState state)
{
  if ( this->m_pMap )
  {
    this->m_state = state;
    this->m_stateTick = Map::getTick(this->m_pMap);
    if ( this->m_state == TrapState::TS_DIE )
      Trap::broadcastLeaveMap(this);
    else
      Trap::broadcastState(this);
  }
}


#####################################
void __cdecl Trap::effect(Trap *const this)
{
  int32_t RunnerId; // r12d
  CharId_t m_user; // rbx
  GameService *v3; // rax
  const char *v4; // rax
  CfgData *v5; // rax
  int32_t v6; // edx
  Buff *v7; // rbx
  CActivityMap *v8; // rax
  Dungeon *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  std::string *v12; // rax
  const char *v13; // rax
  std::string *v14; // rax
  const char *v15; // rax
  std::string *v16; // rax
  const char *v17; // rax
  std::string *v18; // rax
  const char *v19; // rax
  MapManager *v20; // rax
  CActivityMap *v21; // rax
  CActivityMap *v22; // rax
  Dungeon *v23; // rax
  std::string *v24; // rax
  const char *v25; // rax
  std::string *v26; // rax
  const char *v27; // rax
  Player **v28; // rax
  Dungeon *v29; // rax
  const char *v30; // rax
  CfgData *v31; // rax
  MapManager *v32; // rax
  Map *Map; // rax
  int64_t v34; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v37; // rax
  int32_t v38; // ebx
  MapManager *v39; // rax
  DBService *v40; // rax
  Dungeon *v41; // rax
  const char *v42; // rax
  int32_t v43; // eax
  LogDungeon logDungeon; // [rsp+30h] [rbp-1B0h] BYREF
  std::_List_iterator<Player*> it_0; // [rsp+50h] [rbp-190h] BYREF
  PlayerList players_0; // [rsp+60h] [rbp-180h] BYREF
  std::_List_iterator<Player*> it; // [rsp+70h] [rbp-170h] BYREF
  PlayerList players; // [rsp+80h] [rbp-160h] BYREF
  StringVector strPos_0; // [rsp+90h] [rbp-150h] BYREF
  StringVector strPos; // [rsp+B0h] [rbp-130h] BYREF
  UnitHandle launcher; // [rsp+D0h] [rbp-110h] BYREF
  std::string delims; // [rsp+E0h] [rbp-100h] BYREF
  char v53; // [rsp+EFh] [rbp-F1h] BYREF
  std::string v54; // [rsp+F0h] [rbp-F0h] BYREF
  char v55; // [rsp+FFh] [rbp-E1h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+100h] [rbp-E0h] BYREF
  std::_List_iterator<Player*> v57; // [rsp+110h] [rbp-D0h] BYREF
  Player *player; // [rsp+118h] [rbp-C8h]
  int32_t BuffId; // [rsp+124h] [rbp-BCh]
  CfgBuff *cfgBuff; // [rsp+128h] [rbp-B8h]
  Buff *buff; // [rsp+130h] [rbp-B0h]
  CActivityMap *pAactivityMap; // [rsp+138h] [rbp-A8h]
  Dungeon *pDungeon; // [rsp+140h] [rbp-A0h]
  int32_t x; // [rsp+14Ch] [rbp-94h]
  int32_t y; // [rsp+150h] [rbp-90h]
  int32_t id; // [rsp+154h] [rbp-8Ch]
  int32_t x_0; // [rsp+158h] [rbp-88h]
  int32_t y_0; // [rsp+15Ch] [rbp-84h]
  Map *pTarMap; // [rsp+160h] [rbp-80h]
  CActivityMap *pActMap; // [rsp+168h] [rbp-78h]
  CActivityMap *pTarActMap; // [rsp+170h] [rbp-70h]
  CActivity *pActivity; // [rsp+178h] [rbp-68h]
  Dungeon *pDungeon_0; // [rsp+180h] [rbp-60h]
  int32_t x_1; // [rsp+188h] [rbp-58h]
  int32_t y_1; // [rsp+18Ch] [rbp-54h]
  Dungeon *pDungeon_1; // [rsp+190h] [rbp-50h]
  int32_t dungeonId; // [rsp+19Ch] [rbp-44h]
  CfgDungeon *pCfgDungeon; // [rsp+1A0h] [rbp-40h]
  Dungeon *pNewDungeon; // [rsp+1A8h] [rbp-38h]
  Player *player_0; // [rsp+1B0h] [rbp-30h]
  Dungeon *pDungeon_2; // [rsp+1B8h] [rbp-28h]

  if ( this->m_pMap )
  {
    RunnerId = Map::GetRunnerId(this->m_pMap);
    m_user = this->m_user;
    v3 = Answer::Singleton<GameService>::instance();
    player = GameService::getPlayer(v3, m_user, RunnerId, 1);
    if ( player )
    {
      switch ( this->m_cfgTrap.event_type )
      {
        case 1:
          v4 = (const char *)std::string::c_str(&this->m_cfgTrap.effect);
          BuffId = atoi(v4);
          if ( BuffId <= 0 )
            goto LABEL_8;
          v5 = Answer::Singleton<CfgData>::instance();
          cfgBuff = CfgData::getBuff(v5, BuffId);
          if ( !cfgBuff )
            goto LABEL_8;
          launcher.id = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 12))(player);
          launcher.type = v6;
          v7 = (Buff *)operator new(0x60u);
          Buff::Buff(v7, player, cfgBuff, &launcher, 1, 1);
          buff = v7;
          if ( v7 )
          {
            Unit::addBuff(player, buff);
LABEL_8:
            Trap::setState(this, TrapState::TS_DIE);
          }
          return;
        case 2:
        case 5:
          if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap) )
          {
            if ( this->m_pMap )
              v8 = (CActivityMap *)__dynamic_cast(
                                     this->m_pMap,
                                     (const struct __class_type_info *)&`typeinfo for'Map,
                                     (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                     0);
            else
              v8 = 0;
            pAactivityMap = v8;
            if ( v8 )
              CActivityMap::generateMonster(pAactivityMap, &this->m_cfgTrap.effect);
          }
          else if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
          {
            v9 = this->m_pMap
               ? (Dungeon *)__dynamic_cast(
                              this->m_pMap,
                              (const struct __class_type_info *)&`typeinfo for'Map,
                              (const struct __class_type_info *)&`typeinfo for'Dungeon,
                              0)
               : 0LL;
            pDungeon = v9;
            if ( v9 )
              Dungeon::generateMonster(pDungeon, &this->m_cfgTrap.effect, 0);
          }
          goto LABEL_77;
        case 3:
          std::allocator<char>::allocator(&v53);
          std::string::string(&delims, ":");
          Answer::StringUtility::split(&strPos, &this->m_cfgTrap.effect, &delims, 0);
          std::string::~string(&delims);
          std::allocator<char>::~allocator(&v53);
          if ( std::vector<std::string>::size(&strPos) == 2 )
          {
            v10 = std::vector<std::string>::operator[](&strPos, 0);
            v11 = (const char *)std::string::c_str(v10);
            x = atoi(v11);
            v12 = std::vector<std::string>::operator[](&strPos, 1u);
            v13 = (const char *)std::string::c_str(v12);
            y = atoi(v13);
            Unit::instantMove(player, x, y, InstanceMoveReason::IMR_TRANSFER, 0);
            Trap::setState(this, TrapState::TS_STANDBY);
            this->m_user = 0;
            if ( this->m_cfgTrap.cd <= 0 )
              goto LABEL_45;
LABEL_44:
            Trap::setState(this, TrapState::TS_COOLDOWN);
            goto LABEL_45;
          }
          if ( std::vector<std::string>::size(&strPos) != 3 )
            goto LABEL_45;
          v14 = std::vector<std::string>::operator[](&strPos, 0);
          v15 = (const char *)std::string::c_str(v14);
          id = atoi(v15);
          v16 = std::vector<std::string>::operator[](&strPos, 1u);
          v17 = (const char *)std::string::c_str(v16);
          x_0 = atoi(v17);
          v18 = std::vector<std::string>::operator[](&strPos, 2u);
          v19 = (const char *)std::string::c_str(v18);
          y_0 = atoi(v19);
          v20 = Answer::Singleton<MapManager>::instance();
          pTarMap = MapManager::GetMap(v20, id);
          if ( !pTarMap )
            goto LABEL_45;
          if ( this->m_pMap == pTarMap )
          {
            Unit::instantMove(player, x_0, y_0, InstanceMoveReason::IMR_TRANSFER, 0);
            Trap::setState(this, TrapState::TS_STANDBY);
            this->m_user = 0;
            goto LABEL_43;
          }
          if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap) )
          {
            if ( this->m_pMap )
              v21 = (CActivityMap *)__dynamic_cast(
                                      this->m_pMap,
                                      (const struct __class_type_info *)&`typeinfo for'Map,
                                      (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                      0);
            else
              v21 = 0;
            pActMap = v21;
            if ( pTarMap )
              v22 = (CActivityMap *)__dynamic_cast(
                                      pTarMap,
                                      (const struct __class_type_info *)&`typeinfo for'Map,
                                      (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                      0);
            else
              v22 = 0;
            pTarActMap = v22;
            if ( !pActMap
              || !pTarActMap
              || (pActivity = CActivityMap::GetActivity(pActMap)) == 0
              || (*((unsigned __int8 (__fastcall **)(CActivity *, Player *, CActivityMap *, _QWORD, _QWORD, _QWORD))pActivity->_vptr_CActivity
                  + 24))(
                   pActivity,
                   player,
                   pTarActMap,
                   (unsigned int)x_0,
                   (unsigned int)y_0,
                   0) != 1 )
            {
LABEL_45:
              std::vector<std::string>::~vector(&strPos);
              return;
            }
          }
          else
          {
            Player::switchMap(player, pTarMap, x_0, y_0, 1);
            Trap::setState(this, TrapState::TS_STANDBY);
            this->m_user = 0;
          }
LABEL_43:
          if ( this->m_cfgTrap.cd <= 0 )
            goto LABEL_45;
          goto LABEL_44;
        case 4:
          if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
          {
            v23 = this->m_pMap
                ? (Dungeon *)__dynamic_cast(
                               this->m_pMap,
                               (const struct __class_type_info *)&`typeinfo for'Map,
                               (const struct __class_type_info *)&`typeinfo for'Dungeon,
                               0)
                : 0LL;
            pDungeon_0 = v23;
            if ( v23 )
            {
              std::allocator<char>::allocator(&v55);
              std::string::string(&v54, ":");
              Answer::StringUtility::split(&strPos_0, &this->m_cfgTrap.effect, &v54, 0);
              std::string::~string(&v54);
              std::allocator<char>::~allocator(&v55);
              if ( std::vector<std::string>::size(&strPos_0) == 2 )
              {
                v24 = std::vector<std::string>::operator[](&strPos_0, 0);
                v25 = (const char *)std::string::c_str(v24);
                x_1 = atoi(v25);
                v26 = std::vector<std::string>::operator[](&strPos_0, 1u);
                v27 = (const char *)std::string::c_str(v26);
                y_1 = atoi(v27);
                Dungeon::getPlayers((Dungeon *const)&players);
                for ( it._M_node = std::list<Player *>::begin(&players)._M_node;
                      ;
                      std::_List_iterator<Player *>::operator++(&it) )
                {
                  __x._M_node = std::list<Player *>::end(&players)._M_node;
                  if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
                    break;
                  v28 = std::_List_iterator<Player *>::operator*(&it);
                  Unit::instantMove(*v28, x_1, y_1, InstanceMoveReason::IMR_TRANSFER, 0);
                }
                Trap::setState(this, TrapState::TS_DIE);
                std::list<Player *>::~list(&players);
              }
              std::vector<std::string>::~vector(&strPos_0);
            }
          }
          return;
        case 6:
          if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
          {
            v29 = this->m_pMap
                ? (Dungeon *)__dynamic_cast(
                               this->m_pMap,
                               (const struct __class_type_info *)&`typeinfo for'Map,
                               (const struct __class_type_info *)&`typeinfo for'Dungeon,
                               0)
                : 0LL;
            pDungeon_1 = v29;
            if ( v29 )
            {
              v30 = (const char *)std::string::c_str(&this->m_cfgTrap.effect);
              dungeonId = atoi(v30);
              v31 = Answer::Singleton<CfgData>::instance();
              pCfgDungeon = CfgData::getDungeon(v31, dungeonId);
              if ( pCfgDungeon )
              {
                v32 = Answer::Singleton<MapManager>::instance();
                pNewDungeon = MapManager::NewDungeon(v32, dungeonId);
                if ( pNewDungeon )
                {
                  Dungeon::start(pNewDungeon, 0);
                  Dungeon::getPlayers((Dungeon *const)&players_0);
                  for ( it_0._M_node = std::list<Player *>::begin(&players_0)._M_node;
                        ;
                        std::_List_iterator<Player *>::operator++(&it_0) )
                  {
                    v57._M_node = std::list<Player *>::end(&players_0)._M_node;
                    if ( !std::_List_iterator<Player *>::operator!=(&it_0, &v57) )
                      break;
                    player_0 = *std::_List_iterator<Player *>::operator*(&it_0);
                    if ( player_0 )
                    {
                      Player::leaveDungeon(player_0);
                      Player::setOldPosition(player_0);
                      Player::broadcastLeave(player_0);
                      Map = StaticObj::getMap(player_0);
                      (*((void (__fastcall **)(Map *, Player *, _QWORD))Map->_vptr_Map + 16))(Map, player_0, 0);
                      v34 = pCfgDungeon->id;
                      GateIndex = Player::getGateIndex(player_0);
                      ConnId = Player::getConnId(player_0);
                      v37 = Answer::Singleton<GameService>::instance();
                      GameService::replySuccess(v37, ConnId, GateIndex, 0x12u, v34);
                      (*((void (__fastcall **)(Dungeon *, Player *, _QWORD, _QWORD))pNewDungeon->_vptr_Map + 15))(
                        pNewDungeon,
                        player_0,
                        (unsigned int)pCfgDungeon->x,
                        (unsigned int)pCfgDungeon->y);
                      v38 = Map::GetRunnerId(pNewDungeon);
                      v39 = Answer::Singleton<MapManager>::instance();
                      MapManager::PostMsg(v39, v38, GameMsgCode::GMC_ADD_DUNGEON, pNewDungeon, 0, 0, 0, 0);
                      memset(&logDungeon, 0, sizeof(logDungeon));
                      logDungeon.cid = Player::getCid(player_0);
                      logDungeon.did = dungeonId;
                      logDungeon.type = Dungeon::getDungeonType(pNewDungeon);
                      logDungeon.level = (*((__int64 (__fastcall **)(Player *))player_0->_vptr_Entity + 9))(player_0);
                      logDungeon.start_time = Dungeon::GetStartTime(pNewDungeon);
                      LOBYTE(v38) = Player::getConnId(player_0);
                      v40 = Answer::Singleton<DBService>::instance();
                      DBService::insertDungeon(v40, v38, &logDungeon);
                    }
                  }
                  std::list<Player *>::~list(&players_0);
                }
              }
            }
          }
          Trap::setState(this, TrapState::TS_DIE);
          return;
        case 7:
          if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
          {
            v41 = this->m_pMap
                ? (Dungeon *)__dynamic_cast(
                               this->m_pMap,
                               (const struct __class_type_info *)&`typeinfo for'Map,
                               (const struct __class_type_info *)&`typeinfo for'Dungeon,
                               0)
                : 0LL;
            pDungeon_2 = v41;
            if ( v41 )
            {
              v42 = (const char *)std::string::c_str(&this->m_cfgTrap.effect);
              v43 = atoi(v42);
              Dungeon::AddDungeonTime(pDungeon_2, v43);
            }
          }
LABEL_77:
          Trap::setState(this, TrapState::TS_DIE);
          return;
        default:
          return;
      }
    }
  }
}


