// Decompiled methods for class: CfgFamilyTask
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgFamilyTask::AddFamilyTask(
        CfgFamilyTask *const this,
        int32_t nTaskId,
        int32_t nMinLevel,
        int32_t nMaxLevel)
{
  FamilyTask task; // [rsp+20h] [rbp-10h] BYREF

  task.TaskId = nTaskId;
  task.MinLevel = nMinLevel;
  task.MaxLevel = nMaxLevel;
  std::list<FamilyTask>::push_back(&this->m_FamilyTaskList, &task);
}


#####################################
int32_t __cdecl CfgFamilyTask::GetFamilyTask(const CfgFamilyTask *const this, int32_t Level)
{
  size_t v2; // rax
  const FamilyTask *v4; // rax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v6; // rax
  std::_List_const_iterator<FamilyTask> it; // [rsp+10h] [rbp-50h] BYREF
  Int32Vector vTask; // [rsp+20h] [rbp-40h] BYREF
  std::_List_const_iterator<FamilyTask> __x; // [rsp+40h] [rbp-20h] BYREF

  std::vector<int>::vector(&vTask);
  v2 = std::list<FamilyTask>::size(&this->m_FamilyTaskList);
  std::vector<int>::reserve(&vTask, v2);
  for ( it._M_node = std::list<FamilyTask>::begin(&this->m_FamilyTaskList)._M_node;
        ;
        std::_List_const_iterator<FamilyTask>::operator++(&it) )
  {
    __x._M_node = std::list<FamilyTask>::end(&this->m_FamilyTaskList)._M_node;
    if ( !std::_List_const_iterator<FamilyTask>::operator!=(&it, &__x) )
      break;
    if ( std::_List_const_iterator<FamilyTask>::operator->(&it)->MinLevel <= Level
      && std::_List_const_iterator<FamilyTask>::operator->(&it)->MaxLevel >= Level )
    {
      v4 = std::_List_const_iterator<FamilyTask>::operator->(&it);
      std::vector<int>::push_back(&vTask, &v4->TaskId);
    }
  }
  M_current = std::vector<int>::end(&vTask)._M_current;
  v6._M_current = std::vector<int>::begin(&vTask)._M_current;
  std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
    v6,
    (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
  LODWORD(M_current) = *std::vector<int>::front(&vTask);
  std::vector<int>::~vector(&vTask);
  return (int)M_current;
}


