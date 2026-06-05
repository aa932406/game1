// Decompiled methods for class: CExtCharTeamDungeon
// Source: gameserver.cc
// Total methods: 13

#####################################
void __cdecl CExtCharTeamDungeon::~CExtCharTeamDungeon(CExtCharTeamDungeon *const this)
{
  CExtCharTeamDungeon::~CExtCharTeamDungeon(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharTeamDungeon::OnCleanUp(CExtCharTeamDungeon *const this)
{
  this->m_nId = 0;
  this->m_nDungeonId = 0;
  this->m_nLeader = 0;
}


#####################################
void __cdecl CExtCharTeamDungeon::GetInterestsProtocol(CExtCharTeamDungeon *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v3; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v4; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v5; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v6; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v7; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 800;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 801;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 802;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 20069;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 20070;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 20071;
  std::list<unsigned short>::push_back(procList, &v7);
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::DispatchNetDatas(
        CExtCharTeamDungeon *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharTeamDungeon::IsFunctionOpen(this) )
    return 2;
  if ( nProcId == 802 )
    return CExtCharTeamDungeon::onTeamDungeonStart(this, inPacket);
  if ( nProcId > 0x322u )
  {
    switch ( nProcId )
    {
      case 0x4E66u:
        return CExtCharTeamDungeon::onSocialTeamDungeonUpdateInfo(this, inPacket);
      case 0x4E67u:
        return CExtCharTeamDungeon::onSocialTeamDungeonCost(this, inPacket);
      case 0x4E65u:
        return CExtCharTeamDungeon::onSocialTeamDungeonStart(this, inPacket);
    }
  }
  else
  {
    if ( nProcId == 800 )
      return CExtCharTeamDungeon::onTeamDungeonCreate(this, inPacket);
    if ( nProcId == 801 )
      return CExtCharTeamDungeon::onTeamDungeonJoin(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::onTeamDungeonCreate(CExtCharTeamDungeon *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int8_t ConnId; // bl
  GameService *v5; // rax
  int32_t GateIndex; // edx
  GameService *v7; // rax
  int32_t Line; // edx
  uint32_t WOffset; // edx
  int8_t v10; // bl
  GameService *v11; // rax
  int32_t nDungeonId; // [rsp+18h] [rbp-28h]
  int32_t nLimitBattle; // [rsp+1Ch] [rbp-24h]
  const CfgDungeon *pCfgDungeon; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nDungeonId = Answer::NetPacket::readInt32(inPacket);
  nLimitBattle = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v3, nDungeonId);
  if ( !pCfgDungeon )
    return 10002;
  if ( !CExtCharTeamDungeon::checkTeamDungeon(this, pCfgDungeon) )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA8u);
  if ( !packet )
    return 2;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  Answer::NetPacket::writeInt32(packet, nDungeonId);
  Answer::NetPacket::writeInt32(packet, nLimitBattle);
  v7 = Answer::Singleton<GameService>::instance();
  Line = GameService::getLine(v7);
  Answer::NetPacket::writeInt32(packet, Line);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v10 = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v11, v10, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::onTeamDungeonJoin(CExtCharTeamDungeon *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int8_t ConnId; // bl
  GameService *v5; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t nId; // [rsp+18h] [rbp-28h]
  int32_t nDungeonId; // [rsp+1Ch] [rbp-24h]
  const CfgDungeon *pCfgDungeon; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nId = Answer::NetPacket::readInt32(inPacket);
  nDungeonId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v3, nDungeonId);
  if ( !pCfgDungeon )
    return 10002;
  if ( !CExtCharTeamDungeon::checkTeamDungeon(this, pCfgDungeon) )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA9u);
  if ( !packet )
    return 2;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  Answer::NetPacket::writeInt32(packet, nId);
  Answer::NetPacket::writeInt32(packet, nDungeonId);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v8 = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v9, v8, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::onTeamDungeonStart(CExtCharTeamDungeon *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EAAu);
  if ( !packet )
    return 2;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v7 = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v8, v7, packet);
  return 0;
}


#####################################
void __cdecl CExtCharTeamDungeon::LeaveTeamDungeon(CExtCharTeamDungeon *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( CExtCharTeamDungeon::IsInTeamDungeon(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EABu);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v6, v5, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::onSocialTeamDungeonStart(
        CExtCharTeamDungeon *const this,
        Answer::NetPacket *inPacket)
{
  int32_t m_nDungeonId; // ebx
  CfgData *v4; // rax
  int64_t costMoney; // rbx
  CExtCurrency *Currency; // rax
  CExtCharBag *Bag; // rax
  GameService *v8; // rax
  int8_t ConnId; // bl
  GameService *v10; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  CfgDungeon *pCfgDungeon; // [rsp+18h] [rbp-28h]
  int32_t nLine; // [rsp+24h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  m_nDungeonId = this->m_nDungeonId;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v4, m_nDungeonId);
  if ( !pCfgDungeon )
    return 10002;
  if ( pCfgDungeon->costMoney > 0 )
  {
    costMoney = pCfgDungeon->costMoney;
    Currency = Player::GetCurrency(this->m_pPlayer);
    CExtCurrency::DecMoneyAndNoBind(Currency, costMoney, CURRENCY_CHANGE_REASON::MCR_ENTER_DUNGEON, 0);
  }
  if ( pCfgDungeon->costGold > 0 )
    Player::DecCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_GOLD,
      pCfgDungeon->costGold,
      CURRENCY_CHANGE_REASON::GCR_ENTER_DUNGEON,
      this->m_nDungeonId);
  if ( pCfgDungeon->costItem.m_nCount > 0 )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    CExtCharBag::RemoveItem(Bag, &pCfgDungeon->costItem, ITEM_CHANGE_REASON::ICR_ENETR_DUNGEON);
  }
  nLine = Answer::NetPacket::readInt32(inPacket);
  v8 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v8) != nLine )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v10, ConnId, Answer::PackType::PACK_DISPATCH, 0x272Cu);
    if ( !packet )
      return 2;
    Answer::NetPacket::writeInt32(packet, nLine);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v13 = Player::getConnId(this->m_pPlayer);
    v14 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v14, v13, GateIndex, packet);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::onSocialTeamDungeonCost(
        CExtCharTeamDungeon *const this,
        Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  CExtCurrency *Currency; // rax
  int8_t ConnId; // bl
  GameService *v7; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v10; // bl
  GameService *v11; // rax
  int32_t nDungeonId; // [rsp+14h] [rbp-2Ch]
  CfgDungeon *pCfgDungeon; // [rsp+18h] [rbp-28h]
  int8_t nResult; // [rsp+27h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nDungeonId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgDungeon = CfgData::getDungeon(v3, nDungeonId);
  if ( !pCfgDungeon )
    return 10002;
  nResult = 0;
  if ( pCfgDungeon->costItem.m_nCount > 0 )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    nResult = !CExtCharBag::HasItem(Bag, &pCfgDungeon->costItem);
  }
  if ( pCfgDungeon->costMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < pCfgDungeon->costMoney )
      nResult = 2;
  }
  if ( pCfgDungeon->costGold > 0
    && Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < pCfgDungeon->costGold )
  {
    nResult = 3;
  }
  ConnId = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EACu);
  if ( !packet )
    return 10002;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  Answer::NetPacket::writeInt8(packet, nResult);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v10 = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v11, v10, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTeamDungeon::onSocialTeamDungeonUpdateInfo(
        CExtCharTeamDungeon *const this,
        Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 2;
  this->m_nId = Answer::NetPacket::readInt32(inPacket);
  this->m_nDungeonId = Answer::NetPacket::readInt32(inPacket);
  this->m_nLeader = Answer::NetPacket::readInt64(inPacket);
  return 0;
}


#####################################
bool __cdecl CExtCharTeamDungeon::IsTeamDungeonLeader(const CExtCharTeamDungeon *const this)
{
  return this->m_pPlayer && Player::getCid(this->m_pPlayer) == this->m_nLeader;
}


#####################################
bool __cdecl CExtCharTeamDungeon::checkTeamDungeon(
        const CExtCharTeamDungeon *const this,
        const CfgDungeon *const cfgDungeon)
{
  int weekday; // ebx
  Job_t job; // bl
  int32_t v8; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int32_t Record; // ebx
  CharId_t Cid; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  CExtCharBag *Bag; // rax
  CExtCurrency *Currency; // rax
  tm localNow; // [rsp+10h] [rbp-60h] BYREF

  if ( !this->m_pPlayer )
    return 0;
  if ( cfgDungeon->type != 12 )
    return 0;
  if ( CExtCharTeamDungeon::IsInTeamDungeon(this)
    || StaticObj::InDungeon(this->m_pPlayer)
    || StaticObj::InActivity(this->m_pPlayer) )
  {
    return 0;
  }
  Unit::getLocalNow(&localNow, this->m_pPlayer);
  weekday = cfgDungeon->weekday;
  if ( ((weekday >> GetWeekDay(localNow.tm_wday)) & 1) == 0 )
    return 0;
  if ( localNow.tm_hour < cfgDungeon->start_hour || localNow.tm_hour > cfgDungeon->end_hour )
    return 0;
  if ( cfgDungeon->job > 0 )
  {
    job = cfgDungeon->job;
    if ( job != Player::getJob(this->m_pPlayer) )
      return 0;
  }
  if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < cfgDungeon->level
    || (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) > cfgDungeon->maxLevel )
  {
    return 0;
  }
  if ( cfgDungeon->last_id > 0 )
  {
    v8 = cfgDungeon->last_id + 20000;
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    if ( !CExtOperateLimit::CheckIsLimitedForever(OperateLimit, v8) )
      return 0;
  }
  Record = Player::getRecord(this->m_pPlayer, cfgDungeon->group_id);
  if ( Record < Player::GetDungeonDailyEnterLimit(this->m_pPlayer, cfgDungeon->id) )
  {
    if ( cfgDungeon->costItem.m_nCount > 0
      && (Bag = Player::GetBag(this->m_pPlayer), !CExtCharBag::HasItem(Bag, &cfgDungeon->costItem)) )
    {
      return 0;
    }
    else
    {
      if ( cfgDungeon->costMoney <= 0 )
        return cfgDungeon->costGold <= 0
            || Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) >= cfgDungeon->costGold;
      Currency = Player::GetCurrency(this->m_pPlayer);
      return CExtCurrency::GetMoneyBindAndNoBind(Currency) >= cfgDungeon->costMoney
          && (cfgDungeon->costGold <= 0
           || Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) >= cfgDungeon->costGold);
    }
  }
  else
  {
    Cid = Player::getCid(this->m_pPlayer);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v14 = Answer::Singleton<GameService>::instance();
    GameService::replyfailure(v14, ConnId, GateIndex, 0x12u, 10023, Cid);
    return 0;
  }
}


