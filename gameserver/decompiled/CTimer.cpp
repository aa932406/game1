// Decompiled methods for class: CTimer
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CTimer::~CTimer(CTimer *const this)
{
  CTimer::~CTimer(this);
  operator delete(this);
}


#####################################
void __cdecl CTimer::run(CTimer *const this)
{
  CActivityManager *v1; // rax
  CGMBackstate *v2; // rax
  CWorldBoss *v3; // rax
  tm NowTm; // [rsp+10h] [rbp-40h] BYREF
  int64_t CurTick; // [rsp+48h] [rbp-8h]

  this->m_bRunning = 1;
  while ( this->m_bRunning )
  {
    CurTick = CTimer::GetTick(this);
    CTimer::GetLocalNow(&NowTm, this);
    CTimer::updateTime(this);
    CTimer::checkNewMinute(this, &NowTm);
    v1 = Answer::Singleton<CActivityManager>::instance();
    CActivityManager::OnUpdate(v1, CurTick);
    v2 = Answer::Singleton<CGMBackstate>::instance();
    CGMBackstate::OnUpdate(v2);
    v3 = Answer::Singleton<CWorldBoss>::instance();
    CWorldBoss::Update(v3, CurTick);
    Answer::DayTime::sleep(10);
  }
}


#####################################
void __cdecl CTimer::Start(CTimer *const this)
{
  CTimer *v1; // rbx
  tm v2; // [rsp+0h] [rbp-60h] BYREF
  CTimer *thisa; // [rsp+48h] [rbp-18h]

  thisa = this;
  this->m_bRunning = 1;
  v1 = thisa;
  CTimer::GetLocalNow(&v2, thisa);
  v1->m_tmLastLocalNow = v2;
  thisa->m_nextAnnoucement = 0;
  Answer::Thread::start(thisa);
}


#####################################
void __cdecl CTimer::Stop(CTimer *const this)
{
  this->m_bRunning = 0;
  Answer::Thread::join(this);
}


#####################################
int64_t __cdecl CTimer::GetTick(CTimer *const this)
{
  int64_t m_nTick; // rbx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_timeLock);
  m_nTick = this->m_nTick;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_nTick;
}


#####################################
int32_t __cdecl CTimer::GetNow(CTimer *const this)
{
  int32_t m_nNow; // ebx
  Answer::MutexGuard lock; // [rsp+10h] [rbp-20h] BYREF

  Answer::MutexGuard::MutexGuard(&lock, &this->m_timeLock);
  m_nNow = this->m_nNow;
  Answer::MutexGuard::~MutexGuard(&lock);
  return m_nNow;
}


#####################################
bool __cdecl CTimer::BetweenDate(CTimer *const this, int32_t begin_date, int32_t end_date)
{
  int date; // [rsp+1Ch] [rbp-4h]

  date = 10000 * this->m_tmLocalNow.tm_year
       + 100 * (this->m_tmLocalNow.tm_mon + 1)
       + 19000000
       + this->m_tmLocalNow.tm_mday;
  return date >= begin_date && date <= end_date;
}


#####################################
void __cdecl CTimer::updateTime(CTimer *const this)
{
  GameService *v1; // rax
  tm localNow; // [rsp+10h] [rbp-60h] BYREF
  Answer::MutexGuard lock; // [rsp+50h] [rbp-20h] BYREF
  int64_t nTick; // [rsp+60h] [rbp-10h]
  int32_t nNow; // [rsp+6Ch] [rbp-4h]

  nTick = Answer::DayTime::tick();
  nNow = Answer::DayTime::now();
  Answer::DayTime::localnow(&localNow);
  if ( CTimer::isRightLocalNow(this, &localNow) )
  {
    if ( this->m_tmLocalNow.tm_sec != localNow.tm_sec && !(localNow.tm_sec % 15) )
    {
      v1 = Answer::Singleton<GameService>::instance();
      GameService::onUpdatePay(v1);
    }
    Answer::MutexGuard::MutexGuard(&lock, &this->m_timeLock);
    this->m_nTick = nTick;
    this->m_nNow = nNow;
    this->m_tmLocalNow = localNow;
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
bool __cdecl CTimer::isRightLocalNow(CTimer *const this, const tm *const localnow)
{
  if ( localnow->tm_year < this->m_tmLocalNow.tm_year )
    return 0;
  if ( localnow->tm_year != this->m_tmLocalNow.tm_year )
    return 1;
  if ( localnow->tm_yday < this->m_tmLocalNow.tm_yday )
    return 0;
  if ( localnow->tm_yday != this->m_tmLocalNow.tm_yday )
    return 1;
  if ( localnow->tm_hour < this->m_tmLocalNow.tm_hour )
    return 0;
  if ( localnow->tm_hour != this->m_tmLocalNow.tm_hour )
    return 1;
  if ( localnow->tm_min < this->m_tmLocalNow.tm_min )
    return 0;
  return localnow->tm_min != this->m_tmLocalNow.tm_min || localnow->tm_sec >= this->m_tmLocalNow.tm_sec;
}


#####################################
void __cdecl CTimer::checkNewMinute(CTimer *const this, const tm *const localnow)
{
  if ( localnow->tm_yday != this->m_tmLastLocalNow.tm_yday )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_INFO,
      "CTimer::onDaySwitch() nowday=%d-%d %d:%d:%d, lastDay=%d-%d %d:%d:%d\n",
      localnow->tm_year,
      localnow->tm_yday,
      localnow->tm_hour,
      localnow->tm_min,
      localnow->tm_sec,
      this->m_tmLastLocalNow.tm_year,
      this->m_tmLastLocalNow.tm_yday,
      this->m_tmLastLocalNow.tm_hour,
      this->m_tmLastLocalNow.tm_min,
      this->m_tmLastLocalNow.tm_sec);
    CTimer::onDaySwitch(this);
  }
  if ( localnow->tm_min != this->m_tmLastLocalNow.tm_min )
    CTimer::onNewMinute(this, localnow->tm_min + 60 * localnow->tm_hour);
  if ( localnow->tm_wday != this->m_tmLastLocalNow.tm_wday )
    CTimer::onWeekSwitch(this);
  this->m_tmLastLocalNow = *localnow;
}


#####################################
void __cdecl CTimer::onNewMinute(CTimer *const this, int32_t nMinute)
{
  GameService *v2; // rax
  CUniteServer *v3; // rax
  CFestivalDoubleEleven *v4; // rax
  CFestivalActivity *v5; // rax
  CZongHeYunYingHD *v6; // rax
  CKiaFuRecharge *v7; // rax
  COpenBeta *v8; // rax
  COutLinkFestival *v9; // rax
  CGuiGuDaoRen *v10; // rax

  v2 = Answer::Singleton<GameService>::instance();
  GameService::onNewMinuteCome(v2, nMinute);
  v3 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::OnNewMinute(v3, nMinute);
  v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::OnNewMinute(v4, nMinute);
  v5 = Answer::Singleton<CFestivalActivity>::instance();
  CFestivalActivity::OnNewMinute(v5, nMinute);
  v6 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::OnNewMinute(v6, nMinute);
  v7 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::OnNewMinute(v7, nMinute);
  v8 = Answer::Singleton<COpenBeta>::instance();
  COpenBeta::OnNewMinute(v8, nMinute);
  v9 = Answer::Singleton<COutLinkFestival>::instance();
  COutLinkFestival::OnNewMinute(v9, nMinute);
  v10 = Answer::Singleton<CGuiGuDaoRen>::instance();
  CGuiGuDaoRen::OnNewMinute(v10, nMinute);
}


#####################################
void __cdecl CTimer::onDaySwitch(CTimer *const this)
{
  GameService *v1; // rax
  CUniteServer *v2; // rax
  CFestivalDoubleEleven *v3; // rax
  CFestivalActivity *v4; // rax
  CZongHeYunYingHD *v5; // rax
  CKiaFuRecharge *v6; // rax
  COpenBeta *v7; // rax
  COutLinkFestival *v8; // rax
  CGuiGuDaoRen *v9; // rax

  this->m_nWeekDay = (this->m_tmLocalNow.tm_wday + 6) % 7 + 1;
  v1 = Answer::Singleton<GameService>::instance();
  GameService::OnDaySwitch(v1);
  v2 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::OnDaySwitch(v2);
  v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
  CFestivalDoubleEleven::OnDaySwitch(v3);
  v4 = Answer::Singleton<CFestivalActivity>::instance();
  CFestivalActivity::OnDaySwitch(v4);
  v5 = Answer::Singleton<CZongHeYunYingHD>::instance();
  CZongHeYunYingHD::OnDaySwitch(v5);
  v6 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::OnDaySwitch(v6);
  v7 = Answer::Singleton<COpenBeta>::instance();
  COpenBeta::OnDaySwitch(v7);
  v8 = Answer::Singleton<COutLinkFestival>::instance();
  COutLinkFestival::OnDaySwitch(v8);
  v9 = Answer::Singleton<CGuiGuDaoRen>::instance();
  CGuiGuDaoRen::OnDaySwitch(v9);
  if ( !Answer::CheckKey::CheckKeyValid() )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "KEY\n");
    exit(1);
  }
}


