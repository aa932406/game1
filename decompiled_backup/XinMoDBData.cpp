// Decompiled methods for class: XinMoDBData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl XinMoDBData::~XinMoDBData(XinMoDBData *const this)
{
  XinMoDBData::~XinMoDBData(this);
  operator delete(this);
}


#####################################
void __cdecl XinMoDBData::CleanUp(XinMoDBData *const this)
{
  this->m_Exp = 0;
  this->m_XinMoLevel = 0;
  this->m_XinMoActiveLevel = 0;
  std::map<int,int>::clear(&this->m_QiQingLevel);
  this->m_QiQingInfo = 0;
  bzero(this->m_ItemList, 0x700u);
}


#####################################
void __cdecl XinMoDBData::SaveToSqlString(
        XinMoDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  int32_t m_QiQingInfo; // r15d
  int32_t m_XinMoActiveLevel; // r14d
  int32_t m_XinMoLevel; // r13d
  int32_t m_Exp; // r12d
  const char *v9; // rax
  std::string __x; // [rsp+90h] [rbp-70h] BYREF
  char v13; // [rsp+9Fh] [rbp-61h] BYREF
  std::string v14; // [rsp+A0h] [rbp-60h] BYREF
  std::string v15; // [rsp+B0h] [rbp-50h] BYREF
  std::string v16; // [rsp+C0h] [rbp-40h] BYREF
  char v17; // [rsp+CBh] [rbp-35h] BYREF
  int32_t i; // [rsp+CCh] [rbp-34h]

  for ( i = 0; i <= 55; ++i )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_bag` (`cid`, `bag`, `slot`, `id`, `class`, `count`, `bind`, `endtime`, `srcid`) VALUES (%lld,"
      " %d, %d, %d, %d, %d, %d, %d,%lld) on duplicate key update `id`=%d, `class`=%d, `count`=%d, `bind`=%d, `endtime`=%d, `srcid`=%lld",
      nCid,
      4,
      i,
      this->m_ItemList[i].itemId,
      this->m_ItemList[i].itemClass,
      this->m_ItemList[i].itemCount,
      this->m_ItemList[i].bind,
      this->m_ItemList[i].endTime,
      this->m_ItemList[i].srcId,
      this->m_ItemList[i].itemId,
      this->m_ItemList[i].itemClass,
      this->m_ItemList[i].itemCount,
      this->m_ItemList[i].bind,
      this->m_ItemList[i].endTime,
      this->m_ItemList[i].srcId);
    std::allocator<char>::allocator(&v13);
    std::string::string(&__x, (char *)szSQL, &v13);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v13);
  }
  bzero(szSQL, 0x1000u);
  XinMoDBData::GetQiQingLevelString((XinMoDBData *const)&v14);
  v4 = (const char *)std::string::c_str(&v14);
  m_QiQingInfo = this->m_QiQingInfo;
  m_XinMoActiveLevel = this->m_XinMoActiveLevel;
  m_XinMoLevel = this->m_XinMoLevel;
  m_Exp = this->m_Exp;
  XinMoDBData::GetQiQingLevelString((XinMoDBData *const)&v15);
  v9 = (const char *)std::string::c_str(&v15);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_xin_mo` (`cid`,`exp`,`xin_mo_level`,`xin_mo_act_level`,`xin_qing_info`,`qi_qing_level`) VALUES (%ll"
    "d,%d,%d,%d,%d,'%s') ON DUPLICATE KEY UPDATE `exp`=%d,`xin_mo_level`=%d,`xin_mo_act_level`=%d,`xin_qing_info`=%d,`qi_"
    "qing_level`='%s'",
    nCid,
    this->m_Exp,
    this->m_XinMoLevel,
    this->m_XinMoActiveLevel,
    this->m_QiQingInfo,
    v9,
    m_Exp,
    m_XinMoLevel,
    m_XinMoActiveLevel,
    m_QiQingInfo,
    v4);
  std::string::~string(&v15);
  std::string::~string(&v14);
  std::allocator<char>::allocator(&v17);
  std::string::string(&v16, (char *)szSQL, &v17);
  std::list<std::string>::push_back(sqls, &v16);
  std::string::~string(&v16);
  std::allocator<char>::~allocator(&v17);
}


#####################################
bool __cdecl XinMoDBData::LoadFromDB(
        XinMoDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  MemChrBag *v7; // rax
  Answer::MySqlQuery *v8; // rax
  const char *StringValue; // rax
  __int64 slotData; // [rsp+30h] [rbp-90h]
  __int64 slotData_8; // [rsp+38h] [rbp-88h]
  __int64 slotData_16; // [rsp+40h] [rbp-80h]
  int64_t slotData_24; // [rsp+48h] [rbp-78h]
  std::string QiQingLevelString; // [rsp+50h] [rbp-70h] BYREF
  Answer::MySqlQuery result_0; // [rsp+60h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+80h] [rbp-40h] BYREF
  char v20; // [rsp+9Fh] [rbp-21h] BYREF
  std::string p_QiQingLevelString; // [rsp+A0h] [rbp-20h] BYREF
  int32_t gambleSlotCount; // [rsp+A8h] [rbp-18h]
  int32_t slot; // [rsp+ACh] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_bag` WHERE `cid`=%lld AND `bag`=%d", nCid, 4);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  gambleSlotCount = 0;
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    LODWORD(slotData) = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    HIDWORD(slotData) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "class", 0);
    LODWORD(slotData_8) = Answer::MySqlQuery::getIntValue(&result, "count", 0);
    HIDWORD(slotData_8) = (unsigned __int8)Answer::MySqlQuery::getIntValue(&result, "bind", 0);
    slotData_16 = (unsigned int)Answer::MySqlQuery::getIntValue(&result, "endtime", 0);
    slotData_24 = Answer::MySqlQuery::getInt64Value(&result, "srcid", 0);
    if ( (unsigned int)slot >= 0x38 )
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "wrong gamble slot data slot = %d, cid = %lld\n",
        slot,
        nCid);
    }
    else
    {
      v7 = &this->m_ItemList[slot];
      *(_QWORD *)&v7->itemId = slotData;
      *(_QWORD *)&v7->itemCount = slotData_8;
      *(_QWORD *)&v7->endTime = slotData_16;
      v7->srcId = slotData_24;
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_xin_mo` WHERE `cid`=%lld", nCid);
  v8 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_0, v8);
  while ( !Answer::MySqlQuery::eof(&result_0) )
  {
    this->m_Exp = Answer::MySqlQuery::getIntValue(&result_0, "exp", 0);
    this->m_XinMoLevel = Answer::MySqlQuery::getIntValue(&result_0, "xin_mo_level", 0);
    this->m_XinMoActiveLevel = Answer::MySqlQuery::getIntValue(&result_0, "xin_mo_act_level", 0);
    this->m_QiQingInfo = Answer::MySqlQuery::getIntValue(&result_0, "xin_qing_info", 0);
    std::allocator<char>::allocator(&v20);
    StringValue = Answer::MySqlQuery::getStringValue(&result_0, "qi_qing_level", byte_8CFE00);
    std::string::string(&QiQingLevelString, StringValue, &v20);
    std::allocator<char>::~allocator(&v20);
    std::string::string(&p_QiQingLevelString, &QiQingLevelString);
    XinMoDBData::ParesQiQingLevelString(this, &p_QiQingLevelString);
    std::string::~string(&p_QiQingLevelString);
    Answer::MySqlQuery::nextRow(&result_0);
    std::string::~string(&QiQingLevelString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_0);
  return 1;
}


#####################################
void __cdecl XinMoDBData::PackageData(XinMoDBData *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-14h]
  int32_t OldOffet; // [rsp+30h] [rbp-10h]
  int32_t NewOffet; // [rsp+34h] [rbp-Ch]
  int32_t nSize; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_Exp);
    Answer::NetPacket::writeInt32(packet, this->m_XinMoLevel);
    Answer::NetPacket::writeInt32(packet, this->m_XinMoActiveLevel);
    Count = 0;
    OldOffet = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::writeInt32(packet, 0);
    for ( i = 0; i <= 55; ++i )
    {
      if ( this->m_ItemList[i].itemId > 0 && this->m_ItemList[i].itemCount > 0 )
      {
        ++Count;
        Answer::NetPacket::writeInt32(packet, i);
        Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].itemId);
        Answer::NetPacket::writeInt8(packet, this->m_ItemList[i].itemClass);
        Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].itemCount);
        Answer::NetPacket::writeInt8(packet, this->m_ItemList[i].bind);
        Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].endTime);
        Answer::NetPacket::writeInt64(packet, this->m_ItemList[i].srcId);
      }
    }
    NewOffet = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setWOffset(packet, OldOffet);
    Answer::NetPacket::writeInt32(packet, Count);
    Answer::NetPacket::setWOffset(packet, NewOffet);
    nSize = std::map<int,int>::size(&this->m_QiQingLevel);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,int>::begin(&this->m_QiQingLevel)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_QiQingLevel)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
    Answer::NetPacket::writeInt32(packet, this->m_QiQingInfo);
  }
}


#####################################
void __cdecl XinMoDBData::UnPackageData(XinMoDBData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  MemChrBag *v3; // rax
  int *v4; // rax
  __int64 Item; // [rsp+20h] [rbp-40h]
  __int64 Item_8; // [rsp+28h] [rbp-38h]
  __int64 Item_16; // [rsp+30h] [rbp-30h]
  int64_t Item_24; // [rsp+38h] [rbp-28h]
  int32_t nType; // [rsp+44h] [rbp-1Ch] BYREF
  int32_t Count; // [rsp+48h] [rbp-18h]
  int32_t nSize; // [rsp+4Ch] [rbp-14h]
  int32_t i; // [rsp+50h] [rbp-10h]
  int32_t Index; // [rsp+54h] [rbp-Ch]
  int32_t j; // [rsp+58h] [rbp-8h]
  int32_t nLevel; // [rsp+5Ch] [rbp-4h]

  if ( inPacket )
  {
    this->m_Exp = Answer::NetPacket::readInt32(inPacket);
    this->m_XinMoLevel = Answer::NetPacket::readInt32(inPacket);
    this->m_XinMoActiveLevel = Answer::NetPacket::readInt32(inPacket);
    Count = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < Count; ++i )
    {
      Index = Answer::NetPacket::readInt32(inPacket);
      LODWORD(Item) = Answer::NetPacket::readInt32(inPacket);
      HIDWORD(Item) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
      LODWORD(Item_8) = Answer::NetPacket::readInt32(inPacket);
      HIDWORD(Item_8) = (unsigned __int8)Answer::NetPacket::readInt8(inPacket);
      Item_16 = (unsigned int)Answer::NetPacket::readInt32(inPacket);
      Item_24 = Answer::NetPacket::readInt64(inPacket);
      if ( (unsigned int)Index < 0x38 )
      {
        v3 = &this->m_ItemList[Index];
        *(_QWORD *)&v3->itemId = Item;
        *(_QWORD *)&v3->itemCount = Item_8;
        *(_QWORD *)&v3->endTime = Item_16;
        v3->srcId = Item_24;
      }
    }
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( j = 0; j < nSize; ++j )
    {
      nType = Answer::NetPacket::readInt32(inPacket);
      nLevel = Answer::NetPacket::readInt32(inPacket);
      v4 = std::map<int,int>::operator[](&this->m_QiQingLevel, &nType);
      *v4 = nLevel;
    }
    this->m_QiQingInfo = Answer::NetPacket::readInt32(inPacket);
  }
}


#####################################
std::string __cdecl XinMoDBData::GetQiQingLevelString(XinMoDBData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 24))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 24))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl XinMoDBData::ParesQiQingLevelString(XinMoDBData *const this, std::string *p_QiQingLevelString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nType; // [rsp+1Ch] [rbp-84h] BYREF
  StringVector tv; // [rsp+20h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  std::string v13; // [rsp+70h] [rbp-30h] BYREF
  char v14; // [rsp+87h] [rbp-19h] BYREF
  int32_t isize; // [rsp+88h] [rbp-18h]
  int32_t i; // [rsp+8Ch] [rbp-14h]

  if ( !std::operator==<char>(p_QiQingLevelString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, p_QiQingLevelString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, ":", &v14);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&tv) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nType = atoi(v4);
        if ( (unsigned int)nType <= 6 )
        {
          v5 = std::map<int,int>::operator[](&this->m_QiQingLevel, &nType);
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          *v5 = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


