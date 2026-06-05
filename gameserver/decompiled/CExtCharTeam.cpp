// Decompiled methods for class: CExtCharTeam
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl CExtCharTeam::~CExtCharTeam(CExtCharTeam *const this)
{
  CExtCharTeam::~CExtCharTeam(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharTeam::OnCleanUp(CExtCharTeam *const this)
{
  this->m_nTeamId = 0;
  this->m_nLastQueryTeamTick = 0;
  this->m_nLeaderId = 0;
  std::string::operator=(&this->m_strLeaderName, &unk_8CC460);
  std::list<TeamMember>::clear(&this->m_lstMember);
}


#####################################
void __cdecl CExtCharTeam::GetInterestsProtocol(CExtCharTeam *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 46;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 720;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 20067;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CExtCharTeam::DispatchNetDatas(CExtCharTeam *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharTeam::IsFunctionOpen(this) )
    return 2;
  switch ( nProcId )
  {
    case 0x2D0u:
      return CExtCharTeam::onSetTeamAutoOperate(this, inPacket);
    case 0x4E63u:
      return CExtCharTeam::onUpdateTeamInfo(this, inPacket);
    case 0x2Eu:
      return CExtCharTeam::onQueryTeamsAround(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeam::onQueryTeamsAround(CExtCharTeam *const this, Answer::NetPacket *inPacket)
{
  Map *pMap; // [rsp+10h] [rbp-10h]
  int64_t nCurTick; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 10002;
  nCurTick = Unit::getTick(this->m_pPlayer);
  if ( nCurTick - this->m_nLastQueryTeamTick <= 4999 )
    return 10002;
  this->m_nLastQueryTeamTick = nCurTick;
  Map::sendTeamsInMap(pMap, this->m_pPlayer);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeam::onSetTeamAutoOperate(CExtCharTeam *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int8_t bAutoAcceptInvite; // [rsp+1Eh] [rbp-12h]
  int8_t bAutoAcceptApply; // [rsp+1Fh] [rbp-11h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  bAutoAcceptInvite = Answer::NetPacket::readInt8(inPacket);
  bAutoAcceptApply = Answer::NetPacket::readInt8(inPacket);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(OperateLimit, 37201, bAutoAcceptInvite);
  v4 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v4, 37202, bAutoAcceptApply);
  CExtCharTeam::UpdateTeamSetting(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeam::onUpdateTeamInfo(CExtCharTeam *const this, Answer::NetPacket *inPacket)
{
  std::string strName; // [rsp+10h] [rbp-70h] BYREF
  Answer::NetPacket v4; // [rsp+20h] [rbp-60h] BYREF
  CharId_t nCharId; // [rsp+60h] [rbp-20h]
  int16_t nIndex; // [rsp+6Eh] [rbp-12h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  BYTE3(v4.m_pool) = std::list<TeamMember>::size(&this->m_lstMember);
  std::list<TeamMember>::clear(&this->m_lstMember);
  HIDWORD(v4.m_pool) = this->m_nTeamId;
  v4.m_autoIncrease = Answer::NetPacket::readInt32(inPacket);
  if ( this->m_nTeamId != v4.m_autoIncrease )
    this->m_nTeamId = v4.m_autoIncrease;
  this->m_nLeaderId = Answer::NetPacket::readInt64(inPacket);
  Answer::NetPacket::readUTF8(&v4, (bool)inPacket);
  std::string::operator=(&this->m_strLeaderName, &v4);
  std::string::~string(&v4);
  *((_BYTE *)&v4.m_autoIncrease + 6) = Answer::NetPacket::readInt8(inPacket);
  *((_BYTE *)&v4.m_autoIncrease + 7) = 0;
  while ( *((char *)&v4.m_autoIncrease + 7) < *((char *)&v4.m_autoIncrease + 6) )
  {
    nCharId = Answer::NetPacket::readInt64(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)&strName, (bool)inPacket);
    nIndex = Answer::NetPacket::readInt16(inPacket);
    TeamMember::TeamMember((TeamMember *const)&v4.m_wOffset, nCharId, &strName, nIndex);
    std::list<TeamMember>::push_back(&this->m_lstMember, (const TeamMember *const)&v4.m_wOffset);
    TeamMember::~TeamMember((TeamMember *const)&v4.m_wOffset);
    std::string::~string(&strName);
    ++*((_BYTE *)&v4.m_autoIncrease + 7);
  }
  if ( this->m_nTeamId != HIDWORD(v4.m_pool) )
    Player::setBossRankTeamChange(this->m_pPlayer);
  Player::setSyncStatusFlag(this->m_pPlayer);
  return 0;
}


#####################################
bool __cdecl CExtCharTeam::IsLeader(const CExtCharTeam *const this)
{
  return this->m_pPlayer && Player::getCid(this->m_pPlayer) == this->m_nLeaderId;
}


#####################################
std::string __cdecl CExtCharTeam::GetLeaderName(const CExtCharTeam *const this)
{
  const std::string *v1; // rsi

  std::string::string((std::string *)this, v1 + 5);
  return (std::string)this;
}


#####################################
void __cdecl CExtCharTeam::Broadcast(CExtCharTeam *const this, Answer::NetPacket *inPacket)
{
  TeamMember *v2; // rax
  int8_t ConnId; // r12
  GameService *v4; // rax
  std::_List_iterator<TeamMember> it; // [rsp+10h] [rbp-40h] BYREF
  Int16List indexList; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<TeamMember> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( inPacket && this->m_pPlayer )
  {
    std::list<short>::list(&indexList);
    for ( it._M_node = std::list<TeamMember>::begin(&this->m_lstMember)._M_node;
          ;
          std::_List_iterator<TeamMember>::operator++(&it) )
    {
      __x._M_node = std::list<TeamMember>::end(&this->m_lstMember)._M_node;
      if ( !std::_List_iterator<TeamMember>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<TeamMember>::operator->(&it)->nIndex > 0 )
      {
        v2 = std::_List_iterator<TeamMember>::operator->(&it);
        std::list<short>::push_back(&indexList, &v2->nIndex);
      }
    }
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v4, inPacket, ConnId, &indexList);
    Answer::NetPacket::destroy(inPacket);
    std::list<short>::~list(&indexList);
  }
}


#####################################
void __cdecl CExtCharTeam::LeaveTeam(CExtCharTeam *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  CharId_t Cid; // rdx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && CExtCharTeam::IsInTeam(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA1u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
void __cdecl CExtCharTeam::GetTeamMembers(const CExtCharTeam *const this, CharIdList *const members)
{
  const TeamMember *v2; // rdx
  std::_List_const_iterator<TeamMember> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<TeamMember> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<TeamMember>::begin(&this->m_lstMember)._M_node;
  eiter._M_node = std::list<TeamMember>::end(&this->m_lstMember)._M_node;
  while ( std::_List_const_iterator<TeamMember>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_const_iterator<TeamMember>::operator->(&iter);
    std::list<long>::push_back(members, &v2->nCharId);
    std::_List_const_iterator<TeamMember>::operator++(&iter);
  }
}


#####################################
void __cdecl CExtCharTeam::BroadcastBasicData(CExtCharTeam *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CharId_t Cid; // rsi
  int32_t v4; // edx
  int32_t MainWeaponId; // edx
  int32_t ClothesId; // edx
  int32_t WingId; // edx
  int32_t ShiZhuangWeapon; // edx
  int32_t ShiZhuangClothes; // edx
  CShiZhuang *ShiZhuang; // rax
  int32_t EffectId; // edx
  CExtCharTencent *CharTencent; // rax
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && CExtCharTeam::IsInTeam(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2749u);
    if ( packet )
    {
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      v4 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, v4);
      MainWeaponId = Player::getMainWeaponId(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, MainWeaponId);
      ClothesId = Player::getClothesId(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, ClothesId);
      WingId = Player::getWingId(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, WingId);
      ShiZhuangWeapon = Player::getShiZhuangWeapon(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, ShiZhuangWeapon);
      ShiZhuangClothes = Player::getShiZhuangClothes(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, ShiZhuangClothes);
      ShiZhuang = Player::GetShiZhuang(this->m_pPlayer);
      EffectId = CShiZhuang::GetEffectId(ShiZhuang);
      Answer::NetPacket::writeInt32(packet, EffectId);
      CharTencent = Player::GetCharTencent(this->m_pPlayer);
      CExtCharTencent::AppendInfo(CharTencent, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      CExtCharTeam::Broadcast(this, packet);
    }
  }
}


#####################################
void __cdecl CExtCharTeam::UpdateTeamSetting(CExtCharTeam *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v5; // bl
  GameService *v6; // rax
  int8_t bAutoAcceptInvite; // [rsp+14h] [rbp-1Ch]
  int8_t bAutoAcceptApply; // [rsp+15h] [rbp-1Bh]
  bool bCanInvite; // [rsp+16h] [rbp-1Ah]
  bool bCanAddFriend; // [rsp+17h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  bAutoAcceptInvite = Player::getRecord(this->m_pPlayer, 37201);
  bAutoAcceptApply = Player::getRecord(this->m_pPlayer, 37202);
  bCanInvite = Player::GetSysSettingInfo(this->m_pPlayer, 2);
  bCanAddFriend = Player::GetSysSettingInfo(this->m_pPlayer, 3);
  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA0u);
  if ( packet )
  {
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    Answer::NetPacket::writeInt32(packet, GateIndex);
    Answer::NetPacket::writeInt8(packet, bAutoAcceptInvite);
    Answer::NetPacket::writeInt8(packet, bAutoAcceptApply);
    Answer::NetPacket::writeInt8(packet, bCanInvite);
    Answer::NetPacket::writeInt8(packet, bCanAddFriend);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v6, v5, packet);
  }
}


