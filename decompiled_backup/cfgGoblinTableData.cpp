// Decompiled methods for class: cfgGoblinTableData
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl cfgGoblinTableData::Add(cfgGoblinTableData *const this, cfgGoblinData *const stu)
{
  cfgGoblinData *v2; // rax

  v2 = std::map<int,cfgGoblinData>::operator[](&this->m_GoblinDataMap, &stu->m_nIndex);
  cfgGoblinData::operator=(v2, stu);
}


