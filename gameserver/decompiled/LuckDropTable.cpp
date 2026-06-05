// Decompiled methods for class: LuckDropTable
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl LuckDropTable::AddLuckDrop(LuckDropTable *const this, LuckDrop *p_stu)
{
  LuckDrop *v2; // rax
  std::pair<int,int> __k; // [rsp+10h] [rbp-10h] BYREF

  __k = std::make_pair<int,int>(p_stu->Type, p_stu->VipLevel);
  v2 = std::map<std::pair<int,int>,LuckDrop>::operator[](&this->m_LuckDropMap, &__k);
  LuckDrop::operator=(v2, p_stu);
}


#####################################
int32_t __cdecl LuckDropTable::GetLuckRate(const LuckDropTable *const this, int32_t Type, int32_t VipLevel)
{
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,LuckDrop> > it; // [rsp+10h] [rbp-30h] BYREF
  std::pair<int,int> __x; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,LuckDrop> > v6; // [rsp+30h] [rbp-10h] BYREF

  __x = std::make_pair<int,int>(Type, VipLevel);
  it._M_node = std::map<std::pair<int,int>,LuckDrop>::find(&this->m_LuckDropMap, &__x)._M_node;
  v6._M_node = std::map<std::pair<int,int>,LuckDrop>::end(&this->m_LuckDropMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,LuckDrop>>::operator!=(&it, &v6) )
    return *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,LuckDrop>>::operator->(&it) + 8);
  else
    return 0;
}


