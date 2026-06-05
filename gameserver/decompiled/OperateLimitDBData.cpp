// Decompiled methods for class: OperateLimitDBData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl OperateLimitDBData::~OperateLimitDBData(OperateLimitDBData *const this)
{
  OperateLimitDBData::~OperateLimitDBData(this);
  operator delete(this);
}


#####################################
void __cdecl OperateLimitDBData::SaveToSqlString(
        OperateLimitDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t LimitCount; // ebx
  int32_t v5; // r12d
  std::pair<const int,OperateLimit> *v6; // rax
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > eiter; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+40h] [rbp-30h] BYREF
  std::string __x; // [rsp+50h] [rbp-20h] BYREF
  _BYTE v12[17]; // [rsp+5Fh] [rbp-11h] BYREF

  iter._M_node = std::map<int,OperateLimit>::begin(&this->m_mOperateLimit)._M_node;
  eiter._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &eiter) )
  {
    bzero(szSQL, 0x1000u);
    LimitCount = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount;
    v5 = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount;
    v6 = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT `mem_char_operate_limit`(cid,LimitId,LimitCount) VALUES (%lld,%d,%d) ON DUPLICATE KEY UPDATE LimitCount=%d",
      nCid,
      v6->second.LimitId,
      v5,
      LimitCount);
    std::allocator<char>::allocator(v12);
    std::string::string(&__x, (char *)szSQL, v12);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(v12);
    std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator++(&iter);
  }
}


#####################################
bool __cdecl OperateLimitDBData::LoadFromDB(
        OperateLimitDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  OperateLimit *v7; // rax
  OperateLimit limit; // [rsp+30h] [rbp-40h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_operate_limit` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    *(_QWORD *)&limit.LimitId = 0;
    *(_DWORD *)&limit.IsChaned = 0;
    limit.LimitId = Answer::MySqlQuery::getIntValue(&result, "LimitId", 0);
    limit.LimitCount = Answer::MySqlQuery::getIntValue(&result, "LimitCount", 0);
    v7 = std::map<int,OperateLimit>::operator[](&this->m_mOperateLimit, &limit.LimitId);
    *v7 = limit;
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl OperateLimitDBData::PackageData(OperateLimitDBData *const this, Answer::NetPacket *packet)
{
  int32_t LimitId; // edx
  int32_t LimitCount; // edx
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,OperateLimit> > iter; // [rsp+20h] [rbp-10h] BYREF
  int32_t mapSize; // [rsp+2Ch] [rbp-4h]

  mapSize = std::map<int,OperateLimit>::size(&this->m_mOperateLimit);
  Answer::NetPacket::writeInt32(packet, mapSize);
  iter._M_node = std::map<int,OperateLimit>::begin(&this->m_mOperateLimit)._M_node;
  eiter._M_node = std::map<int,OperateLimit>::end(&this->m_mOperateLimit)._M_node;
  while ( std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator!=(&iter, &eiter) )
  {
    LimitId = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitId;
    Answer::NetPacket::writeInt32(packet, LimitId);
    LimitCount = std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator->(&iter)->second.LimitCount;
    Answer::NetPacket::writeInt32(packet, LimitCount);
    std::_Rb_tree_iterator<std::pair<int const,OperateLimit>>::operator++(&iter);
  }
}


#####################################
void __cdecl OperateLimitDBData::UnPackageData(
        OperateLimitDBData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  OperateLimit *v3; // rax
  OperateLimit limit; // [rsp+20h] [rbp-20h] BYREF
  int32_t mapSize; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  mapSize = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < mapSize; ++i )
  {
    *(_QWORD *)&limit.LimitId = 0;
    *(_DWORD *)&limit.IsChaned = 0;
    limit.LimitId = Answer::NetPacket::readInt32(inPacket);
    limit.LimitCount = Answer::NetPacket::readInt32(inPacket);
    v3 = std::map<int,OperateLimit>::operator[](&this->m_mOperateLimit, &limit.LimitId);
    *v3 = limit;
  }
}


