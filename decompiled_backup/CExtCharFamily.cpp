// Decompiled methods for class: CExtCharFamily
// Source: gameserver.cc
// Total methods: 53

#####################################
void __cdecl CExtCharFamily::~CExtCharFamily(CExtCharFamily *const this)
{
  CExtCharFamily::~CExtCharFamily(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharFamily::OnCleanUp(CExtCharFamily *const this)
{
  this->m_nFamilyId = 0;
  this->m_nPosition = 0;
  this->m_nContribution = 0;
  this->m_nDailyContribution = 0;
  this->m_MedLevel = 0;
  this->m_MedRes = 0;
  this->m_Hoe = 0;
  this->m_EnterDungeionFamilyId = 0;
  this->m_EnterCount = 0;
  this->m_EnterTime = 0;
  std::list<FamilySkill>::clear(&this->m_lSkills);
}


#####################################
void __cdecl CExtCharFamily::OnLoadFromDB(CExtCharFamily *const this, const PlayerDBData *const dbData)
{
  this->m_nFamilyId = dbData->m_FamilyData.nFamilyId;
  this->m_nPosition = dbData->m_FamilyData.nPosition;
  this->m_nContribution = dbData->m_FamilyData.nContribution;
  this->m_nDailyContribution = dbData->m_FamilyData.nDailyContribution;
  this->m_MedLevel = dbData->m_FamilyData.nMedLevel;
  this->m_MedRes = dbData->m_FamilyData.nMedRes;
  this->m_Hoe = dbData->m_FamilyData.nHoe;
  this->m_EnterDungeionFamilyId = dbData->m_FamilyData.EnterDungeionFamilyId;
  this->m_EnterCount = dbData->m_FamilyData.EnterCount;
  this->m_EnterTime = dbData->m_FamilyData.EnterTime;
  CExtCharFamily::loadSkillString(this, &dbData->m_FamilyData.strSkills);
}


#####################################
void __cdecl CExtCharFamily::OnSaveToDB(CExtCharFamily *const this, PlayerDBData *const dbData)
{
  _BYTE v2[32]; // [rsp+10h] [rbp-20h] BYREF

  dbData->m_FamilyData.nFamilyId = this->m_nFamilyId;
  dbData->m_FamilyData.nPosition = this->m_nPosition;
  dbData->m_FamilyData.nContribution = this->m_nContribution;
  dbData->m_FamilyData.nDailyContribution = this->m_nDailyContribution;
  CExtCharFamily::saveSkillString((CExtCharFamily *const)v2);
  std::string::operator=(&dbData->m_FamilyData.strSkills, v2);
  std::string::~string(v2);
  dbData->m_FamilyData.nMedLevel = this->m_MedLevel;
  dbData->m_FamilyData.nMedRes = this->m_MedRes;
  dbData->m_FamilyData.nHoe = this->m_Hoe;
  dbData->m_FamilyData.EnterDungeionFamilyId = this->m_EnterDungeionFamilyId;
  dbData->m_FamilyData.EnterCount = this->m_EnterCount;
  dbData->m_FamilyData.EnterTime = this->m_EnterTime;
}


#####################################
void __cdecl CExtCharFamily::GetInterestsProtocol(CExtCharFamily *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-34h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-32h] BYREF
  unsigned __int16 v4; // [rsp+20h] [rbp-30h] BYREF
  unsigned __int16 v5; // [rsp+22h] [rbp-2Eh] BYREF
  unsigned __int16 v6; // [rsp+24h] [rbp-2Ch] BYREF
  unsigned __int16 v7; // [rsp+26h] [rbp-2Ah] BYREF
  unsigned __int16 v8; // [rsp+28h] [rbp-28h] BYREF
  unsigned __int16 v9; // [rsp+2Ah] [rbp-26h] BYREF
  unsigned __int16 v10; // [rsp+2Ch] [rbp-24h] BYREF
  unsigned __int16 v11; // [rsp+2Eh] [rbp-22h] BYREF
  unsigned __int16 v12; // [rsp+30h] [rbp-20h] BYREF
  unsigned __int16 v13; // [rsp+32h] [rbp-1Eh] BYREF
  unsigned __int16 v14; // [rsp+34h] [rbp-1Ch] BYREF
  unsigned __int16 v15; // [rsp+36h] [rbp-1Ah] BYREF
  unsigned __int16 v16; // [rsp+38h] [rbp-18h] BYREF
  unsigned __int16 v17; // [rsp+3Ah] [rbp-16h] BYREF
  unsigned __int16 v18; // [rsp+3Ch] [rbp-14h] BYREF
  unsigned __int16 v19; // [rsp+3Eh] [rbp-12h] BYREF
  unsigned __int16 v20; // [rsp+40h] [rbp-10h] BYREF
  unsigned __int16 v21; // [rsp+42h] [rbp-Eh] BYREF
  unsigned __int16 v22; // [rsp+44h] [rbp-Ch] BYREF
  unsigned __int16 v23; // [rsp+46h] [rbp-Ah] BYREF
  unsigned __int16 v24; // [rsp+48h] [rbp-8h] BYREF
  unsigned __int16 v25; // [rsp+4Ah] [rbp-6h] BYREF
  unsigned __int16 v26; // [rsp+4Ch] [rbp-4h] BYREF
  unsigned __int16 v27; // [rsp+4Eh] [rbp-2h] BYREF

  __x = 780;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 779;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 778;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 777;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 776;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 798;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 747;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 748;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 20059;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 20060;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 783;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 785;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 784;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 786;
  std::list<unsigned short>::push_back(procList, &v15);
  v16 = 20063;
  std::list<unsigned short>::push_back(procList, &v16);
  v17 = 935;
  std::list<unsigned short>::push_back(procList, &v17);
  v18 = 787;
  std::list<unsigned short>::push_back(procList, &v18);
  v19 = 20065;
  std::list<unsigned short>::push_back(procList, &v19);
  v20 = 781;
  std::list<unsigned short>::push_back(procList, &v20);
  v21 = 782;
  std::list<unsigned short>::push_back(procList, &v21);
  v22 = 788;
  std::list<unsigned short>::push_back(procList, &v22);
  v23 = 789;
  std::list<unsigned short>::push_back(procList, &v23);
  v24 = 936;
  std::list<unsigned short>::push_back(procList, &v24);
  v25 = 20062;
  std::list<unsigned short>::push_back(procList, &v25);
  v26 = 20064;
  std::list<unsigned short>::push_back(procList, &v26);
  v27 = 20066;
  std::list<unsigned short>::push_back(procList, &v27);
}


#####################################
int32_t __cdecl CExtCharFamily::DispatchNetDatas(
        CExtCharFamily *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( !CExtCharFamily::isFunctionOpen(this) )
    return 10002;
  if ( nProcId == 786 )
    return CExtCharFamily::onImpeach(this, inPacket);
  if ( nProcId > 0x312u )
  {
    if ( nProcId == 20059 )
      return CExtCharFamily::onSocialCreateFamily(this, inPacket);
    if ( nProcId > 0x4E5Bu )
    {
      if ( nProcId == 20063 )
        return CExtCharFamily::onSocialImpeachResult(this, inPacket);
      if ( nProcId > 0x4E5Fu )
      {
        if ( nProcId == 20065 )
          return CExtCharFamily::onBindRedPacketTake(this, inPacket);
        if ( nProcId < 0x4E61u )
          return CExtCharFamily::onSocialInviteAll(this, inPacket);
        if ( nProcId == 20066 )
          return CExtCharFamily::onSocialChangeFamilyName(this, inPacket);
      }
      else
      {
        if ( nProcId == 20060 )
          return CExtCharFamily::onSocialUpdateFamilyInfo(this, inPacket);
        if ( nProcId == 20062 )
          return CExtCharFamily::onSocialStartBoss(this, inPacket);
      }
      return 0;
    }
    if ( nProcId == 789 )
      return CExtCharFamily::onGetTalkTaskReward(this, inPacket);
    if ( nProcId > 0x315u )
    {
      switch ( nProcId )
      {
        case 0x3A7u:
          return CExtCharFamily::onEnterFamilyDungeon(this, inPacket);
        case 0x3A8u:
          return CExtCharFamily::onAddBossPoint(this, inPacket);
        case 0x31Eu:
          return CExtCharFamily::onWearHoe(this, inPacket);
      }
      return 0;
    }
    if ( nProcId == 787 )
      return CExtCharFamily::onSendRedPacket(this, inPacket);
    else
      return CExtCharFamily::onSetTalkTask(this, inPacket);
  }
  else
  {
    if ( nProcId == 779 )
      return CExtCharFamily::onOpenTerritory(this, inPacket);
    if ( nProcId > 0x30Bu )
    {
      if ( nProcId == 782 )
      {
        return CExtCharFamily::onLearnSkill(this, inPacket);
      }
      else if ( nProcId > 0x30Eu )
      {
        if ( nProcId == 784 )
        {
          return CExtCharFamily::onGetFamilyTaskReward(this, inPacket);
        }
        else if ( nProcId > 0x310u )
        {
          return CExtCharFamily::onQuickSubmitFamilyTask(this, inPacket);
        }
        else
        {
          return CExtCharFamily::onReceiveFamilyTask(this, inPacket);
        }
      }
      else if ( nProcId == 780 )
      {
        return CExtCharFamily::onContribution(this, inPacket);
      }
      else
      {
        return CExtCharFamily::onRequestSkillInfo(this, inPacket);
      }
    }
    else
    {
      if ( nProcId == 776 )
        return CExtCharFamily::onFamilyBuyHoe(this, inPacket);
      if ( nProcId <= 0x308u )
      {
        if ( nProcId == 747 )
          return CExtCharFamily::onGetFamilyDungeonInfo(this, inPacket);
        if ( nProcId == 748 )
          return CExtCharFamily::onStartFamlyDungeon(this, inPacket);
        return 0;
      }
      if ( nProcId == 777 )
        return CExtCharFamily::onFamilyLevelUpMedal(this, inPacket);
      else
        return CExtCharFamily::onEnterTerritory(this, inPacket);
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onContribution(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  FamilyId_t FamilyId; // rbx
  FamilyManager *v4; // rax
  int32_t Record; // eax
  CfgData *v6; // rax
  int64_t nCount; // rbx
  CExtCurrency *Currency; // rax
  CExtOperateLimit *OperateLimit; // rax
  int64_t v10; // rbx
  CExtCurrency *v11; // rax
  int64_t nContributionValue; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v16; // rax
  int8_t v17; // bl
  GameService *v18; // rax
  int32_t v19; // edx
  uint32_t WOffset; // edx
  int8_t v21; // bl
  GameService *v22; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-34h]
  ContributionCfg *pCfg; // [rsp+20h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( CExtCharFamily::GetFamilyId(this) <= 0 )
    return 10002;
  FamilyId = CExtCharFamily::GetFamilyId(this);
  v4 = Answer::Singleton<FamilyManager>::instance();
  if ( FamilyManager::GetTerritoryState(v4, FamilyId) <= 0 )
    return 10002;
  Record = Player::getRecord(this->m_pPlayer, 1925);
  if ( Answer::DayTime::daydiff(Record) <= 0 )
    return 10002;
  Player::LogNpc(this->m_pPlayer, 5002, 2, 0);
  nIndex = Answer::NetPacket::readInt32(inPacket);
  v6 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GettFamilyDonateCfg(v6, nIndex);
  if ( !pCfg )
    return 10002;
  if ( pCfg->nType == 1 )
  {
    if ( Player::getRecord(this->m_pPlayer, 2103) > 2 )
      return 10002;
    nCount = pCfg->nCount;
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(Currency, nCount, CURRENCY_CHANGE_REASON::GCR_FAMILY_CONTRIBUTE, 0) )
      return 10002;
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 2103, 1);
  }
  else if ( pCfg->nType == 2 )
  {
    v10 = pCfg->nCount;
    v11 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecCurrency(
            v11,
            CURRENCY_TYPE::CURRENCY_GOLD,
            v10,
            CURRENCY_CHANGE_REASON::GCR_FAMILY_CONTRIBUTE,
            0) )
      return 10002;
  }
  CExtCharFamily::AddContribution(this, pCfg->nContributionValue, CURRENCY_CHANGE_REASON::FCCR_FAMILY_CONTRIBUTE);
  nContributionValue = pCfg->nContributionValue;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v16 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v16, ConnId, GateIndex, Proc, nContributionValue);
  v17 = Player::getConnId(this->m_pPlayer);
  v18 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v18, v17, Answer::PackType::PACK_DISPATCH, 0x4E9Bu);
  if ( !packet )
    return 10002;
  v19 = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, v19);
  Answer::NetPacket::writeInt8(packet, pCfg->nType);
  Answer::NetPacket::writeInt32(packet, pCfg->nCount);
  Answer::NetPacket::writeInt32(packet, pCfg->nContributionValue);
  Answer::NetPacket::writeInt32(packet, pCfg->nExp);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v21 = Player::getConnId(this->m_pPlayer);
  v22 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v22, v21, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onOpenTerritory(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  FamilyId_t FamilyId; // rbx
  FamilyManager *v5; // rax
  CExtCharBag *Bag; // rax
  CfgData *v7; // rax
  CExtCharBag *v8; // rax
  int8_t ConnId; // bl
  GameService *v10; // rax
  int16_t GateIndex; // ax
  uint32_t WOffset; // eax
  int8_t v13; // bl
  GameService *v14; // rax
  MemChrBag bagItem; // [rsp+10h] [rbp-50h] BYREF
  int8_t nState; // [rsp+3Bh] [rbp-25h]
  int32_t bagSlot; // [rsp+3Ch] [rbp-24h]
  CfgItem *pCfgItem; // [rsp+40h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  if ( CExtCharFamily::GetFamilyId(this) <= 0 )
    return 10002;
  if ( CExtCharFamily::GetPosition(this) != 3 )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) != 1 )
    return 10002;
  FamilyId = CExtCharFamily::GetFamilyId(this);
  v5 = Answer::Singleton<FamilyManager>::instance();
  nState = FamilyManager::GetTerritoryState(v5, FamilyId);
  if ( nState > 0 )
    return 10002;
  bagSlot = Answer::NetPacket::readInt32(inPacket);
  Bag = Player::GetBag(this->m_pPlayer);
  bagItem = *CExtCharBag::GetSlotData(Bag, bagSlot);
  if ( bagItem.itemClass != 1 && bagItem.itemCount <= 0 )
    return 10002;
  v7 = Answer::Singleton<CfgData>::instance();
  pCfgItem = CfgData::getItem(v7, bagItem.itemId);
  if ( !pCfgItem )
    return 10002;
  if ( pCfgItem->type != 218 )
    return 10002;
  --bagItem.itemCount;
  v8 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(v8, bagSlot, &bagItem, ITEM_CHANGE_REASON::ICR_OPEN_TERRITORY, 0);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v10, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E91u);
  if ( !packet )
    return 2;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  Answer::NetPacket::writeInt8(packet, 0);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v13 = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v14, v13, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onEnterTerritory(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  FamilyId_t FamilyId; // rbx
  FamilyManager *v5; // rax
  FamilyId_t v6; // rbx
  MapManager *v7; // rax
  Map *Map; // rax
  int32_t RunnerId; // ebx
  MapManager *v11; // rax
  Position EnterPos; // [rsp+20h] [rbp-30h] BYREF
  int8_t nState; // [rsp+37h] [rbp-19h]
  CTerritory *pTerritory; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) != 1 )
    return 10002;
  if ( CExtCharFamily::GetFamilyId(this) <= 0 )
    return 10002;
  Player::LogNpc(this->m_pPlayer, 102, 1, 5012);
  FamilyId = CExtCharFamily::GetFamilyId(this);
  v5 = Answer::Singleton<FamilyManager>::instance();
  nState = FamilyManager::GetTerritoryState(v5, FamilyId);
  if ( nState <= 0 )
    return 10002;
  v6 = CExtCharFamily::GetFamilyId(this);
  v7 = Answer::Singleton<MapManager>::instance();
  pTerritory = MapManager::NewTerritory(v7, v6);
  if ( pTerritory && StaticObj::getMap(this->m_pPlayer) )
  {
    Position::Position(&EnterPos, 0, 0);
    if ( StaticObj::IsKuangDong(this->m_pPlayer) )
    {
      EnterPos.x = 108;
      EnterPos.y = 27;
    }
    else
    {
      EnterPos = Map::GetEnterPos(pTerritory);
    }
    if ( EnterPos.y <= 0 || EnterPos.x <= 0 )
      return 10002;
    Player::setOldPosition(this->m_pPlayer);
    Player::broadcastLeave(this->m_pPlayer);
    Map = StaticObj::getMap(this->m_pPlayer);
    (*((void (__fastcall **)(Map *, Player *, _QWORD))Map->_vptr_Map + 16))(Map, this->m_pPlayer, 0);
    (*((void (__fastcall **)(CTerritory *, Player *, _QWORD, _QWORD))pTerritory->_vptr_Map + 15))(
      pTerritory,
      this->m_pPlayer,
      (unsigned int)EnterPos.x,
      (unsigned int)EnterPos.y);
    RunnerId = Map::GetRunnerId(pTerritory);
    v11 = Answer::Singleton<MapManager>::instance();
    MapManager::PostMsg(v11, RunnerId, GameMsgCode::GMC_ADD_TERRITORY, pTerritory, 0, 0, 0, 0);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onFamilyLevelUpMedal(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t m_MedLevel; // ebx
  CfgData *v4; // rax
  const CfgFamilyTable *FamilyTable; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const CfgFamilyTable *v8; // rax
  int64_t v9; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  const FamilySelfMedal *pFamilyMedal; // [rsp+10h] [rbp-30h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  m_MedLevel = this->m_MedLevel;
  v4 = Answer::Singleton<CfgData>::instance();
  FamilyTable = CfgData::GetFamilyTable(v4);
  pFamilyMedal = CfgFamilyTable::GetFamilySelfMedal(FamilyTable, m_MedLevel);
  if ( !pFamilyMedal )
    return 2;
  v6 = this->m_MedLevel + 1;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetFamilyTable(v7);
  if ( !CfgFamilyTable::GetFamilySelfMedal(v8, v6) )
    return 2;
  if ( pFamilyMedal->nNeedExp < 0 || pFamilyMedal->nNeedExp > this->m_MedRes )
    return 0;
  this->m_MedRes -= pFamilyMedal->nNeedExp;
  ++this->m_MedLevel;
  CExtCharFamily::sendSkillInfo(this);
  Player::RecalcAttr(this->m_pPlayer);
  v9 = this->m_MedLevel;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v13, ConnId, GateIndex, Proc, v9);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onFamilyBuyHoe(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  FamilyId_t FamilyId; // rbx
  FamilyManager *v4; // rax
  CfgData *v5; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v7; // rax
  FamilyInfo FamilyStu; // [rsp+10h] [rbp-D0h] BYREF
  MemChrBag stu; // [rsp+80h] [rbp-60h] BYREF
  MemChrBagVector ItemTmp; // [rsp+A0h] [rbp-40h] BYREF
  int32_t ItemId; // [rsp+C4h] [rbp-1Ch]
  CfgItem *pCfgItem; // [rsp+C8h] [rbp-18h]

  if ( inPacket && this->m_pPlayer )
  {
    FamilyId = CExtCharFamily::GetFamilyId(this);
    v4 = Answer::Singleton<FamilyManager>::instance();
    FamilyManager::GetFamilyInfo(&FamilyStu, v4, FamilyId);
    if ( FamilyStu.nLevel > 1 )
    {
      ItemId = Answer::NetPacket::readInt32(inPacket);
      if ( Player::getRecord(this->m_pPlayer, 2071) <= 0 )
      {
        v5 = Answer::Singleton<CfgData>::instance();
        pCfgItem = CfgData::getItem(v5, ItemId);
        if ( pCfgItem )
        {
          if ( pCfgItem->type == 220 )
          {
            Bag = Player::GetBag(this->m_pPlayer);
            if ( CExtCharBag::GetFreeSlotCount(Bag) > 0 )
            {
              if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CONTRIBUTION) > 999 )
              {
                if ( pCfgItem->id == 801 )
                {
                  if ( !Player::DecCurrency(
                          this->m_pPlayer,
                          CURRENCY_TYPE::CURRENCY_CONTRIBUTION,
                          1000,
                          CURRENCY_CHANGE_REASON::GCR_BUY_HOE,
                          0) )
                  {
                    v2 = 10002;
                    goto LABEL_29;
                  }
                }
                else
                {
                  if ( pCfgItem->id != 831 )
                  {
                    v2 = 10002;
                    goto LABEL_29;
                  }
                  if ( !Player::DecCurrency(
                          this->m_pPlayer,
                          CURRENCY_TYPE::CURRENCY_CONTRIBUTION,
                          1000,
                          CURRENCY_CHANGE_REASON::GCR_BUY_HOE,
                          0) )
                  {
                    v2 = 10002;
                    goto LABEL_29;
                  }
                  if ( !Player::DecCurrency(
                          this->m_pPlayer,
                          CURRENCY_TYPE::CURRENCY_GOLD,
                          1500,
                          CURRENCY_CHANGE_REASON::GCR_BUY_HOE,
                          0) )
                  {
                    v2 = 10002;
                    goto LABEL_29;
                  }
                }
                std::vector<MemChrBag>::vector(&ItemTmp);
                *(_QWORD *)&stu.itemId = 0x100000000LL;
                *(_QWORD *)&stu.itemCount = 1;
                *(_QWORD *)&stu.endTime = 0;
                stu.srcId = 0;
                stu.itemId = pCfgItem->id;
                stu.bind = 1;
                std::vector<MemChrBag>::push_back(&ItemTmp, &stu);
                v7 = Player::GetBag(this->m_pPlayer);
                if ( !CExtCharBag::AddItem(v7, &ItemTmp, ITEM_CHANGE_REASON::ICR_BUY_HOE) )
                {
                  v2 = 10002;
                }
                else
                {
                  Player::updateRecord(this->m_pPlayer, 2071, 1);
                  v2 = 0;
                }
                std::vector<MemChrBag>::~vector(&ItemTmp);
                goto LABEL_29;
              }
              v2 = 10002;
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
LABEL_29:
    FamilyInfo::~FamilyInfo(&FamilyStu);
    return v2;
  }
  return 10002;
}


#####################################
int32_t __cdecl CExtCharFamily::EndMining(CExtCharFamily *const this)
{
  int32_t m_Hoe; // ebx
  CfgData *v3; // rax
  HoeCfg *pHoeCfg; // [rsp+18h] [rbp-18h]

  if ( this->m_Hoe <= 0 || !this->m_pPlayer )
    return 0;
  m_Hoe = this->m_Hoe;
  v3 = Answer::Singleton<CfgData>::instance();
  pHoeCfg = CfgData::GetHoeCfg(v3, m_Hoe);
  if ( !pHoeCfg )
    return 0;
  this->m_Hoe = pHoeCfg->nNextId;
  CExtCharFamily::SendHoe(this);
  if ( this->m_Hoe <= 0 )
    Player::SetPlantState(this->m_pPlayer, 0);
  return pHoeCfg->nDouble;
}


#####################################
int32_t __cdecl CExtCharFamily::onWearHoe(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CfgData *v4; // rax
  CExtCharBag *v5; // rax
  CExtCharBag *v6; // rax
  CExtCharBag *v7; // rax
  CExtCharBag *v8; // rax
  MemChrBag item; // [rsp+10h] [rbp-60h] BYREF
  MemChrBag bagItem; // [rsp+30h] [rbp-40h] BYREF
  int8_t nType; // [rsp+53h] [rbp-1Dh]
  int32_t bagSlot; // [rsp+54h] [rbp-1Ch]
  CfgItem *pCfgItem; // [rsp+58h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nType = Answer::NetPacket::readInt8(inPacket);
  bagSlot = Answer::NetPacket::readInt32(inPacket);
  if ( nType == 1 )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    bagItem = *CExtCharBag::GetSlotData(Bag, bagSlot);
    if ( bagItem.itemClass != 1 && bagItem.itemCount <= 0 )
      return 10002;
    v4 = Answer::Singleton<CfgData>::instance();
    pCfgItem = CfgData::getItem(v4, bagItem.itemId);
    if ( !pCfgItem )
      return 10002;
    if ( pCfgItem->type != 220 )
      return 10002;
    if ( this->m_Hoe <= 0 )
    {
      this->m_Hoe = pCfgItem->id;
    }
    else
    {
      memset(&item, 0, sizeof(item));
      item.itemId = this->m_Hoe;
      item.itemClass = 1;
      item.itemCount = 1;
      item.bind = 1;
      v5 = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::AddItem(v5, &item, ITEM_CHANGE_REASON::ICR_WEAR_HOE) )
        return 10002;
      this->m_Hoe = pCfgItem->id;
    }
    v6 = Player::GetBag(this->m_pPlayer);
    bagItem = *CExtCharBag::GetSlotData(v6, bagSlot);
    --bagItem.itemCount;
    v7 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::SetSlotData(v7, bagSlot, &bagItem, ITEM_CHANGE_REASON::ICR_FAMILY_CREATE, 0);
  }
  else
  {
    if ( nType != 2 )
      return 2;
    memset(&item, 0, sizeof(item));
    item.itemId = this->m_Hoe;
    item.itemClass = 1;
    item.itemCount = 1;
    item.bind = 1;
    v8 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(v8, &item, ITEM_CHANGE_REASON::ICR_WEAR_HOE) )
      return 10002;
    this->m_Hoe = 0;
    if ( Player::GetPlantState(this->m_pPlayer) == 1 )
      Player::BreakGather(this->m_pPlayer, 1);
  }
  CExtCharFamily::SendHoe(this);
  return 0;
}


#####################################
void __cdecl CExtCharFamily::SendHoe(CExtCharFamily *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2806u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_Hoe);
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
void __cdecl CExtCharFamily::AddContribution(
        CExtCharFamily *const this,
        int32_t nAddValue,
        CURRENCY_CHANGE_REASON nOpWay)
{
  if ( this->m_pPlayer )
  {
    if ( nAddValue > 0 )
    {
      Player::AddCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_CONTRIBUTION, nAddValue, nOpWay, 0);
      this->m_nContribution += nAddValue;
      this->m_nDailyContribution += nAddValue;
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onSocialCreateFamily(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t Now; // ebx
  CExtCharBag *Bag; // rax
  CfgData *v5; // rax
  const char *v6; // rax
  CExtCurrency *Currency; // rax
  CExtCharBag *v9; // rax
  int32_t v10; // eax
  int8_t ConnId; // bl
  GameService *v12; // rax
  int16_t GateIndex; // ax
  uint32_t WOffset; // eax
  int8_t v15; // bl
  GameService *v16; // rax
  MemChrBag bagItem; // [rsp+10h] [rbp-70h] BYREF
  std::string notice; // [rsp+30h] [rbp-50h] BYREF
  std::string name; // [rsp+40h] [rbp-40h] BYREF
  int32_t bagSlot; // [rsp+54h] [rbp-2Ch]
  CfgItem *pCfgItem; // [rsp+58h] [rbp-28h]
  int32_t nCostMoney; // [rsp+64h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+68h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  bagSlot = Answer::NetPacket::readInt32(inPacket);
  Now = Unit::getNow(this->m_pPlayer);
  if ( Now < Player::getRecord(this->m_pPlayer, 1160) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  bagItem = *CExtCharBag::GetSlotData(Bag, bagSlot);
  if ( bagItem.itemClass != 1 && bagItem.itemCount <= 0 )
    return 10002;
  v5 = Answer::Singleton<CfgData>::instance();
  pCfgItem = CfgData::getItem(v5, bagItem.itemId);
  if ( !pCfgItem )
    return 10002;
  if ( pCfgItem->type != 182 )
    return 10002;
  v6 = (const char *)std::string::c_str(&pCfgItem->effect);
  nCostMoney = atoi(v6);
  if ( nCostMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(Currency, nCostMoney, CURRENCY_CHANGE_REASON::MCR_CREATE_FAMILY, 0) )
      return 10002;
  }
  --bagItem.itemCount;
  v9 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(v9, bagSlot, &bagItem, ITEM_CHANGE_REASON::ICR_FAMILY_CREATE, 0);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&name, (bool)inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&notice, (bool)inPacket);
  v10 = Unit::getNow(this->m_pPlayer);
  Player::updateRecord(this->m_pPlayer, 1160, v10 + 86400);
  ConnId = Player::getConnId(this->m_pPlayer);
  v12 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v12, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E92u);
  if ( packet )
  {
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    Answer::NetPacket::writeInt32(packet, GateIndex);
    Answer::NetPacket::writeUTF8(packet, &name);
    Answer::NetPacket::writeUTF8(packet, &notice);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v15 = Player::getConnId(this->m_pPlayer);
    v16 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v16, v15, packet);
    v2 = 0;
  }
  else
  {
    v2 = 2;
  }
  std::string::~string(&notice);
  std::string::~string(&name);
  return v2;
}


#####################################
int32_t __cdecl CExtCharFamily::onSocialChangeFamilyName(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  int16_t GateIndex; // ax
  uint32_t WOffset; // eax
  int8_t v9; // bl
  GameService *v10; // rax
  MemChrBag bagItem; // [rsp+10h] [rbp-50h] BYREF
  std::string name; // [rsp+30h] [rbp-30h] BYREF
  int32_t bagSlot; // [rsp+44h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  bagSlot = Answer::NetPacket::readInt32(inPacket);
  Bag = Player::GetBag(this->m_pPlayer);
  bagItem = *CExtCharBag::GetSlotData(Bag, bagSlot);
  if ( bagItem.itemClass != 1 && bagItem.itemCount <= 0 )
    return 10002;
  if ( bagItem.itemId != 778 )
    return 10002;
  --bagItem.itemCount;
  v4 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(v4, bagSlot, &bagItem, ITEM_CHANGE_REASON::IDCR_FAMILY_CHANGE_NAME, 0);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&name, (bool)inPacket);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E93u);
  if ( packet )
  {
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    Answer::NetPacket::writeInt32(packet, GateIndex);
    Answer::NetPacket::writeUTF8(packet, &name);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v9 = Player::getConnId(this->m_pPlayer);
    v10 = Answer::Singleton<GameService>::instance();
    GameService::sendPacket(v10, v9, packet);
    v2 = 0;
  }
  else
  {
    v2 = 2;
  }
  std::string::~string(&name);
  return v2;
}


#####################################
int32_t __cdecl CExtCharFamily::onSocialUpdateFamilyInfo(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t Now; // eax
  int8_t ConnId; // bl
  CActivityManager *v5; // rax
  int32_t m_nPosition; // ebx
  CExtCharTitle *CharTitle; // rax
  CExtCharTitle *v8; // rax
  FamilyId_t nOldFamilyId; // [rsp+10h] [rbp-30h]
  FamilyId_t FamilyId; // [rsp+18h] [rbp-28h]
  int8_t oldPosition; // [rsp+27h] [rbp-19h]
  __int64 winFamily; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nOldFamilyId = this->m_nFamilyId;
  FamilyId = Answer::NetPacket::readInt64(inPacket);
  if ( this->m_nFamilyId != FamilyId )
  {
    if ( !nOldFamilyId )
    {
      Now = Unit::getNow(this->m_pPlayer);
      Player::updateRecord(this->m_pPlayer, 1925, Now);
    }
    this->m_nFamilyId = FamilyId;
    Player::SendFamilyWarIcon(this->m_pPlayer);
  }
  oldPosition = this->m_nPosition;
  this->m_nPosition = Answer::NetPacket::readInt32(inPacket);
  if ( !this->m_nFamilyId )
  {
    this->m_nPosition = 0;
    this->m_nContribution = 0;
    this->m_nDailyContribution = 0;
    if ( StaticObj::IsTerritory(this->m_pPlayer) )
      Player::OnBackCity(this->m_pPlayer, 1, 0);
  }
  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<CActivityManager>::instance();
  winFamily = CActivityManager::GetCityWarWinner(v5, ConnId);
  if ( winFamily > 0 && this->m_nFamilyId == winFamily )
  {
    if ( this->m_nPosition != oldPosition || this->m_nFamilyId != nOldFamilyId )
    {
      Player::SetActState(this->m_pPlayer, 1);
      m_nPosition = this->m_nPosition;
      CharTitle = Player::GetCharTitle(this->m_pPlayer);
      CExtCharTitle::CheckAddTitle(CharTitle, 1, m_nPosition);
    }
  }
  else if ( nOldFamilyId == winFamily && this->m_nFamilyId != nOldFamilyId )
  {
    Player::SetActState(this->m_pPlayer, 0);
    v8 = Player::GetCharTitle(this->m_pPlayer);
    CExtCharTitle::RemoveTitle(v8, 1, 0);
  }
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Unit::setNeedSyncSelf(this->m_pPlayer);
  Player::setSyncStatusFlag(this->m_pPlayer);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onReceiveFamilyTask(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  const CfgFamilyTask *FamilyTaskTable; // rax
  ChrTask *Task; // rax
  int32_t FamilyTaskId; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 10002;
  if ( CExtCharFamily::GetFamilyId(this) <= 0 )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 2019) > 9 )
    return 10002;
  v3 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v4 = Answer::Singleton<CfgData>::instance();
  FamilyTaskTable = CfgData::GetFamilyTaskTable(v4);
  FamilyTaskId = CfgFamilyTask::GetFamilyTask(FamilyTaskTable, v3);
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::receive(Task, FamilyTaskId);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onQuickSubmitFamilyTask(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  ChrTask *Task; // rax
  int32_t nTaskId; // [rsp+14h] [rbp-Ch]
  CfgTask *pCfgTask; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer )
    return 10002;
  nTaskId = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfgTask = CfgData::getTask(v3, nTaskId);
  if ( !pCfgTask )
    return 10002;
  if ( pCfgTask->quickDoneCost <= 0 )
    return 10002;
  if ( pCfgTask->type != 37 )
    return 10002;
  if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < pCfgTask->quickDoneCost )
    return 10002;
  Task = Player::GetTask(this->m_pPlayer);
  if ( !ChrTask::setTaskCanSubmit(Task, nTaskId, 1) )
    return 10002;
  Player::DecCurrency(
    this->m_pPlayer,
    CURRENCY_TYPE::CURRENCY_GOLD,
    pCfgTask->quickDoneCost,
    CURRENCY_CHANGE_REASON::GCR_QUICK_DONE_FAMILY_TASK,
    nTaskId);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onGetFamilyTaskReward(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  FamilyId_t FamilyId; // rbx
  FamilyManager *v5; // rax
  MemChrBagVector *p_Rewards; // rbx
  CExtCharBag *Bag; // rax
  FamilyInfo familyInfo; // [rsp+10h] [rbp-A0h] BYREF
  int32_t Index; // [rsp+8Ch] [rbp-24h]
  int32_t OldRecord; // [rsp+90h] [rbp-20h]
  int32_t NewRecord; // [rsp+94h] [rbp-1Ch]
  FamilyTaskReward *Rewards; // [rsp+98h] [rbp-18h]

  if ( !inPacket )
    return 10002;
  if ( CExtCharFamily::GetFamilyId(this) <= 0 )
    return 10002;
  Index = Answer::NetPacket::readInt8(inPacket);
  OldRecord = Player::getRecord(this->m_pPlayer, 2020);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  Rewards = CfgData::GetFamilyReward(v3, Index);
  if ( !Rewards )
    return 10002;
  FamilyId = CExtCharFamily::GetFamilyId(this);
  v5 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&familyInfo, v5, FamilyId);
  if ( Rewards->NeedCount <= familyInfo.FamilyTaskCount )
  {
    p_Rewards = &Rewards->Rewards;
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, p_Rewards, ITEM_CHANGE_REASON::ICR_FAMILY_TASK_REWARD) )
    {
      v2 = 10002;
    }
    else
    {
      Player::updateRecord(this->m_pPlayer, 2020, NewRecord);
      v2 = 0;
    }
  }
  else
  {
    v2 = 10002;
  }
  FamilyInfo::~FamilyInfo(&familyInfo);
  return v2;
}


#####################################
std::string __cdecl CExtCharFamily::GetFamilyName(const CExtCharFamily *const this)
{
  __int64 v1; // rsi
  FamilyId_t v2; // r12
  FamilyManager *v3; // rax
  FamilyInfo info; // [rsp+10h] [rbp-90h] BYREF
  _BYTE v6[17]; // [rsp+8Fh] [rbp-11h] BYREF

  v2 = *(_QWORD *)(v1 + 16);
  v3 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&info, v3, v2);
  if ( FamilyInfo::IsEmpty(&info) )
  {
    std::allocator<char>::allocator(v6);
    std::string::string(this, byte_8CAD80, v6);
    std::allocator<char>::~allocator(v6);
  }
  else
  {
    std::string::string((std::string *)this, &info.strName);
  }
  FamilyInfo::~FamilyInfo(&info);
  return (std::string)this;
}


#####################################
int32_t __cdecl CExtCharFamily::GetFamilyLevel(const CExtCharFamily *const this)
{
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v2; // rax
  int32_t nLevel; // ebx
  FamilyInfo info; // [rsp+10h] [rbp-80h] BYREF

  m_nFamilyId = this->m_nFamilyId;
  v2 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&info, v2, m_nFamilyId);
  if ( FamilyInfo::IsEmpty(&info) )
    nLevel = 0;
  else
    nLevel = info.nLevel;
  FamilyInfo::~FamilyInfo(&info);
  return nLevel;
}


#####################################
bool __cdecl CExtCharFamily::IsDeclareWarFamily(CExtCharFamily *const this, FamilyId_t nFamilyId)
{
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v3; // rax
  bool v4; // bl
  FamilyInfo info; // [rsp+10h] [rbp-80h] BYREF

  m_nFamilyId = this->m_nFamilyId;
  v3 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&info, v3, m_nFamilyId);
  v4 = !FamilyInfo::IsEmpty(&info) && FamilyInfo::IsDeclareWarFamily(&info, nFamilyId);
  FamilyInfo::~FamilyInfo(&info);
  return v4;
}


#####################################
bool __cdecl CExtCharFamily::isFunctionOpen(const CExtCharFamily *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax

  if ( !this->m_pPlayer )
    return 0;
  PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
  return CFunctionOpen::IsOpened(PlayerFunctionOpen, 3);
}


#####################################
void __cdecl CExtCharFamily::SendAddFamilyTaskCount(CExtCharFamily *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E9Eu);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v6, v5, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onImpeach(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( this->m_nFamilyId <= 0 )
    return 10002;
  if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) <= 999 )
    return 2;
  CExtCharFamily::sendSocialImpeach(this);
  return 0;
}


#####################################
void __cdecl CExtCharFamily::sendSocialImpeach(CExtCharFamily *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E9Fu);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v6, v5, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onSocialImpeachResult(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v5; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          1000,
          CURRENCY_CHANGE_REASON::GCR_FAMILY_IMPEACH,
          0) )
    return 2;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v5, ConnId, GateIndex, 0x312u, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onSendRedPacket(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  int nTotalValue; // [rsp+18h] [rbp-8h]
  int nTimes; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nTotalValue = Answer::NetPacket::readInt32(inPacket);
  nTimes = Answer::NetPacket::readInt32(inPacket);
  if ( nTotalValue <= 99 || nTimes <= 9 || nTimes > 50 )
    return 10002;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          nTotalValue,
          CURRENCY_CHANGE_REASON::GCR_FAMILY_SEND_RED_PACKET,
          0) )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::AddLimitCount(OperateLimit, 1063, nTotalValue);
  CExtCharFamily::sendSocialSendRedPacket(this, nTotalValue, nTimes);
  return 0;
}


#####################################
void __cdecl CExtCharFamily::sendSocialSendRedPacket(CExtCharFamily *const this, int32_t nTotalValue, int32_t nTimes)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA2u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, nTotalValue);
      Answer::NetPacket::writeInt32(packet, nTimes);
      Answer::NetPacket::writeInt32(packet, 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v8, v7, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onEnterFamilyDungeon(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  if ( this->m_pPlayer )
    CExtCharFamily::EnterFamilyDungeon(this);
  return 10002;
}


#####################################
int32_t __cdecl CExtCharFamily::EnterFamilyDungeon(CExtCharFamily *const this)
{
  GameService *v2; // rax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax
  int16_t v7; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v11; // rax
  Job_t job; // bl
  int v14; // ebx
  int v15; // ebx
  int64_t DungeonId; // r13
  int16_t v18; // r12
  int8_t v19; // bl
  GameService *v20; // rax
  Map *pMap; // [rsp+18h] [rbp-38h]
  const Dungeon *pDungeon; // [rsp+20h] [rbp-30h]
  const CfgDungeon *cfgDungeon; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer )
    return 10002;
  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 1 )
    return 10002;
  if ( Player::IsInStall(this->m_pPlayer)
    || StaticObj::InDungeon(this->m_pPlayer)
    || StaticObj::InActivity(this->m_pPlayer) )
  {
    return 10002;
  }
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 10002;
  if ( (*((unsigned __int8 (__fastcall **)(Map *))pMap->_vptr_Map + 19))(pMap) != 1 )
    return 10002;
  if ( Answer::DayTime::daydiff(this->m_EnterTime) )
  {
    if ( this->m_EnterCount > 1 )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v6 = Answer::Singleton<GameService>::instance();
      GameService::replyfailure(v6, ConnId, GateIndex, 0x3A7u, 3, 0);
      return 10002;
    }
  }
  else if ( this->m_nFamilyId != this->m_EnterDungeionFamilyId )
  {
    v7 = Player::getGateIndex(this->m_pPlayer);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::replyfailure(v9, v8, v7, 0x3A7u, 1, 0);
    return 10002;
  }
  m_nFamilyId = this->m_nFamilyId;
  v11 = Answer::Singleton<FamilyManager>::instance();
  pDungeon = FamilyManager::GetFamilyDungeon(v11, m_nFamilyId);
  if ( pDungeon )
  {
    if ( !Dungeon::IsRunning(pDungeon) )
      return 10002;
    if ( Dungeon::GetCfgDungeon(pDungeon)->job > 0 )
    {
      job = Dungeon::GetCfgDungeon(pDungeon)->job;
      if ( job != Player::getJob(this->m_pPlayer) )
        return 10002;
    }
    v14 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    if ( v14 < Dungeon::GetCfgDungeon(pDungeon)->level )
      return 10002;
    v15 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    if ( v15 > Dungeon::GetCfgDungeon(pDungeon)->maxLevel )
      return 10002;
    Player::broadcastLeave(this->m_pPlayer);
    (*((void (__fastcall **)(Map *, Player *, _QWORD))pMap->_vptr_Map + 16))(pMap, this->m_pPlayer, 0);
    DungeonId = Dungeon::getDungeonId(pDungeon);
    v18 = Player::getGateIndex(this->m_pPlayer);
    v19 = Player::getConnId(this->m_pPlayer);
    v20 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v20, v19, v18, 0x12u, DungeonId);
    cfgDungeon = Dungeon::GetCfgDungeon(pDungeon);
    (*((void (__fastcall **)(const Dungeon *, Player *, _QWORD, _QWORD))pDungeon->_vptr_Map + 15))(
      pDungeon,
      this->m_pPlayer,
      (unsigned int)cfgDungeon->x,
      (unsigned int)cfgDungeon->y);
    this->m_EnterDungeionFamilyId = this->m_nFamilyId;
    if ( Answer::DayTime::daydiff(this->m_EnterTime) )
      ++this->m_EnterCount;
    this->m_EnterTime = Unit::getNow(this->m_pPlayer);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onBindRedPacketTake(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t nTotalValue; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nTotalValue = Answer::NetPacket::readInt32(inPacket);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::AddLimitCount(OperateLimit, 1127, nTotalValue);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onRequestSkillInfo(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CExtCharFamily::sendSkillInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onLearnSkill(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v4; // rax
  int32_t v5; // ebx
  CfgData *v6; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t nFamilyLevel; // ebx
  int32_t PlayerLevel; // ebx
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  int64_t nCostMoney; // rbx
  CExtCurrency *v13; // rax
  int64_t v14; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v18; // rax
  FamilyInfo info; // [rsp+10h] [rbp-A0h] BYREF
  int32_t nSkillId; // [rsp+80h] [rbp-30h]
  int32_t nSkillLevel; // [rsp+84h] [rbp-2Ch]
  const CfgFamilySkill *pCfgSkill; // [rsp+88h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nSkillId = Answer::NetPacket::readInt32(inPacket);
  if ( this->m_nFamilyId <= 0 )
    return 10002;
  m_nFamilyId = this->m_nFamilyId;
  v4 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&info, v4, m_nFamilyId);
  if ( FamilyInfo::IsEmpty(&info) )
  {
    v2 = 10002;
  }
  else
  {
    nSkillLevel = CExtCharFamily::getSkillLevel(this, nSkillId);
    v5 = nSkillLevel + 1;
    v6 = Answer::Singleton<CfgData>::instance();
    SkillTable = CfgData::GetSkillTable(v6);
    pCfgSkill = CfgSkillTable::GetFamilySkill(SkillTable, nSkillId, v5);
    if ( pCfgSkill )
    {
      nFamilyLevel = pCfgSkill->nFamilyLevel;
      if ( nFamilyLevel <= CExtCharFamily::GetFamilyLevel(this) )
      {
        PlayerLevel = pCfgSkill->PlayerLevel;
        if ( PlayerLevel <= (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
        {
          Currency = Player::GetCurrency(this->m_pPlayer);
          MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
          if ( MoneyBindAndNoBind >= pCfgSkill->nCostMoney )
          {
            if ( !Player::DecCurrency(
                    this->m_pPlayer,
                    CURRENCY_TYPE::CURRENCY_CONTRIBUTION,
                    pCfgSkill->nCostValue,
                    CURRENCY_CHANGE_REASON::FCCR_FAMILY_LEARN_SKILL,
                    0) )
            {
              v2 = 10002;
            }
            else
            {
              nCostMoney = pCfgSkill->nCostMoney;
              v13 = Player::GetCurrency(this->m_pPlayer);
              if ( !CExtCurrency::DecMoneyAndNoBind(v13, nCostMoney, CURRENCY_CHANGE_REASON::FCCR_FAMILY_LEARN_SKILL, 0) )
              {
                v2 = 10002;
              }
              else
              {
                CExtCharFamily::addSkillLevel(this, nSkillId);
                Player::recalcAttr(this->m_pPlayer, 0, 0);
                v14 = nSkillId;
                Proc = Answer::NetPacket::getProc(inPacket);
                GateIndex = Player::getGateIndex(this->m_pPlayer);
                ConnId = Player::getConnId(this->m_pPlayer);
                v18 = Answer::Singleton<GameService>::instance();
                v2 = GameService::replySuccess(v18, ConnId, GateIndex, Proc, v14);
              }
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
    }
    else
    {
      v2 = 10002;
    }
  }
  FamilyInfo::~FamilyInfo(&info);
  return v2;
}


#####################################
void __cdecl CExtCharFamily::sendSkillInfo(CExtCharFamily *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  const FamilySkill *v4; // rax
  const FamilySkill *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_List_const_iterator<FamilySkill> iter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<FamilySkill> __x; // [rsp+20h] [rbp-40h] BYREF
  std::_List_const_iterator<FamilySkill> v12; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<FamilySkill> v13; // [rsp+40h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x27D3u);
    if ( packet )
    {
      v3 = std::list<FamilySkill>::size(&this->m_lSkills);
      Answer::NetPacket::writeInt32(packet, v3);
      __x._M_node = std::list<FamilySkill>::begin(&this->m_lSkills)._M_node;
      std::_List_const_iterator<FamilySkill>::_List_const_iterator(&iter, &__x);
      while ( 1 )
      {
        v13._M_node = std::list<FamilySkill>::end(&this->m_lSkills)._M_node;
        std::_List_const_iterator<FamilySkill>::_List_const_iterator(&v12, &v13);
        if ( !std::_List_const_iterator<FamilySkill>::operator!=(&iter, &v12) )
          break;
        v4 = std::_List_const_iterator<FamilySkill>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v4->nSkillId);
        v5 = std::_List_const_iterator<FamilySkill>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, v5->nSkillLevel);
        std::_List_const_iterator<FamilySkill>::operator++(&iter);
      }
      Answer::NetPacket::writeInt32(packet, this->m_MedLevel);
      Answer::NetPacket::writeInt32(packet, this->m_MedRes);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v8 = Player::getConnId(this->m_pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::getSkillLevel(CExtCharFamily *const this, int32_t nSkillId)
{
  std::_List_const_iterator<FamilySkill> iter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<FamilySkill> __x; // [rsp+20h] [rbp-30h] BYREF
  std::_List_const_iterator<FamilySkill> v5; // [rsp+30h] [rbp-20h] BYREF
  std::_List_iterator<FamilySkill> v6; // [rsp+40h] [rbp-10h] BYREF

  __x._M_node = std::list<FamilySkill>::begin(&this->m_lSkills)._M_node;
  std::_List_const_iterator<FamilySkill>::_List_const_iterator(&iter, &__x);
  while ( 1 )
  {
    v6._M_node = std::list<FamilySkill>::end(&this->m_lSkills)._M_node;
    std::_List_const_iterator<FamilySkill>::_List_const_iterator(&v5, &v6);
    if ( !std::_List_const_iterator<FamilySkill>::operator!=(&iter, &v5) )
      break;
    if ( std::_List_const_iterator<FamilySkill>::operator->(&iter)->nSkillId == nSkillId )
      return std::_List_const_iterator<FamilySkill>::operator->(&iter)->nSkillLevel;
    std::_List_const_iterator<FamilySkill>::operator++(&iter);
  }
  return 0;
}


#####################################
void __cdecl CExtCharFamily::addSkillLevel(CExtCharFamily *const this, int32_t nSkillId)
{
  FamilySkill *v2; // rax
  std::_List_iterator<FamilySkill> iter; // [rsp+10h] [rbp-30h] BYREF
  FamilySkill skill; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<FamilySkill> __x; // [rsp+30h] [rbp-10h] BYREF

  for ( iter._M_node = std::list<FamilySkill>::begin(&this->m_lSkills)._M_node;
        ;
        std::_List_iterator<FamilySkill>::operator++(&iter) )
  {
    __x._M_node = std::list<FamilySkill>::end(&this->m_lSkills)._M_node;
    if ( !std::_List_iterator<FamilySkill>::operator!=(&iter, &__x) )
      break;
    if ( std::_List_iterator<FamilySkill>::operator->(&iter)->nSkillId == nSkillId )
    {
      v2 = std::_List_iterator<FamilySkill>::operator->(&iter);
      ++v2->nSkillLevel;
      return;
    }
  }
  skill.nSkillLevel = 1;
  skill.nSkillId = nSkillId;
  std::list<FamilySkill>::push_back(&this->m_lSkills, &skill);
}


#####################################
void __cdecl CExtCharFamily::AddSkillAttr(CExtCharFamily *const this)
{
  int32_t nSkillLevel; // r12d
  int32_t nSkillId; // ebx
  CfgData *v3; // rax
  const CfgSkillTable *SkillTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v6; // rax
  int32_t m_MedLevel; // ebx
  CfgData *v8; // rax
  const CfgFamilyTable *FamilyTable; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v11; // rax
  FamilyId_t FamilyId; // rbx
  FamilyManager *v13; // rax
  CfgData *v14; // rax
  const CfgFamilyTable *v15; // rax
  const AddAttribute *v16; // rax
  int32_t v17; // ebx
  const AddAttribute *v18; // rax
  std::_List_const_iterator<AddAttribute> iter_1; // [rsp+10h] [rbp-D0h] BYREF
  std::_List_const_iterator<AddAttribute> iter_2; // [rsp+20h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter_0; // [rsp+30h] [rbp-B0h] BYREF
  std::_List_const_iterator<FamilySkill> iter; // [rsp+40h] [rbp-A0h] BYREF
  std::_List_iterator<FamilySkill> __x; // [rsp+50h] [rbp-90h] BYREF
  std::_List_const_iterator<FamilySkill> v24; // [rsp+60h] [rbp-80h] BYREF
  std::_List_iterator<FamilySkill> v25; // [rsp+70h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+80h] [rbp-60h] BYREF
  std::_List_const_iterator<AddAttribute> v27; // [rsp+90h] [rbp-50h] BYREF
  std::_List_const_iterator<AddAttribute> v28; // [rsp+A0h] [rbp-40h] BYREF
  int32_t nFamilyLevel; // [rsp+ACh] [rbp-34h]
  const CfgFamilySkill *pCfgFamilySkill; // [rsp+B0h] [rbp-30h]
  const FamilySelfMedal *pFamilySelfMedal; // [rsp+B8h] [rbp-28h]
  int32_t MedlLevel; // [rsp+C4h] [rbp-1Ch]
  const FamilyMedal *pFamilyMedal; // [rsp+C8h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    nFamilyLevel = CExtCharFamily::GetFamilyLevel(this);
    __x._M_node = std::list<FamilySkill>::begin(&this->m_lSkills)._M_node;
    std::_List_const_iterator<FamilySkill>::_List_const_iterator(&iter, &__x);
    while ( 1 )
    {
      v25._M_node = std::list<FamilySkill>::end(&this->m_lSkills)._M_node;
      std::_List_const_iterator<FamilySkill>::_List_const_iterator(&v24, &v25);
      if ( !std::_List_const_iterator<FamilySkill>::operator!=(&iter, &v24) )
        break;
      nSkillLevel = std::_List_const_iterator<FamilySkill>::operator->(&iter)->nSkillLevel;
      nSkillId = std::_List_const_iterator<FamilySkill>::operator->(&iter)->nSkillId;
      v3 = Answer::Singleton<CfgData>::instance();
      SkillTable = CfgData::GetSkillTable(v3);
      pCfgFamilySkill = CfgSkillTable::GetFamilySkill(SkillTable, nSkillId, nSkillLevel, nFamilyLevel);
      if ( pCfgFamilySkill )
      {
        for ( iter_0._M_current = std::vector<AttrAddon>::begin(&pCfgFamilySkill->vAttrAddon)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter_0) )
        {
          __rhs._M_current = std::vector<AttrAddon>::end(&pCfgFamilySkill->vAttrAddon)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter_0, &__rhs) )
            break;
          addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0)->addon;
          v6 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter_0);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v6->index, addon);
        }
      }
      std::_List_const_iterator<FamilySkill>::operator++(&iter);
    }
    if ( nFamilyLevel > 1 )
    {
      m_MedLevel = this->m_MedLevel;
      v8 = Answer::Singleton<CfgData>::instance();
      FamilyTable = CfgData::GetFamilyTable(v8);
      pFamilySelfMedal = CfgFamilyTable::GetFamilySelfMedal(FamilyTable, m_MedLevel);
      if ( pFamilySelfMedal )
      {
        for ( iter_2._M_node = std::list<AddAttribute>::begin(&pFamilySelfMedal->lAttrList)._M_node;
              ;
              std::_List_const_iterator<AddAttribute>::operator++(&iter_2) )
        {
          v27._M_node = std::list<AddAttribute>::end(&pFamilySelfMedal->lAttrList)._M_node;
          if ( !std::_List_const_iterator<AddAttribute>::operator!=(&iter_2, &v27) )
            break;
          m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&iter_2)->m_nAddAttrValue;
          v11 = std::_List_const_iterator<AddAttribute>::operator->(&iter_2);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v11->m_nAddAttrType, m_nAddAttrValue);
        }
        FamilyId = CExtCharFamily::GetFamilyId(this);
        v13 = Answer::Singleton<FamilyManager>::instance();
        MedlLevel = FamilyManager::GetMedlLevel(v13, FamilyId);
        v14 = Answer::Singleton<CfgData>::instance();
        v15 = CfgData::GetFamilyTable(v14);
        pFamilyMedal = CfgFamilyTable::GetFamilyMedal(v15, MedlLevel);
        if ( pFamilyMedal )
        {
          for ( iter_1._M_node = std::list<AddAttribute>::begin(&pFamilyMedal->lAttrList)._M_node;
                ;
                std::_List_const_iterator<AddAttribute>::operator++(&iter_1) )
          {
            v28._M_node = std::list<AddAttribute>::end(&pFamilyMedal->lAttrList)._M_node;
            if ( !std::_List_const_iterator<AddAttribute>::operator!=(&iter_1, &v28) )
              break;
            v16 = std::_List_const_iterator<AddAttribute>::operator->(&iter_1);
            v17 = (int)(float)((float)((float)((float)pFamilySelfMedal->nAttrRate / 1000.0) + 1.0)
                             * (float)v16->m_nAddAttrValue);
            v18 = std::_List_const_iterator<AddAttribute>::operator->(&iter_1);
            Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v18->m_nAddAttrType, v17);
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::GetDefRdc(CExtCharFamily *const this, Player *Target)
{
  FamilyId_t FamilyId; // rdx
  FamilyId_t v4; // rbx
  FamilyManager *v5; // rax
  CfgData *v6; // rax
  const CfgFamilyTable *FamilyTable; // rax
  int32_t MedlLevel; // [rsp+14h] [rbp-1Ch]
  const FamilyMedal *pFamilyMedal; // [rsp+18h] [rbp-18h]

  if ( !Target )
    return 0;
  FamilyId = Player::getFamilyId(Target);
  if ( !CExtCharFamily::IsDeclareWarFamily(this, FamilyId) )
    return 0;
  v4 = CExtCharFamily::GetFamilyId(this);
  v5 = Answer::Singleton<FamilyManager>::instance();
  MedlLevel = FamilyManager::GetMedlLevel(v5, v4);
  v6 = Answer::Singleton<CfgData>::instance();
  FamilyTable = CfgData::GetFamilyTable(v6);
  pFamilyMedal = CfgFamilyTable::GetFamilyMedal(FamilyTable, MedlLevel);
  if ( pFamilyMedal )
    return pFamilyMedal->DefRdc;
  else
    return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onSetTalkTask(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( this->m_nFamilyId <= 0 )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 2039) )
    return 10002;
  v4 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v4, 2039, 1);
  return 0;
}


#####################################
int32_t __cdecl CExtCharFamily::onGetTalkTaskReward(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v5; // rax
  MemChrBag item; // [rsp+10h] [rbp-20h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( this->m_nFamilyId <= 0 )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, 2039) != 1 )
    return 10002;
  *(_QWORD *)&item.itemId = 0x100002711LL;
  *(_QWORD *)&item.itemCount = 0x100000001LL;
  *(_QWORD *)&item.endTime = 0;
  item.srcId = 0;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::ICR_FAMILY_TALK_TASK_REWARD) )
    return 10002;
  v5 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v5, 2039, 2);
  return 0;
}


#####################################
void __cdecl CExtCharFamily::loadSkillString(CExtCharFamily *const this, const std::string *const strSkills)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  FamilySkill skill; // [rsp+10h] [rbp-A0h] BYREF
  StringVector vSkill; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+40h] [rbp-70h] BYREF
  StringVector vStr; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v12; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v14; // [rsp+90h] [rbp-20h] BYREF
  _BYTE v15[17]; // [rsp+9Fh] [rbp-11h] BYREF

  if ( !std::operator==<char>(strSkills, byte_8CAD80) )
  {
    std::allocator<char>::allocator(&v12);
    std::string::string(&delims, "|", &v12);
    Answer::StringUtility::split(&vStr, strSkills, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v12);
    for ( iter._M_current = std::vector<std::string>::begin(&vStr)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<std::string>::end(&vStr)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
        break;
      std::allocator<char>::allocator(v15);
      std::string::string(&v14, ":", v15);
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
      Answer::StringUtility::split(&vSkill, v2, &v14, 0);
      std::string::~string(&v14);
      std::allocator<char>::~allocator(v15);
      if ( std::vector<std::string>::size(&vSkill) == 2 )
      {
        skill = 0;
        v3 = std::vector<std::string>::operator[](&vSkill, 0);
        v4 = (const char *)std::string::c_str(v3);
        skill.nSkillId = atoi(v4);
        v5 = std::vector<std::string>::operator[](&vSkill, 1u);
        v6 = (const char *)std::string::c_str(v5);
        skill.nSkillLevel = atoi(v6);
        std::list<FamilySkill>::push_back(&this->m_lSkills, &skill);
      }
      std::vector<std::string>::~vector(&vSkill);
    }
    std::vector<std::string>::~vector(&vStr);
  }
}


#####################################
std::string __cdecl CExtCharFamily::saveSkillString(CExtCharFamily *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int nSkillLevel; // r12d
  FamilySkill *v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  _BYTE v8[16]; // [rsp+10h] [rbp-1B0h] BYREF
  _BYTE v9[352]; // [rsp+20h] [rbp-1A0h] BYREF
  std::_List_iterator<FamilySkill> iter; // [rsp+180h] [rbp-40h] BYREF
  std::_List_iterator<FamilySkill> v11; // [rsp+190h] [rbp-30h] BYREF
  std::_List_iterator<FamilySkill> __x; // [rsp+1A0h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v8, (unsigned int)v2);
  for ( iter._M_node = std::list<FamilySkill>::begin((std::list<FamilySkill> *const)(v1 + 40))._M_node;
        ;
        std::_List_iterator<FamilySkill>::operator++(&iter) )
  {
    v11._M_node = std::list<FamilySkill>::end((std::list<FamilySkill> *const)(v1 + 40))._M_node;
    if ( !std::_List_iterator<FamilySkill>::operator!=(&iter, &v11) )
      break;
    __x._M_node = std::list<FamilySkill>::begin((std::list<FamilySkill> *const)(v1 + 40))._M_node;
    if ( std::_List_iterator<FamilySkill>::operator!=(&iter, &__x) )
      std::operator<<<std::char_traits<char>>(v9, "|");
    nSkillLevel = std::_List_iterator<FamilySkill>::operator->(&iter)->nSkillLevel;
    v4 = std::_List_iterator<FamilySkill>::operator->(&iter);
    v5 = std::ostream::operator<<(v9, (unsigned int)v4->nSkillId);
    v6 = std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v6, nSkillLevel);
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v8);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v8);
  return (std::string)this;
}


#####################################
int32_t __cdecl CExtCharFamily::onAddBossPoint(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v4; // rax
  CExtCharBag *Bag; // rax
  int32_t itemId; // ebx
  CfgData *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  std::string *v10; // rax
  const char *v11; // rax
  CExtCharBag *v12; // rax
  int64_t v13; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v17; // rax
  CExtOperateLimit *OperateLimit; // rax
  int8_t v19; // bl
  GameService *v20; // rax
  int16_t v21; // ax
  uint32_t WOffset; // eax
  int8_t v23; // bl
  GameService *v24; // rax
  FamilyInfo info; // [rsp+10h] [rbp-110h] BYREF
  MemChrBag bagItem; // [rsp+80h] [rbp-A0h] BYREF
  StringVector vStr; // [rsp+A0h] [rbp-80h] BYREF
  std::string delims; // [rsp+C0h] [rbp-60h] BYREF
  char v30; // [rsp+D7h] [rbp-49h] BYREF
  int32_t nSlot; // [rsp+D8h] [rbp-48h]
  int8_t IsDouble; // [rsp+DFh] [rbp-41h]
  CfgItem *pCfgItem; // [rsp+E0h] [rbp-40h]
  int32_t nAddPoint; // [rsp+ECh] [rbp-34h]
  int32_t nAddContribute; // [rsp+F0h] [rbp-30h]
  int32_t nRate; // [rsp+F4h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+F8h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    if ( this->m_nFamilyId <= 0 )
      return 10002;
    m_nFamilyId = this->m_nFamilyId;
    v4 = Answer::Singleton<FamilyManager>::instance();
    FamilyManager::GetFamilyInfo(&info, v4, m_nFamilyId);
    if ( FamilyInfo::IsEmpty(&info) )
    {
      v2 = 10002;
LABEL_30:
      FamilyInfo::~FamilyInfo(&info);
      return v2;
    }
    if ( Player::getRecord(this->m_pPlayer, 2073) > 2 )
    {
      v2 = 10002;
      goto LABEL_30;
    }
    nSlot = Answer::NetPacket::readInt32(inPacket);
    IsDouble = Answer::NetPacket::readInt8(inPacket);
    Bag = Player::GetBag(this->m_pPlayer);
    bagItem = *CExtCharBag::GetSlotData(Bag, nSlot);
    if ( bagItem.itemClass != 1 || bagItem.itemCount <= 0 )
    {
      v2 = 10002;
      goto LABEL_30;
    }
    itemId = bagItem.itemId;
    v7 = Answer::Singleton<CfgData>::instance();
    pCfgItem = CfgData::getItem(v7, itemId);
    if ( !pCfgItem )
    {
      v2 = 10002;
      goto LABEL_30;
    }
    if ( pCfgItem->type != 184 )
    {
      v2 = 10002;
      goto LABEL_30;
    }
    std::allocator<char>::allocator(&v30);
    std::string::string(&delims, ":", &v30);
    Answer::StringUtility::split(&vStr, &pCfgItem->effect, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v30);
    if ( std::vector<std::string>::size(&vStr) == 2 )
    {
      v8 = std::vector<std::string>::operator[](&vStr, 0);
      v9 = (const char *)std::string::c_str(v8);
      nAddPoint = atoi(v9);
      v10 = std::vector<std::string>::operator[](&vStr, 1u);
      v11 = (const char *)std::string::c_str(v10);
      nAddContribute = atoi(v11);
      if ( nAddPoint > 0 && nAddContribute > 0 )
      {
        nRate = 1;
        if ( IsDouble > 0 )
        {
          if ( !Player::DecCurrency(
                  this->m_pPlayer,
                  CURRENCY_TYPE::CURRENCY_GOLD,
                  200,
                  CURRENCY_CHANGE_REASON::GCR_FAMILY_BOSS,
                  0) )
          {
            v2 = 10002;
            goto LABEL_29;
          }
          nRate = 2;
        }
        --bagItem.itemCount;
        v12 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::SetSlotData(v12, nSlot, &bagItem, ITEM_CHANGE_REASON::ICR_FAMILY_BOSS_POINT, 0);
        CExtCharFamily::AddContribution(this, nRate * nAddContribute, CURRENCY_CHANGE_REASON::FCCR_FAMILY_BOSS_POINT);
        v13 = bagItem.itemId;
        Proc = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        ConnId = Player::getConnId(this->m_pPlayer);
        v17 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v17, ConnId, GateIndex, Proc, v13);
        OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
        CExtOperateLimit::AddLimitCount(OperateLimit, 2073, 1);
        v19 = Player::getConnId(this->m_pPlayer);
        v20 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v20, v19, Answer::PackType::PACK_DISPATCH, 0x4E9Bu);
        if ( packet )
        {
          v21 = Player::getGateIndex(this->m_pPlayer);
          Answer::NetPacket::writeInt32(packet, v21);
          Answer::NetPacket::writeInt8(packet, 3);
          Answer::NetPacket::writeInt32(packet, nRate * nAddPoint);
          Answer::NetPacket::writeInt32(packet, nRate * nAddContribute);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v23 = Player::getConnId(this->m_pPlayer);
          v24 = Answer::Singleton<GameService>::instance();
          GameService::sendPacket(v24, v23, packet);
          v2 = 0;
        }
        else
        {
          v2 = 10002;
        }
        goto LABEL_29;
      }
      v2 = 10002;
    }
    else
    {
      v2 = 10002;
    }
LABEL_29:
    std::vector<std::string>::~vector(&vStr);
    goto LABEL_30;
  }
  return 10002;
}


#####################################
int32_t __cdecl CExtCharFamily::onSocialStartBoss(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  FamilyId_t FamilyId; // rbx
  MapManager *v4; // rax
  CTerritory *pTerritory; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  FamilyId = CExtCharFamily::GetFamilyId(this);
  v4 = Answer::Singleton<MapManager>::instance();
  pTerritory = MapManager::NewTerritory(v4, FamilyId);
  if ( pTerritory )
  {
    CTerritory::StartBigPig(pTerritory);
    CExtCharFamily::StartFamilyAct(this, 0);
  }
  return 0;
}


#####################################
void __cdecl CExtCharFamily::StartFamilyAct(CExtCharFamily *const this, int32_t Param)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E9Cu);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, Param);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onSocialInviteAll(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v4; // rax
  int8_t ConnId; // bl
  GameService *v6; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v9; // bl
  GameService *v10; // rax
  int32_t nNowTime; // [rsp+10h] [rbp-20h]
  int32_t nLevel; // [rsp+14h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nNowTime = Unit::getNow(this->m_pPlayer);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( nNowTime - CExtOperateLimit::GetLimitCount(OperateLimit, 1131) <= 299 )
    return 10002;
  nLevel = Answer::NetPacket::readInt32(inPacket);
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_CASH,
          20,
          CURRENCY_CHANGE_REASON::GCR_FAMILY_INVITE_ALL,
          0) )
    return 10002;
  v4 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v4, 1131, nNowTime);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E9Du);
  if ( !packet )
    return 10002;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  Answer::NetPacket::writeInt32(packet, nLevel);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v9 = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v10, v9, packet);
  return 0;
}


#####################################
bool __cdecl CExtCharFamily::AddMedRes(CExtCharFamily *const this, int32_t AddValues)
{
  if ( AddValues <= 0 )
    return 0;
  this->m_MedRes += AddValues;
  CExtCharFamily::sendSkillInfo(this);
  return 1;
}


#####################################
int32_t __cdecl CExtCharFamily::onStartFamlyDungeon(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  FamilyId_t FamilyId; // rbx
  MapManager *v4; // rax
  int8_t v5; // bl
  CfgData *v6; // rax
  const CfgFamilyDungeonTable *FamilyDungeonTable; // rax
  int32_t FamilyLevel; // eax
  int32_t nDungeonId; // r12d
  FamilyId_t v10; // rbx
  FamilyManager *v11; // rax
  Npc *v12; // rbx
  int32_t nNpcId; // ebx
  CfgData *v14; // rax
  int32_t Now; // eax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v19; // rax
  tm Time; // [rsp+10h] [rbp-80h] BYREF
  int32_t nHard; // [rsp+4Ch] [rbp-44h]
  CTerritory *pTerritory; // [rsp+50h] [rbp-40h]
  const CfgFamilyDungeon *pCfg; // [rsp+58h] [rbp-38h]
  Npc *npc; // [rsp+60h] [rbp-30h]
  const CfgNpc *pCfgNpc; // [rsp+68h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Answer::DayTime::localnow(&Time);
  if ( Time.tm_hour > 21 )
    return 10002;
  if ( Player::getFamilyPosition(this->m_pPlayer) <= 1 )
    return 10002;
  nHard = Answer::NetPacket::readInt32(inPacket);
  FamilyId = CExtCharFamily::GetFamilyId(this);
  v4 = Answer::Singleton<MapManager>::instance();
  pTerritory = MapManager::GetTerritory(v4, FamilyId);
  if ( !pTerritory )
    return 10002;
  v5 = nHard;
  v6 = Answer::Singleton<CfgData>::instance();
  FamilyDungeonTable = CfgData::GetFamilyDungeonTable(v6);
  pCfg = CfgFamilyDungeonTable::GetDungeon(FamilyDungeonTable, v5);
  if ( !pCfg )
    return 10002;
  FamilyLevel = CExtCharFamily::GetFamilyLevel(this);
  if ( FamilyLevel < pCfg->nFamilyLevel )
    return 10002;
  nDungeonId = pCfg->nDungeonId;
  v10 = CExtCharFamily::GetFamilyId(this);
  v11 = Answer::Singleton<FamilyManager>::instance();
  if ( !FamilyManager::StartfamilyDungeon(v11, v10, nDungeonId, nHard) )
    return 10002;
  v12 = (Npc *)operator new(0x4E8u);
  Npc::Npc(v12);
  npc = v12;
  if ( !v12 )
    return 10002;
  nNpcId = pCfg->nNpcId;
  v14 = Answer::Singleton<CfgData>::instance();
  pCfgNpc = CfgData::getNpc(v14, nNpcId);
  if ( !pCfgNpc )
    return 10002;
  Now = Unit::getNow(this->m_pPlayer);
  Npc::init(npc, pCfgNpc, Now + pCfg->nTime);
  Map::addNpc(pTerritory, npc, pCfg->X, pCfg->Y);
  CExtCharFamily::SendFamilyDungeonInfo(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v19 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v19, ConnId, GateIndex, Proc, 0);
  CExtCharFamily::StartFamilyAct(this, 1);
  return 0;
}


#####################################
void __cdecl CExtCharFamily::SendFamilyDungeonInfo(CExtCharFamily *const this)
{
  FamilyId_t FamilyId; // rbx
  FamilyManager *v2; // rax
  int8_t v3; // bl
  GameService *v4; // rax
  uint32_t v5; // edx
  int16_t v6; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  FamilyId_t v9; // rbx
  FamilyManager *v10; // rax
  int8_t ConnId; // bl
  GameService *v12; // rax
  int32_t v13; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v16; // bl
  GameService *v17; // rax
  FamilyDungeonStu *pDungeonCfg; // [rsp+18h] [rbp-38h]
  Answer::NetPacket *packet; // [rsp+20h] [rbp-30h]
  int32_t FamilyDungeonState; // [rsp+2Ch] [rbp-24h]
  Answer::NetPacket *packet_0; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    FamilyId = CExtCharFamily::GetFamilyId(this);
    v2 = Answer::Singleton<FamilyManager>::instance();
    pDungeonCfg = FamilyManager::GetFamilyDungeonInfo(v2, FamilyId);
    if ( pDungeonCfg )
    {
      v9 = CExtCharFamily::GetFamilyId(this);
      v10 = Answer::Singleton<FamilyManager>::instance();
      if ( FamilyManager::GetFamilyDungeon(v10, v9) )
      {
        FamilyDungeonState = 1;
      }
      else if ( Answer::DayTime::daydiff(pDungeonCfg->StartTime) )
      {
        FamilyDungeonState = 0;
      }
      else
      {
        FamilyDungeonState = 2;
      }
      ConnId = Player::getConnId(this->m_pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      packet_0 = GameService::popNetpacket(v12, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F3Au);
      if ( packet_0 )
      {
        Answer::NetPacket::writeInt32(packet_0, FamilyDungeonState);
        Answer::NetPacket::writeInt32(packet_0, pDungeonCfg->StartCounts);
        v13 = 5;
        if ( pDungeonCfg->nMaxHard + 1 <= 5 )
          v13 = pDungeonCfg->nMaxHard + 1;
        Answer::NetPacket::writeInt32(packet_0, v13);
        WOffset = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v16 = Player::getConnId(this->m_pPlayer);
        v17 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v17, v16, GateIndex, packet_0);
      }
    }
    else
    {
      v3 = Player::getConnId(this->m_pPlayer);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, v3, Answer::PackType::PACK_DISPATCH, 0x2F3Au);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, 0);
        Answer::NetPacket::writeInt32(packet, 0);
        Answer::NetPacket::writeInt32(packet, 1);
        v5 = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, v5);
        v6 = Player::getGateIndex(this->m_pPlayer);
        v7 = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, v7, v6, packet);
      }
    }
  }
}


#####################################
int32_t __cdecl CExtCharFamily::onGetFamilyDungeonInfo(CExtCharFamily *const this, Answer::NetPacket *inPacket)
{
  CExtCharFamily::SendFamilyDungeonInfo(this);
  return 0;
}


