// Decompiled methods for class: CfgLimitTimeTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgLimitTimeTable::AddLimitTime(CfgLimitTimeTable *const this, const CfgLimitTime *const cfg)
{
  *std::map<int,CfgLimitTime>::operator[](&this->m_mLimitTime, &cfg->nIndex) = *cfg;
}


#####################################
int32_t __cdecl CfgLimitTimeTable::GetLimitTime(const CfgLimitTimeTable *const this, int32_t nIndex)
{
  int nType; // eax
  int32_t v3; // ebx
  int32_t v5; // eax
  int v6; // ebx
  int32_t nIndexa; // [rsp+4h] [rbp-3Ch] BYREF
  const CfgLimitTimeTable *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_const_iterator<std::pair<const int,CfgLimitTime> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgLimitTime> > __x; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nIndexa = nIndex;
  iter._M_node = std::map<int,CfgLimitTime>::find(&this->m_mLimitTime, &nIndexa)._M_node;
  __x._M_node = std::map<int,CfgLimitTime>::end(&thisa->m_mLimitTime)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgLimitTime>>::operator!=(&iter, &__x) )
  {
    nType = std::_Rb_tree_const_iterator<std::pair<int const,CfgLimitTime>>::operator->(&iter)->second.nType;
    switch ( nType )
    {
      case 2:
        return std::_Rb_tree_const_iterator<std::pair<int const,CfgLimitTime>>::operator->(&iter)->second.nTime;
      case 3:
        v5 = Answer::DayTime::now();
        v6 = Answer::DayTime::dayzero(v5);
        return v6
             + 86400 * std::_Rb_tree_const_iterator<std::pair<int const,CfgLimitTime>>::operator->(&iter)->second.nTime;
      case 1:
        v3 = Answer::DayTime::now();
        return v3 + std::_Rb_tree_const_iterator<std::pair<int const,CfgLimitTime>>::operator->(&iter)->second.nTime;
    }
  }
  return 0;
}


