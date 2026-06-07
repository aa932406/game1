// Decompiled methods for class: CBlackMarket
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl CBlackMarket::~CBlackMarket(CBlackMarket *const this)
{
  CBlackMarket::~CBlackMarket(this);
  operator delete(this);
}


#####################################
void __cdecl CBlackMarket::GetInterestsProtocol(CBlackMarket *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 956;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 957;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 958;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CBlackMarket::DispatchNetDatas(CBlackMarket *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x3BDu:
      return CBlackMarket::onEnterMarket(this, inPacket);
    case 0x3BEu:
      return CBlackMarket::onBuyMarketGoods(this, inPacket);
    case 0x3BCu:
      return CBlackMarket::onRequestMarketInfo(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CBlackMarket::onRequestMarketInfo(CBlackMarket *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 2;
  CBlackMarket::sendMarketInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CBlackMarket::onEnterMarket(CBlackMarket *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CfgData *v5; // rax
  CExtCharBag *v6; // rax
  CExtOperateLimit *v7; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v11; // rax
  MemChrBag bagSlot; // [rsp+10h] [rbp-50h] BYREF
  int32_t nSlot; // [rsp+34h] [rbp-2Ch]
  CfgItem *pCfgItem; // [rsp+38h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 2041) > 0 )
    return 10002;
  nSlot = Answer::NetPacket::readInt32(inPacket);
  if ( nSlot >= 0 )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    bagSlot = *CExtCharBag::GetSlotData(Bag, nSlot);
    if ( bagSlot.itemClass != 1 || bagSlot.itemCount <= 0 )
      return 10002;
    v5 = Answer::Singleton<CfgData>::instance();
    pCfgItem = CfgData::getItem(v5, bagSlot.itemId);
    if ( !pCfgItem )
      return 10002;
    if ( pCfgItem->type != 167 )
      return 10002;
    --bagSlot.itemCount;
    v6 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::SetSlotData(v6, nSlot, &bagSlot, ITEM_CHANGE_REASON::ICR_BLACK_MARKET_ENTER_TICKET, 0);
  }
  else if ( !Player::DecCurrency(
               this->m_pPlayer,
               CURRENCY_TYPE::CURRENCY_GOLD,
               100,
               CURRENCY_CHANGE_REASON::GCR_BLACK_MARCKET_ENTER_TICKET,
               0) )
  {
    return 10002;
  }
  v7 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v7, 2041, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v11, ConnId, GateIndex, Proc, 1);
  return 0;
}


#####################################
int32_t __cdecl CBlackMarket::onBuyMarketGoods(CBlackMarket *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CfgData *v4; // rax
  Job_t Job; // r12
  CfgData *v6; // rax
  const CfgBlacketMarketTable *BlacketMarketTable; // rax
  CExtOperateLimit *v8; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  int8_t nIndex; // [rsp+1Bh] [rbp-35h]
  int32_t nDay; // [rsp+1Ch] [rbp-34h]
  const CfgBlackMarketGoods *pCfgGoods; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 2041) <= 0 )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  nDay = CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL);
  Job = Player::getJob(this->m_pPlayer);
  v6 = Answer::Singleton<CfgData>::instance();
  BlacketMarketTable = CfgData::GetBlacketMarketTable(v6);
  pCfgGoods = CfgBlacketMarketTable::GetGoods(BlacketMarketTable, nDay + 1, nIndex + 1, Job);
  if ( !pCfgGoods )
    return 2;
  v8 = Player::GetOperateLimit(this->m_pPlayer);
  nOldRecord = CExtOperateLimit::GetLimitCount(v8, 2042);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 2;
  if ( pCfgGoods->nPrice <= 0 || Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < pCfgGoods->nPrice )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGoods->item, ITEM_CHANGE_REASON::ICR_BLACK_MARKET_BUY_GOODS) )
    return 2;
  Player::DecCurrency(
    this->m_pPlayer,
    CURRENCY_TYPE::CURRENCY_GOLD,
    pCfgGoods->nPrice,
    CURRENCY_CHANGE_REASON::GCR_BLACK_MARCKET_BUY_GOODS,
    0);
  Player::updateRecord(this->m_pPlayer, 2042, nNewRecord);
  if ( pCfgGoods->nBroadcast > 0 )
    CBlackMarket::broadcastBuyItem(this, pCfgGoods->nBroadcast, &pCfgGoods->item);
  CBlackMarket::SendMarketIcon(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v14, ConnId, GateIndex, Proc, nIndex);
  return 0;
}


#####################################
void __cdecl CBlackMarket::sendMarketInfo(CBlackMarket *const this)
{
  CfgData *v1; // rax
  Job_t Job; // bl
  CfgData *v3; // rax
  const CfgBlacketMarketTable *BlacketMarketTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  int8_t ConnId; // bl
  GameService *v7; // rax
  CExtOperateLimit *v8; // rax
  int8_t LimitCount; // dl
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  int32_t nDay; // [rsp+1Ch] [rbp-34h]
  int nRecord; // [rsp+2Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int8_t i; // [rsp+3Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    nDay = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
    Job = Player::getJob(this->m_pPlayer);
    v3 = Answer::Singleton<CfgData>::instance();
    BlacketMarketTable = CfgData::GetBlacketMarketTable(v3);
    if ( CfgBlacketMarketTable::GetGoods(BlacketMarketTable, nDay + 1, 1, Job) )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      nRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 2042);
      ConnId = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F18u);
      if ( packet )
      {
        v8 = Player::GetOperateLimit(this->m_pPlayer);
        LimitCount = CExtOperateLimit::GetLimitCount(v8, 2041);
        Answer::NetPacket::writeInt8(packet, LimitCount);
        Answer::NetPacket::writeInt8(packet, 4);
        for ( i = 0; i <= 3; ++i )
          Answer::NetPacket::writeInt8(packet, (nRecord >> i) & 1);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v12 = Player::getConnId(this->m_pPlayer);
        v13 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v13, v12, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CBlackMarket::SendMarketIcon(CBlackMarket *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    CBlackMarket::getMarketIconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
void __cdecl CBlackMarket::GetMarketIconState(CBlackMarket *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( CBlackMarket::checkBuyRecord(this) )
    {
      CBlackMarket::getMarketIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
bool __cdecl CBlackMarket::checkBuyRecord(CBlackMarket *const this)
{
  CfgData *v2; // rax
  CfgData *v3; // rax
  Job_t Job; // bl
  CfgData *v5; // rax
  const CfgBlacketMarketTable *BlacketMarketTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t nDay; // [rsp+1Ch] [rbp-24h]
  int32_t nRecord; // [rsp+28h] [rbp-18h]
  int8_t i; // [rsp+2Fh] [rbp-11h]

  if ( !this->m_pPlayer )
    return 0;
  v2 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v2) )
    return 0;
  v3 = Answer::Singleton<CfgData>::instance();
  nDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
  Job = Player::getJob(this->m_pPlayer);
  v5 = Answer::Singleton<CfgData>::instance();
  BlacketMarketTable = CfgData::GetBlacketMarketTable(v5);
  if ( !CfgBlacketMarketTable::GetGoods(BlacketMarketTable, nDay + 1, 1, Job) )
    return 0;
  nRecord = 0;
  for ( i = 0; i <= 3; ++i )
    nRecord |= 1 << i;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  return CExtOperateLimit::GetLimitCount(OperateLimit, 2042) != nRecord;
}


#####################################
void __cdecl CBlackMarket::broadcastBuyItem(CBlackMarket *const this, int32_t nBroadcast, const MemChrBag *const item)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nBroadcast);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, item->itemId);
      Answer::NetPacket::writeInt8(packet, item->itemClass);
      Answer::NetPacket::writeInt32(packet, item->itemCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


