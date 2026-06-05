// Decompiled methods for class: CKunExt
// Source: gameserver.cc
// Total methods: 30

#####################################
void __cdecl CKunExt::~CKunExt(CKunExt *const this)
{
  CKunExt::~CKunExt(this);
  operator delete(this);
}


#####################################
void __cdecl CKunExt::OnLoadFromDB(CKunExt *const this, const PlayerDBData *const dbData)
{
  int32_t m_nKunLevel; // ebx
  CfgData *v3; // rax
  const KunLingTable *KunLingTable; // rax
  int32_t nTalentLevel; // r12d
  int32_t nTalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  const KunLevelUpCfg *pKunLevelUpCfg; // [rsp+18h] [rbp-18h]

  memcpy(this->m_DanTian, dbData->m_CKunData.m_DanTian, sizeof(this->m_DanTian));
  memcpy(this->m_LingZhuBag, dbData->m_CKunData.m_LingZhuBag, sizeof(this->m_LingZhuBag));
  memcpy(this->m_LingZhuPos, dbData->m_CKunData.m_LingZhuPos, sizeof(this->m_LingZhuPos));
  this->m_nBuyTime = dbData->m_CKunData.m_nBuyTime;
  this->m_nLianHuaTime = dbData->m_CKunData.m_nLianHuaTime;
  this->m_nKunLevel = dbData->m_CKunData.m_nKunLevel;
  this->m_nExp = dbData->m_CKunData.m_nExp;
  CKunExt::CheckSuit(this);
  m_nKunLevel = this->m_nKunLevel;
  v3 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v3);
  pKunLevelUpCfg = KunLingTable::GetKunLevelUpCfg(KunLingTable, m_nKunLevel);
  if ( pKunLevelUpCfg && pKunLevelUpCfg->nTalentId > 0 )
  {
    if ( pKunLevelUpCfg->nTalentLevel )
    {
      nTalentLevel = pKunLevelUpCfg->nTalentLevel;
      nTalentId = pKunLevelUpCfg->nTalentId;
      CharSkill = Player::GetCharSkill(this->m_pPlayer);
      CExtCharSkill::AddOtherSkill(CharSkill, nTalentId, nTalentLevel);
    }
  }
}


#####################################
void __cdecl CKunExt::OnSaveToDB(CKunExt *const this, PlayerDBData *const dbData)
{
  memcpy(dbData->m_CKunData.m_DanTian, this->m_DanTian, sizeof(dbData->m_CKunData.m_DanTian));
  memcpy(dbData->m_CKunData.m_LingZhuBag, this->m_LingZhuBag, sizeof(dbData->m_CKunData.m_LingZhuBag));
  memcpy(dbData->m_CKunData.m_LingZhuPos, this->m_LingZhuPos, sizeof(dbData->m_CKunData.m_LingZhuPos));
  dbData->m_CKunData.m_nBuyTime = this->m_nBuyTime;
  dbData->m_CKunData.m_nLianHuaTime = this->m_nLianHuaTime;
  dbData->m_CKunData.m_nKunLevel = this->m_nKunLevel;
  dbData->m_CKunData.m_nExp = this->m_nExp;
}


#####################################
void __cdecl CKunExt::GetInterestsProtocol(CKunExt *const this, ProcIdList *const procList)
{
  unsigned __int16 __x; // [rsp+12h] [rbp-Eh] BYREF
  unsigned __int16 v3; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int16 v4; // [rsp+16h] [rbp-Ah] BYREF
  unsigned __int16 v5; // [rsp+18h] [rbp-8h] BYREF
  unsigned __int16 v6; // [rsp+1Ah] [rbp-6h] BYREF
  unsigned __int16 v7; // [rsp+1Ch] [rbp-4h] BYREF
  unsigned __int16 v8; // [rsp+1Eh] [rbp-2h] BYREF

  __x = 741;
  std::list<unsigned short>::push_back(procList, &__x);
  v3 = 742;
  std::list<unsigned short>::push_back(procList, &v3);
  v4 = 743;
  std::list<unsigned short>::push_back(procList, &v4);
  v5 = 744;
  std::list<unsigned short>::push_back(procList, &v5);
  v6 = 745;
  std::list<unsigned short>::push_back(procList, &v6);
  v7 = 746;
  std::list<unsigned short>::push_back(procList, &v7);
  v8 = 749;
  std::list<unsigned short>::push_back(procList, &v8);
}


#####################################
int32_t __cdecl CKunExt::DispatchNetDatas(CKunExt *const this, ProcId_t nProcId, Answer::NetPacket *inPacket)
{
  int32_t result; // eax

  if ( !inPacket )
    return 2;
  switch ( nProcId )
  {
    case 0x2E5u:
      result = CKunExt::OnKunLingLevelUp(this, inPacket);
      break;
    case 0x2E6u:
      result = CKunExt::OnGetLingZhu(this, inPacket);
      break;
    case 0x2E7u:
      result = CKunExt::OnRecoveryLingZhu(this, inPacket);
      break;
    case 0x2E8u:
      result = CKunExt::OnFastFining(this, inPacket);
      break;
    case 0x2E9u:
      result = CKunExt::OnLingZhuLevelUp(this, inPacket);
      break;
    case 0x2EAu:
      result = CKunExt::OnBuyLianHuaTime(this, inPacket);
      break;
    case 0x2EDu:
      result = CKunExt::OnKunWeiYang(this, inPacket);
      break;
    default:
      result = 2;
      break;
  }
  return result;
}


#####################################
void __cdecl CKunExt::OnCleanUp(CKunExt *const this)
{
  std::list<int>::clear(&this->lSuitList);
  this->m_nKunLevel = 0;
  this->m_nExp = 0;
  this->m_nBuyTime = 0;
  this->m_nLianHuaTime = 0;
  bzero(this->m_DanTian, 0x48u);
  bzero(this->m_LingZhuBag, 0x320u);
  bzero(this->m_LingZhuPos, 0x50u);
  this->m_LastUpdateTick = 0;
}


#####################################
void __cdecl CKunExt::OnDaySwitch(CKunExt *const this, int32_t nDiffDays)
{
  this->m_nBuyTime = 0;
  this->m_nLianHuaTime = 0;
  CKunExt::SendKunLingInfo(this);
}


#####################################
void __cdecl CKunExt::OnUpdate(CKunExt *const this, int64_t curTick)
{
  int32_t nEndTime; // ebx
  int32_t nMid; // ebx
  CfgData *v5; // rax
  const KunLingTable *KunLingTable; // rax
  int i; // [rsp+14h] [rbp-1Ch]
  const DanTianCfg *pDanTian; // [rsp+18h] [rbp-18h]

  if ( curTick - this->m_LastUpdateTick > 999 )
  {
    this->m_LastUpdateTick = curTick;
    for ( i = 0; i <= 5; ++i )
    {
      if ( !DanTian::isEmpty(&this->m_DanTian[i]) )
      {
        if ( this->m_DanTian[i].nEndTime )
        {
          nEndTime = this->m_DanTian[i].nEndTime;
          if ( nEndTime <= Unit::getNow(this->m_pPlayer) )
          {
            nMid = this->m_DanTian[i].nMid;
            v5 = Answer::Singleton<CfgData>::instance();
            KunLingTable = CfgData::GetKunLingTable(v5);
            pDanTian = KunLingTable::GetDanTianCfg(KunLingTable, nMid);
            if ( pDanTian )
            {
              this->m_DanTian[i].nEndTime = 0;
              if ( this->m_nKunLevel <= 10 )
                this->m_DanTian[i].nId = DanTianCfg::RandDanTianId(pDanTian);
              else
                this->m_DanTian[i].nId = DanTianCfg::RandHighDanTianId(pDanTian);
              CKunExt::SendDanTianInfo(this, i);
            }
          }
        }
      }
    }
  }
}


#####################################
void __cdecl CKunExt::AddCharAttr(CKunExt *const this)
{
  int32_t m_nKunLevel; // ebx
  CfgData *v2; // rax
  const KunLingTable *KunLingTable; // rax
  int32_t m_nAddAttrValue; // ebx
  const AddAttribute *v5; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const KunLingTable *v8; // rax
  int32_t v9; // ebx
  const AddAttribute *v10; // rax
  int32_t v11; // ebx
  CfgData *v12; // rax
  const KunLingTable *v13; // rax
  int32_t v14; // ebx
  const AddAttribute *v15; // rax
  std::_List_const_iterator<AddAttribute> it_2; // [rsp+10h] [rbp-B0h] BYREF
  std::_List_iterator<int> it_1; // [rsp+20h] [rbp-A0h] BYREF
  std::_List_const_iterator<AddAttribute> it_0; // [rsp+30h] [rbp-90h] BYREF
  std::_List_const_iterator<AddAttribute> it; // [rsp+40h] [rbp-80h] BYREF
  std::_List_const_iterator<AddAttribute> __x; // [rsp+50h] [rbp-70h] BYREF
  std::_List_const_iterator<AddAttribute> v21; // [rsp+60h] [rbp-60h] BYREF
  std::_List_iterator<int> v22; // [rsp+70h] [rbp-50h] BYREF
  std::_List_const_iterator<AddAttribute> v23; // [rsp+80h] [rbp-40h] BYREF
  const KunLevelUpCfg *pKunLevelUpCfg; // [rsp+90h] [rbp-30h]
  int32_t i; // [rsp+9Ch] [rbp-24h]
  const LingZhuCfg *pLingZhuCfg; // [rsp+A0h] [rbp-20h]
  const LingZhuSuit *LingZhuSuitCfg; // [rsp+A8h] [rbp-18h]

  m_nKunLevel = this->m_nKunLevel;
  v2 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v2);
  pKunLevelUpCfg = KunLingTable::GetKunLevelUpCfg(KunLingTable, m_nKunLevel);
  if ( pKunLevelUpCfg )
  {
    for ( it._M_node = std::list<AddAttribute>::begin(&pKunLevelUpCfg->lAttrList)._M_node;
          ;
          std::_List_const_iterator<AddAttribute>::operator++(&it, 0) )
    {
      __x._M_node = std::list<AddAttribute>::end(&pKunLevelUpCfg->lAttrList)._M_node;
      if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it, &__x) )
        break;
      m_nAddAttrValue = std::_List_const_iterator<AddAttribute>::operator->(&it)->m_nAddAttrValue;
      v5 = std::_List_const_iterator<AddAttribute>::operator->(&it);
      Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v5->m_nAddAttrType, m_nAddAttrValue);
    }
  }
  for ( i = 0; i <= 19; ++i )
  {
    if ( this->m_LingZhuPos[i] > 0 )
    {
      v6 = this->m_LingZhuPos[i];
      v7 = Answer::Singleton<CfgData>::instance();
      v8 = CfgData::GetKunLingTable(v7);
      pLingZhuCfg = KunLingTable::GetLingZhuCfg(v8, v6);
      if ( pLingZhuCfg )
      {
        for ( it_0._M_node = std::list<AddAttribute>::begin(&pLingZhuCfg->lAttrList)._M_node;
              ;
              std::_List_const_iterator<AddAttribute>::operator++(&it_0, 0) )
        {
          v21._M_node = std::list<AddAttribute>::end(&pLingZhuCfg->lAttrList)._M_node;
          if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_0, &v21) )
            break;
          v9 = std::_List_const_iterator<AddAttribute>::operator->(&it_0)->m_nAddAttrValue;
          v10 = std::_List_const_iterator<AddAttribute>::operator->(&it_0);
          Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v10->m_nAddAttrType, v9);
        }
      }
    }
  }
  for ( it_1._M_node = std::list<int>::begin(&this->lSuitList)._M_node; ; std::_List_iterator<int>::operator++(&it_1, 0) )
  {
    v22._M_node = std::list<int>::end(&this->lSuitList)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it_1, &v22) )
      break;
    v11 = *std::_List_iterator<int>::operator*(&it_1);
    v12 = Answer::Singleton<CfgData>::instance();
    v13 = CfgData::GetKunLingTable(v12);
    LingZhuSuitCfg = KunLingTable::GetLingZhuSuit(v13, v11);
    if ( LingZhuSuitCfg )
    {
      for ( it_2._M_node = std::list<AddAttribute>::begin(&LingZhuSuitCfg->lAttrList)._M_node;
            ;
            std::_List_const_iterator<AddAttribute>::operator++(&it_2, 0) )
      {
        v23._M_node = std::list<AddAttribute>::end(&LingZhuSuitCfg->lAttrList)._M_node;
        if ( !std::_List_const_iterator<AddAttribute>::operator!=(&it_2, &v23) )
          break;
        v14 = std::_List_const_iterator<AddAttribute>::operator->(&it_2)->m_nAddAttrValue;
        v15 = std::_List_const_iterator<AddAttribute>::operator->(&it_2);
        Unit::AddAttrValue(this->m_pPlayer, (const CObjAttrs::Index_T)v15->m_nAddAttrType, v14);
      }
    }
  }
}


#####################################
void __cdecl CKunExt::SendKunLingInfo(CKunExt *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  int32_t LeftLianHuaTimes; // edx
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-18h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DDDu);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, this->m_nKunLevel);
      Answer::NetPacket::writeInt32(packet, this->m_nExp);
      Answer::NetPacket::writeInt32(packet, this->m_nBuyTime);
      LeftLianHuaTimes = CKunExt::GetLeftLianHuaTimes(this);
      Answer::NetPacket::writeInt32(packet, LeftLianHuaTimes);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CKunExt::SendLingZhuBagAllItem(CKunExt *const this)
{
  int8_t ConnId; // bl
  GameService *v2; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v5; // bl
  GameService *v6; // rax
  Answer::NetPacket *packet; // [rsp+18h] [rbp-28h]
  int32_t Count; // [rsp+20h] [rbp-20h]
  int32_t OldOffet; // [rsp+24h] [rbp-1Ch]
  int32_t NewOffet; // [rsp+28h] [rbp-18h]
  int i; // [rsp+2Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v2 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v2, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DDEu);
    if ( packet )
    {
      Count = 0;
      OldOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      for ( i = 0; i <= 99; ++i )
      {
        if ( !LingZhuBag::isEmpty(&this->m_LingZhuBag[i]) )
        {
          ++Count;
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt32(packet, this->m_LingZhuBag[i].nId);
          Answer::NetPacket::writeInt32(packet, this->m_LingZhuBag[i].nCount);
        }
      }
      NewOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, OldOffet);
      Answer::NetPacket::writeInt32(packet, Count);
      Answer::NetPacket::setWOffset(packet, NewOffet);
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
void __cdecl CKunExt::SendLingZhuBagChangeItem(CKunExt *const this, Int32List *p_ChangeList)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  int *v5; // rax
  int *v6; // rax
  int *v7; // rax
  uint32_t WOffset; // eax
  int16_t GateIndex; // r12
  int8_t v10; // bl
  GameService *v11; // rax
  std::_List_iterator<int> it; // [rsp+10h] [rbp-40h] BYREF
  std::_List_iterator<int> __x; // [rsp+20h] [rbp-30h] BYREF
  Answer::NetPacket *packet; // [rsp+28h] [rbp-28h]
  int32_t Count; // [rsp+34h] [rbp-1Ch]
  int32_t OldOffet; // [rsp+38h] [rbp-18h]
  int32_t NewOffet; // [rsp+3Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DDFu);
    if ( packet )
    {
      Count = 0;
      OldOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::writeInt32(packet, 0);
      for ( it._M_node = std::list<int>::begin(p_ChangeList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
      {
        __x._M_node = std::list<int>::end(p_ChangeList)._M_node;
        if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
          break;
        if ( *std::_List_iterator<int>::operator*(&it) >= 0 && *std::_List_iterator<int>::operator*(&it) <= 99 )
        {
          ++Count;
          v5 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, *v5);
          v6 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_LingZhuBag[*v6].nId);
          v7 = std::_List_iterator<int>::operator*(&it);
          Answer::NetPacket::writeInt32(packet, this->m_LingZhuBag[*v7].nCount);
        }
      }
      NewOffet = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setWOffset(packet, OldOffet);
      Answer::NetPacket::writeInt32(packet, Count);
      Answer::NetPacket::setWOffset(packet, NewOffet);
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
void __cdecl CKunExt::SendDanTianInfo(CKunExt *const this, int32_t Pos)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DE0u);
    if ( packet )
    {
      if ( Pos == -1 )
      {
        Answer::NetPacket::writeInt32(packet, 6);
        for ( i = 0; i <= 5; ++i )
        {
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt32(packet, this->m_DanTian[i].nMid);
          Answer::NetPacket::writeInt32(packet, this->m_DanTian[i].nEndTime);
          Answer::NetPacket::writeInt32(packet, this->m_DanTian[i].nId);
        }
      }
      else if ( (unsigned int)Pos > 5 )
      {
        Answer::NetPacket::writeInt32(packet, 0);
      }
      else
      {
        Answer::NetPacket::writeInt32(packet, 1);
        Answer::NetPacket::writeInt32(packet, Pos);
        Answer::NetPacket::writeInt32(packet, this->m_DanTian[Pos].nMid);
        Answer::NetPacket::writeInt32(packet, this->m_DanTian[Pos].nEndTime);
        Answer::NetPacket::writeInt32(packet, this->m_DanTian[Pos].nId);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
void __cdecl CKunExt::SendLingZhuPosInfo(CKunExt *const this, int32_t Pos)
{
  int8_t ConnId; // bl
  GameService *v3; // rax
  uint32_t WOffset; // edx
  int16_t GateIndex; // r12
  int8_t v6; // bl
  GameService *v7; // rax
  Answer::NetPacket *packet; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]

  if ( this->m_pPlayer )
  {
    ConnId = Player::getConnId(this->m_pPlayer);
    v3 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v3, ConnId, Answer::PackType::PACK_DISPATCH, 0x2DE1u);
    if ( packet )
    {
      if ( Pos == -1 )
      {
        Answer::NetPacket::writeInt32(packet, 20);
        for ( i = 0; i <= 19; ++i )
        {
          Answer::NetPacket::writeInt32(packet, i);
          Answer::NetPacket::writeInt32(packet, this->m_LingZhuPos[i]);
        }
      }
      else if ( (unsigned int)Pos >= 0x14 )
      {
        Answer::NetPacket::writeInt32(packet, 0);
      }
      else
      {
        Answer::NetPacket::writeInt32(packet, 1);
        Answer::NetPacket::writeInt32(packet, Pos);
        Answer::NetPacket::writeInt32(packet, this->m_LingZhuPos[Pos]);
      }
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      GateIndex = Player::getGateIndex(this->m_pPlayer);
      v6 = Player::getConnId(this->m_pPlayer);
      v7 = Answer::Singleton<GameService>::instance();
      GameService::sendPacketTo(v7, v6, GateIndex, packet);
    }
  }
}


#####################################
bool __cdecl CKunExt::AddLingZhuBagItem(
        CKunExt *const this,
        int32_t LingZhuId,
        int32_t Count,
        ITEM_CHANGE_REASON addReason)
{
  bool v4; // bl
  CfgData *v5; // rax
  const KunLingTable *KunLingTable; // rax
  CExtCharBag *Bag; // rax
  int32_t AllCount; // r13d
  int32_t nId; // r12d
  CExtCharBag *v10; // rax
  int32_t v11; // r12d
  CExtCharBag *v12; // rax
  Int32List ChangeList_0; // [rsp+30h] [rbp-90h] BYREF
  int32_t i_0; // [rsp+4Ch] [rbp-74h] BYREF
  Int32List ChangeList; // [rsp+50h] [rbp-70h] BYREF
  int32_t i; // [rsp+6Ch] [rbp-54h] BYREF
  std::list<int> p_ChangeList; // [rsp+70h] [rbp-50h] BYREF
  std::list<int> v21; // [rsp+80h] [rbp-40h] BYREF
  const LingZhuCfg *pLingZhuCfg; // [rsp+98h] [rbp-28h]

  if ( LingZhuId <= 0 || Count <= 0 || !this->m_pPlayer )
    return 0;
  v5 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v5);
  pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, LingZhuId);
  if ( !pLingZhuCfg )
    return 0;
  if ( pLingZhuCfg->nType == 100 )
  {
    this->m_nExp += Count * pLingZhuCfg->nDecExp;
    Bag = Player::GetBag(this->m_pPlayer);
    CExtCharBag::addItemChangeLog(Bag, addReason, LingZhuId, 11, 0, 2, Count, 0);
    CKunExt::SendKunLingInfo(this);
    return 1;
  }
  else
  {
    for ( i = 0; i <= 99; ++i )
    {
      if ( this->m_LingZhuBag[i].nId == LingZhuId )
      {
        this->m_LingZhuBag[i].nCount += Count;
        std::list<int>::list(&ChangeList);
        std::list<int>::push_back(&ChangeList, &i);
        std::list<int>::list(&p_ChangeList, &ChangeList);
        CKunExt::SendLingZhuBagChangeItem(this, &p_ChangeList);
        std::list<int>::~list(&p_ChangeList);
        AllCount = this->m_LingZhuBag[i].nCount;
        nId = this->m_LingZhuBag[i].nId;
        v10 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::addItemChangeLog(v10, addReason, nId, 11, 0, Count, 1, AllCount);
        v4 = 1;
        std::list<int>::~list(&ChangeList);
        return v4;
      }
    }
    for ( i_0 = 0; i_0 <= 99; ++i_0 )
    {
      if ( LingZhuBag::isEmpty(&this->m_LingZhuBag[i_0]) )
      {
        this->m_LingZhuBag[i_0].nId = LingZhuId;
        this->m_LingZhuBag[i_0].nCount = Count;
        std::list<int>::list(&ChangeList_0);
        std::list<int>::push_back(&ChangeList_0, &i_0);
        std::list<int>::list(&v21, &ChangeList_0);
        CKunExt::SendLingZhuBagChangeItem(this, &v21);
        std::list<int>::~list(&v21);
        v11 = this->m_LingZhuBag[i_0].nId;
        v12 = Player::GetBag(this->m_pPlayer);
        CExtCharBag::addItemChangeLog(v12, addReason, v11, 11, 0, Count, 1, Count);
        v4 = 1;
        std::list<int>::~list(&ChangeList_0);
        return v4;
      }
    }
    return 0;
  }
}


#####################################
int32_t __cdecl CKunExt::GetEmptyBagCount(CKunExt *const this)
{
  int32_t Count; // [rsp+18h] [rbp-8h]
  int32_t i; // [rsp+1Ch] [rbp-4h]

  Count = 0;
  for ( i = 0; i <= 99; ++i )
  {
    if ( LingZhuBag::isEmpty(&this->m_LingZhuBag[i]) )
      ++Count;
  }
  return Count;
}


#####################################
void __cdecl CKunExt::AddExp(CKunExt *const this, int32_t Exp)
{
  this->m_nExp += Exp;
  CKunExt::SendKunLingInfo(this);
}


#####################################
bool __cdecl CKunExt::ReMoveLingZhuItem(
        CKunExt *const this,
        int32_t LingZhuId,
        int32_t Count,
        ITEM_CHANGE_REASON addReason)
{
  bool v4; // bl
  int32_t AllCount; // r13d
  int32_t nId; // r12d
  CExtCharBag *Bag; // rax
  int32_t v8; // r12d
  CExtCharBag *v9; // rax
  int32_t i_0; // [rsp+3Ch] [rbp-54h] BYREF
  Int32List Pos; // [rsp+40h] [rbp-50h] BYREF
  std::list<int> p_ChangeList; // [rsp+50h] [rbp-40h] BYREF
  int32_t HaveCount; // [rsp+64h] [rbp-2Ch]
  int32_t NeedCount; // [rsp+68h] [rbp-28h]
  int32_t i; // [rsp+6Ch] [rbp-24h]

  HaveCount = 0;
  for ( i = 0; i <= 99; ++i )
  {
    if ( this->m_LingZhuBag[i].nId == LingZhuId )
    {
      HaveCount += this->m_LingZhuBag[i].nCount;
      if ( HaveCount >= Count )
        break;
    }
  }
  if ( HaveCount < Count )
    return 0;
  NeedCount = Count;
  std::list<int>::list(&Pos);
  std::list<int>::clear(&Pos);
  for ( i_0 = 0; i_0 <= 99 && NeedCount > 0; ++i_0 )
  {
    if ( this->m_LingZhuBag[i_0].nId == LingZhuId )
    {
      if ( this->m_LingZhuBag[i_0].nCount > NeedCount )
      {
        this->m_LingZhuBag[i_0].nCount -= NeedCount;
        AllCount = this->m_LingZhuBag[i_0].nCount;
        nId = this->m_LingZhuBag[i_0].nId;
        Bag = Player::GetBag(this->m_pPlayer);
        CExtCharBag::addItemChangeLog(Bag, addReason, nId, 11, 0, Count, 2, AllCount);
        std::list<int>::push_back(&Pos, &i_0);
        break;
      }
      NeedCount -= this->m_LingZhuBag[i_0].nCount;
      LingZhuBag::CleanUp(&this->m_LingZhuBag[i_0]);
      v8 = this->m_LingZhuBag[i_0].nId;
      v9 = Player::GetBag(this->m_pPlayer);
      CExtCharBag::addItemChangeLog(v9, addReason, v8, 11, 0, Count, 2, 0);
      std::list<int>::push_back(&Pos, &i_0);
    }
  }
  std::list<int>::list(&p_ChangeList, &Pos);
  CKunExt::SendLingZhuBagChangeItem(this, &p_ChangeList);
  std::list<int>::~list(&p_ChangeList);
  v4 = 1;
  std::list<int>::~list(&Pos);
  return v4;
}


#####################################
void __cdecl CKunExt::RemoveLingZhuItem(CKunExt *const this, Int32List *p_Pos, ITEM_CHANGE_REASON addReason)
{
  int32_t nCount; // r13d
  int32_t nId; // r12d
  CExtCharBag *Bag; // rax
  int *v7; // rax
  std::_List_iterator<int> it; // [rsp+30h] [rbp-50h] BYREF
  std::_List_iterator<int> __x; // [rsp+40h] [rbp-40h] BYREF
  std::list<int> p_ChangeList; // [rsp+50h] [rbp-30h] BYREF

  for ( it._M_node = std::list<int>::begin(p_Pos)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
  {
    __x._M_node = std::list<int>::end(p_Pos)._M_node;
    if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
      break;
    if ( *std::_List_iterator<int>::operator*(&it) >= 0 && *std::_List_iterator<int>::operator*(&it) <= 99 )
    {
      nCount = this->m_LingZhuBag[*std::_List_iterator<int>::operator*(&it)].nCount;
      nId = this->m_LingZhuBag[*std::_List_iterator<int>::operator*(&it)].nId;
      Bag = Player::GetBag(this->m_pPlayer);
      CExtCharBag::addItemChangeLog(Bag, addReason, nId, 11, 0, nCount, 2, 0);
      v7 = std::_List_iterator<int>::operator*(&it);
      LingZhuBag::CleanUp(&this->m_LingZhuBag[*v7]);
    }
  }
  std::list<int>::list(&p_ChangeList, p_Pos);
  CKunExt::SendLingZhuBagChangeItem(this, &p_ChangeList);
  std::list<int>::~list(&p_ChangeList);
}


#####################################
bool __cdecl CKunExt::AddDanTian(CKunExt *const this, int32_t Mid)
{
  CfgData *v2; // rax
  const KunLingTable *KunLingTable; // rax
  Answer::Random *v5; // rax
  const DanTianCfg *pDanTian; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]

  v2 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v2);
  pDanTian = KunLingTable::GetDanTianCfg(KunLingTable, Mid);
  if ( !pDanTian )
    return 0;
  v5 = Answer::Singleton<Answer::Random>::instance();
  if ( pDanTian->nRate < Answer::Random::generate(v5, 1, 10000) )
    return 0;
  for ( i = 0; i <= 5; ++i )
  {
    if ( DanTian::isEmpty(&this->m_DanTian[i]) )
    {
      this->m_DanTian[i].nMid = Mid;
      this->m_DanTian[i].nId = 0;
      this->m_DanTian[i].nEndTime = Unit::getNow(this->m_pPlayer) + pDanTian->nTime;
      CKunExt::SendDanTianInfo(this, i);
      return 1;
    }
  }
  return 0;
}


#####################################
int32_t __cdecl CKunExt::OnKunLingLevelUp(CKunExt *const this, Answer::NetPacket *inPacket)
{
  int32_t m_nKunLevel; // ebx
  CfgData *v4; // rax
  const KunLingTable *KunLingTable; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const KunLingTable *v8; // rax
  CExtCurrency *Currency; // rax
  int64_t nCostMoney; // rbx
  CExtCurrency *v11; // rax
  int32_t nTalentLevel; // r12d
  int32_t nTalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  GameService *v15; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v18; // rax
  int64_t nExp; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v23; // rax
  std::string val; // [rsp+10h] [rbp-50h] BYREF
  const KunLevelUpCfg *pKunLevelUpCfg; // [rsp+20h] [rbp-40h]
  const KunLevelUpCfg *pNextCfg; // [rsp+28h] [rbp-38h]
  int32_t KunLi; // [rsp+34h] [rbp-2Ch]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  m_nKunLevel = this->m_nKunLevel;
  v4 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v4);
  pKunLevelUpCfg = KunLingTable::GetKunLevelUpCfg(KunLingTable, m_nKunLevel);
  v6 = this->m_nKunLevel + 1;
  v7 = Answer::Singleton<CfgData>::instance();
  v8 = CfgData::GetKunLingTable(v7);
  pNextCfg = KunLingTable::GetKunLevelUpCfg(v8, v6);
  if ( !pNextCfg || !pKunLevelUpCfg )
    return 2;
  if ( pKunLevelUpCfg->nExp > 0 && this->m_nExp < pKunLevelUpCfg->nExp )
    return 2;
  if ( pKunLevelUpCfg->nCostMoney > 0 )
  {
    Currency = Player::GetCurrency(this->m_pPlayer);
    if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < pKunLevelUpCfg->nCostMoney )
      return 2;
  }
  if ( pKunLevelUpCfg->nCostShengYaoBi > 0
    && Player::GetCurrency(this->m_pPlayer, CURRENCY_TYPE::CURRENCY_VIGOUR) < pKunLevelUpCfg->nCostShengYaoBi )
  {
    return 2;
  }
  if ( pKunLevelUpCfg->nCostMoney > 0 )
  {
    nCostMoney = pKunLevelUpCfg->nCostMoney;
    v11 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v11, nCostMoney, CURRENCY_CHANGE_REASON::GCR_KUN_LEVEL_UP, 0) )
      return 2;
  }
  if ( pKunLevelUpCfg->nCostShengYaoBi > 0
    && !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_VIGOUR,
          pKunLevelUpCfg->nCostShengYaoBi,
          CURRENCY_CHANGE_REASON::GCR_KUN_LEVEL_UP,
          0) )
  {
    return 2;
  }
  if ( pKunLevelUpCfg->nExp > 0 )
    this->m_nExp -= pKunLevelUpCfg->nExp;
  if ( pNextCfg->nTalentId > 0 && pNextCfg->nTalentLevel )
  {
    nTalentLevel = pNextCfg->nTalentLevel;
    nTalentId = pNextCfg->nTalentId;
    CharSkill = Player::GetCharSkill(this->m_pPlayer);
    CExtCharSkill::AddOtherSkill(CharSkill, nTalentId, nTalentLevel);
  }
  ++this->m_nKunLevel;
  CKunExt::SendKunLingInfo(this);
  Player::recalcAttr(this->m_pPlayer, 1, 0);
  KunLi = Unit::GetAttrValue(this->m_pPlayer, CObjAttrs::Index_T::ATTR_KUN_LI);
  (*((void (__fastcall **)(Player *, _QWORD))this->m_pPlayer->_vptr_Entity + 23))(this->m_pPlayer, (unsigned int)KunLi);
  if ( pNextCfg->nGongGaoId > 0 )
  {
    v15 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v15, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pNextCfg->nGongGaoId);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, this->m_nKunLevel);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v18 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v18, 0, packet);
    }
  }
  nExp = pKunLevelUpCfg->nExp;
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v23 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v23, ConnId, GateIndex, Proc, nExp);
  return 0;
}


#####################################
int32_t __cdecl CKunExt::OnGetLingZhu(CKunExt *const this, Answer::NetPacket *inPacket)
{
  int32_t nId; // ebx
  CfgData *v4; // rax
  const KunLingTable *KunLingTable; // rax
  GameService *v6; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v9; // rax
  DanTian *v10; // rax
  std::string val; // [rsp+20h] [rbp-30h] BYREF
  int32_t Pos; // [rsp+2Ch] [rbp-24h]
  const LingZhuCfg *pLingZhuCfg; // [rsp+30h] [rbp-20h]
  Answer::NetPacket *packet; // [rsp+38h] [rbp-18h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  Pos = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned int)Pos >= 6 )
    return 2;
  if ( CKunExt::GetLeftLianHuaTimes(this) <= 0 )
    return 0;
  if ( DanTian::isEmpty(&this->m_DanTian[Pos]) )
    return 2;
  if ( this->m_DanTian[Pos].nEndTime > 0 )
    return 2;
  nId = this->m_DanTian[Pos].nId;
  v4 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v4);
  pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, nId);
  if ( !pLingZhuCfg )
    return 2;
  if ( !CKunExt::AddLingZhuBagItem(this, this->m_DanTian[Pos].nId, 1, ITEM_CHANGE_REASON::IDCR_DAN_TIAN_GET) )
    return 2;
  if ( pLingZhuCfg->nGetGongGao > 0 )
  {
    v6 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v6, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pLingZhuCfg->nGetGongGao);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, this->m_DanTian[Pos].nMid);
      Answer::NetPacket::writeInt32(packet, this->m_DanTian[Pos].nId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v9 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v9, 0, packet);
    }
  }
  ++this->m_nLianHuaTime;
  v10 = &this->m_DanTian[Pos];
  *(_QWORD *)&v10->nMid = 0;
  v10->nId = 0;
  CKunExt::SendDanTianInfo(this, Pos);
  CKunExt::SendKunLingInfo(this);
  return 0;
}


#####################################
int32_t __cdecl CKunExt::OnRecoveryLingZhu(CKunExt *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t nId; // ebx
  CfgData *v4; // rax
  const KunLingTable *KunLingTable; // rax
  int32_t v6; // ebx
  CfgData *v7; // rax
  const KunLingTable *v8; // rax
  int64_t v9; // r14
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v13; // rax
  int32_t i; // [rsp+1Ch] [rbp-64h] BYREF
  Int32List ChangeList; // [rsp+20h] [rbp-60h] BYREF
  std::list<int> p_Pos; // [rsp+30h] [rbp-50h] BYREF
  int32_t NeedAddExp; // [rsp+4Ch] [rbp-34h]
  const LingZhuCfg *pLingZhuCfg; // [rsp+50h] [rbp-30h]
  const LingZhuCfg *pLingZhuPosCfg; // [rsp+58h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  NeedAddExp = 0;
  std::list<int>::list(&ChangeList);
  for ( i = 0; i <= 99; ++i )
  {
    if ( !LingZhuBag::isEmpty(&this->m_LingZhuBag[i]) )
    {
      nId = this->m_LingZhuBag[i].nId;
      v4 = Answer::Singleton<CfgData>::instance();
      KunLingTable = CfgData::GetKunLingTable(v4);
      pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, nId);
      if ( pLingZhuCfg )
      {
        if ( pLingZhuCfg->nDecExp > 0 )
        {
          if ( pLingZhuCfg->nType >= 0x14u
            || (v6 = this->m_LingZhuPos[pLingZhuCfg->nType],
                v7 = Answer::Singleton<CfgData>::instance(),
                v8 = CfgData::GetKunLingTable(v7),
                (pLingZhuPosCfg = KunLingTable::GetLingZhuCfg(v8, v6)) != 0)
            && pLingZhuPosCfg->nNextId <= 0 )
          {
            NeedAddExp += pLingZhuCfg->nDecExp * this->m_LingZhuBag[i].nCount;
            std::list<int>::push_back(&ChangeList, &i);
          }
        }
      }
    }
  }
  if ( NeedAddExp > 0 )
  {
    std::list<int>::list(&p_Pos, &ChangeList);
    CKunExt::RemoveLingZhuItem(this, &p_Pos, ITEM_CHANGE_REASON::IDCR_BAO_ZHU_HUI_SHOU);
    std::list<int>::~list(&p_Pos);
    this->m_nExp += NeedAddExp;
    CKunExt::SendKunLingInfo(this);
    v9 = NeedAddExp;
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v13 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v13, ConnId, GateIndex, Proc, v9);
    v2 = 0;
  }
  else
  {
    v2 = 2;
  }
  std::list<int>::~list(&ChangeList);
  return v2;
}


#####################################
int32_t __cdecl CKunExt::OnFastFining(CKunExt *const this, Answer::NetPacket *inPacket)
{
  int32_t nMid; // ebx
  CfgData *v4; // rax
  const KunLingTable *KunLingTable; // rax
  unsigned int Slot; // [rsp+14h] [rbp-2Ch]
  const DanTianCfg *pDanTian; // [rsp+18h] [rbp-28h]
  int32_t DiffTime; // [rsp+28h] [rbp-18h]
  int32_t Count; // [rsp+2Ch] [rbp-14h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  Slot = Answer::NetPacket::readInt32(inPacket);
  if ( Slot >= 6 )
    return 2;
  if ( DanTian::isEmpty(&this->m_DanTian[Slot]) )
    return 2;
  if ( this->m_DanTian[Slot].nEndTime <= 0 )
    return 2;
  nMid = this->m_DanTian[Slot].nMid;
  v4 = Answer::Singleton<CfgData>::instance();
  KunLingTable = CfgData::GetKunLingTable(v4);
  pDanTian = KunLingTable::GetDanTianCfg(KunLingTable, nMid);
  if ( !pDanTian )
    return 2;
  DiffTime = this->m_DanTian[Slot].nEndTime - Unit::getNow(this->m_pPlayer);
  if ( DiffTime <= 0 )
    return 2;
  Count = DiffTime / 600;
  if ( DiffTime % 600 )
    ++Count;
  if ( !Player::DecCurrency(
          this->m_pPlayer,
          CURRENCY_TYPE::CURRENCY_GOLD,
          10 * Count,
          CURRENCY_CHANGE_REASON::GCR_KUN_KAST_FINING_COST,
          0) )
    return 2;
  this->m_DanTian[Slot].nEndTime = 0;
  if ( this->m_nKunLevel <= 10 )
    this->m_DanTian[Slot].nId = DanTianCfg::RandDanTianId(pDanTian);
  else
    this->m_DanTian[Slot].nId = DanTianCfg::RandHighDanTianId(pDanTian);
  CKunExt::SendDanTianInfo(this, Slot);
  return 0;
}


#####################################
int32_t __cdecl CKunExt::OnLingZhuLevelUp(CKunExt *const this, Answer::NetPacket *inPacket)
{
  CfgData *v3; // rax
  const KunLingTable *v4; // rax
  CExtCurrency *v5; // rax
  CfgData *v6; // rax
  const KunLingTable *KunLingTable; // rax
  CExtCurrency *Currency; // rax
  int64_t v9; // rbx
  CExtCurrency *v10; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  CfgData *v15; // rax
  const KunLingTable *v16; // rax
  GameService *v17; // rax
  CharId_t Cid; // rax
  uint32_t WOffset; // eax
  GameService *v20; // rax
  LingZhuBag NeedItem; // [rsp+10h] [rbp-70h] BYREF
  std::string val; // [rsp+20h] [rbp-60h] BYREF
  int32_t Pos; // [rsp+30h] [rbp-50h]
  int32_t NeedMoney; // [rsp+34h] [rbp-4Ch]
  int32_t nId; // [rsp+38h] [rbp-48h]
  int32_t OldId; // [rsp+3Ch] [rbp-44h]
  const LingZhuCfg *pNewLingZhuCfg; // [rsp+40h] [rbp-40h]
  const LingZhuPosCfg *pFirstCfg; // [rsp+48h] [rbp-38h]
  const LingZhuCfg *pLingZhuCfg; // [rsp+50h] [rbp-30h]
  Answer::NetPacket *packet; // [rsp+58h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  Pos = Answer::NetPacket::readInt32(inPacket);
  if ( (unsigned int)Pos >= 0x14 )
    return 2;
  NeedItem = 0;
  NeedMoney = 0;
  nId = this->m_LingZhuPos[Pos];
  if ( nId > 0 )
  {
    v6 = Answer::Singleton<CfgData>::instance();
    KunLingTable = CfgData::GetKunLingTable(v6);
    pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, nId);
    if ( !pLingZhuCfg )
      return 2;
    if ( pLingZhuCfg->nKunLingLevel > this->m_nKunLevel )
      return 2;
    if ( pLingZhuCfg->nCostMoney > 0 )
    {
      Currency = Player::GetCurrency(this->m_pPlayer);
      if ( CExtCurrency::GetMoneyBindAndNoBind(Currency) < pLingZhuCfg->nCostMoney )
        return 2;
      NeedMoney = pLingZhuCfg->nCostMoney;
    }
    NeedItem = *(LingZhuBag *)&pLingZhuCfg->nCostId;
    nId = pLingZhuCfg->nNextId;
  }
  else
  {
    v3 = Answer::Singleton<CfgData>::instance();
    v4 = CfgData::GetKunLingTable(v3);
    pFirstCfg = KunLingTable::GetLingZhuPosId(v4, Pos);
    if ( pFirstCfg )
    {
      nId = pFirstCfg->nFirstId;
      NeedItem = *(LingZhuBag *)&pFirstCfg->nCostId;
      if ( pFirstCfg->nMoney > 0 )
      {
        v5 = Player::GetCurrency(this->m_pPlayer);
        if ( CExtCurrency::GetMoneyBindAndNoBind(v5) < pFirstCfg->nMoney )
          return 2;
        NeedMoney = pFirstCfg->nMoney;
      }
    }
  }
  if ( nId <= 0 )
    return 2;
  if ( LingZhuBag::isEmpty(&NeedItem) )
    return 2;
  if ( !CKunExt::ReMoveLingZhuItem(this, NeedItem.nId, NeedItem.nCount, ITEM_CHANGE_REASON::IDCR_LING_ZHU_LEVEL_UP) )
    return 2;
  if ( NeedMoney > 0 )
  {
    v9 = NeedMoney;
    v10 = Player::GetCurrency(this->m_pPlayer);
    if ( !CExtCurrency::DecMoneyAndNoBind(v10, v9, CURRENCY_CHANGE_REASON::GCR_LING_ZHU_JI_HUO, 0) )
      return 2;
  }
  OldId = this->m_LingZhuPos[Pos];
  this->m_LingZhuPos[Pos] = nId;
  CKunExt::SendLingZhuPosInfo(this, Pos);
  CKunExt::CheckSuit(this);
  Player::RecalcAttr(this->m_pPlayer);
  Proc = Answer::NetPacket::getProc(inPacket);
  GateIndex = Player::getGateIndex(this->m_pPlayer);
  ConnId = Player::getConnId(this->m_pPlayer);
  v14 = Answer::Singleton<GameService>::instance();
  GameService::replySuccess(v14, ConnId, GateIndex, Proc, 0);
  v15 = Answer::Singleton<CfgData>::instance();
  v16 = CfgData::GetKunLingTable(v15);
  pNewLingZhuCfg = KunLingTable::GetLingZhuCfg(v16, nId);
  if ( pNewLingZhuCfg && pNewLingZhuCfg->nLevelUpGongGao )
  {
    v17 = Answer::Singleton<GameService>::instance();
    packet = GameService::popNetpacket(v17, 0, Answer::PackType::PACK_DISPATCH, 0x2CD6u);
    if ( packet )
    {
      Answer::NetPacket::writeInt32(packet, pNewLingZhuCfg->nLevelUpGongGao);
      Cid = Player::getCid(this->m_pPlayer);
      Answer::NetPacket::writeInt64(packet, Cid);
      Player::getName((const Player *const)&val);
      Answer::NetPacket::writeUTF8(packet, &val);
      std::string::~string(&val);
      Answer::NetPacket::writeInt32(packet, OldId);
      Answer::NetPacket::writeInt32(packet, nId);
      WOffset = Answer::NetPacket::getWOffset(packet);
      Answer::NetPacket::setSize(packet, WOffset);
      v20 = Answer::Singleton<GameService>::instance();
      GameService::worldBroadcast(v20, 0, packet);
    }
  }
  return 0;
}


#####################################
int32_t __cdecl CKunExt::OnBuyLianHuaTime(CKunExt *const this, Answer::NetPacket *inPacket)
{
  if ( !this->m_pPlayer || !inPacket )
    return 2;
  if ( this->m_nBuyTime > 1 )
    return 2;
  if ( !this->m_nBuyTime )
  {
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            500,
            CURRENCY_CHANGE_REASON::GCR_BUY_LIAN_HUA_TIME,
            0) )
      return 2;
LABEL_13:
    ++this->m_nBuyTime;
    CKunExt::SendKunLingInfo(this);
    return 0;
  }
  if ( this->m_nBuyTime == 1 )
  {
    if ( !Player::DecCurrency(
            this->m_pPlayer,
            CURRENCY_TYPE::CURRENCY_GOLD,
            2000,
            CURRENCY_CHANGE_REASON::GCR_BUY_LIAN_HUA_TIME,
            0) )
      return 2;
    goto LABEL_13;
  }
  return 0;
}


#####################################
int32_t __cdecl CKunExt::OnKunWeiYang(CKunExt *const this, Answer::NetPacket *inPacket)
{
  int32_t v2; // ebx
  int32_t v3; // ebx
  CExtCharBag *Bag; // rax
  int32_t itemId; // ebx
  CfgData *v6; // rax
  int32_t v8; // ebx
  CExtCharBag *v9; // rax
  CExtCharBag *v10; // rax
  uint16_t Proc; // r13
  int16_t GateIndex; // r12
  int8_t ConnId; // bl
  GameService *v14; // rax
  int32_t BagSlot; // [rsp+1Ch] [rbp-74h] BYREF
  std::_List_iterator<int> it; // [rsp+20h] [rbp-70h] BYREF
  Int32List bagSlotList; // [rsp+30h] [rbp-60h] BYREF
  std::_List_iterator<int> __x; // [rsp+40h] [rbp-50h] BYREF
  int32_t nSize; // [rsp+54h] [rbp-3Ch]
  int32_t AddValues; // [rsp+58h] [rbp-38h]
  int32_t i; // [rsp+5Ch] [rbp-34h]
  const MemChrBag *slotData; // [rsp+60h] [rbp-30h]
  CfgItem *cfgItem; // [rsp+68h] [rbp-28h]

  if ( !this->m_pPlayer || !inPacket )
    return 2;
  nSize = Answer::NetPacket::readInt32(inPacket);
  AddValues = 0;
  std::list<int>::list(&bagSlotList);
  for ( i = 0; i < nSize; ++i )
  {
    BagSlot = Answer::NetPacket::readInt32(inPacket);
    v3 = BagSlot;
    Bag = Player::GetBag(this->m_pPlayer);
    slotData = CExtCharBag::GetSlotData(Bag, v3);
    if ( slotData->itemClass != 1 )
    {
      v2 = 2;
      goto LABEL_23;
    }
    itemId = slotData->itemId;
    v6 = Answer::Singleton<CfgData>::instance();
    cfgItem = CfgData::getItem(v6, itemId);
    if ( !cfgItem )
    {
      v2 = 2;
      goto LABEL_23;
    }
    if ( cfgItem->KunLingJingHua <= 0 )
    {
      v2 = 2;
      goto LABEL_23;
    }
    AddValues += cfgItem->KunLingJingHua * slotData->itemCount;
    std::list<int>::push_back(&bagSlotList, &BagSlot);
  }
  if ( AddValues <= 0 || !std::list<int>::size(&bagSlotList) )
  {
    v2 = 2;
  }
  else
  {
    for ( it._M_node = std::list<int>::begin(&bagSlotList)._M_node; ; std::_List_iterator<int>::operator++(&it, 0) )
    {
      __x._M_node = std::list<int>::end(&bagSlotList)._M_node;
      if ( !std::_List_iterator<int>::operator!=(&it, &__x) )
        break;
      v8 = *std::_List_iterator<int>::operator*(&it);
      v9 = Player::GetBag(this->m_pPlayer);
      CExtCharBag::CleanSlot(v9, v8, ITEM_CHANGE_REASON::IDCR_KUN_WEI_YANG);
    }
    v10 = Player::GetBag(this->m_pPlayer);
    CExtCharBag::ForceSendDirty(v10);
    this->m_nExp += AddValues;
    CKunExt::SendKunLingInfo(this);
    Proc = Answer::NetPacket::getProc(inPacket);
    GateIndex = Player::getGateIndex(this->m_pPlayer);
    ConnId = Player::getConnId(this->m_pPlayer);
    v14 = Answer::Singleton<GameService>::instance();
    GameService::replySuccess(v14, ConnId, GateIndex, Proc, 0);
    v2 = 0;
  }
LABEL_23:
  std::list<int>::~list(&bagSlotList);
  return v2;
}


#####################################
void __cdecl CKunExt::CheckSuit(CKunExt *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const KunLingTable *KunLingTable; // rax
  int32_t nSuitId; // eax
  int32_t SuitId; // [rsp+1Ch] [rbp-24h] BYREF
  int32_t i; // [rsp+20h] [rbp-20h]
  int32_t j; // [rsp+24h] [rbp-1Ch]
  const LingZhuCfg *pLingZhuCfg; // [rsp+28h] [rbp-18h]

  std::list<int>::clear(&this->lSuitList);
  for ( i = 0; i <= 3; ++i )
  {
    SuitId = 0;
    for ( j = 5 * i; 5 * (i + 1) > j; ++j )
    {
      if ( this->m_LingZhuPos[j] < 0 )
      {
        SuitId = 0;
        break;
      }
      v1 = this->m_LingZhuPos[j];
      v2 = Answer::Singleton<CfgData>::instance();
      KunLingTable = CfgData::GetKunLingTable(v2);
      pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, v1);
      if ( !pLingZhuCfg || pLingZhuCfg->nSuitId <= 0 )
      {
        SuitId = 0;
        break;
      }
      if ( SuitId )
      {
        if ( pLingZhuCfg->nSuitId >= SuitId )
          nSuitId = SuitId;
        else
          nSuitId = pLingZhuCfg->nSuitId;
        SuitId = nSuitId;
      }
      else
      {
        SuitId = pLingZhuCfg->nSuitId;
      }
    }
    if ( SuitId > 0 )
      std::list<int>::push_back(&this->lSuitList, &SuitId);
  }
  CKunExt::CheckAddSuitSkill(this);
}


#####################################
void __cdecl CKunExt::CheckAddSuitSkill(CKunExt *const this)
{
  int32_t v1; // ebx
  CfgData *v2; // rax
  const KunLingTable *KunLingTable; // rax
  int nLevel; // eax
  CfgData *v5; // rax
  const KunLingTable *v6; // rax
  int32_t TalentLevel; // r12d
  int32_t TalentId; // ebx
  CExtCharSkill *CharSkill; // rax
  int nSuitLevel; // [rsp+18h] [rbp-28h]
  int32_t i; // [rsp+1Ch] [rbp-24h]
  const LingZhuCfg *pLingZhuCfg; // [rsp+20h] [rbp-20h]
  const LingZhuSkill *pLingZhuSkill; // [rsp+28h] [rbp-18h]

  nSuitLevel = 0;
  for ( i = 0; i <= 19; ++i )
  {
    if ( this->m_LingZhuPos[i] <= 0 )
      return;
    v1 = this->m_LingZhuPos[i];
    v2 = Answer::Singleton<CfgData>::instance();
    KunLingTable = CfgData::GetKunLingTable(v2);
    pLingZhuCfg = KunLingTable::GetLingZhuCfg(KunLingTable, v1);
    if ( !pLingZhuCfg || pLingZhuCfg->nLevel <= 0 )
      return;
    if ( nSuitLevel )
    {
      if ( pLingZhuCfg->nLevel >= nSuitLevel )
        nLevel = nSuitLevel;
      else
        nLevel = pLingZhuCfg->nLevel;
      nSuitLevel = nLevel;
    }
    else
    {
      nSuitLevel = pLingZhuCfg->nLevel;
    }
  }
  if ( nSuitLevel > 0 )
  {
    v5 = Answer::Singleton<CfgData>::instance();
    v6 = CfgData::GetKunLingTable(v5);
    pLingZhuSkill = KunLingTable::GetLingZhuSkill(v6, nSuitLevel);
    if ( pLingZhuSkill )
    {
      if ( pLingZhuSkill->TalentId > 0 && pLingZhuSkill->TalentLevel > 0 )
      {
        TalentLevel = pLingZhuSkill->TalentLevel;
        TalentId = pLingZhuSkill->TalentId;
        CharSkill = Player::GetCharSkill(this->m_pPlayer);
        CExtCharSkill::AddOtherSkill(CharSkill, TalentId, TalentLevel);
      }
    }
  }
}


#####################################
int32_t __cdecl CKunExt::GetLeftLianHuaTimes(CKunExt *const this)
{
  int32_t AddTime; // [rsp+14h] [rbp-4h]

  AddTime = 0;
  if ( this->m_nBuyTime == 1 )
  {
    AddTime = 5;
  }
  else if ( this->m_nBuyTime == 2 )
  {
    AddTime = 15;
  }
  return AddTime + 10 - this->m_nLianHuaTime;
}


