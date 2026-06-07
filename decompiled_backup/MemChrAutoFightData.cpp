// Decompiled methods for class: MemChrAutoFightData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrAutoFightData::~MemChrAutoFightData(MemChrAutoFightData *const this)
{
  MemChrAutoFightData::~MemChrAutoFightData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrAutoFightData::CleanUp(MemChrAutoFightData *const this)
{
  bzero(&this->data, 0x4B2u);
}


#####################################
void __cdecl MemChrAutoFightData::SaveToSqlString(
        MemChrAutoFightData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+30h] [rbp-20h] BYREF
  _BYTE v7[17]; // [rsp+3Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_auto_fight` (`cid`, `fight`, `pick`) VALUES (%lld, '%s', '%s') ON DUPLICATE KEY UPDATE `fight`="
    "'%s', `pick`='%s'",
    nCid,
    this->data.fight,
    this->data.pick,
    this->data.fight,
    this->data.pick);
  std::allocator<char>::allocator(v7);
  std::string::string(&__x, (char *)szSQL, v7);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v7);
}


#####################################
bool __cdecl MemChrAutoFightData::LoadFromDB(
        MemChrAutoFightData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  bool v9; // bl
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_auto_fight` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "fight", byte_8CFE00);
    snprintf(this->data.fight, 0x258u, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "pick", byte_8CFE00);
    snprintf(this->data.pick, 0x258u, v8);
    v9 = 1;
  }
  else
  {
    v9 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return v9;
}


#####################################
void __cdecl MemChrAutoFightData::PackageData(MemChrAutoFightData *const this, Answer::NetPacket *packet)
{
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  char v3; // [rsp+1Fh] [rbp-21h] BYREF
  std::string v4; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+2Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(&v3);
  std::string::string(&val, &this->data, &v3);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(&v3);
  std::allocator<char>::allocator(v5);
  std::string::string(&v4, this->data.pick, v5);
  Answer::NetPacket::writeUTF8(packet, &v4);
  std::string::~string(&v4);
  std::allocator<char>::~allocator(v5);
}


#####################################
void __cdecl MemChrAutoFightData::UnPackageData(
        MemChrAutoFightData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  const char *v3; // rax
  const char *v4; // rax
  std::string v5[2]; // [rsp+20h] [rbp-30h] BYREF
  std::string v6; // [rsp+30h] [rbp-20h] BYREF

  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v5, (bool)inPacket);
  v3 = (const char *)std::string::c_str(v5);
  snprintf(this->data.fight, 0x258u, v3);
  std::string::~string(v5);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v6, (bool)inPacket);
  v4 = (const char *)std::string::c_str(&v6);
  snprintf(this->data.pick, 0x258u, v4);
  std::string::~string(&v6);
}


