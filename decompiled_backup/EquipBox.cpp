// Decompiled methods for class: EquipBox
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl EquipBox::~EquipBox(EquipBox *const this)
{
  EquipBox::~EquipBox(this);
  operator delete(this);
}


#####################################
int32_t __cdecl EquipBox::effect(
        EquipBox *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v4; // ebx
  CExtCharBag *Bag; // rax
  int32_t m_nItemId; // ebx
  CfgData *v7; // rax
  const CfgEquipBoxTable *EquipBoxTable; // rax
  Answer::Random *v9; // rax
  const Param2 *v10; // rax
  const Param2 *v11; // rax
  CharId_t nCreaterId; // rbx
  int32_t Sid; // r13d
  int8_t ConnId; // r12
  CEquipManager *v15; // rax
  CExtCharBag *v16; // rax
  CEquipManager *v17; // rax
  MemEquip equip; // [rsp+60h] [rbp-C0h] BYREF
  MemChrBag addItem; // [rsp+A0h] [rbp-80h] BYREF
  std::_List_const_iterator<Param2> iter; // [rsp+C0h] [rbp-60h] BYREF
  std::_List_const_iterator<Param2> __x; // [rsp+D0h] [rbp-50h] BYREF
  std::string p_name; // [rsp+E0h] [rbp-40h] BYREF
  const CfgEquipBox *pCfgEquipBox; // [rsp+E8h] [rbp-38h]
  int32_t nEquipId; // [rsp+F4h] [rbp-2Ch]
  int32_t nStar; // [rsp+F8h] [rbp-28h]
  int32_t nRand; // [rsp+FCh] [rbp-24h]

  if ( *count <= 0 )
    return 10002;
  Bag = Player::GetBag(launcher);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 10002;
  m_nItemId = this->m_nItemId;
  v7 = Answer::Singleton<CfgData>::instance();
  EquipBoxTable = CfgData::GetEquipBoxTable(v7);
  pCfgEquipBox = CfgEquipBoxTable::RandEquip(EquipBoxTable, m_nItemId);
  if ( !pCfgEquipBox )
    return 10002;
  nEquipId = pCfgEquipBox->vEquipId[Player::getJob(launcher)];
  if ( nEquipId <= 0 )
    return 10002;
  nStar = 0;
  v9 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v9, 1, 10000);
  for ( iter._M_node = std::list<Param2>::begin(&pCfgEquipBox->lstStar)._M_node;
        ;
        std::_List_const_iterator<Param2>::operator++(&iter) )
  {
    __x._M_node = std::list<Param2>::end(&pCfgEquipBox->lstStar)._M_node;
    if ( !std::_List_const_iterator<Param2>::operator!=(&iter, &__x) )
      break;
    v10 = std::_List_const_iterator<Param2>::operator->(&iter);
    if ( v10->nParam2 >= nRand )
    {
      nStar = std::_List_const_iterator<Param2>::operator->(&iter)->nParam1;
      break;
    }
    v11 = std::_List_const_iterator<Param2>::operator->(&iter);
    nRand -= v11->nParam2;
  }
  Player::getName((const Player *const)&p_name);
  nCreaterId = Player::getCid(launcher);
  Sid = Player::getSid(launcher);
  ConnId = Player::getConnId(launcher);
  v15 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::CreateMemEquip(&equip, v15, ConnId, 221, nEquipId, Sid, nCreaterId, &p_name, 0, 0, nStar, 0, 0);
  std::string::~string(&p_name);
  if ( equip.id > 0 )
  {
    *(_DWORD *)&addItem.itemClass = 2;
    *(_QWORD *)&addItem.itemCount = 1;
    *(_QWORD *)&addItem.endTime = 0;
    addItem.srcId = 0;
    addItem.itemId = nEquipId;
    addItem.bind = pCfgEquipBox->nBind;
    addItem.srcId = equip.id;
    v16 = Player::GetBag(launcher);
    if ( !CExtCharBag::AddItem(v16, &addItem, ITEM_CHANGE_REASON::ICR_OPEN_EQUIP_BOX) )
    {
      v4 = 10002;
    }
    else
    {
      v17 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v17, launcher, &equip);
      v4 = 0;
    }
  }
  else
  {
    v4 = 10002;
  }
  MemEquip::~MemEquip(&equip);
  return v4;
}


#####################################
bool __cdecl EquipBox::parseEffect(EquipBox *const this, int32_t id, const std::string *const strEffect)
{
  int32_t m_nItemId; // ebx
  CfgData *v4; // rax
  const CfgEquipBoxTable *EquipBoxTable; // rax

  this->m_nItemId = id;
  m_nItemId = this->m_nItemId;
  v4 = Answer::Singleton<CfgData>::instance();
  EquipBoxTable = CfgData::GetEquipBoxTable(v4);
  return CfgEquipBoxTable::RandEquip(EquipBoxTable, m_nItemId) != 0;
}


