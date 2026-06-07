// Decompiled methods for class: CharFamilyDBData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl CharFamilyDBData::~CharFamilyDBData(CharFamilyDBData *const this)
{
  CharFamilyDBData::~CharFamilyDBData(this);
  operator delete(this);
}


#####################################
void __cdecl CharFamilyDBData::CleanUp(CharFamilyDBData *const this)
{
  this->nFamilyId = 0;
  this->nPosition = 0;
  this->nContribution = 0;
  this->nDailyContribution = 0;
  std::string::operator=(&this->strSkills, byte_8CFE00);
  this->nMedLevel = 0;
  this->nMedRes = 0;
  this->nHoe = 0;
  this->EnterDungeionFamilyId = 0;
  this->EnterCount = 0;
  this->EnterTime = 0;
}


#####################################
void __cdecl CharFamilyDBData::SaveToSqlString(
        CharFamilyDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t EnterTime; // r12d
  int32_t EnterCount; // r13d
  FamilyId_t EnterDungeionFamilyId; // r14
  int32_t nHoe; // r15d
  const char *v8; // rax
  int32_t nMedRes; // [rsp+98h] [rbp-98h]
  int32_t nMedLevel; // [rsp+9Ch] [rbp-94h]
  const char *v11; // [rsp+A0h] [rbp-90h]
  int32_t nDailyContribution; // [rsp+A8h] [rbp-88h]
  int32_t nContribution; // [rsp+ACh] [rbp-84h]
  int32_t v14; // [rsp+B0h] [rbp-80h]
  int32_t v15; // [rsp+B4h] [rbp-7Ch]
  FamilyId_t v16; // [rsp+B8h] [rbp-78h]
  int32_t v17; // [rsp+C4h] [rbp-6Ch]
  int32_t v18; // [rsp+C8h] [rbp-68h]
  int32_t v19; // [rsp+CCh] [rbp-64h]
  std::string __x; // [rsp+F0h] [rbp-40h] BYREF
  _BYTE v23[49]; // [rsp+FFh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  EnterTime = this->EnterTime;
  EnterCount = this->EnterCount;
  EnterDungeionFamilyId = this->EnterDungeionFamilyId;
  nHoe = this->nHoe;
  nMedRes = this->nMedRes;
  nMedLevel = this->nMedLevel;
  v11 = (const char *)std::string::c_str(&this->strSkills);
  nDailyContribution = this->nDailyContribution;
  nContribution = this->nContribution;
  v14 = this->EnterTime;
  v15 = this->EnterCount;
  v16 = this->EnterDungeionFamilyId;
  v17 = this->nHoe;
  v18 = this->nMedRes;
  v19 = this->nMedLevel;
  v8 = (const char *)std::string::c_str(&this->strSkills);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT `mem_chr_family`( `cid`,`family_id`,`position`,`contribute`,`daily_contribute`,`skills`,`med_level`,`med_res`"
    ",`hoe` ,`enter_dungeion_family_id`,`enter_count`,`enter_time`) VALUES (%lld,%lld,%d,%d,%d,'%s',%d,%d,%d,%lld,%d,%d) "
    "ON DUPLICATE KEY UPDATE `contribute`=%d,`daily_contribute`=%d,`skills`='%s',`med_level`=%d,`med_res`=%d,`hoe`=%d,`en"
    "ter_dungeion_family_id`=%lld,`enter_count`=%d,`enter_time`=%d",
    nCid,
    this->nFamilyId,
    this->nPosition,
    this->nContribution,
    this->nDailyContribution,
    v8,
    v19,
    v18,
    v17,
    v16,
    v15,
    v14,
    nContribution,
    nDailyContribution,
    v11,
    nMedLevel,
    nMedRes,
    nHoe,
    EnterDungeionFamilyId,
    EnterCount,
    EnterTime);
  std::allocator<char>::allocator(v23);
  std::string::string(&__x, (char *)szSQL, v23);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v23);
}


#####################################
bool __cdecl CharFamilyDBData::LoadFromDB(
        CharFamilyDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  bool v8; // bl
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_family` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->nFamilyId = Answer::MySqlQuery::getInt64Value(&result, "family_id", 0);
    this->nPosition = Answer::MySqlQuery::getIntValue(&result, "position", 0);
    this->nContribution = Answer::MySqlQuery::getIntValue(&result, "contribute", 0);
    this->nDailyContribution = Answer::MySqlQuery::getIntValue(&result, "daily_contribute", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "skills", byte_8CFE00);
    std::string::operator=(&this->strSkills, StringValue);
    this->nMedLevel = Answer::MySqlQuery::getIntValue(&result, "med_level", 0);
    this->nMedRes = Answer::MySqlQuery::getIntValue(&result, "med_res", 0);
    this->nHoe = Answer::MySqlQuery::getIntValue(&result, "hoe", 0);
    this->EnterDungeionFamilyId = Answer::MySqlQuery::getInt64Value(&result, "enter_dungeion_family_id", 0);
    this->EnterCount = Answer::MySqlQuery::getIntValue(&result, "enter_count", 0);
    this->EnterTime = Answer::MySqlQuery::getIntValue(&result, "enter_time", 0);
    v8 = 1;
  }
  else
  {
    v8 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return v8;
}


#####################################
void __cdecl CharFamilyDBData::PackageData(CharFamilyDBData *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, this->nFamilyId);
    Answer::NetPacket::writeInt8(packet, this->nPosition);
    Answer::NetPacket::writeInt32(packet, this->nContribution);
    Answer::NetPacket::writeInt32(packet, this->nDailyContribution);
    Answer::NetPacket::writeUTF8(packet, &this->strSkills);
    Answer::NetPacket::writeInt32(packet, this->nMedLevel);
    Answer::NetPacket::writeInt32(packet, this->nMedRes);
    Answer::NetPacket::writeInt32(packet, this->nHoe);
    Answer::NetPacket::writeInt64(packet, this->EnterDungeionFamilyId);
    Answer::NetPacket::writeInt32(packet, this->EnterCount);
    Answer::NetPacket::writeInt32(packet, this->EnterTime);
  }
}


#####################################
void __cdecl CharFamilyDBData::UnPackageData(CharFamilyDBData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  if ( inPacket )
  {
    this->nFamilyId = Answer::NetPacket::readInt64(inPacket);
    this->nPosition = Answer::NetPacket::readInt8(inPacket);
    this->nContribution = Answer::NetPacket::readInt32(inPacket);
    this->nDailyContribution = Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
    std::string::operator=(&this->strSkills, v3);
    std::string::~string(v3);
    this->nMedLevel = Answer::NetPacket::readInt32(inPacket);
    this->nMedRes = Answer::NetPacket::readInt32(inPacket);
    this->nHoe = Answer::NetPacket::readInt32(inPacket);
    this->EnterDungeionFamilyId = Answer::NetPacket::readInt64(inPacket);
    this->EnterCount = Answer::NetPacket::readInt32(inPacket);
    this->EnterTime = Answer::NetPacket::readInt32(inPacket);
  }
}


