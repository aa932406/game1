// Decompiled methods for class: MoneyRewardTaskData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MoneyRewardTaskData::~MoneyRewardTaskData(MoneyRewardTaskData *const this)
{
  MoneyRewardTaskData::~MoneyRewardTaskData(this);
  operator delete(this);
}


#####################################
void __cdecl MoneyRewardTaskData::CleanUp(MoneyRewardTaskData *const this)
{
  this->m_IsGetReward = 0;
  this->m_FinishTimes = 0;
  std::string::operator=(&this->m_MoneyRewardTaskInfo, byte_8CFE00);
  this->m_TaskId = 0;
  this->m_Star = 0;
  this->m_RandStarTimes = 0;
  this->m_PdbfFinishTimes = 0;
  this->m_EquipBackTaskId = 0;
  this->m_EquipBackTaskFinishTimes = 0;
  this->m_RandEquipBackTaskStarTimes = 0;
  this->m_JieBiaoTimes = 0;
  this->m_YaBiaoTimes = 0;
  this->m_TrailerQuality = 0;
  this->m_EndTime = 0;
  this->m_XiangYaoFinishTimes = 0;
  this->m_RefreshTimes = 0;
  std::string::operator=(&this->m_XiangYaoTask, byte_8CFE00);
}


#####################################
void __cdecl MoneyRewardTaskData::SaveToSqlString(
        MoneyRewardTaskData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t v4; // r15d
  int32_t v5; // r14d
  int32_t v6; // r13d
  int32_t v7; // r12d
  const char *v8; // rax
  const char *v9; // [rsp+D0h] [rbp-E0h]
  const char *v10; // [rsp+D8h] [rbp-D8h]
  int32_t m_RefreshTimes; // [rsp+E4h] [rbp-CCh]
  int32_t m_XiangYaoFinishTimes; // [rsp+E8h] [rbp-C8h]
  int32_t m_RandEquipBackTaskStarTimes; // [rsp+ECh] [rbp-C4h]
  int32_t m_EquipBackTaskFinishTimes; // [rsp+F0h] [rbp-C0h]
  int32_t m_EquipBackTaskId; // [rsp+F4h] [rbp-BCh]
  int32_t m_PdbfFinishTimes; // [rsp+F8h] [rbp-B8h]
  int32_t m_RandStarTimes; // [rsp+FCh] [rbp-B4h]
  int32_t m_Star; // [rsp+100h] [rbp-B0h]
  int32_t m_TaskId; // [rsp+104h] [rbp-ACh]
  const char *v20; // [rsp+108h] [rbp-A8h]
  int m_IsGetReward; // [rsp+110h] [rbp-A0h]
  int32_t m_FinishTimes; // [rsp+114h] [rbp-9Ch]
  const char *v23; // [rsp+118h] [rbp-98h]
  const char *v24; // [rsp+120h] [rbp-90h]
  int32_t v25; // [rsp+12Ch] [rbp-84h]
  int32_t v26; // [rsp+130h] [rbp-80h]
  int32_t v27; // [rsp+134h] [rbp-7Ch]
  int32_t v28; // [rsp+138h] [rbp-78h]
  int32_t v29; // [rsp+13Ch] [rbp-74h]
  std::string __x; // [rsp+160h] [rbp-50h] BYREF
  char v34; // [rsp+16Fh] [rbp-41h] BYREF
  std::string v35; // [rsp+170h] [rbp-40h] BYREF
  _BYTE v36[49]; // [rsp+17Fh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  v9 = (const char *)std::string::c_str(&this->m_ShenWeiTask);
  v10 = (const char *)std::string::c_str(&this->m_XiangYaoTask);
  m_RefreshTimes = this->m_RefreshTimes;
  m_XiangYaoFinishTimes = this->m_XiangYaoFinishTimes;
  m_RandEquipBackTaskStarTimes = this->m_RandEquipBackTaskStarTimes;
  m_EquipBackTaskFinishTimes = this->m_EquipBackTaskFinishTimes;
  m_EquipBackTaskId = this->m_EquipBackTaskId;
  m_PdbfFinishTimes = this->m_PdbfFinishTimes;
  m_RandStarTimes = this->m_RandStarTimes;
  m_Star = this->m_Star;
  m_TaskId = this->m_TaskId;
  v20 = (const char *)std::string::c_str(&this->m_MoneyRewardTaskInfo);
  m_IsGetReward = this->m_IsGetReward;
  m_FinishTimes = this->m_FinishTimes;
  v23 = (const char *)std::string::c_str(&this->m_ShenWeiTask);
  v24 = (const char *)std::string::c_str(&this->m_XiangYaoTask);
  v25 = this->m_RefreshTimes;
  v26 = this->m_XiangYaoFinishTimes;
  v27 = this->m_RandEquipBackTaskStarTimes;
  v28 = this->m_EquipBackTaskFinishTimes;
  v29 = this->m_EquipBackTaskId;
  v4 = this->m_PdbfFinishTimes;
  v5 = this->m_RandStarTimes;
  v6 = this->m_Star;
  v7 = this->m_TaskId;
  v8 = (const char *)std::string::c_str(&this->m_MoneyRewardTaskInfo);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_money_reward_task` (`cid`,`finishtimes`, `getreward`, `taskinfo`,`TaskId`,`Star`,`RandStarTimes`,`P"
    "dbfFinishTimes`,`EquipBackTaskId`,`EquipBackTaskFinishTimes`,`RandEquipBackTaskStarTimes`,`XiangYaoFinishTimes`,`Ref"
    "reshTimes`,`XiangYaoTask`,`ShenWeiTask`) VALUES (%lld,%d,%d,'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,'%s','%s') ON DUPLICATE "
    "KEY UPDATE `finishtimes`=%d, `getreward`=%d, `taskinfo`='%s',`TaskId`=%d,`Star`=%d,`RandStarTimes`=%d,`PdbfFinishTim"
    "es`=%d,`EquipBackTaskId`=%d,`EquipBackTaskFinishTimes`=%d,`RandEquipBackTaskStarTimes`=%d,`XiangYaoFinishTimes`=%d,`"
    "RefreshTimes`=%d,`XiangYaoTask`='%s',ShenWeiTask='%s'",
    nCid,
    this->m_FinishTimes,
    this->m_IsGetReward,
    v8,
    v7,
    v6,
    v5,
    v4,
    v29,
    v28,
    v27,
    v26,
    v25,
    v24,
    v23,
    m_FinishTimes,
    m_IsGetReward,
    v20,
    m_TaskId,
    m_Star,
    m_RandStarTimes,
    m_PdbfFinishTimes,
    m_EquipBackTaskId,
    m_EquipBackTaskFinishTimes,
    m_RandEquipBackTaskStarTimes,
    m_XiangYaoFinishTimes,
    m_RefreshTimes,
    v10,
    v9);
  std::allocator<char>::allocator(&v34);
  std::string::string(&__x, (char *)szSQL, &v34);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v34);
  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_trailer` (`cid`,`JieBiaoTimes`, `YaBiaoTimes`, `TrailerQuality`,`EndTime`) VALUES (%lld,%d,%d,%d,%d"
    ") ON DUPLICATE KEY UPDATE `JieBiaoTimes`=%d, `YaBiaoTimes`=%d, `TrailerQuality`=%d,`EndTime`=%d",
    nCid,
    this->m_JieBiaoTimes,
    this->m_YaBiaoTimes,
    this->m_TrailerQuality,
    this->m_EndTime,
    this->m_JieBiaoTimes,
    this->m_YaBiaoTimes,
    this->m_TrailerQuality,
    this->m_EndTime);
  std::allocator<char>::allocator(v36);
  std::string::string(&v35, (char *)szSQL, v36);
  std::list<std::string>::push_back(sqls, &v35);
  std::string::~string(&v35);
  std::allocator<char>::~allocator(v36);
}


#####################################
bool __cdecl MoneyRewardTaskData::LoadFromDB(
        MoneyRewardTaskData *const this,
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
  Answer::MySqlQuery *v10; // rax
  Answer::MySqlQuery result_0; // [rsp+30h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+50h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_money_reward_task` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( Answer::MySqlQuery::getRowCount(&result) == 1 )
  {
    this->m_FinishTimes = Answer::MySqlQuery::getIntValue(&result, "finishtimes", 0);
    this->m_IsGetReward = Answer::MySqlQuery::getIntValue(&result, "getreward", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "taskinfo", byte_8CFE00);
    std::string::operator=(&this->m_MoneyRewardTaskInfo, StringValue);
    this->m_TaskId = Answer::MySqlQuery::getIntValue(&result, "TaskId", 0);
    this->m_Star = Answer::MySqlQuery::getIntValue(&result, "Star", 0);
    this->m_RandStarTimes = Answer::MySqlQuery::getIntValue(&result, "RandStarTimes", 0);
    this->m_PdbfFinishTimes = Answer::MySqlQuery::getIntValue(&result, "PdbfFinishTimes", 0);
    this->m_EquipBackTaskId = Answer::MySqlQuery::getIntValue(&result, "EquipBackTaskId", 0);
    this->m_EquipBackTaskFinishTimes = Answer::MySqlQuery::getIntValue(&result, "EquipBackTaskFinishTimes", 0);
    this->m_RandEquipBackTaskStarTimes = Answer::MySqlQuery::getIntValue(&result, "RandEquipBackTaskStarTimes", 0);
    this->m_XiangYaoFinishTimes = Answer::MySqlQuery::getIntValue(&result, "XiangYaoFinishTimes", 0);
    this->m_RefreshTimes = Answer::MySqlQuery::getIntValue(&result, "RefreshTimes", 0);
    v8 = Answer::MySqlQuery::getStringValue(&result, "XiangYaoTask", byte_8CFE00);
    std::string::operator=(&this->m_XiangYaoTask, v8);
    v9 = Answer::MySqlQuery::getStringValue(&result, "ShenWeiTask", byte_8CFE00);
    std::string::operator=(&this->m_ShenWeiTask, v9);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_trailer` WHERE `cid`=%lld", nCid);
  v10 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_0, v10);
  if ( Answer::MySqlQuery::getRowCount(&result_0) == 1 )
  {
    this->m_JieBiaoTimes = Answer::MySqlQuery::getIntValue(&result_0, "JieBiaoTimes", 0);
    this->m_YaBiaoTimes = Answer::MySqlQuery::getIntValue(&result_0, "YaBiaoTimes", 0);
    this->m_TrailerQuality = Answer::MySqlQuery::getIntValue(&result_0, "TrailerQuality", 0);
    this->m_EndTime = Answer::MySqlQuery::getIntValue(&result_0, "EndTime", 0);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_0);
  return 1;
}


#####################################
void __cdecl MoneyRewardTaskData::PackageData(MoneyRewardTaskData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt8(packet, this->m_IsGetReward);
  Answer::NetPacket::writeInt32(packet, this->m_FinishTimes);
  Answer::NetPacket::writeUTF8(packet, &this->m_MoneyRewardTaskInfo);
  Answer::NetPacket::writeInt32(packet, this->m_TaskId);
  Answer::NetPacket::writeInt32(packet, this->m_Star);
  Answer::NetPacket::writeInt32(packet, this->m_RandStarTimes);
  Answer::NetPacket::writeInt32(packet, this->m_PdbfFinishTimes);
  Answer::NetPacket::writeInt32(packet, this->m_EquipBackTaskId);
  Answer::NetPacket::writeInt32(packet, this->m_EquipBackTaskFinishTimes);
  Answer::NetPacket::writeInt32(packet, this->m_RandEquipBackTaskStarTimes);
  Answer::NetPacket::writeInt32(packet, this->m_JieBiaoTimes);
  Answer::NetPacket::writeInt32(packet, this->m_YaBiaoTimes);
  Answer::NetPacket::writeInt32(packet, this->m_TrailerQuality);
  Answer::NetPacket::writeInt32(packet, this->m_EndTime);
  Answer::NetPacket::writeInt32(packet, this->m_XiangYaoFinishTimes);
  Answer::NetPacket::writeInt32(packet, this->m_RefreshTimes);
  Answer::NetPacket::writeUTF8(packet, &this->m_XiangYaoTask);
  Answer::NetPacket::writeUTF8(packet, &this->m_ShenWeiTask);
}


#####################################
void __cdecl MoneyRewardTaskData::UnPackageData(
        MoneyRewardTaskData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  Answer::NetPacket v3; // [rsp+20h] [rbp-40h] BYREF

  this->m_IsGetReward = Answer::NetPacket::readInt8(inPacket);
  this->m_FinishTimes = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8(&v3, (bool)inPacket);
  std::string::operator=(&this->m_MoneyRewardTaskInfo, &v3);
  std::string::~string(&v3);
  this->m_TaskId = Answer::NetPacket::readInt32(inPacket);
  this->m_Star = Answer::NetPacket::readInt32(inPacket);
  this->m_RandStarTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_PdbfFinishTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_EquipBackTaskId = Answer::NetPacket::readInt32(inPacket);
  this->m_EquipBackTaskFinishTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_RandEquipBackTaskStarTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_JieBiaoTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_YaBiaoTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_TrailerQuality = Answer::NetPacket::readInt32(inPacket);
  this->m_EndTime = Answer::NetPacket::readInt32(inPacket);
  this->m_XiangYaoFinishTimes = Answer::NetPacket::readInt32(inPacket);
  this->m_RefreshTimes = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v3.m_wOffset, (bool)inPacket);
  std::string::operator=(&this->m_XiangYaoTask, &v3.m_wOffset);
  std::string::~string(&v3.m_wOffset);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v3.m_size, (bool)inPacket);
  std::string::operator=(&this->m_ShenWeiTask, &v3.m_size);
  std::string::~string(&v3.m_size);
}


