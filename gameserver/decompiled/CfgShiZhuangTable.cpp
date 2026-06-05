// Decompiled methods for class: CfgShiZhuangTable
// Source: gameserver.cc
// Total methods: 4

#####################################
bool __cdecl CfgShiZhuangTable::AddShiZhuang(CfgShiZhuangTable *const this, const CfgShiZhuang *const stu)
{
  CfgShiZhuang *v2; // rax

  v2 = std::map<int,CfgShiZhuang>::operator[](&this->m_mShiZhuang, &stu->nId);
  CfgShiZhuang::operator=(v2, stu);
  return 1;
}


#####################################
bool __cdecl CfgShiZhuangTable::AddShiZhuangLevel(CfgShiZhuangTable *const this, const CfgShiZhuangLevel *const stu)
{
  CfgShiZhuangLevel *v2; // rax
  std::pair<signed char,int> __k; // [rsp+10h] [rbp-10h] BYREF

  __k = std::make_pair<signed char,int>(stu->nType, stu->nLevel);
  v2 = std::map<std::pair<signed char,int>,CfgShiZhuangLevel>::operator[](&this->m_mShiZhuangLevel, &__k);
  CfgShiZhuangLevel::operator=(v2, stu);
  return 1;
}


#####################################
void __cdecl CfgShiZhuangTable::AddShiZhuangSuitInfo(CfgShiZhuangTable *const this, ShiZhuangSuitCfg *p_stu)
{
  ShiZhuangSuitCfg *v2; // rax

  v2 = std::map<int,ShiZhuangSuitCfg>::operator[](&this->m_ShiZhuangSuitCfgMap, &p_stu->nSuidId);
  ShiZhuangSuitCfg::operator=(v2, p_stu);
}


#####################################
int32_t __cdecl CfgShiZhuangTable::GetShiZhuangSuitLevel(
        const CfgShiZhuangTable *const this,
        int32_t SuitId,
        int32_t nLevel,
        int32_t nCount)
{
  const std::pair<const int,ShiZhuangSuitCfg> *v5; // rax
  const std::pair<const int,ShiZhuangSuitCfg> *v6; // rax
  int32_t SuitIda; // [rsp+14h] [rbp-4Ch] BYREF
  const CfgShiZhuangTable *thisa; // [rsp+18h] [rbp-48h]
  std::_List_const_iterator<ShiZhuangSuitInfo> itInfo; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,ShiZhuangSuitCfg> > it; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,ShiZhuangSuitCfg> > __x; // [rsp+40h] [rbp-20h] BYREF
  std::_List_const_iterator<ShiZhuangSuitInfo> v14; // [rsp+50h] [rbp-10h] BYREF
  int32_t nSuitId; // [rsp+5Ch] [rbp-4h]

  thisa = this;
  SuitIda = SuitId;
  nSuitId = 0;
  it._M_node = std::map<int,ShiZhuangSuitCfg>::find(&this->m_ShiZhuangSuitCfgMap, &SuitIda)._M_node;
  __x._M_node = std::map<int,ShiZhuangSuitCfg>::end(&thisa->m_ShiZhuangSuitCfgMap)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ShiZhuangSuitCfg>>::operator==(&it, &__x) )
    return 0;
  if ( std::_Rb_tree_const_iterator<std::pair<int const,ShiZhuangSuitCfg>>::operator->(&it)->second.nCount > nCount )
    return 0;
  v5 = std::_Rb_tree_const_iterator<std::pair<int const,ShiZhuangSuitCfg>>::operator->(&it);
  for ( itInfo._M_node = std::list<ShiZhuangSuitInfo>::begin(&v5->second.lInfo)._M_node;
        ;
        std::_List_const_iterator<ShiZhuangSuitInfo>::operator++(&itInfo, 0) )
  {
    v6 = std::_Rb_tree_const_iterator<std::pair<int const,ShiZhuangSuitCfg>>::operator->(&it);
    v14._M_node = std::list<ShiZhuangSuitInfo>::end(&v6->second.lInfo)._M_node;
    if ( !std::_List_const_iterator<ShiZhuangSuitInfo>::operator!=(&itInfo, &v14) )
      break;
    if ( std::_List_const_iterator<ShiZhuangSuitInfo>::operator->(&itInfo)->nLevel > 0 )
    {
      if ( std::_List_const_iterator<ShiZhuangSuitInfo>::operator->(&itInfo)->nLevel > nLevel )
        return nSuitId;
      nSuitId = std::_List_const_iterator<ShiZhuangSuitInfo>::operator->(&itInfo)->nSuitLevel;
    }
  }
  return nSuitId;
}


