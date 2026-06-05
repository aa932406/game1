// Decompiled methods for class: CExtCharDraw
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl CExtCharDraw::~CExtCharDraw(CExtCharDraw *const this)
{
  CExtCharDraw::~CExtCharDraw(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharDraw::GetInterestsProtocol(CExtCharDraw *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 920;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CExtCharDraw::DispatchNetDatas(CExtCharDraw *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 920 )
    return CExtCharDraw::OnDraw(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharDraw::OnDraw(CExtCharDraw *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const CfgDrawTable *DrawTable; // rax
  CExtCharBag *Bag; // rax
  int64_t nIndex; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  int8_t v11; // bl
  GameService *v12; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v15; // bl
  GameService *v16; // rax
  CfgDrawReward pReward; // [rsp+10h] [rbp-80h] BYREF
  int32_t GetItemList; // [rsp+4Ch] [rbp-44h] BYREF
  std::string val; // [rsp+50h] [rbp-40h] BYREF
  int8_t nType; // [rsp+67h] [rbp-29h]
  Answer::NetPacket *packet; // [rsp+68h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( !CExtCharDraw::canDraw(this, nType) )
    return 10002;
  GetItemList = CExtCharDraw::GetItemRecord(this, nType);
  v3 = Answer::Singleton<CfgData>::instance();
  DrawTable = CfgData::GetDrawTable(v3);
  CfgDrawTable::RandomReward(&pReward, DrawTable, nType, &GetItemList);
  if ( std::vector<MemChrBag>::empty(&pReward.vItem) )
  {
    v2 = 10002;
  }
  else
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, &pReward.vItem, ITEM_CHANGE_REASON::ICR_DRAW_GET_REWARD2) )
    {
      v2 = 10002;
    }
    else
    {
      CExtCharDraw::addDrawTimes(this, nType, GetItemList);
      nIndex = pReward.nIndex;
      Proc = Answer::NetPacket::getProc(inPacket);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::replySuccess(v10, ConnId, GateIndex, Proc, nIndex);
      if ( pReward.nBroad > 0 )
      {
        v11 = Player::getConnId(this->m_pPlayer);
        v12 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v12, v11, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( packet )
        {
          Answer::NetPacket::writeInt32(packet, pReward.nBroad);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          Cid = Player::getCid(this->m_pPlayer);
          Answer::NetPacket::writeInt64(packet, Cid);
          Answer::NetPacket::writeInt32(packet, pReward.nIndex);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v15 = Player::getConnId(this->m_pPlayer);
          v16 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v16, v15, packet);
        }
      }
      v2 = 0;
    }
  }
  CfgDrawReward::~CfgDrawReward(&pReward);
  return v2;
}


#####################################
int32_t __cdecl CExtCharDraw::GetItemRecord(CExtCharDraw *const this, int8_t nType)
{
  switch ( nType )
  {
    case 1:
      return 0;
    case 2:
      return Player::getRecord(this->m_pPlayer, 1608);
    case 3:
      return Player::getRecord(this->m_pPlayer, 1633);
    case 4:
      return Player::getRecord(this->m_pPlayer, 1404);
  }
  return 0;
}


#####################################
bool __cdecl CExtCharDraw::canDraw(CExtCharDraw *const this, int8_t nType)
{
  CExtChrTaskCycle *CharTaskCycle; // rax
  int32_t DrawTimes; // ebx
  CExtOperateLimit *OperateLimit; // rax
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v7; // rax
  Player *v8; // rbx
  CFestivalDoubleEleven *v9; // rax
  Player *v10; // rbx
  CUniteServer *v11; // rax

  switch ( nType )
  {
    case 1:
      CharTaskCycle = Player::GetCharTaskCycle(this->m_pPlayer);
      DrawTimes = CExtChrTaskCycle::GetDrawTimes(CharTaskCycle);
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      if ( DrawTimes > CExtOperateLimit::GetLimitCount(OperateLimit, 2032) )
        return 1;
      break;
    case 2:
      m_pPlayer = this->m_pPlayer;
      v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      if ( CFestivalDoubleEleven::CanUseXiaoFeiDraw(v7, m_pPlayer) )
        return 1;
      break;
    case 3:
      v8 = this->m_pPlayer;
      v9 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      if ( CFestivalDoubleEleven::CanUseRechargeDraw(v9, v8) )
        return 1;
      break;
    case 4:
      v10 = this->m_pPlayer;
      v11 = Answer::Singleton<CUniteServer>::instance();
      if ( CUniteServer::GetCanXiaoFeiDrawTime(v11, v10) > 0 )
        return 1;
      break;
  }
  return 0;
}


#####################################
void __cdecl CExtCharDraw::addDrawTimes(CExtCharDraw *const this, int8_t nType, int32_t GetItemRecord)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v6; // rax
  CExtOperateLimit *v7; // rax
  Player *v8; // rbx
  CFestivalDoubleEleven *v9; // rax
  CExtOperateLimit *v10; // rax
  Player *v11; // rbx
  CUniteServer *v12; // rax

  switch ( nType )
  {
    case 1:
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 2032, 1);
      break;
    case 2:
      Player::updateRecord(this->m_pPlayer, 1608, GetItemRecord);
      v4 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(v4, 1606, 1);
      m_pPlayer = this->m_pPlayer;
      v6 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      CFestivalDoubleEleven::SendIconState(v6, m_pPlayer);
      break;
    case 3:
      Player::updateRecord(this->m_pPlayer, 1633, GetItemRecord);
      v7 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(v7, 1632, 1);
      v8 = this->m_pPlayer;
      v9 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      CFestivalDoubleEleven::SendIconState(v9, v8);
      break;
    case 4:
      Player::updateRecord(this->m_pPlayer, 1404, GetItemRecord);
      v10 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(v10, 1403, 1);
      v11 = this->m_pPlayer;
      v12 = Answer::Singleton<CUniteServer>::instance();
      CUniteServer::SendIconState(v12, v11);
      break;
  }
}


