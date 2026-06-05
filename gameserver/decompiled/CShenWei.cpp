// Decompiled methods for class: CShenWei
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CShenWei::~CShenWei(CShenWei *const this)
{
  CShenWei::~CShenWei(this);
  operator delete(this);
}


#####################################
void __cdecl CShenWei::OnDaySwitch(CShenWei *const this, int32_t nDiffDays)
{
  int32_t ShenWeiLevel; // ebx
  CfgData *v3; // rax
  CfgCachet *pCfg; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    while ( nDiffDays > 0 )
    {
      ShenWeiLevel = CShenWei::GetShenWeiLevel(this);
      v3 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetCfgCachet(v3, ShenWeiLevel);
      if ( !pCfg || pCfg->nDeduct <= 0 )
        break;
      Player::DecCurrency(
        this->m_pPlayer,
        CURRENCY_TYPE::CURRENCY_HONOR,
        pCfg->nDeduct,
        CURRENCY_CHANGE_REASON::HCR_HALL_DAY_SWITCH,
        0);
      --nDiffDays;
    }
  }
}


#####################################
void __cdecl CShenWei::AddCharAttr(CShenWei *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  int32_t ShenWeiLevel; // ebx
  CfgData *v3; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v5; // rax
  std::_List_iterator<AddAttribute> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+20h] [rbp-20h] BYREF
  CfgCachet *pCfg; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 188) )
    {
      ShenWeiLevel = CShenWei::GetShenWeiLevel(this);
      v3 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetCfgCachet(v3, ShenWeiLevel);
      if ( pCfg )
      {
        for ( it._M_node = std::list<AddAttribute>::begin(&pCfg->nAttrList)._M_node;
              ;
              std::_List_iterator<AddAttribute>::operator++(&it, 0) )
        {
          __x._M_node = std::list<AddAttribute>::end(&pCfg->nAttrList)._M_node;
          if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
            break;
          m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
          v5 = std::_List_iterator<AddAttribute>::operator->(&it);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->m_nAddAttrType, m_nAddAttrValue);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CShenWei::GetRankAttr(CShenWei *const this, int64_t Exp)
{
  GameService *v2; // rax
  CharId_t Cid; // rbx
  CRankMirror *v5; // rax
  int32_t WeiWangIndex; // eax

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
    return 0;
  if ( !this->m_pPlayer )
    return 0;
  if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_HONOR) <= Exp )
    return 0;
  Cid = Player::getCid(this->m_pPlayer);
  v5 = Answer::Singleton<CRankMirror>::instance();
  WeiWangIndex = CRankMirror::GetWeiWangIndex(v5, Cid);
  switch ( WeiWangIndex )
  {
    case 2:
      return 10;
    case 3:
      return 8;
    case 1:
      return 12;
  }
  return 6;
}


#####################################
int32_t __cdecl CShenWei::GetShenWeiLevel(CShenWei *const this)
{
  int64_t Currency; // rbx
  CfgData *v3; // rax

  if ( !this->m_pPlayer )
    return 0;
  Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_HONOR);
  v3 = Answer::Singleton<CfgData>::instance();
  return CfgData::GetCachetLevel(v3, Currency);
}


