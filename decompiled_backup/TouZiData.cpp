// Decompiled methods for class: TouZiData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl TouZiData::~TouZiData(TouZiData *const this)
{
  TouZiData::~TouZiData(this);
  operator delete(this);
}


#####################################
void __cdecl TouZiData::CleanUp(TouZiData *const this)
{
  this->m_SevenDayTouZiTime = 0;
  this->m_SevenDayRecord = 0;
  this->m_MonthTouZiTime = 0;
  this->m_MonthTouZiRecord = 0;
}


#####################################
void __cdecl TouZiData::SaveToSqlString(
        TouZiData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+50h] [rbp-20h] BYREF
  _BYTE v7[17]; // [rsp+5Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_tou_zi` (`cid`, `seven_day_time`, `seven_day_record`, `month_time`,`month_record`) VALUES (%lld"
    ", %d, %d, %d, %d) ON DUPLICATE KEY UPDATE `seven_day_time`=%d, `seven_day_record`=%d, `month_time`=%d,`month_record`=%d",
    nCid,
    this->m_SevenDayTouZiTime,
    this->m_SevenDayRecord,
    this->m_MonthTouZiTime,
    this->m_MonthTouZiRecord,
    this->m_SevenDayTouZiTime,
    this->m_SevenDayRecord,
    this->m_MonthTouZiTime,
    this->m_MonthTouZiRecord);
  std::allocator<char>::allocator(v7);
  std::string::string(&__x, (char *)szSQL, v7);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v7);
}


#####################################
bool __cdecl TouZiData::LoadFromDB(
        TouZiData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_tou_zi` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_SevenDayTouZiTime = Answer::MySqlQuery::getIntValue(&result, "seven_day_time", 0);
    this->m_SevenDayRecord = Answer::MySqlQuery::getIntValue(&result, "seven_day_record", 0);
    this->m_MonthTouZiTime = Answer::MySqlQuery::getIntValue(&result, "month_time", 0);
    this->m_MonthTouZiRecord = Answer::MySqlQuery::getIntValue(&result, "month_record", 0);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl TouZiData::PackageData(TouZiData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt32(packet, this->m_SevenDayTouZiTime);
  Answer::NetPacket::writeInt32(packet, this->m_SevenDayRecord);
  Answer::NetPacket::writeInt32(packet, this->m_MonthTouZiTime);
  Answer::NetPacket::writeInt32(packet, this->m_MonthTouZiRecord);
}


#####################################
void __cdecl TouZiData::UnPackageData(TouZiData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  this->m_SevenDayTouZiTime = Answer::NetPacket::readInt32(inPacket);
  this->m_SevenDayRecord = Answer::NetPacket::readInt32(inPacket);
  this->m_MonthTouZiTime = Answer::NetPacket::readInt32(inPacket);
  this->m_MonthTouZiRecord = Answer::NetPacket::readInt32(inPacket);
}


