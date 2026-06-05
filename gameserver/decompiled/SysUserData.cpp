// Decompiled methods for class: SysUserData
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl SysUserData::~SysUserData(SysUserData *const this)
{
  SysUserData::~SysUserData(this);
  operator delete(this);
}


#####################################
void __cdecl SysUserData::CleanUp(SysUserData *const this)
{
  bzero(&this->data, 0x120u);
}


#####################################
void __cdecl SysUserData::SaveToSqlString(
        SysUserData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+70h] [rbp-40h] BYREF
  char v6; // [rsp+7Fh] [rbp-31h] BYREF
  std::string v7; // [rsp+80h] [rbp-30h] BYREF
  _BYTE v8[33]; // [rsp+8Fh] [rbp-21h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "UPDATE `sys_user` SET `gold`=%d,`sys_gold`=%d, `gold_cost_total` = %d,`cash`=%d, `last_login_time`=%d, `last_logout_"
    "time`=%d, `total_online_time`=%d, `total_offline_time`=%d,`total_login_count` = %d,`continue_login_count` = %d WHERE"
    " `uid`=%lld AND `sid`=%d",
    this->data.gold,
    this->data.sys_gold,
    this->data.gold_cost_total,
    this->data.cash,
    this->data.last_login_time,
    this->data.last_logout_time,
    this->data.total_online_time,
    this->data.total_offline_time,
    this->data.total_login_count,
    this->data.continue_login_count,
    this->data.uid,
    this->data.sid);
  std::allocator<char>::allocator(&v6);
  std::string::string(&__x, (char *)szSQL, &v6);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v6);
  if ( this->data.map_enter_time )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "UPDATE `sys_user` SET `map_enter_time`=%d WHERE `uid`=%lld AND `sid`=%d",
      this->data.map_enter_time,
      this->data.uid,
      this->data.sid);
    std::allocator<char>::allocator(v8);
    std::string::string(&v7, (char *)szSQL, v8);
    std::list<std::string>::push_back(sqls, &v7);
    std::string::~string(&v7);
    std::allocator<char>::~allocator(v8);
  }
}


#####################################
bool __cdecl SysUserData::LoadFromDB(
        SysUserData *const this,
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
  const char *v10; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `sys_user` WHERE `uid`=%lld AND `sid`=%d", nUid, nSid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->data.sys_gold = Answer::MySqlQuery::getIntValue(&result, "sys_gold", 0);
    this->data.uid = nUid;
    this->data.sid = nSid;
    this->data.gold_pay = Answer::MySqlQuery::getIntValue(&result, "gold_pay", 0);
    this->data.gold = Answer::MySqlQuery::getIntValue(&result, "gold", 0);
    this->data.sys_gold = Answer::MySqlQuery::getIntValue(&result, "sys_gold", 0);
    this->data.gold_pay_total = Answer::MySqlQuery::getIntValue(&result, "gold_pay_total", 0);
    this->data.prepay_gold = Answer::MySqlQuery::getIntValue(&result, "prepay_gold", 0);
    this->data.gold_cost_total = Answer::MySqlQuery::getIntValue(&result, "gold_cost_total", 0);
    this->data.cash = Answer::MySqlQuery::getIntValue(&result, "cash", 0);
    this->data.map_enter_time = Answer::MySqlQuery::getIntValue(&result, "map_enter_time", 0);
    this->data.last_login_time = Answer::MySqlQuery::getIntValue(&result, "last_login_time", 0);
    this->data.adult = Answer::MySqlQuery::getIntValue(&result, "adult", 0);
    this->data.gm_level = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    this->data.last_logout_time = Answer::MySqlQuery::getIntValue(&result, "last_logout_time", 0);
    this->data.continue_login_count = Answer::MySqlQuery::getIntValue(&result, "continue_login_count", 0);
    this->data.total_online_time = Answer::MySqlQuery::getIntValue(&result, "total_online_time", 0);
    this->data.total_offline_time = Answer::MySqlQuery::getIntValue(&result, "total_offline_time", 0);
    this->data.fuli = Answer::MySqlQuery::getIntValue(&result, "fuli", 0);
    this->data.robot = Answer::MySqlQuery::getIntValue(&result, "robot", 0);
    this->data.mini_client = Answer::MySqlQuery::getIntValue(&result, "mini_client", 0);
    this->data.net_bar = Answer::MySqlQuery::getIntValue(&result, "net_bar", 0);
    this->data.JianKong = Answer::MySqlQuery::getIntValue(&result, "jiankong", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "passport", byte_8CFE00);
    snprintf(this->data.passport, 0x80u, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "last_login_ip", byte_8CFE00);
    snprintf(this->data.IP, 0x10u, v8);
    v9 = Answer::MySqlQuery::getStringValue(&result, "platform", byte_8CFE00);
    snprintf(this->data.platform, 0x20u, v9);
    v10 = Answer::MySqlQuery::getStringValue(&result, "from_way", byte_8CFE00);
    snprintf(this->data.from_way, 0x20u, v10);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
bool __cdecl SysUserData::LoadSpecialInfo(
        SysUserData *const this,
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
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `sys_user` WHERE `uid`=%lld AND `sid`=%d", nUid, nSid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->data.mini_client = Answer::MySqlQuery::getIntValue(&result, "mini_client", 0);
    this->data.net_bar = Answer::MySqlQuery::getIntValue(&result, "net_bar", 0);
    this->data.robot = Answer::MySqlQuery::getIntValue(&result, "robot", 0);
    this->data.fuli = Answer::MySqlQuery::getIntValue(&result, "fuli", 0);
    this->data.adult = Answer::MySqlQuery::getIntValue(&result, "adult", 0);
    this->data.gm_level = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    this->data.gold_pay = Answer::MySqlQuery::getIntValue(&result, "gold_pay", 0);
    this->data.gold = Answer::MySqlQuery::getIntValue(&result, "gold", 0);
    this->data.sys_gold = Answer::MySqlQuery::getIntValue(&result, "sys_gold", 0);
    this->data.gold_pay_total = Answer::MySqlQuery::getIntValue(&result, "gold_pay_total", 0);
    this->data.prepay_gold = Answer::MySqlQuery::getIntValue(&result, "prepay_gold", 0);
    this->data.gold_cost_total = Answer::MySqlQuery::getIntValue(&result, "gold_cost_total", 0);
    this->data.JianKong = Answer::MySqlQuery::getIntValue(&result, "jiankong", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "passport", byte_8CFE00);
    snprintf(this->data.passport, 0x80u, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "platform", byte_8CFE00);
    snprintf(this->data.platform, 0x20u, v8);
    v9 = Answer::MySqlQuery::getStringValue(&result, "from_way", byte_8CFE00);
    snprintf(this->data.from_way, 0x20u, v9);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl SysUserData::PackageData(SysUserData *const this, Answer::NetPacket *packet)
{
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  char v3; // [rsp+1Fh] [rbp-41h] BYREF
  std::string v4; // [rsp+20h] [rbp-40h] BYREF
  char v5; // [rsp+2Fh] [rbp-31h] BYREF
  std::string v6; // [rsp+30h] [rbp-30h] BYREF
  char v7; // [rsp+3Fh] [rbp-21h] BYREF
  std::string v8; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v9[17]; // [rsp+4Fh] [rbp-11h] BYREF

  Answer::NetPacket::writeInt64(packet, this->data.uid);
  Answer::NetPacket::writeInt32(packet, this->data.sid);
  Answer::NetPacket::writeInt32(packet, this->data.gold_pay);
  Answer::NetPacket::writeInt32(packet, this->data.gold);
  Answer::NetPacket::writeInt32(packet, this->data.sys_gold);
  Answer::NetPacket::writeInt32(packet, this->data.gold_pay_total);
  Answer::NetPacket::writeInt32(packet, this->data.prepay_gold);
  Answer::NetPacket::writeInt32(packet, this->data.gold_cost_total);
  Answer::NetPacket::writeInt32(packet, this->data.cash);
  Answer::NetPacket::writeInt32(packet, this->data.map_enter_time);
  Answer::NetPacket::writeInt32(packet, this->data.last_login_time);
  Answer::NetPacket::writeInt8(packet, this->data.adult);
  Answer::NetPacket::writeInt8(packet, this->data.gm_level);
  Answer::NetPacket::writeInt32(packet, this->data.last_logout_time);
  Answer::NetPacket::writeInt32(packet, this->data.continue_login_count);
  Answer::NetPacket::writeInt32(packet, this->data.total_online_time);
  Answer::NetPacket::writeInt32(packet, this->data.total_offline_time);
  std::allocator<char>::allocator(&v3);
  std::string::string(&val, this->data.IP, &v3);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(&v3);
  std::allocator<char>::allocator(&v5);
  std::string::string(&v4, this->data.passport, &v5);
  Answer::NetPacket::writeUTF8(packet, &v4);
  std::string::~string(&v4);
  std::allocator<char>::~allocator(&v5);
  std::allocator<char>::allocator(&v7);
  std::string::string(&v6, this->data.platform, &v7);
  Answer::NetPacket::writeUTF8(packet, &v6);
  std::string::~string(&v6);
  std::allocator<char>::~allocator(&v7);
  Answer::NetPacket::writeInt8(packet, this->data.fuli);
  Answer::NetPacket::writeInt8(packet, this->data.robot);
  Answer::NetPacket::writeInt8(packet, this->data.mini_client);
  Answer::NetPacket::writeInt8(packet, this->data.net_bar);
  std::allocator<char>::allocator(v9);
  std::string::string(&v8, this->data.from_way, v9);
  Answer::NetPacket::writeUTF8(packet, &v8);
  std::string::~string(&v8);
  std::allocator<char>::~allocator(v9);
  Answer::NetPacket::writeInt8(packet, this->data.JianKong);
}


#####################################
void __cdecl SysUserData::UnPackageData(SysUserData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  const char *v3; // rax
  const char *v4; // rax
  const char *v5; // rax
  const char *v6; // rax
  Answer::NetPacket v7; // [rsp+20h] [rbp-50h] BYREF

  this->data.uid = Answer::NetPacket::readInt64(inPacket);
  this->data.sid = Answer::NetPacket::readInt32(inPacket);
  this->data.gold_pay = Answer::NetPacket::readInt32(inPacket);
  this->data.gold = Answer::NetPacket::readInt32(inPacket);
  this->data.sys_gold = Answer::NetPacket::readInt32(inPacket);
  this->data.gold_pay_total = Answer::NetPacket::readInt32(inPacket);
  this->data.prepay_gold = Answer::NetPacket::readInt32(inPacket);
  this->data.gold_cost_total = Answer::NetPacket::readInt32(inPacket);
  this->data.cash = Answer::NetPacket::readInt32(inPacket);
  this->data.map_enter_time = Answer::NetPacket::readInt32(inPacket);
  this->data.last_login_time = Answer::NetPacket::readInt32(inPacket);
  this->data.adult = Answer::NetPacket::readInt8(inPacket);
  this->data.gm_level = Answer::NetPacket::readInt8(inPacket);
  this->data.last_logout_time = Answer::NetPacket::readInt32(inPacket);
  this->data.continue_login_count = Answer::NetPacket::readInt32(inPacket);
  this->data.total_online_time = Answer::NetPacket::readInt32(inPacket);
  this->data.total_offline_time = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8(&v7, (bool)inPacket);
  v3 = (const char *)std::string::c_str((std::string *)&v7);
  snprintf(this->data.IP, 0x10u, v3);
  std::string::~string(&v7);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v7.m_wOffset, (bool)inPacket);
  v4 = (const char *)std::string::c_str((std::string *)&v7.m_wOffset);
  snprintf(this->data.passport, 0x80u, v4);
  std::string::~string(&v7.m_wOffset);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v7.m_size, (bool)inPacket);
  v5 = (const char *)std::string::c_str((std::string *)&v7.m_size);
  snprintf(this->data.platform, 0x20u, v5);
  std::string::~string(&v7.m_size);
  this->data.fuli = Answer::NetPacket::readInt8(inPacket);
  this->data.robot = Answer::NetPacket::readInt8(inPacket);
  this->data.mini_client = Answer::NetPacket::readInt8(inPacket);
  this->data.net_bar = Answer::NetPacket::readInt8(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v7.m_pool, (bool)inPacket);
  v6 = (const char *)std::string::c_str((std::string *)&v7.m_pool);
  snprintf(this->data.from_way, 0x20u, v6);
  std::string::~string(&v7.m_pool);
  this->data.JianKong = Answer::NetPacket::readInt8(inPacket);
}


