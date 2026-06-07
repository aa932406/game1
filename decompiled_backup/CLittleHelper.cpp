// Decompiled methods for class: CLittleHelper
// Source: gameserver.cc
// Total methods: 21

#####################################
void __cdecl CLittleHelper::~CLittleHelper(CLittleHelper *const this)
{
  CLittleHelper::~CLittleHelper(this);
  operator delete(this);
}


#####################################
void __cdecl CLittleHelper::reset(CLittleHelper *const this)
{
  this->m_pPlayer = 0;
  this->m_LittleHelperId = 0;
  this->m_Clothes = 0;
  *(_QWORD *)&this->m_nStandPlace = (unsigned int)this->m_nStandPlace;
  this->m_WorkState = LITTLE_HELPER_WORK_STATE::LHWS_AWAY_FROM_MAP;
  this->m_TarDropId = 0;
  this->m_PickTick = 0;
  this->m_LastTick = 0;
}


#####################################
bool __cdecl CLittleHelper::refresh(CLittleHelper *const this)
{
  if ( this->m_nState == LITTLE_HELPER_STATE::LHS_WORK )
  {
    if ( !this->m_pPlayer )
      return 0;
    if ( Unit::isAlive(this->m_pPlayer) )
    {
      CLittleHelper::CheckSwitchMap(this);
      CLittleHelper::updateState(this);
    }
  }
  return 0;
}


#####################################
bool __cdecl CLittleHelper::appendInfo(CLittleHelper *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  EntityId_t EntityId; // rdx
  CharId_t Cid; // rdx
  int16_t x; // dx
  int16_t y; // dx
  int16_t v8; // dx
  int16_t v9; // dx
  std::string val; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !packet )
    return 0;
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  EntityId = Entity::getEntityId(this);
  Answer::NetPacket::writeInt64(packet, EntityId);
  Cid = Player::getCid(this->m_pPlayer);
  Answer::NetPacket::writeInt64(packet, Cid);
  Player::getName((const Player *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  Answer::NetPacket::writeInt32(packet, this->m_LittleHelperId);
  Answer::NetPacket::writeInt32(packet, this->m_Clothes);
  x = StaticObj::getCurrentTile(this).x;
  Answer::NetPacket::writeInt16(packet, x);
  y = StaticObj::getCurrentTile(this).y;
  Answer::NetPacket::writeInt16(packet, y);
  v8 = Unit::getTargetTile(this).x;
  Answer::NetPacket::writeInt16(packet, v8);
  v9 = Unit::getTargetTile(this).y;
  Answer::NetPacket::writeInt16(packet, v9);
  return 1;
}


#####################################
void __cdecl CLittleHelper::init(CLittleHelper *const this, Player *Player, int32_t LittleHelperId, int32_t Clothes)
{
  this->m_pPlayer = Player;
  this->m_LittleHelperId = LittleHelperId;
  this->m_Clothes = Clothes;
  this->m_nStandPlace = Direction::LEFT;
  this->m_nState = LITTLE_HELPER_STATE::LHS_REST;
  CLittleHelper::AddAttr(this);
}


#####################################
void __cdecl CLittleHelper::AddAttr(CLittleHelper *const this)
{
  int32_t m_LittleHelperId; // ebx
  CfgData *v2; // rax
  const LittleHelperCfg *pLittleHelper; // [rsp+18h] [rbp-18h]

  m_LittleHelperId = this->m_LittleHelperId;
  v2 = Answer::Singleton<CfgData>::instance();
  pLittleHelper = CfgData::GetLittleHelperCfg(v2, m_LittleHelperId);
  if ( pLittleHelper )
    Unit::SetAttrValue(this, CObjAttrs::Index_T::ATTR_MOV_SPD, pLittleHelper->nSpeed);
}


#####################################
void __cdecl CLittleHelper::EnterMap(CLittleHelper *const this)
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
      targetTile = CLittleHelper::getFollowTile(this, x, y, Direction);
      Unit::setAtTile(this, pMap, targetTile.x, targetTile.y);
      Map::AddLittleHelper(pMap, this);
      CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_STAND);
    }
  }
}


#####################################
void __cdecl CLittleHelper::LeaveMap(CLittleHelper *const this)
{
  if ( this->m_pMap )
  {
    CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_AWAY_FROM_MAP);
    Unit::broadcastLeave(this);
    Map::removeLittleHelper(this->m_pMap, this);
    this->m_pMap = 0;
  }
}


#####################################
void __cdecl CLittleHelper::OnLogout(CLittleHelper *const this)
{
  if ( this->m_pPlayer )
  {
    if ( this->m_pMap )
      CLittleHelper::LeaveMap(this);
  }
}


#####################################
void __cdecl CLittleHelper::CheckSwitchMap(CLittleHelper *const this)
{
  Map *pMap; // [rsp+18h] [rbp-8h]

  if ( this->m_pPlayer )
  {
    pMap = StaticObj::getMap(this->m_pPlayer);
    if ( pMap )
    {
      if ( Unit::isAlive(this->m_pPlayer) && this->m_pMap != pMap )
      {
        CLittleHelper::LeaveMap(this);
        CLittleHelper::EnterMap(this);
      }
    }
  }
}


#####################################
void __cdecl CLittleHelper::ChangeClothe(CLittleHelper *const this, int32_t ClotheId)
{
  this->m_Clothes = ClotheId;
  CLittleHelper::SynsAreaAround(this);
}


#####################################
void __cdecl CLittleHelper::ChangeLittleHelperId(CLittleHelper *const this, int32_t LittleHelperId, int32_t ClotheId)
{
  this->m_LittleHelperId = LittleHelperId;
  this->m_Clothes = ClotheId;
  CLittleHelper::AddAttr(this);
  CLittleHelper::SynsAreaAround(this);
}


#####################################
void __cdecl CLittleHelper::SynsAreaAround(CLittleHelper *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  EntityId_t EntityId; // rdx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && this->m_pMap )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DE9u);
    if ( packet )
    {
      EntityId = Entity::getEntityId(this);
      Answer::NetPacket::writeInt64(packet, EntityId);
      Answer::NetPacket::writeInt32(packet, this->m_LittleHelperId);
      Answer::NetPacket::writeInt32(packet, this->m_Clothes);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl CLittleHelper::updateState(CLittleHelper *const this)
{
  LITTLE_HELPER_WORK_STATE m_WorkState; // eax
  int64_t CurrTick; // [rsp+18h] [rbp-8h]

  CurrTick = Unit::getTick(this);
  if ( CurrTick - this->m_LastTick > 199 )
  {
    this->m_LastTick = CurrTick;
    m_WorkState = this->m_WorkState;
    if ( m_WorkState == LITTLE_HELPER_WORK_STATE::LHWS_FOLLOW )
    {
      CLittleHelper::onFollow(this);
    }
    else if ( m_WorkState > LITTLE_HELPER_WORK_STATE::LHWS_FOLLOW )
    {
      if ( m_WorkState == LITTLE_HELPER_WORK_STATE::LHWS_WALK_PICK )
      {
        CLittleHelper::onWalkPick(this);
      }
      else if ( m_WorkState == LITTLE_HELPER_WORK_STATE::LHWS_PICK )
      {
        CLittleHelper::onPick(this);
      }
    }
    else if ( m_WorkState == LITTLE_HELPER_WORK_STATE::LHWS_STAND )
    {
      CLittleHelper::onStand(this);
    }
    CLittleHelper::checkFarAway(this);
  }
}


#####################################
void __cdecl CLittleHelper::checkFarAway(CLittleHelper *const this)
{
  Direction Direction; // r13d
  int32_t y; // r12d
  int32_t x; // ebx
  Direction v4; // r13d
  int32_t v5; // r12d
  int32_t v6; // ebx
  Position targetTile; // [rsp+10h] [rbp-50h]
  Position pos; // [rsp+20h] [rbp-40h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-30h] BYREF

  if ( this->m_pPlayer )
  {
    if ( this->m_nState != 3 )
    {
      pos = StaticObj::getCurrentTile(this->m_pPlayer);
      CurrentTile = StaticObj::getCurrentTile(this);
      if ( Position::tileDistance(&CurrentTile, &pos) > 15 )
      {
        Direction = Unit::getDirection(this->m_pPlayer);
        y = StaticObj::getCurrentTile(this->m_pPlayer).y;
        x = StaticObj::getCurrentTile(this->m_pPlayer).x;
        targetTile = CLittleHelper::getFollowTile(this, x, y, Direction);
        Unit::instantMove(this, targetTile.x, targetTile.y, InstanceMoveReason::IMR_LITTLE_HELPER, 0);
        CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_STAND);
        if ( Unit::isMoving(this->m_pPlayer) )
        {
          v4 = Unit::getDirection(this->m_pPlayer);
          v5 = Unit::getTargetTile(this->m_pPlayer).y;
          v6 = Unit::getTargetTile(this->m_pPlayer).x;
          CLittleHelper::ResetTargetTile(this, v6, v5, v4);
        }
      }
    }
  }
}


#####################################
void __cdecl CLittleHelper::ResetTargetTile(CLittleHelper *const this, int32_t tx, int32_t ty, Direction dir)
{
  Position targetTile; // [rsp+20h] [rbp-20h]

  if ( this->m_pMap
    && (this->m_WorkState == LITTLE_HELPER_WORK_STATE::LHWS_STAND
     || this->m_WorkState == LITTLE_HELPER_WORK_STATE::LHWS_FOLLOW) )
  {
    targetTile = CLittleHelper::getFollowTile(this, tx, ty, dir);
    if ( Map::isWalkablePosition(this->m_pMap, targetTile.x, targetTile.y) )
      Unit::setTargetTile(this, targetTile.x, targetTile.y);
    else
      Unit::setTargetTile(this, tx, ty);
    Unit::broadcastMove(this);
    CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_FOLLOW);
  }
}


#####################################
void __cdecl CLittleHelper::onStand(CLittleHelper *const this)
{
  if ( this->m_pPlayer )
  {
    if ( this->m_pMap )
      CLittleHelper::ChangeTarget(this);
  }
}


#####################################
void __cdecl CLittleHelper::ChangeTarget(CLittleHelper *const this)
{
  int32_t y; // ebx
  int32_t x; // ecx
  CDropItem *pItem; // [rsp+18h] [rbp-18h]

  if ( this->m_pMap )
  {
    pItem = Map::GetNearestDropItem(this->m_pMap, this);
    if ( pItem )
    {
      this->m_TarDropId = Entity::getEntityId(pItem);
      y = StaticObj::getCurrentTile(pItem).y;
      x = StaticObj::getCurrentTile(pItem).x;
      Unit::setTargetTile(this, x, y);
      Unit::broadcastMove(this);
      CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_WALK_PICK);
    }
    else
    {
      this->m_TarDropId = 0;
      CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_STAND);
    }
  }
}


#####################################
void __cdecl CLittleHelper::onFollow(CLittleHelper *const this)
{
  Position param; // [rsp+10h] [rbp-20h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-10h] BYREF

  if ( this->m_pPlayer && this->m_pMap )
  {
    param = Unit::getTargetTile(this);
    CurrentTile = StaticObj::getCurrentTile(this);
    if ( Position::operator==(&CurrentTile, &param) )
      CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_STAND);
  }
}


#####################################
void __cdecl CLittleHelper::onWalkPick(CLittleHelper *const this)
{
  Position param; // [rsp+10h] [rbp-20h] BYREF
  Position CurrentTile; // [rsp+20h] [rbp-10h] BYREF
  CDropItem *pItem; // [rsp+28h] [rbp-8h]

  if ( this->m_pPlayer && this->m_pMap )
  {
    if ( this->m_TarDropId )
    {
      pItem = Map::getDropItem(this->m_pMap, this->m_TarDropId);
      if ( !pItem || CDropItem::picked(pItem) )
      {
        CLittleHelper::ChangeTarget(this);
      }
      else
      {
        param = Unit::getTargetTile(this);
        CurrentTile = StaticObj::getCurrentTile(this);
        if ( Position::operator==(&CurrentTile, &param) )
        {
          CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_PICK);
          this->m_PickTick = Unit::getTick(this->m_pPlayer);
        }
      }
    }
    else
    {
      CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_STAND);
    }
  }
}


#####################################
void __cdecl CLittleHelper::onPick(CLittleHelper *const this)
{
  CDropItem *pItem; // [rsp+10h] [rbp-10h]

  if ( this->m_pPlayer && this->m_pMap && Unit::getTick(this->m_pPlayer) - this->m_PickTick > 400 )
  {
    pItem = Map::getDropItem(this->m_pMap, this->m_TarDropId);
    if ( pItem && !CDropItem::picked(pItem) && CDropItem::pick(pItem, this->m_pPlayer) == 10016 )
    {
      this->m_TarDropId = 0;
      CLittleHelper::setWorkState(this, LITTLE_HELPER_WORK_STATE::LHWS_STAND);
    }
    else
    {
      CLittleHelper::ChangeTarget(this);
    }
  }
}


