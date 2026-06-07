// Decompiled methods for class: CfgTalentTable
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CfgTalentTable::AddTalent(CfgTalentTable *const this, const CfgTalent *const stu)
{
  CfgTalent *v2; // rax
  int32_t Level; // ebx
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::pair<int,int> __k; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-20h] BYREF

  __k = std::make_pair<int,int>(stu->id, stu->Level);
  v2 = std::map<std::pair<int,int>,CfgTalent>::operator[](&this->m_mTalent, &__k);
  CfgTalent::operator=(v2, stu);
  iter._M_node = std::map<int,int>::find(&this->m_mTalentMax, &stu->id)._M_node;
  __x._M_node = std::map<int,int>::end(&this->m_mTalentMax)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&iter, &__x) )
  {
    *std::map<int,int>::operator[](&this->m_mTalentMax, &stu->id) = stu->Level;
  }
  else
  {
    Level = stu->Level;
    if ( Level > std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second )
      std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second = stu->Level;
  }
}


#####################################
void __cdecl CfgTalentTable::AddTalentPage(CfgTalentTable *const this, const CfgTalentPage *const stu)
{
  CfgTalentPage *v2; // rax

  v2 = std::map<signed char,CfgTalentPage>::operator[](&this->m_mTalentPage, &stu->job);
  CfgTalentPage::operator=(v2, stu);
}


#####################################
bool __cdecl CfgTalentTable::IsTalentSkill(const CfgTalentTable *const this, Job_t job, SkillId_t id)
{
  const std::pair<const signed char,CfgTalentPage> *v3; // rax
  const std::pair<const signed char,CfgTalentPage> *v5; // rax
  Job_t joba[4]; // [rsp+4h] [rbp-4Ch] BYREF
  const CfgTalentTable *thisa; // [rsp+8h] [rbp-48h]
  std::_List_const_iterator<int> it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgTalentPage> > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgTalentPage> > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_List_const_iterator<int> v12; // [rsp+40h] [rbp-10h] BYREF

  thisa = this;
  joba[0] = job;
  iter._M_node = std::map<signed char,CfgTalentPage>::find(&this->m_mTalentPage, joba)._M_node;
  __x._M_node = std::map<signed char,CfgTalentPage>::end(&thisa->m_mTalentPage)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<signed char const,CfgTalentPage>>::operator!=(&iter, &__x) )
  {
    v3 = std::_Rb_tree_const_iterator<std::pair<signed char const,CfgTalentPage>>::operator->(&iter);
    for ( it._M_node = std::list<int>::begin(&v3->second.talents)._M_node;
          ;
          std::_List_const_iterator<int>::operator++(&it, 0) )
    {
      v5 = std::_Rb_tree_const_iterator<std::pair<signed char const,CfgTalentPage>>::operator->(&iter);
      v12._M_node = std::list<int>::end(&v5->second.talents)._M_node;
      if ( !std::_List_const_iterator<int>::operator!=(&it, &v12) )
        break;
      if ( *std::_List_const_iterator<int>::operator*(&it) == id )
        return 1;
    }
  }
  return 0;
}


