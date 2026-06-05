// Decompiled methods for class: CWan360
// Source: gameserver.cc
// Total methods: 21

#####################################
void __cdecl CWan360::~CWan360(CWan360 *const this)
{
  CWan360::~CWan360(this);
  operator delete(this);
}


#####################################
void __cdecl CWan360::OnDaySwitch(CWan360 *const this, int32_t nDiffDays)
{
  CWan360::SendSpeed360Icon(this);
  CWan360::SendGameAppIcon(this);
}


#####################################
void __cdecl CWan360::OnUpdate(CWan360 *const this, int64_t curTick)
{
  CfgData *v2; // rax
  Speed360Reward *v3; // rax
  Speed360Reward stu; // [rsp+10h] [rbp-40h] BYREF
  int32_t Now; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer && curTick - this->LastUpdateTiem > 999 )
  {
    this->LastUpdateTiem = curTick;
    Now = Unit::getNow(this->m_pPlayer);
    v2 = Answer::Singleton<CfgData>::instance();
    v3 = CfgData::Get360Reward(v2);
    Speed360Reward::Speed360Reward(&stu, v3);
    if ( stu.StartTime > Now || stu.EndTime < Now )
    {
      if ( this->IsSpeed360Start )
      {
        this->IsSpeed360Start = 0;
        CWan360::SendSpeed360Icon(this);
      }
    }
    else if ( !this->IsSpeed360Start )
    {
      this->IsSpeed360Start = 1;
      CWan360::SendSpeed360Icon(this);
    }
    Speed360Reward::~Speed360Reward(&stu);
  }
}


#####################################
void __cdecl CWan360::OnCleanUp(CWan360 *const this)
{
  this->IsGameAppLogin = 0;
  this->IsSpeed360Start = 0;
  this->m_bSouGouSkinLogin = 0;
  this->LastUpdateTiem = 0;
}


#####################################
void __cdecl CWan360::GetInterestsProtocol(CWan360 *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v3; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v4; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v5; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v6; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 530;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 531;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 532;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 533;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 534;
  std::list<unsigned short>::push_back(procList, &v6);
}


#####################################
int32_t __cdecl CWan360::DispatchNetDatas(CWan360 *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 10002;
  switch ( nProcId )
  {
    case 0x212u:
      result = CWan360::OnGetJiaSuQiuReward(this, inPacket);
      break;
    case 0x213u:
      result = CWan360::OnGetGameAppReward(this, inPacket);
      break;
    case 0x214u:
      result = CWan360::OnLoginFromGameApp(this, inPacket);
      break;
    case 0x215u:
      result = CWan360::OnGetSpeed360Reward(this, inPacket);
      break;
    case 0x216u:
      result = CWan360::OnLoginFromSouGouSkin(this, inPacket);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CWan360::OnGetJiaSuQiuReward(CWan360 *const this, Answer::NetPacket *inPacket)
{
  bool v3; // bl
  CfgData *v4; // rax
  MemChrBagVector *p_Items; // rbx
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  std::string __lhs; // [rsp+10h] [rbp-30h] BYREF
  Wan360Reward *pReward; // [rsp+18h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Player::GetPlatform((const Player *const)&__lhs);
  v3 = std::operator!=<char>(&__lhs, "w360");
  std::string::~string(&__lhs);
  if ( v3 )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 1050) > 0 )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::Get360RewardCfg(v4, 100);
  if ( !pReward )
    return 10002;
  p_Items = &pReward->Items;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_Items, ITEM_CHANGE_REASON::ICR_360_JIA_SU_QIU) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1050, 1);
  CWan360::SendJiaShuQiuIcon(this);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
int32_t __cdecl CWan360::OnGetGameAppReward(CWan360 *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  bool v4; // bl
  int32_t v5; // ebx
  CfgData *v6; // rax
  MemChrBagVector *p_Items; // rbx
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v12; // rax
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  int32_t GetRewardTimes; // [rsp+24h] [rbp-2Ch]
  Wan360Reward *pReward; // [rsp+28h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Player::GetPlatform((const Player *const)&platform);
  v3 = Answer::Singleton<CfgData>::instance();
  v4 = CfgData::Get360RewardIcon(v3, &platform) == 0;
  std::string::~string(&platform);
  if ( v4 )
    return 10002;
  if ( !this->IsGameAppLogin )
    return 10002;
  GetRewardTimes = Player::getRecord(this->m_pPlayer, 1051);
  if ( GetRewardTimes > 6 )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 2028) > 0 )
    return 10002;
  v5 = GetRewardTimes + 1;
  v6 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::Get360RewardCfg(v6, v5);
  if ( !pReward )
    return 10002;
  p_Items = &pReward->Items;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_Items, ITEM_CHANGE_REASON::ICR_360_GAME_APP) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 2028, 1);
  Player::updateRecord(this->m_pPlayer, 1051, GetRewardTimes + 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v12 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v12, ConnId, GateIndex, Proc, 0);
  CWan360::SendGameAppIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CWan360::OnLoginFromGameApp(CWan360 *const this, Answer::NetPacket *inPacket)
{
  CfgData *v2; // rax
  bool v3; // bl
  std::string platform; // [rsp+10h] [rbp-20h] BYREF

  Player::GetPlatform((const Player *const)&platform);
  v2 = Answer::Singleton<CfgData>::instance();
  v3 = CfgData::Get360RewardIcon(v2, &platform) == 0;
  std::string::~string(&platform);
  if ( v3 )
    return 10002;
  this->IsGameAppLogin = 1;
  return 0;
}


#####################################
int32_t __cdecl CWan360::OnLoginFromSouGouSkin(CWan360 *const this, Answer::NetPacket *inPacket)
{
  CfgData *v2; // rax
  MemChrBagVector *p_vReward; // rbx
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  std::string platform; // [rsp+10h] [rbp-30h] BYREF
  const CfgSouGouSkin *pSkin; // [rsp+18h] [rbp-28h]

  Player::GetPlatform((const Player *const)&platform);
  v2 = Answer::Singleton<CfgData>::instance();
  pSkin = CfgData::GetSouGouSkin(v2, &platform);
  std::string::~string(&platform);
  if ( !pSkin )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 1118) )
    return 10002;
  p_vReward = &pSkin->vReward;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_vReward, ITEM_CHANGE_REASON::ICR_SOU_GOU_SKIN_LOGIN) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1118, 1);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, 0);
  CWan360::SendSouGouSkinIcon(this);
  return 0;
}


#####################################
void __cdecl CWan360::SendSouGouSkinIcon(CWan360 *const this)
{
  CfgData *v1; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-20h] BYREF
  const CfgSouGouSkin *pSkin; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v1 = Answer::Singleton<CfgData>::instance();
    pSkin = CfgData::GetSouGouSkin(v1, &platform);
    std::string::~string(&platform);
    if ( pSkin )
    {
      CWan360::GetSouGouSkinIconStu(&stu, this, pSkin->nIcon);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CWan360::GetSouGouSkinIconState(CWan360 *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF
  const CfgSouGouSkin *pSkin; // [rsp+38h] [rbp-18h]

  Player::GetPlatform((const Player *const)&platform);
  v2 = Answer::Singleton<CfgData>::instance();
  pSkin = CfgData::GetSouGouSkin(v2, &platform);
  std::string::~string(&platform);
  if ( pSkin && this->m_pPlayer && !Player::getRecord(this->m_pPlayer, 1118) )
  {
    CWan360::GetSouGouSkinIconStu(&__x, this, pSkin->nIcon);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CWan360::SendGameAppIcon(CWan360 *const this)
{
  CfgData *v1; // rax
  bool v2; // bl
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v1 = Answer::Singleton<CfgData>::instance();
    v2 = CfgData::Get360RewardIcon(v1, &platform) == 0;
    std::string::~string(&platform);
    if ( !v2 )
    {
      CWan360::GetGameAppIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CWan360::GetGameAppIconState(CWan360 *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  bool v3; // bl
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF

  Player::GetPlatform((const Player *const)&platform);
  v2 = Answer::Singleton<CfgData>::instance();
  v3 = CfgData::Get360RewardIcon(v2, &platform) == 0;
  std::string::~string(&platform);
  if ( !v3 && this->m_pPlayer && Player::getRecord(this->m_pPlayer, 2028) <= 6 )
  {
    CWan360::GetGameAppIconStu(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CWan360::SendJiaShuQiuIcon(CWan360 *const this)
{
  char v1; // bl
  bool v2; // al
  bool v3; // r12
  ShowIcon stu; // [rsp+10h] [rbp-50h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-30h] BYREF

  v1 = 0;
  v2 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = 1;
    if ( !std::operator!=<char>(&__lhs, "w360") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    CWan360::GetJiaShuQiuIconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
void __cdecl CWan360::GetJiaShuQiuIconState(CWan360 *const this, IconStateList *const IconList)
{
  bool v2; // bl
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator!=<char>(&__lhs, "w360");
    std::string::~string(&__lhs);
    if ( !v2 && Player::getRecord(this->m_pPlayer, 1050) <= 0 )
    {
      CWan360::GetJiaShuQiuIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CWan360::SendWeiXinIcon(CWan360 *const this)
{
  CfgData *v1; // rax
  const CfgWeiXinTable *WeiXinTable; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v1 = Answer::Singleton<CfgData>::instance();
    WeiXinTable = CfgData::GetWeiXinTable(v1);
    if ( CfgWeiXinTable::GetWeiXinGift(WeiXinTable, &platform) )
    {
      if ( !std::operator==<char>(&platform, "duowanclouds")
        || (PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer),
            CFunctionOpen::IsOpened(PlayerFunctionOpen, 211)) )
      {
        CWan360::GetWeiXinIconStu(&stu, this);
        Player::SendIconState(this->m_pPlayer, &stu);
      }
    }
    std::string::~string(&platform);
  }
}


#####################################
void __cdecl CWan360::GetWeiXinIconState(CWan360 *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  const CfgWeiXinTable *WeiXinTable; // rax
  CFunctionOpen *PlayerFunctionOpen; // rax
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v2 = Answer::Singleton<CfgData>::instance();
    WeiXinTable = CfgData::GetWeiXinTable(v2);
    if ( CfgWeiXinTable::GetWeiXinGift(WeiXinTable, &platform) )
    {
      if ( !std::operator==<char>(&platform, "duowanclouds")
        || (PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer),
            CFunctionOpen::IsOpened(PlayerFunctionOpen, 211)) )
      {
        if ( Player::getRecord(this->m_pPlayer, 1052) <= 0 )
        {
          CWan360::GetWeiXinIconStu(&__x, this);
          std::list<ShowIcon>::push_back(IconList, &__x);
        }
      }
    }
    std::string::~string(&platform);
  }
}


#####################################
int32_t __cdecl CWan360::OnGetSpeed360Reward(CWan360 *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  Speed360Reward *v4; // rax
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v7; // rax
  Speed360Reward stu; // [rsp+10h] [rbp-30h] BYREF

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( !CWan360::InSpeed360Time(this) )
    return 2;
  if ( Player::getRecord(this->m_pPlayer, 2048) > 0 )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  v4 = CfgData::Get360Reward(v3);
  Speed360Reward::Speed360Reward(&stu, v4);
  Bag = Player::GetBag(this->m_pPlayer);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
  if ( FreeSlotCount >= (int)std::vector<MemChrBag>::size(&stu.Rewards) )
  {
    v7 = Player::GetBag(this->m_pPlayer);
    if ( !CExtCharBag::AddItem(v7, &stu.Rewards, ITEM_CHANGE_REASON::ICR_SPEED_360_REWARD) )
    {
      v2 = 2;
    }
    else
    {
      Player::updateRecord(this->m_pPlayer, 2048, 1);
      CWan360::SendSpeed360Icon(this);
      v2 = 0;
    }
  }
  else
  {
    v2 = 2;
  }
  Speed360Reward::~Speed360Reward(&stu);
  return v2;
}


#####################################
void __cdecl CWan360::SendSpeed360Icon(CWan360 *const this)
{
  char v1; // bl
  bool v2; // al
  bool v3; // r12
  ShowIcon stu; // [rsp+10h] [rbp-50h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-30h] BYREF

  v1 = 0;
  v2 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = 1;
    if ( !std::operator!=<char>(&__lhs, "w360") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    CWan360::GetSpeed360IconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
void __cdecl CWan360::GetSpeed360State(CWan360 *const this, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( CWan360::InSpeed360Time(this) )
  {
    CWan360::GetSpeed360IconStu(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


