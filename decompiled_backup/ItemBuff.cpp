// Decompiled methods for class: ItemBuff
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl ItemBuff::~ItemBuff(ItemBuff *const this)
{
  ItemBuff::~ItemBuff(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ItemBuff::getGroupId(const ItemBuff *const this)
{
  if ( this->m_cfgItem )
    return this->m_cfgItem->group_id;
  else
    return 0;
}


#####################################
bool __cdecl ItemBuff::init(ItemBuff *const this, int32_t itemid, int32_t time)
{
  CfgData *v3; // rax
  int64_t v4; // rdx

  v3 = Answer::Singleton<CfgData>::instance();
  this->m_cfgItem = CfgData::getItem(v3, itemid);
  if ( time )
    v4 = Unit::getTick(this->m_unit) + 1000 * time;
  else
    v4 = Unit::getTick(this->m_unit) + this->m_cfgBuff->duration;
  this->m_endTick = v4;
  return this->m_cfgItem != 0;
}


#####################################
void __cdecl ItemBuff::extend(ItemBuff *const this, Buff *pBuff)
{
  int64_t m_endTick; // rbx

  if ( pBuff )
  {
    m_endTick = this->m_endTick;
    this->m_endTick = m_endTick + Buff::getCfgBuff(pBuff)->duration;
  }
}


#####################################
int32_t __cdecl ItemBuff::getEndTime(ItemBuff *const this)
{
  int64_t m_endTick; // rbx
  int Tick; // eax

  m_endTick = this->m_endTick;
  Tick = Unit::getTick(this->m_unit);
  return roundInt((double)((int)m_endTick - Tick) * 0.001);
}


#####################################
int32_t __cdecl ItemBuff::getItemId(ItemBuff *const this)
{
  if ( this->m_cfgItem )
    return this->m_cfgItem->id;
  else
    return 0;
}


