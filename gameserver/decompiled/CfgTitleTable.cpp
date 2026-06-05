// Decompiled methods for class: CfgTitleTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgTitleTable::Add(CfgTitleTable *const this, const CfgTitle *const title)
{
  CfgTitle *v2; // rax

  v2 = std::map<int,CfgTitle>::operator[](&this->m_mTitle, &title->nId);
  CfgTitle::operator=(v2, title);
}


