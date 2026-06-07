// Decompiled methods for class: CFamilyLight
// Source: gameserver.cc
// Total methods: 14

#####################################
void __cdecl CFamilyLight::~CFamilyLight(CFamilyLight *const this)
{
  CFamilyLight::~CFamilyLight(this);
  operator delete(this);
}


#####################################
void __cdecl CFamilyLight::OnUpdate(CFamilyLight *const this, CActivityMap *pMap)
{
  std::pair<const long int,CFamilyLight::PlayerScore> *v2; // rax
  int32_t RunnerId; // r12d
  CharId_t nCharId; // rbx
  GameService *v5; // rax
  int32_t MapId; // ebx
  int32_t y; // r12d
  int32_t x; // ebx
  CfgData *v9; // rax
  const CfgFamilyLightExpTable *FamilyLightExpTable; // rax
  std::set<int> PosIdSet; // [rsp+20h] [rbp-B0h] BYREF
  std::_Rb_tree_const_iterator<int> it; // [rsp+50h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > iter; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > v15; // [rsp+70h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<int> __x; // [rsp+80h] [rbp-50h] BYREF
  std::pair<std::_Rb_tree_const_iterator<int>,bool> v17; // [rsp+90h] [rbp-40h]
  int64_t curTick; // [rsp+A0h] [rbp-30h]
  CFamilyLight::PlayerScore *score; // [rsp+A8h] [rbp-28h]
  Player *player; // [rsp+B0h] [rbp-20h]
  const PassionBubbleCfg *pCfg; // [rsp+B8h] [rbp-18h]

  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    curTick = Map::getTick(pMap);
    if ( curTick - this->m_LastUpdateTick > 10000 )
    {
      this->m_LastUpdateTick = curTick;
      std::set<int>::set(&PosIdSet);
      for ( iter._M_node = std::map<long,CFamilyLight::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator++(&iter) )
      {
        v15._M_node = std::map<long,CFamilyLight::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator!=(&iter, &v15) )
        {
          std::set<int>::~set(&PosIdSet);
          return;
        }
        v2 = std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&iter);
        score = &v2->second;
        if ( v2->second.bInActivity )
        {
          RunnerId = Map::GetRunnerId(pMap);
          nCharId = score->nCharId;
          v5 = Answer::Singleton<GameService>::instance();
          player = GameService::getPlayer(v5, nCharId, RunnerId, 1);
          if ( player )
          {
            MapId = StaticObj::getMapId(player);
            if ( MapId == Map::GetMapId(pMap) )
            {
              y = StaticObj::getCurrentTile(player).y;
              x = StaticObj::getCurrentTile(player).x;
              v9 = Answer::Singleton<CfgData>::instance();
              FamilyLightExpTable = CfgData::GetFamilyLightExpTable(v9);
              pCfg = CfgFamilyLightExpTable::GetPassionBubbleCfg(FamilyLightExpTable, x, y);
              if ( pCfg && Unit::isAlive(player) )
              {
                if ( pCfg->nId > 0 )
                {
                  it._M_node = std::set<int>::find(&PosIdSet, &pCfg->nId)._M_node;
                  __x._M_node = std::set<int>::end(&PosIdSet)._M_node;
                  if ( std::_Rb_tree_const_iterator<int>::operator!=(&it, &__x) )
                  {
                    Player::TiShiInfo(player, 23, 0);
                    continue;
                  }
                  v17 = std::set<int>::insert(&PosIdSet, &pCfg->nId);
                }
                Player::AddCurrency(
                  player,
                  CURRENCY_TYPE::CURRENCY_BIND_MONEY,
                  pCfg->Money,
                  CURRENCY_CHANGE_REASON::GCR_FAMILY_LIGHT,
                  0);
                Player::AddCurrency(
                  player,
                  CURRENCY_TYPE::CURRENCY_BLOOD,
                  pCfg->Score,
                  CURRENCY_CHANGE_REASON::GCR_FAMILY_LIGHT,
                  0);
                score->nScore += pCfg->Score;
                score->nMoney += pCfg->Money;
                CFamilyLight::AddScore(this, player, pCfg->Money, pCfg->Score);
              }
              (*((void (__fastcall **)(CFamilyLight *const, Player *))this->_vptr_CActivity + 51))(this, player);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CFamilyLight::onPlayerKilled(CFamilyLight *const this, Player *pDier, Player *pKiller)
{
  std::pair<const long int,CFamilyLight::PlayerScore> *v3; // rax
  unsigned int nKillCount; // eax
  int8_t ConnId; // bl
  GameService *v6; // rax
  CharId_t Cid; // rax
  std::pair<const long int,CFamilyLight::PlayerScore> *v8; // rax
  uint32_t WOffset; // eax
  int8_t v10; // bl
  GameService *v11; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > it; // [rsp+20h] [rbp-40h] BYREF
  __int64 __x; // [rsp+28h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > v15; // [rsp+30h] [rbp-30h] BYREF
  std::string val; // [rsp+40h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( pDier )
  {
    if ( pKiller )
    {
      __x = Player::getCid(pKiller);
      it._M_node = std::map<long,CFamilyLight::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
      v15._M_node = std::map<long,CFamilyLight::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator!=(&it, &v15) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&it);
        ++v3->second.nKillCount;
        nKillCount = std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&it)->second.nKillCount;
        if ( nKillCount <= 0x32 && ((1LL << nKillCount) & 0x4000040008020LL) != 0 )
        {
          ConnId = Player::getConnId(pKiller);
          v6 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( packet )
          {
            Answer::NetPacket::writeInt32(packet, 464);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Cid = Player::getCid(pKiller);
            Answer::NetPacket::writeInt64(packet, Cid);
            v8 = std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&it);
            Answer::NetPacket::writeInt32(packet, v8->second.nKillCount);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v10 = Player::getConnId(pKiller);
            v11 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v11, v10, packet);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CFamilyLight::AddScore(CFamilyLight *const this, Player *pPlayer, int32_t Money, int32_t Score)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E2Fu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, Money);
      Answer::NetPacket::writeInt32(packet, Score);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v8 = Player::getConnId(pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CFamilyLight::OnSitRevive(CFamilyLight *const this, Player *player)
{
  return player != 0;
}


#####################################
void __cdecl CFamilyLight::reset(CFamilyLight *const this)
{
  CActivity::reset(this);
  std::map<long,CFamilyLight::PlayerScore>::clear(&this->m_mPlayerScore);
  this->m_LastUpdateTick = 0;
}


#####################################
void __cdecl CFamilyLight::addPlayer(CFamilyLight *const this, Player *player)
{
  CFamilyLight::PlayerScore score; // [rsp+20h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > iter; // [rsp+40h] [rbp-60h] BYREF
  __int64 __x; // [rsp+48h] [rbp-58h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > v5; // [rsp+50h] [rbp-50h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> >,bool> v6; // [rsp+60h] [rbp-40h]
  std::pair<const long int,CFamilyLight::PlayerScore> v7; // [rsp+70h] [rbp-30h] BYREF

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CFamilyLight::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v5._M_node = std::map<long,CFamilyLight::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator!=(&iter, &v5) )
    {
      std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&iter)->second.bInActivity = 1;
    }
    else
    {
      *(_QWORD *)&score.nScore = 0;
      *(_QWORD *)&score.nArea = 0x100000000LL;
      *(_QWORD *)&score.nKillCount = 0;
      score.nCharId = Player::getCid(player);
      std::pair<long const,CFamilyLight::PlayerScore>::pair(&v7, &score.nCharId, &score);
      v6 = std::map<long,CFamilyLight::PlayerScore>::insert(&this->m_mPlayerScore, &v7);
    }
    if ( Player::getFamilyId(player) <= 0 )
      Player::setPkMode(player, 6, 0);
    else
      Player::setPkMode(player, 3, 0);
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CFamilyLight::removePlayer(CFamilyLight *const this, Player *player, bool islogout)
{
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > iter; // [rsp+20h] [rbp-20h] BYREF
  __int64 __x; // [rsp+28h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > v5; // [rsp+30h] [rbp-10h] BYREF

  CActivity::removePlayer(this, player, islogout);
  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CFamilyLight::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v5._M_node = std::map<long,CFamilyLight::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator!=(&iter, &v5) )
      std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&iter)->second.bInActivity = 0;
  }
}


#####################################
void __cdecl CFamilyLight::sendPlayerScore(CFamilyLight *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int m_LastUpdateTick; // ebx
  int Tick; // eax
  int32_t LeftTime; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  __int64 __x; // [rsp+18h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > v12; // [rsp+20h] [rbp-30h] BYREF
  CFamilyLight::PlayerScore *score; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CFamilyLight::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v12._M_node = std::map<long,CFamilyLight::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator==(&iter, &v12) )
    {
      score = &std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&iter)->second;
      ConnId = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E26u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt32(packet, score->nScore);
        Answer::NetPacket::writeInt32(packet, score->nMoney);
        m_LastUpdateTick = this->m_LastUpdateTick;
        Tick = Unit::getTick(player);
        Answer::NetPacket::writeInt32(packet, m_LastUpdateTick - Tick + 10000);
        LeftTime = CActivity::getLeftTime(this);
        Answer::NetPacket::writeInt32(packet, LeftTime);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(player);
        LOBYTE(m_LastUpdateTick) = Player::getConnId(player);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, m_LastUpdateTick, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CFamilyLight::broadcastActivityResult(CFamilyLight *const this)
{
  std::pair<const long int,CFamilyLight::PlayerScore> *v1; // rax
  CharId_t nCharId; // rbx
  GameService *v3; // rax
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CFamilyLight::PlayerScore> > __x; // [rsp+20h] [rbp-30h] BYREF
  CFamilyLight::PlayerScore *score; // [rsp+28h] [rbp-28h]
  Player *player; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  for ( iter._M_node = std::map<long,CFamilyLight::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<long,CFamilyLight::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator!=(&iter, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<long const,CFamilyLight::PlayerScore>>::operator->(&iter);
    score = &v1->second;
    if ( v1->second.bInActivity )
    {
      nCharId = score->nCharId;
      v3 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v3, nCharId, 0, 0);
      if ( player )
      {
        ConnId = Player::getConnId(player);
        v5 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E27u);
        if ( !packet )
          return;
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt32(packet, score->nScore);
        Answer::NetPacket::writeInt32(packet, score->nMoney);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(player);
        v8 = Player::getConnId(player);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, v8, GateIndex, packet);
      }
    }
  }
}


#####################################
bool __cdecl CFamilyLight::DrinkWine(CFamilyLight *const this, Player *player, int32_t Count)
{
  if ( !player )
    return 0;
  (*((void (__fastcall **)(CFamilyLight *const, Player *))this->_vptr_CActivity + 51))(this, player);
  return 1;
}


#####################################
void __cdecl CFamilyLight::onTimeEnd(CFamilyLight *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_END;
  (*((void (__fastcall **)(CFamilyLight *const))this->_vptr_CActivity + 43))(this);
  CActivity::delayKickAll(this, 0);
}


#####################################
void __cdecl CFamilyLight::broadcastReady(CFamilyLight *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 128);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CFamilyLight::broadcastStart(CFamilyLight *const this)
{
  GameService *v1; // rax
  int32_t Id; // edx
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 129);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, 0, packet);
  }
}


