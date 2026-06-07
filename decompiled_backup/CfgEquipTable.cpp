// Decompiled methods for class: CfgEquipTable
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CfgEquipTable::AddEquip(CfgEquipTable *const this, const CfgEquip *const equip)
{
  CfgEquip *v2; // rax

  v2 = std::map<int,CfgEquip>::operator[](&this->m_mEquip, &equip->m_nId);
  CfgEquip::operator=(v2, equip);
}


#####################################
void __cdecl CfgEquipTable::AddEquipUpStar(CfgEquipTable *const this, const CfgEquipUpStar *const equip)
{
  CfgEquipUpStar *v2; // rax
  std::pair<signed char,int> __k; // [rsp+10h] [rbp-10h] BYREF

  __k = std::make_pair<signed char,int>(equip->m_nType, equip->m_nStar);
  v2 = std::map<std::pair<signed char,int>,CfgEquipUpStar>::operator[](&this->m_mEquipUpStar, &__k);
  CfgEquipUpStar::operator=(v2, equip);
}


#####################################
void __cdecl CfgEquipTable::AddEquipSuit(CfgEquipTable *const this, const CfgEquipSuit *const equip)
{
  CfgEquipSuit *v2; // rax

  v2 = std::map<int,CfgEquipSuit>::operator[](&this->m_mEquipSuit, &equip->m_nId);
  CfgEquipSuit::operator=(v2, equip);
}


#####################################
void __cdecl CfgEquipTable::AddEquipDecompose(CfgEquipTable *const this, const CfgEquipDecompose *const stu)
{
  std::list<CfgEquipDecompose>::push_back(&this->m_mEquipDecompose, stu);
}


#####################################
void __cdecl CfgEquipTable::AddEquipUpPos(CfgEquipTable *const this, const CfgEquipUpPos *const stu)
{
  CfgEquipUpPos *v2; // rax
  std::pair<signed char,int> __k; // [rsp+10h] [rbp-10h] BYREF

  __k = std::make_pair<signed char,int>(stu->m_nType, stu->m_nLevel);
  v2 = std::map<std::pair<signed char,int>,CfgEquipUpPos>::operator[](&this->m_mEquipUpPos, &__k);
  CfgEquipUpPos::operator=(v2, stu);
}


#####################################
void __cdecl CfgEquipTable::AddEquipPosSuit(CfgEquipTable *const this, const CfgEquipPosSuit *const stu)
{
  std::list<CfgEquipPosSuit>::push_front(&this->m_lEquipPosSuit, stu);
}


#####################################
void __cdecl CfgEquipTable::AddEquipBack(CfgEquipTable *const this, EquipBack *p_stu)
{
  EquipBack *v2; // rax

  v2 = std::map<int,EquipBack>::operator[](&this->m_mEquipBackMap, &p_stu->nId);
  EquipBack::operator=(v2, p_stu);
}


#####################################
void __cdecl CfgEquipTable::AddEequipStrengthenCfg(CfgEquipTable *const this, EquipStrengthenCfg *p_stu)
{
  _BYTE v2[80]; // [rsp+30h] [rbp-70h] BYREF
  std::pair<int,int> __a; // [rsp+80h] [rbp-20h] BYREF

  __a = std::make_pair<int,int>(p_stu->Pos, p_stu->Level);
  std::pair<std::pair const<int,int>,EquipStrengthenCfg>::pair(
    (std::pair<const std::pair<int,int>,EquipStrengthenCfg> *const)v2,
    &__a,
    p_stu);
  std::map<std::pair<int,int>,EquipStrengthenCfg>::insert(
    &this->m_EquipStrengthenCfgMap,
    (const std::pair<const std::pair<int,int>,EquipStrengthenCfg> *const)v2);
  std::pair<std::pair const<int,int>,EquipStrengthenCfg>::~pair((std::pair<const std::pair<int,int>,EquipStrengthenCfg> *const)v2);
}


#####################################
void __cdecl CfgEquipTable::AddShenYaoPosCfg(CfgEquipTable *const this, ShenYaoPos *p_stu)
{
  _BYTE v2[64]; // [rsp+30h] [rbp-60h] BYREF
  std::pair<int,int> __a; // [rsp+70h] [rbp-20h] BYREF

  __a = std::make_pair<int,int>(p_stu->nSlotId, p_stu->nLevel);
  std::pair<std::pair const<int,int>,ShenYaoPos>::pair(
    (std::pair<const std::pair<int,int>,ShenYaoPos> *const)v2,
    &__a,
    p_stu);
  std::map<std::pair<int,int>,ShenYaoPos>::insert(
    &this->m_ShenYaoPosCfgMap,
    (const std::pair<const std::pair<int,int>,ShenYaoPos> *const)v2);
  std::pair<std::pair const<int,int>,ShenYaoPos>::~pair((std::pair<const std::pair<int,int>,ShenYaoPos> *const)v2);
}


#####################################
void __cdecl CfgEquipTable::AddShenYaoPosSuit(CfgEquipTable *const this, ShenYaoPosSuit *p_stu)
{
  std::list<ShenYaoPosSuit>::push_front(&this->m_ShenYaoPosSuit, p_stu);
}


