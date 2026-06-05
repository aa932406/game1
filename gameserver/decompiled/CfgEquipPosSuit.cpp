// Decompiled methods for class: CfgEquipPosSuit
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgEquipPosSuit::CleanUp(CfgEquipPosSuit *const this)
{
  this->m_nLevel = 0;
  std::vector<AttrAddon>::clear(&this->m_vAttrAddon);
}


