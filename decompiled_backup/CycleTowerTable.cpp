// Decompiled methods for class: CycleTowerTable
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CycleTowerTable::AddCycleTowerMapCfg(CycleTowerTable *const this, int32_t MapId, CycleTowerMapCfg stu)
{
  int *v3; // rax
  CycleTowerMapCfg stua; // [rsp+0h] [rbp-20h] BYREF
  int32_t MapIda; // [rsp+14h] [rbp-Ch] BYREF
  CycleTowerTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  MapIda = MapId;
  stua = stu;
  *std::map<int,CycleTowerMapCfg>::operator[](&this->m_CycleTowerMapCfgMap, &MapIda) = stu;
  v3 = std::map<int,int>::operator[](&thisa->m_CycleTowerFloor, &stua.Floor);
  *v3 = MapIda;
}


#####################################
int32_t __cdecl CycleTowerTable::GetMapId(const CycleTowerTable *const this, int32_t Floor)
{
  int32_t Floora; // [rsp+4h] [rbp-2Ch] BYREF
  const CycleTowerTable *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Floora = Floor;
  it._M_node = std::map<int,int>::find(&this->m_CycleTowerFloor, &Floora)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_CycleTowerFloor)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
int32_t __cdecl CycleTowerTable::GetCostGold(const CycleTowerTable *const this, int32_t Times)
{
  int32_t Timesa; // [rsp+4h] [rbp-2Ch] BYREF
  const CycleTowerTable *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_const_iterator<std::pair<const int,CycleTowerCost> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CycleTowerCost> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  Timesa = Times;
  it._M_node = std::map<int,CycleTowerCost>::lower_bound(&this->m_CycleTowerCostMap, &Timesa)._M_node;
  __x._M_node = std::map<int,CycleTowerCost>::end(&thisa->m_CycleTowerCostMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,CycleTowerCost>>::operator!=(&it, &__x) )
    return std::_Rb_tree_const_iterator<std::pair<int const,CycleTowerCost>>::operator->(&it)->second.CostGold;
  else
    return 0;
}


