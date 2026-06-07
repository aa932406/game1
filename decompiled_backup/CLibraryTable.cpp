// Decompiled methods for class: CLibraryTable
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CLibraryTable::AddCfgLibraryItem(CLibraryTable *const this, CfgLibraryItem stu)
{
  CfgLibraryItem *v2; // rax

  v2 = std::map<int,CfgLibraryItem>::operator[](&this->m_CfgLibraryItemMap, &stu.nIndex);
  *v2 = stu;
}


#####################################
void __cdecl CLibraryTable::AddCfgLibraryQuality(CLibraryTable *const this, CfgLibraryQuality stu)
{
  CfgLibraryQuality *v2; // rax
  int *v3; // rax
  CfgLibraryQuality stua; // [rsp+8h] [rbp-18h] BYREF
  CLibraryTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  stua = stu;
  v2 = std::map<int,CfgLibraryQuality>::operator[](&this->m_CfgLibraryQualityMap, &stua.nIndex);
  *v2 = stua;
  v3 = std::map<int,int>::operator[](&thisa->m_QualityMaxProbabilityMap, &stua.nQuality);
  *v3 += stua.nProbability;
}


#####################################
void __cdecl CLibraryTable::AddCfgLibraryCost(CLibraryTable *const this, CfgLibraryCost stu)
{
  _BYTE v2[32]; // [rsp+30h] [rbp-30h] BYREF
  std::pair<int,int> __a; // [rsp+50h] [rbp-10h] BYREF

  __a = std::make_pair<int,int>(stu.Times, stu.nDunGeonId);
  std::pair<std::pair const<int,int>,CfgLibraryCost>::pair(
    (std::pair<const std::pair<int,int>,CfgLibraryCost> *const)v2,
    &__a,
    &stu);
  std::map<std::pair<int,int>,CfgLibraryCost>::insert(
    &this->m_CfgLibraryCostMap,
    (const std::pair<const std::pair<int,int>,CfgLibraryCost> *const)v2);
}


