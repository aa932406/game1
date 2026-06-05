// Decompiled methods for class: CVipClub
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CVipClub::Init(CVipClub *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  const char *StringValue; // rax
  ClubData *v5; // rax
  Answer::MySqlDBGuard db; // [rsp+10h] [rbp-80h] BYREF
  ClubData stu; // [rsp+40h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-30h] BYREF

  if ( line != 9 )
  {
    std::map<long,ClubData>::clear(&this->m_ClubDataMap);
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    v3 = Answer::MySqlDBGuard::query(
           &db,
           "select a.cid,a.level,a.club_7_time,a.club_10_time,b.name from mem_chr_vip as a,  mem_character as b where clu"
           "b > 0 and a.cid = b.cid");
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      memset(&stu, 0, 28);
      std::string::string(&stu.strName);
      stu.nCid = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      stu.nVipLevel = Answer::MySqlQuery::getIntValue(&result, "level", 0);
      stu.nVip7Time = Answer::MySqlQuery::getIntValue(&result, "club_7_time", 0);
      stu.nVip10Time = Answer::MySqlQuery::getIntValue(&result, "club_10_time", 0);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "name", &byte_8F4D38);
      std::string::operator=(&stu.strName, StringValue);
      v5 = std::map<long,ClubData>::operator[](&this->m_ClubDataMap, &stu.nCid);
      ClubData::operator=(v5, &stu);
      Answer::MySqlQuery::nextRow(&result);
      ClubData::~ClubData(&stu);
    }
    this->m_ClubLevel = CVipClub::CalculationClubLevel(this);
    CVipClub::CalculationClubWallInfo(this);
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl CVipClub::UpdateClubData(
        CVipClub *const this,
        CharId_t nCid,
        std::string *p_name,
        int32_t nVipLevel,
        int32_t nTime)
{
  std::string *p_strName; // rdx
  ClubData *v8; // rax
  int32_t v9; // eax
  GameService *v10; // rax
  CharId_t nCida; // [rsp+10h] [rbp-60h] BYREF
  CVipClub *thisa; // [rsp+18h] [rbp-58h]
  ClubData stu; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ClubData> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ClubData> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t nOldLevel; // [rsp+5Ch] [rbp-14h]

  thisa = this;
  nCida = nCid;
  it._M_node = std::map<long,ClubData>::find(&this->m_ClubDataMap, &nCida)._M_node;
  __x._M_node = std::map<long,ClubData>::end(&thisa->m_ClubDataMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator!=(&it, &__x) )
  {
    p_strName = &std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.strName;
    std::string::operator=(p_strName, p_name);
    if ( std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVipLevel <= 6 && nVipLevel > 6 )
      std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVip7Time = nTime;
    if ( std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVipLevel <= 9 && nVipLevel > 9 )
      std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVip10Time = nTime;
    std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVipLevel = nVipLevel;
  }
  else
  {
    memset(&stu, 0, 28);
    std::string::string(&stu.strName);
    stu.nCid = nCida;
    std::string::operator=(&stu.strName, p_name);
    if ( nVipLevel > 6 )
      stu.nVip7Time = nTime;
    if ( nVipLevel > 9 )
      stu.nVip10Time = nTime;
    stu.nVipLevel = nVipLevel;
    v8 = std::map<long,ClubData>::operator[](&thisa->m_ClubDataMap, &stu.nCid);
    ClubData::operator=(v8, &stu);
    ClubData::~ClubData(&stu);
  }
  nOldLevel = thisa->m_ClubLevel;
  v9 = CVipClub::CalculationClubLevel(thisa);
  thisa->m_ClubLevel = v9;
  if ( thisa->m_ClubLevel != nOldLevel )
  {
    v10 = Answer::Singleton<GameService>::instance();
    GameService::AddPlayerVipClubDropTime(v10);
  }
  CVipClub::CalculationClubWallInfo(thisa);
}


#####################################
int32_t __cdecl CVipClub::CalculationClubLevel(CVipClub *const this)
{
  CfgData *v1; // rax
  int32_t nVipLevel; // ebx
  const ClbAimCfg *v3; // rax
  const ClbAimCfg *v5; // rax
  int *v6; // rax
  std::_Rb_tree_iterator<std::pair<const long int,ClubData> > iter; // [rsp+10h] [rbp-60h] BYREF
  std::_List_const_iterator<ClbAimCfg> it; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<ClbAimCfg> v10; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ClubData> > __x; // [rsp+40h] [rbp-30h] BYREF
  int32_t nLevel; // [rsp+4Ch] [rbp-24h]
  const ClbAimCfgList *ClbAimCfgTable; // [rsp+50h] [rbp-20h]
  int32_t nCount; // [rsp+58h] [rbp-18h]
  int32_t nAddLevel; // [rsp+5Ch] [rbp-14h]

  nLevel = 0;
  std::map<int,int>::clear(&this->m_LevelCountMap);
  v1 = Answer::Singleton<CfgData>::instance();
  ClbAimCfgTable = CfgData::GetClbAimCfg(v1);
  for ( it._M_node = std::list<ClbAimCfg>::begin(ClbAimCfgTable)._M_node;
        ;
        std::_List_const_iterator<ClbAimCfg>::operator++(&it, 0) )
  {
    v10._M_node = std::list<ClbAimCfg>::end(ClbAimCfgTable)._M_node;
    if ( !std::_List_const_iterator<ClbAimCfg>::operator!=(&it, &v10) )
      break;
    nCount = 0;
    nAddLevel = 0;
    for ( iter._M_node = std::map<long,ClubData>::begin(&this->m_ClubDataMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator++(&iter, 0) )
    {
      __x._M_node = std::map<long,ClubData>::end(&this->m_ClubDataMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator!=(&iter, &__x) )
        break;
      nVipLevel = std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&iter)->second.nVipLevel;
      if ( nVipLevel >= std::_List_const_iterator<ClbAimCfg>::operator->(&it)->nNeedVipLevel )
        ++nCount;
      v3 = std::_List_const_iterator<ClbAimCfg>::operator->(&it);
      if ( v3->nNeedCount <= nCount && nAddLevel <= 0 )
        nAddLevel = std::_List_const_iterator<ClbAimCfg>::operator->(&it)->nAddDropTimes;
    }
    v5 = std::_List_const_iterator<ClbAimCfg>::operator->(&it);
    v6 = std::map<int,int>::operator[](&this->m_LevelCountMap, &v5->nNeedVipLevel);
    *v6 = nCount;
    nLevel += nAddLevel;
  }
  return nLevel + 1;
}


#####################################
void __cdecl CVipClub::CalculationClubWallInfo(CVipClub *const this)
{
  std::pair<const long int,ClubData> *v1; // rax
  std::pair<const long int,ClubData> *v3; // rax
  std::pair<const long int,ClubData> *v4; // rax
  ClubData *M_current; // rbx
  __gnu_cxx::__normal_iterator<ClubData*,std::vector<ClubData> > v6; // rax
  __gnu_cxx::__normal_iterator<ClubData*,std::vector<ClubData> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ClubData> > it; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ClubData> > __x; // [rsp+30h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<ClubData*,std::vector<ClubData> > __rhs; // [rsp+40h] [rbp-20h] BYREF
  int32_t Vip10Time; // [rsp+4Ch] [rbp-14h]

  Vip10Time = 0;
  std::vector<ClubData>::clear(&this->m_Vip7ClubDataVt);
  for ( it._M_node = std::map<long,ClubData>::begin(&this->m_ClubDataMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<long,ClubData>::end(&this->m_ClubDataMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVipLevel > 9 )
    {
      if ( !Vip10Time
        || (v1 = std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it),
            v1->second.nVip10Time < Vip10Time) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it);
        ClubData::operator=(&this->m_Vip10ClubData, &v3->second);
      }
    }
    if ( std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it)->second.nVipLevel > 6 )
    {
      v4 = std::_Rb_tree_iterator<std::pair<long const,ClubData>>::operator->(&it);
      std::vector<ClubData>::push_back(&this->m_Vip7ClubDataVt, &v4->second);
    }
  }
  if ( this->m_Vip10ClubData.nCid > 0 )
  {
    for ( iter._M_current = std::vector<ClubData>::begin(&this->m_Vip7ClubDataVt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<ClubData *,std::vector<ClubData>>::operator++(&iter, 0) )
    {
      __rhs._M_current = std::vector<ClubData>::end(&this->m_Vip7ClubDataVt)._M_current;
      if ( !__gnu_cxx::operator!=<ClubData *,std::vector<ClubData>>(&iter, &__rhs) )
        break;
      if ( __gnu_cxx::__normal_iterator<ClubData *,std::vector<ClubData>>::operator->(&iter)->nCid == this->m_Vip10ClubData.nCid )
      {
        std::vector<ClubData>::erase(&this->m_Vip7ClubDataVt, iter);
        break;
      }
    }
  }
  if ( !std::vector<ClubData>::empty(&this->m_Vip7ClubDataVt) )
  {
    M_current = std::vector<ClubData>::end(&this->m_Vip7ClubDataVt)._M_current;
    v6._M_current = std::vector<ClubData>::begin(&this->m_Vip7ClubDataVt)._M_current;
    std::sort<__gnu_cxx::__normal_iterator<ClubData *,std::vector<ClubData>>,bool (*)(ClubData const&,ClubData const&)>(
      v6,
      (__gnu_cxx::__normal_iterator<ClubData*,std::vector<ClubData> >)M_current,
      (bool (*)(const ClubData *, const ClubData *))GreaterClubData);
  }
}


#####################################
void __cdecl CVipClub::AppendClubWallInfo(CVipClub *const this, Answer::NetPacket *packet)
{
  int32_t v2; // eax
  CharId_t nCid; // rdx
  std::string *p_strName; // rdx
  int32_t v5; // edx
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > itInt; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<ClubData*,std::vector<ClubData> > it; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<ClubData*,std::vector<ClubData> > __rhs; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+40h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+48h] [rbp-8h]
  int32_t Count; // [rsp+4Ch] [rbp-4h]

  if ( packet )
  {
    if ( this->m_Vip10ClubData.nCid > 0 )
    {
      Answer::NetPacket::writeInt32(packet, 1);
      Answer::NetPacket::writeInt64(packet, this->m_Vip10ClubData.nCid);
      Answer::NetPacket::writeUTF8(packet, &this->m_Vip10ClubData.strName);
    }
    else
    {
      Answer::NetPacket::writeInt32(packet, 0);
    }
    nSize = std::vector<ClubData>::size(&this->m_Vip7ClubDataVt);
    v2 = 3;
    if ( nSize <= 3 )
      v2 = nSize;
    nSize = v2;
    Answer::NetPacket::writeInt32(packet, v2);
    Count = 0;
    for ( it._M_current = std::vector<ClubData>::begin(&this->m_Vip7ClubDataVt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<ClubData *,std::vector<ClubData>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<ClubData>::end(&this->m_Vip7ClubDataVt)._M_current;
      if ( !__gnu_cxx::operator!=<ClubData *,std::vector<ClubData>>(&it, &__rhs) )
        break;
      nCid = __gnu_cxx::__normal_iterator<ClubData *,std::vector<ClubData>>::operator->(&it)->nCid;
      Answer::NetPacket::writeInt64(packet, nCid);
      p_strName = &__gnu_cxx::__normal_iterator<ClubData *,std::vector<ClubData>>::operator->(&it)->strName;
      Answer::NetPacket::writeUTF8(packet, p_strName);
      if ( ++Count > 2 )
        break;
    }
    Answer::NetPacket::writeInt32(packet, this->m_ClubLevel);
    v5 = std::map<int,int>::size(&this->m_LevelCountMap);
    Answer::NetPacket::writeInt32(packet, v5);
    for ( itInt._M_node = std::map<int,int>::begin(&this->m_LevelCountMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itInt, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_LevelCountMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itInt, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itInt)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itInt)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
  }
}


