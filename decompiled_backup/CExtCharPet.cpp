// Decompiled methods for class: CExtCharPet
// Source: gameserver.cc
// Total methods: 39

#####################################
void __cdecl CExtCharPet::~CExtCharPet(CExtCharPet *const this)
{
  CExtCharPet::~CExtCharPet(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharPet::OnCleanUp(CExtCharPet *const this)
{
  CObjPet *m_pFightPet; // rbx
  GameService *v2; // rax
  CObjPet *v3; // rbx
  CPoolManager *v4; // rax

  this->m_nStar = 0;
  this->m_HuanHua = 0;
  this->m_nLastTick = 0;
  if ( this->m_pFightPet )
  {
    CObjPet::LeaveMap(this->m_pFightPet);
    m_pFightPet = this->m_pFightPet;
    v2 = Answer::Singleton<GameService>::instance();
    GameService::removePet(v2, m_pFightPet);
    v3 = this->m_pFightPet;
    v4 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<CObjPet>(v4, v3);
    this->m_pFightPet = 0;
  }
  CExtCharPet::clearSummonPet(this);
}


#####################################
void __cdecl CExtCharPet::OnLoadFromDB(CExtCharPet *const this, const PlayerDBData *const dbData)
{
  CPoolManager *v2; // rax
  CExtEquip *Equip; // rax
  CObjPet *m_pFightPet; // rbx
  GameService *v5; // rax

  this->m_nStar = dbData->m_CharPets.petData.nStar;
  this->m_HuanHua = dbData->m_CharPets.petData.nHuanHua;
  if ( this->m_nStar > 0 )
  {
    if ( !this->m_HuanHua )
      this->m_HuanHua = this->m_nStar;
    v2 = Answer::Singleton<CPoolManager>::instance();
    this->m_pFightPet = CPoolManager::pop<CObjPet>(v2);
    if ( this->m_pFightPet )
    {
      CObjPet::SetOwner(this->m_pFightPet, this->m_pPlayer);
      CObjPet::OnLoadFromDB(this->m_pFightPet, &dbData->m_CharPets.petData, this->m_nStar);
      if ( CObjPet::GetState(this->m_pFightPet) == PET_STATE::PS_FIGHTING )
      {
        CObjPet::SetSatandPlace(this->m_pFightPet, Direction::UP_RIGHT);
        CObjPet::EnterMap(this->m_pFightPet);
      }
      else if ( CObjPet::GetState(this->m_pFightPet) == PET_STATE::PS_FITTING )
      {
        Equip = Player::GetEquip(this->m_pPlayer);
        CExtEquip::CheckGongMingSuitBuff(Equip);
      }
      m_pFightPet = this->m_pFightPet;
      v5 = Answer::Singleton<GameService>::instance();
      GameService::addPet(v5, m_pFightPet);
    }
  }
}


#####################################
void __cdecl CExtCharPet::OnSaveToDB(CExtCharPet *const this, PlayerDBData *const dbData)
{
  if ( this->m_pFightPet )
  {
    dbData->m_CharPets.petData.nStar = this->m_nStar;
    dbData->m_CharPets.petData.nHuanHua = this->m_HuanHua;
    CObjPet::OnSaveToDB(this->m_pFightPet, &dbData->m_CharPets.petData);
  }
}


#####################################
void __cdecl CExtCharPet::OnUpdate(CExtCharPet *const this, int64_t curTick)
{
  int32_t i; // [rsp+14h] [rbp-Ch]
  CObjPet *pPet; // [rsp+18h] [rbp-8h]

  if ( this->m_pFightPet )
    Unit::update(this->m_pFightPet);
  for ( i = 0; i <= 3; ++i )
  {
    pPet = (CObjPet *)*((_QWORD *)&this->m_lSummons._M_impl + i + 2);
    if ( pPet )
      Unit::update(pPet);
  }
}


#####################################
void __cdecl CExtCharPet::GetInterestsProtocol(CExtCharPet *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-16h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-14h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-12h] BYREF
  unsigned __int16 v5; // [rsp+20h] [rbp-10h] BYREF
  unsigned __int16 v6; // [rsp+22h] [rbp-Eh] BYREF
  unsigned __int16 v7; // [rsp+24h] [rbp-Ch] BYREF
  unsigned __int16 v8; // [rsp+26h] [rbp-Ah] BYREF
  unsigned __int16 v9; // [rsp+28h] [rbp-8h] BYREF
  unsigned __int16 v10; // [rsp+2Ah] [rbp-6h] BYREF
  unsigned __int16 v11; // [rsp+2Ch] [rbp-4h] BYREF
  unsigned __int16 v12; // [rsp+2Eh] [rbp-2h] BYREF

  __x = 730;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 731;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 732;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 733;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 734;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 736;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 737;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 738;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 739;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 740;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 750;
  std::list<unsigned short>::push_back(procList, &v12);
}


#####################################
int32_t __cdecl CExtCharPet::DispatchNetDatas(CExtCharPet *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x2DAu:
      result = CExtCharPet::onFight(this, inPacket);
      break;
    case 0x2DBu:
      result = CExtCharPet::onRest(this, inPacket);
      break;
    case 0x2DCu:
      result = CExtCharPet::onUpStar(this, inPacket);
      break;
    case 0x2DDu:
      result = CExtCharPet::onDressEquip(this, inPacket);
      break;
    case 0x2DEu:
      result = CExtCharPet::onUnDressEquip(this, inPacket);
      break;
    case 0x2E2u:
      result = CExtCharPet::onChangeName(this, inPacket);
      break;
    case 0x2E3u:
      result = CExtCharPet::onChangeAi(this, inPacket);
      break;
    case 0x2E4u:
      result = CExtCharPet::onPetHuanHua(this, inPacket);
      break;
    case 0x2EEu:
      result = CExtCharPet::onFitting(this, inPacket);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtCharPet::onFight(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  if ( !CExtCharPet::Fight(this) )
    return 10002;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
bool __cdecl CExtCharPet::Fight(CExtCharPet *const this)
{
  CExtEquip *Equip; // rax
  Map *pMap; // [rsp+18h] [rbp-8h]

  if ( !CObjPet::AliveFlag(this->m_pFightPet) )
    return 0;
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( pMap && (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 22))(pMap) != 1 )
    return 0;
  if ( CObjPet::IsRest(this->m_pFightPet) )
  {
    CObjPet::SetSatandPlace(this->m_pFightPet, Direction::UP_RIGHT);
    CObjPet::Fighting(this->m_pFightPet);
    CObjPet::EnterMap(this->m_pFightPet);
    Player::recalcAttr(this->m_pPlayer, 0, 0);
  }
  else
  {
    if ( !CObjPet::IsFitting(this->m_pFightPet) )
      return 0;
    CObjPet::SetSatandPlace(this->m_pFightPet, Direction::UP_RIGHT);
    CObjPet::Fighting(this->m_pFightPet);
    CObjPet::EnterMap(this->m_pFightPet);
    Player::recalcAttr(this->m_pPlayer, 0, 0);
    Equip = Player::GetEquip(this->m_pPlayer);
    CExtEquip::CheckGongMingSuitBuff(Equip);
    Player::SetNeedSyncAround(this->m_pPlayer);
  }
  return 1;
}


#####################################
int32_t __cdecl CExtCharPet::onRest(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  CExtEquip *Equip; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  if ( CObjPet::IsFighting(this->m_pFightPet) )
  {
    CObjPet::LeaveMap(this->m_pFightPet);
    CObjPet::Rest(this->m_pFightPet);
    Player::recalcAttr(this->m_pPlayer, 0, 0);
  }
  else
  {
    if ( !CObjPet::IsFitting(this->m_pFightPet) )
      return 10002;
    CObjPet::Rest(this->m_pFightPet);
    Equip = Player::GetEquip(this->m_pPlayer);
    CExtEquip::CheckGongMingSuitBuff(Equip);
    Player::SetNeedSyncAround(this->m_pPlayer);
  }
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CExtCharPet::onRestPet(CExtCharPet *const this)
{
  CExtEquip *Equip; // rax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v4; // rax

  if ( this->m_pPlayer && this->m_pFightPet )
  {
    if ( CObjPet::IsFighting(this->m_pFightPet) )
    {
      CObjPet::LeaveMap(this->m_pFightPet);
      CObjPet::Rest(this->m_pFightPet);
      Player::recalcAttr(this->m_pPlayer, 0, 0);
    }
    else
    {
      if ( !CObjPet::IsFitting(this->m_pFightPet) )
        return;
      CObjPet::Rest(this->m_pFightPet);
      Equip = Player::GetEquip(this->m_pPlayer);
      CExtEquip::CheckGongMingSuitBuff(Equip);
      Player::SetNeedSyncAround(this->m_pPlayer);
    }
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v4, ConnId, GateIndex, 0x2DBu, 0);
  }
}


#####################################
int32_t __cdecl CExtCharPet::onFitting(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  CExtEquip *Equip; // rax
  CExtEquip *v4; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  Equip = Player::GetEquip(this->m_pPlayer);
  if ( CExtEquip::GetGongMingSuitId(Equip) <= 0 )
    return 10002;
  if ( CObjPet::IsFighting(this->m_pFightPet) )
  {
    CObjPet::LeaveMap(this->m_pFightPet);
    CObjPet::Fitting(this->m_pFightPet);
    Player::recalcAttr(this->m_pPlayer, 0, 0);
  }
  else
  {
    if ( !CObjPet::IsRest(this->m_pFightPet) )
      return 10002;
    CObjPet::Fitting(this->m_pFightPet);
  }
  v4 = Player::GetEquip(this->m_pPlayer);
  CExtEquip::CheckGongMingSuitBuff(v4);
  Player::SetNeedSyncAround(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
bool __cdecl CExtCharPet::IsFighting(const CExtCharPet *const this)
{
  return this->m_pFightPet && CObjPet::IsFighting(this->m_pFightPet);
}


#####################################
bool __cdecl CExtCharPet::IsFitting(const CExtCharPet *const this)
{
  return this->m_pFightPet && CObjPet::IsFitting(this->m_pFightPet);
}


#####################################
int32_t __cdecl CExtCharPet::onPetHuanHua(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  int32_t m_nStar; // ebx
  CfgData *v4; // rax
  const CfgPetTable *PetTable; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int32_t HuanHua; // [rsp+14h] [rbp-2Ch]

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  HuanHua = Answer::NetPacket::readInt32(inPacket);
  if ( this->m_HuanHua == HuanHua )
    return 10002;
  m_nStar = this->m_nStar;
  v4 = Answer::Singleton<CfgData>::instance();
  PetTable = CfgData::GetPetTable(v4);
  if ( !CfgPetTable::GetPetUpStar(PetTable, m_nStar) )
    return 10002;
  this->m_HuanHua = HuanHua;
  if ( CObjPet::GetState(this->m_pFightPet) == PET_STATE::PS_FIGHTING )
    CObjPet::SendPetStatus(this->m_pFightPet);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, HuanHua);
  return 0;
}


#####################################
int32_t __cdecl CExtCharPet::onUpStar(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t m_nStar; // ebx
  CfgData *v4; // rax
  const CfgPetTable *PetTable; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const CfgPetTable *v8; // rax
  CExtCurrency *v9; // rax
  int64_t MoneyBindAndNoBind; // rax
  CfgData *v11; // rax
  int64_t Currency; // rax
  ItemDataList *p_lCostItem; // r12
  CExtCharBag *Bag; // rax
  int64_t nCostMoney; // rbx
  CExtCurrency *v16; // rax
  int64_t nCostGold; // rbx
  CExtCurrency *v18; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v22; // rax
  GameService *v23; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v26; // rax
  ChrTask *Task; // rax
  int8_t v28; // bl
  DBService *v29; // rax
  important_system_log stu; // [rsp+10h] [rbp-C0h] BYREF
  Int32Vector vSlot; // [rsp+50h] [rbp-80h] BYREF
  std::string val; // [rsp+70h] [rbp-60h] BYREF
  _BYTE v34[16]; // [rsp+80h] [rbp-50h] BYREF
  char v35; // [rsp+90h] [rbp-40h] BYREF
  const CfgPetUpStar *pCfgUpStar; // [rsp+98h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+A8h] [rbp-28h]

  if ( this->m_pPlayer && inPacket && this->m_pFightPet )
  {
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    m_nStar = this->m_nStar;
    v4 = Answer::Singleton<CfgData>::instance();
    PetTable = CfgData::GetPetTable(v4);
    pCfgUpStar = CfgPetTable::GetPetUpStar(PetTable, m_nStar);
    if ( pCfgUpStar )
    {
      v6 = this->m_nStar + 1;
      v7 = Answer::Singleton<CfgData>::instance();
      v8 = CfgData::GetPetTable(v7);
      if ( CfgPetTable::GetPetUpStar(v8, v6) )
      {
        if ( pCfgUpStar->nCostMoney <= 0
          || (v9 = Player::GetCurrency(this->m_pPlayer),
              MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(v9),
              MoneyBindAndNoBind >= pCfgUpStar->nCostMoney) )
        {
          if ( pCfgUpStar->nCostGold > 0 )
          {
            v11 = Answer::Singleton<CfgData>::instance();
            if ( CfgData::getServerDiffDay(v11, SERVER_TYPE::SVT_NORMAL) + 1 <= 29 )
            {
              v2 = 10002;
              goto LABEL_35;
            }
            Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
            if ( Currency < pCfgUpStar->nCostGold )
            {
              v2 = 10002;
              goto LABEL_35;
            }
          }
          if ( std::list<ItemData>::size(&pCfgUpStar->lCostItem)
            && (p_lCostItem = &pCfgUpStar->lCostItem,
                Bag = Player::GetBag(this->m_pPlayer),
                !CExtCharBag::RemoveItem(Bag, &vSlot, p_lCostItem, ITEM_CHANGE_REASON::ICR_PET_UP_STAR)) )
          {
            v2 = 10002;
          }
          else if ( pCfgUpStar->nCostMoney > 0
                 && (nCostMoney = pCfgUpStar->nCostMoney,
                     v16 = Player::GetCurrency(this->m_pPlayer),
                     !CExtCurrency::DecMoneyAndNoBind(v16, nCostMoney, CURRENCY_CHANGE_REASON::MCR_PET_UPSTAR, 0)) )
          {
            v2 = 10002;
          }
          else
          {
            if ( pCfgUpStar->nCostGold <= 0
              || (nCostGold = pCfgUpStar->nCostGold,
                  v18 = Player::GetCurrency(this->m_pPlayer),
                  CExtCurrency::DecCurrency(
                    v18,
                    CURRENCY_TYPE::CURRENCY_GOLD,
                    nCostGold,
                    CURRENCY_CHANGE_REASON::MCR_PET_UPSTAR,
                    0)) )
            {
              if ( this->m_HuanHua == this->m_nStar )
                ++this->m_HuanHua;
              Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_PET_STAR, ++this->m_nStar);
              CObjPet::CheckSkillOpen(this->m_pFightPet, this->m_nStar);
              Player::recalcAttr(this->m_pPlayer, 0, 0);
              CObjPet::RecalAttr(this->m_pFightPet);
              Proc = Answer::NetPacket::getProc(inPacket);
              GateIndex = Player::getGateIndex(this->m_pPlayer);
              ConnId = Player::getConnId(this->m_pPlayer);
              v22 = Answer::Singleton<GameService>::instance();
              GameService::replySuccess(v22, ConnId, GateIndex, Proc, 0);
              CExtCharPet::sendPetInfo(this);
              if ( CObjPet::GetState(this->m_pFightPet) == PET_STATE::PS_FIGHTING )
                CObjPet::SendPetStatus(this->m_pFightPet);
              if ( pCfgUpStar->GongGaoId > 0 )
              {
                v23 = Answer::Singleton<GameService>::instance();
                packet = GameService::popNetpacket(v23, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
                if ( !packet )
                {
                  v2 = 10002;
                  goto LABEL_35;
                }
                Answer::NetPacket::writeInt32(packet, pCfgUpStar->GongGaoId);
                Player::getName((const Player *const)&val);
                Answer::NetPacket::writeUTF8(packet, &val);
                std::string::~string(&val);
                Cid = Player::getCid(this->m_pPlayer);
                Answer::NetPacket::writeInt64(packet, Cid);
                Answer::NetPacket::writeInt32(packet, this->m_nStar);
                WOffset = Answer::NetPacket::getWOffset(packet);
                Answer::NetPacket::setSize(packet, WOffset);
                v26 = Answer::Singleton<GameService>::instance();
                GameService::worldBroadcast(v26, 0, packet);
              }
              Task = Player::GetTask(this->m_pPlayer);
              ChrTask::updateTaskCount(Task, 37, 0);
              important_system_log::important_system_log(&stu);
              stu.log_Sid = Player::getSid(this->m_pPlayer);
              stu.log_time = Unit::getNow(this->m_pPlayer);
              Player::GetPassport((Player *const)v34);
              std::string::operator=(&stu.passport, v34);
              std::string::~string(v34);
              stu.cid = Player::getCid(this->m_pPlayer);
              Player::getName((const Player *const)&v35);
              std::string::operator=(&stu.name, &v35);
              std::string::~string(&v35);
              stu.up_time = Unit::getNow(this->m_pPlayer);
              stu.sys_name = 2;
              stu.oper_id = 1;
              stu.level = this->m_nStar;
              v28 = Player::getConnId(this->m_pPlayer);
              v29 = Answer::Singleton<DBService>::instance();
              DBService::AddPlatformLog(v29, v28, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
              v2 = 0;
              important_system_log::~important_system_log(&stu);
              goto LABEL_35;
            }
            v2 = 10002;
          }
        }
        else
        {
          v2 = 10002;
        }
      }
      else
      {
        v2 = 10002;
      }
    }
    else
    {
      v2 = 10002;
    }
LABEL_35:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 10002;
}


#####################################
void __cdecl CExtCharPet::SendPetStaus(CExtCharPet *const this)
{
  if ( this->m_pFightPet )
  {
    if ( CObjPet::GetState(this->m_pFightPet) == PET_STATE::PS_FIGHTING )
      CObjPet::SendPetStatus(this->m_pFightPet);
  }
}


#####################################
int32_t __cdecl CExtCharPet::onDressEquip(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CfgData *v4; // rax
  const CfgPetEquipTable *PetEquipTable; // rax
  CExtCharBag *v6; // rax
  CExtCharBag *v7; // rax
  int64_t v8; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  MemChrBag bagItem; // [rsp+10h] [rbp-60h] BYREF
  int32_t nBagSlot; // [rsp+3Ch] [rbp-34h]
  const CfgPetEquip *pCfgEquip; // [rsp+40h] [rbp-30h]
  int32_t nOldEquip; // [rsp+48h] [rbp-28h]
  int32_t nNewEquip; // [rsp+4Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  nBagSlot = Answer::NetPacket::readInt32(inPacket);
  Bag = Player::GetBag(this->m_pPlayer);
  bagItem = *CExtCharBag::GetSlotData(Bag, nBagSlot);
  if ( bagItem.itemClass != 7 )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  PetEquipTable = CfgData::GetPetEquipTable(v4);
  pCfgEquip = CfgPetEquipTable::GetEquip(PetEquipTable, bagItem.itemId);
  if ( !pCfgEquip )
    return 10002;
  if ( this->m_nStar < pCfgEquip->nNeedStar )
    return 10002;
  nOldEquip = CObjPet::GetEquip(this->m_pFightPet, pCfgEquip->nType);
  nNewEquip = bagItem.itemId;
  if ( nOldEquip <= 0 )
  {
    v7 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::CleanSlot(v7, nBagSlot, ITEM_CHANGE_REASON::ICR_PET_DRESS_EQUIP);
  }
  else
  {
    bagItem.itemId = nOldEquip;
    bagItem.bind = 1;
    v6 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::SetSlotData(v6, nBagSlot, &bagItem, ITEM_CHANGE_REASON::ICR_PET_DRESS_EQUIP, 0);
  }
  CObjPet::SetEquip(this->m_pFightPet, pCfgEquip->nType, nNewEquip);
  CExtCharPet::sendPetInfo(this);
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  v8 = nNewEquip;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v12 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v12, ConnId, GateIndex, Proc, v8);
  return 0;
}


#####################################
int32_t __cdecl CExtCharPet::onUnDressEquip(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  int64_t v4; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  MemChrBag addItem; // [rsp+10h] [rbp-50h] BYREF
  int8_t nSlot; // [rsp+3Bh] [rbp-25h]
  int32_t nEquipId; // [rsp+3Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  nSlot = Answer::NetPacket::readInt8(inPacket);
  nEquipId = CObjPet::GetEquip(this->m_pFightPet, nSlot);
  if ( nEquipId <= 0 )
    return 10002;
  *(_DWORD *)&addItem.itemClass = 7;
  *(_QWORD *)&addItem.itemCount = 0x100000001LL;
  *(_QWORD *)&addItem.endTime = 0;
  addItem.srcId = 0;
  addItem.itemId = nEquipId;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addItem, ITEM_CHANGE_REASON::ICR_PET_DRESS_EQUIP) )
    return 10002;
  CObjPet::SetEquip(this->m_pFightPet, nSlot, 0);
  CExtCharPet::sendPetInfo(this);
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  v4 = nSlot;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, v4);
  return 0;
}


#####################################
int32_t __cdecl CExtCharPet::onSkillUpLevel(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t nLevel; // r12d
  int32_t nId; // ebx
  CfgData *v5; // rax
  const CfgTalentTable *TalentTable; // rax
  ItemDataList *p_costItem; // r12
  CExtCharBag *Bag; // rax
  int64_t v9; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  Int32Vector vSlot; // [rsp+10h] [rbp-50h] BYREF
  int8_t nPos; // [rsp+2Fh] [rbp-31h]
  PetSkillInfo *pSkill; // [rsp+30h] [rbp-30h]
  const CfgTalent *pCfgTalent; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  nPos = Answer::NetPacket::readInt8(inPacket);
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  pSkill = CObjPet::GetSkill(this->m_pFightPet, nPos);
  if ( pSkill )
  {
    nLevel = pSkill->nLevel;
    nId = pSkill->nId;
    v5 = Answer::Singleton<CfgData>::instance();
    TalentTable = CfgData::GetTalentTable(v5);
    pCfgTalent = CfgTalentTable::GetTalent(TalentTable, nId, nLevel);
    if ( pCfgTalent )
    {
      if ( pSkill->nLevel < pCfgTalent->maxLevel )
      {
        p_costItem = &pCfgTalent->costItem;
        Bag = Player::GetBag(this->m_pPlayer);
        if ( !CExtCharBag::RemoveItem(Bag, &vSlot, p_costItem, ITEM_CHANGE_REASON::ICR_PET_UP_SKILL) )
        {
          v2 = 10002;
        }
        else
        {
          CObjPet::LearnSkill(this->m_pFightPet, nPos);
          if ( CObjPet::IsFighting(this->m_pFightPet) )
            Player::recalcAttr(this->m_pPlayer, 0, 0);
          v9 = nPos;
          Proc = Answer::NetPacket::getProc(inPacket);
          GateIndex = Player::getGateIndex(this->m_pPlayer);
          ConnId = Player::getConnId(this->m_pPlayer);
          v13 = Answer::Singleton<GameService>::instance();
          GameService::replySuccess(v13, ConnId, GateIndex, Proc, v9);
          CExtCharPet::sendPetInfo(this);
          v2 = 0;
        }
      }
      else
      {
        v2 = 10002;
      }
    }
    else
    {
      v2 = 10002;
    }
  }
  else
  {
    v2 = 10002;
  }
  std::vector<int>::~vector(&vSlot);
  return v2;
}


#####################################
int32_t __cdecl CExtCharPet::onChangeName(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  std::string strName; // [rsp+10h] [rbp-30h] BYREF

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&strName, (bool)inPacket);
  CObjPet::ChangeName(this->m_pFightPet, &strName);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  v2 = 0;
  std::string::~string(&strName);
  return v2;
}


#####################################
int32_t __cdecl CExtCharPet::onChangeAi(CExtCharPet *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  int8_t AiState; // [rsp+1Fh] [rbp-21h]

  if ( !this->m_pPlayer || !inPacket || !this->m_pFightPet )
    return 10002;
  AiState = Answer::NetPacket::readInt8(inPacket);
  if ( (unsigned __int8)AiState >= 2u )
    return 10002;
  CObjPet::ChangeAi(this->m_pFightPet, AiState);
  CExtCharPet::sendPetInfo(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CExtCharPet::OnLevelUp(CExtCharPet *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pFightPet )
  {
    CObjPet::OnLevelUp(this->m_pFightPet);
    CExtCharPet::sendPetInfo(this);
  }
  for ( i = 0; i <= 3; ++i )
  {
    if ( *((_QWORD *)&this->m_lSummons._M_impl + i + 2)
      && CObjPet::AliveFlag(*((const CObjPet *const *)&this->m_lSummons._M_impl + i + 2)) )
    {
      CObjPet::OnLevelUp(*((CObjPet *const *)&this->m_lSummons._M_impl + i + 2));
    }
  }
}


#####################################
bool __cdecl CExtCharPet::IsFunctionOpen(CExtCharPet *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 32) )
      return 1;
  }
  return result;
}


#####################################
void __cdecl CExtCharPet::OnInitPet(CExtCharPet *const this)
{
  Player *m_pPlayer; // rbx
  CPetManager *v2; // rax
  CObjPet *m_pFightPet; // rbx
  GameService *v4; // rax

  if ( this->m_pPlayer && !this->m_pFightPet )
  {
    this->m_nStar = 1;
    this->m_HuanHua = 1;
    m_pPlayer = this->m_pPlayer;
    v2 = Answer::Singleton<CPetManager>::instance();
    this->m_pFightPet = CPetManager::CreateNewPet(v2, 101, m_pPlayer);
    if ( this->m_pFightPet )
    {
      m_pFightPet = this->m_pFightPet;
      v4 = Answer::Singleton<GameService>::instance();
      GameService::addPet(v4, m_pFightPet);
      CObjPet::CheckSkillOpen(this->m_pFightPet, 1);
      CObjPet::RecalAttr(this->m_pFightPet);
      Player::recalcAttr(this->m_pPlayer, 0, 0);
      CExtCharPet::sendPetInfo(this);
      CExtCharPet::Fight(this);
    }
  }
}


#####################################
void __cdecl CExtCharPet::OnPlayerDie(CExtCharPet *const this)
{
  CExtEquip *Equip; // rax
  CExtCharSkill *CharSkill; // rax

  if ( this->m_pPlayer )
  {
    if ( this->m_pFightPet )
    {
      if ( CObjPet::IsFighting(this->m_pFightPet) )
      {
        CObjPet::LeaveMap(this->m_pFightPet);
        CObjPet::Rest(this->m_pFightPet);
        Player::recalcAttr(this->m_pPlayer, 0, 0);
        CExtCharPet::sendPetInfo(this);
      }
      else if ( CObjPet::IsFitting(this->m_pFightPet) )
      {
        CObjPet::Rest(this->m_pFightPet);
        Equip = Player::GetEquip(this->m_pPlayer);
        CExtEquip::CheckGongMingSuitBuff(Equip);
        CExtCharPet::sendPetInfo(this);
      }
    }
    if ( !std::list<CExtCharPet::SummonInfo>::empty(&this->m_lSummons) )
    {
      CExtCharPet::clearSummonPet(this);
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::CheckSummonBuff(CharSkill);
    }
  }
}


#####################################
void __cdecl CExtCharPet::clearSummonPet(CExtCharPet *const this)
{
  CExtCharPet::SummonInfo *v1; // rax
  GameService *v2; // rax
  CPoolManager *v3; // rax
  CExtCharPet::SummonInfo *v4; // rax
  std::_List_iterator<CObjPet*> j; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<CExtCharPet::SummonInfo> i_0; // [rsp+20h] [rbp-40h] BYREF
  std::_List_iterator<CExtCharPet::SummonInfo> v7; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<CObjPet*> __x; // [rsp+40h] [rbp-20h] BYREF
  int32_t i; // [rsp+54h] [rbp-Ch]
  CObjPet *pPet; // [rsp+58h] [rbp-8h]

  for ( i = 0; i <= 3; ++i )
  {
    if ( *((_QWORD *)&this->m_lSummons._M_impl + i + 2) )
      CObjPet::LeaveMap(*((CObjPet *const *)&this->m_lSummons._M_impl + i + 2));
  }
  bzero(this->m_vSummonPet, 0x20u);
  for ( i_0._M_node = std::list<CExtCharPet::SummonInfo>::begin(&this->m_lSummons)._M_node;
        ;
        std::_List_iterator<CExtCharPet::SummonInfo>::operator++(&i_0) )
  {
    v7._M_node = std::list<CExtCharPet::SummonInfo>::end(&this->m_lSummons)._M_node;
    if ( !std::_List_iterator<CExtCharPet::SummonInfo>::operator!=(&i_0, &v7) )
      break;
    v1 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&i_0);
    for ( j._M_node = std::list<CObjPet *>::begin(&v1->lPets)._M_node; ; std::_List_iterator<CObjPet *>::operator++(&j) )
    {
      v4 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&i_0);
      __x._M_node = std::list<CObjPet *>::end(&v4->lPets)._M_node;
      if ( !std::_List_iterator<CObjPet *>::operator!=(&j, &__x) )
        break;
      pPet = *std::_List_iterator<CObjPet *>::operator*(&j);
      if ( pPet )
      {
        v2 = Answer::Singleton<GameService>::instance();
        GameService::removePet(v2, pPet);
        v3 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<CObjPet>(v3, pPet);
      }
    }
  }
  std::list<CExtCharPet::SummonInfo>::clear(&this->m_lSummons);
}


#####################################
void __cdecl CExtCharPet::OnSummon(CExtCharPet *const this, int32_t nSkillId, const Position *const pos)
{
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  CExtCharPet::SummonInfo *v5; // rax
  CExtCharPet::SummonInfo *v6; // rax
  CExtCharPet::SummonInfo *v7; // rax
  CExtCharPet::SummonInfo *v8; // rax
  CExtCharPet::SummonInfo *v9; // rax
  CExtCharSkill *v10; // rax
  CPoolManager *v11; // rax
  CExtCharPet::SummonInfo *v12; // rax
  CObjPet *v13; // rbx
  GameService *v14; // rax
  CExtCharSkill *v15; // rax
  CPoolManager *v16; // rax
  CObjPet *v17; // rbx
  GameService *v18; // rax
  CExtCharSkill *CharSkill; // rax
  CObjPet *pPet_1; // [rsp+20h] [rbp-70h] BYREF
  CObjPet *pPet_0; // [rsp+28h] [rbp-68h] BYREF
  std::_List_iterator<CExtCharPet::SummonInfo> iter; // [rsp+30h] [rbp-60h] BYREF
  CExtCharPet::SummonInfo info; // [rsp+40h] [rbp-50h] BYREF
  CObjPet *pPet; // [rsp+58h] [rbp-38h] BYREF
  std::_List_iterator<CExtCharPet::SummonInfo> __x; // [rsp+60h] [rbp-30h] BYREF
  const CfgActiveSkill *pCfgSkill; // [rsp+70h] [rbp-20h]
  int32_t nPetSize; // [rsp+7Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v3);
    pCfgSkill = CfgSkillTable::GetActiveSkill(SkillTable, nSkillId);
    if ( pCfgSkill )
    {
      if ( pCfgSkill->summon_id > 0 && pCfgSkill->summon_limit > 0 )
      {
        for ( iter._M_node = std::list<CExtCharPet::SummonInfo>::begin(&this->m_lSummons)._M_node;
              ;
              std::_List_iterator<CExtCharPet::SummonInfo>::operator++(&iter) )
        {
          __x._M_node = std::list<CExtCharPet::SummonInfo>::end(&this->m_lSummons)._M_node;
          if ( !std::_List_iterator<CExtCharPet::SummonInfo>::operator!=(&iter, &__x) )
          {
            v16 = Answer::Singleton<CPoolManager>::instance();
            pPet = CPoolManager::pop<CObjPet>(v16);
            CObjPet::InitSummon(pPet, this->m_pPlayer, pCfgSkill->summon_id, nSkillId);
            CExtCharPet::addSummonPet(this, pPet);
            CObjPet::EnterMap(pPet, pos);
            v17 = pPet;
            v18 = Answer::Singleton<GameService>::instance();
            GameService::addPet(v18, v17);
            CharSkill = Player::GetCharSkill(this->m_pPlayer);
            CExtCharSkill::CheckSummonBuff(CharSkill);
            CExtCharPet::SummonInfo::SummonInfo(&info);
            info.nTalent = pCfgSkill->talent;
            std::list<CObjPet *>::push_back(&info.lPets, &pPet);
            std::list<CExtCharPet::SummonInfo>::push_back(&this->m_lSummons, &info);
            CExtCharPet::SummonInfo::~SummonInfo(&info);
            return;
          }
          v5 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&iter);
          if ( v5->nTalent == pCfgSkill->talent )
            break;
        }
        v6 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&iter);
        nPetSize = std::list<CObjPet *>::size(&v6->lPets);
        if ( pCfgSkill->summon_limit > nPetSize )
        {
          v11 = Answer::Singleton<CPoolManager>::instance();
          pPet_1 = CPoolManager::pop<CObjPet>(v11);
          CObjPet::InitSummon(pPet_1, this->m_pPlayer, pCfgSkill->summon_id, nSkillId);
          CExtCharPet::addSummonPet(this, pPet_1);
          CObjPet::EnterMap(pPet_1, pos);
          v12 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&iter);
          std::list<CObjPet *>::push_back(&v12->lPets, &pPet_1);
          v13 = pPet_1;
          v14 = Answer::Singleton<GameService>::instance();
          GameService::addPet(v14, v13);
          v15 = Player::GetCharSkill(this->m_pPlayer);
          CExtCharSkill::CheckSummonBuff(v15);
        }
        else
        {
          v7 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&iter);
          pPet_0 = *std::list<CObjPet *>::front(&v7->lPets);
          v8 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&iter);
          std::list<CObjPet *>::pop_front(&v8->lPets);
          CObjPet::LeaveMap(pPet_0);
          CObjPet::InitSummon(pPet_0, this->m_pPlayer, pCfgSkill->summon_id, nSkillId);
          CObjPet::EnterMap(pPet_0, pos);
          v9 = std::_List_iterator<CExtCharPet::SummonInfo>::operator->(&iter);
          std::list<CObjPet *>::push_back(&v9->lPets, &pPet_0);
          v10 = Player::GetCharSkill(this->m_pPlayer);
          CExtCharSkill::CheckSummonBuff(v10);
        }
      }
    }
  }
}


#####################################
bool __cdecl CExtCharPet::HaveSummonAlive(CExtCharPet *const this)
{
  int32_t i; // [rsp+14h] [rbp-Ch]
  CObjPet *pPet; // [rsp+18h] [rbp-8h]

  for ( i = 0; i <= 3; ++i )
  {
    pPet = (CObjPet *)*((_QWORD *)&this->m_lSummons._M_impl + i + 2);
    if ( pPet && CObjPet::AliveFlag(pPet) )
      return 1;
  }
  return 0;
}


#####################################
void __cdecl CExtCharPet::AddCharAttr(CExtCharPet *const this)
{
  int32_t m_nStar; // ebx
  CfgData *v2; // rax
  const CfgPetTable *PetTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v5; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  const CfgPetUpStar *pCfgUpStar; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    m_nStar = this->m_nStar;
    v2 = Answer::Singleton<CfgData>::instance();
    PetTable = CfgData::GetPetTable(v2);
    pCfgUpStar = CfgPetTable::GetPetUpStar(PetTable, m_nStar);
    if ( pCfgUpStar )
    {
      for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgUpStar->vAddPlayerAttr)._M_current;
            ;
            __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<AttrAddon>::end(&pCfgUpStar->vAddPlayerAttr)._M_current;
        if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
          break;
        addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
        v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
      }
    }
    if ( this->m_pFightPet )
      CObjPet::AddEquipAttr(this->m_pFightPet, this->m_pPlayer);
  }
}


#####################################
void __cdecl CExtCharPet::AddPetAttr(CExtCharPet *const this, CObjPet *pObjPet)
{
  int32_t m_nStar; // ebx
  CfgData *v3; // rax
  const CfgPetTable *PetTable; // rax
  int32_t addon; // ebx
  int32_t index; // ecx
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  const CfgPetUpStar *pCfgUpStar; // [rsp+28h] [rbp-18h]

  if ( pObjPet )
  {
    if ( this->m_pFightPet == pObjPet )
    {
      m_nStar = this->m_nStar;
      v3 = Answer::Singleton<CfgData>::instance();
      PetTable = CfgData::GetPetTable(v3);
      pCfgUpStar = CfgPetTable::GetPetUpStar(PetTable, m_nStar);
      if ( pCfgUpStar )
      {
        for ( iter._M_current = std::vector<AttrAddon>::begin(&pCfgUpStar->vAddPetAttr)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<AttrAddon>::end(&pCfgUpStar->vAddPetAttr)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
            break;
          addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
          index = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->index;
          Unit::AddAttrValue(pObjPet, (const CObjAttrs::Index_T)index, addon);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CExtCharPet::GetSkillBattle(const CExtCharPet *const this)
{
  if ( this->m_pFightPet && CObjPet::IsFighting(this->m_pFightPet) )
    return CObjPet::GetSkillBattle(this->m_pFightPet);
  else
    return 0;
}


#####################################
void __cdecl CExtCharPet::RecalPetAttr(CExtCharPet *const this)
{
  if ( this->m_pFightPet )
    CObjPet::RecalAttr(this->m_pFightPet);
}


#####################################
void __cdecl CExtCharPet::AddTarget(CExtCharPet *const this, UnitHandle launcher, bool bForce)
{
  UnitHandle launchera; // [rsp+8h] [rbp-48h] BYREF
  CExtCharPet *thisa; // [rsp+18h] [rbp-38h]
  UnitHandle Atter; // [rsp+20h] [rbp-30h]
  int32_t i; // [rsp+34h] [rbp-1Ch]
  CObjPet *pPet; // [rsp+38h] [rbp-18h]

  thisa = this;
  launchera = launcher;
  Atter = launcher;
  if ( launcher.type != 1 )
  {
    if ( thisa->m_pFightPet && CObjPet::IsFighting(thisa->m_pFightPet) )
      CObjPet::AddTarget(thisa->m_pFightPet, &launchera, bForce);
    for ( i = 0; i <= 3; ++i )
    {
      pPet = (CObjPet *)*((_QWORD *)&thisa->m_lSummons._M_impl + i + 2);
      if ( pPet && Unit::isAlive(pPet) )
        CObjPet::AddTarget(pPet, &launchera, bForce);
    }
  }
}


#####################################
void __cdecl CExtCharPet::SetTargetTile(CExtCharPet *const this, int32_t tx, int32_t ty, Direction dir)
{
  int32_t i; // [rsp+24h] [rbp-1Ch]
  CObjPet *pPet; // [rsp+28h] [rbp-18h]

  if ( this->m_pFightPet && CObjPet::IsFighting(this->m_pFightPet) )
    CObjPet::ResetTargetTile(this->m_pFightPet, tx, ty, dir);
  for ( i = 0; i <= 3; ++i )
  {
    pPet = (CObjPet *)*((_QWORD *)&this->m_lSummons._M_impl + i + 2);
    if ( pPet && Unit::isAlive(pPet) )
      CObjPet::ResetTargetTile(pPet, tx, ty, dir);
  }
}


#####################################
void __cdecl CExtCharPet::SendPetInfo(CExtCharPet *const this)
{
  if ( CExtCharPet::IsFunctionOpen(this) )
  {
    if ( !this->m_pFightPet )
      CExtCharPet::OnInitPet(this);
    CExtCharPet::sendPetInfo(this);
  }
}


#####################################
void __cdecl CExtCharPet::sendPetInfo(CExtCharPet *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v5; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && this->m_pFightPet )
  {
    v1 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2DD2u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nStar);
      CObjPet::AppendPetInfo(this->m_pFightPet, packet);
      Answer::NetPacket::writeInt32(packet, this->m_HuanHua);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v5 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v5, ConnId, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CExtCharPet::addSummonPet(CExtCharPet *const this, CObjPet *pPet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  if ( !pPet )
    return 0;
  for ( i = 0; i <= 3; ++i )
  {
    if ( !*((_QWORD *)&this->m_lSummons._M_impl + i + 2) )
    {
      *((_QWORD *)&this->m_lSummons._M_impl + i + 2) = pPet;
      CObjPet::SetSatandPlace(pPet, FIGHT_PET_STAND_POS[i]);
      return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl CExtCharPet::removeSummonPet(CExtCharPet *const this, CObjPet *pPet)
{
  int32_t i; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 3; ++i )
  {
    if ( *((CObjPet **)&this->m_lSummons._M_impl + i + 2) == pPet )
      *((_QWORD *)&this->m_lSummons._M_impl + i + 2) = 0;
  }
}


