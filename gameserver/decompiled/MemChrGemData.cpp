// Decompiled methods for class: MemChrGemData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrGemData::~MemChrGemData(MemChrGemData *const this)
{
  MemChrGemData::~MemChrGemData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrGemData::CleanUp(MemChrGemData *const this)
{
  std::string::operator=(&this->gemInfo, byte_8CFE00);
  std::string::operator=(&this->posLevel, byte_8CFE00);
  std::string::operator=(&this->Strengthen, byte_8CFE00);
  std::string::operator=(&this->ShenYaoEquipPos, byte_8CFE00);
}


#####################################
void __cdecl MemChrGemData::SaveToSqlString(
        MemChrGemData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // r15
  const char *v5; // r14
  const char *v6; // r13
  const char *v7; // r12
  const char *v8; // rbx
  const char *v9; // rax
  const char *v10; // [rsp+30h] [rbp-70h]
  const char *v11; // [rsp+38h] [rbp-68h]
  std::string __x; // [rsp+60h] [rbp-40h] BYREF
  _BYTE v15[49]; // [rsp+6Fh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  v10 = (const char *)std::string::c_str(&this->ShenYaoEquipPos);
  v4 = (const char *)std::string::c_str(&this->Strengthen);
  v5 = (const char *)std::string::c_str(&this->posLevel);
  v6 = (const char *)std::string::c_str(&this->gemInfo);
  v7 = (const char *)std::string::c_str(&this->ShenYaoEquipPos);
  v8 = (const char *)std::string::c_str(&this->Strengthen);
  v11 = (const char *)std::string::c_str(&this->posLevel);
  v9 = (const char *)std::string::c_str(&this->gemInfo);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_gem` (`cid`, `gems`, `pos_level`,`streng_then`,`shen_yao`) VALUES (%lld, '%s', '%s','%s','%s') "
    "ON DUPLICATE KEY UPDATE `gems`='%s', `pos_level`='%s',`streng_then`='%s',`shen_yao`='%s'",
    nCid,
    v9,
    v11,
    v8,
    v7,
    v6,
    v5,
    v4,
    v10);
  std::allocator<char>::allocator(v15);
  std::string::string(&__x, (char *)szSQL, v15);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v15);
}


#####################################
bool __cdecl MemChrGemData::LoadFromDB(
        MemChrGemData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  const char *v9; // rax
  const char *v10; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_gem` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "gems", byte_8CFE00);
    std::string::operator=(&this->gemInfo, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "pos_level", byte_8CFE00);
    std::string::operator=(&this->posLevel, v8);
    v9 = Answer::MySqlQuery::getStringValue(&result, "streng_then", byte_8CFE00);
    std::string::operator=(&this->Strengthen, v9);
    v10 = Answer::MySqlQuery::getStringValue(&result, "shen_yao", byte_8CFE00);
    std::string::operator=(&this->ShenYaoEquipPos, v10);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrGemData::PackageData(MemChrGemData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeUTF8(packet, &this->gemInfo);
  Answer::NetPacket::writeUTF8(packet, &this->posLevel);
  Answer::NetPacket::writeUTF8(packet, &this->Strengthen);
  Answer::NetPacket::writeUTF8(packet, &this->ShenYaoEquipPos);
}


#####################################
void __cdecl MemChrGemData::UnPackageData(MemChrGemData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  Answer::NetPacket v3; // [rsp+20h] [rbp-50h] BYREF

  Answer::NetPacket::readUTF8(&v3, (bool)inPacket);
  std::string::operator=(&this->gemInfo, &v3);
  std::string::~string(&v3);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v3.m_wOffset, (bool)inPacket);
  std::string::operator=(&this->posLevel, &v3.m_wOffset);
  std::string::~string(&v3.m_wOffset);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v3.m_size, (bool)inPacket);
  std::string::operator=(&this->Strengthen, &v3.m_size);
  std::string::~string(&v3.m_size);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v3.m_pool, (bool)inPacket);
  std::string::operator=(&this->ShenYaoEquipPos, &v3.m_pool);
  std::string::~string(&v3.m_pool);
}


