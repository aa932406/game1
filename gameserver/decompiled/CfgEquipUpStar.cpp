// Decompiled methods for class: CfgEquipUpStar
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgEquipUpStar::CleanUp(CfgEquipUpStar *const this)
{
  this->m_nType = 0;
  this->m_nStar = 0;
  this->m_nRate = 0;
  this->m_nSuccessAddStar = 0;
  this->m_nFailLostStar = 0;
  this->m_nCostMoney = 0;
  this->m_nCostXingMai = 0;
  std::list<ItemData>::clear(&this->m_lCosItem);
  std::vector<AttrAddon>::clear(&this->m_vAttrAddon);
}


