// Decompiled methods for class: CWorldBoss
// Source: gameserver.cc
// Total methods: 21

#####################################
void __cdecl CWorldBoss::Init(CWorldBoss *const this, int32_t line)
{
  CTimer *v2; // rax
  CfgData *v3; // rax
  BossInfoMap *BossInfoMap; // rax
  int first; // ebx
  CfgData *v6; // rax
  int32_t monsterid; // ebx
  CfgData *v8; // rax
  int32_t boss_sign; // r12d
  int32_t revive_time; // ebx
  CfgData *v11; // rax
  std::pair<const int,BossInfo> *v12; // rdx
  WorldBossInfo *v13; // rax
  WorldBossInfo stu; // [rsp+10h] [rbp-120h] BYREF
  BossInfoMap BossMap; // [rsp+B0h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossInfo> > it; // [rsp+E0h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BossInfo> > __x; // [rsp+F0h] [rbp-40h] BYREF
  int32_t nNowTime; // [rsp+104h] [rbp-2Ch]
  CfgMapMonster *pCfgMapMonster; // [rsp+108h] [rbp-28h]
  CfgMonster *pMonster; // [rsp+110h] [rbp-20h]
  int32_t ReviveTime; // [rsp+11Ch] [rbp-14h]

  if ( line != 9 )
  {
    v2 = Answer::Singleton<CTimer>::instance();
    nNowTime = CTimer::GetNow(v2);
    v3 = Answer::Singleton<CfgData>::instance();
    BossInfoMap = CfgData::GetBossInfoMap(v3);
    std::map<int,BossInfo>::map(&BossMap, BossInfoMap);
    for ( it._M_node = std::map<int,BossInfo>::begin(&BossMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,BossInfo>>::operator++(&it) )
    {
      __x._M_node = std::map<int,BossInfo>::end(&BossMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,BossInfo>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,BossInfo>>::operator->(&it)->first;
      v6 = Answer::Singleton<CfgData>::instance();
      pCfgMapMonster = CfgData::GetMapMonsterInfo(v6, first);
      if ( pCfgMapMonster )
      {
        monsterid = pCfgMapMonster->monsterid;
        v8 = Answer::Singleton<CfgData>::instance();
        pMonster = CfgData::getMonster(v8, monsterid);
        if ( pMonster )
        {
          WorldBossInfo::WorldBossInfo(&stu);
          stu.nBossId = std::_Rb_tree_iterator<std::pair<int const,BossInfo>>::operator->(&it)->first;
          stu.nMid = pMonster->mid;
          stu.nBossType = pMonster->boss_sign;
          stu.nMapId = pCfgMapMonster->mapid;
          stu.nLevel = 1;
          if ( stu.nBossType == 3 )
          {
            stu.nState = 3;
            stu.nReviveTime = 0;
          }
          else
          {
            stu.nState = 0;
            ReviveTime = CWorldBoss::GetBossRevieTime(this, stu.nBossId);
            if ( ReviveTime <= 0 )
            {
              boss_sign = pMonster->boss_sign;
              revive_time = pMonster->revive_time;
              v11 = Answer::Singleton<CfgData>::instance();
              ReviveTime = CfgData::GetMonsterReviveTime(v11, revive_time, boss_sign) / 1000;
            }
            stu.nReviveTime = nNowTime + ReviveTime;
          }
          v12 = std::_Rb_tree_iterator<std::pair<int const,BossInfo>>::operator->(&it);
          v13 = std::map<int,WorldBossInfo>::operator[](&this->m_mBossMap, &v12->first);
          WorldBossInfo::operator=(v13, &stu);
          WorldBossInfo::~WorldBossInfo(&stu);
        }
      }
    }
    CWorldBoss::InitDBInfo(this);
    CWorldBoss::InitDropRecord(this);
    std::map<int,BossInfo>::~map(&BossMap);
  }
}


#####################################
void __cdecl CWorldBoss::InitDBInfo(CWorldBoss *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  std::pair<const int,WorldBossInfo> *v3; // rbx
  std::pair<const int,WorldBossInfo> *v4; // rbx
  std::pair<const int,WorldBossInfo> *v5; // rbx
  const char *StringValue; // rbx
  std::pair<const int,WorldBossInfo> *v7; // rax
  std::pair<const int,WorldBossInfo> *v8; // rbx
  std::pair<const int,WorldBossInfo> *v9; // rbx
  const char *v10; // rbx
  std::pair<const int,WorldBossInfo> *v11; // rax
  std::pair<const int,WorldBossInfo> *v12; // rbx
  std::pair<const int,WorldBossInfo> *v13; // rbx
  const char *v14; // rbx
  std::pair<const int,WorldBossInfo> *v15; // rax
  std::pair<const int,WorldBossInfo> *v16; // rbx
  std::pair<const int,WorldBossInfo> *v17; // rbx
  const char *v18; // rbx
  std::pair<const int,WorldBossInfo> *v19; // rax
  std::pair<const int,WorldBossInfo> *v20; // rbx
  std::pair<const int,WorldBossInfo> *v21; // rbx
  const char *v22; // rbx
  std::pair<const int,WorldBossInfo> *v23; // rax
  std::pair<const int,WorldBossInfo> *v24; // rbx
  MemPetDBData pet; // [rsp+10h] [rbp-B0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > iter; // [rsp+70h] [rbp-50h] BYREF
  int32_t nBossId; // [rsp+7Ch] [rbp-44h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+A0h] [rbp-20h] BYREF

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  v2 = Answer::MySqlDBGuard::query(&db, "SELECT * FROM `mem_world_boss_info`");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  MemPetDBData::MemPetDBData(&pet);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    nBossId = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    iter._M_node = std::map<int,WorldBossInfo>::find(&this->m_mBossMap, &nBossId)._M_node;
    __x._M_node = std::map<int,WorldBossInfo>::end(&this->m_mBossMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&iter, &__x) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v3->second.nLevel = Answer::MySqlQuery::getIntValue(&result, "level", 0);
      v4 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v4->second.nExp = Answer::MySqlQuery::getIntValue(&result, "exp", 0);
      v5 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v5->second.vKiller[0].nCharId = Answer::MySqlQuery::getInt64Value(&result, "killer1", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "killer_name1", &byte_8F560F);
      v7 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      std::string::operator=(&v7->second.vKiller[0].strName, StringValue);
      v8 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v8->second.vKiller[0].nTime = Answer::MySqlQuery::getIntValue(&result, "kill_time1", 0);
      v9 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v9->second.vKiller[1].nCharId = Answer::MySqlQuery::getInt64Value(&result, "killer2", 0);
      v10 = Answer::MySqlQuery::getStringValue(&result, "killer_name2", &byte_8F560F);
      v11 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      std::string::operator=(&v11->second.vKiller[1].strName, v10);
      v12 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v12->second.vKiller[1].nTime = Answer::MySqlQuery::getIntValue(&result, "kill_time2", 0);
      v13 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v13->second.vKiller[2].nCharId = Answer::MySqlQuery::getInt64Value(&result, "killer3", 0);
      v14 = Answer::MySqlQuery::getStringValue(&result, "killer_name3", &byte_8F560F);
      v15 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      std::string::operator=(&v15->second.vKiller[2].strName, v14);
      v16 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v16->second.vKiller[2].nTime = Answer::MySqlQuery::getIntValue(&result, "kill_time3", 0);
      v17 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v17->second.vKiller[3].nCharId = Answer::MySqlQuery::getInt64Value(&result, "killer4", 0);
      v18 = Answer::MySqlQuery::getStringValue(&result, "killer_name4", &byte_8F560F);
      v19 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      std::string::operator=(&v19->second.vKiller[3].strName, v18);
      v20 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v20->second.vKiller[3].nTime = Answer::MySqlQuery::getIntValue(&result, "kill_time4", 0);
      v21 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v21->second.vKiller[4].nCharId = Answer::MySqlQuery::getInt64Value(&result, "killer5", 0);
      v22 = Answer::MySqlQuery::getStringValue(&result, "killer_name5", &byte_8F560F);
      v23 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      std::string::operator=(&v23->second.vKiller[4].strName, v22);
      v24 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v24->second.vKiller[4].nTime = Answer::MySqlQuery::getIntValue(&result, "kill_time5", 0);
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  MemPetDBData::~MemPetDBData(&pet);
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CWorldBoss::PacketBossInfo(CWorldBoss *const this, Answer::NetPacket *packet, int8_t nBossType)
{
  CTimer *v3; // rax
  int first; // ebx
  CfgData *v5; // rax
  WorldBossInfo *p_second; // rcx
  std::_Rb_tree_const_iterator<std::pair<const int,WorldBossInfo> > mapIter; // [rsp+20h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __it; // [rsp+30h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > v11; // [rsp+50h] [rbp-30h] BYREF
  int32_t nSize; // [rsp+58h] [rbp-28h]
  int32_t nNowTime; // [rsp+5Ch] [rbp-24h]
  int32_t nOldOffset; // [rsp+60h] [rbp-20h]
  int32_t nNewOffset; // [rsp+64h] [rbp-1Ch]

  if ( packet )
  {
    nSize = 0;
    v3 = Answer::Singleton<CTimer>::instance();
    nNowTime = CTimer::GetNow(v3);
    nOldOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt32(packet, 0);
    Answer::NetPacket::writeInt8(packet, nBossType);
    __it._M_node = std::map<int,WorldBossInfo>::begin(&this->m_mBossMap)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::_Rb_tree_const_iterator(&mapIter, &__it);
    while ( 1 )
    {
      v11._M_node = std::map<int,WorldBossInfo>::end(&this->m_mBossMap)._M_node;
      std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::_Rb_tree_const_iterator(&__x, &v11);
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&mapIter, &__x) )
        break;
      if ( std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::operator->(&mapIter)->second.nBossType == nBossType )
      {
        first = std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::operator->(&mapIter)->first;
        v5 = Answer::Singleton<CfgData>::instance();
        if ( CfgData::GetBossInfo(v5, first) )
        {
          p_second = &std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::operator->(&mapIter)->second;
          WorldBossInfo::PackageBossInfo(p_second, packet, nNowTime);
          ++nSize;
        }
      }
      std::_Rb_tree_const_iterator<std::pair<int const,WorldBossInfo>>::operator++(&mapIter);
    }
    nNewOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, nOldOffset);
    Answer::NetPacket::writeInt32(packet, nSize);
    Answer::NetPacket::setWOffset(packet, nNewOffset);
  }
}


#####################################
void __cdecl CWorldBoss::broadcastBossKilled(
        CWorldBoss *const this,
        int32_t Mid,
        std::string *p_KillerName,
        CharId_t KillerId)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x2CB3u);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 0);
    Answer::NetPacket::writeInt32(packet, Mid);
    Answer::NetPacket::writeUTF8(packet, p_KillerName);
    Answer::NetPacket::writeInt64(packet, KillerId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v6, packet);
  }
}


#####################################
void __cdecl CWorldBoss::broadcastBossRevive(CWorldBoss *const this, int32_t Mid, int32_t BossId, int32_t MapId)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x2CB3u);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 1);
    Answer::NetPacket::writeInt32(packet, Mid);
    Answer::NetPacket::writeInt32(packet, BossId);
    Answer::NetPacket::writeInt32(packet, MapId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v6, packet);
  }
}


#####################################
void __cdecl CWorldBoss::GetWorldBossIcon(CWorldBoss *const this, IconStateList *const IconList)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  *(_QWORD *)&stu.nId = 0x200000009LL;
  *(_QWORD *)&stu.nLeftTime = 0xFFFFFFFFLL;
  *(_QWORD *)&stu.nIconRight = 0;
  std::list<ShowIcon>::push_back(IconList, &stu);
}


#####################################
void __cdecl CWorldBoss::SendWorldBossIcon(CWorldBoss *const this, Player *pPlayer)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( pPlayer )
  {
    *(_QWORD *)&stu.nId = 0x200000009LL;
    *(_QWORD *)&stu.nLeftTime = 0xFFFFFFFFLL;
    *(_QWORD *)&stu.nIconRight = 0;
    Player::SendIconState(pPlayer, &stu);
  }
}


#####################################
void __cdecl CWorldBoss::Update(CWorldBoss *const this, int64_t CurTick)
{
  if ( CurTick - this->m_lastUpdateTick > 1000 )
    this->m_lastUpdateTick = CurTick;
}


#####################################
int32_t __cdecl CWorldBoss::GetBossLevel(CWorldBoss *const this, int32_t id)
{
  int32_t nLevel; // ebx
  int32_t ida; // [rsp+4h] [rbp-4Ch] BYREF
  CWorldBoss *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  ida = id;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
  iter._M_node = std::map<int,WorldBossInfo>::find(&this->m_mBossMap, &ida)._M_node;
  __x._M_node = std::map<int,WorldBossInfo>::end(&thisa->m_mBossMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&iter, &__x) )
    nLevel = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nLevel;
  else
    nLevel = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return nLevel;
}


#####################################
void __cdecl CWorldBoss::adjustBossAttr(CWorldBoss *const this, CfgMonster *const cfgMonster, int32_t nLevel)
{
  int32_t mid; // ebx
  CfgData *v4; // rax
  CfgMonsterAdjust *pCfgAdjust; // [rsp+20h] [rbp-20h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  mid = cfgMonster->mid;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgAdjust = CfgData::GetMonsterAdjust(v4, mid, nLevel, 0);
  if ( pCfgAdjust )
  {
    cfgMonster->level = pCfgAdjust->level;
    for ( i = 0; i <= 49; ++i )
      cfgMonster->vAttr[i] = pCfgAdjust->vAttr[i];
  }
}


#####################################
void __cdecl CWorldBoss::OnAddBoss(
        CWorldBoss *const this,
        Map *pMap,
        const CfgMonster *const cfgMonster,
        const CfgMapMonster *const cfgMapMonster)
{
  GameService *v4; // rax
  CPoolManager *v6; // rax
  std::pair<const int,WorldBossInfo> *v7; // rax
  CfgMonster t_cfgMonster; // [rsp+20h] [rbp-310h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > iter; // [rsp+2C0h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+2D0h] [rbp-60h] BYREF
  int32_t nBossId; // [rsp+2DCh] [rbp-54h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+2E0h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+300h] [rbp-30h] BYREF
  int32_t nLevel; // [rsp+310h] [rbp-20h]
  int8_t nState; // [rsp+317h] [rbp-19h]
  Monster *monster; // [rsp+318h] [rbp-18h]

  if ( pMap )
  {
    nBossId = cfgMapMonster->id;
    nLevel = CWorldBoss::GetBossLevel(this, nBossId);
    if ( nLevel <= 0 || (v4 = Answer::Singleton<GameService>::instance(), GameService::getLine(v4) == 1) )
    {
      CfgMonster::CfgMonster(&t_cfgMonster, cfgMonster);
      nState = 0;
      v6 = Answer::Singleton<CPoolManager>::instance();
      monster = CPoolManager::pop<Monster>(v6);
      if ( monster )
      {
        if ( nLevel > 0 )
          CWorldBoss::adjustBossAttr(this, &t_cfgMonster, nLevel);
        if ( t_cfgMonster.boss_sign != 3 )
        {
          std::vector<AttrAddon>::vector(&vAttrAddon);
          Monster::init(monster, &t_cfgMonster, cfgMapMonster, MonsterState::MS_STAND, &vAttrAddon);
          std::vector<AttrAddon>::~vector(&vAttrAddon);
        }
        (*((void (__fastcall **)(Map *, Monster *, _QWORD, _QWORD))pMap->_vptr_Map + 28))(
          pMap,
          monster,
          (unsigned int)cfgMapMonster->x,
          (unsigned int)cfgMapMonster->y);
        Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
        iter._M_node = std::map<int,WorldBossInfo>::find(&this->m_mBossMap, &nBossId)._M_node;
        __x._M_node = std::map<int,WorldBossInfo>::end(&this->m_mBossMap)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&iter, &__x) )
        {
          v7 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
          v7->second.nState = nState;
        }
        Answer::MutexGuard::~MutexGuard(&lock);
      }
      CfgMonster::~CfgMonster(&t_cfgMonster);
    }
  }
}


#####################################
void __cdecl CWorldBoss::OnBossSummon(CWorldBoss *const this, int32_t nBossId, Map *pMap, Monster *pMonster)
{
  std::pair<const int,WorldBossInfo> *v4; // rax
  int32_t nBossIda; // [rsp+14h] [rbp-ECh] BYREF
  CWorldBoss *thisa; // [rsp+18h] [rbp-E8h]
  WorldBossInfo info; // [rsp+20h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > iter; // [rsp+C0h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+D0h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+E0h] [rbp-20h] BYREF
  bool bFind; // [rsp+EFh] [rbp-11h]

  thisa = this;
  nBossIda = nBossId;
  if ( pMonster )
  {
    WorldBossInfo::WorldBossInfo(&info);
    bFind = 0;
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_Lock);
    iter._M_node = std::map<int,WorldBossInfo>::find(&thisa->m_mBossMap, &nBossIda)._M_node;
    __x._M_node = std::map<int,WorldBossInfo>::end(&thisa->m_mBossMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&iter, &__x) )
    {
      std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nState = 0;
      v4 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      WorldBossInfo::operator=(&info, &v4->second);
      bFind = 1;
    }
    Answer::MutexGuard::~MutexGuard(&lock);
    if ( bFind )
    {
      CWorldBoss::broadcastBossRevive(thisa, info.nMid, info.nBossId, info.nMapId);
      CWorldBoss::saveBossInfo(thisa, &info);
    }
    WorldBossInfo::~WorldBossInfo(&info);
  }
}


#####################################
void __cdecl CWorldBoss::OnBossKilled(
        CWorldBoss *const this,
        int32_t id,
        int32_t nowTime,
        Map *pMap,
        Monster *pMonster,
        Player *pKiller)
{
  std::pair<const int,WorldBossInfo> *v6; // rax
  int32_t nLevel; // r12d
  int32_t nMid; // ebx
  CfgData *v9; // rax
  int32_t v10; // r12d
  int32_t v11; // ebx
  CfgData *v12; // rax
  std::pair<const int,WorldBossInfo> *v13; // rax
  std::pair<const int,WorldBossInfo> *v14; // rax
  std::pair<const int,WorldBossInfo> *v15; // rax
  std::pair<const int,WorldBossInfo> *v16; // rax
  std::pair<const int,WorldBossInfo> *v17; // rax
  int32_t v18; // ebx
  CfgData *v19; // rax
  int32_t boss_sign; // r12d
  int32_t revive_time; // ebx
  CfgData *v22; // rax
  std::pair<const int,WorldBossInfo> *v23; // rax
  std::pair<const int,WorldBossInfo> *v24; // rax
  int32_t v25; // ebx
  CfgData *v26; // rax
  CharId_t Cid; // r12
  CharId_t v28; // r12
  CTimer *v29; // rax
  int32_t Now; // eax
  int32_t ida; // [rsp+24h] [rbp-3FCh] BYREF
  CWorldBoss *thisa; // [rsp+28h] [rbp-3F8h]
  CfgMonster cfgMonster; // [rsp+30h] [rbp-3F0h] BYREF
  WorldBossInfo info; // [rsp+2D0h] [rbp-150h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > iter; // [rsp+370h] [rbp-B0h] BYREF
  Answer::MutexGuard lock; // [rsp+380h] [rbp-A0h] BYREF
  KillerInfo killer; // [rsp+390h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+3B0h] [rbp-70h] BYREF
  _BYTE v43[16]; // [rsp+3C0h] [rbp-60h] BYREF
  std::string p_KillerName; // [rsp+3D0h] [rbp-50h] BYREF
  std::string v45; // [rsp+3E0h] [rbp-40h] BYREF
  bool bFind; // [rsp+3EAh] [rbp-36h]
  bool bLevelUp; // [rsp+3EBh] [rbp-35h]
  int32_t nReviveTime; // [rsp+3ECh] [rbp-34h]
  CfgMonsterAdjust *pCfgAdjust; // [rsp+3F0h] [rbp-30h]
  CfgMonsterAdjust *pNext; // [rsp+3F8h] [rbp-28h]
  CfgMonster *pMonster_0; // [rsp+400h] [rbp-20h]
  CfgMonster *pCfgMonster; // [rsp+408h] [rbp-18h]

  thisa = this;
  ida = id;
  if ( pMap && pMonster )
  {
    WorldBossInfo::WorldBossInfo(&info);
    memset(&killer, 0, 20);
    std::string::string(&killer.strName);
    bFind = 0;
    bLevelUp = 0;
    Answer::MutexGuard::MutexGuard(&lock, &thisa->m_Lock);
    iter._M_node = std::map<int,WorldBossInfo>::find(&thisa->m_mBossMap, &ida)._M_node;
    __x._M_node = std::map<int,WorldBossInfo>::end(&thisa->m_mBossMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&iter, &__x) )
    {
      if ( pKiller )
      {
        std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nState = 1;
        killer.nCharId = Player::getCid(pKiller);
        Player::getName((const Player *const)v43);
        std::string::operator=(&killer.strName, v43);
        std::string::~string(v43);
        killer.nTime = nowTime;
        v6 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
        WorldBossInfo::AddKiller(&v6->second, &killer);
        nLevel = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nLevel;
        nMid = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nMid;
        v9 = Answer::Singleton<CfgData>::instance();
        pCfgAdjust = CfgData::GetMonsterAdjust(v9, nMid, nLevel, 0);
        v10 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nLevel + 1;
        v11 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nMid;
        v12 = Answer::Singleton<CfgData>::instance();
        pNext = CfgData::GetMonsterAdjust(v12, v11, v10, 0);
        if ( pCfgAdjust )
        {
          if ( pNext )
          {
            v13 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
            ++v13->second.nExp;
            v14 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
            if ( v14->second.nExp >= pCfgAdjust->exp )
            {
              bLevelUp = 1;
              v15 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
              ++v15->second.nLevel;
              v16 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
              v16->second.nExp -= pCfgAdjust->exp;
            }
          }
        }
      }
      else
      {
        std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nState = 2;
      }
      v17 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      nReviveTime = CWorldBoss::GetBossRevieTime(thisa, v17->second.nBossId);
      if ( nReviveTime <= 0 )
      {
        v18 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second.nMid;
        v19 = Answer::Singleton<CfgData>::instance();
        pMonster_0 = CfgData::getMonster(v19, v18);
        if ( pMonster_0 )
        {
          boss_sign = pMonster_0->boss_sign;
          revive_time = pMonster_0->revive_time;
          v22 = Answer::Singleton<CfgData>::instance();
          nReviveTime = CfgData::GetMonsterReviveTime(v22, revive_time, boss_sign) / 1000;
        }
      }
      v23 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      v23->second.nReviveTime = nowTime + nReviveTime;
      v24 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter);
      WorldBossInfo::operator=(&info, &v24->second);
      bFind = 1;
    }
    Answer::MutexGuard::~MutexGuard(&lock);
    if ( bFind )
    {
      if ( bLevelUp )
      {
        v25 = info.nMid;
        v26 = Answer::Singleton<CfgData>::instance();
        pCfgMonster = CfgData::getMonster(v26, v25);
        if ( pCfgMonster )
        {
          CfgMonster::CfgMonster(&cfgMonster, pCfgMonster);
          CWorldBoss::adjustBossAttr(thisa, &cfgMonster, info.nLevel);
          Monster::OnLevelUp(pMonster, &cfgMonster);
          CfgMonster::~CfgMonster(&cfgMonster);
        }
      }
      Monster::SetReviveTime(pMonster, info.nReviveTime);
      if ( info.nBossType == 3 && pKiller )
      {
        Cid = Player::getCid(pKiller);
        Player::getName((const Player *const)&p_KillerName);
        CWorldBoss::broadcastBossKilled(thisa, info.nMid, &p_KillerName, Cid);
        std::string::~string(&p_KillerName);
      }
      if ( info.nBossType == 1 )
      {
        if ( pKiller )
        {
          v28 = Player::getCid(pKiller);
          Player::getName((const Player *const)&v45);
          CWorldBoss::broadcastBossKilled(thisa, info.nMid, &v45, v28);
          std::string::~string(&v45);
        }
      }
      else if ( info.nBossType == 12 )
      {
        v29 = Answer::Singleton<CTimer>::instance();
        Now = CTimer::GetNow(v29);
        CWorldBoss::UpdateRuinsBossInfo(thisa, pMap, &info, Now);
      }
      CWorldBoss::saveBossInfo(thisa, &info);
    }
    KillerInfo::~KillerInfo(&killer);
    WorldBossInfo::~WorldBossInfo(&info);
  }
}


#####################################
void __cdecl CWorldBoss::UpdateWorldBossInfo(CWorldBoss *const this, WorldBossInfo *const info)
{
  WorldBossInfo *p_second; // rdx
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+30h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
  iter._M_node = std::map<int,WorldBossInfo>::find(&this->m_mBossMap, &info->nBossId)._M_node;
  __x._M_node = std::map<int,WorldBossInfo>::end(&this->m_mBossMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&iter, &__x) )
  {
    p_second = &std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&iter)->second;
    WorldBossInfo::operator=(p_second, info);
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CWorldBoss::saveBossInfo(CWorldBoss *const this, const WorldBossInfo *const info)
{
  DBService *v2; // rax

  v2 = Answer::Singleton<DBService>::instance();
  DBService::SaveWorldBossInfo(v2, info);
}


#####################################
void __cdecl CWorldBoss::InitDropRecord(CWorldBoss *const this)
{
  Answer::DBPool *v1; // rax
  Answer::MySqlQuery *v2; // rax
  const char *StringValue; // rax
  int v4; // ebx
  Answer::MySqlQuery *v5; // rax
  const char *v6; // rax
  int v7; // ebx
  DropRecord record; // [rsp+20h] [rbp-B0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+50h] [rbp-80h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-50h] BYREF
  std::string name; // [rsp+A0h] [rbp-30h] BYREF
  char v12; // [rsp+AFh] [rbp-21h] BYREF
  std::string v13; // [rsp+B0h] [rbp-20h] BYREF
  char v14; // [rsp+BBh] [rbp-15h] BYREF
  int32_t nSize; // [rsp+BCh] [rbp-14h]

  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  nSize = 0;
  v2 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_drop_record` WHERE `special`=1 ORDER BY `time` DESC LIMIT 5");
  Answer::MySqlQuery::MySqlQuery(&result, v2);
  do
  {
    if ( Answer::MySqlQuery::eof(&result) )
      break;
    std::allocator<char>::allocator(&v12);
    std::string::string(&name, &byte_8F560F);
    DropRecord::DropRecord(&record, &name, 0, 0, 0, 0, 0, 0);
    std::string::~string(&name);
    std::allocator<char>::~allocator(&v12);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8F560F);
    std::string::operator=(&record, StringValue);
    record.nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    record.nMapId = Answer::MySqlQuery::getIntValue(&result, "mapid", 0);
    record.nMid = Answer::MySqlQuery::getIntValue(&result, "mid", 0);
    record.nRecord = Answer::MySqlQuery::getIntValue(&result, "record", 0);
    record.nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    record.nSpecial = Answer::MySqlQuery::getIntValue(&result, "special", 0);
    std::list<DropRecord>::push_back(&this->m_dropRecordsSpecial, &record);
    if ( ++nSize <= 4 )
    {
      Answer::MySqlQuery::nextRow(&result);
      v4 = 1;
    }
    else
    {
      v4 = 0;
    }
    DropRecord::~DropRecord(&record);
  }
  while ( v4 );
  v5 = Answer::MySqlDBGuard::query(
         &db,
         "SELECT * FROM `mem_drop_record` WHERE `special`=0 ORDER BY `time` DESC LIMIT 30");
  Answer::MySqlQuery::operator=(&result, v5);
  do
  {
    if ( Answer::MySqlQuery::eof(&result) )
      break;
    std::allocator<char>::allocator(&v14);
    std::string::string(&v13, &byte_8F560F);
    DropRecord::DropRecord(&record, &v13, 0, 0, 0, 0, 0, 0);
    std::string::~string(&v13);
    std::allocator<char>::~allocator(&v14);
    v6 = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8F560F);
    std::string::operator=(&record, v6);
    record.nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    record.nMapId = Answer::MySqlQuery::getIntValue(&result, "mapid", 0);
    record.nMid = Answer::MySqlQuery::getIntValue(&result, "mid", 0);
    record.nRecord = Answer::MySqlQuery::getIntValue(&result, "record", 0);
    record.nTime = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    record.nSpecial = Answer::MySqlQuery::getIntValue(&result, "special", 0);
    std::list<DropRecord>::push_back(&this->m_dropRecords, &record);
    if ( ++nSize <= 29 )
    {
      Answer::MySqlQuery::nextRow(&result);
      v7 = 1;
    }
    else
    {
      v7 = 0;
    }
    DropRecord::~DropRecord(&record);
  }
  while ( v7 );
  Answer::MySqlQuery::~MySqlQuery(&result);
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CWorldBoss::AddDropRecord(
        CWorldBoss *const this,
        const std::string *const name,
        CharId_t cid,
        MapId_t mapid,
        int32_t mid,
        int32_t record,
        int32_t time)
{
  CfgData *v7; // rax
  size_t v8; // rbx
  DBService *v9; // rax
  DropRecord dropRecord; // [rsp+40h] [rbp-60h] BYREF
  Answer::MutexGuard lock_0; // [rsp+70h] [rbp-30h] BYREF
  Answer::MutexGuard lock; // [rsp+80h] [rbp-20h] BYREF
  const CfgDropRecord *pCfgRecord; // [rsp+88h] [rbp-18h]

  v7 = Answer::Singleton<CfgData>::instance();
  pCfgRecord = CfgData::GetDropRecord(v7, record);
  if ( pCfgRecord )
  {
    DropRecord::DropRecord(&dropRecord, name, cid, mapid, mid, record, time, pCfgRecord->nSpecial);
    if ( pCfgRecord->nSpecial )
    {
      Answer::MutexGuard::MutexGuard(&lock_0, &this->m_RecordLock);
      std::list<DropRecord>::push_front(&this->m_dropRecordsSpecial, &dropRecord);
      if ( std::list<DropRecord>::size(&this->m_dropRecordsSpecial) > 5 )
        std::list<DropRecord>::pop_back(&this->m_dropRecordsSpecial);
      Answer::MutexGuard::~MutexGuard(&lock_0);
    }
    else
    {
      Answer::MutexGuard::MutexGuard(&lock, &this->m_RecordLock);
      std::list<DropRecord>::push_front(&this->m_dropRecords, &dropRecord);
      v8 = std::list<DropRecord>::size(&this->m_dropRecords);
      if ( v8 + std::list<DropRecord>::size(&this->m_dropRecordsSpecial) > 0x1E )
        std::list<DropRecord>::pop_back(&this->m_dropRecords);
      Answer::MutexGuard::~MutexGuard(&lock);
    }
    v9 = Answer::Singleton<DBService>::instance();
    DBService::SaveDropRecord(v9, &dropRecord);
    DropRecord::~DropRecord(&dropRecord);
  }
}


#####################################
void __cdecl CWorldBoss::SendDropRecord(CWorldBoss *const this, int8_t connid, int16_t nGateIndex)
{
  GameService *v3; // rax
  __int16 v4; // bx
  __int16 v5; // ax
  const DropRecord *v6; // rax
  const DropRecord *v7; // rax
  const DropRecord *v8; // rax
  const DropRecord *v9; // rax
  const DropRecord *v10; // rax
  const DropRecord *v11; // rax
  const DropRecord *v12; // rax
  const DropRecord *v13; // rax
  const DropRecord *v14; // rax
  const DropRecord *v15; // rax
  const DropRecord *v16; // rax
  const DropRecord *v17; // rax
  uint32_t WOffset; // eax
  GameService *v19; // rax
  std::_List_const_iterator<DropRecord> iter_0; // [rsp+10h] [rbp-A0h] BYREF
  std::_List_const_iterator<DropRecord> iter; // [rsp+20h] [rbp-90h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-80h] BYREF
  std::_List_iterator<DropRecord> __x; // [rsp+40h] [rbp-70h] BYREF
  std::_List_const_iterator<DropRecord> v25; // [rsp+50h] [rbp-60h] BYREF
  std::_List_iterator<DropRecord> v26; // [rsp+60h] [rbp-50h] BYREF
  std::_List_iterator<DropRecord> v27; // [rsp+70h] [rbp-40h] BYREF
  std::_List_const_iterator<DropRecord> v28; // [rsp+80h] [rbp-30h] BYREF
  std::_List_iterator<DropRecord> v29; // [rsp+90h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, connid, Answer::PackType::PACK_DISPATCH, 0x2ED6u);
  if ( packet )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_RecordLock);
    v4 = std::list<DropRecord>::size(&this->m_dropRecords);
    v5 = std::list<DropRecord>::size(&this->m_dropRecordsSpecial);
    Answer::NetPacket::writeInt16(packet, v4 + v5);
    __x._M_node = std::list<DropRecord>::begin(&this->m_dropRecordsSpecial)._M_node;
    std::_List_const_iterator<DropRecord>::_List_const_iterator(&iter, &__x);
    while ( 1 )
    {
      v26._M_node = std::list<DropRecord>::end(&this->m_dropRecordsSpecial)._M_node;
      std::_List_const_iterator<DropRecord>::_List_const_iterator(&v25, &v26);
      if ( !std::_List_const_iterator<DropRecord>::operator!=(&iter, &v25) )
        break;
      v6 = std::_List_const_iterator<DropRecord>::operator->(&iter);
      Answer::NetPacket::writeInt32(packet, v6->nRecord);
      v7 = std::_List_const_iterator<DropRecord>::operator->(&iter);
      Answer::NetPacket::writeUTF8(packet, &v7->strName);
      v8 = std::_List_const_iterator<DropRecord>::operator->(&iter);
      Answer::NetPacket::writeInt64(packet, v8->nCharId);
      v9 = std::_List_const_iterator<DropRecord>::operator->(&iter);
      Answer::NetPacket::writeInt32(packet, v9->nMapId);
      v10 = std::_List_const_iterator<DropRecord>::operator->(&iter);
      Answer::NetPacket::writeInt32(packet, v10->nMid);
      v11 = std::_List_const_iterator<DropRecord>::operator->(&iter);
      Answer::NetPacket::writeInt32(packet, v11->nTime);
      std::_List_const_iterator<DropRecord>::operator++(&iter);
    }
    v27._M_node = std::list<DropRecord>::begin(&this->m_dropRecords)._M_node;
    std::_List_const_iterator<DropRecord>::_List_const_iterator(&iter_0, &v27);
    while ( 1 )
    {
      v29._M_node = std::list<DropRecord>::end(&this->m_dropRecords)._M_node;
      std::_List_const_iterator<DropRecord>::_List_const_iterator(&v28, &v29);
      if ( !std::_List_const_iterator<DropRecord>::operator!=(&iter_0, &v28) )
        break;
      v12 = std::_List_const_iterator<DropRecord>::operator->(&iter_0);
      Answer::NetPacket::writeInt32(packet, v12->nRecord);
      v13 = std::_List_const_iterator<DropRecord>::operator->(&iter_0);
      Answer::NetPacket::writeUTF8(packet, &v13->strName);
      v14 = std::_List_const_iterator<DropRecord>::operator->(&iter_0);
      Answer::NetPacket::writeInt64(packet, v14->nCharId);
      v15 = std::_List_const_iterator<DropRecord>::operator->(&iter_0);
      Answer::NetPacket::writeInt32(packet, v15->nMapId);
      v16 = std::_List_const_iterator<DropRecord>::operator->(&iter_0);
      Answer::NetPacket::writeInt32(packet, v16->nMid);
      v17 = std::_List_const_iterator<DropRecord>::operator->(&iter_0);
      Answer::NetPacket::writeInt32(packet, v17->nTime);
      std::_List_const_iterator<DropRecord>::operator++(&iter_0);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v19 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v19, connid, nGateIndex, packet);
  }
}


#####################################
int32_t __cdecl CWorldBoss::GetBossRevie(CWorldBoss *const this, int32_t mId)
{
  CTimer *v2; // rax
  CTimer *v3; // rax
  std::pair<const int,WorldBossInfo> *v4; // rax
  int32_t mIda; // [rsp+4h] [rbp-6Ch] BYREF
  CWorldBoss *thisa; // [rsp+8h] [rbp-68h]
  tm NowLocal; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > it; // [rsp+50h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+60h] [rbp-10h] BYREF
  int32_t ReviceTime; // [rsp+68h] [rbp-8h]
  int32_t NowTime; // [rsp+6Ch] [rbp-4h]

  thisa = this;
  mIda = mId;
  ReviceTime = 0;
  v2 = Answer::Singleton<CTimer>::instance();
  NowTime = CTimer::GetNow(v2);
  v3 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&NowLocal, v3);
  it._M_node = std::map<int,WorldBossInfo>::find(&this->m_mBossMap, &mIda)._M_node;
  __x._M_node = std::map<int,WorldBossInfo>::end(&thisa->m_mBossMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&it, &__x) )
  {
    if ( !std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it)->second.nState )
      return 0;
    v4 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it);
    return v4->second.nReviveTime - NowTime;
  }
  return ReviceTime;
}


#####################################
void __cdecl CWorldBoss::SendRuinsBossInfo(CWorldBoss *const this, Player *player, BossType nBossType, int32_t nMapId)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  CTimer *v6; // rax
  std::pair<const int,WorldBossInfo> *v8; // rax
  std::pair<const int,WorldBossInfo> *v9; // rax
  std::pair<const int,WorldBossInfo> *v10; // rax
  std::pair<const int,WorldBossInfo> *v11; // rax
  int32_t v12; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v15; // bl
  GameService *v16; // rax
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > it; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,WorldBossInfo> > __x; // [rsp+30h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]
  int8_t nSize; // [rsp+43h] [rbp-1Dh]
  int32_t NowTime; // [rsp+44h] [rbp-1Ch]
  int32_t OldOffset; // [rsp+48h] [rbp-18h]
  int32_t NewOffset; // [rsp+4Ch] [rbp-14h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDDu);
    if ( packet )
    {
      nSize = 0;
      v6 = Answer::Singleton<CTimer>::instance();
      NowTime = CTimer::GetNow(v6);
      OldOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt8(packet, 0);
      for ( it._M_node = std::map<int,WorldBossInfo>::begin(&this->m_mBossMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator++(&it) )
      {
        __x._M_node = std::map<int,WorldBossInfo>::end(&this->m_mBossMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator!=(&it, &__x) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it)->second.nBossType == nBossType
          && std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it)->second.nMapId == nMapId )
        {
          v8 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v8->second.nBossId);
          v9 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v9->second.nMid);
          v10 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v10->second.nMapId);
          if ( std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it)->second.nState )
          {
            v11 = std::_Rb_tree_iterator<std::pair<int const,WorldBossInfo>>::operator->(&it);
            v12 = v11->second.nReviveTime - NowTime;
          }
          else
          {
            v12 = 0;
          }
          Answer::NetPacket::writeInt32(packet, v12);
          ++nSize;
        }
      }
      NewOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, OldOffset);
      Answer::NetPacket::writeInt8(packet, nSize);
      Answer::NetPacket::setWOffset(packet, NewOffset);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v15 = Player::getConnId(player);
      v16 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v16, v15, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CWorldBoss::UpdateRuinsBossInfo(
        CWorldBoss *const this,
        Map *pMap,
        const WorldBossInfo *const info,
        int32_t nNowTime)
{
  GameService *v4; // rax
  int32_t v5; // eax
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  if ( pMap )
  {
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, Answer::PackType::PACK_DISPATCH, 0x2CDEu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, info->nBossId);
      Answer::NetPacket::writeInt32(packet, info->nMid);
      Answer::NetPacket::writeInt32(packet, info->nMapId);
      if ( info->nState )
        v5 = info->nReviveTime - nNowTime;
      else
        v5 = 0;
      Answer::NetPacket::writeInt32(packet, v5);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcast(pMap, packet);
    }
  }
}


