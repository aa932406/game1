// Decompiled methods for class: ShangChengData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl ShangChengData::~ShangChengData(ShangChengData *const this)
{
  ShangChengData::~ShangChengData(this);
  operator delete(this);
}


#####################################
void __cdecl ShangChengData::SaveToSqlString(
        ShangChengData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int second; // ebx
  std::pair<const int,int> *v5; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+30h] [rbp-50h] BYREF
  std::string __x; // [rsp+40h] [rbp-40h] BYREF
  char v10; // [rsp+4Fh] [rbp-31h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v11; // [rsp+50h] [rbp-30h] BYREF
  std::string v12; // [rsp+60h] [rbp-20h] BYREF
  _BYTE v13[17]; // [rsp+6Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM mem_chr_shop_limit WHERE Cid = %lld AND ShopType=%d", nCid, 1);
  std::allocator<char>::allocator(&v10);
  std::string::string(&__x, (char *)szSQL, &v10);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v10);
  for ( it._M_node = std::map<int,int>::begin(&this->m_LiMitMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
  {
    v11._M_node = std::map<int,int>::end(&this->m_LiMitMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &v11) )
      break;
    bzero(szSQL, 0x1000u);
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_shop_limit` ( Cid,ShopType, ShopId, LimitCount ) VALUES( %lld,%d, %d, %d)",
      nCid,
      1,
      v5->first,
      second);
    std::allocator<char>::allocator(v13);
    std::string::string(&v12, (char *)szSQL, v13);
    std::list<std::string>::push_back(sqls, &v12);
    std::string::~string(&v12);
    std::allocator<char>::~allocator(v13);
  }
}


#####################################
bool __cdecl ShangChengData::LoadFromDB(
        ShangChengData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  int *v7; // rax
  int32_t ShopId; // [rsp+3Ch] [rbp-34h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF
  int32_t LimitCount; // [rsp+5Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_shop_limit` WHERE `Cid`=%lld AND ShopType=%d", nCid, 1);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    ShopId = Answer::MySqlQuery::getIntValue(&result, "ShopId", 0);
    LimitCount = Answer::MySqlQuery::getIntValue(&result, "LimitCount", 0);
    v7 = std::map<int,int>::operator[](&this->m_LiMitMap, &ShopId);
    *v7 = LimitCount;
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl ShangChengData::PackageData(ShangChengData *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  nSize = std::map<int,int>::size(&this->m_LiMitMap);
  Answer::NetPacket::writeInt32(packet, nSize);
  for ( it._M_node = std::map<int,int>::begin(&this->m_LiMitMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
  {
    __x._M_node = std::map<int,int>::end(&this->m_LiMitMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
    Answer::NetPacket::writeInt32(packet, first);
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    Answer::NetPacket::writeInt32(packet, second);
  }
}


#####################################
void __cdecl ShangChengData::UnPackageData(ShangChengData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int *v3; // rax
  int32_t ShopId; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+24h] [rbp-Ch]
  int32_t i; // [rsp+28h] [rbp-8h]
  int32_t LimitCount; // [rsp+2Ch] [rbp-4h]

  std::map<int,int>::clear(&this->m_LiMitMap);
  nSize = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < nSize; ++i )
  {
    ShopId = Answer::NetPacket::readInt32(inPacket);
    LimitCount = Answer::NetPacket::readInt32(inPacket);
    v3 = std::map<int,int>::operator[](&this->m_LiMitMap, &ShopId);
    *v3 = LimitCount;
  }
}


