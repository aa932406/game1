// Decompiled methods for class: CfgJueWeiTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgJueWeiTable::AddJueWei(CfgJueWeiTable *const this, const CfgJueWei *const stu)
{
  CfgJueWei *v2; // rax

  v2 = std::map<signed char,CfgJueWei>::operator[](&this->m_mJueWei, &stu->nId);
  CfgJueWei::operator=(v2, stu);
  return 1;
}


