// Decompiled methods for class: CExtChrTaskCycle
// Source: gameserver.cc
// Total methods: 18

#####################################
void __cdecl CExtChrTaskCycle::~CExtChrTaskCycle(CExtChrTaskCycle *const this)
{
  CExtChrTaskCycle::~CExtChrTaskCycle(this);
  operator delete(this);
}


#####################################
void __cdecl CExtChrTaskCycle::OnCleanUp(CExtChrTaskCycle *const this)
{
  this->m_nFinishTimes = 0;
  this->m_nTaskId = 0;
  this->m_nState = 0;
}


#####################################
void __cdecl CExtChrTaskCycle::OnLoadFromDB(CExtChrTaskCycle *const this, const PlayerDBData *const dbData)
{
  if ( CExtChrTaskCycle::IsFunctionOpen(this) && this->m_pPlayer )
  {
    this->m_nFinishTimes = dbData->taskCycleData.nFinishTimes;
    this->m_nTaskId = dbData->taskCycleData.nTaskId;
    this->m_nState = dbData->taskCycleData.nState;
  }
}


#####################################
void __cdecl CExtChrTaskCycle::OnSaveToDB(CExtChrTaskCycle *const this, PlayerDBData *const dbData)
{
  if ( CExtChrTaskCycle::IsFunctionOpen(this) )
  {
    dbData->taskCycleData.nFinishTimes = this->m_nFinishTimes;
    dbData->taskCycleData.nTaskId = this->m_nTaskId;
    dbData->taskCycleData.nState = this->m_nState;
  }
}


#####################################
void __cdecl CExtChrTaskCycle::OnDaySwitch(CExtChrTaskCycle *const this, int32_t nDiffDays)
{
  if ( this->m_pPlayer && CExtChrTaskCycle::IsFunctionOpen(this) )
  {
    CExtChrTaskCycle::refreshTask(this);
    this->m_nFinishTimes = 0;
    CExtChrTaskCycle::sendTaskInfo(this);
  }
}


#####################################
void __cdecl CExtChrTaskCycle::GetInterestsProtocol(CExtChrTaskCycle *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 771;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 772;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CExtChrTaskCycle::DispatchNetDatas(
        CExtChrTaskCycle *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x303u:
      return CExtChrTaskCycle::onSubmitTask(this, inPacket);
    case 0x304u:
      return CExtChrTaskCycle::onQuickDone(this, inPacket);
    case 0x302u:
      return CExtChrTaskCycle::onReceiveTask(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtChrTaskCycle::onReceiveTask(CExtChrTaskCycle *const this, Answer::NetPacket *inPacket)
{
  int32_t m_nFinishTimes; // ebx
  int32_t m_nTaskId; // ebx
  ChrTask *Task; // rax
  int64_t v6; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  m_nFinishTimes = this->m_nFinishTimes;
  if ( m_nFinishTimes >= CExtChrTaskCycle::getTaskCycleTimes(this) )
    return 2;
  if ( this->m_nState != 2 )
    return 10002;
  m_nTaskId = this->m_nTaskId;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::receive(Task, m_nTaskId) )
    return 10002;
  this->m_nState = 3;
  CExtChrTaskCycle::sendTaskInfo(this);
  v6 = this->m_nTaskId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, v6);
  return 0;
}


#####################################
int32_t __cdecl CExtChrTaskCycle::onSubmitTask(CExtChrTaskCycle *const this, Answer::NetPacket *inPacket)
{
  int32_t m_nTaskId; // ebx
  ChrTask *Task; // rax
  int32_t m_nFinishTimes; // ebx
  int64_t v6; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  int8_t nRadio; // [rsp+1Bh] [rbp-25h]
  int32_t nCost; // [rsp+1Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nRadio = Answer::NetPacket::readInt8(inPacket);
  nCost = 0;
  switch ( nRadio )
  {
    case 3:
      nCost = 10;
      break;
    case 5:
      nCost = 20;
      break;
    case 1:
      break;
    default:
      return 10002;
  }
  if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CASH) < nCost )
    return 10002;
  m_nTaskId = this->m_nTaskId;
  Task = Player::GetTask(this->m_pPlayer);
  if ( ChrTask::submit(Task, m_nTaskId, nRadio) )
    return 10002;
  Player::DecCurrency(
    this->m_pPlayer,
    CURRENCY_TYPE::CURRENCY_CASH,
    nCost,
    CURRENCY_CHANGE_REASON::GCR_TASK_CYCLE_GET_REWARD,
    nRadio);
  ++this->m_nFinishTimes;
  CExtChrTaskCycle::addRandomReward(this);
  m_nFinishTimes = this->m_nFinishTimes;
  if ( m_nFinishTimes < CExtChrTaskCycle::getTaskCycleTimes(this) )
    CExtChrTaskCycle::refreshTask(this);
  CExtChrTaskCycle::sendTaskInfo(this);
  v6 = this->m_nTaskId;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, v6);
  return 0;
}


#####################################
int32_t __cdecl CExtChrTaskCycle::onQuickDone(CExtChrTaskCycle *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  int32_t m_nTaskId; // ebx
  CfgData *v6; // rax
  ChrTask *Task; // rax
  MemChrBag *v8; // rbx
  MemChrBag *v9; // rax
  Job_t Job; // bl
  MemChrJobBag *v11; // rax
  CExtCharBag *Bag; // rax
  ChrTask *v13; // rax
  int32_t m_nFinishTimes; // ebx
  int64_t v15; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v19; // rax
  int8_t v20; // bl
  DBService *v21; // rax
  MemChrBag chrbag; // [rsp+10h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > it; // [rsp+30h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+40h] [rbp-A0h] BYREF
  LogTask logTask; // [rsp+50h] [rbp-90h] BYREF
  MemChrBagVector add; // [rsp+70h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+90h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > v29; // [rsp+A0h] [rbp-40h] BYREF
  int32_t nCount; // [rsp+ACh] [rbp-34h]
  CfgTask *pCfgTask; // [rsp+B0h] [rbp-30h]
  int32_t nTimes; // [rsp+BCh] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nCount = Answer::NetPacket::readInt32(inPacket);
  if ( nCount <= 0 )
    return 10002;
  v3 = nCount + this->m_nFinishTimes;
  if ( v3 > CExtChrTaskCycle::getTaskCycleTimes(this) )
    return 10002;
  m_nTaskId = this->m_nTaskId;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgTask = CfgData::getTask(v6, m_nTaskId);
  if ( !pCfgTask )
    return 10002;
  if ( pCfgTask->quickDoneCost <= 0 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          nCount * pCfgTask->quickDoneCost,
          CURRENCY_CHANGE_REASON::GCR_QUICK_DONE_CYCLE_TASK,
          this->m_nTaskId) )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::CleanTaskType(Task, 3);
  nTimes = 5 * nCount;
  std::vector<MemChrBag>::vector(&add, &pCfgTask->award_item);
  for ( iter._M_current = std::vector<MemChrBag>::begin(&add)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(&add)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
      break;
    v8 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter);
    v9 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter);
    v8->itemCount = nTimes * v9->itemCount;
  }
  if ( !std::vector<MemChrJobBag>::empty(&pCfgTask->award_optional) )
  {
    for ( it._M_current = std::vector<MemChrJobBag>::begin(&pCfgTask->award_optional)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator++(&it) )
    {
      v29._M_current = std::vector<MemChrJobBag>::end(&pCfgTask->award_optional)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrJobBag *,std::vector<MemChrJobBag>>(&it, &v29) )
        break;
      Job = Player::getJob(this->m_pPlayer);
      if ( Job == __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->type;
        v11 = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it);
        chrbag.itemCount = nTimes * v11->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->bind;
        std::vector<MemChrBag>::push_back(&add, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &add, ITEM_CHANGE_REASON::ICR_TASK_REWARD) )
  {
    v2 = 10002;
  }
  else
  {
    if ( pCfgTask->award_money > 0 )
      Player::AddCurrency(
        this->m_pPlayer,
        CURRENCY_TYPE::CURRENCY_MONEY,
        nTimes * pCfgTask->award_money,
        CURRENCY_CHANGE_REASON::MCR_TASK,
        pCfgTask->id);
    if ( pCfgTask->award_exp > 0 )
      Player::addExp(this->m_pPlayer, nTimes * pCfgTask->award_exp, 0, 1);
    this->m_nFinishTimes += nCount;
    CExtChrTaskCycle::addRandomReward(this);
    v13 = Player::GetTask(this->m_pPlayer);
    ChrTask::updateTaskTypeCount(v13, 3);
    m_nFinishTimes = this->m_nFinishTimes;
    if ( m_nFinishTimes < CExtChrTaskCycle::getTaskCycleTimes(this) )
      CExtChrTaskCycle::refreshTask(this);
    CExtChrTaskCycle::sendTaskInfo(this);
    v15 = this->m_nTaskId;
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v19 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v19, ConnId, GateIndex, Proc, v15);
    memset(&logTask, 0, sizeof(logTask));
    logTask.cid = Player::getCid(this->m_pPlayer);
    logTask.tid = this->m_nTaskId;
    logTask.type = 3;
    logTask.time = Unit::getNow(this->m_pPlayer);
    v20 = Player::getConnId(this->m_pPlayer);
    v21 = Answer::Singleton<DBService>::instance();
    DBService::insertTaskInfo(v21, v20, &logTask);
    v2 = 0;
  }
  std::vector<MemChrBag>::~vector(&add);
  return v2;
}


#####################################
bool __cdecl CExtChrTaskCycle::IsFunctionOpen(CExtChrTaskCycle *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 26) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CExtChrTaskCycle::OpenCycleTask(CExtChrTaskCycle *const this)
{
  if ( this->m_pPlayer )
  {
    CExtChrTaskCycle::refreshTask(this);
    CExtChrTaskCycle::sendTaskInfo(this);
  }
}


#####################################
void __cdecl CExtChrTaskCycle::sendTaskInfo(CExtChrTaskCycle *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x276Fu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nFinishTimes);
      Answer::NetPacket::writeInt32(packet, this->m_nTaskId);
      Answer::NetPacket::writeInt8(packet, this->m_nState);
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
void __cdecl CExtChrTaskCycle::refreshTask(CExtChrTaskCycle *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgTaskCycleTable *TaskCycleTable; // rax
  ChrTask *Task; // rax
  int32_t m_nTaskId; // ebx
  ChrTask *v6; // rax

  if ( this->m_pPlayer )
  {
    v1 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v2 = Answer::Singleton<CfgData>::instance();
    TaskCycleTable = CfgData::GetTaskCycleTable(v2);
    this->m_nTaskId = CfgTaskCycleTable::RandTask(TaskCycleTable, v1);
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::CleanTaskType(Task, 3);
    m_nTaskId = this->m_nTaskId;
    v6 = Player::GetTask(this->m_pPlayer);
    ChrTask::receive(v6, m_nTaskId);
    this->m_nState = 3;
  }
}


#####################################
int32_t __cdecl CExtChrTaskCycle::getTaskCycleTimes(CExtChrTaskCycle *const this)
{
  if ( this->m_pPlayer )
    return 10;
  else
    return 0;
}


#####################################
int32_t __cdecl CExtChrTaskCycle::GetSurplusTimes(CExtChrTaskCycle *const this)
{
  return CExtChrTaskCycle::getTaskCycleTimes(this) - this->m_nFinishTimes;
}


#####################################
void __cdecl CExtChrTaskCycle::addRandomReward(CExtChrTaskCycle *const this)
{
  int32_t m_nFinishTimes; // ebx
  CfgData *v3; // rax
  const CfgTaskCycleTable *TaskCycleTable; // rax
  CExtCharBag *Bag; // rax
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v8; // rax
  MemChrBagVector vItem; // [rsp+20h] [rbp-40h] BYREF
  std::string Param; // [rsp+40h] [rbp-20h] BYREF
  _BYTE v11[17]; // [rsp+4Fh] [rbp-11h] BYREF

  m_nFinishTimes = this->m_nFinishTimes;
  if ( m_nFinishTimes >= CExtChrTaskCycle::getTaskCycleTimes(this) && this->m_pPlayer )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    TaskCycleTable = CfgData::GetTaskCycleTable(v3);
    CfgTaskCycleTable::GetRandomReward(&vItem, TaskCycleTable, 2);
    if ( !std::vector<MemChrBag>::empty(&vItem) )
    {
      Bag = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::AddItem(Bag, &vItem, ITEM_CHANGE_REASON::ICR_TASK_CYCLE_REWARD) )
      {
        std::allocator<char>::allocator(v11);
        std::string::string(&Param, &unk_8F1D00);
        Cid = Player::getCid(this->m_pPlayer);
        ConnId = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(v8, ConnId, Cid, 1000, &vItem, ITEM_CHANGE_REASON::ICR_TASK_CYCLE_REWARD, &Param, 0);
        std::string::~string(&Param);
        std::allocator<char>::~allocator(v11);
      }
      CExtChrTaskCycle::sendRandomItem(this, &vItem);
    }
    std::vector<MemChrBag>::~vector(&vItem);
  }
}


#####################################
void __cdecl CExtChrTaskCycle::sendRandomItem(CExtChrTaskCycle *const this, const MemChrBagVector *const vItem)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t v4; // eax
  const MemChrBag *v5; // rax
  const MemChrBag *v6; // rax
  const MemChrBag *v7; // rax
  const MemChrBag *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2770u);
    if ( packet )
    {
      v4 = std::vector<MemChrBag>::size(vItem);
      Answer::NetPacket::writeInt32(packet, v4);
      for ( iter._M_current = std::vector<MemChrBag>::begin(vItem)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(vItem)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&iter, &__rhs) )
          break;
        v5 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v5->itemId);
        v6 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
        Answer::NetPacket::writeInt8(packet, v6->itemClass);
        v7 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v7->itemCount);
        v8 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
        Answer::NetPacket::writeInt8(packet, v8->bind);
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


