// Decompiled methods for class: CHuoYueDuData
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl CHuoYueDuData::~CHuoYueDuData(CHuoYueDuData *const this)
{
  CHuoYueDuData::~CHuoYueDuData(this);
  operator delete(this);
}


#####################################
void __cdecl CHuoYueDuData::SaveToSqlString(
        CHuoYueDuData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // rbx
  const char *v5; // rax
  CHuoYueDuData v8; // [rsp+20h] [rbp-40h] BYREF

  bzero(szSQL, 0x1000u);
  CHuoYueDuData::GetHuoYueDuString(&v8);
  v4 = (const char *)std::string::c_str((std::string *)&v8);
  CHuoYueDuData::GetHuoYueDuString((CHuoYueDuData *const)&v8.m_HuoYueDuRecord._M_t._M_impl._M_header);
  v5 = (const char *)std::string::c_str((std::string *)&v8.m_HuoYueDuRecord._M_t._M_impl._M_header);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT `mem_chr_huo_yue_du`(Cid,HuoYueDuInfo) VALUES (%lld,'%s') ON DUPLICATE KEY UPDATE HuoYueDuInfo='%s'",
    nCid,
    v5,
    v4);
  std::string::~string(&v8.m_HuoYueDuRecord._M_t._M_impl._M_header);
  std::string::~string(&v8);
  std::allocator<char>::allocator((char *)&v8.m_HuoYueDuRecord._M_t._M_impl._M_header._M_right + 7);
  std::string::string(
    &v8.m_HuoYueDuRecord._M_t._M_impl._M_header._M_left,
    (char *)szSQL,
    (char *)&v8.m_HuoYueDuRecord._M_t._M_impl._M_header._M_right + 7);
  std::list<std::string>::push_back(sqls, (const std::string *const)&v8.m_HuoYueDuRecord._M_t._M_impl._M_header._M_left);
  std::string::~string(&v8.m_HuoYueDuRecord._M_t._M_impl._M_header._M_left);
  std::allocator<char>::~allocator((char *)&v8.m_HuoYueDuRecord._M_t._M_impl._M_header._M_right + 7);
}


#####################################
bool __cdecl CHuoYueDuData::LoadFromDB(
        CHuoYueDuData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  std::string HuoYueDuString; // [rsp+30h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+40h] [rbp-40h] BYREF
  char v13; // [rsp+5Fh] [rbp-21h] BYREF
  std::string p_HuoYueDuString; // [rsp+60h] [rbp-20h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_huo_yue_du` WHERE `Cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    std::allocator<char>::allocator(&v13);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "HuoYueDuInfo", byte_8CFE00);
    std::string::string(&HuoYueDuString, StringValue, &v13);
    std::allocator<char>::~allocator(&v13);
    std::string::string(&p_HuoYueDuString, &HuoYueDuString);
    CHuoYueDuData::InitHuoYueDu(this, &p_HuoYueDuString);
    std::string::~string(&p_HuoYueDuString);
    Answer::MySqlQuery::nextRow(&result);
    std::string::~string(&HuoYueDuString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CHuoYueDuData::PackageData(CHuoYueDuData *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t FinishTimes; // edx
  int8_t IsSec; // dl
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  nSize = std::map<int,HuoYueDuRecord>::size(&this->m_HuoYueDuRecord);
  Answer::NetPacket::writeInt32(packet, nSize);
  for ( it._M_node = std::map<int,HuoYueDuRecord>::begin(&this->m_HuoYueDuRecord)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator++(&it) )
  {
    __x._M_node = std::map<int,HuoYueDuRecord>::end(&this->m_HuoYueDuRecord)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->first;
    Answer::NetPacket::writeInt32(packet, first);
    FinishTimes = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->second.FinishTimes;
    Answer::NetPacket::writeInt32(packet, FinishTimes);
    IsSec = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->second.IsSec;
    Answer::NetPacket::writeInt8(packet, IsSec);
  }
}


#####################################
void __cdecl CHuoYueDuData::UnPackageData(CHuoYueDuData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  HuoYueDuRecord *v3; // rax
  int32_t Index; // [rsp+2Ch] [rbp-14h] BYREF
  HuoYueDuRecord stu; // [rsp+30h] [rbp-10h]
  int32_t nSize; // [rsp+38h] [rbp-8h]
  int32_t i; // [rsp+3Ch] [rbp-4h]

  nSize = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < nSize; ++i )
  {
    stu = 0;
    Index = Answer::NetPacket::readInt32(inPacket);
    stu.FinishTimes = Answer::NetPacket::readInt32(inPacket);
    stu.IsSec = Answer::NetPacket::readInt8(inPacket);
    v3 = std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &Index);
    *v3 = stu;
  }
}


#####################################
void __cdecl CHuoYueDuData::InitHuoYueDu(CHuoYueDuData *const this, std::string *p_HuoYueDuString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  HuoYueDuRecord stu; // [rsp+10h] [rbp-A0h]
  int32_t Index; // [rsp+1Ch] [rbp-94h] BYREF
  StringVector StringVt; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-70h] BYREF
  StringVector mineString; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v15; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v17; // [rsp+90h] [rbp-20h] BYREF
  _BYTE v18[17]; // [rsp+9Fh] [rbp-11h] BYREF

  if ( !std::operator==<char>(p_HuoYueDuString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v15);
    std::string::string(&delims, "|", &v15);
    Answer::StringUtility::split(&mineString, p_HuoYueDuString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v15);
    for ( it._M_current = std::vector<std::string>::begin(&mineString)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&mineString)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(v18);
      std::string::string(&v17, ":", v18);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&StringVt, v2, &v17, 0);
      std::string::~string(&v17);
      std::allocator<char>::~allocator(v18);
      if ( std::vector<std::string>::size(&StringVt) == 3 )
      {
        v3 = std::vector<std::string>::operator[](&StringVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        Index = atoi(v4);
        v5 = std::vector<std::string>::operator[](&StringVt, 1u);
        v6 = (const char *)std::string::c_str(v5);
        stu.FinishTimes = atoi(v6);
        v7 = std::vector<std::string>::operator[](&StringVt, 2u);
        v8 = (const char *)std::string::c_str(v7);
        *(_DWORD *)&stu.IsSec = (unsigned __int8)atoi(v8);
        *std::map<int,HuoYueDuRecord>::operator[](&this->m_HuoYueDuRecord, &Index) = stu;
      }
      std::vector<std::string>::~vector(&StringVt);
    }
    std::vector<std::string>::~vector(&mineString);
  }
}


#####################################
std::string __cdecl CHuoYueDuData::GetHuoYueDuString(CHuoYueDuData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int IsSec; // r12d
  unsigned int FinishTimes; // r13d
  std::pair<const int,HuoYueDuRecord> *v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rax
  _BYTE v12[16]; // [rsp+10h] [rbp-1B0h] BYREF
  __int64 v13; // [rsp+20h] [rbp-1A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > it; // [rsp+180h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,HuoYueDuRecord> > __x; // [rsp+190h] [rbp-30h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v12, (unsigned int)v2);
  for ( it._M_node = std::map<int,HuoYueDuRecord>::begin((std::map<int,HuoYueDuRecord> *const)(v1 + 8))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator++(&it) )
  {
    __x._M_node = std::map<int,HuoYueDuRecord>::end((std::map<int,HuoYueDuRecord> *const)(v1 + 8))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator!=(&it, &__x) )
      break;
    IsSec = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->second.IsSec;
    FinishTimes = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it)->second.FinishTimes;
    v5 = std::_Rb_tree_iterator<std::pair<int const,HuoYueDuRecord>>::operator->(&it);
    v6 = std::ostream::operator<<(&v13, (unsigned int)v5->first);
    v7 = std::operator<<<std::char_traits<char>>(v6, ":");
    v8 = std::ostream::operator<<(v7, FinishTimes);
    v9 = std::operator<<<std::char_traits<char>>(v8, ":");
    v10 = std::ostream::operator<<(v9, IsSec);
    std::operator<<<std::char_traits<char>>(v10, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v12);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v12);
  return (std::string)this;
}


