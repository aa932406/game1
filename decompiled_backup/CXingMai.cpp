// Decompiled methods for class: CXingMai
// Source: gameserver.cc
// Total methods: 10

#####################################
void __cdecl CXingMai::~CXingMai(CXingMai *const this)
{
  CXingMai::~CXingMai(this);
  operator delete(this);
}


#####################################
void __cdecl CXingMai::GetInterestsProtocol(CXingMai *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 300;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 301;
  std::list<unsigned short>::push_back(procList, &v3);
}


#####################################
int32_t __cdecl CXingMai::DispatchNetDatas(CXingMai *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 300 )
    return CXingMai::OnXingMaiLevelUp(this, inPacket);
  if ( nProcId == 301 )
    return CXingMai::OnXingMaiSlotActive(this, inPacket);
  return 10002;
}


#####################################
int32_t __cdecl CXingMai::OnXingMaiLevelUp(CXingMai *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CfgData *v4; // rax
  int32_t PlayerLevel; // ebx
  int8_t ConnId; // bl
  GameService *v7; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v10; // bl
  GameService *v11; // rax
  ChrTask *Task; // rax
  int8_t v13; // bl
  DBService *v14; // rax
  important_system_log stu; // [rsp+10h] [rbp-A0h] BYREF
  std::string val; // [rsp+50h] [rbp-60h] BYREF
  _BYTE v18[16]; // [rsp+60h] [rbp-50h] BYREF
  _BYTE v19[20]; // [rsp+70h] [rbp-40h] BYREF
  int32_t CurLevel; // [rsp+84h] [rbp-2Ch]
  XingMaiCfg *CurCfg; // [rsp+88h] [rbp-28h]
  XingMaiCfg *NextCfg; // [rsp+90h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CurLevel = Player::getRecord(this->m_pPlayer, 1147);
  v3 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetXingMaiCfg(v3, CurLevel);
  v4 = Answer::Singleton<CfgData>::instance();
  NextCfg = CfgData::GetXingMaiCfg(v4, CurLevel + 1);
  if ( !CurCfg || !NextCfg )
    return 10002;
  PlayerLevel = NextCfg->PlayerLevel;
  if ( PlayerLevel > (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
    return 10002;
  if ( CurCfg->NeedBossScore <= 0 )
    return 10002;
  if ( Player::DecCurrency(
         this->m_pPlayer,
         CURRENCY_TYPE::CURRENCY_BOSS_SCORE,
         CurCfg->NeedBossScore,
         CURRENCY_CHANGE_REASON::SCR_XING_MAI_LEVEL_UP,
         0) )
  {
    Player::updateRecord(this->m_pPlayer, 1147, CurLevel + 1);
    Player::RecalcAttr(this->m_pPlayer);
    if ( NextCfg->GongGaoId > 0 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( !packet )
        return 10002;
      Answer::NetPacket::writeInt32(packet, NextCfg->GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, CurLevel + 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v10 = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v11, v10, packet);
    }
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::updateTaskCount(Task, 38, 0);
    important_system_log::important_system_log(&stu);
    stu.log_Sid = Player::getSid(this->m_pPlayer);
    stu.log_time = Unit::getNow(this->m_pPlayer);
    Player::GetPassport((Player *const)v18);
    std::string::operator=(&stu.passport, v18);
    std::string::~string(v18);
    stu.cid = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)v19);
    std::string::operator=(&stu.name, v19);
    std::string::~string(v19);
    stu.up_time = Unit::getNow(this->m_pPlayer);
    stu.sys_name = 3;
    stu.oper_id = 1;
    stu.level = CurLevel + 1;
    v13 = Player::getConnId(this->m_pPlayer);
    v14 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v14, v13, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
    v2 = 0;
    important_system_log::~important_system_log(&stu);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl CXingMai::OnXingMaiSlotActive(CXingMai *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtOperateLimit *OperateLimit; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  int8_t nIndex; // [rsp+17h] [rbp-29h]
  const CfgXingMaiSlot *pCfgSlot; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgSlot = CfgData::GetXingMaiSlot(v3, nIndex);
  if ( !pCfgSlot )
    return 10002;
  if ( CXingMai::isSlotActived(this, nIndex) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 1147) < pCfgSlot->nLevel )
    return 10002;
  if ( pCfgSlot->nScore <= 0 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_BOSS_SCORE,
          pCfgSlot->nScore,
          CURRENCY_CHANGE_REASON::SCR_XING_MAI_ACTIVE_SLOT,
          0) )
    return 10002;
  CXingMai::activeSlot(this, nIndex);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  return GameService::replySuccess(v8, ConnId, GateIndex, Proc, nIndex);
}


#####################################
void __cdecl CXingMai::AddCharAttr(CXingMai *const this)
{
  CfgData *v1; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  AddAttribute *v4; // rax
  std::_List_iterator<AddAttribute> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t CurLevel; // [rsp+34h] [rbp-1Ch]
  XingMaiCfg *CurCfg; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    CurLevel = Player::getRecord(this->m_pPlayer, 1147);
    v1 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetXingMaiCfg(v1, CurLevel);
    if ( CurCfg )
    {
      for ( it._M_node = std::list<AddAttribute>::begin(&CurCfg->AttrList)._M_node;
            ;
            std::_List_iterator<AddAttribute>::operator++(&it, 0) )
      {
        __x._M_node = std::list<AddAttribute>::end(&CurCfg->AttrList)._M_node;
        if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
          break;
        m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
        v3 = std::_List_iterator<AddAttribute>::operator->(&it);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v3->m_nAddAttrType, m_nAddAttrValue);
        if ( std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrType == 45 )
        {
          v4 = std::_List_iterator<AddAttribute>::operator->(&it);
          Player::AddBeiGongAttr(this->m_pPlayer, 4, v4->m_nAddAttrValue);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CXingMai::GetMaxBossScore(CXingMai *const this)
{
  CfgData *v1; // rax
  int32_t CurLevel; // [rsp+14h] [rbp-Ch]
  XingMaiCfg *CurCfg; // [rsp+18h] [rbp-8h]

  CurLevel = Player::getRecord(this->m_pPlayer, 1147);
  v1 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetXingMaiCfg(v1, CurLevel);
  if ( CurCfg )
    return CurCfg->BossScoreLimit;
  else
    return 0;
}


#####################################
bool __cdecl CXingMai::IsXingMaiSlotActived(const CXingMai *const this, int8_t nEquipSlot)
{
  int8_t XingMaiIndex; // dl

  if ( !isXingMaiSlot(nEquipSlot) )
    return 0;
  XingMaiIndex = CXingMai::getXingMaiIndex(this, nEquipSlot);
  return CXingMai::isSlotActived(this, XingMaiIndex);
}


#####################################
void __cdecl CXingMai::activeSlot(CXingMai *const this, int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v3; // rax
  int nState; // [rsp+1Ch] [rbp-14h]

  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nState = (1 << nIndex) | CExtOperateLimit::GetLimitCount(OperateLimit, 1157);
  v3 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v3, 1157, nState);
}


#####################################
bool __cdecl CXingMai::isSlotActived(const CXingMai *const this, int8_t nIndex)
{
  CExtOperateLimit *OperateLimit; // rax

  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  return (CExtOperateLimit::GetLimitCount(OperateLimit, 1157) >> nIndex) & 1;
}


