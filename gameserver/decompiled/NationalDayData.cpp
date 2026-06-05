// Decompiled methods for class: NationalDayData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl NationalDayData::~NationalDayData(NationalDayData *const this)
{
  NationalDayData::~NationalDayData(this);
  operator delete(this);
}


#####################################
void __cdecl NationalDayData::CleanUp(NationalDayData *const this)
{
  this->m_Level = 0;
  this->m_Exp = 0;
  this->m_UnLockReward = 0;
  this->m_OrdinaryReward = 0;
  this->m_SeniorReward = 0;
  std::string::operator=(&this->m_NationalInfo, byte_8CFE00);
}


#####################################
void __cdecl NationalDayData::SaveToSqlString(
        NationalDayData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  int32_t m_OrdinaryReward; // r15d
  int32_t m_UnLockReward; // r14d
  int32_t m_Exp; // r13d
  int32_t m_Level; // r12d
  const char *v9; // rax
  int32_t m_SeniorReward; // [rsp+5Ch] [rbp-64h]
  std::string __x; // [rsp+80h] [rbp-40h] BYREF
  _BYTE v14[49]; // [rsp+8Fh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  v4 = (const char *)std::string::c_str(&this->m_NationalInfo);
  m_SeniorReward = this->m_SeniorReward;
  m_OrdinaryReward = this->m_OrdinaryReward;
  m_UnLockReward = this->m_UnLockReward;
  m_Exp = this->m_Exp;
  m_Level = this->m_Level;
  v9 = (const char *)std::string::c_str(&this->m_NationalInfo);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_char_guo_qing` (`cid`,`level`,`exp`,`lock`,`ordinary_reward`,`senior_reward`,`national_info`) VALUE"
    "S (%lld,%d,%d,%d,%d,%d,'%s') ON DUPLICATE KEY UPDATE `level`=%d,`exp`=%d,`lock`=%d,`ordinary_reward`=%d,`senior_rewa"
    "rd`=%d,`national_info`='%s'",
    nCid,
    this->m_Level,
    this->m_Exp,
    this->m_UnLockReward,
    this->m_OrdinaryReward,
    this->m_SeniorReward,
    v9,
    m_Level,
    m_Exp,
    m_UnLockReward,
    m_OrdinaryReward,
    m_SeniorReward,
    v4);
  std::allocator<char>::allocator(v14);
  std::string::string(&__x, (char *)szSQL, v14);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v14);
}


#####################################
bool __cdecl NationalDayData::LoadFromDB(
        NationalDayData *const this,
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
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_guo_qing` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_Level = Answer::MySqlQuery::getIntValue(&result, "level", 0);
    this->m_Exp = Answer::MySqlQuery::getIntValue(&result, "exp", 0);
    this->m_UnLockReward = Answer::MySqlQuery::getIntValue(&result, "lock", 0);
    this->m_OrdinaryReward = Answer::MySqlQuery::getIntValue(&result, "ordinary_reward", 0);
    this->m_SeniorReward = Answer::MySqlQuery::getIntValue(&result, "senior_reward", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "national_info", byte_8CFE00);
    std::string::operator=(&this->m_NationalInfo, StringValue);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl NationalDayData::PackageData(NationalDayData *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_Level);
    Answer::NetPacket::writeInt32(packet, this->m_Exp);
    Answer::NetPacket::writeInt32(packet, this->m_UnLockReward);
    Answer::NetPacket::writeInt32(packet, this->m_OrdinaryReward);
    Answer::NetPacket::writeInt32(packet, this->m_SeniorReward);
    Answer::NetPacket::writeUTF8(packet, &this->m_NationalInfo);
  }
}


#####################################
void __cdecl NationalDayData::UnPackageData(NationalDayData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  if ( inPacket )
  {
    this->m_Level = Answer::NetPacket::readInt32(inPacket);
    this->m_Exp = Answer::NetPacket::readInt32(inPacket);
    this->m_UnLockReward = Answer::NetPacket::readInt32(inPacket);
    this->m_OrdinaryReward = Answer::NetPacket::readInt32(inPacket);
    this->m_SeniorReward = Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
    std::string::operator=(&this->m_NationalInfo, v3);
    std::string::~string(v3);
  }
}


