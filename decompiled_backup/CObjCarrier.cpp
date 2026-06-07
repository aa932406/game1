// Decompiled methods for class: CObjCarrier
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl CObjCarrier::~CObjCarrier(CObjCarrier *const this)
{
  CObjCarrier::~CObjCarrier(this);
  operator delete(this);
}


#####################################
bool __cdecl CObjCarrier::refresh(CObjCarrier *const this)
{
  CExtCharCarrier *CharCarrier; // rax

  if ( !this->m_pPlayer )
    return 1;
  if ( !Unit::isAlive(this) )
  {
    CharCarrier = Player::GetCharCarrier(this->m_pPlayer);
    CExtCharCarrier::LeaveCarrier(CharCarrier);
    return 1;
  }
  else
  {
    if ( this->m_needSync )
    {
      Player::SetNeedSync(this->m_pPlayer);
      this->m_needSync = 0;
    }
    if ( this->m_needSyncSelf )
    {
      Player::SetNeedSyncSelf(this->m_pPlayer);
      this->m_needSyncSelf = 0;
    }
    if ( this->m_needSyncAttr )
    {
      Player::SetNeedSyncAttr(this->m_pPlayer);
      this->m_needSyncAttr = 0;
    }
    return 0;
  }
}


#####################################
int32_t __cdecl CObjCarrier::getLevel(const CObjCarrier *const this)
{
  if ( this->m_pPlayer )
    return (*((int32_t (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  else
    return 0;
}


#####################################
int32_t __cdecl CObjCarrier::getBattle(const CObjCarrier *const this)
{
  if ( this->m_pPlayer )
    return (*((int32_t (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 10))(this->m_pPlayer);
  else
    return 0;
}


#####################################
bool __cdecl CObjCarrier::isFriendSide(CObjCarrier *const this, Unit *pUnit)
{
  return this->m_pPlayer
      && (*((bool (__fastcall **)(Player *, Unit *))this->m_pPlayer->_vptr_Entity + 14))(this->m_pPlayer, pUnit);
}


#####################################
bool __cdecl CObjCarrier::checkSkillTarget(CObjCarrier *const this, const CfgActiveSkill *pCfg, Unit *pUnit)
{
  return this->m_pPlayer
      && (*((bool (__fastcall **)(Player *, const CfgActiveSkill *, Unit *))this->m_pPlayer->_vptr_Entity + 15))(
           this->m_pPlayer,
           pCfg,
           pUnit);
}


#####################################
void __cdecl CObjCarrier::reset(CObjCarrier *const this)
{
  Unit::reset(this);
  this->m_nId = 0;
  this->m_pPlayer = 0;
}


#####################################
void __cdecl CObjCarrier::Init(CObjCarrier *const this, Player *pOwner, int32_t nId)
{
  int32_t m_nId; // ebx
  CfgData *v4; // rax
  const CfgCarrierTable *CarrierTable; // rax
  int v6; // ebx
  CfgData *v7; // rax
  const CfgTalentTable *TalentTable; // rax
  std::_List_const_iterator<int> iter; // [rsp+20h] [rbp-40h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+30h] [rbp-30h] BYREF
  const CfgCarrier *pCfgCarrier; // [rsp+40h] [rbp-20h]
  const CfgTalent *pCfgTalent; // [rsp+48h] [rbp-18h]

  this->m_nId = nId;
  this->m_pPlayer = pOwner;
  m_nId = this->m_nId;
  v4 = Answer::Singleton<CfgData>::instance();
  CarrierTable = CfgData::GetCarrierTable(v4);
  pCfgCarrier = CfgCarrierTable::GetCarrier(CarrierTable, m_nId);
  if ( pCfgCarrier )
  {
    for ( iter._M_node = std::list<int>::begin(&pCfgCarrier->lSkills)._M_node;
          ;
          std::_List_const_iterator<int>::operator++(&iter) )
    {
      __x._M_node = std::list<int>::end(&pCfgCarrier->lSkills)._M_node;
      if ( !std::_List_const_iterator<int>::operator!=(&iter, &__x) )
        break;
      v6 = *std::_List_const_iterator<int>::operator*(&iter);
      v7 = Answer::Singleton<CfgData>::instance();
      TalentTable = CfgData::GetTalentTable(v7);
      pCfgTalent = CfgTalentTable::GetTalent(TalentTable, v6, 1);
      if ( pCfgTalent )
        std::list<int>::push_back(&this->m_lSkills, &pCfgTalent->skillid);
    }
    Unit::ResetAttrs(this);
    CObjCarrier::initBaseAttr(this);
    Unit::adjustUnitAttr(this);
    (*((void (__fastcall **)(CObjCarrier *const, __int64))this->_vptr_Entity + 22))(this, 100);
  }
}


#####################################
bool __cdecl CObjCarrier::appendInfo(CObjCarrier *const this, Answer::NetPacket *packet)
{
  return this->m_pPlayer && packet;
}


#####################################
bool __cdecl CObjCarrier::HaveSkill(const CObjCarrier *const this, int32_t nSkillId)
{
  const std::_List_node_base *M_node; // rbx
  std::_List_const_iterator<int> v3; // rax
  int32_t nSkillIda; // [rsp+4h] [rbp-3Ch] BYREF
  const CObjCarrier *thisa; // [rsp+8h] [rbp-38h]
  std::_List_const_iterator<int> __x; // [rsp+10h] [rbp-30h] BYREF
  std::_List_const_iterator<int> v8; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nSkillIda = nSkillId;
  __x._M_node = std::list<int>::end(&this->m_lSkills)._M_node;
  M_node = std::list<int>::end(&this->m_lSkills)._M_node;
  v3._M_node = std::list<int>::begin(&this->m_lSkills)._M_node;
  v8._M_node = std::find<std::_List_const_iterator<int>,int>(v3, (std::_List_const_iterator<int>)M_node, &nSkillIda)._M_node;
  return std::_List_const_iterator<int>::operator!=(&v8, &__x);
}


#####################################
void __cdecl CObjCarrier::initBaseAttr(CObjCarrier *const this)
{
  int32_t v1; // r12d
  int32_t m_nId; // ebx
  CfgData *v3; // rax
  const CfgCarrierTable *CarrierTable; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  const CfgCarrierAttr *pCfgAttr; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    v1 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    m_nId = this->m_nId;
    v3 = Answer::Singleton<CfgData>::instance();
    CarrierTable = CfgData::GetCarrierTable(v3);
    pCfgAttr = CfgCarrierTable::GetCarrierAttr(CarrierTable, m_nId, v1);
    if ( pCfgAttr )
    {
      for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgAttr->vAttr)._M_current;
            ;
            __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<AttrAddon>::end(&pCfgAttr->vAttr)._M_current;
        if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
          break;
        addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
        index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index;
        Unit::AddAttrValue(this, (const CObjAttrs::Index_T)index, addon);
      }
    }
  }
}


