// Decompiled methods for class: CExtCharHallOfFame
// Source: gameserver.cc
// Total methods: 24

#####################################
void __cdecl CExtCharHallOfFame::~CExtCharHallOfFame(CExtCharHallOfFame *const this)
{
  CExtCharHallOfFame::~CExtCharHallOfFame(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharHallOfFame::GetInterestsProtocol(CExtCharHallOfFame *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+12h] [rbp-Eh] BYREF
  unsigned __int16 v3; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v4; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v5; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v6; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v7; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v8; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 850;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 851;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 852;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 853;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 20078;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 20079;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 20080;
  std::list<unsigned short>::push_back(procList, &v8);
}


#####################################
int32_t __cdecl CExtCharHallOfFame::DispatchNetDatas(
        CExtCharHallOfFame *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharHallOfFame::IsFunctionOpen(this) )
    return 2;
  if ( nProcId == 853 )
    return CExtCharHallOfFame::onRequestInfo(this, inPacket);
  if ( nProcId > 0x355u )
  {
    switch ( nProcId )
    {
      case 0x4E6Fu:
        return CExtCharHallOfFame::onSocialGetReward(this, inPacket);
      case 0x4E70u:
        return CExtCharHallOfFame::onSocialRankRewardInfo(this, inPacket);
      case 0x4E6Eu:
        return CExtCharHallOfFame::onSocialFightResult(this, inPacket);
    }
  }
  else
  {
    if ( nProcId == 851 )
      return CExtCharHallOfFame::onBuyTimes(this, inPacket);
    if ( nProcId > 0x353u )
      return CExtCharHallOfFame::onClearCD(this, inPacket);
    if ( nProcId == 850 )
      return CExtCharHallOfFame::onFight(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onFight(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  int32_t FightTimes; // ebx
  int32_t nIndex; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  FightTimes = CExtCharHallOfFame::getFightTimes(this);
  if ( FightTimes >= CExtCharHallOfFame::getLimitFightTimes(this) )
    return 10002;
  if ( CExtCharHallOfFame::getCDTime(this) > 0 )
    return 10002;
  CExtCharHallOfFame::sendSocialFight(this, nIndex);
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onBuyTimes(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  int32_t BuyTimes; // ebx
  int64_t v4; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  BuyTimes = CExtCharHallOfFame::getBuyTimes(this);
  if ( BuyTimes >= CExtCharHallOfFame::getLimitBuyTimes(this) )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          10,
          CURRENCY_CHANGE_REASON::GCR_HALL_OF_FAME_BUY_TIMES,
          0) )
    return 10002;
  CExtCharHallOfFame::addBuyTimes(this);
  v4 = CExtCharHallOfFame::getBuyTimes(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, v4);
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onClearCD(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  if ( CExtCharHallOfFame::getCDTime(this) <= 0 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          2,
          CURRENCY_CHANGE_REASON::GCR_HALL_OF_FAME_CLEAR_CD,
          0) )
    return 10002;
  CExtCharHallOfFame::clearCDTime(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onRequestInfo(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  CExtCharHallOfFame::sendSocialRequestInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onSocialFightResult(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  ChrTask *Task; // rax
  char bWin; // [rsp+1Fh] [rbp-1h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  bWin = Answer::NetPacket::readInt8(inPacket);
  if ( bWin <= 0 )
  {
    Player::addExp(this->m_pPlayer, 500000, 0, 1);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_HONOR,
      5000,
      CURRENCY_CHANGE_REASON::HCR_HALL_OF_FAME_FIGHT,
      0);
  }
  else
  {
    Player::addExp(this->m_pPlayer, 1000000, 0, 1);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_HONOR,
      10000,
      CURRENCY_CHANGE_REASON::HCR_HALL_OF_FAME_FIGHT,
      0);
  }
  CExtCharHallOfFame::addCDTime(this, bWin > 0);
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::updateTaskCount(Task, 17, 0);
  CExtCharHallOfFame::addFightTimes(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onSocialGetReward(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgHallOfFameTable *HallOfFameTable; // rax
  MemChrBag *v5; // r12
  Time_t endTime; // r13d
  CfgData *v7; // rax
  const CfgLimitTimeTable *LimitTimeTable; // rax
  CExtCharBag *Bag; // rax
  int v10; // r12d
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+10h] [rbp-70h] BYREF
  MemChrBagVector vItem; // [rsp+20h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+40h] [rbp-40h] BYREF
  int32_t nLastIndex; // [rsp+54h] [rbp-2Ch]
  const HallOfFameReward *pReward; // [rsp+58h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nLastIndex = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  HallOfFameTable = CfgData::GetHallOfFameTable(v3);
  pReward = CfgHallOfFameTable::GetReward(HallOfFameTable, nLastIndex);
  if ( !pReward )
    return 10002;
  if ( std::vector<MemChrBag>::empty(&pReward->items) )
    goto LABEL_17;
  std::vector<MemChrBag>::vector(&vItem, &pReward->items);
  for ( iter._M_current = std::vector<MemChrBag>::begin(&vItem)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(&vItem)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
      break;
    if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->endTime <= 0 )
    {
      __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->endTime = 0;
    }
    else
    {
      v5 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter);
      endTime = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->endTime;
      v7 = Answer::Singleton<CfgData>::instance();
      LimitTimeTable = CfgData::GetLimitTimeTable(v7);
      v5->endTime = CfgLimitTimeTable::GetLimitTime(LimitTimeTable, endTime);
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &vItem, ITEM_CHANGE_REASON::ICR_HALL_OF_FAME_REWARD) )
  {
    CExtCharHallOfFame::sendSocialRewardResult(this, nLastIndex, 0);
    v2 = 10002;
    v10 = 0;
  }
  else
  {
    v10 = 1;
  }
  std::vector<MemChrBag>::~vector(&vItem);
  if ( v10 )
  {
LABEL_17:
    CExtCharHallOfFame::sendSocialRewardResult(this, nLastIndex, 1);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_HONOR,
      pReward->nHonor,
      CURRENCY_CHANGE_REASON::HCR_HALL_OF_FAME_RANK_REWARD,
      0);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v13 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v13, ConnId, GateIndex, 0xC32u, 0);
    CExtCharHallOfFame::SendIconState(this, 0);
    return 0;
  }
  return v2;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::onSocialRankRewardInfo(CExtCharHallOfFame *const this, Answer::NetPacket *inPacket)
{
  int8_t nReward; // [rsp+1Fh] [rbp-1h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Answer::NetPacket::readInt32(inPacket);
  nReward = Answer::NetPacket::readInt8(inPacket);
  if ( CExtCharHallOfFame::IsFunctionOpen(this) && !nReward )
    CExtCharHallOfFame::SendIconState(this, 1);
  return 0;
}


#####################################
bool __cdecl CExtCharHallOfFame::IsFunctionOpen(const CExtCharHallOfFame *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 68) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CExtCharHallOfFame::sendSocialFight(CExtCharHallOfFame *const this, int32_t nIndex)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EAEu);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, nIndex);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
void __cdecl CExtCharHallOfFame::sendSocialRequestInfo(CExtCharHallOfFame *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  int32_t LimitFightTimes; // ebx
  int32_t v5; // edx
  int32_t LimitBuyTimes; // ebx
  int32_t v7; // edx
  int32_t CDTime; // edx
  uint32_t WOffset; // edx
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EAFu);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      LimitFightTimes = CExtCharHallOfFame::getLimitFightTimes(this);
      v5 = LimitFightTimes - CExtCharHallOfFame::getFightTimes(this);
      Answer::NetPacket::writeInt32(packet, v5);
      LimitBuyTimes = CExtCharHallOfFame::getLimitBuyTimes(this);
      v7 = LimitBuyTimes - CExtCharHallOfFame::getBuyTimes(this);
      Answer::NetPacket::writeInt32(packet, v7);
      CDTime = CExtCharHallOfFame::getCDTime(this);
      Answer::NetPacket::writeInt32(packet, CDTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      LOBYTE(LimitBuyTimes) = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v10, LimitBuyTimes, packet);
    }
  }
}


#####################################
void __cdecl CExtCharHallOfFame::sendSocialRewardResult(
        CExtCharHallOfFame *const this,
        int32_t nLastIndex,
        bool bSuccess)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EB0u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, nLastIndex);
      Answer::NetPacket::writeInt8(packet, bSuccess);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v8, v7, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharHallOfFame::getFightTimes(const CExtCharHallOfFame *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 2015);
}


#####################################
int32_t __cdecl CExtCharHallOfFame::getBuyTimes(const CExtCharHallOfFame *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 2016);
}


#####################################
int32_t __cdecl CExtCharHallOfFame::getLimitBuyTimes(const CExtCharHallOfFame *const this)
{
  return 0;
}


#####################################
int32_t __cdecl CExtCharHallOfFame::getCDTime(const CExtCharHallOfFame *const this)
{
  CVip *PlayerVip; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t nCDTime; // [rsp+18h] [rbp-8h]
  int32_t nNowTime; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( CVip::GetVipLevel(PlayerVip) > 3 )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nCDTime = CExtOperateLimit::GetLimitCount(OperateLimit, 1033);
  nNowTime = Unit::getNow(this->m_pPlayer);
  if ( nCDTime <= nNowTime )
    return 0;
  else
    return nCDTime - nNowTime;
}


#####################################
void __cdecl CExtCharHallOfFame::addFightTimes(CExtCharHallOfFame *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 2015, 1);
  }
}


#####################################
void __cdecl CExtCharHallOfFame::addBuyTimes(CExtCharHallOfFame *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 2016, 1);
  }
}


#####################################
void __cdecl CExtCharHallOfFame::addCDTime(CExtCharHallOfFame *const this, bool bWin)
{
  CVip *PlayerVip; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int32_t AddTime; // [rsp+14h] [rbp-Ch]
  int32_t nCDTime; // [rsp+18h] [rbp-8h]
  int32_t nCDTimea; // [rsp+18h] [rbp-8h]
  int32_t nNowTime; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pPlayer )
  {
    PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
    if ( CVip::GetVipLevel(PlayerVip) <= 3 )
    {
      if ( bWin )
        AddTime = 180;
      else
        AddTime = 600;
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      nCDTime = CExtOperateLimit::GetLimitCount(OperateLimit, 1033);
      nNowTime = Unit::getNow(this->m_pPlayer);
      if ( nCDTime <= nNowTime )
        nCDTimea = nNowTime + AddTime;
      else
        nCDTimea = AddTime + nCDTime;
      v4 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::UpdateLimitCount(v4, 1033, nCDTimea);
    }
  }
}


#####################################
void __cdecl CExtCharHallOfFame::clearCDTime(CExtCharHallOfFame *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::Reset(OperateLimit, 1033);
  }
}


#####################################
void __cdecl CExtCharHallOfFame::GetIconState(CExtCharHallOfFame *const this, IconStateList *const iconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( CExtCharHallOfFame::IsFunctionOpen(this) )
  {
    *(_QWORD *)&icon.nId = 0x200000019LL;
    *(_QWORD *)&icon.nLeftTime = 0xFFFFFFFFLL;
    *(_QWORD *)&icon.nIconRight = 0;
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
void __cdecl CExtCharHallOfFame::SendIconState(CExtCharHallOfFame *const this, int32_t nReward)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    *(_QWORD *)&stu.nId = 0x200000019LL;
    *(_QWORD *)&stu.nLeftTime = 0xFFFFFFFFLL;
    *(_DWORD *)&stu.nEffects = 0;
    stu.nIconRight = nReward;
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


