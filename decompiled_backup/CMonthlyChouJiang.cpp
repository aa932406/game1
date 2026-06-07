// Decompiled methods for class: CMonthlyChouJiang
// Source: gameserver.cc
// Total methods: 18

#####################################
void __cdecl CMonthlyChouJiang::~CMonthlyChouJiang(CMonthlyChouJiang *const this)
{
  CMonthlyChouJiang::~CMonthlyChouJiang(this);
  operator delete(this);
}


#####################################
void __cdecl CMonthlyChouJiang::OnLoadFromDB(CMonthlyChouJiang *const this, const PlayerDBData *const dbData)
{
  this->m_Score = dbData->m_CMonthlyChouJiangData.m_Score;
  this->m_AllScore = dbData->m_CMonthlyChouJiangData.m_AllScore;
  std::list<int>::operator=(&this->m_GetItemList, &dbData->m_CMonthlyChouJiangData.m_GetItemList);
  std::map<int,int>::operator=(&this->m_GetTimes, &dbData->m_CMonthlyChouJiangData.m_GetTimes);
}


#####################################
void __cdecl CMonthlyChouJiang::OnSaveToDB(CMonthlyChouJiang *const this, PlayerDBData *const dbData)
{
  dbData->m_CMonthlyChouJiangData.m_Score = this->m_Score;
  dbData->m_CMonthlyChouJiangData.m_AllScore = this->m_AllScore;
  std::list<int>::operator=(&dbData->m_CMonthlyChouJiangData.m_GetItemList, &this->m_GetItemList);
  std::map<int,int>::operator=(&dbData->m_CMonthlyChouJiangData.m_GetTimes, &this->m_GetTimes);
}


#####################################
void __cdecl CMonthlyChouJiang::GetInterestsProtocol(CMonthlyChouJiang *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 522;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 523;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CMonthlyChouJiang::DispatchNetDatas(
        CMonthlyChouJiang *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( nProcId == 522 )
    return CMonthlyChouJiang::OnAskMonthlyChouJiangInfo(this, inPacket);
  if ( nProcId == 523 )
    return CMonthlyChouJiang::OnMonthlyChouJiang(this, inPacket);
  return 2;
}


#####################################
void __cdecl CMonthlyChouJiang::OnCleanUp(CMonthlyChouJiang *const this)
{
  this->m_Score = 0;
  this->m_AllScore = 0;
  std::list<int>::clear(&this->m_GetItemList);
  std::map<int,int>::clear(&this->m_GetTimes);
}


#####################################
void __cdecl CMonthlyChouJiang::OnDaySwitch(CMonthlyChouJiang *const this, int32_t nDiffDays)
{
  CMonthlyChouJiang::SendIcon(this);
  CMonthlyChouJiang::SendMonthlyChouJiangInfo(this);
}


#####################################
int32_t __cdecl CMonthlyChouJiang::GetKaiFuMonth(CMonthlyChouJiang *const this)
{
  CfgData *v2; // rax
  tm Time; // [rsp+10h] [rbp-50h] BYREF
  int32_t nKaiFuTime; // [rsp+54h] [rbp-Ch]
  int32_t nNowTime; // [rsp+58h] [rbp-8h]
  int32_t DiffMonth; // [rsp+5Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  v2 = Answer::Singleton<CfgData>::instance();
  nKaiFuTime = CfgData::getServerStartTime(v2, SERVER_TYPE::SVT_NORMAL);
  Answer::DayTime::localnow(&Time, nKaiFuTime);
  nNowTime = Unit::getNow(this->m_pPlayer);
  DiffMonth = Answer::DayTime::monthdiff(nKaiFuTime) + 1;
  if ( nNowTime <= 1567267199 )
    return 0;
  if ( Time.tm_mday > 16 )
    --DiffMonth;
  if ( DiffMonth <= 0 )
    DiffMonth = 1;
  if ( DiffMonth > 12 )
    return 12;
  return DiffMonth;
}


#####################################
int32_t __cdecl CMonthlyChouJiang::OnMonthlyChouJiang(CMonthlyChouJiang *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  int32_t KaiFuMonth; // r12d
  CfgData *v5; // rax
  const MonthlyChouJiangTable *MonthlyChouJiangTable; // rax
  CExtCharBag *v7; // rax
  int8_t ConnId; // bl
  GameService *v9; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v12; // bl
  GameService *v13; // rax
  MemChrBag stu; // [rsp+10h] [rbp-80h] BYREF
  RateItem Item; // [rsp+30h] [rbp-60h] BYREF
  std::string val; // [rsp+50h] [rbp-40h] BYREF
  int32_t LastId; // [rsp+64h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+68h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( this->m_Score <= 99 )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  KaiFuMonth = CMonthlyChouJiang::GetKaiFuMonth(this);
  v5 = Answer::Singleton<CfgData>::instance();
  MonthlyChouJiangTable = CfgData::GetMonthlyChouJiangTable(v5);
  MonthlyChouJiangTable::RandRateItem(&Item, MonthlyChouJiangTable, KaiFuMonth, &this->m_GetItemList);
  if ( Item.nItemClass <= 0 || Item.nItemCount <= 0 || Item.nItemId <= 0 )
    return 2;
  *(&stu.endTime + 1) = 0;
  stu.srcId = 0;
  *(_DWORD *)&stu.itemClass = (unsigned __int8)Item.nItemClass;
  stu.itemCount = Item.nItemCount;
  stu.itemId = Item.nItemId;
  *(_QWORD *)&stu.bind = (unsigned __int8)Item.nBind;
  v7 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::AddItem(v7, &stu, ITEM_CHANGE_REASON::IDR_MONTHLY_CHOU_JIANG);
  this->m_Score -= 100;
  LastId = *std::list<int>::back(&this->m_GetItemList);
  CMonthlyChouJiang::SendMonthlyChouJiangResult(this, LastId);
  if ( Item.nGongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v9, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, Item.nGongGaoId);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, stu.itemId);
      Answer::NetPacket::writeInt8(packet, stu.itemClass);
      Answer::NetPacket::writeInt32(packet, stu.itemCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v13, v12, packet);
    }
  }
  CMonthlyChouJiang::SendIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CMonthlyChouJiang::OnAskMonthlyChouJiangInfo(
        CMonthlyChouJiang *const this,
        Answer::NetPacket *inPacket)
{
  CMonthlyChouJiang::SendMonthlyChouJiangInfo(this);
  return 0;
}


#####################################
void __cdecl CMonthlyChouJiang::OnMonthlySwitch(CMonthlyChouJiang *const this)
{
  (*this->_vptr_IExtSystem)(this);
  CMonthlyChouJiang::SendMonthlyChouJiangInfo(this);
  CMonthlyChouJiang::SendIcon(this);
}


#####################################
void __cdecl CMonthlyChouJiang::OnChongZhi(CMonthlyChouJiang *const this, int32_t NewValues, int32_t OldValues)
{
  CfgData *v3; // rax
  CfgData *v4; // rax
  const MonthlyChouJiangTable *MonthlyChouJiangTable; // rax
  const MonthlyChouJiangCfgMap *MonthlyChouJiangCfgMap; // rax
  int first; // edx
  int32_t SocreTimes; // ebx
  const std::pair<const int,MonthlyChouJiangCfg> *v10; // rax
  int *v11; // rax
  int32_t m_Score; // ebx
  int32_t m_AllScore; // ebx
  MonthlyChouJiangCfgMap stu; // [rsp+10h] [rbp-80h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MonthlyChouJiangCfg> > it; // [rsp+40h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonthlyChouJiangCfg> > __it; // [rsp+50h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MonthlyChouJiangCfg> > __x; // [rsp+60h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonthlyChouJiangCfg> > v19; // [rsp+70h] [rbp-20h] BYREF

  v3 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) >= 0 )
  {
    v4 = Answer::Singleton<CfgData>::instance();
    MonthlyChouJiangTable = CfgData::GetMonthlyChouJiangTable(v4);
    MonthlyChouJiangCfgMap = MonthlyChouJiangTable::GetMonthlyChouJiangCfgMap(MonthlyChouJiangTable);
    std::map<int,MonthlyChouJiangCfg>::map(&stu, MonthlyChouJiangCfgMap);
    __it._M_node = std::map<int,MonthlyChouJiangCfg>::begin(&stu)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::_Rb_tree_const_iterator(&it, &__it);
    while ( 1 )
    {
      v19._M_node = std::map<int,MonthlyChouJiangCfg>::end(&stu)._M_node;
      std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::_Rb_tree_const_iterator(&__x, &v19);
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator!=(&it, &__x) )
        break;
      if ( std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->second.nRecharges > OldValues
        && std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->second.nRecharges <= NewValues )
      {
        first = std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->first;
        SocreTimes = CMonthlyChouJiang::GetSocreTimes(this, first);
        if ( SocreTimes < std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->second.nGetTimes )
        {
          v10 = std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it);
          v11 = std::map<int,int>::operator[](&this->m_GetTimes, &v10->first);
          ++*v11;
          m_Score = this->m_Score;
          this->m_Score = m_Score
                        + std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->second.nAddValues;
          m_AllScore = this->m_AllScore;
          this->m_AllScore = m_AllScore
                           + std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->second.nAddValues;
        }
      }
      std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator++(&it, 0);
    }
    std::map<int,MonthlyChouJiangCfg>::~map(&stu);
  }
}


#####################################
void __cdecl CMonthlyChouJiang::SendMonthlyChouJiangInfo(CMonthlyChouJiang *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t TodayPayGold; // eax
  int32_t v4; // eax
  int *v5; // rax
  int32_t v6; // eax
  std::pair<const int,int> *v7; // rax
  std::pair<const int,int> *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > itMap; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<int> it; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v16; // [rsp+40h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDBu);
    if ( packet )
    {
      TodayPayGold = Player::GetTodayPayGold(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, TodayPayGold);
      Answer::NetPacket::writeInt32(packet, this->m_Score);
      Answer::NetPacket::writeInt32(packet, this->m_AllScore);
      v4 = std::list<int>::size(&this->m_GetItemList);
      Answer::NetPacket::writeInt32(packet, v4);
      for ( it._M_node = std::list<int>::begin(&this->m_GetItemList)._M_node; ; std::_List_iterator<int>::operator++(&it) )
      {
        __x._M_node = std::list<int>::end(&this->m_GetItemList)._M_node;
        if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
          break;
        v5 = std::_List_iterator<int>::operator*(&it);
        Answer::NetPacket::writeInt32(packet, *v5);
      }
      v6 = std::map<int,int>::size(&this->m_GetTimes);
      Answer::NetPacket::writeInt32(packet, v6);
      for ( itMap._M_node = std::map<int,int>::begin(&this->m_GetTimes)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itMap, 0) )
      {
        v16._M_node = std::map<int,int>::end(&this->m_GetTimes)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itMap, &v16) )
          break;
        v7 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
        Answer::NetPacket::writeInt32(packet, v7->first);
        v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itMap);
        Answer::NetPacket::writeInt32(packet, v8->second);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v11 = Player::getConnId(this->m_pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CMonthlyChouJiang::SendMonthlyChouJiangResult(CMonthlyChouJiang *const this, int32_t nId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDCu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nId);
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
int32_t __cdecl CMonthlyChouJiang::GetSocreTimes(CMonthlyChouJiang *const this, int32_t nId)
{
  int32_t nIda; // [rsp+4h] [rbp-2Ch] BYREF
  CMonthlyChouJiang *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nIda = nId;
  it._M_node = std::map<int,int>::find(&this->m_GetTimes, &nIda)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_GetTimes)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
void __cdecl CMonthlyChouJiang::GetIcon(CMonthlyChouJiang *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  CfgData *v3; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 210) )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      if ( CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) >= 0 )
      {
        CMonthlyChouJiang::GetIcon(&icon, this);
        std::list<ShowIcon>::push_back(IconList, &icon);
      }
    }
  }
}


#####################################
void __cdecl CMonthlyChouJiang::SendIcon(CMonthlyChouJiang *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  CfgData *v2; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 210) )
    {
      v2 = Answer::Singleton<CfgData>::instance();
      if ( CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_NORMAL) >= 0 )
      {
        CMonthlyChouJiang::GetIcon(&icon, this);
        Player::SendIconState(this->m_pPlayer, &icon);
      }
    }
  }
}


#####################################
bool __cdecl CMonthlyChouJiang::TodaySocreIsAllGet(CMonthlyChouJiang *const this)
{
  CfgData *v1; // rax
  const MonthlyChouJiangTable *MonthlyChouJiangTable; // rax
  const MonthlyChouJiangCfgMap *MonthlyChouJiangCfgMap; // rax
  const std::pair<const int,MonthlyChouJiangCfg> *v4; // rax
  int first; // edx
  int32_t SocreTimes; // ebx
  bool v8; // bl
  MonthlyChouJiangCfgMap stu; // [rsp+10h] [rbp-80h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MonthlyChouJiangCfg> > it; // [rsp+40h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonthlyChouJiangCfg> > __it; // [rsp+50h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,MonthlyChouJiangCfg> > __x; // [rsp+60h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonthlyChouJiangCfg> > v14; // [rsp+70h] [rbp-20h] BYREF
  int32_t TodayPay; // [rsp+7Ch] [rbp-14h]

  TodayPay = Player::GetTodayPayGold(this->m_pPlayer);
  v1 = Answer::Singleton<CfgData>::instance();
  MonthlyChouJiangTable = CfgData::GetMonthlyChouJiangTable(v1);
  MonthlyChouJiangCfgMap = MonthlyChouJiangTable::GetMonthlyChouJiangCfgMap(MonthlyChouJiangTable);
  std::map<int,MonthlyChouJiangCfg>::map(&stu, MonthlyChouJiangCfgMap);
  __it._M_node = std::map<int,MonthlyChouJiangCfg>::begin(&stu)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::_Rb_tree_const_iterator(&it, &__it);
  while ( 1 )
  {
    v14._M_node = std::map<int,MonthlyChouJiangCfg>::end(&stu)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::_Rb_tree_const_iterator(&__x, &v14);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator!=(&it, &__x) )
      break;
    v4 = std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it);
    if ( v4->second.nRecharges > TodayPay )
    {
      first = std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->first;
      SocreTimes = CMonthlyChouJiang::GetSocreTimes(this, first);
      if ( SocreTimes < std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator->(&it)->second.nGetTimes )
      {
        v8 = 0;
        goto LABEL_11;
      }
    }
    std::_Rb_tree_const_iterator<std::pair<int const,MonthlyChouJiangCfg>>::operator++(&it, 0);
  }
  v8 = 1;
LABEL_11:
  std::map<int,MonthlyChouJiangCfg>::~map(&stu);
  return v8;
}


