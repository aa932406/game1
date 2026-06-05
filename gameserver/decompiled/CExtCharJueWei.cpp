// Decompiled methods for class: CExtCharJueWei
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CExtCharJueWei::~CExtCharJueWei(CExtCharJueWei *const this)
{
  CExtCharJueWei::~CExtCharJueWei(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharJueWei::GetInterestsProtocol(CExtCharJueWei *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 666;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 667;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CExtCharJueWei::DispatchNetDatas(
        CExtCharJueWei *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 666 )
    return CExtCharJueWei::onRequestJueWeiInfo(this, inPacket);
  if ( nProcId == 667 )
    return CExtCharJueWei::onAskJueWeiLevelUp(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CExtCharJueWei::onRequestJueWeiInfo(CExtCharJueWei *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  CExtCharJueWei::sendJueWeiInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharJueWei::onAskJueWeiLevelUp(CExtCharJueWei *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t m_nJueWei; // ebx
  CfgData *v4; // rax
  const CfgJueWeiTable *JueWeiTable; // rax
  int32_t nNeedLevel; // ebx
  int32_t v7; // ebx
  CfgData *v8; // rax
  const CfgJueWeiTable *v9; // rax
  ChrTask *Task; // rax
  Player *m_pPlayer; // rbx
  CKaiFuHuoDong *v12; // rax
  DBService *v13; // rax
  CSevenDayTask *CSevenDayTask; // rax
  important_system_log stu; // [rsp+10h] [rbp-80h] BYREF
  _BYTE v17[16]; // [rsp+50h] [rbp-40h] BYREF
  _BYTE v18[16]; // [rsp+60h] [rbp-30h] BYREF
  const CfgJueWei *pCfgJueWei; // [rsp+70h] [rbp-20h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  m_nJueWei = this->m_nJueWei;
  v4 = Answer::Singleton<CfgData>::instance();
  JueWeiTable = CfgData::GetJueWeiTable(v4);
  pCfgJueWei = CfgJueWeiTable::GetJueWei(JueWeiTable, m_nJueWei);
  if ( !pCfgJueWei )
    return 10002;
  nNeedLevel = pCfgJueWei->nNeedLevel;
  if ( nNeedLevel > (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
    return 10002;
  v7 = this->m_nJueWei + 1;
  v8 = Answer::Singleton<CfgData>::instance();
  v9 = CfgData::GetJueWeiTable(v8);
  if ( !CfgJueWeiTable::GetJueWei(v9, v7) )
    return 10002;
  if ( pCfgJueWei->nNeedViGour <= 0 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_VIGOUR,
          pCfgJueWei->nNeedViGour,
          CURRENCY_CHANGE_REASON::MCR_DONATION_JUE_WEI,
          0) )
    return 10002;
  Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_JUE_WEI, ++this->m_nJueWei);
  CExtCharJueWei::GongGao(this);
  CExtCharJueWei::sendJueWeiInfo(this);
  Player::setSyncStatusFlag(this->m_pPlayer);
  Player::RecalcAttr(this->m_pPlayer);
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::updateTaskCount(Task, 39, 0);
  m_pPlayer = this->m_pPlayer;
  v12 = Answer::Singleton<CKaiFuHuoDong>::instance();
  CKaiFuHuoDong::SendKaiFuHuoDongIcon(v12, m_pPlayer);
  important_system_log::important_system_log(&stu);
  stu.log_Sid = Player::getSid(this->m_pPlayer);
  stu.log_time = Unit::getNow(this->m_pPlayer);
  Player::GetPassport((Player *const)v17);
  std::string::operator=(&stu.passport, v17);
  std::string::~string(v17);
  stu.cid = Player::getCid(this->m_pPlayer);
  Player::getName((const Player *const)v18);
  std::string::operator=(&stu.name, v18);
  std::string::~string(v18);
  stu.up_time = Unit::getNow(this->m_pPlayer);
  stu.sys_name = 9;
  stu.oper_id = 1;
  stu.level = this->m_nJueWei;
  LOBYTE(m_pPlayer) = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<DBService>::instance();
  DBService::AddPlatformLog(v13, (int8_t)m_pPlayer, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
  LODWORD(m_pPlayer) = this->m_nJueWei;
  CSevenDayTask = Player::GetCSevenDayTask(this->m_pPlayer);
  CSevenDayTask::UpdateTaskState(CSevenDayTask, 4, (int32_t)m_pPlayer, 1);
  v2 = 0;
  important_system_log::~important_system_log(&stu);
  return v2;
}


#####################################
void __cdecl CExtCharJueWei::GongGao(CExtCharJueWei *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v5; // bl
  GameService *v6; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 400);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, this->m_nJueWei);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v5 = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v6, v5, packet);
  }
}


#####################################
void __cdecl CExtCharJueWei::AddCharAttr(CExtCharJueWei *const this)
{
  int32_t m_nJueWei; // ebx
  CfgData *v2; // rax
  const CfgJueWeiTable *JueWeiTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v5; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > it; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  const CfgJueWei *pCfgJueWei; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    m_nJueWei = this->m_nJueWei;
    v2 = Answer::Singleton<CfgData>::instance();
    JueWeiTable = CfgData::GetJueWeiTable(v2);
    pCfgJueWei = CfgJueWeiTable::GetJueWei(JueWeiTable, m_nJueWei);
    if ( pCfgJueWei )
    {
      for ( it._M_current = std::vector<AttrAddon>::begin(&pCfgJueWei->vAttr)._M_current;
            ;
            __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&it, 0) )
      {
        __rhs._M_current = std::vector<AttrAddon>::end(&pCfgJueWei->vAttr)._M_current;
        if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&it, &__rhs) )
          break;
        addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&it)->addon;
        v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&it);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
      }
    }
  }
}


#####################################
void __cdecl CExtCharJueWei::sendJueWeiInfo(CExtCharJueWei *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CB5u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, this->m_nJueWei);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v6, v5, GateIndex, packet);
    }
  }
}


