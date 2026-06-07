// Decompiled methods for class: MemCharacterData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemCharacterData::~MemCharacterData(MemCharacterData *const this)
{
  MemCharacterData::~MemCharacterData(this);
  operator delete(this);
}


#####################################
void __cdecl MemCharacterData::CleanUp(MemCharacterData *const this)
{
  this->weapon = 0;
  this->cloth = 0;
  this->wing = 0;
  this->equipStar = 0;
  this->equipGem = 0;
  this->moneyDropRatio = 0;
  bzero(&this->data, 0xA8u);
}


#####################################
void __cdecl MemCharacterData::SaveToSqlString(
        MemCharacterData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+130h] [rbp-40h] BYREF
  _BYTE v6[49]; // [rsp+13Fh] [rbp-31h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "UPDATE `mem_character` SET `job`=%d, `level`=%d,`exp`=%lld, `battle`=%d, `top_battle`=%d, `mapid`=%d, `x`=%d, `y`=%d"
    ", `hp`=%d, `mp` = %d,`kun_li`=%d,`pk_mode`=%d,`pk_value`=%d,`pk_time`=%d, `kill_count`=%d,`last_task_id`=%d,`logout_"
    "count`=%d, `pay_click_count`=%d,`level_stay_time` = %d, `last_login_time`=%d, `last_logout_time`=%d, `weapon`=%d, `c"
    "loth`=%d, `wing`=%d, `equip_star`=%d, `equip_gem`=%d, `money_drop_ratio`=%d WHERE `cid`=%lld",
    this->data.job,
    this->data.level,
    this->data.exp,
    this->data.battle,
    this->data.top_battle,
    this->data.mapid,
    this->data.x,
    this->data.y,
    this->data.hp,
    this->data.mp,
    this->data.kun_li,
    this->data.pk_mode,
    this->data.pk_value,
    this->data.pk_time,
    this->data.kill_count,
    this->data.last_task_id,
    this->data.logout_count,
    this->data.pay_click_count,
    this->data.level_stay_time,
    this->data.last_login_time,
    this->data.last_logout_time,
    this->weapon,
    this->cloth,
    this->wing,
    this->equipStar,
    this->equipGem,
    this->moneyDropRatio,
    this->data.cid);
  std::allocator<char>::allocator(v6);
  std::string::string(&__x, (char *)szSQL, v6);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(v6);
}


#####################################
bool __cdecl MemCharacterData::LoadFromDB(
        MemCharacterData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  bool v7; // bl
  const char *StringValue; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "SELECT * FROM `mem_character` WHERE `uid`=%lld AND `sid`=%d AND `delete_time`=0",
    nUid,
    nSid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( Answer::MySqlQuery::getRowCount(&result) == 1 )
  {
    this->data.cid = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "name", byte_8CFE00);
    snprintf(this->data.name, 0x1Eu, StringValue);
    this->data.sex = Answer::MySqlQuery::getIntValue(&result, "sex", 0);
    this->data.job = Answer::MySqlQuery::getIntValue(&result, "job", 0);
    this->data.level = Answer::MySqlQuery::getIntValue(&result, "level", 0);
    this->data.exp = Answer::MySqlQuery::getInt64Value(&result, "exp", 0);
    this->data.battle = Answer::MySqlQuery::getIntValue(&result, "battle", 0);
    this->data.top_battle = Answer::MySqlQuery::getIntValue(&result, "top_battle", 0);
    this->data.mapid = Answer::MySqlQuery::getIntValue(&result, "mapid", 0);
    this->data.x = Answer::MySqlQuery::getIntValue(&result, "x", 0);
    this->data.y = Answer::MySqlQuery::getIntValue(&result, "y", 0);
    this->data.hp = Answer::MySqlQuery::getIntValue(&result, "hp", 0);
    this->data.mp = Answer::MySqlQuery::getIntValue(&result, "mp", 0);
    this->data.kun_li = Answer::MySqlQuery::getIntValue(&result, "kun_li", 0);
    this->data.head = Answer::MySqlQuery::getIntValue(&result, "head", 0);
    this->data.pk_mode = Answer::MySqlQuery::getIntValue(&result, "pk_mode", 0);
    this->data.pk_value = Answer::MySqlQuery::getIntValue(&result, "pk_value", 0);
    this->data.pk_time = Answer::MySqlQuery::getIntValue(&result, "pk_time", 0);
    this->data.kill_count = Answer::MySqlQuery::getIntValue(&result, "kill_count", 0);
    this->data.last_task_id = Answer::MySqlQuery::getIntValue(&result, "last_task_id", 0);
    this->data.logout_count = Answer::MySqlQuery::getIntValue(&result, "logout_count", 0);
    this->data.pay_click_count = Answer::MySqlQuery::getIntValue(&result, "pay_click_count", 0);
    this->data.level_stay_time = Answer::MySqlQuery::getIntValue(&result, "level_stay_time", 0);
    this->data.last_login_time = Answer::MySqlQuery::getIntValue(&result, "last_login_time", 0);
    this->data.last_logout_time = Answer::MySqlQuery::getIntValue(&result, "last_logout_time", 0);
    this->data.create_time = Answer::MySqlQuery::getIntValue(&result, "create_time", 0);
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
void __cdecl MemCharacterData::PackageData(MemCharacterData *const this, Answer::NetPacket *packet)
{
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  char v3; // [rsp+1Fh] [rbp-21h] BYREF
  std::string v4; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v5[17]; // [rsp+2Fh] [rbp-11h] BYREF

  Answer::NetPacket::writeInt64(packet, this->data.cid);
  std::allocator<char>::allocator(&v3);
  std::string::string(&val, this->data.name, &v3);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  std::allocator<char>::~allocator(&v3);
  std::allocator<char>::allocator(v5);
  std::string::string(&v4, this->data.familyName, v5);
  Answer::NetPacket::writeUTF8(packet, &v4);
  std::string::~string(&v4);
  std::allocator<char>::~allocator(v5);
  Answer::NetPacket::writeInt8(packet, this->data.sex);
  Answer::NetPacket::writeInt8(packet, this->data.job);
  Answer::NetPacket::writeInt32(packet, this->data.level);
  Answer::NetPacket::writeInt32(packet, this->data.battle);
  Answer::NetPacket::writeInt32(packet, this->data.top_battle);
  Answer::NetPacket::writeInt64(packet, this->data.exp);
  Answer::NetPacket::writeInt32(packet, this->data.mapid);
  Answer::NetPacket::writeInt32(packet, this->data.x);
  Answer::NetPacket::writeInt32(packet, this->data.y);
  Answer::NetPacket::writeInt32(packet, this->data.hp);
  Answer::NetPacket::writeInt32(packet, this->data.mp);
  Answer::NetPacket::writeInt32(packet, this->data.kun_li);
  Answer::NetPacket::writeInt32(packet, this->data.head);
  Answer::NetPacket::writeInt32(packet, this->data.pk_mode);
  Answer::NetPacket::writeInt32(packet, this->data.pk_value);
  Answer::NetPacket::writeInt32(packet, this->data.pk_time);
  Answer::NetPacket::writeInt32(packet, this->data.kill_count);
  Answer::NetPacket::writeInt32(packet, this->data.last_task_id);
  Answer::NetPacket::writeInt32(packet, this->data.logout_count);
  Answer::NetPacket::writeInt32(packet, this->data.pay_click_count);
  Answer::NetPacket::writeInt32(packet, this->data.level_stay_time);
  Answer::NetPacket::writeInt32(packet, this->data.last_login_time);
  Answer::NetPacket::writeInt32(packet, this->data.last_logout_time);
  Answer::NetPacket::writeInt32(packet, this->data.create_time);
  Answer::NetPacket::writeInt32(packet, this->weapon);
  Answer::NetPacket::writeInt32(packet, this->cloth);
  Answer::NetPacket::writeInt32(packet, this->wing);
  Answer::NetPacket::writeInt32(packet, this->equipStar);
  Answer::NetPacket::writeInt32(packet, this->equipGem);
  Answer::NetPacket::writeInt32(packet, this->moneyDropRatio);
}


#####################################
void __cdecl MemCharacterData::UnPackageData(MemCharacterData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  const char *v3; // rax
  const char *v4; // rax
  std::string v5[2]; // [rsp+20h] [rbp-30h] BYREF
  std::string v6; // [rsp+30h] [rbp-20h] BYREF

  this->data.cid = Answer::NetPacket::readInt64(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)v5, (bool)inPacket);
  v3 = (const char *)std::string::c_str(v5);
  snprintf(this->data.name, 0x1Eu, v3);
  std::string::~string(v5);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v6, (bool)inPacket);
  v4 = (const char *)std::string::c_str(&v6);
  snprintf(this->data.familyName, 0x1Eu, v4);
  std::string::~string(&v6);
  this->data.sex = Answer::NetPacket::readInt8(inPacket);
  this->data.job = Answer::NetPacket::readInt8(inPacket);
  this->data.level = Answer::NetPacket::readInt32(inPacket);
  this->data.battle = Answer::NetPacket::readInt32(inPacket);
  this->data.top_battle = Answer::NetPacket::readInt32(inPacket);
  this->data.exp = Answer::NetPacket::readInt64(inPacket);
  this->data.mapid = Answer::NetPacket::readInt32(inPacket);
  this->data.x = Answer::NetPacket::readInt32(inPacket);
  this->data.y = Answer::NetPacket::readInt32(inPacket);
  this->data.hp = Answer::NetPacket::readInt32(inPacket);
  this->data.mp = Answer::NetPacket::readInt32(inPacket);
  this->data.kun_li = Answer::NetPacket::readInt32(inPacket);
  this->data.head = Answer::NetPacket::readInt32(inPacket);
  this->data.pk_mode = Answer::NetPacket::readInt32(inPacket);
  this->data.pk_value = Answer::NetPacket::readInt32(inPacket);
  this->data.pk_time = Answer::NetPacket::readInt32(inPacket);
  this->data.kill_count = Answer::NetPacket::readInt32(inPacket);
  this->data.last_task_id = Answer::NetPacket::readInt32(inPacket);
  this->data.logout_count = Answer::NetPacket::readInt32(inPacket);
  this->data.pay_click_count = Answer::NetPacket::readInt32(inPacket);
  this->data.level_stay_time = Answer::NetPacket::readInt32(inPacket);
  this->data.last_login_time = Answer::NetPacket::readInt32(inPacket);
  this->data.last_logout_time = Answer::NetPacket::readInt32(inPacket);
  this->data.create_time = Answer::NetPacket::readInt32(inPacket);
  this->weapon = Answer::NetPacket::readInt32(inPacket);
  this->cloth = Answer::NetPacket::readInt32(inPacket);
  this->wing = Answer::NetPacket::readInt32(inPacket);
  this->equipStar = Answer::NetPacket::readInt32(inPacket);
  this->equipGem = Answer::NetPacket::readInt32(inPacket);
  this->moneyDropRatio = Answer::NetPacket::readInt32(inPacket);
}


