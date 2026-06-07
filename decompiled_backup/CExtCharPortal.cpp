// Decompiled methods for class: CExtCharPortal
// Source: gameserver.cc
// Total methods: 16

#####################################
void __cdecl CExtCharPortal::~CExtCharPortal(CExtCharPortal *const this)
{
  CExtCharPortal::~CExtCharPortal(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharPortal::OnCleanUp(CExtCharPortal *const this)
{
  this->m_nPortalId = 0;
  std::list<PortalInfo>::clear(&this->m_lstPortal);
  this->m_nLastTick = 0;
}


#####################################
void __cdecl CExtCharPortal::OnLoadFromDB(CExtCharPortal *const this, const PlayerDBData *const dbData)
{
  std::list<PortalInfo>::operator=(&this->m_lstPortal, &dbData->m_PortalDBData.lstPortal);
  this->m_nPortalId = dbData->m_PortalDBData.nPortalId;
  CExtCharPortal::checkPortalTime(this, 1);
}


#####################################
void __cdecl CExtCharPortal::OnSaveToDB(CExtCharPortal *const this, PlayerDBData *const dbData)
{
  std::list<PortalInfo>::operator=(&dbData->m_PortalDBData.lstPortal, &this->m_lstPortal);
}


#####################################
void __cdecl CExtCharPortal::OnUpdate(CExtCharPortal *const this, int64_t curTick)
{
  if ( this->m_pPlayer )
  {
    if ( curTick - this->m_nLastTick > 999 )
      CExtCharPortal::checkPortalTime(this, 0);
  }
}


#####################################
void __cdecl CExtCharPortal::GetInterestsProtocol(CExtCharPortal *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 809;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 810;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CExtCharPortal::DispatchNetDatas(
        CExtCharPortal *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 809 )
    return CExtCharPortal::onRequestInfo(this, inPacket);
  if ( nProcId == 810 )
    return CExtCharPortal::onUsePortal(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharPortal::onRequestInfo(CExtCharPortal *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CExtCharPortal::SendPortalInfo(this, &this->m_lstPortal);
  return 0;
}


#####################################
int32_t __cdecl CExtCharPortal::onUsePortal(CExtCharPortal *const this, Answer::NetPacket *inPacket)
{
  PortalInfo *v3; // rax
  ProcId_t Proc; // r12
  PortalInfo *v5; // rax
  std::_List_iterator<PortalInfo> iter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<PortalInfo> __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t nId; // [rsp+38h] [rbp-18h]
  int32_t nErr; // [rsp+3Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  for ( iter._M_node = std::list<PortalInfo>::begin(&this->m_lstPortal)._M_node;
        ;
        std::_List_iterator<PortalInfo>::operator++(&iter) )
  {
    __x._M_node = std::list<PortalInfo>::end(&this->m_lstPortal)._M_node;
    if ( !std::_List_iterator<PortalInfo>::operator!=(&iter, &__x) )
      return 10002;
    v3 = std::_List_iterator<PortalInfo>::operator->(&iter);
    if ( v3->nId == nId )
      break;
  }
  if ( std::_List_iterator<PortalInfo>::operator->(&iter)->bClose )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  v5 = std::_List_iterator<PortalInfo>::operator->(&iter);
  nErr = Player::enterDungeon(this->m_pPlayer, v5->nDungeon, Proc, 0, 0, 0, 0, 0);
  if ( nErr )
    return nErr;
  std::_List_iterator<PortalInfo>::operator->(&iter)->bClose = 1;
  CExtCharPortal::SendPortalClose(this, nId);
  return 0;
}


#####################################
void __cdecl CExtCharPortal::AddPortal(
        CExtCharPortal *const this,
        int32_t nMapId,
        int32_t nPosX,
        int32_t nPosY,
        int32_t nDungeon,
        int32_t nStartTime,
        int32_t nDuration)
{
  PortalInfo info; // [rsp+20h] [rbp-20h] BYREF

  *(_DWORD *)&info.bClose = 0;
  info.nId = CExtCharPortal::getPortalId(this);
  info.nMapId = nMapId;
  info.nPosX = nPosX;
  info.nPosY = nPosY;
  info.nDungeon = nDungeon;
  info.nStartTime = nStartTime;
  info.nDuration = nDuration;
  std::list<PortalInfo>::push_back(&this->m_lstPortal, &info);
  CExtCharPortal::SendPortalInfo(this, &info);
  CExtCharPortal::BroadcastPortal(this);
}


#####################################
void __cdecl CExtCharPortal::SendPortalInfo(CExtCharPortal *const this, const PortalInfo *const info)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F53u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      Answer::NetPacket::writeInt32(packet, info->nId);
      Answer::NetPacket::writeInt32(packet, info->nMapId);
      Answer::NetPacket::writeInt32(packet, info->nPosX);
      Answer::NetPacket::writeInt32(packet, info->nPosY);
      Answer::NetPacket::writeInt32(packet, info->nDungeon);
      Answer::NetPacket::writeInt32(packet, info->nStartTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CExtCharPortal::SendPortalInfo(CExtCharPortal *const this, const PortalInfoList *const lst)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  const PortalInfo *v4; // rax
  const PortalInfo *v5; // rax
  const PortalInfo *v6; // rax
  const PortalInfo *v7; // rax
  const PortalInfo *v8; // rax
  const PortalInfo *v9; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  std::_List_const_iterator<PortalInfo> iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_const_iterator<PortalInfo> __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]
  int32_t nCount; // [rsp+34h] [rbp-1Ch]
  uint32_t nOldOffset; // [rsp+38h] [rbp-18h]
  uint32_t nNewOffset; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F53u);
    if ( packet )
    {
      nCount = 0;
      nOldOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      for ( iter._M_node = std::list<PortalInfo>::begin(lst)._M_node;
            ;
            std::_List_const_iterator<PortalInfo>::operator++(&iter) )
      {
        __x._M_node = std::list<PortalInfo>::end(lst)._M_node;
        if ( !std::_List_const_iterator<PortalInfo>::operator!=(&iter, &__x) )
          break;
        if ( !std::_List_const_iterator<PortalInfo>::operator->(&iter)->bClose )
        {
          v4 = std::_List_const_iterator<PortalInfo>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v4->nId);
          v5 = std::_List_const_iterator<PortalInfo>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v5->nMapId);
          v6 = std::_List_const_iterator<PortalInfo>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v6->nPosX);
          v7 = std::_List_const_iterator<PortalInfo>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v7->nPosY);
          v8 = std::_List_const_iterator<PortalInfo>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v8->nDungeon);
          v9 = std::_List_const_iterator<PortalInfo>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v9->nStartTime);
          ++nCount;
        }
      }
      if ( nCount > 0 )
      {
        nNewOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, nOldOffset);
        Answer::NetPacket::writeInt32(packet, nCount);
        Answer::NetPacket::setWOffset(packet, nNewOffset);
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
void __cdecl CExtCharPortal::SendPortalClose(CExtCharPortal *const this, int32_t nId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F54u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharPortal::getPortalId(CExtCharPortal *const this)
{
  if ( ++this->m_nPortalId > 9999 )
    this->m_nPortalId = 1;
  return this->m_nPortalId;
}


#####################################
void __cdecl CExtCharPortal::checkPortalTime(CExtCharPortal *const this, bool bInit)
{
  int32_t nStartTime; // ebx
  PortalInfo *v3; // rax
  int32_t nId; // edx
  std::_List_iterator<PortalInfo> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<PortalInfo> __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nNowTime; // [rsp+2Ch] [rbp-14h]

  nNowTime = Unit::getNow(this->m_pPlayer);
  for ( iter._M_node = std::list<PortalInfo>::begin(&this->m_lstPortal)._M_node;
        ;
        std::_List_iterator<PortalInfo>::operator++(&iter) )
  {
    __x._M_node = std::list<PortalInfo>::end(&this->m_lstPortal)._M_node;
    if ( !std::_List_iterator<PortalInfo>::operator!=(&iter, &__x) )
      break;
    if ( !std::_List_iterator<PortalInfo>::operator->(&iter)->bClose )
    {
      nStartTime = std::_List_iterator<PortalInfo>::operator->(&iter)->nStartTime;
      v3 = std::_List_iterator<PortalInfo>::operator->(&iter);
      if ( nStartTime + v3->nDuration <= nNowTime )
      {
        std::_List_iterator<PortalInfo>::operator->(&iter)->bClose = 1;
        if ( !bInit )
        {
          nId = std::_List_iterator<PortalInfo>::operator->(&iter)->nId;
          CExtCharPortal::SendPortalClose(this, nId);
        }
      }
    }
  }
}


#####################################
void __cdecl CExtCharPortal::BroadcastPortal(CExtCharPortal *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v5; // bl
  GameService *v6; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 538);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v6, v5, packet);
    }
  }
}


