// Decompiled methods for class: SevenTaskTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl SevenTaskTable::AddSevenTaskSumRewardMap(SevenTaskTable *const this, SevenTaskSumReward stu)
{
  SevenTaskSumReward *v2; // rax

  v2 = std::map<int,SevenTaskSumReward>::operator[](&this->m_SevenTaskSumRewardMap, &stu.nId);
  *v2 = stu;
}


#####################################
void __cdecl SevenTaskTable::AddSevenTaskCfgMap(SevenTaskTable *const this, SevenTaskCfg stu)
{
  SevenTaskCfg *v2; // rax

  v2 = std::map<int,SevenTaskCfg>::operator[](&this->m_SevenTaskCfgMap, &stu.nId);
  *v2 = stu;
}


