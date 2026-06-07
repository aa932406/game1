// Decompiled methods for class: CMoLingRuQin
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CMoLingRuQin::~CMoLingRuQin(CMoLingRuQin *const this)
{
  CMoLingRuQin::~CMoLingRuQin(this);
  operator delete(this);
}


#####################################
void __cdecl CMoLingRuQin::CheckActivity(CMoLingRuQin *const this)
{
  CTimer *v1; // rsi
  ACTIVITY_STATE v2; // eax
  tm localnow; // [rsp+10h] [rbp-40h] BYREF
  bool bRightLine; // [rsp+4Bh] [rbp-5h]
  ACTIVITY_STATE nState; // [rsp+4Ch] [rbp-4h]

  if ( (*((unsigned __int8 (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 48))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_TIME_OUT;
  }
  else if ( (*((unsigned __int8 (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 49))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  }
  else
  {
    v1 = Answer::Singleton<CTimer>::instance();
    CTimer::GetLocalNow(&localnow, v1);
    bRightLine = (*((__int64 (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 26))(this);
    v2 = (*((unsigned int (__fastcall **)(CMoLingRuQin *const, tm *))this->_vptr_CActivity + 50))(this, &localnow);
    nState = v2;
    if ( v2 == ACTIVITY_STATE::AS_READY )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END || this->m_nState == ACTIVITY_STATE::AS_NOT_START )
      {
        this->m_nState = ACTIVITY_STATE::AS_READY;
        if ( bRightLine )
        {
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 10))(this);
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 46))(this);
        }
      }
    }
    else if ( v2 > ACTIVITY_STATE::AS_READY )
    {
      if ( v2 == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( this->m_nState <= (unsigned int)ACTIVITY_STATE::AS_READY && bRightLine )
        {
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 54))(this);
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 10))(this);
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 47))(this);
        }
        if ( bRightLine )
          CMoLingRuQin::FlushMonsters(this);
        this->m_nState = ACTIVITY_STATE::AS_RUNNING;
      }
      else if ( v2 == ACTIVITY_STATE::AS_END )
      {
        if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
        {
          if ( bRightLine )
          {
            (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 55))(this);
            (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 10))(this);
          }
          this->m_nState = ACTIVITY_STATE::AS_END;
        }
        this->m_nState = ACTIVITY_STATE::AS_END;
        this->m_refreshCount = 1;
        this->m_RefreshTime = 0;
      }
    }
    else if ( v2 == ACTIVITY_STATE::AS_NOT_START )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END )
      {
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
      else if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( bRightLine )
        {
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 55))(this);
          (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 10))(this);
        }
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
      this->m_refreshCount = 1;
      this->m_RefreshTime = 0;
    }
  }
}


#####################################
void __cdecl CMoLingRuQin::FlushMonsters(CMoLingRuQin *const this)
{
  CTimer *v1; // rax
  int32_t m_refreshCount; // ebx
  CfgData *v3; // rax
  const cfgGoblinTableData *GoblinTable; // rax
  int v5; // ebx
  MapManager *v6; // rax
  int32_t v7; // r12d
  int32_t RunnerId; // ebx
  MapManager *v9; // rax
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > it; // [rsp+20h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+30h] [rbp-30h] BYREF
  int32_t NowTime; // [rsp+3Ch] [rbp-24h]
  const cfgGoblinData *goblin; // [rsp+40h] [rbp-20h]
  Map *pMap; // [rsp+48h] [rbp-18h]

  v1 = Answer::Singleton<CTimer>::instance();
  NowTime = CTimer::GetNow(v1);
  m_refreshCount = this->m_refreshCount;
  v3 = Answer::Singleton<CfgData>::instance();
  GoblinTable = CfgData::GetGoblinTable(v3);
  goblin = cfgGoblinTableData::getGoblinData(GoblinTable, m_refreshCount);
  if ( goblin && NowTime - this->m_LastFlushTime >= this->m_RefreshTime )
  {
    for ( it._M_current = std::vector<int>::begin(&this->m_cfgActivity->maps)._M_current;
          ;
          __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<int>::end(&this->m_cfgActivity->maps)._M_current;
      if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&it, &__rhs) )
        break;
      v5 = *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&it);
      v6 = Answer::Singleton<MapManager>::instance();
      pMap = MapManager::GetMap(v6, v5);
      if ( pMap )
      {
        v7 = this->m_refreshCount;
        RunnerId = Map::GetRunnerId(pMap);
        v9 = Answer::Singleton<MapManager>::instance();
        MapManager::PostMsg(v9, RunnerId, GameMsgCode::GMC_GOBLIN_ACTIVITY, pMap, this, v7, 0, 0);
      }
    }
    this->m_LastFlushTime = NowTime;
    ++this->m_refreshCount;
    this->m_RefreshTime = goblin->m_nRefreshTime;
  }
}


#####################################
void __cdecl CMoLingRuQin::startActivity(CMoLingRuQin *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_RUNNING;
  CMoLingRuQin::FlushMonsters(this);
}


#####################################
void __cdecl CMoLingRuQin::stopActivity(CMoLingRuQin *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  (*((void (__fastcall **)(CMoLingRuQin *const))this->_vptr_CActivity + 45))(this);
  CMoLingRuQin::broadcastEnd(this);
}


#####################################
void __cdecl CMoLingRuQin::broadcastReady(CMoLingRuQin *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 329);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CMoLingRuQin::broadcastStart(CMoLingRuQin *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 327);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CMoLingRuQin::onTimeEnd(CMoLingRuQin *const this)
{
  int v1; // ebx
  MapManager *v2; // rax
  int32_t RunnerId; // ebx
  MapManager *v4; // rax
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > iter; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+30h] [rbp-20h] BYREF
  Map *pMap; // [rsp+38h] [rbp-18h]

  for ( iter._M_current = std::vector<int>::begin(&this->m_cfgActivity->maps)._M_current;
        ;
        __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<int>::end(&this->m_cfgActivity->maps)._M_current;
    if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&iter, &__rhs) )
      break;
    v1 = *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&iter);
    v2 = Answer::Singleton<MapManager>::instance();
    pMap = MapManager::GetMap(v2, v1);
    if ( pMap )
    {
      RunnerId = Map::GetRunnerId(pMap);
      v4 = Answer::Singleton<MapManager>::instance();
      MapManager::PostMsg(v4, RunnerId, GameMsgCode::GMC_GOBLIN_ACTIVITY, pMap, this, 0, 0, 0);
    }
  }
}


