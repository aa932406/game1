// Decompiled methods for class: CfgWishRewardTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgWishRewardTable::Add(CfgWishRewardTable *const this, int32_t nItemId, const CfgWishReward *const stu)
{
  std::list<CfgWishReward> *v3; // rax
  int32_t nItemIda; // [rsp+14h] [rbp-Ch] BYREF
  CfgWishRewardTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nItemIda = nItemId;
  v3 = std::map<int,std::list<CfgWishReward>>::operator[](&this->m_mRewards, &nItemIda);
  std::list<CfgWishReward>::push_back(v3, stu);
}


#####################################
int32_t __cdecl CfgWishRewardTable::GetLeftTime(
        const CfgWishRewardTable *const this,
        int32_t nItemId,
        int32_t nStartTime)
{
  const std::pair<const int,std::list<CfgWishReward> > *v4; // rax
  const std::pair<const int,std::list<CfgWishReward> > *v5; // rax
  int v6; // ebx
  int32_t nItemIda; // [rsp+4h] [rbp-3Ch] BYREF
  const CfgWishRewardTable *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_const_iterator<std::pair<const int,std::list<CfgWishReward> > > findIter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,std::list<CfgWishReward> > > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nTime; // [rsp+2Ch] [rbp-14h]

  thisa = this;
  nItemIda = nItemId;
  findIter._M_node = std::map<int,std::list<CfgWishReward>>::find(&this->m_mRewards, &nItemIda)._M_node;
  __x._M_node = std::map<int,std::list<CfgWishReward>>::end(&thisa->m_mRewards)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,std::list<CfgWishReward>>>::operator==(&findIter, &__x) )
    return 0;
  v4 = std::_Rb_tree_const_iterator<std::pair<int const,std::list<CfgWishReward>>>::operator->(&findIter);
  if ( std::list<CfgWishReward>::empty(&v4->second) )
    return 0;
  v5 = std::_Rb_tree_const_iterator<std::pair<int const,std::list<CfgWishReward>>>::operator->(&findIter);
  v6 = nStartTime + std::list<CfgWishReward>::back(&v5->second)->nTime;
  nTime = v6 - Answer::DayTime::now();
  if ( nTime < 0 )
    return 0;
  return nTime;
}


