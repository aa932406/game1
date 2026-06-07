// Decompiled methods for class: EquipRongHeData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl EquipRongHeData::~EquipRongHeData(EquipRongHeData *const this)
{
  EquipRongHeData::~EquipRongHeData(this);
  operator delete(this);
}


#####################################
void __cdecl EquipRongHeData::CleanUp(EquipRongHeData *const this)
{
  std::string::operator=(&this->m_EquipRongHe, byte_8CFE00);
}


#####################################
void __cdecl EquipRongHeData::SaveToSqlString(
        EquipRongHeData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  const char *v5; // rax
  std::string __x; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v9[17]; // [rsp+2Fh] [rbp-11h] BYREF

  bzero(szSQL, 0x1000u);
  v4 = (const char *)std::string::c_str(&this->m_EquipRongHe);
  v5 = (const char *)std::string::c_str(&this->m_EquipRongHe);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_char_equip_rong_he` (`cid`,`equip_rong_he`) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE `equip_rong_he`='%s'",
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
bool __cdecl EquipRongHeData::LoadFromDB(
        EquipRongHeData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  Answer::MySqlQuery result; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_equip_rong_he` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    StringValue = Answer::MySqlQuery::getStringValue(&result, "equip_rong_he", byte_8CFE00);
    std::string::operator=(&this->m_EquipRongHe, StringValue);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl EquipRongHeData::PackageData(EquipRongHeData *const this, Answer::NetPacket *packet)
{
  if ( packet )
    Answer::NetPacket::writeUTF8(packet, &this->m_EquipRongHe);
}


#####################################
void __cdecl EquipRongHeData::UnPackageData(EquipRongHeData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  if ( inPacket )
  {
    Answer::NetPacket::readUTF8((Answer::NetPacket *const)v3, (bool)inPacket);
    std::string::operator=(&this->m_EquipRongHe, v3);
    std::string::~string(v3);
  }
}


