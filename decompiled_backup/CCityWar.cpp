// Decompiled methods for class: CCityWar
// Source: gameserver.cc
// Total methods: 43

#####################################
void __cdecl CCityWar::~CCityWar(CCityWar *const this)
{
  CCityWar::~CCityWar(this);
  operator delete(this);
}


#####################################
void __cdecl CCityWar::Init(CCityWar *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  const char *StringValue; // rax
  const char *v4; // rax
  const char *v5; // rax
  FamilyId_t m_nFamilyId; // rbx
  CActivityManager *v7; // rax
  Answer::MySqlQuery *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  std::string *v11; // rax
  const char *v12; // rax
  int *v13; // rbx
  std::string *v14; // rax
  const char *v15; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1120h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-120h] BYREF
  StringVector tv; // [rsp+1040h] [rbp-F0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+1060h] [rbp-D0h] BYREF
  StringVector vStr; // [rsp+1070h] [rbp-C0h] BYREF
  std::string ApplyInfo; // [rsp+1090h] [rbp-A0h] BYREF
  Answer::MySqlQuery result_0; // [rsp+10A0h] [rbp-90h] BYREF
  Answer::MySqlQuery result; // [rsp+10C0h] [rbp-70h] BYREF
  char v24; // [rsp+10DFh] [rbp-51h] BYREF
  std::string delims; // [rsp+10E0h] [rbp-50h] BYREF
  char v26; // [rsp+10EFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+10F0h] [rbp-40h] BYREF
  std::string v28; // [rsp+1100h] [rbp-30h] BYREF
  char v29; // [rsp+1117h] [rbp-19h] BYREF
  __int64 __k[3]; // [rsp+1118h] [rbp-18h] BYREF

  CActivity::Init(this);
  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(&db, "SELECT * FROM `mem_city_war` ORDER BY `index` DESC LIMIT 1");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  this->m_nIndex = 0;
  this->m_nFamilyId = 0;
  this->m_nLastFamilyId = 0;
  this->m_nWinTime = 0;
  this->m_Leader = 0;
  this->m_First = 0;
  this->m_Second = 0;
  this->m_Third = 0;
  std::string::operator=(&this->m_FirstFamilyName, &strNull);
  std::string::operator=(&this->m_SecondFamilyName, &strNull);
  std::string::operator=(&this->m_ThirdFamilyName, &strNull);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_nIndex = Answer::MySqlQuery::getIntValue(&result, "index", 0);
    this->m_nFamilyId = Answer::MySqlQuery::getInt64Value(&result, "familyid", 0);
    this->m_nWinTime = Answer::MySqlQuery::getIntValue(&result, "wintime", 0);
    this->m_Leader = Answer::MySqlQuery::getInt64Value(&result, "leader", 0);
    this->m_First = Answer::MySqlQuery::getInt64Value(&result, "first", 0);
    this->m_Second = Answer::MySqlQuery::getInt64Value(&result, "second", 0);
    this->m_Third = Answer::MySqlQuery::getInt64Value(&result, "third", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "firstfamilyname", &strNull);
    std::string::operator=(&this->m_FirstFamilyName, StringValue);
    v4 = Answer::MySqlQuery::getStringValue(&result, "secondfamilyname", &strNull);
    std::string::operator=(&this->m_SecondFamilyName, v4);
    v5 = Answer::MySqlQuery::getStringValue(&result, "thirdfamilyname", &strNull);
    std::string::operator=(&this->m_ThirdFamilyName, v5);
    this->m_nLastFamilyId = this->m_nFamilyId;
    m_nFamilyId = this->m_nFamilyId;
    v7 = Answer::Singleton<CActivityManager>::instance();
    CActivityManager::SetCityWarWinner(v7, 0, m_nFamilyId);
  }
  memset(szSQL, 0, sizeof(szSQL));
  snprintf(szSQL, 0xFFFu, "SELECT * FROM `mem_city_war_apply` where `index`=%d", this->m_nIndex + 1);
  v8 = Answer::MySqlDBGuard::query(&db, szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_0, v8);
  if ( !Answer::MySqlQuery::eof(&result_0) )
  {
    std::allocator<char>::allocator(&v24);
    v9 = Answer::MySqlQuery::getStringValue(&result_0, "applyinfo", &strNull);
    std::string::string(&ApplyInfo, v9, &v24);
    std::allocator<char>::~allocator(&v24);
    std::allocator<char>::allocator(&v26);
    std::string::string(&delims, "|", &v26);
    Answer::StringUtility::split(&vStr, &ApplyInfo, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v26);
    for ( it._M_current = std::vector<std::string>::begin(&vStr)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v29);
      std::string::string(&v28, ":", &v29);
      v10 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&tv, v10, &v28, 0);
      std::string::~string(&v28);
      std::allocator<char>::~allocator(&v29);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v11 = std::vector<std::string>::operator[](&tv, 0);
        v12 = (const char *)std::string::c_str(v11);
        __k[0] = strtoll(v12, 0, 10);
        v13 = std::map<long,int>::operator[](&this->m_Apply, __k);
        v14 = std::vector<std::string>::operator[](&tv, 1u);
        v15 = (const char *)std::string::c_str(v14);
        *v13 = atoi(v15);
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
    std::string::~string(&ApplyInfo);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_0);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CCityWar::getFamilyMembers(CCityWar *const this, FamilyId_t nFamilyId, CharIdList *const cids)
{
  const std::pair<const long int,CCityWar::PlayerScore> *v3; // rax
  std::_Rb_tree_const_iterator<std::pair<const long int,CCityWar::PlayerScore> > iter; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > __it; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const long int,CCityWar::PlayerScore> > __x; // [rsp+40h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > v8; // [rsp+50h] [rbp-10h] BYREF
  const CCityWar::PlayerScore *score; // [rsp+58h] [rbp-8h]

  __it._M_node = std::map<long,CCityWar::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
  std::_Rb_tree_const_iterator<std::pair<long const,CCityWar::PlayerScore>>::_Rb_tree_const_iterator(&iter, &__it);
  while ( 1 )
  {
    v8._M_node = std::map<long,CCityWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    std::_Rb_tree_const_iterator<std::pair<long const,CCityWar::PlayerScore>>::_Rb_tree_const_iterator(&__x, &v8);
    if ( !std::_Rb_tree_const_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter);
    score = &v3->second;
    if ( v3->second.nFamilyId == nFamilyId && score->bInActivity )
      std::list<long>::push_back(cids, &score->nCharId);
    std::_Rb_tree_const_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator++(&iter);
  }
}


#####################################
void __cdecl CCityWar::OnUpdate(CCityWar *const this, CActivityMap *pMap)
{
  FamilyId_t p_x; // rsi
  GameService *v3; // rax
  int v4; // ebx
  uint32_t WOffset; // eax
  GameService *v6; // rax
  CharIdList cids; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > iter; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > __x; // [rsp+40h] [rbp-30h] BYREF
  int64_t nCurTick; // [rsp+48h] [rbp-28h]
  CCityWar::FamilyScore *score; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
    {
      nCurTick = Map::getTick(pMap);
      if ( nCurTick - this->m_nLastUpdateRankTick > 999 )
      {
        this->m_nLastUpdateRankTick = nCurTick;
        if ( this->m_bUpdateFamilyScroe )
        {
          this->m_bUpdateFamilyScroe = 0;
          std::list<CCityWar::FamilyScore *>::sort<CCityWar::FamilyScoreRankGreater>(
            &this->m_lFamilyScore,
            (CCityWar::FamilyScoreRankGreater)pMap);
          CCityWar::checkChangeFamily(this, 1);
          CActivity::setNeedBroadcastActivityScore(this);
        }
        for ( iter._M_node = std::map<long,CCityWar::FamilyScore>::begin(&this->m_mFamilyScore)._M_node;
              ;
              std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator++(&iter) )
        {
          __x._M_node = std::map<long,CCityWar::FamilyScore>::end(&this->m_mFamilyScore)._M_node;
          p_x = (FamilyId_t)&__x;
          if ( !std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator!=(&iter, &__x) )
            return;
          score = &std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&iter)->second;
          std::list<long>::list(&cids);
          if ( score->bUpdateScroeRank )
          {
            p_x = score->nFamilyId;
            CCityWar::getFamilyMembers(this, score->nFamilyId, &cids);
          }
          if ( score->bUpdateScroeRank )
          {
            score->bUpdateScroeRank = 0;
            std::list<CCityWar::PlayerScore *>::sort<CCityWar::PlayerScoreRankGreater>(
              &score->lScoreRank,
              (CCityWar::PlayerScoreRankGreater)p_x);
            v3 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2E2Au);
            if ( !packet )
            {
              v4 = 0;
              goto LABEL_14;
            }
            CCityWar::appendPlayerRankInfo(this, packet, &score->lScoreRank);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v6 = Answer::Singleton<GameService>::instance();
            GameService::broadcast(v6, packet, &cids);
          }
          v4 = 1;
LABEL_14:
          std::list<long>::~list(&cids);
          if ( !v4 )
            return;
        }
      }
    }
  }
}


#####################################
void __cdecl CCityWar::reset(CCityWar *const this)
{
  this->m_pMonster = 0;
  std::map<long,CCityWar::FamilyScore>::clear(&this->m_mFamilyScore);
  std::map<long,CCityWar::PlayerScore>::clear(&this->m_mPlayerScore);
  std::list<CCityWar::FamilyScore *>::clear(&this->m_lFamilyScore);
  this->m_bUpdateFamilyScroe = 0;
  this->m_nLastUpdateRankTick = 0;
  CActivity::reset(this);
}


#####################################
bool __cdecl CCityWar::isSpecialDay(const CCityWar *const this, int32_t nStartDays)
{
  CfgData *v2; // rax

  v2 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v2) )
  {
    if ( nStartDays == 2 )
      return 1;
  }
  else if ( nStartDays == 2 )
  {
    return 1;
  }
  return 0;
}


#####################################
bool __cdecl CCityWar::isInSpecialDay(const CCityWar *const this, int32_t nStartDays)
{
  CfgData *v2; // rax

  v2 = Answer::Singleton<CfgData>::instance();
  CfgData::isUniteServer(v2);
  return nStartDays <= 2;
}


#####################################
bool __cdecl CCityWar::checkData(CCityWar *const this)
{
  CfgData *v1; // rax
  CfgData *v2; // rax
  CfgData *v3; // rax
  int32_t startDays; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_UNITE);
  }
  else
  {
    v3 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
  }
  if ( CCityWar::isSpecialDay(this, startDays) )
    return 1;
  if ( CCityWar::isInSpecialDay(this, startDays) )
    return 0;
  return CActivity::checkData(this);
}


#####################################
bool __cdecl CCityWar::HaveOwner(CCityWar *const this)
{
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-10h] BYREF
  Player *player; // [rsp+28h] [rbp-8h]

  iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
  eiter._M_node = std::list<Player *>::end(&this->m_players)._M_node;
  while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
  {
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( player )
    {
      if ( Player::getFamilyId(player) == this->m_nFamilyId
        && Unit::isAlive(player)
        && StaticObj::getMapId(player) == 50130 )
      {
        return 1;
      }
    }
    std::_List_iterator<Player *>::operator++(&iter);
  }
  return 0;
}


#####################################
void __cdecl CCityWar::checkChangeFamily(CCityWar *const this, bool IsUpdateScore)
{
  int8_t Camp; // al
  FamilyId_t v6; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > it; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<Player*> eiter; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > __x; // [rsp+40h] [rbp-30h] BYREF
  int8_t WinCamp; // [rsp+4Fh] [rbp-21h]
  FamilyId_t FamilyId; // [rsp+50h] [rbp-20h]
  FamilyId_t FamilyId_0; // [rsp+58h] [rbp-18h]
  Player *player; // [rsp+60h] [rbp-10h]
  FamilyId_t FamilyId_1; // [rsp+68h] [rbp-8h]

  if ( IsUpdateScore )
  {
    it._M_node = std::map<long,CCityWar::FamilyScore>::find(&this->m_mFamilyScore, &this->m_nFamilyId)._M_node;
    __x._M_node = std::map<long,CCityWar::FamilyScore>::end(&this->m_mFamilyScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator!=(&it, &__x)
      && std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&it)->second.nFamilyCamp == 2 )
    {
      FamilyId_0 = CCityWar::GetGuilDerFirstFamily(this);
      if ( FamilyId_0 > 0 && this->m_nFamilyId != FamilyId_0 )
      {
        this->m_nFamilyId = FamilyId_0;
        CCityWar::GongGao(this, FamilyId_0, 337);
        CActivity::setNeedBroadcastActivityScore(this);
      }
    }
    return;
  }
  WinCamp = 0;
  FamilyId = 0;
  iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
  eiter._M_node = std::list<Player *>::end(&this->m_players)._M_node;
  while ( 1 )
  {
    if ( !std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
    {
      if ( WinCamp > 0 )
      {
        if ( WinCamp == 2 )
        {
          FamilyId_1 = CCityWar::GetGuilDerFirstFamily(this);
          if ( FamilyId_1 > 0 && this->m_nFamilyId != FamilyId_1 )
          {
            this->m_nFamilyId = FamilyId_1;
            CCityWar::GongGao(this, FamilyId_1, 337);
            CCityWar::SetOwner(this);
            CActivity::setNeedBroadcastActivityScore(this);
          }
        }
        else if ( (WinCamp == 3 || WinCamp == 1) && this->m_nFamilyId != FamilyId )
        {
          this->m_nFamilyId = FamilyId;
          CCityWar::GongGao(this, FamilyId, 337);
          CCityWar::SetOwner(this);
          CActivity::setNeedBroadcastActivityScore(this);
        }
      }
      return;
    }
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( !player || !Unit::isAlive(player) || StaticObj::getMapId(player) != 50130 )
      goto LABEL_39;
    if ( Player::GetCamp(player) <= 0 || Player::GetCamp(player) == 4 )
      return;
    if ( WinCamp )
    {
      Camp = Player::GetCamp(player);
      if ( Camp != WinCamp )
        break;
    }
    if ( WinCamp == 3 )
    {
      v6 = Player::getFamilyId(player);
      if ( v6 != FamilyId )
      {
        if ( !CCityWar::HaveOwner(this) && this->m_nFamilyId > 0 )
          goto LABEL_26;
        return;
      }
    }
    WinCamp = Player::GetCamp(player);
    FamilyId = Player::getFamilyId(player);
LABEL_39:
    std::_List_iterator<Player *>::operator++(&iter);
  }
  if ( !CCityWar::HaveOwner(this) && this->m_nFamilyId > 0 )
  {
LABEL_26:
    this->m_nFamilyId = 0;
    CCityWar::NotOccupyGongGao(this);
    CCityWar::SetOwner(this);
    CActivity::setNeedBroadcastActivityScore(this);
  }
}


#####################################
void __cdecl CCityWar::NotOccupyGongGao(CCityWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 342);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
  }
}


#####################################
void __cdecl CCityWar::SetOwner(CCityWar *const this)
{
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-10h] BYREF
  Player *player; // [rsp+28h] [rbp-8h]

  iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
  eiter._M_node = std::list<Player *>::end(&this->m_players)._M_node;
  while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
  {
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( player )
    {
      if ( Player::getFamilyId(player) == this->m_nFamilyId )
      {
        Player::SetActState(player, 1);
      }
      else if ( Player::GetActState(player) )
      {
        Player::SetActState(player, 0);
      }
    }
    std::_List_iterator<Player *>::operator++(&iter);
  }
}


#####################################
bool __cdecl CCityWar::checkWeek(CCityWar *const this)
{
  CfgData *v1; // rax
  CfgData *v2; // rax
  CfgData *v3; // rax
  int32_t startDays; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_UNITE);
  }
  else
  {
    v3 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
  }
  if ( CCityWar::isSpecialDay(this, startDays) )
    return 1;
  if ( CCityWar::isInSpecialDay(this, startDays) )
    return 0;
  return CActivity::checkWeek(this);
}


#####################################
void __cdecl CCityWar::onMonsterDie(CCityWar *const this, MonsterActivity *pMonster, Player *pKiller)
{
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v6; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( pMonster && pKiller && CActivity::IsRuning(this) )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 336);
      Cid = Player::getCid(pKiller);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v6, packet);
    }
  }
}


#####################################
void __cdecl CCityWar::onPlayerKilled(CCityWar *const this, Player *pDier, Player *pAttacker)
{
  int FamilyPosition; // eax
  int32_t Now; // r12d
  FamilyId_t FamilyId; // rbx
  GameService *v7; // rax
  CharId_t Cid; // rax
  int32_t MapId; // eax
  CharId_t v10; // rax
  uint32_t WOffset; // eax
  GameService *v12; // rax
  std::string val; // [rsp+20h] [rbp-40h] BYREF
  std::string v15; // [rsp+30h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+40h] [rbp-20h]
  int32_t Socre; // [rsp+4Ch] [rbp-14h]

  if ( pDier && pAttacker )
  {
    if ( Player::GetCamp(pDier) != 4 && Player::GetCamp(pAttacker) != 4 )
    {
      Socre = 0;
      FamilyPosition = Player::getFamilyPosition(pDier);
      if ( (char)FamilyPosition == 2 )
      {
        Socre = 200;
      }
      else if ( FamilyPosition == 3 )
      {
        Socre = 200;
      }
      else if ( FamilyPosition == 1 )
      {
        Socre = 150;
      }
      else
      {
        Socre = 100;
      }
      Now = Unit::getNow(pAttacker);
      FamilyId = Player::getFamilyId(pAttacker);
      CCityWar::addFamilyScore(this, FamilyId, Socre, Now);
      CCityWar::addPlayerScore(this, pAttacker, Socre);
    }
    if ( StaticObj::getMapId(pDier) == 50130 )
      CCityWar::checkChangeFamily(this, 0);
    v7 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v7, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 341);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(pAttacker);
      Answer::NetPacket::writeInt64(packet, Cid);
      MapId = StaticObj::getMapId(pAttacker);
      Answer::NetPacket::writeInt32(packet, MapId);
      Player::getName((const Player *const)&v15);
      Answer::NetPacket::writeUTF8(packet, &v15);
      std::string::~string(&v15);
      v10 = Player::getCid(pDier);
      Answer::NetPacket::writeInt64(packet, v10);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v12, packet);
    }
  }
}


#####################################
void __cdecl CCityWar::onMonsterAdd(CCityWar *const this, MonsterActivity *pMonster)
{
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v3; // rax
  FamilyInfo info; // [rsp+10h] [rbp-90h] BYREF
  std::string p_strFamilyName; // [rsp+80h] [rbp-20h] BYREF

  if ( pMonster )
  {
    m_nFamilyId = this->m_nFamilyId;
    v3 = Answer::Singleton<FamilyManager>::instance();
    FamilyManager::GetFamilyInfo(&info, v3, m_nFamilyId);
    std::string::string(&p_strFamilyName, &info.FamilyLeaderName);
    Monster::SetFamilyId(pMonster, this->m_nFamilyId, &p_strFamilyName);
    std::string::~string(&p_strFamilyName);
    this->m_pMonster = pMonster;
    FamilyInfo::~FamilyInfo(&info);
  }
}


#####################################
int8_t __cdecl CCityWar::GetFamilyCamp(CCityWar *const this, FamilyId_t FamilyId)
{
  FamilyId_t FamilyIda; // [rsp+0h] [rbp-30h] BYREF
  CCityWar *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  FamilyIda = FamilyId;
  if ( FamilyId <= 0 )
    return 4;
  if ( thisa->m_nLastFamilyId == FamilyIda )
    return 1;
  it._M_node = std::map<long,int>::find(&thisa->m_Apply, &FamilyIda)._M_node;
  __x._M_node = std::map<long,int>::end(&thisa->m_Apply)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&it, &__x) )
    return 4;
  if ( std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it)->second == 1 )
    return 2;
  return 3;
}


#####################################
void __cdecl CCityWar::addPlayer(CCityWar *const this, Player *player)
{
  FamilyId_t FamilyId; // rdx
  int8_t FamilyCamp; // dl
  std::pair<const long int,CCityWar::PlayerScore> *v4; // rbx
  std::pair<const long int,CCityWar::FamilyScore> *v5; // rax
  CCityWar::PlayerScore score; // [rsp+20h] [rbp-1A0h] BYREF
  CCityWar::FamilyScore family; // [rsp+60h] [rbp-160h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > familyIter; // [rsp+90h] [rbp-130h] BYREF
  CCityWar::PlayerScore *pScore; // [rsp+98h] [rbp-128h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > iter; // [rsp+A0h] [rbp-120h] BYREF
  __int64 __x; // [rsp+A8h] [rbp-118h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > v12; // [rsp+B0h] [rbp-110h] BYREF
  _BYTE v13[16]; // [rsp+C0h] [rbp-100h] BYREF
  _BYTE v14[16]; // [rsp+D0h] [rbp-F0h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> >,bool> v15; // [rsp+E0h] [rbp-E0h]
  std::pair<const long int,CCityWar::PlayerScore> v16; // [rsp+F0h] [rbp-D0h] BYREF
  __int64 v17; // [rsp+138h] [rbp-88h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > v18; // [rsp+140h] [rbp-80h] BYREF
  _BYTE v19[16]; // [rsp+150h] [rbp-70h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> >,bool> v20; // [rsp+160h] [rbp-60h]
  std::pair<const long int,CCityWar::FamilyScore> v21; // [rsp+170h] [rbp-50h] BYREF
  CCityWar::FamilyScore *p_second; // [rsp+1A8h] [rbp-18h] BYREF

  if ( player )
  {
    FamilyId = Player::getFamilyId(player);
    FamilyCamp = CCityWar::GetFamilyCamp(this, FamilyId);
    Player::SetCamp(player, FamilyCamp);
    if ( Player::getFamilyId(player) > 0 )
    {
      if ( Player::GetCamp(player) == 2 )
        Player::setPkMode(player, 7, 0);
      else
        Player::setPkMode(player, 3, 0);
    }
    else
    {
      Player::setPkMode(player, 6, 0);
    }
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCityWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v12._M_node = std::map<long,CCityWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator!=(&iter, &v12) )
    {
      std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter)->second.bInActivity = 1;
      v4 = std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter);
      v4->second.nTime = Unit::getNow(player);
    }
    else
    {
      memset(&score, 0, 60);
      std::string::string(&score.strName);
      std::string::string(&score.strFamilyName);
      score.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v13);
      std::string::operator=(&score.strName, v13);
      std::string::~string(v13);
      score.nFamilyId = Player::getFamilyId(player);
      Player::getFamilyName((const Player *const)v14);
      std::string::operator=(&score.strFamilyName, v14);
      std::string::~string(v14);
      score.bInActivity = 1;
      score.nFamilyPosition = Player::getFamilyPosition(player);
      score.nTime = Unit::getNow(player);
      std::pair<long const,CCityWar::PlayerScore>::pair(&v16, &score.nCharId, &score);
      v15 = std::map<long,CCityWar::PlayerScore>::insert(&this->m_mPlayerScore, &v16);
      iter._M_node = v15.first._M_node;
      std::pair<long const,CCityWar::PlayerScore>::~pair(&v16);
      pScore = &std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter)->second;
      if ( Player::getFamilyId(player) > 0 )
      {
        v17 = Player::getFamilyId(player);
        familyIter._M_node = std::map<long,CCityWar::FamilyScore>::find(&this->m_mFamilyScore, &v17)._M_node;
        v18._M_node = std::map<long,CCityWar::FamilyScore>::end(&this->m_mFamilyScore)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator!=(&familyIter, &v18) )
        {
          v5 = std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&familyIter);
          std::list<CCityWar::PlayerScore *>::push_back(&v5->second.lScoreRank, &pScore);
        }
        else
        {
          memset(&family, 0, sizeof(family));
          std::string::string(&family.strFamilyName);
          std::list<CCityWar::PlayerScore *>::list(&family.lScoreRank);
          family.nFamilyId = Player::getFamilyId(player);
          Player::getFamilyName((const Player *const)v19);
          std::string::operator=(&family.strFamilyName, v19);
          std::string::~string(v19);
          family.nFamilyCamp = Player::GetCamp(player);
          std::list<CCityWar::PlayerScore *>::push_back(&family.lScoreRank, &pScore);
          std::pair<long const,CCityWar::FamilyScore>::pair(&v21, &family.nFamilyId, &family);
          v20 = std::map<long,CCityWar::FamilyScore>::insert(&this->m_mFamilyScore, &v21);
          familyIter._M_node = v20.first._M_node;
          std::pair<long const,CCityWar::FamilyScore>::~pair(&v21);
          p_second = &std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&familyIter)->second;
          std::list<CCityWar::FamilyScore *>::push_back(&this->m_lFamilyScore, &p_second);
          CCityWar::FamilyScore::~FamilyScore(&family);
        }
      }
      CCityWar::PlayerScore::~PlayerScore(&score);
    }
    if ( Player::getFamilyId(player) == this->m_nFamilyId )
      Player::SetActState(player, 1);
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CCityWar::removePlayer(CCityWar *const this, Player *player, bool islogout)
{
  std::pair<const long int,CCityWar::PlayerScore> *v3; // rbx
  int32_t nSeconds; // r13d
  int32_t Now; // r12d
  int8_t ConnId; // bl
  CActivityManager *v7; // rax
  FamilyId_t FamilyId; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > iter; // [rsp+20h] [rbp-50h] BYREF
  __int64 __x; // [rsp+28h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > v13; // [rsp+30h] [rbp-40h] BYREF
  bool bChange; // [rsp+47h] [rbp-29h]
  FamilyId_t winFamily; // [rsp+48h] [rbp-28h]

  if ( player )
  {
    Player::SetCamp(player, 0);
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCityWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v13._M_node = std::map<long,CCityWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator!=(&iter, &v13) )
    {
      std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter)->second.bInActivity = 0;
      v3 = std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter);
      nSeconds = v3->second.nSeconds;
      Now = Unit::getNow(player);
      v3->second.nSeconds = nSeconds
                          + Now
                          - std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter)->second.nTime;
    }
    CActivity::removePlayer(this, player, islogout);
    bChange = 0;
    if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
      CCityWar::checkChangeFamily(this, 0);
    ConnId = Player::getConnId(player);
    v7 = Answer::Singleton<CActivityManager>::instance();
    winFamily = CActivityManager::GetCityWarWinner(v7, ConnId);
    if ( winFamily > 0 && (FamilyId = Player::getFamilyId(player), FamilyId == winFamily) )
    {
      Player::SetActState(player, 1);
    }
    else if ( Player::GetActState(player) )
    {
      Player::SetActState(player, 0);
    }
  }
}


#####################################
bool __cdecl CCityWar::canGetOnlineReward(CCityWar *const this, const CCityWar::PlayerScore *const score)
{
  CTimer *v2; // rax
  int32_t nOnlineTime; // [rsp+1Ch] [rbp-4h]

  nOnlineTime = score->nSeconds;
  if ( score->bInActivity )
  {
    v2 = Answer::Singleton<CTimer>::instance();
    nOnlineTime += CTimer::GetNow(v2) - score->nTime;
  }
  return nOnlineTime > 299;
}


#####################################
void __cdecl CCityWar::SendPlayerActivityInfo(CCityWar *const this, Player *player)
{
  int8_t v2; // bl
  GameService *v3; // rax
  int32_t v4; // edx
  int32_t v5; // edx
  uint32_t v6; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  int8_t ConnId; // bl
  GameService *v10; // rax
  int32_t v11; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v14; // bl
  GameService *v15; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    if ( this->m_nLastFamilyId <= 0 )
    {
      ConnId = Player::getConnId(player);
      v10 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v10, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E22u);
      if ( !packet_0 )
        return;
      Answer::NetPacket::writeInt32(packet_0, this->m_cfgActivity->id);
      v11 = (*((__int64 (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 42))(this);
      Answer::NetPacket::writeInt32(packet_0, v11);
      Answer::NetPacket::writeInt32(packet_0, 0);
      Answer::NetPacket::writeInt64(packet_0, this->m_nLastFamilyId);
      Answer::NetPacket::writeUTF8(packet_0, &this->m_FirstFamilyName);
      Answer::NetPacket::writeUTF8(packet_0, &this->m_SecondFamilyName);
      Answer::NetPacket::writeUTF8(packet_0, &this->m_ThirdFamilyName);
      WOffset = Answer::NetPacket::getWOffset(packet_0);
      Answer::NetPacket::setSize(packet_0, WOffset);
      GateIndex = Player::getGateIndex(player);
      v14 = Player::getConnId(player);
      v15 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v15, v14, GateIndex, packet_0);
    }
    else
    {
      v2 = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, v2, Answer::PackType::PACK_DISPATCH, 0x4EADu);
      if ( !packet )
        return;
      v4 = Player::getGateIndex(player);
      Answer::NetPacket::writeInt32(packet, v4);
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      v5 = (*((__int64 (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 42))(this);
      Answer::NetPacket::writeInt32(packet, v5);
      Answer::NetPacket::writeInt64(packet, this->m_nLastFamilyId);
      Answer::NetPacket::writeInt32(packet, this->m_nWinTime);
      Answer::NetPacket::writeInt64(packet, this->m_First);
      Answer::NetPacket::writeInt64(packet, this->m_Second);
      Answer::NetPacket::writeInt64(packet, this->m_Third);
      Answer::NetPacket::writeUTF8(packet, &this->m_FirstFamilyName);
      Answer::NetPacket::writeUTF8(packet, &this->m_SecondFamilyName);
      Answer::NetPacket::writeUTF8(packet, &this->m_ThirdFamilyName);
      v6 = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, v6);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v8, v7, packet);
    }
    CCityWar::SendAppyCityWarInfo(this, player);
  }
}


#####################################
void __cdecl CCityWar::SendPlayerActivityScore(CCityWar *const this, Player *player)
{
  __int64 (__fastcall *v2)(CCityWar *const, _QWORD); // rbx
  unsigned int ConnId; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  GameService *v7; // rax
  CCityWar::FamilyScore::PlayerScoreRank *p_lScoreRank; // rdx
  uint32_t WOffset; // eax
  int16_t v10; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  __int64 __x; // [rsp+18h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > v15; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *familyPacket; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    v2 = (__int64 (__fastcall *)(CCityWar *const, _QWORD))*((_QWORD *)this->_vptr_CActivity + 52);
    ConnId = Player::getConnId(player);
    familyPacket = (Answer::NetPacket *)v2(this, ConnId);
    if ( familyPacket )
    {
      GateIndex = Player::getGateIndex(player);
      v5 = Player::getConnId(player);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, familyPacket);
    }
    __x = Player::getFamilyId(player);
    iter._M_node = std::map<long,CCityWar::FamilyScore>::find(&this->m_mFamilyScore, &__x)._M_node;
    v15._M_node = std::map<long,CCityWar::FamilyScore>::end(&this->m_mFamilyScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator!=(&iter, &v15) )
    {
      v7 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v7, Answer::PackType::PACK_DISPATCH, 0x2E2Au);
      if ( packet )
      {
        p_lScoreRank = &std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&iter)->second.lScoreRank;
        CCityWar::appendPlayerRankInfo(this, packet, p_lScoreRank);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v10 = Player::getGateIndex(player);
        v11 = Player::getConnId(player);
        v12 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v12, v11, v10, packet);
      }
    }
  }
}


#####################################
int32_t __cdecl CCityWar::GetRevive(CCityWar *const this, Player *player)
{
  Answer::Random *v4; // rax
  int v5; // eax
  Answer::Random *v6; // rax
  int v7; // eax
  int32_t lenth; // [rsp+18h] [rbp-18h]
  int32_t lenth_0; // [rsp+1Ch] [rbp-14h]

  if ( !player )
    return CActivity::GetRevive(this, 0);
  if ( this->m_nFamilyId > 0 && Player::getFamilyId(player) == this->m_nFamilyId )
  {
    lenth = std::vector<int>::size(&this->m_cfgActivity->target_regionb);
    if ( lenth == 1 )
    {
      return *std::vector<int>::operator[](&this->m_cfgActivity->target_regionb, 0);
    }
    else
    {
      v4 = Answer::Singleton<Answer::Random>::instance();
      v5 = Answer::Random::generate(v4, 0, lenth - 1);
      return *std::vector<int>::operator[](&this->m_cfgActivity->target_regionb, v5);
    }
  }
  else
  {
    lenth_0 = std::vector<int>::size(&this->m_cfgActivity->target_regiona);
    if ( lenth_0 == 1 )
    {
      return *std::vector<int>::operator[](&this->m_cfgActivity->target_regiona, 0);
    }
    else
    {
      v6 = Answer::Singleton<Answer::Random>::instance();
      v7 = Answer::Random::generate(v6, 0, lenth_0 - 1);
      return *std::vector<int>::operator[](&this->m_cfgActivity->target_regiona, v7);
    }
  }
}


#####################################
void __cdecl CCityWar::addPlayerScore(CCityWar *const this, Player *player, int32_t nScore)
{
  std::pair<const long int,CCityWar::PlayerScore> *v3; // rax
  std::pair<const long int,CCityWar::PlayerScore> *v4; // rbx
  FamilyId_t FamilyId; // rcx
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > iter; // [rsp+20h] [rbp-30h] BYREF
  __int64 __x; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > v9; // [rsp+30h] [rbp-20h] BYREF

  if ( player )
  {
    __x = Player::getCid(player);
    iter._M_node = std::map<long,CCityWar::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v9._M_node = std::map<long,CCityWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator!=(&iter, &v9) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter);
      v3->second.nScore += nScore;
      v4 = std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&iter);
      v4->second.nScoreTime = Unit::getNow(player);
      FamilyId = Player::getFamilyId(player);
      CCityWar::setUpdateScoreRank(this, FamilyId, nScore > 0);
    }
  }
}


#####################################
void __cdecl CCityWar::setUpdateScoreRank(CCityWar *const this, FamilyId_t nFamilyId, bool bScoreRank)
{
  FamilyId_t nFamilyIda; // [rsp+10h] [rbp-30h] BYREF
  CCityWar *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > __x; // [rsp+30h] [rbp-10h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  iter._M_node = std::map<long,CCityWar::FamilyScore>::find(&this->m_mFamilyScore, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,CCityWar::FamilyScore>::end(&thisa->m_mFamilyScore)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator!=(&iter, &__x) && bScoreRank )
    std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&iter)->second.bUpdateScroeRank = 1;
}


#####################################
void __cdecl CCityWar::addFamilyScore(CCityWar *const this, FamilyId_t nFamilyId, int32_t nScore, int32_t nNowTime)
{
  std::pair<const long int,CCityWar::FamilyScore> *v4; // rax
  FamilyId_t nFamilyIda; // [rsp+10h] [rbp-30h] BYREF
  CCityWar *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::FamilyScore> > __x; // [rsp+30h] [rbp-10h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  iter._M_node = std::map<long,CCityWar::FamilyScore>::find(&this->m_mFamilyScore, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,CCityWar::FamilyScore>::end(&thisa->m_mFamilyScore)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator!=(&iter, &__x) )
  {
    v4 = std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&iter);
    v4->second.nScore += nScore;
    std::_Rb_tree_iterator<std::pair<long const,CCityWar::FamilyScore>>::operator->(&iter)->second.nScoreTime = nNowTime;
    thisa->m_bUpdateFamilyScroe = 1;
    CActivity::setNeedBroadcastActivityScore(thisa);
  }
}


#####################################
void __cdecl CCityWar::win(CCityWar *const this)
{
  FamilyId_t m_nFamilyId; // r12
  FamilyId_t m_nLastFamilyId; // rbx
  GameService *v3; // rax
  FamilyId_t v4; // rbx
  CActivityManager *v5; // rax
  FamilyId_t v6; // rbx
  GameService *v7; // rax
  FamilyId_t v8; // rbx
  FamilyManager *v9; // rsi
  int v10; // ebx
  CfgData *v11; // rax
  CharId_t FamilyLeaderCid; // rbx
  DBService *v13; // rax
  CharId_t v14; // rbx
  DBService *v15; // rax
  GameService *v16; // rax
  uint32_t WOffset; // eax
  GameService *v18; // rax
  GameService *v19; // rax
  uint32_t v20; // eax
  GameService *v21; // rax
  GameService *v22; // rax
  uint32_t v23; // eax
  GameService *v24; // rax
  GameService *v25; // rax
  FamilyInfo info; // [rsp+10h] [rbp-C0h] BYREF
  std::string Param; // [rsp+80h] [rbp-50h] BYREF
  char v28; // [rsp+8Fh] [rbp-41h] BYREF
  std::string v29; // [rsp+90h] [rbp-40h] BYREF
  char v30; // [rsp+A7h] [rbp-29h] BYREF
  Answer::NetPacket *packet; // [rsp+A8h] [rbp-28h]
  Answer::NetPacket *packet_0; // [rsp+B0h] [rbp-20h]
  Answer::NetPacket *packet_1; // [rsp+B8h] [rbp-18h]

  if ( this->m_nFamilyId != this->m_nLastFamilyId )
  {
    this->m_nWinTime = Answer::DayTime::now();
    m_nFamilyId = this->m_nFamilyId;
    m_nLastFamilyId = this->m_nLastFamilyId;
    v3 = Answer::Singleton<GameService>::instance();
    GameService::UpdateCityWarTitle(v3, m_nLastFamilyId, m_nFamilyId);
    this->m_nLastFamilyId = this->m_nFamilyId;
  }
  v4 = this->m_nFamilyId;
  v5 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SetCityWarWinner(v5, 0, v4);
  if ( this->m_nFamilyId > 0 )
  {
    v6 = this->m_nFamilyId;
    v7 = Answer::Singleton<GameService>::instance();
    GameService::UpdateCityActState(v7, v6, 1);
    v8 = this->m_nFamilyId;
    v9 = Answer::Singleton<FamilyManager>::instance();
    FamilyManager::GetFamilyInfo(&info, v9, v8);
    if ( FamilyInfo::IsEmpty(&info) )
    {
      v10 = 0;
      goto LABEL_15;
    }
    if ( this->m_nIndex == 1 )
    {
      v11 = Answer::Singleton<CfgData>::instance();
      if ( CfgData::isUniteServer(v11) )
      {
        std::allocator<char>::allocator(&v28);
        std::string::string(&Param, &strNull, &v28);
        FamilyLeaderCid = info.FamilyLeaderCid;
        v13 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(v13, 0, FamilyLeaderCid, 6397, &Param, 0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(&v28);
      }
      else
      {
        std::allocator<char>::allocator(&v30);
        std::string::string(&v29, &strNull, &v30);
        v14 = info.FamilyLeaderCid;
        v15 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(v15, 0, v14, 6371, &v29, 0);
        std::string::~string(&v29);
        std::allocator<char>::~allocator(&v30);
        v16 = Answer::Singleton<GameService>::instance();
        packet_0 = GameService::popNetpacket(v16, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet_0 )
        {
          v10 = 0;
          goto LABEL_15;
        }
        Answer::NetPacket::writeInt32(packet_0, 442);
        Answer::NetPacket::writeInt64(packet_0, info.FamilyLeaderCid);
        Answer::NetPacket::writeUTF8(packet_0, &info.FamilyLeaderName);
        WOffset = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, WOffset);
        v18 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v18, packet_0);
      }
    }
    v19 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v19, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 338);
      Answer::NetPacket::writeUTF8(packet, &info.strName);
      v20 = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, v20);
      v21 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v21, packet);
      v10 = 1;
    }
    else
    {
      v10 = 0;
    }
LABEL_15:
    FamilyInfo::~FamilyInfo(&info);
    if ( !v10 )
      return;
    goto LABEL_19;
  }
  v22 = Answer::Singleton<GameService>::instance();
  packet_1 = GameService::popNetpacket(v22, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( !packet_1 )
    return;
  Answer::NetPacket::writeInt32(packet_1, 339);
  v23 = Answer::NetPacket::getWOffset(packet_1);
  Answer::NetPacket::setSize(packet_1, v23);
  v24 = Answer::Singleton<GameService>::instance();
  GameService::worldBroadcast(v24, packet_1);
LABEL_19:
  this->m_nState = ACTIVITY_STATE::AS_END;
  CCityWar::addRewards(this);
  CCityWar::saveResult(this);
  (*((void (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 43))(this);
  (*((void (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 10))(this);
  CActivity::delayKickAll(this, 30);
  (*((void (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 55))(this);
  v25 = Answer::Singleton<GameService>::instance();
  GameService::broadFamilyWarIcon(v25);
}


#####################################
void __cdecl CCityWar::addRewards(CCityWar *const this)
{
  CfgData *v1; // rax
  const CfgCityWarTable *CityWarTable; // rax
  CCityWar::PlayerScore *p_second; // rdx
  MemChrBagVector *p_vBreakReward; // r13
  int32_t nBreakMailId; // r12d
  CharId_t nCharId; // rbx
  DBService *v7; // rax
  bool v8; // al
  CCityWar::FamilyScore **v9; // rax
  CCityWar::FamilyScore **v10; // rax
  CfgData *v11; // rax
  const CfgCityWarTable *v12; // rax
  CCityWar::FamilyScore **v13; // rax
  const MemChrBag *v15; // r13
  int32_t v16; // r12d
  CharId_t v17; // rbx
  DBService *v18; // rax
  CCityWar::FamilyScore **v19; // rax
  std::_List_iterator<CCityWar::PlayerScore*> PlayerIt; // [rsp+20h] [rbp-D0h] BYREF
  std::_List_iterator<CCityWar::FamilyScore*> it; // [rsp+30h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > itTmp; // [rsp+40h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CCityWar::PlayerScore> > __x; // [rsp+50h] [rbp-A0h] BYREF
  std::string Param; // [rsp+60h] [rbp-90h] BYREF
  char v25; // [rsp+6Fh] [rbp-81h] BYREF
  std::_List_iterator<CCityWar::FamilyScore*> v26; // [rsp+70h] [rbp-80h] BYREF
  std::_List_iterator<CCityWar::PlayerScore*> v27; // [rsp+80h] [rbp-70h] BYREF
  std::string v28; // [rsp+90h] [rbp-60h] BYREF
  char v29; // [rsp+A7h] [rbp-49h] BYREF
  const CfgCityWarContReward *JoinReward; // [rsp+A8h] [rbp-48h]
  int32_t OtherFamilyIndex; // [rsp+B0h] [rbp-40h]
  int32_t FamilyIndex; // [rsp+B4h] [rbp-3Ch]
  int32_t OtherPlayerIndex; // [rsp+B8h] [rbp-38h]
  int32_t PlayerIndex; // [rsp+BCh] [rbp-34h]
  const CfgCityWarContReward *pCfgContReward; // [rsp+C0h] [rbp-30h]
  int32_t RewardIndex; // [rsp+CCh] [rbp-24h]

  v1 = Answer::Singleton<CfgData>::instance();
  CityWarTable = CfgData::GetCityWarTable(v1);
  JoinReward = CfgCityWarTable::GetContReward(CityWarTable, 4);
  if ( JoinReward )
  {
    for ( itTmp._M_node = std::map<long,CCityWar::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator++(&itTmp, 0) )
    {
      __x._M_node = std::map<long,CCityWar::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator!=(&itTmp, &__x) )
        break;
      p_second = &std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&itTmp)->second;
      if ( CCityWar::canGetOnlineReward(this, p_second) )
      {
        std::allocator<char>::allocator(&v25);
        std::string::string(&Param, &strNull, &v25);
        p_vBreakReward = &JoinReward->vBreakReward;
        nBreakMailId = JoinReward->nBreakMailId;
        nCharId = std::_Rb_tree_iterator<std::pair<long const,CCityWar::PlayerScore>>::operator->(&itTmp)->second.nCharId;
        v7 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(
          v7,
          0,
          nCharId,
          nBreakMailId,
          p_vBreakReward,
          ITEM_CHANGE_REASON::ICR_CITY_WAR_REWARD,
          &Param,
          0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(&v25);
      }
    }
    OtherFamilyIndex = 2;
    FamilyIndex = 0;
    for ( it._M_node = std::list<CCityWar::FamilyScore *>::begin(&this->m_lFamilyScore)._M_node;
          ;
          std::_List_iterator<CCityWar::FamilyScore *>::operator++(&it, 0) )
    {
      v26._M_node = std::list<CCityWar::FamilyScore *>::end(&this->m_lFamilyScore)._M_node;
      if ( !std::_List_iterator<CCityWar::FamilyScore *>::operator!=(&it, &v26) )
        break;
      if ( (*std::_List_iterator<CCityWar::FamilyScore *>::operator*(&it))->nFamilyId == this->m_nFamilyId )
        FamilyIndex = 1;
      else
        FamilyIndex = OtherFamilyIndex++;
      v8 = FamilyIndex > 3
        || (*std::_List_iterator<CCityWar::FamilyScore *>::operator*(&it))->nScore <= 0 && FamilyIndex != 1;
      if ( !v8 && FamilyIndex <= 3 )
      {
        if ( FamilyIndex == 2 )
        {
          v9 = std::_List_iterator<CCityWar::FamilyScore *>::operator*(&it);
          std::string::operator=(&this->m_FirstFamilyName, &(*v9)->strFamilyName);
        }
        else if ( FamilyIndex == 3 )
        {
          v10 = std::_List_iterator<CCityWar::FamilyScore *>::operator*(&it);
          std::string::operator=(&this->m_SecondFamilyName, &(*v10)->strFamilyName);
        }
        OtherPlayerIndex = 2;
        PlayerIndex = 0;
        v11 = Answer::Singleton<CfgData>::instance();
        v12 = CfgData::GetCityWarTable(v11);
        pCfgContReward = CfgCityWarTable::GetContReward(v12, FamilyIndex);
        if ( pCfgContReward )
        {
          v13 = std::_List_iterator<CCityWar::FamilyScore *>::operator*(&it);
          for ( PlayerIt._M_node = std::list<CCityWar::PlayerScore *>::begin(&(*v13)->lScoreRank)._M_node;
                ;
                std::_List_iterator<CCityWar::PlayerScore *>::operator++(&PlayerIt, 0) )
          {
            v19 = std::_List_iterator<CCityWar::FamilyScore *>::operator*(&it);
            v27._M_node = std::list<CCityWar::PlayerScore *>::end(&(*v19)->lScoreRank)._M_node;
            if ( !std::_List_iterator<CCityWar::PlayerScore *>::operator!=(&PlayerIt, &v27) )
              break;
            if ( (*std::_List_iterator<CCityWar::PlayerScore *>::operator*(&PlayerIt))->nFamilyPosition == 3 )
              PlayerIndex = 1;
            else
              PlayerIndex = OtherPlayerIndex++;
            if ( PlayerIndex <= 6
              && ((*std::_List_iterator<CCityWar::PlayerScore *>::operator*(&PlayerIt))->nScore > 0 || PlayerIndex == 1) )
            {
              RewardIndex = 0;
              switch ( PlayerIndex )
              {
                case 1:
                  RewardIndex = 1;
                  break;
                case 2:
                  if ( FamilyIndex == 1 )
                    this->m_First = (*std::_List_iterator<CCityWar::PlayerScore *>::operator*(&PlayerIt))->nCharId;
                  RewardIndex = 2;
                  break;
                case 3:
                  if ( FamilyIndex == 1 )
                    this->m_Second = (*std::_List_iterator<CCityWar::PlayerScore *>::operator*(&PlayerIt))->nCharId;
                  RewardIndex = 3;
                  break;
                case 4:
                  if ( FamilyIndex == 1 )
                    this->m_Third = (*std::_List_iterator<CCityWar::PlayerScore *>::operator*(&PlayerIt))->nCharId;
                  RewardIndex = 3;
                  break;
                case 5:
                case 6:
                  RewardIndex = 4;
                  break;
                default:
                  break;
              }
              if ( RewardIndex > 0 )
              {
                std::allocator<char>::allocator(&v29);
                std::string::string(&v28, &strNull, &v29);
                v15 = std::vector<MemChrBag>::operator[](&pCfgContReward->vBreakReward, RewardIndex - 1);
                v16 = pCfgContReward->nBreakMailId;
                v17 = (*std::_List_iterator<CCityWar::PlayerScore *>::operator*(&PlayerIt))->nCharId;
                v18 = Answer::Singleton<DBService>::instance();
                DBService::OnSendSysMail(v18, 0, v17, v16, v15, ITEM_CHANGE_REASON::ICR_CITY_WAR_REWARD, &v28, 0);
                std::string::~string(&v28);
                std::allocator<char>::~allocator(&v29);
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CCityWar::saveResult(CCityWar *const this)
{
  CharId_t Second; // r15
  CharId_t First; // r14
  int32_t m_nWinTime; // r13d
  FamilyId_t m_nFamilyId; // r12
  int32_t Id; // ebx
  DBService *v6; // rax
  int32_t nIndex; // [rsp+4Ch] [rbp-84h]
  CharId_t Third; // [rsp+50h] [rbp-80h]
  CharId_t nLeaderCid; // [rsp+58h] [rbp-78h]
  int32_t nTime; // [rsp+64h] [rbp-6Ch]
  std::string p_ThirdFamilyName; // [rsp+70h] [rbp-60h] BYREF
  std::string p_SecondFamilyName; // [rsp+80h] [rbp-50h] BYREF
  std::string p_FirstFamilyName; // [rsp+90h] [rbp-40h] BYREF

  std::string::string(&p_ThirdFamilyName, &this->m_ThirdFamilyName);
  std::string::string(&p_SecondFamilyName, &this->m_SecondFamilyName);
  std::string::string(&p_FirstFamilyName, &this->m_FirstFamilyName);
  nIndex = this->m_nIndex;
  Third = this->m_Third;
  Second = this->m_Second;
  First = this->m_First;
  nLeaderCid = this->m_Leader;
  nTime = this->m_nStartTime;
  m_nWinTime = this->m_nWinTime;
  m_nFamilyId = this->m_nFamilyId;
  Id = CActivity::GetId(this);
  v6 = Answer::Singleton<DBService>::instance();
  DBService::SaveCityWarResult(
    v6,
    Id,
    m_nFamilyId,
    m_nWinTime,
    nTime,
    nLeaderCid,
    First,
    Second,
    Third,
    nIndex,
    &p_FirstFamilyName,
    &p_SecondFamilyName,
    &p_ThirdFamilyName);
  std::string::~string(&p_FirstFamilyName);
  std::string::~string(&p_SecondFamilyName);
  std::string::~string(&p_ThirdFamilyName);
}


#####################################
void __cdecl CCityWar::onActivityStart(CCityWar *const this)
{
  FamilyId_t m_nLastFamilyId; // rbx
  GameService *v2; // rax
  CActivityManager *v3; // rax
  FamilyId_t m_nFamilyId; // rbx
  GameService *v5; // rax

  ++this->m_nIndex;
  m_nLastFamilyId = this->m_nLastFamilyId;
  v2 = Answer::Singleton<GameService>::instance();
  GameService::UpdateCityWarTitle(v2, m_nLastFamilyId, 0);
  v3 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SetCityWarWinner(v3, 0, 0);
  CActivity::sendSocialUpdateActivityState(this, 1);
  m_nFamilyId = this->m_nFamilyId;
  v5 = Answer::Singleton<GameService>::instance();
  GameService::UpdateCityActState(v5, m_nFamilyId, 0);
  this->m_nFamilyId = this->m_nLastFamilyId;
  CCityWar::AutoApplyCityWar(this);
}


#####################################
void __cdecl CCityWar::onTimeEnd(CCityWar *const this)
{
  CCityWar::win(this);
  std::map<long,int>::clear(&this->m_Apply);
  CActivity::onTimeEnd(this);
  CActivity::sendSocialUpdateActivityState(this, 0);
}


#####################################
int32_t __cdecl CCityWar::getNextStartTime(CCityWar *const this)
{
  CTimer *v3; // rax
  CTimer *v4; // rax
  int v5; // ebx
  size_t v6; // rbx
  CfgData *v7; // rax
  CfgData *v8; // rax
  CfgData *v9; // rax
  CTimer *v11; // rax
  const int *v12; // rax
  tm localnow; // [rsp+10h] [rbp-B0h] BYREF
  std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > iter; // [rsp+50h] [rbp-70h] BYREF
  std::vector<int> v15; // [rsp+60h] [rbp-60h] BYREF
  int32_t nNowTime; // [rsp+84h] [rbp-3Ch]
  int32_t nowMinute; // [rsp+88h] [rbp-38h]
  int32_t startMinute; // [rsp+8Ch] [rbp-34h]
  int32_t days; // [rsp+90h] [rbp-30h]
  int32_t startDays; // [rsp+94h] [rbp-2Ch]
  int32_t SpecialDay; // [rsp+98h] [rbp-28h]
  uint32_t i; // [rsp+A0h] [rbp-20h]
  int32_t startTime; // [rsp+A4h] [rbp-1Ch]
  int32_t weekday; // [rsp+A8h] [rbp-18h]
  int32_t nextweekday; // [rsp+ACh] [rbp-14h]

  if ( CActivity::IsRuning(this) || std::vector<int>::empty(&this->m_cfgActivity->start_hour) )
    return 0;
  v3 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v3);
  v4 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&localnow, v4);
  nowMinute = 60 * localnow.tm_hour + localnow.tm_min;
  startMinute = *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, 0);
  for ( i = 0; ; ++i )
  {
    v6 = i;
    if ( v6 >= std::vector<int>::size(&this->m_cfgActivity->start_hour) )
      break;
    v5 = Answer::DayTime::dayzero(nNowTime);
    startTime = v5 + 60 * *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, i);
    if ( startMinute > nNowTime )
    {
      startMinute = *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, i);
      break;
    }
  }
  days = -1;
  startDays = 0;
  SpecialDay = 0;
  v7 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v7) )
  {
    v8 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v8, SERVER_TYPE::SVT_UNITE);
  }
  else
  {
    v9 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v9, SERVER_TYPE::SVT_NORMAL);
  }
  SpecialDay = 2;
  if ( (*((unsigned __int8 (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 48))(this)
    && (*((unsigned __int8 (__fastcall **)(CCityWar *const))this->_vptr_CActivity + 49))(this) )
  {
    if ( nowMinute < startMinute )
      days = 0;
  }
  else if ( CCityWar::isInSpecialDay(this, startDays) && startDays < SpecialDay )
  {
    days = SpecialDay - startDays;
  }
  if ( days < 0 )
  {
    if ( std::vector<int>::empty(&this->m_cfgActivity->weekday) )
      return 0;
    v11 = Answer::Singleton<CTimer>::instance();
    weekday = CTimer::GetWeekDay(v11);
    nextweekday = 0;
    std::vector<int>::rbegin((const std::vector<int> *const)&iter);
    while ( 1 )
    {
      std::vector<int>::rend(&v15);
      if ( !std::operator!=<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>(
              &iter,
              (const std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > *const)&v15) )
        break;
      v12 = std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator*(&iter);
      if ( *v12 > weekday )
        break;
      std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator++(&iter);
    }
    std::vector<int>::rend((const std::vector<int> *const)&v15._M_impl._M_end_of_storage);
    if ( std::operator==<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>(
           &iter,
           (const std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > *const)&v15._M_impl._M_end_of_storage) )
    {
      nextweekday = *std::vector<int>::back(&this->m_cfgActivity->weekday);
    }
    else
    {
      nextweekday = *std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator*(&iter);
    }
    if ( nextweekday >= weekday )
      days = nextweekday - weekday;
    else
      days = nextweekday + 7 - weekday;
  }
  return 86400 * days + 60 * startMinute + Answer::DayTime::dayzero(nNowTime);
}


#####################################
void __cdecl CCityWar::OnCityWarResult(
        CCityWar *const this,
        FamilyId_t nFamilyId,
        int32_t nWinTime,
        int32_t nTime,
        CharId_t nLeaderCid,
        CharId_t First,
        CharId_t Second,
        CharId_t Third,
        int32_t nIndex,
        std::string *p_FirstFamilyName,
        std::string *p_SecondFamilyName,
        std::string *p_ThirdFamilyName)
{
  GameService *v12; // rax

  this->m_nState = ACTIVITY_STATE::AS_END;
  this->m_nIndex = nIndex;
  this->m_nFamilyId = nFamilyId;
  this->m_nLastFamilyId = nFamilyId;
  this->m_nWinTime = nWinTime;
  this->m_Leader = nLeaderCid;
  this->m_First = First;
  this->m_Second = Second;
  this->m_Third = Third;
  std::string::operator=(&this->m_FirstFamilyName, p_FirstFamilyName);
  std::string::operator=(&this->m_SecondFamilyName, p_SecondFamilyName);
  std::string::operator=(&this->m_ThirdFamilyName, p_ThirdFamilyName);
  v12 = Answer::Singleton<GameService>::instance();
  GameService::broadFamilyWarIcon(v12);
}


#####################################
void __cdecl CCityWar::SendAppyCityWarInfo(CCityWar *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t v4; // eax
  std::pair<const long int,int> *v5; // rax
  __int64 first; // rbx
  FamilyManager *v7; // rax
  std::pair<const long int,int> *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  FamilyInfo info; // [rsp+10h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+80h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > __x; // [rsp+90h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E2Eu);
    if ( packet )
    {
      v4 = std::map<long,int>::size(&this->m_Apply);
      Answer::NetPacket::writeInt32(packet, v4);
      for ( it._M_node = std::map<long,int>::begin(&this->m_Apply)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<long const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<long,int>::end(&this->m_Apply)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&it, &__x) )
          break;
        v5 = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it);
        Answer::NetPacket::writeInt64(packet, v5->first);
        first = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it)->first;
        v7 = Answer::Singleton<FamilyManager>::instance();
        FamilyManager::GetFamilyInfo(&info, v7, first);
        Answer::NetPacket::writeUTF8(packet, &info.strName);
        v8 = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v8->second);
        FamilyInfo::~FamilyInfo(&info);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v11 = Player::getConnId(player);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CCityWar::ApplyCityWar(CCityWar *const this, Player *player, FamilyId_t FamilyId, int8_t Type)
{
  int *v5; // rbx
  FamilyId_t FamilyIda; // [rsp+8h] [rbp-48h] BYREF
  Player *playera; // [rsp+10h] [rbp-40h]
  CCityWar *thisa; // [rsp+18h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  playera = player;
  FamilyIda = FamilyId;
  if ( !player )
    return 0;
  if ( thisa->m_nLastFamilyId == FamilyIda )
    return 0;
  it._M_node = std::map<long,int>::find(&thisa->m_Apply, &FamilyIda)._M_node;
  __x._M_node = std::map<long,int>::end(&thisa->m_Apply)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&it, &__x) )
  {
    if ( Type == 2 )
    {
      *std::map<long,int>::operator[](&thisa->m_Apply, &FamilyIda) = 1;
      CCityWar::SendAppyCityWarInfo(thisa, playera);
      CCityWar::SaveApplyInfo(thisa);
      return 1;
    }
    else if ( Type == 3 )
    {
      v5 = std::map<long,int>::operator[](&thisa->m_Apply, &FamilyIda);
      *v5 = Unit::getNow(playera);
      CCityWar::SendAppyCityWarInfo(thisa, playera);
      CCityWar::SaveApplyInfo(thisa);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else if ( Type == 1 )
  {
    *std::map<long,int>::operator[](&thisa->m_Apply, &FamilyIda) = 0;
    CCityWar::SendAppyCityWarInfo(thisa, playera);
    CCityWar::SaveApplyInfo(thisa);
    CCityWar::GongGao(thisa, FamilyIda, 340);
    return 1;
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl CCityWar::AutoApplyCityWar(CCityWar *const this)
{
  __int64 *v1; // rax
  __int64 *v2; // rax
  FamilyId_t v3; // rcx
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<long int> itList; // [rsp+20h] [rbp-50h] BYREF
  Int64List FamilyIdList; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<long int> v7; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > __x; // [rsp+50h] [rbp-20h] BYREF

  Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetTop10Family((FamilyManager *const)&FamilyIdList);
  for ( itList._M_node = std::list<long>::begin(&FamilyIdList)._M_node; ; std::_List_iterator<long>::operator++(
                                                                            &itList,
                                                                            0) )
  {
    v7._M_node = std::list<long>::end(&FamilyIdList)._M_node;
    if ( !std::_List_iterator<long>::operator!=(&itList, &v7) )
      break;
    if ( *std::_List_iterator<long>::operator*(&itList) != this->m_nLastFamilyId )
    {
      v1 = std::_List_iterator<long>::operator*(&itList);
      it._M_node = std::map<long,int>::find(&this->m_Apply, v1)._M_node;
      __x._M_node = std::map<long,int>::end(&this->m_Apply)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<long const,int>>::operator==(&it, &__x) )
      {
        v2 = std::_List_iterator<long>::operator*(&itList);
        *std::map<long,int>::operator[](&this->m_Apply, v2) = 0;
        CCityWar::SaveApplyInfo(this);
        v3 = *std::_List_iterator<long>::operator*(&itList);
        CCityWar::GongGao(this, v3, 340);
      }
    }
  }
  std::list<long>::~list(&FamilyIdList);
}


#####################################
void __cdecl CCityWar::GongGao(CCityWar *const this, FamilyId_t FamilyId, int32_t GongGaoId)
{
  FamilyManager *v3; // rax
  GameService *v4; // rax
  uint32_t WOffset; // eax
  GameService *v6; // rax
  FamilyInfo info; // [rsp+20h] [rbp-90h] BYREF
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  v3 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&info, v3, FamilyId);
  if ( !FamilyInfo::IsEmpty(&info) )
  {
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Answer::NetPacket::writeUTF8(packet, &info.strName);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v6, packet);
    }
  }
  FamilyInfo::~FamilyInfo(&info);
}


#####################################
void __cdecl CCityWar::SaveApplyInfo(CCityWar *const this)
{
  std::_Ios_Openmode v1; // eax
  std::pair<const long int,int> *v2; // rax
  std::pair<const long int,int> *v3; // rax
  const char *v4; // rbx
  const char *v5; // rax
  Answer::DBPool *v6; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-11F0h] BYREF
  _BYTE v8[16]; // [rsp+1010h] [rbp-1F0h] BYREF
  _BYTE v9[352]; // [rsp+1020h] [rbp-1E0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1180h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > it; // [rsp+11B0h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,int> > __x; // [rsp+11C0h] [rbp-40h] BYREF
  std::string v13; // [rsp+11D0h] [rbp-30h] BYREF
  std::string v14; // [rsp+11E0h] [rbp-20h] BYREF

  v1 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v8, (unsigned int)v1);
  for ( it._M_node = std::map<long,int>::begin(&this->m_Apply)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<long,int>::end(&this->m_Apply)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,int>>::operator!=(&it, &__x) )
      break;
    v2 = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it);
    std::ostream::operator<<(v9, v2->first);
    std::operator<<<std::char_traits<char>>(v9, ":");
    v3 = std::_Rb_tree_iterator<std::pair<long const,int>>::operator->(&it);
    std::ostream::operator<<(v9, (unsigned int)v3->second);
    std::operator<<<std::char_traits<char>>(v9, "|");
  }
  memset(szSQL, 0, sizeof(szSQL));
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v13, v8);
  v4 = (const char *)std::string::c_str(&v13);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v14, v8);
  v5 = (const char *)std::string::c_str(&v14);
  snprintf(
    szSQL,
    0xFFFu,
    "INSERT INTO `mem_city_war_apply` (`index`,`applyinfo`) VALUES (%d,'%s')  ON DUPLICATE KEY UPDATE `applyinfo`='%s'",
    this->m_nIndex + 1,
    v5,
    v4);
  std::string::~string(&v14);
  std::string::~string(&v13);
  v6 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v6);
  Answer::MySqlDBGuard::excute(&db, szSQL);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v8);
}


#####################################
int32_t __cdecl CCityWar::canEnter(CCityWar *const this, Player *player, CActivityMap *pTargetMap)
{
  char v4; // al

  if ( !player || !pTargetMap )
    return 10002;
  if ( Map::GetMapId(pTargetMap) == 50130 && CActivity::getLeftTime(this) <= 299 )
  {
    Player::TiShiInfo(player, 19, 0);
    return 10002;
  }
  else if ( Player::getFamilyId(player) != this->m_nFamilyId
         && Map::GetMapId(pTargetMap) == 50130
         && (!this->m_pMonster || !Unit::isAlive(this->m_pMonster) ? (v4 = 0) : (v4 = 1), v4) )
  {
    Player::TiShiInfo(player, 18, 0);
    return 10002;
  }
  else
  {
    return CActivity::canEnter(this, player, pTargetMap);
  }
}


#####################################
void __cdecl CCityWar::appendPlayerRankInfo(
        CCityWar *const this,
        Answer::NetPacket *packet,
        const CCityWar::FamilyScore::PlayerScoreRank *const rank)
{
  int32_t Id; // edx
  std::_List_const_iterator<CCityWar::PlayerScore*> iter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_const_iterator<CCityWar::PlayerScore*> __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t nCount; // [rsp+3Ch] [rbp-14h]
  uint32_t oldOffset; // [rsp+40h] [rbp-10h]
  uint32_t newOffset; // [rsp+44h] [rbp-Ch]
  CCityWar::PlayerScore *pScore; // [rsp+48h] [rbp-8h]

  if ( packet )
  {
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    nCount = 0;
    oldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt32(packet, 0);
    for ( iter._M_node = std::list<CCityWar::PlayerScore *>::begin(rank)._M_node;
          ;
          std::_List_const_iterator<CCityWar::PlayerScore *>::operator++(&iter) )
    {
      __x._M_node = std::list<CCityWar::PlayerScore *>::end(rank)._M_node;
      if ( !std::_List_const_iterator<CCityWar::PlayerScore *>::operator!=(&iter, &__x) )
        break;
      pScore = *std::_List_const_iterator<CCityWar::PlayerScore *>::operator*(&iter);
      if ( !pScore || pScore->nScore <= 0 )
        break;
      Answer::NetPacket::writeInt64(packet, pScore->nCharId);
      Answer::NetPacket::writeUTF8(packet, &pScore->strName);
      Answer::NetPacket::writeInt32(packet, pScore->nScore);
      ++nCount;
    }
    if ( nCount )
    {
      newOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, oldOffset);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::setWOffset(packet, newOffset);
    }
  }
}


#####################################
bool __cdecl CCityWar::OnChangeMap(
        CCityWar *const this,
        Player *player,
        CActivityMap *pMap,
        int32_t nX,
        int32_t nY,
        int32_t param)
{
  std::_List_iterator<CActivityMap*> iter; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+40h] [rbp-30h] BYREF
  bool bFind; // [rsp+52h] [rbp-1Eh]
  bool bCheckChangeWinFamily; // [rsp+53h] [rbp-1Dh]
  int32_t Err; // [rsp+54h] [rbp-1Ch]
  CActivityMap *tp; // [rsp+58h] [rbp-18h]

  if ( !player || !pMap )
    return 0;
  if ( !Map::isWalkablePosition(pMap, nX, nY) )
    return 0;
  bFind = 0;
  for ( iter._M_node = std::list<CActivityMap *>::begin(&this->m_activityMaps)._M_node;
        ;
        std::_List_iterator<CActivityMap *>::operator++(&iter) )
  {
    __x._M_node = std::list<CActivityMap *>::end(&this->m_activityMaps)._M_node;
    if ( !std::_List_iterator<CActivityMap *>::operator!=(&iter, &__x) )
      break;
    tp = *std::_List_iterator<CActivityMap *>::operator*(&iter);
    if ( tp && tp == pMap )
    {
      bFind = 1;
      break;
    }
  }
  if ( !bFind )
    return 0;
  bCheckChangeWinFamily = 0;
  if ( StaticObj::getMapId(player) == 50130 || Map::GetMapId(pMap) == 50130 )
    bCheckChangeWinFamily = 1;
  Err = Player::switchMap(player, pMap, nX, nY, 1);
  if ( !Err )
    CCityWar::checkChangeFamily(this, 0);
  return Err == 0;
}


#####################################
void __cdecl CCityWar::broadcastReady(CCityWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 332);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
  }
}


#####################################
void __cdecl CCityWar::broadcastStart(CCityWar *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  MapManager *v4; // rax
  int32_t RunnerId; // ebx
  MapManager *v6; // rax
  Answer::NetPacket *packet; // [rsp+20h] [rbp-20h]
  Map *pMap; // [rsp+28h] [rbp-18h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 335);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
    v4 = Answer::Singleton<MapManager>::instance();
    pMap = MapManager::GetMap(v4, 50133);
    if ( pMap )
    {
      RunnerId = Map::GetRunnerId(pMap);
      v6 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v6, RunnerId, GameMsgCode::GMC_CITY_STAR, pMap, this, 0, 0, 0);
    }
    std::string::operator=(&this->m_FirstFamilyName, &strNull);
    std::string::operator=(&this->m_SecondFamilyName, &strNull);
    std::string::operator=(&this->m_ThirdFamilyName, &strNull);
    this->m_First = 0;
    this->m_Second = 0;
    this->m_Third = 0;
  }
}


