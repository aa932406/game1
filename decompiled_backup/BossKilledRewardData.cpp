// Decompiled methods for class: BossKilledRewardData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl BossKilledRewardData::~BossKilledRewardData(BossKilledRewardData *const this)
{
  BossKilledRewardData::~BossKilledRewardData(this);
  operator delete(this);
}


#####################################
void __cdecl BossKilledRewardData::CleanUp(BossKilledRewardData *const this)
{
  std::string::operator=(&this->RewardString, byte_8CFE00);
}


#####################################
void __cdecl BossKilledRewardData::SaveToSqlString(
        BossKilledRewardData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  const char *v5; // rax
  std::string __x; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v9[17]; // [rsp+2Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  v4 = (const char *)std::string::c_str(&this->RewardString);
  v5 = (const char *)std::string::c_str(&this->RewardString);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_boss_killed` (cid, reward_info) VALUES (%lld,'%s') on duplicate key update reward_info='%s'",
    nCid,
    v5,
    v4);
  std::allocator<char>::allocator(v9);
  std::string::string(&__x, (char *)szSQL, v9);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v9);
}


#####################################
bool __cdecl BossKilledRewardData::LoadFromDB(
        BossKilledRewardData *const this,
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
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_boss_killed` WHERE `Cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "reward_info", byte_8CFE00);
    std::string::operator=(&this->RewardString, StringValue);
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
void __cdecl BossKilledRewardData::PackageData(BossKilledRewardData *const this, Answer::NetPacket *packet)
{
  if ( packet )
    Answer::NetPacket::writeUTF8(packet, &this->RewardString);
}


#####################################
void __cdecl BossKilledRewardData::UnPackageData(
        BossKilledRewardData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  if ( inPacket )
  {
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
    std::string::operator=(&this->RewardString, v3);
    std::string::~string(v3);
  }
}


