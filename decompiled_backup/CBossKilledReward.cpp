// Decompiled methods for class: CBossKilledReward
// Source: gameserver.cc
// Total methods: 13

#####################################
void __cdecl CBossKilledReward::~CBossKilledReward(CBossKilledReward *const this)
{
  CBossKilledReward::~CBossKilledReward(this);
  operator delete(this);
}


#####################################
void __cdecl CBossKilledReward::OnCleanUp(CBossKilledReward *const this)
{
  CfgData *v1; // rax
  const BossKilledRewardMap *BossKilledRewardMap; // rax
  const std::pair<const signed char,BossKilledReward> *v3; // rax
  const std::pair<const signed char,BossKilledReward> *v4; // rax
  BossKilledRewardInfo *v5; // rax
  const std::pair<const signed char,BossKilledReward> *v6; // rax
  const std::pair<const signed char,BossKilledReward> *v7; // rax
  BossKilledRewardMap RewardMap; // [rsp+10h] [rbp-B0h] BYREF
  BossKilledInfo stu; // [rsp+40h] [rbp-80h] BYREF
  std::_List_const_iterator<int> iter; // [rsp+50h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,BossKilledReward> > it; // [rsp+60h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledReward> > __it; // [rsp+70h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,BossKilledReward> > v13; // [rsp+80h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledReward> > v14; // [rsp+90h] [rbp-30h] BYREF
  std::_List_const_iterator<int> __x; // [rsp+A0h] [rbp-20h] BYREF

  std::map<signed char,BossKilledRewardInfo>::clear(&this->m_BossKilledRewardMap);
  v1 = Answer::Singleton<CfgData>::instance();
  BossKilledRewardMap = CfgData::GetBossKilledRewardMap(v1);
  std::map<signed char,BossKilledReward>::map(&RewardMap, BossKilledRewardMap);
  __it._M_node = std::map<signed char,BossKilledReward>::begin(&RewardMap)._M_node;
  std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::_Rb_tree_const_iterator(&it, &__it);
  while ( 1 )
  {
    v14._M_node = std::map<signed char,BossKilledReward>::end(&RewardMap)._M_node;
    std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::_Rb_tree_const_iterator(&v13, &v14);
    if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::operator!=(&it, &v13) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::operator->(&it);
    for ( iter._M_node = std::list<int>::begin(&v3->second.BossList)._M_node;
          ;
          std::_List_const_iterator<int>::operator++(&iter, 0) )
    {
      v7 = std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::operator->(&it);
      __x._M_node = std::list<int>::end(&v7->second.BossList)._M_node;
      if ( !std::_List_const_iterator<int>::operator!=(&iter, &__x) )
        break;
      stu = 0;
      stu.BossId = *std::_List_const_iterator<int>::operator*(&iter);
      v4 = std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::operator->(&it);
      v5 = std::map<signed char,BossKilledRewardInfo>::operator[](&this->m_BossKilledRewardMap, &v4->first);
      std::list<BossKilledInfo>::push_back(&v5->BossKeilled, &stu);
      v6 = std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::operator->(&it);
      std::map<signed char,BossKilledRewardInfo>::operator[](&this->m_BossKilledRewardMap, &v6->first)->IsGetReward = 0;
    }
    std::_Rb_tree_const_iterator<std::pair<signed char const,BossKilledReward>>::operator++(&it, 0);
  }
  std::map<signed char,BossKilledReward>::~map(&RewardMap);
}


#####################################
void __cdecl CBossKilledReward::OnLoadFromDB(CBossKilledReward *const this, const PlayerDBData *const dbData)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v7; // rax
  std::string *v8; // rax
  std::string *v9; // rax
  const char *v10; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v11; // rax
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > iter; // [rsp+10h] [rbp-100h] BYREF
  StringVector BossIdVt; // [rsp+20h] [rbp-F0h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > itBoss; // [rsp+40h] [rbp-D0h] BYREF
  int8_t Type; // [rsp+4Fh] [rbp-C1h] BYREF
  StringVector StringVt; // [rsp+50h] [rbp-C0h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+70h] [rbp-A0h] BYREF
  StringVector mineString; // [rsp+80h] [rbp-90h] BYREF
  std::string delims; // [rsp+A0h] [rbp-70h] BYREF
  char v20; // [rsp+AFh] [rbp-61h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > v21; // [rsp+B0h] [rbp-60h] BYREF
  std::string v22; // [rsp+C0h] [rbp-50h] BYREF
  char v23; // [rsp+CFh] [rbp-41h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > __x; // [rsp+D0h] [rbp-40h] BYREF
  std::string v25; // [rsp+E0h] [rbp-30h] BYREF
  char v26; // [rsp+EFh] [rbp-21h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+F0h] [rbp-20h] BYREF
  int8_t IsGetReward; // [rsp+FBh] [rbp-15h]
  int32_t BossId; // [rsp+FCh] [rbp-14h]

  std::allocator<char>::allocator(&v20);
  std::string::string(&delims, "|", &v20);
  Answer::StringUtility::split(&mineString, &dbData->m_BossKilledReward.RewardString, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v20);
  for ( it._M_current = std::vector<std::string>::begin(&mineString)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
  {
    v21._M_current = std::vector<std::string>::end(&mineString)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &v21) )
      break;
    std::allocator<char>::allocator(&v23);
    std::string::string(&v22, ":", &v23);
    v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
    Answer::StringUtility::split(&StringVt, v2, &v22, 0);
    std::string::~string(&v22);
    std::allocator<char>::~allocator(&v23);
    if ( std::vector<std::string>::size(&StringVt) == 3 )
    {
      v3 = std::vector<std::string>::operator[](&StringVt, 0);
      v4 = (const char *)std::string::c_str(v3);
      Type = atoi(v4);
      v5 = std::vector<std::string>::operator[](&StringVt, 1u);
      v6 = (const char *)std::string::c_str(v5);
      IsGetReward = atoi(v6);
      itBoss._M_node = std::map<signed char,BossKilledRewardInfo>::find(&this->m_BossKilledRewardMap, &Type)._M_node;
      __x._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
      if ( std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&itBoss, &__x) )
      {
        v7 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&itBoss);
        v7->second.IsGetReward = IsGetReward;
        std::allocator<char>::allocator(&v26);
        std::string::string(&v25, ",", &v26);
        v8 = std::vector<std::string>::operator[](&StringVt, 2u);
        Answer::StringUtility::split(&BossIdVt, v8, &v25, 0);
        std::string::~string(&v25);
        std::allocator<char>::~allocator(&v26);
        for ( iter._M_current = std::vector<std::string>::begin(&BossIdVt)._M_current;
              ;
              __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&iter, 0) )
        {
          __rhs._M_current = std::vector<std::string>::end(&BossIdVt)._M_current;
          if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&iter, &__rhs) )
            break;
          v9 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&iter);
          v10 = (const char *)std::string::c_str(v9);
          BossId = atoi(v10);
          v11 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&itBoss);
          BossKilledRewardInfo::SetBossKilled(&v11->second, BossId);
        }
        std::vector<std::string>::~vector(&BossIdVt);
      }
    }
    std::vector<std::string>::~vector(&StringVt);
  }
  std::vector<std::string>::~vector(&mineString);
}


#####################################
void __cdecl CBossKilledReward::OnSaveToDB(CBossKilledReward *const this, PlayerDBData *const dbData)
{
  std::_Ios_Openmode v2; // eax
  unsigned int IsGetReward; // ebx
  std::pair<const signed char,BossKilledRewardInfo> *v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v8; // rax
  BossKilledInfo *v9; // rax
  __int64 v10; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v11; // rax
  _BYTE v12[16]; // [rsp+10h] [rbp-1D0h] BYREF
  _BYTE v13[352]; // [rsp+20h] [rbp-1C0h] BYREF
  std::_List_iterator<BossKilledInfo> itBoss; // [rsp+180h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > it; // [rsp+190h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > v16; // [rsp+1A0h] [rbp-40h] BYREF
  std::_List_iterator<BossKilledInfo> __x; // [rsp+1B0h] [rbp-30h] BYREF
  _BYTE v18[32]; // [rsp+1C0h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v12, (unsigned int)v2);
  for ( it._M_node = std::map<signed char,BossKilledRewardInfo>::begin(&this->m_BossKilledRewardMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator++(&it) )
  {
    v16._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&it, &v16) )
      break;
    IsGetReward = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it)->second.IsGetReward;
    v4 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
    v5 = std::ostream::operator<<(v13, (unsigned int)v4->first);
    v6 = std::operator<<<std::char_traits<char>>(v5, ":");
    v7 = std::ostream::operator<<(v6, IsGetReward);
    std::operator<<<std::char_traits<char>>(v7, ":");
    v8 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
    for ( itBoss._M_node = std::list<BossKilledInfo>::begin(&v8->second.BossKeilled)._M_node;
          ;
          std::_List_iterator<BossKilledInfo>::operator++(&itBoss, 0) )
    {
      v11 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
      __x._M_node = std::list<BossKilledInfo>::end(&v11->second.BossKeilled)._M_node;
      if ( !std::_List_iterator<BossKilledInfo>::operator!=(&itBoss, &__x) )
        break;
      if ( std::_List_iterator<BossKilledInfo>::operator->(&itBoss)->IsKilled > 0 )
      {
        v9 = std::_List_iterator<BossKilledInfo>::operator->(&itBoss);
        v10 = std::ostream::operator<<(v13, (unsigned int)v9->BossId);
        std::operator<<<std::char_traits<char>>(v10, ",");
      }
    }
    std::operator<<<std::char_traits<char>>(v13, ":");
    std::operator<<<std::char_traits<char>>(v13, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(v18, v12);
  std::string::operator=(&dbData->m_BossKilledReward.RewardString, v18);
  std::string::~string(v18);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v12);
}


#####################################
void __cdecl CBossKilledReward::GetInterestsProtocol(CBossKilledReward *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 545;
  std::list<unsigned short>::push_back(procList, &__x);
}


#####################################
int32_t __cdecl CBossKilledReward::DispatchNetDatas(
        CBossKilledReward *const this,
        ProcId_t nProcId,
        Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( nProcId == 545 )
    return CBossKilledReward::OnGetBossKilledReward(this, inPacket);
  return 0;
}


#####################################
int32_t __cdecl CBossKilledReward::OnGetBossKilledReward(CBossKilledReward *const this, Answer::NetPacket *inPacket)
{
  std::pair<const signed char,BossKilledRewardInfo> *v3; // rax
  int32_t v4; // ebx
  CfgData *v5; // rax
  MemChrBagVector *p_Rewars; // rbx
  CExtCharBag *Bag; // rax
  int8_t ConnId; // bl
  GameService *v9; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v12; // bl
  GameService *v13; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > it; // [rsp+10h] [rbp-50h] BYREF
  int8_t type; // [rsp+1Fh] [rbp-41h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > __x; // [rsp+20h] [rbp-40h] BYREF
  std::string val; // [rsp+30h] [rbp-30h] BYREF
  BossKilledReward *pCfg; // [rsp+40h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+48h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  type = Answer::NetPacket::readInt32(inPacket);
  it._M_node = std::map<signed char,BossKilledRewardInfo>::find(&this->m_BossKilledRewardMap, &type)._M_node;
  __x._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&it, &__x) )
  {
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
    if ( !BossKilledRewardInfo::CanGetReward(&v3->second) )
      return 10002;
    v4 = type;
    v5 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetBossKilledReward(v5, v4);
    if ( !pCfg )
      return 10002;
    p_Rewars = &pCfg->Rewars;
    Bag = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(Bag, p_Rewars, ITEM_CHANGE_REASON::ICR_GET_BOSS_KILLED_REWARD) )
      return 10002;
    std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it)->second.IsGetReward = 1;
    CBossKilledReward::SendBossKilledInfo(this);
    CBossKilledReward::SendBossKilledIcon(this);
    ConnId = Player::getConnId(this->m_pPlayer);
    v9 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v9, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, 450);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Answer::NetPacket::writeInt8(packet, type);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v13, v12, packet);
    }
  }
  return 10002;
}


#####################################
void __cdecl CBossKilledReward::AddBossKilled(CBossKilledReward *const this, int32_t BossId)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v3; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > __x; // [rsp+20h] [rbp-10h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 190) )
    {
      for ( it._M_node = std::map<signed char,BossKilledRewardInfo>::begin(&this->m_BossKilledRewardMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator++(&it, 0) )
      {
        __x._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&it, &__x) )
          break;
        v3 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
        if ( BossKilledRewardInfo::SetBossKilled(&v3->second, BossId) )
        {
          CBossKilledReward::SendBossKilledInfo(this);
          CBossKilledReward::SendBossKilledIcon(this);
        }
      }
    }
  }
}


#####################################
void __cdecl CBossKilledReward::SendBossKilledInfo(CBossKilledReward *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t v3; // eax
  std::pair<const signed char,BossKilledRewardInfo> *v4; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v5; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v6; // rax
  BossKilledInfo *v7; // rax
  std::pair<const signed char,BossKilledRewardInfo> *v8; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_List_iterator<BossKilledInfo> iter; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > it; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > v15; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<BossKilledInfo> __x; // [rsp+40h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+48h] [rbp-28h]
  int32_t OldWoffset; // [rsp+54h] [rbp-1Ch]
  int32_t Count; // [rsp+58h] [rbp-18h]
  int32_t NewWoffset; // [rsp+5Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x283Eu);
    if ( packet )
    {
      v3 = std::map<signed char,BossKilledRewardInfo>::size(&this->m_BossKilledRewardMap);
      Answer::NetPacket::writeInt32(packet, v3);
      for ( it._M_node = std::map<signed char,BossKilledRewardInfo>::begin(&this->m_BossKilledRewardMap)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator++(&it, 0) )
      {
        v15._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&it, &v15) )
          break;
        v4 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v4->first);
        v5 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
        Answer::NetPacket::writeInt8(packet, v5->second.IsGetReward);
        OldWoffset = Answer::NetPacket::getWOffset(packet);
        Count = 0;
        Answer::NetPacket::writeInt32(packet, 0);
        v6 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
        for ( iter._M_node = std::list<BossKilledInfo>::begin(&v6->second.BossKeilled)._M_node;
              ;
              std::_List_iterator<BossKilledInfo>::operator++(&iter, 0) )
        {
          v8 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
          __x._M_node = std::list<BossKilledInfo>::end(&v8->second.BossKeilled)._M_node;
          if ( !std::_List_iterator<BossKilledInfo>::operator!=(&iter, &__x) )
            break;
          if ( std::_List_iterator<BossKilledInfo>::operator->(&iter)->IsKilled > 0 )
          {
            v7 = std::_List_iterator<BossKilledInfo>::operator->(&iter);
            Answer::NetPacket::writeInt32(packet, v7->BossId);
            ++Count;
          }
        }
        NewWoffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, OldWoffset);
        Answer::NetPacket::writeInt32(packet, Count);
        Answer::NetPacket::setWOffset(packet, NewWoffset);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v11 = Player::getConnId(this->m_pPlayer);
      v12 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v12, v11, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CBossKilledReward::GetBossKilledIcon(CBossKilledReward *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 190) )
    {
      CBossKilledReward::GetBossKilledIcon(&icon, this);
      std::list<ShowIcon>::push_back(IconList, &icon);
    }
  }
}


#####################################
void __cdecl CBossKilledReward::SendBossKilledIcon(CBossKilledReward *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 190) )
    {
      CBossKilledReward::GetBossKilledIcon(&icon, this);
      Player::SendIconState(this->m_pPlayer, &icon);
    }
  }
}


#####################################
bool __cdecl CBossKilledReward::IsAllRewardGet(CBossKilledReward *const this)
{
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > __x; // [rsp+20h] [rbp-10h] BYREF

  for ( iter._M_node = std::map<signed char,BossKilledRewardInfo>::begin(&this->m_BossKilledRewardMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator++(&iter, 0) )
  {
    __x._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&iter)->second.IsGetReward <= 0 )
      return 0;
  }
  return 1;
}


#####################################
int32_t __cdecl CBossKilledReward::CanGetRewardCount(CBossKilledReward *const this)
{
  std::pair<const signed char,BossKilledRewardInfo> *v1; // rax
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,BossKilledRewardInfo> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t Count; // [rsp+2Ch] [rbp-4h]

  Count = 0;
  for ( it._M_node = std::map<signed char,BossKilledRewardInfo>::begin(&this->m_BossKilledRewardMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<signed char,BossKilledRewardInfo>::end(&this->m_BossKilledRewardMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator!=(&it, &__x) )
      break;
    v1 = std::_Rb_tree_iterator<std::pair<signed char const,BossKilledRewardInfo>>::operator->(&it);
    if ( BossKilledRewardInfo::CanGetReward(&v1->second) )
      ++Count;
  }
  return Count;
}


