// Decompiled methods for class: MemChrActionData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrActionData::~MemChrActionData(MemChrActionData *const this)
{
  MemChrActionData::~MemChrActionData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrActionData::CleanUp(MemChrActionData *const this)
{
  bzero(this->actionArry, 0x68u);
}


#####################################
void __cdecl MemChrActionData::SaveToSqlString(
        MemChrActionData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+30h] [rbp-30h] BYREF
  char v7; // [rsp+3Fh] [rbp-21h] BYREF
  std::string v8; // [rsp+40h] [rbp-20h] BYREF
  char v9; // [rsp+4Bh] [rbp-15h] BYREF
  int i; // [rsp+4Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_action` WHERE `cid`=%lld", nCid);
  std::allocator<char>::allocator(&v7);
  std::string::string(&__x, (char *)szSQL, &v7);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v7);
  for ( i = 1; i <= 12; ++i )
  {
    if ( this->actionArry[i].id )
    {
      bzero(szSQL, 0x1000u);
      snprintf(
        (char *)szSQL,
        0xFFFu,
        "INSERT INTO `mem_chr_action` (`cid`, `slot`, `id`, `type`) VALUES (%lld, %d, %d, %d)",
        nCid,
        i,
        this->actionArry[i].id,
        this->actionArry[i].type);
      std::allocator<char>::allocator(&v9);
      std::string::string(&v8, (char *)szSQL, &v9);
      std::list<std::string>::push_back(sqls, &v8);
      std::string::~string(&v8);
      std::allocator<char>::~allocator(&v9);
    }
  }
}


#####################################
bool __cdecl MemChrActionData::LoadFromDB(
        MemChrActionData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  MemChrAction action; // [rsp+30h] [rbp-40h]
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF
  int32_t slot; // [rsp+5Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_action` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    action.id = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    action.type = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    if ( slot > 0 && slot <= 12 )
      this->actionArry[slot] = action;
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrActionData::PackageData(MemChrActionData *const this, Answer::NetPacket *packet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 1; i <= 12; ++i )
  {
    Answer::NetPacket::writeInt32(packet, this->actionArry[i].id);
    Answer::NetPacket::writeInt32(packet, this->actionArry[i].type);
  }
}


#####################################
void __cdecl MemChrActionData::UnPackageData(MemChrActionData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  MemChrAction action; // [rsp+20h] [rbp-10h]
  int32_t i; // [rsp+2Ch] [rbp-4h]

  for ( i = 1; i <= 12; ++i )
  {
    action.id = Answer::NetPacket::readInt32(inPacket);
    action.type = Answer::NetPacket::readInt32(inPacket);
    this->actionArry[i] = action;
  }
}


