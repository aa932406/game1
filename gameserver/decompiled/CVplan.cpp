// Decompiled methods for class: CVplan
// Source: gameserver.cc
// Total methods: 59

#####################################
void __cdecl CVplan::~CVplan(CVplan *const this)
{
  CVplan::~CVplan(this);
  operator delete(this);
}


#####################################
void __cdecl CVplan::OnDaySwitch(CVplan *const this, int32_t nDiffDays)
{
  bool v2; // bl
  CfgData *v3; // rax
  int32_t v4; // ebx
  CExtOperateLimit *OperateLimit; // rax
  bool v6; // bl
  CfgData *v7; // rax
  int32_t v8; // ebx
  CExtOperateLimit *v9; // rax
  bool v10; // bl
  bool v11; // bl
  CfgData *v12; // rax
  XunLeiCfgMap *XunLeiTable; // rax
  std::pair<const int,XunLeiCfg> *v14; // rax
  std::pair<const int,XunLeiCfg> *v15; // rax
  XunLeiCfgMap XunLieCfgTable; // [rsp+10h] [rbp-F0h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > it; // [rsp+40h] [rbp-C0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,LuDaShiVip> > iter_0; // [rsp+50h] [rbp-B0h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > iter; // [rsp+60h] [rbp-A0h] BYREF
  std::string __lhs; // [rsp+70h] [rbp-90h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > __x; // [rsp+80h] [rbp-80h] BYREF
  std::string v22; // [rsp+90h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,LuDaShiVip> > v23; // [rsp+A0h] [rbp-60h] BYREF
  std::string v24; // [rsp+B0h] [rbp-50h] BYREF
  std::string v25; // [rsp+C0h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > v26; // [rsp+D0h] [rbp-30h] BYREF
  const CfgYYVipMap *YYVipMap; // [rsp+D8h] [rbp-28h]
  const LuDaShiVipMap *LuDaShi; // [rsp+E0h] [rbp-20h]
  int32_t NewRecord; // [rsp+E8h] [rbp-18h]
  int32_t Record; // [rsp+ECh] [rbp-14h]

  CVplan::SendVplanInfo(this);
  CVplan::SendVplanIcon(this);
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator==<char>(&__lhs, "duowanclouds");
    std::string::~string(&__lhs);
    if ( v2 )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      YYVipMap = CfgData::GetCfgYYVipMap(v3);
      for ( iter._M_node = std::map<int,CfgYYVip>::begin(YYVipMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,CfgYYVip>::end(YYVipMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator!=(&iter, &__x) )
          break;
        if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter)->second.nType == 4 )
        {
          v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter)->first + 1500;
          OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
          CExtOperateLimit::Reset(OperateLimit, v4);
        }
      }
      CVplan::SendYYVipIcon(this);
    }
    else
    {
      Player::GetPlatform((const Player *const)&v22);
      v6 = std::operator==<char>(&v22, "taojike");
      std::string::~string(&v22);
      if ( v6 )
      {
        v7 = Answer::Singleton<CfgData>::instance();
        LuDaShi = CfgData::GetLaDaShiHuiYuanMap(v7);
        for ( iter_0._M_node = std::map<int,LuDaShiVip>::begin(LuDaShi)._M_node;
              ;
              std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator++(&iter_0) )
        {
          v23._M_node = std::map<int,LuDaShiVip>::end(LuDaShi)._M_node;
          if ( !std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator!=(&iter_0, &v23) )
            break;
          if ( std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator->(&iter_0)->second.nType == 6 )
          {
            v8 = std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator->(&iter_0)->first + 1551;
            v9 = Player::GetOperateLimit(this->m_pPlayer);
            CExtOperateLimit::Reset(v9, v8);
          }
        }
        CVplan::SendLuDaShiIcon(this);
      }
      else
      {
        Player::GetPlatform((const Player *const)&v24);
        v10 = std::operator==<char>(&v24, "swjoy");
        std::string::~string(&v24);
        if ( v10 )
        {
          CVplan::CheckSwBarLoginCount(this);
          CVplan::resetSwVipDailyReward(this);
          CVplan::resetSwBarDailyReward(this);
          CVplan::sendSwVipIcon(this);
          CVplan::sendSwVipBarIcon(this);
        }
      }
    }
    Player::GetPlatform((const Player *const)&v25);
    v11 = std::operator==<char>(&v25, "niuxyx");
    std::string::~string(&v25);
    if ( v11 )
    {
      NewRecord = 0;
      Record = Player::getRecord(this->m_pPlayer, 1156);
      v12 = Answer::Singleton<CfgData>::instance();
      XunLeiTable = CfgData::GetXunLeiTable(v12);
      std::map<int,XunLeiCfg>::map(&XunLieCfgTable, XunLeiTable);
      for ( it._M_node = std::map<int,XunLeiCfg>::begin(&XunLieCfgTable)._M_node;
            ;
            std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator++(&it, 0) )
      {
        v26._M_node = std::map<int,XunLeiCfg>::end(&XunLieCfgTable)._M_node;
        if ( !std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator!=(&it, &v26) )
          break;
        if ( std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it)->second.nType != 2 )
        {
          v14 = std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it);
          if ( ((Record >> (LOBYTE(v14->first) - 1)) & 1) == 1 )
          {
            v15 = std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it);
            NewRecord |= 1 << (LOBYTE(v15->first) - 1);
          }
        }
      }
      Player::updateRecord(this->m_pPlayer, 1156, NewRecord);
      CVplan::SendXunLeiIcon(this);
      std::map<int,XunLeiCfg>::~map(&XunLieCfgTable);
    }
  }
}


#####################################
void __cdecl CVplan::OnWeekSwitch(CVplan *const this, int32_t nDiffWeeks)
{
  bool v2; // bl
  CfgData *v3; // rax
  int32_t v4; // ebx
  CExtOperateLimit *OperateLimit; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+20h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > __x; // [rsp+30h] [rbp-20h] BYREF
  const CfgYYVipMap *YYVipMap; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = std::operator==<char>(&__lhs, "duowanclouds");
    std::string::~string(&__lhs);
    if ( v2 )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      YYVipMap = CfgData::GetCfgYYVipMap(v3);
      for ( iter._M_node = std::map<int,CfgYYVip>::begin(YYVipMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,CfgYYVip>::end(YYVipMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator!=(&iter, &__x) )
          break;
        if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter)->second.nType == 5 )
        {
          v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter)->first + 1500;
          OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
          CExtOperateLimit::Reset(OperateLimit, v4);
        }
      }
    }
  }
}


#####################################
void __cdecl CVplan::GetInterestsProtocol(CVplan *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int16 v3; // [rsp+12h] [rbp-1Eh] BYREF
  unsigned __int16 v4; // [rsp+14h] [rbp-1Ch] BYREF
  unsigned __int16 v5; // [rsp+16h] [rbp-1Ah] BYREF
  unsigned __int16 v6; // [rsp+18h] [rbp-18h] BYREF
  unsigned __int16 v7; // [rsp+1Ah] [rbp-16h] BYREF
  unsigned __int16 v8; // [rsp+1Ch] [rbp-14h] BYREF
  unsigned __int16 v9; // [rsp+1Eh] [rbp-12h] BYREF
  unsigned __int16 v10; // [rsp+20h] [rbp-10h] BYREF
  unsigned __int16 v11; // [rsp+22h] [rbp-Eh] BYREF
  unsigned __int16 v12; // [rsp+24h] [rbp-Ch] BYREF
  unsigned __int16 v13; // [rsp+26h] [rbp-Ah] BYREF
  unsigned __int16 v14; // [rsp+28h] [rbp-8h] BYREF
  unsigned __int16 v15; // [rsp+2Ah] [rbp-6h] BYREF
  unsigned __int16 v16; // [rsp+2Ch] [rbp-4h] BYREF
  unsigned __int16 v17; // [rsp+2Eh] [rbp-2h] BYREF

  __x = 535;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 536;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 551;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 552;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 553;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 554;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 555;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 538;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 537;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 556;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 557;
  std::list<unsigned short>::push_back(procList, &v12);
  v13 = 558;
  std::list<unsigned short>::push_back(procList, &v13);
  v14 = 559;
  std::list<unsigned short>::push_back(procList, &v14);
  v15 = 560;
  std::list<unsigned short>::push_back(procList, &v15);
  v16 = 565;
  std::list<unsigned short>::push_back(procList, &v16);
  v17 = 566;
  std::list<unsigned short>::push_back(procList, &v17);
}


#####################################
int32_t __cdecl CVplan::DispatchNetDatas(CVplan *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x217u:
      CVplan::SendVplanInfo(this);
      goto LABEL_21;
    case 0x218u:
      return CVplan::OnGetReward(this, inPacket);
    case 0x219u:
      return CVplan::OnGetSWVipReward(this, inPacket);
    case 0x21Au:
      CVplan::SendSwVipReward(this);
      goto LABEL_21;
    case 0x227u:
      return CVplan::OnGetYYLevelReward(this, inPacket);
    case 0x228u:
      CVplan::SendYYInfo(this);
      goto LABEL_21;
    case 0x229u:
      return CVplan::OnGetYYVipGift(this, inPacket);
    case 0x22Au:
      CVplan::SendYYVipInfo(this);
      goto LABEL_21;
    case 0x22Bu:
      return CVplan::OnLoginFromYYgameApp(this, inPacket);
    case 0x22Cu:
      return CVplan::OnGetSWVipBarReward(this, inPacket);
    case 0x22Du:
      CVplan::SendSgGameAppInfo(this);
      goto LABEL_21;
    case 0x22Eu:
      return CVplan::OnGetSgGameApp(this, inPacket);
    case 0x22Fu:
      return CVplan::OnGetXunLeiReward(this, inPacket);
    case 0x230u:
      CVplan::SendXunLieInfo(this);
      goto LABEL_21;
    case 0x235u:
      CVplan::SendLuDaShiVipInfo(this);
LABEL_21:
      result = 0;
      break;
    case 0x236u:
      result = CVplan::OnGetLuDaShiVipGift(this, inPacket);
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
int32_t __cdecl CVplan::OnLoginFromYYgameApp(CVplan *const this, Answer::NetPacket *inPacket)
{
  CWan360 *Wan360; // rax

  if ( !inPacket )
    return 2;
  this->m_fromLYGameApp = Answer::NetPacket::readInt8(inPacket);
  Wan360 = Player::GetWan360(this->m_pPlayer);
  CWan360::SendGameAppIcon(Wan360);
  CVplan::SendSgDownLoadIcon(this);
  return 0;
}


#####################################
void __cdecl CVplan::OnLoadFromDB(CVplan *const this, const PlayerDBData *const dbData)
{
  this->m_VplanType = dbData->m_VplanData.m_VplanType;
  this->m_VplanLevel = dbData->m_VplanData.m_VplanLevel;
  this->m_nSwVipLevel = dbData->m_VplanData.m_SwVipLevel;
  this->m_bSwVipBar = dbData->sysUser.data.net_bar;
  this->m_YyLevel = dbData->m_VplanData.m_YYLevel;
  this->m_YyVipLevel = dbData->m_VplanData.m_YYVipLevel;
  this->m_YySuperLevel = dbData->m_VplanData.m_YySuperLevel;
  this->m_SgHallLevel = dbData->m_VplanData.m_SgHallLevel;
  std::string::operator=(&this->m_strSGPf, &dbData->m_VplanData.m_strSGPf);
  this->m_XlNxLevel = dbData->m_VplanData.m_XlNxLevel;
  this->m_PlatformVip = dbData->m_VplanData.m_PlatformVip;
  this->m_PlatformSuperVip = dbData->m_VplanData.m_PlatformSuperVip;
  if ( this->m_YySuperLevel > 0 )
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_YY_SUPER_VIP_LEVEL, this->m_YySuperLevel);
  if ( this->m_nSwVipLevel > 0 )
    Player::sendUpdateSocialPlayerInfo(this->m_pPlayer, PlayerInfoIndex::PII_SW_VIP_LEVEL, this->m_nSwVipLevel);
}


#####################################
void __cdecl CVplan::AddAttr(CVplan *const this)
{
  int32_t m_YySuperLevel; // ebx
  CfgData *v2; // rax
  int8_t m_nSwVipLevel; // bl
  CfgData *v4; // rax
  CfgVplan *CfgVplan; // rax
  char v6; // bl
  bool v7; // al
  bool v8; // r12
  int32_t m_PlatformVip; // ebx
  CfgData *v10; // rax
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  const CfgYYSuperBuff *pCfgSuperBuff; // [rsp+18h] [rbp-38h]
  int32_t AttValue; // [rsp+24h] [rbp-2Ch]
  const CfgYYSuperBuff *pCfgSuperBuff_0; // [rsp+28h] [rbp-28h]

  if ( this->m_pPlayer )
  {
    if ( this->m_YySuperLevel > 0 )
    {
      m_YySuperLevel = this->m_YySuperLevel;
      v2 = Answer::Singleton<CfgData>::instance();
      pCfgSuperBuff = CfgData::GetSuperBuff(v2, m_YySuperLevel);
      if ( pCfgSuperBuff )
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)pCfgSuperBuff->AttrType, pCfgSuperBuff->AttrRate);
    }
    if ( this->m_nSwVipLevel > 0 )
    {
      m_nSwVipLevel = this->m_nSwVipLevel;
      v4 = Answer::Singleton<CfgData>::instance();
      CfgVplan = CfgData::GetCfgVplan(v4);
      AttValue = CfgVplan::GetSwVipExpRatio(CfgVplan, m_nSwVipLevel);
      Unit::AddAttrValue(this->m_pPlayer, CObjAttrs::Index_T::ATTR_ATK_ADD, AttValue);
    }
    v6 = 0;
    v7 = 0;
    if ( this->m_PlatformVip > 0 )
    {
      Player::GetPlatform((const Player *const)&__lhs);
      v6 = 1;
      if ( std::operator==<char>(&__lhs, "37wan") )
        v7 = 1;
    }
    v8 = v7;
    if ( v6 )
      std::string::~string(&__lhs);
    if ( v8 )
    {
      m_PlatformVip = this->m_PlatformVip;
      v10 = Answer::Singleton<CfgData>::instance();
      pCfgSuperBuff_0 = CfgData::Get37wanSuperBuff(v10, m_PlatformVip);
      if ( pCfgSuperBuff_0 )
        Unit::AddAttrValue(
          this->m_pPlayer,
          (const CObjAttrs::Index_T)pCfgSuperBuff_0->AttrType,
          pCfgSuperBuff_0->AttrRate);
    }
  }
}


#####################################
int32_t __cdecl CVplan::GetExpRatio(const CVplan *const this)
{
  CfgData *v1; // rax
  CfgVplan *CfgVplan; // rax
  bool v3; // al
  bool v4; // r12
  std::string __lhs; // [rsp+10h] [rbp-30h] BYREF
  int32_t nExpRatio; // [rsp+1Ch] [rbp-24h]

  nExpRatio = 0;
  if ( this->m_bSwVipBar )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    CfgVplan = CfgData::GetCfgVplan(v1);
    nExpRatio += CfgVplan::GetSwBarExpRatio(CfgVplan);
  }
  Player::GetPlatform((const Player *const)&__lhs);
  v3 = std::operator==<char>(&__lhs, "sogou") && std::operator==<char>(&this->m_strSGPf, "hz");
  v4 = v3;
  std::string::~string(&__lhs);
  if ( v4 )
    nExpRatio += 10;
  return nExpRatio;
}


#####################################
int32_t __cdecl CVplan::OnGetReward(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgVplan *v4; // rax
  CExtCharBag *v5; // rax
  int32_t v6; // ebx
  CExtCharBag *v7; // rax
  CExtCharBag *v8; // rax
  int32_t v9; // ebx
  CExtCharBag *v10; // rax
  CfgData *v11; // rax
  CfgVplan *CfgVplan; // rax
  int Level; // ebx
  CExtCharBag *Bag; // rax
  CfgData *v15; // rax
  CfgVplan *v16; // rax
  CExtCharBag *v17; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v19; // rax
  CExtCharBag *v20; // rax
  int8_t GiftType; // [rsp+1Ah] [rbp-36h]
  int8_t VplanGiftType; // [rsp+1Bh] [rbp-35h]
  int32_t Index; // [rsp+1Ch] [rbp-34h]
  VplanEveryDayReward *Reward; // [rsp+20h] [rbp-30h]
  VplanLevelReward *Reward_0; // [rsp+28h] [rbp-28h]
  int32_t OldRecord; // [rsp+30h] [rbp-20h]
  int NewRecord; // [rsp+34h] [rbp-1Ch]
  VplanReward *Reward_1; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  GiftType = Answer::NetPacket::readInt8(inPacket);
  VplanGiftType = Answer::NetPacket::readInt8(inPacket);
  Index = Answer::NetPacket::readInt32(inPacket);
  switch ( GiftType )
  {
    case 2:
      v11 = Answer::Singleton<CfgData>::instance();
      CfgVplan = CfgData::GetCfgVplan(v11);
      Reward_0 = CfgVplan::GetVplanLevelReward(CfgVplan, Index);
      if ( !Reward_0 )
        return 2;
      Level = Reward_0->Level;
      if ( Level > (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
        return 2;
      OldRecord = Player::getRecord(this->m_pPlayer, 1096);
      NewRecord = OldRecord | (1 << (Index - 1));
      if ( OldRecord == NewRecord )
        return 2;
      Bag = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::AddItem(Bag, &Reward_0->Reward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT) )
        return 2;
      Player::updateRecord(this->m_pPlayer, 1096, NewRecord);
      break;
    case 3:
      v15 = Answer::Singleton<CfgData>::instance();
      v16 = CfgData::GetCfgVplan(v15);
      Reward_1 = CfgVplan::GetVplanReward(v16, Index);
      if ( !Reward_1 )
        return 2;
      if ( VplanGiftType || !this->m_VplanType )
      {
        if ( VplanGiftType == 1 && this->m_VplanType == 2 )
        {
          if ( Player::getRecord(this->m_pPlayer, 1098) > 0 )
            return 2;
          v20 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::AddItem(v20, &Reward_1->YearVipReward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT);
          Player::updateRecord(this->m_pPlayer, 1098, Index);
        }
      }
      else
      {
        if ( Player::getRecord(this->m_pPlayer, 1097) > 0 )
          return 2;
        v17 = Player::GetBag(this->m_pPlayer);
        FreeSlotCount = CExtCharBag::GetFreeSlotCount(v17);
        if ( FreeSlotCount < (int)std::vector<MemChrBag>::size(&Reward_1->Reward) )
          return 2;
        v19 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::AddItem(v19, &Reward_1->Reward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT);
        Player::updateRecord(this->m_pPlayer, 1097, Index);
      }
      break;
    case 1:
      v3 = Answer::Singleton<CfgData>::instance();
      v4 = CfgData::GetCfgVplan(v3);
      Reward = CfgVplan::GetVplanEveryDayReward(v4, Index);
      if ( !Reward )
        return 2;
      if ( VplanGiftType )
      {
        if ( VplanGiftType == 1 && this->m_VplanType == 2 )
        {
          if ( Player::getRecord(this->m_pPlayer, 2047) > 0 )
            return 2;
          v8 = Player::GetBag(this->m_pPlayer);
          v9 = CExtCharBag::GetFreeSlotCount(v8);
          if ( v9 < (int)std::vector<MemChrBag>::size(&Reward->YearVipReward) )
            return 2;
          v10 = Player::GetBag(this->m_pPlayer);
          CExtCharBag::AddItem(v10, &Reward->YearVipReward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT);
          Player::updateRecord(this->m_pPlayer, 2047, Index);
        }
      }
      else
      {
        if ( this->m_VplanLevel != Reward->Level )
          return 2;
        if ( Player::getRecord(this->m_pPlayer, 2046) > 0 )
          return 2;
        v5 = Player::GetBag(this->m_pPlayer);
        v6 = CExtCharBag::GetFreeSlotCount(v5);
        if ( v6 < (int)std::vector<MemChrBag>::size(&Reward->Reward) )
          return 2;
        v7 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::AddItem(v7, &Reward->Reward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT);
        Player::updateRecord(this->m_pPlayer, 2046, Index);
      }
      break;
    default:
      return 2;
  }
  CVplan::SendVplanInfo(this);
  CVplan::SendVplanIcon(this);
  return 0;
}


#####################################
bool __cdecl CVplan::HaveEveryDayGift(CVplan *const this)
{
  if ( !this->m_pPlayer )
    return 0;
  if ( (this->m_VplanType == 1 || this->m_VplanType == 2) && Player::getRecord(this->m_pPlayer, 2046) <= 0 )
    return 1;
  return this->m_VplanType == 2 && Player::getRecord(this->m_pPlayer, 2047) <= 0;
}


#####################################
bool __cdecl CVplan::HaveLevelGift(CVplan *const this)
{
  CfgData *v2; // rax
  CfgVplan *CfgVplan; // rax
  const std::pair<const int,VplanLevelReward> *v4; // rax
  const std::pair<const int,VplanLevelReward> *v5; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,VplanLevelReward> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,VplanLevelReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t Record; // [rsp+30h] [rbp-20h]
  int32_t Level; // [rsp+34h] [rbp-1Ch]
  const VplanLevelRewardMap *rewardMap; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  if ( this->m_VplanType == 1 || this->m_VplanType == 2 )
  {
    Record = Player::getRecord(this->m_pPlayer, 1096);
    Level = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
    v2 = Answer::Singleton<CfgData>::instance();
    CfgVplan = CfgData::GetCfgVplan(v2);
    rewardMap = CfgVplan::GetVplanLevelRewardMap(CfgVplan);
    for ( it._M_node = std::map<int,VplanLevelReward>::begin(rewardMap)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<int const,VplanLevelReward>>::operator++(&it) )
    {
      __x._M_node = std::map<int,VplanLevelReward>::end(rewardMap)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<int const,VplanLevelReward>>::operator!=(&it, &__x) )
        break;
      v4 = std::_Rb_tree_const_iterator<std::pair<int const,VplanLevelReward>>::operator->(&it);
      if ( v4->second.Level <= Level )
      {
        v5 = std::_Rb_tree_const_iterator<std::pair<int const,VplanLevelReward>>::operator->(&it);
        if ( ((Record >> (LOBYTE(v5->first) - 1)) & 1) == 0 )
          return 1;
      }
    }
  }
  return 0;
}


#####################################
bool __cdecl CVplan::HaveVplanGift(CVplan *const this)
{
  if ( !this->m_pPlayer )
    return 0;
  if ( (this->m_VplanType == 1 || this->m_VplanType == 2) && Player::getRecord(this->m_pPlayer, 1097) <= 0 )
    return 1;
  return this->m_VplanType == 2 && Player::getRecord(this->m_pPlayer, 1098) <= 0;
}


#####################################
void __cdecl CVplan::SendVplanInfo(CVplan *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t v4; // edx
  int32_t v5; // edx
  int32_t v6; // edx
  int32_t v7; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v2 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D06u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, this->m_VplanLevel);
    Answer::NetPacket::writeInt8(packet, this->m_VplanType);
    Record = Player::getRecord(this->m_pPlayer, 2046);
    Answer::NetPacket::writeInt32(packet, Record);
    v4 = Player::getRecord(this->m_pPlayer, 2047);
    Answer::NetPacket::writeInt32(packet, v4);
    v5 = Player::getRecord(this->m_pPlayer, 1096);
    Answer::NetPacket::writeInt32(packet, v5);
    v6 = Player::getRecord(this->m_pPlayer, 1097);
    Answer::NetPacket::writeInt32(packet, v6);
    v7 = Player::getRecord(this->m_pPlayer, 1098);
    Answer::NetPacket::writeInt32(packet, v7);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    v10 = Player::getConnId(this->m_pPlayer);
    v11 = Answer::Singleton<GameService>::instance();
    GameService::sendPacketTo(v11, v10, GateIndex, packet);
  }
}


#####################################
void __cdecl CVplan::SendVplanIcon(CVplan *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "w360");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet )
      {
        CVplan::GetVplanIconStu(&stu, this);
        Answer::NetPacket::writeInt32(packet, stu.nId);
        Answer::NetPacket::writeInt8(packet, stu.nState);
        Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
        Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
        Answer::NetPacket::writeInt32(packet, stu.nIconRight);
        Answer::NetPacket::writeInt8(packet, stu.nEffects);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v6 = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CVplan::GetVplanIconState(CVplan *const this, IconStateList *const IconList)
{
  bool v2; // bl
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF

  Player::GetPlatform((const Player *const)&__lhs);
  v2 = std::operator!=<char>(&__lhs, "w360");
  std::string::~string(&__lhs);
  if ( !v2 )
  {
    if ( this->m_pPlayer )
    {
      CVplan::GetVplanIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
int32_t __cdecl CVplan::OnGetYYLevelReward(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  int nType; // eax
  CExtCharBag *Bag; // rax
  CWan360 *Wan360; // rax
  int32_t Index; // [rsp+1Ch] [rbp-24h]
  CfgYYGameApp *Reward; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  if ( this->m_fromLYGameApp <= 0 )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  Reward = CfgData::GetYYGameApp(v3, Index);
  if ( !Reward )
    return 2;
  nType = Reward->nType;
  if ( nType == 2 )
  {
    if ( Player::GetContinueLoginCount(this->m_pPlayer) < Reward->nCondition )
      return 2;
  }
  else if ( nType > 2 )
  {
    if ( nType == 3 )
    {
      if ( (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) < Reward->nCondition )
        return 2;
    }
    else
    {
      if ( nType != 4 )
        return 2;
      if ( this->m_YyLevel < Reward->nCondition )
        return 2;
    }
  }
  else if ( nType != 1 )
  {
    return 2;
  }
  OldRecord = Player::getRecord(this->m_pPlayer, 1100);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &Reward->Rewards, ITEM_CHANGE_REASON::ICR_YY_DA_TING) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1100, NewRecord);
  CVplan::SendYYInfo(this);
  Wan360 = Player::GetWan360(this->m_pPlayer);
  CWan360::SendGameAppIcon(Wan360);
  return 0;
}


#####################################
int32_t __cdecl CVplan::HaveYYLevelReward(CVplan *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgYYGameAppMap *YYGameAppMap; // rax
  const std::pair<const int,CfgYYGameApp> *v4; // rax
  int nType; // eax
  int32_t ContinueLoginCount; // ebx
  int32_t v7; // ebx
  int32_t m_YyLevel; // ebx
  CfgYYGameAppMap YYGameApp; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYGameApp> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYGameApp> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t Count; // [rsp+58h] [rbp-18h]
  int32_t Record; // [rsp+5Ch] [rbp-14h]

  Count = 0;
  if ( this->m_fromLYGameApp <= 0 )
    return Count;
  Record = Player::getRecord(this->m_pPlayer, 1100);
  v2 = Answer::Singleton<CfgData>::instance();
  YYGameAppMap = CfgData::GetYYGameAppMap(v2);
  std::map<int,CfgYYGameApp>::map(&YYGameApp, YYGameAppMap);
  for ( it._M_node = std::map<int,CfgYYGameApp>::begin(&YYGameApp)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgYYGameApp>::end(&YYGameApp)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator!=(&it, &__x) )
      break;
    v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator->(&it);
    if ( ((Record >> (LOBYTE(v4->first) - 1)) & 1) == 0 )
    {
      nType = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator->(&it)->second.nType;
      if ( nType == 2 )
      {
        ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
        if ( ContinueLoginCount >= std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator->(&it)->second.nCondition )
          ++Count;
      }
      else if ( nType > 2 )
      {
        if ( nType == 3 )
        {
          v7 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
          if ( v7 >= std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator->(&it)->second.nCondition )
            ++Count;
        }
        else if ( nType == 4 )
        {
          m_YyLevel = this->m_YyLevel;
          if ( m_YyLevel >= std::_Rb_tree_const_iterator<std::pair<int const,CfgYYGameApp>>::operator->(&it)->second.nCondition )
            ++Count;
        }
      }
      else if ( nType == 1 )
      {
        ++Count;
      }
    }
  }
  v1 = Count;
  std::map<int,CfgYYGameApp>::~map(&YYGameApp);
  return v1;
}


#####################################
void __cdecl CVplan::SendYYInfo(CVplan *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t ContinueLoginCount; // eax
  int32_t Record; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v8; // bl
  GameService *v9; // rax
  std::string __lhs; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "duowanclouds");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D13u);
      if ( packet )
      {
        ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
        Answer::NetPacket::writeInt32(packet, ContinueLoginCount);
        Answer::NetPacket::writeInt32(packet, this->m_YyLevel);
        Record = Player::getRecord(this->m_pPlayer, 1100);
        Answer::NetPacket::writeInt32(packet, Record);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v8 = Player::getConnId(this->m_pPlayer);
        v9 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v9, v8, GateIndex, packet);
      }
    }
  }
}


#####################################
int32_t __cdecl CVplan::OnGetYYVipGift(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v8; // rax
  int32_t nIndex; // [rsp+14h] [rbp-1Ch]
  CfgYYVip *pReward; // [rsp+18h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::GetYYVip(v3, nIndex);
  if ( !pReward )
    return 2;
  if ( this->m_YyVipLevel < pReward->nCondition )
    return 2;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, nIndex + 1500) >= pReward->nLimit )
    return 2;
  if ( pReward->nPric > 0 && Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < pReward->nPric )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pReward->Rewards, ITEM_CHANGE_REASON::ICR_YY_VIP) )
    return 2;
  if ( pReward->nPric > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          pReward->nPric,
          CURRENCY_CHANGE_REASON::GCR_BUY_YY_VIP_REWARD,
          0) )
  {
    return 2;
  }
  v8 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::AddLimitCount(v8, nIndex + 1500, 1);
  CVplan::SendYYVipInfo(this);
  CVplan::SendYYVipIcon(this);
  return 0;
}


#####################################
void __cdecl CVplan::SendYYVipInfo(CVplan *const this)
{
  char v1; // bl
  bool v2; // al
  bool v3; // r12
  int8_t ConnId; // bl
  GameService *v5; // rax
  CfgData *v6; // rax
  int8_t v7; // al
  const std::pair<const int,CfgYYVip> *v8; // rax
  int8_t Record; // al
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > iter; // [rsp+10h] [rbp-60h] BYREF
  std::string __lhs; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > __x; // [rsp+30h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+40h] [rbp-30h]
  const CfgYYVipMap *YYVipMap; // [rsp+48h] [rbp-28h]

  v1 = 0;
  v2 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = 1;
    if ( !std::operator!=<char>(&__lhs, "duowanclouds") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D14u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_YyVipLevel);
      v6 = Answer::Singleton<CfgData>::instance();
      YYVipMap = CfgData::GetCfgYYVipMap(v6);
      v7 = std::map<int,CfgYYVip>::size(YYVipMap);
      Answer::NetPacket::writeInt8(packet, v7);
      for ( iter._M_node = std::map<int,CfgYYVip>::begin(YYVipMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,CfgYYVip>::end(YYVipMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator!=(&iter, &__x) )
          break;
        v8 = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter);
        Record = Player::getRecord(this->m_pPlayer, v8->first + 1500);
        Answer::NetPacket::writeInt8(packet, Record);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v13, v12, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CVplan::GetYYVipIconState(CVplan *const this, IconStateList *const IconList)
{
  bool v2; // bl
  CFunctionOpen *PlayerFunctionOpen; // rax
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF

  Player::GetPlatform((const Player *const)&__lhs);
  v2 = std::operator!=<char>(&__lhs, "duowanclouds");
  std::string::~string(&__lhs);
  if ( !v2 && this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 213) )
    {
      CVplan::GetYYVipIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CVplan::SendYYVipIcon(CVplan *const this)
{
  bool v1; // bl
  CFunctionOpen *PlayerFunctionOpen; // rax
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "duowanclouds");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 213) )
      {
        ConnId = Player::getConnId(this->m_pPlayer);
        v4 = Answer::Singleton<GameService>::instance();
        packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
        if ( packet )
        {
          CVplan::GetYYVipIconStu(&stu, this);
          Answer::NetPacket::writeInt32(packet, stu.nId);
          Answer::NetPacket::writeInt8(packet, stu.nState);
          Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
          Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
          Answer::NetPacket::writeInt32(packet, stu.nIconRight);
          Answer::NetPacket::writeInt8(packet, stu.nEffects);
          WOffset = Answer::NetPacket::getWOffset(packet);
          Answer::NetPacket::setSize(packet, WOffset);
          GateIndex = Player::getGateIndex(this->m_pPlayer);
          v7 = Player::getConnId(this->m_pPlayer);
          v8 = Answer::Singleton<GameService>::instance();
          GameService::sendPacketTo(v8, v7, GateIndex, packet);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CVplan::HaveYYVipLeftGift(CVplan *const this)
{
  CfgData *v2; // rax
  const std::pair<const int,CfgYYVip> *v3; // rax
  int32_t v4; // ebx
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // ebx
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgYYVip> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+2Ch] [rbp-24h]
  const CfgYYVipMap *YYVipMap; // [rsp+30h] [rbp-20h]
  const CfgYYVip *stu; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  nCount = 0;
  v2 = Answer::Singleton<CfgData>::instance();
  YYVipMap = CfgData::GetCfgYYVipMap(v2);
  for ( iter._M_node = std::map<int,CfgYYVip>::begin(YYVipMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgYYVip>::end(YYVipMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter);
    stu = &v3->second;
    if ( v3->second.nPric <= 0 && this->m_YyVipLevel >= stu->nCondition )
    {
      v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter)->first + 1500;
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, v4);
      if ( LimitCount < std::_Rb_tree_const_iterator<std::pair<int const,CfgYYVip>>::operator->(&iter)->second.nLimit )
        ++nCount;
    }
  }
  return nCount;
}


#####################################
void __cdecl CVplan::AppendYYInfo(CVplan *const this, Answer::NetPacket *packet)
{
  if ( packet )
  {
    Answer::NetPacket::writeInt8(packet, this->m_YyVipLevel);
    Answer::NetPacket::writeInt8(packet, this->m_YySuperLevel);
  }
}


#####################################
int32_t __cdecl CVplan::OnGetSWVipReward(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgVplan *CfgVplan; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-31h]
  const CfgSwVipReward *pCfgReward; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v3);
  pCfgReward = CfgVplan::GetSwVipReward(CfgVplan, nIndex);
  if ( !pCfgReward )
    return 10002;
  nOldRecord = Player::getRecord(this->m_pPlayer, 1099);
  nNewRecord = nOldRecord | (1 << (nIndex - 1));
  if ( nOldRecord == nNewRecord )
    return 10002;
  if ( !CVplan::checkSwVipRewardCondition(this, pCfgReward->nType, pCfgReward->nCondition) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgReward->vReward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1099, nNewRecord);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, nIndex);
  CVplan::sendSwVipIcon(this);
  return 0;
}


#####################################
int32_t __cdecl CVplan::OnGetSWVipBarReward(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgVplan *CfgVplan; // rax
  CExtCharBag *Bag; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v9; // rax
  int8_t nIndex; // [rsp+1Fh] [rbp-31h]
  const CfgSwVipReward *pCfgReward; // [rsp+20h] [rbp-30h]
  int32_t nOldRecord; // [rsp+28h] [rbp-28h]
  int nNewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket )
    return 10002;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v3);
  pCfgReward = CfgVplan::GetSwVipBarReward(CfgVplan, nIndex);
  if ( !pCfgReward )
    return 10002;
  nOldRecord = Player::getRecord(this->m_pPlayer, 1095);
  nNewRecord = nOldRecord | (1 << (nIndex - 1));
  if ( nOldRecord == nNewRecord )
    return 10002;
  if ( !CVplan::checkSwBarRewardCondition(this, pCfgReward->nType, pCfgReward->nCondition) )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfgReward->vReward, ITEM_CHANGE_REASON::ICR_VPALN_GIFT) )
    return 10002;
  Player::updateRecord(this->m_pPlayer, 1095, nNewRecord);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v9 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v9, ConnId, GateIndex, Proc, nIndex);
  CVplan::sendSwVipBarIcon(this);
  return 0;
}


#####################################
void __cdecl CVplan::SendSwVipReward(CVplan *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t v4; // edx
  int32_t v5; // edx
  int32_t v6; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v9; // bl
  GameService *v10; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D07u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, this->m_nSwVipLevel);
      Record = Player::getRecord(this->m_pPlayer, 1099);
      Answer::NetPacket::writeInt32(packet, Record);
      Answer::NetPacket::writeInt8(packet, this->m_bSwVipBar);
      v4 = Player::getRecord(this->m_pPlayer, 1092);
      Answer::NetPacket::writeInt32(packet, v4);
      v5 = Player::getRecord(this->m_pPlayer, 1094);
      Answer::NetPacket::writeInt32(packet, v5);
      v6 = Player::getRecord(this->m_pPlayer, 1095);
      Answer::NetPacket::writeInt32(packet, v6);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v9 = Player::getConnId(this->m_pPlayer);
      v10 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v10, v9, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CVplan::AppendSwVipInfo(CVplan *const this, Answer::NetPacket *packet)
{
  if ( packet )
    Answer::NetPacket::writeInt8(packet, this->m_nSwVipLevel);
}


#####################################
void __cdecl CVplan::CheckSwBarLoginCount(CVplan *const this)
{
  bool v1; // bl
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v3; // rax
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  CExtOperateLimit *v6; // rax
  CExtOperateLimit *v7; // rax
  std::string __lhs; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "swjoy");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      if ( this->m_bSwVipBar )
      {
        OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
        if ( !CExtOperateLimit::GetLimitCount(OperateLimit, 2087) )
        {
          v3 = Player::GetOperateLimit(this->m_pPlayer);
          CExtOperateLimit::AddLimitCount(v3, 1092, 1);
          v4 = Player::GetOperateLimit(this->m_pPlayer);
          CExtOperateLimit::UpdateLimitCount(v4, 2087, 1);
        }
        if ( this->m_nSwVipLevel > 0 )
        {
          v5 = Player::GetOperateLimit(this->m_pPlayer);
          if ( !CExtOperateLimit::GetLimitCount(v5, 2088) )
          {
            v6 = Player::GetOperateLimit(this->m_pPlayer);
            CExtOperateLimit::AddLimitCount(v6, 1094, 1);
            v7 = Player::GetOperateLimit(this->m_pPlayer);
            CExtOperateLimit::UpdateLimitCount(v7, 2088, 1);
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CVplan::GetSwVipIconState(CVplan *const this, IconStateList *const IconList)
{
  char v2; // bl
  bool v3; // al
  bool v4; // r12
  std::string __lhs; // [rsp+10h] [rbp-50h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-40h] BYREF

  v2 = 0;
  v3 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = 1;
    if ( !std::operator!=<char>(&__lhs, "swjoy") )
      v3 = 0;
  }
  v4 = v3;
  if ( v2 )
    std::string::~string(&__lhs);
  if ( !v4 )
  {
    CVplan::getSwVipIconStu(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CVplan::GetSwVipBarIconState(CVplan *const this, IconStateList *const IconList)
{
  char v2; // bl
  bool v3; // al
  bool v4; // r12
  std::string __lhs; // [rsp+10h] [rbp-50h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-40h] BYREF

  v2 = 0;
  v3 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = 1;
    if ( !std::operator!=<char>(&__lhs, "swjoy") )
    {
      if ( this->m_bSwVipBar )
        v3 = 0;
    }
  }
  v4 = v3;
  if ( v2 )
    std::string::~string(&__lhs);
  if ( !v4 )
  {
    CVplan::getSwVipBarIconStu(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CVplan::sendSwVipIcon(CVplan *const this)
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
    if ( !std::operator!=<char>(&__lhs, "swjoy") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    CVplan::getSwVipIconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
int32_t __cdecl CVplan::getSwVipRewardCount(CVplan *const this)
{
  CfgData *v2; // rax
  CfgVplan *CfgVplan; // rax
  int32_t nCondition; // ebx
  int8_t nType; // cl
  const std::pair<const int,CfgSwVipReward> *v6; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+30h] [rbp-20h]
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  const CfgSwVipRewardMap *CfgSwVip; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  nCount = 0;
  nRecord = Player::getRecord(this->m_pPlayer, 1099);
  v2 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v2);
  CfgSwVip = CfgVplan::GetSwVipRewardMap(CfgVplan);
  for ( iter._M_node = std::map<int,CfgSwVipReward>::begin(CfgSwVip)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSwVipReward>::end(CfgSwVip)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator!=(&iter, &__x) )
      break;
    nCondition = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter)->second.nCondition;
    nType = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter)->second.nType;
    if ( CVplan::checkSwVipRewardCondition(this, nType, nCondition) )
    {
      v6 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
      if ( ((nRecord >> (LOBYTE(v6->first) - 1)) & 1) == 0 )
        ++nCount;
    }
  }
  return nCount;
}


#####################################
bool __cdecl CVplan::isGetAllSwVipReward(CVplan *const this)
{
  CfgData *v1; // rax
  CfgVplan *CfgVplan; // rax
  const std::pair<const int,CfgSwVipReward> *v3; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  const CfgSwVipRewardMap *cfgSwVip; // [rsp+38h] [rbp-18h]

  nRecord = Player::getRecord(this->m_pPlayer, 1099);
  v1 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v1);
  cfgSwVip = CfgVplan::GetSwVipRewardMap(CfgVplan);
  for ( iter._M_node = std::map<int,CfgSwVipReward>::begin(cfgSwVip)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSwVipReward>::end(cfgSwVip)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
    if ( ((nRecord >> (LOBYTE(v3->first) - 1)) & 1) == 0 )
      return 0;
  }
  return 1;
}


#####################################
bool __cdecl CVplan::checkSwVipRewardCondition(CVplan *const this, int8_t nType, int32_t nCondition)
{
  if ( !this->m_pPlayer )
    return 0;
  if ( nType == 2 )
    return 1;
  if ( nType > 2 )
  {
    if ( nType == 3 )
      return (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) >= nCondition;
    if ( nType == 4 )
      return this->m_nSwVipLevel >= nCondition;
  }
  else if ( nType == 1 )
  {
    return 1;
  }
  return 0;
}


#####################################
void __cdecl CVplan::resetSwVipDailyReward(CVplan *const this)
{
  CfgData *v1; // rax
  CfgVplan *CfgVplan; // rax
  const std::pair<const int,CfgSwVipReward> *v3; // rax
  const std::pair<const int,CfgSwVipReward> *v4; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  const CfgSwVipRewardMap *cfgSwVip; // [rsp+38h] [rbp-18h]

  nRecord = Player::getRecord(this->m_pPlayer, 1099);
  v1 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v1);
  cfgSwVip = CfgVplan::GetSwVipRewardMap(CfgVplan);
  for ( iter._M_node = std::map<int,CfgSwVipReward>::begin(cfgSwVip)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSwVipReward>::end(cfgSwVip)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter)->second.nType == 2 )
    {
      v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
      nRecord |= 1 << (LOBYTE(v3->first) - 1);
      v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
      nRecord ^= 1 << (LOBYTE(v4->first) - 1);
    }
  }
  Player::updateRecord(this->m_pPlayer, 1099, nRecord);
}


#####################################
void __cdecl CVplan::sendSwVipBarIcon(CVplan *const this)
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
    if ( !std::operator!=<char>(&__lhs, "swjoy") )
    {
      if ( this->m_bSwVipBar )
        v2 = 0;
    }
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    CVplan::getSwVipBarIconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
int32_t __cdecl CVplan::getSwVipBarRewardCount(CVplan *const this)
{
  CfgData *v2; // rax
  CfgVplan *CfgVplan; // rax
  int32_t nCondition; // ebx
  int8_t nType; // cl
  const std::pair<const int,CfgSwVipReward> *v6; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nCount; // [rsp+30h] [rbp-20h]
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  const CfgSwVipRewardMap *CfgSwVipBar; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer )
    return 0;
  nCount = 0;
  nRecord = Player::getRecord(this->m_pPlayer, 1095);
  v2 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v2);
  CfgSwVipBar = CfgVplan::GetSwVipBarRewardMap(CfgVplan);
  for ( iter._M_node = std::map<int,CfgSwVipReward>::begin(CfgSwVipBar)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSwVipReward>::end(CfgSwVipBar)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator!=(&iter, &__x) )
      break;
    nCondition = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter)->second.nCondition;
    nType = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter)->second.nType;
    if ( CVplan::checkSwBarRewardCondition(this, nType, nCondition) )
    {
      v6 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
      if ( ((nRecord >> (LOBYTE(v6->first) - 1)) & 1) == 0 )
        ++nCount;
    }
  }
  return nCount;
}


#####################################
bool __cdecl CVplan::isGetAllSwVipBarReward(CVplan *const this)
{
  CfgData *v1; // rax
  CfgVplan *CfgVplan; // rax
  const std::pair<const int,CfgSwVipReward> *v3; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  const CfgSwVipRewardMap *cfgSwVipBar; // [rsp+38h] [rbp-18h]

  nRecord = Player::getRecord(this->m_pPlayer, 1095);
  v1 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v1);
  cfgSwVipBar = CfgVplan::GetSwVipBarRewardMap(CfgVplan);
  for ( iter._M_node = std::map<int,CfgSwVipReward>::begin(cfgSwVipBar)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSwVipReward>::end(cfgSwVipBar)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
    if ( ((nRecord >> (LOBYTE(v3->first) - 1)) & 1) == 0 )
      return 0;
  }
  return 1;
}


#####################################
bool __cdecl CVplan::checkSwBarRewardCondition(CVplan *const this, int8_t nType, int32_t nCondition)
{
  if ( !this->m_pPlayer )
    return 0;
  switch ( nType )
  {
    case 2:
      return this->m_nSwVipLevel > 0;
    case 3:
      return Player::getRecord(this->m_pPlayer, 1094) >= nCondition;
    case 1:
      return Player::getRecord(this->m_pPlayer, 1092) >= nCondition;
  }
  return 0;
}


#####################################
void __cdecl CVplan::resetSwBarDailyReward(CVplan *const this)
{
  CfgData *v1; // rax
  CfgVplan *CfgVplan; // rax
  const std::pair<const int,CfgSwVipReward> *v3; // rax
  const std::pair<const int,CfgSwVipReward> *v4; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSwVipReward> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nRecord; // [rsp+34h] [rbp-1Ch]
  const CfgSwVipRewardMap *cfgSwBar; // [rsp+38h] [rbp-18h]

  nRecord = Player::getRecord(this->m_pPlayer, 1095);
  v1 = Answer::Singleton<CfgData>::instance();
  CfgVplan = CfgData::GetCfgVplan(v1);
  cfgSwBar = CfgVplan::GetSwVipBarRewardMap(CfgVplan);
  for ( iter._M_node = std::map<int,CfgSwVipReward>::begin(cfgSwBar)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,CfgSwVipReward>::end(cfgSwBar)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator!=(&iter, &__x) )
      break;
    if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter)->second.nType == 2 )
    {
      v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
      nRecord |= 1 << (LOBYTE(v3->first) - 1);
      v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSwVipReward>>::operator->(&iter);
      nRecord ^= 1 << (LOBYTE(v4->first) - 1);
    }
  }
  Player::updateRecord(this->m_pPlayer, 1095, nRecord);
}


#####################################
int32_t __cdecl CVplan::OnGetSgGameApp(CVplan *const this, Answer::NetPacket *inPacket)
{
  bool v3; // al
  bool v4; // r12
  CfgData *v5; // rax
  int nType; // eax
  int32_t ContinueLoginCount; // eax
  int32_t v8; // eax
  MemChrBagVector *p_vRewards; // rbx
  CExtCharBag *Bag; // rax
  CWan360 *Wan360; // rax
  int64_t v12; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v16; // rax
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  int32_t Index; // [rsp+1Ch] [rbp-34h]
  CfgSgGameApp *Reward; // [rsp+20h] [rbp-30h]
  int32_t OldRecord; // [rsp+28h] [rbp-28h]
  int32_t NewRecord; // [rsp+2Ch] [rbp-24h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Player::GetPlatform((const Player *const)&__lhs);
  v3 = std::operator!=<char>(&__lhs, "sogou") || std::operator!=<char>(&this->m_strSGPf, "hz");
  v4 = v3;
  std::string::~string(&__lhs);
  if ( v4 )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v5 = Answer::Singleton<CfgData>::instance();
  Reward = CfgData::GetSoGouGameApp(v5, Index);
  if ( !Reward )
    return 2;
  nType = Reward->nType;
  if ( nType == 2 )
  {
    ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
    if ( ContinueLoginCount < Reward->nCondition )
      return 2;
  }
  else if ( nType > 2 )
  {
    if ( nType == 3 )
    {
      v8 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
      if ( v8 < Reward->nCondition )
        return 2;
    }
    else if ( nType != 4 )
    {
      return 2;
    }
  }
  else if ( nType != 1 )
  {
    return 2;
  }
  OldRecord = Player::getRecord(this->m_pPlayer, 1091);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  p_vRewards = &Reward->vRewards;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, p_vRewards, ITEM_CHANGE_REASON::ICR_SG_GAME_APP) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1091, NewRecord);
  CVplan::SendSgGameAppInfo(this);
  Wan360 = Player::GetWan360(this->m_pPlayer);
  CWan360::SendGameAppIcon(Wan360);
  CVplan::SendSgDownLoadIcon(this);
  v12 = Index;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v16 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v16, ConnId, GateIndex, Proc, v12);
  return 0;
}


#####################################
int32_t __cdecl CVplan::OnGetXunLeiReward(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  int32_t Index; // [rsp+1Ch] [rbp-24h]
  XunLeiCfg *pCfg; // [rsp+20h] [rbp-20h]
  int32_t OldRecord; // [rsp+28h] [rbp-18h]
  int NewRecord; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket )
    return 2;
  Index = Answer::NetPacket::readInt32(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetXunLeiCfg(v3, Index);
  if ( !pCfg )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1156);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  if ( this->m_XlNxLevel < pCfg->nCondition )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pCfg->vRewards, ITEM_CHANGE_REASON::ICR_XUN_LEI) )
    return 2;
  Player::updateRecord(this->m_pPlayer, 1156, NewRecord);
  CVplan::SendXunLeiIcon(this);
  CVplan::SendXunLieInfo(this);
  return 0;
}


#####################################
void __cdecl CVplan::SendXunLieInfo(CVplan *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t Record; // eax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  std::string __lhs; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "niuxyx");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D16u);
      if ( packet )
      {
        Answer::NetPacket::writeInt32(packet, this->m_XlNxLevel);
        Record = Player::getRecord(this->m_pPlayer, 1156);
        Answer::NetPacket::writeInt32(packet, Record);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v7 = Player::getConnId(this->m_pPlayer);
        v8 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v8, v7, GateIndex, packet);
      }
    }
  }
}


#####################################
void __cdecl CVplan::SendSgGameAppInfo(CVplan *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t ContinueLoginCount; // edx
  int32_t Record; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D15u);
    if ( packet )
    {
      ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, ContinueLoginCount);
      Answer::NetPacket::writeInt32(packet, this->m_SgHallLevel);
      Record = Player::getRecord(this->m_pPlayer, 1091);
      Answer::NetPacket::writeInt32(packet, Record);
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
int32_t __cdecl CVplan::HaveSgGameAppReward(CVplan *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const CfgSgGameAppMap *SgGameAppMap; // rax
  const std::pair<const int,CfgSgGameApp> *v4; // rax
  int nType; // eax
  int32_t ContinueLoginCount; // ebx
  int32_t v7; // ebx
  CfgSgGameAppMap SgGameApp; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSgGameApp> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSgGameApp> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t Count; // [rsp+58h] [rbp-18h]
  int32_t Record; // [rsp+5Ch] [rbp-14h]

  if ( std::operator!=<char>(&this->m_strSGPf, "hz") )
    return 0;
  Count = 0;
  Record = Player::getRecord(this->m_pPlayer, 1091);
  v2 = Answer::Singleton<CfgData>::instance();
  SgGameAppMap = CfgData::GetSgGameAppMap(v2);
  std::map<int,CfgSgGameApp>::map(&SgGameApp, SgGameAppMap);
  for ( it._M_node = std::map<int,CfgSgGameApp>::begin(&SgGameApp)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgSgGameApp>::end(&SgGameApp)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator!=(&it, &__x) )
      break;
    v4 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator->(&it);
    if ( ((Record >> (LOBYTE(v4->first) - 1)) & 1) == 0 )
    {
      nType = std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator->(&it)->second.nType;
      switch ( nType )
      {
        case 2:
          ContinueLoginCount = Player::GetContinueLoginCount(this->m_pPlayer);
          if ( ContinueLoginCount >= std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator->(&it)->second.nCondition )
            ++Count;
          break;
        case 3:
          v7 = (*((__int64 (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer);
          if ( v7 >= std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator->(&it)->second.nCondition )
            ++Count;
          break;
        case 1:
          ++Count;
          break;
      }
    }
  }
  v1 = Count;
  std::map<int,CfgSgGameApp>::~map(&SgGameApp);
  return v1;
}


#####################################
bool __cdecl CVplan::HaveSgDownLoadGift(CVplan *const this)
{
  CfgData *v1; // rax
  const CfgSgGameAppMap *SgGameAppMap; // rax
  const std::pair<const int,CfgSgGameApp> *v3; // rax
  bool v4; // bl
  CfgSgGameAppMap SgGameApp; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSgGameApp> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgSgGameApp> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t Count; // [rsp+58h] [rbp-18h]
  int32_t Record; // [rsp+5Ch] [rbp-14h]

  Count = 0;
  Record = Player::getRecord(this->m_pPlayer, 1091);
  v1 = Answer::Singleton<CfgData>::instance();
  SgGameAppMap = CfgData::GetSgGameAppMap(v1);
  std::map<int,CfgSgGameApp>::map(&SgGameApp, SgGameAppMap);
  for ( it._M_node = std::map<int,CfgSgGameApp>::begin(&SgGameApp)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,CfgSgGameApp>::end(&SgGameApp)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator->(&it)->second.nType == 4 )
    {
      v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgSgGameApp>>::operator->(&it);
      if ( ((Record >> (LOBYTE(v3->first) - 1)) & 1) == 0 )
      {
        v4 = 1;
        goto LABEL_8;
      }
    }
  }
  v4 = 0;
LABEL_8:
  std::map<int,CfgSgGameApp>::~map(&SgGameApp);
  return v4;
}


#####################################
void __cdecl CVplan::SendSgDownLoadIcon(CVplan *const this)
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
    if ( !std::operator!=<char>(&__lhs, "sogou") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    CVplan::getSgDownLoadIconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
void __cdecl CVplan::GetSgDownLoadIocnState(CVplan *const this, IconStateList *const IconList)
{
  char v2; // bl
  bool v3; // al
  bool v4; // r12
  std::string __lhs; // [rsp+10h] [rbp-50h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-40h] BYREF

  v2 = 0;
  v3 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = 1;
    if ( !std::operator!=<char>(&__lhs, "sogou") )
      v3 = 0;
  }
  v4 = v3;
  if ( v2 )
    std::string::~string(&__lhs);
  if ( !v4 )
  {
    CVplan::getSgDownLoadIconStu(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
  }
}


#####################################
void __cdecl CVplan::GetXunLeiIconState(CVplan *const this, IconStateList *const IconList)
{
  char v2; // bl
  bool v3; // al
  bool v4; // r12
  std::string __lhs; // [rsp+10h] [rbp-90h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-80h] BYREF
  ShowIcon v7; // [rsp+40h] [rbp-60h] BYREF
  ShowIcon v8; // [rsp+60h] [rbp-40h] BYREF

  v2 = 0;
  v3 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v2 = 1;
    if ( !std::operator!=<char>(&__lhs, "niuxyx") )
      v3 = 0;
  }
  v4 = v3;
  if ( v2 )
    std::string::~string(&__lhs);
  if ( !v4 )
  {
    CVplan::GetXunLeiDownlondIcon(&__x, this);
    std::list<ShowIcon>::push_back(IconList, &__x);
    CVplan::GetXunLeiDaTingIcon(&v7, this);
    std::list<ShowIcon>::push_back(IconList, &v7);
    CVplan::GetXunLeiVipIcon(&v8, this);
    std::list<ShowIcon>::push_back(IconList, &v8);
  }
}


#####################################
void __cdecl CVplan::SendXunLeiIcon(CVplan *const this)
{
  char v1; // bl
  bool v2; // al
  bool v3; // r12
  std::string __lhs; // [rsp+10h] [rbp-90h] BYREF
  ShowIcon icon; // [rsp+20h] [rbp-80h] BYREF
  ShowIcon v6; // [rsp+40h] [rbp-60h] BYREF
  ShowIcon v7; // [rsp+60h] [rbp-40h] BYREF

  v1 = 0;
  v2 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = 1;
    if ( !std::operator!=<char>(&__lhs, "niuxyx") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    CVplan::GetXunLeiDownlondIcon(&icon, this);
    Player::SendIconState(this->m_pPlayer, &icon);
    CVplan::GetXunLeiDaTingIcon(&v6, this);
    Player::SendIconState(this->m_pPlayer, &v6);
    CVplan::GetXunLeiVipIcon(&v7, this);
    Player::SendIconState(this->m_pPlayer, &v7);
  }
}


#####################################
bool __cdecl CVplan::IsGetAllXunLeiReward(CVplan *const this, int32_t Type)
{
  CfgData *v2; // rax
  XunLeiCfgMap *XunLeiTable; // rax
  std::pair<const int,XunLeiCfg> *v4; // rax
  bool v5; // bl
  XunLeiCfgMap XunLieCfgTable; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t Record; // [rsp+5Ch] [rbp-14h]

  v2 = Answer::Singleton<CfgData>::instance();
  XunLeiTable = CfgData::GetXunLeiTable(v2);
  std::map<int,XunLeiCfg>::map(&XunLieCfgTable, XunLeiTable);
  for ( it._M_node = std::map<int,XunLeiCfg>::begin(&XunLieCfgTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,XunLeiCfg>::end(&XunLieCfgTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it)->second.nType == Type )
    {
      Record = Player::getRecord(this->m_pPlayer, 1156);
      v4 = std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it);
      if ( ((Record >> (LOBYTE(v4->first) - 1)) & 1) == 0 )
      {
        v5 = 0;
        goto LABEL_8;
      }
    }
  }
  v5 = 1;
LABEL_8:
  std::map<int,XunLeiCfg>::~map(&XunLieCfgTable);
  return v5;
}


#####################################
int32_t __cdecl CVplan::HaveXunLeiVipReward(CVplan *const this)
{
  CfgData *v1; // rax
  XunLeiCfgMap *XunLeiTable; // rax
  int32_t m_XlNxLevel; // ebx
  std::pair<const int,XunLeiCfg> *v4; // rax
  int32_t v5; // ebx
  XunLeiCfgMap XunLieCfgTable; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,XunLeiCfg> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t Count; // [rsp+58h] [rbp-18h]
  int32_t Record; // [rsp+5Ch] [rbp-14h]

  Count = 0;
  v1 = Answer::Singleton<CfgData>::instance();
  XunLeiTable = CfgData::GetXunLeiTable(v1);
  std::map<int,XunLeiCfg>::map(&XunLieCfgTable, XunLeiTable);
  for ( it._M_node = std::map<int,XunLeiCfg>::begin(&XunLieCfgTable)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator++(&it, 0) )
  {
    __x._M_node = std::map<int,XunLeiCfg>::end(&XunLieCfgTable)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator!=(&it, &__x) )
      break;
    if ( std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it)->second.nType == 3 )
    {
      m_XlNxLevel = this->m_XlNxLevel;
      if ( m_XlNxLevel >= std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it)->second.nCondition )
      {
        Record = Player::getRecord(this->m_pPlayer, 1156);
        v4 = std::_Rb_tree_iterator<std::pair<int const,XunLeiCfg>>::operator->(&it);
        if ( ((Record >> (LOBYTE(v4->first) - 1)) & 1) == 0 )
          ++Count;
      }
    }
  }
  v5 = Count;
  std::map<int,XunLeiCfg>::~map(&XunLieCfgTable);
  return v5;
}


#####################################
int32_t __cdecl CVplan::OnGetLuDaShiVipGift(CVplan *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CExtOperateLimit *OperateLimit; // rax
  CExtCharBag *Bag; // rax
  CExtOperateLimit *v6; // rax
  int32_t nIndex; // [rsp+1Ch] [rbp-24h]
  LuDaShiVip *pReward; // [rsp+20h] [rbp-20h]
  int32_t nCondition; // [rsp+2Ch] [rbp-14h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pReward = CfgData::GetLaDaShiHuiYuan(v3, nIndex);
  if ( !pReward )
    return 2;
  nCondition = this->m_PlatformVip;
  if ( pReward->nVipType == 2 )
    nCondition = this->m_PlatformSuperVip;
  if ( pReward->nCondition > nCondition || pReward->nMaxCondition < nCondition )
    return 2;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, nIndex + 1551) > 0 )
    return 2;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pReward->Rewards, ITEM_CHANGE_REASON::ICR_YY_VIP) )
    return 2;
  v6 = Player::GetOperateLimit(this->m_pPlayer);
  CExtOperateLimit::AddLimitCount(v6, nIndex + 1551, 1);
  CVplan::SendLuDaShiVipInfo(this);
  CVplan::SendLuDaShiIcon(this);
  return 0;
}


#####################################
void __cdecl CVplan::SendLuDaShiVipInfo(CVplan *const this)
{
  char v1; // bl
  bool v2; // al
  bool v3; // r12
  int8_t ConnId; // bl
  GameService *v5; // rax
  CfgData *v6; // rax
  int8_t v7; // al
  const std::pair<const int,LuDaShiVip> *v8; // rax
  int8_t Record; // al
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v12; // bl
  GameService *v13; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,LuDaShiVip> > iter; // [rsp+10h] [rbp-60h] BYREF
  std::string __lhs; // [rsp+20h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,LuDaShiVip> > __x; // [rsp+30h] [rbp-40h] BYREF
  Answer::NetPacket *packet; // [rsp+40h] [rbp-30h]
  const LuDaShiVipMap *LuDaShiMap; // [rsp+48h] [rbp-28h]

  v1 = 0;
  v2 = 1;
  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = 1;
    if ( !std::operator!=<char>(&__lhs, "taojike") )
      v2 = 0;
  }
  v3 = v2;
  if ( v1 )
    std::string::~string(&__lhs);
  if ( !v3 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v5 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v5, ConnId, Answer::PackType::PACK_DISPATCH, 0x2D1Au);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_PlatformVip);
      Answer::NetPacket::writeInt32(packet, this->m_PlatformSuperVip);
      v6 = Answer::Singleton<CfgData>::instance();
      LuDaShiMap = CfgData::GetLaDaShiHuiYuanMap(v6);
      v7 = std::map<int,LuDaShiVip>::size(LuDaShiMap);
      Answer::NetPacket::writeInt8(packet, v7);
      for ( iter._M_node = std::map<int,LuDaShiVip>::begin(LuDaShiMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator++(&iter) )
      {
        __x._M_node = std::map<int,LuDaShiVip>::end(LuDaShiMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator!=(&iter, &__x) )
          break;
        v8 = std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator->(&iter);
        Record = Player::getRecord(this->m_pPlayer, v8->first + 1551);
        Answer::NetPacket::writeInt8(packet, Record);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v12 = Player::getConnId(this->m_pPlayer);
      v13 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v13, v12, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CVplan::HaveLuDaShiVipLeftGift(CVplan *const this)
{
  CfgData *v2; // rax
  const std::pair<const int,LuDaShiVip> *v3; // rax
  int32_t v4; // ebx
  CExtOperateLimit *OperateLimit; // rax
  std::_Rb_tree_const_iterator<std::pair<const int,LuDaShiVip> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,LuDaShiVip> > __x; // [rsp+20h] [rbp-40h] BYREF
  int32_t nCount; // [rsp+34h] [rbp-2Ch]
  const LuDaShiVipMap *LuDaShiMap; // [rsp+38h] [rbp-28h]
  const LuDaShiVip *stu; // [rsp+40h] [rbp-20h]
  int32_t nCondition; // [rsp+4Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  nCount = 0;
  v2 = Answer::Singleton<CfgData>::instance();
  LuDaShiMap = CfgData::GetLaDaShiHuiYuanMap(v2);
  for ( iter._M_node = std::map<int,LuDaShiVip>::begin(LuDaShiMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator++(&iter) )
  {
    __x._M_node = std::map<int,LuDaShiVip>::end(LuDaShiMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator->(&iter);
    stu = &v3->second;
    nCondition = this->m_PlatformVip;
    if ( v3->second.nVipType == 2 )
      nCondition = this->m_PlatformSuperVip;
    if ( stu->nCondition <= nCondition && stu->nMaxCondition >= nCondition )
    {
      v4 = std::_Rb_tree_const_iterator<std::pair<int const,LuDaShiVip>>::operator->(&iter)->first + 1551;
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      if ( CExtOperateLimit::GetLimitCount(OperateLimit, v4) <= 0 )
        ++nCount;
    }
  }
  return nCount;
}


#####################################
void __cdecl CVplan::GetLuDaShiIconState(CVplan *const this, IconStateList *const IconList)
{
  bool v2; // bl
  std::string __lhs; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF

  Player::GetPlatform((const Player *const)&__lhs);
  v2 = std::operator!=<char>(&__lhs, "taojike");
  std::string::~string(&__lhs);
  if ( !v2 )
  {
    if ( this->m_pPlayer )
    {
      CVplan::GetLuDaShiStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CVplan::SendLuDaShiIcon(CVplan *const this)
{
  bool v1; // bl
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string __lhs; // [rsp+30h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&__lhs);
    v1 = std::operator!=<char>(&__lhs, "taojike");
    std::string::~string(&__lhs);
    if ( !v1 )
    {
      ConnId = Player::getConnId(this->m_pPlayer);
      v3 = Answer::Singleton<GameService>::instance();
      packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CC3u);
      if ( packet )
      {
        CVplan::GetLuDaShiStu(&stu, this);
        Answer::NetPacket::writeInt32(packet, stu.nId);
        Answer::NetPacket::writeInt8(packet, stu.nState);
        Answer::NetPacket::writeInt32(packet, stu.nLeftTime);
        Answer::NetPacket::writeInt8(packet, stu.nIconLeft);
        Answer::NetPacket::writeInt32(packet, stu.nIconRight);
        Answer::NetPacket::writeInt8(packet, stu.nEffects);
        WOffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setSize(packet, WOffset);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        v6 = Player::getConnId(this->m_pPlayer);
        v7 = Answer::Singleton<GameService>::instance();
        GameService::sendPacketTo(v7, v6, GateIndex, packet);
      }
    }
  }
}


