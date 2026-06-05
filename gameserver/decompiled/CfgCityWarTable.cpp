// Decompiled methods for class: CfgCityWarTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgCityWarTable::AddContReward(CfgCityWarTable *const this, const CfgCityWarContReward *const stu)
{
  std::list<CfgCityWarContReward>::push_back(&this->m_lContReward, stu);
}


