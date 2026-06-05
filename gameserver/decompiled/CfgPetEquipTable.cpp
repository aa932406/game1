// Decompiled methods for class: CfgPetEquipTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgPetEquipTable::AddEquip(CfgPetEquipTable *const this, const CfgPetEquip *const stu)
{
  CfgPetEquip *v2; // rax

  v2 = std::map<int,CfgPetEquip>::operator[](&this->m_mEquip, &stu->nId);
  CfgPetEquip::operator=(v2, stu);
  return 0;
}


