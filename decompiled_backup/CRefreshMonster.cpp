// Decompiled methods for class: CRefreshMonster
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl CRefreshMonster::~CRefreshMonster(CRefreshMonster *const this)
{
  CRefreshMonster::~CRefreshMonster(this);
  operator delete(this);
}


#####################################
void __cdecl CRefreshMonster::reset(CRefreshMonster *const this)
{
  std::_List_iterator<RefreshMonsterCfg> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<RefreshMonsterCfg> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<RefreshMonsterCfg>::begin(&this->m_RefreshCfgList)._M_node;
        ;
        std::_List_iterator<RefreshMonsterCfg>::operator++(&it, 0) )
  {
    __x._M_node = std::list<RefreshMonsterCfg>::end(&this->m_RefreshCfgList)._M_node;
    if ( !std::_List_iterator<RefreshMonsterCfg>::operator!=(&it, &__x) )
      break;
    std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->LastFreshTime = 0;
  }
  this->m_StateTime = 0;
  CActivity::reset(this);
}


#####################################
void __cdecl CRefreshMonster::CheckActivity(CRefreshMonster *const this)
{
  CTimer *v1; // rsi
  CTimer *v2; // rax
  ACTIVITY_STATE v3; // eax
  tm localnow; // [rsp+10h] [rbp-50h] BYREF
  int32_t NowTime; // [rsp+54h] [rbp-Ch]
  bool bRightLine; // [rsp+5Bh] [rbp-5h]
  ACTIVITY_STATE nState; // [rsp+5Ch] [rbp-4h]

  if ( (*((unsigned __int8 (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 48))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_TIME_OUT;
  }
  else if ( (*((unsigned __int8 (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 49))(this) != 1 )
  {
    this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  }
  else
  {
    if ( this->m_nState == ACTIVITY_STATE::AS_TIME_OUT )
      this->m_nState = ACTIVITY_STATE::AS_NOT_START;
    v1 = Answer::Singleton<CTimer>::instance();
    CTimer::GetLocalNow(&localnow, v1);
    v2 = Answer::Singleton<CTimer>::instance();
    NowTime = CTimer::GetNow(v2);
    bRightLine = (*((__int64 (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 26))(this);
    v3 = (*((unsigned int (__fastcall **)(CRefreshMonster *const, tm *))this->_vptr_CActivity + 50))(this, &localnow);
    nState = v3;
    if ( v3 == ACTIVITY_STATE::AS_READY )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END || this->m_nState == ACTIVITY_STATE::AS_NOT_START )
      {
        this->m_nState = ACTIVITY_STATE::AS_READY;
        if ( bRightLine )
        {
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 10))(this);
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 46))(this);
        }
      }
    }
    else if ( v3 > ACTIVITY_STATE::AS_READY )
    {
      if ( v3 == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( this->m_nState <= (unsigned int)ACTIVITY_STATE::AS_READY && bRightLine )
        {
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 54))(this);
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 10))(this);
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 47))(this);
          this->m_StateTime = NowTime;
        }
        this->m_nState = ACTIVITY_STATE::AS_RUNNING;
        if ( bRightLine )
          CRefreshMonster::FlushMonsters(this, NowTime);
      }
      else if ( v3 == ACTIVITY_STATE::AS_END )
      {
        if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
        {
          if ( bRightLine )
          {
            (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 55))(this);
            (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 10))(this);
          }
          this->m_nState = ACTIVITY_STATE::AS_END;
        }
        this->m_nState = ACTIVITY_STATE::AS_END;
      }
    }
    else if ( v3 == ACTIVITY_STATE::AS_NOT_START )
    {
      if ( this->m_nState == ACTIVITY_STATE::AS_END )
      {
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
      else if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING )
      {
        if ( bRightLine )
        {
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 55))(this);
          (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 10))(this);
        }
        this->m_nState = ACTIVITY_STATE::AS_NOT_START;
      }
    }
  }
}


#####################################
void __cdecl CRefreshMonster::FlushMonsters(CRefreshMonster *const this, int32_t NowTime)
{
  int32_t m_StateTime; // ebx
  int32_t LastFreshTime; // ebx
  int32_t v5; // ebx
  int32_t LeftTime; // eax
  int v7; // ebx
  MapManager *v8; // rax
  int32_t iparam2; // r12d
  int32_t RunnerId; // ebx
  MapManager *v11; // rax
  int32_t GongGaoId; // edx
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > itMap; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<RefreshMonsterCfg> it; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<RefreshMonsterCfg> __x; // [rsp+40h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+50h] [rbp-30h] BYREF
  int32_t nDiffTime; // [rsp+64h] [rbp-1Ch]
  Map *pMap; // [rsp+68h] [rbp-18h]

  for ( it._M_node = std::list<RefreshMonsterCfg>::begin(&this->m_RefreshCfgList)._M_node;
        ;
        std::_List_iterator<RefreshMonsterCfg>::operator++(&it, 0) )
  {
    __x._M_node = std::list<RefreshMonsterCfg>::end(&this->m_RefreshCfgList)._M_node;
    if ( !std::_List_iterator<RefreshMonsterCfg>::operator!=(&it, &__x) )
      break;
    m_StateTime = this->m_StateTime;
    if ( m_StateTime + std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nStartTime < NowTime )
    {
      if ( std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->LastFreshTime <= 0
        || (LastFreshTime = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->LastFreshTime,
            LastFreshTime + std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nDiffTime <= NowTime) )
      {
        std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->LastFreshTime = NowTime;
        v5 = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nDiffTime;
        if ( v5 <= CActivity::GetLeftTime(this) )
          LeftTime = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nDiffTime;
        else
          LeftTime = CActivity::GetLeftTime(this);
        nDiffTime = LeftTime;
        for ( itMap._M_current = std::vector<int>::begin(&this->m_cfgActivity->maps)._M_current;
              ;
              __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&itMap) )
        {
          __rhs._M_current = std::vector<int>::end(&this->m_cfgActivity->maps)._M_current;
          if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&itMap, &__rhs) )
            break;
          v7 = *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&itMap);
          v8 = Answer::Singleton<MapManager>::instance();
          pMap = MapManager::GetMap(v8, v7);
          if ( pMap )
          {
            iparam2 = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->nIndex;
            RunnerId = Map::GetRunnerId(pMap);
            v11 = Answer::Singleton<MapManager>::instance();
            MapManager::PostMsg(v11, RunnerId, GameMsgCode::GMC_ADD_OBJ, pMap, this, nDiffTime, iparam2, 0);
            GongGaoId = std::_List_iterator<RefreshMonsterCfg>::operator->(&it)->GongGaoId;
            CRefreshMonster::FreshObjGongGao(this, GongGaoId);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CRefreshMonster::stopActivity(CRefreshMonster *const this)
{
  this->m_nState = ACTIVITY_STATE::AS_NOT_START;
  (*((void (__fastcall **)(CRefreshMonster *const))this->_vptr_CActivity + 45))(this);
  CRefreshMonster::broadcastEnd(this);
}


#####################################
void __cdecl CRefreshMonster::broadcastStart(CRefreshMonster *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->StartGongGao);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CRefreshMonster::FreshObjGongGao(CRefreshMonster *const this, int32_t GongGaoId)
{
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  if ( GongGaoId > 0 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v4 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v4, 0, packet);
    }
  }
}


