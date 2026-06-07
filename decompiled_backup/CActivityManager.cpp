// Decompiled methods for class: CActivityManager
// Source: gameserver.cc
// Total methods: 25

#####################################
void __cdecl CActivityManager::~CActivityManager(CActivityManager *const this)
{
  CActivityManager::~CActivityManager(this);
  operator delete(this);
}


#####################################
void __cdecl CActivityManager::Init(CActivityManager *const this, int32_t line)
{
  DBService *v2; // rax
  DBService *v3; // rax
  CfgData *v4; // rax
  const std::pair<const int,CfgActivity> *v5; // rax
  CFamilyWar *v6; // rbx
  CFamilyLight *v7; // rbx
  CMoLingRuQin *v8; // rbx
  CActivityWorldBoss *v9; // rbx
  CCampWar *v10; // rbx
  CPeerlessWar *v11; // rbx
  CCityWar *v12; // rbx
  UltimateChallenge *v13; // rbx
  CYaBiao *v14; // rbx
  CKaiFuBoss *v15; // rbx
  CXinMaiMap *v16; // rbx
  CrossTower *v17; // rbx
  CRongLian *v18; // rbx
  CRefreshMonster *v19; // rbx
  CActivity **v20; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgActivity> > eiter; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgActivity> > iter; // [rsp+20h] [rbp-50h] BYREF
  int __k; // [rsp+2Ch] [rbp-44h] BYREF
  const CfgActivityTable *cfgAllActivity; // [rsp+30h] [rbp-40h]
  bool TerritorySign; // [rsp+3Fh] [rbp-31h]
  const CfgActivity *cfgActivity; // [rsp+40h] [rbp-30h]
  CActivity *pActivity; // [rsp+48h] [rbp-28h]

  if ( line == 9 )
  {
    v2 = Answer::Singleton<DBService>::instance();
    DBService::onLoadCityWarInfo(v2);
    v3 = Answer::Singleton<DBService>::instance();
    DBService::onLoadPeerlessWarInfo(v3);
  }
  v4 = Answer::Singleton<CfgData>::instance();
  cfgAllActivity = CfgData::getAllActivity(v4);
  iter._M_node = std::map<int,CfgActivity>::begin(cfgAllActivity)._M_node;
  eiter._M_node = std::map<int,CfgActivity>::end(cfgAllActivity)._M_node;
  TerritorySign = 1;
  while ( std::_Rb_tree_const_iterator<std::pair<int const,CfgActivity>>::operator!=(&iter, &eiter) )
  {
    v5 = std::_Rb_tree_const_iterator<std::pair<int const,CfgActivity>>::operator->(&iter);
    cfgActivity = &v5->second;
    pActivity = 0;
    switch ( v5->second.typeId )
    {
      case 1:
        v6 = (CFamilyWar *)operator new(0xB0u);
        CFamilyWar::CFamilyWar(v6, cfgActivity);
        pActivity = v6;
        break;
      case 3:
        v7 = (CFamilyLight *)operator new(0x90u);
        CFamilyLight::CFamilyLight(v7, cfgActivity);
        pActivity = v7;
        break;
      case 4:
        v8 = (CMoLingRuQin *)operator new(0x68u);
        CMoLingRuQin::CMoLingRuQin(v8, cfgActivity);
        pActivity = v8;
        break;
      case 0xB:
        v9 = (CActivityWorldBoss *)operator new(0xF0u);
        CActivityWorldBoss::CActivityWorldBoss(v9, cfgActivity);
        pActivity = v9;
        break;
      case 0xC:
        v10 = (CCampWar *)operator new(0x100u);
        CCampWar::CCampWar(v10, cfgActivity);
        pActivity = v10;
        break;
      case 0xD:
        v11 = (CPeerlessWar *)operator new(0xA8u);
        CPeerlessWar::CPeerlessWar(v11, cfgActivity);
        pActivity = v11;
        break;
      case 0x12:
        v12 = (CCityWar *)operator new(0x168u);
        CCityWar::CCityWar(v12, cfgActivity);
        pActivity = v12;
        break;
      case 0x13:
        v13 = (UltimateChallenge *)operator new(0x70u);
        UltimateChallenge::UltimateChallenge(v13, cfgActivity);
        pActivity = v13;
        break;
      case 0x14:
        v14 = (CYaBiao *)operator new(0x58u);
        CYaBiao::CYaBiao(v14, cfgActivity);
        pActivity = v14;
        break;
      case 0x15:
        v15 = (CKaiFuBoss *)operator new(0x60u);
        CKaiFuBoss::CKaiFuBoss(v15, cfgActivity);
        pActivity = v15;
        break;
      case 0x16:
        v16 = (CXinMaiMap *)operator new(0xC8u);
        CXinMaiMap::CXinMaiMap(v16, cfgActivity);
        pActivity = v16;
        break;
      case 0x17:
        v17 = (CrossTower *)operator new(0x110u);
        CrossTower::CrossTower(v17, cfgActivity);
        pActivity = v17;
        break;
      case 0x18:
        v18 = (CRongLian *)operator new(0x58u);
        CRongLian::CRongLian(v18, cfgActivity);
        pActivity = v18;
        break;
      case 0x1A:
        v19 = (CRefreshMonster *)operator new(0x70u);
        CRefreshMonster::CRefreshMonster(v19, cfgActivity);
        pActivity = v19;
        break;
      default:
        break;
    }
    if ( pActivity )
    {
      (*((void (__fastcall **)(CActivity *))pActivity->_vptr_CActivity + 2))(pActivity);
      __k = CActivity::GetId(pActivity);
      v20 = std::map<int,CActivity *>::operator[](&this->m_mActivity, &__k);
      *v20 = pActivity;
    }
    else
    {
      Answer::Logger::print(
        Answer::LogLevel::LOG_LEVEL_ERROR,
        "CActivityManager::Init() actid=%d create Activity fail!!!\n",
        cfgActivity->id);
    }
    std::_Rb_tree_const_iterator<std::pair<int const,CfgActivity>>::operator++(&iter);
  }
}


#####################################
void __cdecl CActivityManager::OnUpdate(CActivityManager *const this, int64_t CurTick)
{
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+20h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( pActivity )
    {
      (*((void (__fastcall **)(CActivity *))pActivity->_vptr_CActivity + 5))(pActivity);
      if ( CActivity::IsRuning(pActivity) )
        (*((void (__fastcall **)(CActivity *, int64_t))pActivity->_vptr_CActivity + 28))(pActivity, CurTick);
    }
  }
}


#####################################
void __cdecl CActivityManager::SendActivityInfo(CActivityManager *const this, Player *player, int32_t nId)
{
  int32_t nIda; // [rsp+Ch] [rbp-34h] BYREF
  Player *playera; // [rsp+10h] [rbp-30h]
  CActivityManager *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+38h] [rbp-8h]

  thisa = this;
  playera = player;
  nIda = nId;
  iter._M_node = std::map<int,CActivity *>::find(&this->m_mActivity, &nIda)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
  {
    pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( pActivity )
      (*((void (__fastcall **)(CActivity *, Player *))pActivity->_vptr_CActivity + 6))(pActivity, playera);
  }
}


#####################################
void __cdecl CActivityManager::SendActivityRankInfo(CActivityManager *const this, Player *player, int32_t nId)
{
  int32_t nIda; // [rsp+Ch] [rbp-34h] BYREF
  Player *playera; // [rsp+10h] [rbp-30h]
  CActivityManager *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+38h] [rbp-8h]

  thisa = this;
  playera = player;
  nIda = nId;
  iter._M_node = std::map<int,CActivity *>::find(&this->m_mActivity, &nIda)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
  {
    pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( pActivity )
      (*((void (__fastcall **)(CActivity *, Player *))pActivity->_vptr_CActivity + 9))(pActivity, playera);
  }
}


#####################################
void __cdecl CActivityManager::UpdateActivityState(CActivityManager *const this, int32_t nId, int8_t nState)
{
  MapManager *v4; // rax
  int32_t LeftTime; // r12d
  int32_t RunnerId; // ebx
  MapManager *v7; // rax
  CActivity *pActivity; // [rsp+20h] [rbp-20h]
  Map *pMap; // [rsp+28h] [rbp-18h]

  pActivity = CActivityManager::GetActivity(this, nId);
  if ( pActivity )
  {
    CActivity::UpdateActivityState(pActivity, nState);
    if ( CActivity::GetType(pActivity) == 11 && nState == 2 )
    {
      v4 = Answer::Singleton<MapManager>::instance();
      pMap = MapManager::GetMap(v4, 50106);
      if ( pMap )
      {
        LeftTime = CActivity::GetLeftTime(pActivity);
        RunnerId = Map::GetRunnerId(pMap);
        v7 = Answer::Singleton<MapManager>::instance();
        MapManager::PostMsg(v7, RunnerId, GameMsgCode::GMC_ADD_WORLD_BOSS_NPC, pMap, this, LeftTime, 0, 0);
      }
    }
  }
}


#####################################
int32_t __cdecl CActivityManager::GiveDailyReward(CActivityManager *const this, Player *player, int32_t nId)
{
  int32_t nIda; // [rsp+Ch] [rbp-34h] BYREF
  Player *playera; // [rsp+10h] [rbp-30h]
  CActivityManager *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+38h] [rbp-8h]

  thisa = this;
  playera = player;
  nIda = nId;
  iter._M_node = std::map<int,CActivity *>::find(&this->m_mActivity, &nIda)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x)
    && (pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second) != 0 )
  {
    return (*((int32_t (__fastcall **)(CActivity *, Player *))pActivity->_vptr_CActivity + 15))(pActivity, playera);
  }
  else
  {
    return 10002;
  }
}


#####################################
int32_t __cdecl CActivityManager::HaveRewardCount(CActivityManager *const this, Player *Player, int32_t nId)
{
  int32_t nIda; // [rsp+Ch] [rbp-34h] BYREF
  Player *Playera; // [rsp+10h] [rbp-30h]
  CActivityManager *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+38h] [rbp-8h]

  thisa = this;
  Playera = Player;
  nIda = nId;
  iter._M_node = std::map<int,CActivity *>::find(&this->m_mActivity, &nIda)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x)
    && (pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second) != 0 )
  {
    return (*((int32_t (__fastcall **)(CActivity *, Player *))pActivity->_vptr_CActivity + 21))(pActivity, Playera);
  }
  else
  {
    return 0;
  }
}


#####################################
bool __cdecl CActivityManager::IsActivityRunning(CActivityManager *const this, int32_t id)
{
  int32_t ida; // [rsp+4h] [rbp-2Ch] BYREF
  CActivityManager *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+20h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+28h] [rbp-8h]

  thisa = this;
  ida = id;
  iter._M_node = std::map<int,CActivity *>::find(&this->m_mActivity, &ida)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator==(&iter, &__x) )
    return 0;
  pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
  return pActivity && CActivity::IsRuning(pActivity);
}


#####################################
bool __cdecl CActivityManager::IsActivityRunningByType(CActivityManager *const this, int32_t TypeId)
{
  std::pair<const int,CActivity*> *v2; // rax
  std::pair<const int,CActivity*> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    v2 = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter);
    if ( CActivity::GetType(v2->second) == TypeId )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter);
      if ( CActivity::IsRuning(v3->second) )
        return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl CActivityManager::AppendActivityState(
        CActivityManager *const this,
        Answer::NetPacket *packet,
        int32_t *const nCount)
{
  int8_t Id; // dl
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-20h] BYREF
  CActivity *pActivity; // [rsp+40h] [rbp-10h]
  int8_t nState; // [rsp+4Fh] [rbp-1h]

  if ( packet )
  {
    for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
        break;
      pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
      if ( pActivity )
      {
        nState = (*((__int64 (__fastcall **)(CActivity *))pActivity->_vptr_CActivity + 4))(pActivity);
        if ( nState )
        {
          if ( nState == 4 )
            nState = 5;
        }
        else
        {
          nState = 1;
        }
        Id = CActivity::GetId(pActivity);
        Answer::NetPacket::writeInt8(packet, Id);
        Answer::NetPacket::writeInt8(packet, nState);
        ++*nCount;
      }
    }
  }
}


#####################################
void __cdecl CActivityManager::SetCityWarWinner(CActivityManager *const this, int8_t connid, FamilyId_t nFamilyId)
{
  int8_t v3; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int8_t v6; // bl
  GameService *v7; // rax
  int8_t connida[4]; // [rsp+14h] [rbp-2Ch] BYREF
  CActivityManager *thisa; // [rsp+18h] [rbp-28h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  connida[0] = connid;
  *std::map<signed char,long>::operator[](&this->m_mWinFamily, connida) = nFamilyId;
  v3 = connida[0];
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, v3, Answer::PackType::PACK_DISPATCH, 0x2CC5u);
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, nFamilyId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = connida[0];
    v7 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v7, v6, packet);
  }
}


#####################################
void __cdecl CActivityManager::SetPeerlessWarWinner(CActivityManager *const this, int8_t connid, CharId_t nCharId)
{
  int8_t connida[4]; // [rsp+14h] [rbp-Ch] BYREF
  CActivityManager *thisa; // [rsp+18h] [rbp-8h]

  thisa = this;
  connida[0] = connid;
  *std::map<signed char,long>::operator[](&this->m_mPeerlessWinner, connida) = nCharId;
}


#####################################
void __cdecl CActivityManager::SetCrossTowerWinner(
        CActivityManager *const this,
        CharId_t nCharId,
        int32_t Battle,
        std::string *p_Name)
{
  CActivity *second; // rax
  CrossTower *v5; // rax
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-40h] BYREF
  int __x; // [rsp+2Ch] [rbp-34h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > v9; // [rsp+30h] [rbp-30h] BYREF
  std::string p_sName; // [rsp+40h] [rbp-20h] BYREF
  CrossTower *pCrossTower; // [rsp+48h] [rbp-18h]

  if ( this->m_CrossTowerWiner.Battle <= Battle )
  {
    this->m_CrossTowerWiner.Winner = nCharId;
    this->m_CrossTowerWiner.Battle = Battle;
    std::string::operator=(&this->m_CrossTowerWiner.Name, p_Name);
    __x = 15;
    iter._M_node = std::map<int,CActivity *>::find(&this->m_mActivity, &__x)._M_node;
    v9._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &v9) )
    {
      second = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
      if ( second )
        v5 = (CrossTower *)__dynamic_cast(
                             second,
                             (const struct __class_type_info *)&`typeinfo for'CActivity,
                             (const struct __class_type_info *)&`typeinfo for'CrossTower,
                             0);
      else
        v5 = 0;
      pCrossTower = v5;
      if ( v5 )
      {
        std::string::string(&p_sName, p_Name);
        CrossTower::SetWinnerInfo(pCrossTower, nCharId, &p_sName);
        std::string::~string(&p_sName);
      }
    }
  }
}


#####################################
std::string __cdecl CActivityManager::GetCrossTowerName(CActivityManager *const this)
{
  const std::string *v1; // rsi
  GameService *v2; // rax
  _BYTE v4[17]; // [rsp+1Fh] [rbp-11h] BYREF

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 9 )
  {
    std::allocator<char>::allocator(v4);
    std::string::string(this, &unk_8C1828, v4);
    std::allocator<char>::~allocator(v4);
  }
  else
  {
    std::string::string((std::string *)this, v1 + 14);
  }
  return (std::string)this;
}


#####################################
void __cdecl CActivityManager::SetCrossTowerResult(
        CActivityManager *const this,
        CharId_t nCharId,
        int32_t Battle,
        std::string *p_Name)
{
  this->m_CrossTowerWiner.Winner = nCharId;
  this->m_CrossTowerWiner.Battle = Battle;
  std::string::operator=(&this->m_CrossTowerWiner.Name, p_Name);
}


#####################################
int32_t __cdecl CActivityManager::GetCurActivityId(CActivityManager *const this, int16_t nType)
{
  std::pair<const int,CActivity*> *v2; // rax
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+20h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( pActivity )
    {
      if ( CActivity::GetType(pActivity) == nType && CActivity::IsRuning(pActivity) )
      {
        v2 = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter);
        if ( (*((unsigned __int8 (__fastcall **)(CActivity *))v2->second->_vptr_CActivity + 26))(v2->second) )
          return CActivity::GetId(pActivity);
      }
    }
  }
  return 0;
}


#####################################
void __cdecl CActivityManager::OnCityWarResult(
        CActivityManager *const this,
        int8_t connid,
        int32_t nActId,
        FamilyId_t nFamilyId,
        int32_t nWinTime,
        int32_t nTime,
        CharId_t nLeaderCid,
        CharId_t First,
        CharId_t Second,
        CharId_t Third,
        int32_t nIndex,
        std::string *p_FirstFamilyName,
        std::string *p_SecondFamilyName,
        std::string *p_ThirdFamilyName)
{
  __int64 v14; // rbx
  GameService *v15; // rax
  GameService *v16; // rax
  uint32_t WOffset; // eax
  int8_t v18; // bl
  GameService *v19; // rax
  CActivity *v20; // rax
  CCityWar *v21; // rax
  int32_t nActIda; // [rsp+40h] [rbp-80h] BYREF
  int8_t connida[4]; // [rsp+44h] [rbp-7Ch] BYREF
  CActivityManager *thisa; // [rsp+48h] [rbp-78h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+50h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+60h] [rbp-60h] BYREF
  std::string v30; // [rsp+70h] [rbp-50h] BYREF
  std::string v31; // [rsp+80h] [rbp-40h] BYREF
  std::string v32; // [rsp+90h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+A0h] [rbp-20h]
  CCityWar *pCityWar; // [rsp+A8h] [rbp-18h]

  thisa = this;
  nActIda = nActId;
  connida[0] = connid;
  if ( *std::map<signed char,long>::operator[](&this->m_mWinFamily, connida) != nFamilyId )
  {
    v14 = *std::map<signed char,long>::operator[](&thisa->m_mWinFamily, connida);
    v15 = Answer::Singleton<GameService>::instance();
    GameService::UpdateCityWarTitle(v15, v14, nFamilyId);
    *std::map<signed char,long>::operator[](&thisa->m_mWinFamily, connida) = nFamilyId;
    LOBYTE(v14) = connida[0];
    v16 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v16, v14, Answer::PackType::PACK_DISPATCH, 0x2CC5u);
    if ( !packet )
      return;
    Answer::NetPacket::writeInt64(packet, nFamilyId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v18 = connida[0];
    v19 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v19, v18, packet);
  }
  iter._M_node = std::map<int,CActivity *>::find(&thisa->m_mActivity, &nActIda)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
  {
    v20 = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( v20 )
      v21 = (CCityWar *)__dynamic_cast(
                          v20,
                          (const struct __class_type_info *)&`typeinfo for'CActivity,
                          (const struct __class_type_info *)&`typeinfo for'CCityWar,
                          0);
    else
      v21 = 0;
    pCityWar = v21;
    if ( v21 )
    {
      std::string::string(&v30, p_ThirdFamilyName);
      std::string::string(&v31, p_SecondFamilyName);
      std::string::string(&v32, p_FirstFamilyName);
      CCityWar::OnCityWarResult(
        pCityWar,
        nFamilyId,
        nWinTime,
        nTime,
        nLeaderCid,
        First,
        Second,
        Third,
        nIndex,
        &v32,
        &v31,
        &v30);
      std::string::~string(&v32);
      std::string::~string(&v31);
      std::string::~string(&v30);
    }
  }
}


#####################################
void __cdecl CActivityManager::OnCrossTower(
        CActivityManager *const this,
        int8_t connid,
        int32_t nActId,
        CharId_t Winner,
        std::string *p_Name,
        int32_t Battle)
{
  CharId_t v6; // rbx
  GameService *v7; // rax
  CharId_t v8; // rbx
  GameService *v9; // rax
  GameService *v10; // rax
  GameService *v11; // rax
  uint32_t WOffset; // edx
  GameService *v13; // rax
  GameService *v14; // rax
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_CrossTowerWiner.Winner != Winner )
  {
    if ( this->m_CrossTowerWiner.Winner > 0 )
    {
      v6 = this->m_CrossTowerWiner.Winner;
      v7 = Answer::Singleton<GameService>::instance();
      GameService::onRemoveTitle(v7, v6, 9);
    }
    this->m_CrossTowerWiner.Winner = Winner;
    this->m_CrossTowerWiner.Battle = Battle;
    std::string::operator=(&this->m_CrossTowerWiner.Name, p_Name);
    if ( this->m_CrossTowerWiner.Winner > 0 )
    {
      v8 = this->m_CrossTowerWiner.Winner;
      v9 = Answer::Singleton<GameService>::instance();
      GameService::onCheckTitle(v9, v8, 9, 1);
    }
    v10 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v10) != 9 )
    {
      v11 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v11, connid, Answer::PackType::PACK_DISPATCH, 0x2CC7u);
      if ( !packet )
        return;
      Answer::NetPacket::writeUTF8(packet, &this->m_CrossTowerWiner.Name);
      Answer::NetPacket::writeInt64(packet, this->m_CrossTowerWiner.Winner);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v13, connid, packet);
    }
    v14 = Answer::Singleton<GameService>::instance();
    GameService::RecalAllPlayerAttr(v14);
  }
}


#####################################
void __cdecl CActivityManager::OnPeerlessWarResult(
        CActivityManager *const this,
        int8_t connid,
        int32_t nActId,
        CharId_t winner,
        const std::string *const name)
{
  CharId_t v5; // rbx
  GameService *v6; // rax
  GameService *v7; // rax
  CActivity *second; // rax
  CPeerlessWar *v9; // rax
  int32_t nActIda; // [rsp+10h] [rbp-40h] BYREF
  int8_t connida[4]; // [rsp+14h] [rbp-3Ch] BYREF
  CActivityManager *thisa; // [rsp+18h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-20h] BYREF
  CPeerlessWar *pAct; // [rsp+38h] [rbp-18h]

  thisa = this;
  nActIda = nActId;
  connida[0] = connid;
  if ( *std::map<signed char,long>::operator[](&this->m_mPeerlessWinner, connida) != winner )
  {
    if ( *std::map<signed char,long>::operator[](&thisa->m_mPeerlessWinner, connida) > 0 )
    {
      v5 = *std::map<signed char,long>::operator[](&thisa->m_mPeerlessWinner, connida);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::onRemoveTitle(v6, v5, 2);
    }
    *std::map<signed char,long>::operator[](&thisa->m_mPeerlessWinner, connida) = winner;
    if ( winner > 0 )
    {
      v7 = Answer::Singleton<GameService>::instance();
      GameService::onCheckTitle(v7, winner, 2, 1);
    }
  }
  iter._M_node = std::map<int,CActivity *>::find(&thisa->m_mActivity, &nActIda)._M_node;
  __x._M_node = std::map<int,CActivity *>::end(&thisa->m_mActivity)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
  {
    second = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( second )
      v9 = (CPeerlessWar *)__dynamic_cast(
                             second,
                             (const struct __class_type_info *)&`typeinfo for'CActivity,
                             (const struct __class_type_info *)&`typeinfo for'CPeerlessWar,
                             0);
    else
      v9 = 0;
    pAct = v9;
    if ( v9 )
      CPeerlessWar::OnPeerlessWarResult(pAct, winner, name);
  }
}


#####################################
void __cdecl CActivityManager::GetActicityIconState(
        CActivityManager *const this,
        IconStateList *const iconList,
        Player *Player)
{
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+38h] [rbp-8h]

  if ( Player )
  {
    for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
        break;
      pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
      if ( pActivity )
        CActivity::GetIconState(pActivity, iconList);
    }
  }
}


#####################################
void __cdecl CActivityManager::StopSqiderQueen(CActivityManager *const this)
{
  CSqiderQueen *v1; // rax
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+20h] [rbp-20h] BYREF
  CActivity *pActivity; // [rsp+30h] [rbp-10h]
  CSqiderQueen *pSqiderQueen; // [rsp+38h] [rbp-8h]

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( pActivity )
      v1 = (CSqiderQueen *)__dynamic_cast(
                             pActivity,
                             (const struct __class_type_info *)&`typeinfo for'CActivity,
                             (const struct __class_type_info *)&`typeinfo for'CSqiderQueen,
                             0);
    else
      v1 = 0;
    pSqiderQueen = v1;
    if ( v1 )
    {
      if ( CActivity::IsRuning(pSqiderQueen) )
        CSqiderQueen::StopActivityBySqiderQueenDie(pSqiderQueen);
    }
  }
}


#####################################
void __cdecl CActivityManager::NotifyActivityInfo(CActivityManager *const this, Player *player)
{
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+20h] [rbp-10h] BYREF
  CActivity *pActivity; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    pActivity = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( pActivity )
      (*((void (__fastcall **)(CActivity *, Player *))pActivity->_vptr_CActivity + 22))(pActivity, player);
  }
}


#####################################
bool __cdecl CActivityManager::AddTianJiangBaoXiangCount(
        CActivityManager *const this,
        Player *player,
        int32_t AddCount)
{
  CActivity *second; // rax
  CTianJiangBaoXiang *v4; // rax
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-10h] BYREF
  CTianJiangBaoXiang *pBaoXiang; // [rsp+38h] [rbp-8h]

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    second = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( second )
      v4 = (CTianJiangBaoXiang *)__dynamic_cast(
                                   second,
                                   (const struct __class_type_info *)&`typeinfo for'CActivity,
                                   (const struct __class_type_info *)&`typeinfo for'CTianJiangBaoXiang,
                                   0);
    else
      v4 = 0;
    pBaoXiang = v4;
    if ( v4
      && (*((unsigned __int8 (__fastcall **)(CTianJiangBaoXiang *))pBaoXiang->_vptr_CActivity + 4))(pBaoXiang) == 2 )
    {
      return CTianJiangBaoXiang::AddOpenCount(pBaoXiang, player, AddCount);
    }
  }
  return 0;
}


#####################################
bool __cdecl CActivityManager::ApplyCityWar(
        CActivityManager *const this,
        Player *player,
        FamilyId_t FamilyId,
        int8_t Type)
{
  CActivity *second; // rax
  CCityWar *v5; // rax
  int32_t NextStartTime; // ebx
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > iter; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CActivity*> > __x; // [rsp+30h] [rbp-20h] BYREF
  CCityWar *pCCityWar; // [rsp+38h] [rbp-18h]

  for ( iter._M_node = std::map<int,CActivity *>::begin(&this->m_mActivity)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CActivity *>::end(&this->m_mActivity)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator!=(&iter, &__x) )
      break;
    second = std::_Rb_tree_iterator<std::pair<int const,CActivity *>>::operator->(&iter)->second;
    if ( second )
      v5 = (CCityWar *)__dynamic_cast(
                         second,
                         (const struct __class_type_info *)&`typeinfo for'CActivity,
                         (const struct __class_type_info *)&`typeinfo for'CCityWar,
                         0);
    else
      v5 = 0;
    pCCityWar = v5;
    if ( v5 )
    {
      if ( CActivity::GetNextStartTime(pCCityWar) > 0 )
      {
        NextStartTime = CActivity::GetNextStartTime(pCCityWar);
        if ( NextStartTime - Answer::DayTime::now() > 7200 )
          return CCityWar::ApplyCityWar(pCCityWar, player, FamilyId, Type);
      }
    }
  }
  return 0;
}


