// Decompiled methods for class: CNationalDayHd
// Source: gameserver.cc
// Total methods: 17

#####################################
void __cdecl CNationalDayHd::~CNationalDayHd(CNationalDayHd *const this)
{
  CNationalDayHd::~CNationalDayHd(this);
  operator delete(this);
}


#####################################
void __cdecl CNationalDayHd::OnCleanUp(CNationalDayHd *const this)
{
  this->m_Level = 0;
  this->m_Exp = 0;
  this->m_UnLockReward = 0;
  this->m_OrdinaryReward = 0;
  this->m_SeniorReward = 0;
  std::map<int,Param2>::clear(&this->m_NationalInfo);
}


#####################################
void __cdecl CNationalDayHd::OnLoadFromDB(CNationalDayHd *const this, const PlayerDBData *const dbData)
{
  std::string p_NationalInfo; // [rsp+10h] [rbp-20h] BYREF

  this->m_Level = dbData->m_NationalDayData.m_Level;
  this->m_Exp = dbData->m_NationalDayData.m_Exp;
  this->m_UnLockReward = dbData->m_NationalDayData.m_UnLockReward;
  this->m_OrdinaryReward = dbData->m_NationalDayData.m_OrdinaryReward;
  this->m_SeniorReward = dbData->m_NationalDayData.m_SeniorReward;
  std::string::string(&p_NationalInfo, &dbData->m_NationalDayData.m_NationalInfo);
  CNationalDayHd::paraseNational(this, &p_NationalInfo);
  std::string::~string(&p_NationalInfo);
}


#####################################
void __cdecl CNationalDayHd::OnSaveToDB(CNationalDayHd *const this, PlayerDBData *const dbData)
{
  _BYTE v2[32]; // [rsp+10h] [rbp-20h] BYREF

  dbData->m_NationalDayData.m_Level = this->m_Level;
  dbData->m_NationalDayData.m_Exp = this->m_Exp;
  dbData->m_NationalDayData.m_UnLockReward = this->m_UnLockReward;
  dbData->m_NationalDayData.m_OrdinaryReward = this->m_OrdinaryReward;
  dbData->m_NationalDayData.m_SeniorReward = this->m_SeniorReward;
  CNationalDayHd::SaveNationalInfo((CNationalDayHd *const)v2);
  std::string::operator=(&dbData->m_NationalDayData.m_NationalInfo, v2);
  std::string::~string(v2);
}


#####################################
void __cdecl CNationalDayHd::paraseNational(CNationalDayHd *const this, std::string *p_NationalInfo)
{
  std::string *v2; // rax
  std::string *v3; // rax
  const char *v4; // rax
  std::string *v5; // rax
  const char *v6; // rax
  std::string *v7; // rax
  const char *v8; // rax
  Param2 *v9; // rax
  Param2 stu; // [rsp+10h] [rbp-A0h] BYREF
  int32_t i; // [rsp+1Ch] [rbp-94h] BYREF
  StringVector TaskInfo; // [rsp+20h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > it; // [rsp+40h] [rbp-70h] BYREF
  StringVector items_receive; // [rsp+50h] [rbp-60h] BYREF
  std::string delims; // [rsp+70h] [rbp-40h] BYREF
  char v16; // [rsp+7Fh] [rbp-31h] BYREF
  __gnu_cxx::__normal_iterator<std::string*,std::vector<std::string> > __rhs; // [rsp+80h] [rbp-30h] BYREF
  std::string v18; // [rsp+90h] [rbp-20h] BYREF
  _BYTE v19[17]; // [rsp+9Fh] [rbp-11h] BYREF

  std::allocator<char>::allocator(&v16);
  std::string::string(&delims, "|");
  Answer::StringUtility::split(&items_receive, p_NationalInfo, &delims, 0);
  std::string::~string(&delims);
  std::allocator<char>::~allocator(&v16);
  for ( it._M_current = std::vector<std::string>::begin(&items_receive)._M_current;
        ;
        __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator++(&it) )
  {
    __rhs._M_current = std::vector<std::string>::end(&items_receive)._M_current;
    if ( !__gnu_cxx::operator!=<std::string *,std::vector<std::string>>(&it, &__rhs) )
      break;
    std::allocator<char>::allocator(v19);
    std::string::string(&v18, ":");
    v2 = __gnu_cxx::__normal_iterator<std::string *,std::vector<std::string>>::operator*(&it);
    Answer::StringUtility::split(&TaskInfo, v2, &v18, 0);
    std::string::~string(&v18);
    std::allocator<char>::~allocator(v19);
    if ( std::vector<std::string>::size(&TaskInfo) == 3 )
    {
      v3 = std::vector<std::string>::operator[](&TaskInfo, 0);
      v4 = (const char *)std::string::c_str(v3);
      i = atoi(v4);
      Param2::Param2(&stu, 0, 0);
      v5 = std::vector<std::string>::operator[](&TaskInfo, 1u);
      v6 = (const char *)std::string::c_str(v5);
      stu.nParam1 = atoi(v6);
      v7 = std::vector<std::string>::operator[](&TaskInfo, 2u);
      v8 = (const char *)std::string::c_str(v7);
      stu.nParam2 = atoi(v8);
      v9 = std::map<int,Param2>::operator[](&this->m_NationalInfo, &i);
      *v9 = stu;
    }
    std::vector<std::string>::~vector(&TaskInfo);
  }
  std::vector<std::string>::~vector(&items_receive);
}


#####################################
std::string __cdecl CNationalDayHd::SaveNationalInfo(CNationalDayHd *const this)
{
  __int64 v1; // rsi
  std::_Ios_Openmode v2; // eax
  std::pair<const int,Param2> *v3; // rax
  __int64 v4; // rax
  std::pair<const int,Param2> *v5; // rax
  __int64 v6; // rax
  std::pair<const int,Param2> *v7; // rax
  __int64 v8; // rax
  _BYTE v10[16]; // [rsp+10h] [rbp-1A0h] BYREF
  _BYTE v11[352]; // [rsp+20h] [rbp-190h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Param2> > it; // [rsp+180h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Param2> > __x; // [rsp+190h] [rbp-20h] BYREF

  v2 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_in);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::basic_stringstream(v10, (unsigned int)v2);
  std::map<int,Param2>::begin((std::map<int,Param2> *const)(v1 + 40));
  for ( it._M_node = std::map<int,Param2>::begin((std::map<int,Param2> *const)(v1 + 40))._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,Param2>::end((std::map<int,Param2> *const)(v1 + 40))._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it);
    v4 = std::ostream::operator<<(v11, (unsigned int)v3->first);
    std::operator<<<std::char_traits<char>>(v4, ":");
    v5 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it);
    v6 = std::ostream::operator<<(v11, (unsigned int)v5->second.nParam1);
    std::operator<<<std::char_traits<char>>(v6, ":");
    v7 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it);
    v8 = std::ostream::operator<<(v11, (unsigned int)v7->second.nParam2);
    std::operator<<<std::char_traits<char>>(v8, ":");
    std::operator<<<std::char_traits<char>>(v11, "|");
  }
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::str(this, v10);
  std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::~basic_stringstream(v10);
  return (std::string)this;
}


#####################################
bool __cdecl CNationalDayHd::GetNationalExp(CNationalDayHd *const this, int32_t nType, int32_t nId)
{
  int32_t v4; // ebx
  CfgData *v5; // rax
  std::pair<const int,Param2> *v6; // rax
  std::pair<const int,Param2> *v7; // rax
  int32_t nTypea; // [rsp+4h] [rbp-3Ch] BYREF
  CNationalDayHd *thisa; // [rsp+8h] [rbp-38h]
  std::_Rb_tree_iterator<std::pair<const int,Param2> > it; // [rsp+10h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Param2> > __x; // [rsp+20h] [rbp-20h] BYREF
  const NationalDayTaskCfg *pCfg; // [rsp+28h] [rbp-18h]

  thisa = this;
  nTypea = nType;
  if ( !this->m_pPlayer )
    return 0;
  it._M_node = std::map<int,Param2>::find(&thisa->m_NationalInfo, &nTypea)._M_node;
  __x._M_node = std::map<int,Param2>::end(&thisa->m_NationalInfo)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator==(&it, &__x) )
    return 0;
  v4 = nTypea;
  v5 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetNationalDayTaskCfg(v5, v4, nId);
  if ( !pCfg )
    return 0;
  v6 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it);
  if ( v6->second.nParam1 < pCfg->nNeedValue )
    return 0;
  if ( std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it)->second.nParam2 >= nId )
    return 0;
  v7 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it);
  ++v7->second.nParam2;
  CNationalDayHd::AddExp(thisa, pCfg->nSocre);
  return 1;
}


#####################################
bool __cdecl CNationalDayHd::UnLockHighReward(CNationalDayHd *const this)
{
  CfgData *v2; // rax
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v6; // rax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  const NationalDayLevelCfg *pCfg; // [rsp+20h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  if ( this->m_UnLockReward > 0 )
    return 0;
  v2 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetNationalDayLevelCfg(v2, 0);
  if ( !pCfg || pCfg->nUnlockCost <= 0 )
    return 0;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          pCfg->nUnlockCost,
          CURRENCY_CHANGE_REASON::GCT_NATIONAL_UNLOCK_REWARD,
          0) )
    return 0;
  this->m_UnLockReward = 1;
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( !packet )
    return 0;
  Answer::NetPacket::writeInt32(packet, 3023);
  Cid = Player::getCid(this->m_pPlayer);
  Answer::NetPacket::writeInt64(packet, Cid);
  Player::getName((const Player *const)&val);
  Answer::NetPacket::writeUTF8(packet, &val);
  std::string::~string(&val);
  WOffset = Answer::NetPacket::getWOffset(packet);
  Answer::NetPacket::setSize(packet, WOffset);
  v6 = Answer::Singleton<GameService>::instance();
  GameService::worldBroadcast(v6, packet);
  return 1;
}


#####################################
bool __cdecl CNationalDayHd::GetSeniorReward(CNationalDayHd *const this, int32_t nLevel)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  GameService *v5; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v8; // rax
  std::string val; // [rsp+10h] [rbp-30h] BYREF
  const NationalDayLevelCfg *pCfg; // [rsp+18h] [rbp-28h]
  int32_t nNewRecord; // [rsp+24h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  if ( this->m_Level < nLevel )
    return 0;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetNationalDayLevelCfg(v3, nLevel);
  if ( !pCfg )
    return 0;
  if ( pCfg->vSeniorReward.itemId <= 0 || pCfg->vSeniorReward.itemClass <= 0 )
    return 0;
  nNewRecord = this->m_SeniorReward | (1 << nLevel);
  if ( this->m_SeniorReward == nNewRecord )
    return 0;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vSeniorReward, ITEM_CHANGE_REASON::IDCR_GET_NATIONAL_REWARD) )
    return 0;
  this->m_SeniorReward = nNewRecord;
  if ( pCfg->nGongGaoId > 0 )
  {
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( !packet )
      return 0;
    Answer::NetPacket::writeInt32(packet, pCfg->nGongGaoId);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Answer::NetPacket::writeInt32(packet, pCfg->vSeniorReward.itemId);
    Answer::NetPacket::writeInt8(packet, pCfg->vSeniorReward.itemClass);
    Answer::NetPacket::writeInt32(packet, pCfg->vSeniorReward.itemCount);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v8 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v8, packet);
  }
  return 1;
}


#####################################
bool __cdecl CNationalDayHd::GetOrdinaryReward(CNationalDayHd *const this, int32_t nLevel)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  const NationalDayLevelCfg *pCfg; // [rsp+10h] [rbp-20h]
  int nNewRecord; // [rsp+1Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  if ( this->m_Level < nLevel )
    return 0;
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetNationalDayLevelCfg(v3, nLevel);
  if ( !pCfg )
    return 0;
  if ( std::vector<MemChrBag>::empty(&pCfg->vGeneralReward) )
    return 0;
  nNewRecord = this->m_OrdinaryReward | (1 << nLevel);
  if ( this->m_OrdinaryReward == nNewRecord )
    return 0;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vGeneralReward, ITEM_CHANGE_REASON::IDCR_GET_NATIONAL_REWARD) )
    return 0;
  this->m_OrdinaryReward = nNewRecord;
  return 1;
}


#####################################
bool __cdecl CNationalDayHd::BuyLevel(CNationalDayHd *const this, int32_t BuyLv)
{
  int32_t m_Level; // ebx
  CfgData *v4; // rax
  CfgData *v5; // rax
  const NationalDayLevelCfg *pCfg; // [rsp+18h] [rbp-28h]
  const NationalDayLevelCfg *pBuyCfg; // [rsp+20h] [rbp-20h]
  int32_t diffCost; // [rsp+2Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  if ( this->m_Level >= BuyLv )
    return 0;
  m_Level = this->m_Level;
  v4 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetNationalDayLevelCfg(v4, m_Level);
  v5 = Answer::Singleton<CfgData>::instance();
  pBuyCfg = CfgData::GetNationalDayLevelCfg(v5, BuyLv);
  if ( !pCfg || !pBuyCfg )
    return 0;
  if ( pBuyCfg->nBuyCost <= pCfg->nBuyCost )
    return 0;
  if ( pBuyCfg->nBuyCost <= 0 )
    return 0;
  diffCost = pBuyCfg->nBuyCost - pCfg->nBuyCost;
  if ( diffCost <= 0 )
    return 0;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          diffCost,
          CURRENCY_CHANGE_REASON::GCR_NATIONAL_BUY_LEVEL,
          0) )
    return 0;
  this->m_Level = BuyLv;
  return 1;
}


#####################################
void __cdecl CNationalDayHd::AddNationalValue(
        CNationalDayHd *const this,
        NATIONAL_HD_TYPE nType,
        int32_t ParamValue1,
        int32_t ParamValue2)
{
  COpenBeta *v4; // rax
  Param2 *v5; // rax
  CfgData *v6; // rax
  Param2 *v7; // rax
  CfgData *v8; // rax
  Param2 *v9; // rax
  CfgData *v10; // rax
  Param2 *v11; // rax
  Player *m_pPlayer; // rbx
  COpenBeta *v13; // rax
  int __k; // [rsp+20h] [rbp-40h] BYREF
  int v17; // [rsp+24h] [rbp-3Ch] BYREF
  int v18; // [rsp+28h] [rbp-38h] BYREF
  int v19; // [rsp+2Ch] [rbp-34h] BYREF
  int32_t OldCount; // [rsp+30h] [rbp-30h]
  int32_t NewCount; // [rsp+34h] [rbp-2Ch]
  const NationalDayTaskCfg *pCfg; // [rsp+38h] [rbp-28h]
  const NationalDayTaskCfg *pCfg_0; // [rsp+40h] [rbp-20h]
  const NationalDayTaskCfg *pCfg_1; // [rsp+48h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    v4 = Answer::Singleton<COpenBeta>::instance();
    if ( COpenBeta::IsInTime(v4, 16) )
    {
      OldCount = CNationalDayHd::CanGetCount(this);
      switch ( nType )
      {
        case NATIONAL_HD_TYPE::HHT_LOGIN:
        case NATIONAL_HD_TYPE::HHT_CBT:
        case NATIONAL_HD_TYPE::HHT_CHOU_JIANG:
        case NATIONAL_HD_TYPE::HHT_LUN_HUI_TA:
        case NATIONAL_HD_TYPE::HHT_COST_GOLD:
          __k = nType;
          v5 = std::map<int,Param2>::operator[](&this->m_NationalInfo, &__k);
          v5->nParam1 += ParamValue1;
          break;
        case NATIONAL_HD_TYPE::HHT_RECHARGE:
          v6 = Answer::Singleton<CfgData>::instance();
          pCfg = CfgData::GetNationalDayTaskCfg(v6, nType, 1);
          if ( pCfg && pCfg->nParam > ParamValue1 && pCfg->nParam <= ParamValue2 )
          {
            v17 = nType;
            v7 = std::map<int,Param2>::operator[](&this->m_NationalInfo, &v17);
            ++v7->nParam1;
          }
          break;
        case NATIONAL_HD_TYPE::HHT_YJSK:
          v10 = Answer::Singleton<CfgData>::instance();
          pCfg_1 = CfgData::GetNationalDayTaskCfg(v10, nType, 1);
          if ( pCfg_1 && pCfg_1->nParam == ParamValue2 )
          {
            v19 = nType;
            v11 = std::map<int,Param2>::operator[](&this->m_NationalInfo, &v19);
            v11->nParam1 += ParamValue1;
          }
          break;
        case NATIONAL_HD_TYPE::HHT_KILL_BOSS:
          v8 = Answer::Singleton<CfgData>::instance();
          pCfg_0 = CfgData::GetNationalDayTaskCfg(v8, nType, 1);
          if ( pCfg_0 && pCfg_0->nParam <= ParamValue2 )
          {
            v18 = nType;
            v9 = std::map<int,Param2>::operator[](&this->m_NationalInfo, &v18);
            ++v9->nParam1;
          }
          break;
        default:
          break;
      }
      NewCount = CNationalDayHd::CanGetCount(this);
      if ( NewCount != OldCount )
      {
        m_pPlayer = this->m_pPlayer;
        v13 = Answer::Singleton<COpenBeta>::instance();
        COpenBeta::SendIconState(v13, m_pPlayer);
      }
    }
  }
}


#####################################
void __cdecl CNationalDayHd::AddExp(CNationalDayHd *const this, int32_t AddExp)
{
  this->m_Exp += AddExp;
  CNationalDayHd::CheckLevelUp(this);
  CNationalDayHd::SendLevelInfo(this);
}


#####################################
void __cdecl CNationalDayHd::CheckLevelUp(CNationalDayHd *const this)
{
  int32_t m_Level; // ebx
  CfgData *v2; // rax
  const NationalDayLevelCfg *pCfg; // [rsp+18h] [rbp-18h]

  while ( 1 )
  {
    m_Level = this->m_Level;
    v2 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetNationalDayLevelCfg(v2, m_Level);
    if ( !pCfg || pCfg->nScore <= 0 || this->m_Exp < pCfg->nScore )
      break;
    ++this->m_Level;
    this->m_Exp -= pCfg->nScore;
  }
}


#####################################
void __cdecl CNationalDayHd::SendLevelInfo(CNationalDayHd *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2844u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_Level);
      Answer::NetPacket::writeInt32(packet, this->m_Exp);
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
void __cdecl CNationalDayHd::PackHdInfo(CNationalDayHd *const this, Answer::NetPacket *packet)
{
  int first; // edx
  int32_t nParam1; // edx
  int32_t nParam2; // edx
  std::_Rb_tree_iterator<std::pair<const int,Param2> > it; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Param2> > __x; // [rsp+20h] [rbp-10h] BYREF
  int32_t nSize; // [rsp+2Ch] [rbp-4h]

  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_Level);
    Answer::NetPacket::writeInt32(packet, this->m_Exp);
    Answer::NetPacket::writeInt32(packet, this->m_UnLockReward);
    Answer::NetPacket::writeInt32(packet, this->m_OrdinaryReward);
    Answer::NetPacket::writeInt32(packet, this->m_SeniorReward);
    nSize = std::map<int,Param2>::size(&this->m_NationalInfo);
    Answer::NetPacket::writeInt32(packet, nSize);
    for ( it._M_node = std::map<int,Param2>::begin(&this->m_NationalInfo)._M_node;
          ;
          std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,Param2>::end(&this->m_NationalInfo)._M_node;
      if ( !std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator!=(&it, &__x) )
        break;
      first = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it)->first;
      Answer::NetPacket::writeInt32(packet, first);
      nParam1 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it)->second.nParam1;
      Answer::NetPacket::writeInt32(packet, nParam1);
      nParam2 = std::_Rb_tree_iterator<std::pair<int const,Param2>>::operator->(&it)->second.nParam2;
      Answer::NetPacket::writeInt32(packet, nParam2);
    }
  }
}


#####################################
int32_t __cdecl CNationalDayHd::CanGetCount(CNationalDayHd *const this)
{
  CfgData *v1; // rax
  const NationalDayTaskCfgMap *NationalDayTaskCfgMap; // rax
  int32_t v3; // ebx
  const std::pair<const std::pair<int,int>,NationalDayTaskCfg> *v4; // rax
  int32_t v5; // ebx
  const std::pair<const std::pair<int,int>,NationalDayTaskCfg> *v6; // rax
  CfgData *v7; // rax
  const NationalDayLevelCfgMap *NationalDayLevelCfgMap; // rax
  int32_t m_OrdinaryReward; // ebx
  const std::pair<const int,NationalDayLevelCfg> *v10; // rax
  int32_t m_SeniorReward; // ebx
  NationalDayTaskCfgMap TmpMap; // [rsp+10h] [rbp-B0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,NationalDayLevelCfg> > it_0; // [rsp+40h] [rbp-80h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,NationalDayTaskCfg> > it; // [rsp+50h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const std::pair<int,int>,NationalDayTaskCfg> > __x; // [rsp+60h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,NationalDayLevelCfg> > __it; // [rsp+70h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,NationalDayLevelCfg> > v20; // [rsp+80h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,NationalDayLevelCfg> > v21; // [rsp+90h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+A4h] [rbp-1Ch]
  int32_t nNewRecord; // [rsp+A8h] [rbp-18h]
  int32_t nNewRecord_0; // [rsp+ACh] [rbp-14h]

  nCount = 0;
  v1 = Answer::Singleton<CfgData>::instance();
  NationalDayTaskCfgMap = CfgData::GetNationalDayTaskCfgMap(v1);
  std::map<std::pair<int,int>,NationalDayTaskCfg>::map(&TmpMap, NationalDayTaskCfgMap);
  for ( it._M_node = std::map<std::pair<int,int>,NationalDayTaskCfg>::begin(&TmpMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,NationalDayTaskCfg>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<std::pair<int,int>,NationalDayTaskCfg>::end(&TmpMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,NationalDayTaskCfg>>::operator!=(&it, &__x) )
      break;
    v3 = *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,NationalDayTaskCfg>>::operator->(&it)
         + 3);
    v4 = std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,NationalDayTaskCfg>>::operator->(&it);
    if ( v3 > std::map<int,Param2>::operator[](&this->m_NationalInfo, (const int *const)v4 + 2)->nParam2 )
    {
      v5 = *((_DWORD *)std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,NationalDayTaskCfg>>::operator->(&it)
           + 5);
      v6 = std::_Rb_tree_const_iterator<std::pair<std::pair const<int,int>,NationalDayTaskCfg>>::operator->(&it);
      if ( v5 <= std::map<int,Param2>::operator[](&this->m_NationalInfo, (const int *const)v6 + 2)->nParam1 )
        ++nCount;
    }
  }
  std::map<std::pair<int,int>,NationalDayTaskCfg>::~map(&TmpMap);
  v7 = Answer::Singleton<CfgData>::instance();
  NationalDayLevelCfgMap = CfgData::GetNationalDayLevelCfgMap(v7);
  std::map<int,NationalDayLevelCfg>::map((std::map<int,NationalDayLevelCfg> *const)&TmpMap, NationalDayLevelCfgMap);
  __it._M_node = std::map<int,NationalDayLevelCfg>::begin((std::map<int,NationalDayLevelCfg> *const)&TmpMap)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::_Rb_tree_const_iterator(&it_0, &__it);
  while ( 1 )
  {
    v21._M_node = std::map<int,NationalDayLevelCfg>::end((std::map<int,NationalDayLevelCfg> *const)&TmpMap)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::_Rb_tree_const_iterator(&v20, &v21);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator!=(&it_0, &v20) )
      break;
    m_OrdinaryReward = this->m_OrdinaryReward;
    nNewRecord = m_OrdinaryReward
               | (1 << std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator->(&it_0)->second.nLevel);
    if ( this->m_OrdinaryReward != nNewRecord
      && std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator->(&it_0)->second.nLevel <= this->m_Level )
    {
      v10 = std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator->(&it_0);
      if ( !std::vector<MemChrBag>::empty(&v10->second.vGeneralReward) )
        ++nCount;
    }
    if ( this->m_UnLockReward > 0 )
    {
      m_SeniorReward = this->m_SeniorReward;
      nNewRecord_0 = m_SeniorReward
                   | (1 << std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator->(&it_0)->second.nLevel);
      if ( this->m_SeniorReward != nNewRecord_0
        && std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator->(&it_0)->second.nLevel <= this->m_Level
        && std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator->(&it_0)->second.vSeniorReward.itemId > 0 )
      {
        ++nCount;
      }
    }
    std::_Rb_tree_const_iterator<std::pair<int const,NationalDayLevelCfg>>::operator++(&it_0, 0);
  }
  std::map<int,NationalDayLevelCfg>::~map((std::map<int,NationalDayLevelCfg> *const)&TmpMap);
  return nCount;
}


