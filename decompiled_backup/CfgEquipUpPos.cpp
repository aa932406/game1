// Decompiled methods for class: CfgEquipUpPos
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgEquipUpPos::CleanUp(CfgEquipUpPos *const this)
{
  this->m_nType = 0;
  this->m_nLevel = 0;
  this->m_nRate = 0;
  this->m_nCostMoney = 0;
  this->m_nNeedLevel = 0;
  std::vector<AttrAddon>::clear(&this->m_vAttrAddon);
}


