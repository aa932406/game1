// Decompiled methods for class: CXinMaiMap
// Source: gameserver.cc
// Total methods: 17

#####################################
void __cdecl CXinMaiMap::~CXinMaiMap(CXinMaiMap *const this)
{
  CXinMaiMap::~CXinMaiMap(this);
  operator delete(this);
}


#####################################
void __cdecl CXinMaiMap::OnUpdate(CXinMaiMap *const this, CActivityMap *pMap)
{
  CActivity::OnUpdate(this, pMap);
}


#####################################
void __cdecl CXinMaiMap::onPlayerKilled(CXinMaiMap *const this, Player *pDier, Player *pKiller)
{
  ;
}


#####################################
bool __cdecl CXinMaiMap::OnSitRevive(CXinMaiMap *const this, Player *player)
{
  int *v3; // rax
  __int64 __k; // [rsp+18h] [rbp-18h] BYREF
  __int64 Cid; // [rsp+20h] [rbp-10h] BYREF
  int32_t Time; // [rsp+2Ch] [rbp-4h]

  if ( !player )
    return 0;
  __k = Player::getCid(player);
  Time = *std::map<long,int>::operator[](&this->m_ReviveTimes, &__k);
  if ( Time < 0 )
    return 0;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          100 * (Time + 1),
          CURRENCY_CHANGE_REASON::GCR_XIN_MAI_MAP_REVIVE,
          0) )
    return 0;
  Cid = Player::getCid(player);
  v3 = std::map<long,int>::operator[](&this->m_ReviveTimes, &Cid);
  ++*v3;
  (*((void (__fastcall **)(CXinMaiMap *const, Player *))this->_vptr_CActivity + 51))(this, player);
  return 1;
}


#####################################
int32_t __cdecl CXinMaiMap::canEnter(CXinMaiMap *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( player && pTargetMap )
    return CActivity::canEnter(this, player, pTargetMap);
  else
    return 10002;
}


#####################################
void __cdecl CXinMaiMap::reset(CXinMaiMap *const this)
{
  std::map<long,MonsterActivity *>::clear(&this->m_MonsterActivityMap);
  this->m_pLastBoss = 0;
  this->m_LeftTime = 0;
  std::map<long,int>::clear(&this->m_ReviveTimes);
  CActivity::reset(this);
}


#####################################
void __cdecl CXinMaiMap::addPlayer(CXinMaiMap *const this, Player *player)
{
  if ( player )
  {
    if ( Player::getFamilyId(player) <= 0 )
      Player::setPkMode(player, 6, 0);
    else
      Player::setPkMode(player, 3, 0);
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CXinMaiMap::removePlayer(CXinMaiMap *const this, Player *player, bool islogout)
{
  CActivity::removePlayer(this, player, islogout);
}


#####################################
void __cdecl CXinMaiMap::sendPlayerScore(CXinMaiMap *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_Rb_tree_iterator<std::pair<const long int,int> > iter; // [rsp+10h] [rbp-40h] BYREF
  __int64 __x; // [rsp+18h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > v10; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    Count = 0;
    __x = Player::getCid(player);
    iter._M_node = std::map<long,int>::find(&this->m_ReviveTimes, &__x)._M_node;
    v10._M_node = std::map<long,int>::end(&this->m_ReviveTimes)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&iter, &v10) )
      Count = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&iter)->second;
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E24u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      Answer::NetPacket::writeInt32(packet, Count);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v6 = Player::getConnId(player);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CXinMaiMap::onTimeEnd(CXinMaiMap *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_END;
  (*((void (__fastcall **)(CXinMaiMap *const))this->_vptr_CActivity + 43))(this);
  CActivity::delayKickAll(this, 0);
}


#####################################
void __cdecl CXinMaiMap::broadcastReady(CXinMaiMap *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 491);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
  }
}


#####################################
void __cdecl CXinMaiMap::broadcastStart(CXinMaiMap *const this)
{
  GameService *v1; // rax
  int32_t Id; // edx
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 492);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, packet);
  }
}


#####################################
void __cdecl CXinMaiMap::onMonsterAdd(CXinMaiMap *const this, MonsterActivity *pMonster)
{
  __int64 __k; // [rsp+18h] [rbp-8h] BYREF

  if ( pMonster && (*((unsigned __int8 (__fastcall **)(MonsterActivity *))pMonster->_vptr_Entity + 17))(pMonster) == 1 )
  {
    if ( Monster::getBossSign(pMonster) == 14 )
    {
      this->m_pLastBoss = pMonster;
      this->m_LeftTime = 0;
      CActivity::setNeedBroadcastActivityScore(this);
    }
    else
    {
      __k = (*((__int64 (__fastcall **)(MonsterActivity *))pMonster->_vptr_Entity + 2))(pMonster);
      *std::map<long,MonsterActivity *>::operator[](&this->m_MonsterActivityMap, &__k) = pMonster;
    }
  }
}


#####################################
int32_t __cdecl CXinMaiMap::onBeginGather(CXinMaiMap *const this, PlantActivity *plant, Player *player)
{
  if ( !plant || !player )
    return 10002;
  if ( Player::getRecord(player, 2101) <= 10 )
    return 0;
  return 10002;
}


#####################################
void __cdecl CXinMaiMap::onPlantGather(CXinMaiMap *const this, PlantActivity *pPlant, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( pPlant )
  {
    if ( player )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 2101, 1);
    }
  }
}


#####################################
bool __cdecl CXinMaiMap::alwaysShowIcon(CXinMaiMap *const this)
{
  CfgData *v1; // rax
  int32_t ServerDiffDay; // eax

  v1 = Answer::Singleton<CfgData>::instance();
  ServerDiffDay = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
  return GetDayBattle(ServerDiffDay + 1) > 0;
}


#####################################
void __cdecl CXinMaiMap::onMonsterDie(CXinMaiMap *const this, MonsterActivity *pMonster, Player *pKiller)
{
  std::_Rb_tree_iterator<std::pair<const long int,MonsterActivity*> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,MonsterActivity*> > __x; // [rsp+30h] [rbp-20h] BYREF
  bool IsAllDie; // [rsp+47h] [rbp-9h]
  MonsterActivity *pActivityMonster; // [rsp+48h] [rbp-8h]

  if ( pMonster && pKiller )
  {
    if ( (*((unsigned __int8 (__fastcall **)(MonsterActivity *))pMonster->_vptr_Entity + 17))(pMonster)
      && Monster::getBossSign(pMonster) != 14 )
    {
      IsAllDie = 1;
      for ( it._M_node = std::map<long,MonsterActivity *>::begin(&this->m_MonsterActivityMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<long const,MonsterActivity *>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<long,MonsterActivity *>::end(&this->m_MonsterActivityMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<long const,MonsterActivity *>>::operator!=(&it, &__x) )
          break;
        pActivityMonster = std::_Rb_tree_iterator<std::pair<long const,MonsterActivity *>>::operator->(&it)->second;
        if ( pActivityMonster && Unit::isAlive(pActivityMonster) )
        {
          IsAllDie = 0;
          break;
        }
      }
      if ( IsAllDie )
        this->m_LeftTime = Unit::getNow(pKiller) + 180;
    }
    CActivity::setNeedBroadcastActivityScore(this);
  }
}


