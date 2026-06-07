// Decompiled methods for class: CActivity
// Source: gameserver.cc
// Total methods: 35

#####################################
void __cdecl CActivity::~CActivity(CActivity *const this)
{
  CActivity::~CActivity(this);
  operator delete(this);
}


#####################################
void __cdecl CActivity::Init(CActivity *const this)
{
  MapManager *v1; // rax
  CActivityMap *v3; // rax
  CActivityMap *pActivityMap; // [rsp+18h] [rbp-38h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > eiter; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > iter; // [rsp+30h] [rbp-20h] BYREF
  int32_t nMapId; // [rsp+44h] [rbp-Ch]
  Map *pMap; // [rsp+48h] [rbp-8h]

  if ( (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 26))(this) == 1 )
  {
    iter._M_current = std::vector<int>::begin(&this->m_cfgActivity->maps)._M_current;
    eiter._M_current = std::vector<int>::end(&this->m_cfgActivity->maps)._M_current;
    while ( __gnu_cxx::operator!=<int const*,std::vector<int>>(&iter, &eiter) )
    {
      nMapId = *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&iter);
      if ( nMapId > 0 )
      {
        v1 = Answer::Singleton<MapManager>::instance();
        pMap = MapManager::GetMap(v1, nMapId);
        if ( pMap && (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 17))(pMap) )
        {
          if ( pMap )
            v3 = (CActivityMap *)__dynamic_cast(
                                   pMap,
                                   (const struct __class_type_info *)&`typeinfo for'Map,
                                   (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                   0);
          else
            v3 = 0;
          pActivityMap = v3;
          if ( v3 )
            std::list<CActivityMap *>::push_back(&this->m_activityMaps, &pActivityMap);
        }
      }
      __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&iter);
    }
  }
}


#####################################
void __cdecl CActivity::OnUpdate(CActivity *const this, CActivityMap *pMap)
{
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-40h] BYREF
  PlayerList tList; // [rsp+30h] [rbp-30h] BYREF
  Player *player; // [rsp+48h] [rbp-18h]

  if ( pMap )
  {
    (*((void (__fastcall **)(CActivity *const, CActivityMap *))this->_vptr_CActivity + 11))(this, pMap);
    if ( (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 34))(this) )
      CActivity::checkRevive(this, pMap);
    if ( this->m_nKickTime > 0 && Map::getNow(pMap) >= this->m_nKickTime )
    {
      std::list<Player *>::list(&tList, &this->m_players);
      iter._M_node = std::list<Player *>::begin(&tList)._M_node;
      eiter._M_node = std::list<Player *>::end(&tList)._M_node;
      while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
      {
        player = *std::_List_iterator<Player *>::operator*(&iter);
        if ( player && StaticObj::getMap(player) == pMap )
          Player::leaveActivity(player);
        std::_List_iterator<Player *>::operator++(&iter);
      }
      if ( std::list<Player *>::empty(&this->m_players) )
        (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 29))(this);
      std::list<Player *>::~list(&tList);
    }
  }
}


#####################################
void __cdecl CActivity::reset(CActivity *const this)
{
  this->m_nStartTime = 0;
  this->m_nKickTime = 0;
  this->m_nBraodcastActivityScoreSign = 0;
  this->m_nBroadcastActivityScoreTick = 0;
  this->m_nLastReviveCheckTick = 0;
  std::list<Player *>::clear(&this->m_players);
}


#####################################
void __cdecl CActivity::SendPlayerActivityInfo(CActivity *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t v4; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E22u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      v4 = (*((__int64 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 42))(this);
      Answer::NetPacket::writeInt32(packet, v4);
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
void __cdecl CActivity::SendPlayerActivityScore(CActivity *const this, Player *player)
{
  __int64 (__fastcall *v2)(CActivity *const, _QWORD); // rbx
  unsigned int ConnId; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    v2 = (__int64 (__fastcall *)(CActivity *const, _QWORD))*((_QWORD *)this->_vptr_CActivity + 52);
    ConnId = Player::getConnId(player);
    packet = (Answer::NetPacket *)v2(this, ConnId);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(player);
      v5 = Player::getConnId(player);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
    (*((void (__fastcall **)(CActivity *const, Player *))this->_vptr_CActivity + 51))(this, player);
  }
}


#####################################
void __cdecl CActivity::BroadcastActivityState(CActivity *const this)
{
  GameService *v2; // rax
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  GameService *v5; // rax
  int8_t nIconState; // [rsp+17h] [rbp-9h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  nIconState = (*((__int64 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 35))(this);
  if ( nIconState == 4 && (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 25))(this) )
    nIconState = 0;
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->iconid);
    Answer::NetPacket::writeInt8(packet, nIconState);
    LeftTime = CActivity::getLeftTime(this);
    Answer::NetPacket::writeInt32(packet, LeftTime);
    Answer::NetPacket::writeInt8(packet, 0);
    Answer::NetPacket::writeInt32(packet, 0);
    if ( nIconState == 2 )
      Answer::NetPacket::writeInt8(packet, 1);
    else
      Answer::NetPacket::writeInt8(packet, 0);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v5, packet);
  }
}


#####################################
void __cdecl CActivity::BroadcastActivityScore(CActivity *const this, CActivityMap *pMap)
{
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( pMap
    && (*((unsigned __int8 (__fastcall **)(CActivity *const, CActivityMap *))this->_vptr_CActivity + 53))(this, pMap) == 1 )
  {
    packet = (Answer::NetPacket *)(*((__int64 (__fastcall **)(CActivity *const, _QWORD))this->_vptr_CActivity + 52))(
                                    this,
                                    0);
    if ( packet )
      Map::broadcast(pMap, packet);
  }
}


#####################################
void __cdecl CActivity::GetIconState(CActivity *const this, IconStateList *const iconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF
  int8_t nIconState; // [rsp+2Fh] [rbp-1h]

  nIconState = (*((__int64 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 35))(this);
  if ( !nIconState && this->m_cfgActivity->typeId == 22 )
    nIconState = 4;
  if ( nIconState != 4 || (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 25))(this) == 1 )
  {
    memset(&icon, 0, sizeof(icon));
    icon.nId = this->m_cfgActivity->iconid;
    icon.nState = nIconState;
    icon.nLeftTime = (*((__int64 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 13))(this);
    if ( nIconState == 2 )
      icon.nEffects = 1;
    if ( nIconState == 4 && (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 25))(this) )
      icon.nState = 0;
    std::list<ShowIcon>::push_back(iconList, &icon);
  }
}


#####################################
bool __cdecl CActivity::IsRightTime(CActivity *const this)
{
  unsigned int (__fastcall *v1)(CActivity *const, tm *); // rbx
  CTimer *v2; // rax
  tm v4; // [rsp+10h] [rbp-50h] BYREF

  v1 = (unsigned int (__fastcall *)(CActivity *const, tm *))*((_QWORD *)this->_vptr_CActivity + 50);
  v2 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&v4, v2);
  return v1(this, &v4) == 2;
}


#####################################
int32_t __cdecl CActivity::GetNextStartTime(CActivity *const this)
{
  return (*((int32_t (__fastcall **)(CActivity *const))this->_vptr_CActivity + 42))(this);
}


#####################################
void __cdecl CActivity::CheckActivity(CActivity *const this)
{
  CTimer *v2; // rax
  ACTIVITY_STATE v3; // eax
  tm localnow; // [rsp+30h] [rbp-60h] BYREF
  ACTIVITY_STATE nOldState; // [rsp+74h] [rbp-1Ch]
  bool bRightLine; // [rsp+7Bh] [rbp-15h]
  ACTIVITY_STATE nState; // [rsp+7Ch] [rbp-14h]

  nOldState = this->m_nState;
  if ( (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 48))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_TIME_OUT;
    return;
  }
  if ( (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 49))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_TIME_OUT;
    return;
  }
  if ( this->m_nState == ACTIVITY_STATE::AS_TIME_OUT )
    this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  bRightLine = (*((__int64 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 26))(this);
  if ( bRightLine || !CActivity::isCrossActivity(this) )
  {
    v2 = Answer::Singleton<CTimer>::instance();
    CTimer::GetLocalNow(&localnow, v2);
    v3 = (*((unsigned int (__fastcall **)(CActivity *const, tm *))this->_vptr_CActivity + 50))(this, &localnow);
    nState = v3;
    if ( v3 == ACTIVITY_STATE::AS_READY )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END || this->m_nState == ACTIVITY_STATE::AS_NOT_START )
      {
        this->m_nState = ACTIVITY_STATE::AS_READY;
        if ( bRightLine )
          (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 46))(this);
      }
    }
    else if ( v3 > ACTIVITY_STATE::AS_READY )
    {
      if ( v3 == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( this->m_nState <= (unsigned int)ACTIVITY_STATE::AS_READY )
        {
          if ( bRightLine )
          {
            if ( this->m_nState == ACTIVITY_STATE::AS_READY )
              Answer::Logger::print(
                Answer::LogLevel::LOG_LEVEL_INFO,
                "activity stop AS_READY to AS_RUNNING id=%d,state=%d,time=%d-%d %d:%d:%d\n",
                this->m_cfgActivity->id,
                this->m_nState,
                localnow.tm_year,
                localnow.tm_yday,
                localnow.tm_hour,
                localnow.tm_min,
                localnow.tm_sec);
            else
              Answer::Logger::print(
                Answer::LogLevel::LOG_LEVEL_INFO,
                "activity stop AS_NOT_START to AS_RUNNING id=%d,state=%d,time=%d-%d %d:%d:%d\n",
                this->m_cfgActivity->id,
                this->m_nState,
                localnow.tm_year,
                localnow.tm_yday,
                localnow.tm_hour,
                localnow.tm_min,
                localnow.tm_sec);
            (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 54))(this);
            (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 47))(this);
          }
          else if ( CActivity::GetType(this) == 19 && CActivity::getActivityTime(this) > 599 )
          {
            this->m_nState = ACTIVITY_STATE::AS_END;
            (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 10))(this);
          }
          this->m_nState = ACTIVITY_STATE::AS_RUNNING;
        }
      }
      else
      {
        if ( v3 != ACTIVITY_STATE::AS_END )
          return;
        if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING && bRightLine )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_INFO,
            "activity stop AS_END to AS_RUNNING id=%d,state=%d,time=%d-%d %d:%d:%d\n",
            this->m_cfgActivity->id,
            this->m_nState,
            localnow.tm_year,
            localnow.tm_yday,
            localnow.tm_hour,
            localnow.tm_min,
            localnow.tm_sec);
          (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 55))(this);
          (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 45))(this);
        }
        this->m_nState = ACTIVITY_STATE::AS_END;
      }
    }
    else
    {
      if ( v3 )
        return;
      if ( this->m_nState == ACTIVITY_STATE::AS_END )
      {
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
      else if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( bRightLine )
        {
          Answer::Logger::print(
            Answer::LogLevel::LOG_LEVEL_INFO,
            "activity stop AS_RUNNING to AS_NOT_START id=%d,state=%d,time=%d-%d %d:%d:%d\n",
            this->m_cfgActivity->id,
            this->m_nState,
            localnow.tm_year,
            localnow.tm_yday,
            localnow.tm_hour,
            localnow.tm_min,
            localnow.tm_sec);
          (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 55))(this);
          (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 45))(this);
        }
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
    }
    if ( bRightLine && this->m_nState != nOldState )
    {
      (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 10))(this);
      if ( CActivity::isCrossActivity(this) )
        CActivity::broadcastActivityState(this);
    }
  }
}


#####################################
void __cdecl CActivity::startActivity(CActivity *const this)
{
  CTimer *v1; // rax
  int32_t RunnerId; // ebx
  MapManager *v3; // rax
  std::_List_iterator<CActivityMap*> iter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+30h] [rbp-20h] BYREF
  CActivityMap *pMap; // [rsp+38h] [rbp-18h]

  (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 29))(this);
  v1 = Answer::Singleton<CTimer>::instance();
  this->m_nStartTime = CTimer::GetNow(v1);
  this->m_nState = ACTIVITY_STATE::AS_RUNNING;
  for ( iter._M_node = std::list<CActivityMap *>::begin(&this->m_activityMaps)._M_node;
        ;
        std::_List_iterator<CActivityMap *>::operator++(&iter) )
  {
    __x._M_node = std::list<CActivityMap *>::end(&this->m_activityMaps)._M_node;
    if ( !std::_List_iterator<CActivityMap *>::operator!=(&iter, &__x) )
      break;
    pMap = *std::_List_iterator<CActivityMap *>::operator*(&iter);
    if ( pMap )
    {
      RunnerId = Map::GetRunnerId(pMap);
      v3 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v3, RunnerId, GameMsgCode::GMC_ACTIVITY_START, pMap, this, 0, 0, 0);
    }
  }
  (*((void (__fastcall **)(CActivity *const))this->_vptr_CActivity + 44))(this);
}


#####################################
void __cdecl CActivity::stopActivity(CActivity *const this)
{
  int32_t RunnerId; // ebx
  MapManager *v2; // rax
  std::_List_iterator<CActivityMap*> iter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+30h] [rbp-20h] BYREF
  CActivityMap *pMap; // [rsp+38h] [rbp-18h]

  this->m_nState = ACTIVITY_STATE::AS_END;
  for ( iter._M_node = std::list<CActivityMap *>::begin(&this->m_activityMaps)._M_node;
        ;
        std::_List_iterator<CActivityMap *>::operator++(&iter) )
  {
    __x._M_node = std::list<CActivityMap *>::end(&this->m_activityMaps)._M_node;
    if ( !std::_List_iterator<CActivityMap *>::operator!=(&iter, &__x) )
      break;
    pMap = *std::_List_iterator<CActivityMap *>::operator*(&iter);
    if ( pMap )
    {
      RunnerId = Map::GetRunnerId(pMap);
      v2 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v2, RunnerId, GameMsgCode::GMC_ACTIVITY_STOP, pMap, this, 0, 0, 0);
    }
  }
}


#####################################
void __cdecl CActivity::broadcastActivityState(CActivity *const this)
{
  int8_t m_nState; // r12
  int32_t Id; // ebx
  GameService *v3; // rax

  m_nState = this->m_nState;
  Id = CActivity::GetId(this);
  v3 = Answer::Singleton<GameService>::instance();
  GameService::broadcastActivityState(v3, Id, m_nState);
}


#####################################
void __cdecl CActivity::onTimeEnd(CActivity *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_END;
  CActivity::delayKickAll(this, 30);
}


#####################################
int32_t __cdecl CActivity::getNextStartTime(CActivity *const this)
{
  CTimer *v3; // rax
  CTimer *v4; // rax
  int v5; // ebx
  size_t v6; // rbx
  CTimer *v8; // rax
  const int *v9; // rax
  tm localnow; // [rsp+10h] [rbp-A0h] BYREF
  std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > iter; // [rsp+50h] [rbp-60h] BYREF
  std::vector<int> v12; // [rsp+60h] [rbp-50h] BYREF
  int32_t nNowTime; // [rsp+7Ch] [rbp-34h]
  int32_t nowMinute; // [rsp+80h] [rbp-30h]
  int32_t startMinute; // [rsp+84h] [rbp-2Ch]
  int32_t days; // [rsp+88h] [rbp-28h]
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
  if ( (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 48))(this)
    && (*((unsigned __int8 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 49))(this)
    && nowMinute < startMinute )
  {
    days = 0;
  }
  else
  {
    if ( std::vector<int>::empty(&this->m_cfgActivity->weekday) )
      return 0;
    v8 = Answer::Singleton<CTimer>::instance();
    weekday = CTimer::GetWeekDay(v8);
    nextweekday = 0;
    std::vector<int>::rbegin((const std::vector<int> *const)&iter);
    while ( 1 )
    {
      std::vector<int>::rend(&v12);
      if ( !std::operator!=<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>(
              &iter,
              (const std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > *const)&v12) )
        break;
      v9 = std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator*(&iter);
      if ( *v9 > weekday )
        break;
      std::reverse_iterator<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>::operator++(&iter);
    }
    std::vector<int>::rend((const std::vector<int> *const)&v12._M_impl._M_end_of_storage);
    if ( std::operator==<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>>(
           &iter,
           (const std::reverse_iterator<__gnu_cxx::__normal_iterator<const int*,std::vector<int> > > *const)&v12._M_impl._M_end_of_storage) )
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
int32_t __cdecl CActivity::getLeftTime(CActivity *const this)
{
  CTimer *v2; // rax
  int v3; // ebx
  int nNowTime; // [rsp+1Ch] [rbp-24h]
  int startMinute; // [rsp+20h] [rbp-20h]
  uint32_t i; // [rsp+28h] [rbp-18h]

  if ( std::vector<int>::empty(&this->m_cfgActivity->start_hour) )
    return 0;
  std::vector<int>::operator[](&this->m_cfgActivity->start_hour, 0);
  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  if ( this->m_nState != ACTIVITY_STATE::AS_RUNNING )
    return (*((__int64 (__fastcall **)(CActivity *const))this->_vptr_CActivity + 42))(this) - nNowTime;
  startMinute = *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, 0);
  for ( i = 0; i < std::vector<int>::size(&this->m_cfgActivity->start_hour); ++i )
  {
    v3 = Answer::DayTime::dayzero(nNowTime);
    if ( v3 + 60 * (*std::vector<int>::operator[](&this->m_cfgActivity->start_hour, i) + this->m_cfgActivity->duration) > nNowTime )
    {
      startMinute = *std::vector<int>::operator[](&this->m_cfgActivity->start_hour, i);
      return Answer::DayTime::dayzero(nNowTime) + 60 * (startMinute + this->m_cfgActivity->duration) - nNowTime;
    }
  }
  return Answer::DayTime::dayzero(nNowTime) + 60 * (startMinute + this->m_cfgActivity->duration) - nNowTime;
}


#####################################
int32_t __cdecl CActivity::getActivityTime(CActivity *const this)
{
  int v1; // ebx

  v1 = 60 * this->m_cfgActivity->duration;
  return v1 - CActivity::getLeftTime(this);
}


#####################################
int32_t __cdecl CActivity::canEnter(CActivity *const this, Player *player, CActivityMap *pTargetMap)
{
  int32_t line; // ebx
  GameService *v5; // rax
  int32_t level; // ebx

  if ( !player || !pTargetMap )
    return 10002;
  if ( this->m_cfgActivity->line )
  {
    line = this->m_cfgActivity->line;
    v5 = Answer::Singleton<GameService>::instance();
    if ( line != GameService::getLine(v5) )
      return 10062;
  }
  level = this->m_cfgActivity->level;
  if ( level <= (*((int (__fastcall **)(Player *))player->_vptr_Entity + 9))(player) )
    return 0;
  else
    return 10056;
}


#####################################
int32_t __cdecl CActivity::GetRevive(CActivity *const this, Player *player)
{
  Answer::Random *v3; // rax
  int v4; // eax
  int32_t lenth; // [rsp+1Ch] [rbp-14h]

  lenth = std::vector<int>::size(&this->m_cfgActivity->target_regiona);
  if ( lenth == 1 )
    return *std::vector<int>::operator[](&this->m_cfgActivity->target_regiona, 0);
  v3 = Answer::Singleton<Answer::Random>::instance();
  v4 = Answer::Random::generate(v3, 0, lenth - 1);
  return *std::vector<int>::operator[](&this->m_cfgActivity->target_regiona, v4);
}


#####################################
void __cdecl CActivity::removePlayer(CActivity *const this, Player *player, bool islogout)
{
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&iter) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&iter, &__x) )
      break;
    if ( *std::_List_iterator<Player *>::operator*(&iter) == player )
    {
      std::list<Player *>::erase(&this->m_players, iter);
      return;
    }
  }
}


#####################################
void __cdecl CActivity::addPlayer(CActivity *const this, Player *player)
{
  int32_t Now; // eax
  int32_t id; // r12d
  int8_t typeId; // bl
  DailyActivity *PlayerDailyActivity; // rax
  Player *playera; // [rsp+0h] [rbp-20h] BYREF
  CActivity *thisa; // [rsp+8h] [rbp-18h]

  thisa = this;
  playera = player;
  if ( player )
  {
    Now = Unit::getNow(playera);
    Player::SetStartProtect(playera, Now);
    id = thisa->m_cfgActivity->id;
    typeId = thisa->m_cfgActivity->typeId;
    PlayerDailyActivity = Player::GetPlayerDailyActivity(playera);
    DailyActivity::AddActivityRecord(PlayerDailyActivity, typeId, id);
    std::list<Player *>::push_back(&thisa->m_players, &playera);
    (*((void (__fastcall **)(CActivity *, Player *))thisa->_vptr_CActivity + 8))(thisa, playera);
  }
}


#####################################
bool __cdecl CActivity::checkData(CActivity *const this)
{
  CfgData *v1; // rax
  CfgData *v3; // rax
  int32_t end_date; // r12d
  int32_t begin_date; // ebx
  CTimer *v6; // rax

  if ( this->m_cfgActivity->typeId == 24 )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL) + 1 <= 41 )
      return 0;
  }
  else if ( this->m_cfgActivity->typeId == 11 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1 <= 7 )
      return 0;
  }
  end_date = this->m_cfgActivity->end_date;
  begin_date = this->m_cfgActivity->begin_date;
  v6 = Answer::Singleton<CTimer>::instance();
  return CTimer::BetweenDate(v6, begin_date, end_date);
}


#####################################
bool __cdecl CActivity::checkWeek(CActivity *const this)
{
  CTimer *v1; // rax
  const int *M_current; // rbx
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > v3; // rax
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __lhs; // [rsp+20h] [rbp-20h] BYREF
  int8_t __val[17]; // [rsp+2Fh] [rbp-11h] BYREF

  __rhs._M_current = std::vector<int>::end(&this->m_cfgActivity->weekday)._M_current;
  v1 = Answer::Singleton<CTimer>::instance();
  __val[0] = CTimer::GetWeekDay(v1);
  M_current = std::vector<int>::end(&this->m_cfgActivity->weekday)._M_current;
  v3._M_current = std::vector<int>::begin(&this->m_cfgActivity->weekday)._M_current;
  __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<int const*,std::vector<int>>,signed char>(
                       v3,
                       (__gnu_cxx::__normal_iterator<const int*,std::vector<int> >)M_current,
                       __val)._M_current;
  return __gnu_cxx::operator!=<int const*,std::vector<int>>(&__lhs, &__rhs);
}


#####################################
bool __cdecl CActivity::checkLine(CActivity *const this)
{
  int32_t line; // ebx
  GameService *v2; // rax
  bool result; // al

  result = 1;
  if ( this->m_cfgActivity->line )
  {
    line = this->m_cfgActivity->line;
    v2 = Answer::Singleton<GameService>::instance();
    if ( line != GameService::getLine(v2) )
      return 0;
  }
  return result;
}


#####################################
void __cdecl CActivity::delayKickAll(CActivity *const this, int32_t nTime)
{
  CTimer *v2; // rax

  v2 = Answer::Singleton<CTimer>::instance();
  this->m_nKickTime = nTime + CTimer::GetNow(v2);
}


#####################################
void __cdecl CActivity::removeActivityMonster(CActivity *const this, int32_t monsterId)
{
  int v2; // ebx
  MapManager *v3; // rax
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > it; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  Map *pMap; // [rsp+28h] [rbp-18h]

  for ( it._M_current = std::vector<int>::begin(&this->m_cfgActivity->maps)._M_current;
        ;
        __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<int>::end(&this->m_cfgActivity->maps)._M_current;
    if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&it, &__rhs) )
      break;
    v2 = *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&it);
    v3 = Answer::Singleton<MapManager>::instance();
    pMap = MapManager::GetMap(v3, v2);
    if ( pMap )
      Map::delMonster(pMap, monsterId);
  }
}


#####################################
bool __cdecl CActivity::needBroadcastActivityScore(CActivity *const this, CActivityMap *pMap)
{
  if ( this->m_nBraodcastActivityScoreSign <= 0 )
    return 0;
  --this->m_nBraodcastActivityScoreSign;
  return 1;
}


#####################################
void __cdecl CActivity::setNeedBroadcastActivityScore(CActivity *const this)
{
  this->m_nBraodcastActivityScoreSign = std::list<CActivityMap *>::size(&this->m_activityMaps);
}


#####################################
void __cdecl CActivity::adjustMonsterAttr(
        CActivity *const this,
        CfgMonster *const cfgMonster,
        int32_t nLevel,
        bool bAutoLow)
{
  int32_t mid; // ebx
  CfgData *v6; // rax
  CfgMonsterAdjust *pCfgAdjust; // [rsp+20h] [rbp-20h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  mid = cfgMonster->mid;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgAdjust = CfgData::GetMonsterAdjust(v6, mid, nLevel, bAutoLow);
  if ( pCfgAdjust )
  {
    cfgMonster->level = pCfgAdjust->level;
    for ( i = 0; i <= 49; ++i )
      cfgMonster->vAttr[i] = pCfgAdjust->vAttr[i];
  }
}


#####################################
bool __cdecl CActivity::OnChangeMap(
        CActivity *const this,
        Player *player,
        CActivityMap *pMap,
        int32_t nX,
        int32_t nY,
        int32_t Param)
{
  std::_List_iterator<CActivityMap*> iter; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+40h] [rbp-30h] BYREF
  bool bFind; // [rsp+57h] [rbp-19h]
  CActivityMap *tp; // [rsp+58h] [rbp-18h]

  if ( !player || !pMap )
    return 0;
  if ( !Map::isWalkablePosition(pMap, nX, nY) )
    return 0;
  bFind = 0;
  for ( iter._M_node = std::list<CActivityMap *>::begin(&this->m_activityMaps)._M_node;
        ;
        std::_List_iterator<CActivityMap *>::operator++(&iter) )
  {
    __x._M_node = std::list<CActivityMap *>::end(&this->m_activityMaps)._M_node;
    if ( !std::_List_iterator<CActivityMap *>::operator!=(&iter, &__x) )
      break;
    tp = *std::_List_iterator<CActivityMap *>::operator*(&iter);
    if ( tp && tp == pMap )
    {
      bFind = 1;
      return bFind && Player::switchMap(player, pMap, nX, nY, 1) == 0;
    }
  }
  return bFind && Player::switchMap(player, pMap, nX, nY, 1) == 0;
}


#####################################
void __cdecl CActivity::addActivityBuff(CActivity *const this, Unit *pUnit, int32_t nBuffId, bool bClear)
{
  CfgData *v4; // rax
  int32_t v5; // edx
  Buff *v6; // rbx
  UnitHandle launcher; // [rsp+30h] [rbp-40h] BYREF
  CfgBuff *cfgBuff; // [rsp+40h] [rbp-30h]
  Buff *buff; // [rsp+48h] [rbp-28h]

  if ( pUnit )
  {
    v4 = Answer::Singleton<CfgData>::instance();
    cfgBuff = CfgData::getBuff(v4, nBuffId);
    if ( cfgBuff )
    {
      launcher.id = (*((__int64 (__fastcall **)(Unit *))pUnit->_vptr_Entity + 12))(pUnit);
      launcher.type = v5;
      v6 = (Buff *)operator new(0x60u);
      Buff::Buff(v6, pUnit, cfgBuff, &launcher, 3, bClear);
      buff = v6;
      if ( v6 )
        Unit::addBuff(pUnit, buff);
    }
  }
}


#####################################
void __cdecl CActivity::checkRevive(CActivity *const this, CActivityMap *pMap)
{
  int64_t Tick; // rbx
  int64_t v3; // rbx
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-40h] BYREF
  PlayerList tList; // [rsp+30h] [rbp-30h] BYREF
  Player *player; // [rsp+48h] [rbp-18h]

  if ( Map::getTick(pMap) - this->m_nLastReviveCheckTick > 499 )
  {
    this->m_nLastReviveCheckTick = Map::getTick(pMap);
    std::list<Player *>::list(&tList, &this->m_players);
    iter._M_node = std::list<Player *>::begin(&tList)._M_node;
    eiter._M_node = std::list<Player *>::end(&tList)._M_node;
    while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
    {
      player = *std::_List_iterator<Player *>::operator*(&iter);
      if ( player && Player::IsDead(player) )
      {
        Tick = Map::getTick(pMap);
        v3 = Tick - Player::GetDieTick(player);
        if ( v3 >= (*((int (__fastcall **)(CActivity *const, Player *))this->_vptr_CActivity + 33))(this, player) )
        {
          Player::FullHPAndSync(player);
          Player::moveToReviveRegion(player, 1);
          (*((void (__fastcall **)(CActivityMap *, Player *, __int64))pMap->_vptr_Map + 12))(pMap, player, 1);
        }
      }
      std::_List_iterator<Player *>::operator++(&iter);
    }
    std::list<Player *>::~list(&tList);
  }
}


#####################################
void __cdecl CActivity::sendSocialUpdateActivityState(CActivity *const this, int8_t nState)
{
  GameService *v2; // rax
  GameService *v3; // rax
  uint32_t WOffset; // edx
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 1 )
  {
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x4E52u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, nState);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v5, 0, packet);
    }
  }
}


