// Decompiled methods for class: CGMBackstate
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CGMBackstate::~CGMBackstate(CGMBackstate *const this)
{
  CGMBackstate::~CGMBackstate(this);
  operator delete(this);
}


#####################################
void __cdecl CGMBackstate::Init(CGMBackstate *const this, int32_t line)
{
  Answer::DBPool *v2; // rax
  int32_t v3; // eax
  Answer::MySqlQuery *v4; // rax
  GMBanChat *v5; // rax
  char szSQL[4096]; // [rsp+10h] [rbp-1070h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1010h] [rbp-70h] BYREF
  GMBanChat chat; // [rsp+1040h] [rbp-40h] BYREF
  Answer::MySqlQuery result; // [rsp+1050h] [rbp-30h] BYREF

  if ( line != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(szSQL, 0, sizeof(szSQL));
    v3 = Answer::DayTime::now();
    snprintf(szSQL, 0xFFFu, "SELECT * FROM `gmt_ban_chat` WHERE `expire_time`>%d", v3);
    v4 = Answer::MySqlDBGuard::query(&db, szSQL);
    Answer::MySqlQuery::MySqlQuery(&result, v4);
    while ( !Answer::MySqlQuery::eof(&result) )
    {
      chat.nCharId = 0;
      *(_QWORD *)&chat.nExpireTime = 0;
      chat.nCharId = Answer::MySqlQuery::getInt64Value(&result, "cid", 0);
      chat.nExpireTime = Answer::MySqlQuery::getIntValue(&result, "expire_time", 0);
      v5 = std::map<long,GMBanChat>::operator[](&this->m_mBanChat, &chat.nCharId);
      *v5 = chat;
      Answer::MySqlQuery::nextRow(&result);
    }
    Answer::MySqlQuery::~MySqlQuery(&result);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl CGMBackstate::OnUpdate(CGMBackstate *const this)
{
  CTimer *v1; // rax
  int64_t curTick; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<CTimer>::instance();
  curTick = CTimer::GetTick(v1);
  if ( curTick - this->m_nLastTick > 999 )
  {
    this->m_nLastTick = curTick;
    CGMBackstate::checkBroadcast(this);
  }
}


#####################################
void __cdecl CGMBackstate::checkBroadcast(CGMBackstate *const this)
{
  GameService *v1; // rax
  CTimer *v2; // rax
  std::pair<const int,GMBroadcast> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,GMBroadcast> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GMBroadcast> > __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nowTime; // [rsp+34h] [rbp-Ch]
  GMBroadcast *broad; // [rsp+38h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) == 1 )
  {
    v2 = Answer::Singleton<CTimer>::instance();
    nowTime = CTimer::GetNow(v2);
    for ( iter._M_node = std::map<int,GMBroadcast>::begin(&this->m_mBroadcasts)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,GMBroadcast>::end(&this->m_mBroadcasts)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator!=(&iter, &__x) )
        break;
      v3 = std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator->(&iter);
      broad = &v3->second;
      if ( v3->second.nStartTime <= nowTime
        && broad->nCount < broad->nTimes
        && nowTime - broad->nLastTime >= broad->nInterval )
      {
        CGMBackstate::sendGMBroadcast(this, &broad->strText, broad->nType);
        ++broad->nCount;
        broad->nLastTime = nowTime;
      }
    }
  }
}


#####################################
void __cdecl CGMBackstate::sendGMBroadcast(CGMBackstate *const this, const std::string *const text, int8_t type)
{
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2CD5u);
  if ( packet )
  {
    Answer::NetPacket::writeUTF8(packet, text);
    Answer::NetPacket::writeInt8(packet, type);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, packet);
  }
}


#####################################
int32_t __cdecl CGMBackstate::GetBanChatLeftTime(CGMBackstate *const this, CharId_t cid)
{
  int32_t v2; // ebx
  CTimer *v3; // rax
  std::pair<const long int,GMBanChat> *v4; // rax
  std::pair<const long int,GMBanChat> *v5; // rax
  CharId_t cida; // [rsp+0h] [rbp-50h] BYREF
  CGMBackstate *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,GMBanChat> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,GMBanChat> > __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t nowTime; // [rsp+3Ch] [rbp-14h]

  thisa = this;
  cida = cid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_mutex);
  iter._M_node = std::map<long,GMBanChat>::find(&this->m_mBanChat, &cida)._M_node;
  __x._M_node = std::map<long,GMBanChat>::end(&thisa->m_mBanChat)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,GMBanChat>>::operator==(&iter, &__x) )
  {
    v2 = -1;
  }
  else
  {
    v3 = Answer::Singleton<CTimer>::instance();
    nowTime = CTimer::GetNow(v3);
    v4 = std::_Rb_tree_iterator<std::pair<long const,GMBanChat>>::operator->(&iter);
    if ( v4->second.nExpireTime <= nowTime )
    {
      v2 = -1;
    }
    else
    {
      v5 = std::_Rb_tree_iterator<std::pair<long const,GMBanChat>>::operator->(&iter);
      v2 = v5->second.nExpireTime - nowTime;
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  return v2;
}


#####################################
int32_t __cdecl CGMBackstate::GetSealLeftTime(CGMBackstate *const this, CharId_t cid)
{
  int32_t v2; // ebx
  CTimer *v3; // rax
  std::pair<const long int,GMSeal> *v4; // rax
  std::pair<const long int,GMSeal> *v5; // rax
  CharId_t cida; // [rsp+0h] [rbp-50h] BYREF
  CGMBackstate *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const long int,GMSeal> > iter; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,GMSeal> > __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t nowTime; // [rsp+3Ch] [rbp-14h]

  thisa = this;
  cida = cid;
  Answer::MutexGuard::MutexGuard(&lock, &this->m_mutex);
  iter._M_node = std::map<long,GMSeal>::find(&this->m_mSeal, &cida)._M_node;
  __x._M_node = std::map<long,GMSeal>::end(&thisa->m_mSeal)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,GMSeal>>::operator==(&iter, &__x) )
  {
    v2 = -1;
  }
  else
  {
    v3 = Answer::Singleton<CTimer>::instance();
    nowTime = CTimer::GetNow(v3);
    v4 = std::_Rb_tree_iterator<std::pair<long const,GMSeal>>::operator->(&iter);
    if ( v4->second.nExpireTime <= nowTime )
    {
      v2 = -1;
    }
    else
    {
      v5 = std::_Rb_tree_iterator<std::pair<long const,GMSeal>>::operator->(&iter);
      v2 = v5->second.nExpireTime - nowTime;
    }
  }
  Answer::MutexGuard::~MutexGuard(&lock);
  return v2;
}


#####################################
void __cdecl CGMBackstate::onUpdateGMBroadcast(CGMBackstate *const this, Answer::NetPacket *inPacket)
{
  std::pair<const int,GMBroadcast> *v2; // rax
  std::pair<const int,GMBroadcast> *v3; // rbx
  std::pair<const int,GMBroadcast> *v4; // rbx
  std::pair<const int,GMBroadcast> *v5; // rbx
  std::pair<const int,GMBroadcast> *v6; // rbx
  GMBroadcast *v7; // rax
  std::string strText; // [rsp+20h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GMBroadcast> > iter; // [rsp+30h] [rbp-90h] BYREF
  int32_t nId; // [rsp+3Ch] [rbp-84h] BYREF
  Answer::MutexGuard lock; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,GMBroadcast> > __x; // [rsp+50h] [rbp-70h] BYREF
  Answer::NetPacket v13; // [rsp+60h] [rbp-60h] BYREF
  int8_t nType; // [rsp+A3h] [rbp-1Dh]
  int32_t nStartTime; // [rsp+A4h] [rbp-1Ch]
  int32_t nInterval; // [rsp+A8h] [rbp-18h]
  int32_t nTimes; // [rsp+ACh] [rbp-14h]

  if ( inPacket )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_mutex);
    v13.m_autoIncrease = Answer::NetPacket::readInt32(inPacket);
    for ( *(&v13.m_autoIncrease + 1) = 0; *(&v13.m_autoIncrease + 1) < v13.m_autoIncrease; ++*(&v13.m_autoIncrease + 1) )
    {
      nId = Answer::NetPacket::readInt32(inPacket);
      iter._M_node = std::map<int,GMBroadcast>::find(&this->m_mBroadcasts, &nId)._M_node;
      __x._M_node = std::map<int,GMBroadcast>::end(&this->m_mBroadcasts)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator!=(&iter, &__x) )
      {
        Answer::NetPacket::readUTF8(&v13, (bool)inPacket);
        v2 = std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator->(&iter);
        std::string::operator=(&v2->second.strText, &v13);
        std::string::~string(&v13);
        v3 = std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator->(&iter);
        v3->second.nType = Answer::NetPacket::readInt8(inPacket);
        v4 = std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator->(&iter);
        v4->second.nStartTime = Answer::NetPacket::readInt32(inPacket);
        v5 = std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator->(&iter);
        v5->second.nInterval = Answer::NetPacket::readInt32(inPacket);
        v6 = std::_Rb_tree_iterator<std::pair<int const,GMBroadcast>>::operator->(&iter);
        v6->second.nTimes = Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        Answer::NetPacket::readUTF8((Answer::NetPacket *const)&strText, (bool)inPacket);
        nType = Answer::NetPacket::readInt8(inPacket);
        nStartTime = Answer::NetPacket::readInt32(inPacket);
        nInterval = Answer::NetPacket::readInt32(inPacket);
        nTimes = Answer::NetPacket::readInt32(inPacket);
        GMBroadcast::GMBroadcast(
          (GMBroadcast *const)&v13.m_wOffset,
          nId,
          &strText,
          nType,
          nStartTime,
          nInterval,
          nTimes);
        v7 = std::map<int,GMBroadcast>::operator[](&this->m_mBroadcasts, &nId);
        GMBroadcast::operator=(v7, (const GMBroadcast *const)&v13.m_wOffset);
        GMBroadcast::~GMBroadcast((GMBroadcast *const)&v13.m_wOffset);
        std::string::~string(&strText);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CGMBackstate::onUpdateGMBanChat(CGMBackstate *const this, Answer::NetPacket *inPacket)
{
  std::pair<const long int,GMBanChat> *v2; // rbx
  std::_Rb_tree_iterator<std::pair<const long int,GMBanChat> > iter; // [rsp+20h] [rbp-40h] BYREF
  CharId_t nCharId; // [rsp+28h] [rbp-38h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,GMBanChat> > __x; // [rsp+40h] [rbp-20h] BYREF
  int32_t isize; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]
  GMBanChat gmbanchat; // 0:^10.16

  if ( inPacket )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_mutex);
    isize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < isize; ++i )
    {
      nCharId = Answer::NetPacket::readInt64(inPacket);
      iter._M_node = std::map<long,GMBanChat>::find(&this->m_mBanChat, &nCharId)._M_node;
      __x._M_node = std::map<long,GMBanChat>::end(&this->m_mBanChat)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<long const,GMBanChat>>::operator!=(&iter, &__x) )
      {
        v2 = std::_Rb_tree_iterator<std::pair<long const,GMBanChat>>::operator->(&iter);
        v2->second.nExpireTime = Answer::NetPacket::readInt32(inPacket);
      }
      else
      {
        gmbanchat.nCharId = nCharId;
        *(_QWORD *)&gmbanchat.nExpireTime = (unsigned int)Answer::NetPacket::readInt32(inPacket);
        *std::map<long,GMBanChat>::operator[](&this->m_mBanChat, &nCharId) = gmbanchat;
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CGMBackstate::onUpdateGMSeal(CGMBackstate *const this, Answer::NetPacket *inPacket)
{
  std::pair<const long int,GMSeal> *v2; // rax
  CTimer *v3; // rax
  int32_t Now; // eax
  CharId_t v5; // rbx
  GameService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const long int,GMSeal> > iter; // [rsp+20h] [rbp-50h] BYREF
  CharId_t nCharId; // [rsp+28h] [rbp-48h] BYREF
  Answer::MutexGuard lock; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,GMSeal> > __x; // [rsp+40h] [rbp-30h] BYREF
  int32_t isize; // [rsp+54h] [rbp-1Ch]
  int32_t i; // [rsp+58h] [rbp-18h]
  int32_t nExpireTime; // [rsp+5Ch] [rbp-14h]
  GMSeal gmseal; // 0:^10.16

  if ( inPacket )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_mutex);
    isize = Answer::NetPacket::readInt32(inPacket);
    for ( i = 0; i < isize; ++i )
    {
      nCharId = Answer::NetPacket::readInt64(inPacket);
      nExpireTime = Answer::NetPacket::readInt32(inPacket);
      iter._M_node = std::map<long,GMSeal>::find(&this->m_mSeal, &nCharId)._M_node;
      __x._M_node = std::map<long,GMSeal>::end(&this->m_mSeal)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<long const,GMSeal>>::operator!=(&iter, &__x) )
      {
        v2 = std::_Rb_tree_iterator<std::pair<long const,GMSeal>>::operator->(&iter);
        v2->second.nExpireTime = nExpireTime;
      }
      else
      {
        gmseal.nCharId = nCharId;
        *(_QWORD *)&gmseal.nExpireTime = (unsigned int)nExpireTime;
        *std::map<long,GMSeal>::operator[](&this->m_mSeal, &nCharId) = gmseal;
      }
      v3 = Answer::Singleton<CTimer>::instance();
      Now = CTimer::GetNow(v3);
      if ( Now < nExpireTime )
      {
        v5 = nCharId;
        v6 = Answer::Singleton<GameService>::instance();
        GameService::KickUser(v6, v5, 4);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


