// Decompiled methods for class: CfgPetTable
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CfgPetTable::Add(CfgPetTable *const this, const CfgPetData *const pet)
{
  CfgPetData *v2; // rax

  v2 = std::map<int,CfgPetData>::operator[](&this->m_mPetCfgData, &pet->m_nPetId);
  CfgPetData::operator=(v2, pet);
}


#####################################
bool __cdecl CfgPetTable::AddAttr(CfgPetTable *const this, const CfgPetData *const pet)
{
  std::pair<const int,CfgPetData> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,CfgPetData> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgPetData> > __x; // [rsp+20h] [rbp-20h] BYREF

  iter._M_node = std::map<int,CfgPetData>::find(&this->m_mPetCfgData, &pet->m_nPetId)._M_node;
  __x._M_node = std::map<int,CfgPetData>::end(&this->m_mPetCfgData)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CfgPetData>>::operator==(&iter, &__x) )
    return 0;
  v3 = std::_Rb_tree_iterator<std::pair<int const,CfgPetData>>::operator->(&iter);
  std::vector<AttrAddon>::operator=(&v3->second.m_vBaseAttr, &pet->m_vBaseAttr);
  return 1;
}


#####################################
void __cdecl CfgPetTable::AddPetUpStar(CfgPetTable *const this, const CfgPetUpStar *const stu)
{
  CfgPetUpStar *v2; // rax

  v2 = std::map<int,CfgPetUpStar>::operator[](&this->m_mPetUpStar, &stu->nStar);
  CfgPetUpStar::operator=(v2, stu);
}


