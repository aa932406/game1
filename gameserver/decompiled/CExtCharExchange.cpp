// Decompiled methods for class: CExtCharExchange
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl CExtCharExchange::~CExtCharExchange(CExtCharExchange *const this)
{
  CExtCharExchange::~CExtCharExchange(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharExchange::OnLoadFromDB(CExtCharExchange *const this, const PlayerDBData *const dbData)
{
  std::list<ExchangeRecord>::operator=(&this->m_lstExchangeRecords, &dbData->m_ExchangeDBData.lstExchange);
}


#####################################
void __cdecl CExtCharExchange::OnSaveToDB(CExtCharExchange *const this, PlayerDBData *const dbData)
{
  std::list<ExchangeRecord>::operator=(&dbData->m_ExchangeDBData.lstExchange, &this->m_lstExchangeRecords);
}


#####################################
void __cdecl CExtCharExchange::OnDaySwitch(CExtCharExchange *const this, int32_t nDiffDays)
{
  char nType; // [rsp+1Fh] [rbp-1h]

  if ( std::list<ExchangeRecord>::size(&this->m_lstExchangeRecords) )
  {
    std::list<ExchangeRecord>::clear(&this->m_lstExchangeRecords);
    for ( nType = 0; nType <= 4; ++nType )
      CExtCharExchange::sendExchangeInfo(this, nType);
  }
}


#####################################
void __cdecl CExtCharExchange::GetInterestsProtocol(CExtCharExchange *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 890;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 891;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CExtCharExchange::DispatchNetDatas(
        CExtCharExchange *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharExchange::isFunctionOpen(this) )
    return 10002;
  if ( nProcId == 890 )
    return CExtCharExchange::onAskExchangeInfo(this, inPacket);
  if ( nProcId == 891 )
    return CExtCharExchange::onExchange(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharExchange::onAskExchangeInfo(CExtCharExchange *const this, Answer::NetPacket *inPacket)
{
  CFestivalDoubleEleven *v3; // rax
  int8_t nType; // [rsp+1Fh] [rbp-1h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)nType > 4u )
    return 10002;
  if ( nType == 1 )
  {
    v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( !CFestivalDoubleEleven::IsInTime(v3, FESTIVAL_ACTIVITY_TYPE::FAT_EXCHANGE) )
      return 10002;
  }
  CExtCharExchange::sendExchangeInfo(this, nType);
  return 0;
}


#####################################
int32_t __cdecl CExtCharExchange::onExchange(CExtCharExchange *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CFestivalDoubleEleven *v3; // rax
  CExtCharTencent *CharTencent; // rax
  CUniteServer *v7; // rax
  int16_t v9; // r12
  int8_t v10; // bl
  CfgData *v11; // rax
  const CfgExchangeTable *ExchangeTable; // rax
  int32_t ExchangeRecord; // eax
  ItemDataList *p_vCost; // r12
  MemChrBagVector *p_vReward; // rbx
  CExtCharBag *Bag; // rax
  int64_t v17; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v21; // rax
  Int32Vector vSlot; // [rsp+10h] [rbp-50h] BYREF
  int8_t nType; // [rsp+35h] [rbp-2Bh]
  int16_t nIndex; // [rsp+36h] [rbp-2Ah]
  const CfgExchange *pCfg; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  nIndex = Answer::NetPacket::readInt16(inPacket);
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  if ( (unsigned __int8)nType <= 4u )
  {
    if ( nType == 1
      && (v3 = Answer::Singleton<CFestivalDoubleEleven>::instance(),
          !CFestivalDoubleEleven::IsInTime(v3, FESTIVAL_ACTIVITY_TYPE::FAT_EXCHANGE)) )
    {
      v2 = 10002;
    }
    else if ( nType == 2
           && (CharTencent = Player::GetCharTencent(this->m_pPlayer),
               !CExtCharTencent::IsSevenDayLoginExchangeDay(CharTencent)) )
    {
      v2 = 10002;
    }
    else if ( nType == 3
           && (v7 = Answer::Singleton<CUniteServer>::instance(),
               !CUniteServer::IsInTime(v7, Unit_Server_Activity_typ::US_COLLECT_DROP)) )
    {
      v2 = 10002;
    }
    else
    {
      v9 = nIndex;
      v10 = nType;
      v11 = Answer::Singleton<CfgData>::instance();
      ExchangeTable = CfgData::GetExchangeTable(v11);
      pCfg = CfgExchangeTable::GetExchange(ExchangeTable, v10, v9);
      if ( pCfg )
      {
        ExchangeRecord = CExtCharExchange::getExchangeRecord(this, nType, nIndex);
        if ( ExchangeRecord < pCfg->nLimit )
        {
          p_vCost = &pCfg->vCost;
          p_vReward = &pCfg->vReward;
          Bag = Player::GetBag(this->m_pPlayer);
          if ( !CExtCharBag::AddAndRemoveItem(Bag, p_vReward, &vSlot, p_vCost, ITEM_CHANGE_REASON::ICR_EXCHANGE) )
          {
            v2 = 10002;
          }
          else
          {
            CExtCharExchange::addExchangeRecord(this, nType, nIndex, 1);
            CExtCharExchange::sendExchangeInfo(this, nType);
            v17 = nIndex;
            Proc = Answer::NetPacket::getProc(inPacket);
            GateIndex = Player::getGateIndex(this->m_pPlayer);
            ConnId = Player::getConnId(this->m_pPlayer);
            v21 = Answer::Singleton<GameService>::instance();
            GameService::replySuccess(v21, ConnId, GateIndex, Proc, v17);
            v2 = 0;
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
    }
  }
  else
  {
    v2 = 10002;
  }
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
void __cdecl CExtCharExchange::sendExchangeInfo(CExtCharExchange *const this, int8_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  const ExchangeRecord *v4; // rax
  const ExchangeRecord *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_List_const_iterator<ExchangeRecord> iter; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<ExchangeRecord> __x; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<ExchangeRecord> v12; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<ExchangeRecord> v13; // [rsp+40h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-28h]
  int16_t nCount; // [rsp+56h] [rbp-1Ah]
  uint32_t oldOffset; // [rsp+58h] [rbp-18h]
  uint32_t newOffset; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EAEu);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, nType);
      nCount = 0;
      oldOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt16(packet, 0);
      __x._M_node = std::list<ExchangeRecord>::begin(&this->m_lstExchangeRecords)._M_node;
      std::_List_const_iterator<ExchangeRecord>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v13._M_node = std::list<ExchangeRecord>::end(&this->m_lstExchangeRecords)._M_node;
        std::_List_const_iterator<ExchangeRecord>::_List_const_iterator(&v12, &v13);
        if ( !std::_List_const_iterator<ExchangeRecord>::operator!=(&iter, &v12) )
          break;
        if ( std::_List_const_iterator<ExchangeRecord>::operator->(&iter)->nType == nType )
        {
          v4 = std::_List_const_iterator<ExchangeRecord>::operator->(&iter);
          Answer::NetPacket::writeInt16(packet, v4->nIndex);
          v5 = std::_List_const_iterator<ExchangeRecord>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v5->nCount);
          ++nCount;
        }
        std::_List_const_iterator<ExchangeRecord>::operator++(&iter);
      }
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt16(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharExchange::getExchangeRecord(CExtCharExchange *const this, int8_t nType, int16_t nIndex)
{
  std::_List_const_iterator<ExchangeRecord> iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<ExchangeRecord> __x; // [rsp+20h] [rbp-30h] BYREF
  std::_List_const_iterator<ExchangeRecord> v8; // [rsp+30h] [rbp-20h] BYREF
  std::_List_iterator<ExchangeRecord> v9; // [rsp+40h] [rbp-10h] BYREF

  __x._M_node = std::list<ExchangeRecord>::begin(&this->m_lstExchangeRecords)._M_node;
  std::_List_const_iterator<ExchangeRecord>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v9._M_node = std::list<ExchangeRecord>::end(&this->m_lstExchangeRecords)._M_node;
    std::_List_const_iterator<ExchangeRecord>::_List_const_iterator(&v8, &v9);
    if ( !std::_List_const_iterator<ExchangeRecord>::operator!=(&iter, &v8) )
      break;
    if ( std::_List_const_iterator<ExchangeRecord>::operator->(&iter)->nType == nType
      && std::_List_const_iterator<ExchangeRecord>::operator->(&iter)->nIndex == nIndex )
    {
      return std::_List_const_iterator<ExchangeRecord>::operator->(&iter)->nCount;
    }
    std::_List_const_iterator<ExchangeRecord>::operator++(&iter);
  }
  return 0;
}


#####################################
void __cdecl CExtCharExchange::addExchangeRecord(
        CExtCharExchange *const this,
        int8_t nType,
        int16_t nIndex,
        int32_t nCount)
{
  ExchangeRecord *v5; // rax
  std::_List_iterator<ExchangeRecord> iter; // [rsp+20h] [rbp-40h] BYREF
  ExchangeRecord record; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<ExchangeRecord> __x; // [rsp+40h] [rbp-20h] BYREF

  for ( iter._M_node = std::list<ExchangeRecord>::begin(&this->m_lstExchangeRecords)._M_node;
        ;
        std::_List_iterator<ExchangeRecord>::operator++(&iter) )
  {
    __x._M_node = std::list<ExchangeRecord>::end(&this->m_lstExchangeRecords)._M_node;
    if ( !std::_List_iterator<ExchangeRecord>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<ExchangeRecord>::operator->(&iter)->nType == nType
      && std::_List_iterator<ExchangeRecord>::operator->(&iter)->nIndex == nIndex )
    {
      v5 = std::_List_iterator<ExchangeRecord>::operator->(&iter);
      v5->nCount += nCount;
      return;
    }
  }
  *(_WORD *)&record.nType = (unsigned __int8)nType;
  record.nIndex = nIndex;
  record.nCount = nCount;
  std::list<ExchangeRecord>::push_back(&this->m_lstExchangeRecords, &record);
}


