// Decompiled methods for class: CfgEquipBoxTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgEquipBoxTable::AddEquipBox(CfgEquipBoxTable *const this, const CfgEquipBox *const stu)
{
  std::list<CfgEquipBox> *v2; // rax

  v2 = std::map<int,std::list<CfgEquipBox>>::operator[](&this->m_mEquipBox, &stu->nId);
  std::list<CfgEquipBox>::push_back(v2, stu);
}


