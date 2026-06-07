// Decompiled methods for class: CfgShouChongTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgShouChongTable::Add(CfgShouChongTable *const this, const CfgShouChong *const stu)
{
  CfgShouChong *v2; // rax

  v2 = std::map<signed char,CfgShouChong>::operator[](&this->m_mShouChong, &stu->nIndex);
  CfgShouChong::operator=(v2, stu);
  return 1;
}


