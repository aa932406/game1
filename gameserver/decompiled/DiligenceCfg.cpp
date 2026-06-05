// Decompiled methods for class: DiligenceCfg
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl DiligenceCfg::IsInItemList(DiligenceCfg *const this, int32_t ItemId, int8_t ItemCalss)
{
  std::_List_iterator<RateItem> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<RateItem> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<RateItem>::begin(&this->lItems)._M_node; ; std::_List_iterator<RateItem>::operator++(
                                                                            &it,
                                                                            0) )
  {
    __x._M_node = std::list<RateItem>::end(&this->lItems)._M_node;
    if ( !std::_List_iterator<RateItem>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<RateItem>::operator->(&it)->nItemClass == ItemCalss
      && std::_List_iterator<RateItem>::operator->(&it)->nItemId == ItemId )
    {
      return 1;
    }
  }
  return 0;
}


