// Decompiled methods for class: SysUserPreventWallowData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl SysUserPreventWallowData::~SysUserPreventWallowData(SysUserPreventWallowData *const this)
{
  SysUserPreventWallowData::~SysUserPreventWallowData(this);
  operator delete(this);
}


#####################################
void __cdecl SysUserPreventWallowData::CleanUp(SysUserPreventWallowData *const this)
{
  bzero(&this->data, 0x48u);
}


#####################################
void __cdecl SysUserPreventWallowData::SaveToSqlString(
        SysUserPreventWallowData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+30h] [rbp-20h] BYREF
  _BYTE v6[17]; // [rsp+3Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "UPDATE `sys_user_prevent_wallow` SET `name`='%s',`identitycard`= '%s', `isGrowUp` = %d WHERE `uid`=%lld AND `sid`=%d",
    this->data.name,
    this->data.identitycard,
    this->data.isGrowUp,
    this->data.uid,
    this->data.sid);
  std::allocator<char>::allocator(v6);
  std::string::string(&__x, (char *)szSQL, v6);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v6);
}


#####################################
bool __cdecl SysUserPreventWallowData::LoadFromDB(
        SysUserPreventWallowData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  Answer::MySqlQuery result; // [rsp+40h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `sys_user_prevent_wallow` WHERE `uid`= %lld AND `sid`= %d", nUid, nSid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( Answer::MySqlQuery::eof(&result) )
  {
    this->data.sid = nSid;
    this->data.uid = nUid;
    this->data.isGrowUp = 0;
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `sys_user_prevent_wallow`(`uid`, `sid`,`name`,`identitycard`,`isGrowUp`) VALUES (%lld, %d,'%s','%s', %d)",
      this->data.uid,
      this->data.sid,
      byte_8CFE00,
      byte_8CFE00,
      this->data.isGrowUp);
    Answer::MySqlDBGuard::excute(db, (const char *)szSQL);
  }
  else
  {
    this->data.sid = Answer::MySqlQuery::getIntValue(&result, "sid", 0);
    this->data.uid = Answer::MySqlQuery::getInt64Value(&result, "uid", 0);
    this->data.isGrowUp = Answer::MySqlQuery::getIntValue(&result, "isGrowUp", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", byte_8CFE00);
    snprintf(this->data.name, 0x1Eu, StringValue);
    v8 = Answer::MySqlQuery::getStringValue(&result, "identitycard", byte_8CFE00);
    snprintf(this->data.identitycard, 0x12u, v8);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl SysUserPreventWallowData::PackageData(SysUserPreventWallowData *const this, Answer::NetPacket *packet)
{
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  char v3; // [rsp+1Fh] [rbp-21h] BYREF
  std::string v4; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+2Fh] [rbp-11h] BYREF

  Answer::NetPacket::writeInt64(packet, this->data.uid);
  Answer::NetPacket::writeInt32(packet, this->data.sid);
  std::allocator<char>::allocator(&v3);
  std::string::string(&val, this->data.name, &v3);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(&v3);
  std::allocator<char>::allocator(v5);
  std::string::string(&v4, this->data.identitycard, v5);
  Answer::NetPacket::writeUTF8(packet, &v4);
  std::string::~string(&v4);
  std::allocator<char>::~allocator(v5);
  Answer::NetPacket::writeInt32(packet, this->data.isGrowUp);
}


#####################################
void __cdecl SysUserPreventWallowData::UnPackageData(
        SysUserPreventWallowData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  const char *v3; // rax
  const char *v4; // rax
  std::string v5[2]; // [rsp+20h] [rbp-30h] BYREF
  std::string v6; // [rsp+30h] [rbp-20h] BYREF

  this->data.uid = Answer::NetPacket::readInt64(inPacket);
  this->data.sid = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v5, (bool)inPacket);
  v3 = (const char *)std::string::c_str(v5);
  snprintf(this->data.name, 0x1Eu, v3);
  std::string::~string(v5);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v6, (bool)inPacket);
  v4 = (const char *)std::string::c_str(&v6);
  snprintf(this->data.identitycard, 0x12u, v4);
  std::string::~string(&v6);
  this->data.isGrowUp = Answer::NetPacket::readInt32(inPacket);
}


