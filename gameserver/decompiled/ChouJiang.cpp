// Decompiled methods for class: ChouJiang
// Source: gameserver.cc
// Total methods: 32

#####################################
void __cdecl ChouJiang::~ChouJiang(ChouJiang *const this)
{
  ChouJiang::~ChouJiang(this);
  operator delete(this);
}


#####################################
void __cdecl ChouJiang::OnCleanUp(ChouJiang *const this)
{
  std::list<ChouJiangRecord>::clear(&this->m_RecordList);
  this->m_LuckyPoint = 0;
  bzero(this->m_ItemList, 0x3D40u);
  this->m_WeekReward = 0;
}


#####################################
void __cdecl ChouJiang::OnLoadFromDB(ChouJiang *const this, const PlayerDBData *const dbData)
{
  this->m_LuckyPoint = dbData->m_ChouJinagData.m_LuckyPoint;
  std::list<ChouJiangRecord>::operator=(&this->m_RecordList, &dbData->m_ChouJinagData.m_RecordList);
  memcpy(this->m_ItemList, dbData->m_ChouJinagData.m_ItemList, sizeof(this->m_ItemList));
  this->m_WeekReward = dbData->m_ChouJinagData.m_Score;
  if ( this->m_LuckyPoint < -200 )
    this->m_LuckyPoint = -200;
  if ( this->m_LuckyPoint > 300 )
    this->m_LuckyPoint = 300;
}


#####################################
void __cdecl ChouJiang::OnSaveToDB(ChouJiang *const this, PlayerDBData *const dbData)
{
  dbData->m_ChouJinagData.m_LuckyPoint = this->m_LuckyPoint;
  std::list<ChouJiangRecord>::operator=(&dbData->m_ChouJinagData.m_RecordList, &this->m_RecordList);
  memcpy(dbData->m_ChouJinagData.m_ItemList, this->m_ItemList, sizeof(dbData->m_ChouJinagData.m_ItemList));
  dbData->m_ChouJinagData.m_Score = this->m_WeekReward;
}


#####################################
void __cdecl ChouJiang::GetInterestsProtocol(ChouJiang *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v3; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v4; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v5; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v6; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v7; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 452;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 448;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 449;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 450;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 20083;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 461;
  std::list<unsigned short>::push_back(procList, &v7);
}


#####################################
void __cdecl ChouJiang::OnDaySwitch(ChouJiang *const this, int32_t nDiffDays)
{
  Player::updateRecord(this->m_pPlayer, 1060, 0);
  this->m_WeekReward = 0;
  ChouJiang::SendWeekRewardInfo(this);
}


#####################################
int32_t __cdecl ChouJiang::DispatchNetDatas(ChouJiang *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  GameService *v4; // rax

  if ( !inPacket )
    return 2;
  v4 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v4) == 9 )
    return 10002;
  if ( nProcId == 450 )
    return ChouJiang::OnAskChouJiangRecord(this, inPacket);
  if ( nProcId > 0x1C2u )
  {
    switch ( nProcId )
    {
      case 0x1CDu:
        return ChouJiang::OnGetWeekReward(this, inPacket);
      case 0x4E73u:
        return ChouJiang::OnChouJiang(this, inPacket);
      case 0x1C4u:
        return ChouJiang::OnAskChouJiang(this, inPacket);
    }
  }
  else
  {
    if ( nProcId == 448 )
      return ChouJiang::OnTidy(this, inPacket);
    if ( nProcId == 449 )
      return ChouJiang::OnGetItem(this, inPacket);
  }
  return 2;
}


#####################################
int32_t __cdecl ChouJiang::OnAskChouJiang(ChouJiang *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const ChouJiangTable *CouJiangTable; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v6; // rax
  int8_t m_nClass; // r12
  int32_t m_nId; // ebx
  CExtCharBag *v9; // rax
  CExtCharBag *v10; // rax
  int32_t v11; // r12d
  int8_t v12; // bl
  CfgData *v13; // rax
  int v14; // eax
  int8_t ChouJiangTimes; // [rsp+15h] [rbp-3Bh]
  int8_t AutoBuy; // [rsp+16h] [rbp-3Ah]
  int8_t ChouJiangType; // [rsp+17h] [rbp-39h]
  const ChouJiangCost *pCost; // [rsp+18h] [rbp-38h]
  int32_t HaveBindCount; // [rsp+24h] [rbp-2Ch]
  int32_t HaveUnBindCount; // [rsp+28h] [rbp-28h]
  CfgGameShop *pCfgGameShop; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  ChouJiangTimes = Answer::NetPacket::readInt8(inPacket);
  AutoBuy = Answer::NetPacket::readInt8(inPacket);
  ChouJiangType = Answer::NetPacket::readInt8(inPacket);
  if ( ChouJiang::GetChouJiangType(this) != ChouJiangType )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  CouJiangTable = CfgData::GetCouJiangTable(v3);
  pCost = ChouJiangTable::GetChouJiangCost(CouJiangTable, ChouJiangTimes);
  if ( !pCost )
    return 2;
  if ( pCost->Items.m_nCount <= 0 || pCost->Items.m_nClass <= 0 || pCost->Items.m_nId <= 0 || pCost->ItemPrice <= 0 )
    return 2;
  if ( ChouJiang::GetFreeCount(this) < ChouJiangTimes )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  HaveBindCount = CExtCharBag::HaveItemCount(Bag, &pCost->Items, 1, 1);
  v6 = Player::GetBag(this->m_pPlayer);
  HaveUnBindCount = CExtCharBag::HaveItemCount(v6, &pCost->Items, 0, 1);
  m_nClass = pCost->Items.m_nClass;
  m_nId = pCost->Items.m_nId;
  v9 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::GetItemCount(v9, m_nId, m_nClass);
  if ( HaveUnBindCount + HaveBindCount < ChouJiangTimes )
  {
    if ( AutoBuy != 1 )
      return 2;
    v10 = Player::GetBag(this->m_pPlayer);
    if ( CExtCharBag::GetFreeSlotCount(v10) <= 0 )
      return 2;
    v11 = pCost->Items.m_nId;
    v12 = pCost->Items.m_nClass;
    v13 = Answer::Singleton<CfgData>::instance();
    pCfgGameShop = CfgData::GetGameShopItem(v13, v12, v11);
    if ( !pCfgGameShop )
      return 2;
    if ( pCost->ItemPrice <= 0 )
      return 2;
    if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < (ChouJiangTimes
                                                                             - HaveBindCount
                                                                             - HaveUnBindCount)
                                                                            * pCfgGameShop->Price )
      return 2;
  }
  v14 = ChouJiangTimes - HaveBindCount;
  if ( v14 < 0 )
    LOBYTE(v14) = 0;
  ChouJiang::CheckGlobalPoint(this, AutoBuy, ChouJiangTimes, v14, ChouJiangType);
  return 0;
}


#####################################
int8_t __cdecl ChouJiang::GetChouJiangType(ChouJiang *const this)
{
  COpenBeta *v1; // rax
  COpenBeta *v2; // rax
  CUniteServer *v4; // rax
  CUniteServer *v5; // rax
  CFestivalDoubleEleven *v6; // rax
  CFestivalDoubleEleven *v7; // rax

  v1 = Answer::Singleton<COpenBeta>::instance();
  if ( COpenBeta::GetChouJiangType(v1) <= 0 )
  {
    v4 = Answer::Singleton<CUniteServer>::instance();
    if ( CUniteServer::GetChouJiangType(v4) <= 0 )
    {
      v6 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      if ( CFestivalDoubleEleven::GetChouJiangType(v6) <= 0 )
      {
        return 1;
      }
      else
      {
        v7 = Answer::Singleton<CFestivalDoubleEleven>::instance();
        return CFestivalDoubleEleven::GetChouJiangType(v7);
      }
    }
    else
    {
      v5 = Answer::Singleton<CUniteServer>::instance();
      return CUniteServer::GetChouJiangType(v5);
    }
  }
  else
  {
    v2 = Answer::Singleton<COpenBeta>::instance();
    return COpenBeta::GetChouJiangType(v2);
  }
}


#####################################
int32_t __cdecl ChouJiang::GetChouJiangSpecialTime(ChouJiang *const this)
{
  CUniteServer *v1; // rax
  CUniteServer *v2; // rax
  CFestivalDoubleEleven *v4; // rax
  CFestivalDoubleEleven *v5; // rax

  v1 = Answer::Singleton<CUniteServer>::instance();
  if ( CUniteServer::GetChouJiangSpecialTime(v1) <= 0 )
  {
    v4 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    if ( CFestivalDoubleEleven::GetChouJiangSpecialTime(v4) <= 0 )
    {
      return 0;
    }
    else
    {
      v5 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      return CFestivalDoubleEleven::GetChouJiangSpecialTime(v5);
    }
  }
  else
  {
    v2 = Answer::Singleton<CUniteServer>::instance();
    return CUniteServer::GetChouJiangSpecialTime(v2);
  }
}


#####################################
int32_t __cdecl ChouJiang::OnChouJiang(ChouJiang *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const ChouJiangTable *CouJiangTable; // rax
  int8_t m_nClass; // r12
  int32_t m_nId; // ebx
  CExtCharBag *Bag; // rax
  CExtCharBag *v8; // rax
  int32_t v9; // r12d
  int8_t v10; // bl
  CfgData *v11; // rax
  CExtCharBag *v12; // rax
  CExtCharBag *v13; // rax
  CExtCharBag *v14; // rax
  int32_t v15; // r12d
  Player *m_pPlayer; // rbx
  CKiaFuRecharge *v17; // rax
  int32_t v18; // r12d
  Player *v19; // rbx
  CUniteServer *v20; // rax
  int32_t Record; // eax
  CNationalDayHd *CNationalDayHd; // rax
  CFestivalDoubleEleven *v23; // rax
  CExtOperateLimit *OperateLimit; // rax
  CfgData *v25; // rax
  int8_t v26; // r14
  int32_t m_LuckyPoint; // r13d
  bool v28; // r12
  int32_t v29; // ebx
  CfgData *v30; // rax
  const ChouJiangTable *v31; // rax
  MemChrBag stu; // [rsp+10h] [rbp-100h] BYREF
  int32_t UnBindCount_0; // [rsp+38h] [rbp-D8h] BYREF
  int32_t BindCount_0; // [rsp+3Ch] [rbp-D4h] BYREF
  ItemData item_0; // [rsp+40h] [rbp-D0h] BYREF
  ItemData item; // [rsp+50h] [rbp-C0h] BYREF
  int32_t UnBindCount; // [rsp+68h] [rbp-A8h] BYREF
  int32_t BindCount; // [rsp+6Ch] [rbp-A4h] BYREF
  MemChrBagVector GetItmes; // [rsp+70h] [rbp-A0h] BYREF
  std::vector<MemChrBag> p_Items; // [rsp+90h] [rbp-80h] BYREF
  int8_t AutoBuy; // [rsp+B4h] [rbp-5Ch]
  int8_t ChouJiangTimes; // [rsp+B5h] [rbp-5Bh]
  int8_t Special; // [rsp+B6h] [rbp-5Ah]
  int8_t ChouJiangType; // [rsp+B7h] [rbp-59h]
  const ChouJiangCost *pCost; // [rsp+B8h] [rbp-58h]
  int32_t HaveAllCount; // [rsp+C4h] [rbp-4Ch]
  int32_t CostUnBindCount; // [rsp+C8h] [rbp-48h]
  int32_t diffCount; // [rsp+CCh] [rbp-44h]
  CfgGameShop *pCfgGameShop; // [rsp+D0h] [rbp-40h]
  int32_t IsFirst; // [rsp+D8h] [rbp-38h]
  int32_t KaiFuDay; // [rsp+DCh] [rbp-34h]
  const ChouJiangCfg *pChouJiangCfg; // [rsp+E0h] [rbp-30h]
  int32_t SpecialTime; // [rsp+E8h] [rbp-28h]
  int32_t Time; // [rsp+ECh] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  AutoBuy = Answer::NetPacket::readInt8(inPacket);
  ChouJiangTimes = Answer::NetPacket::readInt8(inPacket);
  Special = Answer::NetPacket::readInt8(inPacket);
  ChouJiangType = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  CouJiangTable = CfgData::GetCouJiangTable(v3);
  pCost = ChouJiangTable::GetChouJiangCost(CouJiangTable, ChouJiangTimes);
  if ( !pCost )
    return 2;
  if ( pCost->Items.m_nCount <= 0 || pCost->Items.m_nClass <= 0 || pCost->Items.m_nId <= 0 || pCost->ItemPrice <= 0 )
    return 2;
  if ( ChouJiang::GetFreeCount(this) < ChouJiangTimes )
    return 2;
  m_nClass = pCost->Items.m_nClass;
  m_nId = pCost->Items.m_nId;
  Bag = Player::GetBag(this->m_pPlayer);
  HaveAllCount = CExtCharBag::GetItemCount(Bag, m_nId, m_nClass);
  CostUnBindCount = 0;
  if ( ChouJiangTimes <= HaveAllCount )
  {
    *(_QWORD *)&item_0.m_nId = 0;
    item_0.m_nCount = 0;
    item_0.m_nClass = pCost->Items.m_nClass;
    item_0.m_nId = pCost->Items.m_nId;
    item_0.m_nCount = ChouJiangTimes;
    BindCount_0 = 0;
    UnBindCount_0 = 0;
    v14 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::RemoveItem(v14, &item_0, ITEM_CHANGE_REASON::ICR_CHOU_JIANG, &BindCount_0, &UnBindCount_0) )
      return 2;
    CostUnBindCount = UnBindCount_0;
  }
  else
  {
    if ( AutoBuy != 1 )
      return 2;
    v8 = Player::GetBag(this->m_pPlayer);
    if ( CExtCharBag::GetFreeSlotCount(v8) <= 0 )
    {
      Player::TiShiInfo(this->m_pPlayer, 2048, 0);
      return 2;
    }
    diffCount = ChouJiangTimes - HaveAllCount;
    v9 = pCost->Items.m_nId;
    v10 = pCost->Items.m_nClass;
    v11 = Answer::Singleton<CfgData>::instance();
    pCfgGameShop = CfgData::GetGameShopItem(v11, v10, v9);
    if ( !pCfgGameShop )
      return 2;
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            diffCount * pCfgGameShop->Price,
            CURRENCY_CHANGE_REASON::GCR_CHOU_JIANG,
            0) )
      return 2;
    BindCount = 0;
    UnBindCount = 0;
    if ( HaveAllCount > 0 )
    {
      *(_QWORD *)&item.m_nId = 0;
      item.m_nCount = 0;
      item.m_nClass = pCost->Items.m_nClass;
      item.m_nId = pCost->Items.m_nId;
      item.m_nCount = HaveAllCount;
      v12 = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::RemoveItem(v12, &item, ITEM_CHANGE_REASON::ICR_CHOU_JIANG, &BindCount, &UnBindCount) )
        return 2;
    }
    CostUnBindCount = diffCount + UnBindCount;
    memset(&stu, 0, sizeof(stu));
    stu = pCost->Gift;
    stu.itemCount = diffCount;
    v13 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::AddItem(v13, &stu, ITEM_CHANGE_REASON::IDCR_CHOU_JIANG_BUY);
  }
  Player::AddCurrency(
    this->m_pPlayer,
    CURRENCY_TYPE::CURRENCY_DRAW_SCORE,
    ChouJiangTimes,
    CURRENCY_CHANGE_REASON::SCR_ON_CHOU_JIANG,
    0);
  v15 = ChouJiangTimes;
  m_pPlayer = this->m_pPlayer;
  v17 = Answer::Singleton<CKiaFuRecharge>::instance();
  CKiaFuRecharge::OnAddChouJiangTimes(v17, m_pPlayer, v15);
  v18 = ChouJiangTimes;
  v19 = this->m_pPlayer;
  v20 = Answer::Singleton<CUniteServer>::instance();
  CUniteServer::OnAddChouJiangTimes(v20, v19, v18);
  Record = Player::getRecord(this->m_pPlayer, 1060);
  Player::updateRecord(this->m_pPlayer, 1060, Record + ChouJiangTimes);
  LODWORD(v19) = ChouJiangTimes;
  CNationalDayHd = Player::GetCNationalDayHd(this->m_pPlayer);
  CNationalDayHd::AddNationalValue(CNationalDayHd, NATIONAL_HD_TYPE::HHT_CHOU_JIANG, (int32_t)v19, 0);
  std::vector<MemChrBag>::vector(&GetItmes);
  while ( ChouJiangTimes > 0 )
  {
    --ChouJiangTimes;
    IsFirst = Player::getRecord(this->m_pPlayer, 1059);
    if ( IsFirst > 0 && Special <= 0 )
    {
      v23 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      SpecialTime = CFestivalDoubleEleven::GetChouJiangSpecialTime(v23);
      if ( SpecialTime > 0 && !(IsFirst % SpecialTime) )
        Special = 4;
    }
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1059, 1);
    v25 = Answer::Singleton<CfgData>::instance();
    KaiFuDay = CfgData::getServerDiffDay(v25, SERVER_TYPE::SVT_NORMAL) + 1;
    v26 = ChouJiangType;
    m_LuckyPoint = this->m_LuckyPoint;
    v28 = IsFirst <= 0;
    v29 = Special;
    v30 = Answer::Singleton<CfgData>::instance();
    v31 = CfgData::GetCouJiangTable(v30);
    pChouJiangCfg = ChouJiangTable::RandItem(v31, v29, v28, m_LuckyPoint, KaiFuDay, v26);
    if ( pChouJiangCfg )
    {
      Special = 0;
      if ( pChouJiangCfg->SubLuckValue > 0 )
      {
        this->m_LuckyPoint -= pChouJiangCfg->SubLuckValue;
        if ( this->m_LuckyPoint < -200 )
          this->m_LuckyPoint = -200;
      }
      if ( pChouJiangCfg->JifenDel > 0 )
        Player::updateRecord(this->m_pPlayer, 1059, 1);
      Time = Unit::getNow(this->m_pPlayer);
      memset(&stu, 0, sizeof(stu));
      stu.itemClass = pChouJiangCfg->Item.itemClass;
      stu.itemId = pChouJiangCfg->Item.itemId;
      stu.itemCount = pChouJiangCfg->Item.itemCount;
      if ( CostUnBindCount <= 0 )
      {
        stu.bind = stu.itemClass != 2;
      }
      else
      {
        --CostUnBindCount;
        if ( ++this->m_LuckyPoint > 300 )
          this->m_LuckyPoint = 300;
      }
      if ( pChouJiangCfg->GongGaoId > 0 )
        ChouJiang::GongGao(
          this,
          pChouJiangCfg->GongGaoId,
          pChouJiangCfg->Index,
          pChouJiangCfg->Item.itemClass,
          pChouJiangCfg->Item.itemId);
      if ( pChouJiangCfg->PersonalRecord > 0 )
        ChouJiang::AddChouJiangRecord(this, &stu, Time);
      if ( pChouJiangCfg->ServerRecord > 0 )
        ChouJiang::AddServerRecord(this, &stu);
      std::vector<MemChrBag>::push_back(&GetItmes, &stu);
    }
  }
  ChouJiang::SendWeekRewardInfo(this);
  std::vector<MemChrBag>::vector(&p_Items, &GetItmes);
  ChouJiang::AddItem(this, &p_Items);
  std::vector<MemChrBag>::~vector(&p_Items);
  v2 = 0;
  std::vector<MemChrBag>::~vector(&GetItmes);
  return v2;
}


#####################################
int32_t __cdecl ChouJiang::OnAskChouJiangRecord(ChouJiang *const this, Answer::NetPacket *inPacket)
{
  ChouJiang::SendChouJiangRecord(this);
  ChouJiang::ToGlobalAskChouJiangRecord(this);
  ChouJiang::SendWeekRewardInfo(this);
  return 0;
}


#####################################
int32_t __cdecl ChouJiang::ToGlobalAskChouJiangRecord(ChouJiang *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_PROC, 0x4EB8u);
  if ( !packet || !this->m_pPlayer )
    return 2;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  Answer::NetPacket::writeInt32(packet, GateIndex);
  Answer::NetPacket::writeInt8(packet, 0);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v6 = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  GameService::sendPacket(v7, v6, packet);
  return 0;
}


#####################################
int32_t __cdecl ChouJiang::OnGetItem(ChouJiang *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v4; // rax
  int Slot; // [rsp+18h] [rbp-8h]
  int i; // [rsp+1Ch] [rbp-4h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Slot = Answer::NetPacket::readInt32(inPacket);
  if ( Slot < -1 || Slot > 489 )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  if ( Slot == -1 )
  {
    for ( i = 0; i <= 489; ++i )
    {
      if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
      {
        v4 = Player::GetBag(this->m_pPlayer);
        if ( CExtCharBag::GetFreeSlotCount(v4) <= 0 )
        {
          Player::TiShiInfo(this->m_pPlayer, 2048, 0);
          return 2;
        }
        ChouJiang::GetItem(this, i);
      }
    }
  }
  else
  {
    ChouJiang::GetItem(this, Slot);
  }
  return 0;
}


#####################################
int32_t __cdecl ChouJiang::OnTidy(ChouJiang *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MemChrBag *v3; // rax
  MemChrBag *v4; // rax
  MemChrBag *v5; // rax
  MemChrBag *v6; // rax
  MemChrBag *v8; // rax
  MemChrBag *M_current; // rbx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v10; // rax
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v13; // rax
  __int64 v16; // rdx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+40h] [rbp-90h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v22; // [rsp+80h] [rbp-50h] BYREF
  int32_t nBagSize; // [rsp+94h] [rbp-3Ch]
  int32_t slot; // [rsp+98h] [rbp-38h]
  int32_t i; // [rsp+9Ch] [rbp-34h]
  const MemChrBag *slotdata; // [rsp+A0h] [rbp-30h]
  bool bFind; // [rsp+AFh] [rbp-21h]
  MemChrBag *bagSlot; // [rsp+B0h] [rbp-20h]
  int32_t overlay; // [rsp+BCh] [rbp-14h]
  MemChrBag nullobj; // 0:^10.32

  if ( !inPacket )
    return 2;
  std::vector<MemChrBag>::vector(&items);
  nBagSize = 490;
  for ( i = 0; i < nBagSize; ++i )
  {
    slotdata = &this->m_ItemList[i];
    if ( slotdata->itemCount > 0 )
    {
      bFind = 0;
      for ( it._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&items)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
          break;
        v3 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
        if ( v3->itemClass == slotdata->itemClass )
        {
          v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
          if ( v4->itemId == slotdata->itemId )
          {
            v5 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
            if ( v5->bind == slotdata->bind )
            {
              v6 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
              if ( v6->srcId == slotdata->srcId )
              {
                v8 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
                v8->itemCount += slotdata->itemCount;
                bFind = 1;
                break;
              }
            }
          }
        }
      }
      if ( !bFind )
        std::vector<MemChrBag>::push_back(&items, slotdata);
    }
  }
  M_current = std::vector<MemChrBag>::end(&items)._M_current;
  v10._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
  std::sort<__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>,bool (*)(MemChrBag const&,MemChrBag const&)>(
    v10,
    (__gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> >)M_current,
    (bool (*)(const MemChrBag *, const MemChrBag *))GreaterChouJiangItem);
  slot = 0;
  for ( iter._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    v22._M_current = std::vector<MemChrBag>::end(&items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &v22) || slot >= nBagSize )
      break;
    bagSlot = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter);
    itemClass = bagSlot->itemClass;
    itemId = bagSlot->itemId;
    v13 = Answer::Singleton<CfgData>::instance();
    overlay = CfgData::getOverlay(v13, itemId, itemClass);
    if ( overlay > 0 )
    {
      while ( bagSlot->itemCount > overlay && slot < nBagSize )
      {
        nullobj = *bagSlot;
        nullobj.itemCount = overlay;
        bagSlot->itemCount -= overlay;
        *((MemChrBag *)&this->_vptr_IExtSystem + ++slot) = nullobj;
      }
      if ( bagSlot->itemCount > 0 && slot < nBagSize )
        *((MemChrBag *)&this->_vptr_IExtSystem + ++slot) = *bagSlot;
    }
  }
  while ( slot < nBagSize )
  {
    v16 = 32 * (slot + 1LL);
    *(int (***)(...))((char *)&this->_vptr_IExtSystem + v16) = 0;
    *(Player **)((char *)&this->m_pPlayer + v16) = 0;
    *(std::_List_node_base **)((char *)&this->m_RecordList._M_impl._M_node._M_next + v16) = 0;
    *(std::_List_node_base **)((char *)&this->m_RecordList._M_impl._M_node._M_prev + v16) = 0;
    ++slot;
  }
  ChouJiang::SendChouJiangItem(this);
  v2 = 0;
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
int32_t __cdecl ChouJiang::OnGetWeekReward(ChouJiang *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const ChouJiangTable *CouJiangTable; // rax
  CExtCharBag *Bag; // rax
  int32_t Index; // [rsp+1Ch] [rbp-24h]
  const ChouJiangWeekReward *pCfg; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Index = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  CouJiangTable = CfgData::GetCouJiangTable(v3);
  pCfg = ChouJiangTable::GetChouJiangWeekReward(CouJiangTable, Index);
  if ( !pCfg )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 1060) < pCfg->Times )
    return 10002;
  OldRecord = this->m_WeekReward;
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->Items, ITEM_CHANGE_REASON::ICR_CHOU_JIANG_WEEK_REWARD) )
    return 2;
  this->m_WeekReward = NewRecord;
  ChouJiang::SendWeekRewardInfo(this);
  return 0;
}


#####################################
void __cdecl ChouJiang::SendWeekRewardInfo(ChouJiang *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD2u);
    if ( packet )
    {
      Record = Player::getRecord(this->m_pPlayer, 1060);
      Answer::NetPacket::writeInt32(packet, Record);
      Answer::NetPacket::writeInt32(packet, this->m_WeekReward);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl ChouJiang::SendChouJiangRecord(ChouJiang *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  ChouJiangRecord *v3; // rax
  ChouJiangRecord *v4; // rax
  ChouJiangRecord *v5; // rax
  ChouJiangRecord *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  std::_List_iterator<ChouJiangRecord> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<ChouJiangRecord> __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t Count; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC9u);
    if ( packet )
    {
      Count = std::list<ChouJiangRecord>::size(&this->m_RecordList);
      Answer::NetPacket::writeInt32(packet, Count);
      for ( it._M_node = std::list<ChouJiangRecord>::begin(&this->m_RecordList)._M_node;
            ;
            std::_List_iterator<ChouJiangRecord>::operator++(&it) )
      {
        __x._M_node = std::list<ChouJiangRecord>::end(&this->m_RecordList)._M_node;
        if ( !std::_List_iterator<ChouJiangRecord>::operator!=(&it, &__x) )
          break;
        v3 = std::_List_iterator<ChouJiangRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->CJItem.itemId);
        v4 = std::_List_iterator<ChouJiangRecord>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v4->CJItem.itemClass);
        v5 = std::_List_iterator<ChouJiangRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->CJItem.itemCount);
        v6 = std::_List_iterator<ChouJiangRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->Time);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl ChouJiang::AddChouJiangRecord(ChouJiang *const this, MemChrBag *const CJItem, int32_t Time)
{
  ChouJiangRecord Record; // [rsp+20h] [rbp-30h] BYREF

  memset(&Record, 0, sizeof(Record));
  Record.CJItem = *(MemChrBag *)CJItem;
  Record.Time = Time;
  if ( std::list<ChouJiangRecord>::size(&this->m_RecordList) > 0x31 )
    std::list<ChouJiangRecord>::pop_front(&this->m_RecordList);
  std::list<ChouJiangRecord>::push_back(&this->m_RecordList, &Record);
  ChouJiang::SendNewRecord(this, CJItem, Time);
}


#####################################
void __cdecl ChouJiang::AddServerRecord(ChouJiang *const this, MemChrBag *const CJItem)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int16_t GateIndex; // ax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_PROC, 0x4EB5u);
    if ( packet )
    {
      if ( this->m_pPlayer )
      {
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        Answer::NetPacket::writeInt32(packet, GateIndex);
        Cid = Player::getCid(this->m_pPlayer);
        Answer::NetPacket::writeInt64(packet, Cid);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        Answer::NetPacket::writeInt8(packet, CJItem->itemClass);
        Answer::NetPacket::writeInt32(packet, CJItem->itemId);
        Answer::NetPacket::writeInt32(packet, CJItem->itemCount);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v7 = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacket(v8, v7, packet);
      }
    }
  }
}


#####################################
void __cdecl ChouJiang::SendNewRecord(ChouJiang *const this, MemChrBag *const CJItem, int32_t Time)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CCAu);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, CJItem->itemId);
    Answer::NetPacket::writeInt8(packet, CJItem->itemClass);
    Answer::NetPacket::writeInt32(packet, CJItem->itemCount);
    Answer::NetPacket::writeInt32(packet, Time);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v7 = Player::getConnId(this->m_pPlayer);
    v8 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v8, v7, GateIndex, packet);
  }
}


#####################################
void __cdecl ChouJiang::CheckGlobalPoint(
        ChouJiang *const this,
        int8_t AutoBuy,
        int8_t ChouJiangTimes,
        int8_t AddPoint,
        int8_t ChouJiangType)
{
  int8_t ConnId; // bl
  GameService *v6; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_PROC, 0x4EB7u);
  if ( packet )
  {
    if ( this->m_pPlayer )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt8(packet, AutoBuy);
      Answer::NetPacket::writeInt8(packet, ChouJiangTimes);
      Answer::NetPacket::writeInt8(packet, AddPoint);
      Answer::NetPacket::writeInt8(packet, ChouJiangType);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v10, v9, packet);
    }
  }
}


#####################################
void __cdecl ChouJiang::SendChouJiangItemChang(ChouJiang *const this, std::list<int> *const ItemList)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int *v4; // rax
  int *v5; // rax
  int *v6; // rax
  int *v7; // rax
  int *v8; // rax
  int *v9; // rax
  int *v10; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  std::_List_iterator<int> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  Count = std::list<int>::size(ItemList);
  if ( Count > 0 )
  {
    if ( this->m_pPlayer )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CCFu);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, Count);
        for ( it._M_node = std::list<int>::begin(ItemList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
        {
          __x._M_node = std::list<int>::end(ItemList)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
            break;
          v4 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, *v4);
          v5 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v5].itemId);
          v6 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[*v6].itemClass);
          v7 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v7].itemCount);
          v8 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[*v8].bind);
          v9 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v9].endTime);
          v10 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt64(packet, this->m_ItemList[*v10].srcId);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v13 = Player::getConnId(this->m_pPlayer);
        v14 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v14, v13, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl ChouJiang::SendGetItem(ChouJiang *const this, std::list<int> *const ItemList)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int *v4; // rax
  int *v5; // rax
  int *v6; // rax
  int *v7; // rax
  int *v8; // rax
  int *v9; // rax
  int *v10; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  std::_List_iterator<int> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  Count = std::list<int>::size(ItemList);
  if ( Count > 0 )
  {
    if ( this->m_pPlayer )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD1u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, Count);
        for ( it._M_node = std::list<int>::begin(ItemList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
        {
          __x._M_node = std::list<int>::end(ItemList)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
            break;
          v4 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, *v4);
          v5 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v5].itemId);
          v6 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[*v6].itemClass);
          v7 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v7].itemCount);
          v8 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[*v8].bind);
          v9 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[*v9].endTime);
          v10 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt64(packet, this->m_ItemList[*v10].srcId);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v13 = Player::getConnId(this->m_pPlayer);
        v14 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v14, v13, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl ChouJiang::SendChouJiangItem(ChouJiang *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  int32_t Count; // [rsp+20h] [rbp-20h]
  int32_t OldOffet; // [rsp+24h] [rbp-1Ch]
  int32_t NewOffet; // [rsp+28h] [rbp-18h]
  int i; // [rsp+2Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CCEu);
    if ( packet )
    {
      Count = 0;
      OldOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      for ( i = 0; i <= 489; ++i )
      {
        if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
        {
          ++Count;
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].itemId);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[i].itemClass);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].itemCount);
          Answer::NetPacket::writeInt8(packet, this->m_ItemList[i].bind);
          Answer::NetPacket::writeInt32(packet, this->m_ItemList[i].endTime);
          Answer::NetPacket::writeInt64(packet, this->m_ItemList[i].srcId);
        }
      }
      NewOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, OldOffet);
      Answer::NetPacket::writeInt32(packet, Count);
      Answer::NetPacket::setWOffset(packet, NewOffet);
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
bool __cdecl ChouJiang::AddItem(ChouJiang *const this, MemChrBagVector *p_Items)
{
  bool v2; // bl
  int32_t v3; // ebx
  int32_t i; // [rsp+1Ch] [rbp-44h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+20h] [rbp-40h] BYREF
  std::list<int> ItemList; // [rsp+30h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+40h] [rbp-20h] BYREF
  int32_t time; // [rsp+4Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  time = Unit::getNow(this->m_pPlayer);
  std::list<int>::list(&ItemList);
  std::list<int>::clear(&ItemList);
  for ( it._M_current = std::vector<MemChrBag>::begin(p_Items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(p_Items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&it, &__rhs) )
      break;
    for ( i = 0; i <= 489; ++i )
    {
      if ( this->m_ItemList[i].itemCount <= 0 || this->m_ItemList[i].itemId <= 0 )
      {
        v3 = i;
        this->m_ItemList[v3] = *__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
        std::list<int>::push_back(&ItemList, &i);
        break;
      }
    }
  }
  ChouJiang::SendChouJiangItemChang(this, &ItemList);
  ChouJiang::SendGetItem(this, &ItemList);
  v2 = 1;
  std::list<int>::~list(&ItemList);
  return v2;
}


#####################################
void __cdecl ChouJiang::GongGao(
        ChouJiang *const this,
        int32_t GongGaoId,
        int32_t Index,
        int8_t ItemClass,
        int32_t ItemId)
{
  int8_t ConnId; // bl
  GameService *v6; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v9; // bl
  GameService *v10; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *pNetData; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v6 = Answer::Singleton<GameService>::instance();
    pNetData = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( pNetData )
    {
      Answer::NetPacket::writeInt32(pNetData, GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(pNetData, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(pNetData, Cid);
      Answer::NetPacket::writeInt8(pNetData, ItemClass);
      Answer::NetPacket::writeInt32(pNetData, ItemId);
      Answer::NetPacket::writeInt32(pNetData, Index);
      WOffset = Answer::NetPacket::getWOffset(pNetData);
      Answer::NetPacket::setSize(pNetData, WOffset);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v10, v9, pNetData);
    }
  }
}


#####################################
void __cdecl ChouJiang::GetItem(ChouJiang *const this, int32_t Slot)
{
  CExtCharBag *Bag; // rax
  CExtCharBag *v3; // rax
  int32_t Slota; // [rsp+4h] [rbp-6Ch] BYREF
  ChouJiang *thisa; // [rsp+8h] [rbp-68h]
  MemChrBag BagItem; // [rsp+10h] [rbp-60h] BYREF
  std::list<int> TmpList; // [rsp+30h] [rbp-40h] BYREF
  MemChrBagVector item; // [rsp+40h] [rbp-30h] BYREF

  thisa = this;
  Slota = Slot;
  if ( this->m_pPlayer )
  {
    if ( (unsigned int)Slota <= 0x1E9 && thisa->m_ItemList[Slota].itemCount > 0 && thisa->m_ItemList[Slota].itemId > 0 )
    {
      Bag = Player::GetBag(thisa->m_pPlayer);
      if ( CExtCharBag::GetFreeSlotCount(Bag) > 0 )
      {
        BagItem = thisa->m_ItemList[Slota];
        std::vector<MemChrBag>::vector(&item);
        std::vector<MemChrBag>::push_back(&item, &BagItem);
        v3 = Player::GetBag(thisa->m_pPlayer);
        if ( CExtCharBag::AddItem(v3, &item, ITEM_CHANGE_REASON::ICR_DRAW_GET_REWARD) )
        {
          bzero(&thisa->m_ItemList[Slota], 0x20u);
          std::list<int>::list(&TmpList);
          std::list<int>::push_back(&TmpList, &Slota);
          ChouJiang::SendChouJiangItemChang(thisa, &TmpList);
          std::list<int>::~list(&TmpList);
        }
        std::vector<MemChrBag>::~vector(&item);
      }
    }
  }
}


#####################################
int32_t __cdecl ChouJiang::GetFreeCount(ChouJiang *const this)
{
  int32_t FreeCount; // [rsp+10h] [rbp-8h]
  int32_t i; // [rsp+14h] [rbp-4h]

  FreeCount = 0;
  for ( i = 0; i <= 489; ++i )
  {
    if ( this->m_ItemList[i].itemId <= 0 || this->m_ItemList[i].itemCount <= 0 )
      ++FreeCount;
  }
  return FreeCount;
}


#####################################
void __cdecl ChouJiang::GetChouJiangStu(ChouJiang *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 177) )
    {
      ChouJiang::GetShowIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl ChouJiang::SendHuoDongIcon(ChouJiang *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 177) )
    {
      ChouJiang::GetShowIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl ChouJiang::CleanBag(ChouJiang *const this)
{
  int32_t i; // [rsp+1Ch] [rbp-24h] BYREF
  std::list<int> TmpList; // [rsp+20h] [rbp-20h] BYREF

  std::list<int>::list(&TmpList);
  for ( i = 0; i <= 489; ++i )
  {
    if ( this->m_ItemList[i].itemCount > 0 && this->m_ItemList[i].itemId > 0 )
    {
      bzero(&this->m_ItemList[i], 0x20u);
      std::list<int>::push_back(&TmpList, &i);
    }
  }
  ChouJiang::SendChouJiangItemChang(this, &TmpList);
  std::list<int>::~list(&TmpList);
}


