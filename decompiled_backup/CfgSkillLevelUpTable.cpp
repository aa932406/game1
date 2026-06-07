// Decompiled methods for class: CfgSkillLevelUpTable
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgSkillLevelUpTable::Add(CfgSkillLevelUpTable *const this, const CfgSkillLevelUp *const skill)
{
  *std::map<int,CfgSkillLevelUp>::operator[](&this->m_mSkillLevelUpMap, &skill->nSkillId) = *skill;
  return 1;
}


