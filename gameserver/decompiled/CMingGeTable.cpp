// Decompiled methods for class: CMingGeTable
// Source: gameserver.cc
// Total methods: 4

#####################################
void __cdecl CMingGeTable::AddMingGeCfg(CMingGeTable *const this, CMingGeCfg *p_stu)
{
  CMingGeCfg *v2; // rax

  v2 = std::map<int,CMingGeCfg>::operator[](&this->m_CMingGeCfgMap, &p_stu->nId);
  CMingGeCfg::operator=(v2, p_stu);
}


#####################################
void __cdecl CMingGeTable::AddMingGeDrawCost(CMingGeTable *const this, MingGeDrawCost stu)
{
  MingGeDrawCost *v2; // rax
  MingGeDrawCost stua; // [rsp+8h] [rbp-18h] BYREF
  CMingGeTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  stua = stu;
  v2 = std::map<int,MingGeDrawCost>::operator[](&this->m_MingGeDrawCostMap, &stua.nType);
  *v2 = stua;
}


#####################################
void __cdecl CMingGeTable::AddMingGeDrawRate(CMingGeTable *const this, int32_t nType, Param2 ItemRate)
{
  MingGeDrawRate *v3; // rax
  MingGeDrawRate *v4; // rax
  Param2 ItemRatea; // [rsp+0h] [rbp-20h] BYREF
  int32_t nTypea; // [rsp+14h] [rbp-Ch] BYREF
  CMingGeTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nTypea = nType;
  ItemRatea = ItemRate;
  v3 = std::map<int,MingGeDrawRate>::operator[](&this->m_MingGeDrawRateMap, &nTypea);
  std::list<Param2>::push_back(&v3->nItemRate, &ItemRatea);
  v4 = std::map<int,MingGeDrawRate>::operator[](&thisa->m_MingGeDrawRateMap, &nTypea);
  v4->nMaxRate += ItemRatea.nParam2;
}


#####################################
int32_t __cdecl CMingGeTable::RandMingGe(const CMingGeTable *const this, int32_t nType)
{
  int32_t nMaxRate; // ebx
  Answer::Random *v3; // rax
  const std::pair<const int,MingGeDrawRate> *v4; // rax
  const Param2 *v5; // rax
  const Param2 *v7; // rax
  const std::pair<const int,MingGeDrawRate> *v8; // rax
  int32_t nTypea; // [rsp+4h] [rbp-5Ch] BYREF
  const CMingGeTable *thisa; // [rsp+8h] [rbp-58h]
  std::_List_const_iterator<Param2> itRate; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MingGeDrawRate> > it; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MingGeDrawRate> > __x; // [rsp+30h] [rbp-30h] BYREF
  std::_List_const_iterator<Param2> v14; // [rsp+40h] [rbp-20h] BYREF
  int32_t nRand; // [rsp+4Ch] [rbp-14h]

  thisa = this;
  nTypea = nType;
  it._M_node = std::map<int,MingGeDrawRate>::find(&this->m_MingGeDrawRateMap, &nTypea)._M_node;
  __x._M_node = std::map<int,MingGeDrawRate>::end(&thisa->m_MingGeDrawRateMap)._M_node;
  if ( !std::_Rb_tree_const_iterator<std::pair<int const,MingGeDrawRate>>::operator!=(&it, &__x) )
    return 0;
  nMaxRate = std::_Rb_tree_const_iterator<std::pair<int const,MingGeDrawRate>>::operator->(&it)->second.nMaxRate;
  v3 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v3, 1, nMaxRate);
  v4 = std::_Rb_tree_const_iterator<std::pair<int const,MingGeDrawRate>>::operator->(&it);
  for ( itRate._M_node = std::list<Param2>::begin(&v4->second.nItemRate)._M_node;
        ;
        std::_List_const_iterator<Param2>::operator++(&itRate, 0) )
  {
    v8 = std::_Rb_tree_const_iterator<std::pair<int const,MingGeDrawRate>>::operator->(&it);
    v14._M_node = std::list<Param2>::end(&v8->second.nItemRate)._M_node;
    if ( !std::_List_const_iterator<Param2>::operator!=(&itRate, &v14) )
      break;
    v5 = std::_List_const_iterator<Param2>::operator->(&itRate);
    if ( v5->nParam2 >= nRand )
      return std::_List_const_iterator<Param2>::operator->(&itRate)->nParam1;
    v7 = std::_List_const_iterator<Param2>::operator->(&itRate);
    nRand -= v7->nParam2;
  }
  return 0;
}


