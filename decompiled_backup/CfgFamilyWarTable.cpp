// Decompiled methods for class: CfgFamilyWarTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgFamilyWarTable::AddJoinReward(CfgFamilyWarTable *const this, int32_t nLevel, int32_t nExp)
{
  CfgFamilyWarJoinReward reward; // [rsp+10h] [rbp-10h] BYREF

  reward.level = nLevel;
  reward.addExp = nExp;
  std::list<CfgFamilyWarJoinReward>::push_back(&this->m_reward, &reward);
}


#####################################
int32_t __cdecl CfgFamilyWarTable::GetJoinReward(const CfgFamilyWarTable *const this, int32_t nLevel)
{
  std::_List_const_iterator<CfgFamilyWarJoinReward> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<CfgFamilyWarJoinReward> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<CfgFamilyWarJoinReward>::begin(&this->m_reward)._M_node;
  eiter._M_node = std::list<CfgFamilyWarJoinReward>::end(&this->m_reward)._M_node;
  while ( std::_List_const_iterator<CfgFamilyWarJoinReward>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_const_iterator<CfgFamilyWarJoinReward>::operator->(&iter)->level >= nLevel )
      return std::_List_const_iterator<CfgFamilyWarJoinReward>::operator->(&iter)->addExp;
    std::_List_const_iterator<CfgFamilyWarJoinReward>::operator++(&iter);
  }
  return 0;
}


