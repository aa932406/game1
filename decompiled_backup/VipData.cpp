// Decompiled methods for class: VipData
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl VipData::CleanUp(VipData *const this)
{
  this->m_Vip = 0;
  this->m_level = 0;
  this->m_ForeverFlg = 0;
  std::string::operator=(&this->m_VipEndTime, byte_8CFE00);
  std::string::operator=(&this->m_DropString, byte_8CFE00);
  this->m_Club = 0;
  this->m_ClubDropTimes = 0;
  this->m_BuyTimes = 0;
  this->m_nVip7Time = 0;
  this->m_nVip10Time = 0;
}


#####################################
void __cdecl VipData::SaveToSqlString(
        VipData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t m_BuyTimes; // r13d
  int32_t m_ClubDropTimes; // r14d
  int32_t m_nVip10Time; // r15d
  const char *v7; // r12
  const char *v8; // rax
  int32_t m_nVip7Time; // [rsp+98h] [rbp-98h]
  int32_t m_Club; // [rsp+9Ch] [rbp-94h]
  const char *v11; // [rsp+A0h] [rbp-90h]
  const char *v12; // [rsp+A8h] [rbp-88h]
  int32_t m_ForeverFlg; // [rsp+B0h] [rbp-80h]
  int32_t m_level; // [rsp+B4h] [rbp-7Ch]
  int32_t m_Vip; // [rsp+B8h] [rbp-78h]
  int32_t v16; // [rsp+BCh] [rbp-74h]
  int32_t v17; // [rsp+C0h] [rbp-70h]
  int32_t v18; // [rsp+C4h] [rbp-6Ch]
  int32_t v19; // [rsp+C8h] [rbp-68h]
  int32_t v20; // [rsp+CCh] [rbp-64h]
  std::string __x; // [rsp+F0h] [rbp-40h] BYREF
  _BYTE v24[49]; // [rsp+FFh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  m_BuyTimes = this->m_BuyTimes;
  m_ClubDropTimes = this->m_ClubDropTimes;
  m_nVip10Time = this->m_nVip10Time;
  m_nVip7Time = this->m_nVip7Time;
  m_Club = this->m_Club;
  v11 = (const char *)std::string::c_str(&this->m_DropString);
  v12 = (const char *)std::string::c_str(&this->m_VipEndTime);
  m_ForeverFlg = this->m_ForeverFlg;
  m_level = this->m_level;
  m_Vip = this->m_Vip;
  v16 = this->m_BuyTimes;
  v17 = this->m_ClubDropTimes;
  v18 = this->m_nVip10Time;
  v19 = this->m_nVip7Time;
  v20 = this->m_Club;
  v7 = (const char *)std::string::c_str(&this->m_DropString);
  v8 = (const char *)std::string::c_str(&this->m_VipEndTime);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_vip` (cid,vipCard,level,forever,vipEndTime,dropString,club,club_7_time,club_10_time,drop_time,b"
    "uy_time) VALUES (%lld,%d,%d,%d,'%s','%s',%d,%d,%d,%d,%d) on duplicate key update vipCard =%d,level=%d,forever=%d,vip"
    "EndTime='%s',dropString='%s',club =%d,club_7_time=%d,club_10_time=%d,drop_time=%d,buy_time=%d",
    nCid,
    this->m_Vip,
    this->m_level,
    this->m_ForeverFlg,
    v8,
    v7,
    v20,
    v19,
    v18,
    v17,
    v16,
    m_Vip,
    m_level,
    m_ForeverFlg,
    v12,
    v11,
    m_Club,
    m_nVip7Time,
    m_nVip10Time,
    m_ClubDropTimes,
    m_BuyTimes);
  std::allocator<char>::allocator(v24);
  std::string::string(&__x, (char *)szSQL, v24);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v24);
}


#####################################
bool __cdecl VipData::LoadFromDB(
        VipData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  bool v9; // bl
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_vip` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_Vip = Answer::MySqlQuery::getIntValue(&result, "vipCard", 0);
    this->m_level = Answer::MySqlQuery::getIntValue(&result, "level", 0);
    this->m_ForeverFlg = Answer::MySqlQuery::getIntValue(&result, "forever", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "vipEndTime", byte_8CFE00);
    std::string::operator=(&this->m_VipEndTime, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "dropString", byte_8CFE00);
    std::string::operator=(&this->m_DropString, v8);
    this->m_Club = Answer::MySqlQuery::getIntValue(&result, "club", 0);
    this->m_nVip7Time = Answer::MySqlQuery::getIntValue(&result, "club_7_time", 0);
    this->m_nVip10Time = Answer::MySqlQuery::getIntValue(&result, "club_10_time", 0);
    this->m_ClubDropTimes = Answer::MySqlQuery::getIntValue(&result, "drop_time", 0);
    this->m_BuyTimes = Answer::MySqlQuery::getIntValue(&result, "buy_time", 0);
    v9 = 1;
  }
  else
  {
    v9 = 0;
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return v9;
}


#####################################
void __cdecl VipData::PackageData(VipData *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_Vip);
    Answer::NetPacket::writeInt32(packet, this->m_level);
    Answer::NetPacket::writeInt32(packet, this->m_ForeverFlg);
    Answer::NetPacket::writeUTF8(packet, &this->m_VipEndTime);
    Answer::NetPacket::writeUTF8(packet, &this->m_DropString);
    Answer::NetPacket::writeInt32(packet, this->m_Club);
    Answer::NetPacket::writeInt32(packet, this->m_ClubDropTimes);
    Answer::NetPacket::writeInt32(packet, this->m_BuyTimes);
    Answer::NetPacket::writeInt32(packet, this->m_nVip7Time);
    Answer::NetPacket::writeInt32(packet, this->m_nVip10Time);
  }
}


#####################################
void __cdecl VipData::UnPackageData(VipData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[16]; // [rsp+20h] [rbp-30h] BYREF
  _BYTE v4[32]; // [rsp+30h] [rbp-20h] BYREF

  if ( inPacket )
  {
    this->m_Vip = Answer::NetPacket::readInt32(inPacket);
    this->m_level = Answer::NetPacket::readInt32(inPacket);
    this->m_ForeverFlg = Answer::NetPacket::readInt32(inPacket);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
    std::string::operator=(&this->m_VipEndTime, v3);
    std::string::~string(v3);
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v4, (bool)inPacket);
    std::string::operator=(&this->m_DropString, v4);
    std::string::~string(v4);
    this->m_Club = Answer::NetPacket::readInt32(inPacket);
    this->m_ClubDropTimes = Answer::NetPacket::readInt32(inPacket);
    this->m_BuyTimes = Answer::NetPacket::readInt32(inPacket);
    this->m_nVip7Time = Answer::NetPacket::readInt32(inPacket);
    this->m_nVip10Time = Answer::NetPacket::readInt32(inPacket);
  }
}


