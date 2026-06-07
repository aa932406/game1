// Decompiled methods for class: CFaBao
// Source: gameserver.cc
// Total methods: 15

#####################################
void __cdecl CFaBao::~CFaBao(CFaBao *const this)
{
  CFaBao::~CFaBao(this);
  operator delete(this);
}


#####################################
void __cdecl CFaBao::OnCleanUp(CFaBao *const this)
{
  bzero(this->m_FaBao, 0x20u);
}


#####################################
void __cdecl CFaBao::OnLoadFromDB(CFaBao *const this, const PlayerDBData *const dbData)
{
  memcpy(this->m_FaBao, dbData->m_FaBaoData.m_FaBao, sizeof(this->m_FaBao));
}


#####################################
void __cdecl CFaBao::OnSaveToDB(CFaBao *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->m_FaBaoData.m_FaBao, this->m_FaBao, sizeof(dbData->m_FaBaoData.m_FaBao));
}


#####################################
void __cdecl CFaBao::GetInterestsProtocol(CFaBao *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v3; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v4; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v5; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v6; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 447;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 439;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 446;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 440;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 441;
  std::list<unsigned short>::push_back(procList, &v6);
}


#####################################
int32_t __cdecl CFaBao::DispatchNetDatas(CFaBao *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x1B9u:
      return CFaBao::onFaBaoPeiYang(this, inPacket);
    case 0x1BEu:
      return CFaBao::onBuyFaBaoRes(this, inPacket);
    case 0x1B8u:
      return CFaBao::onAskFaBaoInfo(this, inPacket);
  }
  return 2;
}


#####################################
int32_t __cdecl CFaBao::onAskFaBaoInfo(CFaBao *const this, Answer::NetPacket *inPacket)
{
  int8_t Int8; // dl

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Int8 = Answer::NetPacket::readInt8(inPacket);
  CFaBao::sendFaBaoInfo(this, Int8);
  return 0;
}


#####################################
int32_t __cdecl CFaBao::onBuyFaBaoRes(CFaBao *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t id; // [rsp+14h] [rbp-Ch]
  BuyFaBaoResCfg *ResCfg; // [rsp+18h] [rbp-8h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  id = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  ResCfg = CfgData::GetBuyFaBaoResCfg(v3, id);
  if ( !ResCfg )
    return 2;
  if ( !IsFaBaoType(ResCfg->FaBaoResType) )
    return 2;
  if ( ResCfg->GetResValues <= 0 )
    return 2;
  if ( ResCfg->NeedGold <= 0 )
    return 2;
  if ( Player::DecCurrency(
         this->m_pPlayer,
         CURRENCY_TYPE::CURRENCY_GOLD,
         ResCfg->NeedGold,
         CURRENCY_CHANGE_REASON::GCR_BUY_FABAO_RES,
         0) )
  {
    CFaBao::AddFaBaoRes(this, ResCfg->FaBaoResType, ResCfg->GetResValues);
  }
  return 2;
}


#####################################
int32_t __cdecl CFaBao::onFaBaoPeiYang(CFaBao *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t FaBaoLevel; // r12d
  CfgData *v4; // rax
  FaBaoTable *FaBaoTable; // rax
  int32_t v6; // r12d
  CfgData *v7; // rax
  FaBaoTable *v8; // rax
  BenefitType v9; // eax
  Player *m_pPlayer; // rbx
  CKaiFuHuoDong *v11; // rax
  int8_t ConnId; // bl
  DBService *v13; // rax
  important_system_log stu; // [rsp+10h] [rbp-80h] BYREF
  _BYTE v16[16]; // [rsp+50h] [rbp-40h] BYREF
  _BYTE v17[15]; // [rsp+60h] [rbp-30h] BYREF
  int8_t nType; // [rsp+6Fh] [rbp-21h]
  CfgFaBao *pFaBao; // [rsp+70h] [rbp-20h]
  CfgFaBao *pNextFaBao; // [rsp+78h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  if ( !IsFaBaoType(nType) )
    return 2;
  FaBaoLevel = this->m_FaBao[nType].FaBaoLevel;
  v4 = Answer::Singleton<CfgData>::instance();
  FaBaoTable = CfgData::GetFaBaoTable(v4);
  pFaBao = FaBaoTable::GetFaBaoCfg(FaBaoTable, nType, FaBaoLevel);
  if ( !pFaBao )
    return 2;
  if ( pFaBao->NeedCurr < 0 )
    return 2;
  if ( pFaBao->NeedCurr > this->m_FaBao[nType].FaBaoRes )
    return 2;
  v6 = this->m_FaBao[nType].FaBaoLevel + 1;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetFaBaoTable(v7);
  pNextFaBao = FaBaoTable::GetFaBaoCfg(v8, nType, v6);
  if ( !pNextFaBao )
    return 2;
  if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < pFaBao->nNeedLevel )
    return 2;
  this->m_FaBao[nType].FaBaoRes -= pFaBao->NeedCurr;
  v9 = Player::benefitType(this->m_pPlayer);
  Player::sendGainInfo(this->m_pPlayer, nType + 100, -pFaBao->NeedCurr, v9);
  ++this->m_FaBao[nType].FaBaoLevel;
  if ( pNextFaBao->GongGaoId > 0 )
    CFaBao::broadcastLevelUp(this, nType, pNextFaBao->GongGaoId);
  CFaBao::sendFaBaoInfo(this, nType);
  Player::RecalcAttr(this->m_pPlayer);
  if ( nType == 3 )
  {
    m_pPlayer = this->m_pPlayer;
    v11 = Answer::Singleton<CKaiFuHuoDong>::instance();
    CKaiFuHuoDong::SendKaiFuHuoDongIcon(v11, m_pPlayer);
  }
  important_system_log::important_system_log(&stu);
  stu.log_Sid = Player::getSid(this->m_pPlayer);
  stu.log_time = Unit::getNow(this->m_pPlayer);
  Player::GetPassport((Player *const)v16);
  std::string::operator=(&stu.passport, v16);
  std::string::~string(v16);
  stu.cid = Player::getCid(this->m_pPlayer);
  Player::getName((const Player *const)v17);
  std::string::operator=(&stu.name, v17);
  std::string::~string(v17);
  stu.up_time = Unit::getNow(this->m_pPlayer);
  if ( nType )
  {
    switch ( nType )
    {
      case 1:
        stu.sys_name = 5;
        break;
      case 2:
        stu.sys_name = 6;
        break;
      case 3:
        stu.sys_name = 8;
        break;
    }
  }
  else
  {
    stu.sys_name = 4;
  }
  stu.oper_id = 1;
  stu.level = this->m_FaBao[nType].FaBaoLevel;
  ConnId = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<DBService>::instance();
  DBService::AddPlatformLog(v13, ConnId, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
  v2 = 0;
  important_system_log::~important_system_log(&stu);
  return v2;
}


#####################################
void __cdecl CFaBao::broadcastLevelUp(CFaBao *const this, int8_t Type, int32_t GongGaoId)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && IsFaBaoType(Type) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt8(packet, Type);
      Answer::NetPacket::writeInt32(packet, this->m_FaBao[Type].FaBaoLevel);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


#####################################
void __cdecl CFaBao::AddPlayerAttr(CFaBao *const this)
{
  int32_t FaBaoLevel; // r12d
  int8_t v2; // bl
  CfgData *v3; // rax
  FaBaoTable *FaBaoTable; // rax
  int32_t addon; // ebx
  AttrAddon *v6; // rax
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > it; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  int8_t i; // [rsp+37h] [rbp-19h]
  CfgFaBao *pFaBao; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 3; ++i )
    {
      FaBaoLevel = this->m_FaBao[i].FaBaoLevel;
      v2 = i;
      v3 = Answer::Singleton<CfgData>::instance();
      FaBaoTable = CfgData::GetFaBaoTable(v3);
      pFaBao = FaBaoTable::GetFaBaoCfg(FaBaoTable, v2, FaBaoLevel);
      if ( pFaBao )
      {
        for ( it._M_current = std::vector<AttrAddon>::begin(&pFaBao->vAttr)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator++(&it) )
        {
          __rhs._M_current = std::vector<AttrAddon>::end(&pFaBao->vAttr)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon *,std::vector<AttrAddon>>(&it, &__rhs) )
            break;
          addon = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it)->addon;
          v6 = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v6->index, addon);
        }
      }
    }
  }
}


#####################################
void __cdecl CFaBao::sendFaBaoInfo(CFaBao *const this, int8_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && IsFaBaoType(nType) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CB0u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, nType);
      Answer::NetPacket::writeInt32(packet, this->m_FaBao[nType].FaBaoLevel);
      Answer::NetPacket::writeInt32(packet, this->m_FaBao[nType].FaBaoRes);
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
void __cdecl CFaBao::SendAllFaBaoInfo(CFaBao *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CB6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, 4);
      for ( i = 0; i <= 3; ++i )
      {
        Answer::NetPacket::writeInt8(packet, i);
        Answer::NetPacket::writeInt32(packet, this->m_FaBao[i].FaBaoLevel);
        Answer::NetPacket::writeInt32(packet, this->m_FaBao[i].FaBaoRes);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CFaBao::AddFaBaoRes(CFaBao *const this, int8_t nType, int32_t Values)
{
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v4; // rax
  BenefitType v5; // eax

  if ( this->m_pPlayer && IsFaBaoType(nType) && Values > 0 )
  {
    this->m_FaBao[nType].FaBaoRes += Values;
    m_pPlayer = this->m_pPlayer;
    v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    CFestivalDoubleEleven::AddFaBaoValue(v4, m_pPlayer, nType, Values);
    v5 = Player::benefitType(this->m_pPlayer);
    Player::sendGainInfo(this->m_pPlayer, nType + 100, Values, v5);
    CFaBao::sendFaBaoInfo(this, nType);
  }
}


#####################################
int32_t __cdecl CFaBao::GetFaBaoLevel(CFaBao *const this, int8_t Type)
{
  if ( !IsFaBaoType(Type) )
    return 0;
  else
    return this->m_FaBao[Type].FaBaoLevel;
}


