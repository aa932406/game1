// Decompiled methods for class: MemChrTaskCycleData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrTaskCycleData::~MemChrTaskCycleData(MemChrTaskCycleData *const this)
{
  MemChrTaskCycleData::~MemChrTaskCycleData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrTaskCycleData::CleanUp(MemChrTaskCycleData *const this)
{
  this->nFinishTimes = 0;
  this->nTaskId = 0;
  this->nState = 0;
}


#####################################
void __cdecl MemChrTaskCycleData::SaveToSqlString(
        MemChrTaskCycleData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v7[17]; // [rsp+4Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_cycle_task` (`cid`,`finishtimes`, `taskid`, `state`) VALUES (%lld,%d,%d,%d) ON DUPLICATE KEY UPDATE"
    " `finishtimes`=%d, `taskid`=%d, `state`=%d",
    nCid,
    this->nFinishTimes,
    this->nTaskId,
    this->nState,
    this->nFinishTimes,
    this->nTaskId,
    this->nState);
  std::allocator<char>::allocator(v7);
  std::string::string(&__x, (char *)szSQL, v7);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v7);
}


#####################################
bool __cdecl MemChrTaskCycleData::LoadFromDB(
        MemChrTaskCycleData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  bool v7; // bl
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_cycle_task` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( Answer::MySqlQuery::getRowCount(&result) == 1 )
  {
    this->nFinishTimes = Answer::MySqlQuery::getIntValue(&result, "finishtimes", 0);
    this->nTaskId = Answer::MySqlQuery::getIntValue(&result, "taskid", 0);
    this->nState = Answer::MySqlQuery::getIntValue(&result, "state", 0);
    v7 = 1;
  }
  else
  {
    v7 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return v7;
}


#####################################
void __cdecl MemChrTaskCycleData::PackageData(MemChrTaskCycleData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt32(packet, this->nFinishTimes);
  Answer::NetPacket::writeInt32(packet, this->nTaskId);
  Answer::NetPacket::writeInt8(packet, this->nState);
}


#####################################
void __cdecl MemChrTaskCycleData::UnPackageData(
        MemChrTaskCycleData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  this->nFinishTimes = Answer::NetPacket::readInt32(inPacket);
  this->nTaskId = Answer::NetPacket::readInt32(inPacket);
  this->nState = Answer::NetPacket::readInt8(inPacket);
}


