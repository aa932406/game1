// Decompiled methods for class: CfgMaintainCompensateTable
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl CfgMaintainCompensateTable::Add(
        CfgMaintainCompensateTable *const this,
        const CfgMaintainCompensate *const stu)
{
  CfgMaintainCompensate *v2; // rax

  v2 = std::map<int,CfgMaintainCompensate>::operator[](&this->m_mMap, &stu->nIndex);
  CfgMaintainCompensate::operator=(v2, stu);
  return 1;
}


#####################################
int32_t __cdecl CfgMaintainCompensateTable::GetInitIndex(const CfgMaintainCompensateTable *const this, int32_t nTime)
{
  std::_Rb_tree_const_iterator<std::pair<const int,CfgMaintainCompensate> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgMaintainCompensate> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nIndex; // [rsp+2Ch] [rbp-4h]

  nIndex = 0;
  for ( iter._M_node = std::map<int,CfgMaintainCompensate>::begin(&this->m_mMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgMaintainCompensate>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgMaintainCompensate>::end(&this->m_mMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgMaintainCompensate>>::operator!=(&iter, &__x)
      || std::_Rb_tree_const_iterator<std::pair<int const,CfgMaintainCompensate>>::operator->(&iter)->second.nTime >= nTime )
    {
      break;
    }
    nIndex = std::_Rb_tree_const_iterator<std::pair<int const,CfgMaintainCompensate>>::operator->(&iter)->first;
  }
  return nIndex;
}


