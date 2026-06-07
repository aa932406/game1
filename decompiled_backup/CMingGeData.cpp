// Decompiled methods for class: CMingGeData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CMingGeData::~CMingGeData(CMingGeData *const this)
{
  CMingGeData::~CMingGeData(this);
  operator delete(this);
}


#####################################
void __cdecl CMingGeData::CleanUp(CMingGeData *const this)
{
  this->m_MingGeExp = 0;
  this->m_MingChip = 0;
  bzero(this->m_MingGeBag, 0x320u);
  bzero(this->m_LieMingBag, 0xF0u);
  bzero(this->m_MingGeEquip, 0x40u);
  bzero(this->m_MingGeNpc, 0x14u);
}


#####################################
void __cdecl CMingGeData::SaveToSqlString(
        CMingGeData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  int32_t m_MingChip; // r13d
  int32_t m_MingGeExp; // r12d
  const char *v7; // rax
  std::string __x; // [rsp+40h] [rbp-A0h] BYREF
  char v11; // [rsp+4Fh] [rbp-91h] BYREF
  std::string v12; // [rsp+50h] [rbp-90h] BYREF
  char v13; // [rsp+5Fh] [rbp-81h] BYREF
  std::string v14; // [rsp+60h] [rbp-80h] BYREF
  char v15; // [rsp+6Fh] [rbp-71h] BYREF
  std::string v16; // [rsp+70h] [rbp-70h] BYREF
  char v17; // [rsp+7Fh] [rbp-61h] BYREF
  std::string v18; // [rsp+80h] [rbp-60h] BYREF
  std::string v19; // [rsp+90h] [rbp-50h] BYREF
  std::string v20; // [rsp+A0h] [rbp-40h] BYREF
  char v21; // [rsp+B3h] [rbp-2Dh] BYREF
  int slot; // [rsp+B4h] [rbp-2Ch]
  int slot_0; // [rsp+B8h] [rbp-28h]
  int slot_1; // [rsp+BCh] [rbp-24h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM mem_chr_ming_ge_bag WHERE Cid = %lld", nCid);
  std::allocator<char>::allocator(&v11);
  std::string::string(&__x, (char *)szSQL, &v11);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v11);
  for ( slot = 0; slot <= 99; ++slot )
  {
    bzero(szSQL, 0x1000u);
    if ( this->m_MingGeBag[slot].nId > 0 )
    {
      snprintf(
        (char *)szSQL,
        0xFFFu,
        "INSERT INTO `mem_chr_ming_ge_bag` (`cid`, `bag`, `slot`, `id`, `lock`) VALUES (%lld, %d, %d, %d, %d)",
        nCid,
        1,
        slot,
        this->m_MingGeBag[slot].nId,
        this->m_MingGeBag[slot].IsLock);
      std::allocator<char>::allocator(&v13);
      std::string::string(&v12, (char *)szSQL, &v13);
      std::list<std::string>::push_back(sqls, &v12);
      std::string::~string(&v12);
      std::allocator<char>::~allocator(&v13);
    }
  }
  for ( slot_0 = 0; slot_0 <= 29; ++slot_0 )
  {
    bzero(szSQL, 0x1000u);
    if ( this->m_LieMingBag[slot_0].nId > 0 )
    {
      snprintf(
        (char *)szSQL,
        0xFFFu,
        "INSERT INTO `mem_chr_ming_ge_bag` (`cid`, `bag`, `slot`, `id`, `lock`) VALUES (%lld, %d, %d, %d, %d)",
        nCid,
        2,
        slot_0,
        this->m_LieMingBag[slot_0].nId,
        this->m_LieMingBag[slot_0].IsLock);
      std::allocator<char>::allocator(&v15);
      std::string::string(&v14, (char *)szSQL, &v15);
      std::list<std::string>::push_back(sqls, &v14);
      std::string::~string(&v14);
      std::allocator<char>::~allocator(&v15);
    }
  }
  for ( slot_1 = 0; slot_1 <= 7; ++slot_1 )
  {
    bzero(szSQL, 0x1000u);
    if ( this->m_MingGeEquip[slot_1].nId > 0 )
    {
      snprintf(
        (char *)szSQL,
        0xFFFu,
        "INSERT INTO `mem_chr_ming_ge_bag` (`cid`, `bag`, `slot`, `id`, `lock`) VALUES (%lld, %d, %d, %d, %d)",
        nCid,
        3,
        slot_1,
        this->m_MingGeEquip[slot_1].nId,
        this->m_MingGeEquip[slot_1].IsLock);
      std::allocator<char>::allocator(&v17);
      std::string::string(&v16, (char *)szSQL, &v17);
      std::list<std::string>::push_back(sqls, &v16);
      std::string::~string(&v16);
      std::allocator<char>::~allocator(&v17);
    }
  }
  bzero(szSQL, 0x1000u);
  CMingGeData::GetNpcString((CMingGeData *const)&v18);
  v4 = (const char *)std::string::c_str(&v18);
  m_MingChip = this->m_MingChip;
  m_MingGeExp = this->m_MingGeExp;
  CMingGeData::GetNpcString((CMingGeData *const)&v19);
  v7 = (const char *)std::string::c_str(&v19);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_ming_ge_info` (`cid`,`ming_ge_exp`,`ming_ge_chip`,`ming_ge_npc`) VALUES (%lld,%d,%d,'%s')  ON D"
    "UPLICATE KEY UPDATE `ming_ge_exp`=%d,`ming_ge_chip`=%d,`ming_ge_npc`='%s'",
    nCid,
    this->m_MingGeExp,
    this->m_MingChip,
    v7,
    m_MingGeExp,
    m_MingChip,
    v4);
  std::string::~string(&v19);
  std::string::~string(&v18);
  std::allocator<char>::allocator(&v21);
  std::string::string(&v20, (char *)szSQL, &v21);
  std::list<std::string>::push_back(sqls, &v20);
  std::string::~string(&v20);
  std::allocator<char>::~allocator(&v21);
}


#####################################
bool __cdecl CMingGeData::LoadFromDB(
        CMingGeData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  Answer::MySqlQuery *v7; // rax
  const char *StringValue; // rax
  MingGe MingGeStu; // [rsp+30h] [rbp-80h]
  Answer::MySqlQuery result_1; // [rsp+40h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+60h] [rbp-50h] BYREF
  std::string p_NpcString; // [rsp+80h] [rbp-30h] BYREF
  char v16; // [rsp+97h] [rbp-19h] BYREF
  int32_t bag; // [rsp+98h] [rbp-18h]
  int32_t slot; // [rsp+9Ch] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_ming_ge_bag` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    bag = Answer::MySqlQuery::getIntValue(&result, "bag", 0);
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    MingGeStu.nId = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    MingGeStu.IsLock = Answer::MySqlQuery::getIntValue(&result, "lock", 0);
    if ( !IsInvalidSlot(bag, slot) )
    {
      switch ( bag )
      {
        case 1:
          this->m_MingGeBag[slot] = MingGeStu;
          break;
        case 2:
          this->m_LieMingBag[slot] = MingGeStu;
          break;
        case 3:
          this->m_MingGeEquip[slot] = MingGeStu;
          break;
      }
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_ming_ge_info` WHERE `Cid`=%lld", nCid);
  v7 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_1, v7);
  if ( !Answer::MySqlQuery::eof(&result_1) )
  {
    this->m_MingGeExp = Answer::MySqlQuery::getIntValue(&result_1, "ming_ge_exp", 0);
    this->m_MingChip = Answer::MySqlQuery::getIntValue(&result_1, "ming_ge_chip", 0);
    std::allocator<char>::allocator(&v16);
    StringValue = Answer::MySqlQuery::getStringValue(&result_1, "ming_ge_npc", byte_8CFE00);
    std::string::string(&p_NpcString, StringValue, &v16);
    CMingGeData::parseMingGeNpc(this, &p_NpcString);
    std::string::~string(&p_NpcString);
    std::allocator<char>::~allocator(&v16);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_1);
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
std::string __cdecl CMingGeData::GetNpcString(CMingGeData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 4; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 4 * (i + 280LL)));
    std::operator<<<std::char_traits<char>>(v5, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CMingGeData::parseMingGeNpc(CMingGeData *const this, std::string *p_NpcString)
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
  int32_t nId; // [rsp+7Ch] [rbp-14h]

  if ( !std::operator==<char>(p_NpcString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v11);
    std::string::string(&delims, "|", &v11);
    Answer::StringUtility::split(&vStr, p_NpcString, &delims, 0);
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
        nId = atoi(v4);
        if ( (unsigned int)nId <= 4 )
        {
          v5 = nId;
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          this->m_MingGeNpc[v5] = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
void __cdecl CMingGeData::PackageData(CMingGeData *const this, Answer::NetPacket *packet)
{
  uint32_t nCount; // [rsp+18h] [rbp-28h]
  int32_t slotCount; // [rsp+1Ch] [rbp-24h]
  int slot; // [rsp+20h] [rbp-20h]
  uint32_t nCount_0; // [rsp+24h] [rbp-1Ch]
  int32_t slotCount_0; // [rsp+28h] [rbp-18h]
  int slot_0; // [rsp+2Ch] [rbp-14h]
  uint32_t nCount_1; // [rsp+30h] [rbp-10h]
  int32_t slotCount_1; // [rsp+34h] [rbp-Ch]
  int slot_1; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  nCount = Answer::NetPacket::getWOffset(packet);
  slotCount = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  for ( slot = 0; slot <= 99; ++slot )
  {
    if ( this->m_MingGeBag[slot].nId > 0 )
    {
      Answer::NetPacket::writeInt32(packet, slot);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeBag[slot].nId);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeBag[slot].IsLock);
      ++slotCount;
    }
  }
  *(_DWORD *)&Answer::NetPacket::getBuffer(packet)[nCount] = slotCount;
  nCount_0 = Answer::NetPacket::getWOffset(packet);
  slotCount_0 = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  for ( slot_0 = 0; slot_0 <= 29; ++slot_0 )
  {
    if ( this->m_LieMingBag[slot_0].nId > 0 )
    {
      Answer::NetPacket::writeInt32(packet, slot_0);
      Answer::NetPacket::writeInt32(packet, this->m_LieMingBag[slot_0].nId);
      Answer::NetPacket::writeInt32(packet, this->m_LieMingBag[slot_0].IsLock);
      ++slotCount_0;
    }
  }
  *(_DWORD *)&Answer::NetPacket::getBuffer(packet)[nCount_0] = slotCount_0;
  nCount_1 = Answer::NetPacket::getWOffset(packet);
  slotCount_1 = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  for ( slot_1 = 0; slot_1 <= 7; ++slot_1 )
  {
    if ( this->m_MingGeEquip[slot_1].nId > 0 )
    {
      Answer::NetPacket::writeInt32(packet, slot_1);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeEquip[slot_1].nId);
      Answer::NetPacket::writeInt32(packet, this->m_MingGeEquip[slot_1].IsLock);
      ++slotCount_1;
    }
  }
  *(_DWORD *)&Answer::NetPacket::getBuffer(packet)[nCount_1] = slotCount_1;
  Answer::NetPacket::writeInt32(packet, this->m_MingGeExp);
  Answer::NetPacket::writeInt32(packet, this->m_MingChip);
  for ( i = 0; i <= 4; ++i )
    Answer::NetPacket::writeInt32(packet, this->m_MingGeNpc[i]);
}


#####################################
void __cdecl CMingGeData::UnPackageData(CMingGeData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  MingGe Stu_1; // [rsp+20h] [rbp-60h]
  MingGe Stu_0; // [rsp+30h] [rbp-50h]
  MingGe Stu; // [rsp+40h] [rbp-40h]
  int32_t slotCount; // [rsp+50h] [rbp-30h]
  int32_t slotCounta; // [rsp+50h] [rbp-30h]
  int32_t slotCountb; // [rsp+50h] [rbp-30h]
  int32_t i; // [rsp+54h] [rbp-2Ch]
  int32_t slot; // [rsp+58h] [rbp-28h]
  int32_t i_0; // [rsp+5Ch] [rbp-24h]
  int32_t slot_0; // [rsp+60h] [rbp-20h]
  int32_t i_1; // [rsp+64h] [rbp-1Ch]
  int32_t slot_1; // [rsp+68h] [rbp-18h]
  int32_t i_2; // [rsp+6Ch] [rbp-14h]

  slotCount = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < slotCount; ++i )
  {
    slot = Answer::NetPacket::readInt32(inPacket);
    Stu.nId = Answer::NetPacket::readInt32(inPacket);
    Stu.IsLock = Answer::NetPacket::readInt32(inPacket);
    this->m_MingGeBag[slot] = Stu;
  }
  slotCounta = Answer::NetPacket::readInt32(inPacket);
  for ( i_0 = 0; i_0 < slotCounta; ++i_0 )
  {
    slot_0 = Answer::NetPacket::readInt32(inPacket);
    Stu_0.nId = Answer::NetPacket::readInt32(inPacket);
    Stu_0.IsLock = Answer::NetPacket::readInt32(inPacket);
    this->m_LieMingBag[slot_0] = Stu_0;
  }
  slotCountb = Answer::NetPacket::readInt32(inPacket);
  for ( i_1 = 0; i_1 < slotCountb; ++i_1 )
  {
    slot_1 = Answer::NetPacket::readInt32(inPacket);
    Stu_1.nId = Answer::NetPacket::readInt32(inPacket);
    Stu_1.IsLock = Answer::NetPacket::readInt32(inPacket);
    this->m_MingGeEquip[slot_1] = Stu_1;
  }
  this->m_MingGeExp = Answer::NetPacket::readInt32(inPacket);
  this->m_MingChip = Answer::NetPacket::readInt32(inPacket);
  for ( i_2 = 0; i_2 <= 4; ++i_2 )
    this->m_MingGeNpc[i_2] = Answer::NetPacket::readInt32(inPacket);
}


