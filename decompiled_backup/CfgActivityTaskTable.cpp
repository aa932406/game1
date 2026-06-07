// Decompiled methods for class: CfgActivityTaskTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgActivityTaskTable::AddTask(
        CfgActivityTaskTable *const this,
        int32_t nId,
        int32_t nMinLevel,
        int32_t nMaxLevel,
        int32_t nRatio)
{
  CfgActivityTask *v5; // rax
  int32_t nIda; // [rsp+14h] [rbp-1Ch] BYREF
  CfgActivityTaskTable *thisa; // [rsp+18h] [rbp-18h]
  CfgActivityTask stu; // [rsp+20h] [rbp-10h]

  thisa = this;
  nIda = nId;
  *(_QWORD *)&stu.nTaskId = __PAIR64__(nMinLevel, nId);
  *(_QWORD *)&stu.nMaxLevel = __PAIR64__(nRatio, nMaxLevel);
  v5 = std::map<int,CfgActivityTask>::operator[](&this->m_mTasks, &nIda);
  *v5 = stu;
}


#####################################
int32_t __cdecl CfgActivityTaskTable::RandomTask(const CfgActivityTaskTable *const this, int32_t nLevel)
{
  const std::pair<const int,CfgActivityTask> *v3; // rax
  const std::pair<const int,CfgActivityTask> *v4; // rax
  Answer::Random *v5; // rax
  const CfgActivityTask *v6; // rax
  int32_t nTaskId; // ebx
  const CfgActivityTask *v8; // rax
  std::_List_const_iterator<CfgActivityTask> iter2; // [rsp+10h] [rbp-80h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgActivityTask> > iter; // [rsp+20h] [rbp-70h] BYREF
  CfgActivityTaskList tList; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgActivityTask> > __x; // [rsp+40h] [rbp-50h] BYREF
  std::_List_iterator<CfgActivityTask> v14; // [rsp+50h] [rbp-40h] BYREF
  std::_List_const_iterator<CfgActivityTask> v15; // [rsp+60h] [rbp-30h] BYREF
  std::_List_iterator<CfgActivityTask> v16; // [rsp+70h] [rbp-20h] BYREF
  int32_t nAllRatio; // [rsp+78h] [rbp-18h]
  int32_t nRand; // [rsp+7Ch] [rbp-14h]

  std::list<CfgActivityTask>::list(&tList);
  nAllRatio = 0;
  for ( iter._M_node = std::map<int,CfgActivityTask>::begin(&this->m_mTasks)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityTask>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgActivityTask>::end(&this->m_mTasks)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityTask>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityTask>>::operator->(&iter)->second.nMinLevel <= nLevel
      && std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityTask>>::operator->(&iter)->second.nMaxLevel >= nLevel )
    {
      v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityTask>>::operator->(&iter);
      std::list<CfgActivityTask>::push_back(&tList, &v3->second);
      v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivityTask>>::operator->(&iter);
      nAllRatio += v4->second.nRatio;
    }
  }
  v5 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v5, 1, nAllRatio);
  v14._M_node = std::list<CfgActivityTask>::begin(&tList)._M_node;
  std::_List_const_iterator<CfgActivityTask>::_List_const_iterator(&iter2, &v14);
  while ( 1 )
  {
    v16._M_node = std::list<CfgActivityTask>::end(&tList)._M_node;
    std::_List_const_iterator<CfgActivityTask>::_List_const_iterator(&v15, &v16);
    if ( !std::_List_const_iterator<CfgActivityTask>::operator!=(&iter2, &v15) )
      break;
    v6 = std::_List_const_iterator<CfgActivityTask>::operator->(&iter2);
    if ( v6->nRatio >= nRand )
    {
      nTaskId = std::_List_const_iterator<CfgActivityTask>::operator->(&iter2)->nTaskId;
      goto LABEL_16;
    }
    v8 = std::_List_const_iterator<CfgActivityTask>::operator->(&iter2);
    nRand -= v8->nRatio;
    std::_List_const_iterator<CfgActivityTask>::operator++(&iter2);
  }
  nTaskId = 0;
LABEL_16:
  std::list<CfgActivityTask>::~list(&tList);
  return nTaskId;
}


