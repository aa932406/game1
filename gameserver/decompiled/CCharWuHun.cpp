// Decompiled methods for class: CCharWuHun
// Source: gameserver.cc
// Total methods: 16

#####################################
void __cdecl CCharWuHun::~CCharWuHun(CCharWuHun *const this)
{
  CCharWuHun::~CCharWuHun(this);
  operator delete(this);
}


#####################################
void __cdecl CCharWuHun::OnLoadFromDB(CCharWuHun *const this, const PlayerDBData *const dbData)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  int32_t i; // [rsp+10h] [rbp-20h]
  int32_t j; // [rsp+14h] [rbp-1Ch]
  WuHunItem *pCfg; // [rsp+18h] [rbp-18h]

  memcpy(this->m_WuHun, dbData->m_WuHunShopDBData.m_WuHun, sizeof(this->m_WuHun));
  for ( i = 0; i <= 4; ++i )
  {
    for ( j = 0; j <= 15; ++j )
    {
      v2 = this->m_WuHun[i][j];
      v3 = Answer::Singleton<CfgData>::instance();
      pCfg = CfgData::GetWuHunItem(v3, v2);
      if ( pCfg )
      {
        if ( pCfg->nTalentId > 0 )
          CCharWuHun::OnAddTalent(this, pCfg->nTalentId, pCfg->nTalentLevel);
      }
    }
  }
}


#####################################
void __cdecl CCharWuHun::OnSaveToDB(CCharWuHun *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->m_WuHunShopDBData.m_WuHun, this->m_WuHun, sizeof(dbData->m_WuHunShopDBData.m_WuHun));
}


#####################################
void __cdecl CCharWuHun::GetInterestsProtocol(CCharWuHun *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v3; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v4; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v5; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 653;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 654;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 655;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 656;
  std::list<unsigned short>::push_back(procList, &v5);
}


#####################################
int32_t __cdecl CCharWuHun::DispatchNetDatas(CCharWuHun *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  if ( !inPacket )
    return 10002;
  if ( nProcId == 654 )
    return CCharWuHun::onDressWuHun(this, inPacket);
  if ( nProcId > 0x28Eu )
  {
    if ( nProcId == 655 )
      return CCharWuHun::onUnDressWuHun(this, inPacket);
    if ( nProcId == 656 )
      return CCharWuHun::onCreateWuHun(this, inPacket);
  }
  else if ( nProcId == 653 )
  {
    return CCharWuHun::onAskWuHunInfo(this, inPacket);
  }
  return 0;
}


#####################################
void __cdecl CCharWuHun::AddCharAttr(CCharWuHun *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  int32_t m_nAddAttrValue; // ebx
  AddAttribute *v4; // rax
  std::_List_iterator<AddAttribute> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<AddAttribute> __x; // [rsp+20h] [rbp-30h] BYREF
  int32_t i; // [rsp+30h] [rbp-20h]
  int32_t j; // [rsp+34h] [rbp-1Ch]
  WuHunItem *pCfg; // [rsp+38h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    for ( i = 0; i <= 4; ++i )
    {
      for ( j = 0; j <= 15; ++j )
      {
        if ( this->m_WuHun[i][j] > 0 )
        {
          v1 = this->m_WuHun[i][j];
          v2 = Answer::Singleton<CfgData>::instance();
          pCfg = CfgData::GetWuHunItem(v2, v1);
          if ( pCfg )
          {
            for ( it._M_node = std::list<AddAttribute>::begin(&pCfg->lAttrList)._M_node;
                  ;
                  std::_List_iterator<AddAttribute>::operator++(&it, 0) )
            {
              __x._M_node = std::list<AddAttribute>::end(&pCfg->lAttrList)._M_node;
              if ( !std::_List_iterator<AddAttribute>::operator!=(&it, &__x) )
                break;
              m_nAddAttrValue = std::_List_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
              v4 = std::_List_iterator<AddAttribute>::operator->(&it);
              Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v4->m_nAddAttrType, m_nAddAttrValue);
            }
          }
        }
      }
    }
  }
}


#####################################
int32_t __cdecl CCharWuHun::onAskWuHunInfo(CCharWuHun *const this, Answer::NetPacket *inPacket)
{
  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Answer::NetPacket::readInt32(inPacket);
  return 0;
}


#####################################
int32_t __cdecl CCharWuHun::onDressWuHun(CCharWuHun *const this, Answer::NetPacket *inPacket)
{
  CExtCharBag *Bag; // rax
  CfgData *v4; // rax
  int32_t nDressLevel; // ebx
  CExtCharBag *v6; // rax
  CfgData *v7; // rax
  CExtCharBag *v8; // rax
  MemChrBag stu; // [rsp+10h] [rbp-80h] BYREF
  MemChrBag bagSlot; // [rsp+30h] [rbp-60h] BYREF
  int32_t Level; // [rsp+5Ch] [rbp-34h]
  int32_t BagSlot; // [rsp+60h] [rbp-30h]
  int32_t WuHunSlot; // [rsp+64h] [rbp-2Ch]
  WuHunItem *pCfg; // [rsp+68h] [rbp-28h]
  int32_t OldId; // [rsp+74h] [rbp-1Ch]
  WuHunItem *pOld; // [rsp+78h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Level = Answer::NetPacket::readInt32(inPacket);
  BagSlot = Answer::NetPacket::readInt32(inPacket);
  WuHunSlot = Answer::NetPacket::readInt32(inPacket);
  if ( Level <= 0 || Level > 5 )
    return 10002;
  if ( (unsigned int)WuHunSlot >= 0x10 )
    return 10002;
  Bag = Player::GetBag(this->m_pPlayer);
  bagSlot = *CExtCharBag::GetSlotData(Bag, BagSlot);
  v4 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetWuHunItem(v4, bagSlot.itemId);
  if ( !pCfg || bagSlot.itemClass != 8 )
    return 10002;
  nDressLevel = pCfg->nDressLevel;
  if ( nDressLevel > (*((int (__fastcall **)(Player *))this->m_pPlayer->_vptr_Entity + 9))(this->m_pPlayer) )
    return 10002;
  if ( pCfg->nNeedQuality > 0 && CCharWuHun::GetSuitLevel(this, Level) < pCfg->nNeedQuality )
    return 10002;
  if ( !CCharWuHun::checkWuHunPlace(this, pCfg->nType, WuHunSlot) )
    return 10002;
  OldId = this->m_WuHun[Level - 1][WuHunSlot];
  this->m_WuHun[Level - 1][WuHunSlot] = bagSlot.itemId;
  --bagSlot.itemCount;
  v6 = Player::GetBag(this->m_pPlayer);
  CExtCharBag::SetSlotData(v6, BagSlot, &bagSlot, ITEM_CHANGE_REASON::ICR_WU_HUN_DRESS, 0);
  if ( OldId > 0 )
  {
    v7 = Answer::Singleton<CfgData>::instance();
    pOld = CfgData::GetWuHunItem(v7, OldId);
    if ( pOld )
    {
      *(_DWORD *)&stu.itemClass = 8;
      *(_QWORD *)&stu.itemCount = 0x100000001LL;
      *(_QWORD *)&stu.endTime = 0;
      stu.srcId = 0;
      stu.itemId = OldId;
      v8 = Player::GetBag(this->m_pPlayer);
      if ( !CExtCharBag::AddItem(v8, &stu, ITEM_CHANGE_REASON::ICR_WU_HUN_DRESS) )
        return 10002;
      if ( pOld->nTalentId > 0 )
        CCharWuHun::OnRemoveTalent(this, pOld->nTalentId, pOld->nTalentLevel);
    }
  }
  if ( pCfg->nTalentId > 0 )
    CCharWuHun::OnAddTalent(this, pCfg->nTalentId, pCfg->nTalentLevel);
  CCharWuHun::sendWuHunSlotInfo(this, Level, WuHunSlot);
  Player::RecalcAttr(this->m_pPlayer);
  return 0;
}


#####################################
int32_t __cdecl CCharWuHun::onUnDressWuHun(CCharWuHun *const this, Answer::NetPacket *inPacket)
{
  int32_t v3; // ebx
  CfgData *v4; // rax
  CExtCharBag *Bag; // rax
  MemChrBag stu; // [rsp+10h] [rbp-40h] BYREF
  int32_t Level; // [rsp+30h] [rbp-20h]
  int32_t WuHunSlot; // [rsp+34h] [rbp-1Ch]
  WuHunItem *pOld; // [rsp+38h] [rbp-18h]

  if ( !inPacket || !this->m_pPlayer )
    return 10002;
  Level = Answer::NetPacket::readInt32(inPacket);
  WuHunSlot = Answer::NetPacket::readInt32(inPacket);
  if ( Level <= 0 || Level > 5 )
    return 10002;
  if ( (unsigned int)WuHunSlot >= 0x10 )
    return 10002;
  if ( this->m_WuHun[Level - 1][WuHunSlot] <= 0 )
    return 10002;
  v3 = this->m_WuHun[Level - 1][WuHunSlot];
  v4 = Answer::Singleton<CfgData>::instance();
  pOld = CfgData::GetWuHunItem(v4, v3);
  if ( !pOld )
    return 10002;
  memset(&stu, 0, sizeof(stu));
  stu.itemId = pOld->nId;
  stu.itemClass = 8;
  stu.bind = 1;
  stu.itemCount = 1;
  Bag = Player::GetBag(this->m_pPlayer);
  if ( !CExtCharBag::AddItem(Bag, &stu, ITEM_CHANGE_REASON::ICR_WU_HUN_UNDRESS) )
    return 10002;
  if ( pOld->nTalentId > 0 )
    CCharWuHun::OnRemoveTalent(this, pOld->nTalentId, pOld->nTalentLevel);
  this->m_WuHun[Level - 1][WuHunSlot] = 0;
  CCharWuHun::sendWuHunSlotInfo(this, Level, WuHunSlot);
  Player::RecalcAttr(this->m_pPlayer);
  return 0;
}


#####################################
void __cdecl CCharWuHun::OnRemoveTalent(CCharWuHun *const this, int32_t TalentId, int32_t TalentLevel)
{
  CExtCharSkill *CharSkill; // rax

  if ( this->m_pPlayer )
  {
    CharSkill = Player::GetCharSkill(this->m_pPlayer);
    CExtCharSkill::removeSkillByTalent(CharSkill, TalentId, TalentLevel);
  }
}


#####################################
void __cdecl CCharWuHun::OnAddTalent(CCharWuHun *const this, int32_t TalentId, int32_t TalentLevel)
{
  CExtCharSkill *CharSkill; // rax

  if ( this->m_pPlayer )
  {
    CharSkill = Player::GetCharSkill(this->m_pPlayer);
    CExtCharSkill::AddOtherSkill(CharSkill, TalentId, TalentLevel);
  }
}


#####################################
int32_t __cdecl CCharWuHun::onCreateWuHun(CCharWuHun *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  CfgData *v3; // rax
  CExtCharBag *Bag; // rax
  Answer::Random *v5; // rax
  RateItem *v6; // rax
  RateItem *v7; // rax
  CExtCharBag *v8; // rax
  CExtCharBag *v9; // rax
  int32_t itemId; // ebx
  CfgData *v11; // rax
  GameService *v12; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v15; // rax
  int32_t nType; // ebx
  ChrTask *Task; // rax
  int64_t v18; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v22; // rax
  MemChrBag stu; // [rsp+10h] [rbp-B0h] BYREF
  std::_List_iterator<RateItem> it; // [rsp+30h] [rbp-90h] BYREF
  ItemDataList CostItem; // [rsp+40h] [rbp-80h] BYREF
  RateItemList Items; // [rsp+50h] [rbp-70h] BYREF
  std::_List_iterator<RateItem> __x; // [rsp+60h] [rbp-60h] BYREF
  std::string val; // [rsp+70h] [rbp-50h] BYREF
  int32_t nId; // [rsp+78h] [rbp-48h]
  int8_t CostSpecial; // [rsp+7Fh] [rbp-41h]
  CreateWuHun *pCfg; // [rsp+80h] [rbp-40h]
  int32_t GongGaoId; // [rsp+88h] [rbp-38h]
  int32_t nRand; // [rsp+8Ch] [rbp-34h]
  WuHunItem *pCfgItem; // [rsp+90h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+98h] [rbp-28h]

  if ( this->m_pPlayer && inPacket )
  {
    nId = Answer::NetPacket::readInt32(inPacket);
    CostSpecial = Answer::NetPacket::readInt8(inPacket);
    v3 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::GetCreateWuHun(v3, nId);
    if ( !pCfg )
      return 10002;
    Bag = Player::GetBag(this->m_pPlayer);
    if ( CExtCharBag::GetFreeSlotCount(Bag) <= 0 )
      return 10002;
    GongGaoId = 0;
    memset(&stu, 0, sizeof(stu));
    std::list<RateItem>::list(&Items, &pCfg->GetItemRate);
    std::list<ItemData>::list(&CostItem, &pCfg->ConstItem);
    if ( CostSpecial == 1 )
    {
      if ( ItemData::IsEmpty(&pCfg->SpecialCost) )
      {
        v2 = 10002;
        goto LABEL_30;
      }
      std::list<RateItem>::operator=(&Items, &pCfg->GetItemRate2);
      std::list<ItemData>::push_back(&CostItem, &pCfg->SpecialCost);
    }
    v5 = Answer::Singleton<Answer::Random>::instance();
    nRand = Answer::Random::generate(v5, 1, 10000);
    for ( it._M_node = std::list<RateItem>::begin(&Items)._M_node; ; std::_List_iterator<RateItem>::operator++(&it, 0) )
    {
      __x._M_node = std::list<RateItem>::end(&Items)._M_node;
      if ( !std::_List_iterator<RateItem>::operator!=(&it, &__x) )
        break;
      v6 = std::_List_iterator<RateItem>::operator->(&it);
      if ( v6->nRate >= nRand )
      {
        stu.itemId = std::_List_iterator<RateItem>::operator->(&it)->nItemId;
        stu.itemClass = std::_List_iterator<RateItem>::operator->(&it)->nItemClass;
        stu.itemCount = std::_List_iterator<RateItem>::operator->(&it)->nItemCount;
        stu.bind = std::_List_iterator<RateItem>::operator->(&it)->nBind;
        if ( std::_List_iterator<RateItem>::operator->(&it)->nGongGaoId > 0 )
          GongGaoId = std::_List_iterator<RateItem>::operator->(&it)->nGongGaoId;
        break;
      }
      v7 = std::_List_iterator<RateItem>::operator->(&it);
      nRand -= v7->nRate;
    }
    if ( stu.itemId > 0 && stu.itemCount > 0 )
    {
      v8 = Player::GetBag(this->m_pPlayer);
      if ( CExtCharBag::RemoveItem(v8, &CostItem, ITEM_CHANGE_REASON::ICR_WU_HUN_CREATE) )
      {
        v9 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::AddItem(v9, &stu, ITEM_CHANGE_REASON::ICR_WU_HUN_CREATE);
        itemId = stu.itemId;
        v11 = Answer::Singleton<CfgData>::instance();
        pCfgItem = CfgData::GetWuHunItem(v11, itemId);
        if ( pCfgItem )
        {
          if ( GongGaoId > 0 )
          {
            v12 = Answer::Singleton<GameService>::instance();
            packet = GameService::popNetpacket(v12, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
            if ( !packet )
            {
              v2 = 10002;
              goto LABEL_30;
            }
            Answer::NetPacket::writeInt32(packet, GongGaoId);
            Player::getName((const Player *const)&val);
            Answer::NetPacket::writeUTF8(packet, &val);
            std::string::~string(&val);
            Cid = Player::getCid(this->m_pPlayer);
            Answer::NetPacket::writeInt64(packet, Cid);
            Answer::NetPacket::writeInt32(packet, stu.itemId);
            WOffset = Answer::NetPacket::getWOffset(packet);
            Answer::NetPacket::setSize(packet, WOffset);
            v15 = Answer::Singleton<GameService>::instance();
            GameService::worldBroadcast(v15, 0, packet);
          }
          nType = pCfgItem->nType;
          Task = Player::GetTask(this->m_pPlayer);
          ChrTask::updateTaskCount(Task, 43, nType);
        }
        v18 = stu.itemId;
        Proc = Answer::NetPacket::getProc(inPacket);
        GateIndex = Player::getGateIndex(this->m_pPlayer);
        ConnId = Player::getConnId(this->m_pPlayer);
        v22 = Answer::Singleton<GameService>::instance();
        GameService::replySuccess(v22, ConnId, GateIndex, Proc, v18);
        v2 = 0;
        goto LABEL_30;
      }
      v2 = 10002;
    }
    else
    {
      v2 = 10002;
    }
LABEL_30:
    std::list<ItemData>::~list(&CostItem);
    std::list<RateItem>::~list(&Items);
    return v2;
  }
  return 10002;
}


#####################################
void __cdecl CCharWuHun::sendWuHunInfo(CCharWuHun *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-30h]
  int32_t i; // [rsp+1Ch] [rbp-24h]
  int8_t Count; // [rsp+20h] [rbp-20h]
  int32_t oldoffest; // [rsp+24h] [rbp-1Ch]
  int32_t newwoffset; // [rsp+28h] [rbp-18h]
  int j; // [rsp+2Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EA1u);
    if ( packet )
    {
      for ( i = 0; i <= 4; ++i )
      {
        Answer::NetPacket::writeInt32(packet, i + 1);
        Count = 0;
        oldoffest = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::writeInt32(packet, 0);
        for ( j = 0; j <= 15; ++j )
        {
          if ( this->m_WuHun[i][j] > 0 )
          {
            Answer::NetPacket::writeInt32(packet, j);
            Answer::NetPacket::writeInt32(packet, this->m_WuHun[i][j]);
            ++Count;
          }
        }
        newwoffset = Answer::NetPacket::getWOffset(packet);
        Answer::NetPacket::setWOffset(packet, oldoffest);
        Answer::NetPacket::writeInt8(packet, Count);
        Answer::NetPacket::setWOffset(packet, newwoffset);
      }
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
void __cdecl CCharWuHun::sendWuHunSlotInfo(CCharWuHun *const this, int32_t Level, int32_t Slot)
{
  int8_t ConnId; // bl
  GameService *v4; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v7; // bl
  GameService *v8; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer && Level > 0 && Level <= 5 && (unsigned int)Slot < 0x10 )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v4 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v4, ConnId, Answer::PackType::PACK_DISPATCH, 0x2EA2u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, Level);
      Answer::NetPacket::writeInt32(packet, Slot);
      Answer::NetPacket::writeInt32(packet, this->m_WuHun[Level - 1][Slot]);
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
bool __cdecl CCharWuHun::checkWuHunPlace(CCharWuHun *const this, int32_t Type, int32_t Slot)
{
  if ( Type == 2 )
  {
    if ( Slot > 4 && Slot <= 9 )
      return 1;
  }
  else if ( Type > 2 )
  {
    if ( Type == 3 )
    {
      if ( Slot > 9 && Slot <= 14 )
        return 1;
    }
    else if ( Type == 4 && Slot == 15 )
    {
      return 1;
    }
  }
  else if ( Type == 1 && (unsigned int)Slot <= 4 )
  {
    return 1;
  }
  return 0;
}


#####################################
int32_t __cdecl CCharWuHun::GetSuitLevel(CCharWuHun *const this, int32_t nLevel)
{
  int32_t Level; // [rsp+14h] [rbp-8h]
  int32_t i; // [rsp+18h] [rbp-4h]

  if ( nLevel <= 0 || nLevel > 5 )
    return 0;
  Level = 0;
  for ( i = 0; i <= 14; ++i )
  {
    if ( this->m_WuHun[nLevel - 1][i] <= 0 )
      return 0;
    if ( Level )
    {
      if ( this->m_WuHun[nLevel - 1][i] < Level )
        Level = this->m_WuHun[nLevel - 1][i];
    }
    else
    {
      Level = this->m_WuHun[nLevel - 1][i];
    }
  }
  return Level;
}


