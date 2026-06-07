// Decompiled methods for class: CfgTouZiTable
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl CfgTouZiTable::AddSevenTouZi(CfgTouZiTable *const this, SevenTouZi *p_stu)
{
  SevenTouZi *v2; // rax

  v2 = std::map<int,SevenTouZi>::operator[](&this->m_SevenTouZiMap, &p_stu->nId);
  SevenTouZi::operator=(v2, p_stu);
}


#####################################
void __cdecl CfgTouZiTable::AddMonthTouZi(CfgTouZiTable *const this, MonthTouZi *p_stu)
{
  MonthTouZi *v2; // rax

  v2 = std::map<int,MonthTouZi>::operator[](&this->m_MonthTouZiMap, &p_stu->nDay);
  MonthTouZi::operator=(v2, p_stu);
}


#####################################
bool __cdecl CfgTouZiTable::IsAllGetSevenDay(const CfgTouZiTable *const this, int32_t SevenDayRecord)
{
  std::_Rb_tree_const_iterator<std::pair<const int,SevenTouZi> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SevenTouZi> > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nNewRecord; // [rsp+2Ch] [rbp-14h]

  for ( it._M_node = std::map<int,SevenTouZi>::begin(&this->m_SevenTouZiMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,SevenTouZi>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,SevenTouZi>::end(&this->m_SevenTouZiMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,SevenTouZi>>::operator!=(&it, &__x) )
      break;
    nNewRecord = SevenDayRecord
               | (1 << (LOBYTE(std::_Rb_tree_const_iterator<std::pair<int const,SevenTouZi>>::operator->(&it)->second.nId)
                      - 1));
    if ( nNewRecord != SevenDayRecord )
      return 0;
  }
  return 1;
}


#####################################
bool __cdecl CfgTouZiTable::IsAllGetMonthTouZi(const CfgTouZiTable *const this, int32_t MonthTouZiRecord)
{
  std::_Rb_tree_const_iterator<std::pair<const int,MonthTouZi> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MonthTouZi> > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nNewRecord; // [rsp+2Ch] [rbp-14h]

  for ( it._M_node = std::map<int,MonthTouZi>::begin(&this->m_MonthTouZiMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,MonthTouZi>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,MonthTouZi>::end(&this->m_MonthTouZiMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,MonthTouZi>>::operator!=(&it, &__x) )
      break;
    nNewRecord = MonthTouZiRecord
               | (1 << (LOBYTE(std::_Rb_tree_const_iterator<std::pair<int const,MonthTouZi>>::operator->(&it)->second.nDay)
                      - 1));
    if ( nNewRecord != MonthTouZiRecord )
      return 0;
  }
  return 1;
}


