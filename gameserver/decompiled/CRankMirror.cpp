// Decompiled methods for class: CRankMirror
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CRankMirror::~CRankMirror(CRankMirror *const this)
{
  CRankMirror::~CRankMirror(this);
  operator delete(this);
}


#####################################
int32_t __cdecl CRankMirror::GetBattleIndex(CRankMirror *const this, CharId_t nCharId)
{
  int32_t nBattleIndex; // ebx
  CharId_t nCharIda; // [rsp+0h] [rbp-50h] BYREF
  CRankMirror *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
    nBattleIndex = std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nBattleIndex;
  else
    nBattleIndex = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return nBattleIndex;
}


#####################################
int32_t __cdecl CRankMirror::GetLevelIndex(CRankMirror *const this, CharId_t nCharId)
{
  int32_t nLevelIndex; // ebx
  CharId_t nCharIda; // [rsp+0h] [rbp-50h] BYREF
  CRankMirror *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
    nLevelIndex = std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nLevelIndex;
  else
    nLevelIndex = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return nLevelIndex;
}


#####################################
bool __cdecl CRankMirror::IsJobBattleFirst(CRankMirror *const this, CharId_t nCharId)
{
  bool v2; // bl
  CharId_t nCharIda; // [rsp+0h] [rbp-50h] BYREF
  CRankMirror *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  v2 = std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x)
    && std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nJobBattleFirst > 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return v2;
}


#####################################
int32_t __cdecl CRankMirror::GetWeiWangIndex(CRankMirror *const this, CharId_t nCharId)
{
  int32_t nWeiWangIndex; // ebx
  CharId_t nCharIda; // [rsp+0h] [rbp-50h] BYREF
  CRankMirror *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
    nWeiWangIndex = std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nWeiWangIndex;
  else
    nWeiWangIndex = 0;
  Answer::MutexGuard::~MutexGuard(&lock);
  return nWeiWangIndex;
}


#####################################
void __cdecl CRankMirror::OnSocialUpdateRank(CRankMirror *const this, Answer::NetPacket *inPacket)
{
  int Int8; // eax
  int8_t v3; // cl
  int32_t nSize; // [rsp+18h] [rbp-58h]
  int32_t i; // [rsp+1Ch] [rbp-54h]
  int64_t nCharId; // [rsp+20h] [rbp-50h]
  int32_t nIndex; // [rsp+28h] [rbp-48h]
  int32_t nSize_0; // [rsp+30h] [rbp-40h]
  int32_t i_0; // [rsp+34h] [rbp-3Ch]
  int64_t nCharId_0; // [rsp+38h] [rbp-38h]
  int32_t nIndex_0; // [rsp+44h] [rbp-2Ch]
  int32_t nSize_1; // [rsp+48h] [rbp-28h]
  int32_t i_1; // [rsp+4Ch] [rbp-24h]
  int64_t nCharId_1; // [rsp+50h] [rbp-20h]
  int32_t nIndex_1; // [rsp+5Ch] [rbp-14h]

  if ( inPacket )
  {
    Int8 = Answer::NetPacket::readInt8(inPacket);
    if ( (char)Int8 == 2 )
    {
      CRankMirror::resetLevelRank(this);
      nSize_0 = Answer::NetPacket::readInt16(inPacket);
      for ( i_0 = 0; i_0 < nSize_0; ++i_0 )
      {
        nCharId_0 = Answer::NetPacket::readInt64(inPacket);
        nIndex_0 = Answer::NetPacket::readInt8(inPacket);
        CRankMirror::setLevelRank(this, nCharId_0, nIndex_0);
      }
    }
    else if ( Int8 == 4 )
    {
      CRankMirror::resetWeiWangRank(this);
      nSize_1 = Answer::NetPacket::readInt16(inPacket);
      for ( i_1 = 0; i_1 < nSize_1; ++i_1 )
      {
        nCharId_1 = Answer::NetPacket::readInt64(inPacket);
        nIndex_1 = Answer::NetPacket::readInt8(inPacket);
        CRankMirror::setWeiWangRank(this, nCharId_1, nIndex_1);
      }
    }
    else if ( Int8 == 1 )
    {
      this->m_nLastRefreshTime = Answer::NetPacket::readInt32(inPacket);
      CRankMirror::resetBattleRank(this);
      nSize = Answer::NetPacket::readInt16(inPacket);
      for ( i = 0; i < nSize; ++i )
      {
        nCharId = Answer::NetPacket::readInt64(inPacket);
        nIndex = Answer::NetPacket::readInt8(inPacket);
        v3 = Answer::NetPacket::readInt8(inPacket);
        CRankMirror::setBattleRank(this, nCharId, nIndex, v3);
      }
    }
  }
}


#####################################
void __cdecl CRankMirror::resetBattleRank(CRankMirror *const this)
{
  CharId_t nCharId; // rbx
  GameService *v2; // rax
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  bzero(this->m_vBattleRank, 0x328u);
  for ( iter._M_node = std::map<long,CRankMirror::PlayerRankData>::begin(&this->m_mPlayerRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&this->m_mPlayerRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
      break;
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nBattleIndex = 0;
    if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nJobBattleFirst > 0 )
    {
      nCharId = std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nCharId;
      v2 = Answer::Singleton<GameService>::instance();
      GameService::onRemoveTitle(v2, nCharId, 3);
      std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nJobBattleFirst = 0;
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CRankMirror::resetLevelRank(CRankMirror *const this)
{
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  bzero(this->m_vLevelRank, 0x328u);
  for ( iter._M_node = std::map<long,CRankMirror::PlayerRankData>::begin(&this->m_mPlayerRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&this->m_mPlayerRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
      break;
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nLevelIndex = 0;
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CRankMirror::resetWeiWangRank(CRankMirror *const this)
{
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+30h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  bzero(this->m_vWeiWangRank, 0x328u);
  for ( iter._M_node = std::map<long,CRankMirror::PlayerRankData>::begin(&this->m_mPlayerRank)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator++(&iter) )
  {
    __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&this->m_mPlayerRank)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
      break;
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nWeiWangIndex = 0;
  }
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CRankMirror::setBattleRank(CRankMirror *const this, CharId_t nCharId, int32_t nIndex, int8_t nJobFrist)
{
  CharId_t v4; // rbx
  GameService *v5; // rax
  CharId_t nCharIda; // [rsp+20h] [rbp-B0h] BYREF
  CRankMirror *thisa; // [rsp+28h] [rbp-A8h]
  CRankMirror::PlayerRankData data; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+50h] [rbp-80h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+70h] [rbp-60h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> >,bool> v14; // [rsp+80h] [rbp-50h]
  std::pair<const long int,CRankMirror::PlayerRankData> v15; // [rsp+90h] [rbp-40h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
  {
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nBattleIndex = nIndex;
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nJobBattleFirst = nJobFrist;
  }
  else
  {
    data.nLevelIndex = 0;
    *(_QWORD *)&data.nGuanWeiIndex = 0;
    data.nCharId = nCharIda;
    data.nBattleIndex = nIndex;
    *(_QWORD *)&data.nJobBattleFirst = (unsigned __int8)nJobFrist;
    std::pair<long const,CRankMirror::PlayerRankData>::pair(&v15, &nCharIda, &data);
    v14 = std::map<long,CRankMirror::PlayerRankData>::insert(&thisa->m_mPlayerRank, &v15);
  }
  if ( nJobFrist > 0 )
  {
    v4 = nCharIda;
    v5 = Answer::Singleton<GameService>::instance();
    GameService::onCheckTitle(v5, v4, 3, nJobFrist);
  }
  if ( nIndex > 0 && nIndex <= 100 )
    thisa->m_vBattleRank[nIndex] = nCharIda;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CRankMirror::setLevelRank(CRankMirror *const this, CharId_t nCharId, int32_t nIndex)
{
  CharId_t nCharIda; // [rsp+20h] [rbp-B0h] BYREF
  CRankMirror *thisa; // [rsp+28h] [rbp-A8h]
  CRankMirror::PlayerRankData data; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+50h] [rbp-80h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+70h] [rbp-60h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> >,bool> v10; // [rsp+80h] [rbp-50h]
  std::pair<const long int,CRankMirror::PlayerRankData> v11; // [rsp+90h] [rbp-40h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
  {
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nLevelIndex = nIndex;
  }
  else
  {
    data.nBattleIndex = 0;
    *(_QWORD *)&data.nGuanWeiIndex = 0;
    *(_QWORD *)&data.nJobBattleFirst = 0;
    data.nCharId = nCharIda;
    data.nLevelIndex = nIndex;
    std::pair<long const,CRankMirror::PlayerRankData>::pair(&v11, &nCharIda, &data);
    v10 = std::map<long,CRankMirror::PlayerRankData>::insert(&thisa->m_mPlayerRank, &v11);
  }
  if ( nIndex > 0 && nIndex <= 100 )
    thisa->m_vLevelRank[nIndex] = nCharIda;
  Answer::MutexGuard::~MutexGuard(&lock);
}


#####################################
void __cdecl CRankMirror::setWeiWangRank(CRankMirror *const this, CharId_t nCharId, int32_t nIndex)
{
  CharId_t nCharIda; // [rsp+20h] [rbp-B0h] BYREF
  CRankMirror *thisa; // [rsp+28h] [rbp-A8h]
  CRankMirror::PlayerRankData data; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > iter; // [rsp+50h] [rbp-80h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> > __x; // [rsp+70h] [rbp-60h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const long int,CRankMirror::PlayerRankData> >,bool> v10; // [rsp+80h] [rbp-50h]
  std::pair<const long int,CRankMirror::PlayerRankData> v11; // [rsp+90h] [rbp-40h] BYREF

  thisa = this;
  nCharIda = nCharId;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_lock);
  iter._M_node = std::map<long,CRankMirror::PlayerRankData>::find(&this->m_mPlayerRank, &nCharIda)._M_node;
  __x._M_node = std::map<long,CRankMirror::PlayerRankData>::end(&thisa->m_mPlayerRank)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator!=(&iter, &__x) )
  {
    std::_Rb_tree_iterator<std::pair<long const,CRankMirror::PlayerRankData>>::operator->(&iter)->second.nWeiWangIndex = nIndex;
  }
  else
  {
    memset(&data.nBattleIndex, 0, 20);
    data.nCharId = nCharIda;
    data.nWeiWangIndex = nIndex;
    std::pair<long const,CRankMirror::PlayerRankData>::pair(&v11, &nCharIda, &data);
    v10 = std::map<long,CRankMirror::PlayerRankData>::insert(&thisa->m_mPlayerRank, &v11);
  }
  if ( nIndex > 0 && nIndex <= 100 )
    thisa->m_vWeiWangRank[nIndex] = nCharIda;
  Answer::MutexGuard::~MutexGuard(&lock);
}


