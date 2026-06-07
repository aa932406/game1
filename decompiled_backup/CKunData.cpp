// Decompiled methods for class: CKunData
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CKunData::~CKunData(CKunData *const this)
{
  CKunData::~CKunData(this);
  operator delete(this);
}


#####################################
void __cdecl CKunData::CleanUp(CKunData *const this)
{
  this->m_nBuyTime = 0;
  this->m_nLianHuaTime = 0;
  this->m_nKunLevel = 0;
  this->m_nExp = 0;
  bzero(this->m_LingZhuPos, 0x50u);
  bzero(this->m_LingZhuBag, 0x320u);
  bzero(this->m_DanTian, 0x48u);
}


#####################################
void __cdecl CKunData::SaveToSqlString(
        CKunData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // r13
  const char *v5; // r12
  int32_t m_nLianHuaTime; // r15d
  int32_t m_nBuyTime; // r14d
  const char *v8; // rbx
  const char *v9; // rax
  int32_t m_nExp; // [rsp+58h] [rbp-B8h]
  int32_t m_nKunLevel; // [rsp+5Ch] [rbp-B4h]
  std::string __x; // [rsp+80h] [rbp-90h] BYREF
  char v15; // [rsp+8Fh] [rbp-81h] BYREF
  std::string v16; // [rsp+90h] [rbp-80h] BYREF
  std::string v17; // [rsp+A0h] [rbp-70h] BYREF
  std::string v18; // [rsp+B0h] [rbp-60h] BYREF
  std::string v19; // [rsp+C0h] [rbp-50h] BYREF
  std::string v20; // [rsp+D0h] [rbp-40h] BYREF
  char v21; // [rsp+DBh] [rbp-35h] BYREF
  int32_t i; // [rsp+DCh] [rbp-34h]

  for ( i = 0; i <= 99; ++i )
  {
    bzero(szSQL, 0x1000u);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_kun_bag` (`cid`, `slot`, `nId`, `nCount`) VALUES (%lld, %d,%d,%d) ON DUPLICATE KEY UPDATE `nI"
      "d`=%d, `nCount`=%d",
      nCid,
      i,
      this->m_LingZhuBag[i].nId,
      this->m_LingZhuBag[i].nCount,
      this->m_LingZhuBag[i].nId,
      this->m_LingZhuBag[i].nCount);
    std::allocator<char>::allocator(&v15);
    std::string::string(&__x, (char *)szSQL, &v15);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v15);
  }
  bzero(szSQL, 0x1000u);
  CKunData::getLingZhuPosString((CKunData *const)&v16);
  v4 = (const char *)std::string::c_str(&v16);
  CKunData::getDanTianString((CKunData *const)&v17);
  v5 = (const char *)std::string::c_str(&v17);
  m_nExp = this->m_nExp;
  m_nKunLevel = this->m_nKunLevel;
  m_nLianHuaTime = this->m_nLianHuaTime;
  m_nBuyTime = this->m_nBuyTime;
  CKunData::getLingZhuPosString((CKunData *const)&v18);
  v8 = (const char *)std::string::c_str(&v18);
  CKunData::getDanTianString((CKunData *const)&v19);
  v9 = (const char *)std::string::c_str(&v19);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_kun` (`cid`, `buy_times`, `lian_hua_time`, `kun_level`, `exp`,`dan_tian`, `ling_zhu_pos`) VALUE"
    "S (%lld, %d,%d,%d,%d,'%s','%s') ON DUPLICATE KEY UPDATE `buy_times`=%d, `lian_hua_time`=%d,`kun_level`=%d, `exp`=%d,"
    " `dan_tian`='%s',`ling_zhu_pos`='%s'",
    nCid,
    this->m_nBuyTime,
    this->m_nLianHuaTime,
    this->m_nKunLevel,
    this->m_nExp,
    v9,
    v8,
    m_nBuyTime,
    m_nLianHuaTime,
    m_nKunLevel,
    m_nExp,
    v5,
    v4);
  std::string::~string(&v19);
  std::string::~string(&v18);
  std::string::~string(&v17);
  std::string::~string(&v16);
  std::allocator<char>::allocator(&v21);
  std::string::string(&v20, (char *)szSQL, &v21);
  std::list<std::string>::push_back(sqls, &v20);
  std::string::~string(&v20);
  std::allocator<char>::~allocator(&v21);
}


#####################################
bool __cdecl CKunData::LoadFromDB(
        CKunData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  int32_t v7; // ebx
  int32_t v8; // ebx
  Answer::MySqlQuery *v9; // rax
  const char *StringValue; // rax
  const char *v11; // rax
  std::string DanTianString; // [rsp+30h] [rbp-90h] BYREF
  std::string LingZhuPos; // [rsp+40h] [rbp-80h] BYREF
  Answer::MySqlQuery result_0; // [rsp+50h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+70h] [rbp-50h] BYREF
  char v19; // [rsp+8Eh] [rbp-32h] BYREF
  char v20; // [rsp+8Fh] [rbp-31h] BYREF
  std::string p_LingZhuPos; // [rsp+90h] [rbp-30h] BYREF
  std::string p_DanTianString; // [rsp+A0h] [rbp-20h] BYREF
  int32_t slot; // [rsp+ACh] [rbp-14h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_kun_bag` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    slot = Answer::MySqlQuery::getIntValue(&result, "slot", 0);
    if ( (unsigned int)slot < 0x64 )
    {
      v7 = slot;
      this->m_LingZhuBag[v7].nId = Answer::MySqlQuery::getIntValue(&result, "nId", 0);
      v8 = slot;
      this->m_LingZhuBag[v8].nCount = Answer::MySqlQuery::getIntValue(&result, "nCount", 0);
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_kun` WHERE `cid`=%lld", nCid);
  v9 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_0, v9);
  while ( !Answer::MySqlQuery::eof(&result_0) )
  {
    this->m_nBuyTime = Answer::MySqlQuery::getIntValue(&result_0, "buy_times", 0);
    this->m_nLianHuaTime = Answer::MySqlQuery::getIntValue(&result_0, "lian_hua_time", 0);
    this->m_nKunLevel = Answer::MySqlQuery::getIntValue(&result_0, "kun_level", 0);
    this->m_nExp = Answer::MySqlQuery::getIntValue(&result_0, "exp", 0);
    std::allocator<char>::allocator(&v19);
    StringValue = Answer::MySqlQuery::getStringValue(&result_0, "ling_zhu_pos", byte_8CFE00);
    std::string::string(&LingZhuPos, StringValue, &v19);
    std::allocator<char>::~allocator(&v19);
    std::allocator<char>::allocator(&v20);
    v11 = Answer::MySqlQuery::getStringValue(&result_0, "dan_tian", byte_8CFE00);
    std::string::string(&DanTianString, v11, &v20);
    std::allocator<char>::~allocator(&v20);
    std::string::string(&p_LingZhuPos, &LingZhuPos);
    CKunData::ParesLingZhuPosString(this, &p_LingZhuPos);
    std::string::~string(&p_LingZhuPos);
    std::string::string(&p_DanTianString, &DanTianString);
    CKunData::ParesDanTianString(this, &p_DanTianString);
    std::string::~string(&p_DanTianString);
    Answer::MySqlQuery::nextRow(&result_0);
    std::string::~string(&DanTianString);
    std::string::~string(&LingZhuPos);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_0);
  return 1;
}


#####################################
void __cdecl CKunData::PackageData(CKunData *const this, Answer::NetPacket *packet)
{
  int32_t i; // [rsp+14h] [rbp-Ch]
  int32_t j; // [rsp+18h] [rbp-8h]
  int32_t k; // [rsp+1Ch] [rbp-4h]

  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_nBuyTime);
    Answer::NetPacket::writeInt32(packet, this->m_nLianHuaTime);
    Answer::NetPacket::writeInt32(packet, this->m_nKunLevel);
    Answer::NetPacket::writeInt32(packet, this->m_nExp);
    for ( i = 0; i <= 5; ++i )
    {
      Answer::NetPacket::writeInt32(packet, this->m_DanTian[i].nMid);
      Answer::NetPacket::writeInt32(packet, this->m_DanTian[i].nId);
      Answer::NetPacket::writeInt32(packet, this->m_DanTian[i].nEndTime);
    }
    for ( j = 0; j <= 99; ++j )
    {
      Answer::NetPacket::writeInt32(packet, this->m_LingZhuBag[j].nId);
      Answer::NetPacket::writeInt32(packet, this->m_LingZhuBag[j].nCount);
    }
    for ( k = 0; k <= 19; ++k )
      Answer::NetPacket::writeInt32(packet, this->m_LingZhuPos[k]);
  }
}


#####################################
void __cdecl CKunData::UnPackageData(CKunData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int32_t i; // [rsp+24h] [rbp-1Ch]
  int32_t j; // [rsp+28h] [rbp-18h]
  int32_t k; // [rsp+2Ch] [rbp-14h]

  if ( inPacket )
  {
    this->m_nBuyTime = Answer::NetPacket::readInt32(inPacket);
    this->m_nLianHuaTime = Answer::NetPacket::readInt32(inPacket);
    this->m_nKunLevel = Answer::NetPacket::readInt32(inPacket);
    this->m_nExp = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i <= 5; ++i )
    {
      this->m_DanTian[i].nMid = Answer::NetPacket::readInt32(inPacket);
      this->m_DanTian[i].nId = Answer::NetPacket::readInt32(inPacket);
      this->m_DanTian[i].nEndTime = Answer::NetPacket::readInt32(inPacket);
    }
    for ( j = 0; j <= 99; ++j )
    {
      this->m_LingZhuBag[j].nId = Answer::NetPacket::readInt32(inPacket);
      this->m_LingZhuBag[j].nCount = Answer::NetPacket::readInt32(inPacket);
    }
    for ( k = 0; k <= 19; ++k )
      this->m_LingZhuPos[k] = Answer::NetPacket::readInt32(inPacket);
  }
}


#####################################
std::string __cdecl CKunData::getLingZhuPosString(CKunData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 19; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 4 * (i + 224LL)));
    std::operator<<<std::char_traits<char>>(v5, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CKunData::ParesLingZhuPosString(CKunData *const this, std::string *p_LingZhuPos)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int32_t v5; // ebx
  std::string *v6; // rax
  const char *v7; // rax
  StringVector ListVt; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+30h] [rbp-70h] BYREF
  StringVector vt; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  std::string v14; // [rsp+80h] [rbp-20h] BYREF
  char v15; // [rsp+8Bh] [rbp-15h] BYREF
  int32_t nId; // [rsp+8Ch] [rbp-14h]

  if ( !(unsigned __int8)std::string::empty(p_LingZhuPos) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vt, p_LingZhuPos, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    for ( iter._M_current = std::vector<std::string>::begin(&vt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(&v15);
      std::string::string(&v14, ":", &v15);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&ListVt, v2, &v14, 0);
      std::string::~string(&v14);
      std::allocator<char>::~allocator(&v15);
      if ( std::vector<std::string>::size(&ListVt) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&ListVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        nId = atoi(v4);
        if ( (unsigned int)nId < 0x14 )
        {
          v5 = nId;
          v6 = std::vector<std::string>::operator[](&ListVt, 1u);
          v7 = (const char *)std::string::c_str(v6);
          this->m_LingZhuPos[v5] = atoi(v7);
        }
      }
      std::vector<std::string>::~vector(&ListVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


#####################################
std::string __cdecl CKunData::getDanTianString(CKunData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 5; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 12LL * i + 24));
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 12LL * i + 32));
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 12LL * i + 28));
    std::operator<<<std::char_traits<char>>(v5, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
void __cdecl CKunData::ParesDanTianString(CKunData *const this, std::string *p_DanTianString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int32_t v5; // r12d
  std::string *v6; // rax
  const char *v7; // rax
  int32_t v8; // r12d
  std::string *v9; // rax
  const char *v10; // rax
  int32_t v11; // r12d
  std::string *v12; // rax
  const char *v13; // rax
  StringVector SocreVt; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+30h] [rbp-70h] BYREF
  StringVector vt; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v18; // [rsp+6Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  std::string v20; // [rsp+80h] [rbp-20h] BYREF
  char v21; // [rsp+8Bh] [rbp-15h] BYREF
  int32_t nId; // [rsp+8Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty(p_DanTianString) != 1 )
  {
    std::allocator<char>::allocator(&v18);
    std::string::string(&delims, "|", &v18);
    Answer::StringUtility::split(&vt, p_DanTianString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v18);
    for ( iter._M_current = std::vector<std::string>::begin(&vt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(&v21);
      std::string::string(&v20, ":", &v21);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&SocreVt, v2, &v20, 0);
      std::string::~string(&v20);
      std::allocator<char>::~allocator(&v21);
      if ( std::vector<std::string>::size(&SocreVt) == 4 )
      {
        v3 = std::vector<std::string>::operator[](&SocreVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        nId = atoi(v4);
        if ( (unsigned int)nId <= 5 )
        {
          v5 = nId;
          v6 = std::vector<std::string>::operator[](&SocreVt, 1u);
          v7 = (const char *)std::string::c_str(v6);
          this->m_DanTian[v5].nMid = atoi(v7);
          v8 = nId;
          v9 = std::vector<std::string>::operator[](&SocreVt, 2u);
          v10 = (const char *)std::string::c_str(v9);
          this->m_DanTian[v8].nId = atoi(v10);
          v11 = nId;
          v12 = std::vector<std::string>::operator[](&SocreVt, 3u);
          v13 = (const char *)std::string::c_str(v12);
          this->m_DanTian[v11].nEndTime = atoi(v13);
        }
      }
      std::vector<std::string>::~vector(&SocreVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


