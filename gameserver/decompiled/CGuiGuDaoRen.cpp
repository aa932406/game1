// Decompiled methods for class: CGuiGuDaoRen
// Source: gameserver.cc
// Total methods: 19

#####################################
int32_t __cdecl CGuiGuDaoRen::OnAskBackItemCount(CGuiGuDaoRen *const this, Player *pPlayer, Answer::NetPacket *packet)
{
  int32_t Int32; // edx

  if ( !packet || !pPlayer )
    return 10002;
  Int32 = Answer::NetPacket::readInt32(packet);
  CGuiGuDaoRen::SendBackItemCount(this, pPlayer, Int32);
  return 0;
}


#####################################
int32_t __cdecl CGuiGuDaoRen::OnBackItem(CGuiGuDaoRen *const this, Player *pPlayer, Answer::NetPacket *packet)
{
  CfgData *v4; // rax
  CExtCharBag *Bag; // rax
  ItemData *v6; // rbx
  CExtCharBag *v7; // rax
  MemChrBag *v8; // rbx
  CExtCharBag *v9; // rax
  int32_t v10; // ebx
  int *v11; // rax
  int32_t v12; // ebx
  int32_t BossId; // ebx
  CfgData *v15; // rax
  int v16; // ebx
  Answer::Random *v17; // rax
  int32_t v18; // ebx
  TileManager *v19; // rax
  CfgData *v20; // rax
  CPoolManager *v21; // rax
  int32_t v22; // ebx
  MapManager *v23; // rax
  int32_t v24; // ebx
  RefreshMonster *v25; // rax
  GameService *v26; // rax
  RefreshMonster *v28; // rax
  RefreshMonster *v29; // rax
  int *v30; // rax
  uint32_t WOffset; // eax
  int8_t ConnId; // bl
  GameService *v33; // rax
  int *v34; // rax
  int *v35; // rax
  int *v36; // rax
  CfgMapMonster MapMonster; // [rsp+20h] [rbp-C0h] BYREF
  Position Pos; // [rsp+40h] [rbp-A0h]
  std::_List_iterator<RefreshMonster> it; // [rsp+50h] [rbp-90h] BYREF
  int32_t nNpcId; // [rsp+5Ch] [rbp-84h] BYREF
  std::_List_iterator<RefreshMonster> __x; // [rsp+60h] [rbp-80h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+70h] [rbp-70h] BYREF
  int8_t Id; // [rsp+8Fh] [rbp-51h]
  GuiGuDaoRenCfg *pCfg; // [rsp+90h] [rbp-50h]
  int32_t AddItemCount; // [rsp+9Ch] [rbp-44h]
  CfgMonster *pMonster; // [rsp+A0h] [rbp-40h]
  int32_t MapIdCount; // [rsp+ACh] [rbp-34h]
  int32_t nRand; // [rsp+B0h] [rbp-30h]
  int32_t MonsterId; // [rsp+B4h] [rbp-2Ch]
  Monster *monster; // [rsp+B8h] [rbp-28h]
  Map *pMap; // [rsp+C0h] [rbp-20h]
  Answer::NetPacket *packet_0; // [rsp+C8h] [rbp-18h]

  if ( !packet || !pPlayer )
    return 10002;
  nNpcId = Answer::NetPacket::readInt32(packet);
  Id = Answer::NetPacket::readInt8(packet);
  if ( Id <= 0 || Id > 3 )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetGuiGuDaoRenCfg(v4, nNpcId);
  if ( !pCfg )
    return 10002;
  Bag = Player::GetBag(pPlayer);
  if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
    return 10002;
  AddItemCount = std::vector<ItemData>::operator[](&pCfg->vItemData, Id - 1)->m_nCount;
  v6 = std::vector<ItemData>::operator[](&pCfg->vItemData, Id - 1);
  v7 = Player::GetBag(pPlayer);
  if ( !CExtCharBag::RemoveItem(v7, v6, ITEM_CHANGE_REASON::ICR_GUI_GU_DAO_REN) )
    return 10002;
  v8 = std::vector<MemChrBag>::operator[](&pCfg->vItem, Id - 1);
  v9 = Player::GetBag(pPlayer);
  if ( !CExtCharBag::AddItem(v9, v8, ITEM_CHANGE_REASON::ICR_GUI_GU_DAO_REN) )
    return 10002;
  for ( it._M_node = std::list<RefreshMonster>::begin(&pCfg->lRefreshMonster)._M_node;
        ;
        std::_List_iterator<RefreshMonster>::operator++(&it, 0) )
  {
    __x._M_node = std::list<RefreshMonster>::end(&pCfg->lRefreshMonster)._M_node;
    if ( !std::_List_iterator<RefreshMonster>::operator!=(&it, &__x) )
      break;
    v10 = *std::map<int,int>::operator[](&this->BackItemCount, &nNpcId);
    if ( v10 < std::_List_iterator<RefreshMonster>::operator->(&it)->nCount )
    {
      v11 = std::map<int,int>::operator[](&this->BackItemCount, &nNpcId);
      v12 = AddItemCount + *v11;
      if ( v12 >= std::_List_iterator<RefreshMonster>::operator->(&it)->nCount )
      {
        BossId = std::_List_iterator<RefreshMonster>::operator->(&it)->BossId;
        v15 = Answer::Singleton<CfgData>::instance();
        pMonster = CfgData::getMonster(v15, BossId);
        if ( !pMonster )
          return 2;
        if ( pMonster->boss_sign != 11 )
          return 2;
        MapIdCount = std::vector<int>::size(&pCfg->vMapId);
        v16 = MapIdCount - 1;
        v17 = Answer::Singleton<Answer::Random>::instance();
        nRand = Answer::Random::generate(v17, 0, v16);
        v18 = *std::vector<int>::operator[](&pCfg->vMapId, nRand);
        v19 = Answer::Singleton<TileManager>::instance();
        Pos = TileManager::getRandomWalkablePosition(v19, v18);
        if ( Pos.x != -1 && Pos.y != -1 )
        {
          v20 = Answer::Singleton<CfgData>::instance();
          MonsterId = CfgData::GetMapMonsterId(v20);
          memset(&MapMonster.mapid, 0, 24);
          MapMonster.id = MonsterId;
          MapMonster.mapid = *std::vector<int>::operator[](&pCfg->vMapId, nRand);
          *(Position *)&MapMonster.x = Pos;
          v21 = Answer::Singleton<CPoolManager>::instance();
          monster = CPoolManager::pop<Monster>(v21);
          v22 = *std::vector<int>::operator[](&pCfg->vMapId, nRand);
          v23 = Answer::Singleton<MapManager>::instance();
          pMap = MapManager::GetMap(v23, v22);
          if ( pMap )
          {
            if ( monster && pMonster )
            {
              std::vector<AttrAddon>::vector(&vAttrAddon);
              Monster::init(monster, pMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
              std::vector<AttrAddon>::~vector(&vAttrAddon);
              v24 = Answer::DayTime::now();
              v25 = std::_List_iterator<RefreshMonster>::operator->(&it);
              Monster::SetLifeTime(monster, v24 + v25->AliveTime);
              (*((void (__fastcall **)(Map *, Monster *, _QWORD, _QWORD))pMap->_vptr_Map + 28))(
                pMap,
                monster,
                (unsigned int)MapMonster.x,
                (unsigned int)MapMonster.y);
              LOBYTE(v24) = Player::getConnId(pPlayer);
              v26 = Answer::Singleton<GameService>::instance();
              packet_0 = GameService::popNetpacket(v26, v24, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
              if ( packet_0 && std::_List_iterator<RefreshMonster>::operator->(&it)->GongGaoId > 0 )
              {
                v28 = std::_List_iterator<RefreshMonster>::operator->(&it);
                Answer::NetPacket::writeInt32(packet_0, v28->GongGaoId);
                v29 = std::_List_iterator<RefreshMonster>::operator->(&it);
                Answer::NetPacket::writeInt32(packet_0, v29->BossId);
                v30 = std::vector<int>::operator[](&pCfg->vMapId, nRand);
                Answer::NetPacket::writeInt32(packet_0, *v30);
                WOffset = Answer::NetPacket::getWOffset(packet_0);
                Answer::NetPacket::setSize(packet_0, WOffset);
                ConnId = Player::getConnId(pPlayer);
                v33 = Answer::Singleton<GameService>::instance();
                GameService::worldBroadcast(v33, ConnId, packet_0);
              }
            }
          }
        }
      }
    }
  }
  v34 = std::map<int,int>::operator[](&this->BackItemCount, &nNpcId);
  *v34 += AddItemCount;
  v35 = std::map<int,int>::operator[](&this->BackItemCount, &nNpcId);
  if ( *v35 >= pCfg->nMaxCount )
  {
    v36 = std::map<int,int>::operator[](&this->BackItemCount, &nNpcId);
    *v36 -= pCfg->nMaxCount;
  }
  CGuiGuDaoRen::UpdateBackItemCount(this, nNpcId);
  CGuiGuDaoRen::SendBackItemCount(this, pPlayer, nNpcId);
  return 0;
}


#####################################
void __cdecl CGuiGuDaoRen::SendBackItemCount(CGuiGuDaoRen *const this, Player *pPlayer, int32_t NpcId)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  std::pair<const int,int> *v5; // rax
  std::pair<const int,int> *v6; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  int32_t NpcIda; // [rsp+Ch] [rbp-44h] BYREF
  Player *pPlayera; // [rsp+10h] [rbp-40h]
  CGuiGuDaoRen *thisa; // [rsp+18h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  thisa = this;
  pPlayera = pPlayer;
  NpcIda = NpcId;
  if ( pPlayer )
  {
    it._M_node = std::map<int,int>::find(&thisa->BackItemCount, &NpcIda)._M_node;
    __x._M_node = std::map<int,int>::end(&thisa->BackItemCount)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator==(&it, &__x) )
    {
      ConnId = Player::getConnId(pPlayera);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F4Fu);
      if ( packet )
      {
        v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->first);
        v6 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->second);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(pPlayera);
        v9 = Player::getConnId(pPlayera);
        v10 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v10, v9, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CGuiGuDaoRen::UpdateBackItemCount(CGuiGuDaoRen *const this, int32_t NpcId)
{
  int32_t v2; // r12d
  int32_t v3; // ebx
  DBService *v4; // rax
  int32_t NpcIda; // [rsp+4h] [rbp-1Ch] BYREF
  CGuiGuDaoRen *thisa; // [rsp+8h] [rbp-18h]

  thisa = this;
  NpcIda = NpcId;
  v2 = *std::map<int,int>::operator[](&this->BackItemCount, &NpcIda);
  v3 = NpcIda;
  v4 = Answer::Singleton<DBService>::instance();
  DBService::SaveGuiGuDaoRenData(v4, v3, v2);
}


#####################################
int32_t __cdecl CGuiGuDaoRen::OnAskBackEquipCount(CGuiGuDaoRen *const this, Player *pPlayer, Answer::NetPacket *packet)
{
  CGuiGuDaoRen::SendBackEquipCount(this, pPlayer);
  return 0;
}


#####################################
int32_t __cdecl CGuiGuDaoRen::OnBackEquipCount(CGuiGuDaoRen *const this, Player *pPlayer, Answer::NetPacket *InPacket)
{
  int32_t v3; // ebx
  int *M_current; // rbx
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v5; // rax
  int32_t v6; // ebx
  CExtCharBag *Bag; // rax
  int32_t v8; // ebx
  CfgData *v9; // rax
  const CfgEquipTable *EquipTable; // rax
  int32_t v11; // ebx
  CExtCharBag *v12; // rax
  EquipBackRankCfg *v13; // rax
  EquipBackRankCfg *v14; // rax
  EquipBackRankCfg *v15; // rax
  EquipBackRankCfg *v16; // rax
  EquipBackRankCfg *v17; // rax
  EquipBackRankCfg *v18; // rbx
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > v19; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  GameService *v22; // rax
  GameService *v23; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t ConnId; // bl
  GameService *v27; // rax
  int32_t nSlotId; // [rsp+4Ch] [rbp-154h] BYREF
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > itRank; // [rsp+50h] [rbp-150h] BYREF
  Answer::MutexGuard lock; // [rsp+60h] [rbp-140h] BYREF
  EquipBackRankCfg stu; // [rsp+70h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it; // [rsp+90h] [rbp-110h] BYREF
  Int32Vector vSlot; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+C0h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __lhs; // [rsp+D0h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v38; // [rsp+E0h] [rbp-C0h] BYREF
  _BYTE v39[16]; // [rsp+F0h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > v40; // [rsp+100h] [rbp-A0h] BYREF
  EquipBackRankCfg p_Stu; // [rsp+110h] [rbp-90h] BYREF
  EquipBackRankCfg v42; // [rsp+130h] [rbp-70h] BYREF
  std::string val; // [rsp+150h] [rbp-50h] BYREF
  int32_t MaxCount; // [rsp+15Ch] [rbp-44h]
  int32_t nCount; // [rsp+160h] [rbp-40h]
  bool bFind; // [rsp+167h] [rbp-39h]
  Answer::NetPacket *packet; // [rsp+168h] [rbp-38h]
  int32_t i; // [rsp+174h] [rbp-2Ch]
  const CfgEquip *pEquip; // [rsp+178h] [rbp-28h]

  if ( !pPlayer || !InPacket )
    return 10002;
  MaxCount = CGuiGuDaoRen::GetMaxCount(this);
  if ( MaxCount <= 0 )
    return 10002;
  std::vector<int>::vector(&vSlot);
  nCount = Answer::NetPacket::readInt32(InPacket);
  for ( i = 0; i < nCount; ++i )
  {
    nSlotId = Answer::NetPacket::readInt32(InPacket);
    __rhs._M_current = std::vector<int>::end(&vSlot)._M_current;
    M_current = std::vector<int>::end(&vSlot)._M_current;
    v5._M_current = std::vector<int>::begin(&vSlot)._M_current;
    __lhs._M_current = std::find<__gnu_cxx::__normal_iterator<int *,std::vector<int>>,int>(
                         v5,
                         (__gnu_cxx::__normal_iterator<int*,std::vector<int> >)M_current,
                         &nSlotId)._M_current;
    if ( __gnu_cxx::operator!=<int *,std::vector<int>>(&__lhs, &__rhs) )
    {
      v3 = 10002;
      goto LABEL_32;
    }
    std::vector<int>::push_back(&vSlot, &nSlotId);
    v6 = nSlotId;
    Bag = Player::GetBag(pPlayer);
    v8 = *(_QWORD *)&CExtCharBag::GetSlotData(Bag, v6)->itemId;
    v9 = Answer::Singleton<CfgData>::instance();
    EquipTable = CfgData::GetEquipTable(v9);
    pEquip = CfgEquipTable::GetEquip(EquipTable, v8);
    if ( !pEquip )
    {
      v3 = 10002;
      goto LABEL_32;
    }
    if ( pEquip->m_nGrade <= 29 || pEquip->m_nGrade > 35 || pEquip->m_nType > 7 )
    {
      v3 = 10002;
      goto LABEL_32;
    }
  }
  if ( std::vector<int>::size(&vSlot) )
  {
    for ( it._M_current = std::vector<int>::begin(&vSlot)._M_current;
          ;
          __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it, 0) )
    {
      v38._M_current = std::vector<int>::end(&vSlot)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it, &v38) )
        break;
      v11 = *__gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
      v12 = Player::GetBag(pPlayer);
      CExtCharBag::CleanSlot(v12, v11, ITEM_CHANGE_REASON::IDCR_BACK_EQUIP_COUNT);
    }
    this->EquipCount += nCount;
    CGuiGuDaoRen::SendBackEquipCount(this, pPlayer);
    CGuiGuDaoRen::UpdateEquipCount(this);
    memset(&stu, 0, sizeof(stu));
    std::string::string(&stu.nName);
    stu.Cid = Player::getCid(pPlayer);
    Player::getName((const Player *const)v39);
    std::string::operator=(&stu.nName, v39);
    std::string::~string(v39);
    stu.Count = nCount;
    stu.Time = Unit::getNow(pPlayer);
    bFind = 0;
    Answer::MutexGuard::MutexGuard(&lock, &this->m_RankLock);
    for ( itRank._M_current = std::vector<EquipBackRankCfg>::begin(&this->m_EquipBackRank)._M_current;
          ;
          __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator++(&itRank, 0) )
    {
      v40._M_current = std::vector<EquipBackRankCfg>::end(&this->m_EquipBackRank)._M_current;
      if ( !__gnu_cxx::operator!=<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>(&itRank, &v40) )
        break;
      v13 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&itRank);
      if ( v13->Cid == stu.Cid )
      {
        v14 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&itRank);
        std::string::operator=(&v14->nName, &stu.nName);
        v15 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&itRank);
        v15->Count += stu.Count;
        v16 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&itRank);
        v16->Time = stu.Time;
        v17 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator*(&itRank);
        EquipBackRankCfg::EquipBackRankCfg(&p_Stu, v17);
        CGuiGuDaoRen::UpdateRankDate(this, &p_Stu);
        EquipBackRankCfg::~EquipBackRankCfg(&p_Stu);
        bFind = 1;
        break;
      }
    }
    if ( !bFind )
    {
      std::vector<EquipBackRankCfg>::push_back(&this->m_EquipBackRank, &stu);
      EquipBackRankCfg::EquipBackRankCfg(&v42, &stu);
      CGuiGuDaoRen::UpdateRankDate(this, &v42);
      EquipBackRankCfg::~EquipBackRankCfg(&v42);
    }
    v18 = std::vector<EquipBackRankCfg>::end(&this->m_EquipBackRank)._M_current;
    v19._M_current = std::vector<EquipBackRankCfg>::begin(&this->m_EquipBackRank)._M_current;
    std::sort<__gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>,bool (*)(EquipBackRankCfg const&,EquipBackRankCfg const&)>(
      v19,
      (__gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> >)v18,
      (bool (*)(const EquipBackRankCfg *, const EquipBackRankCfg *))GreaterEquipBackRank);
    Proc = Answer::NetPacket::getProc(InPacket);
    GateIndex = Player::getGateIndex(pPlayer);
    LOBYTE(v18) = Player::getConnId(pPlayer);
    v22 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v22, (int8_t)v18, GateIndex, Proc, 0);
    LOBYTE(v18) = Player::getConnId(pPlayer);
    v23 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v23, (int8_t)v18, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 540);
      Cid = Player::getCid(pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, nCount);
      Answer::NetPacket::writeInt32(packet, this->EquipCount);
      Answer::NetPacket::writeInt32(packet, MaxCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      ConnId = Player::getConnId(pPlayer);
      v27 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v27, ConnId, packet);
    }
    v3 = 0;
    Answer::MutexGuard::~MutexGuard(&lock);
    EquipBackRankCfg::~EquipBackRankCfg(&stu);
  }
  else
  {
    v3 = 10002;
  }
LABEL_32:
  std::vector<int>::~vector(&vSlot);
  return v3;
}


#####################################
void __cdecl CGuiGuDaoRen::SendBackEquipCount(CGuiGuDaoRen *const this, Player *pPlayer)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F50u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->EquipCount);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v6 = Player::getConnId(pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CGuiGuDaoRen::UpdateEquipCount(CGuiGuDaoRen *const this)
{
  int32_t EquipCount; // ebx
  DBService *v2; // rax

  EquipCount = this->EquipCount;
  v2 = Answer::Singleton<DBService>::instance();
  DBService::SaveBackEquipCount(v2, EquipCount);
}


#####################################
int32_t __cdecl CGuiGuDaoRen::GetMaxCount(CGuiGuDaoRen *const this)
{
  CfgData *v1; // rax
  int32_t nCount; // [rsp+1Ch] [rbp-4h]

  v1 = Answer::Singleton<CfgData>::instance();
  nCount = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL) + 1;
  if ( nCount <= 44 )
    return 0;
  if ( nCount <= 59 )
    return 20;
  if ( nCount > 119 )
    return 30;
  return 25;
}


#####################################
void __cdecl CGuiGuDaoRen::OnNewMinute(CGuiGuDaoRen *const this, int32_t nMinute)
{
  GameService *v2; // rax
  int32_t EquipCount; // ebx
  MapManager *v4; // rax
  int32_t v5; // eax
  CfgData *v6; // rax
  std::_Ios_Openmode v7; // eax
  unsigned int v8; // ebx
  __int64 v9; // rax
  __int64 v10; // rax
  CharId_t Cid; // rbx
  DBService *v12; // rax
  CfgData *v13; // rax
  const CfgTitleTable *TitleTable; // rax
  int8_t nType; // r12
  CharId_t v16; // rbx
  GameService *v17; // rax
  GameService *v18; // rax
  uint32_t WOffset; // eax
  GameService *v20; // rax
  _BYTE v21[16]; // [rsp+10h] [rbp-1E0h] BYREF
  __int64 v22; // [rsp+20h] [rbp-1D0h] BYREF
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > it; // [rsp+180h] [rbp-70h] BYREF
  Answer::MutexGuard lock; // [rsp+190h] [rbp-60h] BYREF
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > __rhs; // [rsp+1A0h] [rbp-50h] BYREF
  std::string Param; // [rsp+1B0h] [rbp-40h] BYREF
  int32_t GongGaoId; // [rsp+1B8h] [rbp-38h]
  int32_t RankIndex; // [rsp+1BCh] [rbp-34h]
  int32_t Time; // [rsp+1C0h] [rbp-30h]
  int32_t TitleId; // [rsp+1C4h] [rbp-2Ch]
  const CfgTitle *pTitle; // [rsp+1C8h] [rbp-28h]
  int32_t nParam; // [rsp+1D4h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+1D8h] [rbp-18h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) != 9 && nMinute == 840 )
  {
    GongGaoId = 0;
    EquipCount = this->EquipCount;
    if ( EquipCount < CGuiGuDaoRen::GetMaxCount(this) )
    {
      GongGaoId = 542;
    }
    else
    {
      v4 = Answer::Singleton<MapManager>::instance();
      MapManager::ResetMapMonster(v4);
      GongGaoId = 541;
    }
    this->EquipCount = 0;
    CGuiGuDaoRen::UpdateEquipCount(this);
    Answer::MutexGuard::MutexGuard(&lock, &this->m_RankLock);
    RankIndex = 0;
    it._M_current = std::vector<EquipBackRankCfg>::begin(&this->m_EquipBackRank)._M_current;
    v5 = Answer::DayTime::now();
    Time = Answer::DayTime::dayzero(v5);
    while ( 1 )
    {
      __rhs._M_current = std::vector<EquipBackRankCfg>::end(&this->m_EquipBackRank)._M_current;
      if ( !__gnu_cxx::operator!=<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>(&it, &__rhs) )
        break;
      ++RankIndex;
      v6 = Answer::Singleton<CfgData>::instance();
      TitleId = CfgData::GetTongTianChiReward(v6, RankIndex);
      if ( TitleId > 0 )
      {
        v7 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(
          v21,
          (unsigned int)v7);
        v8 = RankIndex - 1;
        v9 = std::ostream::operator<<(&v22, (unsigned int)Time);
        v10 = std::operator<<<std::char_traits<char>>(v9, "|");
        std::ostream::operator<<(v10, v8);
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(&Param, v21);
        Cid = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&it)->Cid;
        v12 = Answer::Singleton<DBService>::instance();
        DBService::OnSendSysMail(v12, 0, Cid, 6601, &Param, 0);
        std::string::~string(&Param);
        v13 = Answer::Singleton<CfgData>::instance();
        TitleTable = CfgData::GetTitleTable(v13);
        pTitle = CfgTitleTable::GetTitle(TitleTable, TitleId);
        if ( pTitle )
        {
          if ( std::vector<int>::size(&pTitle->vParams) == 1 )
          {
            nParam = *std::vector<int>::operator[](&pTitle->vParams, 0);
            if ( nParam > 0 && nParam <= 99 )
            {
              nType = pTitle->nType;
              v16 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&it)->Cid;
              v17 = Answer::Singleton<GameService>::instance();
              GameService::onCheckTeShuTitle(v17, v16, nType, nParam);
            }
          }
        }
        std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v21);
      }
      __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator++(&it, 0);
    }
    std::vector<EquipBackRankCfg>::clear(&this->m_EquipBackRank);
    if ( GongGaoId > 0 )
    {
      v18 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v18, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, GongGaoId);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        v20 = Answer::Singleton<GameService>::instance();
        GameService::worldBroadcast(v20, packet);
      }
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
int32_t __cdecl CGuiGuDaoRen::OnAskEquipBackRank(CGuiGuDaoRen *const this, Player *pPlayer, Answer::NetPacket *packet)
{
  CGuiGuDaoRen::SendBackEquipRank(this, pPlayer);
  return 0;
}


#####################################
void __cdecl CGuiGuDaoRen::SendBackEquipRank(CGuiGuDaoRen *const this, Player *pPlayer)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t v4; // eax
  EquipBackRankCfg *v5; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > it; // [rsp+10h] [rbp-40h] BYREF
  Answer::MutexGuard lock; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<EquipBackRankCfg*,std::vector<EquipBackRankCfg> > __rhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( pPlayer )
  {
    Answer::MutexGuard::MutexGuard(&lock, &this->m_RankLock);
    ConnId = Player::getConnId(pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2F51u);
    if ( packet )
    {
      v4 = std::vector<EquipBackRankCfg>::size(&this->m_EquipBackRank);
      Answer::NetPacket::writeInt32(packet, v4);
      for ( it._M_current = std::vector<EquipBackRankCfg>::begin(&this->m_EquipBackRank)._M_current;
            ;
            __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator++(&it, 0) )
      {
        __rhs._M_current = std::vector<EquipBackRankCfg>::end(&this->m_EquipBackRank)._M_current;
        if ( !__gnu_cxx::operator!=<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>(&it, &__rhs) )
          break;
        v5 = __gnu_cxx::__normal_iterator<EquipBackRankCfg *,std::vector<EquipBackRankCfg>>::operator->(&it);
        EquipBackRankCfg::PackageData(v5, packet);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v8 = Player::getConnId(pPlayer);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v9, v8, GateIndex, packet);
    }
    Answer::MutexGuard::~MutexGuard(&lock);
  }
}


#####################################
void __cdecl CGuiGuDaoRen::UpdateRankDate(CGuiGuDaoRen *const this, EquipBackRankCfg *p_Stu)
{
  DBService *v2; // rax
  EquipBackRankCfg p_stu; // [rsp+10h] [rbp-30h] BYREF

  EquipBackRankCfg::EquipBackRankCfg(&p_stu, p_Stu);
  v2 = Answer::Singleton<DBService>::instance();
  DBService::SaveBackEQuipRank(v2, &p_stu);
  EquipBackRankCfg::~EquipBackRankCfg(&p_stu);
}


#####################################
void __cdecl CGuiGuDaoRen::AddRongHeRecord(CGuiGuDaoRen *const this, RongHeRecord *p_Stu)
{
  RongHeRecord v2; // [rsp+10h] [rbp-30h] BYREF

  if ( std::list<RongHeRecord>::size(&this->m_RongHeRecordList) > 0x13 )
    std::list<RongHeRecord>::pop_front(&this->m_RongHeRecordList);
  std::list<RongHeRecord>::push_back(&this->m_RongHeRecordList, p_Stu);
  RongHeRecord::RongHeRecord(&v2, p_Stu);
  CGuiGuDaoRen::SendOneRongHeRecord(this, &v2);
  RongHeRecord::~RongHeRecord(&v2);
}


#####################################
void __cdecl CGuiGuDaoRen::SendAllRongHeRecord(CGuiGuDaoRen *const this, Player *pPlayer)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  RongHeRecord *v4; // rax
  RongHeRecord *v5; // rax
  RongHeRecord *v6; // rax
  RongHeRecord *v7; // rax
  RongHeRecord *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_List_iterator<RongHeRecord> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<RongHeRecord> __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  int32_t nSize; // [rsp+3Ch] [rbp-14h]

  if ( pPlayer )
  {
    ConnId = Player::getConnId(pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x280Bu);
    if ( packet )
    {
      nSize = std::list<RongHeRecord>::size(&this->m_RongHeRecordList);
      Answer::NetPacket::writeInt32(packet, nSize);
      for ( it._M_node = std::list<RongHeRecord>::begin(&this->m_RongHeRecordList)._M_node;
            ;
            std::_List_iterator<RongHeRecord>::operator++(&it, 0) )
      {
        __x._M_node = std::list<RongHeRecord>::end(&this->m_RongHeRecordList)._M_node;
        if ( !std::_List_iterator<RongHeRecord>::operator!=(&it, &__x) )
          break;
        v4 = std::_List_iterator<RongHeRecord>::operator->(&it);
        Answer::NetPacket::writeUTF8(packet, &v4->strName);
        v5 = std::_List_iterator<RongHeRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v5->nCostId);
        v6 = std::_List_iterator<RongHeRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v6->nGiveId);
        v7 = std::_List_iterator<RongHeRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v7->nSuccess);
        v8 = std::_List_iterator<RongHeRecord>::operator->(&it);
        Answer::NetPacket::writeInt32(packet, v8->nTime);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(pPlayer);
      v11 = Player::getConnId(pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CGuiGuDaoRen::SendOneRongHeRecord(CGuiGuDaoRen *const this, RongHeRecord *p_Stu)
{
  GameService *v2; // rax
  uint32_t WOffset; // edx
  GameService *v4; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, 0, Answer::PackType::PACK_DISPATCH, 0x280Cu);
  if ( packet )
  {
    Answer::NetPacket::writeUTF8(packet, &p_Stu->strName);
    Answer::NetPacket::writeInt32(packet, p_Stu->nCostId);
    Answer::NetPacket::writeInt32(packet, p_Stu->nGiveId);
    Answer::NetPacket::writeInt32(packet, p_Stu->nSuccess);
    Answer::NetPacket::writeInt32(packet, p_Stu->nTime);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v4 = Answer::Singleton<GameService>::instance();
    GameService::broadcast(v4, packet);
  }
}


#####################################
void __cdecl CGuiGuDaoRen::AddRongHeCount(CGuiGuDaoRen *const this, int32_t nCostCount, int32_t nGetCount)
{
  int32_t nParam; // [rsp+1Ch] [rbp-4h]

  this->m_CostCount += nCostCount;
  this->m_GetCount += nGetCount;
  if ( this->m_CostCount > 5000000 )
  {
    this->m_CostCount = 0;
    this->m_GetCount = 0;
    this->m_Rate = 0;
  }
  if ( this->m_CostCount > 10000 )
  {
    nParam = (int)(float)((float)((float)this->m_GetCount / (float)this->m_CostCount) * 100.0);
    if ( this->m_Rate )
    {
      if ( nParam <= 96 )
        this->m_Rate = 0;
    }
    else if ( nParam > 103 )
    {
      this->m_Rate = 1;
    }
  }
  else
  {
    this->m_Rate = 0;
  }
  CGuiGuDaoRen::UpdateRongHeCount(this);
}


#####################################
void __cdecl CGuiGuDaoRen::UpdateRongHeCount(CGuiGuDaoRen *const this)
{
  GameService *v1; // rax
  Answer::DBPool *v2; // rax
  Answer::MySqlQuery *v3; // rax
  Answer::MySqlQuery *v4; // rax
  Answer::MySqlQuery *v5; // rax
  char mySql_0[1024]; // [rsp+10h] [rbp-8A0h] BYREF
  char mySql[1024]; // [rsp+410h] [rbp-4A0h] BYREF
  Answer::MySqlDBGuard db; // [rsp+810h] [rbp-A0h] BYREF
  Answer::MySqlQuery result_1; // [rsp+840h] [rbp-70h] BYREF
  Answer::MySqlQuery result_0; // [rsp+860h] [rbp-50h] BYREF
  Answer::MySqlQuery result; // [rsp+880h] [rbp-30h] BYREF

  v1 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v1) != 9 )
  {
    v2 = Answer::Singleton<Answer::DBPool>::instance();
    Answer::MySqlDBGuard::MySqlDBGuard(&db, v2);
    memset(mySql, 0, sizeof(mySql));
    snprintf(mySql, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='COST_VALUE'");
    v3 = Answer::MySqlDBGuard::query(&db, mySql);
    Answer::MySqlQuery::MySqlQuery(&result, v3);
    memset(mySql_0, 0, sizeof(mySql_0));
    if ( Answer::MySqlQuery::eof(&result) )
      snprintf(
        mySql_0,
        0x3FFu,
        "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('COST_VALUE','%d')",
        this->m_CostCount);
    else
      snprintf(
        mySql_0,
        0x3FFu,
        "UPDATE `sys_server_config` SET `value`= %d WHERE `name`='COST_VALUE'",
        this->m_CostCount);
    Answer::MySqlDBGuard::excute(&db, mySql_0);
    Answer::MySqlQuery::~MySqlQuery(&result);
    memset(mySql_0, 0, sizeof(mySql_0));
    snprintf(mySql_0, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='GET_VALUE'");
    v4 = Answer::MySqlDBGuard::query(&db, mySql_0);
    Answer::MySqlQuery::MySqlQuery(&result_0, v4);
    if ( Answer::MySqlQuery::eof(&result_0) )
    {
      memset(mySql, 0, sizeof(mySql));
      snprintf(
        mySql,
        0x3FFu,
        "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('GET_VALUE','%d')",
        this->m_GetCount);
    }
    else
    {
      memset(mySql, 0, sizeof(mySql));
      snprintf(mySql, 0x3FFu, "UPDATE `sys_server_config` SET `value`= %d WHERE `name`='GET_VALUE'", this->m_GetCount);
    }
    Answer::MySqlDBGuard::excute(&db, mySql);
    Answer::MySqlQuery::~MySqlQuery(&result_0);
    memset(mySql, 0, sizeof(mySql));
    snprintf(mySql, 0x3FFu, "SELECT `value` FROM `sys_server_config` WHERE `name`='RATE_VALUE'");
    v5 = Answer::MySqlDBGuard::query(&db, mySql);
    Answer::MySqlQuery::MySqlQuery(&result_1, v5);
    if ( Answer::MySqlQuery::eof(&result_1) )
    {
      memset(mySql_0, 0, sizeof(mySql_0));
      snprintf(
        mySql_0,
        0x3FFu,
        "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('RATE_VALUE','%d')",
        this->m_Rate);
    }
    else
    {
      memset(mySql_0, 0, sizeof(mySql_0));
      snprintf(mySql_0, 0x3FFu, "UPDATE `sys_server_config` SET `value`= %d WHERE `name`='RATE_VALUE'", this->m_Rate);
    }
    Answer::MySqlDBGuard::excute(&db, mySql_0);
    Answer::MySqlQuery::~MySqlQuery(&result_1);
    Answer::MySqlDBGuard::~MySqlDBGuard(&db);
  }
}


#####################################
void __cdecl CGuiGuDaoRen::SaveRecordToDB(CGuiGuDaoRen *const this)
{
  Answer::DBPool *v1; // rax
  int32_t nTime; // r14d
  int32_t nSuccess; // r13d
  int32_t nGiveId; // r12d
  int32_t nCostId; // r15d
  RongHeRecord *v6; // rax
  const char *v7; // rbx
  RongHeRecord *v8; // rax
  char szSQL[4096]; // [rsp+30h] [rbp-1080h] BYREF
  Answer::MySqlDBGuard db; // [rsp+1030h] [rbp-80h] BYREF
  std::_List_iterator<RongHeRecord> it; // [rsp+1060h] [rbp-50h] BYREF
  std::_List_iterator<RongHeRecord> __x; // [rsp+1070h] [rbp-40h] BYREF

  Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "SaveRecordToDB-1\n");
  v1 = Answer::Singleton<Answer::DBPool>::instance();
  Answer::MySqlDBGuard::MySqlDBGuard(&db, v1);
  Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "SaveRecordToDB-3\n");
  qmemcpy(szSQL, "TRUNCATE mem_rong_he_rec", 24);
  *(_QWORD *)&szSQL[24] = &loc_64726F;
  memset(&szSQL[32], 0, 0xFE0u);
  Answer::MySqlDBGuard::excute(&db, szSQL);
  for ( it._M_node = std::list<RongHeRecord>::begin(&this->m_RongHeRecordList)._M_node;
        ;
        std::_List_iterator<RongHeRecord>::operator++(&it) )
  {
    __x._M_node = std::list<RongHeRecord>::end(&this->m_RongHeRecordList)._M_node;
    if ( !std::_List_iterator<RongHeRecord>::operator!=(&it, &__x) )
      break;
    bzero(szSQL, 0x1000u);
    nTime = std::_List_iterator<RongHeRecord>::operator->(&it)->nTime;
    nSuccess = std::_List_iterator<RongHeRecord>::operator->(&it)->nSuccess;
    nGiveId = std::_List_iterator<RongHeRecord>::operator->(&it)->nGiveId;
    nCostId = std::_List_iterator<RongHeRecord>::operator->(&it)->nCostId;
    v6 = std::_List_iterator<RongHeRecord>::operator->(&it);
    v7 = (const char *)std::string::c_str(&v6->strName);
    v8 = std::_List_iterator<RongHeRecord>::operator->(&it);
    snprintf(
      szSQL,
      0xFFFu,
      "INSERT INTO mem_rong_he_record ( cid, name, cost_id,give_id,success, time ) VALUES (%lld, '%s',%d,%d, %d,%d) ",
      v8->nCid,
      v7,
      nCostId,
      nGiveId,
      nSuccess,
      nTime);
    Answer::MySqlDBGuard::excute(&db, szSQL);
  }
  Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_INFO, "SaveRecordToDB\n");
  Answer::MySqlDBGuard::~MySqlDBGuard(&db);
}


