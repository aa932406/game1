// Decompiled methods for class: CMoneyRewardTask
// Source: gameserver.cc
// Total methods: 64

#####################################
void __cdecl CMoneyRewardTask::~CMoneyRewardTask(CMoneyRewardTask *const this)
{
  CMoneyRewardTask::~CMoneyRewardTask(this);
  operator delete(this);
}


#####################################
void __cdecl CMoneyRewardTask::OnCleanUp(CMoneyRewardTask *const this)
{
  int32_t i; // [rsp+Ch] [rbp-Ch]
  int32_t j; // [rsp+10h] [rbp-8h]
  int32_t k; // [rsp+14h] [rbp-4h]

  for ( i = 0; i <= 8; ++i )
  {
    this->m_MoneyRewardTask[i].TaskId = 0;
    this->m_MoneyRewardTask[i].TaskState = 0;
  }
  this->m_IsGetReward = 0;
  this->m_FinishTimes = 0;
  this->m_TaskId = 0;
  this->m_Star = 0;
  this->m_RandStarTimes = 0;
  this->m_PdbfFinishTimes = 0;
  this->m_EquipBackTaskId = 0;
  this->m_EquipBackTaskFinishTimes = 0;
  this->m_RandEquipBackTaskStarTimes = 0;
  for ( j = 0; j <= 3; ++j )
  {
    this->m_XiangYaoTask[j].TaskId = 0;
    this->m_XiangYaoTask[j].TaskState = 0;
  }
  this->m_XiangYaoFinishTimes = 0;
  this->m_RefreshTimes = 0;
  for ( k = 0; k <= 4; ++k )
    this->m_ShenWeiTaskState[k] = 0;
}


#####################################
void __cdecl CMoneyRewardTask::OnLoadFromDB(CMoneyRewardTask *const this, const PlayerDBData *const dbData)
{
  std::string p_TaskInfoString; // [rsp+10h] [rbp-40h] BYREF
  std::string p_InfoString; // [rsp+20h] [rbp-30h] BYREF
  std::string v5; // [rsp+30h] [rbp-20h] BYREF

  this->m_FinishTimes = dbData->m_MoneyRewardTaskData.m_FinishTimes;
  this->m_IsGetReward = dbData->m_MoneyRewardTaskData.m_IsGetReward;
  this->m_TaskId = dbData->m_MoneyRewardTaskData.m_TaskId;
  this->m_Star = dbData->m_MoneyRewardTaskData.m_Star;
  this->m_RandStarTimes = dbData->m_MoneyRewardTaskData.m_RandStarTimes;
  this->m_PdbfFinishTimes = dbData->m_MoneyRewardTaskData.m_PdbfFinishTimes;
  this->m_EquipBackTaskId = dbData->m_MoneyRewardTaskData.m_EquipBackTaskId;
  this->m_EquipBackTaskFinishTimes = dbData->m_MoneyRewardTaskData.m_EquipBackTaskFinishTimes;
  this->m_RandEquipBackTaskStarTimes = dbData->m_MoneyRewardTaskData.m_RandEquipBackTaskStarTimes;
  this->m_JieBiaoTimes = dbData->m_MoneyRewardTaskData.m_JieBiaoTimes;
  this->m_YaBiaoTimes = dbData->m_MoneyRewardTaskData.m_YaBiaoTimes;
  this->m_TrailerQuality = dbData->m_MoneyRewardTaskData.m_TrailerQuality;
  this->m_EndTime = dbData->m_MoneyRewardTaskData.m_EndTime;
  this->m_XiangYaoFinishTimes = dbData->m_MoneyRewardTaskData.m_XiangYaoFinishTimes;
  this->m_RefreshTimes = dbData->m_MoneyRewardTaskData.m_RefreshTimes;
  std::string::string(&p_TaskInfoString, &dbData->m_MoneyRewardTaskData.m_XiangYaoTask);
  CMoneyRewardTask::parseXiangYaoTask(this, &p_TaskInfoString);
  std::string::~string(&p_TaskInfoString);
  std::string::string(&p_InfoString, &dbData->m_MoneyRewardTaskData.m_MoneyRewardTaskInfo);
  CMoneyRewardTask::parseMoneyRewardTaskInfo(this, &p_InfoString);
  std::string::~string(&p_InfoString);
  std::string::string(&v5, &dbData->m_MoneyRewardTaskData.m_ShenWeiTask);
  CMoneyRewardTask::parseShenWeiTask(this, &v5);
  std::string::~string(&v5);
  if ( CMoneyRewardTask::IsPdbfFunctionOpen(this)
    && !this->m_TaskId
    && !this->m_Star
    && !this->m_RandStarTimes
    && !this->m_PdbfFinishTimes )
  {
    CMoneyRewardTask::InitPdbfTask(this);
  }
  if ( CMoneyRewardTask::IsBackEquipFunctionOpen(this)
    && !this->m_EquipBackTaskId
    && !this->m_EquipBackTaskFinishTimes
    && !this->m_RandEquipBackTaskStarTimes )
  {
    CMoneyRewardTask::InitEquipBackTask(this);
  }
  if ( this->m_pPlayer )
  {
    if ( this->m_EndTime > 0 && Unit::getNow(this->m_pPlayer) > this->m_EndTime )
    {
      CMoneyRewardTask::ResetTrailer(this);
      this->m_EndTime = 0;
    }
  }
  if ( !this->m_TrailerQuality )
    CMoneyRewardTask::ResetTrailer(this);
  CMoneyRewardTask::LoginInitXiangYaoTask(this);
  CMoneyRewardTask::LoginInitShenWeiTask(this);
}


#####################################
void __cdecl CMoneyRewardTask::OnSaveToDB(CMoneyRewardTask *const this, PlayerDBData *const dbData)
{
  _BYTE v2[16]; // [rsp+10h] [rbp-40h] BYREF
  _BYTE v3[16]; // [rsp+20h] [rbp-30h] BYREF
  _BYTE v4[32]; // [rsp+30h] [rbp-20h] BYREF

  dbData->m_MoneyRewardTaskData.m_FinishTimes = this->m_FinishTimes;
  dbData->m_MoneyRewardTaskData.m_IsGetReward = this->m_IsGetReward;
  CMoneyRewardTask::GetMoneyRewardTaskInfo((CMoneyRewardTask *const)v2);
  std::string::operator=(&dbData->m_MoneyRewardTaskData.m_MoneyRewardTaskInfo, v2);
  std::string::~string(v2);
  dbData->m_MoneyRewardTaskData.m_TaskId = this->m_TaskId;
  dbData->m_MoneyRewardTaskData.m_Star = this->m_Star;
  dbData->m_MoneyRewardTaskData.m_RandStarTimes = this->m_RandStarTimes;
  dbData->m_MoneyRewardTaskData.m_PdbfFinishTimes = this->m_PdbfFinishTimes;
  dbData->m_MoneyRewardTaskData.m_EquipBackTaskId = this->m_EquipBackTaskId;
  dbData->m_MoneyRewardTaskData.m_EquipBackTaskFinishTimes = this->m_EquipBackTaskFinishTimes;
  dbData->m_MoneyRewardTaskData.m_RandEquipBackTaskStarTimes = this->m_RandEquipBackTaskStarTimes;
  dbData->m_MoneyRewardTaskData.m_JieBiaoTimes = this->m_JieBiaoTimes;
  dbData->m_MoneyRewardTaskData.m_YaBiaoTimes = this->m_YaBiaoTimes;
  dbData->m_MoneyRewardTaskData.m_TrailerQuality = this->m_TrailerQuality;
  dbData->m_MoneyRewardTaskData.m_EndTime = this->m_EndTime;
  dbData->m_MoneyRewardTaskData.m_XiangYaoFinishTimes = this->m_XiangYaoFinishTimes;
  dbData->m_MoneyRewardTaskData.m_RefreshTimes = this->m_RefreshTimes;
  CMoneyRewardTask::saveXiangYaoTaskString((CMoneyRewardTask *const)v3);
  std::string::operator=(&dbData->m_MoneyRewardTaskData.m_XiangYaoTask, v3);
  std::string::~string(v3);
  CMoneyRewardTask::saveShenWeiTaskString((CMoneyRewardTask *const)v4);
  std::string::operator=(&dbData->m_MoneyRewardTaskData.m_ShenWeiTask, v4);
  std::string::~string(v4);
}


#####################################
void __cdecl CMoneyRewardTask::OnDaySwitch(CMoneyRewardTask *const this, int32_t nDiffDays)
{
  if ( CMoneyRewardTask::IsFunctionOpen(this) )
    CMoneyRewardTask::InitMoneyRewardTask(this);
  if ( CMoneyRewardTask::IsPdbfFunctionOpen(this) )
    CMoneyRewardTask::InitPdbfTask(this);
  if ( CMoneyRewardTask::IsBackEquipFunctionOpen(this) )
    CMoneyRewardTask::InitEquipBackTask(this);
  if ( CMoneyRewardTask::IsXiangYaoFunctionOpen(this) )
    CMoneyRewardTask::InitXiangYaoTask(this);
  if ( CMoneyRewardTask::IsShenWeiFunctionOPen(this) )
    CMoneyRewardTask::InitShenWeiTask(this);
  if ( Player::getRecord(this->m_pPlayer, 1001) )
  {
    CMoneyRewardTask::InitXuWuTask(this);
    CMoneyRewardTask::InitXinMoTask(this);
  }
  this->m_JieBiaoTimes = 0;
  this->m_YaBiaoTimes = 0;
  CMoneyRewardTask::SendTrailerInfo(this);
}


#####################################
void __cdecl CMoneyRewardTask::GetInterestsProtocol(CMoneyRewardTask *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-26h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-24h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-22h] BYREF
  unsigned __int16 v5; // [rsp+20h] [rbp-20h] BYREF
  unsigned __int16 v6; // [rsp+22h] [rbp-1Eh] BYREF
  unsigned __int16 v7; // [rsp+24h] [rbp-1Ch] BYREF
  unsigned __int16 v8; // [rsp+26h] [rbp-1Ah] BYREF
  unsigned __int16 v9; // [rsp+28h] [rbp-18h] BYREF
  unsigned __int16 v10; // [rsp+2Ah] [rbp-16h] BYREF
  unsigned __int16 v11; // [rsp+2Ch] [rbp-14h] BYREF
  unsigned __int16 v12; // [rsp+2Eh] [rbp-12h] BYREF
  unsigned __int16 v13; // [rsp+30h] [rbp-10h] BYREF
  unsigned __int16 v14; // [rsp+32h] [rbp-Eh] BYREF
  unsigned __int16 v15; // [rsp+34h] [rbp-Ch] BYREF
  unsigned __int16 v16; // [rsp+36h] [rbp-Ah] BYREF
  unsigned __int16 v17; // [rsp+38h] [rbp-8h] BYREF
  unsigned __int16 v18; // [rsp+3Ah] [rbp-6h] BYREF
  unsigned __int16 v19; // [rsp+3Ch] [rbp-4h] BYREF
  unsigned __int16 v20; // [rsp+3Eh] [rbp-2h] BYREF

  __x = 625;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 627;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 628;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 629;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 630;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 631;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 632;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 633;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 634;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 635;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 636;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 637;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 638;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 639;
  std::list<unsigned short>::push_back(procList, &v15);
  v16 = 640;
  std::list<unsigned short>::push_back(procList, &v16);
  v17 = 641;
  std::list<unsigned short>::push_back(procList, &v17);
  v18 = 642;
  std::list<unsigned short>::push_back(procList, &v18);
  v19 = 643;
  std::list<unsigned short>::push_back(procList, &v19);
  v20 = 644;
  std::list<unsigned short>::push_back(procList, &v20);
}


#####################################
int32_t __cdecl CMoneyRewardTask::DispatchNetDatas(
        CMoneyRewardTask *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x271u:
      result = CMoneyRewardTask::OnSubmitMoneyRewardTask(this, inPacket);
      break;
    case 0x273u:
      result = CMoneyRewardTask::OnGetReward(this, inPacket);
      break;
    case 0x274u:
      result = CMoneyRewardTask::OnSubmitPdbfTask(this, inPacket);
      break;
    case 0x275u:
      result = CMoneyRewardTask::OnPdbfRandStar(this, inPacket);
      break;
    case 0x276u:
      result = CMoneyRewardTask::OnSubmitEquipBackTask(this, inPacket);
      break;
    case 0x277u:
      result = CMoneyRewardTask::OnEquipBackTaskRandStar(this, inPacket);
      break;
    case 0x278u:
      result = CMoneyRewardTask::OnReceivePdbfTask(this, inPacket);
      break;
    case 0x279u:
      result = CMoneyRewardTask::OnAskTrailerPos(this, inPacket);
      break;
    case 0x27Au:
      result = CMoneyRewardTask::OnRandTrailer(this, inPacket);
      break;
    case 0x27Bu:
      result = CMoneyRewardTask::OnStartTrailer(this, inPacket);
      break;
    case 0x27Cu:
      result = CMoneyRewardTask::OnSubTrailer(this, inPacket);
      break;
    case 0x27Du:
      result = CMoneyRewardTask::OnRequestSupport(this, inPacket);
      break;
    case 0x27Eu:
      result = CMoneyRewardTask::OnReceiveMoneyRewardTask(this, inPacket);
      break;
    case 0x27Fu:
      result = CMoneyRewardTask::OnReceiveEquipBackTask(this, inPacket);
      break;
    case 0x280u:
      result = CMoneyRewardTask::OneKeyCompletion(this, inPacket);
      break;
    case 0x281u:
      result = CMoneyRewardTask::OnAskXiangYaoTask(this, inPacket);
      break;
    case 0x282u:
      result = CMoneyRewardTask::OnOperatorTask(this, inPacket);
      break;
    case 0x283u:
      result = CMoneyRewardTask::OnRefreshTask(this, inPacket);
      break;
    case 0x284u:
      result = CMoneyRewardTask::OnOperatorShenWeiTask(this, inPacket);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
bool __cdecl CMoneyRewardTask::IsFunctionOpen(CMoneyRewardTask *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 178) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CMoneyRewardTask::InitMoneyRewardTask(CMoneyRewardTask *const this)
{
  ChrTask *Task; // rax
  int32_t v2; // ebx
  CfgData *v3; // rax

  if ( this->m_pPlayer )
  {
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(Task, 2);
    v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v3 = Answer::Singleton<CfgData>::instance();
    CfgData::InitMoneyRewardTask(v3, (TaskStateInfo (*const)[9])this->m_MoneyRewardTask, v2);
    this->m_MoneyRewardTask[0].TaskState = 2;
    this->m_IsGetReward = 0;
    this->m_FinishTimes = 0;
    CMoneyRewardTask::sendTaskInfo(this);
  }
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnReceiveMoneyRewardTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t TaskId; // ebx
  ChrTask *Task; // rax
  int64_t v5; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( this->m_FinishTimes <= 8u )
  {
    TaskId = this->m_MoneyRewardTask[this->m_FinishTimes].TaskId;
    Task = Player::GetTask(this->m_pPlayer);
    if ( ChrTask::receive(Task, TaskId) )
      return 10002;
    this->m_MoneyRewardTask[this->m_FinishTimes].TaskState = 3;
  }
  CMoneyRewardTask::sendTaskInfo(this);
  v5 = this->m_MoneyRewardTask[this->m_FinishTimes].TaskId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, v5);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnGetReward(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  MemChrBag stu; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( this->m_FinishTimes <= 8 )
    return 10002;
  if ( this->m_IsGetReward > 0 )
    return 10002;
  *(_QWORD *)&stu.itemId = 0x100001B58LL;
  *(_QWORD *)&stu.itemCount = 0x100000001LL;
  *(_QWORD *)&stu.endTime = 0;
  stu.srcId = 0;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &stu, ITEM_CHANGE_REASON::ICR_MONEY_REWARD_TASK) )
    return 10002;
  this->m_IsGetReward = 1;
  CMoneyRewardTask::sendTaskInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnSubmitMoneyRewardTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CVip *PlayerVip; // rax
  int32_t v5; // ebx
  ChrTask *Task; // rax
  CVip *v7; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  int64_t v9; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  int32_t TaskId; // [rsp+18h] [rbp-38h]
  char nTimes; // [rsp+1Fh] [rbp-31h]
  CfgTask *cfgTask; // [rsp+20h] [rbp-30h]
  float Rate; // [rsp+28h] [rbp-28h]
  float Rate_0; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  TaskId = Answer::NetPacket::readInt32(inPacket);
  nTimes = Answer::NetPacket::readInt8(inPacket);
  if ( nTimes <= 0 || nTimes > 2 )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v3, TaskId);
  if ( !cfgTask )
    return 10002;
  if ( nTimes == 2 )
  {
    if ( cfgTask->DoubleGold <= 0 )
      return 10002;
    Rate = 1.0;
    PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
    if ( CVip::GetVipFlg(PlayerVip, 2) )
      Rate = 0.80000001;
    if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < (int)(float)((float)cfgTask->DoubleGold
                                                                                         * Rate) )
      return 10002;
  }
  if ( this->m_FinishTimes > 8u )
    return 10002;
  if ( this->m_MoneyRewardTask[this->m_FinishTimes].TaskId != TaskId )
    return 10002;
  v5 = this->m_MoneyRewardTask[this->m_FinishTimes].TaskId;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::submit(Task, v5, nTimes) )
    return 10002;
  if ( nTimes == 2 )
  {
    if ( cfgTask->DoubleGold <= 0 )
      return 10002;
    Rate_0 = 1.0;
    v7 = Player::GetPlayerVip(this->m_pPlayer);
    if ( CVip::GetVipFlg(v7, 2) )
      Rate_0 = 0.80000001;
    Player::DecCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_GOLD,
      (int)(float)((float)cfgTask->DoubleGold * Rate_0),
      CURRENCY_CHANGE_REASON::MCR_MONEY_TASK_DOUBLE,
      0);
  }
  this->m_MoneyRewardTask[this->m_FinishTimes++].TaskState = 5;
  if ( this->m_FinishTimes > 0 && this->m_FinishTimes <= 8 )
    this->m_MoneyRewardTask[this->m_FinishTimes].TaskState = 2;
  CMoneyRewardTask::sendTaskInfo(this);
  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
  CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 13, 0, 0);
  v9 = this->m_MoneyRewardTask[this->m_FinishTimes].TaskId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v13, ConnId, GateIndex, Proc, v9);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OneKeyCompletion(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CVip *PlayerVip; // rax
  int32_t TaskId; // ebx
  CfgData *v5; // rax
  int32_t v6; // ebx
  CExtCharBag *Bag; // rax
  CVip *v8; // rax
  CExtCharBag *v9; // rax
  CFaBao *PlayerFaBao; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  DailyActivity *PlayerDailyActivity; // rax
  ChrTask *Task; // rax
  ChrTask *v14; // rax
  MemChrBag stu; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+30h] [rbp-70h] BYREF
  MemChrBagVector Items; // [rsp+40h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+60h] [rbp-40h] BYREF
  int32_t Times; // [rsp+6Ch] [rbp-34h]
  int32_t Money; // [rsp+70h] [rbp-30h]
  int32_t FuWen; // [rsp+74h] [rbp-2Ch]
  int32_t NeedGold; // [rsp+78h] [rbp-28h]
  int32_t i; // [rsp+7Ch] [rbp-24h]
  CfgTask *cfgTask; // [rsp+80h] [rbp-20h]
  float Rate; // [rsp+88h] [rbp-18h]
  int32_t i_0; // [rsp+8Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Times = Answer::NetPacket::readInt32(inPacket);
  if ( Times <= 0 || Times > 2 )
    return 10002;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( !CVip::GetVipFlg(PlayerVip, 3) )
    return 10002;
  if ( this->m_FinishTimes > 8 )
    return 10002;
  if ( this->m_FinishTimes < 0 )
    this->m_FinishTimes = 0;
  Money = 0;
  FuWen = 0;
  std::vector<MemChrBag>::vector(&Items);
  NeedGold = 0;
  for ( i = this->m_FinishTimes; i <= 8; ++i )
  {
    TaskId = this->m_MoneyRewardTask[i].TaskId;
    v5 = Answer::Singleton<CfgData>::instance();
    cfgTask = CfgData::getTask(v5, TaskId);
    if ( cfgTask )
    {
      if ( cfgTask->award_money > 0 )
        Money += Times * cfgTask->award_money;
      if ( cfgTask->fuwen > 0 )
        FuWen += Times * cfgTask->fuwen;
      for ( iter._M_current = std::vector<MemChrBag>::begin(&cfgTask->award_item)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&cfgTask->award_item)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
          break;
        memset(&stu, 0, sizeof(stu));
        stu = *__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter);
        stu.itemCount *= Times;
        std::vector<MemChrBag>::push_back(&Items, &stu);
      }
      if ( cfgTask->DoubleGold > 0 )
        NeedGold += cfgTask->DoubleGold;
    }
  }
  v6 = std::vector<MemChrBag>::size(&Items);
  Bag = Player::GetBag(this->m_pPlayer);
  if ( v6 <= CExtCharBag::GetFreeSlotCount(Bag) )
  {
    if ( Times != 2 )
      goto LABEL_48;
    Rate = 1.0;
    v8 = Player::GetPlayerVip(this->m_pPlayer);
    if ( CVip::GetVipFlg(v8, 2) )
      Rate = 0.80000001;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            (int)(float)((float)NeedGold * Rate),
            CURRENCY_CHANGE_REASON::MCR_MONEY_TASK_DOUBLE,
            0) )
    {
      v2 = 10002;
    }
    else
    {
LABEL_48:
      if ( std::vector<MemChrBag>::size(&Items)
        && (v9 = Player::GetBag(this->m_pPlayer), !CExtCharBag::AddItem(v9, &Items, ITEM_CHANGE_REASON::ICR_TASK_REWARD)) )
      {
        v2 = 10002;
      }
      else
      {
        if ( FuWen > 0 )
        {
          PlayerFaBao = Player::GetPlayerFaBao(this->m_pPlayer);
          CFaBao::AddFaBaoRes(PlayerFaBao, 2, FuWen);
        }
        if ( Money > 0 )
          Player::AddCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_BIND_MONEY,
            Money,
            CURRENCY_CHANGE_REASON::MCR_TASK,
            0);
        for ( i_0 = this->m_FinishTimes; i_0 <= 8; ++i_0 )
        {
          this->m_MoneyRewardTask[this->m_FinishTimes++].TaskState = 5;
          PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
          CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 13, 0, 0);
          PlayerDailyActivity = Player::GetPlayerDailyActivity(this->m_pPlayer);
          DailyActivity::AddTaskRecord(PlayerDailyActivity, 2);
        }
        Task = Player::GetTask(this->m_pPlayer);
        ChrTask::CleanTaskType(Task, 2);
        CMoneyRewardTask::sendTaskInfo(this);
        v14 = Player::GetTask(this->m_pPlayer);
        ChrTask::updateTaskTypeCount(v14, 2);
        v2 = 0;
      }
    }
  }
  else
  {
    v2 = 10002;
  }
  std::vector<MemChrBag>::~vector(&Items);
  return v2;
}


#####################################
void __cdecl CMoneyRewardTask::sendTaskInfo(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    if ( CMoneyRewardTask::IsFunctionOpen(this) )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D32u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_FinishTimes);
        Answer::NetPacket::writeInt8(packet, this->m_IsGetReward);
        Answer::NetPacket::writeInt32(packet, 9);
        for ( i = 0; i <= 8; ++i )
        {
          Answer::NetPacket::writeInt32(packet, this->m_MoneyRewardTask[i].TaskId);
          Answer::NetPacket::writeInt8(packet, this->m_MoneyRewardTask[i].TaskState);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v5 = Player::getConnId(this->m_pPlayer);
        v6 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v6, v5, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CMoneyRewardTask::parseMoneyRewardTaskInfo(CMoneyRewardTask *const this, std::string *p_InfoString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  TaskStateInfo stu; // [rsp+10h] [rbp-A0h]
  StringVector TaskInfo; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v14; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v16; // [rsp+90h] [rbp-20h] BYREF
  char v17; // [rsp+9Bh] [rbp-15h] BYREF
  int32_t i; // [rsp+9Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty(p_InfoString) != 1 )
  {
    std::allocator<char>::allocator(&v14);
    std::string::string(&delims, L"|:");
    Answer::StringUtility::split(&items_receive, p_InfoString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v14);
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v17);
      std::string::string(&v16, 9330546);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&TaskInfo, v2, &v16, 0);
      std::string::~string(&v16);
      std::allocator<char>::~allocator(&v17);
      if ( std::vector<std::string>::size(&TaskInfo) == 3 )
      {
        v3 = std::vector<std::string>::operator[](&TaskInfo, 0);
        v4 = (const char *)std::string::c_str(v3);
        i = atoi(v4);
        v5 = std::vector<std::string>::operator[](&TaskInfo, 1u);
        v6 = (const char *)std::string::c_str(v5);
        stu.TaskId = atoi(v6);
        v7 = std::vector<std::string>::operator[](&TaskInfo, 2u);
        v8 = (const char *)std::string::c_str(v7);
        *(_DWORD *)&stu.TaskState = (unsigned __int8)atoi(v8);
        if ( (unsigned int)i <= 8 )
          this->m_MoneyRewardTask[i] = stu;
      }
      std::vector<std::string>::~vector(&TaskInfo);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
  else if ( CMoneyRewardTask::IsFunctionOpen(this) )
  {
    CMoneyRewardTask::InitMoneyRewardTask(this);
  }
}


#####################################
std::string __cdecl CMoneyRewardTask::GetMoneyRewardTaskInfo(CMoneyRewardTask *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 8; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, 9330546);
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 8 * (i + 2LL)));
    std::operator<<<std::char_traits<char>>(v5, 9330546);
    std::ostream::operator<<(v5, (unsigned int)*(char *)(v1 + 8 * (i + 2LL) + 4));
    std::operator<<<std::char_traits<char>>(v5, L"|:");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnSubmitPdbfTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t m_TaskId; // ebx
  ChrTask *Task; // rax
  int64_t v5; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int32_t TaskId; // [rsp+14h] [rbp-2Ch]
  int32_t Times; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  TaskId = Answer::NetPacket::readInt32(inPacket);
  Times = Answer::NetPacket::readInt32(inPacket);
  if ( Times != 1 && Times != 2 )
    return 10002;
  if ( this->m_TaskId != TaskId )
    return 10002;
  m_TaskId = this->m_TaskId;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::submit(Task, m_TaskId, Times) )
    return 10002;
  if ( ++this->m_PdbfFinishTimes <= 0 || this->m_PdbfFinishTimes > 2 )
  {
    this->m_TaskId = 0;
    this->m_Star = 0;
    this->m_RandStarTimes = 0;
  }
  else
  {
    this->m_TaskId = CMoneyRewardTask::RandTaskId(this);
    this->m_Star = CMoneyRewardTask::RandStar(this);
    this->m_RandStarTimes = 1;
  }
  CMoneyRewardTask::SendPdbfTaskInfo(this);
  v5 = this->m_TaskId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, v5);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnReceivePdbfTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  ChrTask *Task; // rax
  int32_t m_TaskId; // ebx
  ChrTask *v5; // rax
  int64_t v6; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::isDoingTaskType(Task, 4) )
    return 10002;
  m_TaskId = this->m_TaskId;
  v5 = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::receive(v5, m_TaskId) )
    return 10002;
  v6 = this->m_TaskId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, v6);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnPdbfRandStar(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  ChrTask *Task; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( this->m_Star == 10 )
    return 10002;
  if ( this->m_TaskId <= 0 )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::isDoingTaskType(Task, 4) )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          10,
          CURRENCY_CHANGE_REASON::GCR_PDBF_TASK_RAND_STAR,
          0) )
    return 10002;
  if ( this->m_RandStarTimes == 15 )
    this->m_Star = 10;
  else
    this->m_Star = CMoneyRewardTask::RandStar(this);
  CMoneyRewardTask::SendPdbfTaskInfo(this);
  return 10002;
}


#####################################
void __cdecl CMoneyRewardTask::InitPdbfTask(CMoneyRewardTask *const this)
{
  ChrTask *Task; // rax

  if ( this->m_pPlayer )
  {
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(Task, 4);
    this->m_TaskId = CMoneyRewardTask::RandTaskId(this);
    this->m_Star = CMoneyRewardTask::RandStar(this);
    this->m_RandStarTimes = 1;
    this->m_PdbfFinishTimes = 0;
    CMoneyRewardTask::SendPdbfTaskInfo(this);
  }
}


#####################################
bool __cdecl CMoneyRewardTask::IsPdbfFunctionOpen(CMoneyRewardTask *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 179) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CMoneyRewardTask::SendPdbfTaskInfo(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( CMoneyRewardTask::IsPdbfFunctionOpen(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D33u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_TaskId);
      Answer::NetPacket::writeInt32(packet, this->m_Star);
      Answer::NetPacket::writeInt32(packet, this->m_PdbfFinishTimes);
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
int32_t __cdecl CMoneyRewardTask::RandTaskId(CMoneyRewardTask *const this)
{
  int32_t v2; // ebx
  CfgData *v3; // rax

  if ( !this->m_pPlayer )
    return 0;
  v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v3 = Answer::Singleton<CfgData>::instance();
  return CfgData::RandPdbfTask(v3, v2);
}


#####################################
int32_t __cdecl CMoneyRewardTask::RandStar(CMoneyRewardTask *const this)
{
  Answer::Random *v1; // rax

  v1 = Answer::Singleton<Answer::Random>::instance();
  return Answer::Random::generate(v1, 1, 10);
}


#####################################
float __cdecl CMoneyRewardTask::GetPdbfRewardRate(CMoneyRewardTask *const this)
{
  return (float)(this->m_Star + 10) / 10.0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnReceiveEquipBackTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  ChrTask *Task; // rax
  int32_t m_EquipBackTaskFinishTimes; // ebx
  int32_t m_EquipBackTaskId; // ebx
  ChrTask *v6; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::isDoingTaskType(Task, 6) )
    return 10002;
  m_EquipBackTaskFinishTimes = this->m_EquipBackTaskFinishTimes;
  if ( m_EquipBackTaskFinishTimes >= CMoneyRewardTask::GetEquipBackTaskLimit(this) )
    return 10002;
  if ( !this->m_EquipBackTaskId )
    CMoneyRewardTask::InitEquipBackTask(this);
  m_EquipBackTaskId = this->m_EquipBackTaskId;
  v6 = Player::GetTask(this->m_pPlayer);
  ChrTask::receive(v6, m_EquipBackTaskId);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnSubmitEquipBackTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  ChrTask *Task; // rax
  CExtCharBag *Bag; // rax
  int32_t m_EquipBackTaskFinishTimes; // ebx
  int32_t m_EquipBackTaskId; // ebx
  CfgData *v7; // rax
  int32_t v8; // ebx
  CfgData *v9; // rax
  CfgData *v10; // rax
  const CfgEquipTable *EquipTable; // rax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v13; // rax
  CExtCharBag *v14; // rax
  int32_t FreeSlotCount; // ebx
  CVip *PlayerVip; // rax
  CExtCharBag *v17; // rax
  CExtCharBag *v18; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  int8_t ConnId; // bl
  DBService *v21; // rax
  DailyActivity *PlayerDailyActivity; // rax
  CNationalDayHd *CNationalDayHd; // rax
  int64_t v24; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v27; // bl
  GameService *v28; // rax
  MemChrBag stu; // [rsp+10h] [rbp-100h] BYREF
  MemChrBag BagItem; // [rsp+30h] [rbp-E0h] BYREF
  LogTask logTask; // [rsp+50h] [rbp-C0h] BYREF
  MemChrBagVector ItemTmp; // [rsp+70h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+90h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+A0h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __lhs; // [rsp+B0h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v37; // [rsp+C0h] [rbp-50h] BYREF
  int32_t Bagslot; // [rsp+C8h] [rbp-48h]
  int32_t times; // [rsp+CCh] [rbp-44h]
  CfgTask *pCfg; // [rsp+D0h] [rbp-40h]
  BackEquipTask *pTask; // [rsp+D8h] [rbp-38h]
  int32_t TaskId; // [rsp+E8h] [rbp-28h]
  float Rate; // [rsp+ECh] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Bagslot = Answer::NetPacket::readInt32(inPacket);
  times = Answer::NetPacket::readInt32(inPacket);
  if ( times <= 0 || times > 2 )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  if ( !ChrTask::isDoingTaskType(Task, 6) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  BagItem = *CExtCharBag::GetSlotData(Bag, Bagslot);
  if ( BagItem.itemClass != 2 )
    return 10002;
  m_EquipBackTaskFinishTimes = this->m_EquipBackTaskFinishTimes;
  if ( m_EquipBackTaskFinishTimes >= CMoneyRewardTask::GetEquipBackTaskLimit(this) )
    return 10002;
  m_EquipBackTaskId = this->m_EquipBackTaskId;
  v7 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::getTask(v7, m_EquipBackTaskId);
  if ( !pCfg )
    return 10002;
  v8 = this->m_EquipBackTaskId;
  v9 = Answer::Singleton<CfgData>::instance();
  pTask = CfgData::GetBackEquipTask(v9, v8);
  if ( !pTask )
    return 10002;
  v10 = Answer::Singleton<CfgData>::instance();
  EquipTable = CfgData::GetEquipTable(v10);
  if ( !CfgEquipTable::GetEquip(EquipTable, BagItem.itemId) )
    return 10002;
  __rhs._M_current = std::vector<int>::end(&pTask->Equips)._M_current;
  M_current = std::vector<int>::end(&pTask->Equips)._M_current;
  v13._M_current = std::vector<int>::begin(&pTask->Equips)._M_current;
  __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<int *,std::vector<int>>,int>(
                       v13,
                       (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current,
                       &BagItem.itemId)._M_current;
  if ( __gnu_cxx::operator==<int *,std::vector<int>>(&__lhs, &__rhs) )
    return 10002;
  v14 = Player::GetBag(this->m_pPlayer);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(v14);
  if ( FreeSlotCount < (int)std::vector<MemChrBag>::size(&pTask->Items) )
    return 10002;
  if ( times != 2 )
    goto LABEL_28;
  Rate = 1.0;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( CVip::GetVipFlg(PlayerVip, 2) )
    Rate = 0.80000001;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          (int)(float)((float)pCfg->DoubleGold * Rate),
          CURRENCY_CHANGE_REASON::GCR_DOUBLE_BACK_EQUIP,
          0) )
    return 10002;
LABEL_28:
  v17 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::CleanSlot(v17, Bagslot, ITEM_CHANGE_REASON::ICR_EQUIP_BACK_TASK);
  it._M_current = std::vector<MemChrBag>::begin(&pTask->Items)._M_current;
  std::vector<MemChrBag>::vector(&ItemTmp);
  while ( 1 )
  {
    v37._M_current = std::vector<MemChrBag>::end(&pTask->Items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &v37) )
      break;
    memset(&stu, 0, sizeof(stu));
    stu = *__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
    stu.itemCount *= times;
    std::vector<MemChrBag>::push_back(&ItemTmp, &stu);
    __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it, 0);
  }
  if ( std::vector<MemChrBag>::size(&ItemTmp)
    && (v18 = Player::GetBag(this->m_pPlayer),
        !CExtCharBag::AddItem(v18, &ItemTmp, ITEM_CHANGE_REASON::ICR_EQUIP_BACK_TASK_GET)) )
  {
    v2 = 10002;
  }
  else
  {
    if ( pTask->GetCurr > 0 )
      Player::AddCurrency(
        this->m_pPlayer,
        CURRENCY_TYPE::CURRENCY_VIGOUR,
        times * pTask->GetCurr,
        CURRENCY_CHANGE_REASON::VCR_EQUIP_BACK_TASK,
        0);
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 14, 0, 0);
    memset(&logTask, 0, sizeof(logTask));
    logTask.cid = Player::getCid(this->m_pPlayer);
    logTask.tid = this->m_EquipBackTaskId;
    logTask.type = 6;
    logTask.time = Unit::getNow(this->m_pPlayer);
    logTask.state = 1;
    ConnId = Player::getConnId(this->m_pPlayer);
    v21 = Answer::Singleton<DBService>::instance();
    DBService::insertTaskInfo(v21, ConnId, &logTask);
    ++this->m_EquipBackTaskFinishTimes;
    TaskId = CMoneyRewardTask::RandTaskIndex(this, 1);
    this->m_EquipBackTaskId = TaskId;
    this->m_RandEquipBackTaskStarTimes = 1;
    CMoneyRewardTask::SendBackEquipTaskInfo(this);
    PlayerDailyActivity = Player::GetPlayerDailyActivity(this->m_pPlayer);
    DailyActivity::AddTaskRecord(PlayerDailyActivity, 6);
    CNationalDayHd = Player::GetCNationalDayHd(this->m_pPlayer);
    CNationalDayHd::AddNationalValue(CNationalDayHd, NATIONAL_HD_TYPE::HHT_LOGIN, 1, 0);
    v24 = this->m_EquipBackTaskId;
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v27 = Player::getConnId(this->m_pPlayer);
    v28 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v28, v27, GateIndex, Proc, v24);
    v2 = 0;
  }
  std::vector<MemChrBag>::~vector(&ItemTmp);
  return v2;
}


#####################################
int32_t __cdecl CMoneyRewardTask::GetEquipBackTaskLimit(CMoneyRewardTask *const this)
{
  return 3;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnEquipBackTaskRandStar(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t m_EquipBackTaskId; // ebx
  CfgData *v4; // rax
  ChrTask *Task; // rax
  int64_t RandGold; // rbx
  CExtCurrency *Currency; // rax
  BackEquipTask *pTask; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  m_EquipBackTaskId = this->m_EquipBackTaskId;
  v4 = Answer::Singleton<CfgData>::instance();
  pTask = CfgData::GetBackEquipTask(v4, m_EquipBackTaskId);
  if ( !pTask )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::isDoingTaskType(Task, 6) )
    return 10002;
  if ( pTask->Star > 9 )
    return 10002;
  if ( pTask->RandGold <= 0 )
    return 10002;
  RandGold = pTask->RandGold;
  Currency = Player::GetCurrency(this->m_pPlayer);
  if ( !CExtCurrency::DecMoneyAndNoBind(Currency, RandGold, CURRENCY_CHANGE_REASON::MCR_EQUIP_BACK_TASK_STAR, 0) )
    return 10002;
  this->m_EquipBackTaskId = CMoneyRewardTask::RandTaskIndex(this, this->m_RandEquipBackTaskStarTimes);
  ++this->m_RandEquipBackTaskStarTimes;
  CMoneyRewardTask::SendBackEquipTaskInfo(this);
  return 0;
}


#####################################
void __cdecl CMoneyRewardTask::InitEquipBackTask(CMoneyRewardTask *const this)
{
  if ( this->m_pPlayer )
  {
    this->m_EquipBackTaskId = CMoneyRewardTask::RandTaskIndex(this, 1);
    this->m_EquipBackTaskFinishTimes = 0;
    this->m_RandEquipBackTaskStarTimes = 1;
    CMoneyRewardTask::SendBackEquipTaskInfo(this);
  }
}


#####################################
int32_t __cdecl CMoneyRewardTask::RandTaskIndex(CMoneyRewardTask *const this, int32_t RandTimes)
{
  ChrTask *Task; // rax
  int32_t v4; // ebx
  CfgData *v5; // rax

  if ( !this->m_pPlayer )
    return 2;
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::CleanTaskType(Task, 6);
  if ( Player::getRecord(this->m_pPlayer, 1910) <= 0 )
  {
    Player::updateRecord(this->m_pPlayer, 1910, 1);
    RandTimes = 15;
  }
  v4 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v5 = Answer::Singleton<CfgData>::instance();
  return CfgData::GetEquipBackTaskId(v5, v4, RandTimes);
}


#####################################
bool __cdecl CMoneyRewardTask::IsBackEquipFunctionOpen(CMoneyRewardTask *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 180) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CMoneyRewardTask::SendBackEquipTaskInfo(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( CMoneyRewardTask::IsBackEquipFunctionOpen(this) )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D34u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_EquipBackTaskId);
      Answer::NetPacket::writeInt32(packet, this->m_EquipBackTaskFinishTimes);
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
int32_t __cdecl CMoneyRewardTask::OnAskTrailerPos(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  Trailer *pTrailer; // [rsp+18h] [rbp-8h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  pTrailer = Player::getTrailer(this->m_pPlayer);
  if ( pTrailer )
    Trailer::SendPos(pTrailer, this->m_pPlayer);
  return 2;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnRandTrailer(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgTrailerTable *TrailerTable; // rax
  CExtCharBag *Bag; // rax
  int32_t m_nId; // r12d
  int8_t m_nClass; // bl
  CfgData *v9; // rax
  int8_t AutoBuy; // [rsp+1Fh] [rbp-21h]
  const CfgTrailerInfo *pTrailerInfo; // [rsp+20h] [rbp-20h]
  CfgGameShop *pCfgGameShop; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  AutoBuy = Answer::NetPacket::readInt8(inPacket);
  if ( this->m_EndTime > 0 )
    return 2;
  if ( this->m_TrailerQuality <= 0 )
    CMoneyRewardTask::ResetTrailer(this);
  v3 = this->m_TrailerQuality + 1;
  v4 = Answer::Singleton<CfgData>::instance();
  TrailerTable = CfgData::GetTrailerTable(v4);
  pTrailerInfo = CfgTrailerTable::GetTrailerInfo(TrailerTable, v3);
  if ( !pTrailerInfo )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::RemoveItem(Bag, &pTrailerInfo->CostItem, ITEM_CHANGE_REASON::ICR_RAND_TRAILER) )
  {
    if ( !AutoBuy )
      return 2;
    if ( AutoBuy != 1 )
      return 2;
    m_nId = pTrailerInfo->CostItem.m_nId;
    m_nClass = pTrailerInfo->CostItem.m_nClass;
    v9 = Answer::Singleton<CfgData>::instance();
    pCfgGameShop = CfgData::GetGameShopItem(v9, m_nClass, m_nId);
    if ( !pCfgGameShop )
      return 2;
    if ( pCfgGameShop->Price <= 0 )
      return 2;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            pCfgGameShop->Price,
            CURRENCY_CHANGE_REASON::GCR_RAND_TRAILE,
            0) )
      return 2;
  }
  CMoneyRewardTask::RandTrailer(this);
  CMoneyRewardTask::SendTrailerInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnStartTrailer(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int32_t m_YaBiaoTimes; // ebx
  CfgData *v4; // rax
  int32_t MapId; // eax
  int32_t m_TrailerQuality; // ebx
  CfgData *v7; // rax
  const CfgTrailerTable *TrailerTable; // rax
  int32_t TrailerId; // ebx
  CfgData *v10; // rax
  const CfgTrailerTable *v11; // rax
  CPoolManager *v12; // rax
  CActivityManager *v13; // rax
  int32_t SubTime; // r14d
  int32_t m_EndTime; // r13d
  int32_t v16; // r12d
  CharId_t Cid; // rax
  int32_t y; // r13d
  int32_t x; // r12d
  Map *Map; // rax
  GameService *v21; // rax
  int8_t ConnId; // bl
  GameService *v23; // rax
  CharId_t v24; // rax
  uint32_t WOffset; // eax
  int8_t v26; // bl
  GameService *v27; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v30; // bl
  GameService *v31; // rax
  std::string p_Name; // [rsp+20h] [rbp-70h] BYREF
  std::string val; // [rsp+30h] [rbp-60h] BYREF
  CfgNpc *cfgNpc; // [rsp+40h] [rbp-50h]
  const CfgTrailerInfo *pTrailerInfo; // [rsp+48h] [rbp-48h]
  const CfgTrailer *pCfgTrailer; // [rsp+50h] [rbp-40h]
  Trailer *pTrailer; // [rsp+58h] [rbp-38h]
  int32_t RewardTimes; // [rsp+60h] [rbp-30h]
  int32_t GongGaoId; // [rsp+64h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+68h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  m_YaBiaoTimes = this->m_YaBiaoTimes;
  if ( m_YaBiaoTimes >= CMoneyRewardTask::GetYaBiaoLimit(this) )
    return 2;
  v4 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v4, 1060);
  if ( !cfgNpc )
    return 2;
  MapId = StaticObj::getMapId(this->m_pPlayer);
  if ( !CfgNpc::findMapId(cfgNpc, MapId) )
    return 2;
  if ( this->m_EndTime > 0 )
    return 2;
  if ( this->m_TrailerQuality <= 0 )
    CMoneyRewardTask::ResetTrailer(this);
  m_TrailerQuality = this->m_TrailerQuality;
  v7 = Answer::Singleton<CfgData>::instance();
  TrailerTable = CfgData::GetTrailerTable(v7);
  pTrailerInfo = CfgTrailerTable::GetTrailerInfo(TrailerTable, m_TrailerQuality);
  if ( !pTrailerInfo )
    return 2;
  TrailerId = pTrailerInfo->TrailerId;
  v10 = Answer::Singleton<CfgData>::instance();
  v11 = CfgData::GetTrailerTable(v10);
  pCfgTrailer = CfgTrailerTable::GetTrailer(v11, TrailerId);
  if ( !pCfgTrailer )
    return 2;
  v12 = Answer::Singleton<CPoolManager>::instance();
  pTrailer = CPoolManager::pop<Trailer>(v12);
  if ( !pTrailer )
    return 2;
  ++this->m_YaBiaoTimes;
  this->m_EndTime = Unit::getNow(this->m_pPlayer) + 1800;
  RewardTimes = 1;
  v13 = Answer::Singleton<CActivityManager>::instance();
  if ( CActivityManager::IsActivityRunningByType(v13, 20) )
    RewardTimes = 2;
  SubTime = Unit::getNow(this->m_pPlayer) + 180;
  m_EndTime = this->m_EndTime;
  v16 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  Player::getName((const Player *const)&p_Name);
  Cid = Player::getCid(this->m_pPlayer);
  Trailer::init(pTrailer, pCfgTrailer, Cid, &p_Name, v16, m_EndTime, RewardTimes, SubTime);
  std::string::~string(&p_Name);
  y = cfgNpc->y;
  x = cfgNpc->x;
  Map = StaticObj::getMap(this->m_pPlayer);
  Trailer::EnterMap(pTrailer, Map, x, y);
  v21 = Answer::Singleton<GameService>::instance();
  GameService::addTrailer(v21, pTrailer);
  Trailer::SendInfo(pTrailer, this->m_pPlayer);
  Player::setTrailer(this->m_pPlayer, pTrailer);
  CMoneyRewardTask::SendTrailerInfo(this);
  GongGaoId = 0;
  if ( this->m_TrailerQuality == 3 )
  {
    GongGaoId = 427;
  }
  else if ( this->m_TrailerQuality == 4 )
  {
    GongGaoId = 428;
  }
  if ( GongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v23 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v23, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      v24 = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, v24);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v26 = Player::getConnId(this->m_pPlayer);
      v27 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v27, v26, packet);
    }
  }
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v30 = Player::getConnId(this->m_pPlayer);
  v31 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v31, v30, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnSubTrailer(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  CfgData *v2; // rax
  int32_t MapId; // eax
  int32_t PosY; // r13d
  int32_t PosX; // r12d
  int32_t v7; // eax
  int32_t v8; // r13d
  int32_t v9; // r12d
  int32_t v10; // eax
  int32_t SubTime; // ebx
  int32_t m_TrailerQuality; // ebx
  CfgData *v13; // rax
  const CfgTrailerTable *TrailerTable; // rax
  int32_t RewardTimes; // eax
  int32_t RobberyWeiWang; // ebx
  int32_t v17; // eax
  int32_t RobberyFuWen; // ebx
  int v19; // ebx
  CFaBao *PlayerFaBao; // rax
  int32_t v21; // eax
  int32_t FullWeiWang; // ebx
  int32_t v23; // eax
  CHuoYueDu *PlayerHuoYueDu; // rax
  DBService *v25; // rax
  DailyActivity *PlayerDailyActivity; // rax
  CNationalDayHd *CNationalDayHd; // rax
  GameService *v28; // rax
  CPoolManager *v29; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  GameService *v32; // rax
  float RobberyMoney; // [rsp+0h] [rbp-70h]
  float v34; // [rsp+4h] [rbp-6Ch]
  float FullMoney; // [rsp+8h] [rbp-68h]
  float v36; // [rsp+Ch] [rbp-64h]
  LogTask logTask; // [rsp+20h] [rbp-50h] BYREF
  CfgNpc *cfgNpc; // [rsp+38h] [rbp-38h]
  Trailer *pTrailer; // [rsp+40h] [rbp-30h]
  const CfgTrailerInfo *pTrailerInfo; // [rsp+48h] [rbp-28h]

  v2 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v2, 1061);
  if ( !cfgNpc )
    return 2;
  MapId = StaticObj::getMapId(this->m_pPlayer);
  if ( !CfgNpc::findMapId(cfgNpc, MapId) )
    return 2;
  PosY = StaticObj::GetPosY(this->m_pPlayer);
  PosX = StaticObj::GetPosX(this->m_pPlayer);
  v7 = StaticObj::getMapId(this->m_pPlayer);
  if ( !CfgNpc::NearNpc(cfgNpc, v7, PosX, PosY, 10) )
    return 2;
  if ( this->m_EndTime <= 0 )
    return 2;
  if ( this->m_TrailerQuality <= 0 )
    CMoneyRewardTask::ResetTrailer(this);
  pTrailer = Player::getTrailer(this->m_pPlayer);
  if ( !pTrailer )
    return 2;
  v8 = StaticObj::GetPosY(pTrailer);
  v9 = StaticObj::GetPosX(pTrailer);
  v10 = StaticObj::getMapId(pTrailer);
  if ( !CfgNpc::NearNpc(cfgNpc, v10, v9, v8, 10) )
    return 2;
  SubTime = Trailer::GetSubTime(pTrailer);
  if ( SubTime > Unit::getNow(this->m_pPlayer) )
    return 2;
  Trailer::LeaveMap(pTrailer);
  m_TrailerQuality = this->m_TrailerQuality;
  v13 = Answer::Singleton<CfgData>::instance();
  TrailerTable = CfgData::GetTrailerTable(v13);
  pTrailerInfo = CfgTrailerTable::GetTrailerInfo(TrailerTable, m_TrailerQuality);
  if ( !pTrailerInfo )
    return 2;
  if ( Trailer::Robbery(pTrailer) )
  {
    RobberyMoney = (float)pTrailerInfo->RobberyMoney;
    v34 = RobberyMoney * Trailer::GetRate(pTrailer);
    RewardTimes = Trailer::GetRewardTimes(pTrailer);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_BIND_MONEY,
      (int)(float)((float)RewardTimes * v34),
      CURRENCY_CHANGE_REASON::MCR_YAO_BIAO,
      0);
    RobberyWeiWang = pTrailerInfo->RobberyWeiWang;
    v17 = Trailer::GetRewardTimes(pTrailer);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_HONOR,
      RobberyWeiWang * v17,
      CURRENCY_CHANGE_REASON::MCR_YAO_BIAO,
      0);
    RobberyFuWen = pTrailerInfo->RobberyFuWen;
  }
  else
  {
    FullMoney = (float)pTrailerInfo->FullMoney;
    v36 = FullMoney * Trailer::GetRate(pTrailer);
    v21 = Trailer::GetRewardTimes(pTrailer);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_BIND_MONEY,
      (int)(float)((float)v21 * v36),
      CURRENCY_CHANGE_REASON::MCR_YAO_BIAO,
      0);
    FullWeiWang = pTrailerInfo->FullWeiWang;
    v23 = Trailer::GetRewardTimes(pTrailer);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_HONOR,
      FullWeiWang * v23,
      CURRENCY_CHANGE_REASON::MCR_YAO_BIAO,
      0);
    RobberyFuWen = pTrailerInfo->FullFuWen;
  }
  v19 = Trailer::GetRewardTimes(pTrailer) * RobberyFuWen;
  PlayerFaBao = Player::GetPlayerFaBao(this->m_pPlayer);
  CFaBao::AddFaBaoRes(PlayerFaBao, 2, v19);
  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
  CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 12, 0, 0);
  memset(&logTask, 0, sizeof(logTask));
  logTask.cid = Player::getCid(this->m_pPlayer);
  logTask.tid = Trailer::GetTaskId(pTrailer);
  logTask.type = 5;
  logTask.time = Unit::getNow(this->m_pPlayer);
  logTask.state = 1;
  LOBYTE(v19) = Player::getConnId(this->m_pPlayer);
  v25 = Answer::Singleton<DBService>::instance();
  DBService::updateTaskInfo(v25, v19, &logTask);
  PlayerDailyActivity = Player::GetPlayerDailyActivity(this->m_pPlayer);
  DailyActivity::AddTaskRecord(PlayerDailyActivity, 5);
  CNationalDayHd = Player::GetCNationalDayHd(this->m_pPlayer);
  CNationalDayHd::AddNationalValue(CNationalDayHd, NATIONAL_HD_TYPE::HHT_COST_GOLD, 1, 0);
  v28 = Answer::Singleton<GameService>::instance();
  GameService::removeTrailer(v28, pTrailer);
  v29 = Answer::Singleton<CPoolManager>::instance();
  CPoolManager::push<Trailer>(v29, pTrailer);
  Player::setTrailer(this->m_pPlayer, 0);
  CMoneyRewardTask::ResetTrailer(this);
  this->m_EndTime = 0;
  CMoneyRewardTask::SendTRailerEnd(this);
  CMoneyRewardTask::SendTrailerInfo(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  LOBYTE(v19) = Player::getConnId(this->m_pPlayer);
  v32 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v32, v19, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CMoneyRewardTask::SendTRailerEnd(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EEFu);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, 0);
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
int32_t __cdecl CMoneyRewardTask::OnRequestSupport(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  int32_t MapId; // eax
  int16_t PosX; // ax
  int16_t PosY; // ax
  uint32_t WOffset; // eax
  int8_t v10; // bl
  GameService *v11; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  if ( Player::getFamilyId(this->m_pPlayer) <= 0 )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_PROC, 0x4E51u);
  if ( !packet )
    return 10002;
  Cid = Player::getCid(this->m_pPlayer);
  Answer::NetPacket::writeInt64(packet, Cid);
  Player::getName((const Player *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  MapId = StaticObj::getMapId(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, MapId);
  PosX = StaticObj::GetPosX(this->m_pPlayer);
  Answer::NetPacket::writeInt16(packet, PosX);
  PosY = StaticObj::GetPosY(this->m_pPlayer);
  Answer::NetPacket::writeInt16(packet, PosY);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v10 = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v11, v10, packet);
  return 0;
}


#####################################
void __cdecl CMoneyRewardTask::AddJieBiaoTimes(CMoneyRewardTask *const this)
{
  ++this->m_JieBiaoTimes;
  CMoneyRewardTask::SendTrailerInfo(this);
}


#####################################
void __cdecl CMoneyRewardTask::SendTrailerInfo(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D38u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_JieBiaoTimes);
    Answer::NetPacket::writeInt32(packet, this->m_YaBiaoTimes);
    Answer::NetPacket::writeInt8(packet, this->m_TrailerQuality);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v5 = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v6, v5, GateIndex, packet);
  }
}


#####################################
void __cdecl CMoneyRewardTask::RandTrailer(CMoneyRewardTask *const this)
{
  int8_t m_TrailerQuality; // bl
  CfgData *v2; // rax
  const CfgTrailerTable *TrailerTable; // rax

  if ( this->m_TrailerQuality <= 0 )
    CMoneyRewardTask::ResetTrailer(this);
  m_TrailerQuality = this->m_TrailerQuality;
  v2 = Answer::Singleton<CfgData>::instance();
  TrailerTable = CfgData::GetTrailerTable(v2);
  this->m_TrailerQuality = CfgTrailerTable::RandQuality(TrailerTable, m_TrailerQuality);
}


#####################################
int32_t __cdecl CMoneyRewardTask::GetYaBiaoLimit(CMoneyRewardTask *const this)
{
  CVip *PlayerVip; // rax
  int32_t YaBiaoLimit; // [rsp+1Ch] [rbp-4h]

  YaBiaoLimit = 3;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( CVip::GetVipFlg(PlayerVip, 3) )
    return 4;
  return YaBiaoLimit;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnRefreshTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  ChrTask *Task; // rax
  char IsBest; // [rsp+1Bh] [rbp-5h]
  int32_t NeedCost; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( this->m_XiangYaoFinishTimes > 9 )
    return 10002;
  if ( !CMoneyRewardTask::IsXiangYaoFunctionOpen(this) )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::isDoingTaskType(Task, 7) )
    return 10002;
  IsBest = Answer::NetPacket::readInt8(inPacket);
  NeedCost = 0;
  if ( IsBest <= 0 )
  {
    if ( this->m_RefreshTimes > 2 )
      NeedCost = 50;
  }
  else
  {
    NeedCost = 200;
  }
  if ( NeedCost > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          NeedCost,
          CURRENCY_CHANGE_REASON::GCR_REFRESH_XIANG_YAO,
          0) )
  {
    return 10002;
  }
  CMoneyRewardTask::RandXiangYaoTask(this, IsBest > 0, 1);
  ++this->m_RefreshTimes;
  CMoneyRewardTask::SendXiangYaoTaskInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnOperatorTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  ChrTask *v3; // rax
  int32_t v4; // ebx
  CfgData *v5; // rax
  int32_t v6; // ebx
  ChrTask *v7; // rax
  int32_t TaskId; // ebx
  ChrTask *Task; // rax
  int32_t v10; // ebx
  ChrTask *v11; // rax
  ChrTask *v12; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  int32_t v14; // ebx
  ChrTask *v15; // rax
  ChrTask *v16; // rax
  int32_t v17; // ebx
  ChrTask *v18; // rax
  ChrTask *v19; // rax
  char nId; // [rsp+1Eh] [rbp-12h]
  int8_t nIda; // [rsp+1Eh] [rbp-12h]
  int8_t Oper; // [rsp+1Fh] [rbp-11h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nId = Answer::NetPacket::readInt8(inPacket);
  Oper = Answer::NetPacket::readInt8(inPacket);
  if ( nId <= 0 || nId > 4 )
    return 10002;
  nIda = nId - 1;
  if ( Oper == 2 )
  {
    TaskId = this->m_XiangYaoTask[nIda].TaskId;
    Task = Player::GetTask(this->m_pPlayer);
    if ( !ChrTask::isDoingTask(Task, TaskId) )
      return 10002;
    if ( this->m_XiangYaoTask[nIda].TaskState != 2 )
      return 10002;
    v10 = this->m_XiangYaoTask[nIda].TaskId;
    v11 = Player::GetTask(this->m_pPlayer);
    if ( ChrTask::submit(v11, v10, 1) )
      return 10002;
    v12 = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(v12, 7);
    this->m_XiangYaoTask[nIda].TaskState = 3;
    if ( CMoneyRewardTask::NeedRefreshTask(this) )
      CMoneyRewardTask::RandXiangYaoTask(this, 0, 1);
LABEL_31:
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 15, 0, 0);
    goto LABEL_46;
  }
  if ( Oper > 2 )
  {
    if ( Oper == 3 )
    {
      if ( this->m_XiangYaoTask[nIda].TaskState != 2 )
        return 10002;
      v14 = this->m_XiangYaoTask[nIda].TaskId;
      v15 = Player::GetTask(this->m_pPlayer);
      if ( !ChrTask::isDoingTask(v15, v14) )
        return 10002;
      v16 = Player::GetTask(this->m_pPlayer);
      ChrTask::CleanTaskType(v16, 7);
      this->m_XiangYaoTask[nIda].TaskState = 4;
      if ( CMoneyRewardTask::NeedRefreshTask(this) )
        CMoneyRewardTask::RandXiangYaoTask(this, 0, 1);
      goto LABEL_46;
    }
    if ( Oper != 4 )
      return 10002;
    if ( this->m_XiangYaoTask[nIda].TaskState != 2 )
      return 10002;
    v17 = this->m_XiangYaoTask[nIda].TaskId;
    v18 = Player::GetTask(this->m_pPlayer);
    if ( ChrTask::quickDone(v18, v17) )
      return 10002;
    v19 = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(v19, 7);
    this->m_XiangYaoTask[nIda].TaskState = 3;
    if ( CMoneyRewardTask::NeedRefreshTask(this) )
      CMoneyRewardTask::RandXiangYaoTask(this, 0, 1);
    goto LABEL_31;
  }
  if ( Oper != 1 )
    return 10002;
  if ( this->m_XiangYaoFinishTimes > 9 )
    return 10002;
  v3 = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::isDoingTaskType(v3, 7) )
    return 10002;
  if ( this->m_XiangYaoTask[nIda].TaskState != 1 )
    return 10002;
  v4 = this->m_XiangYaoTask[nIda].TaskId;
  v5 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::GetTaskType(v5, v4) != 7 )
    return 10002;
  v6 = this->m_XiangYaoTask[nIda].TaskId;
  v7 = Player::GetTask(this->m_pPlayer);
  ChrTask::receive(v7, v6);
  this->m_XiangYaoTask[nIda].TaskState = 2;
  ++this->m_XiangYaoFinishTimes;
LABEL_46:
  CMoneyRewardTask::SendXiangYaoTaskInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnAskXiangYaoTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  CMoneyRewardTask::SendXiangYaoTaskInfo(this);
  return 0;
}


#####################################
bool __cdecl CMoneyRewardTask::NeedRefreshTask(CMoneyRewardTask *const this)
{
  int32_t j; // [rsp+14h] [rbp-4h]

  for ( j = 0; j <= 3; ++j )
  {
    if ( this->m_XiangYaoTask[j].TaskState == 1 || this->m_XiangYaoTask[j].TaskState == 2 )
      return 0;
  }
  return 1;
}


#####################################
bool __cdecl CMoneyRewardTask::IsXiangYaoFunctionOpen(CMoneyRewardTask *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 193) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CMoneyRewardTask::OnXiangYaoFunctionOpen(CMoneyRewardTask *const this)
{
  CMoneyRewardTask::RandXiangYaoTask(this, 0, 0);
  CMoneyRewardTask::SendXiangYaoTaskInfo(this);
}


#####################################
void __cdecl CMoneyRewardTask::SendXiangYaoTaskInfo(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int8_t i; // [rsp+1Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    if ( CMoneyRewardTask::IsShenWeiFunctionOPen(this) )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D3Au);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_RefreshTimes);
        Answer::NetPacket::writeInt32(packet, this->m_XiangYaoFinishTimes);
        Answer::NetPacket::writeInt8(packet, 4);
        for ( i = 0; i <= 3; ++i )
        {
          Answer::NetPacket::writeInt8(packet, i + 1);
          Answer::NetPacket::writeInt32(packet, this->m_XiangYaoTask[i].TaskId);
          Answer::NetPacket::writeInt8(packet, this->m_XiangYaoTask[i].TaskState);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v5 = Player::getConnId(this->m_pPlayer);
        v6 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v6, v5, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CMoneyRewardTask::InitXiangYaoTask(CMoneyRewardTask *const this)
{
  ChrTask *Task; // rax

  if ( this->m_pPlayer )
  {
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(Task, 7);
    this->m_XiangYaoFinishTimes = 0;
    this->m_RefreshTimes = 0;
    CMoneyRewardTask::RandXiangYaoTask(this, 0, 0);
    CMoneyRewardTask::SendXiangYaoTaskInfo(this);
  }
}


#####################################
void __cdecl CMoneyRewardTask::RandXiangYaoTask(CMoneyRewardTask *const this, bool Best, bool NeedGongGao)
{
  int32_t v3; // r13d
  int32_t v4; // ebx
  CfgData *v5; // rax
  int32_t TaskId; // ebx
  CfgData *v7; // rax
  GameService *v8; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v11; // rax
  GameService *v12; // rax
  CharId_t v13; // rax
  uint32_t v14; // eax
  GameService *v15; // rax
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  std::string v18; // [rsp+20h] [rbp-40h] BYREF
  int32_t i; // [rsp+28h] [rbp-38h]
  int32_t nStart; // [rsp+2Ch] [rbp-34h]
  Answer::NetPacket *packet; // [rsp+30h] [rbp-30h]
  Answer::NetPacket *packet_0; // [rsp+38h] [rbp-28h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 3; ++i )
    {
      v3 = i;
      v4 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      v5 = Answer::Singleton<CfgData>::instance();
      this->m_XiangYaoTask[v3].TaskId = CfgData::RandXiangYaoTaskId(v5, v4, Best);
      this->m_XiangYaoTask[i].TaskState = 1;
      if ( !Best && NeedGongGao )
      {
        TaskId = this->m_XiangYaoTask[i].TaskId;
        v7 = Answer::Singleton<CfgData>::instance();
        nStart = CfgData::getXiangYaoStart(v7, TaskId);
        if ( nStart == 4 )
        {
          v8 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v8, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( packet )
          {
            Answer::NetPacket::writeInt32(packet, 458);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v11 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v11, 0, packet);
          }
        }
      }
    }
    if ( Best )
    {
      v12 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v12, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet_0 )
      {
        Answer::NetPacket::writeInt32(packet_0, 459);
        v13 = Player::getCid(this->m_pPlayer);
        Answer::NetPacket::writeInt64(packet_0, v13);
        Player::getName((const Player *const)&v18);
        Answer::NetPacket::writeUTF8(packet_0, &v18);
        std::string::~string(&v18);
        v14 = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, v14);
        v15 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v15, 0, packet_0);
      }
    }
  }
}


#####################################
void __cdecl CMoneyRewardTask::LoginInitXiangYaoTask(CMoneyRewardTask *const this)
{
  bool NeedInit; // [rsp+1Eh] [rbp-2h]
  int8_t i; // [rsp+1Fh] [rbp-1h]

  if ( CMoneyRewardTask::IsXiangYaoFunctionOpen(this) )
  {
    NeedInit = 0;
    for ( i = 0; i <= 3; ++i )
    {
      if ( this->m_XiangYaoTask[i].TaskId <= 0 || this->m_XiangYaoTask[i].TaskState <= 0 )
      {
        NeedInit = 1;
        break;
      }
    }
    if ( NeedInit )
      CMoneyRewardTask::InitXiangYaoTask(this);
  }
}


#####################################
void __cdecl CMoneyRewardTask::parseXiangYaoTask(CMoneyRewardTask *const this, std::string *p_TaskInfoString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  TaskStateInfo stu; // [rsp+10h] [rbp-A0h]
  StringVector TaskInfo; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v14; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v16; // [rsp+90h] [rbp-20h] BYREF
  char v17; // [rsp+9Bh] [rbp-15h] BYREF
  int32_t i; // [rsp+9Ch] [rbp-14h]

  if ( (unsigned __int8)std::string::empty(p_TaskInfoString) != 1 )
  {
    std::allocator<char>::allocator(&v14);
    std::string::string(&delims, L"|:");
    Answer::StringUtility::split(&items_receive, p_TaskInfoString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v14);
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v17);
      std::string::string(&v16, 9330546);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&TaskInfo, v2, &v16, 0);
      std::string::~string(&v16);
      std::allocator<char>::~allocator(&v17);
      if ( std::vector<std::string>::size(&TaskInfo) == 3 )
      {
        v3 = std::vector<std::string>::operator[](&TaskInfo, 0);
        v4 = (const char *)std::string::c_str(v3);
        i = atoi(v4);
        v5 = std::vector<std::string>::operator[](&TaskInfo, 1u);
        v6 = (const char *)std::string::c_str(v5);
        stu.TaskId = atoi(v6);
        v7 = std::vector<std::string>::operator[](&TaskInfo, 2u);
        v8 = (const char *)std::string::c_str(v7);
        *(_DWORD *)&stu.TaskState = (unsigned __int8)atoi(v8);
        if ( (unsigned int)i < 4 )
          this->m_XiangYaoTask[i] = stu;
      }
      std::vector<std::string>::~vector(&TaskInfo);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
}


#####################################
std::string __cdecl CMoneyRewardTask::saveXiangYaoTaskString(CMoneyRewardTask *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 3; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, 9330546);
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 8 * (i + 16LL) + 12));
    std::operator<<<std::char_traits<char>>(v5, 9330546);
    std::ostream::operator<<(v5, (unsigned int)*(char *)(v1 + 8 * (i + 16LL) + 16));
    std::operator<<<std::char_traits<char>>(v5, L"|:");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


#####################################
int32_t __cdecl CMoneyRewardTask::OnOperatorShenWeiTask(CMoneyRewardTask *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  ChrTask *Task; // rax
  ChrTask *v5; // rax
  ChrTask *v6; // rax
  ChrTask *v7; // rax
  ChrTask *v8; // rax
  CHuoYueDu *PlayerHuoYueDu; // rax
  ChrTask *v10; // rax
  ChrTask *v11; // rax
  CHuoYueDu *v12; // rax
  ChrTask *v13; // rax
  ChrTask *v14; // rax
  int8_t nIndex; // [rsp+16h] [rbp-2Ah]
  int8_t nIndexa; // [rsp+16h] [rbp-2Ah]
  int8_t nOper; // [rsp+17h] [rbp-29h]
  ShenWeiTaskCfg *pCfg; // [rsp+18h] [rbp-28h]
  int32_t TaskId; // [rsp+24h] [rbp-1Ch]
  int32_t ConstGold; // [rsp+28h] [rbp-18h]
  int32_t Times; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  nOper = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetShenWeiTaskCfg(v3, nIndex);
  if ( !pCfg )
    return 10002;
  nIndexa = nIndex - 1;
  if ( (unsigned __int8)nIndexa > 4u )
    return 10002;
  TaskId = pCfg->nTaskId;
  switch ( nOper )
  {
    case 1:
      Task = Player::GetTask(this->m_pPlayer);
      if ( ChrTask::isDoingTaskType(Task, 8) )
        return 10002;
      if ( this->m_ShenWeiTaskState[nIndexa] != 2 )
        return 10002;
      v5 = Player::GetTask(this->m_pPlayer);
      if ( ChrTask::receive(v5, TaskId) )
        return 10002;
      this->m_ShenWeiTaskState[nIndexa] = 3;
      break;
    case 2:
    case 3:
      if ( this->m_ShenWeiTaskState[nIndexa] != 3 )
        return 10002;
      v6 = Player::GetTask(this->m_pPlayer);
      if ( !ChrTask::isDoingTask(v6, TaskId) )
        return 10002;
      ConstGold = 0;
      Times = 1;
      if ( nOper == 3 )
      {
        if ( pCfg->nDoubleCost <= 0 )
          return 10002;
        Times = 2;
        ConstGold = pCfg->nDoubleCost;
        if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < ConstGold )
          return 10002;
      }
      v7 = Player::GetTask(this->m_pPlayer);
      if ( ChrTask::submit(v7, TaskId, Times) )
        return 10002;
      if ( ConstGold > 0 )
        Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          ConstGold,
          CURRENCY_CHANGE_REASON::GCR_SHEN_WEI_TASK_DOUBLE_GET,
          0);
      v8 = Player::GetTask(this->m_pPlayer);
      ChrTask::CleanTaskType(v8, 8);
      PlayerHuoYueDu = Player::GetPlayerHuoYueDu(this->m_pPlayer);
      CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 16, 0, 0);
      this->m_ShenWeiTaskState[nIndexa] = 5;
      break;
    case 4:
      if ( this->m_ShenWeiTaskState[nIndexa] != 3 )
        return 10002;
      v10 = Player::GetTask(this->m_pPlayer);
      if ( ChrTask::quickDone(v10, TaskId) )
        return 10002;
      v11 = Player::GetTask(this->m_pPlayer);
      ChrTask::CleanTaskType(v11, 8);
      this->m_ShenWeiTaskState[nIndexa] = 5;
      v12 = Player::GetPlayerHuoYueDu(this->m_pPlayer);
      CHuoYueDu::AddHuoYueDuRecord(v12, 16, 0, 0);
      break;
    case 5:
      if ( this->m_ShenWeiTaskState[nIndexa] != 3 )
        return 10002;
      v13 = Player::GetTask(this->m_pPlayer);
      if ( !ChrTask::isDoingTask(v13, TaskId) )
        return 10002;
      v14 = Player::GetTask(this->m_pPlayer);
      ChrTask::CleanTaskType(v14, 8);
      this->m_ShenWeiTaskState[nIndexa] = 2;
      break;
    default:
      return 10002;
  }
  CMoneyRewardTask::SendShenWeiTaskInfo(this);
  return 0;
}


#####################################
void __cdecl CMoneyRewardTask::InitXuWuTask(CMoneyRewardTask *const this)
{
  ChrTask *Task; // rax
  int32_t v2; // ebx
  CfgData *v3; // rax
  ChrTask *v4; // rax
  int TaskId; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(Task, 9);
    v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v3 = Answer::Singleton<CfgData>::instance();
    TaskId = CfgData::InitXuWuTask(v3, v2, 1);
    if ( TaskId > 0 )
    {
      v4 = Player::GetTask(this->m_pPlayer);
      ChrTask::receive(v4, TaskId);
    }
  }
}


#####################################
void __cdecl CMoneyRewardTask::InitXinMoTask(CMoneyRewardTask *const this)
{
  ChrTask *Task; // rax
  int32_t v2; // ebx
  CfgData *v3; // rax
  ChrTask *v4; // rax
  int TaskId; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(Task, 42);
    v2 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v3 = Answer::Singleton<CfgData>::instance();
    TaskId = CfgData::InitXinMoTask(v3, v2, 1);
    if ( TaskId > 0 )
    {
      v4 = Player::GetTask(this->m_pPlayer);
      ChrTask::receive(v4, TaskId);
    }
  }
}


#####################################
void __cdecl CMoneyRewardTask::InitShenWeiTask(CMoneyRewardTask *const this)
{
  ChrTask *Task; // rax
  int32_t k; // [rsp+1Ch] [rbp-4h]

  for ( k = 0; k <= 4; ++k )
    this->m_ShenWeiTaskState[k] = 2;
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::CleanTaskType(Task, 8);
  CMoneyRewardTask::SendShenWeiTaskInfo(this);
}


#####################################
bool __cdecl CMoneyRewardTask::IsShenWeiFunctionOPen(CMoneyRewardTask *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 194) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CMoneyRewardTask::SendShenWeiTaskInfo(CMoneyRewardTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int8_t i; // [rsp+1Fh] [rbp-11h]

  if ( this->m_pPlayer )
  {
    if ( CMoneyRewardTask::IsShenWeiFunctionOPen(this) )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v2 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D3Bu);
      if ( packet )
      {
        Answer::NetPacket::writeInt8(packet, 5);
        for ( i = 0; i <= 4; ++i )
        {
          Answer::NetPacket::writeInt8(packet, i + 1);
          Answer::NetPacket::writeInt8(packet, this->m_ShenWeiTaskState[i]);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v5 = Player::getConnId(this->m_pPlayer);
        v6 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v6, v5, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CMoneyRewardTask::LoginInitShenWeiTask(CMoneyRewardTask *const this)
{
  bool NeedInit; // [rsp+1Eh] [rbp-2h]
  int8_t i; // [rsp+1Fh] [rbp-1h]

  if ( CMoneyRewardTask::IsShenWeiFunctionOPen(this) )
  {
    NeedInit = 0;
    for ( i = 0; i <= 4; ++i )
    {
      if ( !this->m_ShenWeiTaskState[i] )
      {
        NeedInit = 1;
        break;
      }
    }
    if ( NeedInit )
      CMoneyRewardTask::InitShenWeiTask(this);
  }
}


#####################################
void __cdecl CMoneyRewardTask::parseShenWeiTask(CMoneyRewardTask *const this, std::string *p_TaskInfoString)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  StringVector TaskInfo; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+30h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+40h] [rbp-60h] BYREF
  std::string delims; // [rsp+60h] [rbp-40h] BYREF
  char v11; // [rsp+6Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  std::string v13; // [rsp+80h] [rbp-20h] BYREF
  char v14; // [rsp+8Dh] [rbp-13h] BYREF
  int8_t i; // [rsp+8Eh] [rbp-12h]
  int8_t TaskState; // [rsp+8Fh] [rbp-11h]

  if ( (unsigned __int8)std::string::empty(p_TaskInfoString) != 1 )
  {
    std::allocator<char>::allocator(&v11);
    std::string::string(&delims, L"|:");
    Answer::StringUtility::split(&items_receive, p_TaskInfoString, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v11);
    for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v14);
      std::string::string(&v13, 9330546);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&TaskInfo, v2, &v13, 0);
      std::string::~string(&v13);
      std::allocator<char>::~allocator(&v14);
      if ( std::vector<std::string>::size(&TaskInfo) == 2 )
      {
        v3 = std::vector<std::string>::operator[](&TaskInfo, 0);
        v4 = (const char *)std::string::c_str(v3);
        i = atoi(v4);
        v5 = std::vector<std::string>::operator[](&TaskInfo, 1u);
        v6 = (const char *)std::string::c_str(v5);
        TaskState = atoi(v6);
        if ( (unsigned __int8)i <= 4u )
          this->m_ShenWeiTaskState[i] = TaskState;
      }
      std::vector<std::string>::~vector(&TaskInfo);
    }
    std::vector<std::string>::~vector(&items_receive);
  }
}


#####################################
std::string __cdecl CMoneyRewardTask::saveShenWeiTaskString(CMoneyRewardTask *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i; // [rsp+18Ch] [rbp-14h]

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
  for ( i = 0; i <= 4; ++i )
  {
    std::ostream::operator<<(v5, (unsigned int)i);
    std::operator<<<std::char_traits<char>>(v5, 9330546);
    std::ostream::operator<<(v5, (unsigned int)*(char *)(v1 + i + 180));
    std::operator<<<std::char_traits<char>>(v5, L"|:");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  return (std::string)this;
}


