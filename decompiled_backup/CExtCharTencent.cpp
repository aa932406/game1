// Decompiled methods for class: CExtCharTencent
// Source: gameserver.cc
// Total methods: 55

#####################################
void __cdecl CExtCharTencent::~CExtCharTencent(CExtCharTencent *const this)
{
  CExtCharTencent::~CExtCharTencent(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharTencent::OnDaySwitch(CExtCharTencent *const this, int32_t nDiffDays)
{
  CExtCharTencent::resetQZoneDailyReward(this);
  CExtCharTencent::resetQQGameDailyReward(this);
  CExtCharTencent::SendYellowStoneIcon(this);
  CExtCharTencent::SendQZoneIcon(this);
  CExtCharTencent::SendQQGameIcon(this);
  CExtCharTencent::SendBlueStoneIcon(this);
  CExtCharTencent::SendSevenDayLoginIcon(this);
}


#####################################
void __cdecl CExtCharTencent::GetInterestsProtocol(CExtCharTencent *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ch] [rbp-24h] BYREF
  unsigned __int16 v3; // [rsp+1Eh] [rbp-22h] BYREF
  unsigned __int16 v4; // [rsp+20h] [rbp-20h] BYREF
  unsigned __int16 v5; // [rsp+22h] [rbp-1Eh] BYREF
  unsigned __int16 v6; // [rsp+24h] [rbp-1Ch] BYREF
  unsigned __int16 v7; // [rsp+26h] [rbp-1Ah] BYREF
  unsigned __int16 v8; // [rsp+28h] [rbp-18h] BYREF
  unsigned __int16 v9; // [rsp+2Ah] [rbp-16h] BYREF
  unsigned __int16 v10; // [rsp+2Ch] [rbp-14h] BYREF
  unsigned __int16 v11; // [rsp+2Eh] [rbp-12h] BYREF
  unsigned __int16 v12; // [rsp+30h] [rbp-10h] BYREF
  unsigned __int16 v13; // [rsp+32h] [rbp-Eh] BYREF
  unsigned __int16 v14; // [rsp+34h] [rbp-Ch] BYREF
  unsigned __int16 v15; // [rsp+36h] [rbp-Ah] BYREF
  unsigned __int16 v16; // [rsp+38h] [rbp-8h] BYREF
  unsigned __int16 v17; // [rsp+3Ah] [rbp-6h] BYREF
  unsigned __int16 v18; // [rsp+3Ch] [rbp-4h] BYREF
  unsigned __int16 v19; // [rsp+3Eh] [rbp-2h] BYREF

  __x = 215;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 216;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 218;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 220;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 219;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 221;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 223;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 225;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 224;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 226;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 227;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 228;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 235;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 236;
  std::list<unsigned short>::push_back(procList, &v15);
  v16 = 240;
  std::list<unsigned short>::push_back(procList, &v16);
  v17 = 237;
  std::list<unsigned short>::push_back(procList, &v17);
  v18 = 238;
  std::list<unsigned short>::push_back(procList, &v18);
  v19 = 239;
  std::list<unsigned short>::push_back(procList, &v19);
}


#####################################
int32_t __cdecl CExtCharTencent::DispatchNetDatas(
        CExtCharTencent *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  int32_t result; // eax
  bool v4; // bl
  std::string __lhs; // [rsp+20h] [rbp-20h] BYREF

  if ( !inPacket )
    return 2;
  Player::GetPlatform((const Player *const)&__lhs);
  v4 = std::operator!=<char>(&__lhs, "qq");
  std::string::~string(&__lhs);
  if ( v4 )
    return 2;
  switch ( nProcId )
  {
    case 0xD7u:
      result = CExtCharTencent::onGetQQGameGift(this, inPacket);
      break;
    case 0xD8u:
      result = CExtCharTencent::onGetQZoneGift(this, inPacket);
      break;
    case 0xDAu:
      result = CExtCharTencent::onGetYellowNewerAward(this, inPacket);
      break;
    case 0xDBu:
      result = CExtCharTencent::onGetYellowDailyAward(this, inPacket);
      break;
    case 0xDCu:
      result = CExtCharTencent::onGetYellowYearAward(this, inPacket);
      break;
    case 0xDDu:
      result = CExtCharTencent::onGetYellowLevelAward(this, inPacket);
      break;
    case 0xDFu:
      result = CExtCharTencent::onGetBlueAward(this, inPacket);
      break;
    case 0xE0u:
      result = CExtCharTencent::onGetBlueDailyAward(this, inPacket);
      break;
    case 0xE1u:
      result = CExtCharTencent::onGetBlueYearAward(this, inPacket);
      break;
    case 0xE2u:
      result = CExtCharTencent::onGetBlueLevelAward(this, inPacket);
      break;
    case 0xE3u:
      result = CExtCharTencent::onGetBlueHighAward(this, inPacket);
      break;
    case 0xE4u:
      result = CExtCharTencent::onReloadTencentInfo(this, inPacket);
      break;
    case 0xEBu:
      result = CExtCharTencent::onRequestSevenDayLoginInfo(this, inPacket);
      break;
    case 0xECu:
      result = CExtCharTencent::onGetSevenDayLoginReward(this, inPacket);
      break;
    case 0xEDu:
      result = CExtCharTencent::onGetTGPAward(this, inPacket);
      break;
    case 0xEEu:
      result = CExtCharTencent::onGetTGPDailyAward(this, inPacket);
      break;
    case 0xEFu:
      result = CExtCharTencent::onGetTGPLevelAward(this, inPacket);
      break;
    case 0xF0u:
      result = CExtCharTencent::onRequestTGPInfo(this, inPacket);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CExtCharTencent::onRequestYellowStoneInfo(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int8_t Record; // dl
  int32_t v6; // edx
  int8_t v7; // dl
  int32_t v8; // edx
  int32_t v9; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2822u);
  if ( !packet )
    return 10002;
  Record = Player::getRecord(this->m_pPlayer, 37000);
  Answer::NetPacket::writeInt8(packet, Record);
  v6 = Player::getRecord(this->m_pPlayer, 7000);
  Answer::NetPacket::writeInt32(packet, v6);
  v7 = Player::getRecord(this->m_pPlayer, 7001);
  Answer::NetPacket::writeInt8(packet, v7);
  v8 = Player::getRecord(this->m_pPlayer, 37001);
  Answer::NetPacket::writeInt32(packet, v8);
  v9 = Player::getRecord(this->m_pPlayer, 37008);
  Answer::NetPacket::writeInt32(packet, v9);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v12 = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v13, v12, GateIndex, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetYellowNewerAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  const MemChrBagVector *vReward; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsYellowVip(this) )
    return 10002;
  if ( CExtCharTencent::GetYellowVipLevel(this) <= 0 )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 37000) )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  vReward = CfgTencentTable::GetYellowNewerGift(TencentTable);
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, vReward, ITEM_CHANGE_REASON::ICR_YELLOW_NEWER_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37000, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendYellowStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetYellowDailyAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int32_t YellowVipLevel; // ebx
  CfgData *v4; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  const CfgTencentGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsYellowVip(this) )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 7000) )
    return 10002;
  YellowVipLevel = CExtCharTencent::GetYellowVipLevel(this);
  v4 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v4);
  pCfgGift = CfgTencentTable::GetYellowDailyGift(TencentTable, YellowVipLevel);
  if ( !pCfgGift )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_YELLOW_DAILY_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 7000, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendYellowStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetYellowYearAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int32_t YellowVipLevel; // ebx
  CfgData *v4; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  const CfgTencentGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsYellowVip(this) )
    return 10002;
  if ( !CExtCharTencent::IsYellowYearVip(this) )
    return 10002;
  YellowVipLevel = CExtCharTencent::GetYellowVipLevel(this);
  v4 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v4);
  pCfgGift = CfgTencentTable::GetYellowYearGift(TencentTable, YellowVipLevel);
  if ( !pCfgGift )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 7001) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_YELLOW_YEAR_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 7001, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendYellowStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetYellowLevelAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  CExtCharBag *v6; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  char nIndex; // [rsp+16h] [rbp-3Ah]
  int8_t bVip; // [rsp+17h] [rbp-39h]
  const CfgTencentGift *pCfgGift; // [rsp+18h] [rbp-38h]
  int32_t nRecord; // [rsp+24h] [rbp-2Ch]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  bVip = Answer::NetPacket::readInt8(inPacket);
  if ( nIndex < 0 )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  pCfgGift = CfgTencentTable::GetYellowLevelGift(TencentTable, nIndex);
  if ( !pCfgGift )
    return 10002;
  if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < pCfgGift->nLevel )
    return 10002;
  nRecord = 37001;
  if ( bVip )
  {
    if ( !CExtCharTencent::IsYellowVip(this) )
      return 10002;
    if ( CExtCharTencent::GetYellowVipLevel(this) <= 0 )
      return 10002;
    nRecord = 37008;
  }
  nOldRecord = Player::getRecord(this->m_pPlayer, nRecord);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  if ( bVip )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vVipRewards, ITEM_CHANGE_REASON::ICR_YELLOW_LEVEL_REWARD) )
      return 10002;
  }
  else
  {
    v6 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(v6, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_YELLOW_LEVEL_REWARD) )
      return 10002;
  }
  Player::updateRecord(this->m_pPlayer, nRecord, nNewRecord);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, nIndex);
  CExtCharTencent::SendYellowStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetQZoneGift(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  bool v3; // bl
  int32_t v4; // ebx
  CfgData *v5; // rax
  const CfgTencentTable *TencentTable; // rax
  MemChrBagVector *p_vReward; // rbx
  CExtCharBag *Bag; // rax
  int64_t v9; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  int8_t nIndex; // [rsp+1Fh] [rbp-31h]
  const CfgQQGift *pCfgGift; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int32_t nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( nIndex < 0 )
    return 10002;
  Player::GetPlatform((const Player *const)&__lhs);
  v3 = std::operator!=<char>(&__lhs, "qq");
  std::string::~string(&__lhs);
  if ( v3 )
    return 10002;
  if ( std::operator!=<char>(&this->m_info.m_pf, "qzone") )
    return 10002;
  v4 = nIndex;
  v5 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v5);
  pCfgGift = CfgTencentTable::GetQQZoneGift(TencentTable, v4);
  if ( !pCfgGift )
    return 10002;
  if ( !CExtCharTencent::checkQQGiftCondition(this, pCfgGift->nType, pCfgGift->nCondition) )
    return 10002;
  nOldRecord = Player::getRecord(this->m_pPlayer, 37006);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  p_vReward = &pCfgGift->vReward;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_vReward, ITEM_CHANGE_REASON::ICR_TENCENT_QZONE_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37006, nNewRecord);
  v9 = nIndex;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v13, ConnId, GateIndex, Proc, v9);
  CExtCharTencent::SendQZoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetQQGameGift(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  bool v3; // bl
  int32_t v4; // ebx
  CfgData *v5; // rax
  const CfgTencentTable *TencentTable; // rax
  MemChrBagVector *p_vReward; // rbx
  CExtCharBag *Bag; // rax
  int64_t v9; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  int8_t nIndex; // [rsp+1Fh] [rbp-31h]
  const CfgQQGift *pCfgGift; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int32_t nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( nIndex < 0 )
    return 10002;
  Player::GetPlatform((const Player *const)&__lhs);
  v3 = std::operator!=<char>(&__lhs, "qq");
  std::string::~string(&__lhs);
  if ( v3 )
    return 10002;
  if ( std::operator!=<char>(&this->m_info.m_pf, "qqgame") )
    return 10002;
  v4 = nIndex;
  v5 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v5);
  pCfgGift = CfgTencentTable::GetQQGameGift(TencentTable, v4);
  if ( !pCfgGift )
    return 10002;
  if ( !CExtCharTencent::checkQQGiftCondition(this, pCfgGift->nType, pCfgGift->nCondition) )
    return 10002;
  nOldRecord = Player::getRecord(this->m_pPlayer, 37009);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  p_vReward = &pCfgGift->vReward;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_vReward, ITEM_CHANGE_REASON::ICR_TENCENT_QQGAME_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37009, nNewRecord);
  v9 = nIndex;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v13, ConnId, GateIndex, Proc, v9);
  CExtCharTencent::SendQQGameIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onRequestBlueStoneInfo(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int8_t Record; // dl
  int32_t v6; // edx
  int8_t v7; // dl
  int8_t v8; // dl
  int32_t v9; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2824u);
  if ( !packet )
    return 10002;
  Record = Player::getRecord(this->m_pPlayer, 37002);
  Answer::NetPacket::writeInt8(packet, Record);
  v6 = Player::getRecord(this->m_pPlayer, 7002);
  Answer::NetPacket::writeInt32(packet, v6);
  v7 = Player::getRecord(this->m_pPlayer, 7003);
  Answer::NetPacket::writeInt8(packet, v7);
  v8 = Player::getRecord(this->m_pPlayer, 7004);
  Answer::NetPacket::writeInt8(packet, v8);
  v9 = Player::getRecord(this->m_pPlayer, 37003);
  Answer::NetPacket::writeInt32(packet, v9);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v12 = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v13, v12, GateIndex, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetBlueAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  const MemChrBagVector *vReward; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsBlueVip(this) )
    return 10002;
  if ( CExtCharTencent::GetBlueVipLevel(this) <= 0 )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 37002) )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  vReward = CfgTencentTable::GetBlueNewerGift(TencentTable);
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, vReward, ITEM_CHANGE_REASON::ICR_BLUE_NEWER_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37002, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendBlueStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetBlueDailyAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int32_t BlueVipLevel; // ebx
  CfgData *v4; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  const CfgTencentGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsBlueVip(this) )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 7002) )
    return 10002;
  BlueVipLevel = CExtCharTencent::GetBlueVipLevel(this);
  v4 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v4);
  pCfgGift = CfgTencentTable::GetBlueDailyGift(TencentTable, BlueVipLevel);
  if ( !pCfgGift )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_BLUE_DAILY_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 7002, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendBlueStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetBlueYearAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int32_t BlueVipLevel; // ebx
  CfgData *v4; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  const CfgTencentGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsBlueVip(this) )
    return 10002;
  if ( !CExtCharTencent::IsBlueYearVip(this) )
    return 10002;
  BlueVipLevel = CExtCharTencent::GetBlueVipLevel(this);
  v4 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v4);
  pCfgGift = CfgTencentTable::GetBlueYearGift(TencentTable, BlueVipLevel);
  if ( !pCfgGift )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 7003) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_BLUE_YEAR_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 7003, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendBlueStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetBlueHighAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int32_t BlueVipLevel; // ebx
  CfgData *v4; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  const CfgTencentGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::IsBlueVip(this) )
    return 10002;
  if ( !CExtCharTencent::IsBlueHighVip(this) )
    return 10002;
  BlueVipLevel = CExtCharTencent::GetBlueVipLevel(this);
  v4 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v4);
  pCfgGift = CfgTencentTable::GetBlueHighGift(TencentTable, BlueVipLevel);
  if ( !pCfgGift )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 7004) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_BLUE_HIGH_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 7004, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendBlueStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetBlueLevelAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  char nIndex; // [rsp+1Fh] [rbp-31h]
  const CfgTencentGift *pCfgGift; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( nIndex < 0 )
    return 10002;
  if ( !CExtCharTencent::IsBlueVip(this) )
    return 10002;
  if ( CExtCharTencent::GetBlueVipLevel(this) <= 0 )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  pCfgGift = CfgTencentTable::GetBlueLevelGift(TencentTable, nIndex);
  if ( !pCfgGift )
    return 10002;
  if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < pCfgGift->nLevel )
    return 10002;
  nOldRecord = Player::getRecord(this->m_pPlayer, 37003);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vRewards, ITEM_CHANGE_REASON::ICR_BLUE_LEVEL_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37003, nNewRecord);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, nIndex);
  CExtCharTencent::SendBlueStoneIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onReloadTencentInfo(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v5; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  Cid = Player::getCid(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v5 = Answer::Singleton<DBService>::instance();
  DBService::ReloadTencentInfo(v5, ConnId, Cid);
  Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_TENCENT_INFO, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onRequestSevenDayLoginInfo(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int32_t LoginDay; // edx
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2825u);
  if ( !packet )
    return 10002;
  LoginDay = CExtCharTencent::getLoginDay(this);
  Answer::NetPacket::writeInt32(packet, LoginDay);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1130);
  Answer::NetPacket::writeInt32(packet, LimitCount);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v10 = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v11, v10, GateIndex, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetSevenDayLoginReward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v7; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v11; // rax
  int8_t nDay; // [rsp+17h] [rbp-39h]
  const CfgTencentSevenDayLogin *pCfg; // [rsp+18h] [rbp-38h]
  int32_t nLoginCount; // [rsp+24h] [rbp-2Ch]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nDay = Answer::NetPacket::readInt8(inPacket);
  if ( !CExtCharTencent::isInSevenDay(this) )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  pCfg = CfgTencentTable::GetSevenDayLogin(TencentTable, nDay);
  if ( !pCfg )
    return 10002;
  nLoginCount = CExtCharTencent::getLoginDay(this);
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nOldRecord = CExtOperateLimit::GetLimitCount(OperateLimit, 1130);
  if ( nDay > nLoginCount )
    return 10002;
  if ( (nOldRecord | (1 << (nDay - 1))) == nOldRecord )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vReward, ITEM_CHANGE_REASON::ICR_TENCENT_SEVEN_DAY_LOGIN_REWARD) )
    return 10002;
  v7 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::UpdateLimitCount(v7, 1130, nOldRecord | (1 << (nDay - 1)));
  CExtCharTencent::SendSevenDayLoginIcon(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v11, ConnId, GateIndex, Proc, nDay);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onRequestTGPInfo(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int8_t Record; // dl
  int8_t v6; // dl
  int32_t v7; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 10002;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2826u);
  if ( !packet )
    return 10002;
  Record = Player::getRecord(this->m_pPlayer, 37004);
  Answer::NetPacket::writeInt8(packet, Record);
  v6 = Player::getRecord(this->m_pPlayer, 7005);
  Answer::NetPacket::writeInt8(packet, v6);
  v7 = Player::getRecord(this->m_pPlayer, 37005);
  Answer::NetPacket::writeInt32(packet, v7);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v10 = Player::getConnId(this->m_pPlayer);
  v11 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v11, v10, GateIndex, packet);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetTGPAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  const CfgTGPGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::isTGPEnter(this) )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 37004) )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  pCfgGift = CfgTencentTable::GetTGPNewerGift(TencentTable, &this->m_info.m_pf);
  if ( !pCfgGift )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vReward, ITEM_CHANGE_REASON::ICR_TGP_NEWER_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37004, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendTGPIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetTGPDailyAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  const CfgTGPGift *pCfgGift; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( !CExtCharTencent::isTGPEnter(this) )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 7005) )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  pCfgGift = CfgTencentTable::GetTGPDailyGift(TencentTable, &this->m_info.m_pf);
  if ( !pCfgGift )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vReward, ITEM_CHANGE_REASON::ICR_TGP_DAILY_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 7005, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  CExtCharTencent::SendTGPIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharTencent::onGetTGPLevelAward(CExtCharTencent *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  char nIndex; // [rsp+1Fh] [rbp-31h]
  const CfgTGPGift *pCfgGift; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  if ( nIndex < 0 )
    return 10002;
  if ( !CExtCharTencent::isTGPEnter(this) )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  pCfgGift = CfgTencentTable::GetTGPLevelGift(TencentTable, &this->m_info.m_pf, nIndex);
  if ( !pCfgGift )
    return 10002;
  if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < pCfgGift->nLevel )
    return 10002;
  nOldRecord = Player::getRecord(this->m_pPlayer, 37005);
  nNewRecord = nOldRecord | (1 << nIndex);
  if ( nOldRecord == nNewRecord )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgGift->vReward, ITEM_CHANGE_REASON::ICR_TGP_LEVEL_REWARD) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 37005, nNewRecord);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, nIndex);
  CExtCharTencent::SendTGPIcon(this);
  return 0;
}


#####################################
void __cdecl CExtCharTencent::GetYellowStoneIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && CExtCharTencent::isYellowEnter(this) )
    {
      CExtCharTencent::getYellowStoneIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendYellowStoneIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  ShowIcon stu2; // [rsp+10h] [rbp-60h] BYREF
  ShowIcon stu; // [rsp+30h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+50h] [rbp-20h] BYREF
  int32_t bReward; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && CExtCharTencent::isYellowEnter(this) )
    {
      bReward = CExtCharTencent::canGetYellowReward(this);
      *(_QWORD *)&stu.nId = 73;
      *(_QWORD *)&stu.nLeftTime = 0;
      *(_QWORD *)&stu.nIconRight = 0;
      if ( bReward <= 0 )
      {
        stu.nState = 4;
      }
      else
      {
        stu.nState = 2;
        stu.nIconRight = bReward;
      }
      Player::SendIconState(this->m_pPlayer, &stu);
      *(_QWORD *)&stu2.nId = 172;
      *(_QWORD *)&stu2.nLeftTime = 0;
      *(_QWORD *)&stu2.nIconRight = 0;
      if ( bReward <= 0 )
        stu2.nState = 2;
      else
        stu2.nState = 4;
      Player::SendIconState(this->m_pPlayer, &stu2);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetQZoneIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && !std::operator!=<char>(&this->m_info.m_pf, "qzone") )
    {
      CExtCharTencent::getQZoneIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendQZoneIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && !std::operator!=<char>(&this->m_info.m_pf, "qzone") )
    {
      CExtCharTencent::getQZoneIcon(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetQQGameIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && !std::operator!=<char>(&this->m_info.m_pf, "qqgame") )
    {
      CExtCharTencent::getQQGameIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendQQGameIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && !std::operator!=<char>(&this->m_info.m_pf, "qqgame") )
    {
      CExtCharTencent::getQQGameIcon(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetYellowNewerIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && CExtCharTencent::isYellowEnter(this) )
    {
      CExtCharTencent::getYellowNewerIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendYellowNewerIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && CExtCharTencent::isYellowEnter(this) )
    {
      CExtCharTencent::getYellowNewerIcon(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
int32_t __cdecl CExtCharTencent::canGetYellowReward(CExtCharTencent *const this)
{
  CfgData *v3; // rax
  const CfgTencentTable *TencentTable; // rax
  int32_t v5; // ebx
  const std::pair<const int,CfgTencentGift> *v6; // rax
  const std::pair<const int,CfgTencentGift> *v8; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTencentGift> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTencentGift> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-24h]
  const CfgTencentGiftMap *levelMap; // [rsp+30h] [rbp-20h]
  int32_t nOldRecord; // [rsp+38h] [rbp-18h]
  int32_t nNewRecord; // [rsp+3Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  Count = 0;
  if ( CExtCharTencent::IsYellowVip(this) && CExtCharTencent::GetYellowVipLevel(this) > 0 )
  {
    if ( !Player::getRecord(this->m_pPlayer, 37000) )
      ++Count;
    if ( !Player::getRecord(this->m_pPlayer, 7000) )
      ++Count;
  }
  if ( CExtCharTencent::IsYellowYearVip(this) && !Player::getRecord(this->m_pPlayer, 7001) )
    ++Count;
  v3 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v3);
  levelMap = CfgTencentTable::GetYellowLevelGiftMap(TencentTable);
  for ( iter._M_node = std::map<int,CfgTencentGift>::begin(levelMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgTencentGift>::end(levelMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator!=(&iter, &__x) )
      break;
    v5 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    if ( v5 >= std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator->(&iter)->second.nLevel )
    {
      nOldRecord = Player::getRecord(this->m_pPlayer, 37001);
      v6 = std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator->(&iter);
      nNewRecord = nOldRecord | (1 << v6->first);
      if ( nOldRecord != nNewRecord )
        ++Count;
      if ( CExtCharTencent::IsYellowVip(this) && CExtCharTencent::GetYellowVipLevel(this) > 0 )
      {
        nOldRecord = Player::getRecord(this->m_pPlayer, 37008);
        v8 = std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator->(&iter);
        nNewRecord = nOldRecord | (1 << v8->first);
        if ( nOldRecord != nNewRecord )
          ++Count;
      }
    }
  }
  return Count;
}


#####################################
void __cdecl CExtCharTencent::GetBlueStoneIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && CExtCharTencent::isBlueEnter(this) )
    {
      CExtCharTencent::getBlueStoneIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendBlueStoneIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  ShowIcon stu2; // [rsp+10h] [rbp-60h] BYREF
  ShowIcon stu; // [rsp+30h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+50h] [rbp-20h] BYREF
  int32_t bReward; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && CExtCharTencent::isBlueEnter(this) )
    {
      bReward = CExtCharTencent::canGetBlueReward(this);
      *(_QWORD *)&stu.nId = 75;
      *(_QWORD *)&stu.nLeftTime = 0;
      *(_QWORD *)&stu.nIconRight = 0;
      if ( bReward <= 0 )
      {
        stu.nState = 4;
      }
      else
      {
        stu.nState = 2;
        stu.nIconRight = bReward;
      }
      Player::SendIconState(this->m_pPlayer, &stu);
      *(_QWORD *)&stu2.nId = 77;
      *(_QWORD *)&stu2.nLeftTime = 0;
      *(_QWORD *)&stu2.nIconRight = 0;
      if ( bReward )
        stu2.nState = 4;
      else
        stu2.nState = 2;
      Player::SendIconState(this->m_pPlayer, &stu2);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetBluePayIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && CExtCharTencent::isBlueEnter(this) )
    {
      CExtCharTencent::getBluePayIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendBluePayIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && CExtCharTencent::isBlueEnter(this) )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet )
      {
        CExtCharTencent::getBluePayIcon(&stu, this);
        Answer::NetPacket::writeInt32(packet, stu.nId);
        Answer::NetPacket::writeInt8(packet, stu.nState);
        Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
        Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
        Answer::NetPacket::writeInt32(packet, stu.nIconRight);
        Answer::NetPacket::writeInt8(packet, stu.nEffects);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v6 = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetSevenDayLoginIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 )
    {
      CExtCharTencent::getSevenDayLoginIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendSevenDayLoginIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet )
      {
        CExtCharTencent::getSevenDayLoginIcon(&stu, this);
        Answer::NetPacket::writeInt32(packet, stu.nId);
        Answer::NetPacket::writeInt8(packet, stu.nState);
        Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
        Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
        Answer::NetPacket::writeInt32(packet, stu.nIconRight);
        Answer::NetPacket::writeInt8(packet, stu.nEffects);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v6 = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetTGPIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && CExtCharTencent::isTGPEnter(this) )
    {
      CExtCharTencent::getTGPIcon(&stu, this);
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::SendTGPIcon(CExtCharTencent *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v1 && CExtCharTencent::isTGPEnter(this) )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet )
      {
        CExtCharTencent::getTGPIcon(&stu, this);
        Answer::NetPacket::writeInt32(packet, stu.nId);
        Answer::NetPacket::writeInt8(packet, stu.nState);
        Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
        Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
        Answer::NetPacket::writeInt32(packet, stu.nIconRight);
        Answer::NetPacket::writeInt8(packet, stu.nEffects);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v6 = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CExtCharTencent::GetFriendIcon(CExtCharTencent *const this, IconStateList *const IconList)
{
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "qq");
    std::string::~string(&__lhs);
    if ( !v2 && CExtCharTencent::isYellowEnter(this) )
    {
      *(_QWORD *)&stu.nId = 0x20000004ALL;
      *(_QWORD *)&stu.nLeftTime = 0;
      *(_QWORD *)&stu.nIconRight = 0;
      std::list<ShowIcon>::push_back(IconList, &stu);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::AppendInfo(CExtCharTencent *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeUTF8(packet, &this->m_info.m_pf);
    if ( CExtCharTencent::isYellowEnter(this) )
    {
      Answer::NetPacket::writeInt8(packet, this->m_info.m_bYellowVip);
      Answer::NetPacket::writeInt8(packet, this->m_info.m_bYellowYearVip);
      Answer::NetPacket::writeInt8(packet, this->m_info.m_bYellowHighVip);
      Answer::NetPacket::writeInt8(packet, this->m_info.m_nYellowVipLevel);
    }
    else if ( CExtCharTencent::isBlueEnter(this) )
    {
      Answer::NetPacket::writeInt8(packet, this->m_info.m_bBlueVip);
      Answer::NetPacket::writeInt8(packet, this->m_info.m_bBlueYearVip);
      Answer::NetPacket::writeInt8(packet, this->m_info.m_bBlueHighVip);
      Answer::NetPacket::writeInt8(packet, this->m_info.m_nBlueVipLevel);
    }
    else
    {
      Answer::NetPacket::writeInt8(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
      Answer::NetPacket::writeInt8(packet, 0);
    }
  }
}


#####################################
void __cdecl CExtCharTencent::InitTencentInfo(CExtCharTencent *const this, const TencentInfo *const info)
{
  TencentInfo::operator=(&this->m_info, info);
}


#####################################
void __cdecl CExtCharTencent::UpdateTencentInfo(CExtCharTencent *const this, const TencentInfo *const info)
{
  if ( this->m_pPlayer )
  {
    TencentInfo::operator=(&this->m_info, info);
    CExtCharTencent::SendBlueStoneIcon(this);
    CExtCharTencent::SendBluePayIcon(this);
    Unit::setNeedSyncSelf(this->m_pPlayer);
    Player::SetNeedSyncAround(this->m_pPlayer);
    Player::setSyncToTeamFlag(this->m_pPlayer);
  }
}


#####################################
std::string __cdecl CExtCharTencent::GetPf(const CExtCharTencent *const this)
{
  const std::string *v1; // rsi

  std::string::string((std::string *)this, v1 + 2);
  return (std::string)this;
}


#####################################
int32_t __cdecl CExtCharTencent::canGetBlueReward(CExtCharTencent *const this)
{
  CfgData *v2; // rax
  const CfgTencentTable *TencentTable; // rax
  int32_t v4; // ebx
  const std::pair<const int,CfgTencentGift> *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTencentGift> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgTencentGift> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-24h]
  const CfgTencentGiftMap *levelMap; // [rsp+30h] [rbp-20h]
  int32_t nOldRecord; // [rsp+38h] [rbp-18h]
  int32_t nNewRecord; // [rsp+3Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  Count = 0;
  if ( !CExtCharTencent::IsBlueVip(this) )
    return Count;
  if ( CExtCharTencent::GetBlueVipLevel(this) <= 0 )
    return Count;
  if ( !Player::getRecord(this->m_pPlayer, 37002) )
    ++Count;
  if ( !Player::getRecord(this->m_pPlayer, 7002) )
    ++Count;
  if ( CExtCharTencent::IsBlueYearVip(this) && !Player::getRecord(this->m_pPlayer, 7003) )
    ++Count;
  if ( CExtCharTencent::IsBlueHighVip(this) && !Player::getRecord(this->m_pPlayer, 7004) )
    ++Count;
  v2 = Answer::Singleton<CfgData>::instance();
  TencentTable = CfgData::GetTencentTable(v2);
  levelMap = CfgTencentTable::GetBlueLevelGiftMap(TencentTable);
  for ( iter._M_node = std::map<int,CfgTencentGift>::begin(levelMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgTencentGift>::end(levelMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator!=(&iter, &__x) )
      break;
    v4 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    if ( v4 >= std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator->(&iter)->second.nLevel )
    {
      nOldRecord = Player::getRecord(this->m_pPlayer, 37003);
      v5 = std::_Rb_tree_const_iterator<std::pair<int const,CfgTencentGift>>::operator->(&iter);
      nNewRecord = nOldRecord | (1 << v5->first);
      if ( nOldRecord != nNewRecord )
        ++Count;
    }
  }
  return Count;
}


#####################################
bool __cdecl CExtCharTencent::needShowBluePayIcon(CExtCharTencent *const this)
{
  int32_t EndTime; // eax

  EndTime = TencentInfo::GetEndTime(&this->m_info);
  return (int)abs32(Answer::DayTime::daydiff(EndTime)) <= 2;
}


#####################################
bool __cdecl CExtCharTencent::isInSevenDay(CExtCharTencent *const this)
{
  return this->m_pPlayer && Player::getCreatedDays(this->m_pPlayer) <= 7;
}


#####################################
bool __cdecl CExtCharTencent::needShowSevenDayIcon(CExtCharTencent *const this)
{
  return this->m_pPlayer && Player::getCreatedDays(this->m_pPlayer) <= 8;
}


#####################################
bool __cdecl CExtCharTencent::IsSevenDayLoginExchangeDay(const CExtCharTencent *const this)
{
  char v1; // bl
  bool v2; // al
  bool v3; // r12
  std::string __lhs; // [rsp+10h] [rbp-30h] BYREF

  v1 = 0;
  v2 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = 1;
    if ( !std::operator!=<char>(&__lhs, "qq") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  return !v3 && Player::getCreatedDays(this->m_pPlayer) == 8;
}


#####################################
int32_t __cdecl CExtCharTencent::getLoginDay(CExtCharTencent *const this)
{
  CExtOperateLimit *OperateLimit; // rax
  int nLoginCount; // [rsp+1Ch] [rbp-4h]

  if ( !this->m_pPlayer )
    return 0;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  nLoginCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1011);
  if ( nLoginCount > 7 )
    return 7;
  return nLoginCount;
}


#####################################
void __cdecl CExtCharTencent::resetQZoneDailyReward(CExtCharTencent *const this)
{
  bool v1; // bl
  CfgData *v2; // rax
  const CfgTencentTable *TencentTable; // rax
  const std::pair<const int,CfgQQGift> *v4; // rax
  const std::pair<const int,CfgQQGift> *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgQQGift> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::string __lhs; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgQQGift> > __x; // [rsp+30h] [rbp-30h] BYREF
  int32_t nRecord; // [rsp+44h] [rbp-1Ch]
  const CfgQQGiftMap *cfgMap; // [rsp+48h] [rbp-18h]

  Player::GetPlatform((const Player *const)&__lhs);
  v1 = std::operator!=<char>(&__lhs, "qq");
  std::string::~string(&__lhs);
  if ( !v1 )
  {
    nRecord = Player::getRecord(this->m_pPlayer, 37006);
    v2 = Answer::Singleton<CfgData>::instance();
    TencentTable = CfgData::GetTencentTable(v2);
    cfgMap = CfgTencentTable::GetQQZoneGiftMap(TencentTable);
    for ( iter._M_node = std::map<int,CfgQQGift>::begin(cfgMap)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,CfgQQGift>::end(cfgMap)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator!=(&iter, &__x) )
        break;
      if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator->(&iter)->second.nType == 3 )
      {
        v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator->(&iter);
        nRecord |= 1 << v4->first;
        v5 = std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator->(&iter);
        nRecord ^= 1 << v5->first;
      }
    }
    Player::updateRecord(this->m_pPlayer, 37006, nRecord);
  }
}


#####################################
void __cdecl CExtCharTencent::resetQQGameDailyReward(CExtCharTencent *const this)
{
  bool v1; // bl
  CfgData *v2; // rax
  const CfgTencentTable *TencentTable; // rax
  const std::pair<const int,CfgQQGift> *v4; // rax
  const std::pair<const int,CfgQQGift> *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgQQGift> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::string __lhs; // [rsp+20h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgQQGift> > __x; // [rsp+30h] [rbp-30h] BYREF
  int32_t nRecord; // [rsp+44h] [rbp-1Ch]
  const CfgQQGiftMap *cfgMap; // [rsp+48h] [rbp-18h]

  Player::GetPlatform((const Player *const)&__lhs);
  v1 = std::operator!=<char>(&__lhs, "qq");
  std::string::~string(&__lhs);
  if ( !v1 )
  {
    nRecord = Player::getRecord(this->m_pPlayer, 37009);
    v2 = Answer::Singleton<CfgData>::instance();
    TencentTable = CfgData::GetTencentTable(v2);
    cfgMap = CfgTencentTable::GetQQGameGiftMap(TencentTable);
    for ( iter._M_node = std::map<int,CfgQQGift>::begin(cfgMap)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator++(&iter) )
    {
      __x._M_node = std::map<int,CfgQQGift>::end(cfgMap)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator!=(&iter, &__x) )
        break;
      if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator->(&iter)->second.nType == 3 )
      {
        v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator->(&iter);
        nRecord |= 1 << v4->first;
        v5 = std::_Rb_tree_const_iterator<std::pair<int const,CfgQQGift>>::operator->(&iter);
        nRecord ^= 1 << v5->first;
      }
    }
    Player::updateRecord(this->m_pPlayer, 37009, nRecord);
  }
}


#####################################
bool __cdecl CExtCharTencent::checkQQGiftCondition(CExtCharTencent *const this, int8_t nType, int32_t nCondition)
{
  CExtOperateLimit *OperateLimit; // rax

  if ( nType == 2 )
    return (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) >= nCondition;
  if ( nType > 2 )
  {
    if ( nType == 3 )
      return 1;
    if ( nType == 4 )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      return CExtOperateLimit::GetLimitCount(OperateLimit, 37007) > 7;
    }
  }
  else if ( nType == 1 )
  {
    return 1;
  }
  return 0;
}


