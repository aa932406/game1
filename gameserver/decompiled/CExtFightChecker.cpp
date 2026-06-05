// Decompiled methods for class: CExtFightChecker
// Source: gameserver.cc
// Total methods: 9

#####################################
void __cdecl CExtFightChecker::~CExtFightChecker(CExtFightChecker *const this)
{
  CExtFightChecker::~CExtFightChecker(this);
  operator delete(this);
}


#####################################
void __cdecl CExtFightChecker::OnCleanUp(CExtFightChecker *const this)
{
  this->m_bIsInFight = 0;
  this->m_IsBuleName = 0;
  this->m_bIsInPvP = 0;
  this->m_nFightTick = 0;
  this->m_nBuleNameTick = 0;
  this->m_nPvPTick = 0;
}


#####################################
void __cdecl CExtFightChecker::OnUpdate(CExtFightChecker *const this, int64_t curTick)
{
  CExtFightChecker::CheckInFight(this, curTick);
}


#####################################
int8_t __cdecl CExtFightChecker::GetFightState(const CExtFightChecker *const this)
{
  return this->m_bIsInFight;
}


#####################################
void __cdecl CExtFightChecker::SetInPvP(CExtFightChecker *const this, int64_t nCurTick)
{
  if ( CExtFightChecker::IsBuleName(this) )
    this->m_nBuleNameTick = nCurTick;
  this->m_nPvPTick = nCurTick;
}


#####################################
void __cdecl CExtFightChecker::CheckInFight(CExtFightChecker *const this, int64_t nCurTick)
{
  if ( nCurTick - this->m_nFightTick <= 15000 )
  {
    if ( !this->m_bIsInFight )
      CExtFightChecker::OnEnterFight(this);
  }
  else if ( this->m_bIsInFight )
  {
    CExtFightChecker::OnLeaveFight(this);
    this->m_nBuleNameTick = nCurTick;
  }
  if ( nCurTick - this->m_nPvPTick <= 15000 )
  {
    if ( !this->m_bIsInPvP )
      CExtFightChecker::enterPvP(this);
  }
  else if ( this->m_bIsInPvP )
  {
    CExtFightChecker::leavePvP(this);
  }
  if ( !this->m_bIsInPvP && nCurTick - this->m_nBuleNameTick > 15000 && CExtFightChecker::IsBuleName(this) )
    CExtFightChecker::ChangeBuleName(this, 0);
}


#####################################
void __cdecl CExtFightChecker::OnLeaveFight(CExtFightChecker *const this)
{
  this->m_bIsInFight = 0;
  CExtFightChecker::UpdateFightState(this);
}


#####################################
void __cdecl CExtFightChecker::OnEnterFight(CExtFightChecker *const this)
{
  this->m_bIsInFight = 1;
  CExtFightChecker::UpdateFightState(this);
}


#####################################
void __cdecl CExtFightChecker::ChangeBuleName(CExtFightChecker *const this, bool bFlag)
{
  if ( this->m_pPlayer )
  {
    if ( this->m_IsBuleName != bFlag )
    {
      this->m_IsBuleName = bFlag;
      Unit::setNeedSyncSelf(this->m_pPlayer);
      Player::SetNeedSyncAround(this->m_pPlayer);
    }
    this->m_nBuleNameTick = Unit::getTick(this->m_pPlayer);
  }
}


