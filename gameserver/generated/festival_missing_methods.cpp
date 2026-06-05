// ============ Auto-generated missing method implementations ============
void CFestivalDoubleEleven::OnRecharge(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t OldValue,
        int32_t AddValue)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v7; // rax
  bool NeedSendIcon; // [rsp+2Fh] [rbp-11h]

  if ( player )
  {
    NeedSendIcon = 0;
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_LIAN_CHONG) )
    {
      if ( std::vector<LianRechargeCfg>::operator[](&m_LianRechargeCfgVt, 0)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&m_LianRechargeCfgVt, 0)->nValues )
      {
        OperateLimit = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1634, 1);
        NeedSendIcon = 1;
      }
      if ( std::vector<LianRechargeCfg>::operator[](&m_LianRechargeCfgVt, 1u)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&m_LianRechargeCfgVt, 1u)->nValues )
      {
        v7 = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(v7, 1635, 1);
        NeedSendIcon = 1;
      }
    }
    if ( NeedSendIcon )
      SendIconState(, player);
  }
}



bool CFestivalDoubleEleven::CheckDropGroup(int32_t nDropGroup)
{
  return IsInTime() && m_nDropGroup == nDropGroup;
}



int32_t CFestivalDoubleEleven::GetLandGift(Player *player)
{
  std::vector<MemChrBag> *v4; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax
  int nIndex; // [rsp+1Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !canGetLandGift(, player) )
    return 10002;
  nIndex = m_nDay;
  if ( m_nDay < 0 || (int)std::vector<std::vector<MemChrBag>>::size(&m_vLandGift) <= nIndex )
    return 10002;
  v4 = std::vector<std::vector<MemChrBag>>::operator[](&m_vLandGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v4, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_LAND_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(OperateLimit, 2030, 1);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetLandSumGift(Player *player, int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int32_t nOldRecord; // [rsp+28h] [rbp-18h]
  int nNewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM) )
    return 10002;
  if ( nIndex < 0 || nIndex >= getLandSum(, player) )
    return 10002;
  if ( nIndex < 0 || nIndex >= (int)std::vector<std::vector<MemChrBag>>::size(&m_vLandSumGift) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1614);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&m_vLandSumGift, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_LAND_SUM_GIFT) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1614, nNewRecord);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetDrawGift(Player *player)
{
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 10002;
  if ( !canGetDrawGift(, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &m_vDrawLoopReward, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_GRAW_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 1602, 1);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetOnlineGift(Player *player)
{
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 10002;
  if ( !canGetOnlineGift(, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &m_vOnlineReward, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_ONLINE_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 2037, 1);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GouWuChe(
        CFestivalDoubleEleven * this,
        Player *player,
        Int32List *p_nIndexList)
{
  int32_t v3; // ebx
  int *v5; // rax
  int *v6; // rax
  int *v7; // rax
  int *v8; // rax
  MemChrBag *v9; // rax
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // eax
  CExtCharBag *v13; // rax
  std::_List_iterator<int> it; // [rsp+20h] [rbp-60h] BYREF
  MemChrBagVector items; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<int> __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t OldRecord; // [rsp+5Ch] [rbp-24h]
  int32_t nNewRecord; // [rsp+60h] [rbp-20h]
  int32_t PriceSum; // [rsp+64h] [rbp-1Ch]
  int32_t nSize; // [rsp+68h] [rbp-18h]
  int32_t Rate; // [rsp+6Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_GOU_WU_CHE) )
    return 10002;
  OldRecord = Player::getRecord(player, 2112);
  nNewRecord = 0;
  PriceSum = 0;
  std::vector<MemChrBag>::vector(&items);
  for ( it._M_node = std::list<int>::begin(p_nIndexList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
  {
    __x._M_node = std::list<int>::end(p_nIndexList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    if ( *std::_List_iterator<int>::operator*(&it) < 0
      && *std::_List_iterator<int>::operator*(&it) >= m_nGouWuCheSize )
    {
      v3 = 10002;
      goto LABEL_35;
    }
    v5 = std::_List_iterator<int>::operator*(&it);
    nNewRecord = OldRecord | (1 << *v5);
    if ( nNewRecord == OldRecord )
    {
      v3 = 10002;
      goto LABEL_35;
    }
    v6 = std::_List_iterator<int>::operator*(&it);
    v7 = std::vector<int>::operator[](&m_vGouWuCheGiftPrice, *v6);
    PriceSum += *v7;
    v8 = std::_List_iterator<int>::operator*(&it);
    v9 = std::vector<MemChrBag>::operator[](&m_vGouWuCheItem, *v8);
    std::vector<MemChrBag>::push_back(&items, v9);
    OldRecord = nNewRecord;
  }
  if ( PriceSum <= 0 || (int)std::vector<MemChrBag>::size(&items) <= 0 )
  {
    v3 = 10002;
  }
  else
  {
    nSize = std::list<int>::size(p_nIndexList);
    Bag = Player::GetBag(player);
    FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
    if ( FreeSlotCount >= nSize )
    {
      Rate = 0;
      switch ( nSize )
      {
        case 1:
          Rate = 9;
          break;
        case 2:
          Rate = 8;
          break;
        case 3:
          Rate = 7;
          break;
        case 4:
          Rate = 6;
          break;
        case 5:
          Rate = 5;
          break;
        default:
          break;
      }
      if ( Rate )
      {
        if ( !Player::DecCurrency(
                player,
                CURRENCY_TYPE::CURRENCY_GOLD,
                Rate * PriceSum / 10,
                CURRENCY_CHANGE_REASON::GCR_GOU_WU_CHE,
                0) )
        {
          v3 = 10002;
        }
        else
        {
          Player::updateRecord(player, 2112, nNewRecord);
          v13 = Player::GetBag(player);
          CExtCharBag::AddItemsAndMingGe(v13, &items, ITEM_CHANGE_REASON::IDCR_GOU_WU_CHE);
          v3 = 0;
        }
      }
      else
      {
        v3 = 10002;
      }
    }
    else
    {
      v3 = 10002;
    }
  }

  std::vector<MemChrBag>::~vector(&items);
  return v3;
}



int32_t CFestivalDoubleEleven::GetWishGift(Player *player)
{
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 10002;
  if ( !canGetWishGift(, player) )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &m_vWishReward, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_WISH_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(OperateLimit, 2038, 1);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::BuyDailyLimitShopItem(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v5; // rax

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 2034) >= m_nDailyLimitShopLimit )
    return 10002;
  if ( Player::GetCurrency(player, (const CURRENCY_TYPE)m_nDailyLimitShopCostType) < m_nDailyLimitShopCostValue )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &m_vDailyLimitShopItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_LIMIT) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          (const CURRENCY_TYPE)m_nDailyLimitShopCostType,
          m_nDailyLimitShopCostValue,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_LIMIT_SHOP,
          0) )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(v5, 2034, 1);
  return 0;
}



bool CFestivalDoubleEleven::BuyTitle(Player *player)
{
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v6; // rax

  if ( !player )
    return 0;
  if ( Player::getRecord(player, 1631) > 0 )
    return 0;
  if ( m_Price <= 0 || !std::vector<MemChrBag>::size(&m_Items) )
    return 0;
  Bag = Player::GetBag(player);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
  if ( FreeSlotCount < (int)std::vector<MemChrBag>::size(&m_Items) )
    return 0;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          m_Price,
          CURRENCY_CHANGE_REASON::GCR_BUY_TITLE,
          0) )
    return 0;
  v6 = Player::GetBag(player);
  CExtCharBag::AddItem(v6, &m_Items, ITEM_CHANGE_REASON::IDCR_BUY_TITLE);
  Player::updateRecord(player, 1631, 1);
  return 1;
}



int32_t CFestivalDoubleEleven::BuyGiftShopItem(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  std::vector<ShopGoods> *v5; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  int32_t nDayIndex; // [rsp+2Ch] [rbp-24h]
  int32_t nOldRecord; // [rsp+30h] [rbp-20h]
  int nNewRecord; // [rsp+34h] [rbp-1Ch]
  ShopGoods *goods; // [rsp+38h] [rbp-18h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_GIFT_SHOP) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nGiftShopSize )
    return 10002;
  nDayIndex = m_nDay - m_vStartDay[17];
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1607);
  nNewRecord = nOldRecord | (1 << (nDayIndex * LOBYTE(m_nGiftShopSize) + nIndex));
  if ( nOldRecord == nNewRecord )
    return 10002;
  v5 = std::vector<std::vector<ShopGoods>>::operator[](&m_vGiftShopGoods, nDayIndex);
  goods = std::vector<ShopGoods>::operator[](v5, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM,
          0) )
    return 10002;
  v7 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v7, 1607, nNewRecord);
  return 0;
}



int32_t CFestivalDoubleEleven::BuyGiftShopItem2(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v6; // rax
  CharId_t Cid; // r13
  int32_t v8; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-40h] BYREF
  int32_t nOldRecord; // [rsp+30h] [rbp-30h]
  int32_t nNewRecord; // [rsp+34h] [rbp-2Ch]
  const ShopGoods *goods; // [rsp+38h] [rbp-28h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_LIMIT_SHOP_2) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nDailyLimitShop2Size )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2035);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  goods = std::vector<ShopGoods>::operator[](&m_vDailyLimitShop2Goods, nIndex);
  if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < goods->nPrice )
    return 10002;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &goods->vItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM_2) )
    return 10002;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          goods->nPrice,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_GIFT_SHOP_ITEM_2,
          0) )
    return 10002;
  v6 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v6, 2035, nNewRecord);
  if ( *std::vector<int>::operator[](&m_vDailyLimitShop2Broadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v8 = *std::vector<int>::operator[](&m_vDailyLimitShop2Broadcast, nIndex);
    ConnId = Player::getConnId(player);
    broadcastPlayerAction(, ConnId, v8, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}



int32_t CFestivalDoubleEleven::BuyGiftItem(Player *player, int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int64_t Currency; // rbx
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  int64_t v8; // rdx
  CharId_t Cid; // r13
  int32_t v10; // r12d
  int8_t ConnId; // bl
  CExtOperateLimit *v12; // rax
  std::string strCharName; // [rsp+20h] [rbp-30h] BYREF
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int32_t nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nBuyGiftSize )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BUY_GIFT) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1619);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
  if ( Currency < *std::vector<int>::operator[](&m_vBuyGiftPrice, nIndex) )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&m_vBuyGiftItem, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BUY_GIFT_ITEM) )
    return 10002;
  v8 = *std::vector<int>::operator[](&m_vBuyGiftPrice, nIndex);
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          v8,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_BUY_GIFT_ITEM,
          0) )
    return 10002;
  if ( *std::vector<int>::operator[](&m_vBuyGiftBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v10 = *std::vector<int>::operator[](&m_vBuyGiftBroadcast, nIndex);
    ConnId = Player::getConnId(player);
    broadcastPlayerAction(, ConnId, v10, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  v12 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v12, 1619, nNewRecord);
  return 0;
}



int32_t CFestivalDoubleEleven::GetRechargeBack(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  int nRechargeBack; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRechargeBack = CExtOperateLimit::GetLimitCount(OperateLimit, 1620);
  if ( nRechargeBack <= 0 )
    return 10002;
  if ( !Player::AddCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          nRechargeBack,
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_ELEVEN_RECHARGE_BACK,
          0) )
    return 10002;
  v4 = Player::GetOperateLimit(player);
  CExtOperateLimit::Reset(v4, 1620);
  v5 = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(v5, 1621, nRechargeBack);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetEquipUpStarBackItem(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v5; // rax
  CExtOperateLimit *v6; // rax
  MemChrBag item; // [rsp+10h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+3Ch] [rbp-4h]

  if ( !player )
    return 10002;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1617);
  if ( nCount <= 0 )
    return 10002;
  memset(&item, 0, sizeof(item));
  item.itemId = m_nEquipUpStarBackId;
  item.itemClass = 1;
  item.itemCount = nCount;
  item.bind = 1;
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_EQUIP_UPSTAR_BACK) )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  CExtOperateLimit::Reset(v5, 1617);
  v6 = Player::GetOperateLimit(player);
  CExtOperateLimit::AddLimitCount(v6, 1618, nCount);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetHuoYueDuSumGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // ebx
  CExtOperateLimit *v6; // rax
  int32_t v7; // eax
  std::vector<MemChrBag> *v8; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v10; // rax
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM) )
    return 10002;
  if ( nIndex < 0 || m_nHuoYueDuSumSize <= nIndex )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1603);
  if ( LimitCount < *std::vector<int>::operator[](&m_vHuoYueDuSumLimit, nIndex) )
    return 10002;
  v6 = Player::GetOperateLimit(player);
  v7 = CExtOperateLimit::GetLimitCount(v6, 1604);
  nNewSign = v7 | (1 << nIndex);
  if ( nNewSign == v7 )
    return 10002;
  v8 = std::vector<std::vector<MemChrBag>>::operator[](&m_vHuoYueDuSumReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v8, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_HUO_YUE_DU) )
    return 10002;
  v10 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v10, 1604, nNewSign);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetDailyRechargeGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  int32_t TodayPayGold; // ebx
  CExtOperateLimit *OperateLimit; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  CharId_t Cid; // r13
  int32_t v10; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-30h] BYREF
  int32_t nRewardSign; // [rsp+28h] [rbp-28h]
  int32_t nNewSign; // [rsp+2Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE_2) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nDailyRechargeSize )
    return 10002;
  TodayPayGold = Player::GetTodayPayGold(player);
  if ( TodayPayGold < *std::vector<int>::operator[](&m_vDailyRechargeLimit, nIndex) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRewardSign = CExtOperateLimit::GetLimitCount(OperateLimit, 2033);
  nNewSign = nRewardSign | (1 << nIndex);
  if ( nNewSign == nRewardSign )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&m_vDailyRechargeReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_DAILY_RECHARGE_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 2033, nNewSign);
  SendIconState(, player);
  if ( *std::vector<int>::operator[](&m_vDailyRechargeBroad, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v10 = *std::vector<int>::operator[](&m_vDailyRechargeBroad, nIndex);
    ConnId = Player::getConnId(player);
    broadcastPlayerAction(, ConnId, v10, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}



int32_t CFestivalDoubleEleven::GetRechargeSumGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  CharId_t Cid; // r13
  int32_t v10; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-40h] BYREF
  int32_t nRechargeSum; // [rsp+34h] [rbp-2Ch]
  int32_t nRewardSign; // [rsp+38h] [rbp-28h]
  int32_t nNewSign; // [rsp+3Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_GIFT) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nRechargeSumSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRechargeSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
  if ( *std::vector<int>::operator[](&m_vRechargeSumLimit, nIndex) > nRechargeSum )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  nRewardSign = CExtOperateLimit::GetLimitCount(v5, 1616);
  nNewSign = nRewardSign | (1 << nIndex);
  if ( nNewSign == nRewardSign )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&m_vRechargeSumReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_RECHARGE_SUM_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 1616, nNewSign);
  SendIconState(, player);
  if ( *std::vector<int>::operator[](&m_vRechargeSumBroadcast, nIndex) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v10 = *std::vector<int>::operator[](&m_vRechargeSumBroadcast, nIndex);
    ConnId = Player::getConnId(player);
    broadcastPlayerAction(, ConnId, v10, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}



int32_t CFestivalDoubleEleven::GetPetIllusionItemGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t LimitCount; // eax
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int nIllusionSum; // [rsp+24h] [rbp-1Ch]
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nPetIllusionItemSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nIllusionSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1622);
  if ( *std::vector<int>::operator[](&m_vPetIllusionItemLimit, nIndex) > nIllusionSum )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(v5, 1623);
  nNewSign = LimitCount | (1 << nIndex);
  if ( nNewSign == LimitCount )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&m_vPetIllusionItemReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_PET_ILLUSION_REWARD) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1623, nNewSign);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetXiaoFeiSumGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t nId)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CharId_t Cid; // r13
  int32_t v9; // r12d
  int8_t ConnId; // bl
  std::string strCharName; // [rsp+20h] [rbp-40h] BYREF
  int32_t nRechargeSum; // [rsp+34h] [rbp-2Ch]
  int32_t nRewardSign; // [rsp+38h] [rbp-28h]
  int32_t NewSign; // [rsp+3Ch] [rbp-24h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT) )
    return 10002;
  if ( nId < 0 || m_nXiaoFeiSumSize <= nId )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nRechargeSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
  if ( *std::vector<int>::operator[](&m_vXiaoFeiSumLimit, nId) > nRechargeSum )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  nRewardSign = CExtOperateLimit::GetLimitCount(v5, 1606);
  NewSign = nRewardSign | (1 << nId);
  if ( nRewardSign == NewSign )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&m_vXiaoFeiSumReward, nId);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_XIAO_FAI_SUM_GIFT) )
    return 10002;
  Player::updateRecord(player, 1606, NewSign);
  SendIconState(, player);
  if ( *std::vector<int>::operator[](&m_vXiaoFeiSumBroadcast, nId) > 0 )
  {
    Player::getName((const Player *const)&strCharName);
    Cid = Player::getCid(player);
    v9 = *std::vector<int>::operator[](&m_vXiaoFeiSumBroadcast, nId);
    ConnId = Player::getConnId(player);
    broadcastPlayerAction(, ConnId, v9, Cid, &strCharName);
    std::string::~string(&strCharName);
  }
  return 0;
}



void CFestivalDoubleEleven::GetLianRechargeReward(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t nType,
        int32_t nIndex)
{
  int32_t Record; // eax
  LianRechargeCfg *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  int32_t RewardRecord; // [rsp+2Ch] [rbp-24h]
  int32_t LianChongRecord; // [rsp+30h] [rbp-20h]
  int NewRecord; // [rsp+3Ch] [rbp-14h]

  if ( player && IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_LIAN_CHONG) )
  {
    if ( nType )
    {
      if ( nType != 1 )
        return;
      RewardRecord = 1637;
      LianChongRecord = 1635;
    }
    else
    {
      RewardRecord = 1636;
      LianChongRecord = 1634;
    }
    if ( nIndex + 1 <= Player::getRecord(player, LianChongRecord) )
    {
      Record = Player::getRecord(player, RewardRecord);
      NewRecord = Record | (1 << nIndex);
      if ( NewRecord != Record )
      {
        v5 = std::vector<LianRechargeCfg>::operator[](&m_LianRechargeCfgVt, nType);
        v6 = std::vector<std::vector<MemChrBag>>::operator[](&v5->vGiftVector, nIndex);
        Bag = Player::GetBag(player);
        if ( CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::IDCR_DOUBLE_ELEVEN_LIAN_CHONG) )
        {
          Player::updateRecord(player, RewardRecord, NewRecord);
          GongGao(, 3012, player);
          SendIconState(, player);
        }
      }
    }
  }
}



void CFestivalDoubleEleven::GongGao(int32_t GongGaoId, Player *player)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v4 = GameService::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(player);
      v8 = GameService::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}



void CFestivalDoubleEleven::UpdateRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int8_t nType,
        int16_t nDay,
        int16_t nIndex,
        const FestivalRank * info)
{
  switch ( nType )
  {
    case 4:
      updateDrawRank(, connid, nIndex, info);
      break;
    case 12:
      updateXiaoFeiRank(, connid, nDay, nIndex, info);
      break;
    case 16:
      updateXiaoFeiSumRank(, connid, nIndex, info);
      break;
    case 32:
      updateRechargeSumRank(, connid, nIndex, info);
      break;
    case 33:
      updateCrossRechargeSumRank(, connid, nIndex, info);
      break;
    case 34:
      updateCrossXiaoFeiSumRank(, connid, nIndex, info);
      break;
    case 37:
      updateCrossChouJiangRank(, connid, nIndex, info);
      break;
    case 43:
      updateBossScoreRank(, connid, nIndex, info);
      break;
    default:
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CFestivalDoubleEleven::UpdateRank() wrong type = %d",
        nType);
      break;
  }
}



void CFestivalDoubleEleven::AddHuoYueDu(Player *player, int32_t nValue)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( player )
  {
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_HUO_YUE_DU_SUM) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1603, nValue);
      SendIconState(, player);
    }
  }
}



bool CFestivalDoubleEleven::canGetLandGift(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 0;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_LAND) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 2030) <= 0;
}



bool CFestivalDoubleEleven::canGetLandSumGift(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t nLandDays; // [rsp+14h] [rbp-1Ch]
  int nRecord; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( !player )
    return 0;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_LAND_SUM) )
    return 0;
  nLandDays = getLandSum(, player);
  OperateLimit = Player::GetOperateLimit(player);
  nRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1614);
  for ( i = 0; i < nLandDays; ++i )
  {
    if ( ((nRecord >> i) & 1) == 0 )
      return 1;
  }
  return 0;
}



bool CFestivalDoubleEleven::canGetDrawGift(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nDrawTimes; // [rsp+28h] [rbp-8h]

  if ( !player )
    return 0;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_DRAW) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nDrawTimes = CExtOperateLimit::GetLimitCount(OperateLimit, 1601);
  v4 = Player::GetOperateLimit(player);
  return nDrawTimes / m_nDrawLoopTimes > CExtOperateLimit::GetLimitCount(v4, 1602);
}



bool CFestivalDoubleEleven::canGetOnlineGift(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nOnlineTime; // [rsp+28h] [rbp-8h]
  int32_t nRewardTimes; // [rsp+2Ch] [rbp-4h]

  if ( !player )
    return 0;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2036);
  v4 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v4, 2037);
  return m_nMaxCount > nRewardTimes && nOnlineTime / m_nOnlineTimeArea > nRewardTimes;
}



int32_t CFestivalDoubleEleven::GetOnlineTimeRewardTime(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nOnlineTime; // [rsp+28h] [rbp-8h]
  int nRewardTimes; // [rsp+2Ch] [rbp-4h]

  if ( !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2036);
  v4 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v4, 2037);
  if ( nOnlineTime / m_nOnlineTimeArea > nRewardTimes )
    return 0;
  else
    return (nRewardTimes + 1) * m_nOnlineTimeArea - nOnlineTime;
}



bool CFestivalDoubleEleven::canGetWishGift(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nRecharge; // [rsp+18h] [rbp-8h]
  int32_t nReward; // [rsp+1Ch] [rbp-4h]

  if ( !player )
    return 0;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BEST_WISH) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nRecharge = CExtOperateLimit::GetLimitCount(OperateLimit, 2026);
  v4 = Player::GetOperateLimit(player);
  nReward = CExtOperateLimit::GetLimitCount(v4, 2038);
  return m_nWishRecharge <= nRecharge && !nReward;
}



bool CFestivalDoubleEleven::canGetFaBaoBack(Player *player)
{
  int32_t Record; // ebx
  int32_t OldRecord; // [rsp+14h] [rbp-1Ch]
  int32_t i; // [rsp+18h] [rbp-18h]

  if ( !player )
    return 0;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
    return 0;
  OldRecord = Player::getRecord(player, 1629);
  for ( i = 0; m_nSize > i; ++i )
  {
    if ( OldRecord != (OldRecord | (1 << i)) )
    {
      Record = Player::getRecord(player, 1630);
      if ( Record >= *std::vector<int>::operator[](&m_NeedValue, i) )
        return 1;
    }
  }
  return 0;
}



bool CFestivalDoubleEleven::canGetEquipUpStarBack(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 0;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 1617) > 0;
}



bool CFestivalDoubleEleven::canGetRechargeBack(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !player )
    return 0;
  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 1620) > 0;
}



int32_t CFestivalDoubleEleven::getLandSum(Player *player)
{
  int32_t m_nDay; // eax
  int32_t v4; // eax
  CExtOperateLimit *OperateLimit; // rax
  int32_t nEndDay; // [rsp+18h] [rbp-28h]
  int32_t nStart; // [rsp+1Ch] [rbp-24h]
  int32_t nEnd; // [rsp+20h] [rbp-20h]
  int nLandRecord; // [rsp+24h] [rbp-1Ch]
  int32_t nCount; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 0;
  if ( m_nDay >= m_vEndDay[9] )
    m_nDay = m_vEndDay[9];
  else
    m_nDay = m_nDay;
  nEndDay = m_nDay;
  if ( m_nDay <= m_nDay )
    v4 = 0;
  else
    v4 = m_nDay - m_nDay;
  nStart = v4;
  nEnd = nEndDay + v4 - m_vStartDay[9];
  OperateLimit = Player::GetOperateLimit(player);
  nLandRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1069);
  nCount = 0;
  for ( i = nStart; i <= nEnd; ++i )
  {
    if ( ((nLandRecord >> i) & 1) != 0 )
      ++nCount;
  }
  return nCount;
}



void CFestivalDoubleEleven::checkWorldBoss()
{
  GameService *v2; // rax
  int32_t m_nMinute; // ebx
  int32_t m_Mid; // ebx
  CfgData *v5; // rax
  CfgData *v6; // rax
  CPoolManager *v7; // rax
  int32_t v8; // ebx
  int32_t nEndTime; // r12d
  TimeArea *v10; // rax
  int32_t m_MapId; // ebx
  MapManager *v12; // rax
  int32_t v13; // ebx
  size_t v14; // rbx
  CfgMapMonster MapMonster; // [rsp+10h] [rbp-70h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+30h] [rbp-50h] BYREF
  uint32_t i; // [rsp+4Ch] [rbp-34h]
  CfgMonster *pMonster; // [rsp+50h] [rbp-30h]
  int32_t MonsterId; // [rsp+5Ch] [rbp-24h]
  Monster *monster; // [rsp+60h] [rbp-20h]
  Map *pMap; // [rsp+68h] [rbp-18h]

  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_WORLD_BOSS)
    && !std::vector<TimeArea>::empty(&m_vWorldBossMinute) )
  {
    v2 = GameService::instance();
    if ( GameService::getLine(v2) == 1 )
    {
      for ( i = 0; ; ++i )
      {
        v14 = i;
        if ( v14 >= std::vector<TimeArea>::size(&m_vWorldBossMinute) )
          break;
        m_nMinute = m_nMinute;
        if ( m_nMinute == std::vector<TimeArea>::operator[](&m_vWorldBossMinute, i)->nStartTime )
        {
          m_Mid = m_Mid;
          v5 = CfgData::instance();
          pMonster = CfgData::getMonster(v5, m_Mid);
          if ( !pMonster || pMonster->boss_sign != 11 )
            return;
          v6 = CfgData::instance();
          MonsterId = CfgData::GetMapMonsterId(v6);
          memset(&MapMonster.mapid, 0, 24);
          MapMonster.id = MonsterId;
          MapMonster.mapid = m_MapId;
          MapMonster.x = m_X;
          MapMonster.y = m_Y;
          m_MonsterId = MonsterId;
          v7 = CPoolManager::instance();
          monster = CPoolManager::pop<Monster>(v7);
          if ( monster && pMonster )
          {
            std::vector<AttrAddon>::vector(&vAttrAddon);
            Monster::init(monster, pMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
            std::vector<AttrAddon>::~vector(&vAttrAddon);
            v8 = now();
            nEndTime = std::vector<TimeArea>::operator[](&m_vWorldBossMinute, i)->nEndTime;
            v10 = std::vector<TimeArea>::operator[](&m_vWorldBossMinute, i);
            Monster::SetLifeTime(monster, v8 + 60 * (nEndTime - v10->nStartTime));
            m_MapId = m_MapId;
            v12 = MapManager::instance();
            pMap = MapManager::GetMap(v12, m_MapId);
            if ( pMap )
            {
              (*((void (__fastcall **)(Map *, Monster *, _QWORD, _QWORD))pMap->_vptr_Map + 28))(
                pMap,
                monster,
                (unsigned int)MapMonster.x,
                (unsigned int)MapMonster.y);
              m_bDie = 0;
            }
          }
          broadcastWorldBossStart();
          SendWorldBossIconState();
        }
        else
        {
          v13 = m_nMinute;
          if ( v13 == std::vector<TimeArea>::operator[](&m_vWorldBossMinute, i)->nEndTime )
          {
            m_bDie = 1;
            broadcastWorldBossEnd();
            SendWorldBossIconState();
          }
        }
      }
    }
  }
}



void CFestivalDoubleEleven::BossDie(
        CFestivalDoubleEleven * this,
        int32_t MonsterId,
        std::string *p_name,
        CharId_t Cid)
{
  if ( m_MonsterId > 0 && m_MonsterId == MonsterId )
  {
    m_bDie = 1;
    BroadcastWorldBossKilled(, p_name, Cid);
    SendWorldBossIconState();
  }
}



void CFestivalDoubleEleven::BroadcastWorldBossKilled(
        CFestivalDoubleEleven * this,
        const std::string\& name,
        CharId_t cid)
{
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = GameService::instance();
  packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, m_nWorldBossKillBroadcast);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = GameService::instance();
    GameService::worldBroadcast(v5, 0, packet);
  }
}



void CFestivalDoubleEleven::broadcastWorldBossStart()
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = GameService::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, m_nWorldBossStartBroadcast);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = GameService::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}



void CFestivalDoubleEleven::broadcastWorldBossEnd()
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = GameService::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, m_nWorldBossEndBroadcast);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = GameService::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}



void CFestivalDoubleEleven::AddOnlineRecord(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  int32_t nOnlineTime; // [rsp+20h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+24h] [rbp-Ch]

  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_ONLINE_TIME)
    && player
    && m_nMinute >= m_nOnlineStartMinute
    && m_nMinute < m_nOnlineEndMinute )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nOnlineTime = CExtOperateLimit::GetLimitCount(OperateLimit, 2036);
    v4 = Player::GetOperateLimit(player);
    nRewardTimes = CExtOperateLimit::GetLimitCount(v4, 2037);
    if ( m_nMaxCount > nRewardTimes )
    {
      v5 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v5, 2036, 1);
      if ( nOnlineTime / m_nOnlineTimeArea - nRewardTimes != (nOnlineTime + 1) / m_nOnlineTimeArea
                                                                 - nRewardTimes )
        SendIconState(, player);
    }
  }
}



void CFestivalDoubleEleven::UpdateXiaoFeiRank(Player *player)
{
  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_XIAO_FEI_RANK) )
    updateXiaoFeiRank(, player);
  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_RANK) )
    updateXiaoFeiSumRank(, player);
  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_XIAO_FEI_SUM_RANK) )
    updateCrossXiaoFeiSumRank(, player);
}



void CFestivalDoubleEleven::AddXiaoFeiRecord(Player *player, int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nOldCount; // [rsp+24h] [rbp-Ch]

  if ( player && IsInTime() )
  {
    nOldCount = GetXiaoFeiSumGiftCount(, player);
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
    v4 = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(v4, 1605, nCount);
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW)
      && CanUseXiaoFeiDraw(, player) )
    {
      SendIconState(, player);
    }
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_SUM_GIFT)
      && GetXiaoFeiSumGiftCount(, player) != nOldCount )
    {
      SendIconState(, player);
    }
  }
}



int32_t CFestivalDoubleEleven::GetXiaoFeiSumGiftCount(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t LimitCount; // eax
  int32_t Count; // [rsp+1Ch] [rbp-24h]
  int nRewardSum; // [rsp+20h] [rbp-20h]
  int32_t i; // [rsp+24h] [rbp-1Ch]

  Count = 0;
  if ( !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nRewardSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
  for ( i = 0; m_nXiaoFeiSumSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&m_vXiaoFeiSumLimit, i) <= nRewardSum )
    {
      v4 = Player::GetOperateLimit(player);
      LimitCount = CExtOperateLimit::GetLimitCount(v4, 1606);
      if ( (LimitCount | (1 << i)) != LimitCount )
        ++Count;
    }
  }
  return Count;
}



void CFestivalDoubleEleven::AddRechargeRecord(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t nAddValue; // [rsp+2Ch] [rbp-4h]

  if ( player && IsInTime() )
  {
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1615, nCount);
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_SUM_RANK) )
      updateRechargeSumRank(, player);
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_CROSS_RECHARGE_SUM_RANK) )
      updateCrossRechargeSumRank(, player);
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_BACK) )
    {
      nAddValue = calRechargeBack(, nCount);
      v4 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v4, 1620, nAddValue);
    }
  }
}



void CFestivalDoubleEleven::AddPetIllusionItemRecord(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( player )
  {
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_PET_ILLUSION_ITEM) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1622, nCount);
      SendIconState(, player);
    }
  }
}



void CFestivalDoubleEleven::AddFriendQingYi(Player *player, int32_t nValue)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( player )
  {
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1624, nValue);
      SendIconState(, player);
    }
  }
}



bool CFestivalDoubleEleven::CanUseXiaoFeiDraw(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int nXiaoFeiSum; // [rsp+10h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+14h] [rbp-Ch]
  int32_t nCanGetTime; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_XIAO_FEI_DRAW) || !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nXiaoFeiSum = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 1606);
  nCanGetTime = 0;
  for ( i = 0; m_nXiaoFeiDrawSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&m_nXiaoFeiDrawValue, i) <= nXiaoFeiSum )
      nCanGetTime = i + 1;
  }
  return nCanGetTime - nRewardTimes > 0;
}



bool CFestivalDoubleEleven::CanUseRechargeDraw(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int nChongZhi; // [rsp+10h] [rbp-10h]
  int32_t nRewardTimes; // [rsp+14h] [rbp-Ch]
  int32_t nCanGetTime; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !IsOpen(, FESTIVAL_ACTIVITY_TYPE::FAT_RECHARGE_DRAW) || !player )
    return 0;
  OperateLimit = Player::GetOperateLimit(player);
  nChongZhi = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
  v5 = Player::GetOperateLimit(player);
  nRewardTimes = CExtOperateLimit::GetLimitCount(v5, 1632);
  nCanGetTime = 0;
  for ( i = 0; m_RechargeDrawSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&m_nRechargeDrawValue, i) <= nChongZhi )
      nCanGetTime = i + 1;
  }
  return nCanGetTime - nRewardTimes > 0;
}



void CFestivalDoubleEleven::loadXiaoFeiRank()
{
  Answer::DBPool *v1; // rax
  size_t m_nXiaoFeiRankSize; // rbx
  std::vector<FestivalRank> *v3; // rax
  Answer::MySqlQuery *v4; // rax
  size_t v5; // rbx
  std::vector<FestivalRank> *v6; // rax
  FestivalRank *v7; // rbx
  const char *StringValue; // rbx
  size_t v9; // r12
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  size_t v12; // rbx
  std::vector<FestivalRank> *v13; // rax
  FestivalRank *v14; // rbx
  size_t v15; // rbx
  std::vector<FestivalRank> *v16; // rax
  FestivalRank *v17; // rbx
  std::vector<std::vector<FestivalRank>> *v19; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-10E0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-E0h] BYREF
  Answer::MySqlQuery result; // [rsp+1040h] [rbp-B0h] BYREF
  FestivalRankVtVt vRank; // [rsp+1060h] [rbp-90h] BYREF
  std::vector<FestivalRank> p___x; // [rsp+1080h] [rbp-70h] BYREF
  FestivalRank v25; // [rsp+10A0h] [rbp-50h] BYREF
  char __k; // [rsp+10D7h] [rbp-19h] BYREF
  int32_t i; // [rsp+10D8h] [rbp-18h]
  int32_t nIndex; // [rsp+10DCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  memset(szSQL, 0, sizeof(szSQL));
  std::vector<std::vector<FestivalRank>>::vector(&vRank);
  std::vector<FestivalRank>::vector(&p___x);
  std::vector<std::vector<FestivalRank>>::resize(&vRank, m_nEndDay, &p___x);
  std::vector<FestivalRank>::~vector(&p___x);
  for ( i = 0; m_nEndDay > i; ++i )
  {
    FestivalRank::FestivalRank(&v25);
    m_nXiaoFeiRankSize = m_nXiaoFeiRankSize;
    v3 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
    std::vector<FestivalRank>::resize(v3, m_nXiaoFeiRankSize, &v25);
    FestivalRank::~FestivalRank(&v25);
    bzero(szSQL, 0x1000u);
    snprintf(
      szSQL,
      0xFFFu,
      "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=12 AND `day`=%d ORDER BY `count` DESC,`time`",
      i);
    v4 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery result(v4);
    nIndex = 0;
    while ( !Answer::MySqlQuery::eof(&result) && m_nXiaoFeiRankSize > nIndex )
    {
      v5 = nIndex;
      v6 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v7 = std::vector<FestivalRank>::operator[](v6, v5);
      v7->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
      v9 = nIndex;
      v10 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v11 = std::vector<FestivalRank>::operator[](v10, v9);
      std::string::operator=(&v11->strName, StringValue);
      v12 = nIndex;
      v13 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v14 = std::vector<FestivalRank>::operator[](v13, v12);
      v14->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
      v15 = nIndex;
      v16 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      v17 = std::vector<FestivalRank>::operator[](v16, v15);
      v17->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
      ++nIndex;
      Answer::MySqlQuery::nextRow(&result);
    }
    ;
  }
  __k = 0;
  v19 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &__k);
  std::vector<std::vector<FestivalRank>>::operator=(v19, &vRank);
  std::vector<std::vector<FestivalRank>>::~vector(&vRank);
  ;
}



void CFestivalDoubleEleven::updateXiaoFeiRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  size_t m_nDay; // r12
  std::vector<std::vector<FestivalRank>> *v6; // rax
  std::vector<FestivalRank> *v7; // rax
  FestivalRank *v8; // rax
  int v9; // ebx
  size_t v10; // rbx
  size_t v11; // r12
  std::vector<std::vector<FestivalRank>> *v12; // rax
  std::vector<FestivalRank> *v13; // rax
  FestivalRank *v14; // rax
  int v15; // ebx
  size_t v16; // rbx
  size_t v17; // r12
  std::vector<std::vector<FestivalRank>> *v18; // rax
  std::vector<FestivalRank> *v19; // rax
  FestivalRank *v20; // rbx
  size_t v21; // r12
  size_t v22; // r13
  std::vector<std::vector<FestivalRank>> *v23; // rax
  std::vector<FestivalRank> *v24; // rax
  FestivalRank *v25; // rax
  size_t v26; // rbx
  size_t v27; // r12
  std::vector<std::vector<FestivalRank>> *v28; // rax
  std::vector<FestivalRank> *v29; // rax
  size_t v30; // rbx
  size_t v31; // r12
  std::vector<std::vector<FestivalRank>> *v32; // rax
  std::vector<FestivalRank> *v33; // rax
  FestivalRank *v34; // rax
  size_t v35; // rbx
  size_t v36; // r12
  std::vector<std::vector<FestivalRank>> *v37; // rax
  std::vector<FestivalRank> *v38; // rax
  FestivalRank *v39; // rax
  size_t v40; // rbx
  size_t v41; // r12
  std::vector<std::vector<FestivalRank>> *v42; // rax
  std::vector<FestivalRank> *v43; // rax
  FestivalRank *v44; // rax
  size_t v45; // rbx
  size_t v46; // r12
  std::vector<std::vector<FestivalRank>> *v47; // rax
  std::vector<FestivalRank> *v48; // rax
  FestivalRank *v49; // rbx
  size_t v50; // rbx
  size_t v51; // r12
  std::vector<std::vector<FestivalRank>> *v52; // rax
  std::vector<FestivalRank> *v53; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-90h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-80h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::string strName; // [rsp+50h] [rbp-50h] BYREF
  int8_t connid; // [rsp+63h] [rbp-3Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-3Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-38h]
  int32_t nRankIndex; // [rsp+74h] [rbp-2Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-28h]
  int16_t i; // [rsp+7Ah] [rbp-26h]
  int16_t i_0; // [rsp+7Ch] [rbp-24h]
  int16_t i_1; // [rsp+7Eh] [rbp-22h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 2031);
    if ( m_nDay >= 0 && m_nDay < m_nEndDay )
    {
      connid = Player::getConnId(player);
      nCharId = Player::getCid(player);
      Player::getName((const Player *const)&strName);
      checkXiaoFeiRankInvalid(, connid);
      nRankIndex = -1;
      for ( i = 0; i < m_nXiaoFeiRankSize; ++i )
      {
        v3 = std::vector<int>::operator[](&m_vXiaoFeiRankLimit, i);
        if ( *v3 <= nScore )
        {
          Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
          v4 = i;
          m_nDay = m_nDay;
          v6 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
          v7 = std::vector<std::vector<FestivalRank>>::operator[](v6, m_nDay);
          v8 = std::vector<FestivalRank>::operator[](v7, v4);
          if ( v8->nScore >= nScore )
          {
            v9 = 1;
          }
          else
          {
            nRankIndex = i;
            v9 = 0;
          }
          Answer::MutexGuard::~MutexGuard(&lock_0);
          if ( !v9 )
            break;
        }
      }
      if ( nRankIndex >= 0 )
      {
        nOldIndex = m_nXiaoFeiRankSize - 1;
        for ( i_0 = 0; i_0 < m_nXiaoFeiRankSize; ++i_0 )
        {
          Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
          v10 = i_0;
          v11 = m_nDay;
          v12 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
          v13 = std::vector<std::vector<FestivalRank>>::operator[](v12, v11);
          v14 = std::vector<FestivalRank>::operator[](v13, v10);
          if ( v14->nCharId == nCharId )
          {
            nOldIndex = i_0;
            v15 = 0;
          }
          else
          {
            v15 = 1;
          }
          Answer::MutexGuard::~MutexGuard(&lock_1);
          if ( !v15 )
            break;
        }
        if ( nOldIndex < nRankIndex )
          nRankIndex = nOldIndex;
        if ( nOldIndex != nRankIndex )
        {
          for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
          {
            Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
            v16 = i_1 - 1;
            v17 = m_nDay;
            v18 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &m_mXiaoFeiRank,
                    &connid);
            v19 = std::vector<std::vector<FestivalRank>>::operator[](v18, v17);
            v20 = std::vector<FestivalRank>::operator[](v19, v16);
            v21 = i_1;
            v22 = m_nDay;
            v23 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &m_mXiaoFeiRank,
                    &connid);
            v24 = std::vector<std::vector<FestivalRank>>::operator[](v23, v22);
            v25 = std::vector<FestivalRank>::operator[](v24, v21);
            FestivalRank::operator=(v25, v20);
            v26 = i_1;
            v27 = m_nDay;
            v28 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](
                    &m_mXiaoFeiRank,
                    &connid);
            v29 = std::vector<std::vector<FestivalRank>>::operator[](v28, v27);
            std::vector<FestivalRank>::operator[](v29, v26)->bChange = 1;
            Answer::MutexGuard::~MutexGuard(&lock_2);
          }
        }
        Answer::MutexGuard::MutexGuard(&lock, &m_lock);
        v30 = nRankIndex;
        v31 = m_nDay;
        v32 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
        v33 = std::vector<std::vector<FestivalRank>>::operator[](v32, v31);
        v34 = std::vector<FestivalRank>::operator[](v33, v30);
        v34->nCharId = nCharId;
        v35 = nRankIndex;
        v36 = m_nDay;
        v37 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
        v38 = std::vector<std::vector<FestivalRank>>::operator[](v37, v36);
        v39 = std::vector<FestivalRank>::operator[](v38, v35);
        std::string::operator=(&v39->strName, &strName);
        v40 = nRankIndex;
        v41 = m_nDay;
        v42 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
        v43 = std::vector<std::vector<FestivalRank>>::operator[](v42, v41);
        v44 = std::vector<FestivalRank>::operator[](v43, v40);
        v44->nScore = nScore;
        v45 = nRankIndex;
        v46 = m_nDay;
        v47 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
        v48 = std::vector<std::vector<FestivalRank>>::operator[](v47, v46);
        v49 = std::vector<FestivalRank>::operator[](v48, v45);
        v49->nTime = Unit::getNow(player);
        v50 = nRankIndex;
        v51 = m_nDay;
        v52 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&m_mXiaoFeiRank, &connid);
        v53 = std::vector<std::vector<FestivalRank>>::operator[](v52, v51);
        std::vector<FestivalRank>::operator[](v53, v50)->bChange = 1;
        Answer::MutexGuard::~MutexGuard(&lock);
      }
      std::string::~string(&strName);
    }
  }
}



void CFestivalDoubleEleven::updateXiaoFeiRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nDay,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<std::vector<FestivalRank>> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<std::vector<FestivalRank>> *v7; // rax
  std::vector<FestivalRank> *v8; // rax
  std::vector<std::vector<FestivalRank>> *v9; // rax
  std::vector<FestivalRank> *v10; // rax
  std::vector<std::vector<FestivalRank>> *v12; // rax
  std::vector<FestivalRank> *v13; // rax
  FestivalRank *v14; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nDay >= 0 && nDay < thisa->m_nEndDay && nIndex >= 0 && nIndex < thisa->m_nXiaoFeiRankSize )
  {
    CFestivalDoubleEleven::checkXiaoFeiRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v5 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida);
    v6 = std::vector<std::vector<FestivalRank>>::operator[](v5, nDay);
    if ( std::vector<FestivalRank>::operator[](v6, nIndex)->nScore < info->nScore
      || (v7 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida),
          v8 = std::vector<std::vector<FestivalRank>>::operator[](v7, nDay),
          std::vector<FestivalRank>::operator[](v8, nIndex)->nScore == info->nScore)
      && (v9 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida),
          v10 = std::vector<std::vector<FestivalRank>>::operator[](v9, nDay),
          std::vector<FestivalRank>::operator[](v10, nIndex)->nTime < info->nTime) )
    {
      v12 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida);
      v13 = std::vector<std::vector<FestivalRank>>::operator[](v12, nDay);
      v14 = std::vector<FestivalRank>::operator[](v13, nIndex);
      FestivalRank::operator=(v14, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkXiaoFeiRankInvalid(int8_t connid)
{
  size_t m_nXiaoFeiRankSize; // rbx
  std::vector<FestivalRank> *v3; // rax
  std::vector<std::vector<FestivalRank>> *v4; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-CCh] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-C8h]
  FestivalRankVtVt vRank; // [rsp+10h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > iter; // [rsp+30h] [rbp-A0h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > __x; // [rsp+50h] [rbp-80h] BYREF
  std::vector<FestivalRank> p___x; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank v12; // [rsp+80h] [rbp-50h] BYREF
  int32_t i; // [rsp+BCh] [rbp-14h]

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::find(&m_mXiaoFeiRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::end(&thisa->m_mXiaoFeiRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator==(
         &iter,
         &__x) )
  {
    std::vector<std::vector<FestivalRank>>::vector(&vRank);
    std::vector<FestivalRank>::vector(&p___x);
    std::vector<std::vector<FestivalRank>>::resize(&vRank, thisa->m_nEndDay, &p___x);
    std::vector<FestivalRank>::~vector(&p___x);
    for ( i = 0; thisa->m_nEndDay > i; ++i )
    {
      FestivalRank::FestivalRank(&v12);
      m_nXiaoFeiRankSize = thisa->m_nXiaoFeiRankSize;
      v3 = std::vector<std::vector<FestivalRank>>::operator[](&vRank, i);
      std::vector<FestivalRank>::resize(v3, m_nXiaoFeiRankSize, &v12);
      FestivalRank::~FestivalRank(&v12);
    }
    v4 = std::map<signed char,std::vector<std::vector<FestivalRank>>>::operator[](&thisa->m_mXiaoFeiRank, connida);
    std::vector<std::vector<FestivalRank>>::operator=(v4, &vRank);
    std::vector<std::vector<FestivalRank>>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::checkXiaoFeiRank()
{
  size_t v1; // rbx
  std::vector<FestivalRank> *v2; // rax
  size_t v3; // rbx
  std::vector<FestivalRank> *v4; // rax
  size_t v5; // rbx
  std::vector<FestivalRank> *v6; // rax
  size_t v7; // rbx
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // r13
  int16_t v10; // r14
  int16_t m_nDay; // r12
  DBService *v12; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVtVt *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  if ( m_nDay >= 0 && m_nDay < m_nEndDay )
  {
    Answer::MutexGuard::MutexGuard(&lock, &m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::begin(&m_mXiaoFeiRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::end(&m_mXiaoFeiRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator!=(
              &iter,
              &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->second;
      for ( i = 0; i < m_nXiaoFeiRankSize; ++i )
      {
        v1 = i;
        v2 = std::vector<std::vector<FestivalRank>>::operator[](vRank, m_nDay);
        if ( std::vector<FestivalRank>::operator[](v2, v1)->nCharId <= 0 )
          break;
        v3 = i;
        v4 = std::vector<std::vector<FestivalRank>>::operator[](vRank, m_nDay);
        if ( std::vector<FestivalRank>::operator[](v4, v3)->bChange )
        {
          v5 = i;
          v6 = std::vector<std::vector<FestivalRank>>::operator[](vRank, m_nDay);
          std::vector<FestivalRank>::operator[](v6, v5)->bChange = 0;
          v7 = i;
          v8 = std::vector<std::vector<FestivalRank>>::operator[](vRank, m_nDay);
          v9 = std::vector<FestivalRank>::operator[](v8, v7);
          v10 = i;
          m_nDay = m_nDay;
          LOBYTE(v7) = connid;
          v12 = DBService::instance();
          DBService::SaveDoubleElevenRank(v12, v7, 12, m_nDay, v10, v9);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::sendXiaoFeiRankMail()
{
  GameService *v1; // rax
  size_t v2; // rbx
  std::vector<FestivalRank> *v3; // rax
  std::vector<MemChrBag> *v4; // r14
  int32_t v5; // r13d
  size_t v6; // rbx
  std::vector<FestivalRank> *v7; // rax
  CharId_t nCharId; // r12
  DBService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<std::vector<FestivalRank>> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v14; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVtVt *vRank; // [rsp+60h] [rbp-30h]
  int32_t nIndex; // [rsp+68h] [rbp-28h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 && m_nDay > 0 && m_nDay <= m_nEndDay )
  {
    Answer::MutexGuard::MutexGuard(&lock, &m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::begin(&m_mXiaoFeiRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<std::vector<FestivalRank>>>::end(&m_mXiaoFeiRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator!=(
              &iter,
              &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<std::vector<FestivalRank>>>>::operator->(&iter)->second;
      nIndex = m_nDay - 1;
      for ( i = 0; i < m_nXiaoFeiRankSize; ++i )
      {
        v2 = i;
        v3 = std::vector<std::vector<FestivalRank>>::operator[](vRank, nIndex);
        if ( std::vector<FestivalRank>::operator[](v3, v2)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v14);
          std::string::string(&Param, &byte_8D8B2F, &v14);
          v4 = std::vector<std::vector<MemChrBag>>::operator[](&m_vXiaoFeiRankReward, i);
          v5 = *std::vector<int>::operator[](&m_vXiaoFeiRankMail, i);
          v6 = i;
          v7 = std::vector<std::vector<FestivalRank>>::operator[](vRank, nIndex);
          nCharId = std::vector<FestivalRank>::operator[](v7, v6)->nCharId;
          LOBYTE(v6) = connid;
          v9 = DBService::instance();
          DBService::OnSendSysMail(
            v9,
            v6,
            nCharId,
            v5,
            v4,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_XIAO_FEI_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v14);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::loadXiaoFeiSumRank()
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=16 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery result(v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, m_nXiaoFeiSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && m_nXiaoFeiSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  ;
  ;
}



void CFestivalDoubleEleven::updateXiaoFeiSumRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  size_t v3; // rbx
  std::vector<FestivalRank> *v4; // rax
  FestivalRank *v5; // rax
  int v6; // ebx
  size_t v7; // rbx
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int v10; // ebx
  size_t v11; // rbx
  std::vector<FestivalRank> *v12; // rax
  FestivalRank *v13; // rbx
  size_t v14; // r12
  std::vector<FestivalRank> *v15; // rax
  FestivalRank *v16; // rax
  size_t v17; // rbx
  std::vector<FestivalRank> *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  FestivalRank *v21; // rax
  size_t v22; // rbx
  std::vector<FestivalRank> *v23; // rax
  FestivalRank *v24; // rax
  size_t v25; // rbx
  std::vector<FestivalRank> *v26; // rax
  FestivalRank *v27; // rax
  size_t v28; // rbx
  std::vector<FestivalRank> *v29; // rax
  FestivalRank *v30; // rbx
  size_t v31; // rbx
  std::vector<FestivalRank> *v32; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
    if ( m_nXiaoFeiSumRankLimit <= nScore )
    {
      connid = Player::getConnId(player);
      nCharId = Player::getCid(player);
      Player::getName((const Player *const)&strName);
      checkXiaoFeiSumRankInvalid(, connid);
      nRankIndex = -1;
      for ( i = 0; i < m_nXiaoFeiSumRankSize; ++i )
      {
        Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
        v3 = i;
        v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
        v5 = std::vector<FestivalRank>::operator[](v4, v3);
        if ( v5->nScore >= nScore )
        {
          v6 = 1;
        }
        else
        {
          nRankIndex = i;
          v6 = 0;
        }
        Answer::MutexGuard::~MutexGuard(&lock_0);
        if ( !v6 )
          break;
      }
      if ( nRankIndex >= 0 )
      {
        nOldIndex = m_nXiaoFeiSumRankSize - 1;
        for ( i_0 = 0; i_0 < m_nXiaoFeiSumRankSize; ++i_0 )
        {
          Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
          v7 = i_0;
          v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
          v9 = std::vector<FestivalRank>::operator[](v8, v7);
          if ( v9->nCharId == nCharId )
          {
            nOldIndex = i_0;
            v10 = 0;
          }
          else
          {
            v10 = 1;
          }
          Answer::MutexGuard::~MutexGuard(&lock_1);
          if ( !v10 )
            break;
        }
        if ( nOldIndex < nRankIndex )
          nRankIndex = nOldIndex;
        if ( nOldIndex != nRankIndex )
        {
          for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
          {
            Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
            v11 = i_1 - 1;
            v12 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
            v13 = std::vector<FestivalRank>::operator[](v12, v11);
            v14 = i_1;
            v15 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
            v16 = std::vector<FestivalRank>::operator[](v15, v14);
            FestivalRank::operator=(v16, v13);
            v17 = i_1;
            v18 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
            std::vector<FestivalRank>::operator[](v18, v17)->bChange = 1;
            Answer::MutexGuard::~MutexGuard(&lock_2);
          }
        }
        Answer::MutexGuard::MutexGuard(&lock, &m_lock);
        v19 = nRankIndex;
        v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
        v21 = std::vector<FestivalRank>::operator[](v20, v19);
        v21->nCharId = nCharId;
        v22 = nRankIndex;
        v23 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
        v24 = std::vector<FestivalRank>::operator[](v23, v22);
        std::string::operator=(&v24->strName, &strName);
        v25 = nRankIndex;
        v26 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
        v27 = std::vector<FestivalRank>::operator[](v26, v25);
        v27->nScore = nScore;
        v28 = nRankIndex;
        v29 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
        v30 = std::vector<FestivalRank>::operator[](v29, v28);
        v30->nTime = Unit::getNow(player);
        v31 = nRankIndex;
        v32 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mXiaoFeiSumRank, &connid);
        std::vector<FestivalRank>::operator[](v32, v31)->bChange = 1;
        Answer::MutexGuard::~MutexGuard(&lock);
      }
      std::string::~string(&strName);
    }
  }
}



void CFestivalDoubleEleven::updateXiaoFeiSumRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nXiaoFeiSumRankSize )
  {
    CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkXiaoFeiSumRankInvalid(int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&m_mXiaoFeiSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mXiaoFeiSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nXiaoFeiSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mXiaoFeiSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::checkXiaoFeiSumRank()
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mXiaoFeiSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mXiaoFeiSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < m_nXiaoFeiSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = DBService::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 16, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::sendXiaoFeiSumRankMail()
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mXiaoFeiSumRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mXiaoFeiSumRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < m_nXiaoFeiSumRankSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&m_vXiaoFeiSumRankReward, i);
          v3 = *std::vector<int>::operator[](&m_vXiaoFeiSumRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = DBService::instance();
          DBService::OnSendSysMail(
            v6,
            v5,
            nCharId,
            v3,
            v2,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_XIAO_FEI_SUM_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::loadRechargeSumRank()
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=32 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery result(v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, m_nRechargeSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && m_nRechargeSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  ;
  ;
}



void CFestivalDoubleEleven::updateRechargeSumRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    checkRechargeSumRankInvalid(, connid);
    nRankIndex = -1;
    for ( i = 0; i < m_nRechargeSumRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
      v3 = std::vector<int>::operator[](&m_vRechargeSumRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = m_nRechargeSumRankSize - 1;
      for ( i_0 = 0; i_0 < m_nRechargeSumRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mRechargeSumRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}



void CFestivalDoubleEleven::updateRechargeSumRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nRechargeSumRankSize )
  {
    CFestivalDoubleEleven::checkRechargeSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkRechargeSumRankInvalid(int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&m_mRechargeSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mRechargeSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nRechargeSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mRechargeSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::checkRechargeSumRank()
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mRechargeSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mRechargeSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < m_nRechargeSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = DBService::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 32, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::sendRechargeSumRankMail()
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mRechargeSumRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mRechargeSumRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < m_nRechargeSumRankSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&m_vRechargeSumRankReward, i);
          v3 = *std::vector<int>::operator[](&m_vRechargeSumRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = DBService::instance();
          DBService::OnSendSysMail(
            v6,
            v5,
            nCharId,
            v3,
            v2,
            ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_RECHARGE_SUM_RANK_REWARD,
            &Param,
            0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::BroadCastMoYuShiJieIconState()
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // eax
  GameService *v4; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    CFestivalDoubleEleven::getMoYuShiJieIconState(&stu, this);
    v2 = GameService::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, stu.nId);
      Answer::NetPacket::writeInt8(packet, stu.nState);
      Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
      Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
      Answer::NetPacket::writeInt32(packet, stu.nIconRight);
      Answer::NetPacket::writeInt8(packet, stu.nEffects);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = GameService::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}



void CFestivalDoubleEleven::AddMoYuShiJieDrop(
        CFestivalDoubleEleven * this,
        int32_t nFloor,
        MemChrBagVector * vItem)
{
  std::vector<MemChrBag> *v3; // rax
  std::vector<MemChrBag> *v4; // rax
  Answer::Random *v5; // rax
  size_t v6; // rbx
  std::vector<MemChrBag> *v7; // rax
  MemChrBag *v8; // rdx
  int nIndex; // [rsp+24h] [rbp-1Ch]
  int32_t nMax; // [rsp+28h] [rbp-18h]

  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_MO_YU_SHI_JIE) )
  {
    nIndex = nFloor - 1;
    if ( nFloor - 1 >= 0 && m_nMoYuShiJieDropSize > nIndex )
    {
      v3 = std::vector<std::vector<MemChrBag>>::operator[](&m_vMoYuShiJieDrop, nIndex);
      if ( !std::vector<MemChrBag>::empty(v3) )
      {
        v4 = std::vector<std::vector<MemChrBag>>::operator[](&m_vMoYuShiJieDrop, nIndex);
        nMax = std::vector<MemChrBag>::size(v4) - 1;
        v5 = Answer::Random::instance();
        v6 = Answer::Random::generate(v5, 0, nMax);
        v7 = std::vector<std::vector<MemChrBag>>::operator[](&m_vMoYuShiJieDrop, nIndex);
        v8 = std::vector<MemChrBag>::operator[](v7, v6);
        std::vector<MemChrBag>::push_back(vItem, v8);
      }
    }
  }
}



void CFestivalDoubleEleven::AddEquipUpStarBack(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t nStar)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t nStara; // [rsp+Ch] [rbp-34h] BYREF
  Player *playera; // [rsp+10h] [rbp-30h]
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-10h] BYREF
  int32_t nAddCount; // [rsp+3Ch] [rbp-4h]

  thisa = this;
  playera = player;
  nStara = nStar;
  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_UPSTAR_BACK) && playera )
  {
    iter._M_node = std::map<int,int>::find(&thisa->m_mEquipUpStarBackStarCount, &nStara)._M_node;
    __x._M_node = std::map<int,int>::end(&thisa->m_mEquipUpStarBackStarCount)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&iter, &__x) )
    {
      nAddCount = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      if ( nAddCount > 0 )
      {
        OperateLimit = Player::GetOperateLimit(playera);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1617, nAddCount);
        CFestivalDoubleEleven::SendIconState(thisa, playera);
      }
    }
  }
}



bool CFestivalDoubleEleven::RefreshMysteryShopItem(Player *player)
{
  int64_t m_nCount; // r12
  CURRENCY_TYPE v4; // ebx
  CExtCharBag *Bag; // rax

  if ( !player )
    return 0;
  if ( m_sMysteryShopRefreshCost.m_nClass == 4 )
  {
    m_nCount = m_sMysteryShopRefreshCost.m_nCount;
    v4 = TranseCurrencyType((CURRENCY_ITEM_ID)m_sMysteryShopRefreshCost.m_nId);
    return Player::DecCurrency(player, v4, m_nCount, CURRENCY_CHANGE_REASON::GCR_MYSTERY_SHOP_REFRESH, 0);
  }
  else
  {
    Bag = Player::GetBag(player);
    return CExtCharBag::RemoveItem(Bag, &m_sMysteryShopRefreshCost, ITEM_CHANGE_REASON::ICR_MYSTERY_SHOP_REFRESH);
  }
}



void CFestivalDoubleEleven::checkRefreshMysteryShop()
{
  if ( !(m_nMinute % 120) )
    broadcastRefreshMysteryShop();
}



void CFestivalDoubleEleven::broadcastRefreshMysteryShop()
{
  GameService *v1; // rax
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = GameService::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, m_nMysteryShopRefreshBroad);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = GameService::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}



void CFestivalDoubleEleven::broadcastPlayerAction(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int32_t nBroadId,
        CharId_t nCharId,
        const std::string\& strCharName)
{
  GameService *v5; // rax
  uint32_t WOffset; // edx
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  v5 = GameService::instance();
  packet = GameService::popNetpacket(v5, connid, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, nBroadId);
    Answer::NetPacket::writeUTF8(packet, strCharName);
    Answer::NetPacket::writeInt64(packet, nCharId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v7 = GameService::instance();
    GameService::worldBroadcast(v7, connid, packet);
  }
}



void CFestivalDoubleEleven::SendDaTiReward(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int32_t nIndex,
        CharId_t nCharId)
{
  std::vector<MemChrBag> *v4; // r13
  int32_t v5; // r12d
  DBService *v6; // rax
  std::string Param; // [rsp+30h] [rbp-30h] BYREF
  _BYTE v10[33]; // [rsp+3Fh] [rbp-21h] BYREF

  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_DA_TI)
    && nIndex > 0
    && m_nDaTiRankSize >= nIndex )
  {
    std::allocator<char>::allocator(v10);
    std::string::string(&Param, &byte_8D8B2F, v10);
    v4 = std::vector<std::vector<MemChrBag>>::operator[](&m_vDaTiRankReward, nIndex - 1);
    v5 = *std::vector<int>::operator[](&m_vDaTiRankMail, nIndex - 1);
    v6 = DBService::instance();
    DBService::OnSendSysMail(
      v6,
      connid,
      nCharId,
      v5,
      v4,
      ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_DA_TI_RANK_REWARD,
      &Param,
      0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(v10);
  }
}



int32_t CFestivalDoubleEleven::CalBossScoreAddValue(int32_t nValue)
{
  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE) )
    return nValue * m_nBossScoreRate / 100;
  else
    return nValue;
}



int32_t CFestivalDoubleEleven::calRechargeBack(int32_t nValue)
{
  int32_t nValuea; // [rsp+4h] [rbp-1Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-18h]
  int32_t nBackValue; // [rsp+18h] [rbp-8h]
  int32_t nResult; // [rsp+1Ch] [rbp-4h]

  thisa = this;
  nValuea = nValue;
  for ( nBackValue = 0; nValuea > 0; nBackValue += nResult )
  {
    nResult = CFestivalDoubleEleven::calRechargeBackHelper(thisa, &nValuea);
    if ( nResult <= 0 )
      break;
  }
  return nBackValue;
}



int32_t CFestivalDoubleEleven::calRechargeBackHelper(int32_t * nValue)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  int32_t i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; m_nRechargeBackSize > i; ++i )
  {
    v2 = *nValue;
    if ( v2 >= *std::vector<int>::operator[](&m_vRechargeBackLimit, i) )
    {
      v3 = *nValue;
      *nValue = v3 - *std::vector<int>::operator[](&m_vRechargeBackLimit, i);
      return *std::vector<int>::operator[](&m_vRechargeBackValue, i);
    }
  }
  return 0;
}



void CFestivalDoubleEleven::loadCrossRechargeSumRank()
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=33 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery result(v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, m_nCrossRechargeSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && m_nCrossRechargeSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  ;
  ;
}



void CFestivalDoubleEleven::updateCrossRechargeSumRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1615);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    checkCrossRechargeSumRankInvalid(, connid);
    nRankIndex = -1;
    for ( i = 0; i < m_nCrossRechargeSumRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
      v3 = std::vector<int>::operator[](&m_vCrossRechargeSumRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = m_nCrossRechargeSumRankSize - 1;
      for ( i_0 = 0; i_0 < m_nCrossRechargeSumRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossRechargeSumRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}



void CFestivalDoubleEleven::updateCrossRechargeSumRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nCrossRechargeSumRankSize )
  {
    CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkCrossRechargeSumRankInvalid(int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&m_mCrossRechargeSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mCrossRechargeSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nCrossRechargeSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossRechargeSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::checkCrossRechargeSumRank()
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mCrossRechargeSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mCrossRechargeSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < m_nCrossRechargeSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = DBService::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 33, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::loadCrossXiaoFeiSumRank()
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=34 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery result(v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, m_nCrossXiaoFeiSumRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && m_nCrossXiaoFeiSumRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  ;
  ;
}



void CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1605);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    checkCrossXiaoFeiSumRankInvalid(, connid);
    nRankIndex = -1;
    for ( i = 0; i < m_nCrossXiaoFeiSumRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
      v3 = std::vector<int>::operator[](&m_vCrossXiaoFeiSumRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = m_nCrossXiaoFeiSumRankSize - 1;
      for ( i_0 = 0; i_0 < m_nCrossXiaoFeiSumRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossXiaoFeiSumRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}



void CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&m_mCrossXiaoFeiSumRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mCrossXiaoFeiSumRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nCrossXiaoFeiSumRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::updateCrossXiaoFeiSumRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nCrossXiaoFeiSumRankSize )
  {
    CFestivalDoubleEleven::checkCrossXiaoFeiSumRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossXiaoFeiSumRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkCrossXiaoFeiSumRank()
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mCrossXiaoFeiSumRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mCrossXiaoFeiSumRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < m_nCrossXiaoFeiSumRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = DBService::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 34, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::loadCrossChouJiangRank()
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=37 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery result(v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, m_nCrossChouJiangRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && m_nCrossChouJiangRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  ;
  ;
}



void CFestivalDoubleEleven::updateCrossChouJiangRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  int *v3; // rax
  size_t v4; // rbx
  std::vector<FestivalRank> *v5; // rax
  FestivalRank *v6; // rax
  int v8; // ebx
  size_t v9; // rbx
  std::vector<FestivalRank> *v10; // rax
  FestivalRank *v11; // rax
  int v12; // ebx
  size_t v13; // rbx
  std::vector<FestivalRank> *v14; // rax
  FestivalRank *v15; // rbx
  size_t v16; // r12
  std::vector<FestivalRank> *v17; // rax
  FestivalRank *v18; // rax
  size_t v19; // rbx
  std::vector<FestivalRank> *v20; // rax
  size_t v21; // rbx
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  FestivalRank *v26; // rax
  size_t v27; // rbx
  std::vector<FestivalRank> *v28; // rax
  FestivalRank *v29; // rax
  size_t v30; // rbx
  std::vector<FestivalRank> *v31; // rax
  FestivalRank *v32; // rbx
  size_t v33; // rbx
  std::vector<FestivalRank> *v34; // rax
  Answer::MutexGuard lock_2; // [rsp+10h] [rbp-80h] BYREF
  Answer::MutexGuard lock_1; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock_0; // [rsp+30h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-50h] BYREF
  std::string strName; // [rsp+50h] [rbp-40h] BYREF
  int8_t connid; // [rsp+63h] [rbp-2Dh] BYREF
  int32_t nScore; // [rsp+64h] [rbp-2Ch]
  CharId_t nCharId; // [rsp+68h] [rbp-28h]
  int32_t nRankIndex; // [rsp+74h] [rbp-1Ch]
  int16_t nOldIndex; // [rsp+78h] [rbp-18h]
  int16_t i; // [rsp+7Ah] [rbp-16h]
  int16_t i_0; // [rsp+7Ch] [rbp-14h]
  int16_t i_1; // [rsp+7Eh] [rbp-12h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1601);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    checkCrossChouJiangRankInvalid(, connid);
    nRankIndex = -1;
    for ( i = 0; i < m_nCrossChouJiangRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
      v3 = std::vector<int>::operator[](&m_vCrossChouJiangRankLimit, i);
      if ( *v3 <= nScore
        && (v4 = i,
            v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid),
            v6 = std::vector<FestivalRank>::operator[](v5, v4),
            v6->nScore < nScore) )
      {
        nRankIndex = i;
        v8 = 0;
      }
      else
      {
        v8 = 1;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v8 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = m_nCrossChouJiangRankSize - 1;
      for ( i_0 = 0; i_0 < m_nCrossChouJiangRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
        v9 = i_0;
        v10 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
        v11 = std::vector<FestivalRank>::operator[](v10, v9);
        if ( v11->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v12 = 0;
        }
        else
        {
          v12 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v12 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
          v13 = i_1 - 1;
          v14 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
          v15 = std::vector<FestivalRank>::operator[](v14, v13);
          v16 = i_1;
          v17 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
          v18 = std::vector<FestivalRank>::operator[](v17, v16);
          FestivalRank::operator=(v18, v15);
          v19 = i_1;
          v20 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
          std::vector<FestivalRank>::operator[](v20, v19)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &m_lock);
      v21 = nRankIndex;
      v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
      v23 = std::vector<FestivalRank>::operator[](v22, v21);
      v23->nCharId = nCharId;
      v24 = nRankIndex;
      v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
      v26 = std::vector<FestivalRank>::operator[](v25, v24);
      std::string::operator=(&v26->strName, &strName);
      v27 = nRankIndex;
      v28 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
      v29 = std::vector<FestivalRank>::operator[](v28, v27);
      v29->nScore = nScore;
      v30 = nRankIndex;
      v31 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
      v32 = std::vector<FestivalRank>::operator[](v31, v30);
      v32->nTime = Unit::getNow(player);
      v33 = nRankIndex;
      v34 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mCrossChouJiangRank, &connid);
      std::vector<FestivalRank>::operator[](v34, v33)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}



void CFestivalDoubleEleven::updateCrossChouJiangRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_nCrossChouJiangRankSize )
  {
    CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkCrossChouJiangRankInvalid(int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&m_mCrossChouJiangRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mCrossChouJiangRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_nCrossChouJiangRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mCrossChouJiangRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::checkCrossChouJiangRank()
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mCrossChouJiangRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mCrossChouJiangRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < m_nCrossChouJiangRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = DBService::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 37, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



int32_t CFestivalDoubleEleven::GetEquipQingYiGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // eax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_EQUIP_QING_YI) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nEquipQingYiSize )
    return 10002;
  if ( *std::vector<int>::operator[](&m_vEquipQingYiLimit, nIndex) > 0 )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1125);
  nNewSign = LimitCount | (1 << nIndex);
  if ( nNewSign == LimitCount )
    return 10002;
  v6 = std::vector<std::vector<MemChrBag>>::operator[](&m_vEquipQingYiReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_EQUIP_QING_YI_GIFT) )
    return 10002;
  v8 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v8, 1125, nNewSign);
  SendIconState(, player);
  return 0;
}



int32_t CFestivalDoubleEleven::GetFriendQingYiGift(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t LimitCount; // eax
  std::vector<MemChrBag> *v7; // rbx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v9; // rax
  int nFriendQingYi; // [rsp+24h] [rbp-1Ch]
  int nNewSign; // [rsp+2Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_FRIEND_QING_YI) )
    return 10002;
  if ( nIndex < 0 || nIndex >= m_nFriendQingYiSize )
    return 10002;
  OperateLimit = Player::GetOperateLimit(player);
  nFriendQingYi = CExtOperateLimit::GetLimitCount(OperateLimit, 1624);
  if ( *std::vector<int>::operator[](&m_vFriendQingYiLimit, nIndex) > nFriendQingYi )
    return 10002;
  v5 = Player::GetOperateLimit(player);
  LimitCount = CExtOperateLimit::GetLimitCount(v5, 1625);
  nNewSign = LimitCount | (1 << nIndex);
  if ( nNewSign == LimitCount )
    return 10002;
  v7 = std::vector<std::vector<MemChrBag>>::operator[](&m_vFriendQingYiReward, nIndex);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_FRIEND_QING_YI_GIFT) )
    return 10002;
  v9 = Player::GetOperateLimit(player);
  CExtOperateLimit::UpdateLimitCount(v9, 1625, nNewSign);
  SendIconState(, player);
  return 0;
}



void CFestivalDoubleEleven::UpdateMonsterScore(
        CFestivalDoubleEleven * this,
        Player *player,
        int32_t nCount)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t Times; // [rsp+2Ch] [rbp-4h]

  if ( player && IsInTime() )
  {
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_RANK) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1626, nCount);
      updateBossScoreRank(, player);
    }
    if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
    {
      v4 = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(v4, 2095, nCount);
      Times = Player::getRecord(player, 2096);
      if ( GetScoreCanDrawTime(, player) > Times )
        SendIconState(, player);
    }
  }
}



void CFestivalDoubleEleven::loadBossScoreRank()
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  FestivalRank *v3; // rbx
  const char *StringValue; // rbx
  FestivalRank *v5; // rax
  FestivalRank *v6; // rbx
  FestivalRank *v7; // rbx
  std::vector<FestivalRank> *v9; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-C0h] BYREF
  FestivalRankVector vRank; // [rsp+40h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-70h] BYREF
  FestivalRank p___x; // [rsp+80h] [rbp-50h] BYREF
  char __k; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nIndex; // [rsp+BCh] [rbp-14h]

  v1 = Answer::DBPool::instance();
  Answer::MySqlDBGuard db(v1);
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_double_eleven_rank` WHERE `type`=43 ORDER BY `count` DESC,`time`");
  Answer::MySqlQuery result(v2);
  nIndex = 0;
  std::vector<FestivalRank>::vector(&vRank);
  FestivalRank::FestivalRank(&p___x);
  std::vector<FestivalRank>::resize(&vRank, m_BossScoreRankSize, &p___x);
  FestivalRank::~FestivalRank(&p___x);
  while ( !Answer::MySqlQuery::eof(&result) && m_BossScoreRankSize > nIndex )
  {
    v3 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v3->nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8D8B2F);
    v5 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    std::string::operator=(&v5->strName, StringValue);
    v6 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v6->nScore = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    v7 = std::vector<FestivalRank>::operator[](&vRank, nIndex);
    v7->nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    ++nIndex;
    Answer::MySqlQuery::nextRow(&result);
  }
  __k = 0;
  v9 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &__k);
  std::vector<FestivalRank>::operator=(v9, &vRank);
  std::vector<FestivalRank>::~vector(&vRank);
  ;
  ;
}



void CFestivalDoubleEleven::updateBossScoreRank(Player *player)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v3; // rax
  int *v4; // rax
  int v5; // ebx
  CExtOperateLimit *v6; // rax
  std::vector<MemChrBag> *v7; // r13
  int32_t v8; // r12d
  DBService *v9; // rax
  size_t v10; // rbx
  std::vector<FestivalRank> *v11; // rax
  FestivalRank *v12; // rax
  int v13; // ebx
  size_t v14; // rbx
  std::vector<FestivalRank> *v15; // rax
  FestivalRank *v16; // rax
  int v17; // ebx
  size_t v18; // rbx
  std::vector<FestivalRank> *v19; // rax
  FestivalRank *v20; // rbx
  size_t v21; // r12
  std::vector<FestivalRank> *v22; // rax
  FestivalRank *v23; // rax
  size_t v24; // rbx
  std::vector<FestivalRank> *v25; // rax
  size_t v26; // rbx
  std::vector<FestivalRank> *v27; // rax
  FestivalRank *v28; // rax
  size_t v29; // rbx
  std::vector<FestivalRank> *v30; // rax
  FestivalRank *v31; // rax
  size_t v32; // rbx
  std::vector<FestivalRank> *v33; // rax
  FestivalRank *v34; // rax
  size_t v35; // rbx
  std::vector<FestivalRank> *v36; // rax
  FestivalRank *v37; // rbx
  size_t v38; // rbx
  std::vector<FestivalRank> *v39; // rax
  Answer::MutexGuard lock_2; // [rsp+20h] [rbp-B0h] BYREF
  Answer::MutexGuard lock_1; // [rsp+30h] [rbp-A0h] BYREF
  Answer::MutexGuard lock_0; // [rsp+40h] [rbp-90h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-80h] BYREF
  std::string strName; // [rsp+60h] [rbp-70h] BYREF
  int8_t connid; // [rsp+6Fh] [rbp-61h] BYREF
  std::string Param; // [rsp+70h] [rbp-60h] BYREF
  char v47; // [rsp+87h] [rbp-49h] BYREF
  int32_t nScore; // [rsp+88h] [rbp-48h]
  int32_t nRecord; // [rsp+8Ch] [rbp-44h]
  CharId_t nCharId; // [rsp+90h] [rbp-40h]
  int32_t nRankIndex; // [rsp+9Ch] [rbp-34h]
  int16_t nOldIndex; // [rsp+A2h] [rbp-2Eh]
  int32_t k; // [rsp+A4h] [rbp-2Ch]
  int16_t i; // [rsp+AAh] [rbp-26h]
  int16_t i_0; // [rsp+ACh] [rbp-24h]
  int16_t i_1; // [rsp+AEh] [rbp-22h]

  if ( player )
  {
    OperateLimit = Player::GetOperateLimit(player);
    nScore = CExtOperateLimit::GetLimitCount(OperateLimit, 1626);
    v3 = Player::GetOperateLimit(player);
    nRecord = CExtOperateLimit::GetLimitCount(v3, 1627);
    connid = Player::getConnId(player);
    nCharId = Player::getCid(player);
    Player::getName((const Player *const)&strName);
    for ( k = 0; m_GetReardSize > k; ++k )
    {
      if ( k + 1 > nRecord )
      {
        v4 = std::vector<int>::operator[](&m_vBossScoreiLimit, k);
        if ( *v4 > nScore )
          break;
        v5 = k + 1;
        v6 = Player::GetOperateLimit(player);
        CExtOperateLimit::UpdateLimitCount(v6, 1627, v5);
        std::allocator<char>::allocator(&v47);
        std::string::string(&Param, &byte_8D8B2F, &v47);
        v7 = std::vector<std::vector<MemChrBag>>::operator[](&m_vBossScoreReward, k);
        v8 = *std::vector<int>::operator[](&m_vGetBossScoreMail, k);
        LOBYTE(v5) = connid;
        v9 = DBService::instance();
        DBService::OnSendSysMail(v9, v5, nCharId, v8, v7, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BOSS_RANK, &Param, 0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(&v47);
      }
    }
    checkBossScoreRankInvalid(, connid);
    nRankIndex = -1;
    for ( i = 0; i < m_BossScoreRankSize; ++i )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &m_lock);
      v10 = i;
      v11 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
      v12 = std::vector<FestivalRank>::operator[](v11, v10);
      if ( v12->nScore >= nScore )
      {
        v13 = 1;
      }
      else
      {
        nRankIndex = i;
        v13 = 0;
      }
      Answer::MutexGuard::~MutexGuard(&lock_0);
      if ( !v13 )
        break;
    }
    if ( nRankIndex >= 0 )
    {
      nOldIndex = m_BossScoreRankSize - 1;
      for ( i_0 = 0; i_0 < m_BossScoreRankSize; ++i_0 )
      {
        Answer::MutexGuard::MutexGuard(&lock_1, &m_lock);
        v14 = i_0;
        v15 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
        v16 = std::vector<FestivalRank>::operator[](v15, v14);
        if ( v16->nCharId == nCharId )
        {
          nOldIndex = i_0;
          v17 = 0;
        }
        else
        {
          v17 = 1;
        }
        Answer::MutexGuard::~MutexGuard(&lock_1);
        if ( !v17 )
          break;
      }
      if ( nOldIndex < nRankIndex )
        nRankIndex = nOldIndex;
      if ( nOldIndex != nRankIndex )
      {
        for ( i_1 = nOldIndex; i_1 > nRankIndex; --i_1 )
        {
          Answer::MutexGuard::MutexGuard(&lock_2, &m_lock);
          v18 = i_1 - 1;
          v19 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
          v20 = std::vector<FestivalRank>::operator[](v19, v18);
          v21 = i_1;
          v22 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
          v23 = std::vector<FestivalRank>::operator[](v22, v21);
          FestivalRank::operator=(v23, v20);
          v24 = i_1;
          v25 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
          std::vector<FestivalRank>::operator[](v25, v24)->bChange = 1;
          Answer::MutexGuard::~MutexGuard(&lock_2);
        }
      }
      Answer::MutexGuard::MutexGuard(&lock, &m_lock);
      v26 = nRankIndex;
      v27 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
      v28 = std::vector<FestivalRank>::operator[](v27, v26);
      v28->nCharId = nCharId;
      v29 = nRankIndex;
      v30 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
      v31 = std::vector<FestivalRank>::operator[](v30, v29);
      std::string::operator=(&v31->strName, &strName);
      v32 = nRankIndex;
      v33 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
      v34 = std::vector<FestivalRank>::operator[](v33, v32);
      v34->nScore = nScore;
      v35 = nRankIndex;
      v36 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
      v37 = std::vector<FestivalRank>::operator[](v36, v35);
      v37->nTime = Unit::getNow(player);
      v38 = nRankIndex;
      v39 = std::map<signed char,std::vector<FestivalRank>>::operator[](&m_mBossScoreRank, &connid);
      std::vector<FestivalRank>::operator[](v39, v38)->bChange = 1;
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    std::string::~string(&strName);
  }
}



void CFestivalDoubleEleven::updateBossScoreRank(
        CFestivalDoubleEleven * this,
        int8_t connid,
        int16_t nIndex,
        const FestivalRank * info)
{
  std::vector<FestivalRank> *v4; // rax
  std::vector<FestivalRank> *v5; // rax
  std::vector<FestivalRank> *v6; // rax
  std::vector<FestivalRank> *v8; // rax
  FestivalRank *v9; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+18h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  connida[0] = connid;
  if ( nIndex >= 0 && nIndex < thisa->m_BossScoreRankSize )
  {
    CFestivalDoubleEleven::checkBossScoreRankInvalid(thisa, connida[0]);
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_lock);
    v4 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida);
    if ( std::vector<FestivalRank>::operator[](v4, nIndex)->nScore < info->nScore
      || (v5 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida),
          std::vector<FestivalRank>::operator[](v5, nIndex)->nScore == info->nScore)
      && (v6 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida),
          std::vector<FestivalRank>::operator[](v6, nIndex)->nTime < info->nTime) )
    {
      v8 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida);
      v9 = std::vector<FestivalRank>::operator[](v8, nIndex);
      FestivalRank::operator=(v9, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



void CFestivalDoubleEleven::checkBossScoreRankInvalid(int8_t connid)
{
  std::vector<FestivalRank> *v2; // rax
  int8_t connida[4]; // [rsp+4h] [rbp-9Ch] BYREF
  CFestivalDoubleEleven *thisa; // [rsp+8h] [rbp-98h]
  FestivalRankVector vRank; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+30h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+50h] [rbp-50h] BYREF
  FestivalRank p___x; // [rsp+60h] [rbp-40h] BYREF

  thisa = this;
  connida[0] = connid;
  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  iter._M_node = std::map<signed char,std::vector<FestivalRank>>::find(&m_mBossScoreRank, connida)._M_node;
  __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&thisa->m_mBossScoreRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator==(&iter, &__x) )
  {
    std::vector<FestivalRank>::vector(&vRank);
    FestivalRank::FestivalRank(&p___x);
    std::vector<FestivalRank>::resize(&vRank, thisa->m_BossScoreRankSize, &p___x);
    FestivalRank::~FestivalRank(&p___x);
    v2 = std::map<signed char,std::vector<FestivalRank>>::operator[](&thisa->m_mBossScoreRank, connida);
    std::vector<FestivalRank>::operator=(v2, &vRank);
    std::vector<FestivalRank>::~vector(&vRank);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::checkBossScoreRank()
{
  FestivalRank *v1; // r12
  int16_t v2; // r13
  int8_t v3; // bl
  DBService *v4; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+30h] [rbp-40h] BYREF
  int8_t connid; // [rsp+3Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+40h] [rbp-30h]
  int16_t i; // [rsp+4Eh] [rbp-22h]

  Answer::MutexGuard::MutexGuard(&lock, &m_lock);
  for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mBossScoreRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mBossScoreRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
      break;
    connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
    vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
    for ( i = 0; i < m_BossScoreRankSize && std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0; ++i )
    {
      if ( std::vector<FestivalRank>::operator[](vRank, i)->bChange )
      {
        std::vector<FestivalRank>::operator[](vRank, i)->bChange = 0;
        v1 = std::vector<FestivalRank>::operator[](vRank, i);
        v2 = i;
        v3 = connid;
        v4 = DBService::instance();
        DBService::SaveDoubleElevenRank(v4, v3, 43, 0, v2, v1);
      }
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}



void CFestivalDoubleEleven::sendBossScoreRankMail()
{
  GameService *v1; // rax
  std::vector<MemChrBag> *v2; // r14
  int32_t v3; // r13d
  CharId_t nCharId; // r12
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > iter; // [rsp+20h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,std::vector<FestivalRank> > > __x; // [rsp+40h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Eh] [rbp-32h] BYREF
  int8_t connid; // [rsp+5Fh] [rbp-31h]
  FestivalRankVector *vRank; // [rsp+60h] [rbp-30h]
  int16_t i; // [rsp+6Eh] [rbp-22h]

  v1 = GameService::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    Answer::MutexGuard::MutexGuard(&lock, &m_lock);
    for ( iter._M_node = std::map<signed char,std::vector<FestivalRank>>::begin(&m_mBossScoreRank)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,std::vector<FestivalRank>>::end(&m_mBossScoreRank)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator!=(&iter, &__x) )
        break;
      connid = std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->first;
      vRank = &std::_Rb_tree_iterator<std::pair<signed char const,std::vector<FestivalRank>>>::operator->(&iter)->second;
      for ( i = 0; i < m_BossScoreRewardSize; ++i )
      {
        if ( std::vector<FestivalRank>::operator[](vRank, i)->nCharId > 0 )
        {
          std::allocator<char>::allocator(&v11);
          std::string::string(&Param, &byte_8D8B2F, &v11);
          v2 = std::vector<std::vector<MemChrBag>>::operator[](&m_vBossScoreRankReward, i);
          v3 = *std::vector<int>::operator[](&m_vBossScoreRankMail, i);
          nCharId = std::vector<FestivalRank>::operator[](vRank, i)->nCharId;
          v5 = connid;
          v6 = DBService::instance();
          DBService::OnSendSysMail(v6, v5, nCharId, v3, v2, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_BOSS_RANK, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v11);
        }
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}



int8_t CFestivalDoubleEleven::GetChouJiangType()
{
  int v1; // eax

  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG) )
    return m_ChouJiangType;
  else
    LOBYTE(v1) = 0;
  return v1;
}



int32_t CFestivalDoubleEleven::GetChouJiangSpecialTime()
{
  if ( IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_CHOU_JIANG) )
    return m_ChouJiangCount;
  else
    return 0;
}



int32_t CFestivalDoubleEleven::GetScoreCanDrawTime(Player *pPlayer)
{
  int32_t Count; // [rsp+1Ch] [rbp-14h]
  int Score; // [rsp+20h] [rbp-10h]
  int Recharge; // [rsp+24h] [rbp-Ch]
  int32_t i; // [rsp+28h] [rbp-8h]
  int32_t i_0; // [rsp+2Ch] [rbp-4h]

  if ( !pPlayer )
    return 0;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
    return 0;
  Count = 0;
  Score = Player::getRecord(pPlayer, 2095);
  for ( i = 0; m_nScoreSize > i; ++i )
  {
    if ( *std::vector<int>::operator[](&m_vScoreLimit, i) <= Score )
      ++Count;
  }
  Recharge = Player::GetTodayPayGold(pPlayer);
  for ( i_0 = 0; m_nDailyRechargeDrawSize > i_0; ++i_0 )
  {
    if ( *std::vector<int>::operator[](&m_nDailyRechargeDrawLimit, i_0) <= Recharge )
      ++Count;
  }
  return Count;
}



int32_t CFestivalDoubleEleven::OnRandScoreDrawItem(Player *pPlayer)
{
  int32_t v2; // ebx
  int32_t Record; // ebx
  CExtCharBag *Bag; // rax
  RateItem *v5; // rbx
  RateItem *v6; // rax
  Answer::Random *v7; // rax
  std::pair<const int,RateItem> *v8; // rax
  std::pair<const int,RateItem> *v9; // rax
  int8_t ConnId; // bl
  GameService *v11; // rax
  std::pair<const int,RateItem> *v12; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v15; // bl
  GameService *v16; // rax
  std::pair<const int,RateItem> *v17; // rax
  CExtCharBag *v18; // rax
  CExtOperateLimit *OperateLimit; // rax
  int8_t v20; // bl
  GameService *v21; // rax
  CharId_t Cid; // rax
  uint32_t v23; // eax
  int8_t v24; // bl
  GameService *v25; // rax
  RateItemMap items; // [rsp+10h] [rbp-E0h] BYREF
  MemChrBag bagItem; // [rsp+40h] [rbp-B0h] BYREF
  int32_t i; // [rsp+6Ch] [rbp-84h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,RateItem> > it; // [rsp+70h] [rbp-80h] BYREF
  RateItem stu; // [rsp+80h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,RateItem> > __x; // [rsp+A0h] [rbp-50h] BYREF
  std::string val; // [rsp+B0h] [rbp-40h] BYREF
  int32_t OldRecord; // [rsp+C0h] [rbp-30h]
  int32_t MaxRate; // [rsp+C4h] [rbp-2Ch]
  int32_t nRand; // [rsp+C8h] [rbp-28h]
  int32_t NewRecord; // [rsp+CCh] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+D0h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+D8h] [rbp-18h]

  if ( !pPlayer )
    return 2;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_BOSS_SCORE_DRAW) )
    return 2;
  Record = Player::getRecord(pPlayer, 2096);
  if ( Record >= GetScoreCanDrawTime(, pPlayer) )
    return 2;
  Bag = Player::GetBag(pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  OldRecord = Player::getRecord(pPlayer, 1628);
  std::map<int,RateItem>::map(&items);
  MaxRate = 0;
  for ( i = 0; m_nRewardSize > i; ++i )
  {
    if ( ((OldRecord >> i) & 1) == 0 )
    {
      v5 = std::map<int,RateItem>::operator[](&items, &i);
      *v5 = *std::vector<RateItem>::operator[](&m_vBossScoreDrawReward, i);
      v6 = std::vector<RateItem>::operator[](&m_vBossScoreDrawReward, i);
      MaxRate += v6->nRate;
    }
  }
  if ( MaxRate > 0 )
  {
    memset(&stu, 0, sizeof(stu));
    v7 = Answer::Random::instance();
    nRand = Answer::Random::generate(v7, 1, MaxRate);
    for ( it._M_node = std::map<int,RateItem>::begin(&items)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,RateItem>::end(&items)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator!=(&it, &__x) )
        break;
      v8 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
      if ( v8->second.nRate > nRand )
      {
        stu = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it)->second;
        v9 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
        NewRecord = OldRecord | (1 << v9->first);
        Player::updateRecord(pPlayer, 1628, NewRecord);
        ConnId = Player::getConnId(pPlayer);
        v11 = GameService::instance();
        packet = GameService::popNetpacket(v11, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDFu);
        if ( packet )
        {
          v12 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v12->first);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(pPlayer);
          v15 = Player::getConnId(pPlayer);
          v16 = GameService::instance();
          GameService::sendPacketTo(v16, v15, GateIndex, packet);
        }
        break;
      }
      v17 = std::_Rb_tree_iterator<std::pair<int const,RateItem>>::operator->(&it);
      nRand -= v17->second.nRate;
    }
    if ( stu.nItemId > 0 && stu.nItemCount > 0 )
    {
      *(&bagItem.endTime + 1) = 0;
      bagItem.srcId = 0;
      *(_DWORD *)&bagItem.itemClass = (unsigned __int8)stu.nItemClass;
      bagItem.itemCount = stu.nItemCount;
      bagItem.itemId = stu.nItemId;
      *(_QWORD *)&bagItem.bind = (unsigned __int8)stu.nBind;
      v18 = Player::GetBag(pPlayer);
      CExtCharBag::AddItem(v18, &bagItem, ITEM_CHANGE_REASON::ICR_DOUBLE_ELEVEN_SOCRE_DRAW);
      OperateLimit = Player::GetOperateLimit(pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 2096, 1);
      if ( stu.nGongGaoId > 0 )
      {
        v20 = Player::getConnId(pPlayer);
        v21 = GameService::instance();
        packet_0 = GameService::popNetpacket(v21, v20, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( packet_0 )
        {
          Answer::NetPacket::writeInt32(packet_0, stu.nGongGaoId);
          Cid = Player::getCid(pPlayer);
          Answer::NetPacket::writeInt64(packet_0, Cid);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet_0, &val);
          std::string::~string(&val);
          Answer::NetPacket::writeInt32(packet_0, bagItem.itemId);
          Answer::NetPacket::writeInt8(packet_0, bagItem.itemClass);
          Answer::NetPacket::writeInt32(packet_0, bagItem.itemCount);
          v23 = Answer::NetPacket::getWOffset(packet_0);
          Answer::NetPacket::setSize(packet_0, v23);
          v24 = Player::getConnId(pPlayer);
          v25 = GameService::instance();
          GameService::worldBroadcast(v25, v24, packet_0);
        }
      }
      SendIconState(, pPlayer);
      v2 = 0;
    }
    else
    {
      v2 = 2;
    }
  }
  else
  {
    v2 = 2;
  }
  std::map<int,RateItem>::~map(&items);
  return v2;
}



int32_t CFestivalDoubleEleven::GetFaBaoCritBackItem(
        CFestivalDoubleEleven * this,
        Player *player,
        int8_t nType)
{
  int32_t v4; // ebx
  CExtCharBag *Bag; // rax
  MemChrBag item; // [rsp+20h] [rbp-40h] BYREF
  int32_t OldRecord; // [rsp+48h] [rbp-18h]
  int32_t NewRecord; // [rsp+4Ch] [rbp-14h]

  if ( !player )
    return 10002;
  if ( !IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
    return 10002;
  if ( nType < 0 || nType >= m_nSize )
    return 10002;
  OldRecord = Player::getRecord(player, 1629);
  NewRecord = OldRecord | (1 << nType);
  if ( OldRecord == NewRecord )
    return 10002;
  v4 = *std::vector<int>::operator[](&m_NeedValue, nType);
  if ( v4 > Player::getRecord(player, 1630) )
    return 10002;
  item = *std::vector<MemChrBag>::operator[](&m_BackItem, nType);
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::IDCR_DOUBLE_ELEVEN_FA_BAO_CRIT_BACK) )
    return 10002;
  Player::updateRecord(player, 1629, NewRecord);
  SendIconState(, player);
  return 0;
}



void CFestivalDoubleEleven::AddFaBaoValue(
        CFestivalDoubleEleven * this,
        Player *pPlayer,
        int32_t Type,
        int32_t Value)
{
  CExtOperateLimit *OperateLimit; // rax
  bool CanOldGet; // [rsp+2Eh] [rbp-2h]
  bool CanNewGet; // [rsp+2Fh] [rbp-1h]

  if ( pPlayer )
  {
    if ( Value > 0 && IsInTime(, FESTIVAL_ACTIVITY_TYPE::FAT_FA_BAO_BACK) )
    {
      CanOldGet = canGetFaBaoBack(, pPlayer);
      if ( m_FaBaoType == Type )
      {
        OperateLimit = Player::GetOperateLimit(pPlayer);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1630, Value);
        CanNewGet = canGetFaBaoBack(, pPlayer);
        if ( !CanOldGet && CanNewGet )
          SendIconState(, pPlayer);
      }
    }
  }
}




