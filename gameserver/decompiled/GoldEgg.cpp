// Decompiled methods for class: GoldEgg
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl GoldEgg::~GoldEgg(GoldEgg *const this)
{
  GoldEgg::~GoldEgg(this);
  operator delete(this);
}


#####################################
int32_t __cdecl GoldEgg::effect(GoldEgg *const this, Player *const launcher, Unit *const target, int32_t *const count)
{
  int32_t v4; // ebx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  int32_t v8; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int64_t nId; // r12
  int64_t nCostMoney; // rbx
  CExtCurrency *Currency; // rax
  int32_t v13; // ebx
  CExtOperateLimit *v14; // rax
  Job_t nJob; // bl
  CfgData *v17; // rax
  int32_t ServerStartDayZeroTime; // eax
  int32_t v19; // ebx
  bool v20; // al
  int32_t nEndDate; // r12d
  int32_t nStartDate; // ebx
  CTimer *v23; // rax
  const CfgGoldEggItem *v24; // rax
  const CfgGoldEggItem *v25; // rax
  Answer::Random *v26; // rax
  CfgGoldEggItem *v27; // rax
  int32_t nLimitTime; // ebx
  CfgData *v29; // rax
  const CfgLimitTimeTable *LimitTimeTable; // rax
  CfgGoldEggItem *v31; // rax
  int8_t ConnId; // bl
  GameService *v33; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v36; // bl
  GameService *v37; // rax
  CExtCharBag *Bag; // rax
  MemChrBag item; // [rsp+20h] [rbp-B0h] BYREF
  std::_List_iterator<CfgGoldEggItem> iter_0; // [rsp+40h] [rbp-90h] BYREF
  std::_List_const_iterator<CfgGoldEggItem> iter; // [rsp+50h] [rbp-80h] BYREF
  CfgGoldEggItemList tlst; // [rsp+60h] [rbp-70h] BYREF
  std::_List_const_iterator<CfgGoldEggItem> __x; // [rsp+70h] [rbp-60h] BYREF
  std::_List_iterator<CfgGoldEggItem> v45; // [rsp+80h] [rbp-50h] BYREF
  std::string val; // [rsp+90h] [rbp-40h] BYREF
  int32_t bagslot; // [rsp+A0h] [rbp-30h]
  int32_t nNowTime; // [rsp+A4h] [rbp-2Ch]
  int32_t nSumProbability; // [rsp+A8h] [rbp-28h]
  int32_t nRand; // [rsp+ACh] [rbp-24h]
  int32_t nBroadcast; // [rsp+B0h] [rbp-20h]
  bool bNormal; // [rsp+B7h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+B8h] [rbp-18h]

  if ( !this->m_pCfgItem || *count != 1 )
    return 10002;
  bagslot = Player::getFirstFreeSlot(launcher);
  if ( bagslot >= 0 )
  {
    v8 = this->m_pCfgItem->nGroupId + 6000;
    OperateLimit = Player::GetOperateLimit(launcher);
    if ( CExtOperateLimit::GetLimitCount(OperateLimit, v8) >= this->m_pCfgItem->nOpenTimes )
    {
      if ( !Player::DecCurrency(
              launcher,
              CURRENCY_TYPE::CURRENCY_GOLD,
              this->m_pCfgItem->nCostGold,
              CURRENCY_CHANGE_REASON::GCR_OPEN_GOLD_EGG,
              this->m_pCfgItem->nId) )
        return 10002;
    }
    else
    {
      nId = this->m_pCfgItem->nId;
      nCostMoney = this->m_pCfgItem->nCostMoney;
      Currency = Player::GetCurrency(launcher);
      if ( !CExtCurrency::DecMoneyAndNoBind(Currency, nCostMoney, CURRENCY_CHANGE_REASON::MCR_OPEN_GOLD_EGG, nId) )
        return 10002;
      v13 = this->m_pCfgItem->nGroupId + 6000;
      v14 = Player::GetOperateLimit(launcher);
      CExtOperateLimit::AddLimitCount(v14, v13, 1);
    }
    nNowTime = Unit::getNow(launcher);
    nSumProbability = 0;
    std::list<CfgGoldEggItem>::list(&tlst);
    for ( iter._M_node = std::list<CfgGoldEggItem>::begin(&this->m_pCfgItem->lstItem)._M_node;
          ;
          std::_List_const_iterator<CfgGoldEggItem>::operator++(&iter) )
    {
      __x._M_node = std::list<CfgGoldEggItem>::end(&this->m_pCfgItem->lstItem)._M_node;
      if ( !std::_List_const_iterator<CfgGoldEggItem>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nJob )
      {
        nJob = std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nJob;
        if ( nJob != Player::getJob(launcher) )
          continue;
      }
      bNormal = 1;
      if ( std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nMinute > 0 )
      {
        bNormal = 0;
        v17 = Answer::Singleton<CfgData>::instance();
        ServerStartDayZeroTime = CfgData::getServerStartDayZeroTime(v17, SERVER_TYPE::SVT_NORMAL);
        v19 = nNowTime - ServerStartDayZeroTime;
        if ( v19 <= std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nMinute )
          goto LABEL_28;
      }
      v20 = std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nStartDate > 0
         && std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nEndDate > 0;
      if ( v20
        && (bNormal = 0,
            nEndDate = std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nEndDate,
            nStartDate = std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter)->nStartDate,
            v23 = Answer::Singleton<CTimer>::instance(),
            CTimer::BetweenDate(v23, nStartDate, nEndDate))
        || bNormal )
      {
LABEL_28:
        v24 = std::_List_const_iterator<CfgGoldEggItem>::operator->(&iter);
        nSumProbability += v24->nProbability;
        v25 = std::_List_const_iterator<CfgGoldEggItem>::operator*(&iter);
        std::list<CfgGoldEggItem>::push_back(&tlst, v25);
      }
    }
    memset(&item, 0, sizeof(item));
    v26 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v26, 1, nSumProbability);
    nBroadcast = 0;
    for ( iter_0._M_node = std::list<CfgGoldEggItem>::begin(&tlst)._M_node;
          ;
          std::_List_iterator<CfgGoldEggItem>::operator++(&iter_0) )
    {
      v45._M_node = std::list<CfgGoldEggItem>::end(&tlst)._M_node;
      if ( !std::_List_iterator<CfgGoldEggItem>::operator!=(&iter_0, &v45) )
        break;
      v27 = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0);
      if ( v27->nProbability >= nRand )
      {
        item.itemId = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nItemId;
        item.itemClass = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nItemClass;
        item.itemCount = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nItemCount;
        item.bind = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nBind;
        if ( std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nLimitTime > 0 )
        {
          nLimitTime = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nLimitTime;
          v29 = Answer::Singleton<CfgData>::instance();
          LimitTimeTable = CfgData::GetLimitTimeTable(v29);
          item.endTime = CfgLimitTimeTable::GetLimitTime(LimitTimeTable, nLimitTime);
        }
        nBroadcast = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0)->nBroadcast;
        break;
      }
      v31 = std::_List_iterator<CfgGoldEggItem>::operator->(&iter_0);
      nRand -= v31->nProbability;
    }
    if ( nBroadcast > 0 )
    {
      ConnId = Player::getConnId(launcher);
      v33 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v33, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, nBroadcast);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Cid = Player::getCid(launcher);
        Answer::NetPacket::writeInt64(packet, Cid);
        Answer::NetPacket::writeInt8(packet, item.itemClass);
        Answer::NetPacket::writeInt32(packet, item.itemId);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v36 = Player::getConnId(launcher);
        v37 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v37, v36, packet);
      }
    }
    Bag = Player::GetBag(launcher);
    CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::ICR_GOLD_EGG_OPEN);
    v4 = 0;
    std::list<CfgGoldEggItem>::~list(&tlst);
  }
  else
  {
    GateIndex = Player::getGateIndex(launcher);
    v6 = Player::getConnId(launcher);
    v7 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v7, v6, GateIndex, 0x59u, 10054, 0);
  }
  return v4;
}


#####################################
bool __cdecl GoldEgg::parseEffect(GoldEgg *const this, int32_t id, const std::string *const strEffect)
{
  CfgData *v3; // rax
  const CfgGoldEggTable *GoldEggTable; // rax

  v3 = Answer::Singleton<CfgData>::instance();
  GoldEggTable = CfgData::GetGoldEggTable(v3);
  this->m_pCfgItem = CfgGoldEggTable::GetGoldEgg(GoldEggTable, id);
  return this->m_pCfgItem != 0;
}


