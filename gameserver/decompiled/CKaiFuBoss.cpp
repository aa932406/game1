// Decompiled methods for class: CKaiFuBoss
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CKaiFuBoss::~CKaiFuBoss(CKaiFuBoss *const this)
{
  CKaiFuBoss::~CKaiFuBoss(this);
  operator delete(this);
}


#####################################
void __cdecl CKaiFuBoss::reset(CKaiFuBoss *const this)
{
  this->m_Boss = 0;
  CActivity::reset(this);
}


#####################################
void __cdecl CKaiFuBoss::broadcastReady(CKaiFuBoss *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 470);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CKaiFuBoss::broadcastStart(CKaiFuBoss *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 471);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CKaiFuBoss::broadcastTimeEnd(CKaiFuBoss *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    if ( this->m_Boss && Unit::isAlive(this->m_Boss) )
      Answer::NetPacket::writeInt32(packet, 473);
    else
      Answer::NetPacket::writeInt32(packet, 472);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, 0, packet);
  }
}


#####################################
void __cdecl CKaiFuBoss::sendPlayerScore(CKaiFuBoss *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E26u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      LeftTime = CActivity::getLeftTime(this);
      Answer::NetPacket::writeInt32(packet, LeftTime);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CKaiFuBoss::onTimeEnd(CKaiFuBoss *const this)
{
  CKaiFuBoss::broadcastTimeEnd(this);
  CActivity::delayKickAll(this, 0);
}


#####################################
bool __cdecl CKaiFuBoss::checkData(CKaiFuBoss *const this)
{
  CfgData *v1; // rax
  CfgData *v3; // rax
  int32_t startDays; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
    return 0;
  v3 = Answer::Singleton<CfgData>::instance();
  startDays = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
  if ( CKaiFuBoss::isSpecialDay(this, startDays) )
    return 1;
  if ( CKaiFuBoss::isInSpecialDay(this, startDays) )
    return 0;
  return CActivity::checkData(this);
}


#####################################
bool __cdecl CKaiFuBoss::checkWeek(CKaiFuBoss *const this)
{
  CfgData *v1; // rax
  CfgData *v3; // rax
  int32_t startDays; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v1) )
    return 0;
  v3 = Answer::Singleton<CfgData>::instance();
  startDays = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
  if ( CKaiFuBoss::isSpecialDay(this, startDays) )
    return 1;
  if ( CKaiFuBoss::isInSpecialDay(this, startDays) )
    return 0;
  return CActivity::checkWeek(this);
}


#####################################
bool __cdecl CKaiFuBoss::isSpecialDay(const CKaiFuBoss *const this, int32_t nStartDays)
{
  return (unsigned int)nStartDays <= 6;
}


#####################################
int32_t __cdecl CKaiFuBoss::getNextStartTime(CKaiFuBoss *const this)
{
  CTimer *v3; // rax
  CTimer *v4; // rax
  int v5; // ebx
  size_t v6; // rbx
  CfgData *v7; // rax
  CfgData *v8; // rax
  CfgData *v9; // rax
  CTimer *v11; // rax
  const int *v12; // rax
  tm localnow; // [rsp+10h] [rbp-A0h] BYREF
  std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > iter; // [rsp+50h] [rbp-60h] BYREF
  std::vector<int> v15; // [rsp+60h] [rbp-50h] BYREF
  int32_t nNowTime; // [rsp+78h] [rbp-38h]
  int32_t nowMinute; // [rsp+7Ch] [rbp-34h]
  int32_t startMinute; // [rsp+80h] [rbp-30h]
  int32_t days; // [rsp+84h] [rbp-2Ch]
  int32_t startDays; // [rsp+88h] [rbp-28h]
  uint32_t i; // [rsp+90h] [rbp-20h]
  int32_t startTime; // [rsp+94h] [rbp-1Ch]
  int32_t weekday; // [rsp+98h] [rbp-18h]
  int32_t nextweekday; // [rsp+9Ch] [rbp-14h]

  if ( CActivity::IsRuning(this) || std::vector<int>::empty(&this->m_cfgActivity->start_hour) )
    return 0;
  v3 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v3);
  v4 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&localnow, v4);
  nowMinute = 60 * localnow.tm_hour + localnow.tm_min;
  startMinute = *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, 0);
  for ( i = 0; ; ++i )
  {
    v6 = i;
    if ( v6 >= std::vector<int>::size(&this->m_cfgActivity->start_hour) )
      break;
    v5 = Answer::DayTime::dayzero(nNowTime);
    startTime = v5 + 60 * *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, i);
    if ( startMinute > nNowTime )
    {
      startMinute = *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, i);
      break;
    }
  }
  days = -1;
  startDays = 0;
  v7 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::isUniteServer(v7) )
  {
    v8 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v8, SERVER_TYPE::SVT_UNITE) + 7;
  }
  else
  {
    v9 = Answer::Singleton<CfgData>::instance();
    startDays = CfgData::getServerDiffDay(v9, SERVER_TYPE::SVT_NORMAL);
  }
  if ( (*((unsigned __int8 (__fastcall **)(CKaiFuBoss *const))this->_vptr_CActivity + 48))(this)
    && (*((unsigned __int8 (__fastcall **)(CKaiFuBoss *const))this->_vptr_CActivity + 49))(this) )
  {
    if ( nowMinute < startMinute )
      days = 0;
  }
  else if ( CKaiFuBoss::isInSpecialDay(this, startDays) && startDays <= 6 )
  {
    days = 7 - startDays;
  }
  if ( days < 0 )
  {
    if ( std::vector<int>::empty(&this->m_cfgActivity->weekday) )
      return 0;
    v11 = Answer::Singleton<CTimer>::instance();
    weekday = CTimer::GetWeekDay(v11);
    nextweekday = 0;
    std::vector<int>::rbegin((const std::vector<int> *const)&iter);
    while ( 1 )
    {
      std::vector<int>::rend(&v15);
      if ( !std::operator!=<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>(
              &iter,
              (const std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > *const)&v15) )
        break;
      v12 = std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator*(&iter);
      if ( *v12 > weekday )
        break;
      std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator++(&iter);
    }
    std::vector<int>::rend((const std::vector<int> *const)&v15._M_impl._M_end_of_storage);
    if ( std::operator==<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>(
           &iter,
           (const std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > *const)&v15._M_impl._M_end_of_storage) )
    {
      nextweekday = *std::vector<int>::back(&this->m_cfgActivity->weekday);
    }
    else
    {
      nextweekday = *std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator*(&iter);
    }
    if ( nextweekday >= weekday )
      days = nextweekday - weekday;
    else
      days = nextweekday + 7 - weekday;
  }
  return 86400 * days + 60 * startMinute + Answer::DayTime::dayzero(nNowTime);
}


#####################################
void __cdecl CKaiFuBoss::onMonsterAdd(CKaiFuBoss *const this, MonsterActivity *pMonster)
{
  if ( pMonster )
    this->m_Boss = pMonster;
}


