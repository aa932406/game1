// Decompiled methods for class: CKiaFuRecharge
// Source: gameserver.cc
// Total methods: 24

#####################################
void __cdecl CKiaFuRecharge::Init(CKiaFuRecharge *const this, int32_t line)
{
  CfgData *v2; // rax
  CTimer *v3; // rax
  tm nowTime; // [rsp+10h] [rbp-40h] BYREF

  v2 = Answer::Singleton<CfgData>::instance();
  this->m_nDay = CfgData::getServerDiffDay(v2, SERVER_TYPE::SVT_NORMAL);
  v3 = Answer::Singleton<CTimer>::instance();
  CTimer::GetLocalNow(&nowTime, v3);
  this->m_nMinute = nowTime.tm_min + 60 * nowTime.tm_hour;
  CKiaFuRecharge::initCfgData(this);
}


#####################################
void __cdecl CKiaFuRecharge::OnDaySwitch(CKiaFuRecharge *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  this->m_nDay = CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
  if ( this->m_nDay == this->m_nEndDay )
    CKiaFuRecharge::hideIcon(this, this->m_nIcon);
  if ( this->m_nDay == this->m_vEndDay[3] )
    CKiaFuRecharge::hideIcon(this, this->m_ChouJiangIcon);
}


#####################################
void __cdecl CKiaFuRecharge::OnGetRechargeSumReward(CKiaFuRecharge *const this, Player *player, int32_t nIndex)
{
  int32_t Record; // eax
  std::vector<MemChrBag> *v4; // rbx
  CExtCharBag *Bag; // rax
  int NewRecord; // [rsp+28h] [rbp-18h]
  int RechargeSum; // [rsp+2Ch] [rbp-14h]

  if ( player )
  {
    if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_RECHARGE_SUM)
      && nIndex >= 0
      && this->m_nSize > nIndex )
    {
      Record = Player::getRecord(player, 1042);
      NewRecord = Record | (1 << nIndex);
      if ( NewRecord != Record )
      {
        RechargeSum = Player::getRecord(player, 1041);
        if ( *std::vector<int>::operator[](&this->m_vSumGolds, nIndex) <= RechargeSum )
        {
          v4 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vSumGift, nIndex);
          Bag = Player::GetBag(player);
          if ( CExtCharBag::AddItem(Bag, v4, ITEM_CHANGE_REASON::IDCR_KAI_FU_RECHARGE_SUM) )
          {
            Player::updateRecord(player, 1042, NewRecord);
            CKiaFuRecharge::GongGao(this, 3012, player);
            CKiaFuRecharge::SendIconState(this, player);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CKiaFuRecharge::OnGetChouJiangReward(CKiaFuRecharge *const this, Player *player, int32_t nIndex)
{
  CfgData *v3; // rax
  int32_t Record; // eax
  CExtCharBag *Bag; // rax
  const TreasureHunterCfg *CurCfg; // [rsp+20h] [rbp-20h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( player )
  {
    if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_CHOU_JIANG_TIMES) )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      CurCfg = CfgData::GetTreasureHunterCfg(v3, nIndex);
      if ( CurCfg )
      {
        if ( CurCfg->nType == 1 && Player::getRecord(player, 1047) >= CurCfg->nRequire )
        {
          Record = Player::getRecord(player, 1048);
          NewRecord = Record | (1 << (nIndex - 1));
          if ( NewRecord != Record )
          {
            Bag = Player::GetBag(player);
            if ( CExtCharBag::AddItem(Bag, &CurCfg->Items, ITEM_CHANGE_REASON::IDCR_KAI_FU_CHOU_JIANG) )
            {
              Player::updateRecord(player, 1048, NewRecord);
              CKiaFuRecharge::GongGao(this, 3013, player);
              CKiaFuRecharge::SendChouJiangIconState(this, player);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CKiaFuRecharge::OnGetXiaoFeiReward(CKiaFuRecharge *const this, Player *player, int32_t nIndex)
{
  int32_t Record; // ebx
  int32_t v4; // eax
  std::vector<MemChrBag> *v5; // rbx
  CExtCharBag *Bag; // rax
  int32_t v7; // ecx
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( player
    && CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_XIAO_FEI_SUM)
    && (nIndex >= 0 || this->m_nXiaoFeiSize > nIndex) )
  {
    Record = Player::getRecord(player, 1075);
    if ( Record >= *std::vector<int>::operator[](&this->m_nValues, nIndex) )
    {
      v4 = Player::getRecord(player, 1076);
      NewRecord = v4 | (1 << nIndex);
      if ( NewRecord != v4 )
      {
        v5 = std::vector<std::vector<MemChrBag>>::operator[](&this->m_vXiaoFeiSumGift, nIndex);
        Bag = Player::GetBag(player);
        if ( CExtCharBag::AddItem(Bag, v5, ITEM_CHANGE_REASON::IDCR_KAI_FU_XIAO_FEI_SUM) )
        {
          Player::updateRecord(player, 1076, NewRecord);
          if ( *std::vector<int>::operator[](&this->m_vXiaoFeiGongGaoId, nIndex) > 0 )
          {
            v7 = *std::vector<int>::operator[](&this->m_vXiaoFeiGongGaoId, nIndex);
            CKiaFuRecharge::GongGao(this, v7, player);
          }
          CKiaFuRecharge::SendIconState(this, player);
        }
      }
    }
  }
}


#####################################
void __cdecl CKiaFuRecharge::GetLianRechargeReward(
        CKiaFuRecharge *const this,
        Player *player,
        int32_t nType,
        int32_t nIndex)
{
  int32_t Record; // eax
  LianRechargeCfg *v5; // rax
  std::vector<MemChrBag> *v6; // rbx
  CExtCharBag *Bag; // rax
  int32_t RewardRecord; // [rsp+2Ch] [rbp-24h]
  int32_t LianChongRecord; // [rsp+30h] [rbp-20h]
  int NewRecord; // [rsp+3Ch] [rbp-14h]

  if ( player && CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_LIAN_RECHARGE) )
  {
    if ( nType )
    {
      if ( nType != 1 )
        return;
      RewardRecord = 1046;
      LianChongRecord = 1045;
    }
    else
    {
      RewardRecord = 1044;
      LianChongRecord = 1043;
    }
    if ( nIndex + 1 <= Player::getRecord(player, LianChongRecord) )
    {
      Record = Player::getRecord(player, RewardRecord);
      NewRecord = Record | (1 << nIndex);
      if ( NewRecord != Record )
      {
        v5 = std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, nType);
        v6 = std::vector<std::vector<MemChrBag>>::operator[](&v5->vGiftVector, nIndex);
        Bag = Player::GetBag(player);
        if ( CExtCharBag::AddItem(Bag, v6, ITEM_CHANGE_REASON::IDCR_KAI_FU_RECHARGE_SUM) )
        {
          Player::updateRecord(player, RewardRecord, NewRecord);
          CKiaFuRecharge::GongGao(this, 3012, player);
          CKiaFuRecharge::SendIconState(this, player);
        }
      }
    }
  }
}


#####################################
void __cdecl CKiaFuRecharge::OnXiaoFeiSum(CKiaFuRecharge *const this, Player *player, int32_t AddTimes)
{
  CExtOperateLimit *OperateLimit; // rax
  bool NeedSendIcon; // [rsp+2Fh] [rbp-1h]

  if ( player )
  {
    NeedSendIcon = 0;
    if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_XIAO_FEI_SUM) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1075, AddTimes);
      NeedSendIcon = 1;
    }
    if ( NeedSendIcon )
      CKiaFuRecharge::SendIconState(this, player);
  }
}


#####################################
void __cdecl CKiaFuRecharge::OnRecharge(CKiaFuRecharge *const this, Player *player, int32_t OldValue, int32_t AddValue)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v6; // rax
  CExtOperateLimit *v8; // rax
  bool NeedSendIcon; // [rsp+2Fh] [rbp-11h]

  if ( player )
  {
    NeedSendIcon = 0;
    if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_RECHARGE_SUM) )
    {
      OperateLimit = Player::GetOperateLimit(player);
      CExtOperateLimit::AddLimitCount(OperateLimit, 1041, AddValue);
      NeedSendIcon = 1;
    }
    if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_LIAN_RECHARGE) )
    {
      if ( std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 0)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 0)->nValues )
      {
        v6 = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(v6, 1043, 1);
        NeedSendIcon = 1;
      }
      if ( std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 1u)->nValues > OldValue
        && OldValue + AddValue >= std::vector<LianRechargeCfg>::operator[](&this->m_LianRechargeCfgVt, 1u)->nValues )
      {
        v8 = Player::GetOperateLimit(player);
        CExtOperateLimit::AddLimitCount(v8, 1045, 1);
        NeedSendIcon = 1;
      }
    }
    if ( NeedSendIcon )
      CKiaFuRecharge::SendIconState(this, player);
  }
}


#####################################
void __cdecl CKiaFuRecharge::OnAddChouJiangTimes(CKiaFuRecharge *const this, Player *player, int32_t AddTimes)
{
  CExtOperateLimit *OperateLimit; // rax
  bool NeedSendIcon; // [rsp+2Fh] [rbp-1h]

  NeedSendIcon = 0;
  if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_CHOU_JIANG_TIMES) )
  {
    OperateLimit = Player::GetOperateLimit(player);
    CExtOperateLimit::AddLimitCount(OperateLimit, 1047, AddTimes);
    NeedSendIcon = 1;
  }
  if ( NeedSendIcon )
    CKiaFuRecharge::SendChouJiangIconState(this, player);
}


#####################################
void __cdecl CKiaFuRecharge::SendChouJiangIconState(CKiaFuRecharge *const this, Player *player)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CKiaFuRecharge::needShowShouJinagIcon(this) )
    {
      CKiaFuRecharge::getChouJiangIconState(&icon, this, player);
      Player::SendIconState(player, &icon);
    }
  }
}


#####################################
void __cdecl CKiaFuRecharge::GetChouJiangIconState(
        CKiaFuRecharge *const this,
        Player *player,
        IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CKiaFuRecharge::needShowShouJinagIcon(this) )
    {
      CKiaFuRecharge::getChouJiangIconState(&__x, this, player);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
bool __cdecl CKiaFuRecharge::needShowShouJinagIcon(CKiaFuRecharge *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::getServerStartDayZeroTime(v1, SERVER_TYPE::SVT_NORMAL) <= 1565107199 )
    return 0;
  return this->m_nDay >= this->m_vStartDay[3] && this->m_nDay < this->m_vEndDay[3];
}


#####################################
int32_t __cdecl CKiaFuRecharge::GetChouJiangLeftTime(CKiaFuRecharge *const this)
{
  CTimer *v2; // rax
  int nNowTime; // [rsp+18h] [rbp-8h]

  if ( !CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_CHOU_JIANG_TIMES) )
    return 0;
  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  return 86400 * (this->m_vEndDay[3] - this->m_nDay) - (nNowTime - Answer::DayTime::dayzero(nNowTime));
}


#####################################
bool __cdecl CKiaFuRecharge::IsInTime(CKiaFuRecharge *const this, KAI_FU_RECHARGE_TYPE nType)
{
  CfgData *v2; // rax

  if ( nType == KAI_FU_RECHARGE_TYPE::KFRT_XIAO_FEI_SUM )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getServerStartTime(v2, SERVER_TYPE::SVT_NORMAL) <= 1566316799 )
      return 0;
  }
  return this->m_nDay >= this->m_vStartDay[nType] && this->m_nDay < this->m_vEndDay[nType];
}


#####################################
void __cdecl CKiaFuRecharge::initCfgData(CKiaFuRecharge *const this)
{
  char szCol[64]; // [rsp+10h] [rbp-3E0h] BYREF
  Answer::Inifile ini; // [rsp+50h] [rbp-3A0h] BYREF
  LianRechargeCfg stu; // [rsp+90h] [rbp-360h] BYREF
  std::string file; // [rsp+B0h] [rbp-340h] BYREF
  char v5; // [rsp+BFh] [rbp-331h] BYREF
  std::string key; // [rsp+C0h] [rbp-330h] BYREF
  char v7; // [rsp+CFh] [rbp-321h] BYREF
  std::string section; // [rsp+D0h] [rbp-320h] BYREF
  char v9; // [rsp+DFh] [rbp-311h] BYREF
  std::string v10; // [rsp+E0h] [rbp-310h] BYREF
  char v11; // [rsp+EFh] [rbp-301h] BYREF
  std::string v12; // [rsp+F0h] [rbp-300h] BYREF
  char v13; // [rsp+FFh] [rbp-2F1h] BYREF
  std::string v14; // [rsp+100h] [rbp-2F0h] BYREF
  char v15; // [rsp+10Fh] [rbp-2E1h] BYREF
  std::string v16; // [rsp+110h] [rbp-2E0h] BYREF
  char v17; // [rsp+11Fh] [rbp-2D1h] BYREF
  std::string v18; // [rsp+120h] [rbp-2D0h] BYREF
  char v19; // [rsp+12Fh] [rbp-2C1h] BYREF
  std::string v20; // [rsp+130h] [rbp-2C0h] BYREF
  char v21; // [rsp+13Fh] [rbp-2B1h] BYREF
  std::string v22; // [rsp+140h] [rbp-2B0h] BYREF
  char v23; // [rsp+14Fh] [rbp-2A1h] BYREF
  std::string v24; // [rsp+150h] [rbp-2A0h] BYREF
  char v25; // [rsp+15Bh] [rbp-295h] BYREF
  int __x; // [rsp+15Ch] [rbp-294h] BYREF
  std::string v27; // [rsp+160h] [rbp-290h] BYREF
  char v28; // [rsp+16Fh] [rbp-281h] BYREF
  std::string v29; // [rsp+170h] [rbp-280h] BYREF
  char v30; // [rsp+17Fh] [rbp-271h] BYREF
  MemChrBagVector v31; // [rsp+180h] [rbp-270h] BYREF
  Answer::Inifile v32; // [rsp+1A0h] [rbp-250h] BYREF
  char v33; // [rsp+1DFh] [rbp-211h] BYREF
  std::string v34; // [rsp+1E0h] [rbp-210h] BYREF
  char v35; // [rsp+1EFh] [rbp-201h] BYREF
  std::string v36; // [rsp+1F0h] [rbp-200h] BYREF
  char v37; // [rsp+1FFh] [rbp-1F1h] BYREF
  std::string v38; // [rsp+200h] [rbp-1F0h] BYREF
  char v39; // [rsp+20Fh] [rbp-1E1h] BYREF
  std::string v40; // [rsp+210h] [rbp-1E0h] BYREF
  char v41; // [rsp+21Fh] [rbp-1D1h] BYREF
  std::string v42; // [rsp+220h] [rbp-1D0h] BYREF
  char v43; // [rsp+22Fh] [rbp-1C1h] BYREF
  MemChrBagVector v44; // [rsp+230h] [rbp-1C0h] BYREF
  Answer::Inifile v45; // [rsp+250h] [rbp-1A0h] BYREF
  char v46; // [rsp+28Fh] [rbp-161h] BYREF
  std::string v47; // [rsp+290h] [rbp-160h] BYREF
  char v48; // [rsp+29Fh] [rbp-151h] BYREF
  std::string v49; // [rsp+2A0h] [rbp-150h] BYREF
  char v50; // [rsp+2AFh] [rbp-141h] BYREF
  std::string v51; // [rsp+2B0h] [rbp-140h] BYREF
  char v52; // [rsp+2BFh] [rbp-131h] BYREF
  std::string v53; // [rsp+2C0h] [rbp-130h] BYREF
  char v54; // [rsp+2CFh] [rbp-121h] BYREF
  std::string v55; // [rsp+2D0h] [rbp-120h] BYREF
  char v56; // [rsp+2DFh] [rbp-111h] BYREF
  std::string v57; // [rsp+2E0h] [rbp-110h] BYREF
  char v58; // [rsp+2EFh] [rbp-101h] BYREF
  std::string v59; // [rsp+2F0h] [rbp-100h] BYREF
  char v60; // [rsp+2FFh] [rbp-F1h] BYREF
  std::string v61; // [rsp+300h] [rbp-F0h] BYREF
  char v62; // [rsp+30Fh] [rbp-E1h] BYREF
  std::string v63; // [rsp+310h] [rbp-E0h] BYREF
  char v64; // [rsp+31Fh] [rbp-D1h] BYREF
  std::string v65; // [rsp+320h] [rbp-D0h] BYREF
  char v66; // [rsp+32Fh] [rbp-C1h] BYREF
  std::string v67; // [rsp+330h] [rbp-C0h] BYREF
  char v68; // [rsp+33Bh] [rbp-B5h] BYREF
  int IntValue; // [rsp+33Ch] [rbp-B4h] BYREF
  std::string v70; // [rsp+340h] [rbp-B0h] BYREF
  char v71; // [rsp+34Fh] [rbp-A1h] BYREF
  std::string v72; // [rsp+350h] [rbp-A0h] BYREF
  char v73; // [rsp+35Fh] [rbp-91h] BYREF
  MemChrBagVector v74; // [rsp+360h] [rbp-90h] BYREF
  Answer::Inifile v75; // [rsp+380h] [rbp-70h] BYREF
  char v76; // [rsp+3BFh] [rbp-31h] BYREF
  std::string v77; // [rsp+3C0h] [rbp-30h] BYREF
  char v78; // [rsp+3CFh] [rbp-21h] BYREF
  int32_t i; // [rsp+3D0h] [rbp-20h]
  int32_t i_0; // [rsp+3D4h] [rbp-1Ch]
  int32_t j; // [rsp+3D8h] [rbp-18h]
  int32_t i_1; // [rsp+3DCh] [rbp-14h]

  bzero(this->m_vStartDay, 0x14u);
  bzero(this->m_vEndDay, 0x14u);
  Answer::Inifile::Inifile(&ini);
  std::allocator<char>::allocator(&v5);
  std::string::string(&file, "./ServerConfig/Tables/KaiFuRecharge.cfg");
  Answer::Inifile::parse(&ini, &file);
  std::string::~string(&file);
  std::allocator<char>::~allocator(&v5);
  memset(szCol, 0, sizeof(szCol));
  std::allocator<char>::allocator(&v7);
  std::string::string(&key, "end_day");
  std::allocator<char>::allocator(&v9);
  std::string::string(&section, "CONFIG");
  this->m_nEndDay = Answer::Inifile::getIntValue(&ini, &section, &key);
  std::string::~string(&section);
  std::allocator<char>::~allocator(&v9);
  std::string::~string(&key);
  std::allocator<char>::~allocator(&v7);
  std::allocator<char>::allocator(&v11);
  std::string::string(&v10, "icon");
  std::allocator<char>::allocator(&v13);
  std::string::string(&v12, "CONFIG");
  this->m_nIcon = Answer::Inifile::getIntValue(&ini, &v12, &v10);
  std::string::~string(&v12);
  std::allocator<char>::~allocator(&v13);
  std::string::~string(&v10);
  std::allocator<char>::~allocator(&v11);
  std::allocator<char>::allocator(&v15);
  std::string::string(&v14, "start_day");
  std::allocator<char>::allocator(&v17);
  std::string::string(&v16, "RECHARGE_SUM");
  this->m_vStartDay[1] = Answer::Inifile::getIntValue(&ini, &v16, &v14);
  std::string::~string(&v16);
  std::allocator<char>::~allocator(&v17);
  std::string::~string(&v14);
  std::allocator<char>::~allocator(&v15);
  std::allocator<char>::allocator(&v19);
  std::string::string(&v18, "end_day");
  std::allocator<char>::allocator(&v21);
  std::string::string(&v20, "RECHARGE_SUM");
  this->m_vEndDay[1] = Answer::Inifile::getIntValue(&ini, &v20, &v18);
  std::string::~string(&v20);
  std::allocator<char>::~allocator(&v21);
  std::string::~string(&v18);
  std::allocator<char>::~allocator(&v19);
  std::allocator<char>::allocator(&v23);
  std::string::string(&v22, "size");
  std::allocator<char>::allocator(&v25);
  std::string::string(&v24, "RECHARGE_SUM");
  this->m_nSize = Answer::Inifile::getIntValue(&ini, &v24, &v22);
  std::string::~string(&v24);
  std::allocator<char>::~allocator(&v25);
  std::string::~string(&v22);
  std::allocator<char>::~allocator(&v23);
  for ( i = 0; this->m_nSize > i; ++i )
  {
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "gold%d", i);
    std::allocator<char>::allocator(&v28);
    std::string::string(&v27, szCol);
    std::allocator<char>::allocator(&v30);
    std::string::string(&v29, "RECHARGE_SUM");
    __x = Answer::Inifile::getIntValue(&ini, &v29, &v27);
    std::vector<int>::push_back(&this->m_vSumGolds, &__x);
    std::string::~string(&v29);
    std::allocator<char>::~allocator(&v30);
    std::string::~string(&v27);
    std::allocator<char>::~allocator(&v28);
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "gift%d", i);
    std::allocator<char>::allocator((char *)&v32.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(&v32.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
    std::allocator<char>::allocator((char *)&v32.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::string(&v32.m_strMap._M_t._M_impl._M_header._M_right, "RECHARGE_SUM");
    Answer::Inifile::getStrValue(
      &v32,
      (const std::string *const)&ini,
      (const std::string *const)&v32.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v31, (const std::string *const)&v32);
    std::vector<std::vector<MemChrBag>>::push_back(&this->m_vSumGift, &v31);
    std::vector<MemChrBag>::~vector(&v31);
    std::string::~string(&v32);
    std::string::~string(&v32.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v32.m_strMap._M_t._M_impl._M_node_count + 7);
    std::string::~string(&v32.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v32.m_strMap._M_t._M_impl._M_header._M_left + 7);
  }
  std::allocator<char>::allocator(&v33);
  std::string::string(&v32.m_currentSection, "start_day");
  std::allocator<char>::allocator(&v35);
  std::string::string(&v34, "LIAN_RECHARGE");
  this->m_vStartDay[2] = Answer::Inifile::getIntValue(&ini, &v34, &v32.m_currentSection);
  std::string::~string(&v34);
  std::allocator<char>::~allocator(&v35);
  std::string::~string(&v32.m_currentSection);
  std::allocator<char>::~allocator(&v33);
  std::allocator<char>::allocator(&v37);
  std::string::string(&v36, "end_day");
  std::allocator<char>::allocator(&v39);
  std::string::string(&v38, "LIAN_RECHARGE");
  this->m_vEndDay[2] = Answer::Inifile::getIntValue(&ini, &v38, &v36);
  std::string::~string(&v38);
  std::allocator<char>::~allocator(&v39);
  std::string::~string(&v36);
  std::allocator<char>::~allocator(&v37);
  for ( i_0 = 0; i_0 <= 1; ++i_0 )
  {
    memset(&stu, 0, sizeof(stu));
    std::vector<std::vector<MemChrBag>>::vector(&stu.vGiftVector);
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "type%d", i_0);
    std::allocator<char>::allocator(&v41);
    std::string::string(&v40, szCol);
    std::allocator<char>::allocator(&v43);
    std::string::string(&v42, "LIAN_RECHARGE");
    stu.nValues = Answer::Inifile::getIntValue(&ini, &v42, &v40);
    std::string::~string(&v42);
    std::allocator<char>::~allocator(&v43);
    std::string::~string(&v40);
    std::allocator<char>::~allocator(&v41);
    for ( j = 0; j <= 6; ++j )
    {
      bzero(szCol, 0x40u);
      snprintf(szCol, 0x3Fu, "gift%d_%d", i_0, j);
      std::allocator<char>::allocator((char *)&v45.m_strMap._M_t._M_impl._M_header._M_left + 7);
      std::string::string(&v45.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
      std::allocator<char>::allocator((char *)&v45.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::string(&v45.m_strMap._M_t._M_impl._M_header._M_right, "LIAN_RECHARGE");
      Answer::Inifile::getStrValue(
        &v45,
        (const std::string *const)&ini,
        (const std::string *const)&v45.m_strMap._M_t._M_impl._M_header._M_right);
      CItemHelper::parseItemVectorString(&v44, (const std::string *const)&v45);
      std::vector<std::vector<MemChrBag>>::push_back(&stu.vGiftVector, &v44);
      std::vector<MemChrBag>::~vector(&v44);
      std::string::~string(&v45);
      std::string::~string(&v45.m_strMap._M_t._M_impl._M_header._M_right);
      std::allocator<char>::~allocator((char *)&v45.m_strMap._M_t._M_impl._M_node_count + 7);
      std::string::~string(&v45.m_strMap._M_t._M_impl._M_header._M_parent);
      std::allocator<char>::~allocator((char *)&v45.m_strMap._M_t._M_impl._M_header._M_left + 7);
    }
    std::vector<LianRechargeCfg>::push_back(&this->m_LianRechargeCfgVt, &stu);
    LianRechargeCfg::~LianRechargeCfg(&stu);
  }
  std::allocator<char>::allocator(&v46);
  std::string::string(&v45.m_currentSection, "start_day");
  std::allocator<char>::allocator(&v48);
  std::string::string(&v47, "CHOU_JIANG");
  this->m_vStartDay[3] = Answer::Inifile::getIntValue(&ini, &v47, &v45.m_currentSection);
  std::string::~string(&v47);
  std::allocator<char>::~allocator(&v48);
  std::string::~string(&v45.m_currentSection);
  std::allocator<char>::~allocator(&v46);
  std::allocator<char>::allocator(&v50);
  std::string::string(&v49, "end_day");
  std::allocator<char>::allocator(&v52);
  std::string::string(&v51, "CHOU_JIANG");
  this->m_vEndDay[3] = Answer::Inifile::getIntValue(&ini, &v51, &v49);
  std::string::~string(&v51);
  std::allocator<char>::~allocator(&v52);
  std::string::~string(&v49);
  std::allocator<char>::~allocator(&v50);
  std::allocator<char>::allocator(&v54);
  std::string::string(&v53, "icon");
  std::allocator<char>::allocator(&v56);
  std::string::string(&v55, "CHOU_JIANG");
  this->m_ChouJiangIcon = Answer::Inifile::getIntValue(&ini, &v55, &v53);
  std::string::~string(&v55);
  std::allocator<char>::~allocator(&v56);
  std::string::~string(&v53);
  std::allocator<char>::~allocator(&v54);
  std::allocator<char>::allocator(&v58);
  std::string::string(&v57, "start_day");
  std::allocator<char>::allocator(&v60);
  std::string::string(&v59, "LIAO_FEI_SUM");
  this->m_vStartDay[4] = Answer::Inifile::getIntValue(&ini, &v59, &v57);
  std::string::~string(&v59);
  std::allocator<char>::~allocator(&v60);
  std::string::~string(&v57);
  std::allocator<char>::~allocator(&v58);
  std::allocator<char>::allocator(&v62);
  std::string::string(&v61, "end_day");
  std::allocator<char>::allocator(&v64);
  std::string::string(&v63, "LIAO_FEI_SUM");
  this->m_vEndDay[4] = Answer::Inifile::getIntValue(&ini, &v63, &v61);
  std::string::~string(&v63);
  std::allocator<char>::~allocator(&v64);
  std::string::~string(&v61);
  std::allocator<char>::~allocator(&v62);
  std::allocator<char>::allocator(&v66);
  std::string::string(&v65, "size");
  std::allocator<char>::allocator(&v68);
  std::string::string(&v67, "LIAO_FEI_SUM");
  this->m_nXiaoFeiSize = Answer::Inifile::getIntValue(&ini, &v67, &v65);
  std::string::~string(&v67);
  std::allocator<char>::~allocator(&v68);
  std::string::~string(&v65);
  std::allocator<char>::~allocator(&v66);
  for ( i_1 = 0; this->m_nXiaoFeiSize > i_1; ++i_1 )
  {
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "value%d", i_1 + 1);
    std::allocator<char>::allocator(&v71);
    std::string::string(&v70, szCol);
    std::allocator<char>::allocator(&v73);
    std::string::string(&v72, "LIAO_FEI_SUM");
    IntValue = Answer::Inifile::getIntValue(&ini, &v72, &v70);
    std::vector<int>::push_back(&this->m_nValues, &IntValue);
    std::string::~string(&v72);
    std::allocator<char>::~allocator(&v73);
    std::string::~string(&v70);
    std::allocator<char>::~allocator(&v71);
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "gift%d", i_1 + 1);
    std::allocator<char>::allocator((char *)&v75.m_strMap._M_t._M_impl._M_header._M_left + 7);
    std::string::string(&v75.m_strMap._M_t._M_impl._M_header._M_parent, szCol);
    std::allocator<char>::allocator((char *)&v75.m_strMap._M_t._M_impl._M_node_count + 3);
    std::string::string(&v75.m_strMap._M_t._M_impl._M_header._M_right, "LIAO_FEI_SUM");
    Answer::Inifile::getStrValue(
      &v75,
      (const std::string *const)&ini,
      (const std::string *const)&v75.m_strMap._M_t._M_impl._M_header._M_right);
    CItemHelper::parseItemVectorString(&v74, (const std::string *const)&v75);
    std::vector<std::vector<MemChrBag>>::push_back(&this->m_vXiaoFeiSumGift, &v74);
    std::vector<MemChrBag>::~vector(&v74);
    std::string::~string(&v75);
    std::string::~string(&v75.m_strMap._M_t._M_impl._M_header._M_right);
    std::allocator<char>::~allocator((char *)&v75.m_strMap._M_t._M_impl._M_node_count + 3);
    std::string::~string(&v75.m_strMap._M_t._M_impl._M_header._M_parent);
    std::allocator<char>::~allocator((char *)&v75.m_strMap._M_t._M_impl._M_header._M_left + 7);
    bzero(szCol, 0x40u);
    snprintf(szCol, 0x3Fu, "gonggao%d", i_1 + 1);
    std::allocator<char>::allocator(&v76);
    std::string::string(&v75.m_currentSection, szCol);
    std::allocator<char>::allocator(&v78);
    std::string::string(&v77, "LIAO_FEI_SUM");
    HIDWORD(v75.m_strMap._M_t._M_impl._M_node_count) = Answer::Inifile::getIntValue(&ini, &v77, &v75.m_currentSection);
    std::vector<int>::push_back(
      &this->m_vXiaoFeiGongGaoId,
      (const int *const)&v75.m_strMap._M_t._M_impl._M_node_count + 1);
    std::string::~string(&v77);
    std::allocator<char>::~allocator(&v78);
    std::string::~string(&v75.m_currentSection);
    std::allocator<char>::~allocator(&v76);
  }
  Answer::Inifile::~Inifile(&ini);
}


#####################################
bool __cdecl CKiaFuRecharge::IsInTime(CKiaFuRecharge *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  CfgData::getServerDiffDay(v1, SERVER_TYPE::SVT_NORMAL);
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
void __cdecl CKiaFuRecharge::GetIconState(CKiaFuRecharge *const this, Player *player, IconStateList *const IconList)
{
  ShowIcon __x; // [rsp+20h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CKiaFuRecharge::needShowIcon(this) )
    {
      CKiaFuRecharge::getIconState(&__x, this, player);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CKiaFuRecharge::SendIconState(CKiaFuRecharge *const this, Player *player)
{
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF

  if ( player )
  {
    if ( CKiaFuRecharge::needShowIcon(this) )
    {
      CKiaFuRecharge::getIconState(&icon, this, player);
      Player::SendIconState(player, &icon);
    }
  }
}


#####################################
bool __cdecl CKiaFuRecharge::needShowIcon(CKiaFuRecharge *const this)
{
  CfgData *v1; // rax

  v1 = Answer::Singleton<CfgData>::instance();
  if ( CfgData::getServerStartDayZeroTime(v1, SERVER_TYPE::SVT_NORMAL) <= 1565107199 )
    return 0;
  return this->m_nDay >= 0 && this->m_nDay < this->m_nEndDay;
}


#####################################
void __cdecl CKiaFuRecharge::hideIcon(CKiaFuRecharge *const this, int32_t nIconId)
{
  GameService *v2; // rax
  GameService *v3; // rax
  uint32_t WOffset; // eax
  GameService *v5; // rax
  ShowIcon icon; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-8h]

  v2 = Answer::Singleton<GameService>::instance();
  if ( GameService::getLine(v2) == 1 )
  {
    *(_DWORD *)&icon.nState = 4;
    *(_QWORD *)&icon.nLeftTime = 0;
    *(_QWORD *)&icon.nIconRight = 0;
    icon.nId = nIconId;
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, 0, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
    if ( packet )
    {
      ShowIcon::AppendInfo(&icon, packet);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v5 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v5, 0, packet);
    }
  }
}


#####################################
int32_t __cdecl CKiaFuRecharge::getLeftTime(CKiaFuRecharge *const this)
{
  CTimer *v2; // rax
  int nNowTime; // [rsp+18h] [rbp-8h]

  if ( !CKiaFuRecharge::IsInTime(this) )
    return 0;
  v2 = Answer::Singleton<CTimer>::instance();
  nNowTime = CTimer::GetNow(v2);
  return 86400 * (this->m_nEndDay - this->m_nDay) - (nNowTime - Answer::DayTime::dayzero(nNowTime));
}


#####################################
void __cdecl CKiaFuRecharge::GongGao(CKiaFuRecharge *const this, int32_t GongGaoId, Player *player)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v7; // bl
  GameService *v8; // rax
  std::string val; // [rsp+20h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-18h]

  if ( player )
  {
    ConnId = Player::getConnId(player);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, GongGaoId);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Cid = Player::getCid(player);
      Answer::NetPacket::writeInt64(packet, Cid);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v7 = Player::getConnId(player);
      v8 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v8, v7, packet);
    }
  }
}


#####################################
int32_t __cdecl CKiaFuRecharge::HaveRechargeRewardCount(CKiaFuRecharge *const this, Player *player)
{
  int *v3; // rax
  int *v4; // rax
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it_0; // [rsp+10h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > it; // [rsp+20h] [rbp-80h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > __rhs; // [rsp+30h] [rbp-70h] BYREF
  __gnu_cxx::__normal_iterator<int*,std::vector<int> > v8; // [rsp+40h] [rbp-60h] BYREF
  int32_t Count; // [rsp+4Ch] [rbp-54h]
  int32_t RechargeSum; // [rsp+50h] [rbp-50h]
  int32_t RewardRecord; // [rsp+54h] [rbp-4Ch]
  int32_t i; // [rsp+58h] [rbp-48h]
  int32_t NewRecord; // [rsp+5Ch] [rbp-44h]
  int32_t XiaoFeiSum; // [rsp+60h] [rbp-40h]
  int32_t RewardRecord_0; // [rsp+64h] [rbp-3Ch]
  int32_t i_0; // [rsp+68h] [rbp-38h]
  int32_t NewRecord_0; // [rsp+6Ch] [rbp-34h]
  int32_t ActCount; // [rsp+70h] [rbp-30h]
  int32_t OldRecord; // [rsp+74h] [rbp-2Ch]
  int32_t i_1; // [rsp+78h] [rbp-28h]
  int32_t NewRecord_1; // [rsp+7Ch] [rbp-24h]
  int32_t ActCount_0; // [rsp+80h] [rbp-20h]
  int32_t OldRecord_0; // [rsp+84h] [rbp-1Ch]
  int32_t i_2; // [rsp+88h] [rbp-18h]
  int32_t NewRecord_2; // [rsp+8Ch] [rbp-14h]

  if ( !player )
    return 0;
  Count = 0;
  if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_RECHARGE_SUM) )
  {
    RechargeSum = Player::getRecord(player, 1041);
    RewardRecord = Player::getRecord(player, 1042);
    it._M_current = std::vector<int>::begin(&this->m_vSumGolds)._M_current;
    i = 0;
    while ( 1 )
    {
      __rhs._M_current = std::vector<int>::end(&this->m_vSumGolds)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it, &__rhs) )
        break;
      v3 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it);
      if ( *v3 <= RechargeSum )
      {
        NewRecord = RewardRecord | (1 << i);
        if ( NewRecord != RewardRecord )
          ++Count;
      }
      ++i;
      __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it, 0);
    }
  }
  if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_XIAO_FEI_SUM) )
  {
    XiaoFeiSum = Player::getRecord(player, 1075);
    RewardRecord_0 = Player::getRecord(player, 1076);
    it_0._M_current = std::vector<int>::begin(&this->m_nValues)._M_current;
    i_0 = 0;
    while ( 1 )
    {
      v8._M_current = std::vector<int>::end(&this->m_nValues)._M_current;
      if ( !__gnu_cxx::operator!=<int *,std::vector<int>>(&it_0, &v8) )
        break;
      v4 = __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator*(&it_0);
      if ( *v4 <= XiaoFeiSum )
      {
        NewRecord_0 = RewardRecord_0 | (1 << i_0);
        if ( NewRecord_0 != RewardRecord_0 )
          ++Count;
      }
      ++i_0;
      __gnu_cxx::__normal_iterator<int *,std::vector<int>>::operator++(&it_0, 0);
    }
  }
  if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_LIAN_RECHARGE) )
  {
    ActCount = Player::getRecord(player, 1043);
    OldRecord = Player::getRecord(player, 1044);
    for ( i_1 = 0; i_1 < ActCount; ++i_1 )
    {
      NewRecord_1 = OldRecord | (1 << i_1);
      if ( NewRecord_1 != OldRecord )
        ++Count;
    }
    ActCount_0 = Player::getRecord(player, 1045);
    OldRecord_0 = Player::getRecord(player, 1046);
    for ( i_2 = 0; i_2 < ActCount_0; ++i_2 )
    {
      NewRecord_2 = OldRecord_0 | (1 << i_2);
      if ( NewRecord_2 != OldRecord_0 )
        ++Count;
    }
  }
  return Count;
}


#####################################
int32_t __cdecl CKiaFuRecharge::HaveChouJiangCount(CKiaFuRecharge *const this, Player *player)
{
  CfgData *v3; // rax
  const TreasureHunterCfgMap *TreasureHunterCfgMap; // rax
  const std::pair<const int,TreasureHunterCfg> *v5; // rax
  const std::pair<const int,TreasureHunterCfg> *v7; // rax
  TreasureHunterCfgMap TreasureHunter; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,TreasureHunterCfg> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,TreasureHunterCfg> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t Count; // [rsp+60h] [rbp-20h]
  int32_t ChouJiangTimes; // [rsp+64h] [rbp-1Ch]
  int32_t RewardRecord; // [rsp+68h] [rbp-18h]
  int32_t NewRecord; // [rsp+6Ch] [rbp-14h]

  if ( !player )
    return 0;
  Count = 0;
  if ( CKiaFuRecharge::IsInTime(this, KAI_FU_RECHARGE_TYPE::KFRT_CHOU_JIANG_TIMES) )
  {
    ChouJiangTimes = Player::getRecord(player, 1047);
    RewardRecord = Player::getRecord(player, 1048);
    v3 = Answer::Singleton<CfgData>::instance();
    TreasureHunterCfgMap = CfgData::GetTreasureHunterCfgMap(v3);
    std::map<int,TreasureHunterCfg>::map(&TreasureHunter, TreasureHunterCfgMap);
    for ( it._M_node = std::map<int,TreasureHunterCfg>::begin(&TreasureHunter)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator++(&it, 0) )
    {
      __x._M_node = std::map<int,TreasureHunterCfg>::end(&TreasureHunter)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator!=(&it, &__x) )
        break;
      v5 = std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator->(&it);
      if ( v5->second.nRequire <= ChouJiangTimes
        && std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator->(&it)->second.nType == 1 )
      {
        v7 = std::_Rb_tree_const_iterator<std::pair<int const,TreasureHunterCfg>>::operator->(&it);
        NewRecord = RewardRecord | (1 << (LOBYTE(v7->first) - 1));
        if ( NewRecord != RewardRecord )
          ++Count;
      }
    }
    std::map<int,TreasureHunterCfg>::~map(&TreasureHunter);
  }
  return Count;
}


