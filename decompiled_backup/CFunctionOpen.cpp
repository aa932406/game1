// Decompiled methods for class: CFunctionOpen
// Source: gameserver.cc
// Total methods: 20

#####################################
void __cdecl CFunctionOpen::~CFunctionOpen(CFunctionOpen *const this)
{
  CFunctionOpen::~CFunctionOpen(this);
  operator delete(this);
}


#####################################
void __cdecl CFunctionOpen::OnCleanUp(CFunctionOpen *const this)
{
  std::list<int>::clear(&this->m_OpenedList);
  std::list<int>::clear(&this->m_SendMailList);
}


#####################################
void __cdecl CFunctionOpen::GetInterestsProtocol(CFunctionOpen *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 470;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CFunctionOpen::DispatchNetDatas(
        CFunctionOpen *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 470 )
    return CFunctionOpen::OnGetSysOpenGift(this, inPacket);
  return 2;
}


#####################################
int32_t __cdecl CFunctionOpen::OnGetSysOpenGift(CFunctionOpen *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int32_t Record; // eax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int32_t Id; // [rsp+14h] [rbp-3Ch]
  SystemOpenGift *pCfg; // [rsp+18h] [rbp-38h]
  int NewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Id = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetSystemOpenGift(v3, Id);
  if ( !pCfg )
    return 2;
  if ( !CFunctionOpen::IsOpened(this, pCfg->TypeId) )
    return 2;
  if ( pCfg->Star > Player::getRecord(this->m_pPlayer, 1148) )
    return 2;
  Record = Player::getRecord(this->m_pPlayer, 1151);
  NewRecord = Record | (1 << (Id - 1));
  if ( NewRecord == Record )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->Gifts, ITEM_CHANGE_REASON::ICR_SYS_OPEN_GIFT) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1151, NewRecord);
  CFunctionOpen::SendSysOpenIcon(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CFunctionOpen::GetSysOpenIcon(CFunctionOpen *const this, IconStateList *const IconList)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    CFunctionOpen::GetSysOpenIcon(&icon, this);
    std::list<ShowIcon>::push_back(IconList, &icon);
  }
}


#####################################
void __cdecl CFunctionOpen::SendSysOpenIcon(CFunctionOpen *const this)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    CFunctionOpen::GetSysOpenIcon(&icon, this);
    Player::SendIconState(this->m_pPlayer, &icon);
  }
}


#####################################
bool __cdecl CFunctionOpen::IsAllRewardGet(CFunctionOpen *const this)
{
  CfgData *v1; // rax
  const SystemOpenGiftMap *SystemOpenMap; // rax
  std::pair<const int,SystemOpenGift> *v3; // rax
  bool v4; // bl
  SystemOpenGiftMap SystemOpenGifts; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SystemOpenGift> > iter; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SystemOpenGift> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t OldRecord; // [rsp+58h] [rbp-18h]
  int32_t NewRecord; // [rsp+5Ch] [rbp-14h]

  OldRecord = Player::getRecord(this->m_pPlayer, 1151);
  v1 = Answer::Singleton<CfgData>::instance();
  SystemOpenMap = CfgData::GetSystemOpenMap(v1);
  std::map<int,SystemOpenGift>::map(&SystemOpenGifts, SystemOpenMap);
  for ( iter._M_node = std::map<int,SystemOpenGift>::begin(&SystemOpenGifts)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<int,SystemOpenGift>::end(&SystemOpenGifts)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator->(&iter);
    NewRecord = OldRecord | (1 << (LOBYTE(v3->first) - 1));
    if ( NewRecord != OldRecord )
    {
      v4 = 0;
      goto LABEL_7;
    }
  }
  v4 = 1;
LABEL_7:
  std::map<int,SystemOpenGift>::~map(&SystemOpenGifts);
  return v4;
}


#####################################
int32_t __cdecl CFunctionOpen::CanGetRewardCount(CFunctionOpen *const this)
{
  CfgData *v1; // rax
  const SystemOpenGiftMap *SystemOpenMap; // rax
  std::pair<const int,SystemOpenGift> *v3; // rax
  int32_t TypeId; // edx
  int32_t v5; // ebx
  SystemOpenGiftMap SystemOpenGifts; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SystemOpenGift> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,SystemOpenGift> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t Count; // [rsp+64h] [rbp-1Ch]
  int32_t OldRecord; // [rsp+68h] [rbp-18h]
  int32_t NewRecord; // [rsp+6Ch] [rbp-14h]

  Count = 0;
  OldRecord = Player::getRecord(this->m_pPlayer, 1151);
  v1 = Answer::Singleton<CfgData>::instance();
  SystemOpenMap = CfgData::GetSystemOpenMap(v1);
  std::map<int,SystemOpenGift>::map(&SystemOpenGifts, SystemOpenMap);
  for ( it._M_node = std::map<int,SystemOpenGift>::begin(&SystemOpenGifts)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,SystemOpenGift>::end(&SystemOpenGifts)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator->(&it);
    NewRecord = OldRecord | (1 << (LOBYTE(v3->first) - 1));
    if ( NewRecord != OldRecord )
    {
      TypeId = std::_Rb_tree_iterator<std::pair<int const,SystemOpenGift>>::operator->(&it)->second.TypeId;
      if ( CFunctionOpen::IsOpened(this, TypeId) )
        ++Count;
    }
  }
  v5 = Count;
  std::map<int,SystemOpenGift>::~map(&SystemOpenGifts);
  return v5;
}


#####################################
void __cdecl CFunctionOpen::InitFunctionOpen(CFunctionOpen *const this, int32_t TaskId, int32_t Level)
{
  CfgData *v3; // rax
  FunctionOpenCfgMap *OpenFunctionTable; // rax
  int32_t v5; // ebx
  CfgData *v6; // rax
  CfgData *v7; // rax
  std::pair<const int,FunctionOpenCfg> *v8; // rax
  FunctionOpenCfgMap CfgTable; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenCfg> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenCfg> > __x; // [rsp+50h] [rbp-30h] BYREF
  CfgTask *pTask; // [rsp+60h] [rbp-20h]
  CfgTask *pCfgLastTrunk; // [rsp+68h] [rbp-18h]

  v3 = Answer::Singleton<CfgData>::instance();
  OpenFunctionTable = CfgData::GetOpenFunctionTable(v3);
  std::map<int,FunctionOpenCfg>::map(&CfgTable, OpenFunctionTable);
  for ( it._M_node = std::map<int,FunctionOpenCfg>::begin(&CfgTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator++(&it) )
  {
    __x._M_node = std::map<int,FunctionOpenCfg>::end(&CfgTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator!=(&it, &__x) )
      break;
    if ( TaskId <= 0 )
    {
      if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.TaskId <= 0
        && std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.Level <= Level )
      {
LABEL_10:
        v8 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it);
        std::list<int>::push_back(&this->m_OpenedList, &v8->first);
        continue;
      }
    }
    else if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.TaskId > 0 )
    {
      v5 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.TaskId;
      v6 = Answer::Singleton<CfgData>::instance();
      pTask = CfgData::getTask(v6, v5);
      if ( pTask )
      {
        v7 = Answer::Singleton<CfgData>::instance();
        pCfgLastTrunk = CfgData::getTask(v7, TaskId);
        if ( pCfgLastTrunk )
        {
          if ( pCfgLastTrunk->main_order > pTask->main_order )
            goto LABEL_10;
        }
      }
    }
  }
  std::map<int,FunctionOpenCfg>::~map(&CfgTable);
}


#####################################
void __cdecl CFunctionOpen::CheckFunctionOpne(CFunctionOpen *const this, int32_t TaskId, int32_t Level)
{
  CfgData *v3; // rax
  FunctionOpenCfgMap *OpenFunctionTable; // rax
  int32_t v5; // ebx
  CfgData *v6; // rax
  CfgData *v7; // rax
  int v8; // edx
  int first; // edx
  std::pair<const int,FunctionOpenCfg> *v10; // rax
  std::pair<const int,FunctionOpenCfg> *v11; // rax
  int32_t v12; // edx
  FunctionOpenCfgMap CfgTable; // [rsp+10h] [rbp-A0h] BYREF
  std::_List_iterator<int> itList; // [rsp+40h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenCfg> > it; // [rsp+50h] [rbp-60h] BYREF
  std::list<int> NewOpenList; // [rsp+60h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenCfg> > __x; // [rsp+70h] [rbp-40h] BYREF
  std::_List_iterator<int> v19; // [rsp+80h] [rbp-30h] BYREF
  CfgTask *pTask; // [rsp+90h] [rbp-20h]
  CfgTask *pCfgLastTrunk; // [rsp+98h] [rbp-18h]

  std::list<int>::list(&NewOpenList);
  std::list<int>::clear(&NewOpenList);
  v3 = Answer::Singleton<CfgData>::instance();
  OpenFunctionTable = CfgData::GetOpenFunctionTable(v3);
  std::map<int,FunctionOpenCfg>::map(&CfgTable, OpenFunctionTable);
  for ( it._M_node = std::map<int,FunctionOpenCfg>::begin(&CfgTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator++(&it) )
  {
    __x._M_node = std::map<int,FunctionOpenCfg>::end(&CfgTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator!=(&it, &__x) )
      break;
    if ( TaskId <= 0 )
    {
      if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.TaskId <= 0
        && std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.Level <= Level )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->first;
        if ( !CFunctionOpen::IsOpened(this, first) )
        {
LABEL_12:
          v10 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it);
          std::list<int>::push_back(&this->m_OpenedList, &v10->first);
          v11 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it);
          std::list<int>::push_back(&NewOpenList, &v11->first);
          continue;
        }
      }
    }
    else if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.TaskId > 0 )
    {
      v5 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->second.TaskId;
      v6 = Answer::Singleton<CfgData>::instance();
      pTask = CfgData::getTask(v6, v5);
      if ( pTask )
      {
        v7 = Answer::Singleton<CfgData>::instance();
        pCfgLastTrunk = CfgData::getTask(v7, TaskId);
        if ( pCfgLastTrunk )
        {
          if ( pCfgLastTrunk->main_order >= pTask->main_order )
          {
            v8 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenCfg>>::operator->(&it)->first;
            if ( !CFunctionOpen::IsOpened(this, v8) )
              goto LABEL_12;
          }
        }
      }
    }
  }
  for ( itList._M_node = std::list<int>::begin(&NewOpenList)._M_node; ; std::_List_iterator<int>::operator++(&itList) )
  {
    v19._M_node = std::list<int>::end(&NewOpenList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&itList, &v19) )
      break;
    v12 = *std::_List_iterator<int>::operator*(&itList);
    CFunctionOpen::FunctionInit(this, v12);
  }
  std::map<int,FunctionOpenCfg>::~map(&CfgTable);
  std::list<int>::~list(&NewOpenList);
}


#####################################
void __cdecl CFunctionOpen::FunctionInit(CFunctionOpen *const this, int32_t FunctionId)
{
  CExtCharPet *CharPet; // rax
  Player *m_pPlayer; // rbx
  CWorldBoss *v4; // rax
  DailyActivity *PlayerDailyActivity; // rax
  DailyActivity *v6; // rax
  CExtChrTaskCycle *CharTaskCycle; // rax
  CYunYingHD *PlayerYunYingHd; // rax
  CYunYingHD *v9; // rax
  CYunYingHD *v10; // rax
  CYunYingHD *v11; // rax
  CTouZi *TouZi; // rax
  Player *v13; // rbx
  CKaiFuHuoDong *v14; // rax
  Player *v15; // rbx
  CKaiFuHuoDong *v16; // rax
  CExtCharHallOfFame *CharHallOfFame; // rax
  CQiFu *PlayerQiFu; // rax
  CExtCharTitle *CharTitle; // rax
  DailyActivity *v20; // rax
  CExtCharWing *CharWing; // rax
  DailyActivity *v22; // rax
  CTianLing *TianLing; // rax
  CTianLing *v24; // rax
  CTianLing *v25; // rax
  ChouJiang *PlayerChouJiang; // rax
  CMoneyRewardTask *CMoneyRewardTask; // rax
  CMoneyRewardTask *v28; // rax
  CMoneyRewardTask *v29; // rax
  CSpecialEquip *CSpecialEquip; // rax
  CLevelRefining *CLevelRefining; // rax
  CBossKilledReward *CBossKilledReward; // rax
  CTestServerReward *CTestServerReward; // rax
  CMoneyRewardTask *v34; // rax
  CMoneyRewardTask *v35; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  CSuperTeHui *CSuperTeHui; // rax
  CWan360 *Wan360; // rax
  CWan360 *v39; // rax
  CMonthlyChouJiang *CMonthlyChouJiang; // rax
  CYunYingHD *v41; // rax

  if ( this->m_pPlayer )
  {
    switch ( FunctionId )
    {
      case 25:
        CharTitle = Player::GetCharTitle(this->m_pPlayer);
        CExtCharTitle::InitTitle(CharTitle);
        break;
      case 26:
        CharTaskCycle = Player::GetCharTaskCycle(this->m_pPlayer);
        CExtChrTaskCycle::OpenCycleTask(CharTaskCycle);
        break;
      case 32:
        CharPet = Player::GetCharPet(this->m_pPlayer);
        CExtCharPet::OnInitPet(CharPet);
        break;
      case 53:
        m_pPlayer = this->m_pPlayer;
        v4 = Answer::Singleton<CWorldBoss>::instance();
        CWorldBoss::SendWorldBossIcon(v4, m_pPlayer);
        break;
      case 57:
        PlayerQiFu = Player::GetPlayerQiFu(this->m_pPlayer);
        CQiFu::SendQIFuIcon(PlayerQiFu);
        break;
      case 59:
        PlayerDailyActivity = Player::GetPlayerDailyActivity(this->m_pPlayer);
        DailyActivity::SendHuoDongDaTingIcon(PlayerDailyActivity);
        break;
      case 60:
      case 108:
        v6 = Player::GetPlayerDailyActivity(this->m_pPlayer);
        DailyActivity::SendJiangLiDaTingIcon(v6);
        break;
      case 62:
        PlayerYunYingHd = Player::GetPlayerYunYingHd(this->m_pPlayer);
        CYunYingHD::SendShouChongIcon(PlayerYunYingHd);
        break;
      case 63:
        v9 = Player::GetPlayerYunYingHd(this->m_pPlayer);
        CYunYingHD::SendTeHuiIcon(v9);
        break;
      case 64:
        v10 = Player::GetPlayerYunYingHd(this->m_pPlayer);
        CYunYingHD::SendEveryDayChongZhiIcon(v10, 3);
        v11 = Player::GetPlayerYunYingHd(this->m_pPlayer);
        CYunYingHD::SendEveryDayChongZhiIcon(v11, 2);
        break;
      case 65:
        TouZi = Player::GetPlayerGetTouZi(this->m_pPlayer);
        CTouZi::SendTouZiIcon(TouZi);
        break;
      case 66:
        v13 = this->m_pPlayer;
        v14 = Answer::Singleton<CKaiFuHuoDong>::instance();
        CKaiFuHuoDong::SendKaiFuHuoDongIcon(v14, v13);
        v15 = this->m_pPlayer;
        v16 = Answer::Singleton<CKaiFuHuoDong>::instance();
        CKaiFuHuoDong::SendKaiFuPetIcon(v16, v15);
        break;
      case 68:
        CharHallOfFame = Player::GetCharHallOfFame(this->m_pPlayer);
        CExtCharHallOfFame::SendIconState(CharHallOfFame, 0);
        break;
      case 112:
        v20 = Player::GetPlayerDailyActivity(this->m_pPlayer);
        DailyActivity::SendSevenDayLoginIcon(v20);
        break;
      case 140:
        CharWing = Player::GetCharWing(this->m_pPlayer);
        CExtCharWing::OnFunctionOpen(CharWing);
        break;
      case 167:
        Player::SendDungeonHallIcon(this->m_pPlayer);
        break;
      case 168:
        v22 = Player::GetPlayerDailyActivity(this->m_pPlayer);
        DailyActivity::SendSearchBackIcon(v22);
        break;
      case 173:
        Player::SendQuestionAnswerIcon(this->m_pPlayer);
        break;
      case 175:
        TianLing = Player::GetTianLing(this->m_pPlayer);
        CTianLing::InitTianLing(TianLing);
        break;
      case 177:
        PlayerChouJiang = Player::GetPlayerChouJiang(this->m_pPlayer);
        ChouJiang::SendHuoDongIcon(PlayerChouJiang);
        break;
      case 178:
        CMoneyRewardTask = Player::GetCMoneyRewardTask(this->m_pPlayer);
        CMoneyRewardTask::OnFunctionOpen(CMoneyRewardTask);
        break;
      case 179:
        v28 = Player::GetCMoneyRewardTask(this->m_pPlayer);
        CMoneyRewardTask::OnPdbfFunctionOpen(v28);
        break;
      case 180:
        v29 = Player::GetCMoneyRewardTask(this->m_pPlayer);
        CMoneyRewardTask::OnBackEquipFunctionOpen(v29);
        break;
      case 181:
        CSpecialEquip = Player::GetCSpecialEquip(this->m_pPlayer);
        CSpecialEquip::SendSpecialEquipIcon(CSpecialEquip);
        break;
      case 186:
        CLevelRefining = Player::GetCLevelRefining(this->m_pPlayer);
        CLevelRefining::SendIcon(CLevelRefining);
        break;
      case 188:
        Player::RecalcAttr(this->m_pPlayer);
        break;
      case 190:
        CBossKilledReward = Player::GetCBossKilledReward(this->m_pPlayer);
        CBossKilledReward::SendBossKilledIcon(CBossKilledReward);
        break;
      case 192:
        CTestServerReward = Player::GetCTestServerReward(this->m_pPlayer);
        CTestServerReward::SendTestServerIcon(CTestServerReward);
        break;
      case 193:
        v34 = Player::GetCMoneyRewardTask(this->m_pPlayer);
        CMoneyRewardTask::OnXiangYaoFunctionOpen(v34);
        break;
      case 194:
        v35 = Player::GetCMoneyRewardTask(this->m_pPlayer);
        CMoneyRewardTask::OnShenWeiFunctionOpen(v35);
        break;
      case 195:
        Player::sendJoinQQIcon(this->m_pPlayer);
        break;
      case 197:
        PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
        CHuoYueDu::SendtHuoYueDuIcon(PlayerHuoYueDu);
        break;
      case 201:
        CSuperTeHui = Player::GetCSuperTeHui(this->m_pPlayer);
        CSuperTeHui::SendSuperTeHuiIcon(CSuperTeHui);
        break;
      case 210:
        CMonthlyChouJiang = Player::GetCMonthlyChouJiang(this->m_pPlayer);
        CMonthlyChouJiang::SendIcon(CMonthlyChouJiang);
        break;
      case 211:
        Wan360 = Player::GetWan360(this->m_pPlayer);
        CWan360::SendWeiXinIcon(Wan360);
        break;
      case 212:
        v39 = Player::GetWan360(this->m_pPlayer);
        CWan360::SendGameAppIcon(v39);
        break;
      case 235:
        v24 = Player::GetTianLing(this->m_pPlayer);
        CTianLing::InitZhanHun(v24);
        break;
      case 237:
        v41 = Player::GetPlayerYunYingHd(this->m_pPlayer);
        CYunYingHD::OnZeroBuyPetOpen(v41);
        break;
      case 240:
        v25 = Player::GetTianLing(this->m_pPlayer);
        CTianLing::InitSunAndMoon(v25);
        break;
      default:
        break;
    }
    CFunctionOpen::SendSysOpenIcon(this);
  }
}


#####################################
bool __cdecl CFunctionOpen::IsOpened(CFunctionOpen *const this, int32_t FunctionId)
{
  CfgData *v2; // rax
  std::_List_iterator<int> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-10h] BYREF

  v2 = Answer::Singleton<CfgData>::instance();
  if ( !CfgData::GetOpenFunctionCfg(v2, FunctionId) )
    return 1;
  for ( it._M_node = std::list<int>::begin(&this->m_OpenedList)._M_node; ; std::_List_iterator<int>::operator++(&it) )
  {
    __x._M_node = std::list<int>::end(&this->m_OpenedList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    if ( *std::_List_iterator<int>::operator*(&it) == FunctionId )
      return 1;
  }
  return 0;
}


#####################################
void __cdecl CFunctionOpen::OnDaySwitch(CFunctionOpen *const this, int32_t nDiffDays)
{
  GameService *v2; // rax
  CfgData *v3; // rax
  int32_t v4; // edx

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    v4 = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1;
    CFunctionOpen::CheckFunctionOpenMailByKaiFuDay(this, v4);
  }
}


#####################################
void __cdecl CFunctionOpen::InitFunctionOpenMailByLevel(CFunctionOpen *const this, int32_t nLevel)
{
  GameService *v2; // rax
  CfgData *v3; // rax
  FunctionOpenMailMap *OpenFunctionMailTable; // rax
  int first; // edx
  FunctionOpenMailMap CfgTable; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > __x; // [rsp+50h] [rbp-20h] BYREF

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    OpenFunctionMailTable = CfgData::GetOpenFunctionMailTable(v3);
    std::map<int,FunctionOpenMail>::map(&CfgTable, OpenFunctionMailTable);
    for ( it._M_node = std::map<int,FunctionOpenMail>::begin(&CfgTable)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator++(&it) )
    {
      __x._M_node = std::map<int,FunctionOpenMail>::end(&CfgTable)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator!=(&it, &__x) )
        break;
      if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nLevel > 0
        && std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nLevel <= nLevel )
      {
        first = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->first;
        CFunctionOpen::AddSendMailList(this, first);
      }
    }
    std::map<int,FunctionOpenMail>::~map(&CfgTable);
  }
}


#####################################
void __cdecl CFunctionOpen::InitFunctionOpenMailByKaiFuDay(CFunctionOpen *const this, int32_t KaiFuDay)
{
  GameService *v2; // rax
  CfgData *v3; // rax
  FunctionOpenMailMap *OpenFunctionMailTable; // rax
  std::pair<const int,FunctionOpenMail> *v5; // rax
  int first; // edx
  FunctionOpenMailMap CfgTable; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t nId; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) != 9 )
    {
      nId = Player::getRecord(this->m_pPlayer, 1916);
      if ( nId > 0 )
      {
        v3 = Answer::Singleton<CfgData>::instance();
        OpenFunctionMailTable = CfgData::GetOpenFunctionMailTable(v3);
        std::map<int,FunctionOpenMail>::map(&CfgTable, OpenFunctionMailTable);
        for ( it._M_node = std::map<int,FunctionOpenMail>::begin(&CfgTable)._M_node;
              ;
              std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator++(&it) )
        {
          __x._M_node = std::map<int,FunctionOpenMail>::end(&CfgTable)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator!=(&it, &__x) )
            break;
          if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nLevel <= 0 )
          {
            v5 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it);
            if ( v5->first <= nId )
            {
              first = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->first;
              CFunctionOpen::AddSendMailList(this, first);
            }
          }
        }
        Player::updateRecord(this->m_pPlayer, 1916, 0);
        std::map<int,FunctionOpenMail>::~map(&CfgTable);
      }
    }
  }
}


#####################################
void __cdecl CFunctionOpen::CheckFunctionOpenMailByLevel(CFunctionOpen *const this, int32_t nLevel)
{
  GameService *v2; // rax
  CfgData *v3; // rax
  FunctionOpenMailMap *OpenFunctionMailTable; // rax
  int first; // edx
  int v6; // edx
  int32_t nMailID; // r12d
  CharId_t Cid; // rbx
  DBService *v9; // rax
  FunctionOpenMailMap CfgTable; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > __x; // [rsp+50h] [rbp-30h] BYREF
  std::string Param; // [rsp+60h] [rbp-20h] BYREF
  _BYTE v14[17]; // [rsp+6Fh] [rbp-11h] BYREF

  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) != 9 )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      OpenFunctionMailTable = CfgData::GetOpenFunctionMailTable(v3);
      std::map<int,FunctionOpenMail>::map(&CfgTable, OpenFunctionMailTable);
      for ( it._M_node = std::map<int,FunctionOpenMail>::begin(&CfgTable)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator++(&it) )
      {
        __x._M_node = std::map<int,FunctionOpenMail>::end(&CfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator!=(&it, &__x) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nLevel > 0 )
        {
          first = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->first;
          if ( !CFunctionOpen::IsSendedMail(this, first)
            && std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nLevel <= nLevel )
          {
            v6 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->first;
            CFunctionOpen::AddSendMailList(this, v6);
            std::allocator<char>::allocator(v14);
            std::string::string(&Param, &unk_8DA4E0, v14);
            nMailID = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nMailID;
            Cid = Player::getCid(this->m_pPlayer);
            v9 = Answer::Singleton<DBService>::instance();
            DBService::OnSendSysMail(v9, 0, Cid, nMailID, &Param, 0);
            std::string::~string(&Param);
            std::allocator<char>::~allocator(v14);
          }
        }
      }
      std::map<int,FunctionOpenMail>::~map(&CfgTable);
    }
  }
}


#####################################
void __cdecl CFunctionOpen::CheckFunctionOpenMailByKaiFuDay(CFunctionOpen *const this, int32_t nKaiFuDay)
{
  GameService *v2; // rax
  CfgData *v3; // rax
  FunctionOpenMailMap *OpenFunctionMailTable; // rax
  int first; // edx
  int32_t v6; // ebx
  int v8; // edx
  int32_t nMailID; // r12d
  CharId_t Cid; // rbx
  DBService *v11; // rax
  FunctionOpenMailMap CfgTable; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,FunctionOpenMail> > __x; // [rsp+50h] [rbp-30h] BYREF
  std::string Param; // [rsp+60h] [rbp-20h] BYREF
  _BYTE v16[17]; // [rsp+6Fh] [rbp-11h] BYREF

  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<GameService>::instance();
    if ( GameService::getLine(v2) != 9 )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      OpenFunctionMailTable = CfgData::GetOpenFunctionMailTable(v3);
      std::map<int,FunctionOpenMail>::map(&CfgTable, OpenFunctionMailTable);
      for ( it._M_node = std::map<int,FunctionOpenMail>::begin(&CfgTable)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator++(&it) )
      {
        __x._M_node = std::map<int,FunctionOpenMail>::end(&CfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator!=(&it, &__x) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nLevel <= 0 )
        {
          first = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->first;
          if ( !CFunctionOpen::IsSendedMail(this, first)
            && std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nDay <= nKaiFuDay )
          {
            v6 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
            if ( v6 >= std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nDayLevel )
            {
              v8 = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->first;
              CFunctionOpen::AddSendMailList(this, v8);
              std::allocator<char>::allocator(v16);
              std::string::string(&Param, &unk_8DA4E0, v16);
              nMailID = std::_Rb_tree_iterator<std::pair<int const,FunctionOpenMail>>::operator->(&it)->second.nMailID;
              Cid = Player::getCid(this->m_pPlayer);
              v11 = Answer::Singleton<DBService>::instance();
              DBService::OnSendSysMail(v11, 0, Cid, nMailID, &Param, 0);
              std::string::~string(&Param);
              std::allocator<char>::~allocator(v16);
            }
          }
        }
      }
      std::map<int,FunctionOpenMail>::~map(&CfgTable);
    }
  }
}


#####################################
void __cdecl CFunctionOpen::AddSendMailList(CFunctionOpen *const this, int32_t nId)
{
  if ( nId > 0 && nId <= 199 )
    Player::updateRecord(this->m_pPlayer, nId + 31100, 1);
}


#####################################
bool __cdecl CFunctionOpen::IsSendedMail(CFunctionOpen *const this, int32_t Id)
{
  return Player::getRecord(this->m_pPlayer, Id + 31100) > 0;
}


