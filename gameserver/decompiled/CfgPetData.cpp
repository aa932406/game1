// Decompiled methods for class: CfgPetData
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgPetData::CleanUp(CfgPetData *const this)
{
  this->m_nPetId = 0;
  this->m_Quality = 0;
  bzero(this->m_vSkill, 0x24u);
  bzero(this->m_vSkillOpen, 0x24u);
  std::vector<AttrAddon>::clear(&this->m_vBaseAttr);
}


