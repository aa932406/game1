// Decompiled methods for class: CTestServerReward
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CTestServerReward::~CTestServerReward(CTestServerReward *const this)
{
  CTestServerReward::~CTestServerReward(this);
  operator delete(this);
}


#####################################
void __cdecl CTestServerReward::GetInterestsProtocol(CTestServerReward *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 469;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CTestServerReward::DispatchNetDatas(
        CTestServerReward *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 469 )
    return CTestServerReward::OnGetTestServerReward(this, inPacket);
  return 2;
}


#####################################
int32_t __cdecl CTestServerReward::OnGetTestServerReward(CTestServerReward *const this, Answer::NetPacket *inPacket)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  CfgData *v4; // rax
  int nType; // eax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  GameService *v11; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v14; // rax
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  int32_t nId; // [rsp+24h] [rbp-3Ch]
  TestServerReward *pCfg; // [rsp+28h] [rbp-38h]
  int32_t OldRecord; // [rsp+30h] [rbp-30h]
  int32_t NewRecord; // [rsp+34h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
  if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 192) )
    return 2;
  nId = Answer::NetPacket::readInt32(inPacket);
  v4 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetTestServerReward(v4, nId);
  if ( !pCfg )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1915);
  NewRecord = OldRecord | (1 << (nId - 1));
  if ( NewRecord == OldRecord )
    return 10002;
  nType = pCfg->nType;
  if ( nType == 1 )
  {
    if ( Player::getRecord(this->m_pPlayer, 1011) < pCfg->nParm )
      return 10002;
  }
  else
  {
    if ( nType != 2 )
      return 2;
    if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < pCfg->nParm )
      return 10002;
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vItems, ITEM_CHANGE_REASON::ICR_TEST_SERVER) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1915, NewRecord);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, nId);
  if ( pCfg->nGongId > 0 )
  {
    v11 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v11, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 2;
    Answer::NetPacket::writeInt32(packet, pCfg->nGongId);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Answer::NetPacket::writeInt32(packet, nId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v14 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v14, 0, packet);
  }
  CTestServerReward::SendTestServerIcon(this);
  return 0;
}


#####################################
void __cdecl CTestServerReward::GetTestServerIcon(CTestServerReward *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 192) )
    {
      CTestServerReward::GetTestServerIconStu(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CTestServerReward::SendTestServerIcon(CTestServerReward *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 192) )
    {
      CTestServerReward::GetTestServerIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
int32_t __cdecl CTestServerReward::CanActivationCount(CTestServerReward *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  TestServerRewardMap *TestServerRewardMap; // rax
  std::pair<const int,TestServerReward> *v4; // rax
  int nType; // eax
  int32_t Record; // ebx
  int32_t v7; // ebx
  TestServerRewardMap RewardMap; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,TestServerReward> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,TestServerReward> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t Count; // [rsp+64h] [rbp-1Ch]
  int32_t OldRecord; // [rsp+68h] [rbp-18h]
  int32_t NewRecord; // [rsp+6Ch] [rbp-14h]

  Count = 0;
  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    TestServerRewardMap = CfgData::GetTestServerRewardMap(v2);
    std::map<int,TestServerReward>::map(&RewardMap, TestServerRewardMap);
    it._M_node = std::map<int,TestServerReward>::begin(&RewardMap)._M_node;
    OldRecord = Player::getRecord(this->m_pPlayer, 1915);
    while ( 1 )
    {
      __x._M_node = std::map<int,TestServerReward>::end(&RewardMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator!=(&it, &__x) )
      {
        v1 = Count;
        std::map<int,TestServerReward>::~map(&RewardMap);
        return v1;
      }
      v4 = std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator->(&it);
      NewRecord = OldRecord | (1 << (LOBYTE(v4->first) - 1));
      if ( NewRecord != OldRecord )
      {
        nType = std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator->(&it)->second.nType;
        if ( nType == 1 )
        {
          Record = Player::getRecord(this->m_pPlayer, 1011);
          if ( Record >= std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator->(&it)->second.nParm )
            goto LABEL_11;
        }
        else if ( nType == 2 )
        {
          v7 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
          if ( v7 >= std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator->(&it)->second.nParm )
LABEL_11:
            ++Count;
        }
      }
      std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator++(&it, 0);
    }
  }
  return Count;
}


#####################################
bool __cdecl CTestServerReward::IsAllGetReward(CTestServerReward *const this)
{
  bool v1; // bl
  CfgData *v2; // rax
  TestServerRewardMap *TestServerRewardMap; // rax
  std::pair<const int,TestServerReward> *v4; // rax
  TestServerRewardMap RewardMap; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,TestServerReward> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,TestServerReward> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t OldRecord; // [rsp+58h] [rbp-18h]
  int32_t NewRecord; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 1;
  OldRecord = Player::getRecord(this->m_pPlayer, 1915);
  v2 = Answer::Singleton<CfgData>::instance();
  TestServerRewardMap = CfgData::GetTestServerRewardMap(v2);
  std::map<int,TestServerReward>::map(&RewardMap, TestServerRewardMap);
  for ( it._M_node = std::map<int,TestServerReward>::begin(&RewardMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,TestServerReward>::end(&RewardMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator!=(&it, &__x) )
      break;
    v4 = std::_Rb_tree_iterator<std::pair<int const,TestServerReward>>::operator->(&it);
    NewRecord = OldRecord | (1 << (LOBYTE(v4->first) - 1));
    if ( NewRecord != OldRecord )
    {
      v1 = 0;
      goto LABEL_9;
    }
  }
  v1 = 1;
LABEL_9:
  std::map<int,TestServerReward>::~map(&RewardMap);
  return v1;
}


