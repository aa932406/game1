// Decompiled methods for class: CWuHunShop
// Source: gameserver.cc
// Total methods: 16

#####################################
void __cdecl CWuHunShop::~CWuHunShop(CWuHunShop *const this)
{
  CWuHunShop::~CWuHunShop(this);
  operator delete(this);
}


#####################################
void __cdecl CWuHunShop::OnCleanUp(CWuHunShop *const this)
{
  std::map<int,WuHunShop>::clear(&this->m_WuHunShopMap);
  this->m_RefreshTimes = 0;
  this->m_LastRefreshTime = 0;
}


#####################################
void __cdecl CWuHunShop::OnDaySwitch(CWuHunShop *const this, int32_t nDiffDays)
{
  int first; // edx
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::map<int,WuHunShop>::begin(&this->m_WuHunShopMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,WuHunShop>::end(&this->m_WuHunShopMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator->(&it)->first;
    CWuHunShop::RefreshShop(this, first);
  }
}


#####################################
void __cdecl CWuHunShop::OnUpdate(CWuHunShop *const this, int64_t curTick)
{
  if ( this->m_pPlayer && this->m_LastRefreshTime > 0 && Unit::getNow(this->m_pPlayer) >= this->m_LastRefreshTime + 7200 )
  {
    CWuHunShop::AddRefreshTimes(this, 1, 1);
    this->m_LastRefreshTime = Unit::getNow(this->m_pPlayer);
  }
}


#####################################
void __cdecl CWuHunShop::AddRefreshTimes(CWuHunShop *const this, int32_t Times, bool IsNow)
{
  if ( this->m_pPlayer )
  {
    if ( this->m_RefreshTimes <= 4 )
    {
      this->m_RefreshTimes += Times;
      if ( IsNow )
        this->m_LastRefreshTime = Unit::getNow(this->m_pPlayer);
      if ( this->m_RefreshTimes > 4 )
      {
        this->m_RefreshTimes = 5;
        this->m_LastRefreshTime = 0;
      }
      CWuHunShop::sendShopRefreshTimes(this);
    }
    else
    {
      this->m_RefreshTimes = 5;
      this->m_LastRefreshTime = 0;
    }
  }
}


#####################################
void __cdecl CWuHunShop::SubRefreshTimes(CWuHunShop *const this)
{
  --this->m_RefreshTimes;
  if ( !this->m_LastRefreshTime )
    this->m_LastRefreshTime = Unit::getNow(this->m_pPlayer);
  CWuHunShop::sendShopRefreshTimes(this);
}


#####################################
void __cdecl CWuHunShop::OnLoadFromDB(CWuHunShop *const this, const PlayerDBData *const dbData)
{
  int AddCount; // [rsp+1Ch] [rbp-4h]

  this->m_LastRefreshTime = dbData->m_WuHunShopDBData.m_LastRefreshTime;
  this->m_RefreshTimes = dbData->m_WuHunShopDBData.m_RefreshTimes;
  std::map<int,WuHunShop>::operator=(&this->m_WuHunShopMap, &dbData->m_WuHunShopDBData.m_WuHunShopMap);
  if ( this->m_pPlayer && this->m_LastRefreshTime > 0 )
  {
    AddCount = (Unit::getNow(this->m_pPlayer) - this->m_LastRefreshTime) / 7200;
    if ( AddCount > 0 )
    {
      this->m_LastRefreshTime += 7200 * AddCount;
      CWuHunShop::AddRefreshTimes(this, AddCount, 0);
    }
  }
}


#####################################
void __cdecl CWuHunShop::OnSaveToDB(CWuHunShop *const this, PlayerDBData *const dbData)
{
  dbData->m_WuHunShopDBData.m_LastRefreshTime = this->m_LastRefreshTime;
  dbData->m_WuHunShopDBData.m_RefreshTimes = this->m_RefreshTimes;
  std::map<int,WuHunShop>::operator=(&dbData->m_WuHunShopDBData.m_WuHunShopMap, &this->m_WuHunShopMap);
}


#####################################
void __cdecl CWuHunShop::GetInterestsProtocol(CWuHunShop *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 650;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 651;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 652;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CWuHunShop::DispatchNetDatas(CWuHunShop *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x28Bu:
      return CWuHunShop::onBuyShopItem(this, inPacket);
    case 0x28Cu:
      return CWuHunShop::onRefreshShopItems(this, inPacket);
    case 0x28Au:
      return CWuHunShop::onAskShopInfo(this, inPacket);
  }
  return 10002;
}


#####################################
int32_t __cdecl CWuHunShop::onAskShopInfo(CWuHunShop *const this, Answer::NetPacket *inPacket)
{
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > it; // [rsp+10h] [rbp-20h] BYREF
  int32_t ShopId; // [rsp+1Ch] [rbp-14h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  ShopId = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,WuHunShop>::find(&this->m_WuHunShopMap, &ShopId)._M_node;
  __x._M_node = std::map<int,WuHunShop>::end(&this->m_WuHunShopMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator==(&it, &__x)
    && !CWuHunShop::RefreshShop(this, ShopId) )
  {
    return 10002;
  }
  CWuHunShop::sendShopRefreshTimes(this);
  CWuHunShop::sendShopInfo(this, ShopId);
  return 10002;
}


#####################################
int32_t __cdecl CWuHunShop::onBuyShopItem(CWuHunShop *const this, Answer::NetPacket *inPacket)
{
  std::pair<const int,WuHunShop> *v3; // rax
  std::pair<const int,WuHunShop> *v4; // rax
  int32_t v5; // ebx
  CfgData *v6; // rax
  MemChrBag *p_Item; // rbx
  CExtCharBag *Bag; // rax
  std::pair<const int,WuHunShop> *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t ShopId; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > __x; // [rsp+20h] [rbp-30h] BYREF
  int8_t nIndex; // [rsp+37h] [rbp-19h]
  CfgWuHunShop *pCfg; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  ShopId = Answer::NetPacket::readInt32(inPacket);
  nIndex = Answer::NetPacket::readInt8(inPacket);
  it._M_node = std::map<int,WuHunShop>::find(&this->m_WuHunShopMap, &ShopId)._M_node;
  __x._M_node = std::map<int,WuHunShop>::end(&this->m_WuHunShopMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator==(&it, &__x) )
    return 10002;
  if ( (unsigned __int8)nIndex >= 4u )
    return 10002;
  v3 = std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator->(&it);
  if ( v3->second.nState[nIndex] > 0 )
    return 10002;
  v4 = std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator->(&it);
  v5 = v4->second.nIndex[nIndex];
  v6 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetWuHunShopItem(v6, v5);
  if ( !pCfg )
    return 10002;
  if ( pCfg->Const > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_BLOOD,
          pCfg->Const,
          CURRENCY_CHANGE_REASON::GCR_WU_HUN_SHOP_BUY,
          0) )
  {
    return 10002;
  }
  p_Item = &pCfg->Item;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_Item, ITEM_CHANGE_REASON::ICR_WU_HUN_SHOP_BUY) )
    return 10002;
  v9 = std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator->(&it);
  v9->second.nState[nIndex] = 1;
  CWuHunShop::sendShopInfo(this, ShopId);
  return 0;
}


#####################################
int32_t __cdecl CWuHunShop::onRefreshShopItems(CWuHunShop *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > it; // [rsp+10h] [rbp-40h] BYREF
  int32_t ShopId; // [rsp+1Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > __x; // [rsp+20h] [rbp-30h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  ShopId = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<int,WuHunShop>::find(&this->m_WuHunShopMap, &ShopId)._M_node;
  __x._M_node = std::map<int,WuHunShop>::end(&this->m_WuHunShopMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator==(&it, &__x) )
    return 10002;
  if ( this->m_RefreshTimes > 0 )
  {
    CWuHunShop::SubRefreshTimes(this);
  }
  else if ( !Player::DecCurrency(
               this->m_pPlayer,
               CURRENCY_TYPE::CURRENCY_GOLD,
               100,
               CURRENCY_CHANGE_REASON::GCR_WU_HUN_SHOP_REFRESH,
               0) )
  {
    return 10002;
  }
  if ( !CWuHunShop::RefreshShop(this, ShopId) )
    return 10002;
  CWuHunShop::sendShopInfo(this, ShopId);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CWuHunShop::sendShopInfo(CWuHunShop *const this, int32_t ShopId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,WuHunShop> *v4; // rax
  std::pair<const int,WuHunShop> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t ShopIda; // [rsp+4h] [rbp-4Ch] BYREF
  CWuHunShop *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WuHunShop> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t i; // [rsp+3Ch] [rbp-14h]

  thisa = this;
  ShopIda = ShopId;
  if ( this->m_pPlayer )
  {
    it._M_node = std::map<int,WuHunShop>::find(&thisa->m_WuHunShopMap, &ShopIda)._M_node;
    __x._M_node = std::map<int,WuHunShop>::end(&thisa->m_WuHunShopMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator==(&it, &__x) )
    {
      ConnId = Player::getConnId(thisa->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E9Fu);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, ShopIda);
        Answer::NetPacket::writeInt8(packet, 4);
        for ( i = 0; i <= 3; ++i )
        {
          v4 = std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v4->second.nIndex[i]);
          v5 = std::_Rb_tree_iterator<std::pair<int const,WuHunShop>>::operator->(&it);
          Answer::NetPacket::writeInt8(packet, v5->second.nState[i]);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(thisa->m_pPlayer);
        v8 = Player::getConnId(thisa->m_pPlayer);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, v8, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CWuHunShop::sendShopRefreshTimes(CWuHunShop *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EA0u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_RefreshTimes);
      Answer::NetPacket::writeInt32(packet, this->m_LastRefreshTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CWuHunShop::RefreshShop(CWuHunShop *const this, int32_t ShopId)
{
  int32_t v2; // eax
  bool v3; // bl
  CfgWuHunShop *v4; // rax
  Answer::Random *v5; // rax
  CfgWuHunShop *v6; // rax
  WuHunShop *v7; // rbx
  int32_t v8; // r12d
  WuHunShop *v9; // rax
  CfgWuHunShop *v10; // rax
  CfgWuHunShop *v11; // rax
  int32_t ShopIda; // [rsp+4h] [rbp-7Ch] BYREF
  CWuHunShop *thisa; // [rsp+8h] [rbp-78h]
  std::_List_iterator<CfgWuHunShop> it; // [rsp+10h] [rbp-70h] BYREF
  std::_List_iterator<CfgWuHunShop> iter; // [rsp+20h] [rbp-60h] BYREF
  CfgWuHunShopList Items; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<CfgWuHunShop> __x; // [rsp+40h] [rbp-40h] BYREF
  std::_List_iterator<CfgWuHunShop> v19; // [rsp+50h] [rbp-30h] BYREF
  int32_t MaxRand; // [rsp+64h] [rbp-1Ch]
  int32_t i; // [rsp+68h] [rbp-18h]
  int32_t nRand; // [rsp+6Ch] [rbp-14h]

  thisa = this;
  ShopIda = ShopId;
  v2 = (unsigned int)Answer::Singleton<CfgData>::instance();
  CfgData::GetWuHunShopItemList((CfgData *const)&Items, v2);
  if ( std::list<CfgWuHunShop>::size(&Items) > 3 )
  {
    MaxRand = 0;
    for ( iter._M_node = std::list<CfgWuHunShop>::begin(&Items)._M_node;
          ;
          std::_List_iterator<CfgWuHunShop>::operator++(&iter, 0) )
    {
      __x._M_node = std::list<CfgWuHunShop>::end(&Items)._M_node;
      if ( !std::_List_iterator<CfgWuHunShop>::operator!=(&iter, &__x) )
        break;
      v4 = std::_List_iterator<CfgWuHunShop>::operator->(&iter);
      MaxRand += v4->Rate;
    }
    for ( i = 0; i <= 3; ++i )
    {
      if ( MaxRand <= 0 )
      {
        v3 = 0;
        goto LABEL_17;
      }
      v5 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v5, 1, MaxRand);
      for ( it._M_node = std::list<CfgWuHunShop>::begin(&Items)._M_node;
            ;
            std::_List_iterator<CfgWuHunShop>::operator++(&it, 0) )
      {
        v19._M_node = std::list<CfgWuHunShop>::end(&Items)._M_node;
        if ( !std::_List_iterator<CfgWuHunShop>::operator!=(&it, &v19) )
          break;
        v6 = std::_List_iterator<CfgWuHunShop>::operator->(&it);
        if ( v6->Rate >= nRand )
        {
          v7 = std::map<int,WuHunShop>::operator[](&thisa->m_WuHunShopMap, &ShopIda);
          v8 = i;
          v7->nIndex[v8] = std::_List_iterator<CfgWuHunShop>::operator->(&it)->Index;
          v9 = std::map<int,WuHunShop>::operator[](&thisa->m_WuHunShopMap, &ShopIda);
          v9->nState[i] = 0;
          v10 = std::_List_iterator<CfgWuHunShop>::operator->(&it);
          MaxRand -= v10->Rate;
          std::list<CfgWuHunShop>::erase(&Items, it);
          break;
        }
        v11 = std::_List_iterator<CfgWuHunShop>::operator->(&it);
        nRand -= v11->Rate;
      }
    }
    v3 = 1;
  }
  else
  {
    v3 = 0;
  }
LABEL_17:
  std::list<CfgWuHunShop>::~list(&Items);
  return v3;
}


