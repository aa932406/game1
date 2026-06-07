// Decompiled methods for class: BossKilledRewardInfo
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl BossKilledRewardInfo::CanGetReward(BossKilledRewardInfo *const this)
{
  std::_List_iterator<BossKilledInfo> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<BossKilledInfo> __x; // [rsp+20h] [rbp-10h] BYREF

  if ( this->IsGetReward > 0 )
    return 0;
  for ( it._M_node = std::list<BossKilledInfo>::begin(&this->BossKeilled)._M_node;
        ;
        std::_List_iterator<BossKilledInfo>::operator++(&it, 0) )
  {
    __x._M_node = std::list<BossKilledInfo>::end(&this->BossKeilled)._M_node;
    if ( !std::_List_iterator<BossKilledInfo>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<BossKilledInfo>::operator->(&it)->IsKilled <= 0 )
      return 0;
  }
  return 1;
}


#####################################
bool __cdecl BossKilledRewardInfo::SetBossKilled(BossKilledRewardInfo *const this, int32_t BossId)
{
  std::_List_iterator<BossKilledInfo> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<BossKilledInfo> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<BossKilledInfo>::begin(&this->BossKeilled)._M_node;
        ;
        std::_List_iterator<BossKilledInfo>::operator++(&it, 0) )
  {
    __x._M_node = std::list<BossKilledInfo>::end(&this->BossKeilled)._M_node;
    if ( !std::_List_iterator<BossKilledInfo>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<BossKilledInfo>::operator->(&it)->BossId == BossId
      && std::_List_iterator<BossKilledInfo>::operator->(&it)->IsKilled <= 0 )
    {
      std::_List_iterator<BossKilledInfo>::operator->(&it)->IsKilled = 1;
      return 1;
    }
  }
  return 0;
}


