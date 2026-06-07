// Decompiled methods for class: CExtCharMysteryShop
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl CExtCharMysteryShop::~CExtCharMysteryShop(CExtCharMysteryShop *const this)
{
  CExtCharMysteryShop::~CExtCharMysteryShop(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharMysteryShop::OnLoadFromDB(CExtCharMysteryShop *const this, const PlayerDBData *const dbData)
{
  std::list<MysteryShop>::operator=(&this->m_lstShops, &dbData->m_MysteryShopDBData.lstShop);
}


#####################################
void __cdecl CExtCharMysteryShop::OnSaveToDB(CExtCharMysteryShop *const this, PlayerDBData *const dbData)
{
  std::list<MysteryShop>::operator=(&dbData->m_MysteryShopDBData.lstShop, &this->m_lstShops);
}


#####################################
void __cdecl CExtCharMysteryShop::GetInterestsProtocol(CExtCharMysteryShop *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 880;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 881;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 882;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CExtCharMysteryShop::DispatchNetDatas(
        CExtCharMysteryShop *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharMysteryShop::isFunctionOpen(this) )
    return 10002;
  switch ( nProcId )
  {
    case 0x371u:
      return CExtCharMysteryShop::onBuyShopItem(this, inPacket);
    case 0x372u:
      return CExtCharMysteryShop::onRefreshShopItems(this, inPacket);
    case 0x370u:
      return CExtCharMysteryShop::onAskShopInfo(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharMysteryShop::onAskShopInfo(CExtCharMysteryShop *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  CFestivalDoubleEleven *v4; // rax
  MysteryShop *v5; // rax
  MysteryShop *v6; // rdx
  MysteryShop *v7; // rdx
  std::_List_iterator<MysteryShop> iter; // [rsp+10h] [rbp-40h] BYREF
  MysteryShop shop; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<MysteryShop> __x; // [rsp+40h] [rbp-10h] BYREF
  int8_t nType; // [rsp+4Fh] [rbp-1h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( nType <= 0 || nType > 2 )
    return 10002;
  if ( nType == 1 )
  {
    v3 = Answer::Singleton<CUniteServer>::instance();
    if ( !CUniteServer::IsInMysteryShopTime(v3) )
      return 10002;
  }
  else
  {
    v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( !CFestivalDoubleEleven::IsInTime(v4, FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP) )
      return 10002;
  }
  for ( iter._M_node = std::list<MysteryShop>::begin(&this->m_lstShops)._M_node;
        ;
        std::_List_iterator<MysteryShop>::operator++(&iter) )
  {
    __x._M_node = std::list<MysteryShop>::end(&this->m_lstShops)._M_node;
    if ( !std::_List_iterator<MysteryShop>::operator!=(&iter, &__x) )
      break;
    v5 = std::_List_iterator<MysteryShop>::operator->(&iter);
    if ( v5->nType == nType )
    {
      v6 = std::_List_iterator<MysteryShop>::operator*(&iter);
      CExtCharMysteryShop::checkRefresh(this, v6);
      v7 = std::_List_iterator<MysteryShop>::operator*(&iter);
      CExtCharMysteryShop::sendShopInfo(this, v7);
      return 0;
    }
  }
  memset(&shop.vGoods[1], 0, 20);
  *(_QWORD *)&shop.nType = (unsigned __int8)nType;
  CExtCharMysteryShop::refreshShop(this, &shop, 1);
  CExtCharMysteryShop::sendShopInfo(this, &shop);
  std::list<MysteryShop>::push_back(&this->m_lstShops, &shop);
  return 0;
}


#####################################
int32_t __cdecl CExtCharMysteryShop::onBuyShopItem(CExtCharMysteryShop *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  CFestivalDoubleEleven *v4; // rax
  MysteryShop *v5; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const CfgMysteryShopTable *MysteryShopTable; // rax
  CExtCharBag *Bag; // rax
  ItemData *p_exchange; // rbx
  CExtCharBag *v11; // rax
  int64_t nId; // r12
  int64_t nPrice; // rbx
  CExtCurrency *Currency; // rax
  MemChrBag *p_item; // rbx
  CExtCharBag *v16; // rax
  int32_t v17; // r13d
  CharId_t Cid; // r12
  int64_t v19; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v23; // rax
  std::_List_iterator<MysteryShop> iter; // [rsp+10h] [rbp-70h] BYREF
  std::_List_iterator<MysteryShop> __x; // [rsp+20h] [rbp-60h] BYREF
  std::string name; // [rsp+30h] [rbp-50h] BYREF
  int8_t nType; // [rsp+46h] [rbp-3Ah]
  int8_t nIndex; // [rsp+47h] [rbp-39h]
  MysteryShop *pShop; // [rsp+48h] [rbp-38h]
  int32_t nBuyFlag; // [rsp+54h] [rbp-2Ch]
  const CfgMysteryShop *pCfg; // [rsp+58h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( nType <= 0 || nType > 2 || (unsigned __int8)nIndex >= 4u )
    return 10002;
  if ( nType == 1 )
  {
    v3 = Answer::Singleton<CUniteServer>::instance();
    if ( !CUniteServer::IsInMysteryShopTime(v3) )
      return 10002;
  }
  else
  {
    v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( !CFestivalDoubleEleven::IsInTime(v4, FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP) )
      return 10002;
  }
  for ( iter._M_node = std::list<MysteryShop>::begin(&this->m_lstShops)._M_node;
        ;
        std::_List_iterator<MysteryShop>::operator++(&iter) )
  {
    __x._M_node = std::list<MysteryShop>::end(&this->m_lstShops)._M_node;
    if ( !std::_List_iterator<MysteryShop>::operator!=(&iter, &__x) )
      break;
    v5 = std::_List_iterator<MysteryShop>::operator->(&iter);
    if ( v5->nType == nType )
    {
      pShop = std::_List_iterator<MysteryShop>::operator*(&iter);
      break;
    }
  }
  if ( !pShop )
    return 10002;
  nBuyFlag = pShop->nBuyFlag | (1 << nIndex);
  if ( pShop->nBuyFlag == nBuyFlag )
    return 10002;
  v6 = pShop->vGoods[nIndex];
  v7 = Answer::Singleton<CfgData>::instance();
  MysteryShopTable = CfgData::GetMysteryShopTable(v7);
  pCfg = CfgMysteryShopTable::GetShopGood(MysteryShopTable, v6);
  if ( !pCfg )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 10002;
  if ( pCfg->nCostType == -1 )
  {
    if ( pCfg->exchange.m_nId <= 0 || pCfg->exchange.m_nCount <= 0 )
      return 10002;
    p_exchange = &pCfg->exchange;
    v11 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(v11, p_exchange, ITEM_CHANGE_REASON::ICR_MYSTERY_SHOP_BUY_COST) )
      return 10002;
  }
  else
  {
    if ( pCfg->nPrice <= 0 )
      return 10002;
    if ( pCfg->nCostType )
    {
      if ( !Player::DecCurrency(
              this->m_pPlayer,
              (const CURRENCY_TYPE)pCfg->nCostType,
              pCfg->nPrice,
              CURRENCY_CHANGE_REASON::GCR_MYSTERY_SHOP_BUY,
              pCfg->nId) )
        return 10002;
    }
    else
    {
      nId = pCfg->nId;
      nPrice = pCfg->nPrice;
      Currency = Player::GetCurrency(this->m_pPlayer);
      if ( !CExtCurrency::DecMoneyAndNoBind(Currency, nPrice, CURRENCY_CHANGE_REASON::GCR_MYSTERY_SHOP_BUY, nId) )
        return 10002;
    }
  }
  p_item = &pCfg->item;
  v16 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::AddItem(v16, p_item, ITEM_CHANGE_REASON::ICR_MYSTERY_SHOP_BUY_GET);
  if ( pCfg->nBroad > 0 )
  {
    v17 = pCfg->nId;
    Cid = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)&name);
    CExtCharMysteryShop::broadcastBuyItem(this, pCfg->nBroad, &name, Cid, v17);
    std::string::~string(&name);
  }
  v19 = nIndex;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v23 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v23, ConnId, GateIndex, Proc, v19);
  pShop->nBuyFlag = nBuyFlag;
  if ( nBuyFlag == 15 )
  {
    CExtCharMysteryShop::refreshShop(this, pShop, 1);
    CExtCharMysteryShop::sendShopInfo(this, pShop);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharMysteryShop::onRefreshShopItems(CExtCharMysteryShop *const this, Answer::NetPacket *inPacket)
{
  CUniteServer *v3; // rax
  CFestivalDoubleEleven *v4; // rax
  MysteryShop *v5; // rax
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v7; // rax
  Player *v8; // rbx
  CUniteServer *v9; // rax
  int64_t v10; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  std::_List_iterator<MysteryShop> iter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<MysteryShop> __x; // [rsp+20h] [rbp-40h] BYREF
  int8_t nType; // [rsp+37h] [rbp-29h]
  MysteryShop *pShop; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( nType <= 0 || nType > 2 )
    return 10002;
  if ( nType == 1 )
  {
    v3 = Answer::Singleton<CUniteServer>::instance();
    if ( !CUniteServer::IsInMysteryShopTime(v3) )
      return 10002;
  }
  else
  {
    v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( !CFestivalDoubleEleven::IsInTime(v4, FESTIVAL_ACTIVITY_TYPE::FAT_MYSTERY_SHOP) )
      return 10002;
  }
  for ( iter._M_node = std::list<MysteryShop>::begin(&this->m_lstShops)._M_node;
        ;
        std::_List_iterator<MysteryShop>::operator++(&iter) )
  {
    __x._M_node = std::list<MysteryShop>::end(&this->m_lstShops)._M_node;
    if ( !std::_List_iterator<MysteryShop>::operator!=(&iter, &__x) )
      break;
    v5 = std::_List_iterator<MysteryShop>::operator->(&iter);
    if ( v5->nType == nType )
    {
      pShop = std::_List_iterator<MysteryShop>::operator*(&iter);
      break;
    }
  }
  if ( !pShop )
    return 10002;
  if ( nType == 2 )
  {
    m_pPlayer = this->m_pPlayer;
    v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( !CFestivalDoubleEleven::RefreshMysteryShopItem(v7, m_pPlayer) )
      return 10002;
  }
  else if ( nType == 1 )
  {
    v8 = this->m_pPlayer;
    v9 = Answer::Singleton<CUniteServer>::instance();
    if ( !CUniteServer::RefreshMysteryShopItem(v9, v8) )
      return 10002;
  }
  else if ( !Player::DecCurrency(
               this->m_pPlayer,
               CURRENCY_TYPE::CURRENCY_GOLD,
               20,
               CURRENCY_CHANGE_REASON::GCR_MYSTERY_SHOP_REFRESH,
               nType) )
  {
    return 10002;
  }
  CExtCharMysteryShop::refreshShop(this, pShop, 0);
  CExtCharMysteryShop::sendShopInfo(this, pShop);
  v10 = nType;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v14, ConnId, GateIndex, Proc, v10);
  return 0;
}


#####################################
void __cdecl CExtCharMysteryShop::sendShopInfo(CExtCharMysteryShop *const this, const MysteryShop *const shop)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t NextRefreshTime; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EA4u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, shop->nType);
      NextRefreshTime = CExtCharMysteryShop::getNextRefreshTime(this, shop->nAutoRefreshTime);
      Answer::NetPacket::writeInt32(packet, NextRefreshTime);
      for ( i = 0; i <= 3; ++i )
      {
        Answer::NetPacket::writeInt32(packet, shop->vGoods[i]);
        Answer::NetPacket::writeInt8(packet, ((1 << i) & shop->nBuyFlag) >> i);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtCharMysteryShop::checkRefresh(CExtCharMysteryShop *const this, MysteryShop *const shop)
{
  if ( this->m_pPlayer )
  {
    if ( shop->nAutoRefreshTime / 7200 != Unit::getNow(this->m_pPlayer) / 7200 )
      CExtCharMysteryShop::refreshShop(this, shop, 1);
  }
}


#####################################
void __cdecl CExtCharMysteryShop::refreshShop(CExtCharMysteryShop *const this, MysteryShop *const shop, bool bAuto)
{
  int32_t v3; // edx
  int32_t nGoodsId; // [rsp+2Ch] [rbp-34h] BYREF
  Int32List excepts; // [rsp+30h] [rbp-30h] BYREF
  int32_t i; // [rsp+4Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    shop->nBuyFlag = 0;
    std::list<int>::list(&excepts);
    for ( i = 0; i <= 3; ++i )
    {
      v3 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      nGoodsId = CExtCharMysteryShop::refreshShopItem(this, shop->nType, v3, &excepts);
      shop->vGoods[i] = nGoodsId;
      std::list<int>::push_back(&excepts, &nGoodsId);
    }
    if ( bAuto )
      shop->nAutoRefreshTime = Unit::getNow(this->m_pPlayer);
    std::list<int>::~list(&excepts);
  }
}


#####################################
int32_t __cdecl CExtCharMysteryShop::refreshShopItem(
        CExtCharMysteryShop *const this,
        int8_t nType,
        int32_t nLevel,
        const Int32List *const excepts)
{
  CfgData *v4; // rax
  int8_t MysteryShopTable; // al
  CfgMysteryShop *v6; // r12
  const std::_List_node_base *M_node; // rbx
  std::_List_const_iterator<int> v8; // rax
  CfgMysteryShop *v9; // rax
  CfgMysteryShop *v10; // rax
  int32_t nId; // ebx
  Answer::Random *v12; // rax
  CfgMysteryShop *v13; // rax
  CfgMysteryShop *v14; // rax
  std::_List_iterator<CfgMysteryShop> iter_0; // [rsp+20h] [rbp-90h] BYREF
  std::_List_iterator<CfgMysteryShop> iter; // [rsp+30h] [rbp-80h] BYREF
  CfgMysteryShopList newlist; // [rsp+40h] [rbp-70h] BYREF
  CfgMysteryShopList tlist; // [rsp+50h] [rbp-60h] BYREF
  std::_List_iterator<CfgMysteryShop> v21; // [rsp+60h] [rbp-50h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+70h] [rbp-40h] BYREF
  std::_List_const_iterator<int> v23; // [rsp+80h] [rbp-30h] BYREF
  std::_List_iterator<CfgMysteryShop> v24; // [rsp+90h] [rbp-20h] BYREF
  int32_t nMaxRate; // [rsp+98h] [rbp-18h]
  int32_t nRand; // [rsp+9Ch] [rbp-14h]

  nMaxRate = 0;
  v4 = Answer::Singleton<CfgData>::instance();
  MysteryShopTable = (unsigned __int8)CfgData::GetMysteryShopTable(v4);
  CfgMysteryShopTable::GetShopList((const CfgMysteryShopTable *const)&tlist, MysteryShopTable, nType);
  std::list<CfgMysteryShop>::list(&newlist);
  for ( iter._M_node = std::list<CfgMysteryShop>::begin(&tlist)._M_node;
        ;
        std::_List_iterator<CfgMysteryShop>::operator++(&iter) )
  {
    v21._M_node = std::list<CfgMysteryShop>::end(&tlist)._M_node;
    if ( !std::_List_iterator<CfgMysteryShop>::operator!=(&iter, &v21) )
      break;
    __x._M_node = std::list<int>::end(excepts)._M_node;
    v6 = std::_List_iterator<CfgMysteryShop>::operator->(&iter);
    M_node = std::list<int>::end(excepts)._M_node;
    v8._M_node = std::list<int>::begin(excepts)._M_node;
    v23._M_node = std::find<std::_List_const_iterator<int>,int>(v8, (std::_List_const_iterator<int>)M_node, &v6->nId)._M_node;
    if ( !std::_List_const_iterator<int>::operator!=(&v23, &__x) )
    {
      v9 = std::_List_iterator<CfgMysteryShop>::operator*(&iter);
      std::list<CfgMysteryShop>::push_back(&newlist, v9);
      v10 = std::_List_iterator<CfgMysteryShop>::operator->(&iter);
      nMaxRate += v10->nRate;
    }
  }
  if ( nMaxRate )
  {
    v12 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v12, 1, nMaxRate);
    for ( iter_0._M_node = std::list<CfgMysteryShop>::begin(&newlist)._M_node;
          ;
          std::_List_iterator<CfgMysteryShop>::operator++(&iter_0) )
    {
      v24._M_node = std::list<CfgMysteryShop>::end(&newlist)._M_node;
      if ( !std::_List_iterator<CfgMysteryShop>::operator!=(&iter_0, &v24) )
        break;
      v13 = std::_List_iterator<CfgMysteryShop>::operator->(&iter_0);
      if ( v13->nRate >= nRand )
      {
        nId = std::_List_iterator<CfgMysteryShop>::operator->(&iter_0)->nId;
        goto LABEL_14;
      }
      v14 = std::_List_iterator<CfgMysteryShop>::operator->(&iter_0);
      nRand -= v14->nRate;
    }
    nId = 0;
  }
  else
  {
    nId = 0;
  }
LABEL_14:
  std::list<CfgMysteryShop>::~list(&newlist);
  std::list<CfgMysteryShop>::~list(&tlist);
  return nId;
}


#####################################
int32_t __cdecl CExtCharMysteryShop::getNextRefreshTime(CExtCharMysteryShop *const this, int32_t nLastTime)
{
  return 7200 * (nLastTime / 7200 + 1);
}


#####################################
void __cdecl CExtCharMysteryShop::broadcastBuyItem(
        CExtCharMysteryShop *const this,
        int32_t broad,
        const std::string *const name,
        CharId_t cid,
        int32_t id)
{
  int8_t ConnId; // bl
  GameService *v6; // rax
  uint32_t WOffset; // edx
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, broad);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    Answer::NetPacket::writeInt32(packet, id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v9, v8, packet);
  }
}


