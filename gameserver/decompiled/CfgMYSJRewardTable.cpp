// Decompiled methods for class: CfgMYSJRewardTable
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl CfgMYSJRewardTable::Add(CfgMYSJRewardTable *const this, int32_t nId, const CfgMYSJReward *const reward)
{
  std::list<CfgMYSJReward> *v3; // rax
  std::list<CfgMYSJReward> *v4; // rax
  int32_t nIda; // [rsp+14h] [rbp-Ch] BYREF
  CfgMYSJRewardTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nIda = nId;
  v3 = std::map<int,std::list<CfgMYSJReward>>::operator[](&this->m_mReward, &nIda);
  std::list<CfgMYSJReward>::push_back(v3, reward);
  if ( reward->nGroup > 0 )
  {
    v4 = std::map<int,std::list<CfgMYSJReward>>::operator[](&thisa->m_mGroupReward, &reward->nGroup);
    std::list<CfgMYSJReward>::push_back(v4, reward);
    *std::map<int,int>::operator[](&thisa->m_mDungeonGroup, &nIda) = reward->nGroup;
  }
  return 1;
}


#####################################
int32_t __cdecl CfgMYSJRewardTable::GetGroupId(const CfgMYSJRewardTable *const this, int32_t nDungeonId)
{
  int32_t nDungeonIda; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgMYSJRewardTable *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,int> > findIter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nDungeonIda = nDungeonId;
  findIter._M_node = std::map<int,int>::find(&this->m_mDungeonGroup, &nDungeonIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_mDungeonGroup)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator==(&findIter, &__x) )
    return 0;
  else
    return std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&findIter)->second;
}


