// Decompiled methods for class: CFriendExpReward
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CFriendExpReward::~CFriendExpReward(CFriendExpReward *const this)
{
  CFriendExpReward::~CFriendExpReward(this);
  operator delete(this);
}


#####################################
void __cdecl CFriendExpReward::OnLoadFromDB(CFriendExpReward *const this, const PlayerDBData *const dbData)
{
  std::list<DieRecord>::operator=(&this->m_DieRecord, &dbData->m_FriendExpReward.m_DieRecord);
}


#####################################
void __cdecl CFriendExpReward::OnSaveToDB(CFriendExpReward *const this, PlayerDBData *const dbData)
{
  std::list<DieRecord>::operator=(&dbData->m_FriendExpReward.m_DieRecord, &this->m_DieRecord);
}


#####################################
void __cdecl CFriendExpReward::GetInterestsProtocol(CFriendExpReward *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 20085;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CFriendExpReward::DispatchNetDatas(
        CFriendExpReward *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 20085 )
    return CFriendExpReward::OnZuiZhong(this, inPacket);
  return 0;
}


#####################################
void __cdecl CFriendExpReward::AddDieRecord(
        CFriendExpReward *const this,
        CharId_t Cid,
        std::string *p_Name,
        int32_t MapId,
        int32_t Mid)
{
  DieRecord Stu; // [rsp+20h] [rbp-30h] BYREF

  if ( this->m_pPlayer )
  {
    DieRecord::DieRecord(&Stu);
    Stu.KillTime = Unit::getNow(this->m_pPlayer);
    Stu.MapId = MapId;
    Stu.MonsterId = Mid;
    Stu.Cid = Cid;
    std::string::operator=(&Stu.Name, p_Name);
    if ( std::list<DieRecord>::size(&this->m_DieRecord) > 0x13 )
      std::list<DieRecord>::pop_front(&this->m_DieRecord);
    std::list<DieRecord>::push_back(&this->m_DieRecord, &Stu);
    CFriendExpReward::SendOneDieRecord(this, &Stu);
    DieRecord::~DieRecord(&Stu);
  }
}


#####################################
void __cdecl CFriendExpReward::SendDieBoard(CFriendExpReward *const this)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v5; // rax
  int32_t LimitCount; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  DieRecord *stu; // [rsp+18h] [rbp-28h]
  Answer::NetPacket *packet; // [rsp+20h] [rbp-20h]
  int32_t nNowTime; // [rsp+28h] [rbp-18h]
  int32_t nReviveTime; // [rsp+2Ch] [rbp-14h]

  if ( this->m_pPlayer && !std::list<DieRecord>::empty(&this->m_DieRecord) && !Unit::isAlive(this->m_pPlayer) )
  {
    stu = std::list<DieRecord>::back(&this->m_DieRecord);
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E95u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, stu->MapId);
      if ( stu->MonsterId <= 0 )
      {
        Answer::NetPacket::writeInt8(packet, 2);
        Answer::NetPacket::writeInt64(packet, stu->Cid);
        Answer::NetPacket::writeUTF8(packet, &stu->Name);
      }
      else
      {
        Answer::NetPacket::writeInt8(packet, 1);
        Answer::NetPacket::writeInt32(packet, stu->MonsterId);
      }
      nNowTime = Unit::getNow(this->m_pPlayer);
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      nReviveTime = CExtOperateLimit::GetLimitCount(OperateLimit, 1111);
      if ( nNowTime >= nReviveTime )
        Answer::NetPacket::writeInt32(packet, 0);
      else
        Answer::NetPacket::writeInt32(packet, nReviveTime - nNowTime);
      v5 = Player::GetOperateLimit(this->m_pPlayer);
      LimitCount = CExtOperateLimit::GetLimitCount(v5, 1112);
      Answer::NetPacket::writeInt32(packet, LimitCount);
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
void __cdecl CFriendExpReward::SendOneDieRecord(CFriendExpReward *const this, DieRecord *const Stu)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *pNetData; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    pNetData = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D00u);
    if ( pNetData )
    {
      Answer::NetPacket::writeInt8(pNetData, 1);
      Answer::NetPacket::writeInt8(pNetData, 1);
      Answer::NetPacket::writeInt32(pNetData, Stu->KillTime);
      Answer::NetPacket::writeInt32(pNetData, Stu->MapId);
      if ( Stu->MonsterId <= 0 )
      {
        Answer::NetPacket::writeInt8(pNetData, 2);
        Answer::NetPacket::writeInt64(pNetData, Stu->Cid);
        Answer::NetPacket::writeUTF8(pNetData, &Stu->Name);
      }
      else
      {
        Answer::NetPacket::writeInt8(pNetData, 1);
        Answer::NetPacket::writeInt32(pNetData, Stu->MonsterId);
      }
      WOffset = Answer::NetPacket::getWOffset(pNetData);
      Answer::NetPacket::setSize(pNetData, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, pNetData);
    }
  }
}


#####################################
void __cdecl CFriendExpReward::SendDieRecord(CFriendExpReward *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int8_t v3; // al
  DieRecord *v4; // rax
  DieRecord *v5; // rax
  DieRecord *v6; // rax
  DieRecord *v7; // rax
  DieRecord *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_List_iterator<DieRecord> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<DieRecord> __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *pNetData; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    pNetData = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D00u);
    if ( pNetData )
    {
      it._M_node = std::list<DieRecord>::begin(&this->m_DieRecord)._M_node;
      Answer::NetPacket::writeInt8(pNetData, 2);
      v3 = std::list<DieRecord>::size(&this->m_DieRecord);
      Answer::NetPacket::writeInt8(pNetData, v3);
      while ( 1 )
      {
        __x._M_node = std::list<DieRecord>::end(&this->m_DieRecord)._M_node;
        if ( !std::_List_iterator<DieRecord>::operator!=(&it, &__x) )
          break;
        v4 = std::_List_iterator<DieRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(pNetData, v4->KillTime);
        v5 = std::_List_iterator<DieRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(pNetData, v5->MapId);
        if ( std::_List_iterator<DieRecord>::operator->(&it)->MonsterId <= 0 )
        {
          Answer::NetPacket::writeInt8(pNetData, 2);
          v7 = std::_List_iterator<DieRecord>::operator->(&it);
          Answer::NetPacket::writeInt64(pNetData, v7->Cid);
          v8 = std::_List_iterator<DieRecord>::operator->(&it);
          Answer::NetPacket::writeUTF8(pNetData, &v8->Name);
        }
        else
        {
          Answer::NetPacket::writeInt8(pNetData, 1);
          v6 = std::_List_iterator<DieRecord>::operator->(&it);
          Answer::NetPacket::writeInt32(pNetData, v6->MonsterId);
        }
        std::_List_iterator<DieRecord>::operator++(&it, 0);
      }
      WOffset = Answer::NetPacket::getWOffset(pNetData);
      Answer::NetPacket::setSize(pNetData, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v11 = Player::getConnId(this->m_pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, pNetData);
    }
  }
}


#####################################
int32_t __cdecl CFriendExpReward::OnZuiZhong(CFriendExpReward *const this, Answer::NetPacket *pData)
{
  int32_t v2; // ebx
  int32_t RunnerId; // r12d
  GameService *v4; // rax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax
  int16_t v9; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  CExtCharBag *Bag; // rax
  int v13; // r12d
  int8_t v14; // bl
  GameService *v15; // rax
  CharId_t Cid; // rax
  int32_t MapId; // eax
  int32_t PosX; // eax
  int32_t PosY; // eax
  uint32_t WOffset; // eax
  int16_t v21; // r12
  int8_t v22; // bl
  GameService *v23; // rax
  ItemData data; // [rsp+10h] [rbp-60h] BYREF
  Int32Vector vSlot; // [rsp+20h] [rbp-50h] BYREF
  int32_t bagslot; // [rsp+44h] [rbp-2Ch] BYREF
  CharId_t TargetId; // [rsp+48h] [rbp-28h]
  Player *pTarget; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *pNetData; // [rsp+58h] [rbp-18h]

  if ( !pData || !this->m_pPlayer )
    return 10002;
  TargetId = Answer::NetPacket::readInt64(pData);
  bagslot = Answer::NetPacket::readInt32(pData);
  RunnerId = StaticObj::GetRunnerId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  pTarget = GameService::getPlayer(v4, TargetId, RunnerId, 1);
  if ( !pTarget )
    return 10002;
  if ( Unit::HasBuffById(pTarget, 160) )
  {
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v7 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v7, ConnId, GateIndex, 0xC33u, 12, 0);
  }
  if ( StaticObj::InActivity(pTarget) || StaticObj::InDungeon(pTarget) )
  {
    v9 = Player::getGateIndex(this->m_pPlayer);
    v10 = Player::getConnId(this->m_pPlayer);
    v11 = Answer::Singleton<GameService>::instance();
    return GameService::replyfailure(v11, v10, v9, 0xC33u, 13, 0);
  }
  if ( bagslot < 0 )
  {
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            100,
            CURRENCY_CHANGE_REASON::GCR_ZHUI_ZONG,
            0) )
      return 10002;
  }
  else
  {
    std::vector<int>::vector(&vSlot);
    std::vector<int>::push_back(&vSlot, &bagslot);
    *(_QWORD *)&data.m_nId = 0x100000245LL;
    data.m_nCount = 1;
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, &vSlot, &data, ITEM_CHANGE_REASON::ICR_ZHUI_ZONG) )
    {
      v2 = 10002;
      v13 = 0;
    }
    else
    {
      v13 = 1;
    }
    std::vector<int>::~vector(&vSlot);
    if ( !v13 )
      return v2;
  }
  v14 = Player::getConnId(this->m_pPlayer);
  v15 = Answer::Singleton<GameService>::instance();
  pNetData = GameService::popNetpacket(v15, v14, Answer::PackType::PACK_DISPATCH, 0x2D01u);
  if ( pNetData )
  {
    Cid = Player::getCid(pTarget);
    Answer::NetPacket::writeInt64(pNetData, Cid);
    MapId = StaticObj::getMapId(pTarget);
    Answer::NetPacket::writeInt32(pNetData, MapId);
    PosX = StaticObj::GetPosX(pTarget);
    Answer::NetPacket::writeInt32(pNetData, PosX);
    PosY = StaticObj::GetPosY(pTarget);
    Answer::NetPacket::writeInt32(pNetData, PosY);
    WOffset = Answer::NetPacket::getWOffset(pNetData);
    Answer::NetPacket::setSize(pNetData, WOffset);
    v21 = Player::getGateIndex(this->m_pPlayer);
    v22 = Player::getConnId(this->m_pPlayer);
    v23 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v23, v22, v21, pNetData);
  }
  return 0;
}


