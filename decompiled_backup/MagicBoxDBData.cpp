// Decompiled methods for class: MagicBoxDBData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MagicBoxDBData::~MagicBoxDBData(MagicBoxDBData *const this)
{
  MagicBoxDBData::~MagicBoxDBData(this);
  operator delete(this);
}


#####################################
void __cdecl MagicBoxDBData::CleanUp(MagicBoxDBData *const this)
{
  this->nCombiPoints = 0;
  this->nLastReviveTime = 0;
  std::string::operator=(&this->strActiveScrolls, byte_8CFE00);
  std::string::operator=(&this->strSuccessIds, byte_8CFE00);
}


#####################################
void __cdecl MagicBoxDBData::SaveToSqlString(
        MagicBoxDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // r13
  const char *v5; // r12
  int32_t nLastReviveTime; // r15d
  int32_t nCombiPoints; // r14d
  const char *v8; // rbx
  const char *v9; // rax
  std::string __x; // [rsp+50h] [rbp-40h] BYREF
  _BYTE v13[49]; // [rsp+5Fh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  v4 = (const char *)std::string::c_str(&this->strSuccessIds);
  v5 = (const char *)std::string::c_str(&this->strActiveScrolls);
  nLastReviveTime = this->nLastReviveTime;
  nCombiPoints = this->nCombiPoints;
  v8 = (const char *)std::string::c_str(&this->strSuccessIds);
  v9 = (const char *)std::string::c_str(&this->strActiveScrolls);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_char_magic_box` (`cid`,`combi_points`,`revive_time`,`active_scrolls`,`success_ids`) VALUES (%lld,%d"
    ",%d,'%s','%s') ON DUPLICATE KEY UPDATE `combi_points`=%d,`revive_time`=%d,`active_scrolls`='%s',`success_ids`='%s'",
    nCid,
    this->nCombiPoints,
    this->nLastReviveTime,
    v9,
    v8,
    nCombiPoints,
    nLastReviveTime,
    v5,
    v4);
  std::allocator<char>::allocator(v13);
  std::string::string(&__x, (char *)szSQL, v13);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v13);
}


#####################################
bool __cdecl MagicBoxDBData::LoadFromDB(
        MagicBoxDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_magic_box` WHERE `cid`= %lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->nCombiPoints = Answer::MySqlQuery::getIntValue(&result, "combi_points", 0);
    this->nLastReviveTime = Answer::MySqlQuery::getIntValue(&result, "revive_time", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "active_scrolls", byte_8CFE00);
    std::string::operator=(&this->strActiveScrolls, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "success_ids", byte_8CFE00);
    std::string::operator=(&this->strSuccessIds, v8);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MagicBoxDBData::PackageData(MagicBoxDBData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt32(packet, this->nCombiPoints);
  Answer::NetPacket::writeInt32(packet, this->nLastReviveTime);
  Answer::NetPacket::writeUTF8(packet, &this->strActiveScrolls);
  Answer::NetPacket::writeUTF8(packet, &this->strSuccessIds);
}


#####################################
void __cdecl MagicBoxDBData::UnPackageData(MagicBoxDBData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[16]; // [rsp+20h] [rbp-30h] BYREF
  _BYTE v4[32]; // [rsp+30h] [rbp-20h] BYREF

  this->nCombiPoints = Answer::NetPacket::readInt32(inPacket);
  this->nLastReviveTime = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
  std::string::operator=(&this->strActiveScrolls, v3);
  std::string::~string(v3);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v4, (bool)inPacket);
  std::string::operator=(&this->strSuccessIds, v4);
  std::string::~string(v4);
}


