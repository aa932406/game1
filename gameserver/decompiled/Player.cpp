// Decompiled methods for class: Player
// Source: gameserver.cc
// Total methods: 361

#####################################
void __cdecl Player::SetInFight(Player *const this)
{
  int64_t Tick; // rax

  Tick = Unit::getTick(this);
  CExtFightChecker::SetInFight(&this->m_extFightChecker, Tick);
}


#####################################
void __cdecl Player::SetInPvP(Player *const this)
{
  int64_t Tick; // rax

  Tick = Unit::getTick(this);
  CExtFightChecker::SetInPvP(&this->m_extFightChecker, Tick);
}


#####################################
void __cdecl Player::InitTencentInfo(Player *const this, const TencentInfo *const info)
{
  CExtCharTencent::InitTencentInfo(&this->m_extCharTencent, info);
}


#####################################
void __cdecl Player::~Player(Player *const this)
{
  Player::~Player(this);
  operator delete(this);
}


#####################################
bool __cdecl Player::refresh(Player *const this)
{
  int64_t Tick; // rax

  if ( this->m_needRecalAttr )
    Player::recalcAttr(this, 1, 0);
  Player::checkSaveToDB(this);
  if ( Player::checkNetPackets(this) )
    return 1;
  Player::CheckTrailer(this);
  Player::checkPool(this);
  Player::minuteCheck(this, 1);
  Player::checkSyncStatus(this);
  Player::checkDie(this);
  Tick = Unit::getTick(this);
  CExtSystemMgr::OnUpdate(&this->m_ExtSysMgr, Tick);
  return 0;
}


#####################################
int32_t __cdecl Player::GetViewHP(const Player *const this)
{
  const CObjCarrier *pCarrier; // [rsp+18h] [rbp-8h]

  pCarrier = CExtCharCarrier::GetCarrier(&this->m_extCharCarrier);
  if ( pCarrier )
    return (*((int32_t (__fastcall **)(const CObjCarrier *))pCarrier->_vptr_Entity + 19))(pCarrier);
  else
    return (*((int32_t (__fastcall **)(const Player *const))this->_vptr_Entity + 19))(this);
}


#####################################
int32_t __cdecl Player::GetViewMaxHP(const Player *const this)
{
  const CObjCarrier *pCarrier; // [rsp+18h] [rbp-8h]

  pCarrier = CExtCharCarrier::GetCarrier(&this->m_extCharCarrier);
  if ( pCarrier )
    return (*((int32_t (__fastcall **)(const CObjCarrier *))pCarrier->_vptr_Entity + 20))(pCarrier);
  else
    return (*((int32_t (__fastcall **)(const Player *const))this->_vptr_Entity + 20))(this);
}


#####################################
int32_t __cdecl Player::GetMoveSpeed(const Player *const this)
{
  const CObjCarrier *pCarrier; // [rsp+18h] [rbp-8h]

  pCarrier = CExtCharCarrier::GetCarrier(&this->m_extCharCarrier);
  if ( pCarrier )
    return (*((int32_t (__fastcall **)(const CObjCarrier *))pCarrier->_vptr_Entity + 28))(pCarrier);
  else
    return Unit::GetMoveSpeed(this);
}


#####################################
int32_t __cdecl Player::GetAttackSpeed(const Player *const this)
{
  const CObjCarrier *pCarrier; // [rsp+18h] [rbp-8h]

  pCarrier = CExtCharCarrier::GetCarrier(&this->m_extCharCarrier);
  if ( pCarrier )
    return (*((int32_t (__fastcall **)(const CObjCarrier *))pCarrier->_vptr_Entity + 29))(pCarrier);
  else
    return Unit::GetAttackSpeed(this);
}


#####################################
void __cdecl Player::SetLevel(Player *const this, int32_t Level)
{
  int32_t OldLevel; // [rsp+1Ch] [rbp-4h]

  OldLevel = this->m_chr.level;
  this->m_chr.level = Level;
  Player::LevelUped(this, OldLevel, Level);
}


#####################################
void __cdecl Player::checkDie(Player *const this)
{
  int32_t v2; // edx

  if ( !this->m_bDie && !Unit::isAlive(this) )
  {
    this->m_bDie = 1;
    this->m_nDieTick = Unit::getTick(this);
    v2 = Player::getRecord(this, 1012) + 1;
    Player::updateRecord(this, 1012, v2);
    if ( this->m_pMap )
      (*((void (__fastcall **)(Map *, Player *const))this->m_pMap->_vptr_Map + 14))(this->m_pMap, this);
    CExtCharPet::OnPlayerDie(&this->m_extCharPet);
    CharLittlerHelper::OnRest(&this->m_CharLittlerhelper);
  }
}


#####################################
void __cdecl Player::PkModeTiShi(Player *const this)
{
  bool v1; // al
  int32_t v2; // edx
  int8_t m_connid; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pMap )
  {
    v1 = (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap)
      || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap);
    if ( !v1 && Player::getPkMode(this) == 1 && Player::getRecord(this, 1) <= 0 && Player::getRecord(this, 1914) <= 2 )
    {
      Player::updateRecord(this, 1, 1);
      v2 = Player::getRecord(this, 1914) + 1;
      Player::updateRecord(this, 1914, v2);
      m_connid = this->m_connid;
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x2803u);
      if ( packet )
      {
        Answer::NetPacket::writeInt8(packet, 1);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        m_cgindex = this->m_cgindex;
        v7 = this->m_connid;
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, v7, m_cgindex, packet);
      }
    }
  }
}


#####################################
bool __cdecl Player::IsActDropItemMap(Player *const this)
{
  unsigned int nMapParam; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pMap )
    return 0;
  if ( Map::GetType(this->m_pMap) != 4 )
    return 0;
  nMapParam = Map::GetMapParam(this->m_pMap);
  return nMapParam <= 0x11 && ((1LL << nMapParam) & 0x25020) != 0;
}


#####################################
void __cdecl Player::EnterPrisonByPlayer(Player *const this, Player *killer)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  CharId_t v5; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  std::string v10; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( killer )
  {
    m_connid = this->m_connid;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 189);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&v10);
      Answer::NetPacket::writeUTF8(packet, &v10);
      std::string::~string(&v10);
      v5 = Player::getCid(killer);
      Answer::NetPacket::writeInt64(packet, v5);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = this->m_connid;
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


#####################################
void __cdecl Player::EnterPrisonByMonster(Player *const this, int32_t Mid)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v6; // bl
  GameService *v7; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 190);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, Mid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v7, v6, packet);
  }
}


#####################################
void __cdecl Player::KillerPlayerGongGao(Player *const this, Player *killer)
{
  GameService *v2; // rax
  CharId_t Cid; // rax
  int32_t MapId; // eax
  CharId_t v5; // rax
  uint32_t WOffset; // eax
  GameService *v7; // rax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  std::string v9; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( killer )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 139);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(killer);
      Answer::NetPacket::writeInt64(packet, Cid);
      MapId = StaticObj::getMapId(this);
      Answer::NetPacket::writeInt32(packet, MapId);
      Player::getName((const Player *const)&v9);
      Answer::NetPacket::writeUTF8(packet, &v9);
      std::string::~string(&v9);
      v5 = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, v5);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v7, packet);
    }
  }
}


#####################################
void __cdecl Player::SendFamilyMemberKilled(Player *const this, Player *Killer)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  CharId_t Cid; // rdx
  CharId_t v5; // rdx
  int32_t MapId; // edx
  int16_t PosX; // dx
  int16_t PosY; // dx
  uint32_t WOffset; // edx
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( Killer )
  {
    m_connid = this->m_connid;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_PROC, 0x4E4Au);
    if ( packet )
    {
      Cid = Player::getCid(Killer);
      Answer::NetPacket::writeInt64(packet, Cid);
      v5 = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, v5);
      MapId = StaticObj::getMapId(this);
      Answer::NetPacket::writeInt32(packet, MapId);
      PosX = StaticObj::GetPosX(this);
      Answer::NetPacket::writeInt16(packet, PosX);
      PosY = StaticObj::GetPosY(this);
      Answer::NetPacket::writeInt16(packet, PosY);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v10 = this->m_connid;
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v11, v10, packet);
    }
  }
}


#####################################
bool __cdecl Player::isFriendSide(Player *const this, Unit *pUnit)
{
  bool result; // al
  int32_t RunnerId; // r12d
  CharId_t v5; // rbx
  GameService *v6; // rax
  __int64 v7; // rax
  FamilyId_t FamilyId; // rbx
  int32_t TeamId; // ebx
  bool v10; // al
  CExtFightChecker *FightChecker; // rax
  bool v12; // al
  int8_t ConnId; // bl
  int8_t Camp; // bl
  FamilyId_t v15; // rbx
  CharId_t Cid; // rbx
  const Monster *v17; // rax
  FamilyId_t v18; // rbx
  int8_t v20; // al
  Player *player; // [rsp+20h] [rbp-30h]
  Trailer *pTrailer; // [rsp+30h] [rbp-20h]
  Monster *monster; // [rsp+38h] [rbp-18h]

  if ( !pUnit )
    return 0;
  if ( !StaticObj::getMap(this) )
    return 0;
  if ( Entity::getType(pUnit) == EntityType::ET_PLAYER || Entity::getType(pUnit) == EntityType::ET_PET )
  {
    if ( Entity::getType(pUnit) == EntityType::ET_PET )
    {
      RunnerId = StaticObj::GetRunnerId(this);
      v5 = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 4))(pUnit);
      v6 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v6, v5, RunnerId, 1);
    }
    else
    {
      player = (Player *)__dynamic_cast(
                           pUnit,
                           (const struct __class_type_info *)&`typeinfo for'Unit,
                           (const struct __class_type_info *)&`typeinfo for'Player,
                           0);
    }
    if ( player )
    {
      if ( player == this )
      {
        return 1;
      }
      else if ( Player::GetStartProtect(player) <= 0 )
      {
        if ( Player::getPkProtectTime(player) <= 0 )
        {
          LODWORD(v7) = Player::getPkMode(this);
          switch ( v7 )
          {
            case 1LL:
              result = 1;
              break;
            case 2LL:
              v10 = 0;
              if ( Player::IsInTeam(this) )
              {
                TeamId = Player::GetTeamId(this);
                if ( TeamId == Player::GetTeamId(player) )
                  v10 = 1;
              }
              result = v10;
              break;
            case 3LL:
              result = 0;
              if ( Player::getFamilyId(this) > 0 )
              {
                FamilyId = Player::getFamilyId(this);
                if ( FamilyId == Player::getFamilyId(player) )
                  result = 1;
              }
              break;
            case 4LL:
              v12 = 1;
              if ( Player::getPkValue(player) <= 99 )
              {
                FightChecker = Player::GetFightChecker(player);
                if ( !CExtFightChecker::IsBuleName(FightChecker) )
                  v12 = 0;
              }
              result = !v12;
              break;
            case 5LL:
              ConnId = Player::getConnId(this);
              result = ConnId == Player::getConnId(player);
              break;
            case 6LL:
              result = 0;
              break;
            case 7LL:
              Camp = Player::GetCamp(this);
              result = Camp == Player::GetCamp(player);
              break;
            default:
              result = 0;
              break;
          }
        }
        else
        {
          return 1;
        }
      }
      else
      {
        return 1;
      }
    }
    else
    {
      return 0;
    }
  }
  else if ( Entity::getType(pUnit) == EntityType::ET_TRAILER )
  {
    if ( Player::getPkMode(this) == 1 )
    {
      return 1;
    }
    else
    {
      pTrailer = (Trailer *)__dynamic_cast(
                              pUnit,
                              (const struct __class_type_info *)&`typeinfo for'Unit,
                              (const struct __class_type_info *)&`typeinfo for'Trailer,
                              0);
      if ( pTrailer )
      {
        if ( Player::getPkMode(this) == 3 && (v15 = Player::getFamilyId(this), v15 == Trailer::GetFamilyId(pTrailer)) )
        {
          return 1;
        }
        else
        {
          Cid = Player::getCid(this);
          return Cid == (*((__int64 (__fastcall **)(Trailer *))pTrailer->_vptr_Entity + 4))(pTrailer)
              || Trailer::Robbery(pTrailer);
        }
      }
      else
      {
        return 0;
      }
    }
  }
  else
  {
    v17 = (const Monster *)__dynamic_cast(
                             pUnit,
                             (const struct __class_type_info *)&`typeinfo for'Unit,
                             (const struct __class_type_info *)&`typeinfo for'Monster,
                             0);
    monster = (Monster *)v17;
    if ( v17 )
    {
      if ( Monster::getSide(v17) == 1 )
      {
        return 1;
      }
      else if ( Monster::GetFamilyId(monster) > 0
             && (v18 = Monster::GetFamilyId(monster), v18 == Player::getFamilyId(this)) )
      {
        return 1;
      }
      else if ( Player::GetCamp(this) > 0
             && (v20 = Player::GetCamp(this),
                 v20 == (*((unsigned __int8 (__fastcall **)(Monster *))monster->_vptr_Entity + 39))(monster)) )
      {
        return 1;
      }
      else
      {
        return (Monster::getAIStyle(monster) & 2) != 0 && Player::getPkMode(this) != 6;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}


#####################################
bool __cdecl Player::checkSkillTarget(Player *const this, const CfgActiveSkill *pCfg, Unit *pUnit)
{
  Player *v6; // rax
  CObjPet *v8; // rax
  int32_t RunnerId; // r12d
  GameService *v10; // rax
  Position pos; // [rsp+20h] [rbp-80h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-70h] BYREF
  Position v15; // [rsp+40h] [rbp-60h] BYREF
  Position v16; // [rsp+50h] [rbp-50h] BYREF
  Position v17; // [rsp+60h] [rbp-40h] BYREF
  Player *player; // [rsp+70h] [rbp-30h]
  CObjPet *pPet; // [rsp+78h] [rbp-28h]
  CharId_t ownerId; // [rsp+80h] [rbp-20h]
  Player *player_0; // [rsp+88h] [rbp-18h]

  if ( !pCfg || !pUnit || !this->m_pMap || StaticObj::getMap(pUnit) != this->m_pMap )
    return 0;
  if ( !Unit::isAlive(pUnit) && pCfg->special != 4 )
    return 0;
  if ( pCfg->beneficial )
    return (*((bool (__fastcall **)(Player *const, Unit *))this->_vptr_Entity + 14))(this, pUnit);
  if ( Entity::getType(pUnit) == EntityType::ET_PLAYER )
  {
    if ( (*((int (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this) > 69 )
    {
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
        if ( player == this )
        {
          return 0;
        }
        else if ( (*((int (__fastcall **)(Player *))player->_vptr_Entity + 9))(player) > 69 )
        {
          pos = StaticObj::getCurrentTile(player);
          if ( Map::inSafeRegion(this->m_pMap, &pos) )
            return 0;
          CurrentTile = StaticObj::getCurrentTile(this);
          if ( Map::inSafeRegion(this->m_pMap, &CurrentTile) )
            return 0;
          else
            return (*((__int64 (__fastcall **)(Player *const, Player *))this->_vptr_Entity + 14))(this, player) ^ 1;
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else if ( Entity::getType(pUnit) == EntityType::ET_PET )
  {
    if ( (*((int (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this) > 69 )
    {
      if ( pUnit )
        v8 = (CObjPet *)__dynamic_cast(
                          pUnit,
                          (const struct __class_type_info *)&`typeinfo for'Unit,
                          (const struct __class_type_info *)&`typeinfo for'CObjPet,
                          0);
      else
        v8 = 0;
      pPet = v8;
      if ( v8 )
      {
        ownerId = (*((__int64 (__fastcall **)(CObjPet *))pPet->_vptr_Entity + 4))(pPet);
        RunnerId = StaticObj::GetRunnerId(this);
        v10 = Answer::Singleton<GameService>::instance();
        player_0 = GameService::getPlayer(v10, ownerId, RunnerId, 1);
        if ( player_0 )
        {
          if ( player_0 == this )
          {
            return 0;
          }
          else if ( (*((int (__fastcall **)(Player *))player_0->_vptr_Entity + 9))(player_0) > 29 )
          {
            v15 = StaticObj::getCurrentTile(player_0);
            if ( Map::inSafeRegion(this->m_pMap, &v15) )
              return 0;
            v16 = StaticObj::getCurrentTile(this);
            if ( Map::inSafeRegion(this->m_pMap, &v16) )
              return 0;
            else
              return (*((__int64 (__fastcall **)(Player *const, Player *))this->_vptr_Entity + 14))(this, player_0) ^ 1;
          }
          else
          {
            return 0;
          }
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else if ( Entity::getType(pUnit) == EntityType::ET_MONSTER )
  {
    return (*((__int64 (__fastcall **)(Player *const, Unit *))this->_vptr_Entity + 14))(this, pUnit) ^ 1;
  }
  else if ( Entity::getType(pUnit) == EntityType::ET_TRAILER )
  {
    v17 = StaticObj::getCurrentTile(pUnit);
    if ( Map::inSafeRegion(this->m_pMap, &v17) )
      return 0;
    else
      return (*((__int64 (__fastcall **)(Player *const, Unit *))this->_vptr_Entity + 14))(this, pUnit) ^ 1;
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl Player::SaveDBData(Player *const this, PlayerDBData *const dbData)
{
  int32_t pk_time; // ebx
  int32_t v4; // eax
  int32_t level_stay_time; // ebx
  MemChrBuffVector __x; // [rsp+10h] [rbp-50h] BYREF
  _BYTE v7[16]; // [rsp+30h] [rbp-30h] BYREF
  int32_t mapid; // [rsp+40h] [rbp-20h]
  int32_t x; // [rsp+44h] [rbp-1Ch]
  int32_t y; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  mapid = this->m_chr.mapid;
  x = this->m_chr.x;
  y = this->m_chr.y;
  if ( this->m_pMap )
  {
    mapid = Map::GetMapId(this->m_pMap);
    x = StaticObj::getCurrentTile(this).x;
    y = StaticObj::getCurrentTile(this).y;
    if ( StaticObj::InDungeon(this) || StaticObj::InActivity(this) )
    {
      mapid = this->m_oldPosition.mapid;
      x = this->m_oldPosition.x;
      y = this->m_oldPosition.y;
    }
  }
  dbData->chr.data.cid = this->m_chr.cid;
  snprintf(dbData->chr.data.name, 0x1Eu, this->m_chr.name);
  snprintf(dbData->chr.data.familyName, 0x1Eu, this->m_chr.familyName);
  dbData->chr.data.sex = this->m_chr.sex;
  dbData->chr.data.job = this->m_chr.job;
  dbData->chr.data.level = this->m_chr.level;
  dbData->chr.data.exp = this->m_chr.exp;
  dbData->chr.data.mapid = mapid;
  dbData->chr.data.x = x;
  dbData->chr.data.y = y;
  dbData->chr.data.hp = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 19))(this);
  dbData->chr.data.mp = Unit::GetMP(this);
  dbData->chr.data.kun_li = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 24))(this);
  dbData->chr.data.battle = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 10))(this);
  dbData->chr.data.head = this->m_chr.head;
  dbData->chr.data.pk_mode = this->m_pkMode_bk;
  dbData->chr.data.pk_value = this->m_chr.pk_value;
  pk_time = this->m_chr.pk_time;
  if ( pk_time <= Unit::getNow(this) )
    v4 = 0;
  else
    v4 = this->m_chr.pk_time;
  dbData->chr.data.pk_time = v4;
  dbData->chr.data.kill_count = this->m_chr.kill_count;
  dbData->chr.data.last_task_id = this->m_chr.last_task_id;
  dbData->chr.data.logout_count = this->m_chr.logout_count;
  level_stay_time = this->m_chr.level_stay_time;
  this->m_chr.level_stay_time = level_stay_time + Unit::getNow(this) - this->m_levelStartTime;
  dbData->chr.data.level_stay_time = this->m_chr.level_stay_time;
  dbData->chr.data.last_login_time = this->m_chr.last_login_time;
  dbData->chr.data.last_logout_time = this->m_chr.last_logout_time;
  dbData->chr.data.create_time = this->m_chr.create_time;
  dbData->chr.data.pay_click_count = this->m_chr.pay_click_count;
  dbData->chr.weapon = Player::getMainWeaponId(this);
  dbData->chr.cloth = Player::getClothesId(this);
  dbData->chr.wing = CExtCharWing::GetLevel(&this->m_extCharWing);
  dbData->chr.equipStar = CExtEquip::GetEquipAllStar(&this->m_extEquip);
  dbData->chr.equipGem = CExtEquip::GetEquipAllGemLevel(&this->m_extEquip);
  dbData->chr.moneyDropRatio = Player::GetAllMoneyRate(this);
  for ( i = 0; i <= 49; ++i )
    dbData->attrData.vAttr[i] = Unit::GetAttrValue(this, (const CObjAttrs::Index_T)i);
  dbData->sysUser.data.uid = this->m_sysUser.uid;
  dbData->sysUser.data.sid = this->m_sysUser.sid;
  dbData->sysUser.data.gold_cost_total = this->m_sysUser.gold_cost_total;
  dbData->sysUser.data.map_enter_time = this->m_sysUser.map_enter_time;
  dbData->sysUser.data.last_login_time = this->m_sysUser.last_login_time;
  dbData->sysUser.data.last_logout_time = this->m_sysUser.last_logout_time;
  dbData->sysUser.data.total_login_count = Player::getRecord(this, 1011);
  dbData->sysUser.data.continue_login_count = this->m_sysUser.continue_login_count;
  dbData->sysUser.data.total_online_time = this->m_sysUser.total_online_time;
  dbData->sysUser.data.total_offline_time = this->m_sysUser.total_offline_time;
  dbData->sysUserPreventWallow.data = this->m_sysUserPreventWallow;
  Unit::getItemBuffs(&__x, this);
  std::vector<MemChrBuff>::operator=(&dbData->buffData.buffVt, &__x);
  std::vector<MemChrBuff>::~vector(&__x);
  ChrTask::SaveDBData(&this->m_task, dbData);
  memcpy(dbData->actionData.actionArry, this->m_actions, sizeof(dbData->actionData.actionArry));
  qmemcpy(&dbData->autoFight.data, &this->m_autoFight, sizeof(dbData->autoFight.data));
  Player::GetSysSetting((Player *const)v7);
  std::string::operator=(&dbData->systemSetting.data, v7);
  std::string::~string(v7);
  Player::updateRecord(this, 2008, this->m_InBossHomeTime);
  CExtSystemMgr::OnSaveToDB(&this->m_ExtSysMgr, dbData);
}


#####################################
void __cdecl Player::saveToDB(Player *const this, int32_t reason, int32_t param, int32_t logout_time)
{
  int8_t m_connid; // bl
  DBService *v5; // rax
  PlayerDBData dbData; // [rsp+20h] [rbp-B930h] BYREF

  PlayerDBData::PlayerDBData(&dbData);
  Player::SaveDBData(this, &dbData);
  if ( logout_time )
  {
    dbData.chr.data.last_logout_time = logout_time;
    dbData.sysUser.data.last_logout_time = logout_time;
  }
  Player::saveOnlineTime(this);
  m_connid = this->m_connid;
  v5 = Answer::Singleton<DBService>::instance();
  DBService::savePlayer(v5, m_connid, reason, param, &dbData);
  PlayerDBData::~PlayerDBData(&dbData);
}


#####################################
void __cdecl Player::initNetPacketHandlers()
{
  Player::setNetPacketHandler(8, (Player::NetPacketHandler)(unsigned __int64)Player::onLogout);
  Player::setNetPacketHandler(9, (Player::NetPacketHandler)(unsigned __int64)Player::onSyncTime);
  Player::setNetPacketHandler(10, (Player::NetPacketHandler)(unsigned __int64)Player::onMove);
  Player::setNetPacketHandler(11, (Player::NetPacketHandler)(unsigned __int64)Player::onJump);
  Player::setNetPacketHandler(12, (Player::NetPacketHandler)(unsigned __int64)Player::onTrailerMove);
  Player::setNetPacketHandler(16, (Player::NetPacketHandler)(unsigned __int64)Player::onSwitchMap);
  Player::setNetPacketHandler(18, (Player::NetPacketHandler)(unsigned __int64)Player::onEnterDungeon);
  Player::setNetPacketHandler(21, (Player::NetPacketHandler)(unsigned __int64)Player::onLeaveDungeon);
  Player::setNetPacketHandler(790, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonBuildTower);
  Player::setNetPacketHandler(792, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonBuyTower);
  Player::setNetPacketHandler(791, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonStart);
  Player::setNetPacketHandler(28, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonSelectReward);
  Player::setNetPacketHandler(796, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonSummonBoss);
  Player::setNetPacketHandler(793, (Player::NetPacketHandler)(unsigned __int64)Player::onBuyDungeonEnterTime);
  Player::setNetPacketHandler(797, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonSummon);
  Player::setNetPacketHandler(795, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonQuickDone);
  Player::setNetPacketHandler(23, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonSaoDang);
  Player::setNetPacketHandler(24, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonReset);
  Player::setNetPacketHandler(27, (Player::NetPacketHandler)(unsigned __int64)Player::onGuessTheSize);
  Player::setNetPacketHandler(352, (Player::NetPacketHandler)(unsigned __int64)Player::onEnterChargeDungeon);
  Player::setNetPacketHandler(76, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonYJSKGuWu);
  Player::setNetPacketHandler(29, (Player::NetPacketHandler)(unsigned __int64)Player::onEnterActivity);
  Player::setNetPacketHandler(30, (Player::NetPacketHandler)(unsigned __int64)Player::onLeaveActivity);
  Player::setNetPacketHandler(31, (Player::NetPacketHandler)(unsigned __int64)Player::onGetAwardActivity);
  Player::setNetPacketHandler(32, (Player::NetPacketHandler)(unsigned __int64)Player::onActivityChangeMap);
  Player::setNetPacketHandler(33, (Player::NetPacketHandler)(unsigned __int64)Player::onFamilyWarActivePillar);
  Player::setNetPacketHandler(41, (Player::NetPacketHandler)(unsigned __int64)Player::onPickDropItem);
  Player::setNetPacketHandler(42, (Player::NetPacketHandler)(unsigned __int64)Player::onBeginGather);
  Player::setNetPacketHandler(43, (Player::NetPacketHandler)(unsigned __int64)Player::onEndGather);
  Player::setNetPacketHandler(47, (Player::NetPacketHandler)(unsigned __int64)Player::onSpecialPlant);
  Player::setNetPacketHandler(44, (Player::NetPacketHandler)(unsigned __int64)Player::onUseTrap);
  Player::setNetPacketHandler(45, (Player::NetPacketHandler)(unsigned __int64)Player::onSwitchPkMode);
  Player::setNetPacketHandler(56, (Player::NetPacketHandler)(unsigned __int64)Player::onSafeRevive);
  Player::setNetPacketHandler(57, (Player::NetPacketHandler)(unsigned __int64)Player::onSiteRevive);
  Player::setNetPacketHandler(58, (Player::NetPacketHandler)(unsigned __int64)Player::onStrongRevive);
  Player::setNetPacketHandler(59, (Player::NetPacketHandler)(unsigned __int64)Player::onQueryChrInfo);
  Player::setNetPacketHandler(60, (Player::NetPacketHandler)(unsigned __int64)Player::onUpgradeLevel);
  Player::setNetPacketHandler(299, (Player::NetPacketHandler)(unsigned __int64)Player::checkPreventWallow);
  Player::setNetPacketHandler(114, (Player::NetPacketHandler)(unsigned __int64)Player::onQueryTaskList);
  Player::setNetPacketHandler(115, (Player::NetPacketHandler)(unsigned __int64)Player::onReceiveTask);
  Player::setNetPacketHandler(116, (Player::NetPacketHandler)(unsigned __int64)Player::onSubmitTask);
  Player::setNetPacketHandler(117, (Player::NetPacketHandler)(unsigned __int64)Player::onGiveUpTask);
  Player::setNetPacketHandler(118, (Player::NetPacketHandler)(unsigned __int64)Player::onSetTaskCanSubmit);
  Player::setNetPacketHandler(125, (Player::NetPacketHandler)(unsigned __int64)Player::onTalkWithNpc);
  Player::setNetPacketHandler(126, (Player::NetPacketHandler)(unsigned __int64)Player::onQuickDone);
  Player::setNetPacketHandler(127, (Player::NetPacketHandler)(unsigned __int64)Player::onTeleport);
  Player::setNetPacketHandler(128, (Player::NetPacketHandler)(unsigned __int64)Player::onTeleportActivity);
  Player::setNetPacketHandler(142, (Player::NetPacketHandler)(unsigned __int64)Player::onAddAction);
  Player::setNetPacketHandler(143, (Player::NetPacketHandler)(unsigned __int64)Player::onRemoveAction);
  Player::setNetPacketHandler(144, (Player::NetPacketHandler)(unsigned __int64)Player::onExchangeAction);
  Player::setNetPacketHandler(145, (Player::NetPacketHandler)(unsigned __int64)Player::onSetAutoFight);
  Player::setNetPacketHandler(146, (Player::NetPacketHandler)(unsigned __int64)Player::onSetSystemSetting);
  Player::setNetPacketHandler(149, (Player::NetPacketHandler)(unsigned __int64)Player::onBuyChrShopItem);
  Player::setNetPacketHandler(151, (Player::NetPacketHandler)(unsigned __int64)Player::onBuyBackChrShopItem);
  Player::setNetPacketHandler(152, (Player::NetPacketHandler)(unsigned __int64)Player::onBuyResource);
  Player::setNetPacketHandler(153, (Player::NetPacketHandler)(unsigned __int64)Player::onBuyTaskCount);
  Player::setNetPacketHandler(159, (Player::NetPacketHandler)(unsigned __int64)Player::onTeleportByItem);
  Player::setNetPacketHandler(161, (Player::NetPacketHandler)(unsigned __int64)Player::onClickPayButton);
  Player::setNetPacketHandler(162, (Player::NetPacketHandler)(unsigned __int64)Player::onMapEntered);
  Player::setNetPacketHandler(163, (Player::NetPacketHandler)(unsigned __int64)Player::onDebugCmd);
  Player::setNetPacketHandler(190, (Player::NetPacketHandler)(unsigned __int64)Player::onQueryKillerRankSelf);
  Player::setNetPacketHandler(197, (Player::NetPacketHandler)(unsigned __int64)Player::onGamePublicChat);
  Player::setNetPacketHandler(194, (Player::NetPacketHandler)(unsigned __int64)Player::onCrossPrivateChat);
  Player::setNetPacketHandler(333, (Player::NetPacketHandler)(unsigned __int64)Player::onUpdateFlyIconInt);
  Player::setNetPacketHandler(334, (Player::NetPacketHandler)(unsigned __int64)Player::onSetGuaJi);
  Player::setNetPacketHandler(438, (Player::NetPacketHandler)(unsigned __int64)Player::OnAskBossInfo);
  Player::setNetPacketHandler(830, (Player::NetPacketHandler)(unsigned __int64)Player::OnRequestActivityInfo);
  Player::setNetPacketHandler(836, (Player::NetPacketHandler)(unsigned __int64)Player::OnRequestActivityRankInfo);
  Player::setNetPacketHandler(833, (Player::NetPacketHandler)(unsigned __int64)Player::OnActivityGetDailyReward);
  Player::setNetPacketHandler(839, (Player::NetPacketHandler)(unsigned __int64)Player::OnActivityApplyCityWar);
  Player::setNetPacketHandler(480, (Player::NetPacketHandler)(unsigned __int64)Player::OnClickGame);
  Player::setNetPacketHandler(495, (Player::NetPacketHandler)(unsigned __int64)Player::OnKaiFuHuoDongOperator);
  Player::setNetPacketHandler(496, (Player::NetPacketHandler)(unsigned __int64)Player::OnKaiFuHuoDongOperator);
  Player::setNetPacketHandler(497, (Player::NetPacketHandler)(unsigned __int64)Player::OnKaiFuHuoDongOperator);
  Player::setNetPacketHandler(498, (Player::NetPacketHandler)(unsigned __int64)Player::OnKaiFuHuoDongOperator);
  Player::setNetPacketHandler(835, (Player::NetPacketHandler)(unsigned __int64)Player::OnActivityWorldBossGuWu);
  Player::setNetPacketHandler(527, (Player::NetPacketHandler)(unsigned __int64)Player::OnSubPkValus);
  Player::setNetPacketHandler(528, (Player::NetPacketHandler)(unsigned __int64)Player::OnLevelPrison);
  Player::setNetPacketHandler(870, (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteServerRequestInfo);
  Player::setNetPacketHandler(871, (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteServerGetRechargeGift);
  Player::setNetPacketHandler(872, (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteServerBuyDistinctGift);
  Player::setNetPacketHandler(873, (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteServerHuoYueduGift);
  Player::setNetPacketHandler(869, (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteBuyChangeNameCard);
  Player::setNetPacketHandler(868, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetUniteWingLevelUpReward);
  Player::setNetPacketHandler(887, (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteServerGetLianRechargeGift);
  Player::setNetPacketHandler(
    888,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnUniteServerGetChouJiangTimesReward);
  Player::setNetPacketHandler(846, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetKaiFuREcharge);
  Player::setNetPacketHandler(847, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetKaiFuChouJiang);
  Player::setNetPacketHandler(900, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenRequestInfo);
  Player::setNetPacketHandler(901, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetLandGift);
  Player::setNetPacketHandler(902, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetDrawGift);
  Player::setNetPacketHandler(907, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetOnlineGift);
  Player::setNetPacketHandler(908, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetWishGift);
  Player::setNetPacketHandler(903, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetLandSumGift);
  Player::setNetPacketHandler(
    904,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenBuyDailyLimitShopItem);
  Player::setNetPacketHandler(905, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetHuoYueDuSumGift);
  Player::setNetPacketHandler(
    909,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetDailyRechargeGift);
  Player::setNetPacketHandler(973, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetRechargeSumGift);
  Player::setNetPacketHandler(
    978,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetPetIllusionItemGift);
  Player::setNetPacketHandler(972, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetXiaoFeiSumGift);
  Player::setNetPacketHandler(845, (Player::NetPacketHandler)(unsigned __int64)Player::OnRequestMoYuShiJieRecord);
  Player::setNetPacketHandler(970, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenBuyGiftShopItem);
  Player::setNetPacketHandler(
    971,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetFaBaoCritBackItem);
  Player::setNetPacketHandler(974, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenBuyGiftShopItem2);
  Player::setNetPacketHandler(976, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenBuyGiftItem);
  Player::setNetPacketHandler(
    975,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetEquipUpStarBackItem);
  Player::setNetPacketHandler(260, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenBuyPetGift);
  Player::setNetPacketHandler(540, (Player::NetPacketHandler)(unsigned __int64)Player::OnFengHao);
  Player::setNetPacketHandler(977, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetRechargeBack);
  Player::setNetPacketHandler(985, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetEquipQingYiGift);
  Player::setNetPacketHandler(
    986,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenGetFriendQingYiGift);
  Player::setNetPacketHandler(988, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenRandScoreDrawGift);
  Player::setNetPacketHandler(989, (Player::NetPacketHandler)(unsigned __int64)Player::OnDoubleElevenRandGouWuChe);
  Player::setNetPacketHandler(983, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetLianRechargeReward);
  Player::setNetPacketHandler(541, (Player::NetPacketHandler)(unsigned __int64)Player::OnSetFcmTime);
  Player::setNetPacketHandler(990, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonNpc);
  Player::setNetPacketHandler(991, (Player::NetPacketHandler)(unsigned __int64)Player::onComBackCity);
  Player::setNetPacketHandler(624, (Player::NetPacketHandler)(unsigned __int64)Player::OnCheckAccelerator);
  Player::setNetPacketHandler(661, (Player::NetPacketHandler)(unsigned __int64)Player::OnZHYYHDRequestInfo);
  Player::setNetPacketHandler(662, (Player::NetPacketHandler)(unsigned __int64)Player::OnZHYYHDGetRechargeDailyReward);
  Player::setNetPacketHandler(
    663,
    (Player::NetPacketHandler)(unsigned __int64)Player::OnZHYYHDGetRechargeTeamShopDailyReward);
  Player::setNetPacketHandler(664, (Player::NetPacketHandler)(unsigned __int64)Player::OnZHYYHDBuyOnceShopItem);
  Player::setNetPacketHandler(681, (Player::NetPacketHandler)(unsigned __int64)Player::OnOpenBetaOperator);
  Player::setNetPacketHandler(682, (Player::NetPacketHandler)(unsigned __int64)Player::OnOpenBetaOperator);
  Player::setNetPacketHandler(689, (Player::NetPacketHandler)(unsigned __int64)Player::OnOpenBetaOperator);
  Player::setNetPacketHandler(683, (Player::NetPacketHandler)(unsigned __int64)Player::OnFestivalActivityOperator);
  Player::setNetPacketHandler(684, (Player::NetPacketHandler)(unsigned __int64)Player::OnFestivalActivityOperator);
  Player::setNetPacketHandler(855, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(856, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(857, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(865, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(866, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(862, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(863, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(864, (Player::NetPacketHandler)(unsigned __int64)Player::OnEquipBackOperator);
  Player::setNetPacketHandler(669, (Player::NetPacketHandler)(unsigned __int64)Player::OnAskLastFullHpTime);
  Player::setNetPacketHandler(670, (Player::NetPacketHandler)(unsigned __int64)Player::OnFullHp);
  Player::setNetPacketHandler(513, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetMiniClientReward);
  Player::setNetPacketHandler(205, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetMapBossInfo);
  Player::setNetPacketHandler(204, (Player::NetPacketHandler)(unsigned __int64)Player::OnGetLevelBossInfo);
  Player::setNetPacketHandler(680, (Player::NetPacketHandler)(unsigned __int64)Player::OnPaiMaiHangHanHua);
  Player::setNetPacketHandler(207, (Player::NetPacketHandler)(unsigned __int64)Player::OnEnterSpecialBossMap);
  Player::setNetPacketHandler(208, (Player::NetPacketHandler)(unsigned __int64)Player::OnLeaveSpecialBossMap);
  Player::setNetPacketHandler(561, (Player::NetPacketHandler)(unsigned __int64)Player::OnRollTheDice);
  Player::setNetPacketHandler(562, (Player::NetPacketHandler)(unsigned __int64)Player::OnCycleTowerEvent);
  Player::setNetPacketHandler(563, (Player::NetPacketHandler)(unsigned __int64)Player::ChatValidateed);
  Player::setNetPacketHandler(564, (Player::NetPacketHandler)(unsigned __int64)Player::onBuyXuWuValue);
  Player::setNetPacketHandler(996, (Player::NetPacketHandler)(unsigned __int64)Player::onTeleportByItem);
  Player::setNetPacketHandler(995, (Player::NetPacketHandler)(unsigned __int64)Player::onSwitchMap);
  Player::setNetPacketHandler(994, (Player::NetPacketHandler)(unsigned __int64)Player::onMove);
  Player::setNetPacketHandler(982, (Player::NetPacketHandler)(unsigned __int64)Player::OnChristmasDuiHuan);
  Player::setNetPacketHandler(937, (Player::NetPacketHandler)(unsigned __int64)Player::onDungeonRandom);
  Player::setNetPacketHandler(938, (Player::NetPacketHandler)(unsigned __int64)Player::OnBuyRandomPosTimes);
  Player::setNetPacketHandler(939, (Player::NetPacketHandler)(unsigned __int64)Player::OnBuyJingLiValue);
}


#####################################
void __cdecl Player::init(Player *const this, PlayerDBData *const dbData)
{
  int32_t pk_time; // ebx
  Player *v3; // rbx
  int64_t Tick; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // eax
  CfgData *v7; // rax
  const EnergyCfg *EnergyCfg; // rax
  int32_t Now; // eax
  int32_t v10; // eax
  int32_t v11; // eax
  CfgData *v12; // rax
  int32_t ServerDiffDay; // eax
  CfgData *v14; // rax
  int32_t v15; // eax
  int32_t Record; // eax
  CEquipManager *v17; // rax
  int32_t MapId; // r14d
  int32_t v19; // r13d
  CharId_t Cid; // r12
  int8_t m_connid; // bl
  DBService *v22; // rax
  CfgData *v23; // rax
  int32_t v24; // ebx
  MapManager *v25; // rax
  int32_t v26; // eax
  int32_t RunnerId; // eax
  int8_t ConnId; // bl
  DBService *v29; // rax
  int8_t v30; // bl
  CActivityManager *v31; // rax
  FamilyId_t FamilyId; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  bool v35; // bl
  CharId_t v36; // r12
  int8_t v37; // bl
  DBService *v38; // rax
  int32_t v39; // r12d
  Player *v40; // rsi
  const char *v41; // rbx
  int v42; // eax
  DBService *v43; // rax
  int64_t v44; // rax
  tm v45; // [rsp+0h] [rbp-1160h] BYREF
  PlayerDBData *dbDataa; // [rsp+40h] [rbp-1120h]
  Player *thisa; // [rsp+48h] [rbp-1118h]
  char LogString[4096]; // [rsp+50h] [rbp-1110h] BYREF
  Log360 Stu; // [rsp+1050h] [rbp-110h] BYREF
  EnergyCfg Ener; // [rsp+1080h] [rbp-E0h] BYREF
  Position pos; // [rsp+10B0h] [rbp-B0h]
  std::string __lhs; // [rsp+10C0h] [rbp-A0h] BYREF
  std::string Param; // [rsp+10D0h] [rbp-90h] BYREF
  char v54; // [rsp+10DFh] [rbp-81h] BYREF
  _BYTE v55[16]; // [rsp+10E0h] [rbp-80h] BYREF
  std::string v56; // [rsp+10F0h] [rbp-70h] BYREF
  std::string p_PickString; // [rsp+1100h] [rbp-60h] BYREF
  char v58; // [rsp+1113h] [rbp-4Dh] BYREF
  int32_t nowTime; // [rsp+1114h] [rbp-4Ch]
  CfgMapRegion *pCfgRegion; // [rsp+1118h] [rbp-48h]
  FamilyId_t winFamily; // [rsp+1120h] [rbp-40h]
  int32_t offlineTime; // [rsp+1128h] [rbp-38h]
  int32_t nOffLineDay; // [rsp+112Ch] [rbp-34h]
  Map *pTempMap; // [rsp+1130h] [rbp-30h]
  int32_t nTime; // [rsp+1138h] [rbp-28h]
  int32_t nDay; // [rsp+113Ch] [rbp-24h]

  thisa = this;
  dbDataa = dbData;
  nowTime = Unit::getNow(this);
  this->m_connid = dbData->connid;
  thisa->m_cgindex = dbDataa->cgindex;
  qmemcpy(&thisa->m_chr, &dbDataa->chr.data, sizeof(thisa->m_chr));
  pk_time = thisa->m_chr.pk_time;
  if ( pk_time <= Unit::getNow(thisa) )
    thisa->m_chr.pk_time = 0;
  else
    thisa->m_chr.pk_time = thisa->m_chr.pk_time;
  if ( !thisa->m_chr.pk_mode )
    thisa->m_chr.pk_mode = 1;
  thisa->m_pkMode_bk = thisa->m_chr.pk_mode;
  thisa->m_levelStartTime = nowTime;
  thisa->m_lastPkValueTick = Unit::getTick(thisa);
  thisa->m_nLastSaveOnlineTime = nowTime;
  thisa->m_chr.last_login_time = nowTime;
  qmemcpy(&thisa->m_sysUser, &dbDataa->sysUser.data, sizeof(thisa->m_sysUser));
  thisa->m_sysUser.last_login_time = nowTime;
  thisa->m_sysUser.total_offline_time += nowTime - thisa->m_sysUser.last_logout_time;
  if ( thisa->m_sysUser.total_offline_time > 17999 )
  {
    thisa->m_sysUser.total_online_time = 0;
    thisa->m_sysUser.total_offline_time = 0;
  }
  thisa->m_sysUserPreventWallow = dbDataa->sysUserPreventWallow.data;
  ChrTask::init(&thisa->m_task, thisa, &dbDataa->taskData.taskVt);
  memcpy(thisa->m_actions, dbDataa->actionData.actionArry, sizeof(thisa->m_actions));
  qmemcpy(&thisa->m_autoFight, &dbDataa->autoFight.data, sizeof(thisa->m_autoFight));
  std::string::operator=(&thisa->m_systemSetting, &dbDataa->systemSetting.data);
  v3 = thisa;
  Unit::getLocalNow(&v45, thisa);
  v3->m_lastLocalNow = v45;
  Tick = Unit::getTick(thisa);
  thisa->m_lastSaveTick = Tick;
  Player::initBuff(thisa, &dbDataa->buffData.buffVt);
  CExtSystemMgr::OnLoadFromDB(&thisa->m_ExtSysMgr, dbDataa);
  if ( thisa->m_sysUser.last_logout_time <= 0 )
  {
    Player::updateRecord(thisa, 1016, 0);
    Player::updateRecord(thisa, 2003, 0);
    Player::updateRecord(thisa, 1908, 100000);
    v7 = Answer::Singleton<CfgData>::instance();
    EnergyCfg = CfgData::GetEnergyCfg(v7);
    EnergyCfg::EnergyCfg(&Ener, EnergyCfg);
    Player::updateRecord(thisa, 37305, Ener.MaxEnergy);
    Now = Unit::getNow(thisa);
    Player::updateRecord(thisa, 37307, Now);
    Player::SendJingLiValue(thisa);
    EnergyCfg::~EnergyCfg(&Ener);
  }
  else
  {
    offlineTime = nowTime - thisa->m_sysUser.last_logout_time;
    OperateLimit = Player::GetOperateLimit(thisa);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1019, offlineTime);
    nOffLineDay = Answer::DayTime::daydiffBw(thisa->m_sysUser.last_logout_time, nowTime);
    LimitCount = CExtOperateLimit::GetLimitCount(&thisa->m_extOperateLimit, 37007);
    if ( LimitCount < nOffLineDay )
      CExtOperateLimit::UpdateLimitCount(&thisa->m_extOperateLimit, 37007, nOffLineDay);
  }
  v10 = (*((__int64 (__fastcall **)(Player *))thisa->_vptr_Entity + 9))(thisa);
  CFunctionOpen::InitFunctionOpen(&thisa->m_PlayerFunctionOpen, 0, v10);
  v11 = (*((__int64 (__fastcall **)(Player *))thisa->_vptr_Entity + 9))(thisa);
  CFunctionOpen::InitFunctionOpenMailByLevel(&thisa->m_PlayerFunctionOpen, v11);
  v12 = Answer::Singleton<CfgData>::instance();
  ServerDiffDay = CfgData::getServerDiffDay(v12, SERVER_TYPE::SVT_NORMAL);
  CFunctionOpen::InitFunctionOpenMailByKaiFuDay(&thisa->m_PlayerFunctionOpen, ServerDiffDay + 1);
  v14 = Answer::Singleton<CfgData>::instance();
  v15 = CfgData::getServerDiffDay(v14, SERVER_TYPE::SVT_NORMAL);
  CFunctionOpen::CheckFunctionOpenMailByKaiFuDay(&thisa->m_PlayerFunctionOpen, v15 + 1);
  Player::refreshDailyCheck(thisa, 0);
  Player::checkFestivalVersion(thisa);
  if ( dbDataa->sysUser.data.gold_pay > 0 )
    Player::syncGold(thisa, dbDataa->sysUser.data.gold_pay);
  CExtCharTitle::InitTitle(&thisa->m_extCharTitle);
  Record = Player::getRecord(thisa, 2008);
  thisa->m_InBossHomeTime = Record;
  v17 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::SendPlayerEquipInfo(v17, thisa);
  Player::InitSysSetting(thisa);
  Player::setSyncStatusFlag(thisa);
  Player::minuteCheck(thisa, 0);
  Player::recalcAttr(thisa, 1, 1);
  Unit::setHP(thisa, dbDataa->chr.data.hp);
  Unit::setMP(thisa, dbDataa->chr.data.mp);
  Unit::setKunLi(thisa, dbDataa->chr.data.kun_li);
  Unit::adjustUnitAttr(thisa);
  if ( !Unit::isAlive(thisa) )
    thisa->m_bDie = 1;
  MapId = StaticObj::getMapId(thisa);
  v19 = Unit::getNow(thisa);
  Cid = Player::getCid(thisa);
  m_connid = thisa->m_connid;
  v22 = Answer::Singleton<DBService>::instance();
  DBService::logPlayerLogin(v22, m_connid, Cid, 1, v19, MapId);
  v23 = Answer::Singleton<CfgData>::instance();
  pCfgRegion = CfgData::getMapRegion(v23, 20001);
  if ( pCfgRegion )
  {
    v24 = pCfgRegion->mapid;
    v25 = Answer::Singleton<MapManager>::instance();
    pTempMap = MapManager::GetMap(v25, v24);
    if ( pTempMap )
    {
      pos = Map::getRandomWalkablePositionInRegion(pTempMap, pCfgRegion);
      if ( pos.x >= 0 && pos.y >= 0 )
      {
        v26 = Map::GetMapId(pTempMap);
        thisa->m_oldPosition.mapid = v26;
        thisa->m_oldPosition.x = pos.x;
        thisa->m_oldPosition.y = pos.y;
        RunnerId = Map::GetRunnerId(pTempMap);
        thisa->m_oldPosition.runnerId = RunnerId;
      }
    }
  }
  if ( Answer::DayTime::daydiff(dbDataa->chr.data.last_login_time) > 0 )
  {
    nTime = Answer::DayTime::dayzero(dbDataa->chr.data.create_time);
    nDay = Answer::DayTime::daydiff(dbDataa->chr.data.create_time);
    if ( nDay <= 30 )
    {
      ConnId = Player::getConnId(thisa);
      v29 = Answer::Singleton<DBService>::instance();
      DBService::LogPlayerStay(v29, ConnId, nTime, nDay);
    }
  }
  v30 = Player::getConnId(thisa);
  v31 = Answer::Singleton<CActivityManager>::instance();
  winFamily = CActivityManager::GetCityWarWinner(v31, v30);
  if ( winFamily > 0 )
  {
    FamilyId = Player::getFamilyId(thisa);
    if ( FamilyId == winFamily )
      Player::SetActState(thisa, 1);
  }
  if ( Player::IsMiniClient(thisa) )
  {
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(thisa);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 7, 0, 0);
  }
  Player::GetFromWay((const Player *const)&__lhs);
  v35 = std::operator==<char>(&__lhs, "kkk");
  std::string::~string(&__lhs);
  if ( v35 && Player::getRecord(thisa, 1920) <= 0 )
  {
    Player::updateRecord(thisa, 1920, 1);
    std::allocator<char>::allocator(&v54);
    std::string::string(&Param, byte_8E9580);
    v36 = Player::getCid(thisa);
    v37 = Player::getConnId(thisa);
    v38 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v38, v37, v36, 6398, &Param, 0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(&v54);
  }
  Player::sendUpdateSocialPlayerInfo(thisa, PlayerInfoIndex::PII_LOAD, 1);
  Player::ResetJingLi(thisa);
  memset(&Stu, 0, sizeof(Stu));
  std::string::string(&Stu.Interface);
  std::string::string(&Stu.passport);
  std::string::string(&Stu.LogString);
  std::string::operator=(&Stu, "login");
  Stu.UseSid = Player::getSid(thisa);
  Player::GetPassport((Player *const)v55);
  std::string::operator=(&Stu.passport, v55);
  std::string::~string(v55);
  Stu.Cid = Player::getCid(thisa);
  memset(LogString, 0, sizeof(LogString));
  v39 = thisa->m_chr.mapid;
  v40 = thisa;
  Player::getIP((Player *const)&v56);
  v41 = (const char *)std::string::c_str(&v56);
  v42 = (*((__int64 (__fastcall **)(Player *, Player *))thisa->_vptr_Entity + 9))(thisa, v40);
  snprintf(LogString, 0xFFFu, "level=%d&ip=%s&map_id=%d", v42, v41, v39);
  std::string::~string(&v56);
  std::string::operator=(&Stu.LogString, LogString);
  LOBYTE(v41) = thisa->m_connid;
  v43 = Answer::Singleton<DBService>::instance();
  DBService::log360(v43, (int8_t)v41, &Stu);
  Player::LoginGongGao(thisa);
  std::allocator<char>::allocator(&v58);
  std::string::string(&p_PickString, &thisa->m_autoFight);
  CharLittlerHelper::parsePickString(&thisa->m_CharLittlerhelper, &p_PickString);
  std::string::~string(&p_PickString);
  std::allocator<char>::~allocator(&v58);
  v44 = Unit::getTick(thisa);
  thisa->m_TeJieCRI = v44;
  CExtSystemMgr::InitSystem(&thisa->m_ExtSysMgr);
  Log360::~Log360(&Stu);
}


#####################################
void __cdecl Player::LoginGongGao(Player *const this)
{
  int8_t ConnId; // bl
  CActivityManager *v2; // rax
  int8_t v4; // bl
  GameService *v5; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v8; // bl
  GameService *v9; // rax
  CharId_t v10; // rbx
  CRankMirror *v11; // rax
  int8_t v12; // bl
  GameService *v13; // rax
  CharId_t v14; // rax
  uint32_t v15; // eax
  int8_t v16; // bl
  GameService *v17; // rax
  CActivityManager *v18; // rax
  CharId_t v19; // rax
  int8_t v21; // bl
  GameService *v22; // rax
  CharId_t v23; // rax
  uint32_t v24; // eax
  int8_t v25; // bl
  GameService *v26; // rax
  std::string val; // [rsp+10h] [rbp-60h] BYREF
  std::string v28; // [rsp+20h] [rbp-50h] BYREF
  std::string v29; // [rsp+30h] [rbp-40h] BYREF
  CharId_t peerless; // [rsp+38h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+40h] [rbp-30h]
  Answer::NetPacket *packet_0; // [rsp+48h] [rbp-28h]
  CharId_t CrossTowerWinner; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet_1; // [rsp+58h] [rbp-18h]

  ConnId = Player::getConnId(this);
  v2 = Answer::Singleton<CActivityManager>::instance();
  peerless = CActivityManager::GetPeerlessWarWinner(v2, ConnId);
  if ( peerless > 0 && Player::getCid(this) == peerless )
  {
    v4 = Player::getConnId(this);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, v4, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 481);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v8 = Player::getConnId(this);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v9, v8, packet);
    }
  }
  v10 = Player::getCid(this);
  v11 = Answer::Singleton<CRankMirror>::instance();
  if ( CRankMirror::IsJobBattleFirst(v11, v10) )
  {
    v12 = Player::getConnId(this);
    v13 = Answer::Singleton<GameService>::instance();
    packet_0 = GameService::popNetpacket(v13, v12, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet_0 )
    {
      Answer::NetPacket::writeInt32(packet_0, 482);
      Player::getName((const Player *const)&v28);
      Answer::NetPacket::writeUTF8(packet_0, &v28);
      std::string::~string(&v28);
      v14 = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet_0, v14);
      v15 = Answer::NetPacket::getWOffset(packet_0);
      Answer::NetPacket::setSize(packet_0, v15);
      v16 = Player::getConnId(this);
      v17 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v17, v16, packet_0);
    }
  }
  v18 = Answer::Singleton<CActivityManager>::instance();
  CrossTowerWinner = CActivityManager::GetCrossTowerWinner(v18);
  if ( CrossTowerWinner > 0 )
  {
    v19 = Player::getCid(this);
    if ( v19 == CrossTowerWinner )
    {
      v21 = Player::getConnId(this);
      v22 = Answer::Singleton<GameService>::instance();
      packet_1 = GameService::popNetpacket(v22, v21, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet_1 )
      {
        Answer::NetPacket::writeInt32(packet_1, 518);
        Player::getName((const Player *const)&v29);
        Answer::NetPacket::writeUTF8(packet_1, &v29);
        std::string::~string(&v29);
        v23 = Player::getCid(this);
        Answer::NetPacket::writeInt64(packet_1, v23);
        v24 = Answer::NetPacket::getWOffset(packet_1);
        Answer::NetPacket::setSize(packet_1, v24);
        v25 = Player::getConnId(this);
        v26 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v26, v25, packet_1);
      }
    }
  }
}


#####################################
void __cdecl Player::initBuff(Player *const this, const MemChrBuffVector *const buffVt)
{
  int32_t itemId; // ebx
  CfgData *v3; // rax
  int32_t buffId; // ebx
  CfgData *v5; // rax
  int32_t v6; // edx
  ItemBuff *v7; // rbx
  int32_t time; // ebx
  const MemChrBuff *v9; // rax
  __gnu_cxx::__normal_iterator<const MemChrBuff*,std::vector<MemChrBuff> > it; // [rsp+20h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBuff*,std::vector<MemChrBuff> > __rhs; // [rsp+30h] [rbp-60h] BYREF
  UnitHandle launcher; // [rsp+40h] [rbp-50h] BYREF
  CfgItem *pCfgItem; // [rsp+58h] [rbp-38h]
  CfgBuff *pCfgBuff; // [rsp+60h] [rbp-30h]
  ItemBuff *pBuff; // [rsp+68h] [rbp-28h]

  for ( it._M_current = std::vector<MemChrBuff>::begin(buffVt)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBuff const*,std::vector<MemChrBuff>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<MemChrBuff>::end(buffVt)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBuff const*,std::vector<MemChrBuff>>(&it, &__rhs) )
      break;
    itemId = __gnu_cxx::__normal_iterator<MemChrBuff const*,std::vector<MemChrBuff>>::operator->(&it)->itemId;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfgItem = CfgData::getItem(v3, itemId);
    buffId = __gnu_cxx::__normal_iterator<MemChrBuff const*,std::vector<MemChrBuff>>::operator->(&it)->buffId;
    v5 = Answer::Singleton<CfgData>::instance();
    pCfgBuff = CfgData::getBuff(v5, buffId);
    if ( pCfgItem && pCfgBuff )
    {
      launcher.id = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 12))(this);
      launcher.type = v6;
      v7 = (ItemBuff *)operator new(0x68u);
      ItemBuff::ItemBuff(v7, this, pCfgBuff, &launcher);
      pBuff = v7;
      if ( v7 )
      {
        time = __gnu_cxx::__normal_iterator<MemChrBuff const*,std::vector<MemChrBuff>>::operator->(&it)->time;
        v9 = __gnu_cxx::__normal_iterator<MemChrBuff const*,std::vector<MemChrBuff>>::operator->(&it);
        ItemBuff::init(pBuff, v9->itemId, time);
        Unit::addBuff(this, pBuff);
      }
    }
  }
}


#####################################
void __cdecl Player::reset(Player *const this)
{
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  Unit::reset(this);
  while ( 1 )
  {
    packet = Answer::SafeQueue<Answer::NetPacket *>::pop(&this->m_netPackets);
    if ( !packet )
      break;
    Answer::NetPacket::destroy(packet);
  }
  this->m_cgindex = 0;
  bzero(&this->m_chr, 0xA8u);
  bzero(&this->m_sysUser, 0x120u);
  bzero(&this->m_sysUserPreventWallow, 0x48u);
  this->m_pkMode_bk = 0;
  this->m_lastPkValueTick = 0;
  this->m_levelStartTime = 0;
  this->m_eventHP = 0;
  this->m_nCamp = 0;
  this->m_nGuaJi = 0;
  this->m_nLastJumpTime = 0;
  this->m_nLastJumpEnergyReviveTime = 0;
  this->m_nJumpEnergy = 0;
  ChrTask::reset(&this->m_task);
  bzero(this->m_actions, 0x68u);
  bzero(&this->m_autoFight, 0x4B2u);
  std::string::operator=(&this->m_systemSetting, byte_8E9580);
  bzero(&this->m_lastLocalNow, 0x38u);
  this->m_lastSaveTick = 0;
  this->m_lastPoolTick = 0;
  this->m_lastBingFengZouLangAddExpTick = 0;
  this->m_lastBingFengZouLangAddPointTick = 0;
  bzero(&this->m_oldPosition, 0x14u);
  this->m_plantId = 0;
  this->m_startGatherTick = 0;
  this->m_trailer = 0;
  this->m_needSyncStatus = 0;
  this->m_needSyncToTeam = 0;
  this->m_needRecalAttr = 0;
  this->m_StartProtect = 0;
  this->m_nDieTick = 0;
  this->m_InBossHomeTime = 0;
  std::map<int,int>::clear(&this->m_SystemSetting);
  this->m_lastMPTick = 0;
  this->m_nBFZLLeaveTick = 0;
  this->m_LastCheckAccelerator = 0;
  this->m_AcceleratorTime = 0;
  this->m_isBackCity = 0;
  this->m_nLastSaveOnlineTime = 0;
  this->m_LastUpdateWastelands = 0;
  this->m_Battle = 0;
  this->m_ActState = 0;
  this->m_PlantState = 0;
  this->m_LastPickTick = 0;
  this->m_TeJieCRI = 0;
  this->m_DamageTimes = 0;
  std::set<int>::clear(&this->m_PacketProcSet);
  std::map<int,int>::clear(&this->m_BeiGongAttr);
  CExtSystemMgr::OnCleanUp(&this->m_ExtSysMgr);
}


#####################################
bool __cdecl Player::appendInfo(Player *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  CharId_t Cid; // rdx
  FamilyId_t FamilyId; // rdx
  int8_t FamilyPosition; // dl
  Sex_t Sex; // dl
  Job_t Job; // dl
  int16_t v9; // dx
  int8_t IsBuleName; // al
  int32_t PkProtectTime; // ebx
  int32_t v12; // ebx
  int32_t v13; // eax
  int16_t x; // dx
  int16_t y; // dx
  int16_t v16; // dx
  int16_t v17; // dx
  int32_t v18; // edx
  int32_t v19; // edx
  int32_t v20; // edx
  int32_t v21; // edx
  int16_t v22; // dx
  int8_t Head; // dl
  int8_t TeamStatus; // dl
  int32_t Action; // edx
  int32_t MainWeaponId; // edx
  int32_t ClothesId; // edx
  int32_t WingId; // edx
  int32_t WingEquipPolishSuitId; // edx
  CVip *PlayerVip; // rax
  int8_t VipType; // dl
  CVip *v32; // rax
  int8_t VipLevel; // dl
  int8_t JueWei; // dl
  int8_t Camp; // dl
  int32_t ShiZhuangWeapon; // edx
  int32_t ShiZhuangClothes; // edx
  int32_t EffectId; // edx
  int32_t ShiZhuangFeet; // edx
  int32_t CarrierId; // edx
  int8_t ActState; // dl
  int32_t Record; // edx
  int8_t IsFitting; // al
  int32_t v44; // edx
  int32_t v45; // edx
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  std::string v47; // [rsp+20h] [rbp-20h] BYREF

  if ( !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  Cid = Player::getCid(this);
  Answer::NetPacket::writeInt64(packet, Cid);
  Player::getName((const Player *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  FamilyId = Player::getFamilyId(this);
  Answer::NetPacket::writeInt64(packet, FamilyId);
  FamilyPosition = Player::getFamilyPosition(this);
  Answer::NetPacket::writeInt8(packet, FamilyPosition);
  Player::getFamilyName((const Player *const)&v47);
  Answer::NetPacket::writeUTF8(packet, &v47);
  std::string::~string(&v47);
  Sex = Player::getSex(this);
  Answer::NetPacket::writeInt8(packet, Sex);
  Job = Player::getJob(this);
  Answer::NetPacket::writeInt8(packet, Job);
  Answer::NetPacket::writeInt8(packet, 0);
  v9 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  Answer::NetPacket::writeInt16(packet, v9);
  Answer::NetPacket::writeInt8(packet, this->m_chr.pk_mode);
  Answer::NetPacket::writeInt32(packet, this->m_chr.pk_value);
  IsBuleName = CExtFightChecker::IsBuleName(&this->m_extFightChecker);
  Answer::NetPacket::writeInt8(packet, IsBuleName);
  PkProtectTime = Player::getPkProtectTime(this);
  if ( PkProtectTime - Unit::getNow(this) <= 0 )
  {
    v13 = 0;
  }
  else
  {
    v12 = Player::getPkProtectTime(this);
    v13 = v12 - Unit::getNow(this);
  }
  Answer::NetPacket::writeInt32(packet, v13);
  x = StaticObj::getCurrentTile(this).x;
  Answer::NetPacket::writeInt16(packet, x);
  y = StaticObj::getCurrentTile(this).y;
  Answer::NetPacket::writeInt16(packet, y);
  v16 = Unit::getTargetTile(this).x;
  Answer::NetPacket::writeInt16(packet, v16);
  v17 = Unit::getTargetTile(this).y;
  Answer::NetPacket::writeInt16(packet, v17);
  v18 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 26))(this);
  Answer::NetPacket::writeInt32(packet, v18);
  v19 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 27))(this);
  Answer::NetPacket::writeInt32(packet, v19);
  v20 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 24))(this);
  Answer::NetPacket::writeInt32(packet, v20);
  v21 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 25))(this);
  Answer::NetPacket::writeInt32(packet, v21);
  Unit::packageBuffList(this, packet);
  v22 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 28))(this);
  Answer::NetPacket::writeInt16(packet, v22);
  Head = Player::getHead(this);
  Answer::NetPacket::writeInt8(packet, Head);
  TeamStatus = Player::GetTeamStatus(this);
  Answer::NetPacket::writeInt8(packet, TeamStatus);
  Action = Player::getAction(this);
  Answer::NetPacket::writeInt32(packet, Action);
  Answer::NetPacket::writeInt8(packet, this->m_PlantState);
  MainWeaponId = Player::getMainWeaponId(this);
  Answer::NetPacket::writeInt32(packet, MainWeaponId);
  ClothesId = Player::getClothesId(this);
  Answer::NetPacket::writeInt32(packet, ClothesId);
  WingId = Player::getWingId(this);
  Answer::NetPacket::writeInt32(packet, WingId);
  WingEquipPolishSuitId = CGoblin::GetWingEquipPolishSuitId(&this->m_CGoblin);
  Answer::NetPacket::writeInt32(packet, WingEquipPolishSuitId);
  PlayerVip = Player::GetPlayerVip(this);
  VipType = CVip::GetVipType(PlayerVip);
  Answer::NetPacket::writeInt8(packet, VipType);
  v32 = Player::GetPlayerVip(this);
  VipLevel = CVip::GetVipLevel(v32);
  Answer::NetPacket::writeInt8(packet, VipLevel);
  JueWei = CExtCharJueWei::GetJueWei(&this->m_extCharJueWei);
  Answer::NetPacket::writeInt8(packet, JueWei);
  CExtCharTitle::AppendDressTitle(&this->m_extCharTitle, packet);
  Camp = Player::GetCamp(this);
  Answer::NetPacket::writeInt8(packet, Camp);
  Answer::NetPacket::writeInt8(packet, 0);
  ShiZhuangWeapon = Player::getShiZhuangWeapon(this);
  Answer::NetPacket::writeInt32(packet, ShiZhuangWeapon);
  ShiZhuangClothes = Player::getShiZhuangClothes(this);
  Answer::NetPacket::writeInt32(packet, ShiZhuangClothes);
  EffectId = CShiZhuang::GetEffectId(&this->m_extShiZhuang);
  Answer::NetPacket::writeInt32(packet, EffectId);
  ShiZhuangFeet = Player::getShiZhuangFeet(this);
  Answer::NetPacket::writeInt32(packet, ShiZhuangFeet);
  CExtCharTencent::AppendInfo(&this->m_extCharTencent, packet);
  CVplan::AppendYYInfo(&this->m_Vplan, packet);
  CVplan::AppendSwVipInfo(&this->m_Vplan, packet);
  Answer::NetPacket::writeInt8(packet, this->m_connid);
  Answer::NetPacket::writeInt8(packet, 0);
  CarrierId = CExtCharCarrier::GetCarrierId(&this->m_extCharCarrier);
  Answer::NetPacket::writeInt32(packet, CarrierId);
  ActState = Player::GetActState(this);
  Answer::NetPacket::writeInt8(packet, ActState);
  Record = Player::getRecord(this, 3);
  Answer::NetPacket::writeInt32(packet, Record);
  IsFitting = CExtCharPet::IsFitting(&this->m_extCharPet);
  Answer::NetPacket::writeInt8(packet, IsFitting);
  v44 = Player::getRecord(this, 1148);
  Answer::NetPacket::writeInt32(packet, v44);
  v45 = Player::getRecord(this, 1153);
  Answer::NetPacket::writeInt32(packet, v45);
  return 1;
}


#####################################
int32_t __cdecl Player::switchMap(Player *const this, Map *pMap, int32_t x, int32_t y, bool isFly)
{
  int32_t v5; // ebx
  int64_t MapId; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  int8_t ConnId; // bl
  DBService *v11; // rax
  int32_t v12; // ebx
  int32_t GongGaoId; // ecx
  ChrTask *Task; // rax
  int32_t RunnerId; // eax
  int64_t v17; // r13
  int16_t v18; // r12
  int8_t v19; // bl
  GameService *v20; // rax
  CfgData *v22; // rax
  int32_t v23; // edx
  Buff *v24; // rbx
  MapManager *v25; // rax
  int64_t v26; // r13
  int16_t v27; // r12
  int8_t v28; // bl
  GameService *v29; // rax
  ChangeMapLog stu; // [rsp+40h] [rbp-A0h] BYREF
  Position playerPos; // [rsp+70h] [rbp-70h]
  _BYTE v35[16]; // [rsp+80h] [rbp-60h] BYREF
  UnitHandle launcher; // [rsp+90h] [rbp-50h] BYREF
  int32_t err; // [rsp+A8h] [rbp-38h]
  int32_t nRunnerId; // [rsp+ACh] [rbp-34h]
  CfgBuff *cfgBuff; // [rsp+B0h] [rbp-30h]
  Buff *buff; // [rsp+B8h] [rbp-28h]

  if ( !this->m_pMap || !pMap || this->m_pMap == pMap )
    return 10002;
  err = (*((__int64 (__fastcall **)(Map *, Player *const))pMap->_vptr_Map + 4))(pMap, this);
  if ( err )
  {
    MapId = Map::GetMapId(pMap);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v9 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v9, m_connid, m_cgindex, 0x10u, err, MapId);
  }
  else if ( StaticObj::InDungeon(this) )
  {
    Player::leaveDungeon(this);
    return 0;
  }
  else
  {
    playerPos = StaticObj::getCurrentTile(this);
    nRunnerId = StaticObj::GetRunnerId(this);
    memset(&stu.sName, 0, 32);
    std::string::string(&stu.sName);
    stu.nCid = Player::getCid(this);
    Player::getName((const Player *const)v35);
    std::string::operator=(&stu.sName, v35);
    std::string::~string(v35);
    stu.nCurMapId = StaticObj::getMapId(this);
    stu.nCurX = StaticObj::getCurrentTile(this).x;
    stu.nCurY = StaticObj::getCurrentTile(this).y;
    stu.nTarMapId = Map::GetMapId(pMap);
    stu.nTarX = x;
    stu.nTarY = y;
    ConnId = Player::getConnId(this);
    v11 = Answer::Singleton<DBService>::instance();
    DBService::LogChangeMap(v11, ConnId, &stu);
    Player::setOldPosition(this);
    Player::BreakGather(this, 1);
    Player::broadcastLeave(this);
    (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
    v12 = Map::GetMapId(pMap);
    GongGaoId = Map::GetGongGaoId(pMap);
    Player::EnterMapGongGao(this, GongGaoId, v12);
    if ( Player::getRecord(this, 2118) <= 0 )
    {
      Task = Player::GetTask(this);
      if ( !ChrTask::isDoingTaskType(Task, 42) && Map::IsXinMoCun(pMap) )
        CMoneyRewardTask::InitXinMoTask(&this->m_CMoneyRewardTask);
    }
    RunnerId = Map::GetRunnerId(pMap);
    if ( RunnerId == nRunnerId )
    {
      v17 = Map::GetMapId(pMap);
      v18 = this->m_cgindex;
      v19 = this->m_connid;
      v20 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v20, v19, v18, 0x10u, v17);
      (*((void (__fastcall **)(Map *, Player *const, _QWORD, _QWORD))pMap->_vptr_Map + 15))(
        pMap,
        this,
        (unsigned int)x,
        (unsigned int)y);
      if ( Map::GetMapId(pMap) != 50001
        && (*((int (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this) > 100
        && (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 17))(pMap) != 1 )
      {
        v22 = Answer::Singleton<CfgData>::instance();
        cfgBuff = CfgData::getBuff(v22, 8001);
        if ( cfgBuff )
        {
          launcher.id = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 12))(this);
          launcher.type = v23;
          v24 = (Buff *)operator new(0x60u);
          Buff::Buff(v24, this, cfgBuff, &launcher, 1, 1);
          buff = v24;
          if ( v24 )
            Unit::addBuff(this, buff);
        }
      }
      v5 = 0;
    }
    else
    {
      v25 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v25, nRunnerId, GameMsgCode::GMC_PLAYER_LEAVE_MAP, this, pMap, x, y, 0);
      v26 = Map::GetMapId(pMap);
      v27 = this->m_cgindex;
      v28 = this->m_connid;
      v29 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v29, v28, v27, 0x10u, v26);
      v5 = 1;
    }
    ChangeMapLog::~ChangeMapLog(&stu);
  }
  return v5;
}


#####################################
void __cdecl Player::EnterMapGongGao(Player *const this, int32_t GongGaoId, int32_t MapId)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( GongGaoId > 0 )
  {
    m_connid = this->m_connid;
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, MapId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = this->m_connid;
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


#####################################
int32_t __cdecl Player::OnCheckAccelerator(Player *const this, Answer::NetPacket *inPacket)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  int32_t Tick; // [rsp+1Ch] [rbp-24h]
  int64_t CurTick; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  Tick = Answer::NetPacket::readInt32(inPacket);
  CurTick = Unit::getTick(this);
  if ( this->m_LastCheckAccelerator <= 0 || CurTick - this->m_LastCheckAccelerator > 13000 )
    this->m_AcceleratorTime = 0;
  else
    ++this->m_AcceleratorTime;
  this->m_LastCheckAccelerator = CurTick;
  m_connid = this->m_connid;
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x2D1Eu);
  if ( !packet )
    return 10002;
  Answer::NetPacket::writeInt32(packet, Tick);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  m_cgindex = this->m_cgindex;
  v7 = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v8, v7, m_cgindex, packet);
  return 0;
}


#####################################
void __cdecl Player::moveToReviveRegion(Player *const this, bool bInAct)
{
  CfgData *v2; // rax
  int32_t mapid; // ebx
  CfgData *v4; // rax
  int32_t v5; // ebx
  MapManager *v6; // rax
  Position pos; // [rsp+10h] [rbp-40h]
  int32_t region; // [rsp+24h] [rbp-2Ch]
  CfgMapRegion *pCfgMapRegion; // [rsp+28h] [rbp-28h]
  Map *pTargetMap; // [rsp+38h] [rbp-18h]

  if ( this->m_pMap )
  {
    region = (*((__int64 (__fastcall **)(Map *, Player *const))this->m_pMap->_vptr_Map + 6))(this->m_pMap, this);
    v2 = Answer::Singleton<CfgData>::instance();
    pCfgMapRegion = CfgData::getMapRegion(v2, region);
    if ( pCfgMapRegion )
    {
      mapid = pCfgMapRegion->mapid;
      v4 = Answer::Singleton<CfgData>::instance();
      if ( CfgData::getMap(v4, mapid) )
      {
        v5 = pCfgMapRegion->mapid;
        v6 = Answer::Singleton<MapManager>::instance();
        pTargetMap = MapManager::GetMap(v6, v5);
        if ( pTargetMap )
        {
          pos = Map::getRandomWalkablePositionInRegion(pTargetMap, pCfgMapRegion);
          if ( pos.x >= 0 && pos.y >= 0 )
          {
            if ( this->m_pMap == pTargetMap )
              Unit::instantMove(this, pos.x, pos.y, InstanceMoveReason::IMR_FU_HUO, 0);
            else
              Player::switchMap(this, pTargetMap, pos.x, pos.y, 1);
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl Player::getActivityBirthRegion(const Player *const this, Int32Vector *pRegsions)
{
  Answer::Random *v3; // rax
  size_t v4; // rdx
  int32_t lenth; // [rsp+1Ch] [rbp-14h]

  if ( !pRegsions )
    return 0;
  lenth = std::vector<int>::size(pRegsions);
  if ( std::vector<int>::size(pRegsions) == 1 )
    return *std::vector<int>::at(pRegsions, 0);
  v3 = Answer::Singleton<Answer::Random>::instance();
  v4 = Answer::Random::generate(v3, 0, lenth - 1);
  return *std::vector<int>::at(pRegsions, v4);
}


#####################################
int32_t __cdecl Player::leaveDungeon(Player *const this)
{
  Dungeon *v1; // rax
  MapManager *v3; // rax
  int32_t v4; // eax
  int32_t RunnerId; // eax
  Position oldPosition; // [rsp+10h] [rbp-30h] BYREF
  Dungeon *pDungeon; // [rsp+18h] [rbp-28h]
  int32_t BackMapId; // [rsp+24h] [rbp-1Ch]
  Map *pTargetMap; // [rsp+28h] [rbp-18h]

  if ( this->m_pMap )
    v1 = (Dungeon *)__dynamic_cast(
                      this->m_pMap,
                      (const struct __class_type_info *)&`typeinfo for'Map,
                      (const struct __class_type_info *)&`typeinfo for'Dungeon,
                      0);
  else
    v1 = 0;
  pDungeon = v1;
  if ( v1 )
  {
    Position::Position(&oldPosition, this->m_oldPosition.x, this->m_oldPosition.y);
    if ( Dungeon::StayPosition(pDungeon) )
      oldPosition = StaticObj::getCurrentTile(this);
    BackMapId = Dungeon::GetBackMapId(pDungeon);
    if ( BackMapId > 0 )
      oldPosition = Dungeon::GetBackPos(pDungeon);
    else
      BackMapId = this->m_oldPosition.mapid;
    v3 = Answer::Singleton<MapManager>::instance();
    pTargetMap = MapManager::GetMap(v3, BackMapId);
    if ( pTargetMap )
    {
      if ( pTargetMap == pDungeon )
      {
        RunnerId = StaticObj::GetRunnerId(this);
        Answer::Logger::print(
          Answer::LogLevel::LOG_DUNGEON_INFO,
          "====  id %d,kingdom id %d\n",
          this->m_oldPosition.mapid,
          RunnerId);
        return 10002;
      }
      else
      {
        Player::broadcastLeave(this);
        (*((void (__fastcall **)(Dungeon *, Player *const, _QWORD))pDungeon->_vptr_Map + 16))(pDungeon, this, 0);
        if ( !Unit::isAlive(this) )
          Player::safeRevive(this);
        if ( Dungeon::getDungeonType(pDungeon) == 12 )
          CExtCharTeamDungeon::LeaveTeamDungeon(&this->m_extCharTeamDungeon);
        if ( CExtCharCarrier::IsInCarrier(&this->m_extCharCarrier) )
          CExtCharCarrier::LeaveCarrier(&this->m_extCharCarrier);
        (*((void (__fastcall **)(Map *, Player *const, _QWORD, _QWORD))pTargetMap->_vptr_Map + 15))(
          pTargetMap,
          this,
          (unsigned int)oldPosition.x,
          (unsigned int)oldPosition.y);
        Dungeon::onPlayerLeave(pDungeon, this);
        Player::BreakGather(this, 1);
        return 0;
      }
    }
    else
    {
      v4 = StaticObj::GetRunnerId(this);
      Answer::Logger::print(
        Answer::LogLevel::LOG_DUNGEON_INFO,
        "leave dungeon is  null faile  oldmap id %d,kingdom id %d\n",
        this->m_oldPosition.mapid,
        v4);
      return 10002;
    }
  }
  else
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "pDungeon NULL");
    return 10002;
  }
}


#####################################
int32_t __cdecl Player::leaveActivity(Player *const this)
{
  int32_t mapid; // ebx
  MapManager *v3; // rax
  GameService *v4; // rax
  CfgData *v6; // rax
  int32_t v7; // ebx
  MapManager *v8; // rax
  int32_t RunnerId; // ebx
  int32_t iparam2; // r12d
  int32_t x; // r13d
  int32_t v12; // ebx
  MapManager *v13; // rax
  int8_t m_connid; // bl
  GameService *v15; // rax
  uint32_t WOffset; // edx
  int8_t v17; // bl
  GameService *v18; // rax
  GameService *v19; // rax
  int32_t v20; // edx
  Position pos; // [rsp+20h] [rbp-40h]
  Map *pTargetMap; // [rsp+28h] [rbp-38h]
  Answer::NetPacket *outPacket; // [rsp+30h] [rbp-30h]
  CfgMapRegion *pCfgRegion; // [rsp+38h] [rbp-28h]

  if ( !this->m_pMap )
    return 10002;
  if ( !Unit::isAlive(this) )
  {
    (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
    Player::SetDieTick(this);
  }
  mapid = this->m_oldPosition.mapid;
  v3 = Answer::Singleton<MapManager>::instance();
  pTargetMap = MapManager::GetMap(v3, mapid);
  if ( !pTargetMap
    || this->m_pMap == pTargetMap
    || (v4 = Answer::Singleton<GameService>::instance(), GameService::getLine(v4) != 9) )
  {
    v6 = Answer::Singleton<CfgData>::instance();
    pCfgRegion = CfgData::getMapRegion(v6, 20001);
    if ( !pCfgRegion )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "leave activity back city fail! city regon err!\n");
      return 10002;
    }
    v7 = pCfgRegion->mapid;
    v8 = Answer::Singleton<MapManager>::instance();
    pTargetMap = MapManager::GetMap(v8, v7);
    if ( !pTargetMap )
    {
      Answer::Logger::print(Answer::LogLevel::LOG_DUNGEON_INFO, "leave activity back city fail! city map err!\n");
      return 10002;
    }
    pos = Map::getRandomWalkablePositionInRegion(pTargetMap, pCfgRegion);
    if ( pos.x >= 0 && pos.y >= 0 )
    {
      this->m_oldPosition.mapid = Map::GetMapId(pTargetMap);
      *(Position *)&this->m_oldPosition.x = pos;
    }
  }
  if ( CExtCharCarrier::IsInCarrier(&this->m_extCharCarrier) )
    CExtCharCarrier::LeaveCarrier(&this->m_extCharCarrier);
  Player::broadcastLeave(this);
  RunnerId = Map::GetRunnerId(this->m_pMap);
  if ( RunnerId == Map::GetRunnerId(pTargetMap) )
  {
    (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
    (*((void (__fastcall **)(Map *, Player *const, _QWORD, _QWORD))pTargetMap->_vptr_Map + 15))(
      pTargetMap,
      this,
      (unsigned int)this->m_oldPosition.x,
      (unsigned int)this->m_oldPosition.y);
  }
  else
  {
    (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
    iparam2 = this->m_oldPosition.y;
    x = this->m_oldPosition.x;
    v12 = Map::GetRunnerId(pTargetMap);
    v13 = Answer::Singleton<MapManager>::instance();
    MapManager::PostMsg(v13, v12, GameMsgCode::GMC_PLAYER_LEAVE_MAP, this, pTargetMap, x, iparam2, 0);
  }
  Player::recalcAttr(this, 0, 0);
  m_connid = this->m_connid;
  v15 = Answer::Singleton<GameService>::instance();
  outPacket = GameService::popNetpacket(v15, m_connid, Answer::PackType::PACK_DISPATCH, 0x4EBDu);
  if ( !outPacket )
    return 10002;
  Answer::NetPacket::writeInt32(outPacket, this->m_cgindex);
  Answer::NetPacket::writeInt32(outPacket, 0);
  WOffset = Answer::NetPacket::getWOffset(outPacket);
  Answer::NetPacket::setSize(outPacket, WOffset);
  v17 = this->m_connid;
  v18 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v18, v17, outPacket);
  Player::BreakGather(this, 1);
  v19 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v19) == 9 )
  {
    v20 = Unit::getNow(this) + 120;
    Player::updateRecord(this, 1924, v20);
    Player::kickBackFromCross(this, 10114);
  }
  return 0;
}


#####################################
bool __cdecl Player::isInRectangle(const Player *const this, Position x, Position y)
{
  return Unit::isInRectangle(this, x, y);
}


#####################################
std::string __cdecl Player::getName(const Player *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1192);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
int32_t __cdecl Player::getCreatedDays(const Player *const this)
{
  return Answer::DayTime::daydiff(this->m_chr.create_time) + 1;
}


#####################################
std::string __cdecl Player::getFamilyName(const Player *const this)
{
  CExtCharFamily::GetFamilyName((const CExtCharFamily *const)this);
  return (std::string)this;
}


#####################################
void __cdecl Player::SetCamp(Player *const this, int8_t nCamp)
{
  this->m_nCamp = nCamp;
  Player::setSyncStatusFlag(this);
}


#####################################
void __cdecl Player::SendOtherPlayerInfo(Player *const this, int8_t connid, int16_t cgindex)
{
  GameService *v3; // rax
  Answer::NetPacket *playerInfo; // [rsp+18h] [rbp-18h]

  playerInfo = Player::getOtherQueryInfo(this);
  if ( playerInfo )
  {
    v3 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v3, connid, cgindex, playerInfo);
  }
}


#####################################
void __cdecl Player::delExp(Player *const this, int64_t nValue)
{
  this->m_chr.exp -= nValue;
  if ( this->m_chr.exp < 0 )
    this->m_chr.exp = 0;
  Unit::setNeedSyncSelf(this);
}


#####################################
void __cdecl Player::sendExpGainInfo(Player *const this, int64_t value, int64_t BaseExp, BenefitType benefitType)
{
  int8_t m_connid; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int BaseExpa; // [rsp+18h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int64_t VipExp; // [rsp+38h] [rbp-18h]

  BaseExpa = BaseExp;
  if ( benefitType != BenefitType::BT_NORMAL || value )
  {
    m_connid = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, m_connid, Answer::PackType::PACK_DISPATCH, 0x2763u);
    if ( packet )
    {
      VipExp = (unsigned int)(int)(Player::benefitRatio(this) * (double)BaseExpa);
      Answer::NetPacket::writeInt32(packet, 1);
      Answer::NetPacket::writeInt64(packet, value - VipExp);
      Answer::NetPacket::writeInt32(packet, benefitType);
      Answer::NetPacket::writeInt64(packet, VipExp);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      m_cgindex = this->m_cgindex;
      v8 = this->m_connid;
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, m_cgindex, packet);
    }
  }
}


#####################################
void __cdecl Player::addExp(Player *const this, int64_t addon, int64_t BaseExp, bool Iswallow)
{
  BenefitType v4; // ecx
  int64_t addona; // [rsp+10h] [rbp-30h]

  addona = addon;
  if ( addon > 0 )
  {
    if ( Iswallow )
      addona = (unsigned int)(int)((double)(int)addon * Player::benefitRatio(this));
    v4 = Player::benefitType(this);
    Player::sendExpGainInfo(this, addona, BaseExp, v4);
    this->m_chr.exp += addona;
    Player::autoUpgradeLevel(this);
    Unit::setNeedSyncSelf(this);
  }
}


#####################################
int64_t __cdecl Player::GetLevelExp(Player *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax

  v1 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  v2 = Answer::Singleton<CfgData>::instance();
  return CfgData::getNeedLevelExp(v2, v1);
}


#####################################
int64_t __cdecl Player::GetLevelMaxExp(Player *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax

  v1 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  v2 = Answer::Singleton<CfgData>::instance();
  return CfgData::getMaxExp(v2, v1);
}


#####################################
void __cdecl Player::UpdateGmGold(Player *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  int32_t sid; // ebx
  int64_t Uid; // rax
  Answer::MySqlQuery *v5; // rax
  int32_t v6; // ebx
  int64_t v7; // rax
  Answer::MySqlQuery *v8; // rax
  char szSQL[4096]; // [rsp+20h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1020h] [rbp-80h] BYREF
  Answer::MySqlQuery result_1; // [rsp+1050h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+1070h] [rbp-30h] BYREF
  int32_t gm_pay; // [rsp+108Ch] [rbp-14h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(szSQL, 0, sizeof(szSQL));
    sid = this->m_sysUser.sid;
    Uid = Player::getUid(this);
    snprintf(szSQL, 0xFFFu, "SELECT `gm_gold` FROM `sys_user` WHERE `uid`=%lld AND `sid`=%d", Uid, sid);
    v5 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v5);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      gm_pay = Answer::MySqlQuery::getIntValue(&result, "gm_gold", 0);
      if ( gm_pay > 0 )
      {
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, gm_pay, CURRENCY_CHANGE_REASON::GCR_GM_PAY, 0);
        this->m_sysUser.gold_pay_total += gm_pay;
        Unit::setNeedSyncSelf(this);
        Player::PayedDispose(this, gm_pay);
        bzero(szSQL, 0x1000u);
        v6 = this->m_sysUser.sid;
        v7 = Player::getUid(this);
        snprintf(
          szSQL,
          0xFFFu,
          "UPDATE `sys_user` SET  `gm_gold`=`gm_gold`-%d, `gold_pay_total`=`gold_pay_total`+%d WHERE `uid`=%lld AND `sid`=%d",
          gm_pay,
          gm_pay,
          v7,
          v6);
        Answer::MySqlDBGuard::excute(&db, szSQL);
        bzero(szSQL, 0x1000u);
        snprintf(
          szSQL,
          0xFFFu,
          "SELECT `fuli` FROM `sys_user` WHERE `uid`=%lld AND `sid`=%d ",
          this->m_sysUser.uid,
          this->m_sysUser.sid);
        v8 = Answer::MySqlDBGuard::query(&db, szSQL);
        Answer::MySqlQuery::MySqlQuery(&result_1, v8);
        if ( !Answer::MySqlQuery::eof(&result_1) )
          this->m_sysUser.fuli = Answer::MySqlQuery::getIntValue(&result_1, "fuli", 0);
        Answer::MySqlQuery::~MySqlQuery(&result_1);
      }
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl Player::syncGold(Player *const this, int32_t nGold)
{
  GameService *v2; // rax
  Answer::DBPool *v3; // rax
  Answer::MySqlQuery *v4; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1060h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-30h] BYREF
  int32_t gold_pay; // [rsp+105Ch] [rbp-14h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
  {
    if ( this->m_sysUser.gold_pay != nGold )
    {
      this->m_sysUser.gold_pay = nGold;
      Player::SendRechargeNotice(this, nGold);
    }
  }
  else
  {
    v3 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v3);
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "call GetPayGold(%lld,%d,@OutPayGold)", this->m_sysUser.uid, this->m_sysUser.sid);
    v4 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v4);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      gold_pay = Answer::MySqlQuery::getIntValue(&result, 0, 0);
      if ( gold_pay > 0 )
      {
        this->m_sysUser.gold_pay = 0;
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, gold_pay, CURRENCY_CHANGE_REASON::GCR_RECHARGE, 0);
        this->m_sysUser.gold_pay_total += gold_pay;
        Unit::setNeedSyncSelf(this);
        Player::syncTodayGoldPay(this);
        CYunYingHD::SendShouChongInfo(&this->m_PlayerYunYingHD);
        Player::PayedDispose(this, gold_pay);
      }
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
bool __cdecl Player::UseRechargeCard(Player *const this, int32_t nValue, bool bReal)
{
  GameService *v3; // rax
  bool v4; // bl
  Answer::DBPool *v5; // rax
  int32_t Sid; // ebx
  int64_t Uid; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1040h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-40h] BYREF

  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 0;
  if ( bReal )
    Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, nValue, CURRENCY_CHANGE_REASON::GCR_RECHARGE_CARD, 0);
  this->m_sysUser.gold_pay_total += nValue;
  Unit::setNeedSyncSelf(this);
  Player::syncTodayGoldPay(this);
  CYunYingHD::SendShouChongInfo(&this->m_PlayerYunYingHD);
  Player::PayedDispose(this, nValue);
  v5 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v5);
  memset(szSQL, 0, sizeof(szSQL));
  Sid = Player::getSid(this);
  Uid = Player::getUid(this);
  snprintf(
    szSQL,
    0xFFFu,
    "UPDATE `sys_user` SET `gold_pay_total`=`gold_pay_total`+%d WHERE `uid`=%lld AND `sid`=%d",
    nValue,
    Uid,
    Sid);
  Answer::MySqlDBGuard::excute(&db, szSQL);
  v4 = 1;
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  return v4;
}


#####################################
void __cdecl Player::SendRechargeNotice(Player *const this, int32_t nGold)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x27FAu);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, nGold);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v6 = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v6, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::PayedDispose(Player *const this, const int32_t AddGold)
{
  int32_t TodayPayGold; // ebx
  int32_t v3; // eax
  int32_t v4; // r12d
  CKiaFuRecharge *v5; // rax
  int32_t v6; // r12d
  CFestivalDoubleEleven *v7; // rax
  int32_t v8; // ebx
  int32_t v9; // eax
  CUniteServer *v10; // rax
  CExtOperateLimit *OperateLimit; // rax
  CFestivalDoubleEleven *v12; // rax
  CFestivalDoubleEleven *v13; // rax
  CUniteServer *v14; // rax
  CZongHeYunYingHD *v15; // rax
  COpenBeta *v16; // rax
  CKaiFuHuoDong *v17; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax

  TodayPayGold = Player::GetTodayPayGold(this);
  v3 = Player::GetTodayPayGold(this);
  CMonthlyChouJiang::OnChongZhi(&this->m_CMonthlyChouJiang, AddGold + v3, TodayPayGold);
  v4 = Player::GetTodayPayGold(this);
  v5 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::OnRecharge(v5, this, v4, AddGold);
  v6 = Player::GetTodayPayGold(this);
  v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::OnRecharge(v7, this, v6, AddGold);
  v8 = AddGold + Player::GetTodayPayGold(this);
  v9 = Player::GetTodayPayGold(this);
  CNationalDayHd::AddNationalValue(&this->m_CNationalDayHd, NATIONAL_HD_TYPE::HHT_RECHARGE, v9, v8);
  v10 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::OnRecharge(v10, this, AddGold);
  CYunYingHD::AddTotalChongZhiCount(&this->m_PlayerYunYingHD, AddGold);
  OperateLimit = Player::GetOperateLimit(this);
  CExtOperateLimit::AddLimitCount(OperateLimit, 2026, AddGold);
  CYunYingHD::SuperMemberRecharge(&this->m_PlayerYunYingHD, AddGold);
  CYunYingHD::SendEveryDayChongZhiIcon(&this->m_PlayerYunYingHD, 3);
  CYunYingHD::SendEveryDayChongZhiIcon(&this->m_PlayerYunYingHD, 2);
  v12 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::AddRechargeRecord(v12, this, AddGold);
  v13 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::SendIconState(v13, this);
  v14 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::SendIconState(v14, this);
  v15 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::OnRecharge(v15, this, AddGold);
  v16 = Answer::Singleton<COpenBeta>::instance();
  COpenBeta::SendIconState(v16, this);
  v17 = Answer::Singleton<CKaiFuHuoDong>::instance();
  CKaiFuHuoDong::SendKaiFuHuoDongIcon(v17, this);
  CMonthlyChouJiang::SendIcon(&this->m_CMonthlyChouJiang);
  CMonthlyChouJiang::SendMonthlyChouJiangInfo(&this->m_CMonthlyChouJiang);
  DailyActivity::SendJiangLiDaTingIcon(&this->m_PlayerDailyActivity);
  CVip::AddVipExp(&this->m_PlayerVip, AddGold);
  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this);
  CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 8, AddGold, 0);
}


#####################################
void __cdecl Player::SendRechargeGold(Player *const this, const int32_t Gold)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( Gold > 299 )
  {
    m_connid = this->m_connid;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x4EB9u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, (int)((double)Gold * 0.5));
      Answer::NetPacket::writeInt32(packet, 10);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = this->m_connid;
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
void __cdecl Player::syncTodayGoldPay(Player *const this)
{
  CYunYingHD::SendEveryDayChongZhiInfo(&this->m_PlayerYunYingHD, 3);
  CYunYingHD::SendEveryDayChongZhiInfo(&this->m_PlayerYunYingHD, 2);
}


#####################################
std::string __cdecl Player::getIP(Player *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1556);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
int32_t __cdecl Player::getMainWeaponId(Player *const this)
{
  return CExtEquip::GetEquipSlot(&this->m_extEquip, 0)->itemId;
}


#####################################
int32_t __cdecl Player::getClothesId(Player *const this)
{
  return CExtEquip::GetEquipSlot(&this->m_extEquip, 2)->itemId;
}


#####################################
void __cdecl Player::setTrailer(Player *const this, Trailer *pTrailer)
{
  ChrTask *v2; // rax
  int32_t TaskId; // ebx
  ChrTask *Task; // rax

  this->m_trailer = pTrailer;
  if ( pTrailer )
  {
    TaskId = Trailer::GetTaskId(pTrailer);
    Task = Player::GetTask(this);
    ChrTask::receive(Task, TaskId);
  }
  else
  {
    v2 = Player::GetTask(this);
    ChrTask::CleanTaskType(v2, 5);
  }
}


#####################################
void __cdecl Player::CheckTrailer(Player *const this)
{
  int32_t MapId; // ebx
  int32_t PosY; // ebx
  int32_t PosX; // eax
  Position pos; // [rsp+10h] [rbp-30h] BYREF
  Position CurrentPixel; // [rsp+20h] [rbp-20h] BYREF

  if ( this->m_trailer )
  {
    MapId = StaticObj::getMapId(this->m_trailer);
    if ( MapId != StaticObj::getMapId(this)
      || (pos = StaticObj::getCurrentPixel(this),
          CurrentPixel = StaticObj::getCurrentPixel(this->m_trailer),
          Position::distance(&CurrentPixel, &pos) > 700.0) )
    {
      if ( Unit::isMoving(this->m_trailer) )
      {
        PosY = StaticObj::GetPosY(this->m_trailer);
        PosX = StaticObj::GetPosX(this->m_trailer);
        Unit::setTargetTile(this->m_trailer, PosX, PosY);
        Unit::broadcastMove(this->m_trailer);
      }
    }
  }
}


#####################################
double __cdecl Player::benefitRatio(Player *const this)
{
  int32_t total_online_time; // ebx
  std::string __lhs; // [rsp+20h] [rbp-20h] BYREF
  int32_t onlineTime; // [rsp+2Ch] [rbp-14h]

  if ( this->m_sysUser.adult )
    return 1.0;
  total_online_time = this->m_sysUser.total_online_time;
  onlineTime = total_online_time + Unit::getNow(this) - this->m_sysUser.last_login_time;
  Player::GetPlatform((const Player *const)&__lhs);
  LOBYTE(total_online_time) = std::operator==<char>(&__lhs, "32wan");
  std::string::~string(&__lhs);
  if ( (_BYTE)total_online_time )
    onlineTime = this->m_sysUser.total_online_time;
  if ( onlineTime > 17999 )
    return 0.0;
  if ( onlineTime <= 10799 )
    return 1.0;
  return 0.5;
}


#####################################
bool __cdecl Player::hasItem(Player *const this, int32_t baseid, int32_t type, int32_t count)
{
  return CExtCharBag::HasItem(&this->m_extCharBag, baseid, type, count);
}


#####################################
void __cdecl Player::CalBattle(Player *const this)
{
  CfgData *v1; // rax
  int32_t OldBattle; // [rsp+1Ch] [rbp-24h]
  int64_t nAttrBattle; // [rsp+20h] [rbp-20h]
  int64_t nAttrBattlea; // [rsp+20h] [rbp-20h]
  int8_t i; // [rsp+2Bh] [rbp-15h]
  int32_t nAttrValue; // [rsp+2Ch] [rbp-14h]

  OldBattle = this->m_Battle;
  nAttrBattle = 0;
  for ( i = 0; i <= 49; ++i )
  {
    nAttrValue = Unit::GetBaseAttr(this, (const CObjAttrs::Index_T)i);
    v1 = Answer::Singleton<CfgData>::instance();
    nAttrBattle += nAttrValue * CfgData::GetAttrBattle(v1, i);
  }
  nAttrBattlea = CExtEquip::GetGongMingBuffBattle(&this->m_extEquip) + nAttrBattle / 100;
  if ( OldBattle != nAttrBattlea )
  {
    this->m_Battle = nAttrBattlea;
    Player::sendUpdateSocialPlayerInfo(this, PlayerInfoIndex::PII_BATTLE, this->m_Battle);
    Unit::setNeedSyncAttr(this);
  }
}


#####################################
void __cdecl Player::setPkMode(Player *const this, int32_t mode, bool backUp)
{
  this->m_chr.pk_mode = mode;
  if ( backUp )
    this->m_pkMode_bk = this->m_chr.pk_mode;
  if ( mode != 1 )
    Player::SetPkProtectTime(this, 0);
  Unit::setNeedSyncSelf(this);
  Player::SetNeedSyncAround(this);
}


#####################################
void __cdecl Player::resetPkModeOnEnterMap(Player *const this, const Map *pMap)
{
  if ( pMap )
  {
    if ( (*((unsigned int (__fastcall **)(const Map *))pMap->_vptr_Map + 5))(pMap) )
    {
      if ( (*((unsigned int (__fastcall **)(const Map *))pMap->_vptr_Map + 5))(pMap) == 1 )
      {
        this->m_chr.pk_mode = 1;
      }
      else if ( (*((int (__fastcall **)(const Map *))pMap->_vptr_Map + 5))(pMap) > 1 )
      {
        this->m_chr.pk_mode = (*((__int64 (__fastcall **)(const Map *))pMap->_vptr_Map + 5))(pMap);
        if ( this->m_chr.pk_time > 0 )
          this->m_chr.pk_time = 0;
      }
    }
    else if ( this->m_chr.pk_mode != this->m_pkMode_bk )
    {
      this->m_chr.pk_mode = this->m_pkMode_bk;
    }
    Unit::setNeedSyncSelf(this);
    Player::SetNeedSyncAround(this);
  }
}


#####################################
void __cdecl Player::onDropItem(Player *const this, Player *pKiller, int32_t Mid)
{
  int32_t PkValue; // ebx
  CfgData *v4; // rax
  CVip *PlayerVip; // rax
  MemChrBag stu; // [rsp+50h] [rbp-F0h] BYREF
  int64_t srcId; // [rsp+70h] [rbp-D0h]
  Position CentosPos; // [rsp+80h] [rbp-C0h] BYREF
  CDropItemGroup pDropItemGroup; // [rsp+90h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+A0h] [rbp-A0h] BYREF
  DropItemVector dropItems; // [rsp+B0h] [rbp-90h] BYREF
  MemChrBagVector DropItemVt; // [rsp+D0h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+F0h] [rbp-50h] BYREF
  std::string dropper; // [rsp+100h] [rbp-40h] BYREF
  bool bDropItem; // [rsp+10Bh] [rbp-35h]
  int32_t i; // [rsp+10Ch] [rbp-34h]
  int64_t HaveMoney; // [rsp+110h] [rbp-30h]
  int64_t DropMoneyCount; // [rsp+118h] [rbp-28h]
  PkDropRate *pPkDropRate; // [rsp+120h] [rbp-20h]
  int32_t nEquipRate; // [rsp+128h] [rbp-18h]
  int32_t nUsualRate; // [rsp+12Ch] [rbp-14h]

  bDropItem = 1;
  std::vector<MemChrBag>::vector(&DropItemVt);
  if ( CVip::GetVipFlg(&this->m_PlayerVip, 1) && Player::getRecord(this, 2061) <= 0 )
    bDropItem = 0;
  if ( bDropItem )
  {
    PkValue = Player::getPkValue(this);
    v4 = Answer::Singleton<CfgData>::instance();
    pPkDropRate = CfgData::GetPkDropRate(v4, PkValue);
    if ( pPkDropRate )
    {
      nEquipRate = pPkDropRate->EquipRate;
      nUsualRate = pPkDropRate->UsualDropRate;
      PlayerVip = Player::GetPlayerVip(this);
      if ( CVip::GetVipFlg(PlayerVip, 3) )
        nEquipRate -= 30 * nEquipRate / 100;
      if ( Mid <= 0 )
        CExtEquip::GetDropEquip(&this->m_extEquip, pKiller, pPkDropRate->EquipCount, nEquipRate, &DropItemVt, Mid);
      CExtCharBag::GetDropItem(&this->m_extCharBag, pKiller, pPkDropRate, nUsualRate, &DropItemVt, Mid);
    }
  }
  CXinMo::DieDropFromXinMoBag(&this->m_CXinMo, &DropItemVt);
  std::vector<DropItem>::vector(&dropItems);
  i = 0;
  HaveMoney = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY);
  DropMoneyCount = 0;
  for ( it._M_current = std::vector<MemChrBag>::begin(&DropItemVt)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(&DropItemVt)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) || i > 120 )
      break;
    if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->bind != 1
      && __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->bind != 2 )
    {
      memset(&stu, 0, sizeof(stu));
      srcId = 0;
      stu.itemId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemId;
      stu.itemClass = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemClass;
      stu.bind = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->bind;
      *((_BYTE *)&stu.endTime + 4) = 0;
      LODWORD(stu.srcId) = 0;
      stu.itemCount = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemCount;
      stu.endTime = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->endTime;
      srcId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->srcId;
      std::vector<DropItem>::push_back(&dropItems, (const DropItem *const)&stu);
    }
    ++i;
  }
  CDropItemGroup::CDropItemGroup(&pDropItemGroup);
  if ( this->m_pMap )
  {
    CentosPos = StaticObj::getCurrentTile(this);
    Player::getName((const Player *const)&dropper);
    CDropItemGroup::init(
      &pDropItemGroup,
      this->m_connid,
      this->m_pMap,
      &CentosPos,
      pKiller,
      1,
      0,
      &dropItems,
      &dropper,
      Mid,
      0,
      0);
    std::string::~string(&dropper);
    Map::addDropItemGroup(this->m_pMap, &pDropItemGroup);
  }
  CDropItemGroup::~CDropItemGroup(&pDropItemGroup);
  std::vector<DropItem>::~vector(&dropItems);
  std::vector<MemChrBag>::~vector(&DropItemVt);
}


#####################################
void __cdecl Player::updatePkValue(Player *const this, Player *pKiller, Map *pMap)
{
  bool v3; // al
  bool v4; // al
  GameService *v5; // rax
  CExtEquip *Equip; // rax
  CfgData *v8; // rax
  const CfgEquipBlessTable *EquipBlessTable; // rax
  FamilyId_t v10; // rax
  FamilyId_t FamilyId; // rax
  Answer::Random *v12; // rax
  int32_t v13; // eax
  CExtEquip *v15; // rax
  int8_t ConnId; // bl
  GameService *v17; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v20; // bl
  GameService *v21; // rax
  Position pos; // [rsp+20h] [rbp-50h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-40h] BYREF
  int32_t nRate; // [rsp+44h] [rbp-2Ch]
  bool bCanRemine; // [rsp+4Bh] [rbp-25h]
  int32_t nEquipBless; // [rsp+4Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  if ( this->m_pMap && pKiller && pMap )
  {
    pos = StaticObj::getCurrentTile(pKiller);
    v3 = 1;
    if ( !Map::inSafeRegion(this->m_pMap, &pos) )
    {
      CurrentTile = StaticObj::getCurrentTile(this);
      if ( !Map::inSafeRegion(this->m_pMap, &CurrentTile) )
        v3 = 0;
    }
    if ( !v3 && !StaticObj::InActivity(pKiller) )
    {
      v4 = StaticObj::InDungeon(this) || StaticObj::InActivity(this) || Map::IsPVPMap(pMap);
      if ( !v4 && !CExtFightChecker::IsBuleName(&this->m_extFightChecker) && !StaticObj::InPrison(this) )
      {
        v5 = Answer::Singleton<GameService>::instance();
        if ( GameService::getLine(v5) != 9 )
        {
          nRate = 0;
          bCanRemine = 0;
          Equip = Player::GetEquip(pKiller);
          nEquipBless = CExtEquip::GetWeaponBless(Equip) - 1;
          if ( Player::getWeaponId(pKiller) > 0 )
          {
            v8 = Answer::Singleton<CfgData>::instance();
            EquipBlessTable = CfgData::GetEquipBlessTable(v8);
            if ( CfgEquipBlessTable::GetInfo(EquipBlessTable, nEquipBless) )
              bCanRemine = 1;
          }
          if ( Player::getPkValue(this) > 20 )
          {
            if ( Player::getPkValue(this) <= 100 )
            {
              FamilyId = Player::getFamilyId(pKiller);
              if ( !CExtCharFamily::IsDeclareWarFamily(&this->m_extCharFamily, FamilyId) )
              {
                Player::addPkValue(pKiller, 10);
                if ( bCanRemine )
                  nRate = 10;
              }
            }
          }
          else
          {
            v10 = Player::getFamilyId(pKiller);
            if ( !CExtCharFamily::IsDeclareWarFamily(&this->m_extCharFamily, v10) )
            {
              if ( Player::getPkValue(pKiller) > 20 )
                Player::addPkValue(pKiller, 20);
              else
                Player::addPkValue(pKiller, 10);
              if ( bCanRemine )
                nRate = 20;
            }
          }
          if ( nRate > 0 )
          {
            v12 = Answer::Singleton<Answer::Random>::instance();
            v13 = Answer::Random::generate(v12, 1, 100);
            if ( v13 <= nRate )
            {
              v15 = Player::GetEquip(pKiller);
              CExtEquip::SetWeaponBless(v15, nEquipBless);
              ConnId = Player::getConnId(pKiller);
              v17 = Answer::Singleton<GameService>::instance();
              packet = GameService::popNetpacket(v17, ConnId, Answer::PackType::PACK_DISPATCH, 0x274Eu);
              if ( packet )
              {
                Answer::NetPacket::writeInt8(packet, 1);
                Answer::NetPacket::writeInt8(packet, 2);
                Answer::NetPacket::writeInt32(packet, nEquipBless);
                WOffset = Answer::NetPacket::getWOffset(packet);
                Answer::NetPacket::setSize(packet, WOffset);
                GateIndex = Player::getGateIndex(pKiller);
                v20 = Player::getConnId(pKiller);
                v21 = Answer::Singleton<GameService>::instance();
                GameService::sendPacketTo(v21, v20, GateIndex, packet);
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Player::addPkValue(Player *const this, int32_t addon)
{
  if ( addon > 0 && this->m_chr.pk_value <= 0 )
    this->m_lastPkValueTick = Unit::getTick(this);
  this->m_chr.pk_value += addon;
  if ( this->m_chr.pk_value < 0 )
    this->m_chr.pk_value = 0;
  if ( this->m_chr.pk_value > 99 )
    CExtFightChecker::ChangeBuleName(&this->m_extFightChecker, 0);
  Player::SetNeedSyncAround(this);
  Unit::setNeedSyncSelf(this);
}


#####################################
bool __cdecl Player::SubPkValues(Player *const this, int32_t Addon)
{
  if ( Player::getPkValue(this) <= 0 )
    return 0;
  if ( Addon <= 0 )
    return 0;
  Player::addPkValue(this, -Addon);
  return 1;
}


#####################################
int32_t __cdecl Player::getWeaponId(Player *const this)
{
  return CExtEquip::GetEquipSlot(&this->m_extEquip, 0)->itemId;
}


#####################################
void __cdecl Player::SetPkProtectTime(Player *const this, int32_t Time)
{
  this->m_chr.pk_time = Time;
  Player::SetNeedSyncAround(this);
  Unit::setNeedSyncSelf(this);
}


#####################################
int32_t __cdecl Player::OnLevelPrison(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t mapid; // ebx
  MapManager *v5; // rax
  Position pos; // [rsp+10h] [rbp-30h]
  CfgMapRegion *pCfgRegion; // [rsp+20h] [rbp-20h]
  Map *pTargetMap; // [rsp+28h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  if ( Player::getPkValue(this) > 99 )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgRegion = CfgData::getMapRegion(v3, 20001);
  if ( !pCfgRegion )
    return 10002;
  mapid = pCfgRegion->mapid;
  v5 = Answer::Singleton<MapManager>::instance();
  pTargetMap = MapManager::GetMap(v5, mapid);
  if ( !pTargetMap )
    return 10002;
  pos = Map::getRandomWalkablePositionInRegion(pTargetMap, pCfgRegion);
  if ( pos.x < 0 || pos.y < 0 )
    return 10002;
  Player::switchMap(this, pTargetMap, pos.x, pos.y, 1);
  return 0;
}


#####################################
int32_t __cdecl Player::OnSubPkValus(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int8_t ClearType; // [rsp+12h] [rbp-1Eh]
  int8_t CostType; // [rsp+13h] [rbp-1Dh]
  int32_t BuyCount; // [rsp+14h] [rbp-1Ch]
  int CurPkValue; // [rsp+18h] [rbp-18h]
  CfgGameShop *pCfgGameShop; // [rsp+20h] [rbp-10h]
  int32_t nShopId; // [rsp+28h] [rbp-8h]
  int32_t nCostGold; // [rsp+2Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  ClearType = Answer::NetPacket::readInt8(inPacket);
  CostType = Answer::NetPacket::readInt8(inPacket);
  CurPkValue = Player::getPkValue(this);
  if ( ClearType != 1 )
    return 2;
  if ( CurPkValue <= 0 )
    return 2;
  BuyCount = CurPkValue / 10 + (CurPkValue % 10 != 0);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgGameShop = CfgData::GetGameShopItem(v3, 1, 7281);
  if ( !pCfgGameShop )
    return 2;
  nShopId = pCfgGameShop->ShopId;
  nCostGold = BuyCount * pCfgGameShop->Price;
  if ( nCostGold <= 0 )
    return 2;
  if ( CostType == 1 )
  {
    if ( !Player::DecCurrency(
            this,
            CURRENCY_TYPE::CURRENCY_GOLD,
            nCostGold,
            CURRENCY_CHANGE_REASON::GCR_CLEAR_PK_VALUES,
            nShopId) )
      return 2;
  }
  else if ( !Player::DecCurrency(
               this,
               CURRENCY_TYPE::CURRENCY_CASH,
               10 * nCostGold,
               CURRENCY_CHANGE_REASON::GCC_CLEAR_PK_VALUES,
               nShopId) )
  {
    return 2;
  }
  Player::SubPkValues(this, 10 * BuyCount);
  return 0;
}


#####################################
void __cdecl Player::setTaskCanSubmit(Player *const this, int32_t tid)
{
  ChrTask::setTaskCanSubmit(&this->m_task, tid, 0);
}


#####################################
void __cdecl Player::checkTaskCanSubmit(Player *const this, int32_t dungeonID, int8_t dungeonType)
{
  ChrTask::checkTaskCanSubmit(&this->m_task, dungeonID, dungeonType);
}


#####################################
void __cdecl Player::updateRecord(Player *const this, int32_t id, int32_t param)
{
  CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, id, param);
}


#####################################
int32_t __cdecl Player::getRecord(const Player *const this, int32_t id)
{
  return CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, id);
}


#####################################
void __cdecl Player::clearRecordRange(Player *const this, int32_t start, int32_t end, int32_t diffDay)
{
  CExtOperateLimit::ResetRange(&this->m_extOperateLimit, start, end, diffDay);
}


#####################################
void __cdecl Player::checkFestivalVersion(Player *const this)
{
  CFestivalDoubleEleven *v1; // rax
  CFestivalActivity *v2; // rax
  int32_t nVersion; // [rsp+18h] [rbp-8h]
  int32_t nVersion_0; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  nVersion = CFestivalDoubleEleven::GetVersion(v1);
  if ( CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 1599) != nVersion )
    Player::ResetFestivalData(this, nVersion);
  v2 = Answer::Singleton<CFestivalActivity>::instance();
  nVersion_0 = CFestivalActivity::GetVersion(v2);
  if ( CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37400) != nVersion_0 )
  {
    CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 37400, nVersion_0);
    CExtOperateLimit::ResetRange(&this->m_extOperateLimit, 37401, 37500, 0);
  }
}


#####################################
void __cdecl Player::ResetFestivalData(Player *const this, int32_t nVersion)
{
  CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 1599, nVersion);
  CExtOperateLimit::ResetRange(&this->m_extOperateLimit, 1600, 1699, 0);
}


#####################################
void __cdecl Player::onKillMonster(
        Player *const this,
        int32_t mid,
        int32_t groupId,
        int32_t level,
        int32_t exp,
        bool isBoss,
        bool bKiller)
{
  CHuoYueDu *PlayerHuoYueDu; // rax
  CHuoYueDu *v8; // rax
  int64_t v9; // rdx
  Dungeon *v10; // rax
  CfgData *v12; // rax
  Answer::Random *v13; // rax
  int32_t v14; // ebx
  int32_t item; // ebx
  CfgMonsterTaskDrop *v16; // rax
  Answer::Random *v17; // rax
  __gnu_cxx::__normal_iterator<CfgMonsterTaskDrop*,std::vector<CfgMonsterTaskDrop> > it; // [rsp+20h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterTaskDrop*,std::vector<CfgMonsterTaskDrop> > __rhs; // [rsp+30h] [rbp-40h] BYREF
  int32_t ExpRate; // [rsp+3Ch] [rbp-34h]
  int32_t nCurLevel; // [rsp+40h] [rbp-30h]
  int32_t tLevel; // [rsp+44h] [rbp-2Ch]
  float LevelRatio; // [rsp+48h] [rbp-28h]
  int32_t nFinalExp; // [rsp+4Ch] [rbp-24h]
  CfgMonsterTaskDropVector *pCfgMonsterTaskDrop; // [rsp+50h] [rbp-20h]
  Dungeon *pDungeon; // [rsp+58h] [rbp-18h]

  if ( bKiller )
  {
    if ( isBoss )
    {
      PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this);
      CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 4, 0, 0);
    }
    v8 = Player::GetPlayerHuoYueDu(this);
    CHuoYueDu::AddHuoYueDuRecord(v8, 3, 0, 0);
  }
  ChrTask::updateTaskMonster(&this->m_task, mid, groupId, level);
  ExpRate = 0;
  nCurLevel = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  tLevel = nCurLevel - level;
  LevelRatio = 1.0;
  if ( !isBoss && level <= 179 )
  {
    if ( tLevel >= -30 )
    {
      if ( tLevel >= -15 )
      {
        if ( tLevel > 14 )
        {
          if ( tLevel > 29 )
          {
            if ( tLevel > 59 )
              LevelRatio = 0.1;
            else
              LevelRatio = 0.30000001;
          }
          else
          {
            LevelRatio = 0.80000001;
          }
        }
        else
        {
          LevelRatio = 1.0;
        }
      }
      else
      {
        LevelRatio = 1.2;
      }
    }
    else
    {
      LevelRatio = 1.5;
    }
  }
  ExpRate = Player::GetAllExpRate(this);
  nFinalExp = roundInt((float)((float)((float)((float)ExpRate / 100.0) + 1.0) * (float)((float)exp * LevelRatio)));
  if ( !bKiller )
    nFinalExp /= 2;
  v9 = roundInt((float)((float)exp * LevelRatio));
  Player::addExp(this, nFinalExp, v9, 1);
  if ( StaticObj::InDungeon(this) )
  {
    v10 = this->m_pMap
        ? (Dungeon *)__dynamic_cast(
                       this->m_pMap,
                       (const struct __class_type_info *)&`typeinfo for'Map,
                       (const struct __class_type_info *)&`typeinfo for'Dungeon,
                       0)
        : 0LL;
    pDungeon = v10;
    if ( v10 && Dungeon::getDungeonType(pDungeon) == 23 )
      Dungeon::AddMonsterExp(pDungeon, nFinalExp);
  }
  v12 = Answer::Singleton<CfgData>::instance();
  pCfgMonsterTaskDrop = CfgData::getMonsterTaskDrop(v12, mid);
  if ( pCfgMonsterTaskDrop )
  {
    for ( it._M_current = std::vector<CfgMonsterTaskDrop>::begin(pCfgMonsterTaskDrop)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgMonsterTaskDrop *,std::vector<CfgMonsterTaskDrop>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgMonsterTaskDrop>::end(pCfgMonsterTaskDrop)._M_current;
      if ( !__gnu_cxx::operator!=<CfgMonsterTaskDrop *,std::vector<CfgMonsterTaskDrop>>(&it, &__rhs) )
        break;
      v13 = Answer::Singleton<Answer::Random>::instance();
      v14 = Answer::Random::generate(v13, 1, 1000);
      if ( v14 <= __gnu_cxx::__normal_iterator<CfgMonsterTaskDrop *,std::vector<CfgMonsterTaskDrop>>::operator->(&it)->probability )
      {
        item = __gnu_cxx::__normal_iterator<CfgMonsterTaskDrop *,std::vector<CfgMonsterTaskDrop>>::operator->(&it)->item;
        v16 = __gnu_cxx::__normal_iterator<CfgMonsterTaskDrop *,std::vector<CfgMonsterTaskDrop>>::operator->(&it);
        ChrTask::updateTaskDrop(&this->m_task, v16->tid, item);
      }
    }
  }
  v17 = Answer::Singleton<Answer::Random>::instance();
  if ( Answer::Random::generate(v17, 1, 1000) <= 100 )
    CExtCharSkill::AddSuitSkillEnergy(&this->m_extCharSkill);
}


#####################################
int32_t __cdecl Player::getAction(Player *const this)
{
  EntityId_t PlantId; // rax
  Plant *plant; // [rsp+18h] [rbp-8h]

  if ( !this->m_pMap )
    return 0;
  PlantId = Player::GetPlantId(this);
  plant = Map::getPlant(this->m_pMap, PlantId);
  if ( plant )
    return Plant::getPlantId(plant);
  else
    return 0;
}


#####################################
void __cdecl Player::onNewDayCome(Player *const this)
{
  int32_t Now; // eax
  CHuoYueDu *PlayerHuoYueDu; // rax
  ChrTask *Task; // rax
  int8_t m_connid; // bl
  DBService *v5; // rax
  online_user_24th_log stu; // [rsp+10h] [rbp-D0h] BYREF
  _BYTE v8[16]; // [rsp+A0h] [rbp-40h] BYREF
  _BYTE v9[16]; // [rsp+B0h] [rbp-30h] BYREF
  _BYTE v10[32]; // [rsp+C0h] [rbp-20h] BYREF

  Player::refreshDailyCheck(this, 1);
  Player::sendLoginInfo(this);
  online_user_24th_log::online_user_24th_log(&stu);
  stu.log_Sid = Player::getSid(this);
  stu.log_time = Unit::getNow(this);
  Player::GetPassport((Player *const)v8);
  std::string::operator=(&stu.passport, v8);
  std::string::~string(v8);
  stu.cid = Player::getCid(this);
  Player::getName((const Player *const)v9);
  std::string::operator=(&stu.name, v9);
  std::string::~string(v9);
  stu.create_time = Player::getCreateTime(this);
  stu.login_time = Player::getLastLoginTime(this);
  Now = Unit::getNow(this);
  stu.online_time = Now - stu.login_time;
  Player::getIP((Player *const)v10);
  std::string::operator=(&stu.ip, v10);
  std::string::~string(v10);
  stu.job = Player::getJob(this);
  stu.level = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  stu.battle = (*((int (__fastcall **)(Player *const))this->_vptr_Entity + 10))(this);
  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this);
  stu.huoyuedu = CHuoYueDu::CalculateHuoYueDu(PlayerHuoYueDu);
  stu.map_id = StaticObj::getMapId(this);
  Task = Player::GetTask(this);
  stu.task_id = ChrTask::GetTrunkTaskId(Task);
  stu.recharge_sum = this->m_sysUser.gold_pay_total;
  stu.gold = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD);
  stu.cash = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_CASH);
  stu.money = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY);
  stu.bind_money = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_BIND_MONEY);
  m_connid = this->m_connid;
  v5 = Answer::Singleton<DBService>::instance();
  DBService::AddPlatformLog(v5, m_connid, PLATFORM_LOG_DATA_TYPE::PLDT_ONLINE24, &stu);
  online_user_24th_log::~online_user_24th_log(&stu);
}


#####################################
void __cdecl Player::kickBackFromCross(Player *const this, int32_t Reason)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  int64_t Uid; // rdx
  int32_t Sid; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  CharId_t Cid; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_PROC, 0x4E2Cu);
  if ( packet )
  {
    Uid = Player::getUid(this);
    Answer::NetPacket::writeInt64(packet, Uid);
    Sid = Player::getSid(this);
    Answer::NetPacket::writeInt32(packet, Sid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v8, v7, packet);
    Cid = Player::getCid(this);
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "Kick_back_from_cross cid=%lld\tReason=%d\n", Cid, Reason);
  }
}


#####################################
void __cdecl Player::refeshKillerRecord(Player *const this)
{
  CExtOperateLimit::Reset(&this->m_extOperateLimit, 1010);
}


#####################################
void __cdecl Player::refreshDailyCheck(Player *const this, bool first)
{
  int32_t v2; // eax
  GameService *v3; // rax
  CUniteServer *v6; // rax
  CFestivalDoubleEleven *v7; // rax
  CFestivalActivity *v8; // rax
  CZongHeYunYingHD *v9; // rax
  CKiaFuRecharge *v10; // rax
  CKiaFuRecharge *v11; // rax
  COpenBeta *v12; // rax
  CKaiFuHuoDong *v14; // rax
  CharId_t Cid; // rbx
  DBService *v16; // rax
  int32_t Now; // edx
  MemChrBag mailItem; // [rsp+20h] [rbp-60h] BYREF
  std::string Param; // [rsp+40h] [rbp-40h] BYREF
  char v20; // [rsp+4Bh] [rbp-35h] BYREF
  int32_t daydiff; // [rsp+4Ch] [rbp-34h]
  int32_t loginCount; // [rsp+50h] [rbp-30h]
  int32_t loginRecord; // [rsp+54h] [rbp-2Ch]
  int32_t newRecord; // [rsp+58h] [rbp-28h]
  int32_t PetRecord; // [rsp+5Ch] [rbp-24h]
  int32_t Record; // [rsp+60h] [rbp-20h]
  int32_t nIndex; // [rsp+64h] [rbp-1Ch]
  CfgKaiFuHuoDongData *pCfg; // [rsp+68h] [rbp-18h]

  v2 = Player::getRecord(this, 1001);
  daydiff = Answer::DayTime::daydiff(v2);
  if ( daydiff > 0 && (v3 = Answer::Singleton<GameService>::instance(), GameService::getLine(v3) == 9) )
  {
    Player::kickBackFromCross(this, 10115);
  }
  else
  {
    if ( daydiff == 1 )
    {
      ++this->m_sysUser.continue_login_count;
    }
    else if ( daydiff > 1 )
    {
      this->m_sysUser.continue_login_count = 1;
    }
    if ( daydiff > 0 )
    {
      if ( this->m_pMap && Map::IsXinMoMap(this->m_pMap) )
        Player::OnBackCity(this, 1, 1);
      Player::saveOnlineTime(this);
      Player::clearRecordRange(this, 2000, 19999, daydiff);
      Player::syncTodayGoldPay(this);
      loginCount = Player::getRecord(this, 1011) + 1;
      Player::updateRecord(this, 1011, loginCount);
      loginRecord = Player::getRecord(this, 1069);
      newRecord = (loginRecord << daydiff) + 1;
      Player::updateRecord(this, 1069, newRecord);
      CExtSystemMgr::OnDaySwitch(&this->m_ExtSysMgr, daydiff);
      Player::SendFamilyWarIcon(this);
      v6 = Answer::Singleton<CUniteServer>::instance();
      CUniteServer::SendIconState(v6, this);
      v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      CFestivalDoubleEleven::SendIconState(v7, this);
      v8 = Answer::Singleton<CFestivalActivity>::instance();
      CFestivalActivity::SendIconState(v8, this);
      v9 = Answer::Singleton<CZongHeYunYingHD>::instance();
      CZongHeYunYingHD::SendIconState(v9, this);
      v10 = Answer::Singleton<CKiaFuRecharge>::instance();
      CKiaFuRecharge::SendIconState(v10, this);
      v11 = Answer::Singleton<CKiaFuRecharge>::instance();
      CKiaFuRecharge::SendChouJiangIconState(v11, this);
      v12 = Answer::Singleton<COpenBeta>::instance();
      COpenBeta::SendIconState(v12, this);
      Player::OnMonthSwitch(this);
      PetRecord = Player::getRecord(this, 1030);
      if ( PetRecord > 0 && Unit::getNow(this) >= PetRecord )
      {
        nIndex = Player::getRecord(this, 1031);
        v14 = Answer::Singleton<CKaiFuHuoDong>::instance();
        pCfg = CKaiFuHuoDong::GetKaiFuHuoDongData(v14, nIndex);
        if ( pCfg )
        {
          *(_QWORD *)&mailItem.itemId = 0x400000002LL;
          memset(&mailItem.itemCount, 0, 24);
          mailItem.itemCount = pCfg->Conditions;
          std::allocator<char>::allocator(&v20);
          std::string::string(&Param, byte_8E9580);
          Cid = Player::getCid(this);
          v16 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v16, 0, Cid, 6370, &mailItem, ITEM_CHANGE_REASON::ICR_KAI_HUO_DONG_PET, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v20);
        }
        Player::updateRecord(this, 1030, 0);
        CExtCharPet::SendPetStaus(&this->m_extCharPet);
      }
      Record = Player::getRecord(this, 1905);
      if ( Record > 0 )
        Player::AddCurrency(
          this,
          CURRENCY_TYPE::CURRENCY_GOLD,
          Record,
          CURRENCY_CHANGE_REASON::GCR_KAI_FU_HUO_DONG_FREE_GIFT,
          0);
    }
    Now = Unit::getNow(this);
    Player::updateRecord(this, 1001, Now);
  }
}


#####################################
void __cdecl Player::saveOnlineTime(Player *const this)
{
  int32_t v1; // r14d
  int32_t v2; // r13d
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v5; // rax
  int32_t nNowTime; // [rsp+1Ch] [rbp-24h]

  nNowTime = Unit::getNow(this);
  v1 = nNowTime - this->m_nLastSaveOnlineTime;
  v2 = Answer::DayTime::dayzero(this->m_nLastSaveOnlineTime);
  Cid = Player::getCid(this);
  ConnId = Player::getConnId(this);
  v5 = Answer::Singleton<DBService>::instance();
  DBService::SaveOnlineTime(v5, ConnId, Cid, v2, v1);
  this->m_nLastSaveOnlineTime = nNowTime;
}


#####################################
void __cdecl Player::sendActivityGain(
        Player *const this,
        int32_t activityId,
        int32_t exp,
        int32_t money,
        int32_t isEnd)
{
  int8_t m_connid; // bl
  GameService *v6; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, m_connid, Answer::PackType::PACK_DISPATCH, 0x27C1u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, activityId);
    Answer::NetPacket::writeInt32(packet, exp);
    Answer::NetPacket::writeInt32(packet, money);
    Answer::NetPacket::writeInt32(packet, isEnd);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v9 = this->m_connid;
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v10, v9, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::addNetPacket(Player *const this, Answer::NetPacket *inPacket, uint32_t rsize)
{
  uint32_t Size; // r14d
  uint16_t Proc; // r13
  Answer::PackType Type; // r12d
  int8_t m_connid; // bl
  GameService *v8; // rax
  uint32_t v9; // ebx
  const char *v10; // rcx
  uint32_t v11; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]

  if ( inPacket && Answer::NetPacket::getSize(inPacket) > rsize )
  {
    Size = Answer::NetPacket::getSize(inPacket);
    Proc = Answer::NetPacket::getProc(inPacket);
    Type = Answer::NetPacket::getType(inPacket);
    m_connid = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v8, m_connid, Type, Proc, Size);
    if ( packet )
    {
      v9 = Answer::NetPacket::getSize(inPacket) - rsize;
      v10 = &Answer::NetPacket::getBuffer(inPacket)[rsize];
      Answer::NetPacket::write(packet, v10, v9);
      v11 = Answer::NetPacket::getSize(inPacket) - rsize;
      Answer::NetPacket::setSize(packet, v11);
      Answer::SafeQueue<Answer::NetPacket *>::push(&this->m_netPackets, packet);
    }
  }
}


#####################################
void __cdecl Player::broadcastRevive(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pMap )
  {
    m_connid = this->m_connid;
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x283Du);
    if ( packet )
    {
      Cid = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Player::setOldPosition(Player *const this)
{
  bool v1; // al

  if ( this->m_pMap )
  {
    v1 = StaticObj::InDungeon(this) || StaticObj::InActivity(this);
    if ( !v1 && Map::CanStayInMap(this->m_pMap) )
    {
      this->m_oldPosition.runnerId = StaticObj::GetRunnerId(this);
      this->m_oldPosition.mapid = StaticObj::getMapId(this);
      *(Position *)&this->m_oldPosition.x = StaticObj::getCurrentTile(this);
    }
  }
}


#####################################
void __cdecl Player::addLogoutPacket(Player *const this, int32_t reason, int32_t param)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  void (__fastcall *v6)(Player *const, _QWORD, _QWORD, __int64); // r12
  __int64 Now; // rcx
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pMap )
  {
    m_connid = this->m_connid;
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 8u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, reason);
      Answer::NetPacket::writeInt32(packet, param);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Answer::SafeQueue<Answer::NetPacket *>::push(&this->m_netPackets, packet);
    }
  }
  else
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_INFO,
      "Player::addLogoutPacket with m_pMap == NULL, cid = %lld\n",
      this->m_chr.cid);
    v6 = (void (__fastcall *)(Player *const, _QWORD, _QWORD, __int64))*((_QWORD *)this->_vptr_Entity + 35);
    Now = (unsigned int)Unit::getNow(this);
    v6(this, (unsigned int)reason, (unsigned int)param, Now);
    v8 = Answer::Singleton<GameService>::instance();
    GameService::onPlayerLogout(v8, this);
  }
}


#####################################
void __cdecl Player::sendBasicInfo(Player *const this, int32_t reason)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  CGuiGuDaoRen *v8; // rax
  CActivityManager *v9; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( reason == 3 )
  {
    m_connid = this->m_connid;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x2828u);
    if ( !packet )
      return;
    Answer::NetPacket::writeInt32(packet, 0);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v6 = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v6, m_cgindex, packet);
  }
  Player::SyncTime(this);
  Player::sendChrLoginInInfo(this);
  Player::sendChrInfo(this);
  Player::sendCharAttrInfo(this);
  CExtCurrency::SendCurrencyInfo(&this->m_extCurrency, 1);
  CExtCharBag::SendBagItem(&this->m_extCharBag);
  CExtCharBag::SendBagSellItem(&this->m_extCharBag);
  CExtCharBag::SendLimitCount(&this->m_extCharBag);
  CExtEquip::SendEquipInfo(&this->m_extEquip);
  CExtEquip::SendGemInfo(&this->m_extEquip);
  CExtEquip::SendPosLevelInfo(&this->m_extEquip);
  CExtEquip::SendStrenGthenInfo(&this->m_extEquip);
  CChrDepot::SendDepotCurrency(&this->m_PlayerDepot);
  CChrDepot::SendDepotInfo(&this->m_PlayerDepot);
  CChrDepot::SendDepotItem(&this->m_PlayerDepot);
  CVip::SendVipInfo(&this->m_PlayerVip);
  CExtCharSkill::SendTalentInfo(&this->m_extCharSkill);
  CExtCharSkill::SendTalentAddon(&this->m_extCharSkill);
  CExtCharPet::SendPetInfo(&this->m_extCharPet);
  ChrTask::sendTaskList(&this->m_task);
  CExtMagicBox::SendItemCombiPoint(&this->m_extMagicBox);
  DailyActivity::SendSearchBackInfo(&this->m_PlayerDailyActivity);
  ChouJiang::SendChouJiangItem(&this->m_PlayerChouJiang);
  CBossKilledReward::SendBossKilledInfo(&this->m_CBossKilledReward);
  Player::sendAutoFight(this);
  Player::sendSystemSetting(this);
  Player::sendChrRecord(this);
  Player::sendLoginInfo(this);
  CSpecialEquip::SendActivationInfo(&this->m_CSpecialEquip);
  CExtChrTaskCycle::SendTaskCycle(&this->m_extTaskCycle);
  CMoneyRewardTask::sendTaskInfo(&this->m_CMoneyRewardTask);
  CMoneyRewardTask::SendPdbfTaskInfo(&this->m_CMoneyRewardTask);
  CMoneyRewardTask::SendBackEquipTaskInfo(&this->m_CMoneyRewardTask);
  CMoneyRewardTask::SendTrailerInfo(&this->m_CMoneyRewardTask);
  CMoneyRewardTask::SendXiangYaoTaskInfo(&this->m_CMoneyRewardTask);
  CMoneyRewardTask::SendShenWeiTaskInfo(&this->m_CMoneyRewardTask);
  DailyActivity::SendDailyActivityInfo(&this->m_PlayerDailyActivity);
  CExtCharWorship::SendWorshipInfo(&this->m_extCharWorship);
  CQiFu::SendQiFuInfo(&this->m_PlayerQiFu);
  CHuoYueDu::SendHuoYueDuInfo(&this->m_PlayerHuoYueDu);
  CShangCheng::SendLimitInfo(&this->m_PlayerShangCheng);
  CExtCharTitle::SendTitleInfo(&this->m_extCharTitle);
  CFriendExpReward::SendDieRecord(&this->m_FRiendExp);
  CFriendExpReward::SendDieBoard(&this->m_FRiendExp);
  CFaBao::SendAllFaBaoInfo(&this->m_PlayerFaBao);
  CCharWuHun::sendWuHunInfo(&this->m_CCharWuHun);
  CWuHunShop::sendShopRefreshTimes(&this->m_CWuHunShop);
  CExtCharJueWei::sendJueWeiInfo(&this->m_extCharJueWei);
  CExtCharWing::SendWingInfo(&this->m_extCharWing);
  CGoblin::SendAllGoblinInfo(&this->m_CGoblin);
  CShiZhuang::SendShiZhuangInfo(&this->m_extShiZhuang);
  CGoblin::SendAllShouHuRefiningInfo(&this->m_CGoblin);
  CGoblin::SendAllWingEquipPolishInfo(&this->m_CGoblin);
  CGoblin::SendAllMoFuZhuNengInfo(&this->m_CGoblin);
  CGoblin::SendAllWingEquipRefiningInfo(&this->m_CGoblin);
  CGoblin::SendAllVipEquipPosLevelInfo(&this->m_CGoblin);
  CExtCharFamily::SendHoe(&this->m_extCharFamily);
  CMingGeExt::SendMingGeBagInfo(&this->m_CMingGeExt, 1);
  CMingGeExt::SendMingGeBagInfo(&this->m_CMingGeExt, 2);
  CMingGeExt::SendMingGeBagInfo(&this->m_CMingGeExt, 3);
  CMingGeExt::SendMingGeInfo(&this->m_CMingGeExt);
  CKunExt::SendKunLingInfo(&this->m_CKunExt);
  CKunExt::SendLingZhuBagAllItem(&this->m_CKunExt);
  CKunExt::SendDanTianInfo(&this->m_CKunExt, -1);
  CKunExt::SendLingZhuPosInfo(&this->m_CKunExt, -1);
  CGongMing::SendGongMinInfo(&this->m_CGongMing);
  CExtEquip::SendShenYaoPosLevelInfo(&this->m_extEquip);
  CXinMo::SendXiMoInfo(&this->m_CXinMo);
  CXinMo::SendAllItem(&this->m_CXinMo);
  CXinMo::SendXinMoQiQingLevel(&this->m_CXinMo, 0);
  CXinMo::SendXinQingInfo(&this->m_CXinMo);
  CVip::SendClubInfo(&this->m_PlayerVip);
  CSpecialEquip::SendActivationInfo(&this->m_CSpecialEquip);
  CRongHe::SendAllRongHeInfo(&this->m_CRongHe);
  Player::SendJingLiValue(this);
  CharLittlerHelper::SendCharLittlerhelper(&this->m_CharLittlerhelper);
  CYunYingHD::SendShouChongInfo(&this->m_PlayerYunYingHD);
  v8 = Answer::Singleton<CGuiGuDaoRen>::instance();
  CGuiGuDaoRen::SendAllRongHeRecord(v8, this);
  Player::SendCycleTowerInfo(this);
  Player::sendActionList(this);
  Player::SendHDIcon(this);
  v9 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::NotifyActivityInfo(v9, this);
  CExtCharTeam::UpdateTeamSetting(&this->m_extCharTeam);
  CExtCharMysteryGift::SendMysteryGiftInfo(&this->m_extCharMysteryGift, 1);
  CExtCharWish::SendWishIcon(&this->m_extCharWish);
}


#####################################
void __cdecl Player::sendItemEffect(Player *const this, const std::string *const effect)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  int32_t x; // edx
  int32_t y; // edx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pMap )
  {
    m_connid = this->m_connid;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x2753u);
    if ( packet )
    {
      x = StaticObj::getCurrentTile(this).x;
      Answer::NetPacket::writeInt32(packet, x);
      y = StaticObj::getCurrentTile(this).y;
      Answer::NetPacket::writeInt32(packet, y);
      Answer::NetPacket::writeUTF8(packet, effect);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Player::sendGainInfo(Player *const this, int32_t type, int64_t value, BenefitType benefitType)
{
  int8_t m_connid; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( benefitType != BenefitType::BT_NORMAL || value )
  {
    m_connid = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, m_connid, Answer::PackType::PACK_DISPATCH, 0x2763u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, type);
      Answer::NetPacket::writeInt64(packet, value);
      Answer::NetPacket::writeInt32(packet, benefitType);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      m_cgindex = this->m_cgindex;
      v8 = this->m_connid;
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, m_cgindex, packet);
    }
  }
}


#####################################
void __cdecl Player::sendBuyItemInfo(
        Player *const this,
        int32_t item_id,
        int32_t item_type,
        int32_t count,
        int32_t money,
        int32_t index)
{
  int8_t m_connid; // bl
  GameService *v7; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v7, m_connid, Answer::PackType::PACK_DISPATCH, 0x2766u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, item_id);
    Answer::NetPacket::writeInt32(packet, item_type);
    Answer::NetPacket::writeInt32(packet, count);
    Answer::NetPacket::writeInt32(packet, money);
    Answer::NetPacket::writeInt32(packet, index);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v10 = this->m_connid;
    v11 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v11, v10, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendSellItemInfo(
        Player *const this,
        int32_t item_id,
        int32_t item_type,
        int32_t count,
        int64_t money)
{
  int8_t m_connid; // bl
  GameService *v6; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, m_connid, Answer::PackType::PACK_DISPATCH, 0x2767u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, item_id);
    Answer::NetPacket::writeInt32(packet, item_type);
    Answer::NetPacket::writeInt32(packet, count);
    Answer::NetPacket::writeInt64(packet, money);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v9 = this->m_connid;
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v10, v9, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendKillerRankSelf(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x27F2u);
  if ( packet )
  {
    Record = Player::getRecord(this, 1010);
    Answer::NetPacket::writeInt32(packet, Record);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v6 = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v6, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendPreventWallow(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2823u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_sysUserPreventWallow.isGrowUp);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v5 = this->m_connid;
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v6, v5, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendChrLoginInInfo(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  CfgData *v3; // rax
  int8_t Debug; // dl
  GameService *v5; // rax
  int32_t Line; // edx
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2802u);
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->m_sysUser.uid);
    Answer::NetPacket::writeInt64(packet, this->m_chr.cid);
    Answer::NetPacket::writeInt8(packet, this->m_sysUser.gm_level);
    v3 = Answer::Singleton<CfgData>::instance();
    Debug = CfgData::getDebug(v3);
    Answer::NetPacket::writeInt8(packet, Debug);
    v5 = Answer::Singleton<GameService>::instance();
    Line = GameService::getLine(v5);
    Answer::NetPacket::writeInt32(packet, Line);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v9 = this->m_connid;
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v10, v9, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendGambel(Player *const this, const MemChrBagVector *const item)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  int32_t v4; // eax
  const MemChrBag *v5; // rax
  const MemChrBag *v6; // rax
  const MemChrBag *v7; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > it; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x27F6u);
  if ( packet )
  {
    v4 = std::vector<MemChrBag>::size(item);
    Answer::NetPacket::writeInt32(packet, v4);
    for ( it._M_current = std::vector<MemChrBag>::begin(item)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<MemChrBag>::end(item)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&it, &__rhs) )
        break;
      v5 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v5->itemId);
      v6 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
      Answer::NetPacket::writeInt16(packet, v6->itemClass);
      v7 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
      Answer::NetPacket::writeInt16(packet, v7->itemCount);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v10 = this->m_connid;
    v11 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v11, v10, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendPublicChat(Player *const this, int32_t channel, Answer::NetPacket *inPacket)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  int32_t v5; // eax
  CharId_t Cid; // rax
  int32_t Sid; // eax
  int8_t VipType; // al
  int8_t VipLevel; // al
  GameService *v10; // rax
  int8_t Line; // al
  Job_t Job; // al
  int8_t JueWei; // al
  uint32_t Size; // ebx
  char *Buffer; // rax
  uint32_t WOffset; // eax
  char v17; // r12
  char v18; // r13
  bool v19; // al
  bool v20; // r14
  GameService *v21; // rax
  std::string val; // [rsp+20h] [rbp-90h] BYREF
  std::string v24; // [rsp+30h] [rbp-80h] BYREF
  std::string v25; // [rsp+40h] [rbp-70h] BYREF
  std::string __lhs; // [rsp+50h] [rbp-60h] BYREF
  std::string v27; // [rsp+60h] [rbp-50h] BYREF
  std::string v28; // [rsp+70h] [rbp-40h] BYREF
  Answer::NetPacket *chatPacket; // [rsp+78h] [rbp-38h]

  if ( inPacket )
  {
    m_connid = this->m_connid;
    v4 = Answer::Singleton<GameService>::instance();
    chatPacket = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x27F7u);
    if ( chatPacket )
    {
      Answer::NetPacket::writeInt32(chatPacket, channel);
      v5 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
      Answer::NetPacket::writeInt32(chatPacket, v5);
      Answer::NetPacket::writeInt8(chatPacket, this->m_sysUser.gm_level);
      Cid = Player::getCid(this);
      Answer::NetPacket::writeInt64(chatPacket, Cid);
      Sid = Player::getSid(this);
      Answer::NetPacket::writeInt32(chatPacket, Sid);
      Player::GetPassport((Player *const)&val);
      Answer::NetPacket::writeUTF8(chatPacket, &val);
      std::string::~string(&val);
      Player::getIP((Player *const)&v24);
      Answer::NetPacket::writeUTF8(chatPacket, &v24);
      std::string::~string(&v24);
      VipType = CVip::GetVipType(&this->m_PlayerVip);
      Answer::NetPacket::writeInt8(chatPacket, VipType);
      VipLevel = CVip::GetVipLevel(&this->m_PlayerVip);
      Answer::NetPacket::writeInt8(chatPacket, VipLevel);
      Answer::NetPacket::writeInt8(chatPacket, this->m_chr.sex);
      v10 = Answer::Singleton<GameService>::instance();
      Line = GameService::getLine(v10);
      Answer::NetPacket::writeInt8(chatPacket, Line);
      Player::getName((const Player *const)&v25);
      Answer::NetPacket::writeUTF8(chatPacket, &v25);
      std::string::~string(&v25);
      Job = Player::getJob(this);
      Answer::NetPacket::writeInt8(chatPacket, Job);
      JueWei = CExtCharJueWei::GetJueWei(&this->m_extCharJueWei);
      Answer::NetPacket::writeInt8(chatPacket, JueWei);
      CExtCharTencent::AppendInfo(&this->m_extCharTencent, chatPacket);
      CVplan::AppendYYInfo(&this->m_Vplan, chatPacket);
      CVplan::AppendSwVipInfo(&this->m_Vplan, chatPacket);
      Answer::NetPacket::writeInt8(chatPacket, this->m_connid);
      Size = Answer::NetPacket::getSize(inPacket);
      Buffer = Answer::NetPacket::getBuffer(inPacket);
      Answer::NetPacket::write(chatPacket, Buffer, Size);
      WOffset = Answer::NetPacket::getWOffset(chatPacket);
      Answer::NetPacket::setSize(chatPacket, WOffset);
      v17 = 0;
      v18 = 0;
      Player::GetPlatform((const Player *const)&__lhs);
      v19 = 0;
      if ( std::operator!=<char>(&__lhs, "37wan") )
      {
        Player::GetPlatform((const Player *const)&v27);
        v17 = 1;
        if ( std::operator!=<char>(&v27, "tanwan") )
        {
          Player::GetPlatform((const Player *const)&v28);
          v18 = 1;
          if ( std::operator!=<char>(&v28, "w360") )
            v19 = 1;
        }
      }
      v20 = v19;
      if ( v18 )
        std::string::~string(&v28);
      if ( v17 )
        std::string::~string(&v27);
      std::string::~string(&__lhs);
      if ( v20
        || (v21 = Answer::Singleton<GameService>::instance(),
            !GameService::SendChatValidate(v21, this, channel, chatPacket)) )
      {
        Player::SendPublicChat(this, channel, chatPacket);
      }
    }
  }
}


#####################################
int32_t __cdecl Player::ChatValidateed(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::_Ios_Openmode v3; // eax
  CharId_t Cid; // r13
  int8_t v5; // r12
  GameService *v6; // rax
  int32_t RunnerId; // r12d
  CharId_t SendCharId; // rbx
  GameService *v9; // rax
  _BYTE v11[16]; // [rsp+10h] [rbp-340h] BYREF
  __int64 v12; // [rsp+20h] [rbp-330h] BYREF
  ChatValidate Stu; // [rsp+180h] [rbp-1D0h] BYREF
  std::string Key; // [rsp+1C0h] [rbp-190h] BYREF
  std::string Md5String; // [rsp+1D0h] [rbp-180h] BYREF
  std::string Sid; // [rsp+1E0h] [rbp-170h] BYREF
  std::string Name; // [rsp+1F0h] [rbp-160h] BYREF
  std::string PassPort; // [rsp+200h] [rbp-150h] BYREF
  std::string Md5Value; // [rsp+210h] [rbp-140h] BYREF
  std::string Chat; // [rsp+220h] [rbp-130h] BYREF
  char v21; // [rsp+22Fh] [rbp-121h] BYREF
  _BYTE v22[16]; // [rsp+230h] [rbp-120h] BYREF
  std::string v23; // [rsp+240h] [rbp-110h] BYREF
  std::string v24; // [rsp+250h] [rbp-100h] BYREF
  std::string __rhs; // [rsp+260h] [rbp-F0h] BYREF
  std::string __lhs; // [rsp+270h] [rbp-E0h] BYREF
  Answer::MD5 v27; // [rsp+280h] [rbp-D0h] BYREF
  int32_t nId; // [rsp+31Ch] [rbp-34h]
  int8_t Validateed; // [rsp+323h] [rbp-2Dh]
  int32_t SidInt; // [rsp+324h] [rbp-2Ch]
  Player *player; // [rsp+328h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  Validateed = Answer::NetPacket::readInt8(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&Chat, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&Md5Value, (bool)inPacket);
  Player::GetPassport((Player *const)&PassPort);
  Player::getName((const Player *const)&Name);
  SidInt = Player::getSid(this);
  std::allocator<char>::allocator(&v21);
  std::string::string(&Sid, byte_8E9580);
  std::allocator<char>::~allocator(&v21);
  v3 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v11, (unsigned int)v3);
  std::ostream::operator<<(&v12, (unsigned int)SidInt);
  std::operator>><char>(v11, &Sid);
  Player::GetPlatform((const Player *const)v22);
  std::operator+<char>(&__lhs, (const char *)&Chat);
  std::operator+<char>(&__rhs, &__lhs);
  std::operator+<char>(&v24, &__rhs);
  std::operator+<char>(&v23, &v24);
  std::operator+<char>(&Md5String, &v23);
  std::string::~string(&v23);
  std::string::~string(&v24);
  std::string::~string(&__rhs);
  std::string::~string(&__lhs);
  std::string::~string(v22);
  Answer::MD5::MD5(&v27);
  Answer::MD5::md5sum((Answer::MD5 *const)&Key, (const std::string *const)&v27);
  Answer::MD5::~MD5(&v27);
  if ( std::operator!=<char>(&Md5Value, &Key) )
  {
    v2 = 10002;
  }
  else
  {
    Cid = Player::getCid(this);
    v5 = Validateed;
    v6 = Answer::Singleton<GameService>::instance();
    GameService::GetChatValidate(&Stu, v6, nId, v5, Cid);
    if ( Stu.SendPacket )
    {
      RunnerId = StaticObj::GetRunnerId(this);
      SendCharId = Stu.SendCharId;
      v9 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v9, SendCharId, RunnerId, 1);
      if ( player )
        Player::SendPublicChat(player, Stu.Channel, Stu.SendPacket);
    }
    v2 = 0;
    ChatValidate::~ChatValidate(&Stu);
  }
  std::string::~string(&Key);
  std::string::~string(&Md5String);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v11);
  std::string::~string(&Sid);
  std::string::~string(&Name);
  std::string::~string(&PassPort);
  std::string::~string(&Md5Value);
  std::string::~string(&Chat);
  return v2;
}


#####################################
void __cdecl Player::SendPublicChat(Player *const this, int32_t channel, Answer::NetPacket *inPacket)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  GameService *v6; // rax
  GameService *v7; // rax

  if ( inPacket )
  {
    if ( channel == 1 )
    {
LABEL_3:
      m_connid = this->m_connid;
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, m_connid, inPacket);
      return;
    }
    if ( channel == 4 && Player::IsInTeam(this) )
    {
      CExtCharTeam::Broadcast(&this->m_extCharTeam, inPacket);
      return;
    }
    if ( channel == 5 && this->m_pMap )
    {
      Map::broadcast(this->m_pMap, inPacket);
      return;
    }
    if ( channel == 6 )
    {
      v6 = Answer::Singleton<GameService>::instance();
      if ( GameService::getLine(v6) != 9 )
        goto LABEL_3;
      goto LABEL_15;
    }
    if ( channel == 7 )
    {
LABEL_15:
      v7 = Answer::Singleton<GameService>::instance();
      GameService::broadcast(v7, inPacket);
      return;
    }
    Answer::NetPacket::destroy(inPacket);
  }
}


#####################################
int32_t __cdecl Player::onBuyXuWuValue(Player *const this, Answer::NetPacket *inPacket)
{
  unsigned int nTime; // [rsp+18h] [rbp-8h]
  int32_t ConstGold; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  nTime = Player::getRecord(this, 2107);
  if ( nTime >= 0xA )
    return 10002;
  if ( nTime )
    ConstGold = 1000 * nTime;
  else
    ConstGold = 500;
  if ( !Player::DecCurrency(
          this,
          CURRENCY_TYPE::CURRENCY_GOLD,
          ConstGold,
          CURRENCY_CHANGE_REASON::GCR_BUY_XU_WU_VALUE,
          0) )
    return 10002;
  Player::updateRecord(this, 2107, nTime + 1);
  Player::updateRecord(this, 2106, 0);
  return 0;
}


#####################################
void __cdecl Player::setNetPacketHandler(int32_t proc, Player::NetPacketHandler handler)
{
  __int64 v2; // rax

  if ( proc > 5 && proc <= 996 )
  {
    v2 = proc;
    Player::m_netPacketHandlers[v2].__pfn = handler.__pfn;
    *(_QWORD *)(v2 * 16 + 101567144) = handler.__delta;
  }
}


#####################################
void __cdecl Player::setBaseAttr(Player *const this)
{
  int32_t v1; // r13d
  int32_t Job; // r12d
  CfgData *v3; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  int32_t v6; // edx
  CfgLevelAttr levelAttr; // [rsp+10h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > it; // [rsp+50h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+60h] [rbp-30h] BYREF

  v1 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  Job = Player::getJob(this);
  v3 = Answer::Singleton<CfgData>::instance();
  CfgData::getLevelAttr(&levelAttr, v3, Job, v1);
  if ( levelAttr.job > 0 && levelAttr.level > 0 )
  {
    for ( it._M_current = std::vector<AttrAddon>::begin(&levelAttr.addonattr)._M_current;
          ;
          __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<AttrAddon>::end(&levelAttr.addonattr)._M_current;
      if ( !__gnu_cxx::operator!=<AttrAddon *,std::vector<AttrAddon>>(&it, &__rhs) )
        break;
      addon = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it)->addon;
      index = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it)->index;
      Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, addon);
      if ( __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it)->index == 45 )
      {
        v6 = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it)->addon;
        Player::AddBeiGongAttr(this, 1, v6);
      }
    }
  }
  CfgLevelAttr::~CfgLevelAttr(&levelAttr);
}


#####################################
void __cdecl Player::recalcAttr(Player *const this, bool bNow, bool bInit)
{
  CKaiFuHuoDong *v3; // rax
  CObjAttrs newAttr; // [rsp+10h] [rbp-200h] BYREF
  CObjAttrs oldAttr; // [rsp+E0h] [rbp-130h] BYREF
  AttrAddon addon; // [rsp+1B0h] [rbp-60h] BYREF
  AttrAddonList addAttrs; // [rsp+1C0h] [rbp-50h] BYREF
  int32_t ShiHua; // [rsp+1D4h] [rbp-3Ch]
  int32_t Valuse; // [rsp+1D8h] [rbp-38h]
  int32_t DropRate; // [rsp+1DCh] [rbp-34h]
  int32_t PetRecord; // [rsp+1E0h] [rbp-30h]
  int32_t nIndex; // [rsp+1E4h] [rbp-2Ch]
  CfgKaiFuHuoDongData *pCfg; // [rsp+1E8h] [rbp-28h]
  int32_t i; // [rsp+1F4h] [rbp-1Ch]
  int32_t nOldAttr; // [rsp+1F8h] [rbp-18h]
  int32_t nNewAttr; // [rsp+1FCh] [rbp-14h]

  if ( !bNow )
  {
    this->m_needRecalAttr = 1;
  }
  else
  {
    this->m_needRecalAttr = 0;
    qmemcpy(&oldAttr, Unit::GetBaseAttr(this), sizeof(oldAttr));
    std::map<int,int>::clear(&this->m_BeiGongAttr);
    Unit::ResetAttrs(this);
    Player::setBaseAttr(this);
    CExtCharSkill::AddCharAttr(&this->m_extCharSkill);
    CExtEquip::AddCharAttr(&this->m_extEquip);
    CExtCharPet::AddCharAttr(&this->m_extCharPet);
    CExtCharWing::AddCharAttr(&this->m_extCharWing);
    CExtCharJueWei::AddCharAttr(&this->m_extCharJueWei);
    CFaBao::AddPlayerAttr(&this->m_PlayerFaBao);
    CExtCharTitle::AddCharAttr(&this->m_extCharTitle);
    CVip::AddVipAttr(&this->m_PlayerVip);
    CExtCharFamily::AddSkillAttr(&this->m_extCharFamily);
    CXingMai::AddCharAttr(&this->m_XingMai);
    CTianLing::AddCharAttr(&this->m_TianLing);
    CSpecialEquip::AddCharAttr(&this->m_CSpecialEquip);
    Curse::AddCharAttr(&this->m_Curse);
    CShenWei::AddCharAttr(&this->m_ShenWei);
    CCharWuHun::AddCharAttr(&this->m_CCharWuHun);
    CGoblin::AddChrAttr(&this->m_CGoblin);
    CShiZhuang::AddPlayerAttr(&this->m_extShiZhuang);
    CVplan::AddAttr(&this->m_Vplan);
    CGoblin::AddShouHuChrAttr(&this->m_CGoblin);
    CGoblin::AddWingEquipPolishChrAttr(&this->m_CGoblin);
    CGoblin::AddWingEquipRefiningChrAttr(&this->m_CGoblin);
    CGoblin::AddVipEquipPosLevelCharAttr(&this->m_CGoblin);
    CMingGeExt::AddAttr(&this->m_CMingGeExt);
    CKunExt::AddCharAttr(&this->m_CKunExt);
    CGongMing::AddCharAttr(&this->m_CGongMing);
    CXinMo::AddCharAttr(&this->m_CXinMo);
    ShiHua = Player::getRecord(this, 1153);
    if ( ShiHua > 0 )
      Unit::AddAttrValue(this, CObjAttrs::Index_T::ATTR_XUAN_YUN, ShiHua);
    Valuse = Player::getRecord(this, 1154);
    if ( Valuse > 0 )
      Unit::AddAttrValue(this, CObjAttrs::Index_T::ATTR_QIE_GE_PEC, Valuse);
    DropRate = Player::getRecord(this, 37505);
    if ( DropRate > 0 )
      Unit::AddAttrValue(this, CObjAttrs::Index_T::ATTR_DROP_RATE, DropRate);
    PetRecord = Player::getRecord(this, 1030);
    if ( PetRecord > 0 )
    {
      nIndex = Player::getRecord(this, 1031);
      v3 = Answer::Singleton<CKaiFuHuoDong>::instance();
      pCfg = CKaiFuHuoDong::GetKaiFuHuoDongData(v3, nIndex);
      if ( pCfg )
        Unit::AddAttrValue(this, CObjAttrs::Index_T::ATTR_QIE_GE_PEC, pCfg->PetAttr);
    }
    CharLittlerHelper::AddCharAttr(&this->m_CharLittlerhelper);
    Player::AddAppendAttr(this);
    Player::CalBattle(this);
    Unit::adjustUnitAttr(this);
    if ( !bInit )
    {
      std::list<AttrAddon>::list(&addAttrs);
      qmemcpy(&newAttr, Unit::GetBaseAttr(this), sizeof(newAttr));
      for ( i = 0; i <= 49; ++i )
      {
        nOldAttr = CObjAttrs::GetAttr(&oldAttr, (const CObjAttrs::Index_T)i);
        nNewAttr = CObjAttrs::GetAttr(&newAttr, (const CObjAttrs::Index_T)i);
        if ( nNewAttr > nOldAttr )
        {
          addon.index = i;
          addon.addon = nNewAttr - nOldAttr;
          std::list<AttrAddon>::push_back(&addAttrs, &addon);
        }
      }
      if ( !std::list<AttrAddon>::empty(&addAttrs) )
        Player::sendAttrAddon(this, &addAttrs);
      CObjAttrs::~CObjAttrs(&newAttr);
      std::list<AttrAddon>::~list(&addAttrs);
    }
    Unit::setNeedSync(this);
    Unit::setNeedSyncAttr(this);
    Player::SendBeiGongAttr(this);
    CObjAttrs::~CObjAttrs(&oldAttr);
  }
}


#####################################
int32_t __cdecl Player::verifyBagInfoForGroup(
        Player *const this,
        Answer::NetPacket *inPacket,
        MemChrBagVector *const slotDataVector,
        int32_t item_type,
        int32_t count)
{
  int32_t v5; // ebx
  BagSlot *v6; // rax
  int32_t itemId; // ebx
  CfgData *v8; // rax
  int32_t v9; // eax
  MemChrBag bag; // [rsp+20h] [rbp-C0h] BYREF
  MemChrBag slot_0; // [rsp+40h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<BagSlot*,std::vector<BagSlot> > it; // [rsp+60h] [rbp-80h] BYREF
  BagSlot slot; // [rsp+70h] [rbp-70h] BYREF
  BagSlotVector slotVector; // [rsp+80h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<BagSlot*,std::vector<BagSlot> > __rhs; // [rsp+A0h] [rbp-40h] BYREF
  int32_t slotCount; // [rsp+B4h] [rbp-2Ch]
  int32_t item_count; // [rsp+B8h] [rbp-28h]
  int32_t item_id; // [rsp+BCh] [rbp-24h]
  int32_t newItemCount; // [rsp+C0h] [rbp-20h]
  int32_t i; // [rsp+C4h] [rbp-1Ch]
  CfgItem *pItem; // [rsp+C8h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  slotCount = Answer::NetPacket::readInt32(inPacket);
  std::vector<BagSlot>::vector(&slotVector);
  if ( (unsigned int)slotCount <= 0x64 )
  {
    std::vector<BagSlot>::reserve(&slotVector, slotCount);
    for ( i = 0; i < slotCount; ++i )
    {
      slot = 0;
      slot.bag = Answer::NetPacket::readInt32(inPacket);
      slot.slot = Answer::NetPacket::readInt32(inPacket);
      std::vector<BagSlot>::push_back(&slotVector, &slot);
    }
    if ( count >= 0 )
    {
      item_count = 0;
      item_id = 0;
      for ( it._M_current = std::vector<BagSlot>::begin(&slotVector)._M_current;
            ;
            __gnu_cxx::__normal_iterator<BagSlot *,std::vector<BagSlot>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<BagSlot>::end(&slotVector)._M_current;
        if ( !__gnu_cxx::operator!=<BagSlot *,std::vector<BagSlot>>(&it, &__rhs) )
          break;
        v6 = __gnu_cxx::__normal_iterator<BagSlot *,std::vector<BagSlot>>::operator->(&it);
        Player::getBagSlotData(&slot_0, this, v6->slot);
        if ( !slot_0.itemId )
        {
          v5 = 10002;
          goto LABEL_22;
        }
        itemId = slot_0.itemId;
        v8 = Answer::Singleton<CfgData>::instance();
        pItem = CfgData::getItem(v8, itemId);
        if ( !pItem || pItem->type != item_type )
        {
          v5 = 10002;
          goto LABEL_22;
        }
        item_id = pItem->id;
        item_count += slot_0.itemCount;
      }
      if ( item_count % count )
        v9 = item_count / count;
      else
        v9 = item_count / count + 1;
      newItemCount = v9;
      *(_DWORD *)&bag.itemClass = 1;
      memset(&bag.bind, 0, 20);
      bag.itemId = item_id;
      bag.itemCount = v9;
      std::vector<MemChrBag>::push_back(slotDataVector, &bag);
      v5 = 0;
    }
    else
    {
      v5 = 10002;
    }
  }
  else
  {
    v5 = 10002;
  }
LABEL_22:
  std::vector<BagSlot>::~vector(&slotVector);
  return v5;
}


#####################################
int32_t __cdecl Player::verifyBagInfo(
        Player *const this,
        const Int32Vector *const vSlot,
        int32_t nItemId,
        int32_t nCount)
{
  int32_t *v5; // rax
  int nCounta; // [rsp+8h] [rbp-48h]
  MemChrBag slot; // [rsp+20h] [rbp-30h] BYREF
  int32_t slotCount; // [rsp+48h] [rbp-8h]
  int32_t i; // [rsp+4Ch] [rbp-4h]

  nCounta = nCount;
  if ( nCount <= 0 )
    return 0;
  slotCount = std::vector<int>::size(vSlot);
  for ( i = 0; i < slotCount; ++i )
  {
    v5 = (int32_t *)std::vector<int>::operator[](vSlot, i);
    Player::getBagSlotData(&slot, this, *v5);
    if ( !slot.itemId )
      return 10002;
    if ( slot.itemId != nItemId )
      return 10002;
    if ( slot.itemCount >= nCounta )
    {
      nCounta = 0;
      break;
    }
    nCounta -= slot.itemCount;
  }
  if ( nCounta <= 0 )
    return 0;
  else
    return 10002;
}


#####################################
bool __cdecl Player::queryBagInfo(Player *const this, Answer::NetPacket *inPacket, Int32Vector *const vSlot)
{
  int *v4; // rbx
  int32_t slotCount; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket )
    return 0;
  slotCount = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned int)slotCount > 0x96 )
    return 0;
  std::vector<int>::resize(vSlot, slotCount, 0);
  for ( i = 0; i < slotCount; ++i )
  {
    v4 = std::vector<int>::operator[](vSlot, i);
    *v4 = Answer::NetPacket::readInt32(inPacket);
  }
  return 1;
}


#####################################
int32_t __cdecl Player::queryAutoBuyBagInfo(
        Player *const this,
        const Int32Vector *const vSlot,
        int32_t nItemId,
        int32_t *const count,
        int32_t nShopId)
{
  int32_t *v6; // rax
  CfgData *v7; // rax
  MemChrBag bagSlot; // [rsp+30h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+5Ch] [rbp-24h]
  int32_t slotCount; // [rsp+60h] [rbp-20h]
  int32_t i; // [rsp+64h] [rbp-1Ch]
  CfgGameShop *pCfgGameShop; // [rsp+68h] [rbp-18h]
  int32_t totalCost; // [rsp+74h] [rbp-Ch]
  int64_t nTotalGold; // [rsp+78h] [rbp-8h]

  if ( *count <= 0 )
    return 0;
  nCount = *count;
  slotCount = std::vector<int>::size(vSlot);
  for ( i = 0; i < slotCount; ++i )
  {
    v6 = (int32_t *)std::vector<int>::operator[](vSlot, i);
    Player::getBagSlotData(&bagSlot, this, *v6);
    if ( !bagSlot.itemId )
      return 10002;
    if ( bagSlot.itemId != nItemId )
      return 10002;
    if ( bagSlot.itemCount >= nCount )
    {
      nCount = 0;
      break;
    }
    nCount -= bagSlot.itemCount;
  }
  if ( nCount > 0 )
  {
    v7 = Answer::Singleton<CfgData>::instance();
    pCfgGameShop = CfgData::GetGameShop(v7, nShopId);
    if ( !pCfgGameShop )
      return 10002;
    totalCost = nCount * pCfgGameShop->Price;
    nTotalGold = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD);
    if ( totalCost > nTotalGold )
      return 10002;
    Player::DecCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, totalCost, CURRENCY_CHANGE_REASON::GCR_AUTOBUYBAG, nShopId);
  }
  *count -= nCount;
  return 0;
}


#####################################
bool __cdecl Player::isDeadProc(const Player *const this, ProcId_t nProc)
{
  if ( nProc > 0x4E20u && nProc <= 0x61AAu )
    return 1;
  if ( nProc <= 0x3Au )
    return nProc >= 0x38u || nProc == 8 || nProc == 38;
  if ( nProc == 434 )
    return 1;
  if ( nProc > 0x1B2u )
    return nProc == 440 || nProc == 463;
  return nProc == 197;
}


#####################################
bool __cdecl Player::checkNetPackets(Player *const this)
{
  uint16_t Proc; // ax
  int v3; // eax
  ProcId_t v5; // ax
  int8_t ConnId; // bl
  DBService *v7; // rax
  proc_log stu; // [rsp+20h] [rbp-80h] BYREF
  Player::NetPacketHandler handler; // [rsp+50h] [rbp-50h]
  _BYTE v11[16]; // [rsp+60h] [rbp-40h] BYREF
  _BYTE v12[16]; // [rsp+70h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+80h] [rbp-20h]
  ProcId_t nProc; // [rsp+8Ah] [rbp-16h]
  int32_t nErr; // [rsp+8Ch] [rbp-14h]

  packet = 0;
  while ( 1 )
  {
    packet = Answer::SafeQueue<Answer::NetPacket *>::pop(&this->m_netPackets);
    if ( !packet )
      break;
    nProc = Answer::NetPacket::getProc(packet);
    if ( !Unit::isAlive(this) && !Player::isDeadProc(this, nProc) )
    {
      Answer::NetPacket::destroy(packet);
    }
    else
    {
      Proc = Answer::NetPacket::getProc(packet);
      handler = Player::getNetPacketHandler(Proc);
      if ( handler.__pfn )
      {
        v3 = ((__int64)handler.__pfn & 1) != 0
           ? (*(__int64 (__fastcall **)(char *, Answer::NetPacket *))(*(char **)((char *)&this->_vptr_Entity
                                                                               + handler.__delta)
                                                                    + (unsigned __int64)handler.__pfn
                                                                    - 1))(
               (char *)this + handler.__delta,
               packet)
           : handler.__pfn((char *)this + handler.__delta, packet);
        if ( v3 == 1 )
        {
          Answer::NetPacket::destroy(packet);
          return 0;
        }
      }
      v5 = Answer::NetPacket::getProc(packet);
      nErr = CExtSystemMgr::DispatchNetDatas(&this->m_ExtSysMgr, v5, packet);
      if ( Player::NeedJianKong(this) )
      {
        proc_log::proc_log(&stu);
        stu.log_Sid = Player::getSid(this);
        stu.log_time = Unit::getNow(this);
        Player::GetPassport((Player *const)v11);
        std::string::operator=(&stu.passport, v11);
        std::string::~string(v11);
        stu.cid = Player::getCid(this);
        Player::getName((const Player *const)v12);
        std::string::operator=(&stu.name, v12);
        std::string::~string(v12);
        stu.op_time = Unit::getNow(this);
        stu.proc_id = Answer::NetPacket::getProc(packet);
        ConnId = Player::getConnId(this);
        v7 = Answer::Singleton<DBService>::instance();
        DBService::AddPlatformLog(v7, ConnId, PLATFORM_LOG_DATA_TYPE::PLDT_PROC, &stu);
        proc_log::~proc_log(&stu);
      }
      Answer::NetPacket::destroy(packet);
      if ( nProc == 8 )
        return 1;
    }
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onLogout(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t Int32; // edx
  int32_t reason; // [rsp+18h] [rbp-8h]

  if ( !inPacket )
    return 10002;
  reason = Answer::NetPacket::readInt32(inPacket);
  Int32 = Answer::NetPacket::readInt32(inPacket);
  Player::onLogout(this, reason, Int32);
  return 0;
}


#####################################
void __cdecl Player::onLogout(Player *const this, int32_t nReason, int32_t nParam)
{
  int32_t MapId; // r14d
  int32_t Now; // r13d
  CharId_t Cid; // r12
  int8_t m_connid; // bl
  DBService *v7; // rax
  int v8; // r13d
  const char *v9; // rbx
  int v10; // eax
  DBService *v11; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  ChrTask *Task; // rax
  DBService *v14; // rax
  std::_Ios_Openmode v15; // eax
  unsigned int v16; // r14d
  CExtCharTencent *CharTencent; // rsi
  unsigned int v18; // ebx
  int64_t Uid; // r12
  unsigned int Sid; // r13d
  __int64 v21; // rax
  __int64 v22; // rax
  __int64 v23; // rax
  __int64 v24; // rax
  __int64 v25; // rax
  __int64 v26; // rax
  __int64 v27; // rax
  __int64 v28; // rax
  __int64 v29; // rax
  __int64 v30; // rax
  __int64 v31; // rax
  __int64 v32; // rax
  __int64 v33; // rax
  __int64 v34; // rax
  __int64 v35; // rax
  __int64 v36; // rax
  __int64 v37; // rax
  __int64 v38; // rax
  __int64 v39; // rax
  __int64 v40; // rax
  __int64 v41; // rax
  __int64 v42; // rax
  __int64 v43; // rax
  __int64 v44; // rax
  __int64 v45; // rax
  __int64 v46; // rax
  __int64 v47; // rax
  __int64 v48; // rax
  CHttpRequest *v49; // rax
  int32_t total_online_time; // ebx
  MapManager *v51; // rax
  int v52; // eax
  char LogString[4096]; // [rsp+20h] [rbp-1400h] BYREF
  _BYTE v56[16]; // [rsp+1020h] [rbp-400h] BYREF
  __int64 v57; // [rsp+1030h] [rbp-3F0h] BYREF
  logout_log stu; // [rsp+1190h] [rbp-290h] BYREF
  Log360 Stu; // [rsp+1220h] [rbp-200h] BYREF
  std::string key; // [rsp+1250h] [rbp-1D0h] BYREF
  _BYTE v61[16]; // [rsp+1260h] [rbp-1C0h] BYREF
  std::string v62; // [rsp+1270h] [rbp-1B0h] BYREF
  _BYTE v63[16]; // [rsp+1280h] [rbp-1A0h] BYREF
  _BYTE v64[16]; // [rsp+1290h] [rbp-190h] BYREF
  _BYTE v65[16]; // [rsp+12A0h] [rbp-180h] BYREF
  std::string __lhs; // [rsp+12B0h] [rbp-170h] BYREF
  std::string v67; // [rsp+12C0h] [rbp-160h] BYREF
  std::string v68; // [rsp+12D0h] [rbp-150h] BYREF
  int32_t val[4]; // [rsp+12E0h] [rbp-140h] BYREF
  std::string __rhs; // [rsp+12F0h] [rbp-130h] BYREF
  int32_t v71[4]; // [rsp+1300h] [rbp-120h] BYREF
  int64_t v72[2]; // [rsp+1310h] [rbp-110h] BYREF
  Answer::MD5 v73; // [rsp+1320h] [rbp-100h] BYREF
  _BYTE v74[16]; // [rsp+13C0h] [rbp-60h] BYREF
  CExtCharTencent v75; // [rsp+13D0h] [rbp-50h] BYREF

  Player::BreakGather(this, 0);
  if ( nReason == 1 || nReason == 2 || nReason == 4 )
  {
    ++this->m_chr.logout_count;
    MapId = StaticObj::getMapId(this);
    Now = Unit::getNow(this);
    Cid = Player::getCid(this);
    m_connid = this->m_connid;
    v7 = Answer::Singleton<DBService>::instance();
    DBService::logPlayerLogin(v7, m_connid, Cid, 0, Now, MapId);
    memset(&Stu, 0, sizeof(Stu));
    std::string::string(&Stu.Interface);
    std::string::string(&Stu.passport);
    std::string::string(&Stu.LogString);
    std::string::operator=(&Stu, "logout");
    Stu.UseSid = Player::getSid(this);
    Player::GetPassport((Player *const)v61);
    std::string::operator=(&Stu.passport, v61);
    std::string::~string(v61);
    Stu.Cid = Player::getCid(this);
    memset(LogString, 0, sizeof(LogString));
    v8 = Unit::getNow(this) - this->m_sysUser.last_login_time;
    LODWORD(Cid) = StaticObj::getMapId(this);
    Player::getIP((Player *const)&v62);
    v9 = (const char *)std::string::c_str(&v62);
    v10 = (*((__int64 (__fastcall **)(Player *const, Player *const))this->_vptr_Entity + 9))(this, this);
    snprintf(LogString, 0xFFFu, "level=%d&ip=%s&map_id=%d&onlinetime=%d", v10, v9, Cid, v8);
    std::string::~string(&v62);
    std::string::operator=(&Stu.LogString, LogString);
    LOBYTE(v9) = this->m_connid;
    v11 = Answer::Singleton<DBService>::instance();
    DBService::log360(v11, (int8_t)v9, &Stu);
    logout_log::logout_log(&stu);
    stu.log_Sid = Player::getSid(this);
    stu.log_time = Unit::getNow(this);
    Player::GetPassport((Player *const)v63);
    std::string::operator=(&stu.passport, v63);
    std::string::~string(v63);
    stu.cid = Player::getCid(this);
    Player::getName((const Player *const)v64);
    std::string::operator=(&stu.name, v64);
    std::string::~string(v64);
    stu.create_time = Player::getCreateTime(this);
    stu.logout_time = Unit::getNow(this);
    LODWORD(v9) = Unit::getNow(this);
    stu.online_time = (_DWORD)v9 - Player::getLastLoginTime(this);
    Player::getIP((Player *const)v65);
    std::string::operator=(&stu.ip, v65);
    std::string::~string(v65);
    stu.job = Player::getJob(this);
    stu.level = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
    stu.battle = (*((int (__fastcall **)(Player *const))this->_vptr_Entity + 10))(this);
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this);
    stu.huoyuedu = CHuoYueDu::CalculateHuoYueDu(PlayerHuoYueDu);
    stu.map_id = StaticObj::getMapId(this);
    Task = Player::GetTask(this);
    stu.task_id = ChrTask::GetTrunkTaskId(Task);
    stu.recharge_sum = this->m_sysUser.gold_pay_total;
    stu.gold = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD);
    stu.cash = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_CASH);
    stu.money = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY);
    stu.bind_money = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_BIND_MONEY);
    LOBYTE(v9) = this->m_connid;
    v14 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v14, (int8_t)v9, PLATFORM_LOG_DATA_TYPE::PLDT_LOGOUT, &stu);
    Player::GetPlatform((const Player *const)&__lhs);
    LOBYTE(v9) = std::operator==<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( (_BYTE)v9 )
    {
      *(_DWORD *)&v75.m_info.m_bYellowVip = Unit::getNow(this);
      Answer::StringUtility::toString((int32_t)val);
      Player::getSid(this);
      Answer::StringUtility::toString((int32_t)v71);
      Player::getUid(this);
      Answer::StringUtility::toString((int64_t)v72);
      std::operator+<char>(&__rhs, (const std::string *const)v72);
      std::operator+<char>(&v68, &__rhs);
      std::operator+<char>(&v67, (const char *)&v68);
      Answer::MD5::MD5(&v73);
      Answer::MD5::md5sum((Answer::MD5 *const)&key, (const std::string *const)&v73);
      Answer::MD5::~MD5(&v73);
      std::string::~string(&v67);
      std::string::~string(&v68);
      std::string::~string(&__rhs);
      std::string::~string(v72);
      std::string::~string(v71);
      std::string::~string(val);
      v15 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
      std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
        v56,
        (unsigned int)v15);
      v16 = Unit::getNow(this) - this->m_chr.last_login_time;
      Player::getIP((Player *const)v74);
      CharTencent = Player::GetCharTencent(this);
      CExtCharTencent::GetPf(&v75);
      v18 = (*((__int64 (__fastcall **)(Player *const, CExtCharTencent *))this->_vptr_Entity + 9))(this, CharTencent);
      Uid = Player::getUid(this);
      Sid = Player::getSid(this);
      v21 = std::operator<<<std::char_traits<char>>(&v57, "type=logout");
      v22 = std::operator<<<std::char_traits<char>>(v21, "&");
      v23 = std::operator<<<std::char_traits<char>>(v22, "passport=");
      v24 = std::operator<<<std::char_traits<char>>(v23, this->m_sysUser.passport);
      v25 = std::operator<<<std::char_traits<char>>(v24, "&");
      v26 = std::operator<<<std::char_traits<char>>(v25, "sid=");
      v27 = std::ostream::operator<<(v26, Sid);
      v28 = std::operator<<<std::char_traits<char>>(v27, "&");
      v29 = std::operator<<<std::char_traits<char>>(v28, "uid=");
      v30 = std::ostream::operator<<(v29, Uid);
      v31 = std::operator<<<std::char_traits<char>>(v30, "&");
      v32 = std::operator<<<std::char_traits<char>>(v31, "level=");
      v33 = std::ostream::operator<<(v32, v18);
      v34 = std::operator<<<std::char_traits<char>>(v33, "&");
      v35 = std::operator<<<std::char_traits<char>>(v34, "pf=");
      v36 = std::operator<<<char>(v35, &v75);
      v37 = std::operator<<<std::char_traits<char>>(v36, "&");
      v38 = std::operator<<<std::char_traits<char>>(v37, "ip=");
      v39 = std::operator<<<char>(v38, v74);
      v40 = std::operator<<<std::char_traits<char>>(v39, "&");
      v41 = std::operator<<<std::char_traits<char>>(v40, "online_time=");
      v42 = std::ostream::operator<<(v41, v16);
      v43 = std::operator<<<std::char_traits<char>>(v42, "&");
      v44 = std::operator<<<std::char_traits<char>>(v43, "sign=");
      v45 = std::operator<<<char>(v44, &key);
      v46 = std::operator<<<std::char_traits<char>>(v45, "&");
      v47 = std::operator<<<std::char_traits<char>>(v46, "time=");
      v48 = std::ostream::operator<<(v47, *(unsigned int *)&v75.m_info.m_bYellowVip);
      std::operator<<<std::char_traits<char>>(v48, "&");
      std::string::~string(&v75);
      std::string::~string(v74);
      std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v75.m_info, v56);
      v49 = Answer::Singleton<CHttpRequest>::instance();
      CHttpRequest::AddGetReqString(v49, &v75.m_info.m_pf);
      std::string::~string(&v75.m_info);
      std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v56);
      std::string::~string(&key);
    }
    logout_log::~logout_log(&stu);
    Log360::~Log360(&Stu);
  }
  if ( !CExtOperateLimit::CheckIsLimitedForever(&this->m_extOperateLimit, 37203) )
    CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 37203, 1);
  if ( this->m_pMap )
  {
    *(_DWORD *)&v75.m_info.m_bBlueVip = Map::GetRunnerId(this->m_pMap);
    if ( StaticObj::InDungeon(this) )
    {
      if ( nReason == 3 )
        Player::leaveDungeon(this);
      else
        Player::keepDungeon(this);
    }
    else if ( StaticObj::InActivity(this) )
    {
      Player::leaveActivity(this);
    }
    else if ( StaticObj::IsTerritory(this) || !Map::CanStayInMap(this->m_pMap) )
    {
      Player::OnBackCity(this, 1, 0);
    }
    CExtCharBag::OnLogout(&this->m_extCharBag);
    CExtCharTeamDungeon::LeaveTeamDungeon(&this->m_extCharTeamDungeon);
    CExtCharAuction::OnLogOut(&this->m_extCharAuction);
    this->m_chr.last_logout_time = Unit::getNow(this);
    Player::sendUpdateSocialPlayerInfo(this, PlayerInfoIndex::PII_LAST_LOGOUT_TIME, this->m_chr.last_logout_time);
    this->m_sysUser.last_logout_time = Unit::getNow(this);
    total_online_time = this->m_sysUser.total_online_time;
    this->m_sysUser.total_online_time = total_online_time + Unit::getNow(this) - this->m_sysUser.last_login_time;
    (*((void (__fastcall **)(Player *const, _QWORD, _QWORD, _QWORD))this->_vptr_Entity + 35))(
      this,
      (unsigned int)nReason,
      (unsigned int)nParam,
      0);
    Player::broadcastLeave(this);
    (*((void (__fastcall **)(Map *, Player *const, __int64))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 1);
    v51 = Answer::Singleton<MapManager>::instance();
    MapManager::PostMsg(v51, *(int32_t *)&v75.m_info.m_bBlueVip, GameMsgCode::GMC_PLAYER_LOGOUT, this, 0, 0, 0, 0);
  }
  else
  {
    v52 = Player::getCid(this);
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "Player %d logout with Map = NULL\n", v52);
  }
}


#####################################
int32_t __cdecl Player::onSyncTime(Player *const this, Answer::NetPacket *inPacket)
{
  Player::SyncTime(this);
  return 0;
}


#####################################
void __cdecl Player::SyncTime(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t Now; // edx
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2717u);
  if ( packet )
  {
    Now = Unit::getNow(this);
    Answer::NetPacket::writeInt32(packet, Now);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v6 = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v6, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::SetTeJieCRI(Player *const this)
{
  this->m_TeJieCRI = Unit::getTick(this);
}


#####################################
void __cdecl Player::LogProc(Player *const this, int32_t procId)
{
  int8_t ConnId; // bl
  DBService *v3; // rax
  int32_t procIda; // [rsp+14h] [rbp-7Ch] BYREF
  Player *thisa; // [rsp+18h] [rbp-78h]
  PacketProcLog stu; // [rsp+20h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<int> it; // [rsp+40h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<int> __x; // [rsp+50h] [rbp-40h] BYREF
  _BYTE v9[16]; // [rsp+60h] [rbp-30h] BYREF
  std::pair<std::_Rb_tree_const_iterator<int>,bool> v10; // [rsp+70h] [rbp-20h]

  thisa = this;
  procIda = procId;
  it._M_node = std::set<int>::find(&this->m_PacketProcSet, &procIda)._M_node;
  __x._M_node = std::set<int>::end(&thisa->m_PacketProcSet)._M_node;
  if ( std::_Rb_tree_const_iterator<int>::operator==(&it, &__x) )
  {
    memset(&stu, 0, sizeof(stu));
    std::string::string(&stu.nName);
    stu.nCid = Player::getCid(thisa);
    Player::getName((const Player *const)v9);
    std::string::operator=(&stu.nName, v9);
    std::string::~string(v9);
    stu.nProcId = procIda;
    stu.nTime = Unit::getNow(thisa);
    ConnId = Player::getConnId(thisa);
    v3 = Answer::Singleton<DBService>::instance();
    DBService::LogProc(v3, ConnId, &stu);
    v10 = std::set<int>::insert(&thisa->m_PacketProcSet, &procIda);
    PacketProcLog::~PacketProcLog(&stu);
  }
}


#####################################
void __cdecl Player::LogNpc(Player *const this, int32_t NpcId, int32_t Opway, int32_t OtherNpcId)
{
  CfgData *v4; // rax
  CfgData *v5; // rax
  int32_t v6; // r13d
  int32_t v7; // r12d
  int32_t v8; // eax
  int32_t v9; // r13d
  int32_t v10; // r12d
  int32_t v11; // eax
  int8_t v13; // bl
  DBService *v14; // rax
  int32_t PosY; // r13d
  int32_t PosX; // r12d
  int32_t MapId; // eax
  int8_t ConnId; // bl
  DBService *v19; // rax
  NpcFuncLog stu; // [rsp+20h] [rbp-E0h] BYREF
  _BYTE v23[16]; // [rsp+50h] [rbp-B0h] BYREF
  NpcFuncLog p_LogStu; // [rsp+60h] [rbp-A0h] BYREF
  _BYTE v25[16]; // [rsp+90h] [rbp-70h] BYREF
  NpcFuncLog v26; // [rsp+A0h] [rbp-60h] BYREF
  CfgNpc *cfgNpc; // [rsp+D0h] [rbp-30h]
  CfgNpc *cfgOtherNpc; // [rsp+D8h] [rbp-28h]

  v4 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v4, NpcId);
  if ( cfgNpc )
  {
    if ( OtherNpcId <= 0 )
    {
      PosY = StaticObj::GetPosY(this);
      PosX = StaticObj::GetPosX(this);
      MapId = StaticObj::getMapId(this);
      if ( !CfgNpc::NearNpc(cfgNpc, MapId, PosX, PosY, 10) )
      {
        memset(&stu.sName, 0, 28);
        std::string::string(&stu.sName);
        stu.nCid = Player::getCid(this);
        Player::getName((const Player *const)v25);
        std::string::operator=(&stu.sName, v25);
        std::string::~string(v25);
        stu.nFuncId = Opway;
        stu.nMapId = StaticObj::getMapId(this);
        stu.nX = StaticObj::GetPosX(this);
        stu.nY = StaticObj::GetPosY(this);
        stu.nTime = Unit::getNow(this);
        NpcFuncLog::NpcFuncLog(&v26, &stu);
        ConnId = Player::getConnId(this);
        v19 = Answer::Singleton<DBService>::instance();
        DBService::LogNpcFunc(v19, ConnId, &v26);
        NpcFuncLog::~NpcFuncLog(&v26);
        NpcFuncLog::~NpcFuncLog(&stu);
      }
    }
    else
    {
      v5 = Answer::Singleton<CfgData>::instance();
      cfgOtherNpc = CfgData::getNpc(v5, OtherNpcId);
      if ( cfgOtherNpc )
      {
        v6 = StaticObj::GetPosY(this);
        v7 = StaticObj::GetPosX(this);
        v8 = StaticObj::getMapId(this);
        if ( !CfgNpc::NearNpc(cfgNpc, v8, v7, v6, 10) )
        {
          v9 = StaticObj::GetPosY(this);
          v10 = StaticObj::GetPosX(this);
          v11 = StaticObj::getMapId(this);
          if ( !CfgNpc::NearNpc(cfgOtherNpc, v11, v10, v9, 10) )
          {
            memset(&stu.sName, 0, 28);
            std::string::string(&stu.sName);
            stu.nCid = Player::getCid(this);
            Player::getName((const Player *const)v23);
            std::string::operator=(&stu.sName, v23);
            std::string::~string(v23);
            stu.nFuncId = Opway;
            stu.nMapId = StaticObj::getMapId(this);
            stu.nX = StaticObj::GetPosX(this);
            stu.nY = StaticObj::GetPosY(this);
            stu.nTime = Unit::getNow(this);
            NpcFuncLog::NpcFuncLog(&p_LogStu, &stu);
            v13 = Player::getConnId(this);
            v14 = Answer::Singleton<DBService>::instance();
            DBService::LogNpcFunc(v14, v13, &p_LogStu);
            NpcFuncLog::~NpcFuncLog(&p_LogStu);
            NpcFuncLog::~NpcFuncLog(&stu);
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl Player::onMove(Player *const this, Answer::NetPacket *inPacket)
{
  int64_t Tick; // rbx
  CExtCharSkill *CharSkill; // rax
  int32_t y; // r12d
  int32_t x; // ebx
  int32_t v8; // ebx
  int32_t v9; // eax
  Direction Direction; // eax
  Direction v11; // eax
  Position pos; // [rsp+20h] [rbp-60h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-50h] BYREF
  int32_t ProcId; // [rsp+40h] [rbp-40h]
  int16_t currentX; // [rsp+44h] [rbp-3Ch]
  int16_t currentY; // [rsp+46h] [rbp-3Ah]
  int16_t targetX; // [rsp+48h] [rbp-38h]
  int16_t targetY; // [rsp+4Ah] [rbp-36h]
  int16_t finalX; // [rsp+4Ch] [rbp-34h]
  int16_t finalY; // [rsp+4Eh] [rbp-32h]
  Tile *pCurrentTile; // [rsp+50h] [rbp-30h]
  Tile *pTargetTile; // [rsp+58h] [rbp-28h]
  Tile *pFinalTile; // [rsp+60h] [rbp-20h]
  int32_t ndistan; // [rsp+6Ch] [rbp-14h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  if ( Player::IsInStall(this) )
    return 10002;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 10002;
  }
  if ( Map::GetMapParam(this->m_pMap) == 21 )
    return 10002;
  Tick = Unit::getTick(this);
  CharSkill = Player::GetCharSkill(this);
  if ( !CExtCharSkill::CanUseSkillAndMove(CharSkill, Tick, 0) )
  {
    Unit::setStand(this);
    return 10002;
  }
  else
  {
    Player::BreakGather(this, 1);
    ProcId = Answer::NetPacket::getProc(inPacket);
    Player::LogProc(this, ProcId);
    currentX = Answer::NetPacket::readInt16(inPacket);
    currentY = Answer::NetPacket::readInt16(inPacket);
    targetX = Answer::NetPacket::readInt16(inPacket);
    targetY = Answer::NetPacket::readInt16(inPacket);
    finalX = Answer::NetPacket::readInt16(inPacket);
    finalY = Answer::NetPacket::readInt16(inPacket);
    Answer::NetPacket::readInt8(inPacket);
    pCurrentTile = Map::getTile(this->m_pMap, currentX, currentY);
    pTargetTile = Map::getTile(this->m_pMap, targetX, targetY);
    pFinalTile = Map::getTile(this->m_pMap, finalX, finalY);
    if ( Player::GetStartProtect(this) > 0 && (currentX != targetX || currentY != targetY) )
      Player::SetStartProtect(this, 0);
    if ( pCurrentTile && pTargetTile && pFinalTile )
    {
      Position::Position(&pos, currentX, currentY);
      CurrentTile = StaticObj::getCurrentTile(this);
      ndistan = Position::tileDistance(&CurrentTile, &pos);
      if ( ndistan <= 3 )
      {
        Unit::setTargetTile(this, targetX, targetY);
        Direction = Unit::getDirection(this);
        CExtCharPet::SetTargetTile(&this->m_extCharPet, targetX, targetY, Direction);
        v11 = Unit::getDirection(this);
        CharLittlerHelper::SetTargetTile(&this->m_CharLittlerhelper, targetX, targetY, v11);
        Unit::broadcastMove(this);
        return 0;
      }
      else
      {
        y = StaticObj::getCurrentTile(this).y;
        x = StaticObj::getCurrentTile(this).x;
        Unit::instantMove(this, x, y, InstanceMoveReason::IMR_PULL_BACK, 0);
        v8 = StaticObj::getCurrentTile(this).y;
        v9 = StaticObj::getCurrentTile(this).x;
        printf(
          "PULL_BACK  curx=%d,cury=%d,tarx=%d,tary=%d,serx=%d,sery=%d\n",
          currentX,
          currentY,
          targetX,
          targetY,
          v9,
          v8);
        return 10002;
      }
    }
    else
    {
      return 10002;
    }
  }
}


#####################################
int32_t __cdecl Player::onTrailerMove(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t y; // r12d
  int32_t x; // eax
  int32_t v5; // r13d
  int32_t v6; // r12d
  int32_t v7; // ebx
  int32_t v8; // eax
  Position Pixel; // [rsp+30h] [rbp-A0h] BYREF
  Position pos; // [rsp+40h] [rbp-90h] BYREF
  Position CurrentPixel; // [rsp+50h] [rbp-80h] BYREF
  Position v12; // [rsp+60h] [rbp-70h] BYREF
  Position CurrentTile; // [rsp+70h] [rbp-60h] BYREF
  Position v14; // [rsp+80h] [rbp-50h] BYREF
  int32_t mapId; // [rsp+8Ch] [rbp-44h]
  int16_t currentX; // [rsp+90h] [rbp-40h]
  int16_t currentY; // [rsp+92h] [rbp-3Eh]
  int16_t targetX; // [rsp+94h] [rbp-3Ch]
  int16_t targetY; // [rsp+96h] [rbp-3Ah]
  double Dist; // [rsp+98h] [rbp-38h]
  double DistTar; // [rsp+A0h] [rbp-30h]
  int32_t ndistan; // [rsp+ACh] [rbp-24h]

  if ( !this->m_pMap || !this->m_trailer || !inPacket )
    return 10002;
  mapId = Answer::NetPacket::readInt32(inPacket);
  currentX = Answer::NetPacket::readInt16(inPacket);
  currentY = Answer::NetPacket::readInt16(inPacket);
  targetX = Answer::NetPacket::readInt16(inPacket);
  targetY = Answer::NetPacket::readInt16(inPacket);
  if ( StaticObj::getMapId(this->m_trailer) != mapId )
    return 10002;
  pos = StaticObj::getCurrentPixel(this);
  CurrentPixel = StaticObj::getCurrentPixel(this->m_trailer);
  Dist = Position::distance(&CurrentPixel, &pos);
  if ( Dist < 700.0 )
  {
    Pixel = Map::tileToPixel(targetX, targetY);
    v14 = StaticObj::getCurrentPixel(this);
    DistTar = Position::distance(&v14, &Pixel);
    if ( DistTar < 700.0 )
    {
      return Trailer::move(this->m_trailer, mapId, currentX, currentY, targetX, targetY, 0, 0, Direction::DOWN);
    }
    else
    {
      printf("2 = %f\n", DistTar);
      return 10002;
    }
  }
  else
  {
    Position::Position(&v12, currentX, currentY);
    CurrentTile = StaticObj::getCurrentTile(this->m_trailer);
    ndistan = Position::tileDistance(&CurrentTile, &v12);
    if ( ndistan > 3 )
    {
      y = StaticObj::getCurrentTile(this->m_trailer).y;
      x = StaticObj::getCurrentTile(this->m_trailer).x;
      Unit::instantMove(this->m_trailer, x, y, InstanceMoveReason::IMR_PULL_BACK, 0);
    }
    v5 = StaticObj::getCurrentTile(this->m_trailer).y;
    v6 = StaticObj::getCurrentTile(this->m_trailer).x;
    v7 = StaticObj::getCurrentTile(this).y;
    v8 = StaticObj::getCurrentTile(this).x;
    printf(
      "PULL_BACK  curx=%d,cury=%d,tarx=%d,tary=%d,serx=%d,sery=%d,trailerx=%d,trailery=%d\n",
      currentX,
      currentY,
      targetX,
      targetY,
      v8,
      v7,
      v6,
      v5);
    printf("1 = %f\n", Dist);
    return 10002;
  }
}


#####################################
int32_t __cdecl Player::onJump(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t y; // r12d
  int32_t x; // ebx
  Direction v6; // eax
  Position pos; // [rsp+10h] [rbp-90h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-80h] BYREF
  Position v9; // [rsp+30h] [rbp-70h] BYREF
  Position v10; // [rsp+40h] [rbp-60h] BYREF
  Position v11; // [rsp+50h] [rbp-50h] BYREF
  Position v12; // [rsp+60h] [rbp-40h] BYREF
  int64_t nCurTick; // [rsp+70h] [rbp-30h]
  int16_t currentX; // [rsp+7Ah] [rbp-26h]
  int16_t currentY; // [rsp+7Ch] [rbp-24h]
  int16_t targetX; // [rsp+7Eh] [rbp-22h]
  int16_t targetY; // [rsp+80h] [rbp-20h]
  int8_t dir; // [rsp+83h] [rbp-1Dh]
  int32_t nDistan; // [rsp+84h] [rbp-1Ch]
  int32_t ndisx; // [rsp+88h] [rbp-18h]
  int32_t ndisy; // [rsp+8Ch] [rbp-14h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 23))(this->m_pMap) != 1 )
    return 10002;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 10002;
  }
  nCurTick = Unit::getTick(this);
  Player::BreakGather(this, 1);
  currentX = Answer::NetPacket::readInt16(inPacket);
  currentY = Answer::NetPacket::readInt16(inPacket);
  targetX = Answer::NetPacket::readInt16(inPacket);
  targetY = Answer::NetPacket::readInt16(inPacket);
  dir = Answer::NetPacket::readInt8(inPacket);
  if ( !Map::isWalkablePosition(this->m_pMap, targetX, targetY) )
    return 10002;
  Position::Position(&pos, targetX, targetY);
  CurrentTile = StaticObj::getCurrentTile(this);
  nDistan = Position::tileDistance(&CurrentTile, &pos);
  if ( nDistan <= 10
    || (Position::Position(&v9, currentX, currentY),
        v10 = StaticObj::getCurrentTile(this),
        ndisx = Position::tileDistance(&v10, &v9),
        Position::Position(&v11, targetX, targetY),
        Position::Position(&v12, currentX, currentY),
        ndisy = Position::tileDistance(&v12, &v11),
        ndisx <= 6)
    && ndisy <= 10 )
  {
    CExtCharSkill::CheckSelfTrigBuff(&this->m_extCharSkill, 8);
    v6 = Map::tileDirection(currentX, currentY, targetX, targetY);
    CExtCharPet::SetTargetTile(&this->m_extCharPet, targetX, targetY, v6);
    Unit::instantMove(this, targetX, targetY, InstanceMoveReason::IMR_JUMP, dir);
    this->m_nLastJumpTime = nCurTick;
    Unit::setNeedSyncSelf(this);
    return 0;
  }
  else
  {
    y = StaticObj::getCurrentTile(this).y;
    x = StaticObj::getCurrentTile(this).x;
    Unit::instantMove(this, x, y, InstanceMoveReason::IMR_PULL_BACK, 0);
    return 10002;
  }
}


#####################################
int32_t __cdecl Player::onHit(Player *const this, Answer::NetPacket *inPacket)
{
  char v4; // al
  int32_t y; // r12d
  int32_t x; // ebx
  Position pos; // [rsp+10h] [rbp-70h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-60h] BYREF
  Position v9; // [rsp+30h] [rbp-50h] BYREF
  Position v10; // [rsp+40h] [rbp-40h] BYREF
  Position v11; // [rsp+50h] [rbp-30h] BYREF
  Position v12; // [rsp+60h] [rbp-20h] BYREF
  int16_t currentX; // [rsp+68h] [rbp-18h]
  int16_t currentY; // [rsp+6Ah] [rbp-16h]
  int16_t targetX; // [rsp+6Ch] [rbp-14h]
  int16_t targetY; // [rsp+6Eh] [rbp-12h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_CHENMO)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 10002;
  }
  Player::BreakGather(this, 1);
  currentX = Answer::NetPacket::readInt16(inPacket);
  currentY = Answer::NetPacket::readInt16(inPacket);
  targetX = Answer::NetPacket::readInt16(inPacket);
  targetY = Answer::NetPacket::readInt16(inPacket);
  if ( !Map::isWalkablePosition(this->m_pMap, targetX, targetY) )
    return 10002;
  Position::Position(&pos, targetX, targetY);
  CurrentTile = StaticObj::getCurrentTile(this);
  if ( Position::tileDistance(&CurrentTile, &pos) > 16
    && ((Position::Position(&v9, currentX, currentY),
         v10 = StaticObj::getCurrentTile(this),
         Position::tileDistance(&v10, &v9) <= 6)
     && (Position::Position(&v11, targetX, targetY),
         Position::Position(&v12, currentX, currentY),
         Position::tileDistance(&v12, &v11) <= 10)
      ? (v4 = 0)
      : (v4 = 1),
        v4) )
  {
    y = StaticObj::getCurrentTile(this).y;
    x = StaticObj::getCurrentTile(this).x;
    Unit::instantMove(this, x, y, InstanceMoveReason::IMR_PULL_BACK, 0);
    return 10002;
  }
  else
  {
    Unit::instantMove(this, targetX, targetY, InstanceMoveReason::IMR_HIT, 0);
    return 0;
  }
}


#####################################
int32_t __cdecl Player::onUnitThrowed(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  int64_t id; // [rsp+18h] [rbp-28h]
  int32_t type; // [rsp+24h] [rbp-1Ch]
  Unit *pUnit; // [rsp+28h] [rbp-18h]

  if ( !this->m_pMap || !inPacket )
    return 10002;
  id = Answer::NetPacket::readInt64(inPacket);
  type = Answer::NetPacket::readInt32(inPacket);
  RunnerId = StaticObj::GetRunnerId(this);
  v4 = Answer::Singleton<GameService>::instance();
  pUnit = GameService::getUnit(v4, id, type, RunnerId);
  if ( !pUnit )
    return 10002;
  Unit::onThrowed(pUnit);
  return 0;
}


#####################################
int32_t __cdecl Player::onKickOutMove(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t RunnerId; // r12d
  GameService *v5; // rax
  Direction direction; // edi
  int64_t id; // [rsp+28h] [rbp-38h]
  int32_t type; // [rsp+34h] [rbp-2Ch]
  Unit *pUnit; // [rsp+38h] [rbp-28h]
  int16_t currentX; // [rsp+42h] [rbp-1Eh]
  int16_t currentY; // [rsp+44h] [rbp-1Ch]
  int16_t targetX; // [rsp+46h] [rbp-1Ah]
  int16_t targetY; // [rsp+48h] [rbp-18h]
  int16_t finalX; // [rsp+4Ah] [rbp-16h]
  int16_t finalY; // [rsp+4Ch] [rbp-14h]

  if ( !this->m_pMap || !inPacket )
    return 10002;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 10002;
  }
  id = Answer::NetPacket::readInt64(inPacket);
  type = Answer::NetPacket::readInt32(inPacket);
  RunnerId = StaticObj::GetRunnerId(this);
  v5 = Answer::Singleton<GameService>::instance();
  pUnit = GameService::getUnit(v5, id, type, RunnerId);
  if ( !pUnit )
    return 10002;
  currentX = Answer::NetPacket::readInt16(inPacket);
  currentY = Answer::NetPacket::readInt16(inPacket);
  targetX = Answer::NetPacket::readInt16(inPacket);
  targetY = Answer::NetPacket::readInt16(inPacket);
  finalX = Answer::NetPacket::readInt16(inPacket);
  finalY = Answer::NetPacket::readInt16(inPacket);
  direction = Answer::NetPacket::readInt8(inPacket);
  Unit::onKickOutMove(pUnit, currentX, currentY, targetX, targetY, finalX, finalY, direction);
  return 0;
}


#####################################
int32_t __cdecl Player::checkPreventWallow(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  const char *v3; // rax
  const char *v4; // rax
  std::string identitycard; // [rsp+10h] [rbp-40h] BYREF
  std::string name; // [rsp+20h] [rbp-30h] BYREF
  std::string p_card; // [rsp+30h] [rbp-20h] BYREF
  bool isUseFull; // [rsp+3Fh] [rbp-11h]

  if ( !inPacket )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&name, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&identitycard, (bool)inPacket);
  std::string::string(&p_card, &identitycard);
  isUseFull = Player::isPreventWallow(this, &p_card);
  std::string::~string(&p_card);
  if ( !isUseFull )
  {
    this->m_sysUserPreventWallow.isGrowUp = 1;
    v3 = (const char *)std::string::c_str(&name);
    snprintf(this->m_sysUserPreventWallow.name, 0x1Eu, v3);
    v4 = (const char *)std::string::c_str(&identitycard);
    snprintf(this->m_sysUserPreventWallow.identitycard, 0x12u, v4);
  }
  Player::sendPreventWallow(this);
  v2 = 0;
  std::string::~string(&identitycard);
  std::string::~string(&name);
  return v2;
}


#####################################
bool __cdecl Player::CheckString(Player *const this, std::string *p_card)
{
  const char *v2; // rax
  char szStr[16]; // [rsp+10h] [rbp-40h] BYREF
  char szCardBuf[28]; // [rsp+20h] [rbp-30h] BYREF
  int nFlag; // [rsp+3Ch] [rbp-14h]
  int nLen1; // [rsp+40h] [rbp-10h]
  int nLen2; // [rsp+44h] [rbp-Ch]
  int i; // [rsp+48h] [rbp-8h]
  int j; // [rsp+4Ch] [rbp-4h]

  memset(szCardBuf, 0, 19);
  v2 = (const char *)std::string::c_str(p_card);
  strcpy(szCardBuf, v2);
  strcpy(szStr, "1234567890");
  nFlag = 0;
  nLen1 = strlen(szCardBuf);
  nLen2 = strlen(szStr);
  for ( i = 0; i < nLen1; ++i )
  {
    nFlag = 0;
    for ( j = 0; j < nLen2; ++j )
    {
      if ( szCardBuf[i] == szStr[j] )
      {
        nFlag = 1;
        break;
      }
    }
    if ( nFlag != 1 )
    {
      if ( i == 17 && (szCardBuf[17] == 120 || szCardBuf[i] == 88) )
        nFlag = 1;
      else
        nFlag = 2;
      return nFlag == 1;
    }
  }
  return nFlag == 1;
}


#####################################
bool __cdecl Player::isPreventWallow(Player *const this, std::string *p_card)
{
  bool v3; // bl
  int no[20]; // [rsp+10h] [rbp-B0h]
  char id[16]; // [rsp+60h] [rbp-60h] BYREF
  std::string v6; // [rsp+70h] [rbp-50h] BYREF
  std::string p_cardId; // [rsp+80h] [rbp-40h] BYREF
  bool bResult; // [rsp+8Fh] [rbp-31h]
  int nLen; // [rsp+90h] [rbp-30h]
  bool bFlag; // [rsp+97h] [rbp-29h]
  const char *p; // [rsp+98h] [rbp-28h]
  int i; // [rsp+A4h] [rbp-1Ch]
  int wi; // [rsp+A8h] [rbp-18h]
  int sum; // [rsp+ACh] [rbp-14h]

  bResult = 0;
  nLen = std::string::length(p_card);
  if ( nLen != 18 )
    return 1;
  std::string::string(&v6, p_card);
  bFlag = Player::CheckString(this, &v6);
  std::string::~string(&v6);
  if ( !bFlag )
    return 1;
  std::string::string(&p_cardId, p_card);
  v3 = Player::BirthdayIsRight(this, &p_cardId) == 0;
  std::string::~string(&p_cardId);
  if ( v3 )
    return 1;
  no[0] = 7;
  no[1] = 9;
  no[2] = 10;
  no[3] = 5;
  no[4] = 8;
  no[5] = 4;
  no[6] = 2;
  no[7] = 1;
  no[8] = 6;
  no[9] = 3;
  no[10] = 7;
  no[11] = 9;
  no[12] = 10;
  no[13] = 5;
  no[14] = 8;
  no[15] = 4;
  no[16] = 2;
  qmemcpy(id, "10X98765432", 11);
  p = (const char *)std::string::c_str(p_card);
  i = 0;
  wi = 0;
  sum = 0;
  while ( nLen - 1 > i )
  {
    wi = (p[i] - 48) * no[i];
    sum += wi;
    ++i;
  }
  if ( (p[i] <= 47 || p[i] > 57) && p[i] != 88 && p[i] != 120 )
    bResult = 1;
  wi = sum % 11;
  if ( p[17] == 120 || p[17] == 88 )
  {
    if ( id[wi] != 120 && id[wi] != 88 )
      return 1;
  }
  else if ( id[wi] != p[17] )
  {
    return 1;
  }
  return bResult;
}


#####################################
int32_t __cdecl Player::onSwitchMap(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MapManager *v3; // rax
  int32_t v6; // r12d
  CActivityManager *v9; // rax
  CfgData *v10; // rax
  CfgData *v11; // rax
  SpecialMapMap *SpecialMap; // rax
  std::pair<const int,SpecialMap> *v13; // rax
  std::pair<const int,SpecialMap> *v14; // rax
  int32_t NextMapId; // r12d
  MapManager *v17; // rax
  int v18; // r12d
  MapManager *v20; // rax
  SpecialMapMap SpecialMapTmp; // [rsp+10h] [rbp-D0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SpecialMap> > it; // [rsp+40h] [rbp-A0h] BYREF
  Position Pixel; // [rsp+50h] [rbp-90h] BYREF
  Position pos; // [rsp+60h] [rbp-80h] BYREF
  Position CurrentPixel; // [rsp+70h] [rbp-70h] BYREF
  Position v27; // [rsp+80h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SpecialMap> > __x; // [rsp+90h] [rbp-50h] BYREF
  int32_t ProcId; // [rsp+9Ch] [rbp-44h]
  int32_t FromWhere; // [rsp+A0h] [rbp-40h]
  int32_t mapid; // [rsp+A4h] [rbp-3Ch]
  int32_t x; // [rsp+A8h] [rbp-38h]
  int32_t y; // [rsp+ACh] [rbp-34h]
  Map *pTargetMap; // [rsp+B0h] [rbp-30h]
  bool NeedSwitchMap; // [rsp+BFh] [rbp-21h]
  int32_t Err; // [rsp+C0h] [rbp-20h]
  int32_t MinSize; // [rsp+C4h] [rbp-1Ch]
  int32_t MapId; // [rsp+C8h] [rbp-18h]
  int32_t nSize; // [rsp+CCh] [rbp-14h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  if ( Player::IsInStall(this) )
    return 10002;
  ProcId = Answer::NetPacket::getProc(inPacket);
  Player::LogProc(this, ProcId);
  FromWhere = Answer::NetPacket::readInt32(inPacket);
  mapid = Answer::NetPacket::readInt32(inPacket);
  x = Answer::NetPacket::readInt32(inPacket);
  y = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<MapManager>::instance();
  pTargetMap = MapManager::GetMap(v3, mapid);
  if ( !pTargetMap || this->m_pMap == pTargetMap )
    return 10002;
  if ( Map::IsSpecialBossMap(pTargetMap) )
    return 10002;
  if ( !Map::isWalkablePosition(pTargetMap, x, y) )
    return 10002;
  if ( Map::IsXinMoMap(this->m_pMap) )
    return 10002;
  if ( Map::IsKuangDong(pTargetMap)
    && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 19))(this->m_pMap) != 1 )
  {
    Player::LogNpc(this, 5006, 3, 0);
    Player::TiShiInfo(this, 6, 0);
    return 10002;
  }
  else if ( Map::IsXinMoMap(pTargetMap) && !Map::IsXinMoCun(this->m_pMap) )
  {
    return 10002;
  }
  else
  {
    NeedSwitchMap = 0;
    if ( !FromWhere )
    {
      if ( this->m_trailer )
      {
        v6 = StaticObj::getMapId(this->m_trailer);
        if ( v6 == StaticObj::getMapId(this) )
        {
          pos = StaticObj::getCurrentPixel(this);
          CurrentPixel = StaticObj::getCurrentPixel(this->m_trailer);
          if ( Position::distance(&CurrentPixel, &pos) <= 700.0 )
          {
            Pixel = Map::tileToPixel(11, 202);
            v27 = StaticObj::getCurrentPixel(this);
            if ( Position::distance(&v27, &Pixel) <= 200.0 && StaticObj::getMapId(this) == 50001 )
              NeedSwitchMap = 1;
          }
        }
      }
    }
    if ( Map::GetMapId(pTargetMap) == 50133
      && (v9 = Answer::Singleton<CActivityManager>::instance(), CActivityManager::IsActivityRunning(v9, 7)) )
    {
      Player::EnterActivity(this, 7, 29);
      return 10002;
    }
    else
    {
      v10 = Answer::Singleton<CfgData>::instance();
      if ( !CfgData::IsSpecialMap(v10, mapid) )
        goto LABEL_66;
      MinSize = 99999;
      MapId = 0;
      v11 = Answer::Singleton<CfgData>::instance();
      SpecialMap = CfgData::GetSpecialMap(v11);
      std::map<int,SpecialMap>::map(&SpecialMapTmp, SpecialMap);
      for ( it._M_node = std::map<int,SpecialMap>::begin(&SpecialMapTmp)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,SpecialMap>::end(&SpecialMapTmp)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator!=(&it, &__x) )
          break;
        nSize = Map::GetMapPlayerSize(pTargetMap);
        if ( nSize < MinSize )
        {
          MinSize = nSize;
          MapId = Map::GetMapId(pTargetMap);
        }
        v13 = std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator->(&it);
        if ( v13->second.MaxPlayer > nSize )
          break;
        v14 = std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator->(&it);
        if ( v14->second.MaxPlayer <= nSize
          && std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator->(&it)->second.NextMapId > 0 )
        {
          NextMapId = std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator->(&it)->second.NextMapId;
          v17 = Answer::Singleton<MapManager>::instance();
          pTargetMap = MapManager::GetMap(v17, NextMapId);
          if ( !pTargetMap )
          {
            v2 = 10002;
            v18 = 0;
            goto LABEL_65;
          }
        }
        if ( std::_Rb_tree_iterator<std::pair<int const,SpecialMap>>::operator->(&it)->second.NextMapId <= 0
          && MapId > 0 )
        {
          v20 = Answer::Singleton<MapManager>::instance();
          pTargetMap = MapManager::GetMap(v20, MapId);
          if ( !pTargetMap )
          {
            v2 = 10002;
            v18 = 0;
            goto LABEL_65;
          }
        }
      }
      v18 = 1;
LABEL_65:
      std::map<int,SpecialMap>::~map(&SpecialMapTmp);
      if ( v18 )
      {
LABEL_66:
        Err = Player::switchMap(this, pTargetMap, x, y, 0);
        if ( !Err && !FromWhere && NeedSwitchMap && this->m_trailer )
        {
          Trailer::LeaveMap(this->m_trailer);
          Trailer::EnterMap(this->m_trailer, pTargetMap, x, y);
        }
        return Err;
      }
    }
  }
  return v2;
}


#####################################
int32_t __cdecl Player::onEnterActivity(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t Proc; // edx
  int32_t actID; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  actID = Answer::NetPacket::readInt32(inPacket);
  Proc = Answer::NetPacket::getProc(inPacket);
  Player::EnterActivity(this, actID, Proc);
  return 0;
}


#####################################
int32_t __cdecl Player::OnGetMapBossInfo(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int32_t BossDistribution; // eax
  int32_t v5; // ebx
  MapManager *v6; // rax
  int8_t m_connid; // bl
  GameService *v8; // rax
  int32_t v9; // eax
  Param2 *v10; // rax
  Param2 *v11; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v14; // bl
  GameService *v15; // rax
  std::_List_iterator<Param2> it_0; // [rsp+10h] [rbp-90h] BYREF
  Param2 stu; // [rsp+20h] [rbp-80h] BYREF
  std::_List_iterator<int> it; // [rsp+30h] [rbp-70h] BYREF
  Param2List m_BossInfo; // [rsp+40h] [rbp-60h] BYREF
  Int32List nMapList; // [rsp+50h] [rbp-50h] BYREF
  std::_List_iterator<int> __x; // [rsp+60h] [rbp-40h] BYREF
  std::_List_iterator<Param2> v23; // [rsp+70h] [rbp-30h] BYREF
  int32_t nId; // [rsp+7Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+80h] [rbp-20h]
  Map *pMap; // [rsp+88h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  BossDistribution = (unsigned int)CfgData::GetBossDistribution(v3);
  BossDistribution::GetMapBossInfo((BossDistribution *const)&nMapList, BossDistribution);
  std::list<Param2>::list(&m_BossInfo);
  for ( it._M_node = std::list<int>::begin(&nMapList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
  {
    __x._M_node = std::list<int>::end(&nMapList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    v5 = *std::_List_iterator<int>::operator*(&it);
    v6 = Answer::Singleton<MapManager>::instance();
    pMap = MapManager::GetMap(v6, v5);
    if ( pMap )
    {
      Param2::Param2(&stu, 0, 0);
      stu.nParam1 = *std::_List_iterator<int>::operator*(&it);
      stu.nParam2 = Map::GetAliveBossCount(pMap, 0);
      std::list<Param2>::push_back(&m_BossInfo, &stu);
    }
  }
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v8, m_connid, Answer::PackType::PACK_DISPATCH, 0x2805u);
  if ( packet )
  {
    v9 = std::list<Param2>::size(&m_BossInfo);
    Answer::NetPacket::writeInt32(packet, v9);
    for ( it_0._M_node = std::list<Param2>::begin(&m_BossInfo)._M_node; ; std::_List_iterator<Param2>::operator++(
                                                                            &it_0,
                                                                            0) )
    {
      v23._M_node = std::list<Param2>::end(&m_BossInfo)._M_node;
      if ( !std::_List_iterator<Param2>::operator!=(&it_0, &v23) )
        break;
      v10 = std::_List_iterator<Param2>::operator->(&it_0);
      Answer::NetPacket::writeInt32(packet, v10->nParam1);
      v11 = std::_List_iterator<Param2>::operator->(&it_0);
      Answer::NetPacket::writeInt32(packet, v11->nParam2);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v14 = this->m_connid;
    v15 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v15, v14, m_cgindex, packet);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::list<Param2>::~list(&m_BossInfo);
  std::list<int>::~list(&nMapList);
  return v2;
}


#####################################
int32_t __cdecl Player::OnGetLevelBossInfo(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int32_t BossDistribution; // eax
  int32_t v5; // ebx
  MapManager *v6; // rax
  int8_t m_connid; // bl
  GameService *v8; // rax
  int32_t v9; // eax
  Param2 *v10; // rax
  Param2 *v11; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v14; // bl
  GameService *v15; // rax
  std::_List_iterator<Param2> it_0; // [rsp+10h] [rbp-90h] BYREF
  Param2 stu; // [rsp+20h] [rbp-80h] BYREF
  std::_List_iterator<int> it; // [rsp+30h] [rbp-70h] BYREF
  Param2List m_BossInfo; // [rsp+40h] [rbp-60h] BYREF
  Int32List nMapList; // [rsp+50h] [rbp-50h] BYREF
  std::_List_iterator<int> __x; // [rsp+60h] [rbp-40h] BYREF
  std::_List_iterator<Param2> v23; // [rsp+70h] [rbp-30h] BYREF
  int32_t nLevel; // [rsp+7Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+80h] [rbp-20h]
  Map *pMap; // [rsp+88h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  nLevel = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  BossDistribution = (unsigned int)CfgData::GetBossDistribution(v3);
  BossDistribution::GetBossLevelInfo((BossDistribution *const)&nMapList, BossDistribution);
  std::list<Param2>::list(&m_BossInfo);
  for ( it._M_node = std::list<int>::begin(&nMapList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
  {
    __x._M_node = std::list<int>::end(&nMapList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    v5 = *std::_List_iterator<int>::operator*(&it);
    v6 = Answer::Singleton<MapManager>::instance();
    pMap = MapManager::GetMap(v6, v5);
    if ( pMap )
    {
      Param2::Param2(&stu, 0, 0);
      stu.nParam1 = *std::_List_iterator<int>::operator*(&it);
      stu.nParam2 = Map::GetAliveBossCount(pMap, nLevel);
      std::list<Param2>::push_back(&m_BossInfo, &stu);
    }
  }
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v8, m_connid, Answer::PackType::PACK_DISPATCH, 0x2804u);
  if ( packet )
  {
    v9 = std::list<Param2>::size(&m_BossInfo);
    Answer::NetPacket::writeInt32(packet, v9);
    for ( it_0._M_node = std::list<Param2>::begin(&m_BossInfo)._M_node; ; std::_List_iterator<Param2>::operator++(
                                                                            &it_0,
                                                                            0) )
    {
      v23._M_node = std::list<Param2>::end(&m_BossInfo)._M_node;
      if ( !std::_List_iterator<Param2>::operator!=(&it_0, &v23) )
        break;
      v10 = std::_List_iterator<Param2>::operator->(&it_0);
      Answer::NetPacket::writeInt32(packet, v10->nParam1);
      v11 = std::_List_iterator<Param2>::operator->(&it_0);
      Answer::NetPacket::writeInt32(packet, v11->nParam2);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v14 = this->m_connid;
    v15 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v15, v14, m_cgindex, packet);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::list<Param2>::~list(&m_BossInfo);
  std::list<int>::~list(&nMapList);
  return v2;
}


#####################################
int32_t __cdecl Player::OnPaiMaiHangHanHua(Player *const this, Answer::NetPacket *inPacket)
{
  CExtCurrency *Currency; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  Currency = Player::GetCurrency(this);
  if ( !CExtCurrency::DecCurrency(
          Currency,
          CURRENCY_TYPE::CURRENCY_MONEY,
          20000,
          CURRENCY_CHANGE_REASON::GCR_HAN_HUA,
          0) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this);
  ConnId = Player::getConnId(this);
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl Player::EnterActivity(Player *const this, int32_t nActId, int32_t nProc)
{
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v6; // rax
  int16_t v8; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  CActivityManager *v11; // rax
  CfgData *v13; // rax
  GameService *v14; // rax
  CfgData *v16; // rax
  int32_t PosY; // r12d
  int32_t PosX; // eax
  int32_t Record; // ebx
  int32_t v20; // ebx
  CfgData *v21; // rax
  int32_t ServerDiffDay; // eax
  int16_t Type; // ax
  int8_t v24; // bl
  GameService *v25; // rax
  int64_t Uid; // rax
  int32_t Sid; // eax
  uint32_t v28; // eax
  int8_t v29; // bl
  GameService *v30; // rax
  int32_t v31; // ebx
  MapManager *v32; // rax
  CActivityMap *v33; // rax
  int16_t v34; // r12
  int8_t v35; // bl
  GameService *v36; // rax
  int64_t MapId; // r14
  int16_t v38; // r12
  int8_t v39; // bl
  GameService *v40; // rax
  int16_t v41; // r12
  int8_t v42; // bl
  GameService *v43; // rax
  int32_t RunnerId; // ebx
  int32_t v45; // ebx
  MapManager *v46; // rax
  int16_t v47; // r12
  int8_t v48; // bl
  GameService *v49; // rax
  int8_t v50; // bl
  GameService *v51; // rax
  uint32_t WOffset; // eax
  int8_t v53; // bl
  GameService *v54; // rax
  int8_t v55; // bl
  DBService *v56; // rax
  GameService *v57; // rax
  GameService *v59; // rax
  CharId_t Cid; // rax
  uint16_t nProca; // [rsp+10h] [rbp-A0h]
  LogActivity logActivity; // [rsp+20h] [rbp-90h] BYREF
  Position pos; // [rsp+40h] [rbp-70h]
  int32_t ret; // [rsp+48h] [rbp-68h]
  int32_t actID; // [rsp+4Ch] [rbp-64h]
  CActivity *pActivity; // [rsp+50h] [rbp-60h]
  CfgActivity *pCfgActInfo; // [rsp+58h] [rbp-58h]
  Map *pTargetMap; // [rsp+60h] [rbp-50h]
  CActivityMap *pAct; // [rsp+68h] [rbp-48h]
  int32_t err; // [rsp+74h] [rbp-3Ch]
  Answer::NetPacket *outPacket; // [rsp+78h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+80h] [rbp-30h]
  CfgNpc *cfgNpc; // [rsp+88h] [rbp-28h]

  nProca = nProc;
  if ( !this->m_pMap )
    return 10002;
  ret = 0;
  if ( Player::IsInStall(this) )
  {
    ret = 10002;
    goto LABEL_60;
  }
  if ( StaticObj::InActivity(this) )
  {
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v6 = Answer::Singleton<GameService>::instance();
    ret = GameService::replyfailure(v6, m_connid, m_cgindex, 0x10u, 10081, 0);
    goto LABEL_60;
  }
  if ( StaticObj::InDungeon(this) || CExtCharTeamDungeon::IsInTeamDungeon(&this->m_extCharTeamDungeon) )
  {
    v8 = this->m_cgindex;
    v9 = this->m_connid;
    v10 = Answer::Singleton<GameService>::instance();
    ret = GameService::replyfailure(v10, v9, v8, 0x10u, 10082, 0);
    goto LABEL_60;
  }
  actID = nActId;
  v11 = Answer::Singleton<CActivityManager>::instance();
  pActivity = CActivityManager::GetActivity(v11, nActId);
  if ( !pActivity || !CActivity::IsRuning(pActivity) )
  {
    ret = 10117;
    goto LABEL_60;
  }
  v13 = Answer::Singleton<CfgData>::instance();
  pCfgActInfo = CfgData::getActivity(v13, actID);
  if ( !pCfgActInfo )
  {
    ret = 10118;
    goto LABEL_60;
  }
  if ( pCfgActInfo->line != 9 || (v14 = Answer::Singleton<GameService>::instance(), GameService::getLine(v14) == 9) )
  {
    v31 = (*((__int64 (__fastcall **)(CActivity *, Player *const))pActivity->_vptr_CActivity + 27))(pActivity, this);
    v32 = Answer::Singleton<MapManager>::instance();
    pTargetMap = MapManager::GetMap(v32, v31);
    if ( this->m_pMap == pTargetMap )
    {
      ret = 10002;
    }
    else
    {
      if ( pTargetMap )
        v33 = (CActivityMap *)__dynamic_cast(
                                pTargetMap,
                                (const struct __class_type_info *)&`typeinfo for'Map,
                                (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                0);
      else
        v33 = 0;
      pAct = v33;
      if ( v33 )
      {
        err = (*((__int64 (__fastcall **)(CActivityMap *, Player *const))pAct->_vptr_Map + 4))(pAct, this);
        if ( err )
        {
          MapId = Map::GetMapId(pAct);
          v38 = this->m_cgindex;
          v39 = this->m_connid;
          v40 = Answer::Singleton<GameService>::instance();
          ret = GameService::replyfailure(v40, v39, v38, nProca, err, MapId);
        }
        else
        {
          pos = CActivityMap::GetBornPos(pAct, this);
          if ( pos == -1 )
          {
            v41 = this->m_cgindex;
            v42 = this->m_connid;
            v43 = Answer::Singleton<GameService>::instance();
            ret = GameService::replyfailure(v43, v42, v41, 0x10u, 10084, 0);
          }
          else
          {
            Player::setOldPosition(this);
            Player::broadcastLeave(this);
            RunnerId = Map::GetRunnerId(pTargetMap);
            if ( RunnerId == Map::GetRunnerId(this->m_pMap) )
            {
              (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(
                this->m_pMap,
                this,
                0);
              (*((void (__fastcall **)(Map *, Player *const, _QWORD, _QWORD))pTargetMap->_vptr_Map + 15))(
                pTargetMap,
                this,
                (unsigned int)pos.x,
                (unsigned int)pos.y);
            }
            else
            {
              (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(
                this->m_pMap,
                this,
                0);
              v45 = Map::GetRunnerId(pTargetMap);
              v46 = Answer::Singleton<MapManager>::instance();
              MapManager::PostMsg(v46, v45, GameMsgCode::GMC_PLAYER_LEAVE_MAP, this, pTargetMap, pos.x, pos.y, 0);
            }
            v47 = this->m_cgindex;
            v48 = this->m_connid;
            v49 = Answer::Singleton<GameService>::instance();
            GameService::replySuccess(v49, v48, v47, nProca, actID);
            v50 = this->m_connid;
            v51 = Answer::Singleton<GameService>::instance();
            outPacket = GameService::popNetpacket(v51, v50, Answer::PackType::PACK_DISPATCH, 0x4EBDu);
            if ( outPacket )
            {
              Answer::NetPacket::writeInt32(outPacket, this->m_cgindex);
              Answer::NetPacket::writeInt32(outPacket, 1);
              WOffset = Answer::NetPacket::getWOffset(outPacket);
              Answer::NetPacket::setSize(outPacket, WOffset);
              v53 = this->m_connid;
              v54 = Answer::Singleton<GameService>::instance();
              GameService::sendPacket(v54, v53, outPacket);
              *(&logActivity.time + 1) = 0;
              logActivity.param = 0;
              logActivity.cid = Player::getCid(this);
              logActivity.actid = actID;
              logActivity.acttype = CActivity::GetType(pActivity);
              logActivity.time = Unit::getNow(this);
              if ( CActivity::GetType(pActivity) == 1 )
              {
                logActivity.param = Player::getFamilyId(this);
              }
              else if ( CActivity::GetType(pActivity) == 14 )
              {
                logActivity.param = Map::GetMapId(pTargetMap);
              }
              v55 = this->m_connid;
              v56 = Answer::Singleton<DBService>::instance();
              DBService::InsertActivityLog(v56, v55, &logActivity);
            }
            else
            {
              ret = 10002;
            }
          }
        }
      }
      else
      {
        v34 = this->m_cgindex;
        v35 = this->m_connid;
        v36 = Answer::Singleton<GameService>::instance();
        ret = GameService::replyfailure(v36, v35, v34, 0x10u, 10083, 0);
      }
    }
    goto LABEL_60;
  }
  if ( pCfgActInfo->typeId != 11 )
    goto LABEL_75;
  v16 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v16, 3018);
  if ( !cfgNpc )
  {
    ret = 10119;
    goto LABEL_60;
  }
  PosY = StaticObj::GetPosY(this);
  PosX = StaticObj::GetPosX(this);
  if ( !Map::NearNpc(this->m_pMap, cfgNpc->id, PosX, PosY, 10) )
  {
    ret = 10120;
  }
  else
  {
LABEL_75:
    if ( pCfgActInfo->typeId == 22 && (Record = Player::getRecord(this, 1924), Record > Unit::getNow(this)) )
    {
      ret = 10122;
    }
    else
    {
      v20 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 10))(this);
      v21 = Answer::Singleton<CfgData>::instance();
      ServerDiffDay = CfgData::getServerDiffDay(v21, SERVER_TYPE::SVT_NORMAL);
      if ( v20 >= GetDayBattle(ServerDiffDay + 1) )
      {
        Type = CActivity::GetType(pActivity);
        CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 1057, Type);
        v24 = this->m_connid;
        v25 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v25, v24, Answer::PackType::PACK_PROC, 0x4E2Fu);
        if ( packet )
        {
          Uid = Player::getUid(this);
          Answer::NetPacket::writeInt64(packet, Uid);
          Sid = Player::getSid(this);
          Answer::NetPacket::writeInt32(packet, Sid);
          v28 = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, v28);
          v29 = this->m_connid;
          v30 = Answer::Singleton<GameService>::instance();
          GameService::sendPacket(v30, v29, packet);
          ret = 0;
        }
        else
        {
          ret = 10002;
        }
      }
      else
      {
        ret = 10121;
      }
    }
  }
LABEL_60:
  if ( ret && (v57 = Answer::Singleton<GameService>::instance(), GameService::getLine(v57) == 9) )
  {
    Player::kickBackFromCross(this, ret);
  }
  else if ( ret )
  {
    v59 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v59) != 9 )
    {
      Cid = Player::getCid(this);
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "enter act %lld,err=%d\n", Cid, ret);
    }
  }
  return ret;
}


#####################################
int32_t __cdecl Player::onLeaveActivity(Player *const this, Answer::NetPacket *inPacket)
{
  if ( StaticObj::InActivity(this) )
    Player::leaveActivity(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onActivityChangeMap(Player *const this, Answer::NetPacket *inPacket)
{
  MapManager *v4; // rax
  Map *Map; // rax
  CActivityMap *v6; // rax
  int32_t nMapId; // [rsp+10h] [rbp-30h]
  unsigned int nPosX; // [rsp+14h] [rbp-2Ch]
  unsigned int nPosY; // [rsp+18h] [rbp-28h]
  unsigned int nParam; // [rsp+1Ch] [rbp-24h]
  CActivityMap *pActMap; // [rsp+20h] [rbp-20h]
  const CActivity *pActivity; // [rsp+28h] [rbp-18h]

  if ( !inPacket || !StaticObj::InActivity(this) )
    return 10002;
  nMapId = Answer::NetPacket::readInt32(inPacket);
  nPosX = Answer::NetPacket::readInt32(inPacket);
  nPosY = Answer::NetPacket::readInt32(inPacket);
  nParam = Answer::NetPacket::readInt32(inPacket);
  v4 = Answer::Singleton<MapManager>::instance();
  Map = MapManager::GetMap(v4, nMapId);
  if ( Map )
    v6 = (CActivityMap *)__dynamic_cast(
                           Map,
                           (const struct __class_type_info *)&`typeinfo for'Map,
                           (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                           0);
  else
    v6 = 0;
  pActMap = v6;
  if ( !v6 )
    return 10002;
  pActivity = CActivityMap::GetActivity(v6);
  if ( !pActivity )
    return 10002;
  if ( !CActivity::IsRuning(pActivity) )
    return 10002;
  if ( (*((unsigned __int8 (__fastcall **)(const CActivity *, Player *const, CActivityMap *, _QWORD, _QWORD, _QWORD))pActivity->_vptr_CActivity
        + 24))(
         pActivity,
         this,
         pActMap,
         nPosX,
         nPosY,
         nParam) != 1 )
    return 10002;
  return 0;
}


#####################################
int32_t __cdecl Player::OnCycleTowerEvent(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t MapId; // ebx
  CfgData *v4; // rax
  const CycleTowerTable *CycleTowerTable; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  CfgData *v8; // rax
  CPoolManager *v9; // rax
  int32_t Now; // eax
  CharId_t Cid; // rax
  Position Pos; // [rsp+10h] [rbp-90h]
  CfgMapMonster MapMonster; // [rsp+20h] [rbp-80h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+40h] [rbp-60h] BYREF
  std::string p_Name; // [rsp+60h] [rbp-40h] BYREF
  const CycleTowerMapCfg *pMapCfg; // [rsp+68h] [rbp-38h]
  CfgMonster *pMonster; // [rsp+70h] [rbp-30h]
  int32_t MonsterId; // [rsp+7Ch] [rbp-24h]
  Monster *monster; // [rsp+80h] [rbp-20h]
  Map *pMap; // [rsp+88h] [rbp-18h]

  if ( !inPacket )
    return 2;
  MapId = StaticObj::getMapId(this);
  v4 = Answer::Singleton<CfgData>::instance();
  CycleTowerTable = CfgData::GetCycleTowerTable(v4);
  pMapCfg = CycleTowerTable::GetFloorCfg(CycleTowerTable, MapId);
  if ( !pMapCfg )
    return 2;
  if ( Player::getRecord(this, 1923) > 0 )
    return 2;
  if ( pMapCfg->FloorType == 1 )
  {
    v6 = pMapCfg->MonsterId;
    v7 = Answer::Singleton<CfgData>::instance();
    pMonster = CfgData::getMonster(v7, v6);
    if ( !pMonster )
      return 2;
    if ( pMonster->boss_sign != 11 )
      return 2;
    v8 = Answer::Singleton<CfgData>::instance();
    MonsterId = CfgData::GetMapMonsterId(v8);
    MapMonster.monsterid = 0;
    *(_DWORD *)&MapMonster.hide = 0;
    MapMonster.Day = 0;
    MapMonster.id = MonsterId;
    Pos = Player::GetSummonBossPos(this);
    MapMonster.mapid = StaticObj::getMapId(this);
    *(Position *)&MapMonster.x = Pos;
    v9 = Answer::Singleton<CPoolManager>::instance();
    monster = CPoolManager::pop<Monster>(v9);
    if ( monster )
    {
      std::vector<AttrAddon>::vector(&vAttrAddon);
      Monster::init(monster, pMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
      std::vector<AttrAddon>::~vector(&vAttrAddon);
      Now = Unit::getNow(this);
      Monster::SetLifeTime(monster, Now + 600);
      Monster::SetNotChangeOwner(monster);
      Player::getName((const Player *const)&p_Name);
      Cid = Player::getCid(this);
      Monster::SetOwner(monster, Cid, &p_Name);
      std::string::~string(&p_Name);
      pMap = StaticObj::getMap(this);
      if ( pMap )
        (*((void (__fastcall **)(Map *, Monster *, _QWORD, _QWORD))pMap->_vptr_Map + 28))(
          pMap,
          monster,
          (unsigned int)MapMonster.x,
          (unsigned int)MapMonster.y);
    }
  }
  Player::UpdateCycleTowerState(this, CYCLE_TOWER_ENVET_TYPE::CTET_SUMMON_BOSS);
  return 0;
}


#####################################
void __cdecl Player::AddBeiGongAttr(Player *const this, int32_t nType, int32_t nValue)
{
  int *v3; // rax
  int32_t nTypea; // [rsp+4h] [rbp-Ch] BYREF
  Player *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  nTypea = nType;
  v3 = std::map<int,int>::operator[](&this->m_BeiGongAttr, &nTypea);
  *v3 += nValue;
}


#####################################
void __cdecl Player::SendBeiGongAttr(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2841u);
  if ( packet )
  {
    v3 = std::map<int,int>::size(&this->m_BeiGongAttr);
    Answer::NetPacket::writeInt32(packet, v3);
    for ( it._M_node = std::map<int,int>::begin(&this->m_BeiGongAttr)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_BeiGongAttr)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v4->first);
      v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v5->second);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v8 = this->m_connid;
    v9 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v9, v8, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::UpdateCycleTowerState(Player *const this, CYCLE_TOWER_ENVET_TYPE nType)
{
  int32_t MapId; // ebx
  CfgData *v3; // rax
  const CycleTowerTable *CycleTowerTable; // rax
  const CycleTowerMapCfg *pMapCfg; // [rsp+18h] [rbp-18h]

  if ( StaticObj::IsCycleTower(this) )
  {
    MapId = StaticObj::getMapId(this);
    v3 = Answer::Singleton<CfgData>::instance();
    CycleTowerTable = CfgData::GetCycleTowerTable(v3);
    pMapCfg = CycleTowerTable::GetFloorCfg(CycleTowerTable, MapId);
    if ( pMapCfg )
    {
      if ( pMapCfg->FloorType == nType )
      {
        Player::updateRecord(this, 1923, 1);
        Player::SendCycleTowerInfo(this);
      }
    }
  }
}


#####################################
int32_t __cdecl Player::OnRollTheDice(Player *const this, Answer::NetPacket *inPacket)
{
  Answer::Random *v3; // rax
  int32_t MapId; // ebx
  CfgData *v5; // rax
  const CycleTowerTable *CycleTowerTable; // rax
  CfgData *v7; // rax
  const CycleTowerTable *v8; // rax
  MapManager *v9; // rax
  CfgData *v10; // rax
  const CycleTowerTable *v11; // rax
  CExtCharBag *v12; // rax
  CfgData *v13; // rax
  const CycleTowerTable *v14; // rax
  CfgData *v15; // rax
  const CycleTowerTable *v16; // rax
  CExtCharBag *Bag; // rax
  CfgData *v18; // rax
  const CycleTowerTable *v19; // rax
  int32_t v20; // edx
  int32_t v21; // ebx
  CNationalDayHd *CNationalDayHd; // rax
  int64_t v23; // r14
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  GameService *v26; // rax
  __int64 v27; // rax
  __int64 v28; // rax
  ItemData CostItem_0; // [rsp+20h] [rbp-80h] BYREF
  ItemData CostItem; // [rsp+30h] [rbp-70h] BYREF
  Position EnterPos; // [rsp+40h] [rbp-60h]
  int8_t Point; // [rsp+55h] [rbp-4Bh]
  int8_t PointTmp; // [rsp+56h] [rbp-4Ah]
  int8_t JumpFloor; // [rsp+57h] [rbp-49h]
  const CycleTowerMapCfg *pMapCfg; // [rsp+58h] [rbp-48h]
  int32_t TarGetFloor; // [rsp+60h] [rbp-40h]
  int32_t TarGetMapId; // [rsp+64h] [rbp-3Ch]
  Map *pTarMap; // [rsp+68h] [rbp-38h]
  int32_t CommonTimes; // [rsp+70h] [rbp-30h]
  int32_t VipTimes; // [rsp+74h] [rbp-2Ch]
  int32_t CostGold; // [rsp+78h] [rbp-28h]
  int32_t CostGold_0; // [rsp+7Ch] [rbp-24h]
  ItemData v43; // 0:kr00_12.12
  ItemData v44; // 0:kr14_12.12

  if ( !inPacket )
    return 2;
  if ( !StaticObj::IsCycleTower(this) )
    return 2;
  if ( Player::getRecord(this, 1921) > 0 )
    return 2;
  Point = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)Point > 6u )
    return 2;
  PointTmp = 0;
  JumpFloor = Point;
  if ( !Point )
  {
    v3 = Answer::Singleton<Answer::Random>::instance();
    PointTmp = Answer::Random::generate(v3, 1, 6);
    JumpFloor = PointTmp;
  }
  MapId = StaticObj::getMapId(this);
  v5 = Answer::Singleton<CfgData>::instance();
  CycleTowerTable = CfgData::GetCycleTowerTable(v5);
  pMapCfg = CycleTowerTable::GetFloorCfg(CycleTowerTable, MapId);
  if ( !pMapCfg )
    return 2;
  if ( pMapCfg->Floor > 99 )
    return 2;
  TarGetFloor = pMapCfg->Floor + JumpFloor;
  if ( TarGetFloor > 100 )
  {
    JumpFloor = 100 - pMapCfg->Floor;
    TarGetFloor = 100;
  }
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetCycleTowerTable(v7);
  TarGetMapId = CycleTowerTable::GetMapId(v8, TarGetFloor);
  if ( TarGetMapId <= 0 )
    return 2;
  v9 = Answer::Singleton<MapManager>::instance();
  pTarMap = MapManager::GetMap(v9, TarGetMapId);
  if ( !pTarMap )
    return 2;
  EnterPos = Map::GetEnterPos(pTarMap);
  if ( EnterPos.y <= 0 || EnterPos.x <= 0 )
    return 2;
  CommonTimes = Player::getRecord(this, 2097);
  VipTimes = Player::getRecord(this, 2099);
  if ( CVip::GetCycleTowerTimes(&this->m_PlayerVip) <= VipTimes )
  {
    if ( Point )
    {
      v18 = Answer::Singleton<CfgData>::instance();
      v19 = CfgData::GetCycleTowerTable(v18);
      CostGold_0 = CycleTowerTable::GetCostGold(v19, CommonTimes + 1);
      if ( CostGold_0 <= 0 )
        return 2;
      if ( !Player::DecCurrency(
              this,
              CURRENCY_TYPE::CURRENCY_GOLD,
              CostGold_0,
              CURRENCY_CHANGE_REASON::GCR_CYCLE_TOWER,
              0) )
        return 2;
    }
    else
    {
      v15 = Answer::Singleton<CfgData>::instance();
      v16 = CfgData::GetCycleTowerTable(v15);
      v44 = CycleTowerTable::GetCostItem(v16, CommonTimes + 1);
      LODWORD(v28) = v44.m_nId;
      BYTE4(v28) = v44.m_nClass;
      *(_QWORD *)&CostItem_0.m_nId = v28;
      CostItem_0.m_nCount = v44.m_nCount;
      if ( !ItemData::IsEmpty(&CostItem_0) )
      {
        Bag = Player::GetBag(this);
        if ( !CExtCharBag::RemoveItem(Bag, &CostItem_0, ITEM_CHANGE_REASON::IDCR_CYCLE_TOWER) )
          return 2;
      }
    }
    Player::updateRecord(this, 2097, CommonTimes + 1);
  }
  else
  {
    if ( Point )
    {
      v13 = Answer::Singleton<CfgData>::instance();
      v14 = CfgData::GetCycleTowerTable(v13);
      CostGold = CycleTowerTable::GetCostGold(v14, CommonTimes + 1);
      if ( CostGold <= 0 )
        return 2;
      if ( !Player::DecCurrency(
              this,
              CURRENCY_TYPE::CURRENCY_GOLD,
              CostGold,
              CURRENCY_CHANGE_REASON::GCR_CYCLE_TOWER,
              0) )
        return 2;
    }
    else
    {
      v10 = Answer::Singleton<CfgData>::instance();
      v11 = CfgData::GetCycleTowerTable(v10);
      v43 = CycleTowerTable::GetCostItem(v11, CommonTimes + 1);
      LODWORD(v27) = v43.m_nId;
      BYTE4(v27) = v43.m_nClass;
      *(_QWORD *)&CostItem.m_nId = v27;
      CostItem.m_nCount = v43.m_nCount;
      if ( !ItemData::IsEmpty(&CostItem) )
      {
        v12 = Player::GetBag(this);
        if ( !CExtCharBag::RemoveItem(v12, &CostItem, ITEM_CHANGE_REASON::IDCR_CYCLE_TOWER) )
          return 2;
      }
    }
    Player::updateRecord(this, 2099, VipTimes + 1);
  }
  Player::BreakGather(this, 1);
  Player::updateRecord(this, 1921, TarGetMapId);
  v20 = Unit::getNow(this) + 3;
  Player::updateRecord(this, 1922, v20);
  Player::SendCycleTowerInfo(this);
  v21 = JumpFloor;
  CNationalDayHd = Player::GetCNationalDayHd(this);
  CNationalDayHd::AddNationalValue(CNationalDayHd, NATIONAL_HD_TYPE::HHT_LUN_HUI_TA, v21, 0);
  v23 = PointTmp;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  LOBYTE(v21) = this->m_connid;
  v26 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v26, v21, m_cgindex, Proc, v23);
}


#####################################
void __cdecl Player::CheckEnterCycleTower(Player *const this)
{
  int32_t Now; // ebx
  MapManager *v2; // rax
  int32_t RunnerId; // ebx
  int32_t v4; // ebx
  MapManager *v5; // rax
  int32_t MapId; // ebx
  int32_t GongGaoId; // ecx
  Position EnterPos; // [rsp+20h] [rbp-40h]
  int TarGetMapId; // [rsp+34h] [rbp-2Ch]
  Map *pTarMap; // [rsp+38h] [rbp-28h]

  if ( !this->m_pMap )
    goto LABEL_5;
  TarGetMapId = Player::getRecord(this, 1921);
  if ( TarGetMapId > 0 )
  {
    Now = Unit::getNow(this);
    if ( Now >= Player::getRecord(this, 1922) )
    {
      v2 = Answer::Singleton<MapManager>::instance();
      pTarMap = MapManager::GetMap(v2, TarGetMapId);
      if ( !pTarMap || (EnterPos = Map::GetEnterPos(pTarMap), EnterPos.y <= 0) || EnterPos.x <= 0 )
      {
LABEL_5:
        Player::updateRecord(this, 1921, 0);
        return;
      }
      Player::setOldPosition(this);
      Player::broadcastLeave(this);
      Player::updateRecord(this, 1923, 0);
      RunnerId = Map::GetRunnerId(this->m_pMap);
      if ( RunnerId == Map::GetRunnerId(pTarMap) )
      {
        (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
        (*((void (__fastcall **)(Map *, Player *const, _QWORD, _QWORD))pTarMap->_vptr_Map + 15))(
          pTarMap,
          this,
          (unsigned int)EnterPos.x,
          (unsigned int)EnterPos.y);
      }
      else
      {
        (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
        v4 = Map::GetRunnerId(pTarMap);
        v5 = Answer::Singleton<MapManager>::instance();
        MapManager::PostMsg(v5, v4, GameMsgCode::GMC_PLAYER_LEAVE_MAP, this, pTarMap, EnterPos.x, EnterPos.y, 0);
      }
      Player::updateRecord(this, 1921, 0);
      MapId = Map::GetMapId(pTarMap);
      GongGaoId = Map::GetGongGaoId(pTarMap);
      Player::EnterMapGongGao(this, GongGaoId, MapId);
    }
  }
}


#####################################
void __cdecl Player::CheckLeaveCycleTower(Player *const this)
{
  int EnterTime; // [rsp+1Ch] [rbp-4h]

  EnterTime = Player::getRecord(this, 1922);
  if ( EnterTime > 0 && Unit::getNow(this) >= EnterTime + 1800 )
  {
    Player::updateRecord(this, 1922, 0);
    Player::OnBackCity(this, 1, 0);
  }
}


#####################################
void __cdecl Player::CheckLevelWastelands(Player *const this)
{
  int LevelTime; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pMap )
  {
    if ( Map::IsWastelands(this->m_pMap) )
    {
      LevelTime = Player::getRecord(this, 2106);
      if ( LevelTime > 0 && Unit::getNow(this) >= LevelTime )
      {
        Player::updateRecord(this, 2106, 0);
        Player::OnBackCity(this, 1, 0);
      }
    }
  }
}


#####################################
void __cdecl Player::CheckAddWastelandsValue(Player *const this)
{
  if ( Map::IsWastelands(this->m_pMap) )
    Player::AddWastelandsValue(this, 1);
}


#####################################
int32_t __cdecl Player::GetMaxValue(Player *const this)
{
  return 600 * Player::getRecord(this, 2107) + 900;
}


#####################################
void __cdecl Player::AddWastelandsValue(Player *const this, int32_t Value)
{
  int32_t MaxValue; // edx
  int32_t v3; // edx
  int32_t OldRecord; // [rsp+1Ch] [rbp-14h]

  if ( Value > 0 && Player::getRecord(this, 2106) <= 0 )
  {
    OldRecord = Player::getRecord(this, 2105);
    if ( Player::GetMaxValue(this) > OldRecord )
    {
      if ( OldRecord + Value < Player::GetMaxValue(this) )
      {
        CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 2105, Value);
      }
      else
      {
        MaxValue = Player::GetMaxValue(this);
        Player::updateRecord(this, 2105, MaxValue);
        v3 = Unit::getNow(this) + 10;
        Player::updateRecord(this, 2106, v3);
      }
    }
  }
}


#####################################
void __cdecl Player::AddBeastShrineValue(Player *const this, int32_t Value)
{
  int OldRecord; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pMap )
  {
    if ( Map::IsBeastShrine(this->m_pMap) )
    {
      OldRecord = Player::getRecord(this, 1163);
      if ( OldRecord <= 599 )
      {
        if ( OldRecord + Value <= 599 )
          CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 1163, Value);
        else
          Player::updateRecord(this, 1163, 600);
        Player::CheckBeastShrinePoints(this);
      }
    }
  }
}


#####################################
void __cdecl Player::CheckAddBeastShrineValue(Player *const this)
{
  if ( Map::IsBeastShrine(this->m_pMap) )
    Player::AddBeastShrineValue(this, 1);
}


#####################################
void __cdecl Player::CheckBeastShrinePoints(Player *const this)
{
  int32_t v1; // edx

  if ( Map::IsBeastShrine(this->m_pMap)
    && Player::getRecord(this, 1164) <= 0
    && CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 1163) > 599 )
  {
    v1 = Unit::getNow(this) + 20;
    Player::updateRecord(this, 1164, v1);
  }
}


#####################################
void __cdecl Player::CheckBeastShrineAutoKick(Player *const this)
{
  MapManager *v1; // rax
  int32_t RunnerId; // ebx
  int32_t v3; // ebx
  MapManager *v4; // rax
  int nRecord; // [rsp+24h] [rbp-1Ch]
  Map *pTargetMap; // [rsp+28h] [rbp-18h]

  if ( this->m_pMap )
  {
    if ( Map::IsBeastShrine(this->m_pMap) )
    {
      nRecord = Player::getRecord(this, 1164);
      if ( nRecord > 0 && Unit::getNow(this) >= nRecord )
      {
        v1 = Answer::Singleton<MapManager>::instance();
        pTargetMap = MapManager::GetMap(v1, 50097);
        if ( pTargetMap )
        {
          RunnerId = Map::GetRunnerId(this->m_pMap);
          if ( RunnerId == Map::GetRunnerId(pTargetMap) )
          {
            Player::switchMap(this, pTargetMap, 32, 46, 0);
          }
          else
          {
            (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
            v3 = Map::GetRunnerId(pTargetMap);
            v4 = Answer::Singleton<MapManager>::instance();
            MapManager::PostMsg(v4, v3, GameMsgCode::GMC_PLAYER_LEAVE_MAP, this, pTargetMap, 32, 46, 0);
          }
        }
        Player::updateRecord(this, 1163, 0);
        Player::updateRecord(this, 1164, 0);
      }
    }
  }
}


#####################################
void __cdecl Player::SendCycleTowerInfo(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t v4; // edx
  int8_t v5; // dl
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x283Fu);
  if ( packet )
  {
    Record = Player::getRecord(this, 2099);
    Answer::NetPacket::writeInt32(packet, Record);
    v4 = Player::getRecord(this, 2097);
    Answer::NetPacket::writeInt32(packet, v4);
    v5 = Player::getRecord(this, 1923);
    Answer::NetPacket::writeInt8(packet, v5);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v8 = this->m_connid;
    v9 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v9, v8, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::SendCycleTowerTime(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int v3; // ebx
  int32_t v4; // edx
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2840u);
  if ( packet )
  {
    v3 = Player::getRecord(this, 1922) + 1800;
    v4 = v3 - Unit::getNow(this);
    Answer::NetPacket::writeInt32(packet, v4);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    LOBYTE(v3) = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v3, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::SetPlantState(Player *const this, bool bState)
{
  bool Change; // [rsp+1Fh] [rbp-1h]

  Change = 0;
  if ( bState )
  {
    if ( this->m_PlantState != 1 )
    {
      this->m_PlantState = 1;
      Change = 1;
    }
  }
  else if ( this->m_PlantState )
  {
    this->m_PlantState = 0;
    Change = 1;
  }
  if ( Change )
    Player::SetNeedSyncAround(this);
}


#####################################
int32_t __cdecl Player::OnEnterSpecialBossMap(Player *const this, Answer::NetPacket *inPacket)
{
  MapManager *v4; // rax
  int32_t MapId; // ebx
  CfgData *v6; // rax
  int32_t v7; // ebx
  CfgData *v8; // rax
  const CfgBeastShrineTable *BeastShrineTable; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v11; // rax
  ChrTask *Task; // rax
  int32_t Record; // ebx
  CExtCurrency *Currency; // rax
  int32_t Now; // edx
  int32_t MapParam; // ebx
  int32_t RunnerId; // ebx
  int32_t v19; // ebx
  MapManager *v20; // rax
  int32_t v21; // ebx
  int32_t GongGaoId; // ecx
  int32_t nMapId; // [rsp+2Ch] [rbp-44h]
  unsigned int nPosX; // [rsp+30h] [rbp-40h]
  unsigned int nPosY; // [rsp+34h] [rbp-3Ch]
  Map *pTarMap; // [rsp+38h] [rbp-38h]
  SpecialBossMapCfg *pCfg; // [rsp+40h] [rbp-30h]
  const ItemDataList *Const; // [rsp+50h] [rbp-20h]
  int32_t NeedMoney; // [rsp+58h] [rbp-18h]
  int Times; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pMap || !inPacket )
    return 10002;
  if ( StaticObj::InDungeon(this) || StaticObj::InActivity(this) )
    return 10002;
  nMapId = Answer::NetPacket::readInt32(inPacket);
  nPosX = Answer::NetPacket::readInt32(inPacket);
  nPosY = Answer::NetPacket::readInt32(inPacket);
  v4 = Answer::Singleton<MapManager>::instance();
  pTarMap = MapManager::GetMap(v4, nMapId);
  if ( !pTarMap )
    return 10002;
  if ( (*((unsigned int (__fastcall **)(Map *, Player *const))pTarMap->_vptr_Map + 4))(pTarMap, this) )
    return 10002;
  MapId = Map::GetMapId(pTarMap);
  if ( MapId == Map::GetMapId(this->m_pMap) )
    return 10002;
  if ( !Map::isWalkablePosition(pTarMap, nPosX, nPosY) )
    return 10002;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetSpecialBossMapCfg(v6, nMapId);
  if ( !pCfg )
    return 10002;
  if ( pCfg->StartCD > 0 && !Map::IsStart(pTarMap) )
  {
    Player::TiShiInfo(this, 25, 0);
    return 10002;
  }
  if ( !StaticObj::IsSpecialBossMap(this) )
  {
    if ( !Map::IsCycleTower(pTarMap) )
    {
      if ( !Map::IsWastelands(pTarMap) )
      {
        if ( Map::IsBeastShrine(pTarMap) )
        {
          v7 = Player::getRecord(this, 2115) + 1;
          v8 = Answer::Singleton<CfgData>::instance();
          BeastShrineTable = CfgData::GetBeastShrineTable(v8);
          Const = CfgBeastShrineTable::GetEnterCost(BeastShrineTable, v7);
          if ( !Const )
            return 10002;
          Bag = Player::GetBag(this);
          if ( !CExtCharBag::RemoveItem(Bag, Const, ITEM_CHANGE_REASON::ICR_ENTER_SPECIAL_BOSS_MAP) )
            return 10002;
          Player::updateRecord(this, 1163, 0);
          Player::updateRecord(this, 1164, 0);
          CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 2115, 1);
        }
        else
        {
          if ( pCfg->ConstItem.m_nId <= 0 || pCfg->ConstItem.m_nCount <= 0 || pCfg->ConstItem.m_nClass <= 0 )
            return 10002;
          v11 = Player::GetBag(this);
          if ( !CExtCharBag::RemoveItem(v11, &pCfg->ConstItem, ITEM_CHANGE_REASON::ICR_ENTER_SPECIAL_BOSS_MAP) )
            return 10002;
        }
      }
      else
      {
        if ( Player::getRecord(this, 2072) <= 0 )
        {
          Task = Player::GetTask(this);
          if ( !ChrTask::isDoingTaskType(Task, 9) )
            CMoneyRewardTask::InitXuWuTask(&this->m_CMoneyRewardTask);
        }
        Record = Player::getRecord(this, 2105);
        if ( Record >= Player::GetMaxValue(this) )
          return 10002;
        Times = Player::getRecord(this, 2104);
        if ( Times > 1 )
        {
          if ( Times > 11 )
            NeedMoney = 3000000;
          else
            NeedMoney = 300000 * (Times - 1);
        }
        else
        {
          NeedMoney = 300000;
        }
        Currency = Player::GetCurrency(this);
        if ( !CExtCurrency::DecMoneyAndNoBind(Currency, NeedMoney, CURRENCY_CHANGE_REASON::GCR_ENTER_WASTELANDS, 0) )
          return 10002;
        CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 2104, 1);
      }
    }
    else
    {
      Now = Unit::getNow(this);
      Player::updateRecord(this, 1922, Now);
    }
  }
  else
  {
    MapParam = Map::GetMapParam(this->m_pMap);
    if ( MapParam != Map::GetMapParam(pTarMap) )
      return 10002;
  }
  Player::setOldPosition(this);
  Player::broadcastLeave(this);
  RunnerId = Map::GetRunnerId(this->m_pMap);
  if ( RunnerId == Map::GetRunnerId(pTarMap) )
  {
    (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
    (*((void (__fastcall **)(Map *, Player *const, _QWORD, _QWORD))pTarMap->_vptr_Map + 15))(
      pTarMap,
      this,
      nPosX,
      nPosY);
  }
  else
  {
    (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
    v19 = Map::GetRunnerId(pTarMap);
    v20 = Answer::Singleton<MapManager>::instance();
    MapManager::PostMsg(v20, v19, GameMsgCode::GMC_PLAYER_LEAVE_MAP, this, pTarMap, nPosX, nPosY, 0);
  }
  v21 = Map::GetMapId(pTarMap);
  GongGaoId = Map::GetGongGaoId(pTarMap);
  Player::EnterMapGongGao(this, GongGaoId, v21);
  return 0;
}


#####################################
int32_t __cdecl Player::OnLeaveSpecialBossMap(Player *const this, Answer::NetPacket *inPacket)
{
  Player::OnBackCity(this, 1, 0);
  return 0;
}


#####################################
int32_t __cdecl Player::OnChristmasDuiHuan(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  int32_t nId; // [rsp+1Ch] [rbp-34h]
  ChristmasDuiHuan *pCfg; // [rsp+20h] [rbp-30h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned int)nId >= 0xA )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetChristmasDuiHuanCfg(v3, nId);
  if ( !pCfg )
    return 10002;
  if ( Unit::getNow(this) < pCfg->nStartTime || Unit::getNow(this) > pCfg->nEndTime )
    return 10002;
  if ( pCfg->nLimitCount <= Player::getRecord(this, nId + 8030) )
    return 10002;
  Bag = Player::GetBag(this);
  if ( !CExtCharBag::AddAndRemoveItem(Bag, &pCfg->Items, &pCfg->CostItems, ITEM_CHANGE_REASON::IDCR_CHRISTMAS_DUI_HUAN) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this);
  CExtOperateLimit::AddLimitCount(OperateLimit, nId + 8030, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this);
  ConnId = Player::getConnId(this);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, nId);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonRandom(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  Dungeon *pDungeon; // [rsp+18h] [rbp-8h]

  if ( !inPacket )
    return 10002;
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getDungeonType(v4) != 35 )
    return 10002;
  Dungeon::OnRandomPos(pDungeon, this);
  return 0;
}


#####################################
int32_t __cdecl Player::OnBuyJingLiValue(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const EnergyCfg *EnergyCfg; // rax
  int32_t Record; // eax
  int32_t v6; // eax
  int64_t v7; // rdx
  int32_t BuyAddEnergy; // ebx
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v10; // rax
  EnergyCfg Ener; // [rsp+10h] [rbp-40h] BYREF
  int32_t Times; // [rsp+3Ch] [rbp-14h]

  if ( !inPacket )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  EnergyCfg = CfgData::GetEnergyCfg(v3);
  EnergyCfg::EnergyCfg(&Ener, EnergyCfg);
  Record = Player::getRecord(this, 37305);
  if ( Record < Ener.MaxEnergy )
  {
    Times = Player::getRecord(this, 37306);
    v6 = std::vector<int>::size(&Ener.EnergyPrice);
    if ( v6 > Times )
    {
      if ( *std::vector<int>::operator[](&Ener.EnergyPrice, Times) > 0 )
      {
        v7 = *std::vector<int>::operator[](&Ener.EnergyPrice, Times);
        if ( !Player::DecCurrency(
                this,
                CURRENCY_TYPE::CURRENCY_GOLD,
                v7,
                CURRENCY_CHANGE_REASON::CCR_BUY_JING_LI_VALUE,
                0) )
        {
          v2 = 2;
        }
        else
        {
          BuyAddEnergy = Ener.BuyAddEnergy;
          OperateLimit = Player::GetOperateLimit(this);
          CExtOperateLimit::AddLimitCount(OperateLimit, 37305, BuyAddEnergy);
          v10 = Player::GetOperateLimit(this);
          CExtOperateLimit::AddLimitCount(v10, 37306, 1);
          Player::SendJingLiValue(this);
          v2 = 0;
        }
      }
      else
      {
        v2 = 2;
      }
    }
    else
    {
      v2 = 2;
    }
  }
  else
  {
    v2 = 2;
  }
  EnergyCfg::~EnergyCfg(&Ener);
  return v2;
}


#####################################
void __cdecl Player::SendJingLiValue(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t v4; // edx
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2842u);
  if ( packet )
  {
    Record = Player::getRecord(this, 37305);
    Answer::NetPacket::writeInt32(packet, Record);
    v4 = Player::getRecord(this, 37306);
    Answer::NetPacket::writeInt32(packet, v4);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::ResetJingLi(Player *const this)
{
  CfgData *v1; // rax
  const EnergyCfg *EnergyCfg; // rax
  int32_t Record; // eax
  int32_t v5; // eax
  int32_t Now; // edx
  tm NowTime; // [rsp+10h] [rbp-80h] BYREF
  EnergyCfg Ener; // [rsp+50h] [rbp-40h] BYREF

  v1 = Answer::Singleton<CfgData>::instance();
  EnergyCfg = CfgData::GetEnergyCfg(v1);
  EnergyCfg::EnergyCfg(&Ener, EnergyCfg);
  Unit::getLocalNow(&NowTime, this);
  if ( NowTime.tm_hour >= Ener.EnergyTime )
  {
    Record = Player::getRecord(this, 37307);
    if ( Answer::DayTime::daydiff(Record) )
    {
      v5 = Player::getRecord(this, 37305);
      if ( v5 < Ener.MaxEnergy )
        Player::updateRecord(this, 37305, Ener.MaxEnergy);
      Player::updateRecord(this, 37306, 0);
      Now = Unit::getNow(this);
      Player::updateRecord(this, 37307, Now);
      Player::SendJingLiValue(this);
    }
  }
  EnergyCfg::~EnergyCfg(&Ener);
}


#####################################
int32_t __cdecl Player::OnBuyRandomPosTimes(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  Dungeon *pDungeon; // [rsp+18h] [rbp-8h]

  if ( !inPacket )
    return 10002;
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getDungeonType(v4) != 35 )
    return 10002;
  Dungeon::OnBuyRandomPosTimes(pDungeon, this);
  return 0;
}


#####################################
int32_t __cdecl Player::onFamilyWarActivePillar(Player *const this, Answer::NetPacket *inPacket)
{
  CActivityMap *v4; // rax
  CActivity *Activity; // rax
  CFamilyWar *v6; // rax
  char nIndex; // [rsp+1Fh] [rbp-11h]

  if ( !inPacket || !StaticObj::InActivity(this) )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( nIndex > 3 )
    return 10002;
  if ( this->m_pMap )
    v4 = (CActivityMap *)__dynamic_cast(
                           this->m_pMap,
                           (const struct __class_type_info *)&`typeinfo for'Map,
                           (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                           0);
  else
    v4 = 0;
  if ( !v4 )
    return 10002;
  Activity = CActivityMap::GetActivity(v4);
  if ( Activity )
    v6 = (CFamilyWar *)__dynamic_cast(
                         Activity,
                         (const struct __class_type_info *)&`typeinfo for'CActivity,
                         (const struct __class_type_info *)&`typeinfo for'CFamilyWar,
                         0);
  else
    v6 = 0;
  if ( !v6 )
    return 10002;
  if ( !CFamilyWar::OnActivePillar(v6, this, nIndex) )
    return 10002;
  return 0;
}


#####################################
int32_t __cdecl Player::GetDungeonDailyEnterLimit(Player *const this, int32_t nDungeonId)
{
  CfgData *v2; // rax
  int32_t v4; // edx
  CfgDungeon *pCfgDungeon; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v2, nDungeonId);
  if ( !pCfgDungeon )
    return 0;
  v4 = DungeonBuyLimitKey(pCfgDungeon->group_id);
  return pCfgDungeon->daily_count + Player::getRecord(this, v4);
}


#####################################
int32_t __cdecl Player::onBuyDungeonEnterTime(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t v4; // edx
  int32_t v5; // eax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  int32_t nId; // [rsp+1Ch] [rbp-34h]
  CfgDungeon *pCfgDungeon; // [rsp+20h] [rbp-30h]
  int nBuyTimes; // [rsp+28h] [rbp-28h]
  int32_t buyCost; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v3, nId);
  if ( !pCfgDungeon )
    return 10002;
  v4 = DungeonBuyLimitKey(pCfgDungeon->group_id);
  nBuyTimes = Player::getRecord(this, v4);
  if ( pCfgDungeon->buyTimes <= nBuyTimes )
    return 10002;
  buyCost = pCfgDungeon->buyCost;
  if ( pCfgDungeon->type == 34 && nBuyTimes > 4 )
    buyCost *= 2;
  if ( !Player::DecCurrency(
          this,
          CURRENCY_TYPE::CURRENCY_GOLD,
          buyCost,
          CURRENCY_CHANGE_REASON::GCR_BUY_DUNGEON_ENTER_TIMES,
          nId) )
    return 10002;
  v5 = DungeonBuyLimitKey(pCfgDungeon->group_id);
  CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, v5, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, m_connid, m_cgindex, Proc, nId);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonQuickDone(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int weekday; // ebx
  Job_t job; // bl
  int v7; // eax
  int v8; // eax
  CharId_t Cid; // r14
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v14; // rax
  int32_t Record; // ebx
  CfgData *v16; // rax
  const MemChrBag *v17; // rax
  int32_t quickDoneDrop; // ebx
  CfgData *v19; // rax
  int8_t v20; // bl
  CfgMonsterGroupDrop *v22; // rax
  CfgMonsterGroupDrop *v23; // rax
  Answer::Random *v25; // rax
  CfgMonsterGroupDrop *v26; // rax
  CfgMonsterGroupDrop *v27; // rax
  int32_t v28; // ebx
  CfgData *v29; // rax
  Answer::Random *v30; // rax
  CfgMonsterDropGroup *v31; // rax
  int32_t limit_time; // ebx
  CfgData *v33; // rax
  const CfgLimitTimeTable *LimitTimeTable; // rax
  CfgMonsterDropGroup *v35; // rax
  int32_t FreeSlotCount; // eax
  int32_t v37; // edx
  MemChrBag dropItem; // [rsp+10h] [rbp-1B0h] BYREF
  tm localNow; // [rsp+50h] [rbp-170h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterDropGroup*,std::vector<CfgMonsterDropGroup> > eiter; // [rsp+90h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterDropGroup*,std::vector<CfgMonsterDropGroup> > iter_0; // [rsp+A0h] [rbp-120h] BYREF
  std::_List_iterator<int> it_0; // [rsp+B0h] [rbp-110h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop*,std::vector<CfgMonsterGroupDrop> > it; // [rsp+C0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+D0h] [rbp-F0h] BYREF
  Int32List groupIds; // [rsp+E0h] [rbp-E0h] BYREF
  MemChrBagVector vRewards; // [rsp+F0h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __i; // [rsp+110h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+120h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop*,std::vector<CfgMonsterGroupDrop> > v50; // [rsp+130h] [rbp-90h] BYREF
  std::_List_iterator<int> __x; // [rsp+140h] [rbp-80h] BYREF
  int32_t nDungeonId; // [rsp+148h] [rbp-78h]
  int8_t bDouble; // [rsp+14Fh] [rbp-71h]
  CfgDungeon *pCfgDungeon; // [rsp+150h] [rbp-70h]
  int32_t nRatio; // [rsp+158h] [rbp-68h]
  int32_t nCostGold; // [rsp+15Ch] [rbp-64h]
  CfgDungeonReward *pReward; // [rsp+160h] [rbp-60h]
  int32_t nNeedBagSize; // [rsp+168h] [rbp-58h]
  int32_t nNeedPetEggSize; // [rsp+16Ch] [rbp-54h]
  CfgMonsterGroupDropVector *pGroups; // [rsp+170h] [rbp-50h]
  int32_t nowMinute; // [rsp+178h] [rbp-48h]
  int32_t i; // [rsp+17Ch] [rbp-44h]
  int32_t probability; // [rsp+180h] [rbp-40h]
  int32_t groupProbability; // [rsp+184h] [rbp-3Ch]
  CfgMonsterDropGroupVector *pDropGroup; // [rsp+188h] [rbp-38h]
  int32_t roll; // [rsp+190h] [rbp-30h]
  int32_t nLevel; // [rsp+194h] [rbp-2Ch]
  float f; // [rsp+198h] [rbp-28h]
  int32_t nFinalExp; // [rsp+19Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nDungeonId = Answer::NetPacket::readInt32(inPacket);
  bDouble = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v3, nDungeonId);
  if ( !pCfgDungeon )
    return 10002;
  if ( pCfgDungeon->quickDoneCost <= 0 )
    return 10002;
  nRatio = 1;
  nCostGold = pCfgDungeon->quickDoneCost;
  if ( bDouble )
  {
    nCostGold += pCfgDungeon->double_cost;
    nRatio = 2;
  }
  if ( Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD) < nCostGold )
    return 10002;
  Unit::getLocalNow(&localNow, this);
  weekday = pCfgDungeon->weekday;
  if ( ((weekday >> GetWeekDay(localNow.tm_wday)) & 1) == 0 )
    return 10002;
  if ( localNow.tm_hour < pCfgDungeon->start_hour || localNow.tm_hour > pCfgDungeon->end_hour )
    return 10002;
  if ( pCfgDungeon->job > 0 )
  {
    job = pCfgDungeon->job;
    if ( job != Player::getJob(this) )
      return 10002;
  }
  v7 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  if ( v7 < pCfgDungeon->level
    || (v8 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this), v8 > pCfgDungeon->maxLevel) )
  {
    Cid = Player::getCid(this);
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v14 = Answer::Singleton<GameService>::instance();
    GameService::replyfailure(v14, m_connid, m_cgindex, Proc, 10022, Cid);
    return 10002;
  }
  else if ( !CExtOperateLimit::CheckIsLimitedForever(&this->m_extOperateLimit, nDungeonId + 20000) )
  {
    return 10002;
  }
  else
  {
    Record = Player::getRecord(this, pCfgDungeon->group_id);
    if ( Record < Player::GetDungeonDailyEnterLimit(this, nDungeonId) )
    {
      v16 = Answer::Singleton<CfgData>::instance();
      pReward = CfgData::getDungeonReward(v16, nDungeonId);
      if ( pReward )
      {
        std::vector<MemChrBag>::vector(&vRewards);
        nNeedBagSize = 0;
        nNeedPetEggSize = 0;
        if ( !std::vector<MemChrBag>::empty(&pCfgDungeon->rewardItem) )
        {
          __i._M_current = std::vector<MemChrBag>::begin(&pCfgDungeon->rewardItem)._M_current;
          __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::__normal_iterator<MemChrBag*>(
            &iter,
            &__i);
          while ( 1 )
          {
            __rhs._M_current = std::vector<MemChrBag>::end(&pCfgDungeon->rewardItem)._M_current;
            if ( !__gnu_cxx::operator!=<MemChrBag const*,MemChrBag*,std::vector<MemChrBag>>(&iter, &__rhs) )
              break;
            ++nNeedBagSize;
            v17 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&iter);
            std::vector<MemChrBag>::push_back(&vRewards, v17);
            __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter);
          }
        }
        std::list<int>::list(&groupIds);
        quickDoneDrop = pCfgDungeon->quickDoneDrop;
        v19 = Answer::Singleton<CfgData>::instance();
        pGroups = CfgData::getMonsterGroupDrop(v19, quickDoneDrop);
        if ( pGroups )
        {
          Unit::getLocalNow((tm *)&dropItem, this);
          nowMinute = 60 * dropItem.itemCount + *(_DWORD *)&dropItem.itemClass;
          for ( it._M_current = std::vector<CfgMonsterGroupDrop>::begin(pGroups)._M_current;
                ;
                __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator++(&it) )
          {
            v50._M_current = std::vector<CfgMonsterGroupDrop>::end(pGroups)._M_current;
            if ( !__gnu_cxx::operator!=<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>(&it, &v50) )
              break;
            if ( __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->job )
            {
              v20 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->job;
              if ( v20 != Player::getJob(this) )
                continue;
            }
            v22 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
            if ( v22->begin_time <= nowMinute )
            {
              v23 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
              if ( v23->end_time >= nowMinute )
              {
                for ( i = 0; ; ++i )
                {
                  v27 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
                  if ( v27->repeat <= i )
                    break;
                  probability = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it)->probability;
                  v25 = Answer::Singleton<Answer::Random>::instance();
                  groupProbability = Answer::Random::generate(v25, 1, 1000000);
                  if ( probability >= groupProbability )
                  {
                    v26 = __gnu_cxx::__normal_iterator<CfgMonsterGroupDrop *,std::vector<CfgMonsterGroupDrop>>::operator->(&it);
                    std::list<int>::push_back(&groupIds, &v26->group_id);
                  }
                }
              }
            }
          }
        }
        for ( it_0._M_node = std::list<int>::begin(&groupIds)._M_node; ; std::_List_iterator<int>::operator++(&it_0) )
        {
          __x._M_node = std::list<int>::end(&groupIds)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it_0, &__x) )
            break;
          v28 = *std::_List_iterator<int>::operator*(&it_0);
          v29 = Answer::Singleton<CfgData>::instance();
          pDropGroup = CfgData::getMonsterDropGroup(v29, v28);
          if ( pDropGroup )
          {
            v30 = Answer::Singleton<Answer::Random>::instance();
            roll = Answer::Random::generate(v30, 1, 1000);
            iter_0._M_current = std::vector<CfgMonsterDropGroup>::begin(pDropGroup)._M_current;
            eiter._M_current = std::vector<CfgMonsterDropGroup>::end(pDropGroup)._M_current;
            while ( __gnu_cxx::operator!=<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>(&iter_0, &eiter) )
            {
              v31 = __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0);
              if ( v31->probability >= roll )
              {
                memset(&dropItem, 0, sizeof(dropItem));
                dropItem.itemId = __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0)->item_id;
                dropItem.itemClass = __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0)->item_class;
                dropItem.bind = __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0)->bind_type;
                dropItem.itemCount = 1;
                if ( __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0)->limit_time > 0 )
                {
                  limit_time = __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0)->limit_time;
                  v33 = Answer::Singleton<CfgData>::instance();
                  LimitTimeTable = CfgData::GetLimitTimeTable(v33);
                  dropItem.endTime = CfgLimitTimeTable::GetLimitTime(LimitTimeTable, limit_time);
                }
                if ( dropItem.itemClass == 1
                  || dropItem.itemClass == 2
                  || dropItem.itemClass == 3
                  || dropItem.itemClass == 7 )
                {
                  ++nNeedBagSize;
                }
                else if ( dropItem.itemClass == 6 )
                {
                  ++nNeedPetEggSize;
                }
                std::vector<MemChrBag>::push_back(&vRewards, &dropItem);
                break;
              }
              v35 = __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator->(&iter_0);
              roll -= v35->probability;
              __gnu_cxx::__normal_iterator<CfgMonsterDropGroup *,std::vector<CfgMonsterDropGroup>>::operator++(&iter_0);
            }
          }
        }
        FreeSlotCount = CExtCharBag::GetFreeSlotCount(&this->m_extCharBag);
        if ( FreeSlotCount >= nNeedBagSize )
        {
          CExtCharBag::AddItem(&this->m_extCharBag, &vRewards, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD);
          Player::DecCurrency(
            this,
            CURRENCY_TYPE::CURRENCY_GOLD,
            nCostGold,
            CURRENCY_CHANGE_REASON::GCR_QUICK_DONE_DUNGEON,
            nDungeonId);
          if ( pReward->money > 0 )
            Player::AddCurrency(
              this,
              CURRENCY_TYPE::CURRENCY_MONEY,
              nRatio * pReward->money,
              CURRENCY_CHANGE_REASON::MCR_DUNGEON_REWARD,
              nDungeonId);
          if ( pReward->cash > 0 )
            Player::AddCurrency(
              this,
              CURRENCY_TYPE::CURRENCY_CASH,
              nRatio * pReward->cash,
              CURRENCY_CHANGE_REASON::GCR_DUNGEON_REWARD,
              nDungeonId);
          if ( pReward->exp > 0 )
            Player::addExp(this, nRatio * pReward->exp, 0, 1);
          if ( pCfgDungeon->type == 15 )
          {
            nLevel = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
            if ( nLevel > 70 )
            {
              if ( nLevel > 119 )
                nLevel = ((nLevel - 120) >> 3) + 50;
              else
                nLevel -= 70;
            }
            else
            {
              nLevel = 0;
            }
            f = (float)((float)nLevel / 70.0) + 1.0;
            nFinalExp = nRatio * (int)(float)((float)(25000000.0 * f) * f);
            Player::addExp(this, nFinalExp, 0, 1);
          }
          v37 = Player::getRecord(this, pCfgDungeon->group_id) + 1;
          Player::updateRecord(this, pCfgDungeon->group_id, v37);
          CHuoYueDu::AddHuoYueDuRecord(&this->m_PlayerHuoYueDu, 2, pCfgDungeon->group_id, 0);
          v2 = 0;
        }
        else
        {
          Player::TiShiInfo(this, 2048, 0);
          v2 = 10002;
        }
        std::list<int>::~list(&groupIds);
        std::vector<MemChrBag>::~vector(&vRewards);
      }
      else
      {
        return 10002;
      }
    }
    else
    {
      return 10002;
    }
  }
  return v2;
}


#####################################
int32_t __cdecl Player::onEnterDungeon(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  ProcId_t Proc; // dx
  int32_t nDungeonId; // [rsp+24h] [rbp-1Ch]
  CfgDungeon *pCfgDungeon; // [rsp+28h] [rbp-18h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  nDungeonId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v3, nDungeonId);
  if ( !pCfgDungeon )
    return 10002;
  if ( pCfgDungeon->CanEnter > 0 )
    return 10002;
  if ( pCfgDungeon->type == 25 )
    return CExtCharFamily::EnterFamilyDungeon(&this->m_extCharFamily);
  Proc = Answer::NetPacket::getProc(inPacket);
  return Player::enterDungeon(this, nDungeonId, Proc, 0, 0, 0, 0, 0);
}


#####################################
int32_t __cdecl Player::enterDungeon(
        Player *const this,
        int32_t nDungeonId,
        ProcId_t nProc,
        int32_t nBuffId,
        int32_t nLevel,
        int8_t nHard,
        int8_t nQuality,
        int32_t nEvent)
{
  CfgData *v8; // rax
  Dungeon *v10; // rax
  int8_t Hard; // bl
  CfgData *v12; // rax
  const CfgFamilyDungeonTable *FamilyDungeonTable; // rax
  CfgData *v14; // rax
  int32_t PosY; // r12d
  int32_t PosX; // eax
  int32_t DungeonType; // eax
  int32_t id; // ebx
  CharId_t Cid; // r14
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v24; // rax
  int weekday; // ebx
  Job_t job; // bl
  int v28; // eax
  int v29; // eax
  CharId_t v31; // r14
  int16_t v32; // r12
  int8_t v33; // bl
  GameService *v34; // rax
  int32_t star; // ebx
  int32_t Record; // ebx
  CharId_t v37; // r14
  int16_t v38; // r12
  int8_t v39; // bl
  GameService *v40; // rax
  int8_t vip; // bl
  CVip *PlayerVip; // rax
  int8_t TeQuan; // bl
  CVip *v44; // rax
  int32_t task_id; // ebx
  CfgData *v46; // rax
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  int64_t v50; // rax
  MapManager *v51; // rax
  int16_t v52; // r12
  int8_t v53; // bl
  GameService *v54; // rax
  int64_t costMoney; // rbx
  CExtCurrency *v56; // rax
  int16_t v57; // r12
  int8_t v58; // bl
  GameService *v59; // rax
  int32_t RunnerId; // ebx
  MapManager *v61; // rax
  int16_t v62; // r12
  int8_t v63; // bl
  GameService *v64; // rax
  int32_t v65; // edx
  int32_t group_id; // ebx
  CHuoYueDu *PlayerHuoYueDu; // rax
  int32_t v68; // eax
  int8_t v69; // bl
  DBService *v70; // rax
  tm localNow; // [rsp+30h] [rbp-E0h] BYREF
  LogDungeon logDungeon; // [rsp+70h] [rbp-A0h] BYREF
  Position pos; // [rsp+90h] [rbp-80h] BYREF
  ItemData costItem; // [rsp+A0h] [rbp-70h] BYREF
  CfgDungeon *pCfgDungeon; // [rsp+B8h] [rbp-58h]
  bool bChangeDungeon; // [rsp+C7h] [rbp-49h]
  Dungeon *pCurDungeon; // [rsp+C8h] [rbp-48h]
  const CfgFamilyDungeon *pCfg; // [rsp+D0h] [rbp-40h]
  CfgNpc *cfgNpc; // [rsp+D8h] [rbp-38h]
  Dungeon *pDungeon; // [rsp+E0h] [rbp-30h]
  const CfgTask *pCfgTask; // [rsp+E8h] [rbp-28h]

  v8 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v8, nDungeonId);
  if ( !pCfgDungeon || !this->m_pMap )
    return 10002;
  if ( Player::benefitType(this) != BenefitType::BT_NORMAL )
    return 10002;
  if ( Player::IsInStall(this) )
    return 10002;
  bChangeDungeon = 1;
  if ( this->m_pMap )
    v10 = (Dungeon *)__dynamic_cast(
                       this->m_pMap,
                       (const struct __class_type_info *)&`typeinfo for'Map,
                       (const struct __class_type_info *)&`typeinfo for'Dungeon,
                       0);
  else
    v10 = 0;
  pCurDungeon = v10;
  if ( pCfgDungeon->type == 35 )
  {
    if ( !pCurDungeon )
      return 10002;
    if ( Dungeon::getDungeonType(pCurDungeon) != 25 )
      return 10002;
    Hard = Dungeon::GetHard(pCurDungeon);
    v12 = Answer::Singleton<CfgData>::instance();
    FamilyDungeonTable = CfgData::GetFamilyDungeonTable(v12);
    pCfg = CfgFamilyDungeonTable::GetDungeon(FamilyDungeonTable, Hard);
    if ( !pCfg )
      return 10002;
    if ( pCfg->nBaoKuFuBen != nDungeonId )
      return 10002;
    v14 = Answer::Singleton<CfgData>::instance();
    cfgNpc = CfgData::getNpc(v14, 5015);
    if ( !cfgNpc )
      return 10002;
    PosY = StaticObj::GetPosY(this);
    PosX = StaticObj::GetPosX(this);
    if ( !Map::NearNpc(this->m_pMap, cfgNpc->id, PosX, PosY, 10) )
      return 10002;
  }
  else if ( pCfgDungeon->type == 36 && !Map::IsBeastShrine(this->m_pMap) )
  {
    return 10002;
  }
  if ( pCurDungeon )
  {
    DungeonType = Dungeon::getDungeonType(pCurDungeon);
    if ( DungeonType == 22 )
    {
      id = pCfgDungeon->id;
      if ( id != Dungeon::getDungeonId(pCurDungeon) )
        return 10002;
      if ( Dungeon::getState(pCurDungeon) != DungeonState::DS_WIN
        && Dungeon::getState(pCurDungeon) != DungeonState::DS_FAIL )
      {
        return 10002;
      }
      bChangeDungeon = 0;
    }
    else if ( DungeonType != 25 )
    {
      if ( DungeonType != 16 )
        return 10002;
      if ( pCfgDungeon->type != 16 )
        return 10002;
    }
    if ( bChangeDungeon )
      Player::leaveDungeon(this);
  }
  else if ( StaticObj::InDungeon(this) || StaticObj::InActivity(this) )
  {
    return 10002;
  }
  if ( CExtCharTeamDungeon::IsInTeamDungeon(&this->m_extCharTeamDungeon) )
    return 10002;
  if ( pCfgDungeon->type != 12 )
  {
    if ( this->m_trailer )
    {
      Cid = Player::getCid(this);
      m_cgindex = this->m_cgindex;
      m_connid = this->m_connid;
      v24 = Answer::Singleton<GameService>::instance();
      return GameService::replyfailure(v24, m_connid, m_cgindex, nProc, 10055, Cid);
    }
    Unit::getLocalNow(&localNow, this);
    weekday = pCfgDungeon->weekday;
    if ( ((weekday >> GetWeekDay(localNow.tm_wday)) & 1) == 0 )
      return 10002;
    if ( localNow.tm_hour < pCfgDungeon->start_hour || localNow.tm_hour > pCfgDungeon->end_hour )
      return 10002;
    if ( pCfgDungeon->job > 0 )
    {
      job = pCfgDungeon->job;
      if ( job != Player::getJob(this) )
        return 10002;
    }
    v28 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
    if ( v28 < pCfgDungeon->level
      || (v29 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this), v29 > pCfgDungeon->maxLevel) )
    {
      v31 = Player::getCid(this);
      v32 = this->m_cgindex;
      v33 = this->m_connid;
      v34 = Answer::Singleton<GameService>::instance();
      GameService::replyfailure(v34, v33, v32, nProc, 10022, v31);
      return 10002;
    }
    if ( pCfgDungeon->last_id > 0
      && !CExtOperateLimit::CheckIsLimitedForever(&this->m_extOperateLimit, pCfgDungeon->last_id + 20000) )
    {
      return 10002;
    }
    if ( pCfgDungeon->type == 16 )
    {
      star = pCfgDungeon->star;
      if ( star != CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37210) + 1 )
        return 10002;
    }
    Record = Player::getRecord(this, pCfgDungeon->group_id);
    if ( Record >= Player::GetDungeonDailyEnterLimit(this, nDungeonId) )
    {
      v37 = Player::getCid(this);
      v38 = this->m_cgindex;
      v39 = this->m_connid;
      v40 = Answer::Singleton<GameService>::instance();
      GameService::replyfailure(v40, v39, v38, nProc, 10023, v37);
      return 10002;
    }
    vip = pCfgDungeon->vip;
    PlayerVip = Player::GetPlayerVip(this);
    if ( vip > CVip::GetVipLevel(PlayerVip) )
      return 2;
    if ( pCfgDungeon->TeQuan > 0 )
    {
      TeQuan = pCfgDungeon->TeQuan;
      v44 = Player::GetPlayerVip(this);
      if ( !CVip::GetVipFlg(v44, TeQuan) )
        return 2;
    }
    costItem = pCfgDungeon->costItem;
    if ( pCfgDungeon->type == 22 )
    {
      costItem.m_nCount = Player::getRecord(this, pCfgDungeon->group_id) / 2 + 1;
    }
    else if ( pCfgDungeon->type == 36 && nProc == 810 )
    {
      costItem.m_nCount = 0;
    }
    if ( pCfgDungeon->task_id > 0 )
    {
      task_id = pCfgDungeon->task_id;
      v46 = Answer::Singleton<CfgData>::instance();
      pCfgTask = CfgData::getTask(v46, task_id);
      if ( pCfgTask && ChrTask::GetTypeTask(&this->m_task, pCfgTask->type) )
        return 10002;
    }
    if ( costItem.m_nCount > 0 && !CExtCharBag::HasItem(&this->m_extCharBag, &costItem) )
      return 10002;
    if ( pCfgDungeon->costMoney > 0 )
    {
      Currency = Player::GetCurrency(this);
      MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
      if ( MoneyBindAndNoBind < pCfgDungeon->costMoney )
        return 2;
    }
    if ( pCfgDungeon->costGold > 0 )
    {
      v50 = Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD);
      if ( v50 < pCfgDungeon->costGold )
        return 2;
    }
    pDungeon = pCurDungeon;
    if ( bChangeDungeon )
    {
      v51 = Answer::Singleton<MapManager>::instance();
      pDungeon = MapManager::NewDungeon(v51, nDungeonId);
    }
    if ( !pDungeon )
    {
      v52 = this->m_cgindex;
      v53 = this->m_connid;
      v54 = Answer::Singleton<GameService>::instance();
      GameService::replyfailure(v54, v53, v52, nProc, 50004, 0);
      return 10002;
    }
    if ( pCfgDungeon->type != 17 )
    {
      if ( pCfgDungeon->costMoney > 0 )
      {
        costMoney = pCfgDungeon->costMoney;
        v56 = Player::GetCurrency(this);
        if ( !CExtCurrency::DecMoneyAndNoBind(v56, costMoney, CURRENCY_CHANGE_REASON::MCR_ENTER_DUNGEON, 0) )
          return 2;
      }
      if ( pCfgDungeon->costGold > 0
        && !Player::DecCurrency(
              this,
              CURRENCY_TYPE::CURRENCY_GOLD,
              pCfgDungeon->costGold,
              CURRENCY_CHANGE_REASON::GCR_ENTER_DUNGEON,
              nDungeonId) )
      {
        return 2;
      }
      if ( costItem.m_nCount > 0 )
        CExtCharBag::RemoveItem(&this->m_extCharBag, &costItem, ITEM_CHANGE_REASON::ICR_ENETR_DUNGEON);
    }
    if ( nBuffId > 0 )
      Dungeon::SetMonsterBuff(pDungeon, nBuffId);
    if ( nLevel > 0 )
      Dungeon::SetLevel(pDungeon, nLevel);
    if ( nHard > 0 )
      Dungeon::SetHard(pDungeon, nHard);
    if ( nQuality > 0 )
      Dungeon::SetQuality(pDungeon, nQuality);
    if ( nEvent > 0 )
      Dungeon::OpenEvent(pDungeon, nEvent);
    if ( bChangeDungeon )
    {
      Position::Position(&pos, pCfgDungeon->x, pCfgDungeon->y);
      if ( Dungeon::StayPosition(pDungeon) )
        pos = StaticObj::getCurrentTile(this);
      Dungeon::start(pDungeon, 0);
      Player::setOldPosition(this);
      Player::broadcastLeave(this);
      (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
      v57 = this->m_cgindex;
      v58 = this->m_connid;
      v59 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v59, v58, v57, nProc, nDungeonId);
      (*((void (__fastcall **)(Dungeon *, Player *const, _QWORD, _QWORD))pDungeon->_vptr_Map + 15))(
        pDungeon,
        this,
        (unsigned int)pos.x,
        (unsigned int)pos.y);
      RunnerId = Map::GetRunnerId(pDungeon);
      v61 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v61, RunnerId, GameMsgCode::GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0);
    }
    else
    {
      v62 = this->m_cgindex;
      v63 = this->m_connid;
      v64 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v64, v63, v62, nProc, nDungeonId);
      Dungeon::restart(pDungeon, 0);
    }
    if ( pCfgDungeon->type != 13 && pCfgDungeon->type != 15 && pCfgDungeon->type != 17 )
    {
      v65 = Player::getRecord(this, pCfgDungeon->group_id) + 1;
      Player::updateRecord(this, pCfgDungeon->group_id, v65);
      group_id = pCfgDungeon->group_id;
      PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this);
      CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 2, group_id, 0);
      v68 = Player::getRecord(this, pCfgDungeon->group_id);
      DailyActivity::AddDungeonRecord(&this->m_PlayerDailyActivity, pCfgDungeon->type, v68, 0);
    }
    if ( pCfgDungeon->type == 22 )
      Player::SendNewEquipDungeonIconState(this);
    memset(&logDungeon, 0, sizeof(logDungeon));
    logDungeon.cid = Player::getCid(this);
    logDungeon.did = nDungeonId;
    logDungeon.type = Dungeon::getDungeonType(pDungeon);
    logDungeon.level = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
    logDungeon.start_time = Dungeon::GetStartTime(pDungeon);
    v69 = this->m_connid;
    v70 = Answer::Singleton<DBService>::instance();
    DBService::insertDungeon(v70, v69, &logDungeon);
    CNationalDayHd::AddNationalValue(&this->m_CNationalDayHd, NATIONAL_HD_TYPE::HHT_YJSK, 1, pCfgDungeon->group_id);
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onLeaveDungeon(Player *const this, Answer::NetPacket *inPacket)
{
  Dungeon *v3; // rax
  int8_t m_connid; // bl
  DBService *v6; // rax
  LogDungeon logDungeon; // [rsp+10h] [rbp-40h] BYREF
  Dungeon *pDungeon; // [rsp+38h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  if ( !StaticObj::InDungeon(this) )
    return 10002;
  if ( this->m_pMap )
    v3 = (Dungeon *)__dynamic_cast(
                      this->m_pMap,
                      (const struct __class_type_info *)&`typeinfo for'Map,
                      (const struct __class_type_info *)&`typeinfo for'Dungeon,
                      0);
  else
    v3 = 0;
  pDungeon = v3;
  if ( !v3 )
    return 10002;
  if ( (Dungeon::getDungeonType(pDungeon) == 15 || Dungeon::getDungeonType(pDungeon) == 23) && !Dungeon::IsWin(pDungeon) )
  {
    Dungeon::onEndDungeon(pDungeon, this);
  }
  else
  {
    if ( !Dungeon::IsWin(pDungeon) )
    {
      logDungeon.level = 0;
      logDungeon.cid = Player::getCid(this);
      logDungeon.did = Dungeon::getDungeonId(pDungeon);
      logDungeon.type = Dungeon::getDungeonType(pDungeon);
      logDungeon.start_time = Dungeon::GetStartTime(pDungeon);
      logDungeon.finish_time = Unit::getNow(this);
      logDungeon.state = 2;
      m_connid = this->m_connid;
      v6 = Answer::Singleton<DBService>::instance();
      DBService::updateDungeon(v6, m_connid, &logDungeon);
    }
    Player::leaveDungeon(this);
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonBuildTower(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  int32_t nId; // [rsp+10h] [rbp-30h]
  int16_t nPosX; // [rsp+14h] [rbp-2Ch]
  int16_t nPosY; // [rsp+16h] [rbp-2Ah]
  Dungeon *pDungeon; // [rsp+18h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  nPosX = Answer::NetPacket::readInt16(inPacket);
  nPosY = Answer::NetPacket::readInt16(inPacket);
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getDungeonType(v4) != 15 )
    return 10002;
  if ( Dungeon::getState(pDungeon) != DungeonState::DS_RUNNING && Dungeon::getState(pDungeon) != DungeonState::DS_WAIT )
    return 10002;
  if ( !Dungeon::BuildTower(pDungeon, this, nId, nPosX, nPosY) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, m_connid, m_cgindex, Proc, nId);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonBuyTower(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  int32_t nId; // [rsp+14h] [rbp-2Ch]
  Dungeon *pDungeon; // [rsp+18h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getDungeonType(v4) != 15 )
    return 10002;
  if ( Dungeon::getState(pDungeon) != DungeonState::DS_RUNNING && Dungeon::getState(pDungeon) != DungeonState::DS_WAIT )
    return 10002;
  if ( !Dungeon::BuyTower(pDungeon, this, nId) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, m_connid, m_cgindex, Proc, nId);
  return 0;
}


#####################################
int32_t __cdecl Player::onGuessTheSize(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  int nId; // [rsp+1Ch] [rbp-34h]
  Dungeon *pDungeon; // [rsp+20h] [rbp-30h]
  int nSize; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  if ( nId <= 0 || nId > 3 )
    return 10002;
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getDungeonType(v4) != 34 )
    return 10002;
  nSize = Dungeon::GuessTheSize(pDungeon, this, nId);
  if ( nSize <= 0 )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, m_connid, m_cgindex, Proc, nSize);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonYJSKGuWu(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  int8_t Int32; // dl
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  uint16_t v10; // r13
  int16_t v11; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  Dungeon *pDungeon; // [rsp+10h] [rbp-30h]

  if ( !inPacket )
    return 10002;
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getDungeonType(v4) != 34 )
    return 10002;
  Int32 = Answer::NetPacket::readInt32(inPacket);
  if ( Dungeon::DungeonGuWu(pDungeon, this, Int32) )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v9 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v9, m_connid, m_cgindex, Proc, 1);
  }
  else
  {
    v10 = Answer::NetPacket::getProc(inPacket);
    v11 = this->m_cgindex;
    v12 = this->m_connid;
    v13 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v13, v12, v11, v10, 0);
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonStart(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  Dungeon *pDungeon; // [rsp+18h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 )
    return 10002;
  if ( Dungeon::getState(v4) != DungeonState::DS_WAIT )
    return 10002;
  Dungeon::start(pDungeon, 0);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, m_connid, m_cgindex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonSelectReward(Player *const this, Answer::NetPacket *inPacket)
{
  const Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  int8_t index; // [rsp+14h] [rbp-2Ch]
  Dungeon *pDungeon; // [rsp+18h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  index = Answer::NetPacket::readInt32(inPacket);
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v4 = 0;
  pDungeon = (Dungeon *)v4;
  if ( !v4 || !Dungeon::IsWin(v4) )
    return 10002;
  if ( !Dungeon::GetReward(pDungeon, this, index, 0) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v9 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v9, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::onDungeonSummonBoss(Player *const this, Answer::NetPacket *inPacket)
{
  Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  int8_t nState; // [rsp+17h] [rbp-29h]

  if ( !inPacket )
    return 10002;
  nState = Answer::NetPacket::readInt8(inPacket);
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (Dungeon *)__dynamic_cast(
                      this->m_pMap,
                      (const struct __class_type_info *)&`typeinfo for'Map,
                      (const struct __class_type_info *)&`typeinfo for'Dungeon,
                      0);
  else
    v4 = 0;
  if ( !v4 )
    return 10002;
  if ( !Dungeon::SummonBoss(v4, this, nState) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, m_connid, m_cgindex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonSummon(Player *const this, Answer::NetPacket *inPacket)
{
  Dungeon *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  int32_t nIndex; // [rsp+14h] [rbp-2Ch]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  if ( !this->m_pMap || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) != 1 )
    return 10002;
  if ( this->m_pMap )
    v4 = (Dungeon *)__dynamic_cast(
                      this->m_pMap,
                      (const struct __class_type_info *)&`typeinfo for'Map,
                      (const struct __class_type_info *)&`typeinfo for'Dungeon,
                      0);
  else
    v4 = 0;
  if ( !v4 )
    return 10002;
  if ( !Dungeon::Summon(v4, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, m_connid, m_cgindex, Proc, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::onDungeonSaoDang(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v6; // rax
  int32_t nExp; // [rsp+1Ch] [rbp-44h] BYREF
  MemChrBagVector vItem; // [rsp+20h] [rbp-40h] BYREF
  int32_t nCurFloor; // [rsp+38h] [rbp-28h]
  int32_t nMaxFloor; // [rsp+3Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nCurFloor = CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37210);
  nMaxFloor = CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37211);
  if ( nCurFloor >= nMaxFloor )
    return 10002;
  std::vector<MemChrBag>::vector(&vItem);
  nExp = 0;
  Player::GetSaoDangReward(this, nCurFloor, nMaxFloor, &vItem, &nExp);
  if ( !std::vector<MemChrBag>::empty(&vItem)
    && !CExtCharBag::AddItem(&this->m_extCharBag, &vItem, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD) )
  {
    v2 = 10002;
  }
  else
  {
    if ( nExp > 0 )
      Player::addExp(this, nExp, 0, 1);
    CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 37210, nMaxFloor);
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v6 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v6, m_connid, m_cgindex, Proc, 0);
    v2 = 0;
  }
  std::vector<MemChrBag>::~vector(&vItem);
  return v2;
}


#####################################
void __cdecl Player::GetSaoDangReward(
        Player *const this,
        int32_t nCurFloor,
        int32_t nMaxFloor,
        MemChrBagVector *const vItem,
        int32_t *const nExp)
{
  int32_t v5; // ebx
  CfgData *v6; // rax
  int32_t id; // ebx
  CfgData *v8; // rax
  int8_t itemClass; // bl
  int32_t itemId; // ebx
  MemChrBag *v12; // rbx
  int32_t itemCount; // r12d
  const MemChrBag *v14; // rdx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter2; // [rsp+20h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter1; // [rsp+30h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > v20; // [rsp+40h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+50h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v22; // [rsp+60h] [rbp-30h] BYREF
  int32_t i; // [rsp+6Ch] [rbp-24h]
  const CfgDungeon *pCfgDungeon; // [rsp+70h] [rbp-20h]
  CfgDungeonReward *pReward; // [rsp+78h] [rbp-18h]

  std::vector<MemChrBag>::reserve(vItem, 5u);
  for ( i = nCurFloor; i < nMaxFloor; ++i )
  {
    v5 = i + 1;
    v6 = Answer::Singleton<CfgData>::instance();
    pCfgDungeon = CfgData::GetUpTowerDungeon(v6, v5);
    if ( pCfgDungeon )
    {
      id = pCfgDungeon->id;
      v8 = Answer::Singleton<CfgData>::instance();
      pReward = CfgData::getDungeonReward(v8, id);
      if ( pReward && pReward->exp > 0 )
        *nExp += pReward->exp;
      if ( !std::vector<MemChrBag>::empty(&pCfgDungeon->rewardItem) )
      {
        for ( iter1._M_current = std::vector<MemChrBag>::begin(&pCfgDungeon->rewardItem)._M_current;
              ;
              __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter1) )
        {
          v20._M_current = std::vector<MemChrBag>::end(&pCfgDungeon->rewardItem)._M_current;
          if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&iter1, &v20) )
            break;
          for ( iter2._M_current = std::vector<MemChrBag>::begin(vItem)._M_current;
                ;
                __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter2) )
          {
            __rhs._M_current = std::vector<MemChrBag>::end(vItem)._M_current;
            if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter2, &__rhs) )
              break;
            itemClass = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter1)->itemClass;
            if ( itemClass == __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter2)->itemClass )
            {
              itemId = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter1)->itemId;
              if ( itemId == __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter2)->itemId )
              {
                v12 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter2);
                itemCount = v12->itemCount;
                v12->itemCount = itemCount
                               + __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter1)->itemCount;
                break;
              }
            }
          }
          v22._M_current = std::vector<MemChrBag>::end(vItem)._M_current;
          if ( __gnu_cxx::operator==<MemChrBag *,std::vector<MemChrBag>>(&iter2, &v22) )
          {
            v14 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&iter1);
            std::vector<MemChrBag>::push_back(vItem, v14);
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl Player::onDungeonReset(Player *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v6; // rax

  if ( !inPacket )
    return 10002;
  if ( StaticObj::InDungeon(this) )
    return 10002;
  if ( CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 2064) )
    return 10002;
  if ( CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37210) <= 0 )
    return 10002;
  CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 2064, 1);
  CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 37210, 0);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, m_connid, m_cgindex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl Player::onEnterChargeDungeon(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t TodayPayGold; // ebx
  CfgData *v4; // rax
  int32_t ChargeDungeonId; // ebx
  int32_t nId; // [rsp+28h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  if ( StaticObj::InDungeon(this) )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  TodayPayGold = Player::GetTodayPayGold(this);
  v4 = Answer::Singleton<CfgData>::instance();
  ChargeDungeonId = CfgData::GetChargeDungeonId(v4, nId, TodayPayGold);
  if ( Player::enterDungeon(this, ChargeDungeonId, 0x12u, 0, 0, 0, 0, 0) )
    return 2;
  else
    return 0;
}


#####################################
int32_t __cdecl Player::onPickDropItem(Player *const this, Answer::NetPacket *inPacket)
{
  uint16_t v2; // r13
  int16_t v3; // r12
  int8_t v4; // bl
  GameService *v5; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v11; // rax
  uint16_t v12; // r13
  int16_t v13; // r12
  int8_t v14; // bl
  GameService *v15; // rax
  uint16_t v16; // r13
  int16_t v17; // r12
  int8_t v18; // bl
  GameService *v19; // rax
  int32_t v20; // eax
  uint16_t v21; // r13
  int16_t v22; // r12
  int8_t v23; // bl
  GameService *v24; // rax
  uint16_t v25; // r13
  int16_t v26; // r12
  int8_t v27; // bl
  GameService *v28; // rax
  EntityId_t dropid; // [rsp+10h] [rbp-40h]
  int64_t CurTick; // [rsp+18h] [rbp-38h]
  CDropItem *pDropItem; // [rsp+20h] [rbp-30h]
  int32_t err; // [rsp+2Ch] [rbp-24h]

  if ( inPacket )
  {
    if ( !this->m_pMap || !Unit::isAlive(this) )
    {
      Proc = Answer::NetPacket::getProc(inPacket);
      m_cgindex = this->m_cgindex;
      m_connid = this->m_connid;
      v11 = Answer::Singleton<GameService>::instance();
      GameService::replyfailure(v11, m_connid, m_cgindex, Proc, 0, 0);
      return 10002;
    }
    else
    {
      dropid = Answer::NetPacket::readInt64(inPacket);
      CurTick = Unit::getTick(this);
      if ( CurTick - this->m_LastPickTick <= 299 )
      {
        v12 = Answer::NetPacket::getProc(inPacket);
        v13 = this->m_cgindex;
        v14 = this->m_connid;
        v15 = Answer::Singleton<GameService>::instance();
        GameService::replyfailure(v15, v14, v13, v12, 1, dropid);
        return 10002;
      }
      else
      {
        this->m_LastPickTick = CurTick;
        pDropItem = Map::getDropItem(this->m_pMap, dropid);
        if ( pDropItem )
        {
          v20 = CDropItem::pick(pDropItem, this);
          err = v20;
          if ( v20 )
          {
            v25 = Answer::NetPacket::getProc(inPacket);
            v26 = this->m_cgindex;
            v27 = this->m_connid;
            v28 = Answer::Singleton<GameService>::instance();
            GameService::replyfailure(v28, v27, v26, v25, 3, dropid);
          }
          else
          {
            v21 = Answer::NetPacket::getProc(inPacket);
            v22 = this->m_cgindex;
            v23 = this->m_connid;
            v24 = Answer::Singleton<GameService>::instance();
            GameService::replySuccess(v24, v23, v22, v21, dropid);
          }
          return err;
        }
        else
        {
          v16 = Answer::NetPacket::getProc(inPacket);
          v17 = this->m_cgindex;
          v18 = this->m_connid;
          v19 = Answer::Singleton<GameService>::instance();
          GameService::replyfailure(v19, v18, v17, v16, 2, dropid);
          return 10002;
        }
      }
    }
  }
  else
  {
    v2 = Answer::NetPacket::getProc(0);
    v3 = this->m_cgindex;
    v4 = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    GameService::replyfailure(v5, v4, v3, v2, 0, 0);
    return 10002;
  }
}


#####################################
int32_t __cdecl Player::onUseTrap(Player *const this, Answer::NetPacket *inPacket)
{
  int64_t id; // [rsp+10h] [rbp-10h]
  Trap *trap; // [rsp+18h] [rbp-8h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  id = Answer::NetPacket::readInt64(inPacket);
  trap = Map::getTrap(this->m_pMap, id);
  if ( trap )
    return Trap::onUse(trap, this);
  else
    return 10002;
}


#####################################
int32_t __cdecl Player::onSwitchPkMode(Player *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int pkMode; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  pkMode = Answer::NetPacket::readInt32(inPacket);
  if ( (*((int (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this) <= 69 )
    return 10002;
  if ( pkMode == 2 && !Player::IsInTeam(this) )
    return 10002;
  if ( pkMode == 3 && Player::getFamilyId(this) <= 0 )
    return 10002;
  if ( pkMode == 5 )
  {
    v3 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v3) != 9 )
      return 10002;
  }
  if ( !(*((unsigned int (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 5))(this->m_pMap) && pkMode > 0 && pkMode <= 7 )
  {
    if ( pkMode != 1 )
      this->m_chr.pk_time = 0;
    Player::setPkMode(this, pkMode, 1);
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v7, m_connid, m_cgindex, Proc, pkMode);
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onSafeRevive(Player *const this, Answer::NetPacket *inPacket)
{
  CharLittlerHelper *CharLittlerHelper; // rax
  int32_t Now; // ebx
  CharLittlerHelper *v6; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v10; // rax

  if ( !inPacket )
    return 10002;
  if ( StaticObj::InDungeon(this) )
  {
    if ( this->m_pMap )
    {
      (*((void (__fastcall **)(Map *, Player *const))this->m_pMap->_vptr_Map + 21))(this->m_pMap, this);
      if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 22))(this->m_pMap) )
      {
        CharLittlerHelper = Player::GetCharLittlerHelper(this);
        CharLittlerHelper::OnAutoWork(CharLittlerHelper);
      }
    }
    return 0;
  }
  else
  {
    Now = Unit::getNow(this);
    if ( Now >= CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 1111) )
    {
      Player::safeRevive(this);
      if ( this->m_pMap && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 22))(this->m_pMap) )
      {
        v6 = Player::GetCharLittlerHelper(this);
        CharLittlerHelper::OnAutoWork(v6);
      }
      Proc = Answer::NetPacket::getProc(inPacket);
      m_cgindex = this->m_cgindex;
      m_connid = this->m_connid;
      v10 = Answer::Singleton<GameService>::instance();
      return GameService::replySuccess(v10, m_connid, m_cgindex, Proc, 0);
    }
    else
    {
      return 10002;
    }
  }
}


#####################################
void __cdecl Player::SafeToPrison(Player *const this)
{
  CfgData *v1; // rax
  int32_t mapid; // ebx
  MapManager *v3; // rax
  Position pos; // [rsp+10h] [rbp-30h]
  CfgMapRegion *pCfgRegion; // [rsp+20h] [rbp-20h]
  Map *pTempMap; // [rsp+28h] [rbp-18h]

  v1 = Answer::Singleton<CfgData>::instance();
  pCfgRegion = CfgData::getMapRegion(v1, 20032);
  if ( pCfgRegion )
  {
    mapid = pCfgRegion->mapid;
    v3 = Answer::Singleton<MapManager>::instance();
    pTempMap = MapManager::GetMap(v3, mapid);
    if ( pTempMap )
    {
      pos = Map::getRandomWalkablePositionInRegion(pTempMap, pCfgRegion);
      if ( pos.x >= 0 && pos.y >= 0 )
      {
        if ( this->m_pMap == pTempMap )
          Unit::instantMove(this, pos.x, pos.y, InstanceMoveReason::IMR_TRANSFER, 0);
        else
          Player::switchMap(this, pTempMap, pos.x, pos.y, 1);
      }
    }
  }
}


#####################################
int32_t __cdecl Player::onSiteRevive(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  CVip *PlayerVip; // rax
  CExtOperateLimit *OperateLimit; // rax
  int v10; // r12d
  int32_t Now; // edx
  CharLittlerHelper *CharLittlerHelper; // rax
  uint16_t v13; // r13
  int16_t v14; // r12
  int8_t v15; // bl
  GameService *v16; // rax
  int32_t Slot; // [rsp+1Ch] [rbp-54h] BYREF
  ItemData data; // [rsp+20h] [rbp-50h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-40h] BYREF

  if ( !inPacket || !this->m_pMap )
    return 10002;
  if ( Unit::isAlive(this) )
    return 10002;
  if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 9))(this->m_pMap) != 1
    && Map::GetMapId(this->m_pMap) != 50129 )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v7, m_connid, m_cgindex, Proc, 10061, 0);
  }
  if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 10))(this->m_pMap) )
  {
    if ( (*((unsigned __int8 (__fastcall **)(Map *, Player *const))this->m_pMap->_vptr_Map + 20))(this->m_pMap, this) != 1 )
      return 10002;
    goto LABEL_22;
  }
  PlayerVip = Player::GetPlayerVip(this);
  if ( CVip::CanSiteRevive(PlayerVip) )
  {
    OperateLimit = Player::GetOperateLimit(this);
    CExtOperateLimit::AddLimitCount(OperateLimit, 2021, 1);
LABEL_22:
    (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
    Player::SetDieTick(this);
    Unit::FillMP(this, 100);
    Now = Unit::getNow(this);
    Player::SetStartProtect(this, Now);
    (*((void (__fastcall **)(Player *const))this->_vptr_Entity + 30))(this);
    Unit::setNeedSyncSelf(this);
    (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 12))(this->m_pMap, this, 0);
    if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 22))(this->m_pMap) )
    {
      CharLittlerHelper = Player::GetCharLittlerHelper(this);
      CharLittlerHelper::OnAutoWork(CharLittlerHelper);
    }
    v13 = Answer::NetPacket::getProc(inPacket);
    v14 = this->m_cgindex;
    v15 = this->m_connid;
    v16 = Answer::Singleton<GameService>::instance();
    return GameService::replySuccess(v16, v15, v14, v13, 0);
  }
  std::vector<int>::vector(&vSlot);
  *(_QWORD *)&data.m_nId = 0;
  data.m_nCount = 0;
  Slot = Answer::NetPacket::readInt32(inPacket);
  std::vector<int>::push_back(&vSlot, &Slot);
  data.m_nId = 9;
  data.m_nClass = 1;
  data.m_nCount = 1;
  if ( !CExtCharBag::RemoveItem(&this->m_extCharBag, &vSlot, &data, ITEM_CHANGE_REASON::ICR_SITE_REVIVE)
    && !Player::DecCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, 100, CURRENCY_CHANGE_REASON::GCT_LI_JI_FU_HUO, 0) )
  {
    v2 = 10002;
    v10 = 0;
  }
  else
  {
    v10 = 1;
  }
  std::vector<int>::~vector(&vSlot);
  if ( v10 )
    goto LABEL_22;
  return v2;
}


#####################################
int32_t __cdecl Player::onStrongRevive(Player *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( Unit::isAlive(this) )
    return 10002;
  (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
  Player::SetDieTick(this);
  Unit::FillMP(this, 100);
  Unit::setNeedSyncSelf(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onQueryChrInfo(Player *const this, Answer::NetPacket *inPacket)
{
  Unit::setNeedSyncSelf(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onUpgradeLevel(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // edx
  int32_t OldLevel; // [rsp+1Ch] [rbp-4h]

  OldLevel = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  if ( Player::upgradeLevel(this, 0) )
  {
    v2 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
    Player::LevelUped(this, OldLevel, v2);
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onQueryTaskList(Player *const this, Answer::NetPacket *inPacket)
{
  ChrTask::sendTaskList(&this->m_task);
  return 0;
}


#####################################
int32_t __cdecl Player::onReceiveTask(Player *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v6; // rax
  int32_t tid; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  tid = Answer::NetPacket::readInt32(inPacket);
  if ( !ChrTask::receive(&this->m_task, tid) )
    return 0;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v6 = Answer::Singleton<GameService>::instance();
  return GameService::replyfailure(v6, m_connid, m_cgindex, Proc, 10070, tid);
}


#####################################
int32_t __cdecl Player::onSubmitTask(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CVip *PlayerVip; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  CVip *v9; // rax
  int32_t tid; // [rsp+10h] [rbp-40h]
  char bDouble; // [rsp+17h] [rbp-39h]
  CfgTask *cfgTask; // [rsp+18h] [rbp-38h]
  int32_t nTimes; // [rsp+24h] [rbp-2Ch]
  float Rate; // [rsp+28h] [rbp-28h]
  float Rate_0; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  tid = Answer::NetPacket::readInt32(inPacket);
  bDouble = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v3, tid);
  if ( !cfgTask )
    return 10002;
  nTimes = 1;
  if ( bDouble > 0 )
  {
    Rate = 1.0;
    PlayerVip = Player::GetPlayerVip(this);
    if ( CVip::GetVipFlg(PlayerVip, 2) )
      Rate = 0.80000001;
    if ( Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD) < (int)(float)((float)cfgTask->Double * Rate) )
      return 10002;
    nTimes = 2;
  }
  if ( ChrTask::submit(&this->m_task, tid, nTimes) )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v8, m_connid, m_cgindex, Proc, 10070, tid);
  }
  else
  {
    if ( bDouble > 0 && cfgTask->Double > 0 )
    {
      Rate_0 = 1.0;
      v9 = Player::GetPlayerVip(this);
      if ( CVip::GetVipFlg(v9, 2) )
        Rate_0 = 0.80000001;
      Player::DecCurrency(
        this,
        CURRENCY_TYPE::CURRENCY_GOLD,
        (int)(float)((float)cfgTask->Double * Rate_0),
        CURRENCY_CHANGE_REASON::GCR_TASK_DOUBLE_REWARD,
        0);
    }
    return 0;
  }
}


#####################################
int32_t __cdecl Player::onGiveUpTask(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t tid; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  tid = Answer::NetPacket::readInt32(inPacket);
  return ChrTask::giveUp(&this->m_task, tid);
}


#####################################
int32_t __cdecl Player::onSetTaskCanSubmit(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t tid; // [rsp+14h] [rbp-Ch]
  CfgTask *pCfgTask; // [rsp+18h] [rbp-8h]

  if ( !inPacket )
    return 10002;
  tid = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgTask = CfgData::getTask(v3, tid);
  if ( !pCfgTask || pCfgTask->condition != 12 )
    return 10002;
  Player::setTaskCanSubmit(this, tid);
  return 0;
}


#####################################
int32_t __cdecl Player::onTalkWithNpc(Player *const this, Answer::NetPacket *inPacket)
{
  Position pos; // [rsp+10h] [rbp-30h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-20h] BYREF
  EntityId_t npcid; // [rsp+30h] [rbp-10h]
  Npc *npc; // [rsp+38h] [rbp-8h]

  if ( !this->m_pMap || !inPacket )
    return 10002;
  npcid = Answer::NetPacket::readInt64(inPacket);
  npc = Map::getNpc(this->m_pMap, npcid);
  if ( !npc )
    return 10002;
  pos = StaticObj::getCurrentTile(this);
  CurrentTile = StaticObj::getCurrentTile(npc);
  if ( Position::tileDistance(&CurrentTile, &pos) > 3 )
    return 10002;
  (*((void (__fastcall **)(Npc *, Player *const))npc->_vptr_Entity + 34))(npc, this);
  return 0;
}


#####################################
int32_t __cdecl Player::onQuickDone(Player *const this, Answer::NetPacket *inPacket)
{
  if ( inPacket )
  {
    Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readInt32(inPacket);
  }
  return 10002;
}


#####################################
int32_t __cdecl Player::onTeleport(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t Int32; // edx

  if ( !inPacket )
    return 10002;
  Int32 = Answer::NetPacket::readInt32(inPacket);
  return Player::doTeleport(this, Int32);
}


#####################################
int32_t __cdecl Player::onTeleportActivity(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t Int32; // edx

  if ( !inPacket )
    return 10002;
  Int32 = Answer::NetPacket::readInt32(inPacket);
  return Player::doTeleportActivity(this, Int32);
}


#####################################
int32_t __cdecl Player::onAddAction(Player *const this, Answer::NetPacket *inPacket)
{
  int slot; // [rsp+14h] [rbp-Ch]
  int32_t id; // [rsp+18h] [rbp-8h]
  int32_t type; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  slot = Answer::NetPacket::readInt32(inPacket);
  id = Answer::NetPacket::readInt32(inPacket);
  type = Answer::NetPacket::readInt32(inPacket);
  if ( slot <= 0 || slot > 10 )
    return 10002;
  *((_DWORD *)&this->m_task.m_taskMonsters._M_impl + 2 * slot + 4) = id;
  *((_DWORD *)&this->m_task.m_taskMonsters._M_impl + 2 * slot + 5) = type;
  Player::sendActionList(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onRemoveAction(Player *const this, Answer::NetPacket *inPacket)
{
  int slot; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  slot = Answer::NetPacket::readInt32(inPacket);
  if ( slot <= 0 || slot > 10 )
    return 10002;
  *((_QWORD *)&this->m_task.m_taskMonsters._M_impl + slot + 2) = 0;
  Player::sendActionList(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onExchangeAction(Player *const this, Answer::NetPacket *inPacket)
{
  int oldslot; // [rsp+18h] [rbp-8h]
  int newslot; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  oldslot = Answer::NetPacket::readInt32(inPacket);
  newslot = Answer::NetPacket::readInt32(inPacket);
  if ( oldslot <= 0 || oldslot > 10 || newslot <= 0 || newslot > 10 )
    return 10002;
  std::swap<MemChrAction>(
    (MemChrAction *const)&this->m_task.m_taskMonsters._M_impl + oldslot + 2,
    (MemChrAction *const)&this->m_task.m_taskMonsters._M_impl + newslot + 2);
  Player::sendActionList(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onSetAutoFight(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  const char *v3; // rax
  const char *v4; // rax
  std::string pick; // [rsp+10h] [rbp-40h] BYREF
  std::string fight; // [rsp+20h] [rbp-30h] BYREF
  std::string p_PickString; // [rsp+30h] [rbp-20h] BYREF

  if ( !inPacket )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&fight, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&pick, (bool)inPacket);
  v3 = (const char *)std::string::c_str(&fight);
  snprintf(this->m_autoFight.fight, 0x258u, v3);
  v4 = (const char *)std::string::c_str(&pick);
  snprintf(this->m_autoFight.pick, 0x258u, v4);
  Player::sendAutoFight(this);
  std::string::string(&p_PickString, &fight);
  CharLittlerHelper::parsePickString(&this->m_CharLittlerhelper, &p_PickString);
  std::string::~string(&p_PickString);
  v2 = 0;
  std::string::~string(&pick);
  std::string::~string(&fight);
  return v2;
}


#####################################
int32_t __cdecl Player::onSetSystemSetting(Player *const this, Answer::NetPacket *inPacket)
{
  int *v3; // rax
  int32_t Key; // [rsp+18h] [rbp-8h] BYREF
  int32_t Values; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  Key = Answer::NetPacket::readInt32(inPacket);
  Values = Answer::NetPacket::readInt32(inPacket);
  v3 = std::map<int,int>::operator[](&this->m_SystemSetting, &Key);
  *v3 = Values;
  if ( Key == 2 || Key == 3 )
    CExtCharTeam::UpdateTeamSetting(&this->m_extCharTeam);
  return 0;
}


#####################################
int32_t __cdecl Player::onBuyBackChrShopItem(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t index; // [rsp+14h] [rbp-1Ch]
  int32_t itemID; // [rsp+18h] [rbp-18h]
  int8_t itemClass; // [rsp+1Fh] [rbp-11h]

  index = Answer::NetPacket::readInt32(inPacket);
  itemID = Answer::NetPacket::readInt32(inPacket);
  itemClass = Answer::NetPacket::readInt8(inPacket);
  return CExtCharBag::buyBackChrShopItem(&this->m_extCharBag, index, itemID, itemClass);
}


#####################################
int32_t __cdecl Player::onBuyTaskCount(Player *const this, Answer::NetPacket *inPacket)
{
  if ( inPacket )
    return 0;
  else
    return 10002;
}


#####################################
int32_t __cdecl Player::onBuyResource(Player *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readInt32(inPacket);
  return 0;
}


#####################################
int32_t __cdecl Player::onBuyChrShopItem(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t id; // [rsp+18h] [rbp-38h]
  int count; // [rsp+1Ch] [rbp-34h]
  CfgChrShop *pCharShop; // [rsp+20h] [rbp-30h]
  int32_t err; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  id = Answer::NetPacket::readInt32(inPacket);
  count = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCharShop = CfgData::getChrShop(v3, id);
  if ( !pCharShop )
    return 10002;
  if ( count <= 0 )
    return 10002;
  err = CExtCharBag::buyChrShopItem(&this->m_extCharBag, pCharShop, id, count);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  if ( err )
    GameService::replyfailure(v7, m_connid, m_cgindex, Proc, err, id);
  else
    GameService::replySuccess(v7, m_connid, m_cgindex, Proc, id);
  return err;
}


#####################################
int32_t __cdecl Player::onGamePublicChat(Player *const this, Answer::NetPacket *inPacket)
{
  CActivityMap *v3; // rax
  CharId_t Cid; // rbx
  CGMBackstate *v6; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v10; // rax
  int32_t v11; // ebx
  int32_t v12; // ebx
  CfgData *v13; // rax
  CExtCharBag *Bag; // rax
  GameService *v15; // rax
  ItemData Item; // [rsp+10h] [rbp-50h] BYREF
  int32_t nBanChatTime; // [rsp+1Ch] [rbp-44h]
  int32_t nNowTime; // [rsp+20h] [rbp-40h]
  int32_t channel; // [rsp+24h] [rbp-3Ch]
  CActivityMap *pActMap; // [rsp+28h] [rbp-38h]
  CActivity *pActivity; // [rsp+30h] [rbp-30h]
  int32_t nLimitTimes; // [rsp+38h] [rbp-28h]
  int32_t nChatTimes; // [rsp+3Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  if ( StaticObj::InActivity(this) )
  {
    v3 = this->m_pMap
       ? (CActivityMap *)__dynamic_cast(
                           this->m_pMap,
                           (const struct __class_type_info *)&`typeinfo for'Map,
                           (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                           0)
       : 0LL;
    pActMap = v3;
    if ( v3 )
    {
      pActivity = CActivityMap::GetActivity(pActMap);
      if ( pActivity && CActivity::GetType(pActivity) == 13 )
        return 10002;
    }
  }
  Cid = Player::getCid(this);
  v6 = Answer::Singleton<CGMBackstate>::instance();
  nBanChatTime = CGMBackstate::GetBanChatLeftTime(v6, Cid);
  if ( nBanChatTime > 0 )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v10 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v10, m_connid, m_cgindex, Proc, 10040, nBanChatTime);
  }
  nNowTime = Unit::getNow(this);
  channel = Answer::NetPacket::readInt32(inPacket);
  if ( Player::GetGMLevel(this) <= 1 )
  {
    if ( CVip::GetVipLevel(&this->m_PlayerVip) <= 1 )
    {
      v11 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
      if ( v11 < Player::GetChatLevel(this) )
        return 10002;
    }
    if ( nNowTime - Player::getRecord(this, 1009) <= 3 )
      return 10002;
    Player::updateRecord(this, 1009, nNowTime);
    if ( channel == 1 || channel == 5 )
    {
      v12 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
      v13 = Answer::Singleton<CfgData>::instance();
      nLimitTimes = CfgData::GetChatTimes(v13, v12);
      if ( nLimitTimes > 0 )
      {
        nChatTimes = Player::getRecord(this, 2045);
        if ( nChatTimes >= nLimitTimes )
          return 10002;
        Player::updateRecord(this, 2045, ++nChatTimes);
      }
    }
  }
  if ( channel == 6 )
  {
    *(_QWORD *)&Item.m_nId = 0x100000008LL;
    Item.m_nCount = 1;
    Bag = Player::GetBag(this);
    if ( !CExtCharBag::RemoveItem(Bag, &Item, ITEM_CHANGE_REASON::ICR_BAG_USE) )
      return 10002;
  }
  if ( channel == 7 )
  {
    v15 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v15) != 9 )
      return 10002;
  }
  Player::sendPublicChat(this, channel, inPacket);
  return 0;
}


#####################################
int32_t __cdecl Player::onCrossPrivateChat(Player *const this, Answer::NetPacket *inPacket)
{
  CharId_t v3; // rbx
  CGMBackstate *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  int32_t RunnerId; // r12d
  GameService *v10; // rax
  uint16_t v11; // r13
  int16_t v12; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  int32_t v15; // ebx
  int8_t ConnId; // bl
  GameService *v17; // rax
  int32_t v18; // eax
  CharId_t v19; // rax
  int32_t Sid; // eax
  int8_t VipType; // al
  int8_t VipLevel; // al
  Sex_t Sex; // al
  GameService *v24; // rax
  int8_t Line; // al
  Job_t Job; // al
  int8_t JueWei; // al
  CharId_t v28; // rax
  int32_t v29; // eax
  uint32_t Size; // ebx
  char *Buffer; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  GameService *v34; // rax
  CharId_t v35; // rdx
  Player *chater[2]; // [rsp+10h] [rbp-A0h]
  std::string val; // [rsp+20h] [rbp-90h] BYREF
  std::string v38; // [rsp+30h] [rbp-80h] BYREF
  std::string v39; // [rsp+40h] [rbp-70h] BYREF
  std::string v40; // [rsp+50h] [rbp-60h] BYREF
  std::string v41; // [rsp+60h] [rbp-50h] BYREF
  int32_t nBanChatTime; // [rsp+6Ch] [rbp-44h]
  CharId_t cid; // [rsp+70h] [rbp-40h]
  Player *player; // [rsp+78h] [rbp-38h]
  int32_t nNowTime; // [rsp+80h] [rbp-30h]
  int32_t i; // [rsp+84h] [rbp-2Ch]
  Answer::NetPacket *chatPacket; // [rsp+88h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  v3 = Player::getCid(this);
  v4 = Answer::Singleton<CGMBackstate>::instance();
  nBanChatTime = CGMBackstate::GetBanChatLeftTime(v4, v3);
  if ( nBanChatTime > 0 )
  {
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v8, m_connid, m_cgindex, Proc, 10040, nBanChatTime);
  }
  cid = Answer::NetPacket::readInt64(inPacket);
  RunnerId = StaticObj::GetRunnerId(this);
  v10 = Answer::Singleton<GameService>::instance();
  player = GameService::getPlayer(v10, cid, RunnerId, 1);
  if ( !player )
  {
    v11 = Answer::NetPacket::getProc(inPacket);
    v12 = this->m_cgindex;
    v13 = this->m_connid;
    v14 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v14, v13, v12, v11, 10051, 0);
  }
  if ( Player::GetGMLevel(this) <= 1 )
  {
    if ( CVip::GetVipLevel(&this->m_PlayerVip) <= 1 )
    {
      v15 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
      if ( v15 < Player::GetChatLevel(this) )
        return 10002;
    }
    nNowTime = Unit::getNow(this);
    if ( nNowTime - Player::getRecord(this, 1009) <= 4 )
      return 10002;
    Player::updateRecord(this, 1009, nNowTime);
  }
  chater[0] = this;
  chater[1] = player;
  for ( i = 0; i <= 1; ++i )
  {
    ConnId = Player::getConnId(chater[i]);
    v17 = Answer::Singleton<GameService>::instance();
    chatPacket = GameService::popNetpacket(v17, ConnId, Answer::PackType::PACK_DISPATCH, 0x27C6u);
    if ( chatPacket )
    {
      v18 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
      Answer::NetPacket::writeInt32(chatPacket, v18);
      Answer::NetPacket::writeInt8(chatPacket, this->m_sysUser.gm_level);
      v19 = Player::getCid(this);
      Answer::NetPacket::writeInt64(chatPacket, v19);
      Sid = Player::getSid(this);
      Answer::NetPacket::writeInt32(chatPacket, Sid);
      Player::GetPassport((Player *const)&val);
      Answer::NetPacket::writeUTF8(chatPacket, &val);
      std::string::~string(&val);
      Player::getIP((Player *const)&v38);
      Answer::NetPacket::writeUTF8(chatPacket, &v38);
      std::string::~string(&v38);
      VipType = CVip::GetVipType(&this->m_PlayerVip);
      Answer::NetPacket::writeInt8(chatPacket, VipType);
      VipLevel = CVip::GetVipLevel(&this->m_PlayerVip);
      Answer::NetPacket::writeInt8(chatPacket, VipLevel);
      Sex = Player::getSex(this);
      Answer::NetPacket::writeInt8(chatPacket, Sex);
      v24 = Answer::Singleton<GameService>::instance();
      Line = GameService::getLine(v24);
      Answer::NetPacket::writeInt8(chatPacket, Line);
      Player::getName((const Player *const)&v39);
      Answer::NetPacket::writeUTF8(chatPacket, &v39);
      std::string::~string(&v39);
      Job = Player::getJob(this);
      Answer::NetPacket::writeInt8(chatPacket, Job);
      JueWei = CExtCharJueWei::GetJueWei(&this->m_extCharJueWei);
      Answer::NetPacket::writeInt8(chatPacket, JueWei);
      CExtCharTencent::AppendInfo(&this->m_extCharTencent, chatPacket);
      CVplan::AppendYYInfo(&this->m_Vplan, chatPacket);
      CVplan::AppendSwVipInfo(&this->m_Vplan, chatPacket);
      Answer::NetPacket::writeInt8(chatPacket, this->m_connid);
      v28 = Player::getCid(player);
      Answer::NetPacket::writeInt64(chatPacket, v28);
      v29 = Player::getSid(player);
      Answer::NetPacket::writeInt32(chatPacket, v29);
      Player::getName((const Player *const)&v40);
      Answer::NetPacket::writeUTF8(chatPacket, &v40);
      std::string::~string(&v40);
      Player::GetPassport((Player *const)&v41);
      Answer::NetPacket::writeUTF8(chatPacket, &v41);
      std::string::~string(&v41);
      Size = Answer::NetPacket::getSize(inPacket);
      Buffer = Answer::NetPacket::getBuffer(inPacket);
      Answer::NetPacket::write(chatPacket, Buffer, Size);
      WOffset = Answer::NetPacket::getWOffset(chatPacket);
      Answer::NetPacket::setSize(chatPacket, WOffset);
      GateIndex = Player::getGateIndex(chater[i]);
      LOBYTE(Size) = Player::getConnId(chater[i]);
      v34 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v34, Size, GateIndex, chatPacket);
    }
  }
  v35 = Player::getCid(player);
  Player::onSendSocialData(this, v35);
  return 0;
}


#####################################
int32_t __cdecl Player::GetChatLevel(Player *const this)
{
  CfgData *v1; // rax
  int32_t ServerDiffDay; // eax
  int32_t Day; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  ServerDiffDay = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
  Day = ServerDiffDay + 1;
  if ( !ServerDiffDay )
    return 230;
  if ( ServerDiffDay == 1 )
    return 240;
  if ( Day <= 7 )
    return 250;
  if ( Day <= 15 )
    return 280;
  if ( Day <= 30 )
    return 301;
  if ( Day > 60 )
    return 330;
  return 320;
}


#####################################
void __cdecl Player::onSendSocialData(Player *const this, CharId_t cid)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *Packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this);
  v3 = Answer::Singleton<GameService>::instance();
  Packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EBBu);
  if ( Packet )
  {
    GateIndex = Player::getGateIndex(this);
    Answer::NetPacket::writeInt32(Packet, GateIndex);
    Answer::NetPacket::writeInt64(Packet, cid);
    WOffset = Answer::NetPacket::getWOffset(Packet);
    Answer::NetPacket::setSize(Packet, WOffset);
    v6 = Player::getConnId(this);
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v7, v6, Packet);
  }
}


#####################################
int32_t __cdecl Player::onUpdateFlyIconInt(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t Int32; // edx

  if ( !inPacket )
    return 10002;
  Int32 = Answer::NetPacket::readInt32(inPacket);
  Player::updateRecord(this, 1013, Int32);
  return 0;
}


#####################################
int32_t __cdecl Player::onSetGuaJi(Player *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  this->m_nGuaJi = Answer::NetPacket::readInt8(inPacket);
  return 0;
}


#####################################
int32_t __cdecl Player::onQueryKillerRankSelf(Player *const this, Answer::NetPacket *inPacket)
{
  Player::sendKillerRankSelf(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onTeleportByItem(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v5; // rax
  MapManager *v6; // rax
  int64_t v7; // r13
  int16_t v8; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  bool v11; // al
  char v12; // al
  CSpecialEquip *CSpecialEquip; // rax
  int v14; // r12d
  int64_t v15; // r14
  uint16_t Proc; // r13
  int16_t v17; // r12
  int8_t v18; // bl
  GameService *v19; // rax
  ItemData data; // [rsp+10h] [rbp-80h] BYREF
  Int32Vector vSlot; // [rsp+20h] [rbp-70h] BYREF
  Position finalPos; // [rsp+40h] [rbp-50h]
  int32_t targetkingdom; // [rsp+48h] [rbp-48h]
  int32_t mapid; // [rsp+4Ch] [rbp-44h]
  int32_t mapx; // [rsp+50h] [rbp-40h]
  int32_t mapy; // [rsp+54h] [rbp-3Ch]
  int32_t taskid; // [rsp+58h] [rbp-38h]
  int32_t ProcId; // [rsp+5Ch] [rbp-34h]
  Map *pTargetMap; // [rsp+60h] [rbp-30h]
  int32_t err; // [rsp+6Ch] [rbp-24h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  targetkingdom = Answer::NetPacket::readInt32(inPacket);
  mapid = Answer::NetPacket::readInt32(inPacket);
  mapx = Answer::NetPacket::readInt32(inPacket);
  mapy = Answer::NetPacket::readInt32(inPacket);
  taskid = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readInt32(inPacket);
  ProcId = Answer::NetPacket::getProc(inPacket);
  Player::LogProc(this, ProcId);
  if ( Player::IsInStall(this) )
    return 10002;
  if ( StaticObj::InActivity(this) )
  {
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v5, m_connid, m_cgindex, 0x10u, 10089, 0);
  }
  else if ( StaticObj::getMapId(this) == mapid
         && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 24))(this->m_pMap) != 1 )
  {
    return 2;
  }
  else
  {
    v6 = Answer::Singleton<MapManager>::instance();
    pTargetMap = MapManager::GetMap(v6, mapid);
    if ( pTargetMap )
    {
      if ( Map::IsSpecialBossMap(pTargetMap) )
      {
        return 10002;
      }
      else if ( Map::IsXinMoMap(this->m_pMap) )
      {
        return 10002;
      }
      else
      {
        finalPos = Map::getRandomWalkableAroundPosition(pTargetMap, mapx, mapy);
        if ( finalPos.x >= 0 && finalPos.y >= 0 )
        {
          if ( !Map::isWalkablePosition(pTargetMap, finalPos.x, finalPos.y) )
          {
            return 10002;
          }
          else
          {
            err = (*((__int64 (__fastcall **)(Map *, Player *const))pTargetMap->_vptr_Map + 4))(pTargetMap, this);
            if ( err )
            {
              v7 = Map::GetMapId(pTargetMap);
              v8 = this->m_cgindex;
              v9 = this->m_connid;
              v10 = Answer::Singleton<GameService>::instance();
              return GameService::replyfailure(v10, v9, v8, 0x10u, err, v7);
            }
            else
            {
              v11 = (*((unsigned __int8 (__fastcall **)(Map *))pTargetMap->_vptr_Map + 17))(pTargetMap)
                 || (*((unsigned __int8 (__fastcall **)(Map *))pTargetMap->_vptr_Map + 18))(pTargetMap);
              if ( v11
                || (!Map::IsKuangDong(pTargetMap)
                 || (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 19))(this->m_pMap) == 1
                  ? (v12 = 0)
                  : (v12 = 1),
                    v12) )
              {
                Player::TiShiInfo(this, 6, 0);
                return 10002;
              }
              else
              {
                CSpecialEquip = Player::GetCSpecialEquip(this);
                if ( CSpecialEquip::IsActivation(CSpecialEquip, 1) )
                  goto LABEL_42;
                std::vector<int>::vector(&vSlot);
                *(_QWORD *)&data.m_nId = 0;
                data.m_nCount = 0;
                Player::queryBagInfo(this, inPacket, &vSlot);
                if ( Player::verifyBagInfo(this, &vSlot, 34, 1) )
                {
                  v2 = 10002;
                  v14 = 0;
                }
                else
                {
                  data.m_nId = 34;
                  data.m_nClass = 1;
                  data.m_nCount = 1;
                  if ( !CExtCharBag::RemoveItem(
                          &this->m_extCharBag,
                          &vSlot,
                          &data,
                          ITEM_CHANGE_REASON::ICR_TELEPORT_BY_ITEM) )
                  {
                    v2 = 10002;
                    v14 = 0;
                  }
                  else
                  {
                    v14 = 1;
                  }
                }
                std::vector<int>::~vector(&vSlot);
                if ( v14 )
                {
LABEL_42:
                  if ( this->m_pMap == pTargetMap )
                  {
                    Unit::instantMove(this, finalPos.x, finalPos.y, InstanceMoveReason::IMR_TRANSFER, 0);
                  }
                  else if ( Player::switchMap(this, pTargetMap, finalPos.x, finalPos.y, 1) )
                  {
                    return 10002;
                  }
                  v15 = taskid;
                  Proc = Answer::NetPacket::getProc(inPacket);
                  v17 = this->m_cgindex;
                  v18 = this->m_connid;
                  v19 = Answer::Singleton<GameService>::instance();
                  return GameService::replySuccess(v19, v18, v17, Proc, v15);
                }
              }
            }
          }
        }
        else
        {
          return 10002;
        }
      }
    }
    else
    {
      return 10002;
    }
  }
  return v2;
}


#####################################
int32_t __cdecl Player::onClickPayButton(Player *const this, Answer::NetPacket *inPacket)
{
  ++this->m_chr.pay_click_count;
  return 0;
}


#####################################
int32_t __cdecl Player::onMapEntered(Player *const this, Answer::NetPacket *inPacket)
{
  this->m_sysUser.map_enter_time = Unit::getNow(this);
  return 0;
}


#####################################
int32_t __cdecl Player::onDebugCmd(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CfgData *v4; // rax
  MapManager *v5; // rax
  Map *Map; // rbx
  CfgData *v7; // rax
  const LuckDropTable *LuckDropTableTable; // rbx
  FamilyId_t FamilyId; // rbx
  MapManager *v10; // rax
  FamilyId_t v11; // rbx
  MapManager *v12; // rax
  int64_t TerritoryId; // rax
  int32_t RunnerId; // ebx
  MapManager *v15; // rax
  GameService *v16; // rax
  int32_t Int32; // edx
  int32_t v18; // r12d
  int v19; // r12d
  const char *v20; // rax
  int v21; // r12d
  int v22; // r12d
  int32_t v23; // r12d
  int v24; // r12d
  const char *v25; // rax
  int v26; // r12d
  int v27; // r12d
  const char *v28; // rax
  int v29; // ebx
  CfgData *v30; // rax
  const KunLingTable *KunLingTable; // rax
  MemChrBag slotData; // [rsp+20h] [rbp-210h] BYREF
  std::string ststemTimeLinux_1; // [rsp+40h] [rbp-1F0h] BYREF
  std::string systemTime_1; // [rsp+50h] [rbp-1E0h] BYREF
  std::string systemTimeSFM_1; // [rsp+60h] [rbp-1D0h] BYREF
  std::string systemTimeNYR_1; // [rsp+70h] [rbp-1C0h] BYREF
  std::string ststemTimeLinux_0; // [rsp+80h] [rbp-1B0h] BYREF
  std::string systemTime_0; // [rsp+90h] [rbp-1A0h] BYREF
  std::string systemTimeSFM_0; // [rsp+A0h] [rbp-190h] BYREF
  std::string systemTimeNYR_0; // [rsp+B0h] [rbp-180h] BYREF
  std::string ststemTimeLinux; // [rsp+C0h] [rbp-170h] BYREF
  std::string systemTime; // [rsp+D0h] [rbp-160h] BYREF
  std::string systemTimeSFM; // [rsp+E0h] [rbp-150h] BYREF
  std::string systemTimeNYR; // [rsp+F0h] [rbp-140h] BYREF
  std::string __lhs; // [rsp+100h] [rbp-130h] BYREF
  std::string p_StringTime; // [rsp+110h] [rbp-120h] BYREF
  char __rhs[16]; // [rsp+120h] [rbp-110h] BYREF
  std::string v49; // [rsp+130h] [rbp-100h] BYREF
  std::string v50; // [rsp+140h] [rbp-F0h] BYREF
  char v51[16]; // [rsp+150h] [rbp-E0h] BYREF
  std::string v52; // [rsp+160h] [rbp-D0h] BYREF
  char v53[20]; // [rsp+170h] [rbp-C0h] BYREF
  int32_t opcode; // [rsp+184h] [rbp-ACh]
  int32_t id; // [rsp+188h] [rbp-A8h]
  int32_t count; // [rsp+18Ch] [rbp-A4h]
  CfgItem *cfgItem; // [rsp+190h] [rbp-A0h]
  int32_t id_0; // [rsp+198h] [rbp-98h]
  int32_t count_0; // [rsp+19Ch] [rbp-94h]
  int32_t money; // [rsp+1A0h] [rbp-90h]
  int32_t mapid; // [rsp+1A4h] [rbp-8Ch]
  int32_t x; // [rsp+1A8h] [rbp-88h]
  int32_t y; // [rsp+1ACh] [rbp-84h]
  int64_t exp; // [rsp+1B0h] [rbp-80h]
  int32_t i; // [rsp+1BCh] [rbp-74h]
  int32_t index; // [rsp+1C0h] [rbp-70h]
  int32_t addon; // [rsp+1C4h] [rbp-6Ch]
  int32_t trunkTaskId; // [rsp+1C8h] [rbp-68h]
  int32_t nClass; // [rsp+1CCh] [rbp-64h]
  int32_t nId; // [rsp+1D0h] [rbp-60h]
  int32_t nCount; // [rsp+1D4h] [rbp-5Ch]
  CTerritory *pTerritory; // [rsp+1D8h] [rbp-58h]
  int8_t FaBaoResType; // [rsp+1E3h] [rbp-4Dh]
  int32_t nCount_0; // [rsp+1E4h] [rbp-4Ch]
  int8_t Type; // [rsp+1EBh] [rbp-45h]
  int32_t nCount_1; // [rsp+1ECh] [rbp-44h]
  int32_t nTaskId; // [rsp+1F0h] [rbp-40h]
  int8_t nBagType; // [rsp+1FBh] [rbp-35h]
  int32_t nSize; // [rsp+1FCh] [rbp-34h]
  int32_t i_0; // [rsp+200h] [rbp-30h]
  int32_t nId_0; // [rsp+204h] [rbp-2Ch]
  int32_t oldLevel; // [rsp+208h] [rbp-28h]
  int32_t nId_1; // [rsp+20Ch] [rbp-24h]
  int32_t nId_2; // [rsp+210h] [rbp-20h]
  int32_t nCount_2; // [rsp+214h] [rbp-1Ch]

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  if ( !CfgData::getDebug(v3) )
    return 10002;
  opcode = Answer::NetPacket::readInt32(inPacket);
  switch ( opcode )
  {
    case 1:
      id = Answer::NetPacket::readInt32(inPacket);
      count = Answer::NetPacket::readInt32(inPacket);
      v4 = Answer::Singleton<CfgData>::instance();
      cfgItem = CfgData::getItem(v4, id);
      if ( cfgItem && count > 0 )
      {
        *(_DWORD *)&slotData.itemClass = 1;
        *(_DWORD *)&slotData.bind = 1;
        *(_QWORD *)&slotData.endTime = 0;
        slotData.srcId = 0;
        slotData.itemId = id;
        slotData.itemCount = count;
        CExtCharBag::AddItem(&this->m_extCharBag, &slotData, ITEM_CHANGE_REASON::ICR_NONE);
      }
      goto LABEL_94;
    case 2:
      id_0 = Answer::NetPacket::readInt32(inPacket);
      count_0 = Answer::NetPacket::readInt32(inPacket);
      *(_DWORD *)&slotData.itemClass = 2;
      *(_DWORD *)&slotData.bind = 1;
      *(_QWORD *)&slotData.endTime = 0;
      slotData.srcId = 0;
      slotData.itemId = id_0;
      slotData.itemCount = count_0;
      CExtCharBag::AddItem(&this->m_extCharBag, &slotData, ITEM_CHANGE_REASON::ICR_NONE);
      goto LABEL_94;
    case 3:
      money = Answer::NetPacket::readInt32(inPacket);
      if ( money > 0 )
      {
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_MONEY, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_CASH, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_VIGOUR, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_DRAW_SCORE, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_BOSS_SCORE, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_HONOR, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_AC_SOCRE, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_CONTRIBUTION, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_BLOOD, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
        Player::AddCurrency(this, CURRENCY_TYPE::CURRENCY_DUST, money, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 0);
      }
      goto LABEL_94;
    case 4:
      if ( this->m_pMap )
      {
        mapid = Answer::NetPacket::readInt32(inPacket);
        x = Answer::NetPacket::readInt32(inPacket);
        y = Answer::NetPacket::readInt32(inPacket);
        if ( Map::GetMapId(this->m_pMap) == mapid )
        {
          Unit::instantMove(this, x, y, InstanceMoveReason::IMR_GM, 0);
        }
        else
        {
          v5 = Answer::Singleton<MapManager>::instance();
          Map = MapManager::GetMap(v5, mapid);
          Player::switchMap(this, Map, x, y, 1);
        }
      }
      goto LABEL_94;
    case 5:
      for ( i = 0; i <= 99999; ++i )
      {
        v7 = Answer::Singleton<CfgData>::instance();
        LuckDropTableTable = CfgData::GetLuckDropTableTable(v7);
        LuckDropTable::GetItem(&slotData, LuckDropTableTable, 1, 6);
        if ( slotData.itemClass != 2 || slotData.itemId <= 0 || slotData.itemCount <= 0 )
          printf(
            "vipDrop item.id=%d,itemClass=%d,itemCount=%d\n",
            slotData.itemId,
            slotData.itemClass,
            slotData.itemCount);
      }
      exp = Answer::NetPacket::readInt64(inPacket);
      if ( exp > 0 )
        Player::addExp(this, exp, 0, 0);
      goto LABEL_94;
    case 6:
      index = Answer::NetPacket::readInt32(inPacket);
      addon = Answer::NetPacket::readInt32(inPacket);
      Unit::AddBuffAttrValue(this, (const CObjAttrs::Index_T)index, addon);
      Unit::setNeedSyncSelf(this);
      goto LABEL_94;
    case 8:
      trunkTaskId = Answer::NetPacket::readInt32(inPacket);
      ChrTask::cmdResetTrunkTask(&this->m_task, trunkTaskId);
      goto LABEL_94;
    case 9:
      nClass = Answer::NetPacket::readInt32(inPacket);
      nId = Answer::NetPacket::readInt32(inPacket);
      nCount = Answer::NetPacket::readInt32(inPacket);
      memset(&slotData.bind, 0, 20);
      *(_DWORD *)&slotData.itemClass = (unsigned __int8)nClass;
      slotData.itemId = nId;
      slotData.itemCount = nCount;
      CExtCharBag::AddItem(&this->m_extCharBag, &slotData, ITEM_CHANGE_REASON::ICR_NONE);
      goto LABEL_94;
    case 10:
      if ( Player::getFamilyId(this) > 0 )
      {
        FamilyId = Player::getFamilyId(this);
        v10 = Answer::Singleton<MapManager>::instance();
        pTerritory = MapManager::GetTerritory(v10, FamilyId);
        if ( !pTerritory )
        {
          v11 = Player::getFamilyId(this);
          v12 = Answer::Singleton<MapManager>::instance();
          pTerritory = MapManager::NewTerritory(v12, v11);
          TerritoryId = CTerritory::GetTerritoryId(pTerritory);
          printf("new pTerritory id=%lld\n", TerritoryId);
        }
        if ( pTerritory && this->m_pMap )
        {
          Player::setOldPosition(this);
          Player::broadcastLeave(this);
          (*((void (__fastcall **)(Map *, Player *const, _QWORD))this->m_pMap->_vptr_Map + 16))(this->m_pMap, this, 0);
          (*((void (__fastcall **)(CTerritory *, Player *const, __int64, __int64))pTerritory->_vptr_Map + 15))(
            pTerritory,
            this,
            40,
            40);
          RunnerId = Map::GetRunnerId(pTerritory);
          v15 = Answer::Singleton<MapManager>::instance();
          MapManager::PostMsg(v15, RunnerId, GameMsgCode::GMC_ADD_TERRITORY, pTerritory, 0, 0, 0, 0);
        }
      }
      goto LABEL_94;
    case 11:
      v16 = Answer::Singleton<GameService>::instance();
      GameService::AddPlayerVipClubDropTime(v16);
      goto LABEL_94;
    case 13:
      FaBaoResType = Answer::NetPacket::readInt8(inPacket);
      nCount_0 = Answer::NetPacket::readInt32(inPacket);
      CFaBao::AddFaBaoRes(&this->m_PlayerFaBao, FaBaoResType, nCount_0);
      goto LABEL_94;
    case 14:
      Type = Answer::NetPacket::readInt8(inPacket);
      nCount_1 = Answer::NetPacket::readInt32(inPacket);
      if ( nCount_1 <= 0 )
        Player::DecCurrency(this, (const CURRENCY_TYPE)Type, -nCount_1, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 9527);
      else
        Player::AddCurrency(this, (const CURRENCY_TYPE)Type, nCount_1, CURRENCY_CHANGE_REASON::GM_DEBUG_CMD, 9527);
      goto LABEL_94;
    case 17:
      nTaskId = Answer::NetPacket::readInt32(inPacket);
      ChrTask::ForceSubmit(&this->m_task, nTaskId);
      goto LABEL_94;
    case 18:
      Int32 = Answer::NetPacket::readInt32(inPacket);
      Player::addPkValue(this, Int32);
      goto LABEL_94;
    case 20:
      nBagType = Answer::NetPacket::readInt32(inPacket);
      switch ( nBagType )
      {
        case 1:
          nSize = CExtCharBag::GetBagSize(&this->m_extCharBag);
          for ( i_0 = 0; i_0 < nSize; ++i_0 )
            CExtCharBag::CleanSlot(&this->m_extCharBag, i_0, ITEM_CHANGE_REASON::ICR_NONE);
          break;
        case 2:
          CChrDepot::CleanBag(&this->m_PlayerDepot);
          break;
        case 3:
          ChouJiang::CleanBag(&this->m_PlayerChouJiang);
          break;
      }
      goto LABEL_94;
    case 21:
      Answer::NetPacket::readUTF8((Answer::NetPacket *const)&systemTimeNYR, (bool)inPacket);
      Answer::NetPacket::readUTF8((Answer::NetPacket *const)&systemTimeSFM, (bool)inPacket);
      std::operator+<char>(&__lhs, (const char *)&systemTimeNYR);
      std::operator+<char>(&systemTime, &__lhs);
      std::string::~string(&__lhs);
      std::string::string(&p_StringTime, &systemTime);
      v18 = Answer::DayTime::StringToIntTime(&p_StringTime);
      LOBYTE(v18) = v18 < Unit::getNow(this);
      std::string::~string(&p_StringTime);
      if ( (_BYTE)v18 )
      {
        v2 = 10002;
        v19 = 0;
      }
      else if ( std::operator!=<char>(&systemTime, byte_8E9580) )
      {
        std::operator+<char>(__rhs, &stru_8EE1E8);
        std::operator+<char>(&ststemTimeLinux, __rhs);
        std::string::~string(__rhs);
        v20 = (const char *)std::string::c_str(&ststemTimeLinux);
        system(v20);
        Player::SyncTime(this);
        std::string::~string(&ststemTimeLinux);
        v19 = 1;
      }
      else
      {
        v19 = 2;
      }
      std::string::~string(&systemTime);
      if ( v19 )
      {
        if ( v19 == 1 )
          v21 = 1;
        else
          v21 = 2;
      }
      else
      {
        v21 = 0;
      }
      std::string::~string(&systemTimeSFM);
      if ( v21 )
      {
        if ( v21 == 1 )
          v22 = 1;
        else
          v22 = 2;
      }
      else
      {
        v22 = 0;
      }
      std::string::~string(&systemTimeNYR);
      if ( !v22 )
        return v2;
      if ( v22 != 1 )
      {
LABEL_67:
        nId_0 = Answer::NetPacket::readInt32(inPacket);
        CExtCharCarrier::EnterCarrier(&this->m_extCharCarrier, nId_0);
      }
      goto LABEL_94;
    case 22:
      goto LABEL_67;
    case 23:
      oldLevel = this->m_chr.level;
      this->m_chr.level = Answer::NetPacket::readInt32(inPacket);
      this->m_chr.exp = 0;
      Player::LevelUped(this, oldLevel, this->m_chr.level);
      goto LABEL_94;
    case 25:
      Answer::NetPacket::readUTF8((Answer::NetPacket *const)&systemTimeNYR_0, (bool)inPacket);
      Answer::NetPacket::readUTF8((Answer::NetPacket *const)&systemTimeSFM_0, (bool)inPacket);
      std::operator+<char>(&v49, (const char *)&systemTimeNYR_0);
      std::operator+<char>(&systemTime_0, &v49);
      std::string::~string(&v49);
      std::string::string(&v50, &systemTime_0);
      v23 = Answer::DayTime::StringToIntTime(&v50);
      LOBYTE(v23) = v23 < Unit::getNow(this);
      std::string::~string(&v50);
      if ( (_BYTE)v23 )
      {
        v2 = 10002;
        v24 = 0;
      }
      else if ( std::operator!=<char>(&systemTime_0, byte_8E9580) )
      {
        std::operator+<char>(v51, &stru_8EE1E8);
        std::operator+<char>(&ststemTimeLinux_0, v51);
        std::string::~string(v51);
        v25 = (const char *)std::string::c_str(&ststemTimeLinux_0);
        system(v25);
        Player::SyncTime(this);
        std::string::~string(&ststemTimeLinux_0);
        v24 = 1;
      }
      else
      {
        v24 = 2;
      }
      std::string::~string(&systemTime_0);
      if ( v24 )
      {
        if ( v24 == 1 )
          v26 = 1;
        else
          v26 = 2;
      }
      else
      {
        v26 = 0;
      }
      std::string::~string(&systemTimeSFM_0);
      if ( v26 )
      {
        if ( v26 == 1 )
          v27 = 1;
        else
          v27 = 2;
      }
      else
      {
        v27 = 0;
      }
      std::string::~string(&systemTimeNYR_0);
      if ( !v27 )
        return v2;
      if ( v27 != 1 )
      {
LABEL_86:
        Answer::NetPacket::readUTF8((Answer::NetPacket *const)&systemTimeNYR_1, (bool)inPacket);
        Answer::NetPacket::readUTF8((Answer::NetPacket *const)&systemTimeSFM_1, (bool)inPacket);
        std::operator+<char>(&v52, (const char *)&systemTimeNYR_1);
        std::operator+<char>(&systemTime_1, &v52);
        std::string::~string(&v52);
        if ( std::operator!=<char>(&systemTime_1, byte_8E9580) )
        {
          std::operator+<char>(v53, &stru_8EE1E8);
          std::operator+<char>(&ststemTimeLinux_1, v53);
          std::string::~string(v53);
          v28 = (const char *)std::string::c_str(&ststemTimeLinux_1);
          system(v28);
          Player::SyncTime(this);
          std::string::~string(&ststemTimeLinux_1);
          v29 = 0;
        }
        else
        {
          v29 = 1;
        }
        std::string::~string(&systemTime_1);
        std::string::~string(&systemTimeSFM_1);
        std::string::~string(&systemTimeNYR_1);
        if ( v29 )
        {
LABEL_90:
          nId_1 = Answer::NetPacket::readInt32(inPacket);
          CMingGeExt::AddItem(&this->m_CMingGeExt, nId_1, ITEM_CHANGE_REASON::ICR_NONE);
        }
      }
      goto LABEL_94;
    case 26:
      goto LABEL_86;
    case 27:
      goto LABEL_90;
    case 28:
      nId_2 = Answer::NetPacket::readInt32(inPacket);
      nCount_2 = Answer::NetPacket::readInt32(inPacket);
      v30 = Answer::Singleton<CfgData>::instance();
      KunLingTable = CfgData::GetKunLingTable(v30);
      if ( KunLingTable::GetLingZhuCfg(KunLingTable, nId_2) )
      {
        CKunExt::AddLingZhuBagItem(&this->m_CKunExt, nId_2, nCount_2, ITEM_CHANGE_REASON::ICR_NONE);
LABEL_94:
        v2 = 0;
      }
      else
      {
        v2 = 2;
      }
      break;
    default:
      goto LABEL_94;
  }
  return v2;
}


#####################################
int32_t __cdecl Player::onQueryPlayerInfo(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  int64_t nTargetId; // [rsp+10h] [rbp-20h]
  Player *pTarget; // [rsp+18h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  nTargetId = Answer::NetPacket::readInt64(inPacket);
  if ( nTargetId <= 0 )
    return 10002;
  RunnerId = StaticObj::GetRunnerId(this);
  v4 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v4, nTargetId, RunnerId, 1);
  if ( !pTarget )
    return 10002;
  Player::SendOtherPlayerInfo(pTarget, this->m_connid, this->m_cgindex);
  return 0;
}


#####################################
int32_t __cdecl Player::onSocialUseWeiXinCard(Player *const this, Answer::NetPacket *inPacket)
{
  int16_t v3; // r12
  int8_t v4; // bl
  GameService *v5; // rax
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  MemChrBag item; // [rsp+10h] [rbp-40h] BYREF
  int8_t Type; // [rsp+37h] [rbp-19h]
  int32_t ItemId; // [rsp+38h] [rbp-18h]
  int32_t LimitId; // [rsp+3Ch] [rbp-14h]

  if ( !inPacket )
    return 10002;
  Type = Answer::NetPacket::readInt8(inPacket);
  ItemId = 0;
  LimitId = 0;
  switch ( Type )
  {
    case 2:
      LimitId = 1056;
      ItemId = 7417;
      break;
    case 3:
      LimitId = 1053;
      ItemId = 7039;
      break;
    case 1:
      LimitId = 1052;
      ItemId = 7419;
      break;
    default:
      return 10002;
  }
  if ( Player::getRecord(this, LimitId) <= 0 )
  {
    *(_DWORD *)&item.itemClass = 1;
    *(_QWORD *)&item.itemCount = 0x100000001LL;
    *(_QWORD *)&item.endTime = 0;
    item.srcId = 0;
    item.itemId = ItemId;
    if ( !CExtCharBag::AddItem(&this->m_extCharBag, &item, ITEM_CHANGE_REASON::ICR_EXCHANGE_CODE) )
    {
      m_cgindex = this->m_cgindex;
      m_connid = this->m_connid;
      v8 = Answer::Singleton<GameService>::instance();
      return GameService::replyfailure(v8, m_connid, m_cgindex, 0xBEAu, 10016, 0);
    }
    else
    {
      Player::updateRecord(this, LimitId, 1);
      if ( Type == 1 || Type == 2 )
        CWan360::SendWeiXinIcon(&this->m_Wan360);
      if ( Type == 3 )
        Player::sendJoinQQIcon(this);
      return 0;
    }
  }
  else
  {
    v3 = this->m_cgindex;
    v4 = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v5, v4, v3, 0xBEAu, 10042, 0);
  }
}


#####################################
int32_t __cdecl Player::onSocialUseExchangeCode(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int8_t m_connid; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int8_t v6; // bl
  GameService *v7; // rax
  int16_t m_cgindex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  int8_t v11; // bl
  GameService *v12; // rax
  uint32_t v13; // eax
  int8_t v14; // bl
  GameService *v15; // rax
  MemChrBag item; // [rsp+10h] [rbp-60h] BYREF
  std::string code; // [rsp+30h] [rbp-40h] BYREF
  std::string val; // [rsp+40h] [rbp-30h] BYREF
  char v20; // [rsp+4Bh] [rbp-25h] BYREF
  int32_t item_id; // [rsp+4Ch] [rbp-24h]
  Answer::NetPacket *outPacket; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *outPacket_0; // [rsp+58h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  item_id = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&code, (bool)inPacket);
  *(_DWORD *)&item.itemClass = 1;
  *(_QWORD *)&item.itemCount = 0x100000001LL;
  *(_QWORD *)&item.endTime = 0;
  item.srcId = 0;
  item.itemId = item_id;
  if ( !CExtCharBag::AddItem(&this->m_extCharBag, &item, ITEM_CHANGE_REASON::ICR_EXCHANGE_CODE) )
  {
    m_connid = this->m_connid;
    v4 = Answer::Singleton<GameService>::instance();
    outPacket_0 = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x4E96u);
    if ( outPacket_0 )
    {
      Answer::NetPacket::writeInt32(outPacket_0, this->m_cgindex);
      Answer::NetPacket::writeInt32(outPacket_0, 0);
      std::allocator<char>::allocator(&v20);
      std::string::string(&val, byte_8E9580);
      Answer::NetPacket::writeUTF8(outPacket_0, &val);
      std::string::~string(&val);
      std::allocator<char>::~allocator(&v20);
      WOffset = Answer::NetPacket::getWOffset(outPacket_0);
      Answer::NetPacket::setSize(outPacket_0, WOffset);
      v6 = this->m_connid;
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, outPacket_0);
      m_cgindex = this->m_cgindex;
      v9 = this->m_connid;
      v10 = Answer::Singleton<GameService>::instance();
      v2 = GameService::replyfailure(v10, v9, m_cgindex, 0xBEAu, 10016, 0);
    }
    else
    {
      v2 = 10002;
    }
  }
  else
  {
    v11 = this->m_connid;
    v12 = Answer::Singleton<GameService>::instance();
    outPacket = GameService::popNetpacket(v12, v11, Answer::PackType::PACK_DISPATCH, 0x4E96u);
    if ( outPacket )
    {
      Answer::NetPacket::writeInt32(outPacket, this->m_cgindex);
      Answer::NetPacket::writeInt32(outPacket, 1);
      Answer::NetPacket::writeUTF8(outPacket, &code);
      v13 = Answer::NetPacket::getWOffset(outPacket);
      Answer::NetPacket::setSize(outPacket, v13);
      v14 = this->m_connid;
      v15 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v15, v14, outPacket);
      v2 = 0;
    }
    else
    {
      v2 = 10002;
    }
  }
  std::string::~string(&code);
  return v2;
}


#####################################
void __cdecl Player::sendLoginInfo(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t Record; // eax
  CfgData *v4; // rax
  int8_t ServerType; // al
  CfgData *v6; // rax
  int32_t ServerStartTime; // eax
  CfgData *v8; // rax
  int32_t ServerStartDayZeroTime; // eax
  CfgData *v10; // rax
  int32_t ServerDiffDay; // eax
  CfgData *v12; // rax
  int32_t v13; // eax
  CfgData *v14; // rax
  int32_t v15; // eax
  CfgData *v16; // rax
  int32_t v17; // eax
  int32_t v18; // eax
  int8_t ConnId; // bl
  CActivityManager *v20; // rax
  FamilyId_t CityWarWinner; // rax
  CActivityManager *v22; // rax
  CharId_t CrossTowerWinner; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v26; // bl
  GameService *v27; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2718u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_chr.last_task_id);
    Answer::NetPacket::writeInt32(packet, this->m_sysUser.adult);
    Answer::NetPacket::writeInt32(packet, this->m_sysUser.total_online_time);
    Record = Player::getRecord(this, 1009);
    Answer::NetPacket::writeInt32(packet, Record);
    v4 = Answer::Singleton<CfgData>::instance();
    ServerType = CfgData::getServerType(v4);
    Answer::NetPacket::writeInt8(packet, ServerType);
    v6 = Answer::Singleton<CfgData>::instance();
    ServerStartTime = CfgData::getServerStartTime(v6, SERVER_TYPE::SVT_NORMAL);
    Answer::NetPacket::writeInt32(packet, ServerStartTime);
    v8 = Answer::Singleton<CfgData>::instance();
    ServerStartDayZeroTime = CfgData::getServerStartDayZeroTime(v8, SERVER_TYPE::SVT_NORMAL);
    Answer::NetPacket::writeInt32(packet, ServerStartDayZeroTime);
    v10 = Answer::Singleton<CfgData>::instance();
    ServerDiffDay = CfgData::getServerDiffDay(v10, SERVER_TYPE::SVT_NORMAL);
    Answer::NetPacket::writeInt32(packet, ServerDiffDay);
    v12 = Answer::Singleton<CfgData>::instance();
    v13 = CfgData::getServerStartTime(v12, SERVER_TYPE::SVT_UNITE);
    Answer::NetPacket::writeInt32(packet, v13);
    v14 = Answer::Singleton<CfgData>::instance();
    v15 = CfgData::getServerStartDayZeroTime(v14, SERVER_TYPE::SVT_UNITE);
    Answer::NetPacket::writeInt32(packet, v15);
    v16 = Answer::Singleton<CfgData>::instance();
    v17 = CfgData::getServerDiffDay(v16, SERVER_TYPE::SVT_UNITE);
    Answer::NetPacket::writeInt32(packet, v17);
    Answer::NetPacket::writeInt32(packet, this->m_chr.create_time);
    Answer::NetPacket::writeInt32(packet, this->m_sysUserPreventWallow.isGrowUp);
    v18 = Player::getRecord(this, 1011);
    Answer::NetPacket::writeInt32(packet, v18);
    Answer::NetPacket::writeInt32(packet, this->m_sysUser.continue_login_count);
    ConnId = Player::getConnId(this);
    v20 = Answer::Singleton<CActivityManager>::instance();
    CityWarWinner = CActivityManager::GetCityWarWinner(v20, ConnId);
    Answer::NetPacket::writeInt64(packet, CityWarWinner);
    Answer::Singleton<CActivityManager>::instance();
    CActivityManager::GetCrossTowerName((CActivityManager *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    v22 = Answer::Singleton<CActivityManager>::instance();
    CrossTowerWinner = CActivityManager::GetCrossTowerWinner(v22);
    Answer::NetPacket::writeInt64(packet, CrossTowerWinner);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v26 = this->m_connid;
    v27 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v27, v26, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendChrInfo(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  CharId_t Cid; // rax
  FamilyId_t FamilyId; // rax
  Sex_t Sex; // al
  Job_t Job; // al
  int16_t v7; // ax
  int64_t Exp; // rax
  int64_t LevelExp; // rsi
  int32_t v10; // eax
  int32_t MP; // eax
  int32_t Power; // eax
  CExtCharTitle *CharTitle; // rax
  int32_t DressTitleId; // eax
  int32_t PkValue; // eax
  int8_t PkMode; // al
  int32_t PkProtectTime; // ebx
  int32_t v18; // ebx
  int32_t v19; // eax
  int8_t IsBuleName; // al
  int8_t v21; // al
  int8_t v22; // al
  int32_t EndTime; // eax
  bool v24; // bl
  CVplan *Vplan; // rax
  int8_t PlatformVipLevel; // al
  int32_t CarrierId; // eax
  int32_t v28; // eax
  int32_t v29; // eax
  int8_t v30; // al
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v33; // bl
  GameService *v34; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  std::string v36; // [rsp+20h] [rbp-30h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2755u);
  if ( packet )
  {
    Cid = Player::getCid(this);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    FamilyId = Player::getFamilyId(this);
    Answer::NetPacket::writeInt64(packet, FamilyId);
    Player::getFamilyName((const Player *const)&v36);
    Answer::NetPacket::writeUTF8(packet, &v36);
    std::string::~string(&v36);
    Sex = Player::getSex(this);
    Answer::NetPacket::writeInt8(packet, Sex);
    Job = Player::getJob(this);
    Answer::NetPacket::writeInt8(packet, Job);
    v7 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
    Answer::NetPacket::writeInt16(packet, v7);
    Exp = Player::getExp(this);
    Answer::NetPacket::writeInt64(packet, Exp);
    LevelExp = Player::GetLevelExp(this);
    Answer::NetPacket::writeInt64(packet, LevelExp);
    v10 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 26))(this);
    Answer::NetPacket::writeInt32(packet, v10);
    MP = Unit::GetMP(this);
    Answer::NetPacket::writeInt32(packet, MP);
    Power = CExtCharSkill::GetPower(&this->m_extCharSkill);
    Answer::NetPacket::writeInt32(packet, Power);
    Answer::NetPacket::writeInt32(packet, this->m_nJumpEnergy);
    CharTitle = Player::GetCharTitle(this);
    DressTitleId = CExtCharTitle::GetDressTitleId(CharTitle);
    Answer::NetPacket::writeInt32(packet, DressTitleId);
    PkValue = Player::getPkValue(this);
    Answer::NetPacket::writeInt32(packet, PkValue);
    PkMode = Player::getPkMode(this);
    Answer::NetPacket::writeInt8(packet, PkMode);
    PkProtectTime = Player::getPkProtectTime(this);
    if ( PkProtectTime - Unit::getNow(this) <= 0 )
    {
      v19 = 0;
    }
    else
    {
      v18 = Player::getPkProtectTime(this);
      v19 = v18 - Unit::getNow(this);
    }
    Answer::NetPacket::writeInt32(packet, v19);
    IsBuleName = CExtFightChecker::IsBuleName(&this->m_extFightChecker);
    Answer::NetPacket::writeInt8(packet, IsBuleName);
    v21 = CExtOperateLimit::CheckIsLimitedForever(&this->m_extOperateLimit, 37203);
    Answer::NetPacket::writeInt8(packet, v21);
    v22 = Player::IsInStall(this);
    Answer::NetPacket::writeInt8(packet, v22);
    CExtCharTencent::AppendInfo(&this->m_extCharTencent, packet);
    EndTime = CExtCharTencent::GetEndTime(&this->m_extCharTencent);
    Answer::NetPacket::writeInt32(packet, EndTime);
    CVplan::AppendYYInfo(&this->m_Vplan, packet);
    CVplan::AppendSwVipInfo(&this->m_Vplan, packet);
    Player::GetPlatform((const Player *const)&__lhs);
    v24 = std::operator==<char>(&__lhs, "37wan");
    std::string::~string(&__lhs);
    if ( v24 )
    {
      Vplan = Player::GetVplan(this);
      PlatformVipLevel = CVplan::GetPlatformVipLevel(Vplan);
      Answer::NetPacket::writeInt8(packet, PlatformVipLevel);
    }
    else
    {
      Answer::NetPacket::writeInt8(packet, 0);
    }
    CarrierId = CExtCharCarrier::GetCarrierId(&this->m_extCharCarrier);
    Answer::NetPacket::writeInt32(packet, CarrierId);
    v28 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 26))(this);
    Answer::NetPacket::writeInt32(packet, v28);
    v29 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 27))(this);
    Answer::NetPacket::writeInt32(packet, v29);
    v30 = Player::GetTotalPayGold(this) > 0;
    Answer::NetPacket::writeInt8(packet, v30);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v33 = this->m_connid;
    v34 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v34, v33, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendCharAttrInfo(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  int32_t v3; // edx
  int32_t AllMoneyRate; // edx
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x2756u);
  if ( packet )
  {
    Player::appendCharAttrInfo(this, packet);
    v3 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 10))(this);
    Answer::NetPacket::writeInt32(packet, v3);
    AllMoneyRate = Player::GetAllMoneyRate(this);
    Answer::NetPacket::writeInt32(packet, AllMoneyRate);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::appendCharAttrInfo(Player *const this, Answer::NetPacket *packet)
{
  int32_t AttrValue; // edx
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( packet )
  {
    for ( i = 1; i <= 49; ++i )
    {
      AttrValue = Unit::GetAttrValue(this, (const CObjAttrs::Index_T)i);
      Answer::NetPacket::writeInt32(packet, AttrValue);
    }
  }
}


#####################################
void __cdecl Player::sendAttrAddon(Player *const this, const AttrAddonList *const attrs)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  int32_t v4; // eax
  const AttrAddon *v5; // rax
  const AttrAddon *v6; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_const_iterator<AttrAddon> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_const_iterator<AttrAddon> __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x2757u);
  if ( packet )
  {
    v4 = std::list<AttrAddon>::size(attrs);
    Answer::NetPacket::writeInt32(packet, v4);
    for ( iter._M_node = std::list<AttrAddon>::begin(attrs)._M_node;
          ;
          std::_List_const_iterator<AttrAddon>::operator++(&iter) )
    {
      __x._M_node = std::list<AttrAddon>::end(attrs)._M_node;
      if ( !std::_List_const_iterator<AttrAddon>::operator!=(&iter, &__x) )
        break;
      v5 = std::_List_const_iterator<AttrAddon>::operator->(&iter);
      Answer::NetPacket::writeInt8(packet, v5->index);
      v6 = std::_List_const_iterator<AttrAddon>::operator->(&iter);
      Answer::NetPacket::writeInt32(packet, v6->addon);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v9 = this->m_connid;
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v10, v9, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendActionList(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x27A4u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_actions[12].id);
    Answer::NetPacket::writeInt32(packet, this->m_actions[12].type);
    for ( i = 1; i <= 10; ++i )
    {
      Answer::NetPacket::writeInt32(packet, *((_DWORD *)&this->m_task.m_taskMonsters._M_impl + 2 * i + 4));
      Answer::NetPacket::writeInt32(packet, *((_DWORD *)&this->m_task.m_taskMonsters._M_impl + 2 * i + 5));
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v5 = this->m_connid;
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v6, v5, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendAutoFight(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  char v8; // [rsp+1Fh] [rbp-31h] BYREF
  std::string v9; // [rsp+20h] [rbp-30h] BYREF
  char v10; // [rsp+37h] [rbp-19h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x27A5u);
  if ( packet )
  {
    std::allocator<char>::allocator(&v8);
    std::string::string(&val, &this->m_autoFight);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    std::allocator<char>::~allocator(&v8);
    std::allocator<char>::allocator(&v10);
    std::string::string(&v9, this->m_autoFight.pick);
    Answer::NetPacket::writeUTF8(packet, &v9);
    std::string::~string(&v9);
    std::allocator<char>::~allocator(&v10);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v5 = this->m_connid;
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v6, v5, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendSystemSetting(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  m_connid = this->m_connid;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, m_connid, Answer::PackType::PACK_DISPATCH, 0x27A6u);
  if ( packet )
  {
    nSize = std::map<int,int>::size(&this->m_SystemSetting);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,int>::begin(&this->m_SystemSetting)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_SystemSetting)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v3->first);
      v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v4->second);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::UpdateKilledByPlayer(Player *const this, CharId_t KillerId)
{
  GameService *v2; // rax
  int8_t m_connid; // bl
  GameService *v4; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
  {
    m_connid = this->m_connid;
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_PROC, 0x4EB1u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt64(packet, KillerId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = this->m_connid;
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v8, v7, packet);
    }
  }
}


#####################################
void __cdecl Player::sendKilledByPlayer(Player *const this, CharId_t cid, const std::string *const name)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x27B0u);
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, cid);
    Answer::NetPacket::writeUTF8(packet, name);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::sendUpdateSocialPlayerInfo(Player *const this, PlayerInfoIndex index, int64_t value)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  m_connid = this->m_connid;
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_PROC, 0x4E33u);
  if ( packet )
  {
    Cid = Player::getCid(this);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, index);
    Answer::NetPacket::writeInt64(packet, value);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v8, v7, packet);
  }
}


#####################################
void __cdecl Player::checkSaveToDB(Player *const this)
{
  GameService *v1; // rax

  if ( Unit::getTick(this) - this->m_lastSaveTick >= this->m_saveDataTimeCount )
  {
    v1 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v1) != 9 )
      (*((void (__fastcall **)(Player *const, __int64, _QWORD, _QWORD))this->_vptr_Entity + 35))(this, 5, 0, 0);
    this->m_lastSaveTick = Unit::getTick(this);
  }
}


#####################################
void __cdecl Player::checkSyncStatus(Player *const this)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  int8_t TeamStatus; // al
  int8_t VipType; // al
  int8_t VipLevel; // al
  FamilyId_t FamilyId; // rax
  int8_t FamilyPosition; // al
  int8_t JueWei; // al
  int8_t Camp; // al
  int8_t ActState; // al
  uint32_t WOffset; // eax
  int8_t v14; // bl
  GameService *v15; // rax
  CharId_t v16; // rsi
  int16_t v17; // ax
  int32_t MainWeaponId; // eax
  int32_t ClothesId; // eax
  int32_t WingId; // eax
  int32_t WingEquipPolishSuitId; // eax
  int8_t IsBuleName; // al
  int32_t ProtectTime; // eax
  int32_t ShiZhuangWeapon; // eax
  int32_t ShiZhuangClothes; // eax
  int32_t EffectId; // eax
  int32_t ShiZhuangFeet; // eax
  int32_t Action; // eax
  int32_t CarrierId; // eax
  int32_t Record; // eax
  int8_t IsFitting; // al
  int32_t v32; // eax
  int32_t v33; // eax
  uint32_t v34; // eax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+28h] [rbp-18h]

  if ( (*((unsigned __int8 (__fastcall **)(Player *const))this->_vptr_Entity + 31))(this) || this->m_needSyncToTeam )
  {
    this->m_needSyncToTeam = 0;
    CExtCharTeam::BroadcastBasicData(&this->m_extCharTeam);
  }
  if ( this->m_needSyncStatus && this->m_pMap )
  {
    m_connid = this->m_connid;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x273Cu);
    if ( !packet )
      return;
    Cid = Player::getCid(this);
    Answer::NetPacket::writeInt64(packet, Cid);
    TeamStatus = Player::GetTeamStatus(this);
    Answer::NetPacket::writeInt8(packet, TeamStatus);
    VipType = CVip::GetVipType(&this->m_PlayerVip);
    Answer::NetPacket::writeInt8(packet, VipType);
    VipLevel = CVip::GetVipLevel(&this->m_PlayerVip);
    Answer::NetPacket::writeInt8(packet, VipLevel);
    FamilyId = Player::getFamilyId(this);
    Answer::NetPacket::writeInt64(packet, FamilyId);
    FamilyPosition = Player::getFamilyPosition(this);
    Answer::NetPacket::writeInt8(packet, FamilyPosition);
    Player::getFamilyName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    JueWei = CExtCharJueWei::GetJueWei(&this->m_extCharJueWei);
    Answer::NetPacket::writeInt8(packet, JueWei);
    Answer::NetPacket::writeInt8(packet, 0);
    CExtCharTitle::AppendDressTitle(&this->m_extCharTitle, packet);
    Camp = Player::GetCamp(this);
    Answer::NetPacket::writeInt8(packet, Camp);
    ActState = Player::GetActState(this);
    Answer::NetPacket::writeInt8(packet, ActState);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this->m_pMap, packet);
    this->m_needSyncStatus = 0;
  }
  if ( this->m_needSyncSelf )
  {
    Player::sendChrInfo(this);
    this->m_needSyncSelf = 0;
  }
  if ( this->m_needSyncAttr )
  {
    Player::sendCharAttrInfo(this);
    this->m_needSyncAttr = 0;
  }
  if ( this->m_NeedSyncAround && this->m_pMap )
  {
    v14 = this->m_connid;
    v15 = Answer::Singleton<GameService>::instance();
    packet_0 = GameService::popNetpacket(v15, v14, Answer::PackType::PACK_DISPATCH, 0x2DB5u);
    if ( packet_0 )
    {
      v16 = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet_0, v16);
      v17 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
      Answer::NetPacket::writeInt16(packet_0, v17);
      MainWeaponId = Player::getMainWeaponId(this);
      Answer::NetPacket::writeInt32(packet_0, MainWeaponId);
      ClothesId = Player::getClothesId(this);
      Answer::NetPacket::writeInt32(packet_0, ClothesId);
      WingId = Player::getWingId(this);
      Answer::NetPacket::writeInt32(packet_0, WingId);
      WingEquipPolishSuitId = CGoblin::GetWingEquipPolishSuitId(&this->m_CGoblin);
      Answer::NetPacket::writeInt32(packet_0, WingEquipPolishSuitId);
      Answer::NetPacket::writeInt8(packet_0, this->m_chr.pk_mode);
      Answer::NetPacket::writeInt32(packet_0, this->m_chr.pk_value);
      IsBuleName = CExtFightChecker::IsBuleName(&this->m_extFightChecker);
      Answer::NetPacket::writeInt8(packet_0, IsBuleName);
      ProtectTime = Player::GetProtectTime(this);
      Answer::NetPacket::writeInt32(packet_0, ProtectTime);
      Answer::NetPacket::writeInt8(packet_0, 0);
      ShiZhuangWeapon = Player::getShiZhuangWeapon(this);
      Answer::NetPacket::writeInt32(packet_0, ShiZhuangWeapon);
      ShiZhuangClothes = Player::getShiZhuangClothes(this);
      Answer::NetPacket::writeInt32(packet_0, ShiZhuangClothes);
      EffectId = CShiZhuang::GetEffectId(&this->m_extShiZhuang);
      Answer::NetPacket::writeInt32(packet_0, EffectId);
      ShiZhuangFeet = Player::getShiZhuangFeet(this);
      Answer::NetPacket::writeInt32(packet_0, ShiZhuangFeet);
      Action = Player::getAction(this);
      Answer::NetPacket::writeInt32(packet_0, Action);
      Answer::NetPacket::writeInt8(packet_0, this->m_PlantState);
      CExtCharTencent::AppendInfo(&this->m_extCharTencent, packet_0);
      CVplan::AppendYYInfo(&this->m_Vplan, packet_0);
      CVplan::AppendSwVipInfo(&this->m_Vplan, packet_0);
      Answer::NetPacket::writeInt8(packet_0, 0);
      CarrierId = CExtCharCarrier::GetCarrierId(&this->m_extCharCarrier);
      Answer::NetPacket::writeInt32(packet_0, CarrierId);
      Record = Player::getRecord(this, 3);
      Answer::NetPacket::writeInt32(packet_0, Record);
      IsFitting = CExtCharPet::IsFitting(&this->m_extCharPet);
      Answer::NetPacket::writeInt8(packet_0, IsFitting);
      v32 = Player::getRecord(this, 1148);
      Answer::NetPacket::writeInt32(packet_0, v32);
      v33 = Player::getRecord(this, 1153);
      Answer::NetPacket::writeInt32(packet_0, v33);
      v34 = Answer::NetPacket::getWOffset(packet_0);
      Answer::NetPacket::setSize(packet_0, v34);
      Map::broadcastAreaAround(this->m_pMap, packet_0, this);
      this->m_NeedSyncAround = 0;
    }
  }
}


#####################################
void __cdecl Player::checkPool(Player *const this)
{
  Dungeon *v2; // rax
  int64_t DieTick; // rax
  int32_t v6; // ebx
  float v8; // [rsp+4h] [rbp-6Ch]
  tm time; // [rsp+10h] [rbp-60h] BYREF
  int64_t curTick; // [rsp+48h] [rbp-28h]
  Dungeon *pDungeon; // [rsp+50h] [rbp-20h]
  int32_t Now; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pMap )
    return;
  curTick = Unit::getTick(this);
  if ( Unit::isAlive(this) && this->m_eventHP > 0 )
  {
    if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
    {
      v8 = (float)(*((int (__fastcall **)(Player *const))this->_vptr_Entity + 19))(this);
      if ( (float)((float)(int)(this->m_eventHP
                              * (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 20))(this))
                 * 0.0099999998) >= v8 )
      {
        if ( this->m_pMap )
          v2 = (Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
        else
          v2 = 0;
        pDungeon = v2;
        if ( !v2 )
          return;
        Dungeon::onPlayerHPEvent(pDungeon, this);
      }
    }
  }
  if ( Player::getPkValue(this) > 0 )
  {
    if ( curTick - this->m_lastPkValueTick > 999 )
    {
      CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 1072, 1);
      this->m_lastPkValueTick = curTick;
    }
    if ( CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 1072) > 299 )
    {
      Player::addPkValue(this, -1);
      CExtOperateLimit::Reset(&this->m_extOperateLimit, 1072);
    }
  }
  if ( curTick - this->m_lastPoolTick > 999 )
  {
    Now = Unit::getNow(this);
    if ( Player::getRecord(this, 1066) > 0 && Player::getRecord(this, 1066) < Now )
    {
      Player::updateRecord(this, 1066, 0);
      Player::recalcAttr(this, 0, 0);
    }
    Player::CheckLeaveCycleTower(this);
    Player::CheckEnterCycleTower(this);
    Player::CheckLevelWastelands(this);
    Player::CheckBeastShrinePoints(this);
    Player::CheckBeastShrineAutoKick(this);
    if ( Map::IsXinMoMap(this->m_pMap) )
    {
      Unit::getLocalNow(&time, this);
      if ( time.tm_hour <= 11 )
        Player::OnBackCity(this, 1, 1);
    }
    if ( !Unit::isAlive(this) && Map::CanAutoRevive(this->m_pMap) && Player::GetDieTick(this) > 0 )
    {
      DieTick = Player::GetDieTick(this);
      if ( curTick - DieTick > 179999 )
      {
        Player::FullHPAndSync(this);
        Player::moveToReviveRegion(this, 0);
      }
    }
    this->m_lastPoolTick = curTick;
  }
  if ( curTick - this->m_LastUpdateWastelands > 9999 )
  {
    Player::CheckAddWastelandsValue(this);
    Player::CheckAddBeastShrineValue(this);
    this->m_LastUpdateWastelands = this->m_lastPoolTick;
  }
  if ( Unit::isAlive(this) && Player::GetStartProtect(this) > 0 )
  {
    v6 = Unit::getNow(this);
    if ( v6 - Player::GetStartProtect(this) > 10 )
      Player::SetStartProtect(this, 0);
  }
}


#####################################
void __cdecl Player::minuteCheck(Player *const this, bool bSend)
{
  int32_t Record; // eax
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  CKaiFuHuoDong *v9; // rax
  CKaiFuHuoDong *v10; // rax
  tm localNow; // [rsp+10h] [rbp-60h] BYREF
  int32_t nowTime; // [rsp+50h] [rbp-20h]
  int32_t secondsPassed; // [rsp+54h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  nowTime = Unit::getNow(this);
  Unit::getLocalNow(&localNow, this);
  Record = Player::getRecord(this, 1002);
  secondsPassed = nowTime - Record;
  if ( nowTime - Record > 59 )
  {
    Player::updateRecord(this, 1002, nowTime);
    Player::UpdateGmGold(this);
  }
  if ( this->m_lastLocalNow.tm_min != localNow.tm_min )
  {
    Player::ResetJingLi(this);
    if ( this->m_pMap && Map::IsXinMoMap(this->m_pMap) && 60 * localNow.tm_hour + localNow.tm_min == 1435 )
    {
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x2D41u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, 1);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this);
        ConnId = Player::getConnId(this);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, ConnId, GateIndex, packet);
      }
    }
  }
  if ( this->m_lastLocalNow.tm_mday != localNow.tm_mday )
  {
    Player::onNewDayCome(this);
    v9 = Answer::Singleton<CKaiFuHuoDong>::instance();
    CKaiFuHuoDong::SendKaiFuHuoDongIcon(v9, this);
    v10 = Answer::Singleton<CKaiFuHuoDong>::instance();
    CKaiFuHuoDong::SendKaiFuPetIcon(v10, this);
    Player::SendCycleTowerInfo(this);
  }
  if ( this->m_lastLocalNow.tm_hour != 18 && localNow.tm_hour == 18 )
    Player::refeshKillerRecord(this);
  this->m_lastLocalNow = localNow;
}


#####################################
bool __cdecl Player::autoUpgradeLevel(Player *const this)
{
  int32_t v1; // edx
  bool upgrade; // [rsp+1Bh] [rbp-5h]
  int32_t oldLevel; // [rsp+1Ch] [rbp-4h]

  upgrade = 0;
  oldLevel = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  while ( Player::upgradeLevel(this, 1) )
    upgrade = 1;
  if ( upgrade )
  {
    v1 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
    Player::LevelUped(this, oldLevel, v1);
  }
  return upgrade;
}


#####################################
void __cdecl Player::LevelUped(Player *const this, int32_t OldLevel, int32_t NewLevel)
{
  int8_t ConnId; // bl
  DBService *v4; // rax
  DailyActivity *PlayerDailyActivity; // rax
  int32_t v6; // eax
  int32_t v7; // eax
  CfgData *v8; // rax
  int32_t ServerDiffDay; // eax
  int32_t v10; // edx
  int32_t v11; // eax
  CKaiFuHuoDong *v12; // rax
  int8_t m_connid; // bl
  DBService *v14; // rax
  const char *v15; // r12
  int32_t MapId; // ebx
  int v17; // eax
  DBService *v18; // rax
  char LogString[4096]; // [rsp+10h] [rbp-10F0h] BYREF
  level_up_log stu; // [rsp+1010h] [rbp-F0h] BYREF
  LogPlayerLevel logLevel; // [rsp+1050h] [rbp-B0h] BYREF
  Log360 Stu; // [rsp+1080h] [rbp-80h] BYREF
  _BYTE v25[16]; // [rsp+10B0h] [rbp-50h] BYREF
  _BYTE v26[16]; // [rsp+10C0h] [rbp-40h] BYREF
  _BYTE v27[16]; // [rsp+10D0h] [rbp-30h] BYREF
  std::string v28; // [rsp+10E0h] [rbp-20h] BYREF

  level_up_log::level_up_log(&stu);
  stu.log_Sid = Player::getSid(this);
  stu.log_time = Unit::getNow(this);
  Player::GetPassport((Player *const)v25);
  std::string::operator=(&stu.passport, v25);
  std::string::~string(v25);
  stu.cid = Player::getCid(this);
  Player::getName((const Player *const)v26);
  std::string::operator=(&stu.name, v26);
  std::string::~string(v26);
  stu.create_time = Player::getCreateTime(this);
  stu.level_up_time = Unit::getNow(this);
  stu.level = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  stu.Level_interval = Unit::getNow(this) - this->m_levelStartTime;
  ConnId = Player::getConnId(this);
  v4 = Answer::Singleton<DBService>::instance();
  DBService::AddPlatformLog(v4, ConnId, PLATFORM_LOG_DATA_TYPE::PLDT_LEVEL_UP, &stu);
  Player::SetLevelStartTime(this);
  PlayerDailyActivity = Player::GetPlayerDailyActivity(this);
  DailyActivity::OnLevelUp(PlayerDailyActivity);
  v6 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  CFunctionOpen::CheckFunctionOpne(&this->m_PlayerFunctionOpen, 0, v6);
  v7 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  CFunctionOpen::CheckFunctionOpenMailByLevel(&this->m_PlayerFunctionOpen, v7);
  v8 = Answer::Singleton<CfgData>::instance();
  ServerDiffDay = CfgData::getServerDiffDay(v8, SERVER_TYPE::SVT_NORMAL);
  CFunctionOpen::CheckFunctionOpenMailByKaiFuDay(&this->m_PlayerFunctionOpen, ServerDiffDay + 1);
  CTouZi::SendTouZiIcon(&this->m_PlayerTouZi);
  CExtCharTitle::OnLevelUp(&this->m_extCharTitle, this->m_chr.level);
  CExtCharTencent::SendTGPIcon(&this->m_extCharTencent);
  CExtCharTencent::SendBlueStoneIcon(&this->m_extCharTencent);
  CExtCharPet::OnLevelUp(&this->m_extCharPet);
  CVplan::sendSwVipIcon(&this->m_Vplan);
  CDaTingReward::SendDaTingIcon(&this->m_CDaTingReward);
  CTouZi::SendTouZiIcon(&this->m_PlayerTouZi);
  Player::recalcAttr(this, 1, 0);
  (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
  if ( OldLevel <= 55 && NewLevel > 55 )
  {
    v10 = Unit::getNow(this) + 1800;
    Player::updateRecord(this, 37504, v10);
  }
  v11 = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  CSevenDayTask::UpdateTaskState(&this->m_CSevenDayTask, 1, v11, 1);
  CSevenDayTask::OpenSevenDayTask(&this->m_CSevenDayTask);
  Player::SetNeedSyncAround(this);
  Player::sendUpdateSocialPlayerInfo(this, PlayerInfoIndex::PII_LEVEL, this->m_chr.level);
  v12 = Answer::Singleton<CKaiFuHuoDong>::instance();
  CKaiFuHuoDong::SendKaiFuHuoDongIcon(v12, this);
  CExtOperateLimit::Reset(&this->m_extOperateLimit, 2045);
  CTestServerReward::SendTestServerIcon(&this->m_CTestServerReward);
  memset(&logLevel, 0, sizeof(logLevel));
  logLevel.cid = this->m_chr.cid;
  snprintf(logLevel.name, 0x1Eu, this->m_chr.name);
  logLevel.level = this->m_chr.level;
  logLevel.time = Unit::getNow(this);
  m_connid = this->m_connid;
  v14 = Answer::Singleton<DBService>::instance();
  DBService::logLevelUp(v14, m_connid, &logLevel);
  memset(&Stu, 0, sizeof(Stu));
  std::string::string(&Stu.Interface);
  std::string::string(&Stu.passport);
  std::string::string(&Stu.LogString);
  std::string::operator=(&Stu, "upgrade");
  Stu.UseSid = Player::getSid(this);
  Player::GetPassport((Player *const)v27);
  std::string::operator=(&Stu.passport, v27);
  std::string::~string(v27);
  Stu.Cid = Player::getCid(this);
  memset(LogString, 0, sizeof(LogString));
  Player::getName((const Player *const)&v28);
  v15 = (const char *)std::string::c_str(&v28);
  MapId = StaticObj::getMapId(this);
  v17 = (*((__int64 (__fastcall **)(Player *const, Player *const))this->_vptr_Entity + 9))(this, this);
  snprintf(LogString, 0xFFFu, "level=%d&map_id=%d&reason=&rolename=%s", v17, MapId, v15);
  std::string::~string(&v28);
  std::string::operator=(&Stu.LogString, LogString);
  LOBYTE(MapId) = this->m_connid;
  v18 = Answer::Singleton<DBService>::instance();
  DBService::log360(v18, MapId, &Stu);
  Log360::~Log360(&Stu);
  level_up_log::~level_up_log(&stu);
}


#####################################
bool __cdecl Player::upgradeLevel(Player *const this, bool bAuto)
{
  int32_t level; // ebx
  CfgData *v3; // rax
  int64_t max_exp; // rax
  int64_t exp; // rax
  CfgLevelExp *pCfgLevelExp; // [rsp+10h] [rbp-20h]
  int32_t maxLevel; // [rsp+1Ch] [rbp-14h]

  level = this->m_chr.level;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgLevelExp = CfgData::getUpgradeExp(v3, level);
  if ( !pCfgLevelExp )
    return 0;
  if ( pCfgLevelExp->upgrade_exp > 0 )
  {
    maxLevel = Player::GetMaxLevel(this);
    if ( this->m_chr.exp < pCfgLevelExp->upgrade_exp || this->m_chr.level >= maxLevel )
    {
      if ( this->m_chr.exp <= pCfgLevelExp->max_exp )
        exp = this->m_chr.exp;
      else
        exp = pCfgLevelExp->max_exp;
      this->m_chr.exp = exp;
      return 0;
    }
    else
    {
      ++this->m_chr.level;
      this->m_chr.exp -= pCfgLevelExp->upgrade_exp;
      return 1;
    }
  }
  else
  {
    if ( this->m_chr.exp <= pCfgLevelExp->max_exp )
      max_exp = this->m_chr.exp;
    else
      max_exp = pCfgLevelExp->max_exp;
    this->m_chr.exp = max_exp;
    return 0;
  }
}


#####################################
int32_t __cdecl Player::getShiZhuangWeapon(Player *const this)
{
  return CShiZhuang::GetWearId(&this->m_extShiZhuang, 0);
}


#####################################
int32_t __cdecl Player::getShiZhuangClothes(Player *const this)
{
  return CShiZhuang::GetWearId(&this->m_extShiZhuang, 1);
}


#####################################
int32_t __cdecl Player::getShiZhuangFeet(Player *const this)
{
  return CShiZhuang::GetWearId(&this->m_extShiZhuang, 2);
}


#####################################
void __cdecl Player::SetLevelStartTime(Player *const this)
{
  this->m_chr.level_stay_time = 0;
  this->m_levelStartTime = Unit::getNow(this);
}


#####################################
int32_t __cdecl Player::doTeleportActivity(Player *const this, int32_t aid)
{
  CfgData *v3; // rax
  int32_t id; // ebx
  CActivityManager *v5; // rax
  CfgData *v6; // rax
  int32_t target_mapid; // ebx
  MapManager *v8; // rax
  Position pos; // [rsp+10h] [rbp-40h]
  CfgActivity *activityInfo; // [rsp+20h] [rbp-30h]
  int32_t nReginId; // [rsp+2Ch] [rbp-24h]
  const CfgMapRegion *pCfgRegion; // [rsp+30h] [rbp-20h]
  Map *pTargetMap; // [rsp+38h] [rbp-18h]

  if ( !this->m_pMap )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  activityInfo = CfgData::getActivity(v3, aid);
  if ( !activityInfo || !activityInfo->target_mapid )
    return 10002;
  id = activityInfo->id;
  v5 = Answer::Singleton<CActivityManager>::instance();
  if ( !CActivityManager::IsActivityRunning(v5, id) )
    return 10002;
  if ( !std::vector<int>::size(&activityInfo->target_regiona) )
    return 10002;
  nReginId = Player::getActivityBirthRegion(this, &activityInfo->target_regiona);
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgRegion = CfgData::getMapRegion(v6, nReginId);
  if ( !pCfgRegion )
    return 10002;
  target_mapid = activityInfo->target_mapid;
  v8 = Answer::Singleton<MapManager>::instance();
  pTargetMap = MapManager::GetMap(v8, target_mapid);
  if ( !pTargetMap )
    return 10002;
  pos = Map::getRandomWalkablePositionInRegion(pTargetMap, pCfgRegion);
  if ( pos == -1 )
    return 10002;
  if ( this->m_pMap != pTargetMap )
    return Player::switchMap(this, pTargetMap, pos.x, pos.y, 1);
  Unit::instantMove(this, pos.x, pos.y, InstanceMoveReason::IMR_ACTIVITY, 0);
  return 0;
}


#####################################
void __cdecl Player::FullHPAndSync(Player *const this)
{
  (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
  Unit::FillMP(this, 100);
  Player::SetDieTick(this);
  Unit::setNeedSync(this);
}


#####################################
void __cdecl Player::safeRevive(Player *const this)
{
  int32_t Now; // edx

  if ( !Unit::isAlive(this) )
  {
    (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
    Player::SetDieTick(this);
    Unit::FillMP(this, 100);
    Now = Unit::getNow(this);
    Player::SetStartProtect(this, Now);
    (*((void (__fastcall **)(Player *const))this->_vptr_Entity + 30))(this);
    Unit::setNeedSyncSelf(this);
    if ( StaticObj::InActivity(this) )
      Player::moveToReviveRegion(this, 1);
    else
      Player::moveToReviveRegion(this, 0);
    if ( this->m_pMap )
      (*((void (__fastcall **)(Map *, Player *const, __int64))this->m_pMap->_vptr_Map + 12))(this->m_pMap, this, 1);
  }
}


#####################################
void __cdecl Player::onDamageEvent(Player *const this, UnitHandle target, int32_t attackValue)
{
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  CExtCharPet *CharPet; // rax
  UnitHandle PetUnit; // [rsp+20h] [rbp-40h] BYREF
  Player *player; // [rsp+30h] [rbp-30h]
  CObjPet *pPet; // [rsp+38h] [rbp-28h]
  CObjPet *pPet_0; // [rsp+40h] [rbp-20h]

  switch ( target.type )
  {
    case 1:
      RunnerId = StaticObj::GetRunnerId(this);
      v4 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v4, target.id, RunnerId, 1);
      if ( player )
      {
        CharPet = Player::GetCharPet(player);
        pPet = CExtCharPet::GetFightPet(CharPet);
        if ( pPet )
        {
          UnitHandle::UnitHandle(&PetUnit, 0, 0);
          UnitHandle::clear(&PetUnit);
          PetUnit.type = 4;
          PetUnit.id = CObjPet::GetPetId(pPet);
          CExtCharPet::AddTarget(&this->m_extCharPet, PetUnit, 0);
        }
      }
      break;
    case 4:
      target.type = 4;
      CExtCharPet::AddTarget(&this->m_extCharPet, target, 1);
      break;
    case 2:
      pPet_0 = CExtCharPet::GetFightPet(&this->m_extCharPet);
      if ( pPet_0 )
      {
        if ( CObjPet::GetAiState(pPet_0) == 1 )
        {
          target.type = 2;
          CExtCharPet::AddTarget(&this->m_extCharPet, target, 1);
        }
      }
      break;
  }
}


#####################################
void __cdecl Player::onDamagedEvent(Player *const this, UnitHandle launcher, int32_t attackValue)
{
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  CExtCharPet *CharPet; // rax
  int32_t v6; // r12d
  GameService *v7; // rax
  FamilyId_t FamilyId; // rax
  CExtFightChecker *FightChecker; // rax
  UnitHandle PetUnit; // [rsp+20h] [rbp-50h] BYREF
  Player *player; // [rsp+38h] [rbp-38h]
  CObjPet *pPet; // [rsp+40h] [rbp-30h]
  CObjPet *pPet_0; // [rsp+48h] [rbp-28h]
  CObjPet *pPet_1; // [rsp+50h] [rbp-20h]
  int8_t AiState; // [rsp+5Fh] [rbp-11h]

  if ( this->m_pMap )
  {
    Player::SetInFight(this);
    if ( launcher.type == 1 || launcher.type == 4 )
      Player::SetInPvP(this);
    player = 0;
    if ( launcher.type == 1 )
    {
      Player::PkModeTiShi(this);
      RunnerId = StaticObj::GetRunnerId(this);
      v4 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v4, launcher.id, RunnerId, 1);
      if ( player )
      {
        CharPet = Player::GetCharPet(player);
        pPet = CExtCharPet::GetFightPet(CharPet);
        if ( pPet )
        {
          UnitHandle::UnitHandle(&PetUnit, 0, 0);
          UnitHandle::clear(&PetUnit);
          PetUnit.type = 4;
          PetUnit.id = CObjPet::GetPetId(pPet);
          CExtCharPet::AddTarget(&this->m_extCharPet, PetUnit, 0);
        }
      }
    }
    else if ( launcher.type == 4 )
    {
      v6 = StaticObj::GetRunnerId(this);
      v7 = Answer::Singleton<GameService>::instance();
      pPet_0 = GameService::getPet(v7, launcher.id, v6);
      if ( pPet_0 )
        player = CObjPet::GetPlayer(pPet_0);
    }
    if ( launcher.type != 1 )
    {
      pPet_1 = CExtCharPet::GetFightPet(&this->m_extCharPet);
      if ( pPet_1 )
      {
        AiState = CObjPet::GetAiState(pPet_1);
        if ( AiState == 1 )
          CExtCharPet::AddTarget(&this->m_extCharPet, launcher, 1);
      }
    }
    if ( player
      && !StaticObj::InPrison(this)
      && !Map::IsPVPMap(this->m_pMap)
      && !CExtFightChecker::IsBuleName(&this->m_extFightChecker)
      && Player::getPkValue(this) <= 100
      && Player::getPkValue(player) <= 100 )
    {
      FamilyId = Player::getFamilyId(player);
      if ( !CExtCharFamily::IsDeclareWarFamily(&this->m_extCharFamily, FamilyId) && !StaticObj::InActivity(this) )
      {
        FightChecker = Player::GetFightChecker(player);
        CExtFightChecker::ChangeBuleName(FightChecker, 1);
      }
    }
  }
}


#####################################
int32_t __cdecl Player::OnAskBossInfo(Player *const this, Answer::NetPacket *inPacket)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  CWorldBoss *v5; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int8_t BossType; // [rsp+17h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !inPacket )
    return 2;
  BossType = Answer::NetPacket::readInt8(inPacket);
  m_connid = this->m_connid;
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x2CB2u);
  if ( !packet )
    return 2;
  v5 = Answer::Singleton<CWorldBoss>::instance();
  CWorldBoss::PacketBossInfo(v5, packet, BossType);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  m_cgindex = this->m_cgindex;
  v8 = this->m_connid;
  v9 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v9, v8, m_cgindex, packet);
  return 0;
}


#####################################
int32_t __cdecl Player::OnRequestActivityInfo(Player *const this, Answer::NetPacket *inPacket)
{
  CActivityManager *v3; // rax
  int32_t nActivityId; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  nActivityId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SendActivityInfo(v3, this, nActivityId);
  return 0;
}


#####################################
int32_t __cdecl Player::OnRequestActivityRankInfo(Player *const this, Answer::NetPacket *inPacket)
{
  CActivityManager *v3; // rax
  int32_t nActivityId; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  nActivityId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SendActivityRankInfo(v3, this, nActivityId);
  return 0;
}


#####################################
int32_t __cdecl Player::OnActivityWorldBossGuWu(Player *const this, Answer::NetPacket *inPacket)
{
  int8_t Int8; // r12
  CActivityManager *v4; // rax
  int32_t nActivityId; // [rsp+18h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  nActivityId = Answer::NetPacket::readInt32(inPacket);
  Int8 = Answer::NetPacket::readInt8(inPacket);
  v4 = Answer::Singleton<CActivityManager>::instance();
  return CActivityManager::OnActivityWorldBossGuWu(v4, this, nActivityId, Int8);
}


#####################################
int32_t __cdecl Player::OnActivityGetDailyReward(Player *const this, Answer::NetPacket *inPacket)
{
  CActivityManager *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t nActivityId; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nActivityId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CActivityManager>::instance();
  if ( CActivityManager::GiveDailyReward(v3, this, nActivityId) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nActivityId);
  return 0;
}


#####################################
int32_t __cdecl Player::OnActivityApplyCityWar(Player *const this, Answer::NetPacket *inPacket)
{
  FamilyId_t FamilyId; // r12
  CActivityManager *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax
  int8_t nType; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( Player::getFamilyId(this) <= 0 )
    return 10002;
  if ( Player::getFamilyPosition(this) != 3 )
    return 10002;
  FamilyId = Player::getFamilyId(this);
  v4 = Answer::Singleton<CActivityManager>::instance();
  if ( !CActivityManager::ApplyCityWar(v4, this, FamilyId, nType) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, m_connid, m_cgindex, Proc, 0);
  return 0;
}


#####################################
void __cdecl Player::TiShiInfo(Player *const this, int32_t TiShiId, int32_t Pos)
{
  int8_t m_connid; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, m_connid, Answer::PackType::PACK_DISPATCH, 0x2C97u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, Pos);
    Answer::NetPacket::writeInt32(packet, TiShiId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::AddDaTiExp(Player *const this, int32_t Index, int8_t Result)
{
  CFestivalDoubleEleven *v3; // rax
  int Exp; // [rsp+10h] [rbp-20h]
  int64_t Expa; // [rsp+10h] [rbp-20h]
  int32_t Level; // [rsp+1Ch] [rbp-14h]

  Level = (*((__int64 (__fastcall **)(Player *const))this->_vptr_Entity + 9))(this);
  if ( Level > 80 )
  {
    if ( Level > 120 )
      Exp = 20000 * ((Level - 120) >> 3) + 2400000;
    else
      Exp = 20000 * Level;
  }
  else
  {
    Exp = 1600000;
  }
  Expa = (unsigned int)(int)(float)(std::pow((float)Index / 30.0, 0.34999999) * (float)Exp);
  if ( Result == 2 )
    Expa /= 2LL;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::IsInTime(v3, FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI) )
    Expa *= 2LL;
  Player::addExp(this, Expa, 0, 1);
}


#####################################
int64_t __cdecl Player::GetCurrency(const Player *const this, const CURRENCY_TYPE nType)
{
  return CExtCurrency::GetCurrency(&this->m_extCurrency, nType);
}


#####################################
bool __cdecl Player::AddCurrency(
        Player *const this,
        const CURRENCY_TYPE nType,
        int64_t nVal,
        CURRENCY_CHANGE_REASON opWay,
        int64_t nParam)
{
  return CExtCurrency::AddCurrency(&this->m_extCurrency, nType, nVal, opWay, nParam);
}


#####################################
bool __cdecl Player::DecCurrency(
        Player *const this,
        const CURRENCY_TYPE nType,
        int64_t nVal,
        CURRENCY_CHANGE_REASON opWay,
        int64_t nParam)
{
  return CExtCurrency::DecCurrency(&this->m_extCurrency, nType, nVal, opWay, nParam);
}


#####################################
int32_t __cdecl Player::GetProtectTime(Player *const this)
{
  int32_t m_StartProtect; // ebx

  if ( !this->m_StartProtect )
    return 0;
  m_StartProtect = this->m_StartProtect;
  return m_StartProtect - Unit::getNow(this) + 10;
}


#####################################
void __cdecl Player::SetStartProtect(Player *const this, int32_t ProtectTime)
{
  if ( this->m_StartProtect != ProtectTime )
  {
    this->m_StartProtect = ProtectTime;
    Player::SetNeedSyncAround(this);
  }
}


#####################################
int32_t __cdecl Player::OnRandPos(Player *const this)
{
  int32_t MapId; // ebx
  TileManager *v5; // rax
  ChrTask *Task; // rax
  Position Pos; // [rsp+10h] [rbp-20h]
  const Map *pMap; // [rsp+18h] [rbp-18h]

  if ( StaticObj::InDungeon(this) || StaticObj::InActivity(this) || Player::IsInStall(this) )
    return 2;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 10002;
  }
  pMap = StaticObj::getMap(this);
  if ( !pMap )
    return 2;
  if ( (*((unsigned __int8 (__fastcall **)(const Map *))pMap->_vptr_Map + 24))(pMap) != 1 )
    return 2;
  MapId = Map::GetMapId(pMap);
  v5 = Answer::Singleton<TileManager>::instance();
  Pos = TileManager::getRandomWalkablePosition(v5, MapId);
  if ( Pos.x == -1 || Pos.y == -1 )
    return 2;
  Unit::instantMove(this, Pos.x, Pos.y, InstanceMoveReason::IMR_SUI_JI, 0);
  Task = Player::GetTask(this);
  ChrTask::updateTaskUseItem(Task, 7079, 1);
  Player::BreakGather(this, 1);
  return 0;
}


#####################################
int32_t __cdecl Player::OnBackCity(Player *const this, bool bMust, bool bCleanXinMoBag)
{
  GameService *v6; // rax
  int v7; // eax
  CfgData *v8; // rax
  int32_t mapid; // ebx
  CfgData *v10; // rax
  int32_t v11; // ebx
  MapManager *v12; // rax
  Position pos; // [rsp+10h] [rbp-40h]
  int32_t nMainCity; // [rsp+24h] [rbp-2Ch]
  CfgMapRegion *pCfgMapRegion; // [rsp+28h] [rbp-28h]
  Map *pTargetMap; // [rsp+38h] [rbp-18h]

  if ( !this->m_pMap || StaticObj::InDungeon(this) || StaticObj::InActivity(this) || Player::IsInStall(this) )
    return 2;
  if ( !bMust
    && (Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
     || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN)) )
  {
    return 10002;
  }
  if ( Map::IsXinMoMap(this->m_pMap) )
  {
    nMainCity = 20003;
  }
  else
  {
    v6 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v6) == 9 )
      v7 = 20002;
    else
      v7 = 20001;
    nMainCity = v7;
  }
  v8 = Answer::Singleton<CfgData>::instance();
  pCfgMapRegion = CfgData::getMapRegion(v8, nMainCity);
  if ( !pCfgMapRegion )
    return 2;
  mapid = pCfgMapRegion->mapid;
  v10 = Answer::Singleton<CfgData>::instance();
  if ( !CfgData::getMap(v10, mapid) )
    return 2;
  v11 = pCfgMapRegion->mapid;
  v12 = Answer::Singleton<MapManager>::instance();
  pTargetMap = MapManager::GetMap(v12, v11);
  if ( !pTargetMap )
    return 2;
  pos = Map::getRandomWalkablePositionInRegion(pTargetMap, pCfgMapRegion);
  if ( pos.x < 0 || pos.y < 0 )
    return 2;
  if ( Map::IsXinMoMap(this->m_pMap) && bCleanXinMoBag )
    CXinMo::CleanXinMoBag(&this->m_CXinMo);
  if ( this->m_pMap == pTargetMap )
    Unit::instantMove(this, pos.x, pos.y, InstanceMoveReason::IMR_BACK_CITY, 0);
  else
    Player::switchMap(this, pTargetMap, pos.x, pos.y, 1);
  ChrTask::updateTaskCount(&this->m_task, 25, 0);
  this->m_isBackCity = 0;
  return 0;
}


#####################################
void __cdecl Player::SendHDIcon(Player *const this)
{
  CActivityManager *v1; // rax
  CKaiFuHuoDong *v2; // rax
  CKaiFuHuoDong *v3; // rax
  COpenBeta *v4; // rax
  CUniteServer *v5; // rax
  CUniteServer *v6; // rax
  CFestivalDoubleEleven *v7; // rax
  CFestivalActivity *v8; // rax
  CFestivalDoubleEleven *v9; // rax
  CZongHeYunYingHD *v10; // rax
  CKiaFuRecharge *v11; // rax
  CKiaFuRecharge *v12; // rax
  COutLinkFestival *v13; // rax
  CWorldBoss *v14; // rax
  CFestivalDoubleEleven *v15; // rax
  COpenBeta *v16; // rax
  bool v17; // bl
  CfgData *v18; // rax
  int32_t nId; // ebx
  CfgData *v20; // rax
  ShowIcon *v21; // rax
  int8_t m_connid; // bl
  GameService *v23; // rax
  ShowIcon *v24; // rax
  ShowIcon *v25; // rax
  ShowIcon *v26; // rax
  ShowIcon *v27; // rax
  ShowIcon *v28; // rax
  ShowIcon *v29; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v32; // bl
  GameService *v33; // rax
  tm localnow; // [rsp+10h] [rbp-100h] BYREF
  std::_List_iterator<ShowIcon> it; // [rsp+50h] [rbp-C0h] BYREF
  std::_List_iterator<ShowIcon> iter; // [rsp+60h] [rbp-B0h] BYREF
  IconStateList showIcons; // [rsp+70h] [rbp-A0h] BYREF
  ShowIcon stu; // [rsp+80h] [rbp-90h] BYREF
  IconStateList IconList; // [rsp+A0h] [rbp-70h] BYREF
  std::string __lhs; // [rsp+B0h] [rbp-60h] BYREF
  std::_List_iterator<ShowIcon> __x; // [rsp+C0h] [rbp-50h] BYREF
  std::string platform; // [rsp+D0h] [rbp-40h] BYREF
  std::_List_iterator<ShowIcon> v43; // [rsp+E0h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+F0h] [rbp-20h]
  int32_t nSize; // [rsp+FCh] [rbp-14h]

  std::list<ShowIcon>::list(&IconList);
  Unit::getLocalNow(&localnow, this);
  v1 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::GetActicityIconState(v1, &IconList, this);
  DailyActivity::GetHuoDongDaTingIcon(&this->m_PlayerDailyActivity, &IconList);
  DailyActivity::GetJiangLiDaTingIcon(&this->m_PlayerDailyActivity, &IconList);
  DailyActivity::GetSearchBackIcon(&this->m_PlayerDailyActivity, &IconList);
  DailyActivity::GetSevenDayLoginIcon(&this->m_PlayerDailyActivity, &IconList);
  CYunYingHD::GetTeHuiIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetShouChongIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetEveryDayChongZhiIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetTotalChongZhiIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetMobilePhoneGiftIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetAdultGiftIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetSuperMemberIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetShouChongIconState(&this->m_PlayerYunYingHD, &IconList);
  CYunYingHD::GetZeroBuyPetIconState(&this->m_PlayerYunYingHD, &IconList);
  CTouZi::GetTouZiIconState(&this->m_PlayerTouZi, &IconList);
  CQiFu::GetQiFuStu(&this->m_PlayerQiFu, &IconList);
  CWan360::GetGameAppIconState(&this->m_Wan360, &IconList);
  CWan360::GetJiaShuQiuIconState(&this->m_Wan360, &IconList);
  CWan360::GetWeiXinIconState(&this->m_Wan360, &IconList);
  CWan360::GetSpeed360State(&this->m_Wan360, &IconList);
  CWan360::GetSouGouSkinIconState(&this->m_Wan360, &IconList);
  CVplan::GetVplanIconState(&this->m_Vplan, &IconList);
  CVplan::GetSwVipIconState(&this->m_Vplan, &IconList);
  CVplan::GetSwVipBarIconState(&this->m_Vplan, &IconList);
  CVplan::GetYYVipIconState(&this->m_Vplan, &IconList);
  CVplan::GetLuDaShiIconState(&this->m_Vplan, &IconList);
  CVplan::GetSgDownLoadIocnState(&this->m_Vplan, &IconList);
  CVplan::GetXunLeiIconState(&this->m_Vplan, &IconList);
  ChouJiang::GetChouJiangStu(&this->m_PlayerChouJiang, &IconList);
  CSpecialEquip::GetSpecialEquipIcon(&this->m_CSpecialEquip, &IconList);
  CLevelRefining::GetIcon(&this->m_CLevelRefining, &IconList);
  CBossKilledReward::GetBossKilledIcon(&this->m_CBossKilledReward, &IconList);
  CFunctionOpen::GetSysOpenIcon(&this->m_PlayerFunctionOpen, &IconList);
  CHuoYueDu::GetHuoYueDuIcon(&this->m_PlayerHuoYueDu, &IconList);
  CSuperTeHui::GetJewelPavilionIcon(&this->m_CSuperTeHui, &IconList);
  CSuperTeHui::GetSuperTeHuiIcon(&this->m_CSuperTeHui, &IconList);
  CSuperTeHui::GetShangRenIcon(&this->m_CSuperTeHui, &IconList);
  CDaTingReward::GetDaTingIconState(&this->m_CDaTingReward, &IconList);
  CDaTingReward::GetMiniClientIconState(&this->m_CDaTingReward, &IconList);
  CDaTingReward::GetPlatformVipIconState(&this->m_CDaTingReward, &IconList);
  CDaTingReward::GetPlatformRewardIconState(&this->m_CDaTingReward, &IconList);
  Player::GetMiniClientIcon(this, &IconList);
  Player::GetFamilyWarIcon(this, &IconList);
  v2 = Answer::Singleton<CKaiFuHuoDong>::instance();
  CKaiFuHuoDong::GetKaiFuHuoDongIcon(v2, this, &IconList);
  v3 = Answer::Singleton<CKaiFuHuoDong>::instance();
  CKaiFuHuoDong::GetKaiFuPetIcon(v3, this, &IconList);
  v4 = Answer::Singleton<COpenBeta>::instance();
  COpenBeta::GetIconState(v4, this, &IconList);
  v5 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::GetIconState(v5, this, &IconList);
  v6 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::GetSpiderQueenIconState(v6, &IconList);
  v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::GetIconState(v7, this, &IconList);
  v8 = Answer::Singleton<CFestivalActivity>::instance();
  CFestivalActivity::GetIconState(v8, this, &IconList);
  v9 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::GetWorldBossIconState(v9, &IconList);
  v10 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::GetIconState(v10, this, &IconList);
  v11 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::GetIconState(v11, this, &IconList);
  v12 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::GetChouJiangIconState(v12, this, &IconList);
  v13 = Answer::Singleton<COutLinkFestival>::instance();
  COutLinkFestival::GetIconState(v13, &IconList);
  if ( CFunctionOpen::IsOpened(&this->m_PlayerFunctionOpen, 53) )
  {
    v14 = Answer::Singleton<CWorldBoss>::instance();
    CWorldBoss::GetWorldBossIcon(v14, &IconList);
  }
  CExtCharHallOfFame::GetIconState(&this->m_extCharHallOfFame, &IconList);
  Player::GetNewEquipDungeonIconState(this, &IconList);
  v15 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::GetMoYuShiJieIconState(v15, &IconList);
  CBlackMarket::GetMarketIconState(&this->m_extBlackMarket, &IconList);
  CExtCharTencent::GetYellowStoneIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetFriendIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetQZoneIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetQQGameIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetYellowNewerIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetBlueStoneIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetBluePayIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetSevenDayLoginIcon(&this->m_extCharTencent, &IconList);
  CExtCharTencent::GetTGPIcon(&this->m_extCharTencent, &IconList);
  Player::Get360TGPIconState(this, &IconList);
  CGuardPrivilege::GetIconState(&this->m_CGuardPrivilege, &IconList);
  Player::GetDungeonHallIcon(this, &IconList);
  Player::GetQuestionAnswerIcon(this, &IconList);
  Player::GetJoinQQIcon(this, &IconList);
  CMonthlyChouJiang::GetIcon(&this->m_CMonthlyChouJiang, &IconList);
  CTestServerReward::GetTestServerIcon(&this->m_CTestServerReward, &IconList);
  CSevenDayTask::GetIcon(&this->m_CSevenDayTask, &IconList);
  v16 = Answer::Singleton<COpenBeta>::instance();
  COpenBeta::GetBossIconState(v16, &IconList);
  *(_QWORD *)&stu.nId = 0x200000020LL;
  *(_QWORD *)&stu.nLeftTime = 0;
  *(_QWORD *)&stu.nIconRight = 0;
  std::list<ShowIcon>::push_back(&IconList, &stu);
  stu.nId = 1062;
  stu.nState = 2;
  std::list<ShowIcon>::push_back(&IconList, &stu);
  stu.nId = 141;
  stu.nState = 2;
  std::list<ShowIcon>::push_back(&IconList, &stu);
  Player::GetPlatform((const Player *const)&__lhs);
  v17 = std::operator==<char>(&__lhs, "9377");
  std::string::~string(&__lhs);
  if ( v17 )
  {
    v18 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v18, SERVER_TYPE::SVT_NORMAL) <= 9 )
    {
      stu.nId = 1111;
      stu.nState = 2;
      std::list<ShowIcon>::push_back(&IconList, &stu);
    }
  }
  std::list<ShowIcon>::list(&showIcons);
  for ( iter._M_node = std::list<ShowIcon>::begin(&IconList)._M_node; ; std::_List_iterator<ShowIcon>::operator++(&iter) )
  {
    __x._M_node = std::list<ShowIcon>::end(&IconList)._M_node;
    if ( !std::_List_iterator<ShowIcon>::operator!=(&iter, &__x) )
      break;
    Player::GetPlatform((const Player *const)&platform);
    nId = std::_List_iterator<ShowIcon>::operator->(&iter)->nId;
    v20 = Answer::Singleton<CfgData>::instance();
    LOBYTE(nId) = CfgData::IsShowIcon(v20, nId, &platform);
    std::string::~string(&platform);
    if ( (_BYTE)nId )
    {
      v21 = std::_List_iterator<ShowIcon>::operator*(&iter);
      std::list<ShowIcon>::push_back(&showIcons, v21);
    }
  }
  m_connid = this->m_connid;
  v23 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v23, m_connid, Answer::PackType::PACK_DISPATCH, 0x2CC2u);
  if ( packet )
  {
    nSize = std::list<ShowIcon>::size(&showIcons);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::list<ShowIcon>::begin(&showIcons)._M_node; ; std::_List_iterator<ShowIcon>::operator++(&it) )
    {
      v43._M_node = std::list<ShowIcon>::end(&showIcons)._M_node;
      if ( !std::_List_iterator<ShowIcon>::operator!=(&it, &v43) )
        break;
      v24 = std::_List_iterator<ShowIcon>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v24->nId);
      v25 = std::_List_iterator<ShowIcon>::operator->(&it);
      Answer::NetPacket::writeInt8(packet, v25->nState);
      v26 = std::_List_iterator<ShowIcon>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v26->nLeftTime);
      v27 = std::_List_iterator<ShowIcon>::operator->(&it);
      Answer::NetPacket::writeInt8(packet, v27->nIconLeft);
      v28 = std::_List_iterator<ShowIcon>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v28->nIconRight);
      v29 = std::_List_iterator<ShowIcon>::operator->(&it);
      Answer::NetPacket::writeInt8(packet, v29->nEffects);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v32 = this->m_connid;
    v33 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v33, v32, m_cgindex, packet);
  }
  std::list<ShowIcon>::~list(&showIcons);
  std::list<ShowIcon>::~list(&IconList);
}


#####################################
void __cdecl Player::Get360TGPIconState(Player *const this, IconStateList *const iconList)
{
  bool v2; // bl
  ShowIcon icon; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  Player::GetPlatform((const Player *const)&__lhs);
  v2 = std::operator!=<char>(&__lhs, "w360");
  std::string::~string(&__lhs);
  if ( !v2 )
  {
    *(_QWORD *)&icon.nId = 0x200000050LL;
    *(_QWORD *)&icon.nLeftTime = 0;
    *(_QWORD *)&icon.nIconRight = 0;
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
void __cdecl Player::GetNewEquipDungeonIconState(Player *const this, IconStateList *const iconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  *(_QWORD *)&icon.nId = 0x200000025LL;
  *(_QWORD *)&icon.nLeftTime = 0;
  *(_DWORD *)&icon.nEffects = 0;
  icon.nIconRight = Player::getDungeonLeftTimes(this, 3010);
  std::list<ShowIcon>::push_back(iconList, &icon);
}


#####################################
void __cdecl Player::SendNewEquipDungeonIconState(Player *const this)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  *(_QWORD *)&icon.nId = 0x200000025LL;
  *(_QWORD *)&icon.nLeftTime = 0;
  *(_DWORD *)&icon.nEffects = 0;
  icon.nIconRight = Player::getDungeonLeftTimes(this, 3010);
  Player::SendIconState(this, &icon);
}


#####################################
void __cdecl Player::GetDungeonHallIcon(Player *const this, IconStateList *const iconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( CFunctionOpen::IsOpened(&this->m_PlayerFunctionOpen, 167) )
  {
    Player::GetDungeonHallIconState(&icon, this);
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
void __cdecl Player::SendDungeonHallIcon(Player *const this)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  Player::GetDungeonHallIconState(&icon, this);
  Player::SendIconState(this, &icon);
}


#####################################
void __cdecl Player::GetQuestionAnswerIcon(Player *const this, IconStateList *const iconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( CFunctionOpen::IsOpened(&this->m_PlayerFunctionOpen, 173) )
  {
    Player::GetQuestionAnswerIconState(&icon, this);
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
void __cdecl Player::SendQuestionAnswerIcon(Player *const this)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  Player::GetQuestionAnswerIconState(&icon, this);
  Player::SendIconState(this, &icon);
}


#####################################
void __cdecl Player::sendJoinQQIcon(Player *const this)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  Player::GetJoinQQIconState(&icon, this);
  Player::SendIconState(this, &icon);
}


#####################################
void __cdecl Player::GetJoinQQIcon(Player *const this, IconStateList *const iconList)
{
  char v2; // r12
  char v3; // r13
  char v4; // r14
  bool v5; // al
  bool v6; // r15
  ShowIcon icon; // [rsp+20h] [rbp-90h] BYREF
  std::string __lhs; // [rsp+40h] [rbp-70h] BYREF
  std::string v9; // [rsp+50h] [rbp-60h] BYREF
  std::string v10; // [rsp+60h] [rbp-50h] BYREF
  std::string v11; // [rsp+70h] [rbp-40h] BYREF

  v2 = 0;
  v3 = 0;
  v4 = 0;
  Player::GetPlatform((const Player *const)&__lhs);
  v5 = 1;
  if ( !std::operator==<char>(&__lhs, "w360") )
  {
    Player::GetPlatform((const Player *const)&v9);
    v2 = 1;
    if ( !std::operator==<char>(&v9, "2217") )
    {
      Player::GetPlatform((const Player *const)&v10);
      v3 = 1;
      if ( !std::operator==<char>(&v10, "7youxi") )
      {
        Player::GetPlatform((const Player *const)&v11);
        v4 = 1;
        if ( !std::operator==<char>(&v11, "ledu") )
          v5 = 0;
      }
    }
  }
  v6 = v5;
  if ( v4 )
    std::string::~string(&v11);
  if ( v3 )
    std::string::~string(&v10);
  if ( v2 )
    std::string::~string(&v9);
  std::string::~string(&__lhs);
  if ( v6 && CFunctionOpen::IsOpened(&this->m_PlayerFunctionOpen, 195) )
  {
    Player::GetJoinQQIconState(&icon, this);
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
void __cdecl Player::SendIconState(Player *const this, const ShowIcon *const icon)
{
  int32_t nId; // ebx
  CfgData *v3; // rax
  int8_t m_connid; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int16_t m_cgindex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::string platform; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  Player::GetPlatform((const Player *const)&platform);
  nId = icon->nId;
  v3 = Answer::Singleton<CfgData>::instance();
  LOBYTE(nId) = !CfgData::IsShowIcon(v3, nId, &platform);
  std::string::~string(&platform);
  if ( !(_BYTE)nId )
  {
    m_connid = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, m_connid, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      ShowIcon::AppendInfo(icon, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      m_cgindex = this->m_cgindex;
      v8 = this->m_connid;
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, m_cgindex, packet);
    }
  }
}


#####################################
std::string __cdecl Player::GetPassport(const Player *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1364);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
std::string __cdecl Player::GetPlatform(const Player *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1573);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
std::string __cdecl Player::GetFromWay(const Player *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1605);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
void __cdecl Player::GetMiniClientIcon(Player *const this, IconStateList *const iconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  Player::GetMiniClientIcon(&__x, this);
  std::list<ShowIcon>::push_back(iconList, &__x);
}


#####################################
void __cdecl Player::SendMiniClientIcon(Player *const this)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  Player::GetMiniClientIcon(&icon, this);
  Player::SendIconState(this, &icon);
}


#####################################
void __cdecl Player::CleanDiligenceValue(Player *const this, int8_t nType)
{
  if ( nType > 0 && nType <= 19 )
    Player::updateRecord(this, nType + 1451, 0);
}


#####################################
void __cdecl Player::AddDiligenceValue(Player *const this, int8_t nType, int32_t Value)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( nType > 0 && nType <= 19 )
  {
    OperateLimit = Player::GetOperateLimit(this);
    CExtOperateLimit::AddLimitCount(OperateLimit, nType + 1451, Value);
  }
}


#####################################
int32_t __cdecl Player::GetDiligenceValue(Player *const this, int8_t nType)
{
  if ( nType > 0 && nType <= 19 )
    return Player::getRecord(this, nType + 1451);
  else
    return 0;
}


#####################################
int32_t __cdecl Player::getDungeonLeftTimes(Player *const this, int32_t nDungeonId)
{
  CfgData *v2; // rax
  int32_t DungeonDailyEnterLimit; // ebx
  CfgDungeon *pCfgDungeon; // [rsp+18h] [rbp-18h]

  v2 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v2, nDungeonId);
  if ( !pCfgDungeon )
    return 0;
  DungeonDailyEnterLimit = Player::GetDungeonDailyEnterLimit(this, nDungeonId);
  return DungeonDailyEnterLimit - Player::getRecord(this, pCfgDungeon->group_id);
}


#####################################
int32_t __cdecl Player::onBeginGather(Player *const this, Answer::NetPacket *inPacket)
{
  EntityId_t v3; // rdx
  int64_t plantid; // [rsp+18h] [rbp-18h]
  Plant *plant; // [rsp+20h] [rbp-10h]
  int32_t err; // [rsp+2Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  if ( this->m_pMap )
  {
    plantid = Answer::NetPacket::readInt64(inPacket);
    plant = Map::getPlant(this->m_pMap, plantid);
    if ( plant )
    {
      if ( this->m_plantId || this->m_plantId > 0 && this->m_plantId != plantid )
        Player::BreakGather(this, 0);
      err = (*((__int64 (__fastcall **)(Plant *, Player *const))plant->_vptr_Entity + 7))(plant, this);
      if ( !err )
      {
        v3 = (*((__int64 (__fastcall **)(Plant *))plant->_vptr_Entity + 2))(plant);
        Player::SetPlantId(this, v3);
        if ( Plant::GetPlantType(plant) == 6 )
          Player::SetPlantState(this, 1);
      }
      return err;
    }
    else
    {
      return 10002;
    }
  }
  else
  {
    Player::BreakGather(this, 1);
    return 10002;
  }
}


#####################################
int32_t __cdecl Player::onDungeonNpc(Player *const this, Answer::NetPacket *inPacket)
{
  CExtCurrency *Currency; // rax
  CURRENCY_TYPE v4; // ebx
  CExtCurrency *v5; // rax
  CExtCharBag *Bag; // rax
  ItemData item; // [rsp+20h] [rbp-50h] BYREF
  CfgDungeonNpcCost cost; // [rsp+30h] [rbp-40h]
  int64_t NpcId; // [rsp+48h] [rbp-28h]
  int8_t choice; // [rsp+57h] [rbp-19h]
  NpcDungeon *npc; // [rsp+58h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  if ( !this->m_pMap )
    return 10002;
  NpcId = Answer::NetPacket::readInt64(inPacket);
  choice = Answer::NetPacket::readInt8(inPacket);
  npc = (NpcDungeon *)Map::getNpc(this->m_pMap, NpcId);
  if ( !npc )
    return 10002;
  if ( choice < 0 )
    return 10002;
  if ( !choice )
  {
    cost = Npc::GetNpcCost(npc, 0);
    if ( cost.ItemType >= 0 )
    {
      if ( cost.ItemId > 0 )
      {
        *(_DWORD *)&item.m_nClass = LOBYTE(cost.ItemType);
        item.m_nId = cost.ItemId;
        item.m_nCount = cost.ItemCount;
        Bag = Player::GetBag(this);
        if ( !CExtCharBag::RemoveItem(Bag, &item, ITEM_CHANGE_REASON::ICR_GIVE_DUNGEON_NPC) )
          return 10002;
      }
    }
    else if ( cost.ItemId > 0 )
    {
      if ( cost.ItemId == 1 )
      {
        Currency = Player::GetCurrency(this);
        if ( !CExtCurrency::DecMoneyAndNoBind(Currency, cost.ItemCount, CURRENCY_CHANGE_REASON::MCR_GIVE_DUNGEON_NPC, 0) )
          return 10002;
      }
      else
      {
        v4 = TranseCurrencyType((CURRENCY_ITEM_ID)cost.ItemId);
        v5 = Player::GetCurrency(this);
        if ( !CExtCurrency::DecCurrency(v5, v4, cost.ItemCount, CURRENCY_CHANGE_REASON::MCR_GIVE_DUNGEON_NPC, 0) )
          return 10002;
      }
    }
  }
  Map::removeNpc(this->m_pMap, NpcId);
  (*((void (__fastcall **)(NpcDungeon *, Player *const, _QWORD))npc->_vptr_Entity + 35))(
    npc,
    this,
    (unsigned int)choice);
  if ( npc )
  {
    (*((void (__fastcall **)(NpcDungeon *))npc->_vptr_Entity + 1))(npc);
    npc = 0;
  }
  return 0;
}


#####################################
int32_t __cdecl Player::onEndGather(Player *const this, Answer::NetPacket *inPacket)
{
  int64_t plantid; // [rsp+18h] [rbp-18h]
  Plant *plant; // [rsp+20h] [rbp-10h]
  int32_t Err; // [rsp+2Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  if ( !this->m_pMap || !this->m_plantId )
    return 10002;
  plantid = Answer::NetPacket::readInt64(inPacket);
  if ( this->m_plantId == plantid && (plant = Map::getPlant(this->m_pMap, plantid)) != 0 )
  {
    Err = (*((__int64 (__fastcall **)(Plant *, Player *const))plant->_vptr_Entity + 8))(plant, this);
    Player::SetStartGather(this, 0);
    Player::SetPlantId(this, 0);
    return Err;
  }
  else
  {
    Player::BreakGather(this, 0);
    Player::SetStartGather(this, 0);
    Player::SetPlantId(this, 0);
    return 10002;
  }
}


#####################################
int32_t __cdecl Player::onSpecialPlant(Player *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax
  CExtCharBag *v5; // rax
  CExtCharBag *v6; // rax
  CExtCharBag *v7; // rax
  MemChrBag Item; // [rsp+10h] [rbp-90h] BYREF
  MemChrBag stu; // [rsp+30h] [rbp-70h] BYREF
  MemChrBag Item_0; // [rsp+50h] [rbp-50h]
  EntityId_t plantid; // [rsp+70h] [rbp-30h]
  int32_t nIndex; // [rsp+78h] [rbp-28h]
  int8_t Best; // [rsp+7Fh] [rbp-21h]
  Plant *plant; // [rsp+80h] [rbp-20h]
  int32_t ItemId; // [rsp+88h] [rbp-18h]
  int32_t BagSlot; // [rsp+8Ch] [rbp-14h]

  plantid = Answer::NetPacket::readInt64(inPacket);
  nIndex = Answer::NetPacket::readInt32(inPacket);
  Best = Answer::NetPacket::readInt8(inPacket);
  plant = Map::getPlant(this->m_pMap, plantid);
  if ( !plant )
    return 10002;
  if ( Best > 0 )
  {
    if ( nIndex != 3 )
      return 10002;
    if ( Player::GetCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD) <= 99 )
      return 10002;
  }
  ItemId = Plant::GetSpecialItem(plant, nIndex);
  if ( ItemId <= 0 )
    return 10002;
  Bag = Player::GetBag(this);
  BagSlot = CExtCharBag::GetTypeItem(Bag, 184);
  if ( BagSlot >= 0 )
  {
    v4 = Player::GetBag(this);
    Item_0 = *CExtCharBag::GetSlotData(v4, BagSlot);
    if ( Item_0.itemId == 924 )
      return 10002;
    memset(&stu, 0, sizeof(stu));
    v5 = Player::GetBag(this);
    CExtCharBag::SetSlotData(v5, BagSlot, &stu, ITEM_CHANGE_REASON::ICR_CAI_JI_SHI_LIAO, 0);
  }
  v6 = Player::GetBag(this);
  if ( CExtCharBag::GetFreeSlotCount(v6) <= 0 )
    return 10002;
  if ( Best > 0
    && !Player::DecCurrency(this, CURRENCY_TYPE::CURRENCY_GOLD, 100, CURRENCY_CHANGE_REASON::GCR_SPECIAL_PLANT, 0) )
  {
    return 10002;
  }
  *(_DWORD *)&Item.itemClass = 1;
  *(_QWORD *)&Item.itemCount = 0x100000001LL;
  *(_QWORD *)&Item.endTime = 0;
  Item.srcId = 0;
  Item.itemId = ItemId;
  v7 = Player::GetBag(this);
  CExtCharBag::AddItem(v7, &Item, ITEM_CHANGE_REASON::ICR_CAI_JI_SHI_LIAO);
  return 0;
}


#####################################
int32_t __cdecl Player::OnClickGame(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t Now; // r14d
  int32_t Sid; // r13d
  int64_t Uid; // r12
  int8_t m_connid; // bl
  DBService *v7; // rax

  if ( !inPacket )
    return 10002;
  Now = Unit::getNow(this);
  Sid = Player::getSid(this);
  Uid = Player::getUid(this);
  m_connid = this->m_connid;
  v7 = Answer::Singleton<DBService>::instance();
  DBService::OnDBClickGame(v7, m_connid, Uid, Sid, Now);
  return 0;
}


#####################################
void __cdecl Player::sendEndGather(Player *const this, int32_t err)
{
  int8_t m_connid; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t m_cgindex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  m_connid = this->m_connid;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, m_connid, Answer::PackType::PACK_DISPATCH, 0x2745u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, err);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    m_cgindex = this->m_cgindex;
    v6 = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v7, v6, m_cgindex, packet);
  }
}


#####################################
void __cdecl Player::SetPlantId(Player *const this, EntityId_t PlantId)
{
  this->m_plantId = PlantId;
  Player::SetNeedSyncAround(this);
}


#####################################
void __cdecl Player::BreakGather(Player *const this, bool IsNotify)
{
  EntityId_t PlantId; // rax
  int32_t Err; // [rsp+14h] [rbp-Ch]
  Plant *plant; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    if ( Player::GetPlantId(this) > 0 )
    {
      Err = 0;
      PlantId = Player::GetPlantId(this);
      plant = Map::getPlant(this->m_pMap, PlantId);
      if ( plant )
        Err = Plant::onBreakGather(plant, this);
      Player::SetPlantId(this, 0);
      Player::SetStartGather(this, 0);
      if ( IsNotify )
        Player::sendEndGather(this, Err);
    }
    Player::SetPlantState(this, 0);
  }
}


#####################################
int32_t __cdecl Player::OnKaiFuHuoDongOperator(Player *const this, Answer::NetPacket *inPacket)
{
  CKaiFuHuoDong *v3; // rax

  if ( !inPacket )
    return 2;
  v3 = Answer::Singleton<CKaiFuHuoDong>::instance();
  return CKaiFuHuoDong::KaiFuHuoDongOperator(v3, this, inPacket);
}


#####################################
int32_t __cdecl Player::OnUniteServerRequestInfo(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::SendUniteServerInfo(v3, this);
  return 0;
}


#####################################
int32_t __cdecl Player::OnUniteServerGetRechargeGift(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CUniteServer>::instance();
  if ( CUniteServer::GetRechargeGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnUniteServerGetLianRechargeGift(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  int32_t nType; // [rsp+18h] [rbp-18h]
  int32_t nIndex; // [rsp+1Ch] [rbp-14h]

  if ( !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt32(inPacket);
  nIndex = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::GetLianRechargeReward(v3, this, nType, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::OnUniteServerGetChouJiangTimesReward(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v2; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-4h]

  nIndex = Answer::NetPacket::readInt32(inPacket);
  v2 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::OnGetChouJiangReward(v2, this, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::OnUniteServerBuyDistinctGift(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int16_t nIndex; // [rsp+1Eh] [rbp-22h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt16(inPacket);
  v3 = Answer::Singleton<CUniteServer>::instance();
  if ( CUniteServer::BuyDiscountGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnUniteServerHuoYueduGift(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt16(inPacket);
  v3 = Answer::Singleton<CUniteServer>::instance();
  if ( CUniteServer::GetHuoYueDuGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnUniteBuyChangeNameCard(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CUniteServer>::instance();
  if ( CUniteServer::BuyChangeNameCard(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnGetUniteWingLevelUpReward(Player *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt16(inPacket);
  v3 = Answer::Singleton<CUniteServer>::instance();
  if ( CUniteServer::GetWingLevelUpGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnGetKaiFuREcharge(Player *const this, Answer::NetPacket *inPacket)
{
  CKiaFuRecharge *v3; // rax
  CKiaFuRecharge *v4; // rax
  CKiaFuRecharge *v5; // rax
  int32_t nHdType; // [rsp+14h] [rbp-1Ch]
  int32_t nType; // [rsp+18h] [rbp-18h]
  int32_t nIndex; // [rsp+1Ch] [rbp-14h]

  if ( !inPacket )
    return 10002;
  nHdType = Answer::NetPacket::readInt32(inPacket);
  nType = Answer::NetPacket::readInt32(inPacket);
  nIndex = Answer::NetPacket::readInt32(inPacket);
  switch ( nHdType )
  {
    case 1:
      v3 = Answer::Singleton<CKiaFuRecharge>::instance();
      CKiaFuRecharge::OnGetRechargeSumReward(v3, this, nIndex);
      break;
    case 2:
      v4 = Answer::Singleton<CKiaFuRecharge>::instance();
      CKiaFuRecharge::GetLianRechargeReward(v4, this, nType, nIndex);
      break;
    case 4:
      v5 = Answer::Singleton<CKiaFuRecharge>::instance();
      CKiaFuRecharge::OnGetXiaoFeiReward(v5, this, nIndex);
      break;
  }
  return 0;
}


#####################################
int32_t __cdecl Player::OnGetKaiFuChouJiang(Player *const this, Answer::NetPacket *inPacket)
{
  CKiaFuRecharge *v3; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::OnGetChouJiangReward(v3, this, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::OnDoubleElevenRequestInfo(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::SendActivityInfo(v3, this);
  return 0;
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetLandGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetLandGift(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetLandSumGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetLandSumGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetDrawGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetDrawGift(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetOnlineGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  CFestivalDoubleEleven *v4; // rax
  int64_t OnlineTimeRewardTime; // r14
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetOnlineGift(v3, this) )
    return 10002;
  v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  OnlineTimeRewardTime = CFestivalDoubleEleven::GetOnlineTimeRewardTime(v4, this);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v9 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v9, m_connid, m_cgindex, Proc, OnlineTimeRewardTime);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetWishGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetWishGift(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenBuyDailyLimitShopItem(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::BuyDailyLimitShopItem(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetHuoYueDuSumGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetHuoYueDuSumGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetDailyRechargeGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetDailyRechargeGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetRechargeSumGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetRechargeSumGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetPetIllusionItemGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetPetIllusionItemGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetXiaoFeiSumGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t nId; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetXiaoFeiSumGift(v3, this, nId) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nId);
}


#####################################
int32_t __cdecl Player::OnGetLianRechargeReward(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  int32_t nType; // [rsp+18h] [rbp-18h]
  int32_t nIndex; // [rsp+1Ch] [rbp-14h]

  if ( !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt32(inPacket);
  nIndex = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::GetLianRechargeReward(v3, this, nType, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::OnRequestMoYuShiJieRecord(Player *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  GameService::SendMoYuShiJieRecord(v3, this);
  return 0;
}


#####################################
int32_t __cdecl Player::OnDoubleElevenBuyGiftShopItem(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::BuyGiftShopItem(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetFaBaoCritBackItem(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nType; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetFaBaoCritBackItem(v3, this, nType) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nType);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenBuyGiftShopItem2(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::BuyGiftShopItem2(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenBuyGiftItem(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::BuyGiftItem(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetRechargeBack(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetRechargeBack(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetEquipQingYiGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetEquipQingYiGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetFriendQingYiGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetFriendQingYiGift(v3, this, nIndex) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenRandScoreDrawGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::OnRandScoreDrawItem(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenRandGouWuChe(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CFestivalDoubleEleven *v3; // rax
  bool v4; // bl
  int64_t Record; // r14
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  Int32List IndexList; // [rsp+10h] [rbp-60h] BYREF
  int __x; // [rsp+2Ch] [rbp-44h] BYREF
  std::list<int> p_nIndexList; // [rsp+30h] [rbp-40h] BYREF
  int32_t nSize; // [rsp+48h] [rbp-28h]
  int32_t i; // [rsp+4Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  std::list<int>::list(&IndexList);
  nSize = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < nSize; ++i )
  {
    __x = Answer::NetPacket::readInt32(inPacket);
    std::list<int>::push_back(&IndexList, &__x);
  }
  std::list<int>::list(&p_nIndexList, &IndexList);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  v4 = CFestivalDoubleEleven::GouWuChe(v3, this, &p_nIndexList) != 0;
  std::list<int>::~list(&p_nIndexList);
  if ( v4 )
  {
    v2 = 10002;
  }
  else
  {
    Record = Player::getRecord(this, 2112);
    Proc = Answer::NetPacket::getProc(inPacket);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v9 = Answer::Singleton<GameService>::instance();
    v2 = GameService::replySuccess(v9, m_connid, m_cgindex, Proc, Record);
  }
  std::list<int>::~list(&IndexList);
  return v2;
}


#####################################
int32_t __cdecl Player::OnFestivalActivityOperator(Player *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  uint16_t Proc; // ax
  int8_t Int8; // bl
  CFestivalActivity *v6; // rax
  int32_t v7; // ebx
  CFestivalActivity *v8; // rax
  uint16_t v9; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  CFestivalActivity *v13; // rax
  bool v14; // bl
  uint16_t v15; // r13
  int16_t v16; // r12
  int8_t v17; // bl
  GameService *v18; // rax
  int8_t v19; // bl
  GameService *v20; // rax
  std::string DaAn; // [rsp+10h] [rbp-50h] BYREF
  std::string p_DaAn; // [rsp+20h] [rbp-40h] BYREF
  int32_t Err; // [rsp+34h] [rbp-2Ch]
  int32_t nProcId; // [rsp+38h] [rbp-28h]
  int8_t Type; // [rsp+3Dh] [rbp-23h]

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  Err = -1;
  Proc = Answer::NetPacket::getProc(inPacket);
  nProcId = Proc;
  if ( Proc == 683 )
  {
    Type = Answer::NetPacket::readInt8(inPacket);
    if ( Type == 2 )
    {
      Int8 = Answer::NetPacket::readInt8(inPacket);
      v6 = Answer::Singleton<CFestivalActivity>::instance();
      Err = CFestivalActivity::GetDaTiReward(v6, this, Int8);
    }
    else if ( Type == 5 )
    {
      v7 = Answer::NetPacket::readInt8(inPacket);
      v8 = Answer::Singleton<CFestivalActivity>::instance();
      if ( !CFestivalActivity::DuiHuan(v8, this, v7) )
      {
        v9 = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this);
        ConnId = Player::getConnId(this);
        v12 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v12, ConnId, GateIndex, v9, Type);
      }
    }
  }
  else if ( Proc == 684 )
  {
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&DaAn, (bool)inPacket);
    std::string::string(&p_DaAn, &DaAn);
    v13 = Answer::Singleton<CFestivalActivity>::instance();
    v14 = CFestivalActivity::DaTi(v13, this, &p_DaAn) == 0;
    std::string::~string(&p_DaAn);
    v15 = Answer::NetPacket::getProc(inPacket);
    v16 = Player::getGateIndex(this);
    if ( v14 )
    {
      v17 = Player::getConnId(this);
      v18 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v18, v17, v16, v15, 0);
    }
    else
    {
      v19 = Player::getConnId(this);
      v20 = Answer::Singleton<GameService>::instance();
      GameService::replyfailure(v20, v19, v16, v15, 0, 0);
    }
    std::string::~string(&DaAn);
  }
  return 0;
}


#####################################
int32_t __cdecl Player::OnOpenBetaOperator(Player *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  uint16_t Proc; // ax
  COpenBeta *v5; // rax
  uint16_t v6; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v9; // rax
  COpenBeta *v10; // rax
  COpenBeta *v11; // rax
  COpenBeta *v12; // rax
  COpenBeta *v13; // rax
  int8_t Int32; // bl
  COpenBeta *v15; // rax
  int8_t v16; // bl
  COpenBeta *v17; // rax
  int8_t v18; // bl
  COpenBeta *v19; // rax
  int8_t v20; // bl
  COpenBeta *v21; // rax
  COpenBeta *v22; // rax
  COpenBeta *v23; // rax
  int8_t v24; // r13
  COpenBeta *v25; // rax
  int8_t v26; // bl
  COpenBeta *v27; // rax
  COpenBeta *v28; // rax
  COpenBeta *v29; // rax
  COpenBeta *v30; // rax
  COpenBeta *v31; // rax
  int32_t nLevel; // [rsp+20h] [rbp-60h]
  int8_t Type; // [rsp+27h] [rbp-59h]
  int32_t Index_2; // [rsp+28h] [rbp-58h]
  int32_t nIndex_1; // [rsp+3Ch] [rbp-44h]
  int8_t nIndex_0; // [rsp+40h] [rbp-40h]
  int32_t nType_0; // [rsp+4Ch] [rbp-34h]
  int32_t nId; // [rsp+50h] [rbp-30h]
  int32_t nLevel_0; // [rsp+54h] [rbp-2Ch]
  int32_t nType; // [rsp+58h] [rbp-28h]
  bool SendIcon; // [rsp+5Fh] [rbp-21h]

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  if ( Proc != 682 )
  {
    if ( Proc == 689 )
    {
      nLevel = Answer::NetPacket::readInt32(inPacket);
      if ( CNationalDayHd::BuyLevel(&this->m_CNationalDayHd, nLevel) )
      {
        v6 = Answer::NetPacket::getProc(inPacket);
        m_cgindex = this->m_cgindex;
        m_connid = this->m_connid;
        v9 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v9, m_connid, m_cgindex, v6, nLevel);
        v10 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::SendIconState(v10, this);
      }
    }
    else if ( Proc == 681 )
    {
      v5 = Answer::Singleton<COpenBeta>::instance();
      COpenBeta::SendActivityInfo(v5, this);
      CExtFlopDraw::SendFlopRecord(&this->m_CExtFlopDraw, this, 1);
    }
    return 0;
  }
  Type = Answer::NetPacket::readInt8(inPacket);
  v11 = Answer::Singleton<COpenBeta>::instance();
  if ( COpenBeta::IsInTime(v11, Type) )
  {
    switch ( Type )
    {
      case 1:
        v12 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::GetOnlineGift(v12, this);
        return 0;
      case 2:
        Index_2 = Answer::NetPacket::readInt32(inPacket);
        v13 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::GetRechargeGift(v13, this, Index_2);
        return 0;
      case 3:
        Int32 = Answer::NetPacket::readInt32(inPacket);
        v15 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::BuyGiftShopItem(v15, this, Int32);
        return 0;
      case 6:
        v16 = Answer::NetPacket::readInt32(inPacket);
        v17 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::BuyTitleShopItem(v17, this, v16);
        return 0;
      case 7:
        v18 = Answer::NetPacket::readInt32(inPacket);
        v19 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::BuyShiZhuangShopItem(v19, this, v18);
        return 0;
      case 10:
        v20 = Answer::NetPacket::readInt32(inPacket);
        v21 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::BuyLiQuan(v21, this, v20);
        return 0;
      case 11:
        nIndex_1 = Answer::NetPacket::readInt32(inPacket);
        if ( CExtFlopDraw::OnFlopDraw(&this->m_CExtFlopDraw, 1, nIndex_1) )
        {
          v22 = Answer::Singleton<COpenBeta>::instance();
          COpenBeta::SendIconState(v22, this);
          v23 = Answer::Singleton<COpenBeta>::instance();
          COpenBeta::SendResult(v23, this, 11, nIndex_1, 0);
        }
        return 0;
      case 12:
        nIndex_0 = Answer::NetPacket::readInt32(inPacket);
        v24 = Answer::NetPacket::readInt32(inPacket);
        v25 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::GetQianDaoReward(v25, this, nIndex_0, v24);
        return 0;
      case 13:
        v26 = Answer::NetPacket::readInt32(inPacket);
        v27 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::GetYanHuaPointReward(v27, this, v26);
        return 0;
      case 16:
        nType_0 = Answer::NetPacket::readInt32(inPacket);
        nId = Answer::NetPacket::readInt32(inPacket);
        if ( CNationalDayHd::GetNationalExp(&this->m_CNationalDayHd, nType_0, nId) )
        {
          v28 = Answer::Singleton<COpenBeta>::instance();
          COpenBeta::SendResult(v28, this, Type, nType_0, nId);
          v29 = Answer::Singleton<COpenBeta>::instance();
          COpenBeta::SendIconState(v29, this);
        }
        return 0;
      case 17:
        nLevel_0 = Answer::NetPacket::readInt32(inPacket);
        nType = Answer::NetPacket::readInt32(inPacket);
        SendIcon = 0;
        if ( nType == 1 )
        {
          if ( !CNationalDayHd::GetOrdinaryReward(&this->m_CNationalDayHd, nLevel_0) )
            goto LABEL_34;
        }
        else if ( nType == 2 )
        {
          if ( !CNationalDayHd::GetSeniorReward(&this->m_CNationalDayHd, nLevel_0) )
            goto LABEL_34;
        }
        else if ( nType != 3 || !CNationalDayHd::UnLockHighReward(&this->m_CNationalDayHd) )
        {
LABEL_34:
          if ( SendIcon )
          {
            v31 = Answer::Singleton<COpenBeta>::instance();
            COpenBeta::SendIconState(v31, this);
          }
          return 0;
        }
        v30 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::SendResult(v30, this, Type, nLevel_0, nType);
        SendIcon = 1;
        goto LABEL_34;
      default:
        return 0;
    }
  }
  return 0;
}


#####################################
void __cdecl Player::BroadcastYanHua(Player *const this, int32_t nType)
{
  Direction Direction; // r12d
  GameService *v3; // rax
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  Position tartile; // [rsp+10h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]
  Position CurrentTile; // 0:rax.8

  if ( this->m_pMap )
  {
    Direction = Unit::getDirection(this);
    CurrentTile = StaticObj::getCurrentTile(this);
    tartile = Map::GetDirTileByDistance(this->m_pMap, CurrentTile, Direction, 2);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2829u);
    if ( packet )
    {
      Cid = Player::getCid(this);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, nType);
      Answer::NetPacket::writeInt32(packet, tartile.x);
      Answer::NetPacket::writeInt32(packet, tartile.y);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
int32_t __cdecl Player::OnDoubleElevenBuyPetGift(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  CFestivalDoubleEleven *v4; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v8; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( !CFestivalDoubleEleven::IsInTime(v3, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_PET_GIFT) )
    return 10002;
  v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( !CFestivalDoubleEleven::BuyTitle(v4, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v8 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v8, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnDoubleElevenGetEquipUpStarBackItem(Player *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  if ( CFestivalDoubleEleven::GetEquipUpStarBackItem(v3, this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnZHYYHDRequestInfo(Player *const this, Answer::NetPacket *inPacket)
{
  CZongHeYunYingHD *v3; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::SendActivityInfo(v3, this);
  return 0;
}


#####################################
int32_t __cdecl Player::OnZHYYHDGetRechargeDailyReward(Player *const this, Answer::NetPacket *inPacket)
{
  CZongHeYunYingHD *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax

  if ( !inPacket )
    return 10002;
  v3 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::GetRechargeDailyReward(v3, this);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl Player::OnZHYYHDGetRechargeTeamShopDailyReward(Player *const this, Answer::NetPacket *inPacket)
{
  CZongHeYunYingHD *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::GetRechargeTeamShopDailyReward(v3, this, nIndex);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::OnZHYYHDBuyOnceShopItem(Player *const this, Answer::NetPacket *inPacket)
{
  CZongHeYunYingHD *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::BuyOnceShopItem(v3, this, nIndex);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, m_connid, m_cgindex, Proc, nIndex);
  return 0;
}


#####################################
int32_t __cdecl Player::OnGetMiniClientReward(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  uint16_t Proc; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  std::string platform; // [rsp+10h] [rbp-30h] BYREF
  const CfgMiniClient *pCfgMiniClient; // [rsp+18h] [rbp-28h]

  if ( !inPacket )
    return 10002;
  if ( CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 1152) )
    return 10002;
  Player::GetPlatform((const Player *const)&platform);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgMiniClient = CfgData::GetMiniClient(v3, &platform);
  std::string::~string(&platform);
  if ( !pCfgMiniClient )
    return 10002;
  if ( std::vector<MemChrBag>::empty(&pCfgMiniClient->vReward) )
    return 10002;
  if ( !CExtCharBag::AddItem(&this->m_extCharBag, &pCfgMiniClient->vReward, ITEM_CHANGE_REASON::ICR_MINI_CLIENT_REWARD) )
    return 10002;
  CExtOperateLimit::AddLimitCount(&this->m_extOperateLimit, 1152, 1);
  Player::SendMiniClientIcon(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  m_cgindex = this->m_cgindex;
  m_connid = this->m_connid;
  v7 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v7, m_connid, m_cgindex, Proc, 0);
}


#####################################
int32_t __cdecl Player::OnEquipBackOperator(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t result; // eax
  CEquipBack *v3; // rax
  CEquipBack *v4; // rax
  CEquipBack *v5; // rax
  CGuiGuDaoRen *v6; // rax
  CGuiGuDaoRen *v7; // rax
  CGuiGuDaoRen *v8; // rax
  CGuiGuDaoRen *v9; // rax
  CGuiGuDaoRen *v10; // rax

  if ( !inPacket )
    return 0;
  switch ( Answer::NetPacket::getProc(inPacket) )
  {
    case 0x357u:
      v3 = Answer::Singleton<CEquipBack>::instance();
      result = CEquipBack::OnGoldBack(v3, this, inPacket);
      break;
    case 0x358u:
      v4 = Answer::Singleton<CEquipBack>::instance();
      result = CEquipBack::OnBuyBack(v4, this, inPacket);
      break;
    case 0x359u:
      v5 = Answer::Singleton<CEquipBack>::instance();
      CEquipBack::SendEquipBackInfo(v5, this);
      goto LABEL_7;
    case 0x35Eu:
      v8 = Answer::Singleton<CGuiGuDaoRen>::instance();
      result = CGuiGuDaoRen::OnAskBackEquipCount(v8, this, inPacket);
      break;
    case 0x35Fu:
      v9 = Answer::Singleton<CGuiGuDaoRen>::instance();
      result = CGuiGuDaoRen::OnBackEquipCount(v9, this, inPacket);
      break;
    case 0x360u:
      v10 = Answer::Singleton<CGuiGuDaoRen>::instance();
      result = CGuiGuDaoRen::OnAskEquipBackRank(v10, this, inPacket);
      break;
    case 0x361u:
LABEL_7:
      v6 = Answer::Singleton<CGuiGuDaoRen>::instance();
      result = CGuiGuDaoRen::OnAskBackItemCount(v6, this, inPacket);
      break;
    case 0x362u:
      v7 = Answer::Singleton<CGuiGuDaoRen>::instance();
      result = CGuiGuDaoRen::OnBackItem(v7, this, inPacket);
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl Player::OnAskLastFullHpTime(Player *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  ConnId = Player::getConnId(this);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CB8u);
  if ( !packet )
    return 10002;
  Record = Player::getRecord(this, 1067);
  Answer::NetPacket::writeInt32(packet, Record);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this);
  v8 = Player::getConnId(this);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v9, v8, GateIndex, packet);
  return 0;
}


#####################################
int32_t __cdecl Player::OnFullHp(Player *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t MapId; // edx
  int32_t PosY; // r13d
  int32_t PosX; // r12d
  int32_t v7; // ebx
  GameService *v8; // rax
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  int32_t NpcId; // [rsp+14h] [rbp-3Ch]
  CfgNpc *cfgNpc; // [rsp+18h] [rbp-38h]
  int32_t Now; // [rsp+20h] [rbp-30h]
  unsigned int MaxKunLi; // [rsp+24h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]

  if ( !inPacket || !this->m_pMap )
    return 10002;
  NpcId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v3, NpcId);
  if ( !cfgNpc )
    return 10002;
  if ( cfgNpc->func_extra != 1082 )
    return 10002;
  MapId = StaticObj::getMapId(this);
  if ( !CfgNpc::findMapId(cfgNpc, MapId) )
    return 10002;
  PosY = StaticObj::GetPosY(this);
  PosX = StaticObj::GetPosX(this);
  v7 = StaticObj::getMapId(this);
  if ( !CfgNpc::NearNpc(cfgNpc, v7, PosX, PosY, 10) )
    return 10002;
  Now = Unit::getNow(this);
  if ( Now - Player::getRecord(this, 1067) <= 59 )
    return 10002;
  Player::updateRecord(this, 1067, Now);
  (*((void (__fastcall **)(Player *const, __int64))this->_vptr_Entity + 22))(this, 100);
  MaxKunLi = Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_KUN_LI);
  (*((void (__fastcall **)(Player *const, _QWORD))this->_vptr_Entity + 23))(this, MaxKunLi);
  v8 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v8, Answer::PackType::PACK_DISPATCH, 0x2CB7u);
  if ( !packet )
    return 10002;
  Cid = Player::getCid(this);
  Answer::NetPacket::writeInt64(packet, Cid);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  Map::broadcastAreaAround(this->m_pMap, packet, this);
  return 0;
}


#####################################
void __cdecl Player::InitSysSetting(Player *const this)
{
  std::string *v1; // rax
  std::string *v2; // rax
  const char *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  int *v6; // rax
  int32_t Key; // [rsp+1Ch] [rbp-A4h] BYREF
  StringVector StringVt; // [rsp+20h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-80h] BYREF
  StringVector mineString; // [rsp+50h] [rbp-70h] BYREF
  std::string delims; // [rsp+70h] [rbp-50h] BYREF
  char v12; // [rsp+7Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-40h] BYREF
  std::string v14; // [rsp+90h] [rbp-30h] BYREF
  char v15; // [rsp+A7h] [rbp-19h] BYREF
  int __k; // [rsp+A8h] [rbp-18h] BYREF
  int32_t Values; // [rsp+ACh] [rbp-14h]

  if ( !std::operator==<char>(&this->m_systemSetting, byte_8E9580) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|");
    Answer::StringUtility::split(&mineString, &this->m_systemSetting, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    for ( it._M_current = std::vector<std::string>::begin(&mineString)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&mineString)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v15);
      std::string::string(&v14, ":");
      v1 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&StringVt, v1, &v14, 0);
      std::string::~string(&v14);
      std::allocator<char>::~allocator(&v15);
      if ( std::vector<std::string>::size(&StringVt) == 2 )
      {
        v2 = std::vector<std::string>::operator[](&StringVt, 0);
        v3 = (const char *)std::string::c_str(v2);
        Key = atoi(v3);
        v4 = std::vector<std::string>::operator[](&StringVt, 1u);
        v5 = (const char *)std::string::c_str(v4);
        Values = atoi(v5);
        v6 = std::map<int,int>::operator[](&this->m_SystemSetting, &Key);
        *v6 = Values;
      }
      std::vector<std::string>::~vector(&StringVt);
    }
    __k = 7;
    *std::map<int,int>::operator[](&this->m_SystemSetting, &__k) = 0;
    std::vector<std::string>::~vector(&mineString);
  }
}


#####################################
std::string __cdecl Player::GetSysSetting(Player *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int second; // r12d
  std::pair<const int,int> *v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  _BYTE v9[16]; // [rsp+10h] [rbp-1A0h] BYREF
  __int64 v10; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v9, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 48296))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 48296))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    v5 = std::ostream::operator<<(&v10, (unsigned int)v4->first);
    v6 = std::operator<<<std::char_traits<char>>(v5, ":");
    v7 = std::ostream::operator<<(v6, second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v9);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v9);
  return (std::string)this;
}


#####################################
bool __cdecl Player::GetSysSettingInfo(Player *const this, int32_t Index)
{
  int32_t Indexa; // [rsp+4h] [rbp-Ch] BYREF
  Player *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  Indexa = Index;
  return *std::map<int,int>::operator[](&this->m_SystemSetting, &Indexa) > 0;
}


#####################################
bool __cdecl Player::NearNpc(Player *const this, int32_t NpcId)
{
  CfgData *v2; // rax
  int32_t PosY; // r13d
  int32_t PosX; // r12d
  int32_t MapId; // ebx
  const CfgNpc *cfgNpc; // [rsp+18h] [rbp-28h]

  v2 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v2, NpcId);
  if ( !cfgNpc )
    return 0;
  PosY = StaticObj::GetPosY(this);
  PosX = StaticObj::GetPosX(this);
  MapId = StaticObj::getMapId(this);
  return CfgNpc::NearNpc(cfgNpc, MapId, PosX, PosY, 10);
}


#####################################
void __cdecl Player::AddAppendAttr(Player *const this)
{
  int32_t Record; // ebx
  int32_t v2; // eax
  int32_t m_nAddAttrValue; // ebx
  CObjAttrs::Index_T m_nAddAttrType; // ecx
  GameService *v5; // rax
  CActivityManager *v6; // rax
  int32_t v7; // eax
  int32_t v8; // ebx
  CObjAttrs::Index_T v9; // ecx
  char v10; // bl
  char v11; // r12
  CDaTingReward *CDaTingReward; // rax
  bool v13; // al
  bool v14; // r13
  int32_t v15; // eax
  int32_t v16; // ebx
  CObjAttrs::Index_T v17; // ecx
  std::_List_iterator<AddAttribute> it_1; // [rsp+10h] [rbp-D0h] BYREF
  AddAttrList AddAttr_1; // [rsp+20h] [rbp-C0h] BYREF
  std::_List_iterator<AddAttribute> it_0; // [rsp+30h] [rbp-B0h] BYREF
  AddAttrList AddAttr_0; // [rsp+40h] [rbp-A0h] BYREF
  std::_List_iterator<AddAttribute> it; // [rsp+50h] [rbp-90h] BYREF
  AddAttrList AddAttr; // [rsp+60h] [rbp-80h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+70h] [rbp-70h] BYREF
  std::_List_iterator<AddAttribute> v25; // [rsp+80h] [rbp-60h] BYREF
  std::string __lhs; // [rsp+90h] [rbp-50h] BYREF
  std::string v27; // [rsp+A0h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> v28; // [rsp+B0h] [rbp-30h] BYREF

  Record = Player::getRecord(this, 1066);
  if ( Record > Unit::getNow(this) )
  {
    Player::getJob(this);
    v2 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetAppendAttr((CfgData *const)&AddAttr, v2, 1);
    for ( it._M_node = std::list<AddAttribute>::begin(&AddAttr)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it) )
    {
      __x._M_node = std::list<AddAttribute>::end(&AddAttr)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      m_nAddAttrType = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrType;
      Unit::AddAttrValue(this, m_nAddAttrType, m_nAddAttrValue);
    }
    std::list<AddAttribute>::~list(&AddAttr);
  }
  v5 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v5) != 9 )
  {
    v6 = Answer::Singleton<CActivityManager>::instance();
    if ( CActivityManager::GetCrossTowerWinner(v6) )
    {
      Player::getJob(this);
      v7 = (unsigned int)Answer::Singleton<CfgData>::instance();
      CfgData::GetAppendAttr((CfgData *const)&AddAttr_0, v7, 3);
      for ( it_0._M_node = std::list<AddAttribute>::begin(&AddAttr_0)._M_node;
            ;
            std::_List_iterator<AddAttribute>::operator++(&it_0) )
      {
        v25._M_node = std::list<AddAttribute>::end(&AddAttr_0)._M_node;
        if ( !std::_List_iterator<AddAttribute>::operator!=(&it_0, &v25) )
          break;
        v8 = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
        v9 = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrType;
        Unit::AddAttrValue(this, v9, v8);
      }
      std::list<AddAttribute>::~list(&AddAttr_0);
    }
  }
  v10 = 0;
  v11 = 0;
  v13 = 1;
  if ( !Player::IsMiniClient(this) && !CDaTingReward::IsDaTing(&this->m_CDaTingReward) )
  {
    if ( (Player::GetPlatform((const Player *const)&__lhs), v10 = 1, !std::operator==<char>(&__lhs, "wan_993h"))
      && (Player::GetPlatform((const Player *const)&v27), v11 = 1, !std::operator==<char>(&v27, "liebao_993h"))
      || (CDaTingReward = Player::GetCDaTingReward(this), CDaTingReward::GetPlatformVipLevel(CDaTingReward) <= 0) )
    {
      v13 = 0;
    }
  }
  v14 = v13;
  if ( v11 )
    std::string::~string(&v27);
  if ( v10 )
    std::string::~string(&__lhs);
  if ( v14 )
  {
    Player::getJob(this);
    v15 = (unsigned int)Answer::Singleton<CfgData>::instance();
    CfgData::GetAppendAttr((CfgData *const)&AddAttr_1, v15, 2);
    for ( it_1._M_node = std::list<AddAttribute>::begin(&AddAttr_1)._M_node;
          ;
          std::_List_iterator<AddAttribute>::operator++(&it_1) )
    {
      v28._M_node = std::list<AddAttribute>::end(&AddAttr_1)._M_node;
      if ( !std::_List_iterator<AddAttribute>::operator!=(&it_1, &v28) )
        break;
      v16 = std::_List_iterator<AddAttribute>::operator->(&it_1)->m_nAddAttrValue;
      v17 = std::_List_iterator<AddAttribute>::operator->(&it_1)->m_nAddAttrType;
      Unit::AddAttrValue(this, v17, v16);
    }
    std::list<AddAttribute>::~list(&AddAttr_1);
  }
}


#####################################
void __cdecl Player::SendFamilyWarIcon(Player *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  Player::GetFamilyWarShowIcon(&stu, this);
  Player::SendIconState(this, &stu);
}


#####################################
void __cdecl Player::GetFamilyWarIcon(Player *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  Player::GetFamilyWarShowIcon(&__x, this);
  std::list<ShowIcon>::push_back(IconList, &__x);
}


#####################################
int32_t __cdecl Player::onSocialChangeName(Player *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  const char *v3; // rax
  int8_t m_connid; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  MemChrBag slotData; // [rsp+10h] [rbp-50h] BYREF
  std::string name; // [rsp+30h] [rbp-30h] BYREF
  int32_t slot; // [rsp+44h] [rbp-1Ch]
  Answer::NetPacket *outPacket; // [rsp+48h] [rbp-18h]

  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&name, (bool)inPacket);
  slot = Answer::NetPacket::readInt32(inPacket);
  Player::getBagSlotData(&slotData, this, slot);
  if ( slotData.itemCount > 0 && slotData.itemClass == 1 && slotData.itemId == 10 )
  {
    --slotData.itemCount;
    CExtCharBag::SetSlotData(&this->m_extCharBag, slot, &slotData, ITEM_CHANGE_REASON::ICR_CHANG_NAME, 0);
    v3 = (const char *)std::string::c_str(&name);
    snprintf(this->m_chr.name, 0x1Eu, v3);
    Player::sendChrInfo(this);
    if ( this->m_pMap )
      Map::broadcastIntoMap(this->m_pMap, this);
    m_connid = this->m_connid;
    v5 = Answer::Singleton<GameService>::instance();
    outPacket = GameService::popNetpacket(v5, m_connid, Answer::PackType::PACK_DISPATCH, 0x4E97u);
    Answer::NetPacket::writeInt32(outPacket, this->m_cgindex);
    Answer::NetPacket::writeUTF8(outPacket, &name);
    WOffset = Answer::NetPacket::getWOffset(outPacket);
    Answer::NetPacket::setSize(outPacket, WOffset);
    v7 = this->m_connid;
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v8, v7, outPacket);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::string::~string(&name);
  return v2;
}


#####################################
int32_t __cdecl Player::GetAllMoneyRate(Player *const this)
{
  return CExtCharSkill::GetDropMoneyRate(&this->m_extCharSkill);
}


#####################################
int32_t __cdecl Player::OnFengHao(Player *const this, Answer::NetPacket *inPacket)
{
  int8_t v3; // r12
  int8_t m_connid; // bl
  DBService *v5; // rax
  std::string p_name; // [rsp+10h] [rbp-30h] BYREF
  int8_t Type; // [rsp+27h] [rbp-19h]
  int64_t Cid; // [rsp+28h] [rbp-18h]

  if ( !inPacket )
    return 2;
  if ( Player::GetGMLevel(this) <= 0 )
    return 2;
  Type = Answer::NetPacket::readInt8(inPacket);
  Cid = Answer::NetPacket::readInt64(inPacket);
  Player::getName((const Player *const)&p_name);
  v3 = Type;
  m_connid = this->m_connid;
  v5 = Answer::Singleton<DBService>::instance();
  DBService::fengHao(v5, m_connid, v3, Cid, &p_name);
  std::string::~string(&p_name);
  return 0;
}


#####################################
int32_t __cdecl Player::OnSetFcmTime(Player *const this, Answer::NetPacket *inPacket)
{
  bool v3; // bl
  std::string __lhs; // [rsp+10h] [rbp-20h] BYREF

  if ( !inPacket )
    return 2;
  Player::GetPlatform((const Player *const)&__lhs);
  v3 = std::operator!=<char>(&__lhs, "32wan");
  std::string::~string(&__lhs);
  if ( v3 )
    return 2;
  this->m_sysUser.total_online_time = Answer::NetPacket::readUInt32(inPacket);
  return 0;
}


#####################################
std::string __cdecl Player::GetPassport(Player *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1364);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
void __cdecl Player::SetActState(Player *const this, int8_t ActState)
{
  this->m_ActState = ActState;
  Player::setSyncStatusFlag(this);
}


#####################################
void __cdecl Player::OnMonthSwitch(Player *const this)
{
  int32_t Record; // eax
  int32_t Now; // edx

  Record = Player::getRecord(this, 1040);
  if ( Answer::DayTime::monthdiff(Record) > 0 )
    CMonthlyChouJiang::OnMonthlySwitch(&this->m_CMonthlyChouJiang);
  Now = Unit::getNow(this);
  Player::updateRecord(this, 1040, Now);
}


#####################################
void __cdecl Player::RecalcAttr(Player *const this)
{
  Player::recalcAttr(this, 0, 0);
}


#####################################
int32_t __cdecl Player::onComBackCity(Player *const this, Answer::NetPacket *inPacket)
{
  if ( inPacket )
    return Player::OnBackCity(this, 1, 0);
  else
    return 10002;
}


#####################################
void __cdecl Player::AddBossRank(Player *const this, EntityId_t nBossId)
{
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<long int> v3; // rax
  EntityId_t nBossIda; // [rsp+0h] [rbp-40h] BYREF
  Player *thisa; // [rsp+8h] [rbp-38h]
  std::_List_iterator<long int> __x; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<long int> v7; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nBossIda = nBossId;
  __x._M_node = std::list<long>::end(&this->m_lBossRank)._M_node;
  M_node = std::list<long>::end(&this->m_lBossRank)._M_node;
  v3._M_node = std::list<long>::begin(&this->m_lBossRank)._M_node;
  v7._M_node = std::find<std::_List_iterator<long>,long>(v3, (std::_List_iterator<long int>)M_node, &nBossIda)._M_node;
  if ( std::_List_iterator<long>::operator==(&v7, &__x) )
    std::list<long>::push_back(&thisa->m_lBossRank, &nBossIda);
}


#####################################
void __cdecl Player::RemoveBossRank(Player *const this, EntityId_t nBossId)
{
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<long int> v3; // rax
  EntityId_t nBossIda; // [rsp+0h] [rbp-40h] BYREF
  Player *thisa; // [rsp+8h] [rbp-38h]
  std::_List_iterator<long int> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<long int> __x; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nBossIda = nBossId;
  M_node = std::list<long>::end(&this->m_lBossRank)._M_node;
  v3._M_node = std::list<long>::begin(&this->m_lBossRank)._M_node;
  iter._M_node = std::find<std::_List_iterator<long>,long>(v3, (std::_List_iterator<long int>)M_node, &nBossIda)._M_node;
  __x._M_node = std::list<long>::end(&thisa->m_lBossRank)._M_node;
  if ( std::_List_iterator<long>::operator!=(&iter, &__x) )
    std::list<long>::erase(&thisa->m_lBossRank, iter);
}


#####################################
void __cdecl Player::setBossRankDie(Player *const this)
{
  int32_t RunnerId; // r12d
  EntityId_t v2; // rbx
  GameService *v3; // rax
  std::_List_iterator<long int> iter; // [rsp+10h] [rbp-40h] BYREF
  Int64List tlist; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<long int> __x; // [rsp+30h] [rbp-20h] BYREF
  Monster *pBoss; // [rsp+38h] [rbp-18h]

  if ( !std::list<long>::empty(&this->m_lBossRank) )
  {
    std::list<long>::list(&tlist, &this->m_lBossRank);
    for ( iter._M_node = std::list<long>::begin(&tlist)._M_node; ; std::_List_iterator<long>::operator++(&iter) )
    {
      __x._M_node = std::list<long>::end(&tlist)._M_node;
      if ( !std::_List_iterator<long>::operator!=(&iter, &__x) )
        break;
      RunnerId = StaticObj::GetRunnerId(this);
      v2 = *std::_List_iterator<long>::operator*(&iter);
      v3 = Answer::Singleton<GameService>::instance();
      pBoss = GameService::getMonster(v3, v2, RunnerId);
      if ( pBoss )
        Monster::onPlayerDie(pBoss, this);
    }
    std::list<long>::~list(&tlist);
  }
}


#####################################
void __cdecl Player::setBossRankTeamChange(Player *const this)
{
  int32_t RunnerId; // r12d
  EntityId_t v2; // rbx
  GameService *v3; // rax
  std::_List_iterator<long int> iter; // [rsp+10h] [rbp-40h] BYREF
  Int64List tlist; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<long int> __x; // [rsp+30h] [rbp-20h] BYREF
  Monster *pBoss; // [rsp+38h] [rbp-18h]

  if ( !std::list<long>::empty(&this->m_lBossRank) )
  {
    std::list<long>::list(&tlist, &this->m_lBossRank);
    for ( iter._M_node = std::list<long>::begin(&tlist)._M_node; ; std::_List_iterator<long>::operator++(&iter) )
    {
      __x._M_node = std::list<long>::end(&tlist)._M_node;
      if ( !std::_List_iterator<long>::operator!=(&iter, &__x) )
        break;
      RunnerId = StaticObj::GetRunnerId(this);
      v2 = *std::_List_iterator<long>::operator*(&iter);
      v3 = Answer::Singleton<GameService>::instance();
      pBoss = GameService::getMonster(v3, v2, RunnerId);
      if ( pBoss )
        Monster::onTeamUpdate(pBoss, this);
    }
    std::list<long>::~list(&tlist);
  }
}


#####################################
int32_t __cdecl Player::keepDungeon(Player *const this)
{
  const Dungeon *v1; // rax
  int32_t Id; // eax
  int32_t PosX; // eax
  int32_t PosY; // eax
  Dungeon *pDungeon; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
    v1 = (const Dungeon *)__dynamic_cast(
                            this->m_pMap,
                            (const struct __class_type_info *)&`typeinfo for'Map,
                            (const struct __class_type_info *)&`typeinfo for'Dungeon,
                            0);
  else
    v1 = 0;
  pDungeon = (Dungeon *)v1;
  if ( v1 )
  {
    if ( !Dungeon::CanContinue(v1)
      || Dungeon::getState(pDungeon) == DungeonState::DS_WIN
      || Dungeon::getState(pDungeon) == DungeonState::DS_FAIL )
    {
      Player::leaveDungeon(this);
      return 10002;
    }
    else
    {
      if ( CExtCharCarrier::IsInCarrier(&this->m_extCharCarrier) )
        CExtCharCarrier::LeaveCarrier(&this->m_extCharCarrier);
      if ( Dungeon::StayPosition(pDungeon) )
      {
        this->m_oldPosition.x = StaticObj::GetPosX(this);
        this->m_oldPosition.y = StaticObj::GetPosY(this);
      }
      Id = Dungeon::GetId(pDungeon);
      CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 37301, Id);
      PosX = StaticObj::GetPosX(this);
      CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 37302, PosX);
      PosY = StaticObj::GetPosY(this);
      CExtOperateLimit::UpdateLimitCount(&this->m_extOperateLimit, 37303, PosY);
      Player::broadcastLeave(this);
      if ( Dungeon::getDungeonType(pDungeon) == 12 )
        CExtCharTeamDungeon::LeaveTeamDungeon(&this->m_extCharTeamDungeon);
      return 0;
    }
  }
  else
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "pDungeon NULL");
    return 10002;
  }
}


#####################################
bool __cdecl Player::reconnect(Player *const this)
{
  MapManager *v2; // rax
  char v3; // al
  int64_t DungeonId; // r13
  int16_t m_cgindex; // r12
  int8_t m_connid; // bl
  GameService *v7; // rax
  void (__fastcall *v8)(const Dungeon *, Player *const, __int64, _QWORD); // r13
  unsigned int LimitCount; // r12d
  __int64 v10; // rdx
  int nDungeonId; // [rsp+14h] [rbp-2Ch]
  const Dungeon *pDungeon; // [rsp+18h] [rbp-28h]

  nDungeonId = CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37301);
  if ( nDungeonId <= 0 )
    return 0;
  v2 = Answer::Singleton<MapManager>::instance();
  pDungeon = MapManager::GetDungeon(v2, nDungeonId);
  if ( pDungeon
    && (Dungeon::getState(pDungeon) == DungeonState::DS_WIN || Dungeon::getState(pDungeon) == DungeonState::DS_FAIL
      ? (v3 = 0)
      : (v3 = 1),
        v3) )
  {
    DungeonId = Dungeon::getDungeonId(pDungeon);
    m_cgindex = this->m_cgindex;
    m_connid = this->m_connid;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v7, m_connid, m_cgindex, 0x12u, DungeonId);
    v8 = (void (__fastcall *)(const Dungeon *, Player *const, __int64, _QWORD))*((_QWORD *)pDungeon->_vptr_Map + 15);
    LimitCount = CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37303);
    v10 = (unsigned int)CExtOperateLimit::GetLimitCount(&this->m_extOperateLimit, 37302);
    v8(pDungeon, this, v10, LimitCount);
    CExtOperateLimit::Reset(&this->m_extOperateLimit, 37301);
    CExtOperateLimit::Reset(&this->m_extOperateLimit, 37302);
    CExtOperateLimit::Reset(&this->m_extOperateLimit, 37303);
    return 1;
  }
  else
  {
    CExtOperateLimit::Reset(&this->m_extOperateLimit, 37301);
    CExtOperateLimit::Reset(&this->m_extOperateLimit, 37302);
    CExtOperateLimit::Reset(&this->m_extOperateLimit, 37303);
    return 0;
  }
}


#####################################
void __cdecl Player::InitExtSystems(Player *const this)
{
  CExtSystemBase::Init(&this->m_extOperateLimit, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extOperateLimit);
  CExtSystemBase::Init(&this->m_PlayerFunctionOpen, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerFunctionOpen);
  CExtSystemBase::Init(&this->m_extCurrency, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCurrency);
  CExtSystemBase::Init(&this->m_extCharBag, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharBag);
  CExtSystemBase::Init(&this->m_extEquip, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extEquip);
  CExtSystemBase::Init(&this->m_extFightChecker, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extFightChecker);
  CExtSystemBase::Init(&this->m_extCharTeam, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharTeam);
  CExtSystemBase::Init(&this->m_extCharPet, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharPet);
  CExtSystemBase::Init(&this->m_extCharSkill, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharSkill);
  CExtSystemBase::Init(&this->m_extTaskCycle, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extTaskCycle);
  CExtSystemBase::Init(&this->m_ScoreShop, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_ScoreShop);
  CExtSystemBase::Init(&this->m_extCharFamily, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharFamily);
  CExtSystemBase::Init(&this->m_extCharTeamDungeon, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharTeamDungeon);
  CExtSystemBase::Init(&this->m_extCharWorship, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharWorship);
  CExtSystemBase::Init(&this->m_extCharAuction, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharAuction);
  CExtSystemBase::Init(&this->m_extCharHallOfFame, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharHallOfFame);
  CExtCharTitle::Init(&this->m_extCharTitle, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharTitle);
  CExtSystemBase::Init(&this->m_extCharMysteryShop, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharMysteryShop);
  CExtSystemBase::Init(&this->m_extCharMysteryGift, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharMysteryGift);
  CExtSystemBase::Init(&this->m_extCharExchange, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharExchange);
  CExtSystemBase::Init(&this->m_extCharDraw, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharDraw);
  CExtSystemBase::Init(&this->m_extCharWish, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharWish);
  CExtSystemBase::Init(&this->m_extBlackMarket, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extBlackMarket);
  CExtSystemBase::Init(&this->m_extCharTencent, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharTencent);
  CExtSystemBase::Init(&this->m_extCharWing, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharWing);
  CExtSystemBase::Init(&this->m_extMagicBox, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extMagicBox);
  CExtSystemBase::Init(&this->m_extCharCarrier, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharCarrier);
  CExtSystemBase::Init(&this->m_extCharJueWei, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharJueWei);
  CExtSystemBase::Init(&this->m_PlayerDepot, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerDepot);
  CExtSystemBase::Init(&this->m_PlayerTrade, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerTrade);
  CExtSystemBase::Init(&this->m_PlayerMail, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerMail);
  CExtSystemBase::Init(&this->m_FRiendExp, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_FRiendExp);
  CExtSystemBase::Init(&this->m_PlayerFaBao, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerFaBao);
  CExtSystemBase::Init(&this->m_PlayerShangCheng, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerShangCheng);
  CExtSystemBase::Init(&this->m_PlayerQiFu, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerQiFu);
  CExtSystemBase::Init(&this->m_PlayerDailyActivity, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerDailyActivity);
  CExtSystemBase::Init(&this->m_PlayerVip, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerVip);
  CExtSystemBase::Init(&this->m_PlayerYunYingHD, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerYunYingHD);
  CExtSystemBase::Init(&this->m_PlayerTouZi, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerTouZi);
  CExtSystemBase::Init(&this->m_PlayerHuoYueDu, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerHuoYueDu);
  CExtSystemBase::Init(&this->m_extCharPortal, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extCharPortal);
  CExtSystemBase::Init(&this->m_Wan360, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_Wan360);
  CExtSystemBase::Init(&this->m_Vplan, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_Vplan);
  CExtSystemBase::Init(&this->m_XingMai, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_XingMai);
  CExtSystemBase::Init(&this->m_TianLing, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_TianLing);
  CExtSystemBase::Init(&this->m_PlayerChouJiang, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_PlayerChouJiang);
  CExtSystemBase::Init(&this->m_TreasureMap, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_TreasureMap);
  CExtSystemBase::Init(&this->m_CMoneyRewardTask, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CMoneyRewardTask);
  CExtSystemBase::Init(&this->m_CSpecialEquip, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CSpecialEquip);
  CExtSystemBase::Init(&this->m_Curse, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_Curse);
  CExtSystemBase::Init(&this->m_CLevelRefining, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CLevelRefining);
  CExtSystemBase::Init(&this->m_ShenWei, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_ShenWei);
  CExtSystemBase::Init(&this->m_CBossKilledReward, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CBossKilledReward);
  CExtSystemBase::Init(&this->m_CTestServerReward, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CTestServerReward);
  CExtSystemBase::Init(&this->m_CWuHunShop, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CWuHunShop);
  CExtSystemBase::Init(&this->m_CCharWuHun, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CCharWuHun);
  CExtSystemBase::Init(&this->m_CSuperTeHui, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CSuperTeHui);
  CExtSystemBase::Init(&this->m_CGoblin, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CGoblin);
  CExtSystemBase::Init(&this->m_extShiZhuang, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_extShiZhuang);
  CExtSystemBase::Init(&this->m_CMonthlyChouJiang, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CMonthlyChouJiang);
  CExtSystemBase::Init(&this->m_CGuardPrivilege, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CGuardPrivilege);
  CExtSystemBase::Init(&this->m_CDaTingReward, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CDaTingReward);
  CExtSystemBase::Init(&this->m_CMingGeExt, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CMingGeExt);
  CExtSystemBase::Init(&this->m_CKunExt, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CKunExt);
  CExtSystemBase::Init(&this->m_CExtFlopDraw, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CExtFlopDraw);
  CExtSystemBase::Init(&this->m_CSevenDayTask, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CSevenDayTask);
  CExtSystemBase::Init(&this->m_CGongMing, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CGongMing);
  CExtSystemBase::Init(&this->m_CXinMo, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CXinMo);
  CExtSystemBase::Init(&this->m_CharLittlerhelper, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CharLittlerhelper);
  CExtSystemBase::Init(&this->m_CNationalDayHd, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CNationalDayHd);
  CExtSystemBase::Init(&this->m_CRongHe, this);
  CExtSystemMgr::Register(&this->m_ExtSysMgr, &this->m_CRongHe);
}


