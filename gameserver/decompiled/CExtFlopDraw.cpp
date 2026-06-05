// Decompiled methods for class: CExtFlopDraw
// Source: gameserver.cc
// Total methods: 11

#####################################
void __cdecl CExtFlopDraw::~CExtFlopDraw(CExtFlopDraw *const this)
{
  CExtFlopDraw::~CExtFlopDraw(this);
  operator delete(this);
}


#####################################
void __cdecl CExtFlopDraw::OnLoadFromDB(CExtFlopDraw *const this, const PlayerDBData *const dbData)
{
  std::map<int,std::map<int,int>>::operator=(&this->m_FlopDrawRecordMap, &dbData->m_CFlopDraw.m_FlopDrawRecordMap);
}


#####################################
void __cdecl CExtFlopDraw::OnSaveToDB(CExtFlopDraw *const this, PlayerDBData *const dbData)
{
  std::map<int,std::map<int,int>>::operator=(&dbData->m_CFlopDraw.m_FlopDrawRecordMap, &this->m_FlopDrawRecordMap);
}


#####################################
bool __cdecl CExtFlopDraw::OnFlopDraw(CExtFlopDraw *const this, int32_t nType, int32_t nFlopId)
{
  bool v3; // bl
  CExtCharBag *Bag; // rax
  CfgData *v5; // rax
  const FlopDrawCfgMap *FlopTable; // rax
  const std::pair<const int,FlopDrawCfg> *v7; // rax
  int first; // edx
  const std::pair<const int,FlopDrawCfg> *v9; // rax
  const std::pair<const int,FlopDrawCfg> *v10; // rax
  Answer::Random *v11; // rax
  FlopDrawCfg *v12; // rax
  FlopDrawCfg *v13; // rax
  CExtCharBag *v14; // rax
  GameService *v15; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v18; // rax
  FlopDrawCfg ResultItem; // [rsp+10h] [rbp-E0h] BYREF
  FlopDrawCfgMap pFlopTable; // [rsp+40h] [rbp-B0h] BYREF
  std::_List_iterator<FlopDrawCfg> itList; // [rsp+70h] [rbp-80h] BYREF
  FlopDrawCfgList Stu; // [rsp+80h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,FlopDrawCfg> > it; // [rsp+90h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,FlopDrawCfg> > __x; // [rsp+A0h] [rbp-50h] BYREF
  std::_List_iterator<FlopDrawCfg> v27; // [rsp+B0h] [rbp-40h] BYREF
  std::string val; // [rsp+C0h] [rbp-30h] BYREF
  int32_t FlopType; // [rsp+CCh] [rbp-24h]
  int32_t MaxRate; // [rsp+D0h] [rbp-20h]
  int32_t nRand; // [rsp+D4h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+D8h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Bag = Player::GetBag(this->m_pPlayer);
    if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
      return 0;
    FlopType = CExtFlopDraw::GetFlopType(this, nType, nFlopId);
    v5 = Answer::Singleton<CfgData>::instance();
    FlopTable = CfgData::GetFlopTable(v5);
    std::map<int,FlopDrawCfg>::map(&pFlopTable, FlopTable);
    it._M_node = std::map<int,FlopDrawCfg>::begin(&pFlopTable)._M_node;
    std::list<FlopDrawCfg>::list(&Stu);
    MaxRate = 0;
    while ( 1 )
    {
      __x._M_node = std::map<int,FlopDrawCfg>::end(&pFlopTable)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,FlopDrawCfg>>::operator!=(&it, &__x) )
        break;
      v7 = std::_Rb_tree_const_iterator<std::pair<int const,FlopDrawCfg>>::operator->(&it);
      if ( v7->second.m_nType == FlopType )
      {
        first = std::_Rb_tree_const_iterator<std::pair<int const,FlopDrawCfg>>::operator->(&it)->first;
        if ( !CExtFlopDraw::IsGet(this, nType, first) )
        {
          v9 = std::_Rb_tree_const_iterator<std::pair<int const,FlopDrawCfg>>::operator->(&it);
          std::list<FlopDrawCfg>::push_back(&Stu, &v9->second);
          v10 = std::_Rb_tree_const_iterator<std::pair<int const,FlopDrawCfg>>::operator->(&it);
          MaxRate += v10->second.m_nRate;
        }
      }
      std::_Rb_tree_const_iterator<std::pair<int const,FlopDrawCfg>>::operator++(&it, 0);
    }
    if ( MaxRate > 0 )
    {
      v11 = Answer::Singleton<Answer::Random>::instance();
      nRand = Answer::Random::generate(v11, 1, MaxRate);
      itList._M_node = std::list<FlopDrawCfg>::begin(&Stu)._M_node;
      memset(&ResultItem, 0, sizeof(ResultItem));
      while ( 1 )
      {
        v27._M_node = std::list<FlopDrawCfg>::end(&Stu)._M_node;
        if ( !std::_List_iterator<FlopDrawCfg>::operator!=(&itList, &v27) )
          break;
        v12 = std::_List_iterator<FlopDrawCfg>::operator->(&itList);
        if ( v12->m_nRate >= nRand )
        {
          ResultItem = *std::_List_iterator<FlopDrawCfg>::operator*(&itList);
          break;
        }
        v13 = std::_List_iterator<FlopDrawCfg>::operator->(&itList);
        nRand -= v13->m_nRate;
        std::_List_iterator<FlopDrawCfg>::operator++(&itList, 0);
      }
      if ( ResultItem.m_nId > 0 )
      {
        if ( CExtFlopDraw::DrawAndCost(this, nType, nFlopId) )
        {
          v14 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::AddItem(v14, &ResultItem.m_Item, ITEM_CHANGE_REASON::IDCR_FLOP);
          CExtFlopDraw::addDrawTimes(this, nType, nFlopId, ResultItem.m_nId);
          CExtFlopDraw::SendFlopOneRecord(this, this->m_pPlayer, nType, nFlopId, ResultItem.m_nId);
          if ( ResultItem.m_GongGaoId > 0 )
          {
            v15 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v15, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( !packet )
            {
              v3 = 0;
              goto LABEL_27;
            }
            Answer::NetPacket::writeInt32(packet, ResultItem.m_GongGaoId);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Answer::NetPacket::writeInt32(packet, ResultItem.m_nId);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v18 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v18, 0, packet);
          }
          v3 = 1;
          goto LABEL_27;
        }
        v3 = 0;
      }
      else
      {
        v3 = 0;
      }
    }
    else
    {
      v3 = 0;
    }
LABEL_27:
    std::list<FlopDrawCfg>::~list(&Stu);
    std::map<int,FlopDrawCfg>::~map(&pFlopTable);
    return v3;
  }
  return 0;
}


#####################################
int32_t __cdecl CExtFlopDraw::GetFlopType(CExtFlopDraw *const this, int32_t nType, int32_t nFlopId)
{
  COpenBeta *v3; // rax
  CKaiFuHuoDong *v5; // rax

  if ( nType == 1 )
  {
    v3 = Answer::Singleton<COpenBeta>::instance();
    return COpenBeta::GetFlopType(v3, nFlopId);
  }
  else if ( nType == 2 )
  {
    v5 = Answer::Singleton<CKaiFuHuoDong>::instance();
    return CKaiFuHuoDong::GetFlopType(v5, nFlopId);
  }
  else
  {
    return 0;
  }
}


#####################################
bool __cdecl CExtFlopDraw::DrawAndCost(CExtFlopDraw *const this, int32_t nType, int32_t nFlopId)
{
  Player *m_pPlayer; // rbx
  COpenBeta *v5; // rax
  Player *v6; // rbx
  CKaiFuHuoDong *v7; // rax

  if ( CExtFlopDraw::IsFloped(this, nType, nFlopId) )
    return 0;
  if ( nType == 1 )
  {
    m_pPlayer = this->m_pPlayer;
    v5 = Answer::Singleton<COpenBeta>::instance();
    return COpenBeta::CanFlopDraw(v5, m_pPlayer, nFlopId);
  }
  else if ( nType == 2 )
  {
    v6 = this->m_pPlayer;
    v7 = Answer::Singleton<CKaiFuHuoDong>::instance();
    return CKaiFuHuoDong::CanFlopDraw(v7, v6, nFlopId);
  }
  else
  {
    return 0;
  }
}


#####################################
bool __cdecl CExtFlopDraw::IsGet(CExtFlopDraw *const this, int32_t nType, int32_t nId)
{
  std::pair<const int,std::map<int,int> > *v3; // rax
  std::pair<const int,std::map<int,int> > *v5; // rax
  int32_t nTypea; // [rsp+4h] [rbp-4Ch] BYREF
  CExtFlopDraw *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,int> > itFlop; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v12; // [rsp+40h] [rbp-10h] BYREF

  thisa = this;
  nTypea = nType;
  it._M_node = std::map<int,std::map<int,int>>::find(&this->m_FlopDrawRecordMap, &nTypea)._M_node;
  __x._M_node = std::map<int,std::map<int,int>>::end(&thisa->m_FlopDrawRecordMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
    for ( itFlop._M_node = std::map<int,int>::begin(&v3->second)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itFlop, 0) )
    {
      v5 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
      v12._M_node = std::map<int,int>::end(&v5->second)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itFlop, &v12) )
        break;
      if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->second == nId )
        return 1;
    }
  }
  return 0;
}


#####################################
bool __cdecl CExtFlopDraw::IsFloped(CExtFlopDraw *const this, int32_t nType, int32_t nFlopId)
{
  std::pair<const int,std::map<int,int> > *v3; // rax
  std::pair<const int,std::map<int,int> > *v4; // rax
  int32_t nFlopIda; // [rsp+0h] [rbp-50h] BYREF
  int32_t nTypea; // [rsp+4h] [rbp-4Ch] BYREF
  CExtFlopDraw *thisa; // [rsp+8h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,int> > itFlop; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > it; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > __x; // [rsp+30h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v12; // [rsp+40h] [rbp-10h] BYREF

  thisa = this;
  nTypea = nType;
  nFlopIda = nFlopId;
  it._M_node = std::map<int,std::map<int,int>>::find(&this->m_FlopDrawRecordMap, &nTypea)._M_node;
  __x._M_node = std::map<int,std::map<int,int>>::end(&thisa->m_FlopDrawRecordMap)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator!=(&it, &__x) )
    return 0;
  v3 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
  itFlop._M_node = std::map<int,int>::find(&v3->second, &nFlopIda)._M_node;
  v4 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
  v12._M_node = std::map<int,int>::end(&v4->second)._M_node;
  return std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itFlop, &v12)
      && std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->second > 0;
}


#####################################
void __cdecl CExtFlopDraw::addDrawTimes(CExtFlopDraw *const this, int32_t nType, int32_t nFlopId, int32_t FlopResult)
{
  std::pair<const int,std::map<int,int> > *v4; // rax
  std::pair<const int,std::map<int,int> > *v5; // rax
  std::pair<const int,std::map<int,int> > *v6; // rax
  std::map<int,int> *v7; // rax
  int32_t FlopResulta; // [rsp+1Ch] [rbp-B4h] BYREF
  int32_t nFlopIda; // [rsp+20h] [rbp-B0h] BYREF
  int32_t nTypea; // [rsp+24h] [rbp-ACh] BYREF
  CExtFlopDraw *thisa; // [rsp+28h] [rbp-A8h]
  Int32Int32Map TmpMap; // [rsp+30h] [rbp-A0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > itFlop; // [rsp+60h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > it; // [rsp+70h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > __x; // [rsp+80h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v16; // [rsp+90h] [rbp-40h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,int> >,bool> v17; // [rsp+A0h] [rbp-30h]
  std::pair<const int,int> v18; // [rsp+B0h] [rbp-20h] BYREF

  thisa = this;
  nTypea = nType;
  nFlopIda = nFlopId;
  FlopResulta = FlopResult;
  it._M_node = std::map<int,std::map<int,int>>::find(&this->m_FlopDrawRecordMap, &nTypea)._M_node;
  __x._M_node = std::map<int,std::map<int,int>>::end(&thisa->m_FlopDrawRecordMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator!=(&it, &__x) )
  {
    v4 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
    itFlop._M_node = std::map<int,int>::find(&v4->second, &nFlopIda)._M_node;
    v5 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
    v16._M_node = std::map<int,int>::end(&v5->second)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itFlop, &v16) )
    {
      std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop)->second = FlopResulta;
    }
    else
    {
      std::pair<int const,int>::pair(&v18, &nFlopIda, &FlopResulta);
      v6 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
      v17 = std::map<int,int>::insert(&v6->second, &v18);
    }
  }
  else
  {
    std::map<int,int>::map(&TmpMap);
    *std::map<int,int>::operator[](&TmpMap, &nFlopIda) = FlopResulta;
    v7 = std::map<int,std::map<int,int>>::operator[](&thisa->m_FlopDrawRecordMap, &nTypea);
    std::map<int,int>::operator=(v7, &TmpMap);
    std::map<int,int>::~map(&TmpMap);
  }
}


#####################################
void __cdecl CExtFlopDraw::SendFlopRecord(CExtFlopDraw *const this, Player *player, int32_t nType)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  std::pair<const int,std::map<int,int> > *v5; // rax
  int32_t v6; // eax
  std::pair<const int,std::map<int,int> > *v7; // rax
  std::pair<const int,int> *v8; // rax
  std::pair<const int,int> *v9; // rax
  std::pair<const int,std::map<int,int> > *v10; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v13; // bl
  GameService *v14; // rax
  int32_t nTypea; // [rsp+Ch] [rbp-64h] BYREF
  Player *playera; // [rsp+10h] [rbp-60h]
  CExtFlopDraw *thisa; // [rsp+18h] [rbp-58h]
  std::_Rb_tree_iterator<std::pair<const int,int> > itFlop; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > it; // [rsp+30h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,std::map<int,int> > > __x; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,int> > v21; // [rsp+50h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+58h] [rbp-18h]

  thisa = this;
  playera = player;
  nTypea = nType;
  if ( player )
  {
    it._M_node = std::map<int,std::map<int,int>>::find(&thisa->m_FlopDrawRecordMap, &nTypea)._M_node;
    __x._M_node = std::map<int,std::map<int,int>>::end(&thisa->m_FlopDrawRecordMap)._M_node;
    if ( std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator!=(&it, &__x) )
    {
      ConnId = Player::getConnId(playera);
      v4 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EBFu);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, nTypea);
        v5 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
        v6 = std::map<int,int>::size(&v5->second);
        Answer::NetPacket::writeInt32(packet, v6);
        v7 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
        for ( itFlop._M_node = std::map<int,int>::begin(&v7->second)._M_node;
              ;
              std::_Rb_tree_iterator<std::pair<int const,int>>::operator++(&itFlop, 0) )
        {
          v10 = std::_Rb_tree_iterator<std::pair<int const,std::map<int,int>>>::operator->(&it);
          v21._M_node = std::map<int,int>::end(&v10->second)._M_node;
          if ( !std::_Rb_tree_iterator<std::pair<int const,int>>::operator!=(&itFlop, &v21) )
            break;
          v8 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop);
          Answer::NetPacket::writeInt32(packet, v8->first);
          v9 = std::_Rb_tree_iterator<std::pair<int const,int>>::operator->(&itFlop);
          Answer::NetPacket::writeInt32(packet, v9->second);
        }
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(playera);
        v13 = Player::getConnId(playera);
        v14 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v14, v13, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CExtFlopDraw::SendFlopOneRecord(
        CExtFlopDraw *const this,
        Player *player,
        int32_t nType,
        int32_t FlopId,
        int32_t FlopResult)
{
  int8_t ConnId; // bl
  GameService *v6; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EC0u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, nType);
      Answer::NetPacket::writeInt32(packet, FlopId);
      Answer::NetPacket::writeInt32(packet, FlopResult);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(player);
      v9 = Player::getConnId(player);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


