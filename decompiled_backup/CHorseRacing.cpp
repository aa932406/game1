// Decompiled methods for class: CHorseRacing
// Source: gameserver.cc
// Total methods: 16

#####################################
void __cdecl CHorseRacing::~CHorseRacing(CHorseRacing *const this)
{
  CHorseRacing::~CHorseRacing(this);
  operator delete(this);
}


#####################################
void __cdecl CHorseRacing::reset(CHorseRacing *const this)
{
  CActivity::reset(this);
  std::list<PlayerRank>::clear(&this->m_rankList);
  std::list<Player *>::clear(&this->m_racing);
  std::list<Player *>::clear(&this->m_winner);
  this->m_nIndex = 0;
  this->m_BossDie = 0;
}


#####################################
void __cdecl CHorseRacing::OnUpdate(CHorseRacing *const this, CActivityMap *pMap)
{
  std::_List_iterator<Player*> v2; // rax
  int32_t MapId; // ebx
  std::_List_iterator<Player*> v4; // rax
  Player *player; // [rsp+18h] [rbp-58h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+30h] [rbp-40h] BYREF
  Position pos; // [rsp+40h] [rbp-30h] BYREF
  Position CurrentTile; // [rsp+50h] [rbp-20h] BYREF

  CActivity::OnUpdate(this, pMap);
  if ( pMap && Map::GetMapId(pMap) == 10003 )
  {
    iter._M_node = std::list<Player *>::begin(&this->m_racing)._M_node;
    while ( 1 )
    {
      __x._M_node = std::list<Player *>::end(&this->m_racing)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&iter, &__x) )
        break;
      player = *std::_List_iterator<Player *>::operator*(&iter);
      if ( player )
      {
        MapId = StaticObj::getMapId(player);
        if ( MapId == Map::GetMapId(pMap)
          && (Position::Position(&pos, 20, 57),
              CurrentTile = StaticObj::getCurrentTile(player),
              Position::tileDistance(&CurrentTile, &pos) <= 6) )
        {
          v4._M_node = std::_List_iterator<Player *>::operator++(&iter, 0)._M_node;
          std::list<Player *>::erase(&this->m_racing, v4);
          std::list<Player *>::push_back(&this->m_winner, &player);
          CHorseRacing::win(this, player);
        }
        else
        {
          std::_List_iterator<Player *>::operator++(&iter);
        }
      }
      else
      {
        v2._M_node = std::_List_iterator<Player *>::operator++(&iter, 0)._M_node;
        std::list<Player *>::erase(&this->m_racing, v2);
      }
    }
  }
}


#####################################
void __cdecl CHorseRacing::removePlayer(CHorseRacing *const this, Player *player, bool islogout)
{
  std::_List_iterator<Player*> iter_0; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+40h] [rbp-20h] BYREF
  std::_List_iterator<Player*> v6; // [rsp+50h] [rbp-10h] BYREF

  CActivity::removePlayer(this, player, islogout);
  for ( iter._M_node = std::list<Player *>::begin(&this->m_racing)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&iter) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_racing)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&iter, &__x) )
      break;
    if ( *std::_List_iterator<Player *>::operator*(&iter) == player )
    {
      std::list<Player *>::erase(&this->m_racing, iter);
      break;
    }
  }
  for ( iter_0._M_node = std::list<Player *>::begin(&this->m_winner)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&iter_0) )
  {
    v6._M_node = std::list<Player *>::end(&this->m_winner)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&iter_0, &v6) )
      break;
    if ( *std::_List_iterator<Player *>::operator*(&iter_0) == player )
    {
      std::list<Player *>::erase(&this->m_winner, iter_0);
      break;
    }
  }
  Unit::removeBuff(player, 136);
}


#####################################
void __cdecl CHorseRacing::addPlayer(CHorseRacing *const this, Player *player)
{
  Player *playera; // [rsp+0h] [rbp-20h] BYREF
  CHorseRacing *thisa; // [rsp+8h] [rbp-18h]

  thisa = this;
  playera = player;
  CActivity::addPlayer(this, player);
  std::list<Player *>::push_back(&this->m_racing, &playera);
  if ( playera && StaticObj::getMapId(playera) != 90017 )
    CActivity::addActivityBuff(thisa, playera, 136, 0);
}


#####################################
int32_t __cdecl CHorseRacing::canEnter(CHorseRacing *const this, Player *player, CActivityMap *pTargetMap)
{
  CharId_t Cid; // rdx
  CharId_t v5; // rdx

  if ( !player || !pTargetMap )
    return 10002;
  if ( Map::GetMapId(pTargetMap) == 90017 )
  {
    Cid = Player::getCid(player);
    if ( !CHorseRacing::bArrived(this, Cid) )
      return 10002;
  }
  else
  {
    v5 = Player::getCid(player);
    if ( CHorseRacing::bArrived(this, v5) )
    {
      Player::TiShiInfo(player, 4, 0);
      return 10002;
    }
  }
  return CActivity::canEnter(this, player, pTargetMap);
}


#####################################
bool __cdecl CHorseRacing::bArrived(const CHorseRacing *const this, CharId_t cid)
{
  std::_List_const_iterator<PlayerRank> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<PlayerRank> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<PlayerRank>::begin(&this->m_rankList)._M_node;
  eiter._M_node = std::list<PlayerRank>::end(&this->m_rankList)._M_node;
  while ( std::_List_const_iterator<PlayerRank>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_const_iterator<PlayerRank>::operator->(&iter)->nCharId == cid )
      return 1;
    std::_List_const_iterator<PlayerRank>::operator++(&iter);
  }
  return 0;
}


#####################################
void __cdecl CHorseRacing::win(CHorseRacing *const this, Player *player)
{
  int8_t ConnId; // bl
  DBService *v3; // rax
  LogActivity logActivity; // [rsp+10h] [rbp-50h] BYREF
  PlayerRank Rank; // [rsp+30h] [rbp-30h] BYREF
  _BYTE v6[32]; // [rsp+40h] [rbp-20h] BYREF

  if ( player )
  {
    ++this->m_nIndex;
    CHorseRacing::addReward(this, player);
    (*((void (__fastcall **)(CHorseRacing *const, Player *))this->_vptr_CActivity + 59))(this, player);
    CHorseRacing::broadcastWin(this, player);
    Rank.strName._M_dataplus._M_p = 0;
    std::string::string(&Rank.strName);
    Rank.nCharId = Player::getCid(player);
    Player::getName((const Player *const)v6);
    std::string::operator=(&Rank.strName, v6);
    std::string::~string(v6);
    std::list<PlayerRank>::push_back(&this->m_rankList, &Rank);
    if ( this->m_nIndex <= 3 )
      CActivity::setNeedBroadcastActivityScore(this);
    *(&logActivity.time + 1) = 0;
    logActivity.param = 0;
    logActivity.cid = Player::getCid(player);
    logActivity.actid = 0;
    logActivity.acttype = CActivity::GetType(this);
    logActivity.time = Unit::getNow(player);
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<DBService>::instance();
    DBService::InsertActivityLog(v3, ConnId, &logActivity);
    PlayerRank::~PlayerRank(&Rank);
  }
}


#####################################
void __cdecl CHorseRacing::addReward(CHorseRacing *const this, Player *player)
{
  int32_t m_nIndex; // ebx
  CfgData *v3; // rax
  const CfgHorseRacingRewardTable *HorseRacingRewardTable; // rax
  MemChrBagVector *p_Items; // r13
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v8; // rax
  std::string Param; // [rsp+20h] [rbp-40h] BYREF
  char v10; // [rsp+2Fh] [rbp-31h] BYREF
  const CfgHorseRacingReward *pReward; // [rsp+30h] [rbp-30h]
  int32_t nMailIndex; // [rsp+3Ch] [rbp-24h]

  m_nIndex = this->m_nIndex;
  v3 = Answer::Singleton<CfgData>::instance();
  HorseRacingRewardTable = CfgData::GetHorseRacingRewardTable(v3);
  pReward = CfgHorseRacingRewardTable::GetReward(HorseRacingRewardTable, m_nIndex);
  if ( pReward && player )
  {
    if ( pReward->nExp > 0 )
      Player::addExp(player, pReward->nExp, 0, 1);
    if ( pReward->nMoney > 0 )
      Player::AddCurrency(
        player,
        CURRENCY_TYPE::CURRENCY_MONEY,
        pReward->nMoney,
        CURRENCY_CHANGE_REASON::MCR_HORSE_RACING_REWARD,
        0);
    if ( std::vector<MemChrBag>::size(&pReward->Items) )
    {
      nMailIndex = 0;
      switch ( this->m_nIndex )
      {
        case 1:
          nMailIndex = 6212;
          break;
        case 2:
          nMailIndex = 6213;
          break;
        case 3:
          nMailIndex = 6214;
          break;
        case 4:
          nMailIndex = 6240;
          break;
        case 5:
          nMailIndex = 6241;
          break;
        case 6:
          nMailIndex = 6242;
          break;
        case 7:
          nMailIndex = 6243;
          break;
        case 8:
          nMailIndex = 6244;
          break;
        case 9:
          nMailIndex = 6245;
          break;
        case 0xA:
          nMailIndex = 6246;
          break;
        default:
          nMailIndex = 6247;
          break;
      }
      std::allocator<char>::allocator(&v10);
      std::string::string(&Param, &unk_8E0B2F);
      p_Items = &pReward->Items;
      Cid = Player::getCid(player);
      ConnId = Player::getConnId(player);
      v8 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(
        v8,
        ConnId,
        Cid,
        nMailIndex,
        p_Items,
        ITEM_CHANGE_REASON::ICR_HORCE_RACINT_REWARD,
        &Param,
        0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v10);
    }
  }
}


#####################################
void __cdecl CHorseRacing::sendActivityResult(CHorseRacing *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E27u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      Answer::NetPacket::writeInt32(packet, this->m_nIndex);
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
void __cdecl CHorseRacing::onTimeEnd(CHorseRacing *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  CActivity::delayKickAll(this, 0);
}


#####################################
bool __cdecl CHorseRacing::CanUsePet(const CHorseRacing *const this, MapId_t mid)
{
  return mid == 90017;
}


#####################################
void __cdecl CHorseRacing::onMonsterDie(CHorseRacing *const this, MonsterActivity *pMonster, Player *pKiller)
{
  if ( pMonster )
  {
    if ( Monster::getMid(pMonster) == 476078 )
    {
      this->m_BossDie = 1;
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
void __cdecl CHorseRacing::broadcastReady(CHorseRacing *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 19);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CHorseRacing::broadcastStart(CHorseRacing *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 20);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CHorseRacing::broadcastWin(CHorseRacing *const this, Player *player)
{
  GameService *v2; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  int32_t nBroadCastId; // [rsp+24h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    nBroadCastId = 0;
    switch ( this->m_nIndex )
    {
      case 1:
        nBroadCastId = 13;
        break;
      case 2:
        nBroadCastId = 14;
        break;
      case 3:
        nBroadCastId = 15;
        break;
    }
    if ( nBroadCastId > 0 )
    {
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, nBroadCastId);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Cid = Player::getCid(player);
        Answer::NetPacket::writeInt64(packet, Cid);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v5 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v5, 0, packet);
      }
    }
  }
}


