// Decompiled methods for class: MemChrDepotData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl MemChrDepotData::~MemChrDepotData(MemChrDepotData *const this)
{
  MemChrDepotData::~MemChrDepotData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrDepotData::CleanUp(MemChrDepotData *const this)
{
  bzero(this->gambleDepot, 0x4600u);
  bzero(this->Currency, 0x60u);
  this->OpneCount = 0;
  std::string::operator=(&this->SecondPassword, byte_8CFE00);
  std::string::operator=(&this->Password, byte_8CFE00);
}


#####################################
void __cdecl MemChrDepotData::SaveToSqlString(
        MemChrDepotData *const this,
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
  int32_t OpneCount; // [rsp+68h] [rbp-88h]
  int32_t v11; // [rsp+6Ch] [rbp-84h]
  std::string CurrencyString; // [rsp+90h] [rbp-60h] BYREF
  std::string __x; // [rsp+A0h] [rbp-50h] BYREF
  char v16; // [rsp+AFh] [rbp-41h] BYREF
  std::string v17; // [rsp+B0h] [rbp-40h] BYREF
  char v18; // [rsp+BBh] [rbp-35h] BYREF
  int32_t i; // [rsp+BCh] [rbp-34h]

  for ( i = 0; i <= 559; ++i )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_bag` (`cid`, `bag`, `slot`, `id`, `class`, `count`, `bind`, `endtime`, `srcid`) VALUES (%lld,"
      " %d, %d, %d, %d, %d, %d, %d,%lld) on duplicate key update `id`=%d, `class`=%d, `count`=%d, `bind`=%d, `endtime`=%d, `srcid`=%lld",
      nCid,
      2,
      i,
      this->gambleDepot[i].itemId,
      this->gambleDepot[i].itemClass,
      this->gambleDepot[i].itemCount,
      this->gambleDepot[i].bind,
      this->gambleDepot[i].endTime,
      this->gambleDepot[i].srcId,
      this->gambleDepot[i].itemId,
      this->gambleDepot[i].itemClass,
      this->gambleDepot[i].itemCount,
      this->gambleDepot[i].bind,
      this->gambleDepot[i].endTime,
      this->gambleDepot[i].srcId);
    std::allocator<char>::allocator(&v16);
    std::string::string(&__x, (char *)szSQL, &v16);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v16);
  }
  MemChrDepotData::GetCurrencyString((MemChrDepotData *const)&CurrencyString);
  bzero(szSQL, 0x1000u);
  v4 = (const char *)std::string::c_str(&this->SecondPassword);
  v5 = (const char *)std::string::c_str(&this->Password);
  OpneCount = this->OpneCount;
  v6 = (const char *)std::string::c_str(&CurrencyString);
  v7 = (const char *)std::string::c_str(&this->SecondPassword);
  v8 = (const char *)std::string::c_str(&this->Password);
  v11 = this->OpneCount;
  v9 = (const char *)std::string::c_str(&CurrencyString);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_depot` (Cid,CurrencyString,open_count,password,second_password) VALUES(%lld,'%s',%d,'%s','%s') "
    "on duplicate key update CurrencyString = '%s',open_count=%d,password='%s',second_password='%s'",
    nCid,
    v9,
    v11,
    v8,
    v7,
    v6,
    OpneCount,
    v5,
    v4);
  std::allocator<char>::allocator(&v18);
  std::string::string(&v17, (char *)szSQL, &v18);
  std::list<std::string>::push_back(sqls, &v17);
  std::string::~string(&v17);
  std::allocator<char>::~allocator(&v18);
  std::string::~string(&CurrencyString);
}


#####################################
bool __cdecl MemChrDepotData::LoadFromDB(
        MemChrDepotData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  __int64 v7; // rdx
  Answer::MySqlQuery *v8; // rax
  const char *StringValue; // rax
  const char *v10; // rax
  const char *v11; // rax
  __int64 slotData; // [rsp+30h] [rbp-90h]
  __int64 slotData_8; // [rsp+38h] [rbp-88h]
  __int64 slotData_16; // [rsp+40h] [rbp-80h]
  int64_t slotData_24; // [rsp+48h] [rbp-78h]
  std::string CurrencyString; // [rsp+50h] [rbp-70h] BYREF
  Answer::MySqlQuery resultTmp; // [rsp+60h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-40h] BYREF
  char v22; // [rsp+9Fh] [rbp-21h] BYREF
  std::string p_CurrencyString; // [rsp+A0h] [rbp-20h] BYREF
  int32_t slot; // [rsp+ACh] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_bag` WHERE `cid`=%lld AND `bag`=%d", nCid, 2);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    LODWORD(slotData) = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    HIDWORD(slotData) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "class", 0);
    LODWORD(slotData_8) = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    HIDWORD(slotData_8) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "bind", 0);
    slotData_16 = (unsigned int)Answer::MySqlQuery::getIntValue(&result, "endtime", 0);
    slotData_24 = Answer::MySqlQuery::getInt64Value(&result, "srcid", 0);
    if ( (unsigned int)slot >= 0x230 )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "wrong gamble slot data slot = %d, cid = %lld\n",
        slot,
        nCid);
    }
    else
    {
      v7 = slot;
      *(_QWORD *)&this->gambleDepot[v7].itemId = slotData;
      *(_QWORD *)&this->gambleDepot[v7].itemCount = slotData_8;
      *(_QWORD *)&this->gambleDepot[v7].endTime = slotData_16;
      this->gambleDepot[v7].srcId = slotData_24;
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_depot` WHERE `cid`=%lld", nCid);
  v8 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&resultTmp, v8);
  while ( !Answer::MySqlQuery::eof(&resultTmp) )
  {
    std::allocator<char>::allocator(&v22);
    StringValue = Answer::MySqlQuery::getStringValue(&resultTmp, "CurrencyString", byte_8CFE00);
    std::string::string(&CurrencyString, StringValue, &v22);
    std::allocator<char>::~allocator(&v22);
    this->OpneCount = Answer::MySqlQuery::getIntValue(&resultTmp, "open_count", 0);
    v10 = Answer::MySqlQuery::getStringValue(&resultTmp, "Password", byte_8CFE00);
    std::string::operator=(&this->Password, v10);
    v11 = Answer::MySqlQuery::getStringValue(&resultTmp, "second_password", byte_8CFE00);
    std::string::operator=(&this->SecondPassword, v11);
    std::string::string(&p_CurrencyString, &CurrencyString);
    MemChrDepotData::InitCurrency(this, &p_CurrencyString);
    std::string::~string(&p_CurrencyString);
    Answer::MySqlQuery::nextRow(&resultTmp);
    std::string::~string(&CurrencyString);
  }
  Answer::MySqlQuery::~MySqlQuery(&resultTmp);
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrDepotData::PackageData(MemChrDepotData *const this, Answer::NetPacket *packet)
{
  std::string CurrencyString; // [rsp+10h] [rbp-30h] BYREF
  uint32_t nCount; // [rsp+24h] [rbp-1Ch]
  int32_t gambleSlotCount; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  nCount = Answer::NetPacket::getWOffset(packet);
  gambleSlotCount = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  for ( i = 0; i <= 559; ++i )
  {
    if ( this->gambleDepot[i].itemCount > 0 )
    {
      Answer::NetPacket::writeInt32(packet, i);
      Answer::NetPacket::writeInt32(packet, this->gambleDepot[i].itemId);
      Answer::NetPacket::writeInt8(packet, this->gambleDepot[i].itemClass);
      Answer::NetPacket::writeInt32(packet, this->gambleDepot[i].itemCount);
      Answer::NetPacket::writeInt8(packet, this->gambleDepot[i].bind);
      Answer::NetPacket::writeInt32(packet, this->gambleDepot[i].endTime);
      Answer::NetPacket::writeInt64(packet, this->gambleDepot[i].srcId);
      ++gambleSlotCount;
    }
  }
  *(_DWORD *)&Answer::NetPacket::getBuffer(packet)[nCount] = gambleSlotCount;
  MemChrDepotData::GetCurrencyString((MemChrDepotData *const)&CurrencyString);
  Answer::NetPacket::writeUTF8(packet, &CurrencyString);
  Answer::NetPacket::writeInt32(packet, this->OpneCount);
  Answer::NetPacket::writeUTF8(packet, &this->Password);
  Answer::NetPacket::writeUTF8(packet, &this->SecondPassword);
  std::string::~string(&CurrencyString);
}


#####################################
void __cdecl MemChrDepotData::UnPackageData(MemChrDepotData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  __int64 m_refCount_high; // rdx
  __int64 slotData; // [rsp+20h] [rbp-80h]
  __int64 slotData_8; // [rsp+28h] [rbp-78h]
  __int64 slotData_16; // [rsp+30h] [rbp-70h]
  int64_t slotData_24; // [rsp+38h] [rbp-68h]
  std::string Currency; // [rsp+40h] [rbp-60h] BYREF
  std::string p_CurrencyString; // [rsp+50h] [rbp-50h] BYREF
  Answer::NetPacket v11; // [rsp+60h] [rbp-40h] BYREF

  *(&v11.m_size + 1) = Answer::NetPacket::readInt32(inPacket);
  LODWORD(v11.m_refCount) = 0;
  while ( SLODWORD(v11.m_refCount) < *((int *)&v11.m_size + 1) )
  {
    HIDWORD(v11.m_refCount) = Answer::NetPacket::readInt32(inPacket);
    LODWORD(slotData) = Answer::NetPacket::readInt32(inPacket);
    HIDWORD(slotData) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    LODWORD(slotData_8) = Answer::NetPacket::readInt32(inPacket);
    HIDWORD(slotData_8) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    slotData_16 = (unsigned int)Answer::NetPacket::readInt32(inPacket);
    slotData_24 = Answer::NetPacket::readInt64(inPacket);
    if ( HIDWORD(v11.m_refCount) >= 0x230 )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "wrong bag slotData data slotData = %d, cid = %lld\n",
        HIDWORD(v11.m_refCount),
        nCid);
    }
    else
    {
      m_refCount_high = SHIDWORD(v11.m_refCount);
      *(_QWORD *)&this->gambleDepot[m_refCount_high].itemId = slotData;
      *(_QWORD *)&this->gambleDepot[m_refCount_high].itemCount = slotData_8;
      *(_QWORD *)&this->gambleDepot[m_refCount_high].endTime = slotData_16;
      this->gambleDepot[m_refCount_high].srcId = slotData_24;
    }
    ++LODWORD(v11.m_refCount);
  }
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&Currency, (bool)inPacket);
  std::string::string(&p_CurrencyString, &Currency);
  MemChrDepotData::InitCurrency(this, &p_CurrencyString);
  std::string::~string(&p_CurrencyString);
  this->OpneCount = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8(&v11, (bool)inPacket);
  std::string::operator=(&this->Password, &v11);
  std::string::~string(&v11);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v11.m_wOffset, (bool)inPacket);
  std::string::operator=(&this->SecondPassword, &v11.m_wOffset);
  std::string::~string(&v11.m_wOffset);
  std::string::~string(&Currency);
}


#####################################
std::string __cdecl MemChrDepotData::GetCurrencyString(MemChrDepotData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  __int64 v3; // r12
  __int64 v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  _BYTE v8[16]; // [rsp+10h] [rbp-190h] BYREF
  __int64 v9; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v8, (unsigned int)v2);
  for ( i = 0; i <= 11; ++i )
  {
    if ( *(__int64 *)(v1 + 8 * (i + 2240LL) + 8) > 0 )
    {
      v3 = *(_QWORD *)(v1 + 8 * (i + 2240LL) + 8);
      v4 = std::operator<<<std::char_traits<char>>(&v9, "|");
      v5 = std::ostream::operator<<(v4, (unsigned int)i);
      v6 = std::operator<<<std::char_traits<char>>(v5, ":");
      std::ostream::operator<<(v6, v3);
    }
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v8);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v8);
  return (std::string)this;
}


#####################################
void __cdecl MemChrDepotData::InitCurrency(MemChrDepotData *const this, std::string *p_CurrencyString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int32_t v5; // ebx
  std::string *v6; // rax
  const char *v7; // rax
  StringVector tv; // [rsp+10h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+30h] [rbp-60h] BYREF
  std::string delims; // [rsp+50h] [rbp-40h] BYREF
  char v11; // [rsp+5Fh] [rbp-31h] BYREF
  std::string v12; // [rsp+60h] [rbp-30h] BYREF
  char v13; // [rsp+73h] [rbp-1Dh] BYREF
  int32_t isize; // [rsp+74h] [rbp-1Ch]
  int32_t i; // [rsp+78h] [rbp-18h]
  int32_t nType; // [rsp+7Ch] [rbp-14h]

  std::allocator<char>::allocator(&v11);
  std::string::string(&delims, "|", &v11);
  Answer::StringUtility::split(&vStr, p_CurrencyString, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v11);
  isize = std::vector<std::string>::size(&vStr);
  for ( i = 0; i < isize; ++i )
  {
    std::allocator<char>::allocator(&v13);
    std::string::string(&v12, ":", &v13);
    v2 = std::vector<std::string>::operator[](&vStr, i);
    Answer::StringUtility::split(&tv, v2, &v12, 0);
    std::string::~string(&v12);
    std::allocator<char>::~allocator(&v13);
    if ( std::vector<std::string>::size(&tv) == 2 )
    {
      v3 = std::vector<std::string>::operator[](&tv, 0);
      v4 = (const char *)std::string::c_str(v3);
      nType = atoi(v4);
      if ( (unsigned int)nType < 0xC )
      {
        v5 = nType;
        v6 = std::vector<std::string>::operator[](&tv, 1u);
        v7 = (const char *)std::string::c_str(v6);
        this->Currency[v5] = strtoll(v7, 0, 10);
      }
    }
    std::vector<std::string>::~vector(&tv);
  }
  std::vector<std::string>::~vector(&vStr);
}


