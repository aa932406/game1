// Decompiled methods for class: DailyActivityData
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl DailyActivityData::~DailyActivityData(DailyActivityData *const this)
{
  DailyActivityData::~DailyActivityData(this);
  operator delete(this);
}


#####################################
void __cdecl DailyActivityData::CleanUp(DailyActivityData *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  bzero(&this->data, 0x28u);
  std::list<SearchBackInfo>::clear(&this->lstTodayInfo);
  for ( i = 0; i <= 2; ++i )
    std::list<SearchBackRecord>::clear(&this->vSeachBackRecord[i]);
  std::string::operator=(&this->OnlimeReward, byte_8CFE00);
}


#####################################
void __cdecl DailyActivityData::SaveToSqlString(
        DailyActivityData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  const char *v4; // r13
  const char *v5; // r12
  int32_t sign_record; // r15d
  const char *v7; // rbx
  int32_t v8; // r14d
  const char *v9; // rax
  int32_t nParam; // r14d
  int32_t nTimes; // r13d
  int32_t v12; // r12d
  int32_t v13; // ebx
  int nSubType; // r15d
  const SearchBackInfo *v15; // rax
  int32_t v16; // r14d
  int32_t v17; // r13d
  int32_t v18; // r12d
  int32_t v19; // ebx
  const SearchBackRecord *v20; // rax
  int32_t refresh_time; // [rsp+3Ch] [rbp-144h]
  std::_List_const_iterator<SearchBackRecord> iter_0; // [rsp+60h] [rbp-120h] BYREF
  std::_List_const_iterator<SearchBackInfo> iter; // [rsp+70h] [rbp-110h] BYREF
  DailyActivityData v26; // [rsp+80h] [rbp-100h] BYREF
  char v27; // [rsp+FFh] [rbp-81h] BYREF
  std::string __x; // [rsp+100h] [rbp-80h] BYREF
  char v29; // [rsp+10Fh] [rbp-71h] BYREF
  std::_List_iterator<SearchBackRecord> v30; // [rsp+110h] [rbp-70h] BYREF
  std::_List_const_iterator<SearchBackRecord> v31; // [rsp+120h] [rbp-60h] BYREF
  std::_List_iterator<SearchBackRecord> v32; // [rsp+130h] [rbp-50h] BYREF
  std::string v33; // [rsp+140h] [rbp-40h] BYREF
  char v34; // [rsp+14Bh] [rbp-35h] BYREF
  int32_t i; // [rsp+14Ch] [rbp-34h]

  bzero(szSQL, 0x1000u);
  v4 = (const char *)std::string::c_str(&this->OnlimeReward);
  refresh_time = this->data.refresh_time;
  DailyActivityData::GetSignRewardString(&v26);
  v5 = (const char *)std::string::c_str((std::string *)&v26);
  sign_record = this->data.sign_record;
  v7 = (const char *)std::string::c_str(&this->OnlimeReward);
  v8 = this->data.refresh_time;
  DailyActivityData::GetSignRewardString((DailyActivityData *const)&v26.data.sign_reward);
  v9 = (const char *)std::string::c_str((std::string *)&v26.data.sign_reward);
  snprintf(
    (char *)szSQL,
    0xFFFu,
    "INSERT INTO `mem_chr_sign_info` (`cid`, `sign_record`, `sign_reward`, `refresh_time`,`online_reward`) VALUES (%lld, "
    "%d, '%s', %d,'%s') ON DUPLICATE KEY UPDATE `sign_record` = %d, `sign_reward` = '%s', `refresh_time` = %d,`online_reward`='%s'",
    nCid,
    this->data.sign_record,
    v9,
    v8,
    v7,
    sign_record,
    v5,
    refresh_time,
    v4);
  std::string::~string(&v26.data.sign_reward);
  std::string::~string(&v26);
  std::allocator<char>::allocator((char *)&v26.data.refresh_time + 7);
  std::string::string(
    &v26.data.sign_reward._M_impl._M_end_of_storage,
    (char *)szSQL,
    (char *)&v26.data.refresh_time + 7);
  std::list<std::string>::push_back(sqls, (const std::string *const)&v26.data.sign_reward._M_impl._M_end_of_storage);
  std::string::~string(&v26.data.sign_reward._M_impl._M_end_of_storage);
  std::allocator<char>::~allocator((char *)&v26.data.refresh_time + 7);
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_search_back_info` WHERE `cid`=%lld", nCid);
  std::allocator<char>::allocator((char *)&v26.lstTodayInfo._M_impl._M_node._M_prev + 7);
  std::string::string(&v26.lstTodayInfo, (char *)szSQL, (char *)&v26.lstTodayInfo._M_impl._M_node._M_prev + 7);
  std::list<std::string>::push_back(sqls, (const std::string *const)&v26.lstTodayInfo);
  std::string::~string(&v26.lstTodayInfo);
  std::allocator<char>::~allocator((char *)&v26.lstTodayInfo._M_impl._M_node._M_prev + 7);
  bzero(szSQL, 0x1000u);
  v26.vSeachBackRecord[0]._M_impl._M_node._M_next = std::list<SearchBackInfo>::begin(&this->lstTodayInfo)._M_node;
  std::_List_const_iterator<SearchBackInfo>::_List_const_iterator(
    &iter,
    (const std::_List_iterator<SearchBackInfo> *const)v26.vSeachBackRecord);
  while ( 1 )
  {
    v26.vSeachBackRecord[2]._M_impl._M_node._M_next = std::list<SearchBackInfo>::end(&this->lstTodayInfo)._M_node;
    std::_List_const_iterator<SearchBackInfo>::_List_const_iterator(
      (std::_List_const_iterator<SearchBackInfo> *const)&v26.vSeachBackRecord[1],
      (const std::_List_iterator<SearchBackInfo> *const)&v26.vSeachBackRecord[2]);
    if ( !std::_List_const_iterator<SearchBackInfo>::operator!=(
            &iter,
            (const std::_List_const_iterator<SearchBackInfo> *const)&v26.vSeachBackRecord[1]) )
      break;
    nParam = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nParam;
    nTimes = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nTimes;
    v12 = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nParam;
    v13 = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nTimes;
    nSubType = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nSubType;
    v15 = std::_List_const_iterator<SearchBackInfo>::operator->(&iter);
    snprintf(
      (char *)szSQL,
      0xFFFu,
      "INSERT INTO `mem_chr_search_back_info` (`cid`, `type`, `sub_type`, `times`, `param`) VALUES (%lld, %d, %d, %d, %d)"
      "  ON DUPLICATE KEY UPDATE `times`=%d, `param`=%d ",
      nCid,
      v15->nType,
      nSubType,
      v13,
      v12,
      nTimes,
      nParam);
    std::allocator<char>::allocator(&v27);
    std::string::string(&v26.OnlimeReward, (char *)szSQL, &v27);
    std::list<std::string>::push_back(sqls, &v26.OnlimeReward);
    std::string::~string(&v26.OnlimeReward);
    std::allocator<char>::~allocator(&v27);
    std::_List_const_iterator<SearchBackInfo>::operator++(&iter);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "DELETE FROM `mem_chr_search_back_record` WHERE `cid`=%lld", nCid);
  std::allocator<char>::allocator(&v29);
  std::string::string(&__x, (char *)szSQL, &v29);
  std::list<std::string>::push_back(sqls, &__x);
  std::string::~string(&__x);
  std::allocator<char>::~allocator(&v29);
  bzero(szSQL, 0x1000u);
  for ( i = 0; i <= 2; ++i )
  {
    v30._M_node = std::list<SearchBackRecord>::begin(&this->vSeachBackRecord[i])._M_node;
    std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(&iter_0, &v30);
    while ( 1 )
    {
      v32._M_node = std::list<SearchBackRecord>::end(&this->vSeachBackRecord[i])._M_node;
      std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(&v31, &v32);
      if ( !std::_List_const_iterator<SearchBackRecord>::operator!=(&iter_0, &v31) )
        break;
      v16 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nParam;
      v17 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nTimes;
      v18 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nParam;
      v19 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nTimes;
      v20 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0);
      snprintf(
        (char *)szSQL,
        0xFFFu,
        "INSERT INTO `mem_chr_search_back_record` (`cid`, `day`, `id`, `times`, `param`) VALUES (%lld, %d, %d, %d, %d)  O"
        "N DUPLICATE KEY UPDATE `times`=%d, `param`=%d ",
        nCid,
        i,
        v20->nId,
        v19,
        v18,
        v17,
        v16);
      std::allocator<char>::allocator(&v34);
      std::string::string(&v33, (char *)szSQL, &v34);
      std::list<std::string>::push_back(sqls, &v33);
      std::string::~string(&v33);
      std::allocator<char>::~allocator(&v34);
      std::_List_const_iterator<SearchBackRecord>::operator++(&iter_0);
    }
  }
}


#####################################
bool __cdecl DailyActivityData::LoadFromDB(
        DailyActivityData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  Answer::MySqlQuery *v6; // rax
  const char *StringValue; // rax
  const char *v8; // rax
  Answer::MySqlQuery *v9; // rax
  Answer::MySqlQuery *v10; // rax
  SearchBackRecord record; // [rsp+30h] [rbp-60h] BYREF
  SearchBackInfo info; // [rsp+40h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+50h] [rbp-40h] BYREF
  std::string p_RewardString; // [rsp+70h] [rbp-20h] BYREF
  char v18; // [rsp+7Eh] [rbp-12h] BYREF
  int8_t nDay; // [rsp+7Fh] [rbp-11h]

  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_sign_info` WHERE `cid`=%lld", nCid);
  v6 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::MySqlQuery(&result, v6);
  if ( !Answer::MySqlQuery::eof(&result) )
  {
    this->data.sign_record = Answer::MySqlQuery::getIntValue(&result, "sign_record", 0);
    std::allocator<char>::allocator(&v18);
    StringValue = Answer::MySqlQuery::getStringValue(&result, "sign_reward", byte_8CFE00);
    std::string::string(&p_RewardString, StringValue, &v18);
    DailyActivityData::InitSignRewardInfo(this, &p_RewardString);
    std::string::~string(&p_RewardString);
    std::allocator<char>::~allocator(&v18);
    this->data.refresh_time = Answer::MySqlQuery::getIntValue(&result, "refresh_time", 0);
    v8 = Answer::MySqlQuery::getStringValue(&result, "online_reward", byte_8CFE00);
    std::string::operator=(&this->OnlimeReward, v8);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_search_back_info` WHERE `cid`=%lld", nCid);
  v9 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::operator=(&result, v9);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    *(_QWORD *)&info.nType = 0;
    info.nParam = 0;
    info.nType = Answer::MySqlQuery::getIntValue(&result, "type", 0);
    info.nSubType = Answer::MySqlQuery::getIntValue(&result, "sub_type", 0);
    info.nTimes = Answer::MySqlQuery::getIntValue(&result, "times", 0);
    info.nParam = Answer::MySqlQuery::getIntValue(&result, "param", 0);
    std::list<SearchBackInfo>::push_back(&this->lstTodayInfo, &info);
    Answer::MySqlQuery::nextRow(&result);
  }
  bzero(szSQL, 0x1000u);
  snprintf((char *)szSQL, 0xFFFu, "SELECT * FROM `mem_chr_search_back_record` WHERE `cid`=%lld", nCid);
  v10 = Answer::MySqlDBGuard::query(db, (const char *)szSQL);
  Answer::MySqlQuery::operator=(&result, v10);
  while ( !Answer::MySqlQuery::eof(&result) )
  {
    *(_QWORD *)&record.nId = 0;
    record.nParam = 0;
    nDay = Answer::MySqlQuery::getIntValue(&result, "day", 0);
    record.nId = Answer::MySqlQuery::getIntValue(&result, "id", 0);
    record.nTimes = Answer::MySqlQuery::getIntValue(&result, "times", 0);
    record.nParam = Answer::MySqlQuery::getIntValue(&result, "param", 0);
    if ( (unsigned __int8)nDay <= 2u )
      std::list<SearchBackRecord>::push_back(&this->vSeachBackRecord[nDay], &record);
    Answer::MySqlQuery::nextRow(&result);
  }
  Answer::MySqlQuery::~MySqlQuery(&result);
  return 1;
}


#####################################
void __cdecl DailyActivityData::PackageData(DailyActivityData *const this, Answer::NetPacket *packet)
{
  int32_t v2; // edx
  int8_t nType; // dl
  int8_t nSubType; // dl
  int32_t nTimes; // edx
  int32_t nParam; // edx
  int32_t v7; // edx
  int32_t nId; // edx
  int32_t v9; // edx
  int32_t v10; // edx
  std::_List_const_iterator<SearchBackRecord> iter_0; // [rsp+10h] [rbp-A0h] BYREF
  std::_List_const_iterator<SearchBackInfo> iter; // [rsp+20h] [rbp-90h] BYREF
  DailyActivityData v13; // [rsp+30h] [rbp-80h] BYREF

  Answer::NetPacket::writeInt32(packet, this->data.sign_record);
  DailyActivityData::GetSignRewardString(&v13);
  Answer::NetPacket::writeUTF8(packet, (const std::string *const)&v13);
  std::string::~string(&v13);
  Answer::NetPacket::writeInt32(packet, this->data.refresh_time);
  v2 = std::list<SearchBackInfo>::size(&this->lstTodayInfo);
  Answer::NetPacket::writeInt32(packet, v2);
  v13.data.sign_reward._M_impl._M_start = (char *)std::list<SearchBackInfo>::begin(&this->lstTodayInfo)._M_node;
  std::_List_const_iterator<SearchBackInfo>::_List_const_iterator(
    &iter,
    (const std::_List_iterator<SearchBackInfo> *const)&v13.data.sign_reward);
  while ( 1 )
  {
    v13.lstTodayInfo._M_impl._M_node._M_next = std::list<SearchBackInfo>::end(&this->lstTodayInfo)._M_node;
    std::_List_const_iterator<SearchBackInfo>::_List_const_iterator(
      (std::_List_const_iterator<SearchBackInfo> *const)&v13.data.sign_reward._M_impl._M_end_of_storage,
      (const std::_List_iterator<SearchBackInfo> *const)&v13.lstTodayInfo);
    if ( !std::_List_const_iterator<SearchBackInfo>::operator!=(
            &iter,
            (const std::_List_const_iterator<SearchBackInfo> *const)&v13.data.sign_reward._M_impl._M_end_of_storage) )
      break;
    nType = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nType;
    Answer::NetPacket::writeInt8(packet, nType);
    nSubType = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nSubType;
    Answer::NetPacket::writeInt8(packet, nSubType);
    nTimes = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nTimes;
    Answer::NetPacket::writeInt32(packet, nTimes);
    nParam = std::_List_const_iterator<SearchBackInfo>::operator->(&iter)->nParam;
    Answer::NetPacket::writeInt32(packet, nParam);
    std::_List_const_iterator<SearchBackInfo>::operator++(&iter);
  }
  HIDWORD(v13.vSeachBackRecord[2]._M_impl._M_node._M_prev) = 0;
  while ( SHIDWORD(v13.vSeachBackRecord[2]._M_impl._M_node._M_prev) <= 2 )
  {
    v7 = std::list<SearchBackRecord>::size(&this->vSeachBackRecord[SHIDWORD(v13.vSeachBackRecord[2]._M_impl._M_node._M_prev)]);
    Answer::NetPacket::writeInt32(packet, v7);
    v13.vSeachBackRecord[0]._M_impl._M_node._M_next = std::list<SearchBackRecord>::begin(&this->vSeachBackRecord[SHIDWORD(v13.vSeachBackRecord[2]._M_impl._M_node._M_prev)])._M_node;
    std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(
      &iter_0,
      (const std::_List_iterator<SearchBackRecord> *const)v13.vSeachBackRecord);
    while ( 1 )
    {
      v13.vSeachBackRecord[2]._M_impl._M_node._M_next = std::list<SearchBackRecord>::end(&this->vSeachBackRecord[SHIDWORD(v13.vSeachBackRecord[2]._M_impl._M_node._M_prev)])._M_node;
      std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(
        (std::_List_const_iterator<SearchBackRecord> *const)&v13.vSeachBackRecord[1],
        (const std::_List_iterator<SearchBackRecord> *const)&v13.vSeachBackRecord[2]);
      if ( !std::_List_const_iterator<SearchBackRecord>::operator!=(
              &iter_0,
              (const std::_List_const_iterator<SearchBackRecord> *const)&v13.vSeachBackRecord[1]) )
        break;
      nId = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nId;
      Answer::NetPacket::writeInt32(packet, nId);
      v9 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nTimes;
      Answer::NetPacket::writeInt32(packet, v9);
      v10 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter_0)->nParam;
      Answer::NetPacket::writeInt32(packet, v10);
      std::_List_const_iterator<SearchBackRecord>::operator++(&iter_0);
    }
    ++HIDWORD(v13.vSeachBackRecord[2]._M_impl._M_node._M_prev);
  }
  Answer::NetPacket::writeUTF8(packet, &this->OnlimeReward);
}


#####################################
void __cdecl DailyActivityData::UnPackageData(
        DailyActivityData *const this,
        Answer::NetPacket *inPacket,
        CharId_t nCid)
{
  SearchBackRecord record; // [rsp+20h] [rbp-60h] BYREF
  SearchBackInfo info; // [rsp+30h] [rbp-50h] BYREF
  Answer::NetPacket v5; // [rsp+40h] [rbp-40h] BYREF

  this->data.sign_record = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8(&v5, (bool)inPacket);
  DailyActivityData::InitSignRewardInfo(this, (std::string *)&v5);
  std::string::~string(&v5);
  this->data.refresh_time = Answer::NetPacket::readInt32(inPacket);
  *(_DWORD *)&v5.m_proc = Answer::NetPacket::readInt32(inPacket);
  for ( v5.m_size = 0; (int)v5.m_size < *(int *)&v5.m_proc; ++v5.m_size )
  {
    *(_QWORD *)&info.nType = 0;
    info.nParam = 0;
    info.nType = Answer::NetPacket::readInt8(inPacket);
    info.nSubType = Answer::NetPacket::readInt8(inPacket);
    info.nTimes = Answer::NetPacket::readInt32(inPacket);
    info.nParam = Answer::NetPacket::readInt32(inPacket);
    std::list<SearchBackInfo>::push_back(&this->lstTodayInfo, &info);
  }
  *(&v5.m_size + 1) = 0;
  while ( *((int *)&v5.m_size + 1) <= 2 )
  {
    for ( v5.m_refCount = (unsigned int)Answer::NetPacket::readInt32(inPacket);
          SHIDWORD(v5.m_refCount) < SLODWORD(v5.m_refCount);
          ++HIDWORD(v5.m_refCount) )
    {
      *(_QWORD *)&record.nId = 0;
      record.nParam = 0;
      record.nId = Answer::NetPacket::readInt32(inPacket);
      record.nTimes = Answer::NetPacket::readInt32(inPacket);
      record.nParam = Answer::NetPacket::readInt32(inPacket);
      std::list<SearchBackRecord>::push_back(&this->vSeachBackRecord[*((int *)&v5.m_size + 1)], &record);
    }
    ++*(&v5.m_size + 1);
  }
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&v5.m_wOffset, (bool)inPacket);
  std::string::operator=(&this->OnlimeReward, &v5.m_wOffset);
  std::string::~string(&v5.m_wOffset);
}


#####################################
std::string __cdecl DailyActivityData::GetSignRewardString(DailyActivityData *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  char *v3; // rax
  __int64 v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  __int64 v7; // [rsp+20h] [rbp-190h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > it; // [rsp+180h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > __rhs; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
  for ( it._M_current = std::vector<signed char>::begin((std::vector<signed char> *const)(v1 + 16))._M_current;
        ;
        __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<signed char>::end((std::vector<signed char> *const)(v1 + 16))._M_current;
    if ( !__gnu_cxx::operator!=<signed char *,std::vector<signed char>>(&it, &__rhs) )
      break;
    v3 = __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator*(&it);
    v4 = std::ostream::operator<<(&v7, (unsigned int)*v3);
    std::operator<<<std::char_traits<char>>(v4, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  return (std::string)this;
}


#####################################
void __cdecl DailyActivityData::InitSignRewardInfo(DailyActivityData *const this, std::string *p_RewardString)
{
  std::string *v2; // rax
  const char *v3; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+10h] [rbp-60h] BYREF
  StringVector RewardVector; // [rsp+20h] [rbp-50h] BYREF
  std::string delims; // [rsp+40h] [rbp-30h] BYREF
  char v7; // [rsp+4Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+50h] [rbp-20h] BYREF
  char __x[17]; // [rsp+5Fh] [rbp-11h] BYREF

  if ( !std::operator==<char>(p_RewardString, byte_8CFE00) )
  {
    std::allocator<char>::allocator(&v7);
    std::string::string(&delims, "|", &v7);
    Answer::StringUtility::split(&RewardVector, p_RewardString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v7);
    for ( it._M_current = std::vector<std::string>::begin(&RewardVector)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&RewardVector)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      v3 = (const char *)std::string::c_str(v2);
      __x[0] = atoi(v3);
      std::vector<signed char>::push_back(&this->data.sign_reward, __x);
    }
    std::vector<std::string>::~vector(&RewardVector);
  }
}


