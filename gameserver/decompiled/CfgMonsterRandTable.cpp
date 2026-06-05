// Decompiled methods for class: CfgMonsterRandTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgMonsterRandTable::AddMonsterRand(CfgMonsterRandTable *const this, const CfgMonsterRand *const stu)
{
  CfgMonsterRand *v2; // rax

  v2 = std::map<int,CfgMonsterRand>::operator[](&this->m_mMonsterRand, &stu->nId);
  CfgMonsterRand::operator=(v2, stu);
  std::vector<int>::push_back(&this->m_vId, &stu->nId);
}


