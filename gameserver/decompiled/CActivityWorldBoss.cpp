// Decompiled methods for class: CActivityWorldBoss
// Source: gameserver.cc
// Total methods: 23

#####################################
void __cdecl CActivityWorldBoss::~CActivityWorldBoss(CActivityWorldBoss *const this)
{
  CActivityWorldBoss::~CActivityWorldBoss(this);
  operator delete(this);
}


#####################################
void __cdecl CActivityWorldBoss::OnUpdate(CActivityWorldBoss *const this, CActivityMap *pMap)
{
  CActivity::OnUpdate(this, pMap);
}


#####################################
void __cdecl CActivityWorldBoss::reset(CActivityWorldBoss *const this)
{
  CActivity::reset(this);
  std::map<long,CActivityWorldBoss::PlayerScore>::clear(&this->m_mPlayerScore);
  std::multiset<CActivityWorldBoss::PlayerScore *,CActivityWorldBoss::PlayerScoreRankGreater,std::allocator<CActivityWorldBoss::PlayerScore *>>::clear(&this->m_sScoreRank);
  std::map<long,int>::clear(&this->m_ReviveTimes);
  this->m_IsBossDie = 0;
}


#####################################
int32_t __cdecl CActivityWorldBoss::canEnter(CActivityWorldBoss *const this, Player *player, CActivityMap *pTargetMap)
{
  return CActivity::canEnter(this, player, pTargetMap);
}


#####################################
void __cdecl CActivityWorldBoss::onMonsterDamaged(
        CActivityWorldBoss *const this,
        MonsterActivity *pMonster,
        int32_t nDamage,
        Player *pAttacker)
{
  if ( pMonster && pAttacker && Monster::getBossSign(pMonster) == 4 )
  {
    CActivityWorldBoss::addPlayerScore(this, pAttacker, nDamage);
    (*((void (__fastcall **)(CActivityWorldBoss *const, Player *))this->_vptr_CActivity + 51))(this, pAttacker);
  }
}


#####################################
void __cdecl CActivityWorldBoss::onPlayerKilled(CActivityWorldBoss *const this, Player *pDier, Player *pKiller)
{
  int *v3; // rax
  std::pair<const long int,CActivityWorldBoss::PlayerScore> *v4; // rax
  std::pair<const long int,CActivityWorldBoss::PlayerScore> *v5; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > it; // [rsp+30h] [rbp-40h] BYREF
  __int64 __k; // [rsp+40h] [rbp-30h] BYREF
  __int64 __x; // [rsp+48h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v11; // [rsp+50h] [rbp-20h] BYREF
  __int64 Cid; // [rsp+58h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v13; // [rsp+60h] [rbp-10h] BYREF
  int32_t Score; // [rsp+6Ch] [rbp-4h]

  if ( pDier && this->m_nState != ACTIVITY_STATE::AS_END )
  {
    __k = Player::getCid(pDier);
    v3 = std::map<long,int>::operator[](&this->m_ReviveTimes, &__k);
    ++*v3;
    if ( pKiller )
    {
      Score = 0;
      __x = Player::getCid(pDier);
      it._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
      v11._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&it, &v11) )
      {
        Score = 20
              * std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&it)->second.nDamage
              / 100;
        if ( Score > 0 )
        {
          v4 = std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&it);
          v4->second.nDamage -= Score;
        }
      }
      if ( Score > 0 )
      {
        Cid = Player::getCid(pKiller);
        iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::find(&this->m_mPlayerScore, &Cid)._M_node;
        v13._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&iter, &v13) )
        {
          v5 = std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter);
          v5->second.nDamage += Score;
        }
      }
      CActivityWorldBoss::refreshRank(this);
      CActivity::setNeedBroadcastActivityScore(this);
      (*((void (__fastcall **)(CActivityWorldBoss *const, Player *))this->_vptr_CActivity + 51))(this, pDier);
      (*((void (__fastcall **)(CActivityWorldBoss *const, Player *))this->_vptr_CActivity + 51))(this, pKiller);
    }
    else
    {
      (*((void (__fastcall **)(CActivityWorldBoss *const, Player *))this->_vptr_CActivity + 51))(this, pDier);
    }
  }
}


#####################################
void __cdecl CActivityWorldBoss::onMonsterDie(
        CActivityWorldBoss *const this,
        MonsterActivity *pMonster,
        Player *pKiller)
{
  CharId_t nCharId; // r12
  int8_t connId; // bl
  DBService *v5; // rax
  MemChrBag bagItem; // [rsp+30h] [rbp-50h] BYREF
  std::string Param; // [rsp+50h] [rbp-30h] BYREF
  char v8; // [rsp+5Fh] [rbp-21h] BYREF
  const CActivityWorldBoss::PlayerScore *FirstPlayer; // [rsp+60h] [rbp-20h]
  int32_t nMailId; // [rsp+6Ch] [rbp-14h]

  if ( pMonster && pKiller && CActivity::IsRuning(this) && Monster::getBossSign(pMonster) == 4 )
  {
    this->m_IsBossDie = 1;
    FirstPlayer = CActivityWorldBoss::getRankFirst(this);
    if ( FirstPlayer )
    {
      CActivityWorldBoss::broadcastBossKilled(this, &FirstPlayer->strName, FirstPlayer->nCharId);
      memset(&bagItem, 0, sizeof(bagItem));
      bagItem.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 5u);
      bagItem.itemClass = 1;
      bagItem.itemCount = 1;
      bagItem.bind = 1;
      nMailId = 6505;
      std::allocator<char>::allocator(&v8);
      std::string::string(&Param, &unk_8C1DEF, &v8);
      nCharId = FirstPlayer->nCharId;
      connId = FirstPlayer->connId;
      v5 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(
        v5,
        connId,
        nCharId,
        nMailId,
        &bagItem,
        ITEM_CHANGE_REASON::ICR_WORLD_BOSS_KILL_REWARD,
        &Param,
        0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v8);
    }
  }
}


#####################################
void __cdecl CActivityWorldBoss::onMonsterAdd(CActivityWorldBoss *const this, MonsterActivity *pMonster)
{
  if ( pMonster )
  {
    if ( (*((unsigned __int8 (__fastcall **)(MonsterActivity *))pMonster->_vptr_Entity + 17))(pMonster) == 1 )
    {
      Monster::SetSyncTime(pMonster, 2000);
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
void __cdecl CActivityWorldBoss::addPlayer(CActivityWorldBoss *const this, Player *player)
{
  std::pair<const long int,CActivityWorldBoss::PlayerScore> *v2; // rbx
  CActivityWorldBoss::PlayerScore score; // [rsp+20h] [rbp-100h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+70h] [rbp-B0h] BYREF
  __int64 __x; // [rsp+78h] [rbp-A8h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v6; // [rsp+80h] [rbp-A0h] BYREF
  char v7; // [rsp+90h] [rbp-90h] BYREF
  __int64 __k; // [rsp+98h] [rbp-88h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> >,bool> v9; // [rsp+A0h] [rbp-80h]
  std::pair<const long int,CActivityWorldBoss::PlayerScore> v10; // [rsp+B0h] [rbp-70h] BYREF

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v6._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&iter, &v6) )
    {
      std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter)->second.bInActivity = 1;
      v2 = std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter);
      v2->second.nStartTick = Unit::getTick(player);
    }
    else
    {
      CActivityWorldBoss::PlayerScore::PlayerScore(&score);
      score.nCharId = Player::getCid(player);
      Player::getName((const Player *const)&v7);
      std::string::operator=(&score.strName, &v7);
      std::string::~string(&v7);
      score.bInActivity = 1;
      score.nStartTick = Unit::getTick(player);
      __k = Player::getCid(player);
      *std::map<long,int>::operator[](&this->m_ReviveTimes, &__k) = 0;
      score.connId = Player::getConnId(player);
      std::pair<long const,CActivityWorldBoss::PlayerScore>::pair(&v10, &score.nCharId, &score);
      v9 = std::map<long,CActivityWorldBoss::PlayerScore>::insert(&this->m_mPlayerScore, &v10);
      std::pair<long const,CActivityWorldBoss::PlayerScore>::~pair(&v10);
      CActivityWorldBoss::PlayerScore::~PlayerScore(&score);
    }
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CActivityWorldBoss::removePlayer(CActivityWorldBoss *const this, Player *player, bool islogout)
{
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+20h] [rbp-20h] BYREF
  __int64 __x; // [rsp+28h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v5; // [rsp+30h] [rbp-10h] BYREF

  CActivity::removePlayer(this, player, islogout);
  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v5._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&iter, &v5) )
      std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter)->second.bInActivity = 0;
  }
}


#####################################
bool __cdecl CActivityWorldBoss::needBroadcastActivityScore(CActivityWorldBoss *const this, CActivityMap *pMap)
{
  if ( !pMap )
    return 0;
  if ( this->m_nBraodcastActivityScoreSign <= 0 )
    return 0;
  if ( Map::getTick(pMap) - this->m_nBroadcastActivityScoreTick <= 2999 )
    return 0;
  this->m_nBroadcastActivityScoreTick = Map::getTick(pMap);
  --this->m_nBraodcastActivityScoreSign;
  return 1;
}


#####################################
void __cdecl CActivityWorldBoss::sendPlayerScore(CActivityWorldBoss *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+20h] [rbp-50h] BYREF
  __int64 __x; // [rsp+28h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > v11; // [rsp+30h] [rbp-40h] BYREF
  __int64 Cid; // [rsp+38h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v13; // [rsp+40h] [rbp-30h] BYREF
  int32_t DieTimes; // [rsp+4Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+50h] [rbp-20h]
  const CActivityWorldBoss::PlayerScore *score; // [rsp+58h] [rbp-18h]

  if ( player )
  {
    DieTimes = 0;
    __x = Player::getCid(player);
    it._M_node = std::map<long,int>::find(&this->m_ReviveTimes, &__x)._M_node;
    v11._M_node = std::map<long,int>::end(&this->m_ReviveTimes)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&it, &v11) )
      DieTimes = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it)->second;
    Cid = Player::getCid(player);
    iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::find(&this->m_mPlayerScore, &Cid)._M_node;
    v13._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator==(&iter, &v13) )
    {
      ConnId = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E24u);
      if ( packet )
      {
        score = &std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter)->second;
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt32(packet, score->nIndex);
        Answer::NetPacket::writeInt32(packet, score->nDamage);
        Answer::NetPacket::writeInt32(packet, DieTimes);
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
void __cdecl CActivityWorldBoss::addPlayerScore(CActivityWorldBoss *const this, Player *player, int32_t nDamage)
{
  std::pair<const long int,CActivityWorldBoss::PlayerScore> *v3; // rax
  std::pair<const long int,CActivityWorldBoss::PlayerScore> *v4; // rbx
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+20h] [rbp-30h] BYREF
  __int64 __x; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v7; // [rsp+30h] [rbp-20h] BYREF
  int32_t Score; // [rsp+3Ch] [rbp-14h]

  if ( this->m_nState != ACTIVITY_STATE::AS_END && player )
  {
    Score = 0;
    if ( nDamage <= 100000 )
      Score = 1;
    else
      Score = nDamage / 100000;
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v7._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&iter, &v7) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter);
      v3->second.nDamage += Score;
      v4 = std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter);
      v4->second.DamageTick = Unit::getTick(player);
      CActivity::setNeedBroadcastActivityScore(this);
      CActivityWorldBoss::refreshRank(this);
    }
  }
}


#####################################
void __cdecl CActivityWorldBoss::addRewards(CActivityWorldBoss *const this)
{
  std::pair<const long int,CActivityWorldBoss::PlayerScore> *v1; // rax
  CharId_t nCharId; // r12
  int8_t connId; // bl
  DBService *v4; // rax
  MemChrBag bagItem; // [rsp+20h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > eiter; // [rsp+40h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+50h] [rbp-40h] BYREF
  std::string Param; // [rsp+60h] [rbp-30h] BYREF
  char v9; // [rsp+6Fh] [rbp-21h] BYREF
  const CActivityWorldBoss::PlayerScore *score; // [rsp+70h] [rbp-20h]
  int32_t nGiftId; // [rsp+78h] [rbp-18h]
  int32_t nMailId; // [rsp+7Ch] [rbp-14h]

  CActivityWorldBoss::refreshRank(this);
  iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
  eiter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&iter, &eiter) )
  {
    v1 = std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter);
    score = &v1->second;
    nGiftId = 0;
    nMailId = 0;
    if ( v1->second.nIndex <= 10 || score->bInActivity )
    {
      if ( score->nDamage > 0 )
      {
        if ( score->nIndex <= 0 )
          goto LABEL_16;
        if ( score->nIndex == 1 )
        {
          nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 1u);
          nMailId = 6502;
        }
        else if ( score->nIndex > 3 )
        {
          if ( score->nIndex > 10 )
          {
            nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 4u);
            nMailId = 6501;
          }
          else
          {
            nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 3u);
            nMailId = 6504;
          }
        }
        else
        {
          nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 2u);
          nMailId = 6503;
        }
      }
      else
      {
        nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 0);
        nMailId = 6501;
      }
      if ( nGiftId > 0 )
      {
        *(_DWORD *)&bagItem.itemClass = 1;
        *(_QWORD *)&bagItem.itemCount = 0x100000001LL;
        *(_QWORD *)&bagItem.endTime = 0;
        bagItem.srcId = 0;
        bagItem.itemId = nGiftId;
        std::allocator<char>::allocator(&v9);
        std::string::string(&Param, &unk_8C1DEF, &v9);
        nCharId = score->nCharId;
        connId = score->connId;
        v4 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(
          v4,
          connId,
          nCharId,
          nMailId,
          &bagItem,
          ITEM_CHANGE_REASON::ICR_WORLD_BOSS_KILL_REWARD,
          &Param,
          0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(&v9);
      }
    }
LABEL_16:
    std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator++(&iter);
  }
}


#####################################
void __cdecl CActivityWorldBoss::onTimeEnd(CActivityWorldBoss *const this)
{
  CActivityWorldBoss::addRewards(this);
  (*((void (__fastcall **)(CActivityWorldBoss *const))this->_vptr_CActivity + 59))(this);
  (*((void (__fastcall **)(CActivityWorldBoss *const))this->_vptr_CActivity + 43))(this);
  this->m_nState = ACTIVITY_STATE::AS_END;
  CActivity::delayKickAll(this, 30);
}


#####################################
void __cdecl CActivityWorldBoss::broadcastStart(CActivityWorldBoss *const this)
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
    Answer::NetPacket::writeInt32(packet, 323);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, packet);
  }
}


#####################################
void __cdecl CActivityWorldBoss::broadcastBossKilled(
        CActivityWorldBoss *const this,
        const std::string *const name,
        CharId_t cid)
{
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 324);
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt64(packet, cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, packet);
  }
}


#####################################
void __cdecl CActivityWorldBoss::broadcastEnd(CActivityWorldBoss *const this)
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
    Answer::NetPacket::writeInt32(packet, 325);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, packet);
  }
}


#####################################
int32_t __cdecl CActivityWorldBoss::getAutoReviveTime(const CActivityWorldBoss *const this, Player *player)
{
  std::_Rb_tree_const_iterator<std::pair<const long int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  int64_t CharId; // [rsp+18h] [rbp-18h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Time; // [rsp+2Ch] [rbp-4h]

  if ( !player )
    return 10000;
  CharId = Player::getCid(player);
  Time = 0;
  it._M_node = std::map<long,int>::find(&this->m_ReviveTimes, &CharId)._M_node;
  __x._M_node = std::map<long,int>::end(&this->m_ReviveTimes)._M_node;
  if ( std::_Rb_tree_const_iterator<std::pair<long const,int>>::operator!=(&it, &__x) )
    Time = std::_Rb_tree_const_iterator<std::pair<long const,int>>::operator->(&it)->second;
  if ( 5 * Time <= 30 )
    return 5000 * Time;
  else
    return 30000;
}


#####################################
void __cdecl CActivityWorldBoss::refreshRank(CActivityWorldBoss *const this)
{
  CActivityWorldBoss::PlayerScore *const *v1; // rax
  CActivityWorldBoss::PlayerScore *const *v2; // rax
  CharId_t v3; // rbx
  GameService *v4; // rax
  std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore*> iter_0; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > iter; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CActivityWorldBoss::PlayerScore> > v7; // [rsp+30h] [rbp-40h] BYREF
  CActivityWorldBoss::PlayerScore *__x; // [rsp+38h] [rbp-38h] BYREF
  std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore*> v9; // [rsp+40h] [rbp-30h] BYREF
  int32_t nIndex; // [rsp+54h] [rbp-1Ch]
  Player *pPlayer; // [rsp+58h] [rbp-18h]

  std::multiset<CActivityWorldBoss::PlayerScore *,CActivityWorldBoss::PlayerScoreRankGreater,std::allocator<CActivityWorldBoss::PlayerScore *>>::clear(&this->m_sScoreRank);
  for ( iter._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator++(&iter) )
  {
    v7._M_node = std::map<long,CActivityWorldBoss::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator!=(&iter, &v7) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter)->second.nDamage > 0 )
    {
      __x = &std::_Rb_tree_iterator<std::pair<long const,CActivityWorldBoss::PlayerScore>>::operator->(&iter)->second;
      std::multiset<CActivityWorldBoss::PlayerScore *,CActivityWorldBoss::PlayerScoreRankGreater,std::allocator<CActivityWorldBoss::PlayerScore *>>::insert(
        &this->m_sScoreRank,
        &__x);
    }
  }
  nIndex = 1;
  for ( iter_0._M_node = std::multiset<CActivityWorldBoss::PlayerScore *,CActivityWorldBoss::PlayerScoreRankGreater,std::allocator<CActivityWorldBoss::PlayerScore *>>::begin(&this->m_sScoreRank)._M_node;
        ;
        std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore *>::operator++(&iter_0) )
  {
    v9._M_node = std::multiset<CActivityWorldBoss::PlayerScore *,CActivityWorldBoss::PlayerScoreRankGreater,std::allocator<CActivityWorldBoss::PlayerScore *>>::end(&this->m_sScoreRank)._M_node;
    if ( !std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore *>::operator!=(&iter_0, &v9) )
      break;
    v1 = std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore *>::operator*(&iter_0);
    if ( (*v1)->nIndex != nIndex )
    {
      v2 = std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore *>::operator*(&iter_0);
      (*v2)->nIndex = nIndex;
      if ( (*std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore *>::operator*(&iter_0))->bInActivity )
      {
        v3 = **(_QWORD **)std::_Rb_tree_const_iterator<CActivityWorldBoss::PlayerScore *>::operator*(&iter_0);
        v4 = Answer::Singleton<GameService>::instance();
        pPlayer = GameService::getPlayer(v4, v3, 0, 0);
        if ( pPlayer )
          (*((void (__fastcall **)(CActivityWorldBoss *const, Player *))this->_vptr_CActivity + 51))(this, pPlayer);
      }
    }
    ++nIndex;
  }
}


#####################################
bool __cdecl CActivityWorldBoss::OnSitRevive(CActivityWorldBoss *const this, Player *player)
{
  return player != 0;
}


#####################################
int32_t __cdecl CActivityWorldBoss::GetRevive(CActivityWorldBoss *const this, Player *player)
{
  return CActivity::GetRevive(this, player);
}


#####################################
void __cdecl CActivityWorldBoss::broadcastActivityResult(CActivityWorldBoss *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // eax
  std::_List_const_iterator<CActivityMap*> iter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+20h] [rbp-40h] BYREF
  std::_List_const_iterator<CActivityMap*> v5; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<CActivityMap*> v6; // [rsp+40h] [rbp-20h] BYREF
  CActivityMap *pMap; // [rsp+50h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-8h]

  __x._M_node = std::list<CActivityMap *>::begin(&this->m_activityMaps)._M_node;
  std::_List_const_iterator<CActivityMap *>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v6._M_node = std::list<CActivityMap *>::end(&this->m_activityMaps)._M_node;
    std::_List_const_iterator<CActivityMap *>::_List_const_iterator(&v5, &v6);
    if ( !std::_List_const_iterator<CActivityMap *>::operator!=(&iter, &v5) )
      break;
    pMap = *std::_List_const_iterator<CActivityMap *>::operator*(&iter);
    if ( pMap )
    {
      v1 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2E27u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt8(packet, this->m_IsBossDie);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        Map::broadcast(pMap, packet);
      }
    }
    std::_List_const_iterator<CActivityMap *>::operator++(&iter);
  }
}


