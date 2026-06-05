// Decompiled methods for class: DailyActivity
// Source: gameserver.cc
// Total methods: 68

#####################################
void __cdecl DailyActivity::~DailyActivity(DailyActivity *const this)
{
  DailyActivity::~DailyActivity(this);
  operator delete(this);
}


#####################################
void __cdecl DailyActivity::OnCleanUp(DailyActivity *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  MemChrSignInfo::CleanUp(&this->m_signInfo);
  this->m_LastUpdate = 0;
  this->m_LastUpdateIcon = 0;
  this->m_IsLogin = 0;
  std::list<SearchBackInfo>::clear(&this->m_lstTodayInfo);
  for ( i = 0; i <= 2; ++i )
    std::list<SearchBackRecord>::clear(&this->m_vSeachBackRecord[i]);
  std::map<int,int>::clear(&this->m_OnlimeTimeGetReward);
}


#####################################
void __cdecl DailyActivity::OnUpdate(DailyActivity *const this, int64_t curTick)
{
  int32_t Record; // eax
  int32_t v3; // eax
  Player *m_pPlayer; // rbx
  CFestivalDoubleEleven *v5; // rax
  Player *v6; // rbx
  COpenBeta *v7; // rax

  if ( this->m_pPlayer )
  {
    if ( curTick - this->m_LastUpdate > 999 )
    {
      Record = Player::getRecord(this->m_pPlayer, 2003);
      Player::updateRecord(this->m_pPlayer, 2003, Record + 1);
      v3 = Player::getRecord(this->m_pPlayer, 1016);
      Player::updateRecord(this->m_pPlayer, 1016, v3 + 1);
      m_pPlayer = this->m_pPlayer;
      v5 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      CFestivalDoubleEleven::AddOnlineRecord(v5, m_pPlayer);
      v6 = this->m_pPlayer;
      v7 = Answer::Singleton<COpenBeta>::instance();
      COpenBeta::AddOnlineRecord(v7, v6);
      this->m_LastUpdate = curTick;
    }
    DailyActivity::UpDateJiangLiDatingIcon(this, curTick);
  }
}


#####################################
void __cdecl DailyActivity::OnLoadFromDB(DailyActivity *const this, const PlayerDBData *const dbData)
{
  std::string p_OnlineReward; // [rsp+10h] [rbp-20h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-14h]

  MemChrSignInfo::operator=(&this->m_signInfo, &dbData->signInfo.data);
  std::list<SearchBackInfo>::operator=(&this->m_lstTodayInfo, &dbData->signInfo.lstTodayInfo);
  for ( i = 0; i <= 2; ++i )
    std::list<SearchBackRecord>::operator=(
      &this->m_vSeachBackRecord[i],
      (const std::list<SearchBackRecord> *const)&dbData->signInfo.lstTodayInfo._M_impl + i + 1);
  std::string::string(&p_OnlineReward, &dbData->signInfo.OnlimeReward);
  DailyActivity::PasOnlineReward(this, &p_OnlineReward);
  std::string::~string(&p_OnlineReward);
}


#####################################
void __cdecl DailyActivity::OnSaveToDB(DailyActivity *const this, PlayerDBData *const dbData)
{
  _BYTE v2[12]; // [rsp+10h] [rbp-20h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-14h]

  MemChrSignInfo::operator=(&dbData->signInfo.data, &this->m_signInfo);
  std::list<SearchBackInfo>::operator=(&dbData->signInfo.lstTodayInfo, &this->m_lstTodayInfo);
  for ( i = 0; i <= 2; ++i )
    std::list<SearchBackRecord>::operator=(
      (std::list<SearchBackRecord> *const)&dbData->signInfo.lstTodayInfo._M_impl + i + 1,
      &this->m_vSeachBackRecord[i]);
  DailyActivity::GetOnlineReward((DailyActivity *const)v2);
  std::string::operator=(&dbData->signInfo.OnlimeReward, v2);
  std::string::~string(v2);
}


#####################################
void __cdecl DailyActivity::OnDaySwitch(DailyActivity *const this, int32_t nDiffDays)
{
  std::map<int,int>::clear(&this->m_OnlimeTimeGetReward);
  DailyActivity::refreshSignInfo(this);
  DailyActivity::refreshWeekTime(this);
  DailyActivity::refreshSearchBack(this, nDiffDays);
  DailyActivity::SendJiangLiDaTingIcon(this);
  DailyActivity::SendSearchBackIcon(this);
  DailyActivity::SendSevenDayLoginIcon(this);
  DailyActivity::SendSearchBackInfo(this);
}


#####################################
void __cdecl DailyActivity::GetInterestsProtocol(DailyActivity *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-22h] BYREF
  unsigned __int16 v3; // [rsp+20h] [rbp-20h] BYREF
  unsigned __int16 v4; // [rsp+22h] [rbp-1Eh] BYREF
  unsigned __int16 v5; // [rsp+24h] [rbp-1Ch] BYREF
  unsigned __int16 v6; // [rsp+26h] [rbp-1Ah] BYREF
  unsigned __int16 v7; // [rsp+28h] [rbp-18h] BYREF
  unsigned __int16 v8; // [rsp+2Ah] [rbp-16h] BYREF
  unsigned __int16 v9; // [rsp+2Ch] [rbp-14h] BYREF
  unsigned __int16 v10; // [rsp+2Eh] [rbp-12h] BYREF
  unsigned __int16 v11; // [rsp+30h] [rbp-10h] BYREF
  unsigned __int16 v12; // [rsp+32h] [rbp-Eh] BYREF
  unsigned __int16 v13; // [rsp+34h] [rbp-Ch] BYREF
  unsigned __int16 v14; // [rsp+36h] [rbp-Ah] BYREF
  unsigned __int16 v15; // [rsp+38h] [rbp-8h] BYREF
  unsigned __int16 v16; // [rsp+3Ah] [rbp-6h] BYREF
  unsigned __int16 v17; // [rsp+3Ch] [rbp-4h] BYREF
  unsigned __int16 v18; // [rsp+3Eh] [rbp-2h] BYREF

  __x = 73;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 74;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 75;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 475;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 154;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 155;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 156;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 202;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 203;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 459;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 460;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 462;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 476;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 20081;
  std::list<unsigned short>::push_back(procList, &v15);
  v16 = 895;
  std::list<unsigned short>::push_back(procList, &v16);
  v17 = 992;
  std::list<unsigned short>::push_back(procList, &v17);
  v18 = 993;
  std::list<unsigned short>::push_back(procList, &v18);
}


#####################################
int32_t __cdecl DailyActivity::DispatchNetDatas(
        DailyActivity *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 459 )
    return DailyActivity::OnQueryOffLineExpInfo(this, inPacket);
  if ( nProcId > 0x1CBu )
  {
    if ( nProcId == 476 )
      return DailyActivity::OnGetSearchBackReward(this, inPacket);
    if ( nProcId > 0x1DCu )
    {
      if ( nProcId == 992 )
        return DailyActivity::OnGetDogTitle(this, inPacket);
      if ( nProcId > 0x3E0u )
      {
        if ( nProcId == 993 )
          return DailyActivity::OnAskDogTitleInfo(this, inPacket);
        if ( nProcId == 20081 )
          return DailyActivity::RecordEnterNumber(this, inPacket);
      }
      else if ( nProcId == 895 )
      {
        return DailyActivity::OnGetMaintainCompensateReward(this, inPacket);
      }
    }
    else
    {
      switch ( nProcId )
      {
        case 0x1CEu:
          return DailyActivity::OnQueryHuoDaoDaTingData(this, inPacket);
        case 0x1DBu:
          return DailyActivity::onGetSignDailyReward(this, inPacket);
        case 0x1CCu:
          return DailyActivity::OnGetOffLineExp(this, inPacket);
      }
    }
  }
  else
  {
    if ( nProcId == 154 )
      return DailyActivity::OnGetOnLineReward(this, inPacket);
    if ( nProcId > 0x9Au )
    {
      if ( nProcId == 156 )
        return DailyActivity::OnGetWeekOnLineReward(this, inPacket);
      if ( nProcId < 0x9Cu )
        return DailyActivity::OnQueryOnLineInfo(this, inPacket);
      if ( nProcId == 202 )
        return DailyActivity::OnGetSevenLoginRewrad(this, inPacket);
      if ( nProcId == 203 )
        return DailyActivity::OnQuerySevenLoginInfo(this, inPacket);
    }
    else
    {
      switch ( nProcId )
      {
        case 'J':
          return DailyActivity::onSign(this, inPacket);
        case 'K':
          return DailyActivity::onGetSignReward(this, inPacket);
        case 'I':
          return DailyActivity::onQuerySignInfo(this, inPacket);
      }
    }
  }
  return 10002;
}


#####################################
int32_t __cdecl DailyActivity::onGetSignReward(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  char *v3; // rax
  int8_t v4; // bl
  CfgData *v5; // rax
  CExtCharBag *Bag; // rax
  MemChrBagVector items; // [rsp+10h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > it; // [rsp+30h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > __rhs; // [rsp+40h] [rbp-30h] BYREF
  char __x; // [rsp+53h] [rbp-1Dh] BYREF
  int32_t count; // [rsp+54h] [rbp-1Ch]
  int32_t i; // [rsp+58h] [rbp-18h]
  int32_t signCount; // [rsp+5Ch] [rbp-14h]

  if ( !inPacket )
    return 10002;
  count = Answer::NetPacket::readInt32(inPacket);
  i = 0;
  signCount = 0;
  while ( i <= 30 )
    signCount += (this->m_signInfo.sign_record >> i++) & 1;
  if ( signCount < count )
    return 10002;
  for ( it._M_current = std::vector<signed char>::begin(&this->m_signInfo.sign_reward)._M_current;
        ;
        __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<signed char>::end(&this->m_signInfo.sign_reward)._M_current;
    if ( !__gnu_cxx::operator!=<signed char *,std::vector<signed char>>(&it, &__rhs) )
      break;
    v3 = __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator*(&it);
    if ( *v3 == count )
      return 2;
  }
  v4 = count;
  v5 = Answer::Singleton<CfgData>::instance();
  CfgData::GetSignReward(&items, v5, v4);
  if ( std::vector<MemChrBag>::empty(&items) )
  {
    v2 = 2;
  }
  else
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, &items, ITEM_CHANGE_REASON::ICR_SIGN_REWARD) )
    {
      v2 = 2;
    }
    else
    {
      __x = count;
      std::vector<signed char>::push_back(&this->m_signInfo.sign_reward, &__x);
      DailyActivity::sendSignInfo(this);
      DailyActivity::SendJiangLiDaTingIcon(this);
      v2 = 0;
    }
  }
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
int32_t __cdecl DailyActivity::onGetSignDailyReward(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  if ( inPacket )
    return 0;
  else
    return 10002;
}


#####################################
int32_t __cdecl DailyActivity::onQuerySignInfo(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  DailyActivity::sendSignInfo(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnGetOnLineReward(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  Answer::Random *v4; // rax
  MemChrBag *v5; // rbx
  CExtCharBag *Bag; // rax
  int *v7; // rax
  int __k; // [rsp+10h] [rbp-30h] BYREF
  int8_t Id; // [rsp+17h] [rbp-29h]
  CfgOnlineReward *pReward; // [rsp+18h] [rbp-28h]
  int32_t oldRecord; // [rsp+20h] [rbp-20h]
  int32_t NewRecord; // [rsp+24h] [rbp-1Ch]
  int32_t nSize; // [rsp+28h] [rbp-18h]
  int32_t nRand; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Id = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::GetOnlineRewardCfg(v3, Id);
  if ( !pReward )
    return 2;
  if ( DailyActivity::GetTodayOnLineTime(this) < pReward->NeedTime )
    return 2;
  oldRecord = Player::getRecord(this->m_pPlayer, 2004);
  NewRecord = oldRecord | (1 << (Id - 1));
  if ( oldRecord == NewRecord )
    return 10002;
  if ( !std::vector<MemChrBag>::size(&pReward->ItemVector) )
    return 10002;
  nSize = std::vector<MemChrBag>::size(&pReward->ItemVector);
  v4 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v4, 0, nSize - 1);
  v5 = std::vector<MemChrBag>::operator[](&pReward->ItemVector, nRand);
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, v5, ITEM_CHANGE_REASON::ICR_ONLINE_REWAR) )
    return 2;
  __k = Id;
  v7 = std::map<int,int>::operator[](&this->m_OnlimeTimeGetReward, &__k);
  *v7 = nRand;
  Player::updateRecord(this->m_pPlayer, 2004, NewRecord);
  DailyActivity::SendOnlineRewardInfo(this);
  DailyActivity::SendJiangLiDaTingIcon(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnQueryOnLineInfo(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  DailyActivity::SendOnlineRewardInfo(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnGetWeekOnLineReward(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t Now; // ebx
  CharId_t Cid; // rax
  int Week; // [rsp+1Ch] [rbp-24h]
  CfgWeekOnlineReward *pWeekReward; // [rsp+20h] [rbp-20h]
  int32_t LastWeekOnLineHour; // [rsp+28h] [rbp-18h]
  int32_t GetCash; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket )
    return 2;
  Week = DailyActivity::GetNewSeverWeek(this);
  if ( Week <= 1 )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  pWeekReward = CfgData::GetWeekOnlineReward(v3, Week - 1);
  if ( !pWeekReward )
    return 2;
  LastWeekOnLineHour = DailyActivity::GetLastWeekOnlineTime(this) / 3600;
  if ( pWeekReward->UpperLimit < LastWeekOnLineHour )
    LastWeekOnLineHour = pWeekReward->UpperLimit;
  if ( LastWeekOnLineHour <= 0 )
    return 2;
  GetCash = LastWeekOnLineHour * pWeekReward->Cash;
  if ( GetCash <= 0 )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1017, 0);
  if ( !Player::AddCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_CASH,
          GetCash,
          CURRENCY_CHANGE_REASON::GCC_WEEK_ONLINE_REWARD,
          0) )
  {
    Now = Unit::getNow(this->m_pPlayer);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "WEEK ONLINE REWARD ERR Cid=%lld,time=%d,GetCash=%d\n",
      Cid,
      Now,
      GetCash);
  }
  DailyActivity::SendOnlineRewardInfo(this);
  DailyActivity::SendJiangLiDaTingIcon(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnQuerySevenLoginInfo(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  DailyActivity::SendSevenLoginInfo(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnGetSevenLoginRewrad(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  CfgData *v4; // rax
  Job_t Job; // r12
  int32_t Time; // r15d
  CharId_t nCreaterId; // r12
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v11; // rax
  int v12; // r12d
  CExtCharBag *Bag; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v15; // rax
  int32_t nBaseId; // [rsp+4Ch] [rbp-124h]
  MemEquip equip; // [rsp+60h] [rbp-110h] BYREF
  MemChrBag chrbag; // [rsp+A0h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > it; // [rsp+C0h] [rbp-B0h] BYREF
  MemEquipVector vEquip; // [rsp+D0h] [rbp-A0h] BYREF
  MemChrBagVector addItemVt; // [rsp+F0h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > __rhs; // [rsp+110h] [rbp-60h] BYREF
  std::string p_name; // [rsp+120h] [rbp-50h] BYREF
  int8_t Day; // [rsp+12Bh] [rbp-45h]
  int32_t LoginCount; // [rsp+12Ch] [rbp-44h]
  int32_t OldRecord; // [rsp+130h] [rbp-40h]
  int32_t NewRecord; // [rsp+134h] [rbp-3Ch]
  CfgSevenLoginRewrad *pReward; // [rsp+138h] [rbp-38h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Day = Answer::NetPacket::readInt8(inPacket);
  if ( Day > 7 )
    return 2;
  PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
  if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 112) )
    return 2;
  LoginCount = Player::getRecord(this->m_pPlayer, 1011);
  if ( Day > LoginCount )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1014);
  NewRecord = OldRecord | (1 << (Day - 1));
  if ( OldRecord == NewRecord )
    return 2;
  v4 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::GetSevenLoginRewardCfg(v4, Day);
  if ( !pReward )
    return 2;
  std::vector<MemChrBag>::vector(&addItemVt);
  std::vector<MemEquip>::vector(&vEquip);
  if ( !std::vector<CfgEquipItem>::empty(&pReward->ItemVector) )
  {
    for ( it._M_current = std::vector<CfgEquipItem>::begin(&pReward->ItemVector)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgEquipItem>::end(&pReward->ItemVector)._M_current;
      if ( !__gnu_cxx::operator!=<CfgEquipItem *,std::vector<CfgEquipItem>>(&it, &__rhs) )
        break;
      Job = Player::getJob(this->m_pPlayer);
      if ( Job == __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->job
        || !__gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->type;
        chrbag.itemCount = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->bind;
        if ( chrbag.itemClass == 2 )
        {
          Time = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it)->star;
          Player::getName((const Player *const)&p_name);
          nCreaterId = Player::getCid(this->m_pPlayer);
          Sid = Player::getSid(this->m_pPlayer);
          nBaseId = chrbag.itemId;
          ConnId = Player::getConnId(this->m_pPlayer);
          v11 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v11, ConnId, 601, nBaseId, Sid, nCreaterId, &p_name, 0, 0, Time, 0, 0);
          std::string::~string(&p_name);
          if ( equip.base <= 0 )
            goto LABEL_24;
          if ( equip.id > 0 )
          {
            chrbag.srcId = equip.id;
            std::vector<MemEquip>::push_back(&vEquip, &equip);
            v12 = 1;
          }
          else
          {
LABEL_24:
            v2 = 0;
            v12 = 0;
          }
          MemEquip::~MemEquip(&equip);
          if ( !v12 )
            goto LABEL_35;
        }
        std::vector<MemChrBag>::push_back(&addItemVt, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addItemVt, ITEM_CHANGE_REASON::ICR_SEVEN_LOGIN_REWARD) )
  {
    v2 = 2;
  }
  else
  {
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v15 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v15, m_pPlayer, &vEquip);
    }
    Player::updateRecord(this->m_pPlayer, 1014, NewRecord);
    DailyActivity::SendSevenLoginInfo(this);
    DailyActivity::SendSevenDayLoginIcon(this);
    v2 = 0;
  }
LABEL_35:
  std::vector<MemEquip>::~vector(&vEquip);
  std::vector<MemChrBag>::~vector(&addItemVt);
  return v2;
}


#####################################
int32_t __cdecl DailyActivity::OnQueryLevelGiftInfo(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  DailyActivity::SendLevelGiftInfo(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnGetLevelGift(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int Level; // ebx
  CExtCharBag *Bag; // rax
  uint8_t Index; // [rsp+1Fh] [rbp-21h]
  CfgLevelGift *pLevelGift; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readUInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pLevelGift = CfgData::GetLevelGiftCfg(v3, Index);
  if ( !pLevelGift )
    return 2;
  Level = pLevelGift->Level;
  if ( Level > (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1015);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pLevelGift->ItemVector, ITEM_CHANGE_REASON::ICR_SEVEN_LOGIN_REWARD) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1015, NewRecord);
  DailyActivity::SendLevelGiftInfo(this);
  DailyActivity::SendJiangLiDaTingIcon(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnQueryOffLineExpInfo(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  if ( inPacket )
    return 0;
  else
    return 2;
}


#####################################
int32_t __cdecl DailyActivity::OnGetOffLineExp(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  int8_t Times; // [rsp+1Fh] [rbp-31h]
  CfgOffLineExp *pOfflineExp; // [rsp+20h] [rbp-30h]
  int OfflineSeconds; // [rsp+28h] [rbp-28h]
  int32_t OfflineMinutes; // [rsp+2Ch] [rbp-24h]
  double CanAddExp; // [rsp+30h] [rbp-20h]
  int32_t NeedGold; // [rsp+3Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Times = Answer::NetPacket::readInt8(inPacket);
  v3 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v4 = Answer::Singleton<CfgData>::instance();
  pOfflineExp = CfgData::GetOfflineExpCfg(v4, v3);
  if ( !pOfflineExp )
    return 2;
  OfflineSeconds = Player::getRecord(this->m_pPlayer, 1019);
  if ( OfflineSeconds <= 259200 )
    OfflineMinutes = OfflineSeconds / 60;
  else
    OfflineMinutes = 4320;
  CanAddExp = (double)(OfflineMinutes * pOfflineExp->MinuteExp);
  NeedGold = 0;
  if ( Times == 2 )
  {
    NeedGold = incInt((double)pOfflineExp->TwoTimes * (CanAddExp / (double)pOfflineExp->BaseExp) / 100.0);
    CanAddExp = CanAddExp + CanAddExp;
  }
  else if ( Times == 3 )
  {
    NeedGold = incInt((double)pOfflineExp->ThreeTimes * (CanAddExp / (double)pOfflineExp->BaseExp) / 100.0);
    CanAddExp = 3.0 * CanAddExp;
  }
  if ( CanAddExp <= 0.0 )
    return 2;
  if ( NeedGold > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          NeedGold,
          CURRENCY_CHANGE_REASON::GCR_GET_OFFLINE_EXP,
          0) )
  {
    return 2;
  }
  Player::updateRecord(this->m_pPlayer, 1019, 0);
  Player::addExp(this->m_pPlayer, (unsigned int)(int)CanAddExp, 0, 1);
  DailyActivity::SendJiangLiDaTingIcon(this);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnQueryHuoDaoDaTingData(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int8_t Int8; // dl

  if ( !inPacket )
    return 2;
  Int8 = Answer::NetPacket::readInt8(inPacket);
  DailyActivity::SendHuoDaoDaTingData(this, Int8);
  return 0;
}


#####################################
void __cdecl DailyActivity::sendSignInfo(DailyActivity *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  char *v3; // rax
  int8_t Record; // al
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > it; // [rsp+10h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > __rhs; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int8_t nSize; // [rsp+3Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27F9u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_signInfo.sign_record);
      nSize = std::vector<signed char>::size(&this->m_signInfo.sign_reward);
      Answer::NetPacket::writeInt8(packet, nSize);
      for ( it._M_current = std::vector<signed char>::begin(&this->m_signInfo.sign_reward)._M_current;
            ;
            __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<signed char>::end(&this->m_signInfo.sign_reward)._M_current;
        if ( !__gnu_cxx::operator!=<signed char *,std::vector<signed char>>(&it, &__rhs) )
          break;
        v3 = __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator*(&it);
        Answer::NetPacket::writeInt8(packet, *v3);
      }
      Record = Player::getRecord(this->m_pPlayer, 37207);
      Answer::NetPacket::writeInt8(packet, Record);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl DailyActivity::refreshSignInfo(DailyActivity *const this)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    if ( Answer::DayTime::monthdiff(this->m_signInfo.refresh_time) )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::UpdateLimitCount(OperateLimit, 37207, 0);
      this->m_signInfo.sign_record = 0;
      std::vector<signed char>::clear(&this->m_signInfo.sign_reward);
    }
    DailyActivity::sendSignInfo(this);
  }
}


#####################################
int32_t __cdecl DailyActivity::GetTodayOnLineTime(DailyActivity *const this)
{
  if ( this->m_pPlayer )
    return Player::getRecord(this->m_pPlayer, 2003);
  else
    return 0;
}


#####################################
std::string __cdecl DailyActivity::GetOnlineReward(DailyActivity *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int second; // r12d
  std::pair<const int,int> *v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  _BYTE v9[16]; // [rsp+10h] [rbp-1A0h] BYREF
  __int64 v10; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v9, (unsigned int)v2);
  for ( it._M_node = std::map<int,int>::begin((std::map<int,int> *const)(v1 + 80))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
  {
    __x._M_node = std::map<int,int>::end((std::map<int,int> *const)(v1 + 80))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
      break;
    second = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
    v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    v5 = std::ostream::operator<<(&v10, (unsigned int)v4->first);
    v6 = std::operator<<<std::char_traits<char>>(v5, L":|");
    v7 = std::ostream::operator<<(v6, second);
    std::operator<<<std::char_traits<char>>(v7, 9237662);
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v9);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v9);
  return (std::string)this;
}


#####################################
void __cdecl DailyActivity::PasOnlineReward(DailyActivity *const this, std::string *p_OnlineReward)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  int *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  StringVector vstack; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+30h] [rbp-70h] BYREF
  StringVector strstacks; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v12; // [rsp+6Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  std::string v14; // [rsp+80h] [rbp-20h] BYREF
  char v15; // [rsp+8Bh] [rbp-15h] BYREF
  int __k[5]; // [rsp+8Ch] [rbp-14h] BYREF

  if ( !std::operator==<char>(p_OnlineReward, (const char *)L"") )
  {
    std::map<int,int>::clear(&this->m_OnlimeTimeGetReward);
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, 9237662, &v12);
    Answer::StringUtility::split(&strstacks, p_OnlineReward, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    for ( it._M_current = std::vector<std::string>::begin(&strstacks)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&strstacks)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v15);
      std::string::string(&v14, L":|", &v15);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&vstack, v2, &v14, 0);
      std::string::~string(&v14);
      std::allocator<char>::~allocator(&v15);
      if ( std::vector<std::string>::size(&vstack) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&vstack, 0);
        v4 = (const char *)std::string::c_str(v3);
        __k[0] = atoi(v4);
        v5 = std::map<int,int>::operator[](&this->m_OnlimeTimeGetReward, __k);
        v6 = std::vector<std::string>::operator[](&vstack, 1u);
        v7 = (const char *)std::string::c_str(v6);
        *v5 = atoi(v7);
      }
      std::vector<std::string>::~vector(&vstack);
    }
    std::vector<std::string>::~vector(&strstacks);
  }
}


#####################################
void __cdecl DailyActivity::SendOnlineRewardInfo(DailyActivity *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t TodayOnLineTime; // eax
  int32_t Record; // eax
  int32_t NewSeverWeek; // eax
  int32_t WeekOnlineTime; // eax
  int32_t LastWeekOnlineTime; // eax
  std::pair<const int,int> *v8; // rax
  std::pair<const int,int> *v9; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27ABu);
    if ( packet )
    {
      TodayOnLineTime = DailyActivity::GetTodayOnLineTime(this);
      Answer::NetPacket::writeInt32(packet, TodayOnLineTime);
      Record = Player::getRecord(this->m_pPlayer, 2004);
      Answer::NetPacket::writeInt32(packet, Record);
      NewSeverWeek = DailyActivity::GetNewSeverWeek(this);
      Answer::NetPacket::writeInt32(packet, NewSeverWeek);
      WeekOnlineTime = DailyActivity::GetWeekOnlineTime(this);
      Answer::NetPacket::writeInt32(packet, WeekOnlineTime);
      LastWeekOnlineTime = DailyActivity::GetLastWeekOnlineTime(this);
      Answer::NetPacket::writeInt32(packet, LastWeekOnlineTime);
      nSize = std::map<int,int>::size(&this->m_OnlimeTimeGetReward);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::map<int,int>::begin(&this->m_OnlimeTimeGetReward)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_OnlimeTimeGetReward)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v8->first);
        v9 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v9->second);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v13, v12, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl DailyActivity::SendSevenLoginInfo(DailyActivity *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t v4; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27FBu);
    if ( packet )
    {
      Record = Player::getRecord(this->m_pPlayer, 1011);
      Answer::NetPacket::writeInt32(packet, Record);
      v4 = Player::getRecord(this->m_pPlayer, 1014);
      Answer::NetPacket::writeInt32(packet, v4);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl DailyActivity::SendLevelGiftInfo(DailyActivity *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27F4u);
    if ( packet )
    {
      Record = Player::getRecord(this->m_pPlayer, 1015);
      Answer::NetPacket::writeInt32(packet, Record);
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
int32_t __cdecl DailyActivity::GetNewSeverWeek(DailyActivity *const this)
{
  CfgData *v1; // rax
  int ServerStartTime; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  ServerStartTime = CfgData::getServerStartDayZeroTime(v1, SERVER_TYPE::SVT_NORMAL);
  return Answer::DayTime::weekdiff(ServerStartTime) + 1;
}


#####################################
int32_t __cdecl DailyActivity::GetWeekOnlineTime(DailyActivity *const this)
{
  if ( this->m_pPlayer )
    return Player::getRecord(this->m_pPlayer, 1016);
  else
    return 0;
}


#####################################
int32_t __cdecl DailyActivity::GetLastWeekOnlineTime(DailyActivity *const this)
{
  if ( this->m_pPlayer )
    return Player::getRecord(this->m_pPlayer, 1017);
  else
    return 0;
}


#####################################
void __cdecl DailyActivity::refreshWeekTime(DailyActivity *const this)
{
  int32_t Record; // eax
  int32_t v2; // eax
  CVplan *Vplan; // rax
  CVplan *v4; // rax
  CExtCharFamily *CharFamily; // rax
  ChouJiang *PlayerChouJiang; // rax
  int32_t Now; // eax
  int DiffWeek; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pPlayer )
  {
    Record = Player::getRecord(this->m_pPlayer, 1018);
    DiffWeek = Answer::DayTime::weekdiff(Record);
    if ( DiffWeek == 1 )
    {
      v2 = Player::getRecord(this->m_pPlayer, 1016);
      Player::updateRecord(this->m_pPlayer, 1017, v2);
      Player::updateRecord(this->m_pPlayer, 1016, 0);
      Vplan = Player::GetVplan(this->m_pPlayer);
      (*((void (__fastcall **)(CVplan *, __int64))Vplan->_vptr_IExtSystem + 11))(Vplan, 1);
    }
    else if ( DiffWeek > 1 )
    {
      Player::updateRecord(this->m_pPlayer, 1017, 0);
      Player::updateRecord(this->m_pPlayer, 1016, 0);
      v4 = Player::GetVplan(this->m_pPlayer);
      (*((void (__fastcall **)(CVplan *, _QWORD))v4->_vptr_IExtSystem + 11))(v4, (unsigned int)DiffWeek);
    }
    if ( DiffWeek > 0 )
    {
      Player::updateRecord(this->m_pPlayer, 37212, 0);
      Player::updateRecord(this->m_pPlayer, 37213, 0);
      CharFamily = Player::GetCharFamily(this->m_pPlayer);
      CExtCharFamily::refreshWeekTime(CharFamily);
    }
    PlayerChouJiang = Player::GetPlayerChouJiang(this->m_pPlayer);
    ChouJiang::refreshWeekTime(PlayerChouJiang, DiffWeek);
    Now = Unit::getNow(this->m_pPlayer);
    Player::updateRecord(this->m_pPlayer, 1018, Now);
    DailyActivity::SendOnlineRewardInfo(this);
  }
}


#####################################
void __cdecl DailyActivity::SendOffLineInfo(DailyActivity *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int OfflineSeconds; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27C4u);
    if ( packet )
    {
      OfflineSeconds = Player::getRecord(this->m_pPlayer, 1019);
      if ( OfflineSeconds > 259200 )
        OfflineSeconds = 259200;
      Answer::NetPacket::writeInt32(packet, OfflineSeconds);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl DailyActivity::SendHuoDaoDaTingData(DailyActivity *const this, int8_t Type)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  CActivityManager *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  int8_t v9; // bl
  GameService *v10; // rax
  CExtChrTaskCycle *CharTaskCycle; // rax
  int32_t SurplusTimes; // eax
  int32_t Record; // eax
  int32_t v14; // eax
  uint32_t v15; // eax
  int16_t v16; // r12
  int8_t v17; // bl
  GameService *v18; // rax
  int32_t nCount; // [rsp+14h] [rbp-2Ch] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  uint32_t nOldOffset; // [rsp+20h] [rbp-20h]
  uint32_t nNewOffset; // [rsp+24h] [rbp-1Ch]
  Answer::NetPacket *packet_0; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( Type == 1 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD8u);
      if ( packet )
      {
        nCount = 0;
        Answer::NetPacket::writeInt8(packet, 1);
        nOldOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::writeInt32(packet, 0);
        v4 = Answer::Singleton<CActivityManager>::instance();
        CActivityManager::AppendActivityState(v4, packet, &nCount);
        nNewOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, nOldOffset);
        Answer::NetPacket::writeInt32(packet, nCount);
        Answer::NetPacket::setWOffset(packet, nNewOffset);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v7 = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, v7, GateIndex, packet);
      }
    }
    else if ( Type == 3 )
    {
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v10, v9, Answer::PackType::PACK_DISPATCH, 0x2CD8u);
      if ( packet_0 )
      {
        Answer::NetPacket::writeInt8(packet_0, 3);
        Answer::NetPacket::writeInt32(packet_0, 3);
        Answer::NetPacket::writeInt8(packet_0, 1);
        CharTaskCycle = Player::GetCharTaskCycle(this->m_pPlayer);
        SurplusTimes = CExtChrTaskCycle::GetSurplusTimes(CharTaskCycle);
        Answer::NetPacket::writeInt32(packet_0, SurplusTimes);
        Answer::NetPacket::writeInt8(packet_0, 2);
        Record = Player::getRecord(this->m_pPlayer, 2005);
        Answer::NetPacket::writeInt32(packet_0, 2 - Record);
        Answer::NetPacket::writeInt8(packet_0, 3);
        v14 = Player::getRecord(this->m_pPlayer, 2019);
        Answer::NetPacket::writeInt32(packet_0, 10 - v14);
        v15 = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, v15);
        v16 = Player::getGateIndex(this->m_pPlayer);
        v17 = Player::getConnId(this->m_pPlayer);
        v18 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v18, v17, v16, packet_0);
      }
    }
  }
}


#####################################
void __cdecl DailyActivity::GetHuoDongDaTingIcon(DailyActivity *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 59) )
    {
      DailyActivity::GetHuoDongDaTingIcon(&icon, this);
      std::list<ShowIcon>::push_back(IconList, &icon);
    }
  }
}


#####################################
void __cdecl DailyActivity::SendHuoDongDaTingIcon(DailyActivity *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 59) )
    {
      DailyActivity::GetHuoDongDaTingIcon(&icon, this);
      Player::SendIconState(this->m_pPlayer, &icon);
    }
  }
}


#####################################
int32_t __cdecl DailyActivity::HaveActivityRewardCount(DailyActivity *const this)
{
  int32_t v1; // r12d
  Player *m_pPlayer; // rbx
  CActivityManager *v3; // rax
  int32_t HaveRewardCount; // eax
  int32_t v5; // ebx
  std::_List_iterator<int> it; // [rsp+10h] [rbp-40h] BYREF
  std::list<int> ActivityId; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<int> __x; // [rsp+30h] [rbp-20h] BYREF
  int32_t Count; // [rsp+3Ch] [rbp-14h]

  Count = 0;
  std::list<int>::list(&ActivityId);
  std::list<int>::clear(&ActivityId);
  for ( it._M_node = std::list<int>::begin(&ActivityId)._M_node; ; std::_List_iterator<int>::operator++(&it) )
  {
    __x._M_node = std::list<int>::end(&ActivityId)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    v1 = *std::_List_iterator<int>::operator*(&it);
    m_pPlayer = this->m_pPlayer;
    v3 = Answer::Singleton<CActivityManager>::instance();
    HaveRewardCount = CActivityManager::HaveRewardCount(v3, m_pPlayer, v1);
    Count += HaveRewardCount;
  }
  v5 = Count;
  std::list<int>::~list(&ActivityId);
  return v5;
}


#####################################
void __cdecl DailyActivity::GetJiangLiDaTingIcon(DailyActivity *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 60) )
    {
      DailyActivity::GetJiangLiDaTingIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl DailyActivity::SendJiangLiDaTingIcon(DailyActivity *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 60) )
    {
      DailyActivity::GetJiangLiDaTingIcon(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl DailyActivity::GetSearchBackIcon(DailyActivity *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 168) )
    {
      DailyActivity::GetSearchBackIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl DailyActivity::GetSevenDayLoginIcon(DailyActivity *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 112) )
    {
      DailyActivity::GetSevenDayLoginIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl DailyActivity::SendSevenDayLoginIcon(DailyActivity *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 112) )
    {
      DailyActivity::GetSevenDayLoginIcon(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
bool __cdecl DailyActivity::TodayIsSign(DailyActivity *const this)
{
  tm tmNow; // [rsp+10h] [rbp-50h] BYREF

  Unit::getLocalNow(&tmNow, this->m_pPlayer);
  return ((this->m_signInfo.sign_record >> (LOBYTE(tmNow.tm_mday) - 1)) & 1) != 0;
}


#####################################
bool __cdecl DailyActivity::HaveSignReward(DailyActivity *const this)
{
  bool v1; // bl
  CfgData *v2; // rax
  CfgSignRewardTable *SignRewardTable; // rax
  std::pair<const signed char,CfgSignReward> *v4; // rax
  int v5; // ebx
  tm tmNow; // [rsp+10h] [rbp-D0h] BYREF
  CfgSignRewardTable ReardTable; // [rsp+50h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > itRecord; // [rsp+80h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgSignReward> > it; // [rsp+90h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgSignReward> > __x; // [rsp+A0h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<signed char*,std::vector<signed char> > __rhs; // [rsp+B0h] [rbp-30h] BYREF
  int32_t i; // [rsp+C4h] [rbp-1Ch]
  int32_t signCount; // [rsp+C8h] [rbp-18h]
  bool IsGet; // [rsp+CFh] [rbp-11h]

  if ( !this->m_pPlayer )
    return 0;
  Unit::getLocalNow(&tmNow, this->m_pPlayer);
  i = 0;
  signCount = 0;
  while ( tmNow.tm_mday > i )
    signCount += (this->m_signInfo.sign_record >> i++) & 1;
  v2 = Answer::Singleton<CfgData>::instance();
  SignRewardTable = CfgData::GetSignRewardTable(v2);
  std::map<signed char,CfgSignReward>::map(&ReardTable, SignRewardTable);
  for ( it._M_node = std::map<signed char,CfgSignReward>::begin(&ReardTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,CfgSignReward>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,CfgSignReward>::end(&ReardTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,CfgSignReward>>::operator!=(&it, &__x) )
      break;
    v4 = std::_Rb_tree_iterator<std::pair<signed char const,CfgSignReward>>::operator->(&it);
    if ( v4->second.count <= signCount )
    {
      IsGet = 0;
      for ( itRecord._M_current = std::vector<signed char>::begin(&this->m_signInfo.sign_reward)._M_current;
            ;
            __gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator++(&itRecord) )
      {
        __rhs._M_current = std::vector<signed char>::end(&this->m_signInfo.sign_reward)._M_current;
        if ( !__gnu_cxx::operator!=<signed char *,std::vector<signed char>>(&itRecord, &__rhs) )
          break;
        v5 = *__gnu_cxx::__normal_iterator<signed char *,std::vector<signed char>>::operator*(&itRecord);
        if ( v5 == std::_Rb_tree_iterator<std::pair<signed char const,CfgSignReward>>::operator->(&it)->second.count )
        {
          IsGet = 1;
          break;
        }
      }
      if ( !IsGet )
      {
        v1 = 1;
        goto LABEL_18;
      }
    }
  }
  v1 = 0;
LABEL_18:
  std::map<signed char,CfgSignReward>::~map(&ReardTable);
  return v1;
}


#####################################
bool __cdecl DailyActivity::HaveOnLineReward(DailyActivity *const this)
{
  CfgData *v1; // rax
  CfgOnlineRewardTable *v2; // rax
  std::pair<const signed char,CfgOnlineReward> *v3; // rax
  std::pair<const signed char,CfgOnlineReward> *v4; // rax
  bool v5; // bl
  CfgOnlineRewardTable OnLineRewardTable; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgOnlineReward> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgOnlineReward> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t TodayTime; // [rsp+58h] [rbp-18h]
  int32_t RewardRecord; // [rsp+5Ch] [rbp-14h]

  TodayTime = DailyActivity::GetTodayOnLineTime(this);
  RewardRecord = Player::getRecord(this->m_pPlayer, 2004);
  v1 = Answer::Singleton<CfgData>::instance();
  v2 = CfgData::GetOnLineRewardTable(v1);
  std::map<signed char,CfgOnlineReward>::map(&OnLineRewardTable, v2);
  for ( it._M_node = std::map<signed char,CfgOnlineReward>::begin(&OnLineRewardTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,CfgOnlineReward>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,CfgOnlineReward>::end(&OnLineRewardTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,CfgOnlineReward>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,CfgOnlineReward>>::operator->(&it);
    if ( v3->second.NeedTime <= TodayTime )
    {
      v4 = std::_Rb_tree_iterator<std::pair<signed char const,CfgOnlineReward>>::operator->(&it);
      if ( ((RewardRecord >> (v4->first - 1)) & 1) == 0 )
      {
        v5 = 1;
        goto LABEL_8;
      }
    }
  }
  v5 = 0;
LABEL_8:
  std::map<signed char,CfgOnlineReward>::~map(&OnLineRewardTable);
  return v5;
}


#####################################
bool __cdecl DailyActivity::HaveWeekReward(DailyActivity *const this)
{
  return DailyActivity::GetNewSeverWeek(this) > 1 && DailyActivity::GetLastWeekOnlineTime(this) > 3599;
}


#####################################
bool __cdecl DailyActivity::haveSevenLoginReward(DailyActivity *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  int32_t LoginCount; // [rsp+14h] [rbp-1Ch]
  int RewardRecord; // [rsp+18h] [rbp-18h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
  if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 112) )
    return 0;
  LoginCount = Player::getRecord(this->m_pPlayer, 1011);
  RewardRecord = Player::getRecord(this->m_pPlayer, 1014);
  for ( i = 0; i < LoginCount && i <= 6; ++i )
  {
    if ( ((RewardRecord >> i) & 1) == 0 )
      return 1;
  }
  return 0;
}


#####################################
bool __cdecl DailyActivity::HaveLevelReward(DailyActivity *const this)
{
  bool v1; // bl
  CfgData *v2; // rax
  CfgLevelGiftTable *LeveGiftTable; // rax
  std::pair<const int,CfgLevelGift> *v4; // rax
  std::pair<const int,CfgLevelGift> *v5; // rax
  CfgLevelGiftTable LevelGiftTable; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelGift> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgLevelGift> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t Level; // [rsp+58h] [rbp-18h]
  int32_t RewardRecord; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  Level = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  RewardRecord = Player::getRecord(this->m_pPlayer, 1015);
  v2 = Answer::Singleton<CfgData>::instance();
  LeveGiftTable = CfgData::GetLeveGiftTable(v2);
  std::map<int,CfgLevelGift>::map(&LevelGiftTable, LeveGiftTable);
  for ( it._M_node = std::map<int,CfgLevelGift>::begin(&LevelGiftTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,CfgLevelGift>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgLevelGift>::end(&LevelGiftTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,CfgLevelGift>>::operator!=(&it, &__x) )
      break;
    v4 = std::_Rb_tree_iterator<std::pair<int const,CfgLevelGift>>::operator->(&it);
    if ( v4->second.Level <= Level )
    {
      v5 = std::_Rb_tree_iterator<std::pair<int const,CfgLevelGift>>::operator->(&it);
      if ( ((RewardRecord >> (LOBYTE(v5->first) - 1)) & 1) == 0 )
      {
        v1 = 1;
        goto LABEL_10;
      }
    }
  }
  v1 = 0;
LABEL_10:
  std::map<int,CfgLevelGift>::~map(&LevelGiftTable);
  return v1;
}


#####################################
bool __cdecl DailyActivity::HaveEquipShow(DailyActivity *const this)
{
  int32_t Level; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  Level = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  return Level > 89 && Level <= 360;
}


#####################################
bool __cdecl DailyActivity::HaveOffLineReard(DailyActivity *const this)
{
  return Player::getRecord(this->m_pPlayer, 1019) > 3600;
}


#####################################
bool __cdecl DailyActivity::haveSearchBackReward(DailyActivity *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  int8_t i; // [rsp+1Fh] [rbp-1h]

  if ( !this->m_pPlayer )
    return 0;
  PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
  if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 168) )
    return 0;
  for ( i = 0; i <= 2; ++i )
  {
    if ( !std::list<SearchBackRecord>::empty(&this->m_vSeachBackRecord[i]) )
      return 1;
  }
  return 0;
}


#####################################
void __cdecl DailyActivity::OnLevelUp(DailyActivity *const this)
{
  if ( DailyActivity::HaveLevelReward(this) )
    DailyActivity::SendJiangLiDaTingIcon(this);
}


#####################################
void __cdecl DailyActivity::UpDateJiangLiDatingIcon(DailyActivity *const this, int64_t curTick)
{
  if ( this->m_pPlayer && curTick - this->m_LastUpdateIcon > 60000 )
  {
    if ( DailyActivity::HaveOnLineReward(this) )
      DailyActivity::SendJiangLiDaTingIcon(this);
    this->m_LastUpdateIcon = curTick;
  }
}


#####################################
void __cdecl DailyActivity::AddDungeonRecord(DailyActivity *const this, int8_t nType, int32_t nTimes, int32_t nParam)
{
  std::_List_iterator<SearchBackInfo> iter; // [rsp+20h] [rbp-30h] BYREF
  SearchBackInfo stu; // [rsp+30h] [rbp-20h] BYREF
  std::_List_iterator<SearchBackInfo> __x; // [rsp+40h] [rbp-10h] BYREF

  if ( this->m_pPlayer )
  {
    for ( iter._M_node = std::list<SearchBackInfo>::begin(&this->m_lstTodayInfo)._M_node;
          ;
          std::_List_iterator<SearchBackInfo>::operator++(&iter) )
    {
      __x._M_node = std::list<SearchBackInfo>::end(&this->m_lstTodayInfo)._M_node;
      if ( !std::_List_iterator<SearchBackInfo>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<SearchBackInfo>::operator->(&iter)->nType == 2
        && std::_List_iterator<SearchBackInfo>::operator->(&iter)->nSubType == nType )
      {
        std::_List_iterator<SearchBackInfo>::operator->(&iter)->nTimes = nTimes;
        std::_List_iterator<SearchBackInfo>::operator->(&iter)->nParam = nParam;
        return;
      }
    }
    *(_DWORD *)&stu.nType = 2;
    stu.nSubType = nType;
    stu.nTimes = nTimes;
    stu.nParam = nParam;
    std::list<SearchBackInfo>::push_back(&this->m_lstTodayInfo, &stu);
  }
}


#####################################
void __cdecl DailyActivity::AddActivityRecord(DailyActivity *const this, int8_t nType, int32_t nId)
{
  CHuoYueDu *PlayerHuoYueDu; // rax
  SearchBackInfo *v5; // rax
  std::_List_iterator<SearchBackInfo> iter; // [rsp+10h] [rbp-40h] BYREF
  SearchBackInfo stu; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<SearchBackInfo> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 1, nType, 0);
    for ( iter._M_node = std::list<SearchBackInfo>::begin(&this->m_lstTodayInfo)._M_node;
          ;
          std::_List_iterator<SearchBackInfo>::operator++(&iter) )
    {
      __x._M_node = std::list<SearchBackInfo>::end(&this->m_lstTodayInfo)._M_node;
      if ( !std::_List_iterator<SearchBackInfo>::operator!=(&iter, &__x) )
      {
        *(_QWORD *)&stu.nType = 0x100000001LL;
        stu.nSubType = nType;
        stu.nParam = nId;
        std::list<SearchBackInfo>::push_back(&this->m_lstTodayInfo, &stu);
        return;
      }
      if ( std::_List_iterator<SearchBackInfo>::operator->(&iter)->nType == 1
        && std::_List_iterator<SearchBackInfo>::operator->(&iter)->nSubType == nType )
      {
        break;
      }
    }
    if ( std::_List_iterator<SearchBackInfo>::operator->(&iter)->nParam != nId )
    {
      v5 = std::_List_iterator<SearchBackInfo>::operator->(&iter);
      ++v5->nTimes;
      std::_List_iterator<SearchBackInfo>::operator->(&iter)->nParam = nId;
    }
  }
}


#####################################
void __cdecl DailyActivity::AddTaskRecord(DailyActivity *const this, int32_t nType)
{
  SearchBackInfo *v3; // rax
  std::_List_iterator<SearchBackInfo> iter; // [rsp+10h] [rbp-30h] BYREF
  SearchBackInfo stu; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<SearchBackInfo> __x; // [rsp+30h] [rbp-10h] BYREF

  if ( this->m_pPlayer )
  {
    for ( iter._M_node = std::list<SearchBackInfo>::begin(&this->m_lstTodayInfo)._M_node;
          ;
          std::_List_iterator<SearchBackInfo>::operator++(&iter) )
    {
      __x._M_node = std::list<SearchBackInfo>::end(&this->m_lstTodayInfo)._M_node;
      if ( !std::_List_iterator<SearchBackInfo>::operator!=(&iter, &__x) )
        break;
      if ( std::_List_iterator<SearchBackInfo>::operator->(&iter)->nType == 3
        && std::_List_iterator<SearchBackInfo>::operator->(&iter)->nSubType == nType )
      {
        v3 = std::_List_iterator<SearchBackInfo>::operator->(&iter);
        ++v3->nTimes;
        std::_List_iterator<SearchBackInfo>::operator->(&iter)->nParam = 0;
        return;
      }
    }
    *(_QWORD *)&stu.nType = 0x100000003LL;
    stu.nSubType = nType;
    stu.nParam = 0;
    std::list<SearchBackInfo>::push_back(&this->m_lstTodayInfo, &stu);
  }
}


#####################################
void __cdecl DailyActivity::refreshSearchBack(DailyActivity *const this, int32_t nDiffDays)
{
  SearchBackRecordList lstFree; // [rsp+10h] [rbp-40h] BYREF
  SearchBackRecordList lstToday; // [rsp+20h] [rbp-30h] BYREF
  int32_t i; // [rsp+3Ch] [rbp-14h]

  if ( nDiffDays > 0 )
  {
    std::list<SearchBackRecord>::list(&lstToday);
    DailyActivity::getTodaySearchBackRecord(this, &lstToday, 1);
    std::list<SearchBackRecord>::list(&lstFree);
    DailyActivity::getTodaySearchBackRecord(this, &lstFree, 0);
    for ( i = 2; i >= 0; --i )
    {
      if ( i < nDiffDays )
      {
        if ( nDiffDays - 1 == i )
          std::list<SearchBackRecord>::operator=(&this->m_vSeachBackRecord[i], &lstToday);
        else
          std::list<SearchBackRecord>::operator=(&this->m_vSeachBackRecord[i], &lstFree);
      }
      else
      {
        std::list<SearchBackRecord>::operator=(&this->m_vSeachBackRecord[i], &this->m_vSeachBackRecord[i - nDiffDays]);
      }
    }
    std::list<SearchBackInfo>::clear(&this->m_lstTodayInfo);
    std::list<SearchBackRecord>::~list(&lstFree);
    std::list<SearchBackRecord>::~list(&lstToday);
  }
}


#####################################
void __cdecl DailyActivity::getTodaySearchBackRecord(
        DailyActivity *const this,
        SearchBackRecordList *const outList,
        bool bToday)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgSearchBackTable *SearchBackTable; // rax
  int32_t nOpenType; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  int8_t nSubType; // bl
  int8_t nType; // cl
  const CfgSearchBack *v10; // rax
  const CfgSearchBack *v11; // rax
  __int64 v12; // rax
  SearchBackRecord stu_0; // [rsp+30h] [rbp-90h] BYREF
  SearchBackRecord stu; // [rsp+40h] [rbp-80h] BYREF
  SearchBackInfo info; // [rsp+50h] [rbp-70h]
  std::_List_const_iterator<CfgSearchBack> iter; // [rsp+60h] [rbp-60h] BYREF
  CfgSearchBackList cfgList; // [rsp+70h] [rbp-50h] BYREF
  std::_List_iterator<CfgSearchBack> __x; // [rsp+80h] [rbp-40h] BYREF
  std::_List_const_iterator<CfgSearchBack> v20; // [rsp+90h] [rbp-30h] BYREF
  std::_List_iterator<CfgSearchBack> v21; // [rsp+A0h] [rbp-20h] BYREF
  SearchBackInfo v22; // 0:kr00_12.12

  if ( this->m_pPlayer )
  {
    std::list<CfgSearchBack>::list(&cfgList);
    v3 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v4 = Answer::Singleton<CfgData>::instance();
    SearchBackTable = CfgData::GetSearchBackTable(v4);
    CfgSearchBackTable::GetSearchBackList(SearchBackTable, v3, &cfgList);
    __x._M_node = std::list<CfgSearchBack>::begin(&cfgList)._M_node;
    std::_List_const_iterator<CfgSearchBack>::_List_const_iterator(&iter, &__x);
    while ( 1 )
    {
      v21._M_node = std::list<CfgSearchBack>::end(&cfgList)._M_node;
      std::_List_const_iterator<CfgSearchBack>::_List_const_iterator(&v20, &v21);
      if ( !std::_List_const_iterator<CfgSearchBack>::operator!=(&iter, &v20) )
        break;
      nOpenType = std::_List_const_iterator<CfgSearchBack>::operator->(&iter)->nOpenType;
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, nOpenType) )
      {
        nSubType = std::_List_const_iterator<CfgSearchBack>::operator->(&iter)->nSubType;
        nType = std::_List_const_iterator<CfgSearchBack>::operator->(&iter)->nType;
        v22 = DailyActivity::getSearchBackInfo(this, nType, nSubType);
        LOBYTE(v12) = v22.nType;
        BYTE1(v12) = v22.nSubType;
        HIDWORD(v12) = v22.nTimes;
        *(_QWORD *)&info.nType = v12;
        info.nParam = v22.nParam;
        if ( bToday )
        {
          v10 = std::_List_const_iterator<CfgSearchBack>::operator->(&iter);
          if ( v10->nTimes > info.nTimes )
          {
            *(_QWORD *)&stu.nId = 0;
            stu.nParam = 0;
            stu.nId = std::_List_const_iterator<CfgSearchBack>::operator->(&iter)->nId;
            v11 = std::_List_const_iterator<CfgSearchBack>::operator->(&iter);
            stu.nTimes = v11->nTimes - info.nTimes;
            std::list<SearchBackRecord>::push_back(outList, &stu);
          }
        }
        else
        {
          *(_QWORD *)&stu_0.nId = 0;
          stu_0.nParam = 0;
          stu_0.nId = std::_List_const_iterator<CfgSearchBack>::operator->(&iter)->nId;
          stu_0.nTimes = std::_List_const_iterator<CfgSearchBack>::operator->(&iter)->nTimes;
          std::list<SearchBackRecord>::push_back(outList, &stu_0);
        }
      }
      std::_List_const_iterator<CfgSearchBack>::operator++(&iter);
    }
    std::list<CfgSearchBack>::~list(&cfgList);
  }
}


#####################################
void __cdecl DailyActivity::updateSearchBackRecord(DailyActivity *const this, int32_t nId, int32_t Times)
{
  CfgData *v3; // rax
  const CfgSearchBackTable *SearchBackTable; // rax
  SearchBackRecord *v5; // rax
  std::_List_iterator<SearchBackRecord> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<SearchBackRecord> __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t i; // [rsp+34h] [rbp-Ch]
  const CfgSearchBack *pCfgSearchBack; // [rsp+38h] [rbp-8h]

  i = 2;
LABEL_13:
  if ( i >= 0 )
  {
    for ( iter._M_node = std::list<SearchBackRecord>::begin(&this->m_vSeachBackRecord[i])._M_node;
          ;
          std::_List_iterator<SearchBackRecord>::operator++(&iter) )
    {
      __x._M_node = std::list<SearchBackRecord>::end(&this->m_vSeachBackRecord[i])._M_node;
      if ( !std::_List_iterator<SearchBackRecord>::operator!=(&iter, &__x) )
      {
        --i;
        goto LABEL_13;
      }
      if ( std::_List_iterator<SearchBackRecord>::operator->(&iter)->nId == nId )
        break;
    }
    v3 = Answer::Singleton<CfgData>::instance();
    SearchBackTable = CfgData::GetSearchBackTable(v3);
    pCfgSearchBack = CfgSearchBackTable::GetSearchBack(SearchBackTable, nId);
    if ( pCfgSearchBack )
    {
      if ( pCfgSearchBack->nType == 2 && pCfgSearchBack->nSubType == 16
        || (v5 = std::_List_iterator<SearchBackRecord>::operator->(&iter),
            v5->nTimes -= Times,
            std::_List_iterator<SearchBackRecord>::operator->(&iter)->nTimes <= 0) )
      {
        std::list<SearchBackRecord>::erase(&this->m_vSeachBackRecord[i], iter);
      }
    }
  }
}


#####################################
void __cdecl DailyActivity::SendSearchBackInfo(DailyActivity *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  const SearchBackRecord *v4; // rax
  const SearchBackRecord *v5; // rax
  const SearchBackRecord *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_const_iterator<SearchBackRecord> iter; // [rsp+10h] [rbp-60h] BYREF
  std::_List_iterator<SearchBackRecord> __x; // [rsp+20h] [rbp-50h] BYREF
  std::_List_const_iterator<SearchBackRecord> v13; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<SearchBackRecord> v14; // [rsp+40h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+50h] [rbp-20h]
  int32_t i; // [rsp+5Ch] [rbp-14h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE2u);
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, 3);
    for ( i = 0; i <= 2; ++i )
    {
      v3 = std::list<SearchBackRecord>::size(&this->m_vSeachBackRecord[i]);
      Answer::NetPacket::writeInt32(packet, v3);
      __x._M_node = std::list<SearchBackRecord>::begin(&this->m_vSeachBackRecord[i])._M_node;
      std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v14._M_node = std::list<SearchBackRecord>::end(&this->m_vSeachBackRecord[i])._M_node;
        std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(&v13, &v14);
        if ( !std::_List_const_iterator<SearchBackRecord>::operator!=(&iter, &v13) )
          break;
        v4 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v4->nId);
        v5 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v5->nTimes);
        v6 = std::_List_const_iterator<SearchBackRecord>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v6->nParam);
        std::_List_const_iterator<SearchBackRecord>::operator++(&iter);
      }
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v9 = Player::getConnId(this->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v10, v9, GateIndex, packet);
  }
}


#####################################
int32_t __cdecl DailyActivity::RecordEnterNumber(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int8_t Int32; // cl
  int32_t ActivityId; // [rsp+18h] [rbp-8h]

  if ( !inPacket )
    return 2;
  ActivityId = Answer::NetPacket::readInt32(inPacket);
  Int32 = Answer::NetPacket::readInt32(inPacket);
  DailyActivity::AddActivityRecord(this, Int32, ActivityId);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnGetMaintainCompensateReward(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CfgData *v4; // rax
  const CfgMaintainCompensateTable *MaintainCompensateTable; // rax
  int32_t nTime; // ebx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  int32_t nIndex; // [rsp+10h] [rbp-30h]
  const CfgMaintainCompensate *pCfg; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt32(inPacket);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 1070) + 1 != nIndex )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  MaintainCompensateTable = CfgData::GetMaintainCompensateTable(v4);
  pCfg = CfgMaintainCompensateTable::GetInfo(MaintainCompensateTable, nIndex);
  if ( !pCfg )
    return 10002;
  nTime = pCfg->nTime;
  if ( nTime > Unit::getNow(this->m_pPlayer) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vItems, ITEM_CHANGE_REASON::ICR_MAINTAIN_COMPENSATE_REWARD) )
    return 10002;
  v8 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v8, 1070, nIndex);
  DailyActivity::SendJiangLiDaTingIcon(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v12 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v12, ConnId, GateIndex, Proc, nIndex);
}


#####################################
int32_t __cdecl DailyActivity::OnGetSearchBackReward(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  int32_t nTimes; // r13d
  int8_t v5; // r12
  int v6; // r12d
  std::_List_const_iterator<SearchBackRecord> iter; // [rsp+20h] [rbp-90h] BYREF
  SearchBackRecordList ItemListTmp; // [rsp+30h] [rbp-80h] BYREF
  std::_List_iterator<SearchBackRecord> __x; // [rsp+50h] [rbp-60h] BYREF
  std::_List_const_iterator<SearchBackRecord> v11; // [rsp+60h] [rbp-50h] BYREF
  std::_List_iterator<SearchBackRecord> v12; // [rsp+70h] [rbp-40h] BYREF
  int32_t nId; // [rsp+84h] [rbp-2Ch]
  int8_t nFree; // [rsp+8Bh] [rbp-25h]
  int32_t i; // [rsp+8Ch] [rbp-24h]
  SearchBackRecord v16; // 0:kr00_12.12
  SearchBackRecord v17; // 0:rsi.8,8:edx.4

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
  if ( !CFunctionOpen::IsOpened(PlayerFunctionOpen, 168) )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  nFree = Answer::NetPacket::readInt8(inPacket);
  if ( nId <= 0 )
  {
    for ( i = 2; i >= 0; --i )
    {
      std::list<SearchBackRecord>::list(&ItemListTmp, &this->m_vSeachBackRecord[i]);
      __x._M_node = std::list<SearchBackRecord>::begin(&ItemListTmp)._M_node;
      std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v12._M_node = std::list<SearchBackRecord>::end(&ItemListTmp)._M_node;
        std::_List_const_iterator<SearchBackRecord>::_List_const_iterator(&v11, &v12);
        if ( !std::_List_const_iterator<SearchBackRecord>::operator!=(&iter, &v11) )
          break;
        nTimes = std::_List_const_iterator<SearchBackRecord>::operator->(&iter)->nTimes;
        v5 = nFree;
        v17 = *std::_List_const_iterator<SearchBackRecord>::operator*(&iter);
        if ( !DailyActivity::GetSearchReward(this, v17, v5, nTimes) )
        {
          DailyActivity::SendSearchBackInfo(this);
          DailyActivity::SendSearchBackIcon(this);
          v2 = 0;
          v6 = 0;
          goto LABEL_15;
        }
        std::_List_const_iterator<SearchBackRecord>::operator++(&iter);
      }
      v6 = 1;
LABEL_15:
      std::list<SearchBackRecord>::~list(&ItemListTmp);
      if ( !v6 )
        return v2;
    }
    DailyActivity::SendSearchBackInfo(this);
    DailyActivity::SendSearchBackIcon(this);
    return 0;
  }
  else
  {
    v16 = DailyActivity::getSearchBackRecord(this, nId);
    DailyActivity::GetSearchReward(this, v16, nFree, 1);
    DailyActivity::SendSearchBackInfo(this);
    DailyActivity::SendSearchBackIcon(this);
    return 0;
  }
}


#####################################
bool __cdecl DailyActivity::GetSearchReward(
        DailyActivity *const this,
        SearchBackRecord record,
        int8_t nFree,
        int32_t Times)
{
  bool v4; // bl
  CfgData *v5; // rax
  const CfgSearchBackTable *SearchBackTable; // rax
  int64_t Currency; // rax
  MemChrBag *v9; // rax
  CExtCharBag *Bag; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+20h] [rbp-60h] BYREF
  MemChrBagVector vItemReward; // [rsp+30h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+50h] [rbp-30h] BYREF
  const CfgSearchBack *pCfgSearchBack; // [rsp+60h] [rbp-20h]
  int32_t nGoldCost; // [rsp+6Ch] [rbp-14h]

  if ( record.nTimes >= Times )
  {
    v5 = Answer::Singleton<CfgData>::instance();
    SearchBackTable = CfgData::GetSearchBackTable(v5);
    pCfgSearchBack = CfgSearchBackTable::GetSearchBack(SearchBackTable, record.nId);
    if ( !pCfgSearchBack )
      return 0;
    nGoldCost = Times * pCfgSearchBack->nGoldCost;
    std::vector<MemChrBag>::vector(&vItemReward);
    std::vector<MemChrBag>::operator=(&vItemReward, &pCfgSearchBack->vFreeReward);
    if ( nFree > 0 )
    {
      if ( nGoldCost > 0 )
      {
        Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
        if ( Currency < nGoldCost )
        {
          Player::TiShiInfo(this->m_pPlayer, 11, 0);
          v4 = 0;
LABEL_23:
          std::vector<MemChrBag>::~vector(&vItemReward);
          return v4;
        }
      }
      std::vector<MemChrBag>::operator=(&vItemReward, &pCfgSearchBack->vItemReward);
    }
    if ( std::vector<MemChrBag>::empty(&vItemReward) )
      goto LABEL_20;
    for ( it._M_current = std::vector<MemChrBag>::begin(&vItemReward)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<MemChrBag>::end(&vItemReward)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
        break;
      v9 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
      v9->itemCount *= Times;
    }
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, &vItemReward, ITEM_CHANGE_REASON::ICR_SEARCH_BACK) )
    {
      Player::TiShiInfo(this->m_pPlayer, 2048, 0);
      v4 = 0;
    }
    else
    {
LABEL_20:
      if ( nFree > 0 && nGoldCost > 0 )
        Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          nGoldCost,
          CURRENCY_CHANGE_REASON::MCR_SEARCH_BACK,
          0);
      DailyActivity::updateSearchBackRecord(this, record.nId, Times);
      v4 = 1;
    }
    goto LABEL_23;
  }
  return 0;
}


#####################################
bool __cdecl DailyActivity::HaveMaintainCompensateReward(DailyActivity *const this)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgMaintainCompensateTable *MaintainCompensateTable; // rax
  int32_t nTime; // ebx
  bool v7; // al
  const CfgMaintainCompensate *pCfg; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  v3 = CExtOperateLimit::GetLimitCount(OperateLimit, 1070) + 1;
  v4 = Answer::Singleton<CfgData>::instance();
  MaintainCompensateTable = CfgData::GetMaintainCompensateTable(v4);
  pCfg = CfgMaintainCompensateTable::GetInfo(MaintainCompensateTable, v3);
  v7 = 0;
  if ( pCfg )
  {
    nTime = pCfg->nTime;
    if ( nTime <= Unit::getNow(this->m_pPlayer) )
      return 1;
  }
  return v7;
}


#####################################
int32_t __cdecl DailyActivity::OnGetDogTitle(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax
  int64_t v5; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  MemChrBag stu; // [rsp+10h] [rbp-50h] BYREF
  int8_t Type; // [rsp+3Fh] [rbp-21h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Type = Answer::NetPacket::readInt8(inPacket);
  if ( Type == 1 )
  {
    if ( Player::getRecord(this->m_pPlayer, 1158) > 0 )
      return 10002;
    *(_QWORD *)&stu.itemId = 0x1000014DFLL;
    *(_QWORD *)&stu.itemCount = 0x100000001LL;
    *(_QWORD *)&stu.endTime = 0;
    stu.srcId = 0;
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, &stu, ITEM_CHANGE_REASON::IDCR_DOG_TITLE_GET) )
      return 10002;
    Player::updateRecord(this->m_pPlayer, 1158, 1);
  }
  else if ( Type == 2 )
  {
    if ( Player::getRecord(this->m_pPlayer, 1159) > 0 )
      return 10002;
    *(_QWORD *)&stu.itemId = 0x100001B95LL;
    *(_QWORD *)&stu.itemCount = 0x100000001LL;
    *(_QWORD *)&stu.endTime = 0;
    stu.srcId = 0;
    v4 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(v4, &stu, ITEM_CHANGE_REASON::IDCR_DOG_TITLE_GET) )
      return 10002;
    Player::updateRecord(this->m_pPlayer, 1159, 1);
  }
  v5 = Type;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, v5);
  return 0;
}


#####################################
int32_t __cdecl DailyActivity::OnAskDogTitleInfo(DailyActivity *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t Record; // edx
  int32_t v6; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  int8_t nType; // [rsp+17h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE3u);
  if ( !packet )
    return 10002;
  Answer::NetPacket::writeInt8(packet, nType);
  Record = Player::getRecord(this->m_pPlayer, 1158);
  Answer::NetPacket::writeInt32(packet, Record);
  v6 = Player::getRecord(this->m_pPlayer, 1159);
  Answer::NetPacket::writeInt32(packet, v6);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v9 = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v10, v9, GateIndex, packet);
  return 0;
}


