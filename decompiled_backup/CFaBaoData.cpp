// Decompiled methods for class: CFaBaoData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CFaBaoData::~CFaBaoData(CFaBaoData *const this)
{
  CFaBaoData::~CFaBaoData(this);
  operator delete(this);
}


#####################################
void __cdecl CFaBaoData::CleanUp(CFaBaoData *const this)
{
  bzero(this->m_FaBao, 0x20u);
}


#####################################
void __cdecl CFaBaoData::SaveToSqlString(
        CFaBaoData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rax
  std::string __x; // [rsp+20h] [rbp-40h] BYREF
  char v8; // [rsp+2Fh] [rbp-31h] BYREF
  CFaBaoData v9; // [rsp+30h] [rbp-30h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_fabao` WHERE `Cid`=%lld", nCid);
  std::allocator<char>::allocator(&v8);
  std::string::string(&__x, (char *)szSQL, &v8);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v8);
  bzero(szSQL, 0x1000u);
  CFaBaoData::GetFaBaoLevelString(&v9);
  v4 = (const char *)std::string::c_str((std::string *)&v9);
  snprintf((char *)szSQL, 0xFFFu, "INSERT INTO `mem_chr_fabao` (`Cid`, `FaBaoLevel`) VALUES (%lld, '%s')", nCid, v4);
  std::string::~string(&v9);
  std::allocator<char>::allocator((char *)&v9.m_FaBao[2].FaBaoRes + 3);
  std::string::string(&v9.m_FaBao[1], (char *)szSQL, (char *)&v9.m_FaBao[2].FaBaoRes + 3);
  std::list<std::string>::push_back(sqls, (const std::string *const)&v9.m_FaBao[1]);
  std::string::~string(&v9.m_FaBao[1]);
  std::allocator<char>::~allocator((char *)&v9.m_FaBao[2].FaBaoRes + 3);
}


#####################################
bool __cdecl CFaBaoData::LoadFromDB(
        CFaBaoData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  std::string FaBaoLevelString; // [rsp+30h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-40h] BYREF
  char v13; // [rsp+5Fh] [rbp-21h] BYREF
  std::string p_FaBaoLevelString; // [rsp+60h] [rbp-20h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_fabao` WHERE `Cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    std::allocator<char>::allocator(&v13);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "FaBaoLevel", byte_8CFE00);
    std::string::string(&FaBaoLevelString, StringValue, &v13);
    std::allocator<char>::~allocator(&v13);
    std::string::string(&p_FaBaoLevelString, &FaBaoLevelString);
    CFaBaoData::ParesFaBaoLevelString(this, &p_FaBaoLevelString);
    std::string::~string(&p_FaBaoLevelString);
    Answer::MySqlQuery::nextRow(&result);
    std::string::~string(&FaBaoLevelString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CFaBaoData::PackageData(CFaBaoData *const this, Answer::NetPacket *packet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 4);
    for ( i = 0; i <= 3; ++i )
    {
      Answer::NetPacket::writeInt8(packet, i);
      Answer::NetPacket::writeInt32(packet, this->m_FaBao[i].FaBaoLevel);
      Answer::NetPacket::writeInt32(packet, this->m_FaBao[i].FaBaoRes);
    }
  }
}


#####################################
void __cdecl CFaBaoData::UnPackageData(CFaBaoData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int8_t nSize; // [rsp+27h] [rbp-19h]
  int32_t i; // [rsp+28h] [rbp-18h]
  int8_t nFaBaoType; // [rsp+2Fh] [rbp-11h]

  if ( inPacket )
  {
    nSize = Answer::NetPacket::readInt8(inPacket);
    for ( i = 0; nSize > i; ++i )
    {
      nFaBaoType = Answer::NetPacket::readInt8(inPacket);
      if ( IsFaBaoType(nFaBaoType) )
      {
        this->m_FaBao[nFaBaoType].FaBaoLevel = Answer::NetPacket::readInt32(inPacket);
        this->m_FaBao[nFaBaoType].FaBaoRes = Answer::NetPacket::readInt32(inPacket);
      }
    }
  }
}


#####################################
std::string __cdecl CFaBaoData::GetFaBaoLevelString(CFaBaoData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 3; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 8LL * i + 8));
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 8LL * i + 12));
    std::operator<<<std::char_traits<char>>(v5, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CFaBaoData::ParesFaBaoLevelString(CFaBaoData *const this, std::string *p_FaBaoLevelString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int32_t v5; // ebx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t v8; // ebx
  std::string *v9; // rax
  const char *v10; // rax
  StringVector tv; // [rsp+10h] [rbp-80h] BYREF
  StringVector vStr; // [rsp+30h] [rbp-60h] BYREF
  std::string delims; // [rsp+50h] [rbp-40h] BYREF
  char v14; // [rsp+5Fh] [rbp-31h] BYREF
  std::string v15; // [rsp+60h] [rbp-30h] BYREF
  char v16; // [rsp+73h] [rbp-1Dh] BYREF
  int32_t isize; // [rsp+74h] [rbp-1Ch]
  int32_t i; // [rsp+78h] [rbp-18h]
  int32_t nType; // [rsp+7Ch] [rbp-14h]

  if ( !std::operator==<char>(p_FaBaoLevelString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v14);
    std::string::string(&delims, "|", &v14);
    Answer::StringUtility::split(&vStr, p_FaBaoLevelString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v14);
    isize = std::vector<std::string>::size(&vStr);
    for ( i = 0; i < isize; ++i )
    {
      std::allocator<char>::allocator(&v16);
      std::string::string(&v15, ":", &v16);
      v2 = std::vector<std::string>::operator[](&vStr, i);
      Answer::StringUtility::split(&tv, v2, &v15, 0);
      std::string::~string(&v15);
      std::allocator<char>::~allocator(&v16);
      if ( std::vector<std::string>::size(&tv) == 3 )
      {
        v3 = std::vector<std::string>::operator[](&tv, 0);
        v4 = (const char *)std::string::c_str(v3);
        nType = atoi(v4);
        if ( IsFaBaoType(nType) )
        {
          v5 = nType;
          v6 = std::vector<std::string>::operator[](&tv, 1u);
          v7 = (const char *)std::string::c_str(v6);
          this->m_FaBao[v5].FaBaoLevel = atoi(v7);
          v8 = nType;
          v9 = std::vector<std::string>::operator[](&tv, 2u);
          v10 = (const char *)std::string::c_str(v9);
          this->m_FaBao[v8].FaBaoRes = atoi(v10);
        }
      }
      std::vector<std::string>::~vector(&tv);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


