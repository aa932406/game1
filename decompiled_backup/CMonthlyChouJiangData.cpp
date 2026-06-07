// Decompiled methods for class: CMonthlyChouJiangData
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CMonthlyChouJiangData::~CMonthlyChouJiangData(CMonthlyChouJiangData *const this)
{
  CMonthlyChouJiangData::~CMonthlyChouJiangData(this);
  operator delete(this);
}


#####################################
void __cdecl CMonthlyChouJiangData::CleanUp(CMonthlyChouJiangData *const this)
{
  this->m_Score = 0;
  this->m_AllScore = 0;
  std::list<int>::clear(&this->m_GetItemList);
  std::map<int,int>::clear(&this->m_GetTimes);
}


#####################################
void __cdecl CMonthlyChouJiangData::SaveToSqlString(
        CMonthlyChouJiangData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // r13
  const char *v5; // r12
  int32_t m_AllScore; // r15d
  int32_t m_Score; // r14d
  const char *v8; // rbx
  const char *v9; // rax
  CMonthlyChouJiangData v12; // [rsp+50h] [rbp-80h] BYREF

  bzero(szSQL, 0x1000u);
  CMonthlyChouJiangData::getScoreTime(&v12);
  v4 = (const char *)std::string::c_str((std::string *)&v12);
  CMonthlyChouJiangData::getItemListString((CMonthlyChouJiangData *const)&v12.m_GetItemList);
  v5 = (const char *)std::string::c_str((std::string *)&v12.m_GetItemList);
  m_AllScore = this->m_AllScore;
  m_Score = this->m_Score;
  CMonthlyChouJiangData::getScoreTime((CMonthlyChouJiangData *const)&v12.m_GetTimes);
  v8 = (const char *)std::string::c_str((std::string *)&v12.m_GetTimes);
  CMonthlyChouJiangData::getItemListString((CMonthlyChouJiangData *const)&v12.m_GetTimes._M_t._M_impl._M_header._M_parent);
  v9 = (const char *)std::string::c_str((std::string *)&v12.m_GetTimes._M_t._M_impl._M_header._M_parent);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_month_chou_jiang` (`cid`, `score`, `all_score`, `get_item_list`, `get_score_time`) VALUES (%lld"
    ", %d,%d,'%s','%s') ON DUPLICATE KEY UPDATE `score`=%d, `all_score`=%d, `get_item_list`='%s',`get_score_time`='%s'",
    nCid,
    this->m_Score,
    this->m_AllScore,
    v9,
    v8,
    m_Score,
    m_AllScore,
    v5,
    v4);
  std::string::~string(&v12.m_GetTimes._M_t._M_impl._M_header._M_parent);
  std::string::~string(&v12.m_GetTimes);
  std::string::~string(&v12.m_GetItemList);
  std::string::~string(&v12);
  std::allocator<char>::allocator((char *)&v12.m_GetTimes._M_t._M_impl._M_node_count + 7);
  std::string::string(
    &v12.m_GetTimes._M_t._M_impl._M_header._M_right,
    (char *)szSQL,
    (char *)&v12.m_GetTimes._M_t._M_impl._M_node_count + 7);
  std::list<std::string>::push_back(sqls, (const std::string *const)&v12.m_GetTimes._M_t._M_impl._M_header._M_right);
  std::string::~string(&v12.m_GetTimes._M_t._M_impl._M_header._M_right);
  std::allocator<char>::~allocator((char *)&v12.m_GetTimes._M_t._M_impl._M_node_count + 7);
}


#####################################
bool __cdecl CMonthlyChouJiangData::LoadFromDB(
        CMonthlyChouJiangData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  std::string GetScoreTimesString; // [rsp+30h] [rbp-70h] BYREF
  std::string ItemListString; // [rsp+40h] [rbp-60h] BYREF
  Answer::MySqlQuery result; // [rsp+50h] [rbp-50h] BYREF
  char v15; // [rsp+6Eh] [rbp-32h] BYREF
  char v16; // [rsp+6Fh] [rbp-31h] BYREF
  std::string p_ListString; // [rsp+70h] [rbp-30h] BYREF
  std::string p_ScoreString; // [rsp+80h] [rbp-20h] BYREF

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_month_chou_jiang` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_Score = Answer::MySqlQuery::getIntValue(&result, "score", 0);
    this->m_AllScore = Answer::MySqlQuery::getIntValue(&result, "all_score", 0);
    std::allocator<char>::allocator(&v15);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "get_item_list", byte_8CFE00);
    std::string::string(&ItemListString, StringValue, &v15);
    std::allocator<char>::~allocator(&v15);
    std::allocator<char>::allocator(&v16);
    v8 = Answer::MySqlQuery::getStringValue(&result, "get_score_time", byte_8CFE00);
    std::string::string(&GetScoreTimesString, v8, &v16);
    std::allocator<char>::~allocator(&v16);
    std::string::string(&p_ListString, &ItemListString);
    CMonthlyChouJiangData::ParesItemListString(this, &p_ListString);
    std::string::~string(&p_ListString);
    std::string::string(&p_ScoreString, &GetScoreTimesString);
    CMonthlyChouJiangData::ParesScoreTimesString(this, &p_ScoreString);
    std::string::~string(&p_ScoreString);
    Answer::MySqlQuery::nextRow(&result);
    std::string::~string(&GetScoreTimesString);
    std::string::~string(&ItemListString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl CMonthlyChouJiangData::PackageData(CMonthlyChouJiangData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int32_t v3; // edx
  int32_t v4; // edx
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<int> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<int> __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v10; // [rsp+40h] [rbp-10h] BYREF

  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_Score);
    Answer::NetPacket::writeInt32(packet, this->m_AllScore);
    v2 = std::list<int>::size(&this->m_GetItemList);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( it._M_node = std::list<int>::begin(&this->m_GetItemList)._M_node; ; std::_List_iterator<int>::operator++(&it) )
    {
      __x._M_node = std::list<int>::end(&this->m_GetItemList)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
        break;
      v3 = *std::_List_iterator<int>::operator*(&it);
      Answer::NetPacket::writeInt32(packet, v3);
    }
    v4 = std::map<int,int>::size(&this->m_GetTimes);
    Answer::NetPacket::writeInt32(packet, v4);
    for ( iter._M_node = std::map<int,int>::begin(&this->m_GetTimes)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&iter) )
    {
      v10._M_node = std::map<int,int>::end(&this->m_GetTimes)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&iter, &v10) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&iter)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
  }
}


#####################################
void __cdecl CMonthlyChouJiangData::UnPackageData(
        CMonthlyChouJiangData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  int *v3; // rax
  int32_t nId; // [rsp+24h] [rbp-1Ch] BYREF
  int __x; // [rsp+28h] [rbp-18h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-14h]
  int32_t nSize2; // [rsp+30h] [rbp-10h]
  int32_t i; // [rsp+34h] [rbp-Ch]
  int32_t j; // [rsp+38h] [rbp-8h]
  int32_t nTime; // [rsp+3Ch] [rbp-4h]

  if ( inPacket )
  {
    this->m_Score = Answer::NetPacket::readInt32(inPacket);
    this->m_AllScore = Answer::NetPacket::readInt32(inPacket);
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      __x = Answer::NetPacket::readInt32(inPacket);
      std::list<int>::push_back(&this->m_GetItemList, &__x);
    }
    nSize2 = Answer::NetPacket::readInt32(inPacket);
    for ( j = 0; j < nSize2; ++j )
    {
      nId = Answer::NetPacket::readInt32(inPacket);
      nTime = Answer::NetPacket::readInt32(inPacket);
      v3 = std::map<int,int>::operator[](&this->m_GetTimes, &nId);
      *v3 = nTime;
    }
  }
}


#####################################
std::string __cdecl CMonthlyChouJiangData::getItemListString(CMonthlyChouJiangData *const this)
{
  std::list<int> *v1; // rsi
  std::_Ios_Openmode v2; // eax
  const int *v3; // rax
  _BYTE v5[16]; // [rsp+10h] [rbp-1C0h] BYREF
  _BYTE v6[352]; // [rsp+20h] [rbp-1B0h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+180h] [rbp-50h] BYREF
  std::_List_iterator<int> __x; // [rsp+190h] [rbp-40h] BYREF
  std::_List_const_iterator<int> v9; // [rsp+1A0h] [rbp-30h] BYREF
  std::_List_iterator<int> v10; // [rsp+1B0h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v5, (unsigned int)v2);
  __x._M_node = std::list<int>::begin(v1 + 1)._M_node;
  std::_List_const_iterator<int>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v10._M_node = std::list<int>::end(v1 + 1)._M_node;
    std::_List_const_iterator<int>::_List_const_iterator(&v9, &v10);
    if ( !std::_List_const_iterator<int>::operator!=(&iter, &v9) )
      break;
    v3 = std::_List_const_iterator<int>::operator*(&iter);
    std::ostream::operator<<(v6, *(unsigned int *)v3);
    std::operator<<<std::char_traits<char>>(v6, ":");
    std::_List_const_iterator<int>::operator++(&iter);
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v5);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v5);
  return (std::string)this;
}


#####################################
void __cdecl CMonthlyChouJiangData::ParesItemListString(CMonthlyChouJiangData *const this, std::string *p_ListString)
{
  std::string *v2; // rax
  const char *v3; // rax
  int32_t nId; // [rsp+1Ch] [rbp-64h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+20h] [rbp-60h] BYREF
  StringVector ListVt; // [rsp+30h] [rbp-50h] BYREF
  std::string delims; // [rsp+50h] [rbp-30h] BYREF
  char v8; // [rsp+5Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+60h] [rbp-20h] BYREF

  if ( !(unsigned __int8)std::string::empty(p_ListString) )
  {
    std::allocator<char>::allocator(&v8);
    std::string::string(&delims, ":", &v8);
    Answer::StringUtility::split(&ListVt, p_ListString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v8);
    for ( it._M_current = std::vector<std::string>::begin(&ListVt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<std::string>::end(&ListVt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      v3 = (const char *)std::string::c_str(v2);
      nId = atoi(v3);
      if ( nId > 0 )
        std::list<int>::push_back(&this->m_GetItemList, &nId);
    }
    std::vector<std::string>::~vector(&ListVt);
  }
}


#####################################
std::string __cdecl CMonthlyChouJiangData::getScoreTime(CMonthlyChouJiangData *const this)
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
  __it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 32))._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,int>>::_Rb_tree_const_iterator(&iter, &__it);
  while ( 1 )
  {
    v11._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 32))._M_node;
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
void __cdecl CMonthlyChouJiangData::ParesScoreTimesString(
        CMonthlyChouJiangData *const this,
        std::string *p_ScoreString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  int *v7; // rax
  int32_t nId; // [rsp+1Ch] [rbp-94h] BYREF
  StringVector SocreVt; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-70h] BYREF
  StringVector vt; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v13; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v15; // [rsp+90h] [rbp-20h] BYREF
  char v16; // [rsp+9Bh] [rbp-15h] BYREF
  int32_t nTimes; // [rsp+9Ch] [rbp-14h]

  std::map<int,int>::clear(&this->m_GetTimes);
  if ( (unsigned __int8)std::string::empty(p_ScoreString) != 1 )
  {
    std::allocator<char>::allocator(&v13);
    std::string::string(&delims, "|", &v13);
    Answer::StringUtility::split(&vt, p_ScoreString, &delims, 0);
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
      Answer::StringUtility::split(&SocreVt, v2, &v15, 0);
      std::string::~string(&v15);
      std::allocator<char>::~allocator(&v16);
      if ( std::vector<std::string>::size(&SocreVt) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&SocreVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        nId = atoi(v4);
        v5 = std::vector<std::string>::operator[](&SocreVt, 1u);
        v6 = (const char *)std::string::c_str(v5);
        nTimes = atoi(v6);
        v7 = std::map<int,int>::operator[](&this->m_GetTimes, &nId);
        *v7 = nTimes;
      }
      std::vector<std::string>::~vector(&SocreVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


