// Decompiled methods for class: CfgSkillTable
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl CfgSkillTable::AddActiveSkill(CfgSkillTable *const this, const CfgActiveSkill *const skill)
{
  CfgActiveSkill *v2; // rax

  *std::map<int,signed char>::operator[](&this->m_mSkillType, &skill->id) = 1;
  v2 = std::map<int,CfgActiveSkill>::operator[](&this->m_mActiveSkills, &skill->id);
  CfgActiveSkill::operator=(v2, skill);
}


#####################################
void __cdecl CfgSkillTable::AddPassiveSkill(CfgSkillTable *const this, const CfgPassiveSkill *const skill)
{
  CfgPassiveSkill *v2; // rax

  *std::map<int,signed char>::operator[](&this->m_mSkillType, &skill->id) = 2;
  v2 = std::map<int,CfgPassiveSkill>::operator[](&this->m_mPassiveSkills, &skill->id);
  CfgPassiveSkill::operator=(v2, skill);
}


#####################################
void __cdecl CfgSkillTable::AddTrigSkill(CfgSkillTable *const this, const CfgTrigSkill *const skill)
{
  CfgTrigSkill *v2; // rax

  *std::map<int,signed char>::operator[](&this->m_mSkillType, &skill->id) = 3;
  v2 = std::map<int,CfgTrigSkill>::operator[](&this->m_mTrigSkills, &skill->id);
  CfgTrigSkill::operator=(v2, skill);
}


#####################################
void __cdecl CfgSkillTable::AddFamilySkill(CfgSkillTable *const this, const CfgFamilySkill *const skill)
{
  CfgFamilySkill *v2; // rax
  std::pair<int,int> __k; // [rsp+10h] [rbp-10h] BYREF

  __k = std::make_pair<int,int>(skill->nId, skill->nLevel);
  v2 = std::map<std::pair<int,int>,CfgFamilySkill>::operator[](&this->m_mFamilySkills, &__k);
  CfgFamilySkill::operator=(v2, skill);
}


#####################################
void __cdecl CfgSkillTable::AddTalentActive(CfgSkillTable *const this, const CfgTalentActive *const stu)
{
  CfgTalentActive *v2; // rax

  v2 = std::map<int,CfgTalentActive>::operator[](&this->m_mTalentActive, &stu->nId);
  CfgTalentActive::operator=(v2, stu);
}


#####################################
int8_t __cdecl CfgSkillTable::GetSkillType(const CfgSkillTable *const this, int32_t id)
{
  int32_t ida; // [rsp+4h] [rbp-2Ch] BYREF
  const CfgSkillTable *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,signed char> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,signed char> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  ida = id;
  iter._M_node = std::map<int,signed char>::find(&this->m_mSkillType, &ida)._M_node;
  __x._M_node = std::map<int,signed char>::end(&thisa->m_mSkillType)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,signed char>>::operator!=(&iter, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,signed char>>::operator->(&iter)->second;
  else
    return 0;
}


