// Decompiled methods for class: ChouJiangData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl ChouJiangData::~ChouJiangData(ChouJiangData *const this)
{
  ChouJiangData::~ChouJiangData(this);
  operator delete(this);
}


#####################################
void __cdecl ChouJiangData::CleanUp(ChouJiangData *const this)
{
  std::list<ChouJiangRecord>::clear(&this->m_RecordList);
  this->m_LuckyPoint = 0;
  this->m_Score = 0;
  bzero(this->m_ItemList, 0x3D40u);
}


#####################################
void __cdecl ChouJiangData::SaveToSqlString(
        ChouJiangData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t Time; // r12d
  int32_t itemCount; // ebx
  int itemClass; // r13d
  ChouJiangRecord *v7; // rax
  std::_List_iterator<ChouJiangRecord> it; // [rsp+90h] [rbp-90h] BYREF
  std::string __x; // [rsp+A0h] [rbp-80h] BYREF
  char v12; // [rsp+AFh] [rbp-71h] BYREF
  std::string v13; // [rsp+B0h] [rbp-70h] BYREF
  char v14; // [rsp+BFh] [rbp-61h] BYREF
  std::string v15; // [rsp+C0h] [rbp-60h] BYREF
  char v16; // [rsp+CFh] [rbp-51h] BYREF
  std::_List_iterator<ChouJiangRecord> v17; // [rsp+D0h] [rbp-50h] BYREF
  std::string v18; // [rsp+E0h] [rbp-40h] BYREF
  char v19; // [rsp+EBh] [rbp-35h] BYREF
  int32_t i; // [rsp+ECh] [rbp-34h]

  for ( i = 0; i <= 489; ++i )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_bag` (`cid`, `bag`, `slot`, `id`, `class`, `count`, `bind`, `endtime`, `srcid`) VALUES (%lld,"
      " %d, %d, %d, %d, %d, %d, %d,%lld) on duplicate key update `id`=%d, `class`=%d, `count`=%d, `bind`=%d, `endtime`=%d, `srcid`=%lld",
      nCid,
      3,
      i,
      *((_DWORD *)&this->m_RecordList._M_impl + 8 * i + 4),
      *((char *)&this->m_RecordList._M_impl + 32 * i + 20),
      *((_DWORD *)&this->m_RecordList._M_impl + 8 * i + 6),
      *((char *)&this->m_RecordList._M_impl + 32 * i + 28),
      this->m_ItemList[i].endTime,
      this->m_ItemList[i].srcId,
      *((_DWORD *)&this->m_RecordList._M_impl + 8 * i + 4),
      *((char *)&this->m_RecordList._M_impl + 32 * i + 20),
      *((_DWORD *)&this->m_RecordList._M_impl + 8 * i + 6),
      *((char *)&this->m_RecordList._M_impl + 32 * i + 28),
      this->m_ItemList[i].endTime,
      this->m_ItemList[i].srcId);
    std::allocator<char>::allocator(&v12);
    std::string::string(&__x, (char *)szSQL, &v12);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v12);
  }
  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT `mem_chr_chou_jiang_score`(Cid,LuckPoint,Score) VALUES (%lld,%d,%d) ON DUPLICATE KEY UPDATE LuckPoint =%d,Score=%d",
    nCid,
    this->m_LuckyPoint,
    this->m_Score,
    this->m_LuckyPoint,
    this->m_Score);
  std::allocator<char>::allocator(&v14);
  std::string::string(&v13, (char *)szSQL, &v14);
  std::list<std::string>::push_back(sqls, &v13);
  std::string::~string(&v13);
  std::allocator<char>::~allocator(&v14);
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_chou_jiang_record` WHERE `cid` = %lld", nCid);
  std::allocator<char>::allocator(&v16);
  std::string::string(&v15, (char *)szSQL, &v16);
  std::list<std::string>::push_back(sqls, &v15);
  std::string::~string(&v15);
  std::allocator<char>::~allocator(&v16);
  for ( it._M_node = std::list<ChouJiangRecord>::begin(&this->m_RecordList)._M_node;
        ;
        std::_List_iterator<ChouJiangRecord>::operator++(&it) )
  {
    v17._M_node = std::list<ChouJiangRecord>::end(&this->m_RecordList)._M_node;
    if ( !std::_List_iterator<ChouJiangRecord>::operator!=(&it, &v17) )
      break;
    bzero(szSQL, 0x1000u);
    Time = std::_List_iterator<ChouJiangRecord>::operator->(&it)->Time;
    itemCount = std::_List_iterator<ChouJiangRecord>::operator->(&it)->CJItem.itemCount;
    itemClass = std::_List_iterator<ChouJiangRecord>::operator->(&it)->CJItem.itemClass;
    v7 = std::_List_iterator<ChouJiangRecord>::operator->(&it);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT `mem_chr_chou_jiang_record`( Cid,ItemId,ItemClass,ItemCount,Time ) VALUES (%lld,%d,%d,%d,%d)",
      nCid,
      v7->CJItem.itemId,
      itemClass,
      itemCount,
      Time);
    std::allocator<char>::allocator(&v19);
    std::string::string(&v18, (char *)szSQL, &v19);
    std::list<std::string>::push_back(sqls, &v18);
    std::string::~string(&v18);
    std::allocator<char>::~allocator(&v19);
  }
}


#####################################
bool __cdecl ChouJiangData::LoadFromDB(
        ChouJiangData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  Answer::MySqlQuery *v7; // rax
  Answer::MySqlQuery *v8; // rax
  ChouJiangRecord CJItem; // [rsp+30h] [rbp-A0h] BYREF
  Answer::MySqlQuery result_2; // [rsp+60h] [rbp-70h] BYREF
  Answer::MySqlQuery result_1; // [rsp+80h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+A0h] [rbp-30h] BYREF
  int32_t gambleSlotCount; // [rsp+B8h] [rbp-18h]
  int32_t slot; // [rsp+BCh] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_bag` WHERE `cid`=%lld AND `bag`=%d", nCid, 3);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  gambleSlotCount = 0;
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    *(&CJItem.CJItem.endTime + 1) = 0;
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    CJItem.CJItem.itemId = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    *(_DWORD *)&CJItem.CJItem.itemClass = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "class", 0);
    CJItem.CJItem.itemCount = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    *(_DWORD *)&CJItem.CJItem.bind = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "bind", 0);
    CJItem.CJItem.endTime = Answer::MySqlQuery::getIntValue(&result, "endtime", 0);
    CJItem.CJItem.srcId = Answer::MySqlQuery::getInt64Value(&result, "srcid", 0);
    if ( (unsigned int)slot > 0x1E9 )
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "wrong gamble slot data slot = %d, cid = %lld\n",
        slot,
        nCid);
    else
      *(MemChrBag *)(&this->m_RecordList._M_impl + 2 * slot + 1) = CJItem.CJItem;
    Answer::MySqlQuery::nextRow(&result);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_chou_jiang_score` WHERE `Cid`=%lld", nCid);
  v7 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_1, v7);
  while ( !Answer::MySqlQuery::eof(&result_1) )
  {
    this->m_LuckyPoint = Answer::MySqlQuery::getIntValue(&result_1, "LuckPoint", 0);
    this->m_Score = Answer::MySqlQuery::getIntValue(&result_1, "Score", 0);
    Answer::MySqlQuery::nextRow(&result_1);
  }
  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "SELECT * FROM `mem_chr_chou_jiang_record` WHERE `Cid`=%lld ORDER BY `Time` DESC LIMIT %d",
    nCid,
    20);
  v8 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_2, v8);
  while ( !Answer::MySqlQuery::eof(&result_2) )
  {
    memset(&CJItem, 0, sizeof(CJItem));
    CJItem.CJItem.itemId = Answer::MySqlQuery::getIntValue(&result_2, "ItemId", 0);
    CJItem.CJItem.itemClass = Answer::MySqlQuery::getIntValue(&result_2, "ItemClass", 0);
    CJItem.CJItem.itemCount = Answer::MySqlQuery::getIntValue(&result_2, "ItemCount", 0);
    CJItem.Time = Answer::MySqlQuery::getIntValue(&result_2, "Time", 0);
    std::list<ChouJiangRecord>::push_back(&this->m_RecordList, &CJItem);
    Answer::MySqlQuery::nextRow(&result_2);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_2);
  Answer::MySqlQuery::~MySqlQuery(&result_1);
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl ChouJiangData::PackageData(ChouJiangData *const this, Answer::NetPacket *packet)
{
  int32_t itemId; // edx
  int8_t itemClass; // dl
  int32_t itemCount; // edx
  int32_t Time; // edx
  std::_List_iterator<ChouJiangRecord> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<ChouJiangRecord> __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t Count; // [rsp+30h] [rbp-10h]
  int32_t OldOffet; // [rsp+34h] [rbp-Ch]
  int32_t NewOffet; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  Answer::NetPacket::writeInt32(packet, this->m_LuckyPoint);
  Answer::NetPacket::writeInt32(packet, this->m_Score);
  Count = 0;
  OldOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::writeInt32(packet, 0);
  for ( i = 0; i <= 489; ++i )
  {
    if ( *((int *)&this->m_RecordList._M_impl + 8 * i + 4) > 0 && *((int *)&this->m_RecordList._M_impl + 8 * i + 6) > 0 )
    {
      ++Count;
      Answer::NetPacket::writeInt32(packet, i);
      Answer::NetPacket::writeInt32(packet, *((_DWORD *)&this->m_RecordList._M_impl + 8 * i + 4));
      Answer::NetPacket::writeInt8(packet, *((_BYTE *)&this->m_RecordList._M_impl + 32 * i + 20));
      Answer::NetPacket::writeInt32(packet, *((_DWORD *)&this->m_RecordList._M_impl + 8 * i + 6));
      Answer::NetPacket::writeInt8(packet, *((_BYTE *)&this->m_RecordList._M_impl + 32 * i + 28));
      Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].endTime);
      Answer::NetPacket::writeInt64(packet, this->m_ItemList[i].srcId);
    }
  }
  NewOffet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, OldOffet);
  Answer::NetPacket::writeInt32(packet, Count);
  Answer::NetPacket::setWOffset(packet, NewOffet);
  Count = std::list<ChouJiangRecord>::size(&this->m_RecordList);
  Answer::NetPacket::writeInt32(packet, Count);
  for ( it._M_node = std::list<ChouJiangRecord>::begin(&this->m_RecordList)._M_node;
        ;
        std::_List_iterator<ChouJiangRecord>::operator++(&it) )
  {
    __x._M_node = std::list<ChouJiangRecord>::end(&this->m_RecordList)._M_node;
    if ( !std::_List_iterator<ChouJiangRecord>::operator!=(&it, &__x) )
      break;
    itemId = std::_List_iterator<ChouJiangRecord>::operator->(&it)->CJItem.itemId;
    Answer::NetPacket::writeInt32(packet, itemId);
    itemClass = std::_List_iterator<ChouJiangRecord>::operator->(&it)->CJItem.itemClass;
    Answer::NetPacket::writeInt8(packet, itemClass);
    itemCount = std::_List_iterator<ChouJiangRecord>::operator->(&it)->CJItem.itemCount;
    Answer::NetPacket::writeInt32(packet, itemCount);
    Time = std::_List_iterator<ChouJiangRecord>::operator->(&it)->Time;
    Answer::NetPacket::writeInt32(packet, Time);
  }
}


#####################################
void __cdecl ChouJiangData::UnPackageData(ChouJiangData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  ChouJiangRecord Record; // [rsp+20h] [rbp-40h] BYREF
  int32_t Count; // [rsp+4Ch] [rbp-14h]
  int32_t RecordCount; // [rsp+50h] [rbp-10h]
  int32_t i; // [rsp+54h] [rbp-Ch]
  int32_t Index; // [rsp+58h] [rbp-8h]
  int32_t j; // [rsp+5Ch] [rbp-4h]

  this->m_LuckyPoint = Answer::NetPacket::readInt32(inPacket);
  this->m_Score = Answer::NetPacket::readInt32(inPacket);
  Count = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < Count; ++i )
  {
    Index = Answer::NetPacket::readInt32(inPacket);
    *(&Record.CJItem.endTime + 1) = 0;
    Record.CJItem.itemId = Answer::NetPacket::readInt32(inPacket);
    *(_DWORD *)&Record.CJItem.itemClass = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    Record.CJItem.itemCount = Answer::NetPacket::readInt32(inPacket);
    *(_DWORD *)&Record.CJItem.bind = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    Record.CJItem.endTime = Answer::NetPacket::readInt32(inPacket);
    Record.CJItem.srcId = Answer::NetPacket::readInt64(inPacket);
    if ( (unsigned int)Index <= 0x1E9 )
      *(MemChrBag *)(&this->m_RecordList._M_impl + 2 * Index + 1) = Record.CJItem;
  }
  RecordCount = Answer::NetPacket::readInt32(inPacket);
  for ( j = 0; j < RecordCount; ++j )
  {
    memset(&Record, 0, sizeof(Record));
    Record.CJItem.itemId = Answer::NetPacket::readInt32(inPacket);
    Record.CJItem.itemClass = Answer::NetPacket::readInt8(inPacket);
    Record.CJItem.itemCount = Answer::NetPacket::readInt32(inPacket);
    Record.Time = Answer::NetPacket::readInt32(inPacket);
    std::list<ChouJiangRecord>::push_back(&this->m_RecordList, &Record);
  }
}


