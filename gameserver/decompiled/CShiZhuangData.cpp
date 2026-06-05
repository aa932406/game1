// Decompiled methods for class: CShiZhuangData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CShiZhuangData::~CShiZhuangData(CShiZhuangData *const this)
{
  CShiZhuangData::~CShiZhuangData(this);
  operator delete(this);
}


#####################################
void __cdecl CShiZhuangData::CleanUp(CShiZhuangData *const this)
{
  int8_t i; // [rsp+1Fh] [rbp-1h]

  for ( i = 0; i <= 2; ++i )
    ShiZhuangInfo::CleanUp(&this->m_vShiZhuang[(__int64)i]);
  std::map<int,int>::clear(&this->m_ShiZhuangLevel);
  this->m_EffectId = 0;
}


#####################################
void __cdecl CShiZhuangData::SaveToSqlString(
        CShiZhuangData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  int32_t m_nWear; // r14d
  int32_t m_nExp; // r13d
  int32_t m_nLevel; // r12d
  const char *v8; // rax
  int32_t m_EffectId; // r12d
  const char *v10; // rbx
  int32_t v11; // r13d
  const char *v12; // rax
  std::string strActive; // [rsp+60h] [rbp-60h] BYREF
  std::string ShiZhuangLevel; // [rsp+70h] [rbp-50h] BYREF
  std::string __x; // [rsp+80h] [rbp-40h] BYREF
  char v18; // [rsp+8Fh] [rbp-31h] BYREF
  std::string v19; // [rsp+90h] [rbp-30h] BYREF
  char v20; // [rsp+9Eh] [rbp-22h] BYREF
  int8_t i; // [rsp+9Fh] [rbp-21h]

  for ( i = 0; i <= 2; ++i )
  {
    ShiZhuangInfo::GetActiveString((const ShiZhuangInfo *const)&strActive);
    bzero(szSQL, 0x1000u);
    v4 = (const char *)std::string::c_str(&strActive);
    m_nWear = this->m_vShiZhuang[(__int64)i].m_nWear;
    m_nExp = this->m_vShiZhuang[(__int64)i].m_nExp;
    m_nLevel = this->m_vShiZhuang[(__int64)i].m_nLevel;
    v8 = (const char *)std::string::c_str(&strActive);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_char_shi_zhuang` (`cid`, `type`, `level`, `exp`, `wear`,`active`) VALUES (%lld, %d,%d,%d,%d,'%s')"
      " ON DUPLICATE KEY UPDATE `level`=%d, `exp`=%d, `wear`=%d,`active`='%s'",
      nCid,
      i,
      this->m_vShiZhuang[(__int64)i].m_nLevel,
      this->m_vShiZhuang[(__int64)i].m_nExp,
      this->m_vShiZhuang[(__int64)i].m_nWear,
      v8,
      m_nLevel,
      m_nExp,
      m_nWear,
      v4);
    std::allocator<char>::allocator(&v18);
    std::string::string(&__x, (char *)szSQL, &v18);
    std::list<std::string>::push_back(sqls, &__x);
    std::string::~string(&__x);
    std::allocator<char>::~allocator(&v18);
    std::string::~string(&strActive);
  }
  CShiZhuangData::GetShiZhuangLevelString((CShiZhuangData *const)&ShiZhuangLevel);
  bzero(szSQL, 0x1000u);
  m_EffectId = this->m_EffectId;
  v10 = (const char *)std::string::c_str(&ShiZhuangLevel);
  v11 = this->m_EffectId;
  v12 = (const char *)std::string::c_str(&ShiZhuangLevel);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_char_shi_zhuang_level` (`cid`, `shi_zhuang_level`,`effect`) VALUES (%lld,'%s',%d) ON DUPLICATE KEY "
    "UPDATE `shi_zhuang_level`='%s',`effect`=%d",
    nCid,
    v12,
    v11,
    v10,
    m_EffectId);
  std::allocator<char>::allocator(&v20);
  std::string::string(&v19, (char *)szSQL, &v20);
  std::list<std::string>::push_back(sqls, &v19);
  std::string::~string(&v19);
  std::allocator<char>::~allocator(&v20);
  std::string::~string(&ShiZhuangLevel);
}


#####################################
bool __cdecl CShiZhuangData::LoadFromDB(
        CShiZhuangData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  int v7; // ebx
  int v8; // ebx
  int v9; // ebx
  const char *StringValue; // rax
  Answer::MySqlQuery *v11; // rax
  const char *v12; // rax
  Answer::MySqlQuery result_0; // [rsp+30h] [rbp-70h] BYREF
  Answer::MySqlQuery result; // [rsp+50h] [rbp-50h] BYREF
  std::string strActive; // [rsp+70h] [rbp-30h] BYREF
  char v19; // [rsp+7Fh] [rbp-21h] BYREF
  std::string p_ShiZhuangLevel; // [rsp+80h] [rbp-20h] BYREF
  char v21; // [rsp+8Eh] [rbp-12h] BYREF
  int8_t nType; // [rsp+8Fh] [rbp-11h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_shi_zhuang` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    nType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    if ( (unsigned __int8)nType <= 2u )
    {
      v7 = nType;
      this->m_vShiZhuang[(__int64)v7].m_nLevel = Answer::MySqlQuery::getIntValue(&result, "level", 0);
      v8 = nType;
      this->m_vShiZhuang[(__int64)v8].m_nExp = Answer::MySqlQuery::getIntValue(&result, "exp", 0);
      v9 = nType;
      this->m_vShiZhuang[(__int64)v9].m_nWear = Answer::MySqlQuery::getIntValue(&result, "wear", 0);
      std::allocator<char>::allocator(&v19);
      StringValue = Answer::MySqlQuery::getStringValue(&result, "active", byte_8CFE00);
      std::string::string(&strActive, StringValue, &v19);
      ShiZhuangInfo::ParesActiveString(&this->m_vShiZhuang[(__int64)nType], &strActive);
      std::string::~string(&strActive);
      std::allocator<char>::~allocator(&v19);
    }
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_char_shi_zhuang_level` WHERE `cid`=%lld", nCid);
  v11 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result_0, v11);
  while ( !Answer::MySqlQuery::eof(&result_0) )
  {
    std::allocator<char>::allocator(&v21);
    v12 = Answer::MySqlQuery::getStringValue(&result_0, "shi_zhuang_level", byte_8CFE00);
    std::string::string(&p_ShiZhuangLevel, v12, &v21);
    CShiZhuangData::ParesShiZhuangLevelString(this, &p_ShiZhuangLevel);
    std::string::~string(&p_ShiZhuangLevel);
    std::allocator<char>::~allocator(&v21);
    this->m_EffectId = Answer::MySqlQuery::getIntValue(&result_0, "effect", 0);
    Answer::MySqlQuery::nextRow(&result_0);
  }
  Answer::MySqlQuery::~MySqlQuery(&result_0);
  return 1;
}


#####################################
void __cdecl CShiZhuangData::PackageData(CShiZhuangData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int first; // edx
  int32_t second; // edx
  int32_t v5; // edx
  int v6; // edx
  int32_t v7; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v11; // [rsp+40h] [rbp-10h] BYREF
  int32_t i; // [rsp+4Ch] [rbp-4h]

  if ( packet )
  {
    for ( i = 0; i <= 2; ++i )
    {
      Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[(__int64)i].m_nLevel);
      Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[(__int64)i].m_nExp);
      Answer::NetPacket::writeInt32(packet, this->m_vShiZhuang[(__int64)i].m_nWear);
      v2 = std::map<int,int>::size(&this->m_vShiZhuang[(__int64)i].m_lActive);
      Answer::NetPacket::writeInt32(packet, v2);
      for ( iter._M_node = std::map<int,int>::begin(&this->m_vShiZhuang[(__int64)i].m_lActive)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_vShiZhuang[(__int64)i].m_lActive)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
          break;
        first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
        Answer::NetPacket::writeInt32(packet, first);
        second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
        Answer::NetPacket::writeInt32(packet, second);
      }
    }
    v5 = std::map<int,int>::size(&this->m_ShiZhuangLevel);
    Answer::NetPacket::writeInt32(packet, v5);
    for ( it._M_node = std::map<int,int>::begin(&this->m_ShiZhuangLevel)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      v11._M_node = std::map<int,int>::end(&this->m_ShiZhuangLevel)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &v11) )
        break;
      v6 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, v6);
      v7 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, v7);
    }
    Answer::NetPacket::writeInt32(packet, this->m_EffectId);
  }
}


#####################################
void __cdecl CShiZhuangData::UnPackageData(CShiZhuangData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int32_t v3; // ebx
  int32_t v4; // ebx
  int32_t v5; // ebx
  int *v6; // rax
  int *v7; // rax
  int32_t nId_0; // [rsp+2Ch] [rbp-34h] BYREF
  int32_t nId; // [rsp+30h] [rbp-30h] BYREF
  int32_t nSize; // [rsp+34h] [rbp-2Ch]
  int32_t i; // [rsp+38h] [rbp-28h]
  int32_t nSize_0; // [rsp+3Ch] [rbp-24h]
  int32_t j; // [rsp+40h] [rbp-20h]
  int32_t nTime; // [rsp+44h] [rbp-1Ch]
  int32_t i_0; // [rsp+48h] [rbp-18h]
  int32_t nLevel; // [rsp+4Ch] [rbp-14h]

  if ( inPacket )
  {
    for ( i = 0; i <= 2; ++i )
    {
      v3 = i;
      this->m_vShiZhuang[(__int64)v3].m_nLevel = Answer::NetPacket::readInt32(inPacket);
      v4 = i;
      this->m_vShiZhuang[(__int64)v4].m_nExp = Answer::NetPacket::readInt32(inPacket);
      v5 = i;
      this->m_vShiZhuang[(__int64)v5].m_nWear = Answer::NetPacket::readInt32(inPacket);
      nSize_0 = Answer::NetPacket::readInt32(inPacket);
      for ( j = 0; j < nSize_0; ++j )
      {
        nId = Answer::NetPacket::readInt32(inPacket);
        nTime = Answer::NetPacket::readInt32(inPacket);
        v6 = std::map<int,int>::operator[](&this->m_vShiZhuang[(__int64)i].m_lActive, &nId);
        *v6 = nTime;
      }
    }
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i_0 = 0; i_0 < nSize; ++i_0 )
    {
      nId_0 = Answer::NetPacket::readInt32(inPacket);
      nLevel = Answer::NetPacket::readInt32(inPacket);
      v7 = std::map<int,int>::operator[](&this->m_ShiZhuangLevel, &nId_0);
      *v7 = nLevel;
    }
    this->m_EffectId = Answer::NetPacket::readInt32(inPacket);
  }
}


#####################################
std::string __cdecl CShiZhuangData::GetShiZhuangLevelString(CShiZhuangData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  const std::pair<const int,int> *v3; // rax
  const std::pair<const int,int> *v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1C0h] BYREF
  _BYTE v7[352]; // [rsp+20h] [rbp-1B0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > iter; // [rsp+180h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __it; // [rsp+190h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,int> > __x; // [rsp+1A0h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v11; // [rsp+1B0h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  __it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 200))._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,int>>::_Rb_tree_const_iterator(&iter, &__it);
  while ( 1 )
  {
    v11._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 200))._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,int>>::_Rb_tree_const_iterator(&__x, &v11);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter);
    std::ostream::operator<<(v7, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v4 = std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator->(&iter);
    std::ostream::operator<<(v7, (unsigned int)v4->second);
    std::operator<<<std::char_traits<char>>(v7, "|");
    std::_Rb_tree_const_iterator<std::pair<int const,int>>::operator++(&iter);
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl CShiZhuangData::ParesShiZhuangLevelString(CShiZhuangData *const this, std::string *p_ShiZhuangLevel)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  int *v7; // rax
  int32_t nId; // [rsp+1Ch] [rbp-94h] BYREF
  StringVector ShiZhuangVt; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-70h] BYREF
  StringVector vt; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v13; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v15; // [rsp+90h] [rbp-20h] BYREF
  char v16; // [rsp+9Bh] [rbp-15h] BYREF
  int32_t nLevel; // [rsp+9Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty(p_ShiZhuangLevel) != 1 )
  {
    std::allocator<char>::allocator(&v13);
    std::string::string(&delims, "|", &v13);
    Answer::StringUtility::split(&vt, p_ShiZhuangLevel, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v13);
    for ( iter._M_current = std::vector<std::string>::begin(&vt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(&v16);
      std::string::string(&v15, ":", &v16);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&ShiZhuangVt, v2, &v15, 0);
      std::string::~string(&v15);
      std::allocator<char>::~allocator(&v16);
      if ( std::vector<std::string>::size(&ShiZhuangVt) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&ShiZhuangVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        nId = atoi(v4);
        v5 = std::vector<std::string>::operator[](&ShiZhuangVt, 1u);
        v6 = (const char *)std::string::c_str(v5);
        nLevel = atoi(v6);
        v7 = std::map<int,int>::operator[](&this->m_ShiZhuangLevel, &nId);
        *v7 = nLevel;
      }
      std::vector<std::string>::~vector(&ShiZhuangVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


