// Decompiled methods for class: XinMoTable
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl XinMoTable::AddXingMoCfg(XinMoTable *const this, XinMoCfg *p_Stu)
{
  XinMoCfg *v2; // rax

  v2 = std::map<int,XinMoCfg>::operator[](&this->m_XinMoCfgMap, &p_Stu->XinMoLevel);
  XinMoCfg::operator=(v2, p_Stu);
}


#####################################
void __cdecl XinMoTable::AddQiQingCfg(XinMoTable *const this, QiQingCfg *p_Stu)
{
  QiQingCfg *v2; // rax

  v2 = std::map<int,QiQingCfg>::operator[](&this->m_QiQingCfgMap, &p_Stu->nLevel);
  QiQingCfg::operator=(v2, p_Stu);
}


#####################################
void __cdecl XinMoTable::AddEquipJinHuaCfg(XinMoTable *const this, EquipJinHua *p_Stu)
{
  EquipJinHua *v2; // rax

  v2 = std::map<int,EquipJinHua>::operator[](&this->m_EquipJinHuaMap, &p_Stu->EquipId);
  EquipJinHua::operator=(v2, p_Stu);
}


#####################################
void __cdecl XinMoTable::AddXinMoQiQingLevelUpCfg(XinMoTable *const this, XinMoQiQingLevelUpCfg *p_Stu)
{
  _BYTE v2[64]; // [rsp+30h] [rbp-60h] BYREF
  std::pair<int,int> __a; // [rsp+70h] [rbp-20h] BYREF

  __a = std::make_pair<int,int>(p_Stu->nType, p_Stu->nLevel);
  std::pair<std::pair const<int,int>,XinMoQiQingLevelUpCfg>::pair(
    (std::pair<const std::pair<int,int>,XinMoQiQingLevelUpCfg> *const)v2,
    &__a,
    p_Stu);
  std::map<std::pair<int,int>,XinMoQiQingLevelUpCfg>::insert(
    &this->m_XinMoQiQingLevelUpCfgMap,
    (const std::pair<const std::pair<int,int>,XinMoQiQingLevelUpCfg> *const)v2);
  std::pair<std::pair const<int,int>,XinMoQiQingLevelUpCfg>::~pair((std::pair<const std::pair<int,int>,XinMoQiQingLevelUpCfg> *const)v2);
}


#####################################
void __cdecl XinMoTable::AddXinQingCfg(XinMoTable *const this, XinQingCfg stu)
{
  XinQingCfg stua; // [rsp+8h] [rbp-18h] BYREF
  XinMoTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  stua = stu;
  std::list<XinQingCfg>::push_back(&this->m_XinQingCfgList, &stua);
}


#####################################
void __cdecl XinMoTable::AddXinQingReward(XinMoTable *const this, int32_t nId, XinQingReward *p_stu)
{
  XinQingReward *v3; // rax
  int32_t nIda; // [rsp+14h] [rbp-Ch] BYREF
  XinMoTable *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  nIda = nId;
  v3 = std::map<int,XinQingReward>::operator[](&this->m_MemChrBagVectorMap, &nIda);
  XinQingReward::operator=(v3, p_stu);
}


#####################################
int32_t __cdecl XinMoTable::GetAppearCount(const XinMoTable *const this, int32_t nLeftCount)
{
  const XinQingCfg *v2; // rax
  const XinQingCfg *v3; // rax
  int32_t nAppearCount; // ebx
  Answer::Random *v5; // rax
  XinQingCfg *v6; // rax
  XinQingCfg *v7; // rax
  std::_List_iterator<XinQingCfg> itTmp; // [rsp+10h] [rbp-60h] BYREF
  std::_List_const_iterator<XinQingCfg> it; // [rsp+20h] [rbp-50h] BYREF
  XinQingCfgList TmpList; // [rsp+30h] [rbp-40h] BYREF
  std::_List_const_iterator<XinQingCfg> __x; // [rsp+40h] [rbp-30h] BYREF
  std::_List_iterator<XinQingCfg> v13; // [rsp+50h] [rbp-20h] BYREF
  int32_t nMaxRate; // [rsp+58h] [rbp-18h]
  int32_t nRand; // [rsp+5Ch] [rbp-14h]

  std::list<XinQingCfg>::list(&TmpList);
  nMaxRate = 0;
  for ( it._M_node = std::list<XinQingCfg>::begin(&this->m_XinQingCfgList)._M_node;
        ;
        std::_List_const_iterator<XinQingCfg>::operator++(&it, 0) )
  {
    __x._M_node = std::list<XinQingCfg>::end(&this->m_XinQingCfgList)._M_node;
    if ( !std::_List_const_iterator<XinQingCfg>::operator!=(&it, &__x) )
      break;
    if ( std::_List_const_iterator<XinQingCfg>::operator->(&it)->nLeftCount == nLeftCount )
    {
      v2 = std::_List_const_iterator<XinQingCfg>::operator*(&it);
      std::list<XinQingCfg>::push_back(&TmpList, v2);
      v3 = std::_List_const_iterator<XinQingCfg>::operator->(&it);
      nMaxRate += v3->Rate;
    }
  }
  if ( nMaxRate > 0 )
  {
    v5 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v5, 1, nMaxRate);
    for ( itTmp._M_node = std::list<XinQingCfg>::begin(&TmpList)._M_node;
          ;
          std::_List_iterator<XinQingCfg>::operator++(&itTmp, 0) )
    {
      v13._M_node = std::list<XinQingCfg>::end(&TmpList)._M_node;
      if ( !std::_List_iterator<XinQingCfg>::operator!=(&itTmp, &v13) )
        break;
      v6 = std::_List_iterator<XinQingCfg>::operator->(&itTmp);
      if ( v6->Rate >= nRand )
      {
        nAppearCount = std::_List_iterator<XinQingCfg>::operator->(&itTmp)->nAppearCount;
        goto LABEL_14;
      }
      v7 = std::_List_iterator<XinQingCfg>::operator->(&itTmp);
      nRand -= v7->Rate;
    }
    nAppearCount = 0;
  }
  else
  {
    nAppearCount = 0;
  }
LABEL_14:
  std::list<XinQingCfg>::~list(&TmpList);
  return nAppearCount;
}


