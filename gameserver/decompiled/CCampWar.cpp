// Decompiled methods for class: CCampWar
// Source: gameserver.cc
// Total methods: 28

#####################################
void __cdecl CCampWar::~CCampWar(CCampWar *const this)
{
  CCampWar::~CCampWar(this);
  operator delete(this);
}


#####################################
void __cdecl CCampWar::OnUpdate(CCampWar *const this, CActivityMap *pMap)
{
  GameService *v2; // rax
  uint32_t WOffset; // eax
  GameService *v4; // rax
  int32_t v5; // r12d
  CharId_t v6; // rbx
  GameService *v7; // rax
  int32_t RunnerId; // r12d
  CharId_t nCharId; // rbx
  GameService *v10; // rax
  std::_Rb_tree_const_iterator<CCampWar::PlayerScore*> iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<CCampWar::PlayerScore*> __x; // [rsp+20h] [rbp-40h] BYREF
  int32_t curTick; // [rsp+2Ch] [rbp-34h]
  Answer::NetPacket *packet; // [rsp+30h] [rbp-30h]
  CCampWar::PlayerScore *score; // [rsp+38h] [rbp-28h]
  Player *pPlayer; // [rsp+40h] [rbp-20h]
  Player *pPlayer_0; // [rsp+48h] [rbp-18h]

  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    if ( CActivity::IsRuning(this) )
    {
      curTick = Map::getNow(pMap);
      if ( curTick - this->m_nLastTime > 299 )
      {
        this->m_nLastTime = curTick;
        v2 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( packet )
        {
          Answer::NetPacket::writeInt32(packet, 421);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v4 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v4, 0, packet);
          CActivity::setNeedBroadcastActivityScore(this);
          for ( iter._M_node = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::begin(&this->m_sScoreRank)._M_node;
                ;
                std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator++(&iter) )
          {
            __x._M_node = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::end(&this->m_sScoreRank)._M_node;
            if ( !std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator!=(&iter, &__x) )
              break;
            score = *std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator*(&iter);
            if ( score->nRankIndex && score->bInActivity )
            {
              if ( (score->nRankIndex & 1) != 0 )
              {
                score->nCamp = 2;
                RunnerId = Map::GetRunnerId(pMap);
                nCharId = score->nCharId;
                v10 = Answer::Singleton<GameService>::instance();
                pPlayer_0 = GameService::getPlayer(v10, nCharId, RunnerId, 1);
                if ( pPlayer_0 )
                  Player::SetCamp(pPlayer_0, 2);
              }
              else
              {
                score->nCamp = 1;
                v5 = Map::GetRunnerId(pMap);
                v6 = score->nCharId;
                v7 = Answer::Singleton<GameService>::instance();
                pPlayer = GameService::getPlayer(v7, v6, v5, 1);
                if ( pPlayer )
                  Player::SetCamp(pPlayer, 1);
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CCampWar::reset(CCampWar *const this)
{
  CActivity::reset(this);
  this->m_nLastTime = 0;
  std::map<int,int>::clear(&this->m_BuffIdMap);
  std::map<long,CCampWar::PlayerScore>::clear(&this->m_mPlayerScore);
  std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::clear(&this->m_sScoreRank);
  this->m_Camp_1_battle = 0;
  this->m_Camp_2_battle = 0;
}


#####################################
void __cdecl CCampWar::onPlayerKilled(CCampWar *const this, Player *pDier, Player *pAttacker)
{
  CExtCharTitle *CharTitle; // rax
  int32_t nContLevel; // r14d
  CharId_t Cid; // r13
  CharId_t v6; // r12
  int32_t nKillCount; // ebx
  __int64 first; // rcx
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > AttIt; // [rsp+30h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+40h] [rbp-A0h] BYREF
  __int64 __x; // [rsp+48h] [rbp-98h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v13; // [rsp+50h] [rbp-90h] BYREF
  CCampWar::PlayerScore *p_second; // [rsp+58h] [rbp-88h] BYREF
  std::string breaker_name; // [rsp+60h] [rbp-80h] BYREF
  std::string name; // [rsp+70h] [rbp-70h] BYREF
  std::pair<std::_Rb_tree_const_iterator<CCampWar::PlayerScore*>,bool> v17; // [rsp+80h] [rbp-60h]
  CCampWar::PlayerScore *v18; // [rsp+90h] [rbp-50h] BYREF
  __int64 v19; // [rsp+98h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v20; // [rsp+A0h] [rbp-40h] BYREF
  CCampWar::PlayerScore *score; // [rsp+B0h] [rbp-30h]
  int32_t nPoint; // [rsp+B8h] [rbp-28h]
  int32_t AddOtherPoint; // [rsp+BCh] [rbp-24h]

  if ( pDier )
  {
    if ( pAttacker )
    {
      __x = Player::getCid(pDier);
      iter._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
      v13._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator==(&iter, &v13) )
      {
        score = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
        p_second = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
        std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::erase(
          &this->m_sScoreRank,
          &p_second);
        if ( score->nContLevel > 0 )
        {
          CharTitle = Player::GetCharTitle(pDier);
          CExtCharTitle::SetActivityTitle(CharTitle, 0, 0);
          nContLevel = score->nContLevel;
          Cid = Player::getCid(pAttacker);
          Player::getName((const Player *const)&breaker_name);
          v6 = Player::getCid(pDier);
          Player::getName((const Player *const)&name);
          CCampWar::broadcastBreakContKill(this, &name, v6, &breaker_name, Cid, nContLevel);
          std::string::~string(&name);
          std::string::~string(&breaker_name);
        }
        nPoint = 5;
        AddOtherPoint = 20 * score->nPoints / 100;
        nPoint = AddOtherPoint + 5;
        score->nPoints -= AddOtherPoint;
        v18 = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
        v17 = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::insert(
                &this->m_sScoreRank,
                &v18);
        CCampWar::addPlayerScore(this, pAttacker, nPoint, 1);
        CCampWar::notifyAddScore(this, pAttacker, nPoint, 1);
        score->nContKill = 0;
        score->nContLevel = 0;
        v19 = Player::getCid(pAttacker);
        AttIt._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &v19)._M_node;
        v20._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator==(&AttIt, &v20) )
        {
          nKillCount = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&AttIt)->second.nKillCount;
          first = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&AttIt)->first;
          CCampWar::addKillReward(this, first, nKillCount);
        }
      }
    }
  }
}


#####################################
void __cdecl CCampWar::onMonsterDie(CCampWar *const this, MonsterActivity *pMonster, Player *pKiller)
{
  if ( pMonster )
  {
    if ( pKiller )
    {
      CCampWar::addPlayerScore(this, pKiller, 5, 0);
      CCampWar::notifyAddScore(this, pKiller, 5, 2);
    }
  }
}


#####################################
void __cdecl CCampWar::addKillReward(CCampWar *const this, CharId_t nCharId, int32_t nKillCount)
{
  DBService *v3; // rax
  MemChrBag reward; // [rsp+30h] [rbp-40h] BYREF
  std::string Param; // [rsp+50h] [rbp-20h] BYREF
  char v6; // [rsp+5Bh] [rbp-15h] BYREF
  int32_t MailId; // [rsp+5Ch] [rbp-14h]

  MailId = 0;
  *(_QWORD *)&reward.itemId = 0x100000000LL;
  *(_QWORD *)&reward.itemCount = 0x100000001LL;
  *(_QWORD *)&reward.endTime = 0;
  reward.srcId = 0;
  switch ( nKillCount )
  {
    case 1:
      reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 0);
      MailId = 6256;
      goto LABEL_7;
    case 5:
      reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 1u);
      MailId = 6256;
      goto LABEL_7;
    case 10:
      reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 2u);
      MailId = 6256;
      goto LABEL_7;
    case 20:
      reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 3u);
      MailId = 6256;
      goto LABEL_7;
    case 50:
      reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 4u);
      MailId = 6256;
LABEL_7:
      std::allocator<char>::allocator(&v6);
      std::string::string(&Param, &unk_8C2D4F, &v6);
      v3 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v3, 0, nCharId, MailId, &reward, ITEM_CHANGE_REASON::ICR_PEER_LESS_WAR_REWARD, &Param, 0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v6);
      break;
    default:
      return;
  }
}


#####################################
void __cdecl CCampWar::onPlayerRevive(CCampWar *const this, Player *player, bool bSafe)
{
  int second; // ebx
  int first; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-20h] BYREF

  if ( player )
  {
    for ( it._M_node = std::map<int,int>::begin(&this->m_BuffIdMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_BuffIdMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      if ( second == Player::GetCamp(player) )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
        CActivity::addActivityBuff(this, player, first, 1);
      }
    }
  }
}


#####################################
void __cdecl CCampWar::onPlantGather(CCampWar *const this, PlantActivity *pPlant, Player *player)
{
  int32_t Points; // edx
  int32_t v4; // edx
  int8_t Camp; // dl
  int *v6; // rbx
  int32_t BuffId; // ecx
  GameService *v8; // rax
  CharId_t Cid; // rax
  int8_t v10; // al
  int32_t PlantId; // eax
  uint32_t WOffset; // eax
  GameService *v13; // rax
  int __k; // [rsp+2Ch] [rbp-24h] BYREF
  std::string val; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( pPlant && player && Player::GetCamp(player) > 0 )
  {
    Points = Plant::GetPoints(pPlant);
    CCampWar::addPlayerScore(this, player, Points, 0);
    v4 = Plant::GetPoints(pPlant);
    CCampWar::notifyAddScore(this, player, v4, 0);
    Camp = Player::GetCamp(player);
    Plant::SetCamp(pPlant, Camp);
    __k = Plant::GetBuffId(pPlant);
    v6 = std::map<int,int>::operator[](&this->m_BuffIdMap, &__k);
    *v6 = Player::GetCamp(player);
    LOBYTE(v6) = Player::GetCamp(player);
    BuffId = Plant::GetBuffId(pPlant);
    CCampWar::RefreshBuff(this, BuffId, (int8_t)v6);
    v8 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v8, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 422);
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      v10 = Player::GetCamp(player);
      Answer::NetPacket::writeInt8(packet, v10);
      PlantId = Plant::getPlantId(pPlant);
      Answer::NetPacket::writeInt32(packet, PlantId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v13, 0, packet);
    }
  }
}


#####################################
void __cdecl CCampWar::RefreshBuff(CCampWar *const this, int32_t BuffId, int8_t CampId)
{
  Player **v3; // rax
  Player *v4; // rbx
  Player **v5; // rax
  std::_List_iterator<Player*> PlayerIt; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+20h] [rbp-20h] BYREF

  for ( PlayerIt._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&PlayerIt) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&PlayerIt, &__x) )
      break;
    v3 = std::_List_iterator<Player *>::operator*(&PlayerIt);
    if ( Player::GetCamp(*v3) == CampId )
    {
      v4 = *std::_List_iterator<Player *>::operator*(&PlayerIt);
      CActivity::addActivityBuff(this, v4, BuffId, 1);
    }
    else
    {
      v5 = std::_List_iterator<Player *>::operator*(&PlayerIt);
      Unit::removeBuff(*v5, BuffId);
    }
  }
}


#####################################
void __cdecl CCampWar::broadcastActivityResult(CCampWar *const this)
{
  std::pair<const long int,CCampWar::PlayerScore> *v1; // rax
  CharId_t nCharId; // rbx
  GameService *v3; // rax
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > __x; // [rsp+20h] [rbp-30h] BYREF
  CCampWar::PlayerScore *score; // [rsp+28h] [rbp-28h]
  Player *pPlayer; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  for ( iter._M_node = std::map<long,CCampWar::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator!=(&iter, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter);
    score = &v1->second;
    if ( v1->second.bInActivity )
    {
      nCharId = score->nCharId;
      v3 = Answer::Singleton<GameService>::instance();
      pPlayer = GameService::getPlayer(v3, nCharId, 0, 0);
      if ( pPlayer )
      {
        ConnId = Player::getConnId(pPlayer);
        v5 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E27u);
        if ( !packet )
          return;
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt32(packet, score->nRankIndex);
        Answer::NetPacket::writeInt32(packet, score->nKillCount);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pPlayer);
        v8 = Player::getConnId(pPlayer);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, v8, GateIndex, packet);
      }
    }
  }
}


#####################################
int32_t __cdecl CCampWar::onBeginGather(CCampWar *const this, PlantActivity *pPlant, Player *player)
{
  int8_t Camp; // bl

  if ( !pPlant || !player )
    return 10002;
  if ( Plant::GetCamp(pPlant) && (Camp = Player::GetCamp(player), Camp == Plant::GetCamp(pPlant)) )
    return 10002;
  else
    return 0;
}


#####################################
void __cdecl CCampWar::addPlayer(CCampWar *const this, Player *player)
{
  CExtCharTitle *CharTitle; // rax
  int8_t nCamp; // dl
  int32_t nContLevel; // edx
  int32_t ContTitle; // ebx
  CExtCharTitle *v6; // rax
  int64_t m_Camp_1_battle; // rbx
  int64_t m_Camp_2_battle; // rbx
  int second; // ebx
  int first; // edx
  CCampWar::PlayerScore score; // [rsp+20h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+50h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+60h] [rbp-A0h] BYREF
  __int64 __x; // [rsp+68h] [rbp-98h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v15; // [rsp+70h] [rbp-90h] BYREF
  _BYTE v16[16]; // [rsp+80h] [rbp-80h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> >,bool> v17; // [rsp+90h] [rbp-70h]
  std::pair<const long int,CCampWar::PlayerScore> v18; // [rsp+A0h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v19; // [rsp+E0h] [rbp-20h] BYREF

  if ( player )
  {
    CharTitle = Player::GetCharTitle(player);
    CExtCharTitle::ShowActivityTitle(CharTitle);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v15._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator!=(&iter, &v15) )
    {
      nCamp = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.nCamp;
      Player::SetCamp(player, nCamp);
      if ( std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.nContLevel > 0 )
      {
        nContLevel = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.nContLevel;
        ContTitle = CCampWar::getContTitle(this, nContLevel);
        v6 = Player::GetCharTitle(player);
        CExtCharTitle::SetActivityTitle(v6, 0, ContTitle);
      }
      std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.bInActivity = 1;
    }
    else
    {
      memset(&score, 0, sizeof(score));
      std::string::string(&score.strName);
      score.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v16);
      std::string::operator=(&score.strName, v16);
      std::string::~string(v16);
      score.nAddTime = Unit::getNow(player);
      score.nCamp = CCampWar::selectCamp(this, player);
      score.nRankIndex = 0;
      score.bInActivity = 1;
      Player::SetCamp(player, score.nCamp);
      std::pair<long const,CCampWar::PlayerScore>::pair(&v18, &score.nCharId, &score);
      v17 = std::map<long,CCampWar::PlayerScore>::insert(&this->m_mPlayerScore, &v18);
      std::pair<long const,CCampWar::PlayerScore>::~pair(&v18);
      if ( score.nCamp == 1 )
      {
        m_Camp_1_battle = this->m_Camp_1_battle;
        this->m_Camp_1_battle = m_Camp_1_battle + (*((int (__fastcall **)(Player *))player->_vptr_Entity + 10))(player);
      }
      else
      {
        m_Camp_2_battle = this->m_Camp_2_battle;
        this->m_Camp_2_battle = m_Camp_2_battle + (*((int (__fastcall **)(Player *))player->_vptr_Entity + 10))(player);
      }
      CCampWar::PlayerScore::~PlayerScore(&score);
    }
    for ( it._M_node = std::map<int,int>::begin(&this->m_BuffIdMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      v19._M_node = std::map<int,int>::end(&this->m_BuffIdMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &v19) )
        break;
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      if ( second == Player::GetCamp(player) )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
        CActivity::addActivityBuff(this, player, first, 1);
      }
    }
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CCampWar::removePlayer(CCampWar *const this, Player *player, bool islogout)
{
  CExtCharTitle *CharTitle; // rax
  std::pair<const long int,CCampWar::PlayerScore> *v4; // rbx
  int32_t nPoints; // r12d
  CharId_t nCharId; // rdx
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+30h] [rbp-50h] BYREF
  __int64 __x; // [rsp+38h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v9; // [rsp+40h] [rbp-40h] BYREF
  CCampWar::PlayerScore *p_second; // [rsp+48h] [rbp-38h] BYREF
  std::pair<std::_Rb_tree_const_iterator<CCampWar::PlayerScore*>,bool> v11; // [rsp+50h] [rbp-30h]
  CCampWar::PlayerScore *v12; // [rsp+68h] [rbp-18h] BYREF

  CActivity::removePlayer(this, player, islogout);
  if ( player )
  {
    Player::SetCamp(player, 0);
    CharTitle = Player::GetCharTitle(player);
    CExtCharTitle::HideActivityTitle(CharTitle, 1);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v9._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator!=(&iter, &v9) )
    {
      p_second = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
      std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::erase(
        &this->m_sScoreRank,
        &p_second);
      std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.bInActivity = 0;
      v4 = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter);
      nPoints = v4->second.nPoints;
      v4->second.nPoints = nPoints
                         - (int)((double)std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.nPoints
                               * 0.2);
      v12 = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
      v11 = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::insert(
              &this->m_sScoreRank,
              &v12);
      nCharId = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.nCharId;
      CCampWar::refreshRankIndex(this, nCharId);
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
void __cdecl CCampWar::addPlayerScore(CCampWar *const this, Player *player, int32_t nPoint, int32_t nKillCount)
{
  std::pair<const long int,CCampWar::PlayerScore> *v4; // rax
  int32_t nContKill; // ebx
  CfgData *v6; // rax
  const CfgCampWarTable *CampWarTable; // rax
  CharId_t Cid; // r12
  int32_t v9; // edx
  int32_t ContTitle; // ebx
  CExtCharTitle *CharTitle; // rax
  CharId_t v12; // rdx
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+30h] [rbp-70h] BYREF
  __int64 __x; // [rsp+38h] [rbp-68h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v17; // [rsp+40h] [rbp-60h] BYREF
  CCampWar::PlayerScore *p_second; // [rsp+48h] [rbp-58h] BYREF
  std::string name; // [rsp+50h] [rbp-50h] BYREF
  std::pair<std::_Rb_tree_const_iterator<CCampWar::PlayerScore*>,bool> v20; // [rsp+60h] [rbp-40h]
  CCampWar::PlayerScore *v21; // [rsp+78h] [rbp-28h] BYREF
  CCampWar::PlayerScore *score; // [rsp+80h] [rbp-20h]
  int32_t nContLevel; // [rsp+8Ch] [rbp-14h]

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v17._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator!=(&iter, &v17) )
    {
      p_second = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
      std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::erase(
        &this->m_sScoreRank,
        &p_second);
      v4 = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter);
      score = &v4->second;
      v4->second.nPoints += nPoint;
      if ( nKillCount > 0 )
      {
        score->nKillCount += nKillCount;
        score->nContKill += nKillCount;
        nContKill = score->nContKill;
        v6 = Answer::Singleton<CfgData>::instance();
        CampWarTable = CfgData::GetCampWarTable(v6);
        nContLevel = CfgCampWarTable::GetContKillLevel(CampWarTable, nContKill);
        if ( score->nContLevel != nContLevel )
        {
          score->nContLevel = nContLevel;
          Cid = Player::getCid(player);
          Player::getName((const Player *const)&name);
          CCampWar::broadcastContKill(this, &name, Cid, nContLevel);
          std::string::~string(&name);
          v9 = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second.nContLevel;
          ContTitle = CCampWar::getContTitle(this, v9);
          CharTitle = Player::GetCharTitle(player);
          CExtCharTitle::SetActivityTitle(CharTitle, 0, ContTitle);
        }
      }
      v21 = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
      v20 = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::insert(
              &this->m_sScoreRank,
              &v21);
      v12 = Player::getCid(player);
      CCampWar::refreshRankIndex(this, v12);
      (*((void (__fastcall **)(CCampWar *const, Player *))this->_vptr_CActivity + 51))(this, player);
      CActivity::setNeedBroadcastActivityScore(this);
      if ( score->nPoints > 1999 )
        CCampWar::onWarEnd(this);
    }
  }
}


#####################################
void __cdecl CCampWar::refreshRankIndex(CCampWar *const this, CharId_t nCharId)
{
  CharId_t v2; // rbx
  GameService *v3; // rax
  std::_Rb_tree_const_iterator<CCampWar::PlayerScore*> eiter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<CCampWar::PlayerScore*> iter; // [rsp+20h] [rbp-30h] BYREF
  int32_t nIndex; // [rsp+2Ch] [rbp-24h]
  CCampWar::PlayerScore *pScore; // [rsp+30h] [rbp-20h]
  Player *player; // [rsp+38h] [rbp-18h]

  nIndex = 1;
  iter._M_node = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::begin(&this->m_sScoreRank)._M_node;
  eiter._M_node = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::end(&this->m_sScoreRank)._M_node;
  while ( std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator!=(&iter, &eiter) )
  {
    pScore = *std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator*(&iter);
    if ( pScore )
    {
      if ( pScore->nRankIndex != nIndex )
      {
        pScore->nRankIndex = nIndex;
        if ( pScore->bInActivity && pScore->nCharId != nCharId )
        {
          v2 = pScore->nCharId;
          v3 = Answer::Singleton<GameService>::instance();
          player = GameService::getPlayer(v3, v2, 0, 0);
          if ( player )
            (*((void (__fastcall **)(CCampWar *const, Player *))this->_vptr_CActivity + 51))(this, player);
        }
      }
      ++nIndex;
    }
    std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator++(&iter);
  }
}


#####################################
void __cdecl CCampWar::addRewards(CCampWar *const this)
{
  std::pair<const long int,CCampWar::PlayerScore> *v1; // rax
  int32_t nRankIndex; // ebx
  CfgData *v3; // rax
  const CfgCampWarTable *CampWarTable; // rax
  MemChrBagVector *p_WinItems; // r13
  int32_t nWinMailId; // r12d
  CharId_t nCharId; // rbx
  DBService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > eiter; // [rsp+20h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+30h] [rbp-50h] BYREF
  std::string Param; // [rsp+40h] [rbp-40h] BYREF
  char v12; // [rsp+4Fh] [rbp-31h] BYREF
  const CCampWar::PlayerScore *score; // [rsp+50h] [rbp-30h]
  const CfgCampWarReward *pReward; // [rsp+58h] [rbp-28h]

  (*((void (__fastcall **)(CCampWar *const))this->_vptr_CActivity + 43))(this);
  iter._M_node = std::map<long,CCampWar::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
  eiter._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator!=(&iter, &eiter) )
  {
    v1 = std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter);
    score = &v1->second;
    nRankIndex = v1->second.nRankIndex;
    v3 = Answer::Singleton<CfgData>::instance();
    CampWarTable = CfgData::GetCampWarTable(v3);
    pReward = CfgCampWarTable::GetReward(CampWarTable, nRankIndex);
    if ( pReward )
    {
      std::allocator<char>::allocator(&v12);
      std::string::string(&Param, &unk_8C2D4F, &v12);
      p_WinItems = &pReward->WinItems;
      nWinMailId = pReward->nWinMailId;
      nCharId = score->nCharId;
      v8 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(
        v8,
        0,
        nCharId,
        nWinMailId,
        p_WinItems,
        ITEM_CHANGE_REASON::ICR_CAMP_WAR_REWARD,
        &Param,
        0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v12);
    }
    std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator++(&iter);
  }
}


#####################################
void __cdecl CCampWar::onTimeEnd(CCampWar *const this)
{
  CCampWar::addRewards(this);
  this->m_nState = ACTIVITY_STATE::AS_END;
  CActivity::delayKickAll(this, 0);
  (*((void (__fastcall **)(CCampWar *const))this->_vptr_CActivity + 10))(this);
}


#####################################
void __cdecl CCampWar::onWarEnd(CCampWar *const this)
{
  CCampWar::addRewards(this);
  this->m_nState = ACTIVITY_STATE::AS_END;
  CActivity::delayKickAll(this, 0);
  (*((void (__fastcall **)(CCampWar *const))this->_vptr_CActivity + 10))(this);
}


#####################################
int32_t __cdecl CCampWar::canEnter(CCampWar *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( player && pTargetMap )
    return CActivity::canEnter(this, player, pTargetMap);
  else
    return 10002;
}


#####################################
void __cdecl CCampWar::sendPlayerScore(CCampWar *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  __int64 __x; // [rsp+18h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v10; // [rsp+20h] [rbp-30h] BYREF
  const CCampWar::PlayerScore *score; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v10._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator==(&iter, &v10) )
    {
      score = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
      ConnId = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E24u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        Answer::NetPacket::writeInt8(packet, score->nCamp);
        Answer::NetPacket::writeInt32(packet, score->nPoints);
        Answer::NetPacket::writeInt32(packet, score->nKillCount);
        Answer::NetPacket::writeInt16(packet, score->nRankIndex);
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
void __cdecl CCampWar::SendPlayerRankInfo(CCampWar *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_Rb_tree_const_iterator<CCampWar::PlayerScore*> iter_0; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > iter; // [rsp+20h] [rbp-60h] BYREF
  __int64 __x; // [rsp+28h] [rbp-58h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCampWar::PlayerScore> > v11; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<CCampWar::PlayerScore*> v12; // [rsp+40h] [rbp-40h] BYREF
  const CCampWar::PlayerScore *score; // [rsp+48h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+50h] [rbp-30h]
  int16_t nCount; // [rsp+5Eh] [rbp-22h]
  uint32_t offset; // [rsp+60h] [rbp-20h]
  uint32_t oldOffset; // [rsp+64h] [rbp-1Ch]
  CCampWar::PlayerScore *pScore; // [rsp+68h] [rbp-18h]

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCampWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v11._M_node = std::map<long,CCampWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator==(&iter, &v11) )
    {
      score = &std::_Rb_tree_iterator<std::pair<long const,CCampWar::PlayerScore>>::operator->(&iter)->second;
      ConnId = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E2Au);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        nCount = 0;
        offset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::writeInt16(packet, nCount);
        for ( iter_0._M_node = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::begin(&this->m_sScoreRank)._M_node;
              ;
              std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator++(&iter_0) )
        {
          v12._M_node = std::set<CCampWar::PlayerScore *,CCampWar::PlayerScoreGreater,std::allocator<CCampWar::PlayerScore *>>::end(&this->m_sScoreRank)._M_node;
          if ( !std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator!=(&iter_0, &v12) )
            break;
          pScore = *std::_Rb_tree_const_iterator<CCampWar::PlayerScore *>::operator*(&iter_0);
          if ( pScore )
          {
            if ( pScore->nPoints > 0 )
            {
              Answer::NetPacket::writeUTF8(packet, &pScore->strName);
              Answer::NetPacket::writeInt8(packet, pScore->nCamp);
              Answer::NetPacket::writeInt32(packet, pScore->nPoints);
              Answer::NetPacket::writeInt32(packet, pScore->nKillCount);
              ++nCount;
            }
          }
        }
        oldOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, offset);
        Answer::NetPacket::writeInt16(packet, nCount);
        Answer::NetPacket::setWOffset(packet, oldOffset);
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
void __cdecl CCampWar::broadcastReady(CCampWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 169);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CCampWar::broadcastStart(CCampWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 170);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CCampWar::broadcastContKill(
        CCampWar *const this,
        const std::string *const name,
        CharId_t cid,
        int32_t nContLevel)
{
  CfgData *v4; // rax
  const CfgCampWarTable *CampWarTable; // rax
  GameService *v6; // rax
  uint32_t WOffset; // edx
  GameService *v8; // rax
  const CfgCampWarContKill *pContKill; // [rsp+20h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<CfgData>::instance();
  CampWarTable = CfgData::GetCampWarTable(v4);
  pContKill = CfgCampWarTable::GetContKill(CampWarTable, nContLevel);
  if ( pContKill )
  {
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pContKill->nBroadcast);
      Answer::NetPacket::writeUTF8(packet, name);
      Answer::NetPacket::writeInt64(packet, cid);
      Answer::NetPacket::writeInt32(packet, pContKill->nKillCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, 0, packet);
    }
  }
}


#####################################
void __cdecl CCampWar::broadcastBreakContKill(
        CCampWar *const this,
        const std::string *const name,
        CharId_t cid,
        const std::string *const breaker_name,
        CharId_t breaker_cid,
        int32_t nContLevel)
{
  CfgData *v6; // rax
  const CfgCampWarTable *CampWarTable; // rax
  GameService *v8; // rax
  uint32_t WOffset; // edx
  GameService *v10; // rax
  const CfgCampWarContKill *pContKill; // [rsp+30h] [rbp-10h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  v6 = Answer::Singleton<CfgData>::instance();
  CampWarTable = CfgData::GetCampWarTable(v6);
  pContKill = CfgCampWarTable::GetContKill(CampWarTable, nContLevel);
  if ( pContKill )
  {
    v8 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v8, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pContKill->nBreakBroadcast);
      Answer::NetPacket::writeUTF8(packet, breaker_name);
      Answer::NetPacket::writeInt64(packet, breaker_cid);
      Answer::NetPacket::writeUTF8(packet, name);
      Answer::NetPacket::writeInt64(packet, cid);
      Answer::NetPacket::writeInt32(packet, pContKill->nKillCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v10, 0, packet);
    }
  }
}


#####################################
int32_t __cdecl CCampWar::selectCamp(CCampWar *const this, Player *player)
{
  if ( !player )
    return 0;
  if ( this->m_Camp_1_battle <= this->m_Camp_2_battle )
    return 1;
  return 2;
}


#####################################
int32_t __cdecl CCampWar::getContTitle(CCampWar *const this, int32_t nContLevel)
{
  CfgData *v2; // rax
  const CfgCampWarTable *CampWarTable; // rax
  const CfgCampWarContKill *pContKill; // [rsp+18h] [rbp-8h]

  if ( nContLevel > 0
    && (v2 = Answer::Singleton<CfgData>::instance(),
        CampWarTable = CfgData::GetCampWarTable(v2),
        (pContKill = CfgCampWarTable::GetContKill(CampWarTable, nContLevel)) != 0) )
  {
    return pContKill->nTitle;
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl CCampWar::notifyAddScore(CCampWar *const this, Player *player, int32_t nPoint, int32_t nKillCount)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int8_t nKillCounta; // [rsp+8h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  nKillCounta = nKillCount;
  if ( player )
  {
    ConnId = Player::getConnId(player);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E2Bu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nPoint);
      Answer::NetPacket::writeInt8(packet, nKillCounta);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v8 = Player::getConnId(player);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


