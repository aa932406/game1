// Decompiled methods for class: CfgItemGem
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl CfgItemGem::CheckPos(const CfgItemGem *const this, int8_t nPos)
{
  const std::_List_node_base *M_node; // rbx
  std::_List_const_iterator<signed char> v3; // rax
  int8_t nPosa[4]; // [rsp+4h] [rbp-3Ch] BYREF
  const CfgItemGem *thisa; // [rsp+8h] [rbp-38h]
  std::_List_const_iterator<signed char> __x; // [rsp+10h] [rbp-30h] BYREF
  std::_List_const_iterator<signed char> v8; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nPosa[0] = nPos;
  __x._M_node = std::list<signed char>::end(&this->m_lAddPos)._M_node;
  M_node = std::list<signed char>::end(&this->m_lAddPos)._M_node;
  v3._M_node = std::list<signed char>::begin(&this->m_lAddPos)._M_node;
  v8._M_node = std::find<std::_List_const_iterator<signed char>,signed char>(
                 v3,
                 (std::_List_const_iterator<signed char>)M_node,
                 nPosa)._M_node;
  return std::_List_const_iterator<signed char>::operator!=(&v8, &__x);
}


