// Decompiled methods for class: CJueWeiData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CJueWeiData::~CJueWeiData(CJueWeiData *const this)
{
  CJueWeiData::~CJueWeiData(this);
  operator delete(this);
}


#####################################
void __cdecl CJueWeiData::SaveToSqlString(
        CJueWeiData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v7[17]; // [rsp+2Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT `mem_char_jue_wei`(`cid`,`level`) VALUES (%lld,%d) ON DUPLICATE KEY UPDATE `level`=%d",
    nCid,
    this->nJueWei,
    this->nJueWei);
  std::allocator<char>::allocator(v7);
  std::string::string(&__x, (char *)szSQL, v7);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v7);
}


#####################################
bool __cdecl CJueWeiData::LoadFromDB(
        CJueWeiData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_jue_wei` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->nJueWei = Answer::MySqlQuery::getIntValue(&result, "level", 0);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CJueWeiData::PackageData(CJueWeiData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt8(packet, this->nJueWei);
}


#####################################
void __cdecl CJueWeiData::UnPackageData(CJueWeiData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  this->nJueWei = Answer::NetPacket::readInt8(inPacket);
}


