// Decompiled methods for class: CExtCharWing
// Source: gameserver.cc
// Total methods: 15

#####################################
void __cdecl CExtCharWing::~CExtCharWing(CExtCharWing *const this)
{
  CExtCharWing::~CExtCharWing(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharWing::OnCleanUp(CExtCharWing *const this)
{
  this->m_Level = 0;
  this->m_Luck = 0;
  this->m_LaseUpdateTick = 0;
  this->m_HuanHua = 0;
}


#####################################
void __cdecl CExtCharWing::OnLoadFromDB(CExtCharWing *const this, const PlayerDBData *const dbData)
{
  int32_t m_Level; // ebx
  CfgData *v3; // rax
  const CfgWingTable *WingTable; // rax
  int32_t SkillLevel; // r12d
  int32_t SkillId; // ebx
  CExtCharSkill *CharSkill; // rax
  const WingCfg *pWingCfg; // [rsp+18h] [rbp-18h]

  this->m_Level = dbData->m_CharWingDBData.m_Level;
  this->m_Luck = dbData->m_CharWingDBData.m_Luck;
  this->m_HuanHua = dbData->m_CharWingDBData.m_HuanHua;
  if ( !this->m_HuanHua )
    this->m_HuanHua = this->m_Level;
  m_Level = this->m_Level;
  v3 = Answer::Singleton<CfgData>::instance();
  WingTable = CfgData::GetWingTable(v3);
  pWingCfg = CfgWingTable::GetWingCfg(WingTable, m_Level);
  if ( pWingCfg && pWingCfg->SkillId > 0 && pWingCfg->SkillLevel > 0 )
  {
    SkillLevel = pWingCfg->SkillLevel;
    SkillId = pWingCfg->SkillId;
    CharSkill = Player::GetCharSkill(this->m_pPlayer);
    CExtCharSkill::AddOtherSkill(CharSkill, SkillId, SkillLevel);
  }
}


#####################################
void __cdecl CExtCharWing::OnSaveToDB(CExtCharWing *const this, PlayerDBData *const dbData)
{
  dbData->m_CharWingDBData.m_Level = this->m_Level;
  dbData->m_CharWingDBData.m_Luck = this->m_Luck;
  dbData->m_CharWingDBData.m_HuanHua = this->m_HuanHua;
}


#####################################
void __cdecl CExtCharWing::GetInterestsProtocol(CExtCharWing *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 760;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 761;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 762;
  std::list<unsigned short>::push_back(procList, &v4);
}


#####################################
int32_t __cdecl CExtCharWing::DispatchNetDatas(CExtCharWing *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( !CExtCharWing::IsFunctionOpen(this) )
    return 10002;
  switch ( nProcId )
  {
    case 0x2F9u:
      return CExtCharWing::onWingUpLevel(this, inPacket);
    case 0x2FAu:
      return CExtCharWing::onWingHuanHua(this, inPacket);
    case 0x2F8u:
      return CExtCharWing::onRequestInfo(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharWing::onWingHuanHua(CExtCharWing *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgWingTable *WingTable; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  int32_t Level; // [rsp+14h] [rbp-2Ch]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Level = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  WingTable = CfgData::GetWingTable(v3);
  if ( !CfgWingTable::GetWingCfg(WingTable, Level) )
    return 10002;
  this->m_HuanHua = Level;
  Player::SetNeedSyncAround(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, Level);
  return 0;
}


#####################################
int32_t __cdecl CExtCharWing::onRequestInfo(CExtCharWing *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  CExtCharWing::SendWingInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharWing::onWingUpLevel(CExtCharWing *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t m_Level; // r12d
  CfgData *v4; // rax
  const CfgWingTable *WingTable; // rax
  int32_t v6; // r12d
  CfgData *v7; // rax
  const CfgWingTable *v8; // rax
  int32_t m_nId; // r13d
  int8_t m_nClass; // r12
  CExtCharBag *Bag; // rax
  ItemData *v12; // rax
  ItemData *v13; // rax
  ItemData *v14; // rax
  int32_t v15; // r13d
  int8_t v16; // r12
  CfgData *v17; // rax
  int v18; // r12d
  std::_List_iterator<ItemData> v19; // rax
  int64_t Currency; // rax
  CExtCharBag *v22; // rax
  ItemDataList *p_ConstItems; // r12
  CExtCharBag *v26; // rax
  int32_t m_nCount; // r12d
  Player *m_pPlayer; // rbx
  CUniteServer *v30; // rax
  Answer::Random *v31; // rax
  int32_t SkillLevel; // r12d
  int32_t SkillId; // ebx
  CExtCharSkill *CharSkill; // rax
  int32_t v35; // r12d
  int32_t v36; // ebx
  CExtCharSkill *v37; // rax
  int8_t ConnId; // bl
  GameService *v39; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v42; // bl
  GameService *v43; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t v46; // bl
  GameService *v47; // rax
  Player *v48; // rbx
  CKaiFuHuoDong *v49; // rax
  DBService *v50; // rax
  CSevenDayTask *CSevenDayTask; // rax
  int32_t FailAddPoints; // r14d
  uint16_t v53; // r13
  int16_t v54; // r12
  int8_t v55; // bl
  GameService *v56; // rax
  important_system_log stu; // [rsp+10h] [rbp-150h] BYREF
  std::_List_iterator<ItemData> iter_0; // [rsp+50h] [rbp-110h] BYREF
  ItemDataList costItemList_0; // [rsp+60h] [rbp-100h] BYREF
  std::_List_iterator<ItemData> iter; // [rsp+70h] [rbp-F0h] BYREF
  ItemDataList costItemList; // [rsp+80h] [rbp-E0h] BYREF
  Int32Vector vSlot; // [rsp+90h] [rbp-D0h] BYREF
  std::_List_iterator<ItemData> __x; // [rsp+B0h] [rbp-B0h] BYREF
  std::_List_iterator<ItemData> v65; // [rsp+C0h] [rbp-A0h] BYREF
  std::string val; // [rsp+D0h] [rbp-90h] BYREF
  _BYTE v67[16]; // [rsp+E0h] [rbp-80h] BYREF
  _BYTE v68[23]; // [rsp+F0h] [rbp-70h] BYREF
  int8_t nAutoBuy; // [rsp+107h] [rbp-59h]
  const WingCfg *pWingCfg; // [rsp+108h] [rbp-58h]
  const WingCfg *pNextWingCfg; // [rsp+110h] [rbp-50h]
  bool Success; // [rsp+11Bh] [rbp-45h]
  int32_t nCostGold; // [rsp+11Ch] [rbp-44h]
  int32_t nBuyCount; // [rsp+120h] [rbp-40h]
  int32_t nItemCount; // [rsp+124h] [rbp-3Ch]
  CfgGameShop *pCfgGameShop; // [rsp+128h] [rbp-38h]
  int32_t nRand; // [rsp+134h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+138h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nAutoBuy = Answer::NetPacket::readInt8(inPacket);
    std::vector<int>::vector(&vSlot);
    Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
    m_Level = this->m_Level;
    v4 = Answer::Singleton<CfgData>::instance();
    WingTable = CfgData::GetWingTable(v4);
    pWingCfg = CfgWingTable::GetWingCfg(WingTable, m_Level);
    if ( pWingCfg )
    {
      v6 = this->m_Level + 1;
      v7 = Answer::Singleton<CfgData>::instance();
      v8 = CfgData::GetWingTable(v7);
      pNextWingCfg = CfgWingTable::GetWingCfg(v8, v6);
      if ( pNextWingCfg )
      {
        if ( nAutoBuy )
        {
          nCostGold = 0;
          std::list<ItemData>::list(&costItemList, &pWingCfg->ConstItems);
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
            v12 = std::_List_iterator<ItemData>::operator->(&iter);
            if ( v12->m_nCount > nItemCount )
            {
              v13 = std::_List_iterator<ItemData>::operator->(&iter);
              nBuyCount = v13->m_nCount - nItemCount;
              v14 = std::_List_iterator<ItemData>::operator->(&iter);
              v14->m_nCount = nItemCount;
            }
            if ( nBuyCount > 0 )
            {
              v15 = std::_List_iterator<ItemData>::operator->(&iter)->m_nId;
              v16 = std::_List_iterator<ItemData>::operator->(&iter)->m_nClass;
              v17 = Answer::Singleton<CfgData>::instance();
              pCfgGameShop = CfgData::GetGameShopItem(v17, v16, v15);
              if ( !pCfgGameShop )
              {
                v2 = 2;
                v18 = 0;
                goto LABEL_39;
              }
              nCostGold += nBuyCount * pCfgGameShop->Price;
            }
            if ( std::_List_iterator<ItemData>::operator->(&iter)->m_nCount > 0 )
            {
              std::_List_iterator<ItemData>::operator++(&iter);
            }
            else
            {
              v19._M_node = std::_List_iterator<ItemData>::operator++(&iter, 0)._M_node;
              std::list<ItemData>::erase(&costItemList, v19);
            }
          }
          if ( nCostGold > 0
            && (Currency = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD), Currency < nCostGold) )
          {
            v2 = 10002;
            v18 = 0;
          }
          else if ( !std::list<ItemData>::empty(&costItemList)
                 && (v22 = Player::GetBag(this->m_pPlayer),
                     !CExtCharBag::RemoveItem(v22, &vSlot, &costItemList, ITEM_CHANGE_REASON::ICR_WING_SMITH)) )
          {
            v2 = 10002;
            v18 = 0;
          }
          else if ( nCostGold > 0
                 && !Player::DecCurrency(
                       this->m_pPlayer,
                       CURRENCY_TYPE::CURRENCY_GOLD,
                       nCostGold,
                       CURRENCY_CHANGE_REASON::GCR_PET_UPSTAR_AUTOBUY,
                       0) )
          {
            v2 = 10002;
            v18 = 0;
          }
          else
          {
            v18 = 1;
          }
LABEL_39:
          std::list<ItemData>::~list(&costItemList);
          if ( !v18 )
            goto LABEL_73;
        }
        else if ( !std::list<ItemData>::empty(&pWingCfg->ConstItems) )
        {
          p_ConstItems = &pWingCfg->ConstItems;
          v26 = Player::GetBag(this->m_pPlayer);
          if ( !CExtCharBag::RemoveItem(v26, &vSlot, p_ConstItems, ITEM_CHANGE_REASON::ICR_WING_SMITH) )
          {
            v2 = 10002;
            goto LABEL_73;
          }
        }
        std::list<ItemData>::list(&costItemList_0, &pWingCfg->ConstItems);
        for ( iter_0._M_node = std::list<ItemData>::begin(&costItemList_0)._M_node;
              ;
              std::_List_iterator<ItemData>::operator++(&iter_0) )
        {
          v65._M_node = std::list<ItemData>::end(&costItemList_0)._M_node;
          if ( !std::_List_iterator<ItemData>::operator!=(&iter_0, &v65) )
            break;
          m_nCount = std::_List_iterator<ItemData>::operator->(&iter_0)->m_nCount;
          m_pPlayer = this->m_pPlayer;
          v30 = Answer::Singleton<CUniteServer>::instance();
          CUniteServer::AddWingLevelUp(v30, m_pPlayer, m_nCount);
        }
        std::list<ItemData>::~list(&costItemList_0);
        Success = 0;
        if ( this->m_Luck < pWingCfg->SuccessPoints )
        {
          if ( this->m_Luck >= pWingCfg->StartPoints )
          {
            v31 = Answer::Singleton<Answer::Random>::instance();
            nRand = Answer::Random::generate(v31, 1, 10000);
            if ( pWingCfg->Rate >= nRand )
              Success = 1;
          }
        }
        else
        {
          Success = 1;
        }
        if ( Success )
        {
          if ( this->m_Level == this->m_HuanHua )
            ++this->m_HuanHua;
          *(_QWORD *)&this->m_Level = (unsigned int)(this->m_Level + 1);
          if ( pWingCfg->SkillId > 0 && pWingCfg->SkillLevel > 0 )
          {
            SkillLevel = pWingCfg->SkillLevel;
            SkillId = pWingCfg->SkillId;
            CharSkill = Player::GetCharSkill(this->m_pPlayer);
            CExtCharSkill::removeSkillByTalent(CharSkill, SkillId, SkillLevel);
          }
          if ( pNextWingCfg->SkillId > 0 && pNextWingCfg->SkillLevel > 0 )
          {
            v35 = pNextWingCfg->SkillLevel;
            v36 = pNextWingCfg->SkillId;
            v37 = Player::GetCharSkill(this->m_pPlayer);
            CExtCharSkill::AddOtherSkill(v37, v36, v35);
          }
          if ( pNextWingCfg->GongGaoId > 0 )
          {
            ConnId = Player::getConnId(this->m_pPlayer);
            v39 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v39, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( !packet )
            {
              v2 = 10002;
              goto LABEL_73;
            }
            Answer::NetPacket::writeInt32(packet, pNextWingCfg->GongGaoId);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Answer::NetPacket::writeInt32(packet, this->m_Level);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v42 = Player::getConnId(this->m_pPlayer);
            v43 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v43, v42, packet);
          }
          Player::recalcAttr(this->m_pPlayer, 0, 0);
          Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_WING, this->m_Level);
          Proc = Answer::NetPacket::getProc(inPacket);
          GateIndex = Player::getGateIndex(this->m_pPlayer);
          v46 = Player::getConnId(this->m_pPlayer);
          v47 = Answer::Singleton<GameService>::instance();
          GameService::replySuccess(v47, v46, GateIndex, Proc, 0);
          Player::SetNeedSyncAround(this->m_pPlayer);
          v48 = this->m_pPlayer;
          v49 = Answer::Singleton<CKaiFuHuoDong>::instance();
          CKaiFuHuoDong::SendKaiFuHuoDongIcon(v49, v48);
          important_system_log::important_system_log(&stu);
          stu.log_Sid = Player::getSid(this->m_pPlayer);
          stu.log_time = Unit::getNow(this->m_pPlayer);
          Player::GetPassport((Player *const)v67);
          std::string::operator=(&stu.passport, v67);
          std::string::~string(v67);
          stu.cid = Player::getCid(this->m_pPlayer);
          Player::getName((const Player *const)v68);
          std::string::operator=(&stu.name, v68);
          std::string::~string(v68);
          stu.up_time = Unit::getNow(this->m_pPlayer);
          stu.sys_name = 10;
          stu.oper_id = 1;
          stu.level = this->m_Level;
          LOBYTE(v48) = Player::getConnId(this->m_pPlayer);
          v50 = Answer::Singleton<DBService>::instance();
          DBService::AddPlatformLog(v50, (int8_t)v48, PLATFORM_LOG_DATA_TYPE::PLDT_SYSTEM, &stu);
          LODWORD(v48) = this->m_Level;
          CSevenDayTask = Player::GetCSevenDayTask(this->m_pPlayer);
          CSevenDayTask::UpdateTaskState(CSevenDayTask, 3, (int32_t)v48, 1);
          important_system_log::~important_system_log(&stu);
        }
        else
        {
          this->m_Luck += pWingCfg->FailAddPoints;
          if ( this->m_Luck > pWingCfg->MaxPoints )
            this->m_Luck = pWingCfg->MaxPoints;
          FailAddPoints = pWingCfg->FailAddPoints;
          v53 = Answer::NetPacket::getProc(inPacket);
          v54 = Player::getGateIndex(this->m_pPlayer);
          v55 = Player::getConnId(this->m_pPlayer);
          v56 = Answer::Singleton<GameService>::instance();
          GameService::replyfailure(v56, v55, v54, v53, FailAddPoints, 0);
        }
        CExtCharWing::SendWingInfo(this);
        v2 = 0;
        goto LABEL_73;
      }
      v2 = 10002;
    }
    else
    {
      v2 = 10002;
    }
LABEL_73:
    std::vector<int>::~vector(&vSlot);
    return v2;
  }
  return 10002;
}


#####################################
bool __cdecl CExtCharWing::LevelUp(
        CExtCharWing *const this,
        int32_t UseWingLevel,
        int32_t UpLevel,
        int32_t ItemId,
        int32_t itemCount)
{
  int32_t v6; // ebx
  CfgData *v7; // rax
  const CfgWingTable *WingTable; // rax
  int8_t ConnId; // bl
  GameService *v10; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v13; // bl
  GameService *v14; // rax
  Player *m_pPlayer; // rbx
  CKaiFuHuoDong *v16; // rax
  CExtCharBag *Bag; // rax
  MemChrBag stu; // [rsp+20h] [rbp-50h] BYREF
  std::string val; // [rsp+40h] [rbp-30h] BYREF
  const WingCfg *pWingCfg; // [rsp+50h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  if ( !this->m_pPlayer || UseWingLevel <= 0 || UpLevel <= 0 || ItemId <= 0 || itemCount <= 0 )
    return 0;
  if ( CExtCharWing::GetLevel(this) < UseWingLevel )
    return 0;
  if ( CExtCharWing::GetLevel(this) == UseWingLevel )
  {
    v6 = UpLevel + CExtCharWing::GetLevel(this);
    v7 = Answer::Singleton<CfgData>::instance();
    WingTable = CfgData::GetWingTable(v7);
    pWingCfg = CfgWingTable::GetWingCfg(WingTable, v6);
    if ( !pWingCfg )
      return 0;
    if ( this->m_Level == this->m_HuanHua )
      this->m_HuanHua += UpLevel;
    this->m_Level += UpLevel;
    if ( pWingCfg->GongGaoId > 0 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v10, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( !packet )
        return 1;
      Answer::NetPacket::writeInt32(packet, pWingCfg->GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt32(packet, this->m_Level);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v13 = Player::getConnId(this->m_pPlayer);
      v14 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v14, v13, packet);
    }
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_WING, this->m_Level);
    CExtCharWing::SendWingInfo(this);
    m_pPlayer = this->m_pPlayer;
    v16 = Answer::Singleton<CKaiFuHuoDong>::instance();
    CKaiFuHuoDong::SendKaiFuHuoDongIcon(v16, m_pPlayer);
    return 1;
  }
  else
  {
    *(_DWORD *)&stu.itemClass = 1;
    *(_DWORD *)&stu.bind = 1;
    *(_QWORD *)&stu.endTime = 0;
    stu.srcId = 0;
    stu.itemId = ItemId;
    stu.itemCount = itemCount;
    Bag = Player::GetBag(this->m_pPlayer);
    return CExtCharBag::AddItem(Bag, &stu, ITEM_CHANGE_REASON::ICR_USE_WING_LEVEL_ITEM);
  }
}


#####################################
void __cdecl CExtCharWing::OnDaySwitch(CExtCharWing *const this, int32_t nDiffDays)
{
  int32_t m_Level; // ebx
  CfgData *v3; // rax
  const CfgWingTable *WingTable; // rax
  const WingCfg *pWingCfg; // [rsp+18h] [rbp-18h]

  m_Level = this->m_Level;
  v3 = Answer::Singleton<CfgData>::instance();
  WingTable = CfgData::GetWingTable(v3);
  pWingCfg = CfgWingTable::GetWingCfg(WingTable, m_Level);
  if ( pWingCfg )
  {
    if ( pWingCfg->IsClear > 0 )
      CExtCharWing::ClearLuck(this);
  }
}


#####################################
void __cdecl CExtCharWing::ClearLuck(CExtCharWing *const this)
{
  int32_t Now; // eax

  if ( this->m_pPlayer )
  {
    Now = Unit::getNow(this->m_pPlayer);
    Player::updateRecord(this->m_pPlayer, 1909, Now);
    this->m_Luck = 0;
    CExtCharWing::SendWingInfo(this);
  }
}


#####################################
void __cdecl CExtCharWing::SendWingInfo(CExtCharWing *const this)
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
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DDCu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_Level);
      Answer::NetPacket::writeInt32(packet, this->m_Luck);
      Answer::NetPacket::writeInt32(packet, this->m_HuanHua);
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
void __cdecl CExtCharWing::AddCharAttr(CExtCharWing *const this)
{
  int32_t m_Level; // ebx
  CfgData *v2; // rax
  const CfgWingTable *WingTable; // rax
  int32_t addon; // ebx
  const AttrAddon *v5; // rax
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<const AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+20h] [rbp-20h] BYREF
  const WingCfg *pWingCfg; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( CExtCharWing::IsFunctionOpen(this) )
    {
      m_Level = this->m_Level;
      v2 = Answer::Singleton<CfgData>::instance();
      WingTable = CfgData::GetWingTable(v2);
      pWingCfg = CfgWingTable::GetWingCfg(WingTable, m_Level);
      if ( pWingCfg )
      {
        for ( iter._M_current = std::vector<AttrAddon>::begin(&pWingCfg->AddonVector)._M_current;
              ;
              __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator++(&iter) )
        {
          __rhs._M_current = std::vector<AttrAddon>::end(&pWingCfg->AddonVector)._M_current;
          if ( !__gnu_cxx::operator!=<AttrAddon const*,std::vector<AttrAddon>>(&iter, &__rhs) )
            break;
          addon = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter)->addon;
          v5 = __gnu_cxx::__normal_iterator<AttrAddon const*,std::vector<AttrAddon>>::operator->(&iter);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->index, addon);
        }
      }
    }
  }
}


#####################################
bool __cdecl CExtCharWing::IsFunctionOpen(CExtCharWing *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  bool result; // al

  result = 0;
  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 140) )
      return 1;
  }
  return result;
}


