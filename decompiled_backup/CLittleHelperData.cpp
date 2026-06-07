// Decompiled methods for class: CLittleHelperData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CLittleHelperData::~CLittleHelperData(CLittleHelperData *const this)
{
  CLittleHelperData::~CLittleHelperData(this);
  operator delete(this);
}


#####################################
void __cdecl CLittleHelperData::CleanUp(CLittleHelperData *const this)
{
  this->m_LittleHelperId = 0;
  std::map<int,ActLittleHelperInfo>::clear(&this->m_ActLittleHelperInfoMap);
}


#####################################
void __cdecl CLittleHelperData::SaveToSqlString(
        CLittleHelperData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  int32_t m_LittleHelperId; // r12d
  const char *v6; // rax
  CLittleHelperData v9; // [rsp+30h] [rbp-40h] BYREF

  bzero(szSQL, 0x1000u);
  CLittleHelperData::getRewardState(&v9);
  v4 = (const char *)std::string::c_str((std::string *)&v9);
  m_LittleHelperId = this->m_LittleHelperId;
  CLittleHelperData::getRewardState((CLittleHelperData *const)&v9.m_ActLittleHelperInfoMap);
  v6 = (const char *)std::string::c_str((std::string *)&v9.m_ActLittleHelperInfoMap);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_little_helper` (cid,work_id,act_info) VALUES (%lld,%d,'%s') on duplicate key update work_id =%d,act_info='%s'",
    nCid,
    this->m_LittleHelperId,
    v6,
    m_LittleHelperId,
    v4);
  std::string::~string(&v9.m_ActLittleHelperInfoMap);
  std::string::~string(&v9);
  std::allocator<char>::allocator((char *)&v9.m_ActLittleHelperInfoMap._M_t._M_impl._M_header._M_left + 7);
  std::string::string(
    &v9.m_ActLittleHelperInfoMap._M_t._M_impl._M_header._M_parent,
    (char *)szSQL,
    (char *)&v9.m_ActLittleHelperInfoMap._M_t._M_impl._M_header._M_left + 7);
  std::list<std::string>::push_back(
    sqls,
    (const std::string *const)&v9.m_ActLittleHelperInfoMap._M_t._M_impl._M_header._M_parent);
  std::string::~string(&v9.m_ActLittleHelperInfoMap._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v9.m_ActLittleHelperInfoMap._M_t._M_impl._M_header._M_left + 7);
}


#####################################
bool __cdecl CLittleHelperData::LoadFromDB(
        CLittleHelperData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  std::string nString; // [rsp+30h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-40h] BYREF
  char v13; // [rsp+5Fh] [rbp-21h] BYREF
  std::string p_String; // [rsp+60h] [rbp-20h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_little_helper` WHERE `Cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_LittleHelperId = Answer::MySqlQuery::getIntValue(&result, "work_id", 0);
    std::allocator<char>::allocator(&v13);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "act_info", byte_8CFE00);
    std::string::string(&nString, StringValue, &v13);
    std::allocator<char>::~allocator(&v13);
    std::string::string(&p_String, &nString);
    CLittleHelperData::SaveRewardState(this, &p_String);
    std::string::~string(&p_String);
    Answer::MySqlQuery::nextRow(&result);
    std::string::~string(&nString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
std::string __cdecl CLittleHelperData::getRewardState(CLittleHelperData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int nTimes; // r12d
  unsigned int nSkin; // r13d
  std::pair<const int,ActLittleHelperInfo> *v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rax
  _BYTE v12[16]; // [rsp+10h] [rbp-1B0h] BYREF
  __int64 v13; // [rsp+20h] [rbp-1A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > it; // [rsp+180h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > __x; // [rsp+190h] [rbp-30h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v12, (unsigned int)v2);
  for ( it._M_node = std::map<int,ActLittleHelperInfo>::begin((std::map<int,ActLittleHelperInfo> *const)(v1 + 16))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,ActLittleHelperInfo>::end((std::map<int,ActLittleHelperInfo> *const)(v1 + 16))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator!=(&it, &__x) )
      break;
    nTimes = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it)->second.nTimes;
    nSkin = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it)->second.nSkin;
    v5 = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it);
    v6 = std::ostream::operator<<(&v13, (unsigned int)v5->first);
    v7 = std::operator<<<std::char_traits<char>>(v6, ":");
    v8 = std::ostream::operator<<(v7, nSkin);
    v9 = std::operator<<<std::char_traits<char>>(v8, ":");
    v10 = std::ostream::operator<<(v9, nTimes);
    std::operator<<<std::char_traits<char>>(v10, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v12);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v12);
  return (std::string)this;
}


#####################################
void __cdecl CLittleHelperData::SaveRewardState(CLittleHelperData *const this, std::string *p_String)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  ActLittleHelperInfo *v9; // rax
  ActLittleHelperInfo stu; // [rsp+10h] [rbp-A0h] BYREF
  StringVector SocreVt; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-70h] BYREF
  StringVector vt; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v15; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v17; // [rsp+90h] [rbp-20h] BYREF
  _BYTE v18[17]; // [rsp+9Fh] [rbp-11h] BYREF

  if ( (unsigned __int8)std::string::empty(p_String) != 1 )
  {
    std::allocator<char>::allocator(&v15);
    std::string::string(&delims, "|", &v15);
    Answer::StringUtility::split(&vt, p_String, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v15);
    for ( iter._M_current = std::vector<std::string>::begin(&vt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(v18);
      std::string::string(&v17, ":", v18);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&SocreVt, v2, &v17, 0);
      std::string::~string(&v17);
      std::allocator<char>::~allocator(v18);
      if ( std::vector<std::string>::size(&SocreVt) == 3 )
      {
        *(_QWORD *)&stu.nId = 0;
        stu.nTimes = 0;
        v3 = std::vector<std::string>::operator[](&SocreVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        stu.nId = atoi(v4);
        v5 = std::vector<std::string>::operator[](&SocreVt, 1u);
        v6 = (const char *)std::string::c_str(v5);
        stu.nSkin = atoi(v6);
        v7 = std::vector<std::string>::operator[](&SocreVt, 2u);
        v8 = (const char *)std::string::c_str(v7);
        stu.nTimes = atoi(v8);
        v9 = std::map<int,ActLittleHelperInfo>::operator[](&this->m_ActLittleHelperInfoMap, &stu.nId);
        *v9 = stu;
      }
      std::vector<std::string>::~vector(&SocreVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


#####################################
void __cdecl CLittleHelperData::PackageData(CLittleHelperData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int first; // edx
  int32_t nSkin; // edx
  int32_t nTimes; // edx
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ActLittleHelperInfo> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_LittleHelperId);
    v2 = std::map<int,ActLittleHelperInfo>::size(&this->m_ActLittleHelperInfoMap);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( it._M_node = std::map<int,ActLittleHelperInfo>::begin(&this->m_ActLittleHelperInfoMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,ActLittleHelperInfo>::end(&this->m_ActLittleHelperInfoMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      nSkin = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it)->second.nSkin;
      Answer::NetPacket::writeInt32(packet, nSkin);
      nTimes = std::_Rb_tree_iterator<std::pair<int const,ActLittleHelperInfo>>::operator->(&it)->second.nTimes;
      Answer::NetPacket::writeInt32(packet, nTimes);
    }
  }
}


#####################################
void __cdecl CLittleHelperData::UnPackageData(
        CLittleHelperData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  ActLittleHelperInfo *v3; // rax
  ActLittleHelperInfo stu; // [rsp+20h] [rbp-20h] BYREF
  int32_t nSize; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  if ( inPacket )
  {
    this->m_LittleHelperId = Answer::NetPacket::readInt32(inPacket);
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      *(_QWORD *)&stu.nId = 0;
      stu.nTimes = 0;
      stu.nId = Answer::NetPacket::readInt32(inPacket);
      stu.nSkin = Answer::NetPacket::readInt32(inPacket);
      stu.nTimes = Answer::NetPacket::readInt32(inPacket);
      v3 = std::map<int,ActLittleHelperInfo>::operator[](&this->m_ActLittleHelperInfoMap, &stu.nId);
      *v3 = stu;
    }
  }
}


