// Decompiled methods for class: ScoreShop
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl ScoreShop::~ScoreShop(ScoreShop *const this)
{
  ScoreShop::~ScoreShop(this);
  operator delete(this);
}


#####################################
void __cdecl ScoreShop::OnLoadFromDB(ScoreShop *const this, const PlayerDBData *const dbData)
{
  std::map<int,int>::operator=(&this->m_ItemLimit, &dbData->m_ScoreShopData.m_LiMitMap);
}


#####################################
void __cdecl ScoreShop::OnSaveToDB(ScoreShop *const this, PlayerDBData *const dbData)
{
  std::map<int,int>::operator=(&dbData->m_ScoreShopData.m_LiMitMap, &this->m_ItemLimit);
}


#####################################
void __cdecl ScoreShop::GetInterestsProtocol(ScoreShop *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 451;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 453;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl ScoreShop::DispatchNetDatas(ScoreShop *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 451 )
    return ScoreShop::OnBuyItem(this, inPacket);
  if ( nProcId != 453 )
    return 2;
  ScoreShop::SendLimitInfo(this, 0);
  return 0;
}


#####################################
int32_t __cdecl ScoreShop::OnBuyItem(ScoreShop *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int8_t itemClass; // r13
  int32_t itemId; // r12d
  CfgData *v6; // rax
  CExtCharBag *Bag; // rax
  ItemData *v8; // rax
  CExtCharBag *v9; // rax
  int v10; // r12d
  CExtCharBag *v11; // rax
  int64_t v12; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v16; // rax
  MemChrBag item; // [rsp+10h] [rbp-B0h] BYREF
  std::_List_iterator<ItemData> it; // [rsp+30h] [rbp-90h] BYREF
  ItemDataList CostItems; // [rsp+40h] [rbp-80h] BYREF
  MemChrBagVector Items; // [rsp+50h] [rbp-70h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+70h] [rbp-50h] BYREF
  int32_t Index; // [rsp+80h] [rbp-40h]
  int32_t Count; // [rsp+84h] [rbp-3Ch]
  ScoreShopCfg *pShop; // [rsp+88h] [rbp-38h]
  int32_t nLayNum; // [rsp+94h] [rbp-2Ch]
  int32_t CostValue; // [rsp+98h] [rbp-28h]
  int32_t Limit; // [rsp+9Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt32(inPacket);
  Count = Answer::NetPacket::readInt32(inPacket);
  if ( Count <= 0 )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  pShop = CfgData::GetScoreShopCfg(v3, Index);
  if ( !pShop )
    return 2;
  itemClass = pShop->Item.itemClass;
  itemId = pShop->Item.itemId;
  v6 = Answer::Singleton<CfgData>::instance();
  nLayNum = CfgData::getOverlay(v6, itemId, itemClass);
  if ( Count * pShop->Item.itemCount > nLayNum )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  if ( pShop->CostType < 0 || pShop->CostValue <= 0 )
    return 2;
  if ( pShop->LimitType > 0 )
  {
    Limit = ScoreShop::GetLimitCount(this, Index);
    if ( Count + Limit > pShop->LimitCount )
      return 2;
  }
  CostValue = Count * pShop->CostValue;
  if ( Player::GetCurrency(this->m_pPlayer, (const CURRENCY_TYPE)pShop->CostType) < CostValue )
    return 2;
  if ( !std::list<ItemData>::size(&pShop->CostItems) )
    goto LABEL_38;
  std::list<ItemData>::list(&CostItems, &pShop->CostItems);
  for ( it._M_node = std::list<ItemData>::begin(&CostItems)._M_node; ; std::_List_iterator<ItemData>::operator++(&it, 0) )
  {
    __x._M_node = std::list<ItemData>::end(&CostItems)._M_node;
    if ( !std::_List_iterator<ItemData>::operator!=(&it, &__x) )
      break;
    v8 = std::_List_iterator<ItemData>::operator->(&it);
    v8->m_nCount *= Count;
  }
  v9 = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::RemoveItem(v9, &CostItems, ITEM_CHANGE_REASON::ICR_SCORE_SHOP_COST) )
  {
    v2 = 2;
    v10 = 0;
  }
  else
  {
    v10 = 1;
  }
  std::list<ItemData>::~list(&CostItems);
  if ( v10 )
  {
LABEL_38:
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            (const CURRENCY_TYPE)pShop->CostType,
            CostValue,
            CURRENCY_CHANGE_REASON::SCR_BUY_ITEM,
            Index) )
    {
      return 2;
    }
    else
    {
      memset(&item, 0, sizeof(item));
      item = pShop->Item;
      item.itemCount *= Count;
      std::vector<MemChrBag>::vector(&Items);
      std::vector<MemChrBag>::push_back(&Items, &item);
      v11 = Player::GetBag(this->m_pPlayer);
      CExtCharBag::AddItem(v11, &Items, ITEM_CHANGE_REASON::ICR_SCORE_SHOP_GET);
      if ( pShop->LimitType > 0 )
      {
        ScoreShop::AddLimitCount(this, Index, Count);
        ScoreShop::SendLimitInfo(this, Index);
      }
      if ( pShop->IsRecord > 0 )
        ScoreShop::AddServerRecord(this, &item);
      v12 = Index;
      Proc = Answer::NetPacket::getProc(inPacket);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v16 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v16, ConnId, GateIndex, Proc, v12);
      v2 = 0;
      std::vector<MemChrBag>::~vector(&Items);
    }
  }
  return v2;
}


#####################################
void __cdecl ScoreShop::AddServerRecord(ScoreShop *const this, MemChrBag *const Item)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int16_t GateIndex; // ax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_PROC, 0x4EBAu);
    if ( packet )
    {
      if ( this->m_pPlayer )
      {
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        Answer::NetPacket::writeInt32(packet, GateIndex);
        Cid = Player::getCid(this->m_pPlayer);
        Answer::NetPacket::writeInt64(packet, Cid);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Answer::NetPacket::writeInt8(packet, Item->itemClass);
        Answer::NetPacket::writeInt32(packet, Item->itemId);
        Answer::NetPacket::writeInt32(packet, Item->itemCount);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v7 = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacket(v8, v7, packet);
      }
    }
  }
}


#####################################
void __cdecl ScoreShop::SendLimitInfo(ScoreShop *const this, int32_t Index)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  std::pair<const int,int> *v6; // rax
  std::pair<const int,int> *v7; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  int32_t Indexa; // [rsp+4h] [rbp-6Ch] BYREF
  ScoreShop *thisa; // [rsp+8h] [rbp-68h]
  std::_Rb_tree_iterator<std::pair<const int,int> > eiter; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+40h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+50h] [rbp-20h]
  int32_t nCount; // [rsp+5Ch] [rbp-14h]

  thisa = this;
  Indexa = Index;
  ConnId = Player::getConnId(this->m_pPlayer);
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CCDu);
  if ( packet )
  {
    if ( Indexa <= 0 )
    {
      nCount = std::map<int,int>::size(&thisa->m_ItemLimit);
      Answer::NetPacket::writeInt32(packet, nCount);
      iter._M_node = std::map<int,int>::begin(&thisa->m_ItemLimit)._M_node;
      eiter._M_node = std::map<int,int>::end(&thisa->m_ItemLimit)._M_node;
      while ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &eiter) )
      {
        v6 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v6->first);
        v7 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v7->second);
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter);
      }
    }
    else
    {
      it._M_node = std::map<int,int>::find(&thisa->m_ItemLimit, &Indexa)._M_node;
      __x._M_node = std::map<int,int>::end(&thisa->m_ItemLimit)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      {
        Answer::NetPacket::writeInt32(packet, 1);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->first);
        v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->second);
      }
      else
      {
        Answer::NetPacket::writeInt32(packet, 1);
        Answer::NetPacket::writeInt32(packet, 0);
        Answer::NetPacket::writeInt32(packet, 0);
      }
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(thisa->m_pPlayer);
    v10 = Player::getConnId(thisa->m_pPlayer);
    v11 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v11, v10, GateIndex, packet);
  }
}


#####################################
int32_t __cdecl ScoreShop::GetLimitCount(ScoreShop *const this, int32_t index)
{
  int32_t indexa; // [rsp+4h] [rbp-2Ch] BYREF
  ScoreShop *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  indexa = index;
  it._M_node = std::map<int,int>::find(&this->m_ItemLimit, &indexa)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_ItemLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
void __cdecl ScoreShop::AddLimitCount(ScoreShop *const this, int32_t index, int32_t count)
{
  std::pair<const int,int> *v3; // rax
  int32_t indexa; // [rsp+4h] [rbp-2Ch] BYREF
  ScoreShop *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  indexa = index;
  it._M_node = std::map<int,int>::find(&this->m_ItemLimit, &indexa)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_ItemLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    v3->second += count;
  }
  else
  {
    *std::map<int,int>::operator[](&thisa->m_ItemLimit, &indexa) = count;
  }
}


#####################################
void __cdecl ScoreShop::OnDaySwitch(ScoreShop *const this, int32_t nDiffDays)
{
  int first; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > v4; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  ScoreShopCfg *pShop; // [rsp+28h] [rbp-18h]

  it._M_node = std::map<int,int>::begin(&this->m_ItemLimit)._M_node;
  while ( 1 )
  {
    __x._M_node = std::map<int,int>::end(&this->m_ItemLimit)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
    v3 = Answer::Singleton<CfgData>::instance();
    pShop = CfgData::GetScoreShopCfg(v3, first);
    if ( !pShop || pShop->LimitType == 1 )
    {
      v4._M_node = std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0)._M_node;
      std::map<int,int>::erase(&this->m_ItemLimit, v4);
    }
    else
    {
      std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0);
    }
  }
  ScoreShop::SendLimitInfo(this, 0);
}


