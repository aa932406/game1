// Decompiled methods for class: CSevenDayTask
// Source: gameserver.cc
// Total methods: 15

#####################################
void __cdecl CSevenDayTask::~CSevenDayTask(CSevenDayTask *const this)
{
  CSevenDayTask::~CSevenDayTask(this);
  operator delete(this);
}


#####################################
void __cdecl CSevenDayTask::OnLoadFromDB(CSevenDayTask *const this, const PlayerDBData *const dbData)
{
  if ( this->m_pPlayer )
  {
    this->m_OpenTime = dbData->m_CSevenDayData.m_OpenTime;
    std::map<int,int>::operator=(&this->m_RewardState, &dbData->m_CSevenDayData.m_RewardState);
    this->m_SumRewardState = dbData->m_CSevenDayData.m_SumRewardState;
    this->m_DiffDay = Answer::DayTime::Diff24Hour(this->m_OpenTime) + 1;
    CSevenDayTask::OpenSevenDayTask(this);
  }
}


#####################################
void __cdecl CSevenDayTask::OnSaveToDB(CSevenDayTask *const this, PlayerDBData *const dbData)
{
  dbData->m_CSevenDayData.m_OpenTime = this->m_OpenTime;
  std::map<int,int>::operator=(&dbData->m_CSevenDayData.m_RewardState, &this->m_RewardState);
  dbData->m_CSevenDayData.m_SumRewardState = this->m_SumRewardState;
}


#####################################
void __cdecl CSevenDayTask::GetInterestsProtocol(CSevenDayTask *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 567;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 568;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 569;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CSevenDayTask::DispatchNetDatas(
        CSevenDayTask *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x238u:
      CSevenDayTask::OnAskReward(this, inPacket);
      break;
    case 0x239u:
      CSevenDayTask::OnAskSumReward(this, inPacket);
      break;
    case 0x237u:
      CSevenDayTask::SendTaskSTate(this);
      break;
    default:
      return 2;
  }
  return 0;
}


#####################################
void __cdecl CSevenDayTask::OnCleanUp(CSevenDayTask *const this)
{
  this->m_OpenTime = 0;
  std::map<int,int>::clear(&this->m_RewardState);
  this->m_LastUpdateTick = 0;
  this->m_SumRewardState = 0;
  this->m_bShowIcon = 0;
  this->m_DiffDay = 0;
}


#####################################
void __cdecl CSevenDayTask::OnUpdate(CSevenDayTask *const this, int64_t curTick)
{
  int DiffDay; // [rsp+1Ch] [rbp-4h]

  if ( curTick - this->m_LastUpdateTick > 1000 && this->m_bShowIcon && this->m_OpenTime > 0 )
  {
    if ( Answer::DayTime::Diff24Hour(this->m_OpenTime) + 1 > 7 && CSevenDayTask::HaveRewardCount(this) <= 0 )
    {
      CSevenDayTask::SendIcon(this);
      this->m_bShowIcon = 0;
    }
    DiffDay = Answer::DayTime::Diff24Hour(this->m_OpenTime) + 1;
    if ( this->m_DiffDay != DiffDay )
    {
      this->m_DiffDay = DiffDay;
      CSevenDayTask::SendIcon(this);
    }
    this->m_LastUpdateTick = curTick;
  }
}


#####################################
int32_t __cdecl CSevenDayTask::OnAskReward(CSevenDayTask *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const SevenTaskTable *SevenTaskTable; // rax
  MemChrBag *p_Item; // rbx
  CExtCharBag *Bag; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  int32_t nId; // [rsp+1Ch] [rbp-24h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  const SevenTaskCfg *pSevenTaskCfg; // [rsp+28h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  SevenTaskTable = CfgData::GetSevenTaskTable(v3);
  pSevenTaskCfg = SevenTaskTable::GetSevenTaskCfg(SevenTaskTable, nId);
  if ( !pSevenTaskCfg )
    return 10002;
  it._M_node = std::map<int,int>::find(&this->m_RewardState, &nId)._M_node;
  __x._M_node = std::map<int,int>::end(&this->m_RewardState)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
    return 10002;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second > 0 )
    return 10002;
  p_Item = &pSevenTaskCfg->Item;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_Item, ITEM_CHANGE_REASON::IDCR_SEVEN_DAY) )
    return 10002;
  std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second = 1;
  CSevenDayTask::SendIcon(this);
  CSevenDayTask::SendTaskSTate(this);
  return 0;
}


#####################################
int32_t __cdecl CSevenDayTask::OnAskSumReward(CSevenDayTask *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const SevenTaskTable *SevenTaskTable; // rax
  CExtCharBag *Bag; // rax
  int8_t ConnId; // bl
  GameService *v7; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v10; // bl
  GameService *v11; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  int32_t nId; // [rsp+24h] [rbp-2Ch]
  const SevenTaskSumReward *pSevenTaskSumReward; // [rsp+28h] [rbp-28h]
  int32_t NewSumRewardState; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  SevenTaskTable = CfgData::GetSevenTaskTable(v3);
  pSevenTaskSumReward = SevenTaskTable::GetSevenTaskSumReward(SevenTaskTable, nId);
  if ( !pSevenTaskSumReward )
    return 10002;
  if ( (int)std::map<int,int>::size(&this->m_RewardState) < pSevenTaskSumReward->nFinishCount )
    return 10002;
  NewSumRewardState = (1 << (nId - 1)) | this->m_SumRewardState;
  if ( this->m_SumRewardState == NewSumRewardState )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pSevenTaskSumReward->Item, ITEM_CHANGE_REASON::IDCR_SEVEN_DAY) )
    return 10002;
  this->m_SumRewardState = NewSumRewardState;
  CSevenDayTask::SendIcon(this);
  CSevenDayTask::SendTaskSTate(this);
  if ( pSevenTaskSumReward->GongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v7 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pSevenTaskSumReward->GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v10 = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v11, v10, packet);
    }
  }
  return 0;
}


#####################################
void __cdecl CSevenDayTask::UpdateTaskState(CSevenDayTask *const this, int32_t nType, int32_t Values, bool NeedSend)
{
  CfgData *v4; // rax
  const SevenTaskTable *SevenTaskTable; // rax
  const SevenTaskCfgMap *SevenTaskCfgMap; // rax
  const std::pair<const int,SevenTaskCfg> *v7; // rax
  const std::pair<const int,SevenTaskCfg> *v8; // rax
  const std::pair<const int,SevenTaskCfg> *v10; // rax
  const std::pair<const int,SevenTaskCfg> *v11; // rax
  SevenTaskCfgMap TaskCfgMap; // [rsp+20h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > itState; // [rsp+50h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SevenTaskCfg> > it; // [rsp+60h] [rbp-50h] BYREF
  Int32List NeedSendId; // [rsp+70h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SevenTaskCfg> > v19; // [rsp+80h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+90h] [rbp-20h] BYREF
  int32_t DiffDay; // [rsp+9Ch] [rbp-14h]

  if ( this->m_OpenTime > 0 )
  {
    DiffDay = Answer::DayTime::Diff24Hour(this->m_OpenTime) + 1;
    if ( DiffDay <= 7 )
    {
      std::list<int>::list(&NeedSendId);
      v4 = Answer::Singleton<CfgData>::instance();
      SevenTaskTable = CfgData::GetSevenTaskTable(v4);
      SevenTaskCfgMap = SevenTaskTable::GetSevenTaskCfgMap(SevenTaskTable);
      std::map<int,SevenTaskCfg>::map(&TaskCfgMap, SevenTaskCfgMap);
      for ( it._M_node = std::map<int,SevenTaskCfg>::begin(&TaskCfgMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator++(&it, 0) )
      {
        v19._M_node = std::map<int,SevenTaskCfg>::end(&TaskCfgMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator!=(&it, &v19) )
          break;
        v7 = std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator->(&it);
        itState._M_node = std::map<int,int>::find(&this->m_RewardState, &v7->first)._M_node;
        __x._M_node = std::map<int,int>::end(&this->m_RewardState)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&itState, &__x) )
        {
          v8 = std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator->(&it);
          if ( v8->second.nEndDay >= DiffDay
            && std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator->(&it)->second.nType == nType
            && std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator->(&it)->second.nCondition <= Values )
          {
            v10 = std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator->(&it);
            *std::map<int,int>::operator[](&this->m_RewardState, &v10->first) = 0;
            v11 = std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskCfg>>::operator->(&it);
            std::list<int>::push_back(&NeedSendId, &v11->first);
          }
        }
      }
      if ( NeedSend && std::list<int>::size(&NeedSendId) )
      {
        CSevenDayTask::SendIcon(this);
        CSevenDayTask::SendTaskSTate(this);
      }
      std::map<int,SevenTaskCfg>::~map(&TaskCfgMap);
      std::list<int>::~list(&NeedSendId);
    }
  }
}


#####################################
void __cdecl CSevenDayTask::SendTaskSTate(CSevenDayTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC8u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_OpenTime);
      v3 = std::map<int,int>::size(&this->m_RewardState);
      Answer::NetPacket::writeInt32(packet, v3);
      for ( it._M_node = std::map<int,int>::begin(&this->m_RewardState)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_RewardState)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->first);
        v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->second);
      }
      Answer::NetPacket::writeInt32(packet, this->m_SumRewardState);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CSevenDayTask::OpenSevenDayTask(CSevenDayTask *const this)
{
  CfgData *v1; // rax
  int32_t v2; // edx
  int32_t Record; // edx
  CExtCharWing *CharWing; // rax
  int32_t Level; // edx
  CExtCharJueWei *CharJueWei; // rax
  int32_t JueWei; // edx
  CExtEquip *Equip; // rax
  int32_t EquipAllGemLevel; // edx
  CExtEquip *v10; // rax
  int32_t EquipAllUpPosLevel; // edx

  if ( this->m_pPlayer
    && (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) > 99
    && this->m_OpenTime <= 0 )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL) + 1 <= 7 )
    {
      this->m_OpenTime = Unit::getNow(this->m_pPlayer);
      v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      CSevenDayTask::UpdateTaskState(this, 1, v2, 0);
      Record = Player::getRecord(this->m_pPlayer, 1148);
      CSevenDayTask::UpdateTaskState(this, 2, Record, 0);
      CharWing = Player::GetCharWing(this->m_pPlayer);
      Level = CExtCharWing::GetLevel(CharWing);
      CSevenDayTask::UpdateTaskState(this, 3, Level, 0);
      CharJueWei = Player::GetCharJueWei(this->m_pPlayer);
      JueWei = CExtCharJueWei::GetJueWei(CharJueWei);
      CSevenDayTask::UpdateTaskState(this, 4, JueWei, 0);
      Equip = Player::GetEquip(this->m_pPlayer);
      EquipAllGemLevel = CExtEquip::GetEquipAllGemLevel(Equip);
      CSevenDayTask::UpdateTaskState(this, 5, EquipAllGemLevel, 0);
      v10 = Player::GetEquip(this->m_pPlayer);
      EquipAllUpPosLevel = CExtEquip::GetEquipAllUpPosLevel(v10);
      CSevenDayTask::UpdateTaskState(this, 6, EquipAllUpPosLevel, 0);
      CSevenDayTask::SendIcon(this);
      CSevenDayTask::SendTaskSTate(this);
    }
  }
}


#####################################
void __cdecl CSevenDayTask::GetIcon(CSevenDayTask *const this, IconStateList *const IconList)
{
  bool v2; // al
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF
  int32_t DiffDay; // [rsp+2Ch] [rbp-4h]

  if ( this->m_pPlayer )
  {
    DiffDay = Answer::DayTime::Diff24Hour(this->m_OpenTime) + 1;
    v2 = DiffDay > 7 && CSevenDayTask::HaveRewardCount(this) <= 0;
    if ( !v2 && this->m_OpenTime > 0 )
    {
      CSevenDayTask::GetIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CSevenDayTask::SendIcon(CSevenDayTask *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( this->m_OpenTime > 0 )
    {
      CSevenDayTask::GetIcon(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
int32_t __cdecl CSevenDayTask::HaveRewardCount(CSevenDayTask *const this)
{
  int first; // ebx
  CfgData *v2; // rax
  const SevenTaskTable *SevenTaskTable; // rax
  CfgData *v4; // rax
  const SevenTaskTable *v5; // rax
  const SevenTaskSumRewardMap *SevenTaskSumRewardMap; // rax
  const std::pair<const int,SevenTaskSumReward> *v7; // rax
  int32_t m_SumRewardState; // ebx
  int32_t v10; // ebx
  SevenTaskSumRewardMap TaskCfgMap; // [rsp+10h] [rbp-90h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SevenTaskSumReward> > iter; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+50h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+60h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,SevenTaskSumReward> > v16; // [rsp+70h] [rbp-30h] BYREF
  int32_t DiffDay; // [rsp+7Ch] [rbp-24h]
  int32_t Count; // [rsp+80h] [rbp-20h]
  int32_t FinishCount; // [rsp+84h] [rbp-1Ch]
  const SevenTaskCfg *pSevenTaskCfg; // [rsp+88h] [rbp-18h]

  DiffDay = Answer::DayTime::Diff24Hour(this->m_OpenTime) + 1;
  Count = 0;
  FinishCount = 0;
  for ( it._M_node = std::map<int,int>::begin(&this->m_RewardState)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,int>::end(&this->m_RewardState)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    first = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->first;
    v2 = Answer::Singleton<CfgData>::instance();
    SevenTaskTable = CfgData::GetSevenTaskTable(v2);
    pSevenTaskCfg = SevenTaskTable::GetSevenTaskCfg(SevenTaskTable, first);
    if ( pSevenTaskCfg )
    {
      if ( pSevenTaskCfg->nStartDay <= DiffDay )
      {
        ++FinishCount;
        if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second <= 0 )
          ++Count;
      }
    }
  }
  v4 = Answer::Singleton<CfgData>::instance();
  v5 = CfgData::GetSevenTaskTable(v4);
  SevenTaskSumRewardMap = SevenTaskTable::GetSevenTaskSumRewardMap(v5);
  std::map<int,SevenTaskSumReward>::map(&TaskCfgMap, SevenTaskSumRewardMap);
  for ( iter._M_node = std::map<int,SevenTaskSumReward>::begin(&TaskCfgMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskSumReward>>::operator++(&iter, 0) )
  {
    v16._M_node = std::map<int,SevenTaskSumReward>::end(&TaskCfgMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskSumReward>>::operator!=(&iter, &v16) )
      break;
    v7 = std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskSumReward>>::operator->(&iter);
    if ( v7->second.nFinishCount <= FinishCount )
    {
      m_SumRewardState = this->m_SumRewardState;
      if ( (m_SumRewardState
          & (1 << (LOBYTE(std::_Rb_tree_const_iterator<std::pair<int const,SevenTaskSumReward>>::operator->(&iter)->first)
                 - 1))) <= 0 )
        ++Count;
    }
  }
  v10 = Count;
  std::map<int,SevenTaskSumReward>::~map(&TaskCfgMap);
  return v10;
}


