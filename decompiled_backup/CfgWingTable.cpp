// Decompiled methods for class: CfgWingTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgWingTable::AddWingCfg(CfgWingTable *const this, WingCfg *p_stu)
{
  WingCfg *v2; // rax

  v2 = std::map<int,WingCfg>::operator[](&this->m_WingCfgMap, &p_stu->Level);
  WingCfg::operator=(v2, p_stu);
}


