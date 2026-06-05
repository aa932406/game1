// Decompiled methods for class: CChrDepot
// Source: gameserver.cc
// Total methods: 41

#####################################
void __cdecl CChrDepot::~CChrDepot(CChrDepot *const this)
{
  CChrDepot::~CChrDepot(this);
  operator delete(this);
}


#####################################
void __cdecl CChrDepot::OnLoadFromDB(CChrDepot *const this, const PlayerDBData *const dbData)
{
  this->m_OpenCount = dbData->gambleDepot.OpneCount;
  std::string::operator=(&this->m_Password, &dbData->gambleDepot.Password);
  std::string::operator=(&this->m_SendPassword, &dbData->gambleDepot.SecondPassword);
  memcpy(this->m_DepotData, dbData->gambleDepot.gambleDepot, sizeof(this->m_DepotData));
  memcpy(this->m_aCurrency, dbData->gambleDepot.Currency, sizeof(this->m_aCurrency));
}


#####################################
void __cdecl CChrDepot::OnSaveToDB(CChrDepot *const this, PlayerDBData *const dbData)
{
  dbData->gambleDepot.OpneCount = this->m_OpenCount;
  std::string::operator=(&dbData->gambleDepot.Password, &this->m_Password);
  std::string::operator=(&dbData->gambleDepot.SecondPassword, &this->m_SendPassword);
  memcpy(dbData->gambleDepot.gambleDepot, this->m_DepotData, sizeof(dbData->gambleDepot.gambleDepot));
  memcpy(dbData->gambleDepot.Currency, this->m_aCurrency, sizeof(dbData->gambleDepot.Currency));
}


#####################################
void __cdecl CChrDepot::OnUpdate(CChrDepot *const this, int64_t curTick)
{
  CChrDepot::CheckDirty(this);
  CChrDepot::CheckCurrency(this);
}


#####################################
void __cdecl CChrDepot::GetInterestsProtocol(CChrDepot *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+14h] [rbp-1Ch] BYREF
  unsigned __int16 v3; // [rsp+16h] [rbp-1Ah] BYREF
  unsigned __int16 v4; // [rsp+18h] [rbp-18h] BYREF
  unsigned __int16 v5; // [rsp+1Ah] [rbp-16h] BYREF
  unsigned __int16 v6; // [rsp+1Ch] [rbp-14h] BYREF
  unsigned __int16 v7; // [rsp+1Eh] [rbp-12h] BYREF
  unsigned __int16 v8; // [rsp+20h] [rbp-10h] BYREF
  unsigned __int16 v9; // [rsp+22h] [rbp-Eh] BYREF
  unsigned __int16 v10; // [rsp+24h] [rbp-Ch] BYREF
  unsigned __int16 v11; // [rsp+26h] [rbp-Ah] BYREF
  unsigned __int16 v12; // [rsp+28h] [rbp-8h] BYREF
  unsigned __int16 v13; // [rsp+2Ah] [rbp-6h] BYREF
  unsigned __int16 v14; // [rsp+2Ch] [rbp-4h] BYREF
  unsigned __int16 v15; // [rsp+2Eh] [rbp-2h] BYREF

  __x = 401;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 402;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 403;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 404;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 405;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 406;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 407;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 408;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 409;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 410;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 503;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 504;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 505;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 506;
  std::list<unsigned short>::push_back(procList, &v15);
}


#####################################
int32_t __cdecl CChrDepot::DispatchNetDatas(CChrDepot *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  switch ( nProcId )
  {
    case 0x191u:
      result = CChrDepot::OnGetDepotItem(this, inPacket);
      break;
    case 0x192u:
      result = CChrDepot::OnSaveItemToDepot(this, inPacket);
      break;
    case 0x193u:
      result = CChrDepot::OnGetDepotCurrency(this, inPacket);
      break;
    case 0x194u:
      result = CChrDepot::OnSaveDepotCurrency(this, inPacket);
      break;
    case 0x195u:
      result = CChrDepot::OnNewSortDepot(this, inPacket);
      break;
    case 0x196u:
      result = CChrDepot::OnOpenDepotSlot(this, inPacket);
      break;
    case 0x197u:
      result = CChrDepot::OnSetPassword(this, inPacket);
      break;
    case 0x198u:
      result = CChrDepot::OnEnterPassword(this, inPacket);
      break;
    case 0x199u:
      result = CChrDepot::OnModifyPassword(this, inPacket);
      break;
    case 0x19Au:
      result = CChrDepot::OnCancelPassword(this, inPacket);
      break;
    case 0x1F7u:
      result = CChrDepot::OnSetSecondPassword(this, inPacket);
      break;
    case 0x1F8u:
      result = CChrDepot::OnEnterSecondPassword(this, inPacket);
      break;
    case 0x1F9u:
      result = CChrDepot::OnModifySecondPassword(this, inPacket);
      break;
    case 0x1FAu:
      result = CChrDepot::OnCancelSecondPassword(this, inPacket);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
void __cdecl CChrDepot::CleanUp(CChrDepot *const this)
{
  bzero(this->m_DepotData, 0x4600u);
  bzero(&this->m_nullobj, 0x20u);
  bzero(this->m_aCurrency, 0x60u);
  std::list<int>::clear(&this->m_lstDirty);
  this->m_NeedSendCurrency = 0;
  this->m_NeedSendDirty = 0;
  this->m_OpenCount = 0;
  std::string::operator=(&this->m_Password, byte_8CD620);
  std::string::operator=(&this->m_SendPassword, byte_8CD620);
}


#####################################
bool __cdecl CChrDepot::CanOperateDepot(CChrDepot *const this)
{
  CVip *PlayerVip; // rax

  if ( !this->m_pPlayer )
    return 0;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( !CVip::GetVipFlg(PlayerVip, 2) && StaticObj::getMapId(this->m_pPlayer) != 50001 )
    return 0;
  if ( std::operator==<char>(&this->m_Password, byte_8CD620) )
    return 1;
  return Player::getRecord(this->m_pPlayer, 2) == 1;
}


#####################################
bool __cdecl CChrDepot::IsEnterSecondPasswordOperate(CChrDepot *const this)
{
  if ( !this->m_pPlayer )
    return 0;
  if ( std::operator==<char>(&this->m_SendPassword, byte_8CD620) )
    return 1;
  return Player::getRecord(this->m_pPlayer, 9) == 1;
}


#####################################
int32_t __cdecl CChrDepot::OnGetDepotItem(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *v3; // rax
  CExtCharBag *v4; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  MemChrBag BagItem; // [rsp+10h] [rbp-70h] BYREF
  MemChrBag SlotData; // [rsp+30h] [rbp-50h] BYREF
  int32_t DepotSlot; // [rsp+58h] [rbp-28h]
  int32_t BagSlot; // [rsp+5Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  DepotSlot = Answer::NetPacket::readInt32(inPacket);
  BagSlot = Answer::NetPacket::readInt32(inPacket);
  if ( !CChrDepot::IsSlotValid(this, DepotSlot) )
    return 2;
  SlotData = *CChrDepot::GetSlotData(this, DepotSlot);
  if ( SlotData.itemId <= 0 || SlotData.itemCount <= 0 )
    return 2;
  if ( BagSlot < 0 )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, &SlotData, ITEM_CHANGE_REASON::ICR_DEPOT_GET) )
    {
      Proc = Answer::NetPacket::getProc(inPacket);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      return GameService::replyfailure(v9, ConnId, GateIndex, Proc, 10016, 0);
    }
  }
  else
  {
    v3 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::IsSlotValid(v3, BagSlot) )
      return 2;
    Player::getBagSlotData(&BagItem, this->m_pPlayer, BagSlot);
    if ( BagItem.itemId && BagItem.itemCount )
      return 2;
    v4 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::SetSlotData(v4, BagSlot, &SlotData, ITEM_CHANGE_REASON::ICR_DEPOT_GET, 0);
  }
  CChrDepot::RemoveItem(this, DepotSlot);
  return 0;
}


#####################################
int32_t __cdecl CChrDepot::GetPageBySlot(CChrDepot *const this, int32_t Slot)
{
  return Slot / 56 + 1;
}


#####################################
int32_t __cdecl CChrDepot::OnSaveItemToDepot(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  CVip *PlayerVip; // rax
  const MemChrBag *SlotData; // rax
  CExtCharBag *Bag; // rax
  MemChrBag BagItem; // [rsp+30h] [rbp-40h] BYREF
  int32_t BagSlot; // [rsp+54h] [rbp-1Ch]
  int32_t DepotSlot; // [rsp+58h] [rbp-18h]
  int32_t Page; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  BagSlot = Answer::NetPacket::readInt32(inPacket);
  DepotSlot = Answer::NetPacket::readInt32(inPacket);
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  Page = CVip::GetStorePage(PlayerVip);
  if ( CChrDepot::GetPageBySlot(this, DepotSlot) > Page )
    return 2;
  Player::getBagSlotData(&BagItem, this->m_pPlayer, BagSlot);
  if ( !BagItem.itemId || !BagItem.itemCount )
    return 2;
  if ( DepotSlot < 0 )
  {
    if ( !CChrDepot::AddItem(this, &BagItem) )
      return 2;
  }
  else
  {
    SlotData = CChrDepot::GetSlotData(this, DepotSlot);
    if ( (unsigned int)*(_QWORD *)&SlotData->itemId && (unsigned int)*(_QWORD *)&SlotData->itemCount )
      return 2;
    CChrDepot::setSlotData(this, DepotSlot, &BagItem);
  }
  Bag = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(Bag, BagSlot, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_DEPOT_SAVE, 0);
  return 0;
}


#####################################
bool __cdecl CChrDepot::AddItem(CChrDepot *const this, const MemChrBag *const item)
{
  const MemChrBag *SlotData; // rax
  int32_t DepotSize; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  DepotSize = CChrDepot::GetDepotSize(this);
  for ( i = 0; i < DepotSize; ++i )
  {
    SlotData = CChrDepot::GetSlotData(this, i);
    if ( !(unsigned int)*(_QWORD *)&SlotData->itemId || !(unsigned int)*(_QWORD *)&SlotData->itemCount )
    {
      CChrDepot::setSlotData(this, i, item);
      return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl CChrDepot::RemoveItem(CChrDepot *const this, int32_t Slot)
{
  if ( !CChrDepot::IsSlotValid(this, Slot) )
    return 0;
  CChrDepot::setSlotData(this, Slot, &this->m_nullobj);
  return 1;
}


#####################################
bool __cdecl CChrDepot::IsSlotValid(CChrDepot *const this, int32_t Slot)
{
  return Slot >= 0 && CChrDepot::GetDepotSize(this) > Slot;
}


#####################################
bool __cdecl CChrDepot::setSlotData(CChrDepot *const this, int32_t Slot, const MemChrBag *const slotData)
{
  __int64 v4; // rcx
  int64_t srcId; // rdx

  if ( !CChrDepot::IsSlotValid(this, Slot) )
    return 0;
  v4 = 16 * (2LL * Slot + 1);
  if ( slotData->itemCount <= 0 )
  {
    *(Player **)((char *)&this->m_pPlayer + v4) = *(Player **)&this->m_nullobj.itemId;
    *(_QWORD *)((char *)&this->m_OpenCount + v4) = *(_QWORD *)&this->m_nullobj.itemCount;
    *(_QWORD *)((char *)&this->m_DepotData[0].itemId + v4) = *(_QWORD *)&this->m_nullobj.endTime;
    srcId = this->m_nullobj.srcId;
  }
  else
  {
    *(Player **)((char *)&this->m_pPlayer + v4) = *(Player **)&slotData->itemId;
    *(_QWORD *)((char *)&this->m_OpenCount + v4) = *(_QWORD *)&slotData->itemCount;
    *(_QWORD *)((char *)&this->m_DepotData[0].itemId + v4) = *(_QWORD *)&slotData->endTime;
    srcId = slotData->srcId;
  }
  *(_QWORD *)((char *)&this->m_DepotData[0].itemCount + v4) = srcId;
  CChrDepot::AddDirty(this, Slot);
  return 1;
}


#####################################
void __cdecl CChrDepot::CleanBag(CChrDepot *const this)
{
  EquipId_t srcId; // r12
  int8_t ConnId; // bl
  CEquipManager *v3; // rax
  int32_t nSize; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  nSize = CChrDepot::GetDepotSize(this);
  for ( i = 0; i < nSize && CChrDepot::IsSlotValid(this, i); ++i )
  {
    if ( this->m_DepotData[i].itemId > 0 )
    {
      if ( this->m_DepotData[i].itemClass == 2 && this->m_DepotData[i].srcId > 0 )
      {
        srcId = this->m_DepotData[i].srcId;
        ConnId = Player::getConnId(this->m_pPlayer);
        v3 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::DeleteMemEquip(v3, ConnId, srcId, 0);
      }
      this->m_DepotData[i] = this->m_nullobj;
      CChrDepot::AddDirty(this, i);
    }
  }
}


#####################################
int64_t __cdecl CChrDepot::GetCurrency(CChrDepot *const this, const CURRENCY_TYPE nType)
{
  if ( (unsigned int)nType < CURRENCY_TYPE::CURRENCY_TYPE_COUNT )
    return this->m_aCurrency[nType];
  else
    return 0;
}


#####################################
int32_t __cdecl CChrDepot::OnGetDepotCurrency(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int8_t nType; // [rsp+17h] [rbp-19h]
  __int64 Value; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  Value = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned __int8)nType >= 0xCu )
    return 2;
  if ( Value <= 0 )
    return 2;
  if ( CChrDepot::GetCurrency(this, (const CURRENCY_TYPE)nType) < Value )
    return 2;
  this->m_aCurrency[nType] -= Value;
  Player::AddCurrency(this->m_pPlayer, (const CURRENCY_TYPE)nType, Value, CURRENCY_CHANGE_REASON::GCR_DEPOT_GET, 0);
  this->m_NeedSendCurrency = 1;
  return 0;
}


#####################################
int32_t __cdecl CChrDepot::OnSaveDepotCurrency(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int8_t nType; // [rsp+17h] [rbp-19h]
  __int64 Value; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  Value = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned __int8)nType >= 0xCu )
    return 2;
  if ( Value <= 0 )
    return 2;
  if ( Player::GetCurrency(this->m_pPlayer, (const CURRENCY_TYPE)nType) < Value )
    return 2;
  this->m_aCurrency[nType] += Value;
  Player::DecCurrency(this->m_pPlayer, (const CURRENCY_TYPE)nType, Value, CURRENCY_CHANGE_REASON::GCR_DEPOT_GET, 0);
  this->m_NeedSendCurrency = 1;
  return 0;
}


#####################################
void __cdecl CChrDepot::CheckCurrency(CChrDepot *const this)
{
  if ( this->m_NeedSendCurrency )
  {
    CChrDepot::SendDepotCurrency(this);
    this->m_NeedSendCurrency = 0;
  }
}


#####################################
void __cdecl CChrDepot::SendDepotCurrency(CChrDepot *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  uint32_t oldOffset; // [rsp+20h] [rbp-20h]
  int8_t nCount; // [rsp+27h] [rbp-19h]
  uint32_t newOffset; // [rsp+28h] [rbp-18h]
  char i; // [rsp+2Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2C9Bu);
    if ( packet )
    {
      oldOffset = Answer::NetPacket::getWOffset(packet);
      nCount = 0;
      Answer::NetPacket::writeInt8(packet, 0);
      for ( i = 0; i <= 11; ++i )
      {
        if ( this->m_aCurrency[i] > 0 )
        {
          Answer::NetPacket::writeInt8(packet, i);
          Answer::NetPacket::writeInt64(packet, this->m_aCurrency[i]);
          ++nCount;
        }
      }
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt8(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
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
int32_t __cdecl CChrDepot::OnNewSortDepot(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MemChrBag *v3; // rcx
  MemChrBag *v4; // rax
  MemChrBag *M_current; // rbx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v6; // rax
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v9; // rax
  MemChrBag tSlot; // [rsp+10h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+40h] [rbp-90h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v18; // [rsp+80h] [rbp-50h] BYREF
  int32_t Page; // [rsp+8Ch] [rbp-44h]
  int32_t MinSlot; // [rsp+90h] [rbp-40h]
  int32_t MaxSlot; // [rsp+94h] [rbp-3Ch]
  int32_t slot; // [rsp+98h] [rbp-38h]
  int32_t i; // [rsp+9Ch] [rbp-34h]
  const MemChrBag *slotdata; // [rsp+A0h] [rbp-30h]
  bool bFind; // [rsp+AFh] [rbp-21h]
  MemChrBag *bagSlot; // [rsp+B0h] [rbp-20h]
  int32_t overlay; // [rsp+BCh] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  Page = Answer::NetPacket::readInt32(inPacket);
  MinSlot = 56 * Page;
  MaxSlot = 56 * (Page + 1) - 1;
  if ( 56 * Page < 0 || MaxSlot > 559 )
    return 10002;
  if ( MinSlot >= MaxSlot )
    return 10002;
  std::vector<MemChrBag>::vector(&items);
  for ( i = MinSlot; i <= MaxSlot; ++i )
  {
    slotdata = CChrDepot::GetSlotData(this, i);
    if ( slotdata->itemCount > 0 )
    {
      bFind = 0;
      for ( it._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&items)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
          break;
        v3 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
        if ( CChrDepot::compairSlot(this, v3, slotdata) )
        {
          v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
          v4->itemCount += slotdata->itemCount;
          bFind = 1;
          break;
        }
      }
      if ( !bFind )
        std::vector<MemChrBag>::push_back(&items, slotdata);
    }
  }
  if ( std::vector<MemChrBag>::size(&items) <= 0x38 )
  {
    M_current = std::vector<MemChrBag>::end(&items)._M_current;
    v6._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
    std::sort<__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>,bool (*)(MemChrBag const&,MemChrBag const&)>(
      v6,
      (__gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> >)M_current,
      (bool (*)(const MemChrBag *, const MemChrBag *))sortItem);
    slot = MinSlot;
    for ( iter._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
    {
      v18._M_current = std::vector<MemChrBag>::end(&items)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &v18) || slot > MaxSlot )
        break;
      bagSlot = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter);
      itemClass = bagSlot->itemClass;
      itemId = bagSlot->itemId;
      v9 = Answer::Singleton<CfgData>::instance();
      overlay = CfgData::getOverlay(v9, itemId, itemClass);
      if ( overlay > 0 )
      {
        while ( bagSlot->itemCount > overlay && slot <= MaxSlot )
        {
          tSlot = *bagSlot;
          tSlot.itemCount = overlay;
          bagSlot->itemCount -= overlay;
          CChrDepot::setSlotData(this, slot++, &tSlot);
        }
        if ( bagSlot->itemCount > 0 && slot <= MaxSlot )
          CChrDepot::setSlotData(this, slot++, bagSlot);
      }
    }
    while ( slot <= MaxSlot )
      CChrDepot::setSlotData(this, slot++, &this->m_nullobj);
    v2 = 0;
  }
  else
  {
    v2 = 10002;
  }
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnSortDepot(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MemChrBag *v3; // rcx
  MemChrBag *v4; // rax
  MemChrBag *M_current; // rbx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v6; // rax
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v9; // rax
  MemChrBag tSlot; // [rsp+10h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+40h] [rbp-90h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v18; // [rsp+80h] [rbp-50h] BYREF
  int32_t nDepotSize; // [rsp+94h] [rbp-3Ch]
  int32_t slot; // [rsp+98h] [rbp-38h]
  int32_t i; // [rsp+9Ch] [rbp-34h]
  const MemChrBag *slotdata; // [rsp+A0h] [rbp-30h]
  bool bFind; // [rsp+AFh] [rbp-21h]
  MemChrBag *bagSlot; // [rsp+B0h] [rbp-20h]
  int32_t overlay; // [rsp+BCh] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  std::vector<MemChrBag>::vector(&items);
  nDepotSize = CChrDepot::GetDepotSize(this);
  for ( i = 0; i < nDepotSize; ++i )
  {
    slotdata = CChrDepot::GetSlotData(this, i);
    if ( slotdata->itemCount > 0 )
    {
      bFind = 0;
      for ( it._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&items)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
          break;
        v3 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
        if ( CChrDepot::compairSlot(this, v3, slotdata) )
        {
          v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
          v4->itemCount += slotdata->itemCount;
          bFind = 1;
          break;
        }
      }
      if ( !bFind )
        std::vector<MemChrBag>::push_back(&items, slotdata);
    }
  }
  M_current = std::vector<MemChrBag>::end(&items)._M_current;
  v6._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
  std::sort<__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>,bool (*)(MemChrBag const&,MemChrBag const&)>(
    v6,
    (__gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> >)M_current,
    (bool (*)(const MemChrBag *, const MemChrBag *))sortItem);
  slot = 0;
  for ( iter._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    v18._M_current = std::vector<MemChrBag>::end(&items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &v18) || slot >= nDepotSize )
      break;
    bagSlot = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter);
    itemClass = bagSlot->itemClass;
    itemId = bagSlot->itemId;
    v9 = Answer::Singleton<CfgData>::instance();
    overlay = CfgData::getOverlay(v9, itemId, itemClass);
    if ( overlay > 0 )
    {
      while ( bagSlot->itemCount > overlay && slot < nDepotSize )
      {
        tSlot = *bagSlot;
        tSlot.itemCount = overlay;
        bagSlot->itemCount -= overlay;
        CChrDepot::setSlotData(this, slot++, &tSlot);
      }
      if ( bagSlot->itemCount > 0 && slot < nDepotSize )
        CChrDepot::setSlotData(this, slot++, bagSlot);
    }
  }
  while ( slot < nDepotSize )
    CChrDepot::setSlotData(this, slot++, &this->m_nullobj);
  v2 = 0;
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
bool __cdecl CChrDepot::compairSlot(CChrDepot *const this, const MemChrBag *const left, const MemChrBag *const right)
{
  if ( left->itemId != right->itemId )
    return 0;
  if ( left->srcId != right->srcId )
    return 0;
  if ( left->itemClass != right->itemClass )
    return 0;
  if ( left->bind == right->bind )
    return left->endTime == right->endTime;
  return 0;
}


#####################################
void __cdecl CChrDepot::AddDirty(CChrDepot *const this, int32_t nSlot)
{
  std::_List_node_base *M_node; // rbx
  std::_List_iterator<int> v3; // rax
  int32_t nSlota; // [rsp+4h] [rbp-3Ch] BYREF
  CChrDepot *thisa; // [rsp+8h] [rbp-38h]
  std::_List_iterator<int> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nSlota = nSlot;
  M_node = std::list<int>::end(&this->m_lstDirty)._M_node;
  v3._M_node = std::list<int>::begin(&this->m_lstDirty)._M_node;
  iter._M_node = std::find<std::_List_iterator<int>,int>(v3, (std::_List_iterator<int>)M_node, &nSlota)._M_node;
  __x._M_node = std::list<int>::end(&thisa->m_lstDirty)._M_node;
  if ( !std::_List_iterator<int>::operator!=(&iter, &__x) )
  {
    std::list<int>::push_back(&thisa->m_lstDirty, &nSlota);
    thisa->m_NeedSendDirty = 1;
  }
}


#####################################
void __cdecl CChrDepot::CheckDirty(CChrDepot *const this)
{
  if ( this->m_NeedSendDirty && CChrDepot::SendDirty(this) )
  {
    CChrDepot::ClearDirty(this);
    this->m_NeedSendDirty = 0;
  }
}


#####################################
bool __cdecl CChrDepot::SendDirty(CChrDepot *const this)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_List_iterator<int> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<int> iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-30h]
  uint32_t nOffSet; // [rsp+38h] [rbp-28h]
  int32_t nCount; // [rsp+3Ch] [rbp-24h]
  uint32_t endOffSet; // [rsp+40h] [rbp-20h]
  int32_t nSlot; // [rsp+44h] [rbp-1Ch]
  const MemChrBag *tSlot; // [rsp+48h] [rbp-18h]

  if ( !this->m_pPlayer || std::list<int>::empty(&this->m_lstDirty) )
    return 0;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DB7u);
  if ( !packet )
    return 0;
  Answer::NetPacket::writeInt8(packet, 2);
  nOffSet = Answer::NetPacket::getWOffset(packet);
  nCount = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  iter._M_node = std::list<int>::begin(&this->m_lstDirty)._M_node;
  eiter._M_node = std::list<int>::end(&this->m_lstDirty)._M_node;
  while ( std::_List_iterator<int>::operator!=(&iter, &eiter) )
  {
    nSlot = *std::_List_iterator<int>::operator*(&iter);
    tSlot = CChrDepot::GetSlotData(this, nSlot);
    Answer::NetPacket::writeInt32(packet, nSlot);
    Answer::NetPacket::writeInt32(packet, tSlot->itemId);
    Answer::NetPacket::writeInt8(packet, tSlot->itemClass);
    Answer::NetPacket::writeInt32(packet, tSlot->itemCount);
    Answer::NetPacket::writeInt8(packet, tSlot->bind);
    Answer::NetPacket::writeInt32(packet, tSlot->endTime);
    Answer::NetPacket::writeInt64(packet, tSlot->srcId);
    ++nCount;
    std::_List_iterator<int>::operator++(&iter);
  }
  endOffSet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, nOffSet);
  Answer::NetPacket::writeInt32(packet, nCount);
  Answer::NetPacket::setWOffset(packet, endOffSet);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v7 = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v8, v7, GateIndex, packet);
  return 1;
}


#####################################
int32_t __cdecl CChrDepot::OnOpenDepotSlot(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t slot; // [rsp+10h] [rbp-10h]
  int32_t CostValues; // [rsp+14h] [rbp-Ch]
  int32_t OpenCount; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CChrDepot::CanOperateDepot(this) )
    return 2;
  slot = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned int)slot >= 0x230 )
    return 10002;
  if ( CChrDepot::IsSlotValid(this, slot) )
    return 10002;
  CostValues = 0;
  OpenCount = slot - CChrDepot::GetDepotSize(this) + 1;
  for ( i = CChrDepot::GetDepotSize(this); i <= slot; ++i )
    CostValues += CChrDepot::OpenSlotCostGold(this, i);
  if ( CostValues <= 0 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          CostValues,
          CURRENCY_CHANGE_REASON::GCR_DEPOT_SLOT_OPEN,
          0) )
    return 10002;
  this->m_OpenCount += OpenCount;
  CChrDepot::SendDepotInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CChrDepot::OpenSlotCostGold(CChrDepot *const this, int32_t Slot)
{
  if ( CChrDepot::IsSlotValid(this, Slot) )
    return 0;
  else
    return 10 * ((Slot - 56) / 5 + 1);
}


#####################################
void __cdecl CChrDepot::SendDepotItem(CChrDepot *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-38h]
  uint32_t nOffSet; // [rsp+24h] [rbp-2Ch]
  int32_t nCount; // [rsp+28h] [rbp-28h]
  int32_t nDepotSize; // [rsp+2Ch] [rbp-24h]
  uint32_t endOffSet; // [rsp+30h] [rbp-20h]
  int32_t slot; // [rsp+34h] [rbp-1Ch]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2C9Du);
    if ( packet )
    {
      nOffSet = Answer::NetPacket::getWOffset(packet);
      nCount = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      nDepotSize = CChrDepot::GetDepotSize(this);
      for ( slot = 0; slot < nDepotSize; ++slot )
      {
        if ( this->m_DepotData[slot].itemCount > 0 )
        {
          Answer::NetPacket::writeInt32(packet, slot);
          Answer::NetPacket::writeInt32(packet, this->m_DepotData[slot].itemId);
          Answer::NetPacket::writeInt8(packet, this->m_DepotData[slot].itemClass);
          Answer::NetPacket::writeInt32(packet, this->m_DepotData[slot].itemCount);
          Answer::NetPacket::writeInt8(packet, this->m_DepotData[slot].bind);
          Answer::NetPacket::writeInt32(packet, this->m_DepotData[slot].endTime);
          Answer::NetPacket::writeInt64(packet, this->m_DepotData[slot].srcId);
          ++nCount;
        }
      }
      endOffSet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, nOffSet);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::setWOffset(packet, endOffSet);
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
void __cdecl CChrDepot::SendDepotInfo(CChrDepot *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2C9Cu);
    if ( packet )
    {
      v3 = CChrDepot::GetDepotSize(this) - 1;
      Answer::NetPacket::writeInt32(packet, v3);
      if ( std::operator==<char>(&this->m_Password, byte_8CD620) )
        Answer::NetPacket::writeInt8(packet, 0);
      else
        Answer::NetPacket::writeInt8(packet, 1);
      if ( std::operator==<char>(&this->m_SendPassword, byte_8CD620) )
        Answer::NetPacket::writeInt8(packet, 0);
      else
        Answer::NetPacket::writeInt8(packet, 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CChrDepot::GetItemCount(CChrDepot *const this, int32_t nId, int8_t nClass)
{
  int32_t nCount; // [rsp+14h] [rbp-Ch]
  int32_t nDeportSize; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  nCount = 0;
  nDeportSize = CChrDepot::GetDepotSize(this);
  for ( i = 0; i < nDeportSize; ++i )
  {
    if ( this->m_DepotData[i].itemId == nId && this->m_DepotData[i].itemClass == nClass )
      nCount += this->m_DepotData[i].itemCount;
  }
  return nCount;
}


#####################################
int32_t __cdecl CChrDepot::OnSetPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::string TwoPassword; // [rsp+10h] [rbp-30h] BYREF
  std::string OnePassword; // [rsp+20h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator!=<char>(&this->m_Password, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OnePassword, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&TwoPassword, (bool)inPacket);
  if ( std::operator!=<char>(&OnePassword, &TwoPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 16, 0);
    v2 = 10002;
  }
  else
  {
    std::string::operator=(&this->m_Password, &OnePassword);
    Player::TiShiInfo(this->m_pPlayer, 14, 0);
    Player::updateRecord(this->m_pPlayer, 2, 1);
    CChrDepot::SendDepotInfo(this);
    v2 = 0;
  }
  std::string::~string(&TwoPassword);
  std::string::~string(&OnePassword);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnEnterPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  std::string Password; // [rsp+10h] [rbp-30h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator==<char>(&this->m_Password, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&Password, (bool)inPacket);
  if ( std::operator!=<char>(&Password, &this->m_Password) )
  {
    Player::TiShiInfo(this->m_pPlayer, 15, 0);
    v2 = 10002;
  }
  else
  {
    Player::updateRecord(this->m_pPlayer, 2, 1);
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
    v2 = 0;
  }
  std::string::~string(&Password);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnModifyPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::string TwoPassword; // [rsp+10h] [rbp-40h] BYREF
  std::string OnePassword; // [rsp+20h] [rbp-30h] BYREF
  std::string OldPassword; // [rsp+30h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator==<char>(&this->m_Password, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OldPassword, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OnePassword, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&TwoPassword, (bool)inPacket);
  if ( std::operator!=<char>(&OldPassword, &this->m_Password) )
  {
    Player::TiShiInfo(this->m_pPlayer, 15, 0);
    v2 = 10002;
  }
  else if ( std::operator!=<char>(&OnePassword, &TwoPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 16, 0);
    v2 = 10002;
  }
  else
  {
    std::string::operator=(&this->m_Password, &OnePassword);
    Player::TiShiInfo(this->m_pPlayer, 17, 0);
    v2 = 0;
  }
  std::string::~string(&TwoPassword);
  std::string::~string(&OnePassword);
  std::string::~string(&OldPassword);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnCancelPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::string OldPassword; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator==<char>(&this->m_Password, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OldPassword, (bool)inPacket);
  if ( std::operator!=<char>(&OldPassword, &this->m_Password) )
  {
    Player::TiShiInfo(this->m_pPlayer, 15, 0);
    v2 = 10002;
  }
  else
  {
    std::string::operator=(&this->m_Password, byte_8CD620);
    CChrDepot::SendDepotInfo(this);
    v2 = 0;
  }
  std::string::~string(&OldPassword);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnSetSecondPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::string TwoPassword; // [rsp+10h] [rbp-30h] BYREF
  std::string OnePassword; // [rsp+20h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator!=<char>(&this->m_SendPassword, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OnePassword, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&TwoPassword, (bool)inPacket);
  if ( std::operator!=<char>(&OnePassword, &TwoPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 16, 0);
    v2 = 10002;
  }
  else
  {
    std::string::operator=(&this->m_SendPassword, &OnePassword);
    Player::TiShiInfo(this->m_pPlayer, 14, 0);
    Player::updateRecord(this->m_pPlayer, 9, 1);
    CChrDepot::SendDepotInfo(this);
    v2 = 0;
  }
  std::string::~string(&TwoPassword);
  std::string::~string(&OnePassword);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnEnterSecondPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  std::string Password; // [rsp+10h] [rbp-30h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator==<char>(&this->m_SendPassword, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&Password, (bool)inPacket);
  if ( std::operator!=<char>(&Password, &this->m_SendPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 15, 0);
    v2 = 10002;
  }
  else
  {
    Player::updateRecord(this->m_pPlayer, 9, 1);
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
    v2 = 0;
  }
  std::string::~string(&Password);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnModifySecondPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::string TwoPassword; // [rsp+10h] [rbp-40h] BYREF
  std::string OnePassword; // [rsp+20h] [rbp-30h] BYREF
  std::string OldPassword; // [rsp+30h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator==<char>(&this->m_SendPassword, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OldPassword, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OnePassword, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&TwoPassword, (bool)inPacket);
  if ( std::operator!=<char>(&OldPassword, &this->m_SendPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 15, 0);
    v2 = 10002;
  }
  else if ( std::operator!=<char>(&OnePassword, &TwoPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 16, 0);
    v2 = 10002;
  }
  else
  {
    std::string::operator=(&this->m_SendPassword, &OnePassword);
    Player::TiShiInfo(this->m_pPlayer, 17, 0);
    v2 = 0;
  }
  std::string::~string(&TwoPassword);
  std::string::~string(&OnePassword);
  std::string::~string(&OldPassword);
  return v2;
}


#####################################
int32_t __cdecl CChrDepot::OnCancelSecondPassword(CChrDepot *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  std::string OldPassword; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( std::operator==<char>(&this->m_SendPassword, byte_8CD620) )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&OldPassword, (bool)inPacket);
  if ( std::operator!=<char>(&OldPassword, &this->m_SendPassword) )
  {
    Player::TiShiInfo(this->m_pPlayer, 15, 0);
    v2 = 10002;
  }
  else
  {
    std::string::operator=(&this->m_SendPassword, byte_8CD620);
    CChrDepot::SendDepotInfo(this);
    v2 = 0;
  }
  std::string::~string(&OldPassword);
  return v2;
}


