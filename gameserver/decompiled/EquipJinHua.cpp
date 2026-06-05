// Decompiled methods for class: EquipJinHua
// Source: gameserver.cc
// Total methods: 1

#####################################
int32_t __cdecl EquipJinHua::GetParamRate(const EquipJinHua *const this)
{
  int32_t MaxRate; // ebx
  Answer::Random *v2; // rax
  const Param2 *v3; // rax
  const Param2 *v5; // rax
  std::_List_const_iterator<Param2> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_const_iterator<Param2> __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nRand; // [rsp+2Ch] [rbp-14h]

  MaxRate = this->MaxRate;
  v2 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v2, 1, MaxRate);
  for ( it._M_node = std::list<Param2>::begin(&this->Rate)._M_node; ; std::_List_const_iterator<Param2>::operator++(
                                                                        &it,
                                                                        0) )
  {
    __x._M_node = std::list<Param2>::end(&this->Rate)._M_node;
    if ( !std::_List_const_iterator<Param2>::operator!=(&it, &__x) )
      break;
    v3 = std::_List_const_iterator<Param2>::operator->(&it);
    if ( v3->nParam2 >= nRand )
      return std::_List_const_iterator<Param2>::operator->(&it)->nParam1;
    v5 = std::_List_const_iterator<Param2>::operator->(&it);
    nRand -= v5->nParam2;
  }
  return 0;
}


