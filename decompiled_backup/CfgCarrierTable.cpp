// Decompiled methods for class: CfgCarrierTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl CfgCarrierTable::AddCarrier(CfgCarrierTable *const this, const CfgCarrier *const stu)
{
  CfgCarrier *v2; // rax

  v2 = std::map<int,CfgCarrier>::operator[](&this->m_mCarrier, &stu->nId);
  CfgCarrier::operator=(v2, stu);
}


#####################################
void __cdecl CfgCarrierTable::AddCarrierAttr(CfgCarrierTable *const this, const CfgCarrierAttr *const stu)
{
  CfgCarrierAttr *v2; // rax
  std::pair<int,int> __k; // [rsp+10h] [rbp-10h] BYREF

  __k = std::make_pair<int,int>(stu->nId, stu->nLevel);
  v2 = std::map<std::pair<int,int>,CfgCarrierAttr>::operator[](&this->m_mCarrierAttr, &__k);
  CfgCarrierAttr::operator=(v2, stu);
}


