// Decompiled methods for class: CfgAdultGiftTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgAdultGiftTable::Add(CfgAdultGiftTable *const this, const CfgAdultGift *const stu)
{
  CfgAdultGift *v2; // rax

  v2 = std::map<std::string,CfgAdultGift>::operator[](&this->m_mAdult, &stu->strPlatform);
  CfgAdultGift::operator=(v2, stu);
}


