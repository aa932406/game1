// Decompiled methods for class: CfgCampWarTable
// Source: gameserver.cc
// Total methods: 3

#####################################
int32_t __cdecl CfgCampWarTable::GetContKillLevel(const CfgCampWarTable *const this, int32_t nKillCount)
{
  std::_List_const_iterator<CfgCampWarContKill> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<CfgCampWarContKill> iter; // [rsp+20h] [rbp-10h] BYREF
  int32_t nContLevel; // [rsp+2Ch] [rbp-4h]

  nContLevel = 0;
  iter._M_node = std::list<CfgCampWarContKill>::begin(&this->m_contKills)._M_node;
  eiter._M_node = std::list<CfgCampWarContKill>::end(&this->m_contKills)._M_node;
  while ( std::_List_const_iterator<CfgCampWarContKill>::operator!=(&iter, &eiter)
       && std::_List_const_iterator<CfgCampWarContKill>::operator->(&iter)->nKillCount <= nKillCount )
  {
    nContLevel = std::_List_const_iterator<CfgCampWarContKill>::operator->(&iter)->nLevel;
    std::_List_const_iterator<CfgCampWarContKill>::operator++(&iter);
  }
  return nContLevel;
}


#####################################
void __cdecl CfgCampWarTable::AddReward(CfgCampWarTable *const this, const CfgCampWarReward *const reward)
{
  std::list<CfgCampWarReward>::push_back(&this->m_rewards, reward);
}


#####################################
void __cdecl CfgCampWarTable::AddContKill(CfgCampWarTable *const this, const CfgCampWarContKill *const contKill)
{
  std::list<CfgCampWarContKill>::push_back(&this->m_contKills, contKill);
}


