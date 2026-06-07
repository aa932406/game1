// Decompiled methods for class: RandomBuff
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl RandomBuff::~RandomBuff(RandomBuff *const this)
{
  RandomBuff::~RandomBuff(this);
  operator delete(this);
}


#####################################
int32_t __cdecl RandomBuff::effect(
        RandomBuff *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  Map *Map; // rax
  CActivityMap *v5; // rax
  CActivity *Activity; // rax
  CPeerlessWar *v7; // rax
  int32_t m_nSumRate; // ebx
  Answer::Random *v10; // rax
  RandomBuff::randBuff *v11; // rax
  RandomBuff::randBuff *v13; // rax
  std::_List_iterator<RandomBuff::randBuff> iter; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<RandomBuff::randBuff> __x; // [rsp+30h] [rbp-30h] BYREF
  CActivityMap *pMap; // [rsp+38h] [rbp-28h]
  CPeerlessWar *pAct; // [rsp+40h] [rbp-20h]
  int32_t nRand; // [rsp+4Ch] [rbp-14h]

  Map = StaticObj::getMap(launcher);
  if ( Map )
    v5 = (CActivityMap *)__dynamic_cast(
                           Map,
                           (const struct __class_type_info *)&`typeinfo for'Map,
                           (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                           0);
  else
    v5 = 0;
  pMap = v5;
  if ( v5 )
  {
    Activity = CActivityMap::GetActivity(pMap);
    v7 = Activity
       ? (CPeerlessWar *)__dynamic_cast(
                           Activity,
                           (const struct __class_type_info *)&`typeinfo for'CActivity,
                           (const struct __class_type_info *)&`typeinfo for'CPeerlessWar,
                           0)
       : 0LL;
    pAct = v7;
    if ( v7 && CActivity::IsRuning(pAct) )
    {
      m_nSumRate = this->m_nSumRate;
      v10 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v10, 0, m_nSumRate);
      for ( iter._M_node = std::list<RandomBuff::randBuff>::begin(&this->m_buffs)._M_node;
            ;
            std::_List_iterator<RandomBuff::randBuff>::operator++(&iter) )
      {
        __x._M_node = std::list<RandomBuff::randBuff>::end(&this->m_buffs)._M_node;
        if ( !std::_List_iterator<RandomBuff::randBuff>::operator!=(&iter, &__x) )
          break;
        v11 = std::_List_iterator<RandomBuff::randBuff>::operator->(&iter);
        if ( v11->nRate >= nRand && std::_List_iterator<RandomBuff::randBuff>::operator->(&iter)->m_cfgBuff )
        {
          v13 = std::_List_iterator<RandomBuff::randBuff>::operator->(&iter);
          CActivity::addActivityBuff(pAct, launcher, v13->m_cfgBuff->id, 1);
          return 0;
        }
      }
    }
  }
  return 10002;
}


#####################################
bool __cdecl RandomBuff::parseEffect(RandomBuff *const this, int32_t id, const std::string *const strEffect)
{
  bool v3; // r12
  std::string *v4; // rbx
  std::string *v5; // rax
  const char *v6; // rax
  int32_t v7; // ebx
  CfgData *v8; // rax
  const char *v9; // rax
  int v10; // ebx
  int32_t m_nSumRate; // ebx
  std::string *v12; // rax
  const char *v13; // rax
  const char *v14; // rax
  RandomBuff::randBuff buff; // [rsp+20h] [rbp-A0h] BYREF
  StringVector strBuff; // [rsp+30h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-70h] BYREF
  StringVector strParam; // [rsp+60h] [rbp-60h] BYREF
  std::string delims; // [rsp+80h] [rbp-40h] BYREF
  char v22; // [rsp+8Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-30h] BYREF
  std::string v24; // [rsp+A0h] [rbp-20h] BYREF
  _BYTE v25[17]; // [rsp+AFh] [rbp-11h] BYREF

  this->m_nSumRate = 0;
  std::allocator<char>::allocator(&v22);
  std::string::string(&delims, "|");
  Answer::StringUtility::split(&strParam, strEffect, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v22);
  for ( it._M_current = std::vector<std::string>::begin(&strParam)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<std::string>::end(&strParam)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
      break;
    std::allocator<char>::allocator(v25);
    std::string::string(&v24, ":");
    v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
    Answer::StringUtility::split(&strBuff, v4, &v24, 0);
    std::string::~string(&v24);
    std::allocator<char>::~allocator(v25);
    if ( std::vector<std::string>::size(&strBuff) == 2 )
    {
      buff.m_cfgBuff = 0;
      *(_QWORD *)&buff.nRate = 0;
      v5 = std::vector<std::string>::operator[](&strBuff, 0);
      v6 = (const char *)std::string::c_str(v5);
      v7 = atoi(v6);
      v8 = Answer::Singleton<CfgData>::instance();
      buff.m_cfgBuff = CfgData::getBuff(v8, v7);
      if ( buff.m_cfgBuff )
      {
        m_nSumRate = this->m_nSumRate;
        v12 = std::vector<std::string>::operator[](&strBuff, 1u);
        v13 = (const char *)std::string::c_str(v12);
        this->m_nSumRate = m_nSumRate + atoi(v13);
        buff.nRate = this->m_nSumRate;
        std::list<RandomBuff::randBuff>::push_back(&this->m_buffs, &buff);
        v10 = 1;
      }
      else
      {
        v9 = (const char *)std::string::c_str((std::string *)strEffect);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "RandomBuff::parseEffect() buff not find with id=%d, str = %s\n",
          id,
          v9);
        v3 = 0;
        v10 = 0;
      }
    }
    else
    {
      v14 = (const char *)std::string::c_str((std::string *)strEffect);
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "RandomBuff::parseEffect() wrong format with id=%d, str = %s\n",
        id,
        v14);
      v3 = 0;
      v10 = 0;
    }
    std::vector<std::string>::~vector(&strBuff);
    if ( !v10 )
      goto LABEL_11;
  }
  v3 = 1;
LABEL_11:
  std::vector<std::string>::~vector(&strParam);
  return v3;
}


