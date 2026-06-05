// Decompiled methods for class: Buff
// Source: gameserver.cc
// Total methods: 9

#####################################
void __cdecl Buff::~Buff(Buff *const this)
{
  Buff::~Buff(this);
  operator delete(this);
}


#####################################
int32_t __cdecl Buff::remainTick(Buff *const this)
{
  int m_endTick; // ebx

  m_endTick = this->m_endTick;
  return m_endTick - Unit::getTick(this->m_unit);
}


#####################################
void __cdecl Buff::trigTime(Buff *const this)
{
  if ( this->m_cfgBuff->interval > 0
    && Unit::getTick(this->m_unit) - this->m_lastIntervalTick >= this->m_cfgBuff->interval )
  {
    (*((void (__fastcall **)(Buff *const))this->_vptr_Buff + 5))(this);
    this->m_lastIntervalTick += this->m_cfgBuff->interval;
  }
}


#####################################
bool __cdecl Buff::shieldDamage(Buff *const this, int32_t *const nDamage)
{
  if ( *nDamage < this->m_nShield )
  {
    this->m_nShield -= *nDamage;
    *nDamage = 0;
    return 0;
  }
  else
  {
    *nDamage -= this->m_nShield;
    this->m_nShield = 0;
    return 1;
  }
}


#####################################
bool __cdecl Buff::effectTimes(Buff *const this)
{
  return ++this->m_nEffectTimes >= this->m_cfgBuff->effectTimes;
}


#####################################
bool __cdecl Buff::expire(Buff *const this)
{
  int m_nType; // eax

  if ( Unit::getTick(this->m_unit) > this->m_endTick )
    return 1;
  m_nType = this->m_nType;
  if ( m_nType == 2 )
    return !StaticObj::InDungeon(this->m_unit);
  if ( m_nType == 3 )
    return !StaticObj::InActivity(this->m_unit);
  return 0;
}


#####################################
void __cdecl Buff::effect(Buff *const this)
{
  BuffAttr *v1; // rbx
  BuffAttr *v2; // rbx
  BuffAttr *v3; // rax
  BuffAttr *v4; // rbx
  int32_t ratio; // r12d
  BuffAttr *v6; // rax
  BuffAttr *v7; // rbx
  int32_t addon; // r12d
  BuffAttr *v9; // rax
  int32_t nAttrSize; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]
  BuffAttr v12; // 0:rdx.12

  nAttrSize = std::vector<BuffAttr>::size(&this->m_cfgBuff->buffAttr);
  if ( nAttrSize > 0 )
  {
    *(_QWORD *)&v12.attr = 0;
    v12.addon = 0;
    std::vector<BuffAttr>::resize(&this->m_restore, nAttrSize, v12);
    for ( i = 0; i < nAttrSize; ++i )
    {
      v1 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
      v1->attr = std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i)->attr;
      if ( std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i)->attr == 12 )
      {
        v2 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
        v3 = std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i);
        v2->ratio = Unit::AddSpeedBuffRatio(this->m_unit, v3->ratio);
      }
      else
      {
        v4 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
        ratio = std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i)->ratio;
        v6 = std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i);
        v4->ratio = Unit::AddBuffAttrRatio(this->m_unit, (const CObjAttrs::Index_T)v6->attr, ratio);
      }
      v7 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
      addon = std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i)->addon;
      v9 = std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i);
      v7->addon = Unit::AddBuffAttrValue(this->m_unit, (const CObjAttrs::Index_T)v9->attr, addon);
    }
  }
  switch ( this->m_cfgBuff->special )
  {
    case 1:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_YUNXUAN);
      break;
    case 2:
    case 0xB:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_WUDI);
      break;
    case 3:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_BINGDONG);
      break;
    case 4:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_FREEDOM);
      break;
    case 5:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_CHENMO);
      break;
    case 6:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_SLEEP);
      break;
    case 7:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_SHIELD);
      break;
    case 8:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_PLYSIS);
      break;
    case 9:
      Unit::AddBuffState(this->m_unit, CObjState::Index_T::OBS_FROZEN);
      break;
  }
}


#####################################
void __cdecl Buff::interval(Buff *const this)
{
  int32_t v1; // edx
  int32_t attackState; // [rsp+3Ch] [rbp-34h] BYREF
  UnitHandle launcher; // [rsp+40h] [rbp-30h]
  int32_t hpchange; // [rsp+58h] [rbp-18h]
  int32_t nDamage; // [rsp+5Ch] [rbp-14h]
  UnitHandle v6; // 0:r8.12

  hpchange = 0;
  if ( this->m_cfgBuff->beneficial )
  {
    if ( this->m_cfgBuff->hpValue > 0 )
      hpchange += this->m_cfgBuff->hpValue;
    if ( this->m_cfgBuff->hpPecent > 0 )
      hpchange += this->m_cfgBuff->hpPecent
                * (*((__int64 (__fastcall **)(Unit *const))this->m_unit->_vptr_Entity + 20))(this->m_unit)
                / 100;
    (*((void (__fastcall **)(Unit *const, _QWORD))this->m_unit->_vptr_Entity + 21))(
      this->m_unit,
      (unsigned int)hpchange);
  }
  else
  {
    nDamage = 0;
    if ( this->m_cfgBuff->hpValue > 0 )
      nDamage += this->m_cfgBuff->hpValue;
    if ( this->m_cfgBuff->hpPecent > 0 )
      nDamage += this->m_cfgBuff->hpPecent
               * (*((__int64 (__fastcall **)(Unit *const))this->m_unit->_vptr_Entity + 20))(this->m_unit)
               / 100;
    hpchange -= nDamage;
    attackState = 0;
    launcher.id = (*((__int64 (__fastcall **)(Unit *const))this->m_unit->_vptr_Entity + 12))(this->m_unit);
    launcher.type = v1;
    v6.id = launcher.id;
    v6.type = v1;
    Unit::struckDamage(this->m_unit, nDamage, &attackState, this->m_cfgBuff->attack_type, v6, 0);
  }
}


#####################################
void __cdecl Buff::restore(Buff *const this)
{
  BuffAttr *v1; // rbx
  BuffAttr *v2; // rax
  int32_t v3; // ebx
  BuffAttr *v4; // rax
  int32_t v5; // ebx
  BuffAttr *v6; // rax
  int32_t nAttrSize; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  nAttrSize = std::vector<BuffAttr>::size(&this->m_restore);
  if ( nAttrSize > 0 )
  {
    for ( i = 0; i < nAttrSize; ++i )
    {
      if ( std::vector<BuffAttr>::operator[](&this->m_cfgBuff->buffAttr, i)->attr == 12 )
      {
        v1 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
        v2 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
        v1->ratio = Unit::RemoveSpeedBuffRatio(this->m_unit, v2->ratio);
      }
      else
      {
        v3 = -std::vector<BuffAttr>::operator[](&this->m_restore, i)->ratio;
        v4 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
        Unit::AddBuffAttrRatio(this->m_unit, (const CObjAttrs::Index_T)v4->attr, v3);
      }
      v5 = -std::vector<BuffAttr>::operator[](&this->m_restore, i)->addon;
      v6 = std::vector<BuffAttr>::operator[](&this->m_restore, i);
      Unit::AddBuffAttrValue(this->m_unit, (const CObjAttrs::Index_T)v6->attr, v5);
    }
  }
  switch ( this->m_cfgBuff->special )
  {
    case 1:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_YUNXUAN);
      break;
    case 2:
    case 0xB:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_WUDI);
      break;
    case 3:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_BINGDONG);
      break;
    case 4:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_FREEDOM);
      break;
    case 5:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_CHENMO);
      break;
    case 6:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_SLEEP);
      break;
    case 7:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_SHIELD);
      break;
    case 8:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_PLYSIS);
      break;
    case 9:
      Unit::RemoveBuffState(this->m_unit, CObjState::Index_T::OBS_FROZEN);
      break;
  }
}


