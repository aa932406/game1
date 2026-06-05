// Decompiled methods for class: CfgEquipBlessTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgEquipBlessTable::Add(CfgEquipBlessTable *const this, const CfgEquipBless *const stu)
{
  std::list<CfgEquipBless>::push_back(&this->m_lstBless, stu);
  return 1;
}


