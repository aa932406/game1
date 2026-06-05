// Decompiled methods for class: CExtCharMysteryGift
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl CExtCharMysteryGift::~CExtCharMysteryGift(CExtCharMysteryGift *const this)
{
  CExtCharMysteryGift::~CExtCharMysteryGift(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharMysteryGift::OnDaySwitch(CExtCharMysteryGift *const this, int32_t nDiffDays)
{
  if ( CExtCharMysteryGift::getIndex(this) != 1 || CExtCharMysteryGift::getState(this) )
  {
    CExtCharMysteryGift::addIndex(this);
    CExtCharMysteryGift::setState(this, 0);
    CExtCharMysteryGift::SendMysteryGiftInfo(this, 0);
  }
}


#####################################
void __cdecl CExtCharMysteryGift::GetInterestsProtocol(CExtCharMysteryGift *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 885;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 886;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CExtCharMysteryGift::DispatchNetDatas(
        CExtCharMysteryGift *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharMysteryGift::isFunctionOpen(this) )
    return 10002;
  if ( nProcId == 885 )
    return CExtCharMysteryGift::onGetGift(this, inPacket);
  if ( nProcId == 886 )
    return CExtCharMysteryGift::onRequestInfo(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharMysteryGift::onGetGift(CExtCharMysteryGift *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgMysteryGiftTable *MysteryGiftTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-34h]
  int64_t nCondition; // [rsp+20h] [rbp-30h]
  const CfgMysteryGift *pCfg; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( CExtCharMysteryGift::getState(this) )
    return 10002;
  nIndex = CExtCharMysteryGift::getIndex(this);
  nCondition = CExtCharMysteryGift::getCondition(this);
  v3 = Answer::Singleton<CfgData>::instance();
  MysteryGiftTable = CfgData::GetMysteryGiftTable(v3);
  pCfg = CfgMysteryGiftTable::GetGiftInfo(MysteryGiftTable, nIndex);
  if ( !pCfg )
    return 10002;
  if ( pCfg->nCondition > nCondition )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vItem, ITEM_CHANGE_REASON::ICR_GET_MYSTERY_GIFT) )
    return 10002;
  if ( pCfg->nType == 3 && pCfg->nCondition > 0 )
    Player::DecCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_GOLD,
      pCfg->nCondition,
      CURRENCY_CHANGE_REASON::GCR_MYSTERY_GIFT_BUY,
      nIndex);
  CExtCharMysteryGift::setState(this, 1);
  CExtCharMysteryGift::broadcastGetGift(this, pCfg->nBroadId);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, nIndex);
  return 0;
}


#####################################
int32_t __cdecl CExtCharMysteryGift::onRequestInfo(CExtCharMysteryGift *const this, Answer::NetPacket *inPacket)
{
  CExtCharMysteryGift::SendMysteryGiftInfo(this, 1);
  return 0;
}


#####################################
void __cdecl CExtCharMysteryGift::SendMysteryGiftInfo(CExtCharMysteryGift *const this, bool bCheckIndex)
{
  CYunYingHD *PlayerYunYingHd; // rax
  CfgData *v3; // rax
  const CfgMysteryGiftTable *MysteryGiftTable; // rax
  int32_t nIndex; // [rsp+14h] [rbp-Ch]

  if ( this->m_pPlayer )
  {
    PlayerYunYingHd = Player::GetPlayerYunYingHd(this->m_pPlayer);
    if ( CYunYingHD::GetShouChongIconState(PlayerYunYingHd) )
    {
      if ( bCheckIndex )
      {
        nIndex = CExtCharMysteryGift::getIndex(this);
        v3 = Answer::Singleton<CfgData>::instance();
        MysteryGiftTable = CfgData::GetMysteryGiftTable(v3);
        CfgMysteryGiftTable::GetGiftInfo(MysteryGiftTable, nIndex);
      }
    }
  }
}


#####################################
int32_t __cdecl CExtCharMysteryGift::getLeftTime(CExtCharMysteryGift *const this)
{
  int nNowTime; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  if ( CExtCharMysteryGift::getIndex(this) == 1 )
    return 0;
  nNowTime = Unit::getNow(this->m_pPlayer);
  return Answer::DayTime::dayzero(nNowTime) + 86400 - nNowTime;
}


#####################################
int64_t __cdecl CExtCharMysteryGift::getCondition(CExtCharMysteryGift *const this)
{
  int32_t Index; // ebx
  CfgData *v2; // rax
  const CfgMysteryGiftTable *MysteryGiftTable; // rax
  int nType; // eax
  const CfgMysteryGift *pCfg; // [rsp+18h] [rbp-18h]

  Index = CExtCharMysteryGift::getIndex(this);
  v2 = Answer::Singleton<CfgData>::instance();
  MysteryGiftTable = CfgData::GetMysteryGiftTable(v2);
  pCfg = CfgMysteryGiftTable::GetGiftInfo(MysteryGiftTable, Index);
  if ( !pCfg )
    return 0;
  nType = pCfg->nType;
  switch ( nType )
  {
    case 2:
      return Player::GetTodayUsedGold(this->m_pPlayer);
    case 3:
      return Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
    case 1:
      return Player::GetTodayPayGold(this->m_pPlayer);
  }
  return 0;
}


#####################################
int8_t __cdecl CExtCharMysteryGift::getState(CExtCharMysteryGift *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 1061);
}


#####################################
void __cdecl CExtCharMysteryGift::setState(CExtCharMysteryGift *const this, int8_t nState)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::UpdateLimitCount(OperateLimit, 1061, nState);
  }
}


#####################################
int32_t __cdecl CExtCharMysteryGift::getIndex(CExtCharMysteryGift *const this)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v3; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nIndex = CExtOperateLimit::GetLimitCount(OperateLimit, 1062);
  if ( !nIndex )
  {
    nIndex = 1;
    v3 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::UpdateLimitCount(v3, 1062, 1);
  }
  return nIndex;
}


#####################################
void __cdecl CExtCharMysteryGift::addIndex(CExtCharMysteryGift *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1062, 1);
  }
}


#####################################
void __cdecl CExtCharMysteryGift::broadcastGetGift(CExtCharMysteryGift *const this, int32_t nBroadId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v6; // bl
  GameService *v7; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nBroadId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v7, v6, packet);
    }
  }
}


