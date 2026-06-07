// Decompiled methods for class: CfgWeiXinTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgWeiXinTable::Add(CfgWeiXinTable *const this, const CfgWeiXingGift *const stu)
{
  CfgWeiXingGift *v2; // rax

  v2 = std::map<std::string,CfgWeiXingGift>::operator[](&this->m_mWeiXing, &stu->strPlatform);
  CfgWeiXingGift::operator=(v2, stu);
}


