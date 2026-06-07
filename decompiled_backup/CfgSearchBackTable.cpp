// Decompiled methods for class: CfgSearchBackTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgSearchBackTable::AddSearchBack(CfgSearchBackTable *const this, const CfgSearchBack *const stu)
{
  CfgSearchBack *v2; // rax

  v2 = std::map<int,CfgSearchBack>::operator[](&this->m_mSearchBack, &stu->nId);
  CfgSearchBack::operator=(v2, stu);
}


#####################################
void __cdecl CfgSearchBackTable::GetSearchBackList(
        const CfgSearchBackTable *const this,
        int32_t nLevel,
        CfgSearchBackList *const outList)
{
  CfgSearchBack *p_second; // rdx
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSearchBack> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSearchBack> > __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::map<int,CfgSearchBack>::begin(&this->m_mSearchBack)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSearchBack>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSearchBack>::end(&this->m_mSearchBack)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSearchBack>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgSearchBack>>::operator->(&iter)->second.nMinLevel <= nLevel
      && std::_Rb_tree_const_iterator<std::pair<int const,CfgSearchBack>>::operator->(&iter)->second.nMaxLevel >= nLevel )
    {
      p_second = &std::_Rb_tree_const_iterator<std::pair<int const,CfgSearchBack>>::operator->(&iter)->second;
      std::list<CfgSearchBack>::push_back(outList, p_second);
    }
  }
}


