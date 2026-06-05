// Decompiled methods for class: CDropItemGroup
// Source: gameserver.cc
// Total methods: 5

#####################################
void __cdecl CDropItemGroup::init(
        CDropItemGroup *const this,
        int8_t connid,
        Map *pMap,
        Position *const centerPos,
        Player *pOwner,
        int32_t droperType,
        int32_t droperMid,
        DropItemVector *const dropItems,
        const std::string *const dropper,
        int32_t MonsterMid,
        int8_t bossSign,
        int8_t autoPick)
{
  DropItem *M_current; // rbx
  __gnu_cxx::__normal_iterator<DropItem*,std::vector<DropItem> > v13; // rax
  int32_t itemId; // ebx
  CfgData *v15; // rax
  Plant *v16; // rbx
  CPoolManager *v17; // rax
  int32_t v18; // eax
  int8_t v19; // r13
  DropItem *v20; // rax
  CKaiFuHuoDong *v21; // rax
  CfgData *v23; // rax
  int32_t m_backIndex; // ebx
  CEquipBack *v25; // rax
  CfgMapPlant stu; // [rsp+80h] [rbp-100h] BYREF
  CDropItem *pDropItem; // [rsp+98h] [rbp-E8h] BYREF
  Position pos; // [rsp+A0h] [rbp-E0h] BYREF
  int32_t dropIndex; // [rsp+ACh] [rbp-D4h] BYREF
  PositionVector vRand; // [rsp+B0h] [rbp-D0h] BYREF
  std::string name; // [rsp+D0h] [rbp-B0h] BYREF
  char v36; // [rsp+DFh] [rbp-A1h] BYREF
  _BYTE v37[16]; // [rsp+E0h] [rbp-A0h] BYREF
  std::string p_name; // [rsp+F0h] [rbp-90h] BYREF
  int64_t curTick; // [rsp+100h] [rbp-80h]
  int64_t endTick; // [rsp+108h] [rbp-78h]
  int64_t freeTick; // [rsp+110h] [rbp-70h]
  int8_t dropType; // [rsp+11Fh] [rbp-61h]
  int64_t nOwnerId; // [rsp+120h] [rbp-60h]
  int32_t nTeamId; // [rsp+128h] [rbp-58h]
  int32_t nPositionSize; // [rsp+12Ch] [rbp-54h]
  int32_t isize; // [rsp+130h] [rbp-50h]
  int32_t i; // [rsp+134h] [rbp-4Ch]
  int64_t showTick; // [rsp+138h] [rbp-48h]
  CfgPlant *pCfgPlant; // [rsp+140h] [rbp-40h]
  Plant *plant; // [rsp+148h] [rbp-38h]
  int32_t EquipId; // [rsp+154h] [rbp-2Ch]
  const CfgEquip *pEquip; // [rsp+158h] [rbp-28h]

  if ( pMap )
  {
    curTick = Map::getTick(pMap);
    endTick = curTick + 120000;
    freeTick = curTick + 90000;
    dropType = CDropItemGroup::calDropType(this, droperType, bossSign);
    nOwnerId = 0;
    nTeamId = 0;
    std::allocator<char>::allocator(&v36);
    std::string::string(&name, &unk_8D636F, &v36);
    std::allocator<char>::~allocator(&v36);
    if ( pOwner )
    {
      Player::getName((const Player *const)v37);
      std::string::operator=(&name, v37);
      std::string::~string(v37);
      if ( droperType != 1 && !autoPick )
      {
        nOwnerId = Player::getCid(pOwner);
        nTeamId = Player::GetTeamId(pOwner);
      }
    }
    if ( autoPick == 2 )
    {
      freeTick = curTick + 30;
      nOwnerId = 1;
    }
    if ( autoPick == 3 && pOwner )
    {
      freeTick = endTick;
      nOwnerId = Player::getCid(pOwner);
    }
    M_current = std::vector<DropItem>::end(dropItems)._M_current;
    v13._M_current = std::vector<DropItem>::begin(dropItems)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<DropItem *,std::vector<DropItem>>>(
      v13,
      (__gnu_cxx::__normal_iterator<DropItem*,std::vector<DropItem> >)M_current);
    std::vector<Position>::vector(&vRand);
    nPositionSize = std::vector<DropItem>::size(dropItems);
    CDropItemGroup::calRandPosition(this, pMap, centerPos, &vRand, nPositionSize);
    dropIndex = 0;
    isize = std::vector<DropItem>::size(dropItems);
    for ( i = 0; i < isize; ++i )
    {
      pos = CDropItemGroup::calDropPosition(this, pMap, centerPos, &vRand, &dropIndex);
      if ( std::vector<DropItem>::operator[](dropItems, i)->itemClass == 9
        && (itemId = std::vector<DropItem>::operator[](dropItems, i)->itemId,
            v15 = Answer::Singleton<CfgData>::instance(),
            (pCfgPlant = CfgData::getPlant(v15, itemId)) != 0) )
      {
        v16 = (Plant *)operator new(0xE0u);
        Plant::Plant(v16);
        plant = v16;
        if ( v16 )
        {
          *(_QWORD *)&stu.mapid = 0;
          *(_QWORD *)&stu.x = 0;
          stu.mapid = Map::GetMapId(pMap);
          stu.plantid = pCfgPlant->id;
          *(Position *)&stu.x = pos;
          Plant::init(plant, pMap, pCfgPlant, &stu, 0);
          Plant::setLifeTime(plant, 120);
          Map::addPlant(pMap, plant);
        }
      }
      else
      {
        v17 = Answer::Singleton<CPoolManager>::instance();
        pDropItem = CPoolManager::pop<CDropItem>(v17);
        if ( !pDropItem )
          break;
        v18 = CDropItemGroup::calShowDelay(this, i);
        showTick = curTick + v18;
        v19 = dropType;
        std::string::string(&p_name, &name);
        v20 = std::vector<DropItem>::operator[](dropItems, i);
        CDropItem::init(
          pDropItem,
          pMap,
          &pos,
          connid,
          v20,
          nOwnerId,
          &p_name,
          MonsterMid,
          nTeamId,
          showTick,
          freeTick,
          endTick,
          autoPick,
          v19);
        std::string::~string(&p_name);
        std::list<CDropItem *>::push_back(&this->m_dropItems, &pDropItem);
        v21 = Answer::Singleton<CKaiFuHuoDong>::instance();
        if ( CKaiFuHuoDong::InTime(v21) && CDropItem::getItemClass(pDropItem) == 2 && droperType == 2 )
        {
          EquipId = CDropItem::getItemId(pDropItem);
          v23 = Answer::Singleton<CfgData>::instance();
          pEquip = CfgData::getEquip(v23, EquipId);
          if ( pEquip )
          {
            if ( pEquip->m_backIndex > 0 )
            {
              m_backIndex = pEquip->m_backIndex;
              v25 = Answer::Singleton<CEquipBack>::instance();
              CEquipBack::KiaFuEquipBack(v25, m_backIndex, EquipId, droperMid, pOwner);
            }
          }
        }
        CDropItemGroup::checkBroadcast(this, pMap, pDropItem, pOwner, droperType, droperMid, MonsterMid, dropper);
      }
    }
    std::vector<Position>::~vector(&vRand);
    std::string::~string(&name);
  }
}


#####################################
void __cdecl CDropItemGroup::checkBroadcast(
        CDropItemGroup *const this,
        Map *pMap,
        CDropItem *pDropItem,
        Player *pOwner,
        int8_t droperType,
        int32_t droperMid,
        int32_t MonsterMid,
        const std::string *const dropper)
{
  int8_t ItemClass; // r12
  int32_t ItemId; // ebx
  CfgData *v10; // rax
  GameService *v11; // rax
  CharId_t Cid; // rax
  int8_t v13; // al
  int32_t v14; // eax
  int32_t ItemCount; // eax
  uint32_t WOffset; // eax
  GameService *v17; // rax
  GameService *v18; // rax
  CharId_t v19; // rax
  int32_t MapId; // eax
  int8_t v21; // al
  int32_t v22; // eax
  int32_t v23; // eax
  uint32_t v24; // eax
  GameService *v25; // rax
  std::string val; // [rsp+30h] [rbp-50h] BYREF
  std::string v31; // [rsp+40h] [rbp-40h] BYREF
  std::string v32; // [rsp+50h] [rbp-30h] BYREF
  char v33; // [rsp+5Fh] [rbp-21h] BYREF
  Answer::NetPacket *packet; // [rsp+60h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+68h] [rbp-18h]

  if ( pMap )
  {
    if ( pDropItem )
    {
      ItemClass = CDropItem::getItemClass(pDropItem);
      ItemId = CDropItem::getItemId(pDropItem);
      v10 = Answer::Singleton<CfgData>::instance();
      if ( CfgData::dropBroadcast(v10, ItemId, ItemClass) )
      {
        if ( pOwner && droperType == 6 )
        {
          v11 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v11, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          Answer::NetPacket::writeInt32(packet, 241);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          Cid = Player::getCid(pOwner);
          Answer::NetPacket::writeInt64(packet, Cid);
          Answer::NetPacket::writeInt32(packet, droperMid);
          v13 = CDropItem::getItemClass(pDropItem);
          Answer::NetPacket::writeInt8(packet, v13);
          v14 = CDropItem::getItemId(pDropItem);
          Answer::NetPacket::writeInt32(packet, v14);
          ItemCount = CDropItem::getItemCount(pDropItem);
          Answer::NetPacket::writeInt32(packet, ItemCount);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v17 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v17, packet);
        }
        else if ( pOwner || droperType != 1 )
        {
          v18 = Answer::Singleton<GameService>::instance();
          packet_0 = GameService::popNetpacket(v18, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( packet_0 )
          {
            Answer::NetPacket::writeInt32(packet_0, 11);
            Answer::NetPacket::writeInt32(packet_0, 0);
            if ( pOwner )
            {
              Player::getName((const Player *const)&v31);
              Answer::NetPacket::writeUTF8(packet_0, &v31);
              std::string::~string(&v31);
              v19 = Player::getCid(pOwner);
              Answer::NetPacket::writeInt64(packet_0, v19);
            }
            else
            {
              std::allocator<char>::allocator(&v33);
              std::string::string(&v32, &unk_8D636F, &v33);
              Answer::NetPacket::writeUTF8(packet_0, &v32);
              std::string::~string(&v32);
              std::allocator<char>::~allocator(&v33);
              Answer::NetPacket::writeInt64(packet_0, 0);
            }
            MapId = Map::GetMapId(pMap);
            Answer::NetPacket::writeInt32(packet_0, MapId);
            Answer::NetPacket::writeInt32(packet_0, droperMid);
            Answer::NetPacket::writeUTF8(packet_0, dropper);
            v21 = CDropItem::getItemClass(pDropItem);
            Answer::NetPacket::writeInt8(packet_0, v21);
            v22 = CDropItem::getItemId(pDropItem);
            Answer::NetPacket::writeInt32(packet_0, v22);
            v23 = CDropItem::getItemCount(pDropItem);
            Answer::NetPacket::writeInt32(packet_0, v23);
            v24 = Answer::NetPacket::getWOffset(packet_0);
            Answer::NetPacket::setSize(packet_0, v24);
            v25 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v25, packet_0);
          }
        }
      }
    }
  }
}


#####################################
int8_t __cdecl CDropItemGroup::calDropType(CDropItemGroup *const this, int8_t droperType, int8_t bossSign)
{
  if ( droperType == 1 )
    return 2;
  else
    return bossSign != 0;
}


#####################################
void __cdecl CDropItemGroup::calRandPosition(
        CDropItemGroup *const this,
        Map *pMap,
        const Position *const center,
        PositionVector *const vRand,
        int32_t nSize)
{
  Position TmpPos; // [rsp+30h] [rbp-60h] BYREF
  Position Pos; // [rsp+40h] [rbp-50h] BYREF
  Position __x; // [rsp+50h] [rbp-40h] BYREF
  Position v12; // [rsp+60h] [rbp-30h] BYREF
  int32_t InSize; // [rsp+70h] [rbp-20h]
  int32_t PosSize; // [rsp+74h] [rbp-1Ch]
  int32_t i; // [rsp+78h] [rbp-18h]
  int32_t j; // [rsp+7Ch] [rbp-14h]

  if ( pMap )
  {
    std::vector<Position>::reserve(vRand, nSize);
    InSize = 0;
    for ( i = 0; i <= 120; ++i )
    {
      Position::Position(&TmpPos, 0, 0);
      TmpPos.x = DROP_X_CLIP[i] + center->x;
      TmpPos.y = DROP_Y_CLIP[i] + center->y;
      Position::Position(&Pos, TmpPos.x, TmpPos.y);
      if ( !Map::HaveDropAndPlayer(pMap, Pos) && Map::isWalkablePosition(pMap, TmpPos.x, TmpPos.y) )
      {
        Position::Position(&__x, DROP_X_CLIP[i], DROP_Y_CLIP[i]);
        std::vector<Position>::push_back(vRand, &__x);
        if ( ++InSize >= nSize )
          break;
      }
    }
    PosSize = std::vector<Position>::size(vRand);
    if ( nSize > PosSize )
    {
      for ( j = 0; nSize - PosSize > j; ++j )
      {
        if ( Map::isWalkablePosition(pMap, DROP_X_CLIP[j % 121] + center->x, DROP_Y_CLIP[j % 121] + center->y) )
        {
          Position::Position(&v12, DROP_X_CLIP[j % 121], DROP_Y_CLIP[j % 121]);
          std::vector<Position>::push_back(vRand, &v12);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CDropItemGroup::calPositionSize(CDropItemGroup *const this, int32_t nSize)
{
  int32_t i; // [rsp+18h] [rbp-4h]

  for ( i = 5; i >= 0; --i )
  {
    if ( DROP_ITEM_COUNT[i] <= nSize )
      return DROP_SIZE[i];
  }
  return DROP_SIZE[0];
}


