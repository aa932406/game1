// Decompiled methods for class: CFamilyWar
// Source: gameserver.cc
// Total methods: 31

#####################################
void __cdecl CFamilyWar::~CFamilyWar(CFamilyWar *const this)
{
  CFamilyWar::~CFamilyWar(this);
  operator delete(this);
}


#####################################
void __cdecl CFamilyWar::OnUpdate(CFamilyWar *const this, CActivityMap *pMap)
{
  bool v2; // al
  FamilyId_t FamilyId; // rcx
  CFamilyWar::PlayerScore *v4; // rax
  int32_t RunnerId; // r12d
  CharId_t nCharId; // rbx
  GameService *v8; // rax
  CFamilyWar::PlayerScore *v10; // rax
  int32_t v11; // ebx
  CfgData *v12; // rax
  const CfgFamilyWarTable *FamilyWarTable; // rax
  CFamilyWar::PlayerScore *v14; // rax
  std::_List_iterator<CFamilyWar::PlayerScore> iter; // [rsp+10h] [rbp-50h] BYREF
  std::string strFamilyName; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> __x; // [rsp+30h] [rbp-30h] BYREF
  int64_t curTick; // [rsp+38h] [rbp-28h]
  Player *pPlayer; // [rsp+40h] [rbp-20h]
  int32_t nExp; // [rsp+4Ch] [rbp-14h]

  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    curTick = Map::getTick(pMap);
    v2 = this->m_pBuffPlayer && StaticObj::getMap(this->m_pBuffPlayer) == pMap;
    if ( v2 && curTick - this->m_nBuffStartTick > 299999 )
    {
      Player::getFamilyName((const Player *const)&strFamilyName);
      FamilyId = Player::getFamilyId(this->m_pBuffPlayer);
      CFamilyWar::win(this, FamilyId, &strFamilyName);
      std::string::~string(&strFamilyName);
      CFamilyWar::removeBuff(this, this->m_pBuffPlayer);
      this->m_pBuffPlayer = 0;
      CActivity::setNeedBroadcastActivityScore(this);
    }
    for ( iter._M_node = std::list<CFamilyWar::PlayerScore>::begin(&this->m_lstPlayerScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::PlayerScore>::operator++(&iter) )
    {
      __x._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::PlayerScore>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->bInActivity )
      {
        v4 = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter);
        if ( curTick - v4->nStartTick > 9999 )
        {
          RunnerId = Map::GetRunnerId(pMap);
          nCharId = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nCharId;
          v8 = Answer::Singleton<GameService>::instance();
          pPlayer = GameService::getPlayer(v8, nCharId, RunnerId, 1);
          if ( pPlayer && StaticObj::getMap(pPlayer) == pMap )
          {
            v10 = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter);
            v10->nStartTick = curTick;
            v11 = (*((__int64 (__fastcall **)(Player *))pPlayer->_vptr_Entity + 9))(pPlayer);
            v12 = Answer::Singleton<CfgData>::instance();
            FamilyWarTable = CfgData::GetFamilyWarTable(v12);
            nExp = CfgFamilyWarTable::GetJoinReward(FamilyWarTable, v11);
            Player::addExp(pPlayer, nExp, 0, 1);
            v14 = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter);
            v14->nExp += nExp;
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CFamilyWar::reset(CFamilyWar *const this)
{
  CActivity::reset(this);
  this->m_nActiveState = 0;
  this->m_nActivePillarState = 0;
  this->m_pTitle = 0;
  this->m_pBoss = 0;
  this->m_pBuffPlayer = 0;
  this->m_nBuffStartTick = 0;
  this->m_nWinFamily = 0;
  std::string::operator=(&this->m_strWingFamily, &unk_8D842F);
  std::list<CFamilyWar::FamilyScore>::clear(&this->m_lstFamilyScore);
  std::list<CFamilyWar::PlayerScore>::clear(&this->m_lstPlayerScore);
}


#####################################
void __cdecl CFamilyWar::onMonsterDie(CFamilyWar *const this, MonsterActivity *pMonster, Player *pKiller)
{
  int32_t KillPoints; // edx

  if ( pMonster && pKiller && CActivity::IsRuning(this) )
  {
    KillPoints = Monster::GetKillPoints(pMonster);
    CFamilyWar::addPlayerScore(this, pKiller, KillPoints, 0);
    if ( this->m_pTitle == pMonster )
    {
      this->m_pBuffPlayer = pKiller;
      this->m_nBuffStartTick = Unit::getTick(pKiller);
      CFamilyWar::addBuff(this, this->m_pBuffPlayer);
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
void __cdecl CFamilyWar::onPlayerKilled(CFamilyWar *const this, Player *pDier, Player *pAttacker)
{
  ChrTask *Task; // rax

  if ( pDier && pAttacker )
  {
    CFamilyWar::addPlayerScore(this, pAttacker, 20, 1);
    Task = Player::GetTask(pAttacker);
    ChrTask::updateTaskCount(Task, 27, 0);
    if ( this->m_pBuffPlayer == pDier )
    {
      this->m_pBuffPlayer = pAttacker;
      this->m_nBuffStartTick = Unit::getTick(pAttacker);
      CFamilyWar::addBuff(this, this->m_pBuffPlayer);
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
void __cdecl CFamilyWar::onMonsterAdd(CFamilyWar *const this, MonsterActivity *pMonster)
{
  if ( pMonster )
  {
    if ( MonsterActivity::getActivityMonsterId(pMonster) == 20333 )
    {
      this->m_pTitle = pMonster;
    }
    else if ( MonsterActivity::getActivityMonsterId(pMonster) == 20334 )
    {
      this->m_pBoss = pMonster;
    }
  }
}


#####################################
void __cdecl CFamilyWar::AdjustMonsterAttr(CFamilyWar *const this, CfgMonster *const cfgMonster)
{
  GameService *v2; // rax
  int32_t WorldLevel; // edx

  v2 = Answer::Singleton<GameService>::instance();
  WorldLevel = GameService::GetWorldLevel(v2);
  CActivity::adjustMonsterAttr(this, cfgMonster, WorldLevel, 1);
}


#####################################
bool __cdecl CFamilyWar::OnChangeMap(
        CFamilyWar *const this,
        Player *player,
        CActivityMap *pMap,
        int32_t nX,
        int32_t nY,
        int32_t param)
{
  std::_List_iterator<CActivityMap*> iter; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+40h] [rbp-20h] BYREF
  bool bFind; // [rsp+53h] [rbp-Dh]
  int32_t nIndex; // [rsp+54h] [rbp-Ch]
  CActivityMap *tp; // [rsp+58h] [rbp-8h]

  if ( !player || !pMap )
    return 0;
  if ( !Map::isWalkablePosition(pMap, nX, nY) )
    return 0;
  bFind = 0;
  nIndex = 0;
  for ( iter._M_node = std::list<CActivityMap *>::begin(&this->m_activityMaps)._M_node;
        ;
        std::_List_iterator<CActivityMap *>::operator++(&iter) )
  {
    __x._M_node = std::list<CActivityMap *>::end(&this->m_activityMaps)._M_node;
    if ( !std::_List_iterator<CActivityMap *>::operator!=(&iter, &__x) )
      break;
    ++nIndex;
    tp = *std::_List_iterator<CActivityMap *>::operator*(&iter);
    if ( tp && tp == pMap )
    {
      bFind = 1;
      break;
    }
  }
  if ( !bFind )
    return 0;
  if ( nIndex == 2 )
    return this->m_nActivePillarState == 15;
  if ( nIndex != 3 )
    return 0;
  return this->m_nWinFamily > 0 && Player::getFamilyId(player) == this->m_nWinFamily;
}


#####################################
void __cdecl CFamilyWar::addPlayer(CFamilyWar *const this, Player *player)
{
  CharId_t nCharId; // rbx
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgActivityTaskTable *ActivityTaskTable; // rax
  ChrTask *Task; // rax
  CFamilyWar::PlayerScore score; // [rsp+10h] [rbp-90h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> iter; // [rsp+50h] [rbp-50h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> __x; // [rsp+60h] [rbp-40h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> v10; // [rsp+70h] [rbp-30h] BYREF
  _BYTE v11[12]; // [rsp+80h] [rbp-20h] BYREF
  int32_t nTaskId; // [rsp+8Ch] [rbp-14h]

  if ( player )
  {
    if ( Player::getFamilyId(player) <= 0 )
      Player::setPkMode(player, 6, 0);
    else
      Player::setPkMode(player, 3, 0);
    nTaskId = 0;
    for ( iter._M_node = std::list<CFamilyWar::PlayerScore>::begin(&this->m_lstPlayerScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::PlayerScore>::operator++(&iter) )
    {
      __x._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::PlayerScore>::operator!=(&iter, &__x) )
        break;
      nCharId = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nCharId;
      if ( nCharId == Player::getCid(player) )
      {
        std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->bInActivity = 1;
        nTaskId = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nTaskId;
        break;
      }
    }
    v10._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
    if ( std::_List_iterator<CFamilyWar::PlayerScore>::operator==(&iter, &v10) )
    {
      memset(&score, 0, 57);
      std::string::string(&score.strName);
      score.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v11);
      std::string::operator=(&score.strName, v11);
      std::string::~string(v11);
      score.nFamilyId = Player::getFamilyId(player);
      v3 = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 9))(player);
      v4 = Answer::Singleton<CfgData>::instance();
      ActivityTaskTable = CfgData::GetActivityTaskTable(v4);
      score.nTaskId = CfgActivityTaskTable::RandomTask(ActivityTaskTable, v3);
      score.nStartTick = Unit::getTick(player);
      score.bInActivity = 1;
      nTaskId = score.nTaskId;
      std::list<CFamilyWar::PlayerScore>::push_back(&this->m_lstPlayerScore, &score);
      CFamilyWar::PlayerScore::~PlayerScore(&score);
    }
    if ( nTaskId > 0 )
    {
      Task = Player::GetTask(player);
      ChrTask::receive(Task, nTaskId);
    }
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CFamilyWar::removePlayer(CFamilyWar *const this, Player *player, bool islogout)
{
  ChrTask *Task; // rax
  CharId_t nCharId; // rbx
  std::_List_iterator<CFamilyWar::PlayerScore> iter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> __x; // [rsp+30h] [rbp-20h] BYREF

  CActivity::removePlayer(this, player, islogout);
  if ( player )
  {
    if ( Unit::HasBuffById(player, 100001) )
    {
      CFamilyWar::removeBuff(this, player);
      if ( this->m_pTitle )
        Monster::OnRevive(this->m_pTitle);
    }
    Task = Player::GetTask(player);
    ChrTask::CleanTaskType(Task, 41);
    for ( iter._M_node = std::list<CFamilyWar::PlayerScore>::begin(&this->m_lstPlayerScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::PlayerScore>::operator++(&iter) )
    {
      __x._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::PlayerScore>::operator!=(&iter, &__x) )
        break;
      nCharId = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nCharId;
      if ( nCharId == Player::getCid(player) )
      {
        std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->bInActivity = 0;
        return;
      }
    }
  }
}


#####################################
void __cdecl CFamilyWar::addPlayerScore(CFamilyWar *const this, Player *player, int32_t nScore, int32_t nKillCount)
{
  CharId_t Cid; // rdx
  FamilyId_t FamilyId; // rbx
  std::string strFamilyName; // [rsp+30h] [rbp-20h] BYREF
  CFamilyWar::PlayerScore *pPlayerScore; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    Cid = Player::getCid(player);
    pPlayerScore = CFamilyWar::getPlayerScore(this, Cid);
    if ( pPlayerScore )
    {
      if ( nKillCount > 0 )
      {
        if ( pPlayerScore->nKillCount > 19 )
          return;
        pPlayerScore->nKillCount += nKillCount;
      }
      pPlayerScore->nScore += nScore;
      Player::getFamilyName((const Player *const)&strFamilyName);
      FamilyId = Player::getFamilyId(player);
      CFamilyWar::addFamilyScore(this, FamilyId, &strFamilyName, nScore);
      std::string::~string(&strFamilyName);
      std::list<CFamilyWar::PlayerScore>::sort<std::greater<CFamilyWar::PlayerScore>>(
        &this->m_lstPlayerScore,
        (std::greater<CFamilyWar::PlayerScore>)FamilyId);
      (*((void (__fastcall **)(CFamilyWar *const, Player *))this->_vptr_CActivity + 51))(this, player);
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
void __cdecl CFamilyWar::addFamilyScore(
        CFamilyWar *const this,
        FamilyId_t nFamilyId,
        const std::string *const strFamilyName,
        int32_t nScore)
{
  CFamilyWar::FamilyScore *v4; // rax
  void *p_score; // rsi
  CFamilyWar::FamilyScore score; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> iter; // [rsp+50h] [rbp-40h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> __x; // [rsp+60h] [rbp-30h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> v12; // [rsp+70h] [rbp-20h] BYREF

  for ( iter._M_node = std::list<CFamilyWar::FamilyScore>::begin(&this->m_lstFamilyScore)._M_node;
        ;
        std::_List_iterator<CFamilyWar::FamilyScore>::operator++(&iter) )
  {
    __x._M_node = std::list<CFamilyWar::FamilyScore>::end(&this->m_lstFamilyScore)._M_node;
    if ( !std::_List_iterator<CFamilyWar::FamilyScore>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter)->nFamilyId == nFamilyId )
    {
      v4 = std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter);
      v4->nScore += nScore;
      break;
    }
  }
  v12._M_node = std::list<CFamilyWar::FamilyScore>::end(&this->m_lstFamilyScore)._M_node;
  p_score = &v12;
  if ( std::_List_iterator<CFamilyWar::FamilyScore>::operator==(&iter, &v12) )
  {
    memset(&score.strFamilyName, 0, 20);
    std::string::string(&score.strFamilyName);
    score.nFamilyId = nFamilyId;
    std::string::operator=(&score.strFamilyName, strFamilyName);
    score.nScore = nScore;
    p_score = &score;
    std::list<CFamilyWar::FamilyScore>::push_back(&this->m_lstFamilyScore, &score);
    CFamilyWar::FamilyScore::~FamilyScore(&score);
  }
  std::list<CFamilyWar::FamilyScore>::sort<std::greater<CFamilyWar::FamilyScore>>(
    &this->m_lstFamilyScore,
    (std::greater<CFamilyWar::FamilyScore>)p_score);
  CActivity::setNeedBroadcastActivityScore(this);
}


#####################################
void __cdecl CFamilyWar::win(CFamilyWar *const this, FamilyId_t nFamilyId, const std::string *const strFamilyName)
{
  if ( nFamilyId > 0 )
  {
    this->m_nActiveState = 2;
    this->m_nWinFamily = nFamilyId;
    std::string::operator=(&this->m_strWingFamily, strFamilyName);
    CFamilyWar::sendWinnerReward(this, nFamilyId);
  }
  CFamilyWar::sendPlayerScoreRankReward(this);
  CFamilyWar::sendFamilyScoreRankReward(this);
  CActivity::setNeedBroadcastActivityScore(this);
}


#####################################
void __cdecl CFamilyWar::sendPlayerScoreRankReward(CFamilyWar *const this)
{
  CharId_t nCharId; // rbx
  DBService *v2; // rax
  MemChrBag reward; // [rsp+20h] [rbp-90h] BYREF
  std::_List_const_iterator<CFamilyWar::PlayerScore> iter; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> __x; // [rsp+50h] [rbp-60h] BYREF
  std::_List_const_iterator<CFamilyWar::PlayerScore> v6; // [rsp+60h] [rbp-50h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> v7; // [rsp+70h] [rbp-40h] BYREF
  std::string Param; // [rsp+80h] [rbp-30h] BYREF
  char v9; // [rsp+8Bh] [rbp-25h] BYREF
  int32_t nIndex; // [rsp+8Ch] [rbp-24h]
  const CFamilyWar::PlayerScore *score; // [rsp+90h] [rbp-20h]
  int32_t nGiftId; // [rsp+98h] [rbp-18h]
  int32_t nMailId; // [rsp+9Ch] [rbp-14h]

  nIndex = 1;
  __x._M_node = std::list<CFamilyWar::PlayerScore>::begin(&this->m_lstPlayerScore)._M_node;
  std::_List_const_iterator<CFamilyWar::PlayerScore>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v7._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
    std::_List_const_iterator<CFamilyWar::PlayerScore>::_List_const_iterator(&v6, &v7);
    if ( !std::_List_const_iterator<CFamilyWar::PlayerScore>::operator!=(&iter, &v6) )
      break;
    score = std::_List_const_iterator<CFamilyWar::PlayerScore>::operator*(&iter);
    nGiftId = 0;
    nMailId = 0;
    if ( nIndex == 1 )
    {
      nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 0);
      nMailId = 6336;
    }
    else if ( nIndex <= 1 || nIndex > 3 )
    {
      nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 2u);
      nMailId = 6338;
    }
    else
    {
      nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 1u);
      nMailId = 6337;
    }
    *(_DWORD *)&reward.itemClass = 1;
    *(_QWORD *)&reward.itemCount = 0x100000001LL;
    *(_QWORD *)&reward.endTime = 0;
    reward.srcId = 0;
    reward.itemId = nGiftId;
    std::allocator<char>::allocator(&v9);
    std::string::string(&Param, &unk_8D842F, &v9);
    nCharId = score->nCharId;
    v2 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v2, 0, nCharId, nMailId, &reward, ITEM_CHANGE_REASON::ICR_FAMILY_WAR_REWARD, &Param, 0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(&v9);
    ++nIndex;
    std::_List_const_iterator<CFamilyWar::PlayerScore>::operator++(&iter);
  }
}


#####################################
void __cdecl CFamilyWar::sendFamilyScoreRankReward(CFamilyWar *const this)
{
  FamilyId_t nFamilyid; // rbx
  DBService *v2; // rax
  MemChrBag reward; // [rsp+20h] [rbp-90h] BYREF
  std::_List_const_iterator<CFamilyWar::FamilyScore> iter; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> __x; // [rsp+50h] [rbp-60h] BYREF
  std::_List_const_iterator<CFamilyWar::FamilyScore> v6; // [rsp+60h] [rbp-50h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> v7; // [rsp+70h] [rbp-40h] BYREF
  std::string Param; // [rsp+80h] [rbp-30h] BYREF
  char v9; // [rsp+8Bh] [rbp-25h] BYREF
  int32_t nIndex; // [rsp+8Ch] [rbp-24h]
  const CFamilyWar::FamilyScore *score; // [rsp+90h] [rbp-20h]
  int32_t nGiftId; // [rsp+98h] [rbp-18h]
  int32_t nMailId; // [rsp+9Ch] [rbp-14h]

  nIndex = 1;
  __x._M_node = std::list<CFamilyWar::FamilyScore>::begin(&this->m_lstFamilyScore)._M_node;
  std::_List_const_iterator<CFamilyWar::FamilyScore>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v7._M_node = std::list<CFamilyWar::FamilyScore>::end(&this->m_lstFamilyScore)._M_node;
    std::_List_const_iterator<CFamilyWar::FamilyScore>::_List_const_iterator(&v6, &v7);
    if ( !std::_List_const_iterator<CFamilyWar::FamilyScore>::operator!=(&iter, &v6) )
      break;
    score = std::_List_const_iterator<CFamilyWar::FamilyScore>::operator*(&iter);
    nGiftId = 0;
    nMailId = 0;
    if ( nIndex == 1 )
    {
      nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 3u);
      nMailId = 6339;
    }
    else if ( nIndex <= 1 || nIndex > 3 )
    {
      nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 5u);
      nMailId = 6341;
    }
    else
    {
      nGiftId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 4u);
      nMailId = 6340;
    }
    *(_DWORD *)&reward.itemClass = 1;
    *(_QWORD *)&reward.itemCount = 0x100000001LL;
    *(_QWORD *)&reward.endTime = 0;
    reward.srcId = 0;
    reward.itemId = nGiftId;
    nFamilyid = score->nFamilyId;
    std::allocator<char>::allocator(&v9);
    std::string::string(&Param, &unk_8D842F, &v9);
    v2 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v2, 0, 0, nMailId, &reward, ITEM_CHANGE_REASON::ICR_FAMILY_WAR_REWARD, &Param, nFamilyid);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(&v9);
    ++nIndex;
    std::_List_const_iterator<CFamilyWar::FamilyScore>::operator++(&iter);
  }
}


#####################################
void __cdecl CFamilyWar::sendActivePillarReward(CFamilyWar *const this, FamilyId_t nFamilyId)
{
  DBService *v2; // rax
  MemChrBag reward; // [rsp+20h] [rbp-40h] BYREF
  std::string Param; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+4Fh] [rbp-11h] BYREF

  memset(&reward, 0, sizeof(reward));
  reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 6u);
  reward.itemClass = 1;
  reward.itemCount = 1;
  reward.bind = 1;
  std::allocator<char>::allocator(v5);
  std::string::string(&Param, &unk_8D842F, v5);
  v2 = Answer::Singleton<DBService>::instance();
  DBService::OnSendSysMail(v2, 0, 0, 6342, &reward, ITEM_CHANGE_REASON::ICR_FAMILY_WAR_REWARD, &Param, nFamilyId);
  std::string::~string(&Param);
  std::allocator<char>::~allocator(v5);
}


#####################################
void __cdecl CFamilyWar::sendWinnerReward(CFamilyWar *const this, FamilyId_t nFamilyId)
{
  DBService *v2; // rax
  MemChrBag reward; // [rsp+20h] [rbp-40h] BYREF
  std::string Param; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+4Fh] [rbp-11h] BYREF

  memset(&reward, 0, sizeof(reward));
  reward.itemId = *std::vector<int>::operator[](&this->m_cfgActivity->gift_id, 7u);
  reward.itemClass = 1;
  reward.itemCount = 1;
  reward.bind = 1;
  std::allocator<char>::allocator(v5);
  std::string::string(&Param, &unk_8D842F, v5);
  v2 = Answer::Singleton<DBService>::instance();
  DBService::OnSendSysMail(v2, 0, 0, 6343, &reward, ITEM_CHANGE_REASON::ICR_FAMILY_WAR_REWARD, &Param, nFamilyId);
  std::string::~string(&Param);
  std::allocator<char>::~allocator(v5);
}


#####################################
void __cdecl CFamilyWar::onTimeEnd(CFamilyWar *const this)
{
  FamilyId_t FamilyId; // rcx
  std::string strFamilyName; // [rsp+10h] [rbp-30h] BYREF
  std::string v3; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v4[17]; // [rsp+2Fh] [rbp-11h] BYREF

  if ( this->m_pBuffPlayer )
  {
    Player::getFamilyName((const Player *const)&strFamilyName);
    FamilyId = Player::getFamilyId(this->m_pBuffPlayer);
    CFamilyWar::win(this, FamilyId, &strFamilyName);
    std::string::~string(&strFamilyName);
  }
  else
  {
    std::allocator<char>::allocator(v4);
    std::string::string(&v3, &unk_8D842F, v4);
    CFamilyWar::win(this, 0, &v3);
    std::string::~string(&v3);
    std::allocator<char>::~allocator(v4);
  }
  CActivity::onTimeEnd(this);
  CActivity::sendSocialUpdateActivityState(this, 0);
}


#####################################
void __cdecl CFamilyWar::appendPlayerScoreRank(CFamilyWar *const this, Answer::NetPacket *packet)
{
  std::string *p_strName; // rdx
  int32_t nScore; // edx
  std::_List_iterator<CFamilyWar::PlayerScore> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> __x; // [rsp+20h] [rbp-20h] BYREF
  int8_t nCount; // [rsp+37h] [rbp-9h]
  uint32_t offset; // [rsp+38h] [rbp-8h]
  uint32_t oldOffset; // [rsp+3Ch] [rbp-4h]

  if ( packet )
  {
    nCount = 0;
    offset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt8(packet, 0);
    for ( iter._M_node = std::list<CFamilyWar::PlayerScore>::begin(&this->m_lstPlayerScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::PlayerScore>::operator++(&iter) )
    {
      __x._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::PlayerScore>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nScore <= 0 )
        break;
      p_strName = &std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->strName;
      Answer::NetPacket::writeUTF8(packet, p_strName);
      nScore = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nScore;
      Answer::NetPacket::writeInt32(packet, nScore);
      if ( ++nCount > 9 )
        break;
    }
    oldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, offset);
    Answer::NetPacket::writeInt8(packet, nCount);
    Answer::NetPacket::setWOffset(packet, oldOffset);
  }
}


#####################################
void __cdecl CFamilyWar::appendFamilyScoreRank(CFamilyWar *const this, Answer::NetPacket *packet)
{
  std::string *p_strFamilyName; // rdx
  int32_t nScore; // edx
  std::_List_iterator<CFamilyWar::FamilyScore> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> __x; // [rsp+20h] [rbp-20h] BYREF
  int8_t nCount; // [rsp+37h] [rbp-9h]
  uint32_t offset; // [rsp+38h] [rbp-8h]
  uint32_t oldOffset; // [rsp+3Ch] [rbp-4h]

  if ( packet )
  {
    nCount = 0;
    offset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt8(packet, 0);
    for ( iter._M_node = std::list<CFamilyWar::FamilyScore>::begin(&this->m_lstFamilyScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::FamilyScore>::operator++(&iter) )
    {
      __x._M_node = std::list<CFamilyWar::FamilyScore>::end(&this->m_lstFamilyScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::FamilyScore>::operator!=(&iter, &__x) )
        break;
      p_strFamilyName = &std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter)->strFamilyName;
      Answer::NetPacket::writeUTF8(packet, p_strFamilyName);
      nScore = std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter)->nScore;
      Answer::NetPacket::writeInt32(packet, nScore);
      if ( ++nCount > 2 )
        break;
    }
    oldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, offset);
    Answer::NetPacket::writeInt8(packet, nCount);
    Answer::NetPacket::setWOffset(packet, oldOffset);
  }
}


#####################################
void __cdecl CFamilyWar::sendPlayerScore(CFamilyWar *const this, Player *player)
{
  CharId_t nCharId; // rbx
  FamilyId_t nFamilyId; // rbx
  int32_t v4; // ebx
  int8_t ConnId; // bl
  GameService *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_iterator<CFamilyWar::FamilyScore> iter_0; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> iter; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<CFamilyWar::PlayerScore> __x; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<CFamilyWar::FamilyScore> v14; // [rsp+40h] [rbp-30h] BYREF
  int8_t nIndex; // [rsp+4Bh] [rbp-25h]
  int32_t nScore; // [rsp+4Ch] [rbp-24h]
  int8_t nTaskCount; // [rsp+52h] [rbp-1Eh]
  int8_t nFamilyIndex; // [rsp+53h] [rbp-1Dh]
  int32_t nFamilyScore; // [rsp+54h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  if ( player )
  {
    nIndex = 0;
    nScore = 0;
    nTaskCount = 0;
    for ( iter._M_node = std::list<CFamilyWar::PlayerScore>::begin(&this->m_lstPlayerScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::PlayerScore>::operator++(&iter) )
    {
      __x._M_node = std::list<CFamilyWar::PlayerScore>::end(&this->m_lstPlayerScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::PlayerScore>::operator!=(&iter, &__x) )
        break;
      ++nIndex;
      nCharId = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nCharId;
      if ( nCharId == Player::getCid(player) )
      {
        nScore = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nScore;
        nTaskCount = std::_List_iterator<CFamilyWar::PlayerScore>::operator->(&iter)->nTaskCount;
        break;
      }
    }
    nFamilyIndex = 0;
    nFamilyScore = 0;
    for ( iter_0._M_node = std::list<CFamilyWar::FamilyScore>::begin(&this->m_lstFamilyScore)._M_node;
          ;
          std::_List_iterator<CFamilyWar::FamilyScore>::operator++(&iter_0) )
    {
      v14._M_node = std::list<CFamilyWar::FamilyScore>::end(&this->m_lstFamilyScore)._M_node;
      if ( !std::_List_iterator<CFamilyWar::FamilyScore>::operator!=(&iter_0, &v14) )
        break;
      ++nFamilyIndex;
      nFamilyId = std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter_0)->nFamilyId;
      if ( nFamilyId == Player::getFamilyId(player) )
      {
        v4 = std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter_0)->nScore;
        nFamilyScore = v4 - std::_List_iterator<CFamilyWar::FamilyScore>::operator->(&iter_0)->nUsedScore;
        break;
      }
    }
    ConnId = Player::getConnId(player);
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E24u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      Answer::NetPacket::writeInt8(packet, nIndex);
      Answer::NetPacket::writeInt32(packet, nScore);
      Answer::NetPacket::writeInt8(packet, nFamilyIndex);
      Answer::NetPacket::writeInt32(packet, nFamilyScore);
      Answer::NetPacket::writeInt8(packet, nTaskCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v9 = Player::getConnId(player);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CFamilyWar::broadcastReady(CFamilyWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 2);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CFamilyWar::broadcastStart(CFamilyWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 3);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CFamilyWar::broadcastPillerKilled(CFamilyWar *const this, FamilyId_t nFamilyId)
{
  GameService *v2; // rax
  FamilyManager *v3; // rax
  uint32_t v4; // eax
  GameService *v5; // rax
  GameService *v6; // rax
  uint32_t WOffset; // eax
  GameService *v8; // rax
  FamilyInfo familyInfo; // [rsp+10h] [rbp-90h] BYREF
  Answer::NetPacket *packet; // [rsp+80h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+88h] [rbp-18h]

  if ( nFamilyId <= 0 )
  {
    v6 = Answer::Singleton<GameService>::instance();
    packet_0 = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet_0 )
    {
      Answer::NetPacket::writeInt32(packet_0, 7);
      WOffset = Answer::NetPacket::getWOffset(packet_0);
      Answer::NetPacket::setSize(packet_0, WOffset);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, 0, packet_0);
    }
  }
  else
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 6);
      v3 = Answer::Singleton<FamilyManager>::instance();
      FamilyManager::GetFamilyInfo(&familyInfo, v3, nFamilyId);
      Answer::NetPacket::writeUTF8(packet, &familyInfo.strName);
      v4 = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, v4);
      v5 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v5, 0, packet);
      FamilyInfo::~FamilyInfo(&familyInfo);
    }
  }
}


#####################################
void __cdecl CFamilyWar::broadcastStoneKilled(CFamilyWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 8);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CFamilyWar::addBuff(CFamilyWar *const this, Player *player)
{
  if ( player )
    CActivity::addActivityBuff(this, player, 100001, 1);
}


#####################################
void __cdecl CFamilyWar::removeBuff(CFamilyWar *const this, Player *player)
{
  if ( player )
    Unit::removeBuff(player, 100001);
}


#####################################
bool __cdecl CFamilyWar::OnActivePillar(CFamilyWar *const this, Player *player, int32_t nIndex)
{
  FamilyId_t FamilyId; // rdx
  FamilyId_t v5; // rdx
  char nIndexa; // [rsp+Ch] [rbp-34h]
  CFamilyWar::FamilyScore *pFamilyScore; // [rsp+20h] [rbp-20h]
  int nResult; // [rsp+2Ch] [rbp-14h]

  nIndexa = nIndex;
  if ( !player )
    return 0;
  FamilyId = Player::getFamilyId(player);
  pFamilyScore = CFamilyWar::getFamilyScore(this, FamilyId);
  if ( !pFamilyScore )
    return 0;
  if ( pFamilyScore->nScore - pFamilyScore->nUsedScore <= 999 )
    return 0;
  nResult = this->m_nActivePillarState | (1 << nIndexa);
  if ( this->m_nActivePillarState == nResult )
    return 0;
  pFamilyScore->nUsedScore += 1000;
  ++pFamilyScore->nActivePillar;
  v5 = Player::getFamilyId(player);
  CFamilyWar::sendActivePillarReward(this, v5);
  this->m_nActivePillarState = nResult;
  CActivity::setNeedBroadcastActivityScore(this);
  if ( this->m_nActivePillarState == 15 )
    this->m_nActiveState = 1;
  return 1;
}


#####################################
void __cdecl CFamilyWar::OnTaskSubmited(CFamilyWar *const this, Player *player, int32_t nScore)
{
  CharId_t Cid; // rsi
  int32_t v4; // ebx
  CfgData *v5; // rax
  const CfgActivityTaskTable *ActivityTaskTable; // rax
  int32_t nTaskId; // ebx
  ChrTask *Task; // rax
  FamilyId_t FamilyId; // rbx
  std::string strFamilyName; // [rsp+30h] [rbp-20h] BYREF
  CFamilyWar::PlayerScore *pPlayerScore; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    Cid = Player::getCid(player);
    pPlayerScore = CFamilyWar::getPlayerScore(this, Cid);
    if ( pPlayerScore )
    {
      pPlayerScore->nTaskId = 0;
      ++pPlayerScore->nTaskCount;
      pPlayerScore->nScore += nScore;
      if ( pPlayerScore->nTaskCount == 19 )
      {
        pPlayerScore->nTaskId = 401009;
      }
      else if ( pPlayerScore->nTaskCount <= 19 )
      {
        v4 = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 9))(player);
        v5 = Answer::Singleton<CfgData>::instance();
        ActivityTaskTable = CfgData::GetActivityTaskTable(v5);
        LOBYTE(Cid) = v4;
        pPlayerScore->nTaskId = CfgActivityTaskTable::RandomTask(ActivityTaskTable, v4);
      }
      if ( pPlayerScore->nTaskId > 0 )
      {
        nTaskId = pPlayerScore->nTaskId;
        Task = Player::GetTask(player);
        LOBYTE(Cid) = nTaskId;
        ChrTask::receive(Task, nTaskId);
      }
      std::list<CFamilyWar::PlayerScore>::sort<std::greater<CFamilyWar::PlayerScore>>(
        &this->m_lstPlayerScore,
        (std::greater<CFamilyWar::PlayerScore>)Cid);
      Player::getFamilyName((const Player *const)&strFamilyName);
      FamilyId = Player::getFamilyId(player);
      CFamilyWar::addFamilyScore(this, FamilyId, &strFamilyName, nScore);
      std::string::~string(&strFamilyName);
      (*((void (__fastcall **)(CFamilyWar *const, Player *))this->_vptr_CActivity + 51))(this, player);
    }
  }
}


#####################################
int32_t __cdecl CFamilyWar::GetActivePillar(CFamilyWar *const this, FamilyId_t nFamilyId)
{
  CFamilyWar::FamilyScore *pFamilyScore; // [rsp+18h] [rbp-8h]

  pFamilyScore = CFamilyWar::getFamilyScore(this, nFamilyId);
  if ( pFamilyScore )
    return pFamilyScore->nActivePillar;
  else
    return 0;
}


#####################################
int32_t __cdecl CFamilyWar::canEnter(CFamilyWar *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( !player || !pTargetMap )
    return 10002;
  if ( Player::getFamilyId(player) > 0 )
    return CActivity::canEnter(this, player, pTargetMap);
  return 10102;
}


