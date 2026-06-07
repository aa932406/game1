// Decompiled methods for class: CfgDungeonScoreTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgDungeonScoreTable::AddDungeonScore(
        CfgDungeonScoreTable *const this,
        const CfgDungeonScore *const score)
{
  std::list<CfgDungeonScore> *v2; // rax
  std::list<CfgDungeonScore> *p_second; // rdx
  CfgDungeonScoreList scoreList; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgDungeonScore> > > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::list<CfgDungeonScore> > > __x; // [rsp+30h] [rbp-20h] BYREF

  iter._M_node = std::map<int,std::list<CfgDungeonScore>>::find(&this->m_mDungeonScore, &score->nDungeonId)._M_node;
  __x._M_node = std::map<int,std::list<CfgDungeonScore>>::end(&this->m_mDungeonScore)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::list<CfgDungeonScore>>>::operator==(&iter, &__x) )
  {
    std::list<CfgDungeonScore>::list(&scoreList);
    std::list<CfgDungeonScore>::push_front(&scoreList, score);
    v2 = std::map<int,std::list<CfgDungeonScore>>::operator[](&this->m_mDungeonScore, &score->nDungeonId);
    std::list<CfgDungeonScore>::operator=(v2, &scoreList);
    std::list<CfgDungeonScore>::~list(&scoreList);
  }
  else
  {
    p_second = &std::_Rb_tree_iterator<std::pair<int const,std::list<CfgDungeonScore>>>::operator->(&iter)->second;
    std::list<CfgDungeonScore>::push_front(p_second, score);
  }
  return 1;
}


