// Decompiled methods for class: CObjPet
// Source: gameserver.cc
// Total methods: 60

#####################################
void __cdecl CObjPet::~CObjPet(CObjPet *const this)
{
  CObjPet::~CObjPet(this);
  operator delete(this);
}


#####################################
bool __cdecl CObjPet::refresh(CObjPet *const this)
{
  CExtCharPet *CharPet; // rax

  if ( this->m_bAlive && !Unit::isAlive(this) )
    CObjPet::onDie(this);
  if ( this->m_nState == PET_STATE::PS_FIGHTING && Unit::isAlive(this) )
  {
    CObjPet::checkSpeed(this);
    CObjPet::checkSwitchMap(this);
    CObjPet::updateFightState(this);
  }
  if ( this->m_pPlayer && CObjPet::CheckRelive(this) )
  {
    CharPet = Player::GetCharPet(this->m_pPlayer);
    CExtCharPet::SendPetInfo(CharPet);
  }
  return 0;
}


#####################################
int32_t __cdecl CObjPet::getLevel(const CObjPet *const this)
{
  if ( this->m_pPlayer )
    return (*((int32_t (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  else
    return 0;
}


#####################################
int32_t __cdecl CObjPet::getBattle(const CObjPet *const this)
{
  if ( this->m_pPlayer )
    return (*((int32_t (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 10))(this->m_pPlayer);
  else
    return 0;
}


#####################################
bool __cdecl CObjPet::isFriendSide(CObjPet *const this, Unit *pUnit)
{
  return this->m_pPlayer
      && (*((bool (__fastcall **)(Player *, Unit *))this->m_pPlayer->_vptr_Entity + 14))(this->m_pPlayer, pUnit);
}


#####################################
bool __cdecl CObjPet::checkSkillTarget(CObjPet *const this, const CfgActiveSkill *pCfg, Unit *pUnit)
{
  return this->m_pPlayer
      && (*((bool (__fastcall **)(Player *, const CfgActiveSkill *, Unit *))this->m_pPlayer->_vptr_Entity + 15))(
           this->m_pPlayer,
           pCfg,
           pUnit);
}


#####################################
void __cdecl CObjPet::reset(CObjPet *const this)
{
  Unit::reset(this);
  this->m_pPlayer = 0;
  this->m_pCfgPet = 0;
  this->m_nSummonSkillId = 0;
  this->m_nDieTick = 0;
  this->m_nDieTime = 0;
  this->m_nPetId = 0;
  bzero(this->m_strName, 0x1Fu);
  bzero(this->m_vSkill, 0x90u);
  bzero(this->m_vEquip, 0x10u);
  this->m_bAlive = 0;
  this->m_nState = PET_STATE::PS_REST;
  this->m_nFightState = PET_FIGHT_STATE::PFS_AWAY_FROM_MAP;
  this->m_nStandPlace = Direction::LEFT;
  this->m_nLastSkillTick = 0;
  this->m_nLastReplyHp = 0;
  this->m_pNextSkill = 0;
  UnitHandle::clear(&this->m_target);
  this->m_AiState = 1;
}


#####################################
void __cdecl CObjPet::Init(
        CObjPet *const this,
        Player *pOwner,
        PetId_t nPetId,
        int32_t nBaseId,
        bool bAlive,
        PET_STATE state,
        Direction nDir,
        int8_t AiState)
{
  CfgData *v8; // rax
  const CfgPetTable *PetTable; // rax
  int32_t i; // [rsp+3Ch] [rbp-4h]

  this->m_nPetId = nPetId;
  v8 = Answer::Singleton<CfgData>::instance();
  PetTable = CfgData::GetPetTable(v8);
  this->m_pCfgPet = CfgPetTable::GetPet(PetTable, nBaseId);
  this->m_pPlayer = pOwner;
  this->m_bAlive = bAlive;
  this->m_nState = state;
  this->m_nFightState = PET_FIGHT_STATE::PFS_AWAY_FROM_MAP;
  this->m_nStandPlace = nDir;
  this->m_AiState = AiState;
  UnitHandle::clear(&this->m_target);
  if ( this->m_pCfgPet )
  {
    bzero(this->m_vSkill, 0x90u);
    for ( i = 0; i <= 8; ++i )
      this->m_vSkill[i].nId = this->m_pCfgPet->m_vSkill[i];
  }
  CObjPet::recalAttr(this);
  (*((void (__fastcall **)(CObjPet *const, __int64))this->_vptr_Entity + 22))(this, 100);
}


#####################################
void __cdecl CObjPet::InitSummon(CObjPet *const this, Player *pOwner, int32_t nBaseId, int32_t nSkillId)
{
  CfgData *v4; // rax
  const CfgPetTable *PetTable; // rax
  int32_t i; // [rsp+2Ch] [rbp-4h]

  this->m_nPetId = Entity::getEntityId(this);
  this->m_nSummonSkillId = nSkillId;
  v4 = Answer::Singleton<CfgData>::instance();
  PetTable = CfgData::GetPetTable(v4);
  this->m_pCfgPet = CfgPetTable::GetPet(PetTable, nBaseId);
  this->m_pPlayer = pOwner;
  this->m_bAlive = 1;
  this->m_nState = PET_STATE::PS_FIGHTING;
  this->m_nFightState = PET_FIGHT_STATE::PFS_AWAY_FROM_MAP;
  this->m_AiState = 1;
  UnitHandle::clear(&this->m_target);
  if ( this->m_pCfgPet )
  {
    bzero(this->m_vSkill, 0x90u);
    for ( i = 0; i <= 8; ++i )
    {
      if ( this->m_pCfgPet->m_vSkill[i] > 0 )
      {
        this->m_vSkill[i].nId = this->m_pCfgPet->m_vSkill[i];
        this->m_vSkill[i].nLevel = 1;
      }
    }
  }
  CObjPet::recalAttr(this);
  (*((void (__fastcall **)(CObjPet *const, __int64))this->_vptr_Entity + 22))(this, 100);
}


#####################################
void __cdecl CObjPet::ReplyHp(CObjPet *const this, int64_t CurTick)
{
  __int64 v2; // rbx
  int32_t ReplyRate; // [rsp+18h] [rbp-18h]
  unsigned int NeedAddHp; // [rsp+1Ch] [rbp-14h]

  if ( CObjPet::AliveFlag(this) )
  {
    if ( (*((int (__fastcall **)(CObjPet *const))this->_vptr_Entity + 9))(this) > 90 )
    {
      if ( CurTick - this->m_nLastReplyHp <= 9999 )
        return;
    }
    else if ( CurTick - this->m_nLastReplyHp <= 1999 )
    {
      return;
    }
    this->m_nLastReplyHp = CurTick;
    v2 = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 19))(this);
    if ( v2 < (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 20))(this) )
    {
      ReplyRate = 10;
      if ( (*((int (__fastcall **)(CObjPet *const))this->_vptr_Entity + 9))(this) <= 90 )
        ReplyRate = 20;
      NeedAddHp = (*((int (__fastcall **)(CObjPet *const))this->_vptr_Entity + 20))(this) / 100 * ReplyRate;
      (*((void (__fastcall **)(CObjPet *const, _QWORD))this->_vptr_Entity + 21))(this, NeedAddHp);
    }
  }
}


#####################################
bool __cdecl CObjPet::appendInfo(CObjPet *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  PetId_t PetId; // rdx
  int32_t BaseId; // edx
  CharId_t Cid; // rdx
  int16_t x; // dx
  int16_t y; // dx
  int16_t v9; // dx
  int16_t v10; // dx
  int32_t v11; // edx
  int32_t v12; // edx
  int32_t v13; // edx
  CExtCharPet *CharPet; // rax
  int32_t Star; // edx
  CExtCharPet *v16; // rax
  int32_t HuanHua; // edx
  int8_t Record; // dl
  int8_t v19; // al
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  std::string v21; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v22[17]; // [rsp+2Fh] [rbp-11h] BYREF

  if ( !this->m_pPlayer || !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  PetId = CObjPet::GetPetId(this);
  Answer::NetPacket::writeInt64(packet, PetId);
  BaseId = CObjPet::GetBaseId(this);
  Answer::NetPacket::writeInt32(packet, BaseId);
  Cid = Player::getCid(this->m_pPlayer);
  Answer::NetPacket::writeInt64(packet, Cid);
  Player::getName((const Player *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::allocator(v22);
  std::string::string(&v21, this->m_strName);
  Answer::NetPacket::writeUTF8(packet, &v21);
  std::string::~string(&v21);
  std::allocator<char>::~allocator(v22);
  x = StaticObj::getCurrentTile(this).x;
  Answer::NetPacket::writeInt16(packet, x);
  y = StaticObj::getCurrentTile(this).y;
  Answer::NetPacket::writeInt16(packet, y);
  v9 = Unit::getTargetTile(this).x;
  Answer::NetPacket::writeInt16(packet, v9);
  v10 = Unit::getTargetTile(this).y;
  Answer::NetPacket::writeInt16(packet, v10);
  v11 = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 26))(this);
  Answer::NetPacket::writeInt32(packet, v11);
  v12 = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 27))(this);
  Answer::NetPacket::writeInt32(packet, v12);
  Unit::packageBuffList(this, packet);
  v13 = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 28))(this);
  Answer::NetPacket::writeInt32(packet, v13);
  CharPet = Player::GetCharPet(this->m_pPlayer);
  Star = CExtCharPet::GetStar(CharPet);
  Answer::NetPacket::writeInt32(packet, Star);
  v16 = Player::GetCharPet(this->m_pPlayer);
  HuanHua = CExtCharPet::GetHuanHua(v16);
  Answer::NetPacket::writeInt32(packet, HuanHua);
  if ( Player::getRecord(this->m_pPlayer, 1030) <= 0 )
  {
    Answer::NetPacket::writeInt8(packet, 0);
  }
  else
  {
    Record = Player::getRecord(this->m_pPlayer, 1029);
    Answer::NetPacket::writeInt8(packet, Record);
  }
  v19 = Player::getRecord(this->m_pPlayer, 1153) > 0;
  Answer::NetPacket::writeInt8(packet, v19);
  return 1;
}


#####################################
int32_t __cdecl CObjPet::GetBaseId(const CObjPet *const this)
{
  if ( this->m_pCfgPet )
    return this->m_pCfgPet->m_nPetId;
  else
    return 0;
}


#####################################
void __cdecl CObjPet::CheckSkillOpen(CObjPet *const this, int32_t nStar)
{
  CfgData *v2; // rax
  const CfgPetTable *PetTable; // rax
  const CfgPetUpStar *pCfgUpStar; // [rsp+10h] [rbp-20h]
  int32_t nSkillSize; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pCfgPet )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    PetTable = CfgData::GetPetTable(v2);
    pCfgUpStar = CfgPetTable::GetPetUpStar(PetTable, nStar);
    if ( pCfgUpStar )
    {
      nSkillSize = std::vector<int>::size(&pCfgUpStar->vSkillLevel);
      for ( i = 0; i <= 8; ++i )
      {
        if ( i >= nSkillSize )
          this->m_vSkill[i].nLevel = 0;
        else
          this->m_vSkill[i].nLevel = *std::vector<int>::operator[](&pCfgUpStar->vSkillLevel, i);
      }
    }
  }
}


#####################################
void __cdecl CObjPet::Die(CObjPet *const this)
{
  CExtCharSkill *CharSkill; // rax
  CExtCharPet *CharPet; // rax

  this->m_bAlive = 0;
  this->m_nDieTick = Unit::getTick(this);
  this->m_nDieTime = Unit::getNow(this);
  CObjPet::ClearTarget(this);
  Unit::clearAddonSkills(this);
  CObjPet::Rest(this);
  if ( this->m_pPlayer )
  {
    if ( CObjPet::IsSummonPet(this) )
    {
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::CheckSummonBuff(CharSkill);
    }
    else
    {
      CharPet = Player::GetCharPet(this->m_pPlayer);
      CExtCharPet::SendPetInfo(CharPet);
    }
  }
  CObjPet::LeaveMap(this);
}


#####################################
bool __cdecl CObjPet::CheckRelive(CObjPet *const this)
{
  int32_t Now; // ebx

  if ( this->m_bAlive || CObjPet::IsSummonPet(this) )
    return 0;
  Now = Unit::getNow(this);
  if ( Now < CObjPet::getReliveTime(this) )
    return 0;
  this->m_bAlive = 1;
  this->m_nDieTime = 0;
  (*((void (__fastcall **)(CObjPet *const, __int64))this->_vptr_Entity + 22))(this, 100);
  return 1;
}


#####################################
void __cdecl CObjPet::SendPetStatus(CObjPet *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CExtCharPet *CharPet; // rax
  int32_t Star; // eax
  CExtCharPet *v5; // rax
  int32_t HuanHua; // eax
  int8_t Record; // al
  int8_t v8; // al
  uint32_t WOffset; // eax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  char v11; // [rsp+27h] [rbp-19h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( this->m_pMap )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DD7u);
      if ( packet )
      {
        Answer::NetPacket::writeInt64(packet, this->m_nPetId);
        CharPet = Player::GetCharPet(this->m_pPlayer);
        Star = CExtCharPet::GetStar(CharPet);
        Answer::NetPacket::writeInt32(packet, Star);
        v5 = Player::GetCharPet(this->m_pPlayer);
        HuanHua = CExtCharPet::GetHuanHua(v5);
        Answer::NetPacket::writeInt32(packet, HuanHua);
        std::allocator<char>::allocator(&v11);
        std::string::string(&val, this->m_strName);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        std::allocator<char>::~allocator(&v11);
        if ( Player::getRecord(this->m_pPlayer, 1030) <= 0 )
        {
          Answer::NetPacket::writeInt8(packet, 0);
        }
        else
        {
          Record = Player::getRecord(this->m_pPlayer, 1029);
          Answer::NetPacket::writeInt8(packet, Record);
        }
        v8 = Player::getRecord(this->m_pPlayer, 1153) > 0;
        Answer::NetPacket::writeInt8(packet, v8);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Map::broadcastAreaAround(this->m_pMap, packet, this);
      }
    }
  }
}


#####################################
bool __cdecl CObjPet::AppendPetInfo(CObjPet *const this, Answer::NetPacket *packet)
{
  int32_t ReliveTime; // edx
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+1Fh] [rbp-11h] BYREF

  if ( !packet )
    return 0;
  Answer::NetPacket::writeInt8(packet, this->m_nState);
  ReliveTime = CObjPet::getReliveTime(this);
  Answer::NetPacket::writeInt32(packet, ReliveTime);
  std::allocator<char>::allocator(v5);
  std::string::string(&val, this->m_strName);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(v5);
  CObjPet::appendAttrInfo(this, packet);
  CObjPet::appendEquipInfo(this, packet);
  Answer::NetPacket::writeInt8(packet, this->m_AiState);
  return 1;
}


#####################################
void __cdecl CObjPet::appendAttrInfo(CObjPet *const this, Answer::NetPacket *packet)
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
void __cdecl CObjPet::appendEquipInfo(CObjPet *const this, Answer::NetPacket *packet)
{
  uint32_t nOldOffset; // [rsp+10h] [rbp-10h]
  int8_t nCount; // [rsp+17h] [rbp-9h]
  uint32_t nNewOffset; // [rsp+18h] [rbp-8h]
  char i; // [rsp+1Fh] [rbp-1h]

  if ( packet )
  {
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    nCount = 0;
    Answer::NetPacket::writeInt8(packet, 0);
    for ( i = 0; i <= 3; ++i )
    {
      if ( this->m_vEquip[i] > 0 )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt32(packet, this->m_vEquip[i]);
        ++nCount;
      }
    }
    nNewOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt8(packet, nCount);
    Answer::NetPacket::setWOffset(packet, nNewOffset);
  }
}


#####################################
void __cdecl CObjPet::appendSkillInfo(CObjPet *const this, Answer::NetPacket *packet)
{
  uint32_t nOldOffset; // [rsp+10h] [rbp-10h]
  int8_t nCount; // [rsp+17h] [rbp-9h]
  uint32_t nNewOffset; // [rsp+18h] [rbp-8h]
  char i; // [rsp+1Fh] [rbp-1h]

  if ( packet )
  {
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    nCount = 0;
    Answer::NetPacket::writeInt8(packet, 0);
    for ( i = 0; i <= 8; ++i )
    {
      if ( this->m_vSkill[i].nId > 0 )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt32(packet, this->m_vSkill[i].nLevel);
        ++nCount;
      }
    }
    nNewOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt8(packet, nCount);
    Answer::NetPacket::setWOffset(packet, nNewOffset);
  }
}


#####################################
void __cdecl CObjPet::LearnSkill(CObjPet *const this, int8_t nSkillPos)
{
  if ( (unsigned __int8)nSkillPos <= 8u )
  {
    ++this->m_vSkill[nSkillPos].nLevel;
    CObjPet::recalAttr(this);
  }
}


#####################################
void __cdecl CObjPet::ChangeName(CObjPet *const this, const std::string *const strName)
{
  const char *v2; // rax

  v2 = (const char *)std::string::c_str((std::string *)strName);
  snprintf(this->m_strName, 0x1Eu, v2);
  if ( CObjPet::IsFighting(this) )
    CObjPet::SendPetStatus(this);
}


#####################################
void __cdecl CObjPet::ChangeAi(CObjPet *const this, int8_t State)
{
  if ( this->m_AiState != State )
  {
    this->m_AiState = State;
    if ( this->m_AiState == 1 )
      CObjPet::ClearTarget(this);
  }
}


#####################################
std::string __cdecl CObjPet::GetName(const CObjPet *const this)
{
  __int64 v1; // rsi
  _BYTE v3[17]; // [rsp+1Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(v3);
  std::string::string(this, v1 + 1160);
  std::allocator<char>::~allocator(v3);
  return (std::string)this;
}


#####################################
int32_t __cdecl CObjPet::OnMove(
        CObjPet *const this,
        int32_t mapID,
        int16_t currentX,
        int16_t currentY,
        int16_t targetX,
        int16_t targetY,
        int16_t finalX,
        int16_t finalY,
        Direction direction)
{
  Map *m_pMap; // rbx
  Position pos; // [rsp+30h] [rbp-40h] BYREF
  Position v17; // [rsp+40h] [rbp-30h] BYREF
  Tile *pCurrentTile; // [rsp+48h] [rbp-28h]
  Tile *pTargetTile; // [rsp+50h] [rbp-20h]
  Tile *pFinalTile; // [rsp+58h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 10002;
  if ( !this->m_pMap )
    return 10002;
  m_pMap = this->m_pMap;
  if ( m_pMap != StaticObj::getMap(this->m_pPlayer) || Map::GetMapId(this->m_pMap) != mapID )
    return 10002;
  pCurrentTile = Map::getTile(this->m_pMap, currentX, currentY);
  pTargetTile = Map::getTile(this->m_pMap, targetX, targetY);
  pFinalTile = Map::getTile(this->m_pMap, finalX, finalY);
  if ( !pCurrentTile || !pTargetTile || !pFinalTile )
    return 10002;
  Position::Position(&pos, finalX, finalY);
  Position::Position(&v17, currentX, currentY);
  if ( Position::tileDistance(&v17, &pos) > 20 )
    return 10002;
  Unit::setAtTile(this, this->m_pMap, currentX, currentY);
  Unit::setTargetTile(this, targetX, targetY);
  Unit::broadcastMove(this);
  return 0;
}


#####################################
void __cdecl CObjPet::LeaveMap(CObjPet *const this)
{
  if ( this->m_pMap )
  {
    CObjPet::ClearTarget(this);
    Unit::clearAddonSkills(this);
    CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_AWAY_FROM_MAP);
    Unit::broadcastLeave(this);
    Map::removePet(this->m_pMap, this);
    this->m_pMap = 0;
  }
}


#####################################
void __cdecl CObjPet::EnterMap(CObjPet *const this)
{
  Direction Direction; // r13d
  int32_t y; // r12d
  int32_t x; // ebx
  Position targetTile; // [rsp+10h] [rbp-30h]
  Map *pMap; // [rsp+18h] [rbp-28h]

  if ( this->m_pPlayer )
  {
    pMap = StaticObj::getMap(this->m_pPlayer);
    if ( pMap )
    {
      Direction = Unit::getDirection(this->m_pPlayer);
      y = StaticObj::getCurrentTile(this->m_pPlayer).y;
      x = StaticObj::getCurrentTile(this->m_pPlayer).x;
      targetTile = CObjPet::getFollowTile(this, x, y, Direction);
      Unit::setAtTile(this, pMap, targetTile.x, targetTile.y);
      Map::addPet(pMap, this);
      CObjPet::ClearTarget(this);
      CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_STAND);
    }
  }
}


#####################################
void __cdecl CObjPet::EnterMap(CObjPet *const this, const Position *const pos)
{
  Map *pMap; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    pMap = StaticObj::getMap(this->m_pPlayer);
    if ( pMap )
    {
      Unit::setAtTile(this, pMap, pos->x, pos->y);
      Map::addPet(pMap, this);
      CObjPet::ClearTarget(this);
      CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_STAND);
    }
  }
}


#####################################
void __cdecl CObjPet::OnLogout(CObjPet *const this)
{
  if ( this->m_pPlayer )
  {
    if ( this->m_pMap )
      CObjPet::LeaveMap(this);
  }
}


#####################################
void __cdecl CObjPet::checkSwitchMap(CObjPet *const this)
{
  Map *pMap; // [rsp+18h] [rbp-8h]

  if ( this->m_pPlayer )
  {
    pMap = StaticObj::getMap(this->m_pPlayer);
    if ( pMap )
    {
      if ( Unit::isAlive(this->m_pPlayer)
        && (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 22))(pMap)
        && this->m_pMap != pMap )
      {
        CObjPet::LeaveMap(this);
        CObjPet::EnterMap(this);
      }
    }
  }
}


#####################################
void __cdecl CObjPet::OnLevelUp(CObjPet *const this)
{
  CObjPet::recalAttr(this);
  if ( this->m_bAlive )
    (*((void (__fastcall **)(CObjPet *const, __int64))this->_vptr_Entity + 22))(this, 100);
  Unit::setNeedSync(this);
}


#####################################
int8_t __cdecl CObjPet::calTargetPriority(CObjPet *const this, const UnitHandle *const target)
{
  int32_t type; // eax
  int32_t RunnerId; // r12d
  EntityId_t id; // rbx
  GameService *v5; // rax
  Monster *pMonster; // [rsp+18h] [rbp-18h]

  type = target->type;
  switch ( type )
  {
    case 2:
      RunnerId = StaticObj::GetRunnerId(this);
      id = target->id;
      v5 = Answer::Singleton<GameService>::instance();
      pMonster = GameService::getMonster(v5, id, RunnerId);
      if ( pMonster )
      {
        if ( (*((unsigned __int8 (__fastcall **)(Monster *))pMonster->_vptr_Entity + 17))(pMonster) )
          return 2;
        else
          return 1;
      }
      else
      {
        return 0;
      }
    case 4:
      return 3;
    case 1:
      return 4;
    default:
      return 0;
  }
}


#####################################
void __cdecl CObjPet::AddTarget(CObjPet *const this, const UnitHandle *const target, bool bForce)
{
  Answer::Random *v3; // rax
  Answer::Random *v4; // rax

  if ( CObjPet::AliveFlag(this)
    && this->m_nState == PET_STATE::PS_FIGHTING
    && this->m_nFightState
    && !UnitHandle::operator==(&this->m_target, target) )
  {
    if ( target->type == 4 )
    {
      if ( this->m_target.type == 4 )
      {
        v3 = Answer::Singleton<Answer::Random>::instance();
        if ( Answer::Random::generate(v3, 1, 100) <= 69 )
          return;
      }
    }
    else if ( !UnitHandle::isEmpty(&this->m_target) )
    {
      if ( this->m_AiState == 1 )
        return;
      v4 = Answer::Singleton<Answer::Random>::instance();
      if ( Answer::Random::generate(v4, 1, 100) <= 69 )
        return;
    }
    if ( &this->m_target != target )
      memcpy(&this->m_target, target, 0xCu);
    CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_WALK_ATTACK);
  }
}


#####################################
void __cdecl CObjPet::ResetTargetTile(CObjPet *const this, int32_t tx, int32_t ty, Direction dir)
{
  bool v4; // al
  Position targetTile; // [rsp+20h] [rbp-20h]

  if ( this->m_pMap )
  {
    v4 = Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
      || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
      || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
      || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
      || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN);
    if ( !v4
      && (this->m_nFightState == PET_FIGHT_STATE::PFS_STAND || this->m_nFightState == PET_FIGHT_STATE::PFS_FOLLOW) )
    {
      targetTile = CObjPet::getFollowTile(this, tx, ty, dir);
      if ( Map::isWalkablePosition(this->m_pMap, targetTile.x, targetTile.y) )
        Unit::setTargetTile(this, targetTile.x, targetTile.y);
      else
        Unit::setTargetTile(this, tx, ty);
      Unit::broadcastMove(this);
      CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_FOLLOW);
    }
  }
}


#####################################
void __cdecl CObjPet::backToPlayer(CObjPet *const this)
{
  Direction Direction; // r13d
  int32_t y; // r12d
  int32_t x; // ebx

  if ( this->m_pPlayer )
  {
    if ( !Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
    {
      CObjPet::ClearTarget(this);
      CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_STAND);
      Direction = Unit::getDirection(this->m_pPlayer);
      y = StaticObj::getCurrentTile(this->m_pPlayer).y;
      x = StaticObj::getCurrentTile(this->m_pPlayer).x;
      CObjPet::ResetTargetTile(this, x, y, Direction);
    }
  }
}


#####################################
void __cdecl CObjPet::recalAttr(CObjPet *const this)
{
  Unit::ResetAttrs(this);
  CObjPet::initBaseAttr(this);
  CObjPet::addSystemAttr(this);
  CObjPet::addPassiveSkillAttr(this);
  CObjPet::addEquipAttr(this);
  CObjPet::addOtherAttr(this);
  CObjPet::addSummonAttr(this);
  Unit::adjustUnitAttr(this);
  Unit::setNeedSync(this);
}


#####################################
void __cdecl CObjPet::initBaseAttr(CObjPet *const this)
{
  int32_t addon; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > it; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF

  if ( this->m_pCfgPet && this->m_pPlayer )
  {
    for ( it._M_current = std::vector<AttrAddon>::begin(&this->m_pCfgPet->m_vBaseAttr)._M_current;
          ;
          __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<AttrAddon>::end(&this->m_pCfgPet->m_vBaseAttr)._M_current;
      if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&it, &__rhs) )
        break;
      addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&it)->addon;
      index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&it)->index;
      Unit::SetAttrValue(this, (const CObjAttrs::Index_T)index, addon);
    }
  }
}


#####################################
void __cdecl CObjPet::addSystemAttr(CObjPet *const this)
{
  CExtCharPet *CharPet; // rax

  if ( this->m_pPlayer )
  {
    CharPet = Player::GetCharPet(this->m_pPlayer);
    CExtCharPet::AddPetAttr(CharPet, this);
  }
}


#####################################
void __cdecl CObjPet::addPassiveSkillAttr(CObjPet *const this)
{
  int32_t nLevel; // r12d
  int32_t nId; // ebx
  CfgData *v3; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t skillid; // ebx
  CfgData *v6; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t v8; // ebx
  CfgData *v9; // rax
  const CfgSkillTable *v10; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  int32_t i; // [rsp+2Ch] [rbp-24h]
  const CfgTalent *pCfgTalent; // [rsp+30h] [rbp-20h]
  const CfgPassiveSkill *pCfgSkill; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 8; ++i )
    {
      if ( this->m_vSkill[i].nId > 0 && this->m_vSkill[i].nLevel > 0 )
      {
        nLevel = this->m_vSkill[i].nLevel;
        nId = this->m_vSkill[i].nId;
        v3 = Answer::Singleton<CfgData>::instance();
        TalentTable = CfgData::GetTalentTable(v3);
        pCfgTalent = CfgTalentTable::GetTalent(TalentTable, nId, nLevel);
        if ( pCfgTalent )
        {
          skillid = pCfgTalent->skillid;
          v6 = Answer::Singleton<CfgData>::instance();
          SkillTable = CfgData::GetSkillTable(v6);
          if ( CfgSkillTable::GetSkillType(SkillTable, skillid) == 2 )
          {
            v8 = pCfgTalent->skillid;
            v9 = Answer::Singleton<CfgData>::instance();
            v10 = CfgData::GetSkillTable(v9);
            pCfgSkill = CfgSkillTable::GetPassiveSkill(v10, v8);
            if ( pCfgSkill )
            {
              for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgSkill->vAttrs)._M_current;
                    ;
                    __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
              {
                __rhs._M_current = std::vector<AttrAddon>::end(&pCfgSkill->vAttrs)._M_current;
                if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
                  break;
                addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
                index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index;
                Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, addon);
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CObjPet::AddEquipAttr(CObjPet *const this, Unit *pTarget)
{
  CfgData *v2; // rax
  const CfgPetEquipTable *PetEquipTable; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  int8_t i; // [rsp+33h] [rbp-1Dh]
  int32_t nEquipId; // [rsp+34h] [rbp-1Ch]
  const CfgPetEquip *pCfgEquip; // [rsp+38h] [rbp-18h]

  if ( pTarget )
  {
    for ( i = 0; i <= 3; ++i )
    {
      nEquipId = this->m_vEquip[i];
      if ( nEquipId > 0 )
      {
        v2 = Answer::Singleton<CfgData>::instance();
        PetEquipTable = CfgData::GetPetEquipTable(v2);
        pCfgEquip = CfgPetEquipTable::GetEquip(PetEquipTable, nEquipId);
        if ( pCfgEquip )
        {
          for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgEquip->vOwnerAttr)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<AttrAddon>::end(&pCfgEquip->vOwnerAttr)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
              break;
            if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
            {
              addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
              index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index;
              Unit::AddAttrValue(pTarget, (const CObjAttrs::Index_T)index, addon);
            }
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CObjPet::GetSkillBattle(const CObjPet *const this)
{
  int32_t nLevel; // r12d
  int32_t nId; // ebx
  CfgData *v3; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t nBattle; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+14h] [rbp-1Ch]
  const CfgTalent *pCfgTalent; // [rsp+18h] [rbp-18h]

  nBattle = 0;
  for ( i = 0; i <= 8; ++i )
  {
    if ( this->m_vSkill[i].nId > 0 && this->m_vSkill[i].nLevel > 0 )
    {
      nLevel = this->m_vSkill[i].nLevel;
      nId = this->m_vSkill[i].nId;
      v3 = Answer::Singleton<CfgData>::instance();
      TalentTable = CfgData::GetTalentTable(v3);
      pCfgTalent = CfgTalentTable::GetTalent(TalentTable, nId, nLevel);
      if ( pCfgTalent )
        nBattle += pCfgTalent->battle;
    }
  }
  return nBattle;
}


#####################################
void __cdecl CObjPet::sendPetLearnSkill(CObjPet *const this, int32_t nSkill)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DD5u);
    if ( packet )
    {
      Answer::NetPacket::writeInt64(packet, this->m_nPetId);
      Answer::NetPacket::writeInt32(packet, nSkill);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CObjPet::broadcastPetSkillLevelUp(CObjPet *const this, int16_t nSkillId, int16_t nSkillLevel)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  int32_t BaseId; // eax
  PetId_t PetId; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 113);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      BaseId = CObjPet::GetBaseId(this);
      Answer::NetPacket::writeInt32(packet, BaseId);
      PetId = CObjPet::GetPetId(this);
      Answer::NetPacket::writeInt64(packet, PetId);
      Answer::NetPacket::writeInt16(packet, nSkillId);
      Answer::NetPacket::writeInt16(packet, nSkillLevel);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v10 = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v11, v10, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CObjPet::OnLoadFromDB(CObjPet *const this, const DBPet *const pet, int32_t nStar)
{
  CfgData *v3; // rax
  const CfgPetTable *PetTable; // rax
  int8_t i; // [rsp+2Eh] [rbp-2h]
  int8_t i_0; // [rsp+2Fh] [rbp-1h]

  v3 = Answer::Singleton<CfgData>::instance();
  PetTable = CfgData::GetPetTable(v3);
  this->m_pCfgPet = CfgPetTable::GetPet(PetTable, 101);
  if ( this->m_pCfgPet )
  {
    this->m_nPetId = pet->nPetId;
    this->m_bAlive = pet->bAlive > 0;
    this->m_nState = pet->nState;
    this->m_nDieTime = pet->nDieTime;
    this->m_AiState = pet->AiState;
    snprintf(this->m_strName, 0x1Eu, pet->strName);
    for ( i = 0; i <= 3; ++i )
      this->m_vEquip[i] = pet->vEquip[i];
    for ( i_0 = 0; i_0 <= 8; ++i_0 )
      this->m_vSkill[i_0].nId = this->m_pCfgPet->m_vSkill[i_0];
    CObjPet::CheckSkillOpen(this, nStar);
    CObjPet::recalAttr(this);
    Unit::setHP(this, pet->nHP);
  }
}


#####################################
void __cdecl CObjPet::OnSaveToDB(CObjPet *const this, DBPet *const pet)
{
  int8_t i; // [rsp+1Eh] [rbp-2h]
  int8_t i_0; // [rsp+1Fh] [rbp-1h]

  pet->nPetId = this->m_nPetId;
  pet->bAlive = this->m_bAlive;
  pet->nState = this->m_nState;
  pet->nHP = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 19))(this);
  pet->nDieTime = this->m_nDieTime;
  pet->AiState = this->m_AiState;
  snprintf(pet->strName, 0x1Eu, this->m_strName);
  for ( i = 0; i <= 3; ++i )
    pet->vEquip[i] = this->m_vEquip[i];
  for ( i_0 = 0; i_0 <= 8; ++i_0 )
    pet->vSkillLvel[i_0] = this->m_vSkill[i_0].nLevel;
}


#####################################
void __cdecl CObjPet::updateFightState(CObjPet *const this)
{
  PET_FIGHT_STATE m_nFightState; // eax

  CObjPet::checkFarAway(this);
  m_nFightState = this->m_nFightState;
  if ( m_nFightState == PET_FIGHT_STATE::PFS_FOLLOW )
  {
    CObjPet::onFollow(this);
  }
  else if ( m_nFightState > PET_FIGHT_STATE::PFS_FOLLOW )
  {
    if ( m_nFightState == PET_FIGHT_STATE::PFS_ATTACK )
    {
      CObjPet::onAttack(this);
    }
    else if ( m_nFightState == PET_FIGHT_STATE::PFS_WALK_ATTACK )
    {
      CObjPet::onWalkAttack(this);
    }
  }
  else if ( m_nFightState == PET_FIGHT_STATE::PFS_STAND )
  {
    CObjPet::onStand(this);
  }
}


#####################################
void __cdecl CObjPet::setFightState(CObjPet *const this, PET_FIGHT_STATE state)
{
  PET_FIGHT_STATE m_nFightState; // eax

  this->m_nFightState = state;
  m_nFightState = this->m_nFightState;
  if ( m_nFightState == PET_FIGHT_STATE::PFS_STAND || m_nFightState == PET_FIGHT_STATE::PFS_ATTACK )
    Unit::setStand(this);
}


#####################################
void __cdecl CObjPet::onStand(CObjPet *const this)
{
  int v1; // edx
  Position pos; // [rsp+20h] [rbp-50h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-40h] BYREF
  __int64 src; // [rsp+40h] [rbp-30h] BYREF
  int v5; // [rsp+48h] [rbp-28h]
  int64_t nowTime; // [rsp+50h] [rbp-20h]
  Unit *pUnit; // [rsp+58h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( this->m_pMap )
    {
      if ( CObjPet::AliveFlag(this) && this->m_AiState != 1 )
      {
        nowTime = Unit::getTick(this);
        if ( nowTime - this->m_nLastSkillTick > 499 )
        {
          pUnit = (Unit *)(*((__int64 (__fastcall **)(Map *, CObjPet *const))this->m_pMap->_vptr_Map + 27))(
                            this->m_pMap,
                            this);
          if ( pUnit )
          {
            pos = StaticObj::getCurrentTile(this);
            CurrentTile = StaticObj::getCurrentTile(pUnit);
            if ( Position::tileDistance(&CurrentTile, &pos) <= 5 )
            {
              src = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 12))(pUnit);
              v5 = v1;
              if ( &this->m_target != (UnitHandle *)&src )
                memcpy(&this->m_target, &src, 0xCu);
              CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_ATTACK);
            }
            else
            {
              CObjPet::backToPlayer(this);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CObjPet::onFollow(CObjPet *const this)
{
  Position param; // [rsp+10h] [rbp-20h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-10h] BYREF

  if ( this->m_pPlayer && this->m_pMap )
  {
    param = Unit::getTargetTile(this);
    CurrentTile = StaticObj::getCurrentTile(this);
    if ( Position::operator==(&CurrentTile, &param) )
      CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_STAND);
  }
}


#####################################
void __cdecl CObjPet::changeTarget(CObjPet *const this)
{
  int v1; // edx
  Position pos; // [rsp+20h] [rbp-50h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-40h] BYREF
  __int64 src; // [rsp+40h] [rbp-30h] BYREF
  int v5; // [rsp+48h] [rbp-28h]
  Unit *pUnit; // [rsp+58h] [rbp-18h]

  if ( this->m_AiState == 1 )
  {
    CObjPet::ClearTarget(this);
    CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_STAND);
  }
  else
  {
    pUnit = (Unit *)(*((__int64 (__fastcall **)(Map *, CObjPet *const))this->m_pMap->_vptr_Map + 27))(
                      this->m_pMap,
                      this);
    if ( pUnit )
    {
      pos = StaticObj::getCurrentTile(this);
      CurrentTile = StaticObj::getCurrentTile(pUnit);
      if ( Position::tileDistance(&CurrentTile, &pos) <= 5 )
      {
        src = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 12))(pUnit);
        v5 = v1;
        if ( &this->m_target != (UnitHandle *)&src )
          memcpy(&this->m_target, &src, 0xCu);
      }
      else
      {
        CObjPet::backToPlayer(this);
      }
    }
    else
    {
      CObjPet::backToPlayer(this);
    }
  }
}


#####################################
void __cdecl CObjPet::onAttack(CObjPet *const this)
{
  int32_t RunnerId; // r13d
  int32_t type; // r12d
  EntityId_t id; // rbx
  GameService *v4; // rax
  int32_t nLevel; // r12d
  int32_t nId; // ebx
  CfgData *v8; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t skillid; // ebx
  CfgData *v11; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t SkillFlag; // eax
  int32_t range; // eax
  int32_t v15; // edx
  char v16; // al
  int32_t v17; // r12d
  EntityId_t unitId; // rbx
  GameService *v19; // rax
  int32_t hpChange; // r12d
  int32_t addon_skill; // ebx
  CfgData *v23; // rax
  const CfgSkillTable *v24; // rax
  UnitAddonSkill addonSkill; // [rsp+30h] [rbp-160h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > it; // [rsp+50h] [rbp-140h] BYREF
  UnitVector targets; // [rsp+60h] [rbp-130h] BYREF
  Position pos; // [rsp+80h] [rbp-110h]
  SkillResultVector results; // [rsp+90h] [rbp-100h] BYREF
  Skill skill; // [rsp+B0h] [rbp-E0h] BYREF
  Position CurrentTile; // [rsp+C0h] [rbp-D0h] BYREF
  Position v32; // [rsp+D0h] [rbp-C0h] BYREF
  Position v33; // [rsp+E0h] [rbp-B0h] BYREF
  UnitHandle targetHandle; // [rsp+F0h] [rbp-A0h]
  Position v35; // [rsp+100h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > __rhs; // [rsp+110h] [rbp-80h] BYREF
  UnitHandle launcher; // [rsp+120h] [rbp-70h]
  Position v38; // [rsp+130h] [rbp-60h] BYREF
  int64_t nCurTick; // [rsp+138h] [rbp-58h]
  Unit *pTarget; // [rsp+140h] [rbp-50h]
  const CfgTalent *pCfgTalent; // [rsp+148h] [rbp-48h]
  const CfgActiveSkill *pCfgSkill; // [rsp+150h] [rbp-40h]
  int32_t tileDistance; // [rsp+158h] [rbp-38h]
  int32_t Valuse; // [rsp+15Ch] [rbp-34h]
  Player *victm; // [rsp+160h] [rbp-30h]
  const CfgActiveSkill *pCfgAddonSkill; // [rsp+168h] [rbp-28h]
  Position v47; // 0:rax.8
  UnitHandle v48; // 0:rsi.8,8:edx.4

  nCurTick = Unit::getTick(this);
  if ( nCurTick - this->m_nLastSkillTick > 499 )
  {
    if ( !this->m_pPlayer || !this->m_pMap )
      goto LABEL_24;
    if ( UnitHandle::isEmpty(&this->m_target)
      || (RunnerId = StaticObj::GetRunnerId(this),
          type = this->m_target.type,
          id = this->m_target.id,
          v4 = Answer::Singleton<GameService>::instance(),
          (pTarget = GameService::getUnit(v4, id, type, RunnerId)) == 0)
      || StaticObj::getMap(pTarget) != this->m_pMap
      || !Unit::isAlive(pTarget) )
    {
      CObjPet::changeTarget(this);
      return;
    }
    if ( !Unit::HasBuffState(this, CObjState::Index_T::OBS_CHENMO)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
    {
      if ( !this->m_pNextSkill )
        CObjPet::refreshSkill(this, nCurTick);
      if ( this->m_pNextSkill )
      {
        nLevel = this->m_pNextSkill->nLevel;
        nId = this->m_pNextSkill->nId;
        v8 = Answer::Singleton<CfgData>::instance();
        TalentTable = CfgData::GetTalentTable(v8);
        pCfgTalent = CfgTalentTable::GetTalent(TalentTable, nId, nLevel);
        if ( !pCfgTalent
          || (skillid = pCfgTalent->skillid,
              v11 = Answer::Singleton<CfgData>::instance(),
              SkillTable = CfgData::GetSkillTable(v11),
              (pCfgSkill = CfgSkillTable::GetActiveSkill(SkillTable, skillid)) == 0) )
        {
LABEL_24:
          CObjPet::backToPlayer(this);
          return;
        }
        CurrentTile = StaticObj::getCurrentTile(pTarget);
        v32 = StaticObj::getCurrentTile(this);
        tileDistance = Position::tileDistance(&v32, &CurrentTile);
        if ( pCfgSkill->distance < tileDistance )
        {
          CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_WALK_ATTACK);
          return;
        }
        SkillFlag = Unit::GetSkillFlag(this, 1);
        Skill::Skill(&skill, pCfgSkill, SkillFlag);
        std::vector<SkillResult>::vector(&results);
        range = pCfgSkill->range;
        if ( range )
        {
          if ( range != 1 )
          {
            v16 = (*((__int64 (__fastcall **)(CObjPet *const, const CfgActiveSkill *, Unit *))this->_vptr_Entity + 15))(
                    this,
                    pCfgSkill,
                    pTarget);
            if ( v16 == 1 )
            {
              pos = StaticObj::getCurrentTile(pTarget);
              if ( pCfgSkill->range == 4 || pCfgSkill->range == 2 )
                Unit::resetDirection(this, pos.x, pos.y);
              Map::getSkillTargets(&targets, this->m_pMap, this, pos, pCfgSkill);
              v47 = StaticObj::getCurrentTile(this);
              Skill::posAction(&skill, this, v47, pos, &targets, &results, 1);
              std::vector<Unit *>::~vector(&targets);
              goto LABEL_39;
            }
LABEL_32:
            CObjPet::backToPlayer(this);
LABEL_59:
            std::vector<SkillResult>::~vector(&results);
            Skill::~Skill(&skill);
            return;
          }
          if ( (*((unsigned __int8 (__fastcall **)(CObjPet *const, const CfgActiveSkill *, Unit *))this->_vptr_Entity
                + 15))(
                 this,
                 pCfgSkill,
                 pTarget) != 1 )
            goto LABEL_32;
          Position::Position(&v35, -1, -1);
          Skill::unitAction(&skill, this, this->m_target, &results, v35, 1);
        }
        else
        {
          Position::Position(&v33, -1, -1);
          targetHandle.id = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 12))(this);
          targetHandle.type = v15;
          Skill::unitAction(&skill, this, targetHandle, &results, v33, 1);
        }
LABEL_39:
        if ( !pCfgSkill->beneficial )
        {
          for ( it._M_current = std::vector<SkillResult>::begin(&results)._M_current;
                ;
                __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator++(&it) )
          {
            __rhs._M_current = std::vector<SkillResult>::end(&results)._M_current;
            if ( !__gnu_cxx::operator!=<SkillResult *,std::vector<SkillResult>>(&it, &__rhs) )
              break;
            if ( __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 1 )
            {
              v17 = StaticObj::GetRunnerId(this);
              unitId = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitId;
              v19 = Answer::Singleton<GameService>::instance();
              victm = GameService::getPlayer(v19, unitId, v17, 1);
              if ( victm )
              {
                hpChange = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->hpChange;
                launcher.id = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 12))(this);
                launcher.type = v48.type;
                v48.id = launcher.id;
                Player::onDamagedEvent(victm, v48, hpChange);
              }
            }
            if ( __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 1
              || __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitType == 4 )
            {
              Player::SetInPvP(this->m_pPlayer);
            }
          }
        }
        if ( pCfgSkill->addon_skill > 0 )
        {
          addon_skill = pCfgSkill->addon_skill;
          v23 = Answer::Singleton<CfgData>::instance();
          v24 = CfgData::GetSkillTable(v23);
          pCfgAddonSkill = CfgSkillTable::GetActiveSkill(v24, addon_skill);
          if ( pCfgAddonSkill )
          {
            Position::Position(&v38, 0, 0);
            addonSkill.nLastTrigTime = 0;
            addonSkill.nTrigTimes = 0;
            addonSkill.sTargetPos = v38;
            addonSkill.pCfgSkill = pCfgAddonSkill;
            addonSkill.nLastTrigTime = nCurTick + pCfgAddonSkill->addon_delay;
            addonSkill.sTargetPos = StaticObj::getCurrentTile(pTarget);
            std::list<UnitAddonSkill>::push_back(&this->m_lAddonSkill, &addonSkill);
          }
        }
        Valuse = 0;
        if ( pCfgSkill->cd <= 499 )
          this->m_pNextSkill->nCDTime = nCurTick + pCfgSkill->cd;
        else
          this->m_pNextSkill->nCDTime = nCurTick + pCfgSkill->cd - Valuse;
        this->m_nLastSkillTick = nCurTick;
        this->m_pNextSkill = 0;
        goto LABEL_59;
      }
    }
  }
}


#####################################
void __cdecl CObjPet::onWalkAttack(CObjPet *const this)
{
  int32_t RunnerId; // r13d
  int32_t type; // r12d
  EntityId_t id; // rbx
  GameService *v4; // rax
  int32_t nLevel; // r12d
  int32_t nId; // ebx
  CfgData *v7; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t skillid; // ebx
  CfgData *v10; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t v12; // eax
  Position pos; // [rsp+10h] [rbp-90h]
  Position CurrentTile; // [rsp+20h] [rbp-80h] BYREF
  Position v15; // [rsp+30h] [rbp-70h] BYREF
  Position srcPos; // [rsp+40h] [rbp-60h] BYREF
  Position tarPos; // [rsp+50h] [rbp-50h] BYREF
  Unit *pTarget; // [rsp+60h] [rbp-40h]
  PetSkillInfo *pSkillInfo; // [rsp+68h] [rbp-38h]
  const CfgTalent *pCfgTalent; // [rsp+70h] [rbp-30h]
  const CfgActiveSkill *pSkill; // [rsp+78h] [rbp-28h]

  if ( !this->m_pPlayer || !this->m_pMap )
    goto LABEL_14;
  if ( UnitHandle::isEmpty(&this->m_target)
    || (RunnerId = StaticObj::GetRunnerId(this),
        type = this->m_target.type,
        id = this->m_target.id,
        v4 = Answer::Singleton<GameService>::instance(),
        (pTarget = GameService::getUnit(v4, id, type, RunnerId)) == 0)
    || !Unit::isAlive(pTarget)
    || StaticObj::getMap(pTarget) != this->m_pMap )
  {
    CObjPet::changeTarget(this);
    return;
  }
  pSkillInfo = CObjPet::GetSkill(this, 0);
  if ( !pSkillInfo )
    goto LABEL_14;
  nLevel = pSkillInfo->nLevel;
  nId = pSkillInfo->nId;
  v7 = Answer::Singleton<CfgData>::instance();
  TalentTable = CfgData::GetTalentTable(v7);
  pCfgTalent = CfgTalentTable::GetTalent(TalentTable, nId, nLevel);
  if ( !pCfgTalent )
    goto LABEL_14;
  skillid = pCfgTalent->skillid;
  v10 = Answer::Singleton<CfgData>::instance();
  SkillTable = CfgData::GetSkillTable(v10);
  pSkill = CfgSkillTable::GetActiveSkill(SkillTable, skillid);
  if ( pSkill )
  {
    CurrentTile = StaticObj::getCurrentTile(pTarget);
    v15 = StaticObj::getCurrentTile(this);
    v12 = Position::tileDistance(&v15, &CurrentTile);
    if ( v12 > pSkill->distance )
    {
      if ( !Unit::isMoving(this) )
      {
        srcPos = StaticObj::getCurrentTile(this);
        tarPos = StaticObj::getCurrentTile(pTarget);
        pos = Map::getNearestWalkableAroundPosition(this->m_pMap, &tarPos, &srcPos);
        if ( Map::isWalkablePosition(this->m_pMap, pos.x, pos.y) )
        {
          Unit::setTargetTile(this, pos.x, pos.y);
          Unit::broadcastMove(this);
        }
        else
        {
          CObjPet::backToPlayer(this);
        }
      }
    }
    else
    {
      CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_ATTACK);
    }
  }
  else
  {
LABEL_14:
    CObjPet::backToPlayer(this);
  }
}


#####################################
void __cdecl CObjPet::checkFarAway(CObjPet *const this)
{
  Direction Direction; // r13d
  int32_t y; // r12d
  int32_t x; // ebx
  Direction v5; // r13d
  int32_t v6; // r12d
  int32_t v7; // ebx
  Position targetTile; // [rsp+10h] [rbp-50h]
  Position pos; // [rsp+20h] [rbp-40h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-30h] BYREF

  if ( this->m_pPlayer )
  {
    if ( !Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
      && !Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN)
      && this->m_nFightState != PET_FIGHT_STATE::PFS_ATTACK )
    {
      pos = StaticObj::getCurrentTile(this->m_pPlayer);
      CurrentTile = StaticObj::getCurrentTile(this);
      if ( Position::tileDistance(&CurrentTile, &pos) > 15 )
      {
        CObjPet::ClearTarget(this);
        Direction = Unit::getDirection(this->m_pPlayer);
        y = StaticObj::getCurrentTile(this->m_pPlayer).y;
        x = StaticObj::getCurrentTile(this->m_pPlayer).x;
        targetTile = CObjPet::getFollowTile(this, x, y, Direction);
        Unit::instantMove(this, targetTile.x, targetTile.y, InstanceMoveReason::IMR_BACK_PET, 0);
        CObjPet::setFightState(this, PET_FIGHT_STATE::PFS_STAND);
        if ( Unit::isMoving(this->m_pPlayer) )
        {
          v5 = Unit::getDirection(this->m_pPlayer);
          v6 = Unit::getTargetTile(this->m_pPlayer).y;
          v7 = Unit::getTargetTile(this->m_pPlayer).x;
          CObjPet::ResetTargetTile(this, v7, v6, v5);
        }
      }
    }
  }
}


#####################################
void __cdecl CObjPet::checkSpeed(CObjPet *const this)
{
  int v1; // ebx
  int32_t v2; // edx

  if ( this->m_pPlayer )
  {
    v1 = (*((__int64 (__fastcall **)(CObjPet *const))this->_vptr_Entity + 28))(this);
    if ( v1 != (*((unsigned int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 28))(this->m_pPlayer) )
    {
      v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 28))(this->m_pPlayer);
      Unit::SetAttrValue(this, CObjAttrs::Index_T::ATTR_MOV_SPD, v2);
      Unit::setNeedSync(this);
    }
  }
}


#####################################
int32_t __cdecl CObjPet::calAddBattle(const CObjPet *const this, int32_t nIndex)
{
  if ( nIndex <= 0 )
    return 0;
  switch ( nIndex )
  {
    case 1:
      return 20;
    case 2:
      return 19;
    case 3:
      return 18;
  }
  if ( nIndex <= 10 )
    return 15;
  if ( nIndex <= 20 )
    return 13;
  if ( nIndex <= 50 )
    return 12;
  if ( nIndex <= 80 )
    return 10;
  if ( nIndex <= 90 )
    return 8;
  if ( nIndex > 100 )
    return 0;
  return 5;
}


#####################################
void __cdecl CObjPet::addEquipAttr(CObjPet *const this)
{
  CfgData *v1; // rax
  const CfgPetEquipTable *PetEquipTable; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  int8_t i; // [rsp+33h] [rbp-1Dh]
  int32_t nEquipId; // [rsp+34h] [rbp-1Ch]
  const CfgPetEquip *pCfgEquip; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 3; ++i )
    {
      nEquipId = this->m_vEquip[i];
      if ( nEquipId > 0 )
      {
        v1 = Answer::Singleton<CfgData>::instance();
        PetEquipTable = CfgData::GetPetEquipTable(v1);
        pCfgEquip = CfgPetEquipTable::GetEquip(PetEquipTable, nEquipId);
        if ( pCfgEquip )
        {
          for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgEquip->vAttr)._M_current;
                ;
                __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
          {
            __rhs._M_current = std::vector<AttrAddon>::end(&pCfgEquip->vAttr)._M_current;
            if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
              break;
            if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
            {
              addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
              index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index;
              Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, addon);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CObjPet::addSummonAttr(CObjPet *const this)
{
  int32_t m_nSummonSkillId; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  const AttrAddon *v5; // rax
  int32_t AttrValue; // ebx
  int32_t v7; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  const CfgActiveSkill *pCfgSkill; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer && CObjPet::IsSummonPet(this) )
  {
    m_nSummonSkillId = this->m_nSummonSkillId;
    v3 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v3);
    pCfgSkill = CfgSkillTable::GetActiveSkill(SkillTable, m_nSummonSkillId);
    if ( pCfgSkill )
    {
      for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgSkill->summon_attr)._M_current;
            ;
            __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<AttrAddon>::end(&pCfgSkill->summon_attr)._M_current;
        if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
          break;
        if ( __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon > 0 )
        {
          v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
          AttrValue = Unit::GetAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index);
          v7 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon
             * AttrValue
             / 100;
          index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index;
          Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, v7);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CObjPet::GetEquip(CObjPet *const this, int8_t nPos)
{
  if ( (unsigned __int8)nPos < 4u )
    return this->m_vEquip[nPos];
  else
    return 0;
}


#####################################
void __cdecl CObjPet::SetEquip(CObjPet *const this, int8_t nPos, int32_t nEquipId)
{
  if ( (unsigned __int8)nPos < 4u )
  {
    this->m_vEquip[nPos] = nEquipId;
    CObjPet::recalAttr(this);
  }
}


#####################################
void __cdecl CObjPet::refreshSkill(CObjPet *const this, int64_t nCurTick)
{
  int32_t nLevel; // r12d
  int32_t nId; // ebx
  CfgData *v4; // rax
  const CfgTalentTable *TalentTable; // rax
  int32_t skillid; // ebx
  CfgData *v7; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t i; // [rsp+14h] [rbp-1Ch]
  const CfgTalent *pCfgTalent; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 8; ++i )
    {
      if ( this->m_vSkill[i].nId > 0 && this->m_vSkill[i].nLevel > 0 )
      {
        nLevel = this->m_vSkill[i].nLevel;
        nId = this->m_vSkill[i].nId;
        v4 = Answer::Singleton<CfgData>::instance();
        TalentTable = CfgData::GetTalentTable(v4);
        pCfgTalent = CfgTalentTable::GetTalent(TalentTable, nId, nLevel);
        if ( pCfgTalent )
        {
          skillid = pCfgTalent->skillid;
          v7 = Answer::Singleton<CfgData>::instance();
          SkillTable = CfgData::GetSkillTable(v7);
          if ( CfgSkillTable::GetSkillType(SkillTable, skillid) == 1 && this->m_vSkill[i].nCDTime <= nCurTick )
          {
            this->m_pNextSkill = &this->m_vSkill[i];
            return;
          }
        }
      }
    }
  }
}


