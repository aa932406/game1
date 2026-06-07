// Decompiled methods for class: CfgGoldEggTable
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl CfgGoldEggTable::AddGoldEgg(CfgGoldEggTable *const this, const CfgGoldEgg *const item)
{
  bool second; // bl
  std::pair<const int,CfgGoldEgg> __x; // [rsp+30h] [rbp-40h] BYREF

  std::pair<int const,CfgGoldEgg>::pair(&__x, &item->nId, item);
  second = std::map<int,CfgGoldEgg>::insert(&this->m_mEggs, &__x).second;
  std::pair<int const,CfgGoldEgg>::~pair(&__x);
  return second;
}


#####################################
bool __cdecl CfgGoldEggTable::AddGoldEggProduce(
        CfgGoldEggTable *const this,
        int32_t nId,
        const CfgGoldEggItem *const item)
{
  CfgGoldEggItemList *p_lstItem; // rdx
  int32_t nIda; // [rsp+14h] [rbp-2Ch] BYREF
  CfgGoldEggTable *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CfgGoldEgg> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgGoldEgg> > __x; // [rsp+30h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  iter._M_node = std::map<int,CfgGoldEgg>::find(&this->m_mEggs, &nIda)._M_node;
  __x._M_node = std::map<int,CfgGoldEgg>::end(&thisa->m_mEggs)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<int const,CfgGoldEgg>>::operator!=(&iter, &__x) )
    return 0;
  p_lstItem = &std::_Rb_tree_iterator<std::pair<int const,CfgGoldEgg>>::operator->(&iter)->second.lstItem;
  std::list<CfgGoldEggItem>::push_back(p_lstItem, item);
  return 1;
}


