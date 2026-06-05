// Decompiled methods for class: Unit
// Source: gameserver.cc
// Total methods: 77

#####################################
void __cdecl Unit::~Unit(Unit *const this)
{
  Unit::~Unit(this);
  operator delete(this);
}


#####################################
void __cdecl Unit::reset(Unit *const this)
{
  Answer::Random *v1; // rax
  Position v2; // [rsp+10h] [rbp-20h] BYREF
  Position v3; // [rsp+20h] [rbp-10h] BYREF
  int32_t nRand; // [rsp+28h] [rbp-8h]
  int32_t i; // [rsp+2Ch] [rbp-4h]

  StaticObj::reset(this);
  CObjAttrs::CleanUp(&this->m_baseAttr);
  CObjAttrs::CleanUp(&this->m_buffAttrValue);
  CObjAttrs::CleanUp(&this->m_buffAttrRatio);
  CObjState::CleanUp(&this->m_buffStates);
  std::list<int>::clear(&this->m_lSpeedBuffRatio);
  bzero(&this->m_unitAttr, 0xCu);
  this->m_bDie = 0;
  this->m_needSync = 0;
  Position::Position(&v2, 0, 0);
  this->m_targetTile = v2;
  Position::Position(&v3, 0, 0);
  this->m_targetPos = v3;
  this->m_yOffset = 0.0;
  this->m_xOffset = this->m_yOffset;
  this->m_direction = Direction::DOWN;
  this->m_posUpdateTick = Unit::getTick(this);
  v1 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v1, 1, 1000);
  this->m_posUpdateTick -= nRand;
  this->m_lastHPTick = Unit::getTick(this);
  this->m_throwedTick = -1;
  for ( i = 0; i <= 39; ++i )
  {
    if ( this->m_buffs[i] )
      (*((void (__fastcall **)(Buff *))this->m_buffs[i]->_vptr_Buff + 1))(this->m_buffs[i]);
  }
  bzero(this->m_buffs, 0x140u);
  this->m_nSkillFlag = 0;
  this->m_nSkillChantTime = 0;
  std::list<UnitAddonSkill>::clear(&this->m_lAddonSkill);
}


#####################################
void __cdecl Unit::update(Unit *const this)
{
  (*((void (__fastcall **)(Unit *const))this->_vptr_Entity + 7))(this);
  Unit::checkHPRef(this);
  if ( !(*((unsigned __int8 (__fastcall **)(Unit *const))this->_vptr_Entity + 8))(this) )
  {
    Unit::checkBuffList(this);
    Unit::checkAddonSkills(this);
    Unit::syncBasicData(this);
  }
}


#####################################
void __cdecl Unit::checkHPRef(Unit *const this)
{
  unsigned int AttrValue; // edx
  int64_t curTick; // [rsp+10h] [rbp-10h]
  int nRefValue; // [rsp+1Ch] [rbp-4h]

  if ( Unit::isAlive(this) )
  {
    curTick = Unit::getTick(this);
    if ( curTick - this->m_lastHPTick > 10000 )
    {
      this->m_lastHPTick = curTick;
      nRefValue = Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_HP_REF);
      if ( nRefValue > 0 )
        (*((void (__fastcall **)(Unit *const, _QWORD))this->_vptr_Entity + 21))(this, (unsigned int)nRefValue);
      AttrValue = Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_KUN_LI_REF);
      (*((void (__fastcall **)(Unit *const, _QWORD))this->_vptr_Entity + 23))(this, AttrValue);
    }
  }
}


#####################################
void __cdecl Unit::leaveTile(Unit *const this)
{
  Position v1; // [rsp+10h] [rbp-20h] BYREF
  Position v2; // [rsp+20h] [rbp-10h] BYREF

  Position::Position(&v1, 0, 0);
  this->m_pMap = 0;
  Position::Position(&v2, 0, 0);
  this->m_currentTile = v2;
  this->m_targetTile = this->m_currentTile;
}


#####################################
void __cdecl Unit::setAtTile(Unit *const this, Map *pMap, int32_t tx, int32_t ty)
{
  Position oldPos; // [rsp+20h] [rbp-30h] BYREF
  Position v8; // [rsp+30h] [rbp-20h] BYREF
  Map *pOldMap; // [rsp+38h] [rbp-18h]

  pOldMap = this->m_pMap;
  oldPos = this->m_currentPos;
  this->m_pMap = pMap;
  Position::Position(&v8, tx, ty);
  this->m_targetTile = v8;
  this->m_currentTile = this->m_targetTile;
  this->m_targetPos = Map::tileToPixel(tx, ty);
  this->m_currentPos = this->m_targetPos;
  this->m_posUpdateTick = Unit::getTick(this);
  if ( this->m_pMap == pOldMap && this->m_pMap && Entity::getType(this) != EntityType::ET_TRAILER )
    Map::checkAreaChange(this->m_pMap, this, &oldPos);
}


#####################################
void __cdecl Unit::setTargetTile(Unit *const this, int32_t tx, int32_t ty)
{
  if ( this->m_pMap && Map::isWalkablePosition(this->m_pMap, tx, ty) && Unit::resetDirection(this, tx, ty) )
  {
    this->m_targetTile.x = tx;
    this->m_targetTile.y = ty;
    this->m_targetPos = Map::tileToPixel(tx, ty);
    if ( Unit::getTick(this) - this->m_posUpdateTick > 100 )
      this->m_posUpdateTick = Unit::getTick(this);
  }
}


#####################################
bool __cdecl Unit::resetDirection(Unit *const this, int32_t tx, int32_t ty)
{
  Position targetPos; // [rsp+10h] [rbp-40h]
  Position param; // [rsp+20h] [rbp-30h] BYREF
  Position CurrentTile; // [rsp+30h] [rbp-20h] BYREF
  Direction direction; // [rsp+3Ch] [rbp-14h]

  direction = this->m_direction;
  Position::Position(&param, tx, ty);
  CurrentTile = StaticObj::getCurrentTile(this);
  if ( Position::operator!=(&CurrentTile, &param) )
  {
    direction = Map::tileDirection(this->m_currentTile.x, this->m_currentTile.y, tx, ty);
    if ( direction == Direction::INVALID_DIRECTION )
    {
      targetPos = Map::tileToPixel(tx, ty);
      direction = Map::pixelDirection(this->m_currentPos.x, this->m_currentPos.y, targetPos.x, targetPos.y);
      if ( direction == Direction::INVALID_DIRECTION )
        return 0;
    }
  }
  this->m_direction = direction;
  return 1;
}


#####################################
void __cdecl Unit::instantMove(Unit *const this, int32_t tx, int32_t ty, InstanceMoveReason reason, int8_t dir)
{
  Player *v6; // rax
  int32_t MapId; // ebx
  CharId_t Cid; // rax
  Position oldPos; // [rsp+20h] [rbp-30h] BYREF
  Position v13; // [rsp+30h] [rbp-20h] BYREF
  Player *player; // [rsp+38h] [rbp-18h]

  if ( this->m_pMap
    && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 17))(this->m_pMap) != 1
    && (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 24))(this->m_pMap) != 1
    && Entity::getType(this) == EntityType::ET_PLAYER )
  {
    if ( this )
      v6 = (Player *)__dynamic_cast(
                       this,
                       (const struct __class_type_info *)&`typeinfo for'Unit,
                       (const struct __class_type_info *)&`typeinfo for'Player,
                       0);
    else
      v6 = 0;
    player = v6;
    MapId = Map::GetMapId(this->m_pMap);
    Cid = Player::getCid(player);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_INFO,
      "NoRandMap InstantMove cid=%lld,mapId=%d,Reasonid = %d\n",
      Cid,
      MapId,
      reason);
  }
  Unit::broadcastInstantMove(this, tx, ty, reason, dir);
  oldPos = this->m_currentPos;
  Position::Position(&v13, tx, ty);
  this->m_targetTile = v13;
  this->m_currentTile = this->m_targetTile;
  this->m_targetPos = Map::tileToPixel(tx, ty);
  this->m_currentPos = this->m_targetPos;
  this->m_posUpdateTick = Unit::getTick(this);
  if ( this->m_pMap )
    Map::checkAreaChange(this->m_pMap, this, &oldPos);
}


#####################################
void __cdecl Unit::setStand(Unit *const this)
{
  if ( Position::operator!=(&this->m_targetPos, &this->m_currentPos) )
  {
    this->m_targetTile = this->m_currentTile;
    this->m_targetPos = this->m_currentPos;
    this->m_posUpdateTick = Unit::getTick(this);
    if ( Entity::getType(this) != EntityType::ET_MONSTER )
      Unit::broadcastMove(this);
  }
}


#####################################
bool __cdecl Unit::isInRectangle(const Unit *const this, Position pst1, Position pst2)
{
  return this->m_currentTile.x >= pst1.x
      && this->m_currentTile.x <= pst2.x
      && this->m_currentTile.y >= pst1.y
      && this->m_currentTile.y <= pst2.y;
}


#####################################
bool __cdecl Unit::updatePosition(Unit *const this)
{
  Position oldPos; // [rsp+10h] [rbp-60h] BYREF
  int64_t ticks; // [rsp+18h] [rbp-58h]
  double distance; // [rsp+20h] [rbp-50h]
  int32_t TitDis; // [rsp+2Ch] [rbp-44h]
  double Rate; // [rsp+30h] [rbp-40h]
  double moved; // [rsp+38h] [rbp-38h]
  double ratio; // [rsp+40h] [rbp-30h]
  double xMoved; // [rsp+48h] [rbp-28h]
  double yMoved; // [rsp+50h] [rbp-20h]
  int32_t ixMoved; // [rsp+58h] [rbp-18h]
  int32_t iyMoved; // [rsp+5Ch] [rbp-14h]

  if ( !Unit::isMoving(this) )
    return 0;
  if ( Unit::HasBuffState(this, CObjState::Index_T::OBS_BINGDONG)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_YUNXUAN)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_SLEEP)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN) )
  {
    return 0;
  }
  ticks = Unit::getTick(this) - this->m_posUpdateTick;
  if ( ticks <= 100 )
    return 0;
  distance = sqrt((double)((this->m_targetPos.x - this->m_currentPos.x) * (this->m_targetPos.x - this->m_currentPos.x)
                         + (this->m_targetPos.y - this->m_currentPos.y) * (this->m_targetPos.y - this->m_currentPos.y)));
  TitDis = Position::tileDistance(&this->m_currentTile, &this->m_targetTile);
  Rate = 1.0;
  if ( Entity::getType(this) == EntityType::ET_PLAYER )
  {
    if ( TitDis <= 1 )
      Rate = 0.4000000059604645;
  }
  else if ( Entity::getType(this) == EntityType::ET_PET )
  {
    Rate = 1.100000023841858;
  }
  moved = (double)(int)ticks * (0.001 * Unit::getDirectionSpeed(this)) * Rate;
  oldPos = this->m_currentPos;
  if ( moved <= distance )
  {
    if ( moved > 0.0 )
    {
      ratio = moved / distance;
      xMoved = (double)(this->m_targetPos.x - this->m_currentPos.x) * (moved / distance)
             + (double)this->m_currentPos.x
             + this->m_xOffset;
      yMoved = (double)(this->m_targetPos.y - this->m_currentPos.y) * (moved / distance)
             + (double)this->m_currentPos.y
             + this->m_yOffset;
      ixMoved = (int)xMoved;
      iyMoved = (int)yMoved;
      this->m_xOffset = xMoved - (double)(int)xMoved;
      this->m_yOffset = yMoved - (double)iyMoved;
      this->m_currentPos.x = ixMoved;
      this->m_currentPos.y = iyMoved;
      this->m_currentTile = Map::pixelToTile(this->m_currentPos.x, this->m_currentPos.y);
    }
  }
  else
  {
    this->m_currentPos = this->m_targetPos;
    this->m_currentTile = this->m_targetTile;
  }
  this->m_posUpdateTick = Unit::getTick(this);
  if ( this->m_pMap && Entity::getType(this) != EntityType::ET_TRAILER )
    Map::checkAreaChange(this->m_pMap, this, &oldPos);
  if ( Position::operator==(&this->m_currentPos, &this->m_targetPos) )
    (*((void (__fastcall **)(Unit *const))this->_vptr_Entity + 16))(this);
  return 1;
}


#####################################
bool __cdecl Unit::isMoving(Unit *const this)
{
  return !Position::operator==(&this->m_currentPos, &this->m_targetPos);
}


#####################################
int64_t __cdecl Unit::getTick(const Unit *const this)
{
  CTimer *v2; // rax

  if ( this->m_pMap )
    return Map::getTick(this->m_pMap);
  v2 = Answer::Singleton<CTimer>::instance();
  return CTimer::GetTick(v2);
}


#####################################
int32_t __cdecl Unit::getNow(const Unit *const this)
{
  CTimer *v2; // rax

  if ( this->m_pMap )
    return Map::getNow(this->m_pMap);
  v2 = Answer::Singleton<CTimer>::instance();
  return CTimer::GetNow(v2);
}


#####################################
double __cdecl Unit::pixelDistance(Unit *const this, Unit *unit)
{
  if ( !unit || StaticObj::getMap(unit) != this->m_pMap )
    return (double)std::numeric_limits<int>::max();
  else
    return Position::distance(&this->m_currentPos, &unit->m_currentPos);
}


#####################################
int32_t __cdecl Unit::tileDistance(Unit *const this, Unit *unit)
{
  int32_t y; // ebx
  int32_t x; // ebx
  int __b; // [rsp+18h] [rbp-18h] BYREF
  int __a[5]; // [rsp+1Ch] [rbp-14h] BYREF

  if ( !unit || StaticObj::getMap(unit) != this->m_pMap )
    return std::numeric_limits<int>::max();
  y = StaticObj::getCurrentTile(this).y;
  __b = abs32(y - StaticObj::getCurrentTile(unit).y);
  x = StaticObj::getCurrentTile(this).x;
  __a[0] = abs32(x - StaticObj::getCurrentTile(unit).x);
  return *std::max<int>(__a, &__b);
}


#####################################
bool __cdecl Unit::isAlive(const Unit *const this)
{
  return (*((__int64 (__fastcall **)(const Unit *const))this->_vptr_Entity + 19))(this) > 0;
}


#####################################
int32_t __cdecl Unit::shieldDamage(Unit *const this, int32_t damage)
{
  bool v2; // al
  int32_t v3; // ebx
  int32_t damagea; // [rsp+4h] [rbp-4Ch] BYREF
  Unit *thisa; // [rsp+8h] [rbp-48h]
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  thisa = this;
  damagea = damage;
  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  for ( i = 0; i <= 39; ++i )
  {
    buff = thisa->m_buffs[i];
    v2 = buff && Buff::getSpecial(buff) == 7;
    if ( v2 && Buff::shieldDamage(buff, &damagea) )
    {
      if ( Buff::NeedShow(buff) )
        std::list<signed char>::push_back(&buffs, &i);
      (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
      if ( buff )
        (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
      thisa->m_buffs[i] = 0;
      bNeedSync = 1;
    }
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(thisa);
    Unit::broadcastBuffEnd(thisa, &buffs, 0);
  }
  v3 = damagea;
  std::list<signed char>::~list(&buffs);
  return v3;
}


#####################################
int32_t __cdecl Unit::GetBaseAttr(const Unit *const this, const CObjAttrs::Index_T nIdx)
{
  if ( CObjAttrs::GetAttr(&this->m_baseAttr, nIdx) <= 0 )
    return 0;
  else
    return CObjAttrs::GetAttr(&this->m_baseAttr, nIdx);
}


#####################################
int32_t __cdecl Unit::GetAttrValue(const Unit *const this, const CObjAttrs::Index_T nIdx)
{
  __int64 Attr; // rbx
  __int64 v3; // rbx
  int32_t result; // eax
  float v5; // [rsp+8h] [rbp-88h]
  float v6; // [rsp+Ch] [rbp-84h]
  float v7; // [rsp+10h] [rbp-80h]
  float v8; // [rsp+14h] [rbp-7Ch]
  float v9; // [rsp+18h] [rbp-78h]
  float v10; // [rsp+1Ch] [rbp-74h]
  float v11; // [rsp+20h] [rbp-70h]
  float v12; // [rsp+24h] [rbp-6Ch]
  float v13; // [rsp+28h] [rbp-68h]
  float v14; // [rsp+2Ch] [rbp-64h]
  float v15; // [rsp+30h] [rbp-60h]
  int64_t nValue; // [rsp+48h] [rbp-48h]

  Attr = CObjAttrs::GetAttr(&this->m_baseAttr, nIdx);
  v3 = (Unit::GetBuffAttrRatio(this, nIdx) + 10000) * Attr / 10000;
  nValue = v3 + Unit::GetBuffAttrValue(this, nIdx);
  switch ( nIdx )
  {
    case CObjAttrs::Index_T::ATTR_HP:
      v5 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_HP_ADD) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_HP) * v5);
      break;
    case CObjAttrs::Index_T::ATTR_MP:
      v6 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_MP_ADD) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_MP) * v6);
      break;
    case CObjAttrs::Index_T::ATTR_ATK_MIN:
      v7 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_ATK_ADD) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_ATK_MIN) * v7);
      break;
    case CObjAttrs::Index_T::ATTR_ATK_MAX:
      v8 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_ATK_ADD) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_ATK_MAX) * v8);
      break;
    case CObjAttrs::Index_T::ATTR_DEF_MIN:
      v9 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_DEF_ADD) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_DEF_MIN) * v9);
      break;
    case CObjAttrs::Index_T::ATTR_DEF_MAX:
      v10 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_DEF_ADD) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_DEF_MAX) * v10);
      break;
    case CObjAttrs::Index_T::ATTR_CRI_VAL:
      v11 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_CRI_VAL_PEC) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_CRI_VAL) * v11);
      break;
    case CObjAttrs::Index_T::ATTR_TOUGHNESS:
      v12 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_TOUGHNESS_PEC) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_TOUGHNESS) * v12);
      break;
    case CObjAttrs::Index_T::ATTR_XIN_MO_ATK:
      v13 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_XIN_MO_ATK_PEC) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_XIN_MO_ATK) * v13);
      break;
    case CObjAttrs::Index_T::ATTR_XIN_MO_DEF:
      v14 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_XIN_MO_DEF_PEC) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_XIN_MO_DEF) * v14);
      break;
    case CObjAttrs::Index_T::ATTR_QIE_GE:
      v15 = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_QIE_GE_PEC) / 1000.0;
      nValue += (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_QIE_GE) * v15);
      break;
    default:
      break;
  }
  result = 0;
  if ( nValue >= 0 )
    return nValue;
  return result;
}


#####################################
int32_t __cdecl Unit::AddAttrValue(Unit *const this, const CObjAttrs::Index_T nIdx, int32_t nAddVal)
{
  int32_t nRealValue; // [rsp+1Ch] [rbp-4h]

  if ( (unsigned int)nIdx > CObjAttrs::Index_T::ATTR_XUAN_YUN_DEF || !nAddVal )
    return 0;
  nRealValue = nAddVal + CObjAttrs::GetAttr(&this->m_baseAttr, nIdx);
  CObjAttrs::SetAttr(&this->m_baseAttr, nIdx, nRealValue);
  if ( nIdx != CObjAttrs::Index_T::ATTR_HP && nIdx != CObjAttrs::Index_T::ATTR_MOV_SPD )
    Unit::setNeedSync(this);
  Unit::setNeedSyncAttr(this);
  return nRealValue;
}


#####################################
void __cdecl Unit::SetAttrValue(Unit *const this, const CObjAttrs::Index_T nIdx, int32_t nVal)
{
  CObjAttrs::SetAttr(&this->m_baseAttr, nIdx, nVal);
  if ( nIdx != CObjAttrs::Index_T::ATTR_HP && nIdx != CObjAttrs::Index_T::ATTR_MOV_SPD )
    Unit::setNeedSync(this);
  Unit::setNeedSyncAttr(this);
}


#####################################
int32_t __cdecl Unit::GetBuffAttrRatio(const Unit *const this, const CObjAttrs::Index_T nIdx)
{
  int32_t nRatio; // [rsp+1Ch] [rbp-4h]

  nRatio = CObjAttrs::GetAttr(&this->m_buffAttrRatio, nIdx);
  if ( nIdx == CObjAttrs::Index_T::ATTR_MOV_SPD )
    nRatio += Unit::GetSpeedBuffRatio(this);
  return nRatio;
}


#####################################
int32_t __cdecl Unit::AddBuffAttrRatio(Unit *const this, const CObjAttrs::Index_T nIdx, int32_t nRate)
{
  int32_t Attr; // eax

  if ( !nRate )
    return 0;
  Attr = CObjAttrs::GetAttr(&this->m_buffAttrRatio, nIdx);
  CObjAttrs::SetAttr(&this->m_buffAttrRatio, nIdx, nRate + Attr);
  if ( nIdx != CObjAttrs::Index_T::ATTR_HP && nIdx != CObjAttrs::Index_T::ATTR_MOV_SPD )
    Unit::setNeedSync(this);
  Unit::setNeedSyncAttr(this);
  return nRate;
}


#####################################
int32_t __cdecl Unit::GetBuffAttrValue(const Unit *const this, const CObjAttrs::Index_T nIdx)
{
  return CObjAttrs::GetAttr(&this->m_buffAttrValue, nIdx);
}


#####################################
int32_t __cdecl Unit::AddBuffAttrValue(Unit *const this, const CObjAttrs::Index_T nIdx, int32_t nAddVal)
{
  int32_t Attr; // eax
  float AttrValue; // xmm0_4
  unsigned int HpAdd; // [rsp+2Ch] [rbp-4h]

  if ( !nAddVal )
    return 0;
  Attr = CObjAttrs::GetAttr(&this->m_buffAttrValue, nIdx);
  CObjAttrs::SetAttr(&this->m_buffAttrValue, nIdx, nAddVal + Attr);
  if ( nIdx != CObjAttrs::Index_T::ATTR_HP && nIdx != CObjAttrs::Index_T::ATTR_MOV_SPD )
    Unit::setNeedSync(this);
  if ( nIdx == CObjAttrs::Index_T::ATTR_HP_ADD )
  {
    AttrValue = (float)Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_HP_ADD);
    HpAdd = (int)(float)((float)Unit::GetBaseAttr(this, CObjAttrs::Index_T::ATTR_HP) * (float)(AttrValue / 1000.0));
    (*((void (__fastcall **)(Unit *const, _QWORD))this->_vptr_Entity + 21))(this, HpAdd);
  }
  Unit::setNeedSyncAttr(this);
  return nAddVal;
}


#####################################
int32_t __cdecl Unit::AddSpeedBuffRatio(Unit *const this, int32_t nRatio)
{
  int32_t nRatioa; // [rsp+14h] [rbp-1Ch] BYREF
  Unit *thisa; // [rsp+18h] [rbp-18h]

  thisa = this;
  nRatioa = nRatio;
  std::list<int>::push_back(&this->m_lSpeedBuffRatio, &nRatioa);
  std::list<int>::sort<std::greater<int>>(&thisa->m_lSpeedBuffRatio, (std::greater<int>)&nRatioa);
  Unit::setNeedSync(thisa);
  Unit::setNeedSyncAttr(thisa);
  return nRatioa;
}


#####################################
int32_t __cdecl Unit::RemoveSpeedBuffRatio(Unit *const this, int32_t nRatio)
{
  std::_List_iterator<int> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<int>::begin(&this->m_lSpeedBuffRatio)._M_node;
        ;
        std::_List_iterator<int>::operator++(&iter) )
  {
    __x._M_node = std::list<int>::end(&this->m_lSpeedBuffRatio)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
      break;
    if ( *std::_List_iterator<int>::operator*(&iter) == nRatio )
    {
      std::list<int>::erase(&this->m_lSpeedBuffRatio, iter);
      Unit::setNeedSync(this);
      Unit::setNeedSyncAttr(this);
      return nRatio;
    }
  }
  return nRatio;
}


#####################################
int32_t __cdecl Unit::GetSpeedBuffRatio(const Unit *const this)
{
  int v2; // eax
  int v3; // eax
  int32_t nAddRatio; // [rsp+18h] [rbp-8h]

  if ( std::list<int>::empty(&this->m_lSpeedBuffRatio) )
    return 0;
  if ( *std::list<int>::front(&this->m_lSpeedBuffRatio) <= 0 )
    v2 = 0;
  else
    v2 = *std::list<int>::front(&this->m_lSpeedBuffRatio);
  nAddRatio = v2;
  if ( *std::list<int>::back(&this->m_lSpeedBuffRatio) >= 0 )
    v3 = 0;
  else
    v3 = *std::list<int>::back(&this->m_lSpeedBuffRatio);
  return nAddRatio + v3;
}


#####################################
bool __cdecl Unit::HasBuffState(const Unit *const this, const CObjState::Index_T nIdx)
{
  return CObjState::GetState(&this->m_buffStates, nIdx);
}


#####################################
void __cdecl Unit::AddBuffState(Unit *const this, const CObjState::Index_T nIdx)
{
  bool v2; // al
  int32_t y; // r12d
  int32_t x; // edx

  v2 = (unsigned int)nIdx < CObjState::Index_T::OBS_WUDI
    || nIdx == CObjState::Index_T::OBS_SLEEP
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_PLYSIS)
    || Unit::HasBuffState(this, CObjState::Index_T::OBS_FROZEN);
  if ( v2 && Unit::isMoving(this) )
  {
    y = StaticObj::getCurrentTile(this).y;
    x = StaticObj::getCurrentTile(this).x;
    Unit::setAtTile(this, this->m_pMap, x, y);
    Unit::broadcastMove(this);
  }
  if ( (nIdx == CObjState::Index_T::OBS_YUNXUAN || nIdx == CObjState::Index_T::OBS_CHENMO)
    && this->m_nSkillChantTime > 0 )
  {
    this->m_nSkillChantTime = 0;
    Unit::broadcastBreakSkillChant(this);
    (*((void (__fastcall **)(Unit *const))this->_vptr_Entity + 32))(this);
  }
  if ( nIdx == CObjState::Index_T::OBS_WUDI )
    Unit::clearDebuff(this, 0);
  if ( nIdx == CObjState::Index_T::OBS_FREEDOM )
    Unit::clearContrlBuff(this);
  CObjState::AddState(&this->m_buffStates, nIdx);
}


#####################################
void __cdecl Unit::RemoveBuffState(Unit *const this, const CObjState::Index_T nIdx)
{
  CObjState::RemoveState(&this->m_buffStates, nIdx);
}


#####################################
int64_t __cdecl Unit::GetMaxHP(const Unit *const this)
{
  return Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_HP);
}


#####################################
int32_t __cdecl Unit::GetViewHP(const Unit *const this)
{
  return (*((int32_t (__fastcall **)(const Unit *const))this->_vptr_Entity + 19))(this);
}


#####################################
int32_t __cdecl Unit::GetViewMaxHP(const Unit *const this)
{
  return (*((int32_t (__fastcall **)(const Unit *const))this->_vptr_Entity + 20))(this);
}


#####################################
void __cdecl Unit::AddHP(Unit *const this, int32_t nAddValue)
{
  __int64 hp; // rbx
  int32_t v3; // edx
  Player *v4; // rax
  CExtEquip *Equip; // rax
  CfgData *v6; // rax
  int32_t v7; // edx
  Buff *v8; // rbx
  CExtEquip *v9; // rax
  CfgData *v10; // rax
  int32_t v11; // edx
  Buff *v12; // rbx
  float v13; // [rsp+8h] [rbp-B8h]
  float v14; // [rsp+Ch] [rbp-B4h]
  int32_t nRealValue; // [rsp+3Ch] [rbp-84h] BYREF
  UnitHandle launcher; // [rsp+40h] [rbp-80h] BYREF
  UnitHandle v17; // [rsp+50h] [rbp-70h] BYREF
  int32_t OldHPPecent; // [rsp+68h] [rbp-58h]
  int32_t NewHpPecent; // [rsp+6Ch] [rbp-54h]
  Player *player; // [rsp+70h] [rbp-50h]
  int32_t TeJie2Param; // [rsp+78h] [rbp-48h]
  int32_t TeJie4Param; // [rsp+7Ch] [rbp-44h]
  CfgBuff *pCfgBuff; // [rsp+80h] [rbp-40h]
  Buff *pBuff; // [rsp+88h] [rbp-38h]
  CfgBuff *pCfgBuff_0; // [rsp+90h] [rbp-30h]
  Buff *pBuff_0; // [rsp+98h] [rbp-28h]

  if ( nAddValue < 0 )
  {
    if ( this->m_unitAttr.hp <= 0 )
      return;
  }
  else
  {
    hp = this->m_unitAttr.hp;
    if ( hp == (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this) )
      return;
  }
  v13 = (float)(*((int (__fastcall **)(Unit *const))this->_vptr_Entity + 19))(this);
  OldHPPecent = (int)(float)((float)(v13 / (float)(*((int (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this))
                           * 100.0);
  nRealValue = nAddValue + this->m_unitAttr.hp;
  v3 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this);
  Unit::adjustAttr(this, &nRealValue, v3, 0);
  Unit::setHP(this, nRealValue);
  v14 = (float)(*((int (__fastcall **)(Unit *const))this->_vptr_Entity + 19))(this);
  NewHpPecent = (int)(float)((float)(v14 / (float)(*((int (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this))
                           * 100.0);
  if ( this )
    v4 = (Player *)__dynamic_cast(
                     this,
                     (const struct __class_type_info *)&`typeinfo for'Unit,
                     (const struct __class_type_info *)&`typeinfo for'Player,
                     0);
  else
    v4 = 0;
  player = v4;
  if ( v4 && OldHPPecent > 29 && NewHpPecent <= 29 )
  {
    Equip = Player::GetEquip(player);
    TeJie2Param = CExtEquip::GetTeJieValue(Equip, 88);
    if ( TeJie2Param > 0 )
    {
      v6 = Answer::Singleton<CfgData>::instance();
      pCfgBuff = CfgData::getBuff(v6, TeJie2Param);
      if ( pCfgBuff )
      {
        launcher.id = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 12))(this);
        launcher.type = v7;
        v8 = (Buff *)operator new(0x60u);
        Buff::Buff(v8, this, pCfgBuff, &launcher, 4, 1);
        pBuff = v8;
        if ( v8 )
          Unit::addBuff(this, pBuff);
      }
    }
    v9 = Player::GetEquip(player);
    TeJie4Param = CExtEquip::GetTeJieValue(v9, 90);
    if ( TeJie4Param > 0 )
    {
      v10 = Answer::Singleton<CfgData>::instance();
      pCfgBuff_0 = CfgData::getBuff(v10, TeJie4Param);
      if ( pCfgBuff_0 )
      {
        v17.id = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 12))(this);
        v17.type = v11;
        v12 = (Buff *)operator new(0x60u);
        Buff::Buff(v12, this, pCfgBuff_0, &v17, 4, 1);
        pBuff_0 = v12;
        if ( v12 )
          Unit::addBuff(this, pBuff_0);
      }
    }
  }
  Unit::setNeedSync(this);
  Unit::setNeedSyncSelf(this);
}


#####################################
void __cdecl Unit::AddKunLi(Unit *const this, int32_t nAddValue)
{
  __int64 kun_li; // rbx
  int32_t v3; // edx
  int32_t nRealValue[5]; // [rsp+1Ch] [rbp-14h] BYREF

  if ( nAddValue < 0 )
  {
    if ( this->m_unitAttr.kun_li <= 0 )
      return;
    goto LABEL_5;
  }
  kun_li = this->m_unitAttr.kun_li;
  if ( kun_li != (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 25))(this) )
  {
LABEL_5:
    nRealValue[0] = nAddValue + this->m_unitAttr.kun_li;
    v3 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 25))(this);
    Unit::adjustAttr(this, nRealValue, v3, 0);
    Unit::setKunLi(this, nRealValue[0]);
    Unit::setNeedSync(this);
    Unit::setNeedSyncSelf(this);
  }
}


#####################################
int64_t __cdecl Unit::GetMaxKunLi(Unit *const this)
{
  return Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_KUN_LI);
}


#####################################
void __cdecl Unit::AddMP(Unit *const this, int32_t nAddValue)
{
  int32_t mp; // ebx
  int32_t MaxMP; // edx
  int32_t nRealValue[5]; // [rsp+1Ch] [rbp-14h] BYREF

  if ( nAddValue < 0 )
  {
    if ( this->m_unitAttr.mp <= 0 )
      return;
    goto LABEL_5;
  }
  mp = this->m_unitAttr.mp;
  if ( mp != Unit::GetMaxMP(this) )
  {
LABEL_5:
    nRealValue[0] = nAddValue + this->m_unitAttr.mp;
    MaxMP = Unit::GetMaxMP(this);
    Unit::adjustAttr(this, nRealValue, MaxMP, 0);
    Unit::setMP(this, nRealValue[0]);
    Unit::setNeedSyncSelf(this);
  }
}


#####################################
void __cdecl Unit::FillHP(Unit *const this, int32_t nPercent)
{
  __int64 hp; // rbx
  int32_t AttrValue; // eax

  hp = this->m_unitAttr.hp;
  if ( hp != (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this) )
  {
    AttrValue = Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_HP);
    (*((void (__fastcall **)(Unit *const, _QWORD))this->_vptr_Entity + 21))(
      this,
      (unsigned int)(AttrValue * nPercent / 100));
    this->m_bDie = 0;
    Unit::setNeedSync(this);
    Unit::setNeedSyncSelf(this);
  }
}


#####################################
void __cdecl Unit::FillMP(Unit *const this, int32_t nPercent)
{
  int32_t mp; // ebx
  int nRealValue; // [rsp+1Ch] [rbp-14h]

  mp = this->m_unitAttr.mp;
  if ( mp != Unit::GetMaxMP(this) )
  {
    nRealValue = nPercent * Unit::GetAttrValue(this, CObjAttrs::Index_T::ATTR_MP) / 100;
    Unit::AddMP(this, nRealValue);
    Unit::setNeedSyncSelf(this);
  }
}


#####################################
int32_t __cdecl Unit::GetSkillFlag(Unit *const this, bool bIncrease)
{
  if ( bIncrease && Entity::getType(this) != EntityType::ET_PLAYER )
    ++this->m_nSkillFlag;
  return this->m_nSkillFlag;
}


#####################################
void __cdecl Unit::resetUnitAttr(Unit *const this)
{
  bzero(&this->m_unitAttr, 0xCu);
}


#####################################
void __cdecl Unit::adjustUnitAttr(Unit *const this)
{
  int32_t v1; // edx
  int32_t MaxMP; // edx
  int32_t v3; // edx

  v1 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this);
  Unit::adjustAttr(this, &this->m_unitAttr.hp, v1, 0);
  MaxMP = Unit::GetMaxMP(this);
  Unit::adjustAttr(this, &this->m_unitAttr.mp, MaxMP, 0);
  v3 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 25))(this);
  Unit::adjustAttr(this, &this->m_unitAttr.kun_li, v3, 0);
}


#####################################
void __cdecl Unit::adjustAttr(Unit *const this, int32_t *const nAttr, int32_t nMaxValue, int32_t nMinValue)
{
  int32_t v4; // eax
  int32_t v5; // eax

  if ( *nAttr <= nMinValue )
    v4 = nMinValue;
  else
    v4 = *nAttr;
  *nAttr = v4;
  if ( *nAttr >= nMaxValue )
    v5 = nMaxValue;
  else
    v5 = *nAttr;
  *nAttr = v5;
}


#####################################
bool __cdecl Unit::HasBuffById(Unit *const this, int32_t buffId)
{
  int32_t i; // [rsp+14h] [rbp-Ch]
  Buff *buff; // [rsp+18h] [rbp-8h]

  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::getId(buff) == buffId )
      return 1;
  }
  return 0;
}


#####################################
int32_t __cdecl Unit::getBuffCount(Unit *const this)
{
  int32_t count; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  count = 0;
  for ( i = 0; i <= 39; ++i )
  {
    if ( this->m_buffs[i] && Buff::NeedShow(this->m_buffs[i]) )
      ++count;
  }
  return count;
}


#####################################
int32_t __cdecl Unit::addBuff(Unit *const this, Buff *buff)
{
  char v3; // al
  char v4; // al
  int32_t Type; // ebx
  int32_t GroupId; // ebx
  const UnitHandle *Launcher; // rbx
  const UnitHandle *v9; // rax
  int32_t Id; // ebx
  Buff *v13; // rax
  ItemBuff *v14; // rax
  int32_t Level; // ebx
  int32_t freeSlot; // [rsp+10h] [rbp-20h]
  char i; // [rsp+17h] [rbp-19h]

  if ( !buff )
    return 10002;
  if ( Buff::remainTick(buff) <= 0
    || (!Buff::isControl(buff) || !Unit::HasBuffState(this, CObjState::Index_T::OBS_FREEDOM) ? (v3 = 0) : (v3 = 1),
        v3
     || (Buff::beneficial(buff) || !Unit::HasBuffState(this, CObjState::Index_T::OBS_WUDI) ? (v4 = 0) : (v4 = 1), v4)) )
  {
LABEL_47:
    (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
    return 10002;
  }
  else
  {
    freeSlot = -1;
    for ( i = 0; i <= 39; ++i )
    {
      if ( this->m_buffs[i] )
      {
        Type = Buff::getType(this->m_buffs[i]);
        if ( Type == Buff::getType(buff) )
        {
          GroupId = Buff::getGroupId(this->m_buffs[i]);
          if ( GroupId == Buff::getGroupId(buff) )
          {
            if ( Buff::canRevocer(this->m_buffs[i])
              || (Launcher = Buff::getLauncher(buff),
                  v9 = Buff::getLauncher(this->m_buffs[i]),
                  UnitHandle::operator==(v9, Launcher)) )
            {
              if ( !Buff::getType(this->m_buffs[i]) && (Id = Buff::getId(this->m_buffs[i]), Id == Buff::getId(buff)) )
              {
                v13 = this->m_buffs[i];
                if ( v13 )
                  v14 = (ItemBuff *)__dynamic_cast(
                                      v13,
                                      (const struct __class_type_info *)&`typeinfo for'Buff,
                                      (const struct __class_type_info *)&`typeinfo for'ItemBuff,
                                      0);
                else
                  v14 = 0;
                if ( v14 )
                  ItemBuff::extend(v14, buff);
                (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
                Unit::broadcastAddBuff(this, i, this->m_buffs[i]);
                return 0;
              }
              else
              {
                Level = Buff::getLevel(this->m_buffs[i]);
                if ( Level > Buff::getLevel(buff) )
                  goto LABEL_47;
                (*((void (__fastcall **)(Buff *))this->m_buffs[i]->_vptr_Buff + 4))(this->m_buffs[i]);
                if ( this->m_buffs[i] )
                  (*((void (__fastcall **)(Buff *))this->m_buffs[i]->_vptr_Buff + 1))(this->m_buffs[i]);
                this->m_buffs[i] = buff;
                (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 3))(buff);
                Unit::adjustUnitAttr(this);
                Unit::broadcastAddBuff(this, i, buff);
                return 0;
              }
            }
          }
        }
      }
      else
      {
        freeSlot = i;
      }
    }
    if ( freeSlot < 0 )
      goto LABEL_47;
    this->m_buffs[freeSlot] = buff;
    (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 3))(buff);
    Unit::adjustUnitAttr(this);
    Unit::broadcastAddBuff(this, freeSlot, buff);
    return 0;
  }
}


#####################################
void __cdecl Unit::removeBuff(Unit *const this, int32_t buffId)
{
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::getId(buff) == buffId )
    {
      if ( Buff::NeedShow(buff) )
        std::list<signed char>::push_back(&buffs, &i);
      (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
      if ( buff )
        (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
      this->m_buffs[i] = 0;
      bNeedSync = 1;
    }
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 0);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
void __cdecl Unit::removeBuffBySpecail(Unit *const this, int32_t special)
{
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::getSpecial(buff) == special )
    {
      if ( Buff::NeedShow(buff) )
        std::list<signed char>::push_back(&buffs, &i);
      (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
      if ( buff )
        (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
      this->m_buffs[i] = 0;
      bNeedSync = 1;
    }
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 0);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
void __cdecl Unit::checkBuffEffect(Unit *const this, BUFF_EFFECT_TYPE type)
{
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::effectType(buff) == type && Buff::effectTimes(buff) )
    {
      if ( Buff::NeedShow(buff) )
        std::list<signed char>::push_back(&buffs, &i);
      (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
      if ( buff )
        (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
      this->m_buffs[i] = 0;
      bNeedSync = 1;
    }
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 0);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
void __cdecl Unit::clearDebuff(Unit *const this, int32_t nCount)
{
  char *M_current; // rbx
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > v4; // rax
  char *v5; // rsi
  char v6; // al
  int8_t i_0; // [rsp+1Eh] [rbp-72h] BYREF
  int8_t i; // [rsp+1Fh] [rbp-71h] BYREF
  Int8Vector vIndex; // [rsp+20h] [rbp-70h] BYREF
  Int8List buffs; // [rsp+40h] [rbp-50h] BYREF
  bool bNeedSync; // [rsp+5Fh] [rbp-31h]
  Buff *buff; // [rsp+60h] [rbp-30h]
  int8_t j; // [rsp+6Fh] [rbp-21h]
  Buff *buff_0; // [rsp+70h] [rbp-20h]
  Buff *buff_1; // [rsp+78h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  if ( nCount <= 0 )
  {
    for ( i_0 = 0; i_0 <= 39; ++i_0 )
    {
      buff_1 = this->m_buffs[i_0];
      if ( buff_1 && Buff::canRemove(buff_1) && !Buff::beneficial(buff_1) )
      {
        if ( Buff::NeedShow(buff_1) )
          std::list<signed char>::push_back(&buffs, &i_0);
        (*((void (__fastcall **)(Buff *))buff_1->_vptr_Buff + 4))(buff_1);
        if ( buff_1 )
          (*((void (__fastcall **)(Buff *))buff_1->_vptr_Buff + 1))(buff_1);
        this->m_buffs[i_0] = 0;
        bNeedSync = 1;
      }
    }
  }
  else
  {
    std::vector<signed char>::vector(&vIndex);
    std::vector<signed char>::reserve(&vIndex, 0x28u);
    for ( i = 0; i <= 39; ++i )
    {
      buff = this->m_buffs[i];
      if ( buff && Buff::canRemove(buff) && !Buff::beneficial(buff) )
        std::vector<signed char>::push_back(&vIndex, &i);
    }
    if ( !std::vector<signed char>::empty(&vIndex) )
    {
      M_current = std::vector<signed char>::end(&vIndex)._M_current;
      v4._M_current = std::vector<signed char>::begin(&vIndex)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>>(
        v4,
        (__gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> >)M_current);
      for ( j = 0; ; ++j )
      {
        v6 = std::vector<signed char>::size(&vIndex);
        if ( v6 <= j || j >= nCount )
          break;
        buff_0 = this->m_buffs[*std::vector<signed char>::operator[](&vIndex, j)];
        if ( buff_0 )
        {
          if ( Buff::NeedShow(buff_0) )
          {
            v5 = std::vector<signed char>::operator[](&vIndex, j);
            std::list<signed char>::push_back(&buffs, v5);
          }
          (*((void (__fastcall **)(Buff *))buff_0->_vptr_Buff + 4))(buff_0);
          if ( buff_0 )
            (*((void (__fastcall **)(Buff *))buff_0->_vptr_Buff + 1))(buff_0);
          this->m_buffs[*std::vector<signed char>::operator[](&vIndex, j)] = 0;
          bNeedSync = 1;
        }
      }
    }
    std::vector<signed char>::~vector(&vIndex);
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 2);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
void __cdecl Unit::clearBuff(Unit *const this, int32_t nCount)
{
  char *M_current; // rbx
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > v4; // rax
  char *v5; // rsi
  char v6; // al
  int8_t i_0; // [rsp+1Eh] [rbp-72h] BYREF
  int8_t i; // [rsp+1Fh] [rbp-71h] BYREF
  Int8Vector vIndex; // [rsp+20h] [rbp-70h] BYREF
  Int8List buffs; // [rsp+40h] [rbp-50h] BYREF
  bool bNeedSync; // [rsp+5Fh] [rbp-31h]
  Buff *buff; // [rsp+60h] [rbp-30h]
  int8_t j; // [rsp+6Fh] [rbp-21h]
  Buff *buff_0; // [rsp+70h] [rbp-20h]
  Buff *buff_1; // [rsp+78h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  if ( nCount <= 0 )
  {
    for ( i_0 = 0; i_0 <= 39; ++i_0 )
    {
      buff_1 = this->m_buffs[i_0];
      if ( buff_1 && Buff::canRemove(buff_1) && Buff::beneficial(buff_1) )
      {
        if ( Buff::NeedShow(buff_1) )
          std::list<signed char>::push_back(&buffs, &i_0);
        (*((void (__fastcall **)(Buff *))buff_1->_vptr_Buff + 4))(buff_1);
        if ( buff_1 )
          (*((void (__fastcall **)(Buff *))buff_1->_vptr_Buff + 1))(buff_1);
        this->m_buffs[i_0] = 0;
        bNeedSync = 1;
      }
    }
  }
  else
  {
    std::vector<signed char>::vector(&vIndex);
    std::vector<signed char>::reserve(&vIndex, 0x28u);
    for ( i = 0; i <= 39; ++i )
    {
      buff = this->m_buffs[i];
      if ( buff && Buff::canRemove(buff) && Buff::beneficial(buff) )
        std::vector<signed char>::push_back(&vIndex, &i);
    }
    if ( !std::vector<signed char>::empty(&vIndex) )
    {
      M_current = std::vector<signed char>::end(&vIndex)._M_current;
      v4._M_current = std::vector<signed char>::begin(&vIndex)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>>(
        v4,
        (__gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> >)M_current);
      for ( j = 0; ; ++j )
      {
        v6 = std::vector<signed char>::size(&vIndex);
        if ( v6 <= j || j >= nCount )
          break;
        buff_0 = this->m_buffs[*std::vector<signed char>::operator[](&vIndex, j)];
        if ( buff_0 )
        {
          if ( Buff::NeedShow(buff_0) )
          {
            v5 = std::vector<signed char>::operator[](&vIndex, j);
            std::list<signed char>::push_back(&buffs, v5);
          }
          (*((void (__fastcall **)(Buff *))buff_0->_vptr_Buff + 4))(buff_0);
          if ( buff_0 )
            (*((void (__fastcall **)(Buff *))buff_0->_vptr_Buff + 1))(buff_0);
          this->m_buffs[*std::vector<signed char>::operator[](&vIndex, j)] = 0;
          bNeedSync = 1;
        }
      }
    }
    std::vector<signed char>::~vector(&vIndex);
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 1);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
void __cdecl Unit::clearContrlBuff(Unit *const this)
{
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::isControl(buff) )
    {
      if ( Buff::NeedShow(buff) )
        std::list<signed char>::push_back(&buffs, &i);
      (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
      if ( buff )
        (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
      this->m_buffs[i] = 0;
      bNeedSync = 1;
    }
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 0);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
bool __cdecl Unit::checkBuffBySpecail(Unit *const this, int32_t special)
{
  int32_t i; // [rsp+14h] [rbp-Ch]
  Buff *buff; // [rsp+18h] [rbp-8h]

  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::getSpecial(buff) == special )
      return 1;
  }
  return 0;
}


#####################################
void __cdecl Unit::checkBuffList(Unit *const this)
{
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  if ( !Unit::isAlive(this) )
  {
    Unit::deathClearBuff(this);
  }
  else
  {
    std::list<signed char>::list(&buffs);
    bNeedSync = 0;
    for ( i = 0; i <= 39; ++i )
    {
      buff = this->m_buffs[i];
      if ( buff )
      {
        Buff::trigTime(buff);
        if ( (*((unsigned __int8 (__fastcall **)(Buff *))buff->_vptr_Buff + 2))(buff) )
        {
          if ( Buff::NeedShow(buff) )
            std::list<signed char>::push_back(&buffs, &i);
          (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
          this->m_buffs[i] = 0;
          if ( buff )
            (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
          bNeedSync = 1;
        }
      }
    }
    if ( bNeedSync )
    {
      Unit::adjustUnitAttr(this);
      Unit::broadcastBuffEnd(this, &buffs, 0);
    }
    if ( !Unit::isAlive(this) )
      Unit::deathClearBuff(this);
    std::list<signed char>::~list(&buffs);
  }
}


#####################################
void __cdecl Unit::syncBasicData(Unit *const this)
{
  if ( (*((unsigned __int8 (__fastcall **)(Unit *const))this->_vptr_Entity + 31))(this) )
  {
    (*((void (__fastcall **)(Unit *const))this->_vptr_Entity + 30))(this);
    this->m_needSync = 0;
  }
}


#####################################
void __cdecl Unit::broadcastMove(Unit *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  int16_t x; // [rsp+14h] [rbp-Ch]
  int16_t y; // [rsp+16h] [rbp-Ah]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    x = this->m_targetTile.x;
    y = this->m_targetTile.y;
    if ( Map::isWalkablePosition(this->m_pMap, x, y) )
    {
      v1 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2719u);
      if ( packet )
      {
        v2 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
        Answer::NetPacket::writeInt64(packet, v2);
        Type = Entity::getType(this);
        Answer::NetPacket::writeInt8(packet, Type);
        Answer::NetPacket::writeInt16(packet, x);
        Answer::NetPacket::writeInt16(packet, y);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Map::broadcastAreaAround(this->m_pMap, packet, this);
      }
    }
  }
}


#####################################
void __cdecl Unit::broadcastMoveMonster(Unit *const this, Position Pos)
{
  GameService *v2; // rax
  int64_t v3; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap && Map::isWalkablePosition(this->m_pMap, SLOWORD(Pos.x), SLOWORD(Pos.y)) )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2719u);
    if ( packet )
    {
      v3 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v3);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt16(packet, Pos.x);
      Answer::NetPacket::writeInt16(packet, Pos.y);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::broadcastInstantMove(
        Unit *const this,
        int16_t finalX,
        int16_t finalY,
        InstanceMoveReason reason,
        int8_t dir)
{
  GameService *v5; // rax
  int64_t v6; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pMap )
  {
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, Answer::PackType::PACK_DISPATCH, 0x271Cu);
    if ( packet )
    {
      v6 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v6);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt16(packet, finalX);
      Answer::NetPacket::writeInt16(packet, finalY);
      Answer::NetPacket::writeInt32(packet, reason);
      if ( reason == InstanceMoveReason::IMR_JUMP )
        Answer::NetPacket::writeInt8(packet, dir);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
int32_t __cdecl Unit::onKickOutMove(
        Unit *const this,
        int16_t currentX,
        int16_t currentY,
        int16_t targetX,
        int16_t targetY,
        int16_t finalX,
        int16_t finalY,
        Direction direction)
{
  Tile *pCurrentTile; // [rsp+28h] [rbp-28h]
  Tile *pTargetTile; // [rsp+30h] [rbp-20h]
  Tile *pFinalTile; // [rsp+38h] [rbp-18h]

  if ( !this->m_pMap )
    return 10002;
  pCurrentTile = Map::getTile(this->m_pMap, currentX, currentY);
  pTargetTile = Map::getTile(this->m_pMap, targetX, targetY);
  pFinalTile = Map::getTile(this->m_pMap, finalX, finalY);
  if ( !pCurrentTile || !pTargetTile || !pFinalTile )
    return 10002;
  Unit::setAtTile(this, this->m_pMap, targetX, targetY);
  Unit::broadcastKickOutedMove(this);
  return 0;
}


#####################################
void __cdecl Unit::broadcastKickOutedMove(Unit *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x271Au);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt16(packet, this->m_currentTile.x);
      Answer::NetPacket::writeInt16(packet, this->m_currentTile.y);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::onThrowed(Unit *const this)
{
  this->m_throwedTick = Unit::getTick(this) + 800;
  Unit::broadcastThrowed(this);
}


#####################################
void __cdecl Unit::broadcastThrowed(Unit *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x271Bu);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::broadcastLeave(Unit *const this)
{
  if ( this->m_pMap )
    Map::broadcastLeaveMap(this->m_pMap, this);
}


#####################################
void __cdecl Unit::broadcastBasicData(Unit *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  int8_t Type; // dl
  int64_t v4; // rdx
  int64_t v5; // rsi
  int32_t v6; // edx
  int32_t v7; // edx
  int32_t v8; // edx
  int32_t v9; // edx
  int16_t v10; // dx
  int32_t v11; // edx
  uint32_t WOffset; // edx
  bool nflag; // [rsp+17h] [rbp-9h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    nflag = this->m_bDie;
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2739u);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      if ( Entity::getType(this) == EntityType::ET_MONSTER )
      {
        v4 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 19))(this);
        Answer::NetPacket::writeInt64(packet, v4);
        v5 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 20))(this);
        Answer::NetPacket::writeInt64(packet, v5);
      }
      else
      {
        v6 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 26))(this);
        Answer::NetPacket::writeInt32(packet, v6);
        v7 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 27))(this);
        Answer::NetPacket::writeInt32(packet, v7);
      }
      if ( Entity::getType(this) == EntityType::ET_PLAYER )
      {
        v8 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 24))(this);
        Answer::NetPacket::writeInt32(packet, v8);
        v9 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 25))(this);
        Answer::NetPacket::writeInt32(packet, v9);
      }
      v10 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 28))(this);
      Answer::NetPacket::writeInt16(packet, v10);
      Answer::NetPacket::writeInt8(packet, nflag);
      v11 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 11))(this);
      Answer::NetPacket::writeInt32(packet, v11);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::broadcastSkillChant(Unit *const this, int32_t nSkillId, int32_t nChantTime)
{
  GameService *v3; // rax
  int64_t v4; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2736u);
    if ( packet )
    {
      v4 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v4);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt32(packet, nSkillId);
      Answer::NetPacket::writeInt32(packet, nChantTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::broadcastBreakSkillChant(Unit *const this)
{
  GameService *v1; // rax
  int64_t v2; // rdx
  int8_t Type; // dl
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( this->m_pMap )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x283Cu);
    if ( packet )
    {
      v2 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v2);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt8(packet, Type);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::packageBuffList(Unit *const this, Answer::NetPacket *packet)
{
  int32_t Id; // edx
  int32_t Level; // edx
  int32_t v5; // edx
  int32_t nCount; // [rsp+18h] [rbp-18h]
  uint32_t nOldOffset; // [rsp+1Ch] [rbp-14h]
  int32_t nNewOffset; // [rsp+20h] [rbp-10h]
  char i; // [rsp+27h] [rbp-9h]
  Buff *pBuff; // [rsp+28h] [rbp-8h]

  if ( packet )
  {
    nCount = 0;
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt32(packet, 0);
    for ( i = 0; i <= 39; ++i )
    {
      pBuff = this->m_buffs[i];
      if ( pBuff && Buff::NeedShow(pBuff) )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Id = Buff::getId(pBuff);
        Answer::NetPacket::writeInt32(packet, Id);
        Level = Buff::getLevel(pBuff);
        Answer::NetPacket::writeInt32(packet, Level);
        v5 = Buff::remainTick(pBuff);
        Answer::NetPacket::writeInt32(packet, v5);
        ++nCount;
      }
    }
    nNewOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt32(packet, nCount);
    Answer::NetPacket::setWOffset(packet, nNewOffset);
  }
}


#####################################
void __cdecl Unit::broadcastAddBuff(Unit *const this, int8_t nIndex, Buff *pBuff)
{
  GameService *v3; // rax
  int64_t v4; // rdx
  EntityType Type; // edx
  int32_t Id; // edx
  int32_t Level; // edx
  int32_t v8; // edx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  if ( this->m_pMap && pBuff && Buff::NeedShow(pBuff) )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x273Au);
    if ( packet )
    {
      v4 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v4);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt32(packet, Type);
      Answer::NetPacket::writeInt32(packet, 1);
      Answer::NetPacket::writeInt8(packet, nIndex);
      Id = Buff::getId(pBuff);
      Answer::NetPacket::writeInt32(packet, Id);
      Level = Buff::getLevel(pBuff);
      Answer::NetPacket::writeInt32(packet, Level);
      v8 = Buff::remainTick(pBuff);
      Answer::NetPacket::writeInt32(packet, v8);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcastAreaAround(this->m_pMap, packet, this);
    }
  }
}


#####################################
void __cdecl Unit::broadcastBuffEnd(Unit *const this, int8_t nIndex, int32_t nReason)
{
  int8_t nIndexa[4]; // [rsp+4h] [rbp-2Ch] BYREF
  Unit *thisa; // [rsp+8h] [rbp-28h]
  Int8List buffs; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  nIndexa[0] = nIndex;
  std::list<signed char>::list(&buffs);
  std::list<signed char>::push_back(&buffs, nIndexa);
  Unit::broadcastBuffEnd(thisa, &buffs, nReason);
  std::list<signed char>::~list(&buffs);
}


#####################################
void __cdecl Unit::broadcastBuffEnd(Unit *const this, const Int8List *const buffs, int32_t nReason)
{
  GameService *v4; // rax
  int64_t v5; // rax
  EntityType Type; // eax
  int32_t v7; // eax
  int8_t *v8; // rax
  uint32_t WOffset; // eax
  std::_List_const_iterator<signed char> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_const_iterator<signed char> __x; // [rsp+30h] [rbp-10h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  if ( this->m_pMap && !std::list<signed char>::empty(buffs) )
  {
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x273Bu);
    if ( packet )
    {
      v5 = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 2))(this);
      Answer::NetPacket::writeInt64(packet, v5);
      Type = Entity::getType(this);
      Answer::NetPacket::writeInt32(packet, Type);
      Answer::NetPacket::writeInt32(packet, nReason);
      v7 = std::list<signed char>::size(buffs);
      Answer::NetPacket::writeInt32(packet, v7);
      for ( iter._M_node = std::list<signed char>::begin(buffs)._M_node;
            ;
            std::_List_const_iterator<signed char>::operator++(&iter) )
      {
        __x._M_node = std::list<signed char>::end(buffs)._M_node;
        if ( !std::_List_const_iterator<signed char>::operator!=(&iter, &__x) )
          break;
        v8 = (int8_t *)std::_List_const_iterator<signed char>::operator*(&iter);
        Answer::NetPacket::writeInt8(packet, *v8);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcast(this->m_pMap, packet);
    }
  }
}


#####################################
void __cdecl Unit::deathClearBuff(Unit *const this)
{
  int8_t i; // [rsp+1Fh] [rbp-31h] BYREF
  Int8List buffs; // [rsp+20h] [rbp-30h] BYREF
  bool bNeedSync; // [rsp+37h] [rbp-19h]
  Buff *buff; // [rsp+38h] [rbp-18h]

  std::list<signed char>::list(&buffs);
  bNeedSync = 0;
  for ( i = 0; i <= 39; ++i )
  {
    buff = this->m_buffs[i];
    if ( buff && Buff::deathClear(buff) )
    {
      if ( Buff::NeedShow(buff) )
        std::list<signed char>::push_back(&buffs, &i);
      (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 4))(buff);
      if ( buff )
        (*((void (__fastcall **)(Buff *))buff->_vptr_Buff + 1))(buff);
      this->m_buffs[i] = 0;
      bNeedSync = 1;
    }
  }
  if ( bNeedSync )
  {
    Unit::adjustUnitAttr(this);
    Unit::broadcastBuffEnd(this, &buffs, 0);
  }
  std::list<signed char>::~list(&buffs);
}


#####################################
double __cdecl Unit::getDirectionSpeed(Unit *const this)
{
  Direction m_direction; // eax
  __int64 v2; // rax
  double baseSpeed; // [rsp+20h] [rbp-20h]
  double directionSpeed; // [rsp+28h] [rbp-18h]

  baseSpeed = (double)(*((int (__fastcall **)(Unit *const))this->_vptr_Entity + 28))(this);
  directionSpeed = baseSpeed;
  m_direction = this->m_direction;
  if ( (unsigned int)m_direction > Direction::DOWN_LEFT )
    goto LABEL_8;
  v2 = 1LL << m_direction;
  if ( (v2 & 0xAA) != 0 )
    return 59.0 * baseSpeed / 48.0;
  if ( (v2 & 0x44) != 0 )
    return baseSpeed;
  if ( (v2 & 0x11) == 0 )
  {
LABEL_8:
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "Unit::setTargetPosition with m_direction = %d\n",
      this->m_direction);
    return directionSpeed;
  }
  return 34.0 * baseSpeed / 48.0;
}


#####################################
void __cdecl Unit::clearAddonSkills(Unit *const this)
{
  if ( !std::list<UnitAddonSkill>::empty(&this->m_lAddonSkill) )
    std::list<UnitAddonSkill>::clear(&this->m_lAddonSkill);
}


#####################################
void __cdecl Unit::checkAddonSkills(Unit *const this)
{
  std::_List_iterator<UnitAddonSkill> v1; // rax
  UnitAddonSkill *v2; // rax
  UnitAddonSkill *v4; // rax
  UnitAddonSkill *v5; // rax
  int32_t RunnerId; // r12d
  EntityId_t unitId; // rbx
  GameService *v8; // rax
  int32_t hpChange; // r12d
  UnitAddonSkill *v10; // rax
  std::_List_iterator<UnitAddonSkill> v11; // rax
  int v12; // ebx
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > it; // [rsp+30h] [rbp-E0h] BYREF
  SkillResultVector results; // [rsp+40h] [rbp-D0h] BYREF
  UnitVector targets; // [rsp+60h] [rbp-B0h] BYREF
  Position pos; // [rsp+80h] [rbp-90h]
  Skill skill; // [rsp+90h] [rbp-80h] BYREF
  std::_List_iterator<UnitAddonSkill> iter; // [rsp+A0h] [rbp-70h] BYREF
  std::_List_iterator<UnitAddonSkill> __x; // [rsp+B0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<SkillResult*,std::vector<SkillResult> > __rhs; // [rsp+C0h] [rbp-50h] BYREF
  UnitHandle launcher; // [rsp+D0h] [rbp-40h]
  int64_t nCurTick; // [rsp+E0h] [rbp-30h]
  const CfgActiveSkill *pCfgSkill; // [rsp+E8h] [rbp-28h]
  int32_t attackValue; // [rsp+F4h] [rbp-1Ch]
  Player *victm; // [rsp+F8h] [rbp-18h]
  Position CurrentTile; // 0:rax.8
  UnitHandle v27; // 0:rsi.8,8:edx.4

  if ( !std::list<UnitAddonSkill>::empty(&this->m_lAddonSkill) && this->m_pMap )
  {
    nCurTick = Unit::getTick(this);
    iter._M_node = std::list<UnitAddonSkill>::begin(&this->m_lAddonSkill)._M_node;
    while ( 1 )
    {
      __x._M_node = std::list<UnitAddonSkill>::end(&this->m_lAddonSkill)._M_node;
      if ( !std::_List_iterator<UnitAddonSkill>::operator!=(&iter, &__x) )
        break;
      pCfgSkill = std::_List_iterator<UnitAddonSkill>::operator->(&iter)->pCfgSkill;
      if ( pCfgSkill )
      {
        if ( std::_List_iterator<UnitAddonSkill>::operator->(&iter)->nTrigTimes )
        {
          v2 = std::_List_iterator<UnitAddonSkill>::operator->(&iter);
          if ( nCurTick - v2->nLastTrigTime < pCfgSkill->addon_cd )
            goto LABEL_22;
        }
        v4 = std::_List_iterator<UnitAddonSkill>::operator->(&iter);
        ++v4->nTrigTimes;
        v5 = std::_List_iterator<UnitAddonSkill>::operator->(&iter);
        v5->nLastTrigTime = nCurTick;
        Skill::Skill(&skill, pCfgSkill, 0);
        attackValue = 0;
        pos = std::_List_iterator<UnitAddonSkill>::operator->(&iter)->sTargetPos;
        Map::getSkillTargets(&targets, this->m_pMap, this, pos, pCfgSkill);
        std::vector<SkillResult>::vector(&results);
        CurrentTile = StaticObj::getCurrentTile(this);
        Skill::posAction(&skill, this, CurrentTile, pos, &targets, &results, 0);
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
              RunnerId = StaticObj::GetRunnerId(this);
              unitId = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->unitId;
              v8 = Answer::Singleton<GameService>::instance();
              victm = GameService::getPlayer(v8, unitId, RunnerId, 1);
              if ( victm )
              {
                hpChange = __gnu_cxx::__normal_iterator<SkillResult *,std::vector<SkillResult>>::operator->(&it)->hpChange;
                launcher.id = (*((__int64 (__fastcall **)(Unit *const))this->_vptr_Entity + 12))(this);
                launcher.type = v27.type;
                v27.id = launcher.id;
                Player::onDamagedEvent(victm, v27, hpChange);
              }
            }
          }
        }
        v10 = std::_List_iterator<UnitAddonSkill>::operator->(&iter);
        if ( v10->nTrigTimes < pCfgSkill->addon_trig_times )
        {
          v12 = 1;
        }
        else
        {
          v11._M_node = std::_List_iterator<UnitAddonSkill>::operator++(&iter, 0)._M_node;
          std::list<UnitAddonSkill>::erase(&this->m_lAddonSkill, v11);
          v12 = 0;
        }
        std::vector<SkillResult>::~vector(&results);
        std::vector<Unit *>::~vector(&targets);
        Skill::~Skill(&skill);
        if ( v12 )
LABEL_22:
          std::_List_iterator<UnitAddonSkill>::operator++(&iter);
      }
      else
      {
        v1._M_node = std::_List_iterator<UnitAddonSkill>::operator++(&iter, 0)._M_node;
        std::list<UnitAddonSkill>::erase(&this->m_lAddonSkill, v1);
      }
    }
  }
}


