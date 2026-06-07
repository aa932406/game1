// Decompiled methods for class: CfgTaskCycleTable
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CfgTaskCycleTable::CleanUp(CfgTaskCycleTable *const this)
{
  std::list<CycleStarRate>::clear(&this->m_lstStar);
  std::list<TaskCycle>::clear(&this->m_lstTask);
  std::list<TaskCycleReward>::clear(&this->m_lstReward);
}


#####################################
bool __cdecl CfgTaskCycleTable::AddTask(
        CfgTaskCycleTable *const this,
        int32_t nTaskId,
        int32_t nMinLevel,
        int32_t nMaxLevel)
{
  TaskCycle task; // [rsp+20h] [rbp-10h] BYREF

  task.nTaskId = nTaskId;
  task.nMinLevel = nMinLevel;
  task.nMaxLevel = nMaxLevel;
  std::list<TaskCycle>::push_back(&this->m_lstTask, &task);
  return 1;
}


#####################################
bool __cdecl CfgTaskCycleTable::AddStarRate(CfgTaskCycleTable *const this, CycleStarRate *const StarRate)
{
  std::list<CycleStarRate>::push_back(&this->m_lstStar, StarRate);
  return 1;
}


#####################################
void __cdecl CfgTaskCycleTable::AddTaskReward(CfgTaskCycleTable *const this, const TaskCycleReward *const stu)
{
  std::list<TaskCycleReward>::push_back(&this->m_lstReward, stu);
}


#####################################
int32_t __cdecl CfgTaskCycleTable::RandTask(const CfgTaskCycleTable *const this, int32_t nLevel)
{
  size_t v2; // rax
  const TaskCycle *v4; // rax
  int32_t v5; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v7; // rax
  std::_List_const_iterator<TaskCycle> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_const_iterator<TaskCycle> iter; // [rsp+20h] [rbp-40h] BYREF
  Int32Vector vTask; // [rsp+30h] [rbp-30h] BYREF
  int32_t FirstTask; // [rsp+4Ch] [rbp-14h]

  std::vector<int>::vector(&vTask);
  v2 = std::list<TaskCycle>::size(&this->m_lstTask);
  std::vector<int>::reserve(&vTask, v2);
  FirstTask = 0;
  iter._M_node = std::list<TaskCycle>::begin(&this->m_lstTask)._M_node;
  eiter._M_node = std::list<TaskCycle>::end(&this->m_lstTask)._M_node;
  if ( std::_List_const_iterator<TaskCycle>::operator!=(&iter, &eiter) )
    FirstTask = std::_List_const_iterator<TaskCycle>::operator->(&iter)->nTaskId;
  while ( std::_List_const_iterator<TaskCycle>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_const_iterator<TaskCycle>::operator->(&iter)->nMinLevel <= nLevel
      && std::_List_const_iterator<TaskCycle>::operator->(&iter)->nMaxLevel >= nLevel )
    {
      v4 = std::_List_const_iterator<TaskCycle>::operator->(&iter);
      std::vector<int>::push_back(&vTask, &v4->nTaskId);
    }
    std::_List_const_iterator<TaskCycle>::operator++(&iter);
  }
  if ( std::vector<int>::empty(&vTask) )
  {
    v5 = FirstTask;
  }
  else
  {
    M_current = std::vector<int>::end(&vTask)._M_current;
    v7._M_current = std::vector<int>::begin(&vTask)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
      v7,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    v5 = *std::vector<int>::front(&vTask);
  }
  std::vector<int>::~vector(&vTask);
  return v5;
}


