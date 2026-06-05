// Decompiled methods for class: MemChrBagData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrBagData::~MemChrBagData(MemChrBagData *const this)
{
  MemChrBagData::~MemChrBagData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrBagData::CleanUp(MemChrBagData *const this)
{
  bzero(this->bagData, 0x700u);
  std::map<int,int>::clear(&this->m_ItemLimit);
}


#####################################
void __cdecl MemChrBagData::SaveToSqlString(
        MemChrBagData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int second; // ebx
  std::pair<const int,int> *v5; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+90h] [rbp-80h] BYREF
  std::string __x; // [rsp+A0h] [rbp-70h] BYREF
  char v10; // [rsp+AFh] [rbp-61h] BYREF
  std::string v11; // [rsp+B0h] [rbp-60h] BYREF
  char v12; // [rsp+BFh] [rbp-51h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v13; // [rsp+C0h] [rbp-50h] BYREF
  std::string v14; // [rsp+D0h] [rbp-40h] BYREF
  char v15; // [rsp+DBh] [rbp-35h] BYREF
  int32_t slot; // [rsp+DCh] [rbp-34h]

  for ( slot = 0; slot <= 55; ++slot )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_bag` (`cid`, `bag`, `slot`, `id`, `class`, `count`, `bind`, `endtime`, `srcid`) VALUES (%lld,"
      " %d, %d, %d, %d, %d, %d, %d,%lld) on duplicate key update `id`=%d, `class`=%d, `count`=%d, `bind`=%d, `endtime`=%d, `srcid`=%lld",
      nCid,
      1,
      slot,
      this->bagData[slot].itemId,
      this->bagData[slot].itemClass,
      this->bagData[slot].itemCount,
      this->bagData[slot].bind,
      this->bagData[slot].endTime,
      this->bagData[slot].srcId,
      this->bagData[slot].itemId,
      this->bagData[slot].itemClass,
      this->bagData[slot].itemCount,
      this->bagData[slot].bind,
      this->bagData[slot].endTime,
      this->bagData[slot].srcId);
    std::allocator<char>::allocator(&v10);
    std::string::string(&__x, (char *)szSQL, &v10);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v10);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM mem_chr_shop_limit WHERE Cid = %lld AND ShopType=%d", nCid, 2);
  std::allocator<char>::allocator(&v12);
  std::string::string(&v11, (char *)szSQL, &v12);
  std::list<std::string>::push_back(sqls, &v11);
  std::string::~string(&v11);
  std::allocator<char>::~allocator(&v12);
  for ( it._M_node = std::map<int,int>::begin(&this->m_ItemLimit)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
  {
    v13._M_node = std::map<int,int>::end(&this->m_ItemLimit)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &v13) )
      break;
    bzero(szSQL, 0x1000u);
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_shop_limit` ( Cid,ShopType, ShopId, LimitCount ) VALUES( %lld,%d, %d, %d)",
      nCid,
      2,
      v5->first,
      second);
    std::allocator<char>::allocator(&v15);
    std::string::string(&v14, (char *)szSQL, &v15);
    std::list<std::string>::push_back(sqls, &v14);
    std::string::~string(&v14);
    std::allocator<char>::~allocator(&v15);
  }
}


#####################################
bool __cdecl MemChrBagData::LoadFromDB(
        MemChrBagData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  __int64 v7; // rdx
  Answer::MySqlQuery *v8; // rax
  int *v9; // rax
  __int64 slotData; // [rsp+30h] [rbp-80h]
  __int64 slotData_8; // [rsp+38h] [rbp-78h]
  __int64 slotData_16; // [rsp+40h] [rbp-70h]
  int64_t slotData_24; // [rsp+48h] [rbp-68h]
  int32_t ShopId; // [rsp+5Ch] [rbp-54h] BYREF
  Answer::MySqlQuery result_1; // [rsp+60h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-30h] BYREF
  int32_t slot; // [rsp+98h] [rbp-18h]
  int32_t LimitCount; // [rsp+9Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_bag` WHERE `cid`=%lld AND `bag`=%d", nCid, 1);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    LODWORD(slotData) = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    HIDWORD(slotData) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "class", 0);
    LODWORD(slotData_8) = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    HIDWORD(slotData_8) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "bind", 0);
    slotData_16 = (unsigned int)Answer::MySqlQuery::getIntValue(&result, "endtime", 0);
    slotData_24 = Answer::MySqlQuery::getInt64Value(&result, "srcid", 0);
    if ( (unsigned int)slot < 0x38 )
    {
      v7 = slot;
      *(_QWORD *)&this->bagData[v7].itemId = slotData;
      *(_QWORD *)&this->bagData[v7].itemCount = slotData_8;
      *(_QWORD *)&this->bagData[v7].endTime = slotData_16;
      this->bagData[v7].srcId = slotData_24;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "wrong slot data bag = %d, slot = %d, cid = %lld\n",
        1,
        slot,
        nCid);
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_shop_limit` WHERE `Cid`=%lld AND ShopType=%d", nCid, 2);
  v8 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_1, v8);
  while ( !Answer::MySqlQuery::eof(&result_1) )
  {
    ShopId = Answer::MySqlQuery::getIntValue(&result_1, "ShopId", 0);
    LimitCount = Answer::MySqlQuery::getIntValue(&result_1, "LimitCount", 0);
    v9 = std::map<int,int>::operator[](&this->m_ItemLimit, &ShopId);
    *v9 = LimitCount;
    Answer::MySqlQuery::nextRow(&result_1);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_1);
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrBagData::PackageData(MemChrBagData *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  uint32_t nCount; // [rsp+30h] [rbp-10h]
  int32_t slotCount; // [rsp+34h] [rbp-Ch]
  int32_t nSize; // [rsp+38h] [rbp-8h]
  int32_t slot; // [rsp+3Ch] [rbp-4h]

  nCount = Answer::NetPacket::getWOffset(packet);
  slotCount = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  for ( slot = 0; slot <= 55; ++slot )
  {
    if ( this->bagData[slot].itemCount > 0 )
    {
      Answer::NetPacket::writeInt32(packet, slot);
      Answer::NetPacket::writeInt32(packet, this->bagData[slot].itemId);
      Answer::NetPacket::writeInt8(packet, this->bagData[slot].itemClass);
      Answer::NetPacket::writeInt32(packet, this->bagData[slot].itemCount);
      Answer::NetPacket::writeInt8(packet, this->bagData[slot].bind);
      Answer::NetPacket::writeInt32(packet, this->bagData[slot].endTime);
      Answer::NetPacket::writeInt64(packet, this->bagData[slot].srcId);
      ++slotCount;
    }
  }
  *(_DWORD *)&Answer::NetPacket::getBuffer(packet)[nCount] = slotCount;
  nSize = std::map<int,int>::size(&this->m_ItemLimit);
  Answer::NetPacket::writeInt32(packet, nSize);
  for ( it._M_node = std::map<int,int>::begin(&this->m_ItemLimit)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
  {
    __x._M_node = std::map<int,int>::end(&this->m_ItemLimit)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
    Answer::NetPacket::writeInt32(packet, first);
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    Answer::NetPacket::writeInt32(packet, second);
  }
}


#####################################
void __cdecl MemChrBagData::UnPackageData(MemChrBagData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  __int64 v3; // rdx
  int *v4; // rax
  __int64 slotData; // [rsp+20h] [rbp-40h]
  __int64 slotData_8; // [rsp+28h] [rbp-38h]
  __int64 slotData_16; // [rsp+30h] [rbp-30h]
  int64_t slotData_24; // [rsp+38h] [rbp-28h]
  int32_t ShopId; // [rsp+44h] [rbp-1Ch] BYREF
  int32_t slotCount; // [rsp+48h] [rbp-18h]
  int32_t nSize; // [rsp+4Ch] [rbp-14h]
  int32_t i; // [rsp+50h] [rbp-10h]
  int32_t slot; // [rsp+54h] [rbp-Ch]
  int32_t i_0; // [rsp+58h] [rbp-8h]
  int32_t LimitCount; // [rsp+5Ch] [rbp-4h]

  slotCount = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < slotCount; ++i )
  {
    slot = Answer::NetPacket::readInt32(inPacket);
    LODWORD(slotData) = Answer::NetPacket::readInt32(inPacket);
    HIDWORD(slotData) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    LODWORD(slotData_8) = Answer::NetPacket::readInt32(inPacket);
    HIDWORD(slotData_8) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    slotData_16 = (unsigned int)Answer::NetPacket::readInt32(inPacket);
    slotData_24 = Answer::NetPacket::readInt64(inPacket);
    if ( (unsigned int)slot < 0x38 )
    {
      v3 = slot;
      *(_QWORD *)&this->bagData[v3].itemId = slotData;
      *(_QWORD *)&this->bagData[v3].itemCount = slotData_8;
      *(_QWORD *)&this->bagData[v3].endTime = slotData_16;
      this->bagData[v3].srcId = slotData_24;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "wrong bag slotData data bag = %d, slot = %d, cid = %lld\n",
        1,
        slot,
        nCid);
    }
  }
  std::map<int,int>::clear(&this->m_ItemLimit);
  nSize = Answer::NetPacket::readInt32(inPacket);
  for ( i_0 = 0; i_0 < nSize; ++i_0 )
  {
    ShopId = Answer::NetPacket::readInt32(inPacket);
    LimitCount = Answer::NetPacket::readInt32(inPacket);
    v4 = std::map<int,int>::operator[](&this->m_ItemLimit, &ShopId);
    *v4 = LimitCount;
  }
}


