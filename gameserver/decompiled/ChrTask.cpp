// Decompiled methods for class: ChrTask
// Source: gameserver.cc
// Total methods: 37

#####################################
void __cdecl ChrTask::init(ChrTask *const this, Player *player, const MemChrTaskVector *const tasks)
{
  int32_t id; // ebx
  CfgData *v4; // rax
  int32_t v5; // ebx
  CfgData *v6; // rax
  const MemChrTask *v7; // rax
  MemChrTask *v8; // rbx
  int32_t m_trunkTaskId; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  TaskMonster taskMonster; // [rsp+20h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrTask*,std::vector<MemChrTask> > it; // [rsp+40h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrTask*,std::vector<MemChrTask> > __rhs; // [rsp+50h] [rbp-30h] BYREF
  CfgTask *cfgTask; // [rsp+60h] [rbp-20h]
  CfgTask *pCfgLastTrunk; // [rsp+68h] [rbp-18h]

  if ( player )
  {
    this->m_player = player;
    for ( it._M_current = std::vector<MemChrTask>::begin(tasks)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<MemChrTask>::end(tasks)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrTask const*,std::vector<MemChrTask>>(&it, &__rhs) )
      {
        m_trunkTaskId = this->m_trunkTaskId;
        PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_player);
        CFunctionOpen::InitFunctionOpen(PlayerFunctionOpen, m_trunkTaskId, 0);
        return;
      }
      id = __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it)->id;
      v4 = Answer::Singleton<CfgData>::instance();
      cfgTask = CfgData::getTask(v4, id);
      if ( cfgTask && cfgTask->type != 38 && cfgTask->type != 41 )
      {
        if ( cfgTask->type == 1 )
        {
          v5 = this->m_trunkTaskId;
          v6 = Answer::Singleton<CfgData>::instance();
          pCfgLastTrunk = CfgData::getTask(v6, v5);
          if ( pCfgLastTrunk )
          {
            if ( pCfgLastTrunk->main_order > cfgTask->main_order )
              continue;
            std::map<int,MemChrTask>::erase(&this->m_tasks, &this->m_trunkTaskId);
            this->m_trunkTaskId = __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it)->id;
          }
          else
          {
            this->m_trunkTaskId = cfgTask->id;
          }
        }
        v7 = __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it);
        v8 = std::map<int,MemChrTask>::operator[](&this->m_tasks, &v7->id);
        *v8 = *__gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator*(&it);
        if ( (__gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it)->state == 3
           || __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it)->state == 4)
          && ChrTask::CheckTaskCondition(this, cfgTask->condition) )
        {
          memset(&taskMonster, 0, sizeof(taskMonster));
          taskMonster.tid = __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it)->id;
          taskMonster.condition = cfgTask->condition;
          taskMonster.request.param1 = cfgTask->request.param1;
          taskMonster.request.param2 = __gnu_cxx::__normal_iterator<MemChrTask const*,std::vector<MemChrTask>>::operator->(&it)->monster;
          std::list<TaskMonster>::push_back(&this->m_taskMonsters, &taskMonster);
        }
      }
    }
  }
}


#####################################
bool __cdecl ChrTask::CheckTaskCondition(ChrTask *const this, int32_t taskCondition)
{
  return (unsigned int)taskCondition <= 0x2B && ((1LL << taskCondition) & 0xDFDDB7F2FB8LL) != 0;
}


#####################################
void __cdecl ChrTask::reset(ChrTask *const this)
{
  this->m_player = 0;
  std::map<int,MemChrTask>::clear(&this->m_tasks);
  this->m_trunkTaskId = 0;
  std::list<TaskMonster>::clear(&this->m_taskMonsters);
}


#####################################
int32_t __cdecl ChrTask::receive(ChrTask *const this, int32_t tid)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  int32_t type; // ebx
  MemChrTask *v7; // rax
  int8_t ConnId; // bl
  DBService *v9; // rax
  int32_t BuffId; // ebx
  CfgData *v11; // rax
  int32_t v12; // edx
  Buff *v13; // rbx
  int8_t v14; // bl
  DBService *v15; // rax
  int32_t MapId; // eax
  int8_t v17; // bl
  DBService *v18; // rax
  int32_t tida; // [rsp+14h] [rbp-112Ch] BYREF
  ChrTask *thisa; // [rsp+18h] [rbp-1128h]
  char LogString[4096]; // [rsp+20h] [rbp-1120h] BYREF
  main_task_log stu; // [rsp+1020h] [rbp-120h] BYREF
  Log360 Stu; // [rsp+1060h] [rbp-E0h] BYREF
  LogTask logTask; // [rsp+1090h] [rbp-B0h] BYREF
  TaskMonster taskMonster; // [rsp+10B0h] [rbp-90h] BYREF
  _BYTE v27[16]; // [rsp+10D0h] [rbp-70h] BYREF
  _BYTE v28[16]; // [rsp+10E0h] [rbp-60h] BYREF
  UnitHandle launcher; // [rsp+10F0h] [rbp-50h] BYREF
  char v30; // [rsp+1100h] [rbp-40h] BYREF
  CfgTask *cfgTask; // [rsp+1108h] [rbp-38h]
  CfgBuff *cfgBuff; // [rsp+1110h] [rbp-30h]
  Buff *buff; // [rsp+1118h] [rbp-28h]

  thisa = this;
  tida = tid;
  if ( !this->m_player )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v3, tida);
  if ( !cfgTask )
    return 10002;
  if ( !ChrTask::receivePreCheck(thisa, tida, cfgTask) )
    return 10002;
  Bag = Player::GetBag(thisa->m_player);
  if ( !CExtCharBag::AddItem(Bag, &cfgTask->items_receive, ITEM_CHANGE_REASON::ICR_NONE) )
    return 10002;
  if ( cfgTask->type == 1 )
  {
    std::map<int,MemChrTask>::erase(&thisa->m_tasks, &thisa->m_trunkTaskId);
  }
  else if ( cfgTask->type == 37 )
  {
    ChrTask::CleanTaskType(thisa, cfgTask->type);
  }
  else if ( cfgTask->pretask )
  {
    type = cfgTask->type;
    if ( type == ChrTask::GetTaskType(thisa, cfgTask->pretask) )
      std::map<int,MemChrTask>::erase(&thisa->m_tasks, &cfgTask->pretask);
  }
  v7 = std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida);
  v7->id = tida;
  std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->state = 3;
  ChrTask::sendTaskReceived(thisa, tida);
  taskMonster.condition = 0;
  *(_QWORD *)&taskMonster.request.param1 = 0;
  taskMonster.request.param3 = 0;
  taskMonster.tid = tida;
  taskMonster.condition = cfgTask->condition;
  taskMonster.request.param1 = cfgTask->request.param1;
  std::list<TaskMonster>::push_back(&thisa->m_taskMonsters, &taskMonster);
  ChrTask::sendTaskKilledMonster(thisa);
  Player::updateLastTaskId(thisa->m_player, tida);
  if ( cfgTask->type == 1 )
  {
    main_task_log::main_task_log(&stu);
    stu.log_Sid = Player::getSid(thisa->m_player);
    stu.log_time = Unit::getNow(thisa->m_player);
    Player::GetPassport((Player *const)v27);
    std::string::operator=(&stu.passport, v27);
    std::string::~string(v27);
    stu.cid = Player::getCid(thisa->m_player);
    Player::getName((const Player *const)v28);
    std::string::operator=(&stu.name, v28);
    std::string::~string(v28);
    stu.op_time = Unit::getNow(thisa->m_player);
    stu.task_id = tida;
    stu.oper_id = 1;
    ConnId = Player::getConnId(thisa->m_player);
    v9 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v9, ConnId, PLATFORM_LOG_DATA_TYPE::PLDT_TASK, &stu);
    thisa->m_trunkTaskId = tida;
    main_task_log::~main_task_log(&stu);
  }
  ChrTask::updateTaskCount(thisa, 18, 0);
  ChrTask::updateTaskCount(thisa, 19, 0);
  ChrTask::updateTaskCount(thisa, 20, 0);
  ChrTask::updateTaskCount(thisa, 22, 0);
  ChrTask::updateTaskCount(thisa, 28, 0);
  ChrTask::updateTaskCount(thisa, 37, 0);
  ChrTask::updateTaskCount(thisa, 38, 0);
  ChrTask::updateTaskCount(thisa, 39, 0);
  if ( cfgTask->BuffId > 0 )
  {
    BuffId = cfgTask->BuffId;
    v11 = Answer::Singleton<CfgData>::instance();
    cfgBuff = CfgData::getBuff(v11, BuffId);
    if ( cfgBuff )
    {
      launcher.id = (*((__int64 (__fastcall **)(Player *))thisa->m_player->_vptr_Entity + 12))(thisa->m_player);
      launcher.type = v12;
      v13 = (Buff *)operator new(0x60u);
      Buff::Buff(v13, thisa->m_player, cfgBuff, &launcher, 1, 1);
      buff = v13;
      if ( v13 )
        Unit::addBuff(thisa->m_player, buff);
    }
  }
  memset(&logTask, 0, sizeof(logTask));
  logTask.cid = Player::getCid(thisa->m_player);
  logTask.tid = tida;
  logTask.type = cfgTask->type;
  logTask.time = Unit::getNow(thisa->m_player);
  v14 = Player::getConnId(thisa->m_player);
  v15 = Answer::Singleton<DBService>::instance();
  DBService::insertTaskInfo(v15, v14, &logTask);
  memset(&Stu, 0, sizeof(Stu));
  std::string::string(&Stu.Interface);
  std::string::string(&Stu.passport);
  std::string::string(&Stu.LogString);
  std::string::operator=(&Stu, "task");
  Stu.UseSid = Player::getSid(thisa->m_player);
  Player::GetPassport((Player *const)&v30);
  std::string::operator=(&Stu.passport, &v30);
  std::string::~string(&v30);
  Stu.Cid = Player::getCid(thisa->m_player);
  memset(LogString, 0, sizeof(LogString));
  MapId = StaticObj::getMapId(thisa->m_player);
  snprintf(LogString, 0xFFFu, "taskid=%d&map_id=%d&result=2", tida, MapId);
  std::string::operator=(&Stu.LogString, LogString);
  v17 = Player::getConnId(thisa->m_player);
  v18 = Answer::Singleton<DBService>::instance();
  DBService::log360(v18, v17, &Stu);
  v2 = 0;
  Log360::~Log360(&Stu);
  return v2;
}


#####################################
bool __cdecl ChrTask::ForceSubmit(ChrTask *const this, int32_t tid)
{
  CfgData *v2; // rax
  bool v3; // bl
  Job_t Job; // bl
  CExtCharBag *Bag; // rax
  MemChrTask *v7; // rax
  TaskMonster *v8; // rax
  int8_t ConnId; // bl
  DBService *v10; // rax
  int32_t v11; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  int32_t v13; // ebx
  CfgData *v14; // rax
  MemChrBagVector *p_items_receive; // rbx
  CExtCharBag *v16; // rax
  MemChrTask *v17; // rax
  DBService *v18; // rax
  int32_t tida; // [rsp+4h] [rbp-12Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-128h]
  MemChrBag chrbag; // [rsp+10h] [rbp-120h] BYREF
  LogTask logTask_0; // [rsp+30h] [rbp-100h] BYREF
  TaskMonster taskMonster; // [rsp+50h] [rbp-E0h] BYREF
  int32_t postTaskId; // [rsp+6Ch] [rbp-C4h] BYREF
  std::_List_iterator<TaskMonster> itTaskMonster; // [rsp+70h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > it_0; // [rsp+80h] [rbp-B0h] BYREF
  LogTask logTask; // [rsp+90h] [rbp-A0h] BYREF
  MemChrBagVector add; // [rsp+B0h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+D0h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+E0h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > __rhs; // [rsp+F0h] [rbp-40h] BYREF
  std::_List_iterator<TaskMonster> v33; // [rsp+100h] [rbp-30h] BYREF
  CfgTask *cfgTask; // [rsp+108h] [rbp-28h]
  double bnfRatio; // [rsp+110h] [rbp-20h]
  CfgTask *cfgPostTask; // [rsp+118h] [rbp-18h]

  thisa = this;
  tida = tid;
  v2 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v2, tid);
  if ( cfgTask )
  {
    it._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &tida)._M_node;
    __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&it, &__x) )
      return 0;
    if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 3
      && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 4 )
    {
      return 0;
    }
    std::vector<MemChrBag>::vector(&add, &cfgTask->award_item);
    if ( !std::vector<MemChrJobBag>::empty(&cfgTask->award_optional) )
    {
      for ( it_0._M_current = std::vector<MemChrJobBag>::begin(&cfgTask->award_optional)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator++(&it_0) )
      {
        __rhs._M_current = std::vector<MemChrJobBag>::end(&cfgTask->award_optional)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrJobBag *,std::vector<MemChrJobBag>>(&it_0, &__rhs) )
          break;
        Job = Player::getJob(thisa->m_player);
        if ( Job == __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->job )
        {
          memset(&chrbag, 0, sizeof(chrbag));
          chrbag.itemId = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->id;
          chrbag.itemClass = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->type;
          chrbag.itemCount = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->count;
          chrbag.bind = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->bind;
          std::vector<MemChrBag>::push_back(&add, &chrbag);
        }
      }
    }
    Bag = Player::GetBag(thisa->m_player);
    if ( !CExtCharBag::AddItem(Bag, &add, ITEM_CHANGE_REASON::ICR_TASK_REWARD) )
    {
      v3 = 0;
LABEL_36:
      std::vector<MemChrBag>::~vector(&add);
      return v3;
    }
    if ( cfgTask->award_money > 0 )
      Player::AddCurrency(
        thisa->m_player,
        CURRENCY_TYPE::CURRENCY_MONEY,
        cfgTask->award_money,
        CURRENCY_CHANGE_REASON::MCR_TASK,
        cfgTask->id);
    if ( cfgTask->award_exp > 0 )
      Player::addExp(thisa->m_player, cfgTask->award_exp, 0, 1);
    if ( cfgTask->rongyu > 0 )
      Player::AddCurrency(
        thisa->m_player,
        CURRENCY_TYPE::CURRENCY_HONOR,
        cfgTask->rongyu,
        CURRENCY_CHANGE_REASON::MCR_TASK,
        cfgTask->id);
    v7 = std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida);
    v7->id = tida;
    std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->state = 5;
    std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->monster = 0;
    bnfRatio = Player::benefitRatio(thisa->m_player);
    ChrTask::sendTaskSubmitted(thisa, tida, (int)((double)cfgTask->award_exp * bnfRatio));
    for ( itTaskMonster._M_node = std::list<TaskMonster>::begin(&thisa->m_taskMonsters)._M_node;
          ;
          std::_List_iterator<TaskMonster>::operator++(&itTaskMonster) )
    {
      v33._M_node = std::list<TaskMonster>::end(&thisa->m_taskMonsters)._M_node;
      if ( !std::_List_iterator<TaskMonster>::operator!=(&itTaskMonster, &v33) )
        break;
      v8 = std::_List_iterator<TaskMonster>::operator->(&itTaskMonster);
      if ( v8->tid == tida )
      {
        std::list<TaskMonster>::erase(&thisa->m_taskMonsters, itTaskMonster);
        ChrTask::sendTaskKilledMonster(thisa);
        break;
      }
    }
    Player::updateLastTaskId(thisa->m_player, tida);
    memset(&logTask, 0, sizeof(logTask));
    logTask.cid = Player::getCid(thisa->m_player);
    logTask.tid = tida;
    logTask.type = cfgTask->type;
    logTask.time = Unit::getNow(thisa->m_player);
    logTask.state = 1;
    ConnId = Player::getConnId(thisa->m_player);
    v10 = Answer::Singleton<DBService>::instance();
    DBService::updateTaskInfo(v10, ConnId, &logTask);
    v11 = tida;
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(thisa->m_player);
    CFunctionOpen::CheckFunctionOpne(PlayerFunctionOpen, v11, 0);
    if ( cfgTask->type == 1 && cfgTask->posttask > 0 )
    {
      postTaskId = cfgTask->posttask;
      v13 = postTaskId;
      v14 = Answer::Singleton<CfgData>::instance();
      cfgPostTask = CfgData::getTask(v14, v13);
      if ( !cfgPostTask )
      {
        v3 = 0;
        goto LABEL_36;
      }
      p_items_receive = &cfgPostTask->items_receive;
      v16 = Player::GetBag(thisa->m_player);
      CExtCharBag::AddItem(v16, p_items_receive, ITEM_CHANGE_REASON::ICR_NONE);
      std::map<int,MemChrTask>::erase(&thisa->m_tasks, &tida);
      v17 = std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &postTaskId);
      v17->id = postTaskId;
      std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &postTaskId)->state = 3;
      ChrTask::sendTaskReceived(thisa, postTaskId);
      taskMonster.condition = 0;
      *(_QWORD *)&taskMonster.request.param1 = 0;
      taskMonster.request.param3 = 0;
      taskMonster.tid = postTaskId;
      taskMonster.condition = cfgPostTask->condition;
      taskMonster.request.param1 = cfgPostTask->request.param1;
      std::list<TaskMonster>::push_back(&thisa->m_taskMonsters, &taskMonster);
      ChrTask::sendTaskKilledMonster(thisa);
      Player::updateLastTaskId(thisa->m_player, postTaskId);
      thisa->m_trunkTaskId = postTaskId;
      ChrTask::updateTaskCount(thisa, 18, 0);
      ChrTask::updateTaskCount(thisa, 19, 0);
      ChrTask::updateTaskCount(thisa, 20, 0);
      ChrTask::updateTaskCount(thisa, 22, 0);
      ChrTask::updateTaskCount(thisa, 28, 0);
      ChrTask::updateTaskCount(thisa, 37, 0);
      ChrTask::updateTaskCount(thisa, 38, 0);
      ChrTask::updateTaskCount(thisa, 39, 0);
      memset(&logTask_0, 0, sizeof(logTask_0));
      logTask_0.cid = Player::getCid(thisa->m_player);
      logTask_0.tid = postTaskId;
      logTask_0.type = cfgPostTask->type;
      logTask_0.time = Unit::getNow(thisa->m_player);
      LOBYTE(p_items_receive) = Player::getConnId(thisa->m_player);
      v18 = Answer::Singleton<DBService>::instance();
      DBService::insertTaskInfo(v18, (int8_t)p_items_receive, &logTask_0);
    }
    ChrTask::updateTaskTypeCount(thisa, cfgTask->type);
    v3 = 1;
    goto LABEL_36;
  }
  return 0;
}


#####################################
int32_t __cdecl ChrTask::submit(ChrTask *const this, int32_t tid, int32_t nTimes)
{
  CfgData *v3; // rax
  int32_t v4; // ebx
  MemChrBag *v5; // rax
  Job_t Job; // bl
  CExtCharBag *Bag; // rax
  CExtCharBag *v8; // rax
  int32_t v9; // ebx
  CFaBao *PlayerFaBao; // rax
  MemChrTask *v11; // rax
  TaskMonster *v12; // rax
  int8_t ConnId; // bl
  DBService *v14; // rax
  int32_t MapId; // eax
  int8_t v16; // bl
  DBService *v17; // rax
  int32_t v18; // ebx
  CFunctionOpen *PlayerFunctionOpen; // rax
  int8_t v20; // bl
  DBService *v21; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharFamily *CharFamily; // rax
  CExtCharFamily *v24; // rax
  Map *Map; // rax
  CActivityMap *v26; // rax
  CActivity *Activity; // rax
  CFamilyWar *v28; // rax
  CExtOperateLimit *v29; // rax
  int32_t v30; // r12d
  int32_t v31; // ebx
  CfgData *v32; // rax
  CExtOperateLimit *v33; // rax
  int32_t v34; // r12d
  int32_t v35; // ebx
  CfgData *v36; // rax
  int32_t type; // ebx
  DailyActivity *PlayerDailyActivity; // rax
  int32_t tida; // [rsp+4h] [rbp-11BCh] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-11B8h]
  char LogString[4096]; // [rsp+10h] [rbp-11B0h] BYREF
  main_task_log stu; // [rsp+1010h] [rbp-1B0h] BYREF
  Log360 Stu; // [rsp+1050h] [rbp-170h] BYREF
  std::_List_iterator<TaskMonster> itTaskMonster; // [rsp+1080h] [rbp-140h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > it; // [rsp+1090h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+10A0h] [rbp-120h] BYREF
  ItemData item; // [rsp+10B0h] [rbp-110h] BYREF
  LogTask logTask; // [rsp+10C0h] [rbp-100h] BYREF
  MemChrBagVector add; // [rsp+10E0h] [rbp-E0h] BYREF
  ItemDataList itemSubmit; // [rsp+1100h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+1110h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > v54; // [rsp+1120h] [rbp-A0h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+1130h] [rbp-90h] BYREF
  _BYTE v56[16]; // [rsp+1140h] [rbp-80h] BYREF
  _BYTE v57[16]; // [rsp+1150h] [rbp-70h] BYREF
  char v58; // [rsp+1160h] [rbp-60h] BYREF
  CfgTask *cfgTask; // [rsp+1168h] [rbp-58h]
  float Rate; // [rsp+1174h] [rbp-4Ch]
  double bnfRatio; // [rsp+1178h] [rbp-48h]
  int64_t award_exp; // [rsp+1180h] [rbp-40h]
  int32_t GongXian; // [rsp+118Ch] [rbp-34h]
  CActivityMap *pActivityMap; // [rsp+1190h] [rbp-30h]
  CFamilyWar *pFamilyWar; // [rsp+1198h] [rbp-28h]
  int32_t Times; // [rsp+11A0h] [rbp-20h]
  int32_t TaskId; // [rsp+11A4h] [rbp-1Ch]
  int32_t Times_0; // [rsp+11A8h] [rbp-18h]
  int32_t TaskId_0; // [rsp+11ACh] [rbp-14h]

  thisa = this;
  tida = tid;
  v3 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v3, tid);
  if ( !cfgTask )
    return 10002;
  if ( !ChrTask::submitPreCheck(thisa, tida, cfgTask) )
    return 10002;
  std::list<ItemData>::list(&itemSubmit);
  if ( cfgTask->condition == 2 )
  {
    *(_QWORD *)&item.m_nId = 0;
    item.m_nCount = 0;
    item.m_nId = cfgTask->request.param1;
    item.m_nClass = cfgTask->request.param2;
    item.m_nCount = cfgTask->request.param3;
    std::list<ItemData>::push_back(&itemSubmit, &item);
  }
  std::vector<MemChrBag>::vector(&add, &cfgTask->award_item);
  for ( iter._M_current = std::vector<MemChrBag>::begin(&add)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(&add)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
      break;
    v5 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter);
    v5->itemCount *= nTimes;
  }
  if ( !std::vector<MemChrJobBag>::empty(&cfgTask->award_optional) )
  {
    for ( it._M_current = std::vector<MemChrJobBag>::begin(&cfgTask->award_optional)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator++(&it) )
    {
      v54._M_current = std::vector<MemChrJobBag>::end(&cfgTask->award_optional)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrJobBag *,std::vector<MemChrJobBag>>(&it, &v54) )
        break;
      Job = Player::getJob(thisa->m_player);
      if ( Job == __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->job )
      {
        memset(&stu, 0, 32);
        LODWORD(stu._vptr_platform_log_base) = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->id;
        BYTE4(stu._vptr_platform_log_base) = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->type;
        stu.log_time = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->count;
        LOBYTE(stu.log_Sid) = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it)->bind;
        std::vector<MemChrBag>::push_back(&add, (const MemChrBag *const)&stu);
      }
    }
  }
  Bag = Player::GetBag(thisa->m_player);
  if ( !CExtCharBag::RemoveItem(Bag, &itemSubmit, ITEM_CHANGE_REASON::ICR_TASK_SUBMIT) )
  {
    v4 = 10002;
  }
  else
  {
    v8 = Player::GetBag(thisa->m_player);
    if ( !CExtCharBag::AddItem(v8, &add, ITEM_CHANGE_REASON::ICR_TASK_REWARD) )
    {
      v4 = 10002;
    }
    else
    {
      Rate = ChrTask::GetTaskRewardRate(thisa, (TaskType)cfgTask->type);
      if ( cfgTask->award_money > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_BIND_MONEY,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->award_money) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->award_exp > 0 )
      {
        award_exp = nTimes * cfgTask->award_exp;
        Player::addExp(thisa->m_player, (unsigned int)(int)(float)((float)(int)award_exp * Rate), 0, 1);
      }
      if ( cfgTask->dilong > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_VIGOUR,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->dilong) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->fuwen > 0 )
      {
        v9 = (int)(float)((float)(nTimes * cfgTask->fuwen) * Rate);
        PlayerFaBao = Player::GetPlayerFaBao(thisa->m_player);
        CFaBao::AddFaBaoRes(PlayerFaBao, 2, v9);
      }
      if ( cfgTask->rongyu > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_HONOR,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->rongyu) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->acScore > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_AC_SOCRE,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->acScore) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->gold > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_CASH,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->gold) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->dust > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_DUST,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->dust) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->BossScore > 0 )
        Player::AddCurrency(
          thisa->m_player,
          CURRENCY_TYPE::CURRENCY_BOSS_SCORE,
          (unsigned int)(int)(float)((float)(nTimes * cfgTask->BossScore) * Rate),
          CURRENCY_CHANGE_REASON::MCR_TASK,
          cfgTask->id);
      if ( cfgTask->type == 37 || cfgTask->type == 41 )
      {
        std::map<int,MemChrTask>::erase(&thisa->m_tasks, &tida);
      }
      else
      {
        v11 = std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida);
        v11->id = tida;
        std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->state = 5;
        std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->monster = 0;
      }
      bnfRatio = Player::benefitRatio(thisa->m_player);
      ChrTask::sendTaskSubmitted(thisa, tida, (int)((double)cfgTask->award_exp * bnfRatio));
      for ( itTaskMonster._M_node = std::list<TaskMonster>::begin(&thisa->m_taskMonsters)._M_node;
            ;
            std::_List_iterator<TaskMonster>::operator++(&itTaskMonster) )
      {
        __x._M_node = std::list<TaskMonster>::end(&thisa->m_taskMonsters)._M_node;
        if ( !std::_List_iterator<TaskMonster>::operator!=(&itTaskMonster, &__x) )
          break;
        v12 = std::_List_iterator<TaskMonster>::operator->(&itTaskMonster);
        if ( v12->tid == tida )
        {
          std::list<TaskMonster>::erase(&thisa->m_taskMonsters, itTaskMonster);
          ChrTask::sendTaskKilledMonster(thisa);
          break;
        }
      }
      Player::updateLastTaskId(thisa->m_player, tida);
      memset(&logTask, 0, sizeof(logTask));
      logTask.cid = Player::getCid(thisa->m_player);
      logTask.tid = tida;
      logTask.type = cfgTask->type;
      logTask.time = Unit::getNow(thisa->m_player);
      logTask.state = 1;
      ConnId = Player::getConnId(thisa->m_player);
      v14 = Answer::Singleton<DBService>::instance();
      DBService::updateTaskInfo(v14, ConnId, &logTask);
      memset(&Stu, 0, sizeof(Stu));
      std::string::string(&Stu.Interface);
      std::string::string(&Stu.passport);
      std::string::string(&Stu.LogString);
      std::string::operator=(&Stu, "task");
      Stu.UseSid = Player::getSid(thisa->m_player);
      Player::GetPassport((Player *const)v56);
      std::string::operator=(&Stu.passport, v56);
      std::string::~string(v56);
      Stu.Cid = Player::getCid(thisa->m_player);
      memset(LogString, 0, sizeof(LogString));
      MapId = StaticObj::getMapId(thisa->m_player);
      snprintf(LogString, 0xFFFu, "taskid=%d&map_id=%d&result=0", tida, MapId);
      std::string::operator=(&Stu.LogString, LogString);
      v16 = Player::getConnId(thisa->m_player);
      v17 = Answer::Singleton<DBService>::instance();
      DBService::log360(v17, v16, &Stu);
      v18 = tida;
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(thisa->m_player);
      CFunctionOpen::CheckFunctionOpne(PlayerFunctionOpen, v18, 0);
      switch ( cfgTask->type )
      {
        case 1:
        case 0x26:
          if ( cfgTask->type == 1 )
          {
            main_task_log::main_task_log(&stu);
            stu.log_Sid = Player::getSid(thisa->m_player);
            stu.log_time = Unit::getNow(thisa->m_player);
            Player::GetPassport((Player *const)v57);
            std::string::operator=(&stu.passport, v57);
            std::string::~string(v57);
            stu.cid = Player::getCid(thisa->m_player);
            Player::getName((const Player *const)&v58);
            std::string::operator=(&stu.name, &v58);
            std::string::~string(&v58);
            stu.op_time = Unit::getNow(thisa->m_player);
            stu.task_id = tida;
            stu.oper_id = 2;
            v20 = Player::getConnId(thisa->m_player);
            v21 = Answer::Singleton<DBService>::instance();
            DBService::AddPlatformLog(v21, v20, PLATFORM_LOG_DATA_TYPE::PLDT_TASK, &stu);
            main_task_log::~main_task_log(&stu);
          }
          if ( cfgTask->posttask > 0 )
            ChrTask::receive(thisa, cfgTask->posttask);
          break;
        case 0x25:
          OperateLimit = Player::GetOperateLimit(thisa->m_player);
          CExtOperateLimit::AddLimitCount(OperateLimit, 2019, 1);
          CharFamily = Player::GetCharFamily(thisa->m_player);
          CExtCharFamily::SendAddFamilyTaskCount(CharFamily);
          GongXian = nTimes * cfgTask->GongXian;
          v24 = Player::GetCharFamily(thisa->m_player);
          CExtCharFamily::AddContribution(v24, GongXian, CURRENCY_CHANGE_REASON::FCCR_FAMILY_TASK);
          break;
        case 0x29:
          Map = StaticObj::getMap(thisa->m_player);
          v26 = Map
              ? (CActivityMap *)__dynamic_cast(
                                  Map,
                                  (const struct __class_type_info *)&`typeinfo for'Map,
                                  (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                  0)
              : 0LL;
          pActivityMap = v26;
          if ( v26 )
          {
            Activity = CActivityMap::GetActivity(pActivityMap);
            v28 = Activity
                ? (CFamilyWar *)__dynamic_cast(
                                  Activity,
                                  (const struct __class_type_info *)&`typeinfo for'CActivity,
                                  (const struct __class_type_info *)&`typeinfo for'CFamilyWar,
                                  0)
                : 0LL;
            pFamilyWar = v28;
            if ( v28 )
              CFamilyWar::OnTaskSubmited(pFamilyWar, thisa->m_player, cfgTask->activity_score);
          }
          break;
      }
      if ( cfgTask->type == 9 )
      {
        v29 = Player::GetOperateLimit(thisa->m_player);
        CExtOperateLimit::AddLimitCount(v29, 2072, 1);
        Times = Player::getRecord(thisa->m_player, 2072);
        if ( Times <= 4 )
        {
          v30 = Times + 1;
          v31 = (*((__int64 (__fastcall **)(Player *))thisa->m_player->_vptr_Entity + 9))(thisa->m_player);
          v32 = Answer::Singleton<CfgData>::instance();
          TaskId = CfgData::InitXuWuTask(v32, v31, v30);
          if ( TaskId > 0 )
            ChrTask::receive(thisa, TaskId);
        }
      }
      if ( cfgTask->type == 42 )
      {
        v33 = Player::GetOperateLimit(thisa->m_player);
        CExtOperateLimit::AddLimitCount(v33, 2118, 1);
        Times_0 = Player::getRecord(thisa->m_player, 2118);
        if ( Times_0 <= 4 )
        {
          v34 = Times_0 + 1;
          v35 = (*((__int64 (__fastcall **)(Player *))thisa->m_player->_vptr_Entity + 9))(thisa->m_player);
          v36 = Answer::Singleton<CfgData>::instance();
          TaskId_0 = CfgData::InitXinMoTask(v36, v35, v34);
          if ( TaskId_0 > 0 )
            ChrTask::receive(thisa, TaskId_0);
        }
      }
      type = cfgTask->type;
      PlayerDailyActivity = Player::GetPlayerDailyActivity(thisa->m_player);
      DailyActivity::AddTaskRecord(PlayerDailyActivity, type);
      ChrTask::updateTaskTypeCount(thisa, cfgTask->type);
      v4 = 0;
      Log360::~Log360(&Stu);
    }
  }
  std::vector<MemChrBag>::~vector(&add);
  std::list<ItemData>::~list(&itemSubmit);
  return v4;
}


#####################################
int32_t __cdecl ChrTask::giveUp(ChrTask *const this, int32_t tid)
{
  CfgData *v2; // rax
  int32_t v3; // ebx
  CExtCharBag *Bag; // rax
  TaskMonster *v6; // rax
  int32_t tida; // [rsp+4h] [rbp-9Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-98h]
  std::_List_iterator<TaskMonster> itTaskMonster; // [rsp+10h] [rbp-90h] BYREF
  ItemData data; // [rsp+20h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+30h] [rbp-70h] BYREF
  ItemDataList dataLst; // [rsp+40h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+50h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+60h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> v17; // [rsp+80h] [rbp-20h] BYREF
  CfgTask *cfgTask; // [rsp+88h] [rbp-18h]

  thisa = this;
  tida = tid;
  v2 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v2, tid);
  if ( !cfgTask )
    return 10002;
  if ( !cfgTask->can_giveup )
    return 10002;
  it._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &tida)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&it, &__x)
    || std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 3 )
  {
    return 10002;
  }
  std::list<ItemData>::list(&dataLst);
  for ( iter._M_current = std::vector<MemChrBag>::begin(&cfgTask->items_receive)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(&cfgTask->items_receive)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
      break;
    *(_QWORD *)&data.m_nId = 0;
    data.m_nCount = 0;
    data.m_nId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->itemId;
    data.m_nCount = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->itemCount;
    data.m_nClass = 1;
    std::list<ItemData>::push_back(&dataLst, &data);
  }
  Bag = Player::GetBag(thisa->m_player);
  if ( !CExtCharBag::RemoveItem(Bag, &dataLst, ITEM_CHANGE_REASON::ICR_TASK_DROP) )
  {
    v3 = 10002;
  }
  else
  {
    std::map<int,MemChrTask>::erase(&thisa->m_tasks, &tida);
    ChrTask::sendTaskGiveUped(thisa, tida);
    for ( itTaskMonster._M_node = std::list<TaskMonster>::begin(&thisa->m_taskMonsters)._M_node;
          ;
          std::_List_iterator<TaskMonster>::operator++(&itTaskMonster) )
    {
      v17._M_node = std::list<TaskMonster>::end(&thisa->m_taskMonsters)._M_node;
      if ( !std::_List_iterator<TaskMonster>::operator!=(&itTaskMonster, &v17) )
        break;
      v6 = std::_List_iterator<TaskMonster>::operator->(&itTaskMonster);
      if ( v6->tid == tida )
      {
        std::list<TaskMonster>::erase(&thisa->m_taskMonsters, itTaskMonster);
        ChrTask::sendTaskKilledMonster(thisa);
        break;
      }
    }
    v3 = 0;
  }
  std::list<ItemData>::~list(&dataLst);
  return v3;
}


#####################################
void __cdecl ChrTask::checkTaskCanSubmit(ChrTask *const this, int32_t dungenID, int8_t dungeonType)
{
  int32_t id; // ebx
  CfgData *v4; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  std::pair<const int,MemChrTask> *v7; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-30h] BYREF
  CfgTask *pTask; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  for ( it._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&it) )
  {
    __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it, &__x) )
      break;
    id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.id;
    v4 = Answer::Singleton<CfgData>::instance();
    pTask = CfgData::getTask(v4, id);
    if ( pTask
      && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 5
      && (pTask->condition == 14 && pTask->request.param1 == dungenID
       || pTask->condition == 29 && pTask->request.param1 == dungeonType) )
    {
      std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state = 4;
      ChrTask::sendTaskList(this);
      ConnId = Player::getConnId(this->m_player);
      v6 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2774u);
      if ( packet )
      {
        v7 = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v7->second.id);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_player);
        v10 = Player::getConnId(this->m_player);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v11, v10, GateIndex, packet);
      }
    }
  }
}


#####################################
int32_t __cdecl ChrTask::quickDone(ChrTask *const this, int32_t tid)
{
  CfgData *v2; // rax
  int32_t v3; // ebx
  Job_t Job; // bl
  CExtCharBag *Bag; // rax
  MemChrTask *v7; // rax
  TaskMonster *v8; // rax
  int32_t type; // ebx
  DailyActivity *PlayerDailyActivity; // rax
  DBService *v11; // rax
  int32_t tida; // [rsp+4h] [rbp-ECh] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-E8h]
  MemChrBag chrbag; // [rsp+10h] [rbp-E0h] BYREF
  std::_List_iterator<TaskMonster> itTaskMonster; // [rsp+30h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > it_0; // [rsp+40h] [rbp-B0h] BYREF
  LogTask logTask; // [rsp+50h] [rbp-A0h] BYREF
  MemChrBagVector add; // [rsp+70h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+90h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+A0h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<MemChrJobBag*,std::vector<MemChrJobBag> > __rhs; // [rsp+B0h] [rbp-40h] BYREF
  std::_List_iterator<TaskMonster> v23; // [rsp+C0h] [rbp-30h] BYREF
  CfgTask *cfgTask; // [rsp+C8h] [rbp-28h]
  double bnfRatio; // [rsp+D0h] [rbp-20h]
  BenefitType bnfType; // [rsp+DCh] [rbp-14h]

  thisa = this;
  tida = tid;
  v2 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v2, tid);
  if ( !cfgTask )
    return 10002;
  if ( Player::GetCurrency(thisa->m_player, CURRENCY_TYPE::CURRENCY_GOLD) < cfgTask->quickDoneCost )
    return 10002;
  it._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &tida)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&it, &__x)
    || std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 3 )
  {
    return 10002;
  }
  std::vector<MemChrBag>::vector(&add, &cfgTask->award_item);
  if ( !std::vector<MemChrJobBag>::empty(&cfgTask->award_optional) )
  {
    for ( it_0._M_current = std::vector<MemChrJobBag>::begin(&cfgTask->award_optional)._M_current;
          ;
          __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator++(&it_0) )
    {
      __rhs._M_current = std::vector<MemChrJobBag>::end(&cfgTask->award_optional)._M_current;
      if ( !__gnu_cxx::operator!=<MemChrJobBag *,std::vector<MemChrJobBag>>(&it_0, &__rhs) )
        break;
      Job = Player::getJob(thisa->m_player);
      if ( Job == __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->type;
        chrbag.itemCount = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<MemChrJobBag *,std::vector<MemChrJobBag>>::operator->(&it_0)->bind;
        std::vector<MemChrBag>::push_back(&add, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(thisa->m_player);
  if ( !CExtCharBag::AddItem(Bag, &add, ITEM_CHANGE_REASON::ICR_TASK_REWARD) )
  {
    v3 = 10002;
  }
  else
  {
    if ( cfgTask->award_money > 0 )
      Player::AddCurrency(
        thisa->m_player,
        CURRENCY_TYPE::CURRENCY_MONEY,
        cfgTask->award_money,
        CURRENCY_CHANGE_REASON::MCR_TASK,
        cfgTask->id);
    if ( cfgTask->award_exp > 0 )
      Player::addExp(thisa->m_player, cfgTask->award_exp, 0, 1);
    if ( cfgTask->BossScore > 0 )
      Player::AddCurrency(
        thisa->m_player,
        CURRENCY_TYPE::CURRENCY_BOSS_SCORE,
        cfgTask->BossScore,
        CURRENCY_CHANGE_REASON::MCR_TASK,
        cfgTask->id);
    v7 = std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida);
    v7->id = tida;
    std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->state = 5;
    std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &tida)->monster = 0;
    bnfRatio = Player::benefitRatio(thisa->m_player);
    ChrTask::sendTaskSubmitted(thisa, tida, (int)((double)cfgTask->award_exp * bnfRatio));
    for ( itTaskMonster._M_node = std::list<TaskMonster>::begin(&thisa->m_taskMonsters)._M_node;
          ;
          std::_List_iterator<TaskMonster>::operator++(&itTaskMonster) )
    {
      v23._M_node = std::list<TaskMonster>::end(&thisa->m_taskMonsters)._M_node;
      if ( !std::_List_iterator<TaskMonster>::operator!=(&itTaskMonster, &v23) )
        break;
      v8 = std::_List_iterator<TaskMonster>::operator->(&itTaskMonster);
      if ( v8->tid == tida )
      {
        std::list<TaskMonster>::erase(&thisa->m_taskMonsters, itTaskMonster);
        ChrTask::sendTaskKilledMonster(thisa);
        break;
      }
    }
    bnfType = Player::benefitType(thisa->m_player);
    Player::updateLastTaskId(thisa->m_player, tida);
    if ( cfgTask->quickDoneCost > 0 )
      Player::DecCurrency(
        thisa->m_player,
        CURRENCY_TYPE::CURRENCY_GOLD,
        cfgTask->quickDoneCost,
        CURRENCY_CHANGE_REASON::GCR_QUICK_TASK,
        tida);
    ChrTask::updateTaskTypeCount(thisa, cfgTask->type);
    type = cfgTask->type;
    PlayerDailyActivity = Player::GetPlayerDailyActivity(thisa->m_player);
    DailyActivity::AddTaskRecord(PlayerDailyActivity, type);
    memset(&logTask, 0, sizeof(logTask));
    logTask.cid = Player::getCid(thisa->m_player);
    logTask.tid = tida;
    logTask.type = cfgTask->type;
    logTask.time = Unit::getNow(thisa->m_player);
    logTask.state = 2;
    LOBYTE(type) = Player::getConnId(thisa->m_player);
    v11 = Answer::Singleton<DBService>::instance();
    DBService::updateTaskInfo(v11, type, &logTask);
    v3 = 0;
  }
  std::vector<MemChrBag>::~vector(&add);
  return v3;
}


#####################################
bool __cdecl ChrTask::receivePreCheck(ChrTask *const this, int32_t tid, const CfgTask *const cfgTask)
{
  int32_t start_npc; // ebx
  CfgData *v5; // rax
  int32_t MapId; // eax
  int32_t pretask; // ebx
  CfgData *v8; // rax
  int32_t m_trunkTaskId; // ebx
  CfgData *v10; // rax
  std::pair<const int,MemChrTask> *v11; // rax
  int32_t v12; // ebx
  CfgData *v13; // rax
  CfgData *v14; // rax
  int32_t tida; // [rsp+14h] [rbp-ACh] BYREF
  ChrTask *thisa; // [rsp+18h] [rbp-A8h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itPreTask; // [rsp+20h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTrunk; // [rsp+30h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+50h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v23; // [rsp+60h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v24; // [rsp+70h] [rbp-50h] BYREF
  CfgNpc *cfgNpc; // [rsp+80h] [rbp-40h]
  CfgTask *pCfgPreTask; // [rsp+88h] [rbp-38h]
  CfgTask *pCfgTrunkTask; // [rsp+90h] [rbp-30h]
  CfgTask *pCfg; // [rsp+98h] [rbp-28h]
  int32_t TaskId; // [rsp+A4h] [rbp-1Ch]
  CfgTask *pHasCfg; // [rsp+A8h] [rbp-18h]

  thisa = this;
  tida = tid;
  if ( !this->m_player )
    return 0;
  itTask._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &tida)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&itTask, &__x) )
    return 0;
  if ( cfgTask->start_npc )
  {
    start_npc = cfgTask->start_npc;
    v5 = Answer::Singleton<CfgData>::instance();
    cfgNpc = CfgData::getNpc(v5, start_npc);
    if ( !cfgNpc )
      return 0;
    MapId = StaticObj::getMapId(thisa->m_player);
    if ( !CfgNpc::findMapId(cfgNpc, MapId) )
      return 0;
  }
  if ( cfgTask->pretask )
  {
    pretask = cfgTask->pretask;
    v8 = Answer::Singleton<CfgData>::instance();
    pCfgPreTask = CfgData::getTask(v8, pretask);
    if ( !pCfgPreTask )
      return 0;
    if ( cfgTask->type == 1 )
    {
      m_trunkTaskId = thisa->m_trunkTaskId;
      v10 = Answer::Singleton<CfgData>::instance();
      pCfgTrunkTask = CfgData::getTask(v10, m_trunkTaskId);
      if ( !pCfgTrunkTask )
        return 0;
      itTrunk._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &thisa->m_trunkTaskId)._M_node;
      v23._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTrunk, &v23) )
        return 0;
      v11 = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTrunk);
      if ( v11->second.id == tida )
        return 0;
      if ( pCfgPreTask->id != pCfgTrunkTask->id )
        return 0;
      if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTrunk)->second.state != 5 )
        return 0;
    }
    else
    {
      v12 = cfgTask->pretask;
      v13 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::getTask(v13, v12);
      if ( !pCfg )
        return 0;
      if ( pCfg->type == cfgTask->type )
      {
        itPreTask._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &cfgTask->pretask)._M_node;
        v24._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itPreTask, &v24)
          || std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itPreTask)->second.state != 5 )
        {
          return 0;
        }
      }
      else
      {
        if ( ChrTask::GetTypeTask(thisa, cfgTask->type) > 0 )
          return 0;
        TaskId = ChrTask::GetTypeTask(thisa, pCfg->type);
        v14 = Answer::Singleton<CfgData>::instance();
        pHasCfg = CfgData::getTask(v14, TaskId);
        if ( !pHasCfg )
          return 0;
        if ( pHasCfg->main_order < pCfg->main_order )
          return 0;
      }
    }
  }
  else if ( (cfgTask->type == 3 || cfgTask->type == 37) && ChrTask::GetTypeTask(thisa, cfgTask->type) > 0 )
  {
    return 0;
  }
  if ( cfgTask->job )
  {
    if ( cfgTask->job == 100 )
    {
      if ( !Player::getJob(thisa->m_player) )
        return 0;
    }
    else if ( Player::getJob(thisa->m_player) != cfgTask->job )
    {
      return 0;
    }
  }
  return (*((int (__fastcall **)(Player *))thisa->m_player->_vptr_Entity + 9))(thisa->m_player) >= cfgTask->level;
}


#####################################
bool __cdecl ChrTask::submitPreCheck(ChrTask *const this, int32_t tid, const CfgTask *const cfgTask)
{
  bool result; // al
  int32_t end_npc; // ebx
  CfgData *v5; // rax
  int32_t MapId; // eax
  int32_t tida; // [rsp+14h] [rbp-3Ch] BYREF
  ChrTask *thisa; // [rsp+18h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+30h] [rbp-20h] BYREF
  CfgNpc *cfgNpc; // [rsp+38h] [rbp-18h]

  thisa = this;
  tida = tid;
  if ( !this->m_player )
    return 0;
  if ( !cfgTask->end_npc )
    goto LABEL_8;
  end_npc = cfgTask->end_npc;
  v5 = Answer::Singleton<CfgData>::instance();
  cfgNpc = CfgData::getNpc(v5, end_npc);
  if ( !cfgNpc )
    return 0;
  MapId = StaticObj::getMapId(thisa->m_player);
  if ( !CfgNpc::findMapId(cfgNpc, MapId) )
    return 0;
LABEL_8:
  it._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &tida)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&it, &__x) )
    return 0;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 3
    && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 4 )
  {
    return 0;
  }
  if ( cfgTask->type == 37 && Player::getFamilyId(thisa->m_player) <= 0 )
    return 0;
  switch ( cfgTask->condition )
  {
    case 1:
      result = 1;
      break;
    case 2:
      result = Player::hasItem(
                 thisa->m_player,
                 cfgTask->request.param1,
                 cfgTask->request.param2,
                 cfgTask->request.param3);
      break;
    case 3:
    case 4:
    case 5:
    case 0xB:
    case 0xD:
    case 0x10:
    case 0x1E:
    case 0x24:
    case 0x2B:
      result = ChrTask::getMonster(thisa, tida) >= cfgTask->request.param2;
      break;
    case 6:
      result = (*((int (__fastcall **)(Player *))thisa->m_player->_vptr_Entity + 9))(thisa->m_player) >= cfgTask->request.param1;
      break;
    case 7:
    case 8:
    case 9:
    case 0xA:
    case 0x11:
    case 0x15:
    case 0x18:
    case 0x19:
    case 0x1B:
    case 0x20:
    case 0x22:
    case 0x23:
    case 0x28:
    case 0x2A:
      result = ChrTask::getMonster(thisa, tida) >= cfgTask->request.param1;
      break;
    case 0xC:
    case 0xE:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x16:
    case 0x1C:
    case 0x1D:
    case 0x1F:
    case 0x25:
    case 0x26:
    case 0x27:
      result = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state == 4;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
void __cdecl ChrTask::updateTaskUseItem(ChrTask *const this, int32_t id, int32_t Count)
{
  int32_t tid; // edx
  TaskMonster *v4; // rax
  std::_List_iterator<TaskMonster> it; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+40h] [rbp-20h] BYREF
  bool update; // [rsp+4Fh] [rbp-11h]
  TaskRequest TaskCfgRequest; // 0:rax.12

  update = 0;
  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<TaskMonster>::operator->(&it)->condition == 3
      && std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == id )
    {
      tid = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
      TaskCfgRequest = ChrTask::GetTaskCfgRequest(this, tid);
      if ( TaskCfgRequest.param2 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
        update = 1;
      v4 = std::_List_iterator<TaskMonster>::operator->(&it);
      v4->request.param2 += Count;
    }
  }
  if ( update )
    ChrTask::sendTaskKilledMonster(this);
}


#####################################
void __cdecl ChrTask::updateTaskTypeCount(ChrTask *const this, int32_t taskType)
{
  int32_t tid; // edx
  TaskMonster *v3; // rax
  std::_List_iterator<TaskMonster> it; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+40h] [rbp-20h] BYREF
  bool update; // [rsp+4Fh] [rbp-11h]
  TaskRequest TaskCfgRequest; // 0:rax.12

  update = 0;
  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<TaskMonster>::operator->(&it)->condition == 11
      && std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == taskType )
    {
      tid = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
      TaskCfgRequest = ChrTask::GetTaskCfgRequest(this, tid);
      if ( TaskCfgRequest.param2 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
        update = 1;
      v3 = std::_List_iterator<TaskMonster>::operator->(&it);
      ++v3->request.param2;
    }
  }
  if ( update )
    ChrTask::sendTaskKilledMonster(this);
}


#####################################
void __cdecl ChrTask::updateTaskPlant(ChrTask *const this, int32_t id)
{
  int32_t tid; // edx
  TaskMonster *v3; // rax
  std::_List_iterator<TaskMonster> it; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+40h] [rbp-20h] BYREF
  bool update; // [rsp+4Fh] [rbp-11h]
  TaskRequest TaskCfgRequest; // 0:rax.12

  update = 0;
  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<TaskMonster>::operator->(&it)->condition == 13
      && std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == id )
    {
      tid = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
      TaskCfgRequest = ChrTask::GetTaskCfgRequest(this, tid);
      if ( TaskCfgRequest.param2 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
        update = 1;
      v3 = std::_List_iterator<TaskMonster>::operator->(&it);
      ++v3->request.param2;
    }
  }
  if ( update )
    ChrTask::sendTaskKilledMonster(this);
}


#####################################
void __cdecl ChrTask::updateTaskMonster(ChrTask *const this, int32_t Mid, int32_t group_id, int32_t level)
{
  int32_t condition; // eax
  int32_t v5; // edx
  Answer::Random *v6; // rax
  int32_t v7; // edx
  Answer::Random *v8; // rax
  int32_t tid; // edx
  TaskMonster *v10; // rax
  int32_t param2; // ebx
  int32_t v12; // ecx
  int32_t Request_0_4; // [rsp+44h] [rbp-4Ch]
  int32_t Request_0_8; // [rsp+48h] [rbp-48h]
  int32_t Request_4; // [rsp+54h] [rbp-3Ch]
  int32_t Request_8; // [rsp+58h] [rbp-38h]
  std::_List_iterator<TaskMonster> it; // [rsp+60h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+70h] [rbp-20h] BYREF
  bool update; // [rsp+7Fh] [rbp-11h]
  TaskRequest v22; // 0:rax.12
  TaskRequest v23; // 0:rax.12
  TaskRequest TaskCfgRequest; // 0:rax.12

  update = 0;
  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
      break;
    condition = std::_List_iterator<TaskMonster>::operator->(&it)->condition;
    if ( condition == 5 )
    {
      if ( std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 > level )
        continue;
      tid = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
      TaskCfgRequest = ChrTask::GetTaskCfgRequest(this, tid);
      if ( TaskCfgRequest.param2 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
        update = 1;
      goto LABEL_18;
    }
    if ( condition == 36 )
    {
      if ( std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == group_id )
      {
        v7 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
        v23 = ChrTask::GetTaskCfgRequest(this, v7);
        Request_0_4 = v23.param2;
        Request_0_8 = v23.param3;
        v8 = Answer::Singleton<Answer::Random>::instance();
        if ( Answer::Random::generate(v8, 1, 100) <= Request_0_8 )
        {
          if ( Request_0_4 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
            update = 1;
          goto LABEL_18;
        }
      }
    }
    else if ( condition == 4 && std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == Mid )
    {
      v5 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
      v22 = ChrTask::GetTaskCfgRequest(this, v5);
      Request_4 = v22.param2;
      Request_8 = v22.param3;
      v6 = Answer::Singleton<Answer::Random>::instance();
      if ( Answer::Random::generate(v6, 1, 100) <= Request_8 )
      {
        if ( Request_4 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
          update = 1;
LABEL_18:
        v10 = std::_List_iterator<TaskMonster>::operator->(&it);
        ++v10->request.param2;
        param2 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
        v12 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
        ChrTask::checkTaskDrop(this, v12, param2);
        continue;
      }
    }
  }
  if ( update )
    ChrTask::sendTaskKilledMonster(this);
}


#####################################
void __cdecl ChrTask::updateTaskSkill(ChrTask *const this, int32_t skillID)
{
  int32_t tid; // edx
  TaskMonster *v3; // rax
  std::_List_iterator<TaskMonster> it; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+40h] [rbp-20h] BYREF
  bool update; // [rsp+4Fh] [rbp-11h]
  TaskRequest TaskCfgRequest; // 0:rax.12

  update = 0;
  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<TaskMonster>::operator->(&it)->condition == 16
      && std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == skillID )
    {
      tid = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
      TaskCfgRequest = ChrTask::GetTaskCfgRequest(this, tid);
      if ( TaskCfgRequest.param2 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
        update = 1;
      v3 = std::_List_iterator<TaskMonster>::operator->(&it);
      ++v3->request.param2;
    }
  }
  if ( update )
    ChrTask::sendTaskKilledMonster(this);
}


#####################################
void __cdecl ChrTask::updateTaskCount(ChrTask *const this, int32_t Condition, int32_t param)
{
  int32_t param1; // ebx
  int32_t tid; // edx
  TaskMonster *v5; // rax
  int32_t v6; // ebx
  int32_t v7; // edx
  TaskMonster *v8; // rax
  TaskMonster *v9; // rax
  int32_t v10; // edx
  TaskMonster *v11; // rax
  int32_t v12; // ebx
  CExtEquip *Equip; // rax
  TaskMonster *v14; // rax
  TaskMonster *v15; // rax
  int32_t v16; // ebx
  CfgData *v17; // rax
  TaskMonster *v18; // rax
  int32_t v19; // ecx
  TaskMonster *v20; // rax
  int32_t v21; // ebx
  CExtEquip *v22; // rax
  TaskMonster *v23; // rax
  TaskMonster *v24; // rax
  int32_t v25; // ebx
  CfgData *v26; // rax
  TaskMonster *v27; // rax
  int32_t v28; // ecx
  TaskMonster *v29; // rax
  CVip *PlayerVip; // rax
  TaskMonster *v31; // rax
  TaskMonster *v32; // rax
  int32_t param2; // ebx
  int32_t v34; // ecx
  TaskMonster *v35; // rax
  Map *Map; // rax
  CActivityMap *v37; // rax
  CActivity *Activity; // rax
  CFamilyWar *v39; // rax
  FamilyId_t FamilyId; // rax
  TaskMonster *v41; // rax
  TaskMonster *v42; // rax
  int32_t v43; // ebx
  CfgData *v44; // rax
  TaskMonster *v45; // rax
  int32_t v46; // ecx
  TaskMonster *v47; // rax
  TaskMonster *v48; // rax
  TaskMonster *v49; // rax
  int32_t v50; // ebx
  int32_t v51; // ecx
  TaskMonster *v52; // rax
  TaskMonster *v53; // rax
  TaskMonster *v54; // rax
  int32_t v55; // ebx
  int32_t v56; // ecx
  TaskMonster *v57; // rax
  CExtCharJueWei *CharJueWei; // rax
  TaskMonster *v59; // rax
  TaskMonster *v60; // rax
  int32_t v61; // ebx
  int32_t v62; // ecx
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_6; // [rsp+20h] [rbp-1A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_5; // [rsp+30h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_4; // [rsp+40h] [rbp-180h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_3; // [rsp+50h] [rbp-170h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_2; // [rsp+60h] [rbp-160h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_1; // [rsp+70h] [rbp-150h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask_0; // [rsp+80h] [rbp-140h] BYREF
  TaskRequest Request_1; // [rsp+90h] [rbp-130h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask; // [rsp+A0h] [rbp-120h]
  TaskRequest Request_0; // [rsp+B0h] [rbp-110h]
  TaskRequest Request; // [rsp+C0h] [rbp-100h]
  std::_List_iterator<TaskMonster> it; // [rsp+D0h] [rbp-F0h] BYREF
  std::_List_iterator<TaskMonster> v76; // [rsp+E0h] [rbp-E0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+F0h] [rbp-D0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v78; // [rsp+100h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v79; // [rsp+110h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v80; // [rsp+120h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v81; // [rsp+130h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v82; // [rsp+140h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v83; // [rsp+150h] [rbp-70h] BYREF
  bool update; // [rsp+15Bh] [rbp-65h]
  int32_t Count; // [rsp+15Ch] [rbp-64h]
  CfgTask *pCfgTask; // [rsp+160h] [rbp-60h]
  int32_t Count_0; // [rsp+16Ch] [rbp-54h]
  CfgTask *pCfgTask_0; // [rsp+170h] [rbp-50h]
  int32_t Count_1; // [rsp+17Ch] [rbp-44h]
  CActivityMap *pActivityMap; // [rsp+180h] [rbp-40h]
  CFamilyWar *pFamilyWar; // [rsp+188h] [rbp-38h]
  int32_t Count_2; // [rsp+194h] [rbp-2Ch]
  CfgTask *pCfgTask_1; // [rsp+198h] [rbp-28h]
  int32_t Count_3; // [rsp+1A4h] [rbp-1Ch]
  int32_t Count_4; // [rsp+1A8h] [rbp-18h]
  int32_t Count_5; // [rsp+1ACh] [rbp-14h]

  update = 0;
  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    v76._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &v76) )
      break;
    if ( std::_List_iterator<TaskMonster>::operator->(&it)->condition == Condition )
    {
      switch ( std::_List_iterator<TaskMonster>::operator->(&it)->condition )
      {
        case 7:
        case 8:
        case 9:
        case 0xA:
        case 0x11:
        case 0x15:
        case 0x18:
        case 0x19:
        case 0x1B:
        case 0x22:
          param1 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param1;
          if ( param1 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
          {
            tid = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
            Request = ChrTask::GetTaskCfgRequest(this, tid);
            if ( Request.param1 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
              update = 1;
            goto LABEL_7;
          }
          break;
        case 0x12:
          v11 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_0._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v11->tid)._M_node;
          __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_0, &__x)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_0)->second.state == 3 )
          {
            v12 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param1;
            Equip = Player::GetEquip(this->m_player);
            Count = CExtEquip::HaveLevelEquipCount(Equip, v12);
            v14 = std::_List_iterator<TaskMonster>::operator->(&it);
            if ( v14->request.param2 != Count )
            {
              v15 = std::_List_iterator<TaskMonster>::operator->(&it);
              v15->request.param2 = Count;
              v16 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
              v17 = Answer::Singleton<CfgData>::instance();
              pCfgTask = CfgData::getTask(v17, v16);
              if ( pCfgTask )
              {
                v18 = std::_List_iterator<TaskMonster>::operator->(&it);
                if ( v18->request.param2 >= pCfgTask->request.param2 )
                {
                  v19 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                  ChrTask::setTaskCanSubmit(this, v19, 0);
                }
                update = 1;
              }
            }
          }
          break;
        case 0x13:
          v20 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_1._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v20->tid)._M_node;
          v78._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_1, &v78)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_1)->second.state == 3 )
          {
            v21 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param1;
            v22 = Player::GetEquip(this->m_player);
            Count_0 = CExtEquip::HaveStarEquipCount(v22, v21);
            v23 = std::_List_iterator<TaskMonster>::operator->(&it);
            if ( v23->request.param2 != Count_0 )
            {
              v24 = std::_List_iterator<TaskMonster>::operator->(&it);
              v24->request.param2 = Count_0;
              v25 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
              v26 = Answer::Singleton<CfgData>::instance();
              pCfgTask_0 = CfgData::getTask(v26, v25);
              if ( pCfgTask_0 )
              {
                v27 = std::_List_iterator<TaskMonster>::operator->(&it);
                if ( v27->request.param2 >= pCfgTask_0->request.param2 )
                {
                  v28 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                  ChrTask::setTaskCanSubmit(this, v28, 0);
                }
                update = 1;
              }
            }
          }
          break;
        case 0x16:
          v29 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_2._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v29->tid)._M_node;
          v79._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_2, &v79)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_2)->second.state == 3 )
          {
            PlayerVip = Player::GetPlayerVip(this->m_player);
            Count_1 = CVip::GetVipType(PlayerVip);
            v31 = std::_List_iterator<TaskMonster>::operator->(&it);
            if ( v31->request.param2 != Count_1 )
            {
              v32 = std::_List_iterator<TaskMonster>::operator->(&it);
              v32->request.param2 = Count_1;
              param2 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
              if ( param2 >= std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 )
              {
                v34 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                ChrTask::setTaskCanSubmit(this, v34, 0);
              }
              update = 1;
            }
          }
          break;
        case 0x1C:
          v35 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_3._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v35->tid)._M_node;
          v80._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_3, &v80)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_3)->second.state == 3 )
          {
            Map = StaticObj::getMap(this->m_player);
            v37 = Map
                ? (CActivityMap *)__dynamic_cast(
                                    Map,
                                    (const struct __class_type_info *)&`typeinfo for'Map,
                                    (const struct __class_type_info *)&`typeinfo for'CActivityMap,
                                    0)
                : 0LL;
            pActivityMap = v37;
            if ( v37 )
            {
              Activity = CActivityMap::GetActivity(pActivityMap);
              v39 = Activity
                  ? (CFamilyWar *)__dynamic_cast(
                                    Activity,
                                    (const struct __class_type_info *)&`typeinfo for'CActivity,
                                    (const struct __class_type_info *)&`typeinfo for'CFamilyWar,
                                    0)
                  : 0LL;
              pFamilyWar = v39;
              if ( v39 )
              {
                FamilyId = Player::getFamilyId(this->m_player);
                Count_2 = CFamilyWar::GetActivePillar(pFamilyWar, FamilyId);
                v41 = std::_List_iterator<TaskMonster>::operator->(&it);
                if ( v41->request.param2 != Count_2 )
                {
                  v42 = std::_List_iterator<TaskMonster>::operator->(&it);
                  v42->request.param2 = Count_2;
                  v43 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                  v44 = Answer::Singleton<CfgData>::instance();
                  pCfgTask_1 = CfgData::getTask(v44, v43);
                  if ( pCfgTask_1 )
                  {
                    v45 = std::_List_iterator<TaskMonster>::operator->(&it);
                    if ( v45->request.param2 >= pCfgTask_1->request.param1 )
                    {
                      v46 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                      ChrTask::setTaskCanSubmit(this, v46, 0);
                    }
                    update = 1;
                  }
                }
              }
            }
          }
          break;
        case 0x1E:
        case 0x2B:
          if ( std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 == param )
          {
            v9 = std::_List_iterator<TaskMonster>::operator->(&it);
            itTask._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v9->tid)._M_node;
            v10 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
            Request_1 = ChrTask::GetTaskCfgRequest(this, v10);
            if ( Request_1.param2 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
              update = 1;
LABEL_7:
            v5 = std::_List_iterator<TaskMonster>::operator->(&it);
            ++v5->request.param2;
          }
          break;
        case 0x20:
        case 0x23:
        case 0x28:
        case 0x2A:
          v6 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param1;
          if ( v6 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
          {
            v7 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
            Request_0 = ChrTask::GetTaskCfgRequest(this, v7);
            if ( Request_0.param1 > std::_List_iterator<TaskMonster>::operator->(&it)->request.param2 )
              update = 1;
            v8 = std::_List_iterator<TaskMonster>::operator->(&it);
            v8->request.param2 += param;
          }
          break;
        case 0x25:
          v47 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_4._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v47->tid)._M_node;
          v81._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_4, &v81)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_4)->second.state == 3 )
          {
            Count_3 = Player::getRecord(this->m_player, 1148);
            v48 = std::_List_iterator<TaskMonster>::operator->(&it);
            if ( v48->request.param2 != Count_3 )
            {
              v49 = std::_List_iterator<TaskMonster>::operator->(&it);
              v49->request.param2 = Count_3;
              v50 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
              if ( v50 >= std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 )
              {
                v51 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                ChrTask::setTaskCanSubmit(this, v51, 0);
              }
              update = 1;
            }
          }
          break;
        case 0x26:
          v52 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_5._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v52->tid)._M_node;
          v82._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_5, &v82)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_5)->second.state == 3 )
          {
            Count_4 = Player::getRecord(this->m_player, 1147);
            v53 = std::_List_iterator<TaskMonster>::operator->(&it);
            if ( v53->request.param2 != Count_4 )
            {
              v54 = std::_List_iterator<TaskMonster>::operator->(&it);
              v54->request.param2 = Count_4;
              v55 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
              if ( v55 >= std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 )
              {
                v56 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                ChrTask::setTaskCanSubmit(this, v56, 0);
              }
              update = 1;
            }
          }
          break;
        case 0x27:
          v57 = std::_List_iterator<TaskMonster>::operator->(&it);
          itTask_6._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v57->tid)._M_node;
          v83._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&itTask_6, &v83)
            && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask_6)->second.state == 3 )
          {
            CharJueWei = Player::GetCharJueWei(this->m_player);
            Count_5 = CExtCharJueWei::GetJueWei(CharJueWei);
            v59 = std::_List_iterator<TaskMonster>::operator->(&it);
            if ( v59->request.param2 != Count_5 )
            {
              v60 = std::_List_iterator<TaskMonster>::operator->(&it);
              v60->request.param2 = Count_5;
              v61 = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
              if ( v61 >= std::_List_iterator<TaskMonster>::operator->(&it)->request.param1 )
              {
                v62 = std::_List_iterator<TaskMonster>::operator->(&it)->tid;
                ChrTask::setTaskCanSubmit(this, v62, 0);
              }
              update = 1;
            }
          }
          break;
        default:
          continue;
      }
    }
  }
  if ( update )
    ChrTask::sendTaskKilledMonster(this);
}


#####################################
void __cdecl ChrTask::updateTaskDrop(ChrTask *const this, int32_t tid, int32_t itemid)
{
  int32_t v4; // ebx
  CfgData *v5; // rax
  CExtCharBag *Bag; // rax
  int32_t tida; // [rsp+4h] [rbp-5Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-58h]
  MemChrBag item; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask; // [rsp+30h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+40h] [rbp-20h] BYREF
  CfgTask *pCfgTask; // [rsp+48h] [rbp-18h]

  thisa = this;
  tida = tid;
  if ( this->m_player )
  {
    itTask._M_node = std::map<int,MemChrTask>::find(&thisa->m_tasks, &tida)._M_node;
    __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&itTask, &__x)
      && std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask)->second.state == 3 )
    {
      v4 = tida;
      v5 = Answer::Singleton<CfgData>::instance();
      pCfgTask = CfgData::getTask(v5, v4);
      if ( pCfgTask
        && pCfgTask->condition == 2
        && pCfgTask->request.param1 == itemid
        && !Player::hasItem(
              thisa->m_player,
              pCfgTask->request.param1,
              pCfgTask->request.param2,
              pCfgTask->request.param3) )
      {
        *(_DWORD *)&item.itemClass = 1;
        *(_QWORD *)&item.itemCount = 1;
        *(_QWORD *)&item.endTime = 0;
        item.srcId = 0;
        item.itemId = itemid;
        Bag = Player::GetBag(thisa->m_player);
        CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::ICR_NONE);
      }
    }
  }
}


#####################################
void __cdecl ChrTask::cmdResetTrunkTask(ChrTask *const this, int32_t trunkTaskId)
{
  CfgData *v2; // rax
  MemChrTask *v3; // rax
  int32_t trunkTaskIda; // [rsp+4h] [rbp-5Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-58h]
  std::_List_iterator<TaskMonster> itTaskMonster; // [rsp+10h] [rbp-50h] BYREF
  TaskMonster taskMonster; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+40h] [rbp-20h] BYREF
  CfgTask *pCfgTask; // [rsp+48h] [rbp-18h]

  thisa = this;
  trunkTaskIda = trunkTaskId;
  v2 = Answer::Singleton<CfgData>::instance();
  pCfgTask = CfgData::getTask(v2, trunkTaskId);
  if ( pCfgTask && pCfgTask->type == 1 )
  {
    for ( itTaskMonster._M_node = std::list<TaskMonster>::begin(&thisa->m_taskMonsters)._M_node;
          ;
          std::_List_iterator<TaskMonster>::operator++(&itTaskMonster) )
    {
      __x._M_node = std::list<TaskMonster>::end(&thisa->m_taskMonsters)._M_node;
      if ( !std::_List_iterator<TaskMonster>::operator!=(&itTaskMonster, &__x) )
        break;
      if ( std::_List_iterator<TaskMonster>::operator->(&itTaskMonster)->tid == thisa->m_trunkTaskId )
      {
        std::list<TaskMonster>::erase(&thisa->m_taskMonsters, itTaskMonster);
        ChrTask::sendTaskKilledMonster(thisa);
        break;
      }
    }
    std::map<int,MemChrTask>::erase(&thisa->m_tasks, &thisa->m_trunkTaskId);
    v3 = std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &trunkTaskIda);
    v3->id = trunkTaskIda;
    std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &trunkTaskIda)->monster = 0;
    std::map<int,MemChrTask>::operator[](&thisa->m_tasks, &trunkTaskIda)->state = 3;
    thisa->m_trunkTaskId = trunkTaskIda;
    taskMonster.condition = 0;
    *(_QWORD *)&taskMonster.request.param1 = 0;
    taskMonster.request.param3 = 0;
    taskMonster.tid = trunkTaskIda;
    taskMonster.condition = pCfgTask->condition;
    taskMonster.request.param1 = pCfgTask->request.param1;
    std::list<TaskMonster>::push_back(&thisa->m_taskMonsters, &taskMonster);
    ChrTask::sendTaskList(thisa);
  }
}


#####################################
bool __cdecl ChrTask::isDoingTaskType(ChrTask *const this, int32_t type)
{
  int32_t id; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-20h] BYREF
  CfgTask *pCfg; // [rsp+28h] [rbp-18h]

  for ( it._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&it) )
  {
    __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it, &__x) )
      break;
    id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.id;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::getTask(v3, id);
    if ( pCfg && pCfg->type == type )
      return 1;
  }
  return 0;
}


#####################################
bool __cdecl ChrTask::isDoingTask(ChrTask *const this, int32_t nTaskId)
{
  int32_t nTaskIda; // [rsp+4h] [rbp-2Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nTaskIda = nTaskId;
  iter._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &nTaskIda)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  return !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&iter, &__x);
}


#####################################
int8_t __cdecl ChrTask::GetTaskState(ChrTask *const this, int32_t nTaskId)
{
  int v2; // eax
  int32_t nTaskIda; // [rsp+4h] [rbp-2Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  nTaskIda = nTaskId;
  iter._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &nTaskIda)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator==(&iter, &__x) )
    LOBYTE(v2) = 0;
  else
    return std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&iter)->second.state;
  return v2;
}


#####################################
bool __cdecl ChrTask::setTaskCanSubmit(ChrTask *const this, int32_t tid, bool setCondition)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  int32_t tida; // [rsp+4h] [rbp-3Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  tida = tid;
  it._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &tida)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it, &__x)
    || std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state != 3 )
  {
    return 0;
  }
  std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.state = 4;
  if ( setCondition )
    ChrTask::setMonster(thisa, tida);
  ChrTask::sendTaskList(thisa);
  ConnId = Player::getConnId(thisa->m_player);
  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2774u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, tida);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(thisa->m_player);
    v8 = Player::getConnId(thisa->m_player);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v9, v8, GateIndex, packet);
  }
  return 1;
}


#####################################
void __cdecl ChrTask::sendTaskList(ChrTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  std::pair<const int,MemChrTask> *v4; // rax
  std::pair<const int,MemChrTask> *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_player )
  {
    ConnId = Player::getConnId(this->m_player);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x276Eu);
    if ( packet )
    {
      v3 = std::map<int,MemChrTask>::size(&this->m_tasks);
      Answer::NetPacket::writeInt32(packet, v3);
      for ( it._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&it) )
      {
        __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it, &__x) )
          break;
        v4 = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second.id);
        v5 = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v5->second.state);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_player);
      v8 = Player::getConnId(this->m_player);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
      ChrTask::sendTaskKilledMonster(this);
    }
  }
}


#####################################
void __cdecl ChrTask::sendTaskKilledMonster(ChrTask *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  TaskMonster *v4; // rax
  TaskMonster *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_List_iterator<TaskMonster> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_player )
  {
    ConnId = Player::getConnId(this->m_player);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2772u);
    if ( packet )
    {
      v3 = std::list<TaskMonster>::size(&this->m_taskMonsters);
      Answer::NetPacket::writeInt32(packet, v3);
      for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
            ;
            std::_List_iterator<TaskMonster>::operator++(&it) )
      {
        __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
        if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
          break;
        v4 = std::_List_iterator<TaskMonster>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->tid);
        v5 = std::_List_iterator<TaskMonster>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->request.param2);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_player);
      v8 = Player::getConnId(this->m_player);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl ChrTask::saveToDB(ChrTask *const this, Answer::NetPacket *packet)
{
  TaskMonster *v2; // rax
  std::pair<const int,MemChrTask> *v3; // rbx
  int32_t v4; // edx
  int32_t id; // edx
  int32_t state; // edx
  int32_t monster; // edx
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it_0; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask; // [rsp+20h] [rbp-60h] BYREF
  std::_List_iterator<TaskMonster> it; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<TaskMonster> v11; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+50h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v13; // [rsp+60h] [rbp-20h] BYREF

  if ( packet )
  {
    for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
          ;
          std::_List_iterator<TaskMonster>::operator++(&it) )
    {
      v11._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
      if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &v11) )
        break;
      v2 = std::_List_iterator<TaskMonster>::operator->(&it);
      itTask._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v2->tid)._M_node;
      __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&itTask, &__x) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask);
        v3->second.monster = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
      }
    }
    v4 = std::map<int,MemChrTask>::size(&this->m_tasks);
    Answer::NetPacket::writeInt32(packet, v4);
    for ( it_0._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&it_0) )
    {
      v13._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it_0, &v13) )
        break;
      id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it_0)->second.id;
      Answer::NetPacket::writeInt32(packet, id);
      state = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it_0)->second.state;
      Answer::NetPacket::writeInt32(packet, state);
      monster = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it_0)->second.monster;
      Answer::NetPacket::writeInt32(packet, monster);
    }
  }
}


#####################################
void __cdecl ChrTask::SaveDBData(ChrTask *const this, PlayerDBData *const dbData)
{
  TaskMonster *v2; // rax
  std::pair<const int,MemChrTask> *v3; // rbx
  size_t v4; // rax
  MemChrTask task; // [rsp+10h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it_0; // [rsp+20h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > itTask; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<TaskMonster> it; // [rsp+40h] [rbp-50h] BYREF
  std::_List_iterator<TaskMonster> v9; // [rsp+50h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+60h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v11; // [rsp+70h] [rbp-20h] BYREF

  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    v9._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &v9) )
      break;
    v2 = std::_List_iterator<TaskMonster>::operator->(&it);
    itTask._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &v2->tid)._M_node;
    __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&itTask, &__x) )
    {
      v3 = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&itTask);
      v3->second.monster = std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
    }
  }
  v4 = std::map<int,MemChrTask>::size(&this->m_tasks);
  std::vector<MemChrTask>::reserve(&dbData->taskData.taskVt, v4);
  for ( it_0._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&it_0) )
  {
    v11._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it_0, &v11) )
      break;
    *(_QWORD *)&task.id = 0;
    task.monster = 0;
    task.id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it_0)->second.id;
    task.state = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it_0)->second.state;
    task.monster = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it_0)->second.monster;
    std::vector<MemChrTask>::push_back(&dbData->taskData.taskVt, &task);
  }
}


#####################################
int32_t __cdecl ChrTask::getMonster(ChrTask *const this, int32_t tid)
{
  std::_List_iterator<TaskMonster> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+20h] [rbp-10h] BYREF

  for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
        ;
        std::_List_iterator<TaskMonster>::operator++(&it) )
  {
    __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
      break;
    if ( std::_List_iterator<TaskMonster>::operator->(&it)->tid == tid )
      return std::_List_iterator<TaskMonster>::operator->(&it)->request.param2;
  }
  return 0;
}


#####################################
void __cdecl ChrTask::setMonster(ChrTask *const this, int32_t tid)
{
  CfgData *v2; // rax
  unsigned int condition; // eax
  __int64 v4; // rax
  TaskMonster *v5; // rax
  std::_List_iterator<TaskMonster> it; // [rsp+10h] [rbp-60h] BYREF
  TaskMonster taskMonster; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<TaskMonster> __x; // [rsp+40h] [rbp-30h] BYREF
  CfgTask *cfgTask; // [rsp+50h] [rbp-20h]
  int32_t nCount; // [rsp+5Ch] [rbp-14h]

  v2 = Answer::Singleton<CfgData>::instance();
  cfgTask = CfgData::getTask(v2, tid);
  if ( cfgTask )
  {
    nCount = 0;
    condition = cfgTask->condition;
    if ( condition <= 0x2B )
    {
      v4 = 1LL << condition;
      if ( (v4 & 0xD0A220780LL) != 0 )
      {
        nCount = cfgTask->request.param1;
      }
      else
      {
        if ( (v4 & 0x81040012830LL) == 0 )
          return;
        nCount = cfgTask->request.param2;
      }
      if ( nCount > 0 )
      {
        for ( it._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
              ;
              std::_List_iterator<TaskMonster>::operator++(&it) )
        {
          __x._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
          if ( !std::_List_iterator<TaskMonster>::operator!=(&it, &__x) )
            break;
          if ( std::_List_iterator<TaskMonster>::operator->(&it)->tid == tid )
          {
            v5 = std::_List_iterator<TaskMonster>::operator->(&it);
            v5->request.param2 = nCount;
            return;
          }
        }
        taskMonster.condition = 0;
        *(_QWORD *)&taskMonster.request.param1 = 0;
        taskMonster.request.param3 = 0;
        taskMonster.tid = tid;
        taskMonster.condition = cfgTask->condition;
        taskMonster.request.param1 = cfgTask->request.param1;
        taskMonster.request.param2 = nCount;
        std::list<TaskMonster>::push_back(&this->m_taskMonsters, &taskMonster);
      }
    }
  }
}


#####################################
void __cdecl ChrTask::sendTaskReceived(ChrTask *const this, int32_t tid)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_player )
  {
    ConnId = Player::getConnId(this->m_player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2773u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, tid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_player);
      v6 = Player::getConnId(this->m_player);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl ChrTask::sendTaskSubmitted(ChrTask *const this, int32_t tid, int32_t exp)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_player )
  {
    ConnId = Player::getConnId(this->m_player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2775u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, tid);
      Answer::NetPacket::writeInt32(packet, exp);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_player);
      v7 = Player::getConnId(this->m_player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl ChrTask::sendTaskGiveUped(ChrTask *const this, int32_t tid)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_player )
  {
    ConnId = Player::getConnId(this->m_player);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2776u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, tid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_player);
      v6 = Player::getConnId(this->m_player);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl ChrTask::GetTypeTask(ChrTask *const this, int8_t Type)
{
  int32_t id; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-20h] BYREF
  CfgTask *cfgTask; // [rsp+28h] [rbp-18h]

  for ( it._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&it) )
  {
    __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it, &__x) )
      break;
    id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.id;
    v3 = Answer::Singleton<CfgData>::instance();
    cfgTask = CfgData::getTask(v3, id);
    if ( cfgTask && cfgTask->type == Type )
      return std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.id;
  }
  return 0;
}


#####################################
int8_t __cdecl ChrTask::GetTaskType(ChrTask *const this, int32_t TaskId)
{
  int32_t id; // ebx
  CfgData *v3; // rax
  int v4; // eax
  int32_t TaskIda; // [rsp+4h] [rbp-3Ch] BYREF
  ChrTask *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+20h] [rbp-20h] BYREF
  CfgTask *cfgTask; // [rsp+28h] [rbp-18h]

  thisa = this;
  TaskIda = TaskId;
  it._M_node = std::map<int,MemChrTask>::find(&this->m_tasks, &TaskIda)._M_node;
  __x._M_node = std::map<int,MemChrTask>::end(&thisa->m_tasks)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&it, &__x)
    && (id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&it)->second.id,
        v3 = Answer::Singleton<CfgData>::instance(),
        (cfgTask = CfgData::getTask(v3, id)) != 0) )
  {
    return cfgTask->type;
  }
  else
  {
    LOBYTE(v4) = 0;
  }
  return v4;
}


#####################################
void __cdecl ChrTask::CleanTaskType(ChrTask *const this, int8_t nType)
{
  int32_t id; // ebx
  CfgData *v3; // rax
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v4; // rax
  int8_t v5; // bl
  DBService *v6; // rax
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > v7; // rax
  int8_t ConnId; // bl
  DBService *v9; // rax
  int32_t tid; // ebx
  CfgData *v11; // rax
  std::_List_iterator<TaskMonster> v12; // rax
  std::_List_iterator<TaskMonster> iter_0; // [rsp+10h] [rbp-A0h] BYREF
  LogTask logTask_0; // [rsp+20h] [rbp-90h] BYREF
  LogTask logTask; // [rsp+40h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > iter; // [rsp+60h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MemChrTask> > __x; // [rsp+70h] [rbp-40h] BYREF
  std::_List_iterator<TaskMonster> v18; // [rsp+80h] [rbp-30h] BYREF
  bool update; // [rsp+8Fh] [rbp-21h]
  CfgTask *pCfgTask; // [rsp+90h] [rbp-20h]
  CfgTask *pCfgTask_0; // [rsp+98h] [rbp-18h]

  update = 0;
  iter._M_node = std::map<int,MemChrTask>::begin(&this->m_tasks)._M_node;
  while ( 1 )
  {
    __x._M_node = std::map<int,MemChrTask>::end(&this->m_tasks)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator!=(&iter, &__x) )
      break;
    id = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator->(&iter)->second.id;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfgTask = CfgData::getTask(v3, id);
    if ( pCfgTask )
    {
      if ( pCfgTask->type == nType )
      {
        v7._M_node = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&iter, 0)._M_node;
        std::map<int,MemChrTask>::erase(&this->m_tasks, v7);
        memset(&logTask_0, 0, sizeof(logTask_0));
        logTask_0.cid = Player::getCid(this->m_player);
        logTask_0.tid = pCfgTask->id;
        logTask_0.type = pCfgTask->type;
        logTask_0.time = Unit::getNow(this->m_player);
        logTask_0.state = 2;
        ConnId = Player::getConnId(this->m_player);
        v9 = Answer::Singleton<DBService>::instance();
        DBService::updateTaskInfo(v9, ConnId, &logTask_0);
        update = 1;
      }
      else
      {
        std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&iter);
      }
    }
    else
    {
      v4._M_node = std::_Rb_tree_iterator<std::pair<int const,MemChrTask>>::operator++(&iter, 0)._M_node;
      std::map<int,MemChrTask>::erase(&this->m_tasks, v4);
      update = 1;
      memset(&logTask, 0, sizeof(logTask));
      logTask.cid = Player::getCid(this->m_player);
      logTask.tid = pCfgTask->id;
      logTask.type = pCfgTask->type;
      logTask.time = Unit::getNow(this->m_player);
      logTask.state = 2;
      v5 = Player::getConnId(this->m_player);
      v6 = Answer::Singleton<DBService>::instance();
      DBService::updateTaskInfo(v6, v5, &logTask);
    }
  }
  iter_0._M_node = std::list<TaskMonster>::begin(&this->m_taskMonsters)._M_node;
  while ( 1 )
  {
    v18._M_node = std::list<TaskMonster>::end(&this->m_taskMonsters)._M_node;
    if ( !std::_List_iterator<TaskMonster>::operator!=(&iter_0, &v18) )
      break;
    tid = std::_List_iterator<TaskMonster>::operator->(&iter_0)->tid;
    v11 = Answer::Singleton<CfgData>::instance();
    pCfgTask_0 = CfgData::getTask(v11, tid);
    if ( !pCfgTask_0 || pCfgTask_0->type == nType )
    {
      v12._M_node = std::_List_iterator<TaskMonster>::operator++(&iter_0, 0)._M_node;
      std::list<TaskMonster>::erase(&this->m_taskMonsters, v12);
      update = 1;
    }
    else
    {
      std::_List_iterator<TaskMonster>::operator++(&iter_0);
    }
  }
  if ( update )
  {
    ChrTask::sendTaskList(this);
    ChrTask::sendTaskKilledMonster(this);
  }
}


#####################################
void __cdecl ChrTask::checkTaskDrop(ChrTask *const this, int32_t nTid, int32_t nCount)
{
  CfgData *v3; // rax
  TaskDrop *v4; // rax
  int32_t nParam1; // ebx
  Param2 *v6; // rax
  TaskDrop *v7; // rax
  size_t v8; // rax
  int32_t *v9; // rax
  DropItem dropItem; // [rsp+40h] [rbp-130h] BYREF
  Position centosPos; // [rsp+70h] [rbp-100h] BYREF
  CDropItemGroup dropItemGroup; // [rsp+80h] [rbp-F0h] BYREF
  std::_List_const_iterator<int> it; // [rsp+90h] [rbp-E0h] BYREF
  std::_List_iterator<Param2> i; // [rsp+A0h] [rbp-D0h] BYREF
  std::_List_iterator<TaskDrop> iter; // [rsp+B0h] [rbp-C0h] BYREF
  DropItemVector dropItems; // [rsp+C0h] [rbp-B0h] BYREF
  Int32List groupIds; // [rsp+E0h] [rbp-90h] BYREF
  std::_List_iterator<TaskDrop> v19; // [rsp+F0h] [rbp-80h] BYREF
  std::_List_iterator<Param2> __x; // [rsp+100h] [rbp-70h] BYREF
  std::_List_iterator<int> v21; // [rsp+110h] [rbp-60h] BYREF
  std::_List_const_iterator<int> v22; // [rsp+120h] [rbp-50h] BYREF
  std::_List_iterator<int> v23; // [rsp+130h] [rbp-40h] BYREF
  std::string dropper; // [rsp+140h] [rbp-30h] BYREF
  char v25; // [rsp+14Fh] [rbp-21h] BYREF
  Map *pMap; // [rsp+150h] [rbp-20h]
  CfgTask *cfgTask; // [rsp+158h] [rbp-18h]

  if ( this->m_player )
  {
    pMap = StaticObj::getMap(this->m_player);
    if ( pMap )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      cfgTask = CfgData::getTask(v3, nTid);
      if ( cfgTask )
      {
        if ( !std::list<TaskDrop>::empty(&cfgTask->drop_list) )
        {
          std::list<int>::list(&groupIds);
          for ( iter._M_node = std::list<TaskDrop>::begin(&cfgTask->drop_list)._M_node;
                ;
                std::_List_iterator<TaskDrop>::operator++(&iter) )
          {
            v19._M_node = std::list<TaskDrop>::end(&cfgTask->drop_list)._M_node;
            if ( !std::_List_iterator<TaskDrop>::operator!=(&iter, &v19) )
              break;
            if ( std::_List_iterator<TaskDrop>::operator->(&iter)->nCount == nCount )
            {
              v4 = std::_List_iterator<TaskDrop>::operator->(&iter);
              for ( i._M_node = std::list<Param2>::begin(&v4->lstJobGroup)._M_node;
                    ;
                    std::_List_iterator<Param2>::operator++(&i) )
              {
                v7 = std::_List_iterator<TaskDrop>::operator->(&iter);
                __x._M_node = std::list<Param2>::end(&v7->lstJobGroup)._M_node;
                if ( !std::_List_iterator<Param2>::operator!=(&i, &__x) )
                  break;
                nParam1 = std::_List_iterator<Param2>::operator->(&i)->nParam1;
                if ( nParam1 == Player::getJob(this->m_player) )
                {
                  v6 = std::_List_iterator<Param2>::operator->(&i);
                  std::list<int>::push_back(&groupIds, &v6->nParam2);
                }
              }
            }
          }
          std::vector<DropItem>::vector(&dropItems);
          v8 = std::list<int>::size(&groupIds);
          std::vector<DropItem>::reserve(&dropItems, v8);
          v21._M_node = std::list<int>::begin(&groupIds)._M_node;
          std::_List_const_iterator<int>::_List_const_iterator(&it, &v21);
          while ( 1 )
          {
            v23._M_node = std::list<int>::end(&groupIds)._M_node;
            std::_List_const_iterator<int>::_List_const_iterator(&v22, &v23);
            if ( !std::_List_const_iterator<int>::operator!=(&it, &v22) )
              break;
            v9 = (int32_t *)std::_List_const_iterator<int>::operator*(&it);
            ChrTask::dropItemFromGroup(&dropItem, this, *v9);
            if ( dropItem.itemId > 0 && dropItem.itemClass > 0 )
              std::vector<DropItem>::push_back(&dropItems, &dropItem);
            std::_List_const_iterator<int>::operator++(&it);
          }
          if ( !std::vector<DropItem>::empty(&dropItems) )
          {
            CDropItemGroup::CDropItemGroup(&dropItemGroup);
            centosPos = StaticObj::getCurrentTile(this->m_player);
            std::allocator<char>::allocator(&v25);
            std::string::string(&dropper, &unk_8F1800);
            CDropItemGroup::init(
              &dropItemGroup,
              0,
              pMap,
              &centosPos,
              this->m_player,
              2,
              0,
              &dropItems,
              &dropper,
              0,
              0,
              0);
            std::string::~string(&dropper);
            std::allocator<char>::~allocator(&v25);
            Map::addDropItemGroup(pMap, &dropItemGroup);
            CDropItemGroup::~CDropItemGroup(&dropItemGroup);
          }
          std::vector<DropItem>::~vector(&dropItems);
          std::list<int>::~list(&groupIds);
        }
      }
    }
  }
}


#####################################
float __cdecl ChrTask::GetTaskRewardRate(ChrTask *const this, TaskType type)
{
  CMoneyRewardTask *CMoneyRewardTask; // rax

  if ( !this->m_player )
    return 1.0;
  if ( type != TaskType::TT_PDBF )
    return 1.0;
  CMoneyRewardTask = Player::GetCMoneyRewardTask(this->m_player);
  return CMoneyRewardTask::GetPdbfRewardRate(CMoneyRewardTask);
}


