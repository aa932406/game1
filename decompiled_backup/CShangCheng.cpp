// Decompiled methods for class: CShangCheng
// Source: gameserver.cc
// Total methods: 20

#####################################
void __cdecl CShangCheng::~CShangCheng(CShangCheng *const this)
{
  CShangCheng::~CShangCheng(this);
  operator delete(this);
}


#####################################
void __cdecl CShangCheng::OnLoadFromDB(CShangCheng *const this, const PlayerDBData *const dbData)
{
  std::map<int,int>::operator=(&this->m_LiMitMap, &dbData->m_ShangChengData.m_LiMitMap);
}


#####################################
void __cdecl CShangCheng::OnSaveToDB(CShangCheng *const this, PlayerDBData *const dbData)
{
  std::map<int,int>::operator=(&dbData->m_ShangChengData.m_LiMitMap, &this->m_LiMitMap);
}


#####################################
void __cdecl CShangCheng::GetInterestsProtocol(CShangCheng *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 433;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 434;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 20084;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CShangCheng::DispatchNetDatas(CShangCheng *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x1B2u:
      return CShangCheng::OnBuyShopItem(this, inPacket);
    case 0x4E74u:
      return CShangCheng::OnBuyGameLimitItem(this, inPacket);
    case 0x1B1u:
      return CShangCheng::OnAskLimitInfo(this, inPacket);
  }
  return 2;
}


#####################################
void __cdecl CShangCheng::OnDaySwitch(CShangCheng *const this, int32_t nDiffDays)
{
  std::map<int,int>::clear(&this->m_LiMitMap);
  CShangCheng::SendResetLimitInfo(this);
}


#####################################
void __cdecl CShangCheng::SendResetLimitInfo(CShangCheng *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D05u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 0);
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
int32_t __cdecl CShangCheng::BuyShopItem(CShangCheng *const this, int32_t ShopId, int32_t ItemCount, bool AddBag)
{
  CfgData *v4; // rax
  int8_t VipLevelLimit; // bl
  CVip *PlayerVip; // rax
  int8_t v8; // r12
  int32_t v9; // ebx
  CfgData *v10; // rax
  CKunExt *CKunExt; // rax
  CMingGeExt *CMingGeExt; // rax
  CExtCharBag *Bag; // rax
  int32_t Time; // r12d
  int64_t LeftGold; // rbx
  int32_t ItemClass; // r15d
  CharId_t Cid; // r14
  int8_t ConnId; // r13
  DBService *v19; // rax
  int32_t MapId; // r12d
  int v21; // r13d
  int32_t v22; // r15d
  int64_t Currency; // rax
  DBService *v24; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  int32_t Now; // r12d
  int64_t v27; // rbx
  int32_t v28; // r15d
  CharId_t v29; // r14
  int8_t v30; // r13
  DBService *v31; // rax
  int32_t v32; // r12d
  int v33; // r13d
  int32_t v34; // r15d
  int64_t v35; // rax
  DBService *v36; // rax
  CExtCurrency *v37; // rax
  int64_t v38; // r12
  int64_t v39; // rbx
  CExtCurrency *v40; // rax
  int32_t v41; // r12d
  CExtCurrency *v42; // rax
  int64_t MoneyBindAndNoBind; // rbx
  int32_t v44; // r15d
  CharId_t v45; // r14
  int8_t v46; // r13
  DBService *v47; // rax
  CExtCharBag *v48; // rax
  CharId_t v49; // rbx
  unsigned int v50; // eax
  CExtCharBag *v51; // rax
  int64_t v52; // r13
  int16_t GateIndex; // r12
  int8_t v54; // bl
  GameService *v55; // rax
  CharId_t v56; // r12
  int CostGold; // [rsp+38h] [rbp-1128h]
  int32_t ItemId; // [rsp+3Ch] [rbp-1124h]
  int32_t v59; // [rsp+40h] [rbp-1120h]
  int v60; // [rsp+44h] [rbp-111Ch]
  int32_t v61; // [rsp+48h] [rbp-1118h]
  int32_t v62; // [rsp+4Ch] [rbp-1114h]
  int v63; // [rsp+50h] [rbp-1110h]
  int32_t v64; // [rsp+54h] [rbp-110Ch]
  int32_t v65; // [rsp+58h] [rbp-1108h]
  char LogString[4096]; // [rsp+70h] [rbp-10F0h] BYREF
  MemChrBag Item; // [rsp+1070h] [rbp-F0h] BYREF
  CharId_t v70; // [rsp+1090h] [rbp-D0h]
  MemChrBagVector items; // [rsp+10A0h] [rbp-C0h] BYREF
  std::string name; // [rsp+10C0h] [rbp-A0h] BYREF
  _BYTE v73[16]; // [rsp+10D0h] [rbp-90h] BYREF
  std::string v74; // [rsp+10E0h] [rbp-80h] BYREF
  _BYTE v75[16]; // [rsp+10F0h] [rbp-70h] BYREF
  std::string v76; // [rsp+1100h] [rbp-60h] BYREF
  std::string v77; // [rsp+1110h] [rbp-50h] BYREF
  CfgGameShop *pShangCheng; // [rsp+1120h] [rbp-40h]
  int32_t nLayNum; // [rsp+112Ch] [rbp-34h]

  v4 = Answer::Singleton<CfgData>::instance();
  pShangCheng = CfgData::GetGameShop(v4, ShopId);
  if ( !pShangCheng )
    return 2;
  VipLevelLimit = pShangCheng->VipLevelLimit;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( VipLevelLimit > CVip::GetVipLevel(PlayerVip) )
    return 2;
  if ( pShangCheng->LimitType == 2 )
  {
    CShangCheng::SendSocialBuyLimitItem(this, ShopId, ItemCount);
    return 2;
  }
  if ( CShangCheng::IsLimited(this, pShangCheng, ItemCount) )
    return 2;
  if ( pShangCheng->Price <= 0 )
    return 2;
  v8 = pShangCheng->ItemClass;
  v9 = pShangCheng->ItemId;
  v10 = Answer::Singleton<CfgData>::instance();
  nLayNum = CfgData::getOverlay(v10, v9, v8);
  if ( ItemCount > nLayNum )
    return 2;
  if ( AddBag )
  {
    if ( pShangCheng->ItemClass == 11 )
    {
      CKunExt = Player::GetCKunExt(this->m_pPlayer);
      if ( CKunExt::GetEmptyBagCount(CKunExt) <= 0 )
        return 0;
    }
    else if ( pShangCheng->ItemClass == 10 )
    {
      CMingGeExt = Player::GetCMingGeExt(this->m_pPlayer);
      if ( CMingGeExt::GetBagFreeSlotCount(CMingGeExt, 1) <= 0 )
      {
        Player::TiShiInfo(this->m_pPlayer, 3, 0);
        return 0;
      }
    }
    else
    {
      Bag = Player::GetBag(this->m_pPlayer);
      if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
        return 2;
    }
  }
  if ( pShangCheng->CostType == 2 )
  {
    if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH) < ItemCount * pShangCheng->Price )
      return 2;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_CASH,
            ItemCount * pShangCheng->Price,
            CURRENCY_CHANGE_REASON::GCC_BUY_SHANG_CHENG_ITEM,
            pShangCheng->ShopId) )
      return 2;
    Time = Unit::getNow(this->m_pPlayer);
    LeftGold = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH);
    CostGold = ItemCount * pShangCheng->Price;
    ItemId = pShangCheng->ItemId;
    ItemClass = pShangCheng->ItemClass;
    v59 = pShangCheng->ShopId;
    Player::getName((const Player *const)&name);
    Cid = Player::getCid(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v19 = Answer::Singleton<DBService>::instance();
    DBService::logShangCheng(v19, ConnId, Cid, &name, 2, v59, ItemClass, ItemId, ItemCount, CostGold, LeftGold, Time);
    std::string::~string(&name);
    memset(&Item, 0, sizeof(Item));
    v70 = 0;
    std::string::string((std::string *)&Item);
    std::string::string((std::string *)&Item.endTime);
    std::string::string((std::string *)&Item.srcId);
    std::string::operator=(&Item, "giftmoney_buy");
    Item.itemCount = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v73);
    std::string::operator=(&Item.endTime, v73);
    std::string::~string(v73);
    v70 = Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    MapId = StaticObj::getMapId(this->m_pPlayer);
    LODWORD(LeftGold) = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v21 = ItemCount * pShangCheng->Price;
    v22 = pShangCheng->ItemId;
    LODWORD(Cid) = pShangCheng->ItemClass;
    Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH);
    snprintf(
      LogString,
      0xFFFu,
      "balance=%lld&itemid=%d:%d&amount=%d&money=%d&level=%d&map_id=%d",
      Currency,
      Cid,
      v22,
      ItemCount,
      v21,
      LeftGold,
      MapId);
    std::string::operator=(&Item.srcId, LogString);
    LOBYTE(LeftGold) = Player::getConnId(this->m_pPlayer);
    v24 = Answer::Singleton<DBService>::instance();
    DBService::log360(v24, LeftGold, (Log360 *const)&Item);
    Log360::~Log360((Log360 *const)&Item);
  }
  else if ( pShangCheng->CostType == 1 )
  {
    if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < ItemCount * pShangCheng->Price )
      return 2;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            ItemCount * pShangCheng->Price,
            CURRENCY_CHANGE_REASON::GCR_BUY_SHANG_CHENG_ITEM,
            pShangCheng->ShopId) )
      return 2;
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 11, 0, 0);
    Now = Unit::getNow(this->m_pPlayer);
    v27 = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
    v60 = ItemCount * pShangCheng->Price;
    v61 = pShangCheng->ItemId;
    v28 = pShangCheng->ItemClass;
    v62 = pShangCheng->ShopId;
    Player::getName((const Player *const)&v74);
    v29 = Player::getCid(this->m_pPlayer);
    v30 = Player::getConnId(this->m_pPlayer);
    v31 = Answer::Singleton<DBService>::instance();
    DBService::logShangCheng(v31, v30, v29, &v74, 1, v62, v28, v61, ItemCount, v60, v27, Now);
    std::string::~string(&v74);
    memset(&Item, 0, sizeof(Item));
    v70 = 0;
    std::string::string((std::string *)&Item);
    std::string::string((std::string *)&Item.endTime);
    std::string::string((std::string *)&Item.srcId);
    std::string::operator=(&Item, "shop_buy");
    Item.itemCount = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v75);
    std::string::operator=(&Item.endTime, v75);
    std::string::~string(v75);
    v70 = Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    v32 = StaticObj::getMapId(this->m_pPlayer);
    LODWORD(v27) = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v33 = ItemCount * pShangCheng->Price;
    v34 = pShangCheng->ItemId;
    LODWORD(v29) = pShangCheng->ItemClass;
    v35 = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
    snprintf(
      LogString,
      0xFFFu,
      "balance=%lld&itemid=%d:%d&amount=%d&money=%d&level=%d&remain=&map_id=%d&type=0",
      v35,
      v29,
      v34,
      ItemCount,
      v33,
      v27,
      v32);
    std::string::operator=(&Item.srcId, LogString);
    LOBYTE(v27) = Player::getConnId(this->m_pPlayer);
    v36 = Answer::Singleton<DBService>::instance();
    DBService::log360(v36, v27, (Log360 *const)&Item);
    Log360::~Log360((Log360 *const)&Item);
  }
  else
  {
    if ( pShangCheng->CostType )
      return 10002;
    v37 = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(v37) < ItemCount * pShangCheng->Price )
      return 2;
    v38 = pShangCheng->ShopId;
    v39 = ItemCount * pShangCheng->Price;
    v40 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v40, v39, CURRENCY_CHANGE_REASON::GCR_BUY_SHANG_CHENG_ITEM, v38) )
      return 2;
    v41 = Unit::getNow(this->m_pPlayer);
    v42 = Player::GetCurrency(this->m_pPlayer);
    MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(v42);
    v63 = ItemCount * pShangCheng->Price;
    v64 = pShangCheng->ItemId;
    v44 = pShangCheng->ItemClass;
    v65 = pShangCheng->ShopId;
    Player::getName((const Player *const)&v76);
    v45 = Player::getCid(this->m_pPlayer);
    v46 = Player::getConnId(this->m_pPlayer);
    v47 = Answer::Singleton<DBService>::instance();
    DBService::logShangCheng(v47, v46, v45, &v76, 0, v65, v44, v64, ItemCount, v63, MoneyBindAndNoBind, v41);
    std::string::~string(&v76);
  }
  if ( AddBag )
  {
    memset(&Item, 0, sizeof(Item));
    Item.itemClass = pShangCheng->ItemClass;
    Item.itemCount = ItemCount;
    Item.bind = pShangCheng->ItemBind;
    Item.itemId = pShangCheng->ItemId;
    std::vector<MemChrBag>::vector(&items);
    std::vector<MemChrBag>::push_back(&items, &Item);
    v48 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItemsAndMingGe(v48, &items, ITEM_CHANGE_REASON::ICR_BUY_SHANG_CHENG_ITEM) )
    {
      v49 = Player::getCid(this->m_pPlayer);
      v50 = Unit::getNow(this->m_pPlayer);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        &byte_8F0660,
        (unsigned int)pShangCheng->ItemClass,
        (unsigned int)pShangCheng->ItemId,
        (unsigned int)ItemCount,
        v50,
        v49);
    }
    v51 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::ForceSendDirty(v51);
    v52 = pShangCheng->ShopId;
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v54 = Player::getConnId(this->m_pPlayer);
    v55 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v55, v54, GateIndex, 0x1B2u, v52);
    std::vector<MemChrBag>::~vector(&items);
  }
  if ( pShangCheng->LimitType == 1 )
  {
    CShangCheng::AddLimitCount(this, pShangCheng->ShopId, ItemCount);
    CShangCheng::SendItemLimitChange(this, pShangCheng->ShopId);
  }
  if ( pShangCheng->BroadcastId > 0 )
  {
    v56 = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)&v77);
    CShangCheng::broadcastBuyShopItem(this, pShangCheng->BroadcastId, &v77, v56, ShopId, ItemCount);
    std::string::~string(&v77);
  }
  return 0;
}


#####################################
int32_t __cdecl CShangCheng::OnBuyShopItem(CShangCheng *const this, Answer::NetPacket *inPacket)
{
  int32_t Int32; // edx
  int32_t ShopId; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  ShopId = Answer::NetPacket::readInt32(inPacket);
  Int32 = Answer::NetPacket::readInt32(inPacket);
  return CShangCheng::BuyShopItem(this, ShopId, Int32, 1);
}


#####################################
int32_t __cdecl CShangCheng::OnAskLimitInfo(CShangCheng *const this, Answer::NetPacket *inPacket)
{
  CShangCheng::SendLimitInfo(this);
  CShangCheng::SendSocialAskLimitInfo(this);
  return 0;
}


#####################################
void __cdecl CShangCheng::SendItemLimitChange(CShangCheng *const this, int32_t ShopId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t ShopIda; // [rsp+4h] [rbp-3Ch] BYREF
  CShangCheng *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  ShopIda = ShopId;
  it._M_node = std::map<int,int>::find(&this->m_LiMitMap, &ShopIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_LiMitMap)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
  {
    ConnId = Player::getConnId(thisa->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CAFu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v4->first);
      v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v5->second);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(thisa->m_pPlayer);
      v8 = Player::getConnId(thisa->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CShangCheng::OnBuyGameLimitItem(CShangCheng *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int8_t ItemClass; // r12
  int32_t ItemId; // ebx
  CfgData *v6; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v8; // rax
  CharId_t Cid; // rbx
  unsigned int Now; // eax
  int64_t v11; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  CharId_t v15; // r12
  MemChrBag Item; // [rsp+20h] [rbp-80h] BYREF
  MemChrBagVector items; // [rsp+40h] [rbp-60h] BYREF
  std::string name; // [rsp+60h] [rbp-40h] BYREF
  int32_t ShopId; // [rsp+68h] [rbp-38h]
  int32_t ItemCount; // [rsp+6Ch] [rbp-34h]
  CfgGameShop *pShangCheng; // [rsp+70h] [rbp-30h]
  int32_t nLayNum; // [rsp+7Ch] [rbp-24h]

  if ( !inPacket )
    return 2;
  ShopId = Answer::NetPacket::readInt32(inPacket);
  ItemCount = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pShangCheng = CfgData::GetGameShop(v3, ShopId);
  if ( !pShangCheng )
    return 2;
  if ( ItemCount <= 0 )
    return 2;
  ItemClass = pShangCheng->ItemClass;
  ItemId = pShangCheng->ItemId;
  v6 = Answer::Singleton<CfgData>::instance();
  nLayNum = CfgData::getOverlay(v6, ItemId, ItemClass);
  if ( ItemCount > nLayNum )
    return 2;
  if ( pShangCheng->LimitType != 2 )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < ItemCount * pShangCheng->Price )
    return 2;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          ItemCount * pShangCheng->Price,
          CURRENCY_CHANGE_REASON::GCR_BUY_SHANG_CHENG_ITEM,
          pShangCheng->ShopId) )
    return 2;
  memset(&Item, 0, sizeof(Item));
  Item.itemClass = pShangCheng->ItemClass;
  Item.itemCount = ItemCount;
  Item.bind = pShangCheng->ItemBind;
  Item.itemId = pShangCheng->ItemId;
  std::vector<MemChrBag>::vector(&items);
  std::vector<MemChrBag>::push_back(&items, &Item);
  v8 = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItemsAndMingGe(v8, &items, ITEM_CHANGE_REASON::ICR_BUY_SHANG_CHENG_ITEM) )
  {
    Cid = Player::getCid(this->m_pPlayer);
    Now = Unit::getNow(this->m_pPlayer);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      &byte_8F0660,
      (unsigned int)pShangCheng->ItemClass,
      (unsigned int)pShangCheng->ItemId,
      (unsigned int)ItemCount,
      Now,
      Cid);
  }
  CShangCheng::SendBuyItemSucceed(this, ShopId, ItemCount);
  v11 = pShangCheng->ShopId;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v14, ConnId, GateIndex, 0x1B2u, v11);
  if ( pShangCheng->BroadcastId > 0 )
  {
    v15 = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)&name);
    CShangCheng::broadcastBuyShopItem(this, pShangCheng->BroadcastId, &name, v15, ShopId, ItemCount);
    std::string::~string(&name);
  }
  v2 = 0;
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
void __cdecl CShangCheng::SendBuyItemSucceed(CShangCheng *const this, int32_t ShopId, int32_t AddCount)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *Packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  Packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EB4u);
  if ( Packet )
  {
    if ( this->m_pPlayer )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(Packet, GateIndex);
      Answer::NetPacket::writeInt32(Packet, ShopId);
      Answer::NetPacket::writeInt32(Packet, AddCount);
      WOffset = Answer::NetPacket::getWOffset(Packet);
      Answer::NetPacket::setSize(Packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v8, v7, Packet);
    }
  }
}


#####################################
int32_t __cdecl CShangCheng::GetLimitCount(CShangCheng *const this, int32_t ShopId)
{
  int32_t ShopIda; // [rsp+4h] [rbp-2Ch] BYREF
  CShangCheng *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  ShopIda = ShopId;
  it._M_node = std::map<int,int>::find(&this->m_LiMitMap, &ShopIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_LiMitMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
void __cdecl CShangCheng::SendLimitInfo(CShangCheng *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CAFu);
    if ( packet )
    {
      nSize = std::map<int,int>::size(&this->m_LiMitMap);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_LiMitMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_LiMitMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
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
void __cdecl CShangCheng::AddLimitCount(CShangCheng *const this, int32_t ShopId, int32_t AddCount)
{
  int *v3; // rax
  int32_t ShopIda; // [rsp+4h] [rbp-2Ch] BYREF
  CShangCheng *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  ShopIda = ShopId;
  if ( ShopId > 0 && AddCount > 0 )
  {
    it._M_node = std::map<int,int>::find(&thisa->m_LiMitMap, &ShopIda)._M_node;
    __x._M_node = std::map<int,int>::end(&thisa->m_LiMitMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    {
      v3 = std::map<int,int>::operator[](&thisa->m_LiMitMap, &ShopIda);
      *v3 += AddCount;
    }
    else
    {
      *std::map<int,int>::operator[](&thisa->m_LiMitMap, &ShopIda) = AddCount;
    }
  }
}


#####################################
bool __cdecl CShangCheng::IsLimited(CShangCheng *const this, CfgGameShop *pShangCheng, int32_t ItemCount)
{
  int32_t LimitType; // eax
  int32_t TimeNow; // [rsp+2Ch] [rbp-4h]

  if ( !pShangCheng || ItemCount <= 0 || !this->m_pPlayer )
    return 1;
  LimitType = pShangCheng->LimitType;
  if ( LimitType == 1 )
    return ItemCount + CShangCheng::GetLimitCount(this, pShangCheng->ShopId) > pShangCheng->LimitCount;
  if ( LimitType != 3 )
    return LimitType != 0;
  TimeNow = Unit::getNow(this->m_pPlayer);
  return pShangCheng->LimitStartTime >= TimeNow || pShangCheng->LimitEndTime <= TimeNow;
}


#####################################
void __cdecl CShangCheng::SendSocialBuyLimitItem(CShangCheng *const this, int32_t ShopId, int32_t Count)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *Packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  Packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EB3u);
  if ( Packet )
  {
    if ( this->m_pPlayer )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(Packet, GateIndex);
      Answer::NetPacket::writeInt32(Packet, ShopId);
      Answer::NetPacket::writeInt32(Packet, Count);
      WOffset = Answer::NetPacket::getWOffset(Packet);
      Answer::NetPacket::setSize(Packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v8, v7, Packet);
    }
  }
}


#####################################
void __cdecl CShangCheng::SendSocialAskLimitInfo(CShangCheng *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *Packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  Packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EB2u);
  if ( Packet )
  {
    if ( this->m_pPlayer )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(Packet, GateIndex);
      Answer::NetPacket::writeInt8(Packet, 0);
      WOffset = Answer::NetPacket::getWOffset(Packet);
      Answer::NetPacket::setSize(Packet, WOffset);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v6, v5, Packet);
    }
  }
}


#####################################
void __cdecl CShangCheng::broadcastBuyShopItem(
        CShangCheng *const this,
        int32_t BroadcastId,
        const std::string *const name,
        CharId_t CharId,
        int32_t ShopId,
        int32_t ItemCount)
{
  int8_t ConnId; // bl
  GameService *v7; // rax
  uint32_t WOffset; // edx
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, BroadcastId);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, CharId);
    Answer::NetPacket::writeInt32(packet, ShopId);
    Answer::NetPacket::writeInt32(packet, ItemCount);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v9 = Player::getConnId(this->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v10, v9, packet);
  }
}


