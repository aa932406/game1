// Decompiled methods for class: CYunYingHD
// Source: gameserver.cc
// Total methods: 47

#####################################
void __cdecl CYunYingHD::~CYunYingHD(CYunYingHD *const this)
{
  CYunYingHD::~CYunYingHD(this);
  operator delete(this);
}


#####################################
void __cdecl CYunYingHD::OnLoadFromDB(CYunYingHD *const this, const PlayerDBData *const dbData)
{
  CfgData *v2; // rax
  CfgTotalChongZhi *pCfg; // [rsp+18h] [rbp-8h]

  v2 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetTotalChongZhiCfg(v2, 1);
  if ( pCfg )
    this->m_TotalChongZhiDay = pCfg->NewServerday;
}


#####################################
void __cdecl CYunYingHD::GetInterestsProtocol(CYunYingHD *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+1Ah] [rbp-16h] BYREF
  unsigned __int16 v3; // [rsp+1Ch] [rbp-14h] BYREF
  unsigned __int16 v4; // [rsp+1Eh] [rbp-12h] BYREF
  unsigned __int16 v5; // [rsp+20h] [rbp-10h] BYREF
  unsigned __int16 v6; // [rsp+22h] [rbp-Eh] BYREF
  unsigned __int16 v7; // [rsp+24h] [rbp-Ch] BYREF
  unsigned __int16 v8; // [rsp+26h] [rbp-Ah] BYREF
  unsigned __int16 v9; // [rsp+28h] [rbp-8h] BYREF
  unsigned __int16 v10; // [rsp+2Ah] [rbp-6h] BYREF
  unsigned __int16 v11; // [rsp+2Ch] [rbp-4h] BYREF
  unsigned __int16 v12; // [rsp+2Eh] [rbp-2h] BYREF

  __x = 482;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 483;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 484;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 485;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 486;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 487;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 489;
  std::list<unsigned short>::push_back(procList, &v8);
  v9 = 515;
  std::list<unsigned short>::push_back(procList, &v9);
  v10 = 518;
  std::list<unsigned short>::push_back(procList, &v10);
  v11 = 20257;
  std::list<unsigned short>::push_back(procList, &v11);
  v12 = 519;
  std::list<unsigned short>::push_back(procList, &v12);
}


#####################################
int32_t __cdecl CYunYingHD::DispatchNetDatas(CYunYingHD *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int8_t Int8; // dl

  if ( !inPacket )
    return 2;
  if ( nProcId == 487 )
    return CYunYingHD::OnGetEveryDayChongZhiGift(this, inPacket);
  if ( nProcId > 0x1E7u )
  {
    if ( nProcId == 518 )
      return CYunYingHD::OnGetMobilePhoneGift(this, inPacket);
    if ( nProcId > 0x206u )
    {
      if ( nProcId == 519 )
        return CYunYingHD::OnGetZeroBuyPetGift(this, inPacket);
      if ( nProcId == 20257 )
        return CYunYingHD::OnDBGetMobilePhoneGift(this, inPacket);
    }
    else
    {
      if ( nProcId == 489 )
        return CYunYingHD::OnGetTotalChongZhi(this, inPacket);
      if ( nProcId == 515 )
        CYunYingHD::SendTotalChongZhiInfo(this);
    }
  }
  else if ( nProcId == 484 )
  {
    CYunYingHD::SendTeHuiInfo(this);
  }
  else if ( nProcId > 0x1E4u )
  {
    if ( nProcId == 485 )
      return CYunYingHD::OnGetBuyTeHuiItem(this, inPacket);
    if ( nProcId == 486 )
    {
      Int8 = Answer::NetPacket::readInt8(inPacket);
      CYunYingHD::SendEveryDayChongZhiInfo(this, Int8);
    }
  }
  else
  {
    if ( nProcId == 482 )
      return CYunYingHD::OnGetShouChongReward(this, inPacket);
    if ( nProcId == 483 )
      CYunYingHD::SendShouChongInfo(this);
  }
  return 0;
}


#####################################
void __cdecl CYunYingHD::OnCleanUp(CYunYingHD *const this)
{
  this->m_TotalChongZhiDay = 0;
  this->m_nLastTick = 0;
  this->m_nLastTeHui = 0;
}


#####################################
void __cdecl CYunYingHD::OnUpdate(CYunYingHD *const this, int64_t curTick)
{
  CfgData *v2; // rax
  int32_t nMailId; // r12d
  CharId_t Cid; // rbx
  DBService *v5; // rax
  MemChrBag mailItem; // [rsp+20h] [rbp-50h] BYREF
  std::string Param; // [rsp+40h] [rbp-30h] BYREF
  char v8; // [rsp+4Bh] [rbp-25h] BYREF
  int32_t now; // [rsp+4Ch] [rbp-24h]
  int32_t EndTime; // [rsp+50h] [rbp-20h]
  int32_t BackTime; // [rsp+54h] [rbp-1Ch]
  const ZeroBuyPetCfg *pCfg; // [rsp+58h] [rbp-18h]

  if ( curTick - this->m_nLastTick > 999 )
  {
    this->m_nLastTick = curTick;
    CYunYingHD::checkTeHuiTime(this);
    if ( this->m_pPlayer )
    {
      now = Unit::getNow(this->m_pPlayer);
      EndTime = Player::getRecord(this->m_pPlayer, 37502);
      if ( EndTime > 0 && EndTime < now )
      {
        Player::updateRecord(this->m_pPlayer, 37502, 0);
        CYunYingHD::SendZeroBuyPetIcon(this);
      }
      BackTime = Player::getRecord(this->m_pPlayer, 37503);
      if ( BackTime > 0 && BackTime < now )
      {
        v2 = Answer::Singleton<CfgData>::instance();
        pCfg = CfgData::GetZeroBuyPetCfg(v2);
        if ( pCfg )
        {
          *(_QWORD *)&mailItem.itemId = 0x400000002LL;
          memset(&mailItem.itemCount, 0, 24);
          mailItem.itemCount = pCfg->nGold;
          std::allocator<char>::allocator(&v8);
          std::string::string(&Param, &unk_8F630F);
          nMailId = pCfg->nMailId;
          Cid = Player::getCid(this->m_pPlayer);
          v5 = Answer::Singleton<DBService>::instance();
          DBService::OnSendSysMail(v5, 0, Cid, nMailId, &mailItem, ITEM_CHANGE_REASON::ICR_ZERO_BY_PET, &Param, 0);
          std::string::~string(&Param);
          std::allocator<char>::~allocator(&v8);
        }
        Player::updateRecord(this->m_pPlayer, 37503, 0);
      }
    }
  }
}


#####################################
void __cdecl CYunYingHD::OnDaySwitch(CYunYingHD *const this, int32_t nDiffDays)
{
  CfgData *v2; // rax
  CExtOperateLimit *OperateLimit; // rax
  int32_t LimitCount; // eax
  int32_t Record; // eax
  CExtOperateLimit *v7; // rax
  std::string platform; // [rsp+10h] [rbp-20h] BYREF
  const CfgSuperMember *pCfg; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    CYunYingHD::SendEveryDayChongZhiInfo(this, 3);
    CYunYingHD::SendEveryDayChongZhiInfo(this, 2);
    CYunYingHD::SendEveryDayChongZhiIcon(this, 3);
    CYunYingHD::SendEveryDayChongZhiIcon(this, 2);
    CYunYingHD::SendTotalChongZhiIcon(this);
    Player::GetPlatform((const Player *const)&platform);
    v2 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetSuperMember(v2, &platform);
    std::string::~string(&platform);
    if ( pCfg )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      LimitCount = CExtOperateLimit::GetLimitCount(OperateLimit, 1114);
      if ( Answer::DayTime::monthdiff(LimitCount) > 0 )
      {
        Record = Player::getRecord(this->m_pPlayer, 1115);
        if ( Record < pCfg->nGold )
        {
          v7 = Player::GetOperateLimit(this->m_pPlayer);
          CExtOperateLimit::Reset(v7, 1115);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CYunYingHD::OnGetShouChongReward(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CfgShouChongTable *ShouChongLiBao; // rax
  Job_t Job; // r12
  int32_t Time; // r15d
  CharId_t nCreaterId; // r12
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v11; // rax
  int v12; // r12d
  CExtCharBag *Bag; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v15; // rax
  CExtCharMysteryGift *CharMysteryGift; // rax
  int8_t v17; // bl
  DBService *v18; // rax
  int32_t nBaseId; // [rsp+4Ch] [rbp-154h]
  MemEquip equip; // [rsp+60h] [rbp-140h] BYREF
  MemChrBag chrbag; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<const CfgEquipItem*,std::vector<CfgEquipItem> > it; // [rsp+C0h] [rbp-E0h] BYREF
  LogDailyGift logDailyGift; // [rsp+D0h] [rbp-D0h] BYREF
  MemEquipVector vEquip; // [rsp+F0h] [rbp-B0h] BYREF
  MemChrBagVector addItemVt; // [rsp+110h] [rbp-90h] BYREF
  __gnu_cxx::__normal_iterator<const CfgEquipItem*,std::vector<CfgEquipItem> > __rhs; // [rsp+130h] [rbp-70h] BYREF
  std::string p_name; // [rsp+140h] [rbp-60h] BYREF
  int8_t nIndex; // [rsp+157h] [rbp-49h]
  int32_t nRecord; // [rsp+158h] [rbp-48h]
  int32_t nNewRecord; // [rsp+15Ch] [rbp-44h]
  const CfgShouChong *pCfg; // [rsp+160h] [rbp-40h]
  const MemChrEquipBagVector *Item; // [rsp+168h] [rbp-38h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  nIndex = Answer::NetPacket::readInt8(inPacket);
  nRecord = Player::getRecord(this->m_pPlayer, 1026);
  nNewRecord = nRecord | (1 << (nIndex - 1));
  if ( nRecord == nNewRecord )
    return 2;
  v3 = Answer::Singleton<CfgData>::instance();
  ShouChongLiBao = CfgData::GetShouChongLiBao(v3);
  pCfg = CfgShouChongTable::GetShouChong(ShouChongLiBao, nIndex);
  if ( !pCfg )
    return 2;
  if ( Player::GetTotalPayGold(this->m_pPlayer) < pCfg->nGold )
    return 2;
  Item = &pCfg->vReward;
  std::vector<MemChrBag>::vector(&addItemVt);
  std::vector<MemEquip>::vector(&vEquip);
  if ( !std::vector<CfgEquipItem>::empty(Item) )
  {
    for ( it._M_current = std::vector<CfgEquipItem>::begin(Item)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator++(&it) )
    {
      __rhs._M_current = std::vector<CfgEquipItem>::end(Item)._M_current;
      if ( !__gnu_cxx::operator!=<CfgEquipItem const*,std::vector<CfgEquipItem>>(&it, &__rhs) )
        break;
      Job = Player::getJob(this->m_pPlayer);
      if ( Job == __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->job
        || !__gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->type;
        chrbag.itemCount = __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->bind;
        chrbag.endTime = 0;
        if ( chrbag.itemClass == 2 )
        {
          Time = __gnu_cxx::__normal_iterator<CfgEquipItem const*,std::vector<CfgEquipItem>>::operator->(&it)->star;
          Player::getName((const Player *const)&p_name);
          nCreaterId = Player::getCid(this->m_pPlayer);
          Sid = Player::getSid(this->m_pPlayer);
          nBaseId = chrbag.itemId;
          ConnId = Player::getConnId(this->m_pPlayer);
          v11 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v11, ConnId, 601, nBaseId, Sid, nCreaterId, &p_name, 0, 0, Time, 0, 0);
          std::string::~string(&p_name);
          if ( equip.base <= 0 )
            goto LABEL_20;
          if ( equip.id > 0 )
          {
            chrbag.srcId = equip.id;
            std::vector<MemEquip>::push_back(&vEquip, &equip);
            v12 = 1;
          }
          else
          {
LABEL_20:
            v2 = 0;
            v12 = 0;
          }
          MemEquip::~MemEquip(&equip);
          if ( !v12 )
            goto LABEL_31;
        }
        std::vector<MemChrBag>::push_back(&addItemVt, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addItemVt, ITEM_CHANGE_REASON::ICR_SEVEN_LOGIN_REWARD) )
  {
    v2 = 2;
  }
  else
  {
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v15 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v15, m_pPlayer, &vEquip);
    }
    Player::updateRecord(this->m_pPlayer, 1026, nNewRecord);
    CYunYingHD::GongGao(this, pCfg->nBroadcast);
    CYunYingHD::SendShouChongIcon(this);
    CYunYingHD::SendShouChongInfo(this);
    CYunYingHD::SendEveryDayChongZhiIcon(this, 3);
    CharMysteryGift = Player::GetCharMysteryGift(this->m_pPlayer);
    CExtCharMysteryGift::SendMysteryGiftInfo(CharMysteryGift, 1);
    memset(&logDailyGift, 0, sizeof(logDailyGift));
    logDailyGift.cid = Player::getCid(this->m_pPlayer);
    logDailyGift.type = 1;
    logDailyGift.giftid = 0;
    logDailyGift.time = Unit::getNow(this->m_pPlayer);
    v17 = Player::getConnId(this->m_pPlayer);
    v18 = Answer::Singleton<DBService>::instance();
    DBService::InsertDailyGiftLog(v18, v17, &logDailyGift);
    v2 = 0;
  }
LABEL_31:
  std::vector<MemEquip>::~vector(&vEquip);
  std::vector<MemChrBag>::~vector(&addItemVt);
  return v2;
}


#####################################
int32_t __cdecl CYunYingHD::OnGetBuyTeHuiItem(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int32_t v4; // r12d
  Job_t Job; // r12
  int32_t Time; // r15d
  CharId_t nCreaterId; // r12
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v11; // rax
  int v12; // r12d
  CExtCharBag *Bag; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v15; // rax
  int8_t v16; // bl
  int32_t GongGaoId; // edx
  int32_t nBaseId; // [rsp+4Ch] [rbp-154h]
  MemEquip equip; // [rsp+60h] [rbp-140h] BYREF
  MemChrBag chrbag; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > it_0; // [rsp+C0h] [rbp-E0h] BYREF
  std::_List_iterator<CfgGongGao> it; // [rsp+D0h] [rbp-D0h] BYREF
  MemEquipVector vEquip; // [rsp+E0h] [rbp-C0h] BYREF
  MemChrBagVector addItemVt; // [rsp+100h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > __rhs; // [rsp+120h] [rbp-80h] BYREF
  std::string p_name; // [rsp+130h] [rbp-70h] BYREF
  std::_List_iterator<CfgGongGao> __x; // [rsp+140h] [rbp-60h] BYREF
  int8_t Index; // [rsp+14Fh] [rbp-51h]
  NewServerFavorable *pCfg; // [rsp+150h] [rbp-50h]
  int32_t OldRecord; // [rsp+158h] [rbp-48h]
  int32_t NewRecord; // [rsp+15Ch] [rbp-44h]
  int64_t HaveMoney; // [rsp+160h] [rbp-40h]
  MemChrEquipBagVector *Item; // [rsp+168h] [rbp-38h]

  if ( !inPacket || !this->m_pPlayer )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetNewServerFavorable(v3, Index);
  if ( !pCfg )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1027);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  v4 = Player::getCreateTime(this->m_pPlayer) + pCfg->nLimitTime;
  if ( v4 < Unit::getNow(this->m_pPlayer) )
    return 2;
  if ( pCfg->NeedGold <= 0 )
    return 2;
  HaveMoney = Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD);
  if ( pCfg->NeedGold > HaveMoney )
    return 2;
  Item = &pCfg->ItemVector;
  std::vector<MemChrBag>::vector(&addItemVt);
  std::vector<MemEquip>::vector(&vEquip);
  if ( !std::vector<CfgEquipItem>::empty(Item) )
  {
    for ( it_0._M_current = std::vector<CfgEquipItem>::begin(Item)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator++(&it_0) )
    {
      __rhs._M_current = std::vector<CfgEquipItem>::end(Item)._M_current;
      if ( !__gnu_cxx::operator!=<CfgEquipItem *,std::vector<CfgEquipItem>>(&it_0, &__rhs) )
        break;
      Job = Player::getJob(this->m_pPlayer);
      if ( Job == __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->job
        || !__gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->type;
        chrbag.itemCount = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->bind;
        if ( chrbag.itemClass == 2 )
        {
          Time = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->star;
          Player::getName((const Player *const)&p_name);
          nCreaterId = Player::getCid(this->m_pPlayer);
          Sid = Player::getSid(this->m_pPlayer);
          nBaseId = chrbag.itemId;
          ConnId = Player::getConnId(this->m_pPlayer);
          v11 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v11, ConnId, 602, nBaseId, Sid, nCreaterId, &p_name, 0, 0, Time, 0, 0);
          std::string::~string(&p_name);
          if ( equip.base <= 0 )
            goto LABEL_24;
          if ( equip.id > 0 )
          {
            chrbag.srcId = equip.id;
            std::vector<MemEquip>::push_back(&vEquip, &equip);
            v12 = 1;
          }
          else
          {
LABEL_24:
            v2 = 0;
            v12 = 0;
          }
          MemEquip::~MemEquip(&equip);
          if ( !v12 )
            goto LABEL_46;
        }
        std::vector<MemChrBag>::push_back(&addItemVt, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addItemVt, ITEM_CHANGE_REASON::ICR_NEW_SERVER_TE_HUI) )
  {
    v2 = 2;
  }
  else if ( !Player::DecCurrency(
               this->m_pPlayer,
               CURRENCY_TYPE::CURRENCY_GOLD,
               pCfg->NeedGold,
               CURRENCY_CHANGE_REASON::GCR_BUY_TE_HUI_LI_BAO,
               Index) )
  {
    v2 = 2;
  }
  else
  {
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v15 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v15, m_pPlayer, &vEquip);
    }
    Player::updateRecord(this->m_pPlayer, 1027, NewRecord);
    for ( it._M_node = std::list<CfgGongGao>::begin(&pCfg->GongGaoInfo)._M_node;
          ;
          std::_List_iterator<CfgGongGao>::operator++(&it) )
    {
      __x._M_node = std::list<CfgGongGao>::end(&pCfg->GongGaoInfo)._M_node;
      if ( !std::_List_iterator<CfgGongGao>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<CfgGongGao>::operator->(&it)->Job )
      {
        v16 = std::_List_iterator<CfgGongGao>::operator->(&it)->Job;
        if ( v16 != Player::getJob(this->m_pPlayer) )
          continue;
      }
      GongGaoId = std::_List_iterator<CfgGongGao>::operator->(&it)->GongGaoId;
      CYunYingHD::GongGao(this, GongGaoId);
    }
    CYunYingHD::SendTeHuiInfo(this);
    CYunYingHD::SendTeHuiIcon(this);
    v2 = 0;
  }
LABEL_46:
  std::vector<MemEquip>::~vector(&vEquip);
  std::vector<MemChrBag>::~vector(&addItemVt);
  return v2;
}


#####################################
int32_t __cdecl CYunYingHD::OnGetEveryDayChongZhiGift(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CFestivalDoubleEleven *v3; // rax
  CKaiFuHuoDong *v4; // rax
  CKaiFuHuoDong *v5; // rax
  CKaiFuHuoDong *v6; // rax
  CfgData *v7; // rax
  Job_t Job; // r12
  int32_t Time; // r15d
  CharId_t nCreaterId; // r12
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v14; // rax
  int v15; // r12d
  CExtCharBag *Bag; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v18; // rax
  int8_t v19; // bl
  int32_t GongGaoId; // edx
  int8_t v22; // bl
  DBService *v23; // rax
  int32_t nBaseId; // [rsp+4Ch] [rbp-184h]
  MemEquip equip; // [rsp+60h] [rbp-170h] BYREF
  MemChrBag chrbag; // [rsp+A0h] [rbp-130h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > it_0; // [rsp+C0h] [rbp-110h] BYREF
  LogDailyGift logDailyGift; // [rsp+D0h] [rbp-100h] BYREF
  std::_List_iterator<CfgGongGao> it; // [rsp+F0h] [rbp-E0h] BYREF
  MemEquipVector vEquip; // [rsp+100h] [rbp-D0h] BYREF
  MemChrBagVector addItemVt; // [rsp+120h] [rbp-B0h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > __rhs; // [rsp+140h] [rbp-90h] BYREF
  std::string p_name; // [rsp+150h] [rbp-80h] BYREF
  std::_List_iterator<CfgGongGao> __x; // [rsp+160h] [rbp-70h] BYREF
  int8_t Index; // [rsp+172h] [rbp-5Eh]
  int8_t nType; // [rsp+173h] [rbp-5Dh]
  int32_t nRecordId; // [rsp+174h] [rbp-5Ch]
  CfgEverydayChongZhi *pCfg; // [rsp+178h] [rbp-58h]
  int32_t TodayPayed; // [rsp+184h] [rbp-4Ch]
  int32_t OldRecord; // [rsp+188h] [rbp-48h]
  int32_t NewRecord; // [rsp+18Ch] [rbp-44h]
  MemChrEquipBagVector *Item; // [rsp+190h] [rbp-40h]
  int32_t nKaiFuHuoDongDay; // [rsp+198h] [rbp-38h]
  int32_t nKaiFuHuoDongDay_0; // [rsp+19Ch] [rbp-34h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  nType = Answer::NetPacket::readInt8(inPacket);
  nRecordId = 2011;
  switch ( nType )
  {
    case 2:
      v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
      if ( !CFestivalDoubleEleven::IsOpen(v3, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE) )
        return 10002;
      nRecordId = 2033;
      break;
    case 1:
      v4 = Answer::Singleton<CKaiFuHuoDong>::instance();
      if ( CKaiFuHuoDong::GetDaysFromServerStart(v4) > 2 )
        return 10002;
      break;
    case 4:
      v5 = Answer::Singleton<CKaiFuHuoDong>::instance();
      nKaiFuHuoDongDay = CKaiFuHuoDong::GetDaysFromServerStart(v5);
      if ( nKaiFuHuoDongDay <= 2 || nKaiFuHuoDongDay > 7 )
        return 10002;
      break;
    default:
      v6 = Answer::Singleton<CKaiFuHuoDong>::instance();
      nKaiFuHuoDongDay_0 = CKaiFuHuoDong::GetDaysFromServerStart(v6);
      if ( nKaiFuHuoDongDay_0 <= 7 )
        return 10002;
      if ( nType != 3 )
        return 10002;
      break;
  }
  v7 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetEveryDayChongZhiCfg(v7, nType, Index);
  if ( !pCfg )
    return 2;
  TodayPayed = Player::GetTodayPayGold(this->m_pPlayer);
  if ( pCfg->NeedGold > TodayPayed )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, nRecordId);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  Item = &pCfg->ItemVector;
  std::vector<MemChrBag>::vector(&addItemVt);
  std::vector<MemEquip>::vector(&vEquip);
  if ( !std::vector<CfgEquipItem>::empty(Item) )
  {
    for ( it_0._M_current = std::vector<CfgEquipItem>::begin(Item)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator++(&it_0) )
    {
      __rhs._M_current = std::vector<CfgEquipItem>::end(Item)._M_current;
      if ( !__gnu_cxx::operator!=<CfgEquipItem *,std::vector<CfgEquipItem>>(&it_0, &__rhs) )
        break;
      Job = Player::getJob(this->m_pPlayer);
      if ( Job == __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->job
        || !__gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->type;
        chrbag.itemCount = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->bind;
        if ( chrbag.itemClass == 2 )
        {
          Time = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->star;
          Player::getName((const Player *const)&p_name);
          nCreaterId = Player::getCid(this->m_pPlayer);
          Sid = Player::getSid(this->m_pPlayer);
          nBaseId = chrbag.itemId;
          ConnId = Player::getConnId(this->m_pPlayer);
          v14 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v14, ConnId, 604, nBaseId, Sid, nCreaterId, &p_name, 0, 0, Time, 0, 0);
          std::string::~string(&p_name);
          if ( equip.base <= 0 )
            goto LABEL_35;
          if ( equip.id > 0 )
          {
            chrbag.srcId = equip.id;
            std::vector<MemEquip>::push_back(&vEquip, &equip);
            v15 = 1;
          }
          else
          {
LABEL_35:
            v2 = 0;
            v15 = 0;
          }
          MemEquip::~MemEquip(&equip);
          if ( !v15 )
            goto LABEL_55;
        }
        std::vector<MemChrBag>::push_back(&addItemVt, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addItemVt, ITEM_CHANGE_REASON::ICR_EVERYDAY_CHONG_ZHI) )
  {
    v2 = 2;
  }
  else
  {
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v18 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v18, m_pPlayer, &vEquip);
    }
    Player::updateRecord(this->m_pPlayer, nRecordId, NewRecord);
    for ( it._M_node = std::list<CfgGongGao>::begin(&pCfg->GongGaoInfo)._M_node;
          ;
          std::_List_iterator<CfgGongGao>::operator++(&it) )
    {
      __x._M_node = std::list<CfgGongGao>::end(&pCfg->GongGaoInfo)._M_node;
      if ( !std::_List_iterator<CfgGongGao>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<CfgGongGao>::operator->(&it)->Job )
      {
        v19 = std::_List_iterator<CfgGongGao>::operator->(&it)->Job;
        if ( v19 != Player::getJob(this->m_pPlayer) )
          continue;
      }
      GongGaoId = std::_List_iterator<CfgGongGao>::operator->(&it)->GongGaoId;
      CYunYingHD::GongGao(this, GongGaoId);
    }
    CYunYingHD::SendEveryDayChongZhiInfo(this, nType);
    CYunYingHD::SendEveryDayChongZhiIcon(this, nType);
    memset(&logDailyGift, 0, sizeof(logDailyGift));
    logDailyGift.cid = Player::getCid(this->m_pPlayer);
    logDailyGift.type = 1;
    logDailyGift.giftid = Index;
    logDailyGift.time = Unit::getNow(this->m_pPlayer);
    v22 = Player::getConnId(this->m_pPlayer);
    v23 = Answer::Singleton<DBService>::instance();
    DBService::InsertDailyGiftLog(v23, v22, &logDailyGift);
    v2 = 0;
  }
LABEL_55:
  std::vector<MemEquip>::~vector(&vEquip);
  std::vector<MemChrBag>::~vector(&addItemVt);
  return v2;
}


#####################################
int32_t __cdecl CYunYingHD::OnGetTotalChongZhi(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  Job_t Job; // r12
  int32_t Time; // r15d
  CharId_t nCreaterId; // r12
  int32_t Sid; // r14d
  int8_t ConnId; // r13
  CEquipManager *v10; // rax
  int v11; // r12d
  CExtCharBag *Bag; // rax
  Player *m_pPlayer; // rbx
  CEquipManager *v14; // rax
  int8_t v15; // bl
  int32_t GongGaoId; // edx
  int32_t nBaseId; // [rsp+4Ch] [rbp-154h]
  MemEquip equip; // [rsp+60h] [rbp-140h] BYREF
  MemChrBag chrbag; // [rsp+A0h] [rbp-100h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > it_0; // [rsp+C0h] [rbp-E0h] BYREF
  std::_List_iterator<CfgGongGao> it; // [rsp+D0h] [rbp-D0h] BYREF
  MemEquipVector vEquip; // [rsp+E0h] [rbp-C0h] BYREF
  MemChrBagVector addItemVt; // [rsp+100h] [rbp-A0h] BYREF
  __gnu_cxx::__normal_iterator<CfgEquipItem*,std::vector<CfgEquipItem> > __rhs; // [rsp+120h] [rbp-80h] BYREF
  std::string p_name; // [rsp+130h] [rbp-70h] BYREF
  std::_List_iterator<CfgGongGao> __x; // [rsp+140h] [rbp-60h] BYREF
  int8_t Index; // [rsp+14Fh] [rbp-51h]
  CfgTotalChongZhi *pCfg; // [rsp+150h] [rbp-50h]
  int32_t ZhongZhiValues; // [rsp+15Ch] [rbp-44h]
  int32_t OldRecord; // [rsp+160h] [rbp-40h]
  int32_t NewRecord; // [rsp+164h] [rbp-3Ch]
  MemChrEquipBagVector *Item; // [rsp+168h] [rbp-38h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  Index = Answer::NetPacket::readInt8(inPacket);
  v3 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetTotalChongZhiCfg(v3, Index);
  if ( !pCfg )
    return 2;
  ZhongZhiValues = Player::getRecord(this->m_pPlayer, 1036);
  if ( pCfg->NeedGold > ZhongZhiValues )
    return 2;
  OldRecord = Player::getRecord(this->m_pPlayer, 1037);
  NewRecord = OldRecord | (1 << (Index - 1));
  if ( OldRecord == NewRecord )
    return 2;
  Item = &pCfg->ItemVector;
  std::vector<MemChrBag>::vector(&addItemVt);
  std::vector<MemEquip>::vector(&vEquip);
  if ( !std::vector<CfgEquipItem>::empty(Item) )
  {
    for ( it_0._M_current = std::vector<CfgEquipItem>::begin(Item)._M_current;
          ;
          __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator++(&it_0) )
    {
      __rhs._M_current = std::vector<CfgEquipItem>::end(Item)._M_current;
      if ( !__gnu_cxx::operator!=<CfgEquipItem *,std::vector<CfgEquipItem>>(&it_0, &__rhs) )
        break;
      Job = Player::getJob(this->m_pPlayer);
      if ( Job == __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->job
        || !__gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->job )
      {
        memset(&chrbag, 0, sizeof(chrbag));
        chrbag.itemId = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->id;
        chrbag.itemClass = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->type;
        chrbag.itemCount = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->count;
        chrbag.bind = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->bind;
        chrbag.endTime = 0;
        if ( chrbag.itemClass == 2 )
        {
          Time = __gnu_cxx::__normal_iterator<CfgEquipItem *,std::vector<CfgEquipItem>>::operator->(&it_0)->star;
          Player::getName((const Player *const)&p_name);
          nCreaterId = Player::getCid(this->m_pPlayer);
          Sid = Player::getSid(this->m_pPlayer);
          nBaseId = chrbag.itemId;
          ConnId = Player::getConnId(this->m_pPlayer);
          v10 = Answer::Singleton<CEquipManager>::instance();
          CEquipManager::CreateMemEquip(&equip, v10, ConnId, 606, nBaseId, Sid, nCreaterId, &p_name, 0, 0, Time, 0, 0);
          std::string::~string(&p_name);
          if ( equip.base <= 0 )
            goto LABEL_20;
          if ( equip.id > 0 )
          {
            chrbag.srcId = equip.id;
            std::vector<MemEquip>::push_back(&vEquip, &equip);
            v11 = 1;
          }
          else
          {
LABEL_20:
            v2 = 0;
            v11 = 0;
          }
          MemEquip::~MemEquip(&equip);
          if ( !v11 )
            goto LABEL_40;
        }
        std::vector<MemChrBag>::push_back(&addItemVt, &chrbag);
      }
    }
  }
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &addItemVt, ITEM_CHANGE_REASON::ICR_TOTAL_CHONG_ZHI) )
  {
    v2 = 2;
  }
  else
  {
    if ( !std::vector<MemEquip>::empty(&vEquip) )
    {
      m_pPlayer = this->m_pPlayer;
      v14 = Answer::Singleton<CEquipManager>::instance();
      CEquipManager::SendPlayerEquipInfo(v14, m_pPlayer, &vEquip);
    }
    Player::updateRecord(this->m_pPlayer, 1037, NewRecord);
    for ( it._M_node = std::list<CfgGongGao>::begin(&pCfg->GongGaoInfo)._M_node;
          ;
          std::_List_iterator<CfgGongGao>::operator++(&it) )
    {
      __x._M_node = std::list<CfgGongGao>::end(&pCfg->GongGaoInfo)._M_node;
      if ( !std::_List_iterator<CfgGongGao>::operator!=(&it, &__x) )
        break;
      if ( std::_List_iterator<CfgGongGao>::operator->(&it)->Job )
      {
        v15 = std::_List_iterator<CfgGongGao>::operator->(&it)->Job;
        if ( v15 != Player::getJob(this->m_pPlayer) )
          continue;
      }
      GongGaoId = std::_List_iterator<CfgGongGao>::operator->(&it)->GongGaoId;
      CYunYingHD::GongGao(this, GongGaoId);
    }
    CYunYingHD::SendTotalChongZhiIcon(this);
    CYunYingHD::SendTotalChongZhiInfo(this);
    v2 = 0;
  }
LABEL_40:
  std::vector<MemEquip>::~vector(&vEquip);
  std::vector<MemChrBag>::~vector(&addItemVt);
  return v2;
}


#####################################
int8_t __cdecl CYunYingHD::GetShouChongIconState(CYunYingHD *const this)
{
  CfgData *v1; // rax
  CfgShouChongTable *ShouChongLiBao; // rax
  char first; // dl
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgShouChong> > iter; // [rsp+10h] [rbp-20h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgShouChong> > __x; // [rsp+20h] [rbp-10h] BYREF
  const CfgShouChongMap *stu; // [rsp+28h] [rbp-8h]

  v1 = Answer::Singleton<CfgData>::instance();
  ShouChongLiBao = CfgData::GetShouChongLiBao(v1);
  stu = CfgShouChongTable::GetShouChongMap(ShouChongLiBao);
  for ( iter._M_node = std::map<signed char,CfgShouChong>::begin(stu)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,CfgShouChong>::end(stu)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator!=(&iter, &__x) )
      break;
    first = std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator->(&iter)->first;
    if ( CYunYingHD::GetShouChongState(this, first) <= 1 )
      return 0;
  }
  return 1;
}


#####################################
int8_t __cdecl CYunYingHD::GetShouChongState(CYunYingHD *const this, int8_t nIndex)
{
  CfgData *v2; // rax
  CfgShouChongTable *ShouChongLiBao; // rax
  const CfgShouChong *pCfg; // [rsp+10h] [rbp-20h]
  int32_t nRecord; // [rsp+18h] [rbp-18h]

  v2 = Answer::Singleton<CfgData>::instance();
  ShouChongLiBao = CfgData::GetShouChongLiBao(v2);
  pCfg = CfgShouChongTable::GetShouChong(ShouChongLiBao, nIndex);
  if ( !pCfg )
    return 0;
  if ( Player::GetTotalPayGold(this->m_pPlayer) < pCfg->nGold )
    return 0;
  nRecord = Player::getRecord(this->m_pPlayer, 1026);
  if ( nRecord == (nRecord | (1 << (nIndex - 1))) )
    return 2;
  else
    return 1;
}


#####################################
void __cdecl CYunYingHD::SendShouChongInfo(CYunYingHD *const this)
{
  CfgData *v1; // rax
  CfgShouChongTable *ShouChongLiBao; // rax
  int8_t ConnId; // bl
  GameService *v4; // rax
  int8_t v5; // al
  const std::pair<const signed char,CfgShouChong> *v6; // rax
  char first; // dl
  int8_t ShouChongState; // al
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v11; // bl
  GameService *v12; // rax
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgShouChong> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,CfgShouChong> > __x; // [rsp+20h] [rbp-30h] BYREF
  const CfgShouChongMap *stu; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    v1 = Answer::Singleton<CfgData>::instance();
    ShouChongLiBao = CfgData::GetShouChongLiBao(v1);
    stu = CfgShouChongTable::GetShouChongMap(ShouChongLiBao);
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE4u);
    if ( packet )
    {
      v5 = std::map<signed char,CfgShouChong>::size(stu);
      Answer::NetPacket::writeInt8(packet, v5);
      for ( iter._M_node = std::map<signed char,CfgShouChong>::begin(stu)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator++(&iter) )
      {
        __x._M_node = std::map<signed char,CfgShouChong>::end(stu)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator!=(&iter, &__x) )
          break;
        v6 = std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator->(&iter);
        Answer::NetPacket::writeInt8(packet, v6->first);
        first = std::_Rb_tree_const_iterator<std::pair<signed char const,CfgShouChong>>::operator->(&iter)->first;
        ShouChongState = CYunYingHD::GetShouChongState(this, first);
        Answer::NetPacket::writeInt8(packet, ShouChongState);
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
void __cdecl CYunYingHD::SendShouChongIcon(CYunYingHD *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 62) )
    {
      CYunYingHD::GetShouChongIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CYunYingHD::GetShouChongIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 62) && !CYunYingHD::GetShouChongIconState(this) )
    {
      CYunYingHD::GetShouChongIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
void __cdecl CYunYingHD::SendTeHuiInfo(CYunYingHD *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // eax
  CfgData *v4; // rax
  int32_t v5; // eax
  const std::pair<const signed char,NewServerFavorable> *v6; // rax
  const std::pair<const signed char,NewServerFavorable> *v7; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  std::_Rb_tree_const_iterator<std::pair<const signed char,NewServerFavorable> > iter; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,NewServerFavorable> > __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t nStartTime; // [rsp+28h] [rbp-28h]
  int32_t nNowTime; // [rsp+2Ch] [rbp-24h]
  Answer::NetPacket *packet; // [rsp+30h] [rbp-20h]
  const NewServerFavorableMap *cfgMap; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    nStartTime = Player::getCreateTime(this->m_pPlayer);
    nNowTime = Unit::getNow(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE5u);
    if ( packet )
    {
      Record = Player::getRecord(this->m_pPlayer, 1027);
      Answer::NetPacket::writeInt32(packet, Record);
      v4 = Answer::Singleton<CfgData>::instance();
      cfgMap = CfgData::GetNewServerFavorableCfg(v4);
      v5 = std::map<signed char,NewServerFavorable>::size(cfgMap);
      Answer::NetPacket::writeInt32(packet, v5);
      for ( iter._M_node = std::map<signed char,NewServerFavorable>::begin(cfgMap)._M_node;
            ;
            std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator++(&iter) )
      {
        __x._M_node = std::map<signed char,NewServerFavorable>::end(cfgMap)._M_node;
        if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator!=(&iter, &__x) )
          break;
        v6 = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter);
        Answer::NetPacket::writeInt8(packet, v6->first);
        v7 = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter);
        Answer::NetPacket::writeInt32(packet, nStartTime + v7->second.nLimitTime - nNowTime);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v10 = Player::getConnId(this->m_pPlayer);
      v11 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v11, v10, GateIndex, packet);
    }
  }
}


#####################################
int32_t __cdecl CYunYingHD::getTeHuiLimitTime(CYunYingHD *const this)
{
  CfgData *v2; // rax
  const std::pair<const signed char,NewServerFavorable> *v3; // rax
  const std::pair<const signed char,NewServerFavorable> *v4; // rax
  std::_Rb_tree_const_iterator<std::pair<const signed char,NewServerFavorable> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,NewServerFavorable> > __x; // [rsp+20h] [rbp-40h] BYREF
  int32_t nLimitTime; // [rsp+30h] [rbp-30h]
  int32_t nStartTime; // [rsp+34h] [rbp-2Ch]
  int32_t nNowTime; // [rsp+38h] [rbp-28h]
  int32_t OldRecord; // [rsp+3Ch] [rbp-24h]
  const NewServerFavorableMap *cfgMap; // [rsp+40h] [rbp-20h]
  int32_t NewRecord; // [rsp+48h] [rbp-18h]
  int32_t nTime; // [rsp+4Ch] [rbp-14h]

  if ( !this->m_pPlayer )
    return 0;
  nLimitTime = 0;
  nStartTime = Player::getCreateTime(this->m_pPlayer);
  nNowTime = Unit::getNow(this->m_pPlayer);
  OldRecord = Player::getRecord(this->m_pPlayer, 1027);
  v2 = Answer::Singleton<CfgData>::instance();
  cfgMap = CfgData::GetNewServerFavorableCfg(v2);
  for ( iter._M_node = std::map<signed char,NewServerFavorable>::begin(cfgMap)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator++(&iter) )
  {
    __x._M_node = std::map<signed char,NewServerFavorable>::end(cfgMap)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator!=(&iter, &__x) )
      break;
    v3 = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter);
    NewRecord = OldRecord | (1 << (v3->first - 1));
    if ( OldRecord != NewRecord )
    {
      v4 = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter);
      nTime = nStartTime + v4->second.nLimitTime - nNowTime;
      if ( nTime > 0 && (!nLimitTime || nLimitTime > nTime) )
        nLimitTime = nTime;
    }
  }
  return nLimitTime;
}


#####################################
void __cdecl CYunYingHD::checkTeHuiTime(CYunYingHD *const this)
{
  CfgData *v1; // rax
  const std::pair<const signed char,NewServerFavorable> *v2; // rax
  const std::pair<const signed char,NewServerFavorable> *v3; // rax
  std::_Rb_tree_const_iterator<std::pair<const signed char,NewServerFavorable> > iter; // [rsp+10h] [rbp-50h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const signed char,NewServerFavorable> > __x; // [rsp+20h] [rbp-40h] BYREF
  int32_t nLimitTime; // [rsp+2Ch] [rbp-34h]
  int32_t nIndex; // [rsp+30h] [rbp-30h]
  int32_t nStartTime; // [rsp+34h] [rbp-2Ch]
  int32_t nNowTime; // [rsp+38h] [rbp-28h]
  int32_t OldRecord; // [rsp+3Ch] [rbp-24h]
  const NewServerFavorableMap *cfgMap; // [rsp+40h] [rbp-20h]
  int32_t NewRecord; // [rsp+48h] [rbp-18h]
  int32_t nTime; // [rsp+4Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    nLimitTime = 0;
    nIndex = 0;
    nStartTime = Player::getCreateTime(this->m_pPlayer);
    nNowTime = Unit::getNow(this->m_pPlayer);
    OldRecord = Player::getRecord(this->m_pPlayer, 1027);
    v1 = Answer::Singleton<CfgData>::instance();
    cfgMap = CfgData::GetNewServerFavorableCfg(v1);
    for ( iter._M_node = std::map<signed char,NewServerFavorable>::begin(cfgMap)._M_node;
          ;
          std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator++(&iter) )
    {
      __x._M_node = std::map<signed char,NewServerFavorable>::end(cfgMap)._M_node;
      if ( !std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator!=(&iter, &__x) )
        break;
      v2 = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter);
      NewRecord = OldRecord | (1 << (v2->first - 1));
      if ( OldRecord != NewRecord )
      {
        v3 = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter);
        nTime = nStartTime + v3->second.nLimitTime - nNowTime;
        if ( nTime > 0 && (!nLimitTime || nLimitTime > nTime) )
        {
          nIndex = std::_Rb_tree_const_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&iter)->first;
          nLimitTime = nTime;
        }
      }
    }
    if ( this->m_nLastTeHui != nIndex )
    {
      this->m_nLastTeHui = nIndex;
      CYunYingHD::SendTeHuiIcon(this);
    }
  }
}


#####################################
void __cdecl CYunYingHD::SendTeHuiIcon(CYunYingHD *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 63) )
    {
      CYunYingHD::GetTeHuiIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CYunYingHD::GetTeHuiIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 63) && CYunYingHD::IsHaveTeHuiGift(this) )
    {
      CYunYingHD::GetTeHuiIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
bool __cdecl CYunYingHD::IsHaveTeHuiGift(CYunYingHD *const this)
{
  CfgData *v1; // rax
  NewServerFavorableMap *NewServerFavorableCfg; // rax
  std::pair<const signed char,NewServerFavorable> *v3; // rax
  bool v4; // bl
  NewServerFavorableMap CfgTeHuiMap; // [rsp+10h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,NewServerFavorable> > it; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,NewServerFavorable> > __x; // [rsp+50h] [rbp-20h] BYREF
  int32_t OldRecord; // [rsp+58h] [rbp-18h]
  int32_t NewRecord; // [rsp+5Ch] [rbp-14h]

  OldRecord = Player::getRecord(this->m_pPlayer, 1027);
  v1 = Answer::Singleton<CfgData>::instance();
  NewServerFavorableCfg = CfgData::GetNewServerFavorableCfg(v1);
  std::map<signed char,NewServerFavorable>::map(&CfgTeHuiMap, NewServerFavorableCfg);
  for ( it._M_node = std::map<signed char,NewServerFavorable>::begin(&CfgTeHuiMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,NewServerFavorable>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,NewServerFavorable>::end(&CfgTeHuiMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,NewServerFavorable>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,NewServerFavorable>>::operator->(&it);
    NewRecord = OldRecord | (1 << (v3->first - 1));
    if ( OldRecord != NewRecord )
    {
      v4 = 1;
      goto LABEL_7;
    }
  }
  v4 = 0;
LABEL_7:
  std::map<signed char,NewServerFavorable>::~map(&CfgTeHuiMap);
  return v4;
}


#####################################
void __cdecl CYunYingHD::SendEveryDayChongZhiInfo(CYunYingHD *const this, int8_t nType)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int32_t TodayPayGold; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  int32_t nRecord; // [rsp+14h] [rbp-1Ch]
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    if ( nType == 3 || nType == 1 || nType == 4 )
    {
      nRecord = Player::getRecord(this->m_pPlayer, 2011);
    }
    else
    {
      if ( nType != 2 )
        return;
      nRecord = Player::getRecord(this->m_pPlayer, 2033);
    }
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt8(packet, nType);
      TodayPayGold = Player::GetTodayPayGold(this->m_pPlayer);
      Answer::NetPacket::writeInt32(packet, TodayPayGold);
      Answer::NetPacket::writeInt32(packet, nRecord);
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
void __cdecl CYunYingHD::SendEveryDayChongZhiIcon(CYunYingHD *const this, int8_t nType)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  CFestivalDoubleEleven *v3; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( CYunYingHD::CanShowEveryChongZhiIcon(this) )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 64) )
      {
        if ( nType != 2
          || (v3 = Answer::Singleton<CFestivalDoubleEleven>::instance(),
              CFestivalDoubleEleven::IsInTime(v3, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE)) )
        {
          CYunYingHD::GetEveryDayChongZhiIconStu(&stu, this, nType);
          Player::SendIconState(this->m_pPlayer, &stu);
        }
      }
    }
  }
}


#####################################
bool __cdecl CYunYingHD::CanShowEveryChongZhiIcon(CYunYingHD *const this)
{
  int32_t nRecord; // [rsp+18h] [rbp-8h]

  if ( Player::GetTotalPayGold(this->m_pPlayer) <= 0 )
    return 0;
  nRecord = Player::getRecord(this->m_pPlayer, 1026);
  return nRecord == (nRecord | 2);
}


#####################################
void __cdecl CYunYingHD::GetEveryDayChongZhiIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  CFestivalDoubleEleven *v3; // rax
  int32_t HaveCount; // [rsp+1Ch] [rbp-44h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-40h] BYREF
  ShowIcon v6; // [rsp+40h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    if ( CYunYingHD::CanShowEveryChongZhiIcon(this) )
    {
      PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
      if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 64) )
      {
        HaveCount = 0;
        if ( CYunYingHD::HaveEveryDayChongZhiGiftCount(this, 3, &HaveCount) )
        {
          CYunYingHD::GetEveryDayChongZhiIconStu(&__x, this, 3);
          std::list<ShowIcon>::push_back(IconList, &__x);
        }
        v3 = Answer::Singleton<CFestivalDoubleEleven>::instance();
        if ( CFestivalDoubleEleven::IsInTime(v3, FESTIVAL_ACTIVITY_TYPE::FAT_DAILY_RECHARGE)
          && CYunYingHD::HaveEveryDayChongZhiGiftCount(this, 2, &HaveCount) )
        {
          CYunYingHD::GetEveryDayChongZhiIconStu(&v6, this, 2);
          std::list<ShowIcon>::push_back(IconList, &v6);
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CYunYingHD::getEveryDayChongZhiIcon(CYunYingHD *const this, int8_t nType)
{
  if ( nType == 3 || nType == 1 || nType == 4 )
    return 17;
  if ( nType == 2 )
    return 52;
  return 0;
}


#####################################
bool __cdecl CYunYingHD::HaveEveryDayChongZhiGiftCount(CYunYingHD *const this, int8_t nType, int32_t *const Count)
{
  bool v3; // bl
  int8_t v4; // al
  CfgEverydayChongZhi *v5; // rax
  int32_t TodayPayGold; // ebx
  std::_List_iterator<CfgEverydayChongZhi> it; // [rsp+20h] [rbp-50h] BYREF
  EverydayChongZhiList CfgEveryDayChongZhiMap; // [rsp+30h] [rbp-40h] BYREF
  std::_List_iterator<CfgEverydayChongZhi> __x; // [rsp+40h] [rbp-30h] BYREF
  int32_t OldRecord; // [rsp+54h] [rbp-1Ch]
  bool CanShowIcon; // [rsp+5Bh] [rbp-15h]
  int32_t NewRecord; // [rsp+5Ch] [rbp-14h]

  OldRecord = 0;
  if ( nType == 3 || nType == 1 || nType == 4 )
  {
    OldRecord = Player::getRecord(this->m_pPlayer, 2011);
  }
  else
  {
    if ( nType != 2 )
      return 0;
    OldRecord = Player::getRecord(this->m_pPlayer, 2033);
  }
  CanShowIcon = 0;
  v4 = (unsigned __int8)Answer::Singleton<CfgData>::instance();
  CfgData::GetEveryDayChongZhiTable((CfgData *const)&CfgEveryDayChongZhiMap, v4);
  for ( it._M_node = std::list<CfgEverydayChongZhi>::begin(&CfgEveryDayChongZhiMap)._M_node;
        ;
        std::_List_iterator<CfgEverydayChongZhi>::operator++(&it) )
  {
    __x._M_node = std::list<CfgEverydayChongZhi>::end(&CfgEveryDayChongZhiMap)._M_node;
    if ( !std::_List_iterator<CfgEverydayChongZhi>::operator!=(&it, &__x) )
      break;
    v5 = std::_List_iterator<CfgEverydayChongZhi>::operator->(&it);
    NewRecord = OldRecord | (1 << (v5->Index - 1));
    if ( OldRecord != NewRecord )
    {
      CanShowIcon = 1;
      TodayPayGold = Player::GetTodayPayGold(this->m_pPlayer);
      if ( TodayPayGold >= std::_List_iterator<CfgEverydayChongZhi>::operator->(&it)->NeedGold )
        ++*Count;
    }
  }
  v3 = CanShowIcon;
  std::list<CfgEverydayChongZhi>::~list(&CfgEveryDayChongZhiMap);
  return v3;
}


#####################################
void __cdecl CYunYingHD::GongGao(CYunYingHD *const this, int32_t GongGaoId)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  int8_t v6; // bl
  GameService *v7; // rax
  std::string val; // [rsp+10h] [rbp-20h] BYREF
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  ConnId = Player::getConnId(this->m_pPlayer);
  v3 = Answer::Singleton<GameService>::instance();
  packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
  if ( packet )
  {
    Answer::NetPacket::writeInt32(packet, GongGaoId);
    Player::getName((const Player *const)&val);
    Answer::NetPacket::writeUTF8(packet, &val);
    std::string::~string(&val);
    Cid = Player::getCid(this->m_pPlayer);
    Answer::NetPacket::writeInt64(packet, Cid);
    WOffset = Answer::NetPacket::getWOffset(packet);
    Answer::NetPacket::setSize(packet, WOffset);
    v6 = Player::getConnId(this->m_pPlayer);
    v7 = Answer::Singleton<GameService>::instance();
    GameService::worldBroadcast(v7, v6, packet);
  }
}


#####################################
int32_t __cdecl CYunYingHD::HaveTotalChongZhiRewardCount(CYunYingHD *const this)
{
  CfgData *v1; // rax
  TotalChongZhiMap *TotalChongZhiTable; // rax
  std::pair<const signed char,CfgTotalChongZhi> *v3; // rax
  int32_t NeedGold; // ebx
  int32_t v5; // ebx
  TotalChongZhiMap CfgTotalChongZhiMap; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgTotalChongZhi> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgTotalChongZhi> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t HaveCount; // [rsp+64h] [rbp-1Ch]
  int32_t OldRecord; // [rsp+68h] [rbp-18h]
  int32_t NewRecord; // [rsp+6Ch] [rbp-14h]

  HaveCount = 0;
  OldRecord = Player::getRecord(this->m_pPlayer, 1037);
  v1 = Answer::Singleton<CfgData>::instance();
  TotalChongZhiTable = CfgData::GetTotalChongZhiTable(v1);
  std::map<signed char,CfgTotalChongZhi>::map(&CfgTotalChongZhiMap, TotalChongZhiTable);
  for ( it._M_node = std::map<signed char,CfgTotalChongZhi>::begin(&CfgTotalChongZhiMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,CfgTotalChongZhi>::end(&CfgTotalChongZhiMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator->(&it);
    NewRecord = OldRecord | (1 << (v3->first - 1));
    if ( OldRecord != NewRecord )
    {
      NeedGold = std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator->(&it)->second.NeedGold;
      if ( NeedGold <= Player::getRecord(this->m_pPlayer, 1036) )
        ++HaveCount;
    }
  }
  v5 = HaveCount;
  std::map<signed char,CfgTotalChongZhi>::~map(&CfgTotalChongZhiMap);
  return v5;
}


#####################################
void __cdecl CYunYingHD::SendTotalChongZhiIcon(CYunYingHD *const this)
{
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    CYunYingHD::GetTotalChongZhiIconStu(&stu, this);
    Player::SendIconState(this->m_pPlayer, &stu);
  }
}


#####################################
void __cdecl CYunYingHD::SendTotalChongZhiInfo(CYunYingHD *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t Record; // edx
  int32_t v4; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2CE7u);
    if ( packet )
    {
      Record = Player::getRecord(this->m_pPlayer, 1036);
      Answer::NetPacket::writeInt32(packet, Record);
      v4 = Player::getRecord(this->m_pPlayer, 1037);
      Answer::NetPacket::writeInt32(packet, v4);
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
void __cdecl CYunYingHD::GetTotalChongZhiIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  CfgData *v3; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF
  int32_t ServerDay; // [rsp+2Ch] [rbp-4h]

  v2 = Answer::Singleton<CfgData>::instance();
  if ( !CfgData::getServerType(v2) )
  {
    v3 = Answer::Singleton<CfgData>::instance();
    ServerDay = CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL);
    if ( CYunYingHD::HaveTotalChongZhiRewardCount(this) > 0 || ServerDay + 1 <= this->m_TotalChongZhiDay )
    {
      CYunYingHD::GetTotalChongZhiIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


#####################################
bool __cdecl CYunYingHD::AllGetTotalChongZhiReward(CYunYingHD *const this)
{
  CfgData *v1; // rax
  TotalChongZhiMap *TotalChongZhiTable; // rax
  std::pair<const signed char,CfgTotalChongZhi> *v3; // rax
  bool v4; // bl
  TotalChongZhiMap CfgTotalChongZhiMap; // [rsp+10h] [rbp-70h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgTotalChongZhi> > it; // [rsp+40h] [rbp-40h] BYREF
  std::_Rb_tree_iterator<std::pair<const signed char,CfgTotalChongZhi> > __x; // [rsp+50h] [rbp-30h] BYREF
  int32_t HaveCount; // [rsp+64h] [rbp-1Ch]
  int32_t OldRecord; // [rsp+68h] [rbp-18h]
  int32_t NewRecord; // [rsp+6Ch] [rbp-14h]

  HaveCount = 0;
  OldRecord = Player::getRecord(this->m_pPlayer, 1037);
  v1 = Answer::Singleton<CfgData>::instance();
  TotalChongZhiTable = CfgData::GetTotalChongZhiTable(v1);
  std::map<signed char,CfgTotalChongZhi>::map(&CfgTotalChongZhiMap, TotalChongZhiTable);
  for ( it._M_node = std::map<signed char,CfgTotalChongZhi>::begin(&CfgTotalChongZhiMap)._M_node;
        ;
        std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator++(&it) )
  {
    __x._M_node = std::map<signed char,CfgTotalChongZhi>::end(&CfgTotalChongZhiMap)._M_node;
    if ( !std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator!=(&it, &__x) )
      break;
    v3 = std::_Rb_tree_iterator<std::pair<signed char const,CfgTotalChongZhi>>::operator->(&it);
    NewRecord = OldRecord | (1 << (v3->first - 1));
    if ( OldRecord != NewRecord )
    {
      v4 = 0;
      goto LABEL_7;
    }
  }
  v4 = 1;
LABEL_7:
  std::map<signed char,CfgTotalChongZhi>::~map(&CfgTotalChongZhiMap);
  return v4;
}


#####################################
void __cdecl CYunYingHD::AddTotalChongZhiCount(CYunYingHD *const this, int32_t AddCount)
{
  CfgData *v2; // rax
  CfgData *v3; // rax
  CExtOperateLimit *OperateLimit; // rax

  if ( this->m_pPlayer )
  {
    v2 = Answer::Singleton<CfgData>::instance();
    if ( !CfgData::getServerType(v2) )
    {
      v3 = Answer::Singleton<CfgData>::instance();
      if ( this->m_TotalChongZhiDay > CfgData::getServerDiffDay(v3, SERVER_TYPE::SVT_NORMAL) )
      {
        OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
        CExtOperateLimit::AddLimitCount(OperateLimit, 1036, AddCount);
        if ( CYunYingHD::HaveTotalChongZhiRewardCount(this) > 0 )
          CYunYingHD::SendTotalChongZhiIcon(this);
        CYunYingHD::SendTotalChongZhiInfo(this);
      }
    }
  }
}


#####################################
int32_t __cdecl CYunYingHD::OnGetMobilePhoneGift(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  CfgData *v4; // rax
  const CfgWeiXinTable *WeiXinTable; // rax
  CfgData *v6; // rax
  const CfgAdultGiftTable *AdultGiftTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  int8_t v9; // r14
  int32_t Sid; // r13d
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  DBService *v13; // rax
  std::string platform; // [rsp+10h] [rbp-80h] BYREF
  std::string v15; // [rsp+20h] [rbp-70h] BYREF
  std::string v16; // [rsp+30h] [rbp-60h] BYREF
  std::string p_passport; // [rsp+40h] [rbp-50h] BYREF
  int8_t nType; // [rsp+53h] [rbp-3Dh]
  int32_t nRecord; // [rsp+54h] [rbp-3Ch]
  const CfgMobilePhoneGift *pCfgMobilePhoneGift; // [rsp+58h] [rbp-38h]
  const CfgWeiXingGift *pCfgWeiXin; // [rsp+60h] [rbp-30h]
  const CfgAdultGift *pCfgAdult; // [rsp+68h] [rbp-28h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  nType = Answer::NetPacket::readInt8(inPacket);
  nRecord = 0;
  switch ( nType )
  {
    case 3:
      nRecord = 1113;
      Player::GetPlatform((const Player *const)&platform);
      v3 = Answer::Singleton<CfgData>::instance();
      pCfgMobilePhoneGift = CfgData::GetMobilePhoneGift(v3, &platform);
      std::string::~string(&platform);
      if ( !pCfgMobilePhoneGift )
        return 10002;
      break;
    case 5:
      nRecord = 1054;
      Player::GetPlatform((const Player *const)&v16);
      v6 = Answer::Singleton<CfgData>::instance();
      AdultGiftTable = CfgData::GetAdultGiftTable(v6);
      pCfgAdult = CfgAdultGiftTable::GetAdultGift(AdultGiftTable, &v16);
      std::string::~string(&v16);
      if ( !pCfgAdult )
        return 10002;
      break;
    case 2:
      nRecord = 1052;
      Player::GetPlatform((const Player *const)&v15);
      v4 = Answer::Singleton<CfgData>::instance();
      WeiXinTable = CfgData::GetWeiXinTable(v4);
      pCfgWeiXin = CfgWeiXinTable::GetWeiXinGift(WeiXinTable, &v15);
      std::string::~string(&v15);
      if ( !pCfgWeiXin )
        return 10002;
      break;
  }
  if ( nRecord <= 0 )
    return 10002;
  OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
  if ( CExtOperateLimit::GetLimitCount(OperateLimit, nRecord) > 0 )
    return 10002;
  v9 = nType;
  Player::GetPassport((Player *const)&p_passport);
  Sid = Player::getSid(this->m_pPlayer);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v13 = Answer::Singleton<DBService>::instance();
  DBService::CheckMobilePhoneGiftEffect(v13, ConnId, GateIndex, Sid, &p_passport, v9);
  std::string::~string(&p_passport);
  return 0;
}


#####################################
int32_t __cdecl CYunYingHD::OnDBGetMobilePhoneGift(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v5; // rax
  CfgData *v6; // rax
  CfgData *v7; // rax
  const CfgWeiXinTable *WeiXinTable; // rax
  CfgData *v9; // rax
  const CfgAdultGiftTable *AdultGiftTable; // rax
  int32_t v11; // ebx
  CExtCharBag *Bag; // rax
  CExtOperateLimit *OperateLimit; // rax
  CWan360 *Wan360; // rax
  int16_t v15; // r12
  int8_t v16; // bl
  GameService *v17; // rax
  MemChrBagVector vReward; // [rsp+10h] [rbp-90h] BYREF
  std::string platform; // [rsp+30h] [rbp-70h] BYREF
  std::string v21; // [rsp+40h] [rbp-60h] BYREF
  std::string v22; // [rsp+50h] [rbp-50h] BYREF
  int8_t nType; // [rsp+5Eh] [rbp-42h]
  int32_t nRecord; // [rsp+60h] [rbp-40h]
  int32_t nOpway; // [rsp+64h] [rbp-3Ch]
  const CfgMobilePhoneGift *pCfgMobilePhoneGift; // [rsp+68h] [rbp-38h]
  const CfgWeiXingGift *pCfgWeiXin; // [rsp+70h] [rbp-30h]
  const CfgAdultGift *pCfgAdult; // [rsp+78h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nType = Answer::NetPacket::readInt8(inPacket);
    if ( !Answer::NetPacket::readInt8(inPacket) )
    {
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      ConnId = Player::getConnId(this->m_pPlayer);
      v5 = Answer::Singleton<GameService>::instance();
      return GameService::replyfailure(v5, ConnId, GateIndex, 0x206u, nType, 0);
    }
    nRecord = 0;
    nOpway = 0;
    std::vector<MemChrBag>::vector(&vReward);
    switch ( nType )
    {
      case 3:
        nRecord = 1113;
        nOpway = 1306;
        Player::GetPlatform((const Player *const)&platform);
        v6 = Answer::Singleton<CfgData>::instance();
        pCfgMobilePhoneGift = CfgData::GetMobilePhoneGift(v6, &platform);
        std::string::~string(&platform);
        if ( pCfgMobilePhoneGift )
        {
          std::vector<MemChrBag>::operator=(&vReward, &pCfgMobilePhoneGift->vItem);
          goto LABEL_19;
        }
        v2 = 10002;
        break;
      case 5:
        nRecord = 1054;
        nOpway = 1315;
        Player::GetPlatform((const Player *const)&v22);
        v9 = Answer::Singleton<CfgData>::instance();
        AdultGiftTable = CfgData::GetAdultGiftTable(v9);
        pCfgAdult = CfgAdultGiftTable::GetAdultGift(AdultGiftTable, &v22);
        std::string::~string(&v22);
        if ( pCfgAdult )
        {
          std::vector<MemChrBag>::operator=(&vReward, &pCfgAdult->vReward);
          goto LABEL_19;
        }
        v2 = 10002;
        break;
      case 2:
        nRecord = 1052;
        nOpway = 1314;
        Player::GetPlatform((const Player *const)&v21);
        v7 = Answer::Singleton<CfgData>::instance();
        WeiXinTable = CfgData::GetWeiXinTable(v7);
        pCfgWeiXin = CfgWeiXinTable::GetWeiXinGift(WeiXinTable, &v21);
        std::string::~string(&v21);
        if ( pCfgWeiXin )
        {
          std::vector<MemChrBag>::operator=(&vReward, &pCfgWeiXin->vReward);
          goto LABEL_19;
        }
        v2 = 10002;
        break;
      default:
LABEL_19:
        if ( nRecord > 0 )
        {
          v11 = nOpway;
          Bag = Player::GetBag(this->m_pPlayer);
          if ( !CExtCharBag::AddItem(Bag, &vReward, (ITEM_CHANGE_REASON)v11) )
          {
            v2 = 10002;
          }
          else
          {
            OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
            CExtOperateLimit::UpdateLimitCount(OperateLimit, nRecord, 1);
            switch ( nType )
            {
              case 3:
                CYunYingHD::SendMobilePhoneGiftIcon(this);
                break;
              case 5:
                CYunYingHD::SendAdultGiftIcon(this);
                break;
              case 2:
                Wan360 = Player::GetWan360(this->m_pPlayer);
                CWan360::SendWeiXinIcon(Wan360);
                break;
            }
            v15 = Player::getGateIndex(this->m_pPlayer);
            v16 = Player::getConnId(this->m_pPlayer);
            v17 = Answer::Singleton<GameService>::instance();
            v2 = GameService::replySuccess(v17, v16, v15, 0x206u, 0);
          }
        }
        else
        {
          v2 = 10002;
        }
        break;
    }
    std::vector<MemChrBag>::~vector(&vReward);
    return v2;
  }
  return 10002;
}


#####################################
void __cdecl CYunYingHD::GetMobilePhoneGiftIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  CExtOperateLimit *OperateLimit; // rax
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF
  const CfgMobilePhoneGift *pCfgMobilePhoneGift; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v2 = Answer::Singleton<CfgData>::instance();
    pCfgMobilePhoneGift = CfgData::GetMobilePhoneGift(v2, &platform);
    std::string::~string(&platform);
    if ( pCfgMobilePhoneGift )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      if ( CExtOperateLimit::GetLimitCount(OperateLimit, 1113) <= 0 )
      {
        CYunYingHD::GetMobilePhoneGiftIconStu(&__x, this, pCfgMobilePhoneGift->nIcon);
        std::list<ShowIcon>::push_back(IconList, &__x);
      }
    }
  }
}


#####################################
void __cdecl CYunYingHD::SendMobilePhoneGiftIcon(CYunYingHD *const this)
{
  CfgData *v1; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-20h] BYREF
  const CfgMobilePhoneGift *pCfgMobilePhoneGift; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v1 = Answer::Singleton<CfgData>::instance();
    pCfgMobilePhoneGift = CfgData::GetMobilePhoneGift(v1, &platform);
    std::string::~string(&platform);
    if ( pCfgMobilePhoneGift )
    {
      CYunYingHD::GetMobilePhoneGiftIconStu(&stu, this, pCfgMobilePhoneGift->nIcon);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CYunYingHD::GetAdultGiftIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  const CfgAdultGiftTable *AdultGiftTable; // rax
  CExtOperateLimit *OperateLimit; // rax
  std::string platform; // [rsp+10h] [rbp-40h] BYREF
  ShowIcon __x; // [rsp+20h] [rbp-30h] BYREF
  const CfgAdultGift *pCfgAdultGift; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v2 = Answer::Singleton<CfgData>::instance();
    AdultGiftTable = CfgData::GetAdultGiftTable(v2);
    pCfgAdultGift = CfgAdultGiftTable::GetAdultGift(AdultGiftTable, &platform);
    std::string::~string(&platform);
    if ( pCfgAdultGift )
    {
      OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
      if ( CExtOperateLimit::GetLimitCount(OperateLimit, 1054) <= 0 )
      {
        CYunYingHD::GetAdultGiftIconStu(&__x, this, pCfgAdultGift->nIconId);
        std::list<ShowIcon>::push_back(IconList, &__x);
      }
    }
  }
}


#####################################
void __cdecl CYunYingHD::SendAdultGiftIcon(CYunYingHD *const this)
{
  CfgData *v1; // rax
  const CfgAdultGiftTable *AdultGiftTable; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-20h] BYREF
  const CfgAdultGift *pCfgAdultGift; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    Player::GetPlatform((const Player *const)&platform);
    v1 = Answer::Singleton<CfgData>::instance();
    AdultGiftTable = CfgData::GetAdultGiftTable(v1);
    pCfgAdultGift = CfgAdultGiftTable::GetAdultGift(AdultGiftTable, &platform);
    std::string::~string(&platform);
    if ( pCfgAdultGift )
    {
      CYunYingHD::GetAdultGiftIconStu(&stu, this, pCfgAdultGift->nIconId);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CYunYingHD::SuperMemberRecharge(CYunYingHD *const this, int32_t nGold)
{
  CExtOperateLimit *OperateLimit; // rax
  CExtOperateLimit *v3; // rax
  CExtOperateLimit *v4; // rax
  CExtOperateLimit *v5; // rax
  CExtOperateLimit *v6; // rax
  int32_t nowTime; // [rsp+14h] [rbp-Ch]
  int32_t nOldRecord; // [rsp+18h] [rbp-8h]
  int32_t nNewRecord; // [rsp+1Ch] [rbp-4h]

  if ( this->m_pPlayer )
  {
    nowTime = Unit::getNow(this->m_pPlayer);
    OperateLimit = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::UpdateLimitCount(OperateLimit, 1114, nowTime);
    v3 = Player::GetOperateLimit(this->m_pPlayer);
    CExtOperateLimit::AddLimitCount(v3, 1115, nGold);
    v4 = Player::GetOperateLimit(this->m_pPlayer);
    nOldRecord = CExtOperateLimit::GetLimitCount(v4, 1116);
    v5 = Player::GetOperateLimit(this->m_pPlayer);
    nNewRecord = CExtOperateLimit::GetLimitCount(v5, 1115);
    if ( nNewRecord > nOldRecord )
    {
      v6 = Player::GetOperateLimit(this->m_pPlayer);
      CExtOperateLimit::UpdateLimitCount(v6, 1116, nNewRecord);
    }
  }
}


#####################################
void __cdecl CYunYingHD::GetSuperMemberIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CfgData *v2; // rax
  ShowIcon stu; // [rsp+10h] [rbp-40h] BYREF
  std::string platform; // [rsp+30h] [rbp-20h] BYREF
  const CfgSuperMember *pCfg; // [rsp+38h] [rbp-18h]

  Player::GetPlatform((const Player *const)&platform);
  v2 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetSuperMember(v2, &platform);
  std::string::~string(&platform);
  if ( pCfg )
  {
    *(_QWORD *)&stu.nId = 0x200000000LL;
    *(_QWORD *)&stu.nLeftTime = 0;
    *(_QWORD *)&stu.nIconRight = 0;
    stu.nId = pCfg->nIcon;
    std::list<ShowIcon>::push_back(IconList, &stu);
  }
}


#####################################
int32_t __cdecl CYunYingHD::OnGetZeroBuyPetGift(CYunYingHD *const this, Answer::NetPacket *inPacket)
{
  CfgData *v4; // rax
  CExtCharBag *Bag; // rax
  int32_t Now; // eax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v10; // rax
  const ZeroBuyPetCfg *pZeroBuyPetCfg; // [rsp+18h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 10002;
  if ( Player::getRecord(this->m_pPlayer, 37502) < 0 || Player::getRecord(this->m_pPlayer, 37503) > 0 )
    return 10002;
  v4 = Answer::Singleton<CfgData>::instance();
  pZeroBuyPetCfg = CfgData::GetZeroBuyPetCfg(v4);
  if ( !pZeroBuyPetCfg )
    return 10002;
  if ( Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_GOLD) < pZeroBuyPetCfg->nGold )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &pZeroBuyPetCfg->cItems, ITEM_CHANGE_REASON::ICR_ZERO_BY_PET) )
    return 10002;
  Player::DecCurrency(
    this->m_pPlayer,
    CURRENCY_TYPE::CURRENCY_GOLD,
    pZeroBuyPetCfg->nGold,
    CURRENCY_CHANGE_REASON::GCR_ZERO_BUY_PET,
    0);
  Now = Unit::getNow(this->m_pPlayer);
  Player::updateRecord(this->m_pPlayer, 37503, Now + 259200);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v10 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v10, ConnId, GateIndex, Proc, 0);
  return 0;
}


#####################################
void __cdecl CYunYingHD::OnZeroBuyPetOpen(CYunYingHD *const this)
{
  int32_t Now; // eax

  if ( this->m_pPlayer )
  {
    Now = Unit::getNow(this->m_pPlayer);
    Player::updateRecord(this->m_pPlayer, 37502, Now + 86400);
    CYunYingHD::SendZeroBuyPetIcon(this);
  }
}


#####################################
void __cdecl CYunYingHD::SendZeroBuyPetIcon(CYunYingHD *const this)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon stu; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 237) )
    {
      CYunYingHD::GetZeroBuyPetIconStu(&stu, this);
      Player::SendIconState(this->m_pPlayer, &stu);
    }
  }
}


#####################################
void __cdecl CYunYingHD::GetZeroBuyPetIconState(CYunYingHD *const this, IconStateList *const IconList)
{
  CFunctionOpen *PlayerFunctionOpen; // rax
  ShowIcon __x; // [rsp+10h] [rbp-20h] BYREF

  if ( this->m_pPlayer )
  {
    PlayerFunctionOpen = Player::GetPlayerFunctionOpen(this->m_pPlayer);
    if ( CFunctionOpen::IsOpened(PlayerFunctionOpen, 237) )
    {
      CYunYingHD::GetZeroBuyPetIconStu(&__x, this);
      std::list<ShowIcon>::push_back(IconList, &__x);
    }
  }
}


