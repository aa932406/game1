// Decompiled methods for class: CExtCharAuction
// Source: gameserver.cc
// Total methods: 12

#####################################
void __cdecl CExtCharAuction::~CExtCharAuction(CExtCharAuction *const this)
{
  CExtCharAuction::~CExtCharAuction(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharAuction::GetInterestsProtocol(CExtCharAuction *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v3; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v4; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v5; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v6; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 820;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 821;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 20072;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 20073;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 20075;
  std::list<unsigned short>::push_back(procList, &v6);
}


#####################################
int32_t __cdecl CExtCharAuction::DispatchNetDatas(
        CExtCharAuction *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( nProcId == 20072 )
    return CExtCharAuction::onAuctionSell(this, inPacket);
  if ( nProcId > 0x4E68u )
  {
    if ( nProcId == 20073 )
      return CExtCharAuction::onAuctionBuy(this, inPacket);
    if ( nProcId == 20075 )
      return CExtCharAuction::onAddEquip(this, inPacket);
  }
  else
  {
    if ( nProcId == 820 )
      return CExtCharAuction::onOpenStall(this, inPacket);
    if ( nProcId == 821 )
      return CExtCharAuction::onCloseStall(this, inPacket);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharAuction::onAuctionSell(CExtCharAuction *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CVip *PlayerVip; // rax
  CChrDepot *CharDepot; // rax
  EquipId_t srcId; // r12
  CEquipManager *v6; // rax
  int v7; // r12d
  int32_t itemId; // r12d
  CfgData *v9; // rax
  const CfgEquipTable *EquipTable; // rax
  CfgData *v11; // rax
  int32_t ServerDiffDay; // eax
  CExtCharBag *Bag; // rax
  CExtCurrency *Currency; // rax
  MemChrBag v16; // [rsp+0h] [rbp-E0h] BYREF
  Answer::NetPacket *inPacketa; // [rsp+20h] [rbp-C0h]
  CExtCharAuction *thisa; // [rsp+28h] [rbp-B8h]
  MemEquip equip; // [rsp+30h] [rbp-B0h] BYREF
  MemChrBag emptySlot; // [rsp+70h] [rbp-70h] BYREF
  MemChrBag item; // [rsp+90h] [rbp-50h] BYREF
  int8_t nType; // [rsp+B7h] [rbp-29h]
  int32_t nSlot; // [rsp+B8h] [rbp-28h]
  int32_t nCount; // [rsp+BCh] [rbp-24h]
  int32_t nPrice; // [rsp+C0h] [rbp-20h]
  int8_t nCurrType; // [rsp+C7h] [rbp-19h]
  const CfgEquip *pEquip; // [rsp+C8h] [rbp-18h]

  thisa = this;
  inPacketa = inPacket;
  if ( !this->m_pPlayer || !inPacketa )
    return 10002;
  PlayerVip = Player::GetPlayerVip(thisa->m_pPlayer);
  if ( !CVip::CanAuction(PlayerVip) )
    return 2;
  if ( Player::GetFuLiLevel(thisa->m_pPlayer) == 1 )
    return 2;
  CharDepot = Player::GetCharDepot(thisa->m_pPlayer);
  if ( !CChrDepot::IsEnterSecondPasswordOperate(CharDepot) )
  {
    Player::TiShiInfo(thisa->m_pPlayer, 29, 0);
    return 2;
  }
  nType = Answer::NetPacket::readInt8(inPacketa);
  nSlot = Answer::NetPacket::readInt32(inPacketa);
  nCount = Answer::NetPacket::readInt32(inPacketa);
  nPrice = Answer::NetPacket::readInt32(inPacketa);
  nCurrType = Answer::NetPacket::readInt8(inPacketa);
  if ( nCount <= 0 || nPrice <= 0 )
    return 10002;
  if ( nPrice <= 1 )
    return 10002;
  memset(&item, 0, sizeof(item));
  if ( nType == 1 )
  {
    if ( nCurrType == 1 )
      return 10002;
    Currency = Player::GetCurrency(thisa->m_pPlayer);
    if ( !CExtCurrency::DecCurrency(
            Currency,
            CURRENCY_TYPE::CURRENCY_MONEY,
            nCount,
            CURRENCY_CHANGE_REASON::MCR_AUCTION_SELL,
            0) )
      return 10002;
    item.itemClass = 4;
    item.itemId = 1;
    item.itemCount = nCount;
    goto LABEL_53;
  }
  if ( nType == 2 )
  {
    if ( Player::GetFuLiLevel(thisa->m_pPlayer) == 1 )
      return 2;
    if ( nCurrType == 2 )
      return 10002;
    if ( !Player::DecCurrency(
            thisa->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            nCount,
            CURRENCY_CHANGE_REASON::GCR_AUCTION_SELL,
            0) )
      return 10002;
    item.itemClass = 4;
    item.itemId = 2;
    item.itemCount = nCount;
    goto LABEL_53;
  }
  if ( nType )
    return 10002;
  Player::getBagSlotData(&v16, thisa->m_pPlayer, nSlot);
  item = v16;
  if ( v16.itemClass != 2 )
    goto LABEL_32;
  srcId = item.srcId;
  v6 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::GetMemEquip(&equip, v6, srcId);
  if ( equip.base == item.itemId )
  {
    itemId = item.itemId;
    v9 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v9);
    pEquip = CfgEquipTable::GetEquip(EquipTable, itemId);
    if ( pEquip )
    {
      if ( pEquip->m_SellDay <= 0
        || (v11 = Answer::Singleton<CfgData>::instance(),
            ServerDiffDay = CfgData::getServerDiffDay(v11, SERVER_TYPE::SVT_NORMAL),
            ServerDiffDay + 1 < pEquip->m_SellDay) )
      {
        if ( nCurrType == 1 && pEquip->m_BackValue > nPrice )
        {
          v2 = 10002;
          v7 = 0;
        }
        else
        {
          v7 = 1;
        }
      }
      else
      {
        v2 = 10002;
        v7 = 0;
      }
    }
    else
    {
      v2 = 10002;
      v7 = 0;
    }
  }
  else
  {
    v2 = 10002;
    v7 = 0;
  }
  MemEquip::~MemEquip(&equip);
  if ( v7 )
  {
LABEL_32:
    if ( item.itemId <= 0 || item.itemCount <= 0 )
      return 10002;
    if ( item.bind > 0 || item.endTime > 0 )
      return 10002;
    if ( item.itemCount < nCount )
      return 10002;
    emptySlot = item;
    item.itemCount = nCount;
    emptySlot.itemCount -= nCount;
    Bag = Player::GetBag(thisa->m_pPlayer);
    CExtCharBag::SetSlotData(Bag, nSlot, &emptySlot, ITEM_CHANGE_REASON::ICR_AUCTION_SELL, 0);
LABEL_53:
    CExtCharAuction::sendSocialSell(thisa, &item, nPrice, nCurrType);
    return 0;
  }
  return v2;
}


#####################################
int32_t __cdecl CExtCharAuction::onAuctionBuy(CExtCharAuction *const this, Answer::NetPacket *inPacket)
{
  CVip *PlayerVip; // rax
  CChrDepot *CharDepot; // rax
  CVip *v5; // rax
  CExtCurrency *Currency; // rax
  int32_t nId; // [rsp+14h] [rbp-1Ch]
  int8_t nPayType; // [rsp+1Bh] [rbp-15h]
  int32_t nPrice; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  PlayerVip = Player::GetPlayerVip(this->m_pPlayer);
  if ( !CVip::CanAuction(PlayerVip) )
    return 2;
  if ( Player::GetFuLiLevel(this->m_pPlayer) == 1 )
    return 2;
  CharDepot = Player::GetCharDepot(this->m_pPlayer);
  if ( !CChrDepot::IsEnterSecondPasswordOperate(CharDepot) )
  {
    Player::TiShiInfo(this->m_pPlayer, 29, 0);
    return 2;
  }
  else
  {
    nId = Answer::NetPacket::readInt32(inPacket);
    nPayType = Answer::NetPacket::readInt8(inPacket);
    nPrice = Answer::NetPacket::readInt32(inPacket);
    if ( nPayType == 1 && (v5 = Player::GetPlayerVip(this->m_pPlayer), !CVip::CanAuction(v5)) )
    {
      return 2;
    }
    else if ( nPayType == 2
           && !Player::DecCurrency(
                 this->m_pPlayer,
                 CURRENCY_TYPE::CURRENCY_GOLD,
                 nPrice,
                 CURRENCY_CHANGE_REASON::GCR_AUCTION_BUY,
                 nId) )
    {
      return 2;
    }
    else if ( nPayType == 1
           && (Currency = Player::GetCurrency(this->m_pPlayer),
               !CExtCurrency::DecCurrency(
                  Currency,
                  CURRENCY_TYPE::CURRENCY_MONEY,
                  nPrice,
                  CURRENCY_CHANGE_REASON::MCR_AUCTION_BUY,
                  nId)) )
    {
      return 2;
    }
    else
    {
      CExtCharAuction::sendSocialBuy(this, nId);
      return 0;
    }
  }
}


#####################################
int32_t __cdecl CExtCharAuction::onOpenStall(CExtCharAuction *const this, Answer::NetPacket *inPacket)
{
  GameService *v3; // rax
  CharId_t Cid; // rdx
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  Position stallPos; // [rsp+10h] [rbp-40h]
  int64_t nNpcId; // [rsp+18h] [rbp-38h]
  Map *pMap; // [rsp+20h] [rbp-30h]
  Npc *pNpc; // [rsp+28h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) != 1 )
    return 2;
  nNpcId = Answer::NetPacket::readInt64(inPacket);
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 2;
  pNpc = Map::getNpc(pMap, nNpcId);
  if ( !pNpc )
    return 2;
  if ( Npc::GetFuncExtra(pNpc) != 1047 )
    return 2;
  if ( (*((__int64 (__fastcall **)(Npc *))pNpc->_vptr_Entity + 4))(pNpc) > 0 )
    return 2;
  this->m_nStall = (*((__int64 (__fastcall **)(Npc *))pNpc->_vptr_Entity + 2))(pNpc);
  Unit::setNeedSyncSelf(this->m_pPlayer);
  stallPos = Npc::GetStallPos(pNpc);
  if ( stallPos.x > 0 && stallPos.y > 0 )
    Unit::instantMove(this->m_pPlayer, stallPos.x, stallPos.y, InstanceMoveReason::IMR_OPEN_STALL, 0);
  Cid = Player::getCid(this->m_pPlayer);
  Npc::SetOwner(pNpc, Cid);
  Npc::leaveMap(pNpc);
  Map::broadcastIntoMap(pMap, pNpc);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v8 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v8, ConnId, GateIndex, Proc, nNpcId);
  CExtCharAuction::sendSocialStall(this, 1);
  return 0;
}


#####################################
int32_t __cdecl CExtCharAuction::onCloseStall(CExtCharAuction *const this, Answer::NetPacket *inPacket)
{
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v6; // rax

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CExtCharAuction::closeStall(this) )
    return 2;
  Unit::setNeedSyncSelf(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v6, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCharAuction::onAddEquip(CExtCharAuction *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int8_t ConnId; // bl
  CEquipManager *v4; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v6; // rax
  MemEquip equip; // [rsp+10h] [rbp-50h] BYREF
  int32_t nReason; // [rsp+4Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nReason = Answer::NetPacket::readInt32(inPacket);
  MemEquip::MemEquip(&equip);
  MemEquip::UnPackageData(&equip, inPacket);
  equip.owner = Player::getCid(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::UpdateMemEquip(v4, ConnId, &equip, nReason);
  m_pPlayer = this->m_pPlayer;
  v6 = Answer::Singleton<CEquipManager>::instance();
  CEquipManager::SendPlayerEquipInfo(v6, m_pPlayer, &equip);
  v2 = 0;
  MemEquip::~MemEquip(&equip);
  return v2;
}


#####################################
void __cdecl CExtCharAuction::sendSocialSell(
        CExtCharAuction *const this,
        const MemChrBag *const item,
        int32_t nPrice,
        int8_t nCurrType)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  int16_t GateIndex; // ax
  EquipId_t srcId; // rbx
  CEquipManager *v8; // rax
  int v9; // ebx
  EquipId_t id; // r12
  int8_t v11; // bl
  CEquipManager *v12; // rax
  uint32_t WOffset; // eax
  int8_t v14; // bl
  GameService *v15; // rax
  MemEquip equip; // [rsp+20h] [rbp-50h] BYREF
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA5u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, item->itemId);
      Answer::NetPacket::writeInt8(packet, item->itemClass);
      Answer::NetPacket::writeInt32(packet, item->itemCount);
      Answer::NetPacket::writeInt64(packet, item->srcId);
      Answer::NetPacket::writeInt32(packet, nPrice);
      Answer::NetPacket::writeInt8(packet, nCurrType);
      if ( item->itemClass != 2 )
        goto LABEL_8;
      srcId = item->srcId;
      v8 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::GetMemEquip(&equip, v8, srcId);
      if ( equip.base == item->itemId )
      {
        MemEquip::PackageData(&equip, packet);
        id = equip.id;
        v11 = Player::getConnId(this->m_pPlayer);
        v12 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::DeleteMemEquip(v12, v11, id, 181);
        v9 = 1;
      }
      else
      {
        Answer::NetPacket::destroy(packet);
        v9 = 0;
      }
      MemEquip::~MemEquip(&equip);
      if ( v9 )
      {
LABEL_8:
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v14 = Player::getConnId(this->m_pPlayer);
        v15 = Answer::Singleton<GameService>::instance();
        GameService::sendPacket(v15, v14, packet);
      }
    }
  }
}


#####################################
void __cdecl CExtCharAuction::sendSocialBuy(CExtCharAuction *const this, int32_t nId)
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
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA6u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt32(packet, nId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
void __cdecl CExtCharAuction::sendSocialStall(CExtCharAuction *const this, bool bStall)
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
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x4EA7u);
    if ( packet )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, GateIndex);
      Answer::NetPacket::writeInt8(packet, bStall);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacket(v7, v6, packet);
    }
  }
}


#####################################
bool __cdecl CExtCharAuction::closeStall(CExtCharAuction *const this)
{
  Map *pMap; // [rsp+10h] [rbp-10h]
  Npc *pNpc; // [rsp+18h] [rbp-8h]

  if ( !this->m_pPlayer )
    return 0;
  if ( !CExtCharAuction::IsInStall(this) )
    return 0;
  pMap = StaticObj::getMap(this->m_pPlayer);
  if ( !pMap )
    return 0;
  pNpc = Map::getNpc(pMap, this->m_nStall);
  if ( !pNpc )
    return 0;
  this->m_nStall = 0;
  Npc::SetOwner(pNpc, 0);
  Npc::leaveMap(pNpc);
  Map::broadcastIntoMap(pMap, pNpc);
  CExtCharAuction::sendSocialStall(this, 0);
  return 1;
}


