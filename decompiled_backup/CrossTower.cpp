// Decompiled methods for class: CrossTower
// Source: gameserver.cc
// Total methods: 26

#####################################
void __cdecl CrossTower::~CrossTower(CrossTower *const this)
{
  CrossTower::~CrossTower(this);
  operator delete(this);
}


#####################################
void __cdecl CrossTower::Init(CrossTower *const this)
{
  GameService *v1; // rax
  DBService *v2; // rax
  Answer::DBPool *v3; // rax
  Answer::MySqlQuery *v4; // rax
  const char *StringValue; // rax
  CharId_t m_WinerId; // rbx
  CActivityManager *v7; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-40h] BYREF
  std::string p_Name; // [rsp+60h] [rbp-20h] BYREF
  int32_t Battle; // [rsp+6Ch] [rbp-14h]

  CActivity::Init(this);
  this->m_WinerId = 0;
  std::string::operator=(&this->m_WinerName, &byte_8CE68F);
  this->m_Monster = 0;
  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 9 )
  {
    v2 = Answer::Singleton<DBService>::instance();
    DBService::onLoadCrossTowerInfo(v2);
  }
  else
  {
    v3 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v3);
    v4 = Answer::MySqlDBGuard::query(&db, "SELECT * FROM `mem_cross_tower` where id=1");
    Answer::MySqlQuery::MySqlQuery(&result, v4);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      this->m_WinerId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8CE68F);
      std::string::operator=(&this->m_WinerName, StringValue);
      Battle = Answer::MySqlQuery::getIntValue(&result, "battle", 0);
      if ( this->m_WinerId > 0 )
      {
        std::string::string(&p_Name, &this->m_WinerName);
        m_WinerId = this->m_WinerId;
        v7 = Answer::Singleton<CActivityManager>::instance();
        CActivityManager::SetCrossTowerWinner(v7, m_WinerId, Battle, &p_Name);
        std::string::~string(&p_Name);
      }
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl CrossTower::OnUpdate(CrossTower *const this, CActivityMap *pMap)
{
  Player **v2; // rax
  int32_t MapId; // ebx
  CfgData *v4; // rax
  Player **v5; // rax
  int32_t Record; // eax
  int32_t NextMapId; // ebx
  MapManager *v8; // rax
  CfgData *v9; // rax
  Player **v10; // rax
  Player **v11; // rax
  Player **v12; // rax
  int32_t v13; // ebx
  CfgData *v14; // rax
  Player **v15; // rax
  int32_t Floor; // r12d
  int32_t MapPlayerAliveSize; // esi
  int64_t v18; // rbx
  Player **v19; // rax
  Player **v20; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v21; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v22; // rbx
  Player **v23; // rax
  void (__fastcall *v24)(CrossTower *const, Player *); // rbx
  Player *v25; // rdx
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > ScoreIt; // [rsp+10h] [rbp-110h] BYREF
  std::_List_iterator<Player*> eiter_0; // [rsp+20h] [rbp-100h] BYREF
  std::_List_iterator<Player*> iter_0; // [rsp+30h] [rbp-F0h] BYREF
  PlayerList tList_0; // [rsp+40h] [rbp-E0h] BYREF
  Position pos; // [rsp+50h] [rbp-D0h]
  std::_List_iterator<Player*> eiter; // [rsp+60h] [rbp-C0h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+70h] [rbp-B0h] BYREF
  PlayerList tList; // [rsp+80h] [rbp-A0h] BYREF
  std::_Rb_tree_const_iterator<int> it; // [rsp+90h] [rbp-90h] BYREF
  int __x; // [rsp+9Ch] [rbp-84h] BYREF
  std::_Rb_tree_const_iterator<int> v37; // [rsp+A0h] [rbp-80h] BYREF
  __int64 Cid; // [rsp+A8h] [rbp-78h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v39; // [rsp+B0h] [rbp-70h] BYREF
  Answer::NetPacket *packet; // [rsp+C0h] [rbp-60h]
  CrossTowerCfg *pCrossTowerCfg; // [rsp+C8h] [rbp-58h]
  Map *pTargetMap; // [rsp+D0h] [rbp-50h]
  int32_t ReviveId; // [rsp+DCh] [rbp-44h]
  CfgMapRegion *pCfgMapRegion; // [rsp+E0h] [rbp-40h]
  CrossTowerCfg *pCrossTowerCfg_0; // [rsp+E8h] [rbp-38h]
  Map *pMap_0; // [rsp+F0h] [rbp-30h]
  int32_t AddScore; // [rsp+FCh] [rbp-24h]

  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    __x = Map::GetMapId(pMap);
    it._M_node = std::set<int>::find(&this->m_NeedSysMap, &__x)._M_node;
    v37._M_node = std::set<int>::end(&this->m_NeedSysMap)._M_node;
    if ( std::_Rb_tree_const_iterator<int>::operator!=(&it, &v37) )
    {
      packet = CrossTower::packetActivityMapInfo(this, pMap);
      if ( !packet )
        return;
      Map::broadcast(pMap, packet);
      std::set<int>::erase(&this->m_NeedSysMap, it);
    }
    if ( this->m_NeedChangeMap )
    {
      std::list<Player *>::list(&tList, &this->m_players);
      iter._M_node = std::list<Player *>::begin(&tList)._M_node;
      eiter._M_node = std::list<Player *>::end(&tList)._M_node;
      while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
      {
        v2 = std::_List_iterator<Player *>::operator*(&iter);
        MapId = StaticObj::getMapId(*v2);
        v4 = Answer::Singleton<CfgData>::instance();
        pCrossTowerCfg = CfgData::GetCrossTowerCfg(v4, MapId);
        if ( pCrossTowerCfg && (this->m_State != 3 || pCrossTowerCfg->Floor != 8) && pCrossTowerCfg->NextMapId > 0 )
        {
          v5 = std::_List_iterator<Player *>::operator*(&iter);
          Record = Player::getRecord(*v5, 3);
          if ( Record >= pCrossTowerCfg->KillCount )
          {
            NextMapId = pCrossTowerCfg->NextMapId;
            v8 = Answer::Singleton<MapManager>::instance();
            pTargetMap = MapManager::GetMap(v8, NextMapId);
            if ( pTargetMap )
            {
              ReviveId = (*((__int64 (__fastcall **)(Map *))pTargetMap->_vptr_Map + 7))(pTargetMap);
              v9 = Answer::Singleton<CfgData>::instance();
              pCfgMapRegion = CfgData::getMapRegion(v9, ReviveId);
              if ( pCfgMapRegion )
              {
                pos = Map::getRandomWalkablePositionInRegion(pTargetMap, pCfgMapRegion);
                if ( pos.x < 0 || pos.y < 0 )
                {
                  pos.x = 32;
                  pos.y = 56;
                }
                v10 = std::_List_iterator<Player *>::operator*(&iter);
                Player::FullHPAndSync(*v10);
                v11 = std::_List_iterator<Player *>::operator*(&iter);
                Player::switchMap(*v11, pTargetMap, pos.x, pos.y, 0);
              }
            }
          }
        }
        std::_List_iterator<Player *>::operator++(&iter);
      }
      this->m_NeedChangeMap = 0;
      std::list<Player *>::~list(&tList);
    }
    if ( this->m_NeedAddScore )
    {
      std::list<Player *>::list(&tList_0, &this->m_players);
      iter_0._M_node = std::list<Player *>::begin(&tList_0)._M_node;
      eiter_0._M_node = std::list<Player *>::end(&tList_0)._M_node;
      while ( std::_List_iterator<Player *>::operator!=(&iter_0, &eiter_0) )
      {
        v12 = std::_List_iterator<Player *>::operator*(&iter_0);
        v13 = StaticObj::getMapId(*v12);
        v14 = Answer::Singleton<CfgData>::instance();
        pCrossTowerCfg_0 = CfgData::GetCrossTowerCfg(v14, v13);
        v15 = std::_List_iterator<Player *>::operator*(&iter_0);
        pMap_0 = StaticObj::getMap(*v15);
        if ( pCrossTowerCfg_0 )
        {
          if ( pMap_0 )
          {
            Floor = pCrossTowerCfg_0->Floor;
            MapPlayerAliveSize = Map::GetMapPlayerAliveSize(pMap_0);
            AddScore = CrossTower::CallAddScore(
                         this,
                         pCrossTowerCfg_0->MaxPlayer,
                         pCrossTowerCfg_0->MaxScore,
                         pCrossTowerCfg_0->MinScore,
                         MapPlayerAliveSize,
                         Floor);
            if ( AddScore > 0 )
            {
              v18 = AddScore;
              v19 = std::_List_iterator<Player *>::operator*(&iter_0);
              Player::AddCurrency(*v19, CURRENCY_TYPE::CURRENCY_DUST, v18, CURRENCY_CHANGE_REASON::GCR_CROSS_TOWER, 0);
              v20 = std::_List_iterator<Player *>::operator*(&iter_0);
              Cid = Player::getCid(*v20);
              ScoreIt._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &Cid)._M_node;
              v39._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
              if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&ScoreIt, &v39) )
              {
                v21 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&ScoreIt);
                v21->second.nScore += AddScore;
                v22 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&ScoreIt);
                v23 = std::_List_iterator<Player *>::operator*(&iter_0);
                v22->second.nScoreTime = Unit::getNow(*v23);
                v24 = (void (__fastcall *)(CrossTower *const, Player *))*((_QWORD *)this->_vptr_CActivity + 51);
                v25 = *std::_List_iterator<Player *>::operator*(&iter_0);
                v24(this, v25);
              }
            }
          }
        }
        std::_List_iterator<Player *>::operator++(&iter_0);
      }
      this->m_NeedAddScore = 0;
      std::list<Player *>::~list(&tList_0);
    }
    if ( Map::GetMapId(pMap) != 60029 )
      CrossTower::CheckWin(this, 0);
  }
}


#####################################
int32_t __cdecl CrossTower::onBeginGather(CrossTower *const this, PlantActivity *plant, Player *player)
{
  if ( !plant || !player )
    return 10002;
  if ( Player::getRecord(player, 2110) <= 3 )
    return 0;
  return 10002;
}


#####################################
void __cdecl CrossTower::onPlantGather(CrossTower *const this, PlantActivity *pPlant, Player *player)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( pPlant )
  {
    if ( player )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 2110, 1);
    }
  }
}


#####################################
void __cdecl CrossTower::reset(CrossTower *const this)
{
  this->m_State = 0;
  this->m_StateTime = 0;
  this->m_LastUpdateTime = 0;
  std::map<long,CrossTower::PlayerScore>::clear(&this->m_mPlayerScore);
  this->m_NeedChangeMap = 0;
  this->m_NeedAddScore = 0;
  this->m_LastAddScoreTime = 0;
  std::set<int>::clear(&this->m_NeedSysMap);
  this->m_NewWinerId = 0;
  std::string::operator=(&this->m_NewWinerName, &byte_8CE68F);
  this->m_ConnId = 0;
  this->m_Battle = 0;
  this->m_Monster = 0;
  CActivity::reset(this);
}


#####################################
int32_t __cdecl CrossTower::canEnter(CrossTower *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( player && pTargetMap )
    return CActivity::canEnter(this, player, pTargetMap);
  else
    return 10002;
}


#####################################
void __cdecl CrossTower::addPlayer(CrossTower *const this, Player *player)
{
  std::pair<const long int,CrossTower::PlayerScore> *v2; // rbx
  std::pair<const long int,CrossTower::PlayerScore> *v3; // rbx
  CfgData *v4; // rax
  CfgData *v5; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v6; // rbx
  CrossTower::PlayerScore score; // [rsp+20h] [rbp-110h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > iter; // [rsp+60h] [rbp-D0h] BYREF
  std::pair<std::_Rb_tree_const_iterator<int>,bool> v9; // [rsp+70h] [rbp-C0h]
  int __x; // [rsp+84h] [rbp-ACh] BYREF
  __int64 Cid; // [rsp+88h] [rbp-A8h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v12; // [rsp+90h] [rbp-A0h] BYREF
  _BYTE v13[16]; // [rsp+A0h] [rbp-90h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> >,bool> v14; // [rsp+B0h] [rbp-80h]
  std::pair<const long int,CrossTower::PlayerScore> v15; // [rsp+C0h] [rbp-70h] BYREF
  CrossTowerCfg *pCrossTowerCfg; // [rsp+110h] [rbp-20h]
  CrossTowerCfg *pMaxTowerCfg; // [rsp+118h] [rbp-18h]

  if ( player )
  {
    if ( this->m_State == 1 )
      Player::setPkMode(player, 1, 0);
    else
      Player::setPkMode(player, 6, 0);
    __x = StaticObj::getMapId(player);
    v9 = std::set<int>::insert(&this->m_NeedSysMap, &__x);
    Player::updateRecord(player, 3, 0);
    Cid = Player::getCid(player);
    iter._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &Cid)._M_node;
    v12._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&iter, &v12) )
    {
      std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.bInActivity = 1;
      v2 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter);
      v2->second.nCurMapId = StaticObj::getMapId(player);
      v3 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter);
      v3->second.nBattle = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 10))(player);
      LODWORD(v3) = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.nCurMapId;
      v4 = Answer::Singleton<CfgData>::instance();
      pCrossTowerCfg = CfgData::GetCrossTowerCfg(v4, (int32_t)v3);
      LODWORD(v3) = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.nMaxMapId;
      v5 = Answer::Singleton<CfgData>::instance();
      pMaxTowerCfg = CfgData::GetCrossTowerCfg(v5, (int32_t)v3);
      if ( pCrossTowerCfg && pMaxTowerCfg && pCrossTowerCfg->Floor > pMaxTowerCfg->Floor )
      {
        v6 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter);
        v6->second.nMaxMapId = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.nCurMapId;
      }
    }
    else
    {
      memset(&score, 0, sizeof(score));
      std::string::string(&score.strName);
      score.nCharId = Player::getCid(player);
      Player::getName((const Player *const)v13);
      std::string::operator=(&score.strName, v13);
      std::string::~string(v13);
      score.bInActivity = 1;
      score.nConnId = Player::getConnId(player);
      score.nCurMapId = StaticObj::getMapId(player);
      score.nMaxMapId = StaticObj::getMapId(player);
      score.nBattle = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 10))(player);
      score.nSid = Player::getSid(player);
      score.nEnterTime = Unit::getTick(player);
      std::pair<long const,CrossTower::PlayerScore>::pair(&v15, &score.nCharId, &score);
      v14 = std::map<long,CrossTower::PlayerScore>::insert(&this->m_mPlayerScore, &v15);
      std::pair<long const,CrossTower::PlayerScore>::~pair(&v15);
      CrossTower::PlayerScore::~PlayerScore(&score);
    }
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl CrossTower::removePlayer(CrossTower *const this, Player *player, bool islogout)
{
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > iter; // [rsp+30h] [rbp-40h] BYREF
  std::pair<std::_Rb_tree_const_iterator<int>,bool> v4; // [rsp+40h] [rbp-30h]
  int __x; // [rsp+54h] [rbp-1Ch] BYREF
  __int64 Cid; // [rsp+58h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v7; // [rsp+60h] [rbp-10h] BYREF

  CActivity::removePlayer(this, player, islogout);
  if ( player )
  {
    __x = StaticObj::getMapId(player);
    v4 = std::set<int>::insert(&this->m_NeedSysMap, &__x);
    Player::updateRecord(player, 3, 0);
    Cid = Player::getCid(player);
    iter._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &Cid)._M_node;
    v7._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&iter, &v7) )
      std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.bInActivity = 0;
  }
}


#####################################
void __cdecl CrossTower::broadcastReady(CrossTower *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 511);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
  }
}


#####################################
void __cdecl CrossTower::broadcastStart(CrossTower *const this)
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
    Answer::NetPacket::writeInt32(packet, 512);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, packet);
  }
}


#####################################
void __cdecl CrossTower::onTimeEnd(CrossTower *const this)
{
  GameService *v1; // rax
  int32_t Id; // edx
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  CrossTower::CheckWin(this, 1);
  CrossTower::addRewards(this);
  this->m_nState = ACTIVITY_STATE::AS_END;
  CActivity::delayKickAll(this, 30);
  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 513);
    Id = CActivity::GetId(this);
    Answer::NetPacket::writeInt32(packet, Id);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, packet);
  }
}


#####################################
int32_t __cdecl CrossTower::GiveDailyReward(CrossTower *const this, Player *player)
{
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > it; // [rsp+10h] [rbp-20h] BYREF
  __int64 __x; // [rsp+18h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v5; // [rsp+20h] [rbp-10h] BYREF

  if ( !player )
    return 10002;
  __x = Player::getCid(player);
  it._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
  v5._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator==(&it, &v5) )
    return 10002;
  if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nIsMoBai > 0 )
    return 10002;
  std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nIsMoBai = 1;
  Player::AddCurrency(player, CURRENCY_TYPE::CURRENCY_DUST, 10000, CURRENCY_CHANGE_REASON::GCR_CROSS_TOWER, 0);
  (*((void (__fastcall **)(CrossTower *const, Player *))this->_vptr_CActivity + 51))(this, player);
  return 0;
}


#####################################
void __cdecl CrossTower::addRewards(CrossTower *const this)
{
  CharId_t m_WinerId; // rbx
  GameService *v2; // rax
  CharId_t m_NewWinerId; // rbx
  GameService *v4; // rax
  int32_t m_Battle; // r12d
  CharId_t time; // rbx
  CActivityManager *v7; // rax
  CTimer *v8; // rax
  int8_t m_ConnId; // r15
  int32_t v10; // r14d
  CharId_t v11; // r13
  int32_t Id; // r12d
  DBService *v13; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v14; // rax
  int32_t nCurMapId; // ebx
  CfgData *v16; // rax
  MemChrBagVector *p_RewardVt; // r14
  int32_t MailId; // r13d
  CharId_t nCharId; // r12
  int8_t nConnId; // bl
  DBService *v21; // rax
  CharId_t v22; // r12
  int8_t v23; // bl
  DBService *v24; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > eiter; // [rsp+20h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > iter; // [rsp+30h] [rbp-90h] BYREF
  std::string p_Name; // [rsp+40h] [rbp-80h] BYREF
  std::string p_name; // [rsp+50h] [rbp-70h] BYREF
  std::string Param; // [rsp+60h] [rbp-60h] BYREF
  char v30; // [rsp+6Fh] [rbp-51h] BYREF
  std::string v31; // [rsp+70h] [rbp-50h] BYREF
  char v32; // [rsp+7Fh] [rbp-41h] BYREF
  const CrossTower::PlayerScore *score; // [rsp+80h] [rbp-40h]
  CrossTowerCfg *pCrossTowerCfg; // [rsp+88h] [rbp-38h]

  if ( this->m_WinerId > 0 )
  {
    m_WinerId = this->m_WinerId;
    v2 = Answer::Singleton<GameService>::instance();
    GameService::onRemoveTitle(v2, m_WinerId, 9);
  }
  this->m_WinerId = this->m_NewWinerId;
  std::string::operator=(&this->m_WinerName, &this->m_NewWinerName);
  if ( this->m_NewWinerId > 0 )
  {
    m_NewWinerId = this->m_NewWinerId;
    v4 = Answer::Singleton<GameService>::instance();
    GameService::onCheckTitle(v4, m_NewWinerId, 9, 1);
  }
  std::string::string(&p_Name, &this->m_NewWinerName);
  m_Battle = this->m_Battle;
  time = this->m_NewWinerId;
  v7 = Answer::Singleton<CActivityManager>::instance();
  CActivityManager::SetCrossTowerResult(v7, time, m_Battle, &p_Name);
  std::string::~string(&p_Name);
  v8 = Answer::Singleton<CTimer>::instance();
  LODWORD(time) = CTimer::GetNow(v8);
  m_ConnId = this->m_ConnId;
  v10 = this->m_Battle;
  std::string::string(&p_name, &this->m_NewWinerName);
  v11 = this->m_NewWinerId;
  Id = CActivity::GetId(this);
  v13 = Answer::Singleton<DBService>::instance();
  DBService::SaveCrossTowerResult(v13, Id, v11, &p_name, v10, m_ConnId, time);
  std::string::~string(&p_name);
  (*((void (__fastcall **)(CrossTower *const))this->_vptr_CActivity + 43))(this);
  iter._M_node = std::map<long,CrossTower::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
  eiter._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&iter, &eiter) )
  {
    v14 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter);
    score = &v14->second;
    nCurMapId = v14->second.nCurMapId;
    v16 = Answer::Singleton<CfgData>::instance();
    pCrossTowerCfg = CfgData::GetCrossTowerCfg(v16, nCurMapId);
    if ( pCrossTowerCfg )
    {
      if ( score->bInActivity )
      {
        std::allocator<char>::allocator(&v30);
        std::string::string(&Param, &byte_8CE68F, &v30);
        p_RewardVt = &pCrossTowerCfg->RewardVt;
        MailId = pCrossTowerCfg->MailId;
        nCharId = score->nCharId;
        nConnId = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.nConnId;
        v21 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(
          v21,
          nConnId,
          nCharId,
          MailId,
          p_RewardVt,
          ITEM_CHANGE_REASON::ICR_CROSS_TOWER,
          &Param,
          0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(&v30);
      }
      else
      {
        std::allocator<char>::allocator(&v32);
        std::string::string(&v31, &byte_8CE68F, &v32);
        v22 = score->nCharId;
        v23 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter)->second.nConnId;
        v24 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(v24, v23, v22, 6408, &v31, 0);
        std::string::~string(&v31);
        std::allocator<char>::~allocator(&v32);
      }
    }
    std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator++(&iter);
  }
}


#####################################
void __cdecl CrossTower::broadcastActivityResult(CrossTower *const this)
{
  std::pair<const long int,CrossTower::PlayerScore> *v1; // rax
  CharId_t nCharId; // rbx
  GameService *v3; // rax
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > __x; // [rsp+20h] [rbp-30h] BYREF
  CrossTower::PlayerScore *score; // [rsp+28h] [rbp-28h]
  Player *pPlayer; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  for ( iter._M_node = std::map<long,CrossTower::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&iter, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&iter);
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
        Answer::NetPacket::writeInt32(packet, score->nCurMapId);
        Answer::NetPacket::writeUTF8(packet, &this->m_NewWinerName);
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
void __cdecl CrossTower::sendPlayerScore(CrossTower *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v4; // rax
  int32_t Record; // eax
  std::pair<const long int,CrossTower::PlayerScore> *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > it; // [rsp+10h] [rbp-30h] BYREF
  __int64 __x; // [rsp+18h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v13; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    __x = Player::getCid(player);
    it._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
    v13._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&it, &v13) )
    {
      ConnId = Player::getConnId(player);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E24u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
        v4 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second.nScore);
        Record = Player::getRecord(player, 3);
        Answer::NetPacket::writeInt32(packet, Record);
        v6 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v6->second.nIsMoBai);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(player);
        v9 = Player::getConnId(player);
        v10 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v10, v9, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CrossTower::onPlayerKilled(CrossTower *const this, Player *pDier, Player *pKiller)
{
  int32_t MapId; // ebx
  CfgData *v4; // rax
  int32_t KillCount; // ebx
  CExtOperateLimit *OperateLimit; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v7; // rax
  int32_t nKillCount; // eax
  int8_t ConnId; // bl
  GameService *v11; // rax
  CharId_t v12; // rax
  std::pair<const long int,CrossTower::PlayerScore> *v13; // rax
  uint32_t WOffset; // eax
  int8_t v15; // bl
  GameService *v16; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > it; // [rsp+30h] [rbp-70h] BYREF
  std::pair<std::_Rb_tree_const_iterator<int>,bool> v19; // [rsp+40h] [rbp-60h]
  int __x; // [rsp+54h] [rbp-4Ch] BYREF
  __int64 Cid; // [rsp+58h] [rbp-48h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v22; // [rsp+60h] [rbp-40h] BYREF
  std::string val; // [rsp+70h] [rbp-30h] BYREF
  CrossTowerCfg *pCrossTowerCfg; // [rsp+78h] [rbp-28h]
  bool GongGao; // [rsp+87h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+88h] [rbp-18h]

  if ( pDier )
  {
    if ( pKiller )
    {
      __x = StaticObj::getMapId(pDier);
      v19 = std::set<int>::insert(&this->m_NeedSysMap, &__x);
      MapId = StaticObj::getMapId(pKiller);
      v4 = Answer::Singleton<CfgData>::instance();
      pCrossTowerCfg = CfgData::GetCrossTowerCfg(v4, MapId);
      if ( pCrossTowerCfg )
      {
        KillCount = pCrossTowerCfg->KillCount;
        if ( KillCount > Player::getRecord(pKiller, 3) )
        {
          OperateLimit = Player::GetOperateLimit(pKiller);
          CExtOperateLimit::AddLimitCount(OperateLimit, 3, 1);
          Player::SetNeedSyncAround(pKiller);
        }
        (*((void (__fastcall **)(CrossTower *const, Player *))this->_vptr_CActivity + 51))(this, pKiller);
        Cid = Player::getCid(pKiller);
        it._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &Cid)._M_node;
        v22._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&it, &v22) )
        {
          GongGao = 0;
          v7 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it);
          ++v7->second.nKillCount;
          nKillCount = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nKillCount;
          if ( nKillCount != 30 )
          {
            if ( nKillCount > 30 )
            {
              if ( nKillCount != 100 && nKillCount != 150 && nKillCount != 50 )
                goto LABEL_16;
            }
            else if ( nKillCount != 5 && nKillCount != 15 )
            {
              goto LABEL_16;
            }
          }
          GongGao = 1;
LABEL_16:
          if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nKillCount > 150
            && !(std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nKillCount
               % 50) )
          {
            GongGao = 1;
          }
          if ( GongGao )
          {
            ConnId = Player::getConnId(pKiller);
            v11 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v11, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( packet )
            {
              Answer::NetPacket::writeInt32(packet, 514);
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet, &val);
              std::string::~string(&val);
              v12 = Player::getCid(pKiller);
              Answer::NetPacket::writeInt64(packet, v12);
              v13 = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it);
              Answer::NetPacket::writeInt32(packet, v13->second.nKillCount);
              WOffset = Answer::NetPacket::getWOffset(packet);
              Answer::NetPacket::setSize(packet, WOffset);
              v15 = Player::getConnId(pKiller);
              v16 = Answer::Singleton<GameService>::instance();
              GameService::worldBroadcast(v16, v15, packet);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CrossTower::onMonsterAdd(CrossTower *const this, MonsterActivity *pMonster)
{
  std::string p_strFamilyName; // [rsp+10h] [rbp-20h] BYREF

  if ( pMonster )
  {
    if ( Monster::getMid(pMonster) == 2033 )
    {
      std::string::string(&p_strFamilyName, &this->m_WinerName);
      Monster::SetFamilyId(pMonster, 0, &p_strFamilyName);
      std::string::~string(&p_strFamilyName);
      this->m_Monster = pMonster;
    }
  }
}


#####################################
void __cdecl CrossTower::onMonsterDie(CrossTower *const this, MonsterActivity *pMonster, Player *pKiller)
{
  int32_t MapId; // ebx
  CfgData *v4; // rax
  int32_t KillCount; // ebx
  CExtOperateLimit *OperateLimit; // rax
  CrossTowerCfg *pCrossTowerCfg; // [rsp+28h] [rbp-18h]

  if ( pKiller )
  {
    if ( pMonster )
    {
      MapId = StaticObj::getMapId(pKiller);
      v4 = Answer::Singleton<CfgData>::instance();
      pCrossTowerCfg = CfgData::GetCrossTowerCfg(v4, MapId);
      if ( pCrossTowerCfg )
      {
        KillCount = pCrossTowerCfg->KillCount;
        if ( KillCount > Player::getRecord(pKiller, 3) )
        {
          OperateLimit = Player::GetOperateLimit(pKiller);
          CExtOperateLimit::AddLimitCount(OperateLimit, 3, 1);
          Player::SetNeedSyncAround(pKiller);
          (*((void (__fastcall **)(CrossTower *const, Player *))this->_vptr_CActivity + 51))(this, pKiller);
        }
      }
    }
  }
}


#####################################
void __cdecl CrossTower::ActUpdate(CrossTower *const this, int64_t CurTick)
{
  CTimer *v2; // rax
  int m_State; // eax
  Player **v4; // rax
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-40h] BYREF
  PlayerList tList; // [rsp+30h] [rbp-30h] BYREF
  int32_t Time; // [rsp+4Ch] [rbp-14h]

  v2 = Answer::Singleton<CTimer>::instance();
  Time = CTimer::GetNow(v2);
  this->m_LastUpdateTime = CurTick;
  if ( this->m_LastAddScoreTime > 0 && Time - this->m_LastAddScoreTime > 19 )
  {
    this->m_NeedAddScore = 1;
    this->m_LastAddScoreTime = Time;
    CActivity::setNeedBroadcastActivityScore(this);
  }
  m_State = this->m_State;
  if ( m_State == 1 )
  {
    if ( CActivity::getLeftTime(this) > 300 )
    {
      if ( Time - this->m_StateTime > 119 )
      {
        std::list<Player *>::list(&tList, &this->m_players);
        iter._M_node = std::list<Player *>::begin(&tList)._M_node;
        eiter._M_node = std::list<Player *>::end(&tList)._M_node;
        while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
        {
          v4 = std::_List_iterator<Player *>::operator*(&iter);
          Player::setPkMode(*v4, 6, 0);
          std::_List_iterator<Player *>::operator++(&iter);
        }
        this->m_State = 2;
        this->m_StateTime = Time;
        this->m_LastAddScoreTime = Time;
        CActivity::setNeedBroadcastActivityScore(this);
        std::list<Player *>::~list(&tList);
      }
    }
    else
    {
      this->m_State = 3;
      this->m_LastAddScoreTime = Time;
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
  else
  {
    if ( m_State <= 1 )
    {
      if ( !this->m_State )
      {
        this->m_State = 1;
        this->m_StateTime = Time;
        CActivity::setNeedBroadcastActivityScore(this);
      }
      return;
    }
    if ( m_State == 2 )
    {
      if ( CActivity::getLeftTime(this) <= 300 )
      {
        this->m_State = 3;
        CActivity::setNeedBroadcastActivityScore(this);
      }
      if ( Time - this->m_StateTime > 59 )
        goto LABEL_24;
    }
    else if ( m_State == 3 && Time - this->m_StateTime > 59 )
    {
LABEL_24:
      this->m_NeedChangeMap = 1;
      this->m_StateTime = Time;
      CActivity::setNeedBroadcastActivityScore(this);
    }
  }
}


#####################################
int32_t __cdecl CrossTower::GetEnterMapId(CrossTower *const this, Player *player)
{
  int32_t nCurMapId; // ebx
  CfgData *v4; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > it; // [rsp+10h] [rbp-30h] BYREF
  __int64 __x; // [rsp+18h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v7; // [rsp+20h] [rbp-20h] BYREF
  CrossTowerCfg *pCrossTowerCfg; // [rsp+28h] [rbp-18h]

  if ( !player )
    return CActivity::GetEnterMapId(this, 0);
  __x = Player::getCid(player);
  it._M_node = std::map<long,CrossTower::PlayerScore>::find(&this->m_mPlayerScore, &__x)._M_node;
  v7._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&it, &v7) )
    return CActivity::GetEnterMapId(this, player);
  nCurMapId = std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nCurMapId;
  v4 = Answer::Singleton<CfgData>::instance();
  pCrossTowerCfg = CfgData::GetCrossTowerCfg(v4, nCurMapId);
  if ( !pCrossTowerCfg )
    return CActivity::GetEnterMapId(this, player);
  if ( pCrossTowerCfg->LastMapId > 0 )
    return pCrossTowerCfg->LastMapId;
  return std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nCurMapId;
}


#####################################
int32_t __cdecl CrossTower::GetRevive(CrossTower *const this, Player *player)
{
  int32_t MapId; // ebx
  CfgData *v4; // rax
  MapManager *v5; // rax
  CrossTowerCfg *pCrossTowerCfg; // [rsp+18h] [rbp-28h]
  int32_t TarGetMapId; // [rsp+24h] [rbp-1Ch]
  Map *pTargetMap; // [rsp+28h] [rbp-18h]

  if ( !player )
    return CActivity::GetRevive(this, 0);
  MapId = StaticObj::getMapId(player);
  v4 = Answer::Singleton<CfgData>::instance();
  pCrossTowerCfg = CfgData::GetCrossTowerCfg(v4, MapId);
  if ( !pCrossTowerCfg )
    return CActivity::GetRevive(this, player);
  TarGetMapId = pCrossTowerCfg->LastMapId;
  if ( pCrossTowerCfg->Floor <= 5 )
    TarGetMapId = pCrossTowerCfg->MapId;
  v5 = Answer::Singleton<MapManager>::instance();
  pTargetMap = MapManager::GetMap(v5, TarGetMapId);
  if ( pTargetMap )
    return (*((int32_t (__fastcall **)(Map *))pTargetMap->_vptr_Map + 7))(pTargetMap);
  else
    return CActivity::GetRevive(this, player);
}


#####################################
void __cdecl CrossTower::onPlayerRevive(CrossTower *const this, Player *player, bool bSafe)
{
  int __x; // [rsp+4Ch] [rbp-4h] BYREF

  if ( player )
  {
    __x = StaticObj::getMapId(player);
    std::set<int>::insert(&this->m_NeedSysMap, &__x);
  }
}


#####################################
int32_t __cdecl CrossTower::CallAddScore(
        CrossTower *const this,
        int32_t MaxPlayer,
        int32_t MaxScore,
        int32_t MinScore,
        int32_t CurPlayer,
        int32_t Floor)
{
  int32_t DiffCount; // [rsp+28h] [rbp-8h]
  int GetSocre; // [rsp+2Ch] [rbp-4h]

  if ( CurPlayer <= MaxPlayer )
    return MaxScore;
  DiffCount = CurPlayer - MaxPlayer;
  if ( Floor <= 8 )
    GetSocre = (int)(float)((float)((float)((float)(15 * DiffCount) / -100.0) + 1.0) * (float)MaxScore);
  else
    GetSocre = (int)(float)(std::pow(0.5, (float)DiffCount) * (float)MaxScore);
  if ( GetSocre < MinScore )
    return MinScore;
  return GetSocre;
}


#####################################
void __cdecl CrossTower::CheckWin(CrossTower *const this, bool IsTimeEnd)
{
  std::_Ios_Openmode v3; // eax
  std::string *p_strName; // r12
  unsigned int nSid; // ebx
  __int64 v6; // rax
  __int64 v7; // rax
  __int64 v8; // rax
  std::_Ios_Openmode v9; // eax
  std::string *v10; // r12
  unsigned int v11; // ebx
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  _BYTE v15[16]; // [rsp+20h] [rbp-240h] BYREF
  _BYTE v16[352]; // [rsp+30h] [rbp-230h] BYREF
  CrossTower::PlayerScoreSet ScoreRank; // [rsp+190h] [rbp-D0h] BYREF
  std::_Rb_tree_const_iterator<CrossTower::PlayerScore*> RandIt_0; // [rsp+1C0h] [rbp-A0h] BYREF
  std::_Rb_tree_const_iterator<CrossTower::PlayerScore*> RandIt; // [rsp+1D0h] [rbp-90h] BYREF
  std::pair<std::_Rb_tree_const_iterator<CrossTower::PlayerScore*>,bool> pair5; // [rsp+1E0h] [rbp-80h]
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > it; // [rsp+1F0h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CrossTower::PlayerScore> > v22; // [rsp+200h] [rbp-60h] BYREF
  CrossTower::PlayerScore *__x; // [rsp+208h] [rbp-58h] BYREF
  std::_Rb_tree_const_iterator<CrossTower::PlayerScore*> v24; // [rsp+210h] [rbp-50h] BYREF
  _BYTE v25[16]; // [rsp+220h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<CrossTower::PlayerScore*> v26; // [rsp+230h] [rbp-30h] BYREF
  _BYTE v27[32]; // [rsp+240h] [rbp-20h] BYREF

  if ( this->m_NewWinerId <= 0 && this->m_State == 3 )
  {
    std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::set(&ScoreRank);
    for ( it._M_node = std::map<long,CrossTower::PlayerScore>::begin(&this->m_mPlayerScore)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator++(&it, 0) )
    {
      v22._M_node = std::map<long,CrossTower::PlayerScore>::end(&this->m_mPlayerScore)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator!=(&it, &v22) )
        break;
      if ( std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.nCurMapId == 60029
        && std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second.bInActivity )
      {
        __x = &std::_Rb_tree_iterator<std::pair<long const,CrossTower::PlayerScore>>::operator->(&it)->second;
        pair5 = std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::insert(
                  &ScoreRank,
                  &__x);
      }
    }
    if ( IsTimeEnd )
    {
      RandIt._M_node = std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::begin(&ScoreRank)._M_node;
      v24._M_node = std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::end(&ScoreRank)._M_node;
      if ( std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator!=(&RandIt, &v24) )
      {
        v3 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
          v15,
          (unsigned int)v3);
        p_strName = &(*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt))->strName;
        nSid = (*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt))->nSid;
        v6 = std::operator<<<std::char_traits<char>>(v16, "s");
        v7 = std::ostream::operator<<(v6, nSid);
        v8 = std::operator<<<std::char_traits<char>>(v7, ".");
        std::operator<<<char>(v8, p_strName);
        this->m_NewWinerId = **(_QWORD **)std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt);
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(v25, v15);
        std::string::operator=(&this->m_NewWinerName, v25);
        std::string::~string(v25);
        this->m_ConnId = (*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt))->nConnId;
        this->m_Battle = (*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt))->nBattle;
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v15);
      }
    }
    else if ( std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::size(&ScoreRank) == 1 )
    {
      RandIt_0._M_node = std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::begin(&ScoreRank)._M_node;
      v26._M_node = std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::end(&ScoreRank)._M_node;
      if ( std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator!=(&RandIt_0, &v26) )
      {
        v9 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
          v15,
          (unsigned int)v9);
        v10 = &(*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt_0))->strName;
        v11 = (*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt_0))->nSid;
        v12 = std::operator<<<std::char_traits<char>>(v16, "s");
        v13 = std::ostream::operator<<(v12, v11);
        v14 = std::operator<<<std::char_traits<char>>(v13, ".");
        std::operator<<<char>(v14, v10);
        this->m_NewWinerId = **(_QWORD **)std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt_0);
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(v27, v15);
        std::string::operator=(&this->m_NewWinerName, v27);
        std::string::~string(v27);
        this->m_ConnId = (*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt_0))->nConnId;
        this->m_Battle = (*std::_Rb_tree_const_iterator<CrossTower::PlayerScore *>::operator*(&RandIt_0))->nBattle;
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v15);
      }
    }
    std::set<CrossTower::PlayerScore *,CrossTower::PlayerScoreGreater,std::allocator<CrossTower::PlayerScore *>>::~set(&ScoreRank);
  }
}


#####################################
void __cdecl CrossTower::SetWinnerInfo(CrossTower *const this, CharId_t Winner, std::string *p_sName)
{
  std::string p_strFamilyName; // [rsp+20h] [rbp-20h] BYREF

  this->m_WinerId = Winner;
  std::string::operator=(&this->m_WinerName, p_sName);
  if ( this->m_Monster )
  {
    std::string::string(&p_strFamilyName, &this->m_WinerName);
    Monster::SetFamilyId(this->m_Monster, 0, &p_strFamilyName);
    std::string::~string(&p_strFamilyName);
  }
}


