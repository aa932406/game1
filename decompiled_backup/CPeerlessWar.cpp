// Decompiled methods for class: CPeerlessWar
// Source: gameserver.cc
// Total methods: 34

#####################################
void __cdecl CPeerlessWar::~CPeerlessWar(CPeerlessWar *const this)
{
  CPeerlessWar::~CPeerlessWar(this);
  operator delete(this);
}


#####################################
void __cdecl CPeerlessWar::Init(CPeerlessWar *const this)
{
  Answer::DBPool *v1; // rax
  const char *v2; // rax
  Answer::MySqlQuery *v3; // rax
  const char *StringValue; // rax
  CharId_t m_nWinner; // rbx
  CActivityManager *v6; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-60h] BYREF
  std::string sql_str; // [rsp+60h] [rbp-40h] BYREF
  CharIdList winners; // [rsp+70h] [rbp-30h] BYREF
  _BYTE v11[17]; // [rsp+8Fh] [rbp-11h] BYREF

  CActivity::Init(this);
  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  std::list<long>::list(&winners);
  std::allocator<char>::allocator(v11);
  std::string::string(
    &sql_str,
    "SELECT a.`winner`,b.`name` FROM `mem_peerless_war` a LEFT JOIN `mem_character` b ON a.`winner`=b.`cid` ORDER BY a.`t"
    "ime` DESC LIMIT 1");
  std::allocator<char>::~allocator(v11);
  v2 = (const char *)std::string::c_str(&sql_str);
  v3 = Answer::MySqlDBGuard::query(&db, v2);
  Answer::MySqlQuery::MySqlQuery(&result, v3);
  this->m_nWinner = Answer::MySqlQuery::getInt64Value(&result, "winner", 0);
  StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8E8A9D);
  std::string::operator=(&this->m_strWinnerName, StringValue);
  m_nWinner = this->m_nWinner;
  v6 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SetPeerlessWarWinner(v6, 0, m_nWinner);
  Answer::MySqlQuery::~MySqlQuery(&result);
  std::string::~string(&sql_str);
  std::list<long>::~list(&winners);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CPeerlessWar::OnUpdate(CPeerlessWar *const this, CActivityMap *pMap)
{
  CTimer *v2; // rax
  int64_t curTick; // [rsp+10h] [rbp-10h]
  int32_t nNowTime; // [rsp+1Ch] [rbp-4h]

  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
    {
      curTick = Map::getTick(pMap);
      if ( curTick - this->m_nLastTick > 1000 )
      {
        this->m_nLastTick = curTick;
        v2 = Answer::Singleton<CTimer>::instance();
        nNowTime = CTimer::GetNow(v2);
        if ( this->m_nWarState == 1 && nNowTime - this->m_nStartTime > 300 )
        {
          this->m_nWarState = 2;
          (*((void (__fastcall **)(CPeerlessWar *const))this->_vptr_CActivity + 59))(this);
          CPeerlessWar::checkWin(this);
          CActivity::setNeedBroadcastActivityScore(this);
        }
      }
    }
  }
}


#####################################
void __cdecl CPeerlessWar::reset(CPeerlessWar *const this)
{
  CActivity::reset(this);
  this->m_nLastTick = 0;
  this->m_nWarState = 0;
  std::map<long,CPeerlessWar::PlayerScore>::clear(&this->m_mPlayerScore);
}


#####################################
void __cdecl CPeerlessWar::onPlayerKilled(CPeerlessWar *const this, Player *pDier, Player *pAttacker)
{
  std::pair<const long int,CPeerlessWar::PlayerScore> *v3; // rax
  int32_t nBroadCont; // r14d
  CharId_t Cid; // r13
  CharId_t v6; // r12
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+20h] [rbp-60h] BYREF
  __int64 __x; // [rsp+28h] [rbp-58h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v10; // [rsp+30h] [rbp-50h] BYREF
  std::string name; // [rsp+40h] [rbp-40h] BYREF
  std::string breaker_name; // [rsp+50h] [rbp-30h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+58h] [rbp-28h]

  if ( pDier )
  {
    if ( pAttacker )
    {
      __x = Player::getCid(pDier);
      iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
      v10._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator==(&iter, &v10) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter);
        score = &v3->second;
        if ( CPeerlessWar::needBroadcastBreakCont(this, v3->second.nBroadCont) )
        {
          nBroadCont = score->nBroadCont;
          Cid = Player::getCid(pDier);
          Player::getName((const Player *const)&name);
          v6 = Player::getCid(pAttacker);
          Player::getName((const Player *const)&breaker_name);
          CPeerlessWar::broadcastBreakConst(this, &breaker_name, v6, &name, Cid, nBroadCont);
          std::string::~string(&breaker_name);
          std::string::~string(&name);
        }
        score->nBroadCont = 0;
        score->nContKill = 0;
        if ( score->nReviveTimes > 2 )
          Player::leaveActivity(pDier);
        CPeerlessWar::addPlayerKillCount(this, pAttacker);
        CPeerlessWar::checkWin(this);
      }
    }
  }
}


#####################################
void __cdecl CPeerlessWar::onPlayerRevive(CPeerlessWar *const this, Player *player, bool bSafe)
{
  std::pair<const long int,CPeerlessWar::PlayerScore> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+20h] [rbp-20h] BYREF
  __int64 __x; // [rsp+28h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v6; // [rsp+30h] [rbp-10h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+38h] [rbp-8h]

  if ( player && this->m_nWarState != 1 )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v6._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator==(&iter, &v6)
      || (v3 = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter),
          score = &v3->second,
          v3->second.nReviveTimes > 2) )
    {
      Player::leaveActivity(player);
    }
    else
    {
      ++score->nReviveTimes;
      (*((void (__fastcall **)(CPeerlessWar *const, Player *))this->_vptr_CActivity + 51))(this, player);
    }
  }
}


#####################################
void __cdecl CPeerlessWar::addPlayer(CPeerlessWar *const this, Player *player)
{
  CExtCharTitle *CharTitle; // rax
  CPeerlessWar::PlayerScore score; // [rsp+20h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+50h] [rbp-80h] BYREF
  __int64 __x; // [rsp+58h] [rbp-78h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v6; // [rsp+60h] [rbp-70h] BYREF
  _BYTE v7[16]; // [rsp+70h] [rbp-60h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> >,bool> v8; // [rsp+80h] [rbp-50h]
  std::pair<const long int,CPeerlessWar::PlayerScore> v9; // [rsp+90h] [rbp-40h] BYREF

  if ( player )
  {
    CharTitle = Player::GetCharTitle(player);
    CExtCharTitle::ShowActivityTitle(CharTitle);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v6._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator!=(&iter, &v6) )
    {
      std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter)->second.bInActivity = 1;
    }
    else
    {
      memset(&score.strName, 0, 25);
      std::string::string(&score.strName);
      score.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v7);
      std::string::operator=(&score.strName, v7);
      std::string::~string(v7);
      score.bInActivity = 1;
      std::pair<long const,CPeerlessWar::PlayerScore>::pair(&v9, &score.nCharId, &score);
      v8 = std::map<long,CPeerlessWar::PlayerScore>::insert(&this->m_mPlayerScore, &v9);
      std::pair<long const,CPeerlessWar::PlayerScore>::~pair(&v9);
      CPeerlessWar::PlayerScore::~PlayerScore(&score);
    }
    CActivity::addPlayer(this, player);
    CActivity::setNeedBroadcastActivityScore(this);
  }
}


#####################################
void __cdecl CPeerlessWar::removePlayer(CPeerlessWar *const this, Player *player, bool islogout)
{
  CExtCharTitle *CharTitle; // rax
  std::pair<const long int,CPeerlessWar::PlayerScore> *v4; // rax
  int32_t nKillCount; // edx
  CExtCharBag *Bag; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+20h] [rbp-30h] BYREF
  __int64 __x; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v10; // [rsp+30h] [rbp-20h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    CharTitle = Player::GetCharTitle(player);
    CExtCharTitle::HideActivityTitle(CharTitle, 1);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v10._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator!=(&iter, &v10) )
    {
      v4 = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter);
      score = &v4->second;
      v4->second.bInActivity = 0;
      if ( this->m_nWarState == 2 )
      {
        CPeerlessWar::addJoinReward(this, score->nCharId);
        nKillCount = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter)->second.nKillCount;
        CPeerlessWar::sendActivityResult(this, player, 0, nKillCount);
      }
    }
    Bag = Player::GetBag(player);
    CExtCharBag::CleanItemId(Bag, 574, ITEM_CHANGE_REASON::ICR_LEAVE_ACTIVE, 1);
    CActivity::removePlayer(this, player, islogout);
    CActivity::setNeedBroadcastActivityScore(this);
    CPeerlessWar::checkWin(this);
  }
}


#####################################
void __cdecl CPeerlessWar::sendPlayerScore(CPeerlessWar *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  __int64 __x; // [rsp+18h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v10; // [rsp+20h] [rbp-30h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v10._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator==(&iter, &v10) )
    {
      score = &std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter)->second;
      ConnId = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E24u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt32(packet, 3 - score->nReviveTimes);
        Answer::NetPacket::writeInt32(packet, score->nKillCount);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(player);
        v6 = Player::getConnId(player);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CPeerlessWar::sendActivityResult(CPeerlessWar *const this, Player *player, int8_t nRes, int32_t KillCount)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E27u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      Answer::NetPacket::writeInt8(packet, nRes);
      Answer::NetPacket::writeInt32(packet, KillCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v8 = Player::getConnId(player);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CPeerlessWar::getLeftReviveTimes(CPeerlessWar *const this, Player *player)
{
  std::pair<const long int,CPeerlessWar::PlayerScore> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+10h] [rbp-20h] BYREF
  __int64 __x; // [rsp+18h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v6; // [rsp+20h] [rbp-10h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+28h] [rbp-8h]

  if ( !player )
    return 0;
  __x = Player::getCid(player);
  iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
  v6._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator==(&iter, &v6) )
    return 0;
  v3 = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter);
  score = &v3->second;
  return 3 - v3->second.nReviveTimes;
}


#####################################
void __cdecl CPeerlessWar::win(CPeerlessWar *const this, Player *pWinner)
{
  CExtCharTitle *CharTitle; // rax
  CharId_t m_nWinner; // rbx
  CActivityManager *v4; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > it; // [rsp+10h] [rbp-40h] BYREF
  char v6; // [rsp+20h] [rbp-30h] BYREF
  __int64 __x; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v8; // [rsp+30h] [rbp-20h] BYREF
  int32_t KillerCount; // [rsp+3Ch] [rbp-14h]

  if ( pWinner )
  {
    if ( Player::getCid(pWinner) != this->m_nWinner )
      CPeerlessWar::clearOldTitle(this);
    CharTitle = Player::GetCharTitle(pWinner);
    CExtCharTitle::CheckAddTitle(CharTitle, 2, 1);
    this->m_nWinner = Player::getCid(pWinner);
    Player::getName((const Player *const)&v6);
    std::string::operator=(&this->m_strWinnerName, &v6);
    std::string::~string(&v6);
    m_nWinner = this->m_nWinner;
    v4 = Answer::Singleton<CActivityManager>::instance();
    CActivityManager::SetPeerlessWarWinner(v4, 0, m_nWinner);
    CPeerlessWar::broadcastWin(this, &this->m_strWinnerName, this->m_nWinner);
    this->m_nState = ACTIVITY_STATE::AS_END;
    this->m_nWarState = 3;
    CPeerlessWar::saveWarResult(this);
    CPeerlessWar::addWinnerReward(this);
    CPeerlessWar::addRewards(this);
    KillerCount = 0;
    __x = Player::getCid(pWinner);
    it._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v8._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator!=(&it, &v8) )
      KillerCount = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&it)->second.nKillCount;
    CPeerlessWar::sendActivityResult(this, pWinner, 1, KillerCount);
    CActivity::delayKickAll(this, 30);
    (*((void (__fastcall **)(CPeerlessWar *const))this->_vptr_CActivity + 55))(this);
    (*((void (__fastcall **)(CPeerlessWar *const))this->_vptr_CActivity + 10))(this);
  }
  else
  {
    CPeerlessWar::draw(this);
  }
}


#####################################
void __cdecl CPeerlessWar::draw(CPeerlessWar *const this)
{
  CActivityManager *v1; // rax

  CPeerlessWar::clearOldTitle(this);
  this->m_nWinner = 0;
  std::string::operator=(&this->m_strWinnerName, &byte_8E8A9D);
  this->m_nState = ACTIVITY_STATE::AS_END;
  this->m_nWarState = 3;
  CPeerlessWar::addRewards(this);
  CPeerlessWar::broadcastDraw(this);
  CPeerlessWar::saveWarResult(this);
  CActivity::delayKickAll(this, 30);
  (*((void (__fastcall **)(CPeerlessWar *const))this->_vptr_CActivity + 55))(this);
  (*((void (__fastcall **)(CPeerlessWar *const))this->_vptr_CActivity + 10))(this);
  v1 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SetPeerlessWarWinner(v1, 0, 0);
}


#####################################
void __cdecl CPeerlessWar::addWinnerReward(CPeerlessWar *const this)
{
  CharId_t m_nWinner; // rbx
  DBService *v2; // rax
  MemChrBag reward; // [rsp+20h] [rbp-40h] BYREF
  std::string Param; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+4Fh] [rbp-11h] BYREF

  if ( this->m_nWinner > 0 )
  {
    *(_QWORD *)&reward.itemId = 0x100000000LL;
    *(_QWORD *)&reward.itemCount = 0x100000001LL;
    *(_QWORD *)&reward.endTime = 0;
    reward.srcId = 0;
    reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 0);
    std::allocator<char>::allocator(v5);
    std::string::string(&Param, &byte_8E8A9D);
    m_nWinner = this->m_nWinner;
    v2 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v2, 0, m_nWinner, 6258, &reward, ITEM_CHANGE_REASON::ICR_PEER_LESS_WAR_REWARD, &Param, 0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(v5);
  }
}


#####################################
void __cdecl CPeerlessWar::addJoinReward(CPeerlessWar *const this, CharId_t nCharId)
{
  DBService *v2; // rax
  MemChrBag reward; // [rsp+20h] [rbp-40h] BYREF
  std::string Param; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+4Fh] [rbp-11h] BYREF

  if ( nCharId > 0 )
  {
    *(_QWORD *)&reward.itemId = 0x100000000LL;
    *(_QWORD *)&reward.itemCount = 0x100000001LL;
    *(_QWORD *)&reward.endTime = 0;
    reward.srcId = 0;
    reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 1u);
    std::allocator<char>::allocator(v5);
    std::string::string(&Param, &byte_8E8A9D);
    v2 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v2, 0, nCharId, 6259, &reward, ITEM_CHANGE_REASON::ICR_PEER_LESS_WAR_REWARD, &Param, 0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(v5);
  }
}


#####################################
void __cdecl CPeerlessWar::addKillReward(CPeerlessWar *const this, CharId_t nCharId, int32_t nKillCount)
{
  DBService *v3; // rax
  DBService *v4; // rax
  MemChrBag reward; // [rsp+30h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-30h] BYREF
  char v7; // [rsp+5Fh] [rbp-21h] BYREF
  std::string v8; // [rsp+60h] [rbp-20h] BYREF
  _BYTE v9[17]; // [rsp+6Fh] [rbp-11h] BYREF

  if ( nKillCount == 3 )
  {
    *(_QWORD *)&reward.itemId = 0x100000000LL;
    *(_QWORD *)&reward.itemCount = 0x100000001LL;
    *(_QWORD *)&reward.endTime = 0;
    reward.srcId = 0;
    reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 2u);
    std::allocator<char>::allocator(&v7);
    std::string::string(&Param, &byte_8E8A9D);
    v3 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v3, 0, nCharId, 6260, &reward, ITEM_CHANGE_REASON::ICR_PEER_LESS_WAR_REWARD, &Param, 0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(&v7);
  }
  else if ( nKillCount == 10 )
  {
    *(_QWORD *)&reward.itemId = 0x100000000LL;
    *(_QWORD *)&reward.itemCount = 0x100000001LL;
    *(_QWORD *)&reward.endTime = 0;
    reward.srcId = 0;
    reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 3u);
    std::allocator<char>::allocator(v9);
    std::string::string(&v8, &byte_8E8A9D);
    v4 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v4, 0, nCharId, 6261, &reward, ITEM_CHANGE_REASON::ICR_PEER_LESS_WAR_REWARD, &v8, 0);
    std::string::~string(&v8);
    std::allocator<char>::~allocator(v9);
  }
}


#####################################
void __cdecl CPeerlessWar::addRewards(CPeerlessWar *const this)
{
  std::pair<const long int,CPeerlessWar::PlayerScore> *v1; // rax
  CharId_t nCharId; // rbx
  GameService *v3; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > __x; // [rsp+20h] [rbp-30h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+30h] [rbp-20h]
  Player *player; // [rsp+38h] [rbp-18h]

  for ( iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator!=(&iter, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter);
    score = &v1->second;
    if ( v1->second.bInActivity && score->nCharId != this->m_nWinner )
    {
      CPeerlessWar::addJoinReward(this, score->nCharId);
      nCharId = score->nCharId;
      v3 = Answer::Singleton<GameService>::instance();
      player = GameService::getPlayer(v3, nCharId, 0, 0);
      if ( player )
        CPeerlessWar::sendActivityResult(this, player, 0, score->nKillCount);
    }
  }
}


#####################################
void __cdecl CPeerlessWar::saveWarResult(CPeerlessWar *const this)
{
  int32_t m_nStartTime; // r13d
  CharId_t m_nWinner; // r12
  int32_t Id; // ebx
  DBService *v4; // rax
  std::string p_name; // [rsp+10h] [rbp-30h] BYREF

  m_nStartTime = this->m_nStartTime;
  std::string::string(&p_name, &this->m_strWinnerName);
  m_nWinner = this->m_nWinner;
  Id = CActivity::GetId(this);
  v4 = Answer::Singleton<DBService>::instance();
  DBService::SavePeerlessWarResult(v4, Id, m_nWinner, &p_name, m_nStartTime);
  std::string::~string(&p_name);
}


#####################################
void __cdecl CPeerlessWar::clearOldTitle(CPeerlessWar *const this)
{
  CharId_t m_nWinner; // rbx
  GameService *v2; // rax

  if ( this->m_nWinner > 0 )
  {
    m_nWinner = this->m_nWinner;
    v2 = Answer::Singleton<GameService>::instance();
    GameService::onRemoveTitle(v2, m_nWinner, 2);
  }
}


#####################################
bool __cdecl CPeerlessWar::needBroadcastContKill(CPeerlessWar *const this, int32_t nCountKill)
{
  return (unsigned int)nCountKill <= 0x14 && ((1LL << nCountKill) & 0x100420) != 0;
}


#####################################
bool __cdecl CPeerlessWar::needBroadcastBreakCont(CPeerlessWar *const this, int32_t nCountKill)
{
  return nCountKill == 10 || nCountKill == 20;
}


#####################################
void __cdecl CPeerlessWar::addPlayerKillCount(CPeerlessWar *const this, Player *player)
{
  std::pair<const long int,CPeerlessWar::PlayerScore> *v2; // rax
  int32_t nBroadCont; // r13d
  CharId_t Cid; // r12
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > iter; // [rsp+10h] [rbp-50h] BYREF
  __int64 __x; // [rsp+18h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CPeerlessWar::PlayerScore> > v7; // [rsp+20h] [rbp-40h] BYREF
  std::string name; // [rsp+30h] [rbp-30h] BYREF
  CPeerlessWar::PlayerScore *score; // [rsp+38h] [rbp-28h]

  __x = Player::getCid(player);
  iter._M_node = std::map<long,CPeerlessWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
  v7._M_node = std::map<long,CPeerlessWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator==(&iter, &v7) )
  {
    v2 = std::_Rb_tree_iterator<std::pair<long const,CPeerlessWar::PlayerScore>>::operator->(&iter);
    score = &v2->second;
    ++v2->second.nKillCount;
    ++score->nContKill;
    CPeerlessWar::addKillReward(this, score->nCharId, score->nKillCount);
    if ( CPeerlessWar::needBroadcastContKill(this, score->nContKill) )
    {
      score->nBroadCont = score->nContKill;
      nBroadCont = score->nBroadCont;
      Cid = Player::getCid(player);
      Player::getName((const Player *const)&name);
      CPeerlessWar::broadcastConstKill(this, &name, Cid, nBroadCont);
      std::string::~string(&name);
    }
    (*((void (__fastcall **)(CPeerlessWar *const, Player *))this->_vptr_CActivity + 51))(this, player);
  }
}


#####################################
void __cdecl CPeerlessWar::onTimeEnd(CPeerlessWar *const this)
{
  CPeerlessWar::draw(this);
  CActivity::onTimeEnd(this);
}


#####################################
int32_t __cdecl CPeerlessWar::canEnter(CPeerlessWar *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( this->m_nWarState == 1 )
    return CActivity::canEnter(this, player, pTargetMap);
  else
    return 10109;
}


#####################################
void __cdecl CPeerlessWar::broadcastReady(CPeerlessWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 175);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CPeerlessWar::broadcastStart(CPeerlessWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 176);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CPeerlessWar::broadcastKnockout(CPeerlessWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 177);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CPeerlessWar::broadcastWin(CPeerlessWar *const this, const std::string *const name, CharId_t cid)
{
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 178);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, 0, packet);
  }
}


#####################################
void __cdecl CPeerlessWar::broadcastConstKill(
        CPeerlessWar *const this,
        const std::string *const name,
        CharId_t cid,
        int32_t cont)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 180);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    Answer::NetPacket::writeInt32(packet, cont);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v6, 0, packet);
  }
}


#####################################
void __cdecl CPeerlessWar::broadcastBreakConst(
        CPeerlessWar *const this,
        const std::string *const breaker_name,
        CharId_t breaker_cid,
        const std::string *const name,
        CharId_t cid,
        int32_t cont)
{
  GameService *v6; // rax
  uint32_t WOffset; // edx
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 181);
    Answer::NetPacket::writeUTF8(packet, breaker_name);
    Answer::NetPacket::writeInt64(packet, breaker_cid);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    Answer::NetPacket::writeInt32(packet, cont);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v8, 0, packet);
  }
}


#####################################
void __cdecl CPeerlessWar::broadcastDraw(CPeerlessWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 179);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
bool __cdecl CPeerlessWar::checkWin(CPeerlessWar *const this)
{
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-20h] BYREF
  Player *pWinner; // [rsp+30h] [rbp-10h]
  Player *player; // [rsp+38h] [rbp-8h]

  if ( this->m_nState != ACTIVITY_STATE::AS_RUNNING )
    return 0;
  if ( this->m_nWarState != 2 )
    return 0;
  pWinner = 0;
  iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
  eiter._M_node = std::list<Player *>::end(&this->m_players)._M_node;
  while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
  {
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( player )
    {
      if ( Unit::isAlive(player) || CPeerlessWar::getLeftReviveTimes(this, player) > 0 )
      {
        if ( pWinner )
          return 0;
        pWinner = player;
      }
    }
    std::_List_iterator<Player *>::operator++(&iter);
  }
  CPeerlessWar::win(this, pWinner);
  return 1;
}


#####################################
void __cdecl CPeerlessWar::OnPeerlessWarResult(
        CPeerlessWar *const this,
        CharId_t winner,
        const std::string *const name)
{
  this->m_nState = ACTIVITY_STATE::AS_END;
  this->m_nWinner = winner;
  std::string::operator=(&this->m_strWinnerName, name);
}


#####################################
std::string __cdecl CPeerlessWar::GetWinnerName(const CPeerlessWar *const this)
{
  const std::string *v1; // rsi

  std::string::string((std::string *)this, v1 + 19);
  return (std::string)this;
}


