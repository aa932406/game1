// Decompiled methods for class: MemChrSkillData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrSkillData::~MemChrSkillData(MemChrSkillData *const this)
{
  MemChrSkillData::~MemChrSkillData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrSkillData::CleanUp(MemChrSkillData *const this)
{
  std::string::operator=(&this->talents, byte_8CFE00);
  this->m_nPower = 0;
}


#####################################
void __cdecl MemChrSkillData::SaveToSqlString(
        MemChrSkillData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t m_nPower; // r12d
  const char *v5; // rbx
  int32_t v6; // r13d
  const char *v7; // rax
  std::string __x; // [rsp+30h] [rbp-30h] BYREF
  _BYTE v11[33]; // [rsp+3Fh] [rbp-21h] BYREF

  bzero(szSQL, 0x1000u);
  m_nPower = this->m_nPower;
  v5 = (const char *)std::string::c_str(&this->talents);
  v6 = this->m_nPower;
  v7 = (const char *)std::string::c_str(&this->talents);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_skill` (`cid`, `talents`,`power`) VALUES (%lld, '%s',%d) ON DUPLICATE KEY UPDATE `talents`='%s',power=%d",
    nCid,
    v7,
    v6,
    v5,
    m_nPower);
  std::allocator<char>::allocator(v11);
  std::string::string(&__x, (char *)szSQL, v11);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v11);
}


#####################################
bool __cdecl MemChrSkillData::LoadFromDB(
        MemChrSkillData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_skill` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "talents", byte_8CFE00);
    std::string::operator=(&this->talents, StringValue);
    this->m_nPower = Answer::MySqlQuery::getIntValue(&result, "power", 0);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrSkillData::PackageData(MemChrSkillData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeUTF8(packet, &this->talents);
  Answer::NetPacket::writeInt32(packet, this->m_nPower);
}


#####################################
void __cdecl MemChrSkillData::UnPackageData(MemChrSkillData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
  std::string::operator=(&this->talents, v3);
  std::string::~string(v3);
  this->m_nPower = Answer::NetPacket::readInt32(inPacket);
}


