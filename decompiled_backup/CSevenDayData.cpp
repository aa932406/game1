// Decompiled methods for class: CSevenDayData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CSevenDayData::~CSevenDayData(CSevenDayData *const this)
{
  CSevenDayData::~CSevenDayData(this);
  operator delete(this);
}


#####################################
void __cdecl CSevenDayData::CleanUp(CSevenDayData *const this)
{
  this->m_OpenTime = 0;
  std::map<int,int>::clear(&this->m_RewardState);
  this->m_SumRewardState = 0;
}


#####################################
void __cdecl CSevenDayData::SaveToSqlString(
        CSevenDayData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  int32_t m_SumRewardState; // r14d
  const char *v5; // rbx
  int32_t m_OpenTime; // r13d
  int32_t v7; // r12d
  const char *v8; // rax
  CSevenDayData v11; // [rsp+40h] [rbp-50h] BYREF

  bzero(szSQL, 0x1000u);
  m_SumRewardState = this->m_SumRewardState;
  CSevenDayData::getRewardState(&v11);
  v5 = (const char *)std::string::c_str((std::string *)&v11);
  m_OpenTime = this->m_OpenTime;
  v7 = this->m_SumRewardState;
  CSevenDayData::getRewardState((CSevenDayData *const)&v11.m_RewardState);
  v8 = (const char *)std::string::c_str((std::string *)&v11.m_RewardState);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_seven_task` (cid,open_time,reward_state,sum_reward_state) VALUES (%lld,%d,'%s',%d) on duplicate"
    " key update open_time =%d,reward_state='%s',sum_reward_state=%d",
    nCid,
    this->m_OpenTime,
    v8,
    v7,
    m_OpenTime,
    v5,
    m_SumRewardState);
  std::string::~string(&v11.m_RewardState);
  std::string::~string(&v11);
  std::allocator<char>::allocator((char *)&v11.m_RewardState._M_t._M_impl._M_header._M_left + 7);
  std::string::string(
    &v11.m_RewardState._M_t._M_impl._M_header._M_parent,
    (char *)szSQL,
    (char *)&v11.m_RewardState._M_t._M_impl._M_header._M_left + 7);
  std::list<std::string>::push_back(sqls, (const std::string *const)&v11.m_RewardState._M_t._M_impl._M_header._M_parent);
  std::string::~string(&v11.m_RewardState._M_t._M_impl._M_header._M_parent);
  std::allocator<char>::~allocator((char *)&v11.m_RewardState._M_t._M_impl._M_header._M_left + 7);
}


#####################################
bool __cdecl CSevenDayData::LoadFromDB(
        CSevenDayData *const this,
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
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_seven_task` WHERE `Cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    this->m_OpenTime = Answer::MySqlQuery::getIntValue(&result, "open_time", 0);
    this->m_SumRewardState = Answer::MySqlQuery::getIntValue(&result, "sum_reward_state", 0);
    std::allocator<char>::allocator(&v13);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "reward_state", byte_8CFE00);
    std::string::string(&nString, StringValue, &v13);
    std::allocator<char>::~allocator(&v13);
    std::string::string(&p_String, &nString);
    CSevenDayData::SaveRewardState(this, &p_String);
    std::string::~string(&p_String);
    Answer::MySqlQuery::nextRow(&result);
    std::string::~string(&nString);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
std::string __cdecl CSevenDayData::getRewardState(CSevenDayData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int second; // r12d
  std::pair<const int,int> *v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  _BYTE v9[16]; // [rsp+10h] [rbp-1A0h] BYREF
  __int64 v10; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v9, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 16))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 16))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    v5 = std::ostream::operator<<(&v10, (unsigned int)v4->first);
    v6 = std::operator<<<std::char_traits<char>>(v5, ":");
    v7 = std::ostream::operator<<(v6, second);
    std::operator<<<std::char_traits<char>>(v7, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v9);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v9);
  return (std::string)this;
}


#####################################
void __cdecl CSevenDayData::SaveRewardState(CSevenDayData *const this, std::string *p_String)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  int32_t nId; // [rsp+1Ch] [rbp-94h] BYREF
  StringVector SocreVt; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-70h] BYREF
  StringVector vt; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v13; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v15; // [rsp+90h] [rbp-20h] BYREF
  _BYTE v16[17]; // [rsp+9Fh] [rbp-11h] BYREF

  if ( (unsigned __int8)std::string::empty(p_String) != 1 )
  {
    std::allocator<char>::allocator(&v13);
    std::string::string(&delims, "|", &v13);
    Answer::StringUtility::split(&vt, p_String, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v13);
    for ( iter._M_current = std::vector<std::string>::begin(&vt)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vt)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(v16);
      std::string::string(&v15, ":", v16);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&SocreVt, v2, &v15, 0);
      std::string::~string(&v15);
      std::allocator<char>::~allocator(v16);
      if ( std::vector<std::string>::size(&SocreVt) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&SocreVt, 0);
        v4 = (const char *)std::string::c_str(v3);
        nId = atoi(v4);
        v5 = std::map<int,int>::operator[](&this->m_RewardState, &nId);
        v6 = std::vector<std::string>::operator[](&SocreVt, 1u);
        v7 = (const char *)std::string::c_str(v6);
        *v5 = atoi(v7);
      }
      std::vector<std::string>::~vector(&SocreVt);
    }
    std::vector<std::string>::~vector(&vt);
  }
}


#####################################
void __cdecl CSevenDayData::PackageData(CSevenDayData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int first; // edx
  int32_t second; // edx
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( packet )
  {
    v2 = std::map<int,int>::size(&this->m_RewardState);
    Answer::NetPacket::writeInt32(packet, v2);
    for ( it._M_node = std::map<int,int>::begin(&this->m_RewardState)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_RewardState)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
      Answer::NetPacket::writeInt32(packet, second);
    }
    Answer::NetPacket::writeInt32(packet, this->m_OpenTime);
    Answer::NetPacket::writeInt32(packet, this->m_SumRewardState);
  }
}


#####################################
void __cdecl CSevenDayData::UnPackageData(CSevenDayData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  int *v3; // rax
  int32_t nId; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+24h] [rbp-Ch]
  int32_t i; // [rsp+28h] [rbp-8h]
  int32_t nState; // [rsp+2Ch] [rbp-4h]

  if ( inPacket )
  {
    nSize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nSize; ++i )
    {
      nId = Answer::NetPacket::readInt32(inPacket);
      nState = Answer::NetPacket::readInt32(inPacket);
      v3 = std::map<int,int>::operator[](&this->m_RewardState, &nId);
      *v3 = nState;
    }
    this->m_OpenTime = Answer::NetPacket::readInt32(inPacket);
    this->m_SumRewardState = Answer::NetPacket::readInt32(inPacket);
  }
}


