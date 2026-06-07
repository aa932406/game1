// Decompiled methods for class: CfgEquipSuit
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgEquipSuit::CleanUp(CfgEquipSuit *const this)
{
  this->m_nId = 0;
  this->m_nCount = 0;
  std::vector<AttrAddon>::clear(&this->m_lstSuitAttr);
  std::list<int>::clear(&this->m_IdList);
  this->m_nBuffId = 0;
}


#####################################
bool __cdecl CfgEquipSuit::IsInIdList(const CfgEquipSuit *const this, int32_t nId)
{
  std::_List_const_iterator<int> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<int>::begin(&this->m_IdList)._M_node; ; std::_List_const_iterator<int>::operator++(
                                                                         &it,
                                                                         0) )
  {
    __x._M_node = std::list<int>::end(&this->m_IdList)._M_node;
    if ( !std::_List_const_iterator<int>::operator!=(&it, &__x) )
      break;
    if ( *std::_List_const_iterator<int>::operator*(&it) == nId )
      return 1;
  }
  return 0;
}


