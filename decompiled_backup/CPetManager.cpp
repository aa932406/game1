// Decompiled methods for class: CPetManager
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CPetManager::~CPetManager(CPetManager *const this)
{
  CPetManager::~CPetManager(this);
  operator delete(this);
}


#####################################
int32_t __cdecl CPetManager::GetPetRankIndex(CPetManager *const this, PetId_t nPetId)
{
  int32_t second; // ebx
  PetId_t nPetIda; // [rsp+0h] [rbp-50h] BYREF
  CPetManager *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,short int> > findIter; // [rsp+10h] [rbp-40h] BYREF
  Answer::RwLockWrGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,short int> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nPetIda = nPetId;
  Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwLock);
  findIter._M_node = std::map<long,short>::find(&this->m_mPetRank, &nPetIda)._M_node;
  __x._M_node = std::map<long,short>::end(&thisa->m_mPetRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,short>>::operator!=(&findIter, &__x) )
    second = std::_Rb_tree_iterator<std::pair<long const,short>>::operator->(&findIter)->second;
  else
    second = 0;
  Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
  return second;
}


#####################################
void __cdecl CPetManager::getPetIdFromDB(
        CPetManager *const this,
        int32_t nServerId,
        int64_t *const nNextId,
        int64_t *const nMaxId)
{
  Answer::DBPool *v4; // rax
  GameService *v5; // rax
  Answer::MySqlQuery *v6; // rax
  CTimer *v7; // rax
  int32_t Now; // eax
  Answer::MySqlQuery *v9; // rax
  CTimer *v10; // rax
  int32_t v11; // eax
  char szSql[4096]; // [rsp+20h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1020h] [rbp-80h] BYREF
  Answer::MySqlQuery result_0; // [rsp+1050h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+1070h] [rbp-30h] BYREF
  int32_t nNewPetId; // [rsp+108Ch] [rbp-14h]

  v4 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v4);
  v5 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v5) == 9 )
  {
    v6 = Answer::MySqlDBGuard::query(&db, "call NewPetId(@OutPetId)");
    Answer::MySqlQuery::MySqlQuery(&result, v6);
    if ( !Answer::MySqlQuery::eof(&result) )
    {
      *nNextId = Answer::MySqlQuery::getInt64Value(&result, "OutPetId", 0);
      *nMaxId = *nNextId + 20;
    }
    else
    {
      v7 = Answer::Singleton<CTimer>::instance();
      Now = CTimer::GetNow(v7);
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "CPetManager::getPetId() FAIL! time=%d\n", Now);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
  }
  else
  {
    memset(szSql, 0, sizeof(szSql));
    snprintf(szSql, 0xFFFu, "call NewPetId(%d,@OutPetId)", nServerId);
    v9 = Answer::MySqlDBGuard::query(&db, szSql);
    Answer::MySqlQuery::MySqlQuery(&result_0, v9);
    if ( !Answer::MySqlQuery::eof(&result_0) )
    {
      nNewPetId = Answer::MySqlQuery::getIntValue(&result_0, 0, 0);
      *nNextId = nNewPetId + ((__int64)nServerId << 32);
      *nMaxId = *nNextId + 20;
    }
    else
    {
      v10 = Answer::Singleton<CTimer>::instance();
      v11 = CTimer::GetNow(v10);
      Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "CPetManager::getPetId() FAIL! time=%d\n", v11);
    }
    Answer::MySqlQuery::~MySqlQuery(&result_0);
  }
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


#####################################
void __cdecl CPetManager::OnUpdatePetRank(CPetManager *const this, Answer::NetPacket *inPacket)
{
  __int16 *v2; // rax
  Answer::RwLockWrGuard lock; // [rsp+10h] [rbp-30h] BYREF
  PetId_t nPetId; // [rsp+18h] [rbp-28h] BYREF
  int32_t nCount; // [rsp+20h] [rbp-20h]
  int32_t i; // [rsp+24h] [rbp-1Ch]
  int16_t nIndex; // [rsp+2Ah] [rbp-16h]
  int32_t nOldIndex; // [rsp+2Ch] [rbp-14h]

  if ( inPacket )
  {
    nCount = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nCount; ++i )
    {
      nPetId = Answer::NetPacket::readInt64(inPacket);
      nIndex = Answer::NetPacket::readInt16(inPacket);
      nOldIndex = CPetManager::GetPetRankIndex(this, nPetId);
      Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwLock);
      v2 = std::map<long,short>::operator[](&this->m_mPetRank, &nPetId);
      *v2 = nIndex;
      Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
    }
  }
}


#####################################
void __cdecl CPetManager::OnInitPetRank(CPetManager *const this, Answer::NetPacket *inPacket)
{
  __int16 *v2; // rax
  Answer::RwLockWrGuard lock; // [rsp+10h] [rbp-30h] BYREF
  PetId_t nPetId; // [rsp+18h] [rbp-28h] BYREF
  int32_t nCount; // [rsp+24h] [rbp-1Ch]
  int32_t i; // [rsp+28h] [rbp-18h]
  int16_t nIndex; // [rsp+2Eh] [rbp-12h]

  if ( inPacket )
  {
    nCount = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < nCount; ++i )
    {
      nPetId = Answer::NetPacket::readInt64(inPacket);
      nIndex = Answer::NetPacket::readInt16(inPacket);
      Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_rwLock);
      v2 = std::map<long,short>::operator[](&this->m_mPetRank, &nPetId);
      *v2 = nIndex;
      Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
    }
  }
}


