// Decompiled methods for class: CfgItemCombiTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgItemCombiTable::Add(CfgItemCombiTable *const this, const CfgItemCombi *const itemCombi)
{
  CfgItemCombi *v2; // rax

  v2 = std::map<int,CfgItemCombi>::operator[](&this->m_mItemCombi, &itemCombi->m_nId);
  CfgItemCombi::operator=(v2, itemCombi);
}


