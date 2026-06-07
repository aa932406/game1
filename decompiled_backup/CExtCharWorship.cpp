// Decompiled methods for class: CExtCharWorship
// Source: gameserver.cc
// Total methods: 13

#####################################
void __cdecl CExtCharWorship::~CExtCharWorship(CExtCharWorship *const this)
{
  CExtCharWorship::~CExtCharWorship(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharWorship::OnCleanUp(CExtCharWorship *const this)
{
  this->m_nWorshipTimes = 0;
  std::list<long>::clear(&this->m_lstChars);
}


#####################################
void __cdecl CExtCharWorship::OnLoadFromDB(CExtCharWorship *const this, const PlayerDBData *const dbData)
{
  this->m_nWorshipTimes = dbData->m_WorshipData.nTimes;
  CExtCharWorship::loadCharList(this, &dbData->m_WorshipData.strCharList);
}


#####################################
void __cdecl CExtCharWorship::OnSaveToDB(CExtCharWorship *const this, PlayerDBData *const dbData)
{
  CExtCharWorship var20; // [rsp+10h] [rbp-20h] BYREF

  dbData->m_WorshipData.nTimes = this->m_nWorshipTimes;
  CExtCharWorship::saveCharList(&var20);
  std::string::operator=(&dbData->m_WorshipData.strCharList, &var20);
  std::string::~string(&var20);
}


#####################################
void __cdecl CExtCharWorship::OnDaySwitch(CExtCharWorship *const this, int32_t nDiffDays)
{
  this->m_nWorshipTimes = 0;
  std::list<long>::clear(&this->m_lstChars);
  CExtCharWorship::SendWorshipInfo(this);
}


#####################################
void __cdecl CExtCharWorship::GetInterestsProtocol(CExtCharWorship *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 20068;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CExtCharWorship::DispatchNetDatas(
        CExtCharWorship *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharWorship::isFunctionOpen(this) )
    return 10002;
  if ( nProcId == 20068 )
    return CExtCharWorship::onSocialWorship(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharWorship::onSocialWorship(CExtCharWorship *const this, Answer::NetPacket *inPacket)
{
  CharId_t nCharId; // [rsp+18h] [rbp-8h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nCharId = Answer::NetPacket::readInt64(inPacket);
  if ( nCharId <= 0 )
    return 10002;
  if ( CExtCharWorship::isTimesLimit(this) )
    return 10002;
  if ( CExtCharWorship::isWorshiped(this, nCharId) )
    return 10002;
  std::list<long>::push_back(&this->m_lstChars, &nCharId);
  ++this->m_nWorshipTimes;
  Player::addExp(this->m_pPlayer, 10000, 0, 1);
  CExtCharWorship::sendSocialWorship(this, nCharId);
  return 0;
}


#####################################
void __cdecl CExtCharWorship::sendSocialWorship(CExtCharWorship *const this, CharId_t nCharId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA4u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt64(packet, nCharId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
void __cdecl CExtCharWorship::SendWorshipInfo(CExtCharWorship *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  __int64 *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  std::_List_iterator<long int> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<long int> __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E0Fu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nWorshipTimes);
      for ( iter._M_node = std::list<long>::begin(&this->m_lstChars)._M_node; ; std::_List_iterator<long>::operator++(&iter) )
      {
        __x._M_node = std::list<long>::end(&this->m_lstChars)._M_node;
        if ( !std::_List_iterator<long>::operator!=(&iter, &__x) )
          break;
        v3 = std::_List_iterator<long>::operator*(&iter);
        Answer::NetPacket::writeInt64(packet, *v3);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CExtCharWorship::isWorshiped(const CExtCharWorship *const this, CharId_t nCharId)
{
  std::_List_const_iterator<long int> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_const_iterator<long int> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<long>::begin(&this->m_lstChars)._M_node;
  eiter._M_node = std::list<long>::end(&this->m_lstChars)._M_node;
  while ( std::_List_const_iterator<long>::operator!=(&iter, &eiter) )
  {
    if ( *std::_List_const_iterator<long>::operator*(&iter) == nCharId )
      return 1;
    std::_List_const_iterator<long>::operator++(&iter);
  }
  return 0;
}


#####################################
void __cdecl CExtCharWorship::loadCharList(CExtCharWorship *const this, const std::string *const str)
{
  std::string *v2; // rax
  const char *v3; // rax
  size_t v4; // rbx
  CharId_t cid; // [rsp+18h] [rbp-48h] BYREF
  StringVector vCharIds; // [rsp+20h] [rbp-40h] BYREF
  std::string delims; // [rsp+40h] [rbp-20h] BYREF
  char v8; // [rsp+4Bh] [rbp-15h] BYREF
  uint32_t i; // [rsp+4Ch] [rbp-14h]

  std::allocator<char>::allocator(&v8);
  std::string::string(&delims, ":", &v8);
  Answer::StringUtility::split(&vCharIds, str, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v8);
  if ( !std::vector<std::string>::empty(&vCharIds) )
  {
    this->m_nWorshipTimes = 0;
    for ( i = 0; ; ++i )
    {
      v4 = i;
      if ( v4 >= std::vector<std::string>::size(&vCharIds) )
        break;
      v2 = std::vector<std::string>::operator[](&vCharIds, i);
      v3 = (const char *)std::string::c_str(v2);
      cid = strtoll(v3, 0, 10);
      if ( cid > 0 )
      {
        std::list<long>::push_back(&this->m_lstChars, &cid);
        ++this->m_nWorshipTimes;
      }
    }
  }
  std::vector<std::string>::~vector(&vCharIds);
}


#####################################
std::string __cdecl CExtCharWorship::saveCharList(CExtCharWorship *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  __int64 *v3; // rax
  __int64 v4; // rax
  _BYTE v6[16]; // [rsp+10h] [rbp-1A0h] BYREF
  __int64 v7; // [rsp+20h] [rbp-190h] BYREF
  std::_List_iterator<long int> iter; // [rsp+180h] [rbp-30h] BYREF
  char v9; // [rsp+18Fh] [rbp-21h] BYREF
  std::_List_iterator<long int> __x; // [rsp+190h] [rbp-20h] BYREF

  if ( std::list<long>::empty((const std::list<long int> *const)(v1 + 24)) )
  {
    std::allocator<char>::allocator(&v9);
    std::string::string(this, &unk_8CCF62, &v9);
    std::allocator<char>::~allocator(&v9);
  }
  else
  {
    v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v6, (unsigned int)v2);
    for ( iter._M_node = std::list<long>::begin((std::list<long int> *const)(v1 + 24))._M_node;
          ;
          std::_List_iterator<long>::operator++(&iter) )
    {
      __x._M_node = std::list<long>::end((std::list<long int> *const)(v1 + 24))._M_node;
      if ( !std::_List_iterator<long>::operator!=(&iter, &__x) )
        break;
      v3 = std::_List_iterator<long>::operator*(&iter);
      v4 = std::ostream::operator<<(&v7, *v3);
      std::operator<<<std::char_traits<char>>(v4, ":");
    }
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v6);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v6);
  }
  return (std::string)this;
}


