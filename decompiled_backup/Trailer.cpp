// Decompiled methods for class: Trailer
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl Trailer::~Trailer(Trailer *const this)
{
  Trailer::~Trailer(this);
  operator delete(this);
}


#####################################
void __cdecl Trailer::init(
        Trailer *const this,
        const CfgTrailer *const cfgTrailer,
        CharId_t CharId,
        std::string *p_Name,
        int32_t level,
        int32_t nEndTime,
        int32_t RewardTimes,
        int32_t SubTime)
{
  int32_t m_nAddAttrValue; // ebx
  CObjAttrs::Index_T m_nAddAttrType; // ecx
  std::_List_iterator<AddAttribute> it; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+40h] [rbp-20h] BYREF

  CfgTrailer::operator=(&this->m_cfgTrailer, cfgTrailer);
  this->m_nEndTime = nEndTime;
  this->m_Owner = CharId;
  this->m_State = 0;
  this->m_DieTick = 0;
  std::string::operator=(&this->m_Name, p_Name);
  this->m_Level = level;
  std::string::operator=(&this->m_RobberyName, &unk_8F360F);
  this->m_RobberyId = 0;
  this->m_RewardTimes = RewardTimes;
  this->m_SubTime = SubTime;
  for ( it._M_node = std::list<AddAttribute>::begin(&this->m_cfgTrailer.nAttrList)._M_node;
        ;
        std::_List_iterator<AddAttribute>::operator++(&it, 0) )
  {
    __x._M_node = std::list<AddAttribute>::end(&this->m_cfgTrailer.nAttrList)._M_node;
    if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
      break;
    m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
    m_nAddAttrType = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrType;
    Unit::AddAttrValue(this, m_nAddAttrType, m_nAddAttrValue);
  }
  (*((void (__fastcall **)(Trailer *const, __int64))this->_vptr_Entity + 22))(this, 100);
}


#####################################
void __cdecl Trailer::reset(Trailer *const this)
{
  Unit::reset(this);
  this->m_nEndTime = 0;
  this->m_Owner = 0;
  this->m_State = 0;
  this->m_DieTick = 0;
  std::string::operator=(&this->m_RobberyName, &unk_8F360F);
  this->m_RobberyId = 0;
  this->m_RewardTimes = 0;
}


#####################################
bool __cdecl Trailer::refresh(Trailer *const this)
{
  Trailer::CheckTrailerEnd(this);
  if ( this->m_DieTick > 0 && Unit::getTick(this) - this->m_DieTick > 3000 )
  {
    this->m_DieTick = 0;
    (*((void (__fastcall **)(Trailer *const, __int64))this->_vptr_Entity + 22))(this, 100);
    if ( this->m_pMap )
      Map::broadcastIntoMap(this->m_pMap, this);
  }
  return 0;
}


#####################################
bool __cdecl Trailer::appendInfo(Trailer *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  int64_t v4; // rdx
  int16_t x; // dx
  int16_t y; // dx
  int16_t v7; // dx
  int16_t v8; // dx
  int32_t v9; // edx
  int32_t v10; // edx
  int32_t v11; // edx

  if ( !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  v4 = (*((__int64 (__fastcall **)(Trailer *const))this->_vptr_Entity + 2))(this);
  Answer::NetPacket::writeInt64(packet, v4);
  Answer::NetPacket::writeInt32(packet, this->m_cfgTrailer.nId);
  Answer::NetPacket::writeInt8(packet, this->m_State);
  Answer::NetPacket::writeInt64(packet, this->m_Owner);
  Answer::NetPacket::writeUTF8(packet, &this->m_Name);
  x = StaticObj::getCurrentTile(this).x;
  Answer::NetPacket::writeInt16(packet, x);
  y = StaticObj::getCurrentTile(this).y;
  Answer::NetPacket::writeInt16(packet, y);
  v7 = Unit::getTargetTile(this).x;
  Answer::NetPacket::writeInt16(packet, v7);
  v8 = Unit::getTargetTile(this).y;
  Answer::NetPacket::writeInt16(packet, v8);
  v9 = (*((__int64 (__fastcall **)(Trailer *const))this->_vptr_Entity + 26))(this);
  Answer::NetPacket::writeInt32(packet, v9);
  v10 = (*((__int64 (__fastcall **)(Trailer *const))this->_vptr_Entity + 27))(this);
  Answer::NetPacket::writeInt32(packet, v10);
  v11 = (*((__int64 (__fastcall **)(Trailer *const))this->_vptr_Entity + 28))(this);
  Answer::NetPacket::writeInt32(packet, v11);
  return 1;
}


#####################################
void __cdecl Trailer::LeaveMap(Trailer *const this)
{
  if ( this->m_pMap )
  {
    Map::removeTrailer(this->m_pMap, this);
    Unit::broadcastLeave(this);
    this->m_pMap = 0;
  }
}


#####################################
void __cdecl Trailer::EnterMap(Trailer *const this, Map *pMap, int32_t tx, int32_t ty)
{
  if ( pMap )
  {
    Map::addTrailer(pMap, this, tx, ty);
    this->m_pMap = pMap;
  }
}


#####################################
void __cdecl Trailer::SendInfo(Trailer *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t m_nEndTime; // ebx
  int32_t v5; // edx
  int8_t v6; // al
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player && this->m_pMap )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EF0u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgTrailer.TrailerQuality);
      m_nEndTime = this->m_nEndTime;
      v5 = m_nEndTime - Unit::getNow(this);
      Answer::NetPacket::writeInt32(packet, v5);
      Answer::NetPacket::writeInt32(packet, this->m_Level);
      v6 = Trailer::Robbery(this);
      Answer::NetPacket::writeInt8(packet, v6);
      Answer::NetPacket::writeUTF8(packet, &this->m_RobberyName);
      Answer::NetPacket::writeInt64(packet, this->m_RobberyId);
      Answer::NetPacket::writeInt32(packet, this->m_RewardTimes);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      LOBYTE(m_nEndTime) = Player::getConnId(player);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, m_nEndTime, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Trailer::SendPos(Trailer *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t MapId; // edx
  int32_t x; // edx
  int32_t y; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player && this->m_pMap )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EF1u);
    if ( packet )
    {
      MapId = Map::GetMapId(this->m_pMap);
      Answer::NetPacket::writeInt32(packet, MapId);
      x = StaticObj::getCurrentTile(this).x;
      Answer::NetPacket::writeInt32(packet, x);
      y = StaticObj::getCurrentTile(this).y;
      Answer::NetPacket::writeInt32(packet, y);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v9 = Player::getConnId(player);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl Trailer::isLifeEnd(Trailer *const this)
{
  return this->m_nEndTime > 0 && Unit::getNow(this) > this->m_nEndTime;
}


#####################################
void __cdecl Trailer::CheckTrailerEnd(Trailer *const this)
{
  int32_t RunnerId; // r12d
  CharId_t m_Owner; // rbx
  GameService *v4; // rax
  CMoneyRewardTask *CMoneyRewardTask; // rax
  CMoneyRewardTask *v6; // rax
  CMoneyRewardTask *v7; // rax
  Player *pPlayer; // [rsp+18h] [rbp-18h]

  if ( this->m_nEndTime > 0 && Unit::getNow(this) > this->m_nEndTime )
  {
    RunnerId = StaticObj::GetRunnerId(this);
    m_Owner = this->m_Owner;
    v4 = Answer::Singleton<GameService>::instance();
    pPlayer = GameService::getPlayer(v4, m_Owner, RunnerId, 1);
    if ( pPlayer )
    {
      CMoneyRewardTask = Player::GetCMoneyRewardTask(pPlayer);
      CMoneyRewardTask::SendTRailerEnd(CMoneyRewardTask);
      v6 = Player::GetCMoneyRewardTask(pPlayer);
      CMoneyRewardTask::SetTrailerTime(v6, 0);
      Player::setTrailer(pPlayer, 0);
      v7 = Player::GetCMoneyRewardTask(pPlayer);
      CMoneyRewardTask::ResetTrailer(v7);
    }
  }
}


#####################################
int32_t __cdecl Trailer::move(
        Trailer *const this,
        int32_t mapID,
        int16_t currentX,
        int16_t currentY,
        int16_t targetX,
        int16_t targetY,
        int16_t finalX,
        int16_t finalY,
        Direction direction)
{
  Tile *pCurrentTile; // [rsp+30h] [rbp-20h]
  Tile *pTargetTile; // [rsp+38h] [rbp-18h]

  if ( !this->m_pMap )
    return 10002;
  pCurrentTile = Map::getTile(this->m_pMap, currentX, currentY);
  pTargetTile = Map::getTile(this->m_pMap, targetX, targetY);
  if ( !pCurrentTile || !pTargetTile )
    return 10002;
  Unit::setTargetTile(this, targetX, targetY);
  Unit::broadcastMove(this);
  return 0;
}


#####################################
float __cdecl Trailer::GetRate(Trailer *const this)
{
  if ( this->m_Level <= 299 )
    return 1.0;
  if ( this->m_Level <= 399 )
    return 1.125;
  if ( this->m_Level <= 499 )
    return 1.25;
  if ( this->m_Level > 599 )
    return 1.5;
  return 1.375;
}


#####################################
int32_t __cdecl Trailer::GetRewardTimes(Trailer *const this)
{
  if ( this->m_RewardTimes <= 0 || this->m_RewardTimes > 2 )
    this->m_RewardTimes = 1;
  return this->m_RewardTimes;
}


