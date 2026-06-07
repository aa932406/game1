// Decompiled methods for class: CTianLing
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CTianLing::~CTianLing(CTianLing *const this)
{
  CTianLing::~CTianLing(this);
  operator delete(this);
}


#####################################
void __cdecl CTianLing::InitSystem(CTianLing *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  CFunctionOpen *v2; // rax
  CFunctionOpen *v3; // rax
  CfgData *v4; // rax
  int32_t nSunTelentLevel; // r12d
  int32_t nSunTelentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t nMoonTelentLevel; // r12d
  int32_t nMoonTelentId; // ebx
  CExtCharSkill *v10; // rax
  int32_t CurLevel; // [rsp+14h] [rbp-1Ch]
  const SunAndMoonCfg *CurCfg; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 175) && Player::getRecord(this->m_pPlayer, 1148) <= 0 )
      Player::updateRecord(this->m_pPlayer, 1148, 1);
    v2 = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(v2, 235) && Player::getRecord(this->m_pPlayer, 37501) <= 0 )
      Player::updateRecord(this->m_pPlayer, 37501, 1);
    v3 = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(v3, 240) )
    {
      if ( Player::getRecord(this->m_pPlayer, 37506) <= 0 )
        Player::updateRecord(this->m_pPlayer, 37506, 1);
      CurLevel = Player::getRecord(this->m_pPlayer, 37506);
      v4 = Answer::Singleton<CfgData>::instance();
      CurCfg = CfgData::GetSunAndMoonCfg(v4, CurLevel);
      if ( CurCfg->nSunTelentId > 0 && CurCfg->nSunTelentLevel > 0 )
      {
        nSunTelentLevel = CurCfg->nSunTelentLevel;
        nSunTelentId = CurCfg->nSunTelentId;
        CharSkill = Player::GetCharSkill(this->m_pPlayer);
        CExtCharSkill::AddOtherSkill(CharSkill, nSunTelentId, nSunTelentLevel);
      }
      if ( CurCfg->nMoonTelentId > 0 && CurCfg->nMoonTelentLevel > 0 )
      {
        nMoonTelentLevel = CurCfg->nMoonTelentLevel;
        nMoonTelentId = CurCfg->nMoonTelentId;
        v10 = Player::GetCharSkill(this->m_pPlayer);
        CExtCharSkill::AddOtherSkill(v10, nMoonTelentId, nMoonTelentLevel);
      }
    }
  }
}


#####################################
void __cdecl CTianLing::GetInterestsProtocol(CTianLing *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 261;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 259;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 263;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CTianLing::DispatchNetDatas(CTianLing *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x105u:
      return CTianLing::OnTianLingLevelUp(this, inPacket);
    case 0x107u:
      return CTianLing::OnSunAndMoonLevelUp(this, inPacket);
    case 0x103u:
      return CTianLing::OnZhanHunLevelUp(this, inPacket);
  }
  return 10002;
}


#####################################
void __cdecl CTianLing::InitTianLing(CTianLing *const this)
{
  if ( this->m_pPlayer )
    Player::updateRecord(this->m_pPlayer, 1148, 1);
}


#####################################
void __cdecl CTianLing::AddCharAttr(CTianLing *const this)
{
  CfgData *v1; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v3; // rax
  CfgData *v4; // rax
  int32_t v5; // ebx
  const AddAttribute *v6; // rax
  CfgData *v7; // rax
  int32_t v8; // ebx
  const AddAttribute *v9; // rax
  std::_List_const_iterator<AddAttribute> it_1; // [rsp+10h] [rbp-A0h] BYREF
  std::_List_const_iterator<AddAttribute> it_0; // [rsp+20h] [rbp-90h] BYREF
  std::_List_iterator<AddAttribute> it; // [rsp+30h] [rbp-80h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+40h] [rbp-70h] BYREF
  std::_List_const_iterator<AddAttribute> v14; // [rsp+50h] [rbp-60h] BYREF
  std::_List_const_iterator<AddAttribute> v15; // [rsp+60h] [rbp-50h] BYREF
  int32_t CurLevel; // [rsp+74h] [rbp-3Ch]
  TianLingCfg *CurCfg; // [rsp+78h] [rbp-38h]
  int32_t CurLevel_0; // [rsp+84h] [rbp-2Ch]
  const ZhanHunCfg *CurCfg_0; // [rsp+88h] [rbp-28h]
  int32_t CurLevel_1; // [rsp+94h] [rbp-1Ch]
  const SunAndMoonCfg *CurCfg_1; // [rsp+98h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    CurLevel = Player::getRecord(this->m_pPlayer, 1148);
    v1 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetTianLingCfg(v1, CurLevel);
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
      }
    }
    CurLevel_0 = Player::getRecord(this->m_pPlayer, 37501);
    v4 = Answer::Singleton<CfgData>::instance();
    CurCfg_0 = CfgData::GetZhanHunCfg(v4, CurLevel_0);
    if ( CurCfg_0 )
    {
      for ( it_0._M_node = std::list<AddAttribute>::begin(&CurCfg_0->lAddAttrs)._M_node;
            ;
            std::_List_const_iterator<AddAttribute>::operator++(&it_0, 0) )
      {
        v14._M_node = std::list<AddAttribute>::end(&CurCfg_0->lAddAttrs)._M_node;
        if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_0, &v14) )
          break;
        v5 = std::_List_const_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
        v6 = std::_List_const_iterator<AddAttribute>::operator->(&it_0);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v6->m_nAddAttrType, v5);
      }
    }
    CurLevel_1 = Player::getRecord(this->m_pPlayer, 37506);
    v7 = Answer::Singleton<CfgData>::instance();
    CurCfg_1 = CfgData::GetSunAndMoonCfg(v7, CurLevel_1);
    if ( CurCfg_1 )
    {
      for ( it_1._M_node = std::list<AddAttribute>::begin(&CurCfg_1->lAttr)._M_node;
            ;
            std::_List_const_iterator<AddAttribute>::operator++(&it_1, 0) )
      {
        v15._M_node = std::list<AddAttribute>::end(&CurCfg_1->lAttr)._M_node;
        if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_1, &v15) )
          break;
        v8 = std::_List_const_iterator<AddAttribute>::operator->(&it_1)->m_nAddAttrValue;
        v9 = std::_List_const_iterator<AddAttribute>::operator->(&it_1);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v9->m_nAddAttrType, v8);
      }
    }
  }
}


#####################################
int32_t __cdecl CTianLing::OnTianLingLevelUp(CTianLing *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CfgData *v4; // rax
  CExtCurrency *Currency; // rax
  CExtCharBag *Bag; // rax
  int64_t CostMoney; // rbx
  CExtCurrency *v8; // rax
  ChrTask *Task; // rax
  int32_t Record; // ebx
  CSevenDayTask *CSevenDayTask; // rax
  int8_t ConnId; // bl
  GameService *v13; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v16; // bl
  GameService *v17; // rax
  int8_t v18; // bl
  DBService *v19; // rax
  important_system_log stu; // [rsp+10h] [rbp-A0h] BYREF
  std::string val; // [rsp+50h] [rbp-60h] BYREF
  _BYTE v23[16]; // [rsp+60h] [rbp-50h] BYREF
  _BYTE v24[20]; // [rsp+70h] [rbp-40h] BYREF
  int32_t CurLevel; // [rsp+84h] [rbp-2Ch]
  TianLingCfg *CurCfg; // [rsp+88h] [rbp-28h]
  TianLingCfg *NextCfg; // [rsp+90h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CurLevel = Player::getRecord(this->m_pPlayer, 1148);
  v3 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetTianLingCfg(v3, CurLevel);
  v4 = Answer::Singleton<CfgData>::instance();
  NextCfg = CfgData::GetTianLingCfg(v4, CurLevel + 1);
  if ( !CurCfg || !NextCfg )
    return 10002;
  if ( CurCfg->CostMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < CurCfg->CostMoney )
      return 10002;
  }
  if ( CurCfg->CostCoin > 0 && Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_VIGOUR) < CurCfg->CostCoin )
    return 10002;
  if ( std::list<ItemData>::size(&CurCfg->CostItems) )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(Bag, &CurCfg->CostItems, ITEM_CHANGE_REASON::ICR_TIAN_LING_LEVEL) )
      return 10002;
  }
  if ( CurCfg->CostMoney > 0 )
  {
    CostMoney = CurCfg->CostMoney;
    v8 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v8, CostMoney, CURRENCY_CHANGE_REASON::MCR_TIAN_LING_LEVEL_UP, 0) )
      return 10002;
  }
  if ( CurCfg->CostCoin <= 0
    || Player::DecCurrency(
         this->m_pPlayer,
         CURRENCY_TYPE::CURRENCY_VIGOUR,
         CurCfg->CostCoin,
         CURRENCY_CHANGE_REASON::MCR_TIAN_LING_LEVEL_UP,
         0) )
  {
    Player::updateRecord(this->m_pPlayer, 1148, CurLevel + 1);
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::updateTaskCount(Task, 37, 0);
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_TIAN_LIN, CurLevel + 1);
    Record = Player::getRecord(this->m_pPlayer, 1148);
    CSevenDayTask = Player::GetCSevenDayTask(this->m_pPlayer);
    CSevenDayTask::UpdateTaskState(CSevenDayTask, 2, Record, 1);
    Player::RecalcAttr(this->m_pPlayer);
    Player::SetNeedSyncAround(this->m_pPlayer);
    Player::SetNeedSync(this->m_pPlayer);
    if ( NextCfg->GongGaoId > 0 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v13, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
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
      v16 = Player::getConnId(this->m_pPlayer);
      v17 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v17, v16, packet);
    }
    important_system_log::important_system_log(&stu);
    stu.log_Sid = Player::getSid(this->m_pPlayer);
    stu.log_time = Unit::getNow(this->m_pPlayer);
    Player::GetPassport((Player *const)v23);
    std::string::operator=(&stu.passport, v23);
    std::string::~string(v23);
    stu.cid = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)v24);
    std::string::operator=(&stu.name, v24);
    std::string::~string(v24);
    stu.up_time = Unit::getNow(this->m_pPlayer);
    stu.sys_name = 1;
    stu.oper_id = 1;
    stu.level = CurLevel + 1;
    v18 = Player::getConnId(this->m_pPlayer);
    v19 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v19, v18, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
    v2 = 0;
    important_system_log::~important_system_log(&stu);
    return v2;
  }
  return 10002;
}


#####################################
void __cdecl CTianLing::InitZhanHun(CTianLing *const this)
{
  if ( this->m_pPlayer )
    Player::updateRecord(this->m_pPlayer, 37501, 1);
}


#####################################
int32_t __cdecl CTianLing::OnZhanHunLevelUp(CTianLing *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgData *v4; // rax
  CExtCurrency *Currency; // rax
  int64_t nMoney; // rbx
  CExtCurrency *v7; // rax
  int8_t ConnId; // bl
  GameService *v9; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v12; // bl
  GameService *v13; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  int32_t CurLevel; // [rsp+24h] [rbp-2Ch]
  const ZhanHunCfg *CurCfg; // [rsp+28h] [rbp-28h]
  const ZhanHunCfg *NextCfg; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CurLevel = Player::getRecord(this->m_pPlayer, 37501);
  v3 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetZhanHunCfg(v3, CurLevel);
  v4 = Answer::Singleton<CfgData>::instance();
  NextCfg = CfgData::GetZhanHunCfg(v4, CurLevel + 1);
  if ( !CurCfg || !NextCfg )
    return 10002;
  if ( CurCfg->nMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < CurCfg->nMoney )
      return 10002;
  }
  if ( CurCfg->nSyb > 0 && Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_VIGOUR) < CurCfg->nSyb )
    return 10002;
  if ( CurCfg->nMoney > 0 )
  {
    nMoney = CurCfg->nMoney;
    v7 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v7, nMoney, CURRENCY_CHANGE_REASON::MCR_TIAN_LING_LEVEL_UP, 0) )
      return 10002;
  }
  if ( CurCfg->nSyb > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_VIGOUR,
          CurCfg->nSyb,
          CURRENCY_CHANGE_REASON::MCR_TIAN_LING_LEVEL_UP,
          0) )
  {
    return 10002;
  }
  Player::updateRecord(this->m_pPlayer, 37501, CurLevel + 1);
  Player::RecalcAttr(this->m_pPlayer);
  if ( NextCfg->nGongGaoId > 0 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v9, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 10002;
    Answer::NetPacket::writeInt32(packet, NextCfg->nGongGaoId);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt32(packet, CurLevel + 1);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v12 = Player::getConnId(this->m_pPlayer);
    v13 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v13, v12, packet);
  }
  return 0;
}


#####################################
void __cdecl CTianLing::InitSunAndMoon(CTianLing *const this)
{
  CfgData *v1; // rax
  int32_t nSunTelentLevel; // r12d
  int32_t nSunTelentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t nMoonTelentLevel; // r12d
  int32_t nMoonTelentId; // ebx
  CExtCharSkill *v7; // rax
  const SunAndMoonCfg *CurCfg; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::updateRecord(this->m_pPlayer, 37506, 1);
    v1 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetSunAndMoonCfg(v1, 1);
    if ( CurCfg->nSunTelentId > 0 && CurCfg->nSunTelentLevel > 0 )
    {
      nSunTelentLevel = CurCfg->nSunTelentLevel;
      nSunTelentId = CurCfg->nSunTelentId;
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(CharSkill, nSunTelentId, nSunTelentLevel);
    }
    if ( CurCfg->nMoonTelentId > 0 && CurCfg->nMoonTelentLevel > 0 )
    {
      nMoonTelentLevel = CurCfg->nMoonTelentLevel;
      nMoonTelentId = CurCfg->nMoonTelentId;
      v7 = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(v7, nMoonTelentId, nMoonTelentLevel);
    }
  }
}


#####################################
int32_t __cdecl CTianLing::OnSunAndMoonLevelUp(CTianLing *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int32_t v4; // r12d
  CfgData *v5; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *Bag; // rax
  ItemData *v9; // rax
  ItemData *v10; // rax
  ItemData *v11; // rax
  int32_t v12; // r13d
  int8_t v13; // r12
  CfgData *v14; // rax
  int v15; // r12d
  std::_List_iterator<ItemData> v16; // rax
  int64_t Currency; // rax
  CExtCharBag *v19; // rax
  ItemDataList *p_lConstItems; // r12
  CExtCharBag *v23; // rax
  int32_t nSunTelentLevel; // r12d
  int32_t nSunTelentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t v28; // r12d
  int32_t v29; // ebx
  CExtCharSkill *v30; // rax
  int32_t nMoonTelentLevel; // r12d
  int32_t nMoonTelentId; // ebx
  CExtCharSkill *v33; // rax
  int32_t v34; // r12d
  int32_t v35; // ebx
  CExtCharSkill *v36; // rax
  int8_t ConnId; // bl
  GameService *v38; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v41; // bl
  GameService *v42; // rax
  std::_List_iterator<ItemData> iter; // [rsp+10h] [rbp-B0h] BYREF
  ItemDataList costItemList; // [rsp+20h] [rbp-A0h] BYREF
  Int32Vector vSlot; // [rsp+30h] [rbp-90h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+50h] [rbp-70h] BYREF
  std::string val; // [rsp+60h] [rbp-60h] BYREF
  int8_t nAutoBuy; // [rsp+6Bh] [rbp-55h]
  int32_t CurLevel; // [rsp+6Ch] [rbp-54h]
  const SunAndMoonCfg *CurCfg; // [rsp+70h] [rbp-50h]
  const SunAndMoonCfg *NextCfg; // [rsp+78h] [rbp-48h]
  int32_t nCostGold; // [rsp+84h] [rbp-3Ch]
  int32_t nBuyCount; // [rsp+88h] [rbp-38h]
  int32_t nItemCount; // [rsp+8Ch] [rbp-34h]
  CfgGameShop *pCfgGameShop; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nAutoBuy = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    CurLevel = Player::getRecord(this->m_pPlayer, 37506);
    v3 = Answer::Singleton<CfgData>::instance();
    CurCfg = CfgData::GetSunAndMoonCfg(v3, CurLevel);
    v4 = CurLevel + 1;
    v5 = Answer::Singleton<CfgData>::instance();
    NextCfg = CfgData::GetSunAndMoonCfg(v5, v4);
    if ( !CurCfg || !NextCfg )
    {
      v2 = 10002;
LABEL_63:
      std::vector<int>::~vector(&vSlot);
      return v2;
    }
    if ( nAutoBuy )
    {
      nCostGold = 0;
      std::list<ItemData>::list(&costItemList, &CurCfg->lConstItems);
      iter._M_node = std::list<ItemData>::begin(&costItemList)._M_node;
      while ( 1 )
      {
        __x._M_node = std::list<ItemData>::end(&costItemList)._M_node;
        if ( !std::_List_iterator<ItemData>::operator!=(&iter, &__x) )
          break;
        nBuyCount = 0;
        m_nId = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
        m_nClass = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
        Bag = Player::GetBag(this->m_pPlayer);
        nItemCount = CExtCharBag::GetItemCount(Bag, &vSlot, m_nClass, m_nId);
        v9 = std::_List_iterator<ItemData>::operator->(&iter);
        if ( v9->m_nCount > nItemCount )
        {
          v10 = std::_List_iterator<ItemData>::operator->(&iter);
          nBuyCount = v10->m_nCount - nItemCount;
          v11 = std::_List_iterator<ItemData>::operator->(&iter);
          v11->m_nCount = nItemCount;
        }
        if ( nBuyCount > 0 )
        {
          v12 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
          v13 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
          v14 = Answer::Singleton<CfgData>::instance();
          pCfgGameShop = CfgData::GetGameShopItem(v14, v13, v12);
          if ( !pCfgGameShop )
          {
            v2 = 2;
            v15 = 0;
            goto LABEL_38;
          }
          nCostGold += nBuyCount * pCfgGameShop->Price;
        }
        if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
        {
          std::_List_iterator<ItemData>::operator++(&iter);
        }
        else
        {
          v16._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
          std::list<ItemData>::erase(&costItemList, v16);
        }
      }
      if ( nCostGold > 0
        && (Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), Currency < nCostGold) )
      {
        v2 = 10002;
        v15 = 0;
      }
      else if ( !std::list<ItemData>::empty(&costItemList)
             && (v19 = Player::GetBag(this->m_pPlayer),
                 !CExtCharBag::RemoveItem(v19, &vSlot, &costItemList, ITEM_CHANGE_REASON::IDCR_SUN_AND_MOON_LEVEL_UP)) )
      {
        v2 = 10002;
        v15 = 0;
      }
      else if ( nCostGold > 0
             && !Player::DecCurrency(
                   this->m_pPlayer,
                   CURRENCY_TYPE::CURRENCY_GOLD,
                   nCostGold,
                   CURRENCY_CHANGE_REASON::GCR_SUN_AND_MOON_LEVEL_UP,
                   0) )
      {
        v2 = 10002;
        v15 = 0;
      }
      else
      {
        v15 = 1;
      }
LABEL_38:
      std::list<ItemData>::~list(&costItemList);
      if ( !v15 )
        goto LABEL_63;
    }
    else if ( !std::list<ItemData>::empty(&CurCfg->lConstItems) )
    {
      p_lConstItems = &CurCfg->lConstItems;
      v23 = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::RemoveItem(v23, &vSlot, p_lConstItems, ITEM_CHANGE_REASON::IDCR_SUN_AND_MOON_LEVEL_UP) )
      {
        v2 = 10002;
        goto LABEL_63;
      }
    }
    Player::updateRecord(this->m_pPlayer, 37506, CurLevel + 1);
    if ( CurCfg->nSunTelentId > 0 && CurCfg->nSunTelentLevel > 0 )
    {
      nSunTelentLevel = CurCfg->nSunTelentLevel;
      nSunTelentId = CurCfg->nSunTelentId;
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::removeSkillByTalent(CharSkill, nSunTelentId, nSunTelentLevel);
    }
    if ( NextCfg->nSunTelentId > 0 && NextCfg->nSunTelentLevel > 0 )
    {
      v28 = NextCfg->nSunTelentLevel;
      v29 = NextCfg->nSunTelentId;
      v30 = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(v30, v29, v28);
    }
    if ( CurCfg->nMoonTelentId > 0 && CurCfg->nMoonTelentLevel > 0 )
    {
      nMoonTelentLevel = CurCfg->nMoonTelentLevel;
      nMoonTelentId = CurCfg->nMoonTelentId;
      v33 = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::removeSkillByTalent(v33, nMoonTelentId, nMoonTelentLevel);
    }
    if ( NextCfg->nMoonTelentId > 0 && NextCfg->nMoonTelentLevel > 0 )
    {
      v34 = NextCfg->nMoonTelentLevel;
      v35 = NextCfg->nMoonTelentId;
      v36 = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(v36, v35, v34);
    }
    if ( NextCfg->nGongGaoId > 0 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v38 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v38, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( !packet )
      {
        v2 = 10002;
        goto LABEL_63;
      }
      Answer::NetPacket::writeInt32(packet, NextCfg->nGongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, CurLevel + 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v41 = Player::getConnId(this->m_pPlayer);
      v42 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v42, v41, packet);
    }
    Player::RecalcAttr(this->m_pPlayer);
    v2 = 0;
    goto LABEL_63;
  }
  return 10002;
}


#####################################
bool __cdecl CTianLing::GetMonsterItem(CTianLing *const this, MemChrBag item)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t CurLevel; // [rsp+1Ch] [rbp-14h]
  const SunAndMoonCfg *CurCfg; // [rsp+20h] [rbp-10h]

  if ( !this->m_pPlayer || item.itemId <= 0 || item.itemClass <= 0 || item.itemCount <= 0 )
    return 0;
  CurLevel = Player::getRecord(this->m_pPlayer, 37506);
  v3 = Answer::Singleton<CfgData>::instance();
  CurCfg = CfgData::GetSunAndMoonCfg(v3, CurLevel);
  if ( !CurCfg )
    return 0;
  if ( CurCfg->nGetItemTimes - Player::getRecord(this->m_pPlayer, 2131) <= 0 )
  {
    Player::TiShiInfo(this->m_pPlayer, 32, 0);
    return 0;
  }
  else
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( CExtCharBag::AddItem(Bag, &item, ITEM_CHANGE_REASON::IDCR_MOON_SKILL_GET) )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 2131, 1);
      return 1;
    }
    else
    {
      Player::TiShiInfo(this->m_pPlayer, 2048, 0);
      return 0;
    }
  }
}


