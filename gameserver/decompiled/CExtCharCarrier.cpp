// Decompiled methods for class: CExtCharCarrier
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CExtCharCarrier::~CExtCharCarrier(CExtCharCarrier *const this)
{
  CExtCharCarrier::~CExtCharCarrier(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharCarrier::OnCleanUp(CExtCharCarrier *const this)
{
  CObjCarrier *m_pCarrier; // rbx
  CPoolManager *v2; // rax

  if ( this->m_pCarrier )
  {
    m_pCarrier = this->m_pCarrier;
    v2 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<CObjCarrier>(v2, m_pCarrier);
    this->m_pCarrier = 0;
  }
}


#####################################
void __cdecl CExtCharCarrier::OnUpdate(CExtCharCarrier *const this, int64_t curTick)
{
  if ( this->m_pCarrier )
    Unit::update(this->m_pCarrier);
}


#####################################
void __cdecl CExtCharCarrier::GetInterestsProtocol(CExtCharCarrier *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 921;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CExtCharCarrier::DispatchNetDatas(
        CExtCharCarrier *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 921 )
    return CExtCharCarrier::onLeaveCarrier(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharCarrier::onLeaveCarrier(CExtCharCarrier *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket || !this->m_pCarrier )
    return 10002;
  CExtCharCarrier::LeaveCarrier(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharCarrier::GetCarrierId(CExtCharCarrier *const this)
{
  if ( this->m_pCarrier )
    return CObjCarrier::GetCarrierId(this->m_pCarrier);
  else
    return 0;
}


#####################################
void __cdecl CExtCharCarrier::EnterCarrier(CExtCharCarrier *const this, int32_t nId)
{
  CfgData *v2; // rax
  const CfgCarrierTable *CarrierTable; // rax
  CPoolManager *v4; // rax

  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    CarrierTable = CfgData::GetCarrierTable(v2);
    if ( CfgCarrierTable::GetCarrier(CarrierTable, nId) )
    {
      if ( this->m_pCarrier )
        CExtCharCarrier::LeaveCarrier(this);
      v4 = Answer::Singleton<CPoolManager>::instance();
      this->m_pCarrier = CPoolManager::pop<CObjCarrier>(v4);
      if ( this->m_pCarrier )
      {
        CObjCarrier::Init(this->m_pCarrier, this->m_pPlayer, nId);
        Unit::clearDebuff(this->m_pPlayer, 0);
        Unit::setNeedSyncSelf(this->m_pPlayer);
        Player::SetNeedSyncAround(this->m_pPlayer);
      }
    }
  }
}


#####################################
void __cdecl CExtCharCarrier::LeaveCarrier(CExtCharCarrier *const this)
{
  CObjCarrier *m_pCarrier; // rbx
  CPoolManager *v2; // rax

  if ( this->m_pPlayer )
  {
    if ( this->m_pCarrier )
    {
      m_pCarrier = this->m_pCarrier;
      v2 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<CObjCarrier>(v2, m_pCarrier);
      this->m_pCarrier = 0;
      Unit::setNeedSyncSelf(this->m_pPlayer);
      Player::SetNeedSyncAround(this->m_pPlayer);
    }
  }
}


#####################################
bool __cdecl CExtCharCarrier::HaveSkill(CExtCharCarrier *const this, int32_t nSkillId)
{
  return this->m_pPlayer && this->m_pCarrier && CObjCarrier::HaveSkill(this->m_pCarrier, nSkillId);
}


