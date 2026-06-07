// Decompiled methods for class: CVip
// Source: gameserver.cc
// Total methods: 43

#####################################
void __cdecl CVip::~CVip(CVip *const this)
{
  CVip::~CVip(this);
  operator delete(this);
}


#####################################
void __cdecl CVip::OnCleanUp(CVip *const this)
{
  this->m_LastUpdataTick = 0;
  this->m_PlatinumVipEndTime = 0;
  this->m_StarVipEndTime = 0;
  this->m_DiamVipEndTime = 0;
  this->m_Club = 0;
  this->m_ClubDropTimes = 0;
  this->m_BuyTimes = 0;
  this->m_nVip7Time = 0;
  this->m_nVip10Time = 0;
  std::map<int,VipLuckyDrop>::clear(&this->m_VipLuckyDropMap);
}


#####################################
void __cdecl CVip::OnLoadFromDB(CVip *const this, const PlayerDBData *const dbData)
{
  int8_t VipType; // al
  int8_t VipLevel; // al
  int8_t v4; // bl
  CfgData *v5; // rax
  VipTable *VipTable; // rax
  int8_t v7; // bl
  CfgData *v8; // rax
  VipTable *v9; // rax
  VipLuckyDrop *v10; // rax
  VipLuckyDrop *v11; // rax
  VipLuckyDrop *v12; // rbx
  int32_t CanDropOrdinaryTimes; // r12d
  VipLuckyDrop *v14; // rbx
  int32_t CanDropSpecialTimes; // r12d
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  std::string p_String; // [rsp+20h] [rbp-30h] BYREF
  VipCfg *pVipCfg; // [rsp+28h] [rbp-28h]
  int32_t UpperTimes1; // [rsp+30h] [rbp-20h]
  int32_t UpperTimes2; // [rsp+34h] [rbp-1Ch]
  VipCfg *UpperCfg; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    CVip::OnLoadVipEndTime(this, &dbData->m_vipData.m_VipEndTime);
    VipType = CVip::GetVipType(this);
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_VIP, VipType);
    VipLevel = CVip::GetVipLevel(this);
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_VIP_LEVEL, VipLevel);
    for ( i = 1; i <= 14; ++i )
    {
      v4 = i;
      v5 = Answer::Singleton<CfgData>::instance();
      VipTable = CfgData::GetVipTable(v5);
      pVipCfg = VipTable::GetVipCfg(VipTable, v4);
      if ( pVipCfg )
      {
        UpperTimes1 = 0;
        UpperTimes2 = 0;
        v7 = i - 1;
        v8 = Answer::Singleton<CfgData>::instance();
        v9 = CfgData::GetVipTable(v8);
        UpperCfg = VipTable::GetVipCfg(v9, v7);
        if ( UpperCfg )
        {
          UpperTimes1 = UpperCfg->Luck1;
          UpperTimes2 = UpperCfg->Luck2;
        }
        v10 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i);
        v10->CanDropOrdinaryTimes = pVipCfg->Luck1 - UpperTimes1;
        v11 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i);
        v11->CanDropSpecialTimes = pVipCfg->Luck2 - UpperTimes2;
        if ( i == 1 )
        {
          v12 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i);
          CanDropOrdinaryTimes = v12->CanDropOrdinaryTimes;
          v12->CanDropOrdinaryTimes = CanDropOrdinaryTimes + Player::getRecord(this->m_pPlayer, 1906);
          v14 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i);
          CanDropSpecialTimes = v14->CanDropSpecialTimes;
          v14->CanDropSpecialTimes = CanDropSpecialTimes + Player::getRecord(this->m_pPlayer, 1907);
        }
      }
    }
    std::string::string(&p_String, &dbData->m_vipData.m_DropString);
    CVip::LoadDropString(this, &p_String);
    std::string::~string(&p_String);
    this->m_Club = dbData->m_vipData.m_Club;
    this->m_ClubDropTimes = dbData->m_vipData.m_ClubDropTimes;
    this->m_BuyTimes = dbData->m_vipData.m_BuyTimes;
    this->m_nVip7Time = dbData->m_vipData.m_nVip7Time;
    this->m_nVip10Time = dbData->m_vipData.m_nVip10Time;
  }
}


#####################################
bool __cdecl CVip::AddVipLuckyDrop(CVip *const this, int32_t Type, int32_t Times)
{
  VipLuckyDrop *v4; // rax
  CExtOperateLimit *OperateLimit; // rax
  VipLuckyDrop *v6; // rax
  CExtOperateLimit *v7; // rax
  int __k; // [rsp+18h] [rbp-8h] BYREF
  int v10; // [rsp+1Ch] [rbp-4h] BYREF

  if ( Times <= 0 )
    return 0;
  if ( Type == 1 )
  {
    __k = 1;
    v4 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &__k);
    v4->CanDropOrdinaryTimes += Times;
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1906, Times);
    return 1;
  }
  else if ( Type == 2 )
  {
    v10 = 1;
    v6 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &v10);
    v6->CanDropSpecialTimes += Times;
    v7 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(v7, 1907, Times);
    return 1;
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl CVip::OnSaveToDB(CVip *const this, PlayerDBData *const dbData)
{
  _BYTE v2[16]; // [rsp+10h] [rbp-30h] BYREF
  _BYTE v3[32]; // [rsp+20h] [rbp-20h] BYREF

  CVip::OnSaveVipEndTime((CVip *const)v2);
  std::string::operator=(&dbData->m_vipData.m_VipEndTime, v2);
  std::string::~string(v2);
  dbData->m_vipData.m_level = CVip::GetVipLevel(this);
  CVip::SaveDropString((CVip *const)v3);
  std::string::operator=(&dbData->m_vipData.m_DropString, v3);
  std::string::~string(v3);
  dbData->m_vipData.m_Club = this->m_Club;
  dbData->m_vipData.m_ClubDropTimes = this->m_ClubDropTimes;
  dbData->m_vipData.m_BuyTimes = this->m_BuyTimes;
  dbData->m_vipData.m_nVip7Time = this->m_nVip7Time;
  dbData->m_vipData.m_nVip10Time = this->m_nVip10Time;
}


#####################################
void __cdecl CVip::GetInterestsProtocol(CVip *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+12h] [rbp-Eh] BYREF
  unsigned __int16 v3; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v4; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v5; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v6; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v7; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v8; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 463;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 464;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 465;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 466;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 467;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 468;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 345;
  std::list<unsigned short>::push_back(procList, &v8);
}


#####################################
int32_t __cdecl CVip::DispatchNetDatas(CVip *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 2;
  if ( nProcId == 465 )
    return CVip::OnGetVipCardGift(this, inPacket);
  if ( nProcId > 0x1D1u )
  {
    if ( nProcId == 467 )
      return CVip::OnEnterClub(this, inPacket);
    if ( nProcId < 0x1D3u )
      return CVip::OnBuyAllVipCard(this, inPacket);
    if ( nProcId == 468 )
      return CVip::OnBuyDropTimes(this, inPacket);
  }
  else
  {
    if ( nProcId == 463 )
      return CVip::OnBuyVipCard(this, inPacket);
    if ( nProcId > 0x1CFu )
      return CVip::OnGetVipGift(this, inPacket);
    if ( nProcId == 345 )
    {
      CVip::SendClubInfo(this);
      return 2;
    }
  }
  return 2;
}


#####################################
int32_t __cdecl CVip::OnBuyVipCard(CVip *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v7; // rax
  int8_t VipLevel; // cl
  ChrTask *Task; // rax
  int8_t VipType; // [rsp+1Fh] [rbp-31h]
  VipCardCfg *pVip; // [rsp+20h] [rbp-30h]
  int32_t NeedGold; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  VipType = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pVip = CfgData::GetVipCardCfg(v3, VipType);
  if ( !pVip )
    return 2;
  if ( CVip::GetVipLevel(this) < pVip->VipLevel )
    return 2;
  if ( CVip::GetVipFlg(this, VipType) )
    NeedGold = pVip->ReNeedGold;
  else
    NeedGold = pVip->NeedGold;
  if ( NeedGold <= 0 )
    return 2;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          NeedGold,
          CURRENCY_CHANGE_REASON::GCR_BUY_VIP_CARD,
          VipType) )
    return 2;
  switch ( VipType )
  {
    case 1:
      CVip::AddVipTime(this, 1, pVip->AddVipTime);
      break;
    case 2:
      CVip::AddVipTime(this, 2, pVip->AddVipTime);
      break;
    case 3:
      CVip::AddVipTime(this, 3, pVip->AddVipTime);
      break;
  }
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Player::setSyncStatusFlag(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v7 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v7, ConnId, GateIndex, Proc, VipType);
  VipLevel = CVip::GetVipLevel(this);
  CVip::BuyGongGao(this, 22, VipType, VipLevel);
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::updateTaskCount(Task, 22, 0);
  CVip::SendVipInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CVip::OnEnterClub(CVip *const this, Answer::NetPacket *inPacket)
{
  int32_t Now; // r13d
  int32_t VipLevel; // r12d
  CharId_t Cid; // rbx
  CVipClub *v6; // rax
  int8_t ConnId; // bl
  GameService *v8; // rax
  CharId_t v9; // rax
  uint32_t WOffset; // eax
  int8_t v11; // bl
  GameService *v12; // rax
  std::string p_name; // [rsp+10h] [rbp-50h] BYREF
  std::string val; // [rsp+20h] [rbp-40h] BYREF
  int32_t nVipLevel; // [rsp+34h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( CVip::GetVipLevel(this) <= 0 )
    return 2;
  this->m_Club = 1;
  this->m_ClubDropTimes = 1;
  Now = Unit::getNow(this->m_pPlayer);
  VipLevel = CVip::GetVipLevel(this);
  Player::getName((const Player *const)&p_name);
  Cid = Player::getCid(this->m_pPlayer);
  v6 = Answer::Singleton<CVipClub>::instance();
  CVipClub::UpdateClubData(v6, Cid, &p_name, VipLevel, Now);
  std::string::~string(&p_name);
  CVip::SendClubInfo(this);
  nVipLevel = CVip::GetVipLevel(this);
  if ( nVipLevel > 6 )
    this->m_nVip7Time = Unit::getNow(this->m_pPlayer);
  if ( nVipLevel > 9 )
    this->m_nVip10Time = Unit::getNow(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v8, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 3008);
    v9 = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, v9);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v11 = Player::getConnId(this->m_pPlayer);
    v12 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v12, v11, packet);
  }
  return 0;
}


#####################################
int32_t __cdecl CVip::OnBuyDropTimes(CVip *const this, Answer::NetPacket *inPacket)
{
  int8_t VipLevel; // bl
  CfgData *v4; // rax
  VipTable *VipTable; // rax
  int32_t m_BuyTimes; // eax
  VipCfg *pVipCfg; // [rsp+10h] [rbp-20h]
  int32_t nPrice; // [rsp+1Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  VipLevel = CVip::GetVipLevel(this);
  v4 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v4);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( !pVipCfg )
    return 2;
  if ( this->m_BuyTimes >= pVipCfg->ClubBuyTimes )
    return 2;
  m_BuyTimes = this->m_BuyTimes;
  if ( m_BuyTimes == 1 )
  {
    nPrice = 1000;
  }
  else if ( m_BuyTimes == 2 )
  {
    nPrice = 2000;
  }
  else
  {
    if ( m_BuyTimes )
      return 2;
    nPrice = 500;
  }
  if ( Player::DecCurrency(
         this->m_pPlayer,
         CURRENCY_TYPE::CURRENCY_GOLD,
         nPrice,
         CURRENCY_CHANGE_REASON::GCR_VIP_BUY_DROP_TIMES,
         0) )
  {
    ++this->m_BuyTimes;
    ++this->m_ClubDropTimes;
    CVip::SendClubInfo(this);
  }
  return 2;
}


#####################################
int32_t __cdecl CVip::OnBuyAllVipCard(CVip *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgData *v4; // rax
  int8_t VipLevel; // cl
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  ChrTask *Task; // rax
  int32_t NeedGold; // [rsp+1Ch] [rbp-44h]
  int32_t NeeVipLevel; // [rsp+20h] [rbp-40h]
  int32_t i; // [rsp+24h] [rbp-3Ch]
  VipCardCfg *pVip; // [rsp+28h] [rbp-38h]
  int32_t i_0; // [rsp+34h] [rbp-2Ch]
  VipCardCfg *pVip_0; // [rsp+38h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  NeedGold = 0;
  NeeVipLevel = 0;
  for ( i = 0; i <= 2; ++i )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    pVip = CfgData::GetVipCardCfg(v3, (unsigned __int8)i + 1);
    if ( pVip )
    {
      NeedGold += pVip->NeedGold;
      if ( pVip->VipLevel > NeeVipLevel )
        NeeVipLevel = pVip->VipLevel;
    }
  }
  if ( CVip::GetVipLevel(this) < NeeVipLevel )
    return 2;
  if ( NeedGold <= 0 )
    return 2;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          19064,
          CURRENCY_CHANGE_REASON::GCR_BUY_VIP_CARD,
          0) )
    return 2;
  for ( i_0 = 0; i_0 <= 2; ++i_0 )
  {
    v4 = Answer::Singleton<CfgData>::instance();
    pVip_0 = CfgData::GetVipCardCfg(v4, (unsigned __int8)i_0 + 1);
    if ( pVip_0 )
    {
      CVip::AddVipTime(this, i_0 + 1, pVip_0->AddVipTime);
      VipLevel = CVip::GetVipLevel(this);
      CVip::BuyGongGao(this, 22, i_0 + 1, VipLevel);
    }
  }
  Player::recalcAttr(this->m_pPlayer, 0, 0);
  Player::setSyncStatusFlag(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  Task = Player::GetTask(this->m_pPlayer);
  ChrTask::updateTaskCount(Task, 22, 0);
  CVip::SendVipInfo(this);
  return 0;
}


#####################################
void __cdecl CVip::OnUpdate(CVip *const this, int64_t curTick)
{
  if ( curTick - this->m_LastUpdataTick > 60000 )
  {
    CVip::CheckVipEnd(this, curTick);
    this->m_LastUpdataTick = curTick;
  }
}


#####################################
void __cdecl CVip::OnDaySwitch(CVip *const this, int32_t nDiffDays)
{
  CVip::SendVipInfo(this);
  if ( CVip::IsClub(this) )
    this->m_ClubDropTimes = 1;
  this->m_BuyTimes = 0;
  CVip::SendClubInfo(this);
}


#####################################
bool __cdecl CVip::GetVipFlg(CVip *const this, int8_t VipType)
{
  int32_t Now; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  Now = Unit::getNow(this->m_pPlayer);
  switch ( VipType )
  {
    case 1:
      return this->m_PlatinumVipEndTime > Now;
    case 2:
      return this->m_DiamVipEndTime > Now;
    case 3:
      return this->m_StarVipEndTime > Now;
  }
  return 0;
}


#####################################
int32_t __cdecl CVip::GetVipEquipBackRate(CVip *const this)
{
  int8_t VipLevel; // bl
  CfgData *v2; // rax
  VipTable *VipTable; // rax
  VipCfg *pVipCfg; // [rsp+18h] [rbp-18h]

  VipLevel = CVip::GetVipLevel(this);
  v2 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v2);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( pVipCfg )
    return pVipCfg->EquipBackRate;
  else
    return 2;
}


#####################################
int32_t __cdecl CVip::OnGetVipCardGift(CVip *const this, Answer::NetPacket *inPacket)
{
  int32_t Record; // eax
  CfgData *v4; // rax
  int32_t TianShuJinHua; // ebx
  CFaBao *PlayerFaBao; // rax
  int8_t Type; // [rsp+1Fh] [rbp-21h]
  int NewRecord; // [rsp+24h] [rbp-1Ch]
  VipCardCfg *pVip; // [rsp+28h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Type = Answer::NetPacket::readInt8(inPacket);
  if ( !CVip::GetVipFlg(this, Type) )
    return 2;
  Record = Player::getRecord(this->m_pPlayer, 2018);
  NewRecord = Record | (1 << (Type - 1));
  if ( NewRecord == Record )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  pVip = CfgData::GetVipCardCfg(v4, Type);
  if ( !pVip )
    return 2;
  if ( pVip->Money > 0 )
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_BIND_MONEY,
      pVip->Money,
      CURRENCY_CHANGE_REASON::MCR_VIP_CARD,
      0);
  if ( pVip->TianShuJinHua > 0 )
  {
    TianShuJinHua = pVip->TianShuJinHua;
    PlayerFaBao = Player::GetPlayerFaBao(this->m_pPlayer);
    CFaBao::AddFaBaoRes(PlayerFaBao, 0, TianShuJinHua);
  }
  if ( pVip->WeiWang > 0 )
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_HONOR,
      pVip->WeiWang,
      CURRENCY_CHANGE_REASON::MCR_VIP_CARD,
      0);
  Player::updateRecord(this->m_pPlayer, 2018, NewRecord);
  CVip::SendVipInfo(this);
  return 0;
}


#####################################
void __cdecl CVip::BuyGongGao(CVip *const this, int32_t GongGaoId, int8_t VipType, int8_t VipLevel)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v8; // bl
  GameService *v9; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, GongGaoId);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Answer::NetPacket::writeInt8(packet, VipType);
    Answer::NetPacket::writeInt8(packet, VipLevel);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v9, v8, packet);
  }
}


#####################################
int32_t __cdecl CVip::OnGetVipGift(CVip *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  VipTable *VipTable; // rax
  CExtCharBag *Bag; // rax
  GameService *v6; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v9; // rax
  std::string val; // [rsp+10h] [rbp-40h] BYREF
  int8_t VipGiftLevel; // [rsp+27h] [rbp-29h]
  VipCfg *pVipCfg; // [rsp+28h] [rbp-28h]
  int32_t oldRecord; // [rsp+30h] [rbp-20h]
  int32_t NewRecord; // [rsp+34h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 0;
  VipGiftLevel = Answer::NetPacket::readInt8(inPacket);
  if ( VipGiftLevel <= 0 )
    return 2;
  if ( CVip::GetVipLevel(this) < VipGiftLevel )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v3);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipGiftLevel);
  if ( !pVipCfg )
    return 2;
  oldRecord = Player::getRecord(this->m_pPlayer, 1021);
  NewRecord = oldRecord | (1 << (VipGiftLevel - 1));
  if ( oldRecord == NewRecord )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pVipCfg->Item, ITEM_CHANGE_REASON::ICR_VIP_GIFT) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1021, NewRecord);
  CVip::SendVipInfo(this);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( !packet )
    return 2;
  Answer::NetPacket::writeInt32(packet, 449);
  Cid = Player::getCid(this->m_pPlayer);
  Answer::NetPacket::writeInt64(packet, Cid);
  Player::getName((const Player *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::worldBroadcast(v9, 0, packet);
  return 0;
}


#####################################
void __cdecl CVip::AddVipExp(CVip *const this, int32_t VipExp)
{
  CExtOperateLimit *OperateLimit; // rax
  CSpecialEquip *CSpecialEquip; // rax
  int8_t v4; // al
  int32_t Now; // r13d
  int32_t v6; // r12d
  CharId_t Cid; // rbx
  CVipClub *v8; // rax
  GameService *v9; // rax
  CharId_t v10; // rax
  uint32_t WOffset; // eax
  GameService *v12; // rax
  std::string p_name; // [rsp+10h] [rbp-50h] BYREF
  std::string val; // [rsp+20h] [rbp-40h] BYREF
  int32_t OldVipLevel; // [rsp+30h] [rbp-30h]
  int32_t VipLevel; // [rsp+34h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]

  if ( this->m_pPlayer )
  {
    OldVipLevel = CVip::GetVipLevel(this);
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1020, VipExp);
    VipLevel = CVip::GetVipLevel(this);
    if ( OldVipLevel != VipLevel )
    {
      CSpecialEquip = Player::GetCSpecialEquip(this->m_pPlayer);
      CSpecialEquip::SendSpecialEquipIcon(CSpecialEquip);
      Player::setSyncStatusFlag(this->m_pPlayer);
      v4 = CVip::GetVipLevel(this);
      Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_VIP_LEVEL, v4);
      if ( CVip::IsClub(this) )
      {
        Now = Unit::getNow(this->m_pPlayer);
        v6 = CVip::GetVipLevel(this);
        Player::getName((const Player *const)&p_name);
        Cid = Player::getCid(this->m_pPlayer);
        v8 = Answer::Singleton<CVipClub>::instance();
        CVipClub::UpdateClubData(v8, Cid, &p_name, v6, Now);
        std::string::~string(&p_name);
        if ( OldVipLevel <= 6 && VipLevel > 6 )
        {
          this->m_nVip7Time = Unit::getNow(this->m_pPlayer);
          CVip::SendClubInfo(this);
        }
        if ( OldVipLevel <= 9 && VipLevel > 9 )
        {
          this->m_nVip10Time = Unit::getNow(this->m_pPlayer);
          CVip::SendClubInfo(this);
        }
      }
      Player::recalcAttr(this->m_pPlayer, 0, 0);
      if ( !OldVipLevel )
      {
        v9 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v9, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet )
          return;
        Answer::NetPacket::writeInt32(packet, 448);
        v10 = Player::getCid(this->m_pPlayer);
        Answer::NetPacket::writeInt64(packet, v10);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v12 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v12, 0, packet);
      }
    }
    CVip::SendVipInfo(this);
  }
}


#####################################
bool __cdecl CVip::CanSiteRevive(CVip *const this)
{
  int8_t VipLevel; // bl
  CfgData *v3; // rax
  VipTable *VipTable; // rax
  VipCfg *pVipCfg; // [rsp+10h] [rbp-20h]
  int32_t SiteRevive; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  VipLevel = CVip::GetVipLevel(this);
  v3 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v3);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( !pVipCfg )
    return 0;
  SiteRevive = pVipCfg->Revive;
  return Player::getRecord(this->m_pPlayer, 2021) < SiteRevive;
}


#####################################
void __cdecl CVip::GetClubDrop(CVip *const this, int32_t Mid)
{
  CVipClub *v2; // rax
  CfgData *v3; // rax
  Answer::Random *v4; // rax
  const RateItem *v5; // rax
  Answer::Random *v6; // rax
  const RateItem *v7; // rax
  const RateItem *v8; // rax
  int32_t mapid; // r12d
  CharId_t nCreaterId; // rbx
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v13; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v15; // rax
  int32_t itemId; // ebx
  CfgData *v17; // rax
  Player *v18; // r13
  int32_t v19; // r12d
  int32_t m_backIndex; // ebx
  CEquipBack *v21; // rax
  CExtCharBag *Bag; // rax
  std::_Ios_Openmode v23; // eax
  CharId_t Cid; // rbx
  DBService *v25; // rax
  GameService *v26; // rax
  CharId_t v27; // rax
  int32_t v28; // eax
  uint32_t WOffset; // eax
  GameService *v30; // rax
  int8_t v31; // bl
  GameService *v32; // rax
  uint32_t v33; // eax
  int16_t GateIndex; // r12
  int8_t v35; // bl
  GameService *v36; // rax
  MemEquip ss_0; // [rsp+50h] [rbp-260h] BYREF
  MemChrBag stu; // [rsp+1C0h] [rbp-F0h] BYREF
  std::_List_const_iterator<RateItem> iter; // [rsp+1E0h] [rbp-D0h] BYREF
  std::_List_const_iterator<RateItem> it; // [rsp+1F0h] [rbp-C0h] BYREF
  std::_List_const_iterator<RateItem> __x; // [rsp+200h] [rbp-B0h] BYREF
  std::_List_const_iterator<RateItem> v42; // [rsp+210h] [rbp-A0h] BYREF
  std::string p_name; // [rsp+220h] [rbp-90h] BYREF
  std::string Param; // [rsp+230h] [rbp-80h] BYREF
  std::string val; // [rsp+240h] [rbp-70h] BYREF
  int32_t nLevel; // [rsp+24Ch] [rbp-64h]
  const CVipClubLuckyDrop *pCfg; // [rsp+250h] [rbp-60h]
  int32_t ClubRate; // [rsp+258h] [rbp-58h]
  int32_t MaxRate; // [rsp+25Ch] [rbp-54h]
  int32_t GongGaoId; // [rsp+260h] [rbp-50h]
  int32_t nRand; // [rsp+264h] [rbp-4Ch]
  Answer::NetPacket *packet; // [rsp+268h] [rbp-48h]
  const CfgEquip *pEquip; // [rsp+270h] [rbp-40h]
  Answer::NetPacket *packet_0; // [rsp+278h] [rbp-38h]

  if ( this->m_pPlayer )
  {
    if ( this->m_Club > 0 && this->m_ClubDropTimes > 0 )
    {
      v2 = Answer::Singleton<CVipClub>::instance();
      nLevel = CVipClub::GetClubLevel(v2);
      v3 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetCVipClubLuckyDrop(v3, nLevel - 1);
      if ( pCfg )
      {
        v4 = Answer::Singleton<Answer::Random>::instance();
        ClubRate = Answer::Random::generate(v4, 1, 1000);
        if ( pCfg->nRand >= ClubRate )
        {
          MaxRate = 0;
          for ( it._M_node = std::list<RateItem>::begin(&pCfg->lRateItemList)._M_node;
                ;
                std::_List_const_iterator<RateItem>::operator++(&it, 0) )
          {
            __x._M_node = std::list<RateItem>::end(&pCfg->lRateItemList)._M_node;
            if ( !std::_List_const_iterator<RateItem>::operator!=(&it, &__x) )
              break;
            v5 = std::_List_const_iterator<RateItem>::operator->(&it);
            MaxRate += v5->nRate;
          }
          memset(&stu, 0, sizeof(stu));
          GongGaoId = 0;
          v6 = Answer::Singleton<Answer::Random>::instance();
          nRand = Answer::Random::generate(v6, 1, MaxRate);
          for ( iter._M_node = std::list<RateItem>::begin(&pCfg->lRateItemList)._M_node;
                ;
                std::_List_const_iterator<RateItem>::operator++(&iter) )
          {
            v42._M_node = std::list<RateItem>::end(&pCfg->lRateItemList)._M_node;
            if ( !std::_List_const_iterator<RateItem>::operator!=(&iter, &v42) )
              break;
            v7 = std::_List_const_iterator<RateItem>::operator->(&iter);
            if ( v7->nRate >= nRand )
            {
              stu.itemId = std::_List_const_iterator<RateItem>::operator->(&iter)->nItemId;
              stu.itemClass = std::_List_const_iterator<RateItem>::operator->(&iter)->nItemClass;
              stu.itemCount = std::_List_const_iterator<RateItem>::operator->(&iter)->nItemCount;
              stu.bind = std::_List_const_iterator<RateItem>::operator->(&iter)->nBind;
              GongGaoId = std::_List_const_iterator<RateItem>::operator->(&iter)->nGongGaoId;
              break;
            }
            v8 = std::_List_const_iterator<RateItem>::operator->(&iter);
            nRand -= v8->nRate;
          }
          if ( stu.itemId > 0 && stu.itemCount > 0 )
          {
            if ( stu.itemClass == 2 )
            {
              mapid = StaticObj::getMapId(this->m_pPlayer);
              Player::getName((const Player *const)&p_name);
              nCreaterId = Player::getCid(this->m_pPlayer);
              Sid = Player::getSid(this->m_pPlayer);
              ConnId = Player::getConnId(this->m_pPlayer);
              v13 = Answer::Singleton<CEquipManager>::instance();
              CEquipManager::CreateMemEquip(
                &ss_0,
                v13,
                ConnId,
                1474,
                stu.itemId,
                Sid,
                nCreaterId,
                &p_name,
                mapid,
                Mid,
                0,
                0,
                0);
              std::string::~string(&p_name);
              if ( ss_0.id > 0 )
              {
                m_pPlayer = this->m_pPlayer;
                v15 = Answer::Singleton<CEquipManager>::instance();
                CEquipManager::SendPlayerEquipInfo(v15, m_pPlayer, &ss_0);
                stu.srcId = ss_0.id;
              }
              itemId = stu.itemId;
              v17 = Answer::Singleton<CfgData>::instance();
              pEquip = CfgData::getEquip(v17, itemId);
              if ( pEquip && pEquip->m_backIndex > 0 )
              {
                v18 = this->m_pPlayer;
                v19 = stu.itemId;
                m_backIndex = pEquip->m_backIndex;
                v21 = Answer::Singleton<CEquipBack>::instance();
                CEquipBack::KiaFuEquipBack(v21, m_backIndex, v19, Mid, v18);
              }
              MemEquip::~MemEquip(&ss_0);
            }
            Bag = Player::GetBag(this->m_pPlayer);
            if ( !CExtCharBag::AddItem(Bag, &stu, ITEM_CHANGE_REASON::ICR_CLUB_DROP) )
            {
              v23 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
                &ss_0,
                (unsigned int)v23);
              std::ostream::operator<<(&ss_0.owner, (unsigned int)stu.itemId);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, &ss_0);
              Cid = Player::getCid(this->m_pPlayer);
              v25 = Answer::Singleton<DBService>::instance();
              DBService::OnSendSysMail(v25, 0, Cid, 6611, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP, &Param, 0);
              std::string::~string(&Param);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(&ss_0);
            }
            --this->m_ClubDropTimes;
            CVip::SendClubInfo(this);
            if ( GongGaoId > 0 )
            {
              v26 = Answer::Singleton<GameService>::instance();
              packet_0 = GameService::popNetpacket(v26, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
              if ( !packet_0 )
                return;
              Answer::NetPacket::writeInt32(packet_0, GongGaoId);
              v27 = Player::getCid(this->m_pPlayer);
              Answer::NetPacket::writeInt64(packet_0, v27);
              Player::getName((const Player *const)&val);
              Answer::NetPacket::writeUTF8(packet_0, &val);
              std::string::~string(&val);
              v28 = StaticObj::getMapId(this->m_pPlayer);
              Answer::NetPacket::writeInt32(packet_0, v28);
              Answer::NetPacket::writeInt32(packet_0, Mid);
              Answer::NetPacket::writeInt8(packet_0, stu.itemClass);
              Answer::NetPacket::writeInt32(packet_0, stu.itemId);
              WOffset = Answer::NetPacket::getWOffset(packet_0);
              Answer::NetPacket::setSize(packet_0, WOffset);
              v30 = Answer::Singleton<GameService>::instance();
              GameService::worldBroadcast(v30, 0, packet_0);
            }
            v31 = Player::getConnId(this->m_pPlayer);
            v32 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v32, v31, Answer::PackType::PACK_DISPATCH, 0x2CDAu);
            if ( packet )
            {
              Answer::NetPacket::writeInt32(packet, nLevel);
              Answer::NetPacket::writeInt8(packet, 0);
              Answer::NetPacket::writeInt32(packet, stu.itemId);
              Answer::NetPacket::writeInt8(packet, stu.itemClass);
              Answer::NetPacket::writeInt32(packet, stu.itemCount);
              v33 = Answer::NetPacket::getWOffset(packet);
              Answer::NetPacket::setSize(packet, v33);
              GateIndex = Player::getGateIndex(this->m_pPlayer);
              v35 = Player::getConnId(this->m_pPlayer);
              v36 = Answer::Singleton<GameService>::instance();
              GameService::sendPacketTo(v36, v35, GateIndex, packet);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CVip::GetLuckDropType(CVip *const this, int32_t Mid)
{
  int8_t v2; // bl
  CfgData *v3; // rax
  VipTable *VipTable; // rax
  int32_t Luck1; // ebx
  Answer::Random *v6; // rax
  CfgData *v7; // rax
  const LuckDropTable *v8; // rax
  CfgData *v9; // rax
  const LuckDropTable *v10; // rax
  int32_t v11; // r12d
  CharId_t v12; // rbx
  int32_t v13; // r14d
  int32_t v14; // r15d
  int8_t v15; // r13
  CEquipManager *v16; // rax
  Player *v17; // rbx
  CEquipManager *v18; // rax
  int32_t v19; // ebx
  CfgData *v20; // rax
  Player *v21; // r13
  int32_t v22; // r12d
  int32_t v23; // ebx
  CEquipBack *v24; // rax
  CExtCharBag *v25; // rax
  std::_Ios_Openmode v26; // eax
  CharId_t v27; // rbx
  DBService *v28; // rax
  int32_t Luck2; // ebx
  Answer::Random *v30; // rax
  CfgData *v31; // rax
  const LuckDropTable *LuckDropTableTable; // rax
  CfgData *v33; // rax
  const LuckDropTable *v34; // rax
  int32_t MapId; // r12d
  CharId_t Cid; // rbx
  int32_t Sid; // r14d
  int32_t itemId; // r15d
  int8_t ConnId; // r13
  CEquipManager *v40; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v42; // rax
  int32_t v43; // ebx
  CfgData *v44; // rax
  Player *v45; // r13
  int32_t v46; // r12d
  int32_t m_backIndex; // ebx
  CEquipBack *v48; // rax
  CExtCharBag *Bag; // rax
  std::_Ios_Openmode v50; // eax
  CharId_t v51; // rbx
  DBService *v52; // rax
  MemEquip equip; // [rsp+50h] [rbp-260h] BYREF
  MemChrBag Item; // [rsp+1C0h] [rbp-F0h] BYREF
  MemChrBag stu; // [rsp+1E0h] [rbp-D0h] BYREF
  std::string p_name; // [rsp+200h] [rbp-B0h] BYREF
  std::string Param; // [rsp+210h] [rbp-A0h] BYREF
  std::string v58; // [rsp+220h] [rbp-90h] BYREF
  std::string v59; // [rsp+230h] [rbp-80h] BYREF
  VipCfg *pVipCfg; // [rsp+240h] [rbp-70h]
  int32_t DropTimes1; // [rsp+24Ch] [rbp-64h]
  int32_t DropTimes2; // [rsp+250h] [rbp-60h]
  int32_t VipLevel; // [rsp+254h] [rbp-5Ch]
  int32_t nRand; // [rsp+258h] [rbp-58h]
  int32_t CfgRand; // [rsp+25Ch] [rbp-54h]
  const CfgEquip *pEquip; // [rsp+260h] [rbp-50h]
  int32_t VipLevel_0; // [rsp+26Ch] [rbp-44h]
  int32_t nRand_0; // [rsp+270h] [rbp-40h]
  int32_t CfgRand_0; // [rsp+274h] [rbp-3Ch]
  const CfgEquip *pEquip_0; // [rsp+278h] [rbp-38h]

  memset(&stu, 0, sizeof(stu));
  if ( this->m_pPlayer )
  {
    v2 = CVip::GetVipLevel(this);
    v3 = Answer::Singleton<CfgData>::instance();
    VipTable = CfgData::GetVipTable(v3);
    pVipCfg = VipTable::GetVipCfg(VipTable, v2);
    if ( pVipCfg )
    {
      DropTimes1 = Player::getRecord(this->m_pPlayer, 1911);
      DropTimes2 = Player::getRecord(this->m_pPlayer, 1912);
      Luck1 = pVipCfg->Luck1;
      if ( Luck1 + Player::getRecord(this->m_pPlayer, 1906) <= DropTimes1
        || (VipLevel = CVip::GetDropVipLevel(this, 1),
            v6 = Answer::Singleton<Answer::Random>::instance(),
            nRand = Answer::Random::generate(v6, 1, 10000),
            v7 = Answer::Singleton<CfgData>::instance(),
            v8 = CfgData::GetLuckDropTableTable(v7),
            CfgRand = LuckDropTable::GetLuckRate(v8, 1, VipLevel),
            nRand >= CfgRand) )
      {
        Luck2 = pVipCfg->Luck2;
        if ( Luck2 + Player::getRecord(this->m_pPlayer, 1907) > DropTimes2 )
        {
          VipLevel_0 = CVip::GetDropVipLevel(this, 2);
          v30 = Answer::Singleton<Answer::Random>::instance();
          nRand_0 = Answer::Random::generate(v30, 1, 10000);
          v31 = Answer::Singleton<CfgData>::instance();
          LuckDropTableTable = CfgData::GetLuckDropTableTable(v31);
          CfgRand_0 = LuckDropTable::GetLuckRate(LuckDropTableTable, 2, VipLevel_0);
          if ( nRand_0 < CfgRand_0 )
          {
            v33 = Answer::Singleton<CfgData>::instance();
            v34 = CfgData::GetLuckDropTableTable(v33);
            LuckDropTable::GetItem(&Item, v34, 2, VipLevel_0);
            Player::updateRecord(this->m_pPlayer, 1912, DropTimes2 + 1);
            stu.itemId = Item.itemId;
            stu.itemClass = Item.itemClass;
            stu.itemCount = Item.itemCount;
            stu.bind = Item.bind;
            CVip::SendLuckDrop(this, 2, Item, Mid);
            CVip::SendVipInfo(this);
            CVip::AddDropTimes(this, 2, VipLevel_0);
            if ( Item.itemClass == 2 )
            {
              MapId = StaticObj::getMapId(this->m_pPlayer);
              Player::getName((const Player *const)&v58);
              Cid = Player::getCid(this->m_pPlayer);
              Sid = Player::getSid(this->m_pPlayer);
              itemId = stu.itemId;
              ConnId = Player::getConnId(this->m_pPlayer);
              v40 = Answer::Singleton<CEquipManager>::instance();
              CEquipManager::CreateMemEquip(&equip, v40, ConnId, 1416, itemId, Sid, Cid, &v58, MapId, Mid, 0, 0, 0);
              std::string::~string(&v58);
              if ( equip.id > 0 )
              {
                m_pPlayer = this->m_pPlayer;
                v42 = Answer::Singleton<CEquipManager>::instance();
                CEquipManager::SendPlayerEquipInfo(v42, m_pPlayer, &equip);
                stu.srcId = equip.id;
              }
              v43 = Item.itemId;
              v44 = Answer::Singleton<CfgData>::instance();
              pEquip_0 = CfgData::getEquip(v44, v43);
              if ( pEquip_0 && pEquip_0->m_backIndex > 0 )
              {
                v45 = this->m_pPlayer;
                v46 = Item.itemId;
                m_backIndex = pEquip_0->m_backIndex;
                v48 = Answer::Singleton<CEquipBack>::instance();
                CEquipBack::KiaFuEquipBack(v48, m_backIndex, v46, Mid, v45);
              }
              MemEquip::~MemEquip(&equip);
            }
            Bag = Player::GetBag(this->m_pPlayer);
            if ( !CExtCharBag::AddItem(Bag, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP) )
            {
              v50 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
                &equip,
                (unsigned int)v50);
              std::ostream::operator<<(&equip.owner, (unsigned int)stu.itemId);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&v59, &equip);
              v51 = Player::getCid(this->m_pPlayer);
              v52 = Answer::Singleton<DBService>::instance();
              DBService::OnSendSysMail(v52, 0, v51, 1502, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP, &v59, 0);
              std::string::~string(&v59);
              std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(&equip);
            }
          }
        }
      }
      else
      {
        v9 = Answer::Singleton<CfgData>::instance();
        v10 = CfgData::GetLuckDropTableTable(v9);
        LuckDropTable::GetItem(&Item, v10, 1, VipLevel);
        Player::updateRecord(this->m_pPlayer, 1911, DropTimes1 + 1);
        stu.itemId = Item.itemId;
        stu.itemClass = Item.itemClass;
        stu.itemCount = Item.itemCount;
        stu.bind = Item.bind;
        CVip::SendLuckDrop(this, 1, Item, Mid);
        CVip::SendVipInfo(this);
        CVip::AddDropTimes(this, 1, VipLevel);
        if ( Item.itemClass == 2 )
        {
          v11 = StaticObj::getMapId(this->m_pPlayer);
          Player::getName((const Player *const)&p_name);
          v12 = Player::getCid(this->m_pPlayer);
          v13 = Player::getSid(this->m_pPlayer);
          v14 = stu.itemId;
          v15 = Player::getConnId(this->m_pPlayer);
          v16 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v16, v15, 1416, v14, v13, v12, &p_name, v11, Mid, 0, 0, 0);
          std::string::~string(&p_name);
          if ( equip.id > 0 )
          {
            v17 = this->m_pPlayer;
            v18 = Answer::Singleton<CEquipManager>::instance();
            CEquipManager::SendPlayerEquipInfo(v18, v17, &equip);
            stu.srcId = equip.id;
          }
          v19 = Item.itemId;
          v20 = Answer::Singleton<CfgData>::instance();
          pEquip = CfgData::getEquip(v20, v19);
          if ( pEquip && pEquip->m_backIndex > 0 )
          {
            v21 = this->m_pPlayer;
            v22 = Item.itemId;
            v23 = pEquip->m_backIndex;
            v24 = Answer::Singleton<CEquipBack>::instance();
            CEquipBack::KiaFuEquipBack(v24, v23, v22, Mid, v21);
          }
          MemEquip::~MemEquip(&equip);
        }
        v25 = Player::GetBag(this->m_pPlayer);
        if ( !CExtCharBag::AddItem(v25, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP) )
        {
          v26 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
            &equip,
            (unsigned int)v26);
          std::ostream::operator<<(&equip.owner, (unsigned int)stu.itemId);
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, &equip);
          v27 = Player::getCid(this->m_pPlayer);
          v28 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v28, 0, v27, 1501, &stu, ITEM_CHANGE_REASON::ICR_LUCK_DROP, &Param, 0);
          std::string::~string(&Param);
          std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(&equip);
        }
      }
    }
  }
}


#####################################
void __cdecl CVip::AddDropTimes(CVip *const this, int32_t Type, int32_t VipLevel)
{
  VipLuckyDrop *v3; // rax
  VipLuckyDrop *v4; // rax
  int32_t VipLevela; // [rsp+0h] [rbp-10h] BYREF
  int32_t Typea; // [rsp+4h] [rbp-Ch]
  CVip *thisa; // [rsp+8h] [rbp-8h]

  thisa = this;
  Typea = Type;
  VipLevela = VipLevel;
  if ( VipLevel > 0 && VipLevela <= 14 )
  {
    if ( Typea == 1 )
    {
      v3 = std::map<int,VipLuckyDrop>::operator[](&thisa->m_VipLuckyDropMap, &VipLevela);
      ++v3->DropOrdinaryTimes;
    }
    else if ( Typea == 2 )
    {
      v4 = std::map<int,VipLuckyDrop>::operator[](&thisa->m_VipLuckyDropMap, &VipLevela);
      ++v4->DropSpecialTimes;
    }
  }
}


#####################################
int32_t __cdecl CVip::GetDropVipLevel(CVip *const this, int32_t Type)
{
  int32_t DropOrdinaryTimes; // ebx
  int32_t v3; // ebx
  int8_t VipLevel; // al
  int32_t DropSpecialTimes; // ebx
  int8_t v7; // al
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v10; // rax
  int32_t i_0; // [rsp+18h] [rbp-38h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-34h] BYREF
  Int32Vector CanDroplevel; // [rsp+20h] [rbp-30h] BYREF

  std::vector<int>::vector(&CanDroplevel);
  if ( Type == 1 )
  {
    for ( i = 1; i <= 14; ++i )
    {
      VipLevel = CVip::GetVipLevel(this);
      if ( VipLevel < i )
        break;
      DropOrdinaryTimes = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i)->DropOrdinaryTimes;
      if ( DropOrdinaryTimes < std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i)->CanDropOrdinaryTimes )
      {
        v3 = i;
        goto LABEL_27;
      }
    }
  }
  else
  {
    if ( Type != 2 )
    {
      v3 = 0;
      goto LABEL_27;
    }
    for ( i_0 = 1; i_0 <= 14; ++i_0 )
    {
      v7 = CVip::GetVipLevel(this);
      if ( v7 < i_0 )
        break;
      DropSpecialTimes = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i_0)->DropSpecialTimes;
      if ( DropSpecialTimes < std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &i_0)->CanDropSpecialTimes )
      {
        v3 = i_0;
        goto LABEL_27;
      }
    }
  }
  if ( std::vector<int>::size(&CanDroplevel) )
  {
    M_current = std::vector<int>::end(&CanDroplevel)._M_current;
    v10._M_current = std::vector<int>::begin(&CanDroplevel)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
      v10,
      (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
    v3 = *std::vector<int>::front(&CanDroplevel);
  }
  else
  {
    v3 = 0;
  }
LABEL_27:
  std::vector<int>::~vector(&CanDroplevel);
  return v3;
}


#####################################
int32_t __cdecl CVip::GetTreasureTimes(CVip *const this)
{
  int8_t VipLevel; // bl
  CfgData *v2; // rax
  VipTable *VipTable; // rax
  VipCfg *pVipCfg; // [rsp+18h] [rbp-18h]

  VipLevel = CVip::GetVipLevel(this);
  v2 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v2);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( pVipCfg )
    return pVipCfg->TreasureTimes;
  else
    return 0;
}


#####################################
int32_t __cdecl CVip::GetCycleTowerTimes(CVip *const this)
{
  int8_t VipLevel; // bl
  CfgData *v2; // rax
  VipTable *VipTable; // rax
  VipCfg *pVipCfg; // [rsp+18h] [rbp-18h]

  VipLevel = CVip::GetVipLevel(this);
  v2 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v2);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( pVipCfg )
    return pVipCfg->CycleTower;
  else
    return 0;
}


#####################################
void __cdecl CVip::SendLuckDrop(CVip *const this, int32_t nType, MemChrBag stu, int32_t Mid)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  GameService *v10; // rax
  CharId_t Cid; // rax
  int32_t MapId; // eax
  uint32_t v13; // eax
  GameService *v14; // rax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  int32_t GongGaoId; // [rsp+24h] [rbp-1Ch]
  Answer::NetPacket *packet_0; // [rsp+28h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CDAu);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, 0);
    Answer::NetPacket::writeInt8(packet, nType);
    Answer::NetPacket::writeInt32(packet, stu.itemId);
    Answer::NetPacket::writeInt8(packet, stu.itemClass);
    Answer::NetPacket::writeInt32(packet, stu.itemCount);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v9, v8, GateIndex, packet);
  }
  GongGaoId = 0;
  if ( nType == 1 )
  {
    GongGaoId = 456;
  }
  else if ( nType == 2 )
  {
    GongGaoId = 457;
  }
  if ( GongGaoId > 0 )
  {
    v10 = Answer::Singleton<GameService>::instance();
    packet_0 = GameService::popNetpacket(v10, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet_0 )
    {
      Answer::NetPacket::writeInt32(packet_0, GongGaoId);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet_0, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet_0, &val);
      std::string::~string(&val);
      MapId = StaticObj::getMapId(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet_0, MapId);
      Answer::NetPacket::writeInt32(packet_0, Mid);
      Answer::NetPacket::writeInt8(packet_0, stu.itemClass);
      Answer::NetPacket::writeInt32(packet_0, stu.itemId);
      v13 = Answer::NetPacket::getWOffset(packet_0);
      Answer::NetPacket::setSize(packet_0, v13);
      v14 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v14, 0, packet_0);
    }
  }
}


#####################################
int8_t __cdecl CVip::GetVipLevel(CVip *const this)
{
  int32_t VipExp; // ebx
  CfgData *v2; // rax
  VipTable *VipTable; // rax

  VipExp = CVip::GetVipExp(this);
  v2 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v2);
  return VipTable::GetVipLevel(VipTable, VipExp);
}


#####################################
int32_t __cdecl CVip::GetVipExp(CVip *const this)
{
  if ( this->m_pPlayer )
    return Player::getRecord(this->m_pPlayer, 1020);
  else
    return 0;
}


#####################################
void __cdecl CVip::AddVipTime(CVip *const this, int8_t VipType, int32_t Seconds)
{
  int32_t v3; // edx
  int32_t v4; // edx
  int32_t v5; // edx
  int32_t Now; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pPlayer )
  {
    Now = Unit::getNow(this->m_pPlayer);
    switch ( VipType )
    {
      case 1:
        if ( this->m_PlatinumVipEndTime <= Now )
          v3 = Seconds + Now;
        else
          v3 = Seconds + this->m_PlatinumVipEndTime;
        this->m_PlatinumVipEndTime = v3;
        break;
      case 2:
        if ( this->m_DiamVipEndTime <= Now )
          v4 = Seconds + Now;
        else
          v4 = Seconds + this->m_DiamVipEndTime;
        this->m_DiamVipEndTime = v4;
        break;
      case 3:
        if ( this->m_StarVipEndTime <= Now )
          v5 = Seconds + Now;
        else
          v5 = Seconds + this->m_StarVipEndTime;
        this->m_StarVipEndTime = v5;
        break;
    }
  }
}


#####################################
int8_t __cdecl CVip::GetVipType(CVip *const this)
{
  int32_t Now; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  Now = Unit::getNow(this->m_pPlayer);
  if ( this->m_StarVipEndTime > Now )
    return 1;
  if ( this->m_DiamVipEndTime > Now )
    return 2;
  if ( this->m_StarVipEndTime <= Now )
    return 0;
  return 3;
}


#####################################
void __cdecl CVip::AddVipAttr(CVip *const this)
{
  int8_t v1; // bl
  CfgData *v2; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v4; // rax
  int8_t VipLevel; // bl
  CfgData *v6; // rax
  VipTable *VipTable; // rax
  int32_t addon; // ebx
  AttrAddon *v9; // rax
  std::_List_iterator<AddAttribute> it_0; // [rsp+10h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > it; // [rsp+20h] [rbp-50h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+30h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<AttrAddon*,std::vector<AttrAddon> > __rhs; // [rsp+40h] [rbp-30h] BYREF
  int8_t i; // [rsp+4Fh] [rbp-21h]
  VipCfg *pVipCfg; // [rsp+50h] [rbp-20h]
  VipCardCfg *pVip; // [rsp+58h] [rbp-18h]

  i = 0;
  while ( i <= 2 )
  {
    if ( !CVip::GetVipFlg(this, i + 1) )
    {
      ++i;
    }
    else
    {
      v1 = i + 1;
      v2 = Answer::Singleton<CfgData>::instance();
      pVip = CfgData::GetVipCardCfg(v2, v1);
      if ( pVip )
      {
        for ( it_0._M_node = std::list<AddAttribute>::begin(&pVip->AddAttr)._M_node;
              ;
              std::_List_iterator<AddAttribute>::operator++(&it_0) )
        {
          __x._M_node = std::list<AddAttribute>::end(&pVip->AddAttr)._M_node;
          if ( !std::_List_iterator<AddAttribute>::operator!=(&it_0, &__x) )
            break;
          m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
          v4 = std::_List_iterator<AddAttribute>::operator->(&it_0);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v4->m_nAddAttrType, m_nAddAttrValue);
        }
        ++i;
      }
      else
      {
        ++i;
      }
    }
  }
  VipLevel = CVip::GetVipLevel(this);
  v6 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v6);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( pVipCfg )
  {
    for ( it._M_current = std::vector<AttrAddon>::begin(&pVipCfg->AtttVector)._M_current;
          ;
          __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<AttrAddon>::end(&pVipCfg->AtttVector)._M_current;
      if ( !__gnu_cxx::operator!=<AttrAddon *,std::vector<AttrAddon>>(&it, &__rhs) )
        break;
      addon = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it)->addon;
      v9 = __gnu_cxx::__normal_iterator<AttrAddon *,std::vector<AttrAddon>>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v9->index, addon);
    }
  }
}


#####################################
void __cdecl CVip::SendVipInfo(CVip *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t VipExp; // edx
  int32_t Record; // edx
  int32_t v5; // edx
  int32_t v6; // edx
  int32_t v7; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD9u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_PlatinumVipEndTime);
      Answer::NetPacket::writeInt32(packet, this->m_DiamVipEndTime);
      Answer::NetPacket::writeInt32(packet, this->m_StarVipEndTime);
      VipExp = CVip::GetVipExp(this);
      Answer::NetPacket::writeInt32(packet, VipExp);
      Record = Player::getRecord(this->m_pPlayer, 1021);
      Answer::NetPacket::writeInt32(packet, Record);
      v5 = Player::getRecord(this->m_pPlayer, 2018);
      Answer::NetPacket::writeInt32(packet, v5);
      v6 = Player::getRecord(this->m_pPlayer, 1911);
      Answer::NetPacket::writeInt32(packet, v6);
      v7 = Player::getRecord(this->m_pPlayer, 1912);
      Answer::NetPacket::writeInt32(packet, v7);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v10 = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v11, v10, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CVip::OnLoadVipEndTime(CVip *const this, const std::string *const VipEndTime)
{
  std::string *v2; // rax
  const char *v3; // rax
  std::string *v4; // rax
  const char *v5; // rax
  std::string *v6; // rax
  const char *v7; // rax
  StringVector endTime; // [rsp+10h] [rbp-40h] BYREF
  std::string delims; // [rsp+30h] [rbp-20h] BYREF
  _BYTE v10[17]; // [rsp+3Fh] [rbp-11h] BYREF

  if ( this->m_pPlayer )
  {
    std::allocator<char>::allocator(v10);
    std::string::string(&delims, ":");
    Answer::StringUtility::split(&endTime, VipEndTime, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(v10);
    if ( std::vector<std::string>::size(&endTime) == 3 )
    {
      v2 = std::vector<std::string>::operator[](&endTime, 0);
      v3 = (const char *)std::string::c_str(v2);
      this->m_PlatinumVipEndTime = atoi(v3);
      v4 = std::vector<std::string>::operator[](&endTime, 1u);
      v5 = (const char *)std::string::c_str(v4);
      this->m_DiamVipEndTime = atoi(v5);
      v6 = std::vector<std::string>::operator[](&endTime, 2u);
      v7 = (const char *)std::string::c_str(v6);
      this->m_StarVipEndTime = atoi(v7);
    }
    std::vector<std::string>::~vector(&endTime);
  }
}


#####################################
std::string __cdecl CVip::OnSaveVipEndTime(CVip *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  _BYTE v4[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v5[367]; // [rsp+20h] [rbp-180h] BYREF
  _BYTE v6[17]; // [rsp+18Fh] [rbp-11h] BYREF

  if ( *(_QWORD *)(v1 + 8) )
  {
    v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v4, (unsigned int)v2);
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 24));
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 28));
    std::operator<<<std::char_traits<char>>(v5, ":");
    std::ostream::operator<<(v5, *(unsigned int *)(v1 + 32));
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v4);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v4);
  }
  else
  {
    std::allocator<char>::allocator(v6);
    std::string::string(this, &unk_8F4E91);
    std::allocator<char>::~allocator(v6);
  }
  return (std::string)this;
}


#####################################
void __cdecl CVip::CheckVipEnd(CVip *const this, int64_t Tick)
{
  CharId_t Cid; // rbx
  DBService *v3; // rax
  CharId_t v4; // rbx
  DBService *v5; // rax
  CharId_t v6; // rbx
  DBService *v7; // rax
  std::string Param; // [rsp+10h] [rbp-40h] BYREF
  char v9; // [rsp+1Fh] [rbp-31h] BYREF
  std::string v10; // [rsp+20h] [rbp-30h] BYREF
  char v11; // [rsp+2Fh] [rbp-21h] BYREF
  std::string v12; // [rsp+30h] [rbp-20h] BYREF
  char v13; // [rsp+3Bh] [rbp-15h] BYREF
  int32_t Now; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Now = Unit::getNow(this->m_pPlayer);
    if ( this->m_PlatinumVipEndTime > 0 && this->m_PlatinumVipEndTime < Now )
    {
      std::allocator<char>::allocator(&v9);
      std::string::string(&Param, &unk_8F4E91);
      Cid = Player::getCid(this->m_pPlayer);
      v3 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v3, 0, Cid, 6387, &Param, 0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v9);
      this->m_PlatinumVipEndTime = 0;
      Player::RecalcAttr(this->m_pPlayer);
    }
    if ( this->m_DiamVipEndTime > 0 && this->m_DiamVipEndTime < Now )
    {
      std::allocator<char>::allocator(&v11);
      std::string::string(&v10, &unk_8F4E91);
      v4 = Player::getCid(this->m_pPlayer);
      v5 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v5, 0, v4, 6388, &v10, 0);
      std::string::~string(&v10);
      std::allocator<char>::~allocator(&v11);
      this->m_DiamVipEndTime = 0;
      Player::RecalcAttr(this->m_pPlayer);
    }
    if ( this->m_StarVipEndTime > 0 && this->m_StarVipEndTime < Now )
    {
      std::allocator<char>::allocator(&v13);
      std::string::string(&v12, &unk_8F4E91);
      v6 = Player::getCid(this->m_pPlayer);
      v7 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v7, 0, v6, 6389, &v12, 0);
      std::string::~string(&v12);
      std::allocator<char>::~allocator(&v13);
      this->m_StarVipEndTime = 0;
      Player::RecalcAttr(this->m_pPlayer);
    }
  }
}


#####################################
void __cdecl CVip::LoadDropString(CVip *const this, std::string *p_String)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  VipLuckyDrop *v5; // rbx
  std::string *v6; // rax
  const char *v7; // rax
  std::string *v8; // rax
  const char *v9; // rax
  VipLuckyDrop *v10; // rbx
  std::string *v11; // rax
  const char *v12; // rax
  StringVector DropTimesString; // [rsp+10h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+30h] [rbp-80h] BYREF
  StringVector DropString; // [rsp+40h] [rbp-70h] BYREF
  std::string delims; // [rsp+60h] [rbp-50h] BYREF
  char v17; // [rsp+6Fh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+70h] [rbp-40h] BYREF
  std::string v19; // [rsp+80h] [rbp-30h] BYREF
  char v20; // [rsp+97h] [rbp-19h] BYREF
  int __k; // [rsp+98h] [rbp-18h] BYREF
  int v22[5]; // [rsp+9Ch] [rbp-14h] BYREF

  if ( this->m_pPlayer )
  {
    std::allocator<char>::allocator(&v17);
    std::string::string(&delims, "|");
    Answer::StringUtility::split(&DropString, p_String, &delims, 0);
    std::string::~string(&delims);
    std::allocator<char>::~allocator(&v17);
    for ( it._M_current = std::vector<std::string>::begin(&DropString)._M_current;
          ;
          __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<std::string>::end(&DropString)._M_current;
      if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
        break;
      std::allocator<char>::allocator(&v20);
      std::string::string(&v19, ":");
      v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
      Answer::StringUtility::split(&DropTimesString, v2, &v19, 0);
      std::string::~string(&v19);
      std::allocator<char>::~allocator(&v20);
      if ( std::vector<std::string>::size(&DropTimesString) == 3 )
      {
        v3 = std::vector<std::string>::operator[](&DropTimesString, 0);
        v4 = (const char *)std::string::c_str(v3);
        __k = atoi(v4);
        v5 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, &__k);
        v6 = std::vector<std::string>::operator[](&DropTimesString, 1u);
        v7 = (const char *)std::string::c_str(v6);
        v5->DropOrdinaryTimes = atoi(v7);
        v8 = std::vector<std::string>::operator[](&DropTimesString, 0);
        v9 = (const char *)std::string::c_str(v8);
        v22[0] = atoi(v9);
        v10 = std::map<int,VipLuckyDrop>::operator[](&this->m_VipLuckyDropMap, v22);
        v11 = std::vector<std::string>::operator[](&DropTimesString, 2u);
        v12 = (const char *)std::string::c_str(v11);
        v10->DropSpecialTimes = atoi(v12);
      }
      std::vector<std::string>::~vector(&DropTimesString);
    }
    std::vector<std::string>::~vector(&DropString);
  }
}


#####################################
std::string __cdecl CVip::SaveDropString(CVip *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  unsigned int DropOrdinaryTimes; // r12d
  __int64 v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  VipLuckyDrop *v7; // rax
  __int64 v8; // rax
  _BYTE v10[16]; // [rsp+10h] [rbp-190h] BYREF
  _BYTE v11[364]; // [rsp+20h] [rbp-180h] BYREF
  int32_t i[5]; // [rsp+18Ch] [rbp-14h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v10, (unsigned int)v2);
  for ( i[0] = 1; i[0] <= 14; ++i[0] )
  {
    DropOrdinaryTimes = std::map<int,VipLuckyDrop>::operator[]((std::map<int,VipLuckyDrop> *const)(v1 + 40), i)->DropOrdinaryTimes;
    v4 = std::ostream::operator<<(v11, (unsigned int)i[0]);
    v5 = std::operator<<<std::char_traits<char>>(v4, ":");
    v6 = std::ostream::operator<<(v5, DropOrdinaryTimes);
    std::operator<<<std::char_traits<char>>(v6, ":");
    v7 = std::map<int,VipLuckyDrop>::operator[]((std::map<int,VipLuckyDrop> *const)(v1 + 40), i);
    v8 = std::ostream::operator<<(v11, (unsigned int)v7->DropSpecialTimes);
    std::operator<<<std::char_traits<char>>(v8, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v10);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v10);
  return (std::string)this;
}


#####################################
bool __cdecl CVip::HaveVipPrivilege(CVip *const this)
{
  int32_t Now; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  Now = Unit::getNow(this->m_pPlayer);
  if ( this->m_DiamVipEndTime > Now )
    return 1;
  if ( this->m_PlatinumVipEndTime <= Now )
    return this->m_StarVipEndTime > Now;
  return 1;
}


#####################################
bool __cdecl CVip::CanAuction(CVip *const this)
{
  CfgData *v1; // rax
  CfgData *v3; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL) + 1 <= 10 )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) + 1 > 1 && CVip::GetVipLevel(this) <= 0 )
      return 0;
  }
  else if ( CVip::GetVipLevel(this) <= 1 )
  {
    return 0;
  }
  return 1;
}


#####################################
int32_t __cdecl CVip::GetStorePage(CVip *const this)
{
  int8_t VipLevel; // bl
  CfgData *v2; // rax
  VipTable *VipTable; // rax
  VipCfg *pVipCfg; // [rsp+18h] [rbp-18h]

  VipLevel = CVip::GetVipLevel(this);
  v2 = Answer::Singleton<CfgData>::instance();
  VipTable = CfgData::GetVipTable(v2);
  pVipCfg = VipTable::GetVipCfg(VipTable, VipLevel);
  if ( pVipCfg )
    return pVipCfg->StorePage;
  else
    return 0;
}


#####################################
void __cdecl CVip::AddClubDropTime(CVip *const this)
{
  if ( CVip::IsClub(this) && this->m_ClubDropTimes <= 0 )
  {
    this->m_ClubDropTimes = 1;
    CVip::SendClubInfo(this);
  }
}


#####################################
void __cdecl CVip::SendClubInfo(CVip *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  CVipClub *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CF7u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_Club);
      Answer::NetPacket::writeInt32(packet, this->m_ClubDropTimes);
      Answer::NetPacket::writeInt32(packet, this->m_BuyTimes);
      v3 = Answer::Singleton<CVipClub>::instance();
      CVipClub::AppendClubWallInfo(v3, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


