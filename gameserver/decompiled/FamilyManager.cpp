// Decompiled methods for class: FamilyManager
// Source: gameserver.cc
// Total methods: 13

#####################################
void __cdecl FamilyManager::Init(FamilyManager *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  CTimer *v4; // rax
  const char *StringValue; // rax
  Answer::MySqlQuery *v6; // rax
  char IntValue; // al
  FamilyInfo *v8; // rax
  Answer::MySqlQuery *v9; // rax
  FamilyDungeonStu *v10; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1100h] BYREF
  FamilyInfo info; // [rsp+1010h] [rbp-100h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1080h] [rbp-90h] BYREF
  FamilyId_t nFamilyId; // [rsp+10A8h] [rbp-68h] BYREF
  FamilyDungeonStu stu; // [rsp+10B0h] [rbp-60h]
  Answer::MySqlQuery Leaderdb; // [rsp+10C0h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+10E0h] [rbp-30h] BYREF
  int32_t nNowTime; // [rsp+10FCh] [rbp-14h]

  if ( line != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(szSQL, 0, sizeof(szSQL));
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `mem_family` WHERE `delflag`=0");
    v3 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    v4 = Answer::Singleton<CTimer>::instance();
    nNowTime = CTimer::GetNow(v4);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      FamilyInfo::FamilyInfo(&info);
      info.nId = Answer::MySqlQuery::getInt64Value(&result, "id", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", byte_8D80C0);
      std::string::operator=(&info.strName, StringValue);
      info.nLevel = Answer::MySqlQuery::getIntValue(&result, "level", 0);
      info.nMemberCard = Answer::MySqlQuery::getIntValue(&result, "member_card", 0);
      info.FamilyLeaderCid = Answer::MySqlQuery::getIntValue(&result, "leader_cid", 0);
      info.MedalLevel = Answer::MySqlQuery::getIntValue(&result, "medl_level", 0);
      info.Territory = Answer::MySqlQuery::getIntValue(&result, "territory_open", 0);
      bzero(szSQL, 0x1000u);
      snprintf(szSQL, 0xFFFu, "SELECT name FROM `mem_character` WHERE `cid`=%lld", info.FamilyLeaderCid);
      v6 = Answer::MySqlDBGuard::query(&db, szSQL);
      Answer::MySqlQuery::MySqlQuery(&Leaderdb, v6);
      if ( !Answer::MySqlQuery::eof(&Leaderdb) )
      {
        IntValue = Answer::MySqlQuery::getIntValue(&Leaderdb, "name", 0);
        std::string::operator=(&info.FamilyLeaderName, (unsigned int)IntValue);
      }
      v8 = std::map<long,FamilyInfo>::operator[](&this->m_mFamilyInfo, &info.nId);
      FamilyInfo::operator=(v8, &info);
      Answer::MySqlQuery::nextRow(&result);
      Answer::MySqlQuery::~MySqlQuery(&Leaderdb);
      FamilyInfo::~FamilyInfo(&info);
    }
    v9 = Answer::MySqlDBGuard::query(&db, "SELECT * FROM `mem_family_dungeon`");
    Answer::MySqlQuery::operator=(&result, v9);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      nFamilyId = Answer::MySqlQuery::getInt64Value(&result, "id", 0);
      stu.StartCounts = Answer::MySqlQuery::getIntValue(&result, "times", 0);
      stu.StartTime = Answer::MySqlQuery::getIntValue(&result, "start_time", 0);
      stu.nMaxHard = Answer::MySqlQuery::getIntValue(&result, "finish_hard", 0);
      v10 = std::map<long,FamilyDungeonStu>::operator[](&this->m_FamilyDungeonStuMap, &nFamilyId);
      *v10 = stu;
      Answer::MySqlQuery::nextRow(&result);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl FamilyManager::OnUpdateFamilyInfo(FamilyManager *const this, Answer::NetPacket *inPacket)
{
  FamilyInfo info; // [rsp+10h] [rbp-90h] BYREF
  int8_t nReason; // [rsp+8Fh] [rbp-11h]

  if ( inPacket )
  {
    nReason = Answer::NetPacket::readInt8(inPacket);
    FamilyInfo::FamilyInfo(&info);
    FamilyInfo::UnPackageData(&info, inPacket);
    switch ( nReason )
    {
      case 2:
        FamilyManager::updateFamilyInfo(this, &info);
        break;
      case 3:
        FamilyManager::deleteFamilyInfo(this, info.nId);
        break;
      case 1:
        FamilyManager::addFamilyInfo(this, &info);
        break;
    }
    FamilyInfo::~FamilyInfo(&info);
  }
}


#####################################
void __cdecl FamilyManager::OnInitFamilyInfo(FamilyManager *const this, Answer::NetPacket *inPacket)
{
  FamilyInfo info; // [rsp+10h] [rbp-90h] BYREF
  int32_t size; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( inPacket )
  {
    FamilyInfo::FamilyInfo(&info);
    size = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < size; ++i )
    {
      FamilyInfo::CleanUp(&info);
      FamilyInfo::UnPackageData(&info, inPacket);
      FamilyManager::addFamilyInfo(this, &info);
    }
    FamilyInfo::~FamilyInfo(&info);
  }
}


#####################################
void __cdecl FamilyManager::addFamilyInfo(FamilyManager *const this, const FamilyInfo *const info)
{
  FamilyInfo *v2; // rax
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  if ( !FamilyInfo::IsEmpty(info) )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
    v2 = std::map<long,FamilyInfo>::operator[](&this->m_mFamilyInfo, &info->nId);
    FamilyInfo::operator=(v2, info);
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl FamilyManager::updateFamilyInfo(FamilyManager *const this, const FamilyInfo *const info)
{
  FamilyInfo *p_second; // rdx
  std::_Rb_tree_iterator<std::pair<const long int,FamilyInfo> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyInfo> > __x; // [rsp+30h] [rbp-20h] BYREF

  if ( !FamilyInfo::IsEmpty(info) )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
    iter._M_node = std::map<long,FamilyInfo>::find(&this->m_mFamilyInfo, &info->nId)._M_node;
    __x._M_node = std::map<long,FamilyInfo>::end(&this->m_mFamilyInfo)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,FamilyInfo>>::operator!=(&iter, &__x) )
    {
      p_second = &std::_Rb_tree_iterator<std::pair<long const,FamilyInfo>>::operator->(&iter)->second;
      FamilyInfo::operator=(p_second, info);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl FamilyManager::deleteFamilyInfo(FamilyManager *const this, FamilyId_t nFamilyId)
{
  FamilyId_t nFamilyIda; // [rsp+0h] [rbp-30h] BYREF
  FamilyManager *thisa; // [rsp+8h] [rbp-28h]
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
  std::map<long,FamilyInfo>::erase(&this->m_mFamilyInfo, &nFamilyIda);
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl FamilyManager::SendSocialFinishBoss(
        FamilyManager *const this,
        FamilyId_t nFamilyId,
        int32_t ActId,
        int8_t result)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, 0, Answer::PackType::PACK_DISPATCH, 0x4E50u);
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, nFamilyId);
    Answer::NetPacket::writeInt32(packet, ActId);
    Answer::NetPacket::writeInt8(packet, result);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v6, 0, packet);
  }
}


#####################################
int8_t __cdecl FamilyManager::GetTerritoryState(FamilyManager *const this, FamilyId_t nFamilyId)
{
  int8_t Territory; // bl
  FamilyId_t nFamilyIda; // [rsp+0h] [rbp-50h] BYREF
  FamilyManager *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,FamilyInfo> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyInfo> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
  it._M_node = std::map<long,FamilyInfo>::find(&this->m_mFamilyInfo, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,FamilyInfo>::end(&thisa->m_mFamilyInfo)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,FamilyInfo>>::operator!=(&it, &__x) )
    Territory = std::_Rb_tree_iterator<std::pair<long const,FamilyInfo>>::operator->(&it)->second.Territory;
  else
    Territory = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return Territory;
}


#####################################
int32_t __cdecl FamilyManager::GetMedlLevel(FamilyManager *const this, FamilyId_t nFamilyId)
{
  int32_t MedalLevel; // ebx
  FamilyId_t nFamilyIda; // [rsp+0h] [rbp-50h] BYREF
  FamilyManager *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,FamilyInfo> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyInfo> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_Lock);
  it._M_node = std::map<long,FamilyInfo>::find(&this->m_mFamilyInfo, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,FamilyInfo>::end(&thisa->m_mFamilyInfo)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,FamilyInfo>>::operator!=(&it, &__x) )
    MedalLevel = std::_Rb_tree_iterator<std::pair<long const,FamilyInfo>>::operator->(&it)->second.MedalLevel;
  else
    MedalLevel = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return MedalLevel;
}


#####################################
bool __cdecl FamilyManager::StartfamilyDungeon(
        FamilyManager *const this,
        FamilyId_t nFamilyId,
        int32_t DungeonId,
        int32_t Hard)
{
  std::pair<const long int,FamilyDungeonStu> *v5; // rax
  MapManager *v6; // rax
  int32_t RunnerId; // ebx
  MapManager *v8; // rax
  std::pair<const long int,FamilyDungeonStu> *v9; // rax
  std::pair<const long int,FamilyDungeonStu> *v10; // rbx
  FamilyDungeonStu *v11; // rbx
  Dungeon **v12; // rax
  FamilyId_t nFamilyIda; // [rsp+20h] [rbp-70h] BYREF
  FamilyManager *thisa; // [rsp+28h] [rbp-68h]
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > it; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Dungeon*> > itDun; // [rsp+40h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Dungeon*> > __x; // [rsp+50h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > v20; // [rsp+60h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > v21; // [rsp+70h] [rbp-20h] BYREF
  Dungeon *pDungeon; // [rsp+78h] [rbp-18h]

  thisa = this;
  nFamilyIda = nFamilyId;
  if ( Hard <= 0 || Hard > 5 )
    return 0;
  itDun._M_node = std::map<long,Dungeon *>::find(&thisa->m_FamilyDungeonMap, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,Dungeon *>::end(&thisa->m_FamilyDungeonMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,Dungeon *>>::operator!=(&itDun, &__x) )
    return 0;
  it._M_node = std::map<long,FamilyDungeonStu>::find(&thisa->m_FamilyDungeonStuMap, &nFamilyIda)._M_node;
  v20._M_node = std::map<long,FamilyDungeonStu>::end(&thisa->m_FamilyDungeonStuMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator!=(&it, &v20) )
  {
    v5 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it);
    if ( !Answer::DayTime::daydiff(v5->second.StartTime) )
      return 0;
    if ( std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.StartCounts > 1 )
      return 0;
    if ( std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.nMaxHard + 1 < Hard )
      return 0;
  }
  else if ( Hard != 1 )
  {
    return 0;
  }
  v6 = Answer::Singleton<MapManager>::instance();
  pDungeon = MapManager::NewDungeon(v6, DungeonId);
  if ( !pDungeon )
    return 0;
  Dungeon::SetHard(pDungeon, Hard);
  Dungeon::SetFamilyId(pDungeon, nFamilyIda);
  Dungeon::start(pDungeon, 0);
  RunnerId = Map::GetRunnerId(pDungeon);
  v8 = Answer::Singleton<MapManager>::instance();
  MapManager::PostMsg(v8, RunnerId, GameMsgCode::GMC_ADD_DUNGEON, pDungeon, 0, 0, 0, 0);
  v21._M_node = std::map<long,FamilyDungeonStu>::end(&thisa->m_FamilyDungeonStuMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator!=(&it, &v21) )
  {
    v9 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it);
    ++v9->second.StartCounts;
    v10 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it);
    v10->second.StartTime = Answer::DayTime::now();
  }
  else
  {
    std::map<long,FamilyDungeonStu>::operator[](&thisa->m_FamilyDungeonStuMap, &nFamilyIda)->nMaxHard = 0;
    v11 = std::map<long,FamilyDungeonStu>::operator[](&thisa->m_FamilyDungeonStuMap, &nFamilyIda);
    v11->StartTime = Answer::DayTime::now();
    std::map<long,FamilyDungeonStu>::operator[](&thisa->m_FamilyDungeonStuMap, &nFamilyIda)->StartCounts = 1;
  }
  v12 = std::map<long,Dungeon *>::operator[](&thisa->m_FamilyDungeonMap, &nFamilyIda);
  *v12 = pDungeon;
  FamilyManager::SaveFamilyDungeonStuMap(thisa, nFamilyIda);
  return 1;
}


#####################################
void __cdecl FamilyManager::SaveFamilyDungeonStuMap(FamilyManager *const this, FamilyId_t nFamilyId)
{
  Answer::DBPool *v2; // rax
  int32_t nMaxHard; // r14d
  int32_t StartTime; // r13d
  int32_t StartCounts; // r12d
  int32_t v6; // ebx
  int32_t v7; // r15d
  std::pair<const long int,FamilyDungeonStu> *v8; // rax
  int32_t v9; // [rsp+2Ch] [rbp-1094h]
  FamilyId_t nFamilyIda; // [rsp+30h] [rbp-1090h] BYREF
  FamilyManager *thisa; // [rsp+38h] [rbp-1088h]
  char szSQL[4096]; // [rsp+40h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1040h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > it; // [rsp+1070h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > __x; // [rsp+1080h] [rbp-40h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  it._M_node = std::map<long,FamilyDungeonStu>::find(&this->m_FamilyDungeonStuMap, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,FamilyDungeonStu>::end(&thisa->m_FamilyDungeonStuMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator!=(&it, &__x) )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(szSQL, 0, sizeof(szSQL));
    nMaxHard = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.nMaxHard;
    StartTime = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.StartTime;
    StartCounts = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.StartCounts;
    v6 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.nMaxHard;
    v9 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.StartTime;
    v7 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.StartCounts;
    v8 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it);
    snprintf(
      szSQL,
      0xFFFu,
      "INSERT INTO `mem_family_dungeon` ( `id`, `times`, `start_time`, `finish_hard` ) VALUES ( %lld, %d, %d, %d ) ON DUP"
      "LICATE KEY UPDATE  `times`=%d, `start_time`=%d, `finish_hard`=%d",
      v8->first,
      v7,
      v9,
      v6,
      StartCounts,
      StartTime,
      nMaxHard);
    Answer::MySqlDBGuard::excute(&db, szSQL);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl FamilyManager::DeleteFamilyDungeon(FamilyManager *const this, FamilyId_t nFamilyId)
{
  FamilyId_t nFamilyIda; // [rsp+0h] [rbp-40h] BYREF
  FamilyManager *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const long int,Dungeon*> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,Dungeon*> > __x; // [rsp+20h] [rbp-20h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  iter._M_node = std::map<long,Dungeon *>::find(&this->m_FamilyDungeonMap, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,Dungeon *>::end(&thisa->m_FamilyDungeonMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,Dungeon *>>::operator!=(&iter, &__x) )
  {
    std::map<long,Dungeon *>::erase(&thisa->m_FamilyDungeonMap, iter);
    FamilyManager::SendSocialFinishBoss(thisa, nFamilyIda, 1, 1);
  }
}


#####################################
void __cdecl FamilyManager::SetFamilyDungeonHard(FamilyManager *const this, FamilyId_t nFamilyId, int32_t Hard)
{
  std::pair<const long int,FamilyDungeonStu> *v3; // rax
  FamilyId_t nFamilyIda; // [rsp+10h] [rbp-30h] BYREF
  FamilyManager *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > it; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,FamilyDungeonStu> > __x; // [rsp+30h] [rbp-10h] BYREF

  thisa = this;
  nFamilyIda = nFamilyId;
  it._M_node = std::map<long,FamilyDungeonStu>::find(&this->m_FamilyDungeonStuMap, &nFamilyIda)._M_node;
  __x._M_node = std::map<long,FamilyDungeonStu>::end(&thisa->m_FamilyDungeonStuMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator!=(&it, &__x)
    && std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.nMaxHard < Hard )
  {
    std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it)->second.nMaxHard = Hard;
    v3 = std::_Rb_tree_iterator<std::pair<long const,FamilyDungeonStu>>::operator->(&it);
    FamilyManager::SaveFamilyDungeonStuMap(thisa, v3->first);
  }
}


