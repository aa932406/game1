// Decompiled methods for class: CTerritory
// Source: gameserver.cc
// Total methods: 8

#####################################
void __cdecl CTerritory::~CTerritory(CTerritory *const this)
{
  CTerritory::~CTerritory(this);
  operator delete(this);
}


#####################################
void __cdecl CTerritory::removePlayer(CTerritory *const this, Player *player, bool islogout)
{
  if ( player )
    Map::removePlayer(this, player, islogout);
}


#####################################
void __cdecl CTerritory::reset(CTerritory *const this)
{
  GameService *v1; // rax
  CPoolManager *v2; // rax
  CPoolManager *v3; // rax
  CPoolManager *v4; // rax
  Trap *v5; // rbx
  CPoolManager *v6; // rax
  Npc *v7; // rbx
  CPoolManager *v8; // rax
  std::_List_iterator<Npc*> it_3; // [rsp+10h] [rbp-C0h] BYREF
  std::_List_iterator<Trap*> it_2; // [rsp+20h] [rbp-B0h] BYREF
  std::_List_iterator<CDropItem*> it_1; // [rsp+30h] [rbp-A0h] BYREF
  std::_List_iterator<Plant*> it_0; // [rsp+40h] [rbp-90h] BYREF
  std::_List_iterator<Monster*> it; // [rsp+50h] [rbp-80h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+60h] [rbp-70h] BYREF
  std::_List_iterator<Plant*> v15; // [rsp+70h] [rbp-60h] BYREF
  std::_List_iterator<CDropItem*> v16; // [rsp+80h] [rbp-50h] BYREF
  std::_List_iterator<Trap*> v17; // [rsp+90h] [rbp-40h] BYREF
  std::_List_iterator<Npc*> v18; // [rsp+A0h] [rbp-30h] BYREF
  Monster *monster; // [rsp+A8h] [rbp-28h]
  Plant *plant; // [rsp+B0h] [rbp-20h]
  CDropItem *pDropItem; // [rsp+B8h] [rbp-18h]

  std::list<Player *>::clear(&this->m_players);
  for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    monster = *std::_List_iterator<Monster *>::operator*(&it);
    if ( monster )
    {
      v1 = Answer::Singleton<GameService>::instance();
      GameService::removeMonster(v1, monster);
      v2 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<Monster>(v2, monster);
    }
  }
  std::list<Monster *>::clear(&this->m_monsters);
  for ( it_0._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node; ; std::_List_iterator<Plant *>::operator++(&it_0) )
  {
    v15._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
    if ( !std::_List_iterator<Plant *>::operator!=(&it_0, &v15) )
      break;
    plant = *std::_List_iterator<Plant *>::operator*(&it_0);
    if ( plant )
    {
      v3 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<Plant>(v3, plant);
    }
  }
  std::list<Plant *>::clear(&this->m_plants);
  for ( it_1._M_node = std::list<CDropItem *>::begin(&this->m_dropItems)._M_node;
        ;
        std::_List_iterator<CDropItem *>::operator++(&it_1) )
  {
    v16._M_node = std::list<CDropItem *>::end(&this->m_dropItems)._M_node;
    if ( !std::_List_iterator<CDropItem *>::operator!=(&it_1, &v16) )
      break;
    pDropItem = *std::_List_iterator<CDropItem *>::operator*(&it_1);
    if ( pDropItem )
    {
      v4 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<CDropItem>(v4, pDropItem);
    }
  }
  std::list<CDropItem *>::clear(&this->m_dropItems);
  for ( it_2._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node; ; std::_List_iterator<Trap *>::operator++(&it_2) )
  {
    v17._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
    if ( !std::_List_iterator<Trap *>::operator!=(&it_2, &v17) )
      break;
    v5 = *std::_List_iterator<Trap *>::operator*(&it_2);
    v6 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<Trap>(v6, v5);
  }
  std::list<Trap *>::clear(&this->m_traps);
  for ( it_3._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it_3) )
  {
    v18._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it_3, &v18) )
      break;
    v7 = *std::_List_iterator<Npc *>::operator*(&it_3);
    v8 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<Npc>(v8, v7);
  }
  std::list<Npc *>::clear(&this->m_npcs);
  this->m_FamilyId = 0;
  this->m_Piglet = 0;
}


#####################################
void __cdecl CTerritory::init(
        CTerritory *const this,
        CMapRunner *pRunner,
        const CfgMap *const cfgmap,
        FamilyId_t FamilyId)
{
  this->m_FamilyId = FamilyId;
  Map::init(this, pRunner, cfgmap);
  CTerritory::AddFamilyMonster(this, 1);
}


#####################################
void __cdecl CTerritory::AddFamilyMonster(CTerritory *const this, bool bInit)
{
  FamilyId_t m_FamilyId; // rbx
  FamilyManager *v3; // rsi
  void (__fastcall *v4)(Monster *, _QWORD); // rbx
  int v5; // eax
  CfgData *v6; // rax
  const CfgFamilyTable *FamilyTable; // rax
  int32_t BossMid; // ebx
  CfgData *v9; // rax
  CPoolManager *v10; // rax
  CfgData *v11; // rax
  FamilyInfo FamilyStu; // [rsp+10h] [rbp-D0h] BYREF
  CfgMapMonster MapMonster; // [rsp+80h] [rbp-60h] BYREF
  std::vector<AttrAddon> vAttrAddon; // [rsp+A0h] [rbp-40h] BYREF
  const CfgFamilyBoss *pFamilyBoss; // [rsp+B8h] [rbp-28h]
  CfgMonster *pCfgMonster; // [rsp+C0h] [rbp-20h]
  Monster *monster; // [rsp+C8h] [rbp-18h]

  m_FamilyId = this->m_FamilyId;
  v3 = Answer::Singleton<FamilyManager>::instance();
  FamilyManager::GetFamilyInfo(&FamilyStu, v3, m_FamilyId);
  if ( bInit && FamilyStu.nBossState == 1 || !bInit && FamilyStu.nBossState == 3 )
  {
    if ( this->m_Piglet )
    {
      Monster::leaveMap(this->m_Piglet);
      v4 = (void (__fastcall *)(Monster *, _QWORD))*((_QWORD *)this->m_Piglet->_vptr_Entity + 21);
      v5 = (*((__int64 (__fastcall **)(Monster *))this->m_Piglet->_vptr_Entity + 19))(this->m_Piglet);
      v4(this->m_Piglet, (unsigned int)-v5);
      Monster::SetReviveTime(this->m_Piglet, 0);
      LODWORD(v4) = FamilyStu.nLevel;
      v6 = Answer::Singleton<CfgData>::instance();
      FamilyTable = CfgData::GetFamilyTable(v6);
      pFamilyBoss = CfgFamilyTable::GetFamilyBoss(FamilyTable, (int32_t)v4, 0);
      if ( pFamilyBoss )
      {
        BossMid = pFamilyBoss->BossMid;
        v9 = Answer::Singleton<CfgData>::instance();
        pCfgMonster = CfgData::getMonster(v9, BossMid);
        if ( pCfgMonster )
        {
          v10 = Answer::Singleton<CPoolManager>::instance();
          monster = CPoolManager::pop<Monster>(v10);
          if ( monster )
          {
            memset(&MapMonster, 0, sizeof(MapMonster));
            v11 = Answer::Singleton<CfgData>::instance();
            MapMonster.id = CfgData::GetMapMonsterId(v11);
            MapMonster.mapid = Map::GetMapId(this);
            MapMonster.x = StaticObj::GetPosX(this->m_Piglet);
            MapMonster.y = StaticObj::GetPosY(this->m_Piglet);
            std::vector<AttrAddon>::vector(&vAttrAddon);
            Monster::init(monster, pCfgMonster, &MapMonster, MonsterState::MS_STAND, &vAttrAddon);
            std::vector<AttrAddon>::~vector(&vAttrAddon);
            (*((void (__fastcall **)(CTerritory *const, Monster *, _QWORD, _QWORD))this->_vptr_Map + 28))(
              this,
              monster,
              (unsigned int)MapMonster.x,
              (unsigned int)MapMonster.y);
          }
        }
      }
    }
  }
  FamilyInfo::~FamilyInfo(&FamilyStu);
}


#####################################
void __cdecl CTerritory::addPlayer(CTerritory *const this, Player *player, int32_t x, int32_t y)
{
  if ( player )
    Map::addPlayer(this, player, x, y);
}


#####################################
void __cdecl CTerritory::addMonster(CTerritory *const this, Monster *monster, int32_t x, int32_t y)
{
  std::string p_strFamilyName; // [rsp+20h] [rbp-20h] BYREF
  _BYTE v7[17]; // [rsp+2Fh] [rbp-11h] BYREF

  if ( monster )
  {
    if ( Monster::getMid(monster) == 50001 )
    {
      this->m_Piglet = monster;
      std::allocator<char>::allocator(v7);
      std::string::string(&p_strFamilyName, &unk_8F22A0);
      Monster::SetFamilyId(this->m_Piglet, this->m_FamilyId, &p_strFamilyName);
      std::string::~string(&p_strFamilyName);
      std::allocator<char>::~allocator(v7);
    }
    Map::addMonster(this, monster, x, y);
  }
}


#####################################
void __cdecl CTerritory::onMonsterDie(CTerritory *const this, Monster *monster, Player *player, bool IsGroupMonster)
{
  int32_t Mid; // ebx
  CfgData *v5; // rax
  const CfgFamilyTable *FamilyTable; // rax
  int32_t Now; // eax
  FamilyId_t m_FamilyId; // rbx
  FamilyManager *v9; // rax
  int8_t ConnId; // bl
  GameService *v11; // rax
  int32_t GateIndex; // edx
  uint32_t WOffset; // edx
  int8_t v14; // bl
  GameService *v15; // rax
  const CfgFamilyBoss *pFamilyBoss; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( monster )
  {
    Mid = Monster::getMid(monster);
    v5 = Answer::Singleton<CfgData>::instance();
    FamilyTable = CfgData::GetFamilyTable(v5);
    pFamilyBoss = CfgFamilyTable::GetFamilyBoss(FamilyTable, 0, Mid);
    if ( pFamilyBoss )
    {
      if ( this->m_Piglet )
      {
        Now = Unit::getNow(monster);
        Monster::SetReviveTime(this->m_Piglet, Now + 10);
      }
      Monster::setDelFlg(monster);
      Map::AddContribution(this, 500, CURRENCY_CHANGE_REASON::GCR_KILL_PIG);
      m_FamilyId = this->m_FamilyId;
      v9 = Answer::Singleton<FamilyManager>::instance();
      FamilyManager::SendSocialFinishBoss(v9, m_FamilyId, 0, 1);
      if ( player )
      {
        ConnId = Player::getConnId(player);
        v11 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v11, ConnId, Answer::PackType::PACK_DISPATCH, 0x4E9Bu);
        if ( packet )
        {
          GateIndex = Player::getGateIndex(player);
          Answer::NetPacket::writeInt32(packet, GateIndex);
          Answer::NetPacket::writeInt8(packet, 4);
          Answer::NetPacket::writeInt32(packet, pFamilyBoss->FamilyExp);
          Answer::NetPacket::writeInt32(packet, pFamilyBoss->GongGaoId);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v14 = Player::getConnId(player);
          v15 = Answer::Singleton<GameService>::instance();
          GameService::sendPacket(v15, v14, packet);
        }
      }
    }
    Map::onMonsterDie(this, monster, player, IsGroupMonster);
  }
}


