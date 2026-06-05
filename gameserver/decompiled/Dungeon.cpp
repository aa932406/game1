// Decompiled methods for class: Dungeon
// Source: gameserver.cc
// Total methods: 80

#####################################
void __cdecl Dungeon::~Dungeon(Dungeon *const this)
{
  Dungeon::~Dungeon(this);
  operator delete(this);
}


#####################################
void __cdecl Dungeon::init(
        Dungeon *const this,
        CMapRunner *pRunner,
        const CfgDungeon *const cfgDungeon,
        const CfgMap *const cfgmap,
        int32_t nId)
{
  int64_t Tick; // rbx
  int32_t id; // r12d
  CfgData *v7; // rax
  const CfgMapEventList *DungeonEvent; // rax
  Answer::Random *v9; // rax

  Map::init(this, pRunner, cfgmap);
  Tick = Map::getTick(this);
  id = cfgDungeon->id;
  v7 = Answer::Singleton<CfgData>::instance();
  DungeonEvent = CfgData::getDungeonEvent(v7, id);
  IMapEvent::init(&this->IMapEvent, DungeonEvent, Tick);
  CfgDungeon::operator=(&this->m_cfgDungeon, cfgDungeon);
  this->m_state = DungeonState::DS_FREE;
  this->m_nId = nId;
  v9 = Answer::Singleton<Answer::Random>::instance();
  this->m_Random = Answer::Random::generate(v9, 1, 5);
}


#####################################
void __cdecl Dungeon::addPlayer(Dungeon *const this, Player *player, int32_t x, int32_t y)
{
  int32_t task_id; // ebx
  ChrTask *Task; // rax
  CharId_t cid; // rbx
  int8_t ConnId; // bl
  GameService *v8; // rax
  CharId_t v9; // rax
  uint32_t WOffset; // eax
  int8_t v11; // bl
  GameService *v12; // rax
  int8_t v13; // bl
  GameService *v14; // rax
  int32_t v15; // eax
  int *v16; // rax
  uint32_t v17; // eax
  int16_t GateIndex; // r12
  int8_t v19; // bl
  GameService *v20; // rax
  int32_t BuffId; // ebx
  CfgData *v22; // rax
  int32_t v23; // edx
  Buff *v24; // rbx
  int32_t id; // ebx
  ChrTask *v26; // rax
  std::_List_iterator<int> it; // [rsp+30h] [rbp-D0h] BYREF
  DamageSum dmg; // [rsp+40h] [rbp-C0h] BYREF
  std::_List_iterator<DamageSum> eiter; // [rsp+60h] [rbp-A0h] BYREF
  std::_List_iterator<DamageSum> iter; // [rsp+70h] [rbp-90h] BYREF
  _BYTE v31[16]; // [rsp+80h] [rbp-80h] BYREF
  std::string val; // [rsp+90h] [rbp-70h] BYREF
  std::_List_iterator<int> __x; // [rsp+A0h] [rbp-60h] BYREF
  UnitHandle launcher; // [rsp+B0h] [rbp-50h] BYREF
  Answer::NetPacket *packet; // [rsp+C0h] [rbp-40h]
  Answer::NetPacket *packet_0; // [rsp+C8h] [rbp-38h]
  CfgBuff *cfgBuff; // [rsp+D0h] [rbp-30h]
  Buff *buff; // [rsp+D8h] [rbp-28h]

  if ( player )
  {
    Map::addPlayer(this, player, x, y);
    Dungeon::initPlayerInfo(this, player);
    Dungeon::broadcastDungeonInfo(this);
    if ( this->m_cfgDungeon.task_id > 0 )
    {
      task_id = this->m_cfgDungeon.task_id;
      Task = Player::GetTask(player);
      ChrTask::receive(Task, task_id);
    }
    switch ( this->m_cfgDungeon.type )
    {
      case 0xC:
        iter._M_node = std::list<DamageSum>::begin(&this->m_damages)._M_node;
        eiter._M_node = std::list<DamageSum>::end(&this->m_damages)._M_node;
        while ( std::_List_iterator<DamageSum>::operator!=(&iter, &eiter) )
        {
          cid = std::_List_iterator<DamageSum>::operator->(&iter)->cid;
          if ( cid == Player::getCid(player) )
            break;
          std::_List_iterator<DamageSum>::operator++(&iter);
        }
        if ( std::_List_iterator<DamageSum>::operator==(&iter, &eiter) )
        {
          DamageSum::DamageSum(&dmg);
          dmg.cid = Player::getCid(player);
          Player::getName((const Player *const)v31);
          std::string::operator=(&dmg.name, v31);
          std::string::~string(v31);
          dmg.damage = 0;
          std::list<DamageSum>::push_back(&this->m_damages, &dmg);
          DamageSum::~DamageSum(&dmg);
        }
        this->m_needBroadcastDamage = 1;
        break;
      case 0x11:
        if ( this->m_cfgDungeon.star > 11 )
        {
          ConnId = Player::getConnId(player);
          v8 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v8, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( !packet )
            return;
          Answer::NetPacket::writeInt32(packet, 1);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          v9 = Player::getCid(player);
          Answer::NetPacket::writeInt64(packet, v9);
          Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.star);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v11 = Player::getConnId(player);
          v12 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v12, v11, packet);
        }
        break;
      case 0x23:
        v13 = Player::getConnId(player);
        v14 = Answer::Singleton<GameService>::instance();
        packet_0 = GameService::popNetpacket(v14, v13, Answer::PackType::PACK_DISPATCH, 0x2D3Cu);
        if ( !packet_0 )
          return;
        Answer::NetPacket::writeInt32(packet_0, this->m_cfgDungeon.id);
        Answer::NetPacket::writeInt32(packet_0, this->m_Random);
        v15 = std::list<int>::size(&this->m_RandomList);
        Answer::NetPacket::writeInt32(packet_0, v15);
        for ( it._M_node = std::list<int>::begin(&this->m_RandomList)._M_node;
              ;
              std::_List_iterator<int>::operator++(&it, 0) )
        {
          __x._M_node = std::list<int>::end(&this->m_RandomList)._M_node;
          if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
            break;
          v16 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet_0, *v16);
        }
        v17 = Answer::NetPacket::getWOffset(packet_0);
        Answer::NetPacket::setSize(packet_0, v17);
        GateIndex = Player::getGateIndex(player);
        v19 = Player::getConnId(player);
        v20 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v20, v19, GateIndex, packet_0);
        break;
    }
    if ( this->m_cfgDungeon.BuffId > 0 )
    {
      BuffId = this->m_cfgDungeon.BuffId;
      v22 = Answer::Singleton<CfgData>::instance();
      cfgBuff = CfgData::getBuff(v22, BuffId);
      if ( cfgBuff )
      {
        launcher.id = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 12))(player);
        launcher.type = v23;
        v24 = (Buff *)operator new(0x60u);
        Buff::Buff(v24, player, cfgBuff, &launcher, 2, 0);
        buff = v24;
        if ( v24 )
          Unit::addBuff(player, buff);
      }
    }
    id = this->m_cfgDungeon.id;
    v26 = Player::GetTask(player);
    ChrTask::updateTaskCount(v26, 30, id);
  }
}


#####################################
void __cdecl Dungeon::AddRandomList(Dungeon *const this, Player *player, int32_t nIndex)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  int32_t nIndexa; // [rsp+Ch] [rbp-34h] BYREF
  Player *playera; // [rsp+10h] [rbp-30h]
  Dungeon *thisa; // [rsp+18h] [rbp-28h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  thisa = this;
  playera = player;
  nIndexa = nIndex;
  if ( player )
  {
    std::list<int>::push_back(&thisa->m_RandomList, &nIndexa);
    ConnId = Player::getConnId(playera);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D3Du);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, thisa->m_cfgDungeon.id);
      Answer::NetPacket::writeInt32(packet, nIndexa);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(playera);
      v7 = Player::getConnId(playera);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Dungeon::OnRandomPos(Dungeon *const this, Player *player)
{
  int32_t DungeonId; // ebx
  CfgData *v3; // rax
  BaoKuFuBen *pBaoKuFuBen; // [rsp+10h] [rbp-20h]
  int RandIndex; // [rsp+1Ch] [rbp-14h]

  if ( player )
  {
    DungeonId = Dungeon::getDungeonId(this);
    v3 = Answer::Singleton<CfgData>::instance();
    pBaoKuFuBen = CfgData::GetBaoKuFuBen(v3, DungeonId);
    if ( pBaoKuFuBen )
    {
      if ( this->m_BuyRandomTimes * pBaoKuFuBen->AddTimes + pBaoKuFuBen->InitCount > this->m_RandomTimes )
      {
        RandIndex = Dungeon::RandPosIndex(this, player);
        if ( RandIndex > 0 )
        {
          ++this->m_RandomTimes;
          Dungeon::AddRandomList(this, player, RandIndex);
          Dungeon::broadcastDungeonInfo(this);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl Dungeon::RandPosIndex(Dungeon *const this, Player *player)
{
  CfgData *v3; // rax
  int32_t m_MaxRanomParam; // ebx
  int32_t v5; // ebx
  Answer::Random *v6; // rax
  std::pair<const int,BaoKuRandom> *v7; // rax
  int v8; // ebx
  CExtCharBag *Bag; // rax
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v12; // rax
  int8_t v13; // bl
  GameService *v14; // rax
  std::pair<const int,BaoKuRandom> *v15; // rax
  CharId_t v16; // rax
  uint32_t WOffset; // eax
  int8_t v18; // bl
  GameService *v19; // rax
  int32_t YValue; // r12d
  int32_t XValue; // ebx
  std::pair<const int,BaoKuRandom> *v22; // rax
  MemChrBag Stu; // [rsp+20h] [rbp-F0h] BYREF
  std::_List_iterator<int> itList; // [rsp+40h] [rbp-D0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BaoKuRandom> > it_0; // [rsp+50h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BaoKuRandom> > it; // [rsp+60h] [rbp-B0h] BYREF
  BaoKuRandomMap __x; // [rsp+70h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BaoKuRandom> > v28; // [rsp+A0h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,BaoKuRandom> > v29; // [rsp+B0h] [rbp-60h] BYREF
  std::_List_iterator<int> v30; // [rsp+C0h] [rbp-50h] BYREF
  std::string Param; // [rsp+D0h] [rbp-40h] BYREF
  char v32; // [rsp+DFh] [rbp-31h] BYREF
  std::string val; // [rsp+E0h] [rbp-30h] BYREF
  int32_t Index; // [rsp+ECh] [rbp-24h]
  int32_t nRandom; // [rsp+F0h] [rbp-20h]
  bool InList; // [rsp+F7h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+F8h] [rbp-18h]

  if ( this->m_Random <= 0 || this->m_Random > 5 )
    return 0;
  if ( !this->m_MaxRanomParam )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    CfgData::GetBaoKuRandomMap(&__x, v3);
    std::map<int,BaoKuRandom>::operator=(&this->m_RandomMap, &__x);
    std::map<int,BaoKuRandom>::~map(&__x);
    for ( it_0._M_node = std::map<int,BaoKuRandom>::begin(&this->m_RandomMap)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator++(&it_0, 0) )
    {
      v28._M_node = std::map<int,BaoKuRandom>::end(&this->m_RandomMap)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator!=(&it_0, &v28) )
        break;
      m_MaxRanomParam = this->m_MaxRanomParam;
      this->m_MaxRanomParam = m_MaxRanomParam
                            + *(&std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it_0)->second.XValue
                              + 6 * this->m_Random);
    }
  }
  if ( this->m_MaxRanomParam <= 0 )
    return 0;
  Index = 0;
  v5 = this->m_MaxRanomParam;
  v6 = Answer::Singleton<Answer::Random>::instance();
  nRandom = Answer::Random::generate(v6, 1, v5);
  for ( it._M_node = std::map<int,BaoKuRandom>::begin(&this->m_RandomMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator++(&it, 0) )
  {
    v29._M_node = std::map<int,BaoKuRandom>::end(&this->m_RandomMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator!=(&it, &v29) )
      break;
    v7 = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it);
    if ( *(&v7->second.XValue + 6 * this->m_Random) >= nRandom )
    {
      memset(&Stu, 0, sizeof(Stu));
      Stu.itemId = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->second.Items[this->m_Random - 1].nItemId;
      Stu.itemCount = *((_DWORD *)&std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->first
                      + 6 * this->m_Random);
      Stu.itemClass = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->second.Items[this->m_Random - 1].nItemClass;
      Stu.bind = *((_BYTE *)&std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->second.Index
                 + 24 * this->m_Random);
      InList = 0;
      for ( itList._M_node = std::list<int>::begin(&this->m_RandomList)._M_node;
            ;
            std::_List_iterator<int>::operator++(&itList, 0) )
      {
        v30._M_node = std::list<int>::end(&this->m_RandomList)._M_node;
        if ( !std::_List_iterator<int>::operator!=(&itList, &v30) )
          break;
        v8 = *std::_List_iterator<int>::operator*(&itList);
        if ( v8 == std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->first )
          InList = 1;
      }
      if ( !InList && Stu.itemId > 0 )
      {
        Bag = Player::GetBag(player);
        if ( !CExtCharBag::AddItem(Bag, &Stu, ITEM_CHANGE_REASON::IDCR_DUNGEON_RANDOM) )
        {
          std::allocator<char>::allocator(&v32);
          std::string::string(&Param, &unk_8D658F, &v32);
          Cid = Player::getCid(player);
          ConnId = Player::getConnId(player);
          v12 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v12, ConnId, Cid, 1, &Stu, ITEM_CHANGE_REASON::IDCR_DUNGEON_RANDOM, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v32);
        }
        if ( std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->second.Items[this->m_Random - 1].nGongGaoId > 0 )
        {
          v13 = Player::getConnId(player);
          v14 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v14, v13, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( !packet )
            return 10002;
          v15 = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it);
          Answer::NetPacket::writeInt32(packet, v15->second.Items[this->m_Random - 1].nGongGaoId);
          Player::getName((const Player *const)&val);
          Answer::NetPacket::writeUTF8(packet, &val);
          std::string::~string(&val);
          v16 = Player::getCid(player);
          Answer::NetPacket::writeInt64(packet, v16);
          Answer::NetPacket::writeInt32(packet, Stu.itemId);
          Answer::NetPacket::writeInt32(packet, Stu.itemCount);
          Answer::NetPacket::writeInt32(packet, Stu.itemClass);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          v18 = Player::getConnId(player);
          v19 = Answer::Singleton<GameService>::instance();
          GameService::worldBroadcast(v19, v18, packet);
        }
      }
      YValue = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->second.YValue;
      XValue = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->second.XValue;
      Unit::instantMove(player, XValue, YValue, InstanceMoveReason::IMR_FU_BEN, 0);
      return std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it)->first;
    }
    v22 = std::_Rb_tree_iterator<std::pair<int const,BaoKuRandom>>::operator->(&it);
    nRandom -= *(&v22->second.XValue + 6 * this->m_Random);
  }
  return Index;
}


#####################################
void __cdecl Dungeon::OnBuyRandomPosTimes(Dungeon *const this, Player *player)
{
  int32_t DungeonId; // ebx
  CfgData *v3; // rax
  BaoKuFuBen *pBaoKuFuBen; // [rsp+18h] [rbp-18h]

  if ( player )
  {
    DungeonId = Dungeon::getDungeonId(this);
    v3 = Answer::Singleton<CfgData>::instance();
    pBaoKuFuBen = CfgData::GetBaoKuFuBen(v3, DungeonId);
    if ( pBaoKuFuBen )
    {
      if ( this->m_BuyRandomTimes < pBaoKuFuBen->BuyCount
        && pBaoKuFuBen->Gold > 0
        && this->m_BuyRandomTimes >= 0
        && Player::DecCurrency(
             player,
             CURRENCY_TYPE::CURRENCY_GOLD,
             (this->m_BuyRandomTimes + 1) * pBaoKuFuBen->Gold,
             CURRENCY_CHANGE_REASON::GCR_BUY_RANDOM_DUNGEON_TIMES,
             0) )
      {
        ++this->m_BuyRandomTimes;
        Dungeon::broadcastDungeonInfo(this);
      }
    }
  }
}


#####################################
void __cdecl Dungeon::update(Dungeon *const this)
{
  int64_t Tick; // rax
  int64_t v2; // rbx
  int32_t RunnerId; // ebx
  MapManager *v5; // rax
  std::_List_iterator<Player*> it; // [rsp+20h] [rbp-80h] BYREF
  PlayerList players_0; // [rsp+30h] [rbp-70h] BYREF
  std::_List_iterator<Player*> eiter; // [rsp+40h] [rbp-60h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+50h] [rbp-50h] BYREF
  PlayerList players; // [rsp+60h] [rbp-40h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+70h] [rbp-30h] BYREF
  int64_t curTick; // [rsp+78h] [rbp-28h]
  Player *player; // [rsp+80h] [rbp-20h]
  Player *player_0; // [rsp+88h] [rbp-18h]

  if ( this->m_state )
  {
    curTick = Map::getTick(this);
    switch ( this->m_state )
    {
      case DungeonState::DS_WAIT:
        if ( curTick - this->m_stateTick >= 1000 * this->m_stateParam )
        {
          if ( this->m_cfgDungeon.type == 12 )
            Dungeon::teamDungeonMemberEnter(this);
          Dungeon::setState(this, DungeonState::DS_RUNNING, 0);
          if ( !std::list<int>::empty(&this->m_waitEvent) )
          {
            Tick = Map::getTick(this);
            IMapEvent::openEvents(&this->IMapEvent, &this->m_waitEvent, Tick);
            std::list<int>::clear(&this->m_waitEvent);
          }
        }
        break;
      case DungeonState::DS_RUNNING:
        Dungeon::checkAddMonster(this, curTick);
        (*((void (__fastcall **)(Dungeon *const))this->_vptr_Map + 31))(this);
        v2 = curTick - this->m_stateTick;
        if ( v2 >= 1000 * Dungeon::GetDurationTime(this) )
        {
          Dungeon::clearMonster(this);
          if ( Dungeon::getDungeonType(this) == 19 )
            goto LABEL_16;
          Dungeon::fail(this, 0);
        }
        break;
      case DungeonState::DS_SUMMON:
        if ( curTick - this->m_stateTick >= 1000 * this->m_stateParam )
          goto LABEL_16;
        goto LABEL_14;
      case DungeonState::DS_BOSS:
        if ( curTick - this->m_stateTick < 1000 * this->m_stateParam )
LABEL_14:
          Dungeon::checkSummonBoss(this);
        else
LABEL_16:
          Dungeon::win(this, 0);
        break;
      case DungeonState::DS_WIN:
        if ( curTick - this->m_stateTick >= 1000 * this->m_stateParam )
        {
          std::list<Player *>::list(&players, &this->m_players);
          if ( !std::list<Player *>::empty(&players) )
          {
            iter._M_node = std::list<Player *>::begin(&players)._M_node;
            eiter._M_node = std::list<Player *>::end(&players)._M_node;
            while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
            {
              player = *std::_List_iterator<Player *>::operator*(&iter);
              if ( player )
              {
                if ( Dungeon::getDungeonType(this) == 15 && Player::GetSysSettingInfo(player, 5)
                  || Dungeon::getDungeonType(this) == 23 && Player::GetSysSettingInfo(player, 6) )
                {
                  Dungeon::GetReward(this, player, 2, 1);
                }
                else
                {
                  Dungeon::GetReward(this, player, 1, 0);
                }
              }
              std::_List_iterator<Player *>::operator++(&iter);
            }
          }
          Dungeon::setState(this, DungeonState::DS_RESET, 0);
          std::list<Player *>::~list(&players);
        }
        break;
      case DungeonState::DS_FAIL:
        if ( curTick - this->m_stateTick >= 1000 * this->m_stateParam )
          Dungeon::setState(this, DungeonState::DS_RESET, 0);
        break;
      case DungeonState::DS_RESET:
        if ( !std::list<Player *>::empty(&this->m_players) )
        {
          std::list<Player *>::list(&players_0, &this->m_players);
          for ( it._M_node = std::list<Player *>::begin(&players_0)._M_node;
                ;
                std::_List_iterator<Player *>::operator++(&it) )
          {
            __x._M_node = std::list<Player *>::end(&players_0)._M_node;
            if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
              break;
            player_0 = *std::_List_iterator<Player *>::operator*(&it);
            if ( player_0 )
            {
              Player::leaveDungeon(player_0);
              Dungeon::sendDungeonResult(this, player_0, this->m_stateParam);
            }
          }
          std::list<Player *>::~list(&players_0);
        }
        (*((void (__fastcall **)(Dungeon *const))this->_vptr_Map + 29))(this);
        RunnerId = Map::GetRunnerId(this);
        v5 = Answer::Singleton<MapManager>::instance();
        MapManager::PostMsg(v5, RunnerId, GameMsgCode::GMC_DEL_DUNGEON, this, 0, 0, 0, 0);
        break;
      default:
        break;
    }
    Dungeon::checkRevive(this, curTick);
    Dungeon::checkBroadcastDamageList(this);
    Map::update(this);
  }
  else
  {
    Map::update(this);
  }
}


#####################################
void __cdecl Dungeon::reset(Dungeon *const this)
{
  Monster *v1; // rax
  MonsterDungeon *v2; // rax
  MonsterDungeon *v3; // rbx
  GameService *v4; // rax
  CPoolManager *v5; // rax
  Plant *v6; // rax
  PlantDungeon *v7; // rax
  CPoolManager *v8; // rax
  CPoolManager *v9; // rax
  Trap *v10; // rbx
  CPoolManager *v11; // rax
  Npc *v12; // rbx
  CPoolManager *v13; // rax
  Answer::Random *v14; // rax
  std::_List_iterator<Npc*> it_3; // [rsp+10h] [rbp-C0h] BYREF
  std::_List_iterator<Trap*> it_2; // [rsp+20h] [rbp-B0h] BYREF
  std::_List_iterator<CDropItem*> it_1; // [rsp+30h] [rbp-A0h] BYREF
  std::_List_iterator<Plant*> it_0; // [rsp+40h] [rbp-90h] BYREF
  std::_List_iterator<Monster*> it; // [rsp+50h] [rbp-80h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+60h] [rbp-70h] BYREF
  std::_List_iterator<Plant*> v21; // [rsp+70h] [rbp-60h] BYREF
  std::_List_iterator<CDropItem*> v22; // [rsp+80h] [rbp-50h] BYREF
  std::_List_iterator<Trap*> v23; // [rsp+90h] [rbp-40h] BYREF
  std::_List_iterator<Npc*> v24; // [rsp+A0h] [rbp-30h] BYREF
  MonsterDungeon *monster; // [rsp+A8h] [rbp-28h]
  PlantDungeon *plant; // [rsp+B0h] [rbp-20h]
  CDropItem *pDropItem; // [rsp+B8h] [rbp-18h]

  std::list<Player *>::clear(&this->m_players);
  for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    v1 = *std::_List_iterator<Monster *>::operator*(&it);
    if ( v1 )
      v2 = (MonsterDungeon *)__dynamic_cast(
                               v1,
                               (const struct __class_type_info *)&`typeinfo for'Monster,
                               (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                               0);
    else
      v2 = 0;
    monster = v2;
    if ( v2 )
    {
      v3 = monster;
      v4 = Answer::Singleton<GameService>::instance();
      GameService::removeMonster(v4, v3);
      v5 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<MonsterDungeon>(v5, monster);
    }
  }
  std::list<Monster *>::clear(&this->m_monsters);
  for ( it_0._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node; ; std::_List_iterator<Plant *>::operator++(&it_0) )
  {
    v21._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
    if ( !std::_List_iterator<Plant *>::operator!=(&it_0, &v21) )
      break;
    v6 = *std::_List_iterator<Plant *>::operator*(&it_0);
    if ( v6 )
      v7 = (PlantDungeon *)__dynamic_cast(
                             v6,
                             (const struct __class_type_info *)&`typeinfo for'Plant,
                             (const struct __class_type_info *)&`typeinfo for'PlantDungeon,
                             0);
    else
      v7 = 0;
    plant = v7;
    if ( v7 )
    {
      v8 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<PlantDungeon>(v8, plant);
    }
  }
  std::list<Plant *>::clear(&this->m_plants);
  for ( it_1._M_node = std::list<CDropItem *>::begin(&this->m_dropItems)._M_node;
        ;
        std::_List_iterator<CDropItem *>::operator++(&it_1) )
  {
    v22._M_node = std::list<CDropItem *>::end(&this->m_dropItems)._M_node;
    if ( !std::_List_iterator<CDropItem *>::operator!=(&it_1, &v22) )
      break;
    pDropItem = *std::_List_iterator<CDropItem *>::operator*(&it_1);
    if ( pDropItem )
    {
      v9 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<CDropItem>(v9, pDropItem);
    }
  }
  std::list<CDropItem *>::clear(&this->m_dropItems);
  for ( it_2._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node; ; std::_List_iterator<Trap *>::operator++(&it_2) )
  {
    v23._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
    if ( !std::_List_iterator<Trap *>::operator!=(&it_2, &v23) )
      break;
    v10 = *std::_List_iterator<Trap *>::operator*(&it_2);
    v11 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<Trap>(v11, v10);
  }
  std::list<Trap *>::clear(&this->m_traps);
  for ( it_3._M_node = std::list<Npc *>::begin(&this->m_npcs)._M_node; ; std::_List_iterator<Npc *>::operator++(&it_3) )
  {
    v24._M_node = std::list<Npc *>::end(&this->m_npcs)._M_node;
    if ( !std::_List_iterator<Npc *>::operator!=(&it_3, &v24) )
      break;
    v12 = *std::_List_iterator<Npc *>::operator*(&it_3);
    v13 = Answer::Singleton<CPoolManager>::instance();
    CPoolManager::push<Npc>(v13, v12);
  }
  std::list<Npc *>::clear(&this->m_npcs);
  IMapEvent::clear(&this->IMapEvent);
  bzero(&this->m_finshInfo, 0x20u);
  std::map<int,MonsterWave>::clear(&this->m_monsterWave);
  this->m_state = DungeonState::DS_FREE;
  this->m_stateTick = Map::getTick(this);
  this->m_stateParam = 0;
  std::list<Monster *>::clear(&this->m_buildTower);
  std::list<DungeonTower>::clear(&this->m_waitTower);
  std::list<MonsterWait>::clear(&this->m_waitMonster);
  std::list<DungeonReward>::clear(&this->m_playerReward);
  std::list<long>::clear(&this->m_memberList);
  std::list<DamageSum>::clear(&this->m_damages);
  this->m_needBroadcastDamage = 0;
  this->m_dRatio = 1.0;
  this->m_nAddonTime = 0;
  this->m_nStartTime = 0;
  std::list<Position>::clear(&this->m_lstStack);
  this->m_TeamLeaderId = 0;
  this->m_bFree = 0;
  std::list<SummBossInfo>::clear(&this->m_lSummonBoss);
  this->m_nSummStart = 0;
  this->m_nFamilyId = 0;
  std::map<int,int>::clear(&this->m_mSummonRecord);
  std::vector<MemChrBag>::clear(&this->m_vPickItems);
  this->m_nMonsterBuff = 0;
  this->m_nMonsterScore = 0;
  this->m_nLevel = 0;
  this->m_nHard = 0;
  this->m_nQuality = 0;
  this->m_nWinStar = 0;
  this->m_nGatherTims = 0;
  this->m_MaxnProbability = 0;
  std::vector<CLibraryItem>::clear(&this->m_LibraryRewardVector);
  this->m_bGetReward = 0;
  this->m_Times = 0;
  this->m_MoneyBuffLevel = 0;
  this->m_GoldBuffLevel = 0;
  v14 = Answer::Singleton<Answer::Random>::instance();
  this->m_Random = Answer::Random::generate(v14, 1, 5);
  std::list<int>::clear(&this->m_RandomList);
  this->m_RandomTimes = 0;
  this->m_BuyRandomTimes = 0;
  this->m_MaxRanomParam = 0;
  std::map<int,BaoKuRandom>::clear(&this->m_RandomMap);
}


#####################################
void __cdecl Dungeon::checkEvents(Dungeon *const this)
{
  CfgMapEvent *v1; // rax
  CfgMapEvent *v2; // rax
  void (__fastcall *v5)(Dungeon *const, CfgMapEvent *); // rbx
  CfgMapEvent *v6; // rdx
  std::_List_iterator<CfgMapEvent> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+20h] [rbp-20h] BYREF

  for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
        ;
        std::_List_iterator<CfgMapEvent>::operator++(&it) )
  {
    __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
    if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
      break;
    v1 = std::_List_iterator<CfgMapEvent>::operator->(&it);
    if ( CfgMapEvent::isOpen(v1) )
    {
      v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( !CfgMapEvent::isDone(v2)
        && (std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 1
         || std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 4
         || std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 6
         || std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 8) )
      {
        v5 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *))*((_QWORD *)this->_vptr_Map + 32);
        v6 = std::_List_iterator<CfgMapEvent>::operator*(&it);
        v5(this, v6);
      }
    }
  }
}


#####################################
void __cdecl Dungeon::checkEvent(Dungeon *const this, CfgMapEvent *const mapEvent)
{
  int64_t v3; // rbx
  int *v4; // rax
  std::pair<const int,MonsterWave> *v5; // rax
  int *v7; // rax
  std::pair<const int,MonsterWave> *v8; // rax
  int *v10; // rax
  std::pair<const int,MonsterWave> *v11; // rax
  int64_t Tick; // rbx
  int64_t v13; // rbx
  int32_t v15; // ebx
  int *v16; // rax
  int32_t v17; // ebx
  int *v18; // rax
  std::_List_iterator<Player*> it_2; // [rsp+10h] [rbp-C0h] BYREF
  Position ps2; // [rsp+20h] [rbp-B0h] BYREF
  Position ps1; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it_1; // [rsp+40h] [rbp-90h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it_0; // [rsp+50h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > __x; // [rsp+70h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v27; // [rsp+80h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v28; // [rsp+90h] [rbp-40h] BYREF
  std::_List_iterator<Player*> v29; // [rsp+A0h] [rbp-30h] BYREF
  int32_t nsize; // [rsp+ACh] [rbp-24h]
  int32_t count; // [rsp+B0h] [rbp-20h]
  int32_t i; // [rsp+B4h] [rbp-1Ch]
  Player *pPlayer; // [rsp+B8h] [rbp-18h]

  if ( CfgMapEvent::isOpen(mapEvent) && !CfgMapEvent::isDone(mapEvent) )
  {
    switch ( mapEvent->trigger_type )
    {
      case 1:
        if ( std::vector<int>::size(&mapEvent->trigger_param) == 1 )
        {
          v3 = Map::getTick(this) - mapEvent->nOpenTime;
          if ( v3 >= 1000 * *std::vector<int>::operator[](&mapEvent->trigger_param, 0) )
            (*((void (__fastcall **)(Dungeon *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 33))(
              this,
              mapEvent,
              0);
        }
        break;
      case 2:
        if ( std::vector<int>::size(&mapEvent->trigger_param) == 1 )
        {
          v4 = std::vector<int>::operator[](&mapEvent->trigger_param, 0);
          it._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, v4)._M_node;
          __x._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it, &__x) )
          {
            v5 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it);
            if ( !MonsterWave::alive(&v5->second) )
              (*((void (__fastcall **)(Dungeon *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 33))(
                this,
                mapEvent,
                0);
          }
        }
        break;
      case 4:
        if ( std::vector<int>::size(&mapEvent->trigger_param) == 2 )
        {
          v10 = std::vector<int>::operator[](&mapEvent->trigger_param, 0);
          it_1._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, v10)._M_node;
          v28._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
          if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it_1, &v28) )
          {
            v11 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_1);
            if ( !MonsterWave::alive(&v11->second) )
            {
              Tick = Map::getTick(this);
              v13 = Tick - std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_1)->second.startTime;
              if ( v13 <= 1000 * *std::vector<int>::operator[](&mapEvent->trigger_param, 1u) )
                (*((void (__fastcall **)(Dungeon *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 33))(
                  this,
                  mapEvent,
                  0);
            }
          }
        }
        break;
      case 6:
        if ( std::vector<int>::size(&mapEvent->trigger_param) == 4 )
        {
          v15 = *std::vector<int>::operator[](&mapEvent->trigger_param, 1u);
          v16 = std::vector<int>::operator[](&mapEvent->trigger_param, 0);
          Position::Position(&ps1, *v16, v15);
          v17 = *std::vector<int>::operator[](&mapEvent->trigger_param, 3u);
          v18 = std::vector<int>::operator[](&mapEvent->trigger_param, 2u);
          Position::Position(&ps2, *v18, v17);
          for ( it_2._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
                ;
                std::_List_iterator<Player *>::operator++(&it_2) )
          {
            v29._M_node = std::list<Player *>::end(&this->m_players)._M_node;
            if ( !std::_List_iterator<Player *>::operator!=(&it_2, &v29) )
              break;
            pPlayer = *std::_List_iterator<Player *>::operator*(&it_2);
            if ( pPlayer && Player::isInRectangle(pPlayer, ps1, ps2) )
              (*((void (__fastcall **)(Dungeon *const, CfgMapEvent *const, Player *))this->_vptr_Map + 33))(
                this,
                mapEvent,
                pPlayer);
          }
        }
        break;
      case 8:
        if ( std::vector<int>::size(&mapEvent->trigger_param) > 1 )
        {
          nsize = std::vector<int>::size(&mapEvent->trigger_param);
          if ( nsize > 0 )
          {
            count = 0;
            for ( i = 0; i < nsize; ++i )
            {
              v7 = std::vector<int>::operator[](&mapEvent->trigger_param, i);
              it_0._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, v7)._M_node;
              v27._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
              if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it_0, &v27) )
              {
                v8 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_0);
                if ( !MonsterWave::alive(&v8->second) )
                  ++count;
              }
            }
            if ( count == nsize )
              (*((void (__fastcall **)(Dungeon *const, CfgMapEvent *const, _QWORD))this->_vptr_Map + 33))(
                this,
                mapEvent,
                0);
          }
        }
        break;
      default:
        return;
    }
  }
}


#####################################
void __cdecl Dungeon::updateExpDungeonRank(Dungeon *const this)
{
  int32_t kill_count; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int32_t v3; // ebx
  CExtOperateLimit *v4; // rax
  std::_List_iterator<Player*> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+20h] [rbp-20h] BYREF
  Player *player; // [rsp+28h] [rbp-18h]

  for ( iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
        ;
        std::_List_iterator<Player *>::operator++(&iter) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&iter, &__x) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( player )
    {
      kill_count = this->m_finshInfo.kill_count;
      OperateLimit = Player::GetOperateLimit(player);
      if ( kill_count > CExtOperateLimit::GetLimitCount(OperateLimit, 1071) )
      {
        v3 = this->m_finshInfo.kill_count;
        v4 = Player::GetOperateLimit(player);
        CExtOperateLimit::UpdateLimitCount(v4, 1071, v3);
        Player::sendUpdateSocialPlayerInfo(player, PlayerInfoIndex::PII_EXP_DUNGEON_KILL, this->m_finshInfo.kill_count);
      }
    }
  }
}


#####################################
void __cdecl Dungeon::win(Dungeon *const this, int32_t nParam)
{
  CExtOperateLimit *OperateLimit; // rax
  int32_t star; // ebx
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  int32_t v6; // ebx
  DailyActivity *PlayerDailyActivity; // rax
  CExtCurrency *v8; // rax
  CExtCharBag *Bag; // rax
  int64_t costMoney; // rbx
  CExtCurrency *Currency; // rax
  int32_t Record; // eax
  int32_t group_id; // ebx
  CHuoYueDu *PlayerHuoYueDu; // rax
  int32_t id; // ebx
  CfgData *v16; // rax
  const CfgMYSJRewardTable *MYSJRewardTable; // rax
  CCardGroupBoxManager *v18; // rax
  CfgData *v19; // rax
  const CfgMYSJRewardTable *v20; // rax
  int32_t v21; // ebx
  CfgData *v22; // rax
  const CfgMYSJRewardTable *v23; // rax
  int32_t sequence; // ebx
  CFestivalDoubleEleven *v25; // rax
  CExtCharBag *v26; // rax
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v29; // rax
  int8_t v30; // bl
  GameService *v31; // rax
  int v32; // ebx
  CharId_t v33; // rax
  uint32_t WOffset; // eax
  int8_t v35; // bl
  GameService *v36; // rax
  const char *v37; // rax
  int8_t v38; // bl
  DBService *v39; // rax
  GameService *v40; // rax
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v42; // rax
  LogMoYuShiJieReward logReward; // [rsp+20h] [rbp-130h] BYREF
  MemChrBag item; // [rsp+60h] [rbp-F0h] BYREF
  MemChrBagVector vItem; // [rsp+80h] [rbp-D0h] BYREF
  std::_List_iterator<Player*> iter_0; // [rsp+A0h] [rbp-B0h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+B0h] [rbp-A0h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+C0h] [rbp-90h] BYREF
  std::_List_iterator<Player*> v49; // [rsp+D0h] [rbp-80h] BYREF
  std::string Param; // [rsp+E0h] [rbp-70h] BYREF
  char v51; // [rsp+EFh] [rbp-61h] BYREF
  std::string val; // [rsp+F0h] [rbp-60h] BYREF
  std::string v53; // [rsp+100h] [rbp-50h] BYREF
  Player *player; // [rsp+108h] [rbp-48h]
  int32_t nMaxFloor; // [rsp+114h] [rbp-3Ch]
  Player *player_0; // [rsp+118h] [rbp-38h]
  const CfgMYSJReward *pReward; // [rsp+120h] [rbp-30h]
  int32_t nGroupId; // [rsp+12Ch] [rbp-24h]
  int32_t nIndex; // [rsp+130h] [rbp-20h]
  int8_t nMail; // [rsp+137h] [rbp-19h]
  Answer::NetPacket *packet; // [rsp+138h] [rbp-18h]

  Dungeon::calWinStar(this);
  Dungeon::calWinReward(this);
  Dungeon::setCanSubmit(this);
  Dungeon::clearMonster(this);
  Dungeon::broadcastFinishDungon(this, nParam);
  Dungeon::signDungeonCompleted(this);
  Dungeon::setState(this, DungeonState::DS_WIN, this->m_cfgDungeon.reward_time);
  if ( Dungeon::getDungeonType(this) == 16 )
  {
    for ( iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&iter) )
    {
      __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&iter, &__x) )
        break;
      player = *std::_List_iterator<Player *>::operator*(&iter);
      if ( player )
      {
        OperateLimit = Player::GetOperateLimit(player);
        nMaxFloor = CExtOperateLimit::GetLimitCount(OperateLimit, 37211);
        star = this->m_cfgDungeon.star;
        v4 = Player::GetOperateLimit(player);
        CExtOperateLimit::UpdateLimitCount(v4, 37210, star);
        if ( this->m_cfgDungeon.star > nMaxFloor )
        {
          nMaxFloor = this->m_cfgDungeon.star;
          v5 = Player::GetOperateLimit(player);
          CExtOperateLimit::UpdateLimitCount(v5, 37211, nMaxFloor);
        }
        v6 = this->m_cfgDungeon.star;
        PlayerDailyActivity = Player::GetPlayerDailyActivity(player);
        DailyActivity::AddDungeonRecord(PlayerDailyActivity, 16, v6, nMaxFloor);
      }
    }
    return;
  }
  if ( Dungeon::getDungeonType(this) == 17 )
  {
    for ( iter_0._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&iter_0) )
    {
      v49._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&iter_0, &v49) )
        return;
      player_0 = *std::_List_iterator<Player *>::operator*(&iter_0);
      if ( player_0 )
      {
        if ( this->m_cfgDungeon.costMoney <= 0
          || (v8 = Player::GetCurrency(player_0), CExtCurrency::GetMoneyBindAndNoBind(v8) >= this->m_cfgDungeon.costMoney) )
        {
          if ( this->m_cfgDungeon.costGold <= 0
            || Player::GetCurrency(player_0, CURRENCY_TYPE::CURRENCY_GOLD) >= this->m_cfgDungeon.costGold )
          {
            if ( this->m_cfgDungeon.costItem.m_nCount <= 0
              || (Bag = Player::GetBag(player_0),
                  CExtCharBag::RemoveItem(Bag, &this->m_cfgDungeon.costItem, ITEM_CHANGE_REASON::ICR_ENETR_DUNGEON)) )
            {
              if ( this->m_cfgDungeon.costMoney <= 0
                || (costMoney = this->m_cfgDungeon.costMoney,
                    Currency = Player::GetCurrency(player_0),
                    CExtCurrency::DecMoneyAndNoBind(Currency, costMoney, CURRENCY_CHANGE_REASON::MCR_ENTER_DUNGEON, 0)) )
              {
                if ( this->m_cfgDungeon.costGold <= 0
                  || Player::DecCurrency(
                       player_0,
                       CURRENCY_TYPE::CURRENCY_GOLD,
                       this->m_cfgDungeon.costGold,
                       CURRENCY_CHANGE_REASON::GCR_ENTER_DUNGEON,
                       this->m_cfgDungeon.id) )
                {
                  Record = Player::getRecord(player_0, this->m_cfgDungeon.group_id);
                  Player::updateRecord(player_0, this->m_cfgDungeon.group_id, Record + 1);
                  group_id = this->m_cfgDungeon.group_id;
                  PlayerHuoYueDu = Player::GetPlayerHuoYueDu(player_0);
                  CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 2, group_id, 0);
                  pReward = 0;
                  id = this->m_cfgDungeon.id;
                  v16 = Answer::Singleton<CfgData>::instance();
                  MYSJRewardTable = CfgData::GetMYSJRewardTable(v16);
                  nGroupId = CfgMYSJRewardTable::GetGroupId(MYSJRewardTable, id);
                  if ( nGroupId <= 0 )
                  {
                    v21 = this->m_cfgDungeon.id;
                    v22 = Answer::Singleton<CfgData>::instance();
                    v23 = CfgData::GetMYSJRewardTable(v22);
                    pReward = CfgMYSJRewardTable::GetRandReward(v23, v21);
                  }
                  else
                  {
                    v18 = Answer::Singleton<CCardGroupBoxManager>::instance();
                    nIndex = CCardGroupBoxManager::GetCard(v18, nGroupId);
                    v19 = Answer::Singleton<CfgData>::instance();
                    v20 = CfgData::GetMYSJRewardTable(v19);
                    pReward = CfgMYSJRewardTable::GetReward(v20, nGroupId, nIndex);
                  }
                  if ( pReward )
                    break;
                }
              }
            }
          }
        }
      }
LABEL_35:
      ;
    }
    std::vector<MemChrBag>::vector(&vItem);
    memset(&item, 0, sizeof(item));
    item.itemClass = pReward->nClass;
    item.itemId = pReward->nId;
    item.itemCount = pReward->nCount;
    item.bind = pReward->nBind;
    std::vector<MemChrBag>::push_back(&vItem, &item);
    sequence = this->m_cfgDungeon.sequence;
    v25 = Answer::Singleton<CFestivalDoubleEleven>::instance();
    CFestivalDoubleEleven::AddMoYuShiJieDrop(v25, sequence, &vItem);
    nMail = 0;
    v26 = Player::GetBag(player_0);
    if ( !CExtCharBag::AddItem(v26, &vItem, ITEM_CHANGE_REASON::ICR_MYSJ_REWARD) )
    {
      nMail = 1;
      std::allocator<char>::allocator(&v51);
      std::string::string(&Param, &unk_8D658F, &v51);
      Cid = Player::getCid(player_0);
      ConnId = Player::getConnId(player_0);
      v29 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v29, ConnId, Cid, 6271, &vItem, ITEM_CHANGE_REASON::ICR_MYSJ_REWARD, &Param, 0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v51);
    }
    Dungeon::sendMoYuShiJieReward(this, player_0, item.itemId, item.itemClass, nMail, pReward->nShow);
    if ( pReward->nBroad > 0 )
    {
      v30 = Player::getConnId(player_0);
      v31 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v31, v30, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
      if ( !packet )
      {
        v32 = 0;
        goto LABEL_34;
      }
      Answer::NetPacket::writeInt32(packet, pReward->nBroad);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      v33 = Player::getCid(player_0);
      Answer::NetPacket::writeInt64(packet, v33);
      Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.id);
      Answer::NetPacket::writeInt8(packet, item.itemClass);
      Answer::NetPacket::writeInt32(packet, item.itemId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v35 = Player::getConnId(player_0);
      v36 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v36, v35, packet);
    }
    memset(&logReward, 0, sizeof(logReward));
    logReward.cid = Player::getCid(player_0);
    Player::getName((const Player *const)&v53);
    v37 = (const char *)std::string::c_str(&v53);
    snprintf(logReward.name, 0x1Eu, v37);
    std::string::~string(&v53);
    logReward.dungeonid = this->m_cfgDungeon.id;
    logReward.itemid = pReward->nId;
    logReward.itemclass = pReward->nClass;
    logReward.itemcount = pReward->nCount;
    logReward.time = Unit::getNow(player_0);
    logReward.special = pReward->nSpecial;
    v38 = Player::getConnId(player_0);
    v39 = Answer::Singleton<DBService>::instance();
    DBService::logMoYuShiJieReward(v39, v38, &logReward);
    v40 = Answer::Singleton<GameService>::instance();
    GameService::AddMoYuShiJieRecord(v40, &logReward);
    v32 = 1;
LABEL_34:
    std::vector<MemChrBag>::~vector(&vItem);
    if ( !v32 )
      return;
    goto LABEL_35;
  }
  if ( Dungeon::getDungeonType(this) == 25 )
  {
    m_nFamilyId = this->m_nFamilyId;
    v42 = Answer::Singleton<FamilyManager>::instance();
    FamilyManager::DeleteFamilyDungeon(v42, m_nFamilyId);
  }
}


#####################################
void __cdecl Dungeon::fail(Dungeon *const this, int32_t nParam)
{
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v3; // rax

  if ( Dungeon::getDungeonType(this) == 25 )
  {
    m_nFamilyId = this->m_nFamilyId;
    v3 = Answer::Singleton<FamilyManager>::instance();
    FamilyManager::DeleteFamilyDungeon(v3, m_nFamilyId);
  }
  Dungeon::clearMonster(this);
  Dungeon::setState(this, DungeonState::DS_FAIL, 30);
}


#####################################
void __cdecl Dungeon::triggerEvent(Dungeon *const this, CfgMapEvent *const mapEvent, Unit *pUnit)
{
  int32_t LeftTime; // edx
  const char *v4; // rax
  int32_t v5; // edx
  const char *v6; // rax
  int32_t v7; // edx
  std::string *v8; // rbx
  std::string *v9; // rax
  const char *v10; // rax
  int *v11; // rbx
  std::string *v12; // rax
  const char *v13; // rax
  int32_t DungeonId; // eax
  std::string *v15; // rax
  const char *v16; // rax
  int32_t v17; // ebx
  CfgData *v18; // rax
  int32_t tid; // ebx
  CfgData *v20; // rax
  CPoolManager *v21; // rax
  std::string *v22; // rax
  const char *v23; // rax
  int32_t v24; // ebx
  CfgData *v25; // rax
  int32_t pid; // ebx
  CfgData *v27; // rax
  CPoolManager *v28; // rax
  const char *v29; // rax
  CfgData *v30; // rax
  std::string *v31; // rax
  const char *v32; // rax
  int64_t Tick; // rax
  std::string *v34; // rax
  const char *v35; // rax
  Monster *v36; // rax
  MonsterDungeon *v37; // rax
  int32_t DungeonMid; // eax
  std::string *v40; // rax
  const char *v41; // rax
  std::string *v42; // rax
  const char *v43; // rax
  std::string *v44; // rax
  const char *v45; // rax
  std::string *v46; // rax
  const char *v47; // rax
  std::string *v48; // rax
  const char *v49; // rax
  CfgData *v50; // rax
  std::string *v51; // rax
  const char *v52; // rax
  int32_t v53; // edx
  std::string *v54; // rax
  std::string *v55; // rax
  const char *v56; // rax
  size_t v57; // rbx
  const char *v58; // rax
  std::string *v59; // rax
  std::string *v60; // rax
  const char *v61; // rax
  int32_t v62; // ebx
  std::string *v63; // rax
  const char *v64; // rax
  int32_t v65; // eax
  std::string *v66; // rax
  std::string *v67; // rax
  const char *v68; // rax
  int32_t v69; // ebx
  std::string *v70; // rax
  const char *v71; // rax
  int32_t v72; // eax
  int v73; // ebx
  std::string *v74; // rax
  const char *v75; // rax
  std::string *v76; // rax
  const char *v77; // rax
  MonsterDungeon *v79; // rax
  int32_t v80; // eax
  Monster *v82; // rax
  MonsterDungeon *v83; // rax
  int32_t v84; // eax
  CfgData *v86; // rax
  int32_t v87; // edx
  Buff *v88; // rbx
  std::string *v89; // rax
  const char *v90; // rax
  int64_t v91; // rax
  std::string *v92; // rax
  const char *v93; // rax
  std::string *v94; // rax
  const char *v95; // rax
  Monster *v96; // rax
  MonsterDungeon *v97; // rax
  int32_t v98; // eax
  void (__fastcall *v100)(MonsterDungeon *, _QWORD); // rbx
  __int64 v101; // rax
  std::string *v102; // rax
  std::string *v103; // rax
  const char *v104; // rax
  std::string *v105; // rax
  const char *v106; // rax
  Answer::Random *v107; // rax
  int64_t v108; // rax
  RandEvent *v109; // rax
  int64_t v110; // rbx
  RandEvent *v111; // rax
  RandEvent *v112; // rax
  std::string *v113; // rax
  Answer::Random *v114; // rax
  std::string *v115; // rax
  const char *v116; // rax
  int32_t v117; // eax
  std::string *v118; // rax
  const char *v119; // rax
  int32_t v120; // ebx
  CfgData *v121; // rax
  int32_t NpcId; // ebx
  CfgData *v123; // rax
  NpcDungeon *v124; // rbx
  std::string *v125; // rax
  std::string *v126; // rax
  const char *v127; // rax
  std::string *v128; // rax
  const char *v129; // rax
  std::string *v130; // rax
  const char *v131; // rax
  std::string *v132; // rax
  const char *v133; // rax
  std::string *v134; // rax
  const char *v135; // rax
  Answer::Random *v136; // rax
  DungeonRandItem *v137; // rax
  DungeonRandItem *v138; // rax
  int32_t v139; // ebx
  CfgData *v140; // rax
  int32_t m_nHard; // r12d
  FamilyId_t m_nFamilyId; // rbx
  FamilyManager *v143; // rax
  int64_t v144; // rdx
  Int32Int32Map Monsters; // [rsp+60h] [rbp-940h] BYREF
  DropItem dropItem; // [rsp+90h] [rbp-910h] BYREF
  CDropItemGroup pDropItemGroup; // [rsp+C0h] [rbp-8E0h] BYREF
  Position NpcPos_0; // [rsp+D0h] [rbp-8D0h] BYREF
  std::_List_iterator<DungeonRandItem> iter_6; // [rsp+E0h] [rbp-8C0h] BYREF
  DungeonRandItem RandItem; // [rsp+F0h] [rbp-8B0h] BYREF
  StringVector vRandEven_0; // [rsp+110h] [rbp-890h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter_5; // [rsp+130h] [rbp-870h] BYREF
  DropItemVector dropItems; // [rsp+140h] [rbp-860h] BYREF
  StringVector vStr_1; // [rsp+160h] [rbp-840h] BYREF
  DungeonRandItemList RandItemList; // [rsp+180h] [rbp-820h] BYREF
  Position NpcPos; // [rsp+190h] [rbp-810h] BYREF
  StringVector NpcRands; // [rsp+1A0h] [rbp-800h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_8; // [rsp+1C0h] [rbp-7E0h] BYREF
  StringVector strIds_7; // [rsp+1D0h] [rbp-7D0h] BYREF
  std::_List_iterator<RandEvent> iter_4; // [rsp+1F0h] [rbp-7B0h] BYREF
  RandEvent RandEvn; // [rsp+200h] [rbp-7A0h] BYREF
  StringVector vRandEven; // [rsp+210h] [rbp-790h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter_3; // [rsp+230h] [rbp-770h] BYREF
  StringVector vStr_0; // [rsp+240h] [rbp-760h] BYREF
  RandEventList EventList; // [rsp+260h] [rbp-740h] BYREF
  std::_List_iterator<Monster*> iter_2; // [rsp+270h] [rbp-730h] BYREF
  StringVector vStr; // [rsp+280h] [rbp-720h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_7; // [rsp+2A0h] [rbp-700h] BYREF
  StringVector strIds_6; // [rsp+2B0h] [rbp-6F0h] BYREF
  Int32List events_0; // [rsp+2D0h] [rbp-6D0h] BYREF
  std::_List_iterator<Monster*> iter_1; // [rsp+2E0h] [rbp-6C0h] BYREF
  StringVector strIds_5; // [rsp+2F0h] [rbp-6B0h] BYREF
  StringVector vstack_0; // [rsp+310h] [rbp-690h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_6; // [rsp+330h] [rbp-670h] BYREF
  StringVector strstacks_0; // [rsp+340h] [rbp-660h] BYREF
  PosList stacks_0; // [rsp+360h] [rbp-640h] BYREF
  StringVector vstack; // [rsp+370h] [rbp-630h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_5; // [rsp+390h] [rbp-610h] BYREF
  StringVector strstacks; // [rsp+3A0h] [rbp-600h] BYREF
  PosList stacks; // [rsp+3C0h] [rbp-5E0h] BYREF
  StringVector strEvents; // [rsp+3D0h] [rbp-5D0h] BYREF
  StringVector strIds_4; // [rsp+3F0h] [rbp-5B0h] BYREF
  DungeonTower tower; // [rsp+410h] [rbp-590h] BYREF
  StringVector strIds_3; // [rsp+430h] [rbp-570h] BYREF
  std::_List_iterator<Monster*> iter_0; // [rsp+450h] [rbp-550h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_4; // [rsp+460h] [rbp-540h] BYREF
  StringVector strIds_2; // [rsp+470h] [rbp-530h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_3; // [rsp+490h] [rbp-510h] BYREF
  StringVector strIds_1; // [rsp+4A0h] [rbp-500h] BYREF
  Int32List events; // [rsp+4C0h] [rbp-4E0h] BYREF
  CfgMapPlant mapPlant; // [rsp+4D0h] [rbp-4D0h] BYREF
  Position plantPos; // [rsp+4E0h] [rbp-4C0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_2; // [rsp+4F0h] [rbp-4B0h] BYREF
  StringVector strIds_0; // [rsp+500h] [rbp-4A0h] BYREF
  Position trapPos; // [rsp+520h] [rbp-480h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it_1; // [rsp+530h] [rbp-470h] BYREF
  StringVector strIds; // [rsp+540h] [rbp-460h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it_0; // [rsp+560h] [rbp-440h] BYREF
  int32_t Level; // [rsp+56Ch] [rbp-434h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+570h] [rbp-430h] BYREF
  StringVector MonsterIds; // [rsp+580h] [rbp-420h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+5A0h] [rbp-400h] BYREF
  StringVector LevelMonster; // [rsp+5B0h] [rbp-3F0h] BYREF
  std::string delims; // [rsp+5D0h] [rbp-3D0h] BYREF
  char v206; // [rsp+5DFh] [rbp-3C1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+5E0h] [rbp-3C0h] BYREF
  std::string v208; // [rsp+5F0h] [rbp-3B0h] BYREF
  char v209; // [rsp+5FBh] [rbp-3A5h] BYREF
  int __k; // [rsp+5FCh] [rbp-3A4h] BYREF
  std::_List_iterator<Player*> v211; // [rsp+600h] [rbp-3A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+610h] [rbp-390h] BYREF
  std::string v213; // [rsp+620h] [rbp-380h] BYREF
  char v214; // [rsp+62Fh] [rbp-371h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v215; // [rsp+630h] [rbp-370h] BYREF
  std::string v216; // [rsp+640h] [rbp-360h] BYREF
  char v217; // [rsp+64Fh] [rbp-351h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v218; // [rsp+650h] [rbp-350h] BYREF
  std::string v219; // [rsp+660h] [rbp-340h] BYREF
  char v220; // [rsp+66Fh] [rbp-331h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v221; // [rsp+670h] [rbp-330h] BYREF
  int v222; // [rsp+67Ch] [rbp-324h] BYREF
  std::string v223; // [rsp+680h] [rbp-320h] BYREF
  char v224; // [rsp+68Fh] [rbp-311h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v225; // [rsp+690h] [rbp-310h] BYREF
  std::_List_iterator<Monster*> v226; // [rsp+6A0h] [rbp-300h] BYREF
  std::string v227; // [rsp+6B0h] [rbp-2F0h] BYREF
  char v228; // [rsp+6BFh] [rbp-2E1h] BYREF
  std::string v229; // [rsp+6C0h] [rbp-2E0h] BYREF
  char v230; // [rsp+6CFh] [rbp-2D1h] BYREF
  std::string v231; // [rsp+6D0h] [rbp-2D0h] BYREF
  char v232; // [rsp+6DBh] [rbp-2C5h] BYREF
  int v233; // [rsp+6DCh] [rbp-2C4h] BYREF
  std::string v234; // [rsp+6E0h] [rbp-2C0h] BYREF
  char v235; // [rsp+6EFh] [rbp-2B1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v236; // [rsp+6F0h] [rbp-2B0h] BYREF
  std::string v237; // [rsp+700h] [rbp-2A0h] BYREF
  char v238; // [rsp+70Fh] [rbp-291h] BYREF
  Position v239; // [rsp+710h] [rbp-290h] BYREF
  std::string v240; // [rsp+720h] [rbp-280h] BYREF
  char v241; // [rsp+72Fh] [rbp-271h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v242; // [rsp+730h] [rbp-270h] BYREF
  std::string v243; // [rsp+740h] [rbp-260h] BYREF
  char v244; // [rsp+74Fh] [rbp-251h] BYREF
  Position v245; // [rsp+750h] [rbp-250h] BYREF
  std::string v246; // [rsp+760h] [rbp-240h] BYREF
  char v247; // [rsp+76Fh] [rbp-231h] BYREF
  std::_List_iterator<Monster*> v248; // [rsp+770h] [rbp-230h] BYREF
  UnitHandle launcher; // [rsp+780h] [rbp-220h] BYREF
  std::string v250; // [rsp+790h] [rbp-210h] BYREF
  char v251; // [rsp+79Fh] [rbp-201h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v252; // [rsp+7A0h] [rbp-200h] BYREF
  int v253; // [rsp+7ACh] [rbp-1F4h] BYREF
  std::string v254; // [rsp+7B0h] [rbp-1F0h] BYREF
  char v255; // [rsp+7BFh] [rbp-1E1h] BYREF
  std::_List_iterator<Monster*> v256; // [rsp+7C0h] [rbp-1E0h] BYREF
  std::string v257; // [rsp+7D0h] [rbp-1D0h] BYREF
  char v258; // [rsp+7DFh] [rbp-1C1h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v259; // [rsp+7E0h] [rbp-1C0h] BYREF
  std::string v260; // [rsp+7F0h] [rbp-1B0h] BYREF
  char v261; // [rsp+7FFh] [rbp-1A1h] BYREF
  std::_List_iterator<RandEvent> v262; // [rsp+800h] [rbp-1A0h] BYREF
  std::string v263; // [rsp+810h] [rbp-190h] BYREF
  char v264; // [rsp+81Fh] [rbp-181h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v265; // [rsp+820h] [rbp-180h] BYREF
  std::string v266; // [rsp+830h] [rbp-170h] BYREF
  char v267; // [rsp+83Fh] [rbp-161h] BYREF
  std::string v268; // [rsp+840h] [rbp-160h] BYREF
  char v269; // [rsp+84Fh] [rbp-151h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v270; // [rsp+850h] [rbp-150h] BYREF
  std::string v271; // [rsp+860h] [rbp-140h] BYREF
  char v272; // [rsp+86Fh] [rbp-131h] BYREF
  std::_List_iterator<DungeonRandItem> v273; // [rsp+870h] [rbp-130h] BYREF
  std::string dropper; // [rsp+880h] [rbp-120h] BYREF
  char v275; // [rsp+890h] [rbp-110h] BYREF
  bool rewardWave; // [rsp+891h] [rbp-10Fh]
  bool rewardWave_0; // [rsp+892h] [rbp-10Eh]
  bool rewardWave_1; // [rsp+893h] [rbp-10Dh]
  int32_t MonsterId; // [rsp+894h] [rbp-10Ch]
  Player *player; // [rsp+898h] [rbp-108h]
  CfgDungeonTrap *pCfgDungeonTrap; // [rsp+8A0h] [rbp-100h]
  CfgTrap *pCfgTrap; // [rsp+8A8h] [rbp-F8h]
  Trap *pTrap; // [rsp+8B0h] [rbp-F0h]
  CfgDungeonPlant *pCfgDungeonPlant; // [rsp+8B8h] [rbp-E8h]
  CfgPlant *pCfgPlant; // [rsp+8C0h] [rbp-E0h]
  PlantDungeon *plant; // [rsp+8C8h] [rbp-D8h]
  int32_t movieID; // [rsp+8D0h] [rbp-D0h]
  int32_t nDungeonMid; // [rsp+8D4h] [rbp-CCh]
  MonsterDungeon *pMonster; // [rsp+8D8h] [rbp-C8h]
  CfgDungeonMonster *pCfgDungeonMonster; // [rsp+8E0h] [rbp-C0h]
  uint32_t i; // [rsp+8ECh] [rbp-B4h]
  int32_t nMonsterId; // [rsp+8F0h] [rbp-B0h]
  int32_t nBuffId; // [rsp+8F4h] [rbp-ACh]
  MonsterDungeon *pTarget; // [rsp+8F8h] [rbp-A8h]
  bool bTrigMonster; // [rsp+907h] [rbp-99h]
  MonsterDungeon *pMonster_0; // [rsp+908h] [rbp-98h]
  MonsterDungeon *pMonster_1; // [rsp+910h] [rbp-90h]
  CfgBuff *cfgBuff; // [rsp+918h] [rbp-88h]
  Buff *buff; // [rsp+920h] [rbp-80h]
  int32_t nMonsterId_0; // [rsp+928h] [rbp-78h]
  int32_t nPercent; // [rsp+92Ch] [rbp-74h]
  MonsterDungeon *pMonster_2; // [rsp+930h] [rbp-70h]
  int32_t MaxRand; // [rsp+938h] [rbp-68h]
  int32_t FulfillEvent; // [rsp+93Ch] [rbp-64h]
  int32_t nRand; // [rsp+940h] [rbp-60h]
  int32_t nRand_0; // [rsp+944h] [rbp-5Ch]
  CfgDungeonNpc *pCfgDungeonNpc; // [rsp+948h] [rbp-58h]
  const CfgNpc *pCfgNpc; // [rsp+950h] [rbp-50h]
  NpcDungeon *npc; // [rsp+958h] [rbp-48h]
  int32_t MaxRand_0; // [rsp+964h] [rbp-3Ch]
  Player *player_0; // [rsp+968h] [rbp-38h]
  int32_t nRand_1; // [rsp+974h] [rbp-2Ch]
  CfgDungeonNpc *pCfgDungeonNpc_0; // [rsp+978h] [rbp-28h]

  switch ( mapEvent->event_type )
  {
    case 1:
      v4 = (const char *)std::string::c_str(&mapEvent->effect);
      v5 = atoi(v4);
      Dungeon::win(this, v5);
      goto LABEL_195;
    case 2:
      v6 = (const char *)std::string::c_str(&mapEvent->effect);
      v7 = atoi(v6);
      Dungeon::fail(this, v7);
      goto LABEL_195;
    case 3:
      rewardWave = mapEvent->trigger_type == 4;
      Dungeon::generateMonster(this, &mapEvent->effect, rewardWave);
      goto LABEL_195;
    case 4:
      std::allocator<char>::allocator(&v214);
      std::string::string(&v213, 9266714, &v214);
      Answer::StringUtility::split(&strIds, &mapEvent->effect, &v213, 0);
      std::string::~string(&v213);
      std::allocator<char>::~allocator(&v214);
      for ( it_1._M_current = std::vector<std::string>::begin(&strIds)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_1) )
      {
        v215._M_current = std::vector<std::string>::end(&strIds)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_1, &v215) )
          break;
        v15 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_1);
        v16 = (const char *)std::string::c_str(v15);
        v17 = atoi(v16);
        v18 = Answer::Singleton<CfgData>::instance();
        pCfgDungeonTrap = CfgData::getDungeonTrap(v18, v17);
        if ( pCfgDungeonTrap )
        {
          tid = pCfgDungeonTrap->tid;
          v20 = Answer::Singleton<CfgData>::instance();
          pCfgTrap = CfgData::getTrap(v20, tid);
          if ( pCfgTrap )
          {
            Position::Position(&trapPos, pCfgDungeonTrap->x, pCfgDungeonTrap->y);
            if ( trapPos.x > 0 && trapPos.y > 0 )
            {
              v21 = Answer::Singleton<CPoolManager>::instance();
              pTrap = CPoolManager::pop<Trap>(v21);
              if ( pTrap )
              {
                Trap::init(pTrap, this, trapPos, pCfgTrap);
                Map::addTrap(this, pTrap);
              }
            }
          }
        }
      }
      std::vector<std::string>::~vector(&strIds);
      goto LABEL_195;
    case 5:
      std::allocator<char>::allocator(&v217);
      std::string::string(&v216, 9266714, &v217);
      Answer::StringUtility::split(&strIds_0, &mapEvent->effect, &v216, 0);
      std::string::~string(&v216);
      std::allocator<char>::~allocator(&v217);
      for ( it_2._M_current = std::vector<std::string>::begin(&strIds_0)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_2) )
      {
        v218._M_current = std::vector<std::string>::end(&strIds_0)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_2, &v218) )
          break;
        v22 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_2);
        v23 = (const char *)std::string::c_str(v22);
        v24 = atoi(v23);
        v25 = Answer::Singleton<CfgData>::instance();
        pCfgDungeonPlant = CfgData::getDungeonPlant(v25, v24);
        if ( pCfgDungeonPlant )
        {
          pid = pCfgDungeonPlant->pid;
          v27 = Answer::Singleton<CfgData>::instance();
          pCfgPlant = CfgData::getPlant(v27, pid);
          if ( pCfgPlant )
          {
            Position::Position(&plantPos, pCfgDungeonPlant->x, pCfgDungeonPlant->y);
            if ( pUnit )
              plantPos = StaticObj::getCurrentTile(pUnit);
            if ( plantPos.x > 0 && plantPos.y > 0 )
            {
              mapPlant.mapid = Dungeon::GetId(this);
              mapPlant.plantid = pCfgPlant->id;
              *(Position *)&mapPlant.x = plantPos;
              v28 = Answer::Singleton<CPoolManager>::instance();
              plant = CPoolManager::pop<PlantDungeon>(v28);
              if ( plant )
              {
                PlantDungeon::init(plant, this, pCfgPlant, &mapPlant);
                Map::addPlant(this, plant);
              }
            }
          }
        }
      }
      std::vector<std::string>::~vector(&strIds_0);
      goto LABEL_195;
    case 6:
      v29 = (const char *)std::string::c_str(&mapEvent->effect);
      movieID = atoi(v29);
      v30 = Answer::Singleton<CfgData>::instance();
      if ( CfgData::getMovie(v30, movieID) )
        Dungeon::broadcastPlayMovie(this, movieID);
      goto LABEL_195;
    case 7:
      std::list<int>::list(&events);
      std::allocator<char>::allocator(&v220);
      std::string::string(&v219, 9266714, &v220);
      Answer::StringUtility::split(&strIds_1, &mapEvent->effect, &v219, 0);
      std::string::~string(&v219);
      std::allocator<char>::~allocator(&v220);
      for ( it_3._M_current = std::vector<std::string>::begin(&strIds_1)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_3) )
      {
        v221._M_current = std::vector<std::string>::end(&strIds_1)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_3, &v221) )
          break;
        v31 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_3);
        v32 = (const char *)std::string::c_str(v31);
        v222 = atoi(v32);
        std::list<int>::push_back(&events, &v222);
      }
      Tick = Map::getTick(this);
      IMapEvent::openEvents(&this->IMapEvent, &events, Tick);
      std::vector<std::string>::~vector(&strIds_1);
      std::list<int>::~list(&events);
      goto LABEL_195;
    case 8:
      std::allocator<char>::allocator(&v224);
      std::string::string(&v223, 9266714, &v224);
      Answer::StringUtility::split(&strIds_2, &mapEvent->effect, &v223, 0);
      std::string::~string(&v223);
      std::allocator<char>::~allocator(&v224);
      for ( it_4._M_current = std::vector<std::string>::begin(&strIds_2)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_4) )
      {
        v225._M_current = std::vector<std::string>::end(&strIds_2)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_4, &v225) )
          break;
        v34 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_4);
        v35 = (const char *)std::string::c_str(v34);
        nDungeonMid = atoi(v35);
        for ( iter_0._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
              ;
              std::_List_iterator<Monster *>::operator++(&iter_0) )
        {
          v226._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
          if ( !std::_List_iterator<Monster *>::operator!=(&iter_0, &v226) )
            break;
          v36 = *std::_List_iterator<Monster *>::operator*(&iter_0);
          if ( v36 )
            v37 = (MonsterDungeon *)__dynamic_cast(
                                      v36,
                                      (const struct __class_type_info *)&`typeinfo for'Monster,
                                      (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                                      0);
          else
            v37 = 0;
          pMonster = v37;
          if ( v37 )
          {
            DungeonMid = MonsterDungeon::getDungeonMid(pMonster);
            if ( DungeonMid == nDungeonMid )
              Monster::setDelFlg(pMonster);
          }
        }
      }
      std::vector<std::string>::~vector(&strIds_2);
      goto LABEL_195;
    case 9:
      std::allocator<char>::allocator(&v228);
      std::string::string(&v227, 9266714, &v228);
      Answer::StringUtility::split(&strIds_3, &mapEvent->effect, &v227, 0);
      std::string::~string(&v227);
      std::allocator<char>::~allocator(&v228);
      if ( std::vector<std::string>::size(&strIds_3) == 5 )
      {
        tower.mid = 0;
        tower.count = 0;
        v40 = std::vector<std::string>::operator[](&strIds_3, 0);
        v41 = (const char *)std::string::c_str(v40);
        tower.id = atoi(v41);
        v42 = std::vector<std::string>::operator[](&strIds_3, 1u);
        v43 = (const char *)std::string::c_str(v42);
        tower.free = atoi(v43);
        v44 = std::vector<std::string>::operator[](&strIds_3, 2u);
        v45 = (const char *)std::string::c_str(v44);
        tower.limit = atoi(v45);
        v46 = std::vector<std::string>::operator[](&strIds_3, 3u);
        v47 = (const char *)std::string::c_str(v46);
        *(_DWORD *)&tower.costType = (unsigned __int8)atoi(v47);
        v48 = std::vector<std::string>::operator[](&strIds_3, 4u);
        v49 = (const char *)std::string::c_str(v48);
        tower.costValue = atoi(v49);
        v50 = Answer::Singleton<CfgData>::instance();
        pCfgDungeonMonster = CfgData::getDungeonMonster(v50, tower.id);
        if ( pCfgDungeonMonster )
          tower.mid = CfgDungeonMonster::GetMid(pCfgDungeonMonster);
        if ( tower.mid > 0 )
          Dungeon::addWaitTower(this, &tower);
      }
      std::vector<std::string>::~vector(&strIds_3);
      goto LABEL_195;
    case 0xA:
      std::allocator<char>::allocator(&v230);
      std::string::string(&v229, 9266714, &v230);
      Answer::StringUtility::split(&strIds_4, &mapEvent->effect, &v229, 0);
      std::string::~string(&v229);
      std::allocator<char>::~allocator(&v230);
      if ( std::vector<std::string>::size(&strIds_4) == 2 )
      {
        v51 = std::vector<std::string>::operator[](&strIds_4, 0);
        v52 = (const char *)std::string::c_str(v51);
        v53 = atoi(v52);
        Dungeon::setState(this, DungeonState::DS_WAIT, v53);
        std::allocator<char>::allocator(&v232);
        std::string::string(&v231, 9266716, &v232);
        v54 = std::vector<std::string>::operator[](&strIds_4, 1u);
        Answer::StringUtility::split(&strEvents, v54, &v231, 0);
        std::string::~string(&v231);
        std::allocator<char>::~allocator(&v232);
        for ( i = 0; ; ++i )
        {
          v57 = i;
          if ( v57 >= std::vector<std::string>::size(&strEvents) )
            break;
          v55 = std::vector<std::string>::operator[](&strEvents, i);
          v56 = (const char *)std::string::c_str(v55);
          v233 = atoi(v56);
          std::list<int>::push_back(&this->m_waitEvent, &v233);
        }
        std::vector<std::string>::~vector(&strEvents);
      }
      std::vector<std::string>::~vector(&strIds_4);
      goto LABEL_195;
    case 0xB:
      v58 = (const char *)std::string::c_str(&mapEvent->effect);
      this->m_dRatio = (double)atoi(v58) / 100.0;
      goto LABEL_195;
    case 0xC:
      std::list<Position>::list(&stacks);
      std::allocator<char>::allocator(&v235);
      std::string::string(&v234, L"|:,", &v235);
      Answer::StringUtility::split(&strstacks, &mapEvent->effect, &v234, 0);
      std::string::~string(&v234);
      std::allocator<char>::~allocator(&v235);
      for ( it_5._M_current = std::vector<std::string>::begin(&strstacks)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_5) )
      {
        v236._M_current = std::vector<std::string>::end(&strstacks)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_5, &v236) )
          break;
        std::allocator<char>::allocator(&v238);
        std::string::string(&v237, 9266714, &v238);
        v59 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_5);
        Answer::StringUtility::split(&vstack, v59, &v237, 0);
        std::string::~string(&v237);
        std::allocator<char>::~allocator(&v238);
        if ( std::vector<std::string>::size(&vstack) == 2 )
        {
          v60 = std::vector<std::string>::operator[](&vstack, 1u);
          v61 = (const char *)std::string::c_str(v60);
          v62 = atoi(v61);
          v63 = std::vector<std::string>::operator[](&vstack, 0);
          v64 = (const char *)std::string::c_str(v63);
          v65 = atoi(v64);
          Position::Position(&v239, v65, v62);
          std::list<Position>::push_back(&stacks, &v239);
        }
        std::vector<std::string>::~vector(&vstack);
      }
      Map::AddStack(this, &stacks);
      std::vector<std::string>::~vector(&strstacks);
      std::list<Position>::~list(&stacks);
      goto LABEL_195;
    case 0xD:
      std::list<Position>::list(&stacks_0);
      std::allocator<char>::allocator(&v241);
      std::string::string(&v240, L"|:,", &v241);
      Answer::StringUtility::split(&strstacks_0, &mapEvent->effect, &v240, 0);
      std::string::~string(&v240);
      std::allocator<char>::~allocator(&v241);
      for ( it_6._M_current = std::vector<std::string>::begin(&strstacks_0)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_6) )
      {
        v242._M_current = std::vector<std::string>::end(&strstacks_0)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_6, &v242) )
          break;
        std::allocator<char>::allocator(&v244);
        std::string::string(&v243, 9266714, &v244);
        v66 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_6);
        Answer::StringUtility::split(&vstack_0, v66, &v243, 0);
        std::string::~string(&v243);
        std::allocator<char>::~allocator(&v244);
        if ( std::vector<std::string>::size(&vstack_0) == 2 )
        {
          v67 = std::vector<std::string>::operator[](&vstack_0, 1u);
          v68 = (const char *)std::string::c_str(v67);
          v69 = atoi(v68);
          v70 = std::vector<std::string>::operator[](&vstack_0, 0);
          v71 = (const char *)std::string::c_str(v70);
          v72 = atoi(v71);
          Position::Position(&v245, v72, v69);
          std::list<Position>::push_back(&stacks_0, &v245);
        }
        std::vector<std::string>::~vector(&vstack_0);
      }
      Map::RemoveStack(this, &stacks_0);
      std::vector<std::string>::~vector(&strstacks_0);
      std::list<Position>::~list(&stacks_0);
      goto LABEL_195;
    case 0xE:
      std::allocator<char>::allocator(&v247);
      std::string::string(&v246, 9266714, &v247);
      Answer::StringUtility::split(&strIds_5, &mapEvent->effect, &v246, 0);
      std::string::~string(&v246);
      std::allocator<char>::~allocator(&v247);
      if ( std::vector<std::string>::size(&strIds_5) != 2 )
      {
        v73 = 0;
        goto LABEL_128;
      }
      v74 = std::vector<std::string>::operator[](&strIds_5, 0);
      v75 = (const char *)std::string::c_str(v74);
      nMonsterId = atoi(v75);
      v76 = std::vector<std::string>::operator[](&strIds_5, 1u);
      v77 = (const char *)std::string::c_str(v76);
      nBuffId = atoi(v77);
      pTarget = 0;
      bTrigMonster = 0;
      if ( pUnit && Entity::getType(pUnit) == EntityType::ET_MONSTER )
      {
        v79 = pUnit
            ? (MonsterDungeon *)__dynamic_cast(
                                  pUnit,
                                  (const struct __class_type_info *)&`typeinfo for'Unit,
                                  (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                                  0)
            : 0LL;
        pMonster_0 = v79;
        if ( v79 )
        {
          v80 = MonsterDungeon::getDungeonMid(pMonster_0);
          if ( v80 == nMonsterId )
          {
            pTarget = pMonster_0;
            bTrigMonster = 1;
          }
        }
      }
      if ( bTrigMonster )
        goto LABEL_122;
      iter_1._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
      while ( 2 )
      {
        v248._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
        if ( std::_List_iterator<Monster *>::operator!=(&iter_1, &v248) )
        {
          v82 = *std::_List_iterator<Monster *>::operator*(&iter_1);
          if ( v82 )
            v83 = (MonsterDungeon *)__dynamic_cast(
                                      v82,
                                      (const struct __class_type_info *)&`typeinfo for'Monster,
                                      (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                                      0);
          else
            v83 = 0;
          pMonster_1 = v83;
          if ( !v83 || (v84 = MonsterDungeon::getDungeonMid(pMonster_1), v84 != nMonsterId) )
          {
            std::_List_iterator<Monster *>::operator++(&iter_1);
            continue;
          }
          pTarget = pMonster_1;
        }
        break;
      }
LABEL_122:
      if ( !pTarget )
        goto LABEL_127;
      v86 = Answer::Singleton<CfgData>::instance();
      cfgBuff = CfgData::getBuff(v86, nBuffId);
      if ( !cfgBuff )
        goto LABEL_127;
      launcher.id = (*((__int64 (__fastcall **)(MonsterDungeon *))pTarget->_vptr_Entity + 12))(pTarget);
      launcher.type = v87;
      v88 = (Buff *)operator new(0x60u);
      Buff::Buff(v88, pTarget, cfgBuff, &launcher, 2, 1);
      buff = v88;
      if ( v88 )
      {
        Unit::addBuff(pTarget, buff);
LABEL_127:
        v73 = 2;
      }
      else
      {
        v73 = 1;
      }
LABEL_128:
      std::vector<std::string>::~vector(&strIds_5);
      if ( v73 != 1 )
        goto LABEL_195;
      return;
    case 0xF:
      rewardWave_0 = mapEvent->trigger_type == 4;
      Dungeon::randomMonster(this, &mapEvent->effect, rewardWave_0);
      goto LABEL_195;
    case 0x10:
      std::list<int>::list(&events_0);
      std::allocator<char>::allocator(&v251);
      std::string::string(&v250, 9266714, &v251);
      Answer::StringUtility::split(&strIds_6, &mapEvent->effect, &v250, 0);
      std::string::~string(&v250);
      std::allocator<char>::~allocator(&v251);
      for ( it_7._M_current = std::vector<std::string>::begin(&strIds_6)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_7) )
      {
        v252._M_current = std::vector<std::string>::end(&strIds_6)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_7, &v252) )
          break;
        v89 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it_7);
        v90 = (const char *)std::string::c_str(v89);
        v253 = atoi(v90);
        std::list<int>::push_back(&events_0, &v253);
      }
      v91 = Map::getTick(this);
      IMapEvent::closeEvents(&this->IMapEvent, &events_0, v91);
      std::vector<std::string>::~vector(&strIds_6);
      std::list<int>::~list(&events_0);
      goto LABEL_195;
    case 0x11:
      Dungeon::clearMonster(this);
      LeftTime = Dungeon::GetLeftTime(this);
      Dungeon::setState(this, DungeonState::DS_SUMMON, LeftTime);
      goto LABEL_195;
    case 0x13:
      std::allocator<char>::allocator(&v255);
      std::string::string(&v254, 9266714, &v255);
      Answer::StringUtility::split(&vStr, &mapEvent->effect, &v254, 0);
      std::string::~string(&v254);
      std::allocator<char>::~allocator(&v255);
      if ( std::vector<std::string>::size(&vStr) == 2 )
      {
        v92 = std::vector<std::string>::operator[](&vStr, 0);
        v93 = (const char *)std::string::c_str(v92);
        nMonsterId_0 = atoi(v93);
        v94 = std::vector<std::string>::operator[](&vStr, 1u);
        v95 = (const char *)std::string::c_str(v94);
        nPercent = atoi(v95);
        for ( iter_2._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
              ;
              std::_List_iterator<Monster *>::operator++(&iter_2) )
        {
          v256._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
          if ( !std::_List_iterator<Monster *>::operator!=(&iter_2, &v256) )
            break;
          v96 = *std::_List_iterator<Monster *>::operator*(&iter_2);
          if ( v96 )
            v97 = (MonsterDungeon *)__dynamic_cast(
                                      v96,
                                      (const struct __class_type_info *)&`typeinfo for'Monster,
                                      (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                                      0);
          else
            v97 = 0;
          pMonster_2 = v97;
          if ( v97 )
          {
            v98 = MonsterDungeon::getDungeonMid(pMonster_2);
            if ( v98 == nMonsterId_0 )
            {
              v100 = (void (__fastcall *)(MonsterDungeon *, _QWORD))*((_QWORD *)pMonster_2->_vptr_Entity + 21);
              v101 = (*((__int64 (__fastcall **)(MonsterDungeon *))pMonster_2->_vptr_Entity + 20))(pMonster_2);
              v100(pMonster_2, (unsigned int)(nPercent * v101 / 100));
            }
          }
        }
      }
      std::vector<std::string>::~vector(&vStr);
      goto LABEL_195;
    case 0x14:
      MaxRand = 0;
      std::list<RandEvent>::list(&EventList);
      FulfillEvent = 0;
      std::allocator<char>::allocator(&v258);
      std::string::string(&v257, L"|:,", &v258);
      Answer::StringUtility::split(&vStr_0, &mapEvent->effect, &v257, 0);
      std::string::~string(&v257);
      std::allocator<char>::~allocator(&v258);
      for ( iter_3._M_current = std::vector<std::string>::begin(&vStr_0)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter_3, 0) )
      {
        v259._M_current = std::vector<std::string>::end(&vStr_0)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter_3, &v259) )
          break;
        std::allocator<char>::allocator(&v261);
        std::string::string(&v260, 9266714, &v261);
        v102 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter_3);
        Answer::StringUtility::split(&vRandEven, v102, &v260, 0);
        std::string::~string(&v260);
        std::allocator<char>::~allocator(&v261);
        RandEvn = 0;
        if ( std::vector<std::string>::size(&vRandEven) == 2 )
        {
          v103 = std::vector<std::string>::operator[](&vRandEven, 0);
          v104 = (const char *)std::string::c_str(v103);
          RandEvn.Event = atoi(v104);
          v105 = std::vector<std::string>::operator[](&vRandEven, 1u);
          v106 = (const char *)std::string::c_str(v105);
          RandEvn.Rand = atoi(v106);
        }
        MaxRand += RandEvn.Rand;
        if ( !RandEvn.Rand )
          FulfillEvent = RandEvn.Event;
        std::list<RandEvent>::push_back(&EventList, &RandEvn);
        std::vector<std::string>::~vector(&vRandEven);
      }
      v107 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v107, 0, 10000);
      if ( nRand > MaxRand )
      {
        v108 = Map::getTick(this);
        IMapEvent::openEvent(&this->IMapEvent, FulfillEvent, v108);
        goto LABEL_162;
      }
      iter_4._M_node = std::list<RandEvent>::begin(&EventList)._M_node;
      while ( 2 )
      {
        v262._M_node = std::list<RandEvent>::end(&EventList)._M_node;
        if ( std::_List_iterator<RandEvent>::operator!=(&iter_4, &v262) )
        {
          v109 = std::_List_iterator<RandEvent>::operator->(&iter_4);
          if ( v109->Rand < nRand )
          {
            v112 = std::_List_iterator<RandEvent>::operator->(&iter_4);
            nRand -= v112->Rand;
            std::_List_iterator<RandEvent>::operator++(&iter_4, 0);
            continue;
          }
          v110 = Map::getTick(this);
          v111 = std::_List_iterator<RandEvent>::operator->(&iter_4);
          IMapEvent::openEvent(&this->IMapEvent, v111->Event, v110);
        }
        break;
      }
LABEL_162:
      std::vector<std::string>::~vector(&vStr_0);
      std::list<RandEvent>::~list(&EventList);
      Dungeon::sendRandEventTime(this);
      goto LABEL_195;
    case 0x15:
      std::allocator<char>::allocator(&v264);
      std::string::string(&v263, L"|:,", &v264);
      Answer::StringUtility::split(&strIds_7, &mapEvent->effect, &v263, 0);
      std::string::~string(&v263);
      std::allocator<char>::~allocator(&v264);
      for ( it_8._M_current = std::vector<std::string>::begin(&strIds_7)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it_8) )
      {
        v265._M_current = std::vector<std::string>::end(&strIds_7)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it_8, &v265) )
          break;
        std::allocator<char>::allocator(&v267);
        std::string::string(&v266, 9266714, &v267);
        v113 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it_8);
        Answer::StringUtility::split(&NpcRands, v113, &v266, 0);
        std::string::~string(&v266);
        std::allocator<char>::~allocator(&v267);
        if ( std::vector<std::string>::size(&NpcRands) == 2 )
        {
          v114 = Answer::Singleton<Answer::Random>::instance();
          nRand_0 = Answer::Random::generate(v114, 1, 10000);
          v115 = std::vector<std::string>::operator[](&NpcRands, 1u);
          v116 = (const char *)std::string::c_str(v115);
          v117 = atoi(v116);
          if ( v117 >= nRand_0 )
          {
            v118 = std::vector<std::string>::operator[](&NpcRands, 0);
            v119 = (const char *)std::string::c_str(v118);
            v120 = atoi(v119);
            v121 = Answer::Singleton<CfgData>::instance();
            pCfgDungeonNpc = CfgData::getDungeonNpc(v121, v120);
            if ( pCfgDungeonNpc )
            {
              NpcId = pCfgDungeonNpc->NpcId;
              v123 = Answer::Singleton<CfgData>::instance();
              pCfgNpc = CfgData::getNpc(v123, NpcId);
              if ( pCfgNpc )
              {
                Position::Position(&NpcPos, pCfgDungeonNpc->x, pCfgDungeonNpc->y);
                if ( pUnit )
                  NpcPos = StaticObj::getCurrentTile(pUnit);
                if ( NpcPos.x > 0 && NpcPos.y > 0 )
                {
                  v124 = (NpcDungeon *)operator new(0x4F0u);
                  NpcDungeon::NpcDungeon(v124);
                  npc = v124;
                  if ( v124 )
                  {
                    NpcDungeon::init(npc, this, pCfgNpc);
                    Map::addNpc(this, npc, NpcPos.x, NpcPos.y);
                  }
                }
              }
            }
          }
        }
        std::vector<std::string>::~vector(&NpcRands);
      }
      std::vector<std::string>::~vector(&strIds_7);
      goto LABEL_195;
    case 0x16:
      MaxRand_0 = 0;
      player_0 = Dungeon::GetLeader(this);
      std::list<DungeonRandItem>::list(&RandItemList);
      std::allocator<char>::allocator(&v269);
      std::string::string(&v268, L"|:,", &v269);
      Answer::StringUtility::split(&vStr_1, &mapEvent->effect, &v268, 0);
      std::string::~string(&v268);
      std::allocator<char>::~allocator(&v269);
      for ( iter_5._M_current = std::vector<std::string>::begin(&vStr_1)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter_5, 0) )
      {
        v270._M_current = std::vector<std::string>::end(&vStr_1)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter_5, &v270) )
          break;
        std::allocator<char>::allocator(&v272);
        std::string::string(&v271, 9266714, &v272);
        v125 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter_5);
        Answer::StringUtility::split(&vRandEven_0, v125, &v271, 0);
        std::string::~string(&v271);
        std::allocator<char>::~allocator(&v272);
        if ( std::vector<std::string>::size(&vRandEven_0) == 5 )
        {
          memset(&RandItem, 0, sizeof(RandItem));
          v126 = std::vector<std::string>::operator[](&vRandEven_0, 0);
          v127 = (const char *)std::string::c_str(v126);
          RandItem.ItemId = atoi(v127);
          v128 = std::vector<std::string>::operator[](&vRandEven_0, 1u);
          v129 = (const char *)std::string::c_str(v128);
          RandItem.ItemType = atoi(v129);
          v130 = std::vector<std::string>::operator[](&vRandEven_0, 2u);
          v131 = (const char *)std::string::c_str(v130);
          RandItem.ItemCount = atoi(v131);
          v132 = std::vector<std::string>::operator[](&vRandEven_0, 3u);
          v133 = (const char *)std::string::c_str(v132);
          RandItem.isBind = atoi(v133);
          v134 = std::vector<std::string>::operator[](&vRandEven_0, 4u);
          v135 = (const char *)std::string::c_str(v134);
          RandItem.RandValue = atoi(v135);
          MaxRand_0 += RandItem.RandValue;
          std::list<DungeonRandItem>::push_back(&RandItemList, &RandItem);
        }
        std::vector<std::string>::~vector(&vRandEven_0);
      }
      v136 = Answer::Singleton<Answer::Random>::instance();
      nRand_1 = Answer::Random::generate(v136, 0, 10000);
      if ( nRand_1 > MaxRand_0 )
        goto LABEL_193;
      std::vector<DropItem>::vector(&dropItems);
      iter_6._M_node = std::list<DungeonRandItem>::begin(&RandItemList)._M_node;
      while ( 2 )
      {
        v273._M_node = std::list<DungeonRandItem>::end(&RandItemList)._M_node;
        if ( std::_List_iterator<DungeonRandItem>::operator!=(&iter_6, &v273) )
        {
          v137 = std::_List_iterator<DungeonRandItem>::operator->(&iter_6);
          if ( v137->RandValue < nRand_1 )
          {
            v138 = std::_List_iterator<DungeonRandItem>::operator->(&iter_6);
            nRand_1 -= v138->RandValue;
            std::_List_iterator<DungeonRandItem>::operator++(&iter_6, 0);
            continue;
          }
          memset(&dropItem, 0, sizeof(dropItem));
          dropItem.itemClass = std::_List_iterator<DungeonRandItem>::operator->(&iter_6)->ItemType;
          dropItem.itemId = std::_List_iterator<DungeonRandItem>::operator->(&iter_6)->ItemId;
          dropItem.itemCount = std::_List_iterator<DungeonRandItem>::operator->(&iter_6)->ItemCount;
          dropItem.bindType = std::_List_iterator<DungeonRandItem>::operator->(&iter_6)->isBind;
          if ( dropItem.itemId > 0 && dropItem.itemClass > 0 )
            std::vector<DropItem>::push_back(&dropItems, &dropItem);
        }
        break;
      }
      v139 = *std::vector<int>::operator[](&mapEvent->trigger_param, 0);
      v140 = Answer::Singleton<CfgData>::instance();
      pCfgDungeonNpc_0 = CfgData::getDungeonNpc(v140, v139);
      if ( pCfgDungeonNpc_0 )
      {
        Position::Position(&NpcPos_0, pCfgDungeonNpc_0->x, pCfgDungeonNpc_0->y);
        CDropItemGroup::CDropItemGroup(&pDropItemGroup);
        std::allocator<char>::allocator(&v275);
        std::string::string(&dropper, &unk_8D658F, &v275);
        CDropItemGroup::init(&pDropItemGroup, 0, this, &NpcPos_0, player_0, 2, 0, &dropItems, &dropper, 0, 0, 0);
        std::string::~string(&dropper);
        std::allocator<char>::~allocator(&v275);
        Map::addDropItemGroup(this, &pDropItemGroup);
        CDropItemGroup::~CDropItemGroup(&pDropItemGroup);
      }
      Dungeon::win(this, 0);
      std::vector<DropItem>::~vector(&dropItems);
LABEL_193:
      std::vector<std::string>::~vector(&vStr_1);
      std::list<DungeonRandItem>::~list(&RandItemList);
      goto LABEL_195;
    case 0x17:
      rewardWave_1 = mapEvent->trigger_type == 4;
      std::map<int,int>::map(&Monsters);
      std::allocator<char>::allocator(&v206);
      std::string::string(&delims, L"|:,", &v206);
      Answer::StringUtility::split(&LevelMonster, &mapEvent->effect, &delims, 0);
      std::string::~string(&delims);
      std::allocator<char>::~allocator(&v206);
      for ( it._M_current = std::vector<std::string>::begin(&LevelMonster)._M_current;
            ;
            __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
      {
        __rhs._M_current = std::vector<std::string>::end(&LevelMonster)._M_current;
        if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
          break;
        std::allocator<char>::allocator(&v209);
        std::string::string(&v208, 9266714, &v209);
        v8 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
        Answer::StringUtility::split(&MonsterIds, v8, &v208, 0);
        std::string::~string(&v208);
        std::allocator<char>::~allocator(&v209);
        if ( std::vector<std::string>::size(&MonsterIds) == 2 )
        {
          v9 = std::vector<std::string>::operator[](&MonsterIds, 0);
          v10 = (const char *)std::string::c_str(v9);
          __k = atoi(v10);
          v11 = std::map<int,int>::operator[](&Monsters, &__k);
          v12 = std::vector<std::string>::operator[](&MonsterIds, 1u);
          v13 = (const char *)std::string::c_str(v12);
          *v11 = atoi(v13);
        }
        std::vector<std::string>::~vector(&MonsterIds);
      }
      MonsterId = 0;
      iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
      break;
    case 0x18:
      m_nHard = this->m_nHard;
      m_nFamilyId = this->m_nFamilyId;
      v143 = Answer::Singleton<FamilyManager>::instance();
      FamilyManager::SetFamilyDungeonHard(v143, m_nFamilyId, m_nHard);
      goto LABEL_195;
    default:
      goto LABEL_195;
  }
  while ( 1 )
  {
    v211._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&iter, &v211) )
      break;
    Level = 0;
    player = *std::_List_iterator<Player *>::operator*(&iter);
    if ( player )
    {
      Level = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 9))(player);
      if ( Dungeon::getDungeonType(this) == 34 )
      {
        DungeonId = Dungeon::getDungeonId(this);
        if ( !Player::getRecord(player, DungeonId + 20000) )
          Level = 1;
      }
      it_0._M_node = std::map<int,int>::lower_bound(&Monsters, &Level)._M_node;
      __x._M_node = std::map<int,int>::end(&Monsters)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it_0, &__x) )
      {
        MonsterId = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it_0)->second;
        break;
      }
    }
    std::_List_iterator<Player *>::operator++(&iter);
  }
  if ( MonsterId > 0 )
  {
    memset(&dropItem.itemClass, 0, 28);
    dropItem.itemId = MonsterId;
    dropItem.srcId = rewardWave_1;
    *(_QWORD *)&dropItem.costValue = Map::getTick(this);
    std::list<MonsterWait>::push_back(&this->m_waitMonster, (const MonsterWait *const)&dropItem);
  }
  std::vector<std::string>::~vector(&LevelMonster);
  std::map<int,int>::~map(&Monsters);
LABEL_195:
  Dungeon::broadcastDungeonEvent(this, mapEvent->trigger_id);
  v144 = Map::getTick(this);
  CfgMapEvent::trig(mapEvent, v144);
}


#####################################
void __cdecl Dungeon::addMonsterHPEventInfo(Dungeon *const this, MonsterDungeon *pMonster)
{
  CfgMapEvent *v2; // rax
  CfgMapEvent *v3; // rax
  CfgMapEvent *v5; // rax
  int v6; // ebx
  CfgMapEvent *v7; // rax
  CfgMapEvent *v8; // rax
  CfgMapEvent *v10; // rax
  CfgMapEvent *v11; // rax
  HPEvent hpEvent; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( pMonster )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 7 )
      {
        v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( *std::vector<int>::operator[](&v2->trigger_param, 0) == 2 )
        {
          v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( std::vector<int>::size(&v3->trigger_param) == 4 )
          {
            v5 = std::_List_iterator<CfgMapEvent>::operator->(&it);
            v6 = *std::vector<int>::operator[](&v5->trigger_param, 1u);
            if ( v6 == MonsterDungeon::getDungeonMid(pMonster) )
            {
              v7 = std::_List_iterator<CfgMapEvent>::operator->(&it);
              if ( *std::vector<int>::operator[](&v7->trigger_param, 2u) >= 0 )
              {
                v8 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                if ( *std::vector<int>::operator[](&v8->trigger_param, 3u) > 0 )
                {
                  *(_QWORD *)&hpEvent.id = 0;
                  hpEvent.maxhp = 0;
                  hpEvent.id = std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_id;
                  v10 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                  hpEvent.minhp = *std::vector<int>::operator[](&v10->trigger_param, 2u);
                  v11 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                  hpEvent.maxhp = *std::vector<int>::operator[](&v11->trigger_param, 3u);
                  MonsterDungeon::addEventHp(pMonster, &hpEvent);
                }
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Dungeon::checkPlayerAttrEvent(Dungeon *const this, MonsterDungeon *pMonster)
{
  CfgMapEvent *v2; // rax
  CfgMapEvent *v3; // rax
  CfgMapEvent *v4; // rax
  CfgMapEvent *v5; // rax
  int v6; // ebx
  CfgMapEvent *v8; // rax
  CfgMapEvent *v9; // rax
  int32_t v10; // ebx
  CfgMapEvent *v11; // rax
  int32_t AttrValue; // ebx
  CfgMapEvent *v13; // rax
  void (__fastcall *v14)(Dungeon *const, CfgMapEvent *, MonsterDungeon *); // r12
  CfgMapEvent *v15; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+20h] [rbp-30h] BYREF
  Player *pLeader; // [rsp+30h] [rbp-20h]
  CObjAttrs::Index_T attr; // [rsp+3Ch] [rbp-14h]

  pLeader = Dungeon::GetLeader(this);
  if ( pMonster && pLeader )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        return;
      v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( CfgMapEvent::isOpen(v2) )
      {
        v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v3) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 14 )
        {
          v4 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( std::vector<int>::size(&v4->trigger_param) == 4 )
          {
            v5 = std::_List_iterator<CfgMapEvent>::operator->(&it);
            v6 = *std::vector<int>::operator[](&v5->trigger_param, 0);
            if ( v6 == MonsterDungeon::getDungeonMid(pMonster) )
            {
              v8 = std::_List_iterator<CfgMapEvent>::operator->(&it);
              attr = *std::vector<int>::operator[](&v8->trigger_param, 1u);
              v9 = std::_List_iterator<CfgMapEvent>::operator->(&it);
              if ( *std::vector<int>::operator[](&v9->trigger_param, 2u) )
              {
                AttrValue = Unit::GetAttrValue(pLeader, attr);
                v13 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                if ( AttrValue < *std::vector<int>::operator[](&v13->trigger_param, 2u) )
                  continue;
              }
              else
              {
                v10 = Unit::GetAttrValue(pLeader, attr);
                v11 = std::_List_iterator<CfgMapEvent>::operator->(&it);
                if ( v10 >= *std::vector<int>::operator[](&v11->trigger_param, 3u) )
                  continue;
              }
              v14 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, MonsterDungeon *))*((_QWORD *)this->_vptr_Map
                                                                                          + 33);
              v15 = std::_List_iterator<CfgMapEvent>::operator*(&it);
              v14(this, v15, pMonster);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Dungeon::signDungeonCompleted(Dungeon *const this)
{
  CExtOperateLimit *OperateLimit; // rax
  std::_List_iterator<Player*> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+20h] [rbp-20h] BYREF
  int32_t nRecordId; // [rsp+34h] [rbp-Ch]
  Player *player; // [rsp+38h] [rbp-8h]

  nRecordId = Dungeon::getDungeonId(this) + 20000;
  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&it);
    if ( player )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, nRecordId, 1);
    }
  }
}


#####################################
void __cdecl Dungeon::setCanSubmit(Dungeon *const this)
{
  int8_t ConnId; // bl
  DBService *v2; // rax
  LogDungeon logDungeon; // [rsp+10h] [rbp-50h] BYREF
  std::_List_iterator<Player*> it; // [rsp+30h] [rbp-30h] BYREF
  std::_List_iterator<Player*> __x; // [rsp+40h] [rbp-20h] BYREF
  Player *player; // [rsp+48h] [rbp-18h]

  for ( it._M_node = std::list<Player *>::begin(&this->m_players)._M_node; ; std::_List_iterator<Player *>::operator++(&it) )
  {
    __x._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    if ( !std::_List_iterator<Player *>::operator!=(&it, &__x) )
      break;
    player = *std::_List_iterator<Player *>::operator*(&it);
    if ( player )
    {
      Player::checkTaskCanSubmit(player, this->m_cfgDungeon.id, this->m_cfgDungeon.type);
      memset(&logDungeon, 0, sizeof(logDungeon));
      logDungeon.cid = Player::getCid(player);
      logDungeon.did = this->m_cfgDungeon.id;
      logDungeon.type = Dungeon::getDungeonType(this);
      logDungeon.start_time = Dungeon::GetStartTime(this);
      logDungeon.finish_time = Map::getNow(this);
      logDungeon.state = 1;
      ConnId = Player::getConnId(player);
      v2 = Answer::Singleton<DBService>::instance();
      DBService::updateDungeon(v2, ConnId, &logDungeon);
    }
  }
}


#####################################
void __cdecl Dungeon::generateMonster(Dungeon *const this, const std::string *const str, bool rewardWave)
{
  std::string *v3; // rax
  const char *v4; // rax
  MonsterWait stu; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+50h] [rbp-60h] BYREF
  StringVector strIds; // [rsp+60h] [rbp-50h] BYREF
  std::string delims; // [rsp+80h] [rbp-30h] BYREF
  char v10; // [rsp+8Fh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+90h] [rbp-20h] BYREF

  std::allocator<char>::allocator(&v10);
  std::string::string(&delims, 9266714, &v10);
  Answer::StringUtility::split(&strIds, str, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v10);
  for ( it._M_current = std::vector<std::string>::begin(&strIds)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<std::string>::end(&strIds)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
      break;
    memset(&stu, 0, sizeof(stu));
    v3 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator->(&it);
    v4 = (const char *)std::string::c_str(v3);
    stu.id = atoi(v4);
    stu.rewardWave = rewardWave;
    stu.startTick = Map::getTick(this);
    std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
  }
  std::vector<std::string>::~vector(&strIds);
}


#####################################
void __cdecl Dungeon::randomMonster(Dungeon *const this, const std::string *const str, bool rewardWave)
{
  Answer::Random *v3; // rax
  std::string *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  int v7; // ebx
  std::string *v8; // rax
  const char *v9; // rax
  int v10; // eax
  std::string *v11; // rax
  const char *v12; // rax
  std::string *v13; // rax
  const char *v14; // rax
  MonsterWait stu; // [rsp+20h] [rbp-D0h] BYREF
  StringVector strIds; // [rsp+50h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+70h] [rbp-80h] BYREF
  StringVector strRands; // [rsp+80h] [rbp-70h] BYREF
  std::string delims; // [rsp+A0h] [rbp-50h] BYREF
  char v21; // [rsp+AFh] [rbp-41h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+B0h] [rbp-40h] BYREF
  std::string v23; // [rsp+C0h] [rbp-30h] BYREF
  char v24; // [rsp+CFh] [rbp-21h] BYREF
  int32_t nRand; // [rsp+D0h] [rbp-20h]
  int32_t nRate; // [rsp+D4h] [rbp-1Ch]
  int32_t nId; // [rsp+D8h] [rbp-18h]
  int32_t nBroad; // [rsp+DCh] [rbp-14h]

  v3 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v3, 0, 10000);
  nRate = 0;
  nId = 0;
  nBroad = 0;
  std::allocator<char>::allocator(&v21);
  std::string::string(&delims, L"|:,", &v21);
  Answer::StringUtility::split(&strRands, str, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v21);
  for ( it._M_current = std::vector<std::string>::begin(&strRands)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<std::string>::end(&strRands)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
      break;
    std::allocator<char>::allocator(&v24);
    std::string::string(&v23, 9266714, &v24);
    v4 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
    Answer::StringUtility::split(&strIds, v4, &v23, 0);
    std::string::~string(&v23);
    std::allocator<char>::~allocator(&v24);
    if ( std::vector<std::string>::size(&strIds) != 4 )
      goto LABEL_10;
    v5 = std::vector<std::string>::operator[](&strIds, 3u);
    v6 = (const char *)std::string::c_str(v5);
    if ( atoi(v6) )
    {
      if ( this->m_bFree )
      {
        v7 = 0;
        goto LABEL_11;
      }
    }
    else if ( !this->m_bFree )
    {
      v7 = 0;
      goto LABEL_11;
    }
    v8 = std::vector<std::string>::operator[](&strIds, 1u);
    v9 = (const char *)std::string::c_str(v8);
    v10 = atoi(v9);
    nRate += v10;
    if ( nRate >= nRand )
    {
      v11 = std::vector<std::string>::operator[](&strIds, 0);
      v12 = (const char *)std::string::c_str(v11);
      nId = atoi(v12);
      v13 = std::vector<std::string>::operator[](&strIds, 2u);
      v14 = (const char *)std::string::c_str(v13);
      nBroad = atoi(v14);
      v7 = 1;
    }
    else
    {
LABEL_10:
      v7 = 2;
    }
LABEL_11:
    std::vector<std::string>::~vector(&strIds);
    if ( v7 == 1 )
      break;
  }
  if ( nId > 0 )
  {
    *(_QWORD *)&stu.times = 0;
    stu.lastTick = 0;
    stu.id = nId;
    stu.broad = nBroad;
    *(_QWORD *)&stu.rewardWave = rewardWave;
    stu.startTick = Map::getTick(this);
    std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
  }
  std::vector<std::string>::~vector(&strRands);
}


#####################################
void __cdecl Dungeon::checkAddMonster(Dungeon *const this, int64_t curTick)
{
  MonsterWait *v2; // rcx
  std::_List_iterator<MonsterWait> v3; // rax
  std::_List_iterator<MonsterWait> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<MonsterWait> iter; // [rsp+20h] [rbp-10h] BYREF

  iter._M_node = std::list<MonsterWait>::begin(&this->m_waitMonster)._M_node;
  eiter._M_node = std::list<MonsterWait>::end(&this->m_waitMonster)._M_node;
  while ( std::_List_iterator<MonsterWait>::operator!=(&iter, &eiter) )
  {
    v2 = std::_List_iterator<MonsterWait>::operator*(&iter);
    if ( Dungeon::flashWaitMonster(this, v2, curTick) )
    {
      std::_List_iterator<MonsterWait>::operator++(&iter);
    }
    else
    {
      v3._M_node = std::_List_iterator<MonsterWait>::operator++(&iter, 0)._M_node;
      std::list<MonsterWait>::erase(&this->m_waitMonster, v3);
    }
    Dungeon::broadcastDungeonInfo(this);
  }
}


#####################################
void __cdecl Dungeon::checkDropItem(Dungeon *const this, MonsterDungeon *pMonster)
{
  int32_t DungeonId; // ebx
  CfgData *v3; // rax
  int32_t item_id; // ebx
  CfgData *v5; // rax
  int32_t tid; // ebx
  CfgData *v7; // rax
  CPoolManager *v8; // rax
  int8_t bossSign; // r12
  int32_t MonsterMid; // ebx
  int32_t droperMid; // eax
  DropItem item; // [rsp+40h] [rbp-B0h] BYREF
  Position CentosPos; // [rsp+70h] [rbp-80h] BYREF
  CDropItemGroup dropItemGroup; // [rsp+80h] [rbp-70h] BYREF
  DropItemVector dropItems; // [rsp+90h] [rbp-60h] BYREF
  std::string dropper; // [rsp+B0h] [rbp-40h] BYREF
  char v17; // [rsp+BFh] [rbp-31h] BYREF
  const CfgDungeonDrop *pDrop; // [rsp+C0h] [rbp-30h]
  CfgDungeonTrap *pCfgDungeonTrap; // [rsp+C8h] [rbp-28h]
  CfgTrap *pCfgTrap; // [rsp+D0h] [rbp-20h]
  Trap *pTrap; // [rsp+D8h] [rbp-18h]
  Position CurrentTile; // 0:rax.8

  DungeonId = Dungeon::getDungeonId(this);
  v3 = Answer::Singleton<CfgData>::instance();
  pDrop = CfgData::randDungeonDrop(v3, DungeonId);
  if ( pDrop )
  {
    if ( pDrop->type == 1 )
    {
      item_id = pDrop->item_id;
      v5 = Answer::Singleton<CfgData>::instance();
      pCfgDungeonTrap = CfgData::getDungeonTrap(v5, item_id);
      if ( pCfgDungeonTrap )
      {
        tid = pCfgDungeonTrap->tid;
        v7 = Answer::Singleton<CfgData>::instance();
        pCfgTrap = CfgData::getTrap(v7, tid);
        if ( pCfgTrap )
        {
          v8 = Answer::Singleton<CPoolManager>::instance();
          pTrap = CPoolManager::pop<Trap>(v8);
          if ( pTrap )
          {
            CurrentTile = StaticObj::getCurrentTile(pMonster);
            Trap::init(pTrap, this, CurrentTile, pCfgTrap);
            Map::addTrap(this, pTrap);
          }
        }
      }
    }
    else if ( !pDrop->type )
    {
      item.itemId = pDrop->item_id;
      item.itemClass = pDrop->item_class;
      item.bindType = pDrop->bind_type;
      item.itemCount = 1;
      std::vector<DropItem>::vector(&dropItems);
      std::vector<DropItem>::push_back(&dropItems, &item);
      CDropItemGroup::CDropItemGroup(&dropItemGroup);
      CentosPos = StaticObj::getCurrentTile(pMonster);
      bossSign = Monster::getBossSign(pMonster);
      MonsterMid = Monster::getMid(pMonster);
      std::allocator<char>::allocator(&v17);
      std::string::string(&dropper, &unk_8D658F, &v17);
      droperMid = Monster::getMid(pMonster);
      CDropItemGroup::init(
        &dropItemGroup,
        0,
        this,
        &CentosPos,
        0,
        2,
        droperMid,
        &dropItems,
        &dropper,
        MonsterMid,
        bossSign,
        1);
      std::string::~string(&dropper);
      std::allocator<char>::~allocator(&v17);
      Map::addDropItemGroup(this, &dropItemGroup);
      CDropItemGroup::~CDropItemGroup(&dropItemGroup);
      std::vector<DropItem>::~vector(&dropItems);
    }
  }
}


#####################################
bool __cdecl Dungeon::flashWaitMonster(Dungeon *const this, MonsterWait *const waitAddMonster, int64_t curTick)
{
  int32_t id; // ebx
  CfgData *v4; // rax
  Position *v6; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v7; // rax
  int32_t v8; // r14d
  bool v9; // r13
  int32_t v10; // r12d
  int32_t v11; // edx
  Position *M_current; // rbx
  __gnu_cxx::__normal_iterator<Position*,std::vector<Position> > v13; // rax
  int32_t broad; // r14d
  bool rewardWave; // r13
  int32_t v16; // r12d
  int32_t v17; // edx
  int32_t v18; // eax
  Position pos; // [rsp+20h] [rbp-80h] BYREF
  std::vector<Position> positions; // [rsp+30h] [rbp-70h] BYREF
  PosVt vPos; // [rsp+50h] [rbp-50h] BYREF
  CfgDungeonMonster *pCfgDungeonMonster; // [rsp+68h] [rbp-38h]
  int32_t i; // [rsp+70h] [rbp-30h]
  int32_t x; // [rsp+74h] [rbp-2Ch]
  int32_t y; // [rsp+78h] [rbp-28h]
  int32_t i_0; // [rsp+7Ch] [rbp-24h]

  id = waitAddMonster->id;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfgDungeonMonster = CfgData::getDungeonMonster(v4, id);
  if ( !pCfgDungeonMonster )
    return 0;
  if ( pCfgDungeonMonster->count < 0 )
    return 0;
  if ( curTick - waitAddMonster->startTick < pCfgDungeonMonster->wait )
    return 1;
  if ( curTick - waitAddMonster->lastTick < pCfgDungeonMonster->delay )
    return 1;
  ++waitAddMonster->times;
  waitAddMonster->lastTick = curTick;
  if ( (int)std::vector<Position>::size(&pCfgDungeonMonster->randpos) < pCfgDungeonMonster->count )
  {
    if ( pCfgDungeonMonster->count == 1 )
    {
      Dungeon::flashMonster(
        this,
        pCfgDungeonMonster,
        pCfgDungeonMonster->x,
        pCfgDungeonMonster->y,
        waitAddMonster->rewardWave,
        waitAddMonster->broad);
    }
    else
    {
      std::vector<Position>::vector(&positions);
      for ( x = -2; x <= 1; ++x )
      {
        for ( y = -2; y <= 1; ++y )
        {
          Position::Position(&pos, x + pCfgDungeonMonster->x, y + pCfgDungeonMonster->y);
          if ( Map::isWalkablePosition(this, pos.x, pos.y) )
            std::vector<Position>::push_back(&positions, &pos);
        }
      }
      M_current = std::vector<Position>::end(&positions)._M_current;
      v13._M_current = std::vector<Position>::begin(&positions)._M_current;
      std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
        v13,
        (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)M_current);
      for ( i_0 = 0; pCfgDungeonMonster->count > i_0; ++i_0 )
      {
        v18 = std::vector<Position>::size(&positions);
        if ( v18 <= i_0 )
          break;
        broad = waitAddMonster->broad;
        rewardWave = waitAddMonster->rewardWave;
        v16 = std::vector<Position>::operator[](&positions, i_0)->y;
        v17 = std::vector<Position>::operator[](&positions, i_0)->x;
        Dungeon::flashMonster(this, pCfgDungeonMonster, v17, v16, rewardWave, broad);
      }
      std::vector<Position>::~vector(&positions);
    }
  }
  else
  {
    std::vector<Position>::vector(&vPos, &pCfgDungeonMonster->randpos);
    v6 = std::vector<Position>::end(&vPos)._M_current;
    v7._M_current = std::vector<Position>::begin(&vPos)._M_current;
    std::random_shuffle<__gnu_cxx::__normal_iterator<Position *,std::vector<Position>>>(
      v7,
      (__gnu_cxx::__normal_iterator<Position*,std::vector<Position> >)v6);
    for ( i = 0; pCfgDungeonMonster->count > i; ++i )
    {
      v8 = waitAddMonster->broad;
      v9 = waitAddMonster->rewardWave;
      v10 = std::vector<Position>::operator[](&vPos, i)->y;
      v11 = std::vector<Position>::operator[](&vPos, i)->x;
      Dungeon::flashMonster(this, pCfgDungeonMonster, v11, v10, v9, v8);
    }
    std::vector<Position>::~vector(&vPos);
  }
  return waitAddMonster->times < pCfgDungeonMonster->times;
}


#####################################
void __cdecl Dungeon::flashMonster(
        Dungeon *const this,
        CfgDungeonMonster *pCfgDungeonMonster,
        int32_t x,
        int32_t y,
        bool rewardWave,
        int32_t nBroad)
{
  CfgData *v6; // rax
  CPoolManager *v7; // rax
  int32_t m_nMonsterBuff; // ebx
  CfgData *v9; // rax
  int32_t v10; // edx
  Buff *v11; // rbx
  int8_t ConnId; // bl
  GameService *v14; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v17; // bl
  GameService *v18; // rax
  std::pair<const int,MonsterWave> *v19; // rax
  MonsterWave monsterWave; // [rsp+30h] [rbp-120h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > itMonsterWave; // [rsp+50h] [rbp-100h] BYREF
  CfgMapMonster cfgmapmonster; // [rsp+60h] [rbp-F0h] BYREF
  UnitHandle launcher; // [rsp+80h] [rbp-D0h] BYREF
  std::string p_strFamilyName; // [rsp+90h] [rbp-C0h] BYREF
  char v29; // [rsp+9Fh] [rbp-B1h] BYREF
  std::string val; // [rsp+A0h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > __x; // [rsp+B0h] [rbp-A0h] BYREF
  std::pair<const int,MonsterWave> v32; // [rsp+D0h] [rbp-80h] BYREF
  int32_t nMid; // [rsp+FCh] [rbp-54h]
  const CfgMonster *pCfgMonster; // [rsp+100h] [rbp-50h]
  MonsterDungeon *pMonster; // [rsp+108h] [rbp-48h]
  CfgBuff *pCfgBuff; // [rsp+110h] [rbp-40h]
  Buff *pBuff; // [rsp+118h] [rbp-38h]
  Player *pLeader; // [rsp+120h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+128h] [rbp-28h]

  nMid = CfgDungeonMonster::GetMid(pCfgDungeonMonster);
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgMonster = CfgData::getMonster(v6, nMid);
  if ( pCfgMonster )
  {
    v7 = Answer::Singleton<CPoolManager>::instance();
    pMonster = CPoolManager::pop<MonsterDungeon>(v7);
    if ( pMonster )
    {
      cfgmapmonster.id = 0;
      *(_DWORD *)&cfgmapmonster.hide = 0;
      cfgmapmonster.Day = 0;
      cfgmapmonster.mapid = Dungeon::GetId(this);
      cfgmapmonster.monsterid = nMid;
      cfgmapmonster.x = x;
      cfgmapmonster.y = y;
      cfgmapmonster.side = pCfgDungeonMonster->side;
      MonsterDungeon::init(pMonster, this, pCfgDungeonMonster, pCfgMonster, &cfgmapmonster);
      if ( this->m_nMonsterBuff > 0 )
      {
        m_nMonsterBuff = this->m_nMonsterBuff;
        v9 = Answer::Singleton<CfgData>::instance();
        pCfgBuff = CfgData::getBuff(v9, m_nMonsterBuff);
        if ( pCfgBuff )
        {
          launcher.id = (*((__int64 (__fastcall **)(MonsterDungeon *))pMonster->_vptr_Entity + 12))(pMonster);
          launcher.type = v10;
          v11 = (Buff *)operator new(0x60u);
          Buff::Buff(v11, pMonster, pCfgBuff, &launcher, 2, 0);
          pBuff = v11;
          if ( v11 )
          {
            Unit::addBuff(pMonster, pBuff);
            (*((void (__fastcall **)(MonsterDungeon *, __int64))pMonster->_vptr_Entity + 22))(pMonster, 100);
          }
        }
      }
      if ( Monster::GetFamilyId(pMonster) <= 0 && cfgmapmonster.side > 0 )
      {
        std::allocator<char>::allocator(&v29);
        std::string::string(&p_strFamilyName, &unk_8D658F, &v29);
        Monster::SetFamilyId(pMonster, 1, &p_strFamilyName);
        std::string::~string(&p_strFamilyName);
        std::allocator<char>::~allocator(&v29);
      }
      (*((void (__fastcall **)(Dungeon *const, MonsterDungeon *, _QWORD, _QWORD))this->_vptr_Map + 28))(
        this,
        pMonster,
        (unsigned int)cfgmapmonster.x,
        (unsigned int)cfgmapmonster.y);
      Dungeon::addMonsterHPEventInfo(this, pMonster);
      Dungeon::checkPlayerAttrEvent(this, pMonster);
      MonsterDungeon::runOnRoad(pMonster);
      if ( nBroad > 0 )
      {
        pLeader = Dungeon::GetLeader(this);
        if ( pLeader )
        {
          ConnId = Player::getConnId(pLeader);
          v14 = Answer::Singleton<GameService>::instance();
          packet = GameService::popNetpacket(v14, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
          if ( packet )
          {
            Answer::NetPacket::writeInt32(packet, nBroad);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Cid = Player::getCid(pLeader);
            Answer::NetPacket::writeInt64(packet, Cid);
            Answer::NetPacket::writeInt32(packet, pCfgMonster->mid);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v17 = Player::getConnId(pLeader);
            v18 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v18, v17, packet);
          }
        }
      }
      itMonsterWave._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &pCfgDungeonMonster->wave)._M_node;
      __x._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&itMonsterWave, &__x) )
      {
        v19 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&itMonsterWave);
        ++v19->second.count;
      }
      else
      {
        *(_QWORD *)&monsterWave.count = 1;
        *(_QWORD *)&monsterWave.escaped = 0;
        monsterWave.startTime = Map::getTick(this);
        *(_QWORD *)&monsterWave.rewardWave = rewardWave;
        std::pair<int const,MonsterWave>::pair(&v32, &pCfgDungeonMonster->wave, &monsterWave);
        std::map<int,MonsterWave>::insert(&this->m_monsterWave, &v32);
      }
    }
  }
}


#####################################
void __cdecl Dungeon::SetHard(Dungeon *const this, int8_t nHard)
{
  if ( nHard > 0 && nHard <= 5 )
    this->m_nHard = nHard;
}


#####################################
void __cdecl Dungeon::OpenEvent(Dungeon *const this, int32_t nEvent)
{
  int64_t Tick; // rax

  Tick = Map::getTick(this);
  IMapEvent::openEvent(&this->IMapEvent, nEvent, Tick);
}


#####################################
void __cdecl Dungeon::setState(Dungeon *const this, DungeonState state, int32_t param)
{
  this->m_state = state;
  this->m_stateTick = Map::getTick(this);
  this->m_stateParam = param;
  if ( this->m_state == DungeonState::DS_SUMMON )
  {
    this->m_nSummStart = this->m_stateTick;
    Dungeon::sendStartSummon(this);
  }
}


#####################################
void __cdecl Dungeon::start(Dungeon *const this, bool bFree)
{
  CfgData *v2; // rax
  const CLibraryTable *CLibraryTable; // rax
  int32_t id; // ebx
  CfgData *v5; // rax
  const CLibraryTable *v6; // rax
  MemChrBag *p_Item; // rbx
  CLibraryItem *v8; // rax
  CLibraryItem *v9; // rax
  int32_t v10; // ebx
  CfgData *v11; // rax
  const CLibraryTable *v12; // rax
  MemChrBag *v13; // rbx
  CLibraryItem *v14; // rax
  CLibraryItem *v15; // rax
  int32_t v16; // ebx
  CfgData *v17; // rax
  const CLibraryTable *v18; // rax
  MemChrBag *v19; // rbx
  CLibraryItem *v20; // rax
  int64_t Tick; // rax
  __gnu_cxx::__normal_iterator<CLibraryItem*,std::vector<CLibraryItem> > it; // [rsp+10h] [rbp-90h] BYREF
  CLibraryItem p___x; // [rsp+20h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<CLibraryItem*,std::vector<CLibraryItem> > __rhs; // [rsp+40h] [rbp-60h] BYREF
  int32_t itemCount; // [rsp+4Ch] [rbp-54h]
  int32_t LeftCount; // [rsp+50h] [rbp-50h]
  int32_t j; // [rsp+54h] [rbp-4Ch]
  const CfgLibraryQuality *pQuality; // [rsp+58h] [rbp-48h]
  int32_t i; // [rsp+64h] [rbp-3Ch]
  const CfgLibraryItem *pItem; // [rsp+68h] [rbp-38h]
  int32_t i_0; // [rsp+74h] [rbp-2Ch]
  const CfgLibraryItem *pItem_0; // [rsp+78h] [rbp-28h]
  int j_0; // [rsp+84h] [rbp-1Ch]
  const CfgLibraryItem *pItem_1; // [rsp+88h] [rbp-18h]

  this->m_bFree = bFree;
  if ( !this->m_nStartTime )
    this->m_nStartTime = Map::getNow(this);
  if ( this->m_cfgDungeon.type == 32 )
  {
    this->m_nGatherTims = 0;
    this->m_MaxnProbability = 0;
    std::vector<CLibraryItem>::clear(&this->m_LibraryRewardVector);
    p___x.IsGet = 0;
    memset(&p___x.nProbability, 0, 28);
    CLibraryItem::CLibraryItem(&p___x);
    std::vector<CLibraryItem>::resize(&this->m_LibraryRewardVector, 0xCu, &p___x);
    CLibraryItem::~CLibraryItem(&p___x);
    itemCount = 0;
    for ( j = 5; j > 2; --j )
    {
      v2 = Answer::Singleton<CfgData>::instance();
      CLibraryTable = CfgData::GetCLibraryTable(v2);
      pQuality = CLibraryTable::GetCfgLibraryQuality(CLibraryTable, j);
      if ( pQuality )
      {
        for ( i = 0; pQuality->nCount > i; ++i )
        {
          id = this->m_cfgDungeon.id;
          v5 = Answer::Singleton<CfgData>::instance();
          v6 = CfgData::GetCLibraryTable(v5);
          pItem = CLibraryTable::GetLibraryItem(v6, j, id);
          if ( pItem )
          {
            if ( itemCount > 11 )
              break;
            std::vector<CLibraryItem>::operator[](&this->m_LibraryRewardVector, itemCount)->IsGet = 0;
            p_Item = &pItem->Item;
            v8 = std::vector<CLibraryItem>::operator[](&this->m_LibraryRewardVector, itemCount);
            std::vector<MemChrBag>::push_back(&v8->Items, p_Item);
            v9 = std::vector<CLibraryItem>::operator[](&this->m_LibraryRewardVector, itemCount);
            v9->nProbability = pItem->Probability;
            this->m_MaxnProbability += pItem->Probability;
            ++itemCount;
          }
        }
      }
    }
    LeftCount = 12 - itemCount;
    for ( i_0 = 0; i_0 < LeftCount; ++i_0 )
    {
      v10 = this->m_cfgDungeon.id;
      v11 = Answer::Singleton<CfgData>::instance();
      v12 = CfgData::GetCLibraryTable(v11);
      pItem_0 = CLibraryTable::GetLibraryItem(v12, 2, v10);
      if ( pItem_0 )
      {
        if ( itemCount > 11 )
          break;
        std::vector<CLibraryItem>::operator[](&this->m_LibraryRewardVector, itemCount)->IsGet = 0;
        v13 = &pItem_0->Item;
        v14 = std::vector<CLibraryItem>::operator[](&this->m_LibraryRewardVector, itemCount);
        std::vector<MemChrBag>::push_back(&v14->Items, v13);
        v15 = std::vector<CLibraryItem>::operator[](&this->m_LibraryRewardVector, itemCount);
        v15->nProbability = pItem_0->Probability;
        this->m_MaxnProbability += pItem_0->Probability;
        ++itemCount;
      }
    }
    for ( it._M_current = std::vector<CLibraryItem>::begin(&this->m_LibraryRewardVector)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator++(&it, 0) )
    {
      __rhs._M_current = std::vector<CLibraryItem>::end(&this->m_LibraryRewardVector)._M_current;
      if ( !__gnu_cxx::operator!=<CLibraryItem *,std::vector<CLibraryItem>>(&it, &__rhs) )
        break;
      for ( j_0 = 0; j_0 <= 3; ++j_0 )
      {
        v16 = this->m_cfgDungeon.id;
        v17 = Answer::Singleton<CfgData>::instance();
        v18 = CfgData::GetCLibraryTable(v17);
        pItem_1 = CLibraryTable::GetLibraryItem(v18, 1, v16);
        if ( pItem_1 )
        {
          v19 = &pItem_1->Item;
          v20 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it);
          std::vector<MemChrBag>::push_back(&v20->Items, v19);
        }
      }
    }
  }
  if ( this->m_state == DungeonState::DS_WAIT && !std::list<int>::empty(&this->m_waitEvent) )
  {
    Tick = Map::getTick(this);
    IMapEvent::openEvents(&this->IMapEvent, &this->m_waitEvent, Tick);
    std::list<int>::clear(&this->m_waitEvent);
  }
  if ( this->m_cfgDungeon.type == 12 )
    Dungeon::setState(this, DungeonState::DS_WAIT, 5);
  else
    Dungeon::setState(this, DungeonState::DS_RUNNING, 0);
}


#####################################
void __cdecl Dungeon::restart(Dungeon *const this, bool bFree)
{
  Monster *v2; // rax
  MonsterDungeon *v3; // rax
  MonsterDungeon *v4; // rbx
  GameService *v5; // rax
  CPoolManager *v6; // rax
  Plant *v7; // rax
  PlantDungeon *v8; // rax
  CPoolManager *v9; // rax
  Trap *v10; // rbx
  CPoolManager *v11; // rax
  int64_t Tick; // rbx
  int32_t id; // r12d
  CfgData *v14; // rax
  const CfgMapEventList *DungeonEvent; // rax
  Player *Leader; // rdx
  std::_List_iterator<Trap*> it_1; // [rsp+10h] [rbp-80h] BYREF
  std::_List_iterator<Plant*> it_0; // [rsp+20h] [rbp-70h] BYREF
  std::_List_iterator<Monster*> it; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+40h] [rbp-50h] BYREF
  std::_List_iterator<Plant*> v21; // [rsp+50h] [rbp-40h] BYREF
  std::_List_iterator<Trap*> v22; // [rsp+60h] [rbp-30h] BYREF
  MonsterDungeon *monster; // [rsp+70h] [rbp-20h]
  PlantDungeon *plant; // [rsp+78h] [rbp-18h]

  if ( this->m_state == DungeonState::DS_WIN )
  {
    this->m_bFree = bFree;
    for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
          ;
          std::_List_iterator<Monster *>::operator++(&it) )
    {
      __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
      if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
        break;
      v2 = *std::_List_iterator<Monster *>::operator*(&it);
      if ( v2 )
        v3 = (MonsterDungeon *)__dynamic_cast(
                                 v2,
                                 (const struct __class_type_info *)&`typeinfo for'Monster,
                                 (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                                 0);
      else
        v3 = 0;
      monster = v3;
      if ( v3 )
      {
        v4 = monster;
        v5 = Answer::Singleton<GameService>::instance();
        GameService::removeMonster(v5, v4);
        v6 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<MonsterDungeon>(v6, monster);
      }
    }
    std::list<Monster *>::clear(&this->m_monsters);
    for ( it_0._M_node = std::list<Plant *>::begin(&this->m_plants)._M_node;
          ;
          std::_List_iterator<Plant *>::operator++(&it_0) )
    {
      v21._M_node = std::list<Plant *>::end(&this->m_plants)._M_node;
      if ( !std::_List_iterator<Plant *>::operator!=(&it_0, &v21) )
        break;
      v7 = *std::_List_iterator<Plant *>::operator*(&it_0);
      if ( v7 )
        v8 = (PlantDungeon *)__dynamic_cast(
                               v7,
                               (const struct __class_type_info *)&`typeinfo for'Plant,
                               (const struct __class_type_info *)&`typeinfo for'PlantDungeon,
                               0);
      else
        v8 = 0;
      plant = v8;
      if ( v8 )
      {
        v9 = Answer::Singleton<CPoolManager>::instance();
        CPoolManager::push<PlantDungeon>(v9, plant);
      }
    }
    std::list<Plant *>::clear(&this->m_plants);
    for ( it_1._M_node = std::list<Trap *>::begin(&this->m_traps)._M_node; ; std::_List_iterator<Trap *>::operator++(&it_1) )
    {
      v22._M_node = std::list<Trap *>::end(&this->m_traps)._M_node;
      if ( !std::_List_iterator<Trap *>::operator!=(&it_1, &v22) )
        break;
      v10 = *std::_List_iterator<Trap *>::operator*(&it_1);
      v11 = Answer::Singleton<CPoolManager>::instance();
      CPoolManager::push<Trap>(v11, v10);
    }
    std::list<Trap *>::clear(&this->m_traps);
    IMapEvent::clear(&this->IMapEvent);
    bzero(&this->m_finshInfo, 0x20u);
    std::map<int,MonsterWave>::clear(&this->m_monsterWave);
    std::list<Monster *>::clear(&this->m_buildTower);
    std::list<DungeonTower>::clear(&this->m_waitTower);
    std::list<MonsterWait>::clear(&this->m_waitMonster);
    std::list<DungeonReward>::clear(&this->m_playerReward);
    std::list<long>::clear(&this->m_memberList);
    std::list<DamageSum>::clear(&this->m_damages);
    this->m_needBroadcastDamage = 0;
    this->m_dRatio = 1.0;
    this->m_nAddonTime = 0;
    this->m_nStartTime = 0;
    std::list<Position>::clear(&this->m_lstStack);
    this->m_TeamLeaderId = 0;
    Tick = Map::getTick(this);
    id = this->m_cfgDungeon.id;
    v14 = Answer::Singleton<CfgData>::instance();
    DungeonEvent = CfgData::getDungeonEvent(v14, id);
    IMapEvent::init(&this->IMapEvent, DungeonEvent, Tick);
    Leader = Dungeon::GetLeader(this);
    Dungeon::initPlayerInfo(this, Leader);
    Dungeon::broadcastDungeonInfo(this);
    this->m_nStartTime = Map::getNow(this);
    Dungeon::setState(this, DungeonState::DS_RUNNING, 0);
  }
}


#####################################
void __cdecl Dungeon::initPlayerInfo(Dungeon *const this, Player *player)
{
  int32_t player_buff; // ebx
  CfgData *v3; // rax
  int32_t v4; // edx
  Buff *v5; // rbx
  CfgMapEvent *v6; // rax
  CfgMapEvent *v7; // rax
  CfgMapEvent *v9; // rax
  CfgMapEvent *v10; // rax
  int32_t v11; // edx
  CharId_t cid; // rbx
  int32_t DungeonId; // ebx
  CfgData *v14; // rax
  DungeonReward reward; // [rsp+20h] [rbp-C0h] BYREF
  std::_List_iterator<DungeonReward> eiter; // [rsp+60h] [rbp-80h] BYREF
  std::_List_iterator<DungeonReward> iter; // [rsp+70h] [rbp-70h] BYREF
  std::_List_iterator<CfgMapEvent> it; // [rsp+80h] [rbp-60h] BYREF
  UnitHandle launcher; // [rsp+90h] [rbp-50h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+A0h] [rbp-40h] BYREF
  CfgBuff *pCfgBuff; // [rsp+A8h] [rbp-38h]
  Buff *pBuff; // [rsp+B0h] [rbp-30h]
  CfgDungeonReward *pReward; // [rsp+B8h] [rbp-28h]

  if ( player )
  {
    player_buff = this->m_cfgDungeon.player_buff;
    v3 = Answer::Singleton<CfgData>::instance();
    pCfgBuff = CfgData::getBuff(v3, player_buff);
    if ( pCfgBuff )
    {
      launcher.id = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 12))(player);
      launcher.type = v4;
      v5 = (Buff *)operator new(0x60u);
      Buff::Buff(v5, player, pCfgBuff, &launcher, 2, 0);
      pBuff = v5;
      if ( v5 )
        Unit::addBuff(player, pBuff);
    }
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 7 )
      {
        v6 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( *std::vector<int>::operator[](&v6->trigger_param, 0) == 1 )
        {
          v7 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( std::vector<int>::size(&v7->trigger_param) == 3 )
          {
            v9 = std::_List_iterator<CfgMapEvent>::operator->(&it);
            if ( *std::vector<int>::operator[](&v9->trigger_param, 2u) > 0 )
            {
              v10 = std::_List_iterator<CfgMapEvent>::operator->(&it);
              v11 = *std::vector<int>::operator[](&v10->trigger_param, 2u);
              Player::addEventHp(player, v11);
            }
          }
        }
      }
    }
    iter._M_node = std::list<DungeonReward>::begin(&this->m_playerReward)._M_node;
    eiter._M_node = std::list<DungeonReward>::end(&this->m_playerReward)._M_node;
    while ( std::_List_iterator<DungeonReward>::operator!=(&iter, &eiter) )
    {
      cid = std::_List_iterator<DungeonReward>::operator->(&iter)->cid;
      if ( cid == Player::getCid(player) )
        break;
      std::_List_iterator<DungeonReward>::operator++(&iter);
    }
    if ( std::_List_iterator<DungeonReward>::operator==(&iter, &eiter) )
    {
      memset(&reward, 0, sizeof(reward));
      reward.cid = Player::getCid(player);
      DungeonId = Dungeon::getDungeonId(this);
      v14 = Answer::Singleton<CfgData>::instance();
      pReward = CfgData::getDungeonReward(v14, DungeonId);
      if ( pReward )
      {
        reward.exp = pReward->exp;
        reward.cash = pReward->cash;
        reward.money = pReward->money;
      }
      std::list<DungeonReward>::push_back(&this->m_playerReward, &reward);
    }
  }
}


#####################################
void __cdecl Dungeon::onPlayerLeave(Dungeon *const this, Player *player)
{
  ChrTask *Task; // rax

  if ( player )
  {
    if ( this->m_cfgDungeon.task_id > 0 )
    {
      Task = Player::GetTask(player);
      ChrTask::CleanTaskType(Task, 38);
    }
    if ( this->m_state == DungeonState::DS_RUNNING )
    {
      Dungeon::sendDungeonResult(this, player, 0);
    }
    else if ( this->m_state == DungeonState::DS_WIN )
    {
      Dungeon::sendDungeonResult(this, player, this->m_stateParam);
      if ( Dungeon::getDungeonType(this) == 15 && Player::GetSysSettingInfo(player, 5)
        || Dungeon::getDungeonType(this) == 23 && Player::GetSysSettingInfo(player, 6) )
      {
        Dungeon::GetReward(this, player, 2, 1);
      }
      else
      {
        Dungeon::GetReward(this, player, 1, 0);
      }
    }
    Player::FullHPAndSync(player);
  }
}


#####################################
bool __cdecl Dungeon::onEndDungeon(Dungeon *const this, Player *player)
{
  if ( !player || Dungeon::GetLeader(this) != player )
    return 0;
  if ( this->m_cfgDungeon.type != 15 && this->m_cfgDungeon.type != 23 )
    return 0;
  if ( this->m_state != DungeonState::DS_RUNNING )
    return 0;
  Dungeon::win(this, 0);
  return 1;
}


#####################################
void __cdecl Dungeon::calWinStar(Dungeon *const this)
{
  int *v1; // rax
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > iter; // [rsp+10h] [rbp-20h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+20h] [rbp-10h] BYREF
  int32_t nWinStar; // [rsp+28h] [rbp-8h]
  int32_t nUsedTime; // [rsp+2Ch] [rbp-4h]

  if ( !std::vector<int>::empty(&this->m_cfgDungeon.win_star) )
  {
    nWinStar = std::vector<int>::size(&this->m_cfgDungeon.win_star);
    nUsedTime = Map::getNow(this) - this->m_nStartTime;
    for ( iter._M_current = std::vector<int>::begin(&this->m_cfgDungeon.win_star)._M_current;
          ;
          __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&iter) )
    {
      __rhs._M_current = std::vector<int>::end(&this->m_cfgDungeon.win_star)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&iter, &__rhs) )
        break;
      v1 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&iter);
      if ( *v1 >= nUsedTime )
        break;
      --nWinStar;
    }
    this->m_nWinStar = nWinStar;
  }
}


#####################################
void __cdecl Dungeon::calWinReward(Dungeon *const this)
{
  int32_t normal_wave; // r12d
  int32_t DungeonId; // ebx
  CfgData *v3; // rax
  const CfgDungeonScoreTable *DungeonScoreTable; // rax
  DungeonReward *v5; // rax
  std::_List_iterator<DungeonReward> iter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<DungeonReward> __x; // [rsp+20h] [rbp-20h] BYREF
  const CfgDungeonScore *pCfgScore; // [rsp+28h] [rbp-18h]

  if ( Dungeon::getDungeonType(this) == 23 )
  {
    normal_wave = this->m_finshInfo.normal_wave;
    DungeonId = Dungeon::getDungeonId(this);
    v3 = Answer::Singleton<CfgData>::instance();
    DungeonScoreTable = CfgData::GetDungeonScoreTable(v3);
    pCfgScore = CfgDungeonScoreTable::GetDungeonScore(DungeonScoreTable, DungeonId, normal_wave);
    if ( pCfgScore )
    {
      for ( iter._M_node = std::list<DungeonReward>::begin(&this->m_playerReward)._M_node;
            ;
            std::_List_iterator<DungeonReward>::operator++(&iter) )
      {
        __x._M_node = std::list<DungeonReward>::end(&this->m_playerReward)._M_node;
        if ( !std::_List_iterator<DungeonReward>::operator!=(&iter, &__x) )
          break;
        v5 = std::_List_iterator<DungeonReward>::operator->(&iter);
        v5->Item = pCfgScore->Item;
      }
      Dungeon::updateExpDungeonRank(this);
    }
  }
}


#####################################
void __cdecl Dungeon::onMonsterHPEvent(Dungeon *const this, MonsterDungeon *monster, int32_t id)
{
  CfgMapEvent *v3; // rax
  CfgMapEvent *v4; // rax
  void (__fastcall *v6)(Dungeon *const, CfgMapEvent *, MonsterDungeon *); // r12
  CfgMapEvent *v7; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( monster )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( CfgMapEvent::isOpen(v3) )
      {
        v4 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v4) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_id == id )
        {
          v6 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, MonsterDungeon *))*((_QWORD *)this->_vptr_Map + 33);
          v7 = std::_List_iterator<CfgMapEvent>::operator*(&it);
          v6(this, v7, monster);
        }
      }
    }
  }
}


#####################################
void __cdecl Dungeon::onPlayerHPEvent(Dungeon *const this, Player *player)
{
  CfgMapEvent *v2; // rax
  CfgMapEvent *v3; // rax
  CfgMapEvent *v4; // rax
  void (__fastcall *v6)(Dungeon *const, CfgMapEvent *, Player *); // r12
  CfgMapEvent *v7; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( CfgMapEvent::isOpen(v2) )
      {
        v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v3) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 7 )
        {
          v4 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( std::vector<int>::size(&v4->trigger_param) == 3 )
          {
            v6 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, Player *))*((_QWORD *)this->_vptr_Map + 33);
            v7 = std::_List_iterator<CfgMapEvent>::operator*(&it);
            v6(this, v7, player);
            Player::addEventHp(player, 0);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Dungeon::onPlayerDie(Dungeon *const this, Player *player)
{
  CfgMapEvent *v2; // rax
  CfgMapEvent *v3; // rax
  void (__fastcall *v5)(Dungeon *const, CfgMapEvent *, Player *); // r12
  CfgMapEvent *v6; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      if ( CfgMapEvent::isOpen(v2) )
      {
        v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v3) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 9 )
        {
          v5 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, Player *))*((_QWORD *)this->_vptr_Map + 33);
          v6 = std::_List_iterator<CfgMapEvent>::operator*(&it);
          v5(this, v6, player);
        }
      }
    }
  }
}


#####################################
void __cdecl Dungeon::onMonsterDie(Dungeon *const this, MonsterDungeon *monster)
{
  std::pair<const int,MonsterWave> *v3; // rax
  std::pair<const int,MonsterWave> *v4; // rax
  int16_t PosY; // r13
  int16_t PosX; // r12
  Player *v7; // rbx
  DungeonReward *v8; // rbx
  int32_t money; // r12d
  int32_t get_money; // ebx
  CharId_t Cid; // rbx
  DungeonReward *v12; // rax
  int32_t m_nMonsterScore; // ebx
  CfgMapEvent *v14; // rax
  CfgMapEvent *v15; // rax
  void (__fastcall *v17)(Dungeon *const, CfgMapEvent *); // rbx
  CfgMapEvent *v18; // rdx
  CfgMapEvent *v19; // rax
  int v20; // ebx
  CfgMapEvent *v21; // rax
  int v22; // ebx
  int32_t v24; // ebx
  CfgMapEvent *v25; // rax
  void (__fastcall *v26)(Dungeon *const, CfgMapEvent *, MonsterDungeon *); // r12
  CfgMapEvent *v27; // rcx
  std::_List_iterator<CfgMapEvent> it_1; // [rsp+10h] [rbp-E0h] BYREF
  std::_List_iterator<DungeonReward> eiter_0; // [rsp+20h] [rbp-D0h] BYREF
  std::_List_iterator<DungeonReward> iter_0; // [rsp+30h] [rbp-C0h] BYREF
  std::_List_iterator<DungeonReward> eiter; // [rsp+40h] [rbp-B0h] BYREF
  std::_List_iterator<DungeonReward> iter; // [rsp+50h] [rbp-A0h] BYREF
  std::_List_iterator<Player*> it_0; // [rsp+60h] [rbp-90h] BYREF
  PlayerList players; // [rsp+70h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it; // [rsp+80h] [rbp-70h] BYREF
  int __x; // [rsp+8Ch] [rbp-64h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v37; // [rsp+90h] [rbp-60h] BYREF
  std::_List_iterator<Player*> v38; // [rsp+A0h] [rbp-50h] BYREF
  std::_List_iterator<CfgMapEvent> v39; // [rsp+B0h] [rbp-40h] BYREF
  bool NeedUpDataWave; // [rsp+BFh] [rbp-31h]
  Player *pLeader; // [rsp+C0h] [rbp-30h]
  int32_t AddExp; // [rsp+CCh] [rbp-24h]

  if ( !monster )
    return;
  Dungeon::checkDropItem(this, monster);
  if ( this->m_state != DungeonState::DS_BOSS )
  {
    NeedUpDataWave = 1;
    if ( Dungeon::getDungeonType(this) == 15 )
      NeedUpDataWave = Monster::getSide(monster) == 1;
    __x = MonsterDungeon::getWave(monster);
    it._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &__x)._M_node;
    if ( NeedUpDataWave )
    {
      v37._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it, &v37) )
      {
        v3 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it);
        ++v3->second.killed;
        v4 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it);
        if ( !MonsterWave::alive(&v4->second) )
        {
          if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it)->second.rewardWave )
            ++this->m_finshInfo.reward_wave;
          else
            ++this->m_finshInfo.normal_wave;
        }
      }
    }
    if ( Monster::getSide(monster) != 1 )
    {
      if ( Dungeon::getDungeonType(this) == 15 )
      {
        Dungeon::getPlayers((Dungeon *const)&players);
        for ( it_0._M_node = std::list<Player *>::begin(&players)._M_node;
              ;
              std::_List_iterator<Player *>::operator++(&it_0) )
        {
          v38._M_node = std::list<Player *>::end(&players)._M_node;
          if ( !std::_List_iterator<Player *>::operator!=(&it_0, &v38) )
            break;
          PosY = StaticObj::GetPosY(monster);
          PosX = StaticObj::GetPosX(monster);
          v7 = *std::_List_iterator<Player *>::operator*(&it_0);
          Dungeon::BuildTowerByMonstDie(this, v7, 12001, PosX, PosY);
        }
        std::list<Player *>::~list(&players);
      }
      else if ( Dungeon::getDungeonType(this) == 19 )
      {
        iter._M_node = std::list<DungeonReward>::begin(&this->m_playerReward)._M_node;
        eiter._M_node = std::list<DungeonReward>::end(&this->m_playerReward)._M_node;
        while ( std::_List_iterator<DungeonReward>::operator!=(&iter, &eiter) )
        {
          v8 = std::_List_iterator<DungeonReward>::operator->(&iter);
          money = v8->money;
          v8->money = money + MonsterDungeon::getMoney(monster);
          std::_List_iterator<DungeonReward>::operator++(&iter);
        }
        get_money = this->m_finshInfo.get_money;
        this->m_finshInfo.get_money = get_money + MonsterDungeon::getMoney(monster);
      }
      if ( Dungeon::getDungeonType(this) != 15 )
      {
        if ( (*((unsigned __int8 (__fastcall **)(MonsterDungeon *))monster->_vptr_Entity + 17))(monster) )
          ++this->m_finshInfo.boss_count;
        else
          ++this->m_finshInfo.kill_count;
      }
    }
    if ( Monster::getSide(monster) == 1 )
    {
      if ( Dungeon::getDungeonType(this) == 15 )
      {
        pLeader = Dungeon::GetLeader(this);
        if ( pLeader )
        {
          iter_0._M_node = std::list<DungeonReward>::begin(&this->m_playerReward)._M_node;
          eiter_0._M_node = std::list<DungeonReward>::end(&this->m_playerReward)._M_node;
          AddExp = 0;
          while ( std::_List_iterator<DungeonReward>::operator!=(&iter_0, &eiter_0) )
          {
            Cid = Player::getCid(pLeader);
            if ( Cid == std::_List_iterator<DungeonReward>::operator->(&iter_0)->cid )
            {
              AddExp = Monster::getExp(monster);
              v12 = std::_List_iterator<DungeonReward>::operator->(&iter_0);
              v12->exp += AddExp;
            }
            std::_List_iterator<DungeonReward>::operator++(&iter_0);
          }
          this->m_finshInfo.get_exp += AddExp;
        }
      }
      if ( (*((unsigned __int8 (__fastcall **)(MonsterDungeon *))monster->_vptr_Entity + 17))(monster) )
        ++this->m_finshInfo.boss_count;
      else
        ++this->m_finshInfo.kill_count;
    }
    if ( Monster::GetKillPoints(monster) > 0 )
    {
      m_nMonsterScore = this->m_nMonsterScore;
      this->m_nMonsterScore = m_nMonsterScore + Monster::GetKillPoints(monster);
    }
    for ( it_1._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it_1) )
    {
      v39._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it_1, &v39) )
      {
        Dungeon::broadcastDungeonInfo(this);
        return;
      }
      v14 = std::_List_iterator<CfgMapEvent>::operator->(&it_1);
      if ( CfgMapEvent::isOpen(v14) )
      {
        v15 = std::_List_iterator<CfgMapEvent>::operator->(&it_1);
        if ( !CfgMapEvent::isDone(v15) )
        {
          if ( std::_List_iterator<CfgMapEvent>::operator->(&it_1)->trigger_type == 2 )
          {
            v17 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *))*((_QWORD *)this->_vptr_Map + 32);
            v18 = std::_List_iterator<CfgMapEvent>::operator*(&it_1);
            v17(this, v18);
            continue;
          }
          if ( std::_List_iterator<CfgMapEvent>::operator->(&it_1)->trigger_type == 3 )
          {
            v19 = std::_List_iterator<CfgMapEvent>::operator->(&it_1);
            v20 = *std::vector<int>::operator[](&v19->trigger_param, 0);
            if ( v20 != MonsterDungeon::getDungeonMid(monster) )
              continue;
LABEL_66:
            v26 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, MonsterDungeon *))*((_QWORD *)this->_vptr_Map + 33);
            v27 = std::_List_iterator<CfgMapEvent>::operator*(&it_1);
            v26(this, v27, monster);
            continue;
          }
          if ( std::_List_iterator<CfgMapEvent>::operator->(&it_1)->trigger_type == 12 )
          {
            if ( Monster::getKiller(monster) )
            {
              v21 = std::_List_iterator<CfgMapEvent>::operator->(&it_1);
              v22 = *std::vector<int>::operator[](&v21->trigger_param, 0);
              if ( v22 == MonsterDungeon::getDungeonMid(monster) )
                goto LABEL_66;
            }
          }
          else if ( std::_List_iterator<CfgMapEvent>::operator->(&it_1)->trigger_type == 15 )
          {
            v24 = this->m_nMonsterScore;
            v25 = std::_List_iterator<CfgMapEvent>::operator->(&it_1);
            if ( v24 >= *std::vector<int>::operator[](&v25->trigger_param, 0) )
              goto LABEL_66;
          }
        }
      }
    }
  }
  if ( Dungeon::isAllMonsterDie(this) && Dungeon::isAllPlayerSummon(this) )
    Dungeon::win(this, 0);
}


#####################################
int32_t __cdecl Dungeon::onBeginGather(Dungeon *const this, Player *player)
{
  int32_t id; // ebx
  int32_t v3; // r12d
  CfgData *v4; // rax
  const CLibraryTable *CLibraryTable; // rax
  CExtCharBag *Bag; // rax
  const CfgLibraryCost *pCost; // [rsp+18h] [rbp-18h]

  if ( this->m_cfgDungeon.type != 32 )
    return 0;
  id = this->m_cfgDungeon.id;
  v3 = this->m_nGatherTims + 1;
  v4 = Answer::Singleton<CfgData>::instance();
  CLibraryTable = CfgData::GetCLibraryTable(v4);
  pCost = CLibraryTable::GetCfgLibraryCost(CLibraryTable, v3, id);
  if ( !pCost )
    return 2;
  if ( pCost->Item.m_nId >= 0
    && pCost->Item.m_nCount > 0
    && pCost->Item.m_nClass > 0
    && (Bag = Player::GetBag(player), !CExtCharBag::HasItem(Bag, &pCost->Item)) )
  {
    return 2;
  }
  else
  {
    return 0;
  }
}


#####################################
void __cdecl Dungeon::onPlantGather(Dungeon *const this, PlantDungeon *plant)
{
  CfgMapEvent *v2; // rax
  int32_t v3; // ebx
  CfgData *v4; // rax
  CfgMapEvent *v5; // rax
  CfgMapEvent *v6; // rax
  int32_t pid; // ebx
  void (__fastcall *v9)(Dungeon *const, CfgMapEvent *, _QWORD); // rbx
  CfgMapEvent *v10; // rcx
  int32_t id; // ebx
  int32_t v12; // r12d
  CfgData *v13; // rax
  const CLibraryTable *CLibraryTable; // rax
  ItemData *p_Item; // rbx
  CExtCharBag *Bag; // rax
  int32_t m_MaxnProbability; // ebx
  Answer::Random *v18; // rax
  CLibraryItem *v19; // rax
  int32_t v20; // ebx
  CLibraryItem *v21; // rax
  MemChrBag *v22; // rax
  CLibraryItem *v23; // rax
  CLibraryItem *v24; // rax
  int32_t droperMid; // eax
  DropItem stu; // [rsp+40h] [rbp-140h] BYREF
  Position CentosPos; // [rsp+70h] [rbp-110h] BYREF
  CDropItemGroup pDropItemGroup; // [rsp+80h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > ItemIt; // [rsp+90h] [rbp-F0h] BYREF
  int32_t UnBindCount; // [rsp+98h] [rbp-E8h] BYREF
  int32_t BindCount; // [rsp+9Ch] [rbp-E4h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+A0h] [rbp-E0h] BYREF
  __gnu_cxx::__normal_iterator<CLibraryItem*,std::vector<CLibraryItem> > it_0; // [rsp+B0h] [rbp-D0h] BYREF
  DropItemVector dropItems; // [rsp+C0h] [rbp-C0h] BYREF
  std::_List_iterator<CfgMapEvent> it; // [rsp+E0h] [rbp-A0h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+F0h] [rbp-90h] BYREF
  std::_List_iterator<Player*> v37; // [rsp+100h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<CLibraryItem*,std::vector<CLibraryItem> > v38; // [rsp+110h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+120h] [rbp-60h] BYREF
  std::string dropper; // [rsp+130h] [rbp-50h] BYREF
  char v41; // [rsp+147h] [rbp-39h] BYREF
  CfgDungeonPlant *pCfgDungeonPlant; // [rsp+148h] [rbp-38h]
  Player *player; // [rsp+150h] [rbp-30h]
  int32_t CostBind; // [rsp+158h] [rbp-28h]
  int32_t nRand; // [rsp+15Ch] [rbp-24h]
  const CfgLibraryCost *pCost; // [rsp+160h] [rbp-20h]
  int32_t i; // [rsp+16Ch] [rbp-14h]

  if ( plant )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v2 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      v3 = *std::vector<int>::operator[](&v2->trigger_param, 0);
      v4 = Answer::Singleton<CfgData>::instance();
      pCfgDungeonPlant = CfgData::getDungeonPlant(v4, v3);
      if ( pCfgDungeonPlant )
      {
        v5 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( CfgMapEvent::isOpen(v5) )
        {
          v6 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( !CfgMapEvent::isDone(v6) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 5 )
          {
            pid = pCfgDungeonPlant->pid;
            if ( pid == Plant::getPlantId(plant) )
            {
              v9 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, _QWORD))*((_QWORD *)this->_vptr_Map + 33);
              v10 = std::_List_iterator<CfgMapEvent>::operator*(&it);
              v9(this, v10, 0);
            }
          }
        }
      }
    }
    if ( this->m_cfgDungeon.type == 32 )
    {
      player = 0;
      CostBind = 0;
      for ( iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
            ;
            std::_List_iterator<Player *>::operator++(&iter) )
      {
        v37._M_node = std::list<Player *>::end(&this->m_players)._M_node;
        if ( !std::_List_iterator<Player *>::operator!=(&iter, &v37) )
          break;
        player = *std::_List_iterator<Player *>::operator*(&iter);
        if ( !player )
          return;
        id = this->m_cfgDungeon.id;
        v12 = this->m_nGatherTims + 1;
        v13 = Answer::Singleton<CfgData>::instance();
        CLibraryTable = CfgData::GetCLibraryTable(v13);
        pCost = CLibraryTable::GetCfgLibraryCost(CLibraryTable, v12, id);
        if ( !pCost )
          return;
        if ( pCost->Item.m_nId < 0 || pCost->Item.m_nCount <= 0 || pCost->Item.m_nClass <= 0 )
        {
          CostBind = 1;
        }
        else
        {
          BindCount = 0;
          UnBindCount = 0;
          p_Item = &pCost->Item;
          Bag = Player::GetBag(player);
          if ( !CExtCharBag::RemoveItem(Bag, p_Item, ITEM_CHANGE_REASON::ICR_LIBRARY_CONST, &BindCount, &UnBindCount) )
            return;
          if ( BindCount > 0 )
            CostBind = 1;
        }
      }
      std::vector<DropItem>::vector(&dropItems);
      ++this->m_nGatherTims;
      m_MaxnProbability = this->m_MaxnProbability;
      v18 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v18, 1, m_MaxnProbability);
      for ( it_0._M_current = std::vector<CLibraryItem>::begin(&this->m_LibraryRewardVector)._M_current;
            ;
            __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator++(&it_0, 0) )
      {
        v38._M_current = std::vector<CLibraryItem>::end(&this->m_LibraryRewardVector)._M_current;
        if ( !__gnu_cxx::operator!=<CLibraryItem *,std::vector<CLibraryItem>>(&it_0, &v38) )
          break;
        if ( __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0)->IsGet != 1 )
        {
          v19 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0);
          if ( v19->nProbability >= nRand )
          {
            __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0)->IsGet = 1;
            v20 = this->m_MaxnProbability;
            this->m_MaxnProbability = v20
                                    - __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0)->nProbability;
            v21 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0);
            for ( ItemIt._M_current = std::vector<MemChrBag>::begin(&v21->Items)._M_current;
                  ;
                  __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&ItemIt, 0) )
            {
              v23 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0);
              __rhs._M_current = std::vector<MemChrBag>::end(&v23->Items)._M_current;
              if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&ItemIt, &__rhs) )
                break;
              memset(&stu, 0, sizeof(stu));
              stu.itemClass = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&ItemIt)->itemClass;
              stu.itemId = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&ItemIt)->itemId;
              stu.itemCount = 1;
              stu.bindType = CostBind;
              for ( i = 0; ; ++i )
              {
                v22 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&ItemIt);
                if ( v22->itemCount <= i )
                  break;
                std::vector<DropItem>::push_back(&dropItems, &stu);
              }
            }
            break;
          }
          v24 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_0);
          nRand -= v24->nProbability;
        }
      }
      if ( player )
      {
        CDropItemGroup::CDropItemGroup(&pDropItemGroup);
        CentosPos = StaticObj::getCurrentTile(player);
        std::allocator<char>::allocator(&v41);
        std::string::string(&dropper, &unk_8D658F, &v41);
        droperMid = Plant::getPlantId(plant);
        CDropItemGroup::init(&pDropItemGroup, 0, this, &CentosPos, player, 6, droperMid, &dropItems, &dropper, 0, 0, 0);
        std::string::~string(&dropper);
        std::allocator<char>::~allocator(&v41);
        Map::addDropItemGroup(this, &pDropItemGroup);
        Dungeon::broadcastDungeonInfo(this);
        CDropItemGroup::~CDropItemGroup(&pDropItemGroup);
      }
      if ( this->m_nGatherTims == 12 )
        Dungeon::win(this, 0);
      std::vector<DropItem>::~vector(&dropItems);
    }
  }
}


#####################################
void __cdecl Dungeon::OnNpcEnd(Dungeon *const this, NpcDungeon *npc, int8_t choice)
{
  CfgMapEvent *v3; // rax
  int32_t v4; // ebx
  CfgData *v5; // rax
  CfgMapEvent *v6; // rax
  CfgMapEvent *v7; // rax
  int32_t NpcId; // ebx
  CfgMapEvent *v9; // rax
  void (__fastcall *v11)(Dungeon *const, CfgMapEvent *, _QWORD); // rbx
  CfgMapEvent *v12; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF
  CfgDungeonNpc *pCfgDungeonNpc; // [rsp+38h] [rbp-18h]

  if ( npc )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      v4 = *std::vector<int>::operator[](&v3->trigger_param, 0);
      v5 = Answer::Singleton<CfgData>::instance();
      pCfgDungeonNpc = CfgData::getDungeonNpc(v5, v4);
      if ( pCfgDungeonNpc )
      {
        v6 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( CfgMapEvent::isOpen(v6) )
        {
          v7 = std::_List_iterator<CfgMapEvent>::operator->(&it);
          if ( !CfgMapEvent::isDone(v7) && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 13 )
          {
            NpcId = pCfgDungeonNpc->NpcId;
            if ( NpcId == Npc::getNpcId(npc) )
            {
              v9 = std::_List_iterator<CfgMapEvent>::operator->(&it);
              if ( *std::vector<int>::operator[](&v9->trigger_param, 1u) == choice )
              {
                v11 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, _QWORD))*((_QWORD *)this->_vptr_Map + 33);
                v12 = std::_List_iterator<CfgMapEvent>::operator*(&it);
                v11(this, v12, 0);
              }
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl Dungeon::onMonsterArriveRoadEnd(Dungeon *const this, MonsterDungeon *monster)
{
  std::pair<const int,MonsterWave> *v2; // rax
  Player **v3; // rax
  int32_t Exp; // eax
  CfgMapEvent *v5; // rax
  CfgMapEvent *v6; // rax
  void (__fastcall *v8)(Dungeon *const, CfgMapEvent *); // rbx
  CfgMapEvent *v9; // rdx
  std::_List_iterator<CfgMapEvent> it_0; // [rsp+10h] [rbp-80h] BYREF
  std::_List_iterator<Player*> itPlayer; // [rsp+20h] [rbp-70h] BYREF
  PlayerList players; // [rsp+30h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it; // [rsp+40h] [rbp-50h] BYREF
  int __x; // [rsp+4Ch] [rbp-44h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v15; // [rsp+50h] [rbp-40h] BYREF
  std::_List_iterator<Player*> v16; // [rsp+60h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> v17; // [rsp+70h] [rbp-20h] BYREF
  int32_t LostExp; // [rsp+78h] [rbp-18h]
  int32_t Level; // [rsp+7Ch] [rbp-14h]

  if ( monster )
  {
    __x = MonsterDungeon::getWave(monster);
    it._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &__x)._M_node;
    v15._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it, &v15) )
    {
      v2 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it);
      ++v2->second.escaped;
    }
    ++this->m_finshInfo.escape_count;
    Dungeon::getPlayers((Dungeon *const)&players);
    itPlayer._M_node = std::list<Player *>::begin(&players)._M_node;
    LostExp = 0;
    v16._M_node = std::list<Player *>::end(&players)._M_node;
    if ( std::_List_iterator<Player *>::operator!=(&itPlayer, &v16) )
    {
      v3 = std::_List_iterator<Player *>::operator*(&itPlayer);
      Level = (*((__int64 (__fastcall **)(Player *))(*v3)->_vptr_Entity + 9))(*v3);
      Exp = Monster::getExp(monster);
      LostExp = (int)(float)((float)((float)((float)Level / 50.0) + 1.0)
                           * (float)((float)Exp * (float)((float)((float)Level / 50.0) + 1.0)));
    }
    this->m_finshInfo.lost_exp += LostExp;
    MonsterDungeon::remove(monster);
    for ( it_0._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it_0) )
    {
      v17._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it_0, &v17) )
        break;
      v5 = std::_List_iterator<CfgMapEvent>::operator->(&it_0);
      if ( CfgMapEvent::isOpen(v5) )
      {
        v6 = std::_List_iterator<CfgMapEvent>::operator->(&it_0);
        if ( !CfgMapEvent::isDone(v6) && std::_List_iterator<CfgMapEvent>::operator->(&it_0)->trigger_type == 2 )
        {
          v8 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *))*((_QWORD *)this->_vptr_Map + 32);
          v9 = std::_List_iterator<CfgMapEvent>::operator*(&it_0);
          v8(this, v9);
        }
      }
    }
    std::list<Player *>::~list(&players);
  }
}


#####################################
void __cdecl Dungeon::OnPickItem(Dungeon *const this, Player *player, const MemChrBag *const item)
{
  int8_t itemClass; // r12
  int32_t itemId; // ebx
  CfgData *v5; // rax
  MemChrBag *v7; // rax
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+20h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+30h] [rbp-20h] BYREF

  if ( player && this->m_cfgDungeon.type == 26 )
  {
    itemClass = item->itemClass;
    itemId = item->itemId;
    v5 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getOverlay(v5, itemId, itemClass) > 1 )
    {
      for ( iter._M_current = std::vector<MemChrBag>::begin(&this->m_vPickItems)._M_current;
            ;
            __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator++(&iter) )
      {
        __rhs._M_current = std::vector<MemChrBag>::end(&this->m_vPickItems)._M_current;
        if ( !__gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&iter, &__rhs) )
          break;
        if ( __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->itemClass == item->itemClass
          && __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter)->itemId == item->itemId )
        {
          v7 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&iter);
          v7->itemCount += item->itemCount;
          return;
        }
      }
    }
    std::vector<MemChrBag>::push_back(&this->m_vPickItems, item);
  }
}


#####################################
std::string __cdecl Dungeon::getDungeonName(const Dungeon *const this)
{
  const std::string *v1; // rsi

  std::string::string((std::string *)this, v1 + 61);
  return (std::string)this;
}


#####################################
void __cdecl Dungeon::clearMonster(Dungeon *const this)
{
  Monster *v1; // rax
  MonsterDungeon *v2; // rax
  std::_List_iterator<Monster*> it; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  MonsterDungeon *pMonster; // [rsp+28h] [rbp-8h]

  for ( it._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&it) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&it, &__x) )
      break;
    v1 = *std::_List_iterator<Monster *>::operator*(&it);
    if ( v1 )
      v2 = (MonsterDungeon *)__dynamic_cast(
                               v1,
                               (const struct __class_type_info *)&`typeinfo for'Monster,
                               (const struct __class_type_info *)&`typeinfo for'MonsterDungeon,
                               0);
    else
      v2 = 0;
    pMonster = v2;
    if ( v2 )
      MonsterDungeon::remove(pMonster);
  }
}


#####################################
void __cdecl Dungeon::sendMoYuShiJieReward(
        Dungeon *const this,
        Player *player,
        int32_t nId,
        int8_t nClass,
        int8_t nMail,
        int8_t nShow)
{
  int8_t ConnId; // bl
  GameService *v7; // rax
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v7 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v7, ConnId, Answer::PackType::PACK_DISPATCH, 0x2734u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.id);
      Answer::NetPacket::writeInt8(packet, nShow);
      Answer::NetPacket::writeInt32(packet, nId);
      Answer::NetPacket::writeInt8(packet, nClass);
      Answer::NetPacket::writeInt8(packet, nMail);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcast(this, packet);
    }
  }
}


#####################################
void __cdecl Dungeon::broadcastFinishDungon(Dungeon *const this, int32_t param)
{
  GameService *v2; // rax
  int32_t v3; // eax
  const MemChrBag *v4; // rax
  const MemChrBag *v5; // rax
  const MemChrBag *v6; // rax
  const MemChrBag *v7; // rax
  const MemChrBag *v8; // rax
  uint32_t WOffset; // eax
  __gnu_cxx::__normal_iterator<const MemChrBag*,std::vector<MemChrBag> > iter; // [rsp+10h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __i; // [rsp+20h] [rbp-20h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+30h] [rbp-10h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-8h]

  if ( this->m_cfgDungeon.type != 17 )
  {
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2734u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.id);
      switch ( this->m_cfgDungeon.type )
      {
        case 0xF:
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.get_exp);
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.lost_exp);
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.kill_count);
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.escape_count);
          break;
        case 0x13:
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.kill_count);
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.normal_wave);
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.reward_wave);
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.get_money);
          break;
        case 0x17:
          Answer::NetPacket::writeInt32(packet, this->m_finshInfo.normal_wave);
          break;
        case 0x1A:
          v3 = std::vector<MemChrBag>::size(&this->m_vPickItems);
          Answer::NetPacket::writeInt32(packet, v3);
          __i._M_current = std::vector<MemChrBag>::begin(&this->m_vPickItems)._M_current;
          __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::__normal_iterator<MemChrBag*>(
            &iter,
            &__i);
          while ( 1 )
          {
            __rhs._M_current = std::vector<MemChrBag>::end(&this->m_vPickItems)._M_current;
            if ( !__gnu_cxx::operator!=<MemChrBag const*,MemChrBag*,std::vector<MemChrBag>>(&iter, &__rhs) )
              break;
            v4 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
            Answer::NetPacket::writeInt32(packet, v4->itemId);
            v5 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
            Answer::NetPacket::writeInt8(packet, v5->itemClass);
            v6 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
            Answer::NetPacket::writeInt32(packet, v6->itemCount);
            v7 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
            Answer::NetPacket::writeInt8(packet, v7->bind);
            v8 = __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator->(&iter);
            Answer::NetPacket::writeInt64(packet, v8->srcId);
            __gnu_cxx::__normal_iterator<MemChrBag const*,std::vector<MemChrBag>>::operator++(&iter);
          }
          break;
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      Map::broadcast(this, packet);
    }
  }
}


#####################################
void __cdecl Dungeon::sendDungeonResult(Dungeon *const this, Player *player, int32_t param)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2735u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.id);
      Answer::NetPacket::writeInt32(packet, param);
      Answer::NetPacket::writeInt32(packet, 1);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v8, v7, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl Dungeon::broadcastDungeonEvent(Dungeon *const this, int32_t evtId)
{
  GameService *v2; // rax
  int32_t DungeonId; // edx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2728u);
  if ( packet )
  {
    DungeonId = Dungeon::getDungeonId(this);
    Answer::NetPacket::writeInt32(packet, DungeonId);
    Answer::NetPacket::writeInt32(packet, evtId);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Dungeon::broadcastPlayMovie(Dungeon *const this, int32_t movieID)
{
  GameService *v2; // rax
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, Answer::PackType::PACK_DISPATCH, 0x2729u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, movieID);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Dungeon::broadcastDungeonInfo(Dungeon *const this)
{
  GameService *v1; // rax
  int32_t LeftTime; // eax
  int32_t v3; // eax
  std::pair<const int,int> *v4; // rax
  std::pair<const int,int> *v5; // rax
  int8_t v6; // al
  DungeonTower *v7; // rax
  DungeonTower *v8; // rax
  int32_t free; // ebx
  DungeonTower *v10; // rax
  int32_t limit; // ebx
  DungeonTower *v12; // rax
  DungeonTower *v13; // rax
  DungeonTower *v14; // rax
  int32_t v15; // eax
  std::pair<const int,MonsterWave> *v16; // rax
  std::pair<const int,MonsterWave> *v17; // rax
  int32_t v18; // eax
  int8_t Hard; // al
  std::pair<const int,MonsterWave> *v20; // rax
  std::pair<const int,MonsterWave> *v21; // rax
  int32_t v22; // eax
  int32_t v23; // eax
  CLibraryItem *v24; // rax
  CLibraryItem *v25; // rax
  CLibraryItem *v26; // rax
  uint32_t WOffset; // eax
  __int64 item; // [rsp+10h] [rbp-F0h]
  int32_t item_8; // [rsp+18h] [rbp-E8h]
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > ItemIt; // [rsp+30h] [rbp-D0h] BYREF
  __gnu_cxx::__normal_iterator<CLibraryItem*,std::vector<CLibraryItem> > it_2; // [rsp+40h] [rbp-C0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it_1; // [rsp+50h] [rbp-B0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > it_0; // [rsp+60h] [rbp-A0h] BYREF
  std::_List_iterator<DungeonTower> eiter; // [rsp+70h] [rbp-90h] BYREF
  std::_List_iterator<DungeonTower> iter; // [rsp+80h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > it; // [rsp+90h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > __x; // [rsp+A0h] [rbp-60h] BYREF
  int v38; // [rsp+ACh] [rbp-54h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v39; // [rsp+B0h] [rbp-50h] BYREF
  int v40; // [rsp+BCh] [rbp-44h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,MonsterWave> > v41; // [rsp+C0h] [rbp-40h] BYREF
  __gnu_cxx::__normal_iterator<CLibraryItem*,std::vector<CLibraryItem> > v42; // [rsp+D0h] [rbp-30h] BYREF
  __gnu_cxx::__normal_iterator<MemChrBag*,std::vector<MemChrBag> > __rhs; // [rsp+E0h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+E8h] [rbp-18h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2DF0u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.id);
    LeftTime = Dungeon::GetLeftTime(this);
    Answer::NetPacket::writeInt32(packet, LeftTime);
    v3 = std::map<int,int>::size(&this->m_mSummonRecord);
    Answer::NetPacket::writeInt32(packet, v3);
    for ( it._M_node = std::map<int,int>::begin(&this->m_mSummonRecord)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,int>::end(&this->m_mSummonRecord)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&it, &__x) )
        break;
      v4 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v4->first);
      v5 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&it);
      Answer::NetPacket::writeInt32(packet, v5->second);
    }
    switch ( this->m_cfgDungeon.type )
    {
      case 0xF:
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.kill_count);
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.get_exp);
        v6 = std::list<DungeonTower>::size(&this->m_waitTower);
        Answer::NetPacket::writeInt8(packet, v6);
        iter._M_node = std::list<DungeonTower>::begin(&this->m_waitTower)._M_node;
        eiter._M_node = std::list<DungeonTower>::end(&this->m_waitTower)._M_node;
        while ( std::_List_iterator<DungeonTower>::operator!=(&iter, &eiter) )
        {
          v7 = std::_List_iterator<DungeonTower>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v7->id);
          v8 = std::_List_iterator<DungeonTower>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v8->mid);
          free = std::_List_iterator<DungeonTower>::operator->(&iter)->free;
          v10 = std::_List_iterator<DungeonTower>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, free - v10->count);
          limit = std::_List_iterator<DungeonTower>::operator->(&iter)->limit;
          v12 = std::_List_iterator<DungeonTower>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, limit - v12->free);
          v13 = std::_List_iterator<DungeonTower>::operator->(&iter);
          Answer::NetPacket::writeInt8(packet, v13->costType);
          v14 = std::_List_iterator<DungeonTower>::operator->(&iter);
          Answer::NetPacket::writeInt32(packet, v14->costValue);
          std::_List_iterator<DungeonTower>::operator++(&iter);
        }
        break;
      case 0x13:
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.kill_count);
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.get_money);
        v15 = Dungeon::GetLeftTime(this);
        Answer::NetPacket::writeInt32(packet, v15);
        break;
      case 0x17:
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.normal_wave);
        v38 = this->m_finshInfo.normal_wave + 1;
        it_0._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &v38)._M_node;
        v39._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it_0, &v39) )
        {
          v16 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_0);
          Answer::NetPacket::writeInt32(packet, v16->second.killed);
          v17 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_0);
          Answer::NetPacket::writeInt32(packet, v17->second.count);
        }
        else
        {
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
        }
        v18 = Dungeon::GetLeftTime(this);
        Answer::NetPacket::writeInt32(packet, v18);
        break;
      case 0x19:
        Hard = Dungeon::GetHard(this);
        Answer::NetPacket::writeInt32(packet, Hard);
        v40 = this->m_finshInfo.normal_wave + 1;
        it_1._M_node = std::map<int,MonsterWave>::find(&this->m_monsterWave, &v40)._M_node;
        v41._M_node = std::map<int,MonsterWave>::end(&this->m_monsterWave)._M_node;
        if ( std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator!=(&it_1, &v41) )
        {
          v20 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_1);
          Answer::NetPacket::writeInt32(packet, v20->second.count);
          v21 = std::_Rb_tree_iterator<std::pair<int const,MonsterWave>>::operator->(&it_1);
          Answer::NetPacket::writeInt32(packet, v21->second.killed);
        }
        else
        {
          Answer::NetPacket::writeInt32(packet, 0);
          Answer::NetPacket::writeInt32(packet, 0);
        }
        v22 = Dungeon::GetLeftTime(this);
        Answer::NetPacket::writeInt32(packet, v22);
        break;
      case 0x20:
        Answer::NetPacket::writeInt32(packet, this->m_nGatherTims);
        v23 = std::vector<CLibraryItem>::size(&this->m_LibraryRewardVector);
        Answer::NetPacket::writeInt32(packet, v23);
        for ( it_2._M_current = std::vector<CLibraryItem>::begin(&this->m_LibraryRewardVector)._M_current;
              ;
              __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator++(&it_2, 0) )
        {
          v42._M_current = std::vector<CLibraryItem>::end(&this->m_LibraryRewardVector)._M_current;
          if ( !__gnu_cxx::operator!=<CLibraryItem *,std::vector<CLibraryItem>>(&it_2, &v42) )
            break;
          v24 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_2);
          Answer::NetPacket::writeInt8(packet, v24->IsGet);
          item = 0;
          item_8 = 0;
          v25 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_2);
          ItemIt._M_current = std::vector<MemChrBag>::begin(&v25->Items)._M_current;
          v26 = __gnu_cxx::__normal_iterator<CLibraryItem *,std::vector<CLibraryItem>>::operator->(&it_2);
          __rhs._M_current = std::vector<MemChrBag>::end(&v26->Items)._M_current;
          if ( __gnu_cxx::operator!=<MemChrBag *,std::vector<MemChrBag>>(&ItemIt, &__rhs) )
          {
            BYTE4(item) = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&ItemIt)->itemClass;
            LODWORD(item) = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&ItemIt)->itemId;
            item_8 = __gnu_cxx::__normal_iterator<MemChrBag *,std::vector<MemChrBag>>::operator->(&ItemIt)->itemCount;
          }
          Answer::NetPacket::writeInt32(packet, item);
          Answer::NetPacket::writeInt8(packet, SBYTE4(item));
          Answer::NetPacket::writeInt32(packet, item_8);
        }
        break;
      case 0x22:
        Answer::NetPacket::writeInt32(packet, this->m_Times);
        Answer::NetPacket::writeInt8(packet, this->m_bGetReward);
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.kill_count);
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.boss_count);
        Answer::NetPacket::writeInt32(packet, this->m_MoneyBuffLevel);
        Answer::NetPacket::writeInt32(packet, this->m_GoldBuffLevel);
        break;
      case 0x23:
        Answer::NetPacket::writeInt32(packet, this->m_RandomTimes);
        Answer::NetPacket::writeInt32(packet, this->m_BuyRandomTimes);
        break;
      default:
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.kill_count);
        Answer::NetPacket::writeInt32(packet, this->m_finshInfo.boss_count);
        break;
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Dungeon::broadcastDamageList(Dungeon *const this)
{
  GameService *v1; // rax
  int8_t v2; // al
  DamageSum *v3; // rax
  DamageSum *v4; // rax
  uint32_t WOffset; // eax
  std::_List_iterator<DamageSum> eiter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<DamageSum> iter; // [rsp+20h] [rbp-10h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2DFEu);
  if ( packet )
  {
    v2 = std::list<DamageSum>::size(&this->m_damages);
    Answer::NetPacket::writeInt8(packet, v2);
    iter._M_node = std::list<DamageSum>::begin(&this->m_damages)._M_node;
    eiter._M_node = std::list<DamageSum>::end(&this->m_damages)._M_node;
    while ( std::_List_iterator<DamageSum>::operator!=(&iter, &eiter) )
    {
      v3 = std::_List_iterator<DamageSum>::operator->(&iter);
      Answer::NetPacket::writeUTF8(packet, &v3->name);
      v4 = std::_List_iterator<DamageSum>::operator->(&iter);
      Answer::NetPacket::writeInt32(packet, v4->damage);
      std::_List_iterator<DamageSum>::operator++(&iter);
    }
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
    this->m_needBroadcastDamage = 0;
  }
}


#####################################
void __cdecl Dungeon::broadcastSummonBoss(Dungeon *const this, const std::string *const name, int8_t nState)
{
  GameService *v3; // rax
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2DF4u);
  if ( packet )
  {
    Answer::NetPacket::writeUTF8(packet, name);
    Answer::NetPacket::writeInt8(packet, nState);
    LeftTime = Dungeon::GetLeftTime(this);
    Answer::NetPacket::writeInt32(packet, LeftTime);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Dungeon::checkBroadcastDamageList(Dungeon *const this)
{
  if ( this->m_needBroadcastDamage )
    Dungeon::broadcastDamageList(this);
}


#####################################
bool __cdecl Dungeon::BuyTower(Dungeon *const this, Player *player, int32_t nId)
{
  int32_t free; // ebx
  int64_t costValue; // r12
  CURRENCY_TYPE costType; // ebx
  DungeonTower *v7; // rax
  std::_List_iterator<DungeonTower> eiter; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<DungeonTower> iter; // [rsp+30h] [rbp-20h] BYREF

  if ( !player )
    return 0;
  iter._M_node = std::list<DungeonTower>::begin(&this->m_waitTower)._M_node;
  eiter._M_node = std::list<DungeonTower>::end(&this->m_waitTower)._M_node;
  while ( std::_List_iterator<DungeonTower>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_iterator<DungeonTower>::operator->(&iter)->id == nId )
    {
      free = std::_List_iterator<DungeonTower>::operator->(&iter)->free;
      if ( free < std::_List_iterator<DungeonTower>::operator->(&iter)->limit )
      {
        if ( std::_List_iterator<DungeonTower>::operator->(&iter)->costValue > 0 )
        {
          costValue = std::_List_iterator<DungeonTower>::operator->(&iter)->costValue;
          costType = std::_List_iterator<DungeonTower>::operator->(&iter)->costType;
          if ( !Player::DecCurrency(player, costType, costValue, CURRENCY_CHANGE_REASON::GCR_DUNGEON_BUILD_TOWER, 0) )
            return 0;
        }
        v7 = std::_List_iterator<DungeonTower>::operator->(&iter);
        ++v7->free;
        break;
      }
    }
    std::_List_iterator<DungeonTower>::operator++(&iter);
  }
  if ( std::_List_iterator<DungeonTower>::operator==(&iter, &eiter) )
    return 0;
  Dungeon::broadcastDungeonInfo(this);
  return 1;
}


#####################################
bool __cdecl Dungeon::BuildTowerByMonstDie(
        Dungeon *const this,
        Player *player,
        int32_t nId,
        int16_t nPosX,
        int16_t nPosY)
{
  CfgData *v6; // rax
  CfgData *v7; // rax
  CPoolManager *v8; // rax
  FamilyId_t FamilyId; // rax
  CfgMapMonster cfgmapmonster; // [rsp+20h] [rbp-90h] BYREF
  std::_List_iterator<DungeonTower> eiter; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<DungeonTower> iter; // [rsp+50h] [rbp-60h] BYREF
  std::string p_strFamilyName; // [rsp+60h] [rbp-50h] BYREF
  char v17; // [rsp+77h] [rbp-39h] BYREF
  Monster *__x; // [rsp+78h] [rbp-38h] BYREF
  CfgDungeonMonster *pCfgDungeonMonster; // [rsp+80h] [rbp-30h]
  int32_t nMid; // [rsp+8Ch] [rbp-24h]
  CfgMonster *pCfgMonster; // [rsp+90h] [rbp-20h]
  MonsterDungeon *pMonster; // [rsp+98h] [rbp-18h]

  if ( !player )
    return 0;
  if ( !Map::isWalkablePosition(this, nPosX, nPosY) )
    return 0;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgDungeonMonster = CfgData::getDungeonMonster(v6, nId);
  if ( !pCfgDungeonMonster )
    return 0;
  nMid = CfgDungeonMonster::GetMid(pCfgDungeonMonster);
  v7 = Answer::Singleton<CfgData>::instance();
  pCfgMonster = CfgData::getMonster(v7, nMid);
  if ( !pCfgMonster )
    return 0;
  iter._M_node = std::list<DungeonTower>::begin(&this->m_waitTower)._M_node;
  eiter._M_node = std::list<DungeonTower>::end(&this->m_waitTower)._M_node;
  while ( std::_List_iterator<DungeonTower>::operator!=(&iter, &eiter)
       && std::_List_iterator<DungeonTower>::operator->(&iter)->id != nId )
    std::_List_iterator<DungeonTower>::operator++(&iter);
  if ( std::_List_iterator<DungeonTower>::operator==(&iter, &eiter) )
    return 0;
  v8 = Answer::Singleton<CPoolManager>::instance();
  pMonster = CPoolManager::pop<MonsterDungeon>(v8);
  if ( !pMonster )
    return 0;
  cfgmapmonster.id = 0;
  *(_DWORD *)&cfgmapmonster.hide = 0;
  cfgmapmonster.Day = 0;
  cfgmapmonster.mapid = Dungeon::GetId(this);
  cfgmapmonster.monsterid = nMid;
  cfgmapmonster.x = nPosX;
  cfgmapmonster.y = nPosY;
  cfgmapmonster.side = pCfgDungeonMonster->side;
  MonsterDungeon::init(pMonster, this, pCfgDungeonMonster, pCfgMonster, &cfgmapmonster);
  if ( nId == 12001 )
  {
    std::allocator<char>::allocator(&v17);
    std::string::string(&p_strFamilyName, &unk_8D658F, &v17);
    FamilyId = Player::getFamilyId(player);
    Monster::SetFamilyId(pMonster, FamilyId, &p_strFamilyName);
    std::string::~string(&p_strFamilyName);
    std::allocator<char>::~allocator(&v17);
  }
  (*((void (__fastcall **)(Dungeon *const, MonsterDungeon *, _QWORD, _QWORD))this->_vptr_Map + 28))(
    this,
    pMonster,
    (unsigned int)cfgmapmonster.x,
    (unsigned int)cfgmapmonster.y);
  __x = pMonster;
  std::list<Monster *>::push_back(&this->m_buildTower, &__x);
  Dungeon::broadcastDungeonInfo(this);
  return 1;
}


#####################################
bool __cdecl Dungeon::BuildTower(Dungeon *const this, Player *player, int32_t nId, int16_t nPosX, int16_t nPosY)
{
  CfgData *v6; // rax
  CfgData *v7; // rax
  int32_t count; // ebx
  DungeonTower *v9; // rax
  CPoolManager *v10; // rax
  FamilyId_t FamilyId; // rax
  CfgMapMonster cfgmapmonster; // [rsp+20h] [rbp-90h] BYREF
  std::_List_iterator<DungeonTower> eiter; // [rsp+40h] [rbp-70h] BYREF
  std::_List_iterator<DungeonTower> iter; // [rsp+50h] [rbp-60h] BYREF
  std::string p_strFamilyName; // [rsp+60h] [rbp-50h] BYREF
  char v19; // [rsp+77h] [rbp-39h] BYREF
  Monster *__x; // [rsp+78h] [rbp-38h] BYREF
  CfgDungeonMonster *pCfgDungeonMonster; // [rsp+80h] [rbp-30h]
  int32_t nMid; // [rsp+8Ch] [rbp-24h]
  CfgMonster *pCfgMonster; // [rsp+90h] [rbp-20h]
  MonsterDungeon *pMonster; // [rsp+98h] [rbp-18h]

  if ( !player )
    return 0;
  if ( !Map::isWalkablePosition(this, nPosX, nPosY) )
    return 0;
  v6 = Answer::Singleton<CfgData>::instance();
  pCfgDungeonMonster = CfgData::getDungeonMonster(v6, nId);
  if ( !pCfgDungeonMonster )
    return 0;
  nMid = CfgDungeonMonster::GetMid(pCfgDungeonMonster);
  v7 = Answer::Singleton<CfgData>::instance();
  pCfgMonster = CfgData::getMonster(v7, nMid);
  if ( !pCfgMonster )
    return 0;
  iter._M_node = std::list<DungeonTower>::begin(&this->m_waitTower)._M_node;
  eiter._M_node = std::list<DungeonTower>::end(&this->m_waitTower)._M_node;
  while ( std::_List_iterator<DungeonTower>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_iterator<DungeonTower>::operator->(&iter)->id == nId )
    {
      count = std::_List_iterator<DungeonTower>::operator->(&iter)->count;
      if ( count < std::_List_iterator<DungeonTower>::operator->(&iter)->free )
      {
        v9 = std::_List_iterator<DungeonTower>::operator->(&iter);
        ++v9->count;
        break;
      }
    }
    std::_List_iterator<DungeonTower>::operator++(&iter);
  }
  if ( std::_List_iterator<DungeonTower>::operator==(&iter, &eiter) )
    return 0;
  v10 = Answer::Singleton<CPoolManager>::instance();
  pMonster = CPoolManager::pop<MonsterDungeon>(v10);
  if ( !pMonster )
    return 0;
  cfgmapmonster.id = 0;
  *(_DWORD *)&cfgmapmonster.hide = 0;
  cfgmapmonster.Day = 0;
  cfgmapmonster.mapid = Dungeon::GetId(this);
  cfgmapmonster.monsterid = nMid;
  cfgmapmonster.x = nPosX;
  cfgmapmonster.y = nPosY;
  cfgmapmonster.side = pCfgDungeonMonster->side;
  MonsterDungeon::init(pMonster, this, pCfgDungeonMonster, pCfgMonster, &cfgmapmonster);
  if ( nId == 12001 )
  {
    std::allocator<char>::allocator(&v19);
    std::string::string(&p_strFamilyName, &unk_8D658F, &v19);
    FamilyId = Player::getFamilyId(player);
    Monster::SetFamilyId(pMonster, FamilyId, &p_strFamilyName);
    std::string::~string(&p_strFamilyName);
    std::allocator<char>::~allocator(&v19);
  }
  (*((void (__fastcall **)(Dungeon *const, MonsterDungeon *, _QWORD, _QWORD))this->_vptr_Map + 28))(
    this,
    pMonster,
    (unsigned int)cfgmapmonster.x,
    (unsigned int)cfgmapmonster.y);
  __x = pMonster;
  std::list<Monster *>::push_back(&this->m_buildTower, &__x);
  Dungeon::broadcastDungeonInfo(this);
  return 1;
}


#####################################
bool __cdecl Dungeon::SummonBoss(Dungeon *const this, Player *player, int8_t nState)
{
  CharId_t cid; // rbx
  int32_t summon_boss; // ebx
  CfgData *v6; // rax
  int32_t PosY; // r12d
  int32_t PosX; // edx
  std::_List_iterator<SummBossInfo> iter; // [rsp+20h] [rbp-50h] BYREF
  SummBossInfo info; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<SummBossInfo> __x; // [rsp+40h] [rbp-30h] BYREF
  std::string name; // [rsp+50h] [rbp-20h] BYREF
  CfgDungeonMonster *pCfgDungeonMonster; // [rsp+58h] [rbp-18h]

  if ( !player )
    return 0;
  if ( this->m_state != DungeonState::DS_SUMMON && this->m_state != DungeonState::DS_BOSS )
    return 0;
  for ( iter._M_node = std::list<SummBossInfo>::begin(&this->m_lSummonBoss)._M_node;
        ;
        std::_List_iterator<SummBossInfo>::operator++(&iter) )
  {
    __x._M_node = std::list<SummBossInfo>::end(&this->m_lSummonBoss)._M_node;
    if ( !std::_List_iterator<SummBossInfo>::operator!=(&iter, &__x) )
      break;
    cid = std::_List_iterator<SummBossInfo>::operator->(&iter)->cid;
    if ( cid == Player::getCid(player) )
      return 0;
  }
  if ( nState )
  {
    summon_boss = this->m_cfgDungeon.summon_boss;
    v6 = Answer::Singleton<CfgData>::instance();
    pCfgDungeonMonster = CfgData::getDungeonMonster(v6, summon_boss);
    if ( !pCfgDungeonMonster )
      return 0;
    if ( !Player::DecCurrency(
            player,
            CURRENCY_TYPE::CURRENCY_GOLD,
            this->m_cfgDungeon.summon_cost,
            CURRENCY_CHANGE_REASON::GCR_DUNGEON_SUMMON_BOSS,
            0) )
      return 0;
    PosY = StaticObj::GetPosY(player);
    PosX = StaticObj::GetPosX(player);
    Dungeon::flashMonster(this, pCfgDungeonMonster, PosX, PosY, 0, 0);
    if ( this->m_state != DungeonState::DS_BOSS )
      Dungeon::setState(this, DungeonState::DS_BOSS, 1800);
  }
  info.cid = 0;
  *(_QWORD *)&info.state = 0;
  info.cid = Player::getCid(player);
  info.state = nState;
  std::list<SummBossInfo>::push_back(&this->m_lSummonBoss, &info);
  Player::getName((const Player *const)&name);
  Dungeon::broadcastSummonBoss(this, &name, nState);
  std::string::~string(&name);
  if ( Dungeon::isAllPlayerSummon(this) && Dungeon::isAllMonsterDie(this) )
    Dungeon::win(this, 0);
  return 1;
}


#####################################
bool __cdecl Dungeon::Summon(Dungeon *const this, Player *player, int32_t nIndex)
{
  int32_t id; // ebx
  CfgData *v5; // rax
  int64_t nGold; // rbx
  CExtCurrency *Currency; // rax
  ItemData *p_ConstItem; // rbx
  CExtCharBag *Bag; // rax
  int *v12; // rax
  int v13; // ebx
  CfgData *v14; // rax
  int32_t PosY; // r12d
  int32_t PosX; // eax
  int32_t nIndexa; // [rsp+Ch] [rbp-54h] BYREF
  Player *playera; // [rsp+10h] [rbp-50h]
  Dungeon *thisa; // [rsp+18h] [rbp-48h]
  std::_List_const_iterator<int> iter; // [rsp+20h] [rbp-40h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+30h] [rbp-30h] BYREF
  const CfgDungeonSummon *pCfgSummon; // [rsp+38h] [rbp-28h]
  int32_t nRecord; // [rsp+44h] [rbp-1Ch]
  CfgDungeonMonster *pCfgDungeonMonster; // [rsp+48h] [rbp-18h]

  thisa = this;
  playera = player;
  nIndexa = nIndex;
  if ( !player )
    return 0;
  if ( thisa->m_state != DungeonState::DS_RUNNING )
    return 0;
  id = thisa->m_cfgDungeon.id;
  v5 = Answer::Singleton<CfgData>::instance();
  pCfgSummon = CfgData::GetDungeonSummon(v5, id, nIndexa);
  if ( !pCfgSummon )
    return 0;
  nRecord = *std::map<int,int>::operator[](&thisa->m_mSummonRecord, &nIndexa);
  if ( pCfgSummon->nLimit <= nRecord )
    return 0;
  if ( pCfgSummon->FreeCount > nRecord )
    goto LABEL_22;
  if ( pCfgSummon->nGold > 0 )
  {
    nGold = pCfgSummon->nGold;
    Currency = Player::GetCurrency(playera);
    if ( !CExtCurrency::DecCurrency(
            Currency,
            CURRENCY_TYPE::CURRENCY_GOLD,
            nGold,
            CURRENCY_CHANGE_REASON::GCR_DUNGEON_SUMMON,
            0) )
      return 0;
  }
  if ( pCfgSummon->ConstItem.m_nCount > 0 )
  {
    p_ConstItem = &pCfgSummon->ConstItem;
    Bag = Player::GetBag(playera);
    if ( !CExtCharBag::RemoveItem(Bag, p_ConstItem, ITEM_CHANGE_REASON::ICR_SUMMON_MONSTER) )
      return 0;
  }
LABEL_22:
  v12 = std::map<int,int>::operator[](&thisa->m_mSummonRecord, &nIndexa);
  *v12 = nRecord + 1;
  for ( iter._M_node = std::list<int>::begin(&pCfgSummon->lMonsters)._M_node;
        ;
        std::_List_const_iterator<int>::operator++(&iter) )
  {
    __x._M_node = std::list<int>::end(&pCfgSummon->lMonsters)._M_node;
    if ( !std::_List_const_iterator<int>::operator!=(&iter, &__x) )
      break;
    v13 = *std::_List_const_iterator<int>::operator*(&iter);
    v14 = Answer::Singleton<CfgData>::instance();
    pCfgDungeonMonster = CfgData::getDungeonMonster(v14, v13);
    if ( pCfgDungeonMonster )
    {
      PosY = StaticObj::GetPosY(playera);
      PosX = StaticObj::GetPosX(playera);
      Dungeon::flashMonster(thisa, pCfgDungeonMonster, PosX, PosY, 0, 0);
    }
  }
  Dungeon::broadcastDungeonInfo(thisa);
  return 1;
}


#####################################
void __cdecl Dungeon::addWaitTower(Dungeon *const this, const DungeonTower *const tower)
{
  int32_t costValue; // ebx
  DungeonTower *v4; // rax
  DungeonTower *v5; // rax
  std::_List_iterator<DungeonTower> eiter; // [rsp+10h] [rbp-30h] BYREF
  std::_List_iterator<DungeonTower> iter; // [rsp+20h] [rbp-20h] BYREF

  iter._M_node = std::list<DungeonTower>::begin(&this->m_waitTower)._M_node;
  eiter._M_node = std::list<DungeonTower>::end(&this->m_waitTower)._M_node;
  while ( std::_List_iterator<DungeonTower>::operator!=(&iter, &eiter) )
  {
    if ( std::_List_iterator<DungeonTower>::operator->(&iter)->id == tower->id
      && std::_List_iterator<DungeonTower>::operator->(&iter)->costType == tower->costType )
    {
      costValue = std::_List_iterator<DungeonTower>::operator->(&iter)->costValue;
      if ( costValue == std::_List_iterator<DungeonTower>::operator->(&iter)->costValue )
      {
        v4 = std::_List_iterator<DungeonTower>::operator->(&iter);
        v4->free += tower->free;
        v5 = std::_List_iterator<DungeonTower>::operator->(&iter);
        v5->limit += tower->limit;
        return;
      }
    }
    std::_List_iterator<DungeonTower>::operator++(&iter);
  }
  std::list<DungeonTower>::push_back(&this->m_waitTower, tower);
  Dungeon::broadcastDungeonInfo(this);
}


#####################################
bool __cdecl Dungeon::GetReward(Dungeon *const this, Player *player, int8_t nRatio, bool IsSysTem)
{
  int32_t Record; // ebx
  int m_nWinStar; // ebx
  size_t v7; // rax
  int v8; // ebx
  size_t v9; // rax
  CharId_t cid; // rbx
  int64_t DungeonId; // rcx
  int64_t id; // rbx
  DungeonReward *v13; // rax
  int64_t v14; // rbx
  DungeonReward *v15; // rax
  DungeonReward *v16; // rax
  DungeonReward *v17; // rax
  MemChrBag *p_Item; // rbx
  CExtCharBag *Bag; // rax
  MemChrBag *v20; // r13
  CharId_t v21; // r12
  int8_t ConnId; // bl
  DBService *v23; // rax
  CExtCharBag *v24; // rax
  CharId_t v25; // r12
  int8_t v26; // bl
  DBService *v27; // rax
  int32_t v28; // edx
  CExtCharBag *v30; // rax
  CharId_t v31; // r12
  int8_t v32; // bl
  DBService *v33; // rax
  CExtCharBag *v34; // rax
  CharId_t v35; // r12
  int8_t v36; // bl
  DBService *v37; // rax
  int32_t v38; // edx
  int32_t group_id; // ebx
  CHuoYueDu *PlayerHuoYueDu; // rax
  int32_t v41; // edx
  MemChrBag starReward; // [rsp+30h] [rbp-C0h] BYREF
  std::_List_iterator<DungeonReward> eiter; // [rsp+50h] [rbp-A0h] BYREF
  std::_List_iterator<DungeonReward> iter; // [rsp+60h] [rbp-90h] BYREF
  std::string Param; // [rsp+70h] [rbp-80h] BYREF
  char v48; // [rsp+7Fh] [rbp-71h] BYREF
  std::string v49; // [rsp+80h] [rbp-70h] BYREF
  char v50; // [rsp+8Fh] [rbp-61h] BYREF
  std::string v51; // [rsp+90h] [rbp-60h] BYREF
  char v52; // [rsp+9Fh] [rbp-51h] BYREF
  std::string v53; // [rsp+A0h] [rbp-50h] BYREF
  char v54; // [rsp+B3h] [rbp-3Dh] BYREF
  BenefitType bnfType; // [rsp+B4h] [rbp-3Ch]
  double bnfRatio; // [rsp+B8h] [rbp-38h]
  double hardRatio; // [rsp+C0h] [rbp-30h]
  double starRatio; // [rsp+C8h] [rbp-28h]

  if ( !player )
    return 0;
  Record = Player::getRecord(player, this->m_cfgDungeon.group_id);
  if ( Record > Player::GetDungeonDailyEnterLimit(player, this->m_cfgDungeon.id) )
    return 0;
  bnfType = Player::benefitType(player);
  bnfRatio = Player::benefitRatio(player);
  hardRatio = 1.0;
  starRatio = 1.0;
  memset(&starReward, 0, sizeof(starReward));
  if ( this->m_nWinStar > 0 )
  {
    m_nWinStar = this->m_nWinStar;
    if ( m_nWinStar <= (int)std::vector<int>::size(&this->m_cfgDungeon.star_ratio) )
    {
      v7 = std::vector<int>::size(&this->m_cfgDungeon.star_ratio);
      starRatio = (double)*std::vector<int>::operator[](&this->m_cfgDungeon.star_ratio, v7 - this->m_nWinStar) / 100.0
                + starRatio;
    }
    v8 = this->m_nWinStar;
    if ( v8 <= (int)std::vector<MemChrBag>::size(&this->m_cfgDungeon.star_reward) )
    {
      v9 = std::vector<MemChrBag>::size(&this->m_cfgDungeon.star_reward);
      starReward = *std::vector<MemChrBag>::operator[](&this->m_cfgDungeon.star_reward, v9 - this->m_nWinStar);
    }
  }
  iter._M_node = std::list<DungeonReward>::begin(&this->m_playerReward)._M_node;
  eiter._M_node = std::list<DungeonReward>::end(&this->m_playerReward)._M_node;
  while ( 1 )
  {
    if ( !std::_List_iterator<DungeonReward>::operator!=(&iter, &eiter) )
      return 0;
    cid = std::_List_iterator<DungeonReward>::operator->(&iter)->cid;
    if ( cid == Player::getCid(player) )
      break;
    std::_List_iterator<DungeonReward>::operator++(&iter);
  }
  if ( std::_List_iterator<DungeonReward>::operator->(&iter)->bGet > 0 )
    return 0;
  if ( nRatio == 2 )
  {
    if ( std::_List_iterator<DungeonReward>::operator->(&iter)->Item.itemCount <= 0 )
      return 0;
    if ( this->m_cfgDungeon.double_cost < 0 )
      return 0;
    if ( this->m_cfgDungeon.double_cost > 0 )
    {
      DungeonId = Dungeon::getDungeonId(this);
      if ( !Player::DecCurrency(
              player,
              CURRENCY_TYPE::CURRENCY_GOLD,
              this->m_cfgDungeon.double_cost,
              CURRENCY_CHANGE_REASON::GCR_DUNGEON_DOUBLE_REWARD,
              DungeonId) )
      {
        if ( !IsSysTem )
          return 0;
        nRatio = 1;
      }
    }
  }
  if ( nRatio != 1 && nRatio != 2 )
    return 0;
  if ( std::_List_iterator<DungeonReward>::operator->(&iter)->money > 0 )
  {
    id = this->m_cfgDungeon.id;
    v13 = std::_List_iterator<DungeonReward>::operator->(&iter);
    Player::AddCurrency(
      player,
      CURRENCY_TYPE::CURRENCY_MONEY,
      (int)((double)v13->money * this->m_dRatio * starRatio * hardRatio) * nRatio,
      CURRENCY_CHANGE_REASON::MCR_DUNGEON_REWARD,
      id);
  }
  if ( std::_List_iterator<DungeonReward>::operator->(&iter)->cash > 0 )
  {
    v14 = this->m_cfgDungeon.id;
    v15 = std::_List_iterator<DungeonReward>::operator->(&iter);
    Player::AddCurrency(
      player,
      CURRENCY_TYPE::CURRENCY_CASH,
      (int)((double)v15->cash * bnfRatio * this->m_dRatio * starRatio * hardRatio) * nRatio,
      CURRENCY_CHANGE_REASON::GCR_DUNGEON_REWARD,
      v14);
  }
  if ( std::_List_iterator<DungeonReward>::operator->(&iter)->exp > 0 )
  {
    v16 = std::_List_iterator<DungeonReward>::operator->(&iter);
    Player::addExp(player, (int)((double)v16->exp * this->m_dRatio * starRatio * hardRatio) * nRatio, 0, 1);
  }
  if ( std::_List_iterator<DungeonReward>::operator->(&iter)->Item.itemCount > 0 )
  {
    v17 = std::_List_iterator<DungeonReward>::operator->(&iter);
    v17->Item.itemCount *= nRatio;
    p_Item = &std::_List_iterator<DungeonReward>::operator->(&iter)->Item;
    Bag = Player::GetBag(player);
    if ( !CExtCharBag::AddItem(Bag, p_Item, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD) )
    {
      std::allocator<char>::allocator(&v48);
      std::string::string(&Param, &unk_8D658F, &v48);
      v20 = &std::_List_iterator<DungeonReward>::operator->(&iter)->Item;
      v21 = Player::getCid(player);
      ConnId = Player::getConnId(player);
      v23 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v23, ConnId, v21, 1, v20, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD, &Param, 0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v48);
    }
  }
  if ( starReward.itemId > 0 && starReward.itemCount > 0 )
  {
    v24 = Player::GetBag(player);
    if ( !CExtCharBag::AddItem(v24, &starReward, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD) )
    {
      std::allocator<char>::allocator(&v50);
      std::string::string(&v49, &unk_8D658F, &v50);
      v25 = Player::getCid(player);
      v26 = Player::getConnId(player);
      v27 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v27, v26, v25, 1, &starReward, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD, &v49, 0);
      std::string::~string(&v49);
      std::allocator<char>::~allocator(&v50);
    }
  }
  v28 = Dungeon::getDungeonId(this) + 20000;
  if ( Player::getRecord(player, v28) == 1 && !std::vector<MemChrBag>::empty(&this->m_cfgDungeon.rewardOnce) )
  {
    v30 = Player::GetBag(player);
    if ( !CExtCharBag::AddItem(v30, &this->m_cfgDungeon.rewardOnce, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD) )
    {
      std::allocator<char>::allocator(&v52);
      std::string::string(&v51, &unk_8D658F, &v52);
      v31 = Player::getCid(player);
      v32 = Player::getConnId(player);
      v33 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(
        v33,
        v32,
        v31,
        1,
        &this->m_cfgDungeon.rewardOnce,
        ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD,
        &v51,
        0);
      std::string::~string(&v51);
      std::allocator<char>::~allocator(&v52);
    }
  }
  else if ( !std::vector<MemChrBag>::empty(&this->m_cfgDungeon.rewardItem) )
  {
    v34 = Player::GetBag(player);
    if ( CExtCharBag::AddItem(v34, &this->m_cfgDungeon.rewardItem, ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD) )
    {
      std::allocator<char>::allocator(&v54);
      std::string::string(&v53, &unk_8D658F, &v54);
      v35 = Player::getCid(player);
      v36 = Player::getConnId(player);
      v37 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(
        v37,
        v36,
        v35,
        1,
        &this->m_cfgDungeon.rewardItem,
        ITEM_CHANGE_REASON::ICR_DUNGEON_REWARD,
        &v53,
        0);
      std::string::~string(&v53);
      std::allocator<char>::~allocator(&v54);
    }
  }
  std::_List_iterator<DungeonReward>::operator->(&iter)->bGet = nRatio;
  if ( this->m_cfgDungeon.type == 13 || this->m_cfgDungeon.type == 15 )
  {
    v38 = Player::getRecord(player, this->m_cfgDungeon.group_id) + 1;
    Player::updateRecord(player, this->m_cfgDungeon.group_id, v38);
    group_id = this->m_cfgDungeon.group_id;
    PlayerHuoYueDu = Player::GetPlayerHuoYueDu(player);
    CHuoYueDu::AddHuoYueDuRecord(PlayerHuoYueDu, 2, group_id, 0);
  }
  if ( Dungeon::getDungeonId(this) == 10003 )
  {
    v41 = Unit::getNow(player) + 300;
    Player::updateRecord(player, 1066, v41);
    Player::RecalcAttr(player);
  }
  return 1;
}


#####################################
void __cdecl Dungeon::InitTeamMember(Dungeon *const this, const CharIdList *const lst)
{
  std::list<long>::operator=(&this->m_memberList, lst);
}


#####################################
void __cdecl Dungeon::AddPlayerDamage(Dungeon *const this, CharId_t cid, int32_t attackValue)
{
  DamageSum *v3; // rax
  std::_List_iterator<DamageSum> eiter; // [rsp+20h] [rbp-20h] BYREF
  std::_List_iterator<DamageSum> iter; // [rsp+30h] [rbp-10h] BYREF

  if ( this->m_cfgDungeon.type == 12 )
  {
    iter._M_node = std::list<DamageSum>::begin(&this->m_damages)._M_node;
    eiter._M_node = std::list<DamageSum>::end(&this->m_damages)._M_node;
    while ( std::_List_iterator<DamageSum>::operator!=(&iter, &eiter) )
    {
      if ( std::_List_iterator<DamageSum>::operator->(&iter)->cid == cid )
      {
        v3 = std::_List_iterator<DamageSum>::operator->(&iter);
        v3->damage += attackValue;
        this->m_needBroadcastDamage = 1;
        return;
      }
      std::_List_iterator<DamageSum>::operator++(&iter);
    }
  }
}


#####################################
void __cdecl Dungeon::AddMonsterExp(Dungeon *const this, int32_t nExp)
{
  if ( this->m_cfgDungeon.type == 23 )
    this->m_finshInfo.get_exp += nExp;
}


#####################################
void __cdecl Dungeon::AddDungeonTime(Dungeon *const this, int32_t nTime)
{
  this->m_nAddonTime += nTime;
  Dungeon::broadcastDungeonInfo(this);
}


#####################################
int32_t __cdecl Dungeon::GetLeftTime(Dungeon *const this)
{
  int64_t m_stateTick; // rbx
  int64_t v2; // rbx
  int64_t v3; // rax
  int64_t v4; // rbx
  int64_t v5; // rbx

  switch ( this->m_state )
  {
    case DungeonState::DS_RUNNING:
      m_stateTick = this->m_stateTick;
      v2 = 1000 * Dungeon::GetDurationTime(this) + m_stateTick;
      v3 = (v2 - Map::getTick(this)) / 1000;
      break;
    case DungeonState::DS_SUMMON:
    case DungeonState::DS_BOSS:
    case DungeonState::DS_FAIL:
      v4 = this->m_stateTick + 1000 * this->m_stateParam;
      v3 = (v4 - Map::getTick(this)) / 1000;
      break;
    case DungeonState::DS_WIN:
      v5 = this->m_stateTick + 1000 * this->m_cfgDungeon.reward_time;
      v3 = (v5 - Map::getTick(this)) / 1000;
      break;
    default:
      LODWORD(v3) = Dungeon::GetDurationTime(this);
      break;
  }
  return v3;
}


#####################################
void __cdecl Dungeon::teamDungeonMemberEnter(Dungeon *const this)
{
  GameService *v1; // rax

  if ( std::list<Player *>::empty(&this->m_players) )
  {
    v1 = Answer::Singleton<GameService>::instance();
    GameService::TeamDungeonEnterDungeon(v1, this, &this->m_memberList);
  }
}


#####################################
void __cdecl Dungeon::checkRevive(Dungeon *const this, int64_t curTick)
{
  int64_t DieTick; // rax
  int32_t Now; // eax
  std::_List_iterator<Player*> eiter; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+20h] [rbp-30h] BYREF
  Player *player; // [rsp+30h] [rbp-20h]
  int32_t ReviveTime; // [rsp+3Ch] [rbp-14h]

  if ( this->m_cfgDungeon.type != 36 )
  {
    iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
    eiter._M_node = std::list<Player *>::end(&this->m_players)._M_node;
    while ( std::_List_iterator<Player *>::operator!=(&iter, &eiter) )
    {
      player = *std::_List_iterator<Player *>::operator*(&iter);
      if ( player && Player::IsDead(player) )
      {
        ReviveTime = 10000;
        DieTick = Player::GetDieTick(player);
        if ( curTick - DieTick >= ReviveTime )
        {
          Now = Map::getNow(this);
          Player::SetStartProtect(player, Now);
          Player::FullHPAndSync(player);
          Unit::instantMove(player, this->m_cfgDungeon.x, this->m_cfgDungeon.y, InstanceMoveReason::IMR_TRANSFER, 0);
        }
      }
      std::_List_iterator<Player *>::operator++(&iter);
    }
  }
}


#####################################
bool __cdecl Dungeon::OnSafeRevive(Dungeon *const this, Player *player)
{
  int32_t Now; // edx

  if ( !player )
    return 0;
  if ( this->m_cfgDungeon.type == 36 )
  {
    Player::leaveDungeon(player);
  }
  else
  {
    Now = Map::getNow(this);
    Player::SetStartProtect(player, Now);
    Player::FullHPAndSync(player);
    Unit::instantMove(player, this->m_cfgDungeon.x, this->m_cfgDungeon.y, InstanceMoveReason::IMR_TRANSFER, 0);
  }
  return 1;
}


#####################################
void __cdecl Dungeon::DungeonGongGao(Dungeon *const this, int8_t connid, CharId_t CharId, std::string *p_Name)
{
  GameService *v4; // rax
  uint32_t WOffset; // edx
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  v4 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v4, connid, Answer::PackType::PACK_DISPATCH, 0x2CC1u);
  if ( packet )
  {
    Answer::NetPacket::writeInt64(packet, CharId);
    Answer::NetPacket::writeUTF8(packet, p_Name);
    Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.Battle);
    Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.star);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v6, connid, packet);
  }
}


#####################################
void __cdecl Dungeon::removePlayer(Dungeon *const this, Player *player, bool islogout)
{
  CfgMapEvent *v3; // rax
  CfgMapEvent *v4; // rax
  bool v5; // al
  void (__fastcall *v6)(Dungeon *const, CfgMapEvent *, Player *); // r12
  CfgMapEvent *v7; // rcx
  std::_List_iterator<CfgMapEvent> it; // [rsp+20h] [rbp-30h] BYREF
  std::_List_iterator<CfgMapEvent> __x; // [rsp+30h] [rbp-20h] BYREF

  if ( player && Player::getCid(player) == this->m_TeamLeaderId )
  {
    for ( it._M_node = std::list<CfgMapEvent>::begin(&this->m_events)._M_node;
          ;
          std::_List_iterator<CfgMapEvent>::operator++(&it) )
    {
      __x._M_node = std::list<CfgMapEvent>::end(&this->m_events)._M_node;
      if ( !std::_List_iterator<CfgMapEvent>::operator!=(&it, &__x) )
        break;
      v3 = std::_List_iterator<CfgMapEvent>::operator->(&it);
      v5 = 0;
      if ( CfgMapEvent::isOpen(v3) )
      {
        v4 = std::_List_iterator<CfgMapEvent>::operator->(&it);
        if ( !CfgMapEvent::isDone(v4) )
          v5 = 1;
      }
      if ( v5
        && Dungeon::getState(this) == DungeonState::DS_RUNNING
        && std::_List_iterator<CfgMapEvent>::operator->(&it)->trigger_type == 10 )
      {
        v6 = (void (__fastcall *)(Dungeon *const, CfgMapEvent *, Player *))*((_QWORD *)this->_vptr_Map + 33);
        v7 = std::_List_iterator<CfgMapEvent>::operator*(&it);
        v6(this, v7, player);
      }
    }
  }
  Map::removePlayer(this, player, islogout);
}


#####################################
bool __cdecl Dungeon::isAllMonsterDie(Dungeon *const this)
{
  std::_List_iterator<Monster*> iter; // [rsp+10h] [rbp-20h] BYREF
  std::_List_iterator<Monster*> __x; // [rsp+20h] [rbp-10h] BYREF
  Monster *pMonster; // [rsp+28h] [rbp-8h]

  for ( iter._M_node = std::list<Monster *>::begin(&this->m_monsters)._M_node;
        ;
        std::_List_iterator<Monster *>::operator++(&iter) )
  {
    __x._M_node = std::list<Monster *>::end(&this->m_monsters)._M_node;
    if ( !std::_List_iterator<Monster *>::operator!=(&iter, &__x) )
      break;
    pMonster = *std::_List_iterator<Monster *>::operator*(&iter);
    if ( pMonster && Unit::isAlive(pMonster) )
      return 0;
  }
  return 1;
}


#####################################
bool __cdecl Dungeon::isAllPlayerSummon(Dungeon *const this)
{
  size_t v1; // rbx

  v1 = std::list<SummBossInfo>::size(&this->m_lSummonBoss);
  return v1 == std::list<Player *>::size(&this->m_players);
}


#####################################
void __cdecl Dungeon::checkSummonBoss(Dungeon *const this)
{
  CharId_t cid; // rbx
  SummBossInfo info; // [rsp+10h] [rbp-80h] BYREF
  std::_List_iterator<SummBossInfo> it; // [rsp+20h] [rbp-70h] BYREF
  std::_List_iterator<Player*> iter; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<Player*> v5; // [rsp+40h] [rbp-50h] BYREF
  std::_List_iterator<SummBossInfo> __x; // [rsp+50h] [rbp-40h] BYREF
  std::string name; // [rsp+60h] [rbp-30h] BYREF
  Player *player; // [rsp+70h] [rbp-20h]
  bool bFind; // [rsp+7Fh] [rbp-11h]

  if ( this->m_cfgDungeon.type == 12
    && !Dungeon::isAllPlayerSummon(this)
    && Map::getTick(this) - this->m_nSummStart > 29999 )
  {
    for ( iter._M_node = std::list<Player *>::begin(&this->m_players)._M_node;
          ;
          std::_List_iterator<Player *>::operator++(&iter) )
    {
      v5._M_node = std::list<Player *>::end(&this->m_players)._M_node;
      if ( !std::_List_iterator<Player *>::operator!=(&iter, &v5) )
        break;
      player = *std::_List_iterator<Player *>::operator*(&iter);
      if ( player )
      {
        bFind = 0;
        for ( it._M_node = std::list<SummBossInfo>::begin(&this->m_lSummonBoss)._M_node;
              ;
              std::_List_iterator<SummBossInfo>::operator++(&it) )
        {
          __x._M_node = std::list<SummBossInfo>::end(&this->m_lSummonBoss)._M_node;
          if ( !std::_List_iterator<SummBossInfo>::operator!=(&it, &__x) )
            break;
          cid = std::_List_iterator<SummBossInfo>::operator->(&it)->cid;
          if ( cid == Player::getCid(player) )
          {
            bFind = 1;
            break;
          }
        }
        if ( !bFind )
        {
          info.cid = 0;
          *(_QWORD *)&info.state = 0;
          info.cid = Player::getCid(player);
          std::list<SummBossInfo>::push_back(&this->m_lSummonBoss, &info);
          Player::getName((const Player *const)&name);
          Dungeon::broadcastSummonBoss(this, &name, 0);
          std::string::~string(&name);
        }
      }
    }
    if ( Dungeon::isAllMonsterDie(this) )
      Dungeon::win(this, 0);
  }
}


#####################################
void __cdecl Dungeon::sendStartSummon(Dungeon *const this)
{
  GameService *v1; // rax
  int32_t LeftTime; // edx
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2DF5u);
  if ( packet )
  {
    LeftTime = Dungeon::GetLeftTime(this);
    Answer::NetPacket::writeInt32(packet, LeftTime);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
void __cdecl Dungeon::OpenBoxMonster(Dungeon *const this, const int32_t BossId, bool rewardWave)
{
  MonsterWait stu; // [rsp+10h] [rbp-30h] BYREF

  memset(&stu.broad, 0, 20);
  stu.id = BossId;
  *(_QWORD *)&stu.rewardWave = rewardWave;
  stu.startTick = Map::getTick(this);
  std::list<MonsterWait>::push_back(&this->m_waitMonster, &stu);
}


#####################################
void __cdecl Dungeon::sendRandEventTime(Dungeon *const this)
{
  GameService *v1; // rax
  uint32_t WOffset; // edx
  Answer::NetPacket *packet; // [rsp+18h] [rbp-8h]

  v1 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v1, Answer::PackType::PACK_DISPATCH, 0x2DF6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_cfgDungeon.rand_time);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    Map::broadcast(this, packet);
  }
}


#####################################
int32_t __cdecl Dungeon::GuessTheSize(Dungeon *const this, Player *player, int32_t nId)
{
  Answer::Random *v4; // rax
  CExtCharBag *Bag; // rax
  CharId_t Cid; // r12
  int8_t ConnId; // bl
  DBService *v8; // rax
  GameService *v9; // rax
  CharId_t v10; // rax
  uint32_t WOffset; // eax
  GameService *v12; // rax
  MemChrBag starReward; // [rsp+30h] [rbp-60h] BYREF
  std::string Param; // [rsp+50h] [rbp-40h] BYREF
  char v16; // [rsp+5Fh] [rbp-31h] BYREF
  std::string val; // [rsp+60h] [rbp-30h] BYREF
  int32_t Constgold; // [rsp+70h] [rbp-20h]
  int32_t nRand; // [rsp+74h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+78h] [rbp-18h]

  if ( !player || this->m_bGetReward )
    return 0;
  Constgold = 100;
  if ( this->m_Times <= 0 )
    Constgold = 50;
  if ( !Player::DecCurrency(
          player,
          CURRENCY_TYPE::CURRENCY_GOLD,
          Constgold,
          CURRENCY_CHANGE_REASON::GCR_YJSK_GUESS_SIZE,
          0) )
    return 0;
  v4 = Answer::Singleton<Answer::Random>::instance();
  nRand = Answer::Random::generate(v4, 1, 3);
  if ( nRand == nId )
  {
    *(_QWORD *)&starReward.itemId = 0x100000259LL;
    *(_QWORD *)&starReward.itemCount = 0x100000032LL;
    *(_QWORD *)&starReward.endTime = 0;
    starReward.srcId = 0;
    Bag = Player::GetBag(player);
    if ( !CExtCharBag::AddItem(Bag, &starReward, ITEM_CHANGE_REASON::ICR_DUNGEON_GUESS_SIZE) )
    {
      std::allocator<char>::allocator(&v16);
      std::string::string(&Param, &unk_8D658F, &v16);
      Cid = Player::getCid(player);
      ConnId = Player::getConnId(player);
      v8 = Answer::Singleton<DBService>::instance();
      DBService::OnSendSysMail(v8, ConnId, Cid, 1, &starReward, ITEM_CHANGE_REASON::ICR_DUNGEON_GUESS_SIZE, &Param, 0);
      std::string::~string(&Param);
      std::allocator<char>::~allocator(&v16);
    }
    this->m_bGetReward = 1;
    v9 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v9, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 455);
      v10 = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, v10);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, 50);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v12, 0, packet);
    }
  }
  ++this->m_Times;
  Dungeon::broadcastDungeonInfo(this);
  return nRand;
}


#####################################
bool __cdecl Dungeon::DungeonGuWu(Dungeon *const this, Player *player, int8_t Type)
{
  int32_t v4; // ebx
  CfgData *v5; // rax
  int64_t Money; // rbx
  CExtCurrency *Currency; // rax
  Answer::Random *v8; // rax
  int32_t MoneyBuffId; // ebx
  CfgData *v10; // rax
  int32_t v11; // edx
  Buff *v12; // rbx
  int32_t v13; // ebx
  CfgData *v14; // rax
  Answer::Random *v15; // rax
  int32_t GoldBuffId; // ebx
  CfgData *v17; // rax
  int32_t v18; // edx
  Buff *v19; // rbx
  UnitHandle launcher; // [rsp+30h] [rbp-90h] BYREF
  UnitHandle v21; // [rsp+40h] [rbp-80h] BYREF
  bool Success; // [rsp+5Fh] [rbp-61h]
  GuWuCfg *pGuWu; // [rsp+60h] [rbp-60h]
  int32_t nRand; // [rsp+6Ch] [rbp-54h]
  CfgBuff *cfgBuff; // [rsp+70h] [rbp-50h]
  Buff *buff; // [rsp+78h] [rbp-48h]
  GuWuCfg *pGuWu_0; // [rsp+80h] [rbp-40h]
  int32_t nRand_0; // [rsp+8Ch] [rbp-34h]
  CfgBuff *cfgBuff_0; // [rsp+90h] [rbp-30h]
  Buff *buff_0; // [rsp+98h] [rbp-28h]

  Success = 0;
  if ( !player )
    return Success;
  if ( Type == 1 )
  {
    v4 = this->m_MoneyBuffLevel + 1;
    v5 = Answer::Singleton<CfgData>::instance();
    pGuWu = CfgData::GetGuWuCfg(v5, v4);
    if ( pGuWu )
    {
      if ( pGuWu->Money <= 0 )
        return Success;
      Money = pGuWu->Money;
      Currency = Player::GetCurrency(player);
      if ( !CExtCurrency::DecMoneyAndNoBind(Currency, Money, CURRENCY_CHANGE_REASON::GCR_GU_WU, 0) )
        return Success;
      v8 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v8, 1, 10000);
      if ( pGuWu->MoneyRate >= nRand )
      {
        ++this->m_MoneyBuffLevel;
        Success = 1;
        MoneyBuffId = pGuWu->MoneyBuffId;
        v10 = Answer::Singleton<CfgData>::instance();
        cfgBuff = CfgData::getBuff(v10, MoneyBuffId);
        if ( cfgBuff )
        {
          launcher.id = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 12))(player);
          launcher.type = v11;
          v12 = (Buff *)operator new(0x60u);
          Buff::Buff(v12, player, cfgBuff, &launcher, 2, 0);
          buff = v12;
          if ( v12 )
            Unit::addBuff(player, buff);
        }
      }
    }
  }
  else if ( Type == 2 )
  {
    v13 = this->m_GoldBuffLevel + 1;
    v14 = Answer::Singleton<CfgData>::instance();
    pGuWu_0 = CfgData::GetGuWuCfg(v14, v13);
    if ( pGuWu_0 )
    {
      if ( pGuWu_0->Gold <= 0 )
        return Success;
      if ( !Player::DecCurrency(
              player,
              CURRENCY_TYPE::CURRENCY_GOLD,
              pGuWu_0->Gold,
              CURRENCY_CHANGE_REASON::GCR_GU_WU,
              0) )
        return Success;
      v15 = Answer::Singleton<Answer::Random>::instance();
      nRand_0 = Answer::Random::generate(v15, 1, 10000);
      if ( pGuWu_0->GoldRate >= nRand_0 )
      {
        ++this->m_GoldBuffLevel;
        Success = 1;
        GoldBuffId = pGuWu_0->GoldBuffId;
        v17 = Answer::Singleton<CfgData>::instance();
        cfgBuff_0 = CfgData::getBuff(v17, GoldBuffId);
        if ( cfgBuff_0 )
        {
          v21.id = (*((__int64 (__fastcall **)(Player *))player->_vptr_Entity + 12))(player);
          v21.type = v18;
          v19 = (Buff *)operator new(0x60u);
          Buff::Buff(v19, player, cfgBuff_0, &v21, 2, 0);
          buff_0 = v19;
          if ( v19 )
            Unit::addBuff(player, buff_0);
        }
      }
    }
  }
  Dungeon::broadcastDungeonInfo(this);
  return Success;
}


