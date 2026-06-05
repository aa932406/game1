// Decompiled methods for class: CLevelRefining
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CLevelRefining::~CLevelRefining(CLevelRefining *const this)
{
  CLevelRefining::~CLevelRefining(this);
  operator delete(this);
}


#####################################
void __cdecl CLevelRefining::GetInterestsProtocol(CLevelRefining *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 769;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 768;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CLevelRefining::DispatchNetDatas(
        CLevelRefining *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 768 )
  {
    CLevelRefining::SendRefinInfo(this);
  }
  else if ( nProcId == 769 )
  {
    return CLevelRefining::OnRefining(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CLevelRefining::OnRefining(CLevelRefining *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  int *v5; // rax
  int32_t v6; // ebx
  void (__fastcall *v7)(Player *, _QWORD); // rbx
  unsigned int MaxLevel; // eax
  void (__fastcall *v9)(Player *, _QWORD); // rbx
  int *v10; // rax
  int8_t ConnId; // bl
  GameService *v12; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v15; // bl
  GameService *v16; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v19; // bl
  GameService *v20; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  int32_t nTime; // [rsp+1Ch] [rbp-34h]
  LevelRefinCfg *pCfg; // [rsp+20h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nTime = Player::getRecord(this->m_pPlayer, 2081);
  v3 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v4 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetRefining(v4, v3);
  if ( !pCfg )
    return 10002;
  if ( pCfg->nLimit <= nTime )
    return 10002;
  if ( *std::vector<int>::operator[](&pCfg->vNeedGold, nTime) <= 0 )
    return 10002;
  v5 = std::vector<int>::operator[](&pCfg->vNeedGold, nTime);
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          *v5,
          CURRENCY_CHANGE_REASON::GCR_LEVEL_REFIN,
          0) )
    return 10002;
  v6 = *std::vector<int>::operator[](&pCfg->nLevelUp, nTime);
  if ( v6 <= Player::GetMaxLevel(this->m_pPlayer) )
  {
    v9 = (void (__fastcall *)(Player *, _QWORD))*((_QWORD *)this->m_pPlayer->_vptr_Entity + 33);
    v10 = std::vector<int>::operator[](&pCfg->nLevelUp, nTime);
    v9(this->m_pPlayer, (unsigned int)*v10);
  }
  else
  {
    v7 = (void (__fastcall *)(Player *, _QWORD))*((_QWORD *)this->m_pPlayer->_vptr_Entity + 33);
    MaxLevel = Player::GetMaxLevel(this->m_pPlayer);
    v7(this->m_pPlayer, MaxLevel);
  }
  if ( pCfg->nGongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v12 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v12, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pCfg->nGongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v15 = Player::getConnId(this->m_pPlayer);
      v16 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v16, v15, packet);
    }
  }
  Player::updateRecord(this->m_pPlayer, 2081, nTime + 1);
  CLevelRefining::SendRefinInfo(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v19 = Player::getConnId(this->m_pPlayer);
  v20 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v20, v19, GateIndex, Proc, 0);
  CLevelRefining::SendIcon(this);
  return 0;
}


#####################################
void __cdecl CLevelRefining::SendRefinInfo(CLevelRefining *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D0Au);
  if ( packet )
  {
    Record = Player::getRecord(this->m_pPlayer, 2081);
    Answer::NetPacket::writeInt32(packet, Record);
    LeftTime = CLevelRefining::GetLeftTime(this);
    Answer::NetPacket::writeInt32(packet, LeftTime);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v7 = Player::getConnId(this->m_pPlayer);
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, GateIndex, packet);
  }
}


#####################################
int32_t __cdecl CLevelRefining::GetLeftTime(CLevelRefining *const this)
{
  CfgData *v1; // rax
  int32_t Now; // [rsp+18h] [rbp-8h]

  Now = Unit::getNow(this->m_pPlayer);
  v1 = Answer::Singleton<CfgData>::instance();
  return CfgData::getServerStartDayZeroTime(v1, SERVER_TYPE::SVT_NORMAL) + 259200 - Now;
}


#####################################
void __cdecl CLevelRefining::GetIcon(CLevelRefining *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  CfgData *v4; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF
  int32_t ServerDay; // [rsp+2Ch] [rbp-4h]

  v2 = Answer::Singleton<CfgData>::instance();
  if ( !CfgData::getServerType(v2) )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 186) )
    {
      v4 = Answer::Singleton<CfgData>::instance();
      ServerDay = CfgData::getServerDiffDay(v4, SERVER_TYPE::SVT_NORMAL);
      if ( ServerDay >= 0 && ServerDay + 1 <= 3 )
      {
        CLevelRefining::GetIconStu(&__x, this);
        std::list<ShowIcon>::push_back(IconList, &__x);
      }
    }
  }
}


#####################################
void __cdecl CLevelRefining::SendIcon(CLevelRefining *const this)
{
  CfgData *v1; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::getServerType(v1) )
    {
      CLevelRefining::GetIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


