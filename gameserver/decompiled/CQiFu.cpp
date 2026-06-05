// Decompiled methods for class: CQiFu
// Source: gameserver.cc
// Total methods: 9

#####################################
void __cdecl CQiFu::~CQiFu(CQiFu *const this)
{
  CQiFu::~CQiFu(this);
  operator delete(this);
}


#####################################
void __cdecl CQiFu::GetInterestsProtocol(CQiFu *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 454;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 455;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CQiFu::DispatchNetDatas(CQiFu *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 454 )
  {
    CQiFu::SendQiFuInfo(this);
    return 0;
  }
  else if ( nProcId == 455 )
  {
    return CQiFu::OnQiFu(this, inPacket);
  }
  else
  {
    return 2;
  }
}


#####################################
bool __cdecl CQiFu::CheckQiFuType(CQiFu *const this, int8_t Type)
{
  return Type == 1 || Type == 2;
}


#####################################
int32_t __cdecl CQiFu::OnQiFu(CQiFu *const this, Answer::NetPacket *inPacket)
{
  CVip *PlayerVip; // rax
  CfgData *v4; // rax
  VipTable *VipTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v7; // rax
  int32_t v8; // r12d
  CfgData *v9; // rax
  CQiFuTable *QiFuTable; // rax
  Answer::Random *v11; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v13; // rax
  CExtOperateLimit *v14; // rax
  CExtOperateLimit *v15; // rax
  CExtOperateLimit *v16; // rax
  int64_t v17; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v21; // rax
  ItemData Item; // [rsp+10h] [rbp-60h] BYREF
  int8_t Type; // [rsp+22h] [rbp-4Eh]
  int8_t Times; // [rsp+23h] [rbp-4Dh]
  int32_t QiFuMoneyTimes; // [rsp+24h] [rbp-4Ch]
  int32_t QiFuExpTimes; // [rsp+28h] [rbp-48h]
  int8_t VipLevel; // [rsp+2Fh] [rbp-41h]
  QiFuCfg *pQiFuCfg; // [rsp+38h] [rbp-38h]
  int32_t CriticalStrike; // [rsp+40h] [rbp-30h]
  int32_t nRand; // [rsp+44h] [rbp-2Ch]
  bool bFree; // [rsp+4Bh] [rbp-25h]
  int32_t AddCount; // [rsp+4Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Type = Answer::NetPacket::readInt8(inPacket);
  if ( !CQiFu::CheckQiFuType(this, Type) )
    return 2;
  Times = 0;
  QiFuMoneyTimes = 0;
  QiFuExpTimes = 0;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  VipLevel = CVip::GetVipLevel(PlayerVip);
  v4 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v4);
  if ( !VipTable::GetVipCfg(VipTable, VipLevel) )
    return 2;
  if ( Type == 1 )
  {
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    Times = CExtOperateLimit::GetLimitCount(OperateLimit, 8004);
    if ( Times >= QiFuMoneyTimes )
      return 2;
  }
  else
  {
    if ( Type != 2 )
      return 2;
    v7 = Player::GetOperateLimit(this->m_pPlayer);
    Times = CExtOperateLimit::GetLimitCount(v7, 8005);
    if ( Times >= QiFuExpTimes )
      return 2;
  }
  v8 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v9 = Answer::Singleton<CfgData>::instance();
  QiFuTable = CfgData::GetQiFuTable(v9);
  pQiFuCfg = CQiFuTable::GetQiFuCfg(QiFuTable, Type, v8, Times + 1);
  if ( !pQiFuCfg )
    return 2;
  CriticalStrike = 1;
  v11 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v11, 1, 100);
  if ( pQiFuCfg->Rate >= nRand )
    CriticalStrike = 2;
  *(_QWORD *)&Item.m_nId = 0;
  Item.m_nCount = 0;
  Item.m_nClass = pQiFuCfg->CostItemClass;
  Item.m_nCount = pQiFuCfg->CostItemCount;
  Item.m_nId = pQiFuCfg->CostItemId;
  if ( (Item.m_nId <= 0 || Item.m_nCount <= 0) && pQiFuCfg->CostGold < 0 )
    return 2;
  bFree = 1;
  if ( Item.m_nId > 0 && Item.m_nCount > 0 )
  {
    bFree = 0;
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, &Item, ITEM_CHANGE_REASON::ICR_QI_FU) )
      return 2;
  }
  if ( pQiFuCfg->CostGold > 0 )
  {
    bFree = 0;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            pQiFuCfg->CostGold,
            CURRENCY_CHANGE_REASON::GCR_QI_FU,
            Times) )
      return 2;
  }
  AddCount = 0;
  if ( pQiFuCfg->GetExp > 0 )
  {
    AddCount = CriticalStrike * pQiFuCfg->GetExp;
    Player::AddCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH, AddCount, CURRENCY_CHANGE_REASON::MCR_QI_FU, 0);
  }
  if ( pQiFuCfg->GetMoney > 0 )
  {
    AddCount = CriticalStrike * pQiFuCfg->GetMoney;
    Player::AddCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_MONEY, AddCount, CURRENCY_CHANGE_REASON::MCR_QI_FU, 0);
  }
  if ( Type == 1 )
  {
    v13 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(v13, 8004, 1);
    v14 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(v14, 8006, AddCount);
  }
  else if ( Type == 2 )
  {
    v15 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(v15, 8005, 1);
    v16 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(v16, 8007, AddCount);
  }
  CQiFu::SendQiFuInfo(this);
  CQiFu::SendQiFuSuccess(this, Type, AddCount, CriticalStrike);
  CQiFu::SendQIFuIcon(this);
  v17 = AddCount;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v21 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v21, ConnId, GateIndex, Proc, v17);
  return 0;
}


#####################################
void __cdecl CQiFu::SendQiFuSuccess(CQiFu *const this, int8_t Type, int32_t AddCount, int8_t Double)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD4u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt32(packet, AddCount);
      Answer::NetPacket::writeInt8(packet, Double);
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
void __cdecl CQiFu::SendQiFuInfo(CQiFu *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CExtOperateLimit *OperateLimit; // rax
  int8_t LimitCount; // dl
  CExtOperateLimit *v5; // rax
  int8_t v6; // dl
  CExtOperateLimit *v7; // rax
  int32_t v8; // edx
  CExtOperateLimit *v9; // rax
  int32_t v10; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD3u);
    if ( packet )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 8004);
      Answer::NetPacket::writeInt8(packet, LimitCount);
      v5 = Player::GetOperateLimit(this->m_pPlayer);
      v6 = CExtOperateLimit::GetLimitCount(v5, 8005);
      Answer::NetPacket::writeInt8(packet, v6);
      v7 = Player::GetOperateLimit(this->m_pPlayer);
      v8 = CExtOperateLimit::GetLimitCount(v7, 8006);
      Answer::NetPacket::writeInt32(packet, v8);
      v9 = Player::GetOperateLimit(this->m_pPlayer);
      v10 = CExtOperateLimit::GetLimitCount(v9, 8007);
      Answer::NetPacket::writeInt32(packet, v10);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v13 = Player::getConnId(this->m_pPlayer);
      v14 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v14, v13, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CQiFu::GetQiFuStu(CQiFu *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 57) )
    {
      CQiFu::GetShowIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CQiFu::SendQIFuIcon(CQiFu *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 57) )
    {
      CQiFu::GetShowIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


