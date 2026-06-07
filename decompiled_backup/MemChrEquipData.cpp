// Decompiled methods for class: MemChrEquipData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl MemChrEquipData::~MemChrEquipData(MemChrEquipData *const this)
{
  MemChrEquipData::~MemChrEquipData(this);
  operator delete(this);
}


#####################################
void __cdecl MemChrEquipData::CleanUp(MemChrEquipData *const this)
{
  bzero(this->vEquip, 0xBA0u);
}


#####################################
void __cdecl MemChrEquipData::SaveToSqlString(
        MemChrEquipData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  std::string __x; // [rsp+90h] [rbp-40h] BYREF
  char v7; // [rsp+9Bh] [rbp-35h] BYREF
  int i; // [rsp+9Ch] [rbp-34h]

  for ( i = 0; i <= 92; ++i )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_bag` (`cid`, `bag`, `slot`, `id`, `class`, `count`, `bind`, `endtime`, `srcid`) VALUES (%lld,"
      " %d, %d, %d, %d, %d, %d, %d,%lld) on duplicate key update `id`=%d, `class`=%d, `count`=%d, `bind`=%d, `endtime`=%d, `srcid`=%lld",
      nCid,
      0,
      i,
      this->vEquip[i].itemId,
      this->vEquip[i].itemClass,
      this->vEquip[i].itemCount,
      this->vEquip[i].bind,
      this->vEquip[i].endTime,
      this->vEquip[i].srcId,
      this->vEquip[i].itemId,
      this->vEquip[i].itemClass,
      this->vEquip[i].itemCount,
      this->vEquip[i].bind,
      this->vEquip[i].endTime,
      this->vEquip[i].srcId);
    std::allocator<char>::allocator(&v7);
    std::string::string(&__x, (char *)szSQL, &v7);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v7);
  }
}


#####################################
bool __cdecl MemChrEquipData::LoadFromDB(
        MemChrEquipData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  __int64 v7; // rdx
  __int64 equip; // [rsp+30h] [rbp-50h]
  __int64 equip_8; // [rsp+38h] [rbp-48h]
  __int64 equip_16; // [rsp+40h] [rbp-40h]
  int64_t equip_24; // [rsp+48h] [rbp-38h]
  Answer::MySqlQuery result; // [rsp+50h] [rbp-30h] BYREF
  int32_t slot; // [rsp+6Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_bag` WHERE `cid`=%lld AND `bag`=%d", nCid, 0);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    LODWORD(equip) = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    HIDWORD(equip) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "class", 0);
    LODWORD(equip_8) = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    HIDWORD(equip_8) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "bind", 0);
    equip_16 = (unsigned int)Answer::MySqlQuery::getIntValue(&result, "endtime", 0);
    equip_24 = Answer::MySqlQuery::getInt64Value(&result, "srcid", 0);
    if ( (unsigned int)slot <= 0x5C )
    {
      v7 = slot;
      *(_QWORD *)&this->vEquip[v7].itemId = equip;
      *(_QWORD *)&this->vEquip[v7].itemCount = equip_8;
      *(_QWORD *)&this->vEquip[v7].endTime = equip_16;
      this->vEquip[v7].srcId = equip_24;
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl MemChrEquipData::PackageData(MemChrEquipData *const this, Answer::NetPacket *packet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 92; ++i )
  {
    Answer::NetPacket::writeInt32(packet, this->vEquip[i].itemId);
    Answer::NetPacket::writeInt8(packet, this->vEquip[i].itemClass);
    Answer::NetPacket::writeInt32(packet, this->vEquip[i].itemCount);
    Answer::NetPacket::writeInt8(packet, this->vEquip[i].bind);
    Answer::NetPacket::writeInt32(packet, this->vEquip[i].endTime);
    Answer::NetPacket::writeInt64(packet, this->vEquip[i].srcId);
  }
}


#####################################
void __cdecl MemChrEquipData::UnPackageData(MemChrEquipData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int64_t Int64; // rax
  __int64 v4; // rdx
  __int64 equip; // [rsp+20h] [rbp-30h]
  __int64 equip_8; // [rsp+28h] [rbp-28h]
  __int64 equip_16; // [rsp+30h] [rbp-20h]
  int32_t i; // [rsp+4Ch] [rbp-4h]

  for ( i = 0; i <= 92; ++i )
  {
    LODWORD(equip) = Answer::NetPacket::readInt32(inPacket);
    HIDWORD(equip) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    LODWORD(equip_8) = Answer::NetPacket::readInt32(inPacket);
    HIDWORD(equip_8) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
    equip_16 = (unsigned int)Answer::NetPacket::readInt32(inPacket);
    Int64 = Answer::NetPacket::readInt64(inPacket);
    v4 = i;
    *(_QWORD *)&this->vEquip[v4].itemId = equip;
    *(_QWORD *)&this->vEquip[v4].itemCount = equip_8;
    *(_QWORD *)&this->vEquip[v4].endTime = equip_16;
    this->vEquip[v4].srcId = Int64;
  }
}


