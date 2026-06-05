// Decompiled methods for class: CExtCharWish
// Source: gameserver.cc
// Total methods: 13

#####################################
void __cdecl CExtCharWish::~CExtCharWish(CExtCharWish *const this)
{
  CExtCharWish::~CExtCharWish(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharWish::OnLoadFromDB(CExtCharWish *const this, const PlayerDBData *const dbData)
{
  std::list<CharWishInfo>::operator=(&this->m_lstWishs, &dbData->m_WishDBData.lstWishs);
  this->m_nNextId = std::list<CharWishInfo>::size(&this->m_lstWishs);
}


#####################################
void __cdecl CExtCharWish::OnSaveToDB(CExtCharWish *const this, PlayerDBData *const dbData)
{
  std::list<CharWishInfo>::operator=(&dbData->m_WishDBData.lstWishs, &this->m_lstWishs);
}


#####################################
void __cdecl CExtCharWish::GetInterestsProtocol(CExtCharWish *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 950;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 951;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 952;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CExtCharWish::DispatchNetDatas(CExtCharWish *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x3B7u:
      return CExtCharWish::OnGetWishInfo(this, inPacket);
    case 0x3B8u:
      return CExtCharWish::OnGetWishReward(this, inPacket);
    case 0x3B6u:
      return CExtCharWish::OnWish(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharWish::OnWish(CExtCharWish *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CExtCharBag *Bag; // rax
  CfgData *v5; // rax
  int32_t v6; // ebx
  CExtCharBag *v7; // rax
  int32_t Now; // eax
  int32_t itemId; // edx
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  GameService *v12; // rax
  MemChrBag slotData; // [rsp+10h] [rbp-80h] BYREF
  std::string info; // [rsp+30h] [rbp-60h] BYREF
  CharWishInfo __x; // [rsp+40h] [rbp-50h] BYREF
  int16_t nBagSlot; // [rsp+66h] [rbp-2Ah]
  CfgItem *pItem; // [rsp+68h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nBagSlot = Answer::NetPacket::readInt16(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&info, (bool)inPacket);
  v3 = nBagSlot;
  Bag = Player::GetBag(this->m_pPlayer);
  slotData = *CExtCharBag::GetSlotData(Bag, v3);
  if ( slotData.itemCount > 0 )
  {
    v5 = Answer::Singleton<CfgData>::instance();
    pItem = CfgData::getItem(v5, slotData.itemId);
    if ( pItem )
    {
      if ( pItem->type == 160 )
      {
        --slotData.itemCount;
        v6 = nBagSlot;
        v7 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::SetSlotData(v7, v6, &slotData, ITEM_CHANGE_REASON::ICR_WISH, 0);
        Now = Unit::getNow(this->m_pPlayer);
        itemId = slotData.itemId;
        CharWishInfo::CharWishInfo(&__x, ++this->m_nNextId, itemId, Now, &info);
        std::list<CharWishInfo>::push_back(&this->m_lstWishs, &__x);
        CharWishInfo::~CharWishInfo(&__x);
        CExtCharWish::sendWishInfo(this);
        CExtCharWish::SendWishIcon(this);
        Proc = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        LOBYTE(v6) = Player::getConnId(this->m_pPlayer);
        v12 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v12, v6, GateIndex, Proc, 0);
        v2 = 0;
      }
      else
      {
        v2 = 10002;
      }
    }
    else
    {
      v2 = 10002;
    }
  }
  else
  {
    v2 = 10002;
  }
  std::string::~string(&info);
  return v2;
}


#####################################
int32_t __cdecl CExtCharWish::OnGetWishInfo(CExtCharWish *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 2;
  CExtCharWish::sendWishInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharWish::OnGetWishReward(CExtCharWish *const this, Answer::NetPacket *inPacket)
{
  CharWishInfo *v3; // rax
  CharWishInfo *v4; // rax
  int32_t v5; // r12d
  int32_t nItemId; // ebx
  CfgData *v7; // rax
  const CfgWishRewardTable *WishRewardTable; // rax
  MemChrBagVector *p_vReward; // rbx
  CExtCharBag *Bag; // rax
  std::_List_iterator<CharWishInfo> iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<CharWishInfo> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nId; // [rsp+30h] [rbp-20h]
  int32_t nNowTime; // [rsp+34h] [rbp-1Ch]
  const CfgWishReward *pReward; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  for ( iter._M_node = std::list<CharWishInfo>::begin(&this->m_lstWishs)._M_node;
        ;
        std::_List_iterator<CharWishInfo>::operator++(&iter) )
  {
    __x._M_node = std::list<CharWishInfo>::end(&this->m_lstWishs)._M_node;
    if ( !std::_List_iterator<CharWishInfo>::operator!=(&iter, &__x) )
      break;
    v3 = std::_List_iterator<CharWishInfo>::operator->(&iter);
    if ( v3->nId == nId )
    {
      if ( std::_List_iterator<CharWishInfo>::operator->(&iter)->nGetReward )
        return 10002;
      nNowTime = Unit::getNow(this->m_pPlayer);
      v4 = std::_List_iterator<CharWishInfo>::operator->(&iter);
      v5 = nNowTime - v4->nStartTime;
      nItemId = std::_List_iterator<CharWishInfo>::operator->(&iter)->nItemId;
      v7 = Answer::Singleton<CfgData>::instance();
      WishRewardTable = CfgData::GetWishRewardTable(v7);
      pReward = CfgWishRewardTable::GetReward(WishRewardTable, nItemId, v5);
      if ( !pReward )
        return 10002;
      p_vReward = &pReward->vReward;
      Bag = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::AddItem(Bag, p_vReward, ITEM_CHANGE_REASON::ICR_WISH) )
        return 10002;
      std::_List_iterator<CharWishInfo>::operator->(&iter)->nGetReward = 1;
      CExtCharWish::sendWishInfo(this);
      CExtCharWish::SendWishIcon(this);
      return 0;
    }
  }
  return 0;
}


#####################################
void __cdecl CExtCharWish::sendWishInfo(CExtCharWish *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CharWishInfo *v3; // rax
  CharWishInfo *v4; // rax
  CharWishInfo *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_List_iterator<CharWishInfo> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CharWishInfo> __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( CExtCharWish::canGetReward(this) )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F08u);
      if ( packet )
      {
        for ( iter._M_node = std::list<CharWishInfo>::begin(&this->m_lstWishs)._M_node;
              ;
              std::_List_iterator<CharWishInfo>::operator++(&iter) )
        {
          __x._M_node = std::list<CharWishInfo>::end(&this->m_lstWishs)._M_node;
          if ( !std::_List_iterator<CharWishInfo>::operator!=(&iter, &__x) )
            break;
          if ( !std::_List_iterator<CharWishInfo>::operator->(&iter)->nGetReward )
          {
            v3 = std::_List_iterator<CharWishInfo>::operator->(&iter);
            Answer::NetPacket::writeInt32(packet, v3->nId);
            v4 = std::_List_iterator<CharWishInfo>::operator->(&iter);
            Answer::NetPacket::writeInt32(packet, v4->nStartTime);
            v5 = std::_List_iterator<CharWishInfo>::operator->(&iter);
            Answer::NetPacket::writeUTF8(packet, &v5->strInfo);
            break;
          }
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v8 = Player::getConnId(this->m_pPlayer);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, v8, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CExtCharWish::SendWishIcon(CExtCharWish *const this)
{
  int32_t nStartTime; // r12d
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgWishRewardTable *WishRewardTable; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_iterator<CharWishInfo> iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<CharWishInfo> __x; // [rsp+20h] [rbp-30h] BYREF
  int8_t nCanGetReward; // [rsp+2Fh] [rbp-21h]
  int32_t nLeftTime; // [rsp+30h] [rbp-20h]
  int32_t nItemId; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    nCanGetReward = 0;
    nLeftTime = 0;
    nItemId = 0;
    for ( iter._M_node = std::list<CharWishInfo>::begin(&this->m_lstWishs)._M_node;
          ;
          std::_List_iterator<CharWishInfo>::operator++(&iter) )
    {
      __x._M_node = std::list<CharWishInfo>::end(&this->m_lstWishs)._M_node;
      if ( !std::_List_iterator<CharWishInfo>::operator!=(&iter, &__x) )
        break;
      if ( !std::_List_iterator<CharWishInfo>::operator->(&iter)->nGetReward )
      {
        nCanGetReward = 1;
        nStartTime = std::_List_iterator<CharWishInfo>::operator->(&iter)->nStartTime;
        v2 = std::_List_iterator<CharWishInfo>::operator->(&iter)->nItemId;
        v3 = Answer::Singleton<CfgData>::instance();
        WishRewardTable = CfgData::GetWishRewardTable(v3);
        nLeftTime = CfgWishRewardTable::GetLeftTime(WishRewardTable, v2, nStartTime);
        nItemId = std::_List_iterator<CharWishInfo>::operator->(&iter)->nItemId;
        break;
      }
    }
    ConnId = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F09u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, nCanGetReward);
      Answer::NetPacket::writeInt32(packet, nLeftTime);
      Answer::NetPacket::writeInt32(packet, nItemId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtCharWish::AppendWishInfo(CExtCharWish *const this, Answer::NetPacket *packet)
{
  std::string *p_strInfo; // rdx
  std::_List_iterator<CharWishInfo> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CharWishInfo> __x; // [rsp+20h] [rbp-20h] BYREF
  uint32_t nOldOffset; // [rsp+34h] [rbp-Ch]
  int8_t nCount; // [rsp+3Bh] [rbp-5h]
  uint32_t nNewOffset; // [rsp+3Ch] [rbp-4h]

  if ( packet )
  {
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    nCount = 0;
    Answer::NetPacket::writeInt8(packet, 0);
    for ( iter._M_node = std::list<CharWishInfo>::begin(&this->m_lstWishs)._M_node;
          ;
          std::_List_iterator<CharWishInfo>::operator++(&iter) )
    {
      __x._M_node = std::list<CharWishInfo>::end(&this->m_lstWishs)._M_node;
      if ( !std::_List_iterator<CharWishInfo>::operator!=(&iter, &__x) )
        break;
      p_strInfo = &std::_List_iterator<CharWishInfo>::operator->(&iter)->strInfo;
      Answer::NetPacket::writeUTF8(packet, p_strInfo);
      if ( ++nCount > 2 )
        break;
    }
    nNewOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt8(packet, nCount);
    Answer::NetPacket::setWOffset(packet, nNewOffset);
  }
}


#####################################
bool __cdecl CExtCharWish::canGetReward(CExtCharWish *const this)
{
  std::_List_iterator<CharWishInfo> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<CharWishInfo> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<CharWishInfo>::begin(&this->m_lstWishs)._M_node;
        ;
        std::_List_iterator<CharWishInfo>::operator++(&iter) )
  {
    __x._M_node = std::list<CharWishInfo>::end(&this->m_lstWishs)._M_node;
    if ( !std::_List_iterator<CharWishInfo>::operator!=(&iter, &__x) )
      break;
    if ( !std::_List_iterator<CharWishInfo>::operator->(&iter)->nGetReward )
      return 1;
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharWish::getLeftTime(CExtCharWish *const this)
{
  int32_t nStartTime; // r12d
  int32_t nItemId; // ebx
  CfgData *v3; // rax
  const CfgWishRewardTable *WishRewardTable; // rax
  std::_List_iterator<CharWishInfo> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CharWishInfo> __x; // [rsp+20h] [rbp-20h] BYREF

  for ( iter._M_node = std::list<CharWishInfo>::begin(&this->m_lstWishs)._M_node;
        ;
        std::_List_iterator<CharWishInfo>::operator++(&iter) )
  {
    __x._M_node = std::list<CharWishInfo>::end(&this->m_lstWishs)._M_node;
    if ( !std::_List_iterator<CharWishInfo>::operator!=(&iter, &__x) )
      break;
    if ( !std::_List_iterator<CharWishInfo>::operator->(&iter)->nGetReward )
    {
      nStartTime = std::_List_iterator<CharWishInfo>::operator->(&iter)->nStartTime;
      nItemId = std::_List_iterator<CharWishInfo>::operator->(&iter)->nItemId;
      v3 = Answer::Singleton<CfgData>::instance();
      WishRewardTable = CfgData::GetWishRewardTable(v3);
      return CfgWishRewardTable::GetLeftTime(WishRewardTable, nItemId, nStartTime);
    }
  }
  return 0;
}


