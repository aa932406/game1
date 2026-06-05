// Decompiled methods for class: ChouJiangTable
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl ChouJiangTable::AddChouJiangCfg(ChouJiangTable *const this, ChouJiangCfg stu)
{
  ChouJiangCfg *v2; // rax

  v2 = std::map<int,ChouJiangCfg>::operator[](&this->m_ChouJiangCfgMap, &stu.Index);
  *v2 = stu;
}


#####################################
void __cdecl ChouJiangTable::AddChouJiangLuckyCfg(ChouJiangTable *const this, ChouJiangLuckyCfg stu)
{
  ChouJiangLuckyCfg *v2; // rax
  ChouJiangLuckyCfg stua; // [rsp+8h] [rbp-18h] BYREF
  ChouJiangTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  stua = stu;
  v2 = std::map<int,ChouJiangLuckyCfg>::operator[](&this->m_ChouJiangLuckyCfgMap, &stua.MaxLucky);
  *v2 = stua;
}


#####################################
void __cdecl ChouJiangTable::AddChouJiangWeekReward(ChouJiangTable *const this, ChouJiangWeekReward *p_stu)
{
  ChouJiangWeekReward *v2; // rax

  v2 = std::map<int,ChouJiangWeekReward>::operator[](&this->m_ChouJiangWeekRewardMap, &p_stu->Index);
  ChouJiangWeekReward::operator=(v2, p_stu);
}


#####################################
void __cdecl ChouJiangTable::AddChouJiangCost(ChouJiangTable *const this, ChouJiangCost stu)
{
  ChouJiangCost *v2; // rax

  v2 = std::map<int,ChouJiangCost>::operator[](&this->m_ChouJiangCostMap, &stu.Times);
  *v2 = stu;
}


