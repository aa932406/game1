// Decompiled methods for class: CfgEquipDecompose
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgEquipDecompose::CleanUp(CfgEquipDecompose *const this)
{
  this->m_nId = 0;
  this->m_nCostMoney = 0;
  std::vector<MemChrBag>::clear(&this->m_vGiveItems);
}


