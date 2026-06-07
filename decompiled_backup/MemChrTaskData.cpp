// Decompiled methods for class: MemChrTaskData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl MemChrTaskData::~MemChrTaskData(MemChrTaskData *const this)
{
  MemChrTaskData::~MemChrTaskData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrTaskData::SaveToSqlString(
        MemChrTaskData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t monster; // ebx
  int32_t state; // r12d
  MemChrTask *v6; // rax
  std::string __x; // [rsp+30h] [rbp-40h] BYREF
  char v10; // [rsp+3Fh] [rbp-31h] BYREF
  std::string v11; // [rsp+40h] [rbp-30h] BYREF
  char v12; // [rsp+57h] [rbp-19h] BYREF
  int32_t vtSize; // [rsp+58h] [rbp-18h]
  int32_t i; // [rsp+5Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_task` WHERE `cid`=%lld", nCid);
  std::allocator<char>::allocator(&v10);
  std::string::string(&__x, (char *)szSQL, &v10);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v10);
  vtSize = std::vector<MemChrTask>::size(&this->taskVt);
  for ( i = 0; i < vtSize; ++i )
  {
    bzero(szSQL, 0x1000u);
    monster = std::vector<MemChrTask>::operator[](&this->taskVt, i)->monster;
    state = std::vector<MemChrTask>::operator[](&this->taskVt, i)->state;
    v6 = std::vector<MemChrTask>::operator[](&this->taskVt, i);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_task` (`cid`, `tid`, `state`, `monster`) VALUES (%lld, %d, %d, %d)",
      nCid,
      v6->id,
      state,
      monster);
    std::allocator<char>::allocator(&v12);
    std::string::string(&v11, (char *)szSQL, &v12);
    std::list<std::string>::push_back(sqls, &v11);
    std::string::~string(&v11);
    std::allocator<char>::~allocator(&v12);
  }
}


#####################################
bool __cdecl MemChrTaskData::LoadFromDB(
        MemChrTaskData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  int RowCount; // eax
  MemChrTask task; // [rsp+30h] [rbp-40h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_task` WHERE `cid`=%lld\n", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  RowCount = Answer::MySqlQuery::getRowCount(&result);
  std::vector<MemChrTask>::reserve(&this->taskVt, RowCount);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    *(_QWORD *)&task.id = 0;
    task.monster = 0;
    task.id = Answer::MySqlQuery::getIntValue(&result, "tid", 0);
    task.state = Answer::MySqlQuery::getIntValue(&result, "state", 0);
    task.monster = Answer::MySqlQuery::getIntValue(&result, "monster", 0);
    std::vector<MemChrTask>::push_back(&this->taskVt, &task);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrTaskData::PackageData(MemChrTaskData *const this, Answer::NetPacket *packet)
{
  int32_t id; // edx
  int32_t state; // edx
  int32_t monster; // edx
  int32_t vtSize; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  vtSize = std::vector<MemChrTask>::size(&this->taskVt);
  Answer::NetPacket::writeInt32(packet, vtSize);
  for ( i = 0; i < vtSize; ++i )
  {
    id = std::vector<MemChrTask>::operator[](&this->taskVt, i)->id;
    Answer::NetPacket::writeInt32(packet, id);
    state = std::vector<MemChrTask>::operator[](&this->taskVt, i)->state;
    Answer::NetPacket::writeInt32(packet, state);
    monster = std::vector<MemChrTask>::operator[](&this->taskVt, i)->monster;
    Answer::NetPacket::writeInt32(packet, monster);
  }
}


#####################################
void __cdecl MemChrTaskData::UnPackageData(MemChrTaskData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  MemChrTask task; // [rsp+20h] [rbp-20h] BYREF
  int32_t taskCount; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  taskCount = Answer::NetPacket::readInt32(inPacket);
  std::vector<MemChrTask>::reserve(&this->taskVt, taskCount);
  for ( i = 0; i < taskCount; ++i )
  {
    *(_QWORD *)&task.id = 0;
    task.monster = 0;
    task.id = Answer::NetPacket::readInt32(inPacket);
    task.state = Answer::NetPacket::readInt32(inPacket);
    task.monster = Answer::NetPacket::readInt32(inPacket);
    std::vector<MemChrTask>::push_back(&this->taskVt, &task);
  }
}


