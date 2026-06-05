// Decompiled methods for class: CGuardPrivilege
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CGuardPrivilege::~CGuardPrivilege(CGuardPrivilege *const this)
{
  CGuardPrivilege::~CGuardPrivilege(this);
  operator delete(this);
}


#####################################
void __cdecl CGuardPrivilege::OnUpdate(CGuardPrivilege *const this, int64_t curTick)
{
  int8_t nState; // [rsp+1Fh] [rbp-1h]

  if ( CGuardPrivilege::isOpen(this) && curTick - this->m_nLastTick > 999 )
  {
    this->m_nLastTick = curTick;
    nState = CGuardPrivilege::getTimeState(this);
    if ( this->m_nState != nState )
    {
      this->m_nState = nState;
      CGuardPrivilege::sendIconState(this);
    }
  }
}


#####################################
void __cdecl CGuardPrivilege::GetInterestsProtocol(CGuardPrivilege *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 980;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 981;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 20259;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CGuardPrivilege::DispatchNetDatas(
        CGuardPrivilege *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CGuardPrivilege::isOpen(this) )
    return 2;
  switch ( nProcId )
  {
    case 0x3D5u:
      return CGuardPrivilege::onGetReward(this, inPacket);
    case 0x4F23u:
      return CGuardPrivilege::onDBGetReward(this, inPacket);
    case 0x3D4u:
      return CGuardPrivilege::onRequestInfo(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CGuardPrivilege::onRequestInfo(CGuardPrivilege *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 2;
  CGuardPrivilege::sendInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CGuardPrivilege::onGetReward(CGuardPrivilege *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgGuardPrivilegeTable *GuardPrivilegeTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t param; // r15d
  int32_t Sid; // r14d
  int64_t Uid; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  DBService *v11; // rax
  int8_t type; // [rsp+1Ch] [rbp-64h]
  int8_t nIndex; // [rsp+37h] [rbp-49h]
  const CfgGuardPrivilege *pReward; // [rsp+38h] [rbp-48h]
  int32_t nRecord; // [rsp+44h] [rbp-3Ch]
  int32_t nOldRecord; // [rsp+48h] [rbp-38h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  GuardPrivilegeTable = CfgData::GetGuardPrivilegeTable(v3);
  pReward = CfgGuardPrivilegeTable::GetGuardPrivilege(GuardPrivilegeTable, nIndex);
  if ( !pReward )
    return 10002;
  nRecord = 1109;
  if ( pReward->nDaily == 1 )
    nRecord = 2053;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, nRecord);
  if ( nOldRecord == (nOldRecord | (1 << nIndex)) )
    return 10002;
  param = pReward->nParam;
  type = pReward->nType;
  Sid = Player::getSid(this->m_pPlayer);
  Uid = Player::getUid(this->m_pPlayer);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<DBService>::instance();
  DBService::CheckGuardPrivilege(v11, ConnId, GateIndex, Uid, Sid, type, param, nIndex);
  return 0;
}


#####################################
int32_t __cdecl CGuardPrivilege::onDBGetReward(CGuardPrivilege *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgGuardPrivilegeTable *GuardPrivilegeTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  int8_t nIndex; // [rsp+16h] [rbp-3Ah]
  const CfgGuardPrivilege *pReward; // [rsp+18h] [rbp-38h]
  int32_t nRecord; // [rsp+24h] [rbp-2Ch]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( !Answer::NetPacket::readInt8(inPacket) )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  GuardPrivilegeTable = CfgData::GetGuardPrivilegeTable(v3);
  pReward = CfgGuardPrivilegeTable::GetGuardPrivilege(GuardPrivilegeTable, nIndex);
  if ( !pReward )
    return 10002;
  nRecord = 1109;
  if ( pReward->nDaily == 1 )
    nRecord = 2053;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, nRecord);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pReward->vReward, ITEM_CHANGE_REASON::ICR_GUARD_PRIVILEGE_REWARD) )
    return 10002;
  v7 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v7, nRecord, nNewRecord);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, 0x3D5u, nIndex);
  return 0;
}


#####################################
void __cdecl CGuardPrivilege::sendInfo(CGuardPrivilege *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CfgData *v3; // rax
  const CfgGuardPrivilegeTable *GuardPrivilegeTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v6; // rax
  int8_t v7; // al
  CExtOperateLimit *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgGuardPrivilege> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgGuardPrivilege> > __x; // [rsp+20h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-38h]
  const CfgGuardPrivilegeMap *mGuardPrivilege; // [rsp+30h] [rbp-30h]
  int32_t nRewardRecord; // [rsp+3Ch] [rbp-24h]
  int32_t nDailyRecord; // [rsp+40h] [rbp-20h]
  int32_t nRechargeSumRecord; // [rsp+44h] [rbp-1Ch]
  const CfgGuardPrivilege *guard; // [rsp+48h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F2Bu);
    if ( packet )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      GuardPrivilegeTable = CfgData::GetGuardPrivilegeTable(v3);
      mGuardPrivilege = CfgGuardPrivilegeTable::GetGuardPrivilegeMap(GuardPrivilegeTable);
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      nRewardRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1109);
      v6 = Player::GetOperateLimit(this->m_pPlayer);
      nDailyRecord = CExtOperateLimit::GetLimitCount(v6, 2053);
      v7 = std::map<signed char,CfgGuardPrivilege>::size(mGuardPrivilege);
      Answer::NetPacket::writeInt8(packet, v7);
      v8 = Player::GetOperateLimit(this->m_pPlayer);
      nRechargeSumRecord = CExtOperateLimit::GetLimitCount(v8, 1104);
      for ( iter._M_node = std::map<signed char,CfgGuardPrivilege>::begin(mGuardPrivilege)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<signed char const,CfgGuardPrivilege>>::operator++(&iter) )
      {
        __x._M_node = std::map<signed char,CfgGuardPrivilege>::end(mGuardPrivilege)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,CfgGuardPrivilege>>::operator!=(&iter, &__x) )
          break;
        guard = &std::_Rb_tree_const_iterator<std::pair<signed char const,CfgGuardPrivilege>>::operator->(&iter)->second;
        Answer::NetPacket::writeInt8(packet, guard->nIndex);
        if ( guard->nDaily == 1 )
          Answer::NetPacket::writeInt8(packet, (nDailyRecord >> guard->nIndex) & 1);
        else
          Answer::NetPacket::writeInt8(packet, (nRewardRecord >> guard->nIndex) & 1);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v11 = Player::getConnId(this->m_pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CGuardPrivilege::isOpen(CGuardPrivilege *const this)
{
  bool v1; // bl
  std::string __lhs; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_pPlayer )
    return 0;
  Player::GetPlatform((const Player *const)&__lhs);
  v1 = std::operator==<char>(&__lhs, "w360");
  std::string::~string(&__lhs);
  return v1;
}


#####################################
int8_t __cdecl CGuardPrivilege::getTimeState(CGuardPrivilege *const this)
{
  CfgData *v2; // rax
  int32_t nNowTime; // [rsp+14h] [rbp-Ch]
  const CfgGuardPrivilegeTable *table; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer )
    return 0;
  nNowTime = Unit::getNow(this->m_pPlayer);
  v2 = Answer::Singleton<CfgData>::instance();
  table = CfgData::GetGuardPrivilegeTable(v2);
  if ( CfgGuardPrivilegeTable::GetStartTime(table) > nNowTime )
    return 0;
  if ( CfgGuardPrivilegeTable::GetEndTime(table) >= nNowTime )
    return 2;
  return 4;
}


#####################################
void __cdecl CGuardPrivilege::GetIconState(CGuardPrivilege *const this, IconStateList *const iconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( CGuardPrivilege::isOpen(this) && CGuardPrivilege::getTimeState(this) == 2 )
  {
    *(_QWORD *)&icon.nId = 0x20000003ELL;
    *(_QWORD *)&icon.nLeftTime = 0;
    *(_QWORD *)&icon.nIconRight = 0;
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
void __cdecl CGuardPrivilege::sendIconState(CGuardPrivilege *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  ShowIcon stu; // [rsp+10h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      CGuardPrivilege::getIconState(&stu, this);
      Answer::NetPacket::writeInt32(packet, stu.nId);
      Answer::NetPacket::writeInt8(packet, stu.nState);
      Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
      Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
      Answer::NetPacket::writeInt32(packet, stu.nIconRight);
      Answer::NetPacket::writeInt8(packet, stu.nEffects);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


