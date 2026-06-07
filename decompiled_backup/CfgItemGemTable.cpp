// Decompiled methods for class: CfgItemGemTable
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl CfgItemGemTable::Add(CfgItemGemTable *const this, const CfgItemGem *const gem)
{
  CfgItemGem *v2; // rax

  v2 = std::map<int,CfgItemGem>::operator[](&this->m_mGemMap, &gem->m_nId);
  CfgItemGem::operator=(v2, gem);
}


#####################################
void __cdecl CfgItemGemTable::AddGemOpenHole(CfgItemGemTable *const this, const CfgGemOpenHole *const stu)
{
  std::list<CfgGemOpenHole>::push_back(&this->m_lGemOpenHole, stu);
}


#####################################
void __cdecl CfgItemGemTable::AddGemLevelUp(CfgItemGemTable *const this, const CfgGemLevelUp *const stu)
{
  CfgGemLevelUp *v2; // rax

  v2 = std::map<int,CfgGemLevelUp>::operator[](&this->m_mGemLevelUp, &stu->nId);
  CfgGemLevelUp::operator=(v2, stu);
}


#####################################
void __cdecl CfgItemGemTable::AddGemSuit(CfgItemGemTable *const this, const CfgGemSuit *const stu)
{
  std::list<CfgGemSuit>::push_front(&this->m_lGemSuit, stu);
}


