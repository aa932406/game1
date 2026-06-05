// Decompiled methods for class: CfgVplan
// Source: gameserver.cc
// Total methods: 7

#####################################
int32_t __cdecl CfgVplan::GetSwVipExpRatio(const CfgVplan *const this, int8_t nLevel)
{
  std::_List_const_iterator<Param2> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_const_iterator<Param2> __x; // [rsp+20h] [rbp-20h] BYREF

  for ( iter._M_node = std::list<Param2>::begin(&this->m_lSwVipExpRatio)._M_node;
        ;
        std::_List_const_iterator<Param2>::operator++(&iter) )
  {
    __x._M_node = std::list<Param2>::end(&this->m_lSwVipExpRatio)._M_node;
    if ( !std::_List_const_iterator<Param2>::operator!=(&iter, &__x) )
      break;
    if ( nLevel >= std::_List_const_iterator<Param2>::operator->(&iter)->nParam1 )
      return std::_List_const_iterator<Param2>::operator->(&iter)->nParam2;
  }
  return 0;
}


#####################################
void __cdecl CfgVplan::AddVplanReward(CfgVplan *const this, VplanReward *p_stu)
{
  VplanReward *v2; // rax

  v2 = std::map<int,VplanReward>::operator[](&this->m_VplanRewardMap, &p_stu->Index);
  VplanReward::operator=(v2, p_stu);
}


#####################################
void __cdecl CfgVplan::AddVplanLevelReward(CfgVplan *const this, VplanLevelReward *p_stu)
{
  VplanLevelReward *v2; // rax

  v2 = std::map<int,VplanLevelReward>::operator[](&this->m_VplanLevelRewardMap, &p_stu->Index);
  VplanLevelReward::operator=(v2, p_stu);
}


#####################################
void __cdecl CfgVplan::AddVplanEveryDayReward(CfgVplan *const this, VplanEveryDayReward *p_stu)
{
  VplanEveryDayReward *v2; // rax

  v2 = std::map<int,VplanEveryDayReward>::operator[](&this->m_VplanEveryDayRewardMap, &p_stu->Index);
  VplanEveryDayReward::operator=(v2, p_stu);
}


#####################################
void __cdecl CfgVplan::AddSwVipReward(CfgVplan *const this, const CfgSwVipReward *const stu)
{
  CfgSwVipReward *v2; // rax

  v2 = std::map<int,CfgSwVipReward>::operator[](&this->m_mSwVipReward, &stu->nIndex);
  CfgSwVipReward::operator=(v2, stu);
}


#####################################
void __cdecl CfgVplan::AddSwVipBarReward(CfgVplan *const this, const CfgSwVipReward *const stu)
{
  CfgSwVipReward *v2; // rax

  v2 = std::map<int,CfgSwVipReward>::operator[](&this->m_mSwVipBarReward, &stu->nIndex);
  CfgSwVipReward::operator=(v2, stu);
}


#####################################
void __cdecl CfgVplan::AddSwVipExpRatio(CfgVplan *const this, int8_t nType, const Param2 *const stu)
{
  if ( nType == 1 )
  {
    std::list<Param2>::push_front(&this->m_lSwVipExpRatio, stu);
  }
  else if ( nType == 2 )
  {
    this->m_nSwBarExpRatio = stu->nParam2;
  }
}


