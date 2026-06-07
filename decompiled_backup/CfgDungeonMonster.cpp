// Decompiled methods for class: CfgDungeonMonster
// Source: gameserver.cc
// Total methods: 1

#####################################
int32_t __cdecl CfgDungeonMonster::GetMid(const CfgDungeonMonster *const this)
{
  Answer::Random *v2; // rax
  const Param2 *v3; // rax
  const Param2 *v4; // rax
  std::_List_const_iterator<Param2> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<Param2> __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nRand; // [rsp+2Ch] [rbp-4h]

  if ( std::list<Param2>::empty(&this->mids) )
    return 0;
  if ( std::list<Param2>::size(&this->mids) == 1 )
    return std::list<Param2>::front(&this->mids)->nParam1;
  v2 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v2, 1, 10000);
  for ( iter._M_node = std::list<Param2>::begin(&this->mids)._M_node; ; std::_List_const_iterator<Param2>::operator++(&iter) )
  {
    __x._M_node = std::list<Param2>::end(&this->mids)._M_node;
    if ( !std::_List_const_iterator<Param2>::operator!=(&iter, &__x) )
      break;
    v3 = std::_List_const_iterator<Param2>::operator->(&iter);
    if ( v3->nParam2 >= nRand )
      return std::_List_const_iterator<Param2>::operator->(&iter)->nParam1;
    v4 = std::_List_const_iterator<Param2>::operator->(&iter);
    nRand -= v4->nParam2;
  }
  return 0;
}


