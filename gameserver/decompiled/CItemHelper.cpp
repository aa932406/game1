// Decompiled methods for class: CItemHelper
// Source: gameserver.cc
// Total methods: 3

#####################################
int32_t __cdecl CItemHelper::NeedUseBagCount(MemChrBagVector *p_Items)
{
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v3; // rax
  MemChrBag *v4; // rax
  MemChrBag *v5; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  int32_t Count; // [rsp+28h] [rbp-18h]
  int32_t nLayNum; // [rsp+2Ch] [rbp-14h]

  Count = 0;
  for ( it._M_current = std::vector<MemChrBag>::begin(p_Items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(p_Items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
      break;
    itemClass = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemClass;
    itemId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it)->itemId;
    v3 = Answer::Singleton<CfgData>::instance();
    nLayNum = CfgData::getOverlay(v3, itemId, itemClass);
    v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
    Count = v4->itemCount / nLayNum;
    v5 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
    if ( v5->itemCount % nLayNum )
      ++Count;
  }
  return Count;
}


#####################################
bool __cdecl CItemHelper::CanEnterXinMoBag(int32_t nId, int8_t nClass)
{
  CfgData *v2; // rax
  CfgData *v3; // rax
  const CfgEquipTable *EquipTable; // rax
  bool CanAdd; // [rsp+1Fh] [rbp-11h]
  CfgItem *pItem; // [rsp+20h] [rbp-10h]
  const CfgEquip *pEquip; // [rsp+28h] [rbp-8h]

  CanAdd = 0;
  if ( nClass == 1 )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    pItem = CfgData::getItem(v2, nId);
    if ( pItem )
      return pItem->XinMoBag > 0;
  }
  else if ( nClass == 2 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v3);
    pEquip = CfgEquipTable::GetEquip(EquipTable, nId);
    if ( pEquip )
      return pEquip->m_XinMoBag > 0;
  }
  return CanAdd;
}


#####################################
int32_t __cdecl CItemHelper::GetItemType(int32_t nId, int8_t nClass)
{
  CfgData *v2; // rax
  CfgData *v3; // rax
  const CfgEquipTable *EquipTable; // rax
  CfgData *v5; // rax
  const CfgItemGemTable *ItemGemTable; // rax
  CfgData *v7; // rax
  const CfgPetEquipTable *PetEquipTable; // rax
  int32_t nType; // [rsp+1Ch] [rbp-24h]
  CfgItem *pItem; // [rsp+20h] [rbp-20h]
  const CfgEquip *pEquip; // [rsp+28h] [rbp-18h]
  const CfgItemGem *pGem; // [rsp+30h] [rbp-10h]
  const CfgPetEquip *pPetEquip; // [rsp+38h] [rbp-8h]

  nType = -1;
  if ( nClass == 2 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v3);
    pEquip = CfgEquipTable::GetEquip(EquipTable, nId);
    if ( pEquip )
      return pEquip->m_nType;
  }
  else if ( nClass > 2 )
  {
    if ( nClass == 3 )
    {
      v5 = Answer::Singleton<CfgData>::instance();
      ItemGemTable = CfgData::GetItemGemTable(v5);
      pGem = CfgItemGemTable::GetItemGem(ItemGemTable, nId);
      if ( pGem )
        return pGem->m_nType;
    }
    else if ( nClass == 7 )
    {
      v7 = Answer::Singleton<CfgData>::instance();
      PetEquipTable = CfgData::GetPetEquipTable(v7);
      pPetEquip = CfgPetEquipTable::GetEquip(PetEquipTable, nId);
      if ( pPetEquip )
        return pPetEquip->nType;
    }
  }
  else if ( nClass == 1 )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    pItem = CfgData::getItem(v2, nId);
    if ( pItem )
      return pItem->type;
  }
  return nType;
}


