// Decompiled methods for class: MemChrBuffData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl MemChrBuffData::~MemChrBuffData(MemChrBuffData *const this)
{
  MemChrBuffData::~MemChrBuffData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrBuffData::SaveToSqlString(
        MemChrBuffData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t time; // ebx
  int32_t buffId; // r12d
  MemChrBuff *v6; // rax
  std::string __x; // [rsp+30h] [rbp-40h] BYREF
  char v10; // [rsp+3Fh] [rbp-31h] BYREF
  std::string v11; // [rsp+40h] [rbp-30h] BYREF
  char v12; // [rsp+57h] [rbp-19h] BYREF
  int32_t vtSize; // [rsp+58h] [rbp-18h]
  int32_t i; // [rsp+5Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_buff` WHERE `cid`=%lld", nCid);
  std::allocator<char>::allocator(&v10);
  std::string::string(&__x, (char *)szSQL, &v10);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v10);
  vtSize = std::vector<MemChrBuff>::size(&this->buffVt);
  for ( i = 0; i < vtSize; ++i )
  {
    bzero(szSQL, 0x1000u);
    time = std::vector<MemChrBuff>::operator[](&this->buffVt, i)->time;
    buffId = std::vector<MemChrBuff>::operator[](&this->buffVt, i)->buffId;
    v6 = std::vector<MemChrBuff>::operator[](&this->buffVt, i);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_buff` (`cid`, `item`, `buff`, `time`) VALUES (%lld, %d, %d, %d)",
      nCid,
      v6->itemId,
      buffId,
      time);
    std::allocator<char>::allocator(&v12);
    std::string::string(&v11, (char *)szSQL, &v12);
    std::list<std::string>::push_back(sqls, &v11);
    std::string::~string(&v11);
    std::allocator<char>::~allocator(&v12);
  }
}


#####################################
bool __cdecl MemChrBuffData::LoadFromDB(
        MemChrBuffData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  int RowCount; // eax
  MemChrBuff buff; // [rsp+30h] [rbp-40h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_buff` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  RowCount = Answer::MySqlQuery::getRowCount(&result);
  std::vector<MemChrBuff>::reserve(&this->buffVt, RowCount);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    *(_QWORD *)&buff.itemId = 0;
    buff.time = 0;
    buff.itemId = Answer::MySqlQuery::getIntValue(&result, "item", 0);
    buff.buffId = Answer::MySqlQuery::getIntValue(&result, "buff", 0);
    buff.time = Answer::MySqlQuery::getIntValue(&result, "time", 0);
    std::vector<MemChrBuff>::push_back(&this->buffVt, &buff);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrBuffData::PackageData(MemChrBuffData *const this, Answer::NetPacket *packet)
{
  int32_t itemId; // edx
  int32_t buffId; // edx
  int32_t time; // edx
  int32_t vtSize; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  vtSize = std::vector<MemChrBuff>::size(&this->buffVt);
  Answer::NetPacket::writeInt32(packet, vtSize);
  for ( i = 0; i < vtSize; ++i )
  {
    itemId = std::vector<MemChrBuff>::operator[](&this->buffVt, i)->itemId;
    Answer::NetPacket::writeInt32(packet, itemId);
    buffId = std::vector<MemChrBuff>::operator[](&this->buffVt, i)->buffId;
    Answer::NetPacket::writeInt32(packet, buffId);
    time = std::vector<MemChrBuff>::operator[](&this->buffVt, i)->time;
    Answer::NetPacket::writeInt32(packet, time);
  }
}


#####################################
void __cdecl MemChrBuffData::UnPackageData(MemChrBuffData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  MemChrBuff buff; // [rsp+20h] [rbp-20h] BYREF
  int32_t buffCount; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  buffCount = Answer::NetPacket::readInt32(inPacket);
  std::vector<MemChrBuff>::reserve(&this->buffVt, buffCount);
  for ( i = 0; i < buffCount; ++i )
  {
    *(_QWORD *)&buff.itemId = 0;
    buff.time = 0;
    buff.itemId = Answer::NetPacket::readInt32(inPacket);
    buff.buffId = Answer::NetPacket::readInt32(inPacket);
    buff.time = Answer::NetPacket::readInt32(inPacket);
    std::vector<MemChrBuff>::push_back(&this->buffVt, &buff);
  }
}


