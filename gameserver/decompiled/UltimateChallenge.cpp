// Decompiled methods for class: UltimateChallenge
// Source: gameserver.cc
// Total methods: 16

#####################################
void __cdecl UltimateChallenge::~UltimateChallenge(UltimateChallenge *const this)
{
  UltimateChallenge::~UltimateChallenge(this);
  operator delete(this);
}


#####################################
void __cdecl UltimateChallenge::OnUpdate(UltimateChallenge *const this, CActivityMap *pMap)
{
  CActivity::OnUpdate(this, pMap);
  if ( pMap )
  {
    if ( Map::getTick(pMap) - this->m_lastUpdateTime > 1000 && !this->m_ActState )
    {
      this->m_lastUpdateTime = Map::getTick(pMap);
      if ( CActivity::IsRuning(this) && CActivity::getActivityTime(this) > 599 )
      {
        this->m_ActState = 1;
        (*((void (__fastcall **)(UltimateChallenge *const))this->_vptr_CActivity + 10))(this);
      }
    }
  }
}


#####################################
void __cdecl UltimateChallenge::onMonsterDie(UltimateChallenge *const this, MonsterActivity *pMonster, Player *pKiller)
{
  CfgData *v3; // rax
  int32_t MapId; // ebx
  CfgData *v5; // rax
  Answer::Random *v6; // rax
  Param2 *v7; // rax
  Param2 *v8; // rax
  int8_t bossSign; // r12
  int32_t MonsterMid; // ebx
  int32_t droperMid; // eax
  DropItem item; // [rsp+50h] [rbp-E0h] BYREF
  Position CentosPos; // [rsp+80h] [rbp-B0h] BYREF
  CDropItemGroup dropItemGroup_0; // [rsp+90h] [rbp-A0h] BYREF
  CDropItemGroup dropItemGroup; // [rsp+A0h] [rbp-90h] BYREF
  DropItemVector dropItems; // [rsp+B0h] [rbp-80h] BYREF
  std::_List_iterator<Param2> it; // [rsp+D0h] [rbp-60h] BYREF
  std::_List_iterator<Param2> __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string dropper; // [rsp+F0h] [rbp-40h] BYREF
  char v21; // [rsp+103h] [rbp-2Dh] BYREF
  int32_t startDays; // [rsp+104h] [rbp-2Ch]
  UltimateChallengeCfg *pCfg; // [rsp+108h] [rbp-28h]
  int32_t Equip; // [rsp+110h] [rbp-20h]
  int32_t nRand; // [rsp+114h] [rbp-1Ch]
  Map *pMap; // [rsp+118h] [rbp-18h]

  if ( pMonster )
  {
    if ( pKiller )
    {
      if ( (*((unsigned __int8 (__fastcall **)(MonsterActivity *))pMonster->_vptr_Entity + 17))(pMonster) == 1
        && this->m_nRand > 0 )
      {
        v3 = Answer::Singleton<CfgData>::instance();
        startDays = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
        if ( startDays <= 2 )
        {
          MapId = StaticObj::getMapId(pKiller);
          v5 = Answer::Singleton<CfgData>::instance();
          pCfg = CfgData::GetUltimateChallengeCfgMap(v5, MapId);
          if ( pCfg )
          {
            if ( pCfg->Score > 0 )
            {
              this->m_MonsterScore += pCfg->Score;
              if ( this->m_MonsterScore >= this->m_nRand )
              {
                Equip = 0;
                v6 = Answer::Singleton<Answer::Random>::instance();
                nRand = Answer::Random::generate(v6, 1, 10000);
                for ( it._M_node = std::list<Param2>::begin(&pCfg->DropRateList)._M_node;
                      ;
                      std::_List_iterator<Param2>::operator++(&it, 0) )
                {
                  __x._M_node = std::list<Param2>::end(&pCfg->DropRateList)._M_node;
                  if ( !std::_List_iterator<Param2>::operator!=(&it, &__x) )
                    break;
                  v7 = std::_List_iterator<Param2>::operator->(&it);
                  if ( v7->nParam2 <= nRand )
                  {
                    Equip = std::_List_iterator<Param2>::operator->(&it)->nParam1;
                    break;
                  }
                  v8 = std::_List_iterator<Param2>::operator->(&it);
                  nRand -= v8->nParam2;
                }
                if ( Equip >= 0 )
                {
                  *(_DWORD *)&item.itemClass = 2;
                  *(_QWORD *)&item.itemCount = 1;
                  memset(&item.endTime, 0, 24);
                  item.itemId = Equip;
                  std::vector<DropItem>::vector(&dropItems);
                  std::vector<DropItem>::push_back(&dropItems, &item);
                  CDropItemGroup::CDropItemGroup(&dropItemGroup);
                  pMap = StaticObj::getMap(pMonster);
                  if ( pMap )
                  {
                    CDropItemGroup::CDropItemGroup(&dropItemGroup_0);
                    CentosPos = StaticObj::getCurrentTile(pMonster);
                    bossSign = Monster::getBossSign(pMonster);
                    MonsterMid = Monster::getMid(pMonster);
                    std::allocator<char>::allocator(&v21);
                    std::string::string(&dropper, &unk_8F3CE0);
                    droperMid = Monster::getMid(pMonster);
                    CDropItemGroup::init(
                      &dropItemGroup_0,
                      0,
                      pMap,
                      &CentosPos,
                      pKiller,
                      2,
                      droperMid,
                      &dropItems,
                      &dropper,
                      MonsterMid,
                      bossSign,
                      0);
                    std::string::~string(&dropper);
                    std::allocator<char>::~allocator(&v21);
                    Map::addDropItemGroup(pMap, &dropItemGroup_0);
                    this->m_nRand = 0;
                    CDropItemGroup::~CDropItemGroup(&dropItemGroup_0);
                  }
                  CDropItemGroup::~CDropItemGroup(&dropItemGroup);
                  std::vector<DropItem>::~vector(&dropItems);
                }
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl UltimateChallenge::BroadcastActivityState(UltimateChallenge *const this)
{
  GameService *v1; // rax
  int LeftTime; // edx
  uint32_t WOffset; // edx
  GameService *v4; // rax
  int8_t nIconState; // [rsp+17h] [rbp-9h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  nIconState = (*((__int64 (__fastcall **)(UltimateChallenge *const))this->_vptr_CActivity + 35))(this);
  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->iconid);
    Answer::NetPacket::writeInt8(packet, nIconState);
    if ( nIconState == 2 )
      LeftTime = 600 - CActivity::getActivityTime(this);
    else
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
    v4 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v4, 0, packet);
  }
}


#####################################
int8_t __cdecl UltimateChallenge::GetState(UltimateChallenge *const this)
{
  int v2; // eax

  if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING && CActivity::getActivityTime(this) > 599 )
    LOBYTE(v2) = 3;
  else
    return this->m_nState;
  return v2;
}


#####################################
void __cdecl UltimateChallenge::reset(UltimateChallenge *const this)
{
  CActivity::reset(this);
  this->m_ActState = 0;
  this->m_lastUpdateTime = 0;
  this->m_nRand = 0;
  this->m_MonsterScore = 0;
}


#####################################
int8_t __cdecl UltimateChallenge::getIconState(UltimateChallenge *const this)
{
  int v2; // eax

  if ( this->m_nState == ACTIVITY_STATE::AS_RUNNING && CActivity::getActivityTime(this) > 599 )
    LOBYTE(v2) = 3;
  else
    return this->m_nState;
  return v2;
}


#####################################
int32_t __cdecl UltimateChallenge::GetIconLeftTime(UltimateChallenge *const this)
{
  return 600 - CActivity::getActivityTime(this);
}


#####################################
int32_t __cdecl UltimateChallenge::canEnter(UltimateChallenge *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( this->m_nState != ACTIVITY_STATE::AS_RUNNING )
    return 10002;
  if ( Map::GetMapId(pTargetMap) == 50041 && this->m_ActState )
    return 10002;
  else
    return CActivity::canEnter(this, player, pTargetMap);
}


#####################################
void __cdecl UltimateChallenge::removePlayer(UltimateChallenge *const this, Player *player, bool islogout)
{
  int32_t MapId; // ebx
  CfgData *v4; // rax
  int32_t m_nId; // ebx
  CExtCharBag *Bag; // rax
  UltimateChallengeCfg *pCfg; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    MapId = StaticObj::getMapId(player);
    v4 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetUltimateChallengeCfgMap(v4, MapId);
    if ( pCfg )
    {
      m_nId = pCfg->CostItems.m_nId;
      Bag = Player::GetBag(player);
      CExtCharBag::CleanItemId(Bag, m_nId, ITEM_CHANGE_REASON::ICR_LEAVE_ACTIVE, 1);
      CActivity::removePlayer(this, player, islogout);
    }
  }
}


#####################################
bool __cdecl UltimateChallenge::OnChangeMap(
        UltimateChallenge *const this,
        Player *player,
        CActivityMap *pMap,
        int32_t nX,
        int32_t nY,
        int32_t param)
{
  bool v6; // bl
  int32_t MapId; // r12d
  CfgData *v8; // rax
  int32_t v9; // eax
  int64_t Currency; // rax
  ItemData *p_CostItems; // r12
  CExtCharBag *Bag; // rax
  int v13; // r12d
  MemChrBag *v14; // rax
  int32_t MailId; // r13d
  CharId_t Cid; // r12
  DBService *v17; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+40h] [rbp-B0h] BYREF
  MemChrBagVector GetItems; // [rsp+50h] [rbp-A0h] BYREF
  std::_List_iterator<CActivityMap*> iter; // [rsp+70h] [rbp-80h] BYREF
  std::_List_iterator<CActivityMap*> __x; // [rsp+80h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+90h] [rbp-60h] BYREF
  std::string Param; // [rsp+A0h] [rbp-50h] BYREF
  char v29; // [rsp+B7h] [rbp-39h] BYREF
  UltimateChallengeCfg *pCfg; // [rsp+B8h] [rbp-38h]
  bool bFind; // [rsp+C3h] [rbp-2Dh]
  int32_t MaxFloor; // [rsp+C4h] [rbp-2Ch]
  CActivityMap *tp; // [rsp+C8h] [rbp-28h]

  if ( player && pMap )
  {
    if ( !Map::isWalkablePosition(pMap, nX, nY) )
      return 0;
    MapId = StaticObj::getMapId(player);
    v8 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetUltimateChallengeCfgMap(v8, MapId);
    if ( !pCfg )
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
        break;
      }
    }
    if ( !bFind )
      return 0;
    v9 = Map::GetMapId(pMap);
    if ( v9 != pCfg->NextMapId )
      return 0;
    MaxFloor = Player::getRecord(player, 2082);
    if ( param > 0 && pCfg->Floor > MaxFloor )
    {
      Currency = Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD);
      if ( Currency < pCfg->DoubleConst )
        return 0;
    }
    p_CostItems = &pCfg->CostItems;
    Bag = Player::GetBag(player);
    if ( !CExtCharBag::RemoveItem(Bag, p_CostItems, ITEM_CHANGE_REASON::ICR_ACTIVE_CHANGE_MAP) )
      return 0;
    if ( pCfg->Floor <= MaxFloor )
      return Player::switchMap(player, pMap, nX, nY, 1) == 0;
    std::vector<MemChrBag>::vector(&GetItems, &pCfg->GetItems);
    if ( param > 0 )
    {
      if ( !Player::DecCurrency(
              player,
              CURRENCY_TYPE::CURRENCY_GOLD,
              pCfg->DoubleConst,
              CURRENCY_CHANGE_REASON::GCR_ULTIMATE_CHALLENGE_DOUBLE,
              0) )
      {
        v6 = 0;
        v13 = 0;
        goto LABEL_32;
      }
      for ( it._M_current = std::vector<MemChrBag>::begin(&GetItems)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&GetItems)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
          break;
        v14 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        v14->itemCount *= 3;
      }
    }
    std::allocator<char>::allocator(&v29);
    std::string::string(&Param, &unk_8F3CE0);
    MailId = pCfg->MailId;
    Cid = Player::getCid(player);
    v17 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v17, 0, Cid, MailId, &GetItems, ITEM_CHANGE_REASON::ICR_ULTIMATE_CHALLENGE, &Param, 0);
    std::string::~string(&Param);
    std::allocator<char>::~allocator(&v29);
    Player::updateRecord(player, 2082, pCfg->Floor);
    v13 = 1;
LABEL_32:
    std::vector<MemChrBag>::~vector(&GetItems);
    if ( !v13 )
      return v6;
    return Player::switchMap(player, pMap, nX, nY, 1) == 0;
  }
  return 0;
}


#####################################
void __cdecl UltimateChallenge::addPlayer(UltimateChallenge *const this, Player *player)
{
  if ( player )
  {
    if ( Player::getFamilyId(player) <= 0 )
      Player::setPkMode(player, 6, 0);
    else
      Player::setPkMode(player, 3, 0);
    CActivity::addPlayer(this, player);
  }
}


#####################################
void __cdecl UltimateChallenge::onPlayerRevive(UltimateChallenge *const this, Player *player, bool bSafe)
{
  if ( player )
  {
    if ( bSafe )
      Player::leaveActivity(player);
  }
}


#####################################
void __cdecl UltimateChallenge::broadcastReady(UltimateChallenge *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 420);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
  }
}


#####################################
void __cdecl UltimateChallenge::broadcastStart(UltimateChallenge *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::Random *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 419);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, packet);
    v4 = Answer::Singleton<Answer::Random>::instance();
    this->m_nRand = Answer::Random::generate(v4, 1, 10000);
  }
}


#####################################
void __cdecl UltimateChallenge::onPlayerKilled(UltimateChallenge *const this, Player *pDier, Player *pKiller)
{
  ;
}


