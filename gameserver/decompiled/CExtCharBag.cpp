// Decompiled methods for class: CExtCharBag
// Source: gameserver.cc
// Total methods: 90

#####################################
void __cdecl CExtCharBag::~CExtCharBag(CExtCharBag *const this)
{
  CExtCharBag::~CExtCharBag(this);
  operator delete(this);
}


#####################################
void __cdecl CExtCharBag::OnLoadFromDB(CExtCharBag *const this, const PlayerDBData *const dbData)
{
  memcpy(this->m_bagData, dbData->bagData.bagData, sizeof(this->m_bagData));
  std::map<int,int>::operator=(&this->m_ItemLimit, &dbData->bagData.m_ItemLimit);
}


#####################################
void __cdecl CExtCharBag::OnSaveToDB(CExtCharBag *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->bagData.bagData, this->m_bagData, sizeof(dbData->bagData.bagData));
  std::map<int,int>::operator=(&dbData->bagData.m_ItemLimit, &this->m_ItemLimit);
}


#####################################
void __cdecl CExtCharBag::OnUpdate(CExtCharBag *const this, int64_t curTick)
{
  CExtCharBag::checkCreate(this);
  CExtCharBag::checkDirty(this);
}


#####################################
void __cdecl CExtCharBag::GetInterestsProtocol(CExtCharBag *const this, ProcIdList *const procList)
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

  __x = 91;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 92;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 94;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 95;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 88;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 89;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 90;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 481;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 96;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 20076;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 657;
  std::list<unsigned short>::push_back(procList, &v12);
}


#####################################
int32_t __cdecl CExtCharBag::DispatchNetDatas(CExtCharBag *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( nProcId == 94 )
    return CExtCharBag::onSort(this, inPacket);
  if ( nProcId > 0x5Eu )
  {
    if ( nProcId == 481 )
      return CExtCharBag::onUseMutiItem(this, inPacket);
    if ( nProcId > 0x1E1u )
    {
      if ( nProcId == 657 )
        return CExtCharBag::onSelectItem(this, inPacket);
      if ( nProcId == 20076 )
        return CExtCharBag::onAddItem(this, inPacket);
    }
    else if ( nProcId == 96 )
    {
      return CExtCharBag::onDiscardItem(this, inPacket);
    }
  }
  else
  {
    if ( nProcId == 90 )
      return CExtCharBag::onPatchUseItem(this, inPacket);
    if ( nProcId > 0x5Au )
    {
      if ( nProcId == 91 )
        return CExtCharBag::onMoveItem(this, inPacket);
      if ( nProcId == 92 )
        return CExtCharBag::onSplitItem(this, inPacket);
    }
    else if ( nProcId == 89 )
    {
      return CExtCharBag::onUseItem(this, inPacket);
    }
  }
  return 0;
}


#####################################
void __cdecl CExtCharBag::reset(CExtCharBag *const this)
{
  bzero(this->m_bagData, 0x700u);
  bzero(this->m_sellItemInfo, 0x1E0u);
  bzero(&this->m_nullobj, 0x20u);
  bzero(this->m_lastItemTick, 0x40u);
  bzero(this->m_bagBackUp, 0x700u);
  std::list<LogItemChange>::clear(&this->m_lstItemChangeLog);
  std::list<CExtCharBag::BagDirty>::clear(&this->m_lstDirty);
  std::list<CExtCharBag::WaitCreate>::clear(&this->m_lstWaitCreate);
  std::map<int,int>::clear(&this->m_ItemLimit);
}


#####################################
void __cdecl CExtCharBag::cleanSellItem(CExtCharBag *const this)
{
  EquipId_t srcId; // r12
  int8_t ConnId; // bl
  CEquipManager *v3; // rax
  int32_t i; // [rsp+14h] [rbp-1Ch]
  MemChrBag *curSlot; // [rsp+18h] [rbp-18h]

  for ( i = 0; i <= 14; ++i )
  {
    curSlot = &this->m_sellItemInfo[i];
    if ( curSlot->srcId > 0 && curSlot->itemClass == 2 )
    {
      srcId = curSlot->srcId;
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::DeleteMemEquip(v3, ConnId, srcId, 131);
    }
  }
  bzero(this->m_sellItemInfo, 0x1E0u);
}


#####################################
int32_t __cdecl CExtCharBag::onUseItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  CfgData *v4; // rax
  Player *m_pPlayer; // r13
  ItemEffectManager *v7; // rax
  int32_t v8; // r12d
  ChrTask *Task; // rax
  int32_t cd_group; // ebx
  int32_t id; // r13d
  CharId_t Cid; // r12
  int64_t v13; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v16; // rax
  GameService *v17; // rax
  CharId_t v18; // rax
  uint32_t WOffset; // eax
  GameService *v20; // rax
  MemChrBag slotData; // [rsp+10h] [rbp-90h] BYREF
  int32_t nCount; // [rsp+3Ch] [rbp-64h] BYREF
  std::string p_name; // [rsp+40h] [rbp-60h] BYREF
  std::string val; // [rsp+50h] [rbp-50h] BYREF
  int32_t slot; // [rsp+58h] [rbp-48h]
  int32_t type; // [rsp+5Ch] [rbp-44h]
  int32_t nItemId; // [rsp+60h] [rbp-40h]
  int32_t ItemId; // [rsp+64h] [rbp-3Ch]
  CfgItem *cfgItem; // [rsp+68h] [rbp-38h]
  int32_t err; // [rsp+74h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+78h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  slot = Answer::NetPacket::readInt32(inPacket);
  type = Answer::NetPacket::readInt32(inPacket);
  nItemId = Answer::NetPacket::readInt32(inPacket);
  nCount = 1;
  slotData = *CExtCharBag::GetSlotData(this, slot);
  if ( slotData.itemCount <= 0 || slotData.itemClass != 1 || slotData.itemId != nItemId )
    return 10002;
  if ( slotData.endTime > 0 && Unit::getNow(this->m_pPlayer) > slotData.endTime )
    return 10002;
  ItemId = slotData.itemId;
  v4 = Answer::Singleton<CfgData>::instance();
  cfgItem = CfgData::getItem(v4, slotData.itemId);
  if ( !cfgItem )
    return 10002;
  if ( !CExtCharBag::canUseItem(this, cfgItem) )
    return 10002;
  if ( Player::IsInPvP(this->m_pPlayer) && cfgItem->type == 106 )
  {
    Player::TiShiInfo(this->m_pPlayer, 22, 0);
    return 10002;
  }
  err = 10002;
  if ( type == 1 )
  {
    m_pPlayer = this->m_pPlayer;
    v7 = Answer::Singleton<ItemEffectManager>::instance();
    err = ItemEffectManager::effect(v7, slotData.itemId, m_pPlayer, m_pPlayer, &nCount);
  }
  if ( !err )
  {
    v8 = nCount;
    Task = Player::GetTask(this->m_pPlayer);
    ChrTask::updateTaskUseItem(Task, slotData.itemId, v8);
    --slotData.itemCount;
    CExtCharBag::SetSlotData(this, slot, &slotData, ITEM_CHANGE_REASON::ICR_BAG_USE, nCount);
    cd_group = cfgItem->cd_group;
    this->m_lastItemTick[cd_group] = Unit::getTick(this->m_pPlayer);
    if ( cfgItem->useBroadcast > 0 )
    {
      id = cfgItem->id;
      Cid = Player::getCid(this->m_pPlayer);
      Player::getName((const Player *const)&p_name);
      CExtCharBag::sendUseBroadcast(this, cfgItem->useBroadcast, &p_name, Cid, id);
      std::string::~string(&p_name);
    }
    v13 = cfgItem->id;
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v16 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v16, ConnId, GateIndex, 0x59u, v13);
    if ( cfgItem->GongGaoId > 0 )
    {
      v17 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v17, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( !packet )
        return err;
      Answer::NetPacket::writeInt32(packet, cfgItem->GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      v18 = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, v18);
      Answer::NetPacket::writeInt32(packet, ItemId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v20 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v20, 0, packet);
    }
  }
  return err;
}


#####################################
int32_t __cdecl CExtCharBag::onPatchUseItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  CfgData *v4; // rax
  Player *m_pPlayer; // r13
  int32_t itemId; // ebx
  ItemEffectManager *v8; // rax
  int32_t v9; // r12d
  int32_t v10; // ebx
  ChrTask *Task; // rax
  CExtCharSkill *CharSkill; // rax
  Player *v13; // r13
  ItemEffectManager *v14; // rax
  int32_t v15; // r12d
  ChrTask *v16; // rax
  int32_t cd_group; // ebx
  int64_t id; // r13
  int16_t GateIndex; // r12
  GameService *v20; // rax
  MemChrBag slotData; // [rsp+10h] [rbp-60h] BYREF
  int32_t tmpCount; // [rsp+30h] [rbp-40h] BYREF
  int32_t count; // [rsp+34h] [rbp-3Ch] BYREF
  int32_t slot; // [rsp+38h] [rbp-38h]
  int32_t nItemId; // [rsp+3Ch] [rbp-34h]
  CfgItem *cfgItem; // [rsp+40h] [rbp-30h]
  int32_t err; // [rsp+48h] [rbp-28h]
  int32_t i; // [rsp+4Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  slot = Answer::NetPacket::readInt32(inPacket);
  count = Answer::NetPacket::readInt32(inPacket);
  nItemId = Answer::NetPacket::readInt32(inPacket);
  if ( count <= 0 )
    return 10002;
  slotData = *CExtCharBag::GetSlotData(this, slot);
  if ( slotData.itemCount <= 0 || slotData.itemClass != 1 || slotData.itemId != nItemId )
    return 10002;
  if ( slotData.itemCount < count )
    count = slotData.itemCount;
  if ( slotData.endTime > 0 && Unit::getNow(this->m_pPlayer) > slotData.endTime )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  cfgItem = CfgData::getItem(v4, slotData.itemId);
  if ( !cfgItem )
    return 10002;
  if ( !CExtCharBag::canUseItem(this, cfgItem) )
    return 10002;
  err = 0;
  if ( cfgItem->type == 106 || cfgItem->type == 108 )
  {
    if ( Player::IsInPvP(this->m_pPlayer) && cfgItem->type == 106 )
    {
      Player::TiShiInfo(this->m_pPlayer, 22, 0);
      return 10002;
    }
    for ( i = 0; i < count; ++i )
    {
      tmpCount = 1;
      m_pPlayer = this->m_pPlayer;
      itemId = slotData.itemId;
      v8 = Answer::Singleton<ItemEffectManager>::instance();
      err = ItemEffectManager::effect(v8, itemId, m_pPlayer, m_pPlayer, &tmpCount);
      if ( err )
        break;
      v9 = tmpCount;
      v10 = slotData.itemId;
      Task = Player::GetTask(this->m_pPlayer);
      ChrTask::updateTaskUseItem(Task, v10, v9);
      slotData.itemCount -= tmpCount;
      CExtCharBag::SetSlotData(this, slot, &slotData, ITEM_CHANGE_REASON::ICR_BAG_USE, tmpCount);
    }
    if ( cfgItem->type == 108 )
    {
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::SendTalentInfo(CharSkill);
    }
  }
  else
  {
    v13 = this->m_pPlayer;
    v14 = Answer::Singleton<ItemEffectManager>::instance();
    err = ItemEffectManager::effect(v14, slotData.itemId, v13, v13, &count);
    if ( !err )
    {
      v15 = count;
      v16 = Player::GetTask(this->m_pPlayer);
      ChrTask::updateTaskUseItem(v16, slotData.itemId, v15);
      slotData.itemCount -= count;
      CExtCharBag::SetSlotData(this, slot, &slotData, ITEM_CHANGE_REASON::ICR_BAG_USE, count);
    }
  }
  cd_group = cfgItem->cd_group;
  this->m_lastItemTick[cd_group] = Unit::getTick(this->m_pPlayer);
  id = cfgItem->id;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  LOBYTE(cd_group) = Player::getConnId(this->m_pPlayer);
  v20 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v20, cd_group, GateIndex, 0x5Au, id);
  return err;
}


#####################################
int32_t __cdecl CExtCharBag::onSelectItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  const char *v4; // rax
  CfgData *v5; // rax
  int64_t v7; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v11; // rax
  MemChrBag GetItemStu; // [rsp+10h] [rbp-D0h] BYREF
  MemChrBag slotData; // [rsp+30h] [rbp-B0h]
  MemChrBagVector stu; // [rsp+50h] [rbp-90h] BYREF
  Int32Vector vSlot; // [rsp+70h] [rbp-70h] BYREF
  ItemData RemoveItemData; // [rsp+90h] [rbp-50h] BYREF
  int32_t nSlot; // [rsp+A0h] [rbp-40h] BYREF
  int32_t nId; // [rsp+A4h] [rbp-3Ch]
  CfgItem *pItem; // [rsp+A8h] [rbp-38h]
  int32_t Effect; // [rsp+B4h] [rbp-2Ch]
  SelectItemCfg *pItems; // [rsp+B8h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nSlot = Answer::NetPacket::readInt32(inPacket);
  nId = Answer::NetPacket::readInt32(inPacket);
  slotData = *CExtCharBag::GetSlotData(this, nSlot);
  if ( slotData.itemCount <= 0 )
    return 10002;
  v3 = Answer::Singleton<CfgData>::instance();
  pItem = CfgData::getItem(v3, slotData.itemId);
  if ( !pItem )
    return 10002;
  if ( pItem->type != 213 )
    return 10002;
  v4 = (const char *)std::string::c_str(&pItem->effect);
  Effect = atoi(v4);
  v5 = Answer::Singleton<CfgData>::instance();
  pItems = CfgData::GetSelectItemCfg(v5, Effect);
  if ( !pItems )
    return 10002;
  if ( nId < 0 || (int)std::vector<MemChrBag>::size(&pItems->vItem) <= nId )
    return 10002;
  *(_DWORD *)&RemoveItemData.m_nClass = (unsigned __int8)slotData.itemClass;
  RemoveItemData.m_nId = slotData.itemId;
  RemoveItemData.m_nCount = 1;
  std::vector<int>::vector(&vSlot);
  std::vector<int>::push_back(&vSlot, &nSlot);
  GetItemStu = *std::vector<MemChrBag>::operator[](&pItems->vItem, nId);
  if ( CExtCharBag::GetFreeSlotCount(this) > 0 )
  {
    if ( !CExtCharBag::RemoveItem(this, &vSlot, &RemoveItemData, ITEM_CHANGE_REASON::IDCR_SELECT_ITEM) )
    {
      v2 = 10002;
    }
    else
    {
      std::vector<MemChrBag>::vector(&stu);
      std::vector<MemChrBag>::push_back(&stu, &GetItemStu);
      if ( !CExtCharBag::AddItemsAndMingGe(this, &stu, ITEM_CHANGE_REASON::IDCR_SELECT_ITEM) )
      {
        v2 = 10002;
      }
      else
      {
        v7 = nId;
        Proc = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        ConnId = Player::getConnId(this->m_pPlayer);
        v11 = Answer::Singleton<GameService>::instance();
        v2 = GameService::replySuccess(v11, ConnId, GateIndex, Proc, v7);
      }
      std::vector<MemChrBag>::~vector(&stu);
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
int32_t __cdecl CExtCharBag::onDiscardItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  GameService *v3; // rax
  CChrDepot *CharDepot; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v8; // rax
  int8_t v9; // al
  uint16_t v10; // r13
  int16_t v11; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  DropItem stu; // [rsp+40h] [rbp-D0h] BYREF
  MemChrBag slotData; // [rsp+70h] [rbp-A0h]
  Position CentosPos; // [rsp+90h] [rbp-80h] BYREF
  CDropItemGroup pDropItemGroup; // [rsp+A0h] [rbp-70h] BYREF
  DropItemVector dropItems; // [rsp+B0h] [rbp-60h] BYREF
  std::string dropper; // [rsp+D0h] [rbp-40h] BYREF
  char v21; // [rsp+E3h] [rbp-2Dh] BYREF
  int32_t nSlot; // [rsp+E4h] [rbp-2Ch]
  Map *pMap; // [rsp+E8h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  v3 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v3) == 9 )
    return 10002;
  CharDepot = Player::GetCharDepot(this->m_pPlayer);
  if ( !CChrDepot::IsEnterSecondPasswordOperate(CharDepot) )
  {
    Player::TiShiInfo(this->m_pPlayer, 29, 0);
    return 2;
  }
  else
  {
    nSlot = Answer::NetPacket::readInt32(inPacket);
    if ( !CExtCharBag::IsSlotValid(this, nSlot) )
    {
      return 10002;
    }
    else
    {
      slotData = *CExtCharBag::GetSlotData(this, nSlot);
      if ( slotData.itemCount > 0 )
      {
        if ( slotData.bind == 1 || slotData.bind == 2 )
        {
          CExtCharBag::SetSlotData(this, nSlot, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_ITEM_DISCARD, 0);
          Proc = Answer::NetPacket::getProc(inPacket);
          GateIndex = Player::getGateIndex(this->m_pPlayer);
          ConnId = Player::getConnId(this->m_pPlayer);
          v8 = Answer::Singleton<GameService>::instance();
          GameService::replySuccess(v8, ConnId, GateIndex, Proc, 0);
          return 0;
        }
        else
        {
          std::vector<DropItem>::vector(&dropItems);
          pMap = StaticObj::getMap(this->m_pPlayer);
          if ( pMap )
          {
            CExtCharBag::SetSlotData(this, nSlot, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_ITEM_DISCARD, 0);
            *(_DWORD *)&stu.costType = 0;
            *(_QWORD *)&stu.costValue = 0;
            stu.itemId = slotData.itemId;
            *(_DWORD *)&stu.itemClass = (unsigned __int8)slotData.itemClass;
            *(_DWORD *)&stu.bindType = (unsigned __int8)slotData.bind;
            stu.itemCount = slotData.itemCount;
            stu.endTime = slotData.endTime;
            stu.srcId = slotData.srcId;
            std::vector<DropItem>::push_back(&dropItems, &stu);
            CDropItemGroup::CDropItemGroup(&pDropItemGroup);
            CentosPos = StaticObj::getCurrentTile(this->m_pPlayer);
            std::allocator<char>::allocator(&v21);
            std::string::string(&dropper, &unk_8C2140, &v21);
            v9 = Player::getConnId(this->m_pPlayer);
            CDropItemGroup::init(&pDropItemGroup, v9, pMap, &CentosPos, 0, 1, 0, &dropItems, &dropper, 0, 0, 0);
            std::string::~string(&dropper);
            std::allocator<char>::~allocator(&v21);
            Map::addDropItemGroup(pMap, &pDropItemGroup);
            v10 = Answer::NetPacket::getProc(inPacket);
            v11 = Player::getGateIndex(this->m_pPlayer);
            v12 = Player::getConnId(this->m_pPlayer);
            v13 = Answer::Singleton<GameService>::instance();
            GameService::replySuccess(v13, v12, v11, v10, 0);
            v2 = 0;
            CDropItemGroup::~CDropItemGroup(&pDropItemGroup);
          }
          else
          {
            v2 = 10002;
          }
          std::vector<DropItem>::~vector(&dropItems);
        }
      }
      else
      {
        return 10002;
      }
    }
  }
  return v2;
}


#####################################
int32_t __cdecl CExtCharBag::onUseMutiItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  Player *m_pPlayer; // r13
  ItemEffectManager *v5; // rax
  int32_t v6; // ebx
  ChrTask *Task; // rax
  int32_t cd_group; // ebx
  int64_t v9; // r13
  int16_t GateIndex; // r12
  GameService *v11; // rax
  ItemData item; // [rsp+10h] [rbp-60h] BYREF
  Int32Vector vSlot; // [rsp+20h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+38h] [rbp-38h] BYREF
  int32_t nId; // [rsp+3Ch] [rbp-34h]
  CfgItem *cfgItem; // [rsp+40h] [rbp-30h]
  int32_t nHaveCount; // [rsp+48h] [rbp-28h]
  int32_t err; // [rsp+4Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nId = Answer::NetPacket::readInt32(inPacket);
  nCount = Answer::NetPacket::readInt32(inPacket);
  if ( nCount <= 0 )
    return 10002;
  std::vector<int>::vector(&vSlot);
  Player::queryBagInfo(this->m_pPlayer, inPacket, &vSlot);
  v3 = Answer::Singleton<CfgData>::instance();
  cfgItem = CfgData::getItem(v3, nId);
  if ( cfgItem )
  {
    if ( !CExtCharBag::canUseItem(this, cfgItem) )
    {
      v2 = 10002;
    }
    else
    {
      nHaveCount = CExtCharBag::GetItemCount(this, &vSlot, nId, 1);
      if ( nCount > nHaveCount )
        nCount = nHaveCount;
      m_pPlayer = this->m_pPlayer;
      v5 = Answer::Singleton<ItemEffectManager>::instance();
      err = ItemEffectManager::effect(v5, nId, m_pPlayer, m_pPlayer, &nCount);
      if ( !err )
      {
        v6 = nCount;
        Task = Player::GetTask(this->m_pPlayer);
        ChrTask::updateTaskUseItem(Task, nId, v6);
        *(_DWORD *)&item.m_nClass = 1;
        item.m_nId = nId;
        item.m_nCount = nCount;
        CExtCharBag::RemoveItem(this, &item, ITEM_CHANGE_REASON::ICR_USE_MULTI_ITEM);
        cd_group = cfgItem->cd_group;
        this->m_lastItemTick[cd_group] = Unit::getTick(this->m_pPlayer);
        v9 = nId;
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        LOBYTE(cd_group) = Player::getConnId(this->m_pPlayer);
        v11 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v11, cd_group, GateIndex, 0x1E1u, v9);
      }
      v2 = err;
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
bool __cdecl CExtCharBag::canUseItem(CExtCharBag *const this, const CfgItem *pCfgItem)
{
  Job_t job; // bl
  CExtCharCarrier *CharCarrier; // rax
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax

  if ( !this->m_pPlayer || !pCfgItem )
    return 0;
  if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < pCfgItem->level )
    return 0;
  if ( pCfgItem->job )
  {
    job = pCfgItem->job;
    if ( job != Player::getJob(this->m_pPlayer) )
      return 0;
  }
  CharCarrier = Player::GetCharCarrier(this->m_pPlayer);
  if ( CExtCharCarrier::IsInCarrier(CharCarrier) && !pCfgItem->useInCarrier )
    return 0;
  if ( pCfgItem->cd_group >= 8u )
    return 0;
  if ( Unit::getTick(this->m_pPlayer) - this->m_lastItemTick[pCfgItem->cd_group] >= m_itemCD[pCfgItem->cd_group] )
    return 1;
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replyfailure(v9, ConnId, GateIndex, 0x59u, 10030, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCharBag::onMoveItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v6; // rax
  MemChrBag tmp; // [rsp+10h] [rbp-90h] BYREF
  MemChrBag newSlotData; // [rsp+30h] [rbp-70h] BYREF
  MemChrBag oldSlotData; // [rsp+50h] [rbp-50h] BYREF
  int32_t __b; // [rsp+7Ch] [rbp-24h] BYREF
  int32_t oldslot; // [rsp+80h] [rbp-20h]
  int32_t newslot; // [rsp+84h] [rbp-1Ch]
  int32_t overlay; // [rsp+88h] [rbp-18h]
  int32_t addon; // [rsp+8Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  oldslot = Answer::NetPacket::readInt32(inPacket);
  newslot = Answer::NetPacket::readInt32(inPacket);
  if ( !CExtCharBag::IsSlotValid(this, oldslot) || !CExtCharBag::IsSlotValid(this, newslot) )
    return 10002;
  if ( oldslot == newslot )
    return 10002;
  oldSlotData = *CExtCharBag::GetSlotData(this, oldslot);
  if ( oldSlotData.itemCount <= 0 )
    return 10002;
  newSlotData = *CExtCharBag::GetSlotData(this, newslot);
  if ( newSlotData.itemCount <= 0 )
  {
    CExtCharBag::setSlotData(this, newslot, &oldSlotData, ITEM_CHANGE_REASON::ICR_NONE, 0);
    CExtCharBag::setSlotData(this, oldslot, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_NONE, 0);
  }
  else if ( CExtCharBag::compairSlot(this, &oldSlotData, &newSlotData) )
  {
    itemClass = oldSlotData.itemClass;
    itemId = oldSlotData.itemId;
    v6 = Answer::Singleton<CfgData>::instance();
    overlay = CfgData::getOverlay(v6, itemId, itemClass);
    if ( overlay <= 0 )
      return 10002;
    if ( newSlotData.itemCount >= overlay )
      return 10002;
    __b = overlay - newSlotData.itemCount;
    addon = *std::min<int>(&oldSlotData.itemCount, &__b);
    if ( addon < 0 )
      return 10002;
    newSlotData.itemCount += addon;
    CExtCharBag::setSlotData(this, newslot, &newSlotData, ITEM_CHANGE_REASON::ICR_NONE, 0);
    oldSlotData.itemCount -= addon;
    CExtCharBag::setSlotData(this, oldslot, &oldSlotData, ITEM_CHANGE_REASON::ICR_NONE, 0);
  }
  else
  {
    tmp = newSlotData;
    CExtCharBag::setSlotData(this, newslot, &oldSlotData, ITEM_CHANGE_REASON::ICR_NONE, 0);
    CExtCharBag::setSlotData(this, oldslot, &tmp, ITEM_CHANGE_REASON::ICR_NONE, 0);
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharBag::onSplitItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  MemChrBag newSlotData; // [rsp+10h] [rbp-60h] BYREF
  MemChrBag slotData; // [rsp+30h] [rbp-40h] BYREF
  int32_t slot; // [rsp+54h] [rbp-1Ch]
  int32_t count; // [rsp+58h] [rbp-18h]
  int32_t freeSlot; // [rsp+5Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  slot = Answer::NetPacket::readInt32(inPacket);
  count = Answer::NetPacket::readInt32(inPacket);
  if ( !CExtCharBag::IsSlotValid(this, slot) )
    return 10002;
  slotData = *CExtCharBag::GetSlotData(this, slot);
  if ( count <= 0 || slotData.itemCount < count || slotData.itemCount <= 0 )
    return 10002;
  freeSlot = CExtCharBag::GetFirstFreeSlot(this);
  if ( !CExtCharBag::IsSlotValid(this, freeSlot) )
    return 10002;
  *(_QWORD *)&newSlotData.itemId = *(_QWORD *)&slotData.itemId;
  *(_DWORD *)&newSlotData.bind = *(_DWORD *)&slotData.bind;
  *(_QWORD *)&newSlotData.endTime = *(_QWORD *)&slotData.endTime;
  newSlotData.srcId = slotData.srcId;
  newSlotData.itemCount = count;
  CExtCharBag::setSlotData(this, freeSlot, &newSlotData, ITEM_CHANGE_REASON::ICR_NONE, 0);
  slotData.itemCount -= count;
  CExtCharBag::setSlotData(this, slot, &slotData, ITEM_CHANGE_REASON::ICR_NONE, 0);
  return 0;
}


#####################################
int32_t __cdecl CExtCharBag::onSort(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MemChrBag *v3; // rcx
  MemChrBag *v4; // rax
  MemChrBag *M_current; // rbx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v6; // rax
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v9; // rax
  MemChrBag tSlot; // [rsp+10h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > it; // [rsp+30h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+40h] [rbp-90h] BYREF
  MemChrBagVector items; // [rsp+50h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+70h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v18; // [rsp+80h] [rbp-50h] BYREF
  int32_t nBagSize; // [rsp+94h] [rbp-3Ch]
  int32_t slot; // [rsp+98h] [rbp-38h]
  int32_t i; // [rsp+9Ch] [rbp-34h]
  const MemChrBag *slotdata; // [rsp+A0h] [rbp-30h]
  bool bFind; // [rsp+AFh] [rbp-21h]
  MemChrBag *bagSlot; // [rsp+B0h] [rbp-20h]
  int32_t overlay; // [rsp+BCh] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  std::vector<MemChrBag>::vector(&items);
  nBagSize = CExtCharBag::GetBagSize(this);
  for ( i = 0; i < nBagSize; ++i )
  {
    slotdata = CExtCharBag::GetSlotData(this, i);
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
        v3 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&it);
        if ( CExtCharBag::compairSlot(this, v3, slotdata) )
        {
          v4 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&it);
          v4->itemCount += slotdata->itemCount;
          bFind = 1;
          break;
        }
      }
      if ( !bFind )
        std::vector<MemChrBag>::push_back(&items, slotdata);
    }
  }
  M_current = std::vector<MemChrBag>::end(&items)._M_current;
  v6._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
  std::sort<__gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>,bool (*)(MemChrBag const&,MemChrBag const&)>(
    v6,
    (__gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> >)M_current,
    (bool (*)(const MemChrBag *, const MemChrBag *))GreaterItem);
  slot = 0;
  for ( iter._M_current = std::vector<MemChrBag>::begin(&items)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
  {
    v18._M_current = std::vector<MemChrBag>::end(&items)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &v18) || slot >= nBagSize )
      break;
    bagSlot = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter);
    itemClass = bagSlot->itemClass;
    itemId = bagSlot->itemId;
    v9 = Answer::Singleton<CfgData>::instance();
    overlay = CfgData::getOverlay(v9, itemId, itemClass);
    if ( overlay > 0 )
    {
      while ( bagSlot->itemCount > overlay && slot < nBagSize )
      {
        tSlot = *bagSlot;
        tSlot.itemCount = overlay;
        bagSlot->itemCount -= overlay;
        CExtCharBag::setSlotData(this, slot++, &tSlot, ITEM_CHANGE_REASON::ICR_NONE, 0);
      }
      if ( bagSlot->itemCount > 0 && slot < nBagSize )
        CExtCharBag::setSlotData(this, slot++, bagSlot, ITEM_CHANGE_REASON::ICR_NONE, 0);
    }
  }
  while ( slot < nBagSize )
    CExtCharBag::setSlotData(this, slot++, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_NONE, 0);
  v2 = 0;
  std::vector<MemChrBag>::~vector(&items);
  return v2;
}


#####################################
int32_t __cdecl CExtCharBag::onSellItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int8_t v3; // r12
  int32_t v4; // ebx
  CfgData *v5; // rax
  int8_t v6; // bl
  CfgData *v7; // rax
  int32_t MapId; // r12d
  int v9; // ebx
  int32_t itemCount; // r13d
  int v11; // r14d
  CExtCurrency *Currency; // rax
  int64_t MoneyBindAndNoBind; // rax
  DBService *v14; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v18; // rax
  char LogString[4096]; // [rsp+30h] [rbp-1090h] BYREF
  Log360 Stu; // [rsp+1030h] [rbp-90h] BYREF
  _BYTE v21[16]; // [rsp+1060h] [rbp-60h] BYREF
  int64_t nTotalValue; // [rsp+1070h] [rbp-50h]
  int32_t nSize; // [rsp+107Ch] [rbp-44h]
  int32_t i; // [rsp+1080h] [rbp-40h]
  int32_t nSlot; // [rsp+1084h] [rbp-3Ch]
  const MemChrBag *slotData; // [rsp+1088h] [rbp-38h]
  int32_t itemId; // [rsp+1090h] [rbp-30h]
  int8_t itemClass; // [rsp+1097h] [rbp-29h]
  int64_t outValue; // [rsp+1098h] [rbp-28h]

  if ( !this->m_pPlayer )
    return 2;
  nTotalValue = 0;
  nSize = Answer::NetPacket::readInt32(inPacket);
  for ( i = 0; i < nSize; ++i )
  {
    nSlot = Answer::NetPacket::readInt32(inPacket);
    slotData = CExtCharBag::GetSlotData(this, nSlot);
    if ( slotData->itemCount <= 0 )
      return 10002;
    v3 = slotData->itemClass;
    v4 = slotData->itemId;
    v5 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::canSell(v5, v4, v3) )
      return 10002;
    itemId = slotData->itemId;
    itemClass = slotData->itemClass;
    v6 = itemClass;
    v7 = Answer::Singleton<CfgData>::instance();
    outValue = CfgData::getOutValue(v7, itemId, v6);
    if ( outValue < 0 )
      return 10002;
    outValue *= slotData->itemCount;
    nTotalValue += outValue;
    CExtCharBag::setSellItem(this, slotData);
    CExtCharBag::setSlotData(this, nSlot, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_SELL, 0);
    Player::AddCurrency(
      this->m_pPlayer,
      CURRENCY_TYPE::CURRENCY_MONEY,
      outValue,
      CURRENCY_CHANGE_REASON::MCR_NPC_SELL,
      slotData->itemId);
    memset(&Stu, 0, sizeof(Stu));
    std::string::string(&Stu.Interface);
    std::string::string(&Stu.passport);
    std::string::string(&Stu.LogString);
    std::string::operator=(&Stu, "game_sell");
    Stu.UseSid = Player::getSid(this->m_pPlayer);
    Player::GetPassport((Player *const)v21);
    std::string::operator=(&Stu.passport, v21);
    std::string::~string(v21);
    Stu.Cid = Player::getCid(this->m_pPlayer);
    memset(LogString, 0, sizeof(LogString));
    MapId = StaticObj::getMapId(this->m_pPlayer);
    v9 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    itemCount = slotData->itemCount;
    v11 = itemClass;
    Currency = Player::GetCurrency(this->m_pPlayer);
    MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(Currency);
    snprintf(
      LogString,
      0xFFFu,
      "balance=%lld&itemid=%d:%d&amount=%d&money=%lld&level=%d&map_id=%d",
      MoneyBindAndNoBind,
      v11,
      itemId,
      itemCount,
      outValue,
      v9,
      MapId);
    std::string::operator=(&Stu.LogString, LogString);
    LOBYTE(v9) = Player::getConnId(this->m_pPlayer);
    v14 = Answer::Singleton<DBService>::instance();
    DBService::log360(v14, v9, &Stu);
    Log360::~Log360(&Stu);
  }
  CExtCharBag::SendBagSellItem(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v18 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v18, ConnId, GateIndex, Proc, nTotalValue);
  return 0;
}


#####################################
int32_t __cdecl CExtCharBag::onAddItem(CExtCharBag *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  MemChrBag *v3; // rbx
  MemChrBag *v4; // rbx
  MemChrBag *v5; // rbx
  MemChrBag *v6; // rbx
  MemChrBag *v7; // rbx
  MemChrBag *v8; // rbx
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v11; // rax
  MemChrBag __x; // [rsp+0h] [rbp-A0h]
  MemChrBagVector vItem; // [rsp+30h] [rbp-70h] BYREF
  std::string MailParam; // [rsp+50h] [rbp-50h] BYREF
  MemChrBag v16; // [rsp+60h] [rbp-40h]
  ITEM_CHANGE_REASON nReason; // [rsp+80h] [rbp-20h]
  int32_t nSize; // [rsp+84h] [rbp-1Ch]
  int32_t i; // [rsp+88h] [rbp-18h]
  int32_t MailId; // [rsp+8Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 2;
  nReason = Answer::NetPacket::readInt32(inPacket);
  Answer::NetPacket::readUTF8((Answer::NetPacket *const)&MailParam, (bool)inPacket);
  std::vector<MemChrBag>::vector(&vItem);
  nSize = Answer::NetPacket::readInt32(inPacket);
  v16.itemId = 0;
  v16.itemClass = 0;
  v16.itemCount = 0;
  v16.bind = 0;
  v16.endTime = 0;
  v16.srcId = 0;
  *(_OWORD *)&__x.itemId = *(_OWORD *)&v16.itemId;
  *(_OWORD *)&__x.endTime = *(unsigned __int64 *)&v16.endTime;
  std::vector<MemChrBag>::resize(&vItem, nSize, __x);
  for ( i = 0; i < nSize; ++i )
  {
    v3 = std::vector<MemChrBag>::operator[](&vItem, i);
    v3->itemId = Answer::NetPacket::readInt32(inPacket);
    v4 = std::vector<MemChrBag>::operator[](&vItem, i);
    v4->itemClass = Answer::NetPacket::readInt8(inPacket);
    v5 = std::vector<MemChrBag>::operator[](&vItem, i);
    v5->itemCount = Answer::NetPacket::readInt32(inPacket);
    v6 = std::vector<MemChrBag>::operator[](&vItem, i);
    v6->bind = Answer::NetPacket::readInt8(inPacket);
    v7 = std::vector<MemChrBag>::operator[](&vItem, i);
    v7->endTime = Answer::NetPacket::readInt32(inPacket);
    v8 = std::vector<MemChrBag>::operator[](&vItem, i);
    v8->srcId = Answer::NetPacket::readInt64(inPacket);
  }
  if ( !CExtCharBag::AddItem(this, &vItem, nReason) )
  {
    MailId = 0;
    if ( nReason == ITEM_CHANGE_REASON::ICR_AUCTION_BUY )
    {
      MailId = 6208;
    }
    else if ( nReason == ITEM_CHANGE_REASON::ICR_AUCTION_CANCEL )
    {
      MailId = 6209;
    }
    else
    {
      MailId = 6208;
    }
    Cid = Player::getCid(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v11 = Answer::Singleton<DBService>::instance();
    DBService::OnSendSysMail(v11, ConnId, Cid, MailId, &vItem, nReason, &MailParam, 0);
  }
  v2 = 0;
  std::vector<MemChrBag>::~vector(&vItem);
  std::string::~string(&MailParam);
  return v2;
}


#####################################
int32_t __cdecl CExtCharBag::buyBackChrShopItem(
        CExtCharBag *const this,
        int32_t index,
        int32_t itemID,
        int8_t itemClass)
{
  CfgData *v5; // rax
  CExtCurrency *Currency; // rax
  CExtCurrency *v7; // rax
  int freeSlot; // [rsp+28h] [rbp-18h]
  int costValue; // [rsp+2Ch] [rbp-14h]

  if ( !this->m_pPlayer || (unsigned int)index >= 0x10 )
    return 10002;
  freeSlot = CExtCharBag::GetFirstFreeSlot(this);
  if ( freeSlot < 0 )
    return 10002;
  if ( this->m_sellItemInfo[index].itemId != itemID || this->m_sellItemInfo[index].itemClass != itemClass )
    return 10002;
  v5 = Answer::Singleton<CfgData>::instance();
  costValue = this->m_sellItemInfo[index].itemCount * CfgData::getOutValue(v5, itemID, itemClass);
  if ( costValue <= 0 )
    return 10002;
  Currency = Player::GetCurrency(this->m_pPlayer);
  if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < costValue )
    return 10002;
  CExtCharBag::setSlotData(this, freeSlot, &this->m_sellItemInfo[index], ITEM_CHANGE_REASON::ICR_BUY_BACK, 0);
  Player::sendBuyItemInfo(
    this->m_pPlayer,
    this->m_sellItemInfo[index].itemId,
    this->m_sellItemInfo[index].itemClass,
    this->m_sellItemInfo[index].itemCount,
    costValue,
    0);
  CExtCharBag::deleteSellItem(this, index);
  v7 = Player::GetCurrency(this->m_pPlayer);
  CExtCurrency::DecMoneyAndNoBind(v7, costValue, CURRENCY_CHANGE_REASON::MCR_BUY_BACK_ITEM, itemID);
  CExtCharBag::SendBagSellItem(this);
  return 0;
}


#####################################
int32_t __cdecl CExtCharBag::buyChrShopItem(CExtCharBag *const this, CfgChrShop *pCharShop, int32_t id, int32_t count)
{
  int32_t v4; // ebx
  CExtCharBag *Bag; // rax
  CXinMo *CXinMo; // rax
  int32_t ConstType; // eax
  int64_t v8; // r12
  CExtCurrency *v9; // rax
  int64_t ItemId; // r13
  int32_t v11; // ebx
  CExtCurrency *Currency; // rax
  CharId_t Cid; // rbx
  unsigned int Now; // eax
  int32_t MapId; // r12d
  int v16; // ebx
  int32_t v17; // r14d
  int itemClass; // r13d
  CExtCurrency *v19; // rax
  int64_t MoneyBindAndNoBind; // rax
  DBService *v21; // rax
  char LogString[4096]; // [rsp+40h] [rbp-1080h] BYREF
  Log360 Stu; // [rsp+1040h] [rbp-80h] BYREF
  MemChrBag add; // [rsp+1070h] [rbp-50h] BYREF
  _BYTE v27[12]; // [rsp+1090h] [rbp-30h] BYREF
  int32_t costValue; // [rsp+109Ch] [rbp-24h]

  if ( !this->m_pPlayer || !pCharShop )
    return 10002;
  if ( pCharShop->Price <= 0 || count <= 0 )
    return 10002;
  if ( pCharShop->LimitCount > 0 && count + CExtCharBag::getLimitCount(this, pCharShop->Index) > pCharShop->LimitCount )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 2;
  memset(&add, 0, sizeof(add));
  add.itemId = pCharShop->ItemId;
  add.itemClass = pCharShop->ItemClass;
  add.itemCount = count;
  add.bind = pCharShop->IsBind;
  costValue = count * pCharShop->Price;
  if ( pCharShop->ConstType > 12 || pCharShop->ConstType < -1 )
    return 2;
  CXinMo = Player::GetCXinMo(this->m_pPlayer);
  if ( CXinMo::GetXinMoLevel(CXinMo) < pCharShop->QiQinglevel )
    return 2;
  ConstType = pCharShop->ConstType;
  if ( ConstType && ConstType != 6 )
  {
    ItemId = pCharShop->ItemId;
    v11 = pCharShop->ConstType;
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecCurrency(
            Currency,
            (const CURRENCY_TYPE)v11,
            costValue,
            CURRENCY_CHANGE_REASON::MCR_CHR_SHOP_COST,
            ItemId) )
      return 10002;
  }
  else
  {
    v8 = pCharShop->ItemId;
    v9 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v9, costValue, CURRENCY_CHANGE_REASON::MCR_CHR_SHOP_COST, v8) )
      return 10002;
  }
  if ( !CExtCharBag::AddItem(this, &add, ITEM_CHANGE_REASON::ICR_SHOP_BUY) )
  {
    Cid = Player::getCid(this->m_pPlayer);
    Now = Unit::getNow(this->m_pPlayer);
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      &byte_8C2228,
      (unsigned int)pCharShop->ItemClass,
      (unsigned int)pCharShop->ItemId,
      (unsigned int)count,
      Now,
      Cid);
  }
  if ( pCharShop->LimitCount > 0 )
    CExtCharBag::addLimitCount(this, pCharShop->Index, count);
  Player::sendBuyItemInfo(this->m_pPlayer, add.itemId, add.itemClass, count, costValue, pCharShop->Index);
  memset(&Stu, 0, sizeof(Stu));
  std::string::string(&Stu.Interface);
  std::string::string(&Stu.passport);
  std::string::string(&Stu.LogString);
  std::string::operator=(&Stu, "game_buy");
  Stu.UseSid = Player::getSid(this->m_pPlayer);
  Player::GetPassport((Player *const)v27);
  std::string::operator=(&Stu.passport, v27);
  std::string::~string(v27);
  Stu.Cid = Player::getCid(this->m_pPlayer);
  memset(LogString, 0, sizeof(LogString));
  MapId = StaticObj::getMapId(this->m_pPlayer);
  v16 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
  v17 = add.itemId;
  itemClass = add.itemClass;
  v19 = Player::GetCurrency(this->m_pPlayer);
  MoneyBindAndNoBind = CExtCurrency::GetMoneyBindAndNoBind(v19);
  snprintf(
    LogString,
    0xFFFu,
    "balance=%lld&itemid=%d:%d&amount=%d&money=%d&level=%d&remain=&map_id=%d",
    MoneyBindAndNoBind,
    itemClass,
    v17,
    count,
    costValue,
    v16,
    MapId);
  std::string::operator=(&Stu.LogString, LogString);
  LOBYTE(v16) = Player::getConnId(this->m_pPlayer);
  v21 = Answer::Singleton<DBService>::instance();
  DBService::log360(v21, v16, &Stu);
  v4 = 0;
  Log360::~Log360(&Stu);
  return v4;
}


#####################################
void __cdecl CExtCharBag::CleanItemId(CExtCharBag *const this, int32_t nId, ITEM_CHANGE_REASON nReason, int8_t nClass)
{
  __int64 bagSlot; // [rsp+20h] [rbp-40h]
  int32_t nBagSize; // [rsp+48h] [rbp-18h]
  int32_t i; // [rsp+4Ch] [rbp-14h]

  nBagSize = CExtCharBag::GetBagSize(this);
  for ( i = 0; i < nBagSize; ++i )
  {
    bagSlot = *(_QWORD *)&CExtCharBag::GetSlotData(this, i)->itemId;
    if ( (_DWORD)bagSlot == nId && BYTE4(bagSlot) == nClass )
      CExtCharBag::setSlotData(this, i, &this->m_nullobj, nReason, 0);
  }
}


#####################################
bool __cdecl CExtCharBag::AddItemsAndMingGe(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        ITEM_CHANGE_REASON addReason)
{
  bool v3; // bl
  int32_t itemId; // ebx
  CfgData *v5; // rax
  const CMingGeTable *CMingGeTable; // rax
  const MemChrBag *v7; // rax
  int32_t v8; // ebx
  CfgData *v9; // rax
  const KunLingTable *KunLingTable; // rax
  const MemChrBag *v11; // rax
  CMingGeExt *CMingGeExt; // rax
  int32_t BagFreeSlotCount; // ebx
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CKunExt *CKunExt; // rax
  int32_t EmptyBagCount; // ebx
  int32_t nCount; // r12d
  int32_t nId; // ebx
  CKunExt *v20; // rax
  CExtCharBag *v21; // rax
  int32_t v22; // ebx
  CMingGeExt *v23; // rax
  std::_List_iterator<int> it_1; // [rsp+20h] [rbp-D0h] BYREF
  std::_List_iterator<LingZhuBag> it_0; // [rsp+30h] [rbp-C0h] BYREF
  LingZhuBag stu; // [rsp+40h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > it; // [rsp+50h] [rbp-A0h] BYREF
  std::list<LingZhuBag> LingZhuList; // [rsp+60h] [rbp-90h] BYREF
  std::list<int> MingGeList; // [rsp+70h] [rbp-80h] BYREF
  MemChrBagVector items; // [rsp+80h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+A0h] [rbp-50h] BYREF
  std::_List_iterator<LingZhuBag> __x; // [rsp+B0h] [rbp-40h] BYREF
  std::_List_iterator<int> v35; // [rsp+C0h] [rbp-30h] BYREF
  const CMingGeCfg *pCMingGeCfg; // [rsp+C8h] [rbp-28h]
  int32_t ItemCount; // [rsp+D4h] [rbp-1Ch]
  const LingZhuCfg *pLingZhuCfg; // [rsp+D8h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  if ( std::vector<MemChrBag>::empty(vItem) )
    return 1;
  std::vector<MemChrBag>::vector(&items);
  std::list<int>::list(&MingGeList);
  std::list<LingZhuBag>::list(&LingZhuList);
  for ( it._M_current = std::vector<MemChrBag>::begin(vItem)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(vItem)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&it, &__rhs) )
      break;
    if ( __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemClass == 10 )
    {
      itemId = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemId;
      v5 = Answer::Singleton<CfgData>::instance();
      CMingGeTable = CfgData::GetCMingGeTable(v5);
      pCMingGeCfg = CMingGeTable::GetCMingGeCfg(CMingGeTable, itemId);
      if ( pCMingGeCfg && !pCMingGeCfg->nCanPickup )
      {
        for ( ItemCount = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemCount;
              ItemCount > 0;
              --ItemCount )
        {
          v7 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it);
          std::list<int>::push_back(&MingGeList, &v7->itemId);
        }
      }
    }
    else if ( __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemClass == 11 )
    {
      v8 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemId;
      v9 = Answer::Singleton<CfgData>::instance();
      KunLingTable = CfgData::GetKunLingTable(v9);
      pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, v8);
      if ( pLingZhuCfg
        && __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemCount > 0 )
      {
        stu = 0;
        stu.nId = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemId;
        stu.nCount = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&it)->itemCount;
        std::list<LingZhuBag>::push_back(&LingZhuList, &stu);
      }
    }
    else
    {
      v11 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&it);
      std::vector<MemChrBag>::push_back(&items, v11);
    }
  }
  CMingGeExt = Player::GetCMingGeExt(this->m_pPlayer);
  BagFreeSlotCount = CMingGeExt::GetBagFreeSlotCount(CMingGeExt, 1);
  if ( BagFreeSlotCount >= (int)std::list<int>::size(&MingGeList) )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
    if ( FreeSlotCount >= (int)std::vector<MemChrBag>::size(&items) )
    {
      CKunExt = Player::GetCKunExt(this->m_pPlayer);
      EmptyBagCount = CKunExt::GetEmptyBagCount(CKunExt);
      if ( EmptyBagCount >= (int)std::list<LingZhuBag>::size(&LingZhuList) )
      {
        if ( std::list<LingZhuBag>::size(&LingZhuList) )
        {
          for ( it_0._M_node = std::list<LingZhuBag>::begin(&LingZhuList)._M_node;
                ;
                std::_List_iterator<LingZhuBag>::operator++(&it_0, 0) )
          {
            __x._M_node = std::list<LingZhuBag>::end(&LingZhuList)._M_node;
            if ( !std::_List_iterator<LingZhuBag>::operator!=(&it_0, &__x) )
              break;
            nCount = std::_List_iterator<LingZhuBag>::operator->(&it_0)->nCount;
            nId = std::_List_iterator<LingZhuBag>::operator->(&it_0)->nId;
            v20 = Player::GetCKunExt(this->m_pPlayer);
            if ( !CKunExt::AddLingZhuBagItem(v20, nId, nCount, addReason) )
            {
              v3 = 0;
              goto LABEL_40;
            }
          }
        }
        if ( std::vector<MemChrBag>::size(&items)
          && (v21 = Player::GetBag(this->m_pPlayer), !CExtCharBag::AddItem(v21, &items, addReason)) )
        {
          v3 = 0;
        }
        else
        {
          if ( std::list<int>::size(&MingGeList) )
          {
            for ( it_1._M_node = std::list<int>::begin(&MingGeList)._M_node;
                  ;
                  std::_List_iterator<int>::operator++(&it_1, 0) )
            {
              v35._M_node = std::list<int>::end(&MingGeList)._M_node;
              if ( !std::_List_iterator<int>::operator!=(&it_1, &v35) )
                break;
              v22 = *std::_List_iterator<int>::operator*(&it_1);
              v23 = Player::GetCMingGeExt(this->m_pPlayer);
              CMingGeExt::AddItem(v23, v22, addReason);
            }
          }
          v3 = 1;
        }
      }
      else
      {
        v3 = 0;
      }
    }
    else
    {
      Player::TiShiInfo(this->m_pPlayer, 2048, 0);
      v3 = 0;
    }
  }
  else
  {
    Player::TiShiInfo(this->m_pPlayer, 3, 0);
    v3 = 0;
  }
LABEL_40:
  std::list<LingZhuBag>::~list(&LingZhuList);
  std::list<int>::~list(&MingGeList);
  std::vector<MemChrBag>::~vector(&items);
  return v3;
}


#####################################
int32_t __cdecl CExtCharBag::getLimitCount(CExtCharBag *const this, int32_t index)
{
  int32_t indexa; // [rsp+4h] [rbp-2Ch] BYREF
  CExtCharBag *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  indexa = index;
  it._M_node = std::map<int,int>::find(&this->m_ItemLimit, &indexa)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_ItemLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
    return std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it)->second;
  else
    return 0;
}


#####################################
void __cdecl CExtCharBag::addLimitCount(CExtCharBag *const this, int32_t index, int32_t count)
{
  std::pair<const int,int> *v3; // rax
  int32_t indexa; // [rsp+4h] [rbp-2Ch] BYREF
  CExtCharBag *thisa; // [rsp+8h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-10h] BYREF

  thisa = this;
  indexa = index;
  it._M_node = std::map<int,int>::find(&this->m_ItemLimit, &indexa)._M_node;
  __x._M_node = std::map<int,int>::end(&thisa->m_ItemLimit)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
    v3->second += count;
  }
  else
  {
    *std::map<int,int>::operator[](&thisa->m_ItemLimit, &indexa) = count;
  }
  CExtCharBag::SendLimitCount(thisa);
}


#####################################
void __cdecl CExtCharBag::SendLimitCount(CExtCharBag *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  std::pair<const int,int> *v3; // rax
  std::pair<const int,int> *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t Count; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DBAu);
    if ( packet )
    {
      Count = std::map<int,int>::size(&this->m_ItemLimit);
      Answer::NetPacket::writeInt32(packet, Count);
      for ( it._M_node = std::map<int,int>::begin(&this->m_ItemLimit)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it) )
      {
        __x._M_node = std::map<int,int>::end(&this->m_ItemLimit)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v3->first);
        v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v4->second);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v7 = Player::getConnId(this->m_pPlayer);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CExtCharBag::GetTypeItem(CExtCharBag *const this, int32_t nType)
{
  int32_t BagSize; // [rsp+14h] [rbp-Ch]
  int32_t i; // [rsp+18h] [rbp-8h]

  BagSize = CExtCharBag::GetBagSize(this);
  for ( i = 0; i < BagSize; ++i )
  {
    if ( CItemHelper::GetItemType(this->m_bagData[i].itemId, this->m_bagData[i].itemClass) == nType )
      return i;
  }
  return -1;
}


#####################################
void __cdecl CExtCharBag::SetSlotData(
        CExtCharBag *const this,
        int32_t slot,
        const MemChrBag *const slotData,
        ITEM_CHANGE_REASON reason,
        int32_t count)
{
  CExtCharBag::setSlotData(this, slot, slotData, reason, count);
  CExtCharBag::saveItemChangeLog(this);
}


#####################################
void __cdecl CExtCharBag::CleanSlot(CExtCharBag *const this, int32_t slot, ITEM_CHANGE_REASON reason)
{
  EquipId_t srcId; // r12
  int8_t ConnId; // bl
  CEquipManager *v5; // rax

  if ( CExtCharBag::IsSlotValid(this, slot) && this->m_bagData[slot].itemId > 0 )
  {
    CExtCharBag::addItemChangeLog(
      this,
      reason,
      this->m_bagData[slot].itemId,
      this->m_bagData[slot].itemClass,
      this->m_bagData[slot].srcId,
      this->m_bagData[slot].itemCount,
      2,
      0);
    if ( this->m_bagData[slot].srcId > 0 && this->m_bagData[slot].itemClass == 2 )
    {
      srcId = this->m_bagData[slot].srcId;
      ConnId = Player::getConnId(this->m_pPlayer);
      v5 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::DeleteMemEquip(v5, ConnId, srcId, reason);
    }
    this->m_bagData[slot] = this->m_nullobj;
    CExtCharBag::addDirty(this, slot, reason, 0);
    CExtCharBag::saveItemChangeLog(this);
  }
}


#####################################
void __cdecl CExtCharBag::setSlotData(
        CExtCharBag *const this,
        int32_t slot,
        const MemChrBag *const slotData,
        ITEM_CHANGE_REASON reason,
        int32_t count)
{
  __int64 v5; // rcx
  bool bNeedCreate; // [rsp+3Fh] [rbp-11h]

  if ( CExtCharBag::IsSlotValid(this, slot) )
  {
    if ( slotData->itemCount <= 0 )
    {
      if ( this->m_bagData[slot].itemId > 0 )
        CExtCharBag::addItemChangeLog(
          this,
          reason,
          this->m_bagData[slot].itemId,
          this->m_bagData[slot].itemClass,
          this->m_bagData[slot].srcId,
          this->m_bagData[slot].itemCount,
          2,
          0);
      this->m_bagData[slot] = this->m_nullobj;
      CExtCharBag::addDirty(this, slot, reason, 0);
    }
    else
    {
      if ( this->m_bagData[slot].itemCount < slotData->itemCount )
        CExtCharBag::addItemChangeLog(
          this,
          reason,
          slotData->itemId,
          slotData->itemClass,
          slotData->srcId,
          slotData->itemCount - this->m_bagData[slot].itemCount,
          1,
          0);
      else
        CExtCharBag::addItemChangeLog(
          this,
          reason,
          slotData->itemId,
          slotData->itemClass,
          slotData->srcId,
          this->m_bagData[slot].itemCount - slotData->itemCount,
          2,
          0);
      v5 = 16 * (2LL * slot + 1);
      *(int (***)(...))((char *)&this->_vptr_IExtSystem + v5) = *(int (***)(...))&slotData->itemId;
      *(Player **)((char *)&this->m_pPlayer + v5) = *(Player **)&slotData->itemCount;
      *(_QWORD *)((char *)&this->m_bagData[0].itemId + v5) = *(_QWORD *)&slotData->endTime;
      *(_QWORD *)((char *)&this->m_bagData[0].itemCount + v5) = slotData->srcId;
      bNeedCreate = 0;
      if ( slotData->itemClass == 2 )
        bNeedCreate = slotData->srcId == 0;
      CExtCharBag::addDirty(this, slot, reason, bNeedCreate);
    }
  }
}


#####################################
int32_t __cdecl CExtCharBag::GetItemCount(const CExtCharBag *const this, int32_t nId, int8_t nClass)
{
  int32_t endTime; // ebx
  bool v4; // al
  int32_t nCount; // [rsp+1Ch] [rbp-24h]
  int32_t nBagSize; // [rsp+20h] [rbp-20h]
  int32_t i; // [rsp+24h] [rbp-1Ch]
  const MemChrBag *slotData; // [rsp+28h] [rbp-18h]

  nCount = 0;
  nBagSize = CExtCharBag::GetBagSize(this);
  for ( i = 0; i < nBagSize; ++i )
  {
    slotData = CExtCharBag::GetSlotData(this, i);
    if ( !CExtCharBag::IsEmptySlot(this, slotData) )
    {
      v4 = 0;
      if ( slotData->endTime > 0 )
      {
        if ( this->m_pPlayer )
        {
          endTime = slotData->endTime;
          if ( endTime <= Unit::getNow(this->m_pPlayer) )
            v4 = 1;
        }
      }
      if ( !v4 && slotData->itemClass == nClass && slotData->itemId == nId )
        nCount += slotData->itemCount;
    }
  }
  return nCount;
}


#####################################
bool __cdecl CExtCharBag::HasItem(const CExtCharBag *const this, const ItemData *const data)
{
  return CExtCharBag::HasItem(this, data->m_nId, data->m_nClass, data->m_nCount);
}


#####################################
bool __cdecl CExtCharBag::HasItem(const CExtCharBag *const this, int32_t nId, int8_t nClass, int32_t nCount)
{
  int32_t endTime; // ebx
  int32_t countHas; // [rsp+2Ch] [rbp-24h]
  int32_t nBagSize; // [rsp+30h] [rbp-20h]
  int32_t slot; // [rsp+34h] [rbp-1Ch]
  const MemChrBag *slotData; // [rsp+38h] [rbp-18h]

  countHas = 0;
  nBagSize = CExtCharBag::GetBagSize(this);
  for ( slot = 0; slot < nBagSize; ++slot )
  {
    slotData = CExtCharBag::GetSlotData(this, slot);
    if ( slotData->itemCount > 0 && slotData->itemClass == nClass )
    {
      if ( slotData->endTime <= 0
        || !this->m_pPlayer
        || (endTime = slotData->endTime, endTime > Unit::getNow(this->m_pPlayer)) )
      {
        if ( slotData->itemId == nId )
          countHas += slotData->itemCount;
        if ( countHas >= nCount )
          return 1;
      }
    }
  }
  return 0;
}


#####################################
int32_t __cdecl CExtCharBag::GetFirstFreeSlot(const CExtCharBag *const this)
{
  const MemChrBag *SlotData; // rdx
  int32_t nBagSize; // [rsp+10h] [rbp-10h]
  int32_t slot; // [rsp+14h] [rbp-Ch]

  nBagSize = CExtCharBag::GetBagSize(this);
  for ( slot = 0; slot < nBagSize; ++slot )
  {
    SlotData = CExtCharBag::GetSlotData(this, slot);
    if ( CExtCharBag::IsEmptySlot(this, SlotData) )
      return slot;
  }
  return -1;
}


#####################################
int32_t __cdecl CExtCharBag::GetFreeSlotCount(const CExtCharBag *const this)
{
  const MemChrBag *SlotData; // rdx
  int32_t count; // [rsp+1Ch] [rbp-14h]
  int32_t nBagSize; // [rsp+20h] [rbp-10h]
  int32_t slot; // [rsp+24h] [rbp-Ch]

  count = 0;
  nBagSize = CExtCharBag::GetBagSize(this);
  for ( slot = 0; slot < nBagSize; ++slot )
  {
    SlotData = CExtCharBag::GetSlotData(this, slot);
    if ( CExtCharBag::IsEmptySlot(this, SlotData) )
      ++count;
  }
  return count;
}


#####################################
bool __cdecl CExtCharBag::IsSlotValid(const CExtCharBag *const this, int32_t slot)
{
  return slot >= 0 && CExtCharBag::GetBagSize(this) > slot;
}


#####################################
void __cdecl CExtCharBag::SendBagItem(CExtCharBag *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-38h]
  uint32_t nOffSet; // [rsp+24h] [rbp-2Ch]
  int32_t nCount; // [rsp+28h] [rbp-28h]
  int32_t nBagSize; // [rsp+2Ch] [rbp-24h]
  uint32_t endOffSet; // [rsp+30h] [rbp-20h]
  int32_t slot; // [rsp+34h] [rbp-1Ch]
  const MemChrBag *tSlot; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2759u);
    if ( packet )
    {
      nOffSet = Answer::NetPacket::getWOffset(packet);
      nCount = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      nBagSize = CExtCharBag::GetBagSize(this);
      for ( slot = 0; slot < nBagSize; ++slot )
      {
        tSlot = &this->m_bagData[slot];
        if ( tSlot->itemCount > 0 )
        {
          Answer::NetPacket::writeInt32(packet, slot);
          Answer::NetPacket::writeInt32(packet, tSlot->itemId);
          Answer::NetPacket::writeInt8(packet, tSlot->itemClass);
          Answer::NetPacket::writeInt32(packet, tSlot->itemCount);
          Answer::NetPacket::writeInt8(packet, tSlot->bind);
          Answer::NetPacket::writeInt32(packet, tSlot->endTime);
          Answer::NetPacket::writeInt64(packet, tSlot->srcId);
          ++nCount;
        }
      }
      endOffSet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, nOffSet);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::setWOffset(packet, endOffSet);
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
void __cdecl CExtCharBag::SendBagSellItem(CExtCharBag *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-30h]
  uint32_t nOffSet; // [rsp+18h] [rbp-28h]
  int32_t nCount; // [rsp+1Ch] [rbp-24h]
  uint32_t endOffSet; // [rsp+20h] [rbp-20h]
  int i; // [rsp+24h] [rbp-1Ch]
  const MemChrBag *tSlot; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DB9u);
    if ( packet )
    {
      nOffSet = Answer::NetPacket::getWOffset(packet);
      nCount = 0;
      Answer::NetPacket::writeInt32(packet, 0);
      for ( i = 0; i <= 14; ++i )
      {
        tSlot = &this->m_sellItemInfo[i];
        if ( tSlot->itemCount > 0 )
        {
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt32(packet, tSlot->itemId);
          Answer::NetPacket::writeInt8(packet, tSlot->itemClass);
          Answer::NetPacket::writeInt32(packet, tSlot->itemCount);
          Answer::NetPacket::writeInt8(packet, tSlot->bind);
          Answer::NetPacket::writeInt32(packet, tSlot->endTime);
          Answer::NetPacket::writeInt64(packet, tSlot->srcId);
          ++nCount;
        }
      }
      endOffSet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, nOffSet);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::setWOffset(packet, endOffSet);
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
void __cdecl CExtCharBag::SaveDBData(CExtCharBag *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->bagData.bagData, this->m_bagData, sizeof(dbData->bagData.bagData));
}


#####################################
void __cdecl CExtCharBag::setSellItem(CExtCharBag *const this, const MemChrBag *const sellItem)
{
  EquipId_t srcId; // r12
  int8_t ConnId; // bl
  CEquipManager *v4; // rax
  MemChrBag *v5; // rax
  int32_t i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_sellItemInfo[14].srcId > 0 && this->m_sellItemInfo[14].itemClass == 2 )
  {
    srcId = this->m_sellItemInfo[14].srcId;
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<CEquipManager>::instance();
    CEquipManager::DeleteMemEquip(v4, ConnId, srcId, 131);
  }
  for ( i = 14; i > 0; --i )
  {
    v5 = &this->m_sellItemInfo[i];
    *(_QWORD *)&v5->itemId = *((_QWORD *)&this->m_nullobj.itemId + 4 * i);
    *(_QWORD *)&v5->itemCount = *((_QWORD *)&this->m_nullobj.itemCount + 4 * i);
    *(_QWORD *)&v5->endTime = *((_QWORD *)&this->m_nullobj.endTime + 4 * i);
    v5->srcId = *(&this->m_nullobj.srcId + 4 * i);
  }
  this->m_sellItemInfo[0] = *(const MemChrBag *)sellItem;
}


#####################################
void __cdecl CExtCharBag::deleteSellItem(CExtCharBag *const this, int32_t index)
{
  MemChrBag *v2; // rax
  int i; // [rsp+1Ch] [rbp-4h]

  if ( (unsigned int)index < 0x10 )
  {
    for ( i = index; i <= 13; ++i )
    {
      v2 = &this->m_sellItemInfo[i];
      *(_QWORD *)&v2->itemId = *(_QWORD *)&this->m_sellItemInfo[i + 1].itemId;
      *(_QWORD *)&v2->itemCount = *(_QWORD *)&this->m_sellItemInfo[i + 1].itemCount;
      *(_QWORD *)&v2->endTime = *(_QWORD *)&this->m_sellItemInfo[i + 1].endTime;
      v2->srcId = this->m_sellItemInfo[i + 1].srcId;
    }
    bzero(&this->m_sellItemInfo[14], 0x20u);
  }
}


#####################################
void __cdecl CExtCharBag::sendGoldCashChange(
        CExtCharBag *const this,
        int32_t type,
        int32_t addon,
        BenefitType benefitType)
{
  int8_t ConnId; // bl
  GameService *v5; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x275Cu);
    Answer::NetPacket::writeInt32(packet, type);
    Answer::NetPacket::writeInt32(packet, addon);
    Answer::NetPacket::writeInt32(packet, benefitType);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v9, v8, GateIndex, packet);
  }
}


#####################################
int32_t __cdecl CExtCharBag::GetItemCount(
        const CExtCharBag *const this,
        const Int32Vector *const vSlot,
        int8_t nClass,
        int32_t nId)
{
  int v4; // edx
  int v5; // edx
  int32_t endTime; // ebx
  int32_t nCount; // [rsp+2Ch] [rbp-24h]
  int32_t isize; // [rsp+30h] [rbp-20h]
  int32_t i; // [rsp+34h] [rbp-1Ch]
  const MemChrBag *bagSlot; // [rsp+38h] [rbp-18h]

  nCount = 0;
  isize = std::vector<int>::size(vSlot);
  for ( i = 0; i < isize; ++i )
  {
    v4 = *std::vector<int>::operator[](vSlot, i);
    if ( CExtCharBag::IsSlotValid(this, v4) )
    {
      v5 = *std::vector<int>::operator[](vSlot, i);
      bagSlot = CExtCharBag::GetSlotData(this, v5);
      if ( bagSlot->itemId == nId && bagSlot->itemClass == nClass )
      {
        if ( bagSlot->endTime <= 0
          || !this->m_pPlayer
          || (endTime = bagSlot->endTime, endTime > Unit::getNow(this->m_pPlayer)) )
        {
          nCount += bagSlot->itemCount;
        }
      }
    }
  }
  return nCount;
}


#####################################
int32_t __cdecl CExtCharBag::GetItemType(const CExtCharBag *const this, const MemChrBag *const item)
{
  return CItemHelper::GetItemType(item->itemId, item->itemClass);
}


#####################################
bool __cdecl CExtCharBag::IsEmptySlot(const CExtCharBag *const this, const MemChrBag *const slot)
{
  return !slot->itemId || !slot->itemCount;
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        const Int32Vector *const vSlot,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, lst, nReason) || !CExtCharBag::addItem(this, vItem, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        const Int32Vector *const vSlot,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, data, nReason) || !CExtCharBag::addItem(this, vItem, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, lst, nReason) || !CExtCharBag::addItem(this, vItem, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, data, nReason) || !CExtCharBag::addItem(this, vItem, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBag *const item,
        const Int32Vector *const vSlot,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, lst, nReason) || !CExtCharBag::addItem(this, item, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBag *const item,
        const Int32Vector *const vSlot,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, data, nReason) || !CExtCharBag::addItem(this, item, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBag *const item,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, lst, nReason) || !CExtCharBag::addItem(this, item, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddAndRemoveItem(
        CExtCharBag *const this,
        const MemChrBag *const item,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, data, nReason) || !CExtCharBag::addItem(this, item, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::AddItem(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::addItem(this, vItem, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::addItem(
        CExtCharBag *const this,
        const MemChrBagVector *const vItem,
        ITEM_CHANGE_REASON nReason)
{
  size_t v3; // rax
  const MemChrBag *v4; // rdx
  const MemChrBag *v5; // rax
  const MemChrBag *v6; // rcx
  bool v7; // bl
  MemChrBag *v8; // rcx
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter_0; // [rsp+20h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+30h] [rbp-60h] BYREF
  MemChrBagVector vAutoUseItem; // [rsp+40h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+60h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > v15; // [rsp+70h] [rbp-20h] BYREF

  std::vector<MemChrBag>::vector(&vAutoUseItem);
  v3 = std::vector<MemChrBag>::size(vItem);
  std::vector<MemChrBag>::reserve(&vAutoUseItem, v3);
  for ( iter._M_current = std::vector<MemChrBag>::begin(vItem)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter) )
  {
    __rhs._M_current = std::vector<MemChrBag>::end(vItem)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag const*,std::vector<MemChrBag>>(&iter, &__rhs) )
      break;
    v4 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&iter);
    if ( CExtCharBag::isAutoUseItem(this, v4) )
    {
      v5 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&iter);
      std::vector<MemChrBag>::push_back(&vAutoUseItem, v5);
    }
    else
    {
      v6 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator*(&iter);
      if ( !CExtCharBag::addItem(this, v6, nReason) )
      {
        v7 = 0;
        goto LABEL_12;
      }
    }
  }
  for ( iter_0._M_current = std::vector<MemChrBag>::begin(&vAutoUseItem)._M_current;
        ;
        __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter_0) )
  {
    v15._M_current = std::vector<MemChrBag>::end(&vAutoUseItem)._M_current;
    if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter_0, &v15) )
      break;
    v8 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator*(&iter_0);
    CExtCharBag::autoUseItem(this, v8, nReason);
  }
  v7 = 1;
LABEL_12:
  std::vector<MemChrBag>::~vector(&vAutoUseItem);
  return v7;
}


#####################################
bool __cdecl CExtCharBag::AddItem(CExtCharBag *const this, const MemChrBag *const item, ITEM_CHANGE_REASON nReason)
{
  if ( CExtCharBag::autoUseItem(this, item, nReason) )
    return 1;
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::addItem(this, item, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
int32_t __cdecl CExtCharBag::HaveItemCount(
        CExtCharBag *const this,
        const ItemData *const data,
        bool IsBind,
        bool IsTimeLiness)
{
  Time_t endTime; // ebx
  Time_t v6; // ebx
  int32_t BagSize; // [rsp+24h] [rbp-1Ch]
  int32_t Count; // [rsp+28h] [rbp-18h]
  int32_t i; // [rsp+2Ch] [rbp-14h]

  BagSize = CExtCharBag::GetBagSize(this);
  Count = 0;
  for ( i = 0; i < BagSize; ++i )
  {
    if ( this->m_bagData[i].itemId == data->m_nId && this->m_bagData[i].itemClass == data->m_nClass )
    {
      if ( IsBind && (this->m_bagData[i].bind == 1 || this->m_bagData[i].bind == 2) )
      {
        if ( IsTimeLiness && (endTime = this->m_bagData[i].endTime, endTime <= Unit::getNow(this->m_pPlayer)) )
        {
          Count += this->m_bagData[i].itemCount;
        }
        else if ( !this->m_bagData[i].endTime )
        {
          Count += this->m_bagData[i].itemCount;
        }
      }
      else if ( !IsBind && !this->m_bagData[i].bind )
      {
        if ( IsTimeLiness && (v6 = this->m_bagData[i].endTime, v6 <= Unit::getNow(this->m_pPlayer)) )
        {
          Count += this->m_bagData[i].itemCount;
        }
        else if ( !this->m_bagData[i].endTime )
        {
          Count += this->m_bagData[i].itemCount;
        }
      }
    }
  }
  return Count;
}


#####################################
bool __cdecl CExtCharBag::addItem(CExtCharBag *const this, const MemChrBag *const item, ITEM_CHANGE_REASON nReason)
{
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v5; // rax
  int32_t v7; // eax
  MemChrBag bagSlot; // [rsp+20h] [rbp-70h] BYREF
  MemChrBag slotData; // [rsp+40h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+60h] [rbp-30h] BYREF
  int32_t __a; // [rsp+64h] [rbp-2Ch] BYREF
  int32_t nLayNum; // [rsp+68h] [rbp-28h]
  int32_t nBagSize; // [rsp+6Ch] [rbp-24h]
  int32_t needSlots; // [rsp+70h] [rbp-20h]
  int32_t slot; // [rsp+74h] [rbp-1Ch]
  int32_t nAddon; // [rsp+78h] [rbp-18h]
  int32_t i; // [rsp+7Ch] [rbp-14h]

  itemClass = item->itemClass;
  itemId = item->itemId;
  v5 = Answer::Singleton<CfgData>::instance();
  nLayNum = CfgData::getOverlay(v5, itemId, itemClass);
  if ( nLayNum <= 0 )
    return 0;
  nCount = item->itemCount;
  if ( nCount < 0 )
    return 0;
  if ( !nCount )
    return 1;
  nBagSize = CExtCharBag::GetBagSize(this);
  if ( nLayNum > 1 )
  {
    for ( slot = 0; slot < nBagSize; ++slot )
    {
      slotData = *CExtCharBag::GetSlotData(this, slot);
      if ( CExtCharBag::compairSlot(this, item, &slotData) )
      {
        __a = nLayNum - slotData.itemCount;
        nAddon = *std::min<int>(&__a, &nCount);
        if ( nAddon > 0 )
        {
          slotData.itemCount += nAddon;
          CExtCharBag::setSlotData(this, slot, &slotData, nReason, 0);
          nCount -= nAddon;
          if ( nCount <= 0 )
            return 1;
        }
      }
    }
  }
  memset(&bagSlot, 0, sizeof(bagSlot));
  if ( nCount % nLayNum )
    v7 = nCount / nLayNum + 1;
  else
    v7 = nCount / nLayNum;
  needSlots = v7;
  for ( i = 0; i < nBagSize; ++i )
  {
    bagSlot = *CExtCharBag::GetSlotData(this, i);
    if ( CExtCharBag::IsEmptySlot(this, &bagSlot) )
    {
      bagSlot = *(const MemChrBag *)item;
      if ( nCount <= nLayNum )
      {
        bagSlot.itemCount = nCount;
        CExtCharBag::setSlotData(this, i, &bagSlot, nReason, nCount);
        return 1;
      }
      bagSlot.itemCount = nLayNum;
      nCount -= nLayNum;
      CExtCharBag::setSlotData(this, i, &bagSlot, nReason, nLayNum);
    }
  }
  return 0;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, lst, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::removeItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  const ItemData *v4; // rdx
  std::_List_const_iterator<ItemData> eiter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_const_iterator<ItemData> iter; // [rsp+30h] [rbp-20h] BYREF

  iter._M_node = std::list<ItemData>::begin(lst)._M_node;
  eiter._M_node = std::list<ItemData>::end(lst)._M_node;
  while ( std::_List_const_iterator<ItemData>::operator!=(&iter, &eiter) )
  {
    v4 = std::_List_const_iterator<ItemData>::operator*(&iter);
    if ( !CExtCharBag::removeItem(this, vSlot, v4, nReason) )
      return 0;
    std::_List_const_iterator<ItemData>::operator++(&iter);
  }
  return 1;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, data, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::removeItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason)
{
  int v5; // edx
  int v6; // edx
  Time_t endTime; // ebx
  bool v8; // al
  int32_t v9; // eax
  int v10; // ebx
  EquipId_t srcId; // r12
  int8_t ConnId; // bl
  CEquipManager *v13; // rax
  MemChrBag bagSlot; // [rsp+20h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+40h] [rbp-30h]
  int32_t isize; // [rsp+44h] [rbp-2Ch]
  int32_t i; // [rsp+48h] [rbp-28h]
  int32_t nRemove; // [rsp+4Ch] [rbp-24h]

  nCount = data->m_nCount;
  if ( nCount <= 0 )
    return 0;
  isize = std::vector<int>::size(vSlot);
  for ( i = 0; i < isize; ++i )
  {
    v5 = *std::vector<int>::operator[](vSlot, i);
    if ( !CExtCharBag::IsSlotValid(this, v5) )
      break;
    v6 = *std::vector<int>::operator[](vSlot, i);
    bagSlot = *CExtCharBag::GetSlotData(this, v6);
    v8 = 0;
    if ( bagSlot.endTime > 0 )
    {
      if ( this->m_pPlayer )
      {
        endTime = bagSlot.endTime;
        if ( endTime <= Unit::getNow(this->m_pPlayer) )
          v8 = 1;
      }
    }
    if ( !v8 && CExtCharBag::compairItem(this, &bagSlot, data) )
    {
      v9 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
      nRemove = v9;
      bagSlot.itemCount -= v9;
      v10 = *std::vector<int>::operator[](vSlot, i);
      CExtCharBag::setSlotData(this, v10, &bagSlot, nReason, nRemove);
      if ( bagSlot.srcId > 0 && bagSlot.itemClass == 2 )
      {
        srcId = bagSlot.srcId;
        ConnId = Player::getConnId(this->m_pPlayer);
        v13 = Answer::Singleton<CEquipManager>::instance();
        CEquipManager::DeleteMemEquip(v13, ConnId, srcId, nReason);
      }
      nCount -= nRemove;
      if ( nCount <= 0 )
        return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, lst, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::RemoveCombiItem(
        CExtCharBag *const this,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeCombiItem(this, lst, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
void __cdecl CExtCharBag::GetDropItem(
        CExtCharBag *const this,
        Player *pKiller,
        PkDropRate *DropRate,
        int32_t nUsualRate,
        MemChrBagVector *const ItemVector,
        int32_t Mid)
{
  GameService *v6; // rax
  int32_t BagSize; // eax
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v9; // rax
  Answer::Random *v10; // rax
  int *v11; // rax
  int32_t v12; // ebx
  int32_t v13; // ebx
  MemChrBag BagDataTmp; // [rsp+40h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it; // [rsp+60h] [rbp-60h] BYREF
  int32_t i; // [rsp+6Ch] [rbp-54h] BYREF
  std::vector<int> UsualItemSlotVt; // [rsp+70h] [rbp-50h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+90h] [rbp-30h] BYREF
  int32_t DropUsualItemCount; // [rsp+9Ch] [rbp-24h]
  int32_t nDropUsual; // [rsp+A0h] [rbp-20h]
  int32_t nDropRate; // [rsp+A4h] [rbp-1Ch]
  int32_t nRand; // [rsp+A8h] [rbp-18h]
  int32_t DropCount; // [rsp+ACh] [rbp-14h]

  if ( DropRate )
  {
    if ( this->m_pPlayer )
    {
      v6 = Answer::Singleton<GameService>::instance();
      if ( GameService::getLine(v6) != 9 )
      {
        std::vector<int>::vector(&UsualItemSlotVt);
        for ( i = 0; ; ++i )
        {
          BagSize = CExtCharBag::GetBagSize(this);
          if ( BagSize <= i )
            break;
          if ( this->m_bagData[i].itemId > 0 && this->m_bagData[i].itemCount > 0 && !this->m_bagData[i].bind )
            std::vector<int>::push_back(&UsualItemSlotVt, &i);
        }
        DropUsualItemCount = 0;
        if ( std::vector<int>::size(&UsualItemSlotVt) )
        {
          DropUsualItemCount = DropRate->UsualCountRate * std::vector<int>::size(&UsualItemSlotVt) / 0x64;
          if ( DropUsualItemCount <= 0 )
            DropUsualItemCount = 1;
        }
        if ( DropUsualItemCount > 0 )
        {
          M_current = std::vector<int>::end(&UsualItemSlotVt)._M_current;
          v9._M_current = std::vector<int>::begin(&UsualItemSlotVt)._M_current;
          std::random_shuffle<__gnu_cxx::__normal_iterator<int *,std::vector<int>>>(
            v9,
            (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current);
          nDropUsual = 0;
          for ( it._M_current = std::vector<int>::begin(&UsualItemSlotVt)._M_current;
                ;
                __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it) )
          {
            __rhs._M_current = std::vector<int>::end(&UsualItemSlotVt)._M_current;
            if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it, &__rhs) )
              break;
            nDropRate = nUsualRate;
            v10 = Answer::Singleton<Answer::Random>::instance();
            nRand = Answer::Random::generate(v10, 0, 100);
            if ( nRand < nDropRate )
            {
              DropCount = 0;
              DropCount = DropRate->OverlayRate
                        * this->m_bagData[*__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it)].itemCount
                        / 100;
              if ( !DropCount )
                DropCount = 1;
              BagDataTmp = this->m_bagData[*__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it)];
              v11 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
              if ( this->m_bagData[*v11].itemCount - DropCount > 0 )
              {
                BagDataTmp.itemCount -= DropCount;
                v13 = *__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
                CExtCharBag::setSlotData(this, v13, &BagDataTmp, ITEM_CHANGE_REASON::ICR_DIE_DROP, 0);
              }
              else
              {
                v12 = *__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
                CExtCharBag::setSlotData(this, v12, &this->m_nullobj, ITEM_CHANGE_REASON::ICR_DIE_DROP, 0);
              }
              BagDataTmp.itemCount = DropCount;
              std::vector<MemChrBag>::push_back(ItemVector, &BagDataTmp);
            }
            if ( ++nDropUsual >= DropUsualItemCount )
              break;
          }
        }
        std::vector<int>::~vector(&UsualItemSlotVt);
      }
    }
  }
}


#####################################
bool __cdecl CExtCharBag::removeCombiItem(
        CExtCharBag *const this,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  const ItemData *v3; // rdx
  int32_t v4; // eax
  const ItemData *v5; // rdx
  int32_t v6; // eax
  MemChrBag bagSlot; // [rsp+20h] [rbp-60h] BYREF
  std::_List_const_iterator<ItemData> it; // [rsp+40h] [rbp-40h] BYREF
  std::_List_const_iterator<ItemData> __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+58h] [rbp-28h]
  int32_t nBagSize; // [rsp+5Ch] [rbp-24h]
  int32_t i; // [rsp+60h] [rbp-20h]
  int32_t nRemove; // [rsp+64h] [rbp-1Ch]
  int32_t i_0; // [rsp+68h] [rbp-18h]
  int32_t nRemove_0; // [rsp+6Ch] [rbp-14h]

  for ( it._M_node = std::list<ItemData>::begin(lst)._M_node; ; std::_List_const_iterator<ItemData>::operator++(&it) )
  {
    __x._M_node = std::list<ItemData>::end(lst)._M_node;
    if ( !std::_List_const_iterator<ItemData>::operator!=(&it, &__x) )
      break;
    nCount = std::_List_const_iterator<ItemData>::operator*(&it)->m_nCount;
    nBagSize = CExtCharBag::GetBagSize(this);
    for ( i = 0; i < nBagSize; ++i )
    {
      bagSlot = *CExtCharBag::GetSlotData(this, i);
      v3 = std::_List_const_iterator<ItemData>::operator*(&it);
      if ( CExtCharBag::compairItem(this, &bagSlot, v3) )
      {
        if ( bagSlot.bind )
        {
          v4 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
          nRemove = v4;
          bagSlot.itemCount -= v4;
          CExtCharBag::setSlotData(this, i, &bagSlot, nReason, v4);
          nCount -= nRemove;
          if ( nCount <= 0 )
            break;
        }
      }
    }
    if ( nCount > 0 )
    {
      for ( i_0 = 0; i_0 < nBagSize; ++i_0 )
      {
        bagSlot = *CExtCharBag::GetSlotData(this, i_0);
        v5 = std::_List_const_iterator<ItemData>::operator*(&it);
        if ( CExtCharBag::compairItem(this, &bagSlot, v5) && bagSlot.bind != 1 && bagSlot.bind != 2 )
        {
          v6 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
          nRemove_0 = v6;
          bagSlot.itemCount -= v6;
          CExtCharBag::setSlotData(this, i_0, &bagSlot, nReason, v6);
          nCount -= nRemove_0;
          if ( nCount <= 0 )
            break;
        }
      }
      if ( nCount > 0 )
        return 0;
    }
  }
  return 1;
}


#####################################
bool __cdecl CExtCharBag::removeItem(
        CExtCharBag *const this,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason)
{
  const ItemData *v3; // rcx
  std::_List_const_iterator<ItemData> eiter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_const_iterator<ItemData> iter; // [rsp+30h] [rbp-10h] BYREF

  iter._M_node = std::list<ItemData>::begin(lst)._M_node;
  eiter._M_node = std::list<ItemData>::end(lst)._M_node;
  while ( std::_List_const_iterator<ItemData>::operator!=(&iter, &eiter) )
  {
    v3 = std::_List_const_iterator<ItemData>::operator*(&iter);
    if ( !CExtCharBag::removeItem(this, v3, nReason) )
      return 0;
    std::_List_const_iterator<ItemData>::operator++(&iter);
  }
  return 1;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(CExtCharBag *const this, const ItemData *const data, ITEM_CHANGE_REASON nReason)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, data, nReason) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::removeItem(CExtCharBag *const this, const ItemData *const data, ITEM_CHANGE_REASON nReason)
{
  Time_t endTime; // ebx
  int32_t v6; // eax
  int32_t v7; // eax
  MemChrBag bagSlot; // [rsp+20h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+48h] [rbp-28h]
  int32_t nBagSize; // [rsp+4Ch] [rbp-24h]
  int32_t i; // [rsp+50h] [rbp-20h]
  int32_t nRemove; // [rsp+54h] [rbp-1Ch]
  int32_t i_0; // [rsp+58h] [rbp-18h]
  int32_t nRemove_0; // [rsp+5Ch] [rbp-14h]

  nCount = data->m_nCount;
  nBagSize = CExtCharBag::GetBagSize(this);
  if ( nCount <= 0 )
    return 0;
  for ( i = 0; i < nBagSize; ++i )
  {
    bagSlot = *CExtCharBag::GetSlotData(this, i);
    if ( bagSlot.endTime > 0 && CExtCharBag::compairItem(this, &bagSlot, data) )
    {
      if ( !this->m_pPlayer || (endTime = bagSlot.endTime, endTime > Unit::getNow(this->m_pPlayer)) )
      {
        v6 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
        nRemove = v6;
        bagSlot.itemCount -= v6;
        CExtCharBag::setSlotData(this, i, &bagSlot, nReason, v6);
        nCount -= nRemove;
        if ( nCount <= 0 )
          return 1;
      }
    }
  }
  for ( i_0 = 0; i_0 < nBagSize; ++i_0 )
  {
    bagSlot = *CExtCharBag::GetSlotData(this, i_0);
    if ( bagSlot.endTime <= 0 && CExtCharBag::compairItem(this, &bagSlot, data) )
    {
      v7 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
      nRemove_0 = v7;
      bagSlot.itemCount -= v7;
      CExtCharBag::setSlotData(this, i_0, &bagSlot, nReason, v7);
      nCount -= nRemove_0;
      if ( nCount <= 0 )
        return 1;
    }
  }
  return 0;
}


#####################################
void __cdecl CExtCharBag::backUpBagData(CExtCharBag *const this)
{
  memcpy(this->m_bagBackUp, this->m_bagData, sizeof(this->m_bagBackUp));
  CExtCharBag::saveItemChangeLog(this);
}


#####################################
void __cdecl CExtCharBag::recoverBagData(CExtCharBag *const this)
{
  memcpy(this->m_bagData, this->m_bagBackUp, sizeof(this->m_bagData));
  CExtCharBag::clearItemChangeLog(this);
}


#####################################
void __cdecl CExtCharBag::addItemChangeLog(
        CExtCharBag *const this,
        int32_t nReason,
        int32_t nId,
        int8_t nClass,
        int64_t nSrcId,
        int32_t nCount,
        int8_t nFlag,
        int32_t AllCount)
{
  const char *v8; // rax
  LogItemChange itemLog; // [rsp+30h] [rbp-70h] BYREF
  std::string v14; // [rsp+80h] [rbp-20h] BYREF

  if ( this->m_pPlayer && nReason > 0 )
  {
    memset(&itemLog, 0, sizeof(itemLog));
    itemLog.cid = Player::getCid(this->m_pPlayer);
    itemLog.flag = nFlag;
    itemLog.reason = nReason;
    itemLog.id = nId;
    itemLog.itemClass = nClass;
    itemLog.count = nCount;
    itemLog.time = Unit::getNow(this->m_pPlayer);
    itemLog.srcId = nSrcId;
    if ( AllCount <= 0 )
      itemLog.allCount = CExtCharBag::GetItemCount(this, nId, nClass);
    else
      itemLog.allCount = AllCount;
    Player::getName((const Player *const)&v14);
    v8 = (const char *)std::string::c_str(&v14);
    snprintf(itemLog.name, 0x1Eu, v8);
    std::string::~string(&v14);
    std::list<LogItemChange>::push_back(&this->m_lstItemChangeLog, &itemLog);
  }
}


#####################################
void __cdecl CExtCharBag::saveItemChangeLog(CExtCharBag *const this)
{
  LogItemChange *v1; // r12
  int8_t ConnId; // bl
  DBService *v3; // rax
  int8_t v5; // bl
  int32_t v6; // ecx
  int32_t ItemCount; // r12d
  int32_t v8; // r13d
  int v9; // ebx
  int32_t v10; // r15d
  int32_t v11; // r14d
  LogItemChange *v12; // rax
  DBService *v13; // rax
  int32_t v14; // r14d
  int32_t MapId; // r13d
  int v16; // r12d
  int8_t v17; // bl
  int32_t v18; // ecx
  int32_t v19; // ebx
  int32_t v20; // r15d
  LogItemChange *v21; // rax
  DBService *v22; // rax
  int32_t reason; // r12d
  int32_t count; // ebx
  int32_t id; // r14d
  int itemClass; // r13d
  LogItemChange *v27; // rax
  DBService *v28; // rax
  int32_t v29; // ebx
  int32_t v30; // r13d
  int32_t v31; // r12d
  LogItemChange *v32; // rax
  int8_t v33; // bl
  DBService *v34; // rax
  int v35; // r13d
  int32_t v36; // r12d
  int32_t v37; // ebx
  LogItemChange *v38; // rax
  std::_Ios_Openmode v39; // eax
  unsigned int v40; // ebx
  __int64 v41; // rax
  DBService *v42; // rax
  int32_t v43; // [rsp+24h] [rbp-12DCh]
  char LogString[4096]; // [rsp+30h] [rbp-12D0h] BYREF
  _BYTE v45[16]; // [rsp+1030h] [rbp-2D0h] BYREF
  __int64 v46; // [rsp+1040h] [rbp-2C0h] BYREF
  item_log stu; // [rsp+11A0h] [rbp-160h] BYREF
  Log360 Stu; // [rsp+11F0h] [rbp-110h] BYREF
  std::_List_iterator<LogItemChange> eiter; // [rsp+1220h] [rbp-E0h] BYREF
  std::_List_iterator<LogItemChange> iter; // [rsp+1230h] [rbp-D0h] BYREF
  _BYTE v51[16]; // [rsp+1240h] [rbp-C0h] BYREF
  _BYTE v52[16]; // [rsp+1250h] [rbp-B0h] BYREF
  _BYTE v53[16]; // [rsp+1260h] [rbp-A0h] BYREF
  _BYTE v54[16]; // [rsp+1270h] [rbp-90h] BYREF
  int8_t v55[16]; // [rsp+1280h] [rbp-80h] BYREF
  int8_t ItemType[16]; // [rsp+1290h] [rbp-70h] BYREF
  _BYTE v57[16]; // [rsp+12A0h] [rbp-60h] BYREF
  _BYTE v58[16]; // [rsp+12B0h] [rbp-50h] BYREF
  _BYTE v59[64]; // [rsp+12C0h] [rbp-40h] BYREF

  iter._M_node = std::list<LogItemChange>::begin(&this->m_lstItemChangeLog)._M_node;
  eiter._M_node = std::list<LogItemChange>::end(&this->m_lstItemChangeLog)._M_node;
  while ( std::_List_iterator<LogItemChange>::operator!=(&iter, &eiter) )
  {
    v1 = std::_List_iterator<LogItemChange>::operator*(&iter);
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<DBService>::instance();
    DBService::insertItemChange(v3, ConnId, v1);
    if ( std::_List_iterator<LogItemChange>::operator->(&iter)->itemClass == 2 )
    {
      memset(&Stu, 0, sizeof(Stu));
      std::string::string(&Stu.Interface);
      std::string::string(&Stu.passport);
      std::string::string(&Stu.LogString);
      std::string::operator=(&Stu, "equip");
      Stu.UseSid = Player::getSid(this->m_pPlayer);
      Player::GetPassport((Player *const)v53);
      std::string::operator=(&Stu.passport, v53);
      std::string::~string(v53);
      Stu.Cid = Player::getCid(this->m_pPlayer);
      memset(LogString, 0, sizeof(LogString));
      reason = std::_List_iterator<LogItemChange>::operator->(&iter)->reason;
      count = std::_List_iterator<LogItemChange>::operator->(&iter)->count;
      id = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
      itemClass = std::_List_iterator<LogItemChange>::operator->(&iter)->itemClass;
      v27 = std::_List_iterator<LogItemChange>::operator->(&iter);
      snprintf(
        LogString,
        0xFFFu,
        "equipid=%lld&itemid=%d:%d&amount=%d&opid=%d",
        v27->srcId,
        itemClass,
        id,
        count,
        reason);
      std::string::operator=(&Stu.LogString, LogString);
      LOBYTE(count) = Player::getConnId(this->m_pPlayer);
      v28 = Answer::Singleton<DBService>::instance();
      DBService::log360(v28, count, &Stu);
      Log360::~Log360(&Stu);
    }
    else
    {
      if ( std::_List_iterator<LogItemChange>::operator->(&iter)->reason != 134
        && std::_List_iterator<LogItemChange>::operator->(&iter)->flag == 1 )
      {
        memset(&Stu, 0, sizeof(Stu));
        std::string::string(&Stu.Interface);
        std::string::string(&Stu.passport);
        std::string::string(&Stu.LogString);
        std::string::operator=(&Stu, "item_income");
        Stu.UseSid = Player::getSid(this->m_pPlayer);
        Player::GetPassport((Player *const)v51);
        std::string::operator=(&Stu.passport, v51);
        std::string::~string(v51);
        Stu.Cid = Player::getCid(this->m_pPlayer);
        memset(LogString, 0, sizeof(LogString));
        v5 = std::_List_iterator<LogItemChange>::operator->(&iter)->itemClass;
        v6 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
        ItemCount = CExtCharBag::GetItemCount(this, v6, v5);
        v8 = std::_List_iterator<LogItemChange>::operator->(&iter)->reason;
        v9 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
        v10 = std::_List_iterator<LogItemChange>::operator->(&iter)->count;
        v11 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
        v12 = std::_List_iterator<LogItemChange>::operator->(&iter);
        snprintf(
          LogString,
          0xFFFu,
          "itemid=%d:%d&amount=%d&level=%d&reason=%d&mode=u&remain=%d",
          v12->itemClass,
          v11,
          v10,
          v9,
          v8,
          ItemCount);
        std::string::operator=(&Stu.LogString, LogString);
        LOBYTE(v9) = Player::getConnId(this->m_pPlayer);
        v13 = Answer::Singleton<DBService>::instance();
        DBService::log360(v13, v9, &Stu);
        Log360::~Log360(&Stu);
      }
      if ( std::_List_iterator<LogItemChange>::operator->(&iter)->flag == 2 )
      {
        memset(&Stu, 0, sizeof(Stu));
        std::string::string(&Stu.Interface);
        std::string::string(&Stu.passport);
        std::string::string(&Stu.LogString);
        std::string::operator=(&Stu, "item_use");
        Stu.UseSid = Player::getSid(this->m_pPlayer);
        Player::GetPassport((Player *const)v52);
        std::string::operator=(&Stu.passport, v52);
        std::string::~string(v52);
        Stu.Cid = Player::getCid(this->m_pPlayer);
        memset(LogString, 0, sizeof(LogString));
        v14 = std::_List_iterator<LogItemChange>::operator->(&iter)->reason;
        MapId = StaticObj::getMapId(this->m_pPlayer);
        v16 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
        v17 = std::_List_iterator<LogItemChange>::operator->(&iter)->itemClass;
        v18 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
        v19 = CExtCharBag::GetItemCount(this, v18, v17);
        v43 = std::_List_iterator<LogItemChange>::operator->(&iter)->count;
        v20 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
        v21 = std::_List_iterator<LogItemChange>::operator->(&iter);
        snprintf(
          LogString,
          0xFFFu,
          "itemid=%d:%d&amount=%d&remain=%d&type=1&level=%d&map_id=%d&mode=u&reason=%d&mode=u",
          v21->itemClass,
          v20,
          v43,
          v19,
          v16,
          MapId,
          v14);
        std::string::operator=(&Stu.LogString, LogString);
        LOBYTE(v19) = Player::getConnId(this->m_pPlayer);
        v22 = Answer::Singleton<DBService>::instance();
        DBService::log360(v22, v19, &Stu);
        Log360::~Log360(&Stu);
      }
    }
    if ( std::_List_iterator<LogItemChange>::operator->(&iter)->flag == 1 )
    {
      memset(&Stu, 0, sizeof(Stu));
      std::string::string(&Stu.Interface);
      std::string::string(&Stu.passport);
      std::string::string(&Stu.LogString);
      std::string::operator=(&Stu, "item_log");
      Stu.UseSid = Player::getSid(this->m_pPlayer);
      Player::GetPassport((Player *const)v54);
      std::string::operator=(&Stu.passport, v54);
      std::string::~string(v54);
      Stu.Cid = Player::getCid(this->m_pPlayer);
      memset(LogString, 0, sizeof(LogString));
      v29 = std::_List_iterator<LogItemChange>::operator->(&iter)->count;
      v30 = std::_List_iterator<LogItemChange>::operator->(&iter)->reason;
      v31 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
      v32 = std::_List_iterator<LogItemChange>::operator->(&iter);
      snprintf(LogString, 0xFFFu, "itemid=%d:%d&opid=%d&amount=%d", v32->itemClass, v31, v30, v29);
    }
    else
    {
      memset(&Stu, 0, sizeof(Stu));
      std::string::string(&Stu.Interface);
      std::string::string(&Stu.passport);
      std::string::string(&Stu.LogString);
      std::string::operator=(&Stu, "item_log");
      Stu.UseSid = Player::getSid(this->m_pPlayer);
      Player::GetPassport((Player *const)v55);
      std::string::operator=(&Stu.passport, v55);
      std::string::~string(v55);
      Stu.Cid = Player::getCid(this->m_pPlayer);
      memset(LogString, 0, sizeof(LogString));
      v35 = -std::_List_iterator<LogItemChange>::operator->(&iter)->count;
      v36 = std::_List_iterator<LogItemChange>::operator->(&iter)->reason;
      v37 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
      v38 = std::_List_iterator<LogItemChange>::operator->(&iter);
      snprintf(LogString, 0xFFFu, "itemid=%d:%d&opid=%d&amount=%d", v38->itemClass, v37, v36, v35);
    }
    std::string::operator=(&Stu.LogString, LogString);
    v33 = Player::getConnId(this->m_pPlayer);
    v34 = Answer::Singleton<DBService>::instance();
    DBService::log360(v34, v33, &Stu);
    Log360::~Log360(&Stu);
    v39 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
      v45,
      (unsigned int)v39);
    v40 = std::_List_iterator<LogItemChange>::operator->(&iter)->id;
    std::_List_iterator<LogItemChange>::operator->(&iter);
    GetLogItemFront((int8_t)ItemType);
    v41 = std::operator<<<char>(&v46, ItemType);
    std::ostream::operator<<(v41, v40);
    std::string::~string(ItemType);
    item_log::item_log(&stu);
    stu.log_Sid = Player::getSid(this->m_pPlayer);
    stu.log_time = Unit::getNow(this->m_pPlayer);
    Player::GetPassport((Player *const)v57);
    std::string::operator=(&stu.passport, v57);
    std::string::~string(v57);
    stu.cid = Player::getCid(this->m_pPlayer);
    Player::getName((const Player *const)v58);
    std::string::operator=(&stu.name, v58);
    std::string::~string(v58);
    stu.op_time = Unit::getNow(this->m_pPlayer);
    stu.flag = std::_List_iterator<LogItemChange>::operator->(&iter)->flag != 1;
    stu.opway = std::_List_iterator<LogItemChange>::operator->(&iter)->reason;
    stu.count = std::_List_iterator<LogItemChange>::operator->(&iter)->count;
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(v59, v45);
    std::string::operator=(&stu.ItemId, v59);
    std::string::~string(v59);
    stu.level = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    LOBYTE(v40) = Player::getConnId(this->m_pPlayer);
    v42 = Answer::Singleton<DBService>::instance();
    DBService::AddPlatformLog(v42, v40, PLATFORM_LOG_DATA_TYPE::PLDT_ITEM, &stu);
    item_log::~item_log(&stu);
    std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v45);
    std::_List_iterator<LogItemChange>::operator++(&iter);
  }
  std::list<LogItemChange>::clear(&this->m_lstItemChangeLog);
}


#####################################
bool __cdecl CExtCharBag::compairItem(
        CExtCharBag *const this,
        const MemChrBag *const bagSlot,
        const ItemData *const data)
{
  return bagSlot->itemClass == data->m_nClass && data->m_nId == bagSlot->itemId;
}


#####################################
bool __cdecl CExtCharBag::compairSlot(
        CExtCharBag *const this,
        const MemChrBag *const left,
        const MemChrBag *const right)
{
  if ( left->itemId != right->itemId )
    return 0;
  if ( left->srcId != right->srcId )
    return 0;
  if ( left->itemClass != right->itemClass )
    return 0;
  if ( left->bind == right->bind )
    return left->endTime == right->endTime;
  return 0;
}


#####################################
void __cdecl CExtCharBag::addDirty(CExtCharBag *const this, int32_t nSlot, int32_t reason, bool bNeedCreate)
{
  CExtCharBag::WaitCreate stu; // [rsp+20h] [rbp-40h] BYREF
  CExtCharBag::BagDirty dirty; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<CExtCharBag::BagDirty> eiter; // [rsp+40h] [rbp-20h] BYREF
  std::_List_iterator<CExtCharBag::BagDirty> iter; // [rsp+50h] [rbp-10h] BYREF

  if ( bNeedCreate )
  {
    stu.nSlot = nSlot;
    stu.nReason = reason;
    std::list<CExtCharBag::WaitCreate>::push_back(&this->m_lstWaitCreate, &stu);
  }
  iter._M_node = std::list<CExtCharBag::BagDirty>::begin(&this->m_lstDirty)._M_node;
  eiter._M_node = std::list<CExtCharBag::BagDirty>::end(&this->m_lstDirty)._M_node;
  while ( std::_List_iterator<CExtCharBag::BagDirty>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_iterator<CExtCharBag::BagDirty>::operator->(&iter)->nSlot == nSlot )
      return;
    std::_List_iterator<CExtCharBag::BagDirty>::operator++(&iter);
  }
  dirty.nSlot = nSlot;
  *(_DWORD *)&dirty.bChange = reason > 0;
  std::list<CExtCharBag::BagDirty>::push_back(&this->m_lstDirty, &dirty);
}


#####################################
void __cdecl CExtCharBag::ForceSendDirty(CExtCharBag *const this)
{
  if ( CExtCharBag::sendDirty(this) )
    CExtCharBag::clearDirty(this);
}


#####################################
void __cdecl CExtCharBag::checkDirty(CExtCharBag *const this)
{
  if ( CExtCharBag::sendDirty(this) )
    CExtCharBag::clearDirty(this);
}


#####################################
void __cdecl CExtCharBag::checkCreate(CExtCharBag *const this)
{
  int32_t Now; // ebx
  int Cid; // eax
  CharId_t nCreaterId; // rbx
  int32_t Sid; // r13d
  int32_t itemId; // r14d
  int8_t ConnId; // r12
  CEquipManager *v8; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v10; // rax
  MemEquip equip; // [rsp+50h] [rbp-E0h] BYREF
  MemChrBag tSlot; // [rsp+90h] [rbp-A0h] BYREF
  std::_List_iterator<CExtCharBag::WaitCreate> iter; // [rsp+B0h] [rbp-80h] BYREF
  MemEquipVector vEquip; // [rsp+C0h] [rbp-70h] BYREF
  std::_List_iterator<CExtCharBag::WaitCreate> __x; // [rsp+E0h] [rbp-50h] BYREF
  std::string p_name; // [rsp+F0h] [rbp-40h] BYREF
  int32_t nMaxSize; // [rsp+FCh] [rbp-34h]
  int32_t nSlot; // [rsp+100h] [rbp-30h]
  int32_t nReason; // [rsp+104h] [rbp-2Ch]
  const MemChrBag *bagSlot; // [rsp+108h] [rbp-28h]

  if ( this->m_pPlayer && !std::list<CExtCharBag::WaitCreate>::empty(&this->m_lstWaitCreate) )
  {
    nMaxSize = std::list<CExtCharBag::WaitCreate>::size(&this->m_lstWaitCreate);
    std::vector<MemEquip>::vector(&vEquip);
    std::vector<MemEquip>::reserve(&vEquip, nMaxSize);
    for ( iter._M_node = std::list<CExtCharBag::WaitCreate>::begin(&this->m_lstWaitCreate)._M_node;
          ;
          std::_List_iterator<CExtCharBag::WaitCreate>::operator++(&iter) )
    {
      __x._M_node = std::list<CExtCharBag::WaitCreate>::end(&this->m_lstWaitCreate)._M_node;
      if ( !std::_List_iterator<CExtCharBag::WaitCreate>::operator!=(&iter, &__x) )
        break;
      nSlot = std::_List_iterator<CExtCharBag::WaitCreate>::operator->(&iter)->nSlot;
      nReason = std::_List_iterator<CExtCharBag::WaitCreate>::operator->(&iter)->nReason;
      bagSlot = CExtCharBag::GetSlotData(this, nSlot);
      if ( bagSlot->srcId <= 0 )
      {
        if ( bagSlot->itemClass == 2 )
        {
          Player::getName((const Player *const)&p_name);
          nCreaterId = Player::getCid(this->m_pPlayer);
          Sid = Player::getSid(this->m_pPlayer);
          itemId = bagSlot->itemId;
          ConnId = Player::getConnId(this->m_pPlayer);
          v8 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v8, ConnId, nReason, itemId, Sid, nCreaterId, &p_name, 0, 0, 0, 0, 0);
          std::string::~string(&p_name);
          memset(&tSlot, 0, sizeof(tSlot));
          if ( equip.id > 0 )
          {
            *(_QWORD *)&tSlot.itemId = *(_QWORD *)&bagSlot->itemId;
            *(_QWORD *)&tSlot.itemCount = *(_QWORD *)&bagSlot->itemCount;
            *(_QWORD *)&tSlot.endTime = *(_QWORD *)&bagSlot->endTime;
            tSlot.srcId = equip.id;
            std::vector<MemEquip>::push_back(&vEquip, &equip);
          }
          CExtCharBag::setSlotData(this, nSlot, &tSlot, ITEM_CHANGE_REASON::ICR_NONE, 0);
          MemEquip::~MemEquip(&equip);
        }
      }
      else
      {
        Now = Unit::getNow(this->m_pPlayer);
        Cid = Player::getCid(this->m_pPlayer);
        Answer::Logger::print(
          Answer::LogLevel::LOG_LEVEL_ERROR,
          "CExtCharBag::checkCreate() create twice! id=%d,class=%d,srcid=%d,owner=%d,time=%d",
          bagSlot->itemId,
          bagSlot->itemClass,
          bagSlot->srcId,
          Cid,
          Now);
      }
    }
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v10 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v10, m_pPlayer, &vEquip);
    }
    std::list<CExtCharBag::WaitCreate>::clear(&this->m_lstWaitCreate);
    std::vector<MemEquip>::~vector(&vEquip);
  }
}


#####################################
bool __cdecl CExtCharBag::sendDirty(CExtCharBag *const this)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  int8_t bChange; // al
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::_List_iterator<CExtCharBag::BagDirty> eiter; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<CExtCharBag::BagDirty> iter; // [rsp+20h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-30h]
  uint32_t nOffSet; // [rsp+38h] [rbp-28h]
  int32_t nCount; // [rsp+3Ch] [rbp-24h]
  uint32_t endOffSet; // [rsp+40h] [rbp-20h]
  int32_t nSlot; // [rsp+44h] [rbp-1Ch]
  const MemChrBag *tSlot; // [rsp+48h] [rbp-18h]

  if ( !this->m_pPlayer || std::list<CExtCharBag::BagDirty>::empty(&this->m_lstDirty) )
    return 0;
  ConnId = Player::getConnId(this->m_pPlayer);
  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DB7u);
  if ( !packet )
    return 0;
  Answer::NetPacket::writeInt8(packet, 1);
  nOffSet = Answer::NetPacket::getWOffset(packet);
  nCount = 0;
  Answer::NetPacket::writeInt32(packet, 0);
  iter._M_node = std::list<CExtCharBag::BagDirty>::begin(&this->m_lstDirty)._M_node;
  eiter._M_node = std::list<CExtCharBag::BagDirty>::end(&this->m_lstDirty)._M_node;
  while ( std::_List_iterator<CExtCharBag::BagDirty>::operator!=(&iter, &eiter) )
  {
    bChange = std::_List_iterator<CExtCharBag::BagDirty>::operator->(&iter)->bChange;
    Answer::NetPacket::writeInt8(packet, bChange);
    nSlot = std::_List_iterator<CExtCharBag::BagDirty>::operator->(&iter)->nSlot;
    tSlot = CExtCharBag::GetSlotData(this, nSlot);
    Answer::NetPacket::writeInt32(packet, nSlot);
    Answer::NetPacket::writeInt32(packet, tSlot->itemId);
    Answer::NetPacket::writeInt8(packet, tSlot->itemClass);
    Answer::NetPacket::writeInt32(packet, tSlot->itemCount);
    Answer::NetPacket::writeInt8(packet, tSlot->bind);
    Answer::NetPacket::writeInt32(packet, tSlot->endTime);
    Answer::NetPacket::writeInt64(packet, tSlot->srcId);
    ++nCount;
    std::_List_iterator<CExtCharBag::BagDirty>::operator++(&iter);
  }
  endOffSet = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setWOffset(packet, nOffSet);
  Answer::NetPacket::writeInt32(packet, nCount);
  Answer::NetPacket::setWOffset(packet, endOffSet);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  v8 = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::sendPacketTo(v9, v8, GateIndex, packet);
  return 1;
}


#####################################
void __cdecl CExtCharBag::sendUseBroadcast(
        CExtCharBag *const this,
        int32_t nBroadcast,
        const std::string *p_name,
        CharId_t cid,
        int32_t nItemId)
{
  int8_t ConnId; // bl
  GameService *v6; // rax
  uint32_t WOffset; // edx
  int8_t v8; // bl
  GameService *v9; // rax
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v6 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, nBroadcast);
    Answer::NetPacket::writeUTF8(packet, p_name);
    Answer::NetPacket::writeInt64(packet, cid);
    Answer::NetPacket::writeInt32(packet, nItemId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v9, v8, packet);
  }
}


#####################################
bool __cdecl CExtCharBag::autoUseItem(CExtCharBag *const this, const MemChrBag *const item, ITEM_CHANGE_REASON nReason)
{
  int32_t v4; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int32_t itemId; // ebx
  CfgData *v7; // rax
  int32_t type; // eax
  Player *m_pPlayer; // r13
  int32_t v10; // ebx
  ItemEffectManager *v11; // rax
  int32_t ItemCount; // [rsp+28h] [rbp-38h] BYREF
  int32_t nCount; // [rsp+2Ch] [rbp-34h]
  CURRENCY_TYPE ctype; // [rsp+30h] [rbp-30h]
  CURRENCY_CHANGE_REASON nCCReason; // [rsp+34h] [rbp-2Ch]
  CfgItem *pCfgItem; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer )
    return 0;
  nCount = item->itemCount;
  if ( nCount <= 0 )
    return 0;
  if ( item->itemClass == 4 )
  {
    if ( item->itemId == 6 )
    {
      v4 = item->itemCount;
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::AddLimitCount(OperateLimit, 37209, v4);
      return 1;
    }
    else
    {
      ctype = TranseCurrencyType((CURRENCY_ITEM_ID)item->itemId);
      if ( ctype == CURRENCY_TYPE::CURRENCY_INVALID )
      {
        return 0;
      }
      else
      {
        nCCReason = CURRENCY_CHANGE_REASON::MCR_AUTO_USE;
        switch ( nReason )
        {
          case ITEM_CHANGE_REASON::ICR_PICK:
            nCCReason = CURRENCY_CHANGE_REASON::MCR_PICK_CURRENCY_ITEM;
            break;
          case ITEM_CHANGE_REASON::ICR_MAIL:
          case ITEM_CHANGE_REASON::ICR_AUCTION_BACK:
            nCCReason = CURRENCY_CHANGE_REASON::MCR_MAIL_CURRENCY_ITEM;
            break;
          case ITEM_CHANGE_REASON::ICR_CROSS_DRAW_REWARD:
            nCCReason = CURRENCY_CHANGE_REASON::MCR_CROSS_DRAW_REWARD;
            break;
        }
        return Player::AddCurrency(this->m_pPlayer, ctype, nCount, nCCReason, 0);
      }
    }
  }
  else if ( item->itemClass == 1 )
  {
    itemId = item->itemId;
    v7 = Answer::Singleton<CfgData>::instance();
    pCfgItem = CfgData::getItem(v7, itemId);
    if ( pCfgItem )
    {
      type = pCfgItem->type;
      if ( type == 1 || type == 86 )
      {
        ItemCount = item->itemCount;
        m_pPlayer = this->m_pPlayer;
        v10 = item->itemId;
        v11 = Answer::Singleton<ItemEffectManager>::instance();
        ItemEffectManager::effect(v11, v10, m_pPlayer, m_pPlayer, &ItemCount);
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}


#####################################
bool __cdecl CExtCharBag::isAutoUseItem(const CExtCharBag *const this, const MemChrBag *const item)
{
  int32_t itemId; // ebx
  CfgData *v4; // rax
  int32_t type; // eax
  CfgItem *pCfgItem; // [rsp+18h] [rbp-18h]

  if ( item->itemClass == 4 )
    return 1;
  if ( item->itemClass != 1 )
    return 0;
  itemId = item->itemId;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgItem = CfgData::getItem(v4, itemId);
  if ( !pCfgItem )
    return 0;
  type = pCfgItem->type;
  return type == 1 || type == 86;
}


#####################################
void __cdecl CExtCharBag::OnDaySwitch(CExtCharBag *const this, int32_t nDiffDays)
{
  std::map<int,int>::clear(&this->m_ItemLimit);
  CExtCharBag::SendLimitCount(this);
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason,
        int32_t *const BindCount,
        int32_t *const UnBindCount)
{
  const ItemData *v5; // rbx
  std::_List_const_iterator<ItemData> iter; // [rsp+30h] [rbp-30h] BYREF
  std::_List_const_iterator<ItemData> __x; // [rsp+40h] [rbp-20h] BYREF

  CExtCharBag::backUpBagData(this);
  for ( iter._M_node = std::list<ItemData>::begin(lst)._M_node; ; std::_List_const_iterator<ItemData>::operator++(&iter) )
  {
    __x._M_node = std::list<ItemData>::end(lst)._M_node;
    if ( !std::_List_const_iterator<ItemData>::operator!=(&iter, &__x) )
      break;
    v5 = std::_List_const_iterator<ItemData>::operator*(&iter);
    if ( !CExtCharBag::removeItem(this, v5, nReason, BindCount, UnBindCount) )
    {
      CExtCharBag::recoverBagData(this);
      return 0;
    }
  }
  CExtCharBag::saveItemChangeLog(this);
  return 1;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason,
        int32_t *const BindCount,
        int32_t *const UnBindCount)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, data, nReason, BindCount, UnBindCount) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::removeItem(
        CExtCharBag *const this,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason,
        int32_t *const BindCount,
        int32_t *const UnBindCount)
{
  Time_t endTime; // ebx
  bool v7; // al
  int32_t v8; // eax
  Time_t v9; // ebx
  bool v10; // al
  int32_t v11; // eax
  MemChrBag bagSlot; // [rsp+30h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+58h] [rbp-28h]
  int32_t nBagSize; // [rsp+5Ch] [rbp-24h]
  int32_t i; // [rsp+60h] [rbp-20h]
  int32_t nRemove; // [rsp+64h] [rbp-1Ch]
  int32_t j; // [rsp+68h] [rbp-18h]
  int32_t nRemove_0; // [rsp+6Ch] [rbp-14h]

  nCount = data->m_nCount;
  nBagSize = CExtCharBag::GetBagSize(this);
  if ( nCount <= 0 )
    return 0;
  for ( i = 0; i < nBagSize; ++i )
  {
    bagSlot = *CExtCharBag::GetSlotData(this, i);
    v7 = 0;
    if ( bagSlot.endTime > 0 )
    {
      if ( this->m_pPlayer )
      {
        endTime = bagSlot.endTime;
        if ( endTime <= Unit::getNow(this->m_pPlayer) )
          v7 = 1;
      }
    }
    if ( !v7 && CExtCharBag::compairItem(this, &bagSlot, data) && bagSlot.bind == 1 )
    {
      v8 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
      nRemove = v8;
      bagSlot.itemCount -= v8;
      *BindCount += v8;
      CExtCharBag::setSlotData(this, i, &bagSlot, nReason, nRemove);
      nCount -= nRemove;
      if ( nCount <= 0 )
        return 1;
    }
  }
  for ( j = 0; j < nBagSize; ++j )
  {
    bagSlot = *CExtCharBag::GetSlotData(this, j);
    v10 = 0;
    if ( bagSlot.endTime > 0 )
    {
      if ( this->m_pPlayer )
      {
        v9 = bagSlot.endTime;
        if ( v9 <= Unit::getNow(this->m_pPlayer) )
          v10 = 1;
      }
    }
    if ( !v10 && CExtCharBag::compairItem(this, &bagSlot, data) && !bagSlot.bind )
    {
      v11 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
      nRemove_0 = v11;
      bagSlot.itemCount -= v11;
      *UnBindCount += v11;
      CExtCharBag::setSlotData(this, j, &bagSlot, nReason, nRemove_0);
      nCount -= nRemove_0;
      if ( nCount <= 0 )
        return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemDataList *const lst,
        ITEM_CHANGE_REASON nReason,
        int32_t *const BindCount,
        int32_t *const UnBindCount)
{
  const ItemData *v6; // rdx
  std::_List_const_iterator<ItemData> iter; // [rsp+30h] [rbp-30h] BYREF
  std::_List_const_iterator<ItemData> __x; // [rsp+40h] [rbp-20h] BYREF

  CExtCharBag::backUpBagData(this);
  for ( iter._M_node = std::list<ItemData>::begin(lst)._M_node; ; std::_List_const_iterator<ItemData>::operator++(&iter) )
  {
    __x._M_node = std::list<ItemData>::end(lst)._M_node;
    if ( !std::_List_const_iterator<ItemData>::operator!=(&iter, &__x) )
      break;
    v6 = std::_List_const_iterator<ItemData>::operator*(&iter);
    if ( !CExtCharBag::removeItem(this, vSlot, v6, nReason, BindCount, UnBindCount) )
    {
      CExtCharBag::recoverBagData(this);
      return 0;
    }
  }
  CExtCharBag::saveItemChangeLog(this);
  return 1;
}


#####################################
bool __cdecl CExtCharBag::RemoveItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason,
        int32_t *const BindCount,
        int32_t *const UnBindCount)
{
  CExtCharBag::backUpBagData(this);
  if ( !CExtCharBag::removeItem(this, vSlot, data, nReason, BindCount, UnBindCount) )
  {
    CExtCharBag::recoverBagData(this);
    return 0;
  }
  else
  {
    CExtCharBag::saveItemChangeLog(this);
    return 1;
  }
}


#####################################
bool __cdecl CExtCharBag::removeItem(
        CExtCharBag *const this,
        const Int32Vector *const vSlot,
        const ItemData *const data,
        ITEM_CHANGE_REASON nReason,
        int32_t *const BindCount,
        int32_t *const UnBindCount)
{
  int v7; // edx
  int v8; // edx
  Time_t endTime; // ebx
  bool v10; // al
  int32_t v11; // eax
  int v12; // ebx
  int v13; // edx
  int v14; // edx
  Time_t v15; // ebx
  bool v16; // al
  int32_t v17; // eax
  int v18; // ebx
  MemChrBag bagSlot; // [rsp+30h] [rbp-50h] BYREF
  int32_t nCount; // [rsp+58h] [rbp-28h]
  int32_t isize; // [rsp+5Ch] [rbp-24h]
  int32_t i; // [rsp+60h] [rbp-20h]
  int32_t nRemove; // [rsp+64h] [rbp-1Ch]
  int32_t i_0; // [rsp+68h] [rbp-18h]
  int32_t nRemove_0; // [rsp+6Ch] [rbp-14h]

  nCount = data->m_nCount;
  if ( nCount <= 0 )
    return 0;
  isize = std::vector<int>::size(vSlot);
  for ( i = 0; i < isize; ++i )
  {
    v7 = *std::vector<int>::operator[](vSlot, i);
    if ( !CExtCharBag::IsSlotValid(this, v7) )
      break;
    v8 = *std::vector<int>::operator[](vSlot, i);
    bagSlot = *CExtCharBag::GetSlotData(this, v8);
    v10 = 0;
    if ( bagSlot.endTime > 0 )
    {
      if ( this->m_pPlayer )
      {
        endTime = bagSlot.endTime;
        if ( endTime <= Unit::getNow(this->m_pPlayer) )
          v10 = 1;
      }
    }
    if ( !v10 && CExtCharBag::compairItem(this, &bagSlot, data) && bagSlot.bind == 1 )
    {
      v11 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
      nRemove = v11;
      bagSlot.itemCount -= v11;
      *BindCount += v11;
      v12 = *std::vector<int>::operator[](vSlot, i);
      CExtCharBag::setSlotData(this, v12, &bagSlot, nReason, nRemove);
      nCount -= nRemove;
      if ( nCount <= 0 )
        return 1;
    }
  }
  for ( i_0 = 0; i_0 < isize; ++i_0 )
  {
    v13 = *std::vector<int>::operator[](vSlot, i_0);
    if ( !CExtCharBag::IsSlotValid(this, v13) )
      break;
    v14 = *std::vector<int>::operator[](vSlot, i_0);
    bagSlot = *CExtCharBag::GetSlotData(this, v14);
    v16 = 0;
    if ( bagSlot.endTime > 0 )
    {
      if ( this->m_pPlayer )
      {
        v15 = bagSlot.endTime;
        if ( v15 <= Unit::getNow(this->m_pPlayer) )
          v16 = 1;
      }
    }
    if ( !v16 && CExtCharBag::compairItem(this, &bagSlot, data) && !bagSlot.bind )
    {
      v17 = bagSlot.itemCount >= nCount ? nCount : bagSlot.itemCount;
      nRemove_0 = v17;
      bagSlot.itemCount -= v17;
      *UnBindCount += v17;
      v18 = *std::vector<int>::operator[](vSlot, i_0);
      CExtCharBag::setSlotData(this, v18, &bagSlot, nReason, nRemove_0);
      nCount -= nRemove_0;
      if ( nCount <= 0 )
        return 1;
    }
  }
  return 0;
}


