// Decompiled methods for class: CDropItem
// Source: gameserver.cc
// Total methods: 7

#####################################
void __cdecl CDropItem::~CDropItem(CDropItem *const this)
{
  CDropItem::~CDropItem(this);
  operator delete(this);
}


#####################################
void __cdecl CDropItem::init(
        CDropItem *const this,
        Map *pMap,
        const Position *const pos,
        int8_t connid,
        const DropItem *const item,
        CharId_t owner,
        std::string *p_name,
        int32_t Mid,
        int32_t teamId,
        int64_t showTick,
        int64_t freeTick,
        int64_t endTick,
        int8_t autoPick,
        int8_t droperType)
{
  this->m_pMap = pMap;
  this->m_currentTile = *pos;
  this->m_currentPos = Map::tileToPixel(pos->x, pos->y);
  this->m_connid = connid;
  this->m_item = *item;
  this->m_owner = owner;
  this->m_teamId = teamId;
  this->m_showTick = showTick;
  this->m_freeTick = freeTick;
  this->m_endTick = endTick;
  this->m_autoPick = autoPick;
  this->m_droperType = droperType;
  std::string::operator=(&this->m_name, p_name);
  this->m_mid = Mid;
}


#####################################
void __cdecl CDropItem::reset(CDropItem *const this)
{
  StaticObj::reset(this);
  bzero(&this->m_item, 0x28u);
  this->m_connid = 0;
  this->m_owner = 0;
  this->m_teamId = 0;
  this->m_showTick = 0;
  this->m_freeTick = 0;
  this->m_endTick = 0;
  this->m_autoPick = 0;
  this->m_droperType = 0;
  std::string::operator=(&this->m_name, &unk_8D636F);
  this->m_mid = 0;
  this->m_bPicked = 0;
}


#####################################
bool __cdecl CDropItem::appendInfo(CDropItem *const this, Answer::NetPacket *packet)
{
  int8_t Type; // dl
  int64_t v4; // rdx
  int32_t ItemId; // edx
  int8_t ItemClass; // dl
  int32_t ItemCount; // edx
  int64_t v8; // rdx
  int32_t TeamId; // edx
  int8_t CostType; // dl
  int32_t CostValue; // edx
  int16_t PosX; // dx
  int16_t PosY; // dx
  int32_t v14; // eax
  int64_t curTick; // [rsp+18h] [rbp-8h]

  if ( !packet || !this->m_pMap )
    return 0;
  curTick = Map::getTick(this->m_pMap);
  Type = Entity::getType(this);
  Answer::NetPacket::writeInt8(packet, Type);
  v4 = (*((__int64 (__fastcall **)(CDropItem *const))this->_vptr_Entity + 2))(this);
  Answer::NetPacket::writeInt64(packet, v4);
  ItemId = CDropItem::getItemId(this);
  Answer::NetPacket::writeInt32(packet, ItemId);
  ItemClass = CDropItem::getItemClass(this);
  Answer::NetPacket::writeInt8(packet, ItemClass);
  ItemCount = CDropItem::getItemCount(this);
  Answer::NetPacket::writeInt32(packet, ItemCount);
  v8 = (*((__int64 (__fastcall **)(CDropItem *const))this->_vptr_Entity + 4))(this);
  Answer::NetPacket::writeInt64(packet, v8);
  TeamId = CDropItem::getTeamId(this);
  Answer::NetPacket::writeInt32(packet, TeamId);
  CostType = CDropItem::getCostType(this);
  Answer::NetPacket::writeInt8(packet, CostType);
  CostValue = CDropItem::getCostValue(this);
  Answer::NetPacket::writeInt32(packet, CostValue);
  PosX = StaticObj::GetPosX(this);
  Answer::NetPacket::writeInt16(packet, PosX);
  PosY = StaticObj::GetPosY(this);
  Answer::NetPacket::writeInt16(packet, PosY);
  if ( this->m_freeTick < curTick )
    v14 = 0;
  else
    v14 = this->m_freeTick - curTick;
  Answer::NetPacket::writeInt32(packet, v14);
  Answer::NetPacket::writeInt8(packet, this->m_autoPick);
  Answer::NetPacket::writeInt8(packet, this->m_droperType);
  return 1;
}


#####################################
bool __cdecl CDropItem::checkOwner(CDropItem *const this, CharId_t nCharId, int32_t nTeamId)
{
  if ( !this->m_pMap )
    return 0;
  if ( Map::getTick(this->m_pMap) >= this->m_freeTick )
    return 1;
  if ( !this->m_owner )
    return 1;
  if ( this->m_owner == nCharId )
    return 1;
  return this->m_teamId > 0 && this->m_teamId == nTeamId;
}


#####################################
int32_t __cdecl CDropItem::pick(CDropItem *const this, Player *const player)
{
  int32_t v2; // ebx
  int32_t TeamId; // r12d
  CharId_t Cid; // rsi
  int costType; // eax
  CExtCurrency *Currency; // rax
  CXinMo *CXinMo; // rax
  CExtCharBag *Bag; // rax
  int32_t mapid; // r13d
  CharId_t nCreaterId; // r12
  int32_t v13; // r15d
  int8_t v14; // r14
  CEquipManager *v15; // rax
  CEquipManager *v16; // rax
  EquipId_t srcId; // r12
  CEquipManager *v18; // rax
  CharId_t owner; // r12
  int32_t v21; // r15d
  CharId_t v22; // r12
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v25; // rax
  int8_t v26; // r12
  CEquipManager *v27; // rax
  CEquipManager *v28; // rax
  int8_t v29; // r12
  CEquipManager *v30; // rax
  CEquipManager *v31; // rax
  CXinMo *v33; // rax
  bool v34; // r12
  int v35; // r12d
  CExtCharBag *v36; // rax
  int8_t v37; // bl
  GameService *v38; // rax
  CharId_t v39; // rax
  uint32_t WOffset; // eax
  int8_t v41; // bl
  GameService *v42; // rax
  Dungeon *v43; // rax
  int v44; // eax
  int64_t v45; // r12
  int64_t costValue; // rbx
  CExtCurrency *v47; // rax
  int64_t v48; // rcx
  int64_t v49; // rcx
  int32_t mid; // [rsp+48h] [rbp-178h]
  int32_t nBaseId; // [rsp+4Ch] [rbp-174h]
  int32_t Luckly; // [rsp+50h] [rbp-170h]
  int32_t Time; // [rsp+54h] [rbp-16Ch]
  int32_t v55; // [rsp+58h] [rbp-168h]
  int32_t itemId; // [rsp+5Ch] [rbp-164h]
  MemEquip equip; // [rsp+70h] [rbp-150h] BYREF
  MemEquip pEquip; // [rsp+B0h] [rbp-110h] BYREF
  MemChrBag addItem; // [rsp+F0h] [rbp-D0h] BYREF
  MemChrBagVector Items; // [rsp+110h] [rbp-B0h] BYREF
  std::string p_name; // [rsp+130h] [rbp-90h] BYREF
  std::string v63; // [rsp+140h] [rbp-80h] BYREF
  std::vector<MemChrBag> p_Items; // [rsp+150h] [rbp-70h] BYREF
  std::string val; // [rsp+170h] [rbp-50h] BYREF
  int32_t Type; // [rsp+17Ch] [rbp-44h]
  Answer::NetPacket *packet; // [rsp+180h] [rbp-40h]
  Dungeon *pDungeon; // [rsp+188h] [rbp-38h]

  if ( !this->m_pMap || StaticObj::getMap(player) != this->m_pMap )
    return 10002;
  if ( this->m_bPicked )
    return 10002;
  TeamId = Player::GetTeamId(player);
  Cid = Player::getCid(player);
  if ( !CDropItem::checkOwner(this, Cid, TeamId) )
    return 10002;
  costType = this->m_item.costType;
  switch ( costType )
  {
    case 2:
      if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_CASH) < this->m_item.costValue )
        return 10002;
      break;
    case 3:
      if ( Player::GetCurrency(player, CURRENCY_TYPE::CURRENCY_GOLD) < this->m_item.costValue )
        return 10002;
      break;
    case 1:
      Currency = Player::GetCurrency(player);
      if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < this->m_item.costValue )
        return 10002;
      break;
  }
  memset(&addItem, 0, sizeof(addItem));
  addItem.itemId = this->m_item.itemId;
  addItem.itemClass = this->m_item.itemClass;
  addItem.itemCount = this->m_item.itemCount;
  addItem.bind = this->m_item.bindType;
  addItem.endTime = this->m_item.endTime;
  addItem.srcId = this->m_item.srcId;
  if ( this->m_item.itemCount > 0 )
  {
    if ( this->m_item.itemClass == 2 )
    {
      if ( Map::IsXinMoMap(this->m_pMap) && CItemHelper::CanEnterXinMoBag(addItem.itemId, addItem.itemClass) )
      {
        CXinMo = Player::GetCXinMo(player);
        if ( CXinMo::GetFreeSlotCount(CXinMo) <= 0 )
          return 10016;
      }
      else
      {
        Bag = Player::GetBag(player);
        if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
          return 10016;
      }
      if ( this->m_item.srcId > 0 )
      {
        srcId = this->m_item.srcId;
        v18 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::GetMemEquip(&pEquip, v18, srcId);
        if ( pEquip.id == this->m_item.srcId )
        {
          owner = pEquip.owner;
          if ( owner != Player::getCid(player) )
          {
            pEquip.owner = Player::getCid(player);
            if ( Map::IsCrossMap(this->m_pMap) )
            {
              Luckly = pEquip.Lucky;
              Time = pEquip.time;
              v55 = pEquip.Mid;
              v21 = pEquip.MapId;
              std::string::string(&v63, &pEquip.name);
              v22 = Player::getCid(player);
              Sid = Player::getSid(player);
              itemId = this->m_item.itemId;
              ConnId = Player::getConnId(player);
              v25 = Answer::Singleton<CEquipManager>::instance();
              CEquipManager::CreateMemEquip(&equip, v25, ConnId, 1, itemId, Sid, v22, &v63, v21, v55, Time, Luckly, 0);
              std::string::~string(&v63);
              if ( equip.id > 0 )
              {
                equip.star = pEquip.star;
                addItem.srcId = equip.id;
                v26 = Player::getConnId(player);
                v27 = Answer::Singleton<CEquipManager>::instance();
                CEquipManager::UpdateMemEquip(v27, v26, &equip, 1);
                v28 = Answer::Singleton<CEquipManager>::instance();
                CEquipManager::SendPlayerEquipInfo(v28, player, &equip);
              }
              MemEquip::~MemEquip(&equip);
            }
            else
            {
              v29 = Player::getConnId(player);
              v30 = Answer::Singleton<CEquipManager>::instance();
              CEquipManager::UpdateMemEquip(v30, v29, &pEquip, 1);
              v31 = Answer::Singleton<CEquipManager>::instance();
              CEquipManager::SendPlayerEquipInfo(v31, player, &pEquip);
            }
          }
        }
        MemEquip::~MemEquip(&pEquip);
      }
      else
      {
        mid = this->m_mid;
        mapid = StaticObj::getMapId(player);
        std::string::string(&p_name, &this->m_name);
        nCreaterId = Player::getCid(player);
        v13 = Player::getSid(player);
        nBaseId = this->m_item.itemId;
        v14 = Player::getConnId(player);
        v15 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::CreateMemEquip(&pEquip, v15, v14, 1, nBaseId, v13, nCreaterId, &p_name, mapid, mid, 0, 0, 0);
        std::string::~string(&p_name);
        if ( pEquip.id > 0 )
        {
          v16 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::SendPlayerEquipInfo(v16, player, &pEquip);
          addItem.srcId = pEquip.id;
        }
        MemEquip::~MemEquip(&pEquip);
      }
    }
    if ( Map::IsXinMoMap(this->m_pMap) && CItemHelper::CanEnterXinMoBag(addItem.itemId, addItem.itemClass) )
    {
      std::vector<MemChrBag>::vector(&Items);
      std::vector<MemChrBag>::push_back(&Items, &addItem);
      std::vector<MemChrBag>::vector(&p_Items, &Items);
      v33 = Player::GetCXinMo(player);
      v34 = !CXinMo::AddItem(v33, &p_Items);
      std::vector<MemChrBag>::~vector(&p_Items);
      if ( v34 )
      {
        v2 = 10016;
        v35 = 0;
      }
      else
      {
        v35 = 1;
      }
      std::vector<MemChrBag>::~vector(&Items);
      if ( !v35 )
        return v2;
    }
    else
    {
      v36 = Player::GetBag(player);
      if ( !CExtCharBag::AddItem(v36, &addItem, ITEM_CHANGE_REASON::ICR_PICK) )
        return 10016;
    }
    if ( addItem.itemClass == 2 )
    {
      Type = CItemHelper::GetItemType(addItem.itemId, 2);
      if ( Type == 8 )
      {
        v37 = Player::getConnId(player);
        v38 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v38, v37, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
        if ( !packet )
          return 10002;
        Answer::NetPacket::writeInt32(packet, 413);
        Player::getName((const Player *const)&val);
        Answer::NetPacket::writeUTF8(packet, &val);
        std::string::~string(&val);
        v39 = Player::getCid(player);
        Answer::NetPacket::writeInt64(packet, v39);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v41 = Player::getConnId(player);
        v42 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v42, v41, packet);
      }
    }
    if ( (*((unsigned __int8 (__fastcall **)(Map *))this->m_pMap->_vptr_Map + 18))(this->m_pMap) )
    {
      v43 = this->m_pMap
          ? (Dungeon *)__dynamic_cast(
                         this->m_pMap,
                         (const struct __class_type_info *)&`typeinfo for'Map,
                         (const struct __class_type_info *)&`typeinfo for'Dungeon,
                         0)
          : 0LL;
      pDungeon = v43;
      if ( v43 )
        Dungeon::OnPickItem(pDungeon, player, &addItem);
    }
  }
  v44 = this->m_item.costType;
  switch ( v44 )
  {
    case 2:
      v48 = (*((__int64 (__fastcall **)(CDropItem *const))this->_vptr_Entity + 2))(this);
      Player::DecCurrency(
        player,
        CURRENCY_TYPE::CURRENCY_CASH,
        this->m_item.costValue,
        CURRENCY_CHANGE_REASON::GCR_GET_DROP_ITEM,
        v48);
      break;
    case 3:
      v49 = (*((__int64 (__fastcall **)(CDropItem *const))this->_vptr_Entity + 2))(this);
      Player::DecCurrency(
        player,
        CURRENCY_TYPE::CURRENCY_GOLD,
        this->m_item.costValue,
        CURRENCY_CHANGE_REASON::GCR_GET_DROP_ITEM,
        v49);
      break;
    case 1:
      v45 = (*((__int64 (__fastcall **)(CDropItem *const))this->_vptr_Entity + 2))(this);
      costValue = this->m_item.costValue;
      v47 = Player::GetCurrency(player);
      CExtCurrency::DecMoneyAndNoBind(v47, costValue, CURRENCY_CHANGE_REASON::MCR_GET_DROP_ITEM, v45);
      break;
  }
  this->m_bPicked = 1;
  return 0;
}


#####################################
bool __cdecl CDropItem::checkEnd(CDropItem *const this)
{
  return !this->m_pMap || Map::getTick(this->m_pMap) > this->m_endTick || this->m_bPicked;
}


