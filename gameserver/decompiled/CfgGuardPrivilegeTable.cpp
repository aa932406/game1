// Decompiled methods for class: CfgGuardPrivilegeTable
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl CfgGuardPrivilegeTable::Add(CfgGuardPrivilegeTable *const this, const CfgGuardPrivilege *const stu)
{
  CfgGuardPrivilege *v2; // rax

  v2 = std::map<signed char,CfgGuardPrivilege>::operator[](&this->m_mGuardPrivilege, &stu->nIndex);
  CfgGuardPrivilege::operator=(v2, stu);
  return 1;
}


#####################################
void __cdecl CfgGuardPrivilegeTable::SetTime(CfgGuardPrivilegeTable *const this, int32_t nStartTime, int32_t nEndTime)
{
  this->m_nStartTime = nStartTime;
  this->m_nEndTime = nEndTime;
}


