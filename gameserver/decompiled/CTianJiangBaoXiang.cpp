// Decompiled methods for class: CTianJiangBaoXiang
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CTianJiangBaoXiang::~CTianJiangBaoXiang(CTianJiangBaoXiang *const this)
{
  CTianJiangBaoXiang::~CTianJiangBaoXiang(this);
  operator delete(this);
}


#####################################
void __cdecl CTianJiangBaoXiang::addPlayer(CTianJiangBaoXiang *const this, Player *player)
{
  ActivityRewardRecord *v2; // rax
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > ItRecord; // [rsp+10h] [rbp-40h] BYREF
  ActivityRewardRecord RewardRecord; // [rsp+20h] [rbp-30h]
  __int64 __x; // [rsp+38h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > v6; // [rsp+40h] [rbp-10h] BYREF
  __int64 __k; // [rsp+48h] [rbp-8h] BYREF

  CActivity::addPlayer(this, player);
  if ( player )
  {
    Player::SetPkProtectTime(player, 0);
    *(_QWORD *)&RewardRecord.OpenBaoXiangCount = 0;
    RewardRecord.BuyCount = 0;
    __x = Player::getCid(player);
    ItRecord._M_node = std::map<long,ActivityRewardRecord>::find(&this->m_PlayerSoreMap, &__x)._M_node;
    v6._M_node = std::map<long,ActivityRewardRecord>::end(&this->m_PlayerSoreMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator==(&ItRecord, &v6) )
    {
      __k = Player::getCid(player);
      v2 = std::map<long,ActivityRewardRecord>::operator[](&this->m_PlayerSoreMap, &__k);
      *v2 = RewardRecord;
    }
  }
}


#####################################
int32_t __cdecl CTianJiangBaoXiang::canEnter(CTianJiangBaoXiang *const this, Player *player, CActivityMap *pTargetMap)
{
  if ( player && pTargetMap )
    return 0;
  else
    return 2;
}


#####################################
void __cdecl CTianJiangBaoXiang::reset(CTianJiangBaoXiang *const this)
{
  CActivity::reset(this);
  this->GradeBaoXiangState = 0;
  std::map<long,ActivityRewardRecord>::clear(&this->m_PlayerSoreMap);
}


#####################################
void __cdecl CTianJiangBaoXiang::sendPlayerScore(CTianJiangBaoXiang *const this, Player *player)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t LeftTime; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > it; // [rsp+10h] [rbp-40h] BYREF
  __int64 __x; // [rsp+18h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > v11; // [rsp+20h] [rbp-30h] BYREF
  int32_t AlreadGrageCount; // [rsp+2Ch] [rbp-24h]
  int8_t IsGetSpecial; // [rsp+33h] [rbp-1Dh]
  int32_t BuyCount; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( player )
  {
    AlreadGrageCount = 0;
    IsGetSpecial = 0;
    BuyCount = 0;
    __x = Player::getCid(player);
    it._M_node = std::map<long,ActivityRewardRecord>::find(&this->m_PlayerSoreMap, &__x)._M_node;
    v11._M_node = std::map<long,ActivityRewardRecord>::end(&this->m_PlayerSoreMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator!=(&it, &v11) )
    {
      AlreadGrageCount = std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it)->second.OpenBaoXiangCount;
      IsGetSpecial = std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it)->second.IsGetSpecial;
      BuyCount = std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it)->second.BuyCount;
    }
    ConnId = Player::getConnId(player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2E26u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgActivity->id);
      Answer::NetPacket::writeInt8(packet, this->GradeBaoXiangState);
      Answer::NetPacket::writeInt32(packet, BuyCount + 10 - AlreadGrageCount);
      Answer::NetPacket::writeInt8(packet, IsGetSpecial);
      LeftTime = CActivity::getLeftTime(this);
      Answer::NetPacket::writeInt32(packet, LeftTime);
      Answer::NetPacket::writeInt32(packet, BuyCount);
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
void __cdecl CTianJiangBaoXiang::AddPlant(CTianJiangBaoXiang *const this, PlantActivity *plant)
{
  GameService *v2; // rax
  uint32_t WOffset; // eax
  GameService *v4; // rax
  void (__fastcall *v5)(CTianJiangBaoXiang *const, Player *); // rbx
  Player *v6; // rdx
  std::_List_iterator<Player*> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( plant )
  {
    if ( Plant::GetPlantType(plant) == 1 )
    {
      this->GradeBaoXiangState = 1;
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, 21);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v4 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v4, 0, packet);
      }
    }
    for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&it) )
    {
      __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
        break;
      v5 = (void (__fastcall *)(CTianJiangBaoXiang *const, Player *))*((_QWORD *)this->_vptr_CActivity + 51);
      v6 = *std::_List_iterator<Player *>::operator*(&it);
      v5(this, v6);
    }
  }
}


#####################################
int32_t __cdecl CTianJiangBaoXiang::GiveDailyReward(CTianJiangBaoXiang *const this, Player *player)
{
  int32_t v2; // ebx
  CExtCharBag *Bag; // rax
  ActivityRewardRecord *v4; // rax
  MemChrBag stu; // [rsp+10h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > it; // [rsp+30h] [rbp-90h] BYREF
  MemChrBagVector addItem; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > ItRecord; // [rsp+60h] [rbp-60h] BYREF
  ActivityRewardRecord RewardRecord; // [rsp+70h] [rbp-50h]
  __int64 __x; // [rsp+88h] [rbp-38h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > v12; // [rsp+90h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const int*,std::vector<int> > __rhs; // [rsp+A0h] [rbp-20h] BYREF
  __int64 __k[3]; // [rsp+A8h] [rbp-18h] BYREF

  if ( !player )
    return 2;
  *(_QWORD *)&RewardRecord.OpenBaoXiangCount = 0;
  RewardRecord.BuyCount = 0;
  __x = Player::getCid(player);
  ItRecord._M_node = std::map<long,ActivityRewardRecord>::find(&this->m_PlayerSoreMap, &__x)._M_node;
  v12._M_node = std::map<long,ActivityRewardRecord>::end(&this->m_PlayerSoreMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator!=(&ItRecord, &v12) )
    RewardRecord = std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&ItRecord)->second;
  if ( RewardRecord.IsGetSpecial )
    return 2;
  std::vector<MemChrBag>::vector(&addItem);
  for ( it._M_current = std::vector<int>::begin(&this->m_cfgActivity->gift_id)._M_current;
        ;
        __gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<int>::end(&this->m_cfgActivity->gift_id)._M_current;
    if ( !__gnu_cxx::operator!=<int const*,std::vector<int>>(&it, &__rhs) )
      break;
    *(_QWORD *)&stu.itemId = 0x100000000LL;
    memset(&stu.itemCount, 0, 24);
    stu.itemId = *__gnu_cxx::__normal_iterator<int const*,std::vector<int>>::operator*(&it);
    stu.itemCount = 1;
    stu.bind = 1;
    std::vector<MemChrBag>::push_back(&addItem, &stu);
  }
  Bag = Player::GetBag(player);
  if ( !CExtCharBag::AddItem(Bag, &addItem, ITEM_CHANGE_REASON::ICR_TIAN_JIANG_BAO_XIANG_DAILY_REWARD) )
  {
    v2 = 10002;
  }
  else
  {
    RewardRecord.IsGetSpecial = 1;
    __k[0] = Player::getCid(player);
    v4 = std::map<long,ActivityRewardRecord>::operator[](&this->m_PlayerSoreMap, __k);
    *v4 = RewardRecord;
    (*((void (__fastcall **)(CTianJiangBaoXiang *const, Player *))this->_vptr_CActivity + 51))(this, player);
    v2 = 0;
  }
  std::vector<MemChrBag>::~vector(&addItem);
  return v2;
}


#####################################
void __cdecl CTianJiangBaoXiang::onPlantGather(CTianJiangBaoXiang *const this, PlantActivity *pPlant, Player *player)
{
  void (__fastcall *v3)(CTianJiangBaoXiang *const, Player *); // rbx
  Player *v4; // rdx
  ActivityRewardRecord *v5; // rax
  int8_t ConnId; // bl
  DBService *v7; // rax
  LogActivity logActivity; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<Player*> it; // [rsp+40h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+50h] [rbp-20h] BYREF
  __int64 __k[3]; // [rsp+58h] [rbp-18h] BYREF

  if ( pPlant && player )
  {
    if ( Plant::GetPlantType(pPlant) == 1 )
    {
      this->GradeBaoXiangState = 2;
      for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
            ;
            std::_List_iterator<Player *>::operator++(&it) )
      {
        __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
        if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
          break;
        v3 = (void (__fastcall *)(CTianJiangBaoXiang *const, Player *))*((_QWORD *)this->_vptr_CActivity + 51);
        v4 = *std::_List_iterator<Player *>::operator*(&it);
        v3(this, v4);
      }
    }
    else
    {
      __k[0] = Player::getCid(player);
      v5 = std::map<long,ActivityRewardRecord>::operator[](&this->m_PlayerSoreMap, __k);
      ++v5->OpenBaoXiangCount;
      (*((void (__fastcall **)(CTianJiangBaoXiang *const, Player *))this->_vptr_CActivity + 51))(this, player);
    }
    *(&logActivity.time + 1) = 0;
    logActivity.cid = Player::getCid(player);
    logActivity.actid = CActivity::GetId(this);
    logActivity.acttype = CActivity::GetType(this);
    logActivity.time = Unit::getNow(player);
    logActivity.param = Plant::getPlantId(pPlant);
    ConnId = Player::getConnId(player);
    v7 = Answer::Singleton<DBService>::instance();
    DBService::InsertActivityLog(v7, ConnId, &logActivity);
  }
}


#####################################
int32_t __cdecl CTianJiangBaoXiang::onBeginGather(CTianJiangBaoXiang *const this, PlantActivity *plant, Player *player)
{
  int32_t OpenBaoXiangCount; // ebx
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > it; // [rsp+20h] [rbp-30h] BYREF
  __int64 __x; // [rsp+28h] [rbp-28h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > v8; // [rsp+30h] [rbp-20h] BYREF

  if ( !player || !plant )
    return 2;
  if ( Plant::GetPlantType(plant) == 1 )
    return 0;
  __x = Player::getCid(player);
  it._M_node = std::map<long,ActivityRewardRecord>::find(&this->m_PlayerSoreMap, &__x)._M_node;
  v8._M_node = std::map<long,ActivityRewardRecord>::end(&this->m_PlayerSoreMap)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator!=(&it, &v8) )
    return 0;
  OpenBaoXiangCount = std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it)->second.OpenBaoXiangCount;
  if ( OpenBaoXiangCount < std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it)->second.BuyCount
                         + 10 )
    return 0;
  return 2;
}


#####################################
bool __cdecl CTianJiangBaoXiang::AddOpenCount(CTianJiangBaoXiang *const this, Player *player, int32_t AddCount)
{
  std::pair<const long int,ActivityRewardRecord> *v4; // rax
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > it; // [rsp+20h] [rbp-20h] BYREF
  __int64 __x; // [rsp+28h] [rbp-18h] BYREF
  std::_Rb_tree_iterator<std::pair<const long int,ActivityRewardRecord> > v8; // [rsp+30h] [rbp-10h] BYREF

  if ( this->m_nState != ACTIVITY_STATE::AS_RUNNING || !player )
    return 0;
  __x = Player::getCid(player);
  it._M_node = std::map<long,ActivityRewardRecord>::find(&this->m_PlayerSoreMap, &__x)._M_node;
  v8._M_node = std::map<long,ActivityRewardRecord>::end(&this->m_PlayerSoreMap)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator!=(&it, &v8) )
    return 0;
  if ( AddCount + std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it)->second.BuyCount > 5 )
    return 0;
  v4 = std::_Rb_tree_iterator<std::pair<long const,ActivityRewardRecord>>::operator->(&it);
  v4->second.BuyCount += AddCount;
  return 1;
}


#####################################
void __cdecl CTianJiangBaoXiang::broadcastReady(CTianJiangBaoXiang *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 142);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


#####################################
void __cdecl CTianJiangBaoXiang::broadcastStart(CTianJiangBaoXiang *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  GameService *v3; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 143);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v3 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v3, 0, packet);
  }
}


